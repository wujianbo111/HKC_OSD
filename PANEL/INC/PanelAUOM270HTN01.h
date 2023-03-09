#define PanelName	  "AUOM270HTN01"

#define PanelDither		8

#define PanelTTL			0
#define PanelTCON		0
#define PanelLVDS		0xFF
#define PanelRSDS		0
#define PanelminiLVDS      0 
#define PANEL_VCOM_ADJUST        0x00

#define LVDS_TIMode		0xff
#define PanelDualPort		0xFF
#define PanelSwapPort		0xFF
#define PanelSwapOddML		0
#define PanelSwapEvenML		0
#define PanelSwapOddRB		0//xFF
#define PanelSwapEvenRB		0//xFF
#define PanelSwapMLSB		0
#if 0//SingleBoard
#define PanelSwapLCPS		0xFF
#else
#define PanelSwapLCPS		0
#endif

#define PanelDClkDelay		0
#define PanelInvDClk			0
#define PanelInvDE			0
#define PanelInvHSync		0
#define PanelInvVSync		0

// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent		1 // Dclk current
#define PanelDECurrent		1 // DE signal current
#define PanelOddDataCurrent	1 // Odd data current
#define PanelEvenDataCurrent	1 // Even data current

#define PanelOnTiming1		40//20// T2 <= 20ms // time between panel & data while turn on power
#define PanelOnTiming2		550// T3 >= 200ms // time between data & back light while turn on power
#define PanelOffTiming1		150// T4 >= 200ms // time between back light & data while turn off power 
#define PanelOffTiming2		5// petit  20130903// T5 <= 50ms // time between data & panel while turn off power 
//#define PanelOffOnTiming    1050 // T7 >= 1000ms

#define PanelHSyncWidth		16//32
#define PanelHSyncBackPorch	80

#define PanelVSyncWidth		3
#define PanelVSyncBackPorch	7

 #define PanelHStart   (PanelHSyncWidth+PanelHSyncBackPorch)
 #define PanelVStart   (PanelVSyncWidth+PanelVSyncBackPorch)
 #define PanelWidth    1920
 #define PanelHeight   1080
 #define PanelHTotal   2100 
 #define PanelVTotal   1130 
 
 #define PanelMaxHTotal    2200//4094
 #define PanelMinHTotal     2068
 #define PanelMaxVTotal     1818//2047 
 #define PanelMinVTotal    1092//1088
 #define PanelDCLK            142//150
 #define PanelMaxDCLK         188// 180
 #define PanelMinDCLK          114//80

// 080514
#define PanelMaxVfreq   (750+13)
#define PanelMinVfreq   (500-13)

//=================================================================
// TCON	 setting for LVDS
//PVS / FSYNC
#define GPO9_VStart		0x7
#define GPO9_VEnd		0x705
#define GPO9_HStart		0x0
#define GPO9_HEnd		0x0
#define GPO9_Control		0x7

//HSYNC
#define GPOA_VStart		0x006
#define GPOA_VEnd		0x408
#define GPOA_HStart		0 
#define GPOA_HEnd		0 
#define GPOA_Control		0x4 
#if MainBoardType==MainBoard_5276_M0A
    #define PANEL_SWAP_PN   0xff
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
#define MAX_CURRENT_RATE      120
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
// 20130313 Modify	Follow hungyi solution
#define SAR_V_8p00              0xC5//20130509 from MST hunyi.cai     //6.7/3.3/11*1023=189
#define SAR_V_5p00              0x5D       // U01  0x22E
#define SAR_V_4p50              0x53       // U01  0x1D1
#define SAR_V_1p55              0x30       //=> 2.5V   Skew Low Bond
#define SAR_V_0p55              0xA
#define SAR_V_0p54              0xA
#define SAR_V_0p10              0x5
#endif

