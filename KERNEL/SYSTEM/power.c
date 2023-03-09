#include "types.h"
#include "board.h"
#include "global.h"
#include "ms_reg.h"
#include "panel.h"
#include "misc.h"
#include "ms_rwreg.h"
#include "mstar.h"
#include "debug.h"
#include "msOsd.h"
#include "msosdfunction.h"
#include "menudef.h"
#include <math.h>
#include "GPIO_DEF.h"
#include "drvgpio.h"

#if ENABLE_HDCP
#include "MsHDCP.h"
#endif ///#if UseHDCP
#include "adjust.h"

#if MS_PM
#include "MS_PM.h"
#endif
#if PanelminiLVDS || PANEL_VCOM_ADJUST	//110229 Modify
#include "msMiniLVDSI2c.h"
#endif
////////////////////////////////////////////////////
//#include "drvPower.h" // the function moves to drvmStar
#include "drvmStar.h"
///////////////////////////////////////////////////

#define TurnOffOSD      1
void Power_TurnOffLed(void);
void Power_TurnOnGreenLed(void);
void Power_TurnOnAmberLed(void);

void Power_TurnOffPanel(void);
void Power_PowerOffSystem(void);
void DrawOsdMenu(void);
extern Bool PowerOffSystem( void );



//=============================================
// Control system power status
// caller : main()
void Power_PowerHandler(void)
{
	if (ForcePowerSavingFlag)
	{
		Clr_ForcePowerSavingFlag(); // clear force power saving flag
		if (!PowerSavingFlag)
		{
			if (PowerOnFlag)
			{
				#if ENABLE_DP_INPUT && (CHIP_ID == CHIP_TSUM9 ||CHIP_ID == CHIP_TSUMF)
				if(DPRXCheckDPMS()) // Do not into power saving when CTS
				{
					Clr_ForcePowerSavingFlag();
					return;
				}
				#endif
				#if PowerSaveLedFlicker_Enable
				//Power_TurnOnGreenLed();
				#else
				Power_TurnOnAmberLed();
				#endif
				{
					//130821 jb
					Power_PowerOffSystem();
					#if (MS_PM)
					#if ESaverPowerDownFunc	//120612 Modify
					if(ESaverPowerDownCounter == 0)
					#endif
					#if ENABLE_MHL
						if(!GET_MHL_CABLE_PLUGGED())
					#endif
							msPM_SetFlag_Standby();
					#endif
				}
			}
			else
			{
				PowerOffSystem();
			}
		}
	}
}
#if 1
#if AudioFunc
extern void mStar_AdjustVolume(BYTE volume);
#endif
void Power_PowerOnSystem(void)
{
	gBoolVisualKey = 0;
	gByteVisualKey = 0xff;
	Power_TurnOffPanel();
	mStar_PowerUp();
	Clr_PowerSavingFlag();
	Set_InputTimingChangeFlag();
	#if Dual
	if (!(FactoryModeFlag))
		Set_ShowInputInfoFlag();
	#endif
	#if EANBLE_NEW_DCR_Functing
	DCR_Counter = 0;
	Clr_EanbleClearBalclightStartFlag();
	Clr_DoClearBalclightFlag();
	#endif
	SwitchPortCntr = 0; // 071226
	SrcFlags |= SyncLoss;
}
void Power_PowerOffSystem(void)
{
	#if AudioFunc // 120426 coding modified for audio control
	mStar_AdjustVolume(0);
	hw_SetAudio_SD();
	#if ENABLE_HDMI
	mstar_HDMIAudioMute(0);
	#endif
	hw_SetMute();
	#endif
	Power_TurnOffPanel();
	mStar_PowerDown();
	Set_PowerSavingFlag();
	Clr_InputTimingChangeFlag();
	OsdCounter = 0;
	PowerDownCounter = 0;	//120601 Modify
	Clr_OsdTimeoutFlag();
	Clr_DoModeSettingFlag();		//110311 Modify
	Set_InputTimingStableFlag();	//110311 Modify
	#if Enable_Rotate180Func
	ForceDelay1ms(100);
	#endif
	#if ENABLE_DEBUG
	printMsg("Power_PowerOffSystem ");
	#endif
	#if EANBLE_NEW_DCR_Functing
	DCR_Counter = 0;
	Clr_EanbleClearBalclightStartFlag();
	Clr_DoClearBalclightFlag();
	#endif
	//UserPrefInputType = SrcInputType; // 120523 coding, check it again
}
#endif
void Power_TurnOffLed(void)
{
	hw_ClrGreenLed();
	hw_ClrAmberLed();
}
void Power_TurnOnGreenLed(void)
{
	#if FactoryLedFlicker_Enable
	#else
	if(FactoryModeFlag)
	{
		hw_SetAmberLed();
		hw_ClrGreenLed();
	}
	else
	#endif
	{
		hw_ClrAmberLed();
		hw_SetGreenLed();
	}
}

//void Power_TurnOffGreenLed(void)
//{ hw_ClrGreenLed();
//}
void Power_TurnOnAmberLed(void)
{
	hw_ClrGreenLed();
	hw_SetAmberLed();
}

void Power_TurnOnPanel(void)
{
	while(bPanelDelayFlag)	//110421 Modify
	{
		if(InputTimingChangeFlag && !DisplayLogoFlag)
		{
			return;
		}
	}
	#if ENABLE_DEBUG
	printMsg("33333333333333333333");
	#endif
	Set_PanelOnFlag();
	#if ENABLE_RTE // 081124 od modified
	//msOD_Reset(_OD_Enable);
	#endif
	mStar_BlackWhiteScreenCtrl(BW_SCREEN_BLACK);
	hw_SetPanel();
	#if PANEL_VCOM_ADJUST		//120607 Modify
	HW_SET_VCOM_I2C_SDA();
	HW_SET_VCOM_I2C_SCL();
	#endif
	#if !ENABLE_DisplayPortTX // Leger eDP Tx output without this process to improve display time
	ForceDelay1ms( PanelOnTiming1 );
	#if MainBoardType==	MainBoard_JRY_O58FHG_BV1
	ForceDelay1ms(30);
	#endif
	Power_ModCtrl(_ENABLE);
	#if !PANEL_TCON_CONFIG_LVDS_IMPEDANCE// Delay time  less  20130819 jb move
	if( !iGenTuningFinished )
	{
		I_Gen_Tuning();
	}
	#endif
	#if DisplayPowerOnLogo
	if(DisplayLogoFlag)
		mStar_AdjustBrightness(DefBrightness);
	else
	#endif
		if (SyncLossState())
			mStar_AdjustBrightness(100);
		else
			mStar_AdjustBrightness(UserPrefBrightness);
	#if PANEL_VCOM_ADJUST			//R/W VCOM After 500ms 	130311 Modify
	if(PanelOnTiming2 >= 500)
		ForceDelay1ms( PanelOnTiming2 );
	else
		ForceDelay1ms( 500 );
	#else
	ForceDelay1ms( PanelOnTiming2 );
	#endif
	#endif
	#if PANEL_TCON_CONFIG_LVDS_IMPEDANCE// Delay time  less  20130819 jb move
	if( !iGenTuningFinished )
	{
		I_Gen_Tuning();
		ForceDelay1ms(300);	//130826 xiandi for AC on logo garbage
	}
	#endif
	#if ENABLE_TOUCH_PANEL_CTRL
	hw_Set_TouchPanel();
	#endif
	mStar_BlackWhiteScreenCtrl(BW_SCREEN_OFF);
	#if PanelminiLVDS||PANEL_VCOM_ADJUST	//110229 Modify
	#if PANEL_VCOM_ADJUST			//	For Turn on panel  R/W Vcom	130311 Modify
	#else
	if(g_bACPowerOn_CheckVCOM)
	#endif
	{
		#if VCOM_TYPE == VCOM_MAXIM	|| VCOM_TYPE == VCOM_SMIM ||VCOM_TYPE == VCOM_TPSIM	//120322 Modify
		WORD ucReg;
		#else
		BYTE ucReg;
		#endif
		ucReg = msReadMiniLVDSi2c_Vcom();
		if (ucReg != FactorySetting.VcomValue)
		{
			msWriteMiniLVDSi2c_Vcom(FactorySetting.VcomValue);
		}
		#if PANEL_VCOM_ADJUST			//	For Turn on panel  R/W Vcom	130311 Modify
		#else
		g_bACPowerOn_CheckVCOM = FALSE;
		#endif
	}
	#endif
	if (InputTimingChangeFlag && !DisplayLogoFlag)
	{
		Power_TurnOffPanel();
	}
	else
	{
		hw_SetBlacklit();
	}
	#if ENABLE_DEBUG
	printMsg("power turn on panel");
	#endif
}
#if TURNOFF_PANEL_BEFORE_DISABLE_LVDS_OUTPUT		//120703 Modify
void Power_TurnOffPanel( void )
{
	if( !PanelOnFlag )
		return;
	Clr_PanelOnFlag();
	#if TurnOffOSD
	Osd_DoubleBuffer(FALSE);
	Osd_Hide();
	mStar_ScalerDoubleBuffer(FALSE);
	Delay4us();
	#endif
	hw_ClrBlacklit();
	ForceDelay1ms( PanelOffTiming1 );
	#if !NormalWhite
	mStar_BlackWhiteScreenCtrl(BW_SCREEN_BLACK);
	#else
	mStar_BlackWhiteScreenCtrl(BW_SCREEN_WHITE);
	#endif
	ForceDelay1ms( PanelOffTiming2);
	hw_ClrPanel();
	ForceDelay1ms( 100 );
	Power_ModCtrl(_DISABLE);
	mStar_BlackWhiteScreenCtrl(BW_SCREEN_OFF);
	#if TurnOffOSD
	Osd_DoubleBuffer(TRUE);
	#endif
	PanelOffOnDelayCntr = PanelOffOnDelay;
	bPanelDelayFlag = 1;
}
#elif AFTER_DISABLE_PANEL_POWER_INSERT_WHITE
void Power_TurnOffPanel( void )
{
	if( !PanelOnFlag )
		return;
	Clr_PanelOnFlag();
	#if TurnOffOSD
	Osd_DoubleBuffer(FALSE);
	Osd_Hide();
	mStar_ScalerDoubleBuffer(FALSE);
	Delay4us();
	#endif
	hw_ClrBlacklit();
	ForceDelay1ms( PanelOffTiming1 );
	mStar_BlackWhiteScreenCtrl(BW_SCREEN_WHITE);
	ForceDelay1ms( PanelOffTiming2);
	hw_ClrPanel();
	ForceDelay1ms( 300 );	//121212 Modify
	Power_ModCtrl(_DISABLE);
	mStar_BlackWhiteScreenCtrl(BW_SCREEN_OFF);
	#if TurnOffOSD
	Osd_DoubleBuffer(TRUE);
	#endif
	PanelOffOnDelayCntr = PanelOffOnDelay;
	bPanelDelayFlag = 1;
}
#elif LVDS_OUTPUT_DO_NOT_TURNOFF_PANEL_POWER
void Power_TurnOffPanel(void)
{
	// 080123
	if(!PanelOnFlag)
		return;
	Clr_PanelOnFlag();
	#if TurnOffOSD
	Osd_DoubleBuffer(FALSE);
	Osd_Hide();
	mStar_ScalerDoubleBuffer(FALSE);
	Delay4us();
	#endif
	hw_ClrBlacklit();
	ForceDelay1ms( PanelOffTiming1 );
	mStar_BlackWhiteScreenCtrl(BW_SCREEN_WHITE);
	ForceDelay1ms( PanelOffTiming2 );
	hw_ClrPanel();
	ForceDelay1ms( 90);//( 70 );
	mStar_BlackWhiteScreenCtrl(BW_SCREEN_OFF);
	Power_ModCtrl(_DISABLE);
	// hw_ClrPanel();
	#if TurnOffOSD
	Osd_DoubleBuffer(TRUE);
	#endif
	PanelOffOnDelayCntr = PanelOffOnDelay;
	bPanelDelayFlag = 1;
}


#else
void Power_TurnOffPanel(void)
{
	// 080123
	if(!PanelOnFlag)
		return;
	Clr_PanelOnFlag();
	#if TurnOffOSD
	Osd_DoubleBuffer(FALSE);
	Osd_Hide();
	mStar_ScalerDoubleBuffer(FALSE);
	Delay4us();
	#endif
	hw_ClrBlacklit();
	ForceDelay1ms( PanelOffTiming1 );
	#if 1//!NormalWhite
	mStar_BlackWhiteScreenCtrl(BW_SCREEN_BLACK);
	#else
	mStar_BlackWhiteScreenCtrl(BW_SCREEN_WHITE);
	#endif
	ForceDelay1ms( 80 );
	mStar_BlackWhiteScreenCtrl(BW_SCREEN_OFF);
	#if MainBoardType==MainBoard_W58CDT9_JV1||MainBoardType==MainBoard_MST9570S_DEMO||MainBoardType==MainBoard_WO587HT9_JV1||MainBoardType==MainBoard_JRY_O58FHG_BV1||MainBoardType==MainBoard_JRY_WQ570||MainBoardType == MainBoard_JRY_L58CDT9_PV1||MainBoardType==MainBoard_JRY_W58CDT9_GV3||MainBoardType==MainBoard_JRY_L58CDT9_EV1||MainBoardType==MainBoard_TSUMO58FDT9_1	||MainBoardType==MainBoard_JRY_W58CDT9_AV6//for panel 5v have 120ms delay tina 20170517
	hw_ClrPanel();
	ForceDelay1ms( PanelOffTiming2 );
	Power_ModCtrl(_DISABLE);
	#else
	Power_ModCtrl(_DISABLE);
	#if PANEL_VCOM_ADJUST		//120607 Modify
	HW_CLR_VCOM_I2C_SCL();
	HW_CLR_VCOM_I2C_SDA();
	#endif
	ForceDelay1ms( PanelOffTiming2 );
	hw_ClrPanel();
	#endif
	#if TurnOffOSD
	Osd_DoubleBuffer(TRUE);
	#endif
	PanelOffOnDelayCntr = PanelOffOnDelay;
	bPanelDelayFlag = 1;
}

#endif

