
#ifndef USERPREFDEF_H
#define USERPREFDEF_H
#include <stddef.h>
#include "board.h"
#include "panel.h"

#define ProductModeOnValue 0x55AA
#define ProductModeOffValue 0xBB99
#define FactoryChecksumValue   0xCC//0xBB

#define UseDefaultPanelValue 	0x55AA
#define UseUserPanelValue 	0xBB99

#ifdef DATA_LENGTH_20_BYTE
#define HDCP_BLOCK_LENGTH	20
#else
#define HDCP_BLOCK_LENGTH	5
#endif


typedef enum
{
	InputColor_RGB = 0,
	InputColor_YPBPR_444,
	InputColor_YPBPR_422,
	InputColor_Max
} InputColorType;

typedef enum
{
	YUV_Colorimetry_ITU601 = 0,
	YUV_Colorimetry_ITU709,
	YUV_Colorimetry_NoData,
	YUV_Colorimetry_Max
} InputYPBPRColorimetryType;
//======================20120814===================//

#if 0
typedef enum
{
	DEPTH_INWARD = 0,
	DEPTH_MIDDLE,
	DEPTH_OUTWARD,
	DEPTH_MAX
} ;

typedef enum
{
	SEPARATION_WEAK = 0,
	SEPARATION_MEDIUM,
	SEPARATION_STRONG,
	SEPARATION_MAX
} ;
#else
#define DEPTH_MAX	5               //2012.08.14 Stone.yu
#define SEPARATION_MAX	5
#define DefaultPnlOutLR				FALSE

#endif

enum
{
	OVERSCAN_4_3,           // overscan adjust by panel H/V 4:3 + Ext H/V
	OVERSCAN_16_9,          // overscan adjust by panel H/V 16:9 + Ext H/V
	OVERSCAN_FIXED,         // no overscan, fixed as input image ratio
	OVERSCAN_FIXED_RATIO,   // fixed cutting ratio of input image
	#if ENABLE_OVER_SCAN
	PC_SCALE_17Picth,
	PC_SCALE_19Picth,
	PC_SCALE_W19Picth,
	PC_SCALE_W21_5Picth,
	PC_SCALE_W22Picth,
	PC_SCALE_W23Picth,
	#endif
};

typedef struct
{
	BYTE Enable;
	BYTE AspRatio;
	BYTE ScanRatio;         // 0 ~ 100
	BYTE ImageRatio;        // 0 ~ 100
	int ExtH;
	int ExtV;
	WORD OverScanH;
	WORD OverScanV;
} OverScanType;

#if ENABLE_DeltaE
typedef struct
{
	BYTE CM[18];
	BYTE CalculateStatus; // record eeprom status, if done, this bit will be set.
} CSTransferSettingType;
#define ColorMatrixSize     sizeof(CSTransferSettingType)
#define GammaTblSize   64

#endif

//======================20120814===================//

#if 1
typedef struct
{
	BYTE Ident;
	// DWORD Backlighttime;
	#if Show_BackLightTimeValue
	BYTE BacklighttimeS;
	BYTE BacklighttimeM;
	WORD BacklighttimeH;
	#endif
	BYTE CheckSum;
} MonitorSettingType2;

typedef struct
{
	BYTE Ident;
	WORD MonitorFlag; // 0

	BYTE Brightness; // 1
	BYTE Contrast; //8
	BYTE ColorTemp; //9
	BYTE GamaMode;

	#if PresetMode_Enable
	BYTE Preset_Brightness; // 1
	BYTE Preset_Contrast; //8
	BYTE Preset_ColorTemp; //9
	BYTE Preset_GamaMode;
	#endif

	BYTE BrightnessUser; // 1
	BYTE ContrastUser; //8

	BYTE RedColor; //a
	BYTE GreenColor; //b
	BYTE BlueColor; //c

	BYTE RedColorUser; //d
	BYTE GreenColorUser; //e
	BYTE BlueColorUser; //f
	//BYTE LastMenuPage;
	#if MWEFunction
	BYTE Hue;
	BYTE Saturation;
	BYTE SubContrast;
	BYTE SubBrightness;
	#endif
	BYTE Sharpness;//13


	BYTE Volume;
	BYTE MuteState;

	BYTE ECOMode;
	BYTE Language; //14

	BYTE OsdHStart; //15
	BYTE OsdVStart; //16

	BYTE OsdTime; //17

	BYTE OsdTrans;
	#ifdef OffPower          //090331 xiandi.yu Auto Off Power
	BYTE AutoPowerOff;
	#endif

	BYTE DcrMode;
	BYTE InputType; //1b
	BYTE InputSelectType; //1b
	// 2006/10/24 7:17PM by Emily   BYTE BlackLevel; // 2 //1125

	#if ENABLE_FACTORY_BLACKLEVEL  ||   ENABLE_DDCCI_BLACKLEVEL
	BYTE RedBlackLevel;
	BYTE GreenBlackLevel;
	BYTE BlueBlackLevel;
	#endif

	BYTE SavedModeIndex;
	#if ENABLE_RTE
	BYTE RTEMode;
	#endif
	#if Enable_Expansion
	BYTE ExpansionMode;
	#endif

	//======for AutoBacklight================

	#if ENABLE_DP_INPUT
	//#message "Jemery 181206 try to delete"
	//BYTE DP_Lane;
	//BYTE DP_Speed;
	#endif


	#if ENABLE_FREESYNC
	BYTE FreeSyncMode;	  //Scar
	#endif
	#if ENABLE_OSD_LowBlueLight
	BYTE LowBlueLightMode;
	#endif



	#if  Enable_YCM_Mode
	BYTE YColor; //a
	BYTE CColor; //b
	BYTE MColor; //c
	#endif
	//DWORD BackLightTime;
	// 2006/11/6 5:34PM by Emily   BYTE  AutoModel;
	// 2006/11/6 5:33PM by Emily   BYTE  CompareRange;
	// 2006/11/6 5:34PM by Emily   BYTE  DiffHvalue;
	BYTE checksum; //1c
} MonitorSettingType;

typedef struct
{
	//#ifdef SETTING_IN_FLASH_12K
	BYTE Ident;

	//#endif
	BYTE AdcPgaGain;    //110401 Modify
	WORD AdcRedGain;
	WORD AdcGreenGain;
	WORD AdcBlueGain;
	WORD AdcRedOffset;
	WORD AdcGreenOffset;
	WORD AdcBlueOffset;

	BYTE RedColorWarm1; //d
	BYTE GreenColorWarm1; //e
	BYTE BlueColorWarm1; //f

	#if CT_7500K_ENABLE
	BYTE RedColorNormal; //10
	BYTE GreenColorNormal; //11
	BYTE BlueColorNormal; //12
	#endif

	BYTE RedColorCool1; //10
	BYTE GreenColorCool1; //11
	BYTE BlueColorCool1; //12

	#if CT_sRGB_ENABLE
	BYTE RedColorsRGB; //10
	BYTE GreenColorsRGB; //11
	BYTE BlueColorsRGB; //12
	#endif
	WORD ProductModeValue;
	#if PanelminiLVDS||PANEL_VCOM_ADJUST	//110229 Modify
	#if VCOM_TYPE == VCOM_MAXIM	|| VCOM_TYPE == VCOM_SMIM ||VCOM_TYPE == VCOM_TPSIM	//120322 Modify
	WORD VcomValue;
	#else
	BYTE VcomValue;
	#endif
	#endif
	#if DisplayPowerOnLogo
	BYTE LogoON;
	#endif
	#if ENABLE_FACTORY_SSCADJ	//120305 Modify
	BYTE SSCModulation;
	BYTE SSCPercentage;
	#endif
	#if ENABLE_AUTO_CLOLR_WITHOUT_INPUT
	BYTE ADC_AUTO_COLOR_DONE;
	#endif

	WORD Code_CheckSum;

	BYTE CheckSum; //1c
} FactorySettingType;

#if 1//def SETTING_IN_FLASH_12K
typedef struct
{
	BYTE Ident;
	BYTE Index;
	WORD HTotal;
	WORD HStart;
	WORD VStart;
	WORD AutoHStart;
	WORD AutoVStart;  //2004/01/15 num11
	BYTE Phase;
	BYTE AutoTimes;
	WORD HerFreq;
	WORD VerFreq;
	WORD VTotal;
	BYTE Flags;

	BYTE checksum;
} ModeSettingType;
#endif

typedef struct
{
	BYTE Ident;
	BYTE Index;
	WORD HerFreq;
	WORD VerFreq;
	WORD VTotal;
	BYTE Flags;
} ModeInfoType;

#if USEFLASH
#define MonitorSetting2Size	sizeof(MonitorSettingType2)
#endif

#define NVRamAddress_Base	0x0000
#define MonitorSettingSize	sizeof(MonitorSettingType)
#define FactorySettingSize	sizeof(FactorySettingType)
#define ModeSettingSize		sizeof(ModeSettingType)
#define ModeInfoSize		sizeof(ModeInfoType)

#define NumberOfMode		18
#define UserModeNumber		5
#define ChecksumValue	0xaa
#if ENABLE_DeltaE
#if ENABLE_USE_NewDeltaE
#define RM_COLORSPACE_TRANS_BASEADDR	0x600

#define RM_COLORSPACE_TRANS_BASEADDR 			0x600	//FACTORY_SETTING_ADDR + FACTORY_SETTING_SIZE,//0x320,//
#define RM_COLORSPACE_TRANS_BASEADDR_SRGB		RM_COLORSPACE_TRANS_BASEADDR
#define RM_COLORSPACE_TRANS_BASEADDR_Adobe		RM_COLORSPACE_TRANS_BASEADDR_SRGB+ColorMatrixSize
#else
#define RM_COLORSPACE_TRANS_BASEADDR 			0x800	//FACTORY_SETTING_ADDR + FACTORY_SETTING_SIZE,//0x320,//
#define RM_COLORSPACE_TRANS_BASEADDR_Adobe		RM_COLORSPACE_TRANS_BASEADDR
#define RM_COLORSPACE_TRANS_BASEADDR_SRGB		RM_COLORSPACE_TRANS_BASEADDR_Adobe+ColorMatrixSize
#endif
#define BGammaTblAddr 								RM_COLORSPACE_TRANS_BASEADDR + ColorMatrixSize * 2
#define BGammaTblEndAddr 							BGammaTblAddr + GammaTblSize
#endif



#endif
#endif
