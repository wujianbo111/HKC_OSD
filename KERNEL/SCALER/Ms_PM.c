///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    Ms_PM.c
/// @author MStar Semiconductor Inc.
/// @brief  PM Function
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#define _MS_PM_C_
#include "board.h"
#include <math.h>
#include <string.h>
#include "types.h"
//#include "mode.h"
#include "common.h"
#include "UserPrefDef.h"
#include "global.h"
#include "Misc.h"
#include "ms_reg.h"
#include "ms_rwreg.h"
#include "Debug.h"
#include "menu.h"
#include "userpref.h"
#include "Power.h"
#include "DDC2Bi.h"
#include "Ms_PM.h"
#include "MenuDef.h"
#include "MenuFunc.h"
#include "Mcu.h"
#include "Mstar.h"
#include "Detect.h"
#include "Keypad.h"     // Provides: Key_GetKeypadStatus()
#include "KeypadDef.h"  // Provides: KeypadMask
#include "GPIO_Def.h"
#if ENABLE_DP_INPUT
#include "drvDPRxApp.h"
#endif
#if ENABLE_DisplayPortTX
#include "drvDPTxApp.h"
#endif
#if ENABLE_ANDROID_IR	//131008 Modify
#include "drv_ir.h"
#endif

#if	(MS_PM)
#if (FRAME_BFF_SEL == FRAME_BUFFER) || ENABLE_RTE
extern  Bool msMemoryBist(void);
#endif
extern void msDVISetMux( InputPortType inport );
extern void msPM_ClearStatus(Bool bResetPM);

extern BYTE Key_GetKeypadStatus( void );

extern Bool ExecuteKeyEvent(MenuItemActionType menuAction);
extern void Main_SlowTimerHandler(void);

#if Enable_CheckVcc5V
extern Bool CheckVCC5V ( void );
#endif

#if  ENABLE_DP_INPUT
#if  DPENABLEMCCS
extern void DDC2BI_DP(void);
#if ((CHIP_ID == CHIP_TSUMC)||(CHIP_ID == CHIP_TSUMD)||(CHIP_ID == CHIP_TSUM9)||(CHIP_ID == CHIP_TSUMF))
#if D2B_XShared_DDCBuffer
extern BYTE *DDCBuffer;
#else
extern BYTE xdata DDCBuffer[DDC_BUFFER_LENGTH];
#endif
#else
extern BYTE xdata DDCBuffer[DDC_BUFFER_LENGTH];
#endif
#endif
#endif


extern void mdrv_mhl_RtermControlHWMode(Bool bFlag);//130703 nick
//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define PM_DEBUG    0
#if ENABLE_DEBUG&&PM_DEBUG
#define PM_printData(str, value)   printData(str, value)
#define PM_printMsg(str)           printMsg(str)
#else
#define PM_printData(str, value)
#define PM_printMsg(str)
#endif

#define XBYTE             ((unsigned char volatile xdata *) 0)


//--------PM Option----------------
/*Choice MCU clock when enter into PM_MODE*/
extern BYTE xdata MenuPageIndex ;

extern BYTE xdata MenuItemIndex ;


//---------------------------------
#define VCP_SET             0x03
#define VCP_DPMS            0xD6
#define VCP_DPMS_ON         0x01
//-------------------------------------------------------------------------------------------------
#define IS_SOURCE_AUTOSWITCH() (TRUE)
#define IS_SOURCE_VGA()        (FALSE) //(UserPreference.InputSync == ANALOG)
#define IS_SOURCE_DVI0()       (FALSE) //(UserPreference.InputSync == DIGITAL)
#define IS_SOURCE_DVI1()       (FALSE) //(UserPreference.InputSync == DIGITAL2)

//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------

typedef enum
{
	ePM_POWERON,
	ePM_STANDBY,
	ePM_POWEROFF,

	ePM_INVAILD
} ePM_Mode;


typedef enum
{
	ePMDVI_DVI0,
	ePMDVI_DVI1,
	ePMDVI_DVI0_DVI1,

	ePMDVI_INVALID
} ePM_DVI;

typedef enum
{
	ePMGPIO04_DectDVI5V,
	ePMGPIO02_DectDVI5V,
	ePMGPIO01_DectDVI5V,
	ePMGPIO00_DectDVI5V,
	ePMDVI5V_INVALID
} ePM_DVI5V;

typedef enum
{
	ePMSAR_SAR0 = BIT0,
	ePMSAR_SAR1 = BIT1,
	ePMSAR_SAR2 = BIT2,
	ePMSAR_SAR3 = BIT3,
	ePMSAR_SAR12 = BIT1 | BIT2,
	ePMSAR_SAR123 = BIT1 | BIT2 | BIT3,
	ePMSAR_SAR01 = BIT0 | BIT1,
	ePMSAR_SAR012 = BIT0 | BIT1 | BIT2,
	ePMSAR_INVALID
} ePM_SAR;

#if 0//_OLD_PM_FLOW
typedef enum
{
	ePM_ENTER_PM,
	ePM_IDLE,
	ePM_EXIT_PM,
	ePM_WAIT_EVENT,
} ePM_State;

typedef struct
{
	BYTE bSpecialEvent_1: 1;
	BYTE bSpecialEvent_2: 1;

} sPM_WakeUp_Check;
#endif

typedef enum
{
	ePM_CLK_RCOSC,
	ePM_CLK_XTAL,

	ePMCLK_INVALID
} ePM_CLK;

typedef struct
{
	BYTE bHVSync_enable: 1;
	BYTE bSOG_enable: 1;
	BYTE bGPIO_enable: 1;
	BYTE bSAR_enable: 1;
	BYTE bMCCS_enable: 1;
	BYTE bEDID_enable: 1;
	#if( PM_SUPPORT_WAKEUP_DVI )
	BYTE bDVI_enable: 1;
	#endif  // end of #if( PM_SUPPORT_WAKEUP_DVI )
	#if( PM_SUPPORT_WAKEUP_DP )&&(ENABLE_DP_INPUT)
	BYTE bDP_enable: 1;
	#endif  // end of #if( PM_SUPPORT_WAKEUP_DP )
	#if( PM_SUPPORT_AC2DC )
	BYTE bACtoDC_enable: 1;
	#endif  // end of #if( PM_SUPPORT_AC2DC )
	BYTE bMCUSleep: 1;
	ePM_DVI ePMDVImode;

	ePM_SAR ePMSARmode;

} sPM_Config;

typedef struct
{
	WORD wPMGPIOWakeupSta;

} sPM_WakeUp_Check;
typedef struct
{
	BYTE ucPMMode;
	ePM_State ePMState;
	sPM_Config  sPMConfig;
	sPM_WakeUp_Check sPMWakeUpCheck;
	#if CABLE_DETECT_VGA_USE_SAR||CABLE_DETECT_VGA_USE_SAR
	BYTE bCABLE_SAR_VALUE;
	#endif
} sPM_Info;

XDATA sPM_Info  sPMInfo;
XDATA ePMStatus ucWakeupStatus;

//-------------------------------------------------------------------------------------------------
//  External Variables
//-------------------------------------------------------------------------------------------------
#if !ENABLE_DEBUG
extern BYTE xdata rxIndex;
#if (CHIP_ID==CHIP_TSUMC) || CHIP_ID==CHIP_TSUMD||CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF
#if D2B_XShared_DDCBuffer
extern BYTE *DDCBuffer;
#else
extern BYTE xdata DDCBuffer[];
#endif
#else
extern BYTE xdata DDCBuffer[];
#endif
#endif

#ifndef PM_SUPPORT_ADC_TIME_SHARE
#define PM_SUPPORT_ADC_TIME_SHARE  0
#endif

Bool msPM_IsState_IDLE(void)
{
	if(sPMInfo.ePMState == ePM_IDLE)
		return TRUE;
	return FALSE;
}

//**************************************************************************
//  [Function Name]:
//                  msPM_Init()
//  [Description]
//                  msPM_Init
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void  msPM_Init(void)
{
	sPMInfo.sPMConfig.bHVSync_enable = 0;
	#if( PM_SUPPORT_WAKEUP_DVI )
	sPMInfo.sPMConfig.bDVI_enable = 0;
	#endif  // end of #if( PM_SUPPORT_WAKEUP_DVI )
	#if( PM_SUPPORT_WAKEUP_DP && ENABLE_DP_INPUT)
	sPMInfo.sPMConfig.bDP_enable = 0;
	#endif
	sPMInfo.sPMConfig.bSOG_enable = 0;
	sPMInfo.sPMConfig.bSAR_enable = 0;
	sPMInfo.sPMConfig.bGPIO_enable = 0;
	sPMInfo.sPMConfig.bMCCS_enable = 0;
	#if( PM_SUPPORT_AC2DC )
	sPMInfo.sPMConfig.bACtoDC_enable = 0;
	#endif  // end of #if( PM_SUPPORT_AC2DC )
	sPMInfo.sPMConfig.bMCUSleep = 0;
	sPMInfo.ucPMMode = ePM_POWERON;
	sPMInfo.ePMState = ePM_IDLE;
	sPMInfo.sPMWakeUpCheck.wPMGPIOWakeupSta = msRead2Byte(REG_PM_64)&EN_GPIO_DET_MASK;
}
//**************************************************************************
//  [Function Name]:
//                  msPM_SetPMSandby()
//  [Description]
//                  msPM_SetPMSandby_ForceDVI0
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msPM_SetFlag_Standby(void)
{
	#if TMDS_SYNC_RECHECK
	if(TMDS_INPUT_WITHOUT_HV_SYNC())
	{
		return;
	}
	#endif
	#if (CHIP_ID==CHIP_TSUMC || CHIP_ID==CHIP_TSUMD||CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)//130607 nick
	ComboInputControl(COMBO_INPUT_POWERSAVING);
	#endif
	//PM_printMsg(" msPM_SetFlag_Standby");
	#if (INPUT_TYPE != INPUT_2H) && (INPUT_TYPE != INPUT_1H)&&(INPUT_TYPE != INPUT_1D1H1DP)
	sPMInfo.sPMConfig.bHVSync_enable = 1;
	#else
	sPMInfo.sPMConfig.bHVSync_enable = 0;
	#endif
	#if( PM_SUPPORT_WAKEUP_DVI )
	#if Dual
	sPMInfo.sPMConfig.bDVI_enable = 1;
	#else
	#if (INPUT_TYPE == INPUT_1A)
	sPMInfo.sPMConfig.bDVI_enable = 0;
	#else
	sPMInfo.sPMConfig.bDVI_enable = 1;
	#endif
	#endif
	#endif  // end of #if( PM_SUPPORT_WAKEUP_DVI )
	#if( PM_SUPPORT_WAKEUP_DP && ENABLE_DP_INPUT)
	sPMInfo.sPMConfig.bDP_enable = 1;
	#endif  // end of #if( PM_SUPPORT_WAKEUP_DP )
	sPMInfo.sPMConfig.bSOG_enable = PM_POWERSAVING_WAKEUP_SOG;
	sPMInfo.sPMConfig.bSAR_enable = PM_POWERSAVING_WAKEUP_SAR;
	sPMInfo.sPMConfig.bGPIO_enable = PM_POWERSAVING_WAKEUP_GPIO;
	sPMInfo.sPMConfig.bMCCS_enable = PM_POWERSAVING_WAKEUP_MCCS;
	#if( PM_SUPPORT_AC2DC )
	sPMInfo.sPMConfig.bACtoDC_enable = 0;
	#endif  // end of #if( PM_SUPPORT_AC2DC )
	sPMInfo.sPMConfig.bMCUSleep = 0;
	#if ((CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)&&ENABLE_CABLE_5V_EDID)
	sPMInfo.sPMConfig.bEDID_enable = 1;
	#else
	sPMInfo.sPMConfig.bEDID_enable = 0;
	#endif
	sPMInfo.sPMConfig.ePMDVImode = ePMDVI_DVI0;
	sPMInfo.sPMConfig.ePMSARmode = ePMSAR_SAR0;
	sPMInfo.ucPMMode = ePM_STANDBY;//PM_POWERSAVING_SARmode;
	sPMInfo.ePMState = ePM_ENTER_PM;
//    PM_printData("\r\n==>sPMInfo.ePMState STD %d", sPMInfo.bCABLE_SAR_VALUE);
}


//**************************************************************************
//  [Function Name]:
//                  msPM_SetPMDCoff()
//  [Description]
//                  msPM_SetPMDCoff
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void  msPM_SetFlag_PMDCoff(void)
{
	#if (CHIP_ID==CHIP_TSUMC || CHIP_ID==CHIP_TSUMD||CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)//130607 nick
	ComboInputControl(COMBO_INPUT_OFF);
	#endif
	PM_printMsg(" msPM_SetFlag_PMDCoff");
	sPMInfo.sPMConfig.bHVSync_enable = 0;
	#if( PM_SUPPORT_WAKEUP_DVI )
	sPMInfo.sPMConfig.bDVI_enable = 0;
	#endif  // end of #if( PM_SUPPORT_WAKEUP_DVI )
	#if( PM_SUPPORT_WAKEUP_DP && ENABLE_DP_INPUT)
	sPMInfo.sPMConfig.bDP_enable = 0;
	#endif  // end of #if( PM_SUPPORT_WAKEUP_DP )
	sPMInfo.sPMConfig.bSOG_enable = PM_POWEROFF_WAKEUP_SOG;
	sPMInfo.sPMConfig.bSAR_enable = PM_POWEROFF_WAKEUP_SAR;
	sPMInfo.sPMConfig.bGPIO_enable = PM_POWEROFF_WAKEUP_GPIO;
	sPMInfo.sPMConfig.bMCCS_enable = PM_POWEROFF_WAKEUP_MCCS;
	#if( PM_SUPPORT_AC2DC )
	sPMInfo.sPMConfig.bACtoDC_enable = 0;
	#endif  // end of #if( PM_SUPPORT_AC2DC )
	sPMInfo.sPMConfig.bMCUSleep = 0;
	#if ((CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)&&ENABLE_CABLE_5V_EDID)
	sPMInfo.sPMConfig.bEDID_enable = 1;
	#else
	sPMInfo.sPMConfig.bEDID_enable = 0;
	#endif
	sPMInfo.sPMConfig.ePMDVImode = ePMDVI_DVI0;
	sPMInfo.sPMConfig.ePMSARmode = PM_POWEROFF_SARmode;
	sPMInfo.ucPMMode = ePM_POWEROFF;
	sPMInfo.ePMState = ePM_ENTER_PM;
	#if ENABLE_ANDROID_IR	//131008 Modify
	if(SOURCE_INPUT_IS_ANDROID())//20131022 Modify for IR only support Yun OS.
	{
		IR_Init();
		hw_ClrIRSwitch();
	}
	#endif
	PM_printData("\r\n sPMInfo.ePMState DCOFF %d", sPMInfo.ePMState);
}
//**************************************************************************
//  [Function Name]:
//                  msPM_EnableHVSyncDetect(BOOL bEnable)
//  [Description]
//                  msPM_EnableSyncDetect
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void
msPM_EnableHVSyncDetect(BOOL bEnable)
{
	if(bEnable)
	{
		msWriteByteMask(REG_PM_8E, 0x00, 0xF0);         // Sync clock not gating
		msWriteByteMask(REG_SYNC_DET, EN_SYNC_DET_SET, EN_SYNC_DET_MASK);
	}
	else
	{
		msWriteByteMask(REG_PM_8E, 0xB0, 0xF0);         // Sync clock gating
		msWriteByteMask(REG_SYNC_DET, 0, EN_SYNC_DET_MASK);
	}
}


//**************************************************************************
//  [Function Name]:
//                  msPM_EnableSOGDetect(BOOL bEnable)
//  [Description]
//                  Enable SOG Detect: need power ADC VREF & BANGAP
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void
msPM_EnableSOGDetect(BOOL bEnable)
{
	if(bEnable)
	{
		#if( !PM_SUPPORT_SOG_TIME_SHARE )
		msWriteBit(REG_PM_E9, FALSE, _BIT7);   // disable SoG time sharing option of VREF/BGAP to save power of SoG wakeup
		#else
		msWriteBit(REG_PM_E9, TRUE, _BIT7);   // enable SoG time sharing option of VREF/BGAP to save power of SoG wakeup
		msPM_EnableDVIClockAmp( TRUE );       // enable DVI clock amplifier control, because SoG time sharing requires DVI clock amplifier control.
		#endif
		msWriteByteMask(REG_ADC_ATOP_04_L, 0, (_BIT1 | _BIT0)); // power on ADC BGAP and VREF
		msWriteByteMask(REG_ADC_ATOP_04_H, 0, (_BIT2 | _BIT1)); // power on online SOG DAC and main
		msWriteByteMask(REG_SYNC_DET, EN_SOG_DET, EN_SOG_DET);
	}
	else
	{
		msWriteBit(REG_PM_E9, FALSE, _BIT7);   // disable SoG time sharing option of VREF/BGAP to save power of SoG wakeup
		msWriteByteMask(REG_ADC_ATOP_04_L, (_BIT1 | _BIT0), (_BIT1 | _BIT0)); // power down ADC BGAP and VREF
		msWriteByteMask(REG_ADC_ATOP_04_H, (_BIT2 | _BIT1), (_BIT2 | _BIT1)); // power down online SOG DAC and main
		msWriteByteMask(REG_SYNC_DET, 0, EN_SOG_DET);
	}
}


//**************************************************************************
//  [Function Name]:
//                  msPM_PassWord(BOOL bEnable)
//  [Description]
//                  input  the password for entering pm or turn off XTAL
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void
msPM_PassWord(BOOL bEnable)
{
	if(bEnable)
	{
		msWriteByte(REG_PM_87, 0x55);
		msWriteByte(REG_PM_88, 0xAA);
	}
	else
	{
		msWriteByte(REG_PM_87, 0x00);
		msWriteByte(REG_PM_88, 0x00);
	}
}

//**************************************************************************
//  [Function Name]:
//                  msPM_PassWord(BOOL bEnable)
//  [Description]
//                  input  the password for entering pm or turn off XTAL
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
#if 0//CHIP_ID == CHIP_TSUMD
void msPM0W_Mode_PassWord(BOOL bEnable)
{
	if(bEnable)
	{
		msWriteByte(REG_PM_8B, 0xA5);
		msWriteByte(REG_PM_8B, 0x5E);
	}
	else
	{
	}
}
#endif
#if( PM_SUPPORT_WAKEUP_DVI )

//**************************************************************************
//  [Function Name]:
//                  msPM_EnableDVIClockAmp(BOOL bEnable)
//  [Description]
//                  Enable DVI clock amplifier control
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void
msPM_EnableDVIClockAmp(Bool bEnable)
{
	if(!bEnable)
	{
		msWriteByteMask(REG_PM_A8, BIT3, BIT3);  // DVI Controller Clock gating
		msWriteByteMask(REG_DVI_CTRL, 0x00, EN_DVI_CTRL_MASK ); // disable DVI clock amplifier
	}
	else
	{
		msWriteByteMask(REG_PM_A8, 0x00, 0x0F);  // DVI Controller Clock Not gating
		msWriteByteMask(REG_DVI_CTRL, EN_DVI_CTRL_SET, EN_DVI_CTRL_MASK ); // enable DVI clock amplifier
	}
}


//**************************************************************************
//  [Function Name]:
void msPM_EnableRterm(BOOL bEnable)
{
	#if CHIP_ID >= CHIP_TSUMC
	if(bEnable)
	{
		msWriteByteMask(REG_PM_8E, 0x00, 0x0F); // DVI clock not pass
		drvDVI_PowerCtrl(DVI_POWER_STANDBY);
		ComboInputControl(COMBO_INPUT_POWERSAVING);//130604 Modify
		#if 0//MainBoardType==MainBoard_6124_M0A
		if((UserPrefInputSelectType != INPUT_PRIORITY_AUTO) && (UserPrefInputSelectType != INPUT_PRIORITY_DP))
			msWriteByteMask(REG_01C2, 0, BIT7);   // Turn off Port 2 Port Mux
		else
			msWriteByteMask(REG_01C2, BIT7, BIT7);   // Turn off Port 2 Port Mux
		#endif
		#if HDMI_PRETEST
		msWrite2ByteMask(REG_01C4, 0x0000, 0x0EEE);
		#endif
		#if CHIP_ID == CHIP_TSUMJ
		drvDVI_PortMuxControl(DVI_INPUT_PORT0);
		#endif
	}
	else
	{
		msWriteByteMask(REG_PM_8E, 0x0B, 0x0F);// DVI clock gating
		drvDVI_PowerCtrl(DVI_POWER_DOWN);
		ComboInputControl(COMBO_INPUT_OFF);//130604 Modify
		#if CHIP_ID == CHIP_TSUMJ
		drvDVI_PortMuxControl(DVI_INPUT_NONE);
		#endif
	}
// 111004 coding check with Shadow
	#else
	#if CHIP_ID == CHIP_TSUMV || CHIP_ID == CHIP_TSUM2 // 120522 coding, check 2
	msWriteByteMask(REG_PM_B2, BIT3, BIT3);//Power down DVI PLL band-gap first can reduce 0.4mA
	msWriteByteMask(REG_PM_B2, 0x00, BIT3);//power on DVI PLL band-gap
	#endif
	if(bEnable)
	{
		msWriteByteMask(REG_PM_8E, 0x00, 0x0F); // DVI clock not pass
		#if DVI_PORT
		#if DVI_PORT==TMDS_PORT_A || DVI_PORT==TMDS_PORT_B
		#if DVI_PORT==TMDS_PORT_A
		msWriteByteMask(REG_PM_B3, BIT4, BIT4);//Switch to(A)[4]
		msWriteByteMask(REG_PM_B2, 0x00, BIT0);//Not power down RCK(A)[0]
		#else
		msWriteByteMask(REG_PM_B3, BIT5, BIT5);//Switch to(B)[5]
		msWriteByteMask(REG_PM_B2, 0x00, BIT1);//Not power down RCK(B)[1]
		#endif
		msWriteByteMask(REG_PM_B2, 0x00, BIT2);//Not power down CLKIN(A/B)[2]
		msWriteByteMask(REG_PM_8F, 0x00, 0x0F);// DVI RAW clock (A/B) pass
		#else
		msWriteByteMask(REG_PM_B3, 0x00, BIT0);//Not power down RCK(B)[1]
		msWriteByteMask(REG_PM_B3, 0x00, BIT2);//Not power down CLKIN(C)[2]
		msWriteByteMask(REG_PM_8C, 0x00, 0x0F);// DVI RAW clock (C) pass
		#endif
		#endif
		#if HDMI_PORT
		#if HDMI_PORT==TMDS_PORT_A || HDMI_PORT==TMDS_PORT_B
		#if HDMI_PORT==TMDS_PORT_A
		msWriteByteMask(REG_PM_B3, BIT4, BIT4);//Switch to(A)[4]
		msWriteByteMask(REG_PM_B2, 0x00, BIT0);//Not power down RCK(A)[0]
		#else
		msWriteByteMask(REG_PM_B3, BIT5, BIT5);//Switch to(B)[5]
		msWriteByteMask(REG_PM_B2, 0x00, BIT1);//Not power down RCK(B)[1]
		#endif
		msWriteByteMask(REG_PM_B2, 0x00, BIT2);//Not power down CLKIN(A/B)[2]
		msWriteByteMask(REG_PM_8F, 0x00, 0x0F);// DVI RAW clock (A/B) pass
		#elif (HDMI_PORT==(TMDS_PORT_B|TMDS_PORT_C))
		msWriteByteMask(REG_PM_B3, 0, BIT4);//Switch to(B)[5]
		msWriteByteMask(REG_PM_B3, BIT5, BIT5);//Switch to(B)[5]
		msWriteByteMask(REG_PM_B2, 0x00, BIT1);//Not power down RCK(B)[1]
		msWriteByteMask(REG_PM_B2, 0x00, BIT2);//Not power down CLKIN(A/B)[2]
		msWriteByteMask(REG_PM_8F, 0x00, 0x0F);// DVI RAW clock (A/B) pass
		msWriteByteMask(REG_PM_8C, 0x00, 0x0F);// DVI RAW clock (C)pass  恁寁C prot clock  20180822 鱖牶
		#else
		msWriteByteMask(REG_PM_B3, 0x00, BIT0);//Not power down RCK(B)[1]
		msWriteByteMask(REG_PM_B3, 0x00, BIT2);//Not power down CLKIN(C)[2]
		msWriteByteMask(REG_PM_8C, 0x00, 0x0F);// DVI RAW clock (C)pass
		#endif
		#endif
	}
	else
	{
		msWriteByteMask(REG_PM_8E, 0x0B, 0x0F);// DVI clock gating
		msWriteByteMask(REG_PM_B2, BIT2 | BIT1 | BIT0, BIT2 | BIT1 | BIT0); // power down DVI(A/B) [0][1]:RCK,[2]:CLK
		msWriteByteMask(REG_PM_8F, 0x0B, 0x0F);// DVI RAW clock(A/B)gating
		#if DVI_PORT==TMDS_PORT_C || HDMI_PORT==TMDS_PORT_C
		msWriteByteMask(REG_PM_B3, BIT2 | BIT0, BIT2 | BIT0); // power down DVI(C) [0]:RCK,[2]:CLKIN
		msWriteByteMask(REG_PM_8C, 0x0B, 0x0F);// DVI RAW clock(C)gating
		#endif
	}
	#endif
}

//**************************************************************************
//  [Function Name]:

//                  msPM_EnableDVIDetect(BOOL bEnable)
//  [Description]
//                  Enable DVI Clock Detect -using DVI control clock
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void
msPM_EnableDVIDetect(BOOL bEnable)
{
	if( bEnable)
	{
		//PM_DVIRAW1_CLK_GATE_EN(FALSE);//msWriteByteMask(REG_PM_8C, 0x00, 0x0F);   // DVI RAW clock (C)not gating
		msWriteByteMask(REG_PM_8F, 0x00, 0x0F);   // DVI RAW clock (A/B)not gating
		//msWriteByteMask(REG_PM_8E, 0x00, 0x0F);   // DVI clock not gating
		msPM_EnableRterm(TRUE);
		#if 0
		#if (CHIP_ID == CHIP_TSUMV) // 110901 coding, check it again
		msWriteByteMask(REG_PM_B2, 0x00, BIT3 | BIT2 | BIT1 | BIT0); // NOT power down DVI(A/B) CKIN and RCK
		#else
		msWriteByteMask(REG_PM_B2, 0x00, BIT2 | BIT1 | BIT0); // NOT power down DVI(A/B) CKIN and RCK
		#endif
		msWriteByteMask(REG_PM_B3, 0x00, BIT2 | BIT0);    // NOT power down DVI( C) CLKIN and RCK
		msWriteByteMask(REG_PM_B3, BIT4, BIT5 | BIT4);
		#endif
		#if CHIP_ID == CHIP_TSUMU &&(/* INPUT_TYPE == INPUT_1A1D1H1DP||*/INPUT_TYPE == INPUT_1A2H1DP)
		if(UserPrefInputSelectType == INPUT_PRIORITY_HDMI)
		{
			#if DVI_PORT == TMDS_PORT_C
			msWriteByteMask(REG_DVI_DET, EN_DVI_DET_C, EN_DVI_DET_MASK); // Detection channel selection
			#else
			msWriteByteMask(REG_DVI_DET, EN_DVI_DET_AB, EN_DVI_DET_MASK); // Detection channel selection
			#endif
		}
		else if(UserPrefInputSelectType == INPUT_PRIORITY_HDMI2ND)
		{
			#if HDMI_PORT == TMDS_PORT_C
			msWriteByteMask(REG_DVI_DET, EN_DVI_DET_C, EN_DVI_DET_MASK); // Detection channel selection
			#else
			msWriteByteMask(REG_DVI_DET, EN_DVI_DET_AB, EN_DVI_DET_MASK); // Detection channel selection
			#endif
		}
		else
			msWriteByteMask(REG_DVI_DET, EN_DVI_DET_SET, EN_DVI_DET_MASK); // Detection channel selection
		#elif (CHIP_ID == CHIP_TSUMU &&(INPUT_TYPE == INPUT_1D1H1DP))
		msWriteByteMask(REG_DVI_DET, EN_DVI_DET_SET, EN_DVI_DET_MASK); // Detection channel selection
		//msWriteByteMask(REG_DVI_DET, EN_DVI_DET_SET, EN_DVI_DET_MASK); // Detection channel selection
		#else
		msWriteByteMask(REG_DVI_DET, EN_DVI_DET_SET, EN_DVI_DET_MASK); // Detection channel selection
		#endif
		#if !PM_SUPPORT_DVI_TIME_SHARE
		msPM_EnableDVIClockAmp(FALSE);
		#if (CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)
		msWriteByteMask(REG_PM_CC, 0x00, 0x0F);  // Not Controlled by amplifier
		#else
		msWriteByteMask(REG_PM_AD, 0x00, 0x0F);  // Not Controlled by amplifier
		#endif
		#else
		msPM_EnableDVIClockAmp(TRUE);
		#if (CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)
		msWriteByteMask(REG_PM_CC, 0x0F, 0x0F);  // Not Controlled by amplifier
		#else
		msWriteByteMask(REG_PM_AD, 0x0F, 0x0F);  // Controlled by amplifier
		#endif
		switch(sPMInfo.sPMConfig.ePMDVImode)
		{
			case ePMDVI_DVI0:
				msWriteByteMask(REG_DVI_CHEN, BIT0, EN_DVI_CHEN_MASK);
				break;
			case ePMDVI_DVI1:
				msWriteByteMask(REG_DVI_CHEN, BIT1, EN_DVI_CHEN_MASK);
				break;
			case ePMDVI_DVI0_DVI1:
				msWriteByteMask(REG_DVI_CHEN, BIT1 | BIT0, EN_DVI_CHEN_MASK);
				break;
			default:
				;
		}
		#endif
	}
	else
	{
		msWriteByteMask(REG_DVI_DET, 0, EN_DVI_DET_MASK);
		#if HDMI_PRETEST
		#if CHIP_ID >= CHIP_TSUMC
		msPM_EnableRterm(FALSE);
		#else
		msPM_EnableRterm(TRUE);
		#endif
		#else
		msPM_EnableRterm(FALSE);
		#endif
	}
}
#endif  // end of #if( PM_SUPPORT_WAKEUP_DVI )


//**************************************************************************
//  [Function Name]:
//                  msPM_EnableSARDetect(BOOL bEnable)
//  [Description]
//                  msPM_EnableSARDetect
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void
msPM_EnableSARDetect(BOOL bEnable)
{
	if (bEnable)
	{
		switch(sPMInfo.sPMConfig.ePMSARmode)
		{
			case ePMSAR_SAR0:
				msWriteByteMask(REG_SINGLE_KEY, EN_SAR_SINGLE_SET, EN_SAR_SINGLE_MASK);
				msWriteByteMask(REG_SAR_CMP, EN_SAR_14V, EN_SAR_CMP_MASK);
				msWriteByteMask(REG_SAR_ANYKEY, 0, EN_SAR_ANYKEY_MASK);
				break;
			case ePMSAR_SAR1:
				msWriteByteMask(REG_SINGLE_KEY, 0x11, EN_SAR_SINGLE_MASK);
				msWriteByteMask(REG_SAR_CMP, EN_SAR_05V, EN_SAR_CMP_MASK);
				msWriteByteMask(REG_SAR_ANYKEY, 0, EN_SAR_ANYKEY_MASK);
				break;
			case ePMSAR_SAR2:
				msWriteByteMask(REG_SINGLE_KEY, 0x12, EN_SAR_SINGLE_MASK);
				msWriteByteMask(REG_SAR_CMP, EN_SAR_05V, EN_SAR_CMP_MASK);
				msWriteByteMask(REG_SAR_ANYKEY, 0, EN_SAR_ANYKEY_MASK);
				break;
			case ePMSAR_SAR3:
				msWriteByteMask(REG_SINGLE_KEY, 0x13, EN_SAR_SINGLE_MASK);
				msWriteByteMask(REG_SAR_CMP, EN_SAR_05V, EN_SAR_CMP_MASK);
				msWriteByteMask(REG_SAR_ANYKEY, 0, EN_SAR_ANYKEY_MASK);
				break;
			case ePMSAR_SAR12:
				msWriteByteMask(REG_SINGLE_KEY, 0, EN_SAR_SINGLE_MASK);
				msWriteByteMask(REG_SAR_CMP, EN_SAR_14V, EN_SAR_CMP_MASK);
				msWriteByteMask(REG_SAR_ANYKEY, EN_SAR_2CH_SET, EN_SAR_ANYKEY_MASK);
				msWriteByteMask(REG_3A64, 0, BIT2);
				break;
			case ePMSAR_SAR123:
				msWriteByteMask(REG_SINGLE_KEY, 0, EN_SAR_SINGLE_MASK);
				msWriteByteMask(REG_SAR_CMP, EN_SAR_14V, EN_SAR_CMP_MASK);
				msWriteByteMask(REG_SAR_ANYKEY, EN_SAR_3CH_SET, EN_SAR_ANYKEY_MASK);
				msWriteByteMask(REG_3A64, 0, BIT2);
				break;
			case ePMSAR_SAR01:
				msWriteByteMask(REG_SINGLE_KEY, 0, EN_SAR_SINGLE_MASK);
				msWriteByteMask(REG_SAR_CMP, EN_SAR_05V, EN_SAR_CMP_MASK);
				msWriteByteMask(REG_SAR_ANYKEY, EN_SAR_2CH_SET, EN_SAR_ANYKEY_MASK);
				msWriteByteMask(REG_3A64, BIT2, BIT2);
				break;
			case ePMSAR_SAR012:
				msWriteByteMask(REG_SINGLE_KEY, 0, EN_SAR_SINGLE_MASK);
				msWriteByteMask(REG_SAR_CMP, EN_SAR_05V, EN_SAR_CMP_MASK);
				msWriteByteMask(REG_SAR_ANYKEY, EN_SAR_3CH_SET, EN_SAR_ANYKEY_MASK);
				msWriteByteMask(REG_3A64, BIT2, BIT2);
				break;
		}
		msWriteByteMask(REG_3A62, sPMInfo.sPMConfig.ePMSARmode, 0x0F);
		msWriteByteMask(REG_SAR_GPIO, EN_SAR_DET_SET, EN_SAR_DET_MASK);
	}
	else
	{
		msWriteByteMask(REG_SINGLE_KEY, 0, EN_SAR_SINGLE_MASK);
		msWriteByteMask(REG_SAR_GPIO, 0, EN_SAR_DET_MASK);
		msWriteByteMask(REG_SAR_ANYKEY, 0, EN_SAR_ANYKEY_MASK);
	}
}

#if PM_CABLEDETECT_USE_GPIO
//**************************************************************************
//  [Function Name]:
//                  msPM_EnableGPIODetect(BOOL bEnable)
//  [Description]
//                  msPM_EnableGPIODetect
//  [Arguments]:
//
//  [Return]:

//**************************************************************************
void
msPM_CableDetectStates()

{
	WORD INV_GPIO_POL_SET_Temp = INV_GPIO_POL_SET;
	#if !(CABLE_DETECT_VGA_USE_SAR)
	if(hwDSUBCable_Pin)
		INV_GPIO_POL_SET_Temp = (INV_GPIO_POL_SET_Temp) & ~PM_VGACBL_DET;
	#endif
	#if !(CABLE_DETECT_VGA_USE_SAR)
	if(hwDVICable_Pin)
		INV_GPIO_POL_SET_Temp = (INV_GPIO_POL_SET_Temp) & ~PM_DVICBL_DET;
	#endif
	#if ENABLE_DP_INPUT
	//if(!(DP_CABLE_NODET))
	if(!hwDPCable_Pin)
		INV_GPIO_POL_SET_Temp = (INV_GPIO_POL_SET_Temp) & ~PM_DPCBL_DET;
	#endif
	#if 0
	if(DET_HDMIA)
		INV_GPIO_POL_SET_Temp = (INV_GPIO_POL_SET_Temp) & ~PM_HDMIACBL_DET;
	if(DET_HDMIB)
		INV_GPIO_POL_SET_Temp = (INV_GPIO_POL_SET_Temp) & ~PM_HDMIBCBL_DET;
	if(DET_HDMIC)
		INV_GPIO_POL_SET_Temp = (INV_GPIO_POL_SET_Temp) & ~PM_HDMICCBL_DET;
	#endif
	msWrite2ByteMask(REG_PM_62, INV_GPIO_POL_SET_Temp, INV_GPIO_POL_MASK);
}
#endif
void
msPM_EnableGPIODetect(BOOL bEnable)
{
	if(bEnable)
	{
		msWrite2ByteMask(REG_PM_60, EN_GPIO_DET_SET, EN_GPIO_DET_MASK);
		msWrite2ByteMask(REG_PM_62, INV_GPIO_POL_SET, INV_GPIO_POL_MASK);
		#if  PM_CABLEDETECT_USE_GPIO
		msPM_CableDetectStates();
		#endif
	}
	else
	{
		msWrite2ByteMask(REG_PM_60, 0x00, EN_GPIO_DET_MASK);
		msWrite2ByteMask(REG_PM_62, 0x00, INV_GPIO_POL_MASK);
	}
}


//**************************************************************************
//  [Function Name]:
//                  msPM_EnableMCCSDetect(BOOL bEnable)
//  [Description]
//                  msPM_EnableMCCSDetect
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void
msPM_EnableMCCSDetect(BOOL bEnable)
{
	if(bEnable)
	{
		msWriteByte(REG_3E0A, 0xB7);  // enable DDC2Bi for A0
		#if (DVI_DDC_PORT==TMDS_PORT_A) || (HDMI_DDC_PORT==TMDS_PORT_A)	//121130 Modify
		msWriteByte(REG_3E0C, 0xB7);  // enable DDC2Bi for D0
		#endif
		msWriteByte(REG_3E0D, 0xB7);  // enable DDC2Bi for D1
		msWriteByte(REG_3E52, 0xB7);  // enable DDC2Bi for D2
		msWriteByteMask(REG_3E09, 0, (BIT1 | BIT0)); //disable No ACK ,Hold CLK
		#if CHIP_ID == CHIP_TSUMV
		msWriteByteMask(REG_3EC1, BIT6, BIT6);//Enable MCCS wake up function for ADC (D6 01 04 05)
		msWriteByteMask(REG_3EC0, BIT6 | BIT4 | BIT2, BIT6 | BIT4 | BIT2); //[6]:clear REG_3EC2[2], [4]:clear REG_0186[7], [2]:clear ADC wake up command value
		msWriteByteMask(REG_3EC1, BIT7, BIT7);//Enable MCCS wake up function for DVI (D6 01 04 05)
		msWriteByteMask(REG_3EC0, BIT7 | BIT5 | BIT3, BIT7 | BIT5 | BIT3); //[7]:clear REG_3EC2[3], [5]:clear REG_0186[7], [3]:clear DVI wake up command value
		#elif (CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD || CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)
		msWriteByteMask(REG_3EC1, BIT7 | BIT6, BIT7 | BIT6); // enable A0, D0
		msWriteByteMask(REG_3EEF, BIT7 | BIT6, BIT7 | BIT6); // enable D1, D2
		#else
		msWriteByteMask(REG_3EC1, (BIT4 | BIT3 | BIT2), (BIT4 | BIT3 | BIT2)); // enable MCCS wakeup by power key 04, 05
		#endif
	}
	else
	{
		msWriteBit(REG_3E0A, 0, BIT7);  // disable DDC2Bi for A0
		msWriteBit(REG_3E0C, 0, BIT7);  // disable DDC2Bi for D0
		msWriteBit(REG_3E0D, 0, BIT7);  // disable DDC2Bi for D1
		msWriteBit(REG_3E52, 0, BIT7);  // disable DDC2Bi for D2
		#if CHIP_ID == CHIP_TSUMV
		msWriteByteMask(REG_3EC0, BIT6 | BIT4 | BIT2, BIT6 | BIT4 | BIT2); //[6]:clear REG_3EC2[2], [4]:clear REG_0186[7], [2]:clear ADC wake up command value
		msWriteByteMask(REG_3EC1, 0, BIT6);//0->Bit6//Disable MCCS wake up function for ADC (D6 01 04 05)
		msWriteByteMask(REG_3EC0, BIT7 | BIT5 | BIT3, BIT7 | BIT5 | BIT3); //[7]:clear REG_3EC2[3], [5]:clear REG_0186[7], [3]:clear DVI wake up command value
		msWriteByteMask(REG_3EC1, 0, BIT7);//Disable MCCS wake up function for DVI (D6 01 04 05)
		#elif (CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD || CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)
		msWriteByteMask(REG_3EC1, 0, BIT7 | BIT6); // disable A0, D0
		msWriteByteMask(REG_3EEF, 0, BIT7 | BIT6); // disable D1, D2
		#else
		msWriteByteMask(REG_3EC1, 0, (BIT4 | BIT3 | BIT2) ); // disable MCCS wakeup by power key 04, 05
		#endif
	}
}


//**************************************************************************
//  [Function Name]:
//                  msPM_EDID_READ()
//  [Description]
//                  msPM_EDID_READ
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void
msPM_Enable_EDID_READ(BOOL bEnable)
{
	if(bEnable)
	{
		//msWriteByteMask(REG_3E45, BIT7, BIT7);  // enable DDC function for DVI_0
		//msWriteByteMask(REG_3E4D, BIT7, BIT7);  // enable DDC function for DVI_1
		//  msWriteByteMask(REG_3E49, BIT7, BIT7);  // enable DDC function for ADC_0
		#if(CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)
		// msWriteByteMask(REG_3E60, BIT7, BIT7);//reply ACK while source accesses A0_EDID with address is over 128
		#endif
		#if (CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD)
		//  msWriteByteMask(REG_3E58, BIT7, BIT7);  // enable DDC function for DVI_2
		#endif
	}
	else
	{
		// msWriteByteMask(REG_3E45, 0x00, BIT7);  // disable DDC function for DVI_0
		// msWriteByteMask(REG_3E4D, 0x00, BIT7);  // disable DDC function for DVI_1
		//msWriteByteMask(REG_3E49, 0x00, BIT7);  // disable DDC function for ADC_0
		#if (CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD)
		// msWriteByteMask(REG_3E58, 0x00, BIT7);  // disable DDC function for DVI_2
		#endif
	}
}

//**************************************************************************
//  [Function Name]:
//                  msPM_OutputTriState()
//  [Description]
//                  msPM_OutputTriState
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void
msPM_OutputTriState(void)
{
}


//**************************************************************************
//  [Function Name]:
//                  msPM_PowerDownMacro()
//  [Description]
//                  msPM_PowerDownMacro
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void  msPM_PowerDownMacro(void)
{
	msPM_InterruptEnable(FALSE);
	#if (CHIP_ID == CHIP_TSUMB || ENABLE_RTE)
	msWriteByteMask( REG_1207, BIT4, BIT4 ); // 關閉動態?椐q模式
	msWriteByteMask( REG_1200, 0, BIT1 );   //Bank12: reg_cke =1
	msWriteByteMask( REG_1203, 0, BIT4 );   //reg_cke_oenz=0
	msWriteByteMask( REG_1203, BIT5, BIT5 ); //reg_dq_eonz=1
	msWriteByteMask( REG_1203, BIT6, BIT6 ); //reg_adr_oenz=1
	msWriteByteMask( REG_1203, BIT7, BIT7 ); //reg_cko_oenz=1
	msWriteByteMask( REG_1100, BIT4, BIT4 ); //Gpio mode設??1
	msWriteByteMask( REG_1133, BIT5, BIT5 ); //Reg_ddrpll_reset設??1
	msWriteByteMask( REG_1133, BIT7, BIT7 ); //Reg_ddrpll_pd 設??1
	msWriteByteMask( REG_121E, BIT0, BIT0 ); //Reset 設??1
	msWriteByteMask( REG_1205, BIT2, BIT2 ); //Reg_mcp_en設??0
	msWriteByteMask( REG_1203, BIT4, BIT4 ); //reg_cke_oenz=0
	#endif
	#if CHIP_ID==CHIP_TSUMU
	#if PM_SUPPORT_SOG_TIME_SHARE
	msWriteByteMask(REG_2509, 0xFF, ~BIT7);
	msWriteByte(REG_2508, 0xFF);    //Power down ADC_vref /vref/adc_rgb/phase_digitizer/adc_pll/dpl_bg
	#else
	msWriteByteMask(REG_2509, 0xFF, ~(BIT7 | BIT2 | BIT1)); //dont power down SOG main/DAC
	msWriteByteMask(REG_2508, 0xFF, ~BIT1);             //dont power down band gap
	#endif
	if( sPMInfo.sPMConfig.bHVSync_enable || sPMInfo.sPMConfig.bSOG_enable )
		msWriteByteMask(REG_2508, 0x00, BIT1);
	if( !sPMInfo.sPMConfig.bSOG_enable )
		msWriteByteMask(REG_2560, BIT0, BIT0);
	else
	{
		msWriteByteMask(REG_2560, 0x00, BIT0);
		msWriteByteMask(REG_2509, 0x00, BIT1 | BIT2);
	}
	//DVI
	msWriteByteMask(REG_29C0, 0xFF, ~BIT3); // 121011 coding test
	#if HDMI_PRETEST
	//msWriteByteMask(REG_29C0, 0x00, ~BIT3);
	msWriteByteMask(REG_29C1, 0x00, ~(BIT5 | BIT6));
	#else
	//msWriteByteMask(REG_29C0, 0xFF, ~BIT3);
	msWriteByteMask(REG_29C1, 0xFF, ~(BIT5 | BIT6));
	#endif
	msWriteByteMask(REG_29D2, 0xFF, ~BIT3);
	msWriteByteMask(REG_29D3, 0xFF, ~(BIT4 | BIT5 | BIT6));
	//MOD ATOP
	msWriteByte(REG_3200, 0x00); // sub bank 0
	msWriteByteMask(REG_3265, 0x00, BIT2 | BIT6);
	msWriteByteMask(REG_3250, 0xFF, 0x1F);
	msWriteByteMask(REG_3264, 0x00, 0x1F);
	msWriteByteMask(REG_3250, 0xFF, 0x3F);
	msWrite2Byte(REG_3220, 0x0000); // TTL
	msWrite2Byte(REG_3222, 0x0000);
	msWrite2Byte(REG_3224, 0x0000);
	msWrite2Byte(REG_3230, 0x0000);
	msWrite2Byte(REG_3232, 0x0000);
	msWrite2Byte(REG_3234, 0x0000);
	msWrite2Byte(REG_3236, 0x0000);
	msWrite2Byte(REG_3238, 0x0000);
	msWrite2Byte(REG_323A, 0x0000);
	msWrite2Byte(REG_3228, 0xFFFF);
	msWrite2Byte(REG_322A, 0xFFFF);
	msWrite2Byte(REG_322C, 0xFFFF);
	msWriteByteMask(REG_3265, 0xFF, BIT2 | BIT6);
	//DPRX
	{
		msWriteByte(REG_356C, 0x0F);
		msWrite2Byte(REG_37E8, 0xFFFF);
		msWrite2Byte(REG_37EA, 0xFFFF);
		#if	ENABLE_DP_INPUT
		msWriteByteMask(REG_356D, BIT0, BIT0);
		//20120629  Xm, ASUSPB278Q_1Chip,   Cxxx
		if ( PowerOnFlag )
		{
			msWriteByte( REG_1FE0, msReadByte( REG_1FE0 ) & 0xEF );          //[4]:Enable AUX IRQ
			#if DP_SQUELCH_IRQ
			msWriteByte( REG_1FE3, msReadByte( REG_1FE3 ) & 0x7F );          //[8]:Enable SQUELCH IRQ
			#endif
		}
		else
		{
			msWriteByte( REG_1FE0, msReadByte( REG_1FE0 ) | 0x10 );            //[4]:Disable AUX IRQ
			#if DP_SQUELCH_IRQ
			msWriteByte( REG_1FE3, msReadByte( REG_1FE3 ) | 0x80 );           //[8]:Disable SQUELCH IRQ
			#endif
		}
		//20120629  Xm, ASUSPB278Q_1Chip,   Cxxx
		#else
		msWriteByteMask(REG_356D, BIT1 | BIT0, BIT1 | BIT0); //Mark Bit 1 , when Turn off Bit, we have wake up issue.
		#endif
	}
	msWriteByte(REG_3580, 0x1E);
	//Audio
	msWrite2Byte(REG_2C60, 0x2727);
	msWrite2Byte(REG_2C62, 0x2F06);
	msWrite2Byte(REG_2C64, 0x1800);
	msWrite2Byte(REG_2C66, 0x0000);
	msWrite2Byte(REG_2C68, 0x2003);
	msWrite2Byte(REG_2C6A, 0x0850);
	msWrite2Byte(REG_2C6C, 0x0800);
	//HDMI PLL
	msWriteByteMask(REG_05B9, BIT0, BIT0);
	//AU PLL
	msWriteByteMask(REG_05F0, BIT3, BIT3);
	//dprx Video AUPLL
	msWriteByteMask(REG_35D1, BIT0, BIT0);
	//dprx Audio AUPLL
	msWriteByteMask(REG_35B3, BIT0, BIT0);
	//MOD LPLL
	msWriteByteMask(REG_3881, BIT0, BIT0);
	//SCALAR LPLL
	msWriteByteMask(REG_38A3, BIT7, BIT7);
	//MPLL
	//msWriteByteMask(REG_1ED1, BIT0, BIT0);
	msWriteByteMask(REG_1EDC, BIT4 | BIT5, BIT4 | BIT5);
	//DDR ATOP
	msWriteByteMask(REG_1100, 0xFF, BIT5 | BIT4 | BIT3);
	msWriteByteMask(REG_1108, 0x00, 0x3F);
	msWriteByteMask(REG_110E, 0x00, BIT0);
	msWriteByteMask(REG_1154, BIT4, BIT4);
	msWriteByteMask(REG_1160, BIT1, BIT1);
	msWriteByteMask(REG_1133, BIT7, BIT7);
	//SDR
	msWriteByteMask(REG_1205, 0x00, BIT2);
	//ClK Gen
	msWriteByteMask(REG_1E24, BIT0, BIT0);
	#if(MainBoardType==MainBoard_MST9570S_DEMO)
	msWriteByteMask(REG_1E25, 0x00, 0x00);
	#else
	msWriteByteMask(REG_1E25, BIT2, BIT2);
	#endif
	msWriteByteMask(REG_1E26, BIT4 | BIT0, BIT4 | BIT0);
	msWriteByteMask(REG_1E27, BIT4, BIT4);
	msWriteByteMask(REG_1E28, BIT0, BIT0);
	msWriteByteMask(REG_1E29, BIT0, BIT0);
	msWriteByteMask(REG_1E2A, BIT0, BIT0);
	msWriteByteMask(REG_1E2B, BIT0, BIT0);
	msWriteByteMask(REG_1E2C, BIT0, BIT0);
	msWriteByteMask(REG_1E35, BIT0, BIT0);
	msWriteByteMask(REG_1E36, BIT0, BIT0);
	msWriteByteMask(REG_1E37, BIT0, BIT0);
	msWriteByteMask(REG_1E3B, BIT6, BIT6);
	msWriteByteMask(REG_1E3E, BIT0, BIT0);
	msWriteByteMask(REG_1E3F, BIT0, BIT0);
	msWriteByteMask(REG_1E40, BIT4 | BIT0, BIT4 | BIT0);
	msWriteByteMask(REG_1E41, BIT0, BIT0);
	msWriteByteMask(REG_1E44, BIT0, BIT0);
	msWriteByteMask(REG_1E45, BIT6, BIT6);
	msWriteByteMask(REG_1E46, BIT4 | BIT0, BIT4 | BIT0);
	msWriteByteMask(REG_1E47, BIT4 | BIT0, BIT4 | BIT0);
	//dont remove this setting , Garstin need setting  !!
	//crc collection of all the PM enable setting , if crc wrong , auto reset MCU w/o event trigger!!
	msWriteBit(REG_0381, TRUE, _BIT7);   //crc function disable
	#elif (CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD)
	//Audio
	//HPLL power on
	msWriteByteMask( REG_1707, BIT0, BIT0 );
	msWriteByteMask( REG_1783, BIT0, BIT0 );
	//LPLL
	msWriteByteMask( REG_3806, BIT5, BIT5);
	//MPLL
	msWriteByteMask(REG_1EDC, BIT4 | BIT5, BIT4 | BIT5);
	//DPLL
	//DDR ATOP
	msWrite2Byte(REG_1206, 0x3420); //cke always on
	msWrite2Byte(REG_1246, 0xFFFE);
	ForceDelay1ms(1);
	msWrite2Byte(REG_1218, 0x0400);
	msWrite2Byte(REG_1200, 0x002F); //off auto refresh
	msWrite2Byte(REG_1200, 0x052E); //triggle precharge all
	msWrite2Byte(REG_1200, 0x002E);
	msWrite2Byte(REG_1200, 0x032E); //triggle refresh
	msWrite2Byte(REG_1200, 0x002E); //cke always on
	ForceDelay1ms(1);
	msWrite2Byte(REG_1246, 0xFFFF);
	msWrite2Byte(REG_1200, 0x202E); //self refresh on
	msWriteByteMask(REG_1100, BIT5 | BIT4 | BIT3, BIT5 | BIT4 | BIT3);
	#if CHIP_ID == CHIP_TSUMD
	msWriteByteMask(REG_1101, BIT7, BIT7);
	msWriteByteMask(REG_1108, 0, 0x3F);
	msWriteByteMask(REG_110E, 0, BIT0);
	#endif
	msWriteByteMask(REG_1133, BIT7, BIT7);
	#if CHIP_ID == CHIP_TSUMD
	//ldo ddr
	msWriteByteMask(REG_1E02, 0, BIT3);
	#endif
	//ClK Gen
	msWriteByteMask(REG_1E24, BIT4 | BIT0, BIT4 | BIT0);
	msWriteByteMask(REG_1E25, BIT2, BIT2);
	#if CHIP_ID == CHIP_TSUMC
	msWriteByteMask(REG_1E26, BIT4 | BIT0, BIT4 | BIT0);
	#endif
	msWriteByteMask(REG_1E28, BIT0, BIT0);
	#if CHIP_ID == CHIP_TSUMD
	msWriteByteMask(REG_1E2A, BIT0, BIT0);
	#endif
	msWriteByteMask(REG_1E35, BIT0, BIT0);
	msWriteByteMask(REG_1E37, BIT2 | BIT0, BIT2 | BIT0);
	msWriteByteMask(REG_1E3E, BIT0, BIT0);
	msWriteByteMask(REG_1E40, BIT4 | BIT0, BIT4 | BIT0);
	msWriteByteMask(REG_1E46, BIT0, BIT0);
	msWriteByteMask(REG_1E47, BIT0, BIT0);
	//audio CLK Gen
	msWriteByteMask(REG_2C07, 0x00, 0xFF);
	#if (CHIP_ID == CHIP_TSUMC)
	msWriteByteMask(REG_01BB, 0x0000, 0x0030); //20171113
	#endif
	#elif (CHIP_ID == CHIP_TSUMJ || CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)
	//>>>ADC---------------------------------------------------------------------------------
	if( sPMInfo.sPMConfig.bHVSync_enable || sPMInfo.sPMConfig.bSOG_enable )
	{
		msWriteByteMask(REG_2509, 0xFF & (~(BIT7 | BIT2 | BIT1))	, 0xFF);
		msWriteByteMask(REG_2508, 0xFF & (~(BIT2 | BIT1))			, 0xFF);
		msWriteByteMask(REG_2560, 0x00						, BIT0);
		msWriteByteMask(REG_250C, 0xFF						, 0xFF);
		msWriteByteMask(REG_250D, 0xFF						, 0xFF);
		msWrite2ByteMask(REG_25F0, 0x0002					, 0xFFFF);
		msWrite2ByteMask(REG_25F2, 0x00C8					, 0xFFFF);
		msWriteByteMask(REG_25F4, 0x04						, 0x0E);
	}
	else
	{
		msWriteByteMask(REG_2509, 0xFF	, 0xFF);
		msWriteByteMask(REG_2508, 0xFF	, 0xFF);
		msWriteByteMask(REG_2560, BIT0	, BIT0);
		msWriteByteMask(REG_250C, 0xFF	, 0xFF);
		msWriteByteMask(REG_250D, 0xFF	, 0xFF);
		msWrite2ByteMask(REG_25F0, 0x000	, 0xFFFF);
		msWrite2ByteMask(REG_25F2, 0x000	, 0xFFFF);
		msWriteByteMask(REG_25F4, 0x00	, 0x0E);
	}
	//<<<ADC---------------------------------------------------------------------------------
	/*	//>>>DVI ATOP---------------------------------------------------------------------------------
		//confirming with RD Ocasi
	#if( PM_SUPPORT_WAKEUP_DVI )
		if( sPMInfo.sPMConfig.bDVI_enable)
		{
		    msWriteByteMask(REG_01C2,BIT5 ,BIT6|BIT5);
		    msWriteByteMask(REG_01C3,0x00 ,BIT7|BIT5|BIT4);
		    msWriteByteMask(REG_01CD,0x00 ,BIT0);
		    msWriteByteMask(REG_01CC,0x00 ,BIT2|BIT1|BIT0);
		    msWriteByteMask(REG_01CE, BIT3 ,BIT3|BIT2|BIT1|BIT0);	 //diff
		    msWriteByteMask(REG_17BE, BIT0 ,BIT0);
		    msWriteByteMask(REG_17C0, 0xA7 ,BIT7|BIT5|BIT2|BIT1|BIT0);	 //diff
		    msWriteByteMask(REG_17C1, 0x3F ,BIT5|BIT4|BIT3|BIT2|BIT1|BIT0);
		}
		else
	#endif
		{
		    msWriteByteMask(REG_01C2,0x00 ,BIT6|BIT5);
		    msWriteByteMask(REG_01C3,0x0B ,BIT7|BIT5|BIT4);
		    msWriteByteMask(REG_01CD,0x00 ,BIT0);
		    msWriteByteMask(REG_01CC,0x00 ,BIT2|BIT1|BIT0);
		    msWriteByteMask(REG_01CE, 0x0F ,BIT3|BIT2|BIT1|BIT0);	  //Diff
		    msWriteByteMask(REG_17BE, BIT0 ,BIT0);
		    msWriteByteMask(REG_17C0, 0xA7 ,BIT7|BIT5|BIT2|BIT1|BIT0);	  //Diff
		    msWriteByteMask(REG_17C1, 0x3F ,BIT5|BIT4|BIT3|BIT2|BIT1|BIT0);
		}
	*/	//<<<DVI---------------------------------------------------------------------------------
	//>>>MOD ATOP---------------------------------------------------------------------------------
	//msWriteByteMask(REG_30F0, BIT0, BIT0);
	//msWriteByteMask(REG_30EE, 0x00, BIT2|BIT1|BIT0);
	//msWriteByteMask(REG_30DA, 0x00, 0xFF);
	//msWrite2ByteMask(REG_308C, 0x00, 0xFFFF);
	//msWriteByteMask(REG_308E, 0x00, 0x1F);
	msWriteByteMask(REG_308A,  BIT5 | BIT4, BIT5 | BIT4);
	//<<<MOD ATOP---------------------------------------------------------------------------------
	//>>>KeyPad SAR---------------------------------------------------------------------------------
	//msWriteByteMask(REG_3A60,BIT6, BIT6);       //[6]SAR_PD
	//<<<KeyPad SAR---------------------------------------------------------------------------------
	//>>>MPLL_PD---------------------------------------------------------------------------------
	//msWriteByteMask(REG_1ED1,BIT0, BIT0);             // [4]: MPLL power DOWN   //move to msPM_SetPMClock()
	msWriteByteMask(REG_1EDC, BIT5 | BIT4, BIT5 | BIT4);            //[5][4]:Power Down MPLL 216/432
	//<<<MPLL_PD---------------------------------------------------------------------------------
	//>>>Clock Gen---------------------------------------------------------------------------------
	msWriteByteMask(REG_1E24, BIT0, BIT0);
	msWriteByteMask(REG_1E3E, BIT0, BIT0);
	msWriteByteMask(REG_1E35, BIT0, BIT0);
	msWriteByteMask(REG_1E37, BIT2 | BIT0, BIT2 | BIT0);
	msWriteByteMask(REG_1E47, BIT0, BIT0);
	msWriteByteMask(REG_1E25, BIT2, BIT2);
	msWriteByteMask(REG_1E28, BIT0, BIT0);
	msWriteByteMask(REG_1E46, BIT0, BIT0);
	msWriteByteMask(REG_1E24, BIT4, BIT4);
	#if (CHIP_ID == CHIP_TSUMJ)
	msWriteByteMask(REG_1E40, BIT4 | BIT0, BIT4 | BIT0); // LED
	msWriteByteMask(REG_1E2A, BIT0, BIT0);
	#endif
	#if (CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)
	#if ENABLE_DP_INPUT
	DPRxOutputEnable( FALSE );
	#endif
	msWriteByteMask(REG_1ECA, 0x1F, 0x1F);	// osc432m power down
	#endif
	#else
	#if PM_SUPPORT_SOG_TIME_SHARE
	msWriteByteMask(REG_2509, 0xFF, ~BIT7);
	msWriteByte(REG_2508, 0xFF);    //Power down ADC_vref /vref/adc_rgb/phase_digitizer/adc_pll/dpl_bg
	#else
	msWriteByteMask(REG_2509, 0xFF, ~(BIT7 | BIT2 | BIT1)); //dont power down SOG main/DAC
	msWriteByteMask(REG_2508, 0xFF, ~BIT1);             //dont power down band gap
	#endif
	if( sPMInfo.sPMConfig.bHVSync_enable || sPMInfo.sPMConfig.bSOG_enable )
		msWriteByteMask(REG_2508, 0x00, BIT1);
	if( !sPMInfo.sPMConfig.bSOG_enable )
		msWriteByteMask(REG_2560, BIT0, BIT0);
	else
	{
		msWriteByteMask(REG_2560, 0x00, BIT0);
		msWriteByteMask(REG_2509, 0x00, BIT1 | BIT2);
	}
	//DVI
	#if HDMI_PRETEST
	msWriteByteMask(REG_29C0, 0x00, ~BIT3);
	msWriteByteMask(REG_29C1, 0x00, ~(BIT5 | BIT6));
	#else
	msWriteByteMask(REG_29C0, 0xFF, ~BIT3);
	msWriteByteMask(REG_29C1, 0xFF, ~(BIT5 | BIT6));
	#endif
	msWriteByteMask(REG_29FE, 0xFF, ~(BIT7 | BIT6));
	#if CHIP_ID == CHIP_TSUMV && ! (USE_MOD_HW_CAL)
	msWriteByteMask(REG_306C, 0, BIT6);
	#endif
	msWriteByteMask(REG_306B, BIT2, BIT2);  //Power Down MOD IGEN
	//ClK Gen
	msWriteByteMask(REG_1E24, BIT0, BIT0); //[0]clk_osd_gate_l
	msWriteByteMask(REG_1E35, BIT0, BIT0); //[0]clk_fclk_gate
	#if CHIP_ID!=CHIP_TSUMV
	msWriteByteMask(REG_1E36, BIT0, BIT0); //[0]clk_mod_gate
	#endif
	msWriteByteMask(REG_1E37, BIT0, BIT0); //[0]clk_odclk1_I_gate
	#if CHIP_ID!=CHIP_TSUMV
	msWriteByteMask(REG_1E3B, BIT6, BIT6); //[7]clk_miu_rec_gate
	#endif
	msWriteByteMask(REG_1E3E, BIT0, BIT0); //[0]clk_idclk_i_gate
	msWriteByteMask(REG_1E3F, BIT0, BIT0); //[0]clk_hspclk_gate
	#if CHIP_ID!=CHIP_TSUMV
	msWriteByteMask(REG_1E41, BIT0, BIT0); //[0]clk_led_gate
	msWriteByteMask(REG_1E45, BIT6, BIT6); //[6]clk_patgen_bias_gate
	#endif
	msWriteByteMask(REG_1E47, BIT0, BIT0); //[0]clk_sysclk_ip_ga
	#if CHIP_ID == CHIP_TSUMY
	msWriteByteMask(REG_1E40, _BIT0, _BIT0);    //LED clock gating
	msWriteByteMask(REG_0A60, _BIT6, _BIT6);    //LED SAR power down
	msWrite2Byte(REG_0A80, 0x0000);          //Dimming PWM Disable
	msWriteByteMask(REG_0A87, 0, _BIT7);        //Boost clock  Disable
	msWriteByteMask(REG_0A95, 0, _BIT7);         //Boost PWM  Disable
	msWriteByteMask(REG_0AE1, 0, _BIT7 | _BIT6); //Bias current and External resistor Disable
	msWriteByteMask(REG_0A65, 0, _BIT6);            //Over temperature protectioni Disable
	#endif
	#if ( CHIP_ID == CHIP_TSUMB ) // 111216 coding, trunk
	msWriteByteMask(REG_1E25, BIT2, BIT2);              //[2]ckg_mclk_gate
	msWriteByteMask(REG_1E28, BIT4 | BIT0, BIT4 | BIT0); //[0]CLK_MEMPLL_gate [4]clk_led216_gate
	#endif
	#if HDMI_PRETEST
	#if CHIP_ID == CHIP_TSUMU
	msWrite2ByteMask( REG_29C0, 0, 0xFFFF ); // enable DVI0 PLL power, [12:11]: portB/A Data R-term
	#else
	msWriteByteMask(REG_01C4, 0x00, 0x0F); // Turn on Port 0 Date R-term
	msWriteByteMask(REG_01C4, 0x00, 0xF0); // Turn on Port 1 Date R-term
	msWriteByteMask(REG_01C5, 0x00, 0x0F); // Turn on Port 2 Date R-term
	#endif
	#endif
	#endif
}
//**************************************************************************
//  [Function Name]:
//                  msPM_PowerUpMacro()
//  [Description]
//                  msPM_PowerUpMacro
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msPM_PowerUpMacro(void)
{
	#if CHIP_ID==CHIP_TSUMU
	#ifndef FPGA
	#if (FRAME_BFF_SEL == FRAME_BUFFER)
	BYTE ucDDR3InitCount;
	BOOL bDDR3InitState = FALSE;
	#endif
	#endif
	// PRINT_MSG("Enter msPM_PowerUpMacro");
	//ADC
	msWriteByte(REG_2508, 0x00);    //Power down ADC_vref /vref/adc_rgb/phase_digitizer/adc_pll/dpl_bg
	msWriteByteMask(REG_2509, 0x00, ~BIT7);
	msWriteByteMask(REG_2560, 0x00, BIT0);
	msWriteByteMask(REG_03E9, 0x00, BIT7);
	//DVI
	msWriteByteMask(REG_29C0, 0x00, ~BIT3);
	msWriteByteMask(REG_29C1, 0x00, ~(BIT5 | BIT6));
	msWriteByteMask(REG_29D2, 0x00, ~BIT3);
	msWriteByteMask(REG_29D3, 0x00, ~(BIT4 | BIT5 | BIT6));
	//MOD ATOP
	msWriteByte(REG_3200, 0x00); // sub bank 0
	msWriteByteMask(REG_3265, 0x00, BIT2 | BIT6);
	msWriteByteMask(REG_3250, 0x00, 0x30);
	//DPRX
	#if ENABLE_DP_INPUT
	msWriteByteMask(REG_1FE3, BIT7, BIT7);//Temp for DP wake up issue
	msWriteByte(REG_356C, 0x00);
	msWrite2Byte(REG_37E8, 0x0000);
	msWrite2Byte(REG_37EA, 0x0000);
	msWriteByte(REG_356D, 0x00);
	msWriteByteMask( REG_35E0, BIT2, BIT2 );
	msWriteByteMask( REG_35E1, BIT2 | BIT3 | BIT6, BIT2 | BIT3 | BIT6 ); //if turn off, DP can't wake up
	msWriteByte( REG_3580, 0x00 );
	msWriteByteMask( REG_35FA, 0xC0, 0xC0 );
	//dprx Audio AUPLL
	msWriteByteMask(REG_35B3, 0x00, BIT0);
	//dprx Video AUPLL
	msWriteByteMask(REG_35D1, 0x00, BIT0);
	#endif
	//Audio
	msWrite2Byte(REG_2C60, 0x2F2F);
	msWrite2Byte(REG_2C62, 0x2F06);
	msWrite2Byte(REG_2C64, 0x0000);
	msWrite2Byte(REG_2C66, 0x0000);
	msWrite2Byte(REG_2C68, ((0x0A << 8) | (msReadByte(REG_2C68) & 0x0B)));
	msWrite2Byte(REG_2C6A, 0x6406);
	msWrite2Byte(REG_2C6C, 0x0400);
	//HDMI PLL
	msWriteByteMask(REG_05B9, 0x00, BIT0);
	//AU PLL
	msWriteByteMask(REG_05F0, 0x00, BIT3);
	//MOD LPLL
	msWriteByteMask(REG_3881, 0x00, BIT0);
	//SCALAR LPLL
	msWriteByteMask(REG_38A3, 0x00, BIT7);
	//MPLL
	//msWriteByteMask(REG_1ED1, 0x00, BIT0);
	msWriteByteMask(REG_1EDC, 0x00, BIT4 | BIT5);
	//DDR ATOP
	msWriteByteMask(REG_1154, 0x00, BIT4);
	msWriteByteMask(REG_1160, 0x00, BIT1);
	msWriteByteMask(REG_1133, 0x00, BIT7);
	//SDR
	msWriteByteMask(REG_1205, BIT2, BIT2);
	//ClK Gen
	msWriteByteMask(REG_1E24, 0x00, BIT0);
	msWriteByteMask(REG_1E25, 0x00, BIT2);
	msWriteByteMask(REG_1E26, 0x00, BIT4 | BIT0);
	msWriteByteMask(REG_1E27, 0x00, BIT4);
	msWriteByteMask(REG_1E28, 0x00, BIT0);
	msWriteByteMask(REG_1E29, 0x00, BIT0);
	msWriteByteMask(REG_1E2A, 0x00, BIT0);
	msWriteByteMask(REG_1E2B, 0x00, BIT0);
	msWriteByteMask(REG_1E2C, 0x00, BIT0);
	msWriteByteMask(REG_1E35, 0x00, BIT0);
	msWriteByteMask(REG_1E36, 0x00, BIT0);
	msWriteByteMask(REG_1E37, 0x00, BIT0);
	msWriteByteMask(REG_1E3B, 0x00, BIT6);
	msWriteByteMask(REG_1E3E, 0x00, BIT0);
	msWriteByteMask(REG_1E3F, 0x00, BIT0);
	msWriteByteMask(REG_1E40, 0x00, BIT4 | BIT0);
	msWriteByteMask(REG_1E41, 0x00, BIT0);
	msWriteByteMask(REG_1E44, 0x00, BIT0);
	msWriteByteMask(REG_1E45, 0x00, BIT6);
	msWriteByteMask(REG_1E46, 0x00, BIT4 | BIT0);
	msWriteByteMask(REG_1E47, 0x00, BIT4 | BIT0);
	//110316 The image has garbage issue after Leave PM mode.
	msWrite2Byte(REG_3220, 0x5555); // TTL
	msWrite2Byte(REG_3222, 0x5555);
	msWrite2Byte(REG_3224, 0x5555);
	#ifndef FPGA
	#if (FRAME_BFF_SEL == FRAME_BUFFER)
	msWriteByte( REG_1133, 0x00 );
	#if !PANEL_3D_PASSIVE_4M
	msWriteByte( REG_1205, 0x00 );
	#endif
	msWriteByte( REG_1100, 0x01 );  //miu_0_atop  start
	msWriteByte( REG_1108, 0x3F );
	msWriteByte( REG_110E, 0xE5 );
	msWriteByte( REG_1154, 0x00 );
	msWriteByte( REG_1160, 0x70 );
	msWriteByte( REG_110E, 0xA5 );  // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
	//Initial MIU
	Delay1ms( 1 );                          //delay 1ms
	msWriteByteMask( REG_121E, 0x01, 0x01 );
	msWriteByteMask( REG_121E, 0x00, 0x01 );
	Delay1ms( 1 );                          //delay 200us
	msWriteByteMask( REG_1200, 0x10, 0x10 );
	Delay1ms( 1 );                          //delay 500us
	msWriteByteMask( REG_1200, 0x08, 0x08 );
	Delay1ms( 1 );                          //delay 500us
	msWriteByteMask( REG_1200, 0x04, 0x04 );
	Delay1ms( 1 );                          //delay 500us
	msWriteByteMask( REG_1200, 0x02, 0x02 );
	Delay1ms( 1 );                          //delay 1us
	msWriteByteMask( REG_1200, 0x01, 0x01 );
	//BIST
	ucDDR3InitCount = 1;
	while(!bDDR3InitState)
	{
		if(msMemoryBist())
			bDDR3InitState = TRUE;
		if(ucDDR3InitCount++ >= 30)
			if(!bDDR3InitState)
				bDDR3InitState = TRUE;
	}
	#endif
	#endif
	#elif (CHIP_ID == CHIP_TSUMJ || CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)  //follow power down list to update it
	//>>>ADC---------------------------------------------------------------------------------
	msWriteByteMask(REG_2509, 0x00	, 0xFF);
	msWriteByteMask(REG_2508, 0x00	, 0xFF);
	msWriteByteMask(REG_2560, 0x00	, BIT0);
	msWriteByteMask(REG_01E9, 0x00	, BIT7);
	msWriteByteMask(REG_250C, 0x00, 0xFF);
	msWriteByteMask(REG_250D, 0x00	, 0xFF);
	msWrite2ByteMask(REG_25F0, 0x0002		, 0xFFFF);
	msWrite2ByteMask(REG_25F2, 0x00C8		, 0xFFFF);
	msWriteByteMask(REG_25F4, 0x04	, 0x0E);
	//<<<ADC---------------------------------------------------------------------------------
	/*		//>>>DVI ATOP---------------------------------------------------------------------------------
			msWriteByteMask(REG_01C2,BIT5,BIT6|BIT5);
			msWriteByteMask(REG_01C3,0x00 ,BIT7|BIT5|BIT4);
			msWriteByteMask(REG_01CD,0x00 ,BIT0);
			msWriteByteMask(REG_01CC,0x00 ,BIT2|BIT1|BIT0);
			msWriteByteMask(REG_01CE,0x00 ,BIT3|BIT2|BIT1|BIT0);	  //Diff
			msWriteByteMask(REG_17BE, 0x00 ,BIT0);
			msWriteByteMask(REG_17C0, 0x00 ,BIT7|BIT5|BIT2|BIT1|BIT0);	  //Diff
			msWriteByteMask(REG_17C1, 0x00 ,BIT5|BIT4|BIT3|BIT2|BIT1|BIT0);
	*/		//<<<DVI---------------------------------------------------------------------------------
	//>>>MOD ATOP---------------------------------------------------------------------------------
	//msWriteByteMask(REG_30F0, 0x00, BIT0);
	//msWriteByteMask(REG_30EE, BIT2|BIT1|BIT0, BIT2|BIT1|BIT0);
	//msWriteByteMask(REG_30DA, 0xFF, 0xFF);
	//msWrite2ByteMask(REG_308C, 0xFFFF, 0xFFFF);
	//msWriteByteMask(REG_308E, 0xFF, 0x1F);
	msWriteByteMask(REG_308A,  0x00, BIT5 | BIT4);
	//<<<MOD ATOP---------------------------------------------------------------------------------
	//>>>KeyPad SAR---------------------------------------------------------------------------------
	msWriteByteMask(REG_3A60, 0x00, BIT6);		//[6]SAR_PD
	//<<<KeyPad SAR---------------------------------------------------------------------------------
	//>>>MPLL_PD---------------------------------------------------------------------------------
	//msWriteByteMask(REG_1ED1,BIT0, BIT0); 			// [4]: MPLL power DOWN   //move to msPM_SetPMClock()
	msWriteByteMask(REG_1EDC, 0x00, BIT5 | BIT4);				//[5][4]:Power Down MPLL 216/432
	//<<<MPLL_PD---------------------------------------------------------------------------------
	//>>>Clock Gen---------------------------------------------------------------------------------
	msWriteByteMask(REG_1E24, 0x00, BIT0);
	msWriteByteMask(REG_1E3E, 0x00, BIT0);
	msWriteByteMask(REG_1E35, 0x00, BIT0);
	msWriteByteMask(REG_1E37, 0x00, BIT2 | BIT0);
	msWriteByteMask(REG_1E47, 0x00, BIT0);
	msWriteByteMask(REG_1E25, 0x00, BIT2);
	msWriteByteMask(REG_1E28, 0x00, BIT0);
	msWriteByteMask(REG_1E46, 0x00, BIT0);
	msWriteByteMask(REG_1E24, 0x00, BIT4);
	#if (CHIP_ID == CHIP_TSUMJ)
	msWriteByteMask(REG_1E40, 0x00, BIT4 | BIT0); // LED
	msWriteByteMask(REG_1E2A, 0x00, BIT0);
	#endif
	//#endif
	#if (CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)
	#if ENABLE_DP_INPUT
	DPRxOutputEnable( TRUE );
	#endif
	msWriteByteMask(REG_1ECA, 0x00, 0x1F);	// osc432m power up
	#endif
	//<<<Clock Gen---------------------------------------------------------------------------------
	MPLL_POWER_UP(_ENABLE);
	mcuSetSystemSpeed(SPEED_NORMAL_MODE);
	mStar_Init();  // remove it to speed up powering on time????
	#else//endMST8556
	//ADC
	msWriteByte(REG_2508, 0x00);    //Power down ADC_vref /vref/adc_rgb/phase_digitizer/adc_pll/dpl_bg
	msWriteByteMask(REG_2509, 0x00, ~BIT7);
	msWriteByteMask(REG_2560, 0x00, BIT0);
	msWriteByteMask(REG_03E9, 0x00, BIT7);
	//DVI
	msWriteByteMask(REG_29C0, 0x00, ~BIT3);
	msWriteByteMask(REG_29C1, 0x00, ~(BIT5 | BIT6));
	msWriteByteMask(REG_29FE, 0x00, ~(BIT7 | BIT6));    //111011 Rick add power up condition - C_FOS_018
	#if CHIP_ID == CHIP_TSUMV && !(USE_MOD_HW_CAL)
	msWriteByteMask(REG_306C, BIT6, BIT6);
	#endif
	msWriteByteMask(REG_306B, 0, BIT2);  //Disable Power Down MOD IGEN
	//ClK Gen
	msWriteByteMask(REG_1E24, 0x00, BIT0); //[0]clk_osd_gate_l
	msWriteByteMask(REG_1E35, 0x00, BIT0); //[0]clk_fclk_gate
	#if CHIP_ID!=CHIP_TSUMV
	msWriteByteMask(REG_1E36, 0x00, BIT0); //[0]clk_mod_gate
	#endif
	msWriteByteMask(REG_1E37, 0x00, BIT2 | BIT0); //[0]clk_odclk1_I_gate //130604 Modify
	#if CHIP_ID!=CHIP_TSUMV
	msWriteByteMask(REG_1E3B, 0x00, BIT6); //[7]clk_miu_rec_gate
	#endif
	msWriteByteMask(REG_1E3E, 0x00, BIT0); //[0]clk_idclk_i_gate
	msWriteByteMask(REG_1E3F, 0x00, BIT0); //[0]clk_hspclk_gate
	#if CHIP_ID!=CHIP_TSUMV
	msWriteByteMask(REG_1E41, 0x00, BIT0); //[0]clk_led_gate
	msWriteByteMask(REG_1E45, 0x00, BIT6); //[6]clk_patgen_bias_gate
	#endif
	msWriteByteMask(REG_1E47, 0x00, BIT0); //[0]clk_sysclk_ip_gate
	#if CHIP_ID == CHIP_TSUMY
	msWriteByteMask(REG_1E40, 0x00, BIT0);                  //LED clock gating
	msWriteByteMask(REG_0A60, 0x00, BIT6);                  //LED SAR power On
	//msWriteWord(REG_0A81, 0xFFFF);                    //Dimming PWM enable,  select CH?
	//msWriteByteMask(REG_0A87, BIT7, BIT7);            //Boost clock  enable
	//msWriteByteMask(REG_0A95, BIT7, BIT7);            //Boost PWM  enable
	msWriteByteMask(REG_0AE1, BIT7 | BIT6, BIT7 | BIT6); //Bias current and External resistor enable
	msWriteByteMask(REG_0A65, BIT6, BIT6);         //Over temperature protectioni enable
	#endif
	#if ( CHIP_ID == CHIP_TSUMB ) // 111216 coding, trunk
	msWriteByteMask(REG_1E25, 0x00, BIT2);              //[2]ckg_mclk_gate
	msWriteByteMask(REG_1E28, 0x00, BIT4 | BIT0); //[0]CLK_MEMPLL_gate [4]clk_led216_gate
	#endif
	#if CHIP_ID>=CHIP_TSUMC // nick add for C/D CHip PM Close too much	//130321
	MPLL_POWER_UP(_ENABLE);
	mcuSetSystemSpeed(SPEED_NORMAL_MODE);
	mStar_Init();
	#endif
	#endif
	#if ((FRAME_BFF_SEL == FRAME_BUFFER) || (ENABLE_RTE))&&(CHIP_ID != CHIP_TSUMF)
	{
		extern void msInitMemory( void );
		#if CHIP_ID == CHIP_TSUMB
		msWriteByteMask( REG_1207, 0, BIT4 );   // 打開動態?椐q模式
		#endif
		msInitMemory();
	}
	#endif
	DDC2Bi_Init();
	msPM_InterruptEnable(TRUE);
}
//**************************************************************************
//  [Function Name]:
//                  msPM_MCCSReset()
//  [Description]
//                  msPM_MCCSReset
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msPM_MCCSReset(void)
{
	#if (CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD || CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)
	msWriteByte(REG_3EC0, 0xFF); // clear status of A0, D0
	msWriteByte(REG_3EC0, 0x00);
	msWriteByte(REG_3EEE, 0xFF); // clear status of D1, D2
	msWriteByte(REG_3EEE, 0x00);
	#else
	msWriteByteMask(REG_0381, BIT7, BIT7); //PM wakeup status clear.
	msWriteByteMask( REG_3EC1, (BIT5 | BIT1 | BIT0), (BIT5 | BIT1 | BIT0) ); //Clear DDC2BI D6 Comamnd 04,05  flag
	#endif
}

#if CHIP_ID <=CHIP_TSUM2

//**************************************************************************
//  [Function Name]:
//                  msPM_StartRCOSCCal()
//  [Description]
//                  msPM_StartRCOSCCal
//  [Arguments]:
//
//  [Return]:
//  RCOSC = XTAL * Counter / 512 => Counter = RCOSC *512/XTAL = 143 =>8Fh
//**************************************************************************
Bool msPM_StartRCOSCCal(void)
{
	#ifndef _RCOSC_MAX
	BYTE i;
	WORD ucCounter;
	int iDeltaOld = 100;
	int iDeltaNew = 0;
	BYTE ucSetOld = 0x08;
	#endif
	BYTE ucTemp;
	BYTE ucSetNow = 0x08;
	ucTemp = msReadByte(REG_PM_82) & 0x07; // deglitch time setting
	#ifdef _RCOSC_MAX
	ucSetNow = 0xF;
	msWriteByte(REG_PM_82, (ucSetNow << 4) | ucTemp);
	#else
	for( i = 0; i < 16; i++)
	{
		msWriteByte(REG_PM_82, (ucSetNow << 4) | ucTemp);
		msWriteByte(REG_3A80, 0x80);//osc soft reset
		msWriteByte(REG_3A80, 0x03);//RCOSC calculate & counter one time mode enable
		while( !( msReadByte(REG_3A83) & _BIT4 ) ) // one time counter flag
		{
		}
		ucCounter = msRead2Byte(REG_3A82) & 0x03FF; // one time counter report
//        PM_printData("\r\n***ucCounter(%x)", ucCounter);
		iDeltaNew = RCOSC_TARGET - (int)ucCounter;
//        PM_printData("\r\n***iDeltaNew(%d)", iDeltaNew);
		if(abs(iDeltaNew) < abs(iDeltaOld))
		{
			ucSetOld = ucSetNow;
			if(ucCounter > RCOSC_TARGET)
			{
				ucSetNow--;
			}
			else
			{
				ucSetNow++;
			}
			iDeltaOld = iDeltaNew;
//          PM_printData("\r\n***RCOSC Set_new(%x)", ucSetNow);
		}
		else
		{
			msWriteByte(REG_PM_82, (ucSetOld << 4) | ucTemp);
			PM_printData("\r\n***RCOSC Set_old(%x)", ucSetOld);
			msWriteByte(REG_3A80, 0x00);
			return TRUE;
		}
	}
	#endif
	return FALSE;
}

#endif

#if( PM_SUPPORT_AC2DC )
//**************************************************************************
//  [Function Name]:
//                  msPM_EnableAC2DC()
//  [Description]
//                  msPM_EnableAC2DC
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void
msPM_EnableAC2DC(Bool bEnable)
{
	if(bEnable)   /*Turn On PM*/
	{
		msWriteByteMask(REG_PM_A8, 0x00, 0xF0);       /*AC2DC controler clock bypass*/
		msWriteByte(REG_PM_C0, AC2DC_MODE);     //AC2DC controler enable
		msWriteByte(REG_PM_C2, OFF_PERIOD);     //AC2DC Off period
		msWriteByte(REG_PM_C6, 0x88);       //AC detect voltage
		msWriteByte(REG_PM_C4, AC2DC_PAD);          //AC2DC pad function enable(GPIO2)
	}
	else /*Turn Off PM*/
	{
		msWriteByteMask(REG_PM_A8, 0xB0, 0xF0);       /*AC2DC controler clock bypass*/
		msWriteByte(REG_PM_C4, 0x00);           //AC2DC pad function disable(GPIO2)
		msWriteByte(REG_PM_C0, OFF_MODE);       //AC2DC controler disable
		msWriteByte(REG_PM_C2, 0x00);       /*Off period*/
		msWriteByte(REG_PM_C6, 0x00);
	}
}
#endif  // end of #if( PM_SUPPORT_AC2DC )


//**************************************************************************
//  [Function Name]:
//                  msPM_GetPMStatus()
//  [Description]
//                  msPM_GetPMStatus
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool
msPM_GetPMStatus(void)
{
	BOOL bResault = FALSE;
	BYTE ucStatus_85;
	BYTE ucStatus_86;
	volatile WORD ucStatus_GPIO;
	ucWakeupStatus = ePMSTS_NON;
	ucStatus_85   = msReadByte(REG_EVENT1);
	ucStatus_86   = msReadByte(REG_EVENT2);
	ucStatus_GPIO = msRead2Byte( REG_PM_64 );
	#if  0//ENABLE_DEBUG
	printData("ucStatus_85==%d", ucStatus_85);
	printData("ucStatus_86===%d", ucStatus_86);
	printData("ucStatus_GPIO==%d", ucStatus_GPIO);
	#endif
	#if PM_POWERkEY_GETVALUE
	if(PowerKey == 0)
	{
		KeypadButton = BTN_Nothing;                //110914 Rick add for enable OSDLock function while PM On - A023
		Key_ScanKeypad();
		ucWakeupStatus = ePMSTS_POWERGPIO_ACT;
		bResault = TRUE;
	}
	else
	#endif
	#if PM_CABLE_DETECT_USE_SAR
		if((abs(sPMInfo.bCABLE_SAR_VALUE - CABLE_DET_SAR) > 5) && (PowerOnFlag))
		{
			ucWakeupStatus = ePMSTS_CABLESAR_ACT;
			bResault = TRUE;
		}
		else
	#endif
		#if (ModelName!=LEYI_JRY_LQ570S_BV1)
			if(ucStatus_85 & (HSYNC_DET_0 | VSYNC_DET_0 | HV_DET_0)) // SOG_DET  OPEN  20170308  if(ucStatus_85 & (HSYNC_DET_0|VSYNC_DET_0|SOG_DET_0|HV_DET_0))
			{
				ucWakeupStatus = ePMSTS_VGA_ACT;
				SrcInputType = Input_ANALOG;
				bResault = TRUE;
			}
		#else
			if (0);
			else
		#endif
	#if  0
	#if CHIP_ID==CHIP_TSUMU
			else if( ucStatus_GPIO & ( PMGPIO00_INT \
			                           | PMGPIO01_INT \
			                           | PMGPIO02_INT \
			                           | PMGPIO03_INT \
			                           | PMGPIO04_INT \
			                           | PMGPIO05_INT \
			                           | PMGPIO06_INT \
			                           | PMGPIO07_INT \
			                           | PMGPIO24_INT \
			                           | PMGPIO25_INT \
			                           | PMGPIO26_INT \
			                           | PMGPIO27_INT ) )
	#else
			else if( ucStatus_GPIO & (PMGPIO04_INT\
			                          | GPIO22_INT\
			                          | PMGPIO02_INT \
			                          | PMGPIO06_INT\
			                          | GPIO00_INT\
			                          | GPIO11_INT\
			                          | PMGPIO03_INT ) )
	#endif
	#endif
				if( ucStatus_GPIO & EN_GPIO_DET_MASK)
				{
					//  ucWakeupStatus = ePMSTS_GPIO_ACT;
					ucWakeupStatus = ePMSTS_GPIO_POWER_KEY_ACT; //20121003
					bResault = TRUE;
				}
				else
				{
					if( ucStatus_86 & CEC_WAKEUP )
					{
						ucWakeupStatus = ePMSTS_CEC_ACT;
						bResault = TRUE;
					}
					else if( ucStatus_86 & D2B_WAKEUP )
					{
//#define D2B_PWR_CMD_WKUP_STATUS()   (msReadByte( REG_3EC1 ))
						#if CHIP_ID == CHIP_TSUMV
						volatile BYTE VGA_mccsWakeUpStatus = msReadByte(REG_3EC4);
						volatile BYTE DVI_mccsWakeUpStatus = msReadByte(REG_3EC5);
						if((VGA_mccsWakeUpStatus == 0x01) || (DVI_mccsWakeUpStatus == 0x01))
							ucWakeupStatus = ePMSTS_MCCS01_ACT;
						else if((VGA_mccsWakeUpStatus == 0x04) || (DVI_mccsWakeUpStatus == 0x04))
							ucWakeupStatus = ePMSTS_MCCS04_ACT;
						else if((VGA_mccsWakeUpStatus == 0x05) || (DVI_mccsWakeUpStatus == 0x05))
							ucWakeupStatus = ePMSTS_MCCS05_ACT;
						#elif CHIP_ID == CHIP_TSUMC||CHIP_ID == CHIP_TSUMD ||CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF//20130604 nick add
						volatile BYTE mccsWakeUpStatus;
						if(msReadByte(REG_3EC2)&BIT2) // A0
							mccsWakeUpStatus = msReadByte( REG_3EC4 );
						else if(msReadByte(REG_3EC2)&BIT3) // D0
							mccsWakeUpStatus = msReadByte( REG_3EC5 );
						else if(msReadByte(REG_3EF0)&BIT2) // D1
							mccsWakeUpStatus = msReadByte( REG_3EF2 );
						else if(msReadByte(REG_3EF0)&BIT3) // D2
							mccsWakeUpStatus = msReadByte( REG_3EF3 );
						if( mccsWakeUpStatus == 0x05 )
							ucWakeupStatus = ePMSTS_MCCS05_ACT;
						else if( mccsWakeUpStatus == 0x04 )
							ucWakeupStatus = ePMSTS_MCCS04_ACT;
						else
							ucWakeupStatus = ePMSTS_MCCS01_ACT;
						#else
						volatile BYTE mccsWakeUpStatus = msReadByte( REG_3EC1 );
						if( mccsWakeUpStatus & BIT7 )
							ucWakeupStatus = ePMSTS_MCCS05_ACT;
						else if( mccsWakeUpStatus & BIT6 )
							ucWakeupStatus = ePMSTS_MCCS04_ACT;
						else
							ucWakeupStatus = ePMSTS_MCCS01_ACT;
						#endif
						bResault = TRUE;
					}
					else if( ucStatus_86 & SAR_IN_DET )
					{
						ucWakeupStatus = ePMSTS_SAR_ACT;
						bResault = TRUE;
					}
					//================================================================================
					//  Move DP wake up checking first before DVI, because DVI clock detected bit would report 1 when DP plug in.
					//================================================================================
					#if ((CHIP_ID == CHIP_TSUMC)||(CHIP_ID == CHIP_TSUMD))
					#if( PM_SUPPORT_WAKEUP_DP &&ENABLE_DP_INPUT)
					#if CInput_Displayport_C2 != CInput_Nothing	//130604 xiandi
					else if(((DP_GetSquelchPortB(1)) && ((msReadByte( REG_06E3) & 0x03) == 0x01)) && sPMInfo.sPMConfig.bDP_enable )
					{
						// Normal Trining Wake up
						ucWakeupStatus = ePMSTS_DP_ACT;
						SrcInputType = Input_Displayport;
						bResault = TRUE;
					}
					else if((DP_GetSquelchPortB(0x1FFF)) && sPMInfo.sPMConfig.bDP_enable)
					{
						// fast Trining Wake up
						ucWakeupStatus = ePMSTS_DP_ACT;
						SrcInputType = Input_Displayport;
						bResault = TRUE;
					}
					#endif
					#if CInput_Displayport_C3 != CInput_Nothing	//130604 xiandi
					else if(((DP_GetSquelchPortC(1)) && ((msReadByte( REG_07E3) & 0x03) == 0x01)) && sPMInfo.sPMConfig.bDP_enable )
					{
						// Normal Trining Wake up
						ucWakeupStatus = ePMSTS_DP_ACT;
						SrcInputType = Input_Displayport3;
						bResault = TRUE;
					}
					else if((DP_GetSquelchPortC(0x1FFF)) && sPMInfo.sPMConfig.bDP_enable)
					{
						ucWakeupStatus = ePMSTS_DP_ACT;
						SrcInputType = Input_Displayport3;
						bResault = TRUE;
					}
					#endif
					#endif
					#endif
					#if (CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)
					#if( PM_SUPPORT_WAKEUP_DP &&ENABLE_DP_INPUT)
					else if(
					    //#if DISABLE_AUTO_SWITCH
					    //            sPMInfo.sPMConfig.bDP_enable && (((FIXED_PORT == Input_Displayport)&&(DP_GetSquelchPortB(1))&&((msReadByte( REG_06E3)&0x03)==0x02)))
					    //#else
					    sPMInfo.sPMConfig.bDP_enable && (((DP_GetSquelchPortB(1)) && ((msReadByte( REG_06E3) & 0x03) == 0x02)))
					    //#endif
					)
					{
						// Normal Trining Wake up
						ucWakeupStatus = ePMSTS_DP_ACT;
						SrcInputType = Input_Displayport;
						bResault = TRUE;
						PM_printData("ePMSTS_DP_ACT NormalTraining:%d", ePMSTS_DP_ACT);
					}
					else if(
				    #if DISABLE_AUTO_SWITCH
					    (FIXED_PORT == Input_Displayport) &&
				    #endif
					    ((DP_GetSquelchPortB(0x1FFF)) && sPMInfo.sPMConfig.bDP_enable))
					{
						// fast Trining Wake up
						ucWakeupStatus = ePMSTS_DP_ACT;
						SrcInputType = Input_Displayport;
						bResault = TRUE;
						PM_printData("ePMSTS_DP_ACT FastTraining DP:%d", ePMSTS_DP_ACT);
					}
					#endif
					#endif
					#if( PM_SUPPORT_WAKEUP_DVI )
					#if (ENABLE_HDMI && (HDMI_PORT==TMDS_PORT_B)&&(DVI_PORT==TMDS_PORT_C))		//130107_25 Henry
					else if(((UserPrefInputSelectType == INPUT_PRIORITY_AUTO) || (UserPrefInputSelectType == INPUT_PRIORITY_HDMI)) && ( ucStatus_86 & DVI_CLK_DET_0 ))
					{
						ucWakeupStatus = ePMSTS_DVI_0_ACT;
						//SrcInputType = Input_Digital; // 120117 coding reserved
						bResault = TRUE;
					}
					else if(((UserPrefInputSelectType == INPUT_PRIORITY_AUTO) || (UserPrefInputSelectType == INPUT_PRIORITY_DVI)) && ( ucStatus_86 & DVI_CLK_DET_1 ))
					{
						ucWakeupStatus = ePMSTS_DVI_1_ACT;
						//SrcInputType = Input_Digital2; // 120117 coding reserved
						bResault = TRUE;
					}
					#elif       0
					#else
					else if( ucStatus_86 & DVI_CLK_DET_0 )
					{
						ucWakeupStatus = ePMSTS_DVI_0_ACT;
						//SrcInputType = Input_Digital; // 120117 coding reserved
						bResault = TRUE;
					}
					else if( ucStatus_86 & DVI_CLK_DET_1 )
					{
						ucWakeupStatus = ePMSTS_DVI_1_ACT;
						//SrcInputType = Input_Digital2; // 120117 coding reserved
						bResault = TRUE;
					}
					#endif
					#endif  // end of #if( PM_SUPPORT_WAKEUP_DVI )
					#if CHIP_ID == CHIP_TSUMU
					#if( PM_SUPPORT_WAKEUP_DP &&ENABLE_DP_INPUT)
					else if( (g_bDPAUXVALID && sPMInfo.sPMConfig.bDP_enable ))//||(!(msRegs[REG_1FA5]&_BIT3)))
					{
						ucWakeupStatus = ePMSTS_DP_ACT;
						SrcInputType = Input_Displayport;
						bResault = TRUE;
					}
					if((!g_bDPAUXVALID) && sPMInfo.sPMConfig.bDP_enable && (msReadByte( REG_1FE0)&BIT4))
					{
						msWriteByteMask(REG_1FE0, 0, BIT4);
					}
					#endif
					#endif
					#if CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD || CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF// 20130604 nick add
					#if ENABLE_MHL
					if((sPMInfo.ucPMMode != ePM_POWEROFF))	// 130801 william
					{
						BYTE tempport;
						if(mapi_mhl_WakeupDetect(TRUE, &tempport))// 20130604 nick add
						{
							//if(tempport == Input_HDMI || tempport == Input_HDMI2)
							{
								SrcInputType = tempport;
								ucWakeupStatus = ePMSTS_MHL_ACT;
								bResault = TRUE;
								#if ENABLE_MHL //&& (CHIP_ID == CHIP_TSUM2)//130703 nick
								MHLExtenCountFlag = 0;
								#endif
								PM_printData("ePMSTS_MHL_ACT PowerSaving:%d", ePMSTS_MHL_ACT);
								PM_printData("MHL wakeup port:%d", SrcInputType);
							}
						}
					}
					else
					{
						mapi_mhl_ChargePortDetect();
					}
					#endif
					#endif
				}
	return  bResault;
}


//**************************************************************************
//  [Function Name]:
//                  msPM_SetPMClock()
//  [Description]
//                  msPM_SetPMClock
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void
msPM_SetPMClock(BYTE clk_sel)
#if 1
{
	if (clk_sel == RCOSC)
	{
		//PM_printMsg(" \r\n***PM Clock =>RCOSC ");
		#if (CHIP_ID == CHIP_TSUMC||CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)//130604 Modify
		mcuSetSystemSpeed(SPEED_12MHZ_MODE);
		#else
		mcuSetSystemSpeed(SPEED_4MHZ_MODE);
		#endif
		msWriteByteMask(REG_PM_BC, _BIT6, _BIT6);            // mcu clk Live select ROSC
		#if (CHIP_ID != CHIP_TSUMC && CHIP_ID!=CHIP_TSUMD)&&(CHIP_ID!=CHIP_TSUM9)&&(CHIP_ID!=CHIP_TSUMF)// 20130604 nick add
		msWriteByteMask(REG_PM_8D, 0x00, 0xF0);             // pm CLK select RCOSC mux
		#endif
	}
	else
	{
		//PM_printMsg(" \r\n***PM Clock =>XTAL ");
		mcuSetSystemSpeed(SPEED_XTAL_MODE);
		msWriteByteMask(REG_PM_BC, 0, _BIT6);                // mcu clk Live select XTAL
		#if(CHIP_ID != CHIP_TSUMC && CHIP_ID!=CHIP_TSUMD&&CHIP_ID != CHIP_TSUM9&&CHIP_ID != CHIP_TSUMF)// 20130604 nick add
		msWriteByteMask(REG_PM_8D, 0x30, 0xF0);         // pm CLK select xtal
		#endif
	}
	Delay1ms(1);
	msWriteByteMask(REG_1ED1, _BIT4 | _BIT0, _BIT4 | _BIT0); // power down LPLL and MPLL
	msWriteByteMask(SC0_F0, 0, BIT1 | BIT0);
	msWriteByte(SC0_F1, 0x01);
	msWriteByte(SC0_F1, 0x00);
	msWriteByteMask(SC0_F0, BIT4 | BIT1 | BIT0, BIT4 | BIT1 | BIT0);
}
#else
{
	#if PM_CLOCK == RCOSC
	PM_printMsg(" \r\n***PM Clock =>RCOSC ");
	mcuSetSpiSpeed( SPI_CLK_4M );
	mcuSetMcuSpeed( MCU_CLK_4M );
	msWriteByteMask(REG_PM_8D, 0x00, 0xF0); // pm CLK select RCOSC mux
	msWriteByteMask(REG_03A6, 0, _BIT2);    // SW XTAL off
	#else
	PM_printMsg(" \r\n***PM Clock =>XTAL ");
	mcuSetSpiSpeed( SPI_CLK_XTAL );
	mcuSetMcuSpeed( MCU_CLK_XTAL );
	msWriteByteMask(REG_PM_8D, 0x00, 0xF0); // pm CLK select xtal
	msWriteByteMask(REG_PM_A5, 0xff, BIT2); //SET_PM_REG_FORCE_XTAL_ON();
	#endif
	Delay1ms(1);
	msWriteByteMask(REG_1ED1, _BIT4 | _BIT0, _BIT4 | _BIT0); // power down LPLL and MPLL
	msWriteByteMask(SC0_F0, 0, BIT1 | BIT0);
	msWriteByte(SC0_F1, 0x01);
	msWriteByte(SC0_F1, 0x00);
	msWriteByteMask(SC0_F0, BIT4 | BIT1 | BIT0, BIT4 | BIT1 | BIT0);
}
#endif


//**************************************************************************
//  [Function Name]:
//                  msPM_ClearStatus()
//  [Description]
//                  msPM_ClearStatus
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void
msPM_ClearStatus(Bool bResetPM)
{
	msWriteBit(REG_PM_81, TRUE, BIT7);
	msWriteBit(REG_PM_81, 0, BIT7);
	//*********************************************************
	//Software reset PM //Sky110719                       _                             //
	////                                                                 | |                           //
	//Some wake up event just report a pulse    ____| |___,                    //
	//if wake up event keep happen after Wake up status Clear,              //
	//wake up report register will not update status.                               //
	//software reset can solve it                                                           //
	//*********************************************************
	if(bResetPM)
		msWriteBit(REG_PM_83, TRUE, BIT1);
	msWriteBit(REG_PM_83, 0, BIT1);
}

//**************************************************************************
//  [Function Name]:
//                  msPM_EnableDPDetect(BOOL bEnable)
//  [Description]
//                  Enable DP detect
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
#if ENABLE_DP_INPUT
void msPM_EnableDPDetect(BOOL bEnable)//if not enable can reduce 10mA
{
	#if (CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)
	if(bEnable)
	{
		//130524 XD
		//msWriteByteMask(REG_06AE,(bEnable)?0x07:0x00,0x07);
		//msWriteByteMask(REG_07AE,(bEnable)?0x07:0x00,0x07);
	}
	#else
	if(bEnable)
	{
		msWriteByteMask(REG_356D, 0, BIT1);//Disable Power down CDR center bias gen
	}
	else
	{
		msWriteByteMask(REG_356D, BIT1, BIT1);//Power down CDR center bias gen
	}
	#endif
}
#endif
//**************************************************************************
//  [Function Name]:
//                  msPM_XtalEnable()
//  [Description]
//                  In TSUM9 the register for SW enable XTAL has been changed
//                  to PM_B2[4:0] and need password to overwrite.
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
#if (CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)
static void msPM_XtalEnable(BOOL bEn)
{
	if (!ENABLE_XTAL_LESS)
	{
		msWrite2Byte(REG_PM_B0, 0x5566);	// unlock system configuration protection
		if (bEn)
		{
			msWriteByteMask(REG_PM_B2, 0x1F, 0x1F); 	// enable XTAL
			ForceDelay1ms(2);
		}
		else
		{
			msWriteByteMask(REG_PM_B2, 0x00, 0x1F); 	// disable XTAL
		}
		msWrite2Byte(REG_PM_B0, 0xAA99);	// lock system configuration protection
	}
	return;
}
#endif
//**************************************************************************
//  [Function Name]:
//                  msPM_SetPMMode()
//  [Description]
//                  msPM_SetPMMode
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msPM_SetPMMode(void)
{
	#if PM_SUPPORT_ADC_TIME_SHARE
	msWriteBit(REG_PM_FF, 1, BIT2);
	msWrite2ByteMask(REG_DVI_CHEN, 0xE0 | DVI_CTRL_PERIOD, 0xE7 );
	#else
	msWriteBit(REG_PM_FF, 0, BIT2);
	msWrite2ByteMask(REG_DVI_CHEN, 0x00 | DVI_CTRL_PERIOD, 0xE7 );
	#endif
	if (sPMInfo.sPMConfig.bHVSync_enable)
	{
		msPM_EnableHVSyncDetect(TRUE);
	}
	else
	{
		msPM_EnableHVSyncDetect(FALSE);
	}
	if (sPMInfo.sPMConfig.bSOG_enable)
	{
		msPM_EnableSOGDetect(TRUE);
	}
	else
	{
		msPM_EnableSOGDetect(FALSE);
	}
	#if ENABLE_DP_INPUT&&PM_SUPPORT_WAKEUP_DP
	if (sPMInfo.sPMConfig.bDP_enable)
		msPM_EnableDPDetect(TRUE);
	else
		msPM_EnableDPDetect(FALSE);
	#endif
	#if( PM_SUPPORT_WAKEUP_DVI )
	if (sPMInfo.sPMConfig.bDVI_enable)
	{
		msPM_EnableDVIDetect(TRUE);
	}
	else
	{
		msPM_EnableDVIDetect(FALSE);
	}
	#endif  // end of #if( PM_SUPPORT_WAKEUP_DVI )
	if (sPMInfo.ucPMMode == ePM_POWEROFF)
		while (((Key_GetKeypadStatus()^KeypadMask)&KeypadMask) == KEY_POWER); //Wait power key released,avoid power off and the power on again
	if (sPMInfo.sPMConfig.bGPIO_enable)
	{
		msPM_EnableGPIODetect(TRUE);
	}
	else
	{
		msPM_EnableGPIODetect(FALSE);
	}
	if (sPMInfo.sPMConfig.bSAR_enable)
	{
		msPM_EnableSARDetect(TRUE);
	}
	else
	{
		msPM_EnableSARDetect(FALSE);
	}
	if (sPMInfo.sPMConfig.bMCCS_enable)
	{
		msPM_EnableMCCSDetect(TRUE);
	}
	else
	{
		msPM_EnableMCCSDetect(FALSE);
	}
	msPM_MCCSReset();
	#if( PM_SUPPORT_AC2DC )
	if (sPMInfo.sPMConfig.bACtoDC_enable)
	{
		msPM_EnableAC2DC(TRUE);
	}
	else
	{
		msPM_EnableAC2DC(FALSE);
	}
	#endif  // end of #if( PM_SUPPORT_AC2DC )
	if (sPMInfo.sPMConfig.bEDID_enable)
	{
		msPM_Enable_EDID_READ(TRUE);
	}
	else
	{
		msPM_Enable_EDID_READ(FALSE);
	}
	if (sPMInfo.ucPMMode == ePM_POWERON) return;
	//------------------------------------------------------
	#if CHIP_ID <=CHIP_TSUM2
	if (!msPM_StartRCOSCCal())
	{
		PM_printData("CALIBARYION RCOSC FAIL!", 0);
	}
	else
		PM_printData("CALIBARYION RCOSC Success!", 0);
	#endif
	#if 0//CHIP_ID == CHIP_TSUMC
	#if SPI_SSC_EN
	mcuSetSpiSpeed(IDX_SPI_CLK_XTAL);// change to other clock source before  DDR clk pd
	#endif
	#endif
	msPM_PassWord(TRUE);
	msPM_PowerDownMacro();
	msPM_OutputTriState();
	msPM_ClearStatus(FALSE);
	#if ENABLE_DP_INPUT // 20130604 nick add
	DPRXPMForceEnter();
	#endif
	#if 0//ENABLE_DP_INPUT
	DPRxClearAUXVliadStatus();
	#endif
	#if 0//DEBUG_EN
	msPM_UART();
	#endif
//--------------- Sacaler Reset Start--------------------------------
//--------------- Sacaler Reset End--------------------------------
	#if 0//Enable_Cache
	CACHE_DISABLE();//MCU_EnableCache(_DISABLE);
	#endif
	if (sPMInfo.sPMConfig.bMCUSleep)
	{
		msWriteByteMask(REG_PM_A6, 0, _BIT0);
		msPM_SetPMClock(RCOSC);
		msWriteByteMask(REG_PM_AA, _BIT1, _BIT1);//130604 Modify
		msWriteByteMask(REG_PM_A6, _BIT7, _BIT7 | _BIT6); // Enable HW PM mode (Enable mcu gating)
		//Set MCU sleep mode
		PM_printMsg("Enter HW PM Mode");
		msWriteByte(REG_PM_80, 0xA5);
		msWriteByte(REG_PM_80, 0x56);
	}
	else
	{
		//Set MCU no die mode
		msPM_SetPMClock(PM_CLOCK);
		if(PM_CLOCK == XTAL)
			msWriteByteMask(REG_PM_A6, BIT2, _BIT2 | BIT3);
		else if((PM_CLOCK == RCOSC))
		#if ENABLE_DP_INPUT     //111110 modified VS230 PM mode Clock speed
			msWriteByteMask(REG_PM_A6, BIT2, _BIT2 | BIT3);
		#else
		{
			//msWriteByteMask(REG_PM_A6, 0, _BIT2|BIT3);
			msWriteByteMask(REG_PM_A6, _BIT2, _BIT2);
			msWriteByteMask(REG_PM_A6, 0, _BIT2);
			msWriteByteMask(REG_PM_A6, 0, BIT3);
		}
		#endif
		msWriteByteMask(REG_PM_A6, 0, _BIT0);
		msWriteByteMask(REG_PM_A6, _BIT0, _BIT0); //Software power down mode
		#if ENABLE_DP_INPUT
		g_bDoDPInit = FALSE;
		#endif
		sPMInfo.ePMState = ePM_WAIT_EVENT;
		PM_printMsg("Enter SW PM Mode");
		PM_printData("sPMInfo.ePMState %d", sPMInfo.ePMState);
	}
	#if  0//CHIP_ID == CHIP_TSUMD
	msPM0W_Mode_PassWord(TRUE);
	#endif
	#if PM_CABLE_DETECT_USE_SAR
	sPMInfo.bCABLE_SAR_VALUE = CABLE_DET_SAR;
	#endif
}

//**************************************************************************
//  [Function Name]:
//                  msPM_Reset()
//  [Description]
//                  msPM_Reset
//  [Arguments]:
//
//  [Return]:
//      PM status
//
//**************************************************************************
BYTE msPM_Reset(void)
{
	BYTE ucStatus = ePMSTS_INVAID;
	//msPM_EnableAC2DC(FALSE);
	// msWriteByte(SC0_F1, 0);
	//  msWriteByte(REG_1ED1, 0x4);    //MPLL function enable
	// msWriteByte(SC0_F0, 0);
	//  msWriteByteMask(REG_PM_A6, _BIT3|_BIT2|BIT1, _BIT3|_BIT2|BIT1);       //SW XTAL on
	//  msWriteByteMask(REG_01BC, 0, _BIT6);           //Live cLK select XTAL
	// mcuSetSystemSpeed(SPEED_NORMAL_MODE);
	//mcuSetMcuSpeed(MCU_SPEED_INDEX) ; // see function body for detail description
	//mcuSetSpiSpeed(SPI_SPEED_INDEX) ; // see function body for detail description
	//  msWriteByteMask(REG_PM_A6, 0, _BIT7|_BIT0);  // PM SW power down mode  (MCU no die mode)
	//  msWriteByte(SC0_06, 0x00);                  //power up idclk and odclk
	#if 0//Enable_Cache
	CACHE_ENABLE();//MCU_EnableCache(_ENABLE);
	#endif
	msPM_PassWord(FALSE);
	msPM_Init();
	//msPM_SetPMMode();
	msPM_ClearStatus(TRUE);
	msPM_MCCSReset();
	PM_printData("Enter PM ePM_PowerON mode!", 0);
	return ucStatus;
}



#if 1
void msPM_InterruptEnable(Bool benable)
{
	#if (CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD || CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF)
	INT_IRQ_DISP_ENABLE(benable);
	INT_IRQ_DVI_ENABLE(benable);
	#else
	if( benable )
	{
	}
	else
	{
	}
	#endif
}
#endif


#define RECHECK_COUNT_VGA     5
#define RECHECK_COUNT_TMDS    15 // 121026 coding, modified for pattern gen. may output slower when dual output
Bool IsHVSyncActive(BYTE count)
{
	Bool u8Rlt = FALSE;
	WORD u16InputValue;
	BYTE check_cnt;
	for(check_cnt = 0; check_cnt < count; check_cnt++)
	{
		#if	CHIP_ID == CHIP_TSUMC// 20130604 nick modify
		TMDS_Config_For_PM();// TMDS_SETTING(); //20130416
		#endif
		ForceDelay1ms(20);
		u16InputValue = msRead2Byte(SC0_E4) & 0x1FFF;
		if (u16InputValue == 0x1FFF || u16InputValue < 20)
			continue;
		if(labs( (DWORD)u16InputValue - (msRead2Byte(SC0_E4) & 0x1FFF)) > 4) //130604 Modify
			continue;
		u16InputValue = msRead2Byte(SC0_E2) & 0x7FF;
		if (u16InputValue == 0x7FF || u16InputValue < 200)
			continue;
		u8Rlt = TRUE;
		break;
	}
	return u8Rlt;
}
#if MS_VGA_SOG_EN
extern BYTE GetVSyncWidth(void);
#endif
#if (INPUT_TYPE != INPUT_2H) && (INPUT_TYPE != INPUT_1H)&&(INPUT_TYPE != INPUT_1D1H1DP)
Bool msPM_CheckAnalogSyncActive(void)
{
	Bool u8Rlt = TRUE;
	BYTE SyncTYPE = 0;
	#if MS_VGA_SOG_EN
	BYTE ucStatus;
	BYTE w_VSyncWidth;
	#endif
	msWriteByte(SC0_F3, 0x00);// for SOG+video timing can't wake up(no v count)
	msWriteByte(SC0_F0, 0x00);
	msWriteByte(REG_2E02, 0x00);
	msWriteByte(REG_2508, 0x00);
	msWriteByte(REG_2509, 0x00);
	//msWriteByteMask(REG_1EDC, 0, _BIT5|_BIT4);                //Power On MPLL 216MHz/432MHz
	//msWriteByteMask(REG_1ED1,0, _BIT4|_BIT0);               // power on LPLL and MPLL
	msWriteByteMask(REG_1E47, 0x00, BIT0);     //Select clk source
	SrcInputType = Input_VGA; // 120523 coding, check it again
	mStar_SetupInputPort();
	msWriteByteMask(REG_1E3E, 0, BIT0);//Sky110702 Modify for SOG can't Get V Sync
	for (SyncTYPE = 0; SyncTYPE < 2; SyncTYPE++)
	{
		mStar_SetAnalogInputPort(SyncTYPE);
		msWriteByteMask(SC0_ED, 0, BIT5);
		u8Rlt = IsHVSyncActive(RECHECK_COUNT_VGA);
		if(u8Rlt)
		{
			#if MS_VGA_SOG_EN
			ucStatus = SC0_READ_SYNC_STATUS();//msReadByte(SC0_E1);
			if (ucStatus & (SOGP_B) && ucStatus & (CSP_B))
			{
				if (ucStatus & SOGD_B )
				{
					w_VSyncWidth = GetVSyncWidth();
					if (w_VSyncWidth > 15 || w_VSyncWidth == 0) //check SOG pulse width if bigger than 15  //djyang 20080605
					{
						return FALSE;
					}
					msWriteByteMask(SC0_ED, 1, BIT5);
				}
				return TRUE;
			}
			#endif
			return u8Rlt;
		}
	}
	return u8Rlt;
}
#endif
#if CHIP_ID == CHIP_TSUM9 ||  CHIP_ID == CHIP_TSUMF
extern void msInitHDCPProductionKey(void);
#endif

#if( PM_SUPPORT_WAKEUP_DVI )
Bool msPM_CheckDVISyncActive( )
{
	Bool u8Rlt = FALSE;
	#if 1 // // 120523 coding, check it again
	BYTE count;
	msWriteByteMask(REG_1E3E, 0x00, BIT0);
	msWriteByteMask(REG_1E47, 0x00, BIT4 | BIT0);
	#if (CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD)
	msWriteByteMask(REG_01A6, BIT3, BIT3);
	msWrite2Byte(REG_142A, 0x0017);
	msWrite2Byte(REG_17BC, 0x8000);
	msWrite2Byte(REG_17BE, 0x0000);
	msWrite2Byte(REG_01CE, 0x0020);
	#elif CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF
	mcuSetSystemSpeed(SPEED_NORMAL_MODE);
	msTMDSInit();
	msInitHDCPProductionKey();
	#endif
	#if CHIP_ID!=CHIP_TSUMU && CHIP_ID < CHIP_TSUMC
	msWriteByteMask(REG_29FE, 0x00, ~(BIT7 | BIT6));
	#endif
	for(count = 0; count < Input_Nums; count++) // 121026 coding modified for prevent SrcInputType over TMDS input port numbers
	{
		//20130415 for C/D set CLK port fail
		SrcInputType = count;
		if(CURRENT_INPUT_IS_TMDS())
		{
			mStar_SetupInputPort();
			u8Rlt = IsHVSyncActive(RECHECK_COUNT_TMDS);
			if(u8Rlt == TRUE)
			{
				break;
			}
		}
	}
	#if PM_DEBUG
	PM_printData("PM_A2:%x", msReadByte(REG_PM_A2));
	PM_printData("PM_A4:%x", msReadByte(REG_PM_A4));
	PM_printData("u8Rlt:%d", u8Rlt);
	if(u8Rlt == TRUE)
		PM_printData("msPM_CheckDVISyncActive:%d", SrcInputType);
	#endif
	#else
	mStar_SetupInputPort();
	msWriteByteMask(REG_1E3E, 0x00, BIT0);
	msWriteByteMask(REG_1E47, 0x00, BIT4 | BIT0);
	#if CHIP_ID!=CHIP_TSUMU
	msWriteByteMask(REG_29FE, 0x00, ~(BIT7 | BIT6));
	#endif
	if(DVI_DE_STABLE() == TRUE)
		u8Rlt = TRUE;
	u8Rlt = IsHVSyncActive(RECHECK_COUNT);
	#endif
	return u8Rlt;
}
#endif
#if   0//  sahdow_Need test
Bool msPM_CheckDPMCCSActive(void)
{
	Bool bExitPM = TRUE;
	if(msRegs[REG_1FE6]&_BIT7)   //MCCS Interrupt
	{
		//DDC2BI_DP() ;
		if(DDCBuffer[2] == PowerMode)
		{
			if((DDCBuffer[4] == 0x01)
			        && (sPMInfo.ucPMMode == ePM_POWEROFF || sPMInfo.ucPMMode == ePM_STANDBY))
				;
			else  if((DDCBuffer[4] == 0x05) && (sPMInfo.ucPMMode == ePM_STANDBY))
			{
				msPM_Reset();
				PowerOffSystem();
				bExitPM = FALSE;
			}
			else  if((DDCBuffer[4] == 0x05) && (sPMInfo.ucPMMode == ePM_POWEROFF))
			{
			}
			else
				bExitPM = FALSE;
		}
	}
	return bExitPM;
}
#endif
Bool msPM_CheckMCCSActive(void)
{
	Bool bExitPM = TRUE;
	if((ucWakeupStatus == ePMSTS_MCCS01_ACT)
	        && (sPMInfo.ucPMMode == ePM_POWEROFF || sPMInfo.ucPMMode == ePM_STANDBY))
		;
	#if 0//def WH_REQUEST	//130424 Modify fot FQ request 05h command can't do any active
	else  if((ucWakeupStatus == ePMSTS_MCCS05_ACT) && (sPMInfo.ucPMMode == ePM_STANDBY))
	{
		msPM_Reset();
		PowerOffSystem();
		bExitPM = FALSE;
	}
	else  if((ucWakeupStatus == ePMSTS_MCCS05_ACT) && (sPMInfo.ucPMMode == ePM_POWEROFF))
	{
	}
	#endif
	else
		bExitPM = FALSE;
	return bExitPM;
}
Bool msPM_CheckPowerKeyActive(void)
{
	Bool bExitPM = FALSE;
	#if  PM_POWERkEY_GETVALUE
	{
		if(sPMInfo.ucPMMode == ePM_STANDBY)
		{
			msPM_Reset();
			PowerOffSystem();
		}
		else if(sPMInfo.ucPMMode == ePM_POWEROFF)
		{
			bExitPM = TRUE;
		}
	}
	#else
	WORD ucStatus_GPIO;
	ucStatus_GPIO = msRead2Byte( REG_PMGPIO_STS );
	if ( ucStatus_GPIO & (PM_POWERKEY_INT) )//power key
	{
		if(sPMInfo.ucPMMode == ePM_STANDBY)
		{
			//msPM_Reset();
			PowerOffSystem();
		}
		else if(sPMInfo.ucPMMode == ePM_POWEROFF)
			bExitPM = TRUE;
	}
	#endif
	return bExitPM;
}


BOOL msPM_Checkagain(void)
{
	Bool bExitPM = TRUE;
	BYTE GetKeyTemp = 0;
	//volatile WORD ucStatus_GPIO;
	msWriteByte(SC0_F1, 0);
	// msWriteByte(REG_1ED1, 0x4);    //MPLL function enable//130604 Modify
	msWriteByte(SC0_F0, 0);
	msWriteByteMask(REG_PM_A6, _BIT3 | _BIT2 | BIT1, _BIT3 | _BIT2 | BIT1); //SW XTAL on
	ForceDelay1ms(10);//20130512 add mail 20130426
	#if (CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF)
	msPM_XtalEnable(TRUE);		// eanble XTAL
	drvmStar_MpllSrcCfg();
	#endif
	msWriteByteMask(REG_PM_BC, 0, _BIT6);           //Live cLK select XTAL
	mcuSetSystemSpeed(SPEED_NORMAL_MODE);
	msWriteByteMask(REG_PM_A6, 0, _BIT7 | _BIT0); // PM SW power down mode  (MCU no die mode)
	msWriteByte(SC0_06, 0x00);                  //power up idclk and odclk
	#if 0//Enable_Cache
	CACHE_ENABLE();//MCU_EnableCache(_ENABLE);
	#endif
	#if ENABLE_MHL
	if(ucWakeupStatus == ePMSTS_MHL_SOURCE_ACT)
	{
		mapi_mhl_PowerCtrl(MHL_POWER_ON);
		//drvDVI_PowerCtrl(DVI_POWER_ON);
		mStar_SetupInputPort();
		bExitPM = TRUE;//wakeup
	}
	else
	#endif
		if(ucWakeupStatus == ePMSTS_VGA_ACT)
		{
			#if ENABLE_VGA_INPUT
			if(msPM_CheckAnalogSyncActive())
			{
				bExitPM = TRUE;//wakeup
			}
			else
			#endif
				bExitPM = FALSE;
		}
	#if( PM_SUPPORT_WAKEUP_DVI )
		else if(ucWakeupStatus == ePMSTS_DVI_0_ACT || ucWakeupStatus == ePMSTS_DVI_1_ACT || ucWakeupStatus == ePMSTS_MHL_SOURCE_ACT)
		{
			#if ENABLE_MHL
			mapi_mhl_PowerCtrl(MHL_POWER_ON);
			#endif
			if(msPM_CheckDVISyncActive())
			{
				bExitPM = TRUE;//wakeup
			}
			else
				bExitPM = FALSE;
		}
	#endif
		else if(ucWakeupStatus == ePMSTS_GPIO_ACT)
		{
			#if !(PM_POWERkEY_GETVALUE)
			if(msPM_CheckPowerKeyActive())
			{
				bExitPM = TRUE;//wakeup
			}
			else
			#endif
			#if 	PM_CABLEDETECT_USE_GPIO&&ENABLE_DP_INPUT
				if (!(DP_CABLE_NODET))
				{
					SrcInputType = Input_Displayport;
					mStar_SetupInputPort();
					bExitPM = TRUE;
				}
				else
			#endif
					bExitPM = FALSE;
		}
		else if(ucWakeupStatus == ePMSTS_SAR_ACT)
		{
			bExitPM = TRUE;
		}
		else if(ucWakeupStatus == ePMSTS_ITE_POWER_KEY_ACT)
		{
			bExitPM = TRUE;
		}
		else if(ucWakeupStatus == ePMSTS_GPIO_POWER_KEY_ACT)
		{
			bExitPM = TRUE;
		}
	#if ENABLE_AutoDetech
		else if(ucWakeupStatus == ePMSTS_ITE_SOURCE_KEY_ACT)
		{
			if(PowerOnFlag)
			{
				bExitPM = TRUE;
			}
			else
				bExitPM = FALSE;
		}
	#endif
	#if  (FEnterFunction==FEnter_POWER_MENU)||(FEnterFunction==FEnter_POWER_EXIT)
		else if(ucWakeupStatus == ePMSTS_ITE_FACTORY_KEY_ACT)	//120523 Modify
		{
			if(!PowerOnFlag)
				bExitPM = TRUE;
			else
				bExitPM = FALSE;
		}
	#endif
		else if(ucWakeupStatus == ePMSTS_ITE_OSDLOCK_KEY_ACT)	//120524 Modify
		{
			if(!PowerOnFlag)
				bExitPM = TRUE;
			else
				bExitPM = FALSE;
		}
		else if(ucWakeupStatus == ePMSTS_MCCS05_ACT || ucWakeupStatus == ePMSTS_MCCS04_ACT || ucWakeupStatus == ePMSTS_MCCS01_ACT) //20100419
		{
			if(msPM_CheckMCCSActive())
				bExitPM = TRUE;//wakeup
			else
				bExitPM = FALSE;
		}
	#if ENABLE_DP_INPUT&&PM_SUPPORT_WAKEUP_DP
		else if(ucWakeupStatus == ePMSTS_DP_ACT)
		{
			mStar_SetupInputPort();
			#if  0 //  sahdow_Need test
			if(msPM_CheckDPMCCSActive())
				bExitPM = TRUE;
			else
				bExitPM = FALSE;
			#else
			bExitPM = TRUE;
			#endif
		}
	#endif
	#if (PM_POWERkEY_GETVALUE)
		else if(ucWakeupStatus == ePMSTS_POWERGPIO_ACT)
		{
			if(msPM_CheckPowerKeyActive())
			{
				bExitPM = TRUE;//wakeup
				KeypadButton = BTN_Repeat;    //110914 Rick modified
			}
			else
				bExitPM = FALSE;
		}
	#endif
	#if (PM_CABLE_DETECT_USE_SAR)
		else if(ucWakeupStatus == ePMSTS_CABLESAR_ACT)
		{
			if(CABLE_DET_SAR < sPMInfo.bCABLE_SAR_VALUE)
				bExitPM = TRUE;
			else
				bExitPM = FALSE;
		}
	#endif
	#if ENABLE_MHL
		else if(ucWakeupStatus == ePMSTS_MHL_ACT)
		{
			bExitPM = TRUE;
			PM_printData("ePMSTS_MHL_ACT:%d", ePMSTS_MHL_ACT);
		}
	#endif
	#if ENABLE_ANDROID_IR	//131008 Modify
		else if(ucWakeupStatus == ePMSTS_IR_PowerKEY_ACT) //
		{
			bExitPM = TRUE;
		}
	#endif
		else
			bExitPM = FALSE;
	//    bExitPM = TRUE;//wakeup
	return bExitPM;
}

Bool PM_CheckKeypadStatus(BYTE KeypadStatus)
{
	bit bresult = FALSE;
	if( KeypadStatus)
	{
		#if ENABLE_AutoDetech
		if(KeypadStatus == KEY_EXIT)
		{
			{
				ucWakeupStatus = ePMSTS_ITE_SOURCE_KEY_ACT;
				bresult = TRUE;
			}
		}
		else
		#endif
			if (KeypadStatus == KEY_POWER)
			{
				{
					ucWakeupStatus = ePMSTS_ITE_POWER_KEY_ACT;
					bresult = TRUE;
				}
			}
		#if  (FEnterFunction==FEnter_POWER_MENU)||(FEnterFunction==FEnter_POWER_EXIT)
			else if ((KeypadStatus == KEY_FACTORY) && (!PowerOnFlag))	//120523 Modify
			{
				ucWakeupStatus = ePMSTS_ITE_FACTORY_KEY_ACT;
				bresult = TRUE;
			}
		#endif
	}
	return bresult;
}
//**************************************************************************
//  [Function Name]:
//                  msPM_WaitingEvent()
//  [Description]
//                  msPM_WaitingEvent
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
#define SAR_KEY_TH      0x30
void
msPM_WaitingEvent(void)
{
	BYTE GetKeyTemp = 0;
	// msPM_InterruptEnable(FALSE);
	//msPM_ClearStatus(TRUE); // 120209 coding reserved. PM sw mode, after disable xtal, it should not reset PM
	#if ENABLE_DEBUG
	printMsg("msPM_WaitingEvent.....");
	#endif
	while(1)
	{
		#if ENABLE_DEBUG
		DebugHandler();
		if ( DebugOnlyFlag )
			continue;
		#endif
		#ifdef UseVGACableReadWriteAllPortsEDID
		#endif
		{
			if( SyncLossState() && IsCableNotConnected() )
			{
				hw_SetDDC_WP();//petit 20121123 for TPV new request
			}
		}
		Main_SlowTimerHandler();
		//120521 Modify
		if( !TPDebunceCounter )
		{
			TPDebunceCounter = SKPollingInterval;
			GetKeyTemp =  (Key_GetKeypadStatus() ^ KeypadMask) &KeypadMask;//Key_GetKeypadStatus();
			if(PM_CheckKeypadStatus(GetKeyTemp))
				break;
		}
		#if ENABLE_ANDROID_IR	//131008 Modify
		IR_PM_KeyPadStatus = ( IR_GetIRKeypadStatus() ^ KeypadMask ) & KeypadMask;
		//PM_printData("IR_PM_KeyPadStatus %x",IR_PM_KeyPadStatus );
		if(IR_PM_KeyPadStatus == KEY_POWER)
		{
			ucWakeupStatus = ePMSTS_IR_PowerKEY_ACT;
			break;
		}
		#endif
		#if ENABLE_MHL&&CHIP_ID==CHIP_TSUM2	//130605 nick
		if(MHL_CHECK_CONDITION())
		{
			if(mdrv_mhl_WakeupDetect())
			{
				ucWakeupStatus = ePMSTS_MHL_SOURCE_ACT;
				PM_printMsg("MHL Detect Wakup");
				break;
			}
		}
		#endif
		#if  Enable_CheckVcc5V
		if ( CheckVCC5V() )
			break;
		#endif
		if(msPM_GetPMStatus())
			break;
		#if 0//!DEBUG_EN
		if(DDCCI_CheckDMPSON())
			break;
		#endif
		/*   if((ForceEnterPowerOffFlag)&&(PowerOnFlag))
		   {
		       Clr_ForceEnterPowerOffFlag();
		       //ExecuteKeyEvent(MIA_Power);
		       KeypadButton = BTN_Nothing;
		    ucWakeupStatus = ePMSTS_ITE_POWER_KEY_ACT;
		       break;

		   }*/
	}
	PM_printData("\r\nPM Wakeup Event1 (%d) !", ucWakeupStatus);
	//msPM_InterruptEnable(TRUE);
}


#if 0
void   msPM_SetupWakeUpFunc( void )
{
#define _PMMETA  sPMInfo.sPMConfig
	msPM_printConfiguration();
	msPM_EnableHVSyncDetect(_PMMETA.bHVSync_enable);
	msPM_EnableSOGDetect(_PMMETA.bSOG_enable);
	msPM_EnableGPIODetect(_PMMETA.bGPIO_enable);
	msPM_EnableSARDetect(_PMMETA.bSAR_enable);
	msPM_EnableMCCSDetect(_PMMETA.bMCCS_enable);
	msPM_Enable_EDID_READ(_PMMETA.bEDID_enable);
	#if( PM_SUPPORT_AC2DC )
	msPM_EnableAC2DC(_PMMETA.bACtoDC_enable);
	#endif  // end of #if( PM_SUPPORT_AC2DC )
	#if( PM_SUPPORT_WAKEUP_DVI )
	msPM_EnableDVIDetect(_PMMETA.bDVI_enable);
	#endif  // end of #if( PM_SUPPORT_WAKEUP_DVI )
	#if (!PM_SUPPORT_SOG_TIME_SHARE) && (!PM_SUPPORT_DVI_TIME_SHARE)
	msPM_EnableDVIClockAmp(FALSE);
	#elif PM_SUPPORT_DVI_TIME_SHARE
	if( !_PMMETA.bDVI_enable )
		msPM_EnableDVIClockAmp(FALSE);
	#elif PM_SUPPORT_SOG_TIME_SHARE
	if( !_PMMETA.bSOG_enable )
		msPM_EnableDVIClockAmp(FALSE);
	#else
	if( (!_PMMETA.bSOG_enable) && (!_PMMETA.bDVI_enable) )
		msPM_EnableDVIClockAmp(FALSE);
	#endif
#undef _PMMETA
}
#endif

//**************************************************************************
//  [Function Name]:
//                  msPM_Handler()
//  [Description]
//                  msPM_Handler
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void  msPM_Handler(void)
{
	switch(sPMInfo.ePMState)
	{
		case ePM_ENTER_PM:
			#if( ENABLE_WATCH_DOG )	//130716 xiandi follow demo code
			Init_WDT( _DISABLE );
			#endif
			msPM_SetPMMode();
			break;
		case ePM_WAIT_EVENT:
			msPM_WaitingEvent();
			if(msPM_Checkagain())
				sPMInfo.ePMState = ePM_EXIT_PM;
			else
				sPMInfo.ePMState = ePM_ENTER_PM;
			break;
		case ePM_EXIT_PM:
			#if DEBUG_PRINTDATA
			printMsg("ePM_EXIT_PM   Enter");
			#endif
			msPM_Reset();
			msPM_PowerUpMacro();
			#if ENABLE_DisplayPortTX
			gDPTXInfo.bReTraining = 1;
			#endif
			sPMInfo.ePMState = ePM_IDLE; // 121011 coding, check it again, moves to here for power off set
			// 121026 coding modified for wakeup priority
			if(PowerOnFlag) // wakeup form power saving
			{
				#if !PM_POWERSAVING_WAKEUP_GPIO	//121108 Modify
				if (ucWakeupStatus == ePMSTS_ITE_POWER_KEY_ACT
			        #if ENABLE_ANDROID_IR //Modify HDMI Source Powersaving Press IR Power don't DC ON Issue 20150316 Alpha
				        || ucWakeupStatus == ePMSTS_IR_PowerKEY_ACT
			        #endif
				   )
				{
					ExecuteKeyEvent( MIA_Power);
					KeypadButton = BTN_Repeat;
				}
				else
				#else
				if (ucWakeupStatus == ePMSTS_GPIO_POWER_KEY_ACT)
				{
					ExecuteKeyEvent( MIA_Power);
					KeypadButton = BTN_Repeat;
				}
				else
				#endif
				#if ENABLE_AutoDetech
					if (ucWakeupStatus == ePMSTS_ITE_SOURCE_KEY_ACT)
					{
						Set_PowerSavingFlag();
						mStar_PowerUp();
						ExecuteKeyEvent( MIA_SourceSel );
						OsdCounter = UserPrefOsdTime;	//120523 Modify
					}
					else
				#endif
						if((ucWakeupStatus == ePMSTS_VGA_ACT)
					        #if( PM_SUPPORT_WAKEUP_DVI )
						        || (ucWakeupStatus == ePMSTS_DVI_0_ACT)
						        || (ucWakeupStatus == ePMSTS_DVI_1_ACT)
					        #endif
					        #if ENABLE_DP_INPUT	//121130 Modify
						        || (ucWakeupStatus == ePMSTS_DP_ACT)
					        #endif
					        #if ENABLE_MHL//130703 nick
						        || (ucWakeupStatus == ePMSTS_MHL_ACT)
					        #endif
						  )
						{
							Power_PowerOnSystem();
							if(ucWakeupStatus != ePMSTS_VGA_ACT && UserPrefInputType == Input_VGA)
							{
								SrcInputType = Input_VGA;
								mStar_SetupInputPort();
								ucWakeupStatus = ePMSTS_VGA_ACT;
							}
						}
			}
			else // wakeup from dc off
			{
				#if  (FEnterFunction==FEnter_POWER_MENU)||(FEnterFunction==FEnter_POWER_EXIT)
				if (ucWakeupStatus == ePMSTS_ITE_FACTORY_KEY_ACT)	//120523 Modify
				{
					Set_FactoryModeFlag();
					Set_BurninModeFlag();
					Set_DoBurninModeFlag();
					#if !USEFLASH
					NVRam_WriteByte(nvrMonitorAddr(MonitorFlag), MonitorFlags);
					#else
					SaveMonitorSetting();
					#endif
				}
				#endif
				PowerOnSystem();
			}
			//sPMInfo.ePMState = ePM_IDLE; // 121011 coding, check it again, moves to upper position for power off
			#if( ENABLE_WATCH_DOG )	//130716 xiandi follow demo code
			Init_WDT( _ENABLE );
			WDT_CLEAR();
			#endif
			break;
		case ePM_IDLE:
		default:
			break;
	}
}

#if (CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF)
void msPM_Exit(void)
{
	msWriteByte(REG_PM_A6, 0x0E); //turn on core power
	msPM_PassWord(FALSE);
}
#endif



#endif





