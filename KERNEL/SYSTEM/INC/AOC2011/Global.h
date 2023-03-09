#include "Board.h"





#if defined(DEF_Cool_Red)
#define DefRedGain				100
#define DefGreenGain				100
#define DefBlueGain				100
#define DefRedOffset				128
#define DefGreenOffset			128
#define DefBlueOffset				128


#define DefCool_RedColor			DEF_Cool_Red
#define DefCool_GreenColor   		DEF_Cool_Green
#define DefCool_BlueColor   		DEF_Cool_Blue

#define DefNormal_RedColor   		DEF_Normall_Red
#define DefNormal_GreenColor		DEF_Normall_Green
#define DefNormal_BlueColor  		DEF_Normall_Blue

#define DefWarm_RedColor		DEF_Warml_Red
#define DefWarm_GreenColor		DEF_Warml_Green
#define DefWarm_BlueColor		DEF_Warml_Blue
#else
#define DefRedGain				100
#define DefGreenGain				100
#define DefBlueGain				100
#define DefRedOffset				128
#define DefGreenOffset			128
#define DefBlueOffset				128


#define DefCool_RedColor			110
#define DefCool_GreenColor   		110
#define DefCool_BlueColor   		110

#define DefNormal_RedColor   		120
#define DefNormal_GreenColor		120
#define DefNormal_BlueColor  		120

#define DefWarm_RedColor		130
#define DefWarm_GreenColor		130
#define DefWarm_BlueColor		130
#endif

#if 1
#define DEF_ADC_PGA_GAIN        		0
#define DEF_ADC_RED_GAIN        		1254
#define DEF_ADC_GREEN_GAIN      		1243
#define DEF_ADC_BLUE_GAIN       		1252
#define DEF_ADC_OFFSET          		(0x800-OffsetValue)
#endif


#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#include "Board.h"
#include "types.h"
#include "userprefdef.h"
#include "mode.h"

///////////////////////////////////////////////////////
#include <math.h>
#include <intrins.h>
#include "debug.h"
#include "Common.h"
#include "ms_rwreg.h"
#include "ms_reg.h"
#include "Reg52.h"
#include "misc.h"
#include "mstar.h"
#include "menudef.h"
#include "panel.h"
#include "drvadc.h"
#include "GPIO_DEF.h"
#include "i2cdef.h"
#include "halRwreg.h"
#include "drvMcu.h"
#include "drvAdjust.h"
#include "drvDDC2Bi.h"
//#include "drvPower.h" // the function moves to drvmStar
#include "drvmStar.h"
#include "msScaler.h"
#include "msfb.h"
#include "appmStar.h"
#if ENABLE_HDMI
#include "msHDMI.h"
#include "drv_msHDMI.h"
#endif
#if ENABLE_DP_INPUT
#include "drvDPRxApp.h"
#endif
#if ENABLE_SW_DOUBLE_BUFFER
#include "swdoublebuffer.h"
#endif
#if CHIP_ID==CHIP_TSUM2 ||CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD ||CHIP_ID==CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF
#if ENABLE_MHL
//#include "mapi_mhl.h"
//#include "mhal_mhl.h"
//#include "mdrv_mhl.h"
#include "DRVMHL.h"
#endif
#endif

#if ENABLE_RTE
#include "drvmsOVD.h"
#endif

#if ENABLE_FREESYNC
#include "ComboApp.h"
#endif
#if Display_Checksum			//added by draognheb for factory menu checksum on May 8th ,2011
#define   Code_checksun		FactorySetting.Code_CheckSum
#endif
#if FreeSyncSwitchEDID
extern BYTE xdata HDMI1FreeSyncED;

extern BYTE xdata HDMI2FreeSyncED;
#endif

//130909 nick add
#define V_FREQ_IN   ((SrcVFreq+5)/10)
#define IS_INPUT_VFREQ_IN_PANEL_RANGE()        (SrcVFreq >= PanelMinVfreq && SrcVFreq <= PanelMaxVfreq)
#define IS_INPUT_VFREQ_24Hz()                           (SrcVFreq >= 235 && SrcVFreq <= 245) // need this case for 60Hz panel
#define IS_INPUT_VFREQ_DOUBLE_IN_PANEL_RANGE()        ((V_FREQ_IN*2) >= (PanelMinVfreq/10) && (V_FREQ_IN*2) <= (PanelMaxVfreq/10))
#define IS_INPUT_VFREQ_TRIPLE_IN_PANEL_RANGE()        ((V_FREQ_IN*3) >= (PanelMinVfreq/10) && (V_FREQ_IN*3) <= (PanelMaxVfreq/10))
#define INPUT_TIMING_EXECUTE_FRAME_PLL_LOCK()       (!IS_INPUT_VFREQ_IN_PANEL_RANGE() && \
        (IS_INPUT_VFREQ_24Hz() || \
         IS_INPUT_VFREQ_DOUBLE_IN_PANEL_RANGE() || \
         IS_INPUT_VFREQ_TRIPLE_IN_PANEL_RANGE()))


#if CHIP_ID >= CHIP_TSUMC
#include "msEread.h"
#endif

#if !USEFLASH
#include "NVRam.h"
#endif
///////////////////////////////////////////////////////


#define CURRENT_INPUT_IS_VGA()  (SrcInputType == Input_VGA)
#define CURRENT_INPUT_IS_DVI()  (SrcInputType == Input_DVI || SrcInputType == Input_DVI2 || SrcInputType == Input_DVI3 )
#define CURRENT_INPUT_IS_HDMI() (SrcInputType == Input_HDMI || SrcInputType == Input_HDMI2 || SrcInputType == Input_HDMI3)	//120420 Modify



#define CURRENT_INPUT_IS_DISPLAYPORT() (SrcInputType == Input_Displayport || SrcInputType == Input_Displayport2 || SrcInputType == Input_Displayport3)
#define CURRENT_INPUT_IS_TMDS() (CURRENT_INPUT_IS_DVI()||CURRENT_INPUT_IS_HDMI())	//120420 Modify
#define CURRENT_INPUT_IS_HYBRID_MHL_HDMI()    (SrcInputType == Input_DVI) // MHL/HDMI
#define CURRENT_INPUT_IS_PURE_HDMI()    (SrcInputType == Input_HDMI) // MHL/HDMI
#if CHIP_ID == CHIP_TSUM2
#define MHL_CHECK_CONDITION()   (PowerOnFlag && (UserPrefInputSelectType == INPUT_PRIORITY_AUTO || UserPrefInputSelectType == INPUT_PRIORITY_DVI))
#else
#define MHL_CHECK_CONDITION()  (TRUE)
#endif

#define CURRENT_INPUT_IS_HDMI0()    (SrcInputType == Input_HDMI)
#define CURRENT_INPUT_IS_HDMI1()    (SrcInputType == Input_HDMI2)
#define CURRENT_INPUT_IS_HDMI2()    (SrcInputType == Input_HDMI3)

#define CURRENT_INPUT_IS_DVI0()    (SrcInputType == Input_DVI)
#define CURRENT_INPUT_IS_DVI1()    (SrcInputType == Input_DVI2)
#define CURRENT_INPUT_IS_DVI2()    (SrcInputType == Input_DVI3)

#if ENABLE_MHL
#if CHIP_ID == CHIP_TSUM2
#define CURRENT_INPUT_MHL_CABLE_PLUGGED()   (CURRENT_INPUT_IS_DVI() && GET_MHL_CABLE_PLUGGED())
#define IS_MHL_PORT0_CABLE_CONNECT()     (FALSE)
#define IS_MHL_PORT1_CABLE_CONNECT()     (FALSE)
#define IS_MHL_PORT2_CABLE_CONNECT()     (FALSE)
#elif CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD || CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF
#define CURRENT_INPUT_MHL_CABLE_PLUGGED()   (CurrentInputMHLCablePlugged())
#if ENABLE_MHL_C1
#define IS_MHL_PORT0_CABLE_CONNECT()    (MHL_CABLE_SAR_DETECT_PORT0 >= CBUS_CABLE_DETECT_LEVEL)
#else
#define IS_MHL_PORT0_CABLE_CONNECT()     (FALSE)
#endif

#if ENABLE_MHL_C2
#define IS_MHL_PORT1_CABLE_CONNECT()     (MHL_CABLE_SAR_DETECT_PORT1 >= CBUS_CABLE_DETECT_LEVEL)
#else
#define IS_MHL_PORT1_CABLE_CONNECT()     (FALSE)
#endif

#if ENABLE_MHL_C3
#define IS_MHL_PORT2_CABLE_CONNECT()     (MHL_CABLE_SAR_DETECT_PORT2 >= CBUS_CABLE_DETECT_LEVEL)
#else
#define IS_MHL_PORT2_CABLE_CONNECT()     (FALSE)
#endif
#endif
#else // !ENABLE_MHL
#define CURRENT_INPUT_MHL_CABLE_PLUGGED()   (FALSE)
#define IS_MHL_PORT0_CABLE_CONNECT()     (FALSE)
#define IS_MHL_PORT1_CABLE_CONNECT()     (FALSE)
#define IS_MHL_PORT2_CABLE_CONNECT()     (FALSE)
#endif



#if ENABLE_DP_INPUT
#define CURRENT_INPUT_IS_DISPLAYPORT_PortC() ((SrcInputType == Input_Displayport3))
#endif


#define INPUT_IS_VGA(InputType)  (InputType == Input_VGA)
#define INPUT_IS_DVI(InputType)  (InputType == Input_DVI || InputType == Input_DVI2 || InputType == Input_DVI3)
#define INPUT_IS_HDMI(InputType) (InputType == Input_HDMI || InputType == Input_HDMI2 || InputType == Input_HDMI3)
#define INPUT_IS_DISPLAYPORT(InputType) (InputType == Input_Displayport || InputType == Input_Displayport2 || InputType == Input_Displayport3)

#define EXPANSION_MODE_IS_FULL()    (UserprefExpansionMode == Expansion_Full)
#define EXPANSION_MODE_IS_ASPECT()	(UserprefExpansionMode == Expansion_Aspect)
#define EXPANSION_MODE_IS_11()    	(UserprefExpansionMode == Expansion_11)	//121228 Modify

#if ENABLE_OVER_SCAN
#define EXPANSION_MODE_IS_17()    	(UserprefExpansionMode == PIC_FORMAT_17Picth)	//121228 Modify
#define EXPANSION_MODE_IS_19()    	(UserprefExpansionMode == PIC_FORMAT_19Picth)	//121228 Modify
#define EXPANSION_MODE_IS_W19()    	(UserprefExpansionMode == PIC_FORMAT_W19Picth)	//121228 Modify
#define EXPANSION_MODE_IS_W21()    	(UserprefExpansionMode == PIC_FORMAT_W21_5Picth)	//121228 Modify
#define EXPANSION_MODE_IS_W22()    	(UserprefExpansionMode == PIC_FORMAT_W22Picth)	//121228 Modify
#define EXPANSION_MODE_IS_W23()    	(UserprefExpansionMode == PIC_FORMAT_W23Picth)	//121228 Modify

#define IS_ScreenSizeMode       ( OverScanSetting.AspRatio == PC_SCALE_17Picth || OverScanSetting.AspRatio == PC_SCALE_19Picth|| OverScanSetting.AspRatio == PC_SCALE_W19Picth \
                                  ||OverScanSetting.AspRatio == PC_SCALE_W21_5Picth || OverScanSetting.AspRatio == PC_SCALE_W22Picth|| OverScanSetting.AspRatio == PC_SCALE_W23Picth \
                                )

#endif


#if 0//ENABLE_OVER_SCAN
#define EXPANSION_MODE_IS_NONE()    (UserprefExpansionMode == Expansion_None)
#endif

#define INPUT_IS_WILD_TIMING()      (!ExpansionFlag)
#define INPUT_IS_NATIVE_TIMING()   	((StandardModeWidth==PANEL_WIDTH) && (StandardModeHeight==PANEL_HEIGHT))	//121228 Modify

#define COLOR_SPACE_IS_YUV()   (!IsColorspaceRGB())
#define CURRENT_SOURCE_IS_INTERLACE_MODE()  (SrcFlags & bInterlaceMode)


#define IS_DELAY_TURN_ON_PANEL		( CURRENT_INPUT_IS_HDMI() && (mstar_HDMITmdsGetType() == TMDS_HDMI) && (SrcFlags & bInterlaceMode))




// 121113 coding addition for scalar path setting
#if CHIP_ID == CHIP_TSUMU || CHIP_ID == CHIP_TSUM2||CHIP_ID == CHIP_TSUMD
#define SETUP_PATH_R2Y()  (g_SetupPathInfo.bMRWR2Y)
#else
#define SETUP_PATH_R2Y()  (FALSE)
#endif

#if ENABLE_HDMI && ENABLE_DP_INPUT || INPUT_TYPE == INPUT_1A1D1DP || INPUT_TYPE == INPUT_1A1DP//130608 xiandi
#if (CHIP_ID==CHIP_TSUMC || CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)	//130621 william
#define SETUP_PATH_RGB()    ((CURRENT_INPUT_IS_DISPLAYPORT()?(gDPInfo.ucDPColorFormat == InputColor_RGB):(InputColorFormat == INPUTCOLOR_RGB)) && !SETUP_PATH_R2Y())
#else
#define SETUP_PATH_RGB()    (InputColorFormat == INPUTCOLOR_RGB && !SETUP_PATH_R2Y())
#endif
#elif ENABLE_HDMI
#define SETUP_PATH_RGB()    (InputColorFormat == INPUTCOLOR_RGB && !SETUP_PATH_R2Y())
#else
#define SETUP_PATH_RGB()    (!SETUP_PATH_R2Y())
#endif

// 130418 coding addition

#define TMDS_SYNC_RECHECK    0   // Nick mark 20130426


#if TMDS_SYNC_RECHECK
extern BYTE xdata HsyncDisappearCounter;
extern BYTE xdata VsyncDisappearCounter;
#define SYNC_DISAPPEAR_COUNT    5
#define TMDS_INPUT_WITHOUT_HV_SYNC()    ((HsyncDisappearCounter>=SYNC_DISAPPEAR_COUNT || VsyncDisappearCounter>=SYNC_DISAPPEAR_COUNT) &&\
        DVI_DE_IS_EXIST())
#endif


/////////////////////////////////////////////////////////////////////////
#define HPeriod_Torlance    10 // for mode change
#define VTotal_Torlance     4 // 10 // for mode change	//120112 Modify

#define HFREQ_TOLERANCE_ENLARGE      150 // 15KHz
#define VFREQ_TOLERANCE_ENLARGE      100 // 10Hz

#if PANEL_WIDTH==1366&&PANEL_HEIGHT==768	//120115 Modify
#define HVStartTorlance		((StandardModeGroup==Res_1360x768)?(5):(2))
#else
#define HVStartTorlance		2
#endif

#define HFreq_Torlance     12 // 15 // 1.5 KHz
#define VFreq_Torlance     12 // 15 // 1.5 Hz
#define VTotal_Delta        50

#if ENABLE_DUAL_LINK		//121119 Modify
#ifndef MaxInputHFreq
#define MaxInputHFreq      1600 // 955 //820 // 955 // 80.0 KHz
#endif
#elif (PanelWidth==2560&&PanelHeight==1440)
#define MaxInputHFreq      950//petit 800 // 955 //820 // 955 // 80.0 KHz
#else
#ifndef	MaxInputHFreq
#define MaxInputHFreq      900//petit 800 // 955 //820 // 955 // 80.0 KHz
#endif
#endif

#if ENABLE_HDMI||ENABLE_DP_INPUT	//131105 henry
#define MinInputHFreq     140//  300//240 // 150//150 for YPbPr
#else
#define MinInputHFreq     300//  300//240 // 150//150 for YPbPr
#endif

#if 0//CHIP_ID==CHIP_TSUM2
#if ENABLE_MHL
#define MaxInputVFreq      800 //   865 //765 // 865 // 76.5 Hz
#define MinInputVFreq       280 // 410 //400 // 50.0 Hz
#else
#define MaxInputVFreq      800 //   865 //765 // 865 // 76.5 Hz
#define MinInputVFreq       490 // 410 //400 // 50.0 Hz
#endif
#else
#ifndef MaxInputVFreq
#define MaxInputVFreq      800 //   865 //765 // 865 // 76.5 Hz
#endif
#ifndef MinInputVFreq
#define MinInputVFreq       490 // 410 //400 // 50.0 Hz
#endif
#endif

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

#define xfr_regs ((BYTE xdata*)0xC000)
#define HIBYTE(value)             ((BYTE)((value) >> 8))
#define LOBYTE(value)             ((BYTE)(value))

#define   PrintAutoMsgPeriod	20//23//20//25
#define   WaitForDataBlanking     1   //zjb20071219
extern BYTE xdata g_ucTimer0_TH0;
extern BYTE xdata g_ucTimer0_TL0;
extern BYTE xdata g_u8SystemSpeedMode;
extern WORD xdata DCOffOnCounter;

extern bit   g_bInputSOGFlag;
#if ENABLE_MHL
#if CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD || CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF// demo board	// 130717 william For G15 compiling warning
extern BYTE xdata MHLExtenCountFlag; // 120529 coding addition for switching input port
#endif
#endif
#if (CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)
extern BOOL g_bFROTrimResult;
#endif


extern BYTE  xdata TI0_FLAG;
extern BYTE xdata TPDebunceCounter;

#define SKPollingInterval   50 // unit: ms
//extern bit StartScanKeyFlag;
//#define Set_StartScanKeyFlag()       (StartScanKeyFlag=1)
//#define Clr_StartScanKeyFlag()       (StartScanKeyFlag=0)

//------Eson Start-----------------------------------------
#if CHIP_ID >= CHIP_TSUM2	//120607 Modify
#define OSDMoveSpeed    5
#elif CHIP_ID == CHIP_TSUMB	//120830 Modify
#define OSDMoveSpeed    15
#else
#define OSDMoveSpeed    1
#endif
typedef enum
{
	OSDMoveType_Ini,
	OSDMoveType_Main,
	OSDMoveType_Root,
	OSDMoveType_Setting,
} OSDMoveType;

extern BYTE xdata ucPreXPos;
extern BYTE xdata ucOSDMenuMoveType;
extern BYTE xdata bMoveCURSORFlag;

#if 1//PropFontSource
//extern xdata WORD FontIndex;
//extern xdata BYTE NeedSpaceWidth;
extern xdata WORD CFontData[18];
extern WORD xdata font_shift;
extern WORD xdata font_offset;
extern WORD xdata TotalFontWidth;
extern BYTE xdata PropFontRamWidth;
extern BYTE xdata FontUsedPixel;

extern BYTE xdata font_Norm_Up_Down ; // 0: norm  , 1: half of up, 2:half of down.

#define INIT_WORD_SPACE   1
#define WORD_SPACE        1
#define FONT_COMMAND      0xFF
#endif

//=======20120814========//
#define MAX_DISPLAY_MSG_TIMES				5 // 	pixel orbiting warning msg
//=======20120814========//






#if AudioFunc

extern BYTE xdata bAudioInputStatus;

typedef enum
{
	AudioInput_Ear,    //SPK
	AudioInput_Spk,	//Earphone

} EarphoneDetStatus;

#if All_AudioDet

#define bEarphoneDetStatusChangeFlag						BIT6
#define EarphoneDetStatusChangeFlag    				(SystemFlag1&bEarphoneDetStatusChangeFlag)
#define Set_EarphoneDetStatusChangeFlag()    			(SystemFlag1|=bEarphoneDetStatusChangeFlag)
#define Clr_EarphoneDetStatusChangeFlag()    			(SystemFlag1&=~bEarphoneDetStatusChangeFlag)

#endif

#endif


#if LowBlueLightType == LowBlueLight_SharpFunc
extern xdata BYTE gTempLowBlueMode;
#endif



#if ENABLE_OSD_LowBlueLight
typedef enum
{
	LOW_BLUE_LIGHT_OFF,      // 0ff
	LOW_BLUE_LIGHT_Weak,     // 1Weak
	LOW_BLUE_LIGHT_Middle,     // 2 Middle
	#if ( LowBlueLightType==LowBlueLight_Misc_Guage)||( LowBlueLightType==LowBlueLight_Misc_Group)||( LowBlueLightType==LowBlueLight_SharpFunc)
	LOW_BLUE_LIGHT_Stronger,
	#endif
	LOW_BLUE_LIGHT_Strong,     // 3 Strong
	LOW_BLUE_LIGHT_Nums
} LOW_BLUE_LIGHT_ModeType;

#endif

//------Eson End-----------------------------------------

#if ENABLE_DP_INPUT
extern bit g_bDoDPInit;
#endif


extern bit g_bMcuPMClock;

#if AudioFunc && ENABLE_DP_INPUT
extern BYTE xdata PrevInputType;
#endif

#if sRGBIssue
extern  BYTE xdata UserPrevECOMode, UserPrevGamaMode, UserPrevDcrMode;
#endif

#if ENABLE_ExpanderIO
extern void Switch1_WriteByteMask( WORD addr, BYTE value, BYTE ucMask );
//extern BYTE Switch1_ReadByte(BYTE addr);
#endif

#if CHIP_ID == CHIP_TSUM2 || CHIP_ID == CHIP_TSUMU|| CHIP_ID == CHIP_TSUMC|| CHIP_ID == CHIP_TSUMD|| CHIP_ID == CHIP_TSUMB||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF//20130427
extern BYTE GetLog(DWORD value);
#if ENABLE_DP_INPUT&&(CHIP_ID == CHIP_TSUMC|| CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)
extern BYTE GetPow2(BYTE exp);
#endif
#endif

#if MS_DAC&&(CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)
extern WORD xdata w16DAC_DePopCounter;
extern bit bDAC_DePopCountFlag;
#define SetDAC_DePopCounter(x) ((x)?(bDAC_DePopCountFlag=0,w16DAC_DePopCounter=x,bDAC_DePopCountFlag=1):(bDAC_DePopCountFlag=0))

extern BYTE xdata w16DAC_DePopStep;
extern bit bDAC_DePopFlag ;
#endif

#if (ENABLE_DEBUG && ENABLE_TIME_MEASUREMENT)
extern WORD volatile g_u16TimeMeasurementCounter;
extern bit bTimeMeasurementFlag;
#define SetTimeMeasurementCounter(x) ((x)?(bTimeMeasurementFlag=0,g_u16TimeMeasurementCounter=x,bTimeMeasurementFlag=1):(bTimeMeasurementFlag=0))

extern WORD g_u16Time1;
extern WORD g_u16Time2;
#define INIT_TIMER()           SetTimeMeasurementCounter(0xFFFF);
#define GET_T1()                g_u16Time1=g_u16TimeMeasurementCounter
#define GET_T2()                g_u16Time2=g_u16TimeMeasurementCounter
#define PRINT_DT()              printData(" Delta T=%d",(g_u16Time1-g_u16Time2))
#define TIME_MEASURE_BEGIN()    {INIT_TIMER();GET_T1();}
#define TIME_MEASURE_END()      {GET_T2();PRINT_DT();}
#else
#define TIME_MEASURE_BEGIN()
#define TIME_MEASURE_END()
#endif



#ifdef OffPower
extern BYTE xdata ShowOffPowerWarningFlag;
#endif

extern WORD ms_Counter; // for System timer
extern BYTE xdata ModeDetectCounter;
extern WORD xdata DelayCounter;
extern bit bDelayFlag;
extern BYTE  xdata MenuPageIndex;
extern BYTE  xdata MenuItemIndex ;
extern BYTE  xdata TermBuffer ;
extern WORD xdata PanelOffOnDelayCntr;
extern bit bPanelDelayFlag;
extern BYTE xdata BackLightActiveFlag;
// extern WORD xdata TimeOutCounter; //130823 larry modfiy for WaitOutputFpllStable   // 120510 coding, addition for checking register status
extern WORD xdata u16TimeOutCounter;
extern bit bTimeOutCounterFlag;
#define SetTimOutConter(x) ((x)?(bTimeOutCounterFlag=0,u16TimeOutCounter=x,bTimeOutCounterFlag=1):(bTimeOutCounterFlag=0))



#if ESaverPowerDownFunc
extern WORD xdata ESaverPowerDownCounter;
#endif
//    extern BYTE xdata BoostTempValue;

extern BYTE xdata Second;
//extern WORD SystemFlags;	 // for system status flags
//extern BYTE System2Flags;
#if ENABLE_MHL
extern WORD xdata InputTimingStableCounter;
#else
extern BYTE xdata InputTimingStableCounter;
#endif
//extern WORD xdata SystemFlags; // for system status flags
//extern WORD  System2Flags;
//extern BYTE xdata KeypadFlags;
extern BYTE xdata PowerKeyCounter;
extern BYTE xdata SourceKeyCounter;
extern BYTE xdata OsdCounter;
extern BYTE xdata HotKeyCounter;
extern BYTE xdata PowerDownCounter;
extern BYTE xdata SwitchPortCntr;//071226
//extern BYTE PatternNo;
#ifdef OffPower            //090331 xiandi.yu Auto Off Power
#define AUTO_POWER_OFF_ACTIVE   (PowerOnFlag && UserPrefAutoPowerOff)
#if 1//130723 william For PowerSaving timer slowly  !EXT_TIMER0_1S//20130510 xiandi.yu Auto Off Power
extern BYTE xdata AutoPowerOffSTime;
#endif
extern BYTE xdata AutoPowerOffHTime;
extern BYTE xdata AutoPowerOffMTime;

#endif


#if Show_BackLightTimeValue
extern BYTE  xdata BlacklitTime_S ;
extern BYTE  xdata BlacklitTime_M ;
extern WORD xdata BlacklitTime_H;
//extern BYTE  xdata BlacklitTime_HH;
#endif

extern DWORD xdata BlackoffTime;
extern BYTE xdata gBoolVisualKey;
extern BYTE xdata gByteVisualKey;
//extern BYTE SaveIndex;
extern BYTE xdata SaveIndex;
extern BYTE xdata PatternNo;




#if Enable_ButtonKeyLongPressFunction
extern BYTE xdata g_HoldKeypadButton ;
extern BYTE xdata g_HoldKeyCounter;
#endif



/*
extern BYTE  UserPrefSubRedGain;
extern BYTE  UserPrefSubGreenGain;
extern BYTE  UserPrefSubBlueGain;
 */
//extern BYTE xdata BrightnessTemp;
//extern BYTE xdata PrevHistoValue;
#if DECREASE_V_SCALING
extern WORD  xdata DecVScaleValue; // 2006/7/5 11:45PM by Emily
#define VSTART_OFFSET  (DecVScaleValue/2)
#endif

#if PanelType==PanelCLAA156WB11A||PanelType==PanelCMON156B6L0B||PanelType==PanelBOEHT156WXB
#define VSCALE_DECVALUE	20
#else
#define VSCALE_DECVALUE	50   // 2006/7/6 0:2AM by Emily
#endif

#if 0//ENABLE_HDMI
extern BYTE xdata PreHDMIColor;
#endif

extern BYTE xdata InputColorFormat;
typedef enum
{
	INPUTCOLOR_RGB,
	INPUTCOLOR_YUV,
	INPUTCOLOR_MAX
} InputColorFormatType;



extern BYTE xdata DDC1[289];// 2017/02/20


#if	UseI2cByTableFunc
typedef enum
{
	#if VGA_Write_EEPROM
	VGA_EDID,
	#endif
	#if  DVI_Write_EEPROM
	DVI_EDID,
	#endif
	#if HDMI_Write_EEPROM
	HDMI_EDID,
	#if HDMI2_Write_EEPROM
	HDMI2_EDID,
	#endif
	#endif
	I2C_EEPROM,
	I2C_MAX
} I2CType;
#else
typedef enum I2CType_enum
{
	#if ENABLE_VGA
	VGA_EDID,
	#endif
	DVI_EDID,
	HDMI_EDID,
	HDMI2_EDID,
	I2C_EEPROM,
	I2CMAX
} I2CType;
#endif


extern BYTE EnableReadDDCType;


#if 1//def	UseVGACableReadWriteAllPortsEDID
#if !defined(ReduceDDC)
extern BYTE xdata LoadEDIDSelectPort;
#endif
typedef enum
{
	VGA1,// 0
	DVI1,// 1
	HDMI1,// 2
	DP1,// 3
	VGA2,// 4
	DVI2,// 5
	HDMI2,// 6
	DP2,// 7
	HDMI3,// 8
	HDMI4,// 9
	MHL_HDMI,// a
	MHL_HDMI2,// b
	EEPROM = 0x10,
	HDCP1,
	HDCP2,//for DP
	OSDEDIDSN,//OSD EDID Serial Number(SN)  but AOC not use
	OSDEDIDModelName,//OSD EDID Model Name but AOC not use
	PanelSettingDevice//Panel Setting
} DeviceID;	//130614 xiandi
typedef enum
{
	VGA_Port1 = BIT7,
	VGA_Port2 = BIT6,
	DVI_Port1 = BIT5,
	DVI_Port2 = BIT4,
	HDMI_Port1 = BIT3,
	HDMI_Port2 = BIT2,
	DP_Port1 = BIT1,
	DP_Port2 = BIT0,
	HDMI_Port3 = BIT7,
	HDMI_Port4 = BIT6,
	MHL_HDMI_Port1 = BIT5,
	MHL_HDMI_Port2 = BIT4,
} InputPortID;	//130614 xiandi
#endif

#if CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD ||CHIP_ID==CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF//20130110 nick

#else
#define DDC_BUFFER_LENGTH   50//MaxBufLen 50 // ddc buffer length
#endif

#define _UART_BUFFER_LENGTH_    DDC_BUFFER_LENGTH

#ifdef  UseVGACableReadWriteAllPortsEDID
extern BYTE xdata SIORxBuffer[DDC_BUFFER_LENGTH];	//20120625 updata
#else
#ifdef DATA_LENGTH_20_BYTE
extern BYTE xdata SIORxBuffer[23];
#else
extern BYTE xdata SIORxBuffer[8];
#endif
#endif
#if 0//def WH_REQUEST
#if	 defined(ReduceDDC)||(EnablePreLoadEDID)
#if ENABLE_HDMI
extern BYTE xdata DDC1[256];
#else
extern BYTE xdata DDC1[128];
#endif
#endif
#else
#ifdef ReduceDDC
extern BYTE xdata DDC1[128];
#endif
#endif
#ifdef ReduceDDC
extern bit EnCheckVccFlag;
extern BYTE xdata SystemVccDropDownCnt;
#endif

//extern xdata BYTE xfr_regs[256];
#define xfr_regs ((BYTE xdata*)0xC000)





extern BYTE xdata LanguageIndex;
extern BYTE xdata SecondTblAddr;
extern BYTE xdata HistogramNow;
extern BYTE xdata HistogramPrev;
extern BYTE xdata HistogramFlag;
extern BYTE xdata BacklightNow;
extern BYTE xdata BacklightPrev;
#if CompressPropFont
typedef WORD PropFontType;
#else
typedef struct
{
	BYTE SpaceWidth;
	WORD LineData[18];
} PropFontType;
#endif
#if ENABLE_HDCP
#if HDCPKEY_IN_Flash
extern BYTE xdata HDCPDataBuffer[6];
extern WORD xdata TCRCvalue;
#ifdef HDCP_IN_FLASH_NEW_WAY
extern BYTE xdata HDCPKeySaveIndex;//Zhifeng.wu
#endif
#endif
#endif


#if USEFLASH
extern FactorySettingType xdata FactorySetting;
#endif

#if !USEFLASH
extern FactorySettingType xdata FactorySetting;
#endif

#define BKSVDataAddr  0
#define HDCPKetAddr     5
extern InputModeType code StandardMode[];
extern InputResolutionType code StandardModeResolution[];
extern InputTimingType xdata InputTiming;
extern MonitorSettingType xdata MonitorSetting;
#if USEFLASH
extern MonitorSettingType2 xdata  MonitorSetting2;
#endif

#if (ENABLE_OVER_SCAN||CHIP_ID == CHIP_TSUMD)  //130909 nick add
extern OverScanType xdata OverScanSetting;
#endif


extern ModeSettingType xdata ModeSetting;

#if PanelminiLVDS||PANEL_VCOM_ADJUST	//110229 Modify
#if PANEL_VCOM_ADJUST			//	For Turn on panel  R/W Vcom	130311 Modify
#else
extern BYTE xdata g_bACPowerOn_CheckVCOM;
#endif
#endif

#ifndef DefBrightness
#define DefBrightness	 90
#endif
#define DefContrast	128//106//96 // 92 // 0x5c // 0x60 //32~96~160 171(0xAB)
#if (ModelName==JRY_L58VHN_GV3)
#define DefRedColor	0x74//0xAB // 96(0x60)
#define DefGreenColor	0x70//0xAB //
#define DefBlueColor	0x70//0xAB
#else
#define DefRedColor	0x80//0xAB // 96(0x60)
#define DefGreenColor	0x80//0xAB //
#define DefBlueColor	0x80//0xAB
#endif
#define DefColor		0x80//0cxAB for YCM use

#define DefHue					50
#define DefSaturation			0x80

#define DefOsdTime             10


#define MinSubContrast			55
#define MaxSubContrast			255
#if CHIP_ID ==CHIP_TSUMU
#define MinSubBrightness		94//78//55   //TPV Austin request 20130528
#define MaxSubBrightness		194//178//255
#else
#define MinSubBrightness		68//78//55
#define MaxSubBrightness		168//178//255
#endif

#define DefSubContrast			((MaxSubContrast-MinSubContrast)/2+MinSubContrast)
#define DefSubBrightness		((MaxSubBrightness-MinSubBrightness)/2+MinSubBrightness)
#define DefClearVisionSubBrightness	0x80  //130813 henry	

#if Enable_Expansion
#if WidePanel
#define DefExpansion	Expansion_Full
#else
#define DefExpansion	Expansion_Aspect  //071222
#endif
#endif


#define DefRedBlackLevel    50
#define DefGreenBlackLevel    50
#define DefBlueBlackLevel    50


//For User Brightness
#define RealMaxBrightnessValue	0xFF
#define RealMinBrightnessValue	0x4F//0x7F   petit 20130730


//For Min DCR Brightness
#if 0
#undef RealMinBrightnessValue
#define RealMinBrightnessValue	0x1F
#define RealAbsoluteMinBrightnessValue	0x00
#else
#define RealAbsoluteMinBrightnessValue	0x40 //130816 xiandi
#endif

#define LowBoundDCRRealBriRatio          30     // CCFL: 30%, LED:50%
#define RealMinDcrBrightnessValue    ((((RealMaxBrightnessValue - RealMinBrightnessValue) * LowBoundDCRRealBriRatio) / 100) + RealMinBrightnessValue)




//=======================================================================================//
// for srgb
//=======================================================================================//
#ifndef WH_REQUEST		//Fay 2013/5/27
#if BJ_REQUEST&&(PanelType==PanelAUOM240HW01V8)
#define DefsRGB_RedColor		   128	// 121	// DefWarm_RedColor
#define DefsRGB_GreenColor		126  // 128  // DefWarm_GreenColor
#define DefsRGB_BlueColor		   121	// 123	// DefWarm_BlueColor
#else
#define DefsRGB_RedColor  	DefWarm_RedColor
#define DefsRGB_GreenColor  	DefWarm_GreenColor
#define DefsRGB_BlueColor 	DefWarm_BlueColor
#endif
#endif
#define MaxContrastValue  178//156 // 152 // 160//0x80 wmz 20051017
#define MinContrastValue   78//56//36 // 32 //0x80    wmz 20051017
#define MaxColorValue	(0xFF-28)	//120204 Modify for TPV Request
#define MinColorValue	(0x00+28)	//120204 Modify for TPV Request
#define MaxBrightnessValue 100 // 160//0x80 wmz 20051017
#define MinBrightnessValue  0 //0x80    wmz 20051017
#define ClockAdjRange	100
#define DefRGBgainBase	20
#define DefContrastBase   26//48
#define MAX_VIDEO_SATURATION    0xFF
#define MIN_VIDEO_SATURATION    0
#define MAX_VIDEO_HUE           100
#define MIN_VIDEO_HUE           0
#define MaxVolume         100//74 // 79
#define MinVolume          00//24 // 26 // 27
#define MaxHStart  	((UserPrefAutoHStart>50)?(UserPrefAutoHStart+50):(2*UserPrefAutoHStart-1))  	// 110527 Modify
#define MinHStart	((UserPrefAutoHStart>50)?(UserPrefAutoHStart-50):1)

#if 0//CHIP_ID == CHIP_TSUMF
#define MaxVStart 2*UserPrefAutoVStart-8
#define MinVStart 8  // 2006/10/26 4:18PM by Emily  0
#else
// 110527 Modify
#define MaxVStart 2*UserPrefAutoVStart-1
#define MinVStart 1  // 2006/10/26 4:18PM by Emily  0
#endif

#if PANEL_WIDTH == 1280 && PANEL_HEIGHT == 1024
#define MaxClock	(StandardModeHTotal+45) //120112 Modify for TPV Request
#define MinClock	(StandardModeHTotal-45) //120112 Modify for TPV Request
#else
#define MaxClock    (StandardModeHTotal+50)	//120112 Modify for TPV Request
#define MinClock    (StandardModeHTotal-50)	//120112 Modify for TPV Request
#endif
#define MinSharpness      	0	//120105 Modify
#define DefSharpness       	5	//120105 Modify
#define MaxSharpness      	10	//120105 Modify

#define ByPassSharpness 	5//130524william Modify 3	//120601 Modify

#ifdef OffPower           //090331 xiandi.yu Auto Off Power
#define MaxAutoPowerOffTime		24
#define MinAutoPowerOffTime		0
#endif



//============================================================================================
#define MAIN_FACTORY_FONT_START		0x1D

#define PROP_FONT_START					0x63
#define MAIN_MENU_FONT_START		  	0x21
#define GuageFontStartAddr	                     0x50
#define Arrow_Left				                     0x61
#define Arrow_Right			                     0x62
#define NUM_START						0x57

#define FACTORY_NUM_START				0x03


#define UpLeft_Corner		0x2
#define UpRight_Corner		UpLeft_Corner+1
#define UPMiddle			UpLeft_Corner+2
#define DownLeft_Corner	UpLeft_Corner+3
#define DownRight_Corner	UpLeft_Corner+4
#define DownMiddle		UpLeft_Corner+5


#define E1_FRAME_01		0x08
#define E1_FRAME_02		E1_FRAME_01+1
#define E1_FRAME_03		E1_FRAME_02+1
#define E1_FRAME_04		E1_FRAME_03+1
#define E1_FRAME_05		E1_FRAME_04+1
#define E1_FRAME_06		E1_FRAME_05+1
#define E1_FRAME_07		E1_FRAME_01//E1_FRAME_06+1//E1_FRAME_06+1//E1_FRAME_01//
#define E1_FRAME_08		E1_FRAME_06+1//E1_FRAME_07+1//
#define E1_FRAME_09		E1_FRAME_08+1
#define E1_FRAME_10		E1_FRAME_09+1
#define E1_FRAME_11		E1_FRAME_10+1
#define E1_FRAME_12		E1_FRAME_11+1
#define E1_FRAME_13		E1_FRAME_12+1
#define E1_FRAME_14		E1_FRAME_13+1
#define E1_FRAME_15		E1_FRAME_14+1





#define iconx1_xpos   4// //4
#define iconx2_xpos   12// 13
#define iconx3_xpos    20 //22

#define icon1y_ypos    4//5
#define icon2y_ypos    9//10
#define icon3y_ypos    14//15


//============================================================================================
// for FactoryMenu str
//============================================================================================
#define _SPACE            0x01
#define _DASH             0x02//-

#define	_0			0x03
#define	_1			_0+1
#define	_2			_0+2
#define	_3			_0+3
#define	_4			_0+4
#define	_5			_0+5
#define	_6			_0+6
#define	_7			_0+7
#define	_8			_0+8
#define	_9			_0+9

#define	_A			0x0D
#define	_B			_A+1
#define	_C			_B+1
#define	_D			_C+1
#define	_E			_D+1
#define	_F			_E+1
#define	_G			_F+1
#define	_H			_G+1
#define	_I			_H+1
#define	_J			_I+1
#define	_K			_J+1
#define	_L			_K+1
#define	_M			_L+1
#define	_N			_M+1
#define	_O			_N+1
#define	_P			_O+1
#define	_Q			_P+1
#define	_R			_Q+1
#define	_S			_R+1
#define	_T			_S+1
#define	_U			_T+1
#define	_V			_U+1
#define	_W			_V+1
#define	_X			_W+1
#define	_Y			_X+1
#define	_Z			_Y+1

#define	_a			_Z+1
#define	_b			_a+1
#define	_c			_b+1
#define	_d			_c+1
#define	_e			_d+1
#define	_f			_e+1
#define	_g			_f+1
#define	_h			_g+1
#define	_i			_h+1
#define	_j			_i+1
#define	_k			_j+1
#define	_l			_k+1
#define	_m			_l+1
#define	_n			_m+1
#define	_o			_n+1
#define	_p			_o+1
#define	_q			_p+1
#define	_r			_q+1
#define	_s			_r+1
#define	_t			_s+1
#define	_u			_t+1
#define	_v			_u+1
#define	_w			_v+1
#define	_x			_w+1
#define	_y			_x+1
#define	_z			_y+1

#define _DOT
//============================================================================================
// for MainMenu str
//============================================================================================

#define      English_Luminace                      10,0x8A,0xFF//10, 10,0xFF  //strlen, str , strend
#define      English_Imagesetup                  11,0x8B,0xFF//11, 3,0x82,4,0x82,0xFF
#define      English_Colortemp                     10,0x8B,0xFF//10, 9,0x81,0xFF    //071225
#define      English_Colorboost                    11,0x8B,0xFF//11, 11,0xFF
#define      English_Pictureboost                 12,0x8C,0xFF//  12, 12,0xFF
#define      English_Osdsetup                       10,0x8A,0xFF//10, 8,0x81,1,0xFF
#define      English_Extra                             5, 0x85,0xFF//5,  5,0xFF
#define      English_Reset                             5,0x85,0xFF//5,  5,0xFF
#define      English_Exit                                4,0x84,0xFF//4,  4,0xFF
//============================================================================================

// current input timing information
#define SrcHPeriod		InputTiming.HPeiod
#define SrcVTotal		InputTiming.VTotal
#define SrcModeIndex		InputTiming.ModeIndex
#define SrcFlags		InputTiming.fFlags
#define SrcInputType		InputTiming.InputType
#define SrcVFreq        InputTiming.VFreq  //130909 nick add 
#if ENABLE_CHECK_TMDS_DE
#define SrcTMDSWidth    InputTiming.TMDSWidth
#define SrcTMDSHeight   InputTiming.TMDSHeight
#define SrcTMDSHStart   InputTiming.TMDSHStart
#define SrcTMDSVStart   InputTiming.TMDSVStart
#endif
//============================================================================================
// VESA Standard mode default settings
#define StandardModeWidth		GetStandardModeWidth()//StandardModeResolution[StandardModeGroup].DispWidth
#define StandardModeHeight		GetStandardModeHeight()//StandardModeResolution[StandardModeGroup].DispHeight
#define StandardModeGroup		GetStandardModeGroup()//StandardMode[SrcModeIndex].ResIndex
#define StandardModeHStart		GetStandardModeHStart()//StandardMode[SrcModeIndex].HStart
#define StandardModeVStart		GetStandardModeVStart()//StandardMode[SrcModeIndex].VStart
#define StandardModeHTotal		GetStandardModeHTotal()//StandardMode[SrcModeIndex].HTotal
#if (CHIP_ID==CHIP_TSUMU) || (CHIP_ID==CHIP_TSUM2) ||(CHIP_ID==CHIP_TSUMC)||(CHIP_ID==CHIP_TSUMD)
#define StandardModeVTotal      GetStandardModeVTotal()
#endif
//#define StandardModeHFreq		GetStandardModeHFreq()
#define StandardModeVFreq		GetStandardModeVFreq()//StandardMode[SrcModeIndex].VFreq
//============================================================================================

#if 0//EnablePanelServiceMenu

#define bPanelColorDepth					BIT0//0->6bit+FRC						1->8Bit
#define bChangeModePanelVddOff			BIT1//0->Change Mode Panel Vdd On		1->Change Mode Panel Vdd Off

//#define PanelDither   			(PanelSetting.DitherTpye)
#define PanelSettingFlag   		(PanelSetting.SettingFlag)

#define PanelOnTiming1		(PanelSetting.OnTiming1)
#define PanelOnTiming2		(PanelSetting.OnTiming2)
#define PanelOffTiming1		(PanelSetting.OffTiming1)
#define PanelOffTiming2		(PanelSetting.OffTiming2)



#define PanelHSyncWidth		(PanelSetting.HsyncWidth)
#define PanelHSyncBackPorch	(PanelSetting.HSyncBackPorch)
#define PanelVSyncWidth		(PanelSetting.VSyncWidth)
#define PanelVSyncBackPorch	(PanelSetting.VsyncBackPorch)
#define PanelWidth			(PanelSetting.Width)
#define PanelHeight		(PanelSetting.Height)
#define PanelHTotal		(PanelSetting.HTotal)
#define PanelVTotal		(PanelSetting.VTotal)
#define PanelMaxHTotal	(PanelSetting.MaxHTotal)
#define PanelMinHTotal		(PanelSetting.MinHTotal)
//#define PanelMaxVTotal		(PanelSetting.MaxVTotal)
//#define PanelMinVTotal		(PanelSetting.MinVTotal)


#define PanelDCLK			(PanelSetting.TypicalDCLK)
#define PanelMaxDCLK		(PanelSetting.MaxDCLK)
#define PanelMinDCLK		(PanelSetting.MinDCLK)
#define PanelLVDSSwing	(PanelSetting.Swing)

#define PanelOutputControl1	(PanelSetting.OutputControl1)
#define PanelOutputControl2	(PanelSetting.OutputControl2)
//#define PanelOSContol		(PanelSetting.OSContol)
//#define PanelODRriving		(PanelSetting.ODRriving)

#define PanelBurstModeFreq		(PanelSetting.BurstModeFreq)
#define PanelDefDuty		(PanelSetting.DefDuty)
#define PanelMinDuty		(PanelSetting.MinDuty)
#define PanelMaxDuty		(PanelSetting.MaxDuty)

#define PanelSSCSTEPL		(PanelSetting.SSCSTEPL)
#define PanelSSCSTEPH		(PanelSetting.SSCSTEPH)
#define PanelSSCSPANL		(PanelSetting.SSCSPANL)
#define PanelSSCSPANH		(PanelSetting.SSCSPANH)

#define PanelPanelTypeNum	(PanelSetting.PanelTypeNum)


#define PanelHStart		(PanelHSyncWidth+PanelHSyncBackPorch)
#define PanelVStart		(PanelVSyncWidth+PanelVSyncBackPorch)

#define MaxPanelOnTiming1		100
#define MaxPanelOnTiming2		1000
#define MaxPanelOffTiming1	1000
#define MaxPanelOffTiming2	100

#define MaxPanelHSyncWidth		255
#define MaxPanelHSyncBackPorch	255
#define MaxPanelVSyncWidth		255
#define MaxPanelVSyncBackPorch	255

#define MinBurstModeFreqValue			219//100
#define MaxBurstModeFreqValue		600

#define MinDutyValue			0
#define MaxDutyValue			255

#define MinSwingValue			0
#define MaxSwingValue			0x1F
#define MinSwingAutoTuneValue			0
#define MaxSwingAutoTuneValue		0x3

#endif


#if USEFLASH
#if 1
// Monitor Setting
#define MonitorFlags			          MonitorSetting.MonitorFlag
#if 0//def WH_REQUEST
#define MonitorFlags1		MonitorSetting.MonitorFlag1
#endif
#define UserPrefColorTemp		    MonitorSetting.ColorTemp
#define UserPrefBrightness 	 	   MonitorSetting.Brightness
#define UserPrefContrast 		         MonitorSetting.Contrast

#if PresetMode_Enable
#define UserPrefColorTemp_Preset		    MonitorSetting.Preset_ColorTemp
#define UserPrefBrightness_Preset 	 	   MonitorSetting.Preset_Brightness
#define UserPrefContrast_Preset 		         MonitorSetting.Preset_Contrast
#define UserPrefGamaMode_Preset   	    	MonitorSetting.Preset_GamaMode
#endif

#define UserPrefBrightnessUser 	 	   MonitorSetting.BrightnessUser
#define UserPrefContrastUser 		         MonitorSetting.ContrastUser

#define UserPrefRedColor 		         MonitorSetting.RedColor
#define UserPrefGreenColor 		  MonitorSetting.GreenColor
#define UserPrefBlueColor 		        MonitorSetting.BlueColor
#if  Enable_YCM_Mode
#define UserPrefYColor		        MonitorSetting.YColor
#define UserPrefCColor		 MonitorSetting.CColor
#define UserPrefMColor		       MonitorSetting.MColor
#endif
#define UserPrefRedColorUser		         MonitorSetting.RedColorUser
#define UserPrefGreenColorUser		  MonitorSetting.GreenColorUser
#define UserPrefBlueColorUser		        MonitorSetting.BlueColorUser
#define UserPrefGamaMode   	    MonitorSetting.GamaMode
#if ENABLE_RTE
#define UserPrefRTEMode            MonitorSetting.RTEMode
#endif
#define UserPrefVolume		   MonitorSetting.Volume
#define UserPrefMuteState		   MonitorSetting.MuteState
#define UserPrefECOMode		  MonitorSetting.ECOMode
#define UserPrefLanguage		  MonitorSetting.Language
#define UserPrefOsdHStart	  MonitorSetting.OsdHStart
#define UserPrefOsdVStart		  MonitorSetting.OsdVStart
#define UserPrefOsdTime		  MonitorSetting.OsdTime
#define UserPrefOsdTrans         MonitorSetting.OsdTrans
#ifdef OffPower         //090331 xiandi.yu Auto Off Power
#define UserPrefAutoPowerOff    MonitorSetting.AutoPowerOff
#endif


#define UserPrefInputType		   MonitorSetting.InputType
#define UserPrefInputSelectType		   MonitorSetting.InputSelectType
#define UserPrefSavedModeIndex	MonitorSetting.SavedModeIndex // current mode index can be used
#if ENABLE_FACTORY_BLACKLEVEL  ||   ENABLE_DDCCI_BLACKLEVEL
#define UserprefRedBlackLevel			MonitorSetting.RedBlackLevel
#define UserprefGreenBlackLevel				MonitorSetting.GreenBlackLevel
#define UserprefBlueBlackLevel				MonitorSetting.BlueBlackLevel
#endif

#define UserPrefDcrMode   	    MonitorSetting.DcrMode

#if MWEFunction
#define UserPrefHue					MonitorSetting.Hue
#define UserPrefSaturation		       MonitorSetting.Saturation
#define UserPrefSubContrast		       MonitorSetting.SubContrast
#define UserPrefSubBrightness	              MonitorSetting.SubBrightness
#endif
#define UserPrefSharpness	   MonitorSetting.Sharpness

#if Enable_Expansion
#define UserprefExpansionMode        MonitorSetting.ExpansionMode
#endif



//#define MonitorBackLightTime				MonitorSetting.BackLightTime
// #define MonitorBackLightTime  MonitorSetting2.Backlighttime
#if Show_BackLightTimeValue
#define MonitorBackLightTime_S   MonitorSetting2.BacklighttimeS
#define MonitorBackLightTime_M  MonitorSetting2.BacklighttimeM
#define MonitorBackLightTime_H  MonitorSetting2.BacklighttimeH
#endif
#endif

#define UserPrefAdcPgaGain              FactorySetting.AdcPgaGain
#define UserPrefAdcRedGain		FactorySetting.AdcRedGain
#define UserPrefAdcGreenGain		FactorySetting.AdcGreenGain
#define UserPrefAdcBlueGain		FactorySetting.AdcBlueGain
#define UserPrefAdcRedOffset		FactorySetting.AdcRedOffset
#define UserPrefAdcGreenOffset	FactorySetting.AdcGreenOffset
#define UserPrefAdcBlueOffset		FactorySetting.AdcBlueOffset
#define UserPrefRedColorWarm1	  FactorySetting.RedColorWarm1
#define UserPrefGreenColorWarm1	  FactorySetting.GreenColorWarm1
#define UserPrefBlueColorWarm1	 FactorySetting.BlueColorWarm1
#if CT_7500K_ENABLE
#define UserPrefRedColorNormal	  FactorySetting.RedColorNormal
#define UserPrefGreenColorNormal   FactorySetting.GreenColorNormal
#define UserPrefBlueColorNormal	  FactorySetting.BlueColorNormal
#endif
#define UserPrefRedColorCool1		 FactorySetting.RedColorCool1

#define UserPrefGreenColorCool1	 FactorySetting.GreenColorCool1
#define UserPrefBlueColorCool1	 FactorySetting.BlueColorCool1
#define UserPrefRedColorSRGB		FactorySetting.RedColorsRGB
#define UserPrefGreenColorSRGB    FactorySetting.GreenColorsRGB
#define UserPrefBlueColorSRGB      FactorySetting.BlueColorsRGB
#define FUserPrefBrightnessWarm1	  FactorySetting.FBrightnessWarm1
#define FUserPrefContrastWarm1	  FactorySetting.FContrastWarm1
#define FUserPrefBrightnessNormal	  FactorySetting.FBrightnessNormal
#define FUserPrefContrastNormal	  FactorySetting.FContrastNormal
#define FUserPrefBrightnessCool1	  FactorySetting.FBrightnessCool1
#define FUserPrefContrastCool1	        FactorySetting.FContrastCool1
#define FUserPrefBrightnessSRGB	        FactorySetting.FBrightnesssRGB
#define FUserPrefContrastSRGB	        FactorySetting.FContrastsRGB
#if PanelminiLVDS ||PANEL_VCOM_ADJUST	//110229 Modify
#define UserPrefVcomValue       FactorySetting.VcomValue
#endif
#define UserPrefLogoON  FactorySetting.LogoON	//120420 Modify
#if USEFLASH
#define FactoryProductModeValue	        FactorySetting.ProductModeValue
#endif
#define FactoryCheckSum	        FactorySetting.CheckSum




#else



#if 1
// Monitor Setting
#define MonitorFlags                      MonitorSetting.MonitorFlag
#if 0//def WH_REQUEST
#define MonitorFlags1		MonitorSetting.MonitorFlag1
#endif
#define UserPrefColorTemp           MonitorSetting.ColorTemp
#define UserPrefBrightness         MonitorSetting.Brightness
#define UserPrefContrast                 MonitorSetting.Contrast

#define UserPrefRedColor                 MonitorSetting.RedColor
#define UserPrefGreenColor        MonitorSetting.GreenColor
#define UserPrefBlueColor               MonitorSetting.BlueColor
#define UserPrefYColor              MonitorSetting.YColor
#define UserPrefCColor       MonitorSetting.CColor
#define UserPrefMColor             MonitorSetting.MColor

#define UserPrefRedColorUser                 MonitorSetting.RedColorUser
#define UserPrefGreenColorUser        MonitorSetting.GreenColorUser
#define UserPrefBlueColorUser               MonitorSetting.BlueColorUser
#define UserPrefGamaMode        MonitorSetting.GamaMode
#if ENABLE_RTE
#define UserPrefRTEMode            MonitorSetting.RTEMode
#endif
#define UserPrefVolume         MonitorSetting.Volume
#define UserPrefMuteState		   MonitorSetting.MuteState
#define UserPrefECOMode       MonitorSetting.ECOMode
#define UserPrefLanguage          MonitorSetting.Language
#define UserPrefOsdHStart     MonitorSetting.OsdHStart
#define UserPrefOsdVStart         MonitorSetting.OsdVStart
#define UserPrefOsdTime       MonitorSetting.OsdTime
#define UserPrefOsdTrans         MonitorSetting.OsdTrans
#ifdef OffPower         //090331 xiandi.yu Auto Off Power
#define UserPrefAutoPowerOff    MonitorSetting.AutoPowerOff
#endif


#define UserPrefInputType          MonitorSetting.InputType
#define UserPrefInputSelectType        MonitorSetting.InputSelectType
#define UserPrefSavedModeIndex  MonitorSetting.SavedModeIndex // current mode index can be used
#define UserprefRedBlackLevel           MonitorSetting.RedBlackLevel
#define UserprefGreenBlackLevel             MonitorSetting.GreenBlackLevel
#define UserprefBlueBlackLevel              MonitorSetting.BlueBlackLevel
#define UserPrefDcrMode         MonitorSetting.DcrMode


#if MWEFunction
#define UserPrefHue                 MonitorSetting.Hue
#define UserPrefSaturation             MonitorSetting.Saturation
#define UserPrefSubContrast            MonitorSetting.SubContrast
#define UserPrefSubBrightness                 MonitorSetting.SubBrightness
#endif
#define UserPrefSharpness      MonitorSetting.Sharpness

#if Enable_Expansion
#define UserprefExpansionMode        MonitorSetting.ExpansionMode
#endif



#if Show_BackLightTimeValue
#define MonitorBackLightTime_S   MonitorSetting.BacklighttimeS
#define MonitorBackLightTime_M  MonitorSetting.BacklighttimeM
#define MonitorBackLightTime_H  MonitorSetting.BacklighttimeH
#endif
#endif

#define UserPrefAdcPgaGain              FactorySetting.AdcPgaGain
#define UserPrefAdcRedGain      FactorySetting.AdcRedGain
#define UserPrefAdcGreenGain        FactorySetting.AdcGreenGain
#define UserPrefAdcBlueGain     FactorySetting.AdcBlueGain
#define UserPrefAdcRedOffset        FactorySetting.AdcRedOffset
#define UserPrefAdcGreenOffset  FactorySetting.AdcGreenOffset
#define UserPrefAdcBlueOffset       FactorySetting.AdcBlueOffset
#define UserPrefRedColorWarm1     FactorySetting.RedColorWarm1
#define UserPrefGreenColorWarm1   FactorySetting.GreenColorWarm1
#define UserPrefBlueColorWarm1   FactorySetting.BlueColorWarm1
#define UserPrefRedColorNormal    FactorySetting.RedColorNormal
#define UserPrefGreenColorNormal   FactorySetting.GreenColorNormal
#define UserPrefBlueColorNormal   FactorySetting.BlueColorNormal
#define UserPrefRedColorCool1        FactorySetting.RedColorCool1
#define UserPrefGreenColorCool1  FactorySetting.GreenColorCool1
#define UserPrefBlueColorCool1   FactorySetting.BlueColorCool1
#define UserPrefRedColorSRGB        FactorySetting.RedColorsRGB
#define UserPrefGreenColorSRGB    FactorySetting.GreenColorsRGB
#define UserPrefBlueColorSRGB      FactorySetting.BlueColorsRGB
#define FUserPrefBrightnessWarm1      FactorySetting.FBrightnessWarm1
#define FUserPrefContrastWarm1    FactorySetting.FContrastWarm1
#define FUserPrefBrightnessNormal     FactorySetting.FBrightnessNormal
#define FUserPrefContrastNormal   FactorySetting.FContrastNormal
#define FUserPrefBrightnessCool1      FactorySetting.FBrightnessCool1
#define FUserPrefContrastCool1          FactorySetting.FContrastCool1
#define FUserPrefBrightnessSRGB         FactorySetting.FBrightnesssRGB
#define FUserPrefContrastSRGB           FactorySetting.FContrastsRGB
#if PanelminiLVDS ||PANEL_VCOM_ADJUST   //110229 Modify
#define UserPrefVcomValue       FactorySetting.VcomValue
#endif
#define UserPrefLogoON  FactorySetting.LogoON	//120420 Modify
#define FactoryProductModeValue         FactorySetting.ProductModeValue
#define FactoryCheckSum         FactorySetting.CheckSum


#endif


#if ENABLE_AUTO_CLOLR_WITHOUT_INPUT
#define FactoryAutoColorDone        FactorySetting.ADC_AUTO_COLOR_DONE
#endif



#if ENABLE_FREESYNC
#define UserprefFreeSyncMode        MonitorSetting.FreeSyncMode
#endif

#if ENABLE_OSD_LowBlueLight
#define UserprefLowBlueLightMode		MonitorSetting.LowBlueLightMode
#endif


//============================================================================================
// current input timing setting
#define UserPrefHTotal			ModeSetting.HTotal
#define UserPrefHStart			ModeSetting.HStart
#define UserPrefVStart			ModeSetting.VStart
#define UserPrefPhase			ModeSetting.Phase
#define UserPrefAutoHStart		ModeSetting.AutoHStart
#define UserPrefAutoVStart		ModeSetting.AutoVStart	//2004/01/15 num11
#define UserPrefAutoTimes		ModeSetting.AutoTimes
//======================================================================================
#define SyncLoss				(bHSyncLoss|bVSyncLoss)
#define SyncPolarity(status)	(status&0x03)
#define GetSyncPolarity(status)	(1<<(status&0x03))
//=================================================================================
// Input Timing information flags
#define SyncLossState()			(SrcFlags&SyncLoss)
#define UserModeFlag			(SrcFlags&bUserMode)
#define UnsupportedModeFlag		(SrcFlags&bUnsupportMode)
#define NativeModeFlag			(SrcFlags&bNativeMode)
#define ShrinkModeFlag			(SrcFlags&bShrinkMode)
//==================================================================================
// Monitor status flags for storing into NVRAM
#define bPowerOnBit				BIT0	// system power on/off status
#define bFactoryModeBit			BIT1	// factory mode
#define bBurninModeBit			BIT2	// burnin mode
#define bDoBurninModeBit		BIT3


#define bOverDriveOnBit			BIT6
#define bDCCCIONOBit			BIT7
//========= flags status
#define PowerOnFlag				(MonitorFlags&bPowerOnBit)
#define FactoryModeFlag			(MonitorFlags&bFactoryModeBit)
#define BurninModeFlag			(MonitorFlags&bBurninModeBit)
#define DoBurninModeFlag		(MonitorFlags&bDoBurninModeBit)




#define OverDriveOnFlag 		(MonitorFlags&bOverDriveOnBit)
#define DDCciFlag            	(MonitorFlags&bDCCCIONOBit)
//--------- flags setting
#define Set_PowerOnFlag()		(MonitorFlags|=bPowerOnBit)
#define Set_FactoryModeFlag()	(MonitorFlags|=bFactoryModeBit)
#define Set_BurninModeFlag()	(MonitorFlags|=bBurninModeBit)
#define Set_DoBurninModeFlag()  (MonitorFlags|=bDoBurninModeBit)


#define Set_OverDriveOnFlag() 	(MonitorFlags|=bOverDriveOnBit)
#define Set_DDCciFlag()			(MonitorFlags|=bDCCCIONOBit)
#define Clr_PowerOnFlag()		(MonitorFlags&=~bPowerOnBit)
#define Clr_FactoryModeFlag()	(MonitorFlags&=~bFactoryModeBit)
#define Clr_BurninModeFlag()	(MonitorFlags&=~bBurninModeBit)
#define Clr_DoBurninModeFlag() 	(MonitorFlags&=~bDoBurninModeBit)


#define Clr_OverDriveOnFlag() 	(MonitorFlags&=~bOverDriveOnBit)
#define Clr_DDCciFlag()			(MonitorFlags&=~bDCCCIONOBit)

#if VGA_Write_EEPROM
#define bLoad_VGAEDIDBit         			BIT8
#define Load_VGAEDID_Flag				(MonitorFlags&bLoad_VGAEDIDBit)
#define Set_Load_VGAEDID_Flag() 		(MonitorFlags|=bLoad_VGAEDIDBit)
#define Clr_Load_VGAEDID_Flag()   		(MonitorFlags&=~bLoad_VGAEDIDBit)
#endif

#if DVI_Write_EEPROM
#define bLoad_DVIEDIDBit					BIT9
#define Load_DVIIEDID_Flag				(MonitorFlags&bLoad_DVIEDIDBit)
#define Set_Load_DVIEDID_Flag()  		(MonitorFlags|=bLoad_DVIEDIDBit)
#define Clr_Load_DVIEDID_Flag()   		(MonitorFlags&=~bLoad_DVIEDIDBit)
#endif

#if HDMI_Write_EEPROM
#define bLoad_HDMIEDIDBit				BIT10
#define Load_HDMIEDID_Flag				(MonitorFlags&bLoad_HDMIEDIDBit)
#define Set_Load_HDMIEDID_Flag()  		(MonitorFlags|=bLoad_HDMIEDIDBit)
#define Clr_Load_HDMIEDID_Flag()   		(MonitorFlags&=~bLoad_HDMIEDIDBit)
#endif

#if HDMI2_Write_EEPROM
#define bLoad_HDMI2EDIDBit				BIT11
#define Load_HDMI2EDID_Flag			(MonitorFlags&bLoad_HDMI2EDIDBit)
#define Set_Load_HDMI2EDID_Flag()  		(MonitorFlags|=bLoad_HDMI2EDIDBit)
#define Clr_Load_HDMI2EDID_Flag()   		(MonitorFlags&=~bLoad_HDMI2EDIDBit)
#endif

#if WriteSN_Functiom_New
#define bDDCCIReadLoadEDIDBit					BIT12
#define DDCCIReadLoadEDIDFlag					(MonitorFlags&bDDCCIReadLoadEDIDBit)
#define Set_DDCCIReadLoadEDIDFlag()				(MonitorFlags|=bDDCCIReadLoadEDIDBit)
#define Clr_DDCCIReadLoadEDIDFlag()				(MonitorFlags&=~bDDCCIReadLoadEDIDBit)
#endif

#if Enable_DDCCI_OSDEnable_EN
#define bDDCOSDDisEnableBit							BIT13
#define DDCOSDDisEnableFlag						(MonitorFlags&bDDCOSDDisEnableBit)
#define Set_DDCOSDDisEnableFlag()				(MonitorFlags|=bDDCOSDDisEnableBit)
#define Clr_DDCOSDDisEnableFlag()				(MonitorFlags&=~bDDCOSDDisEnableBit)
#endif



//==================================================================================
//====================MonitorFlags1===========================================//add by lwj 120828
#if 0//def WH_REQUEST
#if EnablePreLoadEDID
#define bAEdidAlreadyFlag		BIT0
#define bDEdidAlreadyFlag		BIT1
#define bHEdidAlreadyFlag		BIT2

#define AEdidIsAlreadyFlag	(MonitorFlags1&bAEdidAlreadyFlag)
#define Set_AEdidIsAlreadyFlag() (MonitorFlags1|=bAEdidAlreadyFlag)
#define Clr_AEdidIsAlreadyFlag() (MonitorFlags1&=~bAEdidAlreadyFlag)

#define DEdidIsAlreadyFlag	(MonitorFlags1&bDEdidAlreadyFlag)
#define Set_DEdidIsAlreadyFlag() (MonitorFlags1|=bDEdidAlreadyFlag)
#define Clr_DEdidIsAlreadyFlag() (MonitorFlags1&=~bDEdidAlreadyFlag)

#define HEdidIsAlreadyFlag	(MonitorFlags1&bHEdidAlreadyFlag)
#define Set_HEdidIsAlreadyFlag() (MonitorFlags1|=bHEdidAlreadyFlag)
#define Clr_HEdidIsAlreadyFlag() (MonitorFlags1&=~bHEdidAlreadyFlag)
#endif
#endif



extern BYTE xdata SystemFlag1;
extern BYTE xdata Sytstemflag2;        //2012.08.14 Stone.yu
extern BYTE xdata Sytstemflag3;        //2012.08.14 Stone.yu
extern BYTE xdata SystemFlags;

#if ColorTool_Clear_Time

#define bDDCCIAutoColorBit              BIT0
#define DDCCIAutoColorFlag              (SystemFlags&bDDCCIAutoColorBit)
#define Set_DDCCIAutoColorFlag()	    (SystemFlags|=bDDCCIAutoColorBit)
#define Clr_DDCCIAutoColorFlag()	    (SystemFlags&=~bDDCCIAutoColorBit)


#define bDDCCResetTimeBit              BIT1
#define DDCCResetTimeFlag               (SystemFlags&bDDCCResetTimeBit)
#define Set_DDCCResetTimeFlag()	    (SystemFlags|=bDDCCResetTimeBit)
#define Clr_DDCCResetTimeFlag()	    (SystemFlags&=~bDDCCResetTimeBit)

#endif

#if JRY_Color_Tool_Functing
#define bATEModeBit					BIT2
#define ATEModeFlag					(SystemFlags&bATEModeBit)
#define Set_ATEModeFlag()			(SystemFlags|=bATEModeBit)
#define Clr_ATEModeFlag()			(SystemFlags&=~bATEModeBit)
#endif

#if JRY_FDDCCI_WriteEDID
#define bDDCCIReadLoadEDIDBit					BIT3
#define DDCCIReadLoadEDIDFlag					(SystemFlags&bDDCCIReadLoadEDIDBit)
#define Set_DDCCIReadLoadEDIDFlag()				(SystemFlags|=bDDCCIReadLoadEDIDBit)
#define Clr_DDCCIReadLoadEDIDFlag()				(SystemFlags&=~bDDCCIReadLoadEDIDBit)
#endif


#if EANBLE_NEW_DCR_Functing

extern BYTE xdata DCR_Counter;
extern BYTE xdata DCRStepTransCnt;

#define ClearBalclightStartBit							BIT4
#define EanbleClearBalclightStartFlag					(SystemFlags&ClearBalclightStartBit)
#define Set_EanbleClearBalclightStartFlag()				(SystemFlags|=ClearBalclightStartBit)
#define Clr_EanbleClearBalclightStartFlag()				(SystemFlags&=~ClearBalclightStartBit)

#define DoClearBalclightBit						BIT5
#define DoClearBalclightFlag						(SystemFlags&DoClearBalclightBit)
#define Set_DoClearBalclightFlag()					(SystemFlags|=DoClearBalclightBit)
#define Clr_DoClearBalclightFlag()					(SystemFlags&=~DoClearBalclightBit)

#endif

#if LoadAllPortSeriealnumberByOneVGAPort
#define bDDCCOneVGAPortLoadEDIDBit					BIT7
#define DDCCOneVGAPortLoadEDIDFlag					(SystemFlags&bDDCCOneVGAPortLoadEDIDBit)
#define Set_DDCCOneVGAPortLoadEDIDFlag()				(SystemFlags|=bDDCCOneVGAPortLoadEDIDBit)
#define Clr_DDCCOneVGAPortLoadEDIDFlag()				(SystemFlags&=~bDDCCOneVGAPortLoadEDIDBit)
#endif

#if Enable_CheckVcc5V
#define bCheckVcc5V						BIT6
#define CheckVcc5VFlag    				(Sytstemflag2&bCheckVcc5V)
#define Set_CheckVcc5VFlag()    			(Sytstemflag2|=bCheckVcc5V)
#define Clr_CheckVcc5VFlag()    			(Sytstemflag2&=~bCheckVcc5V)
#endif


//--> change to SystemFlag1 for reduce data size
#define  bDebugOnlyFlag      BIT0
#define  bMainOSDFlag          BIT1
#define  bSubOSDFlag            BIT2
#define  bPowerKeyFlag         BIT3
#define  bPowerOffFlag          BIT4
#define  bDoAutoConfigFlag   BIT5

#define  bDoKeyCountFlag      BIT7


#define DebugOnlyFlag				(SystemFlag1&bDebugOnlyFlag)
#define MainOSDFlag				(SystemFlag1&bMainOSDFlag)
#define SubOSDFlag				(SystemFlag1&bSubOSDFlag)
#define PowerKeyFlag				(SystemFlag1&bPowerKeyFlag)
#define PowerOffFlag				(SystemFlag1&bPowerOffFlag)
#define DoAutoConfigFlag				(SystemFlag1&bDoAutoConfigFlag)

#define DoKeyCountFlag				(SystemFlag1&bDoKeyCountFlag)

#define Set_DebugOnlyFlag()		(SystemFlag1|=bDebugOnlyFlag)
#define Clr_DebugOnlyFlag()		(SystemFlag1&=~bDebugOnlyFlag)
#define Set_MainOSDFlag()		(SystemFlag1|=bMainOSDFlag)
#define Clr_MainOSDFlag()		(SystemFlag1&=~bMainOSDFlag)
#define Set_SubOSDFlag()		        (SystemFlag1|=bSubOSDFlag)
#define Clr_SubOSDFlag()		        (SystemFlag1&=~bSubOSDFlag)

#define Set_PowerKeyFlag()		        (SystemFlag1|=bPowerKeyFlag)
#define Clr_PowerKeyFlag()		        (SystemFlag1&=~bPowerKeyFlag)
#define Set_PowerOffFlag()		        (SystemFlag1|=bPowerOffFlag)
#define Clr_PowerOffFlag()		        (SystemFlag1&=~bPowerOffFlag)
#define Set_DoAutoConfigFlag()		        (SystemFlag1|=bDoAutoConfigFlag)
#define Clr_DoAutoConfigFlag()		        (SystemFlag1&=~bDoAutoConfigFlag)


#define Set_DoKeyCountFlag()		        (SystemFlag1|=bDoKeyCountFlag)
#define Clr_DoKeyCountFlag()		        (SystemFlag1&=~bDoKeyCountFlag)
//--> change to SystemFlag1 for reduce data size

//======================20120814===================//
#define bExpanderIO         				BIT4
#if ENABLE_FREESYNC
#define bFreeSyncBit         				BIT5
#define bOSDFreeSyncActionBit			BIT6
#endif

#define ExpanderIOFlag       			            (Sytstemflag2&bExpanderIO)
#if ENABLE_FREESYNC
#define FreeSyncFlag       			            (Sytstemflag2&bFreeSyncBit)
#define OSDFreeSyncActionFlag			(Sytstemflag2&bOSDFreeSyncActionBit)
#endif

#define Set_ExpanderIOFlag()			(Sytstemflag2|=bExpanderIO)
#define Clr_ExpanderIOFlag()			(Sytstemflag2&=~bExpanderIO)
#if ENABLE_FREESYNC
#define Set_FreeSyncFlag()			(Sytstemflag2|=bFreeSyncBit)
#define Clr_FreeSyncFlag()			(Sytstemflag2&=~bFreeSyncBit)

#define Set_OSDFreeSyncActionFlag()		(Sytstemflag2|=bOSDFreeSyncActionBit)
#define Clr_OSDFreeSyncActionFlag()		(Sytstemflag2&=~bOSDFreeSyncActionBit)
#endif



//======================20120814===================//
//--> change to SystemFlag3 for reduce data size
#define  bProductModeFlag      BIT0
#define  bBackToStandbyFlag      BIT1
#define  bBackToUnsupportFlag      BIT2
#define  bPanelOnFlag      BIT3
#define  bPressExitFlag      BIT4
#define  bEnableShowDDCFlag      BIT5
#define  bPressMenuFlag      BIT6
#define  bMuteFlag      BIT7


#define  BackToStandbyFlag            (Sytstemflag3&bBackToStandbyFlag)
#define  BackToUnsupportFlag        (Sytstemflag3&bBackToUnsupportFlag)
#define  PanelOnFlag                        (Sytstemflag3&bPanelOnFlag)
#define  PressExitFlag                      (Sytstemflag3&bPressExitFlag)
#define  EnableShowDDCFlag            (Sytstemflag3&bEnableShowDDCFlag)
#define  PressMenuFlag                    (Sytstemflag3&bPressMenuFlag)
#define  MuteFlag                               (Sytstemflag3&bMuteFlag)


#define Set_BackToStandbyFlag()      	(Sytstemflag3|=bBackToStandbyFlag)
#define Clr_BackToStandbyFlag()      	(Sytstemflag3&=~bBackToStandbyFlag)
#define Set_BackToUnsupportFlag()    	(Sytstemflag3|=bBackToUnsupportFlag)
#define Clr_BackToUnsupportFlag()    	(Sytstemflag3&=~bBackToUnsupportFlag)
#define Set_PanelOnFlag()               (Sytstemflag3|=bPanelOnFlag)
#define Clr_PanelOnFlag()               (Sytstemflag3&=~bPanelOnFlag)
#define Set_PressExitFlag()             (Sytstemflag3|=bPressExitFlag)
#define Clr_PressExitFlag()             (Sytstemflag3&=~bPressExitFlag)
#define Set_EnableShowDDCFlag()    (Sytstemflag3|=bEnableShowDDCFlag)
#define Clr_EnableShowDDCFlag()     (Sytstemflag3&=~bEnableShowDDCFlag)
#define Set_PressMenuFlag()             (Sytstemflag3|=bPressMenuFlag)
#define Clr_PressMenuFlag()              (Sytstemflag3&=~bPressMenuFlag)
#define Set_MuteFlag()                       (Sytstemflag3|=bMuteFlag)
#define Clr_MuteFlag()                       (Sytstemflag3&=~bMuteFlag)


#if JRY_Color_Tool_Functing
extern  BYTE idata WhileCounte;
extern bit ubAutoAlign;
#endif

#if JRY_FDDCCI_WriteEDID
extern  BYTE idata DDCCILoadEDIDCount;
#endif


//========== system flags status
extern bit InputTimingChangeFlag;
extern bit PowerSavingFlag;
extern bit ForcePowerSavingFlag;
extern bit InputTimingStableFlag;
#if 0//def WH_REQUEST
#if WH_REQUEST_DDCCI_POWERSAVING
#if MS_PM
extern bit DDCForcePowerSavingFlag;
#endif
#endif
#endif
extern bit DoModeSettingFlag;
extern bit CableNotConnectedFlag;
extern bit FreeRunModeFlag;
extern bit RxBusyFlag;
extern bit OsdTimeoutFlag;
extern bit ChangePatternFlag;
extern bit SaveSettingFlag;
extern bit ms500Flag;
#if 0//ENABLE_FREESYNC
extern bit ms250Flag;
#endif
extern bit ms50Flag;
extern bit ms10Flag;
extern bit ReverseXFlag;
extern bit ReverseYFlag;
extern bit DisplayLogoFlag;
extern bit ReadyForChangeFlag;
extern bit LoadOSDDataFlag;

extern bit AutoColorFlag;
extern bit ShowInputInfoFlag;
extern bit JustShowValueFlag;
extern bit DecVScaleFlag	;
extern bit SecondFlag;

/*====Change to systemflag3 ===//
extern bit BackToStandbyFlag;
extern bit BackToUnsupportFlag;
extern bit PanelOnFlag;
extern bit PressExitFlag;
extern bit EnableShowDDCFlag;
extern bit PressMenuFlag;
extern bit MuteFlag;

#define Set_BackToStandbyFlag()      	(BackToStandbyFlag=1)
#define Clr_BackToStandbyFlag()      	(BackToStandbyFlag=0)
#define Set_BackToUnsupportFlag()    	(BackToUnsupportFlag=1)
#define Clr_BackToUnsupportFlag()    	(BackToUnsupportFlag=0)
#define Set_PanelOnFlag()               (PanelOnFlag=1)
#define Clr_PanelOnFlag()               (PanelOnFlag=0)
#define Set_PressExitFlag()             (PressExitFlag=1)
#define Clr_PressExitFlag()             (PressExitFlag=0)
#define Set_EnableShowDDCFlag()         (EnableShowDDCFlag=1)
#define Clr_EnableShowDDCFlag()         (EnableShowDDCFlag=0)
#define Set_PressMenuFlag()             (PressMenuFlag=1)
#define Clr_PressMenuFlag()             (PressMenuFlag=0)
#define Set_MuteFlag()                  (MuteFlag=1)
#define Clr_MuteFlag()                  (MuteFlag=0)
/====Change to systemflag3 ===
*/



#if ENABLE_OVER_SCAN && AudioFunc	//121211 Modify
extern bit PressPlusFlag;
extern bit EnableExpansionMenuFlag;
extern BYTE xdata HotKeyPlusCounter;
#endif


#if PowerSaveLedFlicker_Enable||FactoryLedFlicker_Enable
extern BYTE xdata LedCounter;
#endif

#define Set_InputTimingChangeFlag()	  	(InputTimingChangeFlag=1)
#define Clr_InputTimingChangeFlag()	  	(InputTimingChangeFlag=0)
#define Set_PowerSavingFlag()		  	(PowerSavingFlag=1)
#define Clr_PowerSavingFlag()		  	(PowerSavingFlag=0)
#define Set_ForcePowerSavingFlag()	  	(ForcePowerSavingFlag=1)
#define Clr_ForcePowerSavingFlag()	 	(ForcePowerSavingFlag=0)
#define Set_InputTimingStableFlag()	  	(InputTimingStableFlag=1)
#define Clr_InputTimingStableFlag()	   	(InputTimingStableFlag=0)
#if 0//def WH_REQUEST
#if WH_REQUEST_DDCCI_POWERSAVING
#if MS_PM
#define Set_DDCForcePowerSavingFlag()	  	(DDCForcePowerSavingFlag=1)
#define Clr_DDCForcePowerSavingFlag()	 	(DDCForcePowerSavingFlag=0)
#endif
#endif
#endif
#define Set_RxBusyFlag()		     	(RxBusyFlag=1)
#define Clr_RxBusyFlag()		    	(RxBusyFlag=0)
#define Set_DoModeSettingFlag()			(DoModeSettingFlag=1)
#define Clr_DoModeSettingFlag()			(DoModeSettingFlag=0)
#define Set_OsdTimeoutFlag()			(OsdTimeoutFlag=1)
#define Clr_OsdTimeoutFlag()		  	(OsdTimeoutFlag=0)
#define Set_CableNotConnectedFlag()	  	(CableNotConnectedFlag=1)
#define Clr_CableNotConnectedFlag()	  	(CableNotConnectedFlag=0)
#define Set_FreeRunModeFlag()		  	(FreeRunModeFlag=1)
#define Clr_FreeRunModeFlag()		  	(FreeRunModeFlag=0)
#define Set_ChangePatternFlag()			(ChangePatternFlag=1)
#define Clr_ChangePatternFlag()			(ChangePatternFlag=0)
#define Set_SaveSettingFlag()		 	(SaveSettingFlag=1)
#define Clr_SaveSettingFlag()			(SaveSettingFlag=0)
#if 0//ENABLE_FREESYNC
#define Set_ms250Flag()			    	(ms250Flag=1)
#define Clr_ms250Flag()			    	(ms250Flag=0)
#endif
#define Set_ms500Flag()			    	(ms500Flag=1)
#define Clr_ms500Flag()			    	(ms500Flag=0)
#define Set_ms50Flag()			    	(ms50Flag=1)
#define Clr_ms50Flag()			    	(ms50Flag=0)
#define Set_ms10Flag()			    	(ms10Flag=1)
#define Clr_ms10Flag()			    	(ms10Flag=0)
#define Set_ReverseXFlag()		 		(ReverseXFlag=1)
#define Clr_ReverseXFlag()		    	(ReverseXFlag=0)
#define Set_ReverseYFlag()		    	(ReverseYFlag=1)
#define Clr_ReverseYFlag()		       	(ReverseYFlag=0)
#define Set_DisplayLogoFlag()		  	(DisplayLogoFlag=1)
#define Clr_DisplayLogoFlag()	      	(DisplayLogoFlag=0)
#define Set_ReadyForChangeFlag()      	(ReadyForChangeFlag=1)
#define Clr_ReadyForChangeFlag()     	(ReadyForChangeFlag=0)
#define Set_LoadOSDDataFlag()		  	(LoadOSDDataFlag=1)
#define Clr_LoadOSDDataFlag()		  	(LoadOSDDataFlag=0)


#define Set_AutoColorFlag() 	     	(AutoColorFlag=1)
#define Clr_AutoColorFlag() 	      	(AutoColorFlag=0)
#define Set_ShowInputInfoFlag()   		(ShowInputInfoFlag=1)
#define Clr_ShowInputInfoFlag()    		(ShowInputInfoFlag=0)
#define Set_JustShowValueFlag()    		(JustShowValueFlag=1)
#define Clr_JustShowValueFlag()    		(JustShowValueFlag=0)
#define Set_DecVScaleFlag()	       		(DecVScaleFlag=1)
#define Clr_DecVScaleFlag()	      		(DecVScaleFlag=0)


#if ENABLE_OVER_SCAN && AudioFunc	//121211 Modify
#define Set_PressPlusFlag()				(PressPlusFlag=1)
#define Clr_PressPlusFlag()				(PressPlusFlag=0)
#define Set_EnableExpansionMenuFlag()	(EnableExpansionMenuFlag=1)
#define Clr_EnableExpansionMenuFlag()	(EnableExpansionMenuFlag=0)
#endif

#if Enable_Expansion
extern bit ExpansionFlag;
#define Set_ExpansionFlag()				(ExpansionFlag=1)
#define Clr_ExpansionFlag()				(ExpansionFlag=1)
extern WORD xdata DispalyWidth;
extern WORD xdata HStartOffset;
#endif
#if Enable_Expansion	//120204 Modify
#if PANEL_QUAD_PORT
#define DISPLAY_WIDTH	2*(msRead2Byte(SC0_1C)-msRead2Byte(SC0_18)+1)//DispalyWidth		//130108_22 Henry//petit 20130227 update
#else
#define DISPLAY_WIDTH	(msRead2Byte(SC0_1C)-msRead2Byte(SC0_18)+1)//DispalyWidth		//130114_1  //petit 20130227 update
#endif
#define DISPLAY_HEIGHT	(msRead2Byte(SC0_1A)+1)
#define HSTART_OFFSET	(PANEL_WIDTH-DISPLAY_WIDTH)/2//HStartOffset
#else
#define DISPLAY_WIDTH	PanelWidth
#define HSTART_OFFSET	0
#endif

#define Set_SecondFlag()			   	(SecondFlag=1)
#define Clr_SecondFlag()			  	(SecondFlag=0)







#if ENABLE_HDCP
extern bit HdcpNVRamFlag;
#define Set_HdcpNVRamFlag()				(HdcpNVRamFlag=1)
#define Clr_HdcpNVRamFlag()				(HdcpNVRamFlag=0)
#if HDCPKEY_IN_Flash
extern bit LoadHDCPKeyFlag;
extern bit WriteHDCPcodeFlag;
#define Set_LoadHDCPKeyFlag()    		(LoadHDCPKeyFlag=1)
#define Clr_LoadHDCPKeyFlag()     		(LoadHDCPKeyFlag=0)
#define Set_WriteHDCPcodeFlag()	      	(WriteHDCPcodeFlag=1)
#define Clr_WriteHDCPcodeFlag()    		(WriteHDCPcodeFlag=0)
#endif
#endif

#ifdef UseVGACableReadWriteAllPortsEDID
#if defined(ReduceDDC) || ENABLE_DP_INPUT || ENABLE_MHL	|| ((CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF)&& ENABLE_CABLE_5V_EDID)//121228 Modify
extern bit LoadEDIDFlag;
#define Set_LoadEDIDFlag()			 	(LoadEDIDFlag=1)
#define Clr_LoadEDIDFlag()		     	(LoadEDIDFlag=0)
#endif
extern bit WriteDeviceFlag;
#define Set_WriteDeviceFlag()			(WriteDeviceFlag=1)
#define Clr_WriteDeviceFlag()			(WriteDeviceFlag=0)
#endif



//=================================================================
#if 0//def WH_REQUEST	//130913 fay
extern bit EnableShowFactoryMenuFlag;

#define Set_EnableShowFactoryMenuFlag() (EnableShowFactoryMenuFlag=1)
#define Clr_EnableShowFactoryMenuFlag() (EnableShowFactoryMenuFlag=0)
#endif


#if ENABLE_FREESYNC
typedef enum
{
	FreeSyncMenuItems_Off,
	FreeSyncMenuItems_On,
	FreeSyncMenuItems_Max,
};
#define IS_HDMI_FREESYNC_ISR()  (msAPI_combo_IPGetDDRFlag_ISR()&&CURRENT_INPUT_IS_HDMI())
#define IS_HDMI_FREESYNC()    	(msAPI_combo_IPGetDDRFlag()&&CURRENT_INPUT_IS_HDMI())

#define IS_DP_FREESYNC()      	(msAPI_combo_IPGetDDRFlag()&&CURRENT_INPUT_IS_DISPLAYPORT())


#if CHIP_ID==CHIP_TSUMU
#define IS_HDMI_FREESYNC_2()    	((msReadByte(REG_0593) & 0x02)&&CURRENT_INPUT_IS_HDMI())
#else
#define IS_HDMI_FREESYNC_2()    	((msReadByte(REG_15BD) & 0x02)&&CURRENT_INPUT_IS_HDMI())
#endif

#endif

#if ENABLE_OSD_LowBlueLight
#if LowBlueLightType == LowBlueLight_SharpFunc
#define DEF_LowBlueLight_MODE           (LOW_BLUE_LIGHT_Middle)

#define LowBlueLight_MODE_OSD_MAX     	(LOW_BLUE_LIGHT_Strong)
#define LowBlueLight_MODE_OSD_MIN    	(LOW_BLUE_LIGHT_Weak)
#else
#define DEF_LowBlueLight_MODE           (LOW_BLUE_LIGHT_OFF)
#define LowBlueLight_MODE_OSD_MAX     	(LOW_BLUE_LIGHT_Strong)
#define LowBlueLight_MODE_OSD_MIN    	(LOW_BLUE_LIGHT_OFF)
#endif
#endif

#if 1//(CHIP_ID==CHIP_TSUMC|| CHIP_ID==CHIP_TSUMD || CHIP_ID==CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)
extern WORD GetImageHeight(void);
extern WORD GetImageWidth(void);
#endif

#define WAIT_V_OUTPUT_BLANKING_START()   { if(!SyncLossState()&&PanelOnFlag){SetTimOutConter(30);while(((msReadByte(SC0_E0)&BIT0)==0)&&bTimeOutCounterFlag);\
			SetTimOutConter(30);while(((msReadByte(SC0_E0)&BIT0)!=0)&&bTimeOutCounterFlag);}}//20130227 modify for DC OFF issue


#endif





