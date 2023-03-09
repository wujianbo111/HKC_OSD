#ifndef _PanelBOEMV190E0M_N10_
#define _PanelBOEMV190E0M_N10_
#define PanelName               "BOEMV190E0M"

#define PanelDither     		8

#define PanelTTL            	0
#define PanelTCON       		0
#define PanelLVDS       		0xFF
#define PanelRSDS       		0
#define PanelminiLVDS      		0
#define NormalWhite    			0      		// for normal Black panel
#define PANEL_VCOM_ADJUST    	0x00
#define MINILVDSTCON_DEVICE     0x50
#define MAX_VCOM_VALUE          0x7F
#define DEF_VCOM_VALUE          0x4F
#define MIN_VCOM_VALUE          0x00

#define LVDS_TIMode     		0xFF
#define PanelDualPort       	0xFF
#define PanelSwapPort       	0xFF
#define PanelSwapOddML      	0
#define PanelSwapEvenML     	0
#define PanelSwapOddRB      	0
#define PanelSwapEvenRB     	0
#define PanelSwapMLSB       	0

#define PANEL_SWAP_PN       	0
#define PanelDClkDelay          0
#define PanelInvDE              0
#define PanelInvDClk            0
#define PanelInvHSync           0
#define PanelInvVSync           0
// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent        1 // Dclk current
#define PanelDECurrent        	1 // DE signal current
#define PanelOddDataCurrent    	1 // Odd data current
#define PanelEvenDataCurrent    1 // Even data current

#define PanelOnTiming1          25// time between panel & data while turn on power
#define PanelOnTiming2          300 // time between data & back light while turn on power
#define PanelOffTiming1         300// time between back light & data while turn off power 
#define PanelOffTiming2         25// time between data & panel while turn off power 

#define PanelHSyncWidth       	14 // 20//48
#define PanelHSyncBackPorch   	21//  28//78

#define PanelVSyncWidth         12// 3
#define PanelVSyncBackPorch     28//12

#define PanelHStart           	(PanelHSyncWidth+PanelHSyncBackPorch)
#define PanelVStart           	(PanelVSyncWidth+PanelVSyncBackPorch)

#define PanelWidth      	1280
#define PanelHeight     	1024

#define PanelHTotal     	1688
#define PanelVTotal     	1066

#define PanelMaxHTotal	    1920
#define PanelMinHTotal		1408

#define PanelMaxVTotal		1150
#define PanelMinVTotal		1036

#define PanelDCLK		    108
#define PanelMaxDCLK		134
#define PanelMinDCLK		80

// 111003 Rick add
#define PanelVfreq          	        (600)
#define PanelMaxVfreq   		(750+20) // 75Hz
#define PanelMinVfreq   		(500-20) // 50Hz
//=================================================================
// TCON  setting for LVDS
//PVS / FSYNC
#define GPO9_VStart     		0x7
#define GPO9_VEnd       		0x705
#define GPO9_HStart     		0x0
#define GPO9_HEnd       		0x0
#define GPO9_Control        	0x7

//HSYNC
#define GPOA_VStart     		0x006
#define GPOA_VEnd       		0x408
#define GPOA_HStart     		0
#define GPOA_HEnd       		0
#define GPOA_Control        	0x4

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
#define DISABLE_SHORT_FRAME_TUNE	1	//120827 Modify

#endif
