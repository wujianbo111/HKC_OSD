#include "board.h"

typedef struct
{
	BYTE u8Red;
	BYTE u8Green;
	BYTE u8Blue;
} ColorType;

#if defined(BRI_PRO_MIN_VALUE)
#define BRIGHTNESS_PWM_MIN_VALUE				 BRI_PRO_MIN_VALUE
#define BRIGHTNESS_PWM_DEF_VALUE              	 BRI_PRO_DEF_VALUE//	
#define BRIGHTNESS_PWM_MAX_VALUE				 BRI_PRO_MAX_VALUE
#define DEF_SHIFTPWM							0x9B5
#else
#define BRIGHTNESS_PWM_MIN_VALUE				0x00
#define BRIGHTNESS_PWM_DEF_VALUE                    	0xD9// 0x75
#define BRIGHTNESS_PWM_MAX_VALUE				0xF2//0xFF
#define DEF_SHIFTPWM							0x9B5
#endif

extern void mStar_AdjustBrightness(BYTE brightness);
extern void mStar_AdjustDcrBrightness(void);
extern void mStar_AdjustUserPrefBlacklevel(BYTE Redblacklevel, BYTE Greenblacklevel, BYTE Blueblacklevel);
extern void mStar_AdjustContrast(BYTE contrast);
extern void mStar_AdjustHPosition(WORD position);
extern void mStar_AdjustVPosition(WORD position);
void mStar_AdjustRGBColor(BYTE u8Contrast, BYTE u8Red, BYTE u8Green, BYTE u8Blue);
#if UsesRGB
void mStar_AdjustRedColor(BYTE rColor, BYTE gColor, BYTE bColor);
void mStar_AdjustGreenColor(BYTE rColor, BYTE gColor, BYTE bColor);
void mStar_AdjustBlueColor(BYTE rColor, BYTE gColor, BYTE bColor);
#else
void mStar_AdjustRedColor(BYTE color, BYTE contrast);
void mStar_AdjustGreenColor(BYTE color, BYTE contrast);
void mStar_AdjustBlueColor(BYTE color, BYTE contrast);
#endif
extern void mStar_AdjustVolume(BYTE volume);
extern void mStar_WaitForDataBlanking(void);
extern void mStar_AdjustBackgoundColor(BYTE pattern);
