/******************************************************************************
Copyright (c) 2003 MStar Semiconductor, Inc.
All rights reserved.
[Module Name]: msACE.h
[Date]:        01-Dec-2003
[Comment]:
Color adjust header file.
[Reversion History]:
 *******************************************************************************/
#ifndef _MSACE_H_
#define _MSACE_H_
#ifdef _MSACE_C_
#define _MSACEDEC_
#else
#define _MSACEDEC_ extern
#endif

#define MAIN_WINDOW 0
#define SUB_WINDOW  1

// sRGB matrix for PC
_MSACEDEC_ XDATA short *tSrgbMatrix;
// Color correction matrix for Video
_MSACEDEC_ XDATA short *tColorCorrectionMatrix;
//for tool
//extern XDATA short g_sCommandMatrix[3][3];

extern BYTE xdata g_bAccOnOff;

extern code short tStandardColorCorrectionMatrix[][3];
extern code short tMultimediaMatrix[][3];
extern code short tGameMatrix[][3];

extern code short tVideoStandardColorCorrectionMatrix[][3];
extern code short tMovieColorCorrectionMatrix[][3];
extern code short tVideoSportsColorCorrectionMatrix[][3];
extern code short tVideoNatureColorCorrectionMatrix[][3];

///////////////////////////////////////////////////////////////////////////////
// Basic color control function(Library)
///////////////////////////////////////////////////////////////////////////////



// ===Move to MSACE.h======================>>
#define SDTV  0
#define HDTV  1

//<<=====================================

//extern void msSetColorFomat(bit ColorFormat);
// Must call this function before using other function
void InitACEVar();
#define NO_CHANGE_SHARPNESS 0xFF
#define NO_CHANGE_STEP      0x80
void InitialPeaking(void);
void msAdjustSharpness(BYTE bScalerWin, BYTE ucSharpness, BYTE ucStep );

void msAdjustSubBrightness(BYTE bScalerWin,  BYTE u8brightnessR, BYTE u8brightnessG, BYTE u8brightnessB );
void msAdjustVideoContrast(BYTE bScalerWin, BYTE ucContrast );// 2004/12/10
void msAdjustVideoSaturation(BYTE bScalerWin, BYTE ucSaturation );// 2004/12/10
void msAdjustVideoHue(BYTE bScalerWin, BYTE ucHue );// 2004/12/10
void msAdjustHSC(BYTE bScalerWin, BYTE ucHue, BYTE ucSaturation, BYTE ucContrast); // 2004/12/10
///////////////////////////////////////////////////////////////////////////////
// Special color control function
///////////////////////////////////////////////////////////////////////////////
void msAdjustVideoRGB(BYTE bScalerWin, BYTE ucRCon, BYTE ucGCon, BYTE ucBCon);
void msAdjustVideoContrastRGB(BYTE bScalerWin, BYTE ucContrast, BYTE ucRCon, BYTE ucGCon, BYTE ucBCon);

void msAdjustPCContrast( BYTE bScalerWin, BYTE ucContrast );
void msAdjustPCRGB( BYTE bScalerWin, BYTE ucRed, BYTE ucGreen, BYTE ucBlue );
void msAdjustPCContrastRGB( BYTE bScalerWin, BYTE ucContrast, BYTE ucRed, BYTE ucGreen, BYTE ucBlue );
///////////////////////////////////////////////////////////////////////////////
// ACC
///////////////////////////////////////////////////////////////////////////////
void msAccSetup(WORD hstart_point, WORD hend_point, WORD vstart_point, WORD vend_point);
void msAccOnOff(BYTE on);
void LoadACETable(BYTE bScalerWin, BYTE *pColorTable, BYTE ucHue, BYTE ucSaturation, BYTE ucSubContrast); // 2004/11/2
extern void msACESetHDTVMode(BYTE isHDTV);
#endif
