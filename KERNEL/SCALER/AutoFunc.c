#include <math.h>
#include "types.h"
#include "board.h"
#include "global.h"
#include "ms_reg.h"
#include "adjust.h"
#include "ms_rwreg.h"
#include "misc.h"
#include "debug.h"
#include "power.h"
#include "panel.h"
#include "drvadc.h"
#include "mstar.h"
#ifdef TSUMXXT//#if (ChipID == TSUMXXT)		//110311 Modify
#include "MsADC.h"
#endif

/////////////////////////////////////
#include "drvmStar.h"
////////////////////////////////////

#define UseWorstPhase   0
#define EvenClock   0
#define QuickAuto   0
#define OverFlow    BIT7
#define NoneOverFlow    BIT6
#define UnderFlow   BIT7
#define NoneUnderFlow   BIT6
//===============================================================
// local declaration
Bool mStar_AutoAdcColor(BYTE vsyncTime);
void CheckDosTextHtotal(BYTE vsyncTime);
//===============================================================
// Code
Bool CheckSyncLoss(void)
{
	#if UseINT
	if (InputTimingChangeFlag)
	{
		Power_TurnOffPanel();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	#else
	Bool result = FALSE;
	if( abs( SrcHPeriod - SC0_READ_HPEROID()) > 10 )//( abs( SrcHPeriod - msRead2Byte(SC0_E4) ) > 10 )
	{
		result = TRUE;
	}
	else if( abs( SrcVTotal - SC0_READ_VTOTAL()) > 10 )//( abs( SrcVTotal - msRead2Byte(SC0_E2) ) > 10 )
	{
		result = TRUE;
	}
	if( result )
	{
		Power_TurnOffPanel();
		Set_InputTimingChangeFlag();
	}
	return result;
	#endif
}
void WaitAutoStatusReady(WORD regAddr, BYTE regFlag)
{
	WORD waits = 0xFFFF;
	while( waits-- && !( msReadByte( regAddr ) &regFlag ) && !SyncLossState());
}

WORD GetAutoValue(WORD regAddr)
{
	AUTO_POSITION_RESULT_READY();//WaitAutoStatusReady(SC0_7B, BIT1);
	return msRead2Byte(regAddr);
}
BYTE GetTranstionPosition(BYTE vsyncTime, WORD regAddr)
{
	BYTE retry = 6;
	BYTE adjPhase;
	WORD pos;
	BYTE minPhase, maxPhase;
	maxPhase = MAX_PHASE_VALUE;
	minPhase = 0x00;
	drvADC_SetPhaseCode( 0 );
	Delay1ms(vsyncTime << 1); //Jison 090514,u8VSyncTime*2 for TSUMP sometime can't get correct AOHEND_H.
	pos = GetAutoValue(regAddr);
	adjPhase = (maxPhase + minPhase) / 2;
	while (retry--)
	{
		drvADC_SetPhaseCode( adjPhase );
		Delay1ms(vsyncTime);
		if (GetAutoValue(regAddr) != pos)
		{
			maxPhase = adjPhase;
		}
		else
		{
			minPhase = adjPhase;
		}
		adjPhase = (maxPhase + minPhase) / 2;
		if (CheckSyncLoss())
		{
			return FALSE;
		}
	}
	//  printData("trans phase %d", adjPhase);
	return (adjPhase);
}
#if !QuickAuto
BYTE AutoSetDataThreshold(BYTE vsyncTime)
{
	BYTE thr;
	BYTE adjPhase;
	WORD regWord1, regWord2;
	for( thr = 3; thr < 0x10; thr++ )
	{
		AUTO_POSITION_SET_VALID_VALUE(thr);//msWriteByte(SC0_7C, thr << 4 );
		drvADC_SetPhaseCode( 0 );
		Delay1ms( vsyncTime );
		AUTO_POSITION_RESULT_READY();//WaitAutoStatusReady(SC0_7B, BIT1);
		regWord1 = SC0_READ_AUTO_START_H();//msRead2Byte(SC0_80);
		#if (MAX_PHASE_VALUE==0x7F)
		for( adjPhase = 7; adjPhase < (MAX_PHASE_VALUE + 1); adjPhase += 7 )
		#else
		for( adjPhase = 4; adjPhase < (MAX_PHASE_VALUE + 1); adjPhase += 4 )
		#endif
		{
			drvADC_SetPhaseCode( adjPhase );
			Delay1ms( vsyncTime );
			AUTO_POSITION_RESULT_READY();//WaitAutoStatusReady(SC0_7B, BIT1);
			regWord2 = SC0_READ_AUTO_START_H();//msRead2Byte(SC0_80);
			if( abs( regWord1 - regWord2 ) > 3 )
				break;
			if( CheckSyncLoss() )
				return FALSE;
		}
		if (adjPhase >= (MAX_PHASE_VALUE + 1))
			break;
	}
	return thr;
}
#endif
WORD SearchMaxWidth(BYTE vsyncTime)
{
	BYTE startPhase;
	WORD hStart, hEnd;
	BYTE ucReg;
	ucReg = AUTO_POSITION_READ_VALID_VALUE();//msReadByte(SC0_7C);
	AUTO_POSITION_SET_VALID_VALUE(AOVDV_VALUE);//msWriteByte(SC0_7C, 0x40);
	drvADC_SetPhaseCode( 0 );
	Delay1ms( vsyncTime );
	Delay1ms( vsyncTime );
	hStart = AUTO_POSITION_READ_HSTART();//GetAutoValue(SC0_80);
	startPhase = AUTO_POSITION_READ_TRANSTION_POSITION(vsyncTime);//GetTranstionPosition( vsyncTime, SC0_80 );
	hEnd = AUTO_POSITION_READ_HEND();//GetAutoValue(SC0_84);
	hStart = hEnd - hStart + 1;
	AUTO_POSITION_SET_VALID_VALUE(ucReg);//msWriteByte(SC0_7C, ucReg);
	Delay1ms(vsyncTime << 1); //Jison 090423, u8VSyncTime*2 wait the status ready because of AOVDV change(Auto Htotal issue).
	return hStart;
}
Bool mStar_AutoHTotal(BYTE vsyncTime)
{
	WORD tempHTotal;
	WORD autoWidth;
	BYTE result;
	// 1st to coast tune HTotal
	drvADC_SetPhaseCode( 0 );
	Delay1ms( vsyncTime );
	autoWidth = AUTO_POSITION_READ_HEND() - AUTO_POSITION_READ_HSTART();//GetAutoValue(SC0_84) - GetAutoValue(SC0_80);
	tempHTotal = StandardModeWidth / 3;
	if( abs( autoWidth - StandardModeWidth ) > tempHTotal )
	{
		drvADC_SetPhaseCode( UserPrefPhase );
		return FALSE;
	}
	tempHTotal = UserPrefHTotal;
	if( abs( autoWidth - StandardModeWidth ) > 1 )
	{
		tempHTotal = ( DWORD )UserPrefHTotal * StandardModeWidth / autoWidth;
		if( abs( tempHTotal - StandardModeHTotal ) > ClockAdjRange )
		{
			goto AutoHTotalFailed;
		}
		drvADC_AdjustHTotal( tempHTotal );
		Delay1ms(vsyncTime);
	}
	autoWidth = SearchMaxWidth( vsyncTime );
	// 2nd fine tune
	if( autoWidth != StandardModeWidth )
	{
		tempHTotal = tempHTotal + ( StandardModeWidth - autoWidth );
		if( abs( tempHTotal - StandardModeHTotal ) > ClockAdjRange )
		{
			goto AutoHTotalFailed;
		}
		drvADC_AdjustHTotal( tempHTotal );
		Delay1ms(vsyncTime);
		autoWidth = SearchMaxWidth( vsyncTime );
		tempHTotal = tempHTotal + ( StandardModeWidth - autoWidth );
	}
	else if( tempHTotal & 1 )
	{
		WORD autoWidth2;
		//tempHTotal=tempHTotal-1;
		drvADC_AdjustHTotal( tempHTotal - 1 );
		autoWidth = SearchMaxWidth( vsyncTime );
		drvADC_AdjustHTotal( tempHTotal + 1 );
		autoWidth2 = SearchMaxWidth( vsyncTime );
		if( autoWidth2 == StandardModeWidth )
		{
			tempHTotal = tempHTotal + 1;
		}
		else if( autoWidth == StandardModeWidth )
		{
			tempHTotal = tempHTotal - 1;
		}
	}
	#if EvenClock
	if( tempHTotal % 4 )
	{
		tempHTotal = (( tempHTotal + 1 ) / 4 ) * 4;
	}
	#endif
AutoHTotalFailed:
	result = FALSE;
	if( abs( tempHTotal - StandardModeHTotal ) < ClockAdjRange )
	{
		UserPrefHTotal = tempHTotal;
		result = TRUE;
	}
	drvADC_AdjustHTotal( UserPrefHTotal );
	drvADC_SetPhaseCode( UserPrefPhase );
	return result;
#undef result
}
Bool mStar_AutoPhase(BYTE vsyncTime)
{
	BYTE adjPhase, i;
	#if UseWorstPhase
	BYTE worsePhase, worsePhase2;
	DWORD mincksum, cksum;
	mincksum = 0xFFFFFFFFul;
	for( adjPhase = 0; adjPhase < 0x80; adjPhase += 7 )
	{
		drvADC_SetPhaseCode( adjPhase );
		Delay1ms( vsyncTime );
		AUTO_PHASE_RESULT_READY();//drvADC_WaitAutoStatusReady(SC0_8B, BIT1);
		//cksum = msRead2Byte(SC0_8E);
		//cksum = ( cksum << 16 ) | msRead2Byte(SC0_8C);
		cksum = AUTO_PHASE_READ_VALUE();
		if( cksum < mincksum )
		{
			mincksum = cksum;
			worsePhase = adjPhase;
		}
		if( CheckSyncLoss() )
			return FALSE;
	}
	// 2nd Search
	if (worsePhase < 7)
		worsePhase = (worsePhase + 127) % 0x80; // 128-7
	else
		worsePhase -= 7;
	mincksum = 0xFFFFFFFFul;
	for (adjPhase = worsePhase; adjPhase < worsePhase + 10; adjPhase++)
	{
		i = adjPhase % 0x80;
		drvADC_SetPhaseCode( i );
		Delay1ms( 2 * vsyncTime );
		AUTO_PHASE_RESULT_READY();//drvADC_WaitAutoStatusReady(SC0_8B, BIT1);
		//cksum = msRead2Byte(SC0_8E);
		//cksum = ( cksum << 16 ) | msRead2Byte(SC0_8C);
		cksum = AUTO_PHASE_READ_VALUE();
		if( cksum < mincksum )
		{
			mincksum = cksum;
			worsePhase2 = i;
		}
		if( CheckSyncLoss() )
			return FALSE;
	}
	UserPrefPhase = ( worsePhase2 + 63 ) % 0x80;
	#else
	BYTE bestPhase, bestPhase2;
	DWORD maxcksum, cksum;
	maxcksum = 0;
	for( adjPhase = 0; adjPhase < 0x80; adjPhase += 7 )
	{
		drvADC_SetPhaseCode( adjPhase );
		Delay1ms( 2 * vsyncTime );
		AUTO_PHASE_RESULT_READY();//drvADC_WaitAutoStatusReady(SC0_8B, BIT1);
		//cksum = msRead2Byte(SC0_8E);
		//cksum = ( cksum << 16 ) | msRead2Byte(SC0_8C);
		cksum = AUTO_PHASE_READ_VALUE();
		if( cksum > maxcksum )
		{
			maxcksum = cksum;
			bestPhase = adjPhase;
		}
		if( CheckSyncLoss() )
			return FALSE;
	}
	// 2nd Search
	if ( bestPhase < 7 )
		bestPhase = (bestPhase + 121) % 0x80; // 128-7
	else
		bestPhase -= 7;
	maxcksum = 0;
	for( adjPhase = bestPhase; adjPhase < bestPhase + 10; adjPhase++)
	{
		i = adjPhase % 0x80;
		drvADC_SetPhaseCode( i );
		Delay1ms( vsyncTime );
		AUTO_PHASE_RESULT_READY();//drvADC_WaitAutoStatusReady(SC0_8B, BIT1);
		//cksum = msRead2Byte(SC0_8E);
		//cksum = ( cksum << 16 ) | msRead2Byte(SC0_8C);
		cksum = AUTO_PHASE_READ_VALUE();
		if( cksum > maxcksum )
		{
			maxcksum = cksum;
			bestPhase2 = i;
		}
		if( CheckSyncLoss() )
			return FALSE;
	}
	UserPrefPhase = bestPhase2;
	#endif
	drvADC_SetPhaseCode( UserPrefPhase );
	return TRUE;
}
Bool mStar_AutoPosition(void)
{
	WORD height, width;
	WORD actHeight;
	WORD hStart, vStart;
	hStart = AUTO_POSITION_READ_HSTART();//GetAutoValue(SC0_80);
	vStart = AUTO_POSITION_READ_VSTART();//GetAutoValue(SC0_7E);
	if( hStart > StandardModeWidth || vStart > StandardModeHeight )
	{
		return FALSE;
	}
	if( StandardModeGroup == Res_640x350 && abs( StandardModeVFreq - 700 ) < 10 )
	{
		if( vStart > ( 2 * StandardModeVStart ) )
		{
			UserPrefVStart = StandardModeVStart;
			if( AUTO_POSITION_READ_VEND() < ( StandardModeVStart + StandardModeHeight - 10 ) ) //if( GetAutoValue(SC0_82) < ( StandardModeVStart + StandardModeHeight - 10 ) )
				UserPrefHStart = StandardModeHStart;
			else
				UserPrefHStart = hStart;
		}
		else
		{
			UserPrefHStart = hStart;
			UserPrefVStart = vStart;
		}
	}
	else
	{
		width = AUTO_POSITION_READ_HEND() - hStart + 1;//GetAutoValue(SC0_84) - hStart + 1;
		height = AUTO_POSITION_READ_VEND() - vStart + 1;//GetAutoValue(SC0_82) - vStart + 1;
		#if DECREASE_V_SCALING
		actHeight = SC0_READ_IMAGE_HEIGHT() - DecVScaleValue; //(msRead2Byte(SC0_09)&SC_MASK_V)-DecVScaleValue;
		#else
		actHeight = SC0_READ_IMAGE_HEIGHT();//(msRead2Byte(SC0_09)&SC_MASK_V);
		#endif
		if( UserModeFlag )
		{
			if( height < ( StandardModeHeight * 2 / 3 ) || width < ( StandardModeWidth * 2 / 3 ) )
			{
				UserPrefHTotal = StandardModeHTotal;
				drvADC_AdjustHTotal( UserPrefHTotal );
				UserPrefHStart = StandardModeHStart;
				UserPrefVStart = StandardModeVStart;
				UserPrefAutoHStart = StandardModeHStart;
				UserPrefAutoVStart = StandardModeVStart;
				return FALSE;
				//goto AutoPositionFail;
			}
		}
		else if( height < ( StandardModeHeight - 80 ) || width < ( StandardModeWidth - 120 ) )
		{
			UserPrefHTotal = StandardModeHTotal;
			drvADC_AdjustHTotal( UserPrefHTotal );
			UserPrefHStart = StandardModeHStart;
			UserPrefVStart = StandardModeVStart;
			UserPrefAutoHStart = StandardModeHStart;
			UserPrefAutoVStart = StandardModeVStart;
			return FALSE;
			//goto AutoPositionFail;
		}
		if(DecVScaleFlag)
		{
			actHeight = actHeight - DecVScaleValue;
		}
		if( actHeight > height || UserModeFlag )
		{
			height = ( actHeight - height ) / 2;
			if( vStart > height )
			{
				UserPrefVStart = ( vStart - height );
			}
			else
			{
				UserPrefHTotal = StandardModeHTotal;
				drvADC_AdjustHTotal( UserPrefHTotal );
				UserPrefHStart = StandardModeHStart;
				UserPrefVStart = StandardModeVStart;
				UserPrefAutoHStart = StandardModeHStart;
				UserPrefAutoVStart = StandardModeVStart;
				return FALSE;
				//goto AutoPositionFail;
			}
		}
		else
		{
			UserPrefVStart = vStart;
		}
		#if PANEL_WIDTH==1366&&PANEL_HEIGHT==768	//120115 Modify
		// input 1360x768 display on 1366 panel
		// input 1360 get 1366, so -3 is in center position.
		if(PanelWidth == 1366)
		{
			if(StandardModeGroup == Res_1360x768)
				UserPrefHStart = hStart - 3;
			else
				UserPrefHStart = hStart;
		}
		else
		#endif
			UserPrefHStart = hStart;
	} //2006-02-23 Andy
	//AutoPositionFail:
	if (SrcInputType == Input_Digital || SrcInputType == Input_Digital2)
		UserPrefHStart -= 0x10;
	//printData("H After auto %d",UserPrefHStart);
	//printData("V After auto %d",UserPrefVStart);
	mStar_AdjustHPosition(UserPrefHStart); //msWrite2Byte( SC0_07, UserPrefHStart );
	mStar_AdjustVPosition(UserPrefVStart);
	return TRUE;
}
// Auto Color Setting
//==================================================================
//2006-03-30 Andy
Bool mStar_AutoGeomtry(void)
{
	Bool result = TRUE;
	BYTE vsyncTime;
	// 100512 coding addition
	if(InputTimingChangeFlag)
		return FALSE;
	vsyncTime = GetVSyncTime();
	if(CURRENT_INPUT_IS_VGA())
	{
		mStar_ScalerDoubleBuffer(FALSE);
		// wait for coding and check
		//msADC_AdjustAdcGain( 0xA0, 0xA0, 0xA0 );
		//msADC_AdjustAdcOffset( 0xA0, 0xA0, 0xA0 );
		// auto adjust threshold
		#if QuickAuto
		AUTO_POSITION_SET_VALID_VALUE(AOVDV_VALUE);//msWriteByte( BK0_7C, 0x40 );
		#else
		AutoSetDataThreshold( vsyncTime * 2 );
		#endif
		if( InputTimingChangeFlag )
		{
			result = FALSE;
			goto AutoGeomtryFailed;
		}
		// auto adjust htotal
		result = mStar_AutoHTotal( vsyncTime * 2 );
		if( !result )
			goto AutoGeomtryFailed;
		if( InputTimingChangeFlag )
		{
			result = FALSE;
			goto AutoGeomtryFailed;
		}
		// auto adjust phase
		if( result )
		{
			//msADC_AdjustAdcGain(UserPrefAdcRedGain, UserPrefAdcGreenGain, UserPrefAdcBlueGain);
			//msADC_AdjustAdcOffset(UserPrefAdcRedOffset, UserPrefAdcGreenOffset, UserPrefAdcBlueOffset);
			#if 0//PANEL_WIDTH==1366&&PANEL_HEIGHT==768
			if( StandardModeGroup == Res_1366x768 && abs( StandardModeVFreq - 600 ) < 10 ) // Check 1366 x768 60 Hz HTotal
				CheckHtotal();
			#endif
			mStar_AutoPhase( vsyncTime * 2 ); //2006-02-12 +3);
		}
		if( InputTimingChangeFlag )
		{
			result = FALSE;
			goto AutoGeomtryFailed;
		}
		Delay1ms( vsyncTime * 3 );
		if( mStar_AutoPosition() )            //Clock fail, but auto positon success still return true
		{
		}
	}
AutoGeomtryFailed:
	//msWriteByte( BK0_7C, 0x40 );
	//msWriteByte( BK0_01, 0x05 );
	AUTO_POSITION_SET_VALID_VALUE(AOVDV_VALUE);//msWriteByte(SC0_7C, AOVDV_VALUE);
	mStar_ScalerDoubleBuffer(TRUE);
	//drvADC_SetRGBGainCode(UserPrefAdcRedGain, UserPrefAdcGreenGain, UserPrefAdcBlueGain);
	//drvADC_SetRGBOffsetCode(UserPrefAdcRedOffset, UserPrefAdcGreenOffset, UserPrefAdcBlueOffset);
	return result;
}
Bool mStar_AutoColor(void)
{
	Bool result;
	BYTE vsyncTime;
	vsyncTime = GetVSyncTime();
	result = drvADC_AutoAdcColor(vsyncTime * 2);
	if (InputTimingChangeFlag)
	{
		return FALSE;
	}
	return result;
}
