#define _MSTAR_C_
#include <math.h>
#include "types.h"
#include "board.h"
#include "ms_reg.h"
#include "global.h"
#include "panel.h"
#include "adjust.h"
#include "ms_rwreg.h"
#include "debug.h"
#include "misc.h"
#include "ddc.h"
#include "power.h"
#include "detect.h"
#include "msOsd.h"
#include "gamma.h"
#include "mstar.h"
//#include "extlib.h"
#include "menu.h"
#include "menudef.h"
#include "menufunc.h"
#include "MsID_V1.h"
#include "drvgpio.h"
#include "drvadc.h"
#include "Mcu.h"
#if ENABLE_HDCP
#include "MsHDCP.h"
#endif

#if ENABLE_HDMI
#include "msHDMI.h"
#include "msHDMIACE.h"
#endif


#include "MsDLC.h"
#include "MsACE.h"
#include "Userpref.h"


#if ENABLE_RTE
#include "drvmsOVD.h"
#endif

#if MS_DAC
#include "drvDAC.h"
#endif


#if ENABLE_DP_INPUT
#include "drvDPRxApp.h"
#endif

#if ENABLE_DisplayPortTX
#include "drvDPTxApp.h"
#endif

//#include "drvmsOVD.h"
///////////////////////////////////////////
#include "drvMcu.h"
#include "drvmStar.h"
#include "appmStar.h"
//////////////////////////////////////////
#include "LedControl.h"
#ifdef TSUMXXT		//110311 Modify
#include <MsADC.h>  // Provides: msADC_init()

typedef enum LPLL_INPUT_DIV_t
{
	LPLL_INPUT_DIV_1 = 0,
	LPLL_INPUT_DIV_2 = 1,
	LPLL_INPUT_DIV_4 = 2,
	LPLL_INPUT_DIV_8 = 3,
} LPLL_INPUT_DIV_t;

typedef enum LPLL_OUTPUT_DIV_t
{
	LPLL_OUTPUT_DIV_1 = 0,
	LPLL_OUTPUT_DIV_2 = 1,
	LPLL_OUTPUT_DIV_4 = 2
} LPLL_OUTPUT_DIV_t;

static void mStar_LPLL_GetDividers (const DWORD kHzODCLK, LPLL_INPUT_DIV_t* pInputDiv, LPLL_OUTPUT_DIV_t* pOutputDiv, BYTE* pLoopDiv);
static void mStar_LPLL_GetFactor   (const DWORD kHzODCLK, const BYTE        loopDiv, DWORD*             pFactor);
#endif  // end of #if( ChipID == CHIP_TSUMT )

#if PanelminiLVDS
extern void SetRSDSToTTL(BYTE on);
#endif

extern void OSDConfGDCurveH(BYTE ci, BYTE pixel_init, BYTE delta_init,
                            BYTE step, BYTE data_sign, BYTE delta_sign, BYTE delta, WORD length0, WORD length1,
                            BYTE hv_sign, BYTE overflow_en, BYTE md);
extern void OSDConfGDCurveV(BYTE ci, BYTE pixel_init, BYTE delta_init,
                            BYTE step, BYTE data_sign, BYTE delta_sign, BYTE delta, WORD length0, WORD length1,
                            BYTE overflow_en, BYTE md);
extern void OSDGDCurveSelectionForWindow(BYTE gi, BYTE wi, BYTE ci);

//*******************************************************************
//
// Constant Definition
//
//*******************************************************************
#define ADC2Sets    0//0// 1 for chip with 2 ADC(9x5x & 9x4x)
#define OutDClk1    108
#define OutDClk2    135
#if PanelLVDS
//14.318 * 15 * 8 / 3.5 = 490.9, 490.9<<19=257374477.16,   490.9<<3=8=3927
#define DClkFactor  257374477ul
//#define DClkFactor      257650102// use 215 as base
#else
//14.318 * 15 * 8 / 4 = 429.54, 429.54<<19=225202667.52,   429.54<<3=8=3436.32
#define DClkFactor  225202667ul
//#define DClkFactor      257650102// use 215 as base
#endif

#define FreeRunDClk (DWORD)DClkFactor/PanelDCLK

// 2006/8/25 11:43AM by Emily BYTE InputSclk;  //2006-07-07 Andy

#if ENABLE_HDMI
#define DIFF(a, b)                  (a>b?(a-b):(b-a))
#endif
//*******************************************************************
//
// extern declaration
//
//*******************************************************************
//*******************************************************************
//
// local declaration
//
//*******************************************************************
void mStar_SetupInputPort(void);
void mStar_SetupADC(void);
Bool mStar_SetCaptureWindow(void);
void mStar_InitADC(void);
//void mStar_InitTCON(void);
void mStar_SetUserPref(void);
#ifdef ReduceDDC
void InitVccDetectPin(void);
void GPIOPWMSelect(void);
#endif

void SetPWMFreq(WORD freq);
void UnUseFunc(void);		//110311 Modify

#if 0
extern void AdjustSuperResolution(void);
extern Bool SetSR_DEMOSize(BYTE ucSize, WORD DEMO_Hsize);	//120524 Modify
#endif

#if ENABLE_RTE
extern  void msFBDummy(void);
#endif
#if 1
extern void msClearVersionDummy(void);
#endif

//*******************************************************************
//*******************************************************************
//*******************************************************************
/*
void mStar_ACOnInit(void)
{
    // 130415 coding test
    hw_Set_HdcpHpd();
//    hw_Set_HdcpHpd2();
 //   hw_Set_HdcpHpd3();

#if ENABLE_MHL
    mapi_mhl_init();
#endif

#if ENABLE_DP_INPUT
    DPRxInit();
#endif
    mStar_SetupInputPort();
}
*/

void ScalerReset(void)
{
	SC0_SUB_BANK_SEL(0);//msWriteByte( SC0_00, 0x00 );
	SC0_SCALER_RESET(0);//msWriteByte( SC0_F1, 0x00 );
	mStar_ScalerDoubleBuffer(FALSE);
	// power down contorl 0xF0~0xF1
	SC0_SCALER_RESET(0);//msWriteByte( SC0_F1, 0x00 ); //20081024 RD suggest
	SC0_SCALER_POWER_DOWN(0, 0xFF);//msWriteByte( SC0_F0, 0x00 ); //|BIT6); // power up chip
	SC0_SCALER_RESET(0x7F);//msWriteByte( SC0_F1, 0x7F ); // software reset // DDCCI enable bit6
	ForceDelay1ms( 1 );
	SC0_SCALER_RESET(0);//msWriteByte( SC0_F1, 0x00 ); // software reset
	SC0_NORMAL_MODE();//msWriteByte( SC0_F8, 0x00 ); // ???? important
}

void SetPWMFreqAndVsyncAlign(void)
{
	drvGPIO_SetPWMFreq(BrightnessPWM, BRIGHTNESS_FREQ);
	drvGPIO_PWMAlignVSync(BrightnessPWM, BRIGHTNESS_VSYNC_ALIGN);
	#if (CHIP_ID == CHIP_TSUM9 ||CHIP_ID == CHIP_TSUMF)
	drvGPIO_PWMAlignHSync(BrightnessPWM, BRIGHTNESS_HSYNC_ALIGN);
	#endif
	#if SpeakerDet_Enable
	drvGPIO_SetPWMFreq(VolumePWM, VOLUME_FREQ);
	drvGPIO_PWMAlignVSync(VolumePWM, VOLUME_VSYNC_ALIGN);
	#endif
}

void GPIOPWMSelect(void)
{
	Init_BrightnessPWM();
	#if SpeakerDet_Enable
	Init_VolumePWM();
	#endif
	SetPWMFreqAndVsyncAlign();
}

//*******************************************************************
// Function Name: mStar_Init(void)
//
// Description: Initialize mStar chip while 1st power on system
//
// Caller: mStar_InitADC(), mStar_InitTCON, mStar_SetupFreeRunMode()
//         mStar_SetupInputPort() in mStar.c
//         msWriteByte(), msWrite2Byte() in ms_rwreg.c
//         mStar_WriteDDC1(), mStar_WriteDDC2() in ddc.c
//         mStar_InitGamma() in gamma.c
//         Osd_InitOSD() in osd.c
// Callee: Init_Device() in main.c
//*******************************************************************
void mStar_Init(void)
{
	#if 1
	#if (CHIP_ID == CHIP_TSUMC)||(CHIP_ID == CHIP_TSUMD)||(CHIP_ID == CHIP_TSUMJ)||(CHIP_ID == CHIP_TSUM9)||(CHIP_ID == CHIP_TSUMF)
	#if USE_VCTRL
	msWriteByteMask(REG_01A5, BIT1, BIT1);
	ForceDelay1ms(10);
	msWriteByteMask(REG_0183, 0x00, 0x70);
	#elif USE_EXTERNAL_LDO
	msWriteByteMask(REG_01A5, 0, BIT1);
	msWriteByteMask(REG_0183, 0x50, 0x70);
	#else
	#if CHIP_ID==CHIP_TSUMF
	if (msEread_GetDataFromEfuse(0x07) < 228)
	{
		msWriteByteMask(REG_0183, 0x70, 0x70);
	}
	else
	#endif
	{
		msWriteByteMask(REG_0183, 0x00, 0x70);
	}
	#endif
	#endif
	#if ENABLE_FLASH_CURRENT_ADJUSTMENT
	msWriteByteMask(REG_0213, FLASH_DEFAULT_CURRENT, BIT1 | BIT0); // SPI_CK driving current
	msWriteByteMask(REG_0213, FLASH_DEFAULT_CURRENT << 2, BIT3 | BIT2); // SPI_DI driving current
	msWriteByteMask(REG_0213, FLASH_DEFAULT_CURRENT << 4, BIT5 | BIT4); // SPI_DO driving current
	msWriteByteMask(REG_0213, FLASH_DEFAULT_CURRENT << 6, BIT7 | BIT6); // SPI_CZ driving current
	#endif
	drvmStar_Init();
	GPIOPWMSelect();
	Power_ModCtrl(_DISABLE); //Jison 110421 disable panel data out
	#if ENABLE_DP_INPUT
	if( g_bDoDPInit )
		DPRxInit();
	#endif
	#if ENABLE_DisplayPortTX
	DPTxInit();
	#endif
	mStar_InitADC();
	mStar_SetupFreeRunMode();
	#if ENABLE_HDCP
	//msDisableHDCP();
	msInitHDCPProductionKey();
	#endif
	#if ENABLE_RTE
	msOverDriverInit();
	#ifdef _MULTI_OD_
	//msLoad_MultiODTable();
	msOverDriveOnOff( FALSE );
	msRTE_LoadLUT();
	msOverDriveOnOff( TRUE );
	//msLoadODTable( tOverDrive );
	#else
	msOverDriveOnOff( FALSE );
	msRTE_LoadLUT();
	if(UserPrefRTEMode == OFF
        #if ENABLE_DISPLAY_UNDERSCAN
	        || (UnderScanSetting.Enable) || (g_SetupPathInfo.bFBMode)
        #endif
        #if ENABLE_DUAL_LINK
	        || ((GetVfreq() > 85) && (!ENABLE_FREESYNC)) //(SrcModeIndex==MODE_1920x1080P_144Hz)	//130328 Modify
        #endif
	  )
	{
		msOverDriveOnOff( FALSE );
	}
	else
	{
		msOverDriveOnOff( TRUE );
	}
	//msLoadODTable( tOverDrive );
	#endif
	// msOverDriveOnOff( FALSE );
	#endif
	#if (CHIP_ID == CHIP_TSUMC) || (CHIP_ID == CHIP_TSUMD) || (CHIP_ID == CHIP_TSUM9)|| (CHIP_ID == CHIP_TSUMF) //130912 nick add
	#if ENABLE_DP_INPUT
	if(!CURRENT_INPUT_IS_DISPLAYPORT())
	{
		DPRxIRQEnable(FALSE);
		DPSetOffLine();
	}
	else
		drvmStar_SetupInputPort_DisplayPort();
	#endif
	#endif
	#if ENABLE_HDMI
	mstar_HDMIInitialVariable();
	mstar_HDMIInitialAudio();
	#endif
	#if MS_DAC
	#if ENABLE_HDMI || ENABLE_DP_AUDIO
	msAudio_I2S_SPDIF_Init();
	#endif
	msAudioDAC_Init(); // Audio DAC init
	#endif
	#else
	BYTE i;
	BYTE NOUSE = 0;
	msInitClockGating();
	#if INPUT_TYPE >= INPUT_1A1D //ENABLE_HDMI_INPUT || ENABLE_DVI_INPUT //coding
	msTMDSInit();
	#endif
	msWriteByteMask(SC0_02, BIT7, BIT7);
	for( i = 0; i < sizeof( tblInit ) / sizeof( RegUnitType ); i++ )
		msWriteByte( tblInit[i].u16Reg, tblInit[i].u8Value );
	#if CHIP_ID==CHIP_TSUMU
	for( i = 0; i < sizeof( tb_3D_DITHER_TABLE ) / sizeof( RegUnitType ); i++ )
		msWriteByte( tb_3D_DITHER_TABLE[i].u16Reg, tb_3D_DITHER_TABLE[i].u8Value );
	#endif
	Power_ModCtrl(_DISABLE); //Jison 110421 disable panel data out
	#if 1//CHIP_ID==CHIP_TSUML || CHIP_ID==CHIP_TSUMU
	msWriteByteMask( SC0_48, 0, BIT4 ); 					//Turn off New mode, (Show line tune fast)
	#endif
	#if CHIP_ID != CHIP_TSUMU
	#if (SHORT_LINE_CHECK== 0) // short-line tuning is disabled
	// Diable short-line tuning
	{
		//Jison 100818 Will update Htotal reg by SPRHDC and LPLL reg, if do after mStar_SetupFreeRunMode(), will cause crash logo screen.
		msWriteByteMask(SC0_63, BIT0,  BIT1 | BIT0);
		msWriteByteMask(SC0_28,    0,  BIT6);
	}
	#endif    // end of #if (ShortLineCheck)
	#endif
	#if CHIP_ID!=CHIP_TSUMV
	msWriteByteMask(SC0_0E, BIT7, BIT7); // H coring disable, for dot pattern certical block issue, Jison 100610
	#endif
	#if (CHIP_ID==CHIP_TSUMB || CHIP_ID==CHIP_TSUMY)
	msDVIEQCalibration();
	#endif // #if ChipID==CHIP_TSUMA
	GPIOPWMSelect(); // wait for coding
	mStar_InitADC();
	mStar_SetupFreeRunMode();
	#if ENABLE_HDCP
	msInitHDCPProductionKey();
	#endif
	//mStar_InitTCON();
	#if ENABLE_HDMI
	mstar_HDMIInitialVariable();
	mstar_HDMIInitialAudio();
	#endif
	#if MS_DAC
	#if ENABLE_DP_AUDIO || ENABLE_HDMI
	msWriteByte( REG_05C8, 0x8A ); // [7]: Frame repetition manual mode; [3]: auto DSD detection; [1]: auto PCM detection
	msWriteByte( REG_05CC, 0xD1 ); // [7]: mute pin to normal(H->L), (set active low for this DAC); [6]:Disable audio mute output; [4]: Global audio mute; [1:0]: 1/4 audio FIFO
	msWriteByte( REG_05CD, 0x0A ); // [7:6]: audio ch 12/34/56/78, [4]: DP/HDMI audio, [3]: auto DSD detection; [1]: auto PCM detection
	msWriteByte( REG_05CF, 0xC0 ); // Fading gain = 0dB
	// I2S and S/PDIF setting
	msWriteByte( REG_05E4, 0x13 ); // [4]: New mode, [1]: Enable CTSN synthesizer clock, [0]: Enable audio FIFO read clock.
	msWriteByte( REG_05E5, 0x6A ); // [7:6]:128Fs, [5]:MCLK output, [3]:I2S encoder clock, [1]:S/PDIF encoder clock
	msWriteByte( REG_05E6, 0x39 ); // [6:5]:24bits to DAC, [4]:enable DAC 256Fs clock, [3]: I2S left-justified, [1:0]:24 bits to I2S
	msWriteByte( REG_05E7, 0x07 ); // [2]:AUMUTE pin, [1]:S/PDIF, [0]:I2S enable
	msWriteByteMask( REG_05F0, 0, BIT3 ); // [3]: AULL power down
	msWriteByte( REG_05F1, 0x0A ); // [3]:FBCLK enable, [1]:DCLK enable
	msWriteByte( REG_05F7, 0x26 ); // [7:4]:DDIV = 2, [3:0]:FBDIV = 6
	msWriteByte( REG_05F8, 0x81 ); // [7]: Enable CTS-N synthesizer, [0]: CTS[19:0]
	#endif
	msAudioDAC_Init(); // Audio DAC init
	#endif
	#endif
	#if (ENABLE_HDMI && ENABLE_CABLE_5V_EDID && ENABLE_FREESYNC)
	drvmStar_EnableHDMIFreeSyncEDID(UserprefFreeSyncMode);
	#endif
	mStar_SetupInputPort();
	#if PanelminiLVDS||PANEL_VCOM_ADJUST	//110229 Modify
	#if PANEL_VCOM_ADJUST			//	For Turn on panel  R/W Vcom	130311 Modify
	#else
	g_bACPowerOn_CheckVCOM = TRUE ;
	#endif
	#endif
	Osd_InitOSD();
	iGenTuningFinished = 0;
	#if DisplayPowerOnLogo
	if (DisplayLogoFlag)
	{
		Menu_InitAction();
	}
	#endif
	#if Enable_Gamma || ENABLE_GAMMA_FIX_PANEL_NOISE	//120204 Modify
	mStar_SetupGamma( UserPrefGamaMode);
	#endif
	// Init_MWE();
	#if MWEFunction
	#if HDMICOLORTEST
	//InitHDMIACEVar();
	#endif
	#endif
	InitACEVar();	//120420 Modify
	InitialPeaking();
	msAdjustSharpness( MAIN_WINDOW, GetRealSharpness(), 0 );
	//msAdjustVideoSaturation(MAIN_WINDOW,0x80);
	#if !ENABLE_DeltaE && CHIP_ID==CHIP_TSUMU
	msWriteByteMask(SC7_D0, BIT7 | BIT6 | BIT0, BIT7 | BIT6 | BIT0); //Main window Y noise-masking dither enable
	msWriteByteMask(SC7_D2, BIT6, BIT6); //Sub window Y noise-masking dither enable
	#endif
//    mStar_SetUserPref();		//130128_4	Henry
	UnUseFunc();
}

#if UseINT //Enable mode change INT
void mStar_EnableModeChangeINT(Bool u8Enable)
{
	//BYTE u8OrgValue=msReadByte(SC0_CE);
	if (u8Enable)
	{
		//msWriteByte( SC0_CC, 0x00 );
		//msWriteByte( SC0_CD, 0x00 );
		INT_STATUS_CLEAR();
		if (CURRENT_INPUT_IS_VGA())
		{
			INT_SCALER_A(0xB0);//msWriteByte(SC0_CE, 0xB0);
			INT_SCALER_B(0x00);//msWriteByte(SC0_CF, 0); // clock change
		}
		else if ( CURRENT_INPUT_IS_DISPLAYPORT())
		{
			#if ENABLE_FREESYNC
			if(IS_DP_FREESYNC())
				INT_SCALER_A(0x20);
			else
			#endif
				INT_SCALER_A(0x30);
			INT_SCALER_B(0x00);
		}
		else
		{
			#if ENABLE_FREESYNC
			if(( CURRENT_INPUT_IS_HDMI()) && (UserprefFreeSyncMode == FreeSyncMenuItems_On))
				INT_SCALER_A(0x20);
			#else
			INT_SCALER_A(0x30);//msWriteByte(SC0_CE, 0x30); // for YCbCr
			#endif
			INT_SCALER_B(BIT2);//msWriteByte(SC0_CF, BIT2); // clock change
		}
	}
	else
	{
		INT_SCALER_A(0x00);//msWriteByte(SC0_CE, 0x00);
		INT_SCALER_B(0x00);//msWriteByte(SC0_CF, 0x00);
		//msWriteByte(SC0_CC, 0x00);
		//msWriteByte(SC0_CD, 0x00);
		INT_STATUS_CLEAR();
	}
	//return u8OrgValue;
}
#endif

Bool mStar_SetPanelTiming(void)
{
	if(appmStar_SetPanelTiming() == FALSE)
		return FALSE;
	return TRUE;
}

#if FieldInvertCheck
void mStar_CheckInterlacemode( BYTE ucFlag )
{
	WORD xdata ucCount;
	BYTE xdata ucField0, ucField1;
	WORD xdata wTemp, wTemp0 = 0, wTemp1 = 0;
	if(CURRENT_INPUT_IS_VGA())//20130418
		return;
	if( ucFlag )
	{
		msWriteByte( SC0_00, 0x00 );
		// if( msReadByte( SC0_E1 )&BIT3 )				//130116_4 Henry For TimingChange After DPS On In DP Source
		//     msWriteByte( SC0_E8, msReadByte( SC0_E8 ) | 0x03 );
		msWriteByte( SC0_E9, msReadByte( SC0_E9 ) | BIT0 );
		ForceDelay1ms( 100 );
		ucCount = 0;
		wTemp0 = wTemp1 = 0;
		while( ucCount++ < 1000 )
		{
			if( msReadByte( SC0_E1 )&BIT2 )
			{
				wTemp = msRead2Byte( SC0_95 );
				if( wTemp > 0x250 )
					wTemp1 = wTemp;
			}
			if( !( msReadByte( SC0_E1 )&BIT2 ) )
			{
				wTemp = msRead2Byte( SC0_95 );
				if( wTemp > 0x250 )
					wTemp0 = wTemp;
			}
			if( !wTemp0 && ( wTemp0 >> 8 ) == ( wTemp1 >> 8 ) && wTemp0 != wTemp1 )
				break;
		}
		ucField1 = abs( wTemp1 - wTemp0 );
		msWriteByte( SC0_E9, msReadByte( SC0_E9 ) & ( ~BIT0 ) );
		ForceDelay1ms( 100 );
		ucCount = 0;
		wTemp0 = wTemp1 = 0;
		while( ucCount++ < 1000 )
		{
			if( msReadByte( SC0_E1 )&BIT2 )
			{
				wTemp = msRead2Byte( SC0_95 );
				if( wTemp > 0x250 )
					wTemp1 = wTemp;
			}
			if( !( msReadByte( SC0_E1 )&BIT2 ) )
			{
				wTemp = msRead2Byte( SC0_95 );
				if( wTemp > 0x250 )
					wTemp0 = wTemp;
			}
			if( !wTemp0 && ( wTemp0 >> 8 ) == ( wTemp1 >> 8 ) && wTemp0 != wTemp1 )
				break;
		}
		ucField0 = abs( wTemp1 - wTemp0 );
		//MST_printData(" FInvert wTemp0 %x", wTemp0);
		//MST_printData(" FInvert wTemp1 %x", wTemp1);
		//MST_printData(" FInvert ucCount %x", ucCount);
		//MST_printData(" FInvert ucField0 %x", ucField0);
		//MST_printData(" FInvert ucField1 %x", ucField1);
		msWriteByte( SC0_00, 0x00 );
		if( ucCount < 1000 )
		{
			if( ucField0 >= 7 )
			{
				msWriteByte( SC0_E9, msReadByte( SC0_E9 ) | BIT0 );
			}
			else
			{
				if( ucField0 > ucField1 && abs( ucField0 - ucField1 ) >= 2 )
				{
					msWriteByte( SC0_E9, msReadByte( SC0_E9 ) | BIT0 );
				}
			}
		}
	}
	else
	{
		msWriteByte( SC0_00, 0x00 );
		//msWriteByte( SC0_E8, 0 );		//130116_4 Henry
	}
}
#endif

//*******************************************************************
// Function Name: mStar_SetupMode
//
// Decscription: setup registers for input timing,
// return      : TRUE,
// caller: mStar_SetupADC(), mStar_SetupCaptureWindow(),
//         mStar_SetScalingFactor(), mStar_SetPanelTiming(),
//         mStar_SetUserPref() in mstar.c
//         mStar_FineTuneDVIPhase(), mStar_ValidTimingDetect() in detect.c
//         mSar_WriteByte(), msReadByte() in ms_rwreg.c
// callee: mStar_ModeHandler() in detect.c
//*******************************************************************
Bool mStar_SetupMode(void)
{
	#if ENABLE_DISPLAY_UNDERSCAN
	WORD hFreq, vFreq;
	#endif
	Clr_FreeRunModeFlag();
	Clr_BackToUnsupportFlag();	//111223 Modify
	Clr_BackToStandbyFlag();	//111223 Modify
// 121123 coding, moved here from mStar_PrepareForTimingChange()
	#if 0//ESaverPowerDownFunc		//110227 Modify for TPV Request
	ESaverPowerDownCounter = 0;
	#endif
	mStar_SetupADC(); // setup ADC block, including polarity & htotal, phase, vco
	#if ENABLE_DUAL_LINK //&& DL_PXL_RAT_DET
	if (IsSrcUseDualLinkDviPort())
		msDVIDualLinkMode(msGetDVIDualLinkStatus());
	#endif
	if (mStar_SetCaptureWindow() == FALSE)
		// setup capture window
	{
		//      printMsg("Err_1");
		return FALSE;
	}
	#if ENABLE_DISPLAY_UNDERSCAN // 120529 coding modified for just MHL timing Vfreq under 48Hz could into frame buffer
	hFreq = HFreq( SrcHPeriod );
	vFreq = VFreq( hFreq, SrcVTotal );
	if(CURRENT_SOURCE_IS_INTERLACE_MODE())
	{
		vFreq *= 2;
		#if 0//ENABLE_DEBUG
		printMsg("CURRENT_SOURCE_IS_INTERLACE_MODE");
		#endif
	}
	//if(CURRENT_INPUT_IS_HYBRID_MHL_HDMI() && gMHLInfo.bMhlCablePlugged == TRUE && vFreq<DISPLAY_UNDERSCAN_FREQ)
	if(vFreq < DISPLAY_UNDERSCAN_FREQ || vFreq > 1400)
	{
		UnderScanSetting.Enable = 1;
		UnderScanSetting.HSize = DISPLAY_UNDERSCAN_SPACE;
		UnderScanSetting.VSize = DISPLAY_UNDERSCAN_SPACE;
		#if ENABLE_RTE	//120611 Modify
		msOverDriveOnOff( FALSE );
		#endif
	}
	else
	{
		UnderScanSetting.Enable = 0;
		UnderScanSetting.HSize = 0;
		UnderScanSetting.VSize = 0;
	}
	#endif
	#if (CHIP_ID==CHIP_TSUMU ||CHIP_ID==CHIP_TSUM2||CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD ||CHIP_ID==CHIP_TSUM9||CHIP_ID==CHIP_TSUMF)
	mStar_SetupPath();
	#else
	mStar_SetScalingFactor(); // setup scaling factor
	mStar_SetScalingFilter();
	#endif
	if (mStar_SetPanelTiming() == FALSE)
		// set output dclk
	{
		#if DEBUG_MSG
		printMsg( "===>mstar fail Not support" );
		#endif
		SrcFlags |= bUnsupportMode;
		//    printMsg("Err_2");
		return TRUE;
	}
// 121019 coding addition
	#if 0//(ENABLE_DUAL_LINK)&&(ENABLE_RTE)		//130402 Modify
	if(GetVfreq() > 85
        #if ENABLE_120Hz_OD
	        && !(g_SetupPathInfo.wImgSizeOutH == PanelWidth &&  g_SetupPathInfo.wImgSizeOutV == PanelHeight)
        #endif
	  )//(SrcModeIndex==MODE_1920x1080P_144Hz)
	{
		msOverDriveOnOff( FALSE );
	}
	#endif
	if (InputTimingChangeFlag || mStar_ValidTimingDetect())
		// check if input timing has changed
	{
		//printMsg("Err3");
		return FALSE;
	}
	// enable double buffer
	mStar_ScalerDoubleBuffer(TRUE);
	// use interrupt to speedup mode changing while input timing is changing
	#if UseINT
	mStar_EnableModeChangeINT(TRUE);
	#endif
	mStar_InterlaceModeSetting();
	#if FieldInvertCheck
	mStar_CheckInterlacemode( SrcFlags & bInterlaceMode );
	#endif
	#if ENABLE_HDMI	//120420 Modify
	if( mstar_HDMITmdsGetType() == TMDS_HDMI && SrcInputType >= Input_Digital )
		gScInfo.InputColor = mstar_HDMIPacketColor();
	#endif
	mStar_SetUserPref(); // restore user setting // 2006/10/16 12:38AM by Emily
	return TRUE;
}
//*******************************************************************
// Function Name: mStar_SetupFreeRunMode
//
// Decscription: setup registers for free run mode without any input timing,
//
//         msWriteByte(), msReadByte(), msWrite2Byte() in ms_rwreg.c
// callee: mStar_ModeHandler() in detect.c
//*******************************************************************
void mStar_SetupFreeRunMode(void)
{
	drvmStar_SetupFreeRunMode();
	Set_FreeRunModeFlag();
	#if BrightFreqByVfreq
	SetPWMFreq( 250 );
	#endif
	#if EANBLE_NEW_DCR_Functing
	DCR_Counter = 0;
	Clr_EanbleClearBalclightStartFlag();
	Clr_DoClearBalclightFlag();
	#endif
	#if ENABLE_FACTORY_SSCADJ
	mStar_SetPanelSSC(FactorySetting.SSCModulation, FactorySetting.SSCPercentage);
	#else
	mStar_SetPanelSSC(PANEL_SSC_MODULATION_DEF, PANEL_SSC_PERCENTAGE_DEF);
	#endif
}

//*******************************************************************
// Function Name: mStar_SetAnalogInputPort
//
// Decscription: setup registers for Separate Sync/Composite Sync/SOG,
//
// caller: mSar_WriteByte(), msReadByte() in ms_rwreg.c
//
// callee: mStar_MonitorInputTiming() in detect.c
//*******************************************************************
void mStar_SetAnalogInputPort( Bool ToSOGPort )
{
	BYTE regValue = SC0_READ_INPUT_SETTING();//msReadByte(SC0_02);
	#if MS_VGA_SOG_EN
	// if( regValue & BIT4 )
	if(!ToSOGPort)
	{
		regValue = regValue & 0x8F;
		g_bInputSOGFlag = 0;
		//if(bInputVGAisYUV)
		//    drvADC_SetADCSource(ADC_TABLE_SOURCE_YUV_HV);  // input is YUV
		//else
		drvADC_SetADCSource(ADC_TABLE_SOURCE_RGB);   // input is RGB
		SC0_ADC_COAST_ENABLE(0x01);//msWriteByte(SC0_ED, 0x01);   // enable ADC coast
		SC0_ADC_COAST_START(0x03);//msWriteByte(SC0_EE, 0x03); //0x00);   // enable coast window start
		SC0_ADC_COAST_END(0x01);//msWriteByte(SC0_EF, 0x01); //0x00);   // enable coast window end
		SC0_GLITCH_REMOVAL_ENABLE(0);//msWriteByte(SC0_F3, 0x00 ); //RD suggest 20081008
		ADC_PLL_LOCKING_EDGE(0);//msWriteByteMask(REG_ADC_DTOP_07_L,0,BIT5); // 0:Hsync leading edge; 1: Hsync trailing edge
		//printMsg("/r/nInputPort_____VGA");
	}
	else
	{
		regValue = regValue | 0x70;
		g_bInputSOGFlag = 1;
		//if(bInputVGAisYUV)
		drvADC_SetADCSource(ADC_TABLE_SOURCE_SOG);  // input is YUV
		//else
		//    drvADC_SetADCSource(ADC_TABLE_SOURCE_RGB);   // input is RGB
		SC0_ADC_COAST_ENABLE(0x21);//msWriteByte(SC0_ED, 0x21);   // enable ADC coast
		SC0_ADC_COAST_START(0x08);//msWriteByte(SC0_EE, 0x08);   // enable coast window start  //Al050814 Micro version need adjust this value
		SC0_ADC_COAST_END(0x08);//msWriteByte(SC0_EF, 0x08 ); //0x05);   // enable coast window end //Jison 110317 follow CHIP_TSUMT
		SC0_GLITCH_REMOVAL_ENABLE(0);//msWriteByte( SC0_F3,  0x00 );
		ADC_PLL_LOCKING_EDGE(1);//msWriteByteMask(REG_ADC_DTOP_07_L,BIT5,BIT5); // 0:Hsync leading edge; 1: Hsync trailing edge
		//	printMsg("/r/nInputPort_____SOG");
	}
//130912 nick modify for speed up switch port
	SC0_RECOVER_INPUT_SETTING(regValue);//msWriteByte(SC0_02, regValue);
	SC0_SCALER_RESET(GPR_B | ADCR_B); // enable software reset function to clear ADC & Graphic port RO register
	Delay1ms(2);
	SC0_SCALER_RESET(0); // disable software reset
	Delay1ms(80); // delay over 1 frame time to wait for status register is ready
	#else
	ToSOGPort = ToSOGPort;
	regValue = regValue & 0x8F;
	g_bInputSOGFlag = 0;
	drvADC_SetADCSource(ADC_TABLE_SOURCE_RGB);
	ADC_PLL_LOCKING_EDGE(0);// 0:Hsync leading edge; 1: Hsync trailing edge  //20130517 Modify
	SC0_RECOVER_INPUT_SETTING(regValue);//msWriteByte(SC0_02, regValue);
	#endif
}
//*******************************************************************
// Function Name: mStar_SetupInputPort
//
// Decscription: setup input port registers for
//               Analog/Digital/YCbCr(Video) input
//
// caller: mSar_WriteByte(), msReadByte() in ms_rwreg.c
// callee: mStar_MonitorInputTiming() in detect.c
//*******************************************************************
void mStar_SetupInputPort(void)
{
	#if Dual
	if (!(FactoryModeFlag))
		Set_ShowInputInfoFlag();
	#endif
	#if CHIP_ID == CHIP_TSUMU
	if(!g_SetupPathInfo.bOverrideSCFmtIn)
		g_SetupPathInfo.ucSCFmtIn = SC_FMT_IN_NORMAL;
	g_SetupPathInfo.ucIPLRSel = IP_3D_LR_FRAME_DET;
	#elif CHIP_ID == CHIP_TSUM2
	if(!g_SetupPathInfo.bOverrideSCFmtIn)
		g_SetupPathInfo.ucSCFmtIn = SC_FMT_IN_NORMAL;
	#endif
	#if ENABLE_MHL //&& (CHIP_ID == CHIP_TSUM2)
	MHLExtenCountFlag = 0;
	#endif
	mStar_IPPowerControl(); // 130319 coding addition for test
	#if ((CHIP_ID == CHIP_TSUMC) || (CHIP_ID == CHIP_TSUMD)||(CHIP_ID == CHIP_TSUM9)||(CHIP_ID == CHIP_TSUMF))
	if(!CURRENT_INPUT_IS_TMDS())
	{
		msWriteByteMask(REG_175D, 0x20, 0x20);//Mask HDMI IRQ
		#if DHDMI_SIMPLAYHD_PATCH // SimplayHD CTS 8-18
		msWriteByteMask(REG_1509, 0x84, 0x84);
		#endif
	}
	else
	{
		msWriteByteMask(REG_175D, 0x00, 0x20);
	}
	#if ENABLE_DP_INPUT
	if(!CURRENT_INPUT_IS_DISPLAYPORT())
	{
		#if(CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF)
		DPRxOutputEnable( FALSE );
		#endif
		DPClearOffLineData();
		DPRxIRQEnable(FALSE);
		DPSetOffLine();
	}
	#endif
	#endif
	#ifdef _HW_AUTO_NO_SIGNAL_
	msWriteByteMask(SC0_E7, _BIT4, _BIT4);
	#endif
	if(CURRENT_INPUT_IS_VGA())//( SrcInputType < Input_Digital )
	{
		#if ENABLE_DEBUG
		printMsg("CURRENT_INPUT_IS_VGA");
		#endif
		drvmStar_SetupInputPort_VGA();
		#if (CHIP_ID==CHIP_TSUMC || CHIP_ID==CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)//130604 Modify
		ComboInputControl(COMBO_INPUT_ANALOG);
		#endif
	}
	else if(CURRENT_INPUT_IS_DVI())//( SrcInputType == Input_Digital )
	{
		#if ENABLE_DEBUG
		printMsg("CURRENT_INPUT_IS_DVI");
		#endif
		drvmStar_SetupInputPort_DVI();
		#if ENABLE_MHL && (CHIP_ID == CHIP_TSUM2)
		mapi_mhl_CbusIsolate();
		#endif
		#if (CHIP_ID==CHIP_TSUMC || CHIP_ID==CHIP_TSUMD || CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)//130604 Modify
		ComboInputControl(COMBO_INPUT_DIGITAL);
		#endif
	}
	#if ENABLE_HDMI
	else if(CURRENT_INPUT_IS_HDMI())//(SrcInputType == Input_HDMI)
	{
		#if ENABLE_DEBUG
		printMsg("CURRENT_INPUT_IS_HDMI");
		#endif
		mstar_HDMIInitialVariable();
		drvmStar_SetupInputPort_HDMI();
		#if (CHIP_ID==CHIP_TSUMC || CHIP_ID==CHIP_TSUMD || CHIP_ID==CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)//130604 Modify
		ComboInputControl(COMBO_INPUT_DIGITAL);
		#endif
	}
	#endif
	#if ENABLE_DP_INPUT
	else if(CURRENT_INPUT_IS_DISPLAYPORT())//(SrcInputType == Input_Displayport)
	{
		#if ENABLE_DEBUG
		printMsg("CURRENT_INPUT_IS_DISPLAYPORT");
		#endif
		drvmStar_SetupInputPort_DisplayPort();
		#if (CHIP_ID==CHIP_TSUMC || CHIP_ID==CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)//130604 Modify
		ComboInputControl(COMBO_INPUT_DIGITAL);
		#endif
	}
	#endif
	#if CHIP_ID == CHIP_TSUMV
	if(SrcInputType != Input_VGA)//20130513 for DVI dot pattern color deviation problem.
		msWriteByteMask(SC7_23, 0x40, 0x40);
	#endif
	#if ENABLE_MHL
	#if ((CHIP_ID == CHIP_TSUMC) ||(CHIP_ID == CHIP_TSUMD) ||(CHIP_ID == CHIP_TSUM9) ||(CHIP_ID == CHIP_TSUMF))
	mapi_mhl_SourceChange();
	#endif
	#endif
	ForceDelay1ms(10);//(20);
	SC0_SCALER_RESET(GPR_B | ADCR_B); // enable software reset function to clear ADC & Graphic port RO register
	ForceDelay1ms(20);//(80);
	SC0_SCALER_RESET(0); // disable software reset
	#if ENABLE_HDCP
	#if ENABLE_MHL //&& (CHIP_ID == CHIP_TSUM2)
	if(!CURRENT_INPUT_MHL_CABLE_PLUGGED())
	#endif
		if(CURRENT_INPUT_IS_TMDS())//( SrcInputType == Input_Digital || SrcInputType == Input_Digital2 )
			msEnableHDCP();
	#endif
}
//*******************************************************************
// Function Name: mStar_SetCaptureWindow
//
// Decscription: setup input capture window for display
//
// caller: mSar_WriteWord(), msRead2Byte() in ms_rwreg.c
///
// callee: mStar_SetupMode() in mstar.c
//*******************************************************************
#if ENABLE_OVER_SCAN
#define PanelPitch 2760ul //2715ul // 0.2715 * 10000 = mm
#endif

Bool mStar_SetCaptureWindow(void)
{
	WORD width, height;
	#if ENABLE_OVER_SCAN
	#if CHIP_ID == CHIP_TSUMU
	BYTE DualInDivider = 1;
	#endif
	XDATA DWORD wTemp;
	XDATA WORD wTempRatio;
	WORD M, N;
	WORD CapWinHStart, CapWinVStart;
	WORD OverScanHDisp, OverScanVDisp, OverScanHCap, OverScanVCap;
	#endif
	#if CHIP_ID == CHIP_TSUMD 	//20130909 nick modify
	#if !ENABLE_OVER_SCAN
	WORD CapWinHStart, CapWinVStart;
	WORD OverScanHDisp, OverScanVDisp, OverScanHCap, OverScanVCap;
	#endif
	BYTE DualInDivider = 1;
	#endif
	if(
	    CURRENT_INPUT_IS_TMDS()//SrcInputType == Input_Digital || SrcInputType == Input_Digital2
    #if ENABLE_DP_INPUT
	    || CURRENT_INPUT_IS_DISPLAYPORT()//SrcInputType == Input_Displayport
    #endif
	)
	{
		UserPrefHStart = SC0_READ_AUTO_START_H();//msRead2Byte(SC0_80); // get hsync DE start
		UserPrefVStart = SC0_READ_AUTO_START_V();//msRead2Byte(SC0_7E); // get vsync DE start
		width = SC0_READ_AUTO_WIDTH();//msRead2Byte(SC0_84)-msRead2Byte(SC0_80)+1; // get DE width
		height = SC0_READ_AUTO_HEIGHT();//msRead2Byte(SC0_82)-msRead2Byte(SC0_7E)+1; // get DE Height
		#if ENABLE_DEBUG
		printData("CAPTUREWIN width001=%d", width);
		printData("CAPTUREWIN height001=%d", height);
		printData("CAPTUREWIN UserPrefHStart001=%d", UserPrefHStart);
		printData("CAPTUREWIN UserPrefVStart001=%d", UserPrefVStart);
		#endif
		if(CURRENT_SOURCE_IS_INTERLACE_MODE())
		{
			if(SC0_DE_ONLY_MODE() == TRUE)//(scReadByte(SC0_04)&BIT6) //DE only mode
			{
				if(SC0_VIDEO_FIELD_INVERSION() == FALSE)//((scReadByte(SC0_E9)&BIT3)==0) //video field invert
				{
					height += 3; //height=(Vend ?V Vstart + 2);
					UserPrefVStart -= 1;      //120522
				}
				else
				{
					height -= 3; //height=(Vend ?V Vstart - 2);
					UserPrefVStart += 1;      //120522
				}
			}
			else
			{
				height--; //height=(Vend ?V Vstart)
			}
			#if ENABLE_DP_INPUT
			if(CURRENT_INPUT_IS_DISPLAYPORT())//SrcInputType == Input_Displayport
			{
				if(scReadByte(SC0_04)&BIT6) //DE only mode
				{
					if((scReadByte(SC0_E9)&BIT3) == 0) //video field invert
						height++;  //height=(Vend ?V Vstart + 2);
					else
						height -= 3; //height=(Vend ?V Vstart - 2);
				}
				else
				{
					if(g_SetupPathInfo.ucSCFmtIn == SC_FMT_IN_NORMAL)
					{
						height += 2; //height=(Vend ?V Vstart + 3);
						UserPrefVStart -= 1;
					}
					else
						height--; //height=(Vend ?V Vstart)
				}
			}
			#endif
		}
		if( PanelWidth == 1366 )		//120119 Modify
		{
			if( width == 1360 )
			{
				UserPrefHStart -= 3;
				width = 1366;
			}
		}
		#if ENABLE_OVER_SCAN && CHIP_ID == CHIP_TSUMU
		if(IS_INPUT_DUAL_IN()) // dual in
		{
			width *= 2;
			DualInDivider = 2;
		}
		#endif
	}
	else
	{
		// input 1360x768 display on 1366 panel,
		// don't do sacle and get 1366 for hori. data
		if( PanelWidth == 1366 )
		{
			if( StandardModeGroup == Res_1360x768 )
				width = 1366;
			else
				width = StandardModeWidth;
		}
		else
		{
			width = StandardModeWidth;
		}
		height = SC0_READ_AUTO_HEIGHT();//msRead2Byte(SC0_82)-msRead2Byte(SC0_7E)+1; // get DE Height
		if( StandardModeGroup == Res_1152x864 )
		{
			height = 864;
		}
		else
		{
			height = StandardModeHeight;
			if (SrcFlags & bInterlaceMode) //120522
			{
				height = (StandardModeHeight + 3);
				UserPrefVStart -= 2;
			}
		}
	}
	#if ENABLE_OVER_SCAN && CHIP_ID == CHIP_TSUMU
	width &= (~BIT0);
	#endif
	#if DEBUG_PRINTDATA//DEBUG_CAPTUREWIN
	printData("CAPTUREWIN0000 height=%d", height);
	#endif
	if (DecVScaleFlag)
		height += DecVScaleValue;
	#if DEBUG_PRINTDATA//DEBUG_CAPTUREWIN
	printData("CAPTUREWIN1111 height=%d", height);
	#endif
//121228 Modify
	#if Enable_Expansion
	if (16 * GetImageHeight() == 9 * GetImageWidth() || 16 * GetImageHeight() == 10 * GetImageWidth() || ((DWORD)GetImageWidth()*PANEL_HEIGHT >= (DWORD)PANEL_WIDTH * GetImageHeight())
        #if !ENABLE_OVER_SCAN
	        || ((GetImageWidth() == PANEL_WIDTH) && (GetImageHeight() == PANEL_HEIGHT))
        #endif
	   ) //120911 Modify
		Clr_ExpansionFlag();
	else
		Set_ExpansionFlag();
	#endif
	#if 0//ENABLE_OVER_SCAN
	if(EXPANSION_MODE_IS_ASPECT() && !INPUT_IS_WILD_TIMING())// && (!INPUT_IS_NATIVE_TIMING()))	//13011422 Henry
	{
		OverScanSetting.ScanRatio = 100;
		OverScanSetting.ImageRatio = 100;
		OverScanSetting.AspRatio = OVERSCAN_4_3;
		OverScanSetting.Enable = 1;
	}
	else if(EXPANSION_MODE_IS_11() && !(INPUT_IS_NATIVE_TIMING() || (StandardModeWidth > PANEL_WIDTH) || (StandardModeHeight > PANEL_HEIGHT))) //  && (!INPUT_IS_NATIVE_TIMING()))	//13011422 Henry
	{
		OverScanSetting.ScanRatio = 100;
		OverScanSetting.ImageRatio = 0;
		OverScanSetting.AspRatio = OVERSCAN_FIXED_RATIO;
		OverScanSetting.Enable = 1;
	}
	else if(EXPANSION_MODE_IS_17())//  && (!INPUT_IS_NATIVE_TIMING())) //13011422 Henry
	{
		OverScanSetting.ScanRatio = 100;
		OverScanSetting.ImageRatio = 0;
		OverScanSetting.AspRatio = PC_SCALE_17Picth;
		OverScanSetting.Enable = 1;
	}
	else if(EXPANSION_MODE_IS_19())//  && (!INPUT_IS_NATIVE_TIMING())) //13011422 Henry
	{
		OverScanSetting.ScanRatio = 100;
		OverScanSetting.ImageRatio = 0;
		OverScanSetting.AspRatio = PC_SCALE_19Picth;
		OverScanSetting.Enable = 1;
	}
	else if(EXPANSION_MODE_IS_W19())//  && (!INPUT_IS_NATIVE_TIMING())) //13011422 Henry
	{
		OverScanSetting.ScanRatio = 100;
		OverScanSetting.ImageRatio = 0;
		OverScanSetting.AspRatio = PC_SCALE_W19Picth;
		OverScanSetting.Enable = 1;
	}
	else if(EXPANSION_MODE_IS_W21())//  && (!INPUT_IS_NATIVE_TIMING())) //13011422 Henry
	{
		OverScanSetting.ScanRatio = 100;
		OverScanSetting.ImageRatio = 0;
		OverScanSetting.AspRatio = PC_SCALE_W21_5Picth;
		OverScanSetting.Enable = 1;
	}
	else if(EXPANSION_MODE_IS_W22())//  && (!INPUT_IS_NATIVE_TIMING())) //13011422 Henry
	{
		OverScanSetting.ScanRatio = 100;
		OverScanSetting.ImageRatio = 0;
		OverScanSetting.AspRatio = PC_SCALE_W22Picth;
		OverScanSetting.Enable = 1;
	}
	else if(EXPANSION_MODE_IS_W23() )// && (!INPUT_IS_NATIVE_TIMING())) //13011422 Henry
	{
		OverScanSetting.ScanRatio = 100;
		OverScanSetting.ImageRatio = 0;
		OverScanSetting.AspRatio = PC_SCALE_W23Picth;
		OverScanSetting.Enable = 1;
	}
	else// if(EXPANSION_MODE_IS_FULL())
	{
		OverScanSetting.ScanRatio = 100;
		OverScanSetting.ImageRatio = 100;
		OverScanSetting.AspRatio = OVERSCAN_16_9;//OVERSCAN_FIXED;
		OverScanSetting.Enable = 1;
		UserprefExpansionMode = Expansion_Full;
	}
	CapWinHStart = UserPrefHStart;
	CapWinVStart = UserPrefVStart;
	if(OverScanSetting.Enable && (g_SetupPathInfo.ucSCFmtIn == SC_FMT_IN_NORMAL))
	{
		OverScanSetting.OverScanH = PanelWidth;
		OverScanSetting.OverScanV = PanelHeight;
		if( (OverScanSetting.AspRatio == OVERSCAN_4_3)
		        || (OverScanSetting.AspRatio == OVERSCAN_16_9) )
		{
			if(OverScanSetting.AspRatio == OVERSCAN_4_3)
			{
				M = 4;
				N = 3;
			}
			else if(OverScanSetting.AspRatio == OVERSCAN_16_9)
			{
				M = 16;
				N = 9;
			}
			if( ((DWORD)PanelWidth * N / M) < PanelHeight )
			{
				OverScanSetting.OverScanH = PanelWidth;
				OverScanSetting.OverScanV = ((DWORD)PanelWidth * N / M);
			}
			else
			{
				OverScanSetting.OverScanH = ((DWORD)PanelHeight * M / N);
				OverScanSetting.OverScanV = PanelHeight;
			}
			OverScanHDisp = OverScanSetting.OverScanH + OverScanSetting.ExtH;
			OverScanVDisp = OverScanSetting.OverScanV + OverScanSetting.ExtV;
			if( OverScanSetting.ExtH )
			{
				OverScanHCap = ((DWORD)width * OverScanSetting.OverScanH / OverScanHDisp);
				CapWinHStart = UserPrefHStart + (width - OverScanHCap) / 2 / DualInDivider;
				width = OverScanHCap;
			}
			if( OverScanSetting.ExtV )
			{
				OverScanVCap = ((DWORD)height * OverScanSetting.OverScanV / OverScanVDisp);
				CapWinVStart = UserPrefVStart + (height - OverScanVCap) / 2;
				height = OverScanVCap;
			}
		}
		else if(OverScanSetting.AspRatio == OVERSCAN_FIXED) //Fixed Input Aspect Ratio
		{
			if( (DWORD)PanelWidth * height >= (DWORD)PanelHeight * width )
			{
				OverScanSetting.OverScanH = ((DWORD)width * PanelHeight / height);
				OverScanSetting.OverScanV = PanelHeight;
			}
			else
			{
				OverScanSetting.OverScanH = PanelWidth;
				OverScanSetting.OverScanV = ((DWORD)height * PanelWidth / width);
			}
		}
		else if( OverScanSetting.AspRatio == OVERSCAN_FIXED_RATIO )
		{
			OverScanSetting.OverScanH = (PanelWidth > width) ? ( width + ((DWORD)(PanelWidth - width) * OverScanSetting.ImageRatio) / 100 ) : PanelWidth ;
			OverScanSetting.OverScanV = (PanelHeight > height) ? ( height + ((DWORD)(PanelHeight - height) * OverScanSetting.ImageRatio) / 100 ) : PanelHeight ;
			if(CURRENT_INPUT_IS_DISPLAYPORT())
				OverScanSetting.OverScanH = OverScanSetting.OverScanH * 2;
			OverScanHCap = ((DWORD)width * OverScanSetting.ScanRatio / 100);
			CapWinHStart = UserPrefHStart + (width - OverScanHCap) / 2 / DualInDivider;
			width = OverScanHCap;
			OverScanVCap = ((DWORD)height * OverScanSetting.ScanRatio / 100);
			CapWinVStart = UserPrefVStart + (height - OverScanVCap) / 2;
			height = OverScanVCap;
		}
		#if ENABLE_OVER_SCAN
		else if(IS_ScreenSizeMode)
		{
			XDATA DWORD PitchTempV;
			XDATA DWORD PitchTempH;
			if(OverScanSetting.AspRatio == PC_SCALE_17Picth)
			{
				PitchTempV = 2400000ul;
				PitchTempH = 3200000ul;
				//printData("############PC_SCALE_17Picth", 1);
			}
			else if(OverScanSetting.AspRatio == PC_SCALE_19Picth)
			{
				PitchTempV = 2700000ul;
				PitchTempH = 3600000ul;
				//printData("############PC_SCALE_19Picth", 1);
			}
			else if(OverScanSetting.AspRatio == PC_SCALE_W19Picth)
			{
				PitchTempV = 2551500ul;
				PitchTempH = 4082400ul;
				//printData("############PC_SCALE_W19Picth", 1);
			}
			else if(OverScanSetting.AspRatio == PC_SCALE_W21_5Picth)
			{
				PitchTempV = 2680000ul;
				PitchTempH = 4766000ul;
				//printData("############PC_SCALE_W21_5Picth", 1);
			}
			else if(OverScanSetting.AspRatio == PC_SCALE_W22Picth)
			{
				PitchTempV = 2930000ul;
				PitchTempH = 4730000ul;
				//printData("############PC_SCALE_W22Picth", 1);
			}
			else if(OverScanSetting.AspRatio == PC_SCALE_W23Picth)
			{
				PitchTempV = 2867000ul;
				PitchTempH = 5097000ul;
				//printData("############PC_SCALE_W23Picth", 1);
			}
			wTemp = PitchTempV / PanelPitch; // panel pixel pitch = mm*10000.
			wTempRatio = PanelHeight - wTemp;
			wTempRatio = (DWORD)0 * wTempRatio / 100;
			wTemp += wTempRatio;
			OverScanSetting.OverScanV = wTemp;
			wTemp = wTemp * (PitchTempH / PanelPitch) / (PitchTempV / PanelPitch); // // // panel pixel pitch = mm*10000.
			OverScanSetting.OverScanH = wTemp;
			if (OverScanSetting.OverScanH & BIT0) // H  must to even to prvent screen break.
				OverScanSetting.OverScanH += 1;
			OverScanHCap = ((DWORD)width * OverScanSetting.ScanRatio / 100);
			CapWinHStart = UserPrefHStart + (width - OverScanHCap) / 2 / DualInDivider;
			width = OverScanHCap;
			OverScanVCap = ((DWORD)height * OverScanSetting.ScanRatio / 100);
			CapWinVStart = UserPrefVStart + (height - OverScanVCap) / 2;
			height = OverScanVCap;
		}
		#endif
		width &= (~BIT0);
		#if DEBUG_CAPTUREWIN
		printData("OverScanEnable = %x", OverScanSetting.Enable);
		printData("OverScanAspRatio = %x", OverScanSetting.AspRatio);
		printData("OverScanExtH = %x", OverScanSetting.ExtH);
		printData("OverScanExtV = %x", OverScanSetting.ExtV);
		#endif
	}
	mStar_AdjustHPosition(CapWinHStart);//msWrite2Byte(SC0_07, UserPrefHStart); // set capture window hstart
	mStar_AdjustVPosition(CapWinVStart);	  // set capture window vstart
	SC0_SET_IMAGE_HEIGHT(height);//msWrite2ByteMask(SC0_09, height, SC_MASK_V);
	SC0_SET_IMAGE_WIDTH((width / DualInDivider)); //msWrite2ByteMask(SC0_0B, width, SC_MASK_H); // set capture window width according input resolution
	#else // !ENABLE_OVER_SCAN
	#if CHIP_ID == CHIP_TSUMD  //130909 nick add for TSUMXXD FRC case
	OverScanSetting.OverScanH = PanelWidth;
	OverScanSetting.OverScanV = PanelHeight;
	#if 0
	if(EXPANSION_MODE_IS_ASPECT() && !INPUT_IS_WILD_TIMING())
	{
		WORD wval;
		OverScanSetting.Enable = 1;
		OverScanSetting.OverScanV = PanelHeight;
		width = GetImageOutH(); //OverScanSetting.OverScanH = GetImageOutH();
		//wval = HStartOffset = (PanelWidth-OverScanSetting.OverScanH)/2;
		//UserPrefHStart += wval;
	}
	else
	{
		OverScanSetting.Enable = 0;
		OverScanSetting.OverScanH = PanelWidth;
		OverScanSetting.OverScanV = PanelHeight;
		HStartOffset = 0;
	}
	#endif
	if(EXPANSION_MODE_IS_ASPECT() && !INPUT_IS_WILD_TIMING())
	{
		if( ((DWORD)PanelWidth * 3 / 4) < PanelHeight )
		{
			OverScanSetting.OverScanH = PanelWidth;
			OverScanSetting.OverScanV = ((DWORD)PanelWidth * 3 / 4);
		}
		else
		{
			OverScanSetting.OverScanH = ((DWORD)PanelHeight * 4 / 3);
			OverScanSetting.OverScanV = PanelHeight;
		}
		OverScanHDisp = OverScanSetting.OverScanH + OverScanSetting.ExtH;
		OverScanVDisp = OverScanSetting.OverScanV + OverScanSetting.ExtV;
		if( OverScanSetting.ExtH )
		{
			OverScanHCap = ((DWORD)width * OverScanSetting.OverScanH / OverScanHDisp);
			CapWinHStart = UserPrefHStart + (width - OverScanHCap) / 2 / DualInDivider;
			width = OverScanHCap;
		}
		if( OverScanSetting.ExtV )
		{
			OverScanVCap = ((DWORD)height * OverScanSetting.OverScanV / OverScanVDisp);
			CapWinVStart = UserPrefVStart + (height - OverScanVCap) / 2;
			height = OverScanVCap;
		}
		width &= (~BIT0);
	}
	#endif
	mStar_AdjustHPosition(UserPrefHStart);//msWrite2Byte(SC0_07, UserPrefHStart); // set capture window hstart
	mStar_AdjustVPosition(UserPrefVStart);	  // set capture window vstart
	SC0_SET_IMAGE_HEIGHT(height);//msWrite2ByteMask(SC0_09, height, SC_MASK_V);
	SC0_SET_IMAGE_WIDTH(width);//msWrite2ByteMask(SC0_0B, width, SC_MASK_H); // set capture window width according input resolution
	#endif
	#if DEBUG_PRINTDATA//DEBUG_CAPTUREWIN
	printData("CAPTUREWIN width=%d", width);
	printData("CAPTUREWIN height=%d", height);
	#endif
	return TRUE;
}

#if CHIP_ID == CHIP_TSUM2
void PowerDownDDR(void)
{
	//DDR DTOP
	msWrite2Byte(REG_1207, 0x3250);
	msWrite2Byte(REG_1247, 0xfffe);
	ForceDelay1ms(2);
	msWrite2Byte(REG_1219, 0x0400);
	msWrite2Byte(REG_1201, 0x002f);
	msWrite2Byte(REG_1201, 0x052e);
	msWrite2Byte(REG_1201, 0x002e);
	msWrite2Byte(REG_1201, 0x032e);
	msWrite2Byte(REG_1201, 0x002e);
	ForceDelay1ms(2);
	msWrite2Byte(REG_1247, 0xffff);
	msWrite2Byte(REG_1201, 0x202e);
}
#endif


//*******************************************************************
// Function Name: mStar_SetupADC
//
// Decscription: setup ADC bandwidth/filter, clock, phase for sampling input data
//               and R/G/B gains, offsets
// caller: mSar_WriteByte(), msReadByte() in ms_rwreg.c
///
// callee: mStar_SetupMode() in mstar.c
//*******************************************************************
void mStar_SetupADC(void)
{
	WORD tempValue;
	if(SrcInputType > Input_ANALOG)
		return;
	tempValue = HFreq( SrcHPeriod );//(( DWORD )MST_CLOCK_MHZ * 10 + SrcHPeriod / 2 ) / SrcHPeriod; //calculate hfreq: round 5
	tempValue = (( DWORD )tempValue * UserPrefHTotal + 5000 ) / 10000; //dclk= hfreq * htotal
	#ifdef DADCPLLPROTECTION
	drvADC_SetModewithPLLProtection(ADC_INPUTSOURCE_RGB, tempValue, UserPrefHTotal);//(g_bInputSOGFlag ? ADC_INPUTSOURCE_YPBPR : ADC_INPUTSOURCE_RGB, tempValue, UserPrefHTotal);
	#else
	drvADC_AdjustHTotal(UserPrefHTotal);
	drvADC_SetADCModeSetting((g_bInputSOGFlag ? ADC_INPUTSOURCE_YPBPR : ADC_INPUTSOURCE_RGB), tempValue);
	#endif
	//drvADC_SetPhaseCode((UPPHASE_GET_REAL_VALUE()+1)%MAX_PHASE_VALUE); //Jison 100818 patch for phase state machine reset
	drvADC_SetPhaseCode(UserPrefPhase); //Jison 100818
	drvADC_SetupHsyncPolarity((SrcFlags & bHSyncNegative)); //Jison 100818
	// wait for checking
	drvADC_SetRGBGainCode(UserPrefAdcRedGain, UserPrefAdcGreenGain, UserPrefAdcBlueGain);
	drvADC_SetRGBOffsetCode(UserPrefAdcRedOffset, UserPrefAdcGreenOffset, UserPrefAdcBlueOffset);
	drvADC_AdjustCalDuring(32);
	//mStar_SetupClampingByMode(); //Jison 110106
	//msADC_AdjustCalDuring( 80/2 );  // unit: pixel // coding temp setting
}


#define DVI_POWER_ON()  (msWriteByteMask(REG_PM_B2, 0, BIT2|BIT3), msWrite2ByteMask(REG_290C, 0, 0xFFFF), msWrite2ByteMask(REG_29C0, 0, 0xFFFF))
#define DVI_POWER_DOWN()    (msWriteByteMask(REG_PM_B2, BIT2|BIT3, BIT2|BIT3), msWrite2ByteMask(REG_290C, 0x7FFE, 0xFFFF), msWrite2ByteMask(REG_29C0, 0xFFFF, 0xFFFF))

//*******************************************************************
// Function Name: mStar_PowerUp
//
// Decscription: Power on chip from power down mode
//
// callee: msWriteByte() in ms_rwreg.c
//
// caller: Power_PowerOnSystem() in power.c
//*******************************************************************
void mStar_PowerUp(void)
{
	#if	!(MS_PM)
	#if ENABLE_MHL
	if(!GET_MHL_CABLE_PLUGGED())
	#endif
	{
		MPLL_POWER_UP(TRUE);
		LPLL_POWER_UP(TRUE);
		MPLL_CLOCK_ADC(TRUE);
		mcuSetSystemSpeed(SPEED_NORMAL_MODE);
	}
	#endif
	#if ENABLE_MHL
	mapi_mhl_PowerCtrl(MHL_POWER_ON);
	#endif
	// 120601 coding reserved
	//mStar_IPPowerControl();	//120204 Modify
	SC0_SCALER_POWER_DOWN(BIT6, 0xFF); // power on chip from power down mode
	SC0_SCALER_RESET( GPR_B | ADCR_B ); // reset graphic port RO register
	SC0_SCALER_RESET( 0 );
	#if MS_DAC
	msAudioDACPowerDown( FALSE );
	#endif
	#if (CHIP_ID==CHIP_TSUM2)|| (CHIP_ID==CHIP_TSUMC)|| (CHIP_ID==CHIP_TSUMD) || (CHIP_ID==CHIP_TSUM9)|| (CHIP_ID==CHIP_TSUMF)
	WRITE_POWER_ON_TABLE();
	#endif
	// 120601 coding addition
	drvADC_PowerCtrl(ADC_POWER_ON);
	drvDVI_PowerCtrl(DVI_POWER_ON);
// 120531 coding addition
	#if ((FRAME_BFF_SEL == FRAME_BUFFER) || (ENABLE_RTE))&&(CHIP_ID != CHIP_TSUMF)
	msInitMemory();
	#endif
	#if ENABLE_DP_INPUT
	#if (CHIP_ID==CHIP_TSUMC)|| (CHIP_ID==CHIP_TSUMD)||(CHIP_ID == CHIP_TSUM9)||(CHIP_ID == CHIP_TSUMF)
	DPRxInit_PM();
	DPRxFastTrainingInitial();
	#endif
	#endif
}
//*******************************************************************
// Function Name: mStar_PowerDown
//
// Decscription: Power down chip
//
// callee: msWriteByte() in ms_rwreg.c
//
// caller: Power_PowerOffSystem() in power.c
//*******************************************************************
void mStar_PowerDown(void)
{
	#if TMDS_SYNC_RECHECK//20130418
	if(TMDS_INPUT_WITHOUT_HV_SYNC())
	{
		return;
	}
	#endif
	#if (((CHIP_ID == CHIP_TSUMC) || (CHIP_ID == CHIP_TSUMD) ||(CHIP_ID == CHIP_TSUM9)||(CHIP_ID == CHIP_TSUMF))&&(ENABLE_DP_INPUT))
	#if (CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)
	#if !DP_AUX_NORMAL_FRO
	DPRxSetAuxClock(FRO);
	#endif
	#endif
	DPAux_Reset();
	DPSetOffLine();
	DPRxIRQEnable(FALSE);
	msWriteByteMask( REG_2B19, ( _BIT7 ), _BIT7 );         // Disable DPISR
	#endif
	#if ENABLE_RTE // 081124 od modified
	msOverDriveOnOff( FALSE); // disable OD function , or you can set BK4_90h= 0 directly.
	#endif
	#if MS_DAC
	msAudioDACPowerDown(TRUE);
	#endif
	#if (MS_PM)	//120612 Modify
	if((ESaverPowerDownCounter != 0)
        #if ENABLE_MHL && (CHIP_ID==CHIP_TSUM2)// 120607 coding addition for VGA cannot wakeup when MHL cable plugged
	        || GET_MHL_CABLE_PLUGGED()
        #endif
	  )
		msWrite2ByteMask( REG_ADC_ATOP_04_L, 0, BIT14);
	#endif
	#if UseINT
	mStar_EnableModeChangeINT(FALSE); //Jison: for DDCCI,DVI input, reduced power off,it wake up immediately.
	#endif
	drvADC_PowerCtrl((PowerOnFlag ? ADC_POWER_STANDBY : ADC_POWER_DOWN));
	drvDVI_PowerCtrl((PowerOnFlag) ? (DVI_POWER_STANDBY) : (DVI_POWER_DOWN));
	// 120203 coding test
	//if(!PowerOnFlag)
	//    DVI_POWER_DOWN();
	#if (CHIP_ID==CHIP_TSUMC || CHIP_ID==CHIP_TSUMD)//130604 Modify
	//ComboInputControl((PowerOnFlag ? COMBO_INPUT_POWERSAVING: COMBO_INPUT_OFF));	//130607 nick
	#endif
	#if	(MS_PM)
	SC0_SCALER_POWER_DOWN( PDDS_B | BIT5 | BIT2 | 0x2 | BIT6, 0xFF ); // power down chip except mode detection
	#else
	SC0_SCALER_POWER_DOWN( PDDS_B | BIT5 | BIT2 | 0x3 | BIT6, 0xFF ); // power down chip except mode detection
	//Jison, Don't enable if use PM mode, it will cause sometime DDCCI_ID is disabled by int 0
	//if (DDCCI_FORCE_POWER_SAVE_FLAG && (SRC_INPUT_TYPE==INPUT_DVI || SRC_INPUT_TYPE==INPUT_HDMI))
	//msWriteByte(SC0_CF, BIT2); //Enable DVI clock change int 090710 // 110928 coding check with Jison
	#endif
	#if ENABLE_MHL
	mapi_mhl_PowerCtrl(PowerOnFlag ? MHL_POWER_STANDBY : MHL_POWER_DOWN);
	#endif
	#if CHIP_ID == CHIP_TSUM2
	PowerDownDDR();
	#endif
	#if	!(MS_PM)// && !ENABLE_MHL
	#if ENABLE_DP_INPUT
	#if CHIP_ID == CHIP_TSUMU
	DPRXPMForceEnter(); /* Force DP Enter Power Saving Mode */
	#endif
	#endif
	#if ENABLE_MHL
	if(!GET_MHL_CABLE_PLUGGED())
	#endif
	{
		mcuSetSystemSpeed(SPEED_XTAL_MODE);		//111012 Modify
		MPLL_POWER_UP(FALSE);
		LPLL_POWER_UP(FALSE);
		MPLL_CLOCK_ADC(FALSE);
	}
	#endif
}
//*******************************************************************
// Function Name: mStar_InitADC
//
// Decscription: Initialize ADC bank registers
//
// callee: msWriteByte() in ms_rwreg.c
//
// caller: mStar_Init() in mStar.c
//*******************************************************************
void mStar_InitADC(void)
{
	drvADC_init(FALSE);
	drvADC_ADCOffsetGainMismatchCal();
	#if _DGAIN_CAL_WITHOUT_INPUT_
	#if ENABLE_AUTO_CLOLR_WITHOUT_INPUT
	if(!FactoryAutoColorDone)
	{
		drvADC_ADCAutoGainCalwithoutInput();
		FactoryAutoColorDone = 1;
		SaveFactorySetting();
	}
	#else
	drvADC_ADCAutoGainCalwithoutInput();
	#endif
	#endif
	#if ENABLE_ADC_DITHERING	//120204 Modify
	msWriteByteMask(REG_ADC_ATOP_51_L, 0x00, 0x03); // [1:0]: enable ADCA interleve H/V dither in the normal display
	#else
	msWriteByteMask(REG_ADC_ATOP_51_L, 0x03, 0x03); // [1:0]: disable ADCA interleve H/V dither in the normal display
	#endif
	//drvADC_SetHsyncRefLevel(ADC_HSYNC_LVL_0);
}

//*******************************************************************
// Function Name: mStar_InitTCON
//
// Decscription: Initialize TCON bank registers according panel type
//
// callee: msWriteByte(), msWrite2Byte in ms_rwreg.c
//
// caller: mStar_Init() in mStar.c
//*******************************************************************
//==================================================================
extern void SetColorBoostWindow(BYTE mode);
extern void SetColorBoostWin(BYTE mode);
extern BYTE code t_MWEDLC_Linear_Table[];
extern code short t_Normal_ColorSettingTable[][3];

//*******************************************************************
// Function Name: mStar_SetUserPref
//
// Decscription: Restore user setting from NVRAM
//
// callee: msWriteByte() in ms_rwreg.c
//
// caller: mStar_SetupMode() in mStar.c
//*******************************************************************
void mStar_SetUserPref(void)
{
	#if ENABLE_RTE	//130605 william
	if(UserPrefRTEMode != OFF
        #if ENABLE_DISPLAY_UNDERSCAN
	        && !UnderScanSetting.Enable && !(g_SetupPathInfo.bFBMode)
        #endif
        #if ENABLE_DUAL_LINK
	        || ((GetVfreq() <= 85) && (!ENABLE_FREESYNC)
            #if ENABLE_120Hz_OD
	            && !(g_SetupPathInfo.wImgSizeOutH == PanelWidth &&	g_SetupPathInfo.wImgSizeOutV == PanelHeight)
            #endif
	           )//(SrcModeIndex!=MODE_1920x1080P_144Hz) //130328 Modify
        #endif
	  )
	{
		msOverDriveOnOff( TRUE );
	}
	#endif
	if (UserPrefDcrMode)
	{
		//msDlcInit( PanelWidth, PanelHeight );
		msDCROnOff(UserPrefDcrMode, MAIN_WINDOW);	//120308 Modify
		ReadColorTempSetting();
		// 091005 coding
		if(FreeRunModeFlag)
			mStar_AdjustBrightness(100);
		return ;
	}
	else
		msAccOnOff(0);
	// 091005 coding
	if(FreeRunModeFlag)
		mStar_AdjustBrightness(100);
	else
		SetECO(); //zhifeng.wu
	#if ENABLE_DeltaE
	msWriteByte(SC7_D0, 0);
	msWriteByte(SC7_D2, 0);
	SetColorTemp();// 091028 for AC OFF/OFF,Contrast error    by lizzie
	#endif
	VIDEO_AUTO_GAIN_SELECT(!IsColorspaceRGB()); //Avoid Some Video After Scaling Blanking area grean line garbge issue  20150212 alpha add
	#if CHIP_ID == CHIP_TSUMV//130306 Modify
	{
		if(UserPrefSharpness < DefSharpness || CURRENT_INPUT_IS_DVI()) //20130516 feed back Sc7_23[6] for DVI
			msAdjustSharpness( MAIN_WINDOW,  GetRealSharpness(), 1);
		else
			msAdjustSharpness( MAIN_WINDOW,  GetRealSharpness(), 0);
	}
	#else
	#if  0
	if(CURRENT_INPUT_IS_VGA())
		msAdjustSharpness( MAIN_WINDOW,  0x0C, 0);
	else
	#endif
		msAdjustSharpness( MAIN_WINDOW,  GetRealSharpness(), 0);
	#endif
	// 2006/10/16 12:39AM by Emily     mStar_InitGamma(); // programming gamma table
	// Restore other settings here
}

void SetPWMFreq(WORD freq)
{
	#if ENABLE_BRIGHTNESS_FREQ_20KHZ		//130627 xiandi
	freq = freq;
	#if ((CHIP_ID==CHIP_TSUM9 || CHIP_ID==CHIP_TSUMF) && ENABLE_XTAL_LESS)
	drvGPIO_SetPWMFreq(BrightnessPWM, 22000); //Modify DC Adjust Light 20Khz For TPV EE Request  20150930
	#else
	drvGPIO_SetPWMFreq(BrightnessPWM, 27000);
	#endif
	#else
	drvGPIO_SetPWMFreq(BrightnessPWM, freq);
	#endif
}
#if (CHIP_ID==CHIP_TSUM9) || (CHIP_ID==CHIP_TSUMF)
void msTrimFROFromEfuse(void)
{
	BYTE uctemp;
	uctemp = msEread_GetDataFromEfuse(0x0004);
	if((uctemp & BIT7) == BIT7)  // Trimming flag
	{
		msWriteByteMask(REG_018A, uctemp, 0x7F);
		g_bFROTrimResult = TRUE;
	}
	else
	{
		g_bFROTrimResult = FALSE;
	}
}

#if (ENABLE_XTAL_LESS)
//*******************************************************
//	RCOSC calibration counter.
//	If HIGH_RESOLUTION_EN = 0
//	>> TARGET frequency = REF_freq * COUNT_REPORT/ 512
//         => COUNT_REPORT = Target * 512  / REF_Freg = (OSC432M/16) * 512 / FRO12M  = 0x480
//	If HIGH_RESOLUTION_EN = 1
//	>> TARGET frequency = REF_freq * COUNT_REPORT/ 2048
//         => COUNT_REPORT = Target * 2048  / REF_Freg = (OSC432M/32) * 2048 / FRO12M = 0x900
//*******************************************************
Bool msStartRCOSC432MCal(void)
{
#define WRITE_CAL_VALUE(A)    (msWriteByteMask(REG_1ECB, A,0xFF))
#define RCOSC_HIGH_RESOLUTION_EN  0 // BIT3
#define RCOSC_COUNTER_MASK  		0xFFF
	#if RCOSC_HIGH_RESOLUTION_EN
	#if CHIP_ID==CHIP_TSUMF
#define OSC432_TARGET               0x900   //0x7C0 for 372M, 0x900 for 432M
	#else
#define OSC432_TARGET               0x7C0   //0x7C0 for 372M, 0x900 for 432M
	#endif
	#else
	#if CHIP_ID==CHIP_TSUMF
#define OSC432_TARGET               0x480   //0x3E0 for 372M, 0x480 for 432M
	#else
#define OSC432_TARGET               0x3E0   //0x3E0 for 372M, 0x480 for 432M
	#endif
	#endif
	WORD ucCounter;
	BYTE i = 0;
	msWriteByte(REG_1ECA, 0x20); //0x1E65[7:0] = 0010_0000
	msWriteByteMask(REG_01B2, 0, BIT5 | BIT6 | BIT7); //0x0159[7:5] = 000 (default)
	msWriteBit(REG_1EEB, TRUE, BIT6);//0x1E75[14] = 1 //Enable test bus output.
	msWriteByteMask(REG_1EE8, 0x13, 0x1F);//0x1E74[4:0] = 10011 // Select TEST_CLK_OUT source.
	msWriteByteMask(REG_1EEB, 0x01, 0x1F);//0x1E75[12:8] = 00001 //ckg_tstclk
	#if RCOSC_HIGH_RESOLUTION_EN
	msWriteByteMask(REG_1EEC, 0x05, 0x07); //0x1E76[2:0] = 101
	#else
	msWriteByteMask(REG_1EEC, 0x04, 0x07); //0x1E76[2:0] = 100
	#endif
	Delay1ms(99);
	do
	{
		WRITE_CAL_VALUE(i++);
		Delay1ms(1);
		msWriteByte(REG_3A80, 0x80 | RCOSC_HIGH_RESOLUTION_EN); //osc soft reset
		msWriteByte(REG_3A80, 0x03 | RCOSC_HIGH_RESOLUTION_EN); // calculate & counter one time mode enable
		while( !( msReadByte(REG_3A83) & BIT4 ) );
		ucCounter = msRead2Byte(REG_3A82)&RCOSC_COUNTER_MASK;
	}
	while(( ucCounter < OSC432_TARGET ) &&  (i < 0xF0 ));
	msWriteBit(REG_1EEB, FALSE, BIT6); //close test bus
	return (BOOL)(ucCounter >= OSC432_TARGET);
#undef WRITE_CAL_VALUE
#undef RCOSC_HIGH_RESOLUTION_EN
#undef RCOSC_COUNTER_MASK
#undef OSC432_TARGET
}
#endif
#endif


#if (CHIP_ID == CHIP_TSUMC)||(CHIP_ID == CHIP_TSUMD) ||(CHIP_ID == CHIP_TSUM9)||(CHIP_ID == CHIP_TSUM2)	||(CHIP_ID == CHIP_TSUMF) 	//130319 Modify
#if !ENABLE_MHL	//130609 bian   petit 20131010 update 	fay 20131030 add M2870VQ/M2870VHE
extern void msEread_SetMHLInitialValue(void);
extern BYTE msEread_GetHDCPKeyFromEfuse(WORD wCount);
#endif
#endif

#if (CHIP_ID == CHIP_TSUM2)
extern Bool msEread_CompareHDCPChecksumInEfuse(WORD u16Value);
extern Bool msEread_IsHDCPKeyInEfuse(void);
extern BYTE msEread_GetADCBandgapTrimValFromEfuse(void);
extern void msEread_SetComboInitialValue(void);
extern void msEread_SetHDMIInitialValue(void);
#endif

#if (CHIP_ID == CHIP_TSUMC)
extern BYTE GetVfreq( void );
#endif

#if !ENABLE_RTE
extern void msOverDriveDummy();
#endif

#if !Enable_Gamma
extern void msGammaDummy(void);
#endif
void UnUseFunc(void)		//110311 Modify for compiler warning
{
	BYTE Temp = 0;
	if(Temp)
	{
		msAdjustVideoRGB(0, 0, 0, 0);
		InitialPeaking();
		InitACEVar();
		InitDLCVar();
		#if CHIP_ID<CHIP_TSUMV	//130808 xiandi for AOC_ID07 warning
		mStar_WriteOSDByte( OSD1_77, mStar_ReadOSDByte(OSD1_77));
		#endif
		#if 1//ENABLE_RTE
		msFBDummy();
		#endif
		#if !ENABLE_RTE
		msOverDriveDummy();
		#endif
		msAdjustPCContrast(0, 0);
		#ifdef TSUMXXT
		msACESetHDTVMode(0);
		msAdjustPCRGB( 0, 0, 0, 0 );
		#endif
		msClearVersionDummy();	//130529 Nick
		#if !Enable_Gamma
		msGammaDummy();
		#endif
		#if (CHIP_ID == CHIP_TSUMC)||(CHIP_ID == CHIP_TSUMD)||(CHIP_ID == CHIP_TSUM2)	||(CHIP_ID == CHIP_TSUM9) ||(CHIP_ID == CHIP_TSUMF)	//130319 Modify
		#if !ENABLE_MHL 	//130609 bian   petit 20131010 update		fay 20131030 add M2870VQ/M2870VHE
		msEread_SetMHLInitialValue();
		msEread_GetHDCPKeyFromEfuse(0);
		#if CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF
		msEread_IsHDCPKeyInEfuse();
		msEread_SetComboInitialValue();
		#endif
		#endif
		#endif
		#if CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF//130315 Modify
		#if !ENABLE_DP_INPUT
		msdrvDPRxAppDummy();
		#endif
		#endif
		#if CHIP_ID == CHIP_TSUMD	//130315 Modify
		#if 0
		#if ENABLE_DP_INPUT
		#else
		msdrvDPRxAppDummy();
		#endif
		#endif
		#if   (1||ModelName == TSUMXXF_DEMO||ModelName==HH_TCL_DEMO_Project ||ModelName==HH_TCL_T27N1_Project||(ModelName==HH_TCL_T27N1_F_Project)\
		||ModelName==YWPK_L58CDT9_NV1|| ModelName==JRY_L58VHN_GV3|| ModelName==HKC_O587HT9_NV1|| ModelName==HKC_L58CDT9_NV1\
		|| ModelName==SPT_CNC_O38CDMT9_GV1||ModelName==SPT_CNC_JRY_L8787_BV1||ModelName==LEYI_JRY_LQ570S_BV1\
		||ModelName==JuFeng_Project||ModelName==JRY_L58CDT9_GV3||ModelName==JRY_L58CDT9_EV1||ModelName==JRY_L58CDT9_PV1\
		||(ModelName==HH_HKC_T32M8C_C_Project)||(ModelName==HH_TSY_KF270F075P_F_Project)||ModelName==JRY_L58CDT9_KV1||ModelName==JRY_L58CDT9_AV6||ModelName==HUNTKEY_F2272WHS\
		||(ModelName==HH_BOARD_DEMO_Project))//130609 bian		fay 20131030 add M2870VQ/M2870VHE
		msSWDBWriteBit(0, 0, 0);
		msEread_SetMHLInitialValue();
		#endif
		#endif
		#if(CHIP_ID == CHIP_TSUM2 && ENABLE_MHL)// 130717 william For G15 compiling warning
		mapi_mhl_SetHPD(0);
		#endif
		#if CHIP_ID >= CHIP_TSUM2	//131031 xiandi
		OSDConfGDCurveH(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		OSDConfGDCurveV(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		OSDGDCurveSelectionForWindow(0, 0, 0);
		#endif
		#if CHIP_ID == CHIP_TSUM2 || CHIP_ID == CHIP_TSUMU|| CHIP_ID == CHIP_TSUMC|| CHIP_ID == CHIP_TSUMD|| CHIP_ID == CHIP_TSUMB|| CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF//20130427//20130509
		GetLog(0);
		#endif
		#if (CHIP_ID == CHIP_TSUM2)
		msEread_CompareHDCPChecksumInEfuse(0);
		msEread_IsHDCPKeyInEfuse();
		msEread_GetADCBandgapTrimValFromEfuse();
		msEread_SetComboInitialValue();
		msEread_SetHDMIInitialValue();
		#endif
		#if (CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF)
		//BYTE u8ADCBandgapTrimVal;
		msEread_GetADCBandgapTrimValFromEfuse();
		drvGPIO_PWMAlignVSyncDelay(0, 0);
		drvGPIO_PWMInverse(0, 0);
		msDrvWriteInternalEDID(0, 0, 0);
		msDrvReadInternalEDID(0, 0);
		msTrimFROFromEfuse();
		SetSPI_Quad_En(0);
		msEread_SetHDMIInitialValue();
		#endif
		#if (CHIP_ID == CHIP_TSUMC)
		GetVfreq();
		#endif
		#if  CHIP_ID==CHIP_TSUMU
		//msAudioDPGA_SetVolume(0,0);
		msWriteWord(0, 0);
		msReadWord(0);
		#endif
	}
}

void mStar_BlackWhiteScreenCtrl(BYTE u8Ctrl)
{
	if (u8Ctrl == BW_SCREEN_WHITE)
		SC0_WHITE_SCREEN_ENABLE();//msWriteByteMask(SC0_43,BIT5,(BIT4|BIT5));
	else if (u8Ctrl == BW_SCREEN_BLACK)
		SC0_BLACK_SCREEN_ENABLE();//msWriteByteMask(SC0_43,BIT4,(BIT4|BIT5));
	else
		SC0_BLACK_WHITE_SCREEN_DISABLE();//msWriteByteMask(SC0_43,0,(BIT4|BIT5));
}

#if   1
BYTE IsColorspaceRGB(void)
{
	BYTE  ColorspaceRGB = TRUE;
	#if  ENABLE_DP_INPUT
	//if(CURRENT_INPUT_IS_DISPLAYPORT()&&(( gDPInfo.ucDPColorFormat  )!=InputColor_RGB))
	if(CURRENT_INPUT_IS_DISPLAYPORT() && DPINPUT_COLORSPACEYUV())
		ColorspaceRGB = FALSE;
	#endif
	#if ENABLE_HDMI
	//if(SrcInputType==Input_HDMI&&(gScInfo.InputColor!=InputColor_RGB))
	#if PANEL_3D_PASSIVE_4M
	if(CURRENT_INPUT_IS_HDMI())//(SrcInputType==Input_Digital)
	#else
	if(CURRENT_INPUT_IS_TMDS() && (gScInfo.InputColor != InputColor_RGB))
	#endif
		ColorspaceRGB = FALSE;
	#endif
	return  ColorspaceRGB;
}

void  SettingInputColorimetry(void)
{
	#if  ENABLE_DP_INPUT
	if(CURRENT_INPUT_IS_DISPLAYPORT() && DPINPUT_COLORIMETRY_ITU709())
		msACESetHDTVMode(YUV_Colorimetry_ITU709);
	else
	#endif
	#if ENABLE_HDMI
		if(CURRENT_INPUT_IS_HDMI() && (gScInfo.AVI_Colorimetry == YUV_Colorimetry_ITU709)) // larry 130906 for the color of window pattern is not the same in SDTV and HDTV
			msACESetHDTVMode(YUV_Colorimetry_ITU709);
		else
	#endif
			msACESetHDTVMode(YUV_Colorimetry_ITU601);
}

#endif

