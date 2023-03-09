
#define PanelName               "BM230WF5_TAE2"
#define PanelDither     		8
#define PanelTTL            	0
#define PanelTCON       		0
#define PanelLVDS       		0xFF
#define PanelRSDS       		0
#define PanelminiLVDS      		0
#define NormalWhite    			0      // for normal Black panel
#define PANEL_VCOM_ADJUST    	0xFF		//120322 Modify
#define MINILVDSTCON_DEVICE     0x50
#define MAX_VCOM_VALUE          0x7F
#define DEF_VCOM_VALUE          0x4F
#define MIN_VCOM_VALUE          0x00

#define LVDS_TIMode     	0xff
#define PANEL_SWAP_PN       0xFF
#define PanelDualPort       0xFF
#define PanelSwapPort       0xFF
#define PanelSwapOddML      0
#define PanelSwapEvenML     0
#define PanelSwapOddRB      0//xFF
#define PanelSwapEvenRB     0//xFF
#define PanelSwapMLSB       0

#define PanelDClkDelay          0
#define PanelInvDE              0
#define PanelInvDClk            0
#define PanelInvHSync           0
#define PanelInvVSync           0

#define PanelOnTiming1          10// time between panel & data while turn on power
#define PanelOnTiming2          550 // time between data & back light while turn on power
#define PanelOffTiming1         250// time between back light & data while turn off power 
#define PanelOffTiming2         10 // time between data & panel while turn off power 
#define PanelWidth      1920
#define PanelHeight     1080
#define PanelHTotal     2176
#define PanelVTotal     1100

#define PanelHSyncWidth       32 // 20//48
#define PanelHSyncBackPorch   48//  28//78

#define PanelVSyncWidth         2// 3
#define PanelVSyncBackPorch     14//12

#define PanelHStart                 (PanelHSyncWidth+PanelHSyncBackPorch)
#define PanelVStart                 (PanelVSyncWidth+PanelVSyncBackPorch)

#define PanelMaxHTotal      2240
#define PanelMinHTotal      2048
#define PanelMaxVTotal      1220
#define PanelMinVTotal          1090
#define PanelDCLK               144
#define PanelMaxDCLK            180//175
#define PanelMinDCLK             120//113
// 111003 Rick add
#define PanelVfreq          (600)
#define PanelMaxVfreq   (750+20) // 75Hz
#define PanelMinVfreq   (500-20) // 50Hz
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


