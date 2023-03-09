
#if	(MS_PM)

#ifndef MS_PM_H
#define MS_PM_H

#ifdef _MS_PM_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif


//#if MainBoardType==MainBoard_MST125B
//#include "TSUMU_DEMO_PMSET.h"
//#elif  MainBoardType==MainBoard_5281_M0A
//#include "OTS_VS230PGLW_PMSET.h"
#if MainBoardType == MainBorad_JRY_L58CDT9_GV2||MainBoard_JRY_L58CDT9_NV1||MainBoardType == MainBoard_W58CDT9_JV1||MainBoardType == MainBoard_JRY_W58CDT9_GV3||MainBoardType == MainBoard_JRY_L58CDT9_EV1||MainBoardType == MainBoard_JRY_L58CDT9_PV1||MainBoardType == MainBoard_W38CDMT9_DV2||MainBoardType == MainBoard_W38CDMT9_DV2|| MainBoardType == MainBoard_JRY_L58CDT9_BV2|| MainBoardType == MainBoard_JRY_W58CDT9_AV6|| MainBoardType==MainBoard_JRY_W58CDT9_AV7
#include "TSUMC_DEMO_PMSET.h"
#elif (CHIP_ID== CHIP_TSUMF||MainBoardType == MainBoard_XY_W58CDT9_AV7||MainBoardType == MainBoard_JRY_L5AFHD_EV1||MainBoardType == MainBorad_JRY_L5AFHD_FV1)
#include "TSUMC_DEMO_PMSET.h"
#elif (CHIP_ID ==CHIP_TSUMD||MainBoardType == MainBoard_TSUMP387MT9_1||MainBoardType == MainBoard_L38CDMT9_GV1||MainBoardType==MainBoard_W38CDMT9_QV1||MainBoardType == MainBoard_W587HT9_DV1||MainBoardType ==MainBoard_WO587HT9_JV1||MainBoardType == MainBoard_W38CDMT9_PV1||(MainBoardType == MainBoard_JRY_L58CDT9_LV1))
#include "TSUMD_DEMO_PMSET.h"
#elif CHIP_ID ==CHIP_TSUM9||MainBoardType == MainBoard_TSUMP58CG_1
#include "TSUM9_DEMO_PMSET.h"
#elif MainBoardType == MainBoard_JRY_O58FHG_CV1||MainBoardType == MainBoard_JRY_O58FHG_BV1||MainBoardType == MainBoard_TSUMO58FDT9_1
#include "BD_JRY_O587HT9_M0A_PMSET.h"
#elif MainBoardType == MainBoard_JRY_W58VHN_NV1||MainBoardType == MainBoard_JRY_L58VHN_GV3
#include "BD_JRY_W58VHN_NV1_PMSET.h"
#elif MainBoardType == MainBoard_JRY_WQ570  ||MainBoardType == MainBoard_JRY_L9BQHD_AV1  ||MainBoardType == MainBoard_JRY_F9BQHD_BV1
#include "TSUMU_BD8395_PMSET.h"
#elif MainBoardType == MainBoard_JRY_WQ570_EV1||MainBoardType == MainBoard_MST9570S_DEMO|| MainBoardType == MainBoard_JRY_W8787_BV1||MainBoardType ==MainBoard_JRY_L8787_BV1   //20170731
#include "TSUMU_DEMO_PMSET.h"
#else
#message "please implement PMSET for new board"
#endif

#if !PM_POWERSAVING_WAKEUP_SOG		//2 Jemery 181123 add
#undef PM_POWERSAVING_WAKEUP_SOG
#define PM_POWERSAVING_WAKEUP_SOG	1
#endif





typedef enum
{
	ePM_ENTER_PM = 0,
	ePM_EXIT_PM = 1,
	ePM_WAIT_EVENT = 2,
	ePM_IDLE = 3
} ePM_State;

typedef enum
{
	ePMSTS_NON,
	ePMSTS_VGA_ACT,
	#if( PM_SUPPORT_WAKEUP_DVI )
	ePMSTS_DVI_0_ACT,
	ePMSTS_DVI_1_ACT,
	#endif
	ePMSTS_SAR_ACT,
	ePMSTS_GPIO_ACT,
	ePMSTS_MCCS04_ACT,
	ePMSTS_MCCS05_ACT,
	ePMSTS_MCCS01_ACT,
	ePMSTS_CEC_ACT,
	ePMSTS_FORCE_ON,
	#if( PM_SUPPORT_WAKEUP_DP )
	ePMSTS_DP_ACT,
	#endif
	#if(PM_POWERkEY_GPIOSAR)
	ePMSTS_SRAPOWER_ACT,
	#endif
	#if (PM_POWERkEY_GETVALUE)
	ePMSTS_POWERGPIO_ACT,
	#endif
	#if(PM_CABLE_DETECT_USE_SAR)
	ePMSTS_CABLESAR_ACT,
	#endif
	ePMSTS_ITE_POWER_KEY_ACT,
	ePMSTS_ITE_SOURCE_KEY_ACT,
	#if  (FEnterFunction==FEnter_POWER_MENU) ||(FEnterFunction==FEnter_POWER_EXIT)
	ePMSTS_ITE_FACTORY_KEY_ACT,	//120523 Modify
	#endif
	ePMSTS_ITE_OSDLOCK_KEY_ACT,	//120524 Modify
	ePMSTS_MHL_SOURCE_ACT,
	ePMSTS_GPIO_POWER_KEY_ACT,
	#if ENABLE_MHL
	ePMSTS_MHL_ACT,
	#endif
	#if ENABLE_ANDROID_IR	//131008 Modify
	ePMSTS_IR_PowerKEY_ACT,
	#endif
	ePMSTS_INVAID
} ePMStatus;

#if ENABLE_MHL || ENABLE_DP_INPUT
#define SET_PM_WAKEUP_NON()      {ucWakeupStatus = ePMSTS_NON;}
#endif

#if ENABLE_MHL
#define PM_WAKEUP_FROM_MHL      (ucWakeupStatus == ePMSTS_MHL_ACT)
#endif

#if ENABLE_DP_INPUT
#define PM_WAKEUP_FROM_DP      (ucWakeupStatus == ePMSTS_DP_ACT)
#endif

#define ConvPercent(x)  ( (WORD)(x)*255/100)

// ACDET low voltage threshold // 0x66
#define Low_Volt_1_20 0x00<<2
#define Low_Volt_1_25 0x01<<2
#define Low_Volt_1_15 0x10<<2
#define Low_Volt_1_10 0x11<<2
// ACDET high voltage threshold // 0x66
#define High_Volt_1_40 0x00
#define High_Volt_1_45 0x01
#define High_Volt_1_50 0x10
#define High_Volt_1_55 0x11

//=============================
#define SAR_Ch          SAR2
//------------------------------------------------
#define SAR0     0
#define SAR1     1
#define SAR2     2
#define SAR3     3
//------------------------------------------------
#define SAR_KEY_TH      0x30

//=============================

#define LEDPWM              LEDPWM1
#define LED_PWM_EN      LED_PWM_Amber

#define PWMDUTY_Val     ConvPercent(2) //%
#define PWMDIV_Val          0xFF // 97.16Hz
//=============================
//#define SAR1   BIT0
//#define SAR2   BIT1
//#define SARALL SAR2|SAR1
//=============================
#define LEDPWM0 0
#define LEDPWM1 1
#define LEDPWM2 2
#define LEDPWM3 3
#define LED_PWM_SEL_P07     LEDPWM<<5
#define LED_PWM_SEL_P06     LEDPWM<<3  // P06 & P15 as same
#define LED_PWM_SEL     LED_PWM_SEL_P07|LED_PWM_SEL_P06

// PWM0 0xC2,0xC3 ; PWM1 0xC4,0xC5
#if (LEDPWM==LEDPWM1)
#define PWMDIV      0xC4
#define PWMDUTY   0xC5
#elif (LEDPWM==LEDPWM0)
#define PWMDIV      0xC2
#define PWMDUTY   0xC3
#elif (LEDPWM==LEDPWM2)
#define PWMDIV      0xC6
#define PWMDUTY   0xC7
#elif (LEDPWM==LEDPWM3)
#define PWMDIV      0xC6
#define PWMDUTY   0xC7
#endif
//=============================
#define LED_P07_EN            BIT1
#define LED_P06_EN            BIT0
#define LED_P15_EN            BIT0

#define LED_PWM_Green       LED_P06_EN
#define LED_PWM_Amber       LED_P07_EN



//**************************************************************************
//  RCOSC = XTAL * Counter / 512 => Counter = RCOSC *512/XTAL,
//  IF RCOSC=4M, Counter=143 =>8Fh
#if ENABLE_DEBUG
#define RCOSC_TARGET    143 //4MHz
#define RCOSC_CLK       4.0
#else
#define RCOSC_TARGET    143 //4MHz
#endif
//**************************************************************************

#define RCOSC       0
#define XTAL        1
#define XTALDIV2    2
#define XTALDIV4    3

//--------PM Option----------------
//#define PM_CLOCK                XTAL
#if PM_CLOCK==RCOSC
#define PM_TIMER_CLOCK_PERIOD (0x10000-265) //more precise
//#define PM_TIMER_CLOCK_PERIOD   (0x10000-((((unsigned long)14318*RCOSC_TARGET/512)*INT_PERIOD)/12))
#define PM_FORCE_DELAY_DIV      8
#define PM_DELAY4US_LOOP        1
#elif PM_CLOCK==XTAL
#define PM_TIMER_CLOCK_PERIOD   (0x10000-(((unsigned long)14318*INT_PERIOD)/12))
#define PM_FORCE_DELAY_DIV      2
#define PM_DELAY4US_LOOP        4
#elif PM_CLOCK==XTALDIV2
#define PM_TIMER_CLOCK_PERIOD   (0x10000-(((unsigned long)14318/2*INT_PERIOD)/12))
#define PM_FORCE_DELAY_DIV      4
#define PM_DELAY4US_LOOP        2
#elif PM_CLOCK==XTALDIV4
#define PM_TIMER_CLOCK_PERIOD   (0x10000-(((unsigned long)14318/4*INT_PERIOD)/12))
#define PM_FORCE_DELAY_DIV      8
#define PM_DELAY4US_LOOP        1
#endif



INTERFACE BYTE xdata Check, Check1;
#if ENABLE_DP_INPUT
extern bit g_bDoDPInit;
#endif
//extern bit g_bMcuPMClock;

INTERFACE Bool msPM_IsState_IDLE(void);

// setting configuration meta data
INTERFACE void msPM_Init(void);
INTERFACE void msPM_SetFlag_Standby(void);
INTERFACE void msPM_SetFlag_PMDCoff(void);
#if 0
INTERFACE void msPM_InputForceMode();
INTERFACE void msPM_SetFlag_Standby_ForceVGA(void);
INTERFACE void msPM_SetFlag_Standby_ForceDVI0(void);
INTERFACE void msPM_SetFlag_Standby_ForceDVI1(void);
INTERFACE void msPM_SetFlag_Standby_ForceAllPort(void);
#endif


#if 0
INTERFACE void msPM_PowerDownMacro(void);
INTERFACE Bool msPM_GetPMStatus(void);
INTERFACE void msPM_SetPMClock(void);
INTERFACE void msPM_ClearStatus(Bool bResetPM);
INTERFACE void msPM_PassWord(Bool bEnable);
#endif
INTERFACE void msPM_Handler(void);
INTERFACE void msPM_WaitingEventActivity(void);
//INTERFACE void msPM_InitWaitingEventActivity(void);
INTERFACE void msPM_PMWakeupInit(void);

#if 0
INTERFACE BYTE msPM_Reset(void);
#endif

INTERFACE Bool msPM_StartRCOSCCal(void);


INTERFACE void msPM_SetPMMode(void);
INTERFACE void msPM_WaitingEvent(void);
INTERFACE Bool msPM_Checkagain(void);

INTERFACE void msPM_InterruptEnable(Bool benable);


#if  0
INTERFACE void msPM_SetConfigurationMeta(
    BOOL bHW_enable, BOOL bMCUSleep, BOOL bXTALOn_enable, BOOL bCorePWOn_enable,
    BOOL bHVSync_enable, BOOL bSOG_enable, BOOL bGPIO_enable,
    BOOL bSAR_enable, BOOL bMCCS_enable, BOOL bEDID_enable,
    #if( PM_SUPPORT_WAKEUP_DVI )
    BOOL bDVI_enable,
    #endif
    #if( PM_SUPPORT_WAKEUP_DP )
    BOOL bDP_enable,
    #endif
    #if( PM_SUPPORT_AC2DC )
    BOOL bACtoDC_enable,
    #endif
    BYTE ePMDVImode, BYTE ePMSARmode, BYTE ePMPMCLK, BYTE ePMLiveCLK);
#endif
INTERFACE void msPM_Functions(void);
//INTERFACE void msPM_ForceExit(void);
INTERFACE void msPM_ForceEnter(void);

INTERFACE void msPM_EnableSOGDetect(Bool bEnable);
INTERFACE void msPM_EnableSARDetect(Bool bEnable);
INTERFACE void msPM_EnableGPIODetect(Bool bEnable);
INTERFACE void msPM_EnableMCCSDetect(Bool bEnable);
INTERFACE void msPM_EnableHVSyncDetect(Bool bEnable);
#if( PM_SUPPORT_AC2DC )
INTERFACE void msPM_EnableAC2DC(Bool bEnable);
#endif//end of #if( PM_SUPPORT_AC2DC )
#if( PM_SUPPORT_WAKEUP_DVI )
INTERFACE void msPM_EnableDVIDetect(Bool bEnable);
//end of #if( PM_SUPPORT_WAKEUP_DVI )

//function for time sharing feature
INTERFACE void msPM_EnableDVIClockAmp (Bool bEnable);
#endif

INTERFACE void msPM_OutputTriState(void);
//void msPM_SetupWakeUpFunc(void);
//void msPM_printConfiguration(void);

INTERFACE void msPM_MCCSReset(void);
INTERFACE Bool DDCCI_CheckDMPSON(void);


#undef INTERFACE
#endif

#endif

