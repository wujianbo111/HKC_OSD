///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    Ms_PM.c
/// @author MStar Semiconductor Inc.
/// @brief  PM Function
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------

#include "board.h"
#if MS_PM
#include <math.h>
#include <string.h>
#include "types.h"
#include "ms_reg.h"
#include "global.h"
#include "Misc.h"
#include "ms_rwreg.h"
#include "Ms_PM.h"
#include "Debug.h"
#include "Common.h"
#include "Power.h"
#include "DDC2Bi.h"
#include "Keypaddef.h"

extern void mStar_AdjustBrightness( BYTE brightness );

#if !MS_VGA_SOG_EN
BYTE xdata checkHVSynce = 0xFF;
#endif

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define XBYTE             ((unsigned char volatile xdata *) 0)

#define RCOSC       0
#define     XTAL        1
#define   XTALDIV2  2
#define   XTALDIV4  3

//--------PM Option----------------
/*Choice MCU clock when enter into PM_MODE*/
#define PM_CLOCK    RCOSC
/*Disable MCU or not when enter into PM_MODE*/
//#define PM_MCUSLEEP       1
#define PM_USE_AC2DC        0// 1
#define PM_DVICTRL      0// 091119  0  //2009-10-07 for FOC DVD issue

#define TYPE_B  // 091026 coding reserved
#if PM_MCUSLEEP
#define PM_SAR_ANYKYE           0
#else
#define PM_SAR_ANYKYE   1
#endif
#if defined(SourcekeyWakeup)||defined(SARpowerkey)
#define PM_SAR      1
#else
#define PM_SAR      0
#endif
#define PM_SOG      0 // 1 // 091022 coding for disabling SOG event wake up from pm
#define PM_CEC      0 // 1 // 091022 coding for disabling CEC event wake up from pm
#define PM_MCCS     1
//#define POWER_KEY     P2_6


// 091026 coding, add a byte to record PM status before mcu shut down
#if PM_MCUSLEEP
BYTE xdata PMPreStatus;
#endif

#if PM_StbyMcuAliveForClockExist
BYTE xdata DVIClockExistFlag = 0;
#endif
//---------------------------------
#define HSYNC_DET_0     BIT7
#define VSYNC_DET_0     BIT6
#define SOG_DET_0       BIT5
#define HV_DET_0        BIT4
#define HSYNC_DET_1     BIT3
#define VSYNC_DET_1     BIT2
#define SOG_DET_1       BIT1
#define HV_DET_1        BIT0

#define CEC_WAKEUP      BIT5
#define D2B_WAKEUP      BIT4
#define SAR_IN_DET      BIT3
#define GPIO_0_INT      BIT2
#define GPIO_1_INT      BIT1
#define DVI_CLK_DET     BIT0
//---------------------------------
#define VCP_SET             0x03
#define VCP_DPMS            0xD6
#define VCP_DPMS_ON  0x01
//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------
#if DEBUG_PRINT_ENABLE
#define printMsg(x) printData(x,0)
extern void printData( char *str, WORD value );
#endif
void hw_SetAmberLed_PM( void );
void hw_ClrAmberLed_PM( void );

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
//static XDATA BYTE ucPM_Status;
//XDATA BYTE fCheckDPMS;
BYTE code tblPM_ON[][2] =
{
	// 091021 coding, power up scalar
	{BK0_00, REGBANK0},
	{BK0_F1, 0x00},

	{BK0_00, REGBANKPM},
	{BKC_21, PD_HSYNCCMP_Disable},
	{BKC_26, DVIRAW_CLK_Enable},
	{BKC_27, DVI_SYNC_CLK_Enable},
	{BKC_29, DVICLK_CTLCLK_Enable},
	{BKC_34, PKEY_WkUp_OFF},
	{BKC_41, DVICLK_DET_Disable},
	{BKC_44, 0x00},
	{BKC_4A, 0x00},
	{BKC_4B, 0x00},
	{BKC_24, 0x00},
	{BKC_25, 0x00},
};

BYTE code tblPM_OFF[][2] =
{
	{BK0_00, REGBANKPM},
	{BKC_21, PD_HSYNCCMP},

	{BKC_26, DVIRAW_CLK_Enable},                /*DVI RAW clock pass*/
	{BKC_27, DVI_SYNC_CLK_Enable},             /*DVI clock pass, Sync clock pass*/
	{BKC_28, AC2DC_CLKOFF},
	{BKC_29, DVICLK_CTLCLK_Enable},            /*enable GPIO/SAR detect */
	#ifndef SARpowerkey
	{BKC_34, Key_WkUp_EN},
	#endif

	#ifdef TYPE_B
	{BKC_35, 0x00},                                          /*enable GPIO P13 detect */
	{BKC_C1, 0x01},                                          /*Select the method to delay the wakeup time to enable MCU and XTAL */
	#endif
	{BKC_41, DVICLK_DET_Disable},
	{BKC_44, 0x00},
	{BKC_4A, 0x00},
	{BKC_4B, DVICLK_CTL_CHEN},
	{BKC_24, 0x55},     /*PM_PASSWORD*/
	{BKC_25, 0xAA},     /*PM_PASSWORD*/

	{BKC_22, 0x02}
};
//for power test - enable Sync ,DVI,GPIO detect
BYTE code tblPM_SB[][2] =
{
	#if 1
	{BK0_00, REGBANKPM},
	{BKC_21, PD_HSYNCCMP},

	{BKC_26, DVIRAW_CLK_Disable},
	{BKC_27, DVI_SYNC_CLK_Disable},
	{BKC_28, AC2DC_CLKOFF},
	{BKC_29, DVICLK_CTLCLK_Disable},
	#ifndef SARpowerkey
	{BKC_34, Key_WkUp_EN},
	#endif

	#ifdef TYPE_B
	{BKC_35, 0x00},                                             /*enable GPIO P13 detect */
	{BKC_C1, 0x01},                                      /*Select the method to delay the wakeup time to enable MCU and XTAL */
	#endif
	{BKC_41, DVICLK_DET_Enable},
	//{BKC_44, HVSYNC_SOG_DET},
	#if PM_DVICTRL
	{BKC_4A, DVICLK_CTL_AMP_SEL},
	{BKC_4B, DVICLK_CTL_CHEN},
	#else
	#ifdef TSUMXXNX
	{BKC_4A, 0xC0}, // 100111 coding for N-type DVI wakeup setting
	#else
	{BKC_4A, 0x00},
	#endif
	{BKC_4B, 0x00},
	#endif
	{BKC_24, 0x55},
	{BKC_25, 0xAA},

	{BKC_22, 0x02}

	#else
	{BK0_00, REGBANKPM},
	{BKC_21, PD_HSYNCCMP},

	{BKC_26, DVIRAW_CLK_Enable},                /*DVI RAW clock pass*/
	{BKC_27, DVI_SYNC_CLK_Enable},             /*DVI clock pass, Sync clock pass*/
	{BKC_28, AC2DC_CLKOFF},
	{BKC_29, DVICLK_CTLCLK_Enable},            /*enable GPIO/SAR detect */
	{BKC_34, Key_WkUp_EN},

	#ifdef TYPE_B
	{BKC_35, 0x00},                                          /*enable GPIO P13 detect */
	{BKC_C1, 0x01},                                          /*Select the method to delay the wakeup time to enable MCU and XTAL */
	#endif
	{BKC_41, DVICLK_DET_Disable},
	{BKC_44, HVSYNC_SOG_DET},
	{BKC_4A, 0x00},
	{BKC_4B, DVICLK_CTL_CHEN},
	{BKC_24, 0x55},     /*PM_PASSWORD*/
	{BKC_25, 0xAA},     /*PM_PASSWORD*/

	{BKC_22, 0x02}

	#endif


};

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  External Variables
//-------------------------------------------------------------------------------------------------
#if !ENABLE_DEBUG
extern BYTE xdata rxIndex;
extern BYTE xdata DDCBuffer[DDC_BUFFER_LENGTH];
#endif

//-------------------------------------------------------------------------------------------------
//  External Functions
//-------------------------------------------------------------------------------------------------
extern Bool PowerOnSystem( void );

//**************************************************************************
//  [Function Name]:
//                  DDCCI_CheckDMPSON()
//  [Description]
//                  DDCCI_CheckDMPSON
//  [Arguments]:
//
//  [Return]:
// DMPS Power On: 6E 51 84 03 D6 00 01 CkSum
// DMPS Power Off(standby): 6E 51 84 03 D6 00 02 CkSum
// DMPS Power Off(suspend) : 6E 51 84 03 D6 00 03 CkSum
// DMPS Power Off: 6E 51 84 03 D6 00 04 CkSum
// Power Off: 6E 51 84 03 D6 00 05 CkSum

//**************************************************************************
#if !ENABLE_DEBUG
BYTE code MCCS_DPMSON[6] = {0x51, 0x84, 0x03, 0xD6, 0x00, 0x01};

Bool DDCCI_CheckDMPSON( void )
{
	if( rxIndex >= 5 )
	{
		if( memcmp( MCCS_DPMSON, DDCBuffer, 6 ) == 0 )
		{
			memset( DDCBuffer, 0, 6 );
			rxIndex = 0;
			//fCheckDPMS=0;
			return TRUE;
		}
	}
	return FALSE;
}
#endif

//**************************************************************************
//  [Function Name]:
//                  msPM_PowerDownMacro()
//  [Description]
//                  msPM_PowerDownMacro
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************

void msPM_PowerDownMacro( BYTE ucMode )
{
	msWriteByte( BK0_00, REGBANK1 );
	msWriteByte( BK1_20, BIT7 );
	mStar_WriteByteMask( BK1_E2, BIT7, BIT7 );
	mStar_WriteByteMask( BK1_5C, BIT5 | BIT4, BIT5 | BIT4 );
	mStar_WriteByteMask( BK1_CF, BIT0, BIT0 );
	#if  1//!PM_DVICTRL
	/*enable DVI A/B T-term & clock */
	//msWriteByte(BK1_E4, 0x11);        /*Only enable DVI0*/
	#if 0
	msWriteByte( BK1_E4, 0x14 );     /*enable DVI0/DVI1*/
	#else
	if( ucMode == ePM_PowerOff )
		msWriteByte( BK1_E4, 0x03 );
	else
		msWriteByte( BK1_E4, 0x14 );     /*enable DVI0/DVI1*/
	#endif
	msWriteByte( BK1_26, 0x01 );
	mStar_WriteByteMask( BK1_C9, 0x00, BIT7 );
	#endif
	msWriteByte( BK1_60, 0x60 ); //Power down SAR
	msWriteByte( BK1_A6, 0x80 );
	msWriteByte( BK1_20, 0x00 );
	msWriteByte( BK0_00, REGBANK5 );
	mStar_WriteByteMask( BK5_1F, BIT6, BIT6 );
	mStar_WriteByteMask( BK5_F5, BIT0, BIT0 );
	msWriteByte( BK0_00, REGBANK0 );
	msWriteByte( BK0_F4, 0x7F );
	mStar_WriteByteMask( BK0_B4, 0, BIT6 ); //Disable DDC filter
	if( ucMode == ePM_PowerOff )
	{
		MCU_P0_OUT_EN = 0x00;
		MCU_P0_FMD = 0x00;
		MCU_P1_OUT_EN = 0x80;
		MCU_P1_FMD = 0x80;
	}
	else
	{
		MCU_P0_OUT_EN = 0x80 | BIT5;
		MCU_P0_FMD = 0x80 | BIT5;
		MCU_P1_OUT_EN = 0x80;
		MCU_P1_FMD = 0x80;
	}
	MCU_P1_OUT_EN = 0x00;
	MCU_P1_FMD = 0x00;
	MCU_P2_OUT_EN = 0x00;
	MCU_P2_FMD = 0x00;
	#if(MainBoardType==MainBoard_3836)
	MCU_P0_OUT_EN = 0;
	MCU_P0_FMD = 0;
	msWriteByte( BK0_00, REGBANK0 );
	mStar_WriteByteMask( BK0_C8, BIT0, BIT0 ); //msWriteByte( BK0_C8, msReadByte( BK0_C8 ) | BIT0 );
	msWriteByte( PWM3, 0xFF );
	mStar_WriteByteMask( BK0_C8, 0x00, BIT0 );  //msWriteByte( BK0_C8, msReadByte( BK0_C8 )&( ~BIT0 ) );
	hw_SetMute();
	#endif
	hw_ClrBlacklit();
	hw_ClrPanel();
	// hw_Set_HdcpHpd();
	//hw_Set_HdcpHpd2();
}

//**************************************************************************
//  [Function Name]:
//                  msPM_PowerUpMacro()
//  [Description]
//                  msPM_PowerUpMacro
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
extern void Init_IOPorts( void );
void msPM_PowerUpMacro( void )
{
	msWriteByte( BK0_00, REGBANK1 );
	msWriteByte( BK1_20, 0x80 );
	mStar_WriteByteMask( BK1_E2, 0, BIT7 );
	mStar_WriteByteMask( BK1_5C, 0, BIT5 | BIT4 );
	msWriteByte( BK1_A6, 0x00 );
	mStar_WriteByteMask( BK1_CF, 0, BIT0 );
	msWriteByte( BK1_20, 0x00 );
	msWriteByte( BK1_60, 0x20 );
	msWriteByte( BK0_00, REGBANK5 );
	mStar_WriteByteMask( BK5_1F, 0, BIT6 );
	mStar_WriteByteMask( BK5_F5, 0, BIT0 );
	msWriteByte( BK0_00, REGBANK0 );
	msWriteByte( BK0_F4, 0x00 );
	#if !PM_MCUSLEEP
	Init_IOPorts();
	#endif
	msWriteByte( BK0_00, REGBANK0 );
}

//**************************************************************************
//  [Function Name]:
//                  StartRCOSCCal()
//  [Description]
//                  StartRCOSCCal
//  [Arguments]:
//
//  [Return]:
//  RCOSC = XTAL * Counter / 512 => Counter = RCOSC *512/XTAL = 143 =>8Fh
//**************************************************************************
#define RCOSC_TARGET    143 //4MHz
//#define RCOSC_MAX
Bool StartRCOSCCal( void )
{
	BYTE ucBank;
	WORD ucCounter;
	BYTE ucTemp, i;
	BYTE ucSetOld = 0x08;
	BYTE ucSetNow = 0x08;
	int iDeltaOld = 100;
	int iDeltaNew = 0;
	ucBank = msReadByte( BK0_00 );
	msWriteByte( BK0_00, REGBANKPM );
	msWriteByte( BKC_28, RCOSC_CLKOFF );
	ucTemp = msReadByte( BKC_20 ) & 0x0F;
	#ifdef RCOSC_MAX
	ucSetNow = 0x00;//0x1F;
	msWriteByte( BKC_20, ( ucSetNow << 4 ) | ucTemp );
	#else
	for( i = 0; i < 31; i++ )
	{
		msWriteByte( BKC_20, ( ucSetNow << 4 ) | ucTemp );
		msWriteByte( BKC_4C, 0x80 );
		msWriteByte( BKC_4C, 0x03 );
		while( !( msReadByte( BKC_4F ) & BIT4 ) )
		{
		}
		ucCounter = mStar_ReadWord( BKC_4F ) & 0x03FF;
		iDeltaNew = ( int )ucCounter - RCOSC_TARGET;
		if( abs( iDeltaNew ) < abs( iDeltaOld ) )
		{
			ucSetOld = ucSetNow;
			if( ucCounter > RCOSC_TARGET )
			{
				ucSetNow--;
			}
			else
			{
				ucSetNow++;
			}
			iDeltaOld = iDeltaNew;
		}
		else
		{
			msWriteByte( BKC_20, ( ucSetOld << 4 ) | ucTemp );
			msWriteByte( BKC_4C, 0x00 );
			msWriteByte( BKC_28, AC2DC_RCOSC_CLKOFF );
			msWriteByte( BK0_00, ucBank );
			return TRUE;
		}
	}
	#endif
	msWriteByte( BKC_28, AC2DC_RCOSC_CLKOFF );
	msWriteByte( BK0_00, ucBank );
	return FALSE;
}


//**************************************************************************
//  [Function Name]:
//                  msPM_EnableAC2DC()
//  [Description]
//                  msPM_EnableAC2DC
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msPM_EnableAC2DC( Bool bEnable )
{
	msWriteByte( BK0_00, REGBANKPM );
	if( bEnable ) /*Turn On PM*/
	{
		mStar_WriteByteMask( BKC_28, 0x00, 0xF0 );        /*AC2DC controler clock bypass*/
		msWriteByte( BKC_60, AC2DC_MODE );            /*AC2DC controler enable      */
		msWriteByte( BKC_62, OFF_PERIOD );            /*AC2DC Off period*/
		msWriteByte( BKC_64, AC2DC_PAD );                /*AC2DC pad function enable        */
		msWriteByte( BKC_66, 0x84 );                        /*AC detect voltage */
	}
	else              /*Turn Off PM*/
	{
		msWriteByte( BKC_64, 0x00 );                        /*AC2DC pad function disable*/
		msWriteByte( BKC_60, OFF_MODE );                 /*AC2DC controler disable*/
		msWriteByte( BKC_62, 0x00 );
		msWriteByte( BKC_66, 0x00 );                  /*Off period*/
		mStar_WriteByteMask( BKC_28, 0xB0, 0xF0 );        /*AC2DC controler clock gating*/
	}
	msWriteByte( BK0_00, REGBANK0 );
}
//**************************************************************************
//  [Function Name]:
//                  GetPMStatus()
//  [Description]
//                  GetPMStatus
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool GetPMStatus( BYTE* pucStatus )
{
	BYTE ucBank;
	Bool bResault = FALSE;
	BYTE ucStatus_3E;
	BYTE ucStatus_3F;
	#ifdef TYPE_B
	BYTE ucStatus_35;
	#endif
	*pucStatus = ePMStatus_Non;
	ucBank = msReadByte( BK0_00 );
	msWriteByte( BK0_00, REGBANKPM );
	ucStatus_3E = msReadByte( BKC_3E );
	ucStatus_3F = msReadByte( BKC_3F );
	#ifdef TYPE_B
	ucStatus_35 = msReadByte( BKC_35 );
	if( ucStatus_35 & ( BIT5 | BIT4 ) )
	{
		*pucStatus = ePMStatus_GPIOActive;
		bResault = TRUE;
	}
	#endif
	if( ucStatus_3E & ( HSYNC_DET_0 | VSYNC_DET_0 | SOG_DET_0 | HV_DET_0 ) )
	{
		*pucStatus = ePMStatus_ADCActive;
		bResault = TRUE;
	}
	else
	{
		switch( ucStatus_3F )
		{
			case CEC_WAKEUP:
				*pucStatus = ePMStatus_CECActive;
				bResault = TRUE;
				break;
			case D2B_WAKEUP:
				*pucStatus = ePMStatus_D2BActive;
				bResault = TRUE;
				break;
			case SAR_IN_DET:
				*pucStatus = ePMStatus_SARActive;
				bResault = TRUE;
				break;
			case GPIO_0_INT:
			case GPIO_1_INT:
				*pucStatus = ePMStatus_GPIOActive;
				bResault = TRUE;
				break;
			case DVI_CLK_DET:
				*pucStatus = ePMStatus_DVIActive;
				bResault = TRUE;
				break;
		}
	}
	msWriteByte( BK0_00, ucBank );
	return  bResault;/* *pucStatus*/ /*ucStatus_3F*//*bResault*/
}


//**************************************************************************
//  [Function Name]:
//                  EnableSAREvent()
//  [Description]
//                  EnableSAREvent
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
#ifdef TYPE_B
#define SAR_33          1<<7
#define SAR_18          0<<7
#define SAR_VOLTAGE         SAR_18

void EnableSAREvent( Bool benable, Bool bAnyKey )
{
	if( benable )
	{
		if( bAnyKey )
		{
			msWriteByte( BK0_00, REGBANK1 );
			msWriteByte( BK1_64, SAR_VOLTAGE ); //|BIT6);
			msWriteByte( BK0_00, REGBANKPM );
			msWriteByte( BKC_C0, 0xF0 );
			mStar_WriteByteMask( BKC_34, BIT0, BIT0 );
		}
		else
		{
			msWriteByte( BK0_00, REGBANK1 );
			#if  MainBoardType==MainBoard_3836
			mStar_WriteByteMask( BK1_60, BIT0 | BIT1 | BIT4, BIT0 | BIT1 | BIT4 | BIT6 );
			#elif  MainBoardType==MainBoard_4266
			mStar_WriteByteMask( BK1_60, BIT0 | BIT1 | BIT4, BIT0 | BIT1 | BIT4 | BIT6 );
			#else
			mStar_WriteByteMask( BK1_60, BIT0 | BIT4, BIT0 | BIT1 | BIT4 | BIT6 );
			#endif
			msWriteByte( BK1_64, SAR_VOLTAGE ); //|BIT6);
			msWriteByte( BK0_00, REGBANKPM );
			msWriteByte( BKC_C0, 0 );
			mStar_WriteByteMask( BKC_34, BIT0, BIT0 );
		}
	}
	else
	{
		msWriteByte( BK0_00, REGBANKPM );
		mStar_WriteByteMask( BKC_34, 0, BIT0 );
		msWriteByte( BKC_C0, 0x00 );
	}
}
#endif

//**************************************************************************
//  [Function Name]:
//                  EnableMCCSPM()
//  [Description]
//                  EnableMCCSPM
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void EnableMCCSPM( Bool benable )
{
	#ifndef TSUMXXNX
	BYTE ucloop;
	#endif
	if( benable )
	{
		#ifdef TSUMXXNX
		XBYTE[0xc019] = 0xB7;
		XBYTE[0xc01A] = 0xB7;
		XBYTE[0xc07A] = 0xB7;
		msWriteByte( BK0_00, REGBANK0 );
		mStar_WriteByteMask( BK0_B3, BIT4 | BIT3, BIT4 | BIT3 );  //msWriteByte( BK0_B3, msReadByte( BK0_B3 ) | ( BIT4 | BIT3 ) ); //MCCS wake up power key 05 Enable , MCCS wake up function Enable
		#else
		msWriteByte( BK0_00, REGBANK0 );
		msWriteByte( BK0_B6, 0x00 );
		for( ucloop = 0; ucloop < 20; ucloop++ )
			msWriteByte( BK0_B7, 0x00 );
		msWriteByte( BK0_BA, 0x00 );
		for( ucloop = 0; ucloop < 20; ucloop++ )
			msWriteByte( BK0_BB, 0x00 );
		XBYTE[0xc019] = 0xB7;
		XBYTE[0xc01A] = 0xB7;
		XBYTE[0xc07A] = 0xB7;
		XBYTE[0xc1B0] = 0xE0;
		XBYTE[0xc1B2] = 0xE0;
		XBYTE[0xc1B3] = 0xE0;
		XBYTE[0xc1B5] = 0xC0;
		#endif
	}
	else
	{
		#ifdef TSUMXXNX
		msWriteByte( BK0_00, REGBANK0 );
		msWriteByte( BK0_B3, 0x00 );
		#else
		XBYTE[0xc1b0] = 0x00;
		XBYTE[0xc1b5] = 0x00;
		#endif
	}
}

//**************************************************************************
//  [Function Name]:
//                  msPM_MCCSReset()
//  [Description]
//                  msPM_MCCSReset
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msPM_MCCSReset( void )
{
	#ifdef TSUMXXNX
	BYTE ucBank;
	ucBank = msReadByte( BK0_00 );
	msWriteByte( BK0_00, REGBANK0 );
	mStar_WriteByteMask( BK0_B3, BIT0 | BIT1, BIT0 | BIT1 );  //msWriteByte( BK0_B3, msReadByte( BK0_B3 ) | ( BIT0 | BIT1 ) );
	mStar_WriteByteMask( BK0_B3, 0x00, BIT0 | BIT1 );   //msWriteByte( BK0_B3, msReadByte( BK0_B3 )&( ~BIT0 | BIT1 ) ); //Clear DDC2BI D6 Comamnd 04,05  flag
	mStar_WriteByteMask( BK0_BA, BIT6, BIT6 ); //msWriteByte( BK0_BA, msReadByte( BK0_BA ) | ( BIT6 ) );
	mStar_WriteByteMask( BK0_BA, 0x00, BIT6 );  //msWriteByte( BK0_BA, msReadByte( BK0_BA )&( ~( BIT6 ) ) ); //Clear DDC2BI wake up flag.
	msWriteByte( BK0_00, ucBank );
	#else // for TSUMXXMX
	XBYTE[0xc1B0] = XBYTE[0xc1b0] | ( BIT4 | BIT3 );
	XBYTE[0xc1B0] = XBYTE[0xc1b0] & ( ~( BIT4 | BIT3 ) );
	XBYTE[0xc1B4] = 0x80;
	XBYTE[0xc1B4] = 0x00;
	#endif
}

//**************************************************************************
//  [Function Name]:
//                  SetPMClock()
//  [Description]
//                  SetPMClock
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void SetPMClock( void )
{
	// 091119 coding for setting sequence
	msWriteByte( BK0_00, REGBANK0 );
	mStar_WriteByteMask( BK0_F0, 0, BIT1 | BIT0 );
	msWriteByte( BK0_F1, 0x01 );
	msWriteByte( BK0_F1, 0x00 );
	msPM_ClearStatus();
	#if PM_USE_AC2DC
	msPM_EnableAC2DC( TRUE );
	#endif
	msWriteByte( BK0_00, REGBANK1 );
	#if PM_CLOCK == RCOSC
	#ifdef TSUMXXNX
	mStar_WriteByteMask( BK1_66, BIT0,  BIT0 );      //1xMCU/XTAL
	ForceDelay1ms_NotTimer( 1 );
	mStar_WriteByteMask( BK1_67, BIT1 | BIT0,  BIT1 | BIT0 );
	ForceDelay1ms_NotTimer( 1 );
	mStar_WriteByteMask( BK1_67, BIT5 | BIT4,  BIT5 | BIT4 );
	ForceDelay1ms_NotTimer( 1 );
	mStar_WriteByteMask( BK1_66, 0x00,  BIT0 );
	msWriteByte( BK0_00, REGBANK0 );
	mStar_WriteByteMask( BK0_D1, 0x00, BIT0 );     /*disable XTAL*/
	#else
	//printMsg(" PM Clock =>RCOSC ");
	// 091026 coding
	//msWriteByte(BK1_67, 0xC3);    // power down MCU PLL
	mStar_WriteByteMask( BK1_67, BIT0 | BIT1, BIT0 | BIT1 );  //msWriteByte( BK1_67, msReadByte( BK1_67 ) | ( BIT0 | BIT1 ) ); // set to RC4M
	ForceDelay1ms_NotTimer( 10 );
	mStar_WriteByteMask( BK1_66, 0x00, BIT0 ); //msWriteByte( BK1_66, msReadByte( BK1_66 )&~BIT0 ); // mcu clock source select by bk1 67
	mStar_WriteByteMask( BK1_67, BIT7, BIT7 ); //msWriteByte( BK1_67, msReadByte( BK1_67 ) | BIT7 ); // power down MCU PLL
	msWriteByte( BK0_00, REGBANKPM );
	mStar_WriteByteMask( BKC_21, 0, BIT1 );     /*disable XTAL*/
	#endif
	#elif PM_CLOCK == XTALDIV4
	//printMsg(" PM Clock =>XTALDIV4 ");
	msWriteByte( BK1_67, 0x82 );
	#elif PM_CLOCK == XTALDIV2
	//printMsg(" PM Clock =>XTALDIV2 ");
	msWriteByte( BK1_67, 0x81 );
	#else
	//printMsg(" PM Clock =>XTAL ");
	msWriteByte( BK1_67, 0x80 );
	#endif  //PM_CLOCK
	/*Set deep power down mode*/
	msWriteByte( BK0_00, REGBANK0 );
	mStar_WriteByteMask( BK0_F0, BIT1 | BIT0, BIT1 | BIT0 );
	msWriteByte( BK0_F1, BIT7 );
	#if PM_MCUSLEEP
	/*Set MCU sleep mode*/
	msWriteByte( BK0_00, REGBANK1 );
	msWriteByte( BK1_BA, 0x00 );
	msWriteByte( BK1_BA, 0x55 );
	msWriteByte( BK0_00, REGBANK0 );
	#endif//PM_MCUSLEEP
}

//**************************************************************************
//  [Function Name]:
//                  msPM_Init()
//  [Description]
//                  msPM_Init
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msPM_ClearStatus( void )
{
	msWriteByte( BK0_00, REGBANKPM );
	//Clear Flag
	msWriteByte( BKC_3F, BIT6 );
	msWriteByte( BKC_3F, 0 );
	//PM Reset
	msWriteByte( BKC_22, 0x03 );
	msWriteByte( BKC_22, 0x02 );
	msWriteByte( BK0_00, REGBANK0 );
}
//**************************************************************************
//  [Function Name]:
//                  msPM_Reset()
//  [Description]
//                  msPM_Reset
//  [Arguments]:
//
//  [Return]:
//      PM status
//
//**************************************************************************
BYTE msPM_Reset( void )
{
	BYTE ucStatus = ePMStatus_Invaild;
	msPM_EnableAC2DC( FALSE );
	if( GetPMStatus( &ucStatus ) )
	#if DEBUG_PRINT_ENABLE
		printData( "\r\nPM Wakeup Event (%d) !", ucStatus );
	#else
		;
	#endif
	msPM_SetUp( ePM_PowerON );
	msWriteByte( BK0_00, REGBANKPM );
	msWriteByte( BKC_34, 0x00 );        /*disable GPIO detect*/
	msWriteByte( BKC_35, 0x00 );        /*disable GPIO detect*/
	#if 0 // 091210 coding reserved
	msWriteByte( BKC_21, 0x02 );        /*Enable XTAL*/
	// 091021 coding, wait for xtal stable
	ForceDelay1ms( 10 );
	msWriteByte( BK0_00, REGBANK1 );
	// 091021 coding, sequence of switching mcu clock
	//msWriteByte(BK1_67, 0x00);            /* Selcet XTAL*/
	// power up mcu pll
	msWriteByte( BK1_67, 0x00, BIT7 );  //msWriteByte( BK1_67, msReadByte( BK1_67 )&~BIT7 );
	// wait for mcu pll stable
	ForceDelay1ms( 10 );
	// switch to mcu pll
	msWriteByte( BK1_66, msReadByte( BK1_66 ) | BIT0 );
	msWriteByte( BK1_67, 0x00 );          /* Selcet XTAL*/
	// switch to xtal
	msWriteByte( BK1_66, msReadByte( BK1_66 ) & ~BIT0 );
	msWriteByte( BK1_BA, 0x00 );         /*Disable MCU Power down*/
	#endif
	msWriteByte( BK0_00, REGBANK0 );
	msPM_ClearStatus();
	msPM_MCCSReset();
	#ifdef TYPE_B
	EnableSAREvent( FALSE, FALSE );
	#endif
	#if DEBUG_PRINT_ENABLE
	printData( "Enter PM ePM_PowerON mode!", 0 );
	#endif
	return ucStatus;
}

void msPM_InterruptEnable( Bool benable )
{
	if( benable )
	{
		//ET0 =0;
		//ET1 =0;
	}
	else
	{
		//ET0 = 1;
		//ET1 = 1;
	}
}
//**************************************************************************
//  [Function Name]:
//                  msPM_WaitingEvent()
//  [Description]
//                  msPM_WaitingEvent
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
#define SAR_KEY_TH      0x30
void msPM_WaitingEvent( void )
{
	BYTE ucStatus = 0;
	msPM_InterruptEnable( FALSE );
	msPM_ClearStatus();
	#if DEBUG_PRINT_ENABLE
	printMsg( "msPM_WaitingEvent....." );
	#endif
	while(( !GetPMStatus( &ucStatus ) ) )
	{
		#if !ENABLE_DEBUG
		if( DDCCI_CheckDMPSON() )
			break;
		#endif
		#if PM_SAR_ANYKYE
		//if((KEYPAD_ADC2 < SAR_KEY_TH) ||(KEYPAD_ADC3 < SAR_KEY_TH))
		if( KEYPAD_ADC4 < SAR_KEY_TH )
			break;
		#endif
		// if(ES)
		//  DebugHandler();
	}
	#if DEBUG_PRINT_ENABLE
	printData( "\r\nPM Wakeup Event1 (%d) !", ucStatus );
	#endif
	msPM_Reset();
	msWriteByte( BK0_00, REGBANK0 );
	PowerOnSystem();
	msPM_PowerUpMacro();
	msWriteByte( BK0_00, REGBANK1 );
	mStar_WriteByteMask( BK1_66, BIT0, BIT0 );
	msWriteByte( BK0_00, REGBANK0 );
	msPM_InterruptEnable( TRUE );
}

//**************************************************************************
//  [Function Name]:
//                  msPM_SetUp()
//  [Description]
//                  msPM_SetUp
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
extern Bool PowerOffSystem( void );
extern void mstar_HDMIAudioMute( BYTE sw );
extern void msDisableHDCP( void );


void msPM_SetUp( BYTE ucMode )
{
	BYTE i;
	switch( ucMode )
	{
		case ePM_Standby:
			//ucPM_Status = ePM_Standby_MCUShutDown;
			#if DEBUG_PRINT_ENABLE
			printMsg( "Enter PM Standby mode!" );
			#endif
			#if PM_CEC
			msWriteByte( BK0_00, REGBANKD );
			mStar_WriteByteMask( BKD_1E, BIT4, BIT4 );
			msWriteByte( BK0_00, REGBANK5 );
			mStar_WriteByteMask( BK5_2E, BIT2, BIT2 );
			#endif
			msWriteByte( BK0_00, REGBANK1 );
			#if PM_SAR_ANYKYE
			mStar_WriteByteMask( BK1_60, 0x20, 0x33 );
			#endif
			#if PM_SOG
			mStar_WriteByteMask( BK1_CF, BIT5, BIT5 );
			mStar_WriteByteMask( BK1_E2, BIT7, BIT7 );
			#endif
			//msWriteByte(BK1_E4, 0x14);
			mStar_WriteByteMask( BK1_66, 0, BIT0 );
			#if PM_MCCS
			EnableMCCSPM( TRUE );
			#endif
			msPM_PowerDownMacro( ePM_Standby );
			if( !StartRCOSCCal() )
			#if DEBUG_PRINT_ENABLE
				printMsg( "CALIBARYION RCOSC FAIL!" );
			#else
				;
			#endif
			for( i = 0; i < sizeof( tblPM_SB ) / 2; i++ )
				msWriteByte( tblPM_SB[i][0], tblPM_SB[i][1] );
			#if LED_PWM // 090318
			hw_SetAmberLed_PM();
			#endif
			#if !MS_VGA_SOG_EN
			if(( checkHVSynce & BIT7 ) == 0 )
				msWriteByte( BKC_44, VSYNC_SOG_DET );
			else if(( checkHVSynce & BIT6 ) == 0 )
				msWriteByte( BKC_44, HSYNC_SOG_DET );
			else
			#endif
				msWriteByte( BKC_44, HVSYNC_SOG_DET );
			#ifdef TYPE_B
			#if PM_SAR
			//EnableSAREvent(TRUE, TRUE);
			EnableSAREvent( TRUE, FALSE );
			#else
			EnableSAREvent( FALSE, FALSE );
			#endif
			#endif
			// 091119 coding, moved to here from power handler
			Power_TurnOnAmberLed();
			SetPMClock();
			break;
		case ePM_PowerOff:
			//ucPM_Status = ePM_PowerOff;
			#if PM_CEC
			msWriteByte( BK0_00, REGBANKD );
			mStar_WriteByteMask( BKD_1E, BIT4, BIT4 );
			msWriteByte( BK0_00, REGBANK5 );
			mStar_WriteByteMask( BK5_2E, BIT2, BIT2 );
			#endif
			msPM_PowerDownMacro( ePM_PowerOff );
			if( !StartRCOSCCal() )
			#if DEBUG_PRINT_ENABLE
				printMsg( "CALIBARYION RCOSC FAIL!" );
			#else
				;
			#endif
			//msWriteByte(BK0_00, REGBANK1); // 091026 coding reserved
			//msWriteByte(BK1_E4, 0x03);
			//mStar_WriteByteMask(BK1_66, 0, BIT0); // 0091026 coding reserved
			#if PM_MCCS
			EnableMCCSPM( TRUE );
			#endif
			//while(!POWER_KEY)
			//{ }
			for( i = 0; i < sizeof( tblPM_OFF ) / 2; i++ )
				msWriteByte( tblPM_OFF[i][0], tblPM_OFF[i][1] );
			#ifdef TYPE_B
			#if  MainBoardType==MainBoard_3836
			EnableSAREvent( TRUE, FALSE );
			#else
			EnableSAREvent( FALSE, FALSE );
			#endif
			#endif
			#if LED_PWM
			hw_ClrAmberLed_PM();
			#endif
			SetPMClock();
			break;
		case ePM_PowerON:
			//ucPM_Status = ePM_PowerON;
			#if DEBUG_PRINT_ENABLE
			printData( "Enter PM PowerON mode!", 0 );
			#endif
			for( i = 0; i < sizeof( tblPM_ON ) / 2; i++ )
				msWriteByte( tblPM_ON[i][0], tblPM_ON[i][1] );
			EnableMCCSPM( FALSE );
			#if LED_PWM
			msWriteByte( BK0_00, REGBANK1 );
			msWriteByte( BK1_98, LED_PWM_SEL ); //Disable LED PWM
			msWriteByte( BK0_00, REGBANK0 );
			#endif
			break;
		default:
			break;
	}
	msWriteByte( BK0_00, REGBANK0 );
}

//================================================
#if LED_PWM
void hw_SetAmberLed_PM( void )
{
	msWriteByte( BK0_00, REGBANK1 );
	mStar_WriteByteMask( BK1_79, BIT5, BIT5 );    /*LIVE_BIUCLK still active in DPD*/
	msWriteByte( BK1_98, LED_PWM_SEL | LED_PWM_EN );
	msWriteByte( BK0_00, REGBANK0 );
	#if (LEDPWM==LEDPWM3)
	mStar_WriteByteMask( BK0_C8, BIT0, BIT0 ); //msWriteByte( BK0_C8, msReadByte( BK0_C8 ) | BIT0 );
	#endif
	msWriteByte( PWMDIV, PWMDIV_Val );
	msWriteByte( PWMDUTY, PWMDUTY_Val );
	#if (LEDPWM==LEDPWM0)   /*use PWMDIV0[8][10:9]*/
	mStar_WriteByteMask( BK0_C8, BIT1, BIT1 ); //msWriteByte( BK0_C8, msReadByte( BK0_C8 ) | BIT1 );
	mStar_WriteByteMask( BK0_4D, BIT1 | BIT0, BIT1 | BIT0 );  //msWriteByte( BK0_4D, msReadByte( BK0_4D ) | BIT1 | BIT0 );
	#elif (LEDPWM==LEDPWM1)   /*use PWMDIV1[8][10:9]*/
	mStar_WriteByteMask( BK0_C8, BIT2, BIT2 ); //msWriteByte( BK0_C8, msReadByte( BK0_C8 ) | BIT2 );
	mStar_WriteByteMask( BK0_4D, BIT3 | BIT2, BIT3 | BIT2 );  //msWriteByte( BK0_4D, msReadByte( BK0_4D ) | BIT3 | BIT2 );
#elif(LEDPWM==LEDPWM2)   /*use PWMDIV2[8][10:9]*/
	mStar_WriteByteMask( BK0_C8, BIT3, BIT3 ); //msWriteByte( BK0_C8, msReadByte( BK0_C8 ) | BIT3 );
	mStar_WriteByteMask( BK0_4D, BIT5 | BIT4, BIT5 | BIT4 );  //msWriteByte( BK0_4D, msReadByte( BK0_4D ) | BIT5 | BIT4 );
#elif(LEDPWM==LEDPWM3)   /*use PWMDIV3[8]*/
	mStar_WriteByteMask( BK0_C8, BIT6, BIT6 ); //msWriteByte( BK0_C8, msReadByte( BK0_C8 ) | BIT6 );
	#endif
	#if (LEDPWM==LEDPWM3)
	mStar_WriteByteMask( BK0_C8, 0x00, BIT0 );  //msWriteByte( BK0_C8, msReadByte( BK0_C8 )&~BIT0 );
	#endif
}

void hw_ClrAmberLed_PM( void )
{
	msWriteByte( BK0_00, REGBANK1 );
	mStar_WriteByteMask( BK1_79, BIT5, BIT5 );
	msWriteByte( BK1_98, LED_PWM_SEL );
	msWriteByte( BK0_00, REGBANK0 );
	#if (LEDPWM==LEDPWM3)
	mStar_WriteByteMask( BK0_C8, BIT0, BIT0 ); //msWriteByte( BK0_C8, msReadByte( BK0_C8 ) | BIT0 );
	#endif
	msWriteByte( PWMDIV, 0x00 );
	msWriteByte( PWMDUTY, 0x00 );
	#if (LEDPWM==LEDPWM3)
	mStar_WriteByteMask( BK0_C8, 0x00, BIT0 );  //msWriteByte( BK0_C8, msReadByte( BK0_C8 )&~BIT0 );
	#endif
}
#endif

//================================================
//====================================================================
// /*1.∵無信號VGA cable接?W?AVsync會由low?駩igh則IC?^報Vsync detected */
// /*?陘F避?K?鴠??bStandby ?氶A?]?做L信號cable插?W喚醒?A?]?髡A檢查?@次是?_有sync detected*/
// /*若第?G次檢查?癡S有sync?A則?P定?做L信號cable插?J?A則keep?bPM_standby mode*/
//
// /*2.After the chip is wakeup, reg_mcupd_key (BK1_BA[7:0]) needs to be cleared to 0x00 */
// /*before we enable AC2DC function (set reg_ac2dc_en=1 (BKC_64[7:0]) to enter in PM mode again.*/
//=====================================================================
BYTE xdata Check, Check1;
extern Bool PowerOffSystem( void );
void ms_PM_Chcek_Sync( void )
{
	// 091026 coding, read out PM status before mcu shut down
	#if PM_MCUSLEEP
	msWriteByte( BK0_00, REGBANK0 );
	PMPreStatus = msReadByte( BK0_2F );
	if( PMPreStatus == 0 )
	{
		PMPreStatus = PMPreStatus_ACOn;
		Check = ePMStatus_Non;
		return;
	}
	#endif
	msWriteByte( BK0_00, REGBANK1 );
	msWriteByte( BK1_BA, 0x00 );
	GetPMStatus( &Check );
	// 091026 coding
	#if 1
	#if PM_MCUSLEEP
	if( Check == ePMStatus_ADCActive || Check == ePMStatus_DVIActive )
	{
		if( PMPreStatus == PMPreStatus_DCOff )
		{
			msWriteByte( BK0_00, REGBANK0 );
			msWriteByte( BK0_F1, 0x00 );
			msWriteByte( BK0_F0, 0x00 );
			msPM_ClearStatus();
			Check = 0;
			PMPreStatus = 0;
			msPM_SetUp( ePM_PowerOff );
		}
	}
	#endif
	#else
	if( Check == ePMStatus_ADCActive )
	{
		msPM_ClearStatus();
		//ForceDelay1ms(5);
		GetPMStatus( &Check1 );
		//ForceDelay1ms(5);
		msPM_ClearStatus();
		#if 0
		if( Check1 != ePMStatus_ADCActive )
		{
			//Delay1ms(25);
			msPM_SetUp( ePM_Standby );
		}
		else if( Check == ePMStatus_ADCActive ) //For test
		{
			Check1 = ePMStatus_ForcPowerOn;
		}
		#endif
	}
	#endif
}

BYTE ms_PM_Get_HV_Status( void )
{
	BYTE UcBank;
	BYTE Temp;
	UcBank = msReadByte( BK0_00 );
	msWriteByte( BK0_00, REGBANK0 );
	Temp = msReadByte( BK0_E1 ) & ( BIT7 | BIT6 );
	msWriteByte( BK0_00, UcBank );
	return Temp;
}

//====================================================================
// /*Case1?GFor test */
// /*Case2?Gif GPIO or SAR detected , check "poweronflag" to know what the mode is(should PM_ON or PM_standby)  */
// /*Case3?Gplug AC off and AC on when set is DC off , should keep DC off*/
//=====================================================================
void msPM_Check_Power_Status( void )
{
	checkHVSynce = ms_PM_Get_HV_Status();
	// if(Check1==ePMStatus_ForcPowerOn)          /*For test*/
	//   Set_PowerOnFlag();
	/*press Power key when set is in PM-Sandby should enter into PM_Off*/
	//else if(Check==ePMStatus_GPIOActive ||Check==ePMStatus_SARActive)
	if( Check == ePMStatus_GPIOActive )
	{
		if( PowerOnFlag )
		{
			//CheckPowerKey(); // 091026 coding reserved
			PowerOffSystem();
		}
		Set_PowerOnFlag();
		KeypadButton = BTN_Repeat;
		Set_PM_PowerOnSaveFlag();//2009-10-07
	}
	/*DC off thenAC off and AC on , should keep DC off*/
	else if( Check == ePMStatus_SARActive )
	{
		#if defined(SARpowerkey)
		if( PowerOnFlag )
		{
			PowerOffSystem();
		}
		Set_PowerOnFlag();
		#endif
		#if defined(SourcekeyWakeup)
		Set_SARwakeupFlag();
		#endif
		Set_PM_PowerOnSaveFlag();//2009-10-07
	}
	#if 0
	else if( Check == ePMStatus_Non )
	{
		if( !PowerOnFlag )
		{
			CheckPowerKey();
			PowerOffSystem();
		}
	}
	#endif
}
//====================================================================
// /*Case1?Guse to clear DisplayLogoFlag when wakeup event is HVsync,SOG ,DVI or MCCS.*/
// /*用來擋掉Standby?隩N?阞摔OGO*/
//=====================================================================
#if DisplayLogo!=NoBrand
Bool msPM_Check_Not_Show_Logo( void )
{
	if( Check == ePMStatus_ADCActive || Check == ePMStatus_DVIActive || Check == ePMStatus_D2BActive || Check == ePMStatus_GPIOActive )
	{
		return TRUE;
	}
	return FALSE;
}
#endif



#if 1//SOG_OR_NOT
extern void mStar_SetAnalogInputPort( void );
extern void mStar_SetupInputPort( void );
#define HVActive    (BIT7|BIT6)
void ms_PM_Chcek_RealSync_Status( void )
{
	BYTE H_V_Status;
	if( Check == ePMStatus_ADCActive || Check == ePMStatus_DVIActive )
	{
		if( Check == ePMStatus_ADCActive )
			SrcInputType = Input_ANALOG;
		else
			SrcInputType = Input_Digital;
		mStar_SetupInputPort();
		ForceDelay1ms( 30 );
		if( Check == ePMStatus_ADCActive )
		{
			H_V_Status = ms_PM_Get_HV_Status();
			if( H_V_Status != HVActive )
			{
				mStar_SetAnalogInputPort();
				H_V_Status = ms_PM_Get_HV_Status();
				if( H_V_Status != HVActive )
				{
					Power_PowerOffSystem( PowerDown_MCUShutDown );
				}
			}
		}
		else if( Check == ePMStatus_DVIActive )
		{
			// 091203 coding, if clock in, system wake up
			//H_V_Status=ms_PM_Get_HV_Status();
			//if(checkHVSynce!=((BIT7|BIT6)))
			if( msReadByte( BK0_CA )&BIT6 )
			{
				Power_PowerOffSystem( PowerDown_MCUShutDown );
			}
			// 100111 coding, DVI clock in but without sync
			#if !PM_StbyMcuAliveForClockExist
			else if( ms_PM_Get_HV_Status() != HVActive )
			{
				BYTE tempCnt = 0, syncvalidCnt = 0;
				do
				{
					Delay1ms( 25 );
					if( ms_PM_Get_HV_Status() == HVActive ) // sync present
					{
						syncvalidCnt++;
						if( tempCnt )
							tempCnt--;
					}
					else // sync loss
						syncvalidCnt = 0;
				}
				while(( ++tempCnt < 20 ) && ( syncvalidCnt < 3 ) );
				if( syncvalidCnt < 3 )
					Power_PowerOffSystem( PowerDown_MCUShutDown );
			}
			#endif
		}
	}
}
#endif





#endif
