
extern BYTE* MainMenu_BrightText(void);
extern BYTE* MainMenu_ImageText(void);
extern BYTE* MainMenu_ColorText(void);
extern BYTE* MainMenu_OSDText(void);
extern BYTE* MainMenu_ResetText(void);
extern BYTE* MainMenu_MiscText(void);

#if !AdjustLanguageFunction
extern BYTE *strEnglishText( void );
extern BYTE *strFranceText( void );
extern BYTE *strEspanolText( void );
extern BYTE *strPortuguesText( void );
extern BYTE *strDeutschText( void );
extern BYTE *strItalianoText( void );
extern BYTE *strNederlandsText( void );
extern BYTE * strSvenskaText( void );
extern BYTE *strSuomiText( void );
extern BYTE *strPolskiText( void );
extern BYTE *strCestinaText( void );
extern BYTE *strPycText( void );
extern BYTE *strKoreanText( void );
extern BYTE *strTChineseText( void );
extern BYTE *strSChineseText( void );
extern BYTE *strJapanText( void );
#endif

extern BYTE* BrightnessIcon(void);
extern BYTE* ImageIcon(void);
extern BYTE* ColorTempIcon(void);
extern BYTE* OSDIcon(void);
extern BYTE* ResetIcon(void);
extern BYTE* MiscIcon(void);
extern BYTE *Main_FText(void);


#if AudioFunc
#if EANBLE_MUTE_ON_OFF

extern BYTE *MuteText( void );
extern BYTE *MuteValueText( void );
#endif
extern BYTE *VolumeText( void );
#endif
#if DDCCI_ENABLE && DDCCCIMenu_Enable
extern BYTE *DDCCIText( void );
extern BYTE *DDCCIValueText( void );
#endif
#if FreeSyncMenu_Enable
extern BYTE *FreeSyncText( void );
extern BYTE *FreeSyncValueText( void );
#endif

#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
extern BYTE *InputSourceText( void );
#endif
#if ENABLE_HDMI2
extern BYTE *HDMI2Text( void );
#endif
#if ENABLE_HDMI
extern BYTE *HDMIText( void );
#endif
#if ENABLE_DP_INPUT
extern BYTE *DPText( void );
#endif
#if ENABLE_DVI
extern BYTE *DigitalText( void );
#endif
#if ENABLE_VGA
extern BYTE *AnalogText(void);
#endif
extern BYTE *AutoText( void );
#if HKC_INPUTSELECT_MODE
extern BYTE *InputTypeRationText( void );
#endif


/*******************************************************************************
*
*
*
*
*
*
*
*
*******************************************************************************/


















extern BYTE *VersionDateText(void);
extern BYTE *ChangeDateText(void);
extern BYTE *ModelNameText(void);
BYTE *ChipNameText( void );

extern BYTE *DateText(void);
extern BYTE *HourText(void);
extern BYTE *ContrastText( void );
extern BYTE *BrightnessText( void );
extern BYTE *ECOModeText( void );
extern BYTE *ECOModeValue( void );
extern BYTE *GammaText( void );
extern BYTE *GammaModeValue( void );
extern BYTE *DCRText( void );
extern BYTE *DcrValueText( void );
#if (ENABLE_RTE)
extern BYTE *OverdriveText( void );
extern BYTE *OverdriveValueText( void );
#endif



extern BYTE *ClockText( void );
extern BYTE *FocusText( void );
extern BYTE *HPositionText( void );
extern BYTE *VPositionText( void );
extern BYTE *SharpnessText( void );


extern BYTE *ColorTempText( void );
extern BYTE *ColorTempValueText( void );
extern BYTE *UserColorRText( void );
extern BYTE *UserColorGText( void );
extern BYTE *UserColorBText( void );
#if MWEFunction

extern BYTE *BF_HueText( void );
extern BYTE *BF_SaturationText( void );

extern BYTE *BF_RightArrowText( void );

#endif

extern BYTE *OsdHPositionText( void );
extern BYTE *OsdVPositionText( void );
extern BYTE *OsdTimeOutText( void );
extern BYTE *TransparenceText( void );
extern BYTE *LanguageText( void );


extern BYTE *InputSelectText( void );
extern BYTE *SubAutoColorText( void );
extern BYTE *AutoConfigText( void );
#if Enable_Adjust_SharpnessMenu
extern BYTE *SharpnessText( void );
#else
#ifdef OffPower
extern BYTE *OffTimerText( void );
extern BYTE *NullText( void );
#endif
#endif
extern BYTE *ResetText( void );



extern BYTE *EraseEEPROMText( void );
#if ENABLE_FREESYNC
extern BYTE *FreeSyncVsyncText( void );
#endif
#if Enable_Expansion
extern BYTE *ExpansionText( void );
extern BYTE *ExpansionValueText( void );
#endif
extern BYTE *InformationExtraText( void );
extern BYTE *InputConnectorText( void );
extern BYTE *ResolutionText( void );
extern BYTE *HFrequenceText( void );
extern BYTE *VFrequenceText( void );

#if ENABLE_FREESYNC
extern BYTE *VsyncText( void );
#endif




extern BYTE *ColorBoostText(void);
extern BYTE *FullText(void);
extern BYTE *NatureSkinText(void);
extern BYTE *GreenFieldText(void);
extern BYTE *SkyBlueText(void);
extern BYTE *AutoDetectText(void);
extern BYTE *DemoText(void);
extern BYTE *FreeColorBarText(void);
extern BYTE *FreeColorFullModeText(void);
extern BYTE *FreeColorSkinProtectModeText(void);
extern BYTE *FreeColorGreenEnhanceModeText(void);
extern BYTE *FreeColorBlueEnhanceModeText(void);
extern BYTE *FreeColorAutoDetectModeText(void);
extern BYTE *FreeColorDemoModeText(void);
extern BYTE *BFHPositionText(void);
extern BYTE *BFVPositionText(void);
extern BYTE *BFPositionText(void);
extern BYTE *BF_FrameSizeText(void);
extern BYTE *BF_BrightnessText(void);
extern BYTE *BF_ContrastText(void);
extern BYTE *BF_HueText(void);
extern BYTE *BF_SaturationText(void);
extern BYTE *BF_PositionText(void);
extern BYTE *BF_RightArrowText(void);
extern BYTE *BF_SwitchText(void);
extern BYTE *BF_SwitchValueText(void);
extern BYTE *OsdHPositionText(void);
extern BYTE *OsdVPositionText(void);
extern BYTE *OsdTransparenceText(void);
extern BYTE *OsdTimeOutText(void);
extern BYTE *LanguageText(void);
#if AdjustLanguageFunction
extern BYTE *LanguageStatusText( void );
#endif
extern BYTE *LanguageValueText(void);
extern BYTE *LanguageValue1Text(void);
extern BYTE *Language1Text(void);
#if 1//Dual
extern BYTE *InputSelectText(void);
#endif
extern BYTE *AutoConfigText(void);
extern BYTE *InformationText(void);
#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
extern BYTE *InputSourceText(void);
#endif


extern BYTE *ExtraBarText(void);
extern BYTE *InformationArrowText(void);
// 071218 reserved for extra page fw version
//extern BYTE *VersionText(void);
//extern BYTE *FW_VerText(void);
#if DDCCI_ENABLE && DDCCCIMenu_Enable
extern BYTE *DDCCIText(void);
extern BYTE *DDCCIValueText(void);
#endif

#if Enable_Expansion
extern BYTE *ExpansionText(void);
extern BYTE *ExpansionValueText(void);
#endif
extern BYTE *InformationExtraText(void);
extern BYTE *InputConnectorText(void);
extern BYTE *ResolutionText(void);
extern BYTE *HResText(void);
extern BYTE *VResText(void);
extern BYTE *X_Text(void);
extern BYTE *HFrequenceText(void);
extern BYTE *VFrequenceText(void);
extern BYTE *KHzText(void);
extern BYTE *HzText(void);


extern BYTE *OutOfRangeText(void);
extern BYTE* CableNotConnectText(void);
extern BYTE *NoSyncText( void );
extern BYTE *NoSyncStatusText( void );

#ifdef OffPower
extern BYTE *OffTimerM98Text( void );
extern BYTE *MonitorOffText( void );
#endif


#if ENABLE_OSD_LowBlueLight
extern BYTE *LowBlueLightText( void );
extern BYTE *LowBlueLightStatusText( void );
#endif

#if Hot_Corss_ColorSelect
extern BYTE* CorssIcon(void);
#elif Hot_Corss_FY_ColorSelect || Hot_Corss_FND_Select
extern BYTE* CorssIcon1(void);
extern BYTE* CorssIcon2(void);
extern BYTE* CorssIcon3(void);
#endif



