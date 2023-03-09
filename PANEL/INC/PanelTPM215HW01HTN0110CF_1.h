#define PanelName              "TPM215HW01-HTN01"

#define PanelDither		8

#define PanelTTL			0
#define PanelTCON		0
#define PanelLVDS		0xFF
#define PanelRSDS		0
#define PanelminiLVDS      0 
#define PANEL_VCOM_ADJUST        0x00

#define LVDS_TIMode		       0xFF
#define PanelDualPort		0xFF
#if MainBoardType==MainBoard_7219_M0C
#define PanelSwapPort		0
#else
#define PanelSwapPort		0xFF
#endif
#define PanelSwapOddML		0
#define PanelSwapEvenML		0
#define PanelSwapOddRB		0
#define PanelSwapEvenRB		0
#define PanelSwapMLSB		0

#define PanelDClkDelay		0
#define PanelInvDClk			0
#define PanelInvDE			0
#define PanelInvHSync		0
#define PanelInvVSync		0

// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent		 0// Dclk current
#define PanelDECurrent		  0//DE signal current
#define PanelOddDataCurrent	 0// Odd data current
#define PanelEvenDataCurrent 	0// Even data current

#define PanelOnTiming1		20 //090302// T2 <= 50ms // time between panel & data while turn on power
#define PanelOnTiming2		550// T5 >= 450ms // time between data & back light while turn on power
#define PanelOffTiming1		250// t6 >= 90ms // time between back light & data while turn off power 
#define PanelOffTiming2		20// T3 <= 50ms // time between data & panel while turn off power 

#define PanelHSyncWidth		  20
#define PanelHSyncBackPorch	  18

#define PanelVSyncWidth		1
#define PanelVSyncBackPorch	1

 #define PanelHStart   (PanelHSyncWidth+PanelHSyncBackPorch)
 #define PanelVStart   (PanelVSyncWidth+PanelVSyncBackPorch)
 #define PanelWidth    1920
 #define PanelHeight   1080
 
 #define PanelHTotal   2100  
 #define PanelVTotal   1130 
 
 #define PanelMaxHTotal     2200
 #define PanelMinHTotal     2068
 
 #define PanelMaxVTotal     1818 
 #define PanelMinVTotal    1092
 
 #define PanelDCLK            142
 #define PanelMaxDCLK          188
 #define PanelMinDCLK          113

// 080514
#define PanelMaxVfreq   (750+13) // 75Hz
#define PanelMinVfreq   (500-13) // 50Hz


