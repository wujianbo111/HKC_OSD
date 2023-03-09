#ifndef __PANEL_TPM236WF1_HJJP02_SC3G__
#define __PANEL_TPM236WF1_HJJP02_SC3G__


#define PanelName	  "TPM236WF1-HJJP02"

#define PanelDither			8

#define PanelTTL			0
#define PanelTCON			0
#define PanelLVDS			0xFF
#define PanelRSDS			0
#define PanelminiLVDS      	0 
#define PANEL_VCOM_ADJUST 	0x00

#define LVDS_TIMode			0xFF
#define PanelDualPort		0xFF
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
#define PanelOffTiming2		20// T5 <= 50ms // time between data & panel while turn off power 
//#define PanelOffOnTiming    1050 // T7 >= 1000ms

#define PanelHSyncWidth		16//32
#define PanelHSyncBackPorch	80

#define PanelVSyncWidth		3
#define PanelVSyncBackPorch	7

 #define PanelHStart   		(PanelHSyncWidth+PanelHSyncBackPorch)
 #define PanelVStart   		(PanelVSyncWidth+PanelVSyncBackPorch)
 #define PanelWidth    		1920
 #define PanelHeight   		1080
 #define PanelHTotal   		2200 
 #define PanelVTotal   		1125
 
 #define PanelMaxHTotal    	2300
 #define PanelMinHTotal     2100
 #define PanelMaxVTotal     1136
 #define PanelMinVTotal    	1115
 #define PanelDCLK       	148
 #define PanelMaxDCLK     	196
 #define PanelMinDCLK    	118

// 080514
#define PanelMaxVfreq   	(750+13)
#define PanelMinVfreq   	(500-13)

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
#endif 

