#ifndef __PANEL_M280HKJ_L50_VER10__   //PanelTPM215HW01
    #define __PANEL_M280HKJ_L50_VER10__


#define PanelName       "PanelM280HKJ-L50"//petit 20130730
#define PanelDither		8//Modify Gino 20150423

#define PanelTTL			0
#define PanelTCON		0
#define PanelLVDS		0xFF
#define PanelRSDS		0
#define PanelminiLVDS      0 
#define PANEL_VCOM_ADJUST        0x00

#define LVDS_TIMode		     0xFF
#if MainBoardType == MainBoard_7983_M0A
#define PANEL_SWAP_PN       0xFF
#else
#define PANEL_SWAP_PN       0x00
#endif
#define PanelDualPort		0xFF

#if MainBoardType == MainBoard_6124_M0A	//131113 fay
#define PanelSwapPort		0xFF
#else
#define PanelSwapPort		0x00
#endif

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
//130708 petit
#if MainBoardType ==MainBoard_6124_M0A		//Fay 2013/12/4   
#define PanelOnTiming1		40  // 20 //090302// T2 <= 50ms // time between panel & data while turn on power
#else
#define PanelOnTiming1		20  // 20 //090302// T2 <= 50ms // time between panel & data while turn on power
#endif
#define PanelOnTiming2		850//550// T5 >= 450ms // time between data & back light while turn on power
#define PanelOffTiming1		250// t6 >= 90ms // time between back light & data while turn off power 
#define PanelOffTiming2		10//20  fay // 20// T3 <= 50ms // time between data & panel while turn off power 
#define PanelOffOnDelay        550 // T4 >= 500ms

#define PanelHSyncWidth		14//46
#define PanelHSyncBackPorch	31

#define PanelVSyncWidth		3
#define PanelVSyncBackPorch	13

 #define PanelHStart   (PanelHSyncWidth+PanelHSyncBackPorch)
 #define PanelVStart   (PanelVSyncWidth+PanelVSyncBackPorch)
 #define PanelWidth    1920
 #define PanelHeight   1080
 
 #define PanelHTotal   2200  
 #define PanelVTotal   1125
 
 #define PanelMaxHTotal     2300//2300	//130910 fay
 #define PanelMinHTotal     2100

 #define PanelMaxVTotal     1220//1380 	//130910 fay
 #define PanelMinVTotal      1110//1115

 #define PanelDCLK           148//150//140		//130910 fay
 #define PanelMaxDCLK         195// 216//190	//130910 fay
 #define PanelMinDCLK          118//50			//130910 fay

// 080514
#define PanelMaxVfreq       610//625  // (750+13) // 75Hz	//Fay 2013/9/10   For Panel SPEC Update
#define PanelMinVfreq        570  //(500-13) // 50Hz


#endif

