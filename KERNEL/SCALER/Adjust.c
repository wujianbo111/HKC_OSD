#include <math.h>
#include "types.h"
#include "ms_reg.h"
#include "ms_rwreg.h"
#include "debug.h"
#include "msosd.h"
#include "Board.h"
#include "global.h"
#include "menudef.h"
#include "msdlc.h"
#include "msace.h"
#include "drvosd.h"
#include "GPIO_DEF.h"
#include "drvgpio.h"
#include "adjust.h"
#if AudioFunc
#include "misc.h"
#endif
#if ENABLE_HDMI
#include "msHDMI.h"
#include "msHDMIACE.h"
#endif



#if 1
#include "drvDAC.h"
#endif
//===================================================
// Local function declaration
#if UsesRGB
void mStar_AdjustRedColor(BYTE rColor, BYTE gColor, BYTE bColor);
void mStar_AdjustGreenColor(BYTE rColor, BYTE gColor, BYTE bColor);
void mStar_AdjustBlueColor(BYTE rColor, BYTE gColor, BYTE bColor);
#else
void mStar_AdjustRedColor(BYTE color, BYTE contrast);
void mStar_AdjustGreenColor(BYTE color, BYTE contrast);
void mStar_AdjustBlueColor(BYTE color, BYTE contrast);
#endif
extern void GetColorTempRGB(ColorType *pstColor);
extern Bool IsColorspaceRGB(void);
#if CHIP_ID==CHIP_TSUMU
extern void drvGPIO_SetPWMDuty(BYTE u8PWMCh, DWORD u32Duty);
#endif
//****************************************************


#define MaxBacklightNowValue	225//230//231//226  //216 //236//238
#define MinBacklightNowValue	  20//17//29  //39  //19//17



#define AbsMostDarkest1  ((SrcInputType == Input_VGA)?(16):(16))  // 16  //20081201
#define AbsNearDarkest1  ((SrcInputType == Input_VGA)?(21):(17))  // 18
#define AbsMostDarkest2  ((SrcInputType == Input_VGA)?(16):(16))  // 17
#define AbsNearDarkest2  ((SrcInputType == Input_VGA)?(23):(19))  // 20

//****************************************************
#define ABS2(x,y) (x>y)?(x-y):(y-x)
#define MAX2(x,y) (x>y)? x : y
#define MIN2(x,y) (x>y)? y : x
xdata BYTE u8DCRfinalBri;
void mStar_AdjustDcrBrightness(void)
{
	static BYTE xdata brightness;
	static BYTE xdata DcrCutoffFlag = 0;    //DCR new rule 081128
	//msWriteByte(REGBK, REG_BANK_SCALER);
	if(BacklightNow < MinBacklightNowValue)
		BacklightNow = MinBacklightNowValue;
	#if 0//EnablePanelServiceMenu
	//if(!DcrCutoffFlag)
	//brightness = (((DWORD)(BacklightNow - MinBacklightNowValue)*(PanelMaxDuty - RealMinDcrBrightnessValue)) / (MaxBacklightNowValue - MinBacklightNowValue)) + RealMinDcrBrightnessValue;
	if (BacklightNow >= MaxBacklightNowValue)
	{
		brightness = PanelMaxDuty;
		DcrCutoffFlag = 0;    //20081201
	}
	else if (BacklightNow <= MinBacklightNowValue)
	{
		if(SetDarkestFlag)
		{
			SetDarkestFlag = 0;
			PreBrightData = 0; // to make sure if bright data exist, it will update brightness.
			//brightness = PanelMinDuty;  // set logical absolute dark value, // RealMinBrightnessValue;
			if(DcrCutoffFlag == 0)
			{
				if((DarkData <= AbsMostDarkest1) && (BrightData <= AbsNearDarkest1))        // >>>  logical absolute dark condition  <<< 20081128
					// set logical absolute dark value, // RealMinBrightnessValue;
				{
					//brightness = RealMinDcrBrightnessValue;  // set logical absolute dark value, // RealMinBrightnessValue;
					DcrCutoffFlag = 1;
				}
				brightness = RealMinDcrBrightnessValue;
			}
			else
			{
				if((DarkData <= AbsMostDarkest2) && (BrightData <= AbsNearDarkest2))        // set logical absolute dark value,
				{
					if(brightness > PanelMinDuty)
						brightness--;  // set logical absolute dark value, // RealMinBrightnessValue;
					#if defined(DCRClearBacklight)      //A008 item
					if(OSD_MENU_EXIST() && ( brightness < RealMinBrightnessValue ) )
						brightness = RealMinBrightnessValue;
					ForceDelay1ms( 100 );
					#endif
				}
				else
				{
					DcrCutoffFlag = 0;
					brightness = RealMinDcrBrightnessValue;
				}
			}
		}
		else // 081116
		{
			DcrCutoffFlag = 0;
			brightness = RealMinDcrBrightnessValue;
		}
	}
	else
	{
		DcrCutoffFlag = 0;
		brightness = (((DWORD)(BacklightNow - MinBacklightNowValue) * (PanelMaxDuty - RealMinDcrBrightnessValue)) / (MaxBacklightNowValue - MinBacklightNowValue)) + RealMinDcrBrightnessValue;
	}
	#else
	//if(!DcrCutoffFlag)
	//brightness = (((DWORD)(BacklightNow - MinBacklightNowValue)*(RealMaxBrightnessValue - RealMinDcrBrightnessValue)) / (MaxBacklightNowValue - MinBacklightNowValue)) + RealMinDcrBrightnessValue;
	if (BacklightNow >= MaxBacklightNowValue)
	{
		brightness = RealMaxBrightnessValue;
		DcrCutoffFlag = 0;    //20081201
	}
	else if (BacklightNow <= MinBacklightNowValue)
	{
		if(SetDarkestFlag)
		{
			SetDarkestFlag = 0;
			PreBrightData = 0; // to make sure if bright data exist, it will update brightness.
			//brightness = RealAbsoluteMinBrightnessValue;  // set logical absolute dark value, // RealMinBrightnessValue;
			if(DcrCutoffFlag == 0)
			{
				if((DarkData <= AbsMostDarkest1) && (BrightData <= AbsNearDarkest1))        // >>>  logical absolute dark condition  <<< 20081128
					// set logical absolute dark value, // RealMinBrightnessValue;
				{
					//brightness = RealMinDcrBrightnessValue;  // set logical absolute dark value, // RealMinBrightnessValue;
					DcrCutoffFlag = 1;
				}
				brightness = RealMinDcrBrightnessValue;  // set logical absolute dark value, // RealMinBrightnessValue;
			}
			else
			{
				if((DarkData <= AbsMostDarkest2) && (BrightData <= AbsNearDarkest2))        // set logical absolute dark value,
				{
					if(brightness > RealAbsoluteMinBrightnessValue)
						brightness--;  // set logical absolute dark value, // RealMinBrightnessValue;
					#if defined(DCRClearBacklight)
					if(OSD_MENU_EXIST() && ( brightness < RealMinBrightnessValue ) )
						brightness = RealMinBrightnessValue;
					if(brightness > RealAbsoluteMinBrightnessValue)	// 130114_3 For While Loop Too Long, Key Pad  insensitive
					{
						ForceDelay1ms( 100 );
					}
					#endif
				}
				else
				{
					DcrCutoffFlag = 0;
					brightness = RealMinDcrBrightnessValue;
				}
			}
		}    // if(SetDarkestFlag)
		else // 081116
		{
			DcrCutoffFlag = 0;
			brightness = RealMinDcrBrightnessValue;
		}
	}
	else
	{
		DcrCutoffFlag = 0;
		brightness = (((DWORD)(BacklightNow - MinBacklightNowValue) * (RealMaxBrightnessValue - RealMinDcrBrightnessValue)) / (MaxBacklightNowValue - MinBacklightNowValue)) + RealMinDcrBrightnessValue;
	}
	#endif
//printData("\r\n DCR _ brightness (%x)", brightness) ;
	u8DCRfinalBri = brightness;
	u8DCRfinalBri = MIN2 ( u8DCRfinalBri,       255 );
	u8DCRfinalBri = MAX2 ( u8DCRfinalBri,       0 );
	#if BRIGHTNESS_INVERSE  //+Duty power
	drvGPIO_SetBacklightDuty(BrightnessPWM, 0xFF - brightness);
	#else                           //-Duty power
	drvGPIO_SetBacklightDuty(BrightnessPWM, brightness);
	#endif
	#if defined(DCRClearBacklight)      //A008 item
	if(brightness == RealAbsoluteMinBrightnessValue)
	{
		if(BackLightActiveFlag)
			hw_ClrBlacklit();
	}
	else
	{
		if(!BackLightActiveFlag)
			hw_SetBlacklit();
	}
	#endif
}

#if Brightness_Table_Enable
BYTE code BrightnessValueTable[] =
{
	0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
	0x09, 0x0A, 0x0B, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11,
	0x13, 0x14, 0x15, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B,
	0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
	0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2B, 0x2C, 0x2D, 0x2E,
	0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
	0x39, 0x3A, 0x3C, 0x3E, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4A,
	0x4C, 0x4C, 0x4D, 0x4D, 0x4E, 0x4E, 0x4F, 0x4F, 0x50, 0x50,
	0x51, 0x51, 0x52, 0x52, 0x53, 0x53, 0x54, 0x54, 0x55, 0x55,
	0x56, 0x57, 0x59, 0x5B, 0x5C, 0x5E, 0x60, 0x61, 0x63, 0x65,
	0x67,
};
#endif

void mStar_AdjustBrightness(BYTE brightness)
{
	#if CHIP_ID==CHIP_TSUMU
	WORD xdata u16Bri;
	BYTE u8Bank = msReadByte(REG_3200);
	msWriteByte( REG_3200, u8Bank );
	#if EANBLE_NEW_DCR_Functing
	BacklightNow = BacklightPrev = brightness;	//120308 Modify
	#endif
	#if Brightness_Table_Enable
	u16Bri = BrightnessValueTable[brightness];
	#elif (DefBrightness==100)		//2  	亮度默认一百，Min Max 均分PWM范围，181013 modify
	u16Bri = ((DWORD)brightness * (BRIGHTNESS_PWM_MAX_VALUE - BRIGHTNESS_PWM_MIN_VALUE)) / 100 + BRIGHTNESS_PWM_MIN_VALUE;
	#else
	if (brightness <= DefBrightness)
	{
		u16Bri = BRIGHTNESS_PWM_MIN_VALUE + ((DWORD)brightness * (BRIGHTNESS_PWM_DEF_VALUE - BRIGHTNESS_PWM_MIN_VALUE) / DefBrightness);
	}
	else
	{
		u16Bri = BRIGHTNESS_PWM_DEF_VALUE + ((DWORD)(brightness - DefBrightness) * (BRIGHTNESS_PWM_MAX_VALUE - BRIGHTNESS_PWM_DEF_VALUE) / (100 - DefBrightness));
	}
	#endif
	#if BRIGHTNESS_INVERSE//
	u16Bri = (DEF_SHIFTPWM - u16Bri);
	#endif
	drvGPIO_SetPWMDuty(BrightnessPWM, u16Bri);
	msWriteByte(REG_3200, u8Bank);
	#else
	#if EANBLE_NEW_DCR_Functing
	BacklightNow = BacklightPrev = brightness;	//120308 Modify
	#endif
	#if Brightness_Table_Enable
	brightness = BrightnessValueTable[brightness];
	#elif (DefBrightness==100)		//2  	亮度默认一百，Min Max 均分PWM范围，181013 modify
	brightness = ((DWORD)brightness * (BRIGHTNESS_PWM_MAX_VALUE - BRIGHTNESS_PWM_MIN_VALUE)) / 100 + BRIGHTNESS_PWM_MIN_VALUE;
	#else
	if(brightness > DefBrightness)
	{
		brightness = ((WORD)(brightness - DefBrightness) * (BRIGHTNESS_PWM_MAX_VALUE - BRIGHTNESS_PWM_DEF_VALUE)) / (MaxBrightnessValue - DefBrightness) + BRIGHTNESS_PWM_DEF_VALUE;
	}
	else
	{
		brightness = ((WORD)brightness * (BRIGHTNESS_PWM_DEF_VALUE - BRIGHTNESS_PWM_MIN_VALUE)) / (DefBrightness - MinBrightnessValue) + BRIGHTNESS_PWM_MIN_VALUE;
	}
	#endif
	#if !EANBLE_NEW_DCR_Functing
	BacklightNow = BacklightPrev = brightness;	//120308 Modify
	#endif
	#if BRIGHTNESS_INVERSE  //+Duty power00
	drvGPIO_SetBacklightDuty(BrightnessPWM, 0xFF - brightness); // 0x0290
	#else                           //-Duty power
	drvGPIO_SetBacklightDuty(BrightnessPWM, brightness);
	#endif
	#endif
}



//=================================================================================
//volume=((DWORD)volume*63)/100+57;    //LM929 2W for Lai
//volume=((DWORD)volume*84)/100+93;    //LM929 3W && Carrefour for Lai
//volume=((DWORD)volume*92)/100+93;    //-0923-LM929 3W && Carrefour for Lai
//volume=((DWORD)volume*170)/100+57;   //LM729 && Carrefour for Lu
//volume = ( ( DWORD ) volume * 70) / 20 +90; //qx.long20061213
//volume = ( ( DWORD ) volume * 34) / 100 +160; //qx.long20061213
// volume=((DWORD)volume*146)/100+51;   //1127 for Lai TESTING 19" AUDIO
//=================================================================================
void mStar_AdjustRGBColor(BYTE u8Contrast, BYTE u8Red, BYTE u8Green, BYTE u8Blue)
{
	if(IsColorspaceRGB()
        #if ENABLE_DISPLAY_UNDERSCAN	//121121 Modify
	        && !SETUP_PATH_R2Y()
        #endif
	  )
	{
		msAdjustPCContrastRGB(MAIN_WINDOW, u8Contrast, u8Red, u8Green, u8Blue);
	}
	else
	{
		msAdjustVideoContrastRGB(MAIN_WINDOW, u8Contrast, u8Red, u8Green, u8Blue);
	}
}

void mStar_AdjustContrast(BYTE contrast)
{
	xdata ColorType CT;
//   WORD xdata u16Cont;
	//WORD wcontrast;
	#if CHIP_ID == CHIP_TSUMV && WaitForDataBlanking//20130511 for I2470SWD
	mStar_WaitForDataBlanking();
	#endif
	GetColorTempRGB(&CT);
	/*
	    #if  ModelName==LEYI_JRY_LQ570S_BV1
	    {
	        if (contrast<=DefContrast)
	        {
	        u16Cont=MinContrastValue+((DWORD)(contrast-MinContrastValue)*(DefContrast-MinContrastValue)/(DefContrast-MinContrastValue));
	        }
	        else
	        {
	        u16Cont=DefContrast+((DWORD)(contrast-DefContrast)*(MaxContrastValue-contrast-44)/(100-DefContrast));
	        }
	    }
	    #else
	    {
	          if (contrast<=DefContrast)
	        {
	        u16Cont=MinContrastValue+((DWORD)contrast*(DefContrast-MinContrastValue)/(DefContrast-MinContrastValue));
	        }
	        else
	        {
	        u16Cont=DefContrast+((DWORD)(contrast-DefContrast)*(MaxContrastValue-DefContrast)/(100-DefContrast));
	        }
	    }
	    #endif
	*/
	mStar_AdjustRGBColor(contrast, CT.u8Red, CT.u8Green, CT.u8Blue);
//   mStar_AdjustRGBColor(contrast, CT.u8Red, CT.u8Green, CT.u8Blue);
}

void mStar_AdjustHPosition(WORD position)
{
	SC0_SET_IMAGE_START_H(position);//msWrite2Byte(SC0_07, position);
}


void mStar_AdjustVPosition(WORD position)
{
	#if 1
	#if DECREASE_V_SCALING
	position = (position > VSTART_OFFSET) ? (position - VSTART_OFFSET) : (0);
	#endif
	SC0_SET_IMAGE_START_V(position);//msWrite2Byte( SC0_05, position );
	#else
	if( DecVScaleFlag )
	{
		if( position <= ( VScaleDecValue / 2 ) )
			position = VScaleDecValue / 2 + 1;
		msWrite2Byte( SC0_05, position - ( VScaleDecValue / 2 ) );
	}
	else
	{
		if( position == 0 )
			position = 1;
		msWrite2Byte( SC0_05, position );
	}
	#endif
}
//wmz 20051017 for response time
void mStar_AdjustRedColor(BYTE color, BYTE contrast)
{
	xdata ColorType CT;
	GetColorTempRGB(&CT);
	mStar_AdjustRGBColor(contrast, color, CT.u8Green, CT.u8Blue);
}
void mStar_AdjustGreenColor(BYTE color, BYTE contrast)
{
	xdata ColorType CT;
	GetColorTempRGB(&CT);
	mStar_AdjustRGBColor(contrast, CT.u8Red, color, CT.u8Blue);
}
void mStar_AdjustBlueColor(BYTE color, BYTE contrast)
{
	xdata ColorType CT;
	GetColorTempRGB(&CT);
	#if ENABLE_OSD_LowBlueLight && (LowBlueLightType != LowBlueLight_SharpFunc)
	color -= UserprefLowBlueLightMode * 7;
	if(color >= 0xFF)
		color = 128;
	#endif
	mStar_AdjustRGBColor(contrast, CT.u8Red, CT.u8Green, color);
}

// 100802 coding modify
#define RETRY_COUNT 0xffff

void mStar_WaitForDataBlanking(void)
{
	#if 0//CHIP_ID>=CHIP_TSUMV
	if(SyncLossState() || !PanelOnFlag)
		return;
	TimeOutCounter = 30;
	while((msReadByte(SC0_E0)&BIT0) != 0 && (TimeOutCounter))
		;
	#else
	WORD retry;
	if(SyncLossState() || !PanelOnFlag)
		return;
	retry = RETRY_COUNT;
	while (retry-- && !InputTimingChangeFlag && (msReadByte(SC0_90)&BIT7));
	if(SyncLossState() || !PanelOnFlag)
		return;
	retry = RETRY_COUNT;
	while (retry-- && !InputTimingChangeFlag && !(msReadByte(SC0_90)&BIT7));
	#endif
}
void mStar_AdjustBackgoundColor(BYTE pattern)
{
	BYTE rColor = 0;
	BYTE gColor = 0;
	BYTE bColor = 0;
	if (pattern == 0)
	{
		rColor = 0xFF;
	}
	else if (pattern == 1)
	{
		gColor = 0xFF;
	}
	else if (pattern == 2)
	{
		bColor = 0xFF;
	}
	else if (pattern == 4)
	{
		rColor = 0xF8;//0xFF;
		gColor = 0xF8;//0xFF;
		bColor = 0xF8; // 0xFF;
	}
	/*    else if (pattern == 5)
	    {
	        rColor = 0xF8;//0xFF;
	        gColor = 0xF8;//0xFF;
	    }
	    else if (pattern == 6)
	    {
	        gColor = 0xF8;//0xFF;
	        bColor =0xF8;// 0xFF;
	    }
	    else if (pattern == 7)
	    {
	        rColor = 0xF8;//0xFF;
	        bColor =0xF8;// 0xFF;
	    }
	 */
	mStar_WaitForDataBlanking();
	drvOSD_FrameColorRGB(rColor, gColor, bColor);
}



#if AudioFunc

#define MaxVolumeValue 		100
#define MinVolumeValue    	0//petit 20130802

#define Volume50Value  ((MaxVolumeValue-MinVolumeValue)*50/100+MinVolumeValue)
#if 1//==============================
#define MaxEARVolumeValue 		0x3F
#define MidEARVolumeValue           0x1C
#define MinEARVolumeValue           	0//petit 20130802

#endif

#if AdjustVolume_UseTable
BYTE code VolumeValueTable[] =
{
	0x00, 0x20, 0x23, 0x24, 0x26, 0x27, 0x29, 0x2A, 0x2C, 0x2D,
	0x30, 0x32, 0x35, 0x38, 0x3B, 0x3E, 0x41, 0x44, 0x47, 0x4A, //10
	0x4C, 0x50, 0x55, 0x59, 0x5E, 0x62, 0x67, 0x6C, 0x70, 0x75, //20
	0x79, 0x7C, 0x7F, 0x81, 0x84, 0x86, 0x89, 0x8B, 0x8E, 0x90, //30
	0x94, 0x97, 0x9A, 0x9D, 0xA0, 0xA3, 0xA6, 0xA9, 0xAB, 0xAD, //40
	0xB0, 0xB1, 0xB3, 0xB4, 0xB6, 0xB7, 0xB9, 0xBA, 0xBC, 0xBE, //50
	0xC0, 0xC1, 0xC3, 0xC4, 0xC6, 0xC7, 0xC9, 0xCA, 0xCC, 0xCE, //60
	0xD0, 0xD1, 0xD3, 0xD4, 0xD5, 0xD7, 0xD9, 0xDA, 0xDC, 0xDE, //70
	0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, //80
	0xE5, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, //90
	0xEE,//100                                                                          //0xEE
};
#endif


#if   USE_DAC_ADJ
#include "drvDAC.h"
void mStar_AdjustVolume(BYTE volume)
{
	if( MinVolume >= volume )
		volume = 0;
	if(volume == 0)    //111031 add for meet the volume adjustment flow
	{
		hw_SetMute();
		Delay1ms(2);
	}
	#if USE_DAC_ADJ
	if(volume == 0 || UserPrefMuteState)
	{
		msWriteByteMask( REG_2C6A, BIT4, BIT4 );
	}
	else
	{
		msWriteByteMask( REG_2C6A, BIT0, BIT4 );
	}
	#endif
	if( volume )
	{
		// hw_ClrMute();
		//volume=TestByte;
		#if AdjustVolume_UseTable
		volume = VolumeValueTable[volume];
		#else
		#if USE_DAC_ADJ
		volume = volume;
		#if 1
		if( volume >= 50 )
			volume = ((( DWORD )volume - 50 ) * ( MaxEARVolumeValue - MidEARVolumeValue ) ) / 50 + MidEARVolumeValue ;
		else
			volume = ((( DWORD )volume) * ( MidEARVolumeValue - MinEARVolumeValue ) ) / 50 + MinEARVolumeValue;
		#endif
		#else
		if( volume >= 50 )
			volume = (( DWORD )volume * ( MaxVolumeValue - Volume50Value ) ) / 50 + 2 * Volume50Value - MaxVolumeValue;
		else
			volume = (( DWORD )volume * ( Volume50Value - MinVolumeValue ) ) / 50 + MinVolumeValue;
		#endif
		#endif
	}
	else
	{
		// hw_SetMute();
		volume = 0;
	}
	#if USE_DAC_ADJ
	msAudioLineOutGain(volume);
	if (volume == 0)
		msAudioDPGA_Mute();
	#else
	#if VOLUME_INVERSE  //+Duty power
	drvGPIO_SetBacklightDuty(VolumePWM, 0xFF - volume);
	#else                           //-Duty power
	drvGPIO_SetBacklightDuty(VolumePWM, volume);
	#endif
	#endif
	if (volume != 0)
	{
		hw_ClrMute();
	}
}
#else

#if 1//EarphoneDet_Enable

//#define MaxVolumeValue		100
//#define MinVolumeValue		0


#if CHIP_ID==CHIP_TSUMU

#ifndef  DEF_AudioMinPWM//defined(Pro_MinVol)
#define DEF_AudioMinPWM                 0x100//0x450//8 ohm 1.5W
#define DEF_AudioMidPWM                 0x500//0xA90   
#define DEF_AudioMaxPWM                 0x900//0xD90//
#elif 0
#define DEF_AudioMinPWM                 0x300//0x450//8 ohm 1.5W
#define DEF_AudioMidPWM                 0x500//0xA90   
#define DEF_AudioMaxPWM               	  0x7A0//0xD90//
#endif

BYTE code DAC_VOLUME[] =
{
	0,   1,   1,   1,   2,   3,   3,   4,   5,   5,
	6,   7,   7,   8,   8,   9,  10,  10,  11,  12,
	12,  13,  14,  14,  15,  16,  16,  17,  17,  18,
	19,  19,  20,  21,  21,  22,  23,  23,  24,  24,
	25,  26,  26,  27,  28,  28,  29,  30,  30,  31,
	32,  32,  33,  33,  34,  35,  35,  36,  36,  37,
	38,  38,  39,  40,  40,  41,  41,  42,  43,  43,
	44,  45,  45,  46,  46,  47,  48,  48,  49,  49,
	50,  51,  51,  52,  53,  53,  54,  54,  55,  56,
	56,  57,  58,  58,  59,  59,  60,  61,  61,  62,
	63
};

#else

#if USE_DAC_CODE

WORD code DAC_VOLUME[101] =
{
	#if 1
	401, 387, 364, 351, 338, 325, 312, 300, 287, 282,
	277, 274, 270, 267, 264, 260, 257, 254, 250, 247,
	245, 241, 237, 233, 229, 225, 221, 217, 213, 209,
	205, 203, 201, 199, 197, 195, 193, 191, 189, 187,
	185, 184, 183, 182, 181, 180, 179, 178, 177, 176,

	175, 173, 170, 167, 165, 162, 160, 157, 154, 152,
	150, 148, 146, 144, 142, 140, 138, 136, 134, 132,
	130, 128, 127, 125, 124, 122, 121, 119, 117, 116,
	115, 114, 113, 112, 111, 109, 108, 107, 105, 102,
	100, 100, 99, 99, 98, 98, 97, 97, 96, 96,
	95,
	#elif (ModelName==MODEL_HS245HFB)||(ModelName==MODEL_HS225HFB)||(ModelName==MODEL_HS275HFB)
	401, 398, 395, 392, 389, 386, 383, 380, 377, 374,
	371, 368, 365, 362, 359, 356, 553, 350, 347, 344,
	341, 338, 335, 332, 329, 326, 323, 320, 317, 314,
	311,  308,  305,  302,  299,  297,  295,  293,  291,  289,
	286,  283,  280,  277,  274,  271,  268,  265,  263,  260,
	258, 255, 250, 245, 240, 235, 230, 225, 220, 215,
	210, 205, 200, 195, 190, 185, 180, 175, 170, 165,
	160, 155, 150, 145, 140, 135, 130, 125, 120, 115,
	110, 105, 100,  95,  90,  85,  80,  75,  70,  65,
	60,  55,  50,  46,  43,  40,  37,  34,  31,  28,
	25
	#elif 1
	496, 491, 486, 481, 476, 471, 466, 461, 456, 451,
	448, 444, 439, 434, 429, 424, 420, 416, 411, 406,
	401, 396, 392, 387, 382, 377, 373, 368, 365, 360,
	355,  350,  345,  340,  335,  330,  325,  320,  315,  310,
	305,  300,  295,  290,  285,  280,  276,  272,  268,  264,
	260, 255, 250, 245, 240, 235, 230, 225, 220, 215,
	210, 205, 200, 195, 190, 185, 180, 175, 170, 165,
	160, 155, 150, 145, 140, 135, 130, 125, 120, 115,
	110, 105, 100,  95,  90,  85,  80,  75,  70,  65,
	60,  55,  50,  45,  40,  35,  30,  25,  20,  15,
	10
	#else
	//0
	0x23F, 0x23A, 0x236, 0x22F, 0x228, 0x221, 0x21A, 0x213, 0x20D, 0x206,
	//10
	0x200, 0x1E6, 0x1D6, 0x1D0, 0x1CA, 0x1C4, 0x1B8, 0x1B2, 0x1AC, 0x1A6,
	//20
	0x1A0, 0x19C, 0x199, 0x196, 0x193, 0x190, 0x18C, 0x189, 0x186, 0x183,
	//30
	0x180, 0x172, 0x169, 0x160, 0x157, 0x14E, 0x145, 0x13B, 0x132, 0x129,
	//40
	0x120, 0x118, 0x110, 0x108, 0x100, 0xFA, 0xF4, 0xEE, 0xE7, 0xDE,
	//50
	0xD0, 0xCA, 0xC1, 0xB9, 0xB5, 0xB0, 0xA8, 0xA1, 0x9C, 0x95,
	//60
	0x92, 0x89, 0x84, 0x7A, 0x74, 0x6C, 0x69, 0x65, 0x60, 0x5A,
	//70
	0x57, 0x54, 0x4F, 0x4B, 0x47, 0x43, 0x3F, 0x3B, 0x38, 0x35,
	//80
	0x33, 0x31, 0x2E, 0x2C, 0x2A, 0x28, 0x26, 0x24, 0x22, 0x20,
	//90
	0x1F, 0x1D, 0x1B, 0x19, 0x17, 0x16, 0x15, 0x14, 0x12, 0x11,

	0x10//100
	#endif
};

#endif


#if DAC_VALUE_TAB

#if 0//(ModelName==MODEL_HP247HJB)
BYTE code SPK_DAC_VOLUME[101] =
{
	48,  54,  60,  66,  72,  78,  84,  90,  94,  98,
	102, 107, 112, 115, 118, 122, 126, 130, 134, 138,
	142, 146, 150, 154, 156, 158, 160, 163, 165, 168,
	171, 173, 175, 178, 180, 182, 184, 186, 188, 190,
	191, 191, 192, 193, 194, 195, 196, 196, 197, 197,
	198, 199, 200, 202, 204, 205, 206, 208, 209, 210,
	211, 212, 212, 213, 213, 214, 214, 215, 215, 216,
	217, 217, 218, 218, 219, 220, 220, 221, 222, 223,
	224, 224, 225, 225, 226, 226, 227, 228, 229, 230,
	232, 232, 233, 233, 234, 235, 236, 237, 238, 239,
	240
};
#else
BYTE code SPK_DAC_VOLUME[101] =
{
	48,  54,  60,  66,  72,  78,  84,  90,  94,  98,
	102, 107, 112, 115, 118, 122, 126, 130, 134, 138,
	142, 146, 150, 154, 156, 158, 160, 163, 165, 168,
	171, 173, 175, 178, 180, 182, 184, 186, 188, 190,
	191, 193, 195, 198, 200, 203, 205, 207, 208, 210,
	211, 211, 212, 212, 213, 213, 214, 214, 215, 215,
	216, 216, 217, 217, 218, 218, 219, 219, 220, 220,
	221, 221, 222, 222, 223, 223, 224, 224, 225, 225,
	226, 226, 227, 227, 228, 228, 229, 229, 230, 230,
	232, 232, 233, 233, 234, 235, 236, 237, 238, 239,
	240
};
#endif


#elif defined(Pro_MinVol)
#define PWM_MinVol		Pro_MinVol
#define PWM_MidVol		Pro_MidVol
#define PWM_MaxVol		Pro_MaxVol
#else
#define PWM_MinVol		0x30
#define PWM_MidVol		0xA0
#define PWM_MaxVol		0xB0
#endif

#endif


#if defined(Pro_MinVol_P)
#define PWM_MinVol_P		Pro_MinVol_P
#define PWM_MidVol_P		Pro_MidVol_P
#define PWM_MaxVol_P		Pro_MaxVol_P
#elif 1
#define PWM_MinVol_P		0x00
#define PWM_MidVol_P		0x80
#define PWM_MaxVol_P		0xEF
#endif



#if (ModelName==YWPK_L58CDT9_NV1)
#define Analog_DPGAVolume   0x20
#define Digital_DPGAVolume	0x30
#else
#define Analog_DPGAVolume   0x40
#define Digital_DPGAVolume	0x30
#endif


#if Only_EarphoneDet
void mStar_AdjustVolume(BYTE volume)
{
	//MEM_MSWRITE_BIT(REG_2CDD, FALSE, BIT1);//TRUE
	//MEM_MSWRITE_BIT(REG_2CDD, FALSE, BIT5);//TRUE
	WORD xdata  SetVolume;
	if(UserPrefMuteState) volume = 0;
	if(MinVolumeValue >= volume) volume = 0;
	if(volume == 0)
	{
		#if  CHIP_ID==CHIP_TSUMU
		//msWriteByteMask(REG_2CA6, BIT4 , BIT4);
		#else
		msWriteByteMask(REG_2CA1, 0x000c, BIT3 | BIT2);
		#endif
		hw_SetMute();
		Delay1ms(2);
	}
	else
	{
		#if  CHIP_ID==CHIP_TSUMU
		/// msWriteByteMask(REG_2CA6, 0 , BIT4);
		msWrite2Byte(REG_2C2A, 0x000); // L-CH: -448
		msWrite2Byte(REG_2C2C, 0x000); // R-CH: -448
		#else
		msWriteByteMask(REG_2CA1, BIT3, BIT3 | BIT2);
		#endif
	}
	#if USE_DAC_CODE
	SetVolume = DAC_VOLUME[volume];
	#else
	if(volume < 50)
		SetVolume = ((DWORD)(volume) * (PWM_MidVol_P - PWM_MinVol_P)) / 50 + PWM_MinVol_P;
	else
		SetVolume = ((DWORD)(volume - 50) * (PWM_MaxVol_P - PWM_MidVol_P)) / 50 + PWM_MidVol_P;
	#if InverseVolume
	SetVolume = PWM_MaxVol_P - SetVolume + PWM_MinVol_P;
	#else
	#endif
	#endif
	#if  CHIP_ID==CHIP_TSUMU
	msAudioDPGA_SetVolume ( E_AUDIO_LEFT_RIGHT_CH, DAC_VOLUME[volume] );
	#elif CHIP_ID != CHIP_TSUMV
	msAudioDPGA_SetVolume ( E_AUDIO_LEFT_RIGHT_CH, SetVolume );
	#endif
}



#elif  Only_SpeakerDet
void mStar_AdjustVolume(BYTE volume)
{
	if(UserPrefMuteState)  volume = 0;
	if(volume == 0)
	{
		#if  CHIP_ID==CHIP_TSUMU
		msAudioEARout_Mute(TRUE);
		#else
		//msAudioDPGA_Mute();
		#endif
		hw_SetMute();
		Delay1ms(2);
		return;
	}
	else if(volume == 1 || volume == 50)
	{
		#if  CHIP_ID==CHIP_TSUMU
		msAudioEARout_Mute(FALSE);
		#else
		//msAudioDPGA_Mute();
		#endif
	}
	#if CHIP_ID==CHIP_TSUMU
	WORD u16Vol;
	BYTE u8Bank = msReadByte(REG_3200);
	msWriteByte( REG_3200, u8Bank );
	msWriteByte( REG_3200, 0x01 ); /*REG_3200[7:0];h02[7:0]*/ /*_CTRL_PWM_REGISTERS*/;
	if (volume > MaxVolumeValue)
		volume = MaxVolumeValue;
	else if (volume < MinVolumeValue)
		volume = MinVolumeValue;
	if(volume == 0)
	{
		u16Vol = 0x9B5;
		hw_SetMute();
		msAudioEARout_Mute( TRUE);
	}
	else
	{
		if(volume < 50)
			u16Vol = ((DWORD)volume * (DEF_AudioMidPWM - DEF_AudioMinPWM)) / 50 + DEF_AudioMinPWM;
		else
			u16Vol = ((DWORD)(volume - 50) * (DEF_AudioMaxPWM - DEF_AudioMidPWM)) / (100 - 50) + DEF_AudioMidPWM;
	}
	#if InverseVolume
	drvGPIO_SetPWMDuty(VolumePWM, DEF_AudioMaxPWM - u16Vol + DEF_AudioMinPWM);
	#else
	drvGPIO_SetPWMDuty(VolumePWM, u16Vol);
	#endif
	msWriteByte(REG_3200, u8Bank);
	#else
	if (volume > MaxVolumeValue)
		volume = MaxVolumeValue;
	else if (volume < MinVolumeValue)
		volume = MinVolumeValue;
	if(volume)
	{
		#if (DefVolume==100)
		volume = ((DWORD)volume * (PWM_MaxVol - PWM_MinVol)) / 100 + PWM_MinVol;
		#else
		if(volume < 50)
			volume = ((DWORD)volume * (PWM_MidVol - PWM_MinVol)) / 50 + PWM_MinVol;
		else
			volume = ((DWORD)(volume - 50) * (PWM_MaxVol - PWM_MidVol)) / (100 - 50) + PWM_MidVol;
		#endif
	}
	else
	{
		volume = 0;
	}
	#if InverseVolume	//+Duty power
	drvGPIO_SetBacklightDuty(VolumePWM, 0xFF - volume); //msAudioDPGA_SetVolume ( E_AUDIO_LEFT_RIGHT_CH, 0xFF-volume );//
	#else				//-Duty power
	drvGPIO_SetBacklightDuty(VolumePWM, volume);//msAudioDPGA_SetVolume ( E_AUDIO_LEFT_RIGHT_CH, volume );//
	#endif
	#endif
	hw_ClrMute();
	#if DEBUG_MSG
	printMsg("run to spk");
	#endif
}
#else  //2All_AudioDet

void mStar_AdjustVolume(BYTE volume)
{
	if(UserPrefMuteState)  volume = 0;
	if(volume == 0)
	{
		//if(bAudioInputStatus == AudioInput_Ear)
		#if  CHIP_ID==CHIP_TSUMU
		msAudioEARout_Mute(TRUE);
		#else
		msAudioDPGA_Mute();
		#endif
		hw_SetMute();
		Delay1ms(2);
		return;
	}
	#if  CHIP_ID==CHIP_TSUMU
	else if(volume == 1 || volume == 50)
	{
		msAudioEARout_Mute(FALSE);
	}
	#else
	else if((bAudioInputStatus == AudioInput_Spk))
		msAudioLineOutGain( Def_DACGain );
	#endif
	if(bAudioInputStatus == AudioInput_Ear)
	{
		WORD xdata  SetVolume = 0;
		#if DEBUG_MSG
		printMsg("run to ear");
		#endif
		hw_SetMute();
		#if USE_DAC_CODE
		SetVolume = DAC_VOLUME[volume];
		#else
		if(volume < 50)
			SetVolume = ((DWORD)(volume) * (PWM_MidVol_P - PWM_MinVol_P)) / 50 + PWM_MinVol_P;
		else
			SetVolume = ((DWORD)(volume - 50) * (PWM_MaxVol_P - PWM_MidVol_P)) / 50 + PWM_MidVol_P;
		#if InverseVolume
		SetVolume = PWM_MaxVol_P - SetVolume + PWM_MinVol_P;
		#else
		#endif
		#endif
		msAudioDPGA_SetVolume ( E_AUDIO_LEFT_RIGHT_CH, SetVolume );
	}
	else
	{
		#if CHIP_ID==CHIP_TSUMU
		WORD u16Vol;
		BYTE u8Bank = msReadByte(REG_3200);
		msWriteByte( REG_3200, u8Bank );
//msWriteByte( REG_3200, 0x01 ); /*REG_3200[7:0];h02[7:0]*/ /*_CTRL_PWM_REGISTERS*/;
		if (volume > MaxVolumeValue)
			volume = MaxVolumeValue;
		else if (volume < MinVolumeValue)
			volume = MinVolumeValue;
		if(volume < 50)
			u16Vol = ((DWORD)volume * (DEF_AudioMidPWM - DEF_AudioMinPWM)) / 50 + DEF_AudioMinPWM;
		else
			u16Vol = ((DWORD)(volume - 50) * (DEF_AudioMaxPWM - DEF_AudioMidPWM)) / (100 - 50) + DEF_AudioMidPWM;
		#if InverseVolume
		drvGPIO_SetPWMDuty(VolumePWM, DEF_AudioMaxPWM - u16Vol + DEF_AudioMinPWM);
		#else
		drvGPIO_SetPWMDuty(VolumePWM, u16Vol);
		#endif
		msWriteByte(REG_3200, u8Bank);
		#else
		if (volume > MaxVolumeValue)
			volume = MaxVolumeValue;
		else if (volume < MinVolumeValue)
			volume = MinVolumeValue;
		#if DAC_VALUE_TAB
		volume = SPK_DAC_VOLUME[volume];
		#elif (DefVolume==100)
		volume = ((DWORD)volume * (PWM_MaxVol - PWM_MinVol)) / 100 + PWM_MinVol;
		#else
		if(volume < 50)
			volume = ((DWORD)volume * (PWM_MidVol - PWM_MinVol)) / 50 + PWM_MinVol;
		else
			volume = ((DWORD)(volume - 50) * (PWM_MaxVol - PWM_MidVol)) / 50 + PWM_MidVol;
		#endif
		#if DAC_VALUE_TAB
		drvGPIO_SetBacklightDuty(VolumePWM, volume);
		#elif InverseVolume	//+Duty power
		drvGPIO_SetBacklightDuty(VolumePWM, 0xFF - volume); //msAudioDPGA_SetVolume ( E_AUDIO_LEFT_RIGHT_CH, 0xFF-volume );//
		#else				//-Duty power
		drvGPIO_SetBacklightDuty(VolumePWM, volume);//msAudioDPGA_SetVolume ( E_AUDIO_LEFT_RIGHT_CH, volume );//
		#endif
		#endif
		hw_ClrMute();
		#if DEBUG_MSG
		printMsg("run to spk");
		#endif
	}
}

#endif
#endif




#endif
#endif
















