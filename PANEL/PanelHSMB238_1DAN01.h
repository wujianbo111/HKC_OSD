
#ifndef _Panel238W_M238DAN01_1_
#define _Panel238W_M238DAN01_1_
#if ModelName==TOP_HF_B2430M
#define PanelName   "HSMB238-1DAN01"
#elif ModelName==HF_ENVISION_H2418WQ
#define PanelName   "HSMF238-2DAN01"
#else
#define PanelName   "HSMF238"
#endif
#define PanelDither     0

#define PanelTTL        0
#define PanelTCON       0
#define PanelLVDS       0xFF
#define PanelRSDS       0
#define PanelMiniLVDS     0
#define PanelMiniLVDS1     0
#define PanelMiniLVDS2     0
#if MainBoardType == MainBoard_JRY_WQ570		///1A2H1DP
#define LVDS_CH_A_SWAP            LVDS_CH_B//  LVDS_CH_A
#define LVDS_CH_B_SWAP      	     LVDS_CH_D  //110427
#define LVDS_CH_C_SWAP      	     LVDS_CH_A//	LVDS_CH_B///0//110511_03  LVDS_CH_C  //110427
#define LVDS_CH_D_SWAP            LVDS_CH_C//	LVDS_CH_D
#elif MainBoardType == MainBoard_JRY_WQ570_EV1			///1A1H
#define LVDS_CH_A_SWAP            LVDS_CH_A//  LVDS_CH_A
#define LVDS_CH_B_SWAP      	     LVDS_CH_C  //110427
#define LVDS_CH_C_SWAP      	     LVDS_CH_B//	LVDS_CH_B///0//110511_03  LVDS_CH_C  //110427
#define LVDS_CH_D_SWAP            LVDS_CH_D//	LVDS_CH_D
#else
#define LVDS_CH_A_SWAP            LVDS_CH_A//  LVDS_CH_A
#define LVDS_CH_B_SWAP      	     LVDS_CH_C  //110427
#define LVDS_CH_C_SWAP      	     LVDS_CH_B//	LVDS_CH_B///0//110511_03  LVDS_CH_C  //110427
#define LVDS_CH_D_SWAP            LVDS_CH_D//	LVDS_CH_D
#endif
#define PANEL_SWAP_AB_PORT      1 //0: non-swap, 0xFF: AB swap
#define PANEL_SWAP_CD_PORT      1 //0: non-swap ,0xFF: CD swap

#define PANEL_SWAP_PN                     0

//    panel output type select
#define PANEL_3D_PASSIVE            	0
#define PANEL_3D_PASSIVE_4M         	0
#define PANEL_OUTPUT_FMT_3D_LR      0//FUNC_ENABLE
#define PANEL_OUTPUT_FMT_3D_CB      0

#define LVDS_TI_BitModeSel     LVDS_TI_8BIT// LVDS_TI_10BIT

#define PANEL_QUAD_PORT      1
#define LVDS_TIMode     		0xFF///X00,¹«Ë¾27  0xff  :ºèºº32

#define PanelDualPort       	0//0xFF
#define PanelSwapPort     		0//  0xFF
#define PanelSwapOddML      	0
#define PanelSwapEvenML     	0
#define PanelSwapOddRB      	0//xFF
#define PanelSwapEvenRB     	0//xFF
#define PanelSwapMLSB       	0
#define PanelSwapLCPS       	0

#define PanelDClkDelay      	0
#define PanelInvDE      		0
#define PanelInvDClk        		0
#define PanelInvHSync       	0
#define PanelInvVSync       	0
// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent		1 // Dclk current
#define PanelDECurrent		1 // DE signal current
#define PanelOddDataCurrent	1 // Odd data current
#define PanelEvenDataCurrent	1 // Even data current

#define PanelOnTiming1		50   //time between panel & data while turn on power
#define PanelOnTiming2		550 //time between data & back light while turn on power 
#define PanelOffTiming1		300 //time between back light & data while turn off power 
#define PanelOffTiming2		20   //time between data & panel while turn off power 


#define PanelHSyncWidth     		32
#define PanelHSyncBackPorch   	80

#define PanelVSyncWidth     		5
#define PanelVSyncBackPorch   	33

#define PanelHStart     (PanelHSyncWidth+PanelHSyncBackPorch)
#define PanelVStart     (PanelVSyncWidth+PanelVSyncBackPorch)

#define PanelWidth      2560
#define PanelHeight     1440

#define PanelHTotal     (680*4)
#define PanelVTotal     1518 //1481

#define PanelMaxHTotal      (1023*4)//2720
#define PanelMinHTotal       (679*4)+40//2720

#define PanelMaxVTotal      2553//1481
#define PanelMinVTotal       1452//1481
#define PanelVsyncFreq      60

#define PanelDCLK           		(60*4)
#define PanelMaxDCLK		(83*4)
#define PanelMinDCLK			(48*4)

// 110929 Rick add
#define PanelVfreq          	(600)
#define PanelMaxVfreq   	(760) // 144Hz
#define PanelMinVfreq   	(480) // 50Hz

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

//=================================================================
// Color Temp
//111103 Rick modified
#define DISABLE_SHORT_FRAME_TUNE     1

#endif

