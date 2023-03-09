
#include "global.h"
#include "ms_reg.h"

#define APPMSTAR_DBG     1

#if APPMSTAR_DBG && ENABLE_DEBUG
#define APPMSTAR_printMsg(str)        printMsg(str)
#define APPMSTAR_printData(str, x)     printData(str, x)
#else
#define APPMSTAR_printMsg(str)
#define APPMSTAR_printData(str, x)
#endif
#if PanelType == PanelAUOM240HW01V8 || PanelType == PanelAUOM240HW01V80A || PanelType == PanelAUOM240HW01V80B
#define HTOTAL_OUTPUT_TOLERANCE     120
#endif

Bool appmStar_SetPanelTiming(void)
{
	DWORD u32Sclk;
	WORD u16Height;
	WORD u16dstHTotal;
	WORD u16hPeriod;
	DWORD u32ODCLK_KHZ;
	WORD u16HDE_OP21;
	WORD u16VDE_OP21;
	#if DECREASE_V_SCALING
	DWORD factor;
	#endif
	#if ENABLE_CHECK_PANEL_VTOTAL
	WORD xdata u16OutVtt = 0;
	WORD xdata u16PanelMaxVotal = 0;
	#endif
	// for getting more accurate output htotal
	if( SrcHPeriod > 511 ) // avoid overflow
		u16hPeriod = SrcHPeriod * 16;
	else
	{
		#if UseINT && Enable_Expansion//Jison110331 for wideMode switch set SC0_E5[7] will cause mode change
		mStar_EnableModeChangeINT(FALSE);
		#endif
		u32Sclk = GetVSyncTime() * 8;
		SC0_HPEROID_DETECT_MODE(TRUE);//msWriteByte( SC0_E5, BIT7 ); // enable 16 line line to calculate hsync period.
		Delay1ms( u32Sclk );
		u16hPeriod = SC0_READ_HPEROID();//msRead2Byte( SC0_E4 ) & 0x1FFF;
		if( abs( u16hPeriod / 16 - SrcHPeriod ) > 5 )
			u16hPeriod = SrcHPeriod * 16;
		SC0_HPEROID_DETECT_MODE(FALSE);//msWriteByte( SC0_E5, 0 );
		Delay1ms( u32Sclk );
		#if UseINT && Enable_Expansion
		//mStar_EnableModeChangeINT(u16Height);//restore
		mStar_EnableModeChangeINT(TRUE);//restore
		#endif
	}
	u16Height = g_SetupPathInfo.wImgSizeInV; // case 1,2 only
	#if ENABLE_CHECK_PANEL_VTOTAL	//Calc uput Vtt need before Interlace mode u16Hight/2
	// calc output vtt
	if(CURRENT_SOURCE_IS_INTERLACE_MODE())//(SRC_FLAGS & INTERLACE_MODE_BIT)
		u16OutVtt = ( ( DWORD ) SrcVTotal * PanelHeight + ( u16Height * 2 - 1 ) ) / (u16Height * 2);
	else
		u16OutVtt = ( ( DWORD ) SrcVTotal * PanelHeight + ( u16Height - 1 ) ) / u16Height;
	#endif
	if( g_SetupPathInfo.bFBMode )
		u16dstHTotal = PanelHTotal;
	else
		u16dstHTotal = PanelMinHTotal + 10;
	APPMSTAR_printData("u16dstHTotal:%d", u16dstHTotal);
// 121101 coding modified
	#if ENABLE_OVER_SCAN
	if((g_SetupPathInfo.ucSCFmtIn == SC_FMT_IN_NORMAL) && OverScanSetting.Enable)
	#else
	if( !EXPANSION_MODE_IS_FULL() && (g_SetupPathInfo.ucSCFmtIn == SC_FMT_IN_NORMAL) && !INPUT_IS_WILD_TIMING() )//( UserprefExpansionMode!=Expansion_Full && (g_SetupPathInfo.ucSCFmtIn == SC_FMT_IN_NORMAL) )	//120525 Modify
	#endif
	{
		u16HDE_OP21 = PANEL_WIDTH;
		u16VDE_OP21 = PANEL_HEIGHT;
	}
	else if( IS_FMT_IN_SBS() )
	{
		u16HDE_OP21 = g_SetupPathInfo.wMRWSizeInH * 2;
		u16VDE_OP21 = g_SetupPathInfo.wMRWSizeInV / 2;
	}
	else
	{
		u16HDE_OP21 = g_SetupPathInfo.wMRWSizeInH;
		u16VDE_OP21 = g_SetupPathInfo.wMRWSizeInV;
	}
	// input/output frame div for frame sync
	//mStar_SetFrameDivider( (DWORD)(((XTAL_CLOCK_KHZ * 16UL * 1000 + u16hPeriod/2)/u16hPeriod +SrcVTotal/2)/(SrcVTotal)) * ((SrcFlags&bInterlaceMode)?2:1) ); // param: input Vfreq
	//mStar_SetFrameDivider( (DWORD)(((XTAL_CLOCK_KHZ * 16UL * 10000 + hPeriod/2)/hPeriod +SrcVTotal/2)/(SrcVTotal)) * ((SrcFlags&bInterlaceMode)?2:1) ); // param: input Vfreq*10
	// ivs setting for nvidia VBI and PSV_4M TB
	// mStar_SetIVS();
	if(CURRENT_INPUT_IS_VGA())
		u32Sclk = (( DWORD ) UserPrefHTotal * MST_HPeriod_UINT ) / (( DWORD )u16hPeriod );
	else // 121101 coding modified
	{
		//u32Sclk = (( DWORD ) StandardModeHTotal * MST_HPeriod_UINT ) / (( DWORD )u16hPeriod );
//APPMSTAR_printData("u32Sclk_0:%d", u32Sclk);
		#if 0//ENABLE_DUAL_LINK		//130328 Modify
		if(GetVfreq() > 90)
			u32Sclk = GetStandardModeHTotal(); //get input HTotal
		else
		#endif
			u32Sclk = mSTar_GetInputHTotal(); //get input HTotal
		u32Sclk = ((DWORD)u32Sclk * MST_HPeriod_UINT) / ((DWORD)u16hPeriod);
	}
	APPMSTAR_printData("u32Sclk_1:%d", u32Sclk);
	#if DECREASE_V_SCALING          //111013 Rick add for display unsupport mode - A045
	#if FRAME_BFF_SEL == FRAME_BFFLESS
	#if ENABLE_FREESYNC
	if(IS_DP_FREESYNC())
	{
		factor = (float)DPRxGetPixelClk() * 10 * PanelHTotal / DPRxGetHTotal() * (PanelHeight - 1)  / ((u16Height - 1) * PANEL_H_DIV); // output dot clock in KHz
	}
	else
	#endif
		factor = ((float)XTAL_CLOCK_KHZ * 16UL / u16hPeriod * u16dstHTotal * (PANEL_HEIGHT - 1) / (u16Height - 1)); // output dot clock in KHz
	#else
	#if ENABLE_FREESYNC
	if(IS_DP_FREESYNC())
	{
		factor = (float)DPRxGetPixelClk() * 10 * PanelHTotal / DPRxGetHTotal() * (PanelHeight - 1)  / ((u16Height - 1) * PANEL_H_DIV); // output dot clock in KHz
	}
	else
	#endif
		factor = (( float )GetVfreq() * GetVtotal() * u16dstHTotal + 500) / 1000; // output dot clock in KHz
	#endif
	u32ODCLK_KHZ = (factor + 500) / 1000;
	#if DEBUG_PRINTDATA
	printData("0000 u32ODCLK_MHZ:%d", u32ODCLK_KHZ);
	#endif
	// APPMSTAR_printData("u32ODCLK_MHZ__00:%d", (u32ODCLK_KHZ + (u32ODCLK_KHZ * FactorySetting.SSCPercentage/10) / 100 + 1));
//printData("OOR oclk(%d)>PANEL_MAX_DCLK",u32ODCLK_KHZ/1000);
	#if FRAME_BFF_SEL==FRAME_BFFLESS  // Need check .....648x480@72_185
	//if (u32ODCLK_KHZ>PanelMaxDCLK) // if ouput clock is out of panel spec, then enable unsupported flag
	#if ENABLE_FACTORY_SSCADJ // 2011-09-16 19:46 CC
	// 120321 coding, modified for ssc percentage, original 0~3 means 0~3%, modified 0~30 means 0~30%
	//if ((u32ODCLK_KHZ + (u32ODCLK_KHZ * FactorySetting.SSCPercentage) / 100 + 1)>PanelMaxDCLK-2)
	#if 0//PanelType==PanelHSMB238_1DAN01
	if ((u32ODCLK_KHZ + (u32ODCLK_KHZ * FactorySetting.SSCPercentage / 10) / 100 + 1) > PanelMaxDCLK - 5)
	#else
	if ((u32ODCLK_KHZ + (u32ODCLK_KHZ * FactorySetting.SSCPercentage / 10) / 100 + 1) > (PanelMaxDCLK - 2))
	#endif
	#else
	// 120321 coding, modified for ssc percentage, original 0~3 means 0~3%, modified 0~30 means 0~30%
	//if ((u32ODCLK_KHZ + (u32ODCLK_KHZ * PANEL_SSC_PERCENTAGE_DEF) / 100 + 1)>PanelMaxDCLK-2)
	if ((u32ODCLK_KHZ + (u32ODCLK_KHZ * PANEL_SSC_PERCENTAGE_DEF / 10) / 100 + 1) > (PanelMaxDCLK - 2))
	#endif
	{
		WORD wHeight;
		if(CURRENT_SOURCE_IS_INTERLACE_MODE())
			u16Height *= 2;
		if(SrcVTotal - u16Height > 10)      //111019 Rick modified  - A066
		{
			DecVScaleValue = SrcVTotal - u16Height - 10;
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
			#if DEBUG_MSG
			printMsg("Unsupport  7");
			#endif
			return FALSE;
		}
		wHeight = u16Height + DecVScaleValue;
		if(CURRENT_SOURCE_IS_INTERLACE_MODE())
			wHeight /= 2;
		factor = ((float)u16dstHTotal * (PanelHeight - 1) * MST_HPeriod_UINT) / ((DWORD)u16hPeriod * (wHeight - 1)); // output dclk
		u32ODCLK_KHZ = (factor + 500) / 1000;
		APPMSTAR_printData("2222  u32ODCLK_KHZ:%d", u32ODCLK_KHZ);
		if(u32ODCLK_KHZ > PanelMaxDCLK)
		{
			SrcFlags |= bUnsupportMode;
			#if DEBUG_MSG
			printMsg("Unsupport  6");
			#endif
			return FALSE;
		}
		mStar_SetCaptureWindow();
		mStar_SetupPath();
		//mStar_SetScalingFactor();
		u16Height += DecVScaleValue;
		if(CURRENT_SOURCE_IS_INTERLACE_MODE())
			u16Height /= 2;
	}
	else
	{
		DecVScaleValue = 0;
	}
	#if ENABLE_CHECK_PANEL_VTOTAL
	APPMSTAR_printData("u16OutVtt:%d", u16OutVtt);
	if ( u16OutVtt > PanelMaxVTotal
        #if ENABLE_CHECK_PANEL_60HZ_MAX_VTOTAL
	        || u16OutVtt > PanelMax60HZVTotal
        #endif
	   )
	{
		WORD xdata u16DecVScaleValue2 = 0;
		u16Height -= DecVScaleValue;
		#if ENABLE_CHECK_PANEL_60HZ_MAX_VTOTAL
		if (abs(GetVfreq() - 60) < 2)
			u16PanelMaxVotal = PanelMax60HZVTotal;
		else
		#endif
			u16PanelMaxVotal = PanelMaxVTotal;
		if(CURRENT_SOURCE_IS_INTERLACE_MODE())
			u16Height *= 2;
		u16DecVScaleValue2 = ( ( DWORD ) SrcVTotal * PanelHeight + ( u16PanelMaxVotal - 1 ) ) / u16PanelMaxVotal;
		u16DecVScaleValue2 = ( u16DecVScaleValue2 + 1 ) & ~BIT0;
		#if DEBUG_PRINT_ENABLE
		printData( "u16DecVScaleValue2=%d", u16DecVScaleValue2 );
		#endif
		if((u16Height + DecVScaleValue) < u16DecVScaleValue2)
			DecVScaleValue = u16DecVScaleValue2;
		else
			DecVScaleValue = u16Height + DecVScaleValue;
		if(SrcVTotal >= (DecVScaleValue + 8) )
		{
			DecVScaleValue = DecVScaleValue - u16Height;
			Set_DecVScaleFlag();	//20150115 Modify
		}
		else
		{
			Clr_DecVScaleFlag();	//20150115 Modify
			#if DEBUG_MSG
			printMsg("Unsupport  5");
			#endif
			SrcFlags |= bUnsupportMode;
			return FALSE;
		}
		u16Height += DecVScaleValue;
		u16OutVtt = ( ( DWORD ) SrcVTotal * PanelHeight + ( u16Height - 1 ) ) / u16Height;
		if( u16OutVtt > u16PanelMaxVotal)
		{
			SrcFlags |= bUnsupportMode;
			#if DEBUG_MSG
			printMsg("Unsupport  4");
			#endif
			return FALSE;
		}
		mStar_SetCaptureWindow();
		mStar_SetupPath();
		if(CURRENT_SOURCE_IS_INTERLACE_MODE())
			u16Height /= 2;
	}
	#endif
	#endif
	#if 0//PanelType == PanelAUOM240HW01V8 || PanelType == PanelAUOM240HW01V80A || PanelType == PanelAUOM240HW01V80B
	if(u32ODCLK_KHZ < PanelMinDCLK)
	{
		u16dstHTotal = PanelHTotal + HTOTAL_OUTPUT_TOLERANCE;
		#if FRAME_BFF_SEL == FRAME_BFFLESS
		factor = ((float)XTAL_CLOCK_KHZ * 16UL / u16hPeriod * u16dstHTotal * (PANEL_HEIGHT - 1) / (u16Height - 1)); // output dot clock in KHz
		#else
		factor = (( float )GetVfreq() * GetVtotal() * u16dstHTotal + 500) / 1000; // output dot clock in KHz
		#endif
		u32ODCLK_KHZ = (factor + 500) / 1000;
	}
	#endif
	u32ODCLK_KHZ = u32ODCLK_KHZ * 1000;
	#else
	#if FRAME_BFF_SEL == FRAME_BFFLESS
	#if ENABLE_FREESYNC
	if(IS_DP_FREESYNC())
	{
		u32ODCLK_KHZ = (float)DPRxGetPixelClk() * 10 * PanelHTotal / DPRxGetHTotal() * (PanelHeight - 1)  / ((u16Height - 1) * PANEL_H_DIV); // output dot clock in KHz
		APPMSTAR_printData("u32ODCLK_KHZ:%d", u32ODCLK_KHZ);
	}
	else
	#endif
		u32ODCLK_KHZ = (float)XTAL_CLOCK_KHZ * 16UL / u16hPeriod * u16dstHTotal * (PANEL_HEIGHT - 1) / (u16Height - 1); // output dot clock in KHz
	#else
	#if ENABLE_FREESYNC
	if(IS_DP_FREESYNC())
	{
		u32ODCLK_KHZ = (float)DPRxGetPixelClk() * 10 * PanelHTotal / DPRxGetHTotal() * (PanelHeight - 1)  / ((u16Height - 1) * PANEL_H_DIV); // output dot clock in KHz
	}
	else
	#endif
		u32ODCLK_KHZ = (( float )GetVfreq() * GetVtotal() * u16dstHTotal + 500) / 1000; // output dot clock in KHz
	#endif
//printData("OOR oclk(%d)>PANEL_MAX_DCLK",u32ODCLK_KHZ/1000);
	#if FRAME_BFF_SEL==FRAME_BFFLESS  // Need check .....648x480@72_185
	if (u32ODCLK_KHZ / 1000 > PanelMaxDCLK) // if ouput clock is out of panel spec, then enable unsupported flag
	{
		SrcFlags |= bUnsupportMode;
		//PRINT_DATA("OOR oclk(%d)>PANEL_MAX_DCLK",u32ODCLK_KHZ/1000);
		#if DEBUG_MSG
		printMsg("Unsupport  3");
		#endif
		return FALSE;
	}
	#endif
	#endif
	// input/output frame div for frame sync
	//mStar_SetFrameDivider( (DWORD)(((XTAL_CLOCK_KHZ * 16UL * 1000 + u16hPeriod/2)/u16hPeriod +msRead2Byte(SC0_E2)/2)/(msRead2Byte(SC0_E2))) * ((SrcFlags&bInterlaceMode)?2:1) ); // param: input Vfreq
	mStar_SetFrameDivider( (DWORD)(((XTAL_CLOCK_KHZ * 16UL * 1000 + u16hPeriod / 2) / u16hPeriod + SC0_READ_VTOTAL() / 2) / (SC0_READ_VTOTAL())) * ((CURRENT_SOURCE_IS_INTERLACE_MODE()) ? 2 : 1) ); // param: input Vfreq
	// ivs setting for nvidia VBI and PSV_4M TB
	mStar_SetIVS();
	#if ( !PanelDualPort && !PANEL_QUAD_PORT) || (PanelTTL)// Single Port
	u32ODCLK_KHZ = u32ODCLK_KHZ * 2;
	#endif // end of ##if LVDS_1ch
	APPMSTAR_printData("11   u32ODCLK_KHZ:%d", u32ODCLK_KHZ / 1000);
	mStar_LPLL1_Setting( u32ODCLK_KHZ / PANEL_H_DIV); // scalar dual engine: /2
	//MST_printData( "output dclk_OP22 %d", (u32ODCLK_KHZ+500)/1000 );
//printData("\r\n _____[%d]",g_SetupPathInfo.ucSCPathMode);
	// Case 1, 2: Set LPLL2
	if ( (g_SetupPathInfo.ucSCPathMode == SC_PATH_MODE_1) )
	{
		// clock changed according to 3D formats
		u32ODCLK_KHZ = ( float )XTAL_CLOCK_KHZ * 16UL / u16hPeriod * (PanelHTotal - PANEL_WIDTH + u16HDE_OP21) * ( (u16VDE_OP21) - 1 ) / ( u16Height - 1 ); // output dot clock in KHz
		mStar_LPLL2_Setting( u32ODCLK_KHZ / PANEL_H_DIV); // scalar dual engine: /2
		//printData( "output dclk_OP21 %d", (u32ODCLK_KHZ+500)/1000 );
	}
	else //Setting LPLL2 for LB clk
	{
		if( (g_SetupPathInfo.ucSCPathMode == SC_PATH_MODE_5)
		        || (g_SetupPathInfo.ucSCPathMode == SC_PATH_MODE_6) )
			u32ODCLK_KHZ = u32Sclk;
		mStar_LPLL2_Setting( u32ODCLK_KHZ / PANEL_H_DIV * 21 / 20); // +5% for SSC
		//MST_printData( "LPLL2 clk (LB) %d", (u32ODCLK_KHZ*21/20+500)/1000 );
	}
	//  Timing Gen Setting
	mStar_SetTimingGen(u16HDE_OP21, u16VDE_OP21, FALSE);
	Delay1ms( 100 ); // 080204 wait for output clock stable
	msWriteByteMask( SC0_02, 0, BIT7); // enable lock input mode
	#if CHIP_ID==CHIP_TSUMU
	msWriteByteMask(SC0_1F, BIT7, BIT7);
	#endif
	#if FRAME_BFF_SEL == FRAME_BUFFER
	#if ENABLE_FREESYNC
	if (g_SetupPathInfo.bFBMode)
		msWriteByteMask( REG_3818, BIT3, BIT3 ); //[3] frame lpll enable
	else
		msWriteByteMask( REG_3818, 0, BIT3 ); //[3] frame lpll enable
	#else
	msWriteByteMask( REG_3818, BIT3, BIT3 ); //[3] frame lpll enable
	#endif
	msWriteByteMask( REG_3818, BIT3, BIT3 ); //[3] frame lpll enable
	#endif
	#if ENABLE_FACTORY_SSCADJ // 2011-09-16 19:46 CC
	mStar_SetPanelSSC(FactorySetting.SSCModulation, FactorySetting.SSCPercentage);
	#else
	mStar_SetPanelSSC(PANEL_SSC_MODULATION_DEF, PANEL_SSC_PERCENTAGE_DEF);
	#endif
	msWriteByteMask(REG_3876,    0, BIT0);  // resync
	msWriteByteMask(REG_3876, BIT0, BIT0);
	msWriteByteMask(REG_3876,    0, BIT0);
	mStar_CheckFastClock(u16hPeriod); //Jison 110413
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
	#if (FRAME_BFF_SEL == FRAME_BUFFER)
	msWriteByte(SC0_27, BIT7 | BIT6 | BIT5 | BIT1); // enable auto-htotal
	#else
	msWriteByte(SC0_27, BIT6 | BIT5 | BIT1); // enable auto-htotal
	#endif
	msWriteByte(SC0_49, 0x6F);
	// display timing OP2-2
	msWrite2Byte(REG_3002, ( PanelVTotal - 1 )); //Vtotal
	msWrite2Byte(REG_3004, ( PanelHTotal / PANEL_H_DIV - 1 )); //Htotal
	msWrite2Byte(REG_3006, 0x00); //FPLL trig line number <Default 0>
	msWrite2Byte(REG_3008, 0x00); //FPLL trig pixel number <Default 0>
	msWrite2Byte(REG_300A, ( PanelVTotal - 1 - 3 )); //VS line start <-3>
	msWrite2Byte(REG_300C, ( PanelVTotal - 1 - 2 )); //VS line end <-2>
	msWrite2Byte(REG_3010, 0x00); //HS pixel start
	msWrite2Byte(REG_3012, ( PanelHSyncWidth / PANEL_H_DIV - 2 )); //HS pixel end
	msWrite2Byte(REG_3014, 0x00); //VFDE line start
	msWrite2Byte(REG_3016, ( PANEL_HEIGHT - 1 )); //VFDE line end
	msWrite2Byte(REG_3018, ( PanelHStart / PANEL_H_DIV )); //HFDE pixel Start
	msWrite2Byte(REG_301A, ( ( PanelHStart / PANEL_H_DIV ) + (PANEL_WIDTH / PANEL_H_DIV) - 1 )); //HFDE pixel End
	msWrite2Byte(REG_301C, 0x00); //VMDE line start
	msWrite2Byte(REG_301E, ( PANEL_HEIGHT - 1 )); //VMDE line end
	msWrite2Byte(REG_3020, ( PanelHStart / PANEL_H_DIV )); //HMDE pixel start
	msWrite2Byte(REG_3022, ( ( PanelHStart / PANEL_H_DIV ) + (PANEL_WIDTH / PANEL_H_DIV) - 1 )); //HMDE pixel end
	msWrite2Byte(REG_302E, 0x00); //MRW trig x <Default 0>
	msWrite2Byte(REG_3030, ( PanelVTotal - 1 - 3 )); //MRW trig y (vtotal -3)
	#if PANEL_OUTPUT_FMT_3D_LR || PANEL_OUTPUT_FMT_3D_CB
	msWrite2Byte(REG_304C, ( (PANEL_WIDTH / 2) - 1 ) | _BIT15);
	msWrite2Byte(REG_3050, ( (PANEL_WIDTH / 4) + 0x0A - 1));
	#endif
	#if PANEL_OUTPUT_FMT_3D_CB
	msWriteByte(REG_30A1, 0x40);
	#endif
}
#endif

