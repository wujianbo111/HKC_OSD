#include "panel.h"
#include "FactoryString.h"

#ifndef MenuTblDef_HKCOSD_H
#define MenuTblDef_HKCOSD_H

//======HotKeyMinus=========
#if OSD_NoHotKeyFunc
#define MIA_HotKeyMinus	MIA_Nothing
#elif ENABLE_OSD_HotKeyVolume
#define MIA_HotKeyMinus	MIA_VOL
#elif Hotkey_ECO_Enable
#define MIA_HotKeyMinus MIA_ECO		//120119 Modify
#else
#define MIA_HotKeyMinus	MIA_Nothing
#endif

//======HotKeyPlus=========
#if OSD_NoHotKeyFunc
#define MIA_HotKeyPlus	MIA_Nothing
#elif Hotkey_Bri_Enable
#define MIA_HotKeyPlus	MIA_Brite
#elif Hot_Corss_FY_ColorSelect
#define MIA_HotKeyPlus	MIA_HotCorssMenu
#elif Hot_Corss_FND_Select
#define MIA_HotKeyPlus	MIA_HotCorssMenu
#elif Enable_Func_AdjExpansion
#define MIA_HotKeyPlus	MIA_Expansion//MIA_HotCorssMenu
#else
#define MIA_HotKeyPlus	MIA_Nothing
#endif

//======HotKeyMenu=========
#define MIA_HotKeyMenu	MIA_GotoNext
//======HotKeyExit=========
/*#if Dual
	#define MIA_HotKeyExit	MIA_SourceSel//
#else
	#define MIA_HotKeyExit		MIA_Auto
#endif
*/

#ifndef  MIA_HotKeyExit
#define	MIA_HotKeyExit		MIA_SourceSel
#endif


//======DcrHotKey=========

#if HKC_INPUTSELECT_MODE

MenuItemActionType code AdjusterKeyExecAEvent[BTN_EndBTN] =
{
	MIA_DecValue,     // BTN_Plus MIA_IncValue
	MIA_IncValue,     // BTN_Minus MIA_DecValue
	MIA_ExecFunc, 	// BTN_Menu
	MIA_GotoPrev, 	// BTN_Exit
	MIA_Power,        // BTN_Power

};
#endif
//=====================================================================================
// Key function definition
#if HH_PivotKey2_Enable
MenuItemActionType code NaviExecKeyEvent[BTN_EndBTN] =
{
	MIA_PrevItem, 	// BTN_Minus
	MIA_NextItem, 	// BTN_Plus
	MIA_ExecFunc, 	// BTN_Menu
	MIA_GotoPrev,     // BTN_Exit
	MIA_Power, 	// BTN_Power

};
#else
MenuItemActionType code NaviExecKeyEvent[BTN_EndBTN] =
{
	MIA_NextItem, 	// BTN_Plus
	MIA_PrevItem, 	// BTN_Minus
	MIA_ExecFunc, 	// BTN_Menu
	MIA_GotoPrev,     // BTN_Exit
	MIA_Power, 	// BTN_Power

};
#endif



#if HH_PivotKey_Enable
MenuItemActionType code FactoryNaviKeyEvent[BTN_EndBTN] =
{
	MIA_NextItem, 	// BTN_Plus
	MIA_PrevItem, 	// BTN_Minus
	MIA_JumpAdjustItem,	// BTN_Menu
	MIA_Exit,//MIA_Nothing, 	// BTN_Exit // 070117
	MIA_Power, 	// BTN_Power

};
MenuItemActionType code FactoryAdjustKeyEvent[BTN_EndBTN] =
{
	MIA_DecValue, 	// BTN_Minus
	MIA_IncValue, 	// BTN_Plus
	MIA_ExecFunc,//MIA_NextItem, 	// BTN_Menu
	MIA_JumpNaviItem,//MIA_Exit,//MIA_Nothing, 	// BTN_Exit // 070117
	MIA_Power, 	// BTN_Power

};
#elif HH_PivotKey2_Enable
MenuItemActionType code FactoryNaviKeyEvent[BTN_EndBTN] =
{
	MIA_PrevItem, 	// BTN_Plus
	MIA_NextItem, 	// BTN_Minus
	MIA_JumpAdjustItem,	// BTN_Menu
	MIA_Exit,//MIA_Nothing, 	// BTN_Exit // 070117
	MIA_Power, 	// BTN_Power

};
MenuItemActionType code FactoryAdjustKeyEvent[BTN_EndBTN] =
{
	MIA_IncValue, 	// BTN_Plus
	MIA_DecValue, 	// BTN_Minus
	MIA_ExecFunc,//MIA_NextItem, 	// BTN_Menu
	MIA_JumpNaviItem,//MIA_Exit,//MIA_Nothing, 	// BTN_Exit // 070117
	MIA_Power, 	// BTN_Power

};
#else
MenuItemActionType code FactoryNaviKeyEvent[BTN_EndBTN] =
{
	MIA_NextItem, 	// BTN_Plus
	MIA_PrevItem, 	// BTN_Minus
	MIA_JumpAdjustItem,	// BTN_Menu
	MIA_Exit,//MIA_Nothing, 	// BTN_Exit // 070117
	MIA_Power, 	// BTN_Power

};
MenuItemActionType code FactoryAdjustKeyEvent[BTN_EndBTN] =
{
	MIA_IncValue, 	// BTN_Plus
	MIA_DecValue, 	// BTN_Minus
	MIA_ExecFunc,//MIA_NextItem, 	// BTN_Menu
	MIA_JumpNaviItem,//MIA_Exit,//MIA_Nothing, 	// BTN_Exit // 070117
	MIA_Power, 	// BTN_Power

};
#endif
MenuItemActionType code ExitKeyEvent[BTN_EndBTN] =
{
	MIA_NextItem,     // BTN_Plus
	MIA_PrevItem,     // BTN_Minus
	MIA_Exit,   // BTN_Menu
	MIA_Exit,   // BTN_Exit
	MIA_Power,  // BTN_Power

};


#if (INPUT_TYPE==INPUT_1A) ||(INPUT_TYPE==INPUT_1H)
MenuItemActionType code NaviKeyEvent_Misc[BTN_EndBTN] =
{
	MIA_NextItem, 	// BTN_Plus
	MIA_PrevItem, 	// BTN_Minus
	MIA_Nothing,//MIA_GotoNext, 	// BTN_Menu
	MIA_GotoPrev, 	// BTN_Exit
	MIA_Power, 	    // BTN_Power


};
#endif
#if HH_PivotKey2_Enable
MenuItemActionType code NaviKeyEvent[BTN_EndBTN] =
{
	MIA_PrevItem, 	// BTN_Plus
	MIA_NextItem, 	//   BTN_Minus
	MIA_GotoNext, 	// BTN_Menu
	MIA_GotoPrev, 	// BTN_Exit
	MIA_Power, 	    // BTN_Power

};
#else
MenuItemActionType code NaviKeyEvent[BTN_EndBTN] =
{
	MIA_NextItem, 	// BTN_Plus
	MIA_PrevItem, 	// BTN_Minus
	MIA_GotoNext, 	// BTN_Menu
	MIA_GotoPrev, 	// BTN_Exit
	MIA_Power, 	    // BTN_Power

};
#endif

MenuItemActionType code AdjusterKeyEvent[BTN_EndBTN] =
{
	#if HH_PivotKey_Enable
	MIA_DecValue,     // BTN_Plus
	MIA_IncValue,     // BTN_Minus
	#elif  HH_PivotKey2_Enable
	MIA_IncValue,     // BTN_Minus
	MIA_DecValue,     // BTN_Plus
	#else
	MIA_IncValue,     // BTN_Minus
	MIA_DecValue,     // BTN_Plus
	#endif
	MIA_GotoNext, 	// BTN_Menu
	MIA_GotoPrev, 	// BTN_Exit
	MIA_Power,        // BTN_Power

};


MenuItemActionType code AdjusterKey1Event[BTN_EndBTN] =
{
	MIA_DecValue,     // BTN_Plus
	MIA_IncValue,     // BTN_Minus
	MIA_GotoNext, 	// BTN_Menu
	MIA_GotoPrev, 	// BTN_Exit
	MIA_Power,    // BTN_Power

};
#if HH_PivotKey2_Enable
MenuItemActionType code AdjustExecKeyEvent[BTN_EndBTN] =
{
	MIA_PrevItem, 	// BTN_Minus
	MIA_NextItem, 	// BTN_Plus
	MIA_ExecFunc, 	// BTN_Menu
	MIA_GotoPrev, 	// BTN_Exit
	MIA_Power, 	// BTN_Power

};
#else
MenuItemActionType code AdjustExecKeyEvent[BTN_EndBTN] =
{
	MIA_NextItem, 	// BTN_Plus
	MIA_PrevItem, 	// BTN_Minus
	MIA_ExecFunc, 	// BTN_Menu
	MIA_GotoPrev, 	// BTN_Exit
	MIA_Power, 	// BTN_Power

};
#endif
MenuItemActionType code AdjustNoExecKeyEvent[BTN_EndBTN] =
{
	MIA_IncValue, 	// BTN_Plus
	MIA_DecValue, 	// BTN_Minus
	MIA_GotoPrev, 	// BTN_Menu
	MIA_GotoPrev, 	//MIA_Exit, 	// BTN_Exit
	MIA_Power, 	// BTN_Power

};
#if HotInputSelect

MenuItemActionType code HotInputSelectKeyEvent[BTN_EndBTN] =	//110301 Modify
{
	MIA_Nothing,// petit 20130929 for all scaler unify
	MIA_Nothing, //  BTN_Minus // 121018 coding modified  // petit 20130929 for all scaler unify
	MIA_ExecFunc,     // BTN_Menu
	MIA_NextItem,     // BTN_Exit
	MIA_Power,    // BTN_Power


};

#endif

#if Hot_Corss_ColorSelect ||Hot_Corss_FY_ColorSelect||Hot_Corss_FND_Select
MenuItemActionType code HotCorssSelectKeyEvent[BTN_EndBTN] =
{
	MIA_NextItem, 	      // BTN_Minus
	MIA_Nothing, 	      // BTN_Plus
	MIA_Nothing, //MIA_GotoPrev,		      // BTN_Menu
	MIA_Exit,	 	      // BTN_Exit
	MIA_Power,		        // BTN_Power
};
MenuItemActionType code HotCorssSelectExitKeyEvent[BTN_EndBTN] =
{
	MIA_Exit, 	      // BTN_Minus
	MIA_Nothing, 	      // BTN_Plus
	MIA_Nothing, //MIA_GotoPrev,		      // BTN_Menu
	MIA_Exit,	 	      // BTN_Exit
	MIA_Power,		        // BTN_Power
};
#endif



#if AudioFunc && ENABLE_OSD_HotKeyVolume// petit 20130929 for all scaler unify
MenuItemActionType code HotAudioKeyEvent[BTN_EndBTN] =
{
	MIA_IncValue,     // BTN_Plus
	MIA_DecValue,     // BTN_Minus
	MIA_GotoNext, 	// BTN_Menu
	MIA_Exit, 	       // BTN_Exit
	MIA_Power,        // BTN_Power

};
#endif
MenuItemActionType code OffTimerWarningKeyEvent[BTN_EndBTN] =	//110408 Modify
{

	MIA_Expansion,
	#if Hotkey_ECO_Enable
	MIA_ECO,    // BTN_Minus
	#else
	MIA_Nothing,
	#endif
	MIA_GotoNext, // BTN_Menu
	MIA_Auto,   // BTN_Exit
	MIA_Power,  // BTN_Power

};

MenuItemActionType code UnsopportModeKeyEvent[BTN_EndBTN] =
{
	MIA_Nothing, // BTN_Plus KeyEvent[BTN_EndBTN];
	MIA_Nothing, // BTN_Minus
	MIA_Nothing, // BTN_Menu
	MIA_SourceSel, // BTN_Exit
	MIA_Power, // BTN_Power
};

MenuItemActionType code HotKeyEvent[BTN_EndBTN] =
{
	MIA_IncValue,     // BTN_Plus
	MIA_DecValue,     // BTN_Minus
	MIA_GotoNext, 	// BTN_Menu
	MIA_Exit, 	       // BTN_Exit
	MIA_Power,        // BTN_Power

};
/*
// 071221 modified for key event define of hot dcr
MenuItemActionType code DCRHotKeyEvent[BTN_EndBTN]=
{
	(MIA_HotKeyPlus-DcrHotKey) ? MIA_HotKeyPlus : MIA_IncValue , //BTN_Plus
	(MIA_HotKeyMinus-DcrHotKey) ? MIA_HotKeyMinus : MIA_IncValue, 	//BTN_Minus
	MIA_Exit,	  // BTN_Menu
	MIA_HotKeyExit,//edit by lizzie.ding,100524   MIA_Exit, //BTN_Exit
	MIA_Power,	//MIA_Nothing,	  // BTN_Power
	MIA_Exit,

};
*/
#if HotExpansionAdjust
#if ENABLE_OVER_SCAN && AudioFunc	//121211 Modify
MenuItemActionType code ExpansionHotKeyEvent[BTN_EndBTN] =
{
	MIA_IncValue,  //BTN_Plus
	(MIA_HotKeyMinus - MIA_Expansion) ? MIA_HotKeyMinus : MIA_IncValue, 	//BTN_Minus
	MIA_Exit,	  // BTN_Menu
	MIA_HotKeyExit,//edit by lizzie.ding,100524   MIA_Exit, //BTN_Exit
	MIA_Power,	//MIA_Nothing,	  // BTN_Power
};
#else
MenuItemActionType code ExpansionHotKeyEvent[BTN_EndBTN] =
{
	// petit 20130929 for all scaler unify
	MIA_IncValue,  //BTN_Plus
	MIA_DecValue, 	//BTN_Minus
	MIA_Exit,	  // BTN_Menu
	MIA_Exit,     //BTN_Exit
	MIA_Power,	//MIA_Nothing,	  // BTN_Power
};
#endif
#endif
// 071221 modified for key define of hot eco
MenuItemActionType code ECOHotKeyEvent[BTN_EndBTN] =
{
	#if HH_PivotKey_Enable
	MIA_DecValue,     // BTN_Plus
	MIA_IncValue,     // BTN_Minus
	#elif  HH_PivotKey2_Enable
	MIA_IncValue,     // BTN_Minus
	MIA_DecValue,     // BTN_Plus
	#else
	MIA_IncValue,     // BTN_Minus
	MIA_DecValue,     // BTN_Plus
	#endif

	MIA_Exit, // BTN_Menu
	MIA_Exit,// 121018 coding modified // MIA_HotKeyExit, // BTN_Exit
	MIA_Power, // BTN_Power

};
//===========================================================

//===========================================================
MenuItemActionType code RootKeyEvent[BTN_EndBTN] =
{
	MIA_HotKeyPlus, 	//BTN_Plus
	MIA_HotKeyMinus,	//BTN_Minus
	MIA_HotKeyMenu, 	//BTN_Menu
	MIA_HotKeyExit,		//BTN_Exit
	MIA_Power,		// BTN_Power

};

//============================================================

MenuItemActionType code LockKeyEvent[BTN_EndBTN] =
{
	MIA_GotoNext, 		// BTN_Plus
	MIA_GotoNext, 		// BTN_Minus
	MIA_Exit, 	// BTN_Menu
	MIA_Exit,
	MIA_Power, 	 // BTN_Power

};

//============================================================
MenuItemActionType code LogoKeyEvent[BTN_EndBTN] =
{
	MIA_Nothing, // BTN_Plus KeyEvent[BTN_EndBTN];
	MIA_Nothing, // BTN_Minus
	MIA_Nothing, // BTN_Menu
	MIA_Nothing, // BTN_Exit
	MIA_Power, // BTN_Power

};


//============================================================


MenuItemActionType code SourceSeKeyEvent[BTN_EndBTN] =
{
	MIA_Nothing, // BTN_Plus KeyEvent[BTN_EndBTN];
	MIA_Nothing, // BTN_Minus
	MIA_Nothing, // BTN_Menu
	MIA_SourceSel, // BTN_Exit
	MIA_Power, // BTN_Power


};

MenuItemActionType code NothingKeyEvent[BTN_EndBTN] =
{
	MIA_Nothing, // BTN_Plus KeyEvent[BTN_EndBTN];
	MIA_Nothing, // BTN_Minus
	MIA_Nothing, // BTN_Menu
	MIA_Nothing, // BTN_Exit
	MIA_Power, // BTN_Power

};

MenuItemActionType code NothingKeyEvent1[BTN_EndBTN] =
{
	MIA_Nothing, // BTN_Plus KeyEvent[BTN_EndBTN];
	MIA_Nothing, // BTN_Minus
	MIA_Nothing, // BTN_Menu
	MIA_Nothing, // BTN_Exit  petit 20130828
	MIA_Power, // BTN_Power

};

// 071221 modified for power saving key event
MenuItemActionType code PwrSavingKeyEvent[BTN_EndBTN] =
{
	MIA_Nothing,  // BTN_Plus
	MIA_Nothing, // BTN_Minus
	MIA_Nothing,
	MIA_Nothing,//MIA_SourceSel,
	MIA_Power, // BTN_Power
};
#ifdef OffPower
MenuItemActionType code OffPowerWarningKeyEvent[BTN_EndBTN] =
{
	MIA_GotoPrev,     // BTN_Plus
	MIA_GotoPrev,     // BTN_Minus
	MIA_GotoPrev, 	// BTN_Menu
	MIA_GotoPrev, 	// BTN_Exit
	MIA_Power, 		// BTN_Power
};
#endif


//============================================================
//============================================================
MenuItemType code PowerOffMenuItems[] =
{
	{
		0, 1, // XPos, YPos;
		0, 1, // ForeColor, BackColor;
		0, 1, // SelForeColor, SelBackColor;
		PowerOnMenu, //NextMenuPage;
		DWI_CenterText,// DrawMenuItemType;
		NULL, // DisplayText;
		NothingKeyEvent,//PowerOffKeyEvent, //KeyEvent
		{
			NULL, // AdjustFunction
			NULL			// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	}
};

MenuItemType code StandbyMenuItems[] =
{
	{
		0, 3, // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_UnselectItem, Color_2, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_CenterPropText,// DrawMenuItemType;
		NoSyncText, // DisplayText;
		NothingKeyEvent1,//PowerOffKeyEvent, //KeyEvent
		{
			NULL, // AdjustFunction
			NULL, // ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL  // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	#if 0
	{
		0, 2, // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_UnselectItem, Color_2, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_CenterPropText,// DrawMenuItemType;
		NoSyncStatusText, // DisplayText;
		NothingKeyEvent1,//PowerOffKeyEvent, //KeyEvent
		{
			NULL, // AdjustFunction
			NULL, // ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL  // DrawRadioGroupType
		},
		NULL, //Font
		NULL // Flags
	}
	#endif
};

MenuItemType code SleepMenuItems[] =
{
	{
		1, 2, // XPos, YPos;
		CP_BlueColor, CP_LightBlue, // ForeColor, BackColor;
		CP_BlueColor, CP_LightBlue, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_CenterText,// DrawMenuItemType;
		NULL,//GoingToSleepText, // DisplayText;
		NULL,//NothingKeyEvent,//PowerOffKeyEvent, //KeyEvent
		{
			NULL, // AdjustFunction
			NULL,//WakeUpSystem // ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	}
};

MenuItemType code CableNotConnectedMenuItems[] =
{
	{
		0, 4, // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_UnselectItem, Color_2, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_CenterPropText,// DrawMenuItemType;
		CableNotConnectText, // DisplayText;
		NothingKeyEvent,//PowerOffKeyEvent, //KeyEvent
		{
			NULL, // AdjustFunction
			NULL, // ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL  // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	}
};

MenuItemType code UnsupportedModeMenuItems[] =
{
	// Input Not
	{
		0, 3, // XPos, YPos;
		CP_UnselectItem, Color_2, // ForeColor, BackColor;
		CP_UnselectItem, Color_2, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_CenterPropText,// DrawMenuItemType;
		OutOfRangeText, // DisplayText;
		NothingKeyEvent1,  //KeyEvent
		{
			NULL, // AdjustFunction
			NULL, // ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL  // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
};

MenuItemType code RootMenuItems[] =
{
	// virtual item
	{
		0, 1, // XPos, YPos;
		0, 1, // ForeColor, BackColor;
		0, 1, // SelForeColor, SelBackColor;
		MainMenu, //NextMenuPage;
		NULL, //DWI_CenterText,// DrawMenuItemType;
		NULL, // DisplayText;
		RootKeyEvent,
		{
			NULL, // AdjustFunction
			NULL,//AutoConfig// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	}
};

typedef enum
{

	#if AboutDSUBFunc_Enable
	Item_AutoColor,

	Item_GainR, Item_GainG, Item_GainB,
	Item_adjGainR, Item_adjGainG, Item_adjGainB,

	Item_OffsR, Item_OffsG, Item_OffsB,
	Item_adjOffsR, Item_adjOffsG, Item_adjOffsB,
	#endif

	Item_9300R, Item_adj9300R, Item_9300G, Item_adj9300G, Item_9300B, Item_adj9300B,

	Item_6500R, Item_adj6500R, Item_6500G, Item_adj6500G, Item_6500B, Item_adj6500B,

	#if CT_7500K_ENABLE
	Item_7500R, Item_adj7500R, Item_7500G, Item_adj7500G, Item_7500B, Item_adj7500B,
	#endif

	#if ENABLE_FACTORY_SSCADJ
	Item_Freq, Item_adjFreq,
	Item_Amp, Item_adjAmp,
	#endif

	Item_BurinIn, Item_adjBurinIn,

	Item_Rever,
} FMenuItemsType;


//==============================================================================================
#if AboutDSUBFunc_Enable
//------------------------------------------------------------------------------------------------------------
NumberType code DrawGainR[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd,	9,	3,	GetRedGainValue}
};
DrawNumberType code DrawGainRNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{	CP_RedColor,	CP_BlueColor, DrawGainR}
};
//------------------------------------------------------------------------------------------------------------
NumberType code DrawGainG[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd,	15, 3,	GetGreenGainValue}
};
DrawNumberType code DrawGainGNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{CP_RedColor,	CP_BlueColor,	DrawGainG}
};
//------------------------------------------------------------------------------------------------------------
NumberType code DrawGainB[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd,	21, 3,	GetBlueGainValue}
};
DrawNumberType code DrawGainBNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{CP_RedColor,	CP_BlueColor,	DrawGainB}
};
//------------------------------------------------------------------------------------------------------------
NumberType code DrawOffsetR[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd, 9,	4,	GetAdcRedOffsetValue}
};
DrawNumberType code DrawOffsetRNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{CP_RedColor,	CP_BlueColor,	DrawOffsetR}
};
//------------------------------------------------------------------------------------------------------------
NumberType code DrawOffsetG[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd,	15, 4,	GetAdcGreenOffsetValue}
};
DrawNumberType code DrawOffsetGNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{	CP_RedColor,	CP_BlueColor,	DrawOffsetG}
};
//------------------------------------------------------------------------------------------------------------
NumberType code DrawOffsetB[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd,	21, 4,	GetAdcBlueOffsetValue}
};
DrawNumberType code DrawOffsetBNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{CP_RedColor,	CP_BlueColor,	DrawOffsetB}
};
#endif
//------------------------------------------------------------------------------------------------------------
//================================================================================================
//------------------------------------------------------------------------------------------------------------
NumberType code DrawRedColorCool1[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd,	9,	6,	GetRColorCool1Value}
};
DrawNumberType code DrawRedColorCool1Number[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{CP_RedColor,	CP_BlueColor,	DrawRedColorCool1}
};
//------------------------------------------------------------------------------------------------------------
NumberType code DrawGreenColorCool1[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd,	15, 6,	GetGColorCool1Value}
};
DrawNumberType code DrawGreenColorCool1Number[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{	CP_RedColor,	CP_BlueColor,	DrawGreenColorCool1}
};
//------------------------------------------------------------------------------------------------------------
NumberType code DrawBlueColorCool1[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd, 21, 6,	GetBColorCool1Value}
};
DrawNumberType code DrawBlueColorCool1Number[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{	CP_RedColor,	CP_BlueColor,	DrawBlueColorCool1}
};
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
//================================================================================================
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
//================================================================================================
//------------------------------------------------------------------------------------------------------------
NumberType code DrawRedColorWarm1[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd,	9,	8,	GetRColorWarm1Value}
};
DrawNumberType code DrawRedColorWarm1Number[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{CP_RedColor,	CP_BlueColor,	DrawRedColorWarm1}
};
//------------------------------------------------------------------------------------------------------------
NumberType code DrawGreenColorWarm1[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd,	15, 8,	GetGColorWarm1Value}
};
DrawNumberType code DrawGreenColorWarm1Number[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{	CP_RedColor,	CP_BlueColor,	DrawGreenColorWarm1}
};
//------------------------------------------------------------------------------------------------------------
NumberType code DrawBlueColorWarm1[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd, 21, 8,	GetBColorWarm1Value}
};
DrawNumberType code DrawBlueColorWarm1Number[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{	CP_RedColor,	CP_BlueColor,	DrawBlueColorWarm1}
};
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
//================================================================================================
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//================================================================================================
//------------------------------------------------------------------------------------------------------------
#if CT_7500K_ENABLE
NumberType code DrawRedColorNormal[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd,	9,	10,	GetRColorNormalValue}
};
DrawNumberType code DrawRedColorNormalNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{CP_RedColor,	CP_BlueColor,	DrawRedColorNormal}
};
//------------------------------------------------------------------------------------------------------------
NumberType code DrawGreenColorNormal[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd,	15, 10,	GetGColorNormalValue}
};
DrawNumberType code DrawGreenColorNormalNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{	CP_RedColor,	CP_BlueColor,	DrawGreenColorNormal}
};
//------------------------------------------------------------------------------------------------------------
NumberType code DrawBlueColorNormal[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd, 21, 10,	GetBColorNormalValue}
};
DrawNumberType code DrawBlueColorNormalNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{	CP_RedColor,	CP_BlueColor,	DrawBlueColorNormal}
};
#endif
//------------------------------------------------------------------------------------------------------------

//================================================================================================
//====================================================================================
#if CT_sRGB_ENABLE
//------------------------------------------------------------------------------------------------------------
NumberType code DrawRedColorSRGB[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd,	9,	12, GetRColorSRGBValue}
};
DrawNumberType code DrawRedColorSRGBNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{	CP_RedColor,	CP_BlueColor, DrawRedColorSRGB}
};
//------------------------------------------------------------------------------------------------------------
NumberType code DrawGreenColorSRGB[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd,		15, 12, GetGColorSRGBValue}
};
DrawNumberType code DrawGreenColorSRGBNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{	CP_RedColor,	CP_BlueColor,  DrawGreenColorSRGB}
};
//------------------------------------------------------------------------------------------------------------
NumberType code DrawBlueColorSRGB[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd,	21, 12, GetBColorSRGBValue}
};
DrawNumberType code DrawBlueColorSRGBNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{	CP_RedColor,	CP_BlueColor,	DrawBlueColorSRGB}
};
#endif
//------------------------------------------------------------------------------------------------------------
#if ENABLE_FACTORY_SSCADJ	//120305 Modify
NumberType code FactorySSCModulationNumber[] =
{
	// Flags, ForeColor,    BackColor,  XPos,   YPos,   GetValue
	{dwiEnd, 4, 18, GetFactorySSCModulationValue}
};
DrawNumberType code DrawFactorySSCModulationNumber[] =
{
	// Flags, ForeColor,    BackColor,  XPos,   YPos,   GetValue
	{   CP_RedColor,    CP_BlueColor,       FactorySSCModulationNumber}
};
NumberType code FactorySSCPercentageNumber[] =
{
	// Flags, ForeColor,    BackColor,  XPos,   YPos,   GetValue
	{dwiEnd, 13, 18, GetFactorySSCPercentageValue}
};
DrawNumberType code DrawFactorySSCPercentageNumber[] =
{
	// Flags, ForeColor,    BackColor,  XPos,   YPos,   GetValue
	{   CP_RedColor,    CP_BlueColor,       FactorySSCPercentageNumber}
};
#endif

//====================================================================================
//----------------------------------------------------------
RadioTextType code BurninRatioText[] =
{
	// Flags, 	XPos,	YPos,	DisplayText
// {dwiEnd,	10, 12, OffText},
	{dwiEnd,	10, 20, BurninOnOffText}
};
DrawRadioGroupType code DrawBurninRadioGroup[] =
{
	//ForeColor,	BackColor,		GetValue	RadioText
	{CP_RedColor, CP_BlueColor,	GetBurninValue, BurninRatioText}
};
#if 0//DisplayPowerOnLogo
RadioTextType code LogoRatioText[] =
{
	// Flags, 	XPos,	YPos,	DisplayText
// {dwiEnd,	10, 12, OffText},
	{dwiEnd,	10, 29, LogoOnOffText}
};
DrawRadioGroupType code DrawLogoRadioGroup[] =
{
	//ForeColor,	BackColor,		GetValue	RadioText
	{CP_RedColor, CP_BlueColor,	GetLogoValue, LogoRatioText}
};
#endif



#if Enable_ProductModeAdjust
RadioTextType code ProductModeRatioText[] =
{
	// Flags, 	XPos,	YPos,	DisplayText
	{dwiEnd,	10, 20, ProductModeOnOffText}
};
DrawRadioGroupType code DrawProductModeRadioGroup[] =
{
	//ForeColor,	BackColor,		GetValue	RadioText
	{CP_RedColor, CP_BlueColor,	GetProductModeValue, ProductModeRatioText}
};
#endif

#if 0
RadioTextType code PanelTpyeRadioText[] =
{
	// Flags, 	XPos,	YPos,	DisplayText
	{dwiEnd,		15,	23, PanelTpyeText}
};
DrawRadioGroupType code DrawPanelTpyeRadioGroup[] =
{
	//ForeColor,	BackColor,		GetValue	RadioText
	{CP_RedColor, CP_BlueColor,	NULL,	PanelTpyeRadioText}
};


#endif
// 090310
#if PanelminiLVDS || PANEL_VCOM_ADJUST	//110229 Modify
NumberType code DrawVCOMValue[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd,	10, 21, GetVCOMValue}
};
DrawNumberType code DrawVCOMValueNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{CP_RedColor,	CP_BlueColor, DrawVCOMValue}
};
#endif


//====================================================================================
RadioTextType code FactoryText[] =
{
	// Flags, 	XPos,	YPos,	DisplayText
	#ifdef  Brand
	{0,			1,	0,	BrandNameText},
	{0,			1,	1,	ModelNameText},
	#else
	{0,			1,	0,	ModelNameText},
	#endif
	{ 0,		22, 	0,	VersionDateText},

	#if AboutDSUBFunc_Enable
	{ 0,		1,	3,	AdcGainText},
	{ 0,		1,	4,	AdcOffsetText},
	#endif
	{ 0,		1,	6,	COOL1Text},
	{ 0,		1,	8,    WARM1Text},
	#if CT_7500K_ENABLE
	{ 0,		1,	10,  	NORMALText},
	#endif

	#if CT_sRGB_ENABLE
	{ 0,	      1,	12,     sRGBText},
	#endif

	#if ENABLE_FACTORY_SSCADJ	//120305 Modify
	{0,	             1,	17,     SpreadSpectrumText},
	#endif


	#if ENABLE_FACTORY_BLACKLEVEL
	{0,	             1,	22,     FacBlacklevelText},
	#endif


	{0, 				 1, 25, 		 	F_BackLightText},
	{0, 				 17, 25,			 F_HourText},
	{0, 				 22, 25,			 F_MinText},


	#if Enable_Factory_Panel
	{0,	             1,	27,     CheckSumText},
	{0,			1,	28, PanelText},
	#else
	{0,	             1,	27,     CheckSumText},
	#endif
	{0,         1, 26,  ChipNameText},
	#ifdef  BoardName
	{0,         1, 29,  BoardNameText},
	#endif
	{dwiEnd,    15,	26,	ChangeDateText},

};

DrawRadioGroupType code DrawFactoryRadioGroup[] =
{
	//ForeColor,	BackColor,		GetValue	RadioText
	{CP_WhiteColor,	CP_BlueColor,	NULL,	FactoryText}
};


NumberType code FactoryPanelOnTimeNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{0		,		12, 25,	GetPanelOnTimeValue},
	{0   	,		17, 25,	GetPanelOnTimeMValue},
	{dwiEnd | dwiHex,	15, 27,	GetCheckSumValue}
};
DrawNumberType code DrawFactoryPanelOnTimeNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{	CP_RedColor,	CP_BlueColor,		FactoryPanelOnTimeNumber}
};
#if F_ShowVsync_Enable
NumberType code FreesyncNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd, 17, 24,	GetVsyncValue}
};
DrawNumberType code DrawFreesyncNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{	CP_RedColor,	CP_BlueColor,		FreesyncNumber}
};
#endif

#if ENABLE_FACTORY_BLACKLEVEL
NumberType code DrawColorBlacklevel[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{dwiEnd,	9,	22, GetColorBlacklevelValue}
};
DrawNumberType code DrawRedColorBlacklevelNumber[] =
{
	// Flags, ForeColor,	BackColor,	XPos,	YPos,	GetValue
	{	CP_RedColor,	CP_BlueColor, DrawColorBlacklevel}
};
#endif



MenuItemType code FactoryMenuItems[] =
{
	#if AboutDSUBFunc_Enable
// 0.Auto Color
	{
		1, 2, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		AutoColorText, // DisplayText;
		NaviExecKeyEvent,
		{
			NULL, // AdjustFunction
			AutoColor// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},

	// 1. Gain R
	{
		8, 3, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FactoryRedText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 2.Gain R adjust
	{
		10, 3, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustRedGain,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawGainRNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 3.Gain G
	{
		14, 3, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FactoryGreenText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable// Flags
	},
	// 4.Gain G adjust
	{
		16, 3, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustGreenGain,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawGainGNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 5.Gain B
	{
		20, 3, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FactoryBlueText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 6.Gain B adjust
	{
		20, 3, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustBlueGain,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawGainBNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 7.Offset R
	{
		8, 4, // XPos, YPos;
		#ifdef TSUMXXT		//110316 Modify
		CP_GrayColor,  CP_BlueColor,//CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		#else
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		#endif
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FactoryRedText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		#ifdef TSUMXXT		//110316 Modify
		NULL 		  // Flags
		#else
		mibSelectable // Flags
		#endif
	},
	// 8.Offset R adjust
	{
		10, 4, // XPos, YPos;
		#ifdef TSUMXXT		//110316 Modify
		CP_GrayColor,  CP_BlueColor,//CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		#else
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		#endif
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustAdcRedOffset,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawOffsetRNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		#ifdef TSUMXXT		//110316 Modify
		mibDrawValue			   // Flags
		#else
		mibDrawValue | mibSelectable // Flags
		#endif
	},
	// 9.Offset G
	{
		14, 4, // XPos, YPos;
		#ifdef TSUMXXT		//110316 Modify
		CP_GrayColor,  CP_BlueColor,//CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		#else
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		#endif
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FactoryGreenText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL,//AutoColor// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		#ifdef TSUMXXT		//110316 Modify
		NULL		  // Flags
		#else
		mibSelectable // Flags
		#endif
	},
	// 10.Offset G adjust
	{
		16, 4, // XPos, YPos;
		#ifdef TSUMXXT		//110316 Modify
		CP_GrayColor,  CP_BlueColor,//CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		#else
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		#endif
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustAdcGreenOffset, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawOffsetGNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		#ifdef TSUMXXT		//110316 Modify
		mibDrawValue			   // Flags
		#else
		mibDrawValue | mibSelectable // Flags
		#endif
	},
	// 11.Offset B
	{
		20, 4, // XPos, YPos;
		#ifdef TSUMXXT		//110316 Modify
		CP_GrayColor,  CP_BlueColor,//CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		#else
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		#endif
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FactoryBlueText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		#ifdef TSUMXXT		//110316 Modify
		NULL		  // Flags
		#else
		mibSelectable // Flags
		#endif
	},
	// 12.Offset B adjust
	{
		20, 4, // XPos, YPos;
		#ifdef TSUMXXT		//110316 Modify
		CP_GrayColor,  CP_BlueColor,//CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		#else
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		#endif
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustAdcBlueOffset,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawOffsetBNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		#ifdef TSUMXXT		//110316 Modify
		mibDrawValue			   // Flags
		#else
		mibDrawValue | mibSelectable // Flags
		#endif
	},
	#endif


	#if 1

	//===Cool1===============================================
	// 13.Cool1_ R
	{
		8, 6, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FactoryRedText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 14.Cool1_R adjust
	{
		10, 6, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustRedColorCool1,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawRedColorCool1Number,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 15.Cool_G
	{
		14, 6, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FactoryGreenText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 16.Cool_G adjust
	{
		16, 6, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustGreenColorCool1,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawGreenColorCool1Number,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 17.Cool1 B
	{
		20, 6, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FactoryBlueText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},

	// 18.Cool1 B adjust
	{
		20, 6, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustBlueColorCool1, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawBlueColorCool1Number, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
//==========Warm1====================================
	// 33.Warm1_ R
	{
		8, 8, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FactoryRedText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 34.Warm1_R adjust
	{
		10, 8, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustRedColorWarm1,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawRedColorWarm1Number,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 35.Cool_G
	{
		14, 8, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FactoryGreenText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 36.Cool_G adjust
	{
		16, 8, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustGreenColorWarm1,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawGreenColorWarm1Number,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 37.Warm1 B
	{
		20, 8, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FactoryBlueText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},

	// 38.Warm1 B adjust
	{
		20, 8, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustBlueColorWarm1, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawBlueColorWarm1Number, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},

	#if CT_7500K_ENABLE
//==========Normal====================================
	// 53.Normal_ R
	{
		8, 10, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FactoryRedText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 54.Normal_R adjust
	{
		10, 10, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustRedColorNormal,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawRedColorNormalNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 55.Cool_G
	{
		14, 10, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FactoryGreenText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 56.Cool_G adjust
	{
		16, 10, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustGreenColorNormal,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawGreenColorNormalNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 57.Normal B
	{
		20, 10, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FactoryBlueText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},

	// 58.Normal B adjust
	{
		20, 10, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustBlueColorNormal, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawBlueColorNormalNumber, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	#endif


	#if CT_sRGB_ENABLE
//========================================================================================================
	//63. SRGB R
	{
		8, 12, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FactoryRedText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 64.SRGB R adjust
	{
		10, 12, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustRedColorSRGB,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawRedColorSRGBNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 65.SRGB G
	{
		14, 12, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FactoryGreenText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},

	// 66.SRGB G adjust
	{
		16, 12, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustGreenColorSRGB, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawGreenColorSRGBNumber, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 67.SRGB B
	{
		20, 12, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FactoryBlueText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 68.SRGB B adjust
	{
		20, 12, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustBlueColorSRGB, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawBlueColorSRGBNumber, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	#endif

	#if ENABLE_FACTORY_SSCADJ	//120305 Modify
	/*//spread spectrum
	{
	    1, 17, // XPos, YPos;
	    CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
	    CP_WhiteColor, CP_BlueColor,// SelForeColor, SelBackColor;
	    RootMenu, //NextMenuPage;
	    DWI_Text,// DrawMenuItemType;
	    SpreadSpectrumText, // DisplayText;
	    FactoryAdjustKeyEvent,
	    {
	        NULL,// AdjustFunction
	        NULL// ExecFunction
	    },// DisplayValue;
	    {
	        NULL,// DrawNumberType
	        NULL, // DrawGuageType
	        NULL,//DrawSpreadSpectrumRadioGroup//DrawRadioGroupType
	    },
	    NULL, //Font
	    mibDrawValue // Flags
	},*/
	//73 FreqText
	{
		1, 18, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FreqText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL    // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// Freq Adjust
	{
		6, 18, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustFactorySSCModulation, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawFactorySSCModulationNumber, // DrawNumberType
			NULL, // DrawGuageType
			NULL// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	//73 AmpText
	{
		11, 18, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		AmpText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL    // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// Amp Adjust
	{
		15, 18, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustFactorySSCPercentage, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawFactorySSCPercentageNumber, // DrawNumberType
			NULL, // DrawGuageType
			NULL    // DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	#endif

//==============================================================================================
	#if Enable_ProductModeAdjust
	//ProductMode
	{
		1, 20, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		ProductModeText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 74Burnin Adjust
	{
		1, 20, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustProductMode, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawProductModeRadioGroup	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	#endif
// 090310
	#if PanelminiLVDS || PANEL_VCOM_ADJUST	//110229 Modify
	{
		1, 21, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		VCOMText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// VCOM Adjust
	{
		10, 21, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustVCOMValue,// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawVCOMValueNumber, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	#endif

	#if 0//ENABLE_RTE
	{
		1, 21, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		OverDriveText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 74Burnin Adjust
	{
		1, 21, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustOverDrive,// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawOverDriveRadioGroup	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	#endif

	//73 Burnin
	{
		1, 20, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		BurninText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 74Burnin Adjust
	{
		1, 20, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustBurnin, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawBurninRadioGroup	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	#if ENABLE_FACTORY_BLACKLEVEL
	//63. Blacklevel
	{
		1, 22, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FacBlacklevelText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 64.Blacklevel R adjust
	{
		10, 22, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustColorBlacklevel,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawRedColorBlacklevelNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	#endif


	#if 0//DisplayPowerOnLogo
	//130613 Jun
	//73 logo
	{
		1, 29, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		LogoText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL  // DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 74Burnin Adjust
	{
		1, 29, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_LightBlue, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustLogo, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawLogoRadioGroup  // DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},

	#endif

	#if !USEFLASH // 130829 larry
	{
		1, 30, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		EraseEEPROMText,// ExecFunction
		NaviExecKeyEvent,
		{
			NULL, // AdjustFunction
			EraseAllEEPROMCell// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	#endif



	#if F_ShowVsync_Enable
	// FreeSync
	{
		1, 24, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_WhiteColor, CP_BlueColor,// SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		FreeSyncVsyncText, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			NULL,// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawFreesyncNumber,// DrawNumberType
			NULL, // DrawGuageType
			NULL//DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue // Flags
	},
	#endif






	// Descript
	{
		20, 10, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_WhiteColor, CP_BlueColor,// SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			NULL,// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawFactoryPanelOnTimeNumber,// DrawNumberType
			NULL, // DrawGuageType
			DrawFactoryRadioGroup//DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue // Flags
	},
	#endif
};
#if 0
MenuItemType code AjustPanlMenuItems[] =
{
	// 0. PanelDitherText
	{
		1, 0, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PanelDitherText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 1.PanelDither adjust
	{
		18, 0, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustPanelDither,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL,//DrawPanelDitherNumber,	// DrawNumberType
			NULL, // DrawGuageType
			DrawPanelDitherGroup	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 2.PanelOnTiming1Text
	{
		1, 2, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PanelOnTiming1Text, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable// Flags
	},
	// 3.PanelOnTiming1 adjust
	{
		17, 2, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustPanelOnTiming1,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawPanelOnTiming1Number,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 4.PanelOnTiming2Text
	{
		20, 2, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PanelOnTiming2Text, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 5.PanelOnTiming2 adjust
	{
		32, 2, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustPanelOnTiming2,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawPanelOnTiming2Number,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 6.PanelOffTiming1Text
	{
		1, 3, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PanelOffTiming1Text, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 7.PanelOffTiming1  adjust
	{
		13, 3, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustPanelOffTiming1,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawPanelOffTiming1Number,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 8.PanelOffTiming2Text
	{
		20, 3, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PanelOffTiming2Text, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 9.PanelOffTiming2 adjust
	{
		32, 3, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustPanelOffTiming2,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawPanelOffTiming2Number,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 10.PanelHSyncWidthText
	{
		1, 5, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PanelHSyncWidthText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 11.PanelHSyncWidth adjust
	{
		13, 5, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustPanelHSyncWidth,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawPanelHSyncWidthNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 12.PanelHSyncBackPorchText
	{
		20, 5, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PanelHSyncBackPorchText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 13.PanelHSyncBackPorch adjust
	{
		32, 5, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustPanelHSyncBackPorch,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawPanelHSyncBackPorchNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 16.PanelVSyncWidthText
	{
		1, 6, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PanelVSyncWidthText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 15.PanelVSyncWidth adjust
	{
		13, 6, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustPanelVSyncWidth,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawPanelVSyncWidthNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 16.PanelVSyncBackPorchText
	{
		20, 6, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PanelVSyncBackPorchText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 17.PanelVSyncBackPorch adjust
	{
		32, 6, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustPanelVSyncBackPorch,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawPanelVSyncBackPorchNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 18.PanelWidthText
	{
		1, 7, // XPos, YPos;
		CP_GrayColor, CP_BlueColor, //CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PanelWidthText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		NULL,//mibSelectable // Flags
	},
	// 19.PanelWidth adjust
	{
		13, 7, // XPos, YPos;
		CP_GrayColor, CP_BlueColor, //CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			NULL,//AdjustPanelWidth,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawPanelWidthNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue,//mibDrawValue|mibSelectable // Flags
	},
	// 20.PanelHeightText
	{
		20, 7, // XPos, YPos;
		CP_GrayColor, CP_BlueColor, //CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PanelHeightText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		NULL,//mibSelectable // Flags
	},
	// 23.PanelHeight adjust
	{
		32, 7, // XPos, YPos;
		CP_GrayColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			NULL,//AdjustPanelHeight,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawPanelHeightNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue,//mibDrawValue|mibSelectable // Flags
	},
	// 22.PanelHTotalText
	{
		1, 8, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PanelHTotalText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 23.PanelHTotal adjust
	{
		13, 8, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustPanelHTotal,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawPanelHTotalNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 24.PanelVTotalText
	{
		20, 8, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PanelVTotalText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 25.PanelVTotal adjust
	{
		32, 8, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustPanelVTotal,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawPanelVTotalNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 26.PanelMaxHTotalText
	{
		1, 9, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PanelMaxHTotalText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 27.PanelMaxHTotal adjust
	{
		13, 9, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustPanelMaxHTotal,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawPanelMaxHTotalNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 28.PanelMinHTotalText
	{
		20, 9, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PanelMinHTotalText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 29.PanelMinHTotal adjust
	{
		32, 9, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustPanelMinHTotal,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawPanelMinHTotalNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	/* // 30.PanelMaxVTotalText
	 { 1, 10, // XPos, YPos;
	CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
	CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
	RootMenu, //NextMenuPage;
	DWI_Text,// DrawMenuItemType;
	PanelMaxVTotalText, // DisplayText;
	FactoryNaviKeyEvent,
	{ NULL, // AdjustFunction
	  NULL// ExecFunction
	},// DisplayValue;
	{ NULL, // DrawNumberType
	  NULL, // DrawGuageType
	  NULL	// DrawRadioGroupType
	},
	     NULL, //Font
	mibSelectable // Flags
	 },
	 // 31.PanelMaxVTotal adjust
	 { 13, 10, // XPos, YPos;
	CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
	CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
	RootMenu, //NextMenuPage;
	DWI_Text,// DrawMenuItemType;
	NULL, // DisplayText;
	FactoryAdjustKeyEvent,
	{ AdjustPanelMaxVTotal,	// AdjustFunction
	  NULL// ExecFunction
	},// DisplayValue;
	{ DrawPanelMaxVTotalNumber,	// DrawNumberType
	  NULL, // DrawGuageType
	  NULL	// DrawRadioGroupType
	},
	     NULL, //Font
	mibDrawValue|mibSelectable // Flags
	 },
	 // 32.PanelMinVTotalText
	 { 20, 10, // XPos, YPos;
	CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
	CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
	RootMenu, //NextMenuPage;
	DWI_Text,// DrawMenuItemType;
	PanelMinVTotalText, // DisplayText;
	FactoryNaviKeyEvent,
	{ NULL, // AdjustFunction
	  NULL// ExecFunction
	},// DisplayValue;
	{ NULL, // DrawNumberType
	  NULL, // DrawGuageType
	  NULL	// DrawRadioGroupType
	},
	     NULL, //Font
	mibSelectable // Flags
	 },
	 // 33.PanelMinVTotal adjust
	 { 32, 10, // XPos, YPos;
	CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
	CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
	RootMenu, //NextMenuPage;
	DWI_Text,// DrawMenuItemType;
	NULL, // DisplayText;
	FactoryAdjustKeyEvent,
	{ AdjustPanelMinVTotal,	// AdjustFunction
	  NULL// ExecFunction
	},// DisplayValue;
	{ DrawPanelMinVTotalNumber,	// DrawNumberType
	  NULL, // DrawGuageType
	  NULL	// DrawRadioGroupType
	},
	     NULL, //Font
	mibDrawValue|mibSelectable // Flags
	 },*/


	// 34.PanelDCLKText
	{
		1, 10, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PanelDCLKText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 35.PanelDCLK adjust
	{
		13, 10, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustPanelDCLK,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawPanelDCLKNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},

	// 38.PanelMinDCLKText
	{
		20, 10, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PanelMinDCLKText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 39.PanelMinDCLK adjust
	{
		32, 10, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustPanelMinDCLK,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawPanelMinDCLKNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	// 36.PanelMaxDCLKText
	{
		1, 11, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PanelMaxDCLKText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// 37.PanelMaxDCLK adjust
	{
		13, 11, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustPanelMaxDCLK,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawPanelMaxDCLKNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},

	//lvds output swing control
	{
		20, 11, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		SwingText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	//lvds output swing control Adjust
	{
		32, 11, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustSwing, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawSwingNumber, // DrawNumberType
			NULL, // DrawGuageType
			NULL// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	/***********************Bank 0 0x43********************************/

	//Dual Pixel Output
	{
		1, 13, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		DualPixelOutputText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// Dual Pixel Output Adjust
	{
		16, 13, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustDualPixelOutput, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawDualPixelOutputGroup	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	//A/B Port Swap (only used when Dual Pixel Output)
	{
		20, 13, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		ABPortSwapText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// A/B Port Swap Adjust
	{
		35, 13, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustABPortSwap, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawABPortSwapGroup	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},


	/***********************Bank 0 0x42********************************/
	//P/N swap
	{
		1, 14, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		PNSwapText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// P/N swap Adjust
	{
		16, 14, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustPNSwap, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawPNSwapGroup	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	//Channel Swap
	{
		20, 14, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		ChannelSwapText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// P/N swap Adjust
	{
		35, 14, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustChannelSwap, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawChannelSwapGroup	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	//MSB/LSB Exchange
	{
		1, 15, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		MSBLSBExchangeText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// MSB/LSB Exchange Adjust
	{
		16, 15, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustMSBLSBExchange, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawMSBLSBExchangeGroup	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	//TI Mode
	{
		20, 15, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		TIModeText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// TI Mode Adjust
	{
		35, 15, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustTIMode, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawTIModeGroup	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	//Odd channel MSB/LSB Exchange.
	{
		1, 16, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		OddMSBLSBExchangeText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// Odd channel MSB/LSB Exchange Adjust
	{
		16, 16, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustOddMSBLSBExchange, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawOddMSBLSBExchangeGroup// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	//Even channel MSB/LSB Exchange.
	{
		20, 16, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		EvenMSBLSBExchangeText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// Even channel MSB/LSB Exchange Adjust
	{
		35, 16, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustEvenMSBLSBExchange, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawEvenMSBLSBExchangeGroup// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	//Odd channel Red/Blue bus Exchange.
	{
		1, 17, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		OddRBExchangeText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// Odd channel Red/Blue bus Exchange Adjust
	{
		16, 17, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustOddRBExchange, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawOddRBExchangeGroup// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	//Even channel Red/Blue bus Exchange.
	{
		20, 17, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		EvenRBExchangeText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// Even channel Red/Blue bus Exchange Adjust
	{
		35, 17, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustEvenRBExchange, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawEvenRBExchangeGroup// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	/* //Output DE Driving current select.
	{ 1, 17, // XPos, YPos;
	CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
	CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
	RootMenu, //NextMenuPage;
	DWI_Text,// DrawMenuItemType;
	DECurrentText, // DisplayText;
	FactoryNaviKeyEvent,
	{ NULL, // AdjustFunction
	  NULL// ExecFunction
	},// DisplayValue;
	{ NULL, // DrawNumberType
	  NULL, // DrawGuageType
	  NULL	// DrawRadioGroupType
	},
	   NULL, //Font
	mibSelectable // Flags
	},
	// Output DE Driving current  adjust
	{ 15, 17, // XPos, YPos;
	CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
	CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
	RootMenu, //NextMenuPage;
	DWI_Text,// DrawMenuItemType;
	NULL, // DisplayText;
	FactoryAdjustKeyEvent,
	{ AdjustDECurrent, // AdjustFunction
	  NULL// ExecFunction
	},// DisplayValue;
	{ NULL, // DrawNumberType
	  NULL, // DrawGuageType
	  DrawDECurrentValueGroup// DrawRadioGroupType
	},
	   NULL, //Font
	mibDrawValue |mibSelectable// Flags
	},
	 //Output Clock Driving current select.
	{ 20, 17, // XPos, YPos;
	CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
	CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
	RootMenu, //NextMenuPage;
	DWI_Text,// DrawMenuItemType;
	ClockCurrentText, // DisplayText;
	FactoryNaviKeyEvent,
	{ NULL, // AdjustFunction
	  NULL// ExecFunction
	},// DisplayValue;
	{ NULL, // DrawNumberType
	  NULL, // DrawGuageType
	  NULL	// DrawRadioGroupType
	},
	   NULL, //Font
	mibSelectable // Flags
	},
	// Output Clock Driving current adjust
	{ 34, 17, // XPos, YPos;
	CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
	CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
	RootMenu, //NextMenuPage;
	DWI_Text,// DrawMenuItemType;
	NULL, // DisplayText;
	FactoryAdjustKeyEvent,
	{ AdjustClockCurrent, // AdjustFunction
	  NULL// ExecFunction
	},// DisplayValue;
	{ NULL, // DrawNumberType
	  NULL, // DrawGuageType
	  DrawClockCurrentValueGroup// DrawRadioGroupType
	},
	   NULL, //Font
	mibDrawValue |mibSelectable// Flags
	},
	 //Output data Odd channel Driving current select
	{ 1, 18, // XPos, YPos;
	CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
	CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
	RootMenu, //NextMenuPage;
	DWI_Text,// DrawMenuItemType;
	OddCurrentText, // DisplayText;
	FactoryNaviKeyEvent,
	{ NULL, // AdjustFunction
	  NULL// ExecFunction
	},// DisplayValue;
	{ NULL, // DrawNumberType
	  NULL, // DrawGuageType
	  NULL	// DrawRadioGroupType
	},
	   NULL, //Font
	mibSelectable // Flags
	},
	// Output data Odd channel Driving current adjust
	{ 15, 18, // XPos, YPos;
	CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
	CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
	RootMenu, //NextMenuPage;
	DWI_Text,// DrawMenuItemType;
	NULL, // DisplayText;
	FactoryAdjustKeyEvent,
	{ AdjustOddCurrent, // AdjustFunction
	  NULL// ExecFunction
	},// DisplayValue;
	{ NULL, // DrawNumberType
	  NULL, // DrawGuageType
	  DrawOddCurrentValueGroup// DrawRadioGroupType
	},
	   NULL, //Font
	mibDrawValue |mibSelectable// Flags
	},
	 //Output data Even channel Driving current select.
	{ 20, 18, // XPos, YPos;
	CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
	CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
	RootMenu, //NextMenuPage;
	DWI_Text,// DrawMenuItemType;
	EvenCurrentText, // DisplayText;
	FactoryNaviKeyEvent,
	{ NULL, // AdjustFunction
	  NULL// ExecFunction
	},// DisplayValue;
	{ NULL, // DrawNumberType
	  NULL, // DrawGuageType
	  NULL	// DrawRadioGroupType
	},
	   NULL, //Font
	mibSelectable // Flags
	},
	//Output data Even channel Driving current adjust
	{ 34, 18, // XPos, YPos;
	CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
	CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
	RootMenu, //NextMenuPage;
	DWI_Text,// DrawMenuItemType;
	NULL, // DisplayText;
	FactoryAdjustKeyEvent,
	{ AdjustEvenCurrent, // AdjustFunction
	  NULL// ExecFunction
	},// DisplayValue;
	{ NULL, // DrawNumberType
	  NULL, // DrawGuageType
	  DrawEvenCurrentValueGroup// DrawRadioGroupType
	},
	   NULL, //Font
	mibDrawValue |mibSelectable// Flags
	},*/
	//BurstModeFreq
	{
		1, 19, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		BurstModeFreqText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	// BurstModeFreq adjust
	{
		13, 19, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustBurstModeFreq,	// AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawBurstModeFreqNumber,	// DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	//Default Duty
	{
		20, 19, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		DefDutyText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	//Default Duty Adjust
	{
		32, 19, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustDefDuty, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawDefDutyNumber, // DrawNumberType
			NULL, // DrawGuageType
			NULL// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	//Min Duty
	{
		1, 20, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		MinDutyText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	//Min Duty Adjust
	{
		13, 20, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustMinDuty, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawMinDutyNumber, // DrawNumberType
			NULL, // DrawGuageType
			NULL// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	//Max Duty
	{
		20, 20, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		MaxDutyText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	//Max Duty Adjust
	{
		32, 20, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustMaxDuty, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawMaxDutyNumber, // DrawNumberType
			NULL, // DrawGuageType
			NULL// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	//Output PLL spread spectrum Step Low Byte
	{
		1, 21, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		SSCSTEPLText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	//Output PLL spread spectrum Step Low Byte Adjust
	{
		15, 21, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustSSCSTEPL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawSSCSTEPLNumber, // DrawNumberType
			NULL, // DrawGuageType
			NULL// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	//Output PLL spread spectrum Step High Byte
	{
		20, 21, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		SSCSTEPHText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	//Output PLL spread spectrum Step High Byte Adjust
	{
		34, 21, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustSSCSTEPH, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawSSCSTEPHNumber, // DrawNumberType
			NULL, // DrawGuageType
			NULL// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	//Output PLL spread spectrum Span Low Byte
	{
		1, 22, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		SSCSPANLText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	//Output PLL spread spectrum Span Low Byte Adjust
	{
		15, 22, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustSSCSPANL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawSSCSPANLNumber, // DrawNumberType
			NULL, // DrawGuageType
			NULL// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	//Output PLL spread spectrum Span High Byte
	{
		20, 22, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		SSCSPANHText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	//Output PLL spread spectrum Span High Byte Adjust
	{
		34, 22, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustSSCSPANH, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			DrawSSCSPANHNumber, // DrawNumberType
			NULL, // DrawGuageType
			NULL// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},

	//Change Mode Panel Vdd On/Off
	{
		1, 23, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		ChangeModePanelVddText, // DisplayText;
		FactoryNaviKeyEvent,
		{
			NULL, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	//Change Mode Panel Vdd On/Off Adjust
	{
		16, 23, // XPos, YPos;
		CP_WhiteColor, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		NULL, // DisplayText;
		FactoryAdjustKeyEvent,
		{
			AdjustChangeModePanelVddOnOff, // AdjustFunction
			NULL// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			DrawChangeModePanelVddGroup// DrawRadioGroupType
		},
		NULL, //Font
		mibDrawValue | mibSelectable // Flags
	},
	{
		1, 25, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		InitialSettingText, // DisplayText;
		NaviExecKeyEvent,
		{
			NULL, // AdjustFunction
			InitialPanelSetting// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},
	{
		20, 25, // XPos, YPos;
		CP_LightBlue, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Text,// DrawMenuItemType;
		SaveSettingText, // DisplayText;
		NaviExecKeyEvent,
		{
			NULL, // AdjustFunction
			SaveCurrentPanelSetting// ExecFunction
		},// DisplayValue;
		{
			NULL, // DrawNumberType
			NULL, // DrawGuageType
			NULL	// DrawRadioGroupType
		},
		NULL, //Font
		mibSelectable // Flags
	},

};

#endif





#endif



