#ifndef MENUDEF_H
#define MENUDEF_H

#include "Board.h"
#define Multi_Number	1
#define Multi_Gauge 1
#define OnlyDrawColor	BIT7
#define OnlyDrawCode	BIT6

#define MONO_COLOR(FColor,BkColor)  ((FColor)<<4|(BkColor))
#define FOUR_COLOR(ColorGroup)      ((ColorGroup)<<2)
#define EIGHT_COLOR(ColorGroup)     ((ColorGroup)<<3)

#define SpaceFont			0x01

//========================================================================
#define Color_2  0x01
#define Color_4  0x02
#define Color_8  0x03
#define Color_2T  0x04    //Transparent
#define Color_4T  0x05    //Transparent
#define Color_8T  0x06    //Transparent
#define Color_2G  0x07  //Gradual
#define Color_8G  0x08  //Gradual


typedef enum
{
	CP_WhiteColor = 0x07,
	CP_RedColor = 0x01,
	CP_LightBlue,
	CP_BlueColor,
	CP_WhiteColor1,
	CP_GrayColor,
	CP_LightColor,
	CP_BlackColor,
	CP_MaxColor
} CP_ColorType;


typedef enum
{
	PowerOffMenu,           // 0
	PowerOnMenu,            // 1
	StandbyMenu,		    // 2
	//	SuspenMenu,
	SleepMenu,              // 3
	CableNotConnectedMenu,  // 4
	UnsupportedModeMenu,    // 5
	RootMenu, 		        // 6

	// user definition from here
	MainMenu, 	        // 7

	OSD_BriContrastMenu,   	// 8
	PictureMenu,  				//  9
	RGBColorMenu,			//  10
	OsdMenu, 					//  11
	SettingMenu, 				//    13
	OSD_MiscMenu,  			 // 	14

	ExitMenu,                             //15
//-----------------------------------------------
	BrightnessMenu,     //
	ContrastMenu,       //
	ECOMenu,            // 11
	DCRMenu,            // 13
	#if ENABLE_RTE
	OverdriveMenu,
	#endif

	#if Enable_Gamma
	GammaMenu,          // 12
	#endif
//-----------------------------------------------
	HPositionMenu,
	VPositionMenu,
	FocusMenu,
	ClockMenu,
	#if Enable_Func_AdjExpansion
	ExpansionMenu,
	#endif
//-----------------------------------------------

	ColorTempMenu, RedMenu, GreenMenu, BlueMenu,    // 21,22,23,24
	#if ENABLE_OSD_LowBlueLight
	LowBlueLightMenu,
	#endif
//-----------------------------------------------
	LanguageMenu,
	#if OsdAdjustHVPos_Enable
	OsdHPositionMenu, OsdVPositionMenu,
	#endif
	OsdTimeOutMenu, //35,36,37,38
	TransparenceMenu,   //39
//------------------------------------------------
	#ifdef OffPower
	OffTimerMenu,
	#endif
//-----------------------------------------------
	#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
	InputSelectMenu,
	#endif
	#if AudioFunc
	#if EANBLE_MUTE_ON_OFF
	MuteMenu,
	#endif
	VolumeMenu, // 55
	#endif
	#if Enable_Adjust_SharpnessMenu
	SharpnessMenu,
	#endif

	#if  DDCCI_ENABLE && DDCCCIMenu_Enable
	DDCCIMenu,
	#endif
	#if  FreeSyncMenu_Enable
	FreeSyncMenu,
	#endif
//-----------------------------------------------



	HotKeyECOMenu, // 54
	#if Hotkey_DCR_Enable
	HotKeyDCRMenu, // 54
	#endif

	#if HotExpansionAdjust
	HotExpansionMenu,
	#endif
	#if AudioFunc && ENABLE_OSD_HotKeyVolume
	HotKeyVolMenu, // 55
	#endif
	#if Hotkey_Bri_Enable
	HotKeyBriMenu,
	#endif
	#if Hotkey_Con_Enable
	HotKeyConMenu,
	#endif

	#if HotInputSelect
	HotInputSelectMenu,
	#endif

	#if Hot_Corss_ColorSelect || Hot_Corss_FY_ColorSelect || Hot_Corss_FND_Select
	HotCorssMenu,
	#endif


	AutoMenu,//57

	#if AboutDSUBFunc_Enable
	AutoColorMenu,	//59
	#endif
	BurninMenu,//60

	FactoryMenu,//	61

	LogoMenu, 	//62

	InputInfoMenu, // 63

	#if DDCCI_ENABLE && DDCCCIMenu_Enable
	DdcciInfoMenu, // 65
	#endif

	// user definition end
	#ifdef OffPower
	OffPowerWarningMenu,
	#endif


	MaxMenu
} MenuPageIndexType;

typedef enum
{
	COLORBOOST_FULL,       //4 //1
	COLORBOOST_HALF,    // 2
	COLORBOOST_OFF,   // 3
	COLORBOOST_Nums

} ColorBoostType;




typedef enum
{
	ECO_Standard,       //4 //1
	ECO_Internet,   // 2
	ECO_Game,        // 3
	#if ENABLE_FPS_RTS
	ECO_FPS,        // 4
	ECO_RTS,        // 5
	#endif
	ECO_Movie,        // 4
	#if	PresetMode_Enable
	ECO_Preset,
	#endif
	ECO_Nums

} ECOModeType;

#if Enable_Expansion
typedef enum
{
	Expansion_Full,
	Expansion_Aspect,
	#if ENABLE_OVER_SCAN // 1:1
	Expansion_11,
	PIC_FORMAT_17Picth,
	PIC_FORMAT_19Picth,
	PIC_FORMAT_W19Picth,
	PIC_FORMAT_W21_5Picth,
	PIC_FORMAT_W22Picth,
	PIC_FORMAT_W23Picth,
	#endif
	Expansion_Nums
} ExpansionType;
#endif

typedef enum
{
	CTEMP_Warm1,	// 6500
	#if CT_7500K_ENABLE
	CTEMP_Normal,  // 7500K
	#endif
	CTEMP_Cool1,   //  9300K
	#if CT_sRGB_ENABLE
	CTEMP_SRGB,   //  SRGB
	#endif
	CTEMP_USER,	//  USER
	#if LowBlueLightType ==  LowBlueLight_SharpFunc
	CTEMP_LowBlue,
	#endif
	CTEMP_Nums
} ColorTempType;

typedef enum
{
	DISP_LANG_English,
	DISP_LANG_France,
	DISP_LANG_Spanish,
	DISP_LANG_Portugues,
	DISP_LANG_German,
	DISP_LANG_Italian,
	DISP_LANG_Dutch,
	DISP_LANG_Swedish,
	DISP_LANG_Finnish,
	DISP_LANG_Polish,
	DISP_LANG_Czech,
	DISP_LANG_Russia,
	DISP_LANG_Korea,
	DISP_LANG_TChina,
	DISP_LANG_SChina,
	DISP_LANG_Japan,
	DISP_LANG_Nums
} DisplayLanguageType;		//120322 Modify
typedef enum
{
	LANG_English,
	LANG_France,
	LANG_Spanish,
	LANG_Portugues,
	LANG_German,
	LANG_Italian,
	LANG_Dutch,
	LANG_Swedish,
	LANG_Finnish,
	LANG_Polish,
	LANG_Czech,
	LANG_Russia,
	LANG_Korea,
	LANG_TChina,
	LANG_SChina,
	LANG_Japan,
	LANG_Nums
} LanguageType;


typedef enum
{
	GAMA1,          // 0
	GAMA2,   // 1
	GAMA3,        // 2

	GAMA_Nums
} GAMAModeType;

typedef enum
{
	GAMAContent_GAMA1,          // 0
	GAMAContent_GAMA2,   // 1
	GAMAContent_GAMA3,        // 2
	GAMAContent_GAMA_sRGB,

	GAMAContent_GAMA_Nums
} GAMAContentType;


typedef enum
{
	OFF,          // 0ff
	RTE1,         // 1Weak
	RTE_Nums
} RTEModeType;



typedef enum
{
	MIA_Nothing,
	MIA_GotoNext, // goto next
	MIA_GotoPrev, // goto prev
	MIA_PrevItem,
	MIA_NextItem,
	MIA_JumpNaviItem,
	MIA_JumpAdjustItem,
	MIA_Exit, // Exit
	MIA_IncValue, // increase value
	MIA_DecValue, // decrease value
	MIA_ExecFunc, // 10
	MIA_Auto,

	MIA_InvIncValue,
	MIA_InvDecValue,
	MIA_RedrawMenu,
	MIA_GotoECO,

	#if Hotkey_ECO_Enable
	MIA_ECO, // 19
	#endif
	#if HotInputSelect
	MIA_ShowHotInput,
	#endif
	MIA_Expansion,
	#if AudioFunc && ENABLE_OSD_HotKeyVolume
	MIA_VOL,
	#endif
	#if Hotkey_Bri_Enable
	MIA_Brite,
	#endif
	#if Hotkey_Con_Enable
	MIA_Cont,
	#endif
	#if Hot_Corss_ColorSelect || Hot_Corss_FY_ColorSelect || Hot_Corss_FND_Select
	MIA_HotCorssMenu,
	#endif
	MIA_DCR,

	MIA_DDC,
	MIA_SourceSel, //2006-02-22
	MIA_Power, // power control
} MenuItemActionType;


typedef enum
{
	DWI_Nothing,
	DWI_Icon,
	DWI_Text,
	DWI_FullText,
	DWI_CenterText,
	DWI_FullCenterText,
	DWI_CenterPropText,
	#if Hot_Corss_ColorSelect
	DWI_8x5Icon,
	#elif Hot_Corss_FY_ColorSelect|| Hot_Corss_FND_Select
	DWI_10x6Icon,
	#endif
	DWI_None
} DrawMenuItemType;


typedef enum
{
	SUB_WIN_00,
	SUB_WIN_01,
	SUB_WIN_02,
	SUB_WIN_03

} SubWinType;




#define MonoFontStart       0x00
#define MonoSpace           0x01
#define MonoFrame_LT        0x02
#define MonoFrame_RT        0x03
#define MonoFrame_LD        0x04
#define MonoFrame_RD        0x05

#define MenuFrame_TopSide	0x06
#define MenuFrame_BottomSide	0x07
#define MenuFrame_LeftSide	0x08
#define MenuFrame_RightSide	0x09

#define MenuFrame_LeftSide_1	0x0A
#define MenuFrame_LeftSide_2	0x0B
#define MenuFrame_LeftSide_3	0x0E

#define MenuFrame_RightSide_1	0x0C
#define MenuFrame_RightSide_2	MenuFrame_RightSide
#define MenuFrame_RightSide_3	0x0D

#define AutoMenuFrameLeftSide_1		MenuFrame_LeftSide_1
#define AutoMenuFrameLeftSide_2		MenuFrame_LeftSide_2
#define AutoMenuFrameLeftSide_3		MenuFrame_LeftSide_3
#define AutoMenuFrameRightSide_1		MenuFrame_RightSide_1
#define AutoMenuFrameRightSide_2		MenuFrame_RightSide_2
#define AutoMenuFrameRightSide_3		MenuFrame_RightSide_3
#define AutoMenuFrameMide_Top			0x10
#define AutoMenuFrameMide_Bottom		0x0F


#define MonoMark_Left		0x1E
#define MonoMark_Right 		0x1F

#define FfontStart                  0x20   //100907 aoivd overlap with arrow


#define MonoNumberStart 	0x21
#define PropFontAddress		0x2C
#define MainAddress			0xC0

#define LanguageAddress		0xF8
//=================================================page2

#define MonoGuageFontStar           0x00//0x100


#define ResoulationAddress  0x20//0x120


//=================================================page3

#define FONT_4COLOR_ICON_START 	0x000
#define FONT_8COLOR_ICON_START	0x045//0x2E

#define _4ColorFontStart            FONT_4COLOR_ICON_START//0x180
#define _8ColorFontStart            FONT_8COLOR_ICON_START//0x200

#define _4ColorHotIconStart      _4ColorFontStart

#define _4ColorMainIconStart      _4ColorHotIconStart+30

#define _8ColorMainIconStart      _8ColorFontStart

#define _8ColorHotIconStart       _8ColorFontStart+54



#if Hot_Corss_ColorSelect

#define CorssAddr	0x90


#define HotCorssXsize	8
#define HotCorssYsize	5

#elif   Hot_Corss_FY_ColorSelect || Hot_Corss_FND_Select
#define CorssAddr	0x90


#define HotCorssXsize	10
#define HotCorssYsize	6
#endif



#if 1

#if OsdHelpKeyType==OsdHelpKey_Right
#define MAIN_MENU_H_SIZE            0x2D//1368 pixel
#define MAIN_MENU_V_SIZE            0x10
#else
#define MAIN_MENU_H_SIZE            0x29//1368 pixel
#define MAIN_MENU_V_SIZE            0x12
#endif

#define MainMenuIcon_DrawXPos		0x01
#define MainMenuIcon_DrawYPos		0x03

#define SUB_TEXT_XPOS		0x07
#define SUB_TEXT_YPOS		0x04
#define IconShift			0x02


#define HOT_MENU_H_SIZE            0x18
#define HOT_MENU_V_SIZE            7

#define IconXPos    4
#define IconFristXPos    IconXPos	// Jun 20130730

#define ItemShiftSpace      40

#define GaugeXPosition      0x18
#define NumXposion           0x20
#define DrawStarXPos		 0x0E

#define OFFTIMER_VALUE_XPOS 	26		// Jun 20130730

#define CENTER_ALIGN_LEN            13
#define CENTER_ALIGN_STARTPOS       (GaugeXPosition-8)//11
#define CENTER_ALIGN_ENDPOS         (CENTER_ALIGN_STARTPOS+CENTER_ALIGN_LEN-1)//23


#define INPUTSELECT_VALUE_XPOS 	0x11	// Jun 20130730
#define DDCCI_VALUE_XPOS 	0x39		// Jun 20130730
#define IMAGERATIO_VALUE_XPOS 	0x39	// Jun 20130730
#define RESET_VALUE_XPOS 	0x39		// Jun 20130730

#endif

#define HotIconXPos    10
#define HotIconYPos    2






typedef enum
{
	#if CHIP_ID>=CHIP_TSUMV
	CPC_Color0,
	#else
	CPC_ColorF,
	#endif
	CPC_Color1,
	CPC_Color2,
	CPC_Color3,

	CPC_Color4,
	CPC_Color5,
	CPC_Color6,
	CPC_Color7,

	CPC_Color8,
	CPC_Color9,
	CPC_ColorA,
	CPC_ColorB,

	CPC_ColorC,
	CPC_ColorD,
	CPC_ColorE,
	#if CHIP_ID>=CHIP_TSUMV
	CPC_ColorF,
	#else
	CPC_Color0,
	#endif

	CPC_MaxColor
} CPC_ColorType;

#define CPC_TranColor           CPC_Color0//0x00
#define CPC_GrayColor           CPC_Color8//0x08
#define CPC_Background          CPC_ColorE//0x0F

#define CP_SelectItem         CPC_ColorF<<4|CPC_Background//0x2F
#define CP_UnselectItem     CPC_ColorC<<4|CPC_Background//0x2F
#define CP_DisableItem      CPC_ColorD<<4|CPC_Background//0x4F

#define CP_ExecItem         CPC_Color3<<4|CPC_Background//0x3F


#define CP_SelectIcon       0x80//128=16x8
#define CP_UnselectIcon     0x08//8=1x8

#define CP_MainUnselectItem     CPC_Color7<<4|CPC_Color8//0x78
#define CP_MainSelectItem       CPC_Color2<<4|CPC_Color8//0x28
#define CP_MainEnterItem        CPC_Color4<<4|CPC_Color8//0x48




typedef enum
{
	MAIN_BriContrast_ITEM,
	MAIN_Picture_ITEM,
	MAIN_RGBColor_ITEM,
	MAIN_Osd_ITEM,
	MAIN_Setting_ITEM,
	MAIN_Misc_ITEM,

	MAIN_MAX_ITEM,
} MainMenuItemsType;

typedef enum
{
	BriContrast_BRIGHTNESS_ITEM,
	BriContrast_CONTRAST_ITEM,
	BriContrast_ECO_ITEM,
	BriContrast_DCR_ITEM,

	#if !PresetMode_Enable
	#if ENABLE_RTE
	BriContrast_Overdrive_ITEM,
	#endif
	#endif

	#if Enable_Gamma
	#if  !PresetMode_Enable
	BriContrast_GAMMA_ITEM,
	#endif
	#endif
	BriContrast_MAX_ITEM,
} BriContrastMenuItemsType;

typedef enum
{
	Picture_HPOSITION_ITEM,
	Picture_VPOSITION_ITEM,
	Picture_CLOCK_ITEM,
	Picture_PHASE_ITEM,
	#if Enable_Func_AdjExpansion
	Picture_IMAGERATIO_ITEM,
	#endif
	Picture_MAX_ITEM,
} PictureMenuItemsType;

typedef enum
{
	RGB_ColorTemp_Item,
	RGB_Red_Item,
	RGB_Green_Item,
	RGB_Blue_Item,
	#if LowBlueLightType==LowBlueLight_ColorTemp || LowBlueLightType==LowBlueLight_SharpFunc
	RGB_LowBlueLigth_Item,
	#endif
	RGB_MAX_Item,
} RGBMenuItemsType;


typedef enum
{
	OSD_LANGUAGE_ITEM,
	#if OsdAdjustHVPos_Enable
	OSD_HPOSITION_ITEM,
	OSD_VPOSITION_ITEM,
	#endif
	OSD_TIMEOUT_ITEM,
	OSD_TRANSPARENCE_ITEM,
	OSD_MAX_ITEM,
} OSDMenuItemsType;

typedef enum
{
	#if AboutDSUBFunc_Enable
	Setting_AUTOCONFIG_ITEM,
	Setting_AUTOCOLOR_ITEM,
	#endif
	Setting_RESTR_ITEM,
	#ifdef OffPower
	Setting_OffPower_ITEM,
	#endif
	Setting_MAX_ITEM,
} SettingMenuItemsType;

typedef enum
{
	#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
	Misc_InputSource_ITEM,
	#endif
	#if AudioFunc
	#if EANBLE_MUTE_ON_OFF
	Misc_Mute_ITEM,
	#endif
	Misc_Volume_ITEM,
	#endif
	#if Enable_Adjust_SharpnessMenu
	Misc_Sharpness_ITEM,
	#endif

	#if DDCCCIMenu_Enable
	Misc_DDCCI_ITEM,
	#endif

	#if PresetMode_Enable
	#if ENABLE_RTE
	Misc_Overdrive_ITEM,
	#endif
	#endif

	#if (LowBlueLightType==LowBlueLight_Misc_Guage)||(LowBlueLightType==LowBlueLight_Misc_Group)
	Misc_LowBlueLigth_Item,
	#endif

	#if  FreeSyncMenu_Enable
	Misc_FreeSync_ITEM,
	#endif
	Misc_MAX_ITEM,
} MiscMenuItemsType;


typedef enum
{
	#if ENABLE_VGA
	HotInput_VGA_ITEM,
	#endif
	#if ENABLE_DVI
	HotInput_DVI_ITEM,
	#endif
	#if ENABLE_HDMI
	HotInput_HDMI_ITEM,
	#endif
	#if ENABLE_HDMI2
	HotInput_HDMI2_ITEM,
	#endif
	#if ENABLE_DP_INPUT
	HotInput_DP_ITEM,
	#endif
	HotInput_MAX_ITEM
} HotInputSelectMenuItemsType;
































typedef BYTE *(*fpDisplayText)(void);
typedef Bool(*fpExecFunc)(void);
typedef BYTE(*fpItemIndex)(void);
typedef Bool(*fpAdjustValue)(MenuItemActionType action);
typedef WORD(*fpGetValue)(void);
typedef WORD(*fpGetMaxValue)(void);
typedef WORD(*fpSetMaxValue)(void);


/*************************************************************/
#define mpbStay 	    0x01 // for stay in menu page
#define mpbInvisible    0x02 // menu page visible or not
#define mpbBrowse		0x04
//#define mpbClrInner	      0x08
#define mpbRedraw		0x10
#define mpbMoving		0x20
#define mpbCenter		0x40

#define mpbClrGroup   	0x80
/*************************************************************/



#define mibSelectable	0x01 // for menu item selectable
#define mibInvisible	0x02 // for menu item selectable
#define mibDVIDisable	0x04
#define mibFactoryItem	0x08
#if Enable_Expansion
#define mibExpansionDisable 0x10
#endif
#define mibsRGBDisable  0x20
#define MIB_LOWBLUEDISABLE		0x40
#define mibDrawValue	0x80
#define mibUserColor 		0x0100
#define mibBFEnable 		0x0200
#define mibStdEnable    	0x0400
#define mibDCRDisable   	0x0800

#define mibAutioDisable   	0x1000



#if 0
#else
#if (ENABLE_RTE)		//130402 Modify
#define mibODDisable 0x2000
#endif

#if FreeSyncMenu_Enable
#define mibFreeSyncDisable  		0x8000
#endif

#endif

#define dwiNumber	    0x01
#define dwiGauge	    0x02
#define dwiRadioGroup   0x04
#define dwiEnd		    0x08
#define dwiHex		    0x10
#define dwiCenterArrowAlign 0x20

#define dwiCenterText         0x40

#define dwiMainTitle         0x80

#if (ENABLE_DUAL_LINK)&&(ENABLE_RTE)		//130402 Modify
#if ENABLE_120Hz_OD
#define Disabe_Overdrive_Item		( GetVfreq() > 85&&!( g_SetupPathInfo.wImgSizeOutH==PanelWidth && g_SetupPathInfo.wImgSizeOutV==PanelHeight )&&(UserprefExpansionMode !=Expansion_Aspect))
#else
#define Disabe_Overdrive_Item		(( GetVfreq() > 85 )&&(!ENABLE_FREESYNC))
#endif
#endif
typedef struct
{
	fpAdjustValue AdjustFunction;
	fpExecFunc ExecFunction;
} MenuItemFuncType;
#if Multi_Number //multi-number
typedef struct
{
	BYTE Flags;
	BYTE XPos, YPos;
	fpGetValue GetValue;
} NumberType;
typedef struct
{
	// BYTE Flags;
	BYTE ForeColor, BackColor;
	NumberType *DisplayNumber;
} DrawNumberType;
#else // single number
typedef struct
{
	BYTE Flags;
	BYTE ForeColor, BackColor;
	BYTE XPos, YPos;
	fpGetValue GetValue;
} DrawNumberType;
#endif
#if Multi_Gauge // multi-gauge
typedef struct
{
	BYTE Flags;
	BYTE XPos, YPos;
	fpGetValue GetValue;
} GaugeType;
typedef struct
{
	//BYTE Flags;
	BYTE ForeColor, BackColor;
	BYTE Length;
	GaugeType *DisplayGauge;
} DrawGuageType;
#else // single gauge
typedef struct
{
	BYTE Flags;
	BYTE ForeColor, BackColor;
	BYTE Length;
	BYTE XPos, YPos;
	fpGetValue GetValue;
} DrawGuageType;
#endif
typedef struct
{
	BYTE Flags;
	BYTE XPos, YPos;
	fpDisplayText DisplayText;
} RadioTextType;
typedef struct
{
	// BYTE Flags;
	BYTE ForeColor, BackColor;
	fpGetValue GetValue;
	RadioTextType *RadioText;
} DrawRadioGroupType;
typedef struct
{
	DrawNumberType *DrawNumber;
	DrawGuageType *DrawGuage;
	DrawRadioGroupType *DrawRadioGroup;
} DrawValueType;
typedef struct
{
	BYTE *Fonts;
	WORD FontCount;
} MenuFontType;
#if 0
typedef struct
{
	BYTE XPos, YPos;
	BYTE ForeColor, BackColor;
	BYTE SelForeColor, SelBackColor;
	BYTE NextPage;
	DrawMenuItemType DrawItemMethod;
	fpDisplayText DisplayText;
	MenuItemActionType *KeyEvents;
	MenuItemFuncType KeyFunction;
	DrawValueType DisplayValue;
	BYTE Flags;
} MenuItemType;
#endif
typedef struct
{
	BYTE XPos, YPos;
	BYTE ForeColor, BackColor;
	BYTE SelForeColor, SelBackColor;
	BYTE NextPage;
	DrawMenuItemType DrawItemMethod;
	fpDisplayText DisplayText;
	MenuItemActionType *KeyEvents;
	MenuItemFuncType KeyFunction;
	DrawValueType DisplayValue;
	MenuFontType *Fonts;
	DWORD Flags; // 2006/9/6 5:41PM by Emily BYTE Flags;
} MenuItemType;
#if 0
typedef struct
{
	BYTE SpaceWidth;
	WORD LineData[18];
} PropFontType;
#endif
#if 0
typedef struct
{
	BYTE XSize, YSize;
	BYTE PrevPage;
	MenuItemType *MenuItems;
	BYTE ItemCount;
	fpExecFunc ExecFunction;
	BYTE Flags;
} MenuPageType;
#endif
typedef struct
{
	BYTE XSize, YSize;
	BYTE PrevPage;
	MenuItemType *MenuItems;
	BYTE ItemCount;
	fpExecFunc ExecFunction;
	MenuFontType *Fonts;
	BYTE Flags;
} MenuPageType;
#endif
