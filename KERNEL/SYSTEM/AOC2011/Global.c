#include "types.h"
#include "board.h"
#include "global.h"
#include "Debug.h"

#include "keypaddef.h"


#include "menudef.h"

#if MWEFunction
#include "MsDLC.h"
#include "MsACE.h"
#include "Userpref.h"
/*
BYTE  UserPrefSubRedGain=0;
BYTE  UserPrefSubGreenGain=0;
BYTE  UserPrefSubBlueGain=0;
 */
#endif



#if ENABLE_DisplayPortTX
#include "drvDPTxApp.h"
#endif

#if ENABLE_DP_INPUT
bit g_bDoDPInit;
#endif

#include "drvmsOVD.h"

//------Eson Start-----------------------------------------
BYTE xdata ucPreXPos;
BYTE xdata ucPreYPos;
BYTE xdata ucOSDMenuMoveType;
BYTE xdata bMoveCURSORFlag;

#if TMDS_SYNC_RECHECK//20130418
BYTE xdata HsyncDisappearCounter = 0;
BYTE xdata VsyncDisappearCounter = 0;
#endif


#if All_AudioDet

BYTE xdata bAudioInputStatus = 0;

#endif



#if LowBlueLightType == LowBlueLight_SharpFunc
xdata BYTE gTempLowBlueMode;
#endif

#if 1//PropFontSource
xdata WORD CFontData[18];
WORD xdata font_shift;
WORD xdata font_offset;
WORD xdata TotalFontWidth;
BYTE xdata PropFontRamWidth;
BYTE xdata FontUsedPixel;

BYTE xdata font_Norm_Up_Down; // 0: norm  , 1: half of up, 2:half of down.
#endif

#if ENABLE_MHL
#if CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD || CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF// demo board	// 130717 william For G15 compiling warning
BYTE xdata MHLExtenCountFlag = 0; // 0 means current MHL port has 1 chance to extend time for staying at current port
#endif
#endif

//------Eson End-------------------------------------------


BYTE xdata g_ucTimer0_TH0;
BYTE xdata g_ucTimer0_TL0;
BYTE xdata g_u8SystemSpeedMode = 0;

bit   g_bInputSOGFlag;

BYTE xdata TI0_FLAG;

bit g_bMcuPMClock;

#if AudioFunc && ENABLE_DP_INPUT
BYTE xdata PrevInputType = 0;		//130107_21 Henry for ChangeSource between DP and other Source,then can not Mute Audio
#endif

#if sRGBIssue
BYTE xdata UserPrevECOMode, UserPrevGamaMode, UserPrevDcrMode;	//130109_23 Henry
#endif





#ifdef OffPower
BYTE xdata ShowOffPowerWarningFlag;
#endif
WORD ms_Counter = SystemTick; // for System timer
BYTE xdata ModeDetectCounter;
BYTE xdata Second;
WORD xdata DelayCounter;
bit bDelayFlag;
WORD xdata PanelOffOnDelayCntr;
bit bPanelDelayFlag;
//WORD xdata TimeOutCounter; //130823 larry modfiy for WaitOutputFpllStable  120510 coding, addition for checking register status
WORD xdata u16TimeOutCounter = 0; // 120510 coding, addition for checking register status
bit bTimeOutCounterFlag = 0;



// 110826 coding addition for recording back light active status
BYTE xdata BackLightActiveFlag;

#if ESaverPowerDownFunc
WORD xdata ESaverPowerDownCounter;
#endif
BYTE xdata OsdCounter;
BYTE xdata HotKeyCounter;
BYTE xdata PowerDownCounter;
BYTE xdata SourceKeyCounter;
#if ENABLE_MHL
WORD xdata InputTimingStableCounter;
#else
BYTE xdata InputTimingStableCounter;
#endif
BYTE xdata SwitchPortCntr; // 071222
#ifdef OffPower          //090331 xiandi.yu Auto Off Power
#if 1//130723 william For PowerSaving timer slowly  !EXT_TIMER0_1S//20130510 xiandi.yu Auto Off Power
BYTE xdata AutoPowerOffSTime = 0;
#endif
BYTE xdata AutoPowerOffMTime;
BYTE xdata AutoPowerOffHTime;
#endif
//WORD SystemFlags=0;    // for system status flags
//BYTE System2Flags=0;
//BYTE PatternNo=0;
#if 0 // 2006/11/9 11:41AM by Emily  temp
DWORD xdata BlackoffTime = 0;
#endif


#if EANBLE_NEW_DCR_Functing
BYTE xdata DCR_Counter = 0;
BYTE xdata DCRStepTransCnt = 0;
#endif


//BYTE LanguageState=0;
//BYTE CurrentLanguage=0;   //wumaozhong add 20050615
//BYTE ShortcutLuminance=0;
//BYTE SaveIndex=0; // saveIndex
//WORD xdata SystemFlags = 0; // for system status flags
//WORD  System2Flags = 0;
BYTE xdata PowerKeyCounter;
//BYTE xdata KeypadFlags=0;
BYTE xdata SaveIndex; // saveIndex
BYTE xdata PatternNo;
//BYTE xdata BrightnessTemp = 0;
//BYTE xdata PrevHistoValue = 0;
#if DECREASE_V_SCALING
WORD xdata DecVScaleValue;

#endif
BYTE xdata gBoolVisualKey = 0;
BYTE xdata gByteVisualKey = 0xff;
BYTE xdata LanguageIndex;
BYTE xdata SecondTblAddr;

BYTE  xdata MenuPageIndex;
BYTE  xdata MenuItemIndex;

//BYTE xdata BoostTempValue=0;

BYTE  xdata TermBuffer;
#if ENABLE_HDCP
//BYTE xdata HPD_Counter = 0;
//BYTE xdata HDCPFlag = 0;
// 2006/11/29 10:35AM by KK WORD xdata g_wHDCP_KeyChkSum;
// 2006/11/29 10:35AM by KK WORD xdata g_HDCP_KeyCounter;
//XDATA g_bHPD_Status;

//bit HpdReadyFlag=0;
bit HdcpNVRamFlag;

#endif

WORD xdata DCOffOnCounter = 0;

#if 0//ENABLE_HDMI
BYTE xdata PreHDMIColor = 0;
#endif
BYTE xdata InputColorFormat;


#if ENABLE_HDCP
#if HDCPKEY_IN_Flash
bit LoadHDCPKeyFlag;
bit WriteHDCPcodeFlag;
BYTE xdata HDCPDataBuffer[6]; //[6];
WORD xdata TCRCvalue;
#ifdef HDCP_IN_FLASH_NEW_WAY
BYTE xdata HDCPKeySaveIndex;//Zhifeng.wu
#endif
#endif
#endif

#if 0//ENABLE_HDMI
bit bDigitalGraphicReset = 0;
#endif
#if USEFLASH
FactorySettingType xdata  FactorySetting;
#endif

#if !USEFLASH
FactorySettingType xdata  FactorySetting;
#endif

#ifdef  UseVGACableReadWriteAllPortsEDID
BYTE xdata SIORxBuffer[DDC_BUFFER_LENGTH];	//20120625 updata
#else
#ifdef DATA_LENGTH_20_BYTE
BYTE xdata SIORxBuffer[23];
#else
BYTE xdata SIORxBuffer[8];
#endif
#endif

#ifdef UseVGACableReadWriteAllPortsEDID
#ifdef ReduceDDC
bit LoadEDIDFlag;
#else
#if ENABLE_DP_INPUT ||ENABLE_MHL || ((CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF) && ENABLE_CABLE_5V_EDID)//121228 Modify
bit LoadEDIDFlag;
#endif
BYTE xdata LoadEDIDSelectPort = 0xFF ;
#endif
bit WriteDeviceFlag;
#endif

BYTE xdata DDC1[289];// 2017/02/20
BYTE EnableReadDDCType = I2C_EEPROM;

#ifdef ReduceDDC
bit EnCheckVccFlag;
BYTE xdata SystemVccDropDownCnt;
#endif

#if 0//def WH_REQUEST	//130913 fay
bit EnableShowFactoryMenuFlag = 0;
#endif
#if FreeSyncSwitchEDID

BYTE xdata HDMI1FreeSyncED = 0;

BYTE xdata HDMI2FreeSyncED = 0;


#endif

//bit SaveFactorySettingFlag=0;
#if 0//EnablePanelServiceMenu
BYTE xdata PanelSelect;
BYTE xdata SavePanelSettingFlag;
BYTE xdata TestMinDutyFlag;
PanelSettingType xdata PanelSetting;
#endif

#if PanelminiLVDS||PANEL_VCOM_ADJUST	//110229 Modify
#if PANEL_VCOM_ADJUST			//	For Turn on panel  R/W Vcom	130311 Modify
#else
BYTE xdata g_bACPowerOn_CheckVCOM = FALSE ;
#endif
#endif

InputTimingType xdata InputTiming;
MonitorSettingType xdata MonitorSetting; //Benz 2007.4.15   19:44:07idata - >xdata
ModeSettingType xdata ModeSetting;
#if USEFLASH
MonitorSettingType2 xdata  MonitorSetting2;
#endif
#if (ENABLE_OVER_SCAN||CHIP_ID == CHIP_TSUMD)  //130909 nick add
OverScanType xdata OverScanSetting;
#endif

#if Show_BackLightTimeValue
BYTE    xdata BlacklitTime_S = 0;
BYTE    xdata BlacklitTime_M = 0;
WORD   xdata BlacklitTime_H = 0;
//BYTE    xdata BlacklitTime_HH = 0;
#endif

//==========================for AutoBacklight=====
BYTE xdata HistogramNow;
BYTE xdata HistogramPrev;
BYTE xdata BacklightNow;
BYTE xdata BacklightPrev;
BYTE xdata HistogramFlag = 1;
//xdata BYTE xfr_regs[256] _at_ 0xC000;




bit InputTimingChangeFlag;
bit PowerSavingFlag;
bit ForcePowerSavingFlag;
bit InputTimingStableFlag;
#if 0//def WH_REQUEST
#if WH_REQUEST_DDCCI_POWERSAVING
#if MS_PM
bit DDCForcePowerSavingFlag;
#endif
#endif
#endif
bit DoModeSettingFlag;
bit CableNotConnectedFlag;
bit FreeRunModeFlag;
bit RxBusyFlag;
bit OsdTimeoutFlag;
bit ChangePatternFlag;
bit SaveSettingFlag;
bit SecondFlag;
bit ms500Flag;
#if 0//ENABLE_FREESYNC
bit ms250Flag;
#endif
bit ms50Flag;
bit ms10Flag;
bit ReverseXFlag;
bit ReverseYFlag;

bit ReadyForChangeFlag;
bit LoadOSDDataFlag;
bit AutoColorFlag;
bit ShowInputInfoFlag;
bit JustShowValueFlag;
bit DecVScaleFlag;
BYTE xdata SystemFlag1;
BYTE xdata SystemFlags = 0;

bit DisplayLogoFlag;

//--> change to SystemFlag1 for reduce data size
/*
bit DebugOnlyFlag=0;
bit MainOSDFlag=0;
bit SubOSDFlag=0;
bit PowerKeyFlag=0;
bit PowerOffFlag=0;
bit DoAutoConfigFlag=0;
bit DoKeyCountFlag=0;
//=============================//
*/

BYTE xdata Sytstemflag2;        //2012.08.14 Stone.yu
BYTE xdata Sytstemflag3;        //
//--> change to SystemFlag3 for reduce data size
/*
bit BackToStandbyFlag;	//111223 Modify
bit BackToUnsupportFlag;	//111223 Modify
bit PanelOnFlag;
bit PressExitFlag;
bit EnableShowDDCFlag;
bit PressMenuFlag;
bit MuteFlag;
*/


#if JRY_Color_Tool_Functing
BYTE idata WhileCounte = 0;
bit ubAutoAlign = 0;
#endif

#if JRY_FDDCCI_WriteEDID
BYTE idata DDCCILoadEDIDCount = 0;
#endif


#if Enable_Expansion
bit ExpansionFlag;
WORD xdata DispalyWidth = PANEL_WIDTH;
WORD xdata HStartOffset;
#endif


#if ENABLE_OVER_SCAN && AudioFunc	//121211 Modify
bit PressPlusFlag;
bit EnableExpansionMenuFlag;
BYTE xdata HotKeyPlusCounter;
#endif


#if PowerSaveLedFlicker_Enable||FactoryLedFlicker_Enable
BYTE xdata LedCounter = 0;
#endif

#if (CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)
BOOL g_bFROTrimResult;
#endif



//bit StartScanKeyFlag = 0;
BYTE xdata TPDebunceCounter;

#if MS_DAC&&(CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)
WORD xdata w16DAC_DePopCounter = 0;
bit bDAC_DePopCountFlag = 0;
BYTE xdata w16DAC_DePopStep = 0;
bit bDAC_DePopFlag = 0;
#endif
#if ENABLE_TIME_MEASUREMENT
WORD volatile g_u16TimeMeasurementCounter = 0;
bit bTimeMeasurementFlag = 0;
WORD g_u16Time1;
WORD g_u16Time2;
#endif



BYTE code UserDataCode[];// =//Set UserDataCode To Bank3 Addr:A000


#if Enable_ButtonKeyLongPressFunction
BYTE xdata g_HoldKeypadButton = BTN_EndBTN;
BYTE xdata g_HoldKeyCounter = 0;
#endif

#if CHIP_ID == CHIP_TSUM2 || CHIP_ID == CHIP_TSUMU
#if !ENABLE_RTE
//  void msFB_DummyCall(void);
#endif
#endif



//#if ENABLE_MHL
//extern void MS_MHL_MAPIDummy(void);

extern void msMHLDummy();
extern msClearVersionDummy();  //nick add 20130529
//#endif

#if !ENABLE_DisplayPortTX
extern void msDpTxDummy();
#endif


#if ENABLE_FREESYNC
extern BYTE GetSrcFreesyncFPS(void);
extern Bool SetDRRFunction(void);
#endif

void UnCalledFunctions( void )
{
	BYTE xdata ucUnCall = 0;
	if( ucUnCall )
	{
		#if !ENABLE_RTE
		msOverDriveDummy();
		#endif
		#if 1//ENABLE_MHL
		msMHLDummy();
		#endif
		#if ENABLE_HDMI_1_4
		//msHDMI_Get_3D_Ext_Data();
		//msHDMI_Get_3D_Meta_Field(0);
		//msHDMI_Get_VIC_Code();
		//msHDMI_Get_4Kx2K_VIC_Code();
		msHDMI_Check_Additional_Format();
		msHDMI_Get_3D_Structure();
		#endif
		TIME_MEASURE_BEGIN();
		TIME_MEASURE_END();
		#if ENABLE_SW_DOUBLE_BUFFER && (CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)
		msSWDBWrite2ByteMask(0, 0, 0);
		msSWDBWriteBit(0, 0, 0);
		msWrite3Byte(0, 0);
		#endif
		#if 0
		GetSrcFreesyncFPS();
		SetDRRFunction();
		#endif
		#if ENABLE_DisplayPortTX
		DPTxCheckCRC();
		DPAUX_TEST();
		DPTxEDIDRead();
		I_Gen_Tuning();
		#else
		msDpTxDummy();
		#endif
	}
}


void Init_GlobalVariables(void)
{
	InputTimingStableCounter = UserDataCode[0];
	InputTimingStableCounter = 0;
	SwitchPortCntr = 0;
	OsdCounter = 0;
	HotKeyCounter = 0;
	PowerKeyCounter = 0;
	PowerDownCounter = 0;
	gBoolVisualKey = 0;
	#if 0
	HotKeyMinusCounter = 0;
	#endif
	#if ENABLE_OVER_SCAN && AudioFunc	//121211 Modify
	HotKeyPlusCounter = 0;
	#endif
	#if (ENABLE_OVER_SCAN||CHIP_ID == CHIP_TSUMD)  //130909 nick add
	OverScanSetting.Enable = 0;
	#endif
	//Clr_StartScanKeyFlag();
	TPDebunceCounter = SKPollingInterval;
	//MS_MHL_MAPIDummy();
	#if CHIP_ID == CHIP_TSUM2 || CHIP_ID == CHIP_TSUMU
	#if !ENABLE_RTE
	// msFB_DummyCall();
	#endif
	#endif
	#if Show_BackLightTimeValue
	BlacklitTime_S = MonitorBackLightTime_S;
	BlacklitTime_M = MonitorBackLightTime_M;
	BlacklitTime_H = MonitorBackLightTime_H;
	#endif
	#if JRY_Color_Tool_Functing
	Clr_ATEModeFlag();
	#endif
	#if JRY_FDDCCI_WriteEDID
	Clr_DDCCIReadLoadEDIDFlag();
	DDCCILoadEDIDCount = 0;
	#endif
	#if LoadAllPortSeriealnumberByOneVGAPort
	Clr_DDCCOneVGAPortLoadEDIDFlag();
	#endif
	#if ESaverPowerDownFunc
	ESaverPowerDownCounter = 0;
	#endif
	#if LowBlueLightType == LowBlueLight_SharpFunc
	if(UserPrefColorTemp != CTEMP_LowBlue)
		gTempLowBlueMode = LOW_BLUE_LIGHT_OFF;
	else
		gTempLowBlueMode = UserprefLowBlueLightMode;
	#endif
	SrcFlags = SyncLoss;
	if (BurninModeFlag)
	{
		Set_DoBurninModeFlag();
	}
	else
	{
		Clr_DoBurninModeFlag();
	}
	if (PowerOnFlag)
	{
		Set_InputTimingChangeFlag();
		#if DisplayPowerOnLogo
		if (!(FactoryModeFlag))
			Set_DisplayLogoFlag();
		#endif
	}
	else
	{
		Set_ForcePowerSavingFlag(); // 080917 addition for dc off
		Clr_DisplayLogoFlag();
	}
	#if Dual
	if (!(FactoryModeFlag))
		Set_ShowInputInfoFlag();
	#endif
	#ifdef OffPower
	ShowOffPowerWarningFlag = 0;
	#endif
	#if DECREASE_V_SCALING
	DecVScaleValue = 0;
	#endif
	#if ENABLE_OVER_SCAN && AudioFunc	//121211 Modify
	PressPlusFlag = 0;
	EnableExpansionMenuFlag = 0;
	HotKeyPlusCounter = 0;
	#endif
	#if ColorTool_Clear_Time
	Clr_DDCCIAutoColorFlag();
	Clr_DDCCResetTimeFlag();
	#endif
	UnCalledFunctions();
}
#if 1//(CHIP_ID==CHIP_TSUMC|| CHIP_ID==CHIP_TSUMD || CHIP_ID==CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)
WORD GetImageWidth(void)
{
	WORD u16ImageWidth;
	if( CURRENT_INPUT_IS_VGA() )
	{
		u16ImageWidth = StandardModeWidth;
	}
	#if ENABLE_DP_INPUT
	else if( CURRENT_INPUT_IS_DISPLAYPORT() )
	{
		u16ImageWidth = gDPInfo.uwDPHWidth;
	}
	#endif
	#if  ENABLE_CHECK_TMDS_DE
	else if( CURRENT_INPUT_IS_TMDS() )
	{
		u16ImageWidth = SrcTMDSWidth;
	}
	#endif
	else
	{
		u16ImageWidth = SC0_READ_AUTO_WIDTH();
	}
	return u16ImageWidth;
}
WORD GetImageHeight(void)
{
	WORD u16ImageHeight;
	if( CURRENT_INPUT_IS_VGA() )
	{
		u16ImageHeight = StandardModeHeight;
	}
	#if ENABLE_DP_INPUT
	else if( CURRENT_INPUT_IS_DISPLAYPORT() )
	{
		u16ImageHeight = gDPInfo.uwDPVWidth;
	}
	#endif
	#if  ENABLE_CHECK_TMDS_DE
	else if( CURRENT_INPUT_IS_TMDS() )
	{
		u16ImageHeight = SrcTMDSHeight;
	}
	#endif
	else
	{
		u16ImageHeight = SC0_READ_AUTO_HEIGHT();
	}
	return u16ImageHeight;
}
#endif

#if CHIP_ID == CHIP_TSUM2 || CHIP_ID == CHIP_TSUMU|| CHIP_ID == CHIP_TSUMC|| CHIP_ID == CHIP_TSUMD|| CHIP_ID == CHIP_TSUMB||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF//20130427//20130509
#if ENABLE_DP_INPUT&&(CHIP_ID == CHIP_TSUMC|| CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)
BYTE GetPow2(BYTE exp)
{
	if( exp == 0 )
		return 1;
	else
		return (0x02 << (exp - 1));
}
#endif
BYTE GetLog(DWORD value)
{
	BYTE i = 0;
	if( value == 0 )
		return 0;
	while(value)
	{
		value >>= 1;
		i++;
	}
	return (i - 1);
}
#endif

