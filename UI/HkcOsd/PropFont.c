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
//#include "font.h"
#include "extlib.h"


#if PropFontNewData
#include "PropFontAllLanguage_new.h"
#include "MenuFontTbl_new.h"
#else
#include "PropFontAllLanguage.h"
#include "MenuFontTbl.h"
#endif




extern BYTE  xdata MenuPageIndex;

#include "loadpropfont1218.h"
#include "msOSD.h"
#include "drvOSD.h"

#if CHIP_ID>=CHIP_TSUMV

void Osd_DynamicLoadFont( BYTE addr, BYTE *fontPtr, WORD num )
{
	TotalFontWidth = 0;
	OSD_WRITE_FONT_ADDRESS(addr);
	LoadCompressedPropFonts( fontPtr, num );
}
#else

void Osd_DynamicLoadFont( BYTE  addr, BYTE *fontPtr, WORD num )
{
	TotalFontWidth = 0;
	/*
		if(( addr & 0xFF00 ) == 0x100 )
		    {
	        	OSD_FONT_HI_ADDR_SET_BIT8();
		    }
		else if(( addr & 0xFF00 ) == 0x200 )
		    {
	        	OSD_FONT_HI_ADDR_SET_BIT9();
		    }
		else if(( addr & 0xFF00 ) == 0x300 )
		    {
	        	OSD_FONT_HI_ADDR_SET_BIT10();
		    }
		else
		    {
	        	OSD_FONT_HI_ADDR_CLR_TO_0();
		    }
	*/
	OSD_WRITE_FONT_ADDRESS(addr & 0xFF);
	LoadCompressedPropFonts( fontPtr, num );
	//OSD_FONT_CLEAR();
}
#endif


#if ENABLE_OVER_SCAN

#define ImageRatioStatusAddr    0xA8
void DynamicLoadFont_RatioStatus(void)
{
	if( UserprefExpansionMode == Expansion_Aspect && ExpansionFlag )
	{
		Osd_DynamicLoadFont( ImageRatioStatusAddr, MenuPage62[UserPrefLanguage].Fonts, MenuPage62[UserPrefLanguage].FontCount );
	}
	#if ENABLE_OVER_SCAN
	else if( UserprefExpansionMode == Expansion_11)// && !INPUT_IS_NATIVE_TIMING() )   //121228 Modify
	{
		Osd_DynamicLoadFont( ImageRatioStatusAddr, MenuPage63[UserPrefLanguage].Fonts, MenuPage63[UserPrefLanguage].FontCount );
	}
	else if( UserprefExpansionMode == PIC_FORMAT_17Picth)// && !INPUT_IS_NATIVE_TIMING() ) //121228 Modify
	{
		Osd_DynamicLoadFont( ImageRatioStatusAddr, MenuPage64[UserPrefLanguage].Fonts, MenuPage64[UserPrefLanguage].FontCount );
	}
	else if( UserprefExpansionMode == PIC_FORMAT_19Picth)// && !INPUT_IS_NATIVE_TIMING() ) //121228 Modify
	{
		Osd_DynamicLoadFont( ImageRatioStatusAddr, MenuPage65[UserPrefLanguage].Fonts, MenuPage65[UserPrefLanguage].FontCount );
	}
	else if( UserprefExpansionMode == PIC_FORMAT_W19Picth)// && !INPUT_IS_NATIVE_TIMING() )    //121228 Modify
	{
		Osd_DynamicLoadFont( ImageRatioStatusAddr, MenuPage66[UserPrefLanguage].Fonts, MenuPage66[UserPrefLanguage].FontCount );
	}
	else if( UserprefExpansionMode == PIC_FORMAT_W21_5Picth)// && !INPUT_IS_NATIVE_TIMING() )  //121228 Modify
	{
		Osd_DynamicLoadFont( ImageRatioStatusAddr, MenuPage67[UserPrefLanguage].Fonts, MenuPage67[UserPrefLanguage].FontCount );
	}
	else if( UserprefExpansionMode == PIC_FORMAT_W22Picth)// && !INPUT_IS_NATIVE_TIMING() )    //121228 Modify
	{
		Osd_DynamicLoadFont( ImageRatioStatusAddr, MenuPage68[UserPrefLanguage].Fonts, MenuPage68[UserPrefLanguage].FontCount );
	}
	else if( UserprefExpansionMode == PIC_FORMAT_W23Picth)// && !INPUT_IS_NATIVE_TIMING() )    //121228 Modify
	{
		Osd_DynamicLoadFont( ImageRatioStatusAddr, MenuPage69[UserPrefLanguage].Fonts, MenuPage69[UserPrefLanguage].FontCount );
	}
	#endif
	else
	{
		Osd_DynamicLoadFont( ImageRatioStatusAddr, MenuPage61[UserPrefLanguage].Fonts, MenuPage61[UserPrefLanguage].FontCount );
	}
}

#endif


void DynamicLoadFont(MenuFontType *menuFonts)
{
	if (menuFonts->Fonts)
	#if !AdjustLanguageFunction
		if(MenuPageIndex == LanguageMenu)
			Osd_DynamicLoadFont(PropFontAddress, (BYTE*)(menuFonts->Fonts), menuFonts->FontCount);
		else
	#endif
			Osd_DynamicLoadFont(PropFontAddress, (BYTE*)((menuFonts + UserPrefLanguage)->Fonts), (menuFonts + UserPrefLanguage)->FontCount);
}


void LoadLanguageStatusPropfont( void )
{
	if(MenuPageIndex != FactoryMenu)
		Osd_DynamicLoadFont( PropFontAddress, MenuPage4[UserPrefLanguage].Fonts, MenuPage4[UserPrefLanguage].FontCount );
	Osd_DynamicLoadFont( MainAddress, MenuPage7[UserPrefLanguage].Fonts, MenuPage7[UserPrefLanguage].FontCount );
	#if AdjustLanguageFunction
	Osd_DynamicLoadFont( LanguageAddress, MenuPage8[UserPrefLanguage].Fonts, MenuPage8[UserPrefLanguage].FontCount );
	#endif
}

