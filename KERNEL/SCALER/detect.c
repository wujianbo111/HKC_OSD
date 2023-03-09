#include <math.h>
#include "types.h"
#include "board.h"
#include "global.h"
#include "ms_reg.h"
#include "ms_rwreg.h"
#include "power.h"
#include "debug.h"
#include "misc.h"
#include "menu.h"
#include "UserPref.h"
#include "msOSD.h"
#include "msosdfunction.h"
#include "mStar.h"
#include "Panel.h"
#include "adjust.h"
#include "GPIO_DEF.h"
#include "drvosd.h"
#include "drvadc.h"
#include "autofunc.h"
#include "MenuFunc.h"   //2012.08.14 Stone.yu
#if ENABLE_HDCP
#include "MsHDCP.h"
#endif
#if MWEFunction
#include "MsACE.h"
#include "msdlc.h"
#endif

#if ENABLE_HDMI
#include "MsHDMI.h"
#endif

#ifdef ReduceDDC
#include "ddc.h"
#endif

#if MS_DAC
#include "drvDAC.h"
#endif



#ifdef TSUMXXT//#if( ChipID == ChipTSUMT )		//110311 Modify
#include "msADC.h"
#endif

#if MS_PM
#include "Ms_PM.h"
#endif
/////////////////////////////////////
#include "drvmStar.h"
////////////////////////////////////

////////////////////////////////////////////////////////////////////////
#define SyncValidCount_VGA    10

#define SyncLossCount_VGA     20


#define SyncValidCount_DVI  20// 80 

#define SyncLossCount_DVI   90//60//  
#define SyncValidCount_HDMI  60//  100

#define SyncLossCount_HDMI     ((150))// 230// 

#define SyncLossCount_ANDROID   1000//

#if ENABLE_HDMI2ND_INPUT
#define SyncValidCount_HDMI2  60//  
#define SyncLossCount_HDMI2  ((150))// 230// 
#endif

#if ENABLE_DP_INPUT
#define SyncValidCount_DP 60// 
#define SyncLossCount_DP   230//
#endif

#if ENABLE_MHL
#define SyncValidCount_MHL  50//25//50//70 // 120718 coding test	//130703 nick
#define SyncLossCount_MHL  (350)//250//250					//130703 nick
//#define MaxLossCount_MHL   (SyncLossCount_MHL*20) // unit: ms
#define ExtenCount_MHL   150 // unit: 20mS, 150x20 = 3000
#define SyncLossExtenCount_MHL      (SyncLossCount_MHL-ExtenCount_MHL)
#endif


#if ENABLE_DEBUG&&DEBUG_DETECT
#define DETECT_printData(str, value)   printData(str, value)
#define DETECT_printMsg(str)           printMsg(str)
#else
#define DETECT_printData(str, value)
#define DETECT_printMsg(str)
#endif

#if ENABLE_DEBUG&&0
#define NOSYNC_printData(str, value)   printData(str, value)
#define NOSYNC_printMsg(str)           printMsg(str)
#else
#define NOSYNC_printData(str, value)
#define NOSYNC_printMsg(str)
#endif

////////////////////////////////////////////////////////////////////////
// 120425 coding add 1A2H model for sync valid/loss conter
#if INPUT_TYPE == INPUT_1A1H || INPUT_TYPE == INPUT_1A2H || INPUT_TYPE == INPUT_2H
#if ENABLE_MHL
#define SyncValidCount_Digital  ((GET_MHL_CABLE_PLUGGED())?(SyncValidCount_MHL):(SyncValidCount_HDMI))
#define SyncLossCount_Digital  ((GET_MHL_CABLE_PLUGGED())?(SyncLossCount_MHL):(SyncLossCount_HDMI))
#else
#define SyncValidCount_Digital  SyncValidCount_HDMI
#define SyncLossCount_Digital  SyncLossCount_HDMI
#endif
#elif INPUT_TYPE == INPUT_1A2D || INPUT_TYPE == INPUT_2A2D||INPUT_TYPE == INPUT_1A1D1H	//131113 fay
#if ENABLE_MHL
#define SyncValidCount_Digital  ((SrcInputType>Input_Digital)?((GET_MHL_CABLE_PLUGGED())?(SyncValidCount_MHL):(SyncValidCount_HDMI)):(SyncValidCount_DVI))
#define SyncLossCount_Digital  ((SrcInputType>Input_Digital)?((GET_MHL_CABLE_PLUGGED())?(SyncLossCount_MHL):(SyncLossCount_HDMI)):(SyncLossCount_DVI))
#else
#define SyncValidCount_Digital  ((SrcInputType>Input_Digital)?(SyncValidCount_HDMI):(SyncValidCount_DVI))
#define SyncLossCount_Digital  ((SrcInputType>Input_Digital)?(SyncLossCount_HDMI):(SyncLossCount_DVI))
#endif
#elif INPUT_TYPE == INPUT_1A1D1H1DP|| INPUT_TYPE == INPUT_1D1H1DP
#if ENABLE_MHL
#define SyncValidCount_TMDS  ((SrcInputType>Input_Digital)?((GET_MHL_CABLE_PLUGGED())?(SyncValidCount_MHL):(SyncValidCount_HDMI)):(SyncValidCount_DVI))
#define SyncLossCount_TMDS  ((SrcInputType>Input_Digital)?((GET_MHL_CABLE_PLUGGED())?(SyncLossCount_MHL):(SyncLossCount_HDMI)):(SyncLossCount_DVI))
#else
#define SyncValidCount_TMDS  ((SrcInputType>Input_Digital)?(SyncValidCount_HDMI):(SyncValidCount_DVI))
#define SyncLossCount_TMDS  ((SrcInputType>Input_Digital)?(SyncLossCount_HDMI):(SyncLossCount_DVI))
#endif
#define SyncValidCount_Digital  ((CURRENT_INPUT_IS_DISPLAYPORT())?(SyncValidCount_DP):(SyncValidCount_TMDS))
#define SyncLossCount_Digital  ((CURRENT_INPUT_IS_DISPLAYPORT())?(SyncLossCount_DP):(SyncLossCount_TMDS))
#elif INPUT_TYPE == INPUT_1A1D1DP	//130924 xiandi
#define SyncValidCount_Digital  ((CURRENT_INPUT_IS_DISPLAYPORT())?(SyncValidCount_DP):(SyncValidCount_DVI))
#define SyncLossCount_Digital  ((CURRENT_INPUT_IS_DISPLAYPORT())?(SyncLossCount_DP):(SyncLossCount_DVI))
#elif INPUT_TYPE == INPUT_1A1DP	////20151126 Alpha
#define SyncValidCount_Digital  (SyncValidCount_DP)
#define SyncLossCount_Digital  (SyncLossCount_DP)
#elif INPUT_TYPE == INPUT_1A2H1DP

#define SyncValidCount_TMDS  ((SrcInputType>Input_Digital)?(SyncValidCount_HDMI):(SyncValidCount_HDMI2))
#define SyncLossCount_TMDS  ((SrcInputType>Input_Digital)?(SyncLossCount_HDMI):(SyncLossCount_HDMI2))

#define SyncValidCount_Digital  ((CURRENT_INPUT_IS_DISPLAYPORT())?(SyncValidCount_DP):(SyncValidCount_TMDS))
#define SyncLossCount_Digital  ((CURRENT_INPUT_IS_DISPLAYPORT())?(SyncLossCount_DP):(SyncLossCount_TMDS))

#elif INPUT_TYPE == INPUT_1A1H1DP	//131203 xiandi
#if ENABLE_MHL
#define SyncValidCount_Digital  ((CURRENT_INPUT_IS_DISPLAYPORT())?(SyncValidCount_DP):((GET_MHL_CABLE_PLUGGED())?(SyncValidCount_MHL):(SyncValidCount_HDMI)))
#define SyncLossCount_Digital  ((CURRENT_INPUT_IS_DISPLAYPORT())?(SyncLossCount_DP):((GET_MHL_CABLE_PLUGGED())?(SyncLossCount_MHL):(SyncLossCount_HDMI)))
#else
#define SyncValidCount_Digital  ((CURRENT_INPUT_IS_DISPLAYPORT())?(SyncValidCount_DP):(SyncValidCount_HDMI))
#define SyncLossCount_Digital  ((CURRENT_INPUT_IS_DISPLAYPORT())?(SyncLossCount_DP):(SyncLossCount_HDMI))
#endif
#else
#define SyncValidCount_Digital  SyncValidCount_DVI
#define SyncLossCount_Digital  SyncLossCount_DVI
#endif

#define ValidTimingStableCount  ((CURRENT_INPUT_IS_VGA())?(SyncValidCount_VGA):(SyncValidCount_Digital))
#define SyncLossStableCount     ((CURRENT_INPUT_IS_VGA())?(SyncLossCount_VGA):(SyncLossCount_Digital))



extern InputModeType code StandardMode[];
#if ENABLE_MHL
extern WORD xdata InputTimingStableCounter;
#else
extern BYTE xdata InputTimingStableCounter;
#endif
#if ENABLE_FREESYNC
Bool xdata bHDMIFreesyncChk = FALSE;
#endif

Bool mStar_FindMode(void);
BYTE mStar_GetInputStatus(void);
Bool IsCableNotConnected(void);
Bool mStar_SyncLossStateDetect(void);
Bool mStar_ValidTimingDetect(void);
#if ENABLE_MHL
Bool CurrentInputMHLCablePlugged(void);
#endif

#if ENABLE_MHL || ENABLE_DP_INPUT
#if MS_PM
extern XDATA ePMStatus ucWakeupStatus;
#endif
#endif
void SpeedupOrExtendSwitchPort(void);	//130625 nick

#if ENABLE_HDMI
// 120530 coding addition for speed up switch port
#define HDMI_STAY_1S_COUNT      50
#define JUST_HDMI_PLUG   0x5D
#define JUST_VGA_PLUG   0x35
#define BOTH_VGA_HDMI_PLUG   0x26
#define NONE_PLUG    0xFF
Bool HDMICableNotConnect(void)
{
	bit bresult = FALSE;
	#if 0
	if(CURRENT_INPUT_IS_HYBRID_MHL_HDMI() && !GET_MHL_CABLE_PLUGGED())
	{
		if( !HYBRID_MHL_HDMI_CABLE_CONNECT())
		{
			Delay1ms(2);
			if( !HYBRID_MHL_HDMI_CABLE_CONNECT())
				bresult = TRUE;
		}
	}
	else if(CURRENT_INPUT_IS_PURE_HDMI())
	{
		BYTE tempValue = CABLE_DET_SAR;
		if(abs(tempValue - JUST_HDMI_PLUG) > 10 && abs(tempValue - BOTH_VGA_HDMI_PLUG) > 10)	//130624 jun
		{
			bresult = TRUE;
		}
	}
	#else
#message "please coding HDMICableNotConnect for speedup switch port"
	#endif
	return bresult;
}
#define HDMI_SPEEDUP_SWITCH_PORT()    ((InputTimingStableCounter >= HDMI_STAY_1S_COUNT) && DVI_CLOCK_IS_MISSING() && HDMICableNotConnect())
#endif

#if ENABLE_MHL
#define MHL_EXTEND_SYNCLOSS_COUNT()   (SyncLossState() \
                                       && InputTimingStableCounter >= SyncLossStableCount \
                                       && !MHLExtenCountFlag\
                                       && CURRENT_INPUT_MHL_CABLE_PLUGGED() \
                                       && GET_MHL_CBUS_CONNECT())
#endif
//*******************************************************************
// Function Name: mStar_MonitorInputTiming
//
// Decscription: Detect input timing
//
// callee: mStar_SyncLossStateDetect(), mStar_ValidTimingDetect(), mStar_AutoDVI() in detect.c
//         mStar_SetInputPort(), mStar_SetAnalogInputPort() in mstar.c
//
// caller: main() in main.c
//*******************************************************************
void mStar_MonitorInputTiming(void)
{
	if (!PowerOnFlag || DisplayLogoFlag)
	{
		return ;
	}
	// detect whether input signal is changing
	if (!InputTimingChangeFlag)
	{
		if (SyncLossState())
		{
			if (!FreeRunModeFlag)
			{
				Set_InputTimingChangeFlag();
			}
			else if (mStar_SyncLossStateDetect())
				// detect mode while no Sync/suspend/standby/disconnect
			{
				DETECT_printMsg("no sync -> have sync");
				Set_InputTimingChangeFlag();
			}
			#if Dual
			else if((InputTimingStableCounter > 0) && (SwitchPortCntr > Input_Nums) && // 100125 coding
			        (UserPrefInputSelectType == INPUT_PRIORITY_AUTO)
			       )
			{
				//130625 nick
				SpeedupOrExtendSwitchPort();
				#if 0//ENABLE_HDMI
				if(HDMI_SPEEDUP_SWITCH_PORT())
				{
					InputTimingStableCounter = SyncLossStableCount;
					#if 0//ENABLE_DEBUG
					printData("PowerSaving Speedup:%d", SrcInputType);
					#endif
				}
				#endif
				#if 0//ENABLE_MHL
				if(MHL_EXTEND_SYNCLOSS_COUNT())
				{
					InputTimingStableCounter = SyncLossExtenCount_MHL;
					MHLExtenCountFlag = 1;
					#if DEBUG_PRINTDATA
					printData("PowerSaving MHL ex3S:%d", SrcInputType);
					#endif
				}
				#endif
				if((InputTimingStableCounter % SyncLossStableCount) == 0)
				{
					InputTimingStableCounter = 1; // 071224
					SrcInputType = (SrcInputType + 1) % Input_Nums;
					/*if(SrcInputType>Input_HDMI3)
					    	{SrcInputType = Input_HDMI3;
					printData(" PS_SwitchTo:%d", SrcInputType);
					#message"rember to del it"
					}
					else	*/
					mStar_SetupInputPort();
					//DETECT_printData(" PS_SwitchTo:%d", SrcInputType);
				}
			}
			#endif
		}
		else
			// valid timing
		{
			// check if input timing is changing
			if (mStar_ValidTimingDetect())
			{
				SrcFlags |= SyncLoss;
				Set_InputTimingChangeFlag();
				hw_ClrBlacklit(); // 2006/9/7 8:39PM by Emily for changed mode had garbage
				#if DEBUG_MSG
				printMsg("have sync -> no sync");
				printData("InputTimingStableCounter %d", InputTimingStableCounter);
				#endif
				#if (ENABLE_DP_INPUT&& ((CHIP_ID == CHIP_TSUMC)||(CHIP_ID == CHIP_TSUMD)||(CHIP_ID == CHIP_TSUM9)||(CHIP_ID == CHIP_TSUMF))) 	//130912 nick
				#if DP_RESETHTT_PATCH
				if(CURRENT_INPUT_IS_DISPLAYPORT())
					DPMSA_Reset();
				#endif
				#endif
//msWriteByteMask( REG_1F15,0,BIT5);	//1 能 解DP FREESYNC 状态保持, 需 待验证,勿使用
			}
		}
	}
	//=============================================================================
	//=============================================================================
	if (InputTimingChangeFlag)
		// input timing is unstable
	{
		#if MWEFunction
		if (g_bAccOnOff)
		{
			//UserPrefMWE=OFF_W;
			//msAccSetup(UserPrefMWE);
			#if (CHIP_ID==CHIP_TSUMU)
			msAccSetup( 0, 0, 0, 0 );
			#endif
			msAccOnOff(0);
		}
		#endif
		// 2006/7/6 0:8AM by Emily for dec. dot clock
		Clr_DecVScaleFlag();
		DecVScaleValue = 0;
		Clr_InputTimingChangeFlag();
		Clr_DoModeSettingFlag();
		Clr_ReadyForChangeFlag();
		//DETECT_printData(" PrepareForTimingChange:%d", SrcInputType);
		#if ENABLE_FREESYNC
		bHDMIFreesyncChk = TRUE;
		//g_bHDMIFreesyncEnable = FALSE;
		#endif
		mStar_PrepareForTimingChange();
	}
	else
		// input timing is stable
	{
		InputTimingStableCounter++; // counter timing stable times
		if(InputTimingStableCounter == 0)
			InputTimingStableCounter = 1;
		if (!InputTimingStableFlag)
		{
			//130625 nick
			SpeedupOrExtendSwitchPort();
			#if 0//ENABLE_HDMI
			if(HDMI_SPEEDUP_SWITCH_PORT())
			{
				InputTimingStableCounter = SyncLossStableCount;
			}
			#endif
			#if 0//ENABLE_MHL
			if(MHL_EXTEND_SYNCLOSS_COUNT())
			{
				InputTimingStableCounter = SyncLossExtenCount_MHL;
				MHLExtenCountFlag = 1;
				#if DEBUG_PRINTDATA
				//DETECT_printData("MHL ex3S:%d", SrcInputType);
				#endif
			}
			#endif
			if((!SyncLossState() && InputTimingStableCounter >= ValidTimingStableCount) ||
			        (SyncLossState() && InputTimingStableCounter >= SyncLossStableCount))
			{
				Set_InputTimingStableFlag(); // set flag to search for input mode
				Set_DoModeSettingFlag();
				#if ENABLE_MHL
				#if MS_PM
				if(SyncLossState() && PM_WAKEUP_FROM_MHL)
				{
					Set_ForcePowerSavingFlag();
					Clr_DoModeSettingFlag();
					return;
				}
				#endif
				#endif
				#if ENABLE_DP_INPUT
				#if MS_PM
				if(SyncLossState() && PM_WAKEUP_FROM_DP)
				{
					Set_ForcePowerSavingFlag();
					Clr_DoModeSettingFlag();
					return;
				}
				#endif
				#endif
				#if Dual
				#if 0//ENABLE_DEBUG
				//if(!SyncLossState())
				//    printData("ValidCntr:%d", InputTimingStableCounter);
				//else
				printData("LossCntr:%d", InputTimingStableCounter);
				printData("SrcInputType:%d", SrcInputType);
				#endif
				InputTimingStableCounter = 1; // 071224
				if(!SyncLossState())
				{
					SwitchPortCntr = 0;
					#if ENABLE_MHL//130703 nick
					MHLExtenCountFlag = 0;
					#endif
				}
				if(SyncLossState() && (UserPrefInputSelectType == INPUT_PRIORITY_AUTO) &&
				        (++SwitchPortCntr <= Input_Nums)
				  ) // 100125 coding
				{
					Clr_InputTimingStableFlag(); // set flag to search for input mode
					Clr_DoModeSettingFlag();
					SrcInputType = (SrcInputType + 1) % Input_Nums;
					#if CHIP_ID==CHIP_TSUMD
					//====Test 20130312  for Auto switch TMDS can't display====//
					//drvADC_PowerCtrl(ADC_POWER_ON);
					//drvDVI_PowerCtrl(DVI_POWER_ON);
					//====Test 20130312 ====//
					#endif
					mStar_SetupInputPort();
					DETECT_printData(" 2-PS_SwitchTo:%d", SrcInputType);
					#if 0//ENABLE_DEBUG
					printData("SwitchPort:%d", SrcInputType);
					#endif
				}
				#if (AudioFunc && ENABLE_DP_INPUT)//131031 xiandi		petit  20131107 update
				PrevInputType = SrcInputType;
				#endif
				#endif
			}
		}
	}
}
//*******************************************************************
// Function Name: mStar_ModeHandler
//
// Decscription: Programming scaler while input timing is changing
//
// callee: mStar_SyncLossStateDetect(), mStar_ValidTimingDetect(), mStar_AutoDVI() in detect.c
//         mStar_SetInputPort(), mStar_SetAnalogInputPort() in mstar.c
//
// caller: main() in main.c
//*******************************************************************
void mStar_ModeHandler(void)
{
	if (DisplayLogoFlag)
	{
		Menu_InitAction();
	}
	#if MS_PM
	#if ENABLE_MHL
	if(SyncLossState() && PM_WAKEUP_FROM_MHL)
		return;
	#endif
	#if ENABLE_DP_INPUT
	if(SyncLossState() && PM_WAKEUP_FROM_DP)
		return;
	#endif
	#endif
	if (!DoModeSettingFlag)
		// while timing change & stable
	{
		return ;
	}
	#if MS_DAC
	#if (CHIP_ID==CHIP_TSUMC ||CHIP_ID==CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)
	if(!SyncLossState() && w16DAC_DePopStep != INIT_FINISH)
		return;
	#endif
	#endif
	//Clr_DoModeSettingFlag();  //0606 for Diaplay LOGO
	if (!SyncLossState())
		// no sync
	{
		#if ENABLE_MHL_COUNT
		if(!SyncLossState() && CURRENT_INPUT_MHL_CABLE_PLUGGED())
		{
			//DETECT_printData("ModeHandler:%d", MHLActionCount);
			MHLActionCount = 1;
		}
		#endif
		{
			BYTE  xdata Retry = 0;
			if (
			    ((CURRENT_INPUT_IS_DISPLAYPORT()) && DP_INTERLACED_VIDEO_STREAM())
			    || (SC0_READ_SYNC_STATUS()&INTM_B))
			{
				SrcFlags |= bInterlaceMode;
			}
			else
				SrcFlags &= ~bInterlaceMode;
			if(SrcFlags & bInterlaceMode)
			{
				for (Retry = 0; Retry < 10; Retry++)
				{
					Delay1ms(20);
					if(((CURRENT_INPUT_IS_DISPLAYPORT()) && DP_INTERLACED_VIDEO_STREAM()) || (SC0_READ_SYNC_STATUS()&INTM_B))
					{
						SrcFlags |= bInterlaceMode;
						//printMsg("111111111 bInterlaceMode");
					}
					else
					{
						SrcFlags &= ~bInterlaceMode;
						//printMsg("00000000000000");
						break;
					}
				}
			}
		}
		#if 0//ENABLE_FREESYNC//170118 Test
		if(SrcFlags & bInterlaceMode)
		{
			scRegs[(SC0_E8) & 0xFF] = ((scRegs[(SC0_E8) & 0xFF]) & (~(BIT1 | BIT0)));
			bHDMIFreesyncChk = FALSE;
		}
		else if((IS_HDMI_FREESYNC_ISR()))
		{
			scRegs[(SC0_E8) & 0xFF] = (((scRegs[(SC0_E8) & 0xFF]) & (~BIT1)) | BIT0);
			bHDMIFreesyncChk = FALSE;
			Delay1ms(30);
		}
		#endif
		#if ENABLE_FREESYNC//170118 Test
		{
			BYTE  xdata Retry = 0;
			if (
			    ((CURRENT_INPUT_IS_DISPLAYPORT()) && DP_INTERLACED_VIDEO_STREAM())
			    || (SC0_READ_SYNC_STATUS()&INTM_B))
			{
				SrcFlags |= bInterlaceMode;
			}
			else
				SrcFlags &= ~bInterlaceMode;
			//if((UserprefFreeSyncMode==FreeSyncMenuItems_On)&&CURRENT_INPUT_IS_HDMI())
			if(SrcFlags & bInterlaceMode)
			{
				for (Retry = 0; Retry < 10; Retry++)
				{
					Delay1ms(20);
					if(((CURRENT_INPUT_IS_DISPLAYPORT()) && DP_INTERLACED_VIDEO_STREAM()) || (SC0_READ_SYNC_STATUS()&INTM_B))
					{
						SrcFlags |= bInterlaceMode;
						//printMsg("111111111 bInterlaceMode");
					}
					else
					{
						SrcFlags &= ~bInterlaceMode;
						//printMsg("00000000000000");
						break;
					}
					//printData("00000000 SRC_FLAGS==%x",SRC_FLAGS);
				}
			}
		}
		if(SrcFlags & bInterlaceMode)
		{
			scRegs[(SC0_E8) & 0xFF] = ((scRegs[(SC0_E8) & 0xFF]) & (~(BIT1 | BIT0)));
			bHDMIFreesyncChk = FALSE;
		}
		else if((IS_HDMI_FREESYNC_ISR()) || ((UserprefFreeSyncMode == FreeSyncMenuItems_On) && CURRENT_INPUT_IS_HDMI()))
		{
			#if DEBUG_MSG
			printMsg("try to run");
			#endif
			// if(bHDMIFreesyncChk)
			//MEM_SCWRITE_BYTE(SC0_E8,((scRegs[(SC0_E8)&0xFF])&(~BIT1))|BIT0);    //Enable force P mode
			scRegs[(SC0_E8) & 0xFF] = (((scRegs[(SC0_E8) & 0xFF]) & (~BIT1)) | BIT0);
			bHDMIFreesyncChk = FALSE;
			Delay1ms(30);
		}
		#endif
		#if 1
		#if ENABLE_HDMI
		if(CURRENT_INPUT_IS_TMDS()
		  )//( (SrcInputType==Input_Digital||SrcInputType==Input_Digital2))	//121130 Modify
		{
			if( mstar_HDMITmdsGetType() == TMDS_HDMI )
			{
				BYTE ucCount = 200; //25;  2009-10-13
				//printMsg("====>TMDS_HDMI");
				while( ucCount-- )
				{
					gScInfo.InputAVIInfoReceived = 0;
					mstar_HDMIGetPktStatus();
					if( gScInfo.InputAVIInfoReceived )
					{
						gScInfo.InputColor = mstar_HDMIPacketColor();
						if(gScInfo.InputColor == INPUT_RGB)
							InputColorFormat = INPUTCOLOR_RGB;
						else
							InputColorFormat = INPUTCOLOR_YUV;
						gScInfo.ColorChanged = 1;
						mstar_HDMIHandleColor();
						break;
					}
					Delay1ms( 20 );
					if (mStar_ValidTimingDetect())			//120526 Modify
					{
						SrcFlags |= SyncLoss;
						Set_InputTimingChangeFlag();
						break;
					}
				}
				#if ENABLE_HDMI_1_4
				msHDMI_Check_3D_Mode_Chg(0);
				#endif
				gScInfo.OutputDataState = HDMI_DATA_OUTPUT_ON;
				mstar_HDMICheckAudio();
				gScInfo.InputTmdsType = TMDS_HDMI;
				#if 0//DEBUG_PRINTDATA
				printData( " TMDS_HDMI Color:%x", msReadByte( REG_0580 ));
				#endif
				//SC0_INPUT_SELECT(ISEL_HDMI_444); //msWriteByteMask(SC0_02, SCALER_ISEL_HDMI, BIT2|BIT1|BIT0);
				//Delay1ms(100);			//120526 Modify
			}
			else if(mstar_HDMITmdsGetType() == TMDS_DVI)
			{
				#if ENABLE_DEBUG
				DETECT_printMsg("===>TMDS_DVI");
				#endif
				gScInfo.InputTmdsType = TMDS_DVI;
				//SC0_INPUT_SELECT(ISEL_DVI); //msWriteByteMask(SC0_02, SCALER_ISEL_DVI, BIT2|BIT1|BIT0);
				InputColorFormat = INPUTCOLOR_RGB;
				#if 0//DEBUG_PRINTDATA
				printData( " TMDS_DVI Color:%x", msReadByte( REG_0580 ));
				#endif
			}
		}
		#endif
		// 121119 coding addition
		if(InputTimingChangeFlag)
			return;
		SettingInputColorimetry();
		#endif
		if (!ReadyForChangeFlag)
		{
			//if(SrcInputType==Input_Digital || SrcInputType==Input_Digital2)
			//    CheckADC();
			if (!mStar_FindMode())
				// search mode index
			{
				Set_InputTimingChangeFlag(); // search mode faile
				SrcFlags |= SyncLoss;			//120526 Modify
				return ;
			}
		}
		if (!UnsupportedModeFlag)
			//supported mode
		{
			if (!ReadyForChangeFlag)
			{
				ReadModeSetting(); // restore user's settings from NVRAM for each mode
				Set_ReadyForChangeFlag();
			}
			#if DisplayPowerOnLogo
			if (DisplayLogoFlag)
			{
				return ;
			}
			#endif
			#if CHIP_ID ==CHIP_TSUMC ||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF	//130508 Modify
			if(CURRENT_INPUT_IS_VGA())
				drvDVI_PowerCtrl(DVI_POWER_DOWN);
			#endif
			if (mStar_SetupMode() == FALSE)
				// setup scaler
			{
				DETECT_printMsg("Setup Mode False!");
				Set_InputTimingChangeFlag(); // setup mode failed
				mStar_SetupFreeRunMode(); // setup freerun mode
				SrcFlags |= SyncLoss; //edit by yz.nie .for DCR ON,change timing quickly have white screen.
				return ;
			}
		}
		else
		{}
		#if ENABLE_MHL || ENABLE_DP_INPUT
		#if MS_PM	//20151022  Alpha, clr ucWakeupStatus to avoid cannot show nosignal OSD after MHL wake up (due to ucWakeupStatus = ePMSTS_MHL_ACT)
		SET_PM_WAKEUP_NON();
		#endif
		#endif
	}
	Set_ReadyForChangeFlag();
	#if 	DisplayPowerOnLogo
	if (DisplayLogoFlag)
	{
		return ;
	}
	#endif
	if (SyncLossState() || UnsupportedModeFlag)
	{
		#if MWEFunction     //110223 Modify for turn on BF and change to the source of nosignal will show garbage
		#if (CHIP_ID==CHIP_TSUMU)
		msAccSetup( 0, 0, 0, 0 );
		#endif
		msAccOnOff(0);
		#endif
		#if Enable_Rotate180Func
		mStar_SetupPath();
		#endif
		mStar_SetupFreeRunMode(); // setup freerun mode
		Power_TurnOnGreenLed();
		// printMsg("Set Free Run 1");
	}
	else
	{
		WORD vfreq, hfreq;
		#if ENABLE_FREESYNC
		if(IS_DP_FREESYNC())
		{
			WORD u16PixClk, u16Htt;
			u16PixClk = msAPI_combo_IPGetPixelClk();
			u16Htt = msAPI_combo_IPGetGetHTotal();
			if((u16Htt != 0) && (SrcVTotal != 0))
			{
				hfreq = ((DWORD)u16PixClk * 100 + u16Htt / 2) / u16Htt;
				vfreq = ((DWORD)hfreq * 1000 + SrcVTotal / 2) / SrcVTotal;
			}
		}
		else
		#endif
		{
			hfreq = HFreq(SrcHPeriod);
			vfreq = VFreq(hfreq, SrcVTotal);
		}
		if(SrcFlags & bInterlaceMode)
		{
			vfreq *= 2;
		}
		#if DEBUG_MSG
		printData("==hfreq===========  %d", hfreq);
		printData("==Vfreq===========  %d", vfreq);
		#endif
		#if BURST_MODE
		#if ENABLE_FREESYNC
		if(IS_HDMI_FREESYNC() || IS_HDMI_FREESYNC())
		{
			SetPWMFreq(240);//set it to a fix value in SetPWMFreq (240, 27000, ...)
		}
		else
		#endif
		{
			BYTE i = 4;
			while((vfreq * i) / 10 < 220) //set pwm freq.>=220
			{
				i++;
			}
			SetPWMFreq((vfreq * 4) / 10);
		}
		#endif
		#if ENABLE_FREESYNC
		if(!IS_HDMI_FREESYNC())
		#endif
		{
			#if (FRAME_BFF_SEL != FRAME_BUFFER) //20130909 nick modify
			#if ENABLE_FREESYNC
			if(!IS_DP_FREESYNC())
			#endif
			{
				if ( hfreq > MaxInputHFreq || vfreq > (PanelMaxVfreq) )// 121101 coding modified ( hfreq > MaxInputHFreq || vfreq>PanelVsyncFreq*11 )
				{
					SrcFlags |= bUnsupportMode;
					#if DEBUG_MSG
					printMsg("Unsupport  1");
					#endif
				}
				else if (hfreq < MinInputHFreq || vfreq < MinInputVFreq )
				{
					if (SrcInputType != Input_VGA )//&& (SrcFlags&bInterlaceMode))   //charles
						SrcFlags &= !bUnsupportMode;
					else
						SrcFlags |= bUnsupportMode;
					#if DEBUG_MSG
					printMsg("Unsupport  2");
					#endif
				}
			}
			#endif
		}
		if (StandardModeHeight <= 400 ||
		        (StandardModeHeight == 480 && (StandardModeGroup != Res_848x480))) //SrcModeIndex!=0))//120911 Modify for TPV request
		{
			UserPrefAutoTimes = 1;
		}
		if (PowerOnFlag)
			// system is on power-off status
		{
			Power_TurnOnGreenLed(); // turn on green led
		}
		//Set_ShowInputInfoFlag();//071226
	}
	#if BrightFreqByVfreq
	if(!SyncLossState())
	{
		WORD vfreq, hfreq;
		hfreq = HFreq( SrcHPeriod );
		vfreq = VFreq( hfreq, SrcVTotal );
		if(SrcFlags & bInterlaceMode)		//130228 Modify
		{
			vfreq *= 2;
		}
		if( abs( vfreq - 500 ) < 10 ) //when Input Vfreq=50Hz,Set Brightness freq to 250Hz
			SetPWMFreq( 250 );
		else
			SetPWMFreq(( vfreq * 4 ) / 10 );
		#if ENABLE_DEBUG
		DETECT_printData("  BrightFreqByVfreq:%d", vfreq / 10);
		#endif
	}
	#endif
	#if BURST_MODE
	if(FreeRunModeFlag)	//110715 Modify
	{
		SetPWMFreq(250);
	}
	else
	{
		WORD vfreq, hfreq;
		hfreq = HFreq(SrcHPeriod);
		vfreq = VFreq(hfreq, SrcVTotal);
		if(SrcFlags & bInterlaceMode)		//130228 Modify
		{
			vfreq *= 2;
		}
		if(abs(vfreq - 500) < 10) //when Input Vfreq=50Hz,Set Brightness freq to 250Hz
			SetPWMFreq(250);
		#if 0
		if(abs(vfreq - 720) < 10)
			SetPWMFreq((vfreq * 5) / 10);
		#endif
		else
			SetPWMFreq((vfreq * 4) / 10);
	}
	#endif
	#if 0	//20171226
	if (!CableNotConnectedFlag || !SyncLossState())
	{
		if (DoBurninModeFlag)
		{
			drvOSD_FrameColorEnable(FALSE);//petit 20121122 disable background color function.
		}
	}
	#else
	drvOSD_FrameColorEnable(FALSE);
	#endif
	Clr_DoModeSettingFlag(); //0606
	TermBuffer = StandardModeGroup;
	#if ENABLE_HDMI
	if(CURRENT_INPUT_IS_TMDS() && !SyncLossState() && CURRENT_INPUT_IS_HDMI())//( (SrcInputType==Input_Digital||SrcInputType==Input_Digital2))	//121130 Modify
	{
		if(gScInfo.InputTmdsType == TMDS_HDMI)
			SC0_INPUT_SELECT(ISEL_HDMI_444);
		else
			SC0_INPUT_SELECT(ISEL_DVI);
	}
	#endif
	#if 0 // 120525 coding move position to find
	#if ENABLE_HDMI
	if(!SyncLossState() && mstar_HDMITmdsGetType() == TMDS_HDMI && SrcInputType >= Input_Digital)
	{
		BYTE ucCount = 200;
		while(ucCount--)
		{
			gScInfo.InputAVIInfoReceived = 0;
			mstar_HDMIGetPktStatus();
			if(gScInfo.InputAVIInfoReceived)
			{
				gScInfo.InputColor = mstar_HDMIPacketColor();
				gScInfo.ColorChanged = 1;
				mstar_HDMIHandleColor();
				break;
			}
			Delay1ms(20);
		}
		gScInfo.OutputDataState = HDMI_DATA_OUTPUT_ON;
		mstar_HDMICheckAudio();
		if( TermBuffer == Res_1920x1080 || TermBuffer == Res_1280x720)
		{
			//msSetColorFomat( HDTV  );
		}
		else //( TermBuffer == Res_720x576	|| TermBuffer == Res_720x483	|| TermBuffer == Res_720x480)
		{
			//msSetColorFomat( SDTV );
		}
	}
	#if MS_DAC
	if( gScInfo.InputTmdsType == TMDS_HDMI && (CURRENT_INPUT_IS_HDMI() || CURRENT_INPUT_IS_DVI())) // && (UserPrefAudioSource == AUDIO_DIGITAL))//SrcInputType >= Input_Digital )
		//if (gScInfo.InputTmdsType ==TMDS_HDMI && SrcInputType>=Input_Digital)
	{
		msAudioLineout_SourceSel( E_LINEOUT_FROM_DAC );
		msAudioDPGA_SetVolume( E_AUDIO_LEFT_RIGHT_CH, 0x00 );
		#if !USE_DAC_ADJ
		msAudioLineOutGain( Def_DACGain );
		#endif
	}
	else // line in to line out: 550mVrms
	{
		msAudioLineout_SourceSel( E_LINEOUT_FROM_LINEIN0 );
		msAudioDPGA_SetVolume( E_AUDIO_LEFT_RIGHT_CH, 0x00 );
		#if !USE_DAC_ADJ
		msAudioLineOutGain( 0x27 );
		#endif
	}
	msAudioEARout_Mute( FALSE );
	#else
	//   if( gScInfo.InputTmdsType == TMDS_HDMI && CURRENT_INPUT_IS_HDMI()// && (UserPrefAudioSource == AUDIO_DIGITAL))//SrcInputType >= Input_Digital )
	//      hw_Audio_HDMI();
	//  else
	//      hw_Audio_PC();
	#endif
	#if DEBUG_HDMI
	printData("gScInfo.InputTmdsType=%d", gScInfo.InputTmdsType);
	#endif
	#endif
	SettingInputColorimetry();
	#endif
	#if AudioFunc
	#if ((CHIP_ID == CHIP_TSUMC) || (CHIP_ID == CHIP_TSUMD) || (CHIP_ID == CHIP_TSUM9) || (CHIP_ID == CHIP_TSUMF))   // reset audio FIFO
	msWriteByteMask(REG_1427, 0x10, 0x10);
	msWriteByteMask(REG_1427, 0x00, 0x10);
	#endif
	#if MS_DAC
	#if DiaghtAudioInput
	if((!(SyncLossState() && CableNotConnectedFlag && DoBurninModeFlag))
	        && (CURRENT_INPUT_IS_DISPLAYPORT()
            #if ENABLE_HDMI
	            || ( gScInfo.InputTmdsType == TMDS_HDMI && CURRENT_INPUT_IS_TMDS())
            #endif
	           ))	//130909 petit //20131022 update
	{
		#if 1
		msAudioLineout_SourceSel( E_LINEOUT_FROM_DAC );
		#if(!USE_DAC_ADJ)
		msAudioDPGA_SetVolume( E_AUDIO_LEFT_RIGHT_CH, 0x0000 );  //20121004
		#endif
		//2 解声音突变
		#if EarphoneDet_Enable
		if (HarphoneDet_Pin)
		{
			msAudioLineOutGain( 0x38F );
		}
		else
		#endif
		{
			msAudioLineOutGain( Def_DACGain );
		}
		#endif
	}
	else // line in to line out: 550mVrms
	#endif
	{
		#if 1
		msAudioLineout_SourceSel( E_LINEOUT_FROM_LINEIN0 );
		#if(!USE_DAC_ADJ)
		#if 1
		msAudioDPGA_SetVolume( E_AUDIO_LEFT_RIGHT_CH, 0x0000 );
		#endif
		#endif
		msAudioLineOutGain( Def_DACGain );
		#endif
	}
	msAudioEARout_Mute( FALSE );
	msAudioGainForceToggle();  // nick add 20130528 for Audio output delay error
	#endif
	#if All_AudioDet
	if (HarphoneDet_Pin)
	{
		bAudioInputStatus = AudioInput_Ear;
		#if SWAP_LR_CHANNL
		msWriteByte(REG_2C05, 0x00);
		#endif
	}
	else
	{
		bAudioInputStatus = AudioInput_Spk;
		#if SWAP_LR_CHANNL
		msWriteByte(REG_2C05, 0x10);
		#endif
	}
	#endif
	#endif
	#if ENABLE_MHL_COUNT
	if(!SyncLossState() && CURRENT_INPUT_MHL_CABLE_PLUGGED())
	{
		DETECT_printData("turn on:%d", MHLActionCount);
		MHLActionCount = 0;
	}
	#endif
	#if ENABLE_FREESYNC
	if((UserprefFreeSyncMode == FreeSyncMenuItems_On) && (CURRENT_INPUT_IS_DISPLAYPORT()) && (!SyncLossState()) && (!UnsupportedModeFlag) && (!FreeRunModeFlag))
		DCOffOnCounter = 20;
	else
		DCOffOnCounter = 0;
	#endif
	Power_TurnOnPanel(); // turn on panel
	#if AudioFunc
	if( UnsupportedModeFlag || (SyncLossState() && CableNotConnectedFlag && BurninModeFlag))		//120215 Modify
	{
		mStar_AdjustVolume(0);
	}
	else if(!FreeRunModeFlag)
		mStar_AdjustVolume(UserPrefVolume);
	#endif
	#if ENABLE_FREESYNC
	if((OSDFreeSyncActionFlag))
	{
		#if FreeSyncMenu_Enable
		if((MenuPageIndex == FreeSyncMenu))//||(MenuPageIndex == SFreesyncMenu))
			Osd_Show();
		else
		#endif
		{
			Clr_OSDFreeSyncActionFlag();
			Menu_InitAction();
		}
	}
	else
	#endif
// printData("ModeHandlerAA=========>>>%d", 1);
		Menu_InitAction(); // initial menu osd state
}
void mStar_PrepareForTimingChange(void)
{
	#if ENABLE_DUAL_LINK
	if(CURRENT_INPUT_IS_DVI())
		msDVIDualLinkMode(DVI_SINGLE_LINK);
	#endif
	#if ENABLE_HDMI // wait for checking
	if( gScInfo.InputTmdsType == TMDS_HDMI )
		mstar_HDMIAudioMute( HDMI_AUDIO_OFF );
	mstar_HDMIInitialVariable();
	//mstar_HDMIResetColorSpace();
	mstar_HDMIRst(Reset_HDMIStatus);
	#endif
	#if ENABLE_DP_INPUT	//130603 william
	#if AudioFunc
	if(CURRENT_INPUT_IS_DISPLAYPORT())
	{
		hw_SetMute();
	}
	#endif
	#endif
	#if AudioFunc
	#if  CHIP_ID==CHIP_TSUMU
	msAudioEARout_Mute(TRUE);
	#else
	msAudioDPGA_Mute();
	#endif
	hw_SetMute();
	#endif
	#if 0//def WH_REQUEST
	#if WH_REQUEST_DDCCI_POWERSAVING
	#if MS_PM
	Clr_DDCForcePowerSavingFlag();
	#endif
	#endif
	#endif
	Clr_ForcePowerSavingFlag();
	PowerDownCounter = 0;
	InputColorFormat = INPUTCOLOR_RGB;
	#if DisplayPowerOnLogo
	if (!DisplayLogoFlag)
	#endif
	{
		if (PowerSavingFlag)
		{
			Power_PowerOnSystem();
			mStar_SetupFreeRunMode();
		}
		else
		{
			//if (PanelOnFlag)
			mStar_SetupFreeRunMode();
			#if ENABLE_FREESYNC
			if(UserprefFreeSyncMode == FreeSyncMenuItems_On)
			{
				if(BackLightActiveFlag)
				{
					hw_ClrBlacklit();
				}
			}
			else
			#endif
				Power_TurnOffPanel();
		}
		Osd_Hide();
	}
	#if UseINT
	mStar_EnableModeChangeINT(FALSE);
	#endif
	// 120601 coding addition
	drvADC_PowerCtrl(ADC_POWER_ON);
	drvDVI_PowerCtrl(DVI_POWER_ON);
	if (InputTimingStableFlag)
	{
		SC0_SCALER_RESET(GPR_B);//msWriteByte(SC0_F1, GPR_B);  // Reset Graphic port to re-counter input hfreq & vtotal
		ForceDelay1ms(3);
		SC0_SCALER_RESET(0);//msWriteByte(SC0_F1, 0);
		ForceDelay1ms(10);
	}
	Clr_InputTimingStableFlag(); // reset input timing stable and wait for timing stable
	InputTimingStableCounter = 0;
	SrcFlags &= ~(bUnsupportMode | bUserMode | bNativeMode);
	//msWriteByte(SC0_01, 0x00);        // disable double bufer.
	mStar_ScalerDoubleBuffer(FALSE);
	//msWriteByte(REGBK, REGBANKADC);
	//msWriteByte(SC0_01, 0x00);        // enable ADC's double bufer.
	//msWriteByte(REGBK, REGBANKSCALER);
	msWriteByteMask(SC0_E8, 0, (BIT0 | BIT1));
	msWriteByteMask(SC0_E9, 0, (BIT0 | BIT1));
	#if ENABLE_DP_INPUT
	if(CURRENT_INPUT_IS_DISPLAYPORT())
	{
		#if DP_RESETHTT_PATCH
		msWriteByteMask( REG_3602, BIT5, BIT5);
		msWriteByteMask( REG_3602, 0, BIT5);
		#endif
	}
	#endif
}
//==========================================================
Bool mStar_SyncLossStateDetect(void)
{
	BYTE fStatus;
	Bool result = FALSE;
	//DETECT_printMsg("Sync Loss Detect Function 1");
	fStatus = mStar_GetInputStatus();
	// printData("status %xH", fStatus);//msReadByte(INSTA));
	// printData("stable counter %d", InputTimingStableCounter);
	if (fStatus & SyncLoss)
	{
		if(CURRENT_INPUT_IS_VGA())//( SrcInputType < Input_Digital )
		{
			if(InputTimingStableCounter % ValidTimingStableCount == 0)
				mStar_SetAnalogInputPort((g_bInputSOGFlag ? FALSE : TRUE));
			//DETECT_printMsg("Sync Loss Detect Function 2");
			fStatus = mStar_GetInputStatus();
			if(!(fStatus & SyncLoss))
				goto SyncActive;
		}
		if (CableNotConnectedFlag)
			// no Cable
		{
			if (!IsCableNotConnected())
			{
				#if ENABLE_CABLESTATUSCHANGE_CAUSESYNCSTATUS
				// 091009 coding, add condition for waking up from power saving, comfirmed to Mark
				if(PowerSavingFlag)
				{
					if(!(fStatus & SyncLoss))
					{
						Clr_CableNotConnectedFlag();
						{
							#if Dual
							SwitchPortCntr = 0;
							#endif
							result = TRUE;
						}
					}
				}
				else
				{
					Clr_CableNotConnectedFlag();
					{
						#if Dual
						SwitchPortCntr = 0;
						#endif
						result = TRUE;
					}
				}
				#else
				Clr_CableNotConnectedFlag();
				#endif
			}
		}
		else if (IsCableNotConnected())
			// no Sync
		{
			Set_CableNotConnectedFlag();
			#if ENABLE_CABLESTATUSCHANGE_CAUSESYNCSTATUS
			hw_SetGreenLed();
			hw_ClrAmberLed();
			result = TRUE;
			#endif
		}
		if (PowerSavingFlag)
		{
			if(CURRENT_INPUT_IS_TMDS())//( SrcInputType == Input_Digital || SrcInputType == Input_Digital2 )
			{
				#if ((CHIP_ID == CHIP_TSUMC) || (CHIP_ID == CHIP_TSUMD) || (CHIP_ID == CHIP_TSUM9) || (CHIP_ID == CHIP_TSUMF))
				if(DVI_CLK_STABLE())
				#else
				if(!DVI_CLOCK_IS_MISSING())//(!(msReadByte(SC0_CA) & 0x40)) // coding check stable or exist
				#endif
				{
					//Delay1ms(150);
					Delay1ms(50);
					mStar_PowerUp();
					Delay1ms(50);
					//DETECT_printMsg("DVI clk exist when PwSv detect");
					fStatus = mStar_GetInputStatus();
					if (fStatus & SyncLoss)
					{
						mStar_PowerDown();
					}
					else
					{
						result = TRUE;
					}
				}
				#if ENABLE_MHL&& (CHIP_ID == CHIP_TSUM2)	// 120529 coding modified for MHL wakeup //120509 Modify
				//if(CURRENT_INPUT_IS_HYBRID_MHL_HDMI())
				//if(UserPrefInputSelectType == INPUT_PRIORITY_AUTO || UserPrefInputSelectType == INPUT_PRIORITY_DVI)
				if(MHL_CHECK_CONDITION()) // 120614 coding
					if(mapi_mhl_WakeupDetect())
					{
						result = TRUE;
					}
				#endif
			}
		}
	}
	else
	{
SyncActive:
		result = TRUE;
	}
	if (result)
	{
		SrcFlags = (SrcFlags & 0xF0) | fStatus;
	} // clear others flags, except sync informat (polarity & w/o)
	return result;
}
#if 1//2006-07-07 Andy
Bool mStar_ValidTimingDetect(void)
{
	BYTE fStatus;
	//DETECT_printMsg("Valid timing detect");
	fStatus = mStar_GetInputStatus();
	if( fStatus & SyncLoss )        // no sync
	{
		SrcFlags = ( SrcFlags & 0xF0 ) | fStatus; // clear others flags, except sync informat (polarity & w/o)
		DETECT_printMsg( "Valid Timing : Sync Loss" );//20121031
		return TRUE;
	}
	else
	{
		if( SyncPolarity( SrcFlags ) != SyncPolarity( fStatus ) )            // Sync polarity changed
		{
			SrcFlags = ( SrcFlags & 0xF0 ) | fStatus; // clear others flags, except sync informat (polarity & w/o)
			DETECT_printMsg( "Valid Timing : Sync polarity changed" );//20121031
			if(CURRENT_INPUT_IS_DISPLAYPORT())
				return FALSE;
			else
				return TRUE;
		}
		else
		{
			WORD tempPeriod;
			SrcFlags = ( SrcFlags & 0xF0 ) | fStatus; // clear others flags, except sync informat (polarity & w/o)
			#if ENABLE_FREESYNC
			if(!IS_DP_FREESYNC())
			#endif
			{
				tempPeriod = SC0_READ_HPEROID();//msRead2Byte(SC0_E4) & MASK_13BIT;
				#if DEBUG_FINDMODE  //20121031
				DETECT_printData("HPeriod1 %d", tempPeriod);
				#endif
				if( InputTimingStableCounter == 0 )
				{
					SrcHPeriod = tempPeriod;
				}
				if( abs( tempPeriod - SrcHPeriod ) > HPeriod_Torlance )
					// HPeriod changed
				{
					// 120425 coding addition
					DETECT_printMsg("SrcHPeriod is out of torlance!");
					tempPeriod = SC0_READ_HPEROID();//msRead2Byte(SC0_E4) & MASK_13BIT;
					if( abs( tempPeriod - SrcHPeriod ) > HPeriod_Torlance )
						return TRUE;
				}
			}
			#if ENABLE_FREESYNC
			#if ENABLE_DP_INPUT
			if(CURRENT_INPUT_IS_DISPLAYPORT())
			{
				if(DPRxGetDRRFlag())
				{
					static WORD xdata u16PixelClock = 0;
					WORD xdata u16temp = DPRxGetPixelClk();
					if(abs(u16PixelClock - u16temp) > 8) // 5
					{
						u16temp = DPRxGetPixelClk();
						if(abs(u16PixelClock - u16temp) > 8) // 5
						{
							u16PixelClock = u16temp;
							return TRUE;
						}
					}
				}
			}
			#endif
			#endif
			#if ENABLE_FREESYNC
			if(!IS_HDMI_FREESYNC())
			#endif
			{
				tempPeriod = SC0_READ_VTOTAL();//msRead2Byte(SC0_E2) & MASK_11BIT;
				#if DEBUG_FINDMODE  //20121031
				DETECT_printData("  VTotal1 %d", tempPeriod);
				#endif
				if( InputTimingStableCounter == 0 )
				{
					// 100902 coding addition
					Delay1ms( 100 );
					tempPeriod = SC0_READ_VTOTAL();//msRead2Byte(SC0_E2) & MASK_11BIT;
					SrcVTotal = tempPeriod;
				}
				if( abs( tempPeriod - SrcVTotal ) > VTotal_Torlance )
					// vtotal changed
				{
					DETECT_printMsg("SrcVTotal is out of torlance!");
					#if ENABLE_HDMI // 100902 coding addition
					Delay1ms( 10 );
					tempPeriod = SC0_READ_VTOTAL();//msRead2Byte(SC0_E2) & MASK_11BIT;
					if( abs( tempPeriod - SrcVTotal ) > VTotal_Torlance ) // vtotal changed
					#endif
						return TRUE;
				}
			}
			#if ENABLE_CHECK_TMDS_DE
			if( CURRENT_INPUT_IS_TMDS() )
			{
				if(!InputTimingStableFlag && (InputTimingStableCounter >= (ValidTimingStableCount - 1)))
				{
					SrcTMDSWidth = SC0_READ_AUTO_WIDTH();
					SrcTMDSHeight = SC0_READ_AUTO_HEIGHT();
					SrcTMDSHStart = SC0_READ_AUTO_START_H();
					SrcTMDSVStart = SC0_READ_AUTO_START_V();
				}
			}
			#endif
			if(( CURRENT_INPUT_IS_TMDS() ) && !FreeRunModeFlag )
			{
				tempPeriod = SC0_READ_AUTO_START_H();//msRead2Byte( SC0_80 ) & MASK_12BIT;
				if( abs( tempPeriod - UserPrefHStart ) > HVStartTorlance )
				{
					DETECT_printData( "HStart changed%d", tempPeriod );  //20121031
					return TRUE;
				}
				tempPeriod = SC0_READ_AUTO_START_V();//msRead2Byte( SC0_7E ) & MASK_11BIT;
				if( abs( tempPeriod - UserPrefVStart ) > 2 )
				{
					DETECT_printData( "HStart changed%d", tempPeriod );  //20121031
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}
#endif
#if  (MS_VGA_SOG_EN||FindModeByVwidth || SHARP_VGA_50Hz_Timing)
BYTE GetVSyncWidth(void)
{
	BYTE u8VSyncWidth;
	SC0_VSYNC_WIDTH_REPORT(TRUE);//msWriteByteMask(SC0_FA,BIT0,BIT0);
	u8VSyncWidth = SC0_READ_VSYNC_WIDTH(); //msReadByte(SC0_E2);
	SC0_VSYNC_WIDTH_REPORT(FALSE);//msWriteByteMask(SC0_FA,0,BIT0);
	//PRINT_DATA("u8VSyncWidth=%d",u8VSyncWidth);
	return u8VSyncWidth;
}
#endif
BYTE mStar_GetInputStatus(void)
{
	BYTE fStatus = 0;
	WORD inputValue;
	BYTE status;
	#if ENABLE_FREESYNC
	if(!IS_DP_FREESYNC())
	#endif
	{
		inputValue = SC0_READ_HPEROID();//msRead2Byte(SC0_E4) & MASK_13BIT;
		if( inputValue == 0x1FFF || inputValue < 10 )
		{
			NOSYNC_printMsg(" H peroid is Out of range!");
			fStatus |= bHSyncLoss;
		}
	}
	#if ENABLE_FREESYNC
	if(!IS_HDMI_FREESYNC())
	#endif
	{
		inputValue = SC0_READ_VTOTAL();//msRead2Byte(SC0_E2) & MASK_11BIT;
		if( inputValue == SC_MASK_V || inputValue < 200 ) // 130530 JUN Modify
		{
			fStatus |= bVSyncLoss;
		}
	}
//	DETECT_printData(" V total:  %d",inputValue);
	#if TMDS_SYNC_RECHECK
	if(CURRENT_INPUT_IS_TMDS())
	{
		if(!(SC0_READ_SYNC_STATUS() & BIT6))
		{
			if(HsyncDisappearCounter < SYNC_DISAPPEAR_COUNT)
				HsyncDisappearCounter ++;
			else
				fStatus |= bHSyncLoss;
		}
		else
		{
			HsyncDisappearCounter = 0;
		}
		if(!(SC0_READ_SYNC_STATUS() & BIT7))
		{
			if(VsyncDisappearCounter < SYNC_DISAPPEAR_COUNT)
				VsyncDisappearCounter ++;
			else
				fStatus |= bVSyncLoss;
		}
		else
		{
			VsyncDisappearCounter = 0;
		}
		if(SC0_DE_ONLY_MODE())
		{
			if(TMDS_INPUT_WITHOUT_HV_SYNC())
			{
				//DETECT_printMsg("DE ONLY");
				SC0_SET_DE_OLNY_MODE(FALSE);
				SC0_GLITCH_REMOVAL_ENABLE(FALSE);  //20130422
			}
		}
	}
	#endif
	status = SC0_READ_SYNC_STATUS();//msReadByte(SC0_E1);
	fStatus |= ( status & 0x03 ); // Get input timing polarity
	#if ENABLE_FREESYNC
	if(IS_DP_FREESYNC())
	{
		if(!(status & CSP_B))
		{
			fStatus |= bVSyncLoss;
		}
	}
	#endif
	if(CURRENT_INPUT_IS_TMDS())//( SrcInputType == Input_Digital || SrcInputType == Input_Digital2 )        // input timing is valid while current state is no sync
	{
		if(DVI_DE_STABLE() == FALSE)
		{
			if(DVI_DE_STABLE() == FALSE)
			{
				NOSYNC_printMsg("DVI DE unstable!");
				fStatus |= SyncLoss;
			}
		}
	}
	else if( SyncLossState() && !( fStatus & SyncLoss ) )        // input timing is valid while current state is no sync
	{
		Delay1ms( 20 );
		if( InputTimingChangeFlag )
		{
			return fStatus;
		}
		status = status & SC0_READ_SYNC_STATUS();//msReadByte(SC0_E1);
		if(( status & 3 ) != ( fStatus & 3 ) )
			// polarity is stable
		{
			NOSYNC_printMsg("polarity is unstable!");
			fStatus |= SyncLoss;
		}
		else if( status & 0x30 )
			// SOG or CSync input
		{
			Delay1ms( 20 );
			if( InputTimingChangeFlag )
			{
				return fStatus;
			}
			status = SC0_READ_SYNC_STATUS();//msReadByte(SC0_E1);           // Check if SOG/CSYNC is valid
			if( abs( SC0_READ_VTOTAL() - inputValue ) > 2 )//( abs( (msRead2Byte( SC0_E2 )&MASK_11BIT) - inputValue ) > 2 )
			{
				NOSYNC_printMsg("SOG or CSYNC is not valid!");
				fStatus |= SyncLoss;
			}
			#if  MS_VGA_SOG_EN
			else if (status & SOGD_B)
			{
				#if 0 //Jison 100330, not find mode yet, use STD_MODE_HEIGHT is not reasonable
				u16InputValue = msRead2Byte(SC0_E2);
				PRINT_DATA("V_Display %d", STD_MODE_HEIGHT);
				if ((u16InputValue - STD_MODE_HEIGHT - 6) < GetVSyncWidth())
				{
					PRINT_MSG("SOG Det Err");
					u8FlagStatus |= SYNC_LOSS;
				}
				#else
				{
					BYTE u8Tmp0 = SC0_READ_POWER_DOWN_STATUS(); //msReadByte(SC0_F0);
					BYTE u8Tmp1 = SC0_READ_ADC_COAST_ENABLE_VALUE(); //msReadByte(SC0_ED);
					BYTE u8Tmp2 = SC0_READ_ADC_COAST_START_VALUE(); //msReadByte(SC0_EE);
					BYTE u8Tmp3 = SC0_READ_ADC_COAST_END_VALUE(); //msReadByte(SC0_EF);
					BYTE i;
					//for get stable VSyncWidth
					SC0_SCALER_POWER_DOWN(0, BIT0 | BIT1); //to get vsyncWidth
					SC0_ADC_COAST_ENABLE(0x21);//msWriteByte(SC0_ED, 0x21); //_NEW_SOG_WAKEUP_DET_
					SC0_ADC_COAST_START(0x08);//msWriteByte(SC0_EE, 0x08);
					SC0_ADC_COAST_END(0x05);//msWriteByte(SC0_EF, 0x05);
					Delay1ms(20);
					inputValue = 0;
					for (i = 0; i < 10; i++)
					{
						inputValue = GetVSyncWidth();
						if (inputValue > 15)
							break;
						ForceDelay1ms(2);
					}
					if (inputValue > 15)
					{
						NOSYNC_printMsg("SOG Det Err!");
						fStatus |= SyncLoss;
					}
					SC0_ADC_COAST_ENABLE(u8Tmp1);//msWriteByte(SC0_ED, u8Tmp1);
					SC0_ADC_COAST_START(u8Tmp2);//msWriteByte(SC0_EE, u8Tmp2);
					SC0_ADC_COAST_END(u8Tmp3);//msWriteByte(SC0_EF, u8Tmp3);
					SC0_SCALER_POWER_DOWN(u8Tmp0, 0xFF);
				}
				#endif
			}
			#endif
		}
	}
	return fStatus;
}

Bool IsCableNotConnected( void )
{
	// wait for coding
	return TRUE;
}


#if ENABLE_MHL
#if CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF// demo board	// 130717 william For G15 compiling warning
Bool CurrentInputMHLCablePlugged(void)//130711 william
{
	bit bresult = FALSE; // false means MHL cable NC
	#if ENABLE_MHL_C1
	if(CURRENT_INPUT_IS_HDMI0())
	{
		if(IS_MHL_PORT0_CABLE_CONNECT())
		{
			bresult = TRUE;
			#if DEBUG_HDMI_MHL_CABLE_DETECT
			printData( "MHL0 CableConnect:%x", hwDVI0Cable_Pin );
			#endif
		}
		else
		{
			#if DEBUG_HDMI_MHL_CABLE_DETECT
			printData( "MHL0 CableNotConnect:%x", hwDVI0Cable_Pin );
			#endif
		}
	}
	else
	#endif
	{
		#if ENABLE_MHL_C2
		if(CURRENT_INPUT_IS_HDMI1())
		{
			if(IS_MHL_PORT1_CABLE_CONNECT())
			{
				bresult = TRUE;
				#if DEBUG_HDMI_MHL_CABLE_DETECT
				printData( "MHL1 CableConnect:%x", hwDVI0Cable_Pin );
				#endif
			}
			else
			{
				#if DEBUG_HDMI_MHL_CABLE_DETECT
				printData( "MHL1 CableNotConnect:%x", hwDVI1Cable_Pin );
				#endif
			}
		}
		else
		#endif
		{
			#if ENABLE_MHL_C3
			if(CURRENT_INPUT_IS_HDMI2())
			{
				if(IS_MHL_PORT2_CABLE_CONNECT())
				{
					#if DEBUG_HDMI_MHL_CABLE_DETECT
					printData( "MHL2 CableConnect:%x", hwDVI0Cable_Pin );
					#endif
					bresult = TRUE;
				}
				else
				{
					#if DEBUG_HDMI_MHL_CABLE_DETECT
					printData( "MHL2 CableNotConnect:%x", hwDVI2Cable_Pin );
					#endif
				}
			}
			#endif
		}
	}
	return bresult;
}

#else
#message "please coding CurrentInputMHLCablePlugged for MHL port"
#endif
#endif



void SpeedupOrExtendSwitchPort(void)	//130625 nick
{
	#if ENABLE_MHL
	if(CURRENT_INPUT_MHL_CABLE_PLUGGED())
	{
		if(MHL_EXTEND_SYNCLOSS_COUNT())
		{
			InputTimingStableCounter = SyncLossExtenCount_MHL;
			MHLExtenCountFlag = 1;
		}
	}
	else
	#endif
	#if ENABLE_HDMI
		if(HDMI_SPEEDUP_SWITCH_PORT())
		{
			InputTimingStableCounter = SyncLossStableCount;
		}
	#endif
	#if (ENABLE_DP_INPUT&&(CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF))
//============================================================================================
//  Please add Cable GND pin detect in  below condition
//  ((SrcInputType  == Input_Displayport)&&(msReadByte(REG_0232)&BIT0)&& (Cable GND pin Detect) )
//===================================================================================== =======
	if(Input_Displayport_C2 != Input_Nothing)
	{
		EnablePBSDM();                              // Set SDM Bit as Input
		if(DPPB_SPEEDUP_SDM_GND() && (InputTimingStableCounter >= 50))   //  Check SDM bit Port B 	//130912 nick
		{
			InputTimingStableCounter = SyncLossStableCount;
		}
	}
	if(Input_Displayport_C3  != Input_Nothing)
	{
		EnablePCSDM();                                // Set SDM Bit as Input
		if(DPPC_SPEEDUP_SDM_GND() && (InputTimingStableCounter >= 50))     // Check SDM bit Port C 	//130912 nick
		{
			InputTimingStableCounter = SyncLossStableCount;
		}
	}
	#endif
}

