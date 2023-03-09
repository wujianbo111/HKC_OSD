#include "types.h"
#include "board.h"
#include "global.h"
#include "Menudef.h"
#include "menufunc.h"
#include "adjust.h"
#include <math.h>
#include "ms_reg.h"
#include "msOSD.h"
#include "msosdfunction.h"
#include "autofunc.h"
#include "drvadc.h"
#include "ms_rwreg.h"
#include "Debug.h"
#include "misc.h"
#include "mstar.h"
#include "power.h"
#include "keypaddef.h"
#include "ddc2bi.h"
#include "userpref.h"

#include "msACE.h"
#include "gamma.h"
#include "msflash.h"
#include "mcu.h"
#include "ddc.h"
#include "nvram.h"
#include "GPIO_DEF.h"
#ifdef TSUMXXT//#if( ChipID == ChipTSUMT )		//110311 Modify
#include "msADC.h"
#endif
#if PanelminiLVDS || PANEL_VCOM_ADJUST	//110229 Modify
#include "msMiniLVDSI2c.h"
#endif
#include "drvgpio.h"
#include "PropFont.h"
////////////////////////////////////////////////////
//#include "drvDDC2Bi.h" // the function changes to hal
///////////////////////////////////////////////////
#include "MsDLC.h"	//120413 Modify
#include "drvOSD.h"


#if ENABLE_DeltaE
#include "msAutoGamma_Setting.h"
extern void drvGammaOnOff(BYTE u8Switch, BYTE u8Window);
#endif
#define CTEMP_6500K CTEMP_Warm1
#define CTEMP_9300K CTEMP_Cool1
#define CTEMP_7500K CTEMP_Normal

#define UserPrefRedColor6500K UserPrefRedColorWarm1
#define UserPrefGreenColor6500K UserPrefGreenColorWarm1
#define UserPrefBlueColor6500K UserPrefBlueColorWarm1

#define UserPrefRedColor9300K UserPrefRedColorCool1
#define UserPrefGreenColor9300K UserPrefGreenColorCool1
#define UserPrefBlueColor9300K UserPrefBlueColorCool1

#define UserPrefRedColor7500K UserPrefRedColorNormal
#define UserPrefGreenColor7500K UserPrefGreenColorNormal
#define UserPrefBlueColor7500K UserPrefBlueColorNormal

extern Bool SetColor(void);
extern Bool SetColorTemp();
extern Bool CheckFactorySettingOutOfRange(void);
void CheckModeSettingRange();
void Init_FactorySetting(void);
#if ENABLE_HDMI
extern void SetColorBoostWin(BYTE mode);
#else
extern void SetColorBoostWindow(BYTE mode);
#endif
#if 0
extern Bool AdjustSuperResolution(void);
#endif
extern Bool xdata bFlashWriteFactory;

extern WORD CRC16(BYTE nData, WORD nCRC);

extern void DrawOsdMenu(void);

#define SIO_ID1     SIORxBuffer[0]
#define SIO_TYPE1   SIORxBuffer[1]
#define SIO_TYPE2   SIORxBuffer[2]
#define SIO_CMD1    SIORxBuffer[3]
#define SIO_CMD2    SIORxBuffer[4]
#define SIO_DATA1   SIORxBuffer[5]
#define SIO_DATA2   SIORxBuffer[6]
#define SIO_DATA3       SIORxBuffer[7]
#define SIOData10   (SIO_DATA1-0x30)*256
#define SIOData11   ((SIO_DATA1-0x41)+10)*256
#define SIOData20   (SIO_DATA2-0x30)*16
#define SIOData21   ((SIO_DATA2-0x41)+10)*16
#define SIOData30   (SIO_DATA3-0x30)
#define SIOData31   (SIO_DATA3-0x41)+10
BYTE AlignControl(void);
#define ASSETSTARTADDR			0x600
#define ASSETLENGTH				64

#if JRY_Color_Tool_Functing

#define EDID_VGA			      0
#define EDID_DVI		                   1
#define EDID_HDMI			      2
#define EDID_DP			            3

#if JRY_FDDCCI_WriteEDID || WriteSN_Functiom_New
WORD idata edid_cont = 0;
BYTE idata edid_pointer = 0;
#endif

#if (ENABLE_HDCP&&JRY_FDDCCI_WriteHDCP)
#define HDCP_L128		             	128
#define HDCP_L33		             	33
WORD idata DDCCI_pointer = 0;
BYTE  idata   DDCCI_cont = 0;
BYTE  idata  Hdcpsave_offset = 0 ;
WORD idata Hdcp_pointer = 0;
WORD idata DDCCi_checksun = 0;
WORD  idata Tchecksun = 0;
WORD idata  checksun_verify = 0;
BYTE  idata Flash_HDCPcont = 0;
#endif

Bool JRYColorToolControl (void)
{
	WhileCounte = 5;
	if(ubAutoAlign == 0)
	{
		if((DDCBuffer[3] == 0x35) && (DDCBuffer[4] == 0x1f) && (DDCBuffer[5] == 0)) //enter align mode
		{
			Set_ATEModeFlag();
			Set_FactoryModeFlag();
			Set_BurninModeFlag();
			#if !USEFLASH
			NVRam_WriteByte(nvrMonitorAddr(MonitorFlag), MonitorFlags);
			#else
			UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
			#endif
			MenuPageIndex = RootMenu;
			MenuItemIndex = 0;
			ubAutoAlign = 1;
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x00;
			DDCBuffer[2] = 0x4F;
			return 2;
		}
		else
		{
			return 0;
		}
	}
	if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x13) && (DDCBuffer[5] == 0)) //auto color
	{
		if(AutoColor() != 0)
		{
			DDCBuffer[1] = 0x00;
			DDCBuffer[2] = 0x4F;
		}
		else
		{
			DDCBuffer[1] = 0x03;
			DDCBuffer[2] = 0x58;
		}
		DDCBuffer[0] = 0x84;
		return 2;
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x14) && (DDCBuffer[5] == 0)) //set CT
	{
		SetFactoryColorTempCool1();
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x00;
		DDCBuffer[2] = 0x4F;
		return 2;
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x14) && (DDCBuffer[5] == 1)) //set CT
	{
		SetFactoryColorTempWarm1();
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x00;
		DDCBuffer[2] = 0x4F;
		return 2;
	}
	#if Adj_7500K_Temp
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x14) && (DDCBuffer[5] == 3)) //set CT
	{
		SetFactoryColorTempNormal();
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x00;
		DDCBuffer[2] = 0x4F;
		return 2;
	}
	#endif
	else if((DDCBuffer[3] == 0x32) && (DDCBuffer[4] == 0x15)) //read R gain
	{
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x00;
		if(UserPrefColorTemp == CTEMP_6500K)
			DDCBuffer[2] = UserPrefRedColor6500K; //0x4F;
		else if(UserPrefColorTemp == CTEMP_9300K)
			DDCBuffer[2] = UserPrefRedColor9300K; //0x4F;
		#if Adj_7500K_Temp
		else if(UserPrefColorTemp == CTEMP_7500K)
			DDCBuffer[2] = UserPrefRedColor7500K; //0x4F;
		#endif
		else
			DDCBuffer[2] = UserPrefRedColor; //0x4F;
		return 2;
	}
	else if((DDCBuffer[3] == 0x32) && (DDCBuffer[4] == 0x16)) //read G gain
	{
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x00;
		if(UserPrefColorTemp == CTEMP_6500K)
			DDCBuffer[2] = UserPrefGreenColor6500K; //0x4F;
		else if(UserPrefColorTemp == CTEMP_9300K)
			DDCBuffer[2] = UserPrefGreenColor9300K; //0x4F;
		#if Adj_7500K_Temp
		else if(UserPrefColorTemp == CTEMP_7500K)
			DDCBuffer[2] = UserPrefGreenColor7500K; //0x4F;
		#endif
		else
			DDCBuffer[2] = UserPrefGreenColor; //0x4F;
		return 2;
	}
	else if((DDCBuffer[3] == 0x32) && (DDCBuffer[4] == 0x17)) //read B gain
	{
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x00;
		if(UserPrefColorTemp == CTEMP_6500K)
			DDCBuffer[2] = UserPrefBlueColor6500K; //0x4F;
		else if(UserPrefColorTemp == CTEMP_9300K)
			DDCBuffer[2] = UserPrefBlueColor9300K; //0x4F;
		#if Adj_7500K_Temp
		else if(UserPrefColorTemp == CTEMP_7500K)
			DDCBuffer[2] = UserPrefBlueColor7500K; //0x4F;
		#endif
		else
			DDCBuffer[2] = UserPrefBlueColor; //0x4F;
		return 2;
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x15)) //write R gain
	{
		BYTE ucR_Gain;
		ucR_Gain = DDCBuffer[5];
		if((ucR_Gain >= 0) && (ucR_Gain <= 255))
		{
			if(UserPrefColorTemp == CTEMP_6500K)
			{
				UserPrefRedColor6500K = ucR_Gain;
				#if CT_sRGB_ENABLE
				UserPrefRedColorSRGB = ucR_Gain;
				#endif
			}
			else if(UserPrefColorTemp == CTEMP_9300K)
				UserPrefRedColor9300K = ucR_Gain;
			#if Adj_7500K_Temp
			else if(UserPrefColorTemp == CTEMP_7500K)
				UserPrefRedColor7500K = ucR_Gain;
			#endif
			else if(UserPrefColorTemp == CTEMP_USER)
				UserPrefRedColor = ucR_Gain;
			mStar_AdjustRedColor(ucR_Gain, UserPrefContrast);
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x00;
			DDCBuffer[2] = 0x4F;
		}
		else
		{
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x03;
			DDCBuffer[2] = 0x58;
		}
		return 2;
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x16)) //write G gain
	{
		BYTE ucG_Gain;
		ucG_Gain = DDCBuffer[5];
		if((ucG_Gain >= 0) && (ucG_Gain <= 255))
		{
			if(UserPrefColorTemp == CTEMP_6500K)
			{
				UserPrefGreenColor6500K = ucG_Gain;
				#if CT_sRGB_ENABLE
				UserPrefGreenColorSRGB = ucG_Gain;
				#endif
			}
			else if(UserPrefColorTemp == CTEMP_9300K)
				UserPrefGreenColor9300K = ucG_Gain;
			#if Adj_7500K_Temp
			else if(UserPrefColorTemp == CTEMP_7500K)
				UserPrefGreenColor7500K = ucG_Gain;
			#endif
			else if(UserPrefColorTemp == CTEMP_USER)
				UserPrefGreenColor = ucG_Gain;
			mStar_AdjustGreenColor(ucG_Gain, UserPrefContrast);
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x00;
			DDCBuffer[2] = 0x4F;
		}
		else
		{
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x03;
			DDCBuffer[2] = 0x58;
		}
		return 2;
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x17)) //write B gain
	{
		BYTE ucB_Gain;
		ucB_Gain = DDCBuffer[5];
		if((ucB_Gain >= 0) && (ucB_Gain <= 255))
		{
			if(UserPrefColorTemp == CTEMP_6500K)
			{
				UserPrefBlueColor6500K = ucB_Gain;
				#if CT_sRGB_ENABLE
				UserPrefBlueColorSRGB = ucB_Gain;
				#endif
			}
			else if(UserPrefColorTemp == CTEMP_9300K)
				UserPrefBlueColor9300K = ucB_Gain;
			#if Adj_7500K_Temp
			else if(UserPrefColorTemp == CTEMP_7500K)
				UserPrefBlueColor7500K = ucB_Gain;
			#endif
			else if(UserPrefColorTemp == CTEMP_USER)
				UserPrefBlueColor = ucB_Gain;
			mStar_AdjustBlueColor(ucB_Gain, UserPrefContrast);
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x00;
			DDCBuffer[2] = 0x4F;
		}
		else
		{
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x03;
			DDCBuffer[2] = 0x58;
		}
		return 2;
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x18) && (DDCBuffer[5] == 0)) //save CT
	{
		UserPrefColorTemp = CTEMP_9300K;
		#if USEFLASH
		SaveFactorySetting();
		#else
		//NVRam_WriteByte(NVR_MONITOR_ADDR(MonitorFlag), FactorySetting);	//need check tina
		#endif
		#if USEFLASH
		SaveMonitorSetting();
		#else
		NVRam_WriteByte(nvrMonitorAddr(ColorTemp), UserPrefColorTemp);
		#endif
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x00;
		DDCBuffer[2] = 0x4F;
		return 2;
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x18) && (DDCBuffer[5] == 1)) //save CT
	{
		UserPrefColorTemp = CTEMP_6500K;
		#if USEFLASH
		SaveFactorySetting();
		#endif
		#if USEFLASH
		SaveMonitorSetting();
		#else
		NVRam_WriteByte(nvrMonitorAddr(ColorTemp), UserPrefColorTemp);
		#endif
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x00;
		DDCBuffer[2] = 0x4F;
		return 2;
	}
	#if  Adj_7500K_Temp
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x18) && (DDCBuffer[5] == 3)) //save CT
	{
		UserPrefColorTemp = CTEMP_7500K;
		#if USEFLASH
		SaveFactorySetting();
		#endif
		#if USEFLASH
		SaveMonitorSetting();
		#else
		NVRam_WriteByte(nvrMonitorAddr(ColorTemp), UserPrefColorTemp);
		#endif
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x00;
		DDCBuffer[2] = 0x4F;
		return 2;
	}
	#endif
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x19) && (DDCBuffer[5] == 0)) //set brightness and contrast default
	{
		UserPrefBrightness = DefBrightness;
		UserPrefContrast = DefContrast;
		mStar_AdjustBrightness(UserPrefBrightness);
		mStar_AdjustContrast( UserPrefContrast );
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x00;
		DDCBuffer[2] = 0x4F;
		return 2;
	}
	else if((DDCBuffer[3] == 0x32) && (DDCBuffer[4] == 0x1A)) //read adjust brightness
	{
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x00;
		DDCBuffer[2] = UserPrefBrightness;
		return 2;
	}
	else if((DDCBuffer[3] == 0x32) && (DDCBuffer[4] == 0x1B)) //read adjust contrast
	{
		UserPrefContrast = GetScale100Value(UserPrefContrast, MinContrastValue, MaxContrastValue);
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x00;
		DDCBuffer[2] = UserPrefContrast;
		return 2;
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x1A)) //write adjust brightness
	{
		BYTE uctempData;
		uctempData = DDCBuffer[5];
		if((uctempData >= 0) && (uctempData <= 100))
		{
			UserPrefBrightness = uctempData;
			mStar_AdjustBrightness(UserPrefBrightness);
			DDCBuffer[1] = 0x00;
			DDCBuffer[2] = 0x4F;
		}
		else
		{
			DDCBuffer[1] = 0x03;
			DDCBuffer[2] = 0x58;
		}
		DDCBuffer[0] = 0x84;
		return 2;
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x1B)) //write adjust contrast
	{
		BYTE uctempData;
		uctempData = DDCBuffer[5];
		if((uctempData >= 0) && (uctempData <= 100))
		{
			UserPrefContrast = uctempData;
			mStar_AdjustContrast(UserPrefContrast);
			DDCBuffer[1] = 0x00;
			DDCBuffer[2] = 0x4F;
		}
		else
		{
			DDCBuffer[1] = 0x03;
			DDCBuffer[2] = 0x58;
		}
		DDCBuffer[0] = 0x84;
		return 2;
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x1C)) //set default language or select reset language
	{
		UserPrefLanguage = DefLanguage;
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x00;
		DDCBuffer[2] = 0x4F;
		return 2;
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x1D) && (DDCBuffer[5] == 0)) //enter burn mode
	{
		return 0;
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x1D) && (DDCBuffer[5] == 1)) //exit burn mode
	{
		return 0;
	}
	else if((DDCBuffer[3] == 0x35) && (DDCBuffer[4] == 0x1F) && (DDCBuffer[5] == 0)) //enter align mode
	{
		Set_ATEModeFlag();
		Set_FactoryModeFlag();
		Set_BurninModeFlag();
		#if !USEFLASH
		NVRam_WriteByte(nvrMonitorAddr(MonitorFlag), MonitorFlags);
		#else
		UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
		#endif
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x00;
		DDCBuffer[2] = 0x4F;
		return 2;
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x21) && (DDCBuffer[5] == 0)) //factory mode on
	{
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x00;
		DDCBuffer[2] = 0x4F;
		return 2;
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x21) && (DDCBuffer[5] == 1)) //factory mode off
	{
		ubAutoAlign = 0;
		if(FactoryModeFlag)
		{
			#if USEFLASH
			SaveMonitorSetting();
			#else
			NVRam_WriteByte(nvrMonitorAddr(MonitorFlag), MonitorFlags);
			#endif
			MenuPageIndex = RootMenu;
			MenuItemIndex = 0;
			Osd_Hide();
			SaveUserPrefSetting(0);
		}
		else
		{
			SaveUserPrefSetting(0);//SaveUserPref();
		}
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x23) && (DDCBuffer[5] == 0)) //change source vga
	{
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x00;
		DDCBuffer[2] = 0x4F;
		return 2;
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x23) && (DDCBuffer[5] == 1)) //change source dvi
	{
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x00;
		DDCBuffer[2] = 0x4F;
		return 2;
	}
	#if WriteSN_Functiom_New
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x30)) //3DDC长度
	{
		edid_cont = ((DDCBuffer[5]) * 128);
		edid_pointer = 0;
		if((DDCBuffer[5]) < 3)
		{
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x00;
			DDCBuffer[2] = 0x4F;
			return 2;
		}
		else
		{
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x03;
			DDCBuffer[2] = 0x58;
			return 2;
		}
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x31)) //3DDC接收
	{
		BYTE  j, i = 0;
		j = DDCBuffer[5];
		if (edid_pointer < edid_cont)
		{
			for(i = 0; i < j; i++)
			{
				DDC1[edid_pointer] = DDCBuffer[6 + i];
				edid_pointer++;
			}
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x00;
			DDCBuffer[2] = 0x4F;
			return 2;
		}
		else
		{
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x03;
			DDCBuffer[2] = 0x58;
			return 2;
		}
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x32)) //3ddC 校验
	{
		BYTE  checksun = 0;
		WORD  i;
		if ((edid_cont == 128) || (edid_cont == 256))
		{
			for(i = 0; i < 128; i++)
			{
				checksun += DDC1[i];
			}
			if(checksun == 0)
			{
				DDCBuffer[0] = 0x84;
				DDCBuffer[1] = 0x00;
				DDCBuffer[2] = 0x4F;
				return 2;
			}
		}
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x03;
		DDCBuffer[2] = 0x58;
		return 2;
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x33)) //3ddc保存
	{
		BYTE  checksun;
		BYTE  EDID_TYPE = 0;
		#if USEFLASH
		WORD  i;
		#endif
		//Osd_Show();
		#if ENABLE_VGA
		if(DDCBuffer[5] == 0)
			EDID_TYPE = EDID_VGA;
		#elif ENABLE_DVI
		if (DDCBuffer[5] == 1)
			EDID_TYPE = EDID_DVI;
		#elif ENABLE_HDMI
		if (DDCBuffer[5] == 2)
			EDID_TYPE = EDID_HDMI;
		#endif
		else
		{
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x03;
			DDCBuffer[2] = 0x58;
			return 2;
		}
		#if USEFLASH
		#if ENABLE_VGA
		Flash_Write_Factory_KeySet(FLASH_KEY_DDCA, FALSE,  DDCAKEY_SIZE, DDC1, DDCAKEY_SIZE);
		#elif ENABLE_DVI
		Flash_Write_Factory_KeySet(FLASH_KEY_DDCD, FALSE,  DDCDKEY_SIZE, DDC1, DDCDKEY_SIZE);
		#elif ENABLE_HDMI
		Flash_Write_Factory_KeySet(FLASH_KEY_DDCH, FALSE,  DDCHKEY_SIZE, DDC1, DDCHKEY_SIZE);
		#endif
		checksun = DDC1[0x7F]; //2  只需校验128 字节
		for(i = 0; i < edid_cont; i++) DDC1[i] = 0;
		#if ENABLE_VGA
		Flash_Read_Factory_KeySet(FLASH_KEY_DDCA, TRUE, 0, DDCAKEY_SIZE, DDC1, DDCAKEY_SIZE);
		#elif ENABLE_DVI
		Flash_Read_Factory_KeySet(FLASH_KEY_DDCD, TRUE, 0,   DDCDKEY_SIZE, DDC1, DDCDKEY_SIZE);
		#elif ENABLE_HDMI
		Flash_Read_Factory_KeySet(FLASH_KEY_DDCH, TRUE, 0,   DDCHKEY_SIZE, DDC1, DDCHKEY_SIZE);
		#endif
		#endif
		if(DDC1[(0x7F)] == checksun)
		{
			Set_DDCCIReadLoadEDIDFlag();
			//SaveMonitorSetting();
			WhileCounte = 1;
			Power_TurnOffLed();		//3灭灯指示
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x00;
			DDCBuffer[2] = 0x4F;
			return 2;
		}
		else
		{
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x03;
			DDCBuffer[2] = 0x58;
			return 2;
		}
	}
	#elif  JRY_FDDCCI_WriteEDID
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x30)) //DDC长度
	{
		#if LoadAllPortSeriealnumberByOneVGAPort
		Clr_DDCCOneVGAPortLoadEDIDFlag();
		#endif
		edid_cont = ((DDCBuffer[5]) * 128);
		edid_pointer = 0;
		if((DDCBuffer[5]) < 3)
		{
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x00;
			DDCBuffer[2] = 0x4F;
			return 2;
		}
		else
		{
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x03;
			DDCBuffer[2] = 0x58;
			return 2;
		}
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x31)) //DDC接收
	{
		BYTE  j, i = 0;
		j = DDCBuffer[5];
		if (edid_pointer < edid_cont)
		{
			for(i = 0; i < j; i++)
			{
				DDC1[edid_pointer] = DDCBuffer[6 + i];
				edid_pointer++;
			}
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x00;
			DDCBuffer[2] = 0x4F;
			return 2;
		}
		else
		{
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x03;
			DDCBuffer[2] = 0x58;
			return 2;
		}
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x32)) //2    ddC 校验
	{
		BYTE  checksun = 0;
		WORD  i;
		if ((edid_cont == 128) || (edid_cont == 256))
		{
			for(i = 0; i < edid_cont; i++)
			{
				checksun += DDC1[i];
			}
			if(checksun == 0)
			{
				DDCBuffer[0] = 0x84;
				DDCBuffer[1] = 0x00;
				DDCBuffer[2] = 0x4F;
				return 2;
			}
		}
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x03;
		DDCBuffer[2] = 0x58;
		return 2;
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x33)) //ddc保存
	{
		BYTE  checksun;
		BYTE  EDID_TYPE = 0;
		#if USEFLASH
		WORD  i;
		#endif
		//Osd_Show();
		if(DDCBuffer[5] == 0)
			EDID_TYPE = EDID_VGA;
		else if (DDCBuffer[5] == 1)
			EDID_TYPE = EDID_DVI;
		else if (DDCBuffer[5] == 2)
			EDID_TYPE = EDID_HDMI;
		else if (DDCBuffer[5] == 3)
			EDID_TYPE = EDID_DP;
		#if USEFLASH
		if(EDID_TYPE == EDID_VGA)
		{
			Flash_Write_Factory_KeySet(FLASH_KEY_DDCA, FALSE,  DDCAKEY_SIZE, DDC1, DDCAKEY_SIZE);
		}
		else if (EDID_TYPE == EDID_DVI)
		{
			Flash_Write_Factory_KeySet(FLASH_KEY_DDCD, FALSE,  DDCDKEY_SIZE, DDC1, DDCDKEY_SIZE);
		}
		#if ENABLE_HDMI
		else if (EDID_TYPE == EDID_HDMI)
		{
			Flash_Write_Factory_KeySet(FLASH_KEY_DDCH, FALSE,  DDCHKEY_SIZE, DDC1, DDCHKEY_SIZE);
		}
		#endif
		#if DP_WRITE_SN
		else if (EDID_TYPE == EDID_DP)
		{
			Flash_Write_Factory_KeySet(FLASH_KEY_HDCP, FALSE, DDCHKEY_SIZE, DDC1, DDCHKEY_SIZE);
		}
		#endif
		checksun = DDC1[edid_cont - 1];
		for(i = 0; i++; i < edid_cont)
			DDC1[i] = 0;
		if(EDID_TYPE == EDID_VGA)
		{
			Flash_Read_Factory_KeySet(FLASH_KEY_DDCA, TRUE, 0, DDCAKEY_SIZE, DDC1, DDCAKEY_SIZE);
		}
		else if (EDID_TYPE == EDID_DVI)
		{
			Flash_Read_Factory_KeySet(FLASH_KEY_DDCD, TRUE, 0,   DDCDKEY_SIZE, DDC1, DDCDKEY_SIZE);
		}
		#if ENABLE_HDMI//(!(CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF) )
		else if (EDID_TYPE == EDID_HDMI)
		{
			Flash_Read_Factory_KeySet(FLASH_KEY_DDCH, TRUE, 0,   DDCHKEY_SIZE, DDC1, DDCHKEY_SIZE);
		}
		#endif
		#if  0//DP_WRITE_SN
		else if (EDID_TYPE == EDID_DP)
		{
			Flash_Read_Factory_KeySet(FLASH_KEY_DDCDP, TRUE, 0,   DDCHKEY_SIZE, DDC1, DDCHKEY_SIZE);
		}
		#endif
		#elif 0//else
		if(EDID_TYPE == EDID_VGA)
			NVRam_WriteTbl( RM_MHL_EDID_BASEADDR, DDC1, 128 );
		else if (EDID_TYPE == S_EDID_DVI)
			NVRam_WriteTbl( RM_MHL_EDID_BASEADDR + 128, DDC1, 128 );
		checksun = DDC1[edid_cont - 1];
		DDC1[edid_cont - 1] = 0;
		if(EDID_TYPE == EDID_VGA)
			NVRam_ReadTbl( RM_MHL_EDID_BASEADDR, &DDC1, 128 );
		else if (EDID_TYPE == S_EDID_DVI)
			NVRam_ReadTbl( RM_MHL_EDID_BASEADDR + 128, &DDC1, 128 );
		#endif
		if(DDC1[(edid_cont - 1)] == checksun)
		{
			#if VGA_Write_EEPROM
			if (EDID_TYPE == EDID_VGA)
			{
				Set_Load_VGAEDID_Flag();
			}
			#endif
			#if LoadAllPortSeriealnumberByOneVGAPort
			if (EDID_TYPE == EDID_VGA)
			{
				Set_DDCCOneVGAPortLoadEDIDFlag();
			}
			#endif
			#if DVI_Write_EEPROM
			if (EDID_TYPE == EDID_DVI)
			{
				Set_Load_DVIEDID_Flag();
			}
			#endif
			#if HDMI_Write_EEPROM
			if (EDID_TYPE == EDID_HDMI)
			{
				Set_Load_HDMIEDID_Flag();
				#if HDMI2_Write_EEPROM
				Set_Load_HDMI2EDID_Flag();
				#endif
			}
			#endif
			Set_DDCCIReadLoadEDIDFlag();
			DDCCILoadEDIDCount = 0;
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x00;
			DDCBuffer[2] = 0x4F;
			return 2;
		}
		else
		{
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x03;
			DDCBuffer[2] = 0x58;
			return 2;
		}
	}
	#endif
	#if (ENABLE_HDCP&&JRY_FDDCCI_WriteHDCP)
#message "please check , dont  have this function"
	#elif 0
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x34)) //HDCP 长度
	{
		if((DDCBuffer[5]) == 6)
		{
			//当前批次[6]
			//分三批，第一/二批128BYTE,
			//第三批33YBTE.
			//当为第一批次时清零校验和。
			if(DDCBuffer[6] == 0)
			{
				DDCCi_checksun = 0;
				Flash_HDCPcont = 0;
			}
			// 3个批次，第一次传0，第二次传1，第三次传2
			Hdcpsave_offset = DDCBuffer[6];
			//DDCCI_cont本批大小[7]；
			DDCCI_cont = DDCBuffer[7];
			//Hdcp_pointer本批次的OFFSET 起始位置[8][9]
			Hdcp_pointer = DDCBuffer[8];
			Hdcp_pointer = Hdcp_pointer << 8;
			Hdcp_pointer = Hdcp_pointer | DDCBuffer[9];
			//Tchecksun本批次的Checksun
			Tchecksun = DDCBuffer[10];
			Tchecksun = Tchecksun << 8;
			Tchecksun = Tchecksun | DDCBuffer[11];
			DDCCI_pointer = 0;
			//DDCCI_pointer=0;
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x00;
			DDCBuffer[2] = 0x4F;
			return 2;
		}
		else
		{
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x03;
			DDCBuffer[2] = 0x58;
			return 2;
		}
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x35)) //HDCP  接收
	{
		BYTE  j, i = 0;
		j = DDCBuffer[5];
		if(DDCCI_pointer < DDCCI_cont)
		{
			//传4批次，每批次32BYTE
			for(i = 0; i < j; i++)
			{
				if(Flash_HDCPcont == 0)
				{
					DDC1[DDCCI_pointer] = DDCBuffer[6 + i];
					DDCCi_checksun += DDC1[DDCCI_pointer];
				}
				else if(Flash_HDCPcont == 1)
				{
					DDC1[DDCCI_pointer + 128] = DDCBuffer[6 + i];
					DDCCi_checksun += DDC1[DDCCI_pointer + 128];
				}
				else if(Flash_HDCPcont == 2)
				{
					DDC1[DDCCI_pointer + 256] = DDCBuffer[6 + i];
					DDCCi_checksun += DDC1[DDCCI_pointer + 256];
				}
				DDCCI_pointer++;
			}
			if(DDCCI_pointer <= (DDCCI_cont - 1)) //2<=  保证卡在最后一次发送校验码
			{
				DDCBuffer[0] = 0x84;
				DDCBuffer[1] = 0x00;
				DDCBuffer[2] = 0x4F;
				return 2;
			}
			else if((DDCCI_pointer == DDCCI_cont) && (Tchecksun == DDCCi_checksun))
			{
				//////////////////////////////至此->本批次接收数据OK，可以以Hdcp_pointer为OFFSET 进行保存/////////////////////////////////////
				//Flash_Write_Factory_KeySet(FLASH_KEY_HDCP, Hdcp_pointer,  DDCCI_cont, RX_EDID, DDCCI_cont);
				if(Flash_HDCPcont == 2)
				{
					#if USEFLASH
					Flash_Write_Factory_KeySet(FLASH_KEY_HDCP, 0, HDCPKEY_SIZE, DDC1, HDCPKEY_SIZE);
					#else
					NVRam_WriteTbl( RM_HDCP_KEY_BASEADDR, DDC1, 128 );
					NVRam_WriteTbl( RM_HDCP_KEY_BASEADDR + 128, DDC1 + 128, 128 );
					NVRam_WriteTbl( RM_HDCP_KEY_BASEADDR + 256, DDC1 + 256, 33 );
					#endif
				}
				Flash_HDCPcont++;
				DDCBuffer[0] = 0x84;
				DDCBuffer[1] = DDCCi_checksun & 0xff;
				DDCBuffer[2] = DDCCi_checksun >> 8;
				return 2;
			}
			else
			{
				DDCBuffer[0] = 0x84;
				DDCBuffer[1] = 0x03;
				DDCBuffer[2] = 0x58;
				return 2;
			}
		}
		else
		{
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x03;
			DDCBuffer[2] = 0x58;
			return 2;
		}
	}
	else if((DDCBuffer[3] == 0x39) && (DDCBuffer[4] == 0x36)) //HDCP 校验
	{
		WORD  wCount ;
		BYTE   i = 0;
		//在此处对保存的数据进行读取，如果校验和与此前接收的校验和相等则OK,否则NG.
		checksun_verify = 0;
		for(i = 0; i < 20; i++)
			DDC1[i] = 0;
		#if USEFLASH
		Flash_Read_Factory_KeySet(FLASH_KEY_HDCP, TRUE, 0, HDCPKEY_SIZE, DDC1, HDCPKEY_SIZE);
		#else
		NVRam_ReadTbl( RM_HDCP_KEY_BASEADDR, &DDC1, 128 );
		NVRam_ReadTbl( RM_HDCP_KEY_BASEADDR + 128, &DDC1 + 128, 128 );
		NVRam_ReadTbl( RM_HDCP_KEY_BASEADDR + 256, &DDC1 + 256, 33 );
		#endif
		for(wCount = 0; wCount < 289; wCount++)
		{
			checksun_verify += DDC1[wCount];
		}
		if(DDCCi_checksun == checksun_verify)
		{
			Set_LoadHDCPKeyFlag();
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x00;
			DDCBuffer[2] = 0x4f;
			return 2;
		}
		else
		{
			DDCBuffer[0] = 0x84;
			DDCBuffer[1] = 0x03;
			DDCBuffer[2] = 0x58;
			return 2;
		}
	}
	#endif
	else if((DDCBuffer[3] == 0x35) && (DDCBuffer[4] == 0x1F) && (DDCBuffer[5] == 1)) //exit align mode
	{
		ubAutoAlign = 0;
		if(FactoryModeFlag)
		{
			Osd_Hide();
			Clr_FactoryModeFlag();
			MenuPageIndex = RootMenu;
		}
		#if USEFLASH
		SaveMonitorSetting();
		#else
		NVRam_WriteByte(nvrMonitorAddr(MonitorFlag), MonitorFlags);
		#endif
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x00;
		DDCBuffer[2] = 0x4F;
		return 2;
	}
	else
	{
		DDCBuffer[0] = 0x84;
		DDCBuffer[1] = 0x03;
		DDCBuffer[2] = 0x58;
		return 2;
	}
	return 2;
}
#endif

#if ENABLE_DP_INPUT	//121130 Modify
#if DPENABLEMCCS
BYTE data ucfinal_status, g_ucDDC_TxRecord ; // use idata to speedup
WORD data DDC2BI_INT_STS, DDC2BI_R_BUF, DDC2BI_W_BUF, DDC2BI_INT_CLR;
code BYTE dpNullMsg[3] = {0x6e, 0x80, 0xbe};
static BYTE u8DDC_RxRecord = 0;
#endif
#endif
//BYTE u8BackupOutDE_H,u8BackupOutDE_L;
//#endif

BYTE code MODEL_TYPE[] =
{
	Model
};

extern  BYTE xdata MenuPageIndex;
extern  BYTE xdata MenuItemIndex;

#if Enabe_DDCCI_FUNCTION
BYTE code CAP_VCP[] =
{
	"("
	"vcp(02 04 05 06 08 0E 10 12 14( 04 05 08 0B) 16 18 1A 1E 20 30 3E "
	#if 0//AudioFunc
	"62 "
	"8D "
	#endif
	#if Dual
	"60(01 03) "
	#endif
	"C8 C9 "
	#if Enable_DDCCI_OSDEnable_EN
	"CA "
	#endif
	#if 1
	"CC(01 02 03 04 05 06 07 09 0A 0B 0D 0E 12 14 16 1E) "
	#endif
	"B0 B6 D6 DF F8)"
	"prot(monitor)"
	"type(LCD)"
	"cmds(01 02 03 07 0C F3)"
	"mccs_ver(2.1)"
	"asset_eep(64)"
	"mpu_ver("FWVersion")"
	"model("Model")"
	"mswhql(1)"
	")"
};
#if Dual
BYTE code DVI_CAP_VCP[] =
{
	"("
	"vcp(02 04 05 08 10 12 14( 04 05 08 0B) 16 18 1A 60(01 03)"
	#if AudioFunc
	"62 "
	"8D "
	#endif
	#if Dual
	"60(01 03) "
	#endif
	" C8 C9 "
	#if 1
	"CC(01 02 03 04 05 06 07 09 0A 0B 0D 0E 12 14 16 1E) "
	#endif
	"B0 B6 D6 DF "
	#if ENABLE_FREESYNC
	"ED "
	#endif
	#if Enable_DDCCI_OSDEnable_EN
	"CA "
	#endif
	"F8)"
	"prot(monitor)"
	"type(LCD)"
	"cmds(01 02 03 07 0C F3)"
	"mccs_ver(2.1)"
	"asset_eep(64)"
	"mpu_ver("FWVersion")"
	"model("Model")"
	"mswhql(1)"
	")"
};
#endif
#else
BYTE code CAP_VCP[] =
{
	"6C 6E 70 C8 C9 "
};
#if Dual
BYTE code DVI_CAP_VCP[] =
{
	"6C 6E 70 C8 C9 "
};
#endif
#endif

void DDC2Bi_InitRx(void)
{
	rxStatus = DDC2B_CLEAR;
	rxIndex = 0;
}
void DDC2Bi_Init( void )
{
	drvDDC2Bi_Init();
}
void DDC2Bi_GetTxBuffer( void )
{
	BYTE i;
	for( i = MAX_TXWAIT_DELAY; i > 0; i-- )
		if( txStatus == DDC2B_MSGON )
		{
			Delay1ms( 1 );
		}
	txStatus = DDC2B_CLEAR;
}
BYTE DDC2Bi_ComputeChecksum( BYTE count )
{
	BYTE CheckSum;
	BYTE i = 0;
	CheckSum = INITTxCK;
	for( ; count > 0; count-- )
		CheckSum ^= DDCBuffer[i++];
	return CheckSum;
}
void DDC2Bi_MessageReady( void )
{
	drvDDC2Bi_MessageReady();
}
void DDC2Bi_ParseCommand( void )
{
	drvDDC2Bi_ParseCommand();
}
void DDC2Bi_CommandHandler( void )
{
	if( rxStatus == DDC2B_COMPLETED )
	{
		DDC2Bi_ParseCommand();
		Clr_RxBusyFlag();
		DDC2Bi_InitRx();
	}
}
void DoDDCCI( BYTE Source ) // Annie 2006.7.5
{
	drvDoDDCCI(Source);
}
void ISR_DDC2Bi(void)
{
	#if CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF
	if( ADC_INT_FLAG & ( BIT3 | BIT4 ) )
	{
		DoDDCCI( InputCombo_A0 );
		CLR_ADC_INT_FLAG();
	}
	#if DDC_Port_D0
	else if( DDCDVI0_INT_FLAG & ( BIT3 | BIT4 ) )
	{
		DoDDCCI( InputCombo_D0 );
		CLR_DVI0_INT_FLAG();
	}
	#endif
	#if DDC_Port_D1
	else if( DDCDVI1_INT_FLAG & ( BIT3 | BIT4 ) )
	{
		DoDDCCI( InputCombo_D1 );
		CLR_DVI1_INT_FLAG();
	}
	#endif
	#if DDC_Port_D2
	else if( DDCDVI2_INT_FLAG & ( BIT3 | BIT4 ) )
	{
		DoDDCCI( InputCombo_D2 );
		CLR_DVI2_INT_FLAG();
	}
	#endif
	#else // CHIP_ID != CHIP_TSUMC
	if( ADC_INT_FLAG & ( BIT3 | BIT4 ) )
	{
		DoDDCCI( Input_VGA );
		CLR_ADC_INT_FLAG();
	}
	#if INPUT_TYPE!=INPUT_1A
	else if( DDCDVI_INT_FLAG & ( BIT3 | BIT4 ) )
	{
		DoDDCCI( Input_Digital );
		CLR_DVI_INT_FLAG();
	}
	#endif
	#if ENABLE_HDMI
	else if( DDCHDMI_INT_FLAG & ( BIT3 | BIT4 ) )
	{
		DoDDCCI( Input_HDMI );
		CLR_HDMI_INT_FLAG();
	}
	#endif
	#endif // #if CHIP_ID == CHIP_TSUMC
}


#if  ENABLE_DP_INPUT	//121130 Modify
#if  DPENABLEMCCS
//================= DP =====================
#if CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD//130607 xiandi
void DDC2BI_DP(void)
{
	BYTE u8AUXCH_RxCmd;
	BYTE u8DDC_Length;
#define u8DDC_RxOnGoing u8DDC_RxRecord
	u8AUXCH_RxCmd = (msRegs[REG_0638 + Aux]) & 0x0F;
	u8DDC_Length = msRegs[REG_063A + Aux];
	//===============//<write>PC Read Command============================
	if(u8AUXCH_RxCmd & _BIT0)    //DP Tx
	{
		if (u8DDC_Length)
		{
			if(rxStatus == DDC2B_CLEAR && txLength)
			{
				while(u8DDC_Length-- && txLength)
				{
					if(g_ucDDC_TxRecord)
					{
						msRegs[REG_06D3 + Aux] = DDCBuffer[g_ucDDC_TxRecord - 1];
						txLength--;
					}
					else
						msRegs[REG_06D3 + Aux] = DDC2B_DEST_ADDRESS;
					g_ucDDC_TxRecord++;
				}
			}
			else
			{
				while(u8DDC_Length--)
				{
					msRegs[REG_06D3 + Aux] = dpNullMsg[g_ucDDC_TxRecord++];
				}
			}
		}
	}
	//===============//<write>PC Write Command============================
	else if(u8AUXCH_RxCmd == 0x00 || u8AUXCH_RxCmd == 0x04) //DP Rx
	{
		if (u8DDC_Length)
		{
			if (!u8DDC_RxOnGoing)
			{
				BYTE xdata temp;
				msRegs[REG_06FC + Aux] = msRegs[REG_06FC + Aux] | _BIT2;
				temp = msRegs[REG_0675 + Aux];
				rxIndex = 0;
				u8DDC_RxOnGoing = TRUE;
				u8DDC_Length--;
			}
			while(u8DDC_Length--)
			{
				BYTE xdata temp1 = 10;
				msRegs[REG_06FC + Aux] = msRegs[REG_06FC + Aux] | _BIT2;
				while(temp1--) {};
				temp1 = 10;
				DDCBuffer[rxIndex++] = msRegs[REG_0675 + Aux];
			}
		}
		if (u8AUXCH_RxCmd == 0x00)
		{
			u8DDC_RxOnGoing = FALSE;
			g_ucDDC_TxRecord = 0;
			rxStatus = DDC2B_COMPLETED;
			txLength = 0;
		}
	}
	msRegs[REG_0679 + Aux] = msRegs[REG_0679 + Aux] | _BIT7; //Clear Interrupt
	msRegs[REG_0679 + Aux] = 0x00;
#undef u8DDC_RxOnGoing
}
void msDP_DDC2BI(void)
{
	if(msRegs[REG_0678 + Aux]&_BIT7)   //MCCS Interrupt
	{
		DDC2BI_DP() ;
	}
}
#elif CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF
//================= DP =====================

void DDC2BI_DP(void)     //Rockman
{
	BYTE u8AUXCH_RxCmd;
	BYTE u8DDC_Length;
#define u8DDC_RxOnGoing u8DDC_RxRecord
	u8AUXCH_RxCmd = (msRegs[REG_0638 + Aux]) & 0x0F;
	u8DDC_Length = msRegs[REG_063A + Aux];
	//===============//<write>PC Read Command============================
	if(u8AUXCH_RxCmd & _BIT0)    //DP Tx
	{
		if (u8DDC_Length)
		{
			if(rxStatus == DDC2B_CLEAR && txLength)
			{
				while(u8DDC_Length-- && txLength)
				{
					if(g_ucDDC_TxRecord)
					{
						msRegs[REG_06F3] = DDCBuffer[g_ucDDC_TxRecord - 1];
						//msRegs[REG_06F3]= test[g_ucDDC_TxRecord-1];
						txLength--;
					}
					else
						msRegs[REG_06F3] = DDC2B_DEST_ADDRESS;
					msRegs[REG_06F2 ] = BIT0;
					while( ! (((msRegs[REG_06F2])&BIT2)))		// Wait
					{}
					msRegs[REG_06F1 ] = BIT1;				       // Clear
					g_ucDDC_TxRecord++;
				}
			}
			else
			{
				while(u8DDC_Length--)
				{
					msRegs[REG_06F3] = dpNullMsg[g_ucDDC_TxRecord++];
					msRegs[REG_06F2 ] = BIT0;
					while( ! (((msRegs[REG_06F2])&BIT2)))		// Wait
					{}
					msRegs[REG_06F1 ] = BIT1;				       // Clear
				}
			}
		}
	}
	//===============//<write>PC Write Command============================
	else if(u8AUXCH_RxCmd == 0x00 || u8AUXCH_RxCmd == 0x04) //DP Rx
	{
		if (u8DDC_Length)
		{
			if (!u8DDC_RxOnGoing)
			{
				BYTE xdata temp;
				msRegs[REG_06F0] = msRegs[REG_06F0] | _BIT0;
				while( ! (((msRegs[REG_06F0])&BIT2)))		// Wait
				{}
				msRegs[REG_06F0 ] = BIT1;				       // Clear
				temp = msRegs[REG_0675];
				rxIndex = 0;
				u8DDC_RxOnGoing = TRUE;
				u8DDC_Length--;
			}
			while(u8DDC_Length--)
			{
				BYTE xdata temp1 = 10;
				msRegs[REG_06F0] = msRegs[REG_06F0] | _BIT0;
				while( ! (((msRegs[REG_06F0])&BIT2)))		// Wait
				{}
				msRegs[REG_06F0 ] = BIT1;
				DDCBuffer[rxIndex++] = msRegs[REG_0675];
				//DDCData[rxIndex++] = msRegs[REG_0675];
			}
		}
		if (u8AUXCH_RxCmd == 0x00)
		{
			u8DDC_RxOnGoing = FALSE;
			g_ucDDC_TxRecord = 0;
			rxStatus = DDC2B_COMPLETED;
			txLength = 0;
		}
	}
	msRegs[REG_0679 + Aux] = msRegs[REG_0679 + Aux] | _BIT7; //Clear Interrupt
	msRegs[REG_0679 + Aux] = 0x00;
#undef u8DDC_RxOnGoing
}

void msDP_DDC2BI(void)
{
	if(msRegs[REG_0678 + Aux]&_BIT7)   //MCCS Interrupt
	{
		DDC2BI_DP() ;
	}
}


#else
void DDC2BI_DP(void)
{
	BYTE u8AUXCH_RxCmd;
	BYTE u8DDC_Length;
#define u8DDC_RxOnGoing u8DDC_RxRecord
	u8AUXCH_RxCmd = msRegs[REG_1FF4];
	u8DDC_Length = msRegs[REG_1FF6];
	//===============//<write>PC Read Command============================
	if(u8AUXCH_RxCmd & _BIT4)    //DP Tx
	{
		if (u8DDC_Length)
		{
			if(rxStatus == DDC2B_CLEAR && txLength)
			{
				while(u8DDC_Length-- && txLength)
				{
					if(g_ucDDC_TxRecord)
					{
						msRegs[REG_1FF9] = DDCBuffer[g_ucDDC_TxRecord - 1];
						txLength--;
					}
					else
						msRegs[REG_1FF9] = DDC2B_DEST_ADDRESS;
					g_ucDDC_TxRecord++;
				}
			}
			else
			{
				while(u8DDC_Length--)
				{
					msRegs[REG_1FF9] = dpNullMsg[g_ucDDC_TxRecord++];
				}
			}
		}
	}
	//===============//<write>PC Read Command============================
	else if(u8AUXCH_RxCmd == 0x00 || u8AUXCH_RxCmd == 0x40) //DP Rx
	{
		if (u8DDC_Length)
		{
			if (!u8DDC_RxOnGoing)
			{
				BYTE xdata temp;
				msRegs[REG_1FFA] = msRegs[REG_1FFA] | _BIT2;
				temp = msRegs[REG_1FF8];
				rxIndex = 0;
				u8DDC_RxOnGoing = TRUE;
				u8DDC_Length--;
			}
			while(u8DDC_Length--)
			{
				BYTE xdata temp1 = 10;
				msRegs[REG_1FFA] = msRegs[REG_1FFA] | _BIT2;
				while(temp1--) {};
				temp1 = 10;
				DDCBuffer[rxIndex++] = msRegs[REG_1FF8];
				//DDCBuffer_Temp[rxIndex++]= msRegs[REG_1FF8];
			}
		}
		if (u8AUXCH_RxCmd == 0x00)
		{
			u8DDC_RxOnGoing = FALSE;
			g_ucDDC_TxRecord = 0;
			rxStatus = DDC2B_COMPLETED;
			txLength = 0;
		}
	}
	msRegs[REG_1FEA] = msRegs[REG_1FEA] | _BIT7; //Clear Interrupt
	msRegs[REG_1FFA] = 0x00;
#undef u8DDC_RxOnGoing
}
void msDP_DDC2BI(void)
{
	if(msRegs[REG_1FE6]&_BIT7)   //MCCS Interrupt
	{
		DDC2BI_DP() ;
	}
}
#endif
#endif
#endif
#if ENABLE_DeltaE

/////////////////////////////////////////////////////////////////////
//
// AUTO-GAMMA
/////////////////////////////////////////////////////////////////////
////Auto-Gamma Varible Declaration///////////
BYTE BackupOutDE_L;
BYTE BackupOutDE_H;
BYTE g_CheckSumResult;
CSTransferSettingType xdata g_CS_Setting[2];
BYTE xdata bToolWriteGamma = 0;

WORD xdata u16ChkSum_Addr = 0;
code BYTE* tAllFGamma3x3Matrix[2] =
{
	g_CS_Setting[0].CM,
	g_CS_Setting[1].CM,
};

code BYTE tSRGB_CM[18] = { 0xfb, 0x03, 0x12, 0x00, 0xdf, 0x1f,
                           0xfa, 0x1f, 0xd0, 0x03, 0x30, 0x00,
                           0x05, 0x00, 0x53, 0x00, 0xa7, 0x03,
                         };

code BYTE tAdobe_CM[18] = {0x62, 0x03, 0x0B, 0x00, 0x08, 0x00, 0x16, 0x00, 0x39, 0x03, 0x10, 0x00, 0x0D, 0x00,
                           0x02, 0x00, 0xF0, 0x03,
                          };


void msWriteFGammaTbl(BOOL bWindow)
{
	#if ENABLE_USE_NewDeltaE
	XDATA BYTE ucTrigger, j ;
	//XDATA BYTE wLevel;
	XDATA WORD wData[2], k;
	XDATA BYTE i;
	XDATA BYTE ucBank, *ucTab1;
	ucBank = scReadByte( 0 );
	msWriteByte(SC0_00, 0x0E);
	if(bWindow)
		msWriteBit(SCE_22, 0, _BIT0);
	else
		msWriteBit(SCE_02, 0, _BIT0);
	for(j = 0 ; j < 3; j++)
	{
		ucTab1 = tAllFrontEndGammaTab[0];
		if(j == 0)      // R
			ucTrigger = 0;
		else if(j == 1) // G
			ucTrigger = _BIT2;
		else if(j == 2) // B
			ucTrigger = _BIT3;
		else if(j == 3) // R/G/B
			ucTrigger = _BIT2 | _BIT3;
		msWrite2Byte(SCE_C0, 0x00);//LUT table R/W address
		msWriteByteMask(SCE_C2, _BIT1 | _BIT0 | ucTrigger, _BIT0 | _BIT1 | _BIT2 | _BIT3); // wrtie enable, ise burst write
		msWriteByteMask(SCE_C2, 0, BIT4);
		/*
		// From level 0 ~ 255
		for( i = 0;i <128; i++ )
		{
		// Cal data
			for( wLevel =0;wLevel<2;wLevel++)
			{
				if(wLevel ==1)
				    wData = (((WORD)ucTab1[i*3+2]) <<4 |((ucTab1[i*3]&0xF0)>>4));
				else
				    wData = (((WORD)ucTab1[i*3+1]) <<4 |(ucTab1[i*3]&0x0F));
				// Write gamma data;
				printData(" %x  ", wData);
				scWrite2Byte(SCE_C4, wData);//msWriteWord( SCE_C5, wData ); //scWriteWord(SCE_C5, wData);
			}
		}
		*/
		for( k = 0; k < 384; k = k + 3 )
		{
			wData[0] = ucTab1[k] | ((ucTab1[k + 2] & 0x0F) << 8) ;
			wData[1] = ucTab1[k + 1] | ((ucTab1[k + 2] & 0xF0) << 4) ;
			for(i = 0; i < 2 ; i++)
			{
				//printData(" %x  ", wData[i]);
				msWrite2Byte(SCE_C4, wData[i]);
			}
		}
		msWriteByteMask(SCE_C2, 0x00, BIT1 | BIT0);	//msWriteByteMask(SC25_F0, 0x00, 0xC0);
	}
	scWriteByte( 0, ucBank );
	#else
	XDATA BYTE ucTrigger, j ;
	//XDATA BYTE wLevel;
	XDATA WORD wData[2], k;
	XDATA BYTE i;
	XDATA BYTE  *ucTab1;
	if(bWindow)
		msWriteByteMask(SCE_22, 0, _BIT0);
	else
		msWriteByteMask(SCE_02, 0, _BIT0);
	for(j = 0 ; j < 3; j++)
	{
		ucTab1 = tAllFrontEndGammaTab[0];
		if(j == 0)      // R
			ucTrigger = 0;
		else if(j == 1) // G
			ucTrigger = _BIT2;
		else if(j == 2) // B
			ucTrigger = _BIT3;
		else if(j == 3) // R/G/B
			ucTrigger = _BIT2 | _BIT3;
		msWrite2Byte(SCE_C0, 0x00);//LUT table R/W address
		msWriteByteMask(SCE_C2, _BIT1 | _BIT0 | ucTrigger, _BIT0 | _BIT1 | _BIT2 | _BIT3); // wrtie enable, ise burst write
		msWriteByteMask(SCE_C2, 0, BIT4);
		for( k = 0; k < 384; k = k + 3 )
		{
			wData[0] = (WORD)ucTab1[k] | ((WORD)(ucTab1[k + 2] & 0x0F) << 8) ;
			wData[1] = (WORD)ucTab1[k + 1] | ((WORD)(ucTab1[k + 2] & 0xF0) << 4) ;
			for(i = 0; i < 2 ; i++)
			{
				//printData(" %x  ", wData[i]);
				msWrite2Byte(SCE_C4, wData[i]);
			}
		}
		msWriteByteMask(SCE_C2, 0x00, BIT1 | BIT0);	//msWriteByteMask(SC25_F0, 0x00, 0xC0);
	}
	#endif
}

void msWriteFixGammaTbl(BOOL bWindow)
{
	#if ENABLE_USE_NewDeltaE
	XDATA BYTE ucTrigger, j, i ;
	XDATA WORD wData[2], k;
	XDATA BYTE ucBank, *ucTab1;
	ucBank = scReadByte( 0 );
	msWriteByte(SC0_00, 0x0E);
	if(bWindow)
		msWriteBit(SCE_22, 0, _BIT2);
	else
		msWriteBit(SCE_02, 0, _BIT2);
	for(j = 0 ; j < 3; j++)
	{
		ucTab1 = tAllxvYccFixGammaTab[0];
		if(j == 0)      // R
			ucTrigger = 0;
		else if(j == 1) // G
			ucTrigger = _BIT2;
		else if(j == 2) // B
			ucTrigger = _BIT3;
		else if(j == 3) // R/G/B
			ucTrigger = _BIT2 | _BIT3;
		msWrite2Byte(SCE_E0, 0x00);//LUT table R/W address
		msWriteByteMask(SCE_E2, _BIT1 | _BIT0 | ucTrigger, _BIT0 | _BIT1 | _BIT2 | _BIT3); // wrtie enable, ise burst write
		msWriteByteMask(SCE_E2, 0, BIT4);
		/*
		for( k = 0;k <512; k=k+2 )
		{
		    wData = (WORD)(ucTab1[k+1] << 8)| ucTab1[k] ;
		    //printData(" %x  ", wData);
		    scWrite2Byte(SCE_E4, wData);
		}
		*/
		for( k = 0; k < 384; k = k + 3 )
		{
			wData[0] = ucTab1[k] | ((ucTab1[k + 2] & 0x0F) << 8) ;
			wData[1] = ucTab1[k + 1] | ((ucTab1[k + 2] & 0xF0) << 4) ;
			for(i = 0; i < 2 ; i++)
			{
				//printData(" %x  ", wData[i]);
				msWrite2Byte(SCE_E4, wData[i]);
			}
		}
		msWriteByteMask(SCE_E2, 0x00, BIT1 | BIT0);	//msWriteByteMask(SC25_F0, 0x00, 0xC0);
	}
	scWriteByte( 0, ucBank );
	#else
	XDATA BYTE ucTrigger, j, i ;
	XDATA WORD wData[2], k;
	XDATA BYTE  *ucTab1;
	if(bWindow)
		msWriteByteMask(SCE_22, 0, _BIT2);
	else
		msWriteByteMask(SCE_02, 0, _BIT2);
	for(j = 0 ; j < 3; j++)
	{
		ucTab1 = tAllxvYccFixGammaTab[0];
		if(j == 0)      // R
			ucTrigger = 0;
		else if(j == 1) // G
			ucTrigger = _BIT2;
		else if(j == 2) // B
			ucTrigger = _BIT3;
		else if(j == 3) // R/G/B
			ucTrigger = _BIT2 | _BIT3;
		msWrite2Byte(SCE_E0, 0x00);//LUT table R/W address
		msWriteByteMask(SCE_E2, _BIT1 | _BIT0 | ucTrigger, _BIT0 | _BIT1 | _BIT2 | _BIT3); // wrtie enable, ise burst write
		msWriteByteMask(SCE_E2, 0, BIT4);
		for( k = 0; k < 384; k = k + 3 )
		{
			wData[0] = (WORD)ucTab1[k] | ((WORD)(ucTab1[k + 2] & 0x0F) << 8) ;
			wData[1] = (WORD)ucTab1[k + 1] | ((WORD)(ucTab1[k + 2] & 0xF0) << 4) ;
			//wData[0] = 0;
			//wData[1] = 0;
			for(i = 0; i < 2 ; i++)
			{
				//printData(" %x  ", wData[i]);
				msWrite2Byte(SCE_E4, wData[i]);
			}
		}
		msWriteByteMask(SCE_E2, 0x00, BIT1 | BIT0);	//msWriteByteMask(SC25_F0, 0x00, 0xC0);
	}
	#endif
}

void msWriteFGammaCM(BYTE bWindow, BYTE idxGamma)
{
	XDATA BYTE idx;
	XDATA WORD ucAddr;
	XDATA BYTE* pcTab;
	if( bWindow == 0 )
	{
		ucAddr = SCE_04 ;
	}
	else
	{
		ucAddr = SCE_24;
	}
	pcTab =  tAllFGamma3x3Matrix[idxGamma];
	for (idx = 0; idx < 18; idx++)
	{
		msWriteByte( ucAddr + idx, pcTab[idx]);
		//printData("w-cm %x  ", pcTab[idx]);
	}
}

void LoadPostGamma(BYTE GmaTblSize)
{
	XDATA WORD i, BaseAddr,  GammaTbl[4], DiffValue0, DiffValue1, SumValue, wRGBGamAddStart = 0 ;
	XDATA BYTE NvrValue, j, ucTrigger, ChannelIndex = 0;
	//BaseAddr = AddrOfPostGamma;
	BaseAddr = BGammaTblAddr;
	msWrite2Byte(SC8_20, 0x00);
	msWriteByteMask( SC8_22, 0x03, BIT1 | BIT0); // Main Window
	for(ChannelIndex = 0 ; ChannelIndex < 3; ChannelIndex++)
	{
		switch(ChannelIndex)
		{
			case 0:
			{
				ucTrigger = 0;
			}
			break;
			case 1:
			{
				ucTrigger = _BIT2;
			}
			break;
			case 2:
			{
				ucTrigger = _BIT3;
			}
			break;
		}
		wRGBGamAddStart = (WORD)GmaTblSize * ChannelIndex ;
		msWriteByteMask( SC8_22, ucTrigger, BIT2 | BIT3);
		for(j = 0; j < 4; j++)
			GammaTbl[j] = 0;
		SumValue = 0;
		for (i = 0; i < GmaTblSize; i++)
		{
			NvrValue = 0;
			NVRam_ReadByte(BaseAddr + wRGBGamAddStart + i, &NvrValue);
			DiffValue1 = NvrValue & 0x0F;
			DiffValue0 = (NvrValue & 0xF0) >> 4;
			if(i == 0)
				GammaTbl[0] = 0;
			else
			{
				GammaTbl[0] = GammaTbl[3] ;
				GammaTbl[0] = GammaTbl[0] + DiffValue0 ;
			}
			GammaTbl[1] = GammaTbl[0] + DiffValue0 ;
			GammaTbl[2] = GammaTbl[1] + DiffValue1 ;
			GammaTbl[3] = GammaTbl[2] + DiffValue1 ;
			for(j = 0; j < 4; j++)
			{
				if(GammaTbl[j] > 1023)
					GammaTbl[j] = 1023;
				//printData(" GammaTbl=  %x", GammaTbl[j]);
				msWrite2Byte(SC8_24, GammaTbl[j]);
			}
		}
	}
	msWriteByteMask( SC8_22, 0, BIT1 | BIT0 );
}

#if 0
void ReadSrgbDefaultValue(int CMIndex)//Hans120316
{
	XDATA BYTE j, idx, chkSum = 0 ;
	for(j = 0; j < 18; j++)
	{
		if(CMIndex == 0)
		{
			g_CS_Setting[0].CM[j] = tSRGB_CM[j];
			chkSum ^= tSRGB_CM[j];
		}
		else
		{
			g_CS_Setting[1].CM[j] = tAdobe_CM[j];
			chkSum ^= tAdobe_CM[j];
		}
	}
	//if(CMIndex)
	//    NVRam_WriteByte(RM_COLORSPACE_TRANS_ChkSum_ADDR+1, chkSum);
	//else
	//    NVRam_WriteByte(RM_COLORSPACE_TRANS_ChkSum_ADDR, chkSum);
	for(idx = 0 ; idx < 18 ; idx++)
		NVRam_WriteByte( (RM_COLORSPACE_TRANS_BASEADDR + idx) + (sizeof(CSTransferSettingType)*CMIndex), g_CS_Setting[CMIndex].CM[idx]  );
}
#endif

void LoadDeltaEColorMode(BOOL bWindow, BYTE ModeIndex, BOOL Enable)//Hans 120223 need modify
{
	XDATA BYTE idx;
	msWriteByteMask(SCE_02,  0, _BIT2 | _BIT1 | _BIT0); // fix-gamma/color-matrix/de-gamma disable.
	msWriteByteMask(SC8_3F, 0, _BIT7);
	// disable noise masking
	msWriteByte(SC7_D0, 0);
	msWriteByte(SC7_D2, 0);
	if(Enable)
	{
		//DeGamma
		msWriteFGammaTbl(bWindow);
		//Color Matrix
		for(idx = 0 ; idx < 18 ; idx++)
		{
			NVRam_ReadByte((RM_COLORSPACE_TRANS_BASEADDR + idx) + (sizeof(CSTransferSettingType)*ModeIndex), &g_CS_Setting[ModeIndex].CM[idx]);
			// printData("NVRAM value ==>%x",g_CS_Setting[ModeIndex].CM[idx]  );
		}
		msWriteFGammaCM(bWindow, ModeIndex);
		//FixGamma
		msWriteFixGammaTbl(bWindow); //Hans120412
		//Post Gamma
		//LoadPostGamma(bWindow,1, BGammaTblAddr,BGammaTblAddr1, GammaTblSize);
		msWriteByteMask(SCE_02,  _BIT2 | _BIT1 | _BIT0, _BIT2 | _BIT1 | _BIT0); // fix-gamma/color-matrix/de-gamma enable.
		msWriteByteMask(SC8_3F, _BIT7, _BIT7);
		drvGammaOnOff(_DISABLE, MAIN_WINDOW );
		drvGammaOnOff(_DISABLE, SUB_WINDOW );
		mStar_WaitForDataBlanking();
		LoadPostGamma(GammaTblSize);
		Delay1ms(50);
		//mStar_WaitForDataBlanking();
		drvGammaOnOff(_ENABLE, MAIN_WINDOW );
		drvGammaOnOff(_ENABLE, SUB_WINDOW );
		//AUTOGAMMA_PUTSTR("\r\n Load DE color table");
	}
}

#endif
//===================================================
#ifdef UseVGACableReadWriteAllPortsEDID
typedef enum
{
	VGA1_EDID_DDC2BI = BIT7,
	DVI1_EDID_DDC2BI = BIT5,
	HDMI1_EDID_DDC2BI = BIT3,
	HDMI2_EDID_DDC2BI = BIT2,
	DP1_EDID_DDC2BI = BIT1,
	MHL_EDID_DDC2BI = BIT5,
	HDMI1_EDID20_EDID_DDC2BI = BIT7,
	HDMI2_EDID20_EDID_DDC2BI = BIT6,
	#if 0//OSD_ENABLE_FREESYNC
	VCP_TPV_PORT_DP1_SECOND = BIT2,
	#endif

} drvFactoryInputPortEDID;

WORD appFactorySetEdidWriteStart( BYTE ucControl )
{
	BYTE xdata ucInputEDID_High, ucInputEDID_Low;
	ucInputEDID_High = 0x00;
	ucInputEDID_Low  = 0x00;
	//Monitor Feedback: 6f 6e 83 02 EDIDPort Status chksum
	//Return Input Types Information
	//
	#if ENABLE_VGA
	ucInputEDID_High |= VGA1_EDID_DDC2BI;
	#endif
	#if ENABLE_DVI
	ucInputEDID_High |= DVI1_EDID_DDC2BI;
	#endif
	#if ENABLE_HDMI
	ucInputEDID_High |= HDMI1_EDID_DDC2BI;
	#endif
	#if ENABLE_HDMI2
	ucInputEDID_High |= HDMI2_EDID_DDC2BI;
	#endif
	#if ENABLE_DP_INPUT
	ucInputEDID_High |= DP1_EDID_DDC2BI;
	#endif
	//BIT0=0,EDID Saved in EEPRom;BIT0=1,EDID Saved in Flash
	//BIT1:(0:Write Disable;1:Write Enable)
	if( ucControl == 0x01 )
	{
		//hw_ClrBlacklit();
		//SET_FACTORY_MODE_FLAG();
		//  hw_ClrDDC_WP();
		//Set_WriteEnableFlag();
		ucInputEDID_Low = ucInputEDID_Low | BIT1;
	}
	else
	{
		//CLR_FACTORY_MODE_FLAG();
		hw_SetDDC_WP();
		//Clr_WriteEnableFlag();
		//SET_DFM_LOADEDIDKEY_FLAG();
		#if  0//!USER_PREF_EDID_USEFLASH
		ReadNVRAMBlock(ADDR_EDID_BLOCK, CNT_EDID_BLOCK);
		#endif
		//LoadAligmentEDID();
		ucInputEDID_Low = ucInputEDID_Low & ~(BIT1);
	}
	return (( WORD )ucInputEDID_High << 8 | ucInputEDID_Low );
}
#endif

#if Enabe_DDCCI_FUNCTION

BYTE AlignControl(void)
{
	BYTE CommandCode, CPCode, ValueL, RetValueH, RetValueL, PageValue;
	BYTE TPValue;
	WORD WordValue, ValueH;
	WORD XDATA g_wFDCRCValue = 0;
	#if DDCCI_ENABLE
	WORD WordAddr;
	#endif
	#if JRY_Color_Tool_Functing
	BYTE  XDATA Resault;
	#endif
	CommandCode = DDCBuffer[1];
	PageValue = 0;
	if( (MenuPageIndex != BurninMenu)
	        && (MenuPageIndex != UnsupportedModeMenu)
	        && (MenuPageIndex != LogoMenu))
	{
		#if ENABLE_FREESYNC
		#if FreeSyncMenu_Enable
		if((MenuPageIndex == FreeSyncMenu))//||(MenuPageIndex == SFreesyncMenu))
			Set_OSDFreeSyncActionFlag();
		else
		#endif
		#endif
		{
			#if ENABLE_FREESYNC
			if(MenuPageIndex != InputInfoMenu)
			#endif
			{
				Osd_Hide(); //20151211 for TPV Request
				MenuPageIndex = RootMenu;
				MenuItemIndex = 0;
				Set_LoadOSDDataFlag();
			}
		}
		/*	Osd_Hide(); //20151211 for TPV Request
			MenuPageIndex=RootMenu;
			MenuItemIndex=0;	*/
	}
	#if DDCCI_ENABLE
	if (!DDCciFlag)
		//We can adjust the W/B By DDC2BI When DDCCI Is Disable
	#endif //When DDCCI_ENABLE=0,we use below to disable DDCCI and Use it to adjust W/B
	{
		if (CommandCode == SETVCPFeature || CommandCode == GETVCPFeature)
		{
			CPCode = DDCBuffer[2];
			if (CPCode != 0xFE)
				return FALSE;
		}
		else
			return FALSE;
	}
	#if DDCCI_ENABLE_DEBUG
	Osd_Show();
	Osd_Draw4Num(15, 0, DDCBuffer[1]);
	Osd_Draw4Num(15, 1, DDCBuffer[2]);
	Osd_Draw4Num(15, 2, DDCBuffer[3]);
	Osd_Draw4Num(15, 3, DDCBuffer[4]);
	Osd_Draw4Num(15, 4, DDCBuffer[5]);
	//Delay1ms(1000);
	#endif
	//111----------------------------------------------------------Start
	if (CommandCode == SETVCPFeature)
		// 1-1
	{
		CPCode = DDCBuffer[2];
		RetValueH = DDCBuffer[3];
		RetValueL = DDCBuffer[4];
		WordValue = ((WORD)DDCBuffer[3] << 8) | ((WORD)DDCBuffer[4]);
		#if 0//def WH_REQUEST //20120904
		if((MenuPageIndex >= MainMenu && MenuPageIndex <= InputInfoMenu)
		  )
		{
			{
				ClrOSDWindosw(SUB_WIN_00);
				ClrOSDWindosw(SUB_WIN_01);
				ClrOSDWindosw(SUB_WIN_02);
				ClrOSDWindosw(SUB_WIN_03);
				MenuPageIndex = RootMenu;
				MenuItemIndex = 0;
				Osd_Hide();
			}
		}
		#endif
	}
	else if (CommandCode == GETVCPFeature)
		// 1-2
	{
		CPCode = DDCBuffer[2];
	}
	else if (CommandCode == ModeChangeRequest)
		// 1-3 xx
	{
		CPCode = DDCBuffer[2];
		ValueH = DDCBuffer[3];
	}
	else if (CommandCode == GETPagedVCP)
		// 1-4
	{
		PageValue = DDCBuffer[2];
		CPCode = DDCBuffer[3];
	}
	else if (CommandCode == SETPagedVCP)
		// 1-5
	{
		PageValue = DDCBuffer[2];
		CPCode = DDCBuffer[3];
		RetValueH = DDCBuffer[4];
		RetValueL = DDCBuffer[5];
		WordValue = ((WORD)DDCBuffer[4] << 8) | ((WORD)DDCBuffer[5]);
	}
	#if DDCCI_ENABLE
	else if (CommandCode == CapabilitiesRequest)
		// 1-6
	{
		RetValueH = DDCBuffer[2];
		RetValueL = DDCBuffer[3];
		WordAddr = ((WORD)DDCBuffer[2] << 8) | ((WORD)DDCBuffer[3]);
		#if Dual
		if( CURRENT_INPUT_IS_TMDS()//SrcInputType == Input_Digital || SrcInputType == Input_Digital2
	        #if ENABLE_DP_INPUT
		        || CURRENT_INPUT_IS_DISPLAYPORT()
	        #endif
		  )
			WordValue = sizeof(DVI_CAP_VCP);
		else
		#endif
			WordValue = sizeof(CAP_VCP);
		if (WordAddr >= WordValue)
		{
			DDCBuffer[0] = 0x83;
			DDCBuffer[1] = 0xE3;
			return 3;
		}
#define CapLen CPCode
		CapLen = (WordAddr + 32 >= WordValue) ? (WordValue - WordAddr) : 32;
		DDCBuffer[0] = CapLen + 3 + 0x80;
		DDCBuffer[1] = 0xE3;
		DDCBuffer[2] = RetValueH;
		DDCBuffer[3] = RetValueL;
		for (ValueL = 4; ValueL < CapLen + 4; ValueL++)
		{
			#if Dual
			if( CURRENT_INPUT_IS_TMDS()//SrcInputType == Input_Digital || SrcInputType == Input_Digital2
		        #if ENABLE_DP_INPUT
			        || CURRENT_INPUT_IS_DISPLAYPORT()//SrcInputType == Input_Displayport
		        #endif
			  )
				DDCBuffer[ValueL] = DVI_CAP_VCP[WordAddr + ValueL - 4];
			else
			#endif
				DDCBuffer[ValueL] = CAP_VCP[WordAddr + ValueL - 4];
		}
#undef CapLen
		return DDCBuffer[0] & ~0x80;
	}
	#endif
	else if (CommandCode == EnableApp)
		// 1-7 xx
	{
		DDCBuffer[0] = 0x80;
		return 0; //0xFE;
	}
	else if (CommandCode == AppTest)
		// 1-8 xx
	{
		DDCBuffer[0] = 0x80;
		return 0; //0xFD;
	}
	#if ENABLE_DeltaE
//*******************************************************************************************
//MSTART COMMAND***************************************************************************
//*******************************************************************************************
	else if ( CommandCode == MStar_Command )
	{
		switch(DDCBuffer[2])
		{
			case MS_ColorEngine_OnOff :
			{
				if ( DDCBuffer[3] == 0x00 )
				{
					bToolWriteGamma = 1;
					//Color Engine Off
					msWriteByteMask(SCE_02,  0, _BIT2 | _BIT1 | _BIT0);	// fix-gamma/color-matrix/de-gamma disable.
					msWriteByteMask(SC8_3F, 0, _BIT7);
				}
				else
				{
					bToolWriteGamma = 0;
					msWriteByteMask(SCE_02,  _BIT2 | _BIT1 | _BIT0, _BIT2 | _BIT1 | _BIT0); // fix-gamma/color-matrix/de-gamma enable.
					msWriteByteMask(SC8_3F, _BIT7, _BIT7);
				}
			}
			break;
			case MS_AutoGamma_OnOff :
			{
				if ( DDCBuffer[3] == 0x00 )
				{
					//Off
					msWriteByte( SC0_32, 0x00);
					msWriteByte( SC0_1C, BackupOutDE_L);
					msWriteByte( SC0_1D, BackupOutDE_H );
				}
				else
				{
					//On
					BackupOutDE_L = msReadByte(SC0_1C);
					BackupOutDE_H = msReadByte(SC0_1D);
					msWriteByte( SC0_32, 0x01);
					msWriteByte( SC0_1C,	msReadByte(SC0_18));
					msWriteByte( SC0_1D, 0x00 );
				}
			}
			break;
			case MS_AutoGamma_SetBGColor :
			{
				msWriteByte( SC0_33, DDCBuffer[3] ); // Set Red frame color
				msWriteByte( SC0_34, DDCBuffer[4] ); // Set Green frame color
				msWriteByte( SC0_35, DDCBuffer[5] ); // Set Blue frame	 color
			}
			break;
			#if ENABLE_USE_NewDeltaE
			case MS_GET_MODEL_NAME :
			{
				int i = 0, model_len = 0;
				while(tool_model_panel_name[model_len])
					++model_len;
				++model_len; //for the \0
				DDCBuffer[0] = model_len;
				for( i = 0 ; i < model_len - 1 ; ++i)
					DDCBuffer[i + 1] = tool_model_panel_name[i];
				DDCBuffer[model_len] = 0x00;
				return model_len;
			}
			break;
			case MS_WR_PostGamma :
			{
				XDATA WORD addr, j;
				XDATA BYTE Sum, cnt, GmaMode, GmaChannel;
				XDATA WORD CheckSum_addr = 0, WordAddr;
				Sum = 0;
				g_CheckSumResult = 0 ;
				GmaMode = DDCBuffer[3] ; // gamma mode
				GmaChannel = DDCBuffer[4] ; // gamma channel
				cnt = DDCBuffer[5] ; // data size
				addr = (WORD)(DDCBuffer[6] << 8 );
				addr += DDCBuffer[7]; // start addr-hi, lo
				if (GmaMode == 0)
				{
					WordAddr = BGammaTblAddr + GmaChannel * GammaTblSize + addr;
				}
				#if 0
				else if (GmaMode == 1)
				{
					WordAddr = BGammaTblAddr1 + GmaChannel * GammaTblSize + addr;
					if (cnt == 40)
						CheckSum_addr = BGammaCheckSumStartAddr1 + GmaChannel * 2;
					else if (cnt == 24)
						CheckSum_addr = BGammaCheckSumStartAddr1 + GmaChannel * 2 + 1;
				}
				else if (GmaMode == 2)
				{
					WordAddr = BGammaTblAddr2 + GmaChannel * GammaTblSize + addr;
					if (cnt == 40)
						CheckSum_addr = BGammaCheckSumStartAddr2 + GmaChannel * 2;
					else if (cnt == 24)
						CheckSum_addr = BGammaCheckSumStartAddr2 + GmaChannel * 2 + 1;
				}
				else if (GmaMode == 3)
				{
					WordAddr = BGammaTblAddr3 + GmaChannel * GammaTblSize + addr;
					if (cnt == 40)
						CheckSum_addr = BGammaCheckSumStartAddr3 + GmaChannel * 2;
					else if (cnt == 24)
						CheckSum_addr = BGammaCheckSumStartAddr3 + GmaChannel * 2 + 1;
				}
				else if (GmaMode == 4)
				{
					WordAddr = BGammaTblAddr4 + GmaChannel * GammaTblSize + addr;
					if (cnt == 40)
						CheckSum_addr = BGammaCheckSumStartAddr4 + GmaChannel * 2;
					else if (cnt == 24)
						CheckSum_addr = BGammaCheckSumStartAddr4 + GmaChannel * 2 + 1;
				}
				#endif
				for(j = 0; j < cnt; j++)
				{
					Sum ^=	DDCBuffer[8 + j] ;
				}
				//hw_ClrGreenLed();
				NVRam_WriteTbl(WordAddr, &DDCBuffer[8], cnt);
				//hw_SetGreenLed();
				g_CheckSumResult = Sum;
				NVRam_WriteByte(CheckSum_addr, g_CheckSumResult);
			}
			break;
			case MS_LoadColorMode :
			{
				LoadDeltaEColorMode(MAIN_WINDOW, sRGB_MODE, TRUE); //AdobeRGB_MODE
			}
			break;
			#else
			case MS_WR_PostGamma :
			{
				XDATA WORD addr, j;
				XDATA BYTE Sum, cnt, GmaMode, GmaChannel;
				XDATA WORD CheckSum_addr = 0, WordAddr;
				Sum = 0;
				g_CheckSumResult = 0 ;
				GmaMode = DDCBuffer[3] & 0x01; // gamma mode
				GmaChannel = DDCBuffer[4] & 0x03 ; // gamma channel
				cnt = DDCBuffer[5] ; // data size
				addr = (WORD)(DDCBuffer[6] << 8 );
				addr += DDCBuffer[7]; // start addr-hi, lo
				//msRegs[0x5004]=0x55;
				//if(GmaMode == 0)
				//{
				//WordAddr = BGammaTblAddr + GmaChannel*GammaTblSize + addr;
				//if(cnt == 40)
				//CheckSum_addr=BGammaCheckSumStartAddr+GmaChannel*2;
				//else if(cnt == 36)//Hans120316
				//CheckSum_addr=BGammaCheckSumStartAddr+GmaChannel*2+1;
				//}
				//if(GmaMode == 1)
				//{
				//WordAddr = BGammaTblAddr1 + GmaChannel*GammaTblSize + addr;
				//u16ChkSum_Addr = BGammaCheckSumStartAddr10+GmaChannel*2;
				//}
				WordAddr = BGammaTblAddr + GmaChannel * GammaTblSize + addr;
				for(j = 0; j < cnt; j++)
				{
					Sum ^=	DDCBuffer[8 + j] ;
					NVRam_WriteByte(WordAddr + j, DDCBuffer[8 + j]);
				}
				//NVRam_WriteTbl(WordAddr, &DDCBuffer[8], cnt);
				g_CheckSumResult ^= Sum;
				//NVRam_WriteByte(u16ChkSum_Addr, g_CheckSumResult);
			}
			break;
			case MS_LoadColorMode :
			{
				LoadDeltaEColorMode(MAIN_WINDOW, AdobeRGB_MODE, TRUE);
			}
			break;
			#endif
			case MS_LoadPostGamma :
			{
				LoadPostGamma(GammaTblSize);
			}
			break;
			case MS_WR_ColorMatrix :
			{
				BYTE  cnt, type, i;
				cnt = DDCBuffer[4];
				type = DDCBuffer[3];
				g_CheckSumResult = 0;
				for(i = 0 ; i < 18 ; i++)
				{
					//tAllFGamma3x3Matrix[type][i] = DDCBuffer[5+i];
					g_CS_Setting[type].CM[i] = DDCBuffer[5 + i];
					g_CheckSumResult ^= DDCBuffer[5 + i];
					NVRam_WriteByte( (RM_COLORSPACE_TRANS_BASEADDR + i) + (sizeof(CSTransferSettingType)*type), g_CS_Setting[type].CM[i]);
				}
				//if(type)
				//	  NVRam_WriteByte(RM_COLORSPACE_TRANS_ChkSum_ADDR+1, g_CheckSumResult);
				//else
				//	  NVRam_WriteByte(RM_COLORSPACE_TRANS_ChkSum_ADDR, g_CheckSumResult);
			}
			break;
			case MS_Read_ACK :
			{
				DDCBuffer[0] = 0x81;
				DDCBuffer[1] =  g_CheckSumResult;
				g_CheckSumResult = 0;
				return 1;
			}
			break;
			case MS_WR_BLOCK :
			{
				bToolWriteGamma = DDCBuffer[3] ;
			}
			break;
		}
	}
	#endif
	else if (CommandCode == GetTimingRequest)
		// 1-9
	{
		DDCBuffer[0] = 0x06;
		DDCBuffer[1] = 0x4E;
		DDCBuffer[2] = SyncPolarity(SrcFlags);
		if (UnsupportedModeFlag)
			DDCBuffer[2] |= 0x80;
		if (!InputTimingStableFlag)
			DDCBuffer[2] |= 0x40;
		WordValue = HFreq(SrcHPeriod) * 10;
		DDCBuffer[3] = WordValue >> 8;
		DDCBuffer[4] = WordValue & 0x00FF;
		WordValue = VFreq(WordValue, SrcVTotal);
		DDCBuffer[5] = WordValue >> 8;
		DDCBuffer[6] = WordValue & 0x00FF;
		return 6;
	}
	if (CommandCode == GETVCPFeature || CommandCode == GETPagedVCP)
	{
		SIORxBuffer[0] = DDCBuffer[3];//CmdByte  0xE1
		SIORxBuffer[1] = DDCBuffer[4];//ExtByte	eg:0x11->ECO Mode
		SIORxBuffer[2] = DDCBuffer[5];
		SIORxBuffer[3] = DDCBuffer[6];
		SIORxBuffer[4] = DDCBuffer[7];
		SIORxBuffer[5] = DDCBuffer[8];
		SIORxBuffer[6] = DDCBuffer[9];
		SIORxBuffer[7] = DDCBuffer[10];
	}
	else if(CommandCode == SETVCPFeature)
	{
		//For I-Menu
		//S-6Ea-51a-PktLena-Pre1Bytea-Pre2Bytea-CmdBytea-ExtBytea-DATA1a-DATA2a-CHKa-P
		#ifdef UseVGACableReadWriteAllPortsEDID
		#if 1  ///yuanzhi 20100428_1 for 单口烧录不通问题.
		if((DDCBuffer[2] == 0xFE && DDCBuffer[3] == 0xEF)
		        || ((DDCBuffer[3] == 0xE1) && (DDCBuffer[4] == 0xA2) && (DDCBuffer[5] == 0x01))
		  )// && DDCBuffer[4]==0x20)
		#else
		if(DDCBuffer[2] == 0xFE && DDCBuffer[3] == 0xEF) // && DDCBuffer[4]==0x20)
		#endif
		{
			;
		}
		else
		#endif
		{
			SIORxBuffer[0] = DDCBuffer[3];//CmdByte  0xE1
			SIORxBuffer[1] = DDCBuffer[4];//ExtByte	eg:0x11->ECO Mode
			SIORxBuffer[2] = DDCBuffer[5];//DATA1	Value High
			SIORxBuffer[3] = DDCBuffer[6];//DATA2	Value Low
			SIORxBuffer[4] = DDCBuffer[7];
			SIORxBuffer[5] = DDCBuffer[8];
			SIORxBuffer[6] = DDCBuffer[9];
			SIORxBuffer[7] = DDCBuffer[10];
		}
	}
	//111----------------------------------------------------------End
	//GetValue------------------------------------------------------Start
	if (CommandCode == GETVCPFeature || CommandCode == GETPagedVCP)
	{
		//Initial-----------------------Start
		if (CommandCode == GETVCPFeature)
		{
			if(CPCode == TPV_App_Command)
			{
				DDCBuffer[0] = 0x88;
				DDCBuffer[1] = 0x02;
				DDCBuffer[2] = 0x00;
				DDCBuffer[3] = IMenu_Application;
				//DDCBuffer[4] = SIORxBuffer[1];//ExtByte
			}
			#ifdef UseVGACableReadWriteAllPortsEDID
			else if((CPCode == 0xFE) && (DDCBuffer[3] == 0xEF))
			{
				;
			}
			#endif
			else
			{
				DDCBuffer[0] = 0x88;
				DDCBuffer[1] = 0x02;
				DDCBuffer[2] = 0x00;
				DDCBuffer[3] = CPCode;
				DDCBuffer[4] = 0x01;
				ValueH = 0x00;
				ValueL = 0xFF;
				RetValueH = 0x00;
				TPValue = 0x01;
			}
		}
		else
		{
			DDCBuffer[0] = 0x89;
			DDCBuffer[1] = 0xC7;
			DDCBuffer[2] = 0x00;
			DDCBuffer[3] = PageValue;
			DDCBuffer[4] = CPCode;
			DDCBuffer[5] = 0x01;
			ValueH = 0x00;
			ValueL = 0xFF;
			RetValueH = 0x00;
			TPValue = 0x01;
		}
		//Initial-----------------------End
		//Setting---------------------------------Start
		if (CPCode == NewControl && PageValue == 0)
		{
			/*if(DDCCINewControlFlag)
			RetValueL = 2;
			else*/
			RetValueL = 1;
			ValueL = 2;
		}
		#if ENABLE_HDMI_DRR_MCCS
		else if(CPCode == VCP_FREESYNC_MODE)
		{
			TPValue = 0x00;
			ValueH = 0x00;
			ValueL = 0x01;
			RetValueH = 0x00;
			#if ENABLE_FREESYNC
			if(UserprefFreeSyncMode)
			{
				RetValueL = 1;
			}
			else
			#endif
			{
				RetValueL = 0; // USER_PREF_FREESYNCMODE;
			}
		}
		#endif
		else if (CPCode == ALL_Reset && PageValue == 0)
		{
			RetValueL = 0;
			ValueL = 1;
		}
		else if(CPCode == BriCon_Reset && PageValue == 0)   // 2-2
		{
			RetValueL = 0;
			ValueL = 1;
		}
		else if (CPCode == Geometry_Reset && PageValue == 0 && SrcInputType < Input_Digital)
			// 2-2
		{
			RetValueL = 0;
			ValueL = 1;
		}
		else if (CPCode == Color_Reset && PageValue == 0)
			// 2-3
		{
			RetValueL = 0;
			ValueL = 1;
		}
		else if( CPCode == ADJ_Clock && PageValue == 0 && CURRENT_INPUT_IS_VGA())//SrcInputType < Input_Digital )
			// 2-4
		{
			RetValueH = 0;
			RetValueL = GetClockValue();
			ValueH = 0;
			ValueL = 100;
			TPValue = 0x00;
		}
		else if (CPCode == ADJ_Brightness && PageValue == 0)
			// 2-5
		{
			ValueL = MaxBrightnessValue - MinBrightnessValue;
			RetValueL = UserPrefBrightness - MinBrightnessValue;
			TPValue = 0x00;
		}
		else if (CPCode == ADJ_Contrast && PageValue == 0)
			// 2-6
		{
			ValueL = ((WORD)(MaxContrastValue - MinContrastValue) * 100) / (MaxContrastValue - MinContrastValue);
			RetValueL = ((WORD)(UserPrefContrast - MinContrastValue) * 100) / (MaxContrastValue - MinContrastValue); //Benz 2007.4.15   20:32:03100;// UserPrefContrast - MinContrastValue;
			TPValue = 0x00;
		}
		else if (CPCode == Select_Color_Preset && PageValue == 0)
			// 2-7
		{
			//Benz 2007.4.15   12:09:45
			ValueL = 0x0D; //0x0B
			if (UserPrefColorTemp == CTEMP_6500K)
				RetValueL = 0x05;
			#if CT_sRGB_ENABLE
			else if (UserPrefColorTemp == CTEMP_SRGB)
				RetValueL = 0x01;
			#endif
			#if CT_7500K_ENABLE
			else if (UserPrefColorTemp == CTEMP_Normal)
				RetValueL = 0x04;
			#endif
			else if (UserPrefColorTemp == CTEMP_9300K)
				RetValueL = 0x08;
			else if (UserPrefColorTemp == CTEMP_USER)
				RetValueL = 0x0B;
			TPValue = 0x00;
		}
		#if ColorTool_Clear_Time
		else if(CPCode == GetUserTime && PageValue == 0)
		{
			#if  Show_BackLightTimeValue
			TPValue = 0x00;
			ValueH		= BlacklitTime_H;
			ValueL		= 0;
			RetValueH	= BlacklitTime_M;
			RetValueL	= BlacklitTime_S;
			#endif
		}
		//*/
		else if(CPCode == CleanUsedTime && PageValue == 0)
		{
			if (PowerOnFlag)
				Set_DDCCResetTimeFlag();
		}
		else if(CPCode == AutoColorDDCCI && PageValue == 0)
		{
			if(SrcInputType == Input_VGA)
			{
				Set_DDCCIAutoColorFlag();
			}
		}
		#endif
		else if ((CPCode == ADJ_Red_Gain) && PageValue == 0)
			// 2-8
		{
			ValueL = 100;//(MaxColorValue - MinColorValue);
			#if 0
			if (UserPrefColorTemp == CTEMP_SRGB)
				RetValueL = (WORD)(UserPrefRedColorSRGB - MinColorValue) * 100 / MaxColorValue;
			else if (UserPrefColorTemp == CTEMP_USER)
				RetValueL = (WORD)(UserPrefRedColorUser - MinColorValue) * 100 / MaxColorValue;
			else if (UserPrefColorTemp == CTEMP_6500K)
				RetValueL = (WORD)(UserPrefRedColor6500K - MinColorValue) * 100 / MaxColorValue;
			else if (UserPrefColorTemp == CTEMP_Normal)
				RetValueL = (WORD)(UserPrefRedColorNormal - MinColorValue) * 100 / MaxColorValue;
			else if (UserPrefColorTemp == CTEMP_9300K)
				RetValueL = (WORD)(UserPrefRedColor9300K - MinColorValue) * 100 / MaxColorValue;
			#else
			RetValueL = GetRedColorValue();
			#endif
			TPValue = 0x00;
		}
		else if ((CPCode == ADJ_Green_Gain) && PageValue == 0)
			// 2-9
		{
			ValueL = 100;//(MaxColorValue - MinColorValue);
			#if 0
			if (UserPrefColorTemp == CTEMP_SRGB)
				RetValueL = (WORD)(UserPrefGreenColorSRGB - MinColorValue) * 100 / MaxColorValue;
			else if (UserPrefColorTemp == CTEMP_USER)
				RetValueL = (WORD)(UserPrefGreenColorUser - MinColorValue) * 100 / MaxColorValue;
			else if (UserPrefColorTemp == CTEMP_6500K)
				RetValueL = (WORD)(UserPrefGreenColor6500K - MinColorValue) * 100 / MaxColorValue;
			else if (UserPrefColorTemp == CTEMP_Normal)
				RetValueL = (WORD)(UserPrefGreenColorNormal - MinColorValue) * 100 / MaxColorValue;
			else if (UserPrefColorTemp == CTEMP_9300K)
				RetValueL = (WORD)(UserPrefGreenColor9300K - MinColorValue) * 100 / MaxColorValue;
			#else
			RetValueL = GetGreenColorValue();
			#endif
			TPValue = 0x00;
		}
		else if ((CPCode == ADJ_Blue_Gain) && PageValue == 0)
			// 2-10
		{
			ValueL = 100;//(MaxColorValue - MinColorValue);
			#if 0
			if (UserPrefColorTemp == CTEMP_SRGB)
				RetValueL = (WORD)(UserPrefBlueColorSRGB - MinColorValue) * 100 / MaxColorValue;
			else if (UserPrefColorTemp == CTEMP_USER)
				RetValueL = (WORD)(UserPrefBlueColorUser - MinColorValue) * 100 / MaxColorValue;
			else if (UserPrefColorTemp == CTEMP_6500K)
				RetValueL = (WORD)(UserPrefBlueColor6500K - MinColorValue) * 100 / MaxColorValue;
			else if (UserPrefColorTemp == CTEMP_Normal)
				RetValueL = (WORD)(UserPrefBlueColorNormal - MinColorValue) * 100 / MaxColorValue;
			else if (UserPrefColorTemp == CTEMP_9300K)
				RetValueL = (WORD)(UserPrefBlueColor9300K - MinColorValue) * 100 / MaxColorValue;
			#else
			RetValueL = GetBlueColorValue();
			#endif
			TPValue = 0x00;
		}
		else if( CPCode == Auto_Setup && PageValue == 0 && CURRENT_INPUT_IS_VGA())//SrcInputType < Input_Digital )
			// 2-11
		{
			RetValueL = 0;
			ValueL = 1;
		}
		#if !ColorTool_Clear_Time
		else if( CPCode == Auto_Color && PageValue == 0 && CURRENT_INPUT_IS_VGA())//SrcInputType < Input_Digital )
			// 2-11
		{
			RetValueL = 0;
			ValueL = 1;
		}
		#endif
		else if( CPCode == ADJ_HorizontalPos && PageValue == 0 && CURRENT_INPUT_IS_VGA())//SrcInputType < Input_Digital )
			// 2-12
		{
			//110527 Modify
			ValueH = 0;
			ValueL = 100;
			RetValueH = 0;
			RetValueL = GetHPositionValue();
			TPValue = 0x00;
		}
		else if (CPCode == ADJ_VerticalPos && PageValue == 0 && SrcInputType < Input_Digital)
			// 2-13
		{
			#if 0
			ValueH = (MaxVStart - MinVStart) >> 8;
			ValueL = (MaxVStart - MinVStart) & 0x00FF;
			RetValueH = (UserPrefVStart - MinVStart) >> 8;
			RetValueL = (UserPrefVStart - MinVStart) & 0x00FF;
			TPValue = 0x00;
			#else
			RetValueH = 0x00;
			RetValueL = GetVPositionValue();
			ValueH = 0x0;
			ValueL = 100;
			TPValue = 0x00;
			#endif
		}
		else if( CPCode == ADJ_Phase && PageValue == 0 && CURRENT_INPUT_IS_VGA())//SrcInputType < Input_Digital )
			// 2-14
		{
			RetValueH = 0x00;
			RetValueL = GetFocusValue();
			ValueH = 0x0;
			ValueL = 100;
			TPValue = 0x00;
		}
		else if (CPCode == Select_InputSource)
		{
			ValueH = 0x00;
			ValueL = 0x04;
			if(CURRENT_INPUT_IS_VGA())//( SrcInputType < Input_Digital ) //if (SrcInputType != Input_Digital)
				RetValueL = 0x01;
			else
				RetValueH = 0x03;
			TPValue = 0x00;
		}
		#if AudioFunc
		else if (CPCode == ADJ_SpeakerVolume && PageValue == 0)
		{
			ValueH = 0;
			ValueL = 100;
			RetValueL = UserPrefVolume;
			RetValueH = 0;
			TPValue = 0x00;
		}
		else if (CPCode == AudioMute && PageValue == 0)
		{
			ValueH = 0;
			ValueL = 100;
			RetValueL = UserPrefMuteState ? 1 : 2;
			RetValueH = 0;
			TPValue = 0x00;
		}
		#endif
		#if ENABLE_FACTORY_BLACKLEVEL  ||   ENABLE_DDCCI_BLACKLEVEL
		else if (CPCode == ADJ_Red_Blacklevel && PageValue == 0)
		{
			ValueH = 0x00;
			ValueL = 100;
			RetValueL = UserprefRedBlackLevel;
			TPValue = 0;
		}
		else if (CPCode == ADJ_Green_Blacklevel && PageValue == 0)
		{
			ValueH = 0x00;
			ValueL = 100;
			RetValueL = UserprefGreenBlackLevel;
			TPValue = 0;
		}
		else if (CPCode == ADJ_Blue_Blacklevel && PageValue == 0)
		{
			ValueH = 0x00;
			ValueL = 100;
			RetValueL = UserprefBlueBlackLevel;
			TPValue = 0;
		}
		#endif
		else if (CPCode == H_Frequency && PageValue == 0)
		{
			ValueH = 0xFF;
			ValueL = 0xFF;
			WordValue = HFreq(SrcHPeriod) * 10;
			RetValueH = WordValue >> 8;
			RetValueL = WordValue & 0x00ff;
			TPValue = 0x01;
		}
		else if (CPCode == V_Frequency && PageValue == 0)
		{
			ValueH = 0xFF;
			ValueL = 0xFF;
			WordValue = HFreq(SrcHPeriod) * 10;
			WordValue = VFreq(WordValue, SrcVTotal);
			RetValueH = WordValue >> 8;
			RetValueL = WordValue & 0x00ff;
			TPValue = 0x01;
		}
		else if (CPCode == FlatPanellayout)
		{
			ValueL = 8;
			RetValueL = 1;
		}
		else if (CPCode == MonitorType && PageValue == 0)
			// 2-20
		{
			RetValueH = 0;
			RetValueL = 3;
			ValueH = 0x00;
			ValueL = 0x08;
			TPValue = 0x00;
		}
		else if (CPCode == DisplayControlType)
			// Jeff add it in 2004?~7る13ら?Uと 04:46:32
		{
			ValueH = 0xFF;
			ValueL = 0x16;
			RetValueH = 0;
			RetValueL = 5; // Mean Mstar
		}
		else if (CPCode == FWLevel)
		{
			ValueH = 0xFF;
			ValueL = 0xFF;
			RetValueL = Version;
			RetValueH = Version >> 16;
		}
		#if Enable_DDCCI_OSDEnable_EN
		else if (CPCode == OSDEnable)
		{
			ValueH = 0x00;
			ValueL = 0x02;
			if(DDCOSDDisEnableFlag)
				RetValueL = 1; //F/W Version
			else
				RetValueL = 2; //F/W Version
		}
		#endif
		else if (CPCode == ADJ_Language && PageValue == 0)
			// 2-17
		{
			#if 1
			ValueL = LANG_Nums;
			if (UserPrefLanguage == LANG_Spanish)
				RetValueL = LanSpanishCode;
			else if (UserPrefLanguage == LANG_France)
				RetValueL = LanFrenchCode;
			else if (UserPrefLanguage == LANG_German)
				RetValueL = LanGermanCode;
			else if (UserPrefLanguage == LANG_Italian)
				RetValueL = LanItalianCode;
			else if (UserPrefLanguage == LANG_Russia)
				RetValueL = LanRussianCode;
			else if (UserPrefLanguage == LANG_Swedish)
				RetValueL = LanSwedishCode;
			else if (UserPrefLanguage == LANG_Polish)
				RetValueL = LanPolishCode;
			else if (UserPrefLanguage == LANG_Czech)
				RetValueL = LanCzechCode;
			else if (UserPrefLanguage == LANG_Portugues)
				RetValueL = LanPortugueseCode_Brazil;
			else if (UserPrefLanguage == LANG_SChina)
				RetValueL = LanSChineseCode;
			else if (UserPrefLanguage == LANG_TChina)
				RetValueL = LanTChineseCode;
			else if (UserPrefLanguage == LANG_Korea)
				RetValueL = LanKoreanCode;
			else if (UserPrefLanguage == LANG_Japan )
				RetValueL = LanJapaneseCode;
			else if (UserPrefLanguage == LanDutchCode)	//120105 Modify
				RetValueL = LANG_Dutch;
			else if (UserPrefLanguage == LANG_Finnish)	//120105 Modify
				RetValueL = LanFinnishCode;
			else if (UserPrefLanguage == LANG_English)
				RetValueL = LanEnglistCode;
			RetValueH = 0x00;
			#endif
		}
		#if 0//ENABLE_FREESYNC
		else if (CPCode == VCP_FREESYNC_MODE)
		{
			//ValueH = 0x00;
			//ValueL = VCP_FREESYNC_MODE_MAX_VALUE;
			ValueH = 0x00;
			ValueL = VCP_FREESYNC_MODE_ENABLE;
			RetValueH = 0x00;
			RetValueL = VCP_FREESYNC_MODE_ENABLE;
		}
		#endif
		else if (CPCode == VCPVersion && PageValue == 0)
		{
			RetValueL = 1;
			RetValueH = 2;
			ValueH = 0xFF;
			ValueL = 0xFF;
		}
		else if (CPCode == 0xFE)
		{
			if (SIORxBuffer[0] == 'R')
			{
				if (SIORxBuffer[1] == 'M' && SIORxBuffer[2] == 'N' && SIORxBuffer[3] == '0')
				{
					TPValue = SIORxBuffer[3];
					ValueH = SIORxBuffer[4];
					if(SIORxBuffer[4] >= '0' && SIORxBuffer[4] <= '3')
					{
						BYTE i;
						i = SIORxBuffer[4] - '0';
						ValueL = MODEL_TYPE[3 * i];
						RetValueH = MODEL_TYPE[3 * i + 1];
						RetValueL = MODEL_TYPE[3 * i + 2];
					}
				}
				#ifdef ReduceDDC
				else if((SIORxBuffer[1] == 'E' && SIORxBuffer[2] == 'D' && SIORxBuffer[3] == 'I')) //'R'	'E'	'D'	'I'	'D'	'W'	'A'	'Y'
				#ifdef OnlyVGAEDIDInFlash
				{
					//'R'	'E'	'D'	'I'	'D'	'V'	'G'	'A'
					TPValue = 'I';
					ValueH = 'D';
					ValueL = 'V';
					RetValueH = 'G';
					RetValueL = 'A';
				}
				#else
				{
					//'R'	'E'	'D'	'I'	'D'	'F'	'L'	'H'
					TPValue = 'I';
					ValueH = 'D';
					ValueL = 'F';
					RetValueH = 'L';
					RetValueL = 'H';
				}
				#endif
				#endif
				#if HDCPKEY_IN_Flash
				else if((SIORxBuffer[1] == 'H' && SIORxBuffer[2] == 'D' && SIORxBuffer[3] == 'C'))
				{
					ValueH = TCRCvalue / 256;
					ValueL = TCRCvalue % 256;
					RetValueH = 0x88;
					RetValueL = 0x02;
					Clr_WriteHDCPcodeFlag();
				}
				#endif
			}
			#ifdef	UseVGACableReadWriteAllPortsEDID
			else if(DDCBuffer[3] == 0xEF) //else if(SIORxBuffer[0]==0xEF)
			{
				BYTE i, Length;
				WORD Addr;
				Length = DDCBuffer[7];
				Addr = (DDCBuffer[5] << 8) + DDCBuffer[6];
				if((DDCBuffer[4] >= VGA1 && DDCBuffer[4] <= MHL_HDMI2) || (DDCBuffer[4] >= EEPROM && DDCBuffer[4] <= PanelSettingDevice))	//130614 xiandi
				{
					ReadDevice(DDCBuffer[4],  Addr, ( BYTE* )&SIORxBuffer, Length); //Read EDID or HDCP KEY
					for(i = 0; i < Length; i++)
					{
						DDCBuffer[i + 1] = SIORxBuffer[i];
					}
				}
				else
				{
					;
				}
				DDCBuffer[0] = 0x80 + Length;
				return Length;
			}
			#endif
			#if HDCPKEY_IN_Flash
			else if(SIORxBuffer[0] == 0xE1 &&  SIORxBuffer[1] == 0xE2 &&  SIORxBuffer[2] == 0x00 && SIORxBuffer[3] == 0x00)
			{
				ValueH = TCRCvalue / 256;
				ValueL = TCRCvalue % 256;
				RetValueH = 0x00;
				RetValueL = 0x00;
				Clr_WriteHDCPcodeFlag();
			}
			#endif
		}
		/***********************************************Zhifeng.Wu***********************************************/
#define	I_Menu_Command	SIORxBuffer[1]
		//For TPV Application
		else if (CPCode == TPV_App_Command && PageValue == 0)
		{
			if(SIORxBuffer[0] == IMenu_Application) //For AOC I-Menu Application
			{
				//For Other Luminance Menu
				if(I_Menu_Command == ECO_Mode)
				{
					RetValueH = 0;
					RetValueL = UserPrefECOMode;
					ValueH = 0;
					ValueL = ECO_Nums - 1;
				}
				#if Enable_Gamma
				else if(I_Menu_Command == Gamma)
				{
					RetValueH = 0;
					RetValueL = UserPrefGamaMode;
					ValueH = 0;
					ValueL = GAMA_Nums - 1;
				}
				#endif
				else if(I_Menu_Command == DCR)
				{
					RetValueH = 0;
					RetValueL = UserPrefDcrMode;
					ValueH = 0;
					ValueL = 1;
				}
				else if(I_Menu_Command == PB_Hue)
				{
				}
				else if(I_Menu_Command == PB_Saturation)
				{
				}
			}
		}
#undef	I_Menu_Command
		/*******************************************************************************************************/
		else if ( CPCode == PowerMode )
		{
			ValueL = 4;
			if ( !PowerOnFlag )
			{
				RetValueL = 4;
			}
			else if ( PowerSavingFlag )
			{
				RetValueL = 2;
			}
			else
			{
				RetValueL = 1;
			}
		}
		else
		{
			DDCBuffer[2] = 0x01;
			RetValueL = 0x00;
			ValueH = 0xFF;
			ValueL = 0xFF;
		}
		//Setting---------------------------------End
		//Transmission----------------------------Start
		if (CommandCode == GETVCPFeature)
		{
			if(CPCode == TPV_App_Command)
			{
				DDCBuffer[5] = ValueH;
				DDCBuffer[6] = ValueL;
				DDCBuffer[7] = RetValueH;
				DDCBuffer[8] = RetValueL;
			}
			else
			{
				DDCBuffer[4] = TPValue;
				DDCBuffer[5] = ValueH;
				DDCBuffer[6] = ValueL;
				DDCBuffer[7] = RetValueH;
				DDCBuffer[8] = RetValueL;
			}
			return 8;
		}
		else
		{
			DDCBuffer[5] = TPValue;
			DDCBuffer[6] = ValueH;
			DDCBuffer[7] = ValueL;
			DDCBuffer[8] = RetValueH;
			DDCBuffer[9] = RetValueL;
			return 9;
		}
		//Transmission----------------------------End
	}
	//GetValue------------------------------------------------------Start
	//SetValue------------------------------------------------------Start
	else if (CommandCode == SETVCPFeature || CommandCode == SETPagedVCP)
	{
		DDCBuffer[2] = 0x00; // Result Code
		ValueH = 0x00;
		ValueL = 0xFF;
		TPValue = 0x01;
		if (CPCode == NewControl && PageValue == 0)
		{
			//Clr_DDCCINewControlFlag();
			ValueL = 2;
		}
		else if (CPCode == ALL_Reset && PageValue == 0)
			// 3-1
		{
			if (WordValue != 0)
			{
				Osd_Hide();//petit 20131024 only for I-Menu reset.
				ResetAllSetting();
				// wait for checking
				//msWriteByte(BCR, 0x80);
				//msWriteByte(BCG, 0x80);
				//msWriteByte(BCB, 0x80);
			}
			ValueL = 1;
		}
		else if(CPCode == BriCon_Reset && PageValue == 0)  // 3-2
		{
			if(WordValue != 0 )
			{
				UserPrefBrightness = DefBrightness;
				UserPrefContrast = DefContrast;
				mStar_AdjustBrightness( UserPrefBrightness);
				mStar_AdjustContrast(UserPrefContrast);	//120413 Modify
			}
			ValueL = 1;
		}
		else if( CPCode == Geometry_Reset && PageValue == 0 && INPUT_IS_VGA(rxInputPort))   //else if (CPCode == Geometry_Reset && PageValue == 0 && rxInputPort != Input_Digital)
		{
			if( WordValue != 0 && CURRENT_INPUT_IS_VGA())//SrcInputType < Input_Digital )   //if (WordValue != 0 && SrcInputType != Input_Digital)
				ResetGeometry();
			ValueL = 1;
			TPValue = 0x00;
		}
		else if (CPCode == Color_Reset && PageValue == 0)
			// 3-3
		{
			UserPrefRedColorUser = DefRedColor;
			UserPrefGreenColorUser = DefGreenColor;
			UserPrefBlueColorUser = DefBlueColor;
			#if ENABLE_FACTORY_BLACKLEVEL  ||   ENABLE_DDCCI_BLACKLEVEL
			UserprefRedBlackLevel = DefRedBlackLevel;
			UserprefGreenBlackLevel = DefGreenBlackLevel;
			UserprefBlueBlackLevel = DefBlueBlackLevel;
			mStar_AdjustUserPrefBlacklevel(UserprefRedBlackLevel, UserprefGreenBlackLevel, UserprefBlueBlackLevel);
			#endif
			UserPrefColorTemp = CTEMP_Warm1; //CTEMP_9300K 20051115 wmz
			if (WordValue != 0)
				SetColorTemp();//Setcolortemp();
			//Benz 2007.4.15   19:31:44SetColor();
			ValueL = 1;
		}
		else if( CPCode == ADJ_Clock && PageValue == 0 && CURRENT_INPUT_IS_VGA())//SrcInputType < Input_Digital )
			// 3-4
		{
			//if( SrcInputType < Input_Digital ) //if (SrcInputType != Input_Digital)
			{
				UserPrefHTotal = ((WordValue * (MaxClock - MinClock) + 50) / 0x64 + MinClock);
				drvADC_AdjustHTotal( UserPrefHTotal );
				#if USEFLASH //Modify Request TPV FW Sting  20170110
				UserPref_EnableFlashSaveBit(bFlashSaveModeBit);
				#else
				NVRam_WriteByte(nvrModeAddr(HTotal), UserPrefHTotal);
				#endif
			}
			TPValue = 0x00;
		}
		else if (CPCode == ADJ_Brightness && PageValue == 0)
			// 3-5
		{
			#if CT_sRGB_ENABLE
			if((UserPrefECOMode == ECO_Standard) && (UserPrefColorTemp != CTEMP_SRGB) && (!UserPrefDcrMode))	//120609 Modify
			#else
			if((UserPrefECOMode == ECO_Standard) && (!UserPrefDcrMode))	//120609 Modify
			#endif
			{
				UserPrefBrightness = RetValueL + MinBrightnessValue;
				mStar_AdjustBrightness(UserPrefBrightness);
			}
			ValueL = MaxBrightnessValue - MinBrightnessValue;
			TPValue = 0x00;
		}
		else if (CPCode == ADJ_Contrast && PageValue == 0)
			// 3-6
		{
			//Osd_Hide();
			#if CT_sRGB_ENABLE
			if((UserPrefECOMode == ECO_Standard) && (UserPrefColorTemp != CTEMP_SRGB) && (!UserPrefDcrMode))	//120609 Modify
			#else
			if((UserPrefECOMode == ECO_Standard) && (!UserPrefDcrMode))	//120609 Modify
			#endif
			{
				if (RetValueL <= (MaxContrastValue - MinContrastValue))
				{
					UserPrefContrast = (WORD)(RetValueL * (MaxContrastValue - MinContrastValue)) / 100 + MinContrastValue;
					mStar_AdjustContrast(UserPrefContrast);
				}
			}
			ValueL = 100;
			TPValue = 0x00;
		}
		else if (CPCode == Select_Color_Preset && PageValue == 0)
			// 3-7
		{
			if (RetValueL == 0x05)
				UserPrefColorTemp = CTEMP_6500K;
			#if CT_sRGB_ENABLE
			else if (RetValueL == 0x01)
				UserPrefColorTemp = CTEMP_SRGB;
			#endif
			#if CT_7500K_ENABLE
			else if (RetValueL == 0x04)
				UserPrefColorTemp = CTEMP_Normal;
			#endif
			else if (RetValueL == 0x08)
				UserPrefColorTemp = CTEMP_9300K;
			else if (RetValueL == 0x0B)
				UserPrefColorTemp = CTEMP_USER;
			#if CT_sRGB_ENABLE
			if( UserPrefColorTemp == CTEMP_SRGB )	//121220 Modify
			{
				if( UserPrefECOMode != ECO_Standard )
				{
					UserPrefECOMode = ECO_Standard;
				}
				#if Enable_Gamma
				if( UserPrefGamaMode != GAMA1 )
				{
					UserPrefGamaMode = GAMA1;
					#if Enable_Gamma
					mStar_SetupGamma( GAMA1 );
					#endif
				}
				#endif
				if(UserPrefDcrMode)
				{
					UserPrefDcrMode = 0;
					SetECO();
					msDCROnOff(UserPrefDcrMode, MAIN_WINDOW);
				}
			}
			#endif
			SetColorTemp();//Setcolortemp();
			ValueL = 0x0D; //0x0B
			TPValue = 0x00;
		}
		else if (CPCode == ADJ_Red_Gain && PageValue == 0)
			// 3-8
		{
			if (UserPrefColorTemp == CTEMP_USER)
			{
				UserPrefRedColorUser = UserPrefRedColor = (WORD)RetValueL * ( MaxColorValue - MinColorValue ) / 100 + MinColorValue;		//120215 Modify
				mStar_AdjustRedColor(UserPrefRedColor, UserPrefContrast);															//120215 Modify
			}
			ValueL = 100;//(MaxColorValue - MinColorValue);
			TPValue = 0x00;
		}
		else if (CPCode == ADJ_Green_Gain && PageValue == 0)
			// 3-9
		{
			if (UserPrefColorTemp == CTEMP_USER)
			{
				UserPrefGreenColorUser = UserPrefGreenColor = (WORD)RetValueL * ( MaxColorValue - MinColorValue ) / 100 + MinColorValue;		//120215 Modify
				mStar_AdjustGreenColor(UserPrefGreenColor, UserPrefContrast);																//120215 Modify
			}
			ValueL = 100;//(MaxColorValue - MinColorValue);
			TPValue = 0x00;
		}
		else if (CPCode == ADJ_Blue_Gain && PageValue == 0)
			// 3-10
		{
			if (UserPrefColorTemp == CTEMP_USER)
			{
				UserPrefBlueColorUser = UserPrefBlueColor = (WORD)RetValueL * ( MaxColorValue - MinColorValue ) / 100 + MinColorValue;		//120215 Modify
				mStar_AdjustBlueColor(UserPrefBlueColor, UserPrefContrast);																//120215 Modify
			}
			ValueL = 100;//(MaxColorValue - MinColorValue);
			TPValue = 0x00;
		}
		else if( CPCode == Auto_Setup && PageValue == 0 && CURRENT_INPUT_IS_VGA())//SrcInputType < Input_Digital )
			// 3-11
		{
			if( WordValue != 0 )   //if (WordValue != 0 && SrcInputType != Input_Digital)
				AutoConfig();
			ValueL = 1;
		}
		else if( CPCode == Auto_Color && PageValue == 0 && CURRENT_INPUT_IS_VGA())//SrcInputType < Input_Digital )
			// 3-12
		{
			if( WordValue != 0 )   //if (WordValue != 0 && SrcInputType != Input_Digital)
				mStar_AutoColor();
			#if Show_BackLightTimeValue
			BlacklitTime_S = 0;
			BlacklitTime_M = 0;
			BlacklitTime_H = 0;
			MonitorBackLightTime_S = BlacklitTime_S;
			MonitorBackLightTime_M = BlacklitTime_M;
			MonitorBackLightTime_H = BlacklitTime_H;
			#if USEFLASH
			//SaveMonitorSetting2();
			UserPref_EnableFlashSaveBit( bFlashForceSaveMonitor2Bit );
			//UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit );
			#else
			NVRam_WriteByte(NVRAM_ADDR_MointorMember(MonitorFlag), MonitorFlags);
			NVRam_WriteByte(nvrMonitorAddr(BacklighttimeS), MonitorBackLightTime_S);
			NVRam_WriteByte(nvrMonitorAddr(BacklighttimeM), MonitorBackLightTime_M);
			NVRam_WriteByte(nvrMonitorAddr(BacklighttimeH), MonitorBackLightTime_H);
			#endif
			#endif
			ValueL = 1;
		}
		else if( CPCode == ADJ_HorizontalPos && PageValue == 0 && CURRENT_INPUT_IS_VGA())//SrcInputType < Input_Digital )
			// 3-12
		{
			//if( SrcInputType < Input_Digital ) //if (SrcInputType != Input_Digital)
			{
				UserPrefHStart = (WORD)(WordValue) * (MaxHStart - MinHStart) / 100 + MinHStart;
				mStar_AdjustHPosition(UserPrefHStart);
				#if USEFLASH //Modify Request TPV FW Sting  20170110
				UserPref_EnableFlashSaveBit(bFlashSaveModeBit);
				#else
				NVRam_WriteByte(nvrModeAddr(HStart), UserPrefHStart);
				#endif
			}
			TPValue = 0x00;
		}
		else if( CPCode == ADJ_VerticalPos && PageValue == 0 && CURRENT_INPUT_IS_VGA())//SrcInputType < Input_Digital )
			// 3-13
		{
			UserPrefVStart = (WORD)WordValue * (MaxVStart - MinVStart) / 100 + MinVStart;
			mStar_AdjustVPosition(UserPrefVStart);
			#if USEFLASH //Modify Request TPV FW Sting
			UserPref_EnableFlashSaveBit(bFlashSaveModeBit);
			#else
			NVRam_WriteByte(nvrModeAddr(VStart), UserPrefVStart);
			#endif
			TPValue = 0x00;
		}
		else if( CPCode == ADJ_Phase && PageValue == 0 && CURRENT_INPUT_IS_VGA())//SrcInputType < Input_Digital )
			// 3-14
		{
			//if( SrcInputType < Input_Digital ) //if (SrcInputType != Input_Digital)
			{
				UserPrefPhase = WordValue * (MAX_PHASE_VALUE + 1) / 100 + 0.5;
				if(UserPrefPhase > MAX_PHASE_VALUE)
					UserPrefPhase = MAX_PHASE_VALUE;
				drvADC_SetPhaseCode( UserPrefPhase );
				#if USEFLASH //Modify Request TPV FW Sting  20170110
				UserPref_EnableFlashSaveBit(bFlashSaveModeBit);
				#else
				NVRam_WriteByte(nvrModeAddr(Phase), UserPrefPhase);
				#endif
			}
			TPValue = 0x00;
		}
		else if (CPCode == DDCCI_Settings && PageValue == 0 )
			// 3-14
		{
			if(CURRENT_INPUT_IS_VGA())//( SrcInputType < Input_Digital ) //if (SrcInputType != Input_Digital)
			{
				#if USEFLASH
				UserPref_EnableFlashSaveBit(bFlashSaveModeBit);
				#else
				SaveModeSetting();
				#endif
			}
			#if USEFLASH
			UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
			#else
			SaveMonitorSetting();
			#endif
			TPValue = 0x00;
		}
		else if (CPCode == Select_InputSource && PageValue == 0)
		{
			// Osd_Hide();
			if (RetValueL == 0x01 || RetValueL == 0x02)
			{
				#if ENABLE_VGA_INPUT
				ChangeSourceToAnalog();
				#endif
			}
			if (RetValueL == 0x03 || RetValueL == 0x04)
			{
				#if Dual
				#if INPUT_TYPE != INPUT_1A1H && INPUT_TYPE != INPUT_1A1DP
				ChangeSourceToDigital();
				#endif
				#endif
			}
			#if ENABLE_HDMI	//130821 xiandi
			if (RetValueL == 0x11)
			{
				#if Dual
				#if INPUT_TYPE == INPUT_1A1H1DP	//131031 xiandi
				ChangeSourceToDigital();
				#else
				ChangeSourceToHDMI();
				#endif
				#endif
			}
			#endif
			#if ENABLE_DP_INPUT	//130821 xiandi
			if (RetValueL == 0x0F)
			{
				ChangeSourceToDP();
			}
			#endif
			TPValue = 0x00;
		}
		#if AudioFunc
		else if (CPCode == ADJ_SpeakerVolume && PageValue == 0)
		{
			//Osd_Hide();
			UserPrefVolume = RetValueL;
			if(UserPrefMuteState)
			{
				SwitchMute(MIA_DecValue);    // UserPrefMuteState=0;
			}
			mStar_AdjustVolume(UserPrefVolume);
			TPValue = 0x00;
		}
		else if (CPCode == AudioMute && PageValue == 0)
		{
			//Osd_Hide();
			if(RetValueL == 0x01)
			{
				UserPrefMuteState = 1;
				SwitchMute(MIA_Nothing);
			}
			else if(RetValueL == 0x02)
			{
				UserPrefMuteState = 0;
				mStar_AdjustVolume(UserPrefVolume);
			}
			TPValue = 0x00;
		}
		#endif
		#if Enable_DDCCI_OSDEnable_EN
		else if(CPCode == OSDEnable && PageValue == 0)
		{
			if(RetValueL == 1)
				Set_DDCOSDDisEnableFlag();
			if(RetValueL == 2)
				Clr_DDCOSDDisEnableFlag();
			TPValue = 0x00;
		}
		#endif
		#if ENABLE_FACTORY_BLACKLEVEL  ||   ENABLE_DDCCI_BLACKLEVEL
		else if ((CPCode == ADJ_Red_Blacklevel || CPCode == ADJ_Green_Blacklevel || CPCode == ADJ_Blue_Blacklevel) && PageValue == 0)
		{
			if (CPCode == ADJ_Red_Blacklevel)
				UserprefRedBlackLevel = RetValueL;
			else if (CPCode == ADJ_Green_Blacklevel)
				UserprefGreenBlackLevel = RetValueL;
			else if (CPCode == ADJ_Blue_Blacklevel)
				UserprefBlueBlackLevel = RetValueL;
			mStar_AdjustUserPrefBlacklevel(UserprefRedBlackLevel, UserprefGreenBlackLevel, UserprefBlueBlackLevel);
			SaveMonitorSetting();
		}
		#endif
		else if (CPCode == ADJ_Language && PageValue == 0)
			// 3-17
		{
			//     UserPrefLanguage = RetValueL-1;
			#if 1
			if (RetValueL == LanSpanishCode)
			{
				UserPrefLanguage = LANG_Spanish;
			}
			else if (RetValueL == LanFrenchCode)
			{
				UserPrefLanguage = LANG_France;
			}
			else if (RetValueL == LanGermanCode)
			{
				UserPrefLanguage = LANG_German;
			}
			else if (RetValueL == LanItalianCode)
			{
				UserPrefLanguage = LANG_Italian;
			}
			else if (RetValueL == LanRussianCode)
			{
				UserPrefLanguage = LANG_Russia;
			}
			else if (RetValueL == LanSwedishCode)
			{
				UserPrefLanguage = LANG_Swedish;
			}
			else if (RetValueL == LanPolishCode)
			{
				UserPrefLanguage = LANG_Polish;
			}
			else if (RetValueL == LanCzechCode)
			{
				UserPrefLanguage = LANG_Czech;
			}
			else if (RetValueL == LanPortugueseCode_Brazil)
			{
				UserPrefLanguage = LANG_Portugues;
			}
			else if (RetValueL == LanSChineseCode)
			{
				UserPrefLanguage = LANG_SChina;
			}
			else if (RetValueL == LanTChineseCode)
			{
				UserPrefLanguage = LANG_TChina;
			}
			else if (RetValueL == LanKoreanCode)
			{
				UserPrefLanguage = LANG_Korea;
			}
			else if (RetValueL == LanJapaneseCode)
			{
				UserPrefLanguage = LANG_Japan;
			}
			else if (RetValueL == LanDutchCode)	//120105 Modify
			{
				UserPrefLanguage = LANG_Dutch;
			}
			else if (RetValueL == LanFinnishCode)	//120105 Modify
			{
				UserPrefLanguage = LANG_Finnish;
			}
			else if (RetValueL == LanEnglistCode)
				// default
			{
				UserPrefLanguage = LANG_English;
			}
			ValueL = LANG_Nums;
			TPValue = 0x00;
			#endif
		}
		else if (CPCode == SyncType && PageValue == 0)
			// 2-19
		{
			ValueL = 3;
			RetValueL = 0;
		}
		else if( CPCode == PowerMode && PageValue == 0 )	//120301 Modify
		{
			if( RetValueL == 0x01 )
			{
				if(!PowerOnFlag)
				{
					PowerOnSystem();
					#if USEFLASH
					UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit );
					#else
					NVRam_WriteByte( nvrMonitorAddr( MonitorFlag ), MonitorFlags );
					#endif
				}
			}
			else if( RetValueL == 0x04 )
			{
				if(PowerOnFlag)
				{
					PowerOffSystem();
					#if USEFLASH
					UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit );
					#else
					NVRam_WriteByte( nvrMonitorAddr( MonitorFlag ), MonitorFlags );
					#endif
				}
			}
			TPValue = 0x00;
		}
		/***********************************************Zhifeng.Wu***********************************************/
		/*	#define	I_Menu_Command	    SIORxBuffer[1]
			#define I_Menu_Set_Value_H  SIORxBuffer[2]
			#define	I_Menu_Set_Value	SIORxBuffer[3]
		         //For TPV Application
			else if (CPCode == TPV_App_Command&& PageValue == 0)
			{
				if(SIORxBuffer[0]==IMenu_Application)//For AOC I-Menu Application
				{
					//For Other Luminance Menu
					if((I_Menu_Command==ECO_Mode)&&(!UserPrefDcrMode))	//121122 Modify
					{
						{

							ICE_MAIN_CTRL(0);
							ICE_SUB_CTRL(0);
						}

						if(UserPrefColorTemp==CTEMP_SRGB)
						{
							UserPrefColorTemp=CTEMP_Warm1;
						}
						UserPrefECOMode=I_Menu_Set_Value;
						SetECO();
					}
					#if CT_sRGB_ENABLE
					else if((I_Menu_Command==Gamma)&&(UserPrefColorTemp!=CTEMP_SRGB)&&(!UserPrefDcrMode))	//120609 Modify
					{
					    #if Enable_Gamma
						UserPrefGamaMode=I_Menu_Set_Value;
						mStar_SetupGamma( UserPrefGamaMode );	//120308 Modify
						#endif
					}
					#endif
					else if(I_Menu_Command==DCR)
					{
					    #if CT_sRGB_ENABLE
						if (UserPrefColorTemp == CTEMP_SRGB)
							UserPrefColorTemp = CTEMP_Warm1;
						 #endif
						if(UserPrefDcrMode!=I_Menu_Set_Value)//duqq080806 test
							AdjustDcrMode(1);
					}

					//For Picture Boost Items

				#if ESaverPowerDownFunc
					else if(I_Menu_Command==PB_AutoPowerDown)
					{
					    ESaverPowerDownCounter=0;
						if((!I_Menu_Set_Value_H)&&(!I_Menu_Set_Value))
						{
		                    ESaverPowerDownCounter=0;
						}
						else
						{
							ESaverPowerDownCounter=((WORD)I_Menu_Set_Value_H << 8) | ((WORD)I_Menu_Set_Value);
						}
						//Osd_Show();
						//Osd_Draw4Num(1,1,ESaverPowerDownCounter);
					}
				#endif
				}

			}
			#undef	I_Menu_Command
			#undef	I_Menu_Set_Value_H
			#undef	I_Menu_Set_Value
		*/
		/*******************************************************************************************************/
		else if (CPCode == 0xFE && PageValue == 0)
		{
			#ifdef UseVGACableReadWriteAllPortsEDID
			if(DDCBuffer[3] == 0xEF)
			{
				BYTE i, Length;
				WORD Addr;
				Addr = (DDCBuffer[5] << 8) + DDCBuffer[6];
				Length = DDCBuffer[0] - 0x86;
				//	if(DDCBuffer[4]==HDMI1)
				{
					for(i = 0; i < Length; i++)
					{
						SIORxBuffer[i] = DDCBuffer[i + 7];
					}
				}
				if((DDCBuffer[4] >= VGA1 && DDCBuffer[4] <= MHL_HDMI2) || (DDCBuffer[4] >= EEPROM && DDCBuffer[4] <= PanelSettingDevice))	//130614 xiandi
				{
					EnableReadDDCType = DDCBuffer[4];
					for(i = 0; i < Length; i++)
					{
						NVRam_WriteByte(Addr + i, SIORxBuffer[i]);
					}
					EnableReadDDCType = I2C_EEPROM;
					//*/
					//WriteDevice(DDCBuffer[4] ,Addr,Length);//Write EDID or HDCP KEY
				}
				else
				{
					return 0;
				}
				DDCBuffer[0] = 0x83;
				DDCBuffer[1] = 0x00;
				DDCBuffer[2] = DDCBuffer[6]; //(Addr<<8);
				DDCBuffer[3] = Length;
				return 3;
			}
			else if((DDCBuffer[3] == 0xE1) && (DDCBuffer[4] == 0xA2))
			{
				if(DDCBuffer[6] == 0x01)
				{
					///hw_ClrDDC_WP();//EDID In Flash should not disable ddc ram.
					Set_WriteDeviceFlag();
					g_wFDCRCValue = appFactorySetEdidWriteStart( DDCBuffer[6] );//VGA1_EDID|HDMI1_EDID;//
					DDCBuffer[0] = 0x84;
					DDCBuffer[1] = 0x02;
					DDCBuffer[2] = g_wFDCRCValue >> 8;
					DDCBuffer[3] = g_wFDCRCValue & 0xFF;
					// DDCBuffer[4] = 0x03;
				}
				else if(DDCBuffer[6] == 0x00)
				{
					hw_SetDDC_WP();
					Clr_WriteDeviceFlag();
					DDCBuffer[1] = 0x02;
				}
			}
			else if(DDCBuffer[3] == 0x04)
			{
				if (PowerOnFlag)
				{
					hw_ClrAmberLed();
					hw_ClrGreenLed();
					//hw_ClrBlacklit();
					#if USEFLASH
					UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit);
					#else
					NVRam_WriteByte( nvrMonitorAddr( MonitorFlag ), MonitorFlags);
					#endif
				}
			}
			else
			#endif
			{
				#if NewFactoryCommand
				BYTE tempValue;
				#endif
				#ifdef DATA_LENGTH_20_BYTE
				BYTE i;
				for(i = 0; i < 23; i++)
					SIORxBuffer[i] = DDCBuffer[i + 3];
				#else
				SIORxBuffer[0] = DDCBuffer[3];
				SIORxBuffer[1] = DDCBuffer[4];
				SIORxBuffer[2] = DDCBuffer[5];
				SIORxBuffer[3] = DDCBuffer[6];
				SIORxBuffer[4] = DDCBuffer[7];
				SIORxBuffer[5] = DDCBuffer[8];
				SIORxBuffer[6] = DDCBuffer[9];
				SIORxBuffer[7] = DDCBuffer[10];
				#endif
				#if NewFactoryCommand
//==========================NewFactoryCommand====================
#define TPVCMD1    DDCBuffer[3]
#define TPVCMD2    DDCBuffer[4]
#define TPV_ValueH DDCBuffer[5]
#define TPV_ValueL DDCBuffer[6]
				#if 0//def WH_REQUEST//add by lwj 120828
				#if 0//WH_REQUEST_DDCCI_POWERSAVING
				if(TPVCMD1 == 0xD6) //POWER DOWN
				{
					if(TPVCMD2 == PowerOff)
					{
						PowerOffSystem();
					}
					if(TPVCMD2 == ForceIntoPowerSaving)
					{
						#if MS_PM
						if (!PowerSavingFlag)
						{
							hw_ClrBlacklit();
							Set_ForcePowerSavingFlag();
							Set_DDCForcePowerSavingFlag();
						}
						#else
						Power_PowerOffSystem();
						#endif
						hw_ClrGreenLed();
						hw_SetAmberLed();
					}
				}
				#endif
				#endif
				if(TPVCMD1 == TPV_FactoryAutoAlignment)
				{
					if(TPVCMD2 == SetFactoryMode)
					{
						if(TPV_ValueL == SetOn)
						{
							Set_FactoryModeFlag();
							Set_BurninModeFlag();
							//120413 Modify for TPV Request
							#if Enable_Gamma
							if( UserPrefGamaMode != GAMA1 )
							{
								UserPrefGamaMode = GAMA1;
								mStar_SetupGamma( GAMA1 );
							}
							#endif
							if(UserPrefECOMode != ECO_Standard)
							{
								UserPrefECOMode = ECO_Standard;
								SetECO();
							}
							if(UserPrefDcrMode)
							{
								UserPrefDcrMode = 0;
								SetECO();
								msDCROnOff(UserPrefDcrMode, MAIN_WINDOW);
							}
							UserPrefBrightness = DefBrightness;
							UserPrefContrast = DefContrast;
							mStar_AdjustBrightness(UserPrefBrightness);
							mStar_AdjustContrast(UserPrefContrast);
							DDCBuffer[1] = 0x02;
						}
						else if(TPV_ValueL == SetOff)
						{
							Clr_FactoryModeFlag();
							DDCBuffer[1] = 0x04;
						}
						#if !USEFLASH
						NVRam_WriteByte(nvrMonitorAddr(MonitorFlag), MonitorFlags);
						#else
						UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
						#endif
					}
					else if(TPVCMD2 == NVMInit)
					{
					}
					else if(TPVCMD2 == SetBurnMode)
					{
						if(TPV_ValueL == SetOn)
						{
							Set_BurninModeFlag();
							Set_DoBurninModeFlag();		//120703 Modify for TPV Request
						}
						else if(TPV_ValueL == SetOff)
						{
							Clr_BurninModeFlag();
							Clr_DoBurninModeFlag();		//120703 Modify for TPV Request
						}
						else if(TPV_ValueL == 2) //burnin room checklater
							;
						#if !USEFLASH
						NVRam_WriteByte(nvrMonitorAddr(MonitorFlag), MonitorFlags);
						#else
						SaveMonitorSetting();
						#endif
						#if USEFLASH
						Flash_ReadMonitorSet((BYTE*)&MonitorSetting, MonitorSettingSize);
						if(MonitorSetting.MonitorFlag == MonitorFlags)
						{
							DDCBuffer[1] = 0x02;
						}
						else
						{
							DDCBuffer[1] = 0x04;
						}
						#else
						NVRam_ReadByte(nvrMonitorAddr(MonitorFlag), &tempValue);
						if(tempValue == MonitorFlags)
						{
							DDCBuffer[1] = 0x02;
						}
						else
						{
							DDCBuffer[1] = 0x04;
						}
						#endif
					}
					else if(TPVCMD2 == ClearBacklitTime)
					{
						#if USEFLASH
						#else
						SaveBlacklitTime();
						NVRam_ReadTbl(BlacklitTimeAddr, (BYTE*)(&tempValue), 4);
						if(tempValue == 0)
						{
							DDCBuffer[1] = 0x02;
						}
						else
						{
							DDCBuffer[1] = 0x04;
						}
						#endif
					}
					else if(TPVCMD2 == SetDPSAndICareEnable)		//130311 Modify
					{
					}
					else if(TPVCMD2 == SetProduceMode)
					{
						#if !USEFLASH
						WORD temp, temp1;
						#endif
						if(TPV_ValueL == SetOn)
						{
							#if AudioFunc
							UserPrefVolume = 90;	//120920 Modify for PE Request
							mStar_AdjustVolume(UserPrefVolume);			//130107_23 Henry
							#endif
							#if USEFLASH
							FactoryProductModeValue = ProductModeOnValue;
							SaveFactorySetting();
							SaveMonitorSetting();
							#else
							{
								temp = ProductModeOnValue;
								NVRam_WriteTbl(ProductModeAddr, (BYTE*)(&temp), 2);
								#if AudioFunc
								NVRam_WriteByte(nvrMonitorAddr(Volume), UserPrefVolume);
								#endif
							}
							#endif
						}
						else if(TPV_ValueL == SetOff)
						{
							#if USEFLASH
							FactoryProductModeValue = ProductModeOffValue;
							SaveFactorySetting();
							#else
							{
								temp = ProductModeOffValue;
								NVRam_WriteTbl(ProductModeAddr, (BYTE*)(&temp), 2);
							}
							#endif
						}
						#if USEFLASH
						Flash_ReadFactorySet((BYTE*)&FactorySetting, FactorySettingSize);
						if(FactorySetting.ProductModeValue == FactoryProductModeValue)
						{
							DDCBuffer[1] = 0x02;
						}
						else
						{
							DDCBuffer[1] = 0x04;
						}
						#else
						NVRam_ReadTbl(ProductModeAddr, (BYTE*)(&temp1), 2);
						if(temp1 == temp)
						{
							DDCBuffer[1] = 0x02;
						}
						else
						{
							DDCBuffer[1] = 0x04;
						}
						#endif
					}
					else if(TPVCMD2 == LogoONOFF) //  2011.8.3
					{
						if(TPV_ValueH == 0x06)	//120420 Modify
						{
							if(TPV_ValueL == 0x01)
							{
								UserPrefLogoON = 1;
								#if USEFLASH
								SaveFactorySetting();
								#else
								NVRam_WriteByte(nvrFactoryAddr(LogoON), UserPrefLogoON);
								#endif
							}
							else
							{
								UserPrefLogoON = 0;
								#if USEFLASH
								SaveFactorySetting();
								#else
								NVRam_WriteByte(nvrFactoryAddr(LogoON), UserPrefLogoON);
								#endif
							}
						}
						else if(TPV_ValueH == 0x03)	//120301 Modify
						{
							if( TPV_ValueL == SetOn )
							{
								if(!UserPrefDcrMode)
								{
									AdjustDcrMode(1);
									#if !USEFLASH
									NVRam_WriteByte( nvrMonitorAddr( DcrMode ), UserPrefDcrMode );
									#else
									UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit );
									#endif
								}
							}
							else if( TPV_ValueL == SetOff )
							{
								if(UserPrefDcrMode)
								{
									AdjustDcrMode(1);
									#if !USEFLASH
									NVRam_WriteByte( nvrMonitorAddr( DcrMode ), UserPrefDcrMode );
									#else
									UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit );
									#endif
								}
							}
						}
					}
					#if PanelminiLVDS ||PANEL_VCOM_ADJUST	//110229 Modify
					else if(TPVCMD2 == AdjPanelVCOM)
					{
						#if VCOM_TYPE == VCOM_MAXIM	|| VCOM_TYPE == VCOM_SMIM ||VCOM_TYPE == VCOM_TPSIM	//120322 Modify
						WordValue = (( TPV_ValueH << 8 ) | TPV_ValueL );
						WordValue = WordValue + VCOM_VALUE_OFFSET;
						if( WordValue >= MAX_VCOM_VALUE )
							FactorySetting.VcomValue = MAX_VCOM_VALUE;
						else
							FactorySetting.VcomValue = WordValue & 0x3FF;
						#else
						if( TPV_ValueL >= 0x7F )
							FactorySetting.VcomValue = 0x7F;
						else
							FactorySetting.VcomValue = TPV_ValueL;
						#endif
						msWriteMiniLVDSi2c_Vcom_DAC(FactorySetting.VcomValue);
						#if USEFLASH
						SaveFactorySetting();
						#else
						#if VCOM_TYPE == VCOM_MAXIM || VCOM_TYPE == VCOM_SMIM ||VCOM_TYPE == VCOM_TPSIM	//120413 Modify
						NVRam_WriteWord( nvrFactoryAddr( VcomValue ), FactorySetting.VcomValue );
						#else
						NVRam_WriteByte( nvrFactoryAddr( VcomValue ), FactorySetting.VcomValue );
						#endif
						#endif
					}
					#endif
					#if HDCPKEY_IN_Flash
					else if(TPVCMD2 == HDCPReadWriteStart)
					{
						Set_WriteHDCPcodeFlag();
						TCRCvalue = 0;
						Power_TurnOffLed();
						//Flash_Erase_FreeBuffer(FLASH_KEY_HDCP,0); // jeff add it in 2009 0907
						bFlashWriteFactory = TRUE;
						#if 0 // Enable_Cache
						MCU_DisableCache();
						#endif
						#if !((CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF) && ENABLE_CABLE_5V_EDID)
						FlashSectorErase(TRUE, HDCPKEYSET_START);
						FlashDisableWP(HDCPKEYSET_START);
						#endif
					}
					#endif
					#if Enable_Gamma
					else if(TPVCMD2 == AdjGammaMode)
					{
						UserPrefGamaMode = TPV_ValueL;
						mStar_SetupGamma( UserPrefGamaMode );
					}
					#endif
				}
				else if(TPVCMD1 == TPV_AdjRedGain)
				{
					UserPrefRedColor = TPV_ValueL; // for CT
					//mStar_AdjustRedColor(UserPrefRedColor, UserPrefContrast);
					mStar_AdjustRGBColor(UserPrefContrast, UserPrefRedColor, UserPrefGreenColor, UserPrefBlueColor);	//120105 Modify
					DDCBuffer[1] = 0x02;
				}
				else if(TPVCMD1 == TPV_AdjGreenGain)
				{
					UserPrefGreenColor = TPV_ValueL; // for CT
					//mStar_AdjustGreenColor(UserPrefGreenColor, UserPrefContrast);
					mStar_AdjustRGBColor(UserPrefContrast, UserPrefRedColor, UserPrefGreenColor, UserPrefBlueColor);	//120105 Modify
					DDCBuffer[1] = 0x02;
				}
				else if(TPVCMD1 == TPV_AdjBlueGain)
				{
					UserPrefBlueColor = TPV_ValueL; // for CT
					//mStar_AdjustBlueColor(UserPrefBlueColor, UserPrefContrast);
					mStar_AdjustRGBColor(UserPrefContrast, UserPrefRedColor, UserPrefGreenColor, UserPrefBlueColor);	//120105 Modify
					DDCBuffer[1] = 0x02;
				}
				else if(TPVCMD1 == TPV_AdjContrast)
				{
					UserPrefContrast = TPV_ValueL;
					UserPrefContrast = UserPrefContrast + MinContrastValue;//checklater
					mStar_AdjustContrast(UserPrefContrast);
					DDCBuffer[1] = 0x02;
				}
				else if(TPVCMD1 == TPV_AdjBrightness)
				{
					UserPrefBrightness = TPV_ValueL;
					mStar_AdjustBrightness(UserPrefBrightness);
					DDCBuffer[1] = 0x02;
				}
				else if(TPVCMD1 == TPV_SetDefLanguage)
				{
					#if 1	//120322 Modify
					if (TPV_ValueL == LanSpanishCode)
					{
						UserPrefLanguage = LANG_Spanish;
					}
					else if (TPV_ValueL == LanFrenchCode)
					{
						UserPrefLanguage = LANG_France;
					}
					else if (TPV_ValueL == LanGermanCode)
					{
						UserPrefLanguage = LANG_German;
					}
					else if (TPV_ValueL == LanItalianCode)
					{
						UserPrefLanguage = LANG_Italian;
					}
					else if (TPV_ValueL == LanRussianCode)
					{
						UserPrefLanguage = LANG_Russia;
					}
					else if (TPV_ValueL == LanSwedishCode)
					{
						UserPrefLanguage = LANG_Swedish;
					}
					else if (TPV_ValueL == LanPolishCode)
					{
						UserPrefLanguage = LANG_Polish;
					}
					else if (TPV_ValueL == LanCzechCode)
					{
						UserPrefLanguage = LANG_Czech;
					}
					else if (TPV_ValueL == LanPortugueseCode_Brazil)
					{
						UserPrefLanguage = LANG_Portugues;
					}
					else if (TPV_ValueL == LanSChineseCode)
					{
						UserPrefLanguage = LANG_SChina;
					}
					else if (TPV_ValueL == LanTChineseCode)
					{
						UserPrefLanguage = LANG_TChina;
					}
					else if (TPV_ValueL == LanKoreanCode)
					{
						UserPrefLanguage = LANG_Korea;
					}
					else if (TPV_ValueL == LanJapaneseCode)
					{
						UserPrefLanguage = LANG_Japan;
					}
					else if (TPV_ValueL == LanDutchCode)	//120105 Modify
					{
						UserPrefLanguage = LANG_Dutch;
					}
					else if (TPV_ValueL == LanFinnishCode)	//120105 Modify
					{
						UserPrefLanguage = LANG_Finnish;
					}
					else if (TPV_ValueL == LanEnglistCode)
						// default
					{
						UserPrefLanguage = LANG_English;
					}
					#if CHIP_ID == CHIP_TSUMV	//130924 henry  petit update 20131017
					Set_LoadOSDDataFlag();
					if(MenuPageIndex >= MainMenu && MenuPageIndex <= ExitMenu)
					{
						Osd_Hide();
						MenuPageIndex = RootMenu;
					}
					#else
					//For Select SChinese/TChinese/Korean Language Font Error Issue
					LoadLanguageStatusPropfont();	//120105 Modify
					#endif
					#endif
					#if !USEFLASH
					NVRam_WriteByte(nvrMonitorAddr(Language), UserPrefLanguage);
					#else
					SaveMonitorSetting();
					#endif
					#if USEFLASH
					Flash_ReadMonitorSet((BYTE*)&MonitorSetting, MonitorSettingSize);
					if(MonitorSetting.Language == UserPrefLanguage)
					{
						DDCBuffer[1] = 0x02;
					}
					else
					{
						DDCBuffer[1] = 0x04;
					}
					#else
					NVRam_ReadByte(nvrMonitorAddr(Language), &tempValue);
					if(tempValue == UserPrefLanguage)
					{
						DDCBuffer[1] = 0x02;
					}
					else
					{
						DDCBuffer[1] = 0x04;
					}
					#endif
				}
				else if(TPVCMD1 == TPV_SelectInput)
				{
				}
				else if(TPVCMD1 == TPV_SelectGamma)
				{
				}
				else if(TPVCMD1 == TPV_RestorFactory)
				{
					{
						if( ResetAllSetting())
							DDCBuffer[1] = 0x02;
						else
							DDCBuffer[1] = 0x04;
					}
					ForceDelay1ms(50);
				}
				else if(TPVCMD1 == TPV_AutoColor)	//120723 Modify
				{
					if (mStar_AutoColor())
					{
						#if Show_BackLightTimeValue
						BlacklitTime_S = 0;
						BlacklitTime_M = 0;
						BlacklitTime_H = 0;
						MonitorBackLightTime_S = BlacklitTime_S;
						MonitorBackLightTime_M = BlacklitTime_M;
						MonitorBackLightTime_H = BlacklitTime_H;
						#endif
						if (CheckFactorySettingOutOfRange())
						{
							#if 1//USEFLASH		//131105 Henry For AutoColor Not Save
							Init_FactorySetting();
							SaveFactorySetting();
							#else
							Init_MonitorSetting();
							SaveMonitorSetting();
							#endif
							DDCBuffer[1] = 0x04;
						}
						else
						{
							#if 1//USEFLASH		//131105 Henry For AutoColor Not Save
							SaveFactorySetting();
							#else
							SaveMonitorSetting();
							#endif
							DDCBuffer[1] = 0x02;
							#if 0//def WH_REQUEST		//Fay 2013/9/13
							Set_EnableShowFactoryMenuFlag();
							#else
							Delay1ms(200);
							MenuPageIndex = FactoryMenu;
							MenuItemIndex = 0;
							Osd_SetPosition(0, 100); //20140903  for BJ PE
							DrawOsdMenu();
							//Osd_SetPosition(0,100);
							#endif
						}
						#if USEFLASH
						//SaveMonitorSetting2();
						UserPref_EnableFlashSaveBit( bFlashForceSaveMonitor2Bit );
						//UserPref_EnableFlashSaveBit( bFlashSaveMonitorBit );
						#else
						NVRam_WriteByte(NVRAM_ADDR_MointorMember(MonitorFlag), MonitorFlags);
						NVRam_WriteByte(nvrMonitorAddr(BacklighttimeS), MonitorBackLightTime_S);
						NVRam_WriteByte(nvrMonitorAddr(BacklighttimeM), MonitorBackLightTime_M);
						NVRam_WriteByte(nvrMonitorAddr(BacklighttimeH), MonitorBackLightTime_H);
						#endif
					}
					else
					{
						#if 1//USEFLASH			//131105 Henry For AutoColor Not Save
						SaveFactorySetting();
						#else
						SaveMonitorSetting();
						#endif
						DDCBuffer[1] = 0x04;
					}
				}
				else if(TPVCMD1 == TPV_AutoConfig)
				{
					if (mStar_AutoGeomtry())
					{
						CheckModeSettingRange();
						DDCBuffer[1] = 0x02;
					}
					else
						DDCBuffer[1] = 0x04;
					SaveModeSetting();
				}
				else if(TPVCMD1 == TPV_SaveOrRecallColTmp)
				{
					//#define ColTemp		DDCBuffer[4]
					//#define InpSrc	  DDCBuffer[5]
					//#define ActFlag	  DDCBuffer[6]
					#if 1//WH_REQUEST_DDCCI
					if( TPVCMD2 == 0x81 )//for quick Set_ColorTemp  //only for WH 20120906 lwj
					{
						//9300
						UserPrefRedColorCool1 = SIORxBuffer[2];
						UserPrefGreenColorCool1 = SIORxBuffer[3];
						UserPrefBlueColorCool1 = SIORxBuffer[4];
						//Normal
						UserPrefRedColorNormal = SIORxBuffer[5];
						UserPrefGreenColorNormal = SIORxBuffer[6];
						UserPrefBlueColorNormal = SIORxBuffer[7];
						//6500
						UserPrefRedColorWarm1 = SIORxBuffer[8];
						UserPrefGreenColorWarm1 = SIORxBuffer[9];
						UserPrefBlueColorWarm1 = SIORxBuffer[10];
						#if CT_sRGB_ENABLE
						//SRGB
						UserPrefRedColorSRGB = SIORxBuffer[11];
						UserPrefGreenColorSRGB = SIORxBuffer[12];
						UserPrefBlueColorSRGB = SIORxBuffer[13];
						#endif
						#if USEFLASH
						SaveFactorySetting();
						#else
						SaveMonitorSetting();
						#endif
						#if USEFLASH
						Flash_ReadMonitorSet((BYTE*)&MonitorSetting, MonitorSettingSize);
						tempValue = MonitorSetting.ColorTemp;
						Flash_ReadFactorySet((BYTE*)&FactorySetting, FactorySettingSize);
						#else
						NVRam_ReadByte(nvrMonitorAddr(ColorTemp), &tempValue);
						NVRam_ReadTbl(MonitorSettingAddr, (BYTE*) &MonitorSetting, MonitorSettingSize);
						#endif
						// recommand = OK_READY;
					}
					#endif
					if(TPV_ValueL)
					{
						switch(TPVCMD2)
						{
								#if CT_sRGB_ENABLE
							case ColorTempSRGB:
								UserPrefColorTemp = CTEMP_SRGB;
								UserPrefRedColor = UserPrefRedColorSRGB;
								UserPrefGreenColor = UserPrefGreenColorSRGB;
								UserPrefBlueColor = UserPrefBlueColorSRGB;
								ReadColorTempSetting(); // 2006/11/10 6:59PM by KK ReadSRGBSetting();
								mStar_AdjustBrightness(UserPrefBrightness);
								mStar_AdjustContrast(UserPrefContrast);
								break;
								#endif
							case ColorTempNative:
								break;
							case ColorTemp4000K:
								break;
							case ColorTemp5000K:
								break;
							case ColorTemp6500K:
								UserPrefColorTemp = CTEMP_Warm1;
								UserPrefRedColor = UserPrefRedColorWarm1;
								UserPrefGreenColor = UserPrefGreenColorWarm1;
								UserPrefBlueColor = UserPrefBlueColorWarm1;
								ReadColorTempSetting(); // 2006/11/10 6:59PM by KK ReadWarm1Setting();
								mStar_AdjustBrightness(UserPrefBrightness);
								mStar_AdjustContrast(UserPrefContrast);
								break;
							case ColorTemp7500K:
								UserPrefColorTemp = CTEMP_Normal;
								UserPrefRedColor = UserPrefRedColorNormal;
								UserPrefGreenColor = UserPrefGreenColorNormal;
								UserPrefBlueColor = UserPrefBlueColorNormal;
								ReadColorTempSetting(); // 2006/11/10 6:59PM by KK ReadNormalSetting();
								mStar_AdjustBrightness(UserPrefBrightness);
								mStar_AdjustContrast(UserPrefContrast);
								break;
							case ColorTemp8200K:
								break;
							case ColorTemp9300K:
								UserPrefColorTemp = CTEMP_Cool1;
								ReadColorTempSetting(); // 2006/11/10 6:59PM by KK	ReadCool1Setting();
								UserPrefRedColor = UserPrefRedColorCool1;
								UserPrefGreenColor = UserPrefGreenColorCool1;
								UserPrefBlueColor = UserPrefBlueColorCool1;
								mStar_AdjustBrightness(UserPrefBrightness);
								mStar_AdjustContrast(UserPrefContrast);
								break;
							case ColorTemp10000K:
								break;
							case ColorTemp11500K:
								break;
							case ColorTempUser:
								break;
							case SaveAllColorTemp:
								SaveFactorySetting();
								break;
							default:
								break;
						}
						DDCBuffer[1] = 0x02;
					}
					else
					{
						switch(TPVCMD2)
						{
								#if CT_sRGB_ENABLE
							case ColorTempSRGB:
								UserPrefColorTemp = CTEMP_SRGB;
								UserPrefRedColorSRGB = UserPrefRedColor;
								UserPrefGreenColorSRGB = UserPrefGreenColor;
								UserPrefBlueColorSRGB = UserPrefBlueColor;
								break;
								#endif
							case ColorTempNative:
								break;
							case ColorTemp4000K:
								break;
							case ColorTemp5000K:
								break;
							case ColorTemp6500K:
								UserPrefColorTemp = CTEMP_Warm1;
								UserPrefRedColorWarm1 = UserPrefRedColor;
								UserPrefGreenColorWarm1 = UserPrefGreenColor;
								UserPrefBlueColorWarm1 = UserPrefBlueColor;
								break;
							case ColorTemp7500K:
								UserPrefColorTemp = CTEMP_Normal;
								UserPrefRedColorNormal = UserPrefRedColor;
								UserPrefGreenColorNormal = UserPrefGreenColor;
								UserPrefBlueColorNormal = UserPrefBlueColor;
								break;
							case ColorTemp8200K:
								break;
							case ColorTemp9300K:
								UserPrefColorTemp = CTEMP_Cool1;
								UserPrefRedColorCool1 = UserPrefRedColor;
								UserPrefGreenColorCool1 = UserPrefGreenColor;
								UserPrefBlueColorCool1 = UserPrefBlueColor;
								//Osd_Draw4Num(0,1,UserPrefRedColor);
								//Osd_Draw4Num(0,2,UserPrefRedColorCool1);
								break;
							case ColorTemp10000K:
								break;
							case ColorTemp11500K:
								break;
							case ColorTempUser:
								break;
							case SaveAllColorTemp:
								SaveFactorySetting();
								break;
							default:
								break;
						}
						//Osd_Draw4Num(0,0,11);
						//Osd_Show();
						SaveFactorySetting();
						#if USEFLASH
						//Flash_ReadMonitorSet(0, (BYTE*)&MonitorSetting, MonitorSettingSize);
						Flash_ReadMonitorSet((BYTE*)&MonitorSetting, MonitorSettingSize);
						tempValue = MonitorSetting.ColorTemp;
						//Flash_ReadFactorySet(0, (BYTE*)&FactorySetting, FactorySettingSize);
						Flash_ReadFactorySet((BYTE*)&FactorySetting, FactorySettingSize);
						//msWriteByte(SC0_34,tempValue);
						//msWriteByte(SC0_35,UserPrefBlueColorCool1);
						#else
						NVRam_ReadByte(nvrMonitorAddr(ColorTemp), &tempValue);
						NVRam_ReadTbl(MonitorSettingAddr, (BYTE*) &MonitorSetting, MonitorSettingSize);
						NVRam_ReadTbl(FactorySettingAddr, (BYTE*) &FactorySetting, FactorySettingSize);
						#endif
						switch(tempValue)
						{
								#if CT_sRGB_ENABLE
							case  CTEMP_SRGB:
								#if USEFLASH
								if( MonitorSetting.ColorTemp == UserPrefColorTemp &&
								        FactorySetting.RedColorsRGB == UserPrefRedColor &&
								        FactorySetting.GreenColorsRGB == UserPrefGreenColor &&
								        FactorySetting.BlueColorsRGB == UserPrefBlueColor)
								#else
								if( MonitorSetting.ColorTemp == UserPrefColorTemp &&
								        FactorySetting.RedColorsRGB == UserPrefRedColor &&
								        FactorySetting.GreenColorsRGB == UserPrefGreenColor &&
								        FactorySetting.BlueColorsRGB == UserPrefBlueColor)
								#endif
									DDCBuffer[1] = 0x02;
								else
									DDCBuffer[1] = 0x04;
								break;
								#endif
							case CTEMP_Warm1:
								#if USEFLASH
								if( MonitorSetting.ColorTemp == UserPrefColorTemp &&
								        FactorySetting.RedColorWarm1 == UserPrefRedColor &&
								        FactorySetting.GreenColorWarm1 == UserPrefGreenColor &&
								        FactorySetting.BlueColorWarm1 == UserPrefBlueColor)
								#else
								if( MonitorSetting.ColorTemp == UserPrefColorTemp &&
								        FactorySetting.RedColorWarm1 == UserPrefRedColor &&
								        FactorySetting.GreenColorWarm1 == UserPrefGreenColor &&
								        FactorySetting.BlueColorWarm1 == UserPrefBlueColor)
								#endif
									DDCBuffer[1] = 0x02;
								else
									DDCBuffer[1] = 0x04;
								break;
							case CTEMP_Normal:
								#if USEFLASH
								if( MonitorSetting.ColorTemp == UserPrefColorTemp &&
								        FactorySetting.RedColorNormal == UserPrefRedColor &&
								        FactorySetting.GreenColorNormal == UserPrefGreenColor &&
								        FactorySetting.BlueColorNormal == UserPrefBlueColor)
								#else
								if( MonitorSetting.ColorTemp == UserPrefColorTemp &&
								        FactorySetting.RedColorNormal == UserPrefRedColor &&
								        FactorySetting.GreenColorNormal == UserPrefGreenColor &&
								        FactorySetting.BlueColorNormal == UserPrefBlueColor)
								#endif
									DDCBuffer[1] = 0x02;
								else
									DDCBuffer[1] = 0x04;
								break;
							case CTEMP_Cool1:
								#if USEFLASH
								if( MonitorSetting.ColorTemp == UserPrefColorTemp &&
								        FactorySetting.RedColorCool1 == UserPrefRedColor &&
								        FactorySetting.GreenColorCool1 == UserPrefGreenColor &&
								        FactorySetting.BlueColorCool1 == UserPrefBlueColor)
								#else
								if( MonitorSetting.ColorTemp == UserPrefColorTemp &&
								        FactorySetting.RedColorCool1 == UserPrefRedColor &&
								        FactorySetting.GreenColorCool1 == UserPrefGreenColor &&
								        FactorySetting.BlueColorCool1 == UserPrefBlueColor)
								#endif
									DDCBuffer[1] = 0x02;
								else
									DDCBuffer[1] = 0x04;
								//Osd_Draw4Num(0,1,UserPrefRedColor);
								//Osd_Draw4Num(0,2,UserPrefRedColorCool1);
								msWriteByte(SC0_36, DDCBuffer[1]);
								break;
							default:
								break;
						}
					}
					//#undef ColTemp
					//#undef InpSrc
					//#undef ActFlag
				}
				#if HDCPKEY_IN_Flash
				else if(TPVCMD1 == TPV_HDCPReadWriteStart && WriteHDCPcodeFlag)
				{
					#if ((CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF) && ENABLE_CABLE_5V_EDID)
					WORD wTemp;
					if(SIO_TYPE2 < (HDCPKEY_SIZE / HDCP_BLOCK_LENGTH))
						Flash_Write_Factory_KeySet(FLASH_KEY_HDCP, SIO_TYPE2, HDCP_BLOCK_LENGTH, &SIORxBuffer[3], HDCP_BLOCK_LENGTH);
					else if(SIO_TYPE2 == (HDCPKEY_SIZE / HDCP_BLOCK_LENGTH))
					{
						Flash_Write_Factory_KeySet(FLASH_KEY_HDCP, SIO_TYPE2, HDCP_BLOCK_LENGTH, &SIORxBuffer[3], HDCPKEY_SIZE % HDCP_BLOCK_LENGTH);
						for(wTemp = 0; wTemp < HDCPKEY_SIZE; wTemp++)
						{
							TCRCvalue = CRC16(FlashReadByte(g_wKEYSET_START + wTemp), TCRCvalue);
						}
						Set_LoadHDCPKeyFlag();
						Power_TurnOnGreenLed();
					}
					#else
					BYTE i;
					for (i = 0; i < HDCP_BLOCK_LENGTH; i++)
					{
						//SIO_TYPE2==HDCP BANK NO	  SIORxBuffer[3+i]==HDCP DATA
						if(HDCP_BLOCK_LENGTH * SIO_TYPE2 + i < HDCPKEY_SIZE)
						{
							FlashHDCPWriteByte((HDCPKEYSET_START + HDCP_BLOCK_LENGTH * SIO_TYPE2 + i), SIORxBuffer[3 + i]);
							TCRCvalue = CRC16(FlashReadByte(HDCPKEYSET_START + HDCP_BLOCK_LENGTH * SIO_TYPE2 + i), TCRCvalue);
						}
					}
					if (SIO_TYPE2 == HDCPKEY_SIZE / HDCP_BLOCK_LENGTH) //HDCP WRITE END
					{
						Set_LoadHDCPKeyFlag();
						bFlashWriteFactory = FALSE;
						FlashEnableWP();
						#if 0 //Enable_Cache
						#if Enable_Cache
						CACHE_ENABLE();  //MCU_EnableCache();
						#else
						CACHE_DISABLE();
						#endif
						#endif
						Power_TurnOnGreenLed();
					}
					#endif
				}
				#endif
				else if(TPVCMD1 == TPV_SelectGamma)
				{
				}
#undef TPV_ValueH
#undef TPV_ValueL
#undef TPVCMD1
//==========================NewFactoryCommand=================
				#endif
				{
					#if 1//ndef WH_REQUEST
					AOCAlign();
					#endif
				}
			}
		}
		#if JRY_Color_Tool_Functing
		else if(CPCode == 0x7B && PageValue == 0)
		{
			Resault = JRYColorToolControl();
		}
		#endif
		else
		{
			DDCBuffer[2] = 0x01;
		}
		//Setting----------------------------------End
		//Transmission-----------------------------Start
		if (CommandCode == SETVCPFeature)
		{
			#if  JRY_Color_Tool_Functing
			if(CPCode == 0x7B)
				return Resault;
			else
			#endif
			{
				UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
				return 9;
			}
		}
		else
		{
			DDCBuffer[0] = 0x89;
			DDCBuffer[1] = 0xC7;
			DDCBuffer[3] = PageValue;
			DDCBuffer[4] = CPCode;
			DDCBuffer[5] = TPValue;
			DDCBuffer[6] = ValueH;
			DDCBuffer[7] = ValueL;
			DDCBuffer[8] = RetValueH;
			DDCBuffer[9] = RetValueL;
			return 9;
		}
		//Transmission-------------------------------End
	}
	//SetValue------------------------------------------------------End
	else if (CommandCode == SaveCurrentSetting)
		// 1-10
	{
		//SaveUserPref();
		#if USEFLASH
		UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit | bFlashSaveModeBit);
		#else
		SaveMonitorSetting();
		SaveModeSetting();
		#endif
		return 0;
	}
	else if (CommandCode == GETVCPPage)
		// 1-11
	{
		DDCBuffer[0] = 0x83;
		DDCBuffer[1] = 0xC5;
		DDCBuffer[2] = 0;
		DDCBuffer[3] = 3;
		return 3;
	}
	DDCBuffer[0] = 0x80;
	return 0;
}

#else

BYTE AlignControl(void)
{
	BYTE CommandCode, CPCode, ValueL, RetValueH, RetValueL, PageValue;
	BYTE TPValue;
	WORD WordValue, ValueH;
	WORD XDATA g_wFDCRCValue = 0;
	#if JRY_Color_Tool_Functing
	BYTE  XDATA Resault;
	#endif
	CommandCode = DDCBuffer[1];
	PageValue = 0;
	if (CommandCode == SETVCPFeature)
		// 1-1
	{
		CPCode = DDCBuffer[2];
		RetValueH = DDCBuffer[3];
		RetValueL = DDCBuffer[4];
		WordValue = ((WORD)DDCBuffer[3] << 8) | ((WORD)DDCBuffer[4]);
	}
	else if (CommandCode == SETPagedVCP)
		// 1-5
	{
		PageValue = DDCBuffer[2];
		CPCode = DDCBuffer[3];
		RetValueH = DDCBuffer[4];
		RetValueL = DDCBuffer[5];
		WordValue = ((WORD)DDCBuffer[4] << 8) | ((WORD)DDCBuffer[5]);
	}
	else if (CommandCode == GETVCPFeature)
		// 1-2
	{
		CPCode = DDCBuffer[2];
	}
	else if (CommandCode == GETPagedVCP)
		// 1-4
	{
		PageValue = DDCBuffer[2];
		CPCode = DDCBuffer[3];
	}
	else
	{
		RetValueH = CAP_VCP[4];
		RetValueL = DVI_CAP_VCP[5];
		DDCBuffer[0] = 0x80;
		return 0;
	}
	if (CommandCode == GETVCPFeature || CommandCode == GETPagedVCP)
	{
		//Initial-----------------------Start
		if (CommandCode == GETVCPFeature)
		{
			if(CPCode == TPV_App_Command)
			{
				DDCBuffer[0] = 0x88;
				DDCBuffer[1] = 0x02;
				DDCBuffer[2] = 0x00;
				DDCBuffer[3] = IMenu_Application;
				//DDCBuffer[4] = SIORxBuffer[1];//ExtByte
			}
			else
			{
				DDCBuffer[0] = 0x88;
				DDCBuffer[1] = 0x02;
				DDCBuffer[2] = 0x00;
				DDCBuffer[3] = CPCode;
				DDCBuffer[4] = 0x01;
				ValueH = 0x00;
				ValueL = 0xFF;
				RetValueH = 0x00;
				TPValue = 0x01;
			}
		}
		else
		{
			DDCBuffer[0] = 0x89;
			DDCBuffer[1] = 0xC7;
			DDCBuffer[2] = 0x00;
			DDCBuffer[3] = PageValue;
			DDCBuffer[4] = CPCode;
			DDCBuffer[5] = 0x01;
			ValueH = 0x00;
			ValueL = 0xFF;
			RetValueH = 0x00;
			TPValue = 0x01;
		}
		//Initial-----------------------End
		//Setting---------------------------------Start
		if (CPCode == NewControl && PageValue == 0)
		{
			/*if(DDCCINewControlFlag)
			RetValueL = 2;
			else*/
			RetValueL = 1;
			ValueL = 2;
		}
		#if ENABLE_HDMI_DRR_MCCS
		else if(CPCode == VCP_FREESYNC_MODE)
		{
			TPValue = 0x00;
			ValueH = 0x00;
			ValueL = 0x01;
			RetValueH = 0x00;
			if(UserprefFreeSyncMode)
				RetValueL = 1;
			else
				RetValueL = 0; // USER_PREF_FREESYNCMODE;
		}
		#endif
		#if ColorTool_Clear_Time
		else if(CPCode == GetUserTime && PageValue == 0)
		{
			#if  Show_BackLightTimeValue
			TPValue = 0x00;
			ValueH		= BlacklitTime_H;
			ValueL		= 0;
			RetValueH	= BlacklitTime_M;
			RetValueL	= BlacklitTime_S;
			#endif
		}
		//*/
		else if(CPCode == CleanUsedTime && PageValue == 0)
		{
			if (PowerOnFlag)
				Set_DDCCResetTimeFlag();
		}
		else if(CPCode == AutoColorDDCCI && PageValue == 0)
		{
			if(SrcInputType == Input_VGA)
			{
				Set_DDCCIAutoColorFlag();
			}
		}
		#endif
		else
		{
			DDCBuffer[2] = 0x01;
			RetValueL = 0x00;
			ValueH = 0xFF;
			ValueL = 0xFF;
		}
		//Setting---------------------------------End
		//Transmission----------------------------Start
		if (CommandCode == GETVCPFeature)
		{
			if(CPCode == TPV_App_Command)
			{
				DDCBuffer[5] = ValueH;
				DDCBuffer[6] = ValueL;
				DDCBuffer[7] = RetValueH;
				DDCBuffer[8] = RetValueL;
			}
			else
			{
				DDCBuffer[4] = TPValue;
				DDCBuffer[5] = ValueH;
				DDCBuffer[6] = ValueL;
				DDCBuffer[7] = RetValueH;
				DDCBuffer[8] = RetValueL;
			}
			return 8;
		}
		else
		{
			DDCBuffer[5] = TPValue;
			DDCBuffer[6] = ValueH;
			DDCBuffer[7] = ValueL;
			DDCBuffer[8] = RetValueH;
			DDCBuffer[9] = RetValueL;
			return 9;
		}
		//Transmission----------------------------End
	}
	//SetValue------------------------------------------------------Start
	else if (CommandCode == SETVCPFeature || CommandCode == SETPagedVCP)
	{
		/*
		//if(!DisplayLogoFlag)
		 // Osd_Hide();
		 */
		DDCBuffer[2] = 0x00; // Result Code
		ValueH = 0x00;
		ValueL = 0xFF;
		TPValue = 0x01;
		#if JRY_Color_Tool_Functing
		if(CPCode == 0x7B && PageValue == 0)
		{
			Resault = JRYColorToolControl();
		}
		else
		#endif
		{
			DDCBuffer[2] = 0x01;
		}
		//Setting----------------------------------End
		//Transmission-----------------------------Start
		if (CommandCode == SETVCPFeature)
		{
			#if  JRY_Color_Tool_Functing
			if(CPCode == 0x7B)
				return Resault;
			else
			#endif
				//else
				return 9;
		}
		else
		{
			DDCBuffer[0] = 0x89;
			DDCBuffer[1] = 0xC7;
			DDCBuffer[3] = PageValue;
			DDCBuffer[4] = CPCode;
			DDCBuffer[5] = TPValue;
			DDCBuffer[6] = ValueH;
			DDCBuffer[7] = ValueL;
			DDCBuffer[8] = RetValueH;
			DDCBuffer[9] = RetValueL;
			return 9;
		}
		//Transmission-------------------------------End
	}
	else
	{
		AOCAlign();
	}
	DDCBuffer[0] = 0x80;
	return 0;
}

#endif

