
#define PanelName   "BOE HV320QHM C80"
#define PanelDither         8

#define PanelTTL            0
#define PanelTCON           0
#define PanelLVDS           0xFF //  0

#define PANEL_SWAP_AB_PORT  0 //0: non-swap, 0xFF: AB swap
#define PANEL_SWAP_CD_PORT  0//0: non-swap ,0xFF: CD swap

#define LVDS_CH_A_SWAP            LVDS_CH_D //LVDS_CH_B  //  LVDS_CH_A
#define LVDS_CH_B_SWAP      	     LVDS_CH_C//	LVDS_CH_B  //110427
#define LVDS_CH_C_SWAP      	     LVDS_CH_B ///0//110511_03  LVDS_CH_C  //110427
#define LVDS_CH_D_SWAP            LVDS_CH_A///0xE0


#define PAIR_SWAP_B         0

#define ShortLineCheck      FUNC_ENABLE
#define LVDS_TIMode         FUNC_ENABLE  //Thine mode:disable TI mode

#define LVDS_TI_BitModeSel  LVDS_TI_10BIT

#define PanelDualPort       0
#define PANEL_QUAD_PORT       0xFF//FUNC_ENABLE
#define PanelSwapPort       0
#define PanelSwapOddML      0
#define PanelSwapEvenML     0
#define PanelSwapOddRB      0
#define PanelSwapEvenRB     0
#define PanelSwapMLSB       0
#define PanelSwapPN         0//FUNC_ENABLE

//    panel output type select
#define PANEL_OUTPUT_FMT_3D_LR      FUNC_ENABLE
#define PANEL_OUTPUT_FMT_3D_CB      0

#define PanelDClkDelay      1//FUNC_DISABLE
#define PanelInvDE          FUNC_DISABLE
#define PanelInvDClk        FUNC_DISABLE
#define PanelInvHSync       FUNC_DISABLE
#define PanelInvVSync       FUNC_DISABLE

// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent    1 // Dclk current
#define PanelDECurrent      1 // DE signal current
#define PanelOddDataCurrent 1 // Odd data current
#define PanelEvenDataCurrent    1 // Even data current
#if 1

#define PanelOnTiming1		50   //time between panel & data while turn on power
#define PanelOnTiming2		550 //time between data & back light while turn on power 
#define PanelOffTiming1		300 //time between back light & data while turn off power 
#define PanelOffTiming2		20   //time between data & panel while turn off power 
#define PanelOffOnDelay		1100


#define PanelHSyncWidth     		32
#define PanelHSyncBackPorch   	80

#define PanelVSyncWidth     		5
#define PanelVSyncBackPorch   	33

#define PanelHStart     (PanelHSyncWidth+PanelHSyncBackPorch)
#define PanelVStart     (PanelVSyncWidth+PanelVSyncBackPorch)
#define PanelWidth      2560
#define PanelHeight     1440

#define PanelHTotal     (730*4)
#define PanelVTotal     1506 //1481

#define PanelMaxHTotal      	(780*4)//2720
#define PanelMinHTotal       (688*4)+40//2720

#define PanelMaxVTotal      	1540//1481
#define PanelMinVTotal       	1478//1481


#define PanelVsyncFreq      60//60

#else

#define PanelOnTiming1      40 //80// time between panel & data while turn on power
#define PanelOnTiming2      400 // time between data & back light while turn on power
#define PanelOffTiming1     250 // time between back light & data while turn off power
#define PanelOffTiming2     1 // time between data & panel while turn off power

#define PanelHSyncWidth     32
#define PanelHSyncBackPorch   80

#define PanelVSyncWidth     5
#define PanelVSyncBackPorch   33

#define PanelHStart     (PanelHSyncWidth+PanelHSyncBackPorch)
#define PanelVStart     (PanelVSyncWidth+PanelVSyncBackPorch)
#define PanelWidth      2560
#define PanelHeight     1440
#define PanelHTotal     2720
#define PanelVTotal     1481

#define PanelMaxHTotal      2728//2720
#define PanelMinHTotal       2712//2720

#define PanelMaxVTotal      1483//1481
#define PanelMinVTotal       1479//1481
#define PanelVsyncFreq      60


#endif





#define Panel_VTT_3D_120    PanelVTotal
#define Panel_VTT_3D_110    PanelVTotal
#define Panel_VTT_3D_100    PanelVTotal
#define Panel_VTT_3D            PanelVTotal

#define PanelDCLK           	     (((DWORD)PanelHTotal*PanelVTotal*PanelVsyncFreq)/1000000)
#define PanelMaxDCLK           400//170
#define PanelMinDCLK            200


//#define ENABLE_WHITE_PATTEN
//=================================================================
// TCON  setting for LVDS
//PVS / FSYNC
#define GPO9_VStart     0x7
#define GPO9_VEnd       0x705
#define GPO9_HStart     0x0
#define GPO9_HEnd       0x0
#define GPO9_Control        0x7

//HSYNC
#define GPOA_VStart     0x006
#define GPOA_VEnd       0x408
#define GPOA_HStart     0
#define GPOA_HEnd       0
#define GPOA_Control        0x4

//I_Gen_Tuning CH Source Select
#define I_Gen_CH  CH3_CLK

//I_Gen_Tuning Target Select
//#define Target_Select Target_350mv   //20111103 xm, ASUS VG278H_1Chip,
#define ENABLE_LOAD_OVD_2nd_TBL	0
//=================================================================
//Def. ColorTemp.





