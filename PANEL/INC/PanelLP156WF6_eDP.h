#define PanelName	  "LP156WF6_eDP"

#define PanelDither			8

#define PanelTTL			0
#define PanelTCON			0
#define PanelLVDS			0xFF
#define PanelRSDS			0
#define PanelminiLVDS      	0
#define PANEL_VCOM_ADJUST 	0xFF//Petit 20141224
#define MINILVDSTCON_DEVICE     	0x50
#define MAX_VCOM_VALUE          	0x7F
#define DEF_VCOM_VALUE          	0x4D//0x4F
#define MIN_VCOM_VALUE          	0x00


#define PANEL_SWAP_PN   0x00
#define LVDS_TIMode			0xFF
#define PanelDualPort		0
#define PanelSwapPort		0
#define PanelSwapOddML		0
#define PanelSwapEvenML		0
#define PanelSwapOddRB		0//xFF
#define PanelSwapEvenRB		0//xFF
#define PanelSwapMLSB		0
#define PanelSwapLCPS		0

#define PanelDClkDelay		0
#define PanelInvDClk		0
#define PanelInvDE			0
#define PanelInvHSync		0
#define PanelInvVSync		0

// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent		 0// Dclk current
#define PanelDECurrent		  0//DE signal current
#define PanelOddDataCurrent	 0// Odd data current
#define PanelEvenDataCurrent 	0// Even data current

#define PanelOnTiming1		20// T2 <= 20ms // time between panel & data while turn on power
#define PanelOnTiming2		550// T3 >= 200ms // time between data & back light while turn on power
#define PanelOffTiming1		250// T4 >= 200ms // time between back light & data while turn off power
#define PanelOffTiming2		5//20// T5 <= 50ms // time between data & panel while turn off power
//#define PanelOffOnTiming    1050 // T7 >= 1000ms

#define PanelHSyncWidth		32
#define PanelHSyncBackPorch	80

#define PanelVSyncWidth		5
#define PanelVSyncBackPorch	23

 #define PanelHStart   		(PanelHSyncWidth+PanelHSyncBackPorch)
 #define PanelVStart   		(PanelVSyncWidth+PanelVSyncBackPorch)
 #define PanelWidth    		1920
 #define PanelHeight   		1080
 #define PanelHTotal   		2080
 #define PanelVTotal   		1111

 #define PanelMaxHTotal    	2088
 #define PanelMinHTotal     2072
 #define PanelMaxVTotal     1114
 #define PanelMinVTotal    	1108
#define PanelVsyncFreq      60

 #define PanelDCLK       	 (((DWORD)PanelHTotal*PanelVTotal*PanelVsyncFreq)/1000000)//138
 #define PanelMaxDCLK     	139
 #define PanelMinDCLK    	137

// 080514
#define PanelMaxVfreq   	(600)
#define PanelMinVfreq   	(600)

// eDP Timing define
#define DP_800X600_60HZ     0
#define DP_1024X768_60HZ   1
#define DP_1280X800_60HZ   2
#define DP_1360X768_60HZ   3
#define DP_480P                     4
#define DP_720P                     5
#define DP_1080P                   6
#define DP_1080P_120HZ       7
#define DP_2560X1440_60Hz    8

// eDP Link Rate define
#define DPTXRBR        0
#define DPTXHBR        1
#define DPTXHBRx11  2
#define DPTXHBRx12  3

// eDP Lane Count define
#define DPTX1L          0
#define DPTX2L          1
#define DPTX4L          2

//set eDP TX Timing
#define eDPTXTiming        DP_1080P
//set eDP TX Min Link Rate
#define eDPTXMinRate     DPTXRBR
// set eDP TX Min Lane Count
#define eDPTXMinLane     DPTX2L

//I_Gen_Tuning CH Source Select
#define I_Gen_CH  CH9_CLK
//=================================================================
// TCON	 setting for LVDS
//PVS / FSYNC
#define GPO9_VStart			0x7
#define GPO9_VEnd			0x705
#define GPO9_HStart			0x0
#define GPO9_HEnd			0x0
#define GPO9_Control		0x7

//HSYNC
#define GPOA_VStart			0x006
#define GPOA_VEnd			0x408
#define GPOA_HStart			0
#define GPOA_HEnd			0
#define GPOA_Control		0x4

