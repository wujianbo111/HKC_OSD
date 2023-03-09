#include "types.h"
#include "board.h"
#include "global.h"
#include "keypaddef.h"
#include "menudef.h"
#include "ms_reg.h"
#include "debug.h"
#include "msosd.h"
#include "power.h"
#include "misc.h"
#include "autofunc.h"
#include "nvram.h"
#include "userpref.h"
#include "mstar.h"
#include "ms_rwreg.h"
#include "adjust.h"
#include "mcu.h"
#include "menustr.h"
#include "Gamma.h"
#include "ddc2bi.h"
#include "GPIO_DEF.h"
#include "drvosd.h"
#include "msosdfunction.h"
#include "drvadc.h"
#include "menufunc.h"       //2012.08.14 Stone.yu

#include "MsDLC.H"
#include "MsACE.H"
#include "MsRegTV.h"
#include "Panel.h"

#if ENABLE_HDCP
#include "MsHDCP.h"
#endif
#if ENABLE_RTE
#include "drvmsovd.h"
#endif
#if ENABLE_HDMI
#include "MsHDMI.h"
#include "msHDMIACE.h"
#endif
#if 1//USEFLASH
#include "msflash.h"
#endif
#if MS_PM
#include "MS_PM.h"
#endif
#include "MsID_V1.h"
#ifdef TSUMXXT//#if( ChipID == TSUMXXT )		//110311 Modify
#include "msADC.h"
#endif
#if PanelminiLVDS || PANEL_VCOM_ADJUST	//110229 Modify
#include "msMiniLVDSI2c.h"
#endif

#if CHIP_ID==CHIP_TSUMU
#include "msscaler.h"
#elif CHIP_ID == CHIP_TSUM2
#include "msscaler_2.h"
#endif

#if ENABLE_FREESYNC
#include "ComboApp.h"
#endif

#include "panel_mwe_default.h"
////////////////////////////////////
#include "drvMcu.h"
#include "drvmStar.h"
///////////////////////////////////

void SaveUserPref(void);
void ReadWarm1Setting(void);
void ReadWarm2Setting(void);
void ReadNormalSetting(void);
void ReadCool1Setting(void);
void ReadCool2Setting(void);
void ReadSRGBSetting(void);
extern Bool ExecuteKeyEvent(MenuItemActionType menuAction);
#if FreeSyncSwitchEDID
extern Bool  FreeSyncEDIDSwitch(BYTE Input, BYTE OnOff);
#endif
#if Enable_Expansion
void SetExpansionMode(void);
Bool AdjustExpansionMode(MenuItemActionType action);
#endif
WORD DecIncValue(MenuItemActionType action, WORD value, WORD minValue, WORD maxValue, BYTE step);
WORD GetScale100Value(WORD value, WORD minValue, WORD maxValue);
void SetYCMColor(MenuItemActionType action, WORD color, WORD value);
void SetECO(void);
void ReadColorTempSetting(void);
void ReadUserSetting(void);
extern void mStar_SetUserPref(void);
#if Enable_Gamma
extern void mStar_SetupGamma(BYTE GamaMode);
#endif
#if ENABLE_DeltaE
extern void LoadDeltaEColorMode(BOOL bWindow, BYTE ModeIndex, BOOL Enable);//Hans 120223 need modify
#endif




#if  ENABLE_OSD_LowBlueLight
WORD DecIncValueCirculate( MenuItemActionType action, WORD value, WORD minValue, WORD maxValue, BYTE step );
#endif
#if 0
extern Bool AdjustSuperResolution(void);
extern Bool SetSR_DEMOSize(BYTE ucSize, WORD DEMO_Hsize);
#endif
//void Save9300KSetting(void);
//void Save6500KSetting(void);

BYTE* code ColorTempPtr[][5] =
{
	{ &UserPrefRedColorWarm1, &UserPrefGreenColorWarm1, &UserPrefBlueColorWarm1},
	#if CT_7500K_ENABLE
	{&UserPrefRedColorNormal, &UserPrefGreenColorNormal, &UserPrefBlueColorNormal},
	#endif
	{&UserPrefRedColorCool1, &UserPrefGreenColorCool1, &UserPrefBlueColorCool1},
	#if CT_sRGB_ENABLE
	{&UserPrefRedColorSRGB, &UserPrefGreenColorSRGB, &UserPrefBlueColorSRGB},
	#endif
	{&UserPrefRedColorUser, &UserPrefGreenColorUser, &UserPrefBlueColorUser},
};

#if LowBlueLightType == LowBlueLight_SharpFunc
BYTE code LBLColorTempPtr[5][3] =
{
	{128, 128, 128},
	{128, 128, 118},
	{128, 128, 108},
	{128, 128, 98},
	{128, 128, 88},
};
#endif

static  xdata g8TempValue;

#if MWEFunction
//////////////////////////////////////////////////////////////////////////
// Matrix for convert to sRGB space
//////////////////////////////////////////////////////////////////////////
code short tSRGB[3][3] =
{
	{ 1096, -43, -28 }, // R  1.0694, -0.0424, -0.0270
	{ - 21,   1063, -18 }, // G -0.0204,  1.0376, -0.0172
	{ - 1,   34,   991 }  // B -0.0009,  0.0330,  0.9679

};
code short tNormalColorCorrectionMatrix[3][3] =
{
	{ 1024,    0,      	0},
	{	  0,	1024,     	0},
	{    0,     0,		1024}
};


//DLC Table......
BYTE code t_MWEDLC_Linear_Table[] =
{
	0x07, 0x17, 0x27, 0x37, 0x47, 0x57, 0x67, 0x77, 0x87, 0x97, 0xA7, 0xB7, 0xC7, 0xD7, 0xE7, 0xF7,
	0x87, 0x9B, 0x0F, 0xC2, 0xBD, 0x4E, 0xC6, 0xFD, 0xF3, 0x3E, 0xE9, 0x35, 0x75, 0xED, 0x76, 0x8D,
	0xC1, 0x74, 0xD4, 0x3C, 0x3A, 0x18, 0xE0, 0x0A, 0xD6, 0xE3, 0x33, 0x0C, 0x0A, 0x84, 0xB7, 0xA0,
};
code short t_Normal_ColorSettingTable[][3] =
{
	0x0400, 0x0000, 0x0000, 0x0000, 0x0400, 0x0000, 0x0000, 0x0000,
	0x0400, -0x03CC, 0x03CC, -0x00A6, 0x02B3, -0x0534, 0x06CB, -0x06C1,
	-0x07B3, 0x057D, 0x0676, -0x065D, 0x0289, 0x0336, -0x0106, 0x0015,
	-0x0831, 0x0100, -0x0000, 0x0000, -0x0000, 0x0000, 0x0000, 0x0000,
};



#if 0
void IndependentColorControl(void)
{
	BYTE i, j;
	#if CHIP_ID>= CHIP_TSUMV
	// 111129 coding
	for(i = 0; i < 3; i++)	// define range R/G/B
		msWriteByte(SC9_04 + i, tColorRangeTbl[i]);
	for(i = 0; i < 6; i++) // active range R/G/B/C/M/Y
		msWriteByte(SC9_08 + i, tColorActiveRangeTbl[i]);
	if (FullEnhanceFlag )
		j = 0;
	else if (SkinFlag )
		j = 1;
	else if(BlueFlag )
		j = 2;
	else if(GreenFlag )
		j = 3;
	else if ( ColorAutoDetectFlag)
		j = 4;
	for(i = 0; i < 6; i++) // saturation R/G/B/C/M/Y
		msWriteByte(SC9_14 + i, tColorControlSatTbl[j][i]);
	for(i = 0; i < 6; i++) // hue R/G/B/C/M/Y
		msWriteByte(SC9_0E+i, tColorControlHueTbl[j][i]);
	for(i = 0; i < 6; i++) // brightness R/G/B/C/M/Y
		msWriteByte(SC9_1A + i, tColorControlBriTbl[j][i]);
	#elif CHIP_ID==CHIP_TSUMU
	// 111129 coding
	for(i = 0; i < 3; i++) // define range R/G/B
		msWriteByte(SC9_04 + i, tColorRangeTbl[i]);
	for(i = 0; i < 6; i++) // active range R/G/B/C/M/Y
		msWriteByte(SC9_08 + i, tColorActiveRangeTbl[i]);
	if (FullEnhanceFlag )
		j = 0;
	else if (SkinFlag )
		j = 1;
	else if(BlueFlag )
		j = 2;
	else if(GreenFlag )
		j = 3;
	else if ( ColorAutoDetectFlag)
		j = 4;
	for(i = 0; i < 6; i++) // saturation R/G/B/C/M/Y
		msWriteByte(SC9_14 + i, tColorControlSatTbl[j][i]);
	for(i = 0; i < 6; i++) // hue R/G/B/C/M/Y
		msWriteByte(SC9_0E+i, tColorControlHueTbl[j][i]);
	for(i = 0; i < 6; i++) // brightness R/G/B/C/M/Y
		msWriteByte(SC9_1A + i, tColorControlBriTbl[j][i]);
	#else
	// 111129 coding
	for(i = 0; i < 3; i++)	// define range R/G/B
		msWriteByte(SC6_31 + i, tColorRangeTbl[i]);
	for(i = 0; i < 6; i++) // active range R/G/B/C/M/Y
		msWriteByte(SC6_34 + i, tColorActiveRangeTbl[i]);
	if (FullEnhanceFlag )
		j = 0;
	else if (SkinFlag )
		j = 1;
	else if(BlueFlag )
		j = 2;
	else if(GreenFlag )
		j = 3;
	else if ( ColorAutoDetectFlag)
		j = 4;
	for(i = 0; i < 6; i++) // saturation R/G/B/C/M/Y
		msWriteByte(SC6_3A + i, tColorControlSatTbl[j][i]);
	for(i = 0; i < 6; i++) // hue R/G/B/C/M/Y
		msWriteByte(SC6_40 + i, tColorControlHueTbl[j][i]);
	for(i = 0; i < 6; i++) // brightness R/G/B/C/M/Y
		msWriteByte(SC6_46 + i, tColorControlBriTbl[j][i]);
	#endif
	if(DemoFlag)
	{
		ICE_MAIN_CTRL(0);
		ICE_SUB_CTRL(1);
	}
	else
	{
		ICE_SUB_CTRL(0);
		ICE_MAIN_CTRL(1);
	}
}

#if !ENABLE_HDMI
void SetColorBoostWindow(BYTE mode)
{
	if (DemoFlag)
		mode = COLORBOOST_HALF;
	if (mode != COLORBOOST_OFF)
	{
		if (DemoFlag)
			msAdjustVideoContrast( SUB_WINDOW, DefContrastBase + DefContrast );
		else
			msAdjustVideoContrast( SUB_WINDOW, DefContrastBase + UserPrefContrast );
		if (mode == COLORBOOST_HALF)
		{
			UserPrefBFHSize = PanelWidth / 2;
			UserPrefBFVSize = PanelHeight;
			UserPrefBFHStart = 0;
			UserPrefBFVStart = 0;
		}
		else if (mode == COLORBOOST_FULL)
		{
			UserPrefBFHSize = PanelWidth;
			UserPrefBFVSize = PanelHeight;
			UserPrefBFHStart = 0;
			UserPrefBFVStart = 0;
		}
		if(DemoFlag)
		{
			msAccSetup(UserPrefBFHStart, UserPrefBFHSize, UserPrefBFVStart, UserPrefBFVSize);
			msAccOnOff(1);
		}
	}
	else
		// COLORBOOST_OFF
	{
		msAccOnOff(0);
	}
}
#endif
void SetColorEnhance(bit enable)
{
	BYTE *pColorTable;
	enable = 1;
	if (UserPrefDcrMode)
	{
		pColorTable = ( BYTE * )t_Normal_ColorSettingTable;
		LoadACETable(SUB_WINDOW, pColorTable, DefHue, DefSaturation, 0x80 ); //  UserPrefSubContrast  );
		msAccOnOff(1);
		msDlcOnOff(1);
	}
	else if (FullEnhanceFlag || SkinFlag || BlueFlag || GreenFlag || DemoFlag || ColorAutoDetectFlag)
	{
		if (FullEnhanceFlag || ColorAutoDetectFlag || GreenFlag || BlueFlag || SkinFlag)
			IndependentColorControl();
		else
		{
			//msWriteByte(0x00, 0x06);
			//msWriteByte(0x30, 0x00);
			//msWriteByte(0x00, 0x00);
			ICE_MAIN_CTRL(0);
			ICE_SUB_CTRL(0);
		}
		if (GreenFlag || SkinFlag)
		{
			//msWriteByte(BK0_00, 0x03);
			//msWriteByte(BK3_72, 0x6a);
			//msWriteByte(BK3_73, 0x6a);
			//msWriteByte(BK3_74, 0x6a);
			//msWriteByte(BK0_00, 0x00);
			msAdjustSubBrightness(SUB_WINDOW, 0x6a, 0x6a, 0x6a);
		}
		else if (ColorAutoDetectFlag)
		{
			//msWriteByte(BK0_00, 0x03);
			//msWriteByte(BK3_72, 0x60);
			//msWriteByte(BK3_73, 0x60);
			//msWriteByte(BK3_74, 0x60);
			//msWriteByte(BK0_00, 0x00);
			msAdjustSubBrightness(SUB_WINDOW, 0x60, 0x60, 0x60);
		}
		else
		{
			//msWriteByte(BK0_00, 0x03);
			//msWriteByte(BK3_72, 0x70);
			//msWriteByte(BK3_73, 0x70);
			//msWriteByte(BK3_74, 0x70);
			//msWriteByte(BK0_00, 0x00);
			msAdjustSubBrightness(SUB_WINDOW, 0x70, 0x70, 0x70);
		}
	}
	else
	{
		//msWriteByte(0x00, 0x06);
		//msWriteByte(0x30, 0x00);
		//msWriteByte(0x00, 0x00);
		ICE_MAIN_CTRL(0);
		ICE_SUB_CTRL(0);
	}
}

#if ENABLE_HDMI
void SetColorBoostWin( BYTE mode )
{
	if( DemoFlag)
		mode =  COLORBOOST_HALF;
	if( mode != COLORBOOST_OFF)
	{
		if(IsColorspaceRGB() && !SETUP_PATH_R2Y())	//130608 xiandi
			msAdjustPCContrast( MAIN_WINDOW, UserPrefContrast );	//120611 Modify
		else
			msAdjustVideoContrast( MAIN_WINDOW, UserPrefContrast );	//120611 Modify
		//msAdjustVideoContrast( SUB_WINDOW, DefContrastBase + UserPrefContrast );
		if (DemoFlag)	//120922 Modify
			msAdjustVideoContrast( SUB_WINDOW, DefContrastBase + DefContrast );
		if(mode == COLORBOOST_HALF )
		{
			UserPrefBFHSize = PanelWidth / 2;
			UserPrefBFVSize = PanelHeight;
			UserPrefBFHStart = 0;
			UserPrefBFVStart = 0;
		}
		else if(mode == COLORBOOST_FULL)
		{
			UserPrefBFHSize = PanelWidth ;
			UserPrefBFVSize = PanelHeight;
			UserPrefBFHStart = 0;
			UserPrefBFVStart = 0;
		}
		if(DemoFlag)
		{
			msAccSetup( UserPrefBFHStart, UserPrefBFHSize, UserPrefBFVStart, UserPrefBFVSize );
			if(IsColorspaceRGB())	//130608 xiandi
				msAccOnOff(1);
			else
			{
				//130110_23 Henry
				msWriteByte(SC0_5C, msReadByte(SC0_5C) | BIT3);
				#if CHIP_ID==CHIP_TSUMU	//121211 Modify
				msAccOnOff( 1 );
				#endif
			}
		}
		else
		{
			if(IsColorspaceRGB())	//130608 xiandi
				msAccOnOff(0);
			else
			{
				//130110_23 Henry
				msWriteByte(SC0_5C, msReadByte(SC0_5C) & ~BIT3);
				#if CHIP_ID==CHIP_TSUMU	//121211 Modify
				msAccOnOff( 0 );
				#endif
			}
		}
	}
	else // COLORBOOST_OFF
	{
		msAccSetup( 0, 0, 0, 0 );
		//msAccOnOff( 0 );
	}
}

void SetColorMatrix( void )
{
	BYTE *pColorTable;
	if( UserPrefDcrMode)
	{
		pColorTable = ( BYTE * )t_Normal_ColorSettingTable;
		LoadACETable(SUB_WINDOW, pColorTable, UserPrefHue, UserPrefSaturation, 0x80 ); //  UserPrefSubContrast  );
		//msAccOnOff( 1 );
		//msDlcOnOff( 1 );
	}
	else  if ( FullEnhanceFlag || SkinFlag || BlueFlag || GreenFlag || DemoFlag || ColorAutoDetectFlag)  //NormalSkin+GreenENhance+BlueEnhance
	{
		if (FullEnhanceFlag || ColorAutoDetectFlag || GreenFlag || BlueFlag || SkinFlag)
			IndependentColorControl();
		else
		{
			//msWriteByte(0x00, 0x06);
			//msWriteByte(0x30, 0x00);
			//msWriteByte(0x00, 0x00);
			ICE_MAIN_CTRL(0);
			ICE_SUB_CTRL(0);
		}
		if (GreenFlag || SkinFlag)
		{
			//msWriteByte(BK0_00, 0x03);
			//msWriteByte(BK3_72, 0x6a);
			//msWriteByte(BK3_73, 0x6a);
			//msWriteByte(BK3_74, 0x6a);
			//msWriteByte(BK0_00, 0x00);
			msAdjustSubBrightness(SUB_WINDOW, 0x7a, 0x7a, 0x7a);
			// msAdjustSubBrightness(SUB_WINDOW, 0x6a, 0x6a, 0x6a);
		}
		else if (ColorAutoDetectFlag)
		{
			//msWriteByte(BK0_00, 0x03);
			//msWriteByte(BK3_72, 0x60);
			//msWriteByte(BK3_73, 0x60);
			//msWriteByte(BK3_74, 0x60);
			//msWriteByte(BK0_00, 0x00);
			msAdjustSubBrightness(SUB_WINDOW, 0x79, 0x79, 0x79);
			//  msAdjustSubBrightness(SUB_WINDOW, 0x60, 0x60, 0x60);
		}
		else
		{
			//msWriteByte(BK0_00, 0x03);
			//msWriteByte(BK3_72, 0x70);
			//msWriteByte(BK3_73, 0x70);
			//msWriteByte(BK3_74, 0x70);
			//msWriteByte(BK0_00, 0x00);
			msAdjustSubBrightness(SUB_WINDOW, 0x7C, 0x7C, 0x7C);
		}
	}
	else
	{
		//msWriteByte(0x00, 0x06);
		//msWriteByte(0x30, 0x00);
		//msWriteByte(0x00, 0x00);
		ICE_MAIN_CTRL(0);
		ICE_SUB_CTRL(0);
	}
}

void SetColorSpace( void )
{
	#if ENABLE_HDMI
	BYTE XDATA ucDomain;
	#endif
	#if ENABLE_HDMI
	ucDomain = 0x00;
	if(!IsColorspaceRGB())	//130608 xiandi
		ucDomain = 0xFF;
	#endif
	if ( DemoFlag || BlueFlag || SkinFlag || GreenFlag || ColorAutoDetectFlag || FullEnhanceFlag)
	{
		#if ENABLE_HDMI
		if (ucDomain)
		{
			if(DemoFlag)
			{
				//SetMainWinVideoDomain(ucDomain);		//SetMainWinColorControl(ucDomain);
				msWriteByte(SC0_5C, msReadByte(0x5C) | BIT3);
			}
			else
			{
				msWriteByte(0x02, msReadByte(0x02) | BIT3);
				msWriteByte(SC0_5C, msReadByte(0x5C) & ~BIT3);
			}
		}
		else
		#endif
			if(DemoFlag)
				msAccOnOff( 1 );
	}
	else
	{
		#if ENABLE_HDMI && CHIP_ID!=CHIP_TSUMU	//121211 Modify
		if (ucDomain)
			msWriteByte(SC0_5C, msReadByte(0x5C) & ~BIT3);
		else
		#endif
			msAccOnOff(0);
		#if ENABLE_HDMI
		//SetMainWinVideoDomain(0);	//SetMainWinColorControl(0);
		if (ucDomain)
			msWriteByte(0x02, msReadByte(0x02) | BIT3);
		#endif
	}
}
#endif

//================================================================================
Bool AdjustColorBoostMode(MenuItemActionType action)
{
	action = 0;
	if (!DemoFlag)
	{
		Clr_DemoFlag();
	}
	Clr_SkinFlag();
	Clr_GreenFlag();
	Clr_BlueFlag();
	Clr_ColorAutoDetectFlag();
	Clr_PictureBoostFlag();
	//if (UserPrefDcrMode)
	//SetECO();
	UserPrefDcrMode = 0;
	UserPrefECOMode = ECO_Standard;
	SetECO();
	#if ENABLE_HDMI
	msDlcOnOff(_DISABLE);
	#endif
	if (FullEnhanceFlag)
		// clr
	{
		Clr_FullEnhanceFlag();
		#if ENABLE_HDMI
		SetColorBoostWin(COLORBOOST_OFF);
		#else
		SetColorBoostWindow(COLORBOOST_OFF);
		#endif
	}
	else
		// set
	{
		Set_FullEnhanceFlag();
		#if ENABLE_HDMI
		SetColorBoostWin(COLORBOOST_FULL);
		#else
		SetColorBoostWindow(COLORBOOST_FULL);
		#endif
	}
	#if ENABLE_HDMI
	SetColorMatrix();
	SetColorSpace();
	#else
	SetColorEnhance(1);
	#endif
	#if !USEFLASH
	NVRam_WriteByte(nvrMonitorAddr(ColorFlag), UserPrefColorFlags);
	#else
	UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
	#endif
	//Benz 2007.4.24   9:50:19		Osd_Draw4Num(7,1,UserPrefColorFlags);
	return TRUE;
}

//================================================================================
Bool AdjustSkinProtectMode(MenuItemActionType action)
{
	action = action;
	if (!DemoFlag)
	{
		Clr_DemoFlag();
	}
	Clr_GreenFlag();
	Clr_FullEnhanceFlag();
	Clr_BlueFlag();
	Clr_ColorAutoDetectFlag();
	Clr_PictureBoostFlag();
	//if (UserPrefDcrMode)
	//SetECO();
	UserPrefDcrMode = 0;
	UserPrefECOMode = ECO_Standard;
	SetECO();
	#if ENABLE_HDMI
	msDlcOnOff(_DISABLE);
	#endif
	if (SkinFlag)
	{
		Clr_SkinFlag();
		#if ENABLE_HDMI
		SetColorBoostWin(COLORBOOST_OFF);
		#else
		SetColorBoostWindow(COLORBOOST_OFF);
		#endif
	}
	else
	{
		Set_SkinFlag();
		#if ENABLE_HDMI
		SetColorBoostWin(COLORBOOST_FULL);
		#else
		SetColorBoostWindow(COLORBOOST_FULL);
		#endif
	}
	#if ENABLE_HDMI
	SetColorMatrix();
	SetColorSpace();
	#else
	SetColorEnhance(1);
	#endif
	#if !USEFLASH
	NVRam_WriteByte(nvrMonitorAddr(ColorFlag), UserPrefColorFlags);
	#else
	UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
	#endif
	//Benz 2007.4.24   9:50:24	Osd_Draw4Num(6,1,UserPrefColorFlags);
	return TRUE;
}
Bool AdjustGreenEnhanceMode(MenuItemActionType action)
{
	action = action;
	if (!DemoFlag)
	{
		Clr_DemoFlag();
	}
	Clr_SkinFlag();
	Clr_FullEnhanceFlag();
	Clr_BlueFlag();
	Clr_ColorAutoDetectFlag();
	Clr_PictureBoostFlag();
	//if (UserPrefDcrMode)
	//SetECO();
	UserPrefDcrMode = 0;
	UserPrefECOMode = ECO_Standard;
	SetECO();
	#if ENABLE_HDMI
	msDlcOnOff(_DISABLE);
	#endif
	if (GreenFlag)
	{
		Clr_GreenFlag();
		#if ENABLE_HDMI
		SetColorBoostWin(COLORBOOST_OFF);
		#else
		SetColorBoostWindow(COLORBOOST_OFF);
		#endif
	}
	else
	{
		Set_GreenFlag();
		#if ENABLE_HDMI
		SetColorBoostWin(COLORBOOST_FULL);
		#else
		SetColorBoostWindow(COLORBOOST_FULL);
		#endif
	}
	#if ENABLE_HDMI
	SetColorMatrix();
	SetColorSpace();
	#else
	SetColorEnhance(1);
	#endif
	#if !USEFLASH
	NVRam_WriteByte(nvrMonitorAddr(ColorFlag), UserPrefColorFlags);
	#else
	UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
	#endif
	//Benz 2007.4.24   9:50:28		Osd_Draw4Num(5,1,UserPrefColorFlags);
	return TRUE;
}
Bool AdjustBlueEnhanceMode(MenuItemActionType action)
{
	action = action;
	if (!DemoFlag)
	{
		Clr_DemoFlag();
	}
	// color boost menu
	Clr_FullEnhanceFlag();
	Clr_GreenFlag();
	Clr_SkinFlag();
	Clr_ColorAutoDetectFlag();
	// picture boost menu
	Clr_PictureBoostFlag();
	// DCR function
	//if (UserPrefDcrMode)
	//SetECO();
	UserPrefDcrMode = 0;
	UserPrefECOMode = ECO_Standard;
	SetECO();
	#if ENABLE_HDMI
	msDlcOnOff(_DISABLE);
	#endif
	if (BlueFlag)
	{
		Clr_BlueFlag();
		#if ENABLE_HDMI
		SetColorBoostWin(COLORBOOST_OFF);
		#else
		SetColorBoostWindow(COLORBOOST_OFF);
		#endif
	}
	else
	{
		Set_BlueFlag();
		#if ENABLE_HDMI
		SetColorBoostWin(COLORBOOST_FULL);
		#else
		SetColorBoostWindow(COLORBOOST_FULL);
		#endif
	}
	#if ENABLE_HDMI
	SetColorMatrix();
	SetColorSpace();
	#else
	SetColorEnhance(1);
	#endif
	#if !USEFLASH
	NVRam_WriteByte(nvrMonitorAddr(ColorFlag), UserPrefColorFlags);
	#else
	UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
	#endif
	//Benz 2007.4.24   9:50:33		Osd_Draw4Num(4,1,UserPrefColorFlags);
	return TRUE;
}

Bool AdjustAutoDetectMode(MenuItemActionType action)
{
	action = action;
	if (!DemoFlag)
		// when demo on, don't clear the demo flag
	{
		Clr_DemoFlag();
	}
	// color boost menu
	Clr_FullEnhanceFlag();
	Clr_GreenFlag();
	Clr_BlueFlag();
	Clr_SkinFlag();
	// picture boost menu
	Clr_PictureBoostFlag();
	// DCR function
	//if (UserPrefDcrMode)
	//SetECO();
	UserPrefDcrMode = 0;
	UserPrefECOMode = ECO_Standard;
	SetECO();
	#if ENABLE_HDMI
	msDlcOnOff(_DISABLE);
	#endif
	if (ColorAutoDetectFlag)
	{
		Clr_ColorAutoDetectFlag();
		#if ENABLE_HDMI
		SetColorBoostWin(COLORBOOST_OFF);
		#else
		msDlcOnOff(_DISABLE);
		SetColorBoostWindow(COLORBOOST_OFF);
		#endif
	}
	else
	{
		Set_ColorAutoDetectFlag();
		#if ENABLE_HDMI
		SetColorBoostWin(COLORBOOST_FULL);
		#else
		LoadDLCTable(t_MWEDLC_Linear_Table);
		msDlcOnOff(_DISABLE);
		SetColorBoostWindow(COLORBOOST_FULL);
		#endif
	}
	#if ENABLE_HDMI
	SetColorMatrix();
	SetColorSpace();
	#else
	SetColorEnhance(1);
	#endif
	#if !USEFLASH
	NVRam_WriteByte(nvrMonitorAddr(ColorFlag), UserPrefColorFlags);
	#else
	UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
	#endif
	//Benz 2007.4.24   9:50:40		Osd_Draw4Num(3,1,UserPrefColorFlags);
	return TRUE;
}


#if 0
Bool AdjustDCBOff( MenuItemActionType action )
{
	action = action;
	Clr_FullEnhanceFlag();
	Clr_GreenFlag();
	Clr_BlueFlag();
	Clr_SkinFlag();
	Clr_ColorAutoDetectFlag();
	Clr_PictureBoostFlag();
	UserPrefDcrMode = 0;
	UserPrefECOMode = ECO_Standard;
	{
		ICE_MAIN_CTRL(0);
		ICE_SUB_CTRL(0);
	}
	SetECO();
	if(DemoFlag)	//130624 Modify
	{
		msAdjustSubBrightness(SUB_WINDOW, 0x7c, 0x7c, 0x7c);
	}
	return TRUE;
}
#endif




#if 1  //2006-08-29 Andy
Bool SetBFSize(BYTE ucSize)
{
	#if ENABLE_HDMI
	BYTE XDATA ucDomain;
	#endif
	#if ENABLE_HDMI
	ucDomain = 0x00;
	if(!IsColorspaceRGB())	//130608 xiandi
		ucDomain = 0xFF;
	#endif
	if (!PictureBoostFlag)
	{
		#if !ENABLE_HDMI
		msAccOnOff(0);
		msDlcOnOff(0);
		#endif
		UserPrefBFHSize = 0;
		UserPrefBFVSize = 0;
		UserPrefBFHStart = 0;
		UserPrefBFVStart = 0;
		UserPrefBFSize = ucSize = 1; //Benz 2007.4.14   14:34:23
	}
	else
	{
		if (ucSize == 1)  // H:5 V:5
		{
			UserPrefBFHSize = (DISPLAY_WIDTH + 4) / 8;	//120204 Modify
			UserPrefBFVSize = PanelHeight / 8; // / 5;
		}
		else if (ucSize == 2)          // H:5 V:3
		{
			UserPrefBFHSize = DISPLAY_WIDTH / 5;		//120204 Modify
			UserPrefBFVSize = PanelHeight / 5; // / 3;
		}
		else if (ucSize == 3)     //  H4 V:4
		{
			UserPrefBFHSize = DISPLAY_WIDTH / 4;		//120204 Modify
			UserPrefBFVSize = PanelHeight / 4;
		}
		else if (ucSize == 4)       //  H3 V:3
		{
			UserPrefBFHSize = DISPLAY_WIDTH / 3;		//120204 Modify
			UserPrefBFVSize = PanelHeight / 3;
		}
		else if (ucSize == 5)        //  H2 V:2
		{
			UserPrefBFHSize = DISPLAY_WIDTH / 2;		//120204 Modify
			UserPrefBFVSize = PanelHeight / 2;
		}
		else if (ucSize == 6)        //  H2 V:1
		{
			UserPrefBFHSize = DISPLAY_WIDTH / 2;		//120204 Modify
			UserPrefBFVSize = PanelHeight;
		}
		else if (ucSize == 7)       //  Full
		{
			UserPrefBFHSize = DISPLAY_WIDTH;			//120204 Modify
			UserPrefBFVSize = PanelHeight;
		}
		else	//120204 Modify
		{
			UserPrefBFHStart = 0;
			UserPrefBFVStart = 0;
		}
		msAdjustVideoContrast( SUB_WINDOW, UserPrefSubContrast );
		msAccSetup(UserPrefBFHStart * ( DISPLAY_WIDTH - UserPrefBFHSize) / 20 + HSTART_OFFSET, (UserPrefBFHStart * ( DISPLAY_WIDTH - UserPrefBFHSize) / 20 + UserPrefBFHSize + HSTART_OFFSET), UserPrefBFVStart * ( PanelHeight - UserPrefBFVSize) / 20, (UserPrefBFVStart * ( PanelHeight - UserPrefBFVSize) / 20 + UserPrefBFVSize));	//120204 Modify
		#if ENABLE_HDMI
		//msAdjustSubBrightness( UserPrefSubBrightness );
		msAdjustSubBrightness( SUB_WINDOW, UserPrefSubBrightness, UserPrefSubBrightness, UserPrefSubBrightness );
		#else
		msAccOnOff(1);
		#endif
	}
	#if ENABLE_HDMI
	if ( PictureBoostFlag)
	{
		#if ENABLE_HDMI && CHIP_ID!=CHIP_TSUMU	//121211 Modify
		if (ucDomain)
		{
			// SetMainWinVideoDomain(ucDomain);	//SetMainWinColorControl(ucDomain);
			msWriteByte(SC0_5C, msReadByte(0x5C) | BIT3);
		}
		else
		#endif
			msAccOnOff( 1 );
	}
	else
	{
		#if ENABLE_HDMI && CHIP_ID!=CHIP_TSUMU	//121211 Modify
		if (ucDomain)
			msWriteByte(SC0_5C, msReadByte(0x5C) & ~BIT3);
		else
		#endif
			msAccOnOff(0);
		#if ENABLE_HDMI
		//SetMainWinVideoDomain(0);	//SetMainWinColorControl(0);
		if (ucDomain)
			msWriteByte(0x02, msReadByte(0x02) | BIT3);
		#endif
	}
	#endif
	return TRUE;
}

#if ENABLE_HDMI
Bool AdjustBrightFrameSize(BYTE ucSize)
{
	if ( ucSize == 1 )        // H:5 V:5
	{
		UserPrefBFHSize = DISPLAY_WIDTH / 8;	//120204 Modify
		UserPrefBFVSize = PanelHeight / 8; // / 5;// 20130109
	}
	else if ( ucSize == 2 ) // H:5 V:3
	{
		UserPrefBFHSize = DISPLAY_WIDTH / 5;	//120204 Modify
		UserPrefBFVSize = PanelHeight / 5; // / 3;// 20130109
	}
	else if ( ucSize == 3 ) //  H4 V:4
	{
		UserPrefBFHSize = DISPLAY_WIDTH / 4;	//120204 Modify
		UserPrefBFVSize = PanelHeight / 4;
	}
	else if ( ucSize == 4 ) //  H3 V:3
	{
		UserPrefBFHSize = DISPLAY_WIDTH / 3;	//120204 Modify
		UserPrefBFVSize = PanelHeight / 3;
	}
	else if ( ucSize == 5 ) //  H2 V:2
	{
		UserPrefBFHSize = DISPLAY_WIDTH / 2;	//120204 Modify
		UserPrefBFVSize = PanelHeight / 2;
	}
	else if ( ucSize == 6 ) //  H2 V:1
	{
		UserPrefBFHSize = DISPLAY_WIDTH / 2;	//120204 Modify
		UserPrefBFVSize = PanelHeight;
	}
	else if ( ucSize == 7 ) //  Full
	{
		UserPrefBFHSize = DISPLAY_WIDTH;		//120204 Modify
		UserPrefBFVSize = PanelHeight;
	}
	UserPrefBFHStart = 0;
	UserPrefBFVStart = 0;
	msAccSetup(UserPrefBFHStart * ( DISPLAY_WIDTH - UserPrefBFHSize) / 20 + HSTART_OFFSET, (UserPrefBFHStart * ( DISPLAY_WIDTH - UserPrefBFHSize) / 20 + UserPrefBFHSize + HSTART_OFFSET), UserPrefBFVStart * ( PanelHeight - UserPrefBFVSize) / 20, (UserPrefBFVStart * ( PanelHeight - UserPrefBFVSize) / 20 + UserPrefBFVSize));	//120204 Modify
	//msAccOnOff( 1 );
	#if CHIP_ID==CHIP_TSUMU	//121211 Modify
	msAccOnOff( 1 );
	#endif
	return TRUE;
}
#endif
//---------------------------------------------------------------
Bool AdjustBFSize(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefBFSize, 1, 7, 1);
	if (tempValue == UserPrefBFSize)
	{
		return FALSE;
	}
	UserPrefBFSize = tempValue;
	UserPrefBFHStart = 0;	//120204 Modify
	UserPrefBFVStart = 0;	//120204 Modify
	//printData("UserPrefBFSize=%d",UserPrefBFSize);
	#if ENABLE_HDMI
	AdjustBrightFrameSize(UserPrefBFSize);	//
	#else
	SetBFSize(UserPrefBFSize);//SetBFSize();
	#endif
	return TRUE;
}
WORD GetBFSizeValue(void)
{
	return GetScale100Value(UserPrefBFSize, 0, 7);
}
//---------------------------------------------------------------
Bool AdjustBFHstart(MenuItemActionType action)
{
	WORD tempValue;
	if (UserPrefBFSize == 1)
	{
		tempValue = DecIncValue(action, UserPrefBFHStart, 0, 20, 1);	//120112 Modify
	}
	else if (UserPrefBFSize == 2)
	{
		tempValue = DecIncValue(action, UserPrefBFHStart, 0, 20, 1);	//120112 Modify
	}
	else if (UserPrefBFSize == 3)
	{
		tempValue = DecIncValue(action, UserPrefBFHStart, 0, 20, 1);	//120112 Modify	//120112 Modify
	}
	else if (UserPrefBFSize == 4)
	{
		tempValue = DecIncValue(action, UserPrefBFHStart, 0, 20, 1);	//120112 Modify
	}
	else if (UserPrefBFSize == 5 || UserPrefBFSize == 6)
	{
		tempValue = DecIncValue(action, UserPrefBFHStart, 0, 20, 1);	//120112 Modify
	}
	else
	{
		tempValue = 0;
	}
	/*						//130123_2 Henry For Can Not Adjust BFPosition After 25 In DP Source
	            if (tempValue == UserPrefHStart)
	            {
	                return FALSE;
	            }
	*/
	UserPrefBFHStart = tempValue;
	tempValue = UserPrefBFHStart * ( DISPLAY_WIDTH - UserPrefBFHSize) / 20 + HSTART_OFFSET;	//120204 Modify
	msAccSetup(tempValue, (UserPrefBFHSize + tempValue), UserPrefBFVStart * ( DISPLAY_HEIGHT - UserPrefBFVSize) / 20, (UserPrefBFVStart * ( DISPLAY_HEIGHT - UserPrefBFVSize) / 20 + UserPrefBFVSize));	//120112 Modify
	return TRUE;
}
WORD GetBFHstartValue(void)
{
	if (UserPrefBFSize == 2)
	{
		return GetScale100Value(UserPrefBFHStart, 0, 20);	//120112 Modify
	}
	else if (UserPrefBFSize == 3)
	{
		return GetScale100Value(UserPrefBFHStart, 0, 20);	//120112 Modify
	}
	else if (UserPrefBFSize == 4)
	{
		return GetScale100Value(UserPrefBFHStart, 0, 20);	//120112 Modify
	}
	else if (UserPrefBFSize == 5 || UserPrefBFSize == 6)
	{
		return GetScale100Value(UserPrefBFHStart, 0, 20);	//120112 Modify
	}
	else if (UserPrefBFSize == 1)
	{
		return GetScale100Value(UserPrefBFHStart, 0, 20);	//120112 Modify
	}
	else
	{
		return 0;
	}
}
//---------------------------------------------------------------
Bool AdjustBFVstart(MenuItemActionType action)
{
	WORD tempValue;
	if (UserPrefBFSize == 6 || UserPrefBFSize == 7)
	{
		tempValue = 0;
	}
	else if (UserPrefBFSize == 1)
	{
		tempValue = DecIncValue(action, UserPrefBFVStart, 0, 20, 1);	//120112 Modify
	}
	else if (UserPrefBFSize == 2)
	{
		tempValue = DecIncValue(action, UserPrefBFVStart, 0, 20, 1);	//120112 Modify
	}
	else if (UserPrefBFSize == 4)
	{
		tempValue = DecIncValue(action, UserPrefBFVStart, 0, 20, 1);	//120112 Modify
	}
	else if (UserPrefBFSize == 3)
	{
		tempValue = DecIncValue(action, UserPrefBFVStart, 0, 20, 1);	//120112 Modify
	}
	else if (UserPrefBFSize == 5)
	{
		tempValue = DecIncValue(action, UserPrefBFVStart, 0, 20, 1);	//120112 Modify
	}
	/*
	if ( tempValue == UserPrefVStart )
	{
	return FALSE;
	}
	 */
	UserPrefBFVStart = tempValue;
	tempValue = UserPrefBFVStart * ( DISPLAY_HEIGHT - UserPrefBFVSize) / 20;	//120112 Modify		//130117 Henry
	//tempValue = UserPrefBFVStart * ( PanelHeight- UserPrefBFVSize) / 20;	//120112 Modify
	msAccSetup(UserPrefBFHStart * ( DISPLAY_WIDTH - UserPrefBFHSize) / 20 + HSTART_OFFSET, UserPrefBFHStart * ( DISPLAY_WIDTH - UserPrefBFHSize) / 20 + UserPrefBFHSize + HSTART_OFFSET, tempValue, (tempValue + UserPrefBFVSize));	//120204 Modify
	return TRUE;
}
WORD GetBFVstartValue(void)
{
	if (UserPrefBFSize == 1)
	{
		return GetScale100Value(UserPrefBFVStart, 0, 20);	//120112 Modify
	}
	else if (UserPrefBFSize == 2)
	{
		return GetScale100Value(UserPrefBFVStart, 0, 20);	//120112 Modify
	}
	else if (UserPrefBFSize == 4)
	{
		return GetScale100Value(UserPrefBFVStart, 0, 20);	//120112 Modify
	}
	else if (UserPrefBFSize == 3)
	{
		return GetScale100Value(UserPrefBFVStart, 0, 20);	//120112 Modify
	}
	else if (UserPrefBFSize == 5)
	{
		return GetScale100Value(UserPrefBFVStart, 0, 20);	//120112 Modify
	}
	else
	{
		return 0;
	}
}
//================================================================================
Bool AdjustBF_Switch(MenuItemActionType action)
{
	action = action;
	Clr_ColorAutoDetectFlag();
	Clr_FullEnhanceFlag();
	Clr_GreenFlag();
	Clr_BlueFlag();
	Clr_SkinFlag();
	Clr_DemoFlag();
	//if (UserPrefDcrMode)
	//SetECO();
	UserPrefDCBMode = DCBMode_Off;	//120204 Modify
	{
		ICE_MAIN_CTRL(0);				//120204 Modify
		ICE_SUB_CTRL(0);				//120204 Modify
	}
	UserPrefDcrMode = 0;
	#if CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF	//130705 xiandi
	msDCROnOff(UserPrefDcrMode, MAIN_WINDOW);
	#endif
	UserPrefECOMode = ECO_Standard;
	SetECO();
	#if ENABLE_HDMI
	msDlcOnOff(_DISABLE);
	#endif
	if (PictureBoostFlag)
	{
		//msWriteByteMask(SC7_40, 0, BIT4);
		Clr_PictureBoostFlag();
		#if ENABLE_HDMI
		UserPrefBFSize = 1 ;	// recall default setting=> BFSize=1, position(0,0)
		#endif
		SetBFSize(UserPrefBFSize);//SetBFSize();
		CSC_SUB_ENABLE(0);	//120204 Modify
	}
	else
	{
		Set_PictureBoostFlag();
		//msWriteByteMask(SC7_40, BIT4, BIT4);
		if(SETUP_PATH_RGB())			//121213 Modify
			CSC_SUB_ENABLE(1);
		else
			CSC_SUB_ENABLE(0);
		#if !ENABLE_HDMI
		UserPrefBFSize = 1; // recall default setting=> BFSize=1, position(0,0)
		#endif
		SetBFSize(UserPrefBFSize);//SetBFSize();
		#if !ENABLE_HDMI
		SetColorEnhance(1);
		#endif
		#if 1//!ENABLE_HDMI
		//msAdjustSubBrightness(UserPrefSubBrightness);
		//msAdjustSubBrightness( SUB_WINDOW, UserPrefSubBrightness, UserPrefSubBrightness, UserPrefSubBrightness );
		//LoadACETable(SUB_WINDOW, t_Normal_ColorSettingTable, UserPrefHue, UserPrefSaturation, UserPrefSubContrast ); //  UserPrefSubContrast  );
		mStar_AdjustContrast(UserPrefContrast);	//120524 Modify
		//msAdjustVideoContrastRGB(SUB_WINDOW, UserPrefSubContrast, 0x80, 0x80, 0x80);	//120524 Modify
		msAdjustSubBrightness( SUB_WINDOW, UserPrefSubBrightness, UserPrefSubBrightness, UserPrefSubBrightness );
		LoadACETable(SUB_WINDOW, ( BYTE * )t_Normal_ColorSettingTable, UserPrefHue, UserPrefSaturation, UserPrefSubContrast ); //  UserPrefSubContrast  );
		//LoadACETable ( MAIN_WINDOW, ( BYTE * ) t_Normal_ColorSettingTable, DefHue, DefSaturation, UserPrefContrast ); // /UserPrefSubContrast
		#endif
	}
	#if !USEFLASH
	NVRam_WriteByte(nvrMonitorAddr(ColorFlag), UserPrefColorFlags);
	#else
	UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
	#endif
	return TRUE;
}
#endif
//---------------------------------------------------------------
#if 0
extern XDATA BYTE g_ucVideoSaturation;
extern XDATA BYTE g_ucVideoHue;
//================================================================================
Bool AdjustHue(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefHue, MIN_VIDEO_HUE, MAX_VIDEO_HUE, 1);
	if (tempValue == UserPrefHue)
	{
		return FALSE;
	}
	UserPrefHue = tempValue;
	msAdjustVideoHue( SUB_WINDOW, UserPrefHue );
	return TRUE;
}
WORD GetHue100Value(void)
{
	return GetScale100Value(UserPrefHue, MIN_VIDEO_HUE, MAX_VIDEO_HUE);
}
//================================================================================
Bool AdjustSaturation(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefSaturation, MIN_VIDEO_SATURATION, MAX_VIDEO_SATURATION, 1);
	if (tempValue == UserPrefSaturation)
	{
		return FALSE;
	}
	UserPrefSaturation = tempValue;
	msAdjustVideoSaturation( SUB_WINDOW, UserPrefSaturation );
	return TRUE;
}
WORD GetSaturation100Value(void)
{
	return GetScale100Value(UserPrefSaturation, MIN_VIDEO_SATURATION, MAX_VIDEO_SATURATION);
}

#endif
//================================================================================
//================================================================================
Bool AdjustSubContrast(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefSubContrast, MinSubContrast, MaxSubContrast, 2);
	if (tempValue == UserPrefSubContrast)
	{
		return FALSE;
	}
	UserPrefSubContrast = tempValue;
	msAdjustVideoContrast( SUB_WINDOW, UserPrefSubContrast );
	//NVRam_WriteByte( nvrMonitorAddr( SubContrast ), UserPrefSubContrast);
	return TRUE;
}
WORD GetSubContrast100Value(void)
{
	return GetScale100Value(UserPrefSubContrast, MinSubContrast, MaxSubContrast);
}
//================================================================================
Bool AdjustSubBrightness(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefSubBrightness, MinSubBrightness, MaxSubBrightness, 1);	//111223 Modify
	if (tempValue == UserPrefSubBrightness)
	{
		return FALSE;
	}
	UserPrefSubBrightness = tempValue;
	//msAdjustSubBrightness(UserPrefSubBrightness);
	msAdjustSubBrightness( SUB_WINDOW, UserPrefSubBrightness, UserPrefSubBrightness, UserPrefSubBrightness );
	return TRUE;
}
#if 0
WORD GetSubBrightnessValue(void)
{
	return UserPrefSubBrightness;
}
#endif
WORD GetSubBrightness100Value(void)
{
	return GetScale100Value(UserPrefSubBrightness, MinSubBrightness, MaxSubBrightness);
}
#endif
#endif
//================================================================================
WORD DecIncValue(MenuItemActionType action, WORD value, WORD minValue, WORD maxValue, BYTE step)
{
	if (action == MIA_IncValue || action == MIA_InvDecValue)
	{
		if (value >= maxValue)
		{
			return value;
		}
		minValue = value + step;
		if (minValue > maxValue)
		{
			minValue = maxValue;
		}
		value = minValue;
	}
	else
		// Decrease value
	{
		if (value <= minValue)
		{
			return value;
		}
		maxValue = value - step;
		if (maxValue < minValue)
		{
			maxValue = minValue;
		}
		value = maxValue;
	}
	return value;
}
WORD GetScale100Value(WORD value, WORD minValue, WORD maxValue)
{
	maxValue = (maxValue <= minValue) ? minValue : (maxValue - minValue);
	//maxValue = maxValue - minValue;
	value = value - minValue;
	if (value > 650)
	{
		value /= 2;
		maxValue /= 2;
	}
	value = ((WORD)value * 100 + maxValue / 2) / maxValue;
	value %= 101;
	return value;
}
extern BYTE  xdata MenuItemIndex;
extern BYTE  xdata MenuPageIndex;
Bool ResetOsdTimer(void)
{
	if (!FactoryModeFlag)
	{
		OsdCounter = UserPrefOsdTime;
	}
	#if Hot_Corss_ColorSelect|| Hot_Corss_FY_ColorSelect || Hot_Corss_FND_Select
	if (MenuPageIndex == HotCorssMenu)
		OsdCounter = 0;
	#endif
	//  else if(MenuPageIndex == SettingMenu && MenuItemIndex == 0) // 20130409 TPV request
//   {
//OsdCounter = 10;
//   }
	return TRUE;
}
Bool EnablePowerDownCounter(void)
{
	{
		#if  (DP_PRETEST || HDMI_PRETEST)
		PowerDownCounter = 30;
		#else
		PowerDownCounter = 6;
		#endif
	}
	//Set_ForcePowerSavingFlag();
	#if ENABLE_DEBUG
	printData("PowerDownCounter:       %d", PowerDownCounter);
	#endif
	return TRUE;
}

#if 0  //2006-08-10 Andy
Bool PowerOffSystem(void)
{
	printMsg("turn off");
	Power_TurnOffLed();
	Power_PowerOffSystem();
	Clr_PowerOnFlag();
	Clr_FactoryModeFlag();
	Clr_DisplayLogoFlag();
	Clr_DoModeSettingFlag();
	// printData("Power-off Monitor Flag %d",MonitorFlags);
	NVRam_WriteByte(nvrMonitorAddr(MonitorFlag), MonitorFlags);
	return TRUE;
}
#endif
Bool PowerOffSystem(void)
{
	Clr_PowerOnFlag();
	Clr_FactoryModeFlag();
	Clr_BurninModeFlag();
	Clr_DisplayLogoFlag();
	Clr_DoModeSettingFlag();
	Clr_DoBurninModeFlag();
	// 120426 coding addition
	Clr_BackToUnsupportFlag();
	Clr_BackToStandbyFlag();
	Power_TurnOffLed();
	// 090819 coding, dc off should set ddc wp to protect
	hw_SetDDC_WP();
	#if MWEFunction     //110223 Modify for turn on BF and change to the source of nosignal will show garbage
	msAccSetup( 0, 0, 0, 0 ); //110408 Modify
	msAccOnOff(0);
	#endif
	#if ESaverPowerDownFunc
	ESaverPowerDownCounter = 0;
	#endif
	#if ENABLE_HDMI
	mstar_HDMIAudioMute(0);
	hw_SetMute();
	#endif
	#if !USEFLASH
	NVRam_WriteByte(nvrMonitorAddr(MonitorFlag), MonitorFlags);
	#else
	SaveMonitorSetting();
	#endif
	#if 0//ENABLE_HDCP
	msDisableHDCP();
	#endif
	#if !MS_PM	//120921 Modify for power consumption
	#if ENABLE_HDCP // 120531 coding reserved
	msPullLowHPD2();
	#endif
	#endif
	#if ENABLE_DP_INPUT  //130815 xiandi follow trunk
	#if ((CHIP_ID == CHIP_TSUMC)||( CHIP_ID == CHIP_TSUMD)||(CHIP_ID == CHIP_TSUM9)||(CHIP_ID == CHIP_TSUMF))
	DPOffSQ()
	#if DP_DCOFFHPDLOW
	DPRxHPDDisable();
	#endif
	#else
	DPRxDCHPD( TRUE );
	#endif
	#endif
	Power_PowerOffSystem();
	#if ENABLE_DP_INPUT&&CHIP_ID==CHIP_TSUMU
	gDPInfo.bDPDCoff = 1;
	g_bDoDPInit = FALSE;
	// DPRxHPDDisable();
	#endif
	#if	(MS_PM)
	msPM_SetFlag_PMDCoff();
	#endif
	#if ENABLE_HDCP // 120531 coding reserved
	msPullLowHPD1();
	#endif
	#if ENABLE_DP_INPUT && ENABLE_DP_PS_CTRL
	CLR_DP_PS_CTRL_CHARGE();
	#endif
	return TRUE;
}
Bool PowerOnSystem(void)
{
	Clr_PowerOffFlag();
	Set_PowerOnFlag();
	Clr_DoKeyCountFlag();
	PowerKeyCounter = 0;
	Power_TurnOnGreenLed();
	Power_PowerOnSystem();
	#if ENABLE_DP_INPUT  //130815 xiandi follow trunk
	#if ((CHIP_ID == CHIP_TSUMC)||( CHIP_ID == CHIP_TSUMD) || (CHIP_ID == CHIP_TSUM9)|| (CHIP_ID == CHIP_TSUMF))
	#if  !DP_DCOFFHPDLOW
	if(DP_GetSquelch( 0x2FFFE ) && !(DPFastLink(TRUE)))
	#endif
	#endif
	{
		DPRxHPDDisable();
		ForceDelay1ms(100);
		DPRxHPDEnable();
	}
	#endif
	#if 0//ENABLE_HDCP // 120531 coding reserved
	msPullHighHPD2();
	#endif
	//Set_ShowInputInfoFlag();
	#if !USEFLASH
	NVRam_WriteByte(nvrMonitorAddr(MonitorFlag), MonitorFlags);
	#else
	SaveMonitorSetting();
	#endif
	#if DisplayPowerOnLogo
	if(!(FactoryModeFlag
	    ))
	{
		Set_DisplayLogoFlag();
		//	if(CHIP_ID!=CHIP_TSUMU)		//131011 fay
		msWriteByte(IOSDC2, 0x02); //Disable color bit setting
		// 091005 coding
		mStar_AdjustBrightness(100);
	}
	else
	{
		Set_LoadOSDDataFlag();	//120611 Modify
	}
	#endif
	#ifdef OffPower           //090331 xiandi.yu Auto Off Power
	AutoPowerOffMTime = 0;
	AutoPowerOffHTime = 0;
	ShowOffPowerWarningFlag = 0;
	#endif
	#if ESaverPowerDownFunc
	ESaverPowerDownCounter = 0;
	#endif
	mStar_SetupFreeRunMode();
	mStar_SetupInputPort();
	#if DEBUG_PRINTDATA
	printMsg("ePM_EXIT_PM  222222222222");
	#endif
	#if ENABLE_HDCP // 120531 coding reserved
	msPullHighHPD1();
	#endif
	#if ENABLE_DP_INPUT && ENABLE_DP_PS_CTRL
	SET_DP_PS_CTRL_CHARGE();
	#endif
	return TRUE;
}
Bool EnterRootMenu(void)
{
	OsdCounter = 0;
	return TRUE;
}
//================================================================================
//================================================================================
//================================================================================
Bool AdjustContrast(MenuItemActionType action)
{
	WORD tempValue;
	#if PresetMode_Enable
	if(UserPrefECOMode == ECO_Preset)
		g8TempValue =  UserPrefContrast_Preset;
	else
	#endif
		g8TempValue = UserPrefContrast;
	tempValue = DecIncValue(action, g8TempValue, MinContrastValue, MaxContrastValue, 1);
	if (tempValue == g8TempValue)
	{
		return FALSE;
	}
	g8TempValue = tempValue;
	#if PresetMode_Enable
	if(UserPrefECOMode == ECO_Preset)
		UserPrefContrast_Preset = g8TempValue;
	else
	#endif
	{
		UserPrefContrast = g8TempValue;
		UserPrefContrastUser = UserPrefContrast;
	}
	mStar_AdjustContrast(g8TempValue);
	//SaveMonitorSetting(); // need check again
	return TRUE;
}

WORD GetContrastValue(void)
{
	#if PresetMode_Enable
	if(UserPrefECOMode == ECO_Preset)
		g8TempValue =  UserPrefContrast_Preset;
	else
	#endif
		g8TempValue = UserPrefContrast;
	return GetScale100Value(g8TempValue, MinContrastValue, MaxContrastValue);;
}
//====================================================
Bool AdjustBrightness(MenuItemActionType action)
{
	WORD tempValue;
	#if PresetMode_Enable
	if(UserPrefECOMode == ECO_Preset)
		g8TempValue =  UserPrefBrightness_Preset;
	else
	#endif
		g8TempValue = UserPrefBrightness;
	{
		if(action != MIA_Nothing)	//130627 gordon
		{
			tempValue = DecIncValue(action, g8TempValue, 0, 100, 1);
			if (tempValue == g8TempValue)
			{
				return FALSE;
			}
			g8TempValue = tempValue;
			#if PresetMode_Enable
			if(UserPrefECOMode == ECO_Preset)
				UserPrefBrightness_Preset = g8TempValue;
			else
			#endif
			{
				UserPrefBrightness = g8TempValue;
				UserPrefBrightnessUser = UserPrefBrightness;
			}
		}
		mStar_AdjustBrightness(g8TempValue);
	}
	//SaveMonitorSetting(); // need changed again
	return TRUE;
}

WORD GetBrightnessValue(void)
{
	#if PresetMode_Enable
	if(UserPrefECOMode == ECO_Preset)
		g8TempValue =  UserPrefBrightness_Preset;
	else
	#endif
		g8TempValue = UserPrefBrightness;
	return g8TempValue; //GetScale100Value(UserPrefBrightness, 0, 100);
}
//====================================================
Bool AdjustFocus(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefPhase, 0, MAX_PHASE_VALUE, 1);
	if (tempValue == UserPrefPhase)
		return FALSE;
	UserPrefPhase = tempValue;
	drvADC_SetPhaseCode(UserPrefPhase);
	return TRUE;
}

WORD GetFocusValue(void)
{
	return (SrcInputType != Input_VGA) ? 50 : GetScale100Value(UserPrefPhase, 0, MAX_PHASE_VALUE);	//111223 Modify
	//return UserPrefPhase;
}

//====================================================
Bool AdjustClock(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefHTotal, MinClock, MaxClock, 1);
	if (tempValue == UserPrefHTotal)
	{
		return FALSE;
	}
	UserPrefHTotal = tempValue;
	#if !ENABLE_MENULOAD||!ENABLE_SW_DOUBLE_BUFFER
	mStar_WaitForDataBlanking();			//110930 Rick add for avoid noise while adjust clock value - C_FOS_5
	#endif
	drvADC_AdjustHTotal(UserPrefHTotal);
	return TRUE;
}

WORD GetClockValue(void) // adjust range
{
	return GetScale100Value(UserPrefHTotal, MinClock, MaxClock);
}
//#define MaxHStart   UserPrefAutoHStart+50
//#define MinHStart   UserPrefAutoHStart-50
//====================================================
Bool AdjustHPosition(MenuItemActionType action)
{
	WORD tempValue;
	//  tempValue=DecIncValue(action, UserPrefHStart, 0, 2*StandardModeHStart, 1);
	if(action == MIA_IncValue)
		action = MIA_DecValue;
	else
		action = MIA_IncValue;
	tempValue = DecIncValue(action, UserPrefHStart, MinHStart, MaxHStart, 1);
	if (tempValue == UserPrefHStart)
	{
		return FALSE;
	}
	UserPrefHStart = tempValue;
	mStar_AdjustHPosition(UserPrefHStart);
	return TRUE;
}

WORD GetHPositionValue(void)
{
	return GetScale100Value(UserPrefHStart, MinHStart, MaxHStart); //, 0);
	// return GetScale100Value(UserPrefHStart, MinHStart, MaxHStart);
}
//====================================================
//#define MaxVStart 2*UserPrefAutoVStart-1
//#define MinVStart 1  // 2006/10/26 4:18PM by Emily  0
//====================================================
Bool AdjustVPosition(MenuItemActionType action)
{
	WORD tempValue;
	if (DecVScaleFlag)
		tempValue = DecIncValue(action, UserPrefVStart, (DecVScaleValue / 2), 100 + (DecVScaleValue / 2), 1);
	else
	#if 1 //2004/01/15 num11
		tempValue = DecIncValue(action, UserPrefVStart, MinVStart, MaxVStart, 1);
	#else
		tempValue = DecIncValue(action, UserPrefVStart, 0, 2 * StandardModeVStart, 1);
	#endif
	if (tempValue == UserPrefVStart)
	{
		return FALSE;
	}
	UserPrefVStart = tempValue;
	mStar_AdjustVPosition(UserPrefVStart);
	return TRUE;
}

WORD GetVPositionValue(void)
{
	//Osd_Draw4Num(11,1,UserPrefVStart);
	//Osd_Draw4Num(11,2,DecVScaleFlag);
	//Osd_Draw4Num(18,1,VScaleDecValue);
	//Osd_Draw4Num(18,2,DecVScaleFlag);
	if (DecVScaleFlag)
		return GetScale100Value(UserPrefVStart, (DecVScaleValue / 2), 100 + (DecVScaleValue / 2));
	else
	#if 1 //2004/01/15 num11
		return GetScale100Value(UserPrefVStart, MinVStart, MaxVStart);
	#else
		return GetScale100Value(UserPrefVStart, 0, 2 * StandardModeVStart);
	#endif
}
//====================================================
#if AudioFunc
#if CHIP_ID==CHIP_TSUMU
extern void msAudioEARout_Mute( Bool EnableMute );
#endif

#if EANBLE_MUTE_ON_OFF
Bool SwitchMute(MenuItemActionType action)
{
	if ((action == MIA_DecValue) || (action == MIA_IncValue))
	{
		UserPrefMuteState = UserPrefMuteState ? 0 : 1;
	}
	if (UserPrefMuteState)
	{
		//hw_SetMute();
		#if USE_DAC_ADJ
		msWriteByteMask( REG_2C6A, BIT4, BIT4 );
		#endif
		#if CHIP_ID==CHIP_TSUMU
		//msAudioEARout_Mute( TRUE);
		#endif
		mStar_AdjustVolume(0);
	}
	else
	{
		//if(bAudioInputStatus == AudioInput_Spk)
		//hw_ClrMute();
		#if CHIP_ID==CHIP_TSUMU
		//msAudioEARout_Mute( FALSE);
		#endif
		#if USE_DAC_ADJ
		msWriteByteMask( REG_2C6A, BIT0, BIT4 );
		#endif
		mStar_AdjustVolume(UserPrefVolume);
	}
	return TRUE;
}
#endif
Bool AdjustVolume(MenuItemActionType action)
{
	WORD tempValue;
	if((action != MIA_DecValue) && (action != MIA_IncValue))
		return FALSE;
	tempValue = DecIncValue(action, UserPrefVolume, MinVolume, MaxVolume, 1);
	if (tempValue == UserPrefVolume)
	{
		return FALSE;
	}
	UserPrefVolume = tempValue;
	if(UserPrefMuteState)
	{
		SwitchMute(MIA_DecValue);    // UserPrefMuteState=0;
	}
	mStar_AdjustVolume(UserPrefVolume);
	return TRUE;
}
WORD GetVolumeValue(void)
{
	return GetScale100Value(UserPrefVolume, MinVolume, MaxVolume);
}
#endif

#if OsdAdjustHVPos_Enable
//=====================================================
Bool AdjustOSDHPosition(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefOsdHStart, 0, 100, 1);		//120119 Modify
	if (tempValue == UserPrefOsdHStart)
	{
		return FALSE;
	}
	UserPrefOsdHStart = tempValue;
	mStar_WaitForDataBlanking();
	Osd_SetPosition(UserPrefOsdHStart, UserPrefOsdVStart);
	return TRUE;
}
WORD GetOSDHPositionValue(void)
{
	return GetScale100Value(UserPrefOsdHStart, 0, 100);
	//   return ( UserPrefOsdHStart % 101 );
}
//================================================================================
Bool AdjustOSDVPosition(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefOsdVStart, 0, 100, 1); //0729 New Spec
	if (tempValue == UserPrefOsdVStart)
	{
		return FALSE;
	}
	UserPrefOsdVStart = tempValue;
	mStar_WaitForDataBlanking();
	if (UserPrefOsdVStart == 100)
		Delay1ms(8);
	Osd_SetPosition(UserPrefOsdHStart, UserPrefOsdVStart);
	return TRUE;
}
WORD GetOSDVPositionValue(void)
{
	return GetScale100Value(UserPrefOsdVStart, 0, 100);
	//return GetScale100Value(UserPrefOsdVStart, 0, 100);
}
#endif
//================================================================================
Bool AdjustOSDTransparence(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefOsdTrans, 0, 4, 1); //0729 New Spec
	if (tempValue == UserPrefOsdTrans)
	{
		return FALSE;
	}
	UserPrefOsdTrans = tempValue;
	Osd_SetTransparence(UserPrefOsdTrans);
	#if Enable_OsdEngine1
	Osd_SetOsdEngine(1);
	Osd_SetTransparence(UserPrefOsdTrans);
	Osd_SetOsdEngine(0);
	#endif
	return TRUE;
}
WORD GetOSDTransparence(void)
{
	return GetScale100Value(UserPrefOsdTrans, 0, 4);
}
//================================================================================
Bool AdjustOSDTime(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefOsdTime, 5, 120, 5); // 071218 modified for osd time out
	if (tempValue == UserPrefOsdTime)
	{
		return FALSE;
	}
	UserPrefOsdTime = tempValue;
	return TRUE;
}
WORD GetOSDTimeValue(void)
{
	return UserPrefOsdTime;
}
WORD GetOSDTime100Value(void)
{
	return GetScale100Value(UserPrefOsdTime, 0, 120); // 071218 modified for osd time out
}


#if !Enable_Adjust_SharpnessMenu
#ifdef OffPower           //090331 xiandi.yu Auto Off Power
Bool AdjustAutoPowerOff(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefAutoPowerOff, MinAutoPowerOffTime, MaxAutoPowerOffTime, 1);
	if (tempValue == UserPrefAutoPowerOff)
	{
		return FALSE;
	}
	UserPrefAutoPowerOff = tempValue;
	AutoPowerOffMTime = 0;
	AutoPowerOffHTime = 0;
	ShowOffPowerWarningFlag = 0;
	return TRUE;
}
WORD GetAutoPowerOffValue(void)
{
	return UserPrefAutoPowerOff;
}
#endif
#endif
#if Enable_YMC
// bit 7 6 5 4 3 2 1 0
//         Y C M R G B
void SetYCMColor(MenuItemActionType action, WORD color, WORD value)
{
	//printData("color %d", color);
	//printData("value %d", value);
	if (color & BIT5)
		// Y
	{
		if (action == MIA_IncValue)
			// inc
		{
			if (value + UserPrefYColor >= MaxColorValue)
				UserPrefYColor = MaxColorValue;
			else
				UserPrefYColor += value;
		}
		else
			// dec
		{
			if (UserPrefYColor == 0 || ((UserPrefYColor - value) <= 0))
				UserPrefYColor = 0;
			else
				UserPrefYColor -= value;
		}
		//printData("y %d", UserPrefYColor);
	}
	if (color & BIT4)
		// C
	{
		if (action == MIA_IncValue)
			// inc
		{
			if (value + UserPrefCColor >= MaxColorValue)
				UserPrefCColor = MaxColorValue;
			else
				UserPrefCColor += value;
		}
		else
			// dec
		{
			if (UserPrefCColor == 0 || ((UserPrefCColor - value) <= 0))
				UserPrefCColor = 0;
			else
				UserPrefCColor -= value;
		}
		//printData("c %d", UserPrefCColor);
	}
	if (color & BIT3)
		// M
	{
		if (action == MIA_IncValue)
			// inc
		{
			if (value + UserPrefMColor >= MaxColorValue)
				UserPrefMColor = MaxColorValue;
			else
				UserPrefMColor += value;
		}
		else
			// dec
		{
			if (UserPrefMColor == 0 || ((UserPrefMColor - value) <= 0))
				UserPrefMColor = 0;
			else
				UserPrefMColor -= value;
		}
		//printData("m %d", UserPrefMColor);
	}
	if (color & BIT2)
		// Red
	{
		if (action == MIA_IncValue)
			// inc
		{
			if (value + UserPrefRedColor >= MaxColorValue)
				UserPrefRedColor = MaxColorValue;
			else
				UserPrefRedColor += value;
		}
		else
			// dec
		{
			if (UserPrefRedColor == 0 || ((UserPrefRedColor - value <= 0)))
				UserPrefRedColor = 0;
			else
				UserPrefRedColor -= value;
		}
		//printData("red %d", UserPrefRedColor);
		UserPrefRedColorUser = UserPrefRedColor;
		mStar_AdjustRedColor(UserPrefRedColorUser, UserPrefContrast);
	}
	if (color & BIT1)
		// Green
	{
		if (action == MIA_IncValue)
			// inc
		{
			if (value + UserPrefGreenColor >= MaxColorValue)
				UserPrefGreenColor = MaxColorValue;
			else
				UserPrefGreenColor += value;
		}
		else
			// dec
		{
			if (UserPrefGreenColor == 0 || ((UserPrefGreenColor - value <= 0)))
				UserPrefGreenColor = 0;
			else
				UserPrefGreenColor -= value;
		}
		//printData("green %d", UserPrefGreenColor);
		UserPrefGreenColorUser = UserPrefGreenColor;
		mStar_AdjustGreenColor(UserPrefGreenColorUser, UserPrefContrast);
	}
	if (color & BIT0)
		// Blue
	{
		if (action == MIA_IncValue)
			// inc
		{
			if (value + UserPrefBlueColor >= MaxColorValue)
				UserPrefBlueColor = MaxColorValue;
			else
				UserPrefBlueColor += value;
		}
		else
			// dec
		{
			if (UserPrefBlueColor == 0 || ((UserPrefBlueColor - value <= 0)))
				UserPrefBlueColor = 0;
			else
				UserPrefBlueColor -= value;
		}
		//printData("blue %d", UserPrefBlueColor);
		UserPrefBlueColorUser = UserPrefBlueColor;
		mStar_AdjustBlueColor(UserPrefBlueColorUser, UserPrefContrast);
	}
}
//====================================================
Bool AdjustYColor(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefYColor, MinColorValue, MaxColorValue, 1);	//120204 Modify
	if (tempValue == UserPrefYColor)
	{
		return FALSE;
	}
	if (action == MIA_IncValue)
		// Y=R+G ; C=G+B ; M=B+R
	{
		SetYCMColor(action, 0x1e, tempValue - UserPrefYColor); // YCMRGB:01 1110
	}
	else
	{
		SetYCMColor(action, 0x1e, UserPrefYColor - tempValue); // YCMRGB:01 1110
	}
	UserPrefYColor = tempValue;
	#if UsesRGB
	mStar_AdjustContrast(UserPrefContrast);
	#endif
	return TRUE;
}
WORD GetYColorValue(void)
{
	return GetScale100Value(UserPrefYColor, MinColorValue, MaxColorValue);	//120204 Modify
}
//====================================================
Bool AdjustCColor(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefCColor, MinColorValue, MaxColorValue, 1);	//120204 Modify
	if (tempValue == UserPrefCColor)
	{
		return FALSE;
	}
	if (action == MIA_IncValue)
		// Y=R+G ; C=G+B ; M=B+R
		SetYCMColor(action, 0x2b, tempValue - UserPrefCColor);
	// YCMRGB:10 1011
	else
		SetYCMColor(action, 0x2b, UserPrefCColor - tempValue);
	// YCMRGB:10 1011
	UserPrefCColor = tempValue;
	#if UsesRGB
	mStar_AdjustContrast(UserPrefContrast);
	#endif
	return TRUE;
}
WORD GetCColorValue(void)
{
	return GetScale100Value(UserPrefCColor, MinColorValue, MaxColorValue);	//120204 Modify
}
//====================================================
Bool AdjustMColor(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefMColor, MinColorValue, MaxColorValue, 1);	//120204 Modify
	if (tempValue == UserPrefMColor)
	{
		return FALSE;
	}
	if (action == MIA_IncValue)
		// Y=R+G ; C=G+B ; M=B+R
		SetYCMColor(action, 0x35, tempValue - UserPrefMColor);
	// YCMRGB:11 0101
	else
		SetYCMColor(action, 0x35, UserPrefMColor - tempValue);
	// YCMRGB:11 0101
	UserPrefMColor = tempValue;
	#if UsesRGB
	mStar_AdjustContrast(UserPrefContrast);
	#endif
	return TRUE;
}
WORD GetMColorValue(void)
{
	return GetScale100Value(UserPrefMColor, MinColorValue, MaxColorValue);	//120204 Modify
}
#endif
//====================================================
//====================================================
Bool AdjustBlueColor(MenuItemActionType action)
{
	WORD tempValue;
	#if 0//defined(WH_REQUEST) && WH_REQUEST_OSD
	tempValue = DecIncValue(action, UserPrefBlueColor, MinColorValue, MaxColorValue, 2);
	#else
	tempValue = DecIncValue(action, UserPrefBlueColor, MinColorValue, MaxColorValue, 2);	//120204 Modify
	#endif
	if (tempValue == UserPrefBlueColor)
	{
		return FALSE;
	}
	#if Enable_YMC
	if (UserPrefColorTemp == CTEMP_USER)
		// R=Y+M B=M+C G=C+Y
	{
		if (action == MIA_IncValue)
			// Y=R+G ; C=G+B ; M=B+R
			SetYCMColor(action, 0x18, tempValue - UserPrefBlueColor);
		// YCMRGB:01 1000
		else
			SetYCMColor(action, 0x18, UserPrefBlueColor - tempValue);
		// YCMRGB:01 1000
	}
	#endif
	UserPrefBlueColor = tempValue;
	UserPrefBlueColorUser = UserPrefBlueColor;
	#if UsesRGB
	mStar_AdjustContrast(UserPrefContrast);
	#else
	mStar_AdjustBlueColor(UserPrefBlueColorUser, UserPrefContrast);
	#endif
	return TRUE;
}

WORD GetBlueColorValue(void)
{
	return GetScale100Value(UserPrefBlueColor, MinColorValue, MaxColorValue);	//120204 Modify
}
//====================================================
Bool AdjustGreenColor(MenuItemActionType action)
{
	WORD tempValue;
	#if 0//defined(WH_REQUEST) && WH_REQUEST_OSD
	tempValue = DecIncValue(action, UserPrefGreenColor, MinColorValue, MaxColorValue, 2);
	#else
	tempValue = DecIncValue(action, UserPrefGreenColor, MinColorValue, MaxColorValue, 2);	//120204 Modify
	#endif
	if (tempValue == UserPrefGreenColor)
	{
		return FALSE;
	}
	#if Enable_YMC
	if (UserPrefColorTemp == CTEMP_USER)
		// R=Y+M B=M+C G=C+Y
	{
		if (action == MIA_IncValue)
			// Y=R+G ; C=G+B ; M=B+R
			SetYCMColor(action, 0x30, tempValue - UserPrefGreenColor);
		// YCMRGB:11 0000
		else
			SetYCMColor(action, 0x30, UserPrefGreenColor - tempValue);
		// YCMRGB:11 0000
	}
	#endif
	UserPrefGreenColor = tempValue;
	UserPrefGreenColorUser = UserPrefGreenColor;
	#if UsesRGB
	mStar_AdjustContrast(UserPrefContrast);
	#else
	mStar_AdjustGreenColor(UserPrefGreenColorUser, UserPrefContrast);
	#endif
	#if 0
	if (UserPrefDcrMode == 1)
		// jeff add in 1112
	{
		msAccOnOff(0); // 2006/11/9 11:27PM by Emily test
		UserPrefColorFlags = 0;
		UserPrefDcrMode = 0;
		ReadColorTempSetting();
	}
	#endif
	return TRUE;
}
WORD GetGreenColorValue(void)
{
	return GetScale100Value(UserPrefGreenColor, MinColorValue, MaxColorValue);	//120204 Modify
}
//====================================================
Bool AdjustRedColor(MenuItemActionType action)
{
	WORD tempValue;
	#if 0//defined(WH_REQUEST) && WH_REQUEST_OSD
	tempValue = DecIncValue(action, UserPrefRedColor, MinColorValue, MaxColorValue, 2);	//120204 Modify
	#else
	tempValue = DecIncValue(action, UserPrefRedColor, MinColorValue, MaxColorValue, 2); //120204 Modify
	#endif
	if (tempValue == UserPrefRedColor)
	{
		return FALSE;
	}
	#if Enable_YMC
	if (UserPrefColorTemp == CTEMP_USER)
		// R=Y+M B=M+C G=C+Y
	{
		if (action == MIA_IncValue)
			// Y=R+G ; C=G+B ; M=B+R
		{
			SetYCMColor(action, 0x28, tempValue - UserPrefRedColor); // YCMRGB:10 1000
		}
		else
		{
			SetYCMColor(action, 0x28, UserPrefRedColor - tempValue); // YCMRGB:10 1000
		}
	}
	#endif
	UserPrefRedColor = tempValue;
	UserPrefRedColorUser = UserPrefRedColor;
	#if UsesRGB
	mStar_AdjustContrast(UserPrefContrast);
	#else
	mStar_AdjustRedColor(UserPrefRedColorUser, UserPrefContrast);
	#endif
	#if 0
	if (UserPrefDcrMode == 1)
		// jeff add in 1112
	{
		msAccOnOff(0); // 2006/11/9 11:27PM by Emily test
		UserPrefColorFlags = 0;
		UserPrefDcrMode = 0;
		ReadColorTempSetting();
	}
	#endif
	return TRUE;
}
WORD GetRedColorValue(void)
{
	return GetScale100Value(UserPrefRedColor, MinColorValue, MaxColorValue);	//120204 Modify
}

#if ENABLE_DeltaE
Bool CheckNVRamGammaValueEmpty(void)
{
	BYTE temp3x3Value, tempGammaValue;
	BYTE i;
	for ( i = 0; i < 10; i++ )
	{
		NVRam_ReadByte(RM_COLORSPACE_TRANS_BASEADDR_SRGB + i, &temp3x3Value);
		NVRam_ReadByte(BGammaTblEndAddr - i, &tempGammaValue);
		if (temp3x3Value == 0x00 || temp3x3Value == 0xFF || tempGammaValue == 0x00 || tempGammaValue == 0xFF)
			continue;
		else
			return FALSE;
	}
	return TRUE;
}
#endif

//====================================================
#if ENABLE_DeltaE
Bool ColorTempCtrl(ColorTempType colortemp)
{
	//xdata ColorType CT;
	// UserPrefContrast =  *ColorTempPtr[colortemp][1];
	// UserPrefBrightness =  *ColorTempPtr[colortemp][0];
	// UserPrefRedColor =  *ColorTempPtr[colortemp][2];
	// UserPrefGreenColor =  *ColorTempPtr[colortemp][3];
	// UserPrefBlueColor =  *ColorTempPtr[colortemp][4];
	// CT.u8Red     =*(ColorTempPtr[colortemp][2]);
	// CT.u8Green   =*(ColorTempPtr[colortemp][3]);
	// CT.u8Blue    =*(ColorTempPtr[colortemp][4]);
	mStar_WaitForDataBlanking();
	//  mStar_AdjustRGBColor(UserPrefContrast, CT.u8Red, CT.u8Green, CT.u8Blue);
	//  mStar_AdjustBrightness(UserPrefBrightness);
	#if ENABLE_DeltaE
	if (colortemp == CTEMP_SRGB)
	{
		if(!CheckNVRamGammaValueEmpty())
		{
			#if ENABLE_USE_NewDeltaE
			LoadDeltaEColorMode(0, 0, 1); // Load delta -E measure value
			#else
			LoadDeltaEColorMode(0, 1, 1); // Load delta -E measure value
			#endif
		}
		GammaContent = GAMAContent_GAMA_sRGB;
	}
	else
	{
		mStar_SetupGamma( UserPrefGamaMode );
		msWriteByteMask(SCE_02,  0, _BIT2 | _BIT1 | _BIT0); // fix-gamma/color-matrix/de-gamma enable.
	}
	#endif
	return TRUE;
}
#endif
Bool SetColorTemp(void)
{
	ReadColorTempSetting();
	#if ENABLE_DeltaE
	if (UserPrefColorTemp == CTEMP_SRGB)
	{
		if(!CheckNVRamGammaValueEmpty())
		{
			mStar_WaitForDataBlanking();
			#if ENABLE_USE_NewDeltaE
			LoadDeltaEColorMode(0, 0, 1); // Load delta -E measure value
			#else
			LoadDeltaEColorMode(0, 1, 1); // Load delta -E measure value
			#endif
		}
		GammaContent = GAMAContent_GAMA_sRGB;
	}
	else
	{
		mStar_SetupGamma( UserPrefGamaMode );
		msWriteByteMask(SCE_02,  0, _BIT2 | _BIT1 | _BIT0); // fix-gamma/color-matrix/de-gamma enable.
	}
	#endif
	//if (UserPrefColorTemp == CTEMP_SRGB)
	//{
	//    UserPrefECOMode = ECO_Standard;
	//}
	//Set_SaveSettingFlag();//1020
	return TRUE;
}
Bool AdjustColorTempMode(MenuItemActionType action)
{
	BYTE temp;
	#if PresetMode_Enable
	if(UserPrefECOMode == ECO_Preset)
		g8TempValue =  UserPrefColorTemp_Preset;
	else
	#endif
		g8TempValue =  UserPrefColorTemp;
	temp = g8TempValue;
	if (action == MIA_DecValue)
	{
		g8TempValue = (g8TempValue + CTEMP_Nums - 1) % CTEMP_Nums;
	}
	else
	{
		g8TempValue = (g8TempValue + 1) % CTEMP_Nums;
	}
	if (temp == g8TempValue)
		return FALSE;
	#if PresetMode_Enable
	if(UserPrefECOMode == ECO_Preset)
		UserPrefColorTemp_Preset = g8TempValue;
	else
	#endif
		UserPrefColorTemp = g8TempValue;
	#if sRGBIssue		//130109_23 Henry Move From Menu.c
	if( UserPrefColorTemp == CTEMP_SRGB )
	{
		if( UserPrefECOMode != ECO_Standard )
		{
			UserPrefECOMode = ECO_Standard;
			SetColorTemp();
		}
		if( UserPrefGamaMode != GAMA1 )
		{
			UserPrefGamaMode = GAMA1;
			#if Enable_Gamma
			mStar_SetupGamma( GAMA1 );
			#endif
		}
		if(UserPrefDcrMode)
		{
			UserPrefDcrMode = 0;
			SetECO();
			msDCROnOff(UserPrefDcrMode, MAIN_WINDOW);
		}
	}
	else
	{
		UserPrefECOMode = UserPrevECOMode;
		UserPrefGamaMode = UserPrevGamaMode;
		#if Enable_Gamma
		mStar_SetupGamma( UserPrefGamaMode );
		#endif
		#if sRGBIssue||iCareForResetIssue
		UserPrefiCareMode = UserPreviCareMode;
		#endif
		UserPrefDcrMode = UserPrevDcrMode;
		SetECO();
		msDCROnOff(UserPrefDcrMode, MAIN_WINDOW);
	}
	#endif
	#if CT_sRGB_ENABLE
	if( UserPrefColorTemp == CTEMP_SRGB )//20140817  for all scaler the same
	{
		if( UserPrefECOMode != ECO_Standard )
		{
			UserPrefECOMode = ECO_Standard;
			SetColorTemp();
		}
		if( UserPrefGamaMode != GAMA1 )
		{
			UserPrefGamaMode = GAMA1;
			#if Enable_Gamma
			mStar_SetupGamma( GAMA1 );
			#endif
		}
		if(UserPrefDcrMode)
		{
			UserPrefDcrMode = 0;
			SetECO();
			msDCROnOff(UserPrefDcrMode, MAIN_WINDOW);
		}
		#if ENABLE_OSD_LowBlueLight
		if(UserprefLowBlueLightMode != LOW_BLUE_LIGHT_OFF)
			UserprefLowBlueLightMode = LOW_BLUE_LIGHT_OFF;
		#endif
	}
	#endif
	#if LowBlueLightType == LowBlueLight_SharpFunc
	if(UserPrefColorTemp == CTEMP_LowBlue)
	{
		gTempLowBlueMode = UserprefLowBlueLightMode ;
	}
	#endif
	SetColorTemp();
	#if !USEFLASH
	NVRam_WriteByte(nvrMonitorAddr(ECOMode), UserPrefECOMode);
	NVRam_WriteByte(nvrMonitorAddr(ColorTemp), UserPrefColorTemp);
	NVRam_WriteByte( nvrMonitorAddr( DcrMode ), UserPrefDcrMode );
	NVRam_WriteByte( nvrMonitorAddr( GamaMode ), UserPrefGamaMode );
	#if ENABLE_OSD_LowBlueLight
	NVRam_WriteByte( nvrMonitorAddr( LowBlueLightMode ), UserprefLowBlueLightMode );
	#endif
	#else
	UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
	#endif
	/*msAccOnOff(0); // 2006/11/9 11:27PM by Emily test
	UserPrefColorFlags = 0;*/
	return TRUE;
}
#if HKC_INPUTSELECT_MODE
Bool AdjustInputSource(MenuItemActionType action)
{
	if (action == MIA_DecValue)
	{
		UserPrefInputType = (UserPrefInputType + Input_Nums - 1) % Input_Nums;
	}
	else if(action == MIA_IncValue)
	{
		UserPrefInputType = (UserPrefInputType + 1) % Input_Nums;
	}
	//  SaveMonitorSetting();
	// Set_SaveSettingFlag();
	return TRUE;
}
#endif
#if AdjustLanguageFunction
Bool AdjustLanguage(MenuItemActionType action)
{
	BYTE temp;
	temp = UserPrefLanguage;
	#if 1//LanguageEnable_All
	if (action == MIA_DecValue)
	{
		UserPrefLanguage = (UserPrefLanguage + LANG_Nums - 1) % LANG_Nums;
	}
	else
	{
		UserPrefLanguage = (UserPrefLanguage + 1) % LANG_Nums;
	}
	#else
	//return TRUE;
	if (action == MIA_DecValue)
	{
		while(1)
		{
			UserPrefLanguage = (UserPrefLanguage + LANG_Nums - 1) % LANG_Nums;
			#if 0//!LanguageEnable_English
			if(UserPrefLanguage == LANG_English) continue;
			#endif
			#if !LanguageEnable_France
			if(UserPrefLanguage == LANG_France) continue;
			#endif
			#if !LanguageEnable_Spanish
			if(UserPrefLanguage == LANG_Spanish) continue;
			#endif
			#if !LanguageEnable_Portugues
			if(UserPrefLanguage == LANG_Portugues) continue;
			#endif
			#if !LanguageEnable_German
			if(UserPrefLanguage == LANG_German) continue;
			#endif
			#if !LanguageEnable_Italian
			if(UserPrefLanguage == LANG_Italian) continue;
			#endif
			#if !LanguageEnable_Dutch
			if(UserPrefLanguage == LANG_Dutch) continue;
			#endif
			#if !LanguageEnable_Swedish
			if(UserPrefLanguage == LANG_Swedish) continue;
			#endif
			#if !LanguageEnable_Finnish
			if(UserPrefLanguage == LANG_Finnish) continue;
			#endif
			#if !LanguageEnable_Polish
			if(UserPrefLanguage == LANG_Polish) continue;
			#endif
			#if !LanguageEnable_Czech
			if(UserPrefLanguage == LANG_Czech) continue;
			#endif
			#if !LanguageEnable_Russia
			if(UserPrefLanguage == LANG_Russia) continue;
			#endif
			#if !LanguageEnable_Korea
			if(UserPrefLanguage == LANG_Korea) continue;
			#endif
			#if !LanguageEnable_TChina
			if(UserPrefLanguage == LANG_TChina) continue;
			#endif
			#if !LanguageEnable_SChina
			if(UserPrefLanguage == LANG_SChina) continue;
			#endif
			#if !LanguageEnable_Japan
			if(UserPrefLanguage == LANG_Japan) continue;
			#endif
			break;
		}
	}
	else
	{
		while(1)
		{
			UserPrefLanguage = (UserPrefLanguage + 1) % LANG_Nums;
			#if 0//!LanguageEnable_English
			if(UserPrefLanguage == LANG_English) continue;
			#endif
			#if !LanguageEnable_France
			if(UserPrefLanguage == LANG_France) continue;
			#endif
			#if !LanguageEnable_Spanish
			if(UserPrefLanguage == LANG_Spanish) continue;
			#endif
			#if !LanguageEnable_Portugues
			if(UserPrefLanguage == LANG_Portugues) continue;
			#endif
			#if !LanguageEnable_German
			if(UserPrefLanguage == LANG_German) continue;
			#endif
			#if !LanguageEnable_Italian
			if(UserPrefLanguage == LANG_Italian) continue;
			#endif
			#if !LanguageEnable_Dutch
			if(UserPrefLanguage == LANG_Dutch) continue;
			#endif
			#if !LanguageEnable_Swedish
			if(UserPrefLanguage == LANG_Swedish) continue;
			#endif
			#if !LanguageEnable_Finnish
			if(UserPrefLanguage == LANG_Finnish) continue;
			#endif
			#if !LanguageEnable_Polish
			if(UserPrefLanguage == LANG_Polish) continue;
			#endif
			#if !LanguageEnable_Czech
			if(UserPrefLanguage == LANG_Czech) continue;
			#endif
			#if !LanguageEnable_Russia
			if(UserPrefLanguage == LANG_Russia) continue;
			#endif
			#if !LanguageEnable_Korea
			if(UserPrefLanguage == LANG_Korea) continue;
			#endif
			#if !LanguageEnable_TChina
			if(UserPrefLanguage == LANG_TChina) continue;
			#endif
			#if !LanguageEnable_SChina
			if(UserPrefLanguage == LANG_SChina) continue;
			#endif
			#if !LanguageEnable_Japan
			if(UserPrefLanguage == LANG_Japan) continue;
			#endif
			break;
		}
	}
	#endif
	if (temp == UserPrefLanguage)
		return FALSE;
	return TRUE;
}
#else
Bool AdjustLanguage( MenuItemActionType action )
{
	action = action;
	if (UserPrefLanguage == MenuItemIndex)
		return FALSE;
	UserPrefLanguage = MenuItemIndex;
	#if DEBUG_PRINTDATA
	printData("UserPrefLanguage Index %d", UserPrefLanguage);
	#endif
	return TRUE;
}
#endif


//========== ADJUST INPUT PORT =======================
#if Dual
Bool ChangeSource(void)
{
	// 071218 source select
	hw_SetGreenLed();
	hw_ClrAmberLed();
	#if AudioFunc && ENABLE_HDMI 	//120119 Modify for TPV Request
	if (SrcInputType == Input_HDMI || SrcInputType == Input_HDMI2 || SrcInputType == Input_HDMI3)
		mstar_HDMIAudioMute(HDMI_AUDIO_OFF);
	#endif
	#if AudioFunc && ENABLE_DP_INPUT
	if(
    #if INPUT_TYPE == INPUT_1A1DP
	    ((PrevInputType == INPUT_PRIORITY_VGA) && (SrcInputType == INPUT_PRIORITY_DP))
	    || ((PrevInputType == INPUT_PRIORITY_DP) && (SrcInputType == INPUT_PRIORITY_VGA))
    #elif INPUT_TYPE == INPUT_1A1H1DP
	    ((PrevInputType == INPUT_PRIORITY_VGA || PrevInputType == INPUT_PRIORITY_HDMI) && (SrcInputType == INPUT_PRIORITY_DP))
	    || ((PrevInputType == INPUT_PRIORITY_DP) && (SrcInputType == INPUT_PRIORITY_VGA || SrcInputType == INPUT_PRIORITY_HDMI))
    #elif (INPUT_TYPE == INPUT_1D1H1DP)
	    ((PrevInputType == INPUT_PRIORITY_DVI || PrevInputType == INPUT_PRIORITY_HDMI) && (SrcInputType == INPUT_PRIORITY_DP))
	    || ((PrevInputType == INPUT_PRIORITY_DP) && (SrcInputType == INPUT_PRIORITY_DVI || SrcInputType == INPUT_PRIORITY_HDMI))
    #elif (INPUT_TYPE == INPUT_1A2H1DP)
	    ((PrevInputType == INPUT_PRIORITY_VGA) && (SrcInputType == INPUT_PRIORITY_DP)) || ((PrevInputType == INPUT_PRIORITY_DP) && (SrcInputType == INPUT_PRIORITY_VGA))
    #else
	    ((PrevInputType == INPUT_PRIORITY_VGA || PrevInputType == INPUT_PRIORITY_DVI) && (SrcInputType == INPUT_PRIORITY_DP))
	    || ((PrevInputType == INPUT_PRIORITY_DP) && (SrcInputType == INPUT_PRIORITY_VGA || SrcInputType == INPUT_PRIORITY_DVI))
    #endif
	)
	{
		hw_SetMute();
	}
	#endif
	Power_TurnOffPanel();
	mStar_SetupInputPort();
	Clr_BackToStandbyFlag();
	Set_InputTimingChangeFlag();
	#if Dual
	if (!(FactoryModeFlag))
		Set_ShowInputInfoFlag();
	#endif
	SrcFlags |= SyncLoss;
	return TRUE;
}
#endif

#if DDCCI_ENABLE && DDCCCIMenu_Enable
void Set_DDC2BI_ID( void )
{
	D2B_SET_ID_VGA(DDCciFlag);//DDCADC_DDCCI_ID = 0xB7;
	#if (CHIP_ID == CHIP_TSUMC) || (CHIP_ID == CHIP_TSUMD) || (CHIP_ID == CHIP_TSUM9) || (CHIP_ID == CHIP_TSUMF)
	#if DDC_Port_D0
	D2B_SET_ID_DVI0(DDCciFlag);
	#endif
	#if DDC_Port_D1
	D2B_SET_ID_DVI1(DDCciFlag);
	#endif
	#if DDC_Port_D2
	D2B_SET_ID_DVI2(DDCciFlag);
	#endif
	#else
	#if INPUT_TYPE!=INPUT_1A
	D2B_SET_ID_DVI(DDCciFlag);//DDCDVI_DDCCI_ID = 0xB7;
	#if ENABLE_HDMI
	D2B_SET_ID_HDMI(DDCciFlag);//DDCHDMI_DDCCI_ID = 0xB7;
	#endif
	#endif
	#endif
	#if ENABLE_DP_INPUT
	D2B_SET_ID_DP(DDCciFlag);//DDCDP_DDCCI_ID=0xB7;
	#endif
}

#if 1
Bool AdjustDDCCI(MenuItemActionType action)
{
	action = action;
	if (DDCciFlag)
		Clr_DDCciFlag();
	else
		Set_DDCciFlag();
	Set_DDC2BI_ID();
	return TRUE;
}
#endif
Bool ExecDDC2Bi(void)
{
	if (DDCciFlag)
		Clr_DDCciFlag();
	else
		Set_DDCciFlag();
	Set_DDC2BI_ID();
	return TRUE;
}
#endif
#if HKC_INPUTSELECT_MODE
Bool SetInputSourceChange( void ) //111223 Modify
{
	if ((SrcInputType == UserPrefInputType)
	   )
	{
		if( UnsupportedModeFlag)
			Set_BackToUnsupportFlag();
		return FALSE;
	}
	SrcInputType = UserPrefInputType;
	if(UserPrefInputSelectType != INPUT_PRIORITY_AUTO)
	{
		UserPrefInputSelectType = INPUT_PRIORITY_AUTO;
		UserPrefInputType = SrcInputType;	//110424 Modify
		Set_SaveSettingFlag();
	}
	ChangeSource();
	#if AudioFunc && ENABLE_DP_INPUT
	PrevInputType = SrcInputType;
	#endif
	return TRUE;
}
#endif
#if ENABLE_AutoDetech
#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
Bool SetInputToAuto( void )	//111223 Modify
{
	UserPrefInputSelectType = INPUT_PRIORITY_AUTO;
	Set_SaveSettingFlag();
	return TRUE;
}
#endif


#if HotInputSelect	//111223 Modify

#if ENABLE_VGA_INPUT
Bool SetInputToAnalog(void)	//111223 Modify
{
	UserPrefInputSelectType = INPUT_PRIORITY_VGA;
	Set_SaveSettingFlag();
	if (SrcInputType == INPUT_PRIORITY_VGA && !FreeRunModeFlag)
	{
		return FALSE;
	}
	UserPrefInputType = SrcInputType = INPUT_PRIORITY_VGA;
	ChangeSource();
	#if AudioFunc && ENABLE_DP_INPUT
	PrevInputType = SrcInputType;
	#endif
	return TRUE;
}
#endif
#if ENABLE_DVI_INPUT
Bool SetInputToDigital(void)	//111223 Modify
{
	UserPrefInputSelectType = INPUT_PRIORITY_DVI;
	Set_SaveSettingFlag();
	if (SrcInputType == INPUT_PRIORITY_DVI && !FreeRunModeFlag)
	{
		return FALSE;
	}
	UserPrefInputType = SrcInputType = INPUT_PRIORITY_DVI;
	ChangeSource();
	#if AudioFunc && ENABLE_DP_INPUT
	PrevInputType = SrcInputType;
	#endif
	return TRUE;
}
#endif

#if ENABLE_HDMI_INPUT
Bool SetInputToHDMI(void)	//111223 Modify
{
	UserPrefInputSelectType = INPUT_PRIORITY_HDMI;
	Set_SaveSettingFlag();
	if (SrcInputType == INPUT_PRIORITY_HDMI && !FreeRunModeFlag)
	{
		return FALSE;
	}
	UserPrefInputType = SrcInputType = INPUT_PRIORITY_HDMI;
	ChangeSource();
	#if AudioFunc && ENABLE_DP_INPUT
	PrevInputType = SrcInputType;
	#endif
	return TRUE;
}
#if ENABLE_HDMI2ND_INPUT
Bool SetInputToHDMI2(void)	//111223 Modify
{
	UserPrefInputSelectType = INPUT_PRIORITY_HDMI2ND;
	Set_SaveSettingFlag();
	if (SrcInputType == INPUT_PRIORITY_HDMI2ND && !FreeRunModeFlag)
	{
		return FALSE;
	}
	UserPrefInputType = SrcInputType = INPUT_PRIORITY_HDMI2ND;
	ChangeSource();
	#if AudioFunc && ENABLE_DP_INPUT
	PrevInputType = SrcInputType;
	#endif
	return TRUE;
}
#endif

#endif

#if ENABLE_DPlay_INPUT
Bool SetInputToDP(void)   //111223 Modify
{
	UserPrefInputSelectType = INPUT_PRIORITY_DP;
	Set_SaveSettingFlag();
	if (SrcInputType == INPUT_PRIORITY_DP && !FreeRunModeFlag)
	{
		return FALSE;
	}
	UserPrefInputType = SrcInputType = INPUT_PRIORITY_DP;
	ChangeSource();
	#if AudioFunc && ENABLE_DP_INPUT
	PrevInputType = SrcInputType;
	#endif
	return TRUE;
}
#endif


#endif
#endif

Bool EnterHotInputMenu( void )
{
	if(PowerSavingFlag)
	{
		Clr_PowerSavingFlag();
		Power_TurnOnPanel();
	}
	return TRUE;
}

#if Dual

#if ENABLE_VGA_INPUT
Bool ChangeSourceToAnalog(void)	//111223 Modify
{
	if ((SrcInputType == INPUT_PRIORITY_VGA))
	{
		if( UnsupportedModeFlag)
			Set_BackToUnsupportFlag();
		return FALSE;
	}
	SrcInputType = INPUT_PRIORITY_VGA;
	if(UserPrefInputSelectType != INPUT_PRIORITY_AUTO)
	{
		UserPrefInputSelectType = INPUT_PRIORITY_VGA;
		UserPrefInputType = SrcInputType;	//110424 Modify
		Set_SaveSettingFlag();
	}
	ChangeSource();
	#if AudioFunc && ENABLE_DP_INPUT
	PrevInputType = SrcInputType;
	#endif
	return TRUE;
}
#endif



#if ENABLE_DVI_INPUT
Bool ChangeSourceToDigital(void)	//111223 Modify
{
	if ((SrcInputType == INPUT_PRIORITY_DVI)// 130717	william
	   )
	{
		if( UnsupportedModeFlag )
			Set_BackToUnsupportFlag();
		return FALSE;
	}
	SrcInputType = INPUT_PRIORITY_DVI;
	if(UserPrefInputSelectType != INPUT_PRIORITY_AUTO)
	{
		UserPrefInputSelectType = INPUT_PRIORITY_DVI;
		UserPrefInputType = SrcInputType;	//110424 Modify
		Set_SaveSettingFlag();
	}
	ChangeSource();
	#if AudioFunc && ENABLE_DP_INPUT
	PrevInputType = SrcInputType;
	#endif
	return TRUE;
}
#endif




#if ENABLE_HDMI_INPUT	//120424 Modify
Bool ChangeSourceToHDMI(void)
{
	if (SrcInputType == INPUT_PRIORITY_HDMI)
	{
		if( UnsupportedModeFlag )
			Set_BackToUnsupportFlag();
		return FALSE;
	}
	SrcInputType = INPUT_PRIORITY_HDMI;
	if(UserPrefInputSelectType != INPUT_PRIORITY_AUTO)
	{
		UserPrefInputSelectType = INPUT_PRIORITY_HDMI;
		UserPrefInputType = SrcInputType;	//110424 Modify
		Set_SaveSettingFlag();
	}
	ChangeSource();
	#if AudioFunc && ENABLE_DP_INPUT
	PrevInputType = SrcInputType;
	#endif
	return TRUE;
}

#if ENABLE_HDMI2ND_INPUT	//120424 Modify
Bool ChangeSourceToHDMI2(void)
{
	if (SrcInputType == INPUT_PRIORITY_HDMI2ND)
	{
		if( UnsupportedModeFlag )
			Set_BackToUnsupportFlag();
		return FALSE;
	}
	SrcInputType = INPUT_PRIORITY_HDMI2ND;
	if(UserPrefInputSelectType != INPUT_PRIORITY_AUTO)
	{
		UserPrefInputSelectType = INPUT_PRIORITY_HDMI2ND;
		UserPrefInputType = SrcInputType;	//110424 Modify
		Set_SaveSettingFlag();
	}
	ChangeSource();
	#if AudioFunc && ENABLE_DP_INPUT
	PrevInputType = SrcInputType;
	#endif
	return TRUE;
}
#endif


#endif

#if ENABLE_DP_INPUT
Bool ChangeSourceToDP(void)
{
	if (SrcInputType == INPUT_PRIORITY_DP)
	{
		if( UnsupportedModeFlag )
			Set_BackToUnsupportFlag();
		return FALSE;
	}
	SrcInputType = INPUT_PRIORITY_DP;
	if(UserPrefInputSelectType != INPUT_PRIORITY_AUTO)
	{
		UserPrefInputSelectType = INPUT_PRIORITY_DP;
		UserPrefInputType = SrcInputType;   //110424 Modify
		Set_SaveSettingFlag();
	}
	ChangeSource();
	#if AudioFunc && ENABLE_DP_INPUT
	PrevInputType = SrcInputType;
	#endif
	return TRUE;
}
#endif



#endif // dual




#if CHIP_ID == CHIP_TSUMV||CHIP_ID == CHIP_TSUM2

BYTE code SharpnessTable[] =
{
	#if CHIP_ID == CHIP_TSUMV	//130306 Modify
	0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x24, 0x28, 0x2C, 0x31, 0x35
	#else
	0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25	//william0524 Modify For Change ByPassSharpness Position//0x1D, 0x1E, 0x1F, 0x20, 0x21,0x22, 0x23, 0x24, 0x25, 0x26,0x27
	#endif
};

#elif CHIP_ID == CHIP_TSUMC||CHIP_ID == CHIP_TSUMD ||CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF
BYTE code SharpnessTable[] =
{
	0x00, 0x02, 0x04, 0x06, 0x08, 0x0B, 0x10, 0x15, 0x1A, 0x1F, 0x24 //william0524 Modify For Change ByPassSharpness Position	//0x00, 0x04, 0x08, 0x0B, 0x10,0x15, 0x1A, 0x1F, 0x24, 0x29,0x2E//  0x00, 0x05, 0x0A, 0x0E, 0x14,0x19, 0x1E, 0x23, 0x28, 0x2D,0x32	//130407 Modify
};

#else

BYTE code SharpnessTable[] =
{
	0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D	// william0524 Modify For Change ByPassSharpness Position//0x05, 0x06, 0x07, 0x08, 0x09,0x0A, 0x0B, 0x0C, 0x0D,0x0E,0x0F
};

#endif




#if ( LowBlueLightType==LowBlueLight_ColorTemp)||(LowBlueLightType==LowBlueLight_Misc_Group)
WORD DecIncValueCirculate( MenuItemActionType action, WORD value, WORD minValue, WORD maxValue, BYTE step )
{
	if ( action == MIA_IncValue )
	{
		if ( value == maxValue )
			value = minValue;
		else
			value += step;
	}
	else if ( action == MIA_DecValue )
	{
		if ( value == minValue )
			value = maxValue;
		else
			value -= step;
	}
	return value;
}
#endif

#if ENABLE_FACTORY_BLACKLEVEL
Bool AdjustColorBlacklevel( MenuItemActionType action )
{
	WORD tempValue;
	tempValue = DecIncValue( action, UserprefRedBlackLevel, 0, 100, 1 );
	if( tempValue == UserprefRedBlackLevel )
	{
		return FALSE;
	}
	UserprefRedBlackLevel = tempValue;
	UserprefGreenBlackLevel = tempValue;
	UserprefBlueBlackLevel = tempValue;
	mStar_AdjustUserPrefBlacklevel( UserprefRedBlackLevel, UserprefGreenBlackLevel, UserprefBlueBlackLevel );
	SaveUserPref();
	return TRUE;
}
WORD GetColorBlacklevelValue( void )
{
	return UserprefRedBlackLevel;
}

#endif



Bool ResetAllSetting(void)
{
	#if 0//ndef SETTING_IN_FLASH_12K
	ModeInfoType modeInfo;
	#endif
	WORD hFreq, vFreq;
	hFreq = HFreq(SrcHPeriod);
	vFreq = VFreq(hFreq, SrcVTotal);
	UserPrefOsdHStart = DefOsdHPosValue;//50;
	UserPrefOsdVStart = DefOsdVPosValue;//50;
	#if 0//ENABLE_FREESYNC
	UserprefFreeSyncMode = FreeSyncMenuItems_On;
	msAPI_combo_IPEnableDDRFlag(UserprefFreeSyncMode);
	#endif
	#if !USEFLASH
	if(FactoryModeFlag)
		FlashEnableWP();
	#endif
	#if INPUT_TYPE == INPUT_1A
	UserPrefInputSelectType = INPUT_PRIORITY_VGA;
	#elif INPUT_TYPE == INPUT_1H
	UserPrefInputSelectType = INPUT_PRIORITY_HDMI;
	#else
	#if DISABLE_AUTO_SWITCH
	UserPrefInputSelectType = FIXED_PORT;
	#else
	UserPrefInputSelectType = INPUT_PRIORITY_AUTO; // 071221 modified for initial UserPrefInputSelectType
	#endif
	#endif
	#if AudioFunc
	UserPrefVolume = DefVolume;
	if(UserPrefMuteState)
	{
		UserPrefMuteState = 0;
		SwitchMute(MIA_Nothing);
	}
	else
		mStar_AdjustVolume(UserPrefVolume);
	#endif
	#if ENABLE_FREESYNC
	// if(UserprefFreeSyncMode != FreeSyncMenuItems_Off)
	{
		#if FreeSyncMenu_Enable
		if (CURRENT_INPUT_IS_HDMI())
			UserprefFreeSyncMode = FreeSyncStatues;//FreeSyncMenuItems_Off
		#else
		UserprefFreeSyncMode = FreeSyncMenuItems_On;//FreeSyncMenuItems_Off
		#endif
		#if FreeSyncSwitchEDID
		FreeSyncEDIDSwitch(HDMI1, UserprefFreeSyncMode);
		//   return 0;
		FreeSyncEDIDSwitch(HDMI2, UserprefFreeSyncMode);
		//   return 0;
		#endif
		#if FreeSyncMenu_Enable
		//  msAPI_combo_IPEnableDDRFlag(UserprefFreeSyncMode);
		#endif
	}
	#endif
	if (FactoryModeFlag)
		// User  R/G/B
	{
		UserPrefRedColor = 0xb2; //0xff;   // 0105 ask by LAI
		UserPrefGreenColor = 0xb2; //0xff; // 0105 ask by LAI
		UserPrefBlueColor = 0xb2; //0xff;  // 0105 ask by LAI
	}
	#if ENABLE_FACTORY_BLACKLEVEL  ||   ENABLE_DDCCI_BLACKLEVEL
	UserprefRedBlackLevel = DefRedBlackLevel;
	UserprefGreenBlackLevel = DefGreenBlackLevel;
	UserprefBlueBlackLevel = DefBlueBlackLevel;
	mStar_AdjustUserPrefBlacklevel(UserprefRedBlackLevel, UserprefGreenBlackLevel, UserprefBlueBlackLevel);
	#endif
	// UserPrefLanguage=ResetLanguage;           //20050919 cancel
	#if Enable_Expansion
	if(UserprefExpansionMode  != DefExpansion)
	{
		UserprefExpansionMode = DefExpansion;
		mStar_BlackWhiteScreenCtrl(BW_SCREEN_BLACK);/////180711 modify
		#if (CHIP_ID!=CHIP_TSUMU && CHIP_ID!=CHIP_TSUM2&& CHIP_ID!=CHIP_TSUMC&& CHIP_ID!=CHIP_TSUMD&& CHIP_ID!=CHIP_TSUMF)
		mStar_SetScalingFactor();
		#else
		#if ENABLE_OVER_SCAN
		mStar_SetCaptureWindow();
		#endif
		mStar_SetupPath();
		mStar_SetTimingGen(PanelWidth, PanelHeight, FALSE);
		#endif
		mStar_BlackWhiteScreenCtrl(BW_SCREEN_OFF);/////180711 modify
	}
	#endif
	UserPrefSavedModeIndex = NumberOfMode;
	UserPrefOsdTime = DefOsdTime;
	UserPrefOsdTrans = 0;		//120119 Modify
	//UserPrefLanguage = DefLanguage;
	Osd_SetTransparence(UserPrefOsdTrans);
	#ifdef OffPower           //090331 xiandi.yu Auto Off Power
	UserPrefAutoPowerOff = 0;
	AutoPowerOffMTime = 0;
	AutoPowerOffHTime = 0;
	ShowOffPowerWarningFlag = 0;
	#endif
	UserPrefSharpness = DefSharpness;							//120105 Modify
	#if CHIP_ID == CHIP_TSUMV
	if(CURRENT_INPUT_IS_DVI())
		msAdjustSharpness( MAIN_WINDOW,  GetRealSharpness(), 1);	//120105 Modify
	else
	#endif
		msAdjustSharpness( MAIN_WINDOW,  GetRealSharpness(), 0);	//120105 Modify
	UserPrefBrightness = DefBrightness;
	UserPrefContrast = DefContrast;
	UserPrefBrightnessUser = UserPrefBrightness;
	UserPrefContrastUser = UserPrefContrast;
	UserPrefECOMode = ECO_Standard;
	UserPrefColorTemp = DefColorTemp;//CTEMP_Warm1;//CTEMP_Warm1; //CTEMP_9300K 20051115 wmz
	#if PresetMode_Enable
	UserPrefColorTemp_Preset	= CTEMP_Warm1;
	UserPrefBrightness_Preset 	= DefBrightness;
	UserPrefContrast_Preset 	= DefContrast;
	UserPrefGamaMode_Preset = GAMA1;
	#endif
	SetColorTemp(); //9300K()
	#if Enable_Gamma
	UserPrefGamaMode = GAMA1;
	mStar_SetupGamma( GAMA1 );
	#endif
	if(UserPrefDcrMode)
	{
		UserPrefDcrMode = 0;
		msDCROnOff(UserPrefDcrMode, MAIN_WINDOW);
	}
	#if 0//ENABLE_RTE
	UserPrefRTEMode = DefRTEMode;
	#if ENABLE_DISPLAY_UNDERSCAN
	if(UnderScanSetting.Enable)
	{
		msOverDriveOnOff( FALSE );
	}
	else  if(g_SetupPathInfo.bFBMode) // FB mode, FRC case
	{
		msOverDriveOnOff( FALSE );
	}
	else
	#endif
	#if ENABLE_DUAL_LINK
		if((GetVfreq() > 85) && (!ENABLE_FREESYNC)
	        #if ENABLE_120Hz_OD
		        && !(g_SetupPathInfo.wImgSizeOutH == PanelWidth &&  g_SetupPathInfo.wImgSizeOutV == PanelHeight) && (UserprefExpansionMode != Expansion_Aspect)
	        #endif
		  )//(SrcModeIndex==MODE_1920x1080P_144Hz)	//130328 Modify
		{
			msOverDriveOnOff( FALSE );
		}
		else
	#endif
		{
			msOverDriveOnOff( TRUE );
		}
	{
		msOverDriveOnOff( FALSE );
		//Clr_OverDriveOnFlag();
		msRTE_LoadLUT();
		msOverDriveOnOff( TRUE );
	}
	#endif
	#if ENABLE_RTE
	UserPrefRTEMode = DefRTEMode;
	msOverDriveOnOff( DefRTEMode );
	#endif
	// 2006/11/10 5:15PM by KK not need reset this item    UserPrefLanguage = LANG_English;
	#if ECO
	SetECO();
	#endif
	#if Enable_YCM_Mode
	UserPrefYColor = DefColor;
	UserPrefCColor = DefColor;
	UserPrefMColor = DefColor;
	#endif
	//if(FactoryModeFlag)
	{
		UserPrefRedColorUser = DefColor;
		UserPrefGreenColorUser = DefColor;
		UserPrefBlueColorUser = DefColor;
	}
	#if MWEFunction
	UserPrefHue = 50;
	UserPrefSaturation = 0x80;
	UserPrefSubContrast = DefSubContrast;
	UserPrefSubBrightness = DefSubBrightness;
	// 2006/10/26 6:46PM by Emily     UserPrefSubSharpness = 11;
	//msAdjustSharpness(SUB_WINDOW, 11, 1);	//111223 Modify
	msAdjustSubBrightness( SUB_WINDOW, UserPrefSubBrightness, UserPrefSubBrightness, UserPrefSubBrightness );
	msAdjustVideoContrast( SUB_WINDOW, DefContrastBase + UserPrefContrast );
	msAdjustVideoHue( SUB_WINDOW, UserPrefHue );
	msAdjustVideoSaturation( SUB_WINDOW, UserPrefSaturation );
	#endif
	#if DDCCI_ENABLE && DDCCCIMenu_Enable//20130509
	Set_DDCciFlag();
	Set_DDC2BI_ID();
	#endif
	#if USEFLASH
	UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
	#else
	SaveMonitorSetting(); //1020
	#endif
	#if 0
	if ((SrcInputType < Input_Digital))//
	{
		if((!FactoryModeFlag) && PowerOnFlag) //add PowerOnFlag for DC off/on close Burnin 101220 add by win
		{
			if (mStar_AutoGeomtry() == TRUE)
			{
				UserPrefAutoTimes = 1;
				UserPrefAutoHStart = UserPrefHStart;
				UserPrefAutoVStart = UserPrefVStart;
			}
		}
		{
			BYTE modeIndex, flag;
			flag = SrcFlags; //UserModeFlag
			modeIndex = SaveIndex; //SrcModeIndex;
			SrcFlags &= ~bUserMode;
			#if !USEFLASH
			for (SaveIndex = 0; SaveIndex < NumberOfMode; SaveIndex++)
			{
				NVRam_WriteByte(nvrModeAddr(checksum), 0);
			}
			for (SaveIndex = 0; SaveIndex < NumberOfMode; SaveIndex++)
			{
				modeInfo.HerFreq = 0;
				modeInfo.VerFreq = 0;
				modeInfo.VTotal = 0;
				modeInfo.Flags = 0;
				NVRam_WriteTbl(nvrModeInfoAddr(SaveIndex), (BYTE*) &modeInfo, ModeInfoSize);
			}
			SaveIndex = 0;
			SrcFlags = flag;
			modeInfo.HerFreq = hFreq;
			modeInfo.VerFreq = vFreq;
			modeInfo.VTotal = SrcVTotal;
			modeInfo.Flags = SrcFlags & 0x13;
			NVRam_WriteTbl(nvrModeInfoAddr(SaveIndex), (BYTE*) &modeInfo, ModeInfoSize);
			NVRam_WriteByte(nvrModeAddr(checksum), 0);
			NVRam_WriteByte(nvrMonitorAddr(SavedModeIndex), UserPrefSavedModeIndex);
			SaveModeSetting();
			#else
			SaveIndex = SrcModeIndex;//0;
			SrcFlags = flag;
			#if 1//ndef SETTING_IN_FLASH_12K
			modeInfo.HerFreq = hFreq;
			modeInfo.VerFreq = vFreq;
			modeInfo.VTotal = SrcVTotal;
			modeInfo.Flags = SrcFlags & 0x13;
			#endif
			Flash_ClearModeSet();
			UserPref_EnableFlashSaveBit(bFlashSaveModeBit);
			#endif
		}
	}
	else
	{
		Delay1ms(500);
	}
	#endif
	Osd_SetPosition(UserPrefOsdHStart, UserPrefOsdVStart);
	#if Enable_OsdEngine1
	Osd_SetOsdEngine(1);
	Osd_SetPosition(UserPrefOsdHStart, UserPrefOsdVStart);
	Osd_SetOsdEngine(0);
	#endif
	if (FactoryModeFlag)
	{
		Clr_FactoryModeFlag();
		hw_ClrAmberLed();
		hw_SetGreenLed();
	}
	Clr_BurninModeFlag();
	Clr_DoBurninModeFlag();//edit by lizzie,100429.for DC ON/OFF can't clr burnin mode the 1st time
	SaveMonitorSetting();//UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
	#if ENABLE_OSD_LowBlueLight
	UserprefLowBlueLightMode  = DEF_LowBlueLight_MODE;
	#if LowBlueLightType == LowBlueLight_SharpFunc
	gTempLowBlueMode = LOW_BLUE_LIGHT_OFF;
	#endif
	SetLowBlueLight();
	#endif
	#if sRGBIssue
	UserPrevDcrMode = UserPrefDcrMode;
	UserPrevGamaMode = UserPrefGamaMode;
	UserPrevECOMode = UserPrefECOMode;
	#endif
	return TRUE;
}


Bool AutoConfig(void)
{
	Bool result;
	result = mStar_AutoGeomtry();
	//UserPrefAutoHStart=UserPrefHStart;
	if (result)
	{
		UserPrefAutoHStart = UserPrefHStart;
		UserPrefAutoVStart = UserPrefVStart;
		UserPrefAutoTimes = 1;
	}
	else
	{
		UserPrefHTotal = StandardModeHTotal;
		UserPrefHStart = StandardModeHStart;
		UserPrefVStart = StandardModeVStart;
		UserPrefAutoHStart = UserPrefHStart;
		UserPrefAutoVStart = UserPrefVStart;
		UserPrefPhase = 18;
		UserPrefAutoTimes = 1;
		drvADC_AdjustHTotal( UserPrefHTotal );
		drvADC_SetPhaseCode( UserPrefPhase );
		msWrite2Byte( SC0_07, UserPrefHStart );
		mStar_AdjustVPosition(UserPrefAutoVStart);
	}
	#if USEFLASH
	UserPref_EnableFlashSaveBit(bFlashSaveModeBit);
	#else
	SaveModeSetting();
	#endif
	return result;
}

#if Enabe_DDCCI_FUNCTION


Bool ResetGeometry(void)
{
	#if !USEFLASH
	UserPrefHStart = StandardModeHStart;
	mStar_AdjustHPosition(UserPrefHStart);
	NVRam_WriteByte(nvrModeAddr(HStart), UserPrefHStart);
	UserPrefVStart = StandardModeVStart;
	mStar_AdjustVPosition(UserPrefVStart);
	NVRam_WriteByte(nvrModeAddr(VStart), UserPrefVStart);
	UserPrefHTotal = StandardModeHTotal;
	drvADC_AdjustHTotal( UserPrefHTotal );
	NVRam_WriteByte(nvrModeAddr(HTotal), UserPrefHTotal);
	UserPrefPhase = 0;
	drvADC_SetPhaseCode( UserPrefPhase );
	NVRam_WriteByte(nvrModeAddr(Phase), UserPrefPhase);
	AutoConfig();
	#else
	UserPrefHStart = StandardModeHStart;
	mStar_AdjustHPosition(UserPrefHStart);
	UserPrefVStart = StandardModeVStart;
	mStar_AdjustVPosition(UserPrefVStart);
	UserPrefHTotal = StandardModeHTotal;
	drvADC_AdjustHTotal( UserPrefHTotal );
	UserPrefPhase = 0;
	drvADC_SetPhaseCode( UserPrefPhase );
	AutoConfig();
	#endif
	return TRUE;
}

#endif
// 090430 check
void SaveUserPref(void)
{
	#if USEFLASH
	UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
	if (SrcInputType < Input_Digital)
	{
		UserPref_EnableFlashSaveBit(bFlashSaveModeBit);
	}
	#else
	SaveMonitorSetting();
	if (SrcInputType < Input_Digital)
	{
		SaveModeSetting();
	}
	#endif
}

void SaveUserPrefSetting(BYTE menuPageIndex)
{
	menuPageIndex = 0;
	SaveUserPref();
	Clr_SaveSettingFlag();
}
#if !USEFLASH

void SaveFactorySetting( void )
{
	NVRam_WriteTbl( FactorySettingAddr, ( BYTE* ) &FactorySetting, FactorySettingSize );
	#if DEBUG_MSG
	//printMsg( "Save FactorySetting" );
	#endif
}
#endif


//=======================================================================================
// For Factory alignment
#if 1
Bool AutoColor(void)
{
	Bool result;
	#if CHIP_ID>=CHIP_TSUMC
	if (SrcInputType == Input_Digital  || SrcInputType == Input_Digital2 || SrcInputType == Input_Displayport || SrcInputType == Input_Displayport3 )	//121128 Modify
	#else
	if (SrcInputType == Input_Digital  || SrcInputType == Input_Digital2 || SrcInputType == Input_Displayport ) //121128 Modify
	#endif
		return FALSE;	//120204 Modify
	result = mStar_AutoColor();
	Osd_SetTextColor(CP_RedColor, CP_WhiteColor);
	if (result)
	{
		SaveFactorySetting();//UserPref_EnableFlashSaveBit(bFlashSaveFactoryBit);
	}
	if (UserPrefAutoTimes == 0)
	{
		mStar_AutoGeomtry();
		UserPrefAutoTimes = 1;
		UserPrefAutoHStart = UserPrefHStart;
		UserPrefAutoVStart = UserPrefVStart;
		#if USEFLASH
		UserPref_EnableFlashSaveBit(bFlashSaveModeBit);
		#else
		SaveModeSetting();
		#endif
	}
	else
	{
		Delay1ms(500);
	}
	return result;
}
#if AboutDSUBFunc_Enable
//====================================================
#define ADC_RESOLUTION  0x0FFF
Bool AdjustRedGain(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefAdcRedGain, 0, ADC_RESOLUTION, 1);		//110311 Modify
	if (tempValue == UserPrefAdcRedGain)
	{
		return FALSE;
	}
	UserPrefAdcRedGain = tempValue;
	drvADC_SetRedGainCode(UserPrefAdcRedGain);
	return TRUE;
}
WORD GetRedGainValue(void)
{
	return UserPrefAdcRedGain;
}
Bool AdjustGreenGain(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefAdcGreenGain, 0, ADC_RESOLUTION, 1);		//110311 Modify
	if (tempValue == UserPrefAdcGreenGain)
	{
		return FALSE;
	}
	UserPrefAdcGreenGain = tempValue;
	drvADC_SetGreenGainCode(UserPrefAdcGreenGain);
	return TRUE;
}
WORD GetGreenGainValue(void)
{
	return UserPrefAdcGreenGain;
}
Bool AdjustBlueGain(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefAdcBlueGain, 0, ADC_RESOLUTION, 1);		//110311 Modify
	if (tempValue == UserPrefAdcBlueGain)
	{
		return FALSE;
	}
	UserPrefAdcBlueGain = tempValue;
	drvADC_SetBlueGainCode(UserPrefAdcBlueGain);
	return TRUE;
}
WORD GetBlueGainValue(void)
{
	return UserPrefAdcBlueGain;
}
//====================================================
//====================================================
Bool AdjustAdcRedOffset(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefAdcRedOffset, 0, ADC_RESOLUTION, 1);		//110311 Modify
	if (tempValue == UserPrefAdcRedOffset)
	{
		return FALSE;
	}
	UserPrefAdcRedOffset = tempValue;
	drvADC_SetRedOffsetCode(UserPrefAdcRedOffset);
	return TRUE;
}
WORD GetAdcRedOffsetValue(void)
{
	return UserPrefAdcRedOffset;
}
Bool AdjustAdcGreenOffset(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefAdcGreenOffset, 0, ADC_RESOLUTION, 1);		//110311 Modify
	if (tempValue == UserPrefAdcGreenOffset)
	{
		return FALSE;
	}
	UserPrefAdcGreenOffset = tempValue;
	drvADC_SetGreenOffsetCode(UserPrefAdcGreenOffset);
	return TRUE;
}
WORD GetAdcGreenOffsetValue(void)
{
	return UserPrefAdcGreenOffset;
}
Bool AdjustAdcBlueOffset(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefAdcBlueOffset, 0, ADC_RESOLUTION, 1);		//110311 Modify
	if (tempValue == UserPrefAdcBlueOffset)
	{
		return FALSE;
	}
	UserPrefAdcBlueOffset = tempValue;
	drvADC_SetBlueOffsetCode(UserPrefAdcBlueOffset);
	return TRUE;
}
WORD GetAdcBlueOffsetValue(void)
{
	return UserPrefAdcBlueOffset;
}
#endif
void GetColorTempRGB(ColorType *pstColor)
{
	#if LowBlueLightType == LowBlueLight_SharpFunc
	if(UserPrefColorTemp < CTEMP_LowBlue)
	{
		pstColor->u8Red =  *ColorTempPtr[UserPrefColorTemp][0];
		pstColor->u8Green =  *ColorTempPtr[UserPrefColorTemp][1];
		pstColor->u8Blue =  *ColorTempPtr[UserPrefColorTemp][2];
	}
	else
	{
		pstColor->u8Red =  LBLColorTempPtr[UserprefLowBlueLightMode][0];
		pstColor->u8Green =  LBLColorTempPtr[UserprefLowBlueLightMode][1];
		pstColor->u8Blue =  LBLColorTempPtr[UserprefLowBlueLightMode][2];
	}
	#else
	#if PresetMode_Enable
	if(UserPrefECOMode == ECO_Preset)
	{
		pstColor->u8Red 	= *(ColorTempPtr[UserPrefColorTemp_Preset][0]);
		pstColor->u8Green	= *(ColorTempPtr[UserPrefColorTemp_Preset][1]);
		pstColor->u8Blue	= *(ColorTempPtr[UserPrefColorTemp_Preset][2]);
	}
	else
	#endif
	{
		pstColor->u8Red 	= *(ColorTempPtr[UserPrefColorTemp][0]);
		pstColor->u8Green	= *(ColorTempPtr[UserPrefColorTemp][1]);
		pstColor->u8Blue	= *(ColorTempPtr[UserPrefColorTemp][2]);
	}
	#if ENABLE_OSD_LowBlueLight
	if(LOW_BLUE_LIGHT_Strong == UserprefLowBlueLightMode)
		pstColor->u8Blue -= UserprefLowBlueLightMode * 15;
	else
		pstColor->u8Blue -= UserprefLowBlueLightMode * 10;
	#endif
	#endif
}
void ReadColorTempSetting(void) //120522
{
	#if PresetMode_Enable
	if(UserPrefECOMode == ECO_Preset)
	{
		UserPrefRedColor =  *ColorTempPtr[UserPrefColorTemp_Preset][0];
		UserPrefGreenColor =  *ColorTempPtr[UserPrefColorTemp_Preset][1];
		UserPrefBlueColor =  *ColorTempPtr[UserPrefColorTemp_Preset][2];
		// 2006/11/10 11:13PM by KK   if(!UserPrefDcrMode) // for under DCR mode, the picture show filter
		mStar_AdjustBrightness(UserPrefBrightness_Preset);
		mStar_AdjustContrast(UserPrefContrast_Preset);
	}
	else
	#endif
	{
		#if LowBlueLightType ==  LowBlueLight_SharpFunc
		if(UserPrefColorTemp < CTEMP_LowBlue)
		{
			UserPrefRedColor =  *ColorTempPtr[UserPrefColorTemp][0];
			UserPrefGreenColor =  *ColorTempPtr[UserPrefColorTemp][1];
			UserPrefBlueColor =  *ColorTempPtr[UserPrefColorTemp][2];
		}
		else
		{
			UserPrefRedColor =  LBLColorTempPtr[UserprefLowBlueLightMode][0];
			UserPrefGreenColor =  LBLColorTempPtr[UserprefLowBlueLightMode][1];
			UserPrefBlueColor =  LBLColorTempPtr[UserprefLowBlueLightMode][2];
		}
		#else
		UserPrefRedColor =  *ColorTempPtr[UserPrefColorTemp][0];
		UserPrefGreenColor =  *ColorTempPtr[UserPrefColorTemp][1];
		UserPrefBlueColor =  *ColorTempPtr[UserPrefColorTemp][2];
		#endif
		CheckColorValueRange();
		UserPrefBrightness %= 101;
		// 2006/11/10 11:13PM by KK   if(!UserPrefDcrMode) // for under DCR mode, the picture show filter
		mStar_AdjustBrightness(UserPrefBrightness);
		mStar_AdjustContrast(UserPrefContrast);
	}
}
#if ECO
void SetECO(void)
{
	if (UserPrefECOMode == ECO_Internet)
	{
		UserPrefBrightness = DefBriValue_ECO_Internet;
		UserPrefContrast = DefContrast;
		//mStar_AdjustUserPrefBlacklevel( 50, 50, 50 );
	}
	else if (UserPrefECOMode == ECO_Game)
	{
		UserPrefBrightness = DefBriValue_ECO_Game;
		UserPrefContrast = DefContrast;
		//mStar_AdjustUserPrefBlacklevel( 70, 70, 70 );
	}
	#if ENABLE_FPS_RTS
	else if (UserPrefECOMode == ECO_FPS)
	{
		UserPrefBrightness = 50;
		UserPrefContrast = DefContrast;
	}
	else if (UserPrefECOMode == ECO_RTS)
	{
		UserPrefBrightness = 70;
		UserPrefContrast = DefContrast;
	}
	#endif
	else if (UserPrefECOMode == ECO_Movie)
	{
		UserPrefBrightness = DefBriValue_ECO_Movies;
		UserPrefContrast = DefContrast;
		//mStar_AdjustUserPrefBlacklevel( 50, 50, 50 );
	}
	#if	PresetMode_Enable
	else if (UserPrefECOMode == ECO_Preset)
	{
	}
	#endif
	else
	{
		UserPrefBrightness = UserPrefBrightnessUser;
		UserPrefContrast = UserPrefContrastUser;
		//mStar_AdjustUserPrefBlacklevel( 50, 50, 50 );
	}
	SetColorTemp();
	//mStar_AdjustBrightness(UserPrefBrightness);
	//mStar_AdjustContrast(UserPrefContrast);
}
Bool AdjustECOMode(MenuItemActionType action)
{
	UserPrefDcrMode = 0;
	msDCROnOff(UserPrefDcrMode, MAIN_WINDOW);
	ICE_MAIN_CTRL(0);				//120204 Modify
	ICE_SUB_CTRL(0);				//120204 Modify
	if (action == MIA_DecValue)
	{
		UserPrefECOMode = (UserPrefECOMode + ECO_Nums - 1) % ECO_Nums; //Benz have some bug issue
	}
	else
	{
		UserPrefECOMode = (UserPrefECOMode + 1) % ECO_Nums;
	}
	#if sRGBIssue
	UserPrevECOMode = UserPrefECOMode;
	#endif
	#if CT_sRGB_ENABLE
	if(UserPrefColorTemp == CTEMP_SRGB)
	{
		UserPrefColorTemp = CTEMP_Warm1;
		#if !USEFLASH
		NVRam_WriteByte(nvrMonitorAddr(ColorTemp), UserPrefColorTemp);
		#endif
	}
	#endif
	#if !USEFLASH
	NVRam_WriteByte(nvrMonitorAddr(ECOMode), UserPrefECOMode);
	NVRam_WriteByte(nvrMonitorAddr(DcrMode), UserPrefDcrMode);
	#else
	UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
	#endif
	SetECO();
	return TRUE;
}
#endif
#if Enable_Gamma
Bool AdjustGamaMode(MenuItemActionType action)
{
	{
		if (action == MIA_DecValue)
		{
			UserPrefGamaMode = (UserPrefGamaMode + GAMA_Nums - 1) % GAMA_Nums;
		}
		else
		{
			UserPrefGamaMode = (UserPrefGamaMode + 1) % GAMA_Nums;
		}
		#if sRGBIssue
		UserPrevGamaMode = UserPrefGamaMode;
		#endif
		#if Enable_Gamma
		mStar_SetupGamma( UserPrefGamaMode );
		#endif
		if ( UserPrefDcrMode)  //yz.nie  100414 for colorboost on,adjust gammamode,have pictureboost
		{
			#if !ENABLE_HDMI
			msAccOnOff(1);
			#endif
		}
		#if !USEFLASH
		NVRam_WriteByte(nvrMonitorAddr(GamaMode), UserPrefGamaMode);
		#else
		UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
		#endif
	}
	return TRUE;
}
#endif
Bool AdjustDcrMode(MenuItemActionType action)
{
	#if ENABLE_HDMI
	BYTE XDATA ucDomain;
	#endif
	action = action;
	#if ENABLE_HDMI
	ucDomain = 0x00;
	if(!IsColorspaceRGB())	//130608 xiandi
		ucDomain = 0xFF;
	#endif
	if( UserPrefDcrMode )
	{
		UserPrefDcrMode = 0;
		SetECO();
	}
	else
	{
		UserPrefDcrMode = 1;
		#if CT_sRGB_ENABLE
		if(UserPrefColorTemp == CTEMP_SRGB)		//121122 Modify
		{
			UserPrefColorTemp = CTEMP_Warm1;
			#if !USEFLASH
			NVRam_WriteByte(nvrMonitorAddr(ColorTemp), UserPrefColorTemp);
			#endif
		}
		#endif
		#if DcrResetEcoFuncEnable
		UserPrefECOMode = ECO_Standard;
		ReadColorTempSetting();
		#endif
		#if MWEFunction
		{
			ICE_MAIN_CTRL(0);				//120117 Modify
			ICE_SUB_CTRL(0);				//120117 Modify
		}
		#endif
	}
	#if sRGBIssue
	UserPrevDcrMode = UserPrefDcrMode;
	#endif
	msDCROnOff(UserPrefDcrMode, MAIN_WINDOW);
	#if !USEFLASH
	NVRam_WriteByte(nvrMonitorAddr(DcrMode), UserPrefDcrMode);
	NVRam_WriteByte(nvrMonitorAddr(ECOMode), UserPrefECOMode);
	#else
	UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
	#endif
	return TRUE;
}
//=====================================================================
#if 1
Bool SetFactoryColorTempCool1(void)
{
	UserPrefColorTemp = CTEMP_Cool1;
	ReadColorTempSetting(); // 2006/11/10 6:58PM by KK ReadCool1Setting();
	mStar_AdjustBrightness(UserPrefBrightness);
	mStar_AdjustContrast(UserPrefContrast);
	return TRUE;
}
Bool SetFactoryColorTempWarm1(void)
{
	UserPrefColorTemp = CTEMP_Warm1;
	ReadColorTempSetting(); // 2006/11/10 6:57PM by KK  ReadWarm1Setting();
	mStar_AdjustBrightness(UserPrefBrightness);
	mStar_AdjustContrast(UserPrefContrast);
	return TRUE;
}
#if CT_7500K_ENABLE
Bool SetFactoryColorTempNormal(void)
{
	UserPrefColorTemp = CTEMP_Normal;
	ReadColorTempSetting(); // 2006/11/10 6:58PM by KK ReadNormalSetting();
	mStar_AdjustBrightness(UserPrefBrightness);
	mStar_AdjustContrast(UserPrefContrast);
	return TRUE;
}
#endif
#if CT_sRGB_ENABLE
Bool SetFactoryColorTempSRGB(void)
{
	UserPrefColorTemp = CTEMP_SRGB;
	ReadColorTempSetting(); // 2006/11/10 6:58PM by KK ReadSRGBSetting();
	mStar_AdjustBrightness(UserPrefBrightness);
	mStar_AdjustContrast(UserPrefContrast);
	return TRUE;
}
#endif
#endif
#if 1
//====================================================
Bool AdjustRedColorCool1(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefRedColorCool1, MinColorValue, MaxColorValue, 1);
	if (tempValue == UserPrefRedColorCool1)
	{
		return FALSE;
	}
	UserPrefRedColorCool1 = tempValue;
	#if UsesRGB
	mStar_AdjustContrast(UserPrefContrast);
	#else
	mStar_AdjustRedColor(UserPrefRedColorCool1, UserPrefContrast);
	#endif
	return TRUE;
}
Bool AdjustGreenColorCool1(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefGreenColorCool1, MinColorValue, MaxColorValue, 1);
	if (tempValue == UserPrefGreenColorCool1)
	{
		return FALSE;
	}
	UserPrefGreenColorCool1 = tempValue;
	#if UsesRGB
	mStar_AdjustContrast(UserPrefContrast);
	#else
	mStar_AdjustGreenColor(UserPrefGreenColorCool1, UserPrefContrast);
	#endif
	return TRUE;
}
Bool AdjustBlueColorCool1(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefBlueColorCool1, MinColorValue, MaxColorValue, 1);
	if (tempValue == UserPrefBlueColorCool1)
	{
		return FALSE;
	}
	UserPrefBlueColorCool1 = tempValue;
	#if UsesRGB
	mStar_AdjustContrast(UserPrefContrast);
	#else
	mStar_AdjustBlueColor(UserPrefBlueColorCool1, UserPrefContrast);
	#endif
	return TRUE;
}

WORD GetRColorCool1Value(void)
{
	return UserPrefRedColorCool1;
}
WORD GetGColorCool1Value(void)
{
	return UserPrefGreenColorCool1;
}
WORD GetBColorCool1Value(void)
{
	return UserPrefBlueColorCool1;
}

//====================================================
Bool AdjustRedColorWarm1(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefRedColorWarm1, MinColorValue, MaxColorValue, 1);
	if (tempValue == UserPrefRedColorWarm1)
	{
		return FALSE;
	}
	UserPrefRedColorWarm1 = tempValue;
	#if UsesRGB
	mStar_AdjustContrast(UserPrefContrast);
	#else
	mStar_AdjustRedColor(UserPrefRedColorWarm1, UserPrefContrast);
	#endif
	return TRUE;
}
Bool AdjustGreenColorWarm1(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefGreenColorWarm1, MinColorValue, MaxColorValue, 1);
	if (tempValue == UserPrefGreenColorWarm1)
	{
		return FALSE;
	}
	UserPrefGreenColorWarm1 = tempValue;
	#if UsesRGB
	mStar_AdjustContrast(UserPrefContrast);
	#else
	mStar_AdjustGreenColor(UserPrefGreenColorWarm1, UserPrefContrast);
	#endif
	return TRUE;
}
Bool AdjustBlueColorWarm1(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefBlueColorWarm1, MinColorValue, MaxColorValue, 1);
	if (tempValue == UserPrefBlueColorWarm1)
	{
		return FALSE;
	}
	UserPrefBlueColorWarm1 = tempValue;
	#if UsesRGB
	mStar_AdjustContrast(UserPrefContrast);
	#else
	mStar_AdjustBlueColor(UserPrefBlueColorWarm1, UserPrefContrast);
	#endif
	return TRUE;
}
WORD GetRColorWarm1Value(void)
{
	return UserPrefRedColorWarm1;
}
WORD GetGColorWarm1Value(void)
{
	return UserPrefGreenColorWarm1;
}
WORD GetBColorWarm1Value(void)
{
	return UserPrefBlueColorWarm1;
}

//===============================================================
#if CT_7500K_ENABLE
Bool AdjustRedColorNormal(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefRedColorNormal, MinColorValue, MaxColorValue, 1);
	if (tempValue == UserPrefRedColorNormal)
	{
		return FALSE;
	}
	UserPrefRedColorNormal = tempValue;
	#if UsesRGB
	mStar_AdjustContrast(UserPrefContrast);
	#else
	mStar_AdjustRedColor(UserPrefRedColorNormal, UserPrefContrast);
	#endif
	return TRUE;
}
Bool AdjustGreenColorNormal(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefGreenColorNormal, MinColorValue, MaxColorValue, 1);
	if (tempValue == UserPrefGreenColorNormal)
	{
		return FALSE;
	}
	UserPrefGreenColorNormal = tempValue;
	#if UsesRGB
	mStar_AdjustContrast(UserPrefContrast);
	#else
	mStar_AdjustGreenColor(UserPrefGreenColorNormal, UserPrefContrast);
	#endif
	return TRUE;
}
Bool AdjustBlueColorNormal(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefBlueColorNormal, MinColorValue, MaxColorValue, 1);
	if (tempValue == UserPrefBlueColorNormal)
	{
		return FALSE;
	}
	UserPrefBlueColorNormal = tempValue;
	#if UsesRGB
	mStar_AdjustContrast(UserPrefContrast);
	#else
	mStar_AdjustBlueColor(UserPrefBlueColorNormal, UserPrefContrast);
	#endif
	return TRUE;
}

WORD GetRColorNormalValue(void)
{
	return UserPrefRedColorNormal;
}
WORD GetGColorNormalValue(void)
{
	return UserPrefGreenColorNormal;
}
WORD GetBColorNormalValue(void)
{
	return UserPrefBlueColorNormal;
}
#endif
//====================================================
#if CT_sRGB_ENABLE
Bool AdjustRedColorSRGB(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefRedColorSRGB, MinColorValue, MaxColorValue, 1);
	if (tempValue == UserPrefRedColorSRGB)
	{
		return FALSE;
	}
	UserPrefRedColorSRGB = tempValue;
	#if UsesRGB
	mStar_AdjustContrast(UserPrefContrast);
	#else
	mStar_AdjustRedColor(UserPrefRedColorSRGB, UserPrefContrast);
	#endif
	return TRUE;
}
Bool AdjustGreenColorSRGB(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefGreenColorSRGB, MinColorValue, MaxColorValue, 1);
	if (tempValue == UserPrefGreenColorSRGB)
	{
		return FALSE;
	}
	UserPrefGreenColorSRGB = tempValue;
	#if UsesRGB
	mStar_AdjustContrast(UserPrefContrast);
	#else
	mStar_AdjustGreenColor(UserPrefGreenColorSRGB, UserPrefContrast);
	#endif
	return TRUE;
}
Bool AdjustBlueColorSRGB(MenuItemActionType action)
{
	WORD tempValue;
	tempValue = DecIncValue(action, UserPrefBlueColorSRGB, MinColorValue, MaxColorValue, 1);
	if (tempValue == UserPrefBlueColorSRGB)
	{
		return FALSE;
	}
	UserPrefBlueColorSRGB = tempValue;
	#if UsesRGB
	mStar_AdjustContrast(UserPrefContrast);
	#else
	mStar_AdjustBlueColor(UserPrefBlueColorSRGB, UserPrefContrast);
	#endif
	return TRUE;
}

WORD GetRColorSRGBValue(void)
{
	return UserPrefRedColorSRGB;
}
WORD GetGColorSRGBValue(void)
{
	return UserPrefGreenColorSRGB;
}
WORD GetBColorSRGBValue(void)
{
	return UserPrefBlueColorSRGB;
}
#endif
#endif
#if ENABLE_FACTORY_SSCADJ	//120305 Modify
Bool AdjustFactorySSCModulation( MenuItemActionType action )
{
	WORD xdata tempValue;
	tempValue = DecIncValue( action, FactorySetting.SSCModulation, 0, PANEL_SSC_MODULATION_MAX, 1 );
	//tempValue = DecIncValue( action, FactorySetting.SSCModulation, 0, MAX_MODULATION, 1 );
	if( tempValue == FactorySetting.SSCModulation )
		return FALSE;
	FactorySetting.SSCModulation = tempValue;
	mStar_SetPanelSSC(FactorySetting.SSCModulation, FactorySetting.SSCPercentage);
	#if USEFLASH
	Set_FlashForceSaveFactoryFlag();
	#else
	NVRam_WriteByte( nvrFactoryAddr( SSCModulation ), FactorySetting.SSCModulation );
	#endif
	return TRUE;
}

WORD GetFactorySSCModulationValue( void )
{
	return FactorySetting.SSCModulation;
}

Bool AdjustFactorySSCPercentage( MenuItemActionType action )
{
	WORD xdata tempValue;
	tempValue = DecIncValue( action, FactorySetting.SSCPercentage, 0, PANEL_SSC_PERCENTAGE_MAX, 1 );
	//tempValue = DecIncValue( action, FactorySetting.SSCPercentage, 0, MAX_PERCENTAGE, 1 );
	if( tempValue == FactorySetting.SSCPercentage )
		return FALSE;
	FactorySetting.SSCPercentage = tempValue;
	mStar_SetPanelSSC(FactorySetting.SSCModulation, FactorySetting.SSCPercentage);
	#if USEFLASH
	Set_FlashForceSaveFactoryFlag();
	#else
	NVRam_WriteByte( nvrFactoryAddr( SSCPercentage ), FactorySetting.SSCPercentage );
	#endif
	return TRUE;
}

WORD GetFactorySSCPercentageValue( void )
{
	return FactorySetting.SSCPercentage;
}
#endif
//======================================================================================
Bool EnableBurninMode(void)
{
	PatternNo = 0;
	drvOSD_FrameColorEnable(TRUE);
	return TRUE;
}
#if 1
WORD GetBurninValue(void)
{
	return (BurninModeFlag) ? (1) : (0);
}
Bool AdjustBurnin(MenuItemActionType action)
{
	action = action;
	if (BurninModeFlag)
	{
		Clr_BurninModeFlag();
		Clr_DoBurninModeFlag();	//120112 Modify for TPV Request
	}
	else
	{
		Set_BurninModeFlag();
		Set_DoBurninModeFlag();	//120112 Modify for TPV Request
	}
	Delay1ms(200);
	return TRUE;
}
#endif

#if !USEFLASH // 130829 larry
Bool EraseAllEEPROMCell( void )
{
	if( UserPrefBrightness == 0 && UserPrefContrast == MinContrastValue )
	{
		WORD  i;
		#if (EEPROM_TYPE==EEPROM_24C32)
		BYTE xdata EmplyTable[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,};
		for( i = 0; i < 0xff; i++ )
			NVRam_WriteTbl(i * (16), (BYTE*) &EmplyTable, 16);
		#else
		#if (EEPROM_TYPE==EEPROM_24C04)
		for( i = 0; i < 0x1ff; i++ )
		#elif (EEPROM_TYPE==EEPROM_24C16)
		for( i = 0; i < 0x7ff; i++ )
		#endif
			NVRam_WriteByte( i, 0xFF );
		#endif
		//Power_TurnOnAmberLed();
		return TRUE;
	}
	else
		return FALSE;
}
#endif

#if 0//DisplayPowerOnLogo//130613 Jun
WORD GetLogoValue(void)
{
	return (UserPrefLogoON) ? (1) : (0);
}
Bool AdjustLogo(MenuItemActionType action)
{
	action = action;
	if (UserPrefLogoON)
	{
		UserPrefLogoON = 0; //130613 Modify for TPV Request
	}
	else
	{
		UserPrefLogoON = 1; //130613 Modify for TPV Request
	}
	#if USEFLASH
	SaveFactorySetting();
	#else
	NVRam_WriteByte(nvrFactoryAddr(LogoON), UserPrefLogoON);
	#endif
	return TRUE;
}
#endif
#if Enable_ProductModeAdjust
WORD GetProductModeValue(void)
{
	return (0);
}
Bool AdjustProductMode(MenuItemActionType action)
{
	action = action;
	if(UserPrefBrightness == 0 && UserPrefContrast == MinContrastValue)
	{
		{
			#if USEFLASH
			FactoryProductModeValue = ProductModeOnValue;
			UserPref_EnableFlashSaveBit(bFlashSaveFactoryBit);
			#else
			//WORD temp=ProductModeOnValue;
			//NVRam_WriteTbl(ProductModeAddr, (BYTE*)(&temp), 2);
			NVRam_WriteWord(ProductModeAddr, ProductModeOnValue);
			#endif
			Set_GreenLedFlash(5);
		}
	}
	return TRUE;
}
#endif
//====================================================

Bool EnterDisplayLogo(void)
{
	OsdCounter = 3;
	mStar_SetupFreeRunMode();
	Osd_Hide();
	Power_TurnOnPanel();
	Osd_Show();
	return TRUE;
}


#endif
#if DDCCI_ENABLE
#if 0
void AdjustTempColorTemp(BYTE ctemp)
{
	mStar_AdjustBrightness(*(ColorTempPtr[ctemp][0])); //wei1010
	mStar_AdjustRedColor(*(ColorTempPtr[ctemp][1]), *(ColorTempPtr[ctemp][2]));
	mStar_AdjustGreenColor(*(ColorTempPtr[ctemp][1]), *(ColorTempPtr[ctemp][3]));
	mStar_AdjustBlueColor(*(ColorTempPtr[ctemp][1]), *(ColorTempPtr[ctemp][4]));
}
Bool ResetGeometry(void)
{
	//Reset HStart
	UserPrefHStart = StandardModeHStart;
	mStar_AdjustHPosition(UserPrefHStart);
	NVRam_WriteByte(nvrModeAddr(HStart), UserPrefHStart);
	//Reset VStart
	UserPrefVStart = StandardModeVStart;
	mStar_AdjustVPosition(UserPrefVStart);
	NVRam_WriteByte(nvrModeAddr(VStart), UserPrefVStart);
	//Reset HTotal
	UserPrefHTotal = StandardModeHTotal;
	mStar_AdjustHTotal(UserPrefHTotal);
	NVRam_WriteByte(nvrModeAddr(HTotal), UserPrefHTotal);
	//Reset Phase
	UserPrefPhase = 0; // Bruce 1211.2003
	mStar_AdjustPhase(UserPrefPhase);
	NVRam_WriteByte(nvrModeAddr(Phase), UserPrefPhase);
	Clr_SaveSettingFlag();
	return TRUE;
}
Bool ResetColorTemp(void)
{
	/*
	UserPrefRedColor9300K=Def9300KRedColor;
	UserPrefGreenColor9300K=Def9300KGreenColor;
	UserPrefBlueColor9300K=Def9300KBlueColor;
	UserPrefRedColor7200K=Def7200KRedColor;
	UserPrefGreenColor7200K=Def7200KGreenColor;
	UserPrefBlueColor7200K=Def7200KBlueColor;
	UserPrefRedColor6500K=Def6500KRedColor;
	UserPrefGreenColor6500K=Def6500KGreenColor;
	UserPrefBlueColor6500K=Def6500KBlueColor;
	NVRam_WriteByte(nvrMonitorAddr(RedColor9300K), UserPrefRedColor9300K);
	NVRam_WriteByte(nvrMonitorAddr(GreenColor9300K), UserPrefGreenColor9300K);
	NVRam_WriteByte(nvrMonitorAddr(BlueColor9300K), UserPrefBlueColor9300K);
	NVRam_WriteByte(nvrMonitorAddr(RedColor7200K), UserPrefRedColor7200K);
	NVRam_WriteByte(nvrMonitorAddr(GreenColor7200K), UserPrefGreenColor7200K);
	NVRam_WriteByte(nvrMonitorAddr(BlueColor7200K), UserPrefBlueColor7200K);
	NVRam_WriteByte(nvrMonitorAddr(RedColor6500K), UserPrefRedColor6500K);
	NVRam_WriteByte(nvrMonitorAddr(GreenColor6500K), UserPrefGreenColor6500K);
	NVRam_WriteByte(nvrMonitorAddr(BlueColor6500K), UserPrefBlueColor6500K);
	 */
	UserPrefRedColor = DefRedColor;
	UserPrefGreenColor = DefGreenColor;
	UserPrefBlueColor = DefBlueColor;
	NVRam_WriteByte(nvrMonitorAddr(RedColor), UserPrefRedColor);
	NVRam_WriteByte(nvrMonitorAddr(GreenColor), UserPrefGreenColor);
	NVRam_WriteByte(nvrMonitorAddr(BlueColor), UserPrefBlueColor);
	UserPrefColorTemp = CTEMP_Cool1;
	NVRam_WriteByte(nvrMonitorAddr(ColorTemp), UserPrefColorTemp);
	AdjustTempColorTemp(UserPrefColorTemp);
	return TRUE;
}
#endif
#endif
#if 0//AudioFunc
Bool SetMute(void)
{
	hw_SetMute();
	//hw_SetStandby();
	return TRUE;
}
#endif



WORD GetPanelOnTimeValue(void)
{
	WORD xdata hour;
	#if Show_BackLightTimeValue
	hour = BlacklitTime_H;
	#endif
	return hour;
}
WORD GetPanelOnTimeMValue(void)
{
	WORD xdata Min;
	#if Show_BackLightTimeValue
	Min = BlacklitTime_M;
	#endif
	return Min;
}



#if 1

WORD GetCheckSumValue(void)
{
	return Code_checksun;
}
#endif


#if F_ShowVsync_Enable
WORD GetVsyncValue(void)
{
	WORD ValueTemp;
	ValueTemp = GetSrcFreesyncFPS();
	return (ValueTemp & 0xFFFF);
}

#endif




#if Enable_Expansion
/*

#define WAIT_V_OUTPUT_BLANKING_START()   { if(!SyncLossState()&&PanelOnFlag){SetTimOutConter(30);while(((msReadByte(SC0_E0)&BIT0)==0)&&bTimeOutCounterFlag);\
                                        SetTimOutConter(30);while(((msReadByte(SC0_E0)&BIT0)!=0)&&bTimeOutCounterFlag);}}//20130227 modify for DC OFF issue
*/
void SetExpansionMode(void)
{
	mStar_WaitForDataBlanking();    //120204 Modify
	mStar_BlackWhiteScreenCtrl(BW_SCREEN_BLACK);
	mStar_WaitForDataBlanking();    //120204 Modify
	#if (CHIP_ID!=CHIP_TSUMU && CHIP_ID!=CHIP_TSUM2&& CHIP_ID!=CHIP_TSUMC&& CHIP_ID!=CHIP_TSUMD&& CHIP_ID!=CHIP_TSUM9&& CHIP_ID!=CHIP_TSUMF)
	mStar_SetScalingFactor();
	#else // 121113 coding, check it again in gaming model
	#if CHIP_ID==CHIP_TSUMU		//william130802 For Q2770PQU 4:3 fail
	hw_ClrBlacklit();
	Delay1ms(300);
	#endif
	#if ENABLE_OVER_SCAN ||  CHIP_ID==CHIP_TSUMD //130909 nick add for FRC case
	mStar_SetCaptureWindow();
	#endif
	mStar_SetupPath();
	mStar_SetTimingGen(PanelWidth, PanelHeight, FALSE);
	#if ENABLE_OVER_SCAN
	//if(!g_SetupPathInfo.bFBMode)
	mStar_SetPanelTiming();
	#endif
	Delay1ms(300);
	hw_SetBlacklit();
	#endif
	#if 0//ENABLE_RTE
	if(
    #if 0
    #else
	    UserPrefRTEMode == OFF
    #endif
    #if ENABLE_DISPLAY_UNDERSCAN
	    || (UnderScanSetting.Enable) || (g_SetupPathInfo.bFBMode)
    #endif
    #if ENABLE_DUAL_LINK
	    || (GetVfreq() > 85
        #if ENABLE_120Hz_OD
	        && !(g_SetupPathInfo.wImgSizeOutH == PanelWidth &&  g_SetupPathInfo.wImgSizeOutV == PanelHeight)
        #endif
	       )//(SrcModeIndex==MODE_1920x1080P_144Hz)
    #endif
	)
	{
		msOverDriveOnOff( FALSE );
	}
	else
	{
		msOverDriveOnOff( FALSE );
		msRTE_LoadLUT();
		msOverDriveOnOff( TRUE );
	}
	#endif
	#if ((CHIP_ID==CHIP_TSUMY)||(CHIP_ID==CHIP_TSUMC)||(CHIP_ID==CHIP_TSUMD)||(CHIP_ID==CHIP_TSUMU)||(CHIP_ID == CHIP_TSUM9)||(CHIP_ID == CHIP_TSUMF))		//130116_1 Henry For Garbage
	WAIT_V_OUTPUT_BLANKING_START();
	#else
	mStar_WaitForDataBlanking();    //120204 Modify
	#endif
	mStar_BlackWhiteScreenCtrl(BW_SCREEN_OFF);
}
Bool AdjustExpansionMode(MenuItemActionType action)
{
	#if ENABLE_OVER_SCAN	//121228 Modify
	//if (INPUT_IS_NATIVE_TIMING())
	//return FALSE;
	#else
	if (!ExpansionFlag)
		return FALSE;
	#endif
	{
		if (action == MIA_DecValue)
		{
			UserprefExpansionMode = (UserprefExpansionMode + Expansion_Nums - 1) % Expansion_Nums;
		}
		else
		{
			UserprefExpansionMode = (UserprefExpansionMode + 1) % Expansion_Nums;
		}
		//UserprefExpansionMode++;
		// UserprefExpansionMode = (UserprefExpansionMode) % Expansion_Nums;
		#if ENABLE_OVER_SCAN	//121228 Modify
		if(UserprefExpansionMode == Expansion_Aspect && INPUT_IS_WILD_TIMING())
		{
			if (action == MIA_DecValue)
			{
				UserprefExpansionMode = (UserprefExpansionMode + Expansion_Nums - 1) % Expansion_Nums;
			}
			else
			{
				UserprefExpansionMode = (UserprefExpansionMode + 1) % Expansion_Nums;
			}
			//UserprefExpansionMode++;
			//UserprefExpansionMode = (UserprefExpansionMode) % Expansion_Nums;
		}
		if((UserprefExpansionMode == Expansion_Aspect || UserprefExpansionMode == Expansion_11) && INPUT_IS_NATIVE_TIMING())
		{
			if (action == MIA_DecValue)
			{
				UserprefExpansionMode = (UserprefExpansionMode + Expansion_Nums - 1) % Expansion_Nums;
			}
			else
			{
				UserprefExpansionMode = (UserprefExpansionMode + 1) % Expansion_Nums;
			}
		}
		if((UserprefExpansionMode == Expansion_Aspect || UserprefExpansionMode == Expansion_11) && INPUT_IS_NATIVE_TIMING())
		{
			if (action == MIA_DecValue)
			{
				UserprefExpansionMode = (UserprefExpansionMode + Expansion_Nums - 1) % Expansion_Nums;
			}
			else
			{
				UserprefExpansionMode = (UserprefExpansionMode + 1) % Expansion_Nums;
			}
		}
		if((UserprefExpansionMode == Expansion_11) && ((StandardModeWidth > PANEL_WIDTH) || (StandardModeHeight > PANEL_HEIGHT)))
		{
			if (action == MIA_DecValue)
			{
				UserprefExpansionMode = (UserprefExpansionMode + Expansion_Nums - 1) % Expansion_Nums;
			}
			else
			{
				UserprefExpansionMode = (UserprefExpansionMode + 1) % Expansion_Nums;
			}
		}
		#endif
		SetExpansionMode();
	}
	#if DEBUG_PRINTDATA
	printData("UserprefExpansionMode:%d", UserprefExpansionMode);
	#endif
	#if !USEFLASH
	NVRam_WriteByte(nvrMonitorAddr(ExpansionMode), UserprefExpansionMode);
	#else
	UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
	#endif
	return TRUE;
}
#endif

#if 0
Bool DoAutoConfig(void)
{
	if(DoAutoConfigFlag)
		AutoConfig();
	Clr_DoAutoConfigFlag();
	return TRUE;
}
#endif

#if 0
void SetDefaultSetting(BYTE ucDef)
{
	if(ucDef)
	{
		if(SrcInputType < Input_Digital) // image setting by default
		{
			if(UserPrefAutoTimes == 0)
			{
				mStar_AdjustHPosition(StandardModeHStart);
				mStar_AdjustVPosition(StandardModeVStart);
			}
			else
			{
				mStar_AdjustHPosition(UserPrefAutoHStart);
				mStar_AdjustVPosition(UserPrefAutoVStart);
			}
			drvADC_AdjustHTotal( StandardModeHTotal );
			drvADC_SetPhaseCode( 0 );
		}
		mStar_AdjustBrightness(DefBrightness);
		mStar_AdjustContrast(DefContrast);
		msWriteByte(0x00, 0x06);
		msWriteByte(0x30, 0x00);
		msWriteByte(0x00, 0x00);
		msWriteByte(SC0_5C, msReadByte(0x5C) & ~BIT3); //disable all sub-win setting
		#if AudioFunc
		mStar_AdjustVolume(50);
		#endif
		#if Enable_Expansion
		{
			mStar_SetScalingFactor();
		}
		#endif
		Osd_SetTransparence(1);		//120119 Modify
		#if OSD_PIVOT_EN  //071226
		if(OSDRotateFlag)
			Osd_SetPosition(50, 50);
		else
		#endif
			Osd_SetPosition(50, 50);
		#if Enable_OsdEngine1
		Osd_SetOsdEngine(1);
		#if OSD_PIVOT_EN  //071226
		if(OSDRotateFlag)
			Osd_SetPosition(50, 50);
		else
		#endif
			Osd_SetPosition(50, 50);
		Osd_SetOsdEngine(0);
		#endif
		#if Enable_Gamma
		mStar_SetupGamma(GAMA1);
		#endif
	}
	else
	{
		if(SrcInputType < Input_Digital) // image setting by user
		{
			mStar_AdjustHPosition(UserPrefHStart);
			mStar_AdjustVPosition(UserPrefVStart);
			drvADC_AdjustHTotal( UserPrefHTotal );
			drvADC_SetPhaseCode( UserPrefPhase );
		}
		#if AudioFunc
		mStar_AdjustVolume(UserPrefVolume);
		#endif
		#if Enable_Expansion
		mStar_SetScalingFactor();
		#endif
//		mStar_SetUserPref();
		mStar_AdjustBrightness( UserPrefBrightness );
		mStar_AdjustContrast(UserPrefContrast);
		if( UserPrefColorFlags )
		{
			msWriteByte(0x00, 0x06);
			if(DemoFlag)
				msWriteByte(0x30, 0x07);
			else
				msWriteByte(0x30, 0x70);
			msWriteByte(0x00, 0x00);
		}
		if (UserPrefDcrMode || DemoFlag || PictureBoostFlag)
		{
			msWriteByte(SC0_5C, msReadByte(SC0_5C) | BIT3);
		}
		Osd_SetTransparence(UserPrefOsdTrans);
		#if OSD_PIVOT_EN  //071226
		if(OSDRotateFlag)
			Osd_SetPosition(100 - UserPrefOsdHStart, 100 - UserPrefOsdVStart);
		else
		#endif
			Osd_SetPosition(UserPrefOsdHStart, UserPrefOsdVStart);
		#if Enable_OsdEngine1
		Osd_SetOsdEngine(1);
		#if OSD_PIVOT_EN  //071226
		if(OSDRotateFlag)
			Osd_SetPosition(100 - UserPrefOsdHStart, 100 - UserPrefOsdVStart);
		else
		#endif
			Osd_SetPosition(UserPrefOsdHStart, UserPrefOsdVStart);
		Osd_SetOsdEngine(0);
		#endif
		#if Enable_Gamma
		mStar_SetupGamma(UserPrefGamaMode);
		#endif
	}
}
#endif


#if 0
WORD GetOverDriveValue(void)
{
	return (OverDriveOnFlag) ? (1) : (0);
}
#endif
#if (ENABLE_RTE)

Bool AdjustOverDrive(MenuItemActionType action)
{
	/*
	    if (action == MIA_DecValue)
	    {
	        UserPrefRTEMode = (UserPrefRTEMode + RTE_Nums - 1) % RTE_Nums;
	    }
	    else
	    {
	        UserPrefRTEMode = (UserPrefRTEMode + 1) % RTE_Nums;
	    }
	    */
	action = action;
	UserPrefRTEMode = UserPrefRTEMode ? 0 : 1;
	if(UserPrefRTEMode == OFF
        #if ENABLE_DISPLAY_UNDERSCAN
	        || (UnderScanSetting.Enable) || (g_SetupPathInfo.bFBMode)
        #endif
        #if ENABLE_DUAL_LINK
	        || ((GetVfreq() > 85) && (!ENABLE_FREESYNC)
            #if ENABLE_120Hz_OD
	            && !(g_SetupPathInfo.wImgSizeOutH == PanelWidth &&  g_SetupPathInfo.wImgSizeOutV == PanelHeight)
            #endif
	           )//(SrcModeIndex==MODE_1920x1080P_144Hz)	//130328 Modify
        #endif
	  )
	{
		//Set_OverDriveOnFlag();
		//Clr_OverDriveOnFlag();
		msOverDriveOnOff( FALSE );
	}
	else
	{
		{
			msOverDriveOnOff( FALSE );
			//Clr_OverDriveOnFlag();
			msRTE_LoadLUT();
			msOverDriveOnOff( TRUE );
		}
	}
	//Delay1ms(200);
	#if !USEFLASH
	NVRam_WriteByte(nvrMonitorAddr(RTEMode), UserPrefRTEMode);
	#else
	UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
	#endif
	return TRUE;
}
#endif




#if PanelminiLVDS || PANEL_VCOM_ADJUST	//110229 Modify
WORD GetVCOMValue(void)
{
	return FactorySetting.VcomValue;
}

Bool AdjustVCOMValue(MenuItemActionType action)
{
	BYTE tempValue;
	tempValue = DecIncValue( action, FactorySetting.VcomValue, MIN_VCOM_VALUE, MAX_VCOM_VALUE, 1 );
	if( tempValue == FactorySetting.VcomValue )
	{
		return FALSE;
	}
	FactorySetting.VcomValue = tempValue;
	msWriteMiniLVDSi2c_Vcom_DAC(FactorySetting.VcomValue);
	return TRUE;
}


#endif


#if ENABLE_FREESYNC
#if F_ShowVsync_Enable
BYTE GetSrcFreesyncFPS(void)
{
	BYTE xdata u8Vfreq = 0xFF;
	DWORD xdata u32OvsPeriod, u8DivN;
	WORD xdata u16TimeOutCnt;
	WORD xdata u16IvsPrd_L;
	BYTE xdata u8IvsPrd_H, u8DivN_L, u8DivN_H;
	u16TimeOutCnt = 600;
	while(u16TimeOutCnt != 0)
	{
		u16TimeOutCnt--;
		u16IvsPrd_L = msRead2Byte(REG_3842);
		u8IvsPrd_H = msReadByte(REG_3844);
		u8DivN_L = msReadByte(REG_3819);
		u8DivN_H = msReadByte(REG_381C);
		u8DivN = (DWORD)(((u8DivN_H & BIT0) << 4) | (u8DivN_L & 0x0F));
		u32OvsPeriod = ((DWORD)u8IvsPrd_H << 16) | u16IvsPrd_L;
		if(u32OvsPeriod != 0)
		{
			u8Vfreq = (((DWORD)CRYSTAL_CLOCK ) * (u8DivN + 1) + u32OvsPeriod / 2) / u32OvsPeriod;
			break;
		}
	}
	return u8Vfreq;
}
#endif

#if FreeSyncMenu_Enable
//#message "Î´ÍêÉÆ£¬Çë×¢Òâ"
Bool SetDRRFunction(void)
{
	hw_ClrBlacklit();//2 jemery  181008 add
	msAPI_combo_IPEnableDDRFlag(UserprefFreeSyncMode);
	return TRUE;
}



Bool AdjustFreeSync( MenuItemActionType action )
{
	action = action;
	if(UserprefFreeSyncMode == FreeSyncMenuItems_On)
		UserprefFreeSyncMode = FreeSyncMenuItems_Off;
	else
		UserprefFreeSyncMode = FreeSyncMenuItems_On;
	Set_OSDFreeSyncActionFlag();
	#if FreeSyncSwitchEDID
	FreeSyncEDIDSwitch(HDMI_EDID, UserprefFreeSyncMode);
	#if ENABLE_HDMI2
	FreeSyncEDIDSwitch(HDMI2_EDID, UserprefFreeSyncMode);
	#endif
	#endif
	SetDRRFunction();
	#if USEFLASH
	UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
	#else
	NVRam_WriteByte(nvrMonitorAddr(FreeSyncMode), UserprefFreeSyncMode);
	#endif
	return TRUE;
}
#endif


#endif
#if ENABLE_OSD_LowBlueLight

Bool SetLowBlueLight(void)
{
	// ColorType CT;
	//	 GetColorTempRGB(&CT);
	//  mStar_AdjustRGBColor(UserPrefContrast, CT.u8Red, CT.u8Green, CT.u8Blue);
	ReadColorTempSetting();
	return TRUE;
}

#if ( LowBlueLightType==LowBlueLight_ColorTemp)||(LowBlueLightType==LowBlueLight_Misc_Group)
Bool AdjustLowBlueLight(MenuItemActionType action)
{
	WORD	u16TempValue;
	u16TempValue = DecIncValueCirculate(action, UserprefLowBlueLightMode, LowBlueLight_MODE_OSD_MIN, LowBlueLight_MODE_OSD_MAX, 1);
	if (u16TempValue == UserprefLowBlueLightMode)
	{
		return FALSE;
	}
	#if CT_sRGB_ENABLE
	if(UserPrefColorTemp == CTEMP_SRGB)
	{
		UserPrefColorTemp = CTEMP_Warm1;
	}
	#endif
	UserprefLowBlueLightMode = u16TempValue;
	SetLowBlueLight();
	return TRUE;
}
#elif ( LowBlueLightType==LowBlueLight_Misc_Guage)
Bool AdjustLowBlueLight(MenuItemActionType action)
{
	WORD	u16TempValue;
	u16TempValue = DecIncValue(action, UserprefLowBlueLightMode, LowBlueLight_MODE_OSD_MIN, LowBlueLight_MODE_OSD_MAX, 1);
	if (u16TempValue == UserprefLowBlueLightMode)
	{
		return FALSE;
	}
	#if CT_sRGB_ENABLE
	if(UserPrefColorTemp == CTEMP_SRGB)
	{
		UserPrefColorTemp = CTEMP_Warm1;
	}
	#endif
	UserprefLowBlueLightMode = u16TempValue;
	SetLowBlueLight();
	return TRUE;
}

#if LowBlueLightType==LowBlueLight_Misc_Guage
WORD GetLowBlueLightValue( void )
{
	//return 5*10;
	return UserprefLowBlueLightMode * 25;
}
#endif

#elif ( LowBlueLightType==LowBlueLight_SharpFunc)
Bool AdjustLowBlueLight(MenuItemActionType action)
{
//	WORD	u16TempValue;
//	u16TempValue = DecIncValue(action, UserprefLowBlueLightMode, LowBlueLight_MODE_OSD_MIN, LowBlueLight_MODE_OSD_MAX, 1);
//	if (u16TempValue == UserprefLowBlueLightMode)
//		return FALSE;
//	 UserprefLowBlueLightMode= u16TempValue;
	if ( action == MIA_IncValue )
	{
		if ( UserprefLowBlueLightMode == LowBlueLight_MODE_OSD_MAX )
			UserprefLowBlueLightMode = LowBlueLight_MODE_OSD_MIN;
		else
			UserprefLowBlueLightMode += 1;
	}
	else if ( action == MIA_DecValue )
	{
		if ( UserprefLowBlueLightMode == LowBlueLight_MODE_OSD_MIN )
			UserprefLowBlueLightMode = LowBlueLight_MODE_OSD_MAX;
		else
			UserprefLowBlueLightMode -= 1;
	}
	gTempLowBlueMode = UserprefLowBlueLightMode;
	SetLowBlueLight();
	return TRUE;
}

#endif
#endif


#if 1
#if Enable_Adjust_SharpnessMenu
WORD GetSharpnessValue( void )
{
	//return GetScale100Value( 5, 0, 10 );
	return GetScale100Value( UserPrefSharpness, MinSharpness, MaxSharpness);	//120105 Modify
}
WORD GetSharpnessRealValue( void )
{
	//return 5*10;
	return UserPrefSharpness * 10;
}
#endif
BYTE GetRealSharpness(void)
{
	#if 1
	if(CURRENT_INPUT_IS_TMDS() || CURRENT_INPUT_IS_DISPLAYPORT())	//121130 Modify
		return SharpnessTable[ByPassSharpness];
	else
	#endif
		return SharpnessTable[UserPrefSharpness];
}
#endif






#if Enable_Adjust_SharpnessMenu
Bool AdjustSharpness( MenuItemActionType action )
{
	WORD tempValue;
	tempValue = DecIncValue( action, UserPrefSharpness, MinSharpness, MaxSharpness, 1 );	//120105 Modify
	if( tempValue == UserPrefSharpness )
	{
		return FALSE;
	}
	UserPrefSharpness = tempValue;
	#if CHIP_ID == CHIP_TSUMV	//130306 Modify
	if((UserPrefSharpness < DefSharpness )
	        || CURRENT_INPUT_IS_DVI()	//20130513 for DVI dot pattern color deviation problem.
	  )
		msAdjustSharpness( MAIN_WINDOW,  GetRealSharpness(), 1);
	else
	#endif
		msAdjustSharpness( MAIN_WINDOW,  GetRealSharpness(), 0);
	return TRUE;
}
#endif





