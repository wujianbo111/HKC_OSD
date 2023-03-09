#ifndef _PanelLM215WF3_S2A2_
#define _PanelLM215WF3_S2A2_


#define PanelName   		"PanelLM215WF3"

#define PanelDither   		8

#define PanelTTL    		0
#define PanelTCON   		0
#define PanelLVDS   		0xff
#define PanelRSDS   		0
#define PanelminiLVDS      	0
#define NormalWhite    		0      // for normal Black panel
#define PANEL_VCOM_ADJUST 		0xFF		//120322 Modify
#define MINILVDSTCON_DEVICE     0xEA
#define MAX_VCOM_VALUE          441
#define DEF_VCOM_VALUE          378
#define MIN_VCOM_VALUE          314
#define VCOM_VALUE_OFFSET       314

#define LVDS_TIMode   		0xff
#define PanelDualPort   	0xff
#define PanelSwapPort   	0xff
#define PanelSwapOddML    	0
#define PanelSwapEvenML   	0
#define PanelSwapOddRB    	0
#define PanelSwapEvenRB   	0
#define PanelSwapMLSB   	0


#define PANEL_SWAP_PN       0xFF
#define PanelDClkDelay    	0
#define PanelInvDE      	0
#define PanelInvDClk    	0
#define PanelInvHSync   	0
#define PanelInvVSync   	0
// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent  	1 // Dclk current
#define PanelDECurrent    	1 // DE signal current
#define PanelOddDataCurrent 1 // Odd data current
#define PanelEvenDataCurrent  1 // Even data current


#define PanelOnTiming1    	25  // time between panel & data while turn on power
#define PanelOnTiming2    	550 // time between data & back light while turn on power  //20050701
#define PanelOffTiming1    	250 // time between back light & data while turn off power
#define PanelOffTiming2    	25 // time between data & panel while turn off power

#define PanelHSyncWidth   	10
#define PanelHSyncBackPorch 32
#define PanelVSyncWidth    	2
#define PanelVSyncBackPorch 10 
#define PanelHStart   		(PanelHSyncWidth+PanelHSyncBackPorch)
#define PanelVStart   		(PanelVSyncWidth+PanelVSyncBackPorch)
#define PanelWidth    		1920
#define PanelHeight   		1080

#define PanelHTotal   		2176
#define PanelVTotal   		1100
#define PanelMaxHTotal     	2320
#define PanelMinHTotal     	2016
#define PanelMaxVTotal     	1160
#define PanelMinVTotal    	1090

#define PanelDCLK         	144 // 74.25
#define PanelMaxDCLK      	180 // 98
#define PanelMinDCLK       	115 // 58.54
#define HV_OUTPUT_TYPE     	HSRM_B


// 110929 Rick add
#define PanelVfreq          (600)
#define PanelMaxVfreq   	(750+20) // 75Hz
#define PanelMinVfreq   	(500-20) // 50Hz

//=================================================================
// TCON  setting for LVDS
//PVS / FSYNC
#define GPO9_VStart     	0x7
#define GPO9_VEnd       	0x705
#define GPO9_HStart     	0x0
#define GPO9_HEnd       	0x0
#define GPO9_Control        0x7

//HSYNC
#define GPOA_VStart     	0x006
#define GPOA_VEnd       	0x408
#define GPOA_HStart     	0
#define GPOA_HEnd       	0
#define GPOA_Control        0x4

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
#define MAX_CURRENT_RATE       110//50
#elif (LED_SERIES == 6)
#define MAX_CURRENT_RATE        30
#elif (LED_SERIES == 8)
#define MAX_CURRENT_RATE        14 //10
#endif


#define BOOST_CURRENT_LIMIT_LEVEL    BIT5//BIT4

#define ENABLE_VCOM_ADJUST              1
#define VCOM_TYPE                   VCOM_MAXIM

#define PANEL_F_MODULATION    			40 // 30~40KHz
#define PANEL_PERCENTAGE        		2.5  // 0.5~3%

//==================================================================
//OVP
#define LED_OVP_TUNING_ENABLE       		0//1

#define PanelLightBarDefaultVoltage    		44
#define PanelLightBarMaximumVoltage    		48
#define OVP1_Ratio							110    // 1.1 
#define OVP1_ProtVoltage					OVP1_Ratio*PanelLightBarMaximumVoltage/100  // 1.1*45=	49.5V
#define OVP2_Ratio							125    // 1.25
#define OVP2_ProtVoltage					OVP2_Ratio*PanelLightBarDefaultVoltage/100  // 1.1*42=	52.5V
#define ResistorRatio						43//(R2+R1)/R1

//==================================================================
//LED Protect
#if 1 //20120419 Rick add
#define SAR_V_10p00             0xB8    //X=10/5.5*100=182=0xB6
#define SAR_V_8p00              0xC5//20130509 from MST hunyi.cai    //6.7/3.3/11*1023=189
#define SAR_V_5p00              0x5D       // U01  0x22E
#define SAR_V_4p50              0x53       // U01  0x1D1
#define SAR_V_1p55              0x30       //=> 2.5V   Skew Low Bond
#define SAR_V_0p55              0xA
#define SAR_V_0p54              0xA
#define SAR_V_0p10              0x5
#endif

#endif
