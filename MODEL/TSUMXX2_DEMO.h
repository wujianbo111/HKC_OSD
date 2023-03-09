#ifndef TSUMXXU_DEMO_H
#define TSUMXXU_DEMO_H
////////////////////////////////////////////////////////////
// BOARD SELECTION
////////////////////////////////////////////////////////////
//#define TSUMXXNX
#define CHIP_ID     CHIP_TSUM2
#define MainBoardType  MainBoard_MST144A_A02A  //MainBoard_AOC_TSUM2 // 

////////////////////////////////////////////////////////////
// INPUT_TYPE SELECTION
#define ENABLE_RTE                 	0
#define PanelType 				PanelM236H3LA3 //PanelBM230WF3_SJC2 //PanelM236H3LA3
////////////////////////////////////////////////////////////
#define DisplayLogo				AOCLOGO
#define DDCCI_ENABLE			1
#define Enable_Expansion		1
#define Dual	    			1
#define WidePanel				1
#define ENABLE_HDCP	 			1
#define HDCPKEY_IN_Flash		1
#define OffPower
#define Panel_Inv            	1 // ownbrand use 1
#define LANGUAGE_TYPE			All14Language_AddJap//ASIA//EUROPE//All13Language//All14Language_AddJap
#define INPUT_TYPE      				INPUT_1A2H
#define DVI_RB_SWAP 				0
#define DVI_PN_SWAP					0
#define Enable_Cache		   		1

#define Enable_OsdEngine1      		0// 1: two OSD engine,; 0: one osd engine

#define PowerKeyDeBounce
#define PowerKeyDeBounceCount     	30


#if INPUT_TYPE == INPUT_1A1H || INPUT_TYPE == INPUT_1A1D1H || INPUT_TYPE == INPUT_1A2H||INPUT_TYPE == INPUT_1A1H1DP
#define ENABLE_HDMI     				 1
#else
#define ENABLE_HDMI     				0
#endif
#define ML_USE_INT           		        0 // 1

#define ENABLE_MHL                         1

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// BRIGHTNESS CONTROL
////////////////////////////////////////////////////////////
#define BrightFreqByVfreq        		1 // set brightness freq. by input Vfreq.
#define BRIGHTNESS_INVERSE  		0
#define BRIGHTNESS_FREQ                     240 // unit: Hz
#define BRIGHTNESS_VSYNC_ALIGN       1
////////////////////////////////////////////////////////////

// AUDIO
////////////////////////////////////////////////////////////
#define AudioFunc                 			1
#define InverseVolume      			0
#define VOLUME_FREQ      			       0 // unit: Hz
#define VOLUME_VSYNC_ALIGN              0
// SYSTEM
////////////////////////////////////////////////////////////

#define AdjustVolume_UseTable          0

//#define ENABLE_HK_DATA_ON_DRAM    1
////////////////////////////////////////////////////////////
// POWERMANAGEMENT
////////////////////////////////////////////////////////////
#define MS_PM                         			0
#define PM_MCUSLEEP          			0
#define LED_PWM                 			0

#define DCRClearBacklight             // when drc is on in black pattern clear the backlight
#define BURST_MODE              		1

#define Model 					"E2460SWG"
#define ShowModelName 			_E,_2,_4,_6,_0,_S,_W,_G
#define FWVersion				"003"
#define F_FWVersion             _0,_0,_3
#define Version					003
#define ChangeDate				"20120206"




#endif

