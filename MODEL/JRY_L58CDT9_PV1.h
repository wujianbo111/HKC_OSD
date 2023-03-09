#ifndef TSUMXXC_DEMO_H
#define TSUMXXC_DEMO_H
////////////////////////////////////////////////////////////
// BOARD SELECTION
////////////////////////////////////////////////////////////
#define CHIP_ID                			CHIP_TSUMC
#define MainBoardType    			MainBoard_JRY_L58CDT9_PV1//MainBoard_JRY_W58CDT9_GV3//MainBoard_JRY_W58CDT9_GV3//MainBoard_L38CDMT9_GV1//MainBoard_P38CDMT9_C10////MainBoard_8643_M0B // MainBoard_6178_M0A // MainBoard_TSUMP387MT9_1 // ////, , , , 


//#define EEPROM_TYPE       EEPROM_24C16
////////////////////////////////////////////////////////////
// Model Type
////////////////////////////////////////////////////////////
#define MF100_215W           0  //  TF 样机
#define MS601_195W           0
#define MS601_215W		   0
#define MS601_238W		   1
#define MS601_27W		   0
/////////////////////////////////////////

#if MF100_215W

#define PanelType 				PanelM215HAN01//PanelM215HTN01_V1//PanelM215HTN01_V1//PanelM195RTN01_V00H//
#define DisplayLogo				Element//Element//NoBrand//AOCLOGO//
#define ENABLE_RTE               		0
#define OD_MODE                   		OD_MODE_333 // 1218 coding test
#define AudioFunc                 		0
#define DefLanguage     			LANG_English
#elif MS601_195W
#define PanelType 				PanelM195RTN01_V00H//PanelM215HTN01_V1//PanelM215HTN01_V1//PanelM195RTN01_V00H//
#define DisplayLogo				NoBrand//Element//NoBrand//AOCLOGO//
#define ENABLE_RTE               		0
#define OD_MODE                   		OD_MODE_333 // 1218 coding test
#define AudioFunc                 		1
#define DefLanguage     			LANG_English
#elif MS601_215W
#define PanelType 				PanelM215HTN01_V1//PanelM215HTN01_V1//PanelM215HTN01_V1//PanelM195RTN01_V00H//
#define DisplayLogo				HUNTKEYLOGO//Element//NoBrand//AOCLOGO//
#define ENABLE_RTE               		0
#define OD_MODE                   		OD_MODE_333 // 1218 coding test
#define AudioFunc                 		1
#define DefLanguage     			LANG_English
#define LanguageEnable_France	1
#elif MS601_238W
#define PanelType 				PanelM238HV_V00000A//PanelM215HTN01_V1//PanelM215HTN01_V1//PanelM195RTN01_V00H//
#define DisplayLogo				HUNTKEYLOGO//HUNTKEYLOGO//Element//NoBrand//AOCLOGO//
#define ENABLE_RTE               		0
#define OD_MODE                   		OD_MODE_333 // 1218 coding test
#define AudioFunc                 		1
#define DefLanguage     			LANG_English
#elif MS601_27W
#define PanelType 				PanelM270HTN02_V1//PanelM215HTN01_V1//PanelM215HTN01_V1//PanelM195RTN01_V00H//
#define DisplayLogo				NoBrand//Element//NoBrand//AOCLOGO//
#define ENABLE_RTE               		0
#define OD_MODE                   		OD_MODE_333 // 1218 coding test
#define AudioFunc                 		1
#define DefLanguage     			LANG_English
#else
#define PanelType 				PanelM215HAN01//PanelM215HTN01_V1//PanelM215HTN01_V1//PanelM195RTN01_V00H//
#define DisplayLogo				NoBrand//Element//NoBrand//AOCLOGO//
#define ENABLE_RTE               		0
#define OD_MODE                   		OD_MODE_333 // 1218 coding test
#define AudioFunc                 		1
#define DefLanguage     			LANG_English
#endif

#define ENABLE_OVER_SCAN          		0 // 121101 coding addition
#define DVI_PN_SWAP              		0
#define DVI_RB_SWAP 			 	0
#define HDMI_PN_SWAP            		0
#define ENABLE_AUTOEQ           		0
#define ZhongXin_Request			0// 1  //LED Siled  老化和待机状态下橙灯闪烁
#define ENABLE_SUPERRESOLUTION     	0
#define DDCCI_ENABLE				1
#define Enable_Expansion		  		1
#define Dual	    						1
#define WidePanel					1
#define ENABLE_HDCP	 				1
#define HDCPKEY_IN_Flash			1
#define HDCPKEY_IN_7F000			0
//#define OffPower
#define Panel_Inv            				1 // ownbrand use 1
#define LANGUAGE_TYPE				All14Language_AddJap//ASIA//EUROPE//All13Language//All14Language_AddJap
#define Enable_Cache		   			1
#define Enable_OsdEngine1      		0// 1: two OSD engine,; 0: one osd engine

//#define PowerKeyDeBounce
#define PowerKeyDeBounceCount     	30




#define Enable_Gamma					0
#define GAMMA_BYPASS    				0

#define FRAME_BFF_SEL       			FRAME_BFFLESS// 130625 william
#define ENABLE_DUAL_LINK    			0
#define DL_PXL_RAT_DET      			0   /* DVI DUAL Link detect by pixel rate */
#define FieldInvertCheck 				1
#define ENABLE_VC_8_5          			1  //130910 nick add for FB mode setting
#define ENABLE_AUTO_CLOLR_WITHOUT_INPUT 1 //20160331 YANPING

#define Show_BackLightTimeValue              1

#define ColorTool_Clear_Time                     1


#define User_DDCTO_FlashSave              1

#define VGA_Write_EEPROM      		 1
#define DVI_Write_EEPROM      		 0
#define HDMI_Write_EEPROM      		 1
#define HDMI2_Write_EEPROM         	 0


#define JRY_Color_Tool_Functing            1

#define  Adj_7500K_Temp  			  (0&&JRY_Color_Tool_Functing)

#define JRY_FDDCCI_WriteEDID 		  (1&&JRY_Color_Tool_Functing)


#define EarphoneDet_Enable          	   0


#define  EANBLE_NEW_DCR_Functing        1

#define Enable_CheckVcc5V                      0  //PC 99 功能

#define EANBLE_MUTE_ON_OFF                 0

#define UseVGACableReadWriteAllPortsEDID


#if MainBoardType == MainBoard_JRY_L58CDT9_PV1 //MainBoard_6178_M0A
#define INPUT_TYPE                  		INPUT_1A1H
#define ENABLE_VGA                     		1
#define ENABLE_DVI                     	 	0
#define ENABLE_HDMI                   		1//((Input_HDMI_C1 != Input_Nothing)||(Input_HDMI_C2 != Input_Nothing)||(Input_HDMI_C3 != Input_Nothing))
#define ENABLE_HDMI2                    	0
#define ENABLE_HDMI_1_4              	0
#define ENABLE_MHL_C1                   	0
#define ENABLE_MHL_C2                   	0
#define ENABLE_MHL_C3                   	0
#define ENABLE_MHL                      	(ENABLE_MHL_C1|ENABLE_MHL_C2|ENABLE_MHL_C3)

#define ENABLE_DP_INPUT              					0//((Input_Displayport_C2 != Input_Nothing)||(Input_Displayport_C3 != Input_Nothing))
#define ENABLE_DP_EDID_IN_FLASH					0	//121115 Modify
#define ENABLE_DP_HDCP_IN_FLASH					0	//121115 Modify
#define ENABLE_DP_AUDIO   							0
#define ENABLE_MHL_EDID_IN_FLASH					0	//enable mhl edid

#else
#message "please define Russel new board type for Port_Func_Enable"
#endif
#define ENABLE_MENULOAD             	0
#define ML_USE_INT           			0 // 1

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// BRIGHTNESS CONTROL
////////////////////////////////////////////////////////////
#define BrightFreqByVfreq        				0   // set brightness freq. by input Vfreq.
#define BRIGHTNESS_INVERSE  				1
#define BRIGHTNESS_FREQ              			240 // unit: Hz	//130715	xiandi
#define BRIGHTNESS_VSYNC_ALIGN       		0
#define ENABLE_BRIGHTNESS_FREQ_20KHZ		0
#define AdjustVolume_UseTable				0

////////////////////////////////////////////////////////////

// AUDIO
////////////////////////////////////////////////////////////
#define InverseVolume      			0
#define VOLUME_FREQ      			  	0//240
#define VOLUME_VSYNC_ALIGN              0
// SYSTEM
////////////////////////////////////////////////////////////
#define AUTO_DATA_PATH               	0
#define ENABLE_BREAKREMINDER	       1
#define EXT_TIMER0_1S      	        	1    //if ENABLE_BREAKREMINDER need turn on this define for correct timer

//PANEL CHECK 60HZ MAX VOTAL
////////////////////////////////////////////////////////////

// POWERMANAGEMENT
////////////////////////////////////////////////////////////
#define MS_PM                        	1
#define PM_MCUSLEEP                 	0
#define LED_PWM                        	0
#define DCRClearBacklight             // when drc is on in black pattern clear the backlight
#define BURST_MODE              		1
// INFORMATION
#if  MS601_195W
#define Model 					"M2072WH"
#elif MS601_215W
#define Model 					"M2072WH"
#elif MS601_238W
#define Model 					"M2072WH"
#elif MS601_27W
#define Model 					"M2072WH"
#endif
#define ShowModelName 				_L,_5,_8,_C,_D,_T,_,9
#define ChipName                			"TSUMU58CDT9"//20140926 Gino
#define FWVersion					"001"
#define F_FWVersion             			_0,_0,_1
#define Version						1
#define ChangeDate					"20171110"
#define DISABLE_AUTO_SWITCH             0 // for MHL test

#endif

