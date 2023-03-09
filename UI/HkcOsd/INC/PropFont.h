
#if CHIP_ID>=CHIP_TSUMV
extern void Osd_DynamicLoadFont(BYTE addr, BYTE *fontPtr, WORD num);
#else
extern void Osd_DynamicLoadFont(BYTE addr, BYTE *fontPtr, WORD num);
#endif

extern void DynamicLoadFont(MenuFontType *menuFonts);
extern void LoadLanguageStatusPropfont( void );

extern MenuFontType code MenuPage1[];
extern MenuFontType code MenuPage2[];
extern MenuFontType code MenuPage3[];
extern MenuFontType code MenuPage4[];
extern MenuFontType code MenuPage5[];
extern MenuFontType code MenuPage6[];
extern MenuFontType code MenuPage7[];
extern MenuFontType code MenuPage8[];
extern MenuFontType code MenuPage9[];
extern MenuFontType code MenuPage10[];
extern MenuFontType code MenuPage11[];
extern MenuFontType code MenuPage12[];
extern MenuFontType code MenuPage13[];

extern MenuFontType code MenuPage98[];

extern MenuFontType code MenuPage30[];
extern MenuFontType code MenuPage23[];

#if 1//Eson20130116
extern MenuFontType code MenuPage61[];
extern MenuFontType code MenuPage62[];
extern MenuFontType code MenuPage63[];
extern MenuFontType code MenuPage64[];
extern MenuFontType code MenuPage65[];
extern MenuFontType code MenuPage66[];
extern MenuFontType code MenuPage67[];
extern MenuFontType code MenuPage68[];
extern MenuFontType code MenuPage69[];
#endif
extern MenuFontType code MenuPage80[];
extern MenuFontType code MenuPage88[];

extern MenuFontType code MenuPage55[];

