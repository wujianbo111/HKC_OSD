#define _MSHDCP_C_
#include "board.h"
#if ENABLE_HDCP
#include "types.h"
#include "ms_reg.h"
#include "ms_rwreg.h"
#include "Common.h"
#include "misc.h"
#include "global.h"
#include "userpref.h"
#include "debug.h"
#include "msflash.h"
#include "NvRam.h"
// Internal
#include "msHDCP.h"
#if ENABLE_MHL
//extern xdata MHLInfo_S gMHLInfo;
#include "DRVMHL.h"
#endif
#if CHIP_ID >= CHIP_TSUMC
#include "msEread.h"
#endif
#include "GPIO_DEF.h"
#define HDCP_DEBUG 0
#if ENABLE_DEBUG && HDCP_DEBUG
#define HDCP_printData(str, value)   printData(str, value)
#define HDCP_printMsg(str)           printMsg(str)
#else
#define HDCP_printData(str, value)
#define HDCP_printMsg(str)
#endif


#if (!Init_HDCPKey)
#message "Please remember to disable the default HDCP key!"
#else
#message "Please remember to ����KEY!"
#endif
#if (!Init_HDCPKey)
BYTE code BKSV[5] =
{
	0x89, 0x38, 0xae, 0x0d, 0xed
};
//////////////////////////////////////////////////////////////
// HDCP production key
//////////////////////////////////////////////////////////////
BYTE code HDCPkey[] =
{
	0x00, 0xE6, 0xD2, 0xD0, 0xA4, 0x0A, 0xF9, 0xAB, 0x2F, 0x9A, 0x2D, 0x3A,
	0xB5, 0xFF, 0x9D, 0x37, 0xB3, 0x63, 0x23, 0x6E, 0xA3, 0x4E, 0x58, 0xEF,
	0xD2, 0x78, 0x6D, 0x3B, 0xDE, 0xFD, 0x7E, 0x4D, 0xAA, 0xB6, 0x0C, 0x59,
	0x4F, 0x74, 0x3C, 0xF8, 0xDA, 0x65, 0x6E, 0x2F, 0xB4, 0xAB, 0xAD, 0x7F,
	0x89, 0xA1, 0x92, 0x25, 0x1A, 0xCD, 0x50, 0x93, 0x50, 0x00, 0x63, 0x88,
	0x7B, 0xD0, 0xD8, 0x4D, 0x46, 0x95, 0xA8, 0xFC, 0x9B, 0x0D, 0xD1, 0x08,
	0x06, 0xB2, 0x67, 0xBE, 0xA2, 0x90, 0xA7, 0x84, 0x2A, 0x4B, 0x28, 0xC8,
	0xDD, 0x8F, 0xC9, 0x48, 0xA3, 0x0A, 0x7D, 0xCA, 0xDA, 0xBC, 0xCE, 0xFA,
	0x9B, 0x9F, 0x61, 0x90, 0x9E, 0x46, 0x24, 0x2B, 0xA6, 0x7B, 0xB1, 0x6F,
	0xC4, 0x4C, 0x63, 0xAF, 0x44, 0xE1, 0x3A, 0xDD, 0x0D, 0xED, 0xF4, 0x45,
	0x36, 0x47, 0x0B, 0x48, 0x0A, 0xB1, 0xE6, 0xE9, 0xB6, 0xED, 0x78, 0x37,
	0xDC, 0xB0, 0x07, 0x72, 0x83, 0xDC, 0x73, 0x26, 0x31, 0x49, 0x03, 0x52,
	0x7C, 0xE6, 0xC6, 0xE8, 0x3C, 0xD1, 0x62, 0xFE, 0xF0, 0x01, 0x73, 0x23,
	0x90, 0x70, 0xA9, 0x52, 0x8C, 0x75, 0x1C, 0xE5, 0x63, 0x7C, 0xA9, 0x98,
	0x5F, 0xD9, 0x7C, 0x62, 0x25, 0x6C, 0x61, 0x6C, 0xB5, 0xF9, 0xDB, 0xD8,
	0x91, 0x2F, 0x25, 0xF6, 0x3E, 0x37, 0xBE, 0xE2, 0x92, 0x08, 0x07, 0x3C,
	0xE6, 0xC9, 0xE3, 0xB0, 0x4D, 0xF6, 0xAD, 0x54, 0x3C, 0xED, 0x92, 0x5A,
	0x97, 0x93, 0xC0, 0x48, 0xEA, 0x23, 0x6C, 0xDD, 0x9A, 0x00, 0xBA, 0xF1,
	0xB4, 0xE7, 0x7E, 0x84, 0x9A, 0xB5, 0xD5, 0xF4, 0xB0, 0x42, 0x49, 0x5E,
	0x15, 0x5A, 0x43, 0x2D, 0xA9, 0xB0, 0x0A, 0x1C, 0x75, 0xDE, 0x2E, 0x08,
	0xF7, 0xDF, 0x38, 0x03, 0xEB, 0x6A, 0x75, 0xEB, 0xDA, 0x1C, 0xA0, 0xC9,
	0x2F, 0x2A, 0x69, 0x3F, 0x13, 0xFB, 0xA4, 0x23, 0x0A, 0xE5, 0x0A, 0xA5,
	0xEF, 0xCC, 0x8D, 0xB6, 0x5E, 0x6C, 0xB6, 0xE8, 0x84, 0xEF, 0x03, 0xDC,
	0xC5, 0x8A, 0xA3, 0x4B, 0xEF, 0x44, 0x12, 0x7F
};
#endif
// 2005/6/3 0:11AM by Emily
//*********************************************************
// HDCP BKSV key
//*********************************************************
void msInitHDCPProductionKey(void)
{
	BYTE ucValue;
	WORD wCount;
	// prevent complier warning
	#if (CHIP_ID==CHIP_TSUMC)||(CHIP_ID==CHIP_TSUMD)||(CHIP_ID==CHIP_TSUMF)
	Bool bHDCPKeyInEfuse = FALSE;
	WORD wChecksum = 0, wEfuseChecksum = 0;
	msEread_SetComboInitialValue();
	bHDCPKeyInEfuse = msEread_IsHDCPKeyInEfuse();
	if(bHDCPKeyInEfuse)
		HDCP_printMsg("HDCP key in Efuse\n");
	#endif
	#if (CHIP_ID == CHIP_TSUM9 ) // cannot load key from efuse
	Bool bHDCPKeyInEfuse = FALSE;
	WORD wChecksum = 0, wEfuseChecksum = 0;
	#endif
	#if (CHIP_ID==CHIP_TSUMC)||(CHIP_ID==CHIP_TSUMD)||(CHIP_ID==CHIP_TSUM9)||(CHIP_ID==CHIP_TSUMF)
	DVI_RELATED_CLOCK_CTRL_0(0xFFFF, 0xFFFF);
	DVI_RELATED_CLOCK_CTRL_1(0x3FFF, 0x3FFF);
	#else
	DVI_RELATED_CLOCK_CTRL(0, 0x601); //msWrite2ByteMask( REG_290C, 0, 0x601 ); // HDCP related power power down
	#endif
	#if (CHIP_ID==CHIP_TSUMC)||(CHIP_ID==CHIP_TSUMD) ||(CHIP_ID==CHIP_TSUM9)||(CHIP_ID==CHIP_TSUMF) //&& ENABLE_XIU_WRITE_KEY
	//Bksv need to write in 74REG for HDMI/DVI
	HDCP_CPU_WRITE_BKSV_START();
	for( wCount = 0; wCount < 5; wCount++ )
	{
		#if !Init_HDCPKey
		ucValue = BKSV[wCount];
		if(bHDCPKeyInEfuse)
		{
			ucValue = msEread_GetHDCPKeyFromEfuse(wCount);
			wChecksum += ucValue;
			//printData("Efuse = 0x%x\n", ucValue);
		}
		#else
		#if HDCPKEY_IN_Flash
		//Flash_Read_Factory_KeySet( FLASH_KEY_HDCP, TRUE, wCount, 1, &ucValue, 1 );
		#if ENABLE_USE_ISPTOOL_Write_HDCP
		ucValue = FlashReadHDCPByte( IspWriteHDCPkey_Addre + BKSVDataAddr + wCount );	//120105 Modify
		//printData("TmpValue=[0-5]===%x", TmpValue);
		#else
		ucValue = FlashReadByte( HDCPKEYSET_START + BKSVDataAddr + wCount);
		#endif
		#else
		Set_HdcpNVRamFlag();
		NVRam_ReadByte( RM_HDCP_KEY_BASEADDR1 + wCount, &ucValue );
		Clr_HdcpNVRamFlag();
		#endif
		#endif
		HDCP_CPU_WRITE_BKSV(wCount, ucValue); // write data and trigger latch data
		while(HDCP_CPU_WR_BUSY()); // wait ready
	}
	// First 5 bytes is BKSV only use for DP port.
	HDCP_CPU_WRITE_ENABLE(0xC0, 0xC0); //[7]Enable CPU write, [6]Access SRAM
	HDCP_XIU_WRITE_KEY_ENABLE(); //Access Key SRAM through XIU.
	for( wCount = 0; wCount < 5; wCount++ )
	{
		#if !Init_HDCPKey
		ucValue = BKSV[wCount];
		if(bHDCPKeyInEfuse)
		{
			ucValue = msEread_GetHDCPKeyFromEfuse(wCount);
		}
		#else
		#if HDCPKEY_IN_Flash
		//Flash_Read_Factory_KeySet( FLASH_KEY_HDCP, TRUE, wCount, 1, &ucValue, 1 );
		#if ENABLE_USE_ISPTOOL_Write_HDCP
		ucValue = FlashReadHDCPByte( IspWriteHDCPkey_Addre + BKSVDataAddr + wCount );	//120105 Modify
		//printData("TmpValue=[0-5]===%x", TmpValue);
		#else
		ucValue = FlashReadByte( HDCPKEYSET_START + BKSVDataAddr + wCount);
		#endif
		#else
		Set_HdcpNVRamFlag();
		NVRam_ReadByte( RM_HDCP_KEY_BASEADDR1 + wCount, &ucValue );
		Clr_HdcpNVRamFlag();
		#endif
		#endif
		HDCP_XIU_WRITE_KEY(ucValue);
		#if ((CHIP_ID==CHIP_TSUMC)||(CHIP_ID==CHIP_TSUMD) ||(CHIP_ID==CHIP_TSUM9)||(CHIP_ID==CHIP_TSUMF)) //130912 nick add follow trunk//&& ENABLE_XIU_WRITE_KEY
		msWriteByte( REG_06A0 + wCount, ucValue );           //Off-Line Key
		msWriteByte( REG_07A0 + wCount, ucValue );           //Off-LineKey
		#endif
	}
	for( wCount = 0; wCount < 284; wCount++ )
	{
		#if !Init_HDCPKey
		ucValue = HDCPkey[wCount] ;
		if(bHDCPKeyInEfuse)
		{
			ucValue = msEread_GetHDCPKeyFromEfuse(wCount + 5);
			wChecksum += ucValue;
			//printData("Efuse = 0x%x\n", ucValue);
		}
		#else
		#if HDCPKEY_IN_Flash
		#if ENABLE_USE_ISPTOOL_Write_HDCP
		ucValue = FlashReadHDCPByte( IspWriteHDCPkey_Addre + HDCPKetAddr + wCount );	//120105 Modify
		//printData("TmpValue=[284]===%x", TmpValue);
		#else
		ucValue = FlashReadByte( HDCPKEYSET_START + HDCPKetAddr + wCount);
		#endif
		//Flash_Read_Factory_KeySet( FLASH_KEY_HDCP, TRUE, wCount + HDCPKetAddr, 1, &ucValue, 1 );
		#else
		Set_HdcpNVRamFlag();
		NVRam_ReadByte( RM_HDCP_KEY_BASEADDR2 + wCount, &ucValue );
		Clr_HdcpNVRamFlag();
		#endif
		#endif
		HDCP_XIU_WRITE_KEY(ucValue); // write data and trigger latch data
	}
	HDCP_XIU_WRITE_KEY_DISABLE();
	if(bHDCPKeyInEfuse)
	{
		if(msEread_CompareHDCPChecksumInEfuse(wChecksum))
			HDCP_printMsg("Efuse Checksum match ^^ \n");
		else
		{
			HDCP_printMsg("Efuse Checksum wrong @@ \n");
			HDCP_printData("Calculate checksum = 0x%x\n", wChecksum);
			HDCP_printData("Efuse checksum = 0x%x\n", wEfuseChecksum);
		}
	}
	#else   //2 u
	HDCP_CPU_WRITE_BKSV_START();
	for( wCount = 0; wCount < 5; wCount++ )
	{
		#if !Init_HDCPKey
		ucValue = BKSV[wCount];
		#else
		#if HDCPKEY_IN_Flash
		#if ENABLE_USE_ISPTOOL_Write_HDCP
		ucValue = FlashReadHDCPByte( IspWriteHDCPkey_Addre + BKSVDataAddr + wCount );	//120105 Modify
		//printData("TmpValue=[0-5]===%x", TmpValue);
		#else
		ucValue = FlashReadByte( HDCPKEYSET_START + BKSVDataAddr + wCount);
		#endif
		#else
		Set_HdcpNVRamFlag();
		NVRam_ReadByte( RM_HDCP_KEY_BASEADDR1 + wCount, &ucValue );
		Clr_HdcpNVRamFlag();
		#endif
		#endif
		HDCP_CPU_WRITE_BKSV(wCount, ucValue); // write data and trigger latch data
		while(HDCP_CPU_WR_BUSY()); // wait ready
	}
	HDCP_CPU_WRITE_ENABLE(0xC0, 0xC0); //[15]: CPU write enable, [14]: 0: 74 RAM, 1 :HDCP RAM
	HDCP_CPU_RW_ADDRESS(0); //address
	HDCP_LOAD_ADDR_GEN_PULSE(); // trigger latch address
	for( wCount = 0; wCount < 284; wCount++ )
	{
		#if !Init_HDCPKey
		ucValue = HDCPkey[wCount] ;
		#else
		#if HDCPKEY_IN_Flash
		#if ENABLE_USE_ISPTOOL_Write_HDCP
		ucValue = FlashReadHDCPByte( IspWriteHDCPkey_Addre + HDCPKetAddr + wCount );	//120105 Modify
		//printData("TmpValue=[284]===%x", TmpValue);
		#else
		ucValue = FlashReadByte( HDCPKEYSET_START + HDCPKetAddr + wCount);
		#endif
		#else
		Set_HdcpNVRamFlag();
		NVRam_ReadByte( RM_HDCP_KEY_BASEADDR2 + wCount, &ucValue );
		Clr_HdcpNVRamFlag();
		#endif
		#endif
		HDCP_CPU_WRITE_DATA(ucValue); // write data and trigger latch data
		while(HDCP_CPU_WR_BUSY()); // wait ready
	}
	#endif //CHIP_ID==CHIP_TSUMC && ENABLE_XIU_WRITE_KEY
//========================//
	//Bcaps=0x00 or 0x80
	#if ENABLE_HDMI
	HDCP_CPU_WRITE_BCAPS(0x80); // HDCP data
	#else
	HDCP_CPU_WRITE_BCAPS(0); // HDCP data
	#endif
	HDCP_CPU_WRITE_ENABLE(0, 0xC0); //msWriteByteMask( REG_28F3, 0x00, 0xC0 ); //[15]: CPU write disable, [14]: 0: 74 RAM, 1 :HDCP RAM
	HDCP_MISC_SETTING(0x721); //msWrite2Byte( REG_28C0, 0x0721 ); // [10:8]: 3'b111 determine Encrp_En during Vblank in DVI mode; [5]:HDCP enable; [0]: EESS mode deglitch Vsync mode
	HDCP_ENABLE_DDC(); // [10]: HDCP enable DDC
	#if CHIP_ID==CHIP_TSUMU && (ENABLE_DUAL_LINK||(HDMI_PORT&(TMDS_PORT_B|TMDS_PORT_C)))
	//Bksv
	for(wCount = 0; wCount < 5; wCount++)
	{
		#if !Init_HDCPKey
		ucValue = BKSV[wCount];
		#else
		#if HDCPKEY_IN_Flash
		#if ENABLE_USE_ISPTOOL_Write_HDCP
		ucValue = FlashReadHDCPByte( IspWriteHDCPkey_Addre + BKSVDataAddr + wCount );	//120105 Modify
		//printData("TmpValue=[0-5]===%x", TmpValue);
		#else
		ucValue = FlashReadByte( HDCPKEYSET_START + BKSVDataAddr + wCount);
		#endif
		//Flash_Read_Factory_KeySet( FLASH_KEY_HDCP, TRUE, wCount, 1, &ucValue, 1 );
		#else
		Set_HdcpNVRamFlag();
		NVRam_ReadByte( RM_HDCP_KEY_BASEADDR1 + wCount, &ucValue );
		Clr_HdcpNVRamFlag();
		#endif
		#endif
		//msWriteByte(REG_3BFA+wCount, ucValue);
		//while( msReadByte( REG_3BF2 ) & 0x80 );     // wait ready
		HDCP1_CPU_WRITE_BKSV(wCount, ucValue);
		while(HDCP1_CPU_WR_BUSY()); // wait ready
	}
	//Bcaps=0x00 or 0x80
	#if ENABLE_HDMI
	HDCP1_CPU_WRITE_BCAPS(0x80); //msWriteByte( REG_3BFF, 0x80 );  //HDCP data
	#else
	HDCP1_CPU_WRITE_BCAPS(0); //msWriteByte( REG_3BFF, 0x00 );  //HDCP data
	#endif // #if ENABLE_HDMI
	HDCP1_MISC_SETTING(0x721); //msWrite2Byte( REG_3BC0, 0x0721 ); // [10:8]: 3'b111 determine Encrp_En during Vblank in DVI mode; [5]:HDCP enable; [0]: EESS mode deglitch Vsync mode
	HDCP1_ENABLE_DDC(); //msWriteByteMask( REG_3BEF, 0x04, 0x04 ); // [10]: HDCP enable DDC
	#endif //
	HDCP_FORCE_ACK();
}
///////////////////////////////////////////////////////////////////////////////
// <Function>: msPullLowHPD1
//
// <Description>: Pull low DVI Hot-Plug-Detection pin
//
// <Parameter>: None
//
//
///////////////////////////////////////////////////////////////////////////////
#if 0
void msPullLowHPD1( void )
{
	if(CURRENT_INPUT_IS_HDMI())//( SrcInputType == Input_HDMI )	//130529 Modify
	{
		if(CURRENT_INPUT_IS_HDMI0())
		{
			if(!IS_MHL_PORT0_CABLE_CONNECT())
				hw_Clr_HdcpHpd();
		}
		if(CURRENT_INPUT_IS_HDMI1())
		{
			if(!IS_MHL_PORT1_CABLE_CONNECT())
				hw_Clr_HdcpHpd2();
		}
		if(CURRENT_INPUT_IS_HDMI2())
		{
			if(!IS_MHL_PORT2_CABLE_CONNECT())
				hw_Clr_HdcpHpd3();
		}
	}
}
#endif
void msPullLowHPD1( void )  // 2017/02/22
{
	if(CURRENT_INPUT_IS_TMDS())
	{
		if(CURRENT_INPUT_IS_HDMI0())//||CURRENT_INPUT_IS_DVI0())
		{
			if(!IS_MHL_PORT0_CABLE_CONNECT())
			{
				hw_Clr_HdcpHpd();
				#if ENABLE_DEBUG
				printMsg("aaaaaaaaaaaaaaaaaaaaaaa");
				#endif
			}
		}
		if(CURRENT_INPUT_IS_HDMI1())//||CURRENT_INPUT_IS_DVI1())
		{
			if(!IS_MHL_PORT1_CABLE_CONNECT())
			{
				hw_Clr_HdcpHpd2();
				#if ENABLE_DEBUG
				printMsg("bbbbbbbbbbbbbbbbb");
				#endif
			}
		}
		if(CURRENT_INPUT_IS_HDMI2())//||CURRENT_INPUT_IS_DVI2())
		{
			if(!IS_MHL_PORT2_CABLE_CONNECT())
				hw_Clr_HdcpHpd3();
			#if ENABLE_DEBUG
			printMsg("cccccccccccccccccc");
			#endif
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
// <Function>: msPullLowHPD1
//
// <Description>: Pull high DVI Hot-Plug-Detection pin
//
// <Parameter>: None
//
//
///////////////////////////////////////////////////////////////////////////////
#if 0
void msPullHighHPD1( void )
{
	if(CURRENT_INPUT_IS_HDMI())//( SrcInputType == Input_HDMI )	//130529 Modify
	{
		if(CURRENT_INPUT_IS_HDMI0())
		{
			if(!IS_MHL_PORT0_CABLE_CONNECT())
				hw_Set_HdcpHpd();
		}
		if(CURRENT_INPUT_IS_HDMI1())
		{
			if(!IS_MHL_PORT1_CABLE_CONNECT())
				hw_Set_HdcpHpd2();
		}
		if(CURRENT_INPUT_IS_HDMI2())
		{
			if(!IS_MHL_PORT2_CABLE_CONNECT())
				hw_Set_HdcpHpd3();
		}
	}
}
#endif
void msPullHighHPD1( void )
{
	if(CURRENT_INPUT_IS_TMDS())
	{
		if(CURRENT_INPUT_IS_HDMI0())//||CURRENT_INPUT_IS_DVI0())
		{
			//if(!IS_MHL_PORT0_CABLE_CONNECT())
			hw_Set_HdcpHpd();
		}
		if(CURRENT_INPUT_IS_HDMI1())//||CURRENT_INPUT_IS_DVI1())
		{
			//if(!IS_MHL_PORT1_CABLE_CONNECT())
			hw_Set_HdcpHpd2();
		}
		if(CURRENT_INPUT_IS_HDMI2())//||CURRENT_INPUT_IS_DVI2())
		{
			//if(!IS_MHL_PORT2_CABLE_CONNECT())
			hw_Set_HdcpHpd3();
		}
	}
}
#if 0
void msTMDSClkOn( Bool u8On)
{
	#if (MainBoardType == MainBoard_5115_M0E || MainBoardType == MainBoard_7115_M0A)
	if(CURRENT_INPUT_IS_DVI0())
	{
		msWriteByteMask( REG_PM_B2, u8On ? 0 : BIT0, BIT0 ); //seurat DVI RCK port A power down
		#if ENABLE_DUAL_LINK
		msWriteByteMask( REG_03B3, u8On ? 0 : BIT0, BIT0 ); //seurat DVI RCK port C power down
		#endif
	}
	else if(CURRENT_INPUT_IS_HDMI0())
	{
		#if ENABLE_MHL&&(CHIP_ID == CHIP_TSUM2)
		mhal_mhl_RxRtermControl((u8On) ? (RX_HDMI_RTERM) : (RX_RTERM_OFF));
		#else
		msWriteByteMask( REG_PM_B2, u8On ? 0 : BIT1, BIT1 ); //seurat DVI RCK port B power down
		#endif
	}
	#else
	if(CURRENT_INPUT_IS_HDMI0() || CURRENT_INPUT_IS_DVI0())
		DVI_A_RCK_CTRL(u8On);
	else if(CURRENT_INPUT_IS_HDMI1() || CURRENT_INPUT_IS_DVI1())
		DVI_B_RCK_CTRL(u8On);
	else if(CURRENT_INPUT_IS_HDMI2() || CURRENT_INPUT_IS_DVI2())
		DVI_C_RCK_CTRL(u8On);
	#endif
}
#endif

void msDVIClkOn( Bool u8On )
{
	#if DVI_PORT==TMDS_PORT_A
	#if ENABLE_MHL&&(CHIP_ID == CHIP_TSUM2)
	//mapi_mhl_SetClk(u8On);
	mhal_mhl_RxRtermControl((u8On) ? (RX_HDMI_RTERM) : (RX_RTERM_OFF));
	#else
	DVI_A_RCK_CTRL(u8On); //msWriteByteMask( REG_PM_B2, (u8On ? 0 : BIT0), BIT0 ); // DVI RCK port A power down
	#endif
	#elif DVI_PORT==TMDS_PORT_B
	DVI_B_RCK_CTRL(u8On); //msWriteByteMask( REG_PM_B2, (u8On ? 0 : BIT1), BIT1 ); // DVI RCK port B power down
	#else
	DVI_C_RCK_CTRL(u8On); //msWriteByteMask( REG_PM_B3, (u8On ? 0 : BIT0), BIT0 ); // DVI RCK port C power down
	#endif
}

#if ENABLE_HDMI
void msHDMIClkOn( Bool u8On)
{
	#if 0//(MainBoardType==MainBoard_JRY_WQ570_EV1)
	if(CURRENT_INPUT_IS_DVI0())
	{
		DVI_A_RCK_CTRL(u8On);
		#if ENABLE_DUAL_LINK
		DVI_C_RCK_CTRL(u8On);
		#endif
	}
	else if(CURRENT_INPUT_IS_HDMI0())
	{
		DVI_B_RCK_CTRL(u8On);
	}
	#else
	if(Input_TMDS_Nums >= 2)
	{
		if(CURRENT_INPUT_IS_HDMI0() || CURRENT_INPUT_IS_DVI0())
			DVI_A_RCK_CTRL(u8On);
		else if(CURRENT_INPUT_IS_HDMI1() || CURRENT_INPUT_IS_DVI1())
			DVI_B_RCK_CTRL(u8On);
		else if(CURRENT_INPUT_IS_HDMI2() || CURRENT_INPUT_IS_DVI2())
			DVI_C_RCK_CTRL(u8On);
	}
	else
	{
		#if HDMI_PORT==TMDS_PORT_C//TMDS_PORT_C
		DVI_C_RCK_CTRL(u8On);
		#elif HDMI_PORT==TMDS_PORT_B //TMDS_PORT_B
		DVI_B_RCK_CTRL(u8On);
		#else //TMDS_PORT_A
		DVI_A_RCK_CTRL(u8On);
		#endif
	}
	#endif
}
#endif

///////////////////////////////////////////////////////////////////////////////
// <Function>: msPullLowHPD2
//
// <Description>: Cut off DVI receiver clock current
//
// <Parameter>: None
//
///////////////////////////////////////////////////////////////////////////////
void msPullLowHPD2( void )
{
	HDCP_PORT_DISABLE(); //disable HDCP port
	HDCP_CLEAR_STATUS(); //Clear HDCP status
	if(CURRENT_INPUT_IS_DVI())
		msDVIClkOn(FALSE);
	#if ENABLE_HDMI
	else
	#if HDMI_PRETEST
		msHDMIClkOn(TRUE);
	#else
		msHDMIClkOn(FALSE);
	#endif
	#endif
}
///////////////////////////////////////////////////////////////////////////////
// <Function>: msPullHighHPD2
//
// <Description>: Connect DVI receiver clock current
//
// <Parameter>: None
//
///////////////////////////////////////////////////////////////////////////////
void msPullHighHPD2( void )
{
	#if 0
	msTMDSClkOn(TRUE);
	#endif
	if(CURRENT_INPUT_IS_DVI())
		msDVIClkOn(TRUE);
	#if ENABLE_HDMI
	else
		msHDMIClkOn(TRUE);
	#endif
	HDCP_PORT_ENABLE(); //msWriteByteMask(SC0_BD,0,BIT7); //enable HDCP port
}
void mstar_HDCPReset(void)
{
	DVI_RESET(TRUE);
	HDCP_RESET(TRUE);
	ForceDelay1ms(2);
	HDCP_RESET(FALSE);
	DVI_RESET(FALSE);
}

void msDisableHDCP( void )
{
	msPullLowHPD1();
	ForceDelay1ms( 100 );//2 jemery 180930 follow demo
	msPullLowHPD2();
	mstar_HDCPReset();
}
void msEnableHDCP( void )
{
	if( !PowerSavingFlag )
	{
		msDisableHDCP();
		ForceDelay1ms(300);
	}
	msPullHighHPD2();
	ForceDelay1ms( 100 );//2 jemery 180930 follow demo
	msPullHighHPD1();
}


#if ENABLE_DUAL_LINK
WORD Mode_GetStandardModePxlRate()
{
	return (WORD)((DWORD)StandardModeHTotal * HFreq( SrcHPeriod ) / 10000);
}

Bool IsSrcUseDualLinkDviPort(void)
{
	if(SrcInputType == Input_Digital) // DVI Dual-link - PortC+A
		return 1;
	return 0;
}

// DVI dual-link configuration
void msDVIDualLinkMode(Bool bEnable)
{
	msWriteBit(REG_1E3E, bEnable, _BIT7);
	if(bEnable) // dual-link, portC+A
	{
		msWriteByteMask( REG_2800, 0, BIT7 | BIT6 ); // [7]: ABSWAP, [6]: ignore_dual_en
		msWriteByteMask( REG_2801, 0, BIT6 | BIT5 ); // [6]: DVI_linkb_en, [5]: DVI_dual_manual_en
		msWriteByteMask( REG_2860, BIT5 | BIT4, BIT6 | BIT5 | BIT4 ); // [6]: DVI_dual_b_ov_en, [5]: DVI_dual_c_ov_en, [4]: DVI_dual_ov_en
		//msWriteByteMask(REG_2E02, 0x10, 0xF0); // Set scaler IPMUX to dual-link
		//msWriteBit(SC23_06, TRUE, _BIT2); // dual-in enable
		//msWriteBit(SC23_07, TRUE, _BIT2); // odd/even pixel swap
		msWriteByteMask(SC0_A6, _BIT1, _BIT1);
	}
	else // single-link, port C
	{
		msWriteByteMask( REG_2800, BIT6, BIT7 | BIT6 ); // [7]: ABSWAP, [6]: ignore_dual_en
		msWriteByteMask( REG_2801, BIT6 | BIT5, BIT6 | BIT5 ); // [6]: DVI_linkb_en, [5]: DVI_dual_manual_en
		//msWriteByteMask( REG_2860, BIT5|BIT4, BIT6|BIT5|BIT4 ); // [6]: DVI_dual_b_ov_en, [5]: DVI_dual_c_ov_en, [4]: DVI_dual_ov_en
		//msWriteByteMask(REG_2E02, 0xA0, 0xF0); // Set scaler IPMUX to single-link
		//msWriteBit(SC23_06, FALSE, _BIT2); // dual-in disable
		//msWriteBit(SC23_07, FALSE, _BIT2);
		msWriteByteMask(SC0_A6, 0, _BIT1);
	}
}

Bool msGetDVIDualLinkStatus(void)
{
	#if DL_PXL_RAT_DET
	WORD rate;
	rate = Mode_GetStandardModePxlRate();
	//printData("DVI Pixel Rate : %d", rate);
	if( rate > 165 )
		return TRUE;
	else
		return FALSE;
	#else
	BYTE ucDualLinkStatus = 0, ucStableCnt, ucIntCount = 0;
	WORD wHDE, wVDE;
	for(ucStableCnt = 0; ucStableCnt < 5; ucStableCnt++)
	{
		msWriteByte(REG_29E3, 0x44); // clear DE changed IRQ status
		msWriteByte(REG_29E3, 0);
		ForceDelay1ms(10);
		ucDualLinkStatus |= msReadByte(REG_29E0); // Check DE changed IRQ status
		if((ucDualLinkStatus & _BIT6)) // Check primary-link DE changed status
			ucIntCount++;
	}
	if(ucIntCount != 0) // If primary-link DE changed, that means signal is coupled from another port.
	{
		//printMsg("\r\n DVI_SINGLE_LINK()");
		return FALSE;
	}
	else // primary-link DE is unchanged, check whether DE is stable or unstable
	{
		for(ucStableCnt = 0; ucStableCnt < 20; ucStableCnt++)
		{
			ForceDelay1ms(20);
			ucDualLinkStatus = msReadByte(REG_3B62); // DVI1 DE is stable
			if((ucDualLinkStatus & _BIT6) != 0)
				break;
		}
		if((ucDualLinkStatus & _BIT6) != 0)
		{
			wHDE = msRead2Byte(SC0_84) - msRead2Byte(SC0_80);
			wVDE = msRead2Byte(SC0_82) - msRead2Byte(SC0_7E);
			// software patch for MSPG4233 dual-link port
			//printMsg("\r\n HDE-VDE = %d", (signed)wHDE - wVDE);
			if(wHDE <= wVDE)
			{
				//printMsg("\r\n DVI_DUAL_LINK");
				return TRUE;
			}
			else
			{
				//printMsg("\r\n II -DVI_SINGLE_LINK()");
				return FALSE; // single-link
			}
		}
		else
		{
			//printMsg("\r\n II -DVI_SINGLE_LINK()");
			return FALSE;
		}
	}
	#endif
}
#endif // #if ENABLE_DUAL_LINK







#endif
