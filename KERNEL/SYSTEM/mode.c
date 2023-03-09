




//2006-06-20
#include "Global.h"
#include "AutoFunc.h"
#include "Detect.h"
#if ENABLE_FREESYNC
#include "ComboApp.h"
#endif

extern BYTE mStar_GetInputStatus( void );
#if FindModeByVwidth
extern BYTE GetVSyncWidth(void);
#endif
InputResolutionType code StandardModeResolution[] =
{
	{ 640,  350},  // Res_640x350,
	{ 640,  400},  // Res_640x400,
	{ 720,  400},  // Res_720x400,
	{ 640,  480},  // Res_640x480,
	//{ 720,  483},  //Res_720x483, // 120424 coding reserved Res_720x483
	{700,	570},//Res_700x570
	{ 720,  576},  //Res_720x576,
	{ 800,  600},  // Res_800x600,
	{ 832,  624},  // Res_832x624,
	{ 884,  930},  // Res_884x930,
	{1024,  768},  // Res_1024x768,
	{1280, 1024},  // Res_1280x1024,
	{1600, 1200},  // Res_1600x1200,
	{1152,  864},  // Res_1152x864,
	{1152,  870},  // Res_1152x870,
	{1280,  720},  // Res_1280x720,
	{1280,  960},  // Res_1280x960,
	{ 720,  480},  // Res_720x240
	{ 800,  1209}, // Res_800x1209
	{1792,  1344}, // Res_1792x1344
	{1400,  1050}, // Res_1400x1050
	{1920,  1080}, // Res_1920x1080
	{1920,  1200}, // Res_1920x1200
	{848,    480}, // Res_848x480
	{1280,   768}, // Res_1280x768
	{1360,   768}, // Res_1360x768
	{1366,	768},//Res_1366x768
	{1440,   900}, // Res1440x900
	{1680,  1050}, // Res_1680x1050
	{1280,  800}, // Res_1280x800
	{1600,   900}, // Res_1600x900
	{1600,  1024}, // Res_1600x1024

	#if  ENABLE_DUAL_LINK
	{640, 480}, // Res_640x480_2D
	{800, 600}, // Res_800x600_2D
	{1280, 960}, // Res_1280x960_2D
	{1024, 768}, // Res_1024x768_2D
	{1440, 900}, // Res_1440x900_2D

	{1920, 1080}, // Res_1920x1080_2D
	{2560, 1440},//Res_2560x1440//20130801 nick
	#endif

	#if SHARP_VGA_50Hz_Timing
	{1152, 900}
	#endif

};
InputModeType code StandardMode[] =
{
//===== 2005-07-26 Andy For Wide Timing =====
// 0. 848X480 60HZ
	{
		SyncHpVp, // Flags
		Res_848x480, // ResIndex
		310, 600, // HFreq, VFreq
		1088, 517, // HTotal, VTotal
		225, 22, // HStart, VStart
	},
	// 1.1280X768 60HZ Reduced Blanking(VESA)
	{
		SyncHpVn, // Flags
		Res_1280x768, // ResIndex
		474, 599, // HFreq, VFreq
		1440, 790, // HTotal, VTotal
		112, 11, // HStart, VStart
	},
// 2.1280X768 60HZ Normal Blanking(VESA)
	{
		SyncHnVp, // Flags
		Res_1280x768, // ResIndex
		477, 598, // HFreq, VFreq
		1664, 798, // HTotal, VTotal
		319, 19, // HStart, VStart
	},
// 3.1280X768 75HZ
	{
		SyncHnVp, // Flags
		Res_1280x768, // ResIndex
		603, 748, // HFreq, VFreq
		1696, 805, // HTotal, VTotal
		336 - 7, 34 - 7 - 1, //336, 34, // HStart, VStart
	},
// 4.1280X768 85HZ
	{
		SyncHnVp, // Flags
		Res_1280x768, // ResIndex
		686, 848, // HFreq, VFreq
		1712, 809, // HTotal, VTotal
		352 - 6, 38 - 7 - 1, //352, 38, // HStart, VStart
	},
	// 5. 1280x960 60Hz (VESA)
	{
		//SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn |bWideMode, // Flags
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,
		Res_1280x960, // ResIndex
		600, 600, // HFreq, VFreq
		1696, 996, //1800, 1000, // HTotal, VTotal
		424, 39, // HStart, VStart
	},

// 6. 1280x960 60Hz (VESA)
	{
		//SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn |bWideMode, // Flags
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,
		Res_1280x960, // ResIndex
		600, 600, // HFreq, VFreq
		1800, 1000, // HTotal, VTotal
		423, 35,//424, 39, // HStart, VStart
	},
// 7. 1280x960 70Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1280x960, // ResIndex
		700, 700, // HFreq, VFreq
		1727, 1000, // HTotal, VTotal
		353, 38, // HStart, VStart
	},
//8. 1280x960 72Hz (VESA)			//need check
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,  // Flags
		Res_1280x960, // ResIndex
		723, 722, // HFreq, VFreq
		1696, 1002,//1728, 1001, // HTotal, VTotal
		353, 38, // HStart, VStart
	},
	//===================================================
	//===>Conflict with SXVGA+(1400x900@75Hz HnVP  ) ====
	//===================================================
// 9. 1280x960 75Hz (VESA)
	{
		//SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		SyncHpVp | SyncHpVn | SyncHnVn | SyncHnVp, // Flags
		Res_1280x960, // ResIndex
		750, 750, // HFreq, VFreq
		1728, 1005,//1680, 1000, // HTotal, VTotal
		383, 35, // HStart, VStart
	},
// 10. 1280x960 85Hz (VESA)
	{
		//SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		SyncHpVp, // Flags
		Res_1280x960, // ResIndex
		859, 850, // HFreq, VFreq
		1728, 1011, // HTotal, VTotal
		384 - 6, 50 - 3 - 1, //384, 50, // HStart, VStart
	},
	// 11. 1360X768 60HZ
	{
		SyncHpVp, // Flags
		Res_1360x768, // ResIndex
		477, 600, // HFreq, VFreq
		1792, 795 - 1, // HTotal, VTotal
		362, 17, // HStart, VStart
	},
//12  //1366x768 60Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,
		Res_1366x768, // ResIndex
		477, 598, // HFreq, VFreq
		1790, 798 + 1, // HTotal, VTotal
		356 - 6, 27 - 3 - 1, //368, 24, // HStart, VStart
	},
// 13. 1440X900 60HZ Reduce Blanking(VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,   // Flags
		Res_1440x900, // ResIndex
		554, 599, // HFreq, VFreq
		1600, 926, // HTotal, VTotal
		112, 23 - 6 - 1, //112, 23, // HStart, VStart
	},
// 14. 1440X900 60HZ Normal Blanking(VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,   // Flags
		Res_1440x900, // ResIndex
		559, 598, // HFreq, VFreq
		1904, 934, // HTotal, VTotal
		383, 31 - 6 - 1, //384, 31, // HStart, VStart
	},
// 15. 1440X900 75HZ
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,   // Flags
		Res_1440x900, // ResIndex
		706, 750, // HFreq, VFreq
		1936, 942, // HTotal, VTotal
		400 - 6,  39 - 6 - 1, //400,  39, // HStart, VStart
	},
// 16. 1440X900 85HZ
	{
		SyncHnVp, // Flags
		Res_1440x900, // ResIndex
		804, 848, // HFreq, VFreq
		1952, 948, // HTotal, VTotal
		408 - 6,  45 - 6 - 1, //408,  45, // HStart, VStart
	},
// 17. 1680X1050 60HZ Reduced Blanking(VESA)
	{
		SyncHnVp | SyncHpVn | SyncHpVp | SyncHnVn, // Flags
		Res_1680x1050, // ResIndex
		646,  598, // HFreq, VFreq
		1840, 1080, // HTotal, VTotal
		112,   20, // HStart, VStart
	},
// 18. 1680X1050 60HZ Normal Blanking(VESA)
	{
		SyncHnVp | SyncHpVn | SyncHpVp | SyncHnVn, // Flags
		Res_1680x1050, // ResIndex
		652, 599,  // HFreq, VFreq
		2240, 1089, // HTotal, VTotal
		454,  29,  // HStart, VStart
	},

// 19. 1680X1050 75HZ
	{
		SyncHnVp, // Flags
		Res_1680x1050, // ResIndex
		823, 748,  // HFreq, VFreq
		2272, 1099, // HTotal, VTotal
		470,  39,  // HStart, VStart
	},
//====================================
//===== Normal Mode Start ============
//====================================
// 20. 640x350 70Hz (IMB VGA)
	{
		SyncHpVn, // Flags
		Res_640x350, // ResIndex
		315, 700, // HFreq, VFreq
		800, 449, // HTotal, VTotal
		90, 62 - 2 - 1 //144 - 5, 62 - 2 - 1, // HStart, VStart    //PS. spec 144, 61
	},
	// 21. 640x350 85Hz (VESA)
	{
		SyncHpVn, // Flags
		Res_640x350, // ResIndex
		379, 851, // HFreq, VFreq
		832, 445, // HTotal, VTotal
		80, 63 - 3 - 1, // HStart, VStart
	},
	// 22. 720x400 70Hz (VGA)
	{
		SyncHpVp | SyncHnVp | SyncHnVn, // Flags
		Res_720x400, // ResIndex
		315, 700, // HFreq, VFreq
		900, 449, // HTotal, VTotal
		162, 34,//160 - 6, 37 - 2 - 1, //160 - 6, 37 - 2 - 1, // HStart, VStart     //PS.spec 153, 29
	},
	// 23. 720x400 85Hz (VESA)
	{
		SyncHpVp | SyncHnVp | SyncHnVn, // Flags
		Res_720x400, // ResIndex
		379, 850, // HFreq, VFreq
		936, 446, // HTotal, VTotal
		180 - 5, 45 - 3 - 1, //180, 45, // HStart, VStart
	},
	// 24. 640x400 85Hz (VESA)
	{
		SyncHpVp | SyncHnVp | SyncHnVn, // Flags
		Res_640x400, // ResIndex
		379, 851, // HFreq, VFreq
		832, 445, // HTotal, VTotal
		80, 33 - 8 - 1, // HStart, VStart
	},
	//===============================================
	//===>Conflict with WSVGA(848x480@60Hz HpVp) ====
	//===============================================
	// 25. 640x480 60Hz (VESA)
	{
		//SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_640x480, // ResIndex
		315, 599, // HFreq, VFreq
		800, 525, // HTotal, VTotal
		144, 32,  //136, 27 - 3, //139, 32, // HStart, VStart           //spec 136, 27   //111111 Rick modified
	},
	// 26. 640x480 66Hz (MAC)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_640x480, // ResIndex
		350, 667, // HFreq, VFreq
		864, 525, // HTotal, VTotal
		160, 38, // HStart, VStart
	},
	//27   // 30. 640x480 67Hz	//ATI		//111223 Modify
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_640x480, // ResIndex
		335, 671, // HFreq, VFreq
		816, 499, // HTotal, VTotal
		153, 14, // HStart, VStart
	},

	// 28. 640x480 72Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_640x480, // ResIndex
		379, 728, // HFreq, VFreq
		832, 520, // HTotal, VTotal
		168, 27, // HStart, VStart
	},
	// 29. 640x480 75Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_640x480, // ResIndex
		375, 750, // HFreq, VFreq
		840, 500, // HTotal, VTotal
		184, 15,// HStart, VStart
	},
	// 30. 640x480 85Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_640x480, // ResIndex
		433, 850, // HFreq, VFreq
		832, 509, // HTotal, VTotal
		136 - 5, 28 - 3 - 1, //136, 28, // HStart, VStart
	},

	// 31. 800x600 56Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_800x600, // ResIndex
		352, 562, // HFreq, VFreq
		1024, 625, // HTotal, VTotal
		201, 21, // HStart, VStart
	},
	// 32. 800x600 60Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_800x600, // ResIndex
		379, 603, // HFreq, VFreq
		1056, 628, // HTotal, VTotal
		217, 22, // HStart, VStart
	},
	// 33. 800x600 72Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_800x600, // ResIndex
		481, 722, // HFreq, VFreq
		1040, 666, // HTotal, VTotal
		185, 22, // HStart, VStart
	},
	// 34. 800x600 75Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_800x600, // ResIndex
		469, 750, // HFreq, VFreq
		1056, 625, // HTotal, VTotal
		241, 20, // HStart, VStart
	},
	// 35. 800x600 85Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_800x600, // ResIndex
		537, 851, // HFreq, VFreq
		1048, 631, // HTotal, VTotal
		216 - 5, 30 - 3 - 1, //216, 30, // HStart, VStart
	},

	// 36. 832x624 75Hz (MAC)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_832x624, // ResIndex
		497, 746, // HFreq, VFreq
		1152, 665,//667, // HTotal, VTotal
		288, 38, // HStart, VStart
	},
	//========================================================
	//===>Conflict with WXVGA(1280x768@60Hz HpVp;HnVp) ====
	//========================================================

	// 37. 1024x768 60Hz (VESA)
	{
		//SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flagsc
		SyncHpVn | SyncHnVn, // Flags
		Res_1024x768, // ResIndex
		484, 600, // HFreq, VFreq
		1344, 806, // HTotal, VTotal
		295, 28 // HStart, VStart
	},
	// 38. 1024x768 60Hz (VESA)
	{
		//SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flagsc
		SyncHpVn | SyncHnVn, // Flags
		Res_1024x768, // ResIndex
		484, 600, // HFreq, VFreq
		1312, 813, // HTotal, VTotal
		290, 39 - 3, // HStart, VStart
	},
	// 39. 1024x768 70Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1024x768, // ResIndex
		565, 700, // HFreq, VFreq
		1328, 806, // HTotal, VTotal
		279, 28, // HStart, VStart
	},

	//===============================================
	//===>Conflict with WXVGA(1280x768@75Hz HnVp) ===
	//===============================================
	// 40. 1024x768 75Hz (VESA)
	{
		//SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		SyncHpVp | SyncHpVn | SyncHnVn, // Flags
		Res_1024x768, // ResIndex
		600, 750, // HFreq, VFreq
		1312, 800, // HTotal, VTotal
		272, 27, // HStart, VStart
	},
	// 41. 1024x768 75Hz (MAC)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1024x768, // ResIndex
		602, 749, // HFreq, VFreq
		1326, 804, // HTotal, VTotal
		271, 29, // HStart, VStart
	},
	//===============================================
	//===>Conflict with WXVGA(1280x768@85Hz HnVp) ===
	//===============================================
	// 42. 1024x768 85Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVn, // Flags
		Res_1024x768, // ResIndex
		683, 850, // HFreq, VFreq
		1376, 808, // HTotal, VTotal
		304 - 5, 39 - 3 - 1, //304, 39, // HStart, VStart
	},
	// 43. 1152x864 60Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1152x864, // ResIndex
		536, 600, // HFreq, VFreq
		1520, 896, // HTotal, VTotal    //2004-09-10
		263, 23, // HStart, VStart
	},
	// 44. 1152x864 70Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1152x864, // ResIndex
		642, 702, // HFreq, VFreq
		1536, 912,//14, // HTotal, VTotal
		295, 43, // HStart, VStart
	},
	// 45. 1152x864 70Hz (For ATI Card)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1152x864, // ResIndex
		662, 702, // HFreq, VFreq
		1536, 900,//14, // HTotal, VTotal
		200, 49, // HStart, VStart
	},
	// 46. 1152x864 75Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1152x864, // ResIndex
		675, 750, // HFreq, VFreq
		1560, 900, //1600, 900, // HTotal, VTotal  --- 2004-09-09
		383, 31, // HStart, VStart
	},
	// 47. 1152x864 85Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1152x864, // ResIndex
		771, 850, // HFreq, VFreq
		1576, 907, // HTotal, VTotal
		210, 42, // HStart, VStart
	},
	#if 1
	// 48. 1152x870 75Hz (MAC)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1152x870, // ResIndex
		689, 751, // HFreq, VFreq
		1456, 915, // HTotal, VTotal
		264, 38, // HStart, VStart
	},
	#endif
	// 49. 1280x720 60Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1280x720, // ResIndex
		447, 600, // HFreq, VFreq
		1688, 750, // HTotal, VTotal
		319, 19, // HStart, VStart //Larry 20130902 frome FOS chroma 2226.
	},
	// 50. 1280x720 60Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1280x720, // ResIndex
		447, 600, // HFreq, VFreq
		1440, 741, // HTotal, VTotal
		424, 39, // HStart, VStart
	},
	// 51. 1280x720 70Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1280x720, // ResIndex
		524, 700, // HFreq, VFreq
		1688, 750, // HTotal, VTotal
		140, 39, // HStart, VStart
	},
	// 52. 1280x720 75Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1280x720, // ResIndex
		563, 750, // HFreq, VFreq
		1688, 750, // HTotal, VTotal
		160, 39, // HStart, VStart
	},
	//========================================================
	//===>Conflict with SXVGA+(1400x1050@60Hz HpVn,HnVP ) ====
	//========================================================
	//53. 1280x1024 60Hz (VESA)
	{
		SyncHpVp | SyncHnVn | SyncHpVn | SyncHnVp, // Flags
		Res_1280x1024, // ResIndex
		640, 600, // HFreq, VFreq
		1688, 1066, // HTotal, VTotal
		359,  37, // HStart, VStart
	},

	//54. 1280x1024 75Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1280x1024, // ResIndex
		800, 750, // HFreq, VFreq
		1688, 1066, // HTotal, VTotal
		391, 37, // HStart, VStart
	},
	//55. 1280x1024 85Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1280x1024, // ResIndex
		911, 850, // HFreq, VFreq
		1728, 1072, // HTotal, VTotal
		384 - 7, 47 - 3 - 1, //384, 47, // HStart, VStart
	},

	#if 1//#ifdef PanelType_1600x900// (PanelWidth==1600 && PanelHeight==900)
// 56 // Mode_1600x900_60_R // 66 //Hfreq/Vfreq/Vtotal are the same with 1280x960 60(26)
	{
		SyncHpVp, // Flags
		Res_1600x900, // ResIndex
		600, 600, // HFreq, VFreq
		1800, 1000, // HTotal, VTotal
		176 - 6, 99 - 3 - 1, //0xab, 0x5f,//(10+12), (3+96), // HStart, VStart
	},
//57  // Mode_1600x900_60,
	{
		SyncHnVp, // Flags
		Res_1600x900, // ResIndex
		559, 599, // HFreq, VFreq
		2112, 934, // HTotal, VTotal
		256, 26,//(10+12), (3+96), // HStart, VStart
	},

//58 // Mode_1600x900_75,
	{
		SyncHnVp, // Flags
		Res_1600x900, // ResIndex
		705, 748, // HFreq, VFreq
		2144, 942, // HTotal, VTotal
		272, 34,//(10+12), (3+96), // HStart, VStart
	},
	#endif

	//59. 1600x1200 60Hz (VESA)
	{
		SyncHpVp | SyncHnVn, // Flags
		Res_1600x1200, // ResIndex
		750, 600, // HFreq, VFreq
		2160, 1250, // HTotal, VTotal
		495, 45, // HStart, VStart
	},
	//60. 1600x1200 65Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1600x1200, // ResIndex
		813, 650, // HFreq, VFreq
		2160, 1250, // HTotal, VTotal
		496 - 9, 49 - 24 - 1, //496, 49, // HStart, VStart
	},


	//61. 1600x1200 70Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1600x1200, // ResIndex
		875, 700, // HFreq, VFreq
		2160, 1250, // HTotal, VTotal
		495, 45, // HStart, VStart
	},
	//62. 1600x1200 75Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1600x1200, // ResIndex
		938, 750, // HFreq, VFreq
		2160, 1250, // HTotal, VTotal
		495, 45, // HStart, VStart
	},



	//63. 1400x1050 75Hz (VESA)
	{
		SyncHnVp,      // Flags
		Res_1400x1050, // ResIndex
		823, 749,      // HFreq, VFreq
		1896, 1099,    // HTotal, VTotal
		392 - 6, 46 - 4 - 1, //392, 46,     // HStart, VStart
	},
	//64. 1400x1050 85Hz (VESA)
	{
		SyncHnVp,      // Flags
		Res_1400x1050, // ResIndex
		938,  849,      // HFreq, VFreq
		1912, 1105,    // HTotal, VTotal
		408 - 6,  52 - 4 - 1, //408,  52,     // HStart, VStart
	},
	//65. 1792x1344 60Hz (VESA)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1792x1344, // ResIndex
		836, 600, // HFreq, VFreq
		2448, 1394, // HTotal, VTotal
		528 - 6, 49 - 3 - 1, //500, 46, // HStart, VStart
	},



	//66. 1920x1080 60Hz   173M
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1920x1080, // ResIndex
		672, 600, // HFreq, VFreq
		2576, 1120, // HTotal, VTotal
		456 - 9, 35 - 3 - 1, //528, 37, // HStart, VStart
	},
	//67. 1920x1200 60Hz (VESA) Reduce Blanking
	{
		SyncHpVn, // Flags
		Res_1920x1200, // ResIndex
		740, 600, // HFreq, VFreq
		2080, 1235, // HTotal, VTotal
		112 - 5, 32 - 6 - 1, // 112, 32, // HStart, VStart
	},
	//68. 1920x1200 60Hz (VESA)
	{
		SyncHnVp, // Flags
		Res_1920x1200, // ResIndex
		746, 600, // HFreq, VFreq
		2592, 1245, // HTotal, VTotal
		536 - 6, 42 - 6 - 1, //536, 42, // HStart, VStart
	},
	//69. 720x480 60Hz (YCbCr)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn | bInterlaceMode, // Flags
		Res_720x480, // ResIndex
		156, 500, // HFreq, VFreq
		900, 525, // HTotal, VTotal
		144, 88, // HStart, VStart
	},

	// 70. 800x1209 //TPV
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_800x1209, // ResIndex
		756, 600, // HFreq, VFreq
		1072, 1259, // HTotal, VTotal
		152 + 96, 46 - 3, // HStart, VStart
	},
	// 71. 1024x768 72Hz (VESA)  //2006-07-07 Andy
	{
		//SyncHpVp | SyncHpVn | SyncHnVp  // Flags
		SyncHpVp | SyncHnVp, // Flags
		Res_1024x768, // ResIndex
		571, 721, // HFreq, VFreq
		1312, 800, // HTotal, VTotal
		279, 28, // HStart, VStart
	},

	// 72 1280 X 1024  72 Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1280x1024, // ResIndex
		770, 720, // HFreq, VFreq
		1712, 1064, // HTotal, VTotal
		359, 51, // HStart, VStart
	},

	//73 1280 X 1024 70 Hz    60
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1280x1024, // ResIndex
		748, 697, // HFreq, VFreq
		1722, 1066, // HTotal, VTotal
		336, 37, // HStart, VStart
	},

//74 720x480I 60Hz (YPbPr)  --> 78  Start of YPbPr
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn | bInterlaceMode, // Flags
		Res_720x480, // resolution index
		156, 600,    // HFreq, VFreq
		858, 525,    // HTotal, VTotal
		238, 18,       // HStart, VStart
	},

	//75 1920x1080i 50Hz (YPbPr)  --> 84
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn | bInterlaceMode, // Flags
		Res_1920x1080, // resolution index
		281, 500,      // HFreq, VFreq
		2640, 1125,    // HTotal, VTotal
		186, 24,       // HStart, VStart
	},
	//76. NTSC 1080i
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn | bInterlaceMode, // Flags
		Res_1920x1080, // resolution index
		337, 600,      // HFreq, VFreq
		2200, 1125,    // HTotal, VTotal
		232, 27,       // HStart, VStart
	},
	//77  700x570 50Hz (For India TV Box)
	{
		SyncHpVp,   // Flags
		Res_700x570, // ResIndex
		313, 500, // HFreq, VFreq
		884, 625, // HTotal, VTotal
		179, 43, // HStart, VStart
	},
	//78  1152x870 60Hz (MAC)
	{
		SyncHnVp,   // Flags
		Res_1152x870, // ResIndex
		540, 600, // HFreq, VFreq
		1480, 900, // HTotal, VTotal
		264, 24, // HStart, VStart
	},
	//79. 576P(YCbCr)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,   // Flags
		Res_720x576, // ResIndex
		312, 500, // HFreq, VFreq
		864, 625, // HTotal, VTotal
		125, 40, // HStart, VStart
	},

// 80. 480P 60Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,   // Flags
		Res_720x480, // ResIndex // Res_720x483 120424 coding reserved Res_720x483
		315, 599, // HFreq, VFreq
		858, 525, // HTotal, VTotal
		138, 32,   // HStart, VStart
	},


//=============================================================================

	//81. 720p 60Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,   // Flags
		Res_1280x720, // ResIndex
		450, 600, // HFreq, VFreq
		1650, 750, // HTotal, VTotal
		260 - 5, 25 - 5 - 1, //296, 20, // HStart, VStart
	},

	//82. PAL 1080p
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,   // Flags
		Res_1920x1080, // ResIndex
		562, 500, // HFreq, VFreq
		2640, 1125, // HTotal, VTotal
		112, 28, // HStart, VStart
	},
	//83. 1080p 148.35M
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,   // Flags
		Res_1920x1080, // ResIndex
		674, 599, // HFreq, VFreq
		2200, 1125,// HTotal, VTotal
		192 - 7, 41 - 5 - 1, //232, 34,       // HStart, VStart
	},
	// 84. 832x624 75Hz (MAC)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_832x624, // ResIndex
		497, 746, // HFreq, VFreq
		1152, 662, // HTotal, VTotal
		288, 42, // HStart, VStart
	},
	//85
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,   // Flags
		Res_720x576, // ResIndex
		455, 750, // HFreq, VFreq
		944, 602, // HTotal, VTotal
		169, 20, // HStart, VStart
	},
	//86. 576i
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn | bInterlaceMode, // Flags
		Res_720x576, // ResIndex
		156, 500, // HFreq, VFreq
		864, 625, // HTotal, VTotal
		132, 22, // HStart, VStart
	},
	//87 1280x800 60Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,   // Flags
		Res_1280x800, // ResIndex
		497, 598, // HFreq, VFreq
		1680, 831,// HTotal, VTotal
		335, 20, // HStart, VStart
	},
	//88 1280x800 60Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,   // Flags
		Res_1280x800, // ResIndex
		497, 598, // HFreq, VFreq
		1696, 838,// HTotal, VTotal
		335, 20, // HStart, VStart
	},
	//89 1280x800 60Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,   // Flags
		Res_1280x800, // ResIndex
		493, 599, // HFreq, VFreq
		1440, 823,// HTotal, VTotal
		336 - 5, 35 - 6 - 1, //334, 35,       // HStart, VStart
	},
	//90 1280x800 75Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,   // Flags
		Res_1280x800, // ResIndex
		628, 749, // HFreq, VFreq
		1696, 838,// HTotal, VTotal
		336 - 5, 35 - 6 - 1, //336, 35,       // HStart, VStart
	},


	//91 1280x800 76Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,   // Flags
		Res_1280x800, // ResIndex
		647, 764, // HFreq, VFreq
		1568, 846,// HTotal, VTotal
		264, 43,       // HStart, VStart
	},
	//92 1080p 138.5M
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,   // Flags
		Res_1920x1080, // ResIndex
		666, 599, // HFreq, VFreq
		2080, 1111,// HTotal, VTotal
		112, 23,  // HStart, VStart
	},
	//93 1080p 148.5M
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,   // Flags
		Res_1920x1080, // ResIndex
		663, 599, // HFreq, VFreq
		2240, 1107,// HTotal, VTotal
		256 - 9, 26 - 3 - 1, //256, 26,       // HStart, VStart
	},
	//94 1600x1024 60Hz NVIDIA
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,	// Flags
		Res_1600x1024, // ResIndex
		636, 600, // HFreq, VFreq
		2144, 1060,// HTotal, VTotal
		442, 31,//256, 26,		 // HStart, VStart
	},
	//95 1920x1080_50			//130917 Henry add For MK Chrma K-8256
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,   // Flags
		Res_1920x1080, // ResIndex
		556, 499, // HFreq, VFreq
		2544, 1114, // HTotal, VTotal
		508, 25, // HStart, VStart
	},
	//96 1920x1080_75			//130917 Henry add For MK Chrma K-8256
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn,   // Flags
		Res_1920x1080, // ResIndex
		839, 750, // HFreq, VFreq
		2080, 1119, // HTotal, VTotal
		106, 24, // HStart, VStart
	},
	//////////////////////////////////////////
	#if  ENABLE_DUAL_LINK
// 97   // 640X480 100Hz RB
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_640x480_2D, // resolution index
		503, 1000,      // HFreq, VFreq
		800, 504,    // HTotal, VTotal
		112, 17,       // HStart, VStart
	},

//98   // 640X480 100Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_640x480_2D, // resolution index
		510, 1000,      // HFreq, VFreq
		832, 512,    // HTotal, VTotal
		160, 25,       // HStart, VStart
	},

//99   // 640X480 120Hz RB
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_640x480_2D, // resolution index
		609, 1200,      // HFreq, VFreq
		800, 509,    // HTotal, VTotal
		112, 22,       // HStart, VStart
	},

//100  // 640X480 120Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_640x480_2D, // resolution index
		619, 1200,      // HFreq, VFreq
		848, 518,    // HTotal, VTotal
		168, 31,       // HStart, VStart
	},

//101  //800X600 100Hz(RB)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_800x600_2D, // resolution index
		627, 1000,      // HFreq, VFreq
		960, 629,    // HTotal, VTotal
		112, 22,       // HStart, VStart
	},

//102  //800X600 100Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_800x600_2D, // resolution index
		636, 1000,      // HFreq, VFreq
		1056, 639,    // HTotal, VTotal
		208, 32,       // HStart, VStart
	},


//103  //800X600 120Hz (RB)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_800x600_2D, // resolution index
		763, 1200,      // HFreq, VFreq
		960, 636,    // HTotal, VTotal
		112, 29,       // HStart, VStart
	},

	//104 //800X600 120Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_800x600_2D, // resolution index
		774, 1200,      // HFreq, VFreq
		1072, 646,    // HTotal, VTotal
		216, 39,       // HStart, VStart
	},


//105  //1280X960 100Hz (RB)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1280x960_2D, // resolution index
		1006, 1000,      // HFreq, VFreq
		1440, 1007,    // HTotal, VTotal
		112, 40,       // HStart, VStart
	},

//106  //1280X960 100Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1280x960_2D, // resolution index
		1017, 1000,      // HFreq, VFreq
		1744, 1020,    // HTotal, VTotal
		368, 53,       // HStart, VStart
	},

	//107 //1024X768 100Hz (RB)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1024x768_2D, // resolution index
		804, 1000,      // HFreq, VFreq
		1184, 806,    // HTotal, VTotal
		112, 31,       // HStart, VStart
	},

//108  //1024X768 100Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1024x768_2D, // resolution index
		815, 1000,      // HFreq, VFreq
		1376, 816,    // HTotal, VTotal
		280, 41,       // HStart, VStart
	},


	//109 //1024X768 120Hz (RB)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1024x768_2D, // resolution index
		975, 1200,      // HFreq, VFreq
		1184, 813,    // HTotal, VTotal
		112, 38,       // HStart, VStart
	},

	//110 //1024X768 120Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1024x768_2D, // resolution index
		989, 1200,      // HFreq, VFreq
		1392, 826,    // HTotal, VTotal
		288, 51,       // HStart, VStart
	},


	//111 //1440X900 120Hz RB
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1440x900_2D, // resolution index
		1142, 1200,      // HFreq, VFreq
		1600, 953,    // HTotal, VTotal
		112, 44,       // HStart, VStart
	},

	//112//1440X900 120Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1440x900_2D, // resolution index
		1159, 1200,      // HFreq, VFreq
		1968, 967,    // HTotal, VTotal
		416, 58,       // HStart, VStart
	},


	//113 //  1920x1080P 120Hz (2D-CVT-RB)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1920x1080_2D, // resolution index //Mod_1920x1080_120Nv2D,
		1372, 1200,      // HFreq, VFreq
		2080, 1144,    // HTotal, VTotal
		80, 8,       // HStart, VStart
	},


//114  //  1920x1080P 120Hz       109
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1920x1080_2D, // resolution index //Mod_1920x1080_120Nv2D,
		1391, 1200,      // HFreq, VFreq
		2656, 1160,    // HTotal, VTotal
		80, 8,       // HStart, VStart
	},



	//115 //  1920x1080P 110Hz (2D-CVT-RB)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1920x1080_2D, // resolution index  //Mod_1920x1080_110Nv2D,
		1251, 1100,      // HFreq, VFreq
		2080, 1138,    // HTotal, VTotal
		80, 8,       // HStart, VStart
	},


	//116 //  1920x1080P 110Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1920x1080_2D, // resolution index  //Mod_1920x1080_110Nv2D,
		1267, 1100,      // HFreq, VFreq
		2640, 1153,    // HTotal, VTotal
		80, 8,       // HStart, VStart
	},


	//117 //  1920x1080P 100Hz (2D-CVT-RB)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1920x1080_2D, // resolution index   // Mod_1920x1080_100Nv2D,
		1133, 1000,      // HFreq, VFreq
		2080, 1133,    // HTotal, VTotal
		80, 8,       // HStart, VStart
	},


	//118//  1920x1080P 100Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1920x1080_2D, // resolution index   // Mod_1920x1080_100Nv2D,
		1145, 1000,      // HFreq, VFreq
		2640, 1147,    // HTotal, VTotal
		80, 8,       // HStart, VStart
	},


//119//  1920x1080P 144Hz (2D-CVT-RB)
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1920x1080_2D,
		1581, 1440,      // HFreq, VFreq
		2056, 1098,    // HTotal, VTotal
		80, 8,       // HStart, VStart
	},

//120//2560x1440 60Hz //20130801 nick from  VASE CVT timing
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_2560x1440,
		888, 600,      // HFreq, VFreq
		2720, 1481,    // HTotal, VTotal
		109, 32,       // HStart, VStart
	},

	#endif

	#if IIYAMASeries

	// 640x400 56Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_640x400, // ResIndex
		248, 564, // HFreq, VFreq
		848, 440, // HTotal, VTotal
		145, 24,// HStart, VStart
	},

	// 848x480 75Hz CVT
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_848x480, // ResIndex
		376, 747, // HFreq, VFreq
		1088, 504, // HTotal, VTotal
		200, 15,// HStart, VStart
	},

	// 1152x864 70Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1152x864, // ResIndex
		638, 700, // HFreq, VFreq
		1480, 912, // HTotal, VTotal
		296, 43,// HStart, VStart
	},

	// 1280x1024 70Hz
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1280x1024, // ResIndex
		748, 698, // HFreq, VFreq
		1696, 1072, // HTotal, VTotal
		384, 41,// HStart, VStart
	},
	#endif

//Mode_1400_1050_60_RB
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // 62
		Res_1400x1050, // ResIndex
		647, 599, // HFreq, VFreq
		1560, 1080, // HTotal, VTotal
		85, 21, // HStart, VStart
	},

//Mode_1400_1050_60
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // 62
		Res_1400x1050, // ResIndex
		653, 599, // HFreq, VFreq
		1864, 1089, // HTotal, VTotal
		232, 36, // HStart, VStart
	},

	#if SHARP_VGA_50Hz_Timing
	// MODE_640x400_56
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_640x400, // ResIndex
		248, 564, // HFreq, VFreq
		848, 440, // HTotal, VTotal
		145, 24,// HStart, VStart
	},

	// MODE_640x400_70
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_640x400, // ResIndex
		314, 700, // HFreq, VFreq
		800, 449, // HTotal, VTotal
		145, 24,// HStart, VStart
	},

	// MODE_720x400_50
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_720x400, // ResIndex
		314, 500, // HFreq, VFreq
		900, 629, // HTotal, VTotal
		162, 120,// HStart, VStart
	},

	//MODE_1024x768_50
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1024x768, // ResIndex
		396, 499, // HFreq, VFreq
		1312, 793, // HTotal, VTotal
		253, 24,// HStart, VStart
	},


	//MODE_1152x900_66
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1152x900, // ResIndex
		617, 659, // HFreq, VFreq
		1504, 937, // HTotal, VTotal
		300, 24,// HStart, VStart
	},

	// MODE_1152x900_66_SOG
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1152x900, // ResIndex
		618, 660, // HFreq, VFreq
		1530, 937, // HTotal, VTotal
		136, 24,// HStart, VStart
	},

	// MODE_1280x768_50
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1280x768, // ResIndex
		395, 499, // HFreq, VFreq
		1648, 793, // HTotal, VTotal
		145, 24,// HStart, VStart
	},

	// MODE_1280x960_50
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1280x960, // ResIndex
		494, 498, // HFreq, VFreq
		1680, 991, // HTotal, VTotal
		201, 25,// HStart, VStart
	},

	// MODE_1400x1050_50
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1400x1050, // ResIndex
		541, 499, // HFreq, VFreq
		1848, 1083, // HTotal, VTotal
		328, 24,// HStart, VStart
	},

	// MODE_1600x1200_50
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1600x1200, // ResIndex
		617, 499, // HFreq, VFreq
		2128, 1238, // HTotal, VTotal
		430, 90,// HStart, VStart
	},

	// MODE_1680x1050_50
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn, // Flags
		Res_1680x1050, // ResIndex
		541, 499, // HFreq, VFreq
		2208, 1083, // HTotal, VTotal
		314, 24,// HStart, VStart
	},

	#endif

	//////////////////////////////////////////
	//=====IMPORTANT	DON'T DELETE IT, OR IT WILL CAUSE LOOP INIFINITE
	{
		0, // Flags
		0, // ResIndex
		0, 0, // HFreq, VFreq
		0, 0, // HTotal, VTotal
		0, 0, // HStart, VStart
	}
};

WORD GetStandardModeWidth(void)
{
	return StandardModeResolution[StandardModeGroup].DispWidth;
}

WORD GetStandardModeHeight(void)
{
	return StandardModeResolution[StandardModeGroup].DispHeight;
}

WORD GetStandardModeGroup(void)
{
	return StandardMode[SrcModeIndex].ResIndex;
}

WORD GetStandardModeHTotal(void)
{
	return StandardMode[SrcModeIndex].HTotal;
}
#if (CHIP_ID==CHIP_TSUMU) || (CHIP_ID==CHIP_TSUM2) ||(CHIP_ID==CHIP_TSUMC)||(CHIP_ID==CHIP_TSUMD)
WORD GetStandardModeVTotal(void)
{
	return StandardMode[SrcModeIndex].VTotal;
}
#endif
//WORD GetStandardModeHFreq(void)
//{
//    return StandardMode[SrcModeIndex].HFreq;
//}
WORD GetStandardModeVFreq(void)
{
	return StandardMode[SrcModeIndex].VFreq;
}

WORD GetStandardModeHStart(void)
{
	return StandardMode[SrcModeIndex].HStart;
}

WORD GetStandardModeVStart(void)
{
	return StandardMode[SrcModeIndex].VStart;
}
//120601 Modify
#define PHASE_MAX          (0x80)
#define PHASE_STEP         (0x07)
#define PHASE_CENTER    0x40

#define CHECK_MODE_WIDTH   1
#define SIMILAR_TIMING_BUFFER_MAX   10
BYTE xdata ucSimilarTimingNums;
BYTE xdata ucSimilarTimingBuffer[SIMILAR_TIMING_BUFFER_MAX]; // record similar timing buffer

void appCheckSimilarTiming(void)
{
	#if CHECK_MODE_WIDTH
	WORD xdata wWidth;
	#endif
	BYTE vsyncTime, i, ucIndex, uccount;
	DWORD maxcksum, cksum, maxcksum1;
	BYTE adjPhase;
	if(ucSimilarTimingNums <= 1 || (SrcFlags & bUnsupportMode))
		return;
	vsyncTime = GetVSyncTime();
	i = 0;
	maxcksum = maxcksum1 = 0;
	ucIndex = SrcModeIndex = ucSimilarTimingBuffer[0];	//131210 jb
	uccount = (ucSimilarTimingNums >= SIMILAR_TIMING_BUFFER_MAX) ? (SIMILAR_TIMING_BUFFER_MAX) : (ucSimilarTimingNums);
	//printData(" ucSimilarTimingNums:%d", ucSimilarTimingNums);
	while(uccount--)
	{
		//111027 Rick add for reload ADC table while check similar timing - B39609
		wWidth = HFreq( SrcHPeriod );//(( DWORD )MST_CLOCK_MHZ * 10 + SrcHPeriod / 2 ) / SrcHPeriod; //calculate hfreq: round 5
		wWidth = (( DWORD )wWidth * StandardModeHTotal + 5000 ) / 10000; //dclk= hfreq * htotal
		drvADC_SetModewithPLLProtection(g_bInputSOGFlag ? ADC_INPUTSOURCE_YPBPR : ADC_INPUTSOURCE_RGB, wWidth, StandardModeHTotal);
		drvADC_AdjustHTotal(StandardModeHTotal);
		#if CHECK_MODE_WIDTH
		wWidth = SearchMaxWidth(vsyncTime);
		//printData(" width:%d", wWidth);
		if(abs(wWidth - StandardModeWidth) < 2)     //111223 Modify
		{
			//printData(" similar width:%d", wWidth);
			return;
		}
		#endif
		SC0_SET_IMAGE_WIDTH(StandardModeWidth);//msWrite2Byte( SC0_0B, StandardModeWidth);
		SC0_SET_IMAGE_HEIGHT(StandardModeHeight);//msWrite2Byte( SC0_09, StandardModeHeight );
		for( adjPhase = 0; adjPhase < PHASE_MAX; adjPhase += PHASE_STEP)
		{
			drvADC_SetPhaseCode( adjPhase );
			Delay1ms( vsyncTime + 3 );
			AUTO_PHASE_RESULT_READY();//WaitAutoStatusReady(SC0_8B, BIT1);
			//cksum = msRead2Byte(SC0_8E);
			//cksum = ( cksum << 16 ) | msRead2Byte(SC0_8C);
			cksum = AUTO_PHASE_READ_VALUE();
			if( cksum > maxcksum )
			{
				maxcksum = cksum;
			}
		}
		if(maxcksum > maxcksum1)
		{
			maxcksum1 = maxcksum;
			ucIndex = SrcModeIndex;
			#if DEBUG_PRINTDATA
			printData(" 11111111111SrcModeIndex_MaxCksm:%d", SrcModeIndex);
			#endif
		}
		SrcModeIndex = ucSimilarTimingBuffer[++i];
	}
	SrcModeIndex = ucIndex;
	#if DEBUG_PRINTDATA
	printData(" 22222222222SrcModeIndexFinal:%d", SrcModeIndex);
	#endif
}


#define DIGITAL_TOLERANCE   		3
#define RECHECK_INPUT_COUNT     	50 // unit: 20ms
#define RECHECK_INTERLACE_COUNT    25 // unit: 20ms		//120703 Modify

extern BYTE GetVSyncWidth(void);

Bool mStar_FindMode(void)
#if 1
{
	WORD hFreq, vFreq = 0;
	BYTE htol, vtol;
	WORD tempHeight, tempWidth;
	bit bDigitalInput = 0;
	#if ENABLE_HDMI && ENABLE_HDMI_1_4
	bit bHDMI3DTimingFlag = 0;
	#endif
#define fStatus  hFreq
	fStatus = mStar_GetInputStatus();
	if( SyncPolarity( SrcFlags ) != SyncPolarity( fStatus ) )        // Sync polarity changed
	{
		return FALSE;
	}
	#if ENABLE_FREESYNC
	SrcFlags &= 0x1F;
	#else
	SrcFlags &= 0x0F;
	#endif
#undef fStaus
	#if ENABLE_FREESYNC
	if (!IS_DP_FREESYNC())
	#endif
	{
		hFreq = SC0_READ_HPEROID();//msRead2Byte(SC0_E4) & 0x1FFF;
		if( abs( hFreq - SrcHPeriod ) > HPeriod_Torlance )        // HPeriod changed
		{
			return FALSE;
		}
	}
	#if ENABLE_FREESYNC
	if (!IS_HDMI_FREESYNC())
	#endif
	{
		vFreq = SC0_READ_VTOTAL();//msRead2Byte(SC0_E2) & 0xFFF;
		if( abs( vFreq - SrcVTotal ) > VTotal_Torlance )        // vtotal changed
		{
			return FALSE;
		}
	}
	#if DEBUG_PRINTDATA
	printData( " SrcHPeriod00000           :%d", SrcHPeriod );
	printData( " vFreq00000           :%d", vFreq );
	#endif
	//111223 Modify
	if( SrcHPeriod > 511 )        // prevent counter overflow when input frequency is very low
	{
		hFreq = SrcHPeriod * 16;
	}
	else
	{
		tempHeight = GetVSyncTime() * 12; ///3	//120112 Modify
		SC0_HPEROID_DETECT_MODE(TRUE);//msWriteByte(SC0_E5, BIT7); // enable 16 line line to calculate hsync period.	//120105 Modify
		Delay1ms( tempHeight );
		hFreq = SC0_READ_HPEROID();							//120105 Modify
		SC0_HPEROID_DETECT_MODE(FALSE);//msWriteByte(SC0_E5, 0);	//120105 Modify
		Delay1ms( tempHeight );
		if( abs( hFreq - SrcHPeriod * 16 ) > 80 )
			// prevent from getting the wrong hperiod to generate unknown panel clock
		{
			hFreq = SrcHPeriod * 16;
		}
	}
	hFreq = (hFreq + 8) / 16;
	/////////////////////////////////////////////////////////
	SrcHPeriod = hFreq;
	SrcVTotal = vFreq;
	#if DEBUG_PRINTDATA
	printData( " c SrcHPeriod00000           :%d", SrcHPeriod );
	printData( " c SrcVTotal           :%d", SrcVTotal );
	#endif
	#if ENABLE_FREESYNC
	if(IS_DP_FREESYNC())
	{
		WORD u16PixClk, u16Htt;
		u16PixClk = msAPI_combo_IPGetPixelClk();
		u16Htt = msAPI_combo_IPGetGetHTotal();
		if((u16Htt != 0) && (SrcVTotal != 0))
		{
			#if 0
			hFreq = ((DWORD)u16PixClk * 100 + u16Htt / 2) / u16Htt;
			vFreq = ((DWORD)hFreq * 1000 + SrcVTotal / 2) / SrcVTotal;
			#else
			hFreq = ((DWORD)u16PixClk * 10 + u16Htt / 2) / (u16Htt);
			hFreq = ((DWORD)hFreq * 1000 + SrcVTotal / 2) * 10 / (SrcVTotal * PANEL_H_DIV);
			#endif
		}
	}
	else
	#endif
	{
		#if DEBUG_PRINTDATA
		printData( " SrcHPeriod1111           :%d", SrcHPeriod );
		#endif
		hFreq = HFreq( SrcHPeriod );
		vFreq = VFreq( hFreq, SrcVTotal );
	}
	#if DEBUG_PRINTDATA
	printData( " hFreq           :%d", hFreq );
	printData( " vFreq           :%d", vFreq );
	#endif
	//======== for interlace mode
	#if ENABLE_FREESYNC
	if(SrcFlags & bInterlaceMode)
	{
		vFreq *= 2;
	}
	#else
	if( (SC0_READ_SYNC_STATUS()&INTM_B) //msReadByte( SC0_E1 ) &INTM_B
        #if ENABLE_DP_INPUT
	        || (CURRENT_INPUT_IS_DISPLAYPORT() && DP_INTERLACED_VIDEO_STREAM() ) //130909 nick add
        #endif
	  )
	{
		if(1)//(CURRENT_INPUT_IS_VGA())		//120703 Modify
		{
			BYTE count;
			for( count = 0; count < RECHECK_INTERLACE_COUNT; count++ )
			{
				if(!(CURRENT_INPUT_IS_DISPLAYPORT()))
				{
					if(!(SC0_READ_SYNC_STATUS()&INTM_B))
						break;
				}
				if(CURRENT_INPUT_IS_DISPLAYPORT())
				{
					if(!DP_INTERLACED_VIDEO_STREAM())
						break;
				}
				Delay1ms(20);
			}
			if(count >= RECHECK_INTERLACE_COUNT)
			{
				SrcFlags |= bInterlaceMode;
				vFreq *= 2;
			}
		}
		else
		{
			SrcFlags |= bInterlaceMode;
			vFreq *= 2;
		}
	}
	#endif
	SrcVFreq = vFreq;  //130909 nick add
	#if FindModeByVwidth
	SrcVsyncwidth = GetVSyncWidth();
	#endif
	#if DEBUG_PRINTDATA
	printData( " FindMode_hFreq:%d", hFreq );
	printData( " FindMode_vFreq:%d", vFreq );
	printData( " SrcHPeriod:%d", SrcHPeriod );
	printData( " SrcVTotal:%d", SrcVTotal );
	//printData("SrcVsyncwidth= %d", SrcVsyncwidth );
	#endif
	#if ENABLE_HDMI && ENABLE_HDMI_1_4
	#if 0//DEBUG_PRINTDATA
	if( mstar_HDMITmdsGetType() == TMDS_HDMI )
	{
		printData( " E_HDMI_3D_FORMAT:%x", (msReadByte(REG_0568) & 0xE0) );
		printData( " E_HDMI_3D_TYPE:%x", msHDMI_Get_3D_Structure() );
		printData( " HDMI_STATUS:%x", msRead2Byte( REG_0502 ) );
	}
	#endif
	if((msHDMI_Check_Additional_Format() == E_HDMI_3D_FORMAT) && (gScInfo.InputPacketStatus & BIT7))
	{
		bHDMI3DTimingFlag = 1;
		#if DEBUG_PRINTDATA
		printData( "bHDMI3DTimingFlag:%x", bHDMI3DTimingFlag);
		#endif
	}
	#endif
	//====================================
	#if ENABLE_FREESYNC
	if(!IS_HDMI_FREESYNC() && !IS_DP_FREESYNC())
	#endif
	{
		#if !ENABLE_DUAL_LINK
		// check if input timing is out of range
		if( hFreq > MaxInputHFreq || hFreq < MinInputHFreq || vFreq > MaxInputVFreq || vFreq < MinInputVFreq )
		{
			#if (ModelName==MODEL_HS245HFB)||(ModelName==MODEL_HS225HFB)
			if(vFreq < 400)
			{
			}
			else
			#endif
			{
				#if ENABLE_FREESYNC
				#else
				SrcFlags |= bUnsupportMode;
				#if DEBUG_MSG
				printData("hFreq %d", hFreq);
				printData("vFreq %d", vFreq);
				printMsg( "Input over freq--> not support" );
				#endif
				return TRUE;
				#endif
			}
		}
		#endif
	}
	htol = HFreq_Torlance; //0527 add for getting more accurate mode
	vtol = VFreq_Torlance;
	ucSimilarTimingNums = 0;
	SrcModeIndex = 0xFF;
	if(!CURRENT_INPUT_IS_VGA())//(SrcInputType >= Input_Digital)
	{
		bDigitalInput = 1;
		#if ENABLE_DP_INPUT     //111027 Rick modified - B39435
		if(CURRENT_INPUT_IS_DISPLAYPORT())//(SrcInputType == Input_Displayport)
		{
			tempWidth = (SC0_READ_AUTO_WIDTH() * 2);
			tempHeight = (SC0_READ_AUTO_HEIGHT());
		}
		else
		#endif
		{
			tempWidth = SC0_READ_AUTO_WIDTH();//msRead2Byte(SC0_84)-msRead2Byte(SC0_80)+1; // get DE width
			tempHeight = SC0_READ_AUTO_HEIGHT();//msRead2Byte(SC0_82)-msRead2Byte(SC0_7E)+1; // get DE Height
			#if ENABLE_HDMI // 120530 coding test
			// 130627 nick
			//if(CURRENT_SOURCE_IS_INTERLACE_MODE())
			{
				BYTE count;
				WORD wWidth = PIXEL_H_DE_COUNT(); // msRead2Byte(REG_14DC); msRead2Byte(REG_05CA);
				BYTE Width_Range;
				Width_Range = (PIXEL_H_DE_COUNT() - SC0_READ_AUTO_WIDTH());
				for(count = 0; count < RECHECK_INPUT_COUNT; count++)
				{
					if(wWidth == 1440 && (CURRENT_SOURCE_IS_INTERLACE_MODE())) // for 480i/576i
					{
						if(abs((wWidth / 2) - tempWidth) < DIGITAL_TOLERANCE)
							break;
					}
					else if(abs(wWidth - tempWidth) < DIGITAL_TOLERANCE)
					{
						#if DEBUG_PRINTDATA
						printData( "Width_Range:%d", Width_Range);
						#endif
						break;
					}
					hFreq = SC0_READ_HPEROID();
					if( abs( hFreq - SrcHPeriod ) > HPeriod_Torlance * 2 )      // HPeriod changed
					{
						hFreq = SC0_READ_HPEROID();
						if( abs( hFreq - SrcHPeriod ) > HPeriod_Torlance * 2 )      // HPeriod changed 130701 nick
						{
							#if DEBUG_PRINTDATA
							printData( "OverSrcHPeriod:%d", abs( hFreq - SrcHPeriod ));
							#endif
							return FALSE;
						}
					}
					Delay1ms(20);
					wWidth = PIXEL_H_DE_COUNT(); // msRead2Byte(REG_14DC); msRead2Byte(REG_05CA);
					tempWidth = SC0_READ_AUTO_WIDTH();
					tempHeight = SC0_READ_AUTO_HEIGHT();
				}
				#if DEBUG_PRINTDATA
				printData( " count:%d", count );
				#endif
				if(count >= RECHECK_INPUT_COUNT)
					Delay1ms( GetVSyncTime() * 8 );
			}
			#if DEBUG_PRINTDATA
			printData( " SC0_READ_AUTO_WIDTH:%d", SC0_READ_AUTO_WIDTH() );
			printData( " SC0_READ_AUTO_HEIGHT:%d", SC0_READ_AUTO_HEIGHT() );
			#endif
			#endif
		}
	}
	// search input mode index
	{
		Bool found = FALSE;
		BYTE ucModeIndex;
		BYTE ucHVtolerance_min = HFreq_Torlance + VFreq_Torlance;
		BYTE ucHVtolerance = HFreq_Torlance + VFreq_Torlance;
		BYTE ucVtotal_min = VTotal_Torlance;
		BYTE ucVtotal = VTotal_Torlance;
		InputModeType *modePtr = StandardMode;
		BYTE ucSimilarindex = 0;
		BYTE ucStartIndex = 0;
		#if ENABLE_HDMI && ENABLE_HDMI_1_4
		if(bHDMI3DTimingFlag)
		{
			ucStartIndex = HDMI_3D_TIMING_START_INDEX;
			modePtr += HDMI_3D_TIMING_START_INDEX;
		}
		#endif
		// get standard mode index
		for(ucModeIndex = ucStartIndex; modePtr->HFreq > 0; modePtr++, ucModeIndex++)
		{
			if(bDigitalInput)
			{
				if((abs(tempWidth - StandardModeResolution[modePtr->ResIndex].DispWidth) > DIGITAL_TOLERANCE) ||
				        (abs(tempHeight - StandardModeResolution[modePtr->ResIndex].DispHeight) > DIGITAL_TOLERANCE))
					continue;
			}
			if((CURRENT_SOURCE_IS_INTERLACE_MODE()) != (modePtr->Flags & bInterlaceMode))
				continue;
			if(SrcVTotal < StandardModeResolution[modePtr->ResIndex].DispHeight)
				continue;
			if((abs(hFreq - modePtr->HFreq) < HFreq_Torlance) &&
			        (abs(vFreq - modePtr->VFreq) < VFreq_Torlance) &&
			        (abs(SrcVTotal - modePtr->VTotal) < VTotal_Torlance) &&
			        (GetSyncPolarity( SrcFlags )&modePtr->Flags))
			{
				ucHVtolerance = abs(hFreq - modePtr->HFreq) + abs(vFreq - modePtr->VFreq);
				ucVtotal = abs(SrcVTotal - modePtr->VTotal);
				if((ucHVtolerance_min >= ucHVtolerance) && (ucVtotal_min >= ucVtotal))
				{
					found = TRUE;
					ucHVtolerance_min = ucHVtolerance;
					ucVtotal_min = ucVtotal;
					SrcModeIndex = ucModeIndex;
					ucSimilarTimingBuffer[ucSimilarindex] = ucModeIndex;
					ucSimilarTimingNums ++;
					ucSimilarindex = (ucSimilarindex + 1) % SIMILAR_TIMING_BUFFER_MAX;
				}
			}
		}
		#if DEBUG_PRINTDATA
		printData(" 8888888 SrcModeIndexFinal:%d", SrcModeIndex);
		#endif
		if( !found )
		{
			modePtr = StandardMode;
			ucHVtolerance_min = HFREQ_TOLERANCE_ENLARGE + VFREQ_TOLERANCE_ENLARGE;
			ucVtotal_min = VTotal_Delta;
			#if ENABLE_HDMI && ENABLE_HDMI_1_4
			if(bHDMI3DTimingFlag)
			{
				modePtr += HDMI_3D_TIMING_START_INDEX;
			}
			#endif
			for(ucModeIndex = ucStartIndex; modePtr->HFreq > 0; modePtr++, ucModeIndex++)
			{
				if(bDigitalInput)
				{
					if((abs(tempWidth - StandardModeResolution[modePtr->ResIndex].DispWidth) > DIGITAL_TOLERANCE) ||
					        (abs(tempHeight - StandardModeResolution[modePtr->ResIndex].DispHeight) > DIGITAL_TOLERANCE))
						continue;
				}
				if((CURRENT_SOURCE_IS_INTERLACE_MODE()) != (modePtr->Flags & bInterlaceMode))
					continue;
				if(SrcVTotal < StandardModeResolution[modePtr->ResIndex].DispHeight)
					continue;
				if((abs(hFreq - modePtr->HFreq) < HFREQ_TOLERANCE_ENLARGE) &&
				        (abs(vFreq - modePtr->VFreq) < VFREQ_TOLERANCE_ENLARGE) &&
				        (abs(SrcVTotal - modePtr->VTotal) < VTotal_Delta))
				{
					ucHVtolerance = abs(hFreq - modePtr->HFreq) + abs(vFreq - modePtr->VFreq);
					ucVtotal = abs(SrcVTotal - modePtr->VTotal);
					if((ucHVtolerance_min >= ucHVtolerance) && (ucVtotal_min >= ucVtotal))
					{
						found = TRUE;
						ucHVtolerance_min = ucHVtolerance;
						ucVtotal_min = ucVtotal;
						SrcModeIndex = ucModeIndex;
						ucSimilarTimingBuffer[ucSimilarindex] = ucModeIndex;
						ucSimilarTimingNums ++;
						ucSimilarindex = (ucSimilarindex + 1) % SIMILAR_TIMING_BUFFER_MAX;
					}
				}
			}
		}
		#if DEBUG_PRINTDATA
		printData(" 9999999  SrcModeIndexFinal:%d", SrcModeIndex);
		#endif
		if( !found )            // out of standard input range
		{
			modePtr = StandardMode;
			ucVtotal_min = VTotal_Delta;
			#if ENABLE_HDMI && ENABLE_HDMI_1_4
			if(bHDMI3DTimingFlag)
			{
				modePtr += HDMI_3D_TIMING_START_INDEX;
			}
			#endif
			for(ucModeIndex = ucStartIndex; modePtr->HFreq > 0; modePtr++, ucModeIndex++)
			{
				if((CURRENT_SOURCE_IS_INTERLACE_MODE()) != (modePtr->Flags & bInterlaceMode))
					continue;
				if(SrcVTotal < StandardModeResolution[modePtr->ResIndex].DispHeight)
					continue;
				if(abs(SrcVTotal - modePtr->VTotal) < VTotal_Delta)
				{
					ucVtotal = abs(SrcVTotal - modePtr->VTotal);
					if(ucVtotal_min > ucVtotal)
					{
						found = TRUE;
						SrcFlags |= bUserMode;
						ucVtotal_min = ucVtotal;
						SrcModeIndex = ucModeIndex;
						ucSimilarTimingBuffer[ucSimilarindex] = ucModeIndex;
						ucSimilarTimingNums ++;
						ucSimilarindex = (ucSimilarindex + 1) % SIMILAR_TIMING_BUFFER_MAX;
					}
				}
			}
		} // out of standard input range
		#if DEBUG_PRINTDATA
		printData(" 7777  SrcModeIndexFinal:%d", SrcModeIndex);
		#endif
		if(CURRENT_INPUT_IS_VGA())	//120420 Modify
			appCheckSimilarTiming();
		#if DEBUG_PRINTDATA
		printData( " 555555-----------666", 0 );
		#endif
//petit from anni.guan  20131017
		#ifndef  A_1400x1050_1680x1050
#define	A_1400x1050_1680x1050	 1
		#endif
		#if A_1400x1050_1680x1050
		if (SrcModeIndex == MODE_1440x900_60_VESA || SrcModeIndex == MODE_1600x900_60_VESA  )
		{
			if (SrcVTotal > 980)
				SrcModeIndex = MODE_1600x900_60_VESA;
			else
				SrcModeIndex = MODE_1440x900_60_VESA;
		}
		else if(SrcModeIndex == MODE_1440x900_60_VESA_RB || SrcModeIndex == MODE_1600x900_60_VESA_RB)
		{
			//printData("%d", GetVSyncWidth());
			if(GetVSyncWidth() > 5)
			{
				SrcModeIndex = MODE_1440x900_60_VESA_RB  ;
			}
			else
			{
				SrcModeIndex = MODE_1600x900_60_VESA_RB;
			}
		}
		#endif
		#if 0
		if(SrcModeIndex == MODE_1600x900_60_VESA_RB || SrcModeIndex == MODE_1280x960_72Hz_VESA)
		{
			if(SrcVTotal < 1001)
				SrcModeIndex = MODE_1600x900_60_VESA_RB;
			else
				SrcModeIndex = MODE_1280x960_72Hz_VESA;
		}
		#endif
		#if 1
		if (SrcModeIndex == MODE_1600x900_60_VESA_RB || SrcModeIndex == MODE_1280x960_60Hz_VESA1
	        #if A_1400x1050_1680x1050
		        || SrcModeIndex == MODE_1680x1050_60_VESA || SrcModeIndex == Mode_1400_1050_60_VESA
		        || SrcModeIndex == MODE_1680x1050_60_VESA_RB || SrcModeIndex == Mode_1400_1050_60_VESA_RB
		        || SrcModeIndex == MODE_1680x1050_75_VESA || SrcModeIndex == MODE_1400x1050_75_VESA
	        #endif
	        #if SHARP_VGA_50Hz_Timing
		        || SrcModeIndex == MODE_1680x1050_50 || SrcModeIndex == MODE_1400x1050_50
	        #endif
		   )   // 2017/2/7
		{
			BYTE i;
			WORD wVS, wVE;
			WORD SHS, SHE;
			#if 	A_1400x1050_1680x1050
			if(SrcModeIndex == MODE_1680x1050_60_VESA || SrcModeIndex == Mode_1400_1050_60_VESA)
			{
				//printData("%d", GetVSyncWidth());
				if(GetVSyncWidth() > 5)
				{
					SrcModeIndex = MODE_1680x1050_60_VESA  ;
				}
				else
				{
					SrcModeIndex = Mode_1400_1050_60_VESA;
				}
			}
			else if(SrcModeIndex == MODE_1680x1050_60_VESA_RB || SrcModeIndex == Mode_1400_1050_60_VESA_RB)
			{
				//printData("%d", GetVSyncWidth());
				if(GetVSyncWidth() > 5)
				{
					SrcModeIndex = MODE_1680x1050_60_VESA_RB  ;
				}
				else
				{
					SrcModeIndex = Mode_1400_1050_60_VESA_RB;
				}
			}
			else if(SrcModeIndex == MODE_1680x1050_75_VESA || SrcModeIndex == MODE_1400x1050_75_VESA)
			{
				//printData("%d", GetVSyncWidth());
				if(GetVSyncWidth() > 5)
				{
					SrcModeIndex = MODE_1680x1050_75_VESA  ;
				}
				else
				{
					SrcModeIndex = MODE_1400x1050_75_VESA;
				}
			}
			else
			#endif
			#if SHARP_VGA_50Hz_Timing
				if(SrcModeIndex == MODE_1680x1050_50 || SrcModeIndex == MODE_1400x1050_50)
				{
					//printData("%d", GetVSyncWidth());
					if(GetVSyncWidth() > 5)
					{
						SrcModeIndex = MODE_1680x1050_50  ;
					}
					else
					{
						SrcModeIndex = MODE_1400x1050_50;
					}
				}
				else
			#endif
					if(SrcModeIndex == MODE_1600x900_60_VESA_RB || SrcModeIndex == MODE_1280x960_60Hz_VESA1)
						for(i = 0; i < 10; i++)
						{
							Delay1ms(100);
							wVS = SC0_READ_AUTO_START_V();
							wVE = SC0_READ_AUTO_END_V();
							//Delay1ms(100);
							SHS = SC0_READ_AUTO_START_H();
							SHE = SC0_READ_AUTO_END_H();
							//HStarFram=
							if((wVS > wVE) || (SHS > SHE))
								continue;
							Delay1ms(50);
							if(abs(wVS - SC0_READ_AUTO_START_V()) > 2 || abs(wVE - SC0_READ_AUTO_END_V()) > 2)
								continue;
							if(abs(SHS - SC0_READ_AUTO_START_H()) > 2 || abs(SHE - SC0_READ_AUTO_END_H()) > 2)
								continue;
							if(((wVE - wVS) > 920) && ((SHE - SHS) < 1366))
							{
								SrcModeIndex = MODE_1280x960_60Hz_VESA1;
								break;
							}
							//#else
							if(((wVE - wVS) > 890) && ((wVE - wVS) < 910)) //899
							{
								SrcModeIndex = MODE_1600x900_60_VESA_RB;
								break;
							}
							else
							{
								//SrcModeIndex = PRESET_1280x960_60Hz_VESA;
								break;
							}
						}
		}
		#endif
		#if  SHARP_VGA_50Hz_Timing
		if(SrcModeIndex == MODE_1280x768_50 || SrcModeIndex == MODE_1024x768_50)
		{
			//printData("%d", GetVSyncWidth());
			if(GetVSyncWidth() > 5)
			{
				SrcModeIndex = MODE_1280x768_50 ;
			}
			else
			{
				SrcModeIndex = MODE_1024x768_50;
			}
		}
		#endif
		if (SrcModeIndex == MODE_1360x768_60_VGA || SrcModeIndex == MODE_1280X768_60Hz_VESA)
		{
			if (abs(SrcVTotal - 795) <= 2)
				SrcModeIndex = MODE_1360x768_60_VGA;
			else
				SrcModeIndex = MODE_1280X768_60Hz_VESA;
		}
		if(SrcModeIndex == MODE_1280x800_60Hz_VESA || SrcModeIndex == MODE_1280X768_60Hz_VESA_RB)
		{
			if(SrcVTotal < 812)
				SrcModeIndex = MODE_1280X768_60Hz_VESA_RB;
			else
				SrcModeIndex = MODE_1280x800_60Hz_VESA;
		}
		if( !found && (CURRENT_INPUT_IS_VGA()))
		{
			#if DEBUG_MSG
			printMsg( "Not Found--> not support" );
			#endif
			SrcFlags |= bUnsupportMode;
		}
		else   // found
		{
			#if ENABLE_DEBUG
			printData("  ucSimilarTimingNums:%d", ucSimilarTimingNums);
			printData("  SrcModeIndex:%d", SrcModeIndex);
			printData("  SrcVTotal:%d", SrcVTotal);
			printData("  StandardModeWidth:%d", StandardModeWidth);
			printData("  StandardModeHeight:%d", StandardModeHeight);
			printData("  MODE_Max:%d", MODE_Max);
			#endif
		}
	} // search mode index
	return TRUE;
}
#endif

