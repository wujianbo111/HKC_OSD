#define PanelName				"TPM215HW01"//20130326

#define PanelTTL    			0
#define PanelTCON   			0
#define PanelLVDS				0xff
#define PanelRSDS				0
#define PanelminiLVDS      		0 
#define PANEL_VCOM_ADJUST     	0x00


#define _PanelColorDepth		bPanelColorDepth
#define _ChangeModePanelVddOff	bChangeModePanelVddOff


#define PanelDualPort   		0xff
#define PanelSwapPort   		0x00
#if MainBoardType==MainBoard_5276_M0A//petit 20130326
#define _PanelOutputControl1	0x90
#else
#define _PanelOutputControl1	0x10
#endif
#define _PanelOutputControl2	((PanelDualPort &BIT0) | (PanelSwapPort &BIT1))//Scaler Bank 0x43 Setting
//#define _PanelOSContol			0x80
//#define _PanelODRriving			0x55

#if MainBoardType ==MainBoard_6474_M0A
#define PanelDither		6
#else
#define PanelDither		8
#endif


#define PanelDClkDelay			8
#define PanelInvDClk			0
#define PanelInvDE				0
#define PanelInvHSync			0
#define PanelInvVSync			0

#if (MainBoardType==MainBoard_7452_M0A)
#define _PanelOnTiming1		25  // 20 //090302// T2 <= 50ms // time between panel & data while turn on power
#define _PanelOnTiming2		1100// T5 >= 450ms // time between data & back light while turn on power
#define _PanelOffTiming1		300// t6 >= 90ms // time between back light & data while turn off power
#define _PanelOffTiming2      20 // 20// T3 <= 50ms // time between data & panel while turn off power
#else
#if (MainBoardType==MainBoard_6223_M0A)//20130522
#define _PanelOnTiming1			10  // 20 //090302// T2 <= 50ms // time between panel & data while turn on power//20130701 bian
#else
#define _PanelOnTiming1    		20
#endif
#define _PanelOnTiming2    		500
#define _PanelOffTiming1 		140
#if (MainBoardType==MainBoard_6223_M0A)//20130701 bian
#define _PanelOffTiming2		15  // 20// T3 <= 50ms // time between data & panel while turn off power 
#else
#define _PanelOffTiming2 		20
#endif
#endif
#define PanelOffOnDelay        1800 // T4 >= 500ms

#define _PanelHSyncWidth   		14
#define _PanelHSyncBackPorch 	31
#define _PanelVSyncWidth   		3
#define _PanelVSyncBackPorch 	13
#define _PanelHStart   			(_PanelHSyncWidth+_PanelHSyncBackPorch)
#define _PanelVStart   			(_PanelVSyncWidth+_PanelVSyncBackPorch)


#define _PanelWidth				1920
#define _PanelHeight			1080
#define _PanelHTotal			2160
#define _PanelVTotal			1110
#define _PanelMaxHTotal		 	2200
#define _PanelMinHTotal			2120
#define _PanelMaxVTotal			1125
#define _PanelMinVTotal			1092


#define _PanelDCLK				140//149
#define _PanelMaxDCLK			180//195
#define _PanelMinDCLK			112//118


#define _DefBurstModeFreq		250
#define _DefMinDutyValue		0x30
#define _DefMaxDutyValue		0xFF


#define _STEPL					0x69
#define _STEPH					0x00
#define _SPANL					0xF4
#define _SPANH					0x01

#define _PanelLVDSSwing1		0x15// 283mV //For old chip
#if MainBoardType==MainBoard_5276_M0A//petit 20130326
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
#define MAX_CURRENT_RATE       60
#elif (LED_SERIES == 6)
#define MAX_CURRENT_RATE        30
#elif (LED_SERIES == 8)
#define MAX_CURRENT_RATE        14 //10
#endif

#define BOOST_CURRENT_LIMIT_LEVEL    BIT5//BIT4

#define PANEL_F_MODULATION    40 // 30~40KHz
#define PANEL_PERCENTAGE      2.8  // 0.5~3%

//==================================================================
//OVP
#define LED_OVP_TUNING_ENABLE       		0

#define PanelLightBarDefaultVoltage    		44
#define PanelLightBarMaximumVoltage    	48
#define OVP1_Ratio						110    // 1.1 
#define OVP1_ProtVoltage					OVP1_Ratio*PanelLightBarMaximumVoltage/100  // 1.1*45=	49.5V
#define OVP2_Ratio						125    // 1.25
#define OVP2_ProtVoltage					OVP2_Ratio*PanelLightBarDefaultVoltage/100  // 1.1*42=	52.5V
#define ResistorRatio						43//(R2+R1)/R1

//==================================================================
//LED Protect

#define SAR_V_10p00             0xB8    //X=10/5.5*100=182=0xB6
#define SAR_V_8p00              0xC5//20130509 from MST hunyi.cai //6.7/3.3/11*1023=189
#define SAR_V_5p00              0x5D       // U01  0x22E
#define SAR_V_4p50              0x53       // U01  0x1D1
#define SAR_V_1p55              0x30       //=> 2.5V   Skew Low Bond
#define SAR_V_0p55              0xA
#define SAR_V_0p54              0xA
#define SAR_V_0p10              0x5
#endif


#define _PanelLVDSSwing2			1// 0:242.37mV    1:339.33mV    2:387mV    3:169.67mV    //For TSUMXXN&TSUMXXQ type ic auto tune target voltage
#define _PanelLVDSSwing				(_PanelLVDSSwing1|_PanelLVDSSwing2<<6)

#define PanelMaxVfreq   (750+10) // 75Hz
#define PanelMinVfreq   (500-10) // 50Hz

