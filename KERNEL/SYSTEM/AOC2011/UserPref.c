#include <math.h>
#include "types.h"
#include "board.h"
#include "global.h"
#include "nvram.h"
#include "debug.h"
#include "menudef.h"
#include "menufunc.h"
#include "mcu.h"
#include "ms_reg.h"
#if 1
#include "MsDLC.h"
#include "MsACE.h"
#include "UserPref.h"
#endif
#if 1//USEFLASH
#include "msflash.h"
//Bool IsFlashSettingAreaEmpty(BYTE EmptyValue);//edit by lizzie.ding ,for check flash empty
#endif



#include "drvADC.h"
#define HFreq_Tol   16 // 1.6 KHz
#define VFreq_Tol   8  // 0.8 Hz

#if USEFLASH
BYTE xdata ucFlashSaveState;	// Save user Setting flag
//WORD xdata ucFlashSaveCount;	// Flash Save counter
#endif

#if !USEFLASH
void CheckBoard(void);
void ReadBlacklitTime(void);
#endif
Bool IsEEPRomEmpty(BYTE EmptyValue);

//Benz 2007.4.24   23:25:55 void SaveBlacklitTime( void );

Bool CheckFactorySettingOutOfRange(void)
{
	#if 0//def WH_REQUEST
	//#if ((CHIP_ID>=CHIP_TSUMV)||CHIP_ID==CHIP_TSUMB)
	#if (CHIP_ID>=CHIP_TSUMU)			//Fay 2013/8/2
	if (UserPrefAdcPgaGain > 0x2A)
		return TRUE;
	if(
	    UserPrefAdcRedGain >= 0x600 ||
	    UserPrefAdcGreenGain >= 0x600 ||
	    UserPrefAdcBlueGain >= 0x600 ||
	    UserPrefAdcRedGain <= 0x200 ||
	    UserPrefAdcGreenGain <= 0x200 ||
	    UserPrefAdcBlueGain <= 0x200
	)
		return TRUE;
	if( (UserPrefAdcRedOffset != 0x00 && UserPrefAdcRedOffset != 0x800 - OffsetValue) ||
	        (UserPrefAdcBlueOffset != 0x00 && UserPrefAdcBlueOffset != 0x800 - OffsetValue) ||
	        (UserPrefAdcGreenOffset != 0x00 && UserPrefAdcGreenOffset != 0x800 - OffsetValue)
	  )
		return TRUE;
	#endif
	#else
	#if (CHIP_ID>=CHIP_TSUMV)
	if (UserPrefAdcPgaGain > 0x2A)
		return TRUE;
	if(
	    UserPrefAdcRedGain >= 0x600 ||
	    UserPrefAdcGreenGain >= 0x600 ||
	    UserPrefAdcBlueGain >= 0x600 ||
	    UserPrefAdcRedGain <= 0x200 ||
	    UserPrefAdcGreenGain <= 0x200 ||
	    UserPrefAdcBlueGain <= 0x200
	)
		return TRUE;
	if( (UserPrefAdcRedOffset != 0x00 && UserPrefAdcRedOffset != 0x800 - OffsetValue) ||
	        (UserPrefAdcBlueOffset != 0x00 && UserPrefAdcBlueOffset != 0x800 - OffsetValue) ||
	        (UserPrefAdcGreenOffset != 0x00 && UserPrefAdcGreenOffset != 0x800 - OffsetValue)
	  )
		return TRUE;
	#endif
	#endif
	if(
	    UserPrefRedColorCool1 <= 50 ||
	    UserPrefGreenColorCool1 <= 50 ||
	    UserPrefBlueColorCool1 <= 50 ||
    #if CT_7500K_ENABLE
	    UserPrefRedColorNormal <= 50 ||
	    UserPrefGreenColorNormal <= 50 ||
	    UserPrefBlueColorNormal <= 50 ||
    #endif
	    UserPrefRedColorWarm1 <= 50 ||
	    UserPrefGreenColorWarm1 <= 50 ||
	    UserPrefBlueColorWarm1 <= 50
    #if CT_sRGB_ENABLE
	    || UserPrefRedColorSRGB <= 50 ||
	    UserPrefGreenColorSRGB <= 50 ||
	    UserPrefBlueColorSRGB <= 50
    #endif
	)
		return TRUE;
	if(
	    UserPrefRedColorUser < MinColorValue ||
	    UserPrefRedColorUser > MaxColorValue ||
	    UserPrefGreenColorUser < MinColorValue ||
	    UserPrefGreenColorUser > MaxColorValue ||
	    UserPrefBlueColorUser < MinColorValue ||
	    UserPrefBlueColorUser > MaxColorValue
	)
		return TRUE;
	if(
    #if PanelminiLVDS||PANEL_VCOM_ADJUST	//110229 Modify
	    FactorySetting.VcomValue > MAX_VCOM_VALUE ||
	    FactorySetting.VcomValue < MIN_VCOM_VALUE ||
    #endif
	    abs(UserPrefRedColorCool1 - UserPrefGreenColorCool1) >= 100 ||
	    abs(UserPrefGreenColorCool1 - UserPrefBlueColorCool1)  >= 100 ||
	    abs(UserPrefRedColorCool1 - UserPrefBlueColorCool1)  >= 100 ||
    #if CT_7500K_ENABLE
	    abs(UserPrefRedColorNormal - UserPrefGreenColorNormal) >= 100 ||
	    abs(UserPrefGreenColorNormal - UserPrefBlueColorNormal)  >= 100 ||
	    abs(UserPrefRedColorNormal - UserPrefBlueColorNormal)  >= 100 ||
    #endif
	    abs(UserPrefRedColorWarm1 - UserPrefGreenColorWarm1) >= 100 ||
	    abs(UserPrefGreenColorWarm1 - UserPrefBlueColorWarm1)  >= 100 ||
	    abs(UserPrefRedColorWarm1 - UserPrefBlueColorWarm1)  >= 100
    #if CT_sRGB_ENABLE
	    || abs(UserPrefRedColorSRGB - UserPrefGreenColorSRGB) >= 100 ||
	    abs(UserPrefGreenColorSRGB - UserPrefBlueColorSRGB)  >= 100 ||
	    abs(UserPrefRedColorSRGB - UserPrefBlueColorSRGB)  >= 100
    #endif
	)
		return TRUE;
	#if ENABLE_FACTORY_SSCADJ	//120305 Modify
	if (FactorySetting.SSCModulation > PANEL_SSC_MODULATION_MAX)
		FactorySetting.SSCModulation = PANEL_SSC_MODULATION_MAX;
	if (FactorySetting.SSCPercentage > PANEL_SSC_PERCENTAGE_MAX)
		FactorySetting.SSCPercentage = PANEL_SSC_PERCENTAGE_DEF;
	#endif
	#if USEFLASH
	if(FactoryCheckSum != FLASH_CHECKSUM)
		return TRUE;
	#endif
	return FALSE;
}

Bool CheckMonitorSettingOutOfRange(void)
{
	if(
	    UserPrefBrightness > MaxBrightnessValue ||
	    UserPrefContrast > MaxContrastValue ||
	    UserPrefContrast < MinContrastValue ||
	    UserPrefECOMode  >= ECO_Nums ||
	    UserPrefColorTemp >= CTEMP_Nums ||
    #if AudioFunc
	    UserPrefVolume  > 100 ||
    #endif
	    UserPrefLanguage >= LANG_Nums ||
	    UserPrefOsdHStart > 100 ||
	    UserPrefOsdVStart > 100 ||
	    UserPrefOsdTime > 120 ||
	    UserPrefOsdTrans > 4 ||
    #if MWEFunction
	    UserPrefSubBrightness < MinSubBrightness ||
	    UserPrefSubBrightness > MaxSubBrightness ||
	    UserPrefSubContrast < MinSubContrast ||
	    UserPrefSubContrast > MaxSubContrast ||
	    UserPrefHue > 100 ||
    #endif
	    UserPrefDcrMode > 2 ||
	    UserPrefGamaMode >= GAMA_Nums ||
    #if ENABLE_RTE
	    UserPrefRTEMode >= RTE_Nums ||
    #endif
	    UserPrefInputType >= Input_Nums ||
	    UserPrefSharpness > MaxSharpness ||
	    UserPrefSharpness < MinSharpness
	)
		return TRUE;
	return FALSE;
}


#if USEFLASH
void Init_FactorySetting(void)
{
	#if ENABLE_AUTO_CLOLR_WITHOUT_INPUT
	FactoryAutoColorDone = 0;
	#endif
	UserPrefAdcPgaGain = DEF_ADC_PGA_GAIN;  	//110401 Modify
	UserPrefAdcRedGain = DEF_ADC_RED_GAIN;		//120105 Modify
	UserPrefAdcGreenGain = DEF_ADC_GREEN_GAIN;	//120105 Modify
	UserPrefAdcBlueGain = DEF_ADC_BLUE_GAIN;		//120105 Modify
	UserPrefAdcRedOffset = DEF_ADC_OFFSET;  	//110401 Modify
	UserPrefAdcGreenOffset = DEF_ADC_OFFSET;  	//110401 Modify
	UserPrefAdcBlueOffset = DEF_ADC_OFFSET;  	//110401 Modify
	UserPrefRedColorWarm1 = DefWarm_RedColor;
	UserPrefGreenColorWarm1 = DefWarm_GreenColor;
	UserPrefBlueColorWarm1 = DefWarm_BlueColor;
	UserPrefRedColorCool1 = DefCool_RedColor;
	UserPrefGreenColorCool1 = DefCool_GreenColor;
	UserPrefBlueColorCool1 = DefCool_BlueColor;
	#if CT_7500K_ENABLE
	UserPrefRedColorNormal = DefNormal_RedColor;
	UserPrefGreenColorNormal = DefNormal_GreenColor;
	UserPrefBlueColorNormal = DefNormal_BlueColor;
	#endif
	#if CT_sRGB_ENABLE
	UserPrefRedColorSRGB = DefsRGB_RedColor;
	UserPrefGreenColorSRGB = DefsRGB_GreenColor;
	UserPrefBlueColorSRGB = DefsRGB_BlueColor;
	#endif
	FactoryCheckSum = FLASH_CHECKSUM;
	#if 1//def WH_REQUEST
	if (FactoryProductModeValue == ProductModeOnValue)
		FactoryProductModeValue = ProductModeOnValue;
	else
	#endif
		FactoryProductModeValue = ProductModeOffValue;
	#if PanelminiLVDS || PANEL_VCOM_ADJUST	//110229 Modify
	UserPrefVcomValue = DEF_VCOM_VALUE;
	#endif
	#if	DisplayPowerOnLogo
	UserPrefLogoON = 1;	//120420 Modify
	#endif
	#if ENABLE_FACTORY_SSCADJ	//120305 Modify
	FactorySetting.SSCModulation = PANEL_SSC_MODULATION_DEF;
	FactorySetting.SSCPercentage = PANEL_SSC_PERCENTAGE_DEF;
	#endif
	//#ifdef SETTING_IN_FLASH_12K
	FactorySetting.Ident = FLASH_IDENTDATA;
	FactorySetting.CheckSum = FLASH_CHECKSUM;
	//#endif
}

void Init_MonitorSetting(void)
{
	UserPrefBrightness = DefBrightness;
	UserPrefContrast = DefContrast;
	UserPrefBrightnessUser = UserPrefBrightness;
	UserPrefContrastUser = UserPrefContrast;
	UserPrefRedColor = DefRedColor;
	UserPrefGreenColor = DefGreenColor;
	UserPrefBlueColor = DefBlueColor;
	UserPrefRedColorUser = DefRedColor;
	UserPrefGreenColorUser = DefGreenColor;
	UserPrefBlueColorUser = DefBlueColor;
	#if PresetMode_Enable
	UserPrefColorTemp_Preset	= CTEMP_Warm1;
	UserPrefBrightness_Preset 	= DefBrightness;
	UserPrefContrast_Preset 	= DefContrast;
	UserPrefGamaMode_Preset = GAMA1;
	#endif
	#if Enable_YMC
	UserPrefYColor = DefRedColor;
	UserPrefCColor = DefGreenColor;
	UserPrefMColor = DefBlueColor;
	#endif
	UserPrefECOMode = 0;
	UserPrefColorTemp = CTEMP_Warm1;//CTEMP_Warm1;
	UserPrefSharpness = DefSharpness;	//120105 Modify
	UserPrefLanguage = DefLanguage;
	UserPrefMuteState = 0;
	UserPrefVolume = DefVolume;
	UserPrefOsdHStart = DefOsdHPosValue;//50;
	UserPrefOsdVStart = DefOsdVPosValue;//50;
	UserPrefOsdTime = DefOsdTime;
	UserPrefOsdTrans = 0;		//120119 Modify
	#ifdef OffPower      //090331 xiandi.yu Auto Off Power
	UserPrefAutoPowerOff = 0;
	#endif
	UserPrefDcrMode = 0;
	UserPrefGamaMode = 0;
	#if ENABLE_RTE
	UserPrefRTEMode = DefRTEMode; //20150914 gyp
	#endif
	#if ENABLE_VGA_INPUT
	UserPrefInputType = Input_ANALOG;
	#else
	UserPrefInputType = Input_DIGHTAL1;
	#endif
	#if INPUT_TYPE == INPUT_1A
	UserPrefInputSelectType = INPUT_PRIORITY_VGA;
	#elif INPUT_TYPE == INPUT_1H
	UserPrefInputSelectType = INPUT_PRIORITY_HDMI;
	#else
	#if DISABLE_AUTO_SWITCH
	UserPrefInputSelectType = FIXED_PORT;
	#else
	UserPrefInputSelectType = INPUT_PRIORITY_AUTO; // 071221 modified for initial UserPrefInputSelectType
	#endif
	#endif
	UserPrefSavedModeIndex = NumberOfMode;
	#if ENABLE_FACTORY_BLACKLEVEL  ||   ENABLE_DDCCI_BLACKLEVEL
	UserprefRedBlackLevel = DefRedBlackLevel;
	UserprefGreenBlackLevel = DefGreenBlackLevel;
	UserprefBlueBlackLevel = DefBlueBlackLevel;
	#endif
	#if Enable_Expansion
	UserprefExpansionMode = DefExpansion;
	#endif
	#if MWEFunction
	//UserPrefMWE=OFF_W;
	UserPrefHue = DefHue;
	UserPrefSaturation = DefSaturation;
	UserPrefSubContrast = DefSubContrast;
	UserPrefSubBrightness = DefSubBrightness;
	// 2006/10/26 6:47PM by Emily     UserPrefSubSharpness = 11;
	//UserPrefSkinTone=OFF_SKIN;
	// 2006/10/26 6:48PM by Emily     UserPrefDLCMode = OFF_DLC;
	// UserPrefBFPosition =0;
	#endif
	//=======for AutoBacklight=====================
	// 2006/11/6 5:34PM by Emily      UserprefAutoModel=1;
	// 2006/11/6 5:33PM by Emily      UserprefCompareRange=8;
	// 2006/11/6 5:33PM by Emily      UserprefDiffHvalue=0x80;
	#if  ENABLE_RTE
	MonitorFlags = bPowerOnBit | bBurninModeBit | bDoBurninModeBit | bDCCCIONOBit | bFactoryModeBit | bOverDriveOnBit; //Benz 2007.4.23   20:32:00
	#else
	MonitorFlags = bPowerOnBit | bBurninModeBit | bDoBurninModeBit | bDCCCIONOBit | bFactoryModeBit; //Benz 2007.4.23   20:32:00
	#endif
	#if VGA_Write_EEPROM
	Set_Load_VGAEDID_Flag();
	#endif
	#if DVI_Write_EEPROM
	Set_Load_DVIEDID_Flag();
	#endif
	#if HDMI_Write_EEPROM
	Set_Load_HDMIEDID_Flag();
	#endif
	#if HDMI2_Write_EEPROM
	Set_Load_HDMI2EDID_Flag();
	#endif
	#if WriteSN_Functiom_New
	Clr_DDCCIReadLoadEDIDFlag();
	#endif
	#if ENABLE_FREESYNC
	#if FreeSyncMenu_Enable
	UserprefFreeSyncMode = FreeSyncStatues; //FreeSyncMenuItems_Off FreeSyncMenuItems_On
	#else
	UserprefFreeSyncMode = FreeSyncMenuItems_On;
	#endif
	#endif
	#if ENABLE_OSD_LowBlueLight
	UserprefLowBlueLightMode  = DEF_LowBlueLight_MODE;
	#endif
	MonitorSetting.checksum = FLASH_CHECKSUM;
}
void Init_ModeSetting(void)
{
	UserPrefHTotal = StandardModeHTotal;
	UserPrefHStart = StandardModeHStart;
	UserPrefVStart = StandardModeVStart;
	UserPrefAutoHStart = UserPrefHStart;
	UserPrefAutoVStart = StandardModeVStart; //2004/01/15 num11
	UserPrefPhase = 18;
	UserPrefAutoTimes = 0;
	#if USEFLASH
	ModeSetting.Index = SaveIndex;
	ModeSetting.Ident = FLASH_IDENTDATA;
	ModeSetting.checksum = FLASH_CHECKSUM;
	ModeSetting.HerFreq = 0xFFFF;
	ModeSetting.VerFreq = 0xFFFF;
	ModeSetting.VTotal = 0xFFFF;
	ModeSetting.Flags = 0xFF;
	#else
	ModeSetting.CheckSum = FLASH_CHECKSUM;
	#endif
}
void CheckColorValueRange(void)
{
	if (UserPrefContrast > MaxContrastValue || UserPrefContrast < MinContrastValue)
	{
		UserPrefContrast = DefContrast;
	}
	#if 1
	if (UserPrefRedColor > MaxColorValue)
		UserPrefRedColor = DefRedColor;
	if (UserPrefGreenColor > MaxColorValue)
		UserPrefGreenColor = DefGreenColor;
	if (UserPrefBlueColor > MaxColorValue)
		UserPrefBlueColor = DefBlueColor;
	#endif
}


void CheckModeSettingRange(void)
{
	if (abs(UserPrefHTotal - StandardModeHTotal) > 100)
	{
		UserPrefHTotal = StandardModeHTotal;
	}
	//  if (UserPrefHStart>2*StandardModeHStart)
	//    UserPrefHStart=StandardModeHStart;
	//  if (UserPrefVStart>2*StandardModeVStart)
	//    UserPrefVStart=StandardModeVStart;
	if (abs(UserPrefHStart - UserPrefAutoHStart) > 50)
		//2004/02/10 num1
	{
		UserPrefHStart = UserPrefAutoHStart;
	} //2004/02/10 num1
	if (UserPrefVStart > 2 * UserPrefAutoVStart)
		//2004/02/10 num1
	{
		UserPrefVStart = UserPrefAutoVStart;
	} //2004/02/10 num1
	UserPrefPhase &= MAX_PHASE_VALUE;
	if (/*UserPrefAutoTimes == 0 ||*/ abs(UserPrefHStart - UserPrefAutoHStart) > 50)
	{
		UserPrefAutoHStart = UserPrefHStart;
	}
}

void UserPref_EnableFlashSaveBit(BYTE ucFlag)
{
	ucFlashSaveState |= ucFlag;
}
void UserPref_FlashSaveFlagCheck(void)
{
	if(FlashSaveMonitorFlag)
	{
		Clr_FlashSaveMonitorFlag();
		Set_FlashForceSaveMonitorFlag();
	}
	if(FlashSaveModeFlag)
	{
		Clr_FlashSaveModeFlag();
		Set_FlashForceSaveModeFlag();
	}
	if(FlashSaveFactoryFlag)
	{
		Clr_FlashSaveFactoryFlag();
		Set_FlashForceSaveFactoryFlag();
	}
	if(FlashSaveMonitor2Flag)
	{
		Clr_FlashSaveMonitor2Flag();
		Set_FlashForceSaveMonitor2Flag();
	}
}

void UserPref_FlashDataSaving(void)
{
	if(FlashForceSaveMonitorFlag)
	{
		//USERP_printMsg("--UserPref_FlashDataSaving SaveMonitorSetting");
		Clr_FlashForceSaveMonitorFlag();
		SaveMonitorSetting();
	}
	if(FlashForceSaveModeFlag)
	{
		//USERP_printMsg("--UserPref_FlashDataSaving SaveModeSetting");
		Clr_FlashForceSaveModeFlag();
		SaveModeSetting();
	}
	if(FlashForceSaveFactoryFlag)
	{
		//USERP_printMsg("--UserPref_FlashDataSaving SaveFactorySetting");
		Clr_FlashForceSaveFactoryFlag();
		SaveFactorySetting();
	}
	if(FlashForceSaveMonitor2Flag)
	{
		//USERP_printMsg("--UserPref_FlashDataSaving SaveMonitorSetting2");
		Clr_FlashForceSaveMonitor2Flag();
		SaveMonitorSetting2();
	}
}
#if Display_Checksum
#define PROTECT_START_ADDR			0x02FFFEul
///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Read one byte from flash.
// <Returns> : Data value in the address
// <Parameter>:  -  <Flow>  -  <Description>
//-----------------------------------------------------------------------------
//  wAddr   -   In  -   Only in the same bank ot MsFlash.c
///////////////////////////////////////////////////////////////////////////////
//#define xfr_FlashCode_NVRom ((BYTE code*)0x0000)
void drvFlashWaitSPINotBusy(void);

BYTE FlashReadByte_CheckSum(DWORD address)
{
	SPI_SI_BUF[0]   = (SPI_MODE == SPI_MODE_FR) ? H_READ : READ;
	SPI_SI_BUF[1]   = (address >> 16) & 0xff;
	SPI_SI_BUF[2]   = (address >> 8) & 0xff;
	SPI_SI_BUF[3]   = address & 0xff;
	//2nd
	SPI_SI_BUF[4]   = RDSR;
	if(SPI_MODE == SPI_MODE_FR)
		SPI_SI_BUF[5]   = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
	SPI_CTRL1       = (EN_2ND_CMD | RDSR_IN_2ND | EN_AUTO_CHECK);
	SET_WBF_SIZE( (SPI_MODE == SPI_MODE_FR) ? 5 : 4, 1, 0);
	SET_WBF_SIZE( 5, 1, 0);
	SET_RBF_SIZE(1, 1, 0);
	SPI_TRIGGER     = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
	return SPI_SO_BUF[0];
}

void Checksum_Calculator(void)
{
	Code_checksun = (FlashReadByte_CheckSum(PROTECT_START_ADDR));
	Code_checksun = ((Code_checksun << 8) | (FlashReadByte_CheckSum(PROTECT_START_ADDR + 1)));
}
#endif

void Init_MonitorSetting2(void)
{
	MonitorSetting2.Ident = FLASH_IDENTDATA;
	#if Show_BackLightTimeValue
	MonitorSetting2.BacklighttimeS = 0;
	MonitorSetting2.BacklighttimeM = 0;
	MonitorSetting2.BacklighttimeH = 0;
	#endif
	MonitorSetting2.CheckSum = FLASH_CHECKSUM;
}
void SaveMonitorSetting(void)
{
	MonitorSetting.Ident = FLASH_IDENTDATA;
	MonitorSetting.checksum = FLASH_CHECKSUM;
	#if 0//Enable_Cache
	MCU_DisableCache();
	#endif
	Flash_WriteMonitorSet((BYTE*)&MonitorSetting, MonitorSettingSize);
	#if 0//Enable_Cache
	MCU_EnableCache();
	#endif
}
void SaveMonitorSetting2(void)
{
	MonitorSetting2.Ident = FLASH_IDENTDATA;
	MonitorSetting2.CheckSum = FLASH_CHECKSUM;
	#if 0//Enable_Cache
	MCU_DisableCache();
	#endif
	Flash_WriteMonitorSet2((BYTE*)&MonitorSetting2, MonitorSetting2Size);
	#if 0//Enable_Cache
	MCU_EnableCache();
	#endif
}
void SaveFactorySetting(void)
{
	FactorySetting.Ident = FLASH_IDENTDATA;
	FactorySetting.CheckSum = FLASH_CHECKSUM;
	#if 0//Enable_Cache
	MCU_DisableCache();
	#endif
	Flash_WriteFactorySet((BYTE*)&FactorySetting, FactorySettingSize);
	#if 0//Enable_Cache
	MCU_EnableCache();
	#endif
}

void SaveModeSetting(void)
{
	if (SrcInputType >= Input_Digital || SyncLossState())	//110424 Modify
		return;
	// USERP_printData("UserModeFlag %x",UserModeFlag);
	//USERP_printData("SaveIndex %x",SaveIndex);
	#if 0//Enable_Cache
	MCU_DisableCache();
	#endif
	if(UserModeFlag)
	{
		ModeSetting.Index = SaveIndex | BIT7; //|= 0x80;
		ModeSetting.HerFreq = HFreq(SrcHPeriod); //HFreq(tempHperiod);
		ModeSetting.VerFreq = VFreq(HFreq(SrcHPeriod), SrcVTotal);
		ModeSetting.Flags = (SrcFlags & 0x13);
		//USERP_printData("ModeSetting.Index %x",ModeSetting.Index);
	}
	else
	{
		ModeSetting.Index = SaveIndex = SrcModeIndex;
		ModeSetting.HerFreq = 0xFFFF;
		ModeSetting.VerFreq = 0xFFFF;
		ModeSetting.Flags = 0xFF;
	}
	ModeSetting.Ident = FLASH_IDENTDATA;
	ModeSetting.checksum = FLASH_CHECKSUM;
	if(UserModeFlag)
		Flash_WriteModeSet((SaveIndex | BIT7), (BYTE*)&ModeSetting);
	else
		Flash_WriteModeSet(SaveIndex, (BYTE*)&ModeSetting);
	ModeSetting.Index &= 0x7F;
	#if 0//Enable_Cache
	MCU_EnableCache();
	#endif
}

Bool IsFlashSettingAreaEmpty(BYTE EmptyValue)  //add  by lizzie.ding ,for check flashsetting empty
{
	BYTE i, j;
	for(i = 0; i < FDATA_DYNAMIC_SECTOR_NUM; i++)
	{
		for(j = 0; j < 10; j++)
		{
			if(FlashReadByte(FDATA_DYNAMIC_ADDR + FDATA_SECTOR_SIZE * i + j) != EmptyValue)	//130812 xiandi
				return FALSE;
		}
	}
	return TRUE;
}

void ReadMonitorSetting(void)
{
	BYTE xdata FlashEmptyFlag = 0;
	Flash_GetBufferAddr();
	Flash_AllocateBufferAddr();
	if(IsFlashSettingAreaEmpty(0x00) || IsFlashSettingAreaEmpty(0xFF)) //edit by lizzie.ding ,for make sure flashsetting empty
	{
		FlashEmptyFlag = 1;
	}
	Flash_CheckBufferType();
	#if Display_Checksum
	Checksum_Calculator();
	#endif
	if(!Flash_ReadMonitorSet((BYTE*)&MonitorSetting, MonitorSettingSize))
	{
		//printMsg(" RMS MonitorSetting initial");
		Init_MonitorSetting();
		if(FlashEmptyFlag)
		{
			UserPrefVolume = DefVolume; //PE Request
		}
		SaveMonitorSetting();
	}
	if (CheckMonitorSettingOutOfRange())
	{
		//USERP_printMsg(" CheckMonitorSettingOutOfRange initial");
		Init_MonitorSetting();
		SaveMonitorSetting();
	}
	if(!Flash_ReadFactorySet((BYTE*)&FactorySetting, FactorySettingSize))
	{
		//USERP_printMsg(" RMS FactorySetting initial");
		Init_FactorySetting();
		if(FlashEmptyFlag)
			FactoryProductModeValue = ProductModeOnValue;
		SaveFactorySetting();
	}
	if (CheckFactorySettingOutOfRange())
	{
		//USERP_printMsg(" CheckFactorySettingOutOfRange initial");
		Init_FactorySetting();
		SaveFactorySetting();
	}
	#if 0//EnablePanelServiceMenu
	if(!Flash_Read_Factory_KeySet(FLASH_KEY_PANEL, TRUE, 0x00, PanelSettingSize, (BYTE*)&PanelSetting, PanelSettingSize))	//110311 Modify
	{
		//USERP_printMsg(" RMS PanelSetting initial");
		Init_PanelSetting();
		SavePanelSetting();
	}
	if(CheckPanelSettingRange())
	{
		Init_PanelSetting();
		SavePanelSetting();
	}
	if( PanelPanelTypeNum == UseDefaultPanelValue )	//120112 Modify
		PanelSelect = 0;
	else
		PanelSelect = 1;
	#endif
	if(!Flash_ReadMonitorSet2((BYTE*)&MonitorSetting2, MonitorSetting2Size))
	{
		//USERP_printMsg(" RMS MonitorSetting2 initial");
		Init_MonitorSetting2();
		SaveMonitorSetting2();
	}
	//USERP_printData("	Backlighttime[%d]",MonitorSetting2.Backlighttime);
	#if DISABLE_AUTO_SWITCH
	UserPrefInputSelectType = FIXED_PORT;
	UserPrefInputType = FIXED_PORT;
	#endif
	SrcInputType = UserPrefInputType;//0909003
//-----------------------------------------------------------------
}

Bool ReadUserModeSetting(void)
{
	BYTE bFound = FALSE;
	WORD hFreq, vFreq;
	BYTE i;
	hFreq = HFreq(SrcHPeriod); //HFreq(tempHperiod);
	vFreq = VFreq(hFreq, SrcVTotal);
	// 20070426Albert.Search each user mode
	for (i = 0; i < UserModeNumber; i++)
	{
		Flash_ReadModeSet((i | BIT7), (BYTE*)&ModeSetting);	// BIT7 == (UserModeFlag<<1)
		if(ModeSetting.Ident == FLASH_IDENTDATA && ModeSetting.checksum == FLASH_CHECKSUM)
		{
			if (abs(hFreq - ModeSetting.HerFreq) < HFreq_Tol &&    abs(vFreq - ModeSetting.VerFreq) < VFreq_Tol &&
			        (SrcFlags & 0x13) == ModeSetting.Flags)
				break;
		}
	}
	// 20070426Albert,Init new Mode info
	if(i < UserModeNumber)
		bFound = TRUE;
	else
	{
		UserPrefSavedModeIndex = (UserPrefSavedModeIndex + 1) % UserModeNumber;
		SaveIndex = UserPrefSavedModeIndex;
		SaveMonitorSetting();
	}
	return bFound;
}

void ReadModeSetting(void)
{
	Bool bFound = FALSE;
	if (UserModeFlag)
		bFound = ReadUserModeSetting();
	else
	{
		SaveIndex = SrcModeIndex;
		bFound = Flash_ReadModeSet(SrcModeIndex, (BYTE*)&ModeSetting);
	}
	if (bFound)
	{
		//USERP_printMsg("mode setting found");
		//USERP_printData("Index=%d",ModeSetting.Index);
		//USERP_printData("AutoTimes=%d",ModeSetting.AutoTimes);
	}
	else
	{
		//USERP_printMsg("mode setting found fail");
		Init_ModeSetting();
		SaveModeSetting();
	}
	CheckModeSettingRange();
}




#else

void Init_FactorySetting(void)
{
	#if ENABLE_AUTO_CLOLR_WITHOUT_INPUT
	FactoryAutoColorDone = 0;
	#endif
	UserPrefAdcPgaGain = DEF_ADC_PGA_GAIN;  	//110401 Modify
	UserPrefAdcRedGain = DEF_ADC_RED_GAIN;		//120105 Modify
	UserPrefAdcGreenGain = DEF_ADC_GREEN_GAIN;	//120105 Modify
	UserPrefAdcBlueGain = DEF_ADC_BLUE_GAIN;		//120105 Modify
	UserPrefAdcRedOffset = DEF_ADC_OFFSET;  	//110401 Modify
	UserPrefAdcGreenOffset = DEF_ADC_OFFSET;  	//110401 Modify
	UserPrefAdcBlueOffset = DEF_ADC_OFFSET;  	//110401 Modify
	FUserPrefBrightnessWarm1 = DefBrightness;
	FUserPrefContrastWarm1 = DefContrast;
	UserPrefRedColorWarm1 = DefWarm_RedColor;
	UserPrefGreenColorWarm1 = DefWarm_GreenColor;
	UserPrefBlueColorWarm1 = DefWarm_BlueColor;
	FUserPrefBrightnessCool1 = DefBrightness;
	FUserPrefContrastCool1 = DefContrast;
	UserPrefRedColorCool1 = DefCool_RedColor;
	UserPrefGreenColorCool1 = DefCool_GreenColor;
	UserPrefBlueColorCool1 = DefCool_BlueColor;
	FUserPrefBrightnessNormal = DefBrightness;
	FUserPrefContrastNormal = DefContrast;
	UserPrefRedColorNormal = DefNormal_RedColor;
	UserPrefGreenColorNormal = DefNormal_GreenColor;
	UserPrefBlueColorNormal = DefNormal_BlueColor;
	UserPrefRedColorSRGB = DefsRGB_RedColor;
	UserPrefGreenColorSRGB = DefsRGB_GreenColor;
	UserPrefBlueColorSRGB = DefsRGB_BlueColor;
	FUserPrefBrightnessSRGB = DefBrightness;
	FUserPrefContrastSRGB = DefContrast;
	//FactoryCheckSum=FLASH_CHECKSUM;
	FactoryProductModeValue = ProductModeOffValue;
	#if PanelminiLVDS || PANEL_VCOM_ADJUST	//110229 Modify
	UserPrefVcomValue = DEF_VCOM_VALUE;
	#endif
	UserPrefLogoON = 1;	//120420 Modify
	#if ENABLE_FACTORY_SSCADJ	//120305 Modify
	FactorySetting.SSCModulation = PANEL_SSC_MODULATION_DEF;
	FactorySetting.SSCPercentage = PANEL_SSC_PERCENTAGE_DEF;
	#endif
	//#ifdef SETTING_IN_FLASH_12K
	FactorySetting.CheckSum = FactoryChecksumValue;
	//#endif
}

void Init_MonitorSetting(void)
{
	UserPrefBrightness = DefBrightness;
	UserPrefContrast = DefContrast;
	UserPrefRedColor = DefRedColor;
	UserPrefGreenColor = DefGreenColor;
	UserPrefBlueColor = DefBlueColor;
	UserPrefRedColorUser = DefRedColor;
	UserPrefGreenColorUser = DefGreenColor;
	UserPrefBlueColorUser = DefBlueColor;
	#if Enable_YMC
	UserPrefYColor = DefRedColor;
	UserPrefCColor = DefGreenColor;
	UserPrefMColor = DefBlueColor;
	#endif
	UserPrefBrightnessUser = UserPrefBrightness;
	UserPrefContrastUser = UserPrefContrast;
	UserPrefECOMode = 0;
	UserPrefColorTemp = DefColorTemp;//CTEMP_Warm1;//CTEMP_Warm1;
	UserPrefSharpness = DefSharpness;   //120105 Modify
	UserPrefLanguage = LANG_English;
	UserPrefMuteState = 0;
	UserPrefVolume = DefVolume;
	UserPrefOsdHStart = 50;
	UserPrefOsdVStart = 50;
	UserPrefOsdTime = DefOsdTime;
	UserPrefOsdTrans = 0;       //120119 Modify
	#ifdef OffPower      //090331 xiandi.yu Auto Off Power
	UserPrefAutoPowerOff = 0;
	#endif
	UserPrefDcrMode = 0;
	UserPrefGamaMode = 0;
	#if ENABLE_RTE
	UserPrefRTEMode = DefRTEMode; //20150914 GYP
	#endif
	#if 0
	#else
	#if (INPUT_TYPE == INPUT_2H) || (INPUT_TYPE == INPUT_1H)
	UserPrefInputType = Input_Digital;
	#else
	UserPrefInputType = Input_ANALOG;
	#endif
	#endif
	#if INPUT_TYPE == INPUT_1A
	UserPrefInputSelectType = INPUT_PRIORITY_VGA;
	#elif INPUT_TYPE == INPUT_1H
	UserPrefInputSelectType = INPUT_PRIORITY_HDMI;
	#else
	#if DISABLE_AUTO_SWITCH
	UserPrefInputSelectType = FIXED_PORT;
	#else
	UserPrefInputSelectType = INPUT_PRIORITY_AUTO; // 071221 modified for initial UserPrefInputSelectType
	#endif
	#endif
	UserPrefSavedModeIndex = NumberOfMode;
	#if DDCCI_ENABLE
	UserprefRedBlackLevel = DefRedBlackLevel;
	UserprefGreenBlackLevel = DefGreenBlackLevel;
	UserprefBlueBlackLevel = DefBlueBlackLevel;
	#endif
	#if Enable_Expansion
	UserprefExpansionMode = DefExpansion;
	#endif
	#if MWEFunction
	//UserPrefMWE=OFF_W;
	UserPrefHue = DefHue;
	UserPrefSaturation = DefSaturation;
	UserPrefSubContrast = DefSubContrast;
	UserPrefSubBrightness = DefSubBrightness;
	// 2006/10/26 6:47PM by Emily     UserPrefSubSharpness = 11;
	//UserPrefSkinTone=OFF_SKIN;
	// 2006/10/26 6:48PM by Emily     UserPrefDLCMode = OFF_DLC;
	// UserPrefBFPosition =0;
	#endif
	//=======for AutoBacklight=====================
	UserprefHistogram1 = 0x40;
	UserprefHistogram2 = 0xB0;
	UserprefALha = 50;
	UserprefBata = 50;
	// 2006/11/6 5:34PM by Emily      UserprefAutoModel=1;
	// 2006/11/6 5:33PM by Emily      UserprefCompareRange=8;
	// 2006/11/6 5:33PM by Emily      UserprefDiffHvalue=0x80;
	#if ENABLE_RTE
	MonitorFlags = bPowerOnBit | bBurninModeBit | bDCCCIONOBit | bOverDriveOnBit; //Benz 2007.4.23   20:32:00]
	#else
	MonitorFlags = bPowerOnBit | bBurninModeBit | bDCCCIONOBit; //Benz 2007.4.23   20:32:00
	#endif
	#if ENABLE_FREESYNC
	#if FreeSyncMenu_Enable
	UserprefFreeSyncMode = FreeSyncStatues; //FreeSyncMenuItems_Off FreeSyncMenuItems_On
	#else
	UserprefFreeSyncMode = FreeSyncMenuItems_On;
	#endif
	#endif
	#if ENABLE_OSD_LowBlueLight
	UserprefLowBlueLightMode  = DEF_LowBlueLight_MODE;
	#endif
	MonitorSetting.checksum = ChecksumValue;
}

void Init_ModeSetting(void)
{
	UserPrefHTotal = StandardModeHTotal;
	UserPrefHStart = StandardModeHStart;
	UserPrefVStart = StandardModeVStart;
	UserPrefAutoHStart = UserPrefHStart;
	UserPrefAutoVStart = StandardModeVStart; //2004/01/15 num11
	UserPrefPhase = 18;
	UserPrefAutoTimes = 0;
	ModeSetting.checksum = ChecksumValue;
}

void CheckColorValueRange(void)
{
	if (UserPrefContrast > MaxContrastValue || UserPrefContrast < MinContrastValue)
	{
		UserPrefContrast = DefContrast;
	}
	#if 1
	if (UserPrefRedColor > MaxColorValue)
		UserPrefRedColor = DefRedColor;
	if (UserPrefGreenColor > MaxColorValue)
		UserPrefGreenColor = DefGreenColor;
	if (UserPrefBlueColor > MaxColorValue)
		UserPrefBlueColor = DefBlueColor;
	#endif
}
void CheckMonitorSettingRange(void)
{
	CheckColorValueRange();
	UserPrefBrightness %= 101;
	UserPrefColorTemp %= CTEMP_Nums;
	UserPrefSharpness %= 11;
	UserPrefLanguage %= LANG_Nums;
	UserPrefInputType %= Input_Nums;
	UserPrefECOMode %= ECO_Nums; //Benz 2007.4.23   16:12:21
	UserPrefHue %= (MAX_VIDEO_HUE + 1);
	UserPrefSaturation %= (MAX_VIDEO_SATURATION + 1);
	UserPrefSubContrast %= 256;
	UserPrefSubBrightness %= 256;
	// 2006/10/26 6:47PM by Emily     UserPrefSubSharpness %= 16;
}
void CheckModeSettingRange(void)
{
	if (abs(UserPrefHTotal - StandardModeHTotal) > 100)
	{
		UserPrefHTotal = StandardModeHTotal;
	}
	//  if (UserPrefHStart>2*StandardModeHStart)
	//    UserPrefHStart=StandardModeHStart;
	//  if (UserPrefVStart>2*StandardModeVStart)
	//    UserPrefVStart=StandardModeVStart;
	if (abs(UserPrefHStart - UserPrefAutoHStart) > 50)
		//2004/02/10 num1
	{
		UserPrefHStart = UserPrefAutoHStart;
	} //2004/02/10 num1
	if (UserPrefVStart > 2 * UserPrefAutoVStart)
		//2004/02/10 num1
	{
		UserPrefVStart = UserPrefAutoVStart;
	} //2004/02/10 num1
	UserPrefPhase &= MAX_PHASE_VALUE;
	if (UserPrefAutoTimes == 0 || abs(UserPrefHStart - UserPrefAutoHStart) > 50)
	{
		UserPrefAutoHStart = UserPrefHStart;
	}
}
void SaveMonitorSetting(void)
{
	NVRam_WriteTbl(MonitorSettingAddr, (BYTE*) &MonitorSetting, MonitorSettingSize);
}

void SaveModeSetting(void)
{
	if (SrcInputType >= Input_Digital || SyncLossState())	//110424 Modify
		return;
	//NVRam_WriteTbl(nvrModeBaseAddr(SrcModeIndex), (BYTE*)&ModeSetting, ModeSettingSize);
	NVRam_WriteTbl( nvrModeBaseAddr( SaveIndex ), ( BYTE* ) &ModeSetting, ModeSettingSize );
	#if DEBUG_MSG
	//    printMsg( "Save SaveModeSetting" );
	#endif
}


void ReadMonitorSetting(void)
{
	BYTE tempValue, i;
	BYTE xdata EEPromEmptyFlag = 0;
	#if Display_Checksum
	Checksum_Calculator();
	#endif
	if(IsEEPRomEmpty(0xFF) || IsEEPRomEmpty(0x00))
	{
		//WORD temp=ProductModeOnValue;
		// NVRam_WriteTbl(ProductModeAddr, (BYTE*)(&temp), 2);
		NVRam_WriteWord(ProductModeAddr, ProductModeOnValue);
		Init_FactorySetting();
		SaveFactorySetting();
		Init_MonitorSetting();
		#if AudioFunc
		UserPrefVolume = DefVolume;
		#endif
		SaveMonitorSetting();
		#if 0//EnablePanelServiceMenu&&!USEFLASH
		Init_PanelSetting();
		SavePanelSetting();
		#endif
		EEPromEmptyFlag = 1;
	}
	CheckBoard(); //Benz 2007.4.24   23:28:02 Why?
	NVRam_ReadByte(nvrMonitorAddr(checksum), &tempValue);
	if (tempValue == ChecksumValue)
	{
		NVRam_ReadTbl(MonitorSettingAddr, (BYTE*) &MonitorSetting, MonitorSettingSize);
	}
	else
	{
		for(i = 0; i < 10; i++)
		{
			NVRam_ReadByte(nvrMonitorAddr(checksum), &tempValue);
			if (tempValue == ChecksumValue) // double check
			{
				NVRam_ReadTbl(MonitorSettingAddr, (BYTE*)&MonitorSetting, MonitorSettingSize);
				break;
			}
		}
		if(i == 10)
		{
			Init_MonitorSetting();
			if(EEPromEmptyFlag)
			{
				#if AudioFunc
				UserPrefVolume = DefVolume;
				#endif
			}
			SaveMonitorSetting();
		}
	}
	NVRam_ReadByte( nvrFactoryAddr( CheckSum ), &tempValue );
	if( tempValue == FactoryChecksumValue )
	{
		NVRam_ReadTbl( FactorySettingAddr, ( BYTE* ) &FactorySetting, FactorySettingSize );
	}
	else
	{
		for( i = 0; i < 10; i++ )
		{
			NVRam_ReadByte( nvrFactoryAddr( CheckSum ), &tempValue );
			if( tempValue == FactoryChecksumValue ) // double check
			{
				NVRam_ReadTbl( FactorySettingAddr, ( BYTE* )&FactorySetting, FactorySettingSize );
				break;
			}
		}
		if( i == 10 )
		{
			Init_FactorySetting();
			SaveFactorySetting();
		}
	}
	//************************************************************
	#if 0//EnablePanelServiceMenu	//120420 Modify
	{
		WORD temp;
		NVRam_ReadTbl(PanelTypeNumAddr, (BYTE*)(&temp), 2);
		if(temp == UseUserPanelValue)
		{
			PanelSelect = 1;
			//NVRam_ReadByte(nvrPanelAddr(CheckSum), &tempValue);
			NVRam_ReadTbl(PanelSettingAddr, (BYTE*) &PanelSetting, PanelSettingSize);
			if (PanelSetting.CheckSum == CalculateSettingCheckSum((BYTE *)(&PanelSetting) + PanelSettingChecksumSize, PanelSettingSize - PanelSettingChecksumSize))
			{
				//NVRam_ReadTbl(PanelSettingAddr, (BYTE*) &PanelSetting, PanelSettingSize);
				if(CheckPanelSettingRange())
				{
					Init_PanelSetting();
					SavePanelSetting();
				}
			}
			else
			{
				for(i = 0; i < 10; i++)
				{
					//NVRam_ReadByte(nvrPanelAddr(CheckSum), &tempValue);
					NVRam_ReadTbl(PanelSettingAddr, (BYTE*) &PanelSetting, PanelSettingSize);
					if (PanelSetting.CheckSum == (CalculateSettingCheckSum((BYTE *)(&PanelSetting) + PanelSettingChecksumSize, PanelSettingSize - PanelSettingChecksumSize) != PanelSetting.CheckSum))
					{
						NVRam_ReadTbl(PanelSettingAddr, (BYTE*) &PanelSetting, PanelSettingSize);
						if(CheckPanelSettingRange())
						{
							Init_PanelSetting();
							SavePanelSetting();
						}
						break;
					}
				}
				if(i == 10)
				{
					Init_PanelSetting();
					SavePanelSetting();
				}
			}
		}
		else
		{
			Init_PanelSetting();
			PanelSelect = 0;
		}
	}
	#endif
	//************************************************************
	CheckMonitorSettingRange();
	if( CheckMonitorSettingOutOfRange() )
	{
		Init_MonitorSetting();
		SaveMonitorSetting();
	}
	if( CheckFactorySettingOutOfRange() )
	{
		Init_FactorySetting();
		SaveFactorySetting();
	}
	#if DISABLE_AUTO_SWITCH
	UserPrefInputSelectType = FIXED_PORT;
	UserPrefInputType = FIXED_PORT;
	#endif
	SrcInputType = UserPrefInputType;
	{
		WORD temp;
		NVRam_ReadTbl(ProductModeAddr, (BYTE*)(&temp), 2);
	}
}
void GetModeSaveIndex(void)
{
	ModeInfoType modeInfo;
	BYTE i;
	WORD hFreq, vFreq;
	hFreq = HFreq( SrcHPeriod );
	vFreq = VFreq( hFreq, SrcVTotal );
	for( i = 0; i < NumberOfMode; i++ )
	{
		NVRam_ReadTbl( nvrModeInfoAddr( i ), ( BYTE* ) &modeInfo, ModeInfoSize );
		if( abs( hFreq - modeInfo.HerFreq ) < HFreq_Tol && abs( vFreq - modeInfo.VerFreq ) < VFreq_Tol
		        && abs( SrcVTotal - modeInfo.VTotal ) < 3 && ( SrcFlags & 0x13 ) == modeInfo.Flags )
		{
			#if DEBUG_MSG
			// printMsg( "found saveindex" );
			// printData( "SaveIndex=%d", i );
			#endif
			break;
		}
	}
	if( i >= NumberOfMode )
	{
		UserPrefSavedModeIndex = ( UserPrefSavedModeIndex + 1 ) % NumberOfMode;
		SaveIndex = UserPrefSavedModeIndex;
		modeInfo.HerFreq = hFreq;
		modeInfo.VerFreq = vFreq;
		modeInfo.VTotal = SrcVTotal;
		modeInfo.Flags = SrcFlags & 0x13;
		NVRam_WriteTbl( nvrModeInfoAddr( SaveIndex ), ( BYTE* ) &modeInfo, ModeInfoSize );
		NVRam_WriteByte( nvrModeAddr( checksum ), 0 );
		NVRam_WriteByte( nvrMonitorAddr( SavedModeIndex ), UserPrefSavedModeIndex );
	}
	else
	{
		SaveIndex = i;
	}
}

void ReadModeSetting(void)
{
	BYTE tempValue;
	if(CURRENT_INPUT_IS_VGA())//( SrcInputType < Input_Digital ) //if (SrcInputType != Input_Digital)
	{
		GetModeSaveIndex();
		NVRam_ReadByte( nvrModeAddr(checksum), &tempValue );
		if( tempValue == ChecksumValue )	//120612 Modify
		{
			#if DEBUG_MSG
			// printMsg( "mode setting found" );
			#endif
			NVRam_ReadTbl( nvrModeBaseAddr( SaveIndex ), ( BYTE* ) &ModeSetting, ModeSettingSize );
		}
		else
		{
			#if DEBUG_MSG
			// printMsg( "mode setting not found" );
			#endif
			Init_ModeSetting();
			SaveModeSetting();
		}
		CheckModeSettingRange();
	}
	else
	{
		Init_ModeSetting();
	}
}

Bool IsEEPRomEmpty(BYTE EmptyValue)
{
	BYTE tempValue, i;
	for ( i = 0; i < ModeSettingAddr - 1; i++ )
	{
		NVRam_ReadByte(i, &tempValue);
		if(tempValue == EmptyValue)
			continue;
		else
			return FALSE;
	}
	return TRUE;
}

void EraseEEPROM(void)
{
	NVRam_WriteByte(nvrMonitorAddr(checksum), 0);
	for (SaveIndex = 0; SaveIndex < NumberOfMode; SaveIndex++)
	{
		NVRam_WriteByte(nvrModeAddr(checksum), 0);
	}
//    SrcFlags |= bUserMode;
//    for (SaveIndex = 0; SaveIndex < NumberOfMode; SaveIndex++)
//    {
//        NVRam_WriteByte(nvrModeInfoAddr(checksum), 0);
//    }
	SrcFlags &= ~bUserMode;
	//  NVRam_WriteByte(Factory9300KBrightnessAddr, DefBrightness);
	//  NVRam_WriteByte(Factory6500KBrightnessAddr, DefBrightness);
	//  NVRam_WriteByte(Factory9300KContrastAddr, DefContrast);
	// NVRam_WriteByte(Factory6500KContrastAddr, DefContrast);
}
/**********
void CheckBoard(void)
{ BYTE tempValue;
NVRam_ReadByte(CheckBoardAddr, &tempValue);
if (tempValue!=BoardChecksum)
{ EraseEEPROM();
BlacklitTime=0;
SaveBlacklitTime();
NVRam_WriteByte(CheckBoardAddr, BoardChecksum);
}
else
ReadBlacklitTime();
}
 ************/
void CheckBoard(void)
{
	BYTE tempValue;
	BYTE i;
	NVRam_ReadByte( CheckBoardAddr, &tempValue );
	if ( tempValue != BoardChecksum )
	{
		for ( i = 0; i < 10; i++ )
		{
			NVRam_ReadByte( CheckBoardAddr, &tempValue );
			if ( tempValue == BoardChecksum )   // double check
			{
				ReadBlacklitTime();
				break;
			}
		}
		if ( i == 10 )
		{
			EraseEEPROM();
			BlacklitTime = 0;
			SaveBlacklitTime();
			NVRam_WriteByte( CheckBoardAddr, BoardChecksum );
		}
	}
	else
	{
		ReadBlacklitTime();
	}
}
void ReadBlacklitTime(void)
{
	NVRam_ReadTbl(BlacklitTimeAddr, (BYTE*)(&BlacklitTime), 4);
}

void SaveBlacklitTime(void)
{
	NVRam_WriteTbl(BlacklitTimeAddr, (BYTE*)(&BlacklitTime), 4);
}
#endif

