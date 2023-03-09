#ifndef __PANE_LM315WF1_S4A1___   //PanelTPM215HW01
#define __PANE_LM315WF1_S4A1___
// for samsung_panel
#define PanelName               "LM315WF1S4A1"

#define PanelDither             8

#define PanelTTL                0
#define PanelTCON               0
#define PanelLVDS               0xFF
#define PanelRSDS               0
#define PanelminiLVDS      		0
#define NormalWhite    			0      // for normal Black panel
#define PANEL_VCOM_ADJUST 		0xFF		//120322 Modify
#define MINILVDSTCON_DEVICE     0x40
#define MAX_VCOM_VALUE          225
#define DEF_VCOM_VALUE          195
#define MIN_VCOM_VALUE          165
#define VCOM_VALUE_OFFSET       314


#define LVDS_TIMode             0xFF  //Thine mode:disable TI mode
#define PANEL_SWAP_PN           0xFF
#define LVDS_TI_BitModeSel      LVDS_TI_8BIT
#define PanelDualPort      		0xFF
#define PanelSwapPort           0x00

#define PanelSwapOddML          0
#define PanelSwapEvenML         0
#define PanelSwapOddRB          0
#define PanelSwapEvenRB         0
#define PanelSwapMLSB           0

#define PanelDClkDelay          0
#define PanelInvDE              0
#define PanelInvDClk            0
#define PanelInvHSync           0
#define PanelInvVSync           0

// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent        1 // Dclk current
#define PanelDECurrent          1 // DE signal current
#define PanelOddDataCurrent     1 // Odd data current
#define PanelEvenDataCurrent    1 // Even data current

#define PanelOnTiming1          20 // time between panel & data while turn on power
#define PanelOnTiming2          550 // time between data & back light while turn on power
#define PanelOffTiming1         250//350//220 // 2005/5/3// time between back light & data while turn off power
#define PanelOffTiming2         20//20//25 // 2005/5/3//10 // time between data & panel while turn off power

#define PanelOffOnDelay         1100 // T4 >= 500ms

#define PanelWidth     			1920
#define PanelHeight     		1080

#define PanelHTotal     		2200
#define PanelVTotal     		1125


#define PanelHSyncWidth         32//48
#define PanelHSyncBackPorch     48//78

#define PanelVSyncWidth         4// 3
#define PanelVSyncBackPorch     8//12

#define PanelHStart                 (PanelHSyncWidth+PanelHSyncBackPorch)
#define PanelVStart                 (PanelVSyncWidth+PanelVSyncBackPorch)

#define PanelMaxHTotal      	2400
#define PanelMinHTotal       	2120 //2060//2048  petit 20131216

#define PanelMaxVTotal     		1149
#define PanelMinVTotal          1100

#define PanelDCLK                148
#define PanelMaxDCLK             156
#define PanelMinDCLK             126

// 111003 Rick add
#define PanelVfreq          (600)
#define PanelMaxVfreq   (750+20) // 75Hz
#define PanelMinVfreq   (500-20) // 50Hz

#define ENABLE_VCOM_ADJUST              1
#define VCOM_TYPE                   VCOM_SMIM

#endif

