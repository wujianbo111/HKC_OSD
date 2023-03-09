#ifndef __PANEL_TPM270WF1HP04__   //PanelCMIM215HGE_L21
#define __PANEL_TPM270WF1HP04__

//#define PanelNumber             1800
#define PanelName       "TPM270WF1HP04"
#define PanelDither			8

#define PanelTTL			0
#define PanelTCON			0
#define PanelLVDS			0xFF
#define PanelRSDS			0
#define PanelminiLVDS      	0 
#define NormalWhite			0

#define LVDS_TIMode		 	0xFF


#define PANEL_SWAP_PN          0x00

#define LVDS_TI_BitModeSel      LVDS_TI_8BIT
#define PanelDualPort			0xFF
#define PanelSwapPort           0xFF
#define PanelSwapOddML			0
#define PanelSwapEvenML			0
#define PanelSwapOddRB			0
#define PanelSwapEvenRB			0
#define PanelSwapMLSB			0

#define PanelDClkDelay			8
#define PanelInvDClk			0
#define PanelInvDE				0
#define PanelInvHSync			0
#define PanelInvVSync			0

// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent		1 // Dclk current
#define PanelDECurrent			1 // DE signal current
#define PanelOddDataCurrent		1 // Odd data current
#define PanelEvenDataCurrent	1 // Even data current


#define PanelOnTiming1		30  // 20 //090302// T2 <= 50ms // time between panel & data while turn on power//20130701 bian
#define PanelOnTiming2		1100// T5 >= 450ms // time between data & back light while turn on power
#define PanelOffTiming1		250// t6 >= 90ms // time between back light & data while turn off power 
#define PanelOffTiming2		120  // 20// T3 <= 50ms // time between data & panel while turn off power 


#define PanelOffOnDelay        1100 // T4 >= 500ms

#define PanelHSyncWidth			12//46
#define PanelHSyncBackPorch		28

#define PanelVSyncWidth			14
#define PanelVSyncBackPorch		21

 #define PanelHStart   		(PanelHSyncWidth+PanelHSyncBackPorch)
 #define PanelVStart   		(PanelVSyncWidth+PanelVSyncBackPorch)
 #define PanelWidth    		1920
 #define PanelHeight   		1080
 
 #define PanelHTotal   		2160//2200  
 #define PanelVTotal   		1100//1126
 
 #define PanelMaxHTotal     2200//2300
 #define PanelMinHTotal     2120//2100
 
 #define PanelMaxVTotal     1220//1136 
 #define PanelMinVTotal     1105//1050
 
 #define PanelDCLK       	144
 #define PanelMaxDCLK      	184
 #define PanelMinDCLK     	116

// 080514
#define PanelVfreq          (600)
#define PanelMaxVfreq   	(750+13)
#define PanelMinVfreq   	(500-13)

#define DISABLE_SHORT_FRAME_TUNE     1

#endif

