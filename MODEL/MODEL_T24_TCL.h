#ifndef TSUMXXF_DEMO_H
#define TSUMXXF_DEMO_H
////////////////////////////////////////////////////////////
// BOARD SELECTION
////////////////////////////////////////////////////////////
#define CHIP_ID                			CHIP_TSUMV
#define MainBoardType    				MainBoard_JRY_L58VHN_GV3
#define PanelType 					PanelLC238LF1L
#define DisplayLogo					TCL_Logo



//#define EEPROM_TYPE       EEPROM_24C16
////////////////////////////////////////////////////////////
///////////////////////////////////////////////
#define ENABLE_XTAL_LESS               	0
#define ENABLE_XTAL_LESS_FPLL           (0 && ENABLE_XTAL_LESS)     // Note: FPLL will stay disabled when the input is DP
#define ENABLE_XTAL_LESS_SW_SLT         (0 && ENABLE_XTAL_LESS)
#define ENABLE_RESET_PIN                0
#define ENABLE_CABLE_5V_EDID          0
///////////////////////////////////////////////
////////////////////////////////////////////////////////////



#define ENABLE_RTE               			0
#define OD_MODE                   			OD_MODE_485 // 1218 coding test

#define DefLanguage     				LANG_SChina//LANG_English

/*****************************************************/
/****************************************************/


#define ENABLE_OVER_SCAN          	0 // 121101 coding addition
#define DVI_PN_SWAP              		1
#define DVI_RB_SWAP 			 	0
#define HDMI_PN_SWAP            		0
#define ENABLE_AUTOEQ           		0

#define ENABLE_SUPERRESOLUTION     	0
#define DDCCI_ENABLE				1
#define Enable_Expansion		  		1
#define WidePanel					1
#define ENABLE_HDCP	 			1
#define HDCPKEY_IN_Flash			1
#define HDCPKEY_IN_7F000			0
//#define OffPower
#define Panel_Inv            				1 // ownbrand use 1
#define LANGUAGE_TYPE				All14Language_AddJap//ASIA//EUROPE//All13Language//All14Language_AddJap
#define Enable_Cache		   			1
#define Enable_OsdEngine1      		0// 1: two OSD engine,; 0: one osd engine

//#define PowerKeyDeBounce
#define PowerKeyDeBounceCount     	30





#define GAMMA_BYPASS    				0

#define FRAME_BFF_SEL       			FRAME_BFFLESS// 130625 william
#define ENABLE_DUAL_LINK    			0
#define DL_PXL_RAT_DET      			0   /* DVI DUAL Link detect by pixel rate */
#define FieldInvertCheck 				1
#define ENABLE_VC_8_5          			1  //130910 nick add for FB mode setting
#define ENABLE_AUTO_CLOLR_WITHOUT_INPUT 1 //20160331 YANPING

#define Show_BackLightTimeValue              1


#define	UseI2cByTableFunc				0


#define Init_HDCPKey    	           			0

/***************************************************************************************/
//1 DDC/CIπ¶ƒ‹
#define JRY_Color_Tool_Functing            	1

#define  Adj_7500K_Temp  				(1&&JRY_Color_Tool_Functing)

#define JRY_FDDCCI_WriteEDID 			  (1&&JRY_Color_Tool_Functing)

#define ColorTool_Clear_Time                     1

#define User_DDCTO_FlashSave     			(JRY_FDDCCI_WriteEDID)
/***************************************************************************************/


#define  EANBLE_NEW_DCR_Functing       1



#if MainBoardType == MainBoard_JRY_L58VHN_GV3

#define INPUT_TYPE_SEL              			(INPUT_0A|INPUT_1C)
#define DVI_PORT_PRIORITY       			1 //
#define HDMI_A_PORT_PRIORITY      		2 //
#define HDMI_B_PORT_PRIORITY   			2 //
#define HDMI_C_PORT_PRIORITY   			2 //
#define DP_PORT_PRIORITY        			2 //


#define INPUT_TYPE                  		INPUT_1A1D
#define ENABLE_VGA                     		1
#define ENABLE_DVI                     		1
#define ENABLE_HDMI                   		0
#define ENABLE_HDMI2                    	0
#define ENABLE_HDMI_1_4              	0
#define ENABLE_MHL_C1                   	0
#define ENABLE_MHL_C2                   	0
#define ENABLE_MHL_C3                   	0
#define ENABLE_MHL                      	(ENABLE_MHL_C1|ENABLE_MHL_C2|ENABLE_MHL_C3)

#define ENABLE_DP_INPUT              				0//((Input_Displayport_C2 != Input_Nothing)||(Input_Displayport_C3 != Input_Nothing))
#define ENABLE_DP_EDID_IN_FLASH					0	//121115 Modify
#define ENABLE_DP_HDCP_IN_FLASH					0	//121115 Modify
#define ENABLE_DP_AUDIO   							1
#define ENABLE_MHL_EDID_IN_FLASH					0	//enable mhl edid

#define VGA_Write_EEPROM      		0
#define DVI_Write_EEPROM      		1// 1
#define HDMI_Write_EEPROM      		0
#define HDMI2_Write_EEPROM          	0
#else
#message "please define Russel new board type for Port_Func_Enable"
#endif
/*********************************/
#if(INPUT_TYPE != INPUT_1H)&&(INPUT_TYPE != INPUT_1A)
#define Dual	    				1
#else
#define Dual	    				0
#endif
/******************************/
#define ENABLE_MENULOAD             			0
#define ML_USE_INT           					0 // 1

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// BRIGHTNESS CONTROL
////////////////////////////////////////////////////////////
#define BrightFreqByVfreq        				1 // set brightness freq. by input Vfreq.
#define BRIGHTNESS_INVERSE  				1
#define BRIGHTNESS_FREQ              			240 // unit: Hz	//130715	xiandi
#define BRIGHTNESS_VSYNC_ALIGN       		0
#define ENABLE_BRIGHTNESS_FREQ_20KHZ		0
#define AdjustVolume_UseTable				0

////////////////////////////////////////////////////////////

// AUDIO
////////////////////////////////////////////////////////////


#define InverseVolume      				0
#define VOLUME_FREQ      			  	0//240
#define VOLUME_VSYNC_ALIGN            		0
// SYSTEM
////////////////////////////////////////////////////////////
#define AUTO_DATA_PATH               		0
#define ENABLE_BREAKREMINDER	        	1
#define EXT_TIMER0_1S      	        		1    //if ENABLE_BREAKREMINDER need turn on this define for correct timer

//PANEL CHECK 60HZ MAX VOTAL
////////////////////////////////////////////////////////////

// POWERMANAGEMENT
////////////////////////////////////////////////////////////
#define MS_PM                        	1
#define PM_MCUSLEEP                 	0
#define LED_PWM                        	0
#define DCRClearBacklight             // when drc is on in black pattern clear the backlight
#define BURST_MODE              		1

#define DISABLE_AUTO_SWITCH             0 // for MHL test


//=============================================================

#define	SpeakerDet_Enable		 0
#define 	EarphoneDet_Enable         0
#define 	AudioFunc                 	(SpeakerDet_Enable|| EarphoneDet_Enable)

#define USE_DAC_CODE				1
#define Def_DACGain					0x50
//////////////////////////INFORMATION////////////////////////////////
//#define	Brand					    "ChongHong"
#define   Model 					    "T24"

#define ShowModelName 				_L,_5,_8,_C,_D,_T,_9
#define ChipName                			"TSUMU58VHN"//20140926 Gino
#define FWVersion					"001"
#define F_FWVersion             			_0,_0,_1
#define Version						1
#define ChangeDate					"20190801"//"""20190605"//""

/********************************************************************************************/
//1 Project …Ë÷√

#define	HH_PivotKey_Enable						0

#define 	Hot_Corss_FY_ColorSelect				0
#define   Hotkey_ECO_Enable						1
#define 	AdjustLanguageFunction            			1

#define LowBlueLightType					LowBlueLight_Misc_Group


#define ENABLE_FPS_RTS                  	0


#define		PropFontNewData		1
#define 		TimingInfoYpos			14
#define 		EN_HotInputSelect_ShowCenter		1

/////////////////////////brightness///////////////////////////////////
#define BRI_PRO_MIN_VALUE			0x09
#define BRI_PRO_DEF_VALUE			0x4A
#define BRI_PRO_MAX_VALUE			0x65
////////////////////////color temp/////////////////////////////////
#define DEF_Cool_Red			106
#define DEF_Cool_Green			114
#define DEF_Cool_Blue			129

#define DEF_Normall_Red			120
#define DEF_Normall_Green		123
#define DEF_Normall_Blue			129

#define DEF_Warml_Red			128
#define DEF_Warml_Green			128
#define DEF_Warml_Blue			128
///////////////////////volume/////////////////////////////
#define DefVolume				50
#define Pro_MinVol   				0x10
#define Pro_MidVol   				0xDB
#define Pro_MaxVol				0xF0

#define Pro_MinVol_P   			0x040
#define Pro_MidVol_P   			0x10F
#define Pro_MaxVol_P				0x23F
///////////////////////////////////////////////////////////////

#define ADCKEY_A0_VALUE     0x00
#define ADCKEY_A1_VALUE     0x47//0x68
#define ADCKEY_A2_VALUE     0xA0

#define ADCKEY_B0_VALUE     0x00
#define ADCKEY_B1_VALUE     0x47//0x68
#define ADCKEY_B2_VALUE     0xFF


#define ADCKEY_A0       KEY_EXIT
#define ADCKEY_A1       KEY_PLUS
#define ADCKEY_A2       KEY_NOTHING

#define ADCKEY_B0       KEY_MINUS
#define ADCKEY_B1       KEY_MENU
#define ADCKEY_B2       KEY_NOTHING
///////////////////////////////////////////////////////////////
#endif

