
#include "global.h"
#include "msosd.h"
#include "msosdfunction.h"
#include "drvosd.h"
#include "extlib.h"
#include "CommonLoadCPnCompressFont.h"
#include "FactoryStringText.h"
#include "FactoryFontText.h"
#include "PropFont.h"


#include "LogoFontText.h"


extern xdata BYTE OsdFontColor;

void Osd_DrawRealStr_F(BYTE xPos, BYTE yPos, BYTE *str);

#if CHIP_ID >= CHIP_TSUMV
static void Load256ColorPalette(BYTE u8Group, BYTE u8Addr, ColorPaletteType *colorPtr, WORD u16Num)
{
	#if CHIP_ID>=CHIP_TSUM2
	WORD xdata i;
	if (u8Group == 0)
		WRITE_PSRAM0_ADDR();
	else
		WRITE_PSRAM1_ADDR();
	//write R/G/B
	msWriteByte(OSD1_66, u8Addr);
	if (u8Group == 0)
		WRITE_PSRAM0_COLOR();
	else
		WRITE_PSRAM1_COLOR();
	for (i = 0; i < u16Num; i++)
	{
		msWriteByte(OSD1_66, ((colorPtr + i)->u8Blue));
		msWriteByte(OSD1_66, ((colorPtr + i)->u8Green));
		msWriteByte(OSD1_66, ((colorPtr + i)->u8Red));
	}
	//write colorkey
	if (u8Group == 0)
		WRITE_PSRAM0_ADDR();
	else
		WRITE_PSRAM1_ADDR();
	msWriteByte(OSD1_66, u8Addr);
	if (u8Group == 0)
		WRITE_PSRAM0_COLOR_KEY();
	else
		WRITE_PSRAM0_COLOR_KEY();
	while (u16Num--)
	{
		if(colorPtr->u8ColorKey)
			msWriteByteMask(OSD1_66, BIT0, BIT0);
		else
			msWriteByteMask(OSD1_66, 0, BIT0);
		colorPtr++;
	}
	#elif CHIP_ID==CHIP_TSUMV
	WORD xdata i, u16PSRAM_AddrPort;
	BYTE u8Bank = msReadByte(OSD1_00);
	msWriteByte(OSD1_00, 0x00); //subbank 0
	if (u8Group == 0)
		u16PSRAM_AddrPort = OSD1_76;
	else
		u16PSRAM_AddrPort = OSD1_86;
//u8Addr=0;
	//write R/G/B
	msWriteByte(u16PSRAM_AddrPort, u8Addr);
	for (i = 0; i < u16Num; i++)
	{
		msWriteByte(u16PSRAM_AddrPort + 2, ((colorPtr + i)->u8Blue));
		msWriteByte(u16PSRAM_AddrPort + 2, ((colorPtr + i)->u8Green));
		msWriteByte(u16PSRAM_AddrPort + 2, ((colorPtr + i)->u8Red));
	}
	//write colorkey
	msWriteByte(u16PSRAM_AddrPort, u8Addr);
	while (u16Num--)
	{
		if(colorPtr->u8ColorKey)
			msWriteByteMask(u16PSRAM_AddrPort + 3, BIT0, BIT0);
		else
			msWriteByteMask(u16PSRAM_AddrPort + 3, 0, BIT0);
		colorPtr++;
	}
	msWriteByte(OSD1_00, u8Bank); //subbank 0
	#else
	WORD xdata i;
	u8Group = 0;
	msWriteByte( OSD2_AC, u8Addr );
	for (i = 0; i < u16Num; i++)
	{
		msWriteByte(OSD2_AD, ((colorPtr + i)->u8Red));
		msWriteByte(OSD2_AD, ((colorPtr + i)->u8Green));
		msWriteByte(OSD2_AD, ((colorPtr + i)->u8Blue));
	}
	#endif
}

#endif


#if (DisplayLogo!=NoBrand)//130306 Modify






void Osd_LoadLogoFontCP(void)
{
	Load256ColorPalette(0, 0, &tOSDColorPalette0, sizeof( tOSDColorPalette0) / sizeof(ColorPaletteType) );
	#if CHIP_ID==CHIP_TSUMV
	#if (DisplayLogo==AlgeriaLOGO)
	mStar_LoadCompressedFont(1, &tOSDLogoFont_LEFT, 0);
	mStar_LoadCompressedFont(50, &tOSDLogoFont_Right, 0);
	msWrite2ByteMask(OSD1_0A, 200, 0x03FF);
	OSD_WRITE_FONT_ADDRESS(LOBYTE(200));
	LoadCompressColorFont( &tOSDLogoFont_Middle, 0, 25 );
	#elif (DisplayLogo==HUNTKEYLOGO)
	mStar_LoadCompressedFont(1, &tOSDLogoFont, 0);
	#elif (DisplayLogo==DAHUALOGO)
	mStar_LoadCompressedFont(1, &tOSDLogoFont, 0);
	OSD_FONT_HI_ADDR_SET_BIT8();
	msWrite2ByteMask(OSD1_0A, 0x1ff, 0x03FF);
	msWrite2ByteMask(OSD1_0C, 0x2ff, 0x03FF);
	mStar_LoadCompressedFont(1, &tOSDLogoFont1, 0);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#else
	mStar_LoadCompressedFont(1, &tOSDLogoFont, 0);
	#endif
	#else
	#if (DisplayLogo==AlgeriaLOGO)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(1), &tOSDLogoFont_LEFT, 0);
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(50), &tOSDLogoFont_Right, 0);
	msWrite2ByteMask(OSD1_0A, 200, 0x03FF);
	OSD_WRITE_FONT_ADDRESS(LOBYTE(200));
	LoadCompressColorFont( &tOSDLogoFont_Middle, 0, 25 );
	#elif (DisplayLogo==DAHUALOGO)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, sizeof(tOSDLogoFont));
	OSD_FONT_HI_ADDR_SET_BIT8();
	msWrite2ByteMask(OSD1_0A, 0x1ff, 0x03FF);
	msWrite2ByteMask(OSD1_0C, 0x2ff, 0x03FF);
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont1, sizeof(tOSDLogoFont1));
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==LOGO_ELECTROMAN)
	msWrite2ByteMask(OSD1_0A, 0x1ff, 0x03FF);
	msWrite2ByteMask(OSD1_0C, 0x2ff, 0x03FF);
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, sizeof(tOSDLogoFont));
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont1, sizeof(tOSDLogoFont1));
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==LOGO_DULLDOG)
	msWrite2ByteMask(OSD1_0A, 0x2ff, 0x03FF);
	msWrite2ByteMask(OSD1_0C, 0x2ff, 0x03FF);
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, sizeof(tOSDLogoFont));
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogo2Font, sizeof(tOSDLogo2Font));
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==LOGO_ONEPIECE)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, 0);
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont1, 0);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==LOGO_AISI)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, 0);
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont1, 0);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==LOGO_AISI2)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, 0);
	msWrite2ByteMask(OSD1_0A, 0x140, 0x03FF);
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x00), &tOSDLogoFont1, 0);
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x40));
	LoadCompressColorFont( &tOSDLogoFont2, NULL, 90 );
	OSD_FONT_HI_ADDR_CLR_TO_0();
	OSD_FONT_HI_ADDR_SET_BIT9();
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x00));
	LoadCompressColorFont( &tOSDLogoFont3, NULL, 92 );
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==LOGO_CAOMAO)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, 0);
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont1, 0);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==LOGO_LUFEI2)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, 0);
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont1, 0);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==LOGO_LUFEI)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, 0);
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont1, 0);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==LOGO_LONG)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont2, 0);
	msWrite2ByteMask(OSD1_0A, 0x100, 0x03FF);
	OSD_FONT_HI_ADDR_SET_BIT8();
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x100));
	LoadCompressColorFont( &tOSDLogoFont4, NULL, 82 );
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==LOGO_AI)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont2, 0);
	msWrite2ByteMask(OSD1_0A, 0x100, 0x03FF);
	OSD_FONT_HI_ADDR_SET_BIT8();
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x100));
	LoadCompressColorFont( &tOSDLogoFont4, NULL, 14 );
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==LOGO_ZEI)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont2, 0);
	msWrite2ByteMask(OSD1_0A, 0x100, 0x03FF);
	OSD_FONT_HI_ADDR_SET_BIT8();
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x100));
	LoadCompressColorFont( &tOSDLogoFont4, NULL, 24 );
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==HUANGHE_LOGO)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, sizeof(tOSDLogoFont));
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont1, sizeof(tOSDLogoFont1));
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==MIMO_LOGO)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(1), &tOSDLogoFont, 0);
	msWrite2ByteMask(OSD1_0A, 0x9D, 0x03FF);
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0xEC));
	LoadCompressColorFont( &tOSDLogoFont1, 0, 10);
	#elif (DisplayLogo==YWYMIMO_LOGO)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(1), &tOSDLogoFont, sizeof(tOSDLogoFont));
	msWrite2ByteMask(OSD1_0A, 0xEC, 0x03FF);
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0xEC));
	LoadCompressColorFont(&tOSDLogoFont1, 0, 10);
	#elif (DisplayLogo==CHANG_LOGO)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, sizeof(tOSDLogoFont));
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont1, sizeof(tOSDLogoFont1));
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==YWYPOLY_LOGO)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, sizeof(tOSDLogoFont));
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont1, sizeof(tOSDLogoFont1));
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==POLY_LOGO)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, sizeof(tOSDLogoFont));
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont1, sizeof(tOSDLogoFont1));
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==LOGO_SUO2)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, sizeof(tOSDLogoFont));
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x00), &tOSDLogoFont1, sizeof(tOSDLogoFont1));
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==DRAGON_LOGO)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, 0);
	msWrite2ByteMask(OSD1_0A, 0x100, 0x03FF);
	OSD_FONT_HI_ADDR_SET_BIT8();
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x00));
	LoadCompressColorFont( &tOSDLogoFont1, NULL, 82);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==YWYDGM_LOGO)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, sizeof(tOSDLogoFont));
	msWrite2ByteMask(OSD1_0A, 0x100, 0x03FF);
	OSD_FONT_HI_ADDR_SET_BIT8();
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x00));
	LoadCompressColorFont(&tOSDLogoFont1, 0, 82);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==YWYLBS_LOGO)
	msWrite2ByteMask(OSD1_0A, 0x165, 0x03FF);
	msWrite2ByteMask(OSD1_0C, 0x3FF, 0x03FF);
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, 0);
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x00), &tOSDLogoFont1, 0);
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x65));
	LoadCompressColorFont( &tOSDLogoFont2, NULL, 60);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	OSD_FONT_HI_ADDR_SET_BIT9();
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x00));
	LoadCompressColorFont( &tOSDLogoFont3, NULL, 60);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==YMH_LOGO)
	msWrite2ByteMask(OSD1_0A, 0x100, 0x03FF);
	msWrite2ByteMask(OSD1_0C, 0x03FF, 0x03FF);
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, 0);
	OSD_FONT_HI_ADDR_SET_BIT8();//0x100
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x00));
	LoadCompressColorFont( &tOSDLogoFont4, NULL, 43);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	OSD_FONT_HI_ADDR_SET_BIT9();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont1, 0);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==YWYBIRD_LOGO)
	msWrite2ByteMask(OSD1_0A, 0x100, 0x03FF);
	msWrite2ByteMask(OSD1_0C, 0x03FF, 0x03FF);
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, sizeof(tOSDLogoFont));
	OSD_FONT_HI_ADDR_SET_BIT8();
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x00));
	LoadCompressColorFont(&tOSDLogoFont1, 0, 118);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==LOGO_DUNPAI)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, 0);
	msWrite2ByteMask(OSD1_0A, 0x165, 0x03FF);
	msWrite2ByteMask(OSD1_0C, 0x300, 0x03FF);
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont1, 0);
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x65));
	LoadCompressColorFont( &tOSDLogoFont2, NULL, 60);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	OSD_FONT_HI_ADDR_SET_BIT9();
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x01));
	LoadCompressColorFont( &tOSDLogoFont3, NULL, 60);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==LOGO_YINGYAN)
	msWrite2ByteMask(OSD1_0A, 0x209, 0x03FF);
	msWrite2ByteMask(OSD1_0C, 0x300, 0x03FF);
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, 0);
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont1, 0);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	OSD_FONT_HI_ADDR_SET_BIT9();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont2, 0);
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x09));
	LoadCompressColorFont( &tOSDLogoFont4, NULL, 9);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==LOGO_SUO)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, 0);
	msWrite2ByteMask(OSD1_0A, 0x10D, 0x03FF);
	msWrite2ByteMask(OSD1_0C, 0x300, 0x03FF);
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x00), &tOSDLogoFont1, 0);
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x0D));
	LoadCompressColorFont( &tOSDLogoFont2, NULL, 70);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	OSD_FONT_HI_ADDR_SET_BIT9();
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x00));
	LoadCompressColorFont( &tOSDLogoFont3, NULL, 77);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==LBS_LOGO)
	msWrite2ByteMask(OSD1_0A, 0x165, 0x03FF);
	msWrite2ByteMask(OSD1_0C, 0x300, 0x03FF);
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont, 0);
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont1, 0);
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x65));
	LoadCompressColorFont( &tOSDLogoFont2, NULL, 60);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	OSD_FONT_HI_ADDR_SET_BIT9();
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x01));
	LoadCompressColorFont( &tOSDLogoFont3, NULL, 60);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==LOGO_NIAO)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont2, 0);
	msWrite2ByteMask(OSD1_0A, 0x100, 0x03FF);
	msWrite2ByteMask(OSD1_0C, 0x300, 0x03FF);
	OSD_FONT_HI_ADDR_SET_BIT8();
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x100));
	LoadCompressColorFont( &tOSDLogoFont4, NULL, 118);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==ViewSync_LOGO)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont2_1, 0);
	msWrite2ByteMask(OSD1_0A, 0x125, 0x03FF);
	msWrite2ByteMask(OSD1_0C, 0x300, 0x03FF);
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont2_2, 0);
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x125));
	LoadCompressColorFont( &tOSDLogoFont4, NULL, 5);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==Vison_LOGO)
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont2_1, 0);
	msWrite2ByteMask(OSD1_0A, 0x13D, 0x03FF);
	msWrite2ByteMask(OSD1_0C, 0x300, 0x03FF);
	OSD_FONT_HI_ADDR_SET_BIT8();
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont2_2, 0);
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x13D));
	LoadCompressColorFont( &tOSDLogoFont4, NULL, 34);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==DAHUA_LOGO)
	msWrite2ByteMask(OSD1_0A, 0x88, 0x03FF);
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x01), &tOSDLogoFont2, 0);
	OSD_WRITE_FONT_ADDRESS(LOBYTE(0x88));
	LoadCompressColorFont( &tOSDLogoFont4, NULL, 5);
	#else
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(1), &tOSDLogoFont, 0);
	#endif
	#endif
}

void DrawLogo(void) // Draw AOC Logo
{
	BYTE i;
	#if (DisplayLogo==YMH_LOGO||DisplayLogo==YWYLBS_LOGO||DisplayLogo==YWYBIRD_LOGO||DisplayLogo==YWYDGM_LOGO||DisplayLogo==YWYPOLY_LOGO||DisplayLogo==YWYMIMO_LOGO||DisplayLogo==CHANG_LOGO||DisplayLogo==YWY_LOGO||DisplayLogo==TEST_LOGO\
	||DisplayLogo==LOGO_AISI||DisplayLogo==LOGO_AI||DisplayLogo==LOGO_DUNPAI||DisplayLogo==LOGO_LUFEI2||DisplayLogo==LOGO_AISI||DisplayLogo==LOGO_LUFEI||DisplayLogo==LOGO_CAOMAO||DisplayLogo==LOGO_BAIHUZI||DisplayLogo==LOGO_OCEAN||DisplayLogo==LOGO_ONEPIECE||DisplayLogo==DAHUA_LOGO||DisplayLogo==Vison_LOGO||DisplayLogo==ViewSync_LOGO||DisplayLogo==AMAZON_LOGO||DisplayLogo==LBS_LOGO||DisplayLogo==DRAGON_LOGO||DisplayLogo==POLY_LOGO||DisplayLogo==MIMO_LOGO||DisplayLogo==HUANGHE_LOGO||DisplayLogo==EOE_LOGO||DisplayLogo==CHANGHONG||DisplayLogo==AlgeriaLOGO||DisplayLogo==TOPSYNC_LOGO||DisplayLogo==MYIGLOGO||DisplayLogo==LOGO_ZEI||DisplayLogo==Element||DisplayLogo==DAHUALOGO||DisplayLogo==SANXINGLOGO||DisplayLogo==TCL_Logo)
	BYTE j;
	#elif 1
	BYTE j;
	#endif
	Osd_LoadLogoFontCP();
	#if  (DisplayLogo==AOCSoHuLOGO)
	Osd_SetTextMonoColor(0, CP_BlackColor);
	for (i = 0; i < OsdWindowHeight; i++)
{
	Osd_DrawRealStr_F(0, i, AOCSohuLogoText[i]);
	}
	#elif (DisplayLogo==AlgeriaLOGO)
	Osd_SetTextMonoColor(10, CP_BlackColor);
	for (i = 0; i < 5; i++)
{
	for (j = 0; j < 16; j++)
			Osd_DrawCharDirect(j, i, strLOGWindow_Left[i][j]);
	}
	Osd_Set256TextColor( 0x10, Color_2);
	for (i = 0; i < 5; i++)
{
	for (j = 0; j < 5; j++)
			Osd_DrawCharDirect(j + 16, i, strLOGWindow_Middle[i][j]);
	}
	Osd_SetTextMonoColor(CP_BlackColor, 10);
	for (i = 0; i < 5; i++)
{
	for (j = 0; j < 25; j++)
			Osd_DrawCharDirect(j + 16 + 5, i, strLOGWindow_Right[i][j]);
	}
	#elif (DisplayLogo==MYIGLOGO)
	Osd_SetTextMonoColor(CP_RedColor, CP_BlackColor);
	for (i = 0; i < 4; i++)
{
	for (j = 0; j < 70; j++)
			Osd_DrawCharDirect(j, i, strmyiWindow[i][j]);
	}
	Osd_SetTextMonoColor(0x08, CP_BlackColor);
	for (i = 4; i < 14; i++)
{
	for (j = 0; j < 70; j++)
			Osd_DrawCharDirect(j, i, strmyiWindow[i][j]);
	}
	Osd_SetTextMonoColor(CP_RedColor, CP_RedColor);
	for (i = 1; i < 3; i++)
{
	for (j = 52; j < 55; j++)
			Osd_DrawCharDirect(j, i, strmyiWindow[i][j]);
	}
#elif(DisplayLogo==Element)
	Osd_SetTextMonoColor(2, 1);
	for (i = 0; i < 10; i++)
{
	for (j = 0; j < 96; j++)
		{
			Osd_DrawCharDirect(j, i, strELEWindow[i][j]);
		}
	}
	#elif (DisplayLogo==LOGO_FANGZHENG)
	Osd_SetTextMonoColor(2, 3);
	for (i = 0; i < 6; i++)
{
	for (j = 0; j < 60; j++)
		{
			Osd_DrawCharDirect(j, i, strFanWindow[i][j]);
		}
	}
	#elif (DisplayLogo==LOGO_NOBRAND)
	Osd_SetTextMonoColor(2, 3);
	for (i = 0; i < 6; i++)
{
	for (j = 0; j < 48; j++)
		{
			Osd_DrawCharDirect(j, i, strNobWindow[i][j]);
		}
	}
	#elif (DisplayLogo==LOGO_OCEAN)
	Osd_SetTextMonoColor(1, 0);
	for (i = 0; i < 18; i++)
{
	for (j = 0; j < 40; j++)
		{
			Osd_DrawCharDirect(j, i, strOCEWindow[i][j]);
		}
	}
	#elif (DisplayLogo==CHANGHONG)
	Osd_SetTextMonoColor(1, 0);
	for (i = 0; i < 8; i++)
{
	for (j = 0; j < 70; j++)
		{
			Osd_DrawCharDirect(j, i, strCHAWindow[i][j]);
		}
	}
	#elif (DisplayLogo==YWYBIRD_LOGO)
	for (i = 0; i < 13; i++)
{
	for(j = 0; j < 32; j++)
		{
			if(PalSON[i][j] >= 0x98)
			{
				Osd_SetTextMonoColor(PalSON[i][j] + 1, PalSON[i][j]);
			}
			else
			{
				Osd_Set256TextColor(PalSON[i][j], Color_2);
			}
			if(strSONWindow[i][j] > 0xFF)
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, strSONWindow[i][j] & 0xFF);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else
			{
				Osd_DrawCharDirect(j, i, strSONWindow[i][j]);
			}
		}
	}
	#elif (DisplayLogo==YWYDGM_LOGO)
	for (i = 0; i < 23; i++)
{
	for(j = 0; j < 39; j++)
		{
			if(PalDRA[i][j] >= 0x04)
			{
				Osd_SetTextMonoColor(PalDRA[i][j] + 1, PalDRA[i][j]);
			}
			else
			{
				Osd_Set256TextColor(PalDRA[i][j], Color_2);
			}
			if(strDRAWindow[i][j] > 0xFF)
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, strDRAWindow[i][j] & 0xFF);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else
			{
				Osd_DrawCharDirect(j, i, strDRAWindow[i][j]);
			}
		}
	}
	#elif (DisplayLogo==YWYMIMO_LOGO)
	for (i = 0; i < 17; i++)
{
	for(j = 0; j < 67; j++)
		{
			if(i >= 11)
			{
				Osd_SetTextMonoColor(4, 0);
			}
			else
			{
				if((j <= 18) || (j >= 23 && j <= 43) || (i <= 6 && j >= 55) || (i == 4 && j >= 53) || (i == 5 && (j >= 50 && j <= 65)) || (i == 7 && (j >= 57 && j <= 61)))
				{
					Osd_SetTextMonoColor(2, 0);
				}
				else if((j >= 19 && j <= 22) || (j >= 44 && j <= 49) || (i == 3 && (j >= 50 && j <= 52)) || (i == 8 && j == 55) || ((i >= 9 && i <= 10) && (j >= 50 && j <= 58)))
				{
					Osd_SetTextMonoColor(3, 0);
				}
				else if((i == 3 && (j >= 53 && j <= 54)) || (i == 4 && (j >= 50 && j <= 52)) || (i == 7 && (j >= 55 && j <= 56)) || (i == 8 && (j >= 56 && j <= 58)))
				{
					Osd_Set256TextColor(0x00, Color_2);
				}
			}
			Osd_DrawCharDirect(j, i, strYWYMIMWindow[i][j]);
		}
	}
	#elif (DisplayLogo==YWYPOLY_LOGO)
	for(i = 0; i < 17; i++)
{
	for(j = 0; j < 42; j++)
		{
			if(i >= 11 || (i <= 10 && j <= 31))
			{
				Osd_SetTextMonoColor(1, 0);
			}
			else if(i <= 6 && j >= 32)
			{
				Osd_SetTextMonoColor(2, 0);
			}
			else if((i >= 7 && i <= 10) && j >= 32)
			{
				Osd_SetTextMonoColor(4, 0);
			}
			Osd_DrawCharDirect(j, i, strAPOWindow[i][j]);
		}
	}
	OSD_TEXT_HI_ADDR_SET_BIT8();
	for(i = 0; i < 17; i++)
{
	for(j = 0; j < 38; j++)
		{
			if(i >= 11 || (i <= 10 && j >= 7) || ((i >= 9 && i <= 10) && (j >= 4 && j <= 6)))
			{
				Osd_SetTextMonoColor(1, 0);
			}
			else if((i <= 7 && j <= 6) || (i == 8 && (j >= 4 && j <= 6)))
			{
				Osd_SetTextMonoColor(3, 0);
			}
			else if((i >= 8 && i <= 10) && j <= 3)
			{
				Osd_SetTextMonoColor(4, 0);
			}
			Osd_DrawCharDirect(j + 42, i, strBPOWindow[i][j]);
		}
	}
	OSD_TEXT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==CHANG_LOGO)
	for (i = 0; i < 7; i++)
{
	for (j = 0; j < 40; j++)
		{
			Osd_SetTextMonoColor(1, 0);
			Osd_DrawCharDirect(j, i, strAHUWindow[i][j]);
		}
	}
	OSD_TEXT_HI_ADDR_SET_BIT8();
	for (i = 0; i < 5; i++)
{
	for (j = 0; j < 40; j++)
		{
			Osd_SetTextMonoColor(2, 0);
			Osd_DrawCharDirect(j, i + 7, strBHUWindow[i][j]);
		}
	}
	OSD_TEXT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo == YWY_LOGO)
	for (i = 0; i < 15; i++)
{
	for(j = 0; j < 80; j++)
		{
			if(j >= 28 && j <= 51)
			{
				Osd_SetTextMonoColor(3, 2); //色板选色
				Osd_DrawCharDirect(j, i, strYWYWindow[i][j]);
			}
			else
			{
				Osd_SetTextMonoColor(1, 0);
				Osd_DrawCharDirect(j, i, strYWYWindow[i][j]);
			}
		}
	}
	#elif (DisplayLogo == TEST_LOGO)
	for (i = 0; i < 8; i++)
{
	for(j = 0; j < 35 ; j++)
		{
			Osd_SetTextMonoColor(0, 1); //
			Osd_DrawCharDirect(j, i, strLEFWindow[i][j]);
		}
	}
	#elif (DisplayLogo == EOE_LOGO)
	for (i = 0; i < 15; i++)
{
	for(j = 0; j < 80; j++)
		{
			if(j >= 28 && j <= 51)
			{
				Osd_SetTextMonoColor(3, 2); //色板选色
				Osd_DrawCharDirect(j, i, strEOEWindow[i][j]);
			}
			else
			{
				Osd_SetTextMonoColor(1, 0);
				Osd_DrawCharDirect(j, i, strEOEWindow[i][j]);
			}
		}
	}
	#elif (DisplayLogo==HUANGHE_LOGO)
	for (i = 0; i < 7; i++)
{
	for (j = 0; j < 40; j++)
		{
			Osd_SetTextMonoColor(1, 0);
			Osd_DrawCharDirect(j, i, strAHUWindow[i][j]);
		}
	}
	OSD_TEXT_HI_ADDR_SET_BIT8();
	for (i = 0; i < 5; i++)
{
	for (j = 0; j < 40; j++)
		{
			Osd_SetTextMonoColor(2, 0);
			Osd_DrawCharDirect(j, i + 7, strBHUWindow[i][j]);
		}
	}
	OSD_TEXT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==MIMO_LOGO)
	for (i = 0; i < 17; i++)
{
	for(j = 0; j < 67; j++)
		{
			if(i >= 11)
			{
				Osd_SetTextMonoColor(4, 0);
			}
			else
			{
				if((j <= 18) || (j >= 23 && j <= 43) || (i <= 6 && j >= 55) || (i == 4 && j >= 53) || (i == 5 && (j >= 50 && j <= 65)) || (i == 7 && (j >= 57 && j <= 61)))
				{
					Osd_SetTextMonoColor(2, 0);
				}
				else if((j >= 19 && j <= 22) || (j >= 44 && j <= 49) || (i == 3 && (j >= 50 && j <= 52)) || (i == 8 && j == 55) || ((i >= 9 && i <= 10) && (j >= 50 && j <= 58)))
				{
					Osd_SetTextMonoColor(3, 0);
				}
				else if((i == 3 && (j >= 53 && j <= 54)) || (i == 4 && (j >= 50 && j <= 52)) || (i == 7 && (j >= 55 && j <= 56)) || (i == 8 && (j >= 56 && j <= 58)))
				{
					Osd_Set256TextColor(0x00, Color_2);
				}
			}
			Osd_DrawCharDirect(j, i, strMIOWindow[i][j]);
		}
	}
	#elif (DisplayLogo==POLY_LOGO)
	for(i = 0; i < 17; i++)
{
	for(j = 0; j < 42; j++)
		{
			if(i >= 11 || (i <= 10 && j <= 31))
			{
				Osd_SetTextMonoColor(1, 0);
			}
			else if(i <= 6 && j >= 32)
			{
				Osd_SetTextMonoColor(2, 0);
			}
			else if((i >= 7 && i <= 10) && j >= 32)
			{
				Osd_SetTextMonoColor(4, 0);
			}
			Osd_DrawCharDirect(j, i, strAPOWindow[i][j]);
		}
	}
	OSD_TEXT_HI_ADDR_SET_BIT8();
	for(i = 0; i < 17; i++)
{
	for(j = 0; j < 38; j++)
		{
			if(i >= 11 || (i <= 10 && j >= 7) || ((i >= 9 && i <= 10) && (j >= 4 && j <= 6)))
			{
				Osd_SetTextMonoColor(1, 0);
			}
			else if((i <= 7 && j <= 6) || (i == 8 && (j >= 4 && j <= 6)))
			{
				Osd_SetTextMonoColor(3, 0);
			}
			else if((i >= 8 && i <= 10) && j <= 3)
			{
				Osd_SetTextMonoColor(4, 0);
			}
			Osd_DrawCharDirect(j + 42, i, strBPOWindow[i][j]);
		}
	}
	OSD_TEXT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==DRAGON_LOGO)
	for(i = 0; i < 23; i++)
{
	for(j = 0; j < 39; j++)
		{
			if(PalDRA[i][j] >= 0x04)      //为甚要大于等于0x04?
			{
				Osd_SetTextMonoColor((PalDRA[i][j] + 1), PalDRA[i][j]);
			}
			else
			{
				Osd_Set256TextColor((PalDRA[i][j] >> 2), Color_4); //既然是四色取色，PalDRA[i][j]右移的作用?
			}
			if(strDRAWindow[i][j] > 0xFF)
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, strDRAWindow[i][j] - 0x100);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else
			{
				Osd_DrawCharDirect(j, i, strDRAWindow[i][j]);
			}
		}
	}
	#elif (DisplayLogo==LOGO_LONG)
	for(i = 0; i < 23; i++)
{
	for(j = 0; j < 39; j++)
		{
			if(PalLON[i][j] >= 0x04)
			{
				Osd_SetTextMonoColor((PalLON[i][j] + 1), PalLON[i][j]);
			}
			else
			{
				Osd_Set256TextColor((PalLON[i][j] >> 2), Color_4);
			}
			if(strLONWindow[i][j] > 0xFF)
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, strLONWindow[i][j] - 0x100);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else
			{
				Osd_DrawCharDirect(j, i, strLONWindow[i][j]);
			}
		}
	}
	#elif (DisplayLogo==LOGO_ZEI)
	for(i = 0; i < 20; i++)
{
	for(j = 0; j < 35; j++)
		{
			if(Palhai[i][j] >= 0x08)
			{
				Osd_SetTextMonoColor((Palhai[i][j] + 1), Palhai[i][j]);
			}
			else
			{
				Osd_Set256TextColor((Palhai[i][j] >> 2), Color_4);
			}
			if(strhaiWindow[i][j] > 0xFF)
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, strhaiWindow[i][j] - 0x100);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else
			{
				Osd_DrawCharDirect(j, i, strhaiWindow[i][j]);
			}
		}
	}
	#elif (DisplayLogo==LOGO_SUO2)
	Osd_SetTextMonoColor(1, 0);
	for (i = 0; i < 26; i++)
{
	for (j = 0; j < 46; j++)
		{
			if(strsuoWindow[i][j] > 255)
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, strsuoWindow[i][j] - 0x100);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else Osd_DrawCharDirect(j, i, strsuoWindow[i][j]);
		}
	}
	#elif (DisplayLogo==LOGO_SUO)
	for(i = 0; i < 26; i++)
{
	for(j = 0; j < 45; j++)
		{
			if(Palsuo[i][j] == 0x20)
			{
				Osd_SetTextMonoColor(1, 2);
			}
			else	 if(Palsuo[i][j] > 0x20)
			{
				Osd_SetTextMonoColor(Palsuo[i][j] - 0x20 + 1, Palsuo[i][j] - 0x20);
			}
			/*if(Palsuo[i][j] == 0x22)
			{
			Osd_SetTextMonoColor(3,2);
			}
			else if(Palsuo[i][j] == 0x24)
			{
			Osd_SetTextMonoColor(5,4);
			}
			else if(Palsuo[i][j] == 0x26)
			{
			Osd_SetTextMonoColor(7,6);
			}*/
			else
			{
				Osd_Set256TextColor(((Palsuo[i][j] + 10) >> 2), Color_4);
			}
			if(strsuoWindow[i][j] >= 0x100 && strsuoWindow[i][j] <= 0x198)
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, strsuoWindow[i][j] - 0x100);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else if(strsuoWindow[i][j] >= 0x199)
			{
				OSD_TEXT_HI_ADDR_SET_BIT9();
				Osd_DrawCharDirect(j, i, strsuoWindow[i][j] - 0x199);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else
			{
				Osd_DrawCharDirect(j, i, strsuoWindow[i][j]);
			}
		}
	}
	#elif (DisplayLogo==LOGO_YINGYAN)
	for(i = 0; i < 32; i++)
{
	for(j = 0; j < 40; j++)
		{
			if(Palyin[i][j] >= 0x04)
			{
				if(i == 31 && j == 16)
					Osd_SetTextMonoColor(1, 0);
				else if(i == 31 && j == 17)
					Osd_SetTextMonoColor(1, 0);
				else Osd_SetTextMonoColor((Palyin[i][j] + 1), Palyin[i][j]);
			}
			else
			{
				if(i == 11 && j == 15)
					Osd_SetTextMonoColor(3, 1);
				else Osd_Set256TextColor((Palyin[i][j] >> 2), Color_4);
			}
			if(stryinWindow[i][j] < 0x100)
			{
				Osd_DrawCharDirect(j, i, stryinWindow[i][j]);
			}
			else if(stryinWindow[i][j] < 0x200 && stryinWindow[i][j] > 0xFF)
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, stryinWindow[i][j] - 0xFF);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else  if(stryinWindow[i][j] < 0x209 && stryinWindow[i][j] > 0x1FF)
			{
				OSD_TEXT_HI_ADDR_SET_BIT9();
				Osd_DrawCharDirect(j, i, stryinWindow[i][j] - 0x200);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else
			{
				OSD_TEXT_HI_ADDR_SET_BIT9();
				Osd_DrawCharDirect(j, i, stryinWindow[i][j] - 0x1FF);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
		}
	}
	#elif (DisplayLogo==LOGO_AI)
	for(i = 0; i < 14; i++)
{
	for(j = 0; j < 36; j++)
		{
			if(PalAI7[i][j] >= 0x08)
			{
				Osd_SetTextMonoColor((PalAI7[i][j] + 1), PalAI7[i][j]);
			}
			else
			{
				Osd_Set256TextColor((PalAI7[i][j] >> 2), Color_4);
			}
			if(strAI7Window[i][j] > 0xFF)
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, strAI7Window[i][j] - 0x100);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else
			{
				Osd_DrawCharDirect(j, i, strAI7Window[i][j]);
			}
		}
	}
	#elif (DisplayLogo==LOGO_NIAO)
	/*
		for(i = 0;i < 13;i++)
		{
			for(j = 0;j < 32;j++)
			{
				if(Palvie[i][j] >= 0x98)
				{
					Osd_Set256TextColor((Palvie[i][j]-0x98),Color_2);
				}
				else
				{
					Osd_Set256TextColor(((Palvie[i][j]+0x98) >> 2), Color_4);
				}
				if(strvieWindow[i][j] <0x6D)
				{
					Osd_DrawCharDirect(j, i, strvieWindow[i][j]);
				}
				else
				{
					OSD_TEXT_HI_ADDR_SET_BIT8();
					Osd_DrawCharDirect(j, i, strvieWindow[i][j]-0x100);
					OSD_TEXT_HI_ADDR_CLR_TO_0();
				}
			}
		}*/
	msWriteByteMask(OSD2_23, 0, BIT7);//修改使用属性
	for (i = 0; i < 13; i++)
for (j = 0; j < 32; j++)
{
	//OsdFontColor=Palvie[i][j];
	Osd_Set256TextColor((Palvie[i][j]), Color_2);//直接取色，不分四色两色
		if(strvieWindow[i][j] <= 0x6c)
			Osd_DrawCharDirect(j, i, strvieWindow[i][j]);//画第一页的两色部分
		else
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect(j, i, strvieWindow[i][j] - 0x100); //画第二页的四色部分
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
	}
	msWriteByteMask(OSD2_23, 1, BIT7);//恢复
	#elif (DisplayLogo==LOGO_DUNPAI)
	for(i = 0; i < 30; i++)
{
	for(j = 0; j < 42; j++)
		{
			if(PalBUB[i][j] >= 0x08)
			{
				if(PalBUB[i][j] == 0x10)
					Osd_SetTextMonoColor(0x0A, 0x0C);
				else
					Osd_SetTextMonoColor((PalBUB[i][j] + 1), PalBUB[i][j]);
			}
			else
			{
				Osd_Set256TextColor((PalBUB[i][j] >> 2), Color_4);
			}
			if(strBUBWindow[i][j] > 0xFF && strBUBWindow[i][j] < 0x1DD)
			{
				if(strBUBWindow[i][j] < 0x165)
				{
					OSD_TEXT_HI_ADDR_SET_BIT8();
					Osd_DrawCharDirect(j, i, strBUBWindow[i][j] - 0xFF);
					OSD_TEXT_HI_ADDR_CLR_TO_0();
				}
				else
				{
					OSD_TEXT_HI_ADDR_SET_BIT8();
					Osd_DrawCharDirect(j, i, strBUBWindow[i][j] - 0x100);
					OSD_TEXT_HI_ADDR_CLR_TO_0();
				}
			}
			else if(strBUBWindow[i][j] > 0x1DC)
			{
				OSD_TEXT_HI_ADDR_SET_BIT9();
				Osd_DrawCharDirect(j, i, strBUBWindow[i][j] - 0x1DC);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else
			{
				Osd_DrawCharDirect(j, i, strBUBWindow[i][j]);
			}
		}
	}
	#elif (DisplayLogo==YMH_LOGO)
	for(i = 0; i < 14; i++)
{
	for(j = 0; j < 47; j++)
		{
			if(PalL_0[i][j] >= 0x04)
			{
				Osd_SetTextMonoColor((PalL_0[i][j] + 1), PalL_0[i][j]);
			}
			else
			{
				Osd_Set256TextColor((PalL_0[i][j] >> 2), Color_4);
			}
			if(strL_0Window[i][j] > 0xFF)
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, strL_0Window[i][j] & 0xFF);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else
			{
				Osd_DrawCharDirect(j, i, strL_0Window[i][j]);
			}
		}
	}
	for(i = 0; i < 14; i++)
{
	for(j = 0; j < 47; j++)
		{
			Osd_SetTextMonoColor(0x09, 0x08);
			OSD_TEXT_HI_ADDR_SET_BIT9();
			Osd_DrawCharDirect(j, i, strR_0Window[i][j] & 0xFF);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
	}
	#elif (DisplayLogo==YWYLBS_LOGO)
	for(i = 0; i < 30; i++)
{
	for(j = 0; j < 42; j++)
		{
			if(PalBUB[i][j] >= 0x08)
			{
				if(PalBUB[i][j] == 0x10)
					Osd_SetTextMonoColor(0x0A, 0x0C);
				else
					Osd_SetTextMonoColor((PalBUB[i][j] + 1), PalBUB[i][j]);
			}
			else
			{
				Osd_Set256TextColor((PalBUB[i][j] >> 2), Color_4);
			}
			if(strBUBWindow[i][j] > 0xFF && strBUBWindow[i][j] < 0x1DD)
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, strBUBWindow[i][j] & 0xFF);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else if(strBUBWindow[i][j] > 0x1DC)
			{
				OSD_TEXT_HI_ADDR_SET_BIT9();
				Osd_DrawCharDirect(j, i, strBUBWindow[i][j] - 0x1DD);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else
			{
				Osd_DrawCharDirect(j, i, strBUBWindow[i][j]);
			}
		}
	}
	#elif (DisplayLogo==LOGO_LUFEI2)
	Osd_SetTextMonoColor(1, 0);
	for (i = 0; i < 30; i++)
{
	for (j = 0; j < 45; j++)
		{
			if(strlufWindow[i][j] > 255)
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, strlufWindow[i][j] - 255);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else Osd_DrawCharDirect(j, i, strlufWindow[i][j]);
		}
	}
	#elif (DisplayLogo==LOGO_AISI)
	Osd_SetTextMonoColor(1, 0);
	for (i = 0; i < 29; i++)
{
	for (j = 0; j < 35; j++)
		{
			if(straisWindow[i][j] < 0x100)
			{
				Osd_DrawCharDirect(j, i, straisWindow[i][j]);
			}
			else
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, straisWindow[i][j] - 0xFF);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
		}
	}
	#elif (DisplayLogo==LOGO_AISI2)
	for(i = 0; i < 29; i++)
{
	for(j = 0; j < 35; j++)
		{
			if(Palais[i][j] >= 0x1C)
			{
				if(Palais[i][j] == 0x1C)
					Osd_SetTextMonoColor(1, 0);
				else Osd_SetTextMonoColor(Palais[i][j] + 1, Palais[i][j]);
				. = -
			}
			else
			{
				Osd_Set256TextColor((Palais[i][j] >> 2), Color_4);
			}
			if(straisWindow[i][j] >= 0x100 && straisWindow[i][j] < 0x1F4)
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, straisWindow[i][j] - 0x100);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else if(straisWindow[i][j] >= 0x1F4)
			{
				OSD_TEXT_HI_ADDR_SET_BIT9();
				Osd_DrawCharDirect(j, i, straisWindow[i][j] - 0x1F4);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else
			{
				Osd_DrawCharDirect(j, i, straisWindow[i][j]);
			}
		}
	}
	#elif (DisplayLogo==LOGO_LUFEI)
	Osd_SetTextMonoColor(1, 0);
	for (i = 0; i < 27; i++)
{
	for (j = 0; j < 32; j++)
		{
			if(strlufWindow[i][j] > 255)
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, strlufWindow[i][j] - 255);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else Osd_DrawCharDirect(j, i, strlufWindow[i][j]);
		}
	}
	#elif (DisplayLogo==LOGO_BAIHUZI)
	Osd_SetTextMonoColor(1, 0);
	for (i = 0; i < 24; i++)
{
	for (j = 0; j < 38; j++)
		{
			Osd_DrawCharDirect(j, i, strbaiWindow[i][j]);
		}
	}
	#elif (DisplayLogo==LOGO_CAOMAO)
	Osd_SetTextMonoColor(1, 0);
	for (i = 0; i < 21; i++)
{
	for (j = 0; j < 53; j++)
		{
			if(strcaoWindow[i][j] < 0x100)
				Osd_DrawCharDirect(j, i, strcaoWindow[i][j]);
			else
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, strcaoWindow[i][j] - 0xFF);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
		}
	}
	#elif (DisplayLogo==ViewSync_LOGO)
	for(i = 0; i < 15; i++)
{
	for(j = 0; j < 60; j++)
		{
			if(PalSYN[i][j] >= 0x08)
			{
				if(PalSYN[i][j] == 0x10)
					Osd_SetTextMonoColor(0x0D, 0x09);
				else
					Osd_SetTextMonoColor((PalSYN[i][j] + 1), PalSYN[i][j]);
			}
			else
			{
				Osd_Set256TextColor((PalSYN[i][j] >> 2), Color_4);
			}
			if(strSYNWindow[i][j] <= 0xFF)
			{
				Osd_DrawCharDirect(j, i, strSYNWindow[i][j]);
			}
			else if(strSYNWindow[i][j] > 0xFF && strSYNWindow[i][j] < 0x125)
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, strSYNWindow[i][j] - 0xFF);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, strSYNWindow[i][j] - 0x100);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
		}
	}
	#elif (DisplayLogo==Vison_LOGO)
	for(i = 0; i < 22; i++)
{
	for(j = 0; j < 60; j++)
		{
			if(PalVIS[i][j] >= 0x08)
			{
				if(PalVIS[i][j] == 0x10)
					Osd_SetTextMonoColor(0x0D, 0x0F);
				else
					Osd_SetTextMonoColor((PalVIS[i][j] + 1), PalVIS[i][j]);
			}
			else
			{
				Osd_Set256TextColor((PalVIS[i][j] >> 2), Color_4);
			}
			if(strVISWindow[i][j] <= 0xFF)
			{
				Osd_DrawCharDirect(j, i, strVISWindow[i][j]);
			}
			else if(strVISWindow[i][j] > 0xFF && strVISWindow[i][j] < 0x13D)
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, strVISWindow[i][j] - 0xFF);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else
			{
				OSD_TEXT_HI_ADDR_SET_BIT8();
				Osd_DrawCharDirect(j, i, strVISWindow[i][j] - 0x100);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
		}
	}
	#elif (DisplayLogo==DAHUA_LOGO)
	for(i = 0; i < 6; i++)
{
	for(j = 0; j < 29 ; j++)
		{
			if(PalDAH[i][j] >= 0x04)
			{
				Osd_SetTextMonoColor((PalDAH[i][j] + 1), PalDAH[i][j]);
			}
			else
			{
				Osd_Set256TextColor((PalDAH[i][j] >> 2), Color_4);
			}
			Osd_DrawCharDirect(j, i, strDAHWindow[i][j]);
		}
	}
	#elif (DisplayLogo==LOGO_ELECTROMAN)
	Osd_SetTextMonoColor(2, 3);
	for (i = 0; i < 14; i++)
for(j = 0; j < 40; j++)
{
	Osd_DrawCharDirect(j, i, strEl_Window[i][j]);
	}
	OSD_TEXT_HI_ADDR_SET_BIT8();
	for (i = 0; i < 14; i++)
for(j = 0; j < 40; j++)
{
	Osd_DrawCharDirect(j, (i + 14), strEl2_Window[i][j]);
	}
	OSD_TEXT_HI_ADDR_CLR_TO_0();
	#elif (DisplayLogo==TCL_Logo)
	for (i = 0; i < 19; i++)
for(j = 0; j < 32; j++)
{
	if(i <= 12)
		{
			if((i == 0 && j < 5) || (i == 1 && j < 2) || (i == 2 && j == 0))
				OsdFontColor = 0x72;
			else
				OsdFontColor = 0x82;
		}
		else
		{
			OsdFontColor = 0x78;
		}
		Osd_DrawCharDirect(j, i, strTCLWindow[i][j]);
	}
	#elif (DisplayLogo==TOPSYNC_LOGO)
	OsdFontColor = 0x87;
	for (i = 0; i < 5; i++) //(i=0; i<8; i++)
for(j = 0; j < 61; j++) //(j=0; j<90; j++)
{
	Osd_DrawCharDirect(j, i, strtopWindow[i][j]);
	}
	#elif DisplayLogo==LOGO_DULLDOG
	OsdFontColor = 0x12;
	for (i = 0; i < 31; i++)
for(j = 0; j < 44; j++)
{
	if(strbulWindow[i][j] > 0xFF)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect(j, i, strbulWindow[i][j] - 0xFF);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		else
			Osd_DrawCharDirect(j, i, strbulWindow[i][j]);
	}
	#elif DisplayLogo==LOGO_XSTAR
	OsdFontColor = 0x87;
	for (i = 0; i < 9; i++) //(i=0; i<8; i++)
for(j = 0; j < 42; j++) //(j=0; j<90; j++)
{
	Osd_DrawCharDirect(j, i, strXSTWindow[i][j]);
	}
	#elif (DisplayLogo==OGNENTUS_LOGO)
	OsdFontColor = 0x87;
	for (i = 0; i < 11; i++) //(i=0; i<8; i++)
for(j = 0; j < 72; j++) //(j=0; j<90; j++)
{
	Osd_DrawCharDirect(j, i, strOGNWindow[i][j]);
	}
	#elif (DisplayLogo==HUNTKEYLOGO)
	Osd_SetTextMonoColor(0, CP_BlackColor);
	for (i = 0; i < OsdWindowHeight; i++)
{
	Osd_DrawRealStr_F(0, i, HUNTKEYLogoText[i]);
	}
	#elif (DisplayLogo==SANXINGLOGO)
	Osd_SetTextMonoColor(0x08, CP_BlueColor);
	for (i = 0; i < 12; i++)
for(j = 0; j < 60; j++)
{
	Osd_DrawCharDirect(j, i, strSANWindow[i][j]);
	}
	#elif (DisplayLogo==TogetherLOGO)
	for (i = 0; i < OsdWindowHeight; i++)
{
	Osd_DrawRealStr_F(0, i, TogetherLogoText[i]);
	}
	#elif (DisplayLogo==NECLOGO)
	Osd_SetTextMonoColor(0x01, 0x08);
	for (i = 0; i < OsdWindowHeight; i++)
{
	Osd_DrawRealStr_F(0, i, NECLogoText[i]);
	}
	#elif (DisplayLogo==DAHUALOGO)
	for(i = 0; i < 16; i++)
for(j = 0; j < 31; j++)
{
	if((i >= 0 && i <= 2)\
		        || ((i == 3) && ((j >= 6 && j <= 11) || (j >= 20 && j <= 29)))\
		        || ((i == 4) && ((j >= 4 && j <= 8) || (j >= 22 && j <= 29)))\
		        || ((i == 5) && ((j >= 3 && j <= 7) || (j >= 23 && j <= 28)))\
		        || ((i == 6) && ((j >= 2 && j <= 5) || (j >= 23 && j <= 28)))\
		        || ((i == 7) && ((j >= 2 && j <= 5) || (j >= 22 && j <= 27)))\
		        || ((i == 8) && ((j >= 2 && j <= 4) || (j >= 22 && j <= 27)))\
		        || ((i == 9) && ((j >= 2 && j <= 4) || (j >= 21 && j <= 26)))\
		        || ((i == 10) && ((j >= 2 && j <= 4) || (j >= 20 && j <= 25)))\
		        || ((i == 11) && (j >= 2 && j <= 5))\
		        || ((i == 12) && ((j >= 3 && j <= 7) || (j >= 15 && j <= 17)))\
		        || ((i == 13) && (j >= 4 && j <= 16))\
		        || ((i == 14) && (j >= 7 && j <= 12))
		  )
			Osd_SetTextMonoColor(CP_RedColor, CP_BlueColor);
		else if(
		    ((i == 4) && (j == 16 || j == 17))\
		    || ((i == 5) && (j == 12 || j == 13 || j == 18 || j == 19 || j == 20))\
		    || ((i == 6) && (j == 18 || j == 19 || j == 20))\
		    || ((i == 7) && (j == 14 || j == 17 || j == 18 || j == 19))\
		    || ((i == 8) && (j == 10 || j == 11 || j == 17 || j == 18 || j == 19 || j == 30))\
		    || ((i == 9) && (j == 9 || j == 10 || j == 11 || j == 16 || j == 17 || j == 18 || j == 30))\
		    || ((i == 10) && (j == 10 || j == 11 || j == 12 || j == 16 || j == 17 || j == 18 || j == 29 || j == 30))
		)
			Osd_SetTextMonoColor(CP_WhiteColor, CP_WhiteColor);
		else
			Osd_SetTextMonoColor(CP_WhiteColor, CP_BlueColor);
		Osd_DrawCharDirect(j, i, strADAWindow[i][j]);
	}
	OSD_TEXT_HI_ADDR_SET_BIT8();
	for(i = 0; i < 16; i++)
for(j = 0; j < 39; j++)
{
	Osd_SetTextMonoColor(CP_BlueColor, CP_WhiteColor);
		Osd_DrawCharDirect(j + 31, i, strMDAWindow[i][j]);
	}
	OSD_TEXT_HI_ADDR_CLR_TO_0();
	#else
	for (i = 0; i < OsdWindowHeight; i++)
{
	Osd_DrawRealStr_F(0, i, AOCLogoText[i]);
	}
	#endif
	#if (DisplayLogo==LOGO_ONEPIECE)   //海贼王
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==LOGO_LUFEI)   //海贼王
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==LOGO_LUFEI2)   //海贼王
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==LOGO_AISI)   //海贼王
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==LOGO_AISI2)   //海贼王
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==Element)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0x44, 0x98, 0xD4);
	#elif (DisplayLogo==LOGO_BAIHUZI) //白胡子
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==LOGO_BAIHUZI) //草帽
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0x00, 0x00, 0x00);
	#elif (DisplayLogo==LOGO_YINGYAN) //草帽
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==LOGO_SUO) //草帽
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==LOGO_SUO2) //草帽
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==LOGO_LONG)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0x00, 0x00, 0x00);
	#elif (DisplayLogo==LOGO_AI)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==LOGO_DUNPAI)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0x00, 0x00, 0x00);
	#elif (DisplayLogo==LOGO_ZEI)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0x00, 0x00, 0x00);
	#elif (DisplayLogo==HUNTKEYLOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==DAHUALOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0x00, 0x00, 0xFF);
	#elif (DisplayLogo==SANXINGLOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xff, 0xff, 0xff);
	#elif (DisplayLogo==LOGO_OCEAN)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0x00, 0x00, 0x00);
	#elif (DisplayLogo==CHANGHONG)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0x00, 0x00, 0x00);
	#elif (DisplayLogo==EOE_LOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==HUANGHE_LOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==MIMO_LOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==POLY_LOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==DRAGON_LOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0x00, 0x00, 0x00);
	#elif (DisplayLogo==LBS_LOGO||DisplayLogo==LOGO_NIAO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0x00, 0x00, 0x00);
	#elif (DisplayLogo==AMAZON_LOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0x00, 0x00, 0x00);
	#elif (DisplayLogo==ViewSync_LOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==Vison_LOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==DAHUA_LOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0x00, 0x00, 0x00);
	#elif (DisplayLogo==YWY_LOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==TEST_LOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0x00, 0x00, 0x00);
	#elif (DisplayLogo==CHANG_LOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==YWYPOLY_LOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==YWYMIMO_LOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0xFF, 0xFF, 0xFF);
	#elif (DisplayLogo==YWYDGM_LOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0x00, 0x00, 0x00);
	#elif (DisplayLogo==YWYLBS_LOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0x00, 0x00, 0x00);
	#elif (DisplayLogo==YMH_LOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0x00, 0x00, 0x00);
	#elif (DisplayLogo==YWYBIRD_LOGO)
	drvOSD_FrameColorEnable(TRUE);
	drvOSD_FrameColorRGB(0x00, 0x00, 0x00);
	#else
	drvOSD_FrameColorEnable(FALSE);
	#endif
	msWriteByte(BKMASKOSD1 | 0x29, 0x00); //reserve
	msWriteByte(BKMASKOSD1 | 0x2f, 0x00); //reserve
}
#endif


void Osd_LoadFacoryFontCP(void)
{
	Load256ColorPalette(0, 0, &tOSDColorPaletteF, sizeof( tOSDColorPaletteF ) / sizeof(ColorPaletteType) );
	#if CHIP_ID==CHIP_TSUMV
	mStar_LoadCompressedFont( 0x20, &tFactoryFont0, 0 );
	mStar_LoadCompressedFont( 0x2D, &tFactoryFont1, 0 );
	mStar_LoadCompressedFont( 0x30, &tFactoryFont_Number, 0 );
	mStar_LoadCompressedFont( 0x41, &tFactoryFont_EnglishBig, 0 );
	mStar_LoadCompressedFont( 0x61, &tFactoryFont_EnglishSmall, 0 );
	#else
	mStar_LoadCompressedFont( GET_FONT_RAM_ADDR(0x20), &tFactoryFont0, 0 );
	mStar_LoadCompressedFont( GET_FONT_RAM_ADDR(0x2D), &tFactoryFont1, 0 );
	mStar_LoadCompressedFont( GET_FONT_RAM_ADDR(0x30), &tFactoryFont_Number, 0 );
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x41), &tFactoryFont_EnglishBig, 0 );
	mStar_LoadCompressedFont(GET_FONT_RAM_ADDR(0x61), &tFactoryFont_EnglishSmall, 0 );
	#endif
}

void Osd_DrawRealStr_F(BYTE xPos, BYTE yPos, BYTE *str)
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



BYTE *VersionDateText(void)
{
	return strVersionDate;
}
BYTE *ChangeDateText(void)
{
	return strChangeDate;
}

#ifdef  Brand
BYTE *BrandNameText(void)
{
	return strBrandName;
}
#endif

BYTE *ModelNameText(void)
{
	return strModelName;
}
BYTE *ChipNameText( void )
{
	return strChipName;
}

#ifdef  BoardName
BYTE *BoardNameText(void)
{
	return BoardName;
}
#endif

#if Enable_Factory_Panel
BYTE *PanelText(void)
{
	return strPanel;
}
#endif


BYTE *CheckSumText(void)
{
	return strCheckSum;
}

#if AboutDSUBFunc_Enable
BYTE *AutoColorMenuText(void)
{
	return strAutoColor;
}

BYTE *PassText(void)
{
	return strPass;
}

BYTE *FailText(void)
{
	return strFail;
}


BYTE *AutoColorText(void)
{
	return strAutoColor;
}
BYTE *AdcGainText(void)
{
	return strAdcGain;
}
BYTE *AdcOffsetText(void)
{
	return strAdcOffset;
}
#endif
BYTE *FactoryRedText(void)
{
	return strFactoryRed;
}
BYTE *FactoryGreenText(void)
{
	return strFactoryGreen;
}
BYTE *FactoryBlueText(void)
{
	return strFactoryBlue;
}

BYTE *COOL1Text(void)
{
	return strFCool1;
}
BYTE *WARM1Text(void)
{
	return strFWarm1;
}
#if CT_sRGB_ENABLE
BYTE *sRGBText(void)
{
	return strFsRGB;
}
#endif
#if CT_7500K_ENABLE
BYTE *NORMALText(void)
{
	return strFNORMAL;
}
#endif
BYTE *BurninText(void)
{
	return strBurnin;
}

#if ENABLE_FACTORY_BLACKLEVEL
BYTE * FacBlacklevelText(void)
{
	return strBlacklevelText;
}
#endif

BYTE *F_BackLightText(void)
{
	return strBackLight;
}
BYTE *F_HourText(void)
{
	return strHour;
}

BYTE *F_MinText(void)
{
	return strMinute;
}


#if !USEFLASH // 130829 larry
BYTE *EraseEEPROMText(void)
{
	return strEraseEEPROM;
}
#endif
#if F_ShowVsync_Enable
BYTE *FreeSyncVsyncText(void)
{
	return strFreeSyncVsync;
}
#endif

#if Enable_ProductModeAdjust
BYTE *ProductModeText(void)
{
	return strDFM;
}
BYTE *ProductModeOnOffText(void)
{
	return  (strOnOff[0]);
}
#endif

BYTE *BurninOnOffText(void)
{
	return (BurninModeFlag) ? (strOnOff[1]) : (strOnOff[0]);
}

#if 0//DisplayPowerOnLogo
BYTE *LogoOnOffText(void)
{
	return (UserPrefLogoON) ? (strOnOff[1]) : (strOnOff[0]);
}
#endif

#if PanelminiLVDS || PANEL_VCOM_ADJUST	//110229 Modify
BYTE *VCOMText(void)
{
	return strVCOM;
}
#endif


#if ENABLE_FACTORY_SSCADJ	//120305 Modify
BYTE *SpreadSpectrumText( void )
{
	return strSpreadSpectrum;
}
BYTE *FreqText( void )
{
	return strFreq;
}
BYTE *AmpText( void )
{
	return strAmp;
}
#endif




