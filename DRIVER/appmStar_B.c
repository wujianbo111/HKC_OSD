
#include "global.h"
#include "ms_reg.h"
Bool appmStar_SetPanelTiming( void )
{
	DWORD factor;
	DWORD dclk;
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
		sclk = (( DWORD )StandardModeHTotal * MST_HPeriod_UINT ) / (( DWORD )hPeriod * 1000 );
	#if 0//DEBUG_PRINTDATA
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
		#if DEBUG_PRINTDATA
		//printData( "  dclk=%d", dclk );
		// printData( "  PanelMaxDCLK=%d", PanelMaxDCLK );
		#endif
		#if ENABLE_FACTORY_SSCADJ
		if ((dclk + (((dclk * FactorySetting.SSCPercentage / 10) + 50) / 100)) > PanelMaxDCLK)
		#else
		if ((dclk + (((dclk * PANEL_PERCENTAGE / 10) + 50) / 100)) > PanelMaxDCLK)
		#endif
		{
			WORD wHeight;
			if(CURRENT_SOURCE_IS_INTERLACE_MODE())
				height *= 2;
			dclk = (PanelMaxDCLK - (((PanelMaxDCLK * FactorySetting.SSCPercentage / 10) + 50) / 100)) * 1000ul; // 2012-04-27
			DecVScaleValue  = ((float)MST_HPeriod_UINT / hPeriod  * dstHTotal * (PANEL_HEIGHT - 1) / dclk) + 1; // output dot clock in KHz
			DecVScaleValue = (DecVScaleValue + 1) & ~BIT0;
			if(SrcVTotal >= (DecVScaleValue + 12) )
			{
				DecVScaleValue = DecVScaleValue - height;
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
			#if DEBUG_PRINTDATA
			printData( "  dclk=%d", dclk );
			printData( "  PanelMaxDCLK=%d", PanelMaxDCLK );
			#endif
			#if ENABLE_FACTORY_SSCADJ
			if ((dclk + (((dclk * FactorySetting.SSCPercentage / 10) + 50) / 100)) > PanelMaxDCLK)
			#else
			if ((dclk + (((dclk * PANEL_PERCENTAGE / 10) + 50) / 100)) > PanelMaxDCLK)
			#endif
			{
				Clr_DecVScaleFlag(); //120424 Modify
				SrcFlags |= bUnsupportMode;
				return FALSE;
			}
			mStar_SetCaptureWindow();
			mStar_SetScalingFactor();
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
			mStar_SetScalingFactor();
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
	mStar_SetDClkPLL(factor);
	//if (SRC_FLAGS&INTERLACE_MODE_BIT) //Jison: Workaround for floating LPLL issue.
	//      Delay1ms(150);
	Delay1ms(100); //Jison 110707 delay before lock input for CHIP_TSUMV avoid update wrong SC0_24/SC0_25 htotal value
	SC0_OUTPUT_LOCK_MODE(TRUE);//msWriteByteMask(SC0_02, 0 , NIS_B);// enable lock input mode
	//FixShortLine(u32Factor);
	//mStar_ResetDClkPLL(); // reset output PLL to prevent PLL works abnormally
//****************Setup line buffer clock*************************************
	#if 0//DEBUG_EN
	PRINT_DATA(" current idclk=%d", (((DWORD)USER_PREF_H_TOTAL * MST_HPeriod_UINT) / ((DWORD)u16HPeriod * 1000)));
	#endif
	mStar_CheckFastClock(sclk, dclk);
	#if ENABLE_FACTORY_SSCADJ // 2011-09-16 19:46 CC
	mStar_SetPanelSSC(FactorySetting.SSCModulation, FactorySetting.SSCPercentage);
	#else
	mStar_SetPanelSSC(PANEL_SSC_MODULATION_DEF, PANEL_SSC_PERCENTAGE_DEF);
	#endif
	return TRUE;
}
#if 0	//120112 Modify
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
	//{SC0_02, 0x80},
	msWrite2Byte(SC0_24, ( PanelHTotal / PANEL_H_DIV - 1 )); // output htotal
	msWriteByte(SC0_26, ( ( PanelHSyncWidth / PANEL_H_DIV ) - 2 )); //-1}, //
	// Scaling Image window size
	msWrite2Byte(SC0_18, ( PanelHStart / PANEL_H_DIV ));
	msWrite2Byte(SC0_1C, ( ( PanelHStart / PANEL_H_DIV ) + (PANEL_WIDTH / PANEL_H_DIV) - 1 ));
	msWrite2Byte(SC0_1A, ( PANEL_HEIGHT - 1 ));
	msWriteByte(SC0_27, ( BIT6 | BIT5 | BIT1 ));// enable auto-htotal
	//{SC0_28, BIT5}, // setup clock mode
	msWriteByte(SC0_49, 0xAF);
	msWriteByte(REG_3042, PanelOutputControl1);
	msWriteByte(REG_30F2, (PanelDClkDelay << 4) | (BIT3 & PanelInvDClk) | (BIT2 & PanelInvDE) |
	            (BIT1 & PanelInvVSync) | (BIT0 & PanelInvHSync)); // output signal polarity control
	msWriteByte(SC0_43, PanelOutputControl2);
}
#endif

