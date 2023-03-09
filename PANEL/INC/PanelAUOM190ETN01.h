#ifndef __PANEL_AUOM190ETN01__
    #define __PANEL_AUOM190ETN01__

//#define PanelNumber             1800 
#define PanelName             "AUOM190ETN01"

#define PanelDither		8

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

#define PanelOnTiming1		30// T2 <= 20ms // time between panel & data while turn on power
#define PanelOnTiming2		550// T3 >= 200ms // time between data & back light while turn on power
#define PanelOffTiming1		250// T4 >= 200ms // time between back light & data while turn off power 
#define PanelOffTiming2		16//30// T5 <= 50ms // time between data & panel while turn off power 
#define PanelOffOnTiming    1050 // T7 >= 1000ms

#define PanelHSyncWidth       	34 // 20//48
#define PanelHSyncBackPorch   	46//  28//78

#define PanelVSyncWidth         2// 3
#define PanelVSyncBackPorch     14//12

#define PanelHStart           	(PanelHSyncWidth+PanelHSyncBackPorch)
#define PanelVStart           	(PanelVSyncWidth+PanelVSyncBackPorch)

#define PanelWidth      		1280
#define PanelHeight     		1024
#define PanelHTotal     		1688
#define PanelVTotal     		1066

#define PanelMaxHTotal		2640//2400
#define PanelMinHTotal		1460//1680
#define PanelMaxVTotal		1873//1200
#define PanelMinVTotal		1036//908
#define PanelDCLK		    108//98
#define PanelMaxDCLK		136//144
#define PanelMinDCLK		75//80

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
#endif
