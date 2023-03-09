
#define DoubleXSize 0
#define DoubleYSize 0

#if CHIP_ID>=CHIP_TSUMV
#define CP_COLORKEY_T    1
#define CP_COLORKEY_F    0
#else
#define CP_COLORKEY_T
#define CP_COLORKEY_F
#endif

//OSD_WIN0 for PG
#define OSD_MAIN_WND        OSD_WIN1
#define OSD_MAIN_WIN_BIT    OSD_GD_WIN1_EN_BIT
#define OSD_BUTTON_WND      OSD_WIN2
#define OSD_CURSOR_WND      OSD_WIN3
#define OSD_CURSOR_WIN_BIT  OSD_GD_WIN3_EN_BIT
#define OSD_ICON_WND        OSD_WIN4
#define OSD_ICON_WIN_BIT    OSD_GD_WIN4_EN_BIT

#define OSD_MAIN_WND_CA_BASE    0x0001

#define OSD_MAIN_WND_SIZE       1728//(20+20+24)*27

#define OSD_BUTTON_WND_CA_BASE  (OSD_MAIN_WND_CA_BASE+OSD_MAIN_WND_SIZE)
#define OSD_BUTTON_WND_SIZE     60//
#define OSD_CURSOR_WND_CA_BASE  (OSD_BUTTON_WND_CA_BASE+OSD_BUTTON_WND_SIZE)
#define OSD_CURSOR_WND_SIZE     60//

#if CHIP_ID==CHIP_TSUMV

extern BYTE xdata g_u8OsdWndNo;
extern BYTE xdata g_u8FontAddrHiBits;
//extern WORD xdata g_u16OsdWndCABase[];

#define OSD_SET_WND(u8Wnd)  (g_u8OsdWndNo=u8Wnd)
#define OSD_ENABLE_GRADIENT_COLOR()     //msWriteByteMask(OSD1_15, BIT3, BIT3)
#define OSD_DISABLE_GRADIENT_COLOR()    //msWriteByteMask(OSD1_15,    0, BIT3)

//Font RAM bit8/bit9
#define OSD_FONT_HI_ADDR_SET_BIT8()     (g_u8FontAddrHiBits=BIT0) //msWriteByteMask(OSD2_AE, BIT7, BIT7|BIT6); //enable bit 8
#define OSD_FONT_HI_ADDR_SET_BIT9()     (g_u8FontAddrHiBits=BIT1) //msWriteByteMask(OSD2_AE, BIT6, BIT7|BIT6); //enable bit 9
#define OSD_FONT_HI_ADDR_CLR_TO_0()     (g_u8FontAddrHiBits=0) //msWriteByteMask(OSD2_AE,    0, BIT7|BIT6);

#define OSD_FONT_START_ENTRY        0x1D4   //464(0x1D0) + 2160 entries= 2088 c/a + 720 fonts
#define OSD_FONT_UNIT_SIZE          3       //12x18 font, 1.5x18 = 27 Bytes = 3 x 72 bits = 3 entries
#define GET_FONT_RAM_ADDR(u8Addr)   ((OSD_FONT_START_ENTRY+((((WORD)g_u8FontAddrHiBits)<<8)+(u8Addr))*OSD_FONT_UNIT_SIZE)<<2)


typedef struct
{
	BYTE bButtonOsd: 1;
	BYTE bSync2Main: 1;
} WrapLayerFlagType;

#elif CHIP_ID==CHIP_TSUM2

extern BYTE xdata g_u8OsdWndNo;
extern BYTE xdata g_u8FontAddrHiBits;
//extern WORD xdata g_u16OsdWndCABase[];
extern BYTE xdata g_u8OsdFontDataHighByte;
#define OSD_SET_WND(u8Wnd)  (g_u8OsdWndNo=u8Wnd)
#define OSD_ENABLE_GRADIENT_COLOR()     //msWriteByteMask(OSD1_15, BIT3, BIT3)
#define OSD_DISABLE_GRADIENT_COLOR()    //msWriteByteMask(OSD1_15,    0, BIT3)

//Font RAM bit8/bit9
#define OSD_FONT_HI_ADDR_SET_BIT8()     (g_u8FontAddrHiBits=BIT0) //msWriteByteMask(OSD2_AE, BIT7, BIT7|BIT6); //enable bit 8
#define OSD_FONT_HI_ADDR_SET_BIT9()     (g_u8FontAddrHiBits=BIT1) //msWriteByteMask(OSD2_AE, BIT6, BIT7|BIT6); //enable bit 9
#define OSD_FONT_HI_ADDR_CLR_TO_0()     (g_u8FontAddrHiBits=0) //msWriteByteMask(OSD2_AE,    0, BIT7|BIT6);

#define OSD_FONT_START_ENTRY        0x1D4   //464(0x1D0) + 2160 entries= 2088 c/a + 720 fonts
#define OSD_FONT_UNIT_SIZE          3       //12x18 font, 1.5x18 = 27 Bytes = 3 x 72 bits = 3 entries
#define GET_FONT_RAM_ADDR(u8Addr)   ((OSD_FONT_START_ENTRY+((((WORD)g_u8FontAddrHiBits)<<8)+(u8Addr))*OSD_FONT_UNIT_SIZE)<<2)


typedef struct
{
	BYTE bButtonOsd: 1;
	BYTE bSync2Main: 1;
} WrapLayerFlagType;

#elif CHIP_ID==CHIP_TSUMC || CHIP_ID==CHIP_TSUMD || CHIP_ID==CHIP_TSUM9 ||CHIP_ID == CHIP_TSUMF
extern BYTE xdata g_u8OsdWndNo;
extern BYTE xdata g_u8FontAddrHiBits;
//extern WORD xdata g_u16OsdWndCABase[];
extern BYTE xdata g_u8OsdFontDataHighByte;
#define OSD_SET_WND(u8Wnd)  (g_u8OsdWndNo=u8Wnd)
#define OSD_ENABLE_GRADIENT_COLOR()     //msWriteByteMask(OSD1_15, BIT3, BIT3)
#define OSD_DISABLE_GRADIENT_COLOR()    //msWriteByteMask(OSD1_15,    0, BIT3)

//Font RAM bit8/bit9
#define OSD_FONT_HI_ADDR_SET_BIT8()     (g_u8FontAddrHiBits=BIT0) //msWriteByteMask(OSD2_AE, BIT7, BIT7|BIT6); //enable bit 8
#define OSD_FONT_HI_ADDR_SET_BIT9()     (g_u8FontAddrHiBits=BIT1) //msWriteByteMask(OSD2_AE, BIT6, BIT7|BIT6); //enable bit 9
#define OSD_FONT_HI_ADDR_CLR_TO_0()     (g_u8FontAddrHiBits=0) //msWriteByteMask(OSD2_AE,    0, BIT7|BIT6);

#define OSD_FONT_START_ENTRY        0x1D4   //464(0x1D0) + 2160 entries= 2088 c/a + 720 fonts
#define OSD_FONT_UNIT_SIZE          3       //12x18 font, 1.5x18 = 27 Bytes = 3 x 72 bits = 3 entries
#define GET_FONT_RAM_ADDR(u8Addr)   ((OSD_FONT_START_ENTRY+((((WORD)g_u8FontAddrHiBits)<<8)+(u8Addr))*OSD_FONT_UNIT_SIZE)<<2)

typedef struct
{
	BYTE bButtonOsd: 1;
	BYTE bSync2Main: 1;
} WrapLayerFlagType;

#else
#define GET_FONT_RAM_ADDR(u8Addr)		(u8Addr)
#define OSD_FONT_HI_ADDR_SET_BIT8()     msWriteByteMask(OSD2_AE, BIT7, BIT7|BIT6); //enable bit 8
#define OSD_FONT_HI_ADDR_SET_BIT9()     msWriteByteMask(OSD2_AE, BIT6, BIT7|BIT6); //enable bit 9
#define OSD_FONT_HI_ADDR_SET_BIT10()     msWriteByteMask(OSD2_AE, BIT6|BIT7, BIT7|BIT6) //enable bit 9
#define OSD_FONT_HI_ADDR_CLR_TO_0()     msWriteByteMask(OSD2_AE,    0, BIT7|BIT6);
#endif

typedef struct
{
	BYTE u8Red;
	BYTE u8Green;
	BYTE u8Blue;
	#if CHIP_ID>=CHIP_TSUMV
	BYTE u8ColorKey;
	#endif
} ColorPaletteType;

extern  BYTE OsdWindowWidth;
extern  BYTE OsdWindowHeight;
//extern void Osd_SetOsdEngine(BYTE ucValue);
//extern void msWriteByte( WORD u16Reg, BYTE u8Val );
extern void Osd_DrawNum(BYTE xPos, BYTE yPos, int value);
extern void Osd_Draw4Num(BYTE xPos, BYTE yPos, int value);
extern void Osd_DrawStr(BYTE xPos, BYTE yPos, BYTE *str);
extern void Osd_DrawHex(BYTE xPos, BYTE yPos, WORD value);
//extern void Osd_SetPosition(BYTE xPos, BYTE yPos);
//extern void Osd_SetWindowSize(BYTE width, BYTE height);
//extern void Osd_SetTextColor(BYTE foreColor, BYTE backColor);
//extern void Osd_DrawChar(BYTE xPos, BYTE yPos, BYTE ch);
extern void Osd_DrawGuage(BYTE xPos, BYTE yPos, BYTE length, BYTE value);
//extern void Osd_Show(void);
//extern void Osd_Hide(void);
extern void Osd_InitOSD(void);
//extern void Osd_DrawPropStr(BYTE xPos, BYTE yPos, BYTE *str);
//extern void DisableOsdWindow(BYTE winIndex);
//extern void MoveOsdWindow(BYTE winIndex, BYTE YPos, BYTE xPosStar, BYTE Xlength, BYTE Ylength, BYTE FgColor, BYTE BgColor);
//extern void Osd_DrawRealStr(BYTE xPos, BYTE yPos, BYTE *str);
//extern void Osd_DrawCharDirect(BYTE xPos, BYTE yPos, BYTE ch);
//extern void Osd_DrawContinuesChar(BYTE xPos, BYTE yPos, BYTE ch, BYTE ucNum);
//extern void Osd_LoadLogoFontCP(void);
extern void LoadCommonFont(void);
//extern void Osd_LoadFacoryFontCP(void);
#if 0
extern void Osd_SetText4Color(color);
extern void Osd_SetText8Color(color);
#else
//extern void Osd_Set256TextColor(BYTE foreColor, BYTE backColor);
#endif
//extern void Osd_DrawPropStr(BYTE xPos, BYTE yPos, BYTE *str);
//extern void Osd_SetTextMonoColor(BYTE foreColor, BYTE backColor);
//extern void Osd_DrawMainIcon(BYTE itemIndex, BYTE xpos, BYTE ypos, BYTE selected);
//extern void Osd_SetTransparence(BYTE value);
//extern void LoadMainSmallLogoFont(void);

//extern void SetOsdSubWindow( BYTE Win_Num, BYTE HStar, BYTE HEnd , BYTE VStar, BYTE VEnd, BYTE Color );
//extern void DisableOsdSubWindow( BYTE Win_Num );
//extern void SetOsdGraduallyBackGround( BYTE Win_Num, BYTE GDRValue, BYTE GDGValue, BYTE GDBValue, BYTE GDDelta , BYTE GDDERange, BYTE GDControl, BYTE GDRInit , BYTE GDGInit, BYTE GDBInit);
//extern BYTE Osd_DoubleBuffer(Bool u8Enable);
//extern void SetOSDWindosw(BYTE ucSubWin,BYTE u8HStart,BYTE u8HEnd ,BYTE u8VStart, BYTE u8VEnd,BYTE u8Color);
//extern void ClrOSDWindosw(BYTE ucSubWin);
//extern void Osd_HVPositionWindowAtr(BYTE u8Win_Num,BYTE u8HStart,BYTE u8HEnd ,BYTE u8VStart, BYTE u8VEnd);

extern void Osd_DrawCharDirect(BYTE xPos, BYTE yPos, BYTE ch);
extern void Osd_DrawContinuesChar(BYTE xPos, BYTE yPos, BYTE ch, BYTE ucNum);
extern void Osd_DrawPropStr(BYTE xPos, BYTE yPos, BYTE *str);
extern void Osd_DrawRealStr(BYTE xPos, BYTE yPos, BYTE *str);
#if CHIP_ID < CHIP_TSUMV
extern void Load256ColorPalette(BYTE u8Group, BYTE u8Addr, ColorPaletteType *colorPtr, WORD u16Num);
#endif


#if OsdHelpKeyType ==	 OsdHelpKey_Under || OsdHelpKeyType ==	 OsdHelpKey_Right
extern void UpdataHelyKeyShowInMenu(void);
#endif