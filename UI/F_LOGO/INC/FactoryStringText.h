#include "Panel.h"




ColorPaletteType code tOSDColorPaletteF[] =
{
	{0xFF, 0xFF, 0xFF,    CP_COLORKEY_F},  // Palette 0 // White
	{0xFF, 0x00, 0x00,    CP_COLORKEY_F},  // Palette 1 // Red
	{0xFF, 0x00, 0x00,    CP_COLORKEY_F},  // Palette 2 //lightblue Green
	{0x00, 0x00, 0xFF,    CP_COLORKEY_F},  // Palette 3 // Blue

	{0xFF, 0xFF, 0xFF,    CP_COLORKEY_F},  // Palette 0 // White
	{0xFF, 0x00, 0x00,    CP_COLORKEY_F},  // Palette 1 // Red
	{0x00, 0x80, 0xff,    CP_COLORKEY_F},  // Palette 2 //lightblue Green
	{0xFF, 0xFF, 0xFF,    CP_COLORKEY_F},  // Palette 3 // Blue

};





BYTE code strVersionDate[] =
{
	//123456789012345678901234567890
	"V"FWVersion
};

BYTE code strChangeDate[] =
{
	//123456789012345678901234567890
	ChangeDate
};
#ifdef  Brand
BYTE code strBrandName[] =
{
	//123456789012345678901234567890
	Brand
};
#endif

BYTE code strModelName[] =
{
	//123456789012345678901234567890
	Model
};

BYTE code strPanel[] =  //
{
	//123456789012345678901234567890
	PanelName
};


BYTE code strCheckSum[] =  //
{
	//123456789012345678901234567890
	"CheckSum"
};
#if AboutDSUBFunc_Enable
BYTE code strAutoColor[] =
{
	//123456789012345678901234567890
	"Auto Color"
};
BYTE code strPass[] =
{
	//123456789012345678901234567890
	"Pass"
};
BYTE code strFail[] =
{
	//123456789012345678901234567890
	"Fail"
};
BYTE code strAdcGain[] =
{
	//123456789012345678901234567890
	"Gain"
};
BYTE code strAdcOffset[] =
{
	//123456789012345678901234567890
	"Offset"
};
#endif

BYTE code strFactoryRed[] =
{
	//123456789012345678901234567890
	"R"
};
BYTE code strFactoryGreen[] =
{
	//123456789012345678901234567890
	"G"
};
BYTE code strFactoryBlue[] =
{
	//123456789012345678901234567890
	"B"
};

#if FOSD_Trans_ColorTemp
BYTE code strFCool1[] =
{
	//123456789012345678901234567890
	"9300"
};
BYTE code strFWarm1[] =
{
	//123456789012345678901234567890
	"6500"
};
#if CT_7500K_ENABLE
BYTE code strFNORMAL[] =
{
	//123456789012345678901234567890
	"5500"
};
#endif
#else
BYTE code strFCool1[] =
{
	//123456789012345678901234567890
	"Cool"
};
BYTE code strFWarm1[] =
{
	//123456789012345678901234567890
	"Warm"
};
#if CT_7500K_ENABLE
BYTE code strFNORMAL[] =
{
	//123456789012345678901234567890
	"Normal"
};
#endif
#endif

#if CT_sRGB_ENABLE
BYTE code strFsRGB[] =
{
	//123456789012345678901234567890
	"sRGB"
};
#endif

#ifdef ChipName
BYTE code strChipName[] =
{
	//123456789012345678901234567890
	ChipName//20140926 Gino
};
#else
BYTE code strChipName[] =
{
	//123456789012345678901234567890
	"MST "//20141013 alpha
};
#message "please implement ChipName for new model"
#endif    //20141015 alpha

BYTE code strFactoryBrightness[] =
{
	//123456789012345678901234567890
	"Bri"
};
BYTE code strFactoryContrast[] =
{
	//123456789012345678901234567890
	"Con"
};
BYTE code strBurnin[] =
{
	//123456789012345678901234567890
	"BurnIn"
};

#if ENABLE_FACTORY_BLACKLEVEL
BYTE code strBlacklevelText[] =
{
	"BLACK"
};
#endif

BYTE code strBackLight[] =
{
	"BackLight"
};

BYTE code strHour[] =
{
	"H"
};

BYTE code strMinute[] =
{
	"M"
};

#if !USEFLASH // 130829 larry
BYTE code strEraseEEPROM[] =
{
	//123456789012345678901234567890
	"Erase EEPROM"
};
#endif
#if F_ShowVsync_Enable
BYTE code strFreeSyncVsync[] =
{
	"V sync"
};
#endif

#if Enable_ProductModeAdjust
BYTE code strDFM[] =
{
	//123456789012345678901234567890
	"DFM"//_D,_F,_M,'\x0'//  20130503  from WH
};
#endif

BYTE code strOnOff[2][4] =
{
	//123456789012345678901234567890
	//  O    f   f
	{"Off"},
	//  O    n
	{"On "}
};

#if PanelminiLVDS || PANEL_VCOM_ADJUST	//110229 Modify
BYTE code strVCOM[] =
{
	//123456789012345678901234567890
	"VCOM"
};
#endif

#if ENABLE_FACTORY_SSCADJ	//120305 Modify
BYTE code strSpreadSpectrum[] =  //
{
	//123456789012345678901234567890
	"Spread spectrum"
};
BYTE code strFreq[] =  //
{
	//123456789012345678901234567890
	"Freq"
};
BYTE code strAmp[] =  //
{
	//123456789012345678901234567890
	"Amp"
};

#endif

//===============================================================================================================================================================================






