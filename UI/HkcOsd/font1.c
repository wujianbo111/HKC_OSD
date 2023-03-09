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
//#include "font.h"
#include "font1.h"
#include "extlib.h"
#include "MsID_V1.h"


void DynamicLoadHotIconFont_ECO( void )	//120713 Modify
{
	if( UserPrefECOMode == ECO_Standard )
	{
		LoadCompressColorFont(&tDCRStandardIconFont, NULL, 12);
	}
	else if( UserPrefECOMode == ECO_Internet )
	{
		LoadCompressColorFont(&tECOWebIconFont, NULL, 12);
	}
	else if( UserPrefECOMode == ECO_Game )
	{
		LoadCompressColorFont(&tECOGameIconFont, NULL, 12);
	}
	#if ENABLE_FPS_RTS
	else if(UserPrefECOMode == ECO_FPS)
	{
		LoadCompressColorFont( &tECOFPSIconFont, NULL, 12);
	}
	else if(UserPrefECOMode == ECO_RTS)
	{
		LoadCompressColorFont( &tECORTSIconFont, NULL, 12);
	}
	#endif
	else if( UserPrefECOMode == ECO_Movie)
	{
		LoadCompressColorFont(&tECOMovieIconFont, NULL, 12);
	}
	#if	PresetMode_Enable
	else if( UserPrefECOMode == ECO_Preset)
	{
		LoadCompressColorFont(&tECOPresetModeIconFont, NULL, 12);
	}
	#endif
}



void Osd_Load8ColorFont2(BYTE u8Addr, BYTE *pu8Font, WORD u16Num)
{
	#if CHIP_ID>=CHIP_TSUMV
	DWORD xdata u32Data;
	BYTE xdata u8FontData0, u8FontData1, u8FontData2;
	BYTE xdata u8PixelBit;
	BYTE xdata i;
	#if CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF
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
	#if CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF
	msWriteByteMask(OSD1_6D, 0x00, BIT7 | BIT6); //00: for 1/2Bpp; 01: for 3Bpp; 10:for 4Bpp;
	#elif  CHIP_ID==CHIP_TSUM2||CHIP_ID==CHIP_TSUMV
	msWriteByteMask(OSD1_6D, 0x00, BIT7);         //0: for 1/2/3Bpp; 1: for 4Bpp;
	#endif
	#else
	msWriteByte(OSD2_A3, u8Addr);
	while (u16Num--)
		msWriteByte(OSD2_A4, *(pu8Font++));
	#endif
}
#if CHIP_ID>=CHIP_TSUMV

void Load256ColorPalette2(BYTE u8Group, BYTE u8Addr, ColorPaletteType *colorPtr, WORD u16Num)
{
	#if CHIP_ID>=CHIP_TSUM2
	WORD i;
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
	#else
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
	#endif
}

#else
void Load256ColorPalette2(BYTE u8Group, BYTE u8Addr, ColorPaletteType *colorPtr, WORD u16Num)
{
	WORD xdata i;
	u8Group = 0;
	msWriteByte( OSD2_AC, u8Addr );
	for (i = 0; i < u16Num; i++)
	{
		msWriteByte(OSD2_AD, ((colorPtr + i)->u8Red));
		msWriteByte(OSD2_AD, ((colorPtr + i)->u8Green));
		msWriteByte(OSD2_AD, ((colorPtr + i)->u8Blue));
	}
}

#endif


void DynamicLoadHotIconFont( void )
{
	if ( MenuPageIndex != AutoMenu
        #if HotExpansionAdjust
	        && MenuPageIndex != HotExpansionMenu
        #endif
	        && MenuPageIndex != HotKeyECOMenu
        #if Hotkey_DCR_Enable
	        && MenuPageIndex != HotKeyDCRMenu
        #endif
	   )	//110221 Modify
		return;
	#if HotExpansionAdjust
	if(MenuPageIndex == HotExpansionMenu )
		Load256ColorPalette2(0, CP_SelectIcon, &tOSDColorPalette256_HotIcon, sizeof( tOSDColorPalette256_HotIcon ) / sizeof(ColorPaletteType) );
	else
	#endif
	#if !Hotkey_ECO_Text_Enable
		if( UserPrefECOMode == ECO_Standard )
			Load256ColorPalette2(0, CP_SelectIcon, &tOSDColorPalette256_ECOStandard, sizeof( tOSDColorPalette256_ECOStandard ) / sizeof(ColorPaletteType) );
		else   if( UserPrefECOMode == ECO_Internet )
			Load256ColorPalette2(0, CP_SelectIcon, &tOSDColorPalette256_ECO_Internet, sizeof( tOSDColorPalette256_ECOStandard ) / sizeof(ColorPaletteType) );
		else   if( UserPrefECOMode == ECO_Game )
			Load256ColorPalette2(0, CP_SelectIcon, &tOSDColorPalette256_ECO_Game, sizeof( tOSDColorPalette256_ECOStandard ) / sizeof(ColorPaletteType) );
	#if ENABLE_FPS_RTS
		else   if( UserPrefECOMode == ECO_FPS )
			Load256ColorPalette2(0, CP_SelectIcon, &tOSDColorPalette256_ECO_FPS, sizeof( tOSDColorPalette256_ECOStandard ) / sizeof(ColorPaletteType) );
		else   if( UserPrefECOMode == ECO_RTS )
			Load256ColorPalette2(0, CP_SelectIcon, &tOSDColorPalette256_ECO_FPS, sizeof( tOSDColorPalette256_ECOStandard ) / sizeof(ColorPaletteType) );
	#endif
		else   if( UserPrefECOMode == ECO_Movie )
			Load256ColorPalette2(0, CP_SelectIcon, &tOSDColorPalette256_ECO_Movie, sizeof( tOSDColorPalette256_ECOStandard ) / sizeof(ColorPaletteType) );
	#if PresetMode_Enable
		else   if( UserPrefECOMode == ECO_Preset )
			Load256ColorPalette2(0, CP_SelectIcon, &tOSDColorPalette256_ECOStandard, sizeof( tOSDColorPalette256_ECOStandard ) / sizeof(ColorPaletteType) );
		else
	#endif
	#endif
		{
		}
	OSD_FONT_HI_ADDR_SET_BIT9();//0x200~0x2FF
	OSD_WRITE_FONT_ADDRESS(_4ColorHotIconStart);
	if( MenuPageIndex == HotKeyECOMenu )
	{
		#if Hotkey_ECO_Text_Enable
		DynamicLoadHotIconFont_ECO();	//120713 Modify
		#endif
	}
	#if Hotkey_DCR_Enable
	else if( MenuPageIndex == HotKeyDCRMenu )	//110221 Modify
	{
		#if !HotKey_ECO_DCR
		if( !UserPrefDcrMode )
		{
			Load256ColorPalette2(0, CP_SelectIcon, &tOSDColorPalette256_DCROFF, sizeof( tOSDColorPalette256_DCROFF ) / sizeof(ColorPaletteType) );
			LoadCompressColorFont(&tDCROFFIconFont, NULL, 12);
		}
		else
		#endif
		{
			Load256ColorPalette2(0, CP_SelectIcon, &tOSDColorPalette256_DCRON, sizeof( tOSDColorPalette256_DCRON ) / sizeof(ColorPaletteType) );
			LoadCompressColorFont(&tDCRONIconFont, NULL, 12);
		}
	}
	#endif
	#if HotExpansionAdjust
	else if( MenuPageIndex == HotExpansionMenu )
	{
		OSD_WRITE_FONT_ADDRESS(_8ColorHotIconStart);
		if( UserprefExpansionMode == Expansion_Aspect && ExpansionFlag )
		{
			Osd_Load8ColorFont2( _8ColorHotIconStart, &tIconFont_8Color_4_3, sizeof( tIconFont_8Color_4_3 ) );
		}
		else
		{
			Osd_Load8ColorFont2( _8ColorHotIconStart, &tIconFont_8Color_Wide, sizeof( tIconFont_8Color_Wide ) );
		}
	}
	#endif
	OSD_FONT_HI_ADDR_CLR_TO_0();
}

#if Hot_Corss_ColorSelect

void DynamicLoadHotCorssIcon( BYTE Mode )
{
	Mode = Mode;
	OSD_FONT_HI_ADDR_SET_BIT8();
	#if CHIP_ID>=CHIP_TSUM2
	mStar_LoadCompressedFont( GET_FONT_RAM_ADDR(CorssAddr), tOSDFont_Tree, 0 );
	#else
	mStar_LoadCompressedFont( CorssAddr, tOSDFont_Tree, 0 );
	#endif
	OSD_FONT_HI_ADDR_CLR_TO_0();
}
#elif Hot_Corss_FY_ColorSelect
void DynamicLoadHotCorssIcon( BYTE Mode )
{
	OSD_FONT_HI_ADDR_SET_BIT8();
	#if CHIP_ID>=CHIP_TSUM2
	if(Mode == 0)
		mStar_LoadCompressedFont( GET_FONT_RAM_ADDR(CorssAddr), tOSDFont_One, 0 );
	else  if(Mode == 1)
		mStar_LoadCompressedFont( GET_FONT_RAM_ADDR(CorssAddr), tOSDFont_Tow, 0 );
	else
		mStar_LoadCompressedFont( GET_FONT_RAM_ADDR(CorssAddr), tOSDFont_Tree, 0 );
	#else
	if(Mode == 0)
		mStar_LoadCompressedFont( (CorssAddr), tOSDFont_One, 0 );
	else  if(Mode == 1)
		mStar_LoadCompressedFont( (CorssAddr), tOSDFont_Tow, 0 );
	else
		mStar_LoadCompressedFont( (CorssAddr), tOSDFont_Tree, 0 );
	#endif
	OSD_FONT_HI_ADDR_CLR_TO_0();
}
#elif Hot_Corss_FND_Select
void DynamicLoadHotCorssIcon( BYTE Mode )
{
	OSD_FONT_HI_ADDR_SET_BIT8();
	#if CHIP_ID>=CHIP_TSUM2
	if(Mode == 0)
		mStar_LoadCompressedFont( GET_FONT_RAM_ADDR(CorssAddr), tOSDFont_One, 0 );
	else  if(Mode == 1)
		mStar_LoadCompressedFont( GET_FONT_RAM_ADDR(CorssAddr), tOSDFont_Tow, 0 );
	else
		mStar_LoadCompressedFont( GET_FONT_RAM_ADDR(CorssAddr), tOSDFont_Tree, 0 );
	#else
	if(Mode == 0)
		mStar_LoadCompressedFont( (CorssAddr), tOSDFont_One, 0 );
	else  if(Mode == 1)
		mStar_LoadCompressedFont( (CorssAddr), tOSDFont_Tow, 0 );
	else
		mStar_LoadCompressedFont( (CorssAddr), tOSDFont_Tree, 0 );
	#endif
	OSD_FONT_HI_ADDR_CLR_TO_0();
}
#endif



