#ifndef __AUOM240HW01V80B_120HZ_H
#define __AUOM240HW01V80B_120HZ_H

#define PanelName   "M240HW01V80B"

#define _PanelColorDepth				bPanelColorDepth//6 Bit Panel->0		8 Bit Panel->bPanelColorDepth
#define _ChangeModePanelVddOff		bChangeModePanelVddOff
#define _PanelOutputControl1            0x10//Scaler Bank 0x42 Setting
#define _PanelOutputControl2			( (PanelDualPort &BIT0) | (PanelSwapPort &BIT1))//Scaler Bank 0x43 Setting // Rosen 3043h Setting 2011.9.16 cc add
#define _PanelOSContol              0x80//Scaler Bank 0xF2 Setting
#define _PanelODRriving             0x55//Scaler Bank 0xF5 Setting
#define _DefBurstModeFreq           250//Hz
#define _DefMinDutyValue                0x01
#define _DefMaxDutyValue            0xFF
#define _STEPL                      0x44
#define _STEPH                      0x00
#define _SPANL                      0xCC
#define _SPANH                      0x01

#define PanelDither         8
#define PanelTTL            0 //
#define PanelTCON           0
#define PanelLVDS           1 //  0

#define PANEL_SWAP_AB_PORT  0 //0: non-swap, 0xFF: AB swap
#define PANEL_SWAP_CD_PORT  0//0: non-swap ,0xFF: CD swap

#define LVDS_CH_A_SWAP              LVDS_CH_A
#define LVDS_CH_B_SWAP              LVDS_CH_B
#define LVDS_CH_C_SWAP              LVDS_CH_C
#define LVDS_CH_D_SWAP              LVDS_CH_D

#define PAIR_SWAP_B         0 

#define ShortLineCheck      FUNC_ENABLE
#define LVDS_TIMode         FUNC_ENABLE  //Thine mode:disable TI mode

#define LVDS_TI_BitModeSel  LVDS_TI_8BIT

#define PanelDualPort       0
#define PANEL_QUAD_PORT       1
#define PanelSwapPort       0
#define PanelSwapOddML      0
#define PanelSwapEvenML     0
#define PanelSwapOddRB      0
#define PanelSwapEvenRB     0
#define PanelSwapMLSB       0
#define PanelSwapPN         0//FUNC_ENABLE

//    panel output type select
#define PANEL_OUTPUT_FMT_3D_LR      1//0
#define PANEL_OUTPUT_FMT_3D_CB      0

#define PanelDClkDelay      FUNC_DISABLE
#define PanelInvDE          FUNC_DISABLE
#define PanelInvDClk        FUNC_DISABLE
#define PanelInvHSync       FUNC_DISABLE
#define PanelInvVSync       FUNC_DISABLE

// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent    1 // Dclk current
#define PanelDECurrent      1 // DE signal current
#define PanelOddDataCurrent 1 // Odd data current
#define PanelEvenDataCurrent    1 // Even data current

#define _PanelOnTiming1      40 // time between panel & data while turn on power        //2011018 Xm, ASUS VG278H_1Chip, 
#define _PanelOnTiming2      600 // time between data & back light while turn on power//2011018 Xm, ASUS VG278H_1Chip, 
#define _PanelOffTiming1     250 // time between back light & data while turn off power  //2011018 Xm, ASUS VG278H_1Chip, 
#define _PanelOffTiming2     60 // time between data & panel while turn off power       //2011018 Xm, ASUS VG278H_1Chip,
#define PanelOffOnDelay		1100

#define _PanelHSyncWidth     6
#define _PanelHSyncBackPorch 20

#define _PanelVSyncWidth     2
#define _PanelVSyncBackPorch 12

#define _PanelHStart         (PanelHSyncWidth+PanelHSyncBackPorch)
#define _PanelVStart         (PanelVSyncWidth+PanelVSyncBackPorch)
#define _PanelWidth          1920
#define _PanelHeight         1080

#if ENABLE_DUAL_LINK//20130412 follow PHL for 144hz issue.
#define _PanelHTotal         (_PanelMinHTotal+20)
#else
#define _PanelHTotal         2240
#endif
#define _PanelVTotal         1130 
#define _PanelMaxHTotal      2400
#define _PanelMinHTotal      2040
#define _PanelMaxVTotal      1715
#define _PanelMinVTotal      1088
#define PanelVsyncFreq      120
#define PanelMaxVsyncFreq    1500//  (1200+13)
#define PanelMaxVfreq     1500 //request by TPV for support Dual Link 144M (1200+13)

#define Panel_VTT_3D_120    1524//1480//1524    //20111114 xm, ASUS VG278H_1Chip, A512  //2011024 Xm, ASUS VG278H_1Chip, A039
#define Panel_VTT_3D_110    1663//1616//1663    //20111114 xm, ASUS VG278H_1Chip, A512   //2011024 Xm, ASUS VG278H_1Chip, A039
#define Panel_VTT_3D_100    1829//1776//1829    //20111114 xm, ASUS VG278H_1Chip, A512  //2011024 Xm, ASUS VG278H_1Chip, A039
#define Panel_VTT_3D        Panel_VTT_3D_120

#define _PanelDCLK           (((DWORD)PanelHTotal*PanelVTotal*PanelVsyncFreq)/1000000)
#define _PanelMaxDCLK        385
#define _PanelMinDCLK        132//130  follow BJ 20130418      

#define _PanelLVDSSwing2			1// 0:242.37mV    1:339.33mV    2:387mV    3:169.67mV    //For TSUMXXNXX&TSUMXXQXX type ic auto tune target voltage
#define _PanelLVDSSwing1			0x15// 283mV //For old chip
#define _PanelLVDSSwing				(_PanelLVDSSwing1|_PanelLVDSSwing2<<6)


//=================================================================
// Not Used
#if 0
// backlight voltage
#define PNL_PWM_INVERT          1

#define USE_FRAME_PLL               1

#define PANEL_DITHER                0 // 8/6 bits panel
#define PANEL_MONO                  0
#define PANEL_MONO_MONO_MODE        0 //_PNL_FUNC_EN_

#define PANEL_RSDS                  0
#define PANEL_MINI_LVDS_5PAIR       0
#define PANEL_MINI_LVDS_6PAIR       0
#define PANEL_MINI_LVDS_6PAIR_TV    0

#endif // Not Used

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
//#define I_Gen_CH  CH3_CLK

//I_Gen_Tuning Target Select
//#define Target_Select Target_350mv   //20111103 xm, ASUS VG278H_1Chip, 

#endif

