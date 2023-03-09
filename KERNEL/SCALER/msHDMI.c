#ifndef _MSHDMI_C_
#define _MSHDMI_C_
#include "types.h"
#include "board.h"
#include "Global.h"
#include "Adjust.h"
#include "ms_Reg.h"
#include "ms_rwreg.h"
#include "msHDMI.h"
#include "Debug.h"
#include <math.h>

#include "misc.h"
#include "GPIO_DEF.h"

#if  ENABLE_HDMI_1_4
#include "msScaler.h"
#endif
#if ENABLE_RTE
#include "drvmsovd.h"
#endif

#if ENABLE_HDMI

extern void mStar_SetUserPref(void);

#define HDMI_DEBUG   0
#if ENABLE_DEBUG &&HDMI_DEBUG
#define HDMI_printData(str, value)   printData(str, value)
#define HDMI_printMsg(str)           printMsg(str)
#else
#define HDMI_printData(str, value)
#define HDMI_printMsg(str)
#endif


void mstar_HDMIInitialVariable( void )
{
	gScInfo.InputColor = INPUT_RGB;
	gScInfo.InputColorimetry = YUV_Colorimetry_ITU601;
	gScInfo.InputSource = INPUT_TMDS_A;
	gScInfo.InputTmdsType = TMDS_DVI;
	gScInfo.ColorChanged = 0;
	gScInfo.ModeChange = 0;
	gScInfo.wAviPktLossCnt = 0;
	gScInfo.InputPacketStatus = 0;
	#if ENABLE_HDMI_1_4
	gScInfo.NoVsPktCnt = 0;
	#endif
	gScInfo.AudioOffDebunce = 0;
	gScInfo.InputPacketError = 0;
	gScInfo.InputVideoMode = 16; // check here
	gScInfo.InputAVIInfoReceived = 0;
	#if ENABLE_FREESYNC
	gScInfo.InputSPDInfoReceived = 0;
	#endif
	gScInfo.OutputAudioState = HDMI_AUDIO_OFF; //Mute
	gScInfo.OutputDataState = HDMI_DATA_OUTPUT_OFF;
	#if ENABLE_HDMI_SW_CTS_STABLE
	gScInfo.InputCTSValue = 0;
	gScInfo.OutputAudioCnt = AudioDeBounce;
	#endif
	gScInfo.cs0 = 0;
	#if ENABLE_CTS_INT && ENABLE_CTSN_FILTER	//130814 jb
	gScInfo.ucAudioErrorEvents.bAVMUTE = 0;
	#endif
	#if  0
	CSpcPollingCounter = 0;
	#endif
}

void mstar_HDMIInitialAudio( void )
{
	drv_mstar_HDMIInitialAudio();
}

void mstar_HDMIHandler( void )
{
	mstar_MonitorHDMI();//2这是主要的流程
	mstar_HDMIHandleColor();
	mstar_HDMIHandleMode();
}


void mstar_HDMIRst( BYTE rst )
{
	drv_mstar_HDMIRst(rst);
}

void mstar_HDMIHandleMode( void )
{
	//BYTE    temp;
	if( gScInfo.ModeChange )
	{
		gScInfo.ModeChange = 0;
		Set_InputTimingChangeFlag();
		HDMI_printData( "TMDS mode is=%d", gScInfo.InputTmdsType );
	}
}
void mstar_HDMIHandleColor( void )
{
	if( gScInfo.ColorChanged )
	{
		gScInfo.ColorChanged = 0;
		mStar_SetUserPref();
		HDMI_printData( "Handle HDMI CSC%d", gScInfo.InputColor );
	}
}
#if  0
void mstar_HDMIResetColorSpace( void )
{
	BYTE temp, reg_bank;
	HDMI_printMsg( "HDMIResetColorSpace ");
	reg_bank = msReadByte( BK0_00 );
	msWriteByte( BK0_00, REGBANK0 );
	if( msReadByte( BK0_5C )&BIT3 )
	{
		temp = msReadByte( BK0_5A ) | BIT7 | BIT6;
		msWriteByte( BK0_5A, temp );
	}
	temp = msReadByte( BK0_02 ) & ( ~BIT3 );
	msWriteByte( BK0_02, temp );
	SetMainWinVideoDomain( INPUT_RGB );     //MainWin Color Space Change YUV -> RGB
	msWriteByte( BK0_00, reg_bank );
}
#endif
void mstar_MonitorHDMI( void )
{
	BYTE temp, curr_color;
	if( HdmiPollingCounter == 0 )
	{
		HdmiPollingCounter = 20;
		if(CURRENT_INPUT_IS_TMDS())//( SrcInputType == Input_Digital || SrcInputType == Input_Digital2 )
		{
			if( SrcFlags & ( SyncLoss | bUnsupportMode ) ) // unsupport mode
			{
				if( gScInfo.OutputAudioState != HDMI_AUDIO_OFF )
					mstar_HDMIAudioMute( HDMI_AUDIO_OFF ); // mute audio
			}
			else if( InputTimingStableFlag )
			{
				temp = mstar_HDMITmdsGetType();
				if( temp != gScInfo.InputTmdsType )
				{
					gScInfo.InputTmdsType = temp;
					gScInfo.InputPacketStatus = 0;
					gScInfo.ModeChange = 1;
					return;
				}
				// 120604 coding modified for reading packet status is unnecessary for DVI mode.
				if(temp == TMDS_DVI)
				{
					mstar_HDMIRst(Reset_HDMIStatus);
					return;
				}
				mstar_HDMIGetPktStatus();
				mstar_HDMICheckAudio();
				mstar_HDMIAutoEQProc();
				#if ENABLE_HDMI_1_4
				msHDMI_Check_3D_Mode_Chg(1);
				if(InputTimingChangeFlag)
					return;
				#endif
				#if (ENABLE_CTS_INT && (ENABLE_CTSN_FILTER || ENABLE_AUDIO_AUTO_MUTE || ENABLE_AUDIO_AUTO_FADING))
				CheckAudioErrorStatus();
				#endif
				if( gScInfo.InputPacketStatus & BIT3 )
				{
					gScInfo.wAviPktLossCnt = 0;
					curr_color = mstar_HDMIPacketColor();
					if( curr_color != gScInfo.InputColor )
					{
						gScInfo.InputColor = curr_color;
						gScInfo.ColorChanged = 1;
						if(curr_color == INPUT_RGB)
							InputColorFormat = INPUTCOLOR_RGB;
						else
							InputColorFormat = INPUTCOLOR_YUV;
					}
				}
				else
				{
					if( gScInfo.wAviPktLossCnt >= AviPktLossBound )
					{
						if( gScInfo.InputColor != INPUT_RGB )
						{
							gScInfo.InputColor = INPUT_RGB;
							InputColorFormat = INPUTCOLOR_RGB;
							mstar_HDMIRst(Reset_Color);
							gScInfo.ColorChanged = 1;
						}
					}
				}
			}
		}
	}
}
//BYTE xdata bAudioInputStatus;
#message "Please check the audio"
void mstar_HDMICheckAudio( void )
{
	BYTE temp;
	#if ENABLE_HDMI_SW_AUDCLK_CHECK
	BYTE ucCurInFreq;
	#endif
	if( (gScInfo.InputPacketError & ( BIT5 | BIT4 )) ) //|| gScInfo.cs0 & BIT6 ) //audio sample error
	{
		temp = HDMI_AUDIO_OFF;
	}
	else if(( gScInfo.InputPacketStatus & ( BIT6 | BIT5 ) ) == ( BIT6 | BIT5 ) )
	{
		/* if( (bAudioInputStatus)&&(UserPrefVolume == 0 || UserPrefMuteState))
		     temp = HDMI_AUDIO_OFF;
		 else
		 */
		{
			if( gScInfo.OutputDataState == HDMI_DATA_OUTPUT_ON )
				temp = HDMI_AUDIO_ON;
			else
				temp = HDMI_AUDIO_OFF;
		}
		#if ENABLE_HDMI_SW_CTS_STABLE
		if( gScInfo.OutputAudioCnt ) // && gScInfo.OutputAudioState==HDMI_AUDIO_ON)    // Check CTS Value Stable
			temp = HDMI_AUDIO_OFF;
		#endif
	}
	else
		temp = HDMI_AUDIO_OFF;
	if( gScInfo.OutputAudioState == HDMI_AUDIO_ON && temp == HDMI_AUDIO_OFF )
	{
		if( ++gScInfo.AudioOffDebunce < 20 )
			return ;
	}
	else
		gScInfo.AudioOffDebunce = 0;
	#if ENABLE_HDMI_SW_AUDCLK_CHECK// 20080403 audio clock over spec
	ucCurInFreq = mstar_HDMICheckAudioFreq();
	if( temp == HDMI_AUDIO_ON )
	{
		if(( ucCurInFreq > AUD_FREQ_ERROR ) )
		{
			if( ucCurInFreq != gScInfo.CurOutAudFreq )
			{
				if( ++gScInfo.FreqStableDebunce > 1 ) // > "1" this value can be adjust
				{
					gScInfo.CurOutAudFreq = ucCurInFreq;
					mstar_SetAudioClockLock( TRUE ); // chip w
				}
			}
			else
				gScInfo.FreqStableDebunce = 0;
		}
		else
		{
			if( ucCurInFreq != gScInfo.CurOutAudFreq )
			{
				if( ++gScInfo.FreqStableDebunce > 3 )
				{
					HDMI_printData( "--Input Audio Freq Error[%d]--", gScInfo.CurOutAudFreq );
					gScInfo.CurOutAudFreq = ucCurInFreq;
					if( temp == HDMI_AUDIO_ON )
						temp = HDMI_AUDIO_OFF;
				}
			}
			else
				gScInfo.FreqStableDebunce = 0;
		}
	}
	#endif
	if( temp != gScInfo.OutputAudioState )
	{
		mstar_HDMIAudioMute( temp );
	}
}

BYTE mstar_HDMIPacketColor( void )
{
	return drv_mstar_HDMIPacketColor();
}


void mstar_HDMIAudioMute( BYTE sw )
{
	drv_mstar_HDMIAudioMute(sw);
}

void mstar_HDMIGetPktStatus( void )
{
	drv_mstar_HDMIGetPktStatus();
}
#if (ENABLE_FREESYNC&&ENABLE_HDMI)
Bool mstar_HDMIGetFreeSyncFlag( void )
{
	#if 1
	if(gScInfo.InputPacketStatus == 0) //170118 Test
	{
		mstar_HDMIGetPktStatus();
	}
	if(gScInfo.InputSPDInfoReceived)
	{
		return drv_mstar_HDMIGetFreeSyncFlag();
	}
	else
		return FALSE;
	#else
	if(gScInfo.InputSPDInfoReceived)
		return drv_mstar_HDMIGetFreeSyncFlag();
	else
		return FALSE;
	#endif
}
#endif

void mstar_HDMIAutoEQProc(void)
{
	drv_mstar_HDMIAutoEQProc();
}

BYTE mstar_HDMITmdsGetType( void )
{
	return drv_mstar_HDMITmdsGetType();
}

#if ENABLE_CTS_INT
#if ENABLE_CTSN_FILTER
/*
void EnableCTSNFileterFunction( void )
{
    drv_EnableCTSNFileterFunction();
}

void CheckCTSNFilterFunction( void )
{
    drv_CheckCTSNFilterFunction();
}
*/
#else
void EnableCTSFileterFunction( void )
{
	drv_EnableCTSFileterFunction();
}

void CheckCTSFilterFunction( void )
{
	drv_CheckCTSFilterFunction();
}
#endif
#endif
#if ENABLE_HDMI_SW_AUDCLK_CHECK   // 20080403 audio clock over spec
//*******************************************************************
// Function Name: mstar_HDMICheckAudioFreq
// Decscription: N/CTS = (128 fs)/(TMDS_Clk)
//*******************************************************************
AudioFreqType mstar_HDMICheckAudioFreq( void )
//BYTE mstar_HDMICheckAudioFreq(void)
{
	return drv_mstar_HDMICheckAudioFreq();
}

void mstar_SetAudioClockLock( Bool bLock )
{
	drv_mstar_SetAudioClockLock(bLock);
}
#endif // #if EN_HDMI_SW_AUDCLK_CHECK

#if ENABLE_AUDIO_AUTO_MUTE || ENABLE_AUDIO_AUTO_FADING || ENABLE_CTSN_FILTER

///////////////////////////////////////////////////////////////////////////////
//     Audio mute/fading events:
//     [0]: HDMI audio sample error.
//     [1]: HDMI audio sample parity error.
//     [2]: HDMI non-PCM.
//     [3]: HDMI AVMUTE.
//     [4]: HDMI CTS/N over range.
//     [5]: HDMI no input clock.
//     [6]: HDMI video clock big change.
//     [7]: HDMI audio sample channel status information changes.
//     [8]: HDMI 2-channel audio sample present bit error.
//     [9]: HDMI audio sample flat bit is set.
///////////////////////////////////////////////////////////////////////////////
void CheckAudioErrorStatus( void )
{
	drv_CheckAudioErrorStatus();
}

#endif // #if ENABLE_AUDIO_AUTO_MUTE || ENABLE_AUDIO_AUTO_FADING || ENABLE_CTSN_FILTER
#if ENABLE_HDMI_1_4
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                                HDMI 1.4 new feature:
//                                1. 3D format
//                                2. 4K x 2K format
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// HDMI_Video_Format: Vendor Specifc Info-frame, PB4[7:5]
//   000: No additional HDMI video format is presented in this packet
//   001: Extended resolution format (e.g. 4Kx2K video) present
//   010: 3D format indication present
//   011~111: Reserved
E_HDMI_ADDITIONAL_VIDEO_FORMAT msHDMI_Check_Additional_Format(void)
{
	return drv_msHDMI_Check_Additional_Format();
}


// 3D_Structure: Vendor Specifc Info-frame, PB5[7:4]
//   0000: Frame packing
//   0001: Field alternative
//   0010: Line alternative
//   0011: Side-by-Side(Full)
//   0100: L+depth
//   0101: L+depth+graphics+graphics-depth
//   0110: Top-and-Bottom
//   0111: Reserved
//   1000: Side-by-Side(Half)
//   1001 ~ 1111: Reserved
E_HDMI_3D_INPUT_MODE msHDMI_Get_3D_Structure(void)
{
	return drv_msHDMI_Get_3D_Structure();
}

void msHDMI_Check_3D_Mode_Chg(BYTE SetTimingChg)
{
	BYTE ucSCFmtIn = SC_FMT_IN_NORMAL;
	if(InputTimingChangeFlag || DisplayLogoFlag)//(InputTimingChangeFlag || DisplayLogoFlag || DoModeSettingFlag)
		return;
	gScInfo.NoVsPktCnt++;
	if( gScInfo.InputPacketStatus & BIT7 )
	{
	}
	if( ((ucSCFmtIn != g_SetupPathInfo.ucSCFmtIn) && ( (gScInfo.NoVsPktCnt == 0) || (gScInfo.NoVsPktCnt >= NoVsPktBound))) )
	{
		HDMI_printData("HDMI 3D FMT CHG : %d", ucSCFmtIn);
		gScInfo.NoVsPktCnt = 0;
		if(!g_SetupPathInfo.bOverrideSCFmtIn)
		{
			g_SetupPathInfo.ucSCFmtIn = ucSCFmtIn;
			if ( SetTimingChg )
			{
				Set_InputTimingChangeFlag();
			}
		}
	}
}
#endif // #if ENABLE_HDMI_1_4

#endif//#if ENABLE_HDMI
#endif
