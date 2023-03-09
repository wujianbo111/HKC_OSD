#include <stdlib.h>
#include "types.h"
#include "ms_reg.h"
#include "panel.h"
#include "Board.h"
#include "debug.h"
#include "ms_rwreg.h"
#include "mstar.h"
#include "misc.h"
#include "global.h"
#include "menudef.h"
#include "drvosd.h"
#include "msOSD.h"
#include "msOSDFunction.h"
#include "font.h"
#include "extlib.h"
#include "MsID_V1.h"
#include "CommonLoadCPnCompressFont.h"




#if CHIP_ID>=CHIP_TSUM2
BYTE xdata g_u8OsdWndNo = OSD_MAIN_WND;
BYTE xdata g_u8FontAddrHiBits = 0;
BYTE xdata g_u8OsdFontDataHighByte = 0;
#elif CHIP_ID==CHIP_TSUMV
BYTE xdata g_u8OsdWndNo = OSD_MAIN_WND;
BYTE xdata g_u8FontAddrHiBits = 0;
#else
BYTE xdata g_u8FontAddrHiBits = 0;
#endif




#if DoubleXSize
#define DOUBLE_RATIO_X  2
#else
#define DOUBLE_RATIO_X  1
#endif
#if DoubleYSize
#define DOUBLE_RATIO_Y  2
#else
#define DOUBLE_RATIO_Y  1
#endif
#define Color8FontRAMStart   0xA2 //0xA2//0x7d // 100
//==================================================================================
// Local function declaration
//
//void Osd_SetWindowSize(BYTE width, BYTE height);
//void Osd_SetPosition(BYTE xPos, BYTE yPos);
//void Osd_DrawChar(BYTE xPos, BYTE yPos, BYTE ch);
//#if CHIP_ID>=CHIP_TSUMV
//void Load256ColorPalette(BYTE u8Group, BYTE u8Addr, ColorPaletteType *colorPtr, WORD u16Num);
//#else
//void Load256ColorPalette(BYTE u8Group, BYTE u8Addr, ColorPaletteType *colorPtr, WORD u16Num);
//#endif
void LoadCommonFont(void);
//void Osd_LoadLogoFontCP(void);
extern void mStar_WaitForDataBlanking(void);
extern void LoadLanguageStatusPropfont( void );

void msOSDuncall(void);

//==================================================================================
// variable declaration
//
BYTE OsdWindowWidth = 10;
BYTE OsdWindowHeight = 10;
xdata BYTE OsdFontColor = 0x01;
extern  BYTE  xdata MenuPageIndex;
extern  BYTE  xdata MenuItemIndex;
extern  BYTE  xdata PrevPage;

BYTE xdata OsdEngStatus = 0;
//==================================================================================

void Osd_InitOSD(void)
{
	BYTE u8Retry = 10;
	if(!u8Retry)
	{
		drvOSD_uncall();
		msOSDuncall();
	}
	#if CHIP_ID>=CHIP_TSUMV
	msWriteByte(OSD1_00, 0x00); //Set to OSD1 BK0
	while (u8Retry--)
	{
		msWriteByteMask(OSD1_65, BIT1, BIT1);		//clear cafsram
		ForceDelay1ms(3);
		if (!(msReadByte(OSD1_65)&BIT1))
			break;
	}
	msWriteByteMask(OSD1_03, BIT2, BIT2); 	  //OSD wr priority is over display for both cafsram/psram
	msWrite2Byte(OSD1_04, PANEL_WIDTH); 		//set osd h range size
	msWrite2Byte(OSD1_06, PANEL_HEIGHT);		//set osd v range size
	msWriteByteMask(OSD1_02, BIT1, BIT1);		 //force blending
	//Init cafsram
	msWrite2Byte(OSD1_08, OSD_FONT_START_ENTRY);			   //set font data entry base,
	msWriteByteMask(OSD1_0B, (OSD_FONT_UNIT_SIZE - 1) << 4, BIT4 | BIT5); //Set unit size to 3 entries, [5:4] value+1 entries
	drvOSD_SetWndCABaseAddr(OSD_WIN0, 0x0000);
	drvOSD_SetWndShiftPixel(OSD_WIN0, 0, 0);	//avoid compiler warning
	drvOSD_SetWndFixColor(OSD_WIN0, 0, 0, 0);	//avoid compiler warning
	//init OSD_MAIN_WND
	drvOSD_SetWndCtrl(OSD_MAIN_WND, OSD_WND_CTRL0,
	                  (OWC0_FP_MODE |
	                   OWC0_GROUP_SEL0 |
	                   OWC0_LV1_ALPHA_SRC(OSD_A_FIX) |
	                   OWC0_LV2_ALPHA_SRC(OSD_A_FIX) |
	                   OWC0_OUT_ALPHA_SRC(OSD_A_FIX)),
	                  OWC0MASK_ALL);
	drvOSD_SetWndCtrl(OSD_MAIN_WND, OSD_WND_CTRL1,
	                  (OWC1_1BP_44MODE_EN |
	                   OWC1_44MODE_TRS_EN |
	                   OWC1_FONT_HEIGHT(18)),
	                  OWC1MASK_ALL);
	drvOSD_SetWndCtrl(OSD_MAIN_WND, OSD_WND_CTRL2,
	                  (OWC2_GD_COLOR_R(OSD_GD_EG4) |
	                   OWC2_GD_COLOR_G(OSD_GD_EG4) |
	                   OWC2_GD_COLOR_B(OSD_GD_EG4)),
	                  OWC2MASK_ALL);
	drvOSD_SetWndCtrl(OSD_MAIN_WND, OSD_WND_CTRL3,
	                  (OWC3_1BPP_ATTR_BIT1/*|OWC3_LV1_KM_SWITCH|OWC3MASK_CKEY_INV*/),
	                  OWC3MASK_ALL);
	drvOSD_SetWndFixAlpha(OSD_MAIN_WND, OSD_ALPHA_LV2, 0x00); //PG   //(1-a)*low_lvl+a*top_lvl
	drvOSD_SetWndFixAlpha(OSD_MAIN_WND, OSD_ALPHA_LV1, 0x10); //FG
	drvOSD_SetWndFixAlpha(OSD_MAIN_WND, OSD_ALPHA_OUT, 0x3F); //OSD
	drvOSD_SetWndCABaseAddr(OSD_MAIN_WND, OSD_MAIN_WND_CA_BASE);
	//init OSD_BUTTON_WND
	drvOSD_SetWndCtrl(OSD_BUTTON_WND, OSD_WND_CTRL0,
	                  (OWC0_FP_MODE |
	                   OWC0_GROUP_SEL0 |
	                   OWC0_LV1_ALPHA_SRC(OSD_A_FIX) |
	                   OWC0_LV2_ALPHA_SRC(OSD_A_FIX) |
	                   OWC0_OUT_ALPHA_SRC(OSD_A_FIX)),
	                  OWC0MASK_ALL);
	drvOSD_SetWndCtrl(OSD_BUTTON_WND, OSD_WND_CTRL1,
	                  (OWC1_1BP_44MODE_EN |
	                   OWC1_44MODE_TRS_EN |
	                   OWC1_FONT_HEIGHT(18)),
	                  OWC1MASK_ALL);
	drvOSD_SetWndCtrl(OSD_BUTTON_WND, OSD_WND_CTRL2,
	                  (OWC2_GD_COLOR_R(OSD_COLOR_FIX) |
	                   OWC2_GD_COLOR_G(OSD_COLOR_FIX) |
	                   OWC2_GD_COLOR_B(OSD_COLOR_FIX)),
	                  OWC2MASK_ALL);
	drvOSD_SetWndCtrl(OSD_BUTTON_WND, OSD_WND_CTRL3,
	                  (OWC3_LV1_KM_SWITCH | OWC3MASK_CKEY_INV),
	                  OWC3MASK_ALL);
	drvOSD_SetWndFixAlpha(OSD_BUTTON_WND, OSD_ALPHA_LV2, 0x00); //PG	 //(1-a)*low_lvl+a*top_lvl
	drvOSD_SetWndFixAlpha(OSD_BUTTON_WND, OSD_ALPHA_LV1, 0x3F); //FG
	drvOSD_SetWndFixAlpha(OSD_BUTTON_WND, OSD_ALPHA_OUT, 0x3F); //OSD
	drvOSD_SetWndCABaseAddr(OSD_BUTTON_WND, OSD_BUTTON_WND_CA_BASE);
	//init OSD_CURSOR_WND
	drvOSD_SetWndCtrl(OSD_CURSOR_WND, OSD_WND_CTRL0,
	                  (OWC0_FP_MODE |
	                   OWC0_GROUP_SEL0 |
	                   //OWC0_GROUP_SEL1|
	                   OWC0_LV1_ALPHA_SRC(OSD_A_FIX) |
	                   OWC0_LV2_ALPHA_SRC(OSD_A_FIX) |
	                   OWC0_OUT_ALPHA_SRC(OSD_A_FIX)),
	                  OWC0MASK_ALL);
	drvOSD_SetWndCtrl(OSD_CURSOR_WND, OSD_WND_CTRL1,
	                  (OWC1_1BP_44MODE_EN |
	                   OWC1_44MODE_TRS_EN |
	                   OWC1_FONT_HEIGHT(18)),
	                  OWC1MASK_ALL);
	drvOSD_SetWndCtrl(OSD_CURSOR_WND, OSD_WND_CTRL2,
	                  (OWC2_GD_COLOR_R(OSD_GD_EG3) |
	                   OWC2_GD_COLOR_G(OSD_GD_EG3) |
	                   OWC2_GD_COLOR_B(OSD_GD_EG3)),
	                  OWC2MASK_ALL);
	drvOSD_SetWndCtrl(OSD_CURSOR_WND, OSD_WND_CTRL3,
	                  (OWC3_1BPP_ATTR_BIT1 | OWC3_LV1_KM_SWITCH | OWC3MASK_CKEY_INV),
	                  OWC3MASK_ALL);
	drvOSD_SetWndFixAlpha(OSD_CURSOR_WND, OSD_ALPHA_LV2, 0x00); //PG   //(1-a)*low_lvl+a*top_lvl
	drvOSD_SetWndFixAlpha(OSD_CURSOR_WND, OSD_ALPHA_LV1, 0x10); //PG
	drvOSD_SetWndFixAlpha(OSD_CURSOR_WND, OSD_ALPHA_OUT, 0x3F); //OSD
	drvOSD_SetWndCABaseAddr(OSD_CURSOR_WND, OSD_CURSOR_WND_CA_BASE);
	#if CHIP_ID >= CHIP_TSUM2
	drvOSD_SetGDEngineEnableWnd();
	#elif CHIP_ID == CHIP_TSUMV
	drvOSD_SetGDEngineEnableWnd(OSD_GD_EG3, OSD_CURSOR_WIN_BIT, OSD_CURSOR_WIN_BIT);
	drvOSD_SetGDEngineEnableWnd(OSD_GD_EG4, OSD_MAIN_WIN_BIT, OSD_MAIN_WIN_BIT);
	#endif
	OSD_SET_WND(OSD_MAIN_WND);
	#else
	{
		BYTE retry = 10;
		while( retry-- )
		{
			msWriteByte( OSD2_A0, BIT6 );
			Delay1ms( 3 );
			if( !( msReadByte( OSD2_A0 )&BIT6 ) )
				break;
		}
	}
	//msWriteByte( BLENDC, 0 ); //111102 Rick modified cal pipedelay condition - B39842
	//msWriteByte( BLENDL, 0 );
	#if CHIP_ID==CHIP_TSUMB
	msWriteByte( OSD2_4B, 0x83 );//color key mode
	#else
	msWriteByte( OSD2_4B, 0x07 );//color key mode
	#endif
	mStar_WriteOSDByte( OSD1_3D, 0x00 );//color key
	mStar_WriteOSDByte( OSD1_3E, 0x08 );//color key
	mStar_WriteOSDByte( OSD1_3F, 0x80 );//color key
	msWriteByte( OSD1_10, 0x80 );
	msWriteByte( OSDDBC, 0x5 ); // enable double
	msWriteByte( OCBUFO, 0x00 ); // disable OSD code buffer Base/Offset address
	msWriteByte( IOSDC3, 0x00 ); //0x0F); // shadow function control
	msWriteByte( OSDHC, 0x11 ); // shadow width control
	Osd_SetWindowSize( 20, 10 ); // set osd window
	msWriteByte( IOSDC2, 0x00 ); // color bit setting
	msWriteByte( OSD1_70, BIT4 | BIT2 ); // [4]: set osd move step by 1 pixel; [2] add 9 pixels
	Osd_SetPosition(0, 100); // set osd position
	#endif
	LoadCommonFont(); //eshin
	//Osd_SetPosition(50, 50); // set osd position
}

void Osd_Load8ColorFont(BYTE u8Addr, BYTE *pu8Font, WORD u16Num)
{
	#if CHIP_ID>=CHIP_TSUMV
	DWORD xdata u32Data;
	BYTE xdata u8FontData0, u8FontData1, u8FontData2;
	BYTE xdata u8PixelBit;
	BYTE xdata i;
	#if CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD||CHIP_ID == CHIP_TSUM9 ||CHIP_ID == CHIP_TSUMF
	msWriteByteMask(OSD1_6D, BIT6, BIT7 | BIT6); //00: for 1/2Bpp; 01: for 3Bpp; 10:for 4Bpp;
	#elif  CHIP_ID==CHIP_TSUM2||CHIP_ID==CHIP_TSUMV
	msWriteByteMask(OSD1_6D, 0x00, BIT7); //0: for 1/2/3Bpp; 1: for 4Bpp;
	#endif
	WRITE_CAFSRAM_ADDR();
	msWrite2Byte(PORT_FONT_ADDR, GET_FONT_RAM_ADDR(u8Addr));
	WRITE_FONT();
	// handle 2 lines, 8 pixels each time, 2 lines x 12 pixels = 8 pixels x 3 times
	while(u16Num)
	{
		for (i = 0; i < 3; i++)
		{
			//    0        1        2        3        4        5        6        7        8
			//11110000 00000000 11111111 00002222 22222222 00000000 22221111 11111111 22222222 //line 0/1
			if (i == 0)
			{
				u8FontData0 = ((*(pu8Font)) << 4) + ((*(pu8Font + 1)) >> 4);
				u8FontData1 = ((*(pu8Font)) & 0xF0) + ((*(pu8Font + 2)) >> 4);
				u8FontData2 = ((*(pu8Font + 3)) << 4) + ((*(pu8Font + 4)) >> 4);
			}
			else if (i == 1)
			{
				u8FontData0 = ((*(pu8Font + 1)) << 4) + ((*(pu8Font + 3)) >> 4);
				u8FontData1 = ((*(pu8Font + 2)) << 4) + ((*(pu8Font + 6)) & 0x0F);
				u8FontData2 = ((*(pu8Font + 4)) << 4) + ((*(pu8Font + 6)) >> 4);
			}
			else
			{
				u8FontData0 = (*(pu8Font + 5));
				u8FontData1 = (*(pu8Font + 7));
				u8FontData2 = (*(pu8Font + 8));
			}
			u8PixelBit = BIT7;
			u32Data = 0;
			while(u8PixelBit)
			{
				u32Data <<= 3;
				if (u8FontData0 & u8PixelBit) //color bit0
					u32Data |= BIT0;
				if (u8FontData1 & u8PixelBit) //color bit1
					u32Data |= BIT1;
				if (u8FontData2 & u8PixelBit) //color bit2
					u32Data |= BIT2;
				u8PixelBit >>= 1;
			}
			msWriteByte(PORT_FONT_DATA, u32Data >> 16);
			msWriteByte(PORT_FONT_DATA, u32Data >> 8);
			msWriteByte(PORT_FONT_DATA, u32Data);
		}
		if (u16Num >= 9)
		{
			u16Num -= 9;
			pu8Font += 9;
		}
		else
			u16Num = 0;
	}
	#if CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD||CHIP_ID == CHIP_TSUM9 ||CHIP_ID == CHIP_TSUMF
	msWriteByteMask(OSD1_6D, 0x00, BIT7 | BIT6); //00: for 1/2Bpp; 01: for 3Bpp; 10:for 4Bpp;
	#elif  CHIP_ID==CHIP_TSUM2||CHIP_ID==CHIP_TSUMV
	msWriteByteMask(OSD1_6D, 0x00, BIT7);  		 //0: for 1/2/3Bpp; 1: for 4Bpp;
	#endif
	#else
	msWriteByte(OSD2_A3, u8Addr);
	while (u16Num--)
		msWriteByte(OSD2_A4, *(pu8Font++));
	#endif
}

#if 0
void Osd_SetTextMonoColor(BYTE foreColor, BYTE backColor)
{
	OsdFontColor = (foreColor & 0xF) << 4 | (backColor & 0xF);
}
void Osd_SetTextColor(BYTE foreColor, BYTE backColor)
{
	// OsdFontColor=(foreColor&0xF)<<4|(backColor&0xF);
	OsdFontColor = (foreColor & 0x0) | (backColor & 0xFF);
}
void Osd_Set256TextColor(BYTE foreColor, BYTE backColor)
{
	if(backColor == Color_2)
		OsdFontColor = foreColor;
	else if(backColor == Color_2G)
	{
		#if CHIP_ID>=CHIP_TSUMV
		OsdFontColor = (foreColor & 0xF0) | 0x01;
		#else
		OsdFontColor = foreColor;
		#endif
	}
	else if(backColor == Color_4)
		OsdFontColor = foreColor << 2;
	else if(backColor == Color_8)
		OsdFontColor = foreColor << 3;
	else if(backColor == Color_8G)
		OsdFontColor = (foreColor << 3) | BIT1;
	else if(backColor == Color_2T)
		OsdFontColor = foreColor | 0x00;
	else if(backColor == Color_4T)
		OsdFontColor = foreColor << 2 | 0x01;
	else// (backColor==Color_8T)
		OsdFontColor = foreColor << 3 | 0x01;
}
#endif

void DrawNum(BYTE xPos, BYTE yPos, char len, int value) //int value)
{
	char _minus = 0;
	BYTE ZeroStart;
	if( MenuPageIndex == FactoryMenu )
	{
		ZeroStart = 0x30;
	}
	else
	{
		ZeroStart = MonoNumberStart;
	}
	if( value < 0 )
	{
		value = 0 - value;
		_minus = 1;
	}
	if( value == 0 )
	{
		Osd_DrawCharDirect( xPos + ( len-- ), yPos, ( BYTE )( value + ZeroStart ) );
	}
	else
	{
		while( value && len )            // translate integer to string
		{
			Osd_DrawCharDirect( xPos + ( len-- ), yPos, ( BYTE )(( value % 10 ) + ZeroStart ) );
			value /= 10;
		}
	}
	if( _minus && len >= 0 )            // add sign
	{
		Osd_DrawCharDirect( xPos + ( len-- ), yPos, ( BYTE )'-' );
	}
	_minus = ( _minus ) ? ( 0 ) : ( 1 );
	for( ; _minus <= len; _minus++ )
	{
		Osd_DrawCharDirect( xPos + _minus, yPos, ( BYTE )MonoSpace );
	}
}

void Osd_DrawNum(BYTE xPos, BYTE yPos, int value)
{
	DrawNum(xPos, yPos, 3, value);
}

#if DDCCI_ENABLE_DEBUG	//130806 henry
void Osd_Draw4Num(BYTE xPos, BYTE yPos, int value)
{
	DrawNum(xPos, yPos, 5, value);
}
#endif
//===================================================================================
#define GuageFontStart_Normal	(MonoGuageFontStar+0x00)
#define GuageFontEnd_Normal		(MonoGuageFontStar+0x12)

#define GuageFont0_6	(MonoGuageFontStar+0x06)
#define GuageFont1_6	(MonoGuageFontStar+0x07)
#define GuageFont2_6	(MonoGuageFontStar+0x08)
#define GuageFont3_6	(MonoGuageFontStar+0x09)
#define GuageFont4_6	(MonoGuageFontStar+0x0A)
#define GuageFont5_6	(MonoGuageFontStar+0x0B)
#define GuageFont6_6	(MonoGuageFontStar+0x0C)
#define GuageFont6_full	(MonoGuageFontStar+0x0C)

#define GuageLevel		6
void Osd_DrawGuage(BYTE xPos, BYTE yPos, BYTE length, BYTE value)
{
	BYTE pLead;
	BYTE ucLoop;
	if (value > 100)
		value = 100;
	OSD_TEXT_HI_ADDR_SET_BIT8(); //enable bit 8
	if (value >= 95)
	{
		if (value == 100)
			Osd_DrawCharDirect(xPos + length - 1, yPos, (GuageFontEnd_Normal - 5));
		else if (value == 99)
			Osd_DrawCharDirect(xPos + length - 1, yPos, (GuageFontEnd_Normal - 4));
		else if (value == 98)
			Osd_DrawCharDirect(xPos + length - 1, yPos, (GuageFontEnd_Normal - 3));
		else if (value == 97)
			Osd_DrawCharDirect(xPos + length - 1, yPos, (GuageFontEnd_Normal - 2));
		else if (value == 96)
			Osd_DrawCharDirect(xPos + length - 1, yPos, (GuageFontEnd_Normal - 1));
		else
			Osd_DrawCharDirect(xPos + length - 1, yPos, (GuageFontEnd_Normal - 0));
		value = 100;
	}
	else
		Osd_DrawCharDirect(xPos + length - 1, yPos, (GuageFontEnd_Normal - 0));
	if (value <= 5)
	{
		if (value == 0)
			Osd_DrawCharDirect(xPos, yPos, (GuageFontStart_Normal + 0));
		else if (value == 1)
			Osd_DrawCharDirect(xPos, yPos, (GuageFontStart_Normal + 1));
		else if (value == 2)
			Osd_DrawCharDirect(xPos, yPos, (GuageFontStart_Normal + 2));
		else if (value == 3)
			Osd_DrawCharDirect(xPos, yPos, (GuageFontStart_Normal + 3));
		else if (value == 4)
			Osd_DrawCharDirect(xPos, yPos, (GuageFontStart_Normal + 4));
		else
			Osd_DrawCharDirect(xPos, yPos, (GuageFontStart_Normal + 5));
		value = 0;
	}
	else
	{
		Osd_DrawCharDirect(xPos, yPos, (GuageFontStart_Normal + 5));
		//value=value-6;
	}
	length -= 2;
	// bar length should small than 42 ( ucLength < 43 )
	pLead = ( (WORD) value * length * GuageLevel ) / 100;   // resver 0.1 // fill bar ucLength 10 times
	if( value != 0 && pLead == 0 )
		pLead++;
	for(ucLoop = 1; ucLoop <= (pLead / GuageLevel); ucLoop++)
	{
		Osd_DrawCharDirect(xPos + ucLoop, yPos, GuageFont6_6);
	}
	if(pLead < length * GuageLevel)
	{
		Osd_DrawCharDirect(xPos + ucLoop, yPos, GuageFont0_6 + (pLead % GuageLevel));
	}
	for(ucLoop = (pLead / GuageLevel + 2); ucLoop <= length; ucLoop++)
	{
		Osd_DrawCharDirect(xPos + ucLoop, yPos, GuageFont0_6);
	}
	OSD_TEXT_HI_ADDR_CLR_TO_0();
}

// ============================
// Draw Hex for Debug
BYTE Hex2ASCII(WORD Num)
{
	return ( Num < 10 ) ? ( Num + 0x30 ) : ( Num - 10 + 0x41 );
}
void DrawHex(BYTE xPos, BYTE yPos, WORD value)
{
	char len = 3;
	while( value && len >= 0 )
	{
		Osd_DrawCharDirect( xPos + ( len-- ), yPos, ( BYTE )Hex2ASCII( value % 0x10 ) );
		value /= 0x10;
	}
	if( len >= 0 )
	{
		for( value = 0; value <= len; value++ )
		{
			Osd_DrawCharDirect( xPos + value, yPos, ( BYTE )0x30 );
		}
	}
}
void Osd_DrawHex(BYTE xPos, BYTE yPos, WORD value)
{
	DrawHex(xPos, yPos, value);
}


#if CHIP_ID>=CHIP_TSUMV
void LoadCommonFont(void)
{
	msWrite2ByteMask(OSD1_0A, 0x0200 + _4ColorFontStart, 0x03FF); // 4 color start
	msWrite2ByteMask(OSD1_0C, 0x0200 + _8ColorFontStart, 0x03FF); // 8 color start
	msWrite2ByteMask(OSD1_0E, 0x03FF, 0x03FF);  // 16 color start
	LoadCompressColorFont(0, 0, 0); //xxxx
	#if CHIP_ID>=CHIP_TSUM2
	mStar_LoadCompressedFont( GET_FONT_RAM_ADDR(MonoFontStart), tColor2FixFont, 0 );
	mStar_LoadCompressedFont( GET_FONT_RAM_ADDR(MonoNumberStart), tOSDNumberFont, 0 );
	mStar_LoadCompressedFont( GET_FONT_RAM_ADDR(FfontStart), &tFontF, 0 );
	#else
	mStar_LoadCompressedFont( MonoFontStart, tColor2FixFont, 0 );
	mStar_LoadCompressedFont( MonoNumberStart, tOSDNumberFont, 0 );
	mStar_LoadCompressedFont( (FfontStart), &tFontF, 0 );
	#endif
	#if OsdHelpKeyType == OsdHelpKey_Under
	mStar_LoadCompressedFont( GET_FONT_RAM_ADDR(0x11), &HelpKeyIcon, 0 );
	#elif 	OsdHelpKeyType == OsdHelpKey_Right
	OSD_FONT_HI_ADDR_SET_BIT8();//0x100~0x1FF
	mStar_LoadCompressedFont( GET_FONT_RAM_ADDR(0x11), &HelpKeyIcon, 0 );
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#endif
	LoadLanguageStatusPropfont();
	OSD_FONT_HI_ADDR_SET_BIT8();//0x100~0x1FF
	OSD_WRITE_FONT_ADDRESS(MonoGuageFontStar);
	#if CHIP_ID>=CHIP_TSUM2
	mStar_LoadCompressedFont( GET_FONT_RAM_ADDR(MonoGuageFontStar), tMonoGauge, 0 );
	#else
	mStar_LoadCompressedFont( MonoGuageFontStar, tMonoGauge, 0 );
	#endif
	OSD_FONT_HI_ADDR_CLR_TO_0();
	OSD_FONT_HI_ADDR_SET_BIT9();//0x200~0x2FF
	OSD_WRITE_FONT_ADDRESS(_4ColorMainIconStart);
	LoadCompressColorFont(&tMainMenuIcon4ColorFont, NULL, 18); // load osd fonts
	OSD_WRITE_FONT_ADDRESS(_8ColorMainIconStart);
	Osd_Load8ColorFont( _8ColorMainIconStart, &tMainMenuIcon8ColorFont, sizeof( tMainMenuIcon8ColorFont ) );
	OSD_FONT_HI_ADDR_CLR_TO_0();
	Load256ColorPalette(0, 0, &tOSDColorPalette256, sizeof( tOSDColorPalette256 ) / sizeof(ColorPaletteType) );
}

#else
void LoadCommonFont(void)
{
	mStar_LoadCompressedFont(0, 0, 0); //xxxx
	//Load 2 COLOR Font
	#if CHIP_ID==CHIP_TSUMU
	msWriteByte( OCFF, 0xC0 );
	#else
	msWriteByte( OCFF, 0xC6 );
	#endif
	msWriteByte( IOSDC2, 0x83); // color bit setting
	mStar_LoadCompressedFont( MonoFontStart, tColor2FixFont, 0 );
	mStar_LoadCompressedFont( MonoNumberStart, tOSDNumberFont, 0 );
	mStar_LoadCompressedFont( FfontStart, &tFontF, 0 );
	LoadLanguageStatusPropfont();
	msWriteByte( OSD2_AE, BIT7 );
	mStar_LoadCompressedFont( MonoGuageFontStar, tMonoGauge, 0 );
	msWriteByte( OSD2_AE, 0 );
	msWriteByte( OSDCFHA, msReadByte(OSDCFHA) | BIT6 | BIT3);
	//Load 4 COLOR Font
	msWriteByte( IOSDC2, 0x83 ); //0x83); // color bit setting
	msWriteByte( OSDCFHA, (msReadByte(OSDCFHA) & ~(BIT3 | BIT2)) | BIT3);
	msWriteByte( OSDCFA, FONT_4COLOR_ICON_START + 0xFF ); // color font start address
	msWriteByte( OSDCFHA, (msReadByte(OSDCFHA) & ~(BIT7 | BIT6)) | BIT6);
	msWriteByte( OSD8CFFA, FONT_8COLOR_ICON_START );
	msWriteByte( OSD2_AE, BIT6 );
	OSD_WRITE_FONT_ADDRESS(_4ColorMainIconStart);
	LoadCompressColorFont(&tMainMenuIcon4ColorFont, NULL, 18); // load osd fonts
	OSD_WRITE_FONT_ADDRESS(_8ColorMainIconStart);
	Osd_Load8ColorFont( _8ColorMainIconStart, &tMainMenuIcon8ColorFont, sizeof( tMainMenuIcon8ColorFont ) );
	msWriteByte( OSD2_AE, 0 );
	Load256ColorPalette(0, 0, &tOSDColorPalette256, sizeof( tOSDColorPalette256 ) / sizeof(ColorPaletteType) );
	//drvOsdLoad256ColorPalette( 0x00, &tOSDColorPalette256, sizeof( tOSDColorPalette256 ), TRUE ); // load osd color
}

#endif


#if OsdHelpKeyType ==	 OsdHelpKey_Under || OsdHelpKeyType ==	 OsdHelpKey_Right
void UpdataHelyKeyShowInMenu(void)
{
	OSD_FONT_HI_ADDR_SET_BIT8();//0x100~0x1FF
	if(MenuPageIndex > RootMenu && MenuPageIndex < ExitMenu)
	{
		mStar_LoadCompressedFont( GET_FONT_RAM_ADDR(0x80), &HelpKeyIcon, 0 );
	}
	else if(MenuPageIndex > ExitMenu && MenuPageIndex < HotKeyECOMenu)
	{
		mStar_LoadCompressedFont( GET_FONT_RAM_ADDR(0x80), &HelpKeyIcon2, 0 );
	}
	OSD_FONT_HI_ADDR_CLR_TO_0();
}
#endif


//==============================================================================
//==============================================================================
#if 0
extern xdata BYTE OsdFontColor  ;
extern BYTE  xdata MenuPageIndex ;


#define WAIT_V_OUTPUT_BLANKING_START()   { if(!SyncLossState()&&PanelOnFlag){TimeOutCounter=30;while((msReadByte(SC0_E0)&BIT0)==0);\
			TimeOutCounter=30;while((msReadByte(SC0_E0)&BIT0)!=0);}}//20130227 modify for DC OFF issue

#define OSD_WINDOW_ADDR(OsdWND,Addr)    ((OsdWND<<5)+Addr)
void SetOSDWindosw(BYTE ucSubWin, BYTE u8HStart, BYTE u8HEnd, BYTE u8VStart, BYTE u8VEnd, BYTE u8Color)
{
	#if CHIP_ID>=CHIP_TSUMV
	// WAIT_V_OUTPUT_BLANKING_START(); //Jison wait 1 frame to avoid the last text garbage
	//drvOSD_SetWndOn(ucSubWin, FALSE);
	{
		WORD xdata u16MainHStart = drvOSD_GetWndInfo(OSD_MAIN_WND, OSD_WND_INFO_H_START);
		WORD xdata u16MainVStart = drvOSD_GetWndInfo(OSD_MAIN_WND, OSD_WND_INFO_V_START);
		if (bMoveCURSORFlag)
		{
			#if 1//20120817-1 Eson
			drvOSD_SetWndCABaseAddr(ucSubWin, 0x046);//clear
			#else
			if( MenuPageIndex == HotInputSelectMenu
			  )		//120428 Modify
				drvOSD_SetWndCABaseAddr(ucSubWin, 0x046);//clear
			else
				drvOSD_SetWndCABaseAddr(ucSubWin, 0x200);//clear
			#endif
			WAIT_V_OUTPUT_BLANKING_START();
		}
		else
			drvOSD_SetWndCABaseAddr(ucSubWin, drvOSD_GetWndInfo(OSD_MAIN_WND, OSD_WND_INFO_CABASE) +
			                        (WORD)u8VStart * drvOSD_GetWndInfo(OSD_MAIN_WND, OSD_WND_INFO_LINE_OFFSET) + u8HStart);
		#if ENABLE_MENULOAD	//111223 Modify
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW_ADDR(ucSubWin, OSD2_04), (u16MainHStart + (WORD)u8HStart * 12));
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW_ADDR(ucSubWin, OSD2_05), (u16MainHStart + (WORD)u8HStart * 12) >> 8);
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW_ADDR(ucSubWin, OSD2_08), (u16MainHStart + ((WORD)u8HEnd + 1) * 12));
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW_ADDR(ucSubWin, OSD2_09), (u16MainHStart + ((WORD)u8HEnd + 1) * 12) >> 8);
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW_ADDR(ucSubWin, OSD2_06), (u16MainVStart + (WORD)u8VStart * 18));
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW_ADDR(ucSubWin, OSD2_07), (u16MainVStart + (WORD)u8VStart * 18) >> 8);
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW_ADDR(ucSubWin, OSD2_0A), (u16MainVStart + ((WORD)u8VEnd + 1) * 18));
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW_ADDR(ucSubWin, OSD2_0B), (u16MainVStart + ((WORD)u8VEnd + 1) * 18) >> 8);
		msML_Trigger(ML_TRIG_SW);// Vde-end-OP

		#elif ENABLE_SW_DOUBLE_BUFFER
		//msSWDBWaitForRdy();
		DB_Mode(ML_MODE_NORMAL);
		DB_WB(OSD_WINDOW_ADDR(ucSubWin, OSD2_04), (u16MainHStart + (WORD)u8HStart * 12));
		DB_WB(OSD_WINDOW_ADDR(ucSubWin, OSD2_05), (u16MainHStart + (WORD)u8HStart * 12) >> 8);
		DB_WB(OSD_WINDOW_ADDR(ucSubWin, OSD2_08), (u16MainHStart + ((WORD)u8HEnd + 1) * 12));
		DB_WB(OSD_WINDOW_ADDR(ucSubWin, OSD2_09), (u16MainHStart + ((WORD)u8HEnd + 1) * 12) >> 8);
		DB_WB(OSD_WINDOW_ADDR(ucSubWin, OSD2_06), (u16MainVStart + (WORD)u8VStart * 18));
		DB_WB(OSD_WINDOW_ADDR(ucSubWin, OSD2_07), (u16MainVStart + (WORD)u8VStart * 18) >> 8);
		DB_WB(OSD_WINDOW_ADDR(ucSubWin, OSD2_0A), (u16MainVStart + ((WORD)u8VEnd + 1) * 18));
		DB_WB(OSD_WINDOW_ADDR(ucSubWin, OSD2_0B), (u16MainVStart + ((WORD)u8VEnd + 1) * 18) >> 8);
		msSWDBWriteToRegister();
		msSWDBWaitForRdy();
		#else
		drvOSD_SetWndHPosition(ucSubWin, u16MainHStart + (WORD)u8HStart * 12, u16MainHStart + ((WORD)u8HEnd + 1) * 12);
		drvOSD_SetWndVPosition(ucSubWin, u16MainVStart + (WORD)u8VStart * 18, u16MainVStart + ((WORD)u8VEnd + 1) * 18);
		#endif
	}
	drvOSD_SetWndFixAttr(ucSubWin, _ENABLE, u8Color);
	//WAIT_V_OUTPUT_BLANKING_START(); //Jison wait 1 frame to avoid the last text garbage
	drvOSD_SetWndOn(ucSubWin, TRUE);
	#else    // Wind as 0 ~3
	if (OSD_CURSOR_WND == ucSubWin)
		ucSubWin = SUB_WIN_00;
	ucSubWin = SUBW0C + ucSubWin * 6;
	mStar_WriteOSDByte(ucSubWin + 1, u8HStart);
	mStar_WriteOSDByte(ucSubWin + 2, u8HEnd);
	mStar_WriteOSDByte(ucSubWin + 3, u8VStart);
	mStar_WriteOSDByte(ucSubWin + 4, u8VEnd);
	mStar_WriteOSDByte(ucSubWin + 5, u8Color);
	if ((ucSubWin | BKMASKOSD1) == SUBW1C)
		mStar_WriteOSDByte(ucSubWin + 0, 0x03);
	else
		mStar_WriteOSDByte(ucSubWin + 0, 0x01);
	#endif
}

void ClrOSDWindosw(BYTE ucSubWin)
{
	#if CHIP_ID>=CHIP_TSUMV
	drvOSD_SetWndOn(ucSubWin, FALSE);
	#else
	// Wind as 0 ~3
	if (OSD_CURSOR_WND == ucSubWin)
		ucSubWin = SUB_WIN_00;
	ucSubWin = SUBW0C + ucSubWin * 6;
	mStar_WriteOSDByte(ucSubWin + 0, 0x00);
	mStar_WriteOSDByte(ucSubWin + 1, 0x00);
	mStar_WriteOSDByte(ucSubWin + 2, 0x00);
	mStar_WriteOSDByte(ucSubWin + 3, 0x00);
	mStar_WriteOSDByte(ucSubWin + 4, 0x00);
	mStar_WriteOSDByte(ucSubWin + 5, 0x00);
	#endif
}

#if CHIP_ID<CHIP_TSUMV

void SetOsdGraduallyBackGround( BYTE Win_Num, BYTE GDRValue, BYTE GDGValue, BYTE GDBValue, BYTE GDDelta, BYTE GDDERange, BYTE GDControl, BYTE GDRInit, BYTE GDGInit, BYTE GDBInit)
{
	if (Win_Num > 4) return;
	switch (Win_Num)
	{
		case SUB_WIN_00:
			Win_Num = OSD_GD00;
			break;
		case SUB_WIN_01:
			Win_Num = OSD_GD01;
			break;
		case SUB_WIN_02:
			Win_Num = OSD_GD02;
			break;
		case SUB_WIN_03:
			Win_Num = OSD_GD03;
			break;
	}
	mStar_WriteOSDByte( Win_Num + 0, GDRValue);
	mStar_WriteOSDByte( Win_Num + 1, GDGValue );
	mStar_WriteOSDByte( Win_Num + 2, GDBValue );
	mStar_WriteOSDByte( Win_Num + 3, GDDelta );
	mStar_WriteOSDByte( Win_Num + 4, GDDelta );
	mStar_WriteOSDByte( Win_Num + 5, GDDERange );
	mStar_WriteOSDByte( Win_Num + 6, GDDERange );
	mStar_WriteOSDByte( Win_Num + 7, GDDERange );
	mStar_WriteOSDByte( Win_Num + 8, GDDERange );
	mStar_WriteOSDByte( Win_Num + 9, GDControl );
	mStar_WriteOSDByte( Win_Num + 10, GDRInit );
	mStar_WriteOSDByte( Win_Num + 11, GDGInit );
	mStar_WriteOSDByte( Win_Num + 12, GDBInit );
}
#endif

BYTE Osd_DoubleBuffer(Bool u8Enable)
{
	#if CHIP_ID>=CHIP_TSUMV
	u8Enable = 0;
	return u8Enable;
	#else
	BYTE u8Org = msReadByte(OSD1_01);
	msWriteByte(OSD1_01, (u8Enable ? 0x05 : 0));
	return (u8Org);
	#endif
}

void Osd_Set256TextColor(BYTE foreColor, BYTE backColor)
{
	if(backColor == Color_2)
		OsdFontColor = foreColor;
	else if(backColor == Color_2G)
	{
		#if CHIP_ID>=CHIP_TSUMV
		OsdFontColor = (foreColor & 0xF0) | 0x01;
		#else
		OsdFontColor = foreColor;
		#endif
	}
	else if(backColor == Color_4)
		OsdFontColor = foreColor << 2;
	else if(backColor == Color_8)
		OsdFontColor = foreColor << 3;
	else if(backColor == Color_8G)
		OsdFontColor = (foreColor << 3) | BIT1;
	else if(backColor == Color_2T)
		OsdFontColor = foreColor | 0x00;
	else if(backColor == Color_4T)
		OsdFontColor = foreColor << 2 | 0x01;
	else// (backColor==Color_8T)
		OsdFontColor = foreColor << 3 | 0x01;
}

#endif


//Character Direct Write DisplayCode
void Osd_DrawCharDirect(BYTE xPos, BYTE yPos, BYTE ch)
{
	#if CHIP_ID>=CHIP_TSUMV
	//drvOSD_DrawRealChar(g_u8OsdWndNo, xPos, yPos, ch);
	WORD u16TempValue;
	BYTE u8DrawCode = (!(yPos & BIT7));
	yPos &= 0x7F;
	//u8Wnd<<=5;
	//u16TempValue=msRead2Byte((u8Wnd)+OSD2_10)+(WORD)u8YPos*msReadByte((u8Wnd)+OSD2_12)+u8XPos; // get real address
	u16TempValue = GET_TXT_CASTART(g_u8OsdWndNo, xPos, yPos); // get real address
	WRITE_CAFSRAM_ADDR();
	msWrite2Byte(PORT_ATTR_ADDR, u16TempValue); // display font attribute
	WRITE_ATTRIBUTE();
	msWriteByte(PORT_ATTR_DATA, OsdFontColor);
	if (u8DrawCode)
	{
		WRITE_CAFSRAM_ADDR();
		msWrite2Byte(PORT_CODE_ADDR, u16TempValue); // dispaly font code
		WRITE_CODE();
		msWriteByte(PORT_CODE_DATA, ch);
	}
	#else
	WORD u16TempValue;
	BYTE u8DrawCode = (!(yPos & BIT7));
	yPos &= 0x7F;
	u16TempValue = (WORD)yPos * OsdWindowWidth + xPos; // get real address
	msWrite2Byte(OSD2_A8, u16TempValue); // display font attribute
	msWriteByte(OSD2_AA, OsdFontColor);
	if (u8DrawCode)
	{
		msWrite2Byte(OSD2_A5, u16TempValue); // dispaly font code
		msWriteByte(OSD2_A7, ch);
	}
	#endif
}

void Osd_DrawContinuesChar(BYTE xPos, BYTE yPos, BYTE ch, BYTE ucNum)
{
	#if CHIP_ID>=CHIP_TSUMV
	//drvOSD_DrawContinuousChar(g_u8OsdWndNo,xPos,yPos,ch,ucNum);
	WORD u16TempValue;
	BYTE i;
	BYTE    u8DrawCode = (!(yPos & BIT7));
	yPos &= 0x7F;
	//u8Wnd<<=5;
	//u16TempValue=msRead2Byte((u8Wnd)+OSD2_10)+(WORD)u8YPos*msReadByte((u8Wnd)+OSD2_12)+u8XPos; // get real address
	u16TempValue = GET_TXT_CASTART(g_u8OsdWndNo, xPos, yPos); // get real address
	WRITE_CAFSRAM_ADDR();
	msWrite2Byte(PORT_ATTR_ADDR, u16TempValue);
	WRITE_ATTRIBUTE();
	for(i = 0; i < ucNum; i++)
	{
		msWriteByte(PORT_ATTR_DATA, OsdFontColor);
	}
	if (u8DrawCode)
	{
		WRITE_CAFSRAM_ADDR();
		msWrite2Byte(PORT_CODE_ADDR, u16TempValue);
		WRITE_CODE();
		for(i = 0; i < ucNum; i++)
		{
			msWriteByte(PORT_CODE_DATA, ch);
		}
	}
	#else
	WORD u16TempValue;
	BYTE i;
	BYTE	u8DrawCode = (!(yPos & BIT7));
	yPos &= 0x7F;
	u16TempValue = (WORD)yPos * OsdWindowWidth + xPos; // get real address
	msWrite2Byte(OSD2_A8, u16TempValue);
	for(i = 0; i < ucNum; i++)
	{
		msWriteByte(OSD2_AA, OsdFontColor);
	}
	if (u8DrawCode)
	{
		msWrite2Byte(OSD2_A5, u16TempValue);
		for(i = 0; i < ucNum; i++)
		{
			msWriteByte(OSD2_A7, ch);
		}
	}
	#endif
}

void Osd_DrawPropStr(BYTE xPos, BYTE yPos, BYTE *str)
{
	#if CHIP_ID>=CHIP_TSUMV
	WORD  xdata  u16TempValue;
	Bool  xdata  IsDrawCode = TRUE;
	if (str == NULL || (*(str + 1)) == 0) //Jison
		return;
	if (yPos & BIT7)
		IsDrawCode = FALSE;
	#if 0
	if( yPos == 2 || xPos == 0 )
	{
		xPos = ( OsdWindowWidth - (*(str + 1)) ) / 2 + 1;
	}
	#endif
	yPos &= 0x7F; //~(BIT7|BIT6);
#define DISP_CHAR   xPos
#define DISP_PTR    yPos
	//u16TempValue=g_u8OsdWndNo<<5;
	//u16TempValue=msRead2Byte(u16TempValue+OSD2_10)+(WORD)u8YPos*msReadByte(u16TempValue+OSD2_12)+u8XPos; // get real address
	u16TempValue = GET_TXT_CASTART(g_u8OsdWndNo, xPos, yPos); // get real address
	DISP_PTR = 0;
	WRITE_CAFSRAM_ADDR();
	msWrite2Byte(PORT_ATTR_ADDR, u16TempValue);
	WRITE_ATTRIBUTE();
	while (DISP_PTR++ < * (str + 1))
		msWriteByte(PORT_ATTR_DATA, OsdFontColor);
	if (IsDrawCode == TRUE)
	{
		DISP_PTR = 0;
		WRITE_CAFSRAM_ADDR();
		msWrite2Byte(PORT_CODE_ADDR, u16TempValue);
		WRITE_CODE();
		{
			while (DISP_PTR < * (str + 1))
			{
				msWriteByte(PORT_CODE_DATA, (*str) + DISP_PTR);
				DISP_PTR++;
			}
		}
	}
#undef DISP_CHAR
#undef DISP_PTR
	#else
	WORD tempValue;
	BYTE drawCode = TRUE, tempdispPtr;
	if (str == NULL || (*(str + 1)) == 0) //Jison
		return;
	if( yPos & BIT7 )
	{
		drawCode = FALSE;
	}
	yPos &= 0x7F; //~(BIT7|BIT6);
#define dispChar    xPos
#define dispPtr     tempdispPtr
	tempValue = ( WORD )yPos * OsdWindowWidth + xPos;// get real address
	dispPtr = 0;
	msWrite2Byte( OSD2_A8, tempValue );
	while( dispPtr++ < * ( str + 1 ) )
	{
		msWriteByte( OSD2_AA, OsdFontColor );
	}
	if( drawCode == TRUE )
	{
		dispPtr = 0;
		msWrite2Byte( OSD2_A5, tempValue );
		while( dispPtr < * ( str + 1 ) )
		{
			msWriteByte( OSD2_A7, ( *str) + dispPtr );
			dispPtr++;
		}
	}
#undef dispChar
#undef dispPtr
	#endif
}

void Osd_DrawRealStr(BYTE xPos, BYTE yPos, BYTE *str)
{
	#if CHIP_ID>=CHIP_TSUMV
	WORD u16TempValue;
	BYTE u8DrawCode = (!(yPos & BIT7));
	yPos &= 0x7F;
	//u8Wnd<<=5;
	//u16TempValue=msRead2Byte((u8Wnd)+OSD2_10)+(WORD)u8YPos*msReadByte((u8Wnd)+OSD2_12)+u8XPos; // get real address
	u16TempValue = GET_TXT_CASTART(g_u8OsdWndNo, xPos, yPos); // get real address
#define dispChar    xPos
#define dispPtr     yPos
	dispPtr = 0;
	WRITE_CAFSRAM_ADDR();
	msWrite2Byte(PORT_ATTR_ADDR, u16TempValue); // display font attribute
	WRITE_ATTRIBUTE();
	while( *( str + dispPtr ) ) 	   // display string font index
	{
		msWriteByte(PORT_ATTR_DATA, OsdFontColor);
		dispPtr++;
	}
	if( u8DrawCode )
	{
		dispPtr = 0;
		WRITE_CAFSRAM_ADDR();
		msWrite2Byte(PORT_CODE_ADDR, u16TempValue); // dispaly font code
		WRITE_CODE();
		while( dispChar = *( str + dispPtr ) )			  // display string font index
		{
			msWriteByte(PORT_CODE_DATA, dispChar);
			dispPtr++;
		}
	}
#undef dispChar
#undef dispPtr
	#else
	#if 1 // 110819 wait for coding
	WORD tempValue;
	BYTE drawCode = TRUE;
	BYTE y;
	if( yPos & BIT7 )
	{
		drawCode = FALSE;
	}
	yPos &= 0x3F; //~(BIT7|BIT6);
	y = yPos;
#define dispChar    xPos
#define dispPtr     yPos
	tempValue = ( WORD )yPos * OsdWindowWidth + xPos; // get real address
	dispPtr = 0;
	msWrite2Byte( OSD2_A8, tempValue );
	while( *( str + dispPtr ) ) 	   // display string font index
	{
		msWriteByte( OSD2_AA, OsdFontColor );
		dispPtr++;
	}
	if( drawCode == TRUE )
	{
		dispPtr = 0;
		msWrite2Byte( OSD2_A5, tempValue );
		while( dispChar = *( str + dispPtr ) )			  // display string font index
		{
			msWriteByte( OSD2_A7, dispChar );
			dispPtr++;
			#if DEBUG_OSD
			ForceDelay1ms(20);
			#endif
		}
	}
#undef dispChar
#undef dispPtr
	#endif
	#endif
}

void msOSDuncall(void)
{
	#if !ENABLE_MENULOAD//||!ENABLE_SW_DOUBLE_BUFFER
	drvOSD_SetWndHPosition(0, 0, 0);
	drvOSD_SetWndVPosition(0, 0, 0);
	#endif
}







