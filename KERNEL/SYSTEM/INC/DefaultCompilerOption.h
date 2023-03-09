
/////////////////////////////////////////////////////////////
// ADC
/////////////////////////////////////////////////////////////
#ifndef ENABLE_ADC_RESET // 120502 coding addition
#define ENABLE_ADC_RESET        1
#endif

#ifndef ENABLE_AUTO_CLOLR_WITHOUT_INPUT // 130517 coding addition
#define ENABLE_AUTO_CLOLR_WITHOUT_INPUT     (CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)
#endif
///////////////////////////////////////////////////////////////
// touch key
///////////////////////////////////////////////////////////////


#ifndef ENABLE_LOW_CONTACT
#define ENABLE_LOW_CONTACT     1
#endif

#ifndef MOBILE_INTERFERENCE
#define MOBILE_INTERFERENCE     0
#endif


///////////////////////////////////////////////////////////////

#ifndef ENABLE_MENULOAD	//111223 Modify
#define ENABLE_MENULOAD             0
#endif

#ifndef HDMI_RB_SWAP	//130109 Modify
#define HDMI_RB_SWAP                                0
#endif

#ifndef HDMI_PN_SWAP	//130109 Modify
#define HDMI_PN_SWAP					0
#endif

#ifndef  DP_AUX_PortB_PNSWAP
#define DP_AUX_PortB_PNSWAP      0
#endif


#ifndef  DP_AUX_PortC_PNSWAP
#define DP_AUX_PortC_PNSWAP      0
#endif

#ifndef _NEW_SOG_DET_
#define _NEW_SOG_DET_               0
#endif

#ifndef ENABLE_TNR
#define ENABLE_TNR                  0
#endif



#ifndef ENABLE_MOTION_SPF
#define ENABLE_MOTION_SPF    0//
#endif

#ifndef ML_USE_INT		//111223 Modify
#define ML_USE_INT                 	0
#endif

#ifndef DISABLE_SSC
#define DISABLE_SSC   0
#endif

#ifndef ENABLE_FACTORY_SSCADJ	//120305 Modify
#define ENABLE_FACTORY_SSCADJ   1
#endif

#ifndef ENABLE_UART1	//120305 Modify
#define ENABLE_UART1           0
#endif

#ifndef ENABLE_DISPLAY_UNDERSCAN
#define ENABLE_DISPLAY_UNDERSCAN    0
#endif

#ifndef DISPLAY_UNDERSCAN_SPACE
#define DISPLAY_UNDERSCAN_SPACE     0// unit: pixel
#endif

#ifndef DISPLAY_UNDERSCAN_FREQ
#define DISPLAY_UNDERSCAN_FREQ      480 // 48Hz
#endif

#ifndef HDCPKEY_IN_7F000	//120420 Modify
#define HDCPKEY_IN_7F000		0
#endif



#ifndef DEBUG_SELFTEST
#define DEBUG_SELFTEST  (0&&ENABLE_DEBUG)
#endif




#ifndef sRGBIssue//130107_1
#define sRGBIssue                      0
#endif


#ifndef ENABLE_BREAKREMINDER	//120713 Modify
#define ENABLE_BREAKREMINDER		0
#endif

#ifndef EXT_TIMER0_1S
#define EXT_TIMER0_1S      	  0      // if ENABLE_BREAKREMINDER need turn on this define for correct timer
#endif

#ifndef ENABLE_MHL
#define ENABLE_MHL       0
#endif

#ifndef ENABLE_DP_INPUT
#define ENABLE_DP_INPUT 0
#endif

///////For eDP Out ////////////
#ifndef ENABLE_DisplayPortTX
#define ENABLE_DisplayPortTX     0
#endif

#ifndef EN_FPLL_FASTLOCK
#define EN_FPLL_FASTLOCK         0
#endif
//////////////////////////////
#ifndef DVI_SUPPORT_INTERLACE_MODE // 121113 coding addition, set to 1 for DVI support interlace mode
#define DVI_SUPPORT_INTERLACE_MODE      0
#endif



#ifndef FRAME_BFF_SEL
#define FRAME_BFF_SEL  FRAME_BFFLESS
#endif



#ifndef ENABLE_VC_8_5
#define ENABLE_VC_8_5          0
#endif

#ifndef ADC_HSYNC_LVL_DEF // each main board may have different setting
#define ADC_HSYNC_LVL_DEF   ADC_HSYNC_LVL_5 // 120725 coding, default set to 5 to compatible with old chips
#endif

//#ifndef LVDS_CLK_1TO2  //20130604 nick add
//#define LVDS_CLK_1TO2               0
//#endif

#ifndef  EANBLE_NEW_DCR_Functing
#define  EANBLE_NEW_DCR_Functing       1
#endif


#ifndef HotKey_ECO_DCR
#define 	HotKey_ECO_DCR   		0
#endif

#ifndef DefLanguage
#define DefLanguage     		LANG_English
#endif



#ifndef FindModeByVwidth
#define FindModeByVwidth          0
#endif



#ifndef  JRY_Color_Tool_Functing
#define JRY_Color_Tool_Functing            0
#endif

#ifndef  Adj_7500K_Temp
#define  Adj_7500K_Temp  				(1&&JRY_Color_Tool_Functing)
#endif

#ifndef JRY_FDDCCI_WriteEDID
#define JRY_FDDCCI_WriteEDID 			  (1&&JRY_Color_Tool_Functing)
#endif

#ifndef JRY_FDDCCI_WriteHDCP
#define JRY_FDDCCI_WriteHDCP 			  (0&&JRY_Color_Tool_Functing)
#endif

#ifndef ENABLE_VGA    //2017/02/20
#define ENABLE_VGA         		0// 1
#endif

#ifndef ENABLE_HDMI2
#define ENABLE_HDMI2           0
#endif

#ifndef User_DDCTO_FlashSave
#define User_DDCTO_FlashSave     0
#endif
#ifndef VGA_Write_EEPROM
#define VGA_Write_EEPROM      	0
#endif
#ifndef DVI_Write_EEPROM
#define DVI_Write_EEPROM      	0// 1
#endif

#ifndef HDMI_Write_EEPROM
#define HDMI_Write_EEPROM      0
#endif

#ifndef HDMI2_Write_EEPROM
#define HDMI2_Write_EEPROM      0
#endif

#ifndef   DP_WRITE_SN
#define	DP_WRITE_SN		0
#endif



#ifndef  Show_BackLightTimeValue
#define Show_BackLightTimeValue        				0
#endif

#ifndef ColorTool_Clear_Time
#define  ColorTool_Clear_Time         0
#endif

#ifndef ENABLE_HK_XDATA_ON_DRAM
#define ENABLE_HK_XDATA_ON_DRAM         			0
#endif

#ifndef DHDMI_SIMPLAYHD_PATCH
#define DHDMI_SIMPLAYHD_PATCH            0
#endif


#ifndef HDMI_PRETEST
#define HDMI_PRETEST                  0
#endif

#ifndef DP_PRETEST
#define   DP_PRETEST                   0
#endif

#if HDMI_PRETEST && DP_PRETEST
#define DISABLE_AUTO_SWITCH             0
#define FIXED_PORT                      INPUT_PRIORITY_AUTO
#else
#if  HDMI_PRETEST
#define DISABLE_AUTO_SWITCH             1
#define FIXED_PORT                      INPUT_PRIORITY_HDMI
#elif DP_PRETEST
#define DISABLE_AUTO_SWITCH             1
#define FIXED_PORT                      INPUT_PRIORITY_DP
#else
#define DISABLE_AUTO_SWITCH            0
#define FIXED_PORT                      INPUT_PRIORITY_AUTO
#endif
#endif


#ifndef ENABLE_HDMI_1_4
#define ENABLE_HDMI_1_4        	     0
#endif

#ifndef HDMITurnOnPanelWhenCTSNStable
#define HDMITurnOnPanelWhenCTSNStable		(1&&ENABLE_HDMI_1_4)
#endif

#ifndef  GAMMA_BYPASS   //Request by TPV for 120Hz panel default byapss gamma
#define GAMMA_BYPASS                0
#endif

#ifndef  FieldInvertCheck
#define FieldInvertCheck                0
#endif

//====For Dual_DVI_Link function Used====//

#ifndef ENABLE_DUAL_LINK
#define ENABLE_DUAL_LINK    	0
#endif


#define DVI_SINGLE_LINK     0
#define DVI_DUAL_LINK       1

#ifndef DL_PXL_RAT_DET
#define DL_PXL_RAT_DET      0   /* DVI DUAL Link detect by pixel rate */
#endif
//====For Dual_DVI_Link function Used====//






#ifndef EEPROM_TYPE
#define EEPROM_TYPE         EEPROM_24C16
#endif


//20130611 nick add

#ifndef USE_VCTRL
#define USE_VCTRL                   0
#endif

#ifndef USE_EXTERNAL_LDO	//130613 nick
#define USE_EXTERNAL_LDO     0//  ((CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)&&(MainBoardType != MainBoard_7319_M0A)&&(MainBoardType != MainBoard_7379_M0A)&&(MainBoardType != MainBoard_7334_M01)&&(MainBoardType != MainBoard_7334_M0B)&&(MainBoardType != MainBoard_7334_M02)&&(MainBoardType != MainBoard_7910_M0A))
#endif

// DDCCI
////////////////////////////////////////////////////////////
#ifndef DDCCI_FILTER_FUNCTION
#define DDCCI_FILTER_FUNCTION       0
#endif

#ifndef DDCCI_REPLY_NULL_MESSAGE // wait for coding
#define DDCCI_REPLY_NULL_MESSAGE    0 // set to reply null message for special case
#endif

#ifndef ENABLE_OVER_SCAN
#define ENABLE_OVER_SCAN    0
#endif

#ifndef ENABLE_ExpanderIO  // Smart monotor for external IO control chip
#define ENABLE_ExpanderIO      0
#endif


#ifndef ENABLE_UART_CONTROL
#define ENABLE_UART_CONTROL               0
#endif


//20130607 nick add

#ifndef DISABLE_UARTCONTROL
#define DISABLE_UARTCONTROL        0
#endif


#ifndef ENABLE_DP_AUDIO
#define ENABLE_DP_AUDIO   0
#endif


#ifndef ENABLE_SHARPNESS_ADJUST		//130221 Modify
#define ENABLE_SHARPNESS_ADJUST			0
#endif


#ifndef ENABLE_BRIGHTNESS_FREQ_20KHZ		//130627 xiandi
#define ENABLE_BRIGHTNESS_FREQ_20KHZ			0
#endif


#ifndef ENABLE_FLASH_UNPROTECT_3A_3D	// TPV new request for that user data in EEPROM or flash, HDCP key always located at 3F000	//130712 xiandi
#define ENABLE_FLASH_UNPROTECT_3A_3D     1// 0   petit 20140421
#endif

#ifndef ENABLE_ANDROID_IR
#define ENABLE_ANDROID_IR   0
#endif


#ifndef ENABLE_DP_EDID_IN_FLASH_3B	//131101 Modify
#define ENABLE_DP_EDID_IN_FLASH_3B		0
#endif


#ifndef ENABLE_LBCLK_FIXED_216M
#define ENABLE_LBCLK_FIXED_216M 1
#endif

#ifndef ENABLE_120Hz_OD
#define ENABLE_120Hz_OD ((ENABLE_DUAL_LINK)&&(ENABLE_RTE)&&(!ENABLE_FREESYNC))
#endif

#ifndef ENABLE_DeltaE
#define ENABLE_DeltaE 0
#endif

#ifndef ENABLE_USE_NewDeltaE
#define ENABLE_USE_NewDeltaE  0
#endif

#ifndef IIYAMASeries
#define IIYAMASeries			0
#endif

#ifndef ENABLE_GAMMA_FIX_PANEL_NOISE
#define ENABLE_GAMMA_FIX_PANEL_NOISE	0
#endif


#ifndef USE_DAC_ADJ
#define USE_DAC_ADJ     0
#endif




#ifndef ENABLE_CHECK_PANEL_VTOTAL
#define ENABLE_CHECK_PANEL_VTOTAL 	(1&&!ENABLE_FREESYNC)
#endif


#ifndef ENABLE_CHECK_PANEL_60HZ_MAX_VTOTAL
#define ENABLE_CHECK_PANEL_60HZ_MAX_VTOTAL 	0
#endif


#ifndef SUPPORT_PROXIMITY
#define SUPPORT_PROXIMITY  0
#endif


#ifndef PANEL_TIMING_ITLC
#define PANEL_TIMING_ITLC					0
#endif




#ifndef ENABLE_Deep_Color   // add for panel 10 bit
#define ENABLE_Deep_Color                    0
#endif

#ifndef ENABLE_TIME_MEASUREMENT
#define ENABLE_TIME_MEASUREMENT    0
#endif

#ifndef ENABLE_I2S_ALWAYS_OUT
#define ENABLE_I2S_ALWAYS_OUT    0
#endif

#ifndef I2S_Earout_Simultaneously
#define I2S_Earout_Simultaneously       0// for TSUMD,check with MainBoard_TSUML887DS_1
#endif

#ifndef DAC_IDLE_TONE_IMPROVEMENT
#define DAC_IDLE_TONE_IMPROVEMENT       0
#endif

#ifndef I2S_gothrough_DPGA
#define I2S_gothrough_DPGA       0// for TSUMD,check with MainBoard_TSUML887DS_1
#endif

#ifndef AUDIDO_ADC_HPF_N
#define AUDIDO_ADC_HPF_N            1   // enable or not enable high pass filter, default enable (1)
#endif
//////////////For SPI Flash Current Setting//////////////////////////////////
#ifndef ENABLE_FLASH_CURRENT_ADJUSTMENT
#define ENABLE_FLASH_CURRENT_ADJUSTMENT   (CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD||CHIP_ID==CHIP_TSUMJ||CHIP_ID==CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)
#endif

#define FLASH_DRIVING_1mA       0
#define FLASH_DRIVING_2mA       1
#define FLASH_DRIVING_3mA       3
#define FLASH_DRIVING_4mA       2

#ifndef FLASH_DEFAULT_CURRENT
#define FLASH_DEFAULT_CURRENT   FLASH_DRIVING_4mA
#endif

////////////NEW CHIP TSUM9 Define ////////////////////////////////////////

#ifndef ENABLE_WATCH_DOG_INT
#define ENABLE_WATCH_DOG_INT            0
#endif

#ifndef ENABLE_XTAL_LESS
#define ENABLE_XTAL_LESS            0
#endif
#ifndef ENABLE_CHECK_TMDS_DE
#define ENABLE_CHECK_TMDS_DE       (CHIP_ID==CHIP_TSUMC || CHIP_ID==CHIP_TSUMD || CHIP_ID==CHIP_TSUM9|| CHIP_ID==CHIP_TSUMF)
#endif

#ifndef BRIGHTNESS_HSYNC_ALIGN
#define BRIGHTNESS_HSYNC_ALIGN    0
#endif

#ifndef ENABLE_RESET_PIN
#define ENABLE_RESET_PIN		0
#endif

#ifndef ENABLE_HDMI_DRR_MCCS
#define ENABLE_HDMI_DRR_MCCS                   (1&& ENABLE_FREESYNC)
#endif

#ifndef ENABLE_CABLE_5V_EDID
#define ENABLE_CABLE_5V_EDID    0
#endif


////////////////For 2010 OSD ///////////////////
//////////////////////////////////////////////



#ifndef Enable_ButtonKeyLongPressFunction
#define Enable_ButtonKeyLongPressFunction	(Enable_Menu_LongPressKeyFunction||Enable_Plus_LongPressKeyFunction||Enable_Minus_LongPressKeyFunction||Enable_Exit_LongPressKeyFunction)
#endif

#ifndef		Enable_Func_AdjExpansion
#define		Enable_Func_AdjExpansion	(Enable_Expansion&&PanelWidth==1920&&PanelHeight==1080)
#endif


///////////////////For 2011 OSD//////////////////////////////////////

#ifndef ENABLE_OSD_HotKeyVolume
#define ENABLE_OSD_HotKeyVolume		        0
#endif

#ifndef DISABLE_VGA_OR_DVI_OSD_HotKeyVolume
#define DISABLE_VGA_OR_DVI_OSD_HotKeyVolume		0
#endif

///////////////////////DP Setting /////////////////////////////////////////
#ifndef ENABLE_DP_PS_CTRL
#define ENABLE_DP_PS_CTRL   0
#endif

////////////////////////////////////////////////////////////////////////
#if 0//ndef WH_REQUEST_DDCCI
#define WH_REQUEST_DDCCI	0
#endif


#ifndef HF_AutoSourceFunction
#define HF_AutoSourceFunction        0
#endif


#ifndef EarphoneDet_Enable
#define EarphoneDet_Enable            0		//  耳机输出
#endif
#ifndef SpeakerDet_Enable
#define SpeakerDet_Enable            0		//喇叭输出
#endif




#ifndef FreeSyncSwitchEDID
#define FreeSyncSwitchEDID		   	0
#endif

#ifndef FREESYNC_DP_on_off
#define FREESYNC_DP_on_off                0
#endif

#ifndef Enable_Factory_Panel
#define Enable_Factory_Panel              1
#endif




#ifndef Check_EEPROM_EDID
#define Check_EEPROM_EDID            0
#endif


#ifndef Enable_Adjust_SharpnessMenu
#define Enable_Adjust_SharpnessMenu 0
#endif

//--------------------------------------------------------------------------
#ifndef ZhongXin_Request
#define ZhongXin_Request            0
#endif


#ifndef Reset_Language
#define Reset_Language            1
#endif

#if PanelType==PanelM195RTN01_V00H
#define EDID_Panel_195            1
#endif

#if	PanelType==PanelM215HTN01_V1||PanelType==PanelM215HAN01||PanelType==PanelMV236FH8||PanelType==PanelLSC490HN03
#define EDID_Panel_215            1
#endif

#if PanelType==PanelM238HV_V00000A
#define EDID_Panel_238            1
#endif




//***********************EDID  Panel  Type*****************************
#ifndef EDID_Panel_195
#define EDID_Panel_195            0
#endif

#ifndef EDID_Panel_215
#define EDID_Panel_215            0
#endif

#ifndef EDID_Panel_238
#define EDID_Panel_238            0
#endif


//*****************************************************************//
//2这是音频的设置 不需要定义这些Define
#ifndef	AudioFunc
#define 	AudioFunc                 	(SpeakerDet_Enable|| EarphoneDet_Enable)
#endif


#if   EarphoneDet_Enable && !SpeakerDet_Enable
#define	Only_EarphoneDet		1
#else
#define	Only_EarphoneDet		0
#endif

#if   !EarphoneDet_Enable && SpeakerDet_Enable
#define	Only_SpeakerDet		1
#else
#define	Only_SpeakerDet		0
#endif

#if   EarphoneDet_Enable && SpeakerDet_Enable
#define	All_AudioDet			1
#else
#define	All_AudioDet			0
#endif

//*****************************************************************
#ifndef AdjustLanguageFunction
#define AdjustLanguageFunction            1   // 1---------group      0----------list
#endif

#ifndef LanguageEnable_English
#define LanguageEnable_English            0
#endif
#ifndef LanguageEnable_France
#define LanguageEnable_France            0
#endif
#ifndef LanguageEnable_Spanish
#define LanguageEnable_Spanish            0
#endif
#ifndef LanguageEnable_Portugues
#define LanguageEnable_Portugues            0
#endif


#ifndef LanguageEnable_German
#define LanguageEnable_German            0
#endif
#ifndef LanguageEnable_Italian
#define LanguageEnable_Italian            0
#endif
#ifndef LanguageEnable_Dutch
#define LanguageEnable_Dutch            0
#endif
#ifndef LanguageEnable_Swedish
#define LanguageEnable_Swedish            0
#endif

#ifndef LanguageEnable_Finnish
#define LanguageEnable_Finnish            0
#endif
#ifndef LanguageEnable_Polish
#define LanguageEnable_Polish            0
#endif
#ifndef LanguageEnable_Czech
#define LanguageEnable_Czech            0
#endif
#ifndef LanguageEnable_Russia
#define LanguageEnable_Russia            0
#endif

#ifndef LanguageEnable_Korea
#define LanguageEnable_Korea            0
#endif
#ifndef LanguageEnable_TChina
#define LanguageEnable_TChina            0
#endif
#ifndef LanguageEnable_SChina
#define LanguageEnable_SChina            0
#endif
#ifndef LanguageEnable_Japan
#define LanguageEnable_Japan            0
#endif
//----------------------------------------------------------------------------------

#ifndef DefVolume
#define DefVolume            50
#endif

//========================================================================
#ifndef 		ENABLE_AutoDetech			//2如果开启，请注意待机唤醒功能的添加
#define		ENABLE_AutoDetech			0
#endif


//===================================================================================================

//1 此code 中暂时用不到的功能

#ifndef Enable_YCM_Mode
#define Enable_YCM_Mode 			 Enable_YMC
#endif


#ifndef PowerSaving_PinContal
#define PowerSaving_PinContal		0 //2 降低待机功耗  8757 翻转开 OD
#endif

#ifndef	Hotkey_BriCon_Enable          //1快捷键	亮度对比度调节
#define   Hotkey_BriCon_Enable		0
#endif

#ifndef	Hotkey_Bri_Enable          //1快捷键	亮度调节
#define   Hotkey_Bri_Enable		0
#endif

#ifndef	Hotkey_Con_Enable          //1快捷键	对比度调节
#define   Hotkey_Con_Enable		0
#endif

#ifndef	Hotkey_ECO_Enable          //1快捷键	ECO 调节
#define   Hotkey_ECO_Enable		0
#endif

#ifndef	Hotkey_DCR_Enable          //1快捷键	ECO 调节
#define   Hotkey_DCR_Enable		HotKey_ECO_DCR
#endif

#ifndef	Hotkey_ECO_Text_Enable
#define	Hotkey_ECO_Text_Enable		0
#endif


//================================================================================================//
#ifndef		FEnterFunction
#define		FEnterFunction			FEnter_AC_MENU
#endif


#ifndef PowerSaveLedFlicker_Enable
#define PowerSaveLedFlicker_Enable            0
#endif

#ifndef FactoryLedFlicker_Enable
#define FactoryLedFlicker_Enable            0
#endif



#ifndef DDCCCIMenu_Enable
#define  DDCCCIMenu_Enable       	0
#endif


#ifndef		DefOsdHPosValue
#define		DefOsdHPosValue	50
#endif

#ifndef		DefOsdVPosValue
#define		DefOsdVPosValue	50
#endif

/***************************************************************************************************/
/***************************************************************************************************/

#ifndef	F_ShowVsync_Enable			//2 需要支持Freesync
#define   F_ShowVsync_Enable		0		//2
#endif


#ifndef ENABLE_FREESYNC
#define ENABLE_FREESYNC   0
#endif


#ifndef FreeSyncMenu_Enable
#define  FreeSyncMenu_Enable       	0
#endif


#ifndef	FreeSyncStatues
#define	FreeSyncStatues				FreeSyncMenuItems_On
#endif




#ifndef Hot_Corss_ColorSelect			//2十字准星红、黄、绿切换
#define Hot_Corss_ColorSelect			0
#endif

#ifndef Hot_Corss_FY_ColorSelect				//2瞄准器3种
#define Hot_Corss_FY_ColorSelect				0
#endif

#ifndef Hot_Corss_FND_Select				//2瞄准器3种
#define Hot_Corss_FND_Select				0
#endif

#ifndef	PresetMode_Enable			//1将开启Gamma
#define	PresetMode_Enable			0
#endif

#ifndef Enable_Gamma
#define Enable_Gamma			(0||PresetMode_Enable)	//111223 Modify
#endif


#ifndef   HH_PivotKey_Enable
#define	HH_PivotKey_Enable			0			//1(+ )
#endif

#ifndef   HH_PivotKey2_Enable
#define	HH_PivotKey2_Enable			0			//1(+ )
#endif

#ifndef Enable_Rotate180Func
#define Enable_Rotate180Func		Enable_8757DDRRotate180			//2(8757+DDR 画面翻转)
#endif


#ifndef OD_MODE_333_HSD					//1 9570 OD 选333 并开启
#define OD_MODE_333_HSD			0
#endif

#ifndef		ENABLE_DDCCI_BLACKLEVEL
#define		ENABLE_DDCCI_BLACKLEVEL		0
#endif

#ifndef		ENABLE_FACTORY_BLACKLEVEL
#define		ENABLE_FACTORY_BLACKLEVEL		0
#endif

#ifndef   Enabe_DDCCI_FUNCTION			//2  禁用除了JRY DDCCI 命令外所有的指令
#define	Enabe_DDCCI_FUNCTION		1
#endif


#ifndef	LowBlueLightType					//2 低蓝光模式选择
#define	LowBlueLightType		LowBlueLight_Off
#endif

#if	LowBlueLightType==LowBlueLight_Off
#define ENABLE_OSD_LowBlueLight		0
#else
#define ENABLE_OSD_LowBlueLight		1
#endif


#ifndef	OsdHelpKeyType					//2 低蓝光模式选择
#define	OsdHelpKeyType		OsdHelpKey_Off
#endif

//1******************************************************************************************

//2 waring  以下定义重要，切勿改动

#ifndef DefRTEMode
#define 	DefRTEMode   		OFF
#endif

#ifndef	CT_sRGB_ENABLE
#define   CT_sRGB_ENABLE			0
#endif

#ifndef		Def_DACGain
#define		Def_DACGain				0x1D
#endif



#define ADCLimited					165 // scaler ADC operating range

#ifndef  AboutDSUBFunc_Enable
#define  AboutDSUBFunc_Enable		ENABLE_VGA
#endif

#ifndef  HowShowFMenu
#define	HowShowFMenu				0   //2       0 直接显示工厂  1 mainmenu进工厂
#endif

#ifndef   SWAP_LR_CHANNL					//2 左右声道切换
#define	SWAP_LR_CHANNL			0
#endif

#ifndef   WriteSN_Functiom_New			//2 这是新的SN 烧录方式，//仅仅适用于具有24C02 的板子
#define   WriteSN_Functiom_New		0
//1  说明
//2   SN 必须存放在第4  位(0x6C-0x7D)
//2 无论几个端口，只是接受V D H DP 顺序烧录SN 的一路
//2 需要给客户提供符合规范的EDID 烧录
#endif





#ifndef		PropFontNewData
#define		PropFontNewData		0
#endif

#ifndef		TimingInfoYpos
#define		TimingInfoYpos			14
#endif

#ifndef		DiaghtAudioInput
#define		DiaghtAudioInput			1
#endif

#ifndef USE_DAC_CODE						//2使用Table 表调节声音大小
#define USE_DAC_CODE				0
#endif

/*********************************************************************************************/
//1 此为特殊要求

#ifndef		EDID_Over_165Hz
#define		EDID_Over_165Hz		0
#endif

/********************************************************************************************/
//1 测试功能添加


#define ENABLE_VGA_INPUT       		ENABLE_VGA//(INPUT_TYPE&INPUT_0A)
#define ENABLE_DVI_INPUT        		ENABLE_DVI
#define ENABLE_HDMI_INPUT       		ENABLE_HDMI
#define ENABLE_HDMI2ND_INPUT    	ENABLE_HDMI2
#define ENABLE_DPlay_INPUT         	ENABLE_DP_INPUT//0


/////////////////////////////////////////////////////////////////////////////////////////////////////////




/********************************************************************************************/
//2  OSD 翻译修改
#ifndef		OD_Trans_Chinese				//2更改OD翻译为响应时间加速
#define		OD_Trans_Chinese		0
#endif



#ifndef 		EN_HotInputSelect_ShowCenter				//2 Source 选择居中显示
#define 		EN_HotInputSelect_ShowCenter		0
#endif

#ifndef		DefBriValue_ECO_Internet
#define		DefBriValue_ECO_Internet	40
#define		DefBriValue_ECO_Game		60
#define		DefBriValue_ECO_Movies		80
#endif

#ifndef		EN_ShowInfoUnderBurinInMenu
#define		EN_ShowInfoUnderBurinInMenu		0		//2老化菜单显示信息
#endif


#ifndef		DefColorTemp
#define		DefColorTemp				CTEMP_Warm1
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef		OSD_NoHotKeyFunc
#define		OSD_NoHotKeyFunc			0					//2 OSD + - 键无快捷键功能使能
#endif


#ifndef		OSD_Trans_ECO_Mode								//3 外加 DCR 改为：Active Contrast；
#define		OSD_Trans_ECO_Mode		0					//1情景模式修改为PresetMode(PC，Movie，Game，ECO)
#endif

#ifndef		ECOMode_NewName			//3      Standard/Web /Game/ Movies
#define		ECOMode_NewName		0	 //3General / Movies / Games / Documents
#endif

#ifndef		OSD_Trans_ColorTemp
#define		OSD_Trans_ColorTemp		0				//2 Color Temperature?9300，6500，5500，User；
#endif

#ifndef		FOSD_Trans_ColorTemp
#define		FOSD_Trans_ColorTemp		0				//2 Color Temperature?99300，6500，7500
#endif


#ifndef		DcrResetEcoFuncEnable
#define		DcrResetEcoFuncEnable		1
#endif

#ifndef		DefSaturationValue
#define		DefSaturationValue			128
#endif


#ifndef		OsdAdjustHVPos_Enable
#define		OsdAdjustHVPos_Enable		1
#endif


#ifndef		Enable_DDCCI_OSDEnable_EN
#define		Enable_DDCCI_OSDEnable_EN		0
#endif


#ifndef		Disable_VgaToAdjustVolume
#define		Disable_VgaToAdjustVolume		0
#endif

#ifndef		Osd_Page2_Focus_Trans
#define		Osd_Page2_Focus_Trans			0			//2 0:聚焦 1: 相位
#endif


#ifndef	   Enable_GDFlash_Save
#define	   Enable_GDFlash_Save			1			//3此Flash需要关闭一些Function
#endif

#ifndef	   Enable_FMFlash_Save
#define	   Enable_FMFlash_Save			0			//3此Flash需要关闭一些Function
#endif

#ifndef	CT_7500K_ENABLE
#define   CT_7500K_ENABLE			0
#endif

#ifndef DAC_VALUE_TAB
#define DAC_VALUE_TAB 				0
#endif


#ifndef	Brightness_Table_Enable
#define	Brightness_Table_Enable			0
#endif


#ifndef	LoadAllPortSeriealnumberByOneVGAPort
#define	LoadAllPortSeriealnumberByOneVGAPort		1
#endif


