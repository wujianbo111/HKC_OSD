#ifndef __PanelM170ETN01__
#define __PanelM170ETN01__
#define PanelName	"M170ETN01"
#define PANEL_TYPE	        PANEL_17_WIDE	//??
#define PanelDither   6
#define PanelTTL    0
#define PanelTCON   0
#define PanelLVDS   0xff
#define PanelRSDS   0
#define PanelminiLVDS      0 

#define PANEL_VCOM_ADJUST        0x00

#define LVDS_TIMode   			0xff
#define PanelDualPort   			0xff
#define PanelSwapPort   			0xff
#define PanelSwapOddML    		0
#define PanelSwapEvenML   		0
#define PanelSwapOddRB    		0
#define PanelSwapEvenRB   		0
#define PanelSwapMLSB   			0
#define PanelDClkDelay    			8
#define PanelInvDE      			0
#define PanelInvDClk    			0
#define PanelInvHSync   			0
#define PanelInvVSync   			0
// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent  		1 // Dclk current
#define PanelDECurrent    			1 // DE signal current
#define PanelOddDataCurrent 		1 // Odd data current
#define PanelEvenDataCurrent  	1 // Even data current
#define PanelOnTiming1    		25 // 0//40 // time between panel & data while turn on power
#define PanelOnTiming2    		550//250 // 300//300 //30 // time between data & back light while turn on power  //20050701
#define PanelOffTiming1 			250//250 // 300 // time between back light & data while turn off power
#define PanelOffTiming2 			40 // 20 // time between data & panel while turn off power
#define PanelHSyncWidth   		25//32
#define PanelHSyncBackPorch 	20 //152//24
#define PanelVSyncWidth   		3
#define PanelVSyncBackPorch 		21 // 46
#define PanelHStart   	(PanelHSyncWidth+PanelHSyncBackPorch)
#define PanelVStart   	(PanelVSyncWidth+PanelVSyncBackPorch)
#define PanelWidth    	1280
#define PanelHeight   	1024
#define PanelHTotal   		1688
#define PanelVTotal   		1066
#define PanelMaxHTotal 		4096
#define PanelMinHTotal     	1560
#define PanelMaxVTotal   	1150
#define PanelMinVTotal    	1032
#define PanelDCLK           108
#define PanelMaxDCLK        135
#define PanelMinDCLK        80

#define TURNOFF_PANEL_BEFORE_DISABLE_LVDS_OUTPUT				1
#define NormalWhite    1
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
