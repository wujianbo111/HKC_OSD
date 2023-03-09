#include "types.h"
#include "board.h"
#include "global.h"
#include "mcu.h"
#include "detect.h"
#include "menu.h"
#include "ms_reg.h"
#include "power.h"
#include "debug.h"
#include "ms_rwreg.h"
#include "msosd.h"
#include "misc.h"
#include "NVRam.h"
#include "mstar.h"
#include "UserPref.h"
#include "keypad.h"
#include "Panel.h"
#include "msflash.h"  //2006-03-20
#include "ddc2bi.h"
#include "menudef.h"//071226
#include "keypaddef.h"
#if DDCCI_ENABLE   || AudioFunc
#include "adjust.h"
#endif
#if MWEFunction
#include "MsDLC.h"
#include "MsACE.h"
#endif

#if ENABLE_RTE
#include "drvmsovd.h"
#endif

#if ENABLE_HDMI
#include "MsHDMI.h"
#endif
#if 1	//#ifdef ReduceDDC   For WH_REQUEST
#include "ddc.h"
#endif
#if MS_DAC
#include "drvDAC.h"
#endif
#if MS_PM
#include "MS_PM.h"
#endif

#if ENABLE_DisplayPortTX
#include "drvDPTxApp.h"
#endif


////////////////////////////////////
//#include "drvMcu.h"
///////////////////////////////////
#include "GPIO_DEF.h"

#if  ENABLE_ANDROID_IR	//131008 Modify
#include "drv_Ir.h"
#endif

#define Main_DEBUG    0
#if ENABLE_DEBUG&&Main_DEBUG
#define Main_printData(str, value)   printData(str, value)
#define Main_printMsg(str)           printMsg(str)
#else
#define Main_printData(str, value)
#define Main_printMsg(str)
#endif

void Init_Device(void);
void Main_SlowTimerHandler(void);
extern void Init_GlobalVariables(void);
extern void NVRAM_i2C_Intial(void); //2006/03/20
//extern WORD ReadFlashID(DWORD address);

extern BYTE xdata PowerDownCounter;
#if ENABLE_DeltaE
extern BYTE xdata bToolWriteGamma;
#endif
#if ENABLE_HDCP
#if HDCPKEY_IN_Flash
extern void msInitHDCPProductionKey(void);
#endif
#endif

#if 1// 110915 coding def OffPower           //090331 xiandi.yu Auto Off Power
extern PowerOffSystem(void);
#endif

#if Enable_CheckVcc5V
extern Bool CheckVCC5V ( void );
#endif

//extern BYTE Second;

#if ((CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF)&& ENABLE_CABLE_5V_EDID)
void ReadHdcpEdidInFlashSetting(void)
{
	FLASH_HDCP_EDIDAddr = FDATA_HDCPKEY_START_ADDR;
}
#endif



#if AudioFunc

#if All_AudioDet

void CheckEarphoneDetStatus(void)
{
	if (HarphoneDet_Pin)
	{
		if(bAudioInputStatus == AudioInput_Spk)
		{
			#if DEBUG_MSG
			printMsg("change to ear");
			#endif
			Delay1ms(1);
			if (HarphoneDet_Pin)
			{
				#if SWAP_LR_CHANNL
				#if CHIP_ID==CHIP_TSUMU
				msWriteByte(REG_2C05, 0x00);
				#else
				#endif
				#endif
				Set_EarphoneDetStatusChangeFlag();
				bAudioInputStatus = AudioInput_Ear;
			}
		}
	}
	else
	{
		if(bAudioInputStatus == AudioInput_Ear)
		{
			Delay1ms(1);
			if (HarphoneDet_Pin)
			{
				;
			}
			else
			{
				#if DEBUG_MSG
				printMsg("change to spk");
				#endif
				#if SWAP_LR_CHANNL
				#if CHIP_ID==CHIP_TSUMU
				msWriteByte(REG_2C05, 0x10);
				#else
				#endif
				#endif
				msAudioLineOutGain( Def_DACGain );
				msAudioEARout_Mute( FALSE );
				Set_EarphoneDetStatusChangeFlag();
				bAudioInputStatus = AudioInput_Spk;
			}
		}
	}
}




void Volume_EarphoneDetHander(void)
{
	CheckEarphoneDetStatus();
	if(EarphoneDetStatusChangeFlag)
	{
		#if DEBUG_MSG
		printMsg("change to audio");
		#endif
		mStar_AdjustVolume(UserPrefVolume);
		Clr_EarphoneDetStatusChangeFlag();
	}
}
#endif


#endif



void main(void)
{
	#if Enable_CheckVcc5V
Restart:
	#endif
	#if (CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)
	#if ENABLE_CABLE_5V_EDID
	ReadHdcpEdidInFlashSetting();
	#endif
	drvmStar_PowerOnInit();
	#if (CHIP_ID == CHIP_TSUMF)
	MPLL_CLOCK_ADC(TRUE);
	#endif
	#endif
	#if ENABLE_DP_INPUT
	gDPInfo.bDPSave = 1;
	g_bDoDPInit = TRUE;
	#endif
	Init_MCU();
	#if (CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)
	if (!g_bFROTrimResult)
		Main_printMsg("FRO trim failed!");
	#endif
	#if( ENABLE_WATCH_DOG )	//130716 xiandi follow demo code
	WDT_CLEAR();
	#endif
	ForceDelay1ms(100); // 100802 coding, wait for system power stable then execute scalar setting
	ScalerReset();
	mcuSetSystemSpeed(SPEED_NORMAL_MODE);
	Delay1ms( 100 );
	GPIOPWMSelect();
	g_ucFlashID = ReadFlashID();
	#if !USEFLASH
	NVRAM_i2C_Intial();
	#endif
	#if DisplayPowerOnLogo
	UserPrefLogoON = 1;	//120420 Modify
	#endif
	#if  Enable_CheckVcc5V
	if ( CheckVCC5V() )
		goto Restart;
	#endif
	ReadMonitorSetting(); //Benz 2007.4.23   19:11:22
	mStar_InitDDC(); // 2017/02/20
	mStar_Init(); //2006-03-07
	#if  (MS_PM)
	msPM_Init();
	#endif
	#if (FEnterFunction==FEnter_AC_MENU)
	CheckFactoryKeyStatus();
	#endif
	Init_GlobalVariables();
	Menu_InitVariable();
	Init_Device();
	DDC2Bi_Init();
	#if ENABLE_FACTORY_BLACKLEVEL  ||   ENABLE_DDCCI_BLACKLEVEL
	mStar_AdjustUserPrefBlacklevel(UserprefRedBlackLevel, UserprefGreenBlackLevel, UserprefBlueBlackLevel);
	#else
	mStar_AdjustUserPrefBlacklevel(DefRedBlackLevel, DefGreenBlackLevel, DefBlueBlackLevel);
	#endif
	#if ENABLE_MHL
	mapi_mhl_init();
	#endif
	do
	{
		#if	(MS_PM)
		while(1)
		{
			msPM_Handler();
			if(msPM_IsState_IDLE())break;
		}
		#endif
		while(1)
		{
			#if Enable_CheckVcc5V
			if ( CheckVCC5V() )   goto Restart;
			#endif
			DebugHandler();
			if(DebugOnlyFlag)
				continue;
			#if( ENABLE_WATCH_DOG )	//130702 xiandi
			WDT_CLEAR();//ClearWDT();
			#endif
			DDC2Bi_CommandHandler();
			Main_SlowTimerHandler();
			#if JRY_Color_Tool_Functing
			if (ATEModeFlag)
				continue;
			#if LoadAllPortSeriealnumberByOneVGAPort
			if(DDCCOneVGAPortLoadEDIDFlag && !ATEModeFlag)
			{
				hw_ClrAmberLed();
				hw_ClrGreenLed();
				ReLoadEDIDtoAddSN();
				Clr_DDCCOneVGAPortLoadEDIDFlag();
			}
			#endif
			#if WriteSN_Functiom_New
			if(DDCCIReadLoadEDIDFlag) break;
			#elif JRY_FDDCCI_WriteEDID
			if (DDCCIReadLoadEDIDFlag && DDCCILoadEDIDCount % 3 == 0)
			{
				mStar_InitDDC();
				#if ENABLE_DP_INPUT
				DPRxEDIDLoad();
				#endif
				Clr_DDCCIReadLoadEDIDFlag();
				DDCCILoadEDIDCount = 0;
			}
			#endif
			#endif
			#if ENABLE_DeltaE
			if(bToolWriteGamma) //nick add for avoid delta-E fail 20131122
				continue;
			#endif
			#if 0//def UseVGACableReadWriteAllPortsEDID
			#if ENABLE_DP_INPUT||ENABLE_MHL	//121228 Modify
			if(LoadEDIDFlag)
			{
				#if ENABLE_DP_INPUT
				DPRxEDIDLoad();
				#endif
				#if ENABLE_MHL
				mapi_mhl_init();
				#endif
				Clr_LoadEDIDFlag();
			}
			#endif
			if(WriteDeviceFlag)
				continue;
			#endif
//3这是DDCCI烧录HDCP，我们不需要使用
			#if 0//ENABLE_HDCP
			#if HDCPKEY_IN_Flash
			if (WriteHDCPcodeFlag)
				continue;
			if (LoadHDCPKeyFlag)
			{
				msInitHDCPProductionKey();
				Clr_LoadHDCPKeyFlag();
				#if ENABLE_DP_INPUT	//121228 Modify
				DPRxHDCPLoadKey();
				#endif
			}
			#endif
			#endif
			Power_PowerHandler();
			#if (MS_PM)
			if(!msPM_IsState_IDLE())break;
			#endif
			if (!ModeDetectCounter || InputTimingChangeFlag)
			{
				mStar_MonitorInputTiming();
				ModeDetectCounter = 20;
			}
			mStar_ModeHandler();
			#if(CHIP_ID==CHIP_TSUM9)
			#if (ENABLE_HDMI || ENABLE_DVI)
			drv_TMDS_DATA_ALIGN();
			#endif
			#endif
			#if ENABLE_HDMI
			mstar_HDMIHandler();
			#endif
			#if ENABLE_DP_INPUT
			if (CURRENT_INPUT_IS_DISPLAYPORT())
				DPRxHandle();             // DP hander
			#endif
			#if ENABLE_DisplayPortTX
			//if( !SyncLossState() )
			DPTxHandle();
			#endif
			#if MS_DAC
			#if (CHIP_ID==CHIP_TSUMC ||CHIP_ID==CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)
			msDACInitStep();
			#endif
			msAudioGainToggle();
			#endif
			Menu_OsdHandler();
			#if (MS_PM)
			if(!msPM_IsState_IDLE())break;
			#endif
			#if MWEFunction
			if ((UserPrefDcrMode) && PowerOnFlag && !SyncLossState() && !FreeRunModeFlag && InputTimingStableFlag) //edit by yz.nie .for DCR ON,change timing quickly have white screen.
			{
				msDlcHandler();
				msDCRHandler();
			}
			#endif
			#if 0// ENABLE_MHL
			if(MHL_CHECK_CONDITION()) // 120614 coding addition//130703 nick
			{
				#if ((CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF))
				#if MHL_HW_RTERM_SUPPORT		// 130717 william For G15 compiling warning
				mapi_mhl_RtermControlHWMode(FALSE);
				#endif
				#endif
				mapi_mhl_handler();
				#if ((CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF))
				#if MHL_HW_RTERM_SUPPORT		// 130717 william For G15 compiling warning
				mapi_mhl_RtermControlHWMode(TRUE);
				#endif
				#endif
			}
			#endif
			#if AudioFunc
			#if All_AudioDet
			if((!InputTimingChangeFlag) && InputTimingStableFlag && (!SyncLossState()) && (!PowerSavingFlag) && PanelOnFlag && (!UnsupportedModeFlag))
				Volume_EarphoneDetHander();
			#endif
			#endif
			#if USEFLASH
			UserPref_FlashDataSaving();
			#endif
		}
		#if WriteSN_Functiom_New
#message "你将使用只烧录SN的方式，请确认是否满足需求"
#message "若使用，请遵守规范"
		if(DDCCIReadLoadEDIDFlag)
		{
			ReLoadEDIDtoAddSN();
			mStar_InitDDC();
			#if ENABLE_DP_INPUT
			DPRxEDIDLoad();
			#endif
			Clr_DDCCIReadLoadEDIDFlag();
			Power_TurnOnGreenLed();
		}
		#endif
	}
	while (1);
}


void Init_Device()
{
	#if AudioFunc
	mStar_AdjustVolume(0);
	#endif
	if (PowerOnFlag)
	{
		Power_TurnOnGreenLed();
	}
	else
	{
		Power_TurnOffLed();
	}
}

#if Enable_CheckVcc5V
extern void Osd_Hide( void );
extern void Power_PowerOffSystem( void );

Bool CheckVCC5V ( void )
{
	if ( !hwDetectVCC5V_Pin )
	{
		Delay1ms ( 20 );
		if ( !hwDetectVCC5V_Pin )
		{
			Clr_CheckVcc5VFlag();
			if(PowerOnFlag && (!PowerSavingFlag))
			{
				hw_ClrBlacklit();
				hw_ClrPanel();
				Osd_Hide();
				Power_PowerOffSystem();
				hw_ClrGreenLed();
				hw_ClrAmberLed();
			}
			else
			{
				hw_ClrGreenLed();
				hw_ClrAmberLed();
			}
			Delay1ms ( 20 );
			while ( 1 )
			{
				if ( hwDetectVCC5V_Pin )
				{
					Delay1ms ( 20 );
					if ( hwDetectVCC5V_Pin )
					{
						Set_CheckVcc5VFlag();
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}


#endif

void Main_SlowTimerHandler(void)
{
	if(ms10Flag)
	{
		if (ModeDetectCounter)
		{
			if(ModeDetectCounter > 10)
				ModeDetectCounter -= 10;
			else
				ModeDetectCounter = 0;
		}
		if( TPDebunceCounter )
		{
			if(TPDebunceCounter > 10)
				TPDebunceCounter -= 10;
			else
				TPDebunceCounter = 0;
		}
		#if ENABLE_HDMI
		if(HdmiPollingCounter)
		{
			if(HdmiPollingCounter > 10)
				HdmiPollingCounter -= 10;
			else
				HdmiPollingCounter = 0;
		}
		if (gScInfo.InputTmdsType == TMDS_HDMI && (!(SrcFlags & (SyncLoss | bUnsupportMode))) )
		{
			if(gScInfo.wAviPktLossCnt < AviPktLossBound)
				gScInfo.wAviPktLossCnt += 10;
		}
		#endif
		#if MS_DAC
		if(ToggleGainCntr)
		{
			if(ToggleGainCntr > 10)
				ToggleGainCntr -= 10;
			else
			{
				ToggleGainCntr = 0;
				bToggleGainFlag = 1;
			}
		}
		#endif
		#if ENABLE_MHL
		#if((CHIP_ID == CHIP_TSUMC) ||(CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF))
		mapi_mhl_PollingTimerhandler();
		#endif
		#endif
		#if MS_DAC && ((CHIP_ID == CHIP_TSUMC) || (CHIP_ID == CHIP_TSUMD) || (CHIP_ID == CHIP_TSUM9)|| (CHIP_ID == CHIP_TSUMF))
		#if (!InitialDACByISR)
		if( w16DAC_DePopCounter )
		{
			if(w16DAC_DePopCounter > 10)
			{
				w16DAC_DePopCounter -= 10;
			}
			else
			{
				w16DAC_DePopCounter = 0;
				bDAC_DePopFlag = 1;
			}
		}
		#endif
		#endif
		Clr_ms10Flag();
	}
	if(ms50Flag)
	{
		Clr_ms50Flag();
	}
	#if 0//ENABLE_FREESYNC
	if(ms250Flag)
	{
		Clr_ms250Flag();
		//if(USER_PREF_FREE_SYNC)//need check it
		Set_FreeSyncFlag();
	}
	#endif
	#if 0//ENABLE_FREESYNC
	if(ms250Flag)
	{
		Clr_ms250Flag();
	}
	#endif
	if(SecondFlag)
	{
		#if ((ENABLE_FREESYNC)&&(CHIP_ID==CHIP_TSUMU))//mqsh 20170421 for RX480 dp freesync on sometime get DRRFlag error
		if((PowerOnFlag) && (!SyncLossState()) && (!FreeRunModeFlag) && (!InputTimingChangeFlag) && (!UnsupportedModeFlag) && (UserprefFreeSyncMode == FreeSyncMenuItems_On) && (CURRENT_INPUT_IS_DISPLAYPORT()))
		{
			if(DCOffOnCounter)
			{
				if((msRead2Byte(SC0_0F)) != 0x02)
				{
					if(DPRxGetDRRFlag())
					{
						BYTE xdata ucDlyLine, u8SampleRangeVStartOffset; //SC0_7E
						if( ( CURRENT_SOURCE_IS_INTERLACE_MODE() )
						        || (g_SetupPathInfo.ucSCFmtIn == SC_FMT_IN_3D_FP)
						        || ((g_SetupPathInfo.wImgSizeOutV / g_SetupPathInfo.wImgSizeInV) >= 3) )
							ucDlyLine = 2;
						else
							ucDlyLine = 1;
						#if ENABLE_DUAL_LINK//for DP 1680x1050/60Hz flick
						if(CURRENT_INPUT_IS_DISPLAYPORT())  // follow trunk code
							ucDlyLine = 2;
						#endif
						msWriteByteMask(SC0_0F, 0x02, 0x0F); //Ylock line
						u8SampleRangeVStartOffset = (msRead2Byte(SC0_7E)) + (4 - ucDlyLine);
						msWrite2Byte(SC0_05, u8SampleRangeVStartOffset); // set capture window vstart
					}
					DCOffOnCounter--;
				}
			}
		}
		#endif
		#if FactoryLedFlicker_Enable
		if(FactoryModeFlag)
		{
			LedCounter ++;
			if(LedCounter % 2)
			{
				hw_SetGreenLed();
				//hw_SetAmberLed();
			}
			else
			{
				hw_ClrGreenLed();
				//hw_ClrAmberLed();
			}
		}
		#endif
		#if PowerSaveLedFlicker_Enable
		if((PowerSavingFlag && PowerOnFlag))
		{
			LedCounter ++;
			if(LedCounter % 2)
			{
				hw_SetGreenLed();
				//hw_SetAmberLed();
			}
			else
			{
				hw_ClrGreenLed();
				//hw_ClrAmberLed();
			}
		}
		#endif
		#if EANBLE_NEW_DCR_Functing
		if(DCR_Counter != 0 && EanbleClearBalclightStartFlag)
			if(--DCR_Counter == 0)
				Set_DoClearBalclightFlag();
		#endif
		if (!PowerSavingFlag)
		{
			#if Show_BackLightTimeValue
			if (BlacklitTime_S < 0xFF)
			{
				BlacklitTime_S++;
				if (BlacklitTime_S >= 60)
				{
					BlacklitTime_S = 0;
					BlacklitTime_M++;
					if (BlacklitTime_M % 30 == 0)
					{
						if (BlacklitTime_M >= 60)
						{
							BlacklitTime_M = 0;
							if (BlacklitTime_H >= 0xFFFF)
							{
								BlacklitTime_H = 0xFFFE;
							}
							BlacklitTime_H++;
						}
						BlacklitTime_S = 18; //2矫正时间
						MonitorBackLightTime_M = BlacklitTime_M;
						MonitorBackLightTime_H = BlacklitTime_H;
						SaveMonitorSetting2();
					}
				}
			}
			else
				BlacklitTime_S = 0;
			#endif
		}
		#if JRY_Color_Tool_Functing
		if (WhileCounte > 0 && (ATEModeFlag))
		{
			WhileCounte--;
			if (WhileCounte == 0)
				Clr_ATEModeFlag();
		}
		#endif
		#if JRY_FDDCCI_WriteEDID
		DDCCILoadEDIDCount++;
		#endif
		#if ESaverPowerDownFunc
		if(ESaverPowerDownCounter)
		{
			if(--ESaverPowerDownCounter == 0)
			{
				{
					MenuPageIndex = PowerOffMenu;
					MenuItemIndex = 0;
					PowerOffSystem();
				}
			}
			// Osd_Draw4Num(1,2,ESaverPowerDownCounter);
		}
		#endif
		#if Enable_ButtonKeyLongPressFunction
		if(g_HoldKeypadButton < BTN_EndBTN)
			if(g_HoldKeyCounter < 10)
				g_HoldKeyCounter++;
		#endif
		if (OsdCounter)
		{
			if (--OsdCounter == 0)
			{
				Set_OsdTimeoutFlag();
				#if DEBUG_HOTSWITCH
				printMsg("Set_OsdTimeoutFlag");
				#endif
			}
		}
		if (HotKeyCounter)
		{
			if (--HotKeyCounter == 0)
			{
				if (PressExitFlag)
					Set_EnableShowDDCFlag();
			}
		}
		#if ENABLE_OVER_SCAN && AudioFunc	//121211 Modify
		if (HotKeyPlusCounter)
		{
			if (--HotKeyPlusCounter == 0)
			{
				if (PressPlusFlag)
					Set_EnableExpansionMenuFlag();
			}
		}
		#endif
		if (DoKeyCountFlag && PowerOnFlag)
		{
			PowerKeyCounter++;
			PowerKeyCounter %= 2; // /3;For GPM Request
			if(PowerKeyCounter == 0)
				Set_PowerOffFlag();
		}
		if (PowerDownCounter)
		{
			if (--PowerDownCounter == 0)
			{
				Set_ForcePowerSavingFlag();
			}
		}
		#if USEFLASH
		UserPref_FlashSaveFlagCheck();//edit by lizzie,100429.for FlashSave every 1s,suggest by hungyi.cai
		#endif
		Set_ChangePatternFlag();
		Clr_SecondFlag();
		#if ( defined(OffPower))//  130723 william For PowerSaving timer slowly  && EXT_TIMER0_1S==0 )         //120919 Modify  20130510 update
		if (UserPrefAutoPowerOff && PowerOnFlag)
		{
			AutoPowerOffSTime++;
			if ((AutoPowerOffSTime % 60) == 0)
			{
				AutoPowerOffSTime = 0;
				AutoPowerOffMTime++;
				if ((!PowerSavingFlag) && (AutoPowerOffHTime == (UserPrefAutoPowerOff - 1)))		//130123_3 Henry
				{
					if((AutoPowerOffMTime == 50)
					  )
						ShowOffPowerWarningFlag = 1;
				}
				if ((AutoPowerOffMTime % 60) == 0)
				{
					AutoPowerOffMTime = 0;
					if (AutoPowerOffHTime < UserPrefAutoPowerOff)
					{
						AutoPowerOffHTime++;
						if (AutoPowerOffHTime == UserPrefAutoPowerOff)
						{
							{
								MenuPageIndex = PowerOffMenu;
								MenuItemIndex = 0;
								PowerOffSystem();
							}
						}
					}
				}
			}
		}
		#endif
	}
	#if (EXT_TIMER0_1S)// 2012-05-23-1
	if (g_oneSecondFlag)
	{
		g_oneSecondFlag = 0;
		// minute routine
		if(g_oneMinuteFlag)
		{
			g_oneMinuteFlag = 0;
			#if	0// 130723 william For PowerSaving timer slowly  OffPower
			if(AUTO_POWER_OFF_ACTIVE)
			{
				AutoPowerOffMTime++;
				if(AutoPowerOffMTime == 50)
				{
					if((!PowerSavingFlag) && ( AutoPowerOffHTime == (UserPrefAutoPowerOff - 1)))
					{
						ShowOffPowerWarningFlag = 1;
					}
				}
				else if ((AutoPowerOffMTime % 60) == 0)
				{
					AutoPowerOffMTime = 0;
					if (AutoPowerOffHTime < UserPrefAutoPowerOff)
					{
						AutoPowerOffHTime++;
						if (AutoPowerOffHTime == UserPrefAutoPowerOff)
						{
							MenuPageIndex = PowerOffMenu;
							MenuItemIndex = 0;
							PowerOffSystem();
						}
					}
				}
			}
			#endif
		}
	}
	#endif
}

