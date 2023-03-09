#ifndef  _TSUMXXV_DEMO_
#define _TSUMXXV_DEMO_
#define CHIP_ID     			CHIP_TSUMV
#define MainBoardType			MainBoard_MST135B

#define ENABLE_RTE                 	0
#define PanelType 				PanelM236H3LA3
#define DisplayLogo				AOCLOGO
#define DDCCI_ENABLE			1
#define Enable_Expansion		1
#define Dual	    			1
#define WidePanel				1
#define ENABLE_HDCP	 			1
#define HDCPKEY_IN_Flash		1

//#define PanelSwapPolarity       0xFF
#define OffPower

#define Panel_Inv            	1 // ownbrand use 1
#define LANGUAGE_TYPE			All14Language_AddJap//ASIA//EUROPE//All13Language//All14Language_AddJap
#define INPUT_TYPE             	INPUT_1A1D
//
#define DVI_RB_SWAP 				0
#define DVI_PN_SWAP					0
#define Enable_Cache		   		1

#define Enable_OsdEngine1      		0// 1: two OSD engine,; 0: one osd engine


////////////////////////////////////////////////////////////
// BRIGHTNESS CONTROL
////////////////////////////////////////////////////////////
#define BrightFreqByVfreq        	1 // set brightness freq. by input Vfreq.
#define BRIGHTNESS_INVERSE  		0

#define BRIGHTNESS_FREQ          	250 // unit: Hz
#define BRIGHTNESS_VSYNC_ALIGN    	1
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////

// AUDIO
////////////////////////////////////////////////////////////
#define AudioFunc                 		 1
#define InverseVolume      			0
#define VOLUME_FREQ      				240 // unit: Hz
#define VOLUME_VSYNC_ALIGN              0
#define AdjustVolume_UseTable          1

////////////////////////////////////////////////////////////
// POWERMANAGEMENT
////////////////////////////////////////////////////////////
#define MS_PM                         	0
#define PM_MCUSLEEP          			0
#define LED_PWM                 		0


#define DCRClearBacklight         		1
#define BURST_MODE              		1


//=================================
//110623 Modify
//#define GreenLEDDutyCtrl
//#define Type_OnOff500mS          	0
//#define Type_Breathing              1
//#define PSAmberLEDFlashingType     Type_Breathing
//#if PSAmberLEDFlashingType == Type_Breathing
//    #define LED_PWM_MAX     0x80
//    #define LED_PWM_MIN     0xff
//#endif
//=================================

//#define PowerSavingAmberLEDFlash // 090701

//#define ProgramKey // scan key could program key attribute
/*******************HDMI****************/
#define ENABLE_HDMI					0

/****************************************/
#define Model 					"E2460S"
#define ShowModelName 			_P,_2,_0,_7,_1,_L
#define FWVersion				"000"
#define F_FWVersion             _0,_0,_3
#define Version					003
#define ChangeDate				"20111005"//_2,_0,_1,_1,_0,_7,_1,_8

#endif

