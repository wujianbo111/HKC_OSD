#ifndef __PanelM270HVN02__
#define __PanelM270HVN02__
#define PanelName           "M270HVN02"




#define PanelDither     8

#define PanelTTL            0
#define PanelTCON           0
#define PanelLVDS           0xFF
#define PanelRSDS           0

#define LVDS_TIMode     	0xff
#define PanelDualPort       0xFF
#define PanelSwapPort       0
#define PanelSwapOddML      0
#define PanelSwapEvenML     0
#define PanelSwapOddRB      0//xFF
#define PanelSwapEvenRB     0//xFF
#define PanelSwapMLSB       0
#define PanelSwapPlusMinus      0
#define PANEL_SWAP_PN       0xFF





#define PanelSwapOddML		0
#define PanelSwapEvenML		0
#define PanelSwapOddRB		0//xFF
#define PanelSwapEvenRB		0//xFF
#define PanelSwapMLSB		0

#define PanelSwapLCPS		0


#define PanelDClkDelay		0
#define PanelInvDClk			0
#define PanelInvDE			0
#define PanelInvHSync		0
#define PanelInvVSync		0

// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent		1 // Dclk current
#define PanelDECurrent		1 // DE signal current
#define PanelOddDataCurrent	1 // Odd data current
#define PanelEvenDataCurrent	1 // Even data current

#define PanelOnTiming1		20// T2 <= 20ms // time between panel & data while turn on power
#define PanelOnTiming2		550// T3 >= 200ms // time between data & back light while turn on power
#define PanelOffTiming1		150// T4 >= 200ms // time between back light & data while turn off power 
#define PanelOffTiming2		15// T5 <= 50ms // time between data & panel while turn off power 


#define PanelHSyncWidth		16//32
#define PanelHSyncBackPorch	50

#define PanelVSyncWidth		3
#define PanelVSyncBackPorch	6

 #define PanelHStart   (PanelHSyncWidth+PanelHSyncBackPorch)
 #define PanelVStart   (PanelVSyncWidth+PanelVSyncBackPorch)
 #define PanelWidth    1920
 #define PanelHeight   1080
 #define PanelHTotal   2100 
 #define PanelVTotal   1130 
 
 #define PanelMaxHTotal    2200
 #define PanelMinHTotal     2028
 #define PanelMaxVTotal     1793 
 #define PanelMinVTotal    1092
 
 #define PanelDCLK            142
 #define PanelMaxDCLK          180
 #define PanelMinDCLK          110

// 080514
#define PanelMaxVfreq   (900+13)
#define PanelMinVfreq   (550-13)

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
#define LVDS_VOLTAGE_TARGET  IGT_TARGET_250//petit 20131216

#endif
