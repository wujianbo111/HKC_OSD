///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvDAC.h
/// @author MStar Semiconductor Inc.
/// @brief  Audio DAC Function
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _drvDAC_H_
#define _drvDAC_H_
extern bit bToggleGainFlag;
extern BYTE xdata ToggleGainCntr;
#define ToggleGainPeriod    50 // unit: ms

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

// Audio channel selection
typedef enum _AUDIO_CH_SEL
{
	E_AUDIO_LEFT_CH = 0,
	E_AUDIO_RIGHT_CH = 1,
	E_AUDIO_LEFT_RIGHT_CH = 2
} AUDIO_CH_SEL;

// Line-out source selection
typedef enum _AUDIO_LINEOUT_SOURCE_SEL
{
	E_LINEOUT_FROM_LINEIN0 = 0,
	E_LINEOUT_FROM_LINEIN1 = 1,
	E_LINEOUT_FROM_DAC = 2,
	E_LINEOUT_FROM_AVSS = 3 // ground
} AUDIO_LINEOUT_SOURCE_SEL;

// Earphone-out source selection
typedef enum _AUDIO_EAROUT_SOURCE_SEL
{
	E_EAROUT_FROM_LINEIN0 = 0,
	E_EAROUT_FROM_LINEIN1 = 1,
	E_EAROUT_FROM_LINEOUT = 2,
	E_EAROUT_FROM_DACOUT = 3
} AUDIO_EAROUT_SOURCE_SEL;

//Internal PCM generator
typedef enum __AUDIO_PCM_FREQ
{
	PCM_250Hz,
	PCM_500HZ,
	PCM_1KHZ,
	PCM_1500HZ,
	PCM_2KHZ,
	PCM_3KHZ,
	PCM_4KHZ,
	PCM_6KHZ,
	PCM_8KHZ,
	PCM_12KHZ,
	PCM_16KHZ
} AUDIO_PCM_FREQ;
#if ENABLE_HDMI || ENABLE_DP_INPUT
typedef enum _AUDIO_SOURCE_SEL
{
	AUDIO_LINE_IN = 0,
	AUDIO_DIGITAL = 1,
} AUDIO_SOURCE_SEL;
#endif
//-------------------------------------------------------------------------------------------------
//  Function Prototype
//-------------------------------------------------------------------------------------------------
extern void msAudio_I2S_SPDIF_Init(void);
extern void msAudioDAC_Init( void );
extern void msAudioDPGA_Mute( void );
#if(!USE_DAC_ADJ)
extern void msAudioDPGA_SetVolume( AUDIO_CH_SEL chsel, int volume );
#endif
extern void msAudioLineout_SourceSel( AUDIO_LINEOUT_SOURCE_SEL src );
//extern AUDIO_LINEOUT_SOURCE_SEL msAudioLineout_GetSourceSel(void);
extern void msAudioEARout_Mute( Bool EnableMute );
extern void msAudioEAR_SourceSel( AUDIO_EAROUT_SOURCE_SEL src );
//extern AUDIO_EAROUT_SOURCE_SEL msAudioEARout_GetSourceSel(void);
//extern void msAudioDACPCMGenerator(Bool bEnable, AUDIO_PCM_FREQ eFreq);
extern void msAudioDACPowerDown( Bool bPowerDN );
extern void msAudioLineOutGain( BYTE val );
extern void msAudioGainToggle( void );
extern void msAudioGainForceToggle(void);	//130529 Nick
#endif //_drvDAC_H_


