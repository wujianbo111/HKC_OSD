//130801 xiandi by panel spec
#define PanelName               "HR236WU1"
#define PanelDither             8
#define PanelTTL                0
#define PanelTCON               0
#define PanelLVDS               0xFF
#define PanelRSDS               0
#define PanelminiLVDS      		0
#define PANEL_VCOM_ADJUST     	0x00

#define LVDS_TIMode             0xFF  //Thine mode:disable TI mode
#define PANEL_SWAP_PN       	0
#define LVDS_TI_BitModeSel      LVDS_TI_8BIT
#define PanelDualPort       	0xFF
#define PanelSwapPort           0
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
#define PanelDECurrent              1 // DE signal current
#define PanelOddDataCurrent         1 // Odd data current
#define PanelEvenDataCurrent    1 // Even data current

#if (MainBoardType==MainBoard_6223_M0A)//20130522
#define PanelOnTiming1			10  // 20 //090302// T2 <= 50ms // time between panel & data while turn on power//20130701 bian
#else
#define PanelOnTiming1          25//60//20 // time between panel & data while turn on power
#endif
#define PanelOnTiming2          250//550//350//220 // time between data & back light while turn on power
#define PanelOffTiming1         250//350//220 // 2005/5/3// time between back light & data while turn off power
#if (MainBoardType==MainBoard_6223_M0A)//20130701 bian
#define PanelOffTiming2			15  // 20// T3 <= 50ms // time between data & panel while turn off power 
#else
#define PanelOffTiming2         25//20//25 // 2005/5/3//10 // time between data & panel while turn off power
#endif

#define PanelHSyncWidth         20//48
#define PanelHSyncBackPorch     28//78

#define PanelVSyncWidth         2// 3
#define PanelVSyncBackPorch     14//12

#define PanelHStart                 (PanelHSyncWidth+PanelHSyncBackPorch)
#define PanelVStart                 (PanelVSyncWidth+PanelVSyncBackPorch)

#define PanelWidth      		1920
#define PanelHeight     		1080
#define PanelHTotal     		2200
#define PanelVTotal     		1126

#define PanelMaxHTotal      	2300
#define PanelMinHTotal      	2110
#define PanelMaxVTotal     		1136
#define PanelMinVTotal     		1115

#define PanelDCLK         		148
#define PanelMaxDCLK          	196
#define PanelMinDCLK          	118

// 111003 Rick add
#define PanelVfreq          	(600)
#define PanelMaxVfreq   		(750+10) // 75Hz
#define PanelMinVfreq   		(500-10) // 50Hz
#define PanelVsyncFreq          60
