#ifndef __PANEL_LM240WU8_SLD1__   //PanelTPM215HW01
    #define __PANEL_LM240WU8_SLD1__


//#define PanelNumber             1800
#define PanelName       "LM240WU8SLD1" // 130530 JUN Modify
#define PanelDither		6//8	//	130711 william	For NVIDIA 9500GT NVIDIA GeForce 9600 GT  Noise 	

#define PanelTTL			0
#define PanelTCON		0
#define PanelLVDS		0xFF
#define PanelRSDS		0
#define PanelminiLVDS      0 
#define PANEL_VCOM_ADJUST        0x00

#define LVDS_TIMode		     0xFF
#define PANEL_SWAP_PN       0x00

#define PanelDualPort		0xFF
#define PanelSwapPort		0x00
#define PanelSwapOddML		0
#define PanelSwapEvenML		0
#define PanelSwapOddRB		0
#define PanelSwapEvenRB		0
#define PanelSwapMLSB		0

#define PanelDClkDelay		8
#define PanelInvDClk			0
#define PanelInvDE			0
#define PanelInvHSync		0
#define PanelInvVSync		0

// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent		1 // Dclk current
#define PanelDECurrent		1 // DE signal current
#define PanelOddDataCurrent	1 // Odd data current
#define PanelEvenDataCurrent	1 // Even data current

//130708 Petit
#define PanelOnTiming1		25  // 20 //090302// T2 <= 50ms // time between panel & data while turn on power // 130530 JUN Modify
#define PanelOnTiming2		500// T5 >= 450ms // time between data & back light while turn on power
#if ModelName == NDS_E2421PI
#define PanelOffTiming1		250// t6 >= 90ms // time between back light & data while turn off power // spec is 200 ms
#else
#define PanelOffTiming1		140// t6 >= 90ms // time between back light & data while turn off power 
#endif
#define PanelOffTiming2		5  // 20// T3 <= 50ms // time between data & panel while turn off power 
#define PanelOffOnDelay     1400 // T4 >= 500ms

#define PanelHSyncWidth		14//46
#define PanelHSyncBackPorch	31

#define PanelVSyncWidth		3
#define PanelVSyncBackPorch	13

 #define PanelHStart   (PanelHSyncWidth+PanelHSyncBackPorch)
 #define PanelVStart   (PanelVSyncWidth+PanelVSyncBackPorch)
 #define PanelWidth    1920
 #define PanelHeight   1200
 
 #define PanelHTotal   2086  
 #define PanelVTotal   1235
 
 #define PanelMaxHTotal     2096
 #define PanelMinHTotal     2026
 
 #define PanelMaxVTotal     1390 
 #define PanelMinVTotal    1229
 
 #define PanelDCLK           149//140
 #define PanelMaxDCLK          164//190
 #define PanelMinDCLK          124

// 080514
#define PanelMaxVfreq   620 // 75Hz
#define PanelMinVfreq   495 // 50Hz


#endif

