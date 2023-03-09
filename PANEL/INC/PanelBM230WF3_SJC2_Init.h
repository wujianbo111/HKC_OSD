#ifndef _PanelBM230WF3_
#define _PanelBM230WF3_
#define PanelName               "PanelBM230WF3"

#define _PanelColorDepth                1//0->6bit+FRC                      bPanelColorDepth->8Bit
#define PanelTTL                        0
#define PanelTCON                   0
#define PanelLVDS                   0xff
#define PanelRSDS                   0
#define PanelminiLVDS      			0
#define NormalWhite    				0      // for normal Black panel
#define PANEL_VCOM_ADJUST        	0xFF		//120322 Modify
#define MINILVDSTCON_DEVICE     	0x50
#define MAX_VCOM_VALUE          	0x7F
#define DEF_VCOM_VALUE          	0x4F
#define MIN_VCOM_VALUE          	0x00

#define _ChangeModePanelVddOff      bChangeModePanelVddOff//0->Change Mode Panel Vdd On     bChangeModePanelVddOff->Change Mode Panel Vdd Off

#define LVDS_TIMode               0xff
#define PANEL_SWAP_PN           0xff
#define PanelDualPort               0xff
#define PanelSwapPort               0xff
#define PanelSwapOddML         0
#define PanelSwapEvenML        0
#define PanelSwapOddRB         0
#define PanelSwapEvenRB        0
#define PanelSwapMLSB           0

#define _PanelOutputControl1            0x10//Scaler Bank 0x42 Setting
#define _PanelOutputControl2			( (PanelDualPort &BIT0) | (PanelSwapPort &BIT1))//Scaler Bank 0x43 Setting // Rosen 3043h Setting 2011.9.16 cc add
#define _PanelOSContol              0x80//Scaler Bank 0xF2 Setting
#define _PanelODRriving             0x55//Scaler Bank 0xF5 Setting

#define _PanelOnTiming1          40//60//20 // time between panel & data while turn on power
#define _PanelOnTiming2          550//550//350//220 // time between data & back light while turn on power
#define _PanelOffTiming1         250//350//220 // 2005/5/3// time between back light & data while turn off power 
#define _PanelOffTiming2         20//20//25 // 2005/5/3//10 // time between data & panel while turn off power 

#define _PanelHSyncWidth         32//20//48
#define _PanelHSyncBackPorch     48//28//78
#define _PanelVSyncWidth         2// 3
#define _PanelVSyncBackPorch     14//12
#define _PanelHStart                    (_PanelHSyncWidth+_PanelHSyncBackPorch)
#define _PanelVStart                    (_PanelVSyncWidth+_PanelVSyncBackPorch)

#define PanelDClkDelay             0
#define PanelInvDE                  0
#define PanelInvDClk                0
#define PanelInvHSync            0
#define PanelInvVSync             0

#define _PanelWidth      1920
#define _PanelHeight     1080
#define _PanelHTotal     2176
#define _PanelVTotal     1100
#define _PanelMaxHTotal      2240
#define _PanelMinHTotal      2048
#define _PanelMaxVTotal      1160
#define _PanelMinVTotal      1090
#define _PanelDCLK           144
#define _PanelMaxDCLK        190//175
#define _PanelMinDCLK            120//113

#define _DefBurstModeFreq           250//Hz
#define _DefMinDutyValue                0x01
#define _DefMaxDutyValue            0xFF


#define _STEPL                      0x44
#define _STEPH                      0x00
#define _SPANL                      0xCC
#define _SPANH                      0x01

//=======================================================================
#define PanelDither                 8

#define _PanelLVDSSwing2			1// 0:242.37mV    1:339.33mV    2:387mV    3:169.67mV    //For TSUMXXNXX&TSUMXXQXX type ic auto tune target voltage
#define _PanelLVDSSwing1			0x15// 283mV //For old chip
#define _PanelLVDSSwing				(_PanelLVDSSwing1|_PanelLVDSSwing2<<6)

// 111003 Rick add
#define PanelVfreq          (600)
#define PanelMaxVfreq   (750+20) // 75Hz
#define PanelMinVfreq   (500-20) // 50Hz

//=================================================================
//==================================================================
//LED Backlight Control
#define LED_STRING_NUM                  4


#define LED_CH_0    1
#define LED_CH_1    1
#define LED_CH_2    1
#define LED_CH_3    1
#define LED_CH_4    0
#define LED_CH_5    0
#define LED_CH_6    0
#define LED_CH_7    0

#define LED_SERIES                      (LED_CH_0+LED_CH_1+LED_CH_2+LED_CH_3+LED_CH_4+LED_CH_5+LED_CH_6+LED_CH_7)

#if (LED_SERIES == 4) || (LED_SERIES == 3)
#define MAX_CURRENT_RATE        110//50
#elif (LED_SERIES == 6)
#define MAX_CURRENT_RATE        30
#elif (LED_SERIES == 8)
#define MAX_CURRENT_RATE        14 //10
#endif

#define BOOST_CURRENT_LIMIT_LEVEL    BIT5//BIT4


#define ENABLE_VCOM_ADJUST              1
#define VCOM_TYPE                   VCOM_RICHTEK

#define PANEL_F_MODULATION    40 // 30~40KHz
#define PANEL_PERCENTAGE      2.8  // 0.5~3%

//==================================================================
//OVP
#define LED_OVP_TUNING_ENABLE       		0//1

#define PanelLightBarDefaultVoltage    		44
#define PanelLightBarMaximumVoltage    	48
#define OVP1_Ratio						110    // 1.1 
#define OVP1_ProtVoltage					OVP1_Ratio*PanelLightBarMaximumVoltage/100  // 1.1*45=	49.5V
#define OVP2_Ratio						125    // 1.25
#define OVP2_ProtVoltage					OVP2_Ratio*PanelLightBarDefaultVoltage/100  // 1.1*42=	52.5V
#define ResistorRatio						43//(R2+R1)/R1

//==================================================================
//LED Protect
#if 1 //20120419 Rick add
#define SAR_V_10p00             0xB8    //X=10/5.5*100=182=0xB6
#define SAR_V_8p00              0xC5//20130509 from MST hunyi.cai//6.7/3.3/11*1023=189
#define SAR_V_5p00              0x5D       // U01  0x22E
#define SAR_V_4p50              0x53       // U01  0x1D1
#define SAR_V_1p55              0x30       //=> 2.5V   Skew Low Bond
#define SAR_V_0p55              0xA
#define SAR_V_0p54              0xA
#define SAR_V_0p10              0x5
#endif

#endif
