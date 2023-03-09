/******************************************************************************
 Copyright (c) 2003 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: MsACE.c
 [Date]:        11-Nov-2003
 [Comment]:
   Color Adjust subroutines.
 [Reversion History]:
*******************************************************************************/

#define _MSACE_C_

#include <math.h>
// System

#include "types.h"
//#include "msRegTV.h"
//#include "board.h"
//#include "Ms_rwreg.h"
//#include "DebugMsg.h"
#include "msACE.h"
#include "ms_reg.h"
#include "Adjust.h"
//#include "MsGmaTbl.h"

//#include "UserPref.h"
//#include "misc.h"

//#include "myglobal.h"
#include "global.h"
//#include "ms_reg.h"
//#include "MZone.h"
//#include <intrins.h>

//#ifndef _ACE_MST8556T_
//#define _ACE_MST8556T_  //define in compiler
//#else
// CHIP_TSUML
//#endif

#if CHIP_ID == CHIP_TSUMV||CHIP_ID == CHIP_TSUM2
#define _ACE_TSUMV_
#elif CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD||CHIP_ID == CHIP_TSUM9 ||CHIP_ID == CHIP_TSUMF
#define _ACE_TSUMC_
#elif CHIP_ID == CHIP_TSUMU
 #define _ACE_MST8556T_
#else

#endif
//#define _ACE_TSUMV_
#define                 ACE_LIB_VERSION           0x0001
#define Y_MINUS16   1	//120420 Modify

#define SC_REGS        ((unsigned char volatile xdata *) 0x2F00)

#define _scReadByte(u16Addr)                     (SC_REGS[(u16Addr)&0xFF])
#define _scWriteByte(u16Addr,u8Value)            (SC_REGS[(u16Addr)&0xFF]=(u8Value))
#define _scWrite2Byte(u16Addr,u16Value)          {(SC_REGS[(u16Addr)&0xFF]=((u16Value)&0xFF));(SC_REGS[((u16Addr)&0xFF)+1]=((u16Value)>>8));}
#define _scRead2Byte(u16Addr)                    ((((WORD)SC_REGS[((u16Addr)&0xFF)+1])<<8)+SC_REGS[(u16Addr)&0xFF])
#define _scWriteByteMask(u16Addr,u8Value,u8Mask) ( SC_REGS[(u16Addr)&0xFF] = ( (SC_REGS[(u16Addr)&0xFF] & (~(u8Mask))) | ((u8Value) & (u8Mask))) )

#define     msDoubleBufferStart()
#define     msDoubleBufferEnd()


#define IS_RGB_RANGE_LIMITED 0//(SOURCE_INPUT_IS_ANDROID())  //130624 nick add Add RGB Limite Range define
// Internal
#include "msACE.h"
//#include "msDLC.h"

#define ENABLE_MAIN_NEW3X3     1

//extern code short tSRGB[3][3] ;
extern code short tNormalColorCorrectionMatrix[3][3] ;

XDATA BYTE g_bAccOnOff=0;
XDATA BYTE g_bHDTV  = FALSE;

// matrix used to convert RGB color space to YUV color space for SDTV
//code short tSDTVRgb2yuv[3][3] =
//{
//    {  0x0107,  0x0204,  0x0064 }, // 0.257,  0.504,  0.098
//    { -0x0098, -0x012A,  0x01C2 }, // -0.148, -0.291, 0.439
//    {  0x01C2, -0x0179, -0x0049 }  // 0.439,  -0.368, -0.071
//};

// matrix used to convert YUV color space to RGB color space, used for video input for SDTV
code short tSDTVYuv2rgb[3][3] =
{
    {   0x0662, 0x04A8,  0x0000 }, // 1.596,  1.164, 0
    {  -0x0341, 0x04A8, -0x0190 }, // -0.813, 1.164, -0.391
    {   0x0000, 0x04A8,  0x0812 }  // 0,      1.164, 2.018
};

// matrix used to convert RGB color space to YUV color space for HDTV
//code short tHDTVRgb2yuv[3][3] =
//{
//    {  0x00DA,  0x02DC,  0x004A }, // 0.213,  0.715,  0.072
//    { -0x0078, -0x0193,  0x020B }, // -0.117, -0.394, 0.511
//    {  0x020B, -0x01DB, -0x0030 }  // 0.511,  -0.464, -0.047
//};

// matrix used to convert YUV color space to RGB color space, used for video input for HDTV
code short tHDTVYuv2rgb[3][3] =
{
    {   0x072C, 0x04A8,  0x0000 }, // 1.793,  1.164, 0
    {  -0x0223, 0x04A8, -0x00DA }, // -0.534, 1.164, -0.213
    {   0x0000, 0x04A8,  0x0876 }  // 0,      1.164, 2.115
};

// For video
XDATA BYTE g_ucVideoRCon;
XDATA BYTE g_ucVideoGCon;
XDATA BYTE g_ucVideoBCon;
XDATA BYTE g_ucVideoContrast;
XDATA BYTE g_ucVideoSaturation;
XDATA BYTE g_ucVideoHue;

XDATA short g_sVideoSatHueMatrix[2][3][3];//XDATA short g_sVideoSatHueMatrix[3][3];
XDATA short g_sVideoContrastMatrix[2][3][3];//XDATA short g_sVideoContrastMatrix[3][3];

// For PC
XDATA BYTE g_ucPCRCon;
XDATA BYTE g_ucPCGCon;
XDATA BYTE g_ucPCBCon;
XDATA BYTE g_ucPCContrast;
XDATA short g_sPCConRGBMatrix[2][3][3];

// For erase the lost of brightness
XDATA BYTE g_ucMainDigiBrightness;
XDATA BYTE g_ucSubDigiBrightness;
XDATA BYTE g_ucBriteComp;

// for tools
//XDATA short g_sCommandMatrix[3][3];

void msACESetHDTVMode(BYTE isHDTV)
{
    if(isHDTV)
        g_bHDTV = TRUE;
    else
        g_bHDTV = FALSE;

}
WORD msACE_GetVersion(void)
{
    return ACE_LIB_VERSION;
}

void InitACEVar()
{
    // For video
    g_ucVideoRCon = 0x80;
    g_ucVideoGCon = 0x80;
    g_ucVideoBCon = 0x80;
    g_ucVideoContrast = 0x80;
    g_ucVideoSaturation = DefSaturationValue;//0x80;
    g_ucVideoHue = 50;

    g_sVideoSatHueMatrix[MAIN_WINDOW][0][0] = g_sVideoSatHueMatrix[MAIN_WINDOW][1][1] = g_sVideoSatHueMatrix[MAIN_WINDOW][2][2] = 1024;
    g_sVideoSatHueMatrix[MAIN_WINDOW][0][1] = g_sVideoSatHueMatrix[MAIN_WINDOW][1][0] = g_sVideoSatHueMatrix[MAIN_WINDOW][2][0] =
    g_sVideoSatHueMatrix[MAIN_WINDOW][0][2] = g_sVideoSatHueMatrix[MAIN_WINDOW][1][2] = g_sVideoSatHueMatrix[MAIN_WINDOW][2][1] = 0;

    g_sVideoContrastMatrix[MAIN_WINDOW][0][0] = g_sVideoContrastMatrix[MAIN_WINDOW][1][1] = g_sVideoContrastMatrix[MAIN_WINDOW][2][2] = 1024;
    g_sVideoContrastMatrix[MAIN_WINDOW][0][1] = g_sVideoContrastMatrix[MAIN_WINDOW][1][0] = g_sVideoContrastMatrix[MAIN_WINDOW][2][0] =
    g_sVideoContrastMatrix[MAIN_WINDOW][0][2] = g_sVideoContrastMatrix[MAIN_WINDOW][1][2] = g_sVideoContrastMatrix[MAIN_WINDOW][2][1] = 0;

    g_sVideoSatHueMatrix[SUB_WINDOW][0][0] = g_sVideoSatHueMatrix[SUB_WINDOW][1][1] = g_sVideoSatHueMatrix[SUB_WINDOW][2][2] = 1024;
    g_sVideoSatHueMatrix[SUB_WINDOW][0][1] = g_sVideoSatHueMatrix[SUB_WINDOW][1][0] = g_sVideoSatHueMatrix[SUB_WINDOW][2][0] =
    g_sVideoSatHueMatrix[SUB_WINDOW][0][2] = g_sVideoSatHueMatrix[SUB_WINDOW][1][2] = g_sVideoSatHueMatrix[SUB_WINDOW][2][1] = 0;

    g_sVideoContrastMatrix[SUB_WINDOW][0][0] = g_sVideoContrastMatrix[SUB_WINDOW][1][1] = g_sVideoContrastMatrix[SUB_WINDOW][2][2] = 1024;
    g_sVideoContrastMatrix[SUB_WINDOW][0][1] = g_sVideoContrastMatrix[SUB_WINDOW][1][0] = g_sVideoContrastMatrix[SUB_WINDOW][2][0] =
    g_sVideoContrastMatrix[SUB_WINDOW][0][2] = g_sVideoContrastMatrix[SUB_WINDOW][1][2] = g_sVideoContrastMatrix[SUB_WINDOW][2][1] = 0;

    // For PC
    g_ucPCRCon = 0x80;
    g_ucPCGCon = 0x80;
    g_ucPCBCon = 0x80;
    g_ucPCContrast = 0x80;

    g_sPCConRGBMatrix[MAIN_WINDOW][0][0] = g_sPCConRGBMatrix[MAIN_WINDOW][1][1] = g_sPCConRGBMatrix[MAIN_WINDOW][2][2] = 1024;
    g_sPCConRGBMatrix[MAIN_WINDOW][0][1] = g_sPCConRGBMatrix[MAIN_WINDOW][1][0] = g_sPCConRGBMatrix[MAIN_WINDOW][2][0] =
    g_sPCConRGBMatrix[MAIN_WINDOW][0][2] = g_sPCConRGBMatrix[MAIN_WINDOW][1][2] = g_sPCConRGBMatrix[MAIN_WINDOW][2][1] = 0;

    g_sPCConRGBMatrix[SUB_WINDOW][0][0] = g_sPCConRGBMatrix[SUB_WINDOW][1][1] = g_sPCConRGBMatrix[SUB_WINDOW][2][2] = 1024;
    g_sPCConRGBMatrix[SUB_WINDOW][0][1] = g_sPCConRGBMatrix[SUB_WINDOW][1][0] = g_sPCConRGBMatrix[SUB_WINDOW][2][0] =
    g_sPCConRGBMatrix[SUB_WINDOW][0][2] = g_sPCConRGBMatrix[SUB_WINDOW][1][2] = g_sPCConRGBMatrix[SUB_WINDOW][2][1] = 0;

    // Color matrix initilaize
    //tSrgbMatrix = &tSRGB[0][0];
    tColorCorrectionMatrix = &tNormalColorCorrectionMatrix[0][0];

    // For erase the lost of brightness
    g_ucMainDigiBrightness = 0x80;
    g_ucSubDigiBrightness = 0x80;
    g_ucBriteComp = 0;

    //g_ucACEConfig = 0;
    //msACEPCYUV2RGBCtl( FALSE );
    //msACEPCsRGBCtl( FALSE );

    // for tool
#if 1 //avoid compiler warning
    if (g_bHDTV!=g_bHDTV)
    {
        msACESetHDTVMode(FALSE);
        msACE_GetVersion();
        #if ENABLE_MAIN_NEW3X3
        msAdjustPCContrast( MAIN_WINDOW, 0x80 );
        msAdjustPCRGB( MAIN_WINDOW, 0x80, 0x80, 0x80 );
        #endif
        msAdjustPCContrast( SUB_WINDOW, 0x80 );
        msAdjustVideoRGB( SUB_WINDOW, 0x80, 0x80, 0x80 );
    }
#endif
#if CHIP_ID == CHIP_TSUMU	//121211 Modify
	{
		BYTE xdata ucBank;
		ucBank = msReadByte(SC0_00);
		msWriteByte(SC7_41, 0x11);
		msWriteByte(SC0_00, ucBank);
	}
#endif
}


#define PI  (3.14159265)

// sin function
short sine(BYTE ucValue)
{
    return (short)(sin((ucValue * PI) / 128.) * 1024.);
}

// cos function
short cosine(BYTE ucValue)
{
    return (short)(cos((ucValue * PI) / 128.) * 1024.);
}


xdata short (* sFirst)[3];
xdata short  (* sSecond)[3];
xdata short  (* sResult)[3];

//void ArrayMultiply(short sFirst[3][3], short sSecond[3][3], short sResult[3][3])
static void ArrayMultiply(void)
{
    BYTE LOCAL_TYPE ucRow, ucCol;

    //go line by line
    for(ucRow=0; ucRow!=3; ucRow++)
    {
        // go column by column
        for(ucCol=0; ucCol!=3; ucCol++)
        {
            sResult[ucRow][ucCol] = (((long)sFirst[ucRow][0] * sSecond[0][ucCol]) +
                                     ((long)sFirst[ucRow][1] * sSecond[1][ucCol]) +
                                     ((long)sFirst[ucRow][2] * sSecond[2][ucCol])) >> 10;
       } // for
    } // for
}

void SetVideoSatHueMatrix(BYTE bScalerWin)//static void SetVideoSatHueMatrix()
{
    short LOCAL_TYPE sTmp;
    BYTE LOCAL_TYPE ucHue;

    ucHue = ((g_ucVideoHue <= 50) ? (50 - g_ucVideoHue) : ~(g_ucVideoHue - 50));

//    ucHue = ((g_ucVideoHue >= 90) ? (90 - g_ucVideoHue) : ~(g_ucVideoHue -91));

    sTmp = ((short)g_ucVideoSaturation * 8);

    g_sVideoSatHueMatrix[bScalerWin][2][2] = ((((long)cosine(ucHue) * sTmp))>>10);
    g_sVideoSatHueMatrix[bScalerWin][0][0] = ((( (long)cosine(ucHue)* sTmp))>>10);

    g_sVideoSatHueMatrix[bScalerWin][2][0] = ((((long)sine(ucHue)   * sTmp))>>10);
    g_sVideoSatHueMatrix[bScalerWin][0][2] = (((-(long)sine(ucHue)  * sTmp))>>10);

    g_sVideoSatHueMatrix[bScalerWin][1][1] = 1024;
    g_sVideoSatHueMatrix[bScalerWin][0][1] = g_sVideoSatHueMatrix[bScalerWin][1][0] = g_sVideoSatHueMatrix[bScalerWin][1][2] = g_sVideoSatHueMatrix[bScalerWin][2][1] = 0;
}

void SetVideoContrastMatrix(BYTE bScalerWin)//static void SetVideoContrastMatrix()
{
    g_sVideoContrastMatrix[bScalerWin][0][0] = ( (WORD)g_ucVideoRCon * (g_ucVideoContrast)) >> 4;
    g_sVideoContrastMatrix[bScalerWin][1][1] = ( (WORD)g_ucVideoGCon * (g_ucVideoContrast)) >> 4;
    g_sVideoContrastMatrix[bScalerWin][2][2] = ( (WORD)g_ucVideoBCon * (g_ucVideoContrast)) >> 4;
}

xdata short *psMatrix;
//void msWriteColorMatrix( short* psMatrix )
//Main/Sub
void msWriteColorMatrix(BYTE bScalerWin)//static void msWriteColorMatrix()
{
    BYTE LOCAL_TYPE i,j;
    WORD  LOCAL_TYPE ucAddr ;// SC8_82//BYTE LOCAL_TYPE ucAddr = BK3_5E;
    short LOCAL_TYPE sTmp;
    BYTE LOCAL_TYPE u8Bank=_scReadByte(SC0_00);
#if defined(_ACE_MST8556T_) || defined(_ACE_TSUMV_)||defined(_ACE_TSUMC_)
    if(bScalerWin == MAIN_WINDOW)
        ucAddr = SC8_82;// SC8_82
    else
        ucAddr = SC8_6E;//

    _scWriteByte(SC0_00, 0x08);
#else
    BYTE LOCAL_TYPE u8OrgReg71;
    _scWriteByte(SC0_00, 0x03);
    u8OrgReg71=_scReadByte(SC3_71);
    if(bScalerWin == MAIN_WINDOW)
       _scWriteByteMask(SC3_71, BIT2, BIT2); //enable main NEW3x3
    else
       _scWriteByteMask(SC3_71, 0, BIT2); //use sub 3x3

    ucAddr = SC3_5E;//
#endif

    for(i=0; i!=3; i++)
    {
        for(j=0; j!=3; j++)
        {
            sTmp = psMatrix[i*3+j];
            //printf( "[%X]:", ucAddr );
            if( sTmp >= 0 )
            {
                if( sTmp > 0xfff )
                {
                    sTmp = 0xfff;
                }
                _scWrite2Byte( ucAddr, sTmp );//mStar_WriteWord( ucAddr+1, sTmp );
                //printf( "%X\r\n", sTmp );
            }
            else
            {
                sTmp = sTmp * -1;
                if( sTmp > 0xfff )
                {
                    sTmp = 0xfff;
                }
            #if defined(_ACE_TSUMV_)||defined(_ACE_TSUMC_)
                sTmp = 0x10000 - sTmp;//for 2's//sTmp |= 0x1000;
            #else
                sTmp |= 0x1000;
            #endif
                _scWrite2Byte( ucAddr, sTmp );//mStar_WriteWord( ucAddr+1, sTmp );
                //printf( "%X\r\n", sTmp );
            }
            ucAddr += 2;
        } // for
    } // for
#if !(defined(_ACE_MST8556T_) || defined(_ACE_TSUMV_)||defined(_ACE_TSUMC_))
    _scWriteByte(SC3_71, u8OrgReg71);
#endif
    _scWriteByte(SC0_00, u8Bank);
}

//Main/Sub
void msSetVideoColorMatrix(BYTE bScalerWin)//static void msSetVedioColorMatrix()
{
    XDATA short sResultTmp1[3][3];
    XDATA short sResultTmp2[3][3];
    typedef XDATA short TypArr[3][3];
    BYTE LOCAL_TYPE ucBank;
    //BYTE LOCAL_TYPE ucColorBank;
    short* LOCAL_TYPE psOutTab;
    //XDATA BYTE ucTmpBri;

    // Adjust hue&saturation, and then YUV to RGB
    if(g_bHDTV)
        sFirst = tHDTVYuv2rgb;
    else
        sFirst = tSDTVYuv2rgb;
    sSecond=g_sVideoSatHueMatrix[bScalerWin];
    sResult=sResultTmp1;
    ArrayMultiply();
    //ArrayMultiply( tSDTVYuv2rgb, g_sVideoSatHueMatrix, sResultTmp1 );

    // Adjust contrast-RGB
    sFirst=g_sVideoContrastMatrix[bScalerWin];
    sSecond=sResultTmp1;
    sResult=sResultTmp2;
    ArrayMultiply();
    //ArrayMultiply( g_sVideoContrastMatrix, sResultTmp1, sResultTmp2 );

    psOutTab = (short*)sResultTmp2;

    // Do color correction
    //ArrayMultiply( tVedioColorCorrectionMatrix, (TypArr)psOutTab, sResultTmp1 );

    sFirst=(TypArr)tColorCorrectionMatrix;
    sSecond=(TypArr)psOutTab;
    sResult=sResultTmp1;
    ArrayMultiply();
    //ArrayMultiply( (TypArr)tColorCorrectionMatrix, (TypArr)psOutTab, sResultTmp1 );

    psOutTab = (short*)sResultTmp1;

    // g_ucBriteComp = sResultTmp1[1][1] >> 6;

    ucBank = _scReadByte(SC0_00); // Backup bank

    msDoubleBufferStart();

    //msWriteByte(SC0_00, REG_BANK_PIP);//ucColorBank);
    psMatrix=psOutTab;
    msWriteColorMatrix(bScalerWin);

#if (defined(_ACE_MST8556T_) || defined(_ACE_TSUMV_)||defined(_ACE_TSUMC_))
    _scWriteByte(SC0_00, 0x08);
    //msWriteColorMatrix( psOutTab );
	#if Y_MINUS16	//120420 Modify
    if (bScalerWin == MAIN_WINDOW)
        _scWriteByteMask( SC8_81, BIT7|BIT6|BIT5|BIT3, BIT7|BIT6|BIT5|BIT4|BIT3 ); // Enable MainWin color matrix&Change R/B range Sky110215
    else
        _scWriteByteMask( SC8_80, BIT7|BIT6|BIT5|BIT3, BIT7|BIT6|BIT5|BIT4|BIT3 ); // Enable SubWin color matrix&Change R/B range Sky110215
  	#else
    if (bScalerWin == MAIN_WINDOW) //Jison BIT6 Y minus 16 ctrl by outside
        _scWriteByteMask( SC8_81, BIT7|BIT5|BIT3, BIT7|BIT5|BIT4|BIT3 ); // Enable MainWin color matrix&Change R/B range Sky110215
    else
        _scWriteByteMask( SC8_80, BIT7|BIT5|BIT3, BIT7|BIT5|BIT4|BIT3 ); // Enable SubWin color matrix&Change R/B range Sky110215
	#endif
#else
    _scWriteByte(SC0_00, 0x03);
    #if Y_MINUS16   //120420 Modify
            if (bScalerWin == MAIN_WINDOW)
             {
                _scWriteByteMask( SC3_71, BIT2|BIT0, BIT2|BIT0 );  //0x15
                 _scWriteByteMask( SC3_70, BIT5|BIT4|BIT2|BIT0|BIT3, BIT5|BIT4|BIT2|BIT1|BIT0|BIT3 );  //0x15
             }
            else
             {
                    _scWriteByteMask( SC3_71, BIT0, BIT2|BIT0 );  //0x15
                    _scWriteByteMask( SC3_70, BIT4|BIT2|BIT0|BIT3, BIT4|BIT2|BIT1|BIT0|BIT3 );  //0x15
            }
    #else
           if (bScalerWin == MAIN_WINDOW)
            {
               _scWriteByteMask( SC3_71, BIT2|BIT0, BIT2|BIT0 );  //0x15
                _scWriteByteMask( SC3_70, BIT5|BIT4|BIT2|BIT0, BIT5|BIT4|BIT2|BIT1|BIT0 );  //0x15
            }
           else
            {
                   _scWriteByteMask( SC3_71, BIT0, BIT2|BIT0 );  //0x15
                   _scWriteByteMask( SC3_70, BIT4|BIT2|BIT0, BIT4|BIT2|BIT1|BIT0 );  //0x15
           }
    #endif
#endif
    //msWriteByte( BK0_72, ucTmpBri );
    //msWriteByte( BK0_73, ucTmpBri );
    //msWriteByte( BK0_74, ucTmpBri );

    msDoubleBufferEnd();

    _scWriteByte(SC0_00, ucBank); // Restore bank
}

//Main/Sub
#if 0
void msAdjustHSC(BYTE bScalerWin,BYTE ucHue, BYTE ucSaturation, BYTE ucContrast)
{
    g_ucVideoSaturation = ucSaturation;
    g_ucVideoContrast = ucContrast;
    g_ucVideoHue = ucHue;
    SetVideoSatHueMatrix(bScalerWin);
    SetVideoContrastMatrix(bScalerWin);

    msSetVideoColorMatrix(bScalerWin);
}
#endif

#if MWEFunction

//Main/Sub
void msAdjustVideoContrast(BYTE bScalerWin, BYTE ucContrast )// 2004/12/8
{
    g_ucVideoContrast = ucContrast;
    SetVideoContrastMatrix(bScalerWin);
    msSetVideoColorMatrix( bScalerWin);
}

//Main/Sub
void msAdjustVideoSaturation(BYTE bScalerWin, BYTE ucSaturation )
{
     g_ucVideoSaturation = ucSaturation;
    SetVideoSatHueMatrix(bScalerWin);
    msSetVideoColorMatrix(bScalerWin);
}

//Main/Sub
void msAdjustVideoHue(BYTE bScalerWin, BYTE ucHue )
{
    g_ucVideoHue = ucHue;
    SetVideoSatHueMatrix(bScalerWin);
    msSetVideoColorMatrix( bScalerWin);
}


//Main/Sub
void msAdjustSubBrightness(BYTE bScalerWin,  BYTE u8brightnessR, BYTE u8brightnessG, BYTE u8brightnessB )
{
  BYTE LOCAL_TYPE ucBank;

#if defined(_ACE_MST8556T_) || defined(_ACE_TSUMV_)||defined(_ACE_TSUMC_)

    //WORD wSubBrightness = ((WORD)u8brightness)<<3;
    WORD wAddr;

    ucBank = _scReadByte(SC0_00); // Backup bank

    if(bScalerWin == MAIN_WINDOW)
        wAddr = SC8_62;
    else
        wAddr = SC8_68;

    _scWriteByte(SC0_00, 0x08);
   #if defined(_ACE_TSUMV_)
    u8brightnessR -= 0x80;  //120425 Modify
    
    u8brightnessG -= 0x80;  //120425 Modify 
    
    u8brightnessB -= 0x80;  //120425 Modify 
  
    _scWrite2Byte( wAddr, u8brightnessR );
    _scWrite2Byte( wAddr+2, u8brightnessG );
    _scWrite2Byte( wAddr+4, u8brightnessB );
  #elif defined(_ACE_TSUMC_)
    if(IS_RGB_RANGE_LIMITED)		//130723 gordon
    	{
    	      u8brightnessR=u8brightnessR-(8);//16*1.18
	      u8brightnessG=u8brightnessG-(8);
    	      u8brightnessB=u8brightnessB-(8);
		  
		    _scWrite2Byte( wAddr, (((WORD)u8brightnessR)<<3)-0x400 );
		    _scWrite2Byte( wAddr+2, (((WORD)u8brightnessG)<<3)-0x400 );
		    _scWrite2Byte( wAddr+4, (((WORD)u8brightnessB)<<3)-0x400 );
    	}
	else
	{

		    _scWrite2Byte( wAddr, (((WORD)u8brightnessR)<<3)-0x400 );
		    _scWrite2Byte( wAddr+2, (((WORD)u8brightnessG)<<3)-0x400 );
		    _scWrite2Byte( wAddr+4, (((WORD)u8brightnessB)<<3)-0x400 );

	}
  #else
    _scWrite2Byte( wAddr, (((WORD)u8brightnessR)<<3) );
    _scWrite2Byte( wAddr+2, (((WORD)u8brightnessG)<<3) );
    _scWrite2Byte( wAddr+4, (((WORD)u8brightnessB)<<3) );
  #endif
    _scWriteByte(SC0_00, ucBank);

#else
    ucBank = _scReadByte(SC0_00);
    if(bScalerWin == MAIN_WINDOW)
    {
        _scWriteByte(SC0_00, 0x00); // Bank 0

        _scWriteByte(SC0_2B, u8brightnessR);
        _scWriteByte(SC0_2C, u8brightnessG);
        _scWriteByte(SC0_2D, u8brightnessB);
    }
    else
    {
        _scWriteByte(SC0_00, 0x03); // Bank 3

        _scWriteByte(SC3_72, u8brightnessR);
        _scWriteByte(SC3_73, u8brightnessG);
        _scWriteByte(SC3_74, u8brightnessB);
    }
  _scWriteByte(SC0_00, ucBank);
  #endif
}
#endif



#if 1
//Main/Sub
void msAdjustVideoRGB( BYTE bScalerWin, BYTE ucRed, BYTE ucGreen, BYTE ucBlue )
{
    msAdjustVideoContrastRGB( bScalerWin, g_ucVideoContrast, ucRed, ucGreen, ucBlue );
}

void msAdjustVideoContrastRGB(BYTE bScalerWin, BYTE ucContrast, BYTE ucRCon, BYTE ucGCon, BYTE ucBCon)
{
    g_ucVideoContrast = ucContrast;
    g_ucVideoRCon = ucRCon;
    g_ucVideoGCon = ucGCon;
    g_ucVideoBCon = ucBCon;
    SetVideoContrastMatrix(bScalerWin);
    msSetVideoColorMatrix(bScalerWin);
}
#endif

#if ENABLE_MAIN_NEW3X3
void SetPCConRGBMatrix(BYTE bScalerWin)
{
    g_sPCConRGBMatrix[bScalerWin][0][0] = ( (WORD)g_ucPCRCon * (g_ucPCContrast)) >> 4;
    g_sPCConRGBMatrix[bScalerWin][1][1] = ( (WORD)g_ucPCGCon * (g_ucPCContrast)) >> 4;
    g_sPCConRGBMatrix[bScalerWin][2][2] = ( (WORD)g_ucPCBCon * (g_ucPCContrast)) >> 4;
}

//Main/Sub
static void msSetPCColorMatrix( BYTE bScalerWin )
{
    //XDATA short sResultTmp1[3][3];
    //XDATA short sResultTmp2[3][3];
    BYTE ucBank;//, ucColorBank;
    short* psOutTab;

    //BYTE ucReg70Val;
    ucBank = _scReadByte(SC0_00);
    //ucColorBank = REG_BANK_PIP;
    psOutTab = (short*)g_sPCConRGBMatrix;

    {
        //ucReg70Val = 0x80;//ucReg70Val = 0x30;
    }

    msDoubleBufferStart();

    //msWriteByte(BK0_00, ucColorBank);
    psMatrix=psOutTab;
    msWriteColorMatrix(bScalerWin);// psOutTab );
    //msWriteByte(BK3_70, ucReg70Val);
#if defined(_ACE_MST8556T_) || defined(_ACE_TSUMV_)||defined(_ACE_TSUMC_)
    _scWriteByte(SC0_00, 0x08);
	#if Y_MINUS16	//120503 Modify
            if(bScalerWin == MAIN_WINDOW) //Jison BIT6 Y minus 16 ctrl by outside
                _scWriteByteMask(SC8_81, BIT7, BIT7|BIT6|BIT5|BIT4|BIT3); //color matrix enable
            else
                _scWriteByteMask(SC8_80, BIT7, BIT7|BIT6|BIT5|BIT4|BIT3);
	#else
            if(bScalerWin == MAIN_WINDOW) //Jison BIT6 Y minus 16 ctrl by outside
                _scWriteByteMask(SC8_81, BIT7, BIT7|BIT5|BIT4|BIT3); //color matrix enable
            else
                _scWriteByteMask(SC8_80, BIT7, BIT7|BIT5|BIT4|BIT3);
	#endif
#else
    _scWriteByte(SC0_00, 0x03);
    #if Y_MINUS16   //120503 Modify
        if(bScalerWin == MAIN_WINDOW)
            {
            _scWriteByteMask(SC3_71, BIT2, BIT2);
            _scWriteByteMask( SC3_70,BIT5|BIT4, BIT5|BIT4|BIT3|BIT2|BIT1|BIT0 );  //0x10	//120919 Modify
            }
        else
            {
            _scWriteByteMask(SC3_71, 0, BIT2);
            _scWriteByteMask( SC3_70, BIT5|BIT4|BIT2|BIT0, BIT5|BIT4|BIT3|BIT2|BIT1|BIT0 );	//120919 Modify  
            }
    #else
        if(bScalerWin == MAIN_WINDOW)
            {
            _scWriteByteMask(SC3_71, BIT2, BIT2);
            _scWriteByteMask( SC3_70,BIT5|BIT4, BIT5|BIT4|BIT2|BIT1|BIT0 );  //0x10
            }
        else
            {
            _scWriteByteMask(SC3_71, 0, BIT2);
            _scWriteByteMask( SC3_70, BIT5|BIT4|BIT2|BIT0, BIT5|BIT4|BIT2|BIT1|BIT0 );  
            }
     #endif
    //Jison BIT3 Y minus 16 ctrl by outside
	
#endif
    msDoubleBufferEnd();
    _scWriteByte(SC0_00, ucBank);
    //msWriteByte(BK0_00, ucBank);
}
#endif

#if ENABLE_MAIN_NEW3X3

//Main/Sub
void msAdjustPCContrastRGB( BYTE bScalerWin, BYTE ucContrast, BYTE ucRed, BYTE ucGreen, BYTE ucBlue )
{

	if(IS_RGB_RANGE_LIMITED)	//130624 nick add
	{
	       msAdjustSubBrightness(MAIN_WINDOW,128,128,128);
		g_ucPCContrast=ucContrast*1.18;		//130723 gordon
		//printData("g_ucPCContrast==%d", g_ucPCContrast);
		//printData("g_ucPCContrastR==%d", ucRed);
		//printData("g_ucPCContrast==%d", ucGreen);
		//printData("g_ucPCContrast==%d", ucBlue);

	}
	else
		g_ucPCContrast = ucContrast;
    g_ucPCRCon = ucRed;
    g_ucPCGCon = ucGreen;
    g_ucPCBCon = ucBlue;
    SetPCConRGBMatrix(bScalerWin);
    msSetPCColorMatrix( bScalerWin );
}

//Main/Sub
void msAdjustPCContrast( BYTE bScalerWin, BYTE ucContrast )
{
    msAdjustPCContrastRGB( bScalerWin, ucContrast, g_ucPCRCon, g_ucPCGCon, g_ucPCBCon );
}

//Main/Sub
void msAdjustPCRGB( BYTE bScalerWin, BYTE ucRed, BYTE ucGreen, BYTE ucBlue )
{
    msAdjustPCContrastRGB( bScalerWin, g_ucPCContrast, ucRed, ucGreen, ucBlue );
}
#endif


/////////////////////////////////////////////////////////////////////
// ACC
/////////////////////////////////////////////////////////////////////

#define ACC_H_POS       (PANEL_H_START+PANEL_WIDTH/4)
#define ACC_V_POS       (PANEL_HEIGHT/4)
#define ACC_H_SIZE      PANEL_WIDTH/2
#define ACC_V_SIZE      PANEL_HEIGHT/2

#define ACC_H_POS_SPLIT       (PANEL_H_START+PANEL_WIDTH/2)
#define ACC_V_POS_SPLIT       (0)
#define ACC_H_SIZE_SPLIT      PANEL_WIDTH/2
#define ACC_V_SIZE_SPLIT      PANEL_HEIGHT

#define ACC_H_POS_FULL       (PANEL_H_START)
#define ACC_V_POS_FULL       (0)
#define ACC_H_SIZE_FULL      PANEL_WIDTH
#define ACC_V_SIZE_FULL      PANEL_HEIGHT

// para[0]: flag
// para[1~2]:H-Start
// para[3~4]:V-Start
// para[5~6]:H-Size
// para[7~8]:V-Size


XDATA WORD g_uiHStart;
XDATA WORD g_uiHEnd;
XDATA WORD g_uiVStart;
XDATA WORD g_uiVEnd;
/*

#if CHIP_ID == CHIP_TSUM2 || CHIP_ID == CHIP_TSUMV||CHIP_ID == CHIP_TSUMC||CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9	//121108 Modify
#define WAIT_V_OUTPUT_BLANKING_START()   { if(!SyncLossState()&&PanelOnFlag){SetTimOutConter(30);while(((msReadByte(SC0_E0)&BIT0)==0)&&bTimeOutCounterFlag);\
                                        SetTimOutConter(30);while(((msReadByte(SC0_E0)&BIT0)!=0)&&bTimeOutCounterFlag);}}//20130227 modify for DC OFF issue
#endif
*/

#if MWEFunction

void msAccSetup( WORD phstart_point, WORD phend_point, WORD pvstart_point, WORD pvend_point)
//void msAccSetup()
{
    BYTE LOCAL_TYPE ucBank;
    WORD LOCAL_TYPE panel_h_start;
    #ifdef _ACE_MST8556T_
    //BYTE LOCAL_TYPE u8HDiv=(phstart_point&0x8000?2:1); //Jison 110322
    BYTE LOCAL_TYPE u8HDiv=2; //Jison 110322
    #else
    BYTE LOCAL_TYPE u8HDiv=1; //Jison 110322
    #endif
    g_uiHStart = (phstart_point&0x7FFF)/u8HDiv; //Jison 110322, bit15 is used to indicate H divider=2 if set
    g_uiHEnd = phend_point/u8HDiv; //Jison 110322
    g_uiVStart = pvstart_point;
    g_uiVEnd = pvend_point;

    #if 0
    if(!SupportMWE())
        return;
    #endif
    ucBank = _scReadByte( SC0_00 );

    _scWriteByte(SC0_00, 0x00);
    panel_h_start=_scRead2Byte(SC0_12); // Hor. DE start

    g_uiHStart = g_uiHStart + panel_h_start;
    g_uiHEnd   = g_uiHEnd   + panel_h_start;
#if 1//def _ACE_MST8556T_// for MST8556T
	#if CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUMC||CHIP_ID == CHIP_TSUM9	||CHIP_ID == CHIP_TSUMF//130924 xiandi
	if(g_uiHEnd>g_uiHStart)
	#endif
    g_uiHEnd -=1;
#endif
	#if CHIP_ID == CHIP_TSUM2 || CHIP_ID == CHIP_TSUMV||CHIP_ID == CHIP_TSUMC||CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9 ||CHIP_ID == CHIP_TSUMF	//121108 Modify
	WAIT_V_OUTPUT_BLANKING_START();
	#else
	mStar_WaitForDataBlanking();	//111223 Modify
	#endif
    _scWriteByte(SC0_00, 0x03);
    _scWrite2Byte(SC3_18,g_uiHStart);
    _scWrite2Byte(SC3_1C,g_uiHEnd);

    _scWrite2Byte(SC3_1E,g_uiVStart);
    _scWrite2Byte(SC3_1A,g_uiVEnd);

    _scWriteByte(SC0_00, ucBank);

}
void msAccOnOff( BYTE on )
{
    BYTE LOCAL_TYPE ucBank=_scReadByte(SC0_00);
    //WORD LOCAL_TYPE time_out;
    //WORD LOCAL_TYPE hstart,vstart;

    #if 0
    if(!SupportMWE())
        return;
    #endif

    //msWriteByte(BK0_32, 0x01);//0x00);
	mStar_WaitForDataBlanking();	//120204 Modify
#ifdef _ACE_MST8556T_//forMST8556T
    _scWriteByte(SC0_00, 0x03);
    if(on != 0)
    {
        g_bAccOnOff = TRUE;
        _scWriteByteMask(SC3_17, BIT0, BIT0);
    }
    else
    {
        g_bAccOnOff = FALSE;
        _scWriteByteMask( SC3_17, 0, BIT0 );
    }

    _scWriteByte(SC0_00, ucBank);
#else //_ACE_TSUMV_
    _scWriteByte(SC0_00, 0x00);
    if(on != 0)
    {
        g_bAccOnOff = TRUE;
        _scWriteByteMask(SC0_5C, BIT3, BIT3);
    }
    else
    {
        g_bAccOnOff = FALSE;
        _scWriteByteMask( SC0_5C, 0, BIT3 );
    }

    _scWriteByte(SC0_00, ucBank);
#endif
}

#endif

#if 1
#define INIT_SUBWIN_PEAKING_CTL     0x03
#define INIT_SUBWIN_CORING          0x44
#define INIT_SUBWIN_CTI             0x90
//#define INIT_SUBWIN_LTI             0x4C

void InitialPeaking(void)
{
  BYTE u8Bank=_scReadByte(SC0_00);
#if defined(_ACE_MST8556T_) || defined(_ACE_TSUMV_)//MST8556T
  _scWriteByte(SC0_00,0x07);
  _scWriteByteMask( SC7_20, BIT0,BIT0 );    // enable peaking of main window
  _scWriteByte( SC7_64, 0x05 );    // enable peaking of main window
  _scWriteByteMask( SC7_3B, BIT0,BIT0 );    // enable peaking of sub window
  _scWriteByte(SC7_21, INIT_SUBWIN_CORING); //Jison 110323, 0x00 will cause native timing too sharp while OSD sharpness 100%
  _scWriteByte(SC7_3C, INIT_SUBWIN_CORING);

  _scWriteByte(SC0_00,0x08);
  _scWriteByteMask(SC8_61, BIT6, BIT6);//Enable sub bri function
#elif defined(_ACE_TSUMC_)
      BYTE uci;
      _scWriteByte(SC0_00,0x08);
      _scWriteByteMask(SC8_61, BIT6, BIT6);//Enable sub bri function
      _scWriteByte(SC0_00,0x0B);
      //Over/Under shoort Setting  //main and sub use the same setting
      for( uci = 0; uci < 8; uci ++ )
      {
           _scWriteByteMask(SCB_40+uci, 0xFF,0xFF);       //overshoort¡GSCB_40~SCB_47
           _scWriteByteMask(SCB_48+uci, 0xFF,0xFF);       //undershoort¡GSCB_48~SCB_4F
      }   
      for( uci = 0; uci < 4; uci ++ )
      {   //Term Setting for main win
           _scWriteByteMask(SCB_38+uci*2  , (uci*2<<4)|(uci*2+1)  ,0x77);     
           _scWriteByteMask(SCB_38+uci*2+1, (uci*2<<4)|(uci*2+1) ,0x77);      
          //Term Setting for sub win   
           _scWriteByteMask(SCB_58+uci*2  , (uci*2<<4)|(uci*2+1)  ,0x77);     
           _scWriteByteMask(SCB_58+uci*2+1, (uci*2<<4)|(uci*2+1) ,0x77);      
      }   
      //_scWriteByteMask( SCB_20, BIT0    , BIT0 );   //main post peaking enable, Setting in msAdjustSharpness()
      _scWriteByteMask( SCB_21, 0x01  , 0xFF );   //main Bank1 peaking enable
  
      //_scWriteByteMask( SCB_28, BIT0    , BIT0 );   //sub post peaking enable, Setting in msAdjustSharpness()
      _scWriteByteMask( SCB_29, 0x01  , 0xFF );   //sub Bank1~8 peaking enable
      //main win Post Coring Setting
      _scWriteByteMask( SCB_26, 0x42  , 0xFF );           //[7:4]:Coring_TH_2 ,[3:0]:Coring_TH_1
      //sub win Post Coring Setting
      _scWriteByteMask( SCB_2E, 0x42  , 0xFF );           //[7:4]:Coring_TH_2 ,[3:0]:Coring_TH_1
      //coring step - default
      _scWriteByteMask( SCB_61, 0x33  , 0x33 );           //[5:4]:Sub Coring_TH_Step ,[1:0]:Main Coring_TH_Step

#else
  _scWriteByte(SC0_00, 0x03);
  // brightness
  _scWriteByte(SC3_71, 0x01);
  _scWriteByte(SC3_72, 0x70);
  _scWriteByte(SC3_73, 0x70);
  _scWriteByte(SC3_74, 0x70);

  #if 1//CHIP_TSUMA
  _scWriteByteMask(SC3_3B,BIT0,BIT0); //enable MWE peaking
  _scWriteByte(SC3_3E,0xFF);
  _scWriteByte(SC3_3F,0xFF);
  _scWriteByte(SC3_4E,0xFF);
  _scWriteByte(SC3_4F,0xFF);
  _scWriteByte(SC0_00, 0x00);
  _scWriteByteMask(SC0_5C,BIT0,BIT0); //enable main wnd peaking
  #endif
#endif
  _scWriteByte(SC0_00,u8Bank);
}
void msAdjustSharpness(BYTE bScalerWin ,BYTE ucSharpness, BYTE ucStep )
{
    BYTE LOCAL_TYPE ucBank;
    BYTE LOCAL_TYPE ucTmp = 0;
    ucBank = _scReadByte(SC0_00);
    
#if defined(_ACE_TSUMV_)
    _scWriteByte(SC0_00, 0x07);
    if(bScalerWin == MAIN_WINDOW)
    {
        _scWriteByteMask(SC7_3B, BIT4, BIT4);
        if( NO_CHANGE_SHARPNESS == ucSharpness )
            ucSharpness = _scReadByte(SC7_23)&0x1F;    // MWE window Y peaking coefficient
        else
        {
            ucSharpness&=0x3F;
            if (ucSharpness>=0x20)
                ucSharpness-=0x20;
            else
                ucSharpness=0x40-ucSharpness;                
        }

        if( NO_CHANGE_STEP == ucStep )
            ucStep = _scReadByte(SC7_23)&0x40;                 // MWE window peaking step
        else
            ucStep<<=6;
        
        _scWriteByte(SC7_23, (ucStep)| ucSharpness); // Bank 3
    }
    else
    {
        if( NO_CHANGE_SHARPNESS == ucSharpness )
            ucSharpness = _scReadByte(SC7_3F)&0x1F;    // MWE window Y peaking coefficient
        else
        {
            ucSharpness&=0x3F;
            if (ucSharpness>=0x20)
                ucSharpness-=0x20;
            else
                ucSharpness=0x40-ucSharpness;                
        }
        if( NO_CHANGE_STEP == ucStep )
            ucStep = _scReadByte(SC7_3B)&BIT4;                 // MWE window peaking step
        else
            ucStep=(ucStep?0:BIT4);

        _scWriteByte(SC7_3B,  _scReadByte(SC7_3B)&(~BIT4)|ucStep); //Peaking Coefficient Extension as x.xxxx.
        _scWriteByte(SC7_3F,  ucSharpness);

    }
#elif defined(_ACE_TSUMC_) // Sharpness gain, SCB_27: xx.xxxx foramt, band1 coef(sharp or blur), SCB_30: xxx.xxx format
    
        _scWriteByte(SC0_00, 0x0B);
    
        ucSharpness&=0x3F;
        ucStep&=0x03;
    
        if(bScalerWin == MAIN_WINDOW)
        {
            _scWriteByte(SCB_27,  0x3F);    //gain for all band
            _scWriteByte(SCB_30,  ucSharpness); //bank1 coeff
            _scWriteByte(SCB_22,  (ucStep<<6 |ucStep<<4|ucStep<<2|ucStep)); //for band1~4
            _scWriteByte(SCB_23,  (ucStep<<6 |ucStep<<4|ucStep<<2|ucStep)); //for band5~8
            _scWriteByteMask( SCB_20, BIT0  , BIT0 );   //main post peaking enable      
        }
        else
        {
            _scWriteByte(SCB_2F,  0x3F);    //gain for all band
            _scWriteByte(SCB_50,  ucSharpness); //bank1 coeff
            _scWriteByte(SCB_2A,  (ucStep<<6 |ucStep<<4|ucStep<<2|ucStep)); //for band1~4
            _scWriteByte(SCB_2B,  (ucStep<<6 |ucStep<<4|ucStep<<2|ucStep)); //for band5~8
            _scWriteByteMask( SCB_28, BIT0  , BIT0 );   //sub post peaking enable
        }
        

    
#elif defined(_ACE_MST8556T_) 
    _scWriteByte(SC0_00, 0x07);
    if(bScalerWin == MAIN_WINDOW)
    {
        if( NO_CHANGE_SHARPNESS == ucSharpness )
            ucSharpness = _scReadByte(SC7_23)&0x1F;    // MWE window Y peaking coefficient
        else
            ucSharpness&=0x1F;

        if( NO_CHANGE_STEP == ucStep )
            ucStep = _scReadByte(SC7_23)&0x40;                 // MWE window peaking step
        else
            ucStep<<=6;

        _scWriteByte(SC7_23, (ucStep)| ucSharpness); // Bank 3
    }
    else
    {
        if( NO_CHANGE_SHARPNESS == ucSharpness )
            ucSharpness = _scReadByte(SC7_3F)&0x1F;    // MWE window Y peaking coefficient
        else
            ucSharpness&=0x1F;

        if( NO_CHANGE_STEP == ucStep )
            ucStep = _scReadByte(SC7_3F)&0xC0;                 // MWE window peaking step
        else
            ucStep<<=6;

        _scWriteByte(SC7_3F, (ucStep)| ucSharpness); // Bank 3

    }
#else //CHIP_TSUMA, not checked in CHIP_TSUML
    if(bScalerWin == MAIN_WINDOW)
    {
        if( NO_CHANGE_SHARPNESS == ucSharpness )
        {
            _scWriteByte(SC0_00, 0x00); // Bank 0
            ucSharpness = _scReadByte(SC0_5D)&(BIT4|BIT3|BIT2|BIT1|BIT0);  // main window peaking coefficient
        }
        if( NO_CHANGE_STEP == ucStep )
        {
            _scWriteByte(SC0_00, 0x03); // Bank 3
            ucStep = _scReadByte(SC3_50)&BIT7;                 // SC3_50[7] enable bit
        }

        _scWriteByte(SC0_00, 0x00); // Bank 0
        _scWriteByteMask( SC0_5D, ucSharpness, (BIT4|BIT3|BIT2|BIT1|BIT0) );  // MWE window peaking coefficient

        {
	        _scWriteByte(SC0_00, 0x03); // Bank 3
	        _scWriteByteMask( SC3_50, ucSharpness, (BIT4|BIT3|BIT2|BIT1|BIT0) );  // MWE window peaking coefficient

	        _scWriteByteMask( SC3_50, (ucStep?BIT7:0), BIT7 );                   // SC3_50[7] enable bit
        }
    }
    else
    {
        _scWriteByte(SC0_00, 0x03); // Bank 3
        if( NO_CHANGE_SHARPNESS == ucSharpness )
        {
            ucSharpness = _scReadByte(SC3_41)&(BIT4|BIT3|BIT2|BIT1|BIT0);  // MWE window peaking coefficient
        }
        if( NO_CHANGE_STEP == ucStep )
        {
            ucStep = _scReadByte(SC3_51)&BIT7;                 // SC3_51[7] enable bit
        }

        _scWriteByteMask( SC3_41, ucSharpness, (BIT4|BIT3|BIT2|BIT1|BIT0) );  // MWE window peaking coefficient
        _scWriteByteMask( SC3_51, ucSharpness, (BIT4|BIT3|BIT2|BIT1|BIT0) );  // MWE window peaking coefficient

        _scWriteByteMask( SC3_51, (ucStep?BIT7:0), BIT7 );                   // SC3_51[7] enable bit
    }
#endif
    _scWriteByte(SC0_00, ucBank);
}

#endif


//XDATA BYTE g_ucVideoContrast;
//XDATA BYTE g_ucVideoSaturation;
//XDATA BYTE g_ucVideoHue;

//void LoadACETable(BYTE * pColorTable)// 2004/11/2
//Main/Sub
#if 0
void LoadACETable(BYTE bScalerWin, BYTE * pColorTable,BYTE ucHue,BYTE ucSaturation,BYTE ucSubContrast)// 2004/11/2
{
    //LOCAL_TYPE BYTE *pColorTable;
    //pColorTable=ppColorTable;
    g_ucVideoHue = ucHue;
    g_ucVideoSaturation = ucSaturation;
    g_ucVideoContrast = ucSubContrast;
    // color correct
    tColorCorrectionMatrix=(short *)pColorTable;
    msAdjustHSC(bScalerWin, g_ucVideoHue,g_ucVideoSaturation,g_ucVideoContrast);
}
#endif

