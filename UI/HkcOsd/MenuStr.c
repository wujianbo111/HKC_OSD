#include "types.h"
#include "board.h"
#include "global.h"
#include "keypaddef.h"
#include "menudef.h"

#if PropFontNewData
#include "menuTextProp_new.h"
#else
#include "menuTextProp.h"
#endif

#define Icon4Color_AddrShift   2
#define Icon8Color_AddrShift   3

BYTE code strBrightnessIcon[7] =
{
	_8ColorMainIconStart + 0 * Icon8Color_AddrShift,
	_8ColorMainIconStart + 1 * Icon8Color_AddrShift,
	_8ColorMainIconStart + 2 * Icon8Color_AddrShift,
	_8ColorMainIconStart + 3 * Icon8Color_AddrShift,
	_8ColorMainIconStart + 4 * Icon8Color_AddrShift,
	_8ColorMainIconStart + 5 * Icon8Color_AddrShift,
	'\0'
};
BYTE code strImageIcon[7] =
{
	_4ColorMainIconStart + 0 * Icon4Color_AddrShift,
	_4ColorMainIconStart + 1 * Icon4Color_AddrShift,
	_4ColorMainIconStart + 2 * Icon4Color_AddrShift,
	_4ColorMainIconStart + 3 * Icon4Color_AddrShift,
	_4ColorMainIconStart + 4 * Icon4Color_AddrShift,
	_4ColorMainIconStart + 5 * Icon4Color_AddrShift,
	'\0'
};

BYTE code strColorTempIcon[7] =
{
	_8ColorMainIconStart + 6 * Icon8Color_AddrShift,
	_8ColorMainIconStart + 7 * Icon8Color_AddrShift,
	_8ColorMainIconStart + 8 * Icon8Color_AddrShift,
	_8ColorMainIconStart + 9 * Icon8Color_AddrShift,
	_8ColorMainIconStart + 10 * Icon8Color_AddrShift,
	_8ColorMainIconStart + 11 * Icon8Color_AddrShift,
	'\0'
};

BYTE code strOSDIcon[7] =
{
	_8ColorMainIconStart + 12 * Icon8Color_AddrShift,
	_8ColorMainIconStart + 13 * Icon8Color_AddrShift,
	_8ColorMainIconStart + 14 * Icon8Color_AddrShift,
	_8ColorMainIconStart + 15 * Icon8Color_AddrShift,
	_8ColorMainIconStart + 16 * Icon8Color_AddrShift,
	_8ColorMainIconStart + 17 * Icon8Color_AddrShift,
	'\0'
};

BYTE code strResetIcon[7] =
{
	_4ColorMainIconStart + 6 * Icon4Color_AddrShift,
	_4ColorMainIconStart + 7 * Icon4Color_AddrShift,
	_4ColorMainIconStart + 8 * Icon4Color_AddrShift,
	_4ColorMainIconStart + 9 * Icon4Color_AddrShift,
	_4ColorMainIconStart + 10 * Icon4Color_AddrShift,
	_4ColorMainIconStart + 11 * Icon4Color_AddrShift,
	'\0'
};

BYTE code strMiscIcon[7] =
{
	_4ColorMainIconStart + 12 * Icon4Color_AddrShift,
	_4ColorMainIconStart + 13 * Icon4Color_AddrShift,
	_4ColorMainIconStart + 14 * Icon4Color_AddrShift,
	_4ColorMainIconStart + 15 * Icon4Color_AddrShift,
	_4ColorMainIconStart + 16 * Icon4Color_AddrShift,
	_4ColorMainIconStart + 17 * Icon4Color_AddrShift,
	'\0'
};

BYTE* BrightnessIcon(void)
{
	return strBrightnessIcon;
}
BYTE* ImageIcon(void)
{
	return strImageIcon;
}
BYTE* ColorTempIcon(void)
{
	return strColorTempIcon;
}
BYTE* OSDIcon(void)
{
	return strOSDIcon;
}
BYTE* ResetIcon(void)
{
	return strResetIcon;
}
BYTE* MiscIcon(void)
{
	return strMiscIcon;
}


//----Eson Start----------------------------------
//========= TEXT =========
BYTE* MainMenu_BrightText(void)
{
	return strLuminanceM7[UserPrefLanguage];
}
BYTE* MainMenu_ImageText(void)
{
	return strImageSetupM7[UserPrefLanguage];
}
BYTE* MainMenu_ColorText(void)
{
	return strColorSetupM7[UserPrefLanguage];
}

BYTE* MainMenu_OSDText(void)
{
	return strOSDSetupM7[UserPrefLanguage];
}

BYTE* MainMenu_ResetText(void)
{
	return strResetM7[UserPrefLanguage];
}
BYTE* MainMenu_MiscText(void)
{
	return strExtraM7[UserPrefLanguage];
}
BYTE *Main_FText(void)
{
	return strFactory;
}

//-----------------------------------------------
BYTE *ContrastText( void )
{
	return strContrastM1[UserPrefLanguage];
}
BYTE *BrightnessText( void )
{
	return strBrightnessM1[UserPrefLanguage];
}
BYTE *ECOModeText( void )
{
	return strEcoModeM1[UserPrefLanguage];
}
BYTE *ECOModeValue( void )
{
	if( UserPrefECOMode == ECO_Standard )
	{
		return strStandardM1[UserPrefLanguage];
	}
	else if( UserPrefECOMode == ECO_Internet )
	{
		return strInternetM1[UserPrefLanguage];
	}
	else if( UserPrefECOMode == ECO_Game )
	{
		return strGameM1[UserPrefLanguage];
	}
	#if ENABLE_FPS_RTS
	else if( UserPrefECOMode == ECO_FPS )
	{
		return strFPSM1[UserPrefLanguage];
	}
	else if( UserPrefECOMode == ECO_RTS )
	{
		return strRTSM1[UserPrefLanguage];
	}
	#endif
	else if( UserPrefECOMode == ECO_Movie)
	{
		return strMovieM1[UserPrefLanguage];
	}
	#if	PresetMode_Enable
	else if( UserPrefECOMode == ECO_Preset)
	{
		return strPresetModeM1[UserPrefLanguage];
	}
	#endif
	else
	{
		return strStandardM1[UserPrefLanguage];
	}
}
#if Enable_Gamma
BYTE *GammaText( void )
{
	return strGammaM1[UserPrefLanguage];
}
BYTE *GammaModeValue( void )
{
	BYTE u8gammamode = UserPrefGamaMode;
	if( u8gammamode == GAMA2 )
	{
		return strGamma2M1[UserPrefLanguage];
	}
	else if( u8gammamode == GAMA3 )
	{
		return strGamma3M1[UserPrefLanguage];
	}
	else
	{
		return strGamma1M1[UserPrefLanguage];
	}
}
#endif
BYTE *DCRText( void )
{
	#if PresetMode_Enable && Enable_Gamma
	if(UserPrefECOMode == ECO_Preset)
		return strGammaM1[UserPrefLanguage];
	else
	#endif
		return strDCRM1[UserPrefLanguage];
}
BYTE *DcrValueText( void )
{
	#if PresetMode_Enable && Enable_Gamma
	if(UserPrefECOMode == ECO_Preset)
	{
		if( UserPrefGamaMode == GAMA2 )
		{
			return strGamma2M1[UserPrefLanguage];
		}
		else if( UserPrefGamaMode == GAMA3 )
		{
			return strGamma3M1[UserPrefLanguage];
		}
		else
		{
			return strGamma1M1[UserPrefLanguage];
		}
	}
	else
	#endif
	{
		if( UserPrefDcrMode )
		{
			return strOnM1[UserPrefLanguage];
		}
		else
		{
			return strOffM1[UserPrefLanguage];
		}
	}
}

#if (ENABLE_RTE )
#if PresetMode_Enable
BYTE *OverdriveText( void )
{
	return strOverdriveM6[UserPrefLanguage];
}
BYTE *OverdriveValueText( void )
{
	#if  1
	#if (ENABLE_DUAL_LINK)	//130402 Modify
	if(Disabe_Overdrive_Item)
	{
		return strOffM6[UserPrefLanguage];
	}
	else
	#endif
	{
		if(UserPrefRTEMode == RTE1)
		{
			return strOnM6[UserPrefLanguage];
		}
		else
		{
			return strOffM6[UserPrefLanguage];
		}
	}
	#endif
}
#else
BYTE *OverdriveText( void )
{
	return strOverdriveM1[UserPrefLanguage];
}
BYTE *OverdriveValueText( void )
{
	#if  1
	#if (ENABLE_DUAL_LINK)	//130402 Modify
	if(Disabe_Overdrive_Item)
	{
		return strOffM1[UserPrefLanguage];
	}
	else
	#endif
	{
		if(UserPrefRTEMode == RTE1)
		{
			return strOnM1[UserPrefLanguage];
		}
		else
		{
			return strOffM1[UserPrefLanguage];
		}
	}
	#endif
}
#endif
#endif
//-----------------------------------------------

//-----------------------------------------------------------
BYTE *HPositionText( void )
{
	return strHPositionM2[UserPrefLanguage];
}
BYTE *VPositionText( void )
{
	return strVPositionM2[UserPrefLanguage];
}
BYTE *ClockText( void )
{
	return strClockM2[UserPrefLanguage];
}
BYTE *FocusText( void )
{
	return strPhaseM2[UserPrefLanguage];
}
#if Enable_Func_AdjExpansion
BYTE *ExpansionText( void )
{
	return strImageRatioM2[UserPrefLanguage];
}
BYTE *ExpansionValueText( void )
{
	if( UserprefExpansionMode == Expansion_Aspect && ExpansionFlag )
	{
		return strRatio43M2[UserPrefLanguage];
	}
	#if ENABLE_OVER_SCAN
	else if( UserprefExpansionMode == Expansion_11 )//&& !INPUT_IS_NATIVE_TIMING() )	//121228 Modify
	{
		return strRatio11M63[UserPrefLanguage];
	}
	else if( UserprefExpansionMode == PIC_FORMAT_17Picth )//&& !INPUT_IS_NATIVE_TIMING() )	//121228 Modify
	{
		return strRatio43_17M64[UserPrefLanguage];
	}
	else if( UserprefExpansionMode == PIC_FORMAT_19Picth )//&& !INPUT_IS_NATIVE_TIMING() )	//121228 Modify
	{
		return strRatio43_19M65[UserPrefLanguage];
	}
	else if( UserprefExpansionMode == PIC_FORMAT_W19Picth )//&& !INPUT_IS_NATIVE_TIMING() )	//121228 Modify
	{
		return strRatio1610_19M66[UserPrefLanguage];
	}
	else if( UserprefExpansionMode == PIC_FORMAT_W21_5Picth )//&& !INPUT_IS_NATIVE_TIMING() )	//121228 Modify
	{
		return strRatio169_215M67[UserPrefLanguage];
	}
	else if( UserprefExpansionMode == PIC_FORMAT_W22Picth )//&& !INPUT_IS_NATIVE_TIMING() )	//121228 Modify
	{
		return strRatio1610_22M68[UserPrefLanguage];
	}
	else if( UserprefExpansionMode == PIC_FORMAT_W23Picth )//&& !INPUT_IS_NATIVE_TIMING() )	//121228 Modify
	{
		return strRatio169_23M69[UserPrefLanguage];
	}
	#endif
	else
	{
		return strWideM2[UserPrefLanguage];
	}
}

#endif
//-----------------------------------------------------------------------
//-----------------------------------------------------------
BYTE *ColorTempText( void )
{
	return strColorTempM3[UserPrefLanguage];
}
BYTE *ColorTempValueText( void )
{
	#if PresetMode_Enable
	if(UserPrefECOMode == ECO_Preset)
	{
		if( UserPrefColorTemp_Preset == CTEMP_Warm1)
		{
			return strWarmM3[UserPrefLanguage];
		}
		else if( UserPrefColorTemp_Preset == CTEMP_Normal)
		{
			return strNormalM3[UserPrefLanguage];
		}
		else if( UserPrefColorTemp_Preset == CTEMP_Cool1)
		{
			return strCoolM3[UserPrefLanguage];
		}
		else if( UserPrefColorTemp_Preset == CTEMP_USER )
		{
			return strUserM3[UserPrefLanguage];
		}
		else
		{
			return strWarmM3[UserPrefLanguage];
		}
	}
	else
	#endif
	{
		if( UserPrefColorTemp == CTEMP_Warm1)
		{
			return strWarmM3[UserPrefLanguage];
		}
		#if CT_7500K_ENABLE
		else if( UserPrefColorTemp == CTEMP_Normal)
		{
			return strNormalM3[UserPrefLanguage];
		}
		#endif
		else if( UserPrefColorTemp == CTEMP_Cool1)
		{
			return strCoolM3[UserPrefLanguage];
		}
		#if CT_sRGB_ENABLE
		else if( UserPrefColorTemp == CTEMP_SRGB )
		{
			return strsRGBM3[UserPrefLanguage];
		}
		#endif
		else if( UserPrefColorTemp == CTEMP_USER )
		{
			return strUserM3[UserPrefLanguage];
		}
		#if LowBlueLightType ==  LowBlueLight_SharpFunc
		else if( UserPrefColorTemp == CTEMP_LowBlue )
		{
			return strLowBlueLightM3[UserPrefLanguage];
		}
		#endif
		else
		{
			return strWarmM3[UserPrefLanguage];
		}
	}
}
BYTE *UserColorRText( void )
{
	return strRedM3[UserPrefLanguage];
}
BYTE *UserColorGText( void )
{
	return strGreenM3[UserPrefLanguage];
}
BYTE *UserColorBText( void )
{
	return strBlueM3[UserPrefLanguage];
}
#if ( LowBlueLightType==LowBlueLight_ColorTemp)
BYTE *LowBlueLightText( void )
{
	return strLowBlueLightM3[UserPrefLanguage];
}

BYTE *LowBlueLightStatusText( void )
{
	if(UserprefLowBlueLightMode == LOW_BLUE_LIGHT_Weak)
	{
		return strWeakM3[UserPrefLanguage];
	}
	else if(UserprefLowBlueLightMode == LOW_BLUE_LIGHT_Middle)
	{
		return strMediumM3[UserPrefLanguage];
	}
	else if(UserprefLowBlueLightMode == LOW_BLUE_LIGHT_Strong)
	{
		return strStrongM3[UserPrefLanguage];
	}
	else
	{
		return strOffM3[UserPrefLanguage];
	}
}
#elif ( LowBlueLightType==LowBlueLight_Misc_Guage)
BYTE *LowBlueLightText( void )
{
	return strLowBlueLightM6[UserPrefLanguage];
}
#elif ( LowBlueLightType==LowBlueLight_SharpFunc)
BYTE *LowBlueLightText( void )
{
	return strLowBlueLightM3[UserPrefLanguage];
}

BYTE *LowBlueLightStatusText( void )
{
	if(gTempLowBlueMode == LOW_BLUE_LIGHT_Weak)
	{
		return strWeakM3[UserPrefLanguage];
	}
	else if(gTempLowBlueMode == LOW_BLUE_LIGHT_Middle)
	{
		return strMediumM3[UserPrefLanguage];
	}
	else if(gTempLowBlueMode == LOW_BLUE_LIGHT_Stronger)
	{
		return strStrongerM3[UserPrefLanguage];
	}
	else if(gTempLowBlueMode == LOW_BLUE_LIGHT_Strong)
	{
		return strStrongM3[UserPrefLanguage];
	}
	else
	{
		return strOffM3[UserPrefLanguage];
	}
}
#elif ( LowBlueLightType==LowBlueLight_Misc_Group)
BYTE *LowBlueLightText( void )
{
	return strLowBlueLightM6[UserPrefLanguage];
}

BYTE *LowBlueLightStatusText( void )
{
	if(UserprefLowBlueLightMode == LOW_BLUE_LIGHT_Weak)
	{
		return strWeakM6[UserPrefLanguage];
	}
	else if(UserprefLowBlueLightMode == LOW_BLUE_LIGHT_Middle)
	{
		return strMediumM6[UserPrefLanguage];
	}
	else if(UserprefLowBlueLightMode == LOW_BLUE_LIGHT_Strong)
	{
		return strStrongestM6[UserPrefLanguage];
	}
	else if(UserprefLowBlueLightMode == LOW_BLUE_LIGHT_Stronger)
	{
		return strStrongM6[UserPrefLanguage];
	}
	else
	{
		return strOffM6[UserPrefLanguage];
	}
}
#endif

//-----------------------------------------------------------
#if OsdAdjustHVPos_Enable
BYTE *OsdHPositionText( void )
{
	return strHPositionM4[UserPrefLanguage];
}
BYTE *OsdVPositionText( void )
{
	return strVPositionM4[UserPrefLanguage];
}
#endif
BYTE *OsdTimeOutText( void )
{
	return strTimeoutM4[UserPrefLanguage];
}
BYTE *TransparenceText( void )
{
	return strTransparenceM4[UserPrefLanguage];
}
BYTE *LanguageText( void )
{
	return strLanguageM4[UserPrefLanguage];
}
#if AdjustLanguageFunction
BYTE *LanguageStatusText( void )
{
	return strLanguageStatusM8[UserPrefLanguage];
}
#else

BYTE *strEnglishText( void )
{
	return strEnglishM8[0];
}
BYTE *strFranceText( void )
{
	return strFranshM8[0];
}
BYTE *strEspanolText( void )
{
	return strEspanolM8[0];
}
BYTE *strPortuguesText( void )
{
	return strPortuguesM8[0];
}
BYTE *strDeutschText( void )
{
	return strDeutschM8[0];
}

BYTE *strItalianoText( void )
{
	return strItalianoM8[0];
}
BYTE *strNederlandsText( void )
{
	return strNederlandsM8[0];
}
BYTE * strSvenskaText( void )
{
	return strSvenskaM8[0];
}
BYTE *strSuomiText( void )
{
	return strSuomiM8[0];
}
BYTE *strPolskiText( void )
{
	return strPolskiM8[0];
}

BYTE *strCestinaText( void )
{
	return strCestinaM8[0];
}
BYTE *strPycText( void )
{
	return strPycM8[0];
}
BYTE *strKoreanText( void )
{
	return strKoreanM8[0];
}
BYTE *strTChineseText( void )
{
	return strTChineseM8[0];
}
BYTE *strSChineseText( void )
{
	return strSChineseM8[0];
}
BYTE *strJapanText( void )
{
	return strJapanM8[0];
}

#endif

BYTE *ResetText( void )
{
	return strResetM5[UserPrefLanguage];
}

#if AboutDSUBFunc_Enable
BYTE *SubAutoColorText(void)
{
	return strAutoColorM5[UserPrefLanguage];
}
BYTE *AutoConfigText( void )
{
	return strAutoConfigM5[UserPrefLanguage];
}
#endif
#ifdef OffPower

BYTE *OffTimerText( void )
{
	return strOffTimerM5[UserPrefLanguage];
}
BYTE *NullText( void )
{
	return 0;
}
#endif

//-------------------------------------------------------------
#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
BYTE *InputSelectText( void )
{
	return strInputSelectM6[UserPrefLanguage];
}
#endif
#if !HKC_INPUTSELECT_MODE
#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)

BYTE *InputSourceText( void )
{
	#if ENABLE_AutoDetech
	if (UserPrefInputSelectType == INPUT_PRIORITY_AUTO)//(EnableAutoswitchFlag)
	{
		return strAutoM6[UserPrefLanguage];
	}
	else
	#endif
	{
		#if INPUT_TYPE == INPUT_1A2H || INPUT_TYPE == INPUT_2H //110424 Modify
		if( UserPrefInputType == INPUT_PRIORITY_DVI)
		{
			return strHDMI1M6[UserPrefLanguage];
		}
		else if( UserPrefInputType == INPUT_PRIORITY_HDMI)
		{
			return strHDMI2M6[UserPrefLanguage];	//120511 Modify
		}
		#elif INPUT_TYPE == INPUT_1A1H || INPUT_TYPE == INPUT_1H
		if( UserPrefInputType == INPUT_PRIORITY_HDMI)
		{
			return strHDMIM6[UserPrefLanguage];	//120511 Modify
		}
		#elif INPUT_TYPE == INPUT_1A1D1DP	//130924 xiandi
		if( UserPrefInputType == INPUT_PRIORITY_DVI)
		{
			return strDVIM6[UserPrefLanguage];
		}
		else if( UserPrefInputType == INPUT_PRIORITY_DP)
		{
			return strDPM6[UserPrefLanguage];
		}
		#elif INPUT_TYPE == INPUT_1A1DP	//20151126 Alpha
		if( UserPrefInputType == INPUT_PRIORITY_DP)
		{
			return strDPM6[UserPrefLanguage];
		}
		#elif (INPUT_TYPE == INPUT_1A2H1DP)
		if( UserPrefInputType == INPUT_PRIORITY_HDMI)
		{
			return strHDMI1M6[UserPrefLanguage];
		}
		else if( UserPrefInputType == INPUT_PRIORITY_HDMI2ND)
		{
			return strHDMI2M6[UserPrefLanguage];
		}
		else if( UserPrefInputType == INPUT_PRIORITY_DP)
		{
			return strDPM6[UserPrefLanguage];	// 20130109
		}
		#elif (INPUT_TYPE == INPUT_1A1D1H1DP)
		if( UserPrefInputType == INPUT_PRIORITY_DVI)
		{
			return strDVIM6[UserPrefLanguage];
		}
		else if( UserPrefInputType == INPUT_PRIORITY_HDMI)
		{
			return strHDMIM6[UserPrefLanguage];
		}
		else if( UserPrefInputType == INPUT_PRIORITY_DP)
		{
			return strDPM6[UserPrefLanguage];	// 20130109
		}
		#elif INPUT_TYPE == INPUT_1A1H1DP
		if( UserPrefInputType == INPUT_PRIORITY_HDMI)
		{
			return strHDMIM6[UserPrefLanguage];
		}
		else if( UserPrefInputType == INPUT_PRIORITY_DP)
		{
			return strDPM6[UserPrefLanguage];	// 20130109
		}
		#elif INPUT_TYPE == INPUT_1D1H1DP
		if( UserPrefInputType == INPUT_PRIORITY_HDMI)
		{
			return strHDMIM6[UserPrefLanguage];
		}
		else if( UserPrefInputType == INPUT_PRIORITY_DP)
		{
			return strDPM6[UserPrefLanguage];   // 20130109
		}
		else if( UserPrefInputType == INPUT_PRIORITY_DVI)
		{
			return strDVIM6[UserPrefLanguage];   // 20130109
		}
		#elif INPUT_TYPE == INPUT_1A1D1H	//131113 fay
		if( UserPrefInputType == INPUT_PRIORITY_DVI)
		{
			return strDVIM6[UserPrefLanguage];
		}
		else if( UserPrefInputType == INPUT_PRIORITY_HDMI)
		{
			return strHDMIM6[UserPrefLanguage];
		}
		#else
		if( UserPrefInputType == INPUT_PRIORITY_DVI)
		{
			return strDVIM6[UserPrefLanguage];
		}
		/*
		else if( UserPrefInputType == INPUT_PRIORITY_HDMI)
		{
		    return strHDMIM6[UserPrefLanguage];
		}
		*/
		#endif
		#if INPUT_TYPE != INPUT_1D1H1DP
		else
		{
			return strDSUBM6[UserPrefLanguage];
		}
		#else
		return strDVIM6[UserPrefLanguage];
		#endif
	}
}
#endif
#endif
#if AudioFunc
#if EANBLE_MUTE_ON_OFF

BYTE *MuteText(void)
{
	return strMuteM6[UserPrefLanguage];
}
BYTE *MuteValueText( void )
{
	if( UserPrefMuteState)
	{
		return strOnM6[UserPrefLanguage];
	}
	else
	{
		return strOffM6[UserPrefLanguage];
	}
}
#endif
BYTE *VolumeText(void)
{
	return strVolumeM6[UserPrefLanguage];
}
#endif
#if Enable_Adjust_SharpnessMenu
BYTE *SharpnessText( void )
{
	return strSharpnessM6[UserPrefLanguage];
}
#endif

#if  DDCCI_ENABLE && DDCCCIMenu_Enable
BYTE *DDCCIText( void )
{
	return strDDCCIM6[UserPrefLanguage];
}
BYTE *DDCCIValueText( void )
{
	if( DDCciFlag )
	{
		return strOnM6[UserPrefLanguage];
	}
	else
	{
		return strOffM6[UserPrefLanguage];
	}
}
#endif
#if  FreeSyncMenu_Enable
BYTE *FreeSyncText( void )
{
	return strFreeSyncM6[UserPrefLanguage];
}
BYTE *FreeSyncValueText( void )
{
	#if FREESYNC_DP_on_off
	if (CURRENT_INPUT_IS_HDMI())
		return strOnM6[UserPrefLanguage];
	else if(CURRENT_INPUT_IS_DVI())
		return strOffM6[UserPrefLanguage];
	else
	{
		if(UserprefFreeSyncMode == FreeSyncMenuItems_On) //    if( FreeSyncFlag )
		{
			return strOnM6[UserPrefLanguage];
		}
		else
		{
			return strOffM6[UserPrefLanguage];
		}
	}
	#else
	if(CURRENT_INPUT_IS_VGA())
		return strOffM6[UserPrefLanguage];
	#if ENABLE_FREESYNC
	if(UserprefFreeSyncMode == FreeSyncMenuItems_On) //    if( FreeSyncFlag )
	{
		return strOnM6[UserPrefLanguage];
	}
	else
	#endif
	{
		return strOffM6[UserPrefLanguage];
	}
	#endif
}
#endif
#if 0//ENABLE_FREESYNC
BYTE *FreesyncDesText1( void )
{
	return strFreeSyncDes01M15[UserPrefLanguage];
}
BYTE *FreesyncDesText2( void )
{
	return strFreeSyncDes02M15[UserPrefLanguage];
}
BYTE *Quick_FreesyncText( void )
{
	return strFreeSyncM2[UserPrefLanguage];
}
BYTE *Quick_FreesyncValue( void )
{
	if(UserprefFreeSyncMode == FreeSyncMenuItems_On)
		return strONM2[UserPrefLanguage];
	else
		return strOFFM2[UserPrefLanguage];
}
#endif


//-------------------------------------------------------------



BYTE *InputConnectorText(void)
{
	if (SrcInputType == Input_VGA)
	{
		return strDSUBM6[UserPrefLanguage];
	}
	#if ENABLE_DP_INPUT
	#if CHIP_ID>=CHIP_TSUMC
	#if (INPUT_TYPE == INPUT_1A1DP)
	else if( SrcInputType == Input_Displayport )
	{
		return strDPM6[UserPrefLanguage];
	}
	#else
	else if( SrcInputType == Input_Displayport3 )
	{
		return strDPM6[UserPrefLanguage];
	}
	#endif
	#else
	else if( SrcInputType == Input_Displayport)
	{
		return strDPM6[UserPrefLanguage];
	}
	#endif
	#endif
	#if ENABLE_HDMI
	#if INPUT_TYPE==INPUT_1A1H ||INPUT_TYPE==INPUT_1A1H1DP
	else if(SrcInputType == Input_Digital)
	#else
	else if(SrcInputType == Input_Digital2)
	#endif
	{
		#if INPUT_TYPE==INPUT_1A2H ||INPUT_TYPE == INPUT_2H	//121108 Modify
		return strHDMI2M6[UserPrefLanguage];
		#else
		#if INPUT_TYPE==INPUT_1A2H1DP
		return strHDMI2M6[UserPrefLanguage];
		#else
		return strHDMIM6[UserPrefLanguage];
		#endif
		#endif
	}
	#endif
	else
	{
		#if  INPUT_TYPE==INPUT_1A2H ||INPUT_TYPE == INPUT_2H	//121108 Modify
		return strHDMI1M6[UserPrefLanguage];
		#elif INPUT_TYPE == INPUT_1H
		return strHDMIM6[UserPrefLanguage];
		#else
		#if INPUT_TYPE == INPUT_1A2H1DP
		return strHDMI1M6[UserPrefLanguage];
		#else
		return strDVIM6[UserPrefLanguage];
		#endif
		#endif
	}
}





































//-----------------------------------------------------------



//-----------------------------------------------------------


#if Dual
#if ENABLE_VGA
BYTE *AnalogText( void )
{
	return strDSUBM6[UserPrefLanguage];
}
#endif
#if ENABLE_DVI
BYTE *DigitalText( void )
{
	return strDVIM6[UserPrefLanguage];
}
#endif
#if ENABLE_HDMI
BYTE *HDMIText( void )
{
	#if ENABLE_HDMI2
	return strHDMI1M6[UserPrefLanguage];
	#else
	return strHDMIM6[UserPrefLanguage];
	#endif
}
#endif
#if ENABLE_HDMI2
BYTE *HDMI2Text( void )
{
	return strHDMI2M6[UserPrefLanguage];
}
#endif
#if ENABLE_DP_INPUT
BYTE *DPText( void )
{
	return strDPM6[UserPrefLanguage];
}
#endif




#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
#if ENABLE_AutoDetech
BYTE *AutoText( void )
{
	return strAutoM6[UserPrefLanguage];
}
#endif
#endif

#if HKC_INPUTSELECT_MODE
BYTE *InputTypeRationText( void )
{
//CURRENT_INPUT_IS_TMDS()
	#if ENABLE_VGA
	if(UserPrefInputType == Input_VGA  ) //=
		return strDSUBM6[UserPrefLanguage];
	#endif
	#if ENABLE_HDMI
	if(UserPrefInputType == Input_HDMI) //=
		return strHDMIM6[UserPrefLanguage];
	#endif
	#if ENABLE_HDMI2
	if(UserPrefInputType == Input_HDMI2) //==========problem
		strHDMI2M6[UserPrefLanguage];
	#endif
	#if ENABLE_DVI
	if(UserPrefInputType == Input_DVI     )
		return strDVIM6[UserPrefLanguage];
	#endif
	#if ENABLE_DP_INPUT
	if(UserPrefInputType == Input_Displayport)
		return strDPM6[UserPrefLanguage];
	#endif
	#if 0//(INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
	if(UserPrefInputType == INPUT_PRIORITY_AUTO) //=
		return strAutoM6[PropFontIndex];
	#endif
}
#endif

#endif




#if ENABLE_FREESYNC
BYTE *VsyncText( void )
{
	return strVsyncM6[UserPrefLanguage];
}
#endif

//-----------------------------------------------------------
BYTE *OutOfRangeText( void )
{
	return strInputNotSupportM9[UserPrefLanguage];
}
BYTE * CableNotConnectText( void )
{
	return strCableNotConnectedM10[UserPrefLanguage];
}

BYTE *NoSyncText( void )
{
	return strNoSignalM11[UserPrefLanguage];
}





#ifdef OffPower
BYTE *OffTimerM98Text( void )
{
	return strOffTimerM98[UserPrefLanguage];
}
BYTE *MonitorOffText( void )
{
	return strMonitorOffM98[UserPrefLanguage];
}
#endif



#if Hot_Corss_ColorSelect



BYTE code strCorssIcon[41] =
{
	(CorssAddr + 0),  (CorssAddr + 0),  (CorssAddr + 0), (CorssAddr + 1),    (CorssAddr + 2),   (CorssAddr + 0),       (CorssAddr + 0),    (CorssAddr + 0),
	(CorssAddr + 0),  (CorssAddr + 0),  (CorssAddr + 0), (CorssAddr + 3),    (CorssAddr + 4),   (CorssAddr + 0),       (CorssAddr + 0),    (CorssAddr + 0),
	(CorssAddr + 5),  (CorssAddr + 6),  (CorssAddr + 7), (CorssAddr + 8),    (CorssAddr + 9),   (CorssAddr + 7),       (CorssAddr + 10),  (CorssAddr + 11),
	(CorssAddr + 0),  (CorssAddr + 0),  (CorssAddr + 0), (CorssAddr + 12),  (CorssAddr + 13),  (CorssAddr + 0),       (CorssAddr + 0),    (CorssAddr + 0),
	(CorssAddr + 0),  (CorssAddr + 0),  (CorssAddr + 0), (CorssAddr + 14),  (CorssAddr + 15),  (CorssAddr + 0),       (CorssAddr + 0),    (CorssAddr + 0),
	'\0'
};


BYTE* CorssIcon(void)
{
	return strCorssIcon;
}
#elif Hot_Corss_FY_ColorSelect


#define CRM(x)        (CorssAddr+x)
BYTE code strCROWindow_ONE[6][11] =
{
	{
		CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x01), CRM(0x02), CRM(0x00), CRM(0x00),
		CRM(0x00), CRM(0x00),
		0
	},
	{
		CRM(0x00), CRM(0x00), CRM(0x03), CRM(0x04), CRM(0x05), CRM(0x06), CRM(0x07), CRM(0x08),
		CRM(0x00), CRM(0x00),
		0
	},
	{
		CRM(0x09), CRM(0x0A), CRM(0x0B), CRM(0x0A), CRM(0x0C), CRM(0x0D), CRM(0x0A), CRM(0x0E),
		CRM(0x0A), CRM(0x0F),
		0
	},
	{
		CRM(0x10), CRM(0x11), CRM(0x12), CRM(0x11), CRM(0x13), CRM(0x14), CRM(0x11), CRM(0x15),
		CRM(0x11), CRM(0x16),
		0
	},
	{
		CRM(0x00), CRM(0x00), CRM(0x17), CRM(0x18), CRM(0x19), CRM(0x1A), CRM(0x1B), CRM(0x1C),
		CRM(0x00), CRM(0x00),
		0
	},
	{
		CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x1D), CRM(0x1E), CRM(0x00), CRM(0x00),
		CRM(0x00), CRM(0x00),
		0
	}
};



BYTE code strCROWindow_TOW[6][11] =
{
	{
		CRM(0x00), CRM(0x01), CRM(0x02), CRM(0x03), CRM(0x04), CRM(0x05), CRM(0x06), CRM(0x07),
		CRM(0x08), CRM(0x00),
		0
	},
	{
		CRM(0x09), CRM(0x0A), CRM(0x0B), CRM(0x00), CRM(0x0C), CRM(0x0B), CRM(0x00), CRM(0x0C),
		CRM(0x0D), CRM(0x0E),
		0
	},
	{
		CRM(0x0F), CRM(0x10), CRM(0x08), CRM(0x11), CRM(0x12), CRM(0x13), CRM(0x14), CRM(0x01),
		CRM(0x15), CRM(0x16),
		0
	},
	{
		CRM(0x17), CRM(0x18), CRM(0x0B), CRM(0x19), CRM(0x1A), CRM(0x1B), CRM(0x1C), CRM(0x0C),
		CRM(0x1D), CRM(0x1E),
		0
	},
	{
		CRM(0x1F), CRM(0x20), CRM(0x08), CRM(0x00), CRM(0x01), CRM(0x08), CRM(0x00), CRM(0x01),
		CRM(0x21), CRM(0x22),
		0
	},
	{
		CRM(0x00), CRM(0x0C), CRM(0x23), CRM(0x24), CRM(0x25), CRM(0x26), CRM(0x27), CRM(0x28),
		CRM(0x0B), CRM(0x00),
		0
	}
};


BYTE code strCROWindow_THR[6][11] =
{
	{
		CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x01), CRM(0x02), CRM(0x00), CRM(0x00),
		CRM(0x00), CRM(0x00),
		0
	},
	{
		CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x03), CRM(0x04), CRM(0x00), CRM(0x00),
		CRM(0x00), CRM(0x00),
		0
	},
	{
		CRM(0x05), CRM(0x06), CRM(0x07), CRM(0x06), CRM(0x08), CRM(0x09), CRM(0x0A), CRM(0x0B),
		CRM(0x0A), CRM(0x0C),
		0
	},
	{
		CRM(0x0D), CRM(0x0E), CRM(0x0F), CRM(0x0E), CRM(0x10), CRM(0x11), CRM(0x12), CRM(0x13),
		CRM(0x12), CRM(0x14),
		0
	},
	{
		CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x15), CRM(0x16), CRM(0x00), CRM(0x00),
		CRM(0x00), CRM(0x00),
		0
	},
	{
		CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x17), CRM(0x18), CRM(0x00), CRM(0x00),
		CRM(0x00), CRM(0x00),
		0
	}
};

BYTE* CorssIcon1(void)
{
	return strCROWindow_ONE;
}
BYTE* CorssIcon2(void)
{
	return strCROWindow_TOW;
}
BYTE* CorssIcon3(void)
{
	return strCROWindow_THR;
}

#elif Hot_Corss_FND_Select


#define CRM(x)        (CorssAddr+x)
BYTE code strCROWindow_ONE[6][11] =
{
	{
		CRM(0x00), CRM(0x00), CRM(0x01), CRM(0x02), CRM(0x03), CRM(0x04), CRM(0x05), CRM(0x06),
		CRM(0x00), CRM(0x00),
		0
	},
	{
		CRM(0x00), CRM(0x07), CRM(0x08), CRM(0x09), CRM(0x0A), CRM(0x0B), CRM(0x0C), CRM(0x0D),
		CRM(0x0E), CRM(0x00),
		0
	},
	{
		CRM(0x00), CRM(0x0F), CRM(0x10), CRM(0x11), CRM(0x12), CRM(0x13), CRM(0x14), CRM(0x10),
		CRM(0x15), CRM(0x00),
		0
	},
	{
		CRM(0x00), CRM(0x16), CRM(0x17), CRM(0x18), CRM(0x19), CRM(0x1A), CRM(0x1B), CRM(0x17),
		CRM(0x1C), CRM(0x00),
		0
	},
	{
		CRM(0x00), CRM(0x1D), CRM(0x1E), CRM(0x1F), CRM(0x20), CRM(0x21), CRM(0x22), CRM(0x23),
		CRM(0x24), CRM(0x00),
		0
	},
	{
		CRM(0x00), CRM(0x00), CRM(0x25), CRM(0x26), CRM(0x27), CRM(0x28), CRM(0x29), CRM(0x2A),
		CRM(0x00), CRM(0x00),
		0
	}
};



BYTE code strCROWindow_TOW[6][11] =
{
	{
		CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x01), CRM(0x02), CRM(0x00), CRM(0x00),
		CRM(0x00), CRM(0x00),
		0
	},
	{
		CRM(0x00), CRM(0x00), CRM(0x03), CRM(0x04), CRM(0x05), CRM(0x06), CRM(0x07), CRM(0x08),
		CRM(0x00), CRM(0x00),
		0
	},
	{
		CRM(0x09), CRM(0x0A), CRM(0x0B), CRM(0x0C), CRM(0x0D), CRM(0x0E), CRM(0x0F), CRM(0x10),
		CRM(0x11), CRM(0x12),
		0
	},
	{
		CRM(0x13), CRM(0x14), CRM(0x15), CRM(0x16), CRM(0x17), CRM(0x18), CRM(0x19), CRM(0x1A),
		CRM(0x1B), CRM(0x1C),
		0
	},
	{
		CRM(0x00), CRM(0x00), CRM(0x1D), CRM(0x1E), CRM(0x1F), CRM(0x20), CRM(0x21), CRM(0x22),
		CRM(0x00), CRM(0x00),
		0
	},
	{
		CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x23), CRM(0x24), CRM(0x00), CRM(0x00),
		CRM(0x00), CRM(0x00),
		0
	}
};

BYTE code strCROWindow_THR[6][11] =
{
	{
		CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x01), CRM(0x02), CRM(0x00), CRM(0x00),
		CRM(0x00), CRM(0x00),
		0
	},
	{
		CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x03), CRM(0x04), CRM(0x00), CRM(0x00),
		CRM(0x00), CRM(0x00),
		0
	},
	{
		CRM(0x05), CRM(0x06), CRM(0x07), CRM(0x08), CRM(0x09), CRM(0x0A), CRM(0x0B), CRM(0x0C),
		CRM(0x06), CRM(0x0D),
		0
	},
	{
		CRM(0x0E), CRM(0x0F), CRM(0x10), CRM(0x11), CRM(0x12), CRM(0x13), CRM(0x14), CRM(0x15),
		CRM(0x0F), CRM(0x16),
		0
	},
	{
		CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x17), CRM(0x18), CRM(0x00), CRM(0x00),
		CRM(0x00), CRM(0x00),
		0
	},
	{
		CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x00), CRM(0x19), CRM(0x1A), CRM(0x00), CRM(0x00),
		CRM(0x00), CRM(0x00),
		0
	}
};

BYTE* CorssIcon1(void)
{
	return strCROWindow_ONE;
}
BYTE* CorssIcon2(void)
{
	return strCROWindow_TOW;
}
BYTE* CorssIcon3(void)
{
	return strCROWindow_THR;
}

#endif





//----Eson End----------------------------------




