#include "global.h"
#include "msosd.h"
#include "drvosd.h"

#include "Extlib.h"

extern  xdata BYTE  OsdFontColor;

#if CHIP_ID >= CHIP_TSUMV

void Load256ColorPalette(BYTE u8Group, BYTE u8Addr, ColorPaletteType *colorPtr, WORD u16Num)
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
#if CHIP_ID < CHIP_TSUMV
void Load256ColorPalette(BYTE u8Group, BYTE u8Addr, ColorPaletteType *colorPtr, WORD u16Num)
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



