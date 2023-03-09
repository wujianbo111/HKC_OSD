
#include "global.h"

#define DEBUG_PANEL_TIMING      0

#if ENABLE_DEBUG && DEBUG_PANEL_TIMING
#define PANEL_TIMING_printData(str, value)   printData(str, value)
#define PANEL_TIMING_printMsg(str)               printMsg(str)
#else
#define PANEL_TIMING_printData(str, value)
#define PANEL_TIMING_printMsg(str)

#endif

BYTE FPLLTimeoutCounter; // 121120 coding addition, unit: 50mS

WORD mSTar_GetInputHTotal(void)
{
	WORD u16HTotal;
	msWriteByteMask(SC0_ED, BIT6, BIT6);
	u16HTotal = (msRead2Byte(SC0_E4) & 0x1FFF) + 1; //get input HTotal
	msWriteByteMask(SC0_ED, 0, BIT6);
	return u16HTotal;
}

#define HTOTAL_OUTPUT_TOLERANCE     10
#define VTOTAL_OUTPUT_TOLERANCE     10

// 121113 coding addition, calculate output dclk with ssc to comapre panel dclk limitation
#if ENABLE_FACTORY_SSCADJ
#define PANEL_SSC_PERCENTAGE    (FactorySetting.SSCPercentage)
#else
#define PANEL_SSC_PERCENTAGE    (PANEL_SSC_PERCENTAGE_DEF)
#endif
#define MAX_DCLK_WITH_SSC(wDclk)     (wDclk+((wDclk * PANEL_SSC_PERCENTAGE/10) / 100)+1)
#define MIN_DCLK_WITH_SSC(wDclk)     (wDclk-((wDclk * PANEL_SSC_PERCENTAGE/10) / 100)-1)

#define OUTPUT_VTOTAL_PROTECT   0 // 121113 coding addition, set to 1 for prevent output vtotal over panel spec

#if OUTPUT_VTOTAL_PROTECT
#define OUTPUT_VTOTAL   ((DWORD)PanelHeight*GetStandardModeVTotal()/GetStandardModeHeight()+1)
#endif

Bool appmStar_SetPanelTiming( void )
{
	DWORD factor;
	WORD dclk;
	WORD sclk;
	WORD height;
	WORD dstHTotal;
	WORD hPeriod;
	#if ENABLE_CHECK_PANEL_VTOTAL
	WORD xdata u16OutVtt = 0;
	WORD xdata u16PanelMaxVotal = 0;
	#endif
	// for getting more accurate output htotal //0812 for AC speed switch
	if( SrcHPeriod > 511 )        // prevent counter overflow when input frequency is very low
	{
		hPeriod = SrcHPeriod * 16;
	}
	else
	{
		#if UseINT
		mStar_EnableModeChangeINT(FALSE);
		#endif
		sclk = GetVSyncTime() * 8; ///3
		SC0_HPEROID_DETECT_MODE(TRUE);//msWriteByte(SC0_E5, BIT7); // enable 16 line line to calculate hsync period.
		Delay1ms( sclk );
		hPeriod = SC0_READ_HPEROID();//msRead2Byte(SC0_E4)&MASK_13BIT;
		SC0_HPEROID_DETECT_MODE(FALSE);//msWriteByte(SC0_E5, 0);
		Delay1ms( sclk );
		if( abs( hPeriod - SrcHPeriod * 16 ) > 80 )
			// prevent from getting the wrong hperiod to generate unknown panel clock
		{
			hPeriod = SrcHPeriod * 16;
		}
		#if UseINT
		mStar_EnableModeChangeINT(TRUE);
		#endif
	}
	// calculate input timing dot clock for comparing with output dot clock
	if(CURRENT_INPUT_IS_VGA())
		sclk = (( DWORD )UserPrefHTotal * MST_HPeriod_UINT ) / (( DWORD )hPeriod * 1000 );
	else
	{
		dclk = mSTar_GetInputHTotal();
		sclk = (( DWORD )dclk * MST_HPeriod_UINT ) / (( DWORD )hPeriod * 1000 );
	}
	PANEL_TIMING_printData( "  sclk=%d", sclk );
	height = SC0_READ_IMAGE_HEIGHT();//msRead2Byte(SC0_09)&SC_MASK_V;
	#if ENABLE_CHECK_PANEL_VTOTAL	//Calc uput Vtt need before Interlace mode u16Hight/2
	// calc output vtt
	u16OutVtt = ( ( DWORD ) SrcVTotal * PanelHeight + ( height - 1 ) ) / height;
	#endif
	if( CURRENT_SOURCE_IS_INTERLACE_MODE() )
	{
		height /= 2;
	}
	dstHTotal = PanelMinHTotal + HTOTAL_OUTPUT_TOLERANCE;
	//***************************************************************
	if( sclk )
	{
		// in expansion mode, chip will assume output clock is faster than input clock,
		// if input clock is faster than output clock, must make output clock faster than input clock
		factor = (( float )dstHTotal * ( PanelHeight - 1 ) * MST_HPeriod_UINT ) / (( DWORD )hPeriod * ( height - 1 ) ); // output dclk
		dclk = ( factor + 500 ) / 1000;
		DecVScaleValue = 0;
		#if 1 // 121113 coding modified
		if(MAX_DCLK_WITH_SSC(dclk) > PanelMaxDCLK)
		{
			WORD wHeight;
			if(CURRENT_SOURCE_IS_INTERLACE_MODE())
				height *= 2;
			factor = (PanelMaxDCLK - (((PanelMaxDCLK * PANEL_SSC_PERCENTAGE / 10) + 50) / 100)) * 1000ul;
			DecVScaleValue  = ((float)XTAL_CLOCK_KHZ * 16UL / hPeriod  * dstHTotal * (PANEL_HEIGHT - 1) / factor) + 1; // output dot clock in KHz
			DecVScaleValue = (DecVScaleValue + 1) & ~BIT0;
			if(SrcVTotal >= (DecVScaleValue + VTOTAL_OUTPUT_TOLERANCE) )
			{
				DecVScaleValue = DecVScaleValue - height;
			}
			else
			{
				SrcFlags |= bUnsupportMode;
				return FALSE;
			}
			//modified some timing display unsymmetrically
			DecVScaleValue = ((VSTART_OFFSET >= SC0_READ_AUTO_START_V()) ? (SC0_READ_AUTO_START_V() * 2) : (DecVScaleValue));
			Set_DecVScaleFlag();	//120424 Modify
			wHeight = height + DecVScaleValue;
			if(CURRENT_SOURCE_IS_INTERLACE_MODE())
				wHeight /= 2;
			factor = ((float)dstHTotal * (PANEL_HEIGHT - 1) * MST_HPeriod_UINT) / ((DWORD)hPeriod * (wHeight - 1)); // output dclk
			dclk = ( factor + 500 ) / 1000;
			PANEL_TIMING_printData( "  Recal dclk-0=%d", dclk );
			if(MAX_DCLK_WITH_SSC(dclk) > PanelMaxDCLK)
			{
				PANEL_TIMING_printData( "  Recal max dclk SSC fail=%d", MAX_DCLK_WITH_SSC(dclk) );
				SrcFlags |= bUnsupportMode;
				return FALSE;
			}
			mStar_SetCaptureWindow();
			mStar_SetupPath();
			//mStar_SetScalingFactor();
			height += DecVScaleValue;
			if(CURRENT_SOURCE_IS_INTERLACE_MODE())
				height /= 2;
		}
		#if ENABLE_CHECK_PANEL_VTOTAL
		if ( u16OutVtt > PanelMaxVTotal
	        #if ENABLE_CHECK_PANEL_60HZ_MAX_VTOTAL
		        || u16OutVtt > PanelMax60HZVTotal
	        #endif
		   )
		{
			WORD xdata u16DecVScaleValue2 = 0;
			height -= DecVScaleValue;
			#if ENABLE_CHECK_PANEL_60HZ_MAX_VTOTAL
			if (abs(GetVfreq() - 60) < 2)
				u16PanelMaxVotal = PanelMax60HZVTotal;
			else
			#endif
				u16PanelMaxVotal = PanelMaxVTotal;
			if(CURRENT_SOURCE_IS_INTERLACE_MODE())
				height *= 2;
			u16DecVScaleValue2 = ( ( DWORD ) SrcVTotal * PanelHeight + ( u16PanelMaxVotal - 1 ) ) / u16PanelMaxVotal;
			u16DecVScaleValue2 = ( u16DecVScaleValue2 + 1 ) & ~BIT0;
			#if DEBUG_PRINT_ENABLE
			printData( "u16DecVScaleValue2=%d", u16DecVScaleValue2 );
			#endif
			if((height + DecVScaleValue) < u16DecVScaleValue2)
				DecVScaleValue = u16DecVScaleValue2;
			else
				DecVScaleValue = height + DecVScaleValue;
			if(SrcVTotal >= (DecVScaleValue + 8) )
			{
				DecVScaleValue = DecVScaleValue - height;
				Set_DecVScaleFlag();//20150115 alpha
			}
			else
			{
				Clr_DecVScaleFlag();//20150115 alpha
				SrcFlags |= bUnsupportMode;
				return FALSE;
			}
			height += DecVScaleValue;
			u16OutVtt = ( ( DWORD ) SrcVTotal * PanelHeight + ( height - 1 ) ) / height;
			if( u16OutVtt > u16PanelMaxVotal)
			{
				SrcFlags |= bUnsupportMode;
				return FALSE;
			}
			mStar_SetCaptureWindow();
			mStar_SetupPath();
			if(CURRENT_SOURCE_IS_INTERLACE_MODE())
				height /= 2;
		}
		#endif
		if(MIN_DCLK_WITH_SSC(dclk) < PanelMinDCLK)
		{
			dstHTotal = PanelHTotal + HTOTAL_OUTPUT_TOLERANCE;
			factor = (( float )dstHTotal * ( PanelHeight - 1 ) * MST_HPeriod_UINT ) / (( DWORD )hPeriod * ( height - 1 ) ); // output dclk
			dclk = ( factor + 500 ) / 1000;
			PANEL_TIMING_printData( "  Recal dclk-1=%d", dclk );
			if(MIN_DCLK_WITH_SSC(dclk) < PanelMinDCLK)
			{
				PANEL_TIMING_printData( "  Recal min dclk SSC fail=%d", MIN_DCLK_WITH_SSC(dclk) );
				SrcFlags |= bUnsupportMode;
				return FALSE;
			}
		}
		#if OUTPUT_VTOTAL_PROTECT
		{
			WORD outputVtotal = OUTPUT_VTOTAL;
			PANEL_TIMING_printData( "  OUTPUT_VTOTAL=%d", OUTPUT_VTOTAL );
			PANEL_TIMING_printData( "  PanelMaxVTotal=%d", PanelMaxVTotal );
			PANEL_TIMING_printData( "  PanelMinVTotal=%d", PanelMinVTotal );
			if(outputVtotal > PanelMaxVTotal || outputVtotal < PanelMinVTotal)
			{
				SrcFlags |= bUnsupportMode;
				return FALSE;
			}
		}
		#endif
		PANEL_TIMING_printData( "  dclk SSC=%d", MAX_DCLK_WITH_SSC(dclk) );
		#else
		if(MAX_DCLK_WITH_SSC(dclk) > PanelMaxDCLK)// && !OverScanFlag)
		{
			WORD wHeight;
			if(CURRENT_SOURCE_IS_INTERLACE_MODE())
				height *= 2;
			if(SrcVTotal - height > VTOTAL_OUTPUT_TOLERANCE)
			{
				DecVScaleValue = SrcVTotal - height - VTOTAL_OUTPUT_TOLERANCE;
				if(DecVScaleValue % 2)
					DecVScaleValue += 1;
				//modified some timing display unsymmetrically
				DecVScaleValue = ((VSTART_OFFSET >= SC0_READ_AUTO_START_V()) ? (SC0_READ_AUTO_START_V() * 2) : (DecVScaleValue));
				Set_DecVScaleFlag();	//120424 Modify
			}
			else
			{
				SrcFlags |= bUnsupportMode;
				return FALSE;
			}
			wHeight = height + DecVScaleValue;
			if(CURRENT_SOURCE_IS_INTERLACE_MODE())
				wHeight /= 2;
			factor = ((float)dstHTotal * (PanelHeight - 1) * MST_HPeriod_UINT) / ((DWORD)hPeriod * (wHeight - 1)); // output dclk
			dclk = (factor + 500) / 1000;
			if(MAX_DCLK_WITH_SSC(dclk) > PanelMaxDCLK)
			{
				SrcFlags |= bUnsupportMode;
				return FALSE;
			}
			mStar_SetCaptureWindow();
			mStar_SetupPath();
			//mStar_SetScalingFactor();
			height += DecVScaleValue;
			if(CURRENT_SOURCE_IS_INTERLACE_MODE())
				height /= 2;
		}
		if(MIN_DCLK_WITH_SSC(dclk) < PanelMinDCLK)
		{
			dstHTotal = PanelHTotal;
			factor = (( float )dstHTotal * ( PanelHeight - 1 ) * MST_HPeriod_UINT ) / (( DWORD )hPeriod * ( height - 1 ) ); // output dclk
			dclk = ( factor + 500 ) / 1000;
		}
		#endif
	}
	#if 1
	SC0_SAMPLE_CLOCK_INVERT(sclk);
	#else
	if (sclk > 165)
		msWriteByteMask(SC0_F3, BIT0, BIT0);
	else
		msWriteByteMask(SC0_F3, 0, BIT0);
	#endif
	SC0_SET_OUTPUT_VTOTAL(0xFFF);//msWrite2ByteMask(SC0_1E, 0xFFF, SC_MASK_V); // output vtotal //Jison 110527 lost to add.
	factor = (float)XTAL_CLOCK_KHZ * 16UL / hPeriod * dstHTotal * (PANEL_HEIGHT - 1) / (height - 1); // output dot clock in KHz
	//mStar_SetDClkPLL(factor);
	//mStar_ResetDClkPLL(); // reset output PLL to prevent PLL works abnormally
//****************Setup line buffer clock*************************************
	#if 0//DEBUG_EN
	PRINT_DATA(" current idclk=%d", (((DWORD)USER_PREF_H_TOTAL * MST_HPeriod_UINT) / ((DWORD)u16HPeriod * 1000)));
	#endif
	if (SyncLossState() || UnsupportedModeFlag)
	{
		mStar_SetDClkPLL((DWORD)PanelHTotal * PanelVTotal * GetVfreq() / 1000);
		msSetFrameSyncMode(FLM_FB_FPLL_NOLOCK);
	}
	else // valid timing
	{
		if(g_SetupPathInfo.bFBMode)
		{
			mStar_SetDClkPLL((DWORD)PanelHTotal * PanelVTotal * GetVfreq() / 1000);
			msSetFrameSyncMode(FLM_FB_FPLL);
			msWriteByteMask(REG_3818, BIT3, BIT3); //FramePLL Enable
		}
		else
		{
			msWriteByteMask(REG_3818, 0, BIT3);
			msSetFrameSyncMode(FLM_FBL);
			mStar_SetDClkPLL(factor);
		}
	}
	#if ENABLE_FACTORY_SSCADJ // 2011-09-16 19:46 CC
	mStar_SetPanelSSC(FactorySetting.SSCModulation, FactorySetting.SSCPercentage);
	#else
	mStar_SetPanelSSC(PANEL_SSC_MODULATION_DEF, PANEL_SSC_PERCENTAGE_DEF);
	#endif
	mStar_CheckFastClock(hPeriod, hPeriod);
	Delay1ms(100); //Jison 110707 delay before lock input for CHIP_TSUMV avoid update wrong SC0_24/SC0_25 htotal value //110916 Rick modified for A026
	SC0_OUTPUT_LOCK_MODE(TRUE);//msWriteByteMask(SC0_02, 0 , NIS_B);// enable lock input mode
	if(g_SetupPathInfo.bFBMode)
		WaitOutputFpllStable();
	FPLLTimeoutCounter = 0;
	return TRUE;
}


#if 0	//120420 Modify
void appmStar_InitPanelPara( void )
{
	// display timing OP2-1
	// output DE size // 0x10~0x1D
	msWrite2Byte(SC0_10, 0);// Vert. DE start
	msWrite2Byte(SC0_14, ( PANEL_HEIGHT - 1 ));// Vert. DE end
	msWrite2Byte(SC0_12, ( PanelHStart / PANEL_H_DIV )); // Hor. DE start
	msWrite2Byte(SC0_16, ( ( PanelHStart / PANEL_H_DIV ) + (PANEL_WIDTH / PANEL_H_DIV) - 1 )); // Hor. DE end
	// Output Sync Timing //0x1E~0x26
	#if DOWN_COUNTER_V_SYNC //Vsync using down counter
	msWrite2Byte(SC0_1E, ( PanelVTotal - 1 ) | _BIT15); // output vtotal
	msWriteByte(SC0_20, 0x02);// vsync start
	msWriteByte(SC0_22, 0x01);//vsync end
	#else //Vsync using v counter
	msWrite2Byte(SC0_1E, ( PanelVTotal - 1 ));// output vtotal
	msWrite2Byte(SC0_20, ( PanelVTotal - PanelVStart ));// vsync start
	msWrite2Byte(SC0_22, ( PanelVTotal - PanelVSyncBackPorch ));//vsync end
	#endif
	msWrite2Byte(SC0_24, ( PanelHTotal / PANEL_H_DIV - 1 )); // output htotal
	msWriteByte(SC0_26, ( ( PanelHSyncWidth / PANEL_H_DIV ) - 2 )); //-1}, //
	// Scaling Image window size
	msWrite2Byte(SC0_18, ( PanelHStart / PANEL_H_DIV ));
	msWrite2Byte(SC0_1C, ( ( PanelHStart / PANEL_H_DIV ) + (PANEL_WIDTH / PANEL_H_DIV) - 1 ));
	msWrite2Byte(SC0_1A, ( PANEL_HEIGHT - 1 ));
	msWriteByte(SC0_27, BIT6 | BIT5 | BIT1); // enable auto-htotal
	msWriteByte(SC0_49, 0xAF);
	#if (ModelName==AOC_G15)
	msWriteByte(REG_3680, (PanelSwapMLSB & BIT6) | (BIT2 & LVDS_TIMode) | BIT3);
	#else
	msWriteByte(REG_3680, (PanelSwapMLSB & BIT6) | (BIT5) | (BIT2 & LVDS_TIMode) | BIT3);
	#endif
	msWriteByte(REG_368A, 0x3F);
	msWriteByte(REG_3693, (PanelSwapOddRB & BIT3) | (PanelSwapEvenRB & BIT5) | (PanelSwapOddML & BIT4) | (PanelSwapEvenML & BIT6));
	msWriteByte(REG_3681, (PanelDClkDelay << 4));
	msWriteByte(REG_3694, (PanelInvDClk & BIT4) | (PanelInvDE & BIT2) | (PanelInvVSync & BIT3)
	            | (PanelDualPort & BIT1) | (PanelSwapPort & BIT0));
	msWriteByte(REG_3689, PanelDualPort & BIT4);
	msWriteByte(REG_3695, (PanelInvHSync & BIT4));
	msWriteByte(REG_3696, LVDS_TI_BitModeSel);
	msWriteByte(REG_3692, 0x00);
	msWriteByte(REG_36EE, BIT0 | (BIT1 & PanelDualPort));
	msWriteByteMask(REG_3694, (PanelOutputControl2 & BIT1) >> 1, BIT0);
	msWriteByteMask(REG_3694, (PanelOutputControl2 & BIT0) << 1, BIT1);
	msWriteByteMask(REG_3689, (PanelOutputControl2 & BIT0) << 4, BIT4);
	msWriteByteMask(REG_36EE, (PanelOutputControl2 & BIT0) << 1, BIT1);
	msWriteByteMask(REG_3680, (PanelOutputControl1 & BIT5) << 1, BIT6);
	msWriteByteMask(REG_3680, (PanelOutputControl1 & BIT4) >> 2, BIT2);
	msWriteByteMask(REG_3693, (PanelOutputControl1 & BIT3) << 1, BIT4);
	msWriteByteMask(REG_3693, (PanelOutputControl1 & BIT2) << 4, BIT6);
	msWriteByteMask(REG_3693, (PanelOutputControl1 & BIT1) << 2, BIT3);
	msWriteByteMask(REG_3693, (PanelOutputControl1 & BIT0) << 5, BIT5);
}
#endif


