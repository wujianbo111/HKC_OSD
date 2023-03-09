//#include "MenuFontTbl.h"
#include "MenuTblDef.h"
#include "propfont.h"




#define MenuItemXPos	1
#define MenuItemYPos	4
#define MenuItemYPos1    5

#define X_SIZE	29//31
#define Y_SIZE	21//22//21
#define HOTKEY_X_SIZE	27//27
#define HOTKEY_Y_SIZE	11
#define GUAGE_X_POS       16
#define NUM_X_POS           24
#define OPBAR_X_POS        16


//---------------------------------------------------------------
//============================================================
RadioTextType code DrawBrightnessTextRatio[] =
{
	// Flags,					XPos,	YPos,	DisplayText
	{dwiEnd | dwiRadioGroup | dwiMainTitle,		9, 		1,		MainMenu_BrightText}
};
DrawRadioGroupType code DrawBrightnessTextRatioGroup[] =
{
	//ForeColor,				BackColor,				GetValue	RadioText
	{0x76, Color_2, NULL,		DrawBrightnessTextRatio}
};
//----------
RadioTextType code DrawImageTextRatio[] =
{
	// Flags,					XPos,	YPos,	DisplayText
	{dwiEnd | dwiRadioGroup | dwiMainTitle,		9, 		1,		MainMenu_ImageText}
};
DrawRadioGroupType code DrawImageTextRatioGroup[] =
{
	//ForeColor,				BackColor,				GetValue	RadioText
	{0x76, Color_2, NULL,		DrawImageTextRatio}
};
//----------
RadioTextType code DrawColorTextRatio[] =
{
	// Flags,					XPos,	YPos,	DisplayText
	{dwiEnd | dwiRadioGroup | dwiMainTitle,		9, 		1,		MainMenu_ColorText}
};
DrawRadioGroupType code DrawColorTextRatioGroup[] =
{
	//ForeColor,				BackColor,				GetValue	RadioText
	{0x76, Color_2, NULL,		DrawColorTextRatio}
};
//----------
RadioTextType code DrawOSDTextRatio[] =
{
	// Flags,					XPos,	YPos,	DisplayText
	{dwiEnd | dwiRadioGroup | dwiMainTitle,		9, 		1,		MainMenu_OSDText}
};
DrawRadioGroupType code DrawOSDTextRatioGroup[] =
{
	//ForeColor,				BackColor,				GetValue	RadioText
	{0x76, Color_2, NULL,		DrawOSDTextRatio}
};
//----------
RadioTextType code DrawResetTextRatio[] =
{
	// Flags,					XPos,	YPos,	DisplayText
	{dwiEnd | dwiRadioGroup | dwiMainTitle,		9, 		1,		MainMenu_ResetText}
};
DrawRadioGroupType code DrawResetTextRatioGroup[] =
{
	//ForeColor,				BackColor,				GetValue	RadioText
	{0x76, Color_2, NULL,		DrawResetTextRatio}
};
//----------
RadioTextType code DrawMiscTextRatio[] =
{
	// Flags,					XPos,	YPos,	DisplayText
	{dwiEnd | dwiRadioGroup | dwiMainTitle,		9, 		1,		MainMenu_MiscText}
};
DrawRadioGroupType code DrawMiscTextRatioGroup[] =
{
	//ForeColor,				BackColor,				GetValue	RadioText
	{0x76, Color_2, NULL,		DrawMiscTextRatio}
};
//=========== MainMenuItems ================================
MenuItemType code MainMenuItems[] =
{
// 0 Brightness
	{
		MainMenuIcon_DrawXPos, MainMenuIcon_DrawYPos + 2 * MAIN_BriContrast_ITEM,		// XPos, YPos;
		7, Color_8, // ForeColor, BackColor;
		6, Color_8, // SelForeColor, SelBackColor;
		OSD_BriContrastMenu,///NextMenuPage;
		DWI_Icon,// DrawMenuItemType;
		BrightnessIcon, // DisplayText;
		NaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL, // ExecFunction
		},
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawBrightnessTextRatioGroup, // DrawRadioGroupType
		},
		MenuPage1, //Font
		mibSelectable  // Flags
	},
// 1 Image
	{
		MainMenuIcon_DrawXPos, MainMenuIcon_DrawYPos + 2 * MAIN_Picture_ITEM,		// XPos, YPos;
		0x05, Color_4, // ForeColor, BackColor;
		0x04, Color_4, // SelForeColor, SelBackColor;
		PictureMenu,///NextMenuPage;
		DWI_Icon,// DrawMenuItemType;
		ImageIcon, // DisplayText;
		NaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL, // ExecFunction
		},
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawImageTextRatioGroup, // DrawRadioGroupType
		},
		MenuPage2, //Font
		mibSelectable
		#if !Enable_Func_AdjExpansion
		| mibDVIDisable // Flags
		#endif
	},
// 2 ColorTemp
	{
		MainMenuIcon_DrawXPos, MainMenuIcon_DrawYPos + 2 * MAIN_RGBColor_ITEM,		// XPos, YPos;
		9, Color_8, // ForeColor, BackColor;
		8, Color_8, // SelForeColor, SelBackColor;
		RGBColorMenu,///NextMenuPage;
		DWI_Icon,// DrawMenuItemType;
		ColorTempIcon, // DisplayText;
		NaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL, // ExecFunction
		},
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawColorTextRatioGroup, // DrawRadioGroupType
		},
		MenuPage3, //Font
		mibSelectable  // Flags
	},
// 3  OSD
	{
		MainMenuIcon_DrawXPos, MainMenuIcon_DrawYPos + 2 * MAIN_Osd_ITEM,		// XPos, YPos;
		11, Color_8, // ForeColor, BackColor;
		10, Color_8, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Icon,// DrawMenuItemType;
		OSDIcon, // DisplayText;
		NaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL, // ExecFunction
		},
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawOSDTextRatioGroup, // DrawRadioGroupType
		},
		MenuPage4, //Font
		mibSelectable  // Flags
	},
// 4  Reset
	{
		MainMenuIcon_DrawXPos, MainMenuIcon_DrawYPos + 2 * MAIN_Setting_ITEM,		// XPos, YPos;
		0x07, Color_4, // ForeColor, BackColor;
		0x06, Color_4, // SelForeColor, SelBackColor;
		SettingMenu,///NextMenuPage;
		DWI_Icon,// DrawMenuItemType;
		ResetIcon, // DisplayText;
		NaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL, // ExecFunction
		},
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawResetTextRatioGroup, // DrawRadioGroupType
		},
		MenuPage5, //Font
		mibSelectable  // Flags
	},
// 5  Misc
	{
		MainMenuIcon_DrawXPos, MainMenuIcon_DrawYPos + 2 * MAIN_Misc_ITEM,		// XPos, YPos;
		0x09, Color_4, // ForeColor, BackColor;
		0x08, Color_4, // SelForeColor, SelBackColor;
		OSD_MiscMenu,///NextMenuPage;
		DWI_Icon,// DrawMenuItemType;
		MiscIcon, // DisplayText;
		NaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL, // ExecFunction
		},
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawMiscTextRatioGroup, // DrawRadioGroupType
		},
		MenuPage6, //Font
		mibSelectable  // Flags
	},

// 11 Factory,
	{
		1, 0, // XPos, YPos;
		0x0E, 0x02, // ForeColor, BackColor;
		CPC_ColorF, 0x02, // SelForeColor, SelBackColor;
		FactoryMenu,//NextMenuPage;
		DWI_Text, // DrawMenuItemType;
		Main_FText, // DisplayText;
		NaviKeyEvent,
		{
			NULL, 		// AdjustFunction
			NULL			// ExecFunction
		},
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL, // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable | mibFactoryItem // Flags
	},
};



//=========== BriContrastMenuItems ================================
//--------------------BrightnessNumber--------------------------
NumberType code BrightnessNumber[] =
{
	// Flags,   XPos,   YPos,   GetValue
	{dwiEnd,          NumXposion, ( SUB_TEXT_YPOS + BriContrast_BRIGHTNESS_ITEM * IconShift ), GetBrightnessValue},
};
DrawNumberType code DrawBrightnessNumber[] =
{
	// F ForeColor, BackColor,  GetValue
	CP_SelectItem, Color_2,     BrightnessNumber
};
//--------------------BrightnessIconGuge--------------------------
GaugeType code BrightnessGuage[] =
{
	// Flags, ForeColor,    BackColor,  Length,     GetValue
	{dwiEnd,         GaugeXPosition, ( SUB_TEXT_YPOS + BriContrast_BRIGHTNESS_ITEM * IconShift ),  GetBrightnessValue},
};
DrawGuageType code DrawBrightnessGuage[] =
{
	//  ForeColor,  BackColor,  Length,,    GetValue
	27,  Color_4,    9,  BrightnessGuage
};
//--------------------ContrastNumber--------------------------
NumberType code ContrastNumber[] =
{
	// Flags,   XPos,   YPos,   GetValue
	{dwiEnd,          NumXposion, ( SUB_TEXT_YPOS + BriContrast_CONTRAST_ITEM * IconShift ), GetContrastValue},
};
DrawNumberType code DrawContrastNumber[] =
{
	// F ForeColor, BackColor,  GetValue
	CP_UnselectItem, Color_2,     ContrastNumber
};
//--------------------ContrastIconGuge--------------------------
GaugeType code ContrastGuage[] =
{
	// Flags, ForeColor,    BackColor,  Length,     GetValue
	{dwiEnd,             GaugeXPosition, ( SUB_TEXT_YPOS + BriContrast_CONTRAST_ITEM * IconShift ),  GetContrastValue},
};
DrawGuageType code DrawContrastGuage[] =
{
	//  ForeColor,  BackColor,  Length,,    GetValue
	27,  Color_4,    9,  ContrastGuage
};
//--------------------ECOIconRatioText--------------------------
RadioTextType code DrawECOText[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + BriContrast_ECO_ITEM * IconShift ),     ECOModeValue},
};
DrawRadioGroupType code DrawECOIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_SelectItem,   Color_2, NULL,  DrawECOText}
};
//--------------------DCRIconRatioText--------------------------
RadioTextType code DrawDcr[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + BriContrast_DCR_ITEM * IconShift ),     DcrValueText},
};
DrawRadioGroupType code DrawDcrIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2, NULL, DrawDcr}
};
//--------------------OverdriveIconRatioText--------------------------
#if ENABLE_RTE
#if PresetMode_Enable
RadioTextType code DrawOverdrive[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + Misc_Overdrive_ITEM * IconShift ),     OverdriveValueText},
};
DrawRadioGroupType code DrawOverdriveIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2, NULL, DrawOverdrive}
};
#else
RadioTextType code DrawOverdrive[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + BriContrast_Overdrive_ITEM * IconShift ),     OverdriveValueText},
};
DrawRadioGroupType code DrawOverdriveIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2, NULL, DrawOverdrive}
};
#endif
#endif
//--------------------iCareIconRatioText--------------------------
#if Enable_Gamma
#if !PresetMode_Enable
RadioTextType code DrawGammaText[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_GAMMA_ITEM),     GammaModeValue},
};
DrawRadioGroupType code DrawGammaIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2, NULL, DrawGammaText}
};
#endif
#endif
//=========== ========================= =======================
MenuItemType code BriContrastMenuItems[] =
{
	// 0 Brightness
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_BRIGHTNESS_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		BrightnessMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		BrightnessText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawBrightnessNumber,// DrawNumberType
			DrawBrightnessGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable | mibsRGBDisable | mibDCRDisable | mibStdEnable // Flags
	},
	// 1 Contrast
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_CONTRAST_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		ContrastMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		ContrastText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawContrastNumber,// DrawNumberType
			DrawContrastGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable | mibsRGBDisable | mibDCRDisable | mibStdEnable
	},

	// 2 ECOModeSelect
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_ECO_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		ECOMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		ECOModeText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawECOIconRatioText // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable | mibDCRDisable // Flags	//110304 Modify
	},
	// 3 DCR
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_DCR_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		DCRMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		DCRText,  // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawDcrIconRatioText // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable
	},

	#if !PresetMode_Enable
	#if ENABLE_RTE
// 4 Overdrive
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_Overdrive_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OverdriveMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		OverdriveText,  // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawOverdriveIconRatioText // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable | mibODDisable // Flags  		// 130402 Modify
	},
	#endif
	#endif

	#if Enable_Gamma
	#if !PresetMode_Enable
	// 3 Gamma
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_GAMMA_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		GammaMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		GammaText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawGammaIconRatioText // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable | mibDCRDisable | mibsRGBDisable// Flags	//110222 Modify
	},
	#endif
	#endif

};

//============ Brightness MenuItem==============
MenuItemType code BrightnessMenuItems[] =
{
	// 0 Brightness
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_BRIGHTNESS_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OSD_BriContrastMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		BrightnessText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustBrightness,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawBrightnessNumber,// DrawNumberType
			DrawBrightnessGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};

//============ Contrast MenuItem==============
MenuItemType code ContrastMenuItems[] =
{
	// 0 Contrast
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_CONTRAST_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OSD_BriContrastMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		ContrastText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustContrast,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawContrastNumber,// DrawNumberType
			DrawContrastGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};


RadioTextType code DrawECOMenuText[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_ECO_ITEM),     ECOModeValue},
};
DrawRadioGroupType code DrawECOMenuIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{14,   Color_2, NULL,  DrawECOMenuText}
};
MenuItemType code ECOMODEMenuItems[] =
{
	// 0 ECOMemu
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_ECO_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OSD_BriContrastMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		ECOModeText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustECOMode,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL, // DrawNumberType
			NULL, //  DrawGuageType
			DrawECOMenuIconRatioText // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};



//============ DCRMenu ==============
RadioTextType code DrawDcrMenuText[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_DCR_ITEM),     DcrValueText },
};
DrawRadioGroupType code DrawDcrMenuIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{10,    Color_2, NULL, DrawDcrMenuText}
};
MenuItemType code DCRMenuItems[] =
{
	// 0 DCRMenu
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_DCR_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OSD_BriContrastMenu,      //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		DCRText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustDcrMode,// AdjustFunction
			NULL,               // ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawDcrMenuIconRatioText        //DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable // Flags
	},
};



#if ENABLE_RTE
//========== == OverdriveMenu ==============
#if PresetMode_Enable
RadioTextType code DrawOverdriveMenuText[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_Overdrive_ITEM),     OverdriveValueText },
};
DrawRadioGroupType code DrawOverdriveMenuIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{10,    Color_2, NULL, DrawOverdriveMenuText}
};
MenuItemType code OverdriveMenuItems[] =
{
	// 0 OverdriveMenu
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_Overdrive_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OSD_MiscMenu,      //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		OverdriveText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustOverDrive,// AdjustFunction
			NULL,               // ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawOverdriveMenuIconRatioText        //DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#else
RadioTextType code DrawOverdriveMenuText[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_Overdrive_ITEM),     OverdriveValueText },
};
DrawRadioGroupType code DrawOverdriveMenuIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{10,    Color_2, NULL, DrawOverdriveMenuText}
};
MenuItemType code OverdriveMenuItems[] =
{
	// 0 OverdriveMenu
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_Overdrive_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OSD_BriContrastMenu,      //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		OverdriveText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustOverDrive,// AdjustFunction
			NULL,               // ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawOverdriveMenuIconRatioText        //DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#endif

#endif

#if Enable_Gamma
#if PresetMode_Enable
//============ Gamma ==============
RadioTextType code DrawGammaMenuText[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_DCR_ITEM),     GammaModeValue },
};
DrawRadioGroupType code DrawGammaMenuIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{10,    Color_2, NULL, DrawGammaMenuText}
};
MenuItemType code GammaMenuItems[] =
{
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_DCR_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OSD_BriContrastMenu,      //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		GammaText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustGamaMode,// AdjustFunction
			NULL,           // ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawGammaMenuIconRatioText        //DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#else
//============ Gamma ==============
RadioTextType code DrawGammaMenuText[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_GAMMA_ITEM),     GammaModeValue },
};
DrawRadioGroupType code DrawGammaMenuIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{10,    Color_2, NULL, DrawGammaMenuText}
};
MenuItemType code GammaMenuItems[] =
{
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * BriContrast_GAMMA_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OSD_BriContrastMenu,      //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		GammaText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustGamaMode,// AdjustFunction
			NULL,           // ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawGammaMenuIconRatioText        //DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#endif

#endif




//=========== PictureMenuItems ================================
//--------------------HPositionNumber--------------------------
NumberType code HPositionNumber[] =
{
	// Flags,   XPos,   YPos,   GetValue
	{dwiEnd,       NumXposion, ( SUB_TEXT_YPOS + IconShift * Picture_HPOSITION_ITEM ), GetHPositionValue},
};
DrawNumberType code DrawHPositionNumber[] =
{
	// F ForeColor, BackColor,  GetValue
	14, Color_2,     HPositionNumber
};
//--------------------HPositionIconGuge--------------------------
GaugeType code HPositionGuage[] =
{
	// Flags, ForeColor,    BackColor,  Length,     GetValue
	{dwiEnd,    GaugeXPosition, ( SUB_TEXT_YPOS + IconShift * Picture_HPOSITION_ITEM ),   GetHPositionValue},
};
DrawGuageType code DrawHPositionGuage[] =
{
	//  ForeColor,  BackColor,  Length,,    GetValue
	6,  Color_4,    9,  HPositionGuage
};

//--------------------VPositionNumber--------------------------
NumberType code VPositionNumber[] =
{
	// Flags,   XPos,   YPos,   GetValue
	{dwiEnd,       NumXposion, ( SUB_TEXT_YPOS + IconShift * Picture_VPOSITION_ITEM),    GetVPositionValue},
};
DrawNumberType code DrawVPositionNumber[] =
{
	// F ForeColor, BackColor,  GetValue
	14, Color_2,     VPositionNumber
};
//--------------------VPositionIconGuge--------------------------
GaugeType code VPositionGuage[] =
{
	// Flags, ForeColor,    BackColor,  Length,     GetValue
	{dwiEnd,            GaugeXPosition, (SUB_TEXT_YPOS + IconShift * Picture_VPOSITION_ITEM),  GetVPositionValue},
};
DrawGuageType code DrawVPositionGuage[] =
{
	//  ForeColor,  BackColor,  Length,,    GetValue
	6,  Color_4,    9,  VPositionGuage
};
//--------------------ClockNumber--------------------------
NumberType code ClockNumber[] =
{
	// Flags,   XPos,   YPos,   GetValue
	{ dwiEnd,      NumXposion, ( SUB_TEXT_YPOS + IconShift * Picture_CLOCK_ITEM),  GetClockValue},
};
DrawNumberType code DrawClockNumber[] =
{
	// F ForeColor, BackColor,  GetValue
	14, Color_2,     ClockNumber
};
//--------------------ClockIconGuge--------------------------
GaugeType code ClockGuage[] =
{
	// Flags, ForeColor,    BackColor,  Length,     GetValue
	{dwiEnd,             GaugeXPosition, ( SUB_TEXT_YPOS + IconShift * Picture_CLOCK_ITEM ),   GetClockValue},
};
DrawGuageType code DrawClockGuage[] =
{
	//  ForeColor,  BackColor,  Length,,    GetValue
	6,  Color_4,    9,  ClockGuage
};

//--------------------FocusNumber--------------------------
NumberType code FocusNumber[] =
{
	// Flags,   XPos,   YPos,   GetValue
	{dwiEnd,       NumXposion, ( SUB_TEXT_YPOS + IconShift * Picture_PHASE_ITEM ), GetFocusValue},
};
DrawNumberType code DrawFocusNumber[] =
{
	// F ForeColor, BackColor,  GetValue
	14, Color_2,     FocusNumber
};
//--------------------FocusIconGuge--------------------------
GaugeType code FocusGuage[] =
{
	// Flags, ForeColor,    BackColor,  Length,     GetValue
	{dwiEnd,            GaugeXPosition, ( SUB_TEXT_YPOS + IconShift * Picture_PHASE_ITEM ),   GetFocusValue},
};
DrawGuageType code DrawFocusGuage[] =
{
	//  ForeColor,  BackColor,  Length,,    GetValue
	6,  Color_4,    9,  FocusGuage
};
#if Enable_Func_AdjExpansion
RadioTextType code DrawExpansion[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Picture_IMAGERATIO_ITEM ),     ExpansionValueText},
};
DrawRadioGroupType code DrawExpansionText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2, NULL, DrawExpansion}
};
#endif




MenuItemType code PictureMenuItems[] =
{
	// 0 HPositionMenu
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Picture_HPOSITION_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		HPositionMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		HPositionText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawHPositionNumber,// DrawNumberType
			DrawHPositionGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable | mibDVIDisable // Flags
	},
	// 1 VPositionMenu
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Picture_VPOSITION_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		VPositionMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		VPositionText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawVPositionNumber,// DrawNumberType
			DrawVPositionGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable | mibDVIDisable // Flags
	},

	// 2 ClockMenu
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Picture_CLOCK_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		ClockMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		ClockText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawClockNumber,// DrawNumberType
			DrawClockGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable | mibDVIDisable // Flags
	},
	// 3 FocusMenu
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Picture_PHASE_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		FocusMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FocusText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawFocusNumber,// DrawNumberType
			DrawFocusGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable | mibDVIDisable // Flags
	},
	#if Enable_Func_AdjExpansion
	// 4  Ratio
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Picture_IMAGERATIO_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		ExpansionMenu,//MainMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		ExpansionText,// DisplayText;
		NaviKeyEvent,
		{
			AdjustExpansionMode,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawExpansionText,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable | mibExpansionDisable
	},
	#endif

};
//============ HPosition MenuItem==============
MenuItemType code HPositionMenuItems[] =
{
	// 0 HPosition
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Picture_HPOSITION_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		PictureMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		HPositionText, // DisplayText;
		AdjusterKey1Event,
		{
			AdjustHPosition,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawHPositionNumber,// DrawNumberType
			DrawHPositionGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable | mibDVIDisable // Flags
	},
};

//============ HPosition MenuItem==============
MenuItemType code VPositionMenuItems[] =
{
	// 0 VPosition
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Picture_VPOSITION_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		PictureMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		VPositionText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustVPosition,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawVPositionNumber,// DrawNumberType
			DrawVPositionGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable | mibDVIDisable // Flags
	},
};


//============ Clock MenuItem==============
MenuItemType code ClockMenuItems[] =
{
	// 0 Clock
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Picture_CLOCK_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		PictureMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		ClockText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustClock,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawClockNumber,// DrawNumberType
			DrawClockGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable | mibDVIDisable // Flags
	},
};

//============ Focus MenuItem==============
MenuItemType code FocusMenuItems[] =
{
	// 0 Focus
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Picture_PHASE_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		PictureMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FocusText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustFocus,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawFocusNumber,// DrawNumberType
			DrawFocusGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable | mibDVIDisable // Flags
	},
};
#if Enable_Func_AdjExpansion
MenuItemType code ExpansionMenuItems[] =
{
	// 0
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Picture_IMAGERATIO_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		PictureMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		ExpansionText, // DisplayText;
		AdjustNoExecKeyEvent,
		{
			AdjustExpansionMode,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawExpansionText,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#endif



//=========== RGBMenuItems ================================
//--------------------ColorTempText--------------------------
RadioTextType code DrawColorTempSelectText[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * RGB_ColorTemp_Item),     ColorTempValueText},
};
DrawRadioGroupType code DrawColorTempSelectIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2, NULL, DrawColorTempSelectText}
};
//--------------------UserColorRedNumber--------------------------
NumberType code UserColorRedNumber[] =
{
	// Flags,   XPos,   YPos,   GetValue
	{dwiEnd,          NumXposion, ( SUB_TEXT_YPOS + IconShift * RGB_Red_Item),  GetRedColorValue},
};
DrawNumberType code DrawUserColorRedNumber[] =
{
	// F ForeColor, BackColor,  GetValue
	14, Color_2,     UserColorRedNumber
};
//--------------------UserColorRedIconGuge--------------------------
GaugeType code UserColorRedGuage[] =
{
	// Flags, ForeColor,    BackColor,  Length,     GetValue
	{dwiEnd,             GaugeXPosition, ( SUB_TEXT_YPOS + IconShift * RGB_Red_Item),   GetRedColorValue},
};
DrawGuageType code DrawUserColorRedGuage[] =
{
	//  ForeColor,  BackColor,  Length,,    GetValue
	6,  Color_4,    9,  UserColorRedGuage
};

//--------------------UserColorGreenNumber--------------------------
NumberType code UserColorGreenNumber[] =
{
	// Flags,   XPos,   YPos,   GetValue
	{dwiEnd,          NumXposion, ( SUB_TEXT_YPOS + IconShift * RGB_Green_Item),  GetGreenColorValue},
};
DrawNumberType code DrawUserColorGreenNumber[] =
{
	// F ForeColor, BackColor,  GetValue
	14, Color_2,     UserColorGreenNumber
};
//--------------------UserColorGreenIconGuge--------------------------
GaugeType code UserColorGreenGuage[] =
{
	// Flags, ForeColor,    BackColor,  Length,     GetValue
	{dwiEnd,             GaugeXPosition, ( SUB_TEXT_YPOS + IconShift * RGB_Green_Item),   GetGreenColorValue},
};
DrawGuageType code DrawUserColorGreenGuage[] =
{
	//  ForeColor,  BackColor,  Length,,    GetValue
	6,  Color_4,    9,  UserColorGreenGuage
};

//--------------------UserColorBlueNumber--------------------------
NumberType code UserColorBlueNumber[] =
{
	// Flags,   XPos,   YPos,   GetValue
	{dwiEnd,          NumXposion, ( SUB_TEXT_YPOS + IconShift * RGB_Blue_Item), GetBlueColorValue},
};
DrawNumberType code DrawUserColorBlueNumber[] =
{
	// F ForeColor, BackColor,  GetValue
	14, Color_2,     UserColorBlueNumber
};
//--------------------UserColorBlueIconGuge--------------------------
GaugeType code UserColorBlueGuage[] =
{
	// Flags, ForeColor,    BackColor,  Length,     GetValue
	{dwiEnd,             GaugeXPosition, ( SUB_TEXT_YPOS + IconShift * RGB_Blue_Item),  GetBlueColorValue},
};
DrawGuageType code DrawUserColorBlueGuage[] =
{
	//  ForeColor,  BackColor,  Length,,    GetValue
	6,  Color_4,    9,  UserColorBlueGuage
};
#if LowBlueLightType==LowBlueLight_ColorTemp
//--------------------LowBlueLightText--------------------------
RadioTextType code DrawLowBlueLightMenuText[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * RGB_LowBlueLigth_Item),     LowBlueLightStatusText},
};
DrawRadioGroupType code DrawLowBlueLightMenuIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_SelectItem,   Color_2, NULL, DrawLowBlueLightMenuText}
};
#elif LowBlueLightType==LowBlueLight_SharpFunc
RadioTextType code DrawLowBlueLightMenuText[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * RGB_LowBlueLigth_Item),     LowBlueLightStatusText},
};
DrawRadioGroupType code DrawLowBlueLightMenuIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_SelectItem,   Color_2, NULL, DrawLowBlueLightMenuText}
};
#elif LowBlueLightType==LowBlueLight_Misc_Guage

NumberType code DrawLowBlueLightMenu_LowBlueLightNum[] =
{
	// Flags,	XPos,	YPos,	GetValue
	{dwiEnd, NumXposion, ( SUB_TEXT_YPOS + IconShift * Misc_LowBlueLigth_Item),	GetLowBlueLightValue}
};
DrawNumberType code DrawLowBlueLightMenu_LowBlueLightNumber[] =
{
	// Flags,	ForeColor,					BackColor,								XPos,	YPos,	GetValue
	{CP_ExecItem, CP_ExecItem,  	DrawLowBlueLightMenu_LowBlueLightNum}
};

GaugeType code DrawLowBlueLightMenu_LowBlueLightGuagee[] =
{
	// Flags,	XPos,	YPos,	GetValue
	{dwiEnd,	GaugeXPosition, ( SUB_TEXT_YPOS + IconShift * Misc_LowBlueLigth_Item),	GetLowBlueLightValue}
};
DrawGuageType code DrawLowBlueLightMenu_LowBlueLightGuage[] =
{
	//Flags,	ForeColor,	    			BackColor,						Length,	XPos,	YPos,	GetValue
	{CP_ExecItem, Color_2,  9, DrawLowBlueLightMenu_LowBlueLightGuagee}
};
#elif LowBlueLightType==LowBlueLight_Misc_Group
//--------------------LowBlueLightText--------------------------
RadioTextType code DrawLowBlueLightMenuText[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_LowBlueLigth_Item),     LowBlueLightStatusText},
};
DrawRadioGroupType code DrawLowBlueLightMenuIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_SelectItem,   Color_2, NULL, DrawLowBlueLightMenuText}
};

#endif


MenuItemType code RGBMenuItems[] =
{
	// 0 ColorTempMenu
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * RGB_ColorTemp_Item), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		ColorTempMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		ColorTempText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawColorTempSelectIconRatioText,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 1 UserColorRedMenu
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * RGB_Red_Item), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		RedMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		UserColorRText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawUserColorRedNumber,// DrawNumberType
			DrawUserColorRedGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable | mibUserColor // Flags
	},
	// 2 UserColorGreenMenu
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * RGB_Green_Item), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		GreenMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		UserColorGText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawUserColorGreenNumber,// DrawNumberType
			DrawUserColorGreenGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable | mibUserColor // Flags
	},
	// 3 UserColorBlueMenu
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * RGB_Blue_Item), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		BlueMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		UserColorBText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawUserColorBlueNumber,// DrawNumberType
			DrawUserColorBlueGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable | mibUserColor // Flags
	},
	#if LowBlueLightType==LowBlueLight_ColorTemp
	// 4 LowBlueLightMenu
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * RGB_LowBlueLigth_Item), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		LowBlueLightMenu,//NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		LowBlueLightText,// DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawLowBlueLightMenuIconRatioText,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable// Flags
	},
	#elif  LowBlueLightType==LowBlueLight_SharpFunc
	// 4 LowBlueLightMenu
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * RGB_LowBlueLigth_Item), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		LowBlueLightMenu,//NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		LowBlueLightText,// DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawLowBlueLightMenuIconRatioText,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable | MIB_LOWBLUEDISABLE // Flags
	},
	#endif
};


//============ ColorTempSelectMenuItem==============
MenuItemType code ColorTempSelectMenuItems[] =
{
	// 0 ColorTempSelect
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * RGB_ColorTemp_Item), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		RGBColorMenu,                                  //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		ColorTempText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustColorTempMode,// AdjustFunction
			NULL,                                           // ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawColorTempSelectIconRatioText        //DrawMenuRadioGroup,
		},
		NULL,//Font
		mibSelectable // Flags
	},
};
//============ UserColorRed MenuItem==============
MenuItemType code UserColorRedMenuItems[] =
{
	// 0 UserColorRedMENU
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * RGB_Red_Item), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		RGBColorMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		UserColorRText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustRedColor,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawUserColorRedNumber,// DrawNumberType
			DrawUserColorRedGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
//============ UserColorGreen MenuItem==============
MenuItemType code UserColorGreenMenuItems[] =
{
	// 0 UserColorGreenMENU
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * RGB_Green_Item), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		RGBColorMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		UserColorGText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustGreenColor,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawUserColorGreenNumber,// DrawNumberType
			DrawUserColorGreenGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
//============ UserColorBlue MenuItem==============
MenuItemType code UserColorBlueMenuItems[] =
{
	// 0 UserColorBlueMENU
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * RGB_Blue_Item), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		RGBColorMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		UserColorBText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustBlueColor,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawUserColorBlueNumber,// DrawNumberType
			DrawUserColorBlueGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};


#if LowBlueLightType==LowBlueLight_ColorTemp
//============ LowBlueLight MenuItem==============

MenuItemType code LowBlueLightMenuItems[] =
{
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * RGB_LowBlueLigth_Item), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		RGBColorMenu,//NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		LowBlueLightText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustLowBlueLight, //,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawLowBlueLightMenuIconRatioText,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#elif LowBlueLightType==LowBlueLight_SharpFunc
//============ LowBlueLight MenuItem==============

MenuItemType code LowBlueLightMenuItems[] =
{
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * RGB_LowBlueLigth_Item), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		RGBColorMenu,//NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		LowBlueLightText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustLowBlueLight, //,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawLowBlueLightMenuIconRatioText,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#elif LowBlueLightType==LowBlueLight_Misc_Guage
MenuItemType code LowBlueLightMenuItems[] =
{
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_LowBlueLigth_Item), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OSD_MiscMenu,//NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		LowBlueLightText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustLowBlueLight, //,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawLowBlueLightMenu_LowBlueLightNumber,// DrawNumberType
			DrawLowBlueLightMenu_LowBlueLightGuage,// DrawGuageType
			NULL,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#elif LowBlueLightType==LowBlueLight_Misc_Group
MenuItemType code LowBlueLightMenuItems[] =
{
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_LowBlueLigth_Item), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OSD_MiscMenu,//NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		LowBlueLightText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustLowBlueLight, //,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawLowBlueLightMenuIconRatioText,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#endif


//=========== OSDMenuItems ================================
#if AdjustLanguageFunction
RadioTextType code DrawLanguageText[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * OSD_LANGUAGE_ITEM),     LanguageStatusText},
};
DrawRadioGroupType code DrawLanguageIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2, NULL, DrawLanguageText}
};
#endif

#if OsdAdjustHVPos_Enable
//--------------------OsdHPositionNumber--------------------------
NumberType code OsdHPositionNumber[] =
{
	// Flags,   XPos,   YPos,   GetValue
	{dwiEnd,       NumXposion, ( SUB_TEXT_YPOS + IconShift * OSD_HPOSITION_ITEM), GetOSDHPositionValue},
};
DrawNumberType code DrawOsdHPositionNumber[] =
{
	// F ForeColor, BackColor,  GetValue
	14, Color_2,     OsdHPositionNumber
};
//--------------------OsdHPositionIconGuge--------------------------
GaugeType code OsdHPositionGuage[] =
{
	// Flags, ForeColor,    BackColor,  Length,     GetValue
	{dwiEnd,            GaugeXPosition, ( SUB_TEXT_YPOS + IconShift * OSD_HPOSITION_ITEM),   GetOSDHPositionValue},
};
DrawGuageType code DrawOsdHPositionGuage[] =
{
	//  ForeColor,  BackColor,  Length,,    GetValue
	6, Color_4, 9,  OsdHPositionGuage
};
//--------------------OsdVPositionNumber--------------------------
NumberType code OsdVPositionNumber[] =
{
	// Flags,   XPos,   YPos,   GetValue
	{dwiEnd,       NumXposion, ( SUB_TEXT_YPOS + IconShift * OSD_VPOSITION_ITEM), GetOSDVPositionValue},
};
DrawNumberType code DrawOsdVPositionNumber[] =
{
	// F ForeColor, BackColor,  GetValue
	14, Color_2,     OsdVPositionNumber
};
//--------------------OsdVPositionIconGuge--------------------------
GaugeType code OsdVPositionGuage[] =
{
	// Flags, ForeColor,    BackColor,  Length,     GetValue
	{dwiEnd,            GaugeXPosition, ( SUB_TEXT_YPOS + IconShift * OSD_VPOSITION_ITEM),   GetOSDVPositionValue},
};
DrawGuageType code DrawOsdVPositionGuage[] =
{
	//  ForeColor,  BackColor,  Length,,    GetValue
	6, Color_4, 9,  OsdVPositionGuage
};
#endif
//--------------------OsdTimeOutNumber--------------------------
NumberType code OsdTimeOutNumber[] =
{
	// Flags,   XPos,   YPos,   GetValue
	{dwiEnd,       NumXposion, ( SUB_TEXT_YPOS + IconShift * OSD_TIMEOUT_ITEM), GetOSDTimeValue},
};
DrawNumberType code DrawOsdTimeOutNumber[] =
{
	// F ForeColor, BackColor,  GetValue
	14, Color_2,     OsdTimeOutNumber
};
//--------------------OsdTimeOutIconGuge--------------------------
GaugeType code OsdTimeOutGuage[] =
{
	// Flags, ForeColor,    BackColor,  Length,     GetValue
	{dwiEnd,            GaugeXPosition, ( SUB_TEXT_YPOS + IconShift * OSD_TIMEOUT_ITEM),   GetOSDTime100Value},
};
DrawGuageType code DrawOsdTimeOutGuage[] =
{
	//  ForeColor,  BackColor,  Length,,    GetValue
	6,  Color_4, 9,  OsdTimeOutGuage
};
//--------------------TransparenceNumber--------------------------
NumberType code TransparenceNumber[] =
{
	// Flags,   XPos,   YPos,   GetValue
	{dwiEnd,       NumXposion, ( SUB_TEXT_YPOS + IconShift * OSD_TRANSPARENCE_ITEM), GetOSDTransparence},
};
DrawNumberType code DrawTransparenceNumber[] =
{
	// F ForeColor, BackColor,  GetValue
	14, Color_2,     TransparenceNumber
};
//--------------------TransparenceIconGuge--------------------------
GaugeType code TransparenceGuage[] =
{
	// Flags, ForeColor,    BackColor,  Length,     GetValue
	{dwiEnd,            GaugeXPosition, ( SUB_TEXT_YPOS + IconShift * OSD_TRANSPARENCE_ITEM),   GetOSDTransparence},
};
DrawGuageType code DrawTransparenceGuage[] =
{
	//  ForeColor,  BackColor,  Length,,    GetValue
	6, Color_4, 9,  TransparenceGuage
};

MenuItemType code OSDMenuItems[] =
{
	#if AdjustLanguageFunction
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * OSD_LANGUAGE_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		LanguageMenu, 			// NextMenuPage;
		DWI_Text,						// DrawMenuItemType;
		LanguageText, 						// DisplayText;
		NaviKeyEvent, 			// KeyEvent;
		{
			NULL,								// AdjustFunction
			NULL								// ExecFunction
		},									// *DisplayValue;
		{
			NULL,								// DrawNumberType
			NULL,								// DrawGuageType
			DrawLanguageIconRatioText			// DrawRadioGroupType
		},
		NULL, // Fonts
		mibSelectable 						// Flags
	},

	#else
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * OSD_LANGUAGE_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		LanguageMenu, 			// NextMenuPage;
		DWI_Text,						// DrawMenuItemType;
		LanguageText, 						// DisplayText;
		NaviKeyEvent, 			// KeyEvent;
		{
			NULL,								// AdjustFunction
			NULL								// ExecFunction
		},									// *DisplayValue;
		{
			NULL,								// DrawNumberType
			NULL,								// DrawGuageType
			NULL			// DrawRadioGroupType
		},
		NULL, // Fonts
		mibSelectable 						// Flags
	},
	#endif

	#if OsdAdjustHVPos_Enable
	// 1 OsdHPosition
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * OSD_HPOSITION_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdHPositionMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		OsdHPositionText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,//AutoConfig// ExecFunction
		},
		{
			DrawOsdHPositionNumber,// DrawNumberType
			DrawOsdHPositionGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 1 OsdVPosition
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * OSD_VPOSITION_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdVPositionMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		OsdVPositionText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,//AutoConfig// ExecFunction
		},
		{
			DrawOsdVPositionNumber,// DrawNumberType
			DrawOsdVPositionGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	#endif
	// 2 OsdTimeOut
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * OSD_TIMEOUT_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdTimeOutMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		OsdTimeOutText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawOsdTimeOutNumber,// DrawNumberType
			DrawOsdTimeOutGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},

	// 2 Transparence
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * OSD_TRANSPARENCE_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		TransparenceMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		TransparenceText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawTransparenceNumber,// DrawNumberType
			DrawTransparenceGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};

//=========== OsdMenuItems ================================
//------------- LanguageeModeText  --------------------
#if AdjustLanguageFunction
MenuItemType code LanguageMenuItems[] =
{
	// 0 LanguageMemu
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * OSD_LANGUAGE_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		LanguageText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustLanguage,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawLanguageIconRatioText // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#else
MenuItemType code LanguageMenuItems[] =
{
	// 0 ENGLISH
	{
		7, ( SUB_TEXT_YPOS + 0 * 2 ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		strEnglishText, // DiplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			AdjustLanguage,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL, // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},

	{
		7, ( SUB_TEXT_YPOS + 1 * 2 ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		strFranceText, // DiplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			AdjustLanguage,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL, // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	{
		7, ( SUB_TEXT_YPOS + 2 * 2 ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		strEspanolText, // DiplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			AdjustLanguage,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL, // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	{
		7, ( SUB_TEXT_YPOS + 3 * 2 ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		strPortuguesText, // DiplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			AdjustLanguage,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL, // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	{
		7, ( SUB_TEXT_YPOS + 4 * 2 ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		strDeutschText, // DiplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			AdjustLanguage,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL, // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	{
		7, ( SUB_TEXT_YPOS + 5 * 2 ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		strItalianoText, // DiplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			AdjustLanguage,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL, // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	{
		16, ( SUB_TEXT_YPOS + 0 * 2 ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		strNederlandsText, // DiplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			AdjustLanguage,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL, // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	{
		16, ( SUB_TEXT_YPOS + 1 * 2 ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		strSvenskaText, // DiplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			AdjustLanguage,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL, // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	{
		16, ( SUB_TEXT_YPOS + 2 * 2 ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		strSuomiText, // DiplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			AdjustLanguage,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL, // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	{
		16, ( SUB_TEXT_YPOS + 3 * 2 ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		strPolskiText, // DiplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			AdjustLanguage,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL, // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	{
		16, ( SUB_TEXT_YPOS + 4 * 2 ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		strCestinaText, // DiplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			AdjustLanguage,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL, // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	{
		16, ( SUB_TEXT_YPOS + 5 * 2 ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		strPycText, // DiplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			AdjustLanguage,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL, // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	{
		25, ( SUB_TEXT_YPOS + 0 * 2 ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		strKoreanText, // DiplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			AdjustLanguage,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL, // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	{
		25, ( SUB_TEXT_YPOS + 1 * 2 ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		strTChineseText, // DiplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			AdjustLanguage,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL, // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	{
		25, ( SUB_TEXT_YPOS + 2 * 2 ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		strSChineseText, // DiplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			AdjustLanguage,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL, // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	{
		25, ( SUB_TEXT_YPOS + 3 * 2 ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		strJapanText, // DiplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			AdjustLanguage,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL, // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},

} ;
#endif

#if OsdAdjustHVPos_Enable
//============ OsdHPositionMenuItem==============
MenuItemType code OsdHPositionMenuItems[] =
{
	// 0 OsdHPosition
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * OSD_HPOSITION_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		OsdHPositionText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustOSDHPosition,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawOsdHPositionNumber,// DrawNumberType
			DrawOsdHPositionGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};

//============ OsdVPositionMenuItem==============
MenuItemType code OsdVPositionMenuItems[] =
{
	// 0 OsdVPosition
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * OSD_VPOSITION_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		OsdVPositionText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustOSDVPosition,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawOsdVPositionNumber,// DrawNumberType
			DrawOsdVPositionGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#endif
//============ OsdTimeOutMenuItem==============
MenuItemType code OsdTimeOutMenuItems[] =
{
	// 0 OsdTimeOutPosition
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * OSD_TIMEOUT_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		OsdTimeOutText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustOSDTime,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawOsdTimeOutNumber,// DrawNumberType
			DrawOsdTimeOutGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};

//------------- Transparence  --------------------
MenuItemType code TransparenceMenuItems[] =
{
	// TransparenceMemu
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * OSD_TRANSPARENCE_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OsdMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		TransparenceText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustOSDTransparence,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawTransparenceNumber,// DrawNumberType
			DrawTransparenceGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};

#ifdef OffPower
//--------------------OffTimer--------------------------
RadioTextType code DrawOffTimer[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Setting_OffPower_ITEM),     NullText},
};
DrawRadioGroupType code DrawOffTimerIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2, NULL, DrawOffTimer}
};
NumberType code OffTimerNumber[] =
{
	//  Flags,      XPos,           YPos,                       GetValue
	{   dwiOffTimer | dwiEnd,    OFFTIMER_VALUE_XPOS,  ( SUB_TEXT_YPOS + IconShift * Setting_OffPower_ITEM),  GetAutoPowerOffValue}, // 130730 JUN Modify
};
DrawNumberType code DrawOffTimerNumber[] =
{
	// F ForeColor, BackColor,  GetValue
	14, Color_2,     OffTimerNumber
};
#endif
//----------------------------------------------



//=========== SettingMenuItems ================================

MenuItemType code SettingMenuItems[] =
{
	#if AboutDSUBFunc_Enable
// 0  AutoConfig
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Setting_AUTOCONFIG_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		MainMenu,//NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		AutoConfigText,// DisplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			AutoConfig,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable | mibDVIDisable // Flags
	},

	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Setting_AUTOCOLOR_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		MainMenu,//NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		SubAutoColorText,// DisplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			AutoColor,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable | mibDVIDisable // Flags
	},
	#endif
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Setting_RESTR_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		MainMenu,//NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		ResetText,// DisplayText;
		AdjustExecKeyEvent,
		{
			NULL,// AdjustFunction
			ResetAllSetting,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable // Flags
	},
	#ifdef OffPower
	// 2 OffTimer
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Setting_OffPower_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OffTimerMenu,//NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		OffTimerText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawOffTimerNumber,// DrawNumberType
			NULL,// DrawGuageType
			DrawOffTimerIconRatioText,//DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	#endif
};


#ifdef OffPower

MenuItemType code OffTimerMenuItems[] =
{
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Setting_OffPower_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		SettingMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		OffTimerText, // DisplayText;
		AdjustNoExecKeyEvent,
		{
			AdjustAutoPowerOff,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawOffTimerNumber,// DrawNumberType
			NULL,// DrawGuageType
			DrawOffTimerIconRatioText,//DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#endif


//=========== MiscMenuItems ================================
//--------------------InputSelectText--------------------------
#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
RadioTextType code DrawInputSelect[] =
{
	#if HKC_INPUTSELECT_MODE
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_InputSource_ITEM),     InputTypeRationText},
	#else
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_InputSource_ITEM),     InputSourceText},
	#endif
};
DrawRadioGroupType code DrawInputSelectIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2, NULL, DrawInputSelect}
};
#endif
#if AudioFunc
#if EANBLE_MUTE_ON_OFF

//-------------------MuteText--------------------------
RadioTextType code DrawMute[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_Mute_ITEM ),  MuteValueText},
};
DrawRadioGroupType code DrawMuteRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2, NULL, DrawMute}
};
#endif

//--------------------VolumeNumber--------------------------
NumberType code VolumeNumber[] =
{
	// Flags,   XPos,   YPos,   GetValue
	{dwiEnd,        NumXposion, ( SUB_TEXT_YPOS + IconShift * Misc_Volume_ITEM), GetVolumeValue},
};
DrawNumberType code DrawVolumeNumber[] =
{
	// F ForeColor, BackColor,  GetValue
	CP_ExecItem, CP_ExecItem,     VolumeNumber
};
//--------------------VolumeIconGuge--------------------------
GaugeType code VolumeGuage[] =
{
	// Flags    XPos,   YPos,   GetValue
	{dwiEnd,   GaugeXPosition, ( SUB_TEXT_YPOS + IconShift * Misc_Volume_ITEM),      GetVolumeValue},
};
DrawGuageType code DrawVolumeGuage[] =
{
	//  ForeColor,  BackColor,  Length,,    GetValue
	CP_ExecItem, Color_2,  9,  VolumeGuage
};
#endif
//--------------------ddcci Text--------------------------
#if  DDCCI_ENABLE && DDCCCIMenu_Enable
RadioTextType code DrawDDCCI[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_DDCCI_ITEM ),  DDCCIValueText},
};
DrawRadioGroupType code DrawDDCCIIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2, NULL, DrawDDCCI}
};
#endif

#if  FreeSyncMenu_Enable
RadioTextType code DrawFreeSync[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_FreeSync_ITEM ),  FreeSyncValueText},
};
DrawRadioGroupType code DrawFreeSyncIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2, NULL, DrawFreeSync}
};
#endif

#if Enable_Adjust_SharpnessMenu

NumberType code DrawSharpnessMenu_SharpnessNum[] =
{
	// Flags,	XPos,	YPos,	GetValue
	{dwiEnd, NumXposion, ( SUB_TEXT_YPOS + IconShift * Misc_Sharpness_ITEM),	GetSharpnessRealValue}
};
DrawNumberType code DrawSharpnessMenu_SharpnessNumber[] =
{
	// Flags,	ForeColor,					BackColor,								XPos,	YPos,	GetValue
	{CP_ExecItem, CP_ExecItem,  	DrawSharpnessMenu_SharpnessNum}
};

GaugeType code DrawSharpnessMenu_SharpnessGuagee[] =
{
	// Flags,	XPos,	YPos,	GetValue
	{dwiEnd,	GaugeXPosition, ( SUB_TEXT_YPOS + IconShift * Misc_Sharpness_ITEM),	GetSharpnessValue}
};
DrawGuageType code DrawSharpnessMenu_SharpnessGuage[] =
{
	//Flags,	ForeColor,	    			BackColor,						Length,	XPos,	YPos,	GetValue
	{CP_ExecItem, Color_2,  9, DrawSharpnessMenu_SharpnessGuagee}
};

#endif





MenuItemType code MiscMenuItems[] =
{
	#if HKC_INPUTSELECT_MODE
// 0 InputSelect
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_InputSource_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		InputSelectMenu,//NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		InputSelectText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawInputSelectIconRatioText,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable // Flags
	},

	#else
	#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
	// 0 InputSelect
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_InputSource_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		InputSelectMenu,//NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		InputSelectText, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawInputSelectIconRatioText,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable // Flags
	},
	#endif
	#endif
	#if AudioFunc
	#if EANBLE_MUTE_ON_OFF

	// 0 Mute
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_Mute_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		MuteMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		MuteText,// DisplayText;
		NaviKeyEvent,// petit 20130929 for all scaler unify
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawMuteRatioText,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable
		#if Disable_VgaToAdjustVolume
		| mibAutioDisable
		#endif
	},
	#endif
	// 0 Volume
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_Volume_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		VolumeMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		VolumeText,// DisplayText;
		NaviKeyEvent,// petit 20130929 for all scaler unify
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawVolumeNumber,// DrawNumberType
			DrawVolumeGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
		#if Disable_VgaToAdjustVolume
		| mibAutioDisable
		#endif

	},
	#endif
	#if Enable_Adjust_SharpnessMenu
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_Sharpness_ITEM),		// XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		SharpnessMenu, 			// NextMenuPage;
		DWI_Text,						// DrawMenuItemType;
		SharpnessText, 						// DisplayText;
		NaviKeyEvent, 			// KeyEvent;
		{
			NULL,								// AdjustFunction
			NULL								// ExecFunction
		},									// *DisplayValue;
		{
			DrawSharpnessMenu_SharpnessNumber,								// DrawNumberType
			DrawSharpnessMenu_SharpnessGuage,								// DrawGuageType
			NULL			// DrawRadioGroupType
		},
		NULL, // Fonts
		mibSelectable 						// Flags
	},

	#endif

	#if  DDCCI_ENABLE && DDCCCIMenu_Enable
	// DDCCI
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_DDCCI_ITEM ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		DDCCIMenu,//NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		DDCCIText,// DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawDDCCIIconRatioText,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable// Flags
	},
	#endif

	#if PresetMode_Enable
	#if ENABLE_RTE
// 4 Overdrive
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_Overdrive_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OverdriveMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		OverdriveText,  // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawOverdriveIconRatioText // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable | mibODDisable // Flags  		// 130402 Modify
	},
	#endif
	#endif

	#if (LowBlueLightType==LowBlueLight_Misc_Guage)

	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_LowBlueLigth_Item), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		LowBlueLightMenu,//NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		LowBlueLightText, // DisplayText;
		NaviKeyEvent,
		{
			NULL, //,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawLowBlueLightMenu_LowBlueLightNumber,// DrawNumberType
			DrawLowBlueLightMenu_LowBlueLightGuage,// DrawGuageType
			NULL,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable // Flags
	},
	#elif   (LowBlueLightType==LowBlueLight_Misc_Group)
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_LowBlueLigth_Item), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		LowBlueLightMenu,//NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		LowBlueLightText, // DisplayText;
		NaviKeyEvent,
		{
			NULL, //,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawLowBlueLightMenuIconRatioText,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable // Flags
	},
	#endif


	#if FreeSyncMenu_Enable
	// DDCCI
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_FreeSync_ITEM ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		FreeSyncMenu,//NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FreeSyncText,// DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawFreeSyncIconRatioText,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable | mibFreeSyncDisable // Flags
	},
	#endif
};

#if AudioFunc

//============ MuteMenuItem==============
#if EANBLE_MUTE_ON_OFF

MenuItemType code MuteMenuItems[] =
{
	// 0 Volume
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_Mute_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OSD_MiscMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		MuteText,// DisplayText;
		AdjusterKeyEvent,// petit 20130929 for all scaler unify
		{
			SwitchMute,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawMuteRatioText,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#endif
//============ Volume MenuItem==============
MenuItemType code VolumeMenuItems[] =
{
	// 0 Volume
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_Volume_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OSD_MiscMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		VolumeText,// DisplayText;
		AdjusterKeyEvent,// petit 20130929 for all scaler unify
		{
			AdjustVolume,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawVolumeNumber,// DrawNumberType
			DrawVolumeGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#endif

#if Enable_Adjust_SharpnessMenu
MenuItemType code SharpnessMenuItems[] =
{
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_Sharpness_ITEM), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OSD_MiscMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		SharpnessText, // DisplayText;
		AdjusterKeyEvent,
		{
			AdjustSharpness,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawSharpnessMenu_SharpnessNumber,								// DrawNumberType
			DrawSharpnessMenu_SharpnessGuage,								// DrawGuageType
			NULL			// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#endif


//------------- DCCCIMenuItem  --------------------
#if DDCCI_ENABLE && DDCCCIMenu_Enable
MenuItemType code DDCCIMenuItems[] =
{
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_DDCCI_ITEM ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OSD_MiscMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		DDCCIText, // DisplayText;
		AdjustNoExecKeyEvent,
		{
			AdjustDDCCI,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawDDCCIIconRatioText,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#endif
//------------- FreeSyncMenuItem  --------------------
#if FreeSyncMenu_Enable
MenuItemType code FreeSyncMenuItems[] =
{
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + IconShift * Misc_FreeSync_ITEM ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		OSD_MiscMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FreeSyncText, // DisplayText;
		AdjustNoExecKeyEvent,
		{
			AdjustFreeSync,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawFreeSyncIconRatioText,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#endif









//------------- InputInfoMenu  --------------------
MenuItemType code InputInfoMenuItems[] =
{
	{
		0, 2, // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_UnselectItem,  Color_2, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_CenterPropText,// DrawMenuItemType;
		InputConnectorText, // DisplayText;
		NothingKeyEvent,// KeyEvent
		{
			NULL, // AdjustFunction
			NULL    // ExecFunction
		},// *DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL//DrawInputInfoIconRationText   // DrawRadioGroupType
		},
		NULL, //Font
		NULL // Flags
	}
};

//====================================================






















#if 0//AudioFunc && ENABLE_OSD_HotKeyVolume
//--------------------VolumeNumber--------------------------
NumberType code VolumeNumber[] =
{
	// Flags,   XPos,   YPos,   GetValue
	{dwiEnd,        19,  4, GetVolumeValue},
};
DrawNumberType code DrawVolumeNumber[] =
{
	// F ForeColor, BackColor,  GetValue
	CP_ExecItem, CP_ExecItem,     VolumeNumber
};
//--------------------VolumeIconGuge--------------------------
GaugeType code VolumeGuage[] =
{
	// Flags    XPos,   YPos,   GetValue
	{dwiEnd,    9,     4,      GetVolumeValue},
};
DrawGuageType code DrawVolumeGuage[] =
{
	//  ForeColor,  BackColor,  Length,,    GetValue
	CP_ExecItem, Color_2,  10,  VolumeGuage
};
#endif



//================= ColorTempItems ======================


#if Hotkey_DCR_Enable
MenuItemType code HotKeyDCRMenuItems[] =
{
	//0  Icon
	{
		HotIconXPos, HotIconYPos, // XPos, YPos;
		0, 0, // ForeColor, BackColor;
		0, 3, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Icon,// DrawMenuItemType;
		NULL,// DisplayText;
		ECOHotKeyEvent,// KeyEvent
		{
			AdjustDcrMode, // AdjustFunction
			NULL    // ExecFunction
		},// *DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	}
};
#endif




#if HotExpansionAdjust
MenuItemType code HotKeyExpansionMenuItems[] =
{
	//0  Icon
	{
		HotIconXPos, HotIconYPos, // XPos, YPos;
		0, 0, // ForeColor, BackColor;
		0, 3, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Icon,// DrawMenuItemType;
		NULL,// DisplayText;
		ExpansionHotKeyEvent,// KeyEvent	//110301 Modify
		{
			AdjustExpansionMode, // AdjustFunction
			NULL    // ExecFunction
		},// *DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	}
};

#endif


#if AudioFunc && ENABLE_OSD_HotKeyVolume

NumberType code DrawHotKeyVolumeIconNum[] =
{
	// Flags,	XPos,	YPos,	GetValue
	{dwiEnd,	18,	4,	GetVolumeValue}
};
DrawNumberType code DrawHotKeyVolumeIconNumber[] =
{
	// Flags,	ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{CP_UnselectItem, Color_2, DrawHotKeyVolumeIconNum}
};

GaugeType code DrawHotKeyVolumeIconGuagee[] =
{
	// Flags,	XPos,	YPos,	GetValue
	{dwiEnd,	5,	4,	GetVolumeValue}
};
GaugeType code DrawHotKeyVolumeIconGuage[] =
{
	// Flags,	ForeColor,	BackColor,	Length,	XPos,	YPos,	GetValue
	{CP_UnselectItem, Color_2,	14, DrawHotKeyVolumeIconGuagee}
};
//============ Volume MenuItem==============
MenuItemType code HotKeyVolumeMenuItems[] =
{
	// 0 Volume
	{
		0, 2, // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_UnselectItem, Color_2, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_CenterPropText,// DrawMenuItemType;
		VolumeText,// DisplayText;
		HotAudioKeyEvent,// petit 20130929 for all scaler unify
		{
			AdjustVolume,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			DrawHotKeyVolumeIconNumber,// DrawNumberType
			DrawHotKeyVolumeIconGuage,// DrawGuageType
			NULL,// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#endif
#if Hotkey_Bri_Enable
NumberType code DrawHotKeyBrightnessIconNum[] =
{
	// Flags,	XPos,	YPos,	GetValue
	{dwiEnd,	18,	4,	GetBrightnessValue}
};
DrawNumberType code DrawHotKeyBrightnessIconNumber[] =
{
	// Flags,	ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{CP_UnselectItem, Color_2, DrawHotKeyBrightnessIconNum}
};

GaugeType code DrawHotKeyBrightnessIconGuagee[] =
{
	// Flags,	XPos,	YPos,	GetValue
	{dwiEnd,	5,	4,	GetBrightnessValue}
};
GaugeType code DrawHotKeyBrightnessIconGuage[] =
{
	// Flags,	ForeColor,	BackColor,	Length,	XPos,	YPos,	GetValue
	{CP_UnselectItem, Color_2,	14, DrawHotKeyBrightnessIconGuagee}
};
MenuItemType code HotKeyBriMenuItems[] =
{
	{
		0, 2, // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_UnselectItem, Color_2, // SelForeColor, SelBackColor;
		RootMenu,///NextMenuPage;
		DWI_CenterPropText,// DrawMenuItemType;
		BrightnessText, // 2007/10/24  by KK   VolumeText, // DisplayText;
		HotKeyEvent,
		{
			AdjustBrightness,// AdjustFunction
			NULL,//AutoConfig// ExecFunction
		},
		{
			DrawHotKeyBrightnessIconNumber,// DrawNumberType
			DrawHotKeyBrightnessIconGuage,// DrawGuageType
			NULL,//DrawMenuRadioGroup,//DrawAutoSetupRadioGroup // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#endif
#if Hotkey_Con_Enable
NumberType code DrawHotKeyContrastIconNum[] =
{
	// Flags,	XPos,	YPos,	GetValue
	{dwiEnd,	18,	4,	GetContrastValue}
};
DrawNumberType code DrawHotKeyContrastIconNumber[] =
{
	// Flags,	ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{CP_UnselectItem, Color_2, DrawHotKeyContrastIconNum}
};

GaugeType code DrawHotKeyContrastIconGuagee[] =
{
	// Flags,	XPos,	YPos,	GetValue
	{dwiEnd,	5,	4,	GetContrastValue}
};
GaugeType code DrawHotKeyVolumeIconGuage[] =
{
	// Flags,	ForeColor,	BackColor,	Length,	XPos,	YPos,	GetValue
	{CP_UnselectItem, Color_2,	14, DrawHotKeyContrastIconGuagee}
};

MenuItemType code HotKeyConMenuItems[] =
{
	{
		0, 2, // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_UnselectItem, Color_2, // SelForeColor, SelBackColor;
		RootMenu,///NextMenuPage;
		DWI_CenterPropText,// DrawMenuItemType;
		ContrastText, // 2007/10/24  by KK   VolumeText, // DisplayText;
		HotKeyEvent,
		{
			AdjustContrast,// AdjustFunction
			NULL,//AutoConfig// ExecFunction
		},
		{
			DrawHotKeyContrastIconNumber,// DrawNumberType
			DrawHotKeyVolumeIconGuage,// DrawGuageType
			NULL,//DrawMenuRadioGroup,//DrawAutoSetupRadioGroup // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};
#endif
#if HotInputSelect

MenuItemType code HotInputSelectMenuItems[] =
{
	#if ENABLE_VGA_INPUT					//130129_1  Henry follow Spec
	{
		0, 2 + HotInput_VGA_ITEM, // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		RootMenu,///NextMenuPage;
		DWI_CenterPropText,// DrawMenuItemType;
		AnalogText, // DisplayText;
		HotInputSelectKeyEvent,
		{
			NULL,// AdjustFunction
			ChangeSourceToAnalog// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	#endif

	#if ENABLE_DVI_INPUT

	{
		0, 2 + HotInput_DVI_ITEM, // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		RootMenu,///NextMenuPage;
		DWI_CenterPropText,// DrawMenuItemType;
		DigitalText, // DisplayText;
		HotInputSelectKeyEvent,
		{
			NULL,// AdjustFunction
			ChangeSourceToDigital// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	#endif

	#if ENABLE_HDMI_INPUT
	{
		0, 2 + HotInput_HDMI_ITEM, // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		RootMenu,///NextMenuPage;
		DWI_CenterPropText,// DrawMenuItemType;
		HDMIText,
		HotInputSelectKeyEvent,
		{
			NULL,// AdjustFunction
			ChangeSourceToHDMI// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	#endif

	#if ENABLE_HDMI2ND_INPUT
	{
		0, 2 + HotInput_HDMI2_ITEM, // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		RootMenu,///NextMenuPage;
		DWI_CenterPropText,// DrawMenuItemType;
		HDMI2Text,
		HotInputSelectKeyEvent,
		{
			NULL,// AdjustFunction
			ChangeSourceToHDMI// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	#endif

	#if ENABLE_DP_INPUT
	{
		0, 2 + HotInput_DP_ITEM, // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		RootMenu,///NextMenuPage;
		DWI_CenterPropText,// DrawMenuItemType;
		DPText,
		HotInputSelectKeyEvent,
		{
			NULL,// AdjustFunction
			ChangeSourceToDP// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			NULL// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},

	#endif
};

#endif


#if Hot_Corss_ColorSelect
MenuItemType code HotCorssMenuItems[] =
{
///0
	{
		0, 0, // XPos, YPos;
		CPC_Color1, CPC_Color0,                       // ForeColor, BackColor;      0x00,0x02, //  modify 2007.04.17
		CPC_Color1, CPC_Color0,           // SelForeColor, SelBackColor;0x00,0x06, //  modify 2007.04.17
		RootMenu,                                        // NextMenuPage;
		DWI_8x5Icon,                                         // DrawMenuItemType;
		CorssIcon,                                         // DisplayText;
		HotCorssSelectKeyEvent,//NaviExecKeyEvent,
		{
			NULL,	                                          // AdjustFunction
			NULL,		                        // ExecFunction
		},
		{
			NULL,	                                          // DrawNumberType
			NULL,	                                          // DrawGuageType
			NULL,	                                          // DrawRadioGroupType
		},
		NULL,                                             // Fonts
		mibSelectable                                     // Flags
	},
///1
	{
		0, 0, // XPos, YPos;
		CPC_ColorB, CPC_Color0,                       // ForeColor, BackColor;      0x00,0x02, //  modify 2007.04.17
		CPC_ColorB, CPC_Color0,          // SelForeColor, SelBackColor;0x00,0x06, //  modify 2007.04.17
		RootMenu,                                        // NextMenuPage;
		DWI_8x5Icon,                                         // DrawMenuItemType;
		CorssIcon,                                         // DisplayText;
		HotCorssSelectKeyEvent,//NaviExecKeyEvent,
		{
			NULL,	                                          // AdjustFunction
			NULL,		                        // ExecFunction
		},
		{
			NULL,	                                          // DrawNumberType
			NULL,	                                          // DrawGuageType
			NULL,	                                          // DrawRadioGroupType
		},
		NULL,                                             // Fonts
		mibSelectable                                     // Flags
	},
///2
	{
		0, 0, // XPos, YPos;
		CPC_ColorF, CPC_Color0,                      // ForeColor, BackColor;      0x00,0x02, //  modify 2007.04.17
		CPC_ColorF, CPC_Color0,           // SelForeColor, SelBackColor;0x00,0x06, //  modify 2007.04.17
		RootMenu,                                        // NextMenuPage;
		DWI_8x5Icon,                                         // DrawMenuItemType;
		CorssIcon,                                         // DisplayText;
		HotCorssSelectExitKeyEvent,//NaviExecKeyEvent,
		{
			NULL,	                                          // AdjustFunction
			NULL,		                        // ExecFunction
		},
		{
			NULL,	                                          // DrawNumberType
			NULL,	                                          // DrawGuageType
			NULL,	                                          // DrawRadioGroupType
		},
		NULL,                                             // Fonts
		mibSelectable                                     // Flags
	},
};
#elif Hot_Corss_FY_ColorSelect
MenuItemType code HotCorssMenuItems[] =
{
///0
	{
		0, 0, // XPos, YPos;
		CPC_ColorF, CPC_Color0,                      // ForeColor, BackColor;      0x00,0x02, //  modify 2007.04.17
		CPC_ColorF, CPC_Color0,           // SelForeColor, SelBackColor;0x00,0x06, //  modify 2007.04.17
		RootMenu,                                        // NextMenuPage;
		DWI_10x6Icon,                                         // DrawMenuItemType;
		CorssIcon1,                                         // DisplayText;
		HotCorssSelectKeyEvent,//NaviExecKeyEvent,
		{
			NULL,	                                          // AdjustFunction
			NULL,		                        // ExecFunction
		},
		{
			NULL,	                                          // DrawNumberType
			NULL,	                                          // DrawGuageType
			NULL,	                                          // DrawRadioGroupType
		},
		NULL,                                             // Fonts
		mibSelectable                                     // Flags
	},
///1
	{
		0, 0, // XPos, YPos;
		CPC_ColorB, CPC_Color0,                       // ForeColor, BackColor;      0x00,0x02, //  modify 2007.04.17
		CPC_ColorB, CPC_Color0,          // SelForeColor, SelBackColor;0x00,0x06, //  modify 2007.04.17
		RootMenu,                                        // NextMenuPage;
		DWI_10x6Icon,                                         // DrawMenuItemType;
		CorssIcon1,                                         // DisplayText;
		HotCorssSelectKeyEvent,//NaviExecKeyEvent,
		{
			NULL,	                                          // AdjustFunction
			NULL,		                        // ExecFunction
		},
		{
			NULL,	                                          // DrawNumberType
			NULL,	                                          // DrawGuageType
			NULL,	                                          // DrawRadioGroupType
		},
		NULL,                                             // Fonts
		mibSelectable                                     // Flags
	},
///2
	{
		0, 0, // XPos, YPos;
		CPC_ColorF, CPC_Color0,                      // ForeColor, BackColor;      0x00,0x02, //  modify 2007.04.17
		CPC_ColorF, CPC_Color0,           // SelForeColor, SelBackColor;0x00,0x06, //  modify 2007.04.17
		RootMenu,                                        // NextMenuPage;
		DWI_10x6Icon,                                         // DrawMenuItemType;
		CorssIcon2,                                         // DisplayText;
		HotCorssSelectKeyEvent,//NaviExecKeyEvent,
		{
			NULL,	                                          // AdjustFunction
			NULL,		                        // ExecFunction
		},
		{
			NULL,	                                          // DrawNumberType
			NULL,	                                          // DrawGuageType
			NULL,	                                          // DrawRadioGroupType
		},
		NULL,                                             // Fonts
		mibSelectable                                     // Flags
	},
///0
	{
		0, 0, // XPos, YPos;
		CPC_ColorB, CPC_Color0,                       // ForeColor, BackColor;      0x00,0x02, //  modify 2007.04.17
		CPC_ColorB, CPC_Color0,          // SelForeColor, SelBackColor;0x00,0x06, //  modify 2007.04.17
		RootMenu,                                        // NextMenuPage;
		DWI_10x6Icon,                                         // DrawMenuItemType;
		CorssIcon2,                                         // DisplayText;
		HotCorssSelectKeyEvent,//NaviExecKeyEvent,
		{
			NULL,	                                          // AdjustFunction
			NULL,		                        // ExecFunction
		},
		{
			NULL,	                                          // DrawNumberType
			NULL,	                                          // DrawGuageType
			NULL,	                                          // DrawRadioGroupType
		},
		NULL,                                             // Fonts
		mibSelectable                                     // Flags
	},
///1
	{
		0, 0, // XPos, YPos;
		CPC_ColorF, CPC_Color0,                      // ForeColor, BackColor;      0x00,0x02, //  modify 2007.04.17
		CPC_ColorF, CPC_Color0,           // SelForeColor, SelBackColor;0x00,0x06, //  modify 2007.04.17
		RootMenu,                                        // NextMenuPage;
		DWI_10x6Icon,                                         // DrawMenuItemType;
		CorssIcon3,                                         // DisplayText;
		HotCorssSelectKeyEvent,//NaviExecKeyEvent,
		{
			NULL,	                                          // AdjustFunction
			NULL,		                        // ExecFunction
		},
		{
			NULL,	                                          // DrawNumberType
			NULL,	                                          // DrawGuageType
			NULL,	                                          // DrawRadioGroupType
		},
		NULL,                                             // Fonts
		mibSelectable                                     // Flags
	},
///2
	{
		0, 0, // XPos, YPos;
		CPC_ColorB, CPC_Color0,                       // ForeColor, BackColor;      0x00,0x02, //  modify 2007.04.17
		CPC_ColorB, CPC_Color0,          // SelForeColor, SelBackColor;0x00,0x06, //  modify 2007.04.17
		RootMenu,                                        // NextMenuPage;
		DWI_10x6Icon,                                         // DrawMenuItemType;
		CorssIcon3,                                         // DisplayText;
		HotCorssSelectExitKeyEvent,//NaviExecKeyEvent,
		{
			NULL,	                                          // AdjustFunction
			NULL,		                        // ExecFunction
		},
		{
			NULL,	                                          // DrawNumberType
			NULL,	                                          // DrawGuageType
			NULL,	                                          // DrawRadioGroupType
		},
		NULL,                                             // Fonts
		mibSelectable                                     // Flags
	},
};
#elif Hot_Corss_FND_Select
MenuItemType code HotCorssMenuItems[] =
{
///0
	{
		0, 0, // XPos, YPos;
		CPC_ColorF, CPC_Color0,                      // ForeColor, BackColor;      0x00,0x02, //  modify 2007.04.17
		CPC_ColorF, CPC_Color0,           // SelForeColor, SelBackColor;0x00,0x06, //  modify 2007.04.17
		RootMenu,                                        // NextMenuPage;
		DWI_10x6Icon,                                         // DrawMenuItemType;
		CorssIcon1,                                         // DisplayText;
		HotCorssSelectKeyEvent,//NaviExecKeyEvent,
		{
			NULL,	                                          // AdjustFunction
			NULL,		                        // ExecFunction
		},
		{
			NULL,	                                          // DrawNumberType
			NULL,	                                          // DrawGuageType
			NULL,	                                          // DrawRadioGroupType
		},
		NULL,                                             // Fonts
		mibSelectable                                     // Flags
	},

///2
	{
		0, 0, // XPos, YPos;
		CPC_ColorF, CPC_Color0,                      // ForeColor, BackColor;      0x00,0x02, //  modify 2007.04.17
		CPC_ColorF, CPC_Color0,           // SelForeColor, SelBackColor;0x00,0x06, //  modify 2007.04.17
		RootMenu,                                        // NextMenuPage;
		DWI_10x6Icon,                                         // DrawMenuItemType;
		CorssIcon2,                                         // DisplayText;
		HotCorssSelectKeyEvent,//NaviExecKeyEvent,
		{
			NULL,	                                          // AdjustFunction
			NULL,		                        // ExecFunction
		},
		{
			NULL,	                                          // DrawNumberType
			NULL,	                                          // DrawGuageType
			NULL,	                                          // DrawRadioGroupType
		},
		NULL,                                             // Fonts
		mibSelectable                                     // Flags
	},

///1
	{
		0, 0, // XPos, YPos;
		CPC_ColorF, CPC_Color0,                      // ForeColor, BackColor;      0x00,0x02, //  modify 2007.04.17
		CPC_ColorF, CPC_Color0,           // SelForeColor, SelBackColor;0x00,0x06, //  modify 2007.04.17
		RootMenu,                                        // NextMenuPage;
		DWI_10x6Icon,                                         // DrawMenuItemType;
		CorssIcon3,                                         // DisplayText;
		HotCorssSelectKeyEvent,//NaviExecKeyEvent,
		{
			NULL,	                                          // AdjustFunction
			NULL,		                        // ExecFunction
		},
		{
			NULL,	                                          // DrawNumberType
			NULL,	                                          // DrawGuageType
			NULL,	                                          // DrawRadioGroupType
		},
		NULL,                                             // Fonts
		mibSelectable                                     // Flags
	},

};
#endif








//------------- InputSelectMenuItem  --------------------
#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
#if ENABLE_VGA_INPUT
RadioTextType code DrawInputTypeAnalog[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + 0 * 2 ),     AnalogText},
};
DrawRadioGroupType code DrawInputTypeAnalogRationText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2,  NULL, DrawInputTypeAnalog}
};
#endif
#if ENABLE_DVI_INPUT
RadioTextType code DrawInputTypeDigital[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + 0 * 2 ),     DigitalText},
};
DrawRadioGroupType code DrawInputTypeDigitalRationText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2,  NULL, DrawInputTypeDigital}
};
#endif

#if ENABLE_HDMI_INPUT
RadioTextType code DrawInputTypeHDMI[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + 0 * 2 ),     HDMIText},
};
DrawRadioGroupType code DrawInputTypeHDMIRationText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2,  NULL, DrawInputTypeHDMI}
};
#endif


#if ENABLE_HDMI2ND_INPUT
RadioTextType code DrawInputTypeHDMI2[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + 0 * 2 ),     HDMI2Text},
};
DrawRadioGroupType code DrawInputTypeHDMI2RationText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2,  NULL, DrawInputTypeHDMI2}
};
#endif
#if ENABLE_DP_INPUT
RadioTextType code DrawInputTypeDP[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + 0 * 2 ),     DPText},// 20130109
};
DrawRadioGroupType code DrawInputTypeDPRationText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2,  NULL, DrawInputTypeDP}
};
#endif
#if ENABLE_AutoDetech
RadioTextType code DrawInputTypeAuto[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + 0 * 2 ),     AutoText},
};
DrawRadioGroupType code DrawInputTypeAutoRationText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2,  NULL, DrawInputTypeAuto}
};
#endif
#if HKC_INPUTSELECT_MODE
//================================================================
RadioTextType code DrawInputTypeRation[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiCenterArrowAlign | dwiEnd, SUB_TEXT_XPOS, SUB_TEXT_YPOS,     InputTypeRationText},
};
DrawRadioGroupType code DrawInputTypeRationText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   Color_2,  NULL, DrawInputTypeRation}
};
#endif
MenuItemType code InputSelectMenuItems[] =
    #if HKC_INPUTSELECT_MODE
{
	{
		SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + 0 * 2 ), // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
		InputSelectMenu,// NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		InputSelectText, // DisplayText;
		AdjusterKeyExecAEvent,// AdjusterKeyEvent,//AdjustExecKeyEvent,
		{
			AdjustInputSource,//AdjustInputSource,// AdjustFunction
			SetInputSourceChange,//SetInputToAuto,// ExecFunction
		},
		{
			NULL,// DrawNumberType
			NULL,// DrawGuageType
			DrawInputTypeRationText,//DrawMenuRadioGroup,
		},
		NULL, //Font
		mibSelectable // Flags
	},
};

    #else
    {
        #if ENABLE_AutoDetech
{
	SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + 0 * 2 ), // XPos, YPos;
	CP_UnselectItem, Color_2, // ForeColor, BackColor;
	CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
	MainMenu,///NextMenuPage;
	DWI_Text,// DrawMenuItemType;
	InputSelectText, // DisplayText;
	NaviExecKeyEvent,//AdjustExecKeyEvent,
	{
		NULL,//AdjustInputSource,// AdjustFunction
		SetInputToAuto,// ExecFunction
	},
	{
		NULL,// DrawNumberType
		NULL,// DrawGuageType
		DrawInputTypeAutoRationText,//DrawMenuRadioGroup,
	},
	NULL, //Font
	mibSelectable // Flags
},
        #endif
#if ENABLE_VGA_INPUT
{
	SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + 0 * 2 ), // XPos, YPos;
	CP_UnselectItem, Color_2, // ForeColor, BackColor;
	CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
	MainMenu,///NextMenuPage;
	DWI_Text,// DrawMenuItemType;
	InputSelectText, // DisplayText;
	NaviExecKeyEvent,//AdjustExecKeyEvent,
	{
		NULL,//AdjustInputSource,// AdjustFunction
		#if ENABLE_AutoDetech
		SetInputToAnalog,// ExecFunction
		#else
		ChangeSourceToAnalog
		#endif
	},
	{
		NULL,// DrawNumberType
		NULL,// DrawGuageType
		DrawInputTypeAnalogRationText,//DrawMenuRadioGroup,
	},
	NULL, //Font
	mibSelectable // Flags
},
#endif
#if ENABLE_DVI_INPUT
{
	SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + 0 * 2 ), // XPos, YPos;
	CP_UnselectItem, Color_2, // ForeColor, BackColor;
	CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
	MainMenu,///NextMenuPage;
	DWI_Text,// DrawMenuItemType;
	InputSelectText, // DisplayText;
	NaviExecKeyEvent,//AdjustExecKeyEvent,
	{
		NULL, // AdjustFunction
		#if ENABLE_AutoDetech
		SetInputToDigital,//AutoConfig// ExecFunction
		#else
		ChangeSourceToDigital,
		#endif
	},
	{
		NULL,// DrawNumberType
		NULL,// DrawGuageType
		DrawInputTypeDigitalRationText,//DrawMenuRadioGroup,
	},
	NULL, //Font
	mibSelectable // Flags
},
#endif
#if ENABLE_HDMI_INPUT
{
	SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + 0 * 2 ), // XPos, YPos;
	CP_UnselectItem, Color_2, // ForeColor, BackColor;
	CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
	MainMenu,///NextMenuPage;
	DWI_Text,// DrawMenuItemType;
	InputSelectText, // DisplayText;
	NaviExecKeyEvent,//AdjustExecKeyEvent,
	{
		NULL, // AdjustFunction
		#if ENABLE_AutoDetech
		SetInputToHDMI,// ExecFunction
		#else
		ChangeSourceToHDMI,
		#endif
	},
	{
		NULL,// DrawNumberType
		NULL,// DrawGuageType
		DrawInputTypeHDMIRationText,//DrawMenuRadioGroup,
	},
	NULL, //Font
	mibSelectable // Flags

},
#if ENABLE_HDMI2ND_INPUT
{
	SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + 0 * 2 ), // XPos, YPos;
	CP_UnselectItem, Color_2, // ForeColor, BackColor;
	CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
	MainMenu,///NextMenuPage;
	DWI_Text,// DrawMenuItemType;
	InputSelectText, // DisplayText;
	NaviExecKeyEvent,//AdjustExecKeyEvent,
	{
		NULL, // AdjustFunction
		#if ENABLE_AutoDetech
		SetInputToHDMI,// ExecFunction
		#else
		ChangeSourceToHDMI2,
		#endif
	},
	{
		NULL,// DrawNumberType
		NULL,// DrawGuageType
		DrawInputTypeHDMI2RationText,//DrawMenuRadioGroup,
	},
	NULL, //Font
	mibSelectable // Flags

},
#endif
#endif
#if ENABLE_DP_INPUT
{
	SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + 0 * 2 ), // XPos, YPos;
	CP_UnselectItem, Color_2, // ForeColor, BackColor;
	CP_SelectItem, Color_2, // SelForeColor, SelBackColor;
	MainMenu,///NextMenuPage;
	DWI_Text,// DrawMenuItemType;
	InputSelectText, // DisplayText;

	NaviExecKeyEvent,//AdjustExecKeyEvent,

	{
		NULL, // AdjustFunction
		#if ENABLE_AutoDetech
		SetInputToDP,// ExecFunction
		#else
		ChangeSourceToDP
		#endif
	},
	{
		NULL,// DrawNumberType
		NULL,// DrawGuageType
		DrawInputTypeDPRationText,//DrawMenuRadioGroup,
	},
	NULL, //Font
	mibSelectable // Flags
},
#endif
    };
    #endif
#endif




MenuItemType code ExitMenuItems[] =
{
	// Describe
	{
		1, 6, // XPos, YPos;
		0x10, Color_2, // ForeColor, BackColor;
		0x10, Color_2, // SelForeColor, SelBackColor;
		ExitMenu,///NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		NaviKeyEvent,
		{
			NULL,// AdjustFunction
			NULL,// ExecFunction
		},
		{
			NULL,   // DrawNumberType
			NULL,   // DrawGuageType
			NULL,   // DrawRadioGroupType
		},
		NULL, //Font
		NULL // Flags
	},
};

#if Hotkey_ECO_Text_Enable
RadioTextType code DrawHotECOText[] =
{
	// Flags,            XPos,  YPos,   DisplayText
	{dwiRadioGroup | dwiCenterText | dwiEnd, 8, 3,     ECOModeValue},
};
DrawRadioGroupType code DrawHotECOIconRatioText[] =
{
	//ForeColor,    BackColor,  GetValue    RadioText
	{CP_UnselectItem,   CPC_Background, NULL,  DrawHotECOText}
};
#endif

MenuItemType code HotKeyECOMenuItems[] =
{
	//0  Icon
	{
		#if Hotkey_ECO_Text_Enable
		0, 3,
		#else
		HotIconXPos, HotIconYPos, // XPos, YPos;
		#endif
		0, 0, // ForeColor, BackColor;
		0, 3, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		#if Hotkey_ECO_Text_Enable
		DWI_Nothing,
		#else
		DWI_Icon,// DrawMenuItemType;
		#endif
		NULL,// DisplayText;
		ECOHotKeyEvent,// KeyEvent
		{
			AdjustECOMode, // AdjustFunction
			NULL    // ExecFunction
		},// *DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			#if Hotkey_ECO_Text_Enable
			DrawHotECOIconRatioText
			#else
			NULL// DrawRadioGroupType
			#endif
		},
		NULL, //Font
		mibSelectable // Flags
	}
};


#if DDCCI_ENABLE && DDCCCIMenu_Enable
//------------- DdcciInfoMenu  --------------------
RadioTextType code DrawDdcciInfo[] =
{
	// Flags,            XPos,	YPos,	DisplayText
	{dwiRadioGroup | dwiEnd,	20, 4,  	DDCCIValueText},

};
DrawRadioGroupType code DrawDdcciInfoIconRationText[] =
{
	//ForeColor,	BackColor,	GetValue	RadioText
	{0,	6, NULL, DrawDdcciInfo}
};
MenuItemType code DdcciInfoMenuItems[] =
{
	//0 Reset Icon
	{
		4, 4, // XPos, YPos;
		CP_BlackColor, CP_WhiteColor, // ForeColor, BackColor;
		0,  6, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		DDCCIText, // DisplayText;
		LockKeyEvent,// KeyEvent //Benz 2007.4.24   21:48:06
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// *DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawDdcciInfoIconRationText	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	}
};
#endif


MenuItemType code AutoMenuItems[] =
{
	{
		1, 3, // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_UnselectItem, Color_2, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_CenterPropText,// DrawMenuItemType;
		#if AboutDSUBFunc_Enable
		AutoConfigText,// DisplayText;
		#else
		NULL,
		#endif
		NothingKeyEvent,// KeyEvent
		{
			NULL, // AdjustFunction
			NULL    // ExecFunction
		},// *DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	}
};



#if AboutDSUBFunc_Enable
MenuItemType code AutoColorMenuItems[] =
{
	//0 Reset Icon
	{
		10, 5, // XPos, YPos;
		CP_BlackColor, CP_WhiteColor, // ForeColor, BackColor;
		0,  6, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		AutoColorMenuText,//LogoText, // DisplayText;
		NothingKeyEvent,// KeyEvent
		{
			NULL, // AdjustFunction
			NULL	// ExecFunction
		},// *DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL, // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	}
};
#endif






//===============================================================
#if EN_ShowInfoUnderBurinInMenu

NumberType code BurinPanelOnTimeNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
// {0		,		12, 1,	GetPanelOnTimeValue} ,
// {0   	,		17, 1,	GetPanelOnTimeMValue},
	{dwiEnd | dwiHex,	15, 1,	GetCheckSumValue}
};
DrawNumberType code DrawBurinPanelOnTimeNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{	CP_RedColor,	CP_BlueColor,		BurinPanelOnTimeNumber}
};


RadioTextType code BurinText[] =
{
	// Flags, 	XPos,	YPos,	DisplayText
	#ifdef  Brand
	{0,			1,	0,	BrandNameText},
	{0,			9,	0,	ModelNameText},
	#else
	{0,			1,	0,	ModelNameText},
	#endif
	{ 0,		22, 	0,	VersionDateText},


//   {0, 				 1,1, 		 	F_BackLightText},
//   {0, 				 17,1,			 F_HourText},
//   {0, 				 22,1,			 F_MinText},


	#if Enable_Factory_Panel
	{0,	             1,	1,     CheckSumText},
	{0,			1,	2, PanelText},
	#else
	{0,	             1,	1,     CheckSumText},
	#endif
	{0,         1, 3,  ChipNameText},
	#ifdef  BoardName
	{0,         1, 4,  BoardNameText},
	#endif
	{dwiEnd,    1,	5,	ChangeDateText},

};

DrawRadioGroupType code DrawBurinRadioGroup[] =
{
	//ForeColor,	BackColor,		GetValue	RadioText
	{CP_WhiteColor,	CP_BlueColor,	NULL,	BurinText}
};

MenuItemType code BurninMenuItems[] =
{
	// Contrast Icon
	{
		2, 1, // XPos, YPos;
		0x04, CP_BlueColor, // ForeColor, BackColor;
		0x04, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_CenterText,// DrawMenuItemType;
		NULL, // DisplayText;
		NothingKeyEvent,// KeyEvent
		{
			NULL, // AdjustFunction
			NULL			// ExecFunction
		},// *DisplayValue;
		{
			DrawBurinPanelOnTimeNumber, // DrawNumberType
			NULL, // DrawGuageType
			DrawBurinRadioGroup	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	}
};
#else
MenuItemType code BurninMenuItems[] =
{
	// Contrast Icon
	{
		2, 1, // XPos, YPos;
		0x04, CP_WhiteColor, // ForeColor, BackColor;
		0x04, CP_WhiteColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_CenterText,// DrawMenuItemType;
		NULL, // DisplayText;
		NothingKeyEvent,// KeyEvent
		{
			NULL, // AdjustFunction
			NULL			// ExecFunction
		},// *DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	}
};
#endif

MenuItemType code LogoMenuItems[] =
{
	//0 Reset Icon
	{
		0, 9, // 8, // XPos, YPos;
		CP_BlackColor, CP_WhiteColor, // ForeColor, BackColor;
		CP_BlackColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		NULL,//DWI_Text,// DrawMenuItemType;
		NULL,//LogoText, // DisplayText;
		LogoKeyEvent,// KeyEvent
		{
			NULL, // AdjustFunction
			NULL	// ExecFunction
		},// *DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	}
};

#ifdef OffPower

MenuItemType code OffPowerWarningMenuItems[] =
{
	{
		2, 3, // XPos, YPos;
		CP_UnselectItem, Color_2,  // ForeColor, BackColor;
		CP_UnselectItem, Color_2,  // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_CenterPropText,// DrawMenuItemType;
		OffTimerM98Text, // DisplayText;
		OffTimerWarningKeyEvent,// KeyEvent	//110408 Modify
		{
			NULL, // AdjustFunction
			NULL    // ExecFunction
		},// *DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL   // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	{
		2, 4, // XPos, YPos;
		CP_UnselectItem, Color_2,  // ForeColor, BackColor;
		CP_UnselectItem, Color_2,  // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_CenterPropText,// DrawMenuItemType;
		MonitorOffText, // DisplayText;
		LockKeyEvent,// KeyEvent
		{
			NULL, // AdjustFunction
			NULL    // ExecFunction
		},// *DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL   // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	}

};
#endif




//==============================================================================================
MenuPageType code tblMenus[] =
{
	// 0 PowerOffMenu
	{
		16, 3, //	XSize, YSize;
		PowerOnMenu,// PrevMenuPage;
		PowerOffMenuItems, // MenuItems;
		sizeof(PowerOffMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		PowerOffSystem,// ExecFunction;
		NULL, // Fonts
		mpbInvisible | mpbStay // 	Flags;
	},
	// 1 PowerOnMenu
	{
		16, 3, //	XSize, YSize;
		RootMenu,// PrevMenuPage;
		NULL, // MenuItems;
		NULL, // MenuItemCount;
		PowerOnSystem,// ExecFunction;
		NULL, // Fonts
		mpbInvisible // 	Flags;
	},
	// 2 StandbyMenu
	{
		HOT_MENU_H_SIZE, HOT_MENU_V_SIZE, //  XSize, YSize;
		RootMenu,// PrevMenuPage;
		StandbyMenuItems, // MenuItems;
		sizeof( StandbyMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		EnablePowerDownCounter, // ExecFunction;
		MenuPage11, // Fonts
		mpbStay | mpbRedraw | mpbCenter // Flags;
	},

	/*
		// 3 SuspendOnMenu
		{
			24, 5, //	XSize, YSize;
			RootMenu,// PrevMenuPage;
			StandbyMenuItems, // MenuItems;
			sizeof(StandbyMenuItems)/sizeof(MenuItemType), // MenuItemCount;
			EnablePowerDownCounter, // ExecFunction;
			mpbStay //	 Flags;
		},
	*/
	// 3 SleepMenu
	{
		HOTKEY_X_SIZE/*29*/, 13, //	XSize, YSize;
		RootMenu,// PrevMenuPage;
		SleepMenuItems, // MenuItems;
		sizeof(SleepMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		EnablePowerDownCounter, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbRedraw//|mpbCenter //	 Flags;
	},
	// 4 CableNotConnectedMenu
	{
		HOT_MENU_H_SIZE, HOT_MENU_V_SIZE, //  XSize, YSize;
		RootMenu,// PrevMenuPage;
		CableNotConnectedMenuItems, // MenuItems;
		sizeof( CableNotConnectedMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		MenuPage10, // Fonts
		mpbMoving | mpbStay | mpbCenter // Flags;
	},
	// 5 UnsupportedModeMenu
	{
		HOT_MENU_H_SIZE, HOT_MENU_V_SIZE, //  XSize, YSize;
		RootMenu,// PrevMenuPage;
		UnsupportedModeMenuItems, // MenuItems;
		sizeof( UnsupportedModeMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		MenuPage9, // Fonts
		mpbMoving | mpbStay | mpbCenter | mpbRedraw // Flags;
	},
	// 6 RootMenu
	{
		16, 3, // XSize, YSize;
		RootMenu,// PrevMenuPage;
		RootMenuItems, // MenuItems;
		sizeof( RootMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		EnterRootMenu, // ExecFunction;
		NULL, // Fonts
		mpbInvisible | mpbStay //   Flags;
	},
////=================================================================/////
	//7 MainMenu
	{
		MAIN_MENU_H_SIZE,  MAIN_MENU_V_SIZE,  //	XSize, YSize;
		RootMenu,// PrevMenuPage;
		MainMenuItems, // MenuItems;
		sizeof(MainMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		NULL,   // ExecFunction;
		NULL,   // Fonts
		mpbStay | mpbBrowse | mpbRedraw //   Flags;
	},

	//7 OSD_BriContrastMenu
	{
		MAIN_MENU_H_SIZE,  MAIN_MENU_V_SIZE,  //	XSize, YSize;
		MainMenu,// PrevMenuPage;
		BriContrastMenuItems, // MenuItems;
		sizeof(BriContrastMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		NULL,   // ExecFunction;
		NULL,   // Fonts
		mpbStay//   Flags;
	},
	//8 PictureMenu
	{
		MAIN_MENU_H_SIZE,  MAIN_MENU_V_SIZE,  //	XSize, YSize;
		MainMenu,// PrevMenuPage;
		PictureMenuItems, // MenuItems;
		sizeof(PictureMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		NULL,   // ExecFunction;
		NULL,   // Fonts
		mpbStay//   Flags;
	},
	//9  RGBColorMenu
	{
		MAIN_MENU_H_SIZE,  MAIN_MENU_V_SIZE,  //	XSize, YSize;
		MainMenu,// PrevMenuPage;
		RGBMenuItems, // MenuItems;
		sizeof(RGBMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		NULL,   // ExecFunction;
		NULL,   // Fonts
		mpbStay//   Flags;
	},
	// 10 OsdMenu
	{
		MAIN_MENU_H_SIZE,  MAIN_MENU_V_SIZE,  //	XSize, YSize;
		MainMenu,// PrevMenuPage;
		OSDMenuItems, // MenuItems;
		sizeof(OSDMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		NULL,   // ExecFunction;
		MenuPage4,   // Fonts
		mpbStay//   Flags;
	},
	//12  SettingMenu
	{
		MAIN_MENU_H_SIZE,  MAIN_MENU_V_SIZE,  //	XSize, YSize;
		MainMenu,// PrevMenuPage;
		SettingMenuItems, // MenuItems;
		sizeof(SettingMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		NULL,   // ExecFunction;
		NULL,   // Fonts
		mpbStay//   Flags;
	},
	//13  OSD_MiscMenu
	{
		MAIN_MENU_H_SIZE,  MAIN_MENU_V_SIZE,  //	XSize, YSize;
		MainMenu,// PrevMenuPage;
		MiscMenuItems, // MenuItems;
		sizeof(MiscMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		NULL,   // ExecFunction;
		NULL,   // Fonts
		mpbStay//   Flags;
	},


	// ExitMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		MainMenu,// PrevMenuPage;
		ExitMenuItems, // MenuItems;
		sizeof( ExitMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay //   Flags;
	},

////=================================================================/////
	//9 BrightnessMenu
	{
		MAIN_MENU_H_SIZE,  MAIN_MENU_V_SIZE,  //	XSize, YSize;
		OSD_BriContrastMenu,// PrevMenuPage;
		BrightnessMenuItems, // MenuItems;
		sizeof( BrightnessMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay  //   Flags;
	},
	//10  ContrastMenu
	{
		MAIN_MENU_H_SIZE,  MAIN_MENU_V_SIZE,  //	XSize, YSize;
		OSD_BriContrastMenu,// PrevMenuPage;
		ContrastMenuItems, // MenuItems;
		sizeof( ContrastMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay //   Flags;
	},

	//11 ECOMenu
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		OSD_BriContrastMenu,// PrevMenuPage;
		ECOMODEMenuItems, // MenuItems;
		sizeof( ECOMODEMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbClrGroup //   Flags;
	},
	//13 DCRMenu
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //    XSize, YSize;
		OSD_BriContrastMenu,// PrevMenuPage;
		DCRMenuItems, // MenuItems;
		sizeof( DCRMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbClrGroup //   Flags;
	},
	#if ENABLE_RTE
	#if PresetMode_Enable
	//13 OverdriveMenu
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //    XSize, YSize;
		OSD_MiscMenu,// PrevMenuPage;
		OverdriveMenuItems, // MenuItems;
		sizeof( OverdriveMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbClrGroup //   Flags;
	},
	#else
	//13 OverdriveMenu
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //    XSize, YSize;
		OSD_BriContrastMenu,// PrevMenuPage;
		OverdriveMenuItems, // MenuItems;
		sizeof( OverdriveMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbClrGroup //   Flags;
	},
	#endif
	#endif

	#if Enable_Gamma
	//12 GammaMenu
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		OSD_BriContrastMenu,// PrevMenuPage;
		GammaMenuItems, // MenuItems;
		sizeof( GammaMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbClrGroup //   Flags;
	},
	#endif
////=================================================================/////
	// HPositionMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		PictureMenu,// PrevMenuPage;
		HPositionMenuItems, // MenuItems;
		sizeof( HPositionMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay  //   Flags;
	},
	// VPositionMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		PictureMenu,// PrevMenuPage;
		VPositionMenuItems, // MenuItems;
		sizeof( VPositionMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay  //   Flags;
	},
	// FocusMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		PictureMenu,// PrevMenuPage;
		FocusMenuItems, // MenuItems;
		sizeof( FocusMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay  //   Flags;
	},
	// ClockMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		PictureMenu,// PrevMenuPage;
		ClockMenuItems, // MenuItems;
		sizeof( ClockMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay  //   Flags;
	},
	#if Enable_Func_AdjExpansion
	// ExpansionMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		PictureMenu, // MainMenu,// PrevMenuPage;
		ExpansionMenuItems, // MenuItems;
		sizeof( ExpansionMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbClrGroup //   Flags;
	},
	#endif
////=================================================================/////
	//21 ColorTempMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		RGBColorMenu,// PrevMenuPage;
		ColorTempSelectMenuItems, // MenuItems;
		sizeof( ColorTempSelectMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbClrGroup //   Flags;
	},
	//22 RedMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		RGBColorMenu,// PrevMenuPage;
		UserColorRedMenuItems, // MenuItems;
		sizeof( UserColorRedMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay  //   Flags;
	},
	//23 GreenMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		RGBColorMenu,// PrevMenuPage;
		UserColorGreenMenuItems, // MenuItems;
		sizeof( UserColorGreenMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay  //   Flags;
	},
	//24 BlueMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		RGBColorMenu,// PrevMenuPage;
		UserColorBlueMenuItems, // MenuItems;
		sizeof( UserColorBlueMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay  //   Flags;
	},
	#if ENABLE_OSD_LowBlueLight
	// LowBlueLightMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		#if   ( LowBlueLightType==LowBlueLight_ColorTemp)
		RGBColorMenu,// PrevMenuPage;
		#elif   ( LowBlueLightType==LowBlueLight_SharpFunc)
		RGBColorMenu,// PrevMenuPage;
		#elif ( LowBlueLightType==LowBlueLight_Misc_Guage)
		OSD_MiscMenu,
		#elif ( LowBlueLightType==LowBlueLight_Misc_Group)
		OSD_MiscMenu,
		#endif
		LowBlueLightMenuItems, // MenuItems;
		sizeof( LowBlueLightMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbClrGroup //	 Flags;
	},
	#endif
////=================================================================/////
	#if AdjustLanguageFunction
	//38 LanguageMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		OsdMenu,// PrevMenuPage;
		LanguageMenuItems, // MenuItems;
		sizeof( LanguageMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbClrGroup //   Flags;
	},

	#else
	//38 LanguageMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		OsdMenu,// PrevMenuPage;
		LanguageMenuItems, // MenuItems;
		sizeof( LanguageMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		MenuPage8, // Fonts
		mpbStay  //   Flags;
	},
	#endif

	#if OsdAdjustHVPos_Enable
	//35 OsdHPositionMenu
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		OsdMenu,// PrevMenuPage;
		OsdHPositionMenuItems, // MenuItems;
		sizeof( OsdHPositionMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay  //   Flags;
	},
	//36 OsdVPositionMenu
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		OsdMenu,// PrevMenuPage;
		OsdVPositionMenuItems, // MenuItems;
		sizeof( OsdVPositionMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay //   Flags;
	},
	#endif
	//37 OsdTimeOutMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		OsdMenu,// PrevMenuPage;
		OsdTimeOutMenuItems, // MenuItems;
		sizeof( OsdTimeOutMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay  //   Flags;
	},

	//39 TransparenceMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		OsdMenu,// PrevMenuPage;
		TransparenceMenuItems, // MenuItems;
		sizeof( TransparenceMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay  //   Flags;
	},
////=====================================================================
	#ifdef OffPower
	//43 OffTimerMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		SettingMenu, // MainMenu,// PrevMenuPage;
		OffTimerMenuItems, // MenuItems;
		sizeof( OffTimerMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbClrGroup //   Flags;
	},
	#endif
////=================================================================/////
	#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
	//41 InputSelectMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		OSD_MiscMenu, // MainMenu,// PrevMenuPage;
		InputSelectMenuItems, // MenuItems;
		sizeof( InputSelectMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbClrGroup //   Flags;
	},
	#endif
	#if  AudioFunc
	//45 Mute,
	#if EANBLE_MUTE_ON_OFF
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		OSD_MiscMenu, // MainMenu,// PrevMenuPage;
		MuteMenuItems, // MenuItems;
		sizeof( MuteMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbClrGroup //   Flags;
	},
	#endif
	//45 Volume,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		OSD_MiscMenu, // MainMenu,// PrevMenuPage;
		VolumeMenuItems, // MenuItems;
		sizeof( VolumeMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay //   Flags;
	},
	#endif

	#if Enable_Adjust_SharpnessMenu
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		OSD_MiscMenu, // MainMenu,// PrevMenuPage;
		SharpnessMenuItems, // MenuItems;
		sizeof( SharpnessMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay //   Flags;
	},
	#endif


	#if  DDCCI_ENABLE && DDCCCIMenu_Enable
	//45 DDCCIMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		OSD_MiscMenu, // MainMenu,// PrevMenuPage;
		DDCCIMenuItems, // MenuItems;
		sizeof( DDCCIMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbClrGroup //   Flags;
	},
	#endif

	#if  FreeSyncMenu_Enable
	//45 FreeSyncMenu,
	{
		MAIN_MENU_H_SIZE/*29*/, MAIN_MENU_V_SIZE, //  XSize, YSize;
		OSD_MiscMenu, // MainMenu,// PrevMenuPage;
		FreeSyncMenuItems, // MenuItems;
		sizeof( FreeSyncMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbClrGroup | mibFreeSyncDisable //   Flags;
	},
	#endif

////=================================================================/////


	// 54 HotKeyECOMenu,
	{
		HOT_MENU_H_SIZE, HOT_MENU_V_SIZE, //  XSize, YSize;
		RootMenu,// PrevMenuPage;
		HotKeyECOMenuItems, // MenuItems;
		sizeof( HotKeyECOMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		#if Hotkey_ECO_Text_Enable
		MenuPage1, // Fonts
		#else
		NULL,
		#endif
		mpbStay | mpbCenter | mpbRedraw //   Flags;	//110408 Modify
	},

	#if Hotkey_DCR_Enable
	// 54 HotKeyDCRMenu,		//110221 Modify
	{
		HOT_MENU_H_SIZE, HOT_MENU_V_SIZE, //  XSize, YSize;
		RootMenu,// PrevMenuPage;
		HotKeyDCRMenuItems, // MenuItems;
		sizeof( HotKeyDCRMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbCenter | mpbRedraw //   Flags;	//110408 Modify
	},
	#endif
	#if HotExpansionAdjust
// HotExpansionMenu
	{
		HOT_MENU_H_SIZE, HOT_MENU_V_SIZE, //  XSize, YSize;
		RootMenu,// PrevMenuPage;
		HotKeyExpansionMenuItems, // MenuItems;
		sizeof( HotKeyExpansionMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbRedraw | mpbCenter | mpbStay//   Flags;
	},
	#endif

	#if AudioFunc && ENABLE_OSD_HotKeyVolume
	// 54 HotKeyVolMenu,
	{
		HOT_MENU_H_SIZE, HOT_MENU_V_SIZE, //  XSize, YSize;
		RootMenu,// PrevMenuPage;
		HotKeyVolumeMenuItems, // MenuItems;
		sizeof( HotKeyVolumeMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		MenuPage6, // Fonts
		mpbStay | mpbCenter | mpbRedraw //   Flags;	//110408 Modify
	},

	#endif
	#if Hotkey_Bri_Enable
// 54 HotConMenu,
	{
		HOT_MENU_H_SIZE, HOT_MENU_V_SIZE, //  XSize, YSize;
		RootMenu,// PrevMenuPage;
		HotKeyBriMenuItems, // MenuItems;
		sizeof(HotKeyBriMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		NULL, // ExecFunction;
		MenuPage1,//MenuPage58, // // Fonts
		mpbStay | mpbCenter | mpbRedraw //   Flags;
	},
	#endif
	#if Hotkey_Con_Enable
// 54 HotConMenu,
	{
		HOT_MENU_H_SIZE, HOT_MENU_V_SIZE, //  XSize, YSize;
		RootMenu,// PrevMenuPage;
		HotKeyConMenuItems, // MenuItems;
		sizeof(HotKeyConMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		NULL, // ExecFunction;
		MenuPage1,//MenuPage58, // // Fonts
		mpbStay | mpbCenter | mpbRedraw //   Flags;
	},
	#endif
	#if HotInputSelect
	// HotInputSelectMenu,
	{
		11, (4 + HotInput_MAX_ITEM), //(4+Input_Nums),		//130129_1  Henry follow Spec
		RootMenu,// PrevMenuPage;
		HotInputSelectMenuItems, // MenuItems;
		sizeof( HotInputSelectMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		EnterHotInputMenu, // ExecFunction;
		#if 0
		#else
		MenuPage6, // Fonts
		#endif
		mpbRedraw | mpbCenter | mpbStay//   Flags;
	},
	#endif


	#if Hot_Corss_ColorSelect
	// HotCorssMenu,
	{
		HotCorssXsize, HotCorssYsize, //  XSize, YSize;
		RootMenu,// PrevMenuPage;
		HotCorssMenuItems, // MenuItems;
		sizeof(HotCorssMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		NULL, // ExecFunction;
		NULL,//MenuPage58, // // Fonts
		mpbStay | mpbCenter | mpbRedraw //   Flags;
	},
	#elif   Hot_Corss_FY_ColorSelect
	// HotCorssFYMenu,
	{
		HotCorssXsize, HotCorssYsize, //  XSize, YSize;
		RootMenu,// PrevMenuPage;
		HotCorssMenuItems, // MenuItems;
		sizeof(HotCorssMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		NULL, // ExecFunction;
		NULL,//MenuPage58, // // Fonts
		mpbStay | mpbCenter | mpbRedraw //   Flags;
	},
	#elif   Hot_Corss_FND_Select
	// HotCorssFYMenu,
	{
		HotCorssXsize, HotCorssYsize, //  XSize, YSize;
		RootMenu,// PrevMenuPage;
		HotCorssMenuItems, // MenuItems;
		sizeof(HotCorssMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		NULL, // ExecFunction;
		NULL,//MenuPage58, // // Fonts
		mpbStay | mpbCenter | mpbRedraw //   Flags;
	},
	#endif


//55 AutoMenu,
	{
		HOT_MENU_H_SIZE, HOT_MENU_V_SIZE, //  XSize, YSize;
		RootMenu,// PrevMenuPage;
		AutoMenuItems, // MenuItems;
		sizeof( AutoMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		AutoConfig, // ExecFunction;
		MenuPage5, // Fonts
		mpbCenter | mpbRedraw//   Flags; //110301 Modify for AutoMenu Garbage
	},


	#if AboutDSUBFunc_Enable
// 57 AutoColorMenu
	{
		31/*29*/, 13, // 	XSize, YSize;
		RootMenu,// PrevMenuPage;
		AutoColorMenuItems, // MenuItems;
		sizeof(AutoColorMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		AutoColor, // ExecFunction;
		NULL, // Fonts
		mpbRedraw//|mpbCenter//   Flags;
	},
	#endif
	#if EN_ShowInfoUnderBurinInMenu
//
// 58 BurninMenu
	{
		28, 6, // 	XSize, YSize;
		RootMenu,// PrevMenuPage;
		BurninMenuItems, // MenuItems;
		sizeof(BurninMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		EnableBurninMode, // ExecFunction;
		NULL, // Fonts
		mpbMoving | mpbStay | mpbCenter | mpbRedraw // Flags;
	},
	#else
// 58 BurninMenu
	{
		29, 13, // 	XSize, YSize;
		RootMenu,// PrevMenuPage;
		BurninMenuItems, // MenuItems;
		sizeof(BurninMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		EnableBurninMode, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbInvisible //   Flags;
	},
	#endif
	// 59 FactoryMenu
	{
		27, 30, //17,  	XSize, YSize;  wmz 20050106
		RootMenu,// PrevMenuPage;
		FactoryMenuItems, // MenuItems;
		sizeof(FactoryMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbRedraw //   Flags;
	},
	// 60 LogoMenu
	{
		LOGO_W, LOGO_H,
		MainMenu,// PrevMenuPage;
		LogoMenuItems, // MenuItems;
		sizeof(LogoMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		EnterDisplayLogo, // ExecFunction;
		NULL, // Fonts
		mpbStay | mpbCenter | mpbRedraw //	Flags;
	},
	// 61 InputInfoMenu
	{
		11, 5, //  XSize, YSize;
		MainMenu,// PrevMenuPage;
		InputInfoMenuItems, // MenuItems;
		sizeof( InputInfoMenuItems ) / sizeof( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		MenuPage6, // Fonts
		mpbStay | mpbRedraw //   Flags;
	},
	#if DDCCI_ENABLE && DDCCCIMenu_Enable
// 61  DdcciInfoMenu
	{
		HOTKEY_X_SIZE, HOTKEY_Y_SIZE,
		RootMenu,// PrevMenuPage;
		DdcciInfoMenuItems, // MenuItems;
		sizeof(DdcciInfoMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		ExecDDC2Bi, // ExecFunction;
		NULL, // Fonts
		mpbStay//|mpbCenter //   Flags;
	},
	#endif

	#ifdef OffPower
	// OffPowerWarningMenu,
	{
		HOT_MENU_H_SIZE, HOT_MENU_V_SIZE, //  XSize, YSize;
		RootMenu,// PrevMenuPage;
		OffPowerWarningMenuItems, // MenuItems;
		sizeof(OffPowerWarningMenuItems) / sizeof(MenuItemType), // MenuItemCount;
		NULL, // ExecFunction;
		MenuPage98, // Fonts
		mpbStay | mpbCenter | mpbRedraw //   Flags;	//110408 Modify
	},
	#endif


};







