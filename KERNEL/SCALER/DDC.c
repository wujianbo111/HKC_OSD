#include "types.h"
#include "ms_reg.h"
#include "ms_rwreg.h"
#include "Global.h"
#include "MsID_V1.h"
#include "UserPref.h"
#include "nvram.h"	//120420 Modify
#include "msflash.h"

#include "EDID.H"

#include "I2C.H"

extern void SetPWMFreq(WORD freq);
#define CheckDDCAddr1	0x10
#define CheckDDCAddr2	0x20

#if (CHIP_ID==CHIP_TSUMF)
#define _BIT(a)                         (BIT0 << a)
#define MASKBIT(a)                      (_BIT((1?a) +1) -_BIT((0?a)))
#endif
//extern void i2c_WriteTBL(BYTE deviceID, WORD addr, BYTE *buffer, BYTE count);
//extern void i2c_ReadTBL(BYTE deviceID,WORD addr,BYTE * buffer,BYTE count);


#define NVRAM_ADDR_EDID          0x00
#if ((!VGA_Write_EEPROM&&ENABLE_VGA)||(!DVI_Write_EEPROM&&ENABLE_DVI))
void mStar_ClrDDC_WP(void)
{
	#if (ENABLE_DVI&&(!DVI_Write_EEPROM))
	msWriteByte(REG_3E45, BIT7);
	#else
	msWriteByte(REG_3E45, BIT0);
	#endif
	msWriteByte(REG_3E49, BIT7); //ADC DDC disable write protect
	msWriteByte(REG_3E4B, msReadByte(REG_3E4B) & ~BIT7);
}

void mStar_SetDDC_WP(void)    //
{
	#if (ENABLE_DVI&&(!DVI_Write_EEPROM))
	msWriteByte(REG_3E45, BIT7 | BIT5);
	#else
	msWriteByte(REG_3E45, BIT0);
	#endif
	#if CHIP_ID==CHIP_TSUMF
	msWriteByteMask(REG_3EFA, 0, 0x0F);   // REG_DDC_BANK_7D[4:0]: Select A0 EDID sram base address
	msWriteByte(REG_3E49, BIT7 | BIT5); //ADC DDC Enable write protect
	#else
	msWriteByte(REG_3E49, BIT7 | BIT5); //ADC DDC Enable write protect
	#endif
	msWriteByte(REG_3E4B, msReadByte(REG_3E4B) | BIT7);
}
#endif
#if User_DDCTO_FlashSave
Bool CheckFlashEDIDData(void)
{
	if(DDC1[0] == 0x00 && DDC1[1] == 0xFF && DDC1[2] == 0xFF && DDC1[3] == 0xFF && DDC1[4] == 0xFF && DDC1[5] == 0xFF && DDC1[6] == 0xFF && DDC1[7] == 0x00)
	{
		return TRUE;
	}
	else
		return FALSE;
}
#endif

#if ((!VGA_Write_EEPROM)&&ENABLE_VGA)
void mStar_VGADDC_Base_Address(void)
{
	#if CHIP_ID==CHIP_TSUMF
	msWriteByteMask(REG_0260, 0, BIT2 | BIT3);
	#endif
	#if (CHIP_ID == CHIP_TSUMC||CHIP_ID == CHIP_TSUMD)
	msWriteByte( REG_3EEC, 0x11);                                           // EDID Set Base address
	msWriteByte( REG_3EED, 0x03);
	#elif (CHIP_ID==CHIP_TSUMF)
	msWriteByte( REG_3EEC, 0x11);
	#endif
	#if (CHIP_ID == CHIP_TSUMC||CHIP_ID == CHIP_TSUMD)
	msWriteByteMask( REG_3EEB, 0x00, 0xF0);
	#elif (CHIP_ID==CHIP_TSUMF)
	msWriteByteMask(REG_3EEB, 0, 0x0F);   // REG_DDC_BANK_75[12:8]: Select EDID sram base address for cpu read/write
	#endif
}
#endif
#if ((!DVI_Write_EEPROM)&&ENABLE_DVI)
void mStar_DVIDDC_Base_Address(void)
{
	#if CHIP_ID==CHIP_TSUMF
	msWriteByteMask(REG_0260, 0, BIT2 | BIT3);
	#endif
	#if (CHIP_ID == CHIP_TSUMC||CHIP_ID == CHIP_TSUMD)
	msWriteByte( REG_3EEC, 0x11);                                           // EDID Set Base address
	msWriteByte( REG_3EED, 0x03);
	#elif (CHIP_ID==CHIP_TSUMF)
	msWriteByte( REG_3EEC, 0x11);
	msWriteByteMask(REG_3EEB, 1, MASKBIT(4: 0));
	msWriteByteMask(REG_3E43, 0, BIT1);
	#endif
	#if (CHIP_ID == CHIP_TSUMC||CHIP_ID == CHIP_TSUMD)
	msWriteByteMask( REG_3EEB, 0x10, 0xF0);
	#elif (CHIP_ID==CHIP_TSUMF)
	msWriteByteMask(REG_3EEB, 0x01, 0x1F);   // REG_DDC_BANK_75[12:8]: Select EDID sram base address for cpu read/write
	#endif
}
#endif

#if User_DDCTO_FlashSave
void CleanDDCBuff (void)
{
	BYTE i = 0;
	for(i = 0; i < 20; i++)
		DDC1[i] = 0xFF;
}
#endif

//2返回值 :   烧录成功/失败
#define		TryToModDdcFunction	0


#if		TryToModDdcFunction
Bool		Init_AllPort_Ddc_ToE2PROM_Func(const BYTE DdcPort, const BYTE DdcDate[], const WORD DdcCount)
{
	BYTE dd = 0;
	WORD i = 0;
	Bool Result = FALSE;
	BYTE  ReadCheckSum = 0;
	EnableReadDDCType = DdcPort;
	Init_NVRAM_I2C_SCL_Pin();
	Init_NVRAM_I2C_SDA_Pin();
	hw_ClrDDC_WP();
	for(i = 0; i < DdcCount; i++)
	{
		NVRam_WriteByte(NVRAM_ADDR_EDID + i, DdcDate[i]);
	}
	hw_SetDDC_WP();
	Delay1ms(2);
	ReadCheckSum = 0;
	for(i = 0; i < DdcCount; i++)
	{
		NVRam_ReadByte(NVRAM_ADDR_EDID + i, &dd);
		DDC1[i] = dd;
		ReadCheckSum += DDC1[i];
	}
	if((DDC1[0] == 0x00) && (DDC1[1] == 0xFF) && (DDC1[2] == 0xFF) && (DDC1[3] == 0xFF) && (DDC1[4] == 0xFF)
	        && (DDC1[5] == 0xFF) && (DDC1[6] == 0xFF) && (DDC1[7] == 0x00) && (DDC1[0x7F] == DdcDate[0x7F]))
	{
		if ((ReadCheckSum) == 0)
		{
			Result = TRUE;
		}
	}
	EnableReadDDCType = I2C_EEPROM;
	Init_NVRAM_I2C_SCL_Pin();
	Init_NVRAM_I2C_SDA_Pin();
	return Result;
}


#if ENABLE_VGA
void mStar_VGA_InitDDC(void)
{
	#if VGA_Write_EEPROM
	if (Load_VGAEDID_Flag)
	{
		BYTE ChecKVGADoubleFlag = 0;
		#if User_DDCTO_FlashSave
		BYTE EDID_CheckSum = 0 ;
		#endif
		#if USEFLASH
		#if User_DDCTO_FlashSave
		CleanDDCBuff ();
		Flash_Read_Factory_KeySet(FLASH_KEY_DDCA, TRUE, 0, DDCAKEY_SIZE, &DDC1, DDCAKEY_SIZE);
		EDID_CheckSum = DDC1[0x7F];
		#else
#message "VGA DDC Data User Default EDID"
		#endif
		#endif
		#if User_DDCTO_FlashSave
		if (CheckFlashEDIDData())
		{
			ChecKVGADoubleFlag = Init_AllPort_Ddc_ToE2PROM_Func(VGA_EDID, DDC1, 128);
		}
		else
		#endif
		{
			ChecKVGADoubleFlag = Init_AllPort_Ddc_ToE2PROM_Func(VGA_EDID, EDID_vga, 128);
		}
		if (ChecKVGADoubleFlag)
		{
			Clr_Load_VGAEDID_Flag();
			#if USEFLASH
			UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit );
			#else
			NVRam_WriteWord(nvrMonitorAddr(MonitorFlag), MonitorFlags);
			#endif
		}
	}
	#else
	BYTE i;
	mStar_ClrDDC_WP();
	mStar_VGADDC_Base_Address();
	#if USEFLASH
	#if User_DDCTO_FlashSave
	Flash_Read_Factory_KeySet(FLASH_KEY_DDCA, TRUE, 0, DDCAKEY_SIZE, &DDC1, DDCAKEY_SIZE);
	#else
#message "VGA DDC Data User Default EDID"
	#endif
	#else
	//NVRam_ReadTbl(DDC_ADC_ADDR, DDC1, 128);
	#endif
	#if User_DDCTO_FlashSave
	if(CheckFlashEDIDData())
	{
		for(i = 0; i < 128; i++)
		{
			msWriteByte(REG_3E4B, i);
			msWriteByte(REG_3E4C, DDC1[i]);
			msWriteByteMask(REG_3E43, BIT5, BIT5);
			while(msReadByte(REG_3E7B) & BIT5);
		}
	}
	else
	#endif
	{
		for(i = 0; i < 128; i++)
		{
			msWriteByte(REG_3E4B, i);
			msWriteByte(REG_3E4C, EDID_vga[i]);
			msWriteByteMask(REG_3E43, BIT5, BIT5);
			while(msReadByte(REG_3E7B) & BIT5);
		}
	}
	mStar_SetDDC_WP();
	#endif
}
#endif
#if ENABLE_DVI
void mStar_DVI_InitDDC(void)
{
	#if DVI_Write_EEPROM
	#if DEBUG_PRINTDATA
	printData("Load_DVIIEDID_FlagAA=%d", Load_DVIIEDID_Flag);
	#endif
	if (Load_DVIIEDID_Flag)
	{
		BYTE ChecKDVIDoubleFlag = 0;
		#if User_DDCTO_FlashSave
		BYTE EDID_CheckSum = 0 ;
		#endif
		#if USEFLASH
		#if User_DDCTO_FlashSave
		CleanDDCBuff ();
		Flash_Read_Factory_KeySet(FLASH_KEY_DDCD, TRUE, 0, DDCDKEY_SIZE, &DDC1, DDCDKEY_SIZE);
		EDID_CheckSum = DDC1[0x7F];
		#else
#message "DVI DDC Data User Default EDID"
		#endif
		#endif
		#if User_DDCTO_FlashSave
		if (CheckFlashEDIDData())
		{
			ChecKDVIDoubleFlag = Init_AllPort_Ddc_ToE2PROM_Func(DVI_EDID, DDC1, 128);
		}
		else
		#endif
		{
			ChecKDVIDoubleFlag = Init_AllPort_Ddc_ToE2PROM_Func(DVI_EDID, EDID_dvi, 128);
		}
		if (ChecKDVIDoubleFlag)
		{
			Clr_Load_DVIEDID_Flag();
			#if USEFLASH
			UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit );
			#else
			NVRam_WriteWord(nvrMonitorAddr(MonitorFlag), MonitorFlags);
			#endif
		}
	}
	#else
	BYTE i;
	mStar_ClrDDC_WP();
	mStar_DVIDDC_Base_Address();
	#if USEFLASH
	#if User_DDCTO_FlashSave
	Flash_Read_Factory_KeySet(FLASH_KEY_DDCD, TRUE, 0, DDCDKEY_SIZE, &DDC1, DDCDKEY_SIZE);
	#else
#message "DVI DDC Data User Default EDID"
	#endif
	#else
	//NVRam_ReadTbl(DDC_ADC_ADDR, DDC1, 128);
	#endif
	#if User_DDCTO_FlashSave
	if(CheckFlashEDIDData())
	{
		for(i = 0; i < 128; i++)
		{
			msWriteByte(REG_3E4B, i);
			msWriteByte(REG_3E4C, DDC1[i]);
			msWriteByteMask(REG_3E43, BIT5, BIT5);
		}
	}
	else
	#endif
	{
		for(i = 0; i < 128; i++)
		{
			msWriteByte(REG_3E4B, i);
			msWriteByte(REG_3E4C, EDID_dvi[i]);
			msWriteByteMask(REG_3E43, BIT5, BIT5);
		}
	}
	Delay1ms(100);
	mStar_SetDDC_WP(void)();
	#endif
}
#endif
#if ENABLE_HDMI
void mStar_HDMI_InitDDC(void)
{
	#if HDMI_Write_EEPROM
	if (Load_HDMIEDID_Flag)
	{
		BYTE ChecKHDMIDoubleFlag = 0;
		#if User_DDCTO_FlashSave
		BYTE EDID_CheckSum = 0 ;
		#endif
		#if USEFLASH
		#if User_DDCTO_FlashSave
		CleanDDCBuff ();
		Flash_Read_Factory_KeySet(FLASH_KEY_DDCH, TRUE, 0, DDCHKEY_SIZE, &DDC1, DDCHKEY_SIZE);
		EDID_CheckSum = DDC1[0x7F];
		#else
#message "HDMI DDC Data User Default EDID"
		#endif
		#endif
		#if User_DDCTO_FlashSave
		if (CheckFlashEDIDData())
		{
			ChecKHDMIDoubleFlag = Init_AllPort_Ddc_ToE2PROM_Func(HDMI_EDID, DDC1, 256);
		}
		else
		#endif
		{
			ChecKHDMIDoubleFlag = Init_AllPort_Ddc_ToE2PROM_Func(HDMI_EDID, EDID_hdmi, 256);
		}
		if (ChecKHDMIDoubleFlag)
		{
			Clr_Load_HDMIEDID_Flag();
			#if USEFLASH
			UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit );
			#else
			NVRam_WriteWord(nvrMonitorAddr(MonitorFlag), MonitorFlags);
			#endif
		}
	}
	#endif
	#if CHIP_ID==CHIP_TSUMF
	DDC_Port_Sel();
	#endif
}
#endif
#if ENABLE_HDMI2
void mStar_HDMI2_InitDDC(void)
{
	#if HDMI2_Write_EEPROM
	if (Load_HDMI2EDID_Flag)
	{
		BYTE ChecKHDMIDoubleFlag = 0;
		#if User_DDCTO_FlashSave
		BYTE EDID_CheckSum = 0 ;
		#endif
		#if USEFLASH
		#if User_DDCTO_FlashSave
		CleanDDCBuff ();
		Flash_Read_Factory_KeySet(FLASH_KEY_DDCH, TRUE, 0, DDCHKEY_SIZE, &DDC1, DDCHKEY_SIZE);
		EDID_CheckSum = DDC1[0x7F];
		#else
#message "HDMI2 DDC Data User Default EDID"
		#endif
		#endif
		#if User_DDCTO_FlashSave
		if (CheckFlashEDIDData())
		{
			ChecKHDMIDoubleFlag = Init_AllPort_Ddc_ToE2PROM_Func(HDMI2_EDID, DDC1, 256);
		}
		else
		#endif
		{
			ChecKHDMIDoubleFlag = Init_AllPort_Ddc_ToE2PROM_Func(HDMI2_EDID, EDID_hdmi2, 256);
		}
		if (ChecKHDMIDoubleFlag)
		{
			Clr_Load_HDMI2EDID_Flag();
			#if USEFLASH
			UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit );
			#else
			NVRam_WriteWord(nvrMonitorAddr(MonitorFlag), MonitorFlags);
			#endif
		}
	}
	#endif
}
#endif


#else



#if ENABLE_VGA
void mStar_VGA_InitDDC(void)
{
	#if VGA_Write_EEPROM
	if (Load_VGAEDID_Flag)
	{
		BYTE i;
		BYTE  ReadCheckSum = 0;
		BYTE  dd = 0;
		BYTE CheckVGADoubleFlag = 0;
		#if User_DDCTO_FlashSave
		BYTE EDID_CheckSum = 0 ;
		#endif
		#if USEFLASH
		#if User_DDCTO_FlashSave
		CleanDDCBuff ();
		Flash_Read_Factory_KeySet(FLASH_KEY_DDCA, TRUE, 0, DDCAKEY_SIZE, &DDC1, DDCAKEY_SIZE);
		EDID_CheckSum = DDC1[0x7F];
		#else
#message "VGA DDC Data User Default EDID"
		#endif
		#else
		//NVRam_ReadTbl(DDC_ADC_ADDR, DDC1, 128);
		#endif
		#if 1
		#if User_DDCTO_FlashSave
		if (CheckFlashEDIDData())
		{
			hw_ClrDDC_WP();
			Delay1ms(2);
			EnableReadDDCType = VGA_EDID;
			Init_NVRAM_I2C_SCL_Pin();
			Init_NVRAM_I2C_SDA_Pin();
			for(i = 0; i < 128; i++)
			{
				NVRam_WriteByte(NVRAM_ADDR_EDID + i, DDC1[i]);
			}
			hw_SetDDC_WP();
			Delay1ms(2);
			for (i = 0; i < 128; i++)
			{
				DDC1[i] = 0xFF;
			}
			for(i = 0; i < 128; i++)
			{
				NVRam_ReadByte(NVRAM_ADDR_EDID + i, &dd);
				DDC1[i] = dd;
				ReadCheckSum += DDC1[i];
			}
			if((DDC1[0] == 0x00) && (DDC1[1] == 0xFF) && (DDC1[2] == 0xFF) && (DDC1[3] == 0xFF) && (DDC1[4] == 0xFF)
			        && (DDC1[5] == 0xFF) && (DDC1[6] == 0xFF) && (DDC1[7] == 0x00) && (DDC1[0x7F] == EDID_CheckSum))
			{
				if ((ReadCheckSum) == 0 && ((DDC1[0x14] & 0x80) != 0x80))
				{
					CheckVGADoubleFlag = 1;
				}
			}
			if (CheckVGADoubleFlag)
			{
				Clr_Load_VGAEDID_Flag();
				#if USEFLASH
				UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit );
				#else
				NVRam_WriteWord(nvrMonitorAddr(MonitorFlag), MonitorFlags);
				#endif
			}
		}
		else
		#endif
		{
			hw_ClrDDC_WP();
			Delay1ms(5);
			EnableReadDDCType = VGA_EDID;
			Init_NVRAM_I2C_SCL_Pin();
			Init_NVRAM_I2C_SDA_Pin();
			for(i = 0; i < 128; i++)
			{
				NVRam_WriteByte(NVRAM_ADDR_EDID + i, EDID_vga[i]);
			}
			hw_SetDDC_WP();
			Delay1ms(5);
			for(i = 0; i < 128; i++)
			{
				NVRam_ReadByte(NVRAM_ADDR_EDID + i, &dd);
				DDC1[i] = dd;
				ReadCheckSum += DDC1[i];
				// printMsg("11111111111111");
				//  printData("DDC1[i]====%x",DDC1[i]);
			}
			// printData("ReadCheckSum", ReadCheckSum);
			if((DDC1[0] == 0x00) && (DDC1[1] == 0xFF) && (DDC1[2] == 0xFF) && (DDC1[3] == 0xFF) && (DDC1[4] == 0xFF)
			        && (DDC1[5] == 0xFF) && (DDC1[6] == 0xFF) && (DDC1[7] == 0x00) && (DDC1[0x7F] == EDID_vga[0x7F]))
			{
				if ((ReadCheckSum) == 0 && ((DDC1[0x14] & 0x80) != 0x80))
				{
					CheckVGADoubleFlag = 1;
				}
			}
			//printData("CheckVGADoubleFlag====%d",CheckVGADoubleFlag);
			if (CheckVGADoubleFlag)
			{
				Clr_Load_VGAEDID_Flag();
				#if USEFLASH
				UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit );
				#else
				NVRam_WriteWord(nvrMonitorAddr(MonitorFlag), MonitorFlags);
				#endif
			}
			EnableReadDDCType = I2C_EEPROM;
			Init_NVRAM_I2C_SCL_Pin();
			Init_NVRAM_I2C_SDA_Pin();
		}
		#endif
	}
	#else
	BYTE i;
	mStar_ClrDDC_WP();
	mStar_VGADDC_Base_Address();
	#if USEFLASH
	#if User_DDCTO_FlashSave
	Flash_Read_Factory_KeySet(FLASH_KEY_DDCA, TRUE, 0, DDCAKEY_SIZE, &DDC1, DDCAKEY_SIZE);
#message "VGA DDC Data User Default EDID and Flash EDID"
	#else
#message "VGA DDC Data User Default EDID"
	#endif
	#else
	//NVRam_ReadTbl(DDC_ADC_ADDR, DDC1, 128);
	#endif
	#if User_DDCTO_FlashSave
	if(CheckFlashEDIDData())
	{
		for(i = 0; i < 128; i++)
		{
			msWriteByte(REG_3E4B, i);
			msWriteByte(REG_3E4C, DDC1[i]);
			msWriteByteMask(REG_3E43, BIT5, BIT5);
			while(msReadByte(REG_3E7B) & BIT5);
		}
	}
	else
	#endif
	{
		for(i = 0; i < 128; i++)
		{
			msWriteByte(REG_3E4B, i);
			msWriteByte(REG_3E4C, EDID_vga[i]);
			msWriteByteMask(REG_3E43, BIT5, BIT5);
			while(msReadByte(REG_3E7B) & BIT5);
		}
	}
	mStar_SetDDC_WP();
	#endif
}
#endif
#if ENABLE_DVI
void mStar_DVI_InitDDC(void)
{
	#if DVI_Write_EEPROM
	#if DEBUG_PRINTDATA
	printData("Load_DVIIEDID_FlagAA=%d", Load_DVIIEDID_Flag);
	#endif
	if (Load_DVIIEDID_Flag)
	{
		BYTE i;
		BYTE  ReadCheckSum = 0;
		BYTE  dd = 0;
		BYTE CheckDVIDoubleFlag = 0;
		#if User_DDCTO_FlashSave
		BYTE EDID_CheckSum = 0 ;
		#endif
		#if USEFLASH
		#if User_DDCTO_FlashSave
		CleanDDCBuff ();
		Flash_Read_Factory_KeySet(FLASH_KEY_DDCD, TRUE, 0, DDCDKEY_SIZE, &DDC1, DDCDKEY_SIZE);
		EDID_CheckSum = DDC1[0x7F];
		#else
#message "DVI DDC Data User Default EDID"
		#endif
		#else
		//NVRam_ReadTbl(DDC_ADC_ADDR, DDC1, 128);
		#endif
		#if User_DDCTO_FlashSave
		if (CheckFlashEDIDData())
		{
			#if ENABLE_DEBUG
			printMsg("DVI0000000");
			#endif
			hw_ClrDDC_WP();
			Delay1ms(10);
			EnableReadDDCType = DVI_EDID;
			Init_NVRAM_I2C_SCL_Pin();
			Init_NVRAM_I2C_SDA_Pin();
			for(i = 0; i < 128; i++)
			{
				NVRam_WriteByte(NVRAM_ADDR_EDID + i, DDC1[i]);
			}
			Delay1ms(100);
			hw_SetDDC_WP();
			Delay1ms(2);
			for (i = 0; i < 128; i++)
			{
				DDC1[i] = 0xFF;
			}
			for(i = 0; i < 128; i++)
			{
				NVRam_ReadByte(NVRAM_ADDR_EDID + i, &dd);
				DDC1[i] = dd;
				ReadCheckSum += DDC1[i];
			}
			Delay1ms(100);
			if((DDC1[0] == 0x00) && (DDC1[1] == 0xFF) && (DDC1[2] == 0xFF) && (DDC1[3] == 0xFF) && (DDC1[4] == 0xFF)
			        && (DDC1[5] == 0xFF) && (DDC1[6] == 0xFF) && (DDC1[7] == 0x00) && (DDC1[0x7F] == EDID_CheckSum))
			{
				#if ENABLE_DEBUG
				printMsg("DVI1111111");
				#endif
				if ((ReadCheckSum) == 0 && ((DDC1[0x14] & 0x80) == 0x80))
				{
					CheckDVIDoubleFlag = 1;
				}
			}
			if (CheckDVIDoubleFlag)
			{
				Clr_Load_DVIEDID_Flag();
				#if USEFLASH
				UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit );
				#else
				NVRam_WriteWord(nvrMonitorAddr(MonitorFlag), MonitorFlags);
				#endif
			}
			EnableReadDDCType = I2C_EEPROM;
			Init_NVRAM_I2C_SCL_Pin();
			Init_NVRAM_I2C_SDA_Pin();
		}
		else
		#endif
		{
			#if ENABLE_DEBUG
			printMsg("DVI  EDID  INIT");
			#endif
			hw_ClrDDC_WP();
			Delay1ms(5);
			EnableReadDDCType = DVI_EDID;
			Init_NVRAM_I2C_SCL_Pin();
			Init_NVRAM_I2C_SDA_Pin();
			for(i = 0; i < 128; i++)
			{
				NVRam_WriteByte(NVRAM_ADDR_EDID + i, EDID_dvi[i]);
			}
			Delay1ms(100);
			hw_SetDDC_WP();
			Delay1ms(5);
			for(i = 0; i < 128; i++)
			{
				NVRam_ReadByte(NVRAM_ADDR_EDID + i, &dd);
				DDC1[i] = dd;
				ReadCheckSum += DDC1[i];
			}
			if((DDC1[0] == 0x00) && (DDC1[1] == 0xFF) && (DDC1[2] == 0xFF) && (DDC1[3] == 0xFF) && (DDC1[4] == 0xFF)
			        && (DDC1[5] == 0xFF) && (DDC1[6] == 0xFF) && (DDC1[7] == 0x00) && (DDC1[0x7F] == EDID_dvi[0x7F]))
			{
				if ((ReadCheckSum) == 0 && ((DDC1[0x14] & 0x80) == 0x80))
				{
					CheckDVIDoubleFlag = 1;
				}
			}
			if (CheckDVIDoubleFlag)
			{
				Clr_Load_DVIEDID_Flag();
				#if USEFLASH
				UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit );
				#else
				NVRam_WriteWord(nvrMonitorAddr(MonitorFlag), MonitorFlags);
				#endif
				#if ENABLE_DEBUG
				printMsg("DVI  EDID  PASS");
				#endif
			}
			EnableReadDDCType = I2C_EEPROM;
			Init_NVRAM_I2C_SCL_Pin();
			Init_NVRAM_I2C_SDA_Pin();
		}
	}
	#else
	BYTE i;
	mStar_ClrDDC_WP();
	mStar_DVIDDC_Base_Address();
	#if USEFLASH
	#if User_DDCTO_FlashSave
	Flash_Read_Factory_KeySet(FLASH_KEY_DDCD, TRUE, 0, DDCDKEY_SIZE, &DDC1, DDCDKEY_SIZE);
	#else
#message "DVI DDC Data User Default EDID"
	#endif
	#else
	//NVRam_ReadTbl(DDC_ADC_ADDR, DDC1, 128);
	#endif
	#if User_DDCTO_FlashSave
	if(CheckFlashEDIDData())
	{
		for(i = 0; i < 128; i++)
		{
			msWriteByte(REG_3E4B, i);
			msWriteByte(REG_3E4C, DDC1[i]);
			msWriteByteMask(REG_3E43, BIT5, BIT5);
		}
	}
	else
	#endif
	{
		for(i = 0; i < 128; i++)
		{
			msWriteByte(REG_3E4B, i);
			msWriteByte(REG_3E4C, EDID_dvi[i]);
			msWriteByteMask(REG_3E43, BIT5, BIT5);
		}
	}
	Delay1ms(100);
	mStar_SetDDC_WP();
	#endif
}
#endif
#if ENABLE_HDMI
void mStar_HDMI_InitDDC(void)
{
	#if HDMI_Write_EEPROM
	if (Load_HDMIEDID_Flag)
	{
		WORD i;
		BYTE  ReadCheckSum = 0;
		BYTE  dd = 0;
		BYTE ChecKHDMIDoubleFlag = 0;
		#if User_DDCTO_FlashSave
		BYTE EDID_CheckSum = 0 ;
		#endif
		#if USEFLASH
		#if User_DDCTO_FlashSave
		CleanDDCBuff ();
		#if 0//ENABLE_HDMI2
		Flash_Read_Factory_KeySet(FLASH_KEY_DDCD, TRUE, 0, DDCHKEY_SIZE, &DDC1, DDCHKEY_SIZE);
		#else
		Flash_Read_Factory_KeySet(FLASH_KEY_DDCH, TRUE, 0, DDCHKEY_SIZE, &DDC1, DDCHKEY_SIZE);
		#endif
		EDID_CheckSum = DDC1[0x7F];
#message "HDMI DDC Data User Default EDID and Flash EDID"
		#else
#message "HDMI DDC Data User Default EDID"
		#endif
		#else
		//NVRam_ReadTbl(DDC_ADC_ADDR, DDC1, 128);
		#endif
		#if User_DDCTO_FlashSave
		if (CheckFlashEDIDData())
		{
			hw_ClrDDC_WP();
			Delay1ms(2);
			EnableReadDDCType = HDMI_EDID;
			Init_NVRAM_I2C_SCL_Pin();
			Init_NVRAM_I2C_SDA_Pin();
			for(i = 0; i < 256; i++)
			{
				NVRam_WriteByte(NVRAM_ADDR_EDID + i, DDC1[i]);
			}
			Delay1ms(100);
			hw_SetDDC_WP();
			Delay1ms(2);
			for (i = 0; i < 256; i++)
			{
				DDC1[i] = 0xFF;
			}
			for(i = 0; i < 256; i++)
			{
				NVRam_ReadByte(NVRAM_ADDR_EDID + i, &dd);
				DDC1[i] = dd;
				ReadCheckSum += DDC1[i];
			}
			if((DDC1[0] == 0x00) && (DDC1[1] == 0xFF) && (DDC1[2] == 0xFF) && (DDC1[3] == 0xFF) && (DDC1[4] == 0xFF)
			        && (DDC1[5] == 0xFF) && (DDC1[6] == 0xFF) && (DDC1[7] == 0x00) && (DDC1[0x7F] == EDID_CheckSum))
			{
				if ((ReadCheckSum) == 0 && ((DDC1[0x14] & 0x80) == 0x80))
				{
					ChecKHDMIDoubleFlag = 1;
				}
			}
			if (ChecKHDMIDoubleFlag)
			{
				Clr_Load_HDMIEDID_Flag();
				#if USEFLASH
				UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit );
				#else
				NVRam_WriteWord(nvrMonitorAddr(MonitorFlag), MonitorFlags);
				#endif
			}
			EnableReadDDCType = I2C_EEPROM;
			Init_NVRAM_I2C_SCL_Pin();
			Init_NVRAM_I2C_SDA_Pin();
		}
		else
		#endif
		{
			hw_ClrDDC_WP();
			Delay1ms(2);
			EnableReadDDCType = HDMI_EDID;
			Init_NVRAM_I2C_SCL_Pin();
			Init_NVRAM_I2C_SDA_Pin();
			for(i = 0; i < 256; i++)
			{
				NVRam_WriteByte(NVRAM_ADDR_EDID + i, EDID_hdmi[i]);
			}
			Delay1ms(100);
			hw_SetDDC_WP();
			Delay1ms(2);
			for(i = 0; i < 256; i++)
			{
				NVRam_ReadByte(NVRAM_ADDR_EDID + i, &dd);
				DDC1[i] = dd;
				ReadCheckSum += DDC1[i];
			}
			if((DDC1[0] == 0x00) && (DDC1[1] == 0xFF) && (DDC1[2] == 0xFF) && (DDC1[3] == 0xFF) && (DDC1[4] == 0xFF)
			        && (DDC1[5] == 0xFF) && (DDC1[6] == 0xFF) && (DDC1[7] == 0x00) && (DDC1[0x7F] == EDID_hdmi[0x7F]))
			{
				if ((ReadCheckSum) == 0 && ((DDC1[0x14] & 0x80) == 0x80))
				{
					ChecKHDMIDoubleFlag = 1;
				}
			}
			if (ChecKHDMIDoubleFlag)
			{
				Clr_Load_HDMIEDID_Flag();
				#if USEFLASH
				UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit );
				#else
				NVRam_WriteWord(nvrMonitorAddr(MonitorFlag), MonitorFlags);
				#endif
			}
			EnableReadDDCType = I2C_EEPROM;
			Init_NVRAM_I2C_SCL_Pin();
			Init_NVRAM_I2C_SDA_Pin();
		}
	}
	#endif
	#if CHIP_ID==CHIP_TSUMF
	DDC_Port_Sel();
	#endif
}
#endif

#if ENABLE_HDMI2
void mStar_HDMI2_InitDDC(void)
{
	#if HDMI2_Write_EEPROM
	if (Load_HDMI2EDID_Flag)
	{
		WORD i;
		BYTE  ReadCheckSum = 0;
		BYTE  dd = 0;
		bit ChecKHDMIDoubleFlag = 0;
		#if User_DDCTO_FlashSave
		BYTE EDID_CheckSum = 0 ;
		#endif
		#if USEFLASH
		#if User_DDCTO_FlashSave
		CleanDDCBuff ();
		Flash_Read_Factory_KeySet(FLASH_KEY_DDCH, TRUE, 0, DDCHKEY_SIZE, &DDC1, DDCHKEY_SIZE);
		EDID_CheckSum = DDC1[0x7F];
		#else
#message "HDMI2 DDC Data User Default EDID"
		#endif
		#else
		//NVRam_ReadTbl(DDC_ADC_ADDR, DDC1, 128);
		#endif
		#if User_DDCTO_FlashSave
		if (CheckFlashEDIDData())
		{
			hw_ClrDDC_WP();
			Delay1ms(2);
			EnableReadDDCType = HDMI2_EDID;
			for(i = 0; i < 256; i++)
			{
				NVRam_WriteByte(NVRAM_ADDR_EDID + i, DDC1[i]);
			}
			hw_SetDDC_WP();
			Delay1ms(2);
			for (i = 0; i < 256; i++)
			{
				DDC1[i] = 0xFF;
			}
			for(i = 0; i < 256; i++)
			{
				NVRam_ReadByte(NVRAM_ADDR_EDID + i, &dd);
				DDC1[i] = dd;
				ReadCheckSum += DDC1[i];
			}
			if((DDC1[0] == 0x00) && (DDC1[1] == 0xFF) && (DDC1[2] == 0xFF) && (DDC1[3] == 0xFF) && (DDC1[4] == 0xFF)
			        && (DDC1[5] == 0xFF) && (DDC1[6] == 0xFF) && (DDC1[7] == 0x00) && (DDC1[0x7F] == EDID_CheckSum))
			{
				if ((ReadCheckSum) == 0 && ((DDC1[0x14] & 0x80) == 0x80))
				{
					ChecKHDMIDoubleFlag = 1;
				}
			}
			if (ChecKHDMIDoubleFlag)
			{
				Clr_Load_HDMI2EDID_Flag();
				#if USEFLASH
				UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit );
				#else
				NVRam_WriteWord(nvrMonitorAddr(MonitorFlag), MonitorFlags);
				#endif
			}
			EnableReadDDCType = I2C_EEPROM;
			Init_NVRAM_I2C_SCL_Pin();
			Init_NVRAM_I2C_SDA_Pin();
		}
		else
		#endif
		{
			hw_ClrDDC_WP();
			Delay1ms(2);
			EnableReadDDCType = HDMI2_EDID;
			for(i = 0; i < 256; i++)
			{
				NVRam_WriteByte(NVRAM_ADDR_EDID + i, EDID_hdmi2[i]);
			}
			hw_SetDDC_WP();
			Delay1ms(2);
			for(i = 0; i < 256; i++)
			{
				NVRam_ReadByte(NVRAM_ADDR_EDID + i, &dd);
				DDC1[i] = dd;
				ReadCheckSum += DDC1[i];
			}
			if((DDC1[0] == 0x00) && (DDC1[1] == 0xFF) && (DDC1[2] == 0xFF) && (DDC1[3] == 0xFF) && (DDC1[4] == 0xFF)
			        && (DDC1[5] == 0xFF) && (DDC1[6] == 0xFF) && (DDC1[7] == 0x00) && (DDC1[0x7F] == EDID_hdmi[0x7F]))
			{
				if ((ReadCheckSum) == 0 && ((DDC1[0x14] & 0x80) == 0x80))
				{
					ChecKHDMIDoubleFlag = 1;
				}
			}
			if (ChecKHDMIDoubleFlag)
			{
				Clr_Load_HDMI2EDID_Flag();
				#if USEFLASH
				UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit );
				#else
				NVRam_WriteWord(nvrMonitorAddr(MonitorFlag), MonitorFlags);
				#endif
			}
			EnableReadDDCType = I2C_EEPROM;
			Init_NVRAM_I2C_SCL_Pin();
			Init_NVRAM_I2C_SDA_Pin();
		}
	}
	#endif
}
#endif

#endif

void mStar_InitDDC(void)
{
	#if ENABLE_VGA
	mStar_VGA_InitDDC();
	#endif
	#if ENABLE_DVI
	mStar_DVI_InitDDC();
	#endif
	#if ENABLE_HDMI
	mStar_HDMI_InitDDC();
	#endif
	#if ENABLE_HDMI2
	mStar_HDMI2_InitDDC();
	#endif
}

/*********************************************************************************************************/
#if WriteSN_Functiom_New
extern code BYTE EDID[];
void ReLoadEDIDtoAddSN(void)
{
	BYTE Week = 0x00, Year = 0x1C;
	BYTE SNdata[18];
	WORD i;
	BYTE  ReadCheckSum = 0;
	BYTE  dd = 0;
//2    1  读取EDID    只接受一路
	#if ENABLE_VGA
	Flash_Read_Factory_KeySet(FLASH_KEY_DDCA, TRUE, 0, DDCAKEY_SIZE,
	                          DDC1, DDCAKEY_SIZE);
	#elif ENABLE_DVI
	Flash_Read_Factory_KeySet(FLASH_KEY_DDCD, TRUE, 0,   DDCDKEY_SIZE, DDC1,
	                          DDCDKEY_SIZE);
	#elif ENABLE_HDMI
	Flash_Read_Factory_KeySet(FLASH_KEY_DDCH, TRUE, 0,   DDCHKEY_SIZE,
	                          DDC1, DDCHKEY_SIZE);
	#endif
//2  2 截取 SN   (必须在6C -7D 间)
//for(i = 0;i<18;i++) SNdata[i] = DDC1[0X5A+i];
	Week = DDC1[0x10];
	Year = DDC1[0x11];
	for(i = 0; i < 14; i++) SNdata[i] = DDC1[0x70 + i];
//2  3 拼合SN
	#if ENABLE_VGA
	#if VGA_Write_EEPROM
	Set_Load_VGAEDID_Flag();
	#endif
	#endif
	#if ENABLE_DVI
	#if !ENABLE_VGA
	Set_Load_DVIEDID_Flag();
	#else
	#if DVI_Write_EEPROM
	ReadCheckSum = 0;
	hw_ClrDDC_WP();
	Delay1ms(2);
	EnableReadDDCType = DVI_EDID;
	NVRam_WriteByte(0x10, Week);
	NVRam_WriteByte(0x11, Year);
	for(i = 0; i < 14; i++)
	{
		NVRam_WriteByte(0x70 + i, SNdata[i]);
	}
	for(i = 0; i < 127; i++)
	{
		NVRam_ReadByte(i, &dd);
		ReadCheckSum += dd;
	}
	NVRam_WriteByte(0x7F, 0x100 - ReadCheckSum);
	hw_SetDDC_WP();
	#else
	for(i = 0; i < 128; i++) DDC1[i] = DVI_EDID[i];
	DDC1[0x10] = Week;
	DDC1[0x11] = Year ;
	for(i = 0; i < 14; i++)  DDC1[0x70 + i] = SNdata[i] ;
	for(i = 0; i < 127; i++) ReadCheckSum += DDC1[i];
	DDC1[0x7F] = 0x100 - ReadCheckSum;
	Flash_Write_Factory_KeySet(FLASH_KEY_DDCD, FALSE,  DDCHKEY_SIZE, DDC1,
	                           DDCDKEY_SIZE);
	#endif
	#endif
	#endif
//3   HDMI 一般存放于24C02
//3(3)  直接操作24C02
	#if ENABLE_HDMI
	#if !ENABLE_VGA&&!ENABLE_DVI
	Set_Load_HDMIEDID_Flag();
	#else
	ReadCheckSum = 0;
	hw_ClrDDC_WP();
	Delay1ms(2);
	EnableReadDDCType = HDMI_EDID;
	NVRam_WriteByte(0x10, Week);
	NVRam_WriteByte(0x11, Year);
	for(i = 0; i < 14; i++)
	{
		NVRam_WriteByte(0x70 + i, SNdata[i]);
	}
	for(i = 0; i < 127; i++)
	{
		NVRam_ReadByte(i, &dd);
		ReadCheckSum += dd;
	}
	NVRam_WriteByte(0x7F, 0x100 - ReadCheckSum);
	hw_SetDDC_WP();
	EnableReadDDCType = I2C_EEPROM;
	#endif
	#endif
	#if ENABLE_HDMI2
	ReadCheckSum = 0;
	hw_ClrDDC_WP();
	Delay1ms(2);
	EnableReadDDCType = HDMI2_EDID;
	NVRam_WriteByte(0x10, Week);
	NVRam_WriteByte(0x11, Year);
	for(i = 0; i < 14; i++)
	{
		NVRam_WriteByte(0x70 + i, SNdata[i]);
	}
	for(i = 0; i < 127; i++)
	{
		NVRam_ReadByte(i, &dd);
		ReadCheckSum += dd;
	}
	NVRam_WriteByte(0x7F, 0x100 - ReadCheckSum);
	hw_SetDDC_WP();
	EnableReadDDCType = I2C_EEPROM;
	#endif
//3 (4)  DP 要回存Flash
	#if ENABLE_DP_INPUT 	&&   DP_WRITE_SN
	ReadCheckSum = 0;
	for(i = 0; i < 256; i++) DDC1[i] = EDID[i];
	DDC1[0x10] = Week;
	DDC1[0x11] = Year ;
	for(i = 0; i < 14; i++)  DDC1[0x70 + i] = SNdata[i] ;
	for(i = 0; i < 127; i++) ReadCheckSum += DDC1[i];
	DDC1[0x7F] = 0x100 - ReadCheckSum;
	Flash_Write_Factory_KeySet(FLASH_KEY_HDCP, FALSE,  DDCHKEY_SIZE, DDC1,
	                           DDCHKEY_SIZE);
	#endif
}
#endif
/*********************************************************************************************************/

#if FreeSyncSwitchEDID
//*************************************************
//Check EDID Support FreeSync or Not
//If No Support return 0  (HDMI1FreeSyncED&&HDMI2FreeSyncED==0)
//If Support return 1 HDMI1FreeSyncED&&HDMI2FreeSyncED is the 0xED Addrs  (HDMI1FreeSyncED&&HDMI2FreeSyncED>=128)
//*************************************************
Bool CheckEDIDSupportFreeSync(BYTE Input)
{
	BYTE temp;
	if(Input == HDMI_EDID)
	{
		for(temp = 0; temp < 125; temp++)
		{
			if((EDID_hdmi[128 + temp] == 0x68) && (EDID_hdmi[128 + temp + 1] == 0x1A) && (EDID_hdmi[128 + temp + 2] == 0x00) && (EDID_hdmi[128 + temp + 3] == 0x00) && (EDID_hdmi[128 + temp + 4] == 0x01) && (EDID_hdmi[128 + temp + 5] == 0x01))
			{
				HDMI1FreeSyncED = temp + 8 + 128;
				return 1;
			}
		}
		if(temp >= 124)
		{
			HDMI1FreeSyncED = 0;
			return 0;
		}
	}
	#if ENABLE_HDMI2
	if(Input == HDMI2_EDID)
	{
		for(temp = 0; temp < 125; temp++)
		{
			if((EDID_hdmi2[128 + temp] == 0x68) && (EDID_hdmi2[128 + temp + 1] == 0x1A) && (EDID_hdmi2[128 + temp + 2] == 0x00) && (EDID_hdmi2[128 + temp + 3] == 0x00) && (EDID_hdmi2[128 + temp + 4] == 0x01) && (EDID_hdmi2[128 + temp + 5] == 0x01))
			{
				HDMI2FreeSyncED = temp + 8 + 128;
				return 1;
			}
		}
		if(temp >= 124)
		{
			HDMI2FreeSyncED = 0;
			return 0;
		}
	}
	#endif
	return 0;
}
//*************************************************
//通过默认EDID直接返回一个开或关对应的CheckSum
//如果默认EDID不支持FreeSync 返回 NULL
//*************************************************
BYTE GetEDIDCheckSum(BYTE Input, BYTE OnOff)
{
	if(Input == HDMI_EDID)
	{
		if(CheckEDIDSupportFreeSync(Input))
		{
			if(EDID_hdmi[HDMI1FreeSyncED] == 0xED)
			{
				if(OnOff)
				{
					return (EDID_hdmi[0xFF] + 0xED);
				}
				else
				{
					return (EDID_hdmi[0xFF]);
				}
			}
			else
			{
				if(OnOff)
				{
					return (EDID_hdmi[0xFF]);
				}
				else
				{
					return (EDID_hdmi[0xFF] - 0xED);
				}
			}
		}
		else
		{
			return 0;
		}
	}
	#if ENABLE_HDMI2
	if(Input == HDMI2_EDID)
	{
		if(CheckEDIDSupportFreeSync(Input))
		{
			if(EDID_hdmi2[HDMI2FreeSyncED] == 0xED)
			{
				if(OnOff)
				{
					return (EDID_hdmi2[0xFF] + 0xED);
				}
				else
				{
					return (EDID_hdmi2[0xFF]);
				}
			}
			else
			{
				if(OnOff)
				{
					return (EDID_hdmi2[0xFF]);
				}
				else
				{
					return (EDID_hdmi2[0xFF] - 0xED);
				}
			}
		}
		else
		{
			return 0;
		}
	}
	#endif
	return 0;
}
//*************************************************
//Write Success Return 1
//Write Fail Or Default EDID NoSupport FreeSync Return 0
//*************************************************
Bool  FreeSyncEDIDSwitch(BYTE Input, BYTE OnOff)
{
	//BYTE CheckCount;
	BYTE xdata EDIDCheckSum = GetEDIDCheckSum(Input, OnOff);
	#if ENABLE_DEBUG
	printData("EDIDCheckSum   %d", EDIDCheckSum);
	#endif
	if(EDIDCheckSum)
	{
		if(Input == HDMI_EDID)
		{
			#if ENABLE_DEBUG
			printData("HDMI1FreeSyncED   %d", HDMI1FreeSyncED);
			#endif
			EnableReadDDCType = HDMI_EDID;
			hw_ClrDDC_WP();
			Delay1ms(2);
			if(OnOff)
			{
				//i2c_WriteTBL(0xA0, HDMI1FreeSyncED, ,1);
				//i2c_WriteTBL(0xA0, HDMI1FreeSyncED, &ED_0x00, 1);
				NVRam_WriteByte(HDMI1FreeSyncED, 0x00);
				//i2c_WriteTBL(0xA0, 0xFF, &EDIDCheckSum, 1);
				NVRam_WriteByte(0xFF, EDIDCheckSum);
			}
			else
			{
				#if ENABLE_DEBUG
				printMsg("close freesync");
				#endif
				//i2c_WriteTBL(0xA0, HDMI1FreeSyncED, &ED_0xED, 1);
				NVRam_WriteByte(HDMI1FreeSyncED, 0xED);
				//i2c_WriteTBL(0xA0, 0xFF, &EDIDCheckSum, 1);
				NVRam_WriteByte(0xFF, EDIDCheckSum);
			}
			ForceDelay1ms(30);
			hw_SetDDC_WP();
			EnableReadDDCType = 0xFF;
		}
		#if ENABLE_HDMI2
		if(Input == HDMI2_EDID)
		{
			EnableReadDDCType = Input;
			hw_ClrDDC_WP();
			if(OnOff)
			{
				//i2c_WriteTBL;
				//i2c_WriteTBL(0xA0, HDMI2FreeSyncED, &ED_0x00, 1);
				NVRam_WriteByte(HDMI1FreeSyncED, 0x00);
				//i2c_WriteTBL(0xA0, 0xFF, &EDIDCheckSum, 1);
				NVRam_WriteByte(0xFF, EDIDCheckSum);
			}
			else
			{
				//i2c_WriteTBL(0xA0, HDMI2FreeSyncED, &ED_0xED, 1);
				NVRam_WriteByte(HDMI1FreeSyncED, 0xED);
				//i2c_WriteTBL(0xA0, 0xFF, &EDIDCheckSum, 1);
				NVRam_WriteByte(0xFF, EDIDCheckSum);
			}
			ForceDelay1ms(30);
			hw_SetDDC_WP();
			EnableReadDDCType = 0xFF;
		}
		#endif
		Init_NVRAM_I2C_SCL_Pin();
		Init_NVRAM_I2C_SDA_Pin();
	}
	else
	{
		return 0;
	}
//Check Write OK?
	if(Input == HDMI_EDID)
	{
		BYTE xdata FreeSyncED = 0;
		BYTE xdata EDIDCheckSumTemp = 0;
		EnableReadDDCType = Input;
		NVRam_ReadByte(HDMI1FreeSyncED, &FreeSyncED);
		NVRam_ReadByte(0xFF, &EDIDCheckSumTemp);
		ForceDelay1ms(30);
		Init_NVRAM_I2C_SCL_Pin();
		Init_NVRAM_I2C_SDA_Pin();
		EnableReadDDCType = 0xFF;
		#if ENABLE_DEBUG
		printData("EDIDCheckSumTemp   %d", EDIDCheckSumTemp);
		printData("EDIDCheckSum   %d", EDIDCheckSum);
		printData("FreeSyncED   %d", FreeSyncED);
		printData("HDMI1FreeSyncED   %d", HDMI1FreeSyncED);
		printMsg("====================================");
		#endif
		if(OnOff)
		{
			if((EDIDCheckSumTemp == EDIDCheckSum) && (FreeSyncED == 0x00))
				return 1;
			else
				return 0;
		}
		else
		{
			if((EDIDCheckSumTemp == EDIDCheckSum) && (FreeSyncED == 0xED))
				return 1;
			else
				return 0;
		}
	}
	if(Input == HDMI2_EDID)
	{
		BYTE xdata FreeSyncED = 0;
		BYTE xdata EDIDCheckSumTemp = 0;
		EnableReadDDCType = Input;
		NVRam_ReadByte(HDMI2FreeSyncED, &FreeSyncED);
		NVRam_ReadByte(0xFF, &EDIDCheckSumTemp);
		ForceDelay1ms(30);
		Init_NVRAM_I2C_SCL_Pin();
		Init_NVRAM_I2C_SDA_Pin();
		EnableReadDDCType = 0xFF;
		if(OnOff)
		{
			if((EDIDCheckSumTemp == EDIDCheckSum) && (FreeSyncED == 0x00))
				return 1;
			else
				return 0;
		}
		else
		{
			if((EDIDCheckSumTemp == EDIDCheckSum) && (FreeSyncED == 0xED))
				return 1;
			else
				return 0;
		}
	}
	return 0;
}

#endif

#if LoadAllPortSeriealnumberByOneVGAPort

#define SNStrat		0x71//0x4D

#define HDMISNStrat		0x71//0x4D

void ReLoadEDIDtoAddSN(void)
{
	BYTE Week = 0x00, Year = 0x1C;
	BYTE SNdata[18] = {0};
	WORD i;
	BYTE  ReadCheckSum = 0;
	BYTE  dd = 0;
//2    1  读取EDID    只接受一路
	#if ENABLE_VGA
	Flash_Read_Factory_KeySet(FLASH_KEY_DDCA, TRUE, 0, DDCAKEY_SIZE, DDC1, DDCAKEY_SIZE);
	#elif ENABLE_DVI
	Flash_Read_Factory_KeySet(FLASH_KEY_DDCD, TRUE, 0,   DDCDKEY_SIZE, DDC1, DDCDKEY_SIZE);
	#elif ENABLE_HDMI
	Flash_Read_Factory_KeySet(FLASH_KEY_DDCH, TRUE, 0,   DDCHKEY_SIZE, DDC1, DDCHKEY_SIZE);
	#endif
//2  2 截取 SN   (必须在6C -7D 间)
//for(i = 0;i<18;i++) SNdata[i] = DDC1[0X5A+i];
	Week = DDC1[0x10];
	Year = DDC1[0x11];
	for(i = 0; i < 13; i++) SNdata[i] = DDC1[SNStrat + i];
//2  3 拼合SN
	#if ENABLE_VGA
	#if VGA_Write_EEPROM
//Set_LoadVGAEDIDFlag_A();
	#endif
	#endif
//3   HDMI 一般存放于24C02
//3(3)  直接操作24C02
	#if ENABLE_HDMI
	#if 0
	Set_Load_HDMIEDID_Flag();
	#else
	ReadCheckSum = 0;
	hw_ClrDDC_WP();
	Delay1ms(2);
	EnableReadDDCType = HDMI_EDID;
	NVRam_WriteByte(0x10, Week);
	NVRam_WriteByte(0x11, Year);
	for(i = 0; i < 13; i++)
	{
		NVRam_WriteByte(HDMISNStrat + i, SNdata[i]);
	}
	for(i = 0; i < 127; i++)
	{
		NVRam_ReadByte(i, &dd);
		ReadCheckSum += dd;
	}
	NVRam_WriteByte(0x7F, 0x100 - ReadCheckSum);
	hw_SetDDC_WP();
	EnableReadDDCType = I2C_EEPROM;
	#endif
	#endif
}
#endif


#ifdef  UseVGACableReadWriteAllPortsEDID
extern void NVRAM_i2c_WriteTBL(BYTE deviceID, WORD addr, BYTE *buffer, BYTE count);
extern void NVRAM_i2c_ReadTBL(BYTE deviceID, WORD addr, BYTE *buffer, BYTE count);


#endif
