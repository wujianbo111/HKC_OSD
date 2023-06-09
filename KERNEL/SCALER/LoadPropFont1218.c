///////////////////////////////////////////////////////////////////////////////
/// @file LoadPropFont1218.c
/// @brief
/// @author MStarSemi Inc.
///
/// The Prop. font generating and loading function.
///
/// Features
///  -Left/Center/Right Align
///  -Prop Font shift up/down
///  -Load 12x18 font format to 12x18 font RAM
///
///////////////////////////////////////////////////////////////////////////////


#define _LOADPROPFONT1218_C

#include <stddef.h>
#include "LoadPropFont1218.h"
#include "Ms_rwReg.h"
#include "board.h"
#include "Ms_Reg.h"
#include "global.h"
//#include "DebugMsg.h"

#if 1
extern void Font_Transform( BYTE u8Data );

extern WORD code tPropFontSet[];
extern WORD code tPropFontMap[];

extern void printMsg(char *str);
extern void printData(char *str, WORD value);


xdata BYTE Font_Transform_Counter = 0;
xdata BYTE Font_Transform_Type = 0;
xdata BYTE Font_Transform_Data[9] = 0;

void Font_Transform( BYTE u8Data )
{
	#if CHIP_ID>=CHIP_TSUMV
	Font_Transform_Data[Font_Transform_Counter] = u8Data;
	Font_Transform_Counter++;
	if (Font_Transform_Type == 0 && Font_Transform_Counter >= 3)
	{
		DWORD xdata u32Data = 0;
		u32Data = ((DWORD)(Font_Transform_Data[0] & 0x0F) << 20)
		          | ((DWORD)(Font_Transform_Data[0] & 0xF0) << 4)
		          | ((DWORD)Font_Transform_Data[1] << 12)
		          | ((DWORD)Font_Transform_Data[2]);
		WRITE_FONT();
		msWriteByte ( PORT_FONT_DATA, u32Data >> 16 );
		msWriteByte ( PORT_FONT_DATA, u32Data >> 8 );
		msWriteByte ( PORT_FONT_DATA, u32Data >> 0 );
		Font_Transform_Counter = 0;
	}
	else if (Font_Transform_Type == 1 && Font_Transform_Counter >= 3)
	{
		DWORD xdata u32Data = 0;
		WORD xdata u16FontIndex;
		WORD xdata u16FontData1 = ((WORD)Font_Transform_Data[1]) | ((WORD)(Font_Transform_Data[0] & 0x0F) << 8);
		WORD xdata u16FontData2 = ((WORD)Font_Transform_Data[2]) | ((WORD)(Font_Transform_Data[0] & 0xF0) << 4);
		u16FontIndex = BIT11;
		while ( u16FontIndex )
		{
			u32Data <<= 2;
			if ( u16FontData1 & u16FontIndex ) //color bit0
			{
				u32Data |= BIT0;
			}
			if ( u16FontData2 & u16FontIndex ) //color bit1
			{
				u32Data |= BIT1;
			}
			u16FontIndex >>= 1;
		}
		WRITE_FONT();
		msWriteByte ( PORT_FONT_DATA, u32Data >> 16 );
		msWriteByte ( PORT_FONT_DATA, u32Data >> 8 );
		msWriteByte ( PORT_FONT_DATA, u32Data >> 0 );
		Font_Transform_Counter = 0;
	}
	else if (Font_Transform_Type == 2 && Font_Transform_Counter >= 9)
	{
		DWORD xdata u32Data = 0;
		BYTE xdata u8FontData0, u8FontData1, u8FontData2;
		BYTE xdata u8PixelBit;
		BYTE xdata i;
		for ( i = 0; i < 3; i++ )
		{
			if ( i == 0 )
			{
				u8FontData0 = (Font_Transform_Data[0] << 4) + (Font_Transform_Data[1] >> 4);
				u8FontData1 = (Font_Transform_Data[0] & 0xF0) + (Font_Transform_Data[2] >> 4);
				u8FontData2 = (Font_Transform_Data[3] << 4) + (Font_Transform_Data[4] >> 4);
			}
			else if ( i == 1 )
			{
				u8FontData0 = (Font_Transform_Data[1] << 4) + (Font_Transform_Data[3] >> 4);
				u8FontData1 = (Font_Transform_Data[2] << 4) + (Font_Transform_Data[6] & 0x0F);
				u8FontData2 = (Font_Transform_Data[4] << 4) + (Font_Transform_Data[6] >> 4);
			}
			else
			{
				u8FontData0 = (Font_Transform_Data[5]);
				u8FontData1 = (Font_Transform_Data[7]);
				u8FontData2 = (Font_Transform_Data[8]);
			}
			u8PixelBit = BIT7;
			u32Data = 0;
			while ( u8PixelBit )
			{
				u32Data <<= 3;
				if ( u8FontData0 & u8PixelBit ) //color bit0
				{
					u32Data |= BIT0;
				}
				if ( u8FontData1 & u8PixelBit ) //color bit1
				{
					u32Data |= BIT1;
				}
				if ( u8FontData2 & u8PixelBit ) //color bit2
				{
					u32Data |= BIT2;
				}
				u8PixelBit >>= 1;
			}
			WRITE_FONT();
			msWriteByte ( PORT_FONT_DATA, u32Data >> 16 );
			msWriteByte ( PORT_FONT_DATA, u32Data >> 8 );
			msWriteByte ( PORT_FONT_DATA, u32Data );
		}
		Font_Transform_Counter = 0;
	}
	#else
	msWriteByte ( OSD2_A4, ( BYTE ) u8Data );
	#endif
}


void ClearPropFontRam ( WORD *font_ram )
{
	BYTE i;
	for ( i = 0; i < 18; i++ )
	{
		font_ram[i] = 0;
	}
}

//===================================================================================================================================================================:
WORD GetFontSpace ( BYTE index )
{
	return tPropFontSet[tPropFontMap[index + font_offset]];
}
//===================================================================================================================================================================:
void _GetPropCompressFontData ( BYTE index )
{
	WORD *pTable;
	BYTE xdata count, i, row;
	pTable = & ( tPropFontSet[tPropFontMap[index + font_offset]] );
	pTable++;
	row = 0;
	do
	{
		count = ( *pTable ) >> 12;
		for ( i = 0; i < count; i++ )
		{
			CFontData[row + i] = ( *pTable ) & 0x0fff;
		}
		row += count;
		pTable++;
	}
	while ( row < 18 );
}


//===================================================================================================================================================================:
void LoadFontRam ( WORD *font_ram )
{
	BYTE i;
	WORD font_data;
	for ( i = 0; i < 9; i++ )
	{
		font_data = ( font_ram[2 * i] >> 8 ) | ( ( font_ram[2 * i + 1] & 0xf00 ) >> 4 );
		//msWriteByte ( PORT_FONT_DATA, ( BYTE ) font_data );
		Font_Transform( ( BYTE ) font_data );
		font_data = font_ram[2 * i] & 0x0ff;
		//msWriteByte ( PORT_FONT_DATA, ( BYTE ) font_data );
		Font_Transform( ( BYTE ) font_data );
		font_data = font_ram[2 * i + 1] & 0x0ff;
		//msWriteByte ( PORT_FONT_DATA, ( BYTE ) font_data );
		Font_Transform( ( BYTE ) font_data );
	}
}

BYTE LoadCompressedPropFonts ( BYTE *font, WORD num )
{
	Bool not_prop;
	BYTE i;
	BYTE l_space, r_space, font_width;
	BYTE xdata NeedSpaceWidth;
	WORD xdata font_data;
	WORD xdata TotalFont = 0;
	WORD xdata PropFontRam[18];
	WORD xdata FontIndex = 0;
	font_offset = 0;
	#if 1
	if ( font[FontIndex] == FONT_COMMAND )
	{
		FontIndex ++;
		num--;
		font_offset = font[FontIndex] * 0x0100;
		FontIndex ++;
		num--;
	}
	#endif
	//GetPropFontTable ();
	ClearPropFontRam ( PropFontRam );
	NeedSpaceWidth = 0;
	PropFontRamWidth = INIT_WORD_SPACE;
	//PropFontRamWidth = ( BYTE ) font_shift;
	font_width = ( BYTE ) GetFontSpace ( font[FontIndex] );
	l_space = font_width >> 4;
	r_space = font_width & 0x0f;
	font_width = 12 - l_space - r_space;
	TotalFontWidth += font_width; //new
	FontUsedPixel = font_width;
	while ( num )
	{
		#if 1
		if ( font[FontIndex] == FONT_COMMAND )
		{
			FontIndex ++;
			num--;
			font_offset = font[FontIndex] * 0x0100;
			FontIndex ++;
			num--;
		}
		#endif
		_GetPropCompressFontData ( font[FontIndex] );
		for ( i = 0; i < 18; i++ )
		{
			font_data = CFontData[i];
			PropFontRam[i] = PropFontRam[i] | ( ( ( font_data << ( l_space + font_width - FontUsedPixel ) ) & 0x0fff ) >> PropFontRamWidth );
		}
		PropFontRamWidth += FontUsedPixel;
		if ( PropFontRamWidth > 12 )
		{
			FontUsedPixel = PropFontRamWidth - 12;
			PropFontRamWidth = 12;
		}
		else
		{
			FontUsedPixel = 0;
		}
		if ( FontUsedPixel == 0 )  // word finish
		{
			if ( num )
			{
				num--;
				if ( num == 0 )
				{
					TotalFont++;
					LoadFontRam ( PropFontRam );
					return ( BYTE ) TotalFont;
				}
			}
			FontIndex++;
			#if 1
			if ( font[FontIndex] == FONT_COMMAND )
			{
				FontIndex ++;
				num--;
				font_offset = font[FontIndex] * 0x0100;
				FontIndex ++;
				num--;
			}
			#endif
			if ( font[FontIndex] == 0x00 )  // new string
			{
				TotalFont++;
				LoadFontRam ( PropFontRam );
				if ( num )
				{
					num--;
					if ( num == 0 )
					{
						return ( BYTE ) TotalFont;
					}
				}
				FontIndex++;
				ClearPropFontRam ( PropFontRam );
				PropFontRamWidth = INIT_WORD_SPACE;
				NeedSpaceWidth = 0;
			}
			else  // next word
			{
				#if 1
				if ( font[FontIndex] == FONT_COMMAND )
				{
					FontIndex ++;
					num--;
					font_offset = font[FontIndex] * 0x0100;
					FontIndex ++;
					num--;
				}
				#endif
				//GetPropFontTable ();
				if ( GetFontSpace ( font[FontIndex] ) & 0x8000 )
				{
					not_prop = 1;
				}
				else
				{
					not_prop = 0;
					NeedSpaceWidth += WORD_SPACE;
					TotalFontWidth += WORD_SPACE; //new
				}
			}
			#if 1
			if ( font[FontIndex] == FONT_COMMAND )
			{
				FontIndex ++;
				num--;
				font_offset = font[FontIndex] * 0x0100;
				FontIndex ++;
				num--;
			}
			#endif
			//GetPropFontTable ();
			font_width = ( BYTE ) GetFontSpace ( font[FontIndex] );
			l_space = font_width >> 4;
			r_space = font_width & 0x0f;
			font_width = 12 - l_space - r_space;
			TotalFontWidth += font_width; //new
			FontUsedPixel = font_width;
		}
		PropFontRamWidth += NeedSpaceWidth;
		if ( PropFontRamWidth > 12 )
		{
			NeedSpaceWidth = PropFontRamWidth - 12;
			PropFontRamWidth = 12;
		}
		else
		{
			NeedSpaceWidth = 0;
		}
		if ( PropFontRamWidth == 12 )
		{
			TotalFont++;
			LoadFontRam ( PropFontRam );
			ClearPropFontRam ( PropFontRam );
			PropFontRamWidth = 0;
		}
		PropFontRamWidth += NeedSpaceWidth;
		NeedSpaceWidth = 0;
	}
	return ( BYTE ) TotalFont;
}
#else



#if PropFontUseCommonArea
extern PropFontNonCompressType code tPropFontSet[];
extern PropFontNonCompressType code tPropFontSet1[];
extern PropFontNonCompressType code tPropFontSet2[];
#endif
//#define OSD2_A3 0xA3
//#define OSD2_A4 0xA4

PropFontNonCompressType *pstPropFontSet1218;
///BIT 0~1 : pixel between font
///BIT 2~3 : align(00=left align, 01=right align, 11= center align)
BYTE g_u8PropFontFlags = SPACE2PIXEL | LEFT_ALIGN;
BYTE g_u8AlignResetIndex = 0xFF; ///start number of strings for reset align flag to left align
BYTE xdata g_u8ByPassLength = 0;
/// Shift "a font" up or down inner 12x18 dimension.
static void ShiftFontUpDown(WORD *pu16SN, BYTE u8Shift)
{
	BYTE  i;
	BYTE  u8ShiftUp;
	if(u8Shift & 0x80)
	{
		u8ShiftUp = 1;
		u8Shift &= 0x7F;
	}
	else
		u8ShiftUp = 0;
	if(u8ShiftUp)
	{
		for(i = u8Shift; i < FONT_HEIGHT; i++)
			*(pu16SN + i - u8Shift) = (*(pu16SN + i));
		for(i = (FONT_HEIGHT - u8Shift); i < FONT_HEIGHT; i++)
			*(pu16SN + i) = 0;
	}
	else//ShiftDown
	{
		for(i = (FONT_HEIGHT - u8Shift); i > 0; i--)
			*(pu16SN + i - 1 + u8Shift) = (*(pu16SN + i - 1));
		for(i = 0; i < u8Shift; i++)
			*(pu16SN + i) = 0;
	}
}

#if 0
/// Write 2 words of font data(2 line with 12 pixel width) to font RAM. ex: 0Aaa,0Bbb ===> BA,AA,BB
/// This function should be modified if use 16x16
static void WriteWord2Font(WORD u16SN1, WORD u16SN2)
{
	msWriteByte(OSD2_A4, HIBYTE(u16SN1) + (HIBYTE(u16SN2) << 4));
	msWriteByte(OSD2_A4, LOBYTE(u16SN1));
	msWriteByte(OSD2_A4, LOBYTE(u16SN2));
}
/// Load a font char(12x18) to font RAM.
/// This function should be modified if use 16x16!
void OSDLoadOneFont(WORD* pu16SN)
{
	BYTE  i;
	for(i = 0; i < (FONT_HEIGHT >> 1); i++)
		WriteWord2Font(*(pu16SN + (i << 1)), *(pu16SN + (i << 1) + 1));
}
#else
/// Load a font char(12x18) to font RAM.
/// This function should be modified if use 16x16!
void OSDLoadOneFont(WORD* pu16SN)
{
	BYTE  i;
#define u16SN1  (*(pu16SN+i))
#define u16SN2  (*(pu16SN+i+1))
	for(i = 0; i < FONT_HEIGHT; i += 2)
	{
		#if CHIP_ID>=CHIP_TSUMV
		//xxxx0000 00001111
		//xxxx1111 22222222
		MEM_MSWRITE_BYTE(PORT_FONT_DATA, (BYTE)(u16SN1 >> 4) );
		MEM_MSWRITE_BYTE(PORT_FONT_DATA, (LOBYTE(u16SN1) << 4) + HIBYTE(u16SN2));
		MEM_MSWRITE_BYTE(PORT_FONT_DATA, LOBYTE(u16SN2));
		#else
		MEM_MSWRITE_BYTE(OSD2_A4, HIBYTE(u16SN1) + (HIBYTE(u16SN2) << 4));
		MEM_MSWRITE_BYTE(OSD2_A4, LOBYTE(u16SN1));
		MEM_MSWRITE_BYTE(OSD2_A4, LOBYTE(u16SN2));
		#endif
	}
#undef u16SN1
#undef u16SN2
}
#endif

/// Clear a font char(12x18) buffer.
void ClearFontBuf(WORD* pu16SN)
{
	BYTE  i;
	#if 0
	for(i = 0; i < FONT_HEIGHT; i++)
		*(pu16SN + i) = 0;
	#else
	//Jison: Speed up
	for(i = 0; i < (FONT_HEIGHT >> 1); i++)
		*((DWORD*)pu16SN + i) = 0;
	#endif
}
/// Do OR operation between two font buffer, save the sesult to 1st buffer.
static void MergeFontBuf(WORD* pu16SN, WORD* pu16SN1)
{
	BYTE  i;
	for(i = 0; i < FONT_HEIGHT; i++)
		*(pu16SN + i) = (*(pu16SN + i)) | (*(pu16SN1 + i));
}
//BitTarLStart 0xFFF = 1111 1111 1111 sequence >>  0123 4567 89AB
/// Copy sub-part of src font (start from u8BitSrcLStart with u8BitWidth) to tar font area.
/// This function should be modified if use 16x16!
///u8BitSrcLStart is the 1st pixel position of Src font that will be merged to Tar.
///u8BitWidth is the pixel width following 1st pixel position that will be merged to.
static void CopySubFontBuf(WORD* pu16Tar, WORD*pu16Src, BYTE u8BitSrcLStart, BYTE u8BitWidth)
{
	BYTE  i;
	WORD  u16Temp;
	#if 0
	for(i = 0; i < FONT_HEIGHT; i++)
	{
		u16Temp = (*(pu16Src + i));
		u16Temp = u16Temp << u8BitSrcLStart;
		u16Temp &= 0xFFF;
		u16Temp = u16Temp >> (FONT_WIDTH - u8BitWidth);
		*(pu16Tar + i) = *(pu16Tar + i) | u16Temp;
	}
	#else //Jison, Speed up
	u8BitWidth = (FONT_WIDTH - u8BitWidth);
	for(i = 0; i < FONT_HEIGHT; i++)
	{
		u16Temp = ((((*(pu16Src + i)) << u8BitSrcLStart) & 0xFFF) >> (u8BitWidth));
		*(pu16Tar + i) |= u16Temp;
	}
	#endif
}

static BYTE GetRemainderPixelOfString(BYTE *pu8String)
{
	WORD u16PixelLen = 0;
	BYTE u8SpaceWidth;
	while(*pu8String)
	{
		u8SpaceWidth = pstPropFontSet1218[*pu8String].u8SpaceWidth;
//        u16PixelLen+=(SP_BETWEEN_FONT+FONT_WIDTH-( (pstFontData->u8SpaceWidth & 0x0F) + ((pstFontData->u8SpaceWidth & 0xF0)>>4) ));
		if ((u8SpaceWidth & 0xF0) == 0xF0)
			u16PixelLen += (FONT_WIDTH - (u8SpaceWidth & 0x0F));
		else
			u16PixelLen += (( (u8SpaceWidth & 0x0F) + ((u8SpaceWidth & 0xF0) >> 4) ) - SP_BETWEEN_FONT);
		pu8String++;
	}
	u16PixelLen %= FONT_WIDTH;
	#if 0
	u16PixelLen = FONT_WIDTH - u16PixelLen;
	return (BYTE)(u16PixelLen ? FONT_WIDTH - u16PixelLen : 0);
	#else //Jison 080109
	return ((BYTE)u16PixelLen);
	#endif
}
/// pu8Strings and pu8Strings1 are the null-terminal strings set of font indexes to PropFontNonCompressType array.
/// u16FontCount and u16FontCount1 are array size of pu8Strings and pu8Strings1 respectively.
/// u8UDShift and u8UDShift1 are the shift pixels pu8Strings and pu8Strings1, Bit 7==1 means shift up.
/// >>>Shift up/down and load single line string to font RAM if pu8Strings1==0 and u16FontCount1==0.
/// >>>Merge two font string lines to a single 18 pixels height charactor line and load to font RAM.
BYTE LoadPropFonts1218(BYTE u8Addr, BYTE *pu8Strings, WORD u16FontCount,
                       BYTE *pu8Strings1, WORD u16FontCount1, BYTE u8UDShift, BYTE u8UDShift1)
{
	PropFontNonCompressType *pstFontData;
	PropFontNonCompressType *pstFontData1;
	WORD  xdata u16StrIndex = 0, u16StrIndex1 = 0; ///The str index in pu8Strings
	BYTE  xdata u8Flags = 0;
	BYTE  xdata u8BufW = 0, u8BufW1 = 0;
	BYTE  xdata u8NextFontW = 0, u8NextFontW1 = 0;
	BYTE  xdata u8NextBit = 0, u8NextBit1 = 0;
	WORD  xdata tSN[FONT_HEIGHT]; //May cause problem if use idata. Why???
	WORD  xdata tSN1[FONT_HEIGHT];
	BYTE  xdata u8StrCount = 0;
	BYTE  xdata u8FontCnt = 0;
#define LOAD_SINGLE_LINE_BIT            BIT7
#define LOAD_SINGLE_LINE_FLAG           (u8Flags&LOAD_SINGLE_LINE_BIT)
#define SET_LOAD_SINGLE()               (u8Flags|=LOAD_SINGLE_LINE_BIT)
#define STR_1ST_CHAR_BIT                BIT0
#define STR_1ST_CHAR_FLAG               (u8Flags&STR_1ST_CHAR_BIT)
#define SET_STR_1ST_CHAR_FLAG()         (u8Flags|=STR_1ST_CHAR_BIT)
#define CLR_STR_1ST_CHAR_FLAG()         (u8Flags&=~STR_1ST_CHAR_BIT)
#define STR1_1ST_CHAR_BIT               BIT1
#define STR1_1ST_CHAR_FLAG              (u8Flags&STR1_1ST_CHAR_BIT)
#define SET_STR1_1ST_CHAR_FLAG()        (u8Flags|=STR1_1ST_CHAR_BIT)
#define CLR_STR1_1ST_CHAR_FLAG()        (u8Flags&=~STR1_1ST_CHAR_BIT)
#define LOAD_SINGLE_FONT_BIT            BIT2
#define LOAD_SINGLE_FONT_FLAG           (u8Flags&LOAD_SINGLE_FONT_BIT)
#define SET_LOAD_SINGLE_FONT_FLAG()     (u8Flags|=LOAD_SINGLE_FONT_BIT)
#define CLR_LOAD_SINGLE_FONT_FLAG()     (u8Flags&=~LOAD_SINGLE_FONT_BIT)
#define LOAD_SINGLE_FONT1_BIT           BIT3
#define LOAD_SINGLE_FONT1_FLAG          (u8Flags&LOAD_SINGLE_FONT1_BIT)
#define SET_LOAD_SINGLE_FONT1_FLAG()    (u8Flags|=LOAD_SINGLE_FONT1_BIT)
#define CLR_LOAD_SINGLE_FONT1_FLAG()    (u8Flags&=~LOAD_SINGLE_FONT1_BIT)
	if(pu8Strings1 == NULL || u16FontCount1 == 0)
		SET_LOAD_SINGLE();
	#if CHIP_ID>=CHIP_TSUMV
	{
		extern BYTE xdata g_u8FontAddrHiBits;
		u16StrIndex = ((msRead2Byte(OSD1_08) + ((((WORD)g_u8FontAddrHiBits) << 8) + (u8Addr)) * (((msReadByte(OSD1_0B) >> 4) & 0x03) + 1)) << 2); //get real address in cafram, ((font base entry)+unit*(unit size))*4 addr/entry
		//u16StrIndex=GET_FONT_RAM_ADDR(u8Addr); //get real address in cafram, ((font base entry)+unit*(unit size))*4 addr/entry
	}
	msWrite2Byte(PORT_FONT_ADDR, u16StrIndex);
	u16StrIndex = 0;
	#else
	MEM_MSWRITE_BYTE(OSD2_A3, u8Addr);
	#endif
	SET_STR_1ST_CHAR_FLAG();
	SET_STR1_1ST_CHAR_FLAG();
	while((u16StrIndex < u16FontCount) || (u16StrIndex1 < u16FontCount1))
	{
		if((!LOAD_SINGLE_FONT_FLAG) && (u16StrIndex < u16FontCount))   /// Handle 1st strings
		{
			if(STR_1ST_CHAR_FLAG)
			{
				ClearFontBuf(tSN);
				CLR_STR_1ST_CHAR_FLAG();
				#if PropFontUseCommonArea
				{
					if (*(pu8Strings + u16StrIndex) >= SecondTblAddr)
					{
						if ( LanguageIndex == 1 )
						{
							pstPropFontSet1218 = tPropFontSet1;
							pstFontData = pstPropFontSet1218 + *(pu8Strings + u16StrIndex) - SecondTblAddr;
						}
						else if ( LanguageIndex == 2 )
						{
							pstPropFontSet1218 = tPropFontSet2;
							pstFontData = pstPropFontSet1218 + *(pu8Strings + u16StrIndex) - SecondTblAddr;
						}
					}
					else
					{
						pstPropFontSet1218 = tPropFontSet;
						pstFontData = pstPropFontSet1218 + *(pu8Strings + u16StrIndex);
					}
				}
				#else
				pstFontData = pstPropFontSet1218 + *(pu8Strings + u16StrIndex);
				#endif
				u8NextFontW = (FONT_WIDTH - ( (pstFontData->u8SpaceWidth & 0x0F) + ((pstFontData->u8SpaceWidth & 0xF0) >> 4) ));
				if (IS_LEFT_ALIGN)
					u8BufW = FONT_WIDTH - SP_BETWEEN_FONT; //Leading with SP_BETWEEN_FONT pixels
				else if (IS_RIGHT_ALIGN)
					u8BufW = FONT_WIDTH -/*SP_BETWEEN_FONT-*/GetRemainderPixelOfString(pu8Strings + u16StrIndex);
				else    //IS_CENTER_ALIGN
					u8BufW = FONT_WIDTH -/*SP_BETWEEN_FONT-*/(GetRemainderPixelOfString(pu8Strings + u16StrIndex) >> 1);
				//u8BufW : the remainder pixel width
				/// Retrieve the first font of string and copy to a blank buffer.
				CopySubFontBuf(tSN, pstFontData->tLineData, (pstFontData->u8SpaceWidth & 0xF0) >> 4, u8BufW);
			}
			else
			{
				if ((pstFontData->u8SpaceWidth & 0xF0) == 0xF0)
				{
					CopySubFontBuf(tSN, pstFontData->tLineData, u8NextBit, u8BufW);
				}
				else
					CopySubFontBuf(tSN, pstFontData->tLineData, u8NextBit + ((pstFontData->u8SpaceWidth & 0xF0) >> 4), u8BufW);
			}
			///Reset position variable
			if(u8BufW >= u8NextFontW)
			{
				u8BufW -= u8NextFontW;
				u8NextFontW = 0;
				u8NextBit = 0;
			}
			else
			{
				u8NextFontW -= u8BufW;
				u8NextBit += u8BufW;
				u8BufW = 0;
			}
			if(u8BufW == 0) ///Buffur full
			{
				u8BufW = FONT_WIDTH;
				SET_LOAD_SINGLE_FONT_FLAG();
			}
			if(u8NextFontW == 0) ///finished a font
			{
				#if PropFontUseCommonArea
				{
					if (*(pu8Strings + u16StrIndex) >= SecondTblAddr)
					{
						if ( LanguageIndex == 1 )
						{
							pstPropFontSet1218 = tPropFontSet1;
						}
						else if ( LanguageIndex == 2 )
						{
							pstPropFontSet1218 = tPropFontSet2;
						}
						if (((pstPropFontSet1218 + * (pu8Strings + u16StrIndex + 1) - SecondTblAddr)->u8SpaceWidth & 0xF0) != 0xF0)
						{
							if(u8BufW > SP_BETWEEN_FONT)
								u8BufW -= SP_BETWEEN_FONT;
							else if(u8BufW == SP_BETWEEN_FONT)
							{
								u8BufW = FONT_WIDTH;
								SET_LOAD_SINGLE_FONT_FLAG();
							}
							else// if(u8BufW!=0)  u8BufW<SP_BETWEEN_FONT
							{
								//u8BufW=FONT_WIDTH-u8BufW;
								u8BufW = FONT_WIDTH - (SP_BETWEEN_FONT - u8BufW);
								SET_LOAD_SINGLE_FONT_FLAG();
							}
						}
					}
					else
					{
						pstPropFontSet1218 = tPropFontSet;
						if (((pstPropFontSet1218 + * (pu8Strings + u16StrIndex + 1))->u8SpaceWidth & 0xF0) != 0xF0)
						{
							if(u8BufW > SP_BETWEEN_FONT)
								u8BufW -= SP_BETWEEN_FONT;
							else if(u8BufW == SP_BETWEEN_FONT)
							{
								u8BufW = FONT_WIDTH;
								SET_LOAD_SINGLE_FONT_FLAG();
							}
							else// if(u8BufW!=0)  u8BufW<SP_BETWEEN_FONT
							{
								//u8BufW=FONT_WIDTH-u8BufW;
								u8BufW = FONT_WIDTH - (SP_BETWEEN_FONT - u8BufW);
								SET_LOAD_SINGLE_FONT_FLAG();
							}
						}
					}
				}
				#else
				if (((pstPropFontSet1218 + * (pu8Strings + u16StrIndex + 1))->u8SpaceWidth & 0xF0) != 0xF0)
				{
					if(u8BufW > SP_BETWEEN_FONT)
						u8BufW -= SP_BETWEEN_FONT;
					else if(u8BufW == SP_BETWEEN_FONT)
					{
						u8BufW = FONT_WIDTH;
						SET_LOAD_SINGLE_FONT_FLAG();
					}
					else// if(u8BufW!=0)  u8BufW<SP_BETWEEN_FONT
					{
						//u8BufW=FONT_WIDTH-u8BufW;
						u8BufW = FONT_WIDTH - (SP_BETWEEN_FONT - u8BufW);
						SET_LOAD_SINGLE_FONT_FLAG();
					}
				}
				#endif
				u16StrIndex++;
				#if PropFontUseCommonArea
				{
					if (*(pu8Strings + u16StrIndex) >= SecondTblAddr)
					{
						if ( LanguageIndex == 1 )
						{
							pstPropFontSet1218 = tPropFontSet1;
							pstFontData = pstPropFontSet1218 + *(pu8Strings + u16StrIndex) - SecondTblAddr;
						}
						else if ( LanguageIndex == 2 )
						{
							pstPropFontSet1218 = tPropFontSet2;
							pstFontData = pstPropFontSet1218 + *(pu8Strings + u16StrIndex) - SecondTblAddr;
						}
					}
					else
					{
						pstPropFontSet1218 = tPropFontSet;
						pstFontData = pstPropFontSet1218 + *(pu8Strings + u16StrIndex);
					}
				}
				#else
				pstFontData = pstPropFontSet1218 + *(pu8Strings + u16StrIndex); ///get next font data
				#endif
				if ((pstFontData->u8SpaceWidth & 0xF0) == 0xF0)
					u8NextFontW = (pstFontData->u8SpaceWidth & 0x0F);
				else
					u8NextFontW = (FONT_WIDTH - ( (pstFontData->u8SpaceWidth & 0x0F) + ((pstFontData->u8SpaceWidth & 0xF0) >> 4) ));
				u8NextBit = 0;
				if(*(pu8Strings + u16StrIndex) == 0x00)
				{
					if(u8BufW < (FONT_WIDTH - SP_BETWEEN_FONT)) ///???
					{
						SET_LOAD_SINGLE_FONT_FLAG();
					}
					SET_STR_1ST_CHAR_FLAG();
					u16StrIndex++;
					if ((++u8StrCount) == g_u8AlignResetIndex)
						g_u8PropFontFlags &= ~0x0C;
				}
			}
		}
		else if(u16StrIndex >= u16FontCount)
		{
			if(u8BufW)
				u8BufW = 0;
			SET_LOAD_SINGLE_FONT_FLAG();
		}
		//===================================================================================
		if((!LOAD_SINGLE_FONT1_FLAG) && (u16StrIndex1 < u16FontCount1))   /// Handle 2nd strings
		{
			if(STR1_1ST_CHAR_FLAG)
			{
				ClearFontBuf(tSN1);
				CLR_STR1_1ST_CHAR_FLAG();
				#if PropFontUseCommonArea
				{
					if (*(pu8Strings1 + u16StrIndex1) >= SecondTblAddr)
					{
						if ( LanguageIndex == 1 )
						{
							pstPropFontSet1218 = tPropFontSet1;
							pstFontData1 = pstPropFontSet1218 + *(pu8Strings1 + u16StrIndex1) - SecondTblAddr;
						}
						else if ( LanguageIndex == 2 )
						{
							pstPropFontSet1218 = tPropFontSet2;
							pstFontData1 = pstPropFontSet1218 + *(pu8Strings1 + u16StrIndex1) - SecondTblAddr;
						}
					}
					else
					{
						pstPropFontSet1218 = tPropFontSet;
						pstFontData1 = pstPropFontSet1218 + *(pu8Strings1 + u16StrIndex1);
					}
				}
				#else
				pstFontData1 = pstPropFontSet1218 + *(pu8Strings1 + u16StrIndex1);
				#endif
				u8NextFontW1 = (FONT_WIDTH - ( (pstFontData1->u8SpaceWidth & 0x0F) + ((pstFontData1->u8SpaceWidth & 0xF0) >> 4) ));
				if (IS_LEFT_ALIGN)
					u8BufW1 = FONT_WIDTH - SP_BETWEEN_FONT;
				else if (IS_RIGHT_ALIGN)
					u8BufW = FONT_WIDTH -/*SP_BETWEEN_FONT-*/GetRemainderPixelOfString(pu8Strings1 + u16StrIndex1);
				else    //IS_CENTER_ALIGN
					u8BufW = FONT_WIDTH -/*SP_BETWEEN_FONT-*/(GetRemainderPixelOfString(pu8Strings1 + u16StrIndex1) >> 1);
				CopySubFontBuf(tSN1, pstFontData1->tLineData, (pstFontData1->u8SpaceWidth & 0xF0) >> 4, u8BufW1);
			}
			else
			{
				if ((pstFontData1->u8SpaceWidth & 0xF0) == 0xF0)
				{
					CopySubFontBuf(tSN1, pstFontData1->tLineData, u8NextBit1, u8BufW1);
				}
				else
					CopySubFontBuf(tSN1, pstFontData1->tLineData, u8NextBit1 + ((pstFontData1->u8SpaceWidth & 0xF0) >> 4), u8BufW1);
			}
			if(u8BufW1 >= u8NextFontW1)
			{
				u8BufW1 -= u8NextFontW1;
				u8NextFontW1 = 0;
				u8NextBit1 = 0;
			}
			else
			{
				u8NextFontW1 -= u8BufW1;
				u8NextBit1 += u8BufW1;
				u8BufW1 = 0;
			}
			if(u8BufW1 == 0)
			{
				u8BufW1 = FONT_WIDTH;
				SET_LOAD_SINGLE_FONT1_FLAG();
			}
			if(u8NextFontW1 == 0)
			{
				#if PropFontUseCommonArea
				{
					if (*(pu8Strings1 + u16StrIndex1) >= SecondTblAddr)
					{
						if ( LanguageIndex == 1 )
						{
							pstPropFontSet1218 = tPropFontSet1;
						}
						else if ( LanguageIndex == 2 )
						{
							pstPropFontSet1218 = tPropFontSet2;
						}
						if (((pstPropFontSet1218 + * (pu8Strings1 + u16StrIndex1) - SecondTblAddr)->u8SpaceWidth & 0xF0) != 0xF0)
						{
							if(u8BufW > SP_BETWEEN_FONT)
								u8BufW -= SP_BETWEEN_FONT;
							else if(u8BufW == SP_BETWEEN_FONT)
							{
								u8BufW = FONT_WIDTH;
								SET_LOAD_SINGLE_FONT_FLAG();
							}
							else// if(u8BufW!=0)  u8BufW<SP_BETWEEN_FONT
							{
								//u8BufW=FONT_WIDTH-u8BufW;
								u8BufW = FONT_WIDTH - (SP_BETWEEN_FONT - u8BufW);
								SET_LOAD_SINGLE_FONT_FLAG();
							}
						}
					}
					else
					{
						pstPropFontSet1218 = tPropFontSet;
						if (((pstPropFontSet1218 + * (pu8Strings1 + u16StrIndex1))->u8SpaceWidth & 0xF0) != 0xF0)
						{
							if(u8BufW > SP_BETWEEN_FONT)
								u8BufW -= SP_BETWEEN_FONT;
							else if(u8BufW == SP_BETWEEN_FONT)
							{
								u8BufW = FONT_WIDTH;
								SET_LOAD_SINGLE_FONT_FLAG();
							}
							else// if(u8BufW!=0)  u8BufW<SP_BETWEEN_FONT
							{
								//u8BufW=FONT_WIDTH-u8BufW;
								u8BufW = FONT_WIDTH - (SP_BETWEEN_FONT - u8BufW);
								SET_LOAD_SINGLE_FONT_FLAG();
							}
						}
					}
				}
				#else
				if (((pstPropFontSet1218 + * (pu8Strings1 + u16StrIndex1))->u8SpaceWidth & 0xF0) != 0xF0)
				{
					if(u8BufW1 > SP_BETWEEN_FONT)
						u8BufW1 -= SP_BETWEEN_FONT;
					else if(u8BufW1 == SP_BETWEEN_FONT)
					{
						u8BufW1 = FONT_WIDTH;
						SET_LOAD_SINGLE_FONT1_FLAG();
					}
					else
					{
						//u8BufW1=FONT_WIDTH-u8BufW1;
						u8BufW1 = FONT_WIDTH - (SP_BETWEEN_FONT - u8BufW1);
						SET_LOAD_SINGLE_FONT1_FLAG();
					}
				}
				#endif
				u16StrIndex1++;
				#if PropFontUseCommonArea
				{
					if (*(pu8Strings1 + u16StrIndex1) >= SecondTblAddr)
					{
						if ( LanguageIndex == 1 )
						{
							pstPropFontSet1218 = tPropFontSet1;
							pstFontData1 = pstPropFontSet1218 + *(pu8Strings1 + u16StrIndex1) - SecondTblAddr;
						}
						else if ( LanguageIndex == 2 )
						{
							pstPropFontSet1218 = tPropFontSet2;
							pstFontData1 = pstPropFontSet1218 + *(pu8Strings1 + u16StrIndex1) - SecondTblAddr;
						}
					}
					else
					{
						pstPropFontSet1218 = tPropFontSet;
						pstFontData1 = pstPropFontSet1218 + *(pu8Strings1 + u16StrIndex1);
					}
				}
				#else
				pstFontData1 = pstPropFontSet1218 + *(pu8Strings1 + u16StrIndex1);
				#endif
				if ((pstFontData1->u8SpaceWidth & 0xF0) == 0xF0)
					u8NextFontW1 = (pstFontData1->u8SpaceWidth & 0x0F);
				else
					u8NextFontW1 = (FONT_WIDTH - ( (pstFontData1->u8SpaceWidth & 0x0F) + ((pstFontData1->u8SpaceWidth & 0xF0) >> 4) ));
				u8NextBit1 = 0;
				if(*(pu8Strings1 + u16StrIndex1) == 0x00)
				{
					if(u8BufW1 < (FONT_WIDTH - SP_BETWEEN_FONT))
					{
						SET_LOAD_SINGLE_FONT1_FLAG();
					}
					SET_STR1_1ST_CHAR_FLAG();
					u16StrIndex1++;
				}
			}
		}
		else if(u16StrIndex1 >= u16FontCount1)
		{
			if(u8BufW1)
				u8BufW1 = 0;
			SET_LOAD_SINGLE_FONT1_FLAG();
		}
		if(LOAD_SINGLE_FONT_FLAG && LOAD_SINGLE_FONT1_FLAG)
		{
			#if 0
			if(LOAD_SINGLE_LINE_FLAG)
			{
				ShiftFontUpDown(tSN, u8UDShift);
			}
			else//if(!IsLoadsingleLine)
			{
				ShiftFontUpDown(tSN, u8UDShift);
				ShiftFontUpDown(tSN1, u8UDShift1);
				MergeFontBuf(tSN, tSN1);
			}
			OSDLoadOneFont(tSN);
			u8FontCnt++;
			ClearFontBuf(tSN);
			ClearFontBuf(tSN1);
			#else   //Jison, Speed up
			if(LOAD_SINGLE_LINE_FLAG)
			{
				if (u8UDShift & 0x7F)
					ShiftFontUpDown(tSN, u8UDShift);
				if (g_u8ByPassLength)
					g_u8ByPassLength--;
				else
				{
					OSDLoadOneFont(tSN);
					u8FontCnt++;
				}
				ClearFontBuf(tSN);
			}
			else
			{
				if (u8UDShift & 0x7F)
					ShiftFontUpDown(tSN, u8UDShift);
				if (u8UDShift1 & 0x7F)
					ShiftFontUpDown(tSN1, u8UDShift1);
				MergeFontBuf(tSN, tSN1);
				OSDLoadOneFont(tSN);
				u8FontCnt++;
				ClearFontBuf(tSN);
				ClearFontBuf(tSN1);
			}
			#endif
			CLR_LOAD_SINGLE_FONT_FLAG();
			CLR_LOAD_SINGLE_FONT1_FLAG();
		}
	}
	//msWriteByte(OSDIOA, OWEND_B|OSBM_B|ORBW_B);
	return u8FontCnt;
}

#if 0//ENABLE_PERSONALIZE_MENU
//u8UDShift, Bit 7==1 means shift up
//u16Size is the total bytes of u8FontTbl
//for 12x18 only
//The font table must not be compressed format.
BYTE LoadShiftBmpFont(BYTE u8Addr, BYTE *u8FontTbl, WORD u16Size, BYTE u8UDShift)
{
	WORD i;
	BYTE j, u8FontCnt = 0;
	WORD  idata tSN[FONT_HEIGHT];
	msWriteByte(OSD2_A3, u8Addr);
	i = 0;
	while(u8FontCnt < u16Size / 27)
	{
		for (j = 0; j < 18; j += 2, i += 3) //Load on font to buffer
		{
			tSN[j] = u8FontTbl[i] & 0x0f;
			tSN[j] <<= 8;
			tSN[j] += u8FontTbl[i + 1];
			tSN[j + 1] = u8FontTbl[i] & 0xf0;
			tSN[j + 1] <<= 4;
			tSN[j + 1] += u8FontTbl[i + 2];
		}
		if (u8UDShift & 0x7F)
			ShiftFontUpDown(tSN, u8UDShift);
		OSDLoadOneFont(tSN);
		u8FontCnt++;
	}
	return u8FontCnt;
}
#endif

#endif


