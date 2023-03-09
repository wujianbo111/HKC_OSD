#ifndef __PanelTPM215HW01DAT01__
#define __PanelTPM215HW01DAT01__
#define PanelName       "TPM215HW01DAT01"

#define PanelDither		8

#define PanelTTL			0
#define PanelTCON		0
#define PanelLVDS		0xFF
#define PanelRSDS		0
#define PanelminiLVDS      0 
#define PANEL_VCOM_ADJUST        0x00

#define LVDS_TIMode		0xff

#define PANEL_SWAP_PN       0xFF
#define PanelDualPort		0xFF
#define PanelSwapPort		0
#define PanelSwapOddML		0
#define PanelSwapEvenML		0
#define PanelSwapOddRB		0//xFF
#define PanelSwapEvenRB		0//xFF
#define PanelSwapMLSB		0

#define PanelDClkDelay    8
#define PanelInvDE      0
#define PanelInvDClk    0
#define PanelInvHSync   0
#define PanelInvVSync   0
// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent  1 // Dclk current
#define PanelDECurrent    1 // DE signal current
#define PanelOddDataCurrent 1 // Odd data current
#define PanelEvenDataCurrent  1 // Even data current

#define PanelOnTiming1		15//20//60//20 // time between panel & data while turn on power
#define PanelOnTiming2		650//530//350//220 // time between data & back light while turn on power
#define PanelOffTiming1		130//350//220 // 2005/5/3// time between back light & data while turn off power 
#define PanelOffTiming2		20//20//25 // 2014/7/15/10 // time between data & panel while turn off power 

#define PanelHSyncWidth		14//15
#define PanelHSyncBackPorch	15//40

#define PanelVSyncWidth		3
#define PanelVSyncBackPorch	29//13

#define PanelHStart   (PanelHSyncWidth+PanelHSyncBackPorch)
#define PanelVStart   (PanelVSyncWidth+PanelVSyncBackPorch)


#define PanelWidth    1920
#define PanelHeight   1080
#define PanelHTotal   2120//2020//2100 
#define PanelVTotal   1130//1111//1130 
#define PanelMaxHTotal     2150//2080//2176 
#define PanelMinHTotal     1984//1980//2048
#define PanelMaxVTotal     1170//1118//2047 
#define PanelMinVTotal     1084//1105//1088 


#define PanelDCLK            144//136  //  120
#define PanelMaxDCLK          180//174//166//170 // 160 // 150 //  162  //140715 Gino
#define PanelMinDCLK          110//113//   100
// 080514
#define PanelMaxVfreq   (750+13)
#define PanelMinVfreq   (500-13)

//HSYNC
#define GPOA_VStart   0
#define GPOA_VEnd   0
#define GPOA_HStart   0
#define GPOA_HEnd   0
#define GPOA_Control  0
#endif
