#include <intrins.h>
#include "types.h"
#include "board.h"
#include "global.h"
#if	(MS_PM)
#include "ms_pm.h"
#endif

#define DelayPeriod ((WORD)CPU_CLOCK_MHZ*78/12)
void Delay4us(void)
{
	#if Enable_Cache    // jeff 12 22 for cache add it
	BYTE i;
	for(i = 0; i < 70; i++) // 50 090421 100 090417
	{
		_nop_();
		_nop_();
	}
	#else
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	#endif
	#if (MS_PM)
	if( g_bMcuPMClock )
	{
		BYTE i;
		for( i = 0; i < PM_DELAY4US_LOOP; i++ )
		{
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
		}
	}
	#endif
}

extern BYTE xdata rxStatus;
void Delay1ms(WORD msNums)
{
	if(!msNums)
		return;
	DelayCounter = msNums;
	bDelayFlag = 1;
	while(bDelayFlag)
	{
		if(InputTimingChangeFlag)
		{
			DelayCounter = 0;
			bDelayFlag = 0;
			break;
		}
	}
}

void ForceDelay1ms(WORD msNums)
{
	if(!msNums)
		return;
	DelayCounter = msNums;
	bDelayFlag = 1;
	while(bDelayFlag);
}

BYTE GetVSyncTime(void)
{
	WORD freq;
	#if ENABLE_FREESYNC
	if(IS_DP_FREESYNC())
	{
		WORD u16PixClk, u16Htt;
		u16PixClk = msAPI_combo_IPGetPixelClk();
		u16Htt = msAPI_combo_IPGetGetHTotal();
		if((u16Htt != 0) && (SrcVTotal != 0))
		{
			freq = ((DWORD)u16PixClk * 100 + u16Htt / 2) / u16Htt;
		}
	}
	else
	#endif
	{
		freq = HFreq( SrcHPeriod ); //get hfreq round 5
	}
	freq = ((WORD)SrcVTotal * 10 + (freq / 2)) / freq;
	return (BYTE)freq;
}

#if ENABLE_HDCP
#if HDCPKEY_IN_Flash
WORD CRC16(BYTE nData, WORD nCRC)
{
	BYTE nMask;
	Bool fFeedback;
	for (nMask = 0x80; nMask; nMask >>= 1)
	{
		fFeedback = (Bool)(((nCRC & 0x8000) ? 1 : 0) ^ ((nMask & nData) ? 1 : 0));
		nCRC <<= 1;
		if (fFeedback)
		{
			nCRC ^= 0x1021;
		}
	}
	return nCRC;
}
#endif
#endif

