#ifndef TSUMXXF_DEMO_H
#define TSUMXXF_DEMO_H
////////////////////////////////////////////////////////////
// BOARD SELECTION
////////////////////////////////////////////////////////////
#define CHIP_ID                CHIP_TSUMF//CHIP_TSUMD
#define MainBoardType    	 MainBoard_8806_M0A//MainBoard_6148_M0A //MainBoard_6038_M0A // MainBoard_TSUMP387MT9_1 // ////, , , , 
#define ENABLE_XTAL_LESS               1
#define ENABLE_XTAL_LESS_FPLL         	(0 && ENABLE_XTAL_LESS)		// Note: FPLL will stay disabled when the input is DP
#define ENABLE_XTAL_LESS_SW_SLT         (0 && ENABLE_XTAL_LESS)
#define ENABLE_RESET_PIN                0
#define ENABLE_CABLE_5V_EDID            1
//#define EEPROM_TYPE       EEPROM_24C32
////////////////////////////////////////////////////////////
// INPUT_TYPE SELECTION
////////////////////////////////////////////////////////////
#define ENABLE_RTE                       1
//#define OD_MODE                            OD_MODE_333//20130522 OD_MODE_333 // 1218 coding test
#define DVI_PN_SWAP             	 0
#define DVI_RB_SWAP 			 0

#define HDMI_PN_SWAP                    0// 1
#define ENABLE_AUTOEQ                   0

#define PanelType 						PanelLM238WF2_S1N1

#define DisplayLogo				AOCLOGO
#define DDCCI_ENABLE			1
#define Enable_Expansion		       1
#define Dual	    			              1
#define WidePanel				1
#define ENABLE_HDCP	 			1
#define HDCPKEY_IN_Flash		1
#define HDCPKEY_IN_7F000		1
#define HPD_INVERSE            0

#define OffPower
#define Panel_Inv            	1 // ownbrand use 1
#define LANGUAGE_TYPE			All14Language_AddJap//ASIA//EUROPE//All13Language//All14Language_AddJap
#define Enable_Cache		   		1
#define Enable_OsdEngine1      		0// 1: two OSD engine,; 0: one osd engine


#define GAMMA_BYPASS                  0

#define FRAME_BFF_SEL       FRAME_BFFLESS
#define ENABLE_DUAL_LINK           	0
#define DL_PXL_RAT_DET         0   /* DVI DUAL Link detect by pixel rate */
#define FieldInvertCheck          1

#if MainBoardType == MainBoard_8806_M0A
#define INPUT_TYPE                  INPUT_1A1H//INPUT_1A1D1H1DP
#define ENABLE_HDMI                   1// 1//((Input_HDMI_C1 != Input_Nothing)||(Input_HDMI_C2 != Input_Nothing)||(Input_HDMI_C3 != Input_Nothing))
#define ENABLE_DVI                    0
#define ENABLE_HDMI_1_4               0
#define ENABLE_MHL_C1                   0
#define ENABLE_MHL_C2                   0
#define ENABLE_MHL_C3                   0
#define ENABLE_MHL                      (ENABLE_MHL_C1|ENABLE_MHL_C2|ENABLE_MHL_C3)

#define ENABLE_DP_INPUT                    0// 1//((Input_Displayport_C2 != Input_Nothing)||(Input_Displayport_C3 != Input_Nothing))
#define ENABLE_DP_EDID_IN_FLASH	         0// 1	//121115 Modify
#define ENABLE_DP_HDCP_IN_FLASH	          0// 1	//121115 Modify
#define ENABLE_DP_AUDIO                    0
#define ENABLE_MHL_EDID_IN_FLASH			0	//enable mhl edid

#else
#message "please define Russel new board type for Port_Func_Enable"
#endif
#define ML_USE_INT           			0 // 1

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// BRIGHTNESS CONTROL
////////////////////////////////////////////////////////////
#define BrightFreqByVfreq        		        1 // set brightness freq. by input Vfreq.
#define BRIGHTNESS_INVERSE  			 0
#define BRIGHTNESS_FREQ              	        20000 // unit: Hz	//130719 petit
#define BRIGHTNESS_VSYNC_ALIGN       	    1						//130719 petit
#define ENABLE_BRIGHTNESS_FREQ_20KHZ   	1
////////////////////////////////////////////////////////////

// AUDIO
////////////////////////////////////////////////////////////
#define AudioFunc                 		              1	//130710 petit
#define InverseVolume      				1//0
#define VOLUME_FREQ      			  	       0//240 // unit: Hz
#define VOLUME_VSYNC_ALIGN                     0
#define AdjustVolume_UseTable                 0
// SYSTEM
////////////////////////////////////////////////////////////
#define AUTO_DATA_PATH               	0

// POWERMANAGEMENT
////////////////////////////////////////////////////////////
#define MS_PM                         	1
#define PM_MCUSLEEP          			0
#define LED_PWM                 		0

#define DCRClearBacklight             // when drc is on in black pattern clear the backlight
#define BURST_MODE              		1
// INFORMATION
#define Model 					"TSUMXXF"//"M2870V"//20130427
#define ShowModelName 			_T,_S,_U,_M,_X,_X,_F
#define ChipName                "TSUMO58FDT9-8"
#define FWVersion				"001"
#define F_FWVersion             _0,_0,_1
#define Version					001
#define ChangeDate				"20160414"


#endif

