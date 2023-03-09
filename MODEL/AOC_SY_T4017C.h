#ifndef TSUMXXU_DEMO_H
#define TSUMXXU_DEMO_H
////////////////////////////////////////////////////////////
// BOARD SELECTION
////////////////////////////////////////////////////////////
#define CHIP_ID              		CHIP_TSUMC
#define MainBoardType  		MainBoard_W38CDMT9_DV2 // MainBoard_TSUML88CMC2//MainBoard_TSUML887DC4_1//MainBoard_TSUML88CMC2, MainBoard_TSUML887DC4_1, MainBoard_TSUMP387MT9_1, MainBoard_TSUMP387MT9_1_DP, MainBoard_tsuml88bdc2_1
//#define EEPROM_TYPE         	EEPROM_24C32
////////////////////////////////////////////////////////////
// INPUT_TYPE SELECTION
////////////////////////////////////////////////////////////
#define ENABLE_RTE                   		0
//#define OD_MODE     OD_MODE_333 // 1218 coding test
#define ENABLE_OVER_SCAN    		0 // 121101 coding addition
#define DVI_PN_SWAP                     	0
#define DVI_RB_SWAP 				0

#define HDMI_PN_SWAP                    	0
#define ENABLE_AUTOEQ                   	0

#define PanelType 					PanelM236HJJSUFFIX_L31//PanelLM230WF5_T2F2
#define ENABLE_SUPERRESOLUTION     	0


#define DisplayLogo					SANXINGLOGO
#define DDCCI_ENABLE				1
#define Enable_Expansion		       	1
#define Dual	    			              	1
#define WidePanel					1
#define ENABLE_HDCP	 			1
#define HDCPKEY_IN_Flash			1
#define HDCPKEY_IN_7F000			0	//120420 Modify
#define OffPower
#define ENABLE_OSD_HotKeyVolume	0
#define Panel_Inv            				1 // ownbrand use 1
#define LANGUAGE_TYPE				All14Language_AddJap//ASIA//EUROPE//All13Language//All14Language_AddJap
#define Enable_Cache		   			1
#define Enable_OsdEngine1      		0// 1: two OSD engine,; 0: one osd engine


//#define PowerKeyDeBounce
#define PowerKeyDeBounceCount     	30


#define Enable_Gamma				0	//111223 Modify
#define GAMMA_BYPASS    			0

#define FRAME_BFF_SEL       			FRAME_BFFLESS
#define ENABLE_DUAL_LINK    			0
#define DL_PXL_RAT_DET      			0   /* DVI DUAL Link detect by pixel rate */
#define FieldInvertCheck 				1

#define Show_BackLightTimeValue              1

#define ColorTool_Clear_Time                     1


#define  EANBLE_NEW_DCR_Functing       1

#define DefLanguage     			LANG_English

#define ENABLE_VGA         		1// 1
#define User_DDCTO_FlashSave     0
#define VGA_Write_EEPROM      	0
#define DVI_Write_EEPROM      	0// 1
#define HDMI_Write_EEPROM      	1

#if MainBoardType == MainBoard_W38CDMT9_DV2
#define INPUT_TYPE                  	INPUT_1A1D1H//INPUT_1A1D1H1DP
#define ENABLE_DVI                      	1
#define ENABLE_HDMI                   		1// 1//((Input_HDMI_C1 != Input_Nothing)||(Input_HDMI_C2 != Input_Nothing)||(Input_HDMI_C3 != Input_Nothing))
#define ENABLE_HDMI_1_4               	0

#define ENABLE_DP_INPUT               			0// 1//((Input_Displayport_C2 != Input_Nothing)||(Input_Displayport_C3 != Input_Nothing))
#define ENABLE_DP_EDID_IN_FLASH			0// 1	//121115 Modify
#define ENABLE_DP_HDCP_IN_FLASH			0// 1	//121115 Modify
#define ENABLE_DP_AUDIO   					0
#define ENABLE_MHL_EDID_IN_FLASH			0	//enable mhl edid

#define ENABLE_VGA            1


#define ENABLE_MHL_C1                  	0
#define ENABLE_MHL_C2                   	0
#define ENABLE_MHL_C3                   	0
#define ENABLE_MHL                      	(ENABLE_MHL_C1|ENABLE_MHL_C2|ENABLE_MHL_C3)

#else
#message "please define Russel new board type for Port_Func_Enable"
#endif

#define ENABLE_MENULOAD             	0
#define ML_USE_INT           			0 // 1

//#define ENABLE_MHL                   	0
//#define ENABLE_DISPLAY_UNDERSCAN    0 // MHL timing Vfreq under 48Hz should get into frame buffer

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// BRIGHTNESS CONTROL
////////////////////////////////////////////////////////////
#define BrightFreqByVfreq        			1 // set brightness freq. by input Vfreq.
#define BRIGHTNESS_INVERSE  			1
#define BRIGHTNESS_FREQ              		240 // unit: Hz
#define BRIGHTNESS_VSYNC_ALIGN       	1
////////////////////////////////////////////////////////////

// AUDIO
////////////////////////////////////////////////////////////
#define AudioFunc                 				1
#define InverseVolume      				0
#define VOLUME_FREQ      			  	0 // unit: Hz
#define VOLUME_VSYNC_ALIGN              	0
// SYSTEM
////////////////////////////////////////////////////////////
#define AUTO_DATA_PATH               		0
#define AdjustVolume_UseTable          		0

#define ENABLE_DSC                  			0

// POWERMANAGEMENT
////////////////////////////////////////////////////////////
#define MS_PM                   				1
#define PM_MCUSLEEP             			0
#define LED_PWM                 				0
#define ENABLE_POWER_BOARD_CONTROL   0 // control power board enter to saving mode
#define DCRClearBacklight             // when drc is on in black pattern clear the backlight
#define BURST_MODE              				1
#define POWER_CONTROL_TEST  			0
// INFORMATION
#define Model 					"T4017C"
#define ShowModelName 			_T,_4,_0,_1,_7,_C
#define FWVersion				"001"
#define F_FWVersion             		_0,_0,_1
#define Version					001
#define ChangeDate				"20170309"


#define DISABLE_AUTO_SWITCH     0 // for MHL test

#endif

