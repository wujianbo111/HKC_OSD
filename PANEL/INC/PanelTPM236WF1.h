#ifndef __PANEL_TPM236WF1__
#define __PANEL_TPM236WF1__
#define PanelName	  		"TPM236WF1"

#define PanelDither			8

#define PanelTTL			0
#define PanelTCON			0
#define PanelLVDS			0xFF
#define PanelRSDS			0
#define PanelminiLVDS      	0 
#define PANEL_VCOM_ADJUST 	0x00

#define LVDS_TIMode			0xFF
#define PanelDualPort		0xFF
#define PanelSwapPort		0x00
#define PanelSwapOddML		0
#define PanelSwapEvenML		0
#define PanelSwapOddRB		0
#define PanelSwapEvenRB		0
#define PanelSwapMLSB		0
#define PanelSwapLCPS		0

#define PanelDClkDelay		0
#define PanelInvDClk		0
#define PanelInvDE			0
#define PanelInvHSync		0
#define PanelInvVSync		0

// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent		1 // Dclk current
#define PanelDECurrent			1 // DE signal current
#define PanelOddDataCurrent		1 // Odd data current
#define PanelEvenDataCurrent	1 // Even data current

#define PanelOnTiming1		30// T2 <= 20ms // time between panel & data while turn on power
#define PanelOnTiming2		250// T3 >= 200ms // time between data & back light while turn on power
#define PanelOffTiming1		250// T4 >= 200ms // time between back light & data while turn off power 
#if ModelName==AOC_M2470SWD || ModelName==AOC_M2470SWDA
#define PanelOffTiming2		20// T5 <= 50ms // time between data & panel while turn off power 
#else
#define PanelOffTiming2		10// T5 <= 50ms // time between data & panel while turn off power 
#endif
//#define PanelOffOnTiming    1050 // T7 >= 1000ms

#define PanelHSyncWidth		14//32
#define PanelHSyncBackPorch	20

#define PanelVSyncWidth		3
#define PanelVSyncBackPorch	7

#define PanelHStart   		(PanelHSyncWidth+PanelHSyncBackPorch)
#define PanelVStart   		(PanelVSyncWidth+PanelVSyncBackPorch)
#define PanelWidth    		1920
#define PanelHeight   		1080
#define PanelHTotal   		2200 
#define PanelVTotal   		1125

#define PanelMaxHTotal    	2300
#define PanelMinHTotal     	2110
#define PanelMaxVTotal     	1136
#define PanelMinVTotal    	1115
#define PanelDCLK       	148
#define PanelMaxDCLK     	164
#define PanelMinDCLK    	118

#define PanelMaxVfreq   	630
#define PanelMinVfreq   	500

#endif
