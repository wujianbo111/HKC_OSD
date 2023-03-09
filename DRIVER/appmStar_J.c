
#include "global.h"

WORD mSTar_GetInputHTotal(void)
{
	WORD u16HTotal;
	msWriteByteMask(SC0_ED, BIT6, BIT6);
	u16HTotal = (msRead2Byte(SC0_E4) & 0x1FFF) + 1; //get input HTotal
	msWriteByteMask(SC0_ED, 0, BIT6);
	return u16HTotal;
}

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
	}
	// calculate input timing dot clock for comparing with output dot clock
	if(CURRENT_INPUT_IS_VGA())
		sclk = (( DWORD )UserPrefHTotal * MST_HPeriod_UINT ) / (( DWORD )hPeriod * 1000 );
	else
	{
		dclk = mSTar_GetInputHTotal();
		sclk = (( DWORD )dclk * MST_HPeriod_UINT ) / (( DWORD )hPeriod * 1000 );
	}
	#if 0//DEBUG_PRINT_ENABLE
	printData( "  sclk=%d", sclk );
	#endif
	height = SC0_READ_IMAGE_HEIGHT();//msRead2Byte(SC0_09)&SC_MASK_V;
	#if ENABLE_CHECK_PANEL_VTOTAL	//Calc uput Vtt need before Interlace mode u16Hight/2
	// calc output vtt
	u16OutVtt = ( ( DWORD ) SrcVTotal * PanelHeight + ( height - 1 ) ) / height;
	#endif
	if( CURRENT_SOURCE_IS_INTERLACE_MODE() )
	{
		height /= 2;
	}
	dstHTotal = PanelMinHTotal + 10;
	//***************************************************************
	if( sclk )
	{
		// in expansion mode, chip will assume output clock is faster than input clock,
		// if input clock is faster than output clock, must make output clock faster than input clock
		factor = (( float )dstHTotal * ( PanelHeight - 1 ) * MST_HPeriod_UINT ) / (( DWORD )hPeriod * ( height - 1 ) ); // output dclk
		dclk = ( factor + 500 ) / 1000;
		#if DEBUG_PRINT_ENABLE
		printData( "  dclk=%d", dclk );
		printData( "  PanelMaxDCLK=%d", PanelMaxDCLK );
		#endif
		if(dclk > PanelMaxDCLK)// && !OverScanFlag)
		{
			WORD wHeight;
			if(CURRENT_SOURCE_IS_INTERLACE_MODE())
				height *= 2;
			if(SrcVTotal - height > 8)
			{
				DecVScaleValue = SrcVTotal - height - 8;
				if(DecVScaleValue % 2)
					DecVScaleValue += 1;
				//modified some timing display unsymmetrically
				DecVScaleValue = ((VSTART_OFFSET >= SC0_READ_AUTO_START_V()) ? (SC0_READ_AUTO_START_V() * 2) : (DecVScaleValue));
				Set_DecVScaleFlag();	//20150115 Modify
			}
			else
			{
				Clr_DecVScaleFlag();	//20150115 Modify
				SrcFlags |= bUnsupportMode;
				return FALSE;
			}
			wHeight = height + DecVScaleValue;
			if(CURRENT_SOURCE_IS_INTERLACE_MODE())
				wHeight /= 2;
			factor = ((float)dstHTotal * (PanelHeight - 1) * MST_HPeriod_UINT) / ((DWORD)hPeriod * (wHeight - 1)); // output dclk
			dclk = (factor + 500) / 1000;
			if(dclk > PanelMaxDCLK)
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
		else
		{
			DecVScaleValue = 0;
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
				Set_DecVScaleFlag();	//20150115 Modify
			}
			else
			{
				Clr_DecVScaleFlag();	//20150115 Modify
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
		drvmStar_SetupFreeRunMode();
	}
	else // valid timing
	{
		msWriteByteMask(REG_3818, 0, BIT3);
		msSetFrameSyncMode(FLM_FBL);
		mStar_SetDClkPLL(factor);
	}
	mStar_CheckFastClock(hPeriod, hPeriod);
	mStar_SetPanelSSC( 0, 0 );
	Delay1ms(2);
	SC0_OUTPUT_LOCK_MODE(TRUE);//msWriteByteMask(SC0_02, 0 , NIS_B);// enable lock input mode
	Delay1ms(100);
	#if ENABLE_FACTORY_SSCADJ // 2011-09-16 19:46 CC
	mStar_SetPanelSSC(FactorySetting.SSCModulation, FactorySetting.SSCPercentage);
	#else
	mStar_SetPanelSSC(PANEL_SSC_MODULATION_DEF, PANEL_SSC_PERCENTAGE_DEF);
	#endif
	return TRUE;
}
