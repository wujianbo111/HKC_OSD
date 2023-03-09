// for samsung_panel
#define PanelName               "PanelLM230WF3"//petit 20131108  update

#define PanelDither             8

#define PanelTTL                0
#define PanelTCON               0
#define PanelLVDS               0xFF
#define PanelRSDS               0
#define PanelminiLVDS      		0
#define NormalWhite    			0      // for normal Black panel

#define LVDS_TIMode             0xFF  //Thine mode:disable TI mode
#define PANEL_SWAP_PN       0

#define PanelDualPort       0xFF
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

#define PanelOnTiming1          20 // time between panel & data while turn on power
#define PanelOnTiming2          550 // time between data & back light while turn on power
#define PanelOffTiming1         250//350//220 // 2005/5/3// time between back light & data while turn off power
#define PanelOffTiming2         20//20//25 // 2005/5/3//10 // time between data & panel while turn off power

#define PanelWidth      1920
#define PanelHeight     1080
#define PanelHTotal     2176
#define PanelVTotal     1100


#define PanelHSyncWidth         20//48
#define PanelHSyncBackPorch     28//78

#define PanelVSyncWidth         2// 3
#define PanelVSyncBackPorch     14//12

#define PanelHStart                 (PanelHSyncWidth+PanelHSyncBackPorch)
#define PanelVStart                 (PanelVSyncWidth+PanelVSyncBackPorch)

#define PanelMaxHTotal      2240
#define PanelMinHTotal       2048 //2060//2048  petit 20131216
#define PanelMaxVTotal     1160
#define PanelMinVTotal          1090

#define PanelDCLK               	144
#define PanelMaxDCLK             180//175//petit 20131219//Gino 20140516
#define PanelMinDCLK              120

// 111003 Rick add
#define PanelVfreq          (600)
#define PanelMaxVfreq   (750+20) // 75Hz
#define PanelMinVfreq   (500-20) // 50Hz


