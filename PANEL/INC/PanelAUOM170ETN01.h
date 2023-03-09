#define PanelName               "AUOM170ETN01"//petit 20130731
#define PanelDither 		8
#define PanelTTL			0
#define PanelTCON		0
#define PanelLVDS		0xFF
#define PanelRSDS		0
#define PanelminiLVDS      0 
#define PANEL_VCOM_ADJUST        0x00
#define LVDS_TIMode   			0xFF
#define PanelDualPort		0xFF
#define PanelSwapPort		0xFF
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
#define PanelDCLKCurrent  		0 // Dclk current
#define PanelDECurrent    			0 // DE signal current
#define PanelOddDataCurrent 		0// Odd data current
#define PanelEvenDataCurrent  	0 // Even data current
#define PanelOnTiming1    		20 // time between panel & data while turn on power
#define PanelOnTiming2    		550 //  time between data & back light while turn on power  //20050701
#define PanelOffTiming1 			150 //  time between back light & data while turn off power
#define PanelOffTiming2 			20 //  time between data & panel while turn off power
#define PanelHSyncWidth			35
#define PanelHSyncBackPorch		21
#define PanelVSyncWidth			3
#define PanelVSyncBackPorch		7
#define PanelHStart 		(PanelHSyncWidth+PanelHSyncBackPorch)
#define PanelVStart 		(PanelVSyncWidth+PanelVSyncBackPorch)
#define PanelWidth		1280
#define PanelHeight 		1024
#define PanelHTotal		1688 
#define PanelVTotal 		1066
#define PanelMaxHTotal	2640
#define PanelMinHTotal	PanelHTotal//1460  petit 20130909
#define PanelMaxVTotal	1873
#define PanelMinVTotal	1036
#define PanelDCLK		128
#define PanelMaxDCLK	186
#define PanelMinDCLK		104
#define PanelMaxVfreq   (750+13) // 75Hz
#define PanelMinVfreq   (500-13) // 50Hz
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


