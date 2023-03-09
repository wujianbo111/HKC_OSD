/******************************************************************************
 Copyright (c) 2008 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: CapactiveKeypad.c
 [Date]:        12-May-2008
 [Comment]:
   Capactive Keypad control subroutines.
 [Reversion History]:
*******************************************************************************/
// Common
#include <global.h>
#include <menudef.h>
#include <misc.h>
#include <debug.h>
#include <menu.h>
#include <Keypad.h>
#include <KeypadDef.h>
#include <power.h>
#include <CapactiveKeypad.h>
#include "GPIO_DEF.h"

////  Prototypes of Private Variables /////////////////////////////////////////
static BYTE xdata s_ucI2CkeyLEDStatus = 0;
static BYTE xdata s_ucCurrentPage = 0;
static BYTE xdata s_uckeypadStatus = 0;
static BYTE xdata s_ucKeyErrorCnt = 0;
static WORD xdata usTouchKeyLEDStatus = 0;	//110304 Modiy By ITE FAE Request
static WORD xdata S2_High_Thresh = 0;			//110304 Modiy By ITE FAE Request

////  Prototypes of Private Functions /////////////////////////////////////////
static Bool appCapkeyIteCheckPage( BYTE page );
static Bool appCapkeyIteWriteWord( const BYTE registerStartAddr, const WORD WriteData );
static Bool appCapkeyIteReadWord( const BYTE registerStartAddr, WORD *recWord );
void ITE_Check_ESD(void);				//110304 Modiy By ITE FAE Request

////  Prototypes of Public Variables //////////////////////////////////////////
WORD xdata g_wOneTouchDataRegs;
BYTE xdata usCheckTouchKeyTimer_1s = 0;
bit CheckTouchKeyFlag = 0;					//110304 Modiy By ITE FAE Request

////  Implementations of Public Functions /////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @note           Original name is appCapkeyIteReadReg
/// @details
///////////////////////////////////////////////////////////////////////////////
Bool appCapkeyIteReadReg( BYTE page, BYTE addr_byte, WORD *val )
{
	WORD xdata data_word = 0;
	if( appCapkeyIteCheckPage( page ) == FALSE )
		return FALSE;
	if( appCapkeyIteReadWord( addr_byte, &data_word ) == TRUE )
	{
		*val = data_word;
		return TRUE;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// @note           Original name is appCapkeyIteWriteReg
/// @details
///////////////////////////////////////////////////////////////////////////////
Bool appCapkeyIteWriteReg( BYTE page, BYTE addr_byte, WORD data_word )
{
	if( appCapkeyIteCheckPage( page ) == FALSE )
		return FALSE;
	if( appCapkeyIteWriteWord( addr_byte, data_word ) == FALSE )
	{
		return FALSE;
	}
	//When the "reset" bit of PCR register is 1, s_CurrentPage is set to 0.
	if( CAPS_PCR == addr_byte && 1 == page && ( data_word & 0x0001 ) )
		s_ucCurrentPage = 0;
	return TRUE;
}

//TODO: Replace this array with the one produced by MPTool.
const sInitCapSReg code asInitCapSReg[] =
{
	#if 0// PCB_715G4197_K0A //L2262		//110304 Modiy By ITE FAE
	{ PAGE_1,  CAPS_PCR, 0x0001},
	{ PAGE_1,  CAPS_PSR, 0x0001},
	{ PAGE_1,  CAPS_PMR, 0x0000},
	{ PAGE_1,  CAPS_RTR, 0x0000},	//110126 Modify
	{ PAGE_1,  CAPS_CTR, 0x0000},       //110126 Modify
	{ PAGE_1,  CAPS_CRMR, 0x0020},
	{ PAGE_1,  CAPS_PDR, 0x00C0},
	{ PAGE_1,  CAPS_DR, 0x0050},
	{ PAGE_1,  CAPS_S0CR, 0xC012},
	{ PAGE_1,  CAPS_S1CR, 0xC0B2},
	{ PAGE_1,  CAPS_S2CR, 0x8000},
	{ PAGE_1,  CAPS_S3CR, 0xC092},
	{ PAGE_1,  CAPS_S4CR, 0xC072},
	{ PAGE_1,  CAPS_S5CR, 0xC042},
	{ PAGE_1,  CAPS_S6CR, 0xC032},
	{ PAGE_1,  CAPS_C0COR, 0x57C8},
	{ PAGE_1,  CAPS_C1COR, 0x7AC0},
	{ PAGE_1,  CAPS_C2COR, 0x7ABF},
	{ PAGE_1,  CAPS_C3COR, 0x7AB7},
	{ PAGE_1,  CAPS_C4COR, 0x7AC8},
	{ PAGE_1,  CAPS_C7COR, 0x7AC9},
	{ PAGE_1,  CAPS_C9COR, 0x57C2},
	{ PAGE_1,  CAPS_C11COR, 0x7AC8},
	{ PAGE_1,  CAPS_ICR0, 0xFFEF},
	{ PAGE_1,  CAPS_ICR1, 0x0FFF},
	{ PAGE_1,  CAPS_COER0, 0xFFFF},
	{ PAGE_1,  CAPS_COER1, 0x03FF},
	{ PAGE_1,  CAPS_CGCR, 0x0001},
	{ PAGE_1,  CAPS_LEDBR, 0x0000},
	{ PAGE_1,  CAPS_GPIODR, 0x0000},
	{ PAGE_1,  CAPS_GPIOOR, 0x0000},
	{ PAGE_1,  CAPS_GPIOMR, 0x0000},
	{ PAGE_1,  CAPS_GPIOLR, ITEREG_LED_CONTROL},
	{ PAGE_1,  CAPS_GPIOER, 0x0000},
	{ PAGE_1,  CAPS_LEDCMR0, 0xFFFF},
	{ PAGE_1,  CAPS_LEDCMR1, 0xFFFF},
	{ PAGE_1,  CAPS_LEDCMR2, 0xFFFF},
	{ PAGE_1,  CAPS_LEDCMR3, 0x0FFF},
	{ PAGE_1,  CAPS_LEDRPR, 0x3030},
	{ PAGE_1,  CAPS_LEDBR, 0x0016},
	{ PAGE_1,  CAPS_LEDCGCR, 0x0000},
	{ PAGE_1,  CAPS_LEDPR0, 0x3333},
	{ PAGE_1,  CAPS_LEDPR1, 0x3333},
	{ PAGE_1,  CAPS_LEDPR2, 0x3333},
	{ PAGE_1,  CAPS_LEDPR3, 0x3333},
	{ PAGE_1,  CAPS_GPIOMSR, ITEREG_LED_CONTROL},
	{ PAGE_0,  CAPS_S0DLR, 0x8000},
	{ PAGE_0,  CAPS_S0OHCR, 0x0400},
	{ PAGE_0,  CAPS_S0OLCR, 0x7000},
	{ PAGE_0,  CAPS_S0SR, 0xCC88},
	{ PAGE_0,  CAPS_S1DLR, 0x8000},
	{ PAGE_0,  CAPS_S1OHCR, 0x0200},    //110223 Modify  0x280
	{ PAGE_0,  CAPS_S1OLCR, 0x7000},
	{ PAGE_0,  CAPS_S1SR, 0xCC88},
	{ PAGE_0,  CAPS_S2DLR, 0x8000},
	{ PAGE_0,  CAPS_S2OHCR, 0x0200},    //110126 Modify
	{ PAGE_0,  CAPS_S2OLCR, 0x7000},
	{ PAGE_0,  CAPS_S2SR, 0xCF8F},
	{ PAGE_0,  CAPS_S3DLR, 0x8000},
	{ PAGE_0,  CAPS_S3OHCR, 0x0300},    //110126 Modify
	{ PAGE_0,  CAPS_S3OLCR, 0x7000},
	{ PAGE_0,  CAPS_S3SR, 0xCC88},
	{ PAGE_0,  CAPS_S4DLR, 0x8000},
	{ PAGE_0,  CAPS_S4OHCR, 0x0300},	//110223 Modify  0x400
	{ PAGE_0,  CAPS_S4OLCR, 0x7000},
	{ PAGE_0,  CAPS_S4SR, 0xCC88},
	{ PAGE_0,  CAPS_S5DLR, 0x8000},
	{ PAGE_0,  CAPS_S5OHCR, 0x0400},
	{ PAGE_0,  CAPS_S5OLCR, 0x7000},
	{ PAGE_0,  CAPS_S5SR, 0xCC88},
	{ PAGE_0,  CAPS_S6DLR, 0x8000},
	{ PAGE_0,  CAPS_S6OHCR, 0x0400},
	{ PAGE_0,  CAPS_S6OLCR, 0x7000},
	{ PAGE_0,  CAPS_S6SR, 0xCC88},
	#if 1
	{ PAGE_0,  CAPS_SXCHAIER, 0x003F},
	{ PAGE_0,  CAPS_SXCHRIER, 0x003F},
	{ PAGE_0,  CAPS_SXCLAIER, 0x0000},
	{ PAGE_0,  CAPS_SXCLRIER, 0x0000},
	{ PAGE_1,  CAPS_GPIONPCR, 0x1FFF},
	#else
	{ PAGE_0,  CAPS_SXCHAIER, 0x007F},
	{ PAGE_0,  CAPS_SXCHRIER, 0x007F},
	{ PAGE_0,  CAPS_SXCLAIER, 0x007B},
	{ PAGE_0,  CAPS_SXCLRIER, 0x007B},
	{ PAGE_1,  CAPS_GPIONPCR, 0x1FFF},
	#endif
	{ PAGE_1,  CAPS_GPIONPCR, 0x1FFF},
	{ PAGE_1,  CAPS_CFER, 0x4000},
	{ PAGE_1,  CAPS_PCR, 0x6406}      //for decimation 128
	//{ PAGE_1,  CAPS_PCR      , 0x6C06},for decimation 64
	#endif


	#if  0// PCB_715G4842_K0B //51ID			//110304 Modiy By ITE FAE

	{ PAGE_1,  CAPS_PCR 	, 0x0001},
	{ PAGE_1,  CAPS_PSR	, 0x0001},
	{ PAGE_1,  CAPS_PMR		, 0x0000},
	{ PAGE_1,  CAPS_RTR		, 0x0000}, //110126 Modify
	{ PAGE_1,  CAPS_CTR		, 0x0000}, //110126 Modify
	{ PAGE_1,  CAPS_CFER 	, 0x4000},//add 20110425 by amanda
	{ PAGE_1,  CAPS_CRMR 	, 0x0020},
	{ PAGE_1,  CAPS_PDR		, 0x00E0},//	{ PAGE_1,  CAPS_PDR		, 0x00C0},
	{ PAGE_1,  CAPS_DR		, 0x0050},
	{ PAGE_1,  CAPS_S0CR, 0xC003},
	{ PAGE_1,  CAPS_S1CR, 0xC013},
	{ PAGE_1,  CAPS_S2CR, 0x8022},
	{ PAGE_1,  CAPS_S3CR, 0xC073},
	{ PAGE_1,  CAPS_S4CR, 0xC093},
	{ PAGE_1,  CAPS_S5CR, 0xC0B3},
	{ PAGE_1,  CAPS_C0COR, 0x68D8},
	{ PAGE_1,  CAPS_C1COR, 0x68CE},
	{ PAGE_1,  CAPS_C2COR, 0x63DB},
	{ PAGE_1,  CAPS_C3COR, 0x68C0},
	{ PAGE_1,  CAPS_C7COR, 0x68D2},
	{ PAGE_1,  CAPS_C9COR, 0x68CF},
	{ PAGE_1,  CAPS_C11COR, 0x68DC},
	{ PAGE_1,  CAPS_ICR0, 0xFFBF},
	{ PAGE_1,  CAPS_ICR1, 0x0FFF},
	{ PAGE_1,  CAPS_COER0, 0xFFFF},
	{ PAGE_1,  CAPS_COER1, 0x03FF},
	{ PAGE_1,  CAPS_CGCR, 0x0001},
	{ PAGE_1,  CAPS_LEDBR, 0x0000},
	{ PAGE_1,  CAPS_GPIODR	, 0x0000},
	{ PAGE_1,  CAPS_GPIOOR	, 0x0000},
	{ PAGE_1,  CAPS_GPIOMR	, 0x0000},
	{ PAGE_1,  CAPS_GPIOLR	, ITEREG_LED_CONTROL},
	{ PAGE_1,  CAPS_GPIOER	, 0x0000},
	{ PAGE_1,  CAPS_LEDCMR0	, 0xFFFF},
	{ PAGE_1,  CAPS_LEDCMR1	, 0xFFFF},
	{ PAGE_1,  CAPS_LEDCMR2	, 0xFFFF},
	{ PAGE_1,  CAPS_LEDCMR3	, 0x0FFF},
	{ PAGE_1,  CAPS_LEDRPR	, 0x3030},
	{ PAGE_1,  CAPS_LEDBR	, 0x0016},
	{ PAGE_1,  CAPS_LEDCGCR	, 0x0000},
	{ PAGE_1,  CAPS_LEDPR0	, 0x3333},
	{ PAGE_1,  CAPS_LEDPR1	, 0x3333},
	{ PAGE_1,  CAPS_LEDPR2	, 0x3333},
	{ PAGE_1,  CAPS_LEDPR3	, 0x3333},
	{ PAGE_1,  CAPS_GPIOMSR	, 0x7FFF},
	{ PAGE_0,  CAPS_S0DLR	, 0x8000},
	{ PAGE_0,  CAPS_S0OHCR	, 0x0280}, //
	{ PAGE_0,  CAPS_S0OLCR	, 0x7000},
	{ PAGE_0,  CAPS_S0SR	, 0xCC88},
	{ PAGE_0,  CAPS_S1DLR	, 0x8000},
	{ PAGE_0,  CAPS_S1OHCR	, 0x0400}, //
	{ PAGE_0,  CAPS_S1OLCR	, 0x7000},
	{ PAGE_0,  CAPS_S1SR	, 0xCC88},
	{ PAGE_0,  CAPS_S2DLR	, 0x8000},
	{ PAGE_0,  CAPS_S2OHCR	, 0x7000},
	{ PAGE_0,  CAPS_S2OLCR	, 0x7000},
	{ PAGE_0,  CAPS_S2SR	, 0xCC88},
	{ PAGE_0,  CAPS_S3DLR	, 0x8000},
	{ PAGE_0,  CAPS_S3OHCR	, 0x0240},
	{ PAGE_0,  CAPS_S3OLCR	, 0x7000},
	{ PAGE_0,  CAPS_S3SR	, 0xCC88},
	{ PAGE_0,  CAPS_S4DLR	, 0x8000},
	{ PAGE_0,  CAPS_S4OHCR	, 0x0400},
	{ PAGE_0,  CAPS_S4OLCR	, 0x7000},
	{ PAGE_0,  CAPS_S4SR	, 0xCC88},
	{ PAGE_0,  CAPS_S5DLR	, 0x8000},
	{ PAGE_0,  CAPS_S5OHCR	, 0x0280},
	{ PAGE_0,  CAPS_S5OLCR	, 0x7000},
	{ PAGE_0,  CAPS_S5SR	, 0xCC88},
	{ PAGE_0,  CAPS_SXCHAIER, 0x003F},
	{ PAGE_0,  CAPS_SXCHRIER, 0x003F},
	{ PAGE_0,  CAPS_SXCLAIER, 0x0000},
	{ PAGE_0,  CAPS_SXCLRIER, 0x0000},
	{ PAGE_1,  CAPS_GPIONPCR, 0x1FFF},
	{ PAGE_1,  CAPS_GPIONPCR, 0x1FFF},
	//{ PAGE_1,  CAPS_CFER 	, 0x4000},//del 20110425 by amanda
	{ PAGE_1,  CAPS_PCR		, 0x5406}//for decimation 128
	//{ PAGE_1,	CAPS_PCR	  , 0x5C06},for decimation 64
	#endif


	#if 1
	{ PAGE_1,  CAPS_PCR, 0x0001},
	{ PAGE_1,  CAPS_PSR, 0x0001},
	{ PAGE_1,  CAPS_PMR, 0x0000},
	{ PAGE_1,  CAPS_RTR, 0x005F},
	{ PAGE_1,  CAPS_CTR, 0x001F},
	{ PAGE_1,  CAPS_CFER, 0x4000},
	{ PAGE_1,  CAPS_CRMR, 0x0020},
	{ PAGE_1,  CAPS_PDR, 0x00C0},
	{ PAGE_1,  CAPS_DR, 0x0050},
	{ PAGE_1,  CAPS_S0CR, 0xC003},
	{ PAGE_1,  CAPS_S1CR, 0xC013},
	{ PAGE_1,  CAPS_S2CR, 0x8022},
	{ PAGE_1,  CAPS_S3CR, 0xC073},
	{ PAGE_1,  CAPS_S4CR, 0xC093},
	{ PAGE_1,  CAPS_S5CR, 0xC0B3},
	{ PAGE_1,  CAPS_C0COR, 0x68D8},
	{ PAGE_1,  CAPS_C1COR, 0x68CE},
	{ PAGE_1,  CAPS_C2COR, 0x63DB},
	{ PAGE_1,  CAPS_C3COR, 0x68C0},
	{ PAGE_1,  CAPS_C7COR, 0x68D2},
	{ PAGE_1,  CAPS_C9COR, 0x68CF},
	{ PAGE_1,  CAPS_C11COR, 0x68DC},
	{ PAGE_1,  CAPS_ICR0, 0xFFBF},
	{ PAGE_1,  CAPS_ICR1, 0x0FFF},
	{ PAGE_1,  CAPS_COER0, 0xFFFF},
	{ PAGE_1,  CAPS_COER1, 0x03FF},
	{ PAGE_1,  CAPS_CGCR, 0x0001},
	{ PAGE_1,  CAPS_LEDBR, 0x0000},
	{ PAGE_1,  CAPS_GPIODR, 0x0003},    // set GPIO 0 & 1 output
	{ PAGE_1,  CAPS_GPIOOR, 0x0000},
	{ PAGE_1,  CAPS_GPIOMR, 0x0000},
	{ PAGE_1,  CAPS_GPIOLR, 0x0003},
	{ PAGE_1,  CAPS_GPIOER, 0x0000},
	{ PAGE_1,  CAPS_LEDCMR0, 0xFFFF}, //0x50DD
	{ PAGE_1,  CAPS_LEDCMR1, 0xFFFF}, //0x3DD4
	{ PAGE_1,  CAPS_LEDCMR2, 0xFFFF}, //0x1D2D
	{ PAGE_1,  CAPS_LEDCMR3, 0xFFFF},
	{ PAGE_1,  CAPS_LEDRPR, 0x3030},
	{ PAGE_1,  CAPS_LEDBR, 0x001A},	//120607 Modify for ITE Request LED current 5mA
	{ PAGE_1,  CAPS_LEDCGCR, 0x0000},
	{ PAGE_1,  CAPS_LEDPR0, 0x3333},
	{ PAGE_1,  CAPS_LEDPR1, 0x3443},
	{ PAGE_1,  CAPS_LEDPR2, 0x3434},
	{ PAGE_1,  CAPS_LEDPR3, 0x0444},
	{ PAGE_1,  CAPS_GPIOMSR, 0x0003},   // set GPIO 0 & 1
	{ PAGE_0,  CAPS_S0DLR, 0x8000},
	{ PAGE_0,  CAPS_S0OHCR, 0x0280},  //0x0280
	{ PAGE_0,  CAPS_S0OLCR, 0x7000},
	{ PAGE_0,  CAPS_S0SR, 0xCC88},
	{ PAGE_0,  CAPS_S1DLR, 0x8000},
	{ PAGE_0,  CAPS_S1OHCR, 0x0400},  //0x0400
	{ PAGE_0,  CAPS_S1OLCR, 0x7000},
	{ PAGE_0,  CAPS_S1SR, 0xCC88},
	{ PAGE_0,  CAPS_S2DLR, 0x8000},
	{ PAGE_0,  CAPS_S2OHCR, 0x7000},
	{ PAGE_0,  CAPS_S2OLCR, 0x7000},
	{ PAGE_0,  CAPS_S2SR, 0xCC88},
	{ PAGE_0,  CAPS_S3DLR, 0x8000},
	{ PAGE_0,  CAPS_S3OHCR, 0x0240}, //0x0240
	{ PAGE_0,  CAPS_S3OLCR, 0x7000},
	{ PAGE_0,  CAPS_S3SR, 0xCC88},
	{ PAGE_0,  CAPS_S4DLR, 0x8000},
	{ PAGE_0,  CAPS_S4OHCR, 0x0400}, //0x0400
	{ PAGE_0,  CAPS_S4OLCR, 0x7000},
	{ PAGE_0,  CAPS_S4SR, 0xCC88},
	{ PAGE_0,  CAPS_S5DLR, 0x8000},
	{ PAGE_0,  CAPS_S5OHCR, 0x0280}, //0x0280
	{ PAGE_0,  CAPS_S5OLCR, 0x7000},
	{ PAGE_0,  CAPS_S5SR, 0xCC88},
	{ PAGE_0,  CAPS_SXCHAIER, 0x003F},
	{ PAGE_0,  CAPS_SXCHRIER, 0x003F},
	{ PAGE_0,  CAPS_SXCLAIER, 0x00000},
	{ PAGE_0,  CAPS_SXCLRIER, 0x0000},
	{ PAGE_1,  CAPS_GPIONPCR, 0x1FFF},
	{ PAGE_1,  CAPS_PCR, 0x5406}     //0x5C06

	#endif


};

#define NEED_RESET 1
void CapS_PowerOn( void )		//110329 Modiy for ITE FAE request
{
	#if NEED_RESET
	BYTE  xdata i = 0x00;
	#else //#if NEED_RESET
	BYTE  xdata i = 0x01;
	#endif //#if NEED_RESET
	appCapkeyIteWriteReg(PAGE_1, CAPS_PCR, 0x0001);
	ForceDelay1ms(1);
	while( i < ( sizeof( asInitCapSReg ) / sizeof( sInitCapSReg ) ) )
	{
		appCapkeyIteWriteReg( asInitCapSReg[i].page, asInitCapSReg[i].reg, asInitCapSReg[i].value );
		i++;
		if (i == 1)
		{
			ForceDelay1ms(1);//Delay 1ms.
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @note           Original name is appI2CKeyInit
/// @details        ITE Key init, after CapS_PowerOn function need delay 200ms wait stable and write
///                     PAGE_1 CAPS_CFER reg to 0xC000 value.
///////////////////////////////////////////////////////////////////////////////
void appI2CKeyInit( void )
{
	HW_SET_CPK_I2C_SCL_PIN();		//110310 Modify for ITE Enigineer Request
	ForceDelay1ms( 2 );				//110310 Modify for ITE Enigineer Request
	HW_CLR_CPK_I2C_SCL_PIN();		//110310 Modify for ITE Enigineer Request
	ForceDelay1ms( 6 );				//110310 Modify for ITE Enigineer Request
	HW_SET_CPK_I2C_SCL_PIN();		//110310 Modify for ITE Enigineer Request
	ForceDelay1ms( 2 );				//110310 Modify for ITE Enigineer Request
	CapS_PowerOn();
	//test
	appCapkeyIteWriteReg( PAGE_1, CAPS_RTR, 0x0000 );
	appCapkeyIteWriteReg( PAGE_1, CAPS_CTR, 0x0000 );
	appCapkeyIteWriteReg( PAGE_1, CAPS_CFER, 0x4000 );
	//test
	ForceDelay1ms( 350 ); //Delay 350ms. //110126 Modify for ITE Enigineer Request
	appCapkeyIteWriteReg( PAGE_1, CAPS_RTR, 0x003F );
	// appCapkeyIteWriteReg( PAGE_1, CAPS_RTR, 0x007F ); //110126 Modify for ITE Enigineer Request
	appCapkeyIteWriteReg( PAGE_1, CAPS_CTR, 0x003F ); //110126 Modify for ITE Enigineer Request
	appCapkeyIteWriteReg( PAGE_1, CAPS_CFER, 0xC000 );
	s_ucI2CkeyLEDStatus = 0;
	appCapkeyIteReadReg(PAGE_0, CAPS_S2HTR, &S2_High_Thresh);		//110304 Modiy By ITE FAE Request
	usCheckTouchKeyTimer_1s = 2;										//110304 Modiy By ITE FAE Request
	CheckTouchKeyFlag = FALSE;										//110304 Modiy By ITE FAE Request
	ForceDelay1ms(115);				//110329 Modify for ITE FAE request for wait Key stable
}

///////////////////////////////////////////////////////////////////////////////
/// @note           Original name is appGetI2CKeypadInt
/// @details        Get I2C Key INT status
///////////////////////////////////////////////////////////////////////////////
Bool appGetI2CKeypadInt(void)
{
	// if (!HW_CPK_I2C_SCL_PIN_IS_LO())
	return TRUE;
	//return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// @note           Original name is appGetI2CKeypadStatus
/// @details        Get I2C Key Button status
///////////////////////////////////////////////////////////////////////////////
BYTE appGetI2CKeypadStatus( void )
{
	#if 0
	appCapkeyIteReadReg( PAGE_0, CAPS_SXCHSR, &g_wOneTouchDataRegs );
	printData("key status %x\n", g_wOneTouchDataRegs);
	appCapkeyIteReadReg( PAGE_0, 0x23, &g_wOneTouchDataRegs );
	printData("0x23 %x\n", g_wOneTouchDataRegs);
	appCapkeyIteReadReg( PAGE_0, 0x6E, &g_wOneTouchDataRegs );
	printData("0x6E %x\n", g_wOneTouchDataRegs);
	#endif
	if (appGetI2CKeypadInt())
	{
		if( appCapkeyIteReadReg( PAGE_0, CAPS_SXCHSR, &g_wOneTouchDataRegs ) == TRUE )
		{
			s_ucKeyErrorCnt = 0;
			s_uckeypadStatus = 0xFF;		//110328 Modify
			g_wOneTouchDataRegs &= TPREG_KEYPADMASK;
			//  if(g_wOneTouchDataRegs)
			//  printData("g_wOneTouchDataRegs %x", g_wOneTouchDataRegs);
			if( g_wOneTouchDataRegs == TPREG_POWER )
			{
				s_uckeypadStatus &= ~KEY_POWER;
			}
			else if( g_wOneTouchDataRegs == TPREG_MENU )
			{
				s_uckeypadStatus &= ~KEY_MENU;
			}
			else if( g_wOneTouchDataRegs == TPREG_MINUS )
			{
				s_uckeypadStatus &= ~KEY_MINUS;
			}
			else if( g_wOneTouchDataRegs == TPREG_PLUS )
			{
				s_uckeypadStatus &= ~KEY_PLUS;
			}
			else if( g_wOneTouchDataRegs == TPREG_AUTO )
			{
				s_uckeypadStatus &= ~KEY_EXIT;
			}
			else if(( g_wOneTouchDataRegs == TPREG_FACTORY ) && !PowerOnFlag )
			{
				s_uckeypadStatus &= ~KEY_FACTORY;
			}
			else if(( g_wOneTouchDataRegs == TPREG_OSDLOCK ) && !PowerOnFlag )
			{
				s_uckeypadStatus &= ~KEY_LOCK;
			}
			else
			{
				s_uckeypadStatus = 0xFF;
			}
		}
		else
		{
			s_ucKeyErrorCnt ++;
		}
		if( s_ucKeyErrorCnt >= 100 )
		{
			s_ucKeyErrorCnt = 0;
			appI2CKeyInit();
			if( PowerOnFlag )
			{
				if( PowerSavingFlag )
				{
					Power_TurnOnAmberLed();
				}
				else
				{
					Power_TurnOnGreenLed();
				}
			}
			else // power off
			{
				Power_TurnOffLed();
			}
		}
	}
	if(CheckTouchKeyFlag)		//11-04-14 Modiy By ITE FAE Request
	{
		CheckTouchKeyFlag = FALSE;
		ITE_Check_ESD();
	}
	return s_uckeypadStatus;
}


//20110302 FOR ESD
void ITE_Check_ESD(void)		//11-04-14 ITE Modify
{
	static WORD  xdata pre_tmp[6];
	WORD  xdata cur_tmp[6];
	static BYTE  xdata CAPS_RST_CNT = 0;
	static BYTE  xdata temp = 0;
	BYTE  xdata i = 0;
	appCapkeyIteReadReg(PAGE_1, CAPS_GPIOOR, &cur_tmp[0]);
	if (usTouchKeyLEDStatus != cur_tmp[0])
	{
		appCapkeyIteWriteReg(PAGE_1, CAPS_GPIOOR, usTouchKeyLEDStatus);
	}
	//appCapkeyIteReadReg(PAGE_1, CAPS_PCR, 	&cur_tmp[0]);
	appCapkeyIteReadReg(PAGE_0, CAPS_S2HTR, &cur_tmp[1]);
	if(S2_High_Thresh != cur_tmp[1])    //((cur_tmp[0] == 0x0000 )||(S2_High_Thresh != cur_tmp[1]))
	{
		appI2CKeyInit();
		usCheckTouchKeyTimer_1s = 2;
		CAPS_RST_CNT = 0;
		temp = 0;
		return;
	}
	appCapkeyIteReadReg(PAGE_0, CAPS_S0CDC_CMP, &cur_tmp[0]);
	appCapkeyIteReadReg(PAGE_0, CAPS_S1CDC_CMP, &cur_tmp[1]);
	appCapkeyIteReadReg(PAGE_0, CAPS_S2CDC_CMP, &cur_tmp[2]);
	appCapkeyIteReadReg(PAGE_0, CAPS_S3CDC_CMP, &cur_tmp[3]);
	appCapkeyIteReadReg(PAGE_0, CAPS_S4CDC_CMP, &cur_tmp[4]);
	appCapkeyIteReadReg(PAGE_0, CAPS_S5CDC_CMP, &cur_tmp[5]);
	//20110425 add by amanda->
	for(i = 0; i < 6; i++)
	{
		if ((pre_tmp[i] == cur_tmp[i]) && ((cur_tmp[i] == 0x0000) || (cur_tmp[i] == 0xffff)))
		{
			temp++;
		}
	}
	if(  (pre_tmp[0] != cur_tmp[0])\
	        || (pre_tmp[1] != cur_tmp[1])\
	        || (pre_tmp[2] != cur_tmp[2])\
	        || (pre_tmp[3] != cur_tmp[3])\
	        || (pre_tmp[4] != cur_tmp[4])\
	        || (pre_tmp[5] != cur_tmp[5]))
	{
		for(i = 0; i < 6; i++)
		{
			pre_tmp[i] = cur_tmp[i];
		}
		CAPS_RST_CNT = 0;
	}
	else
	{
		CAPS_RST_CNT++;
	}
	//<-
	//20110425 disenable by amanda
	/*->
	if(  (cur_tmp[0] == 0x0000||cur_tmp[0] == 0xffff)\
	||(cur_tmp[1] == 0x0000||cur_tmp[1] == 0xffff)\
	||(cur_tmp[2] == 0x0000||cur_tmp[2] == 0xffff)\
	||(cur_tmp[3] == 0x0000||cur_tmp[3] == 0xffff)\
	||(cur_tmp[4] == 0x0000||cur_tmp[4] == 0xffff)\
	||(cur_tmp[5] == 0x0000||cur_tmp[5] == 0xffff))
	{
	    temp++;
	}
	else
	{
	    temp = 0;
	}


	if(  (pre_tmp[0] == cur_tmp[0])\
	||(pre_tmp[1]== cur_tmp[1])\
	||(pre_tmp[2] == cur_tmp[2])\
	||(pre_tmp[3] == cur_tmp[3])\
	||(pre_tmp[4] == cur_tmp[4])\
	||(pre_tmp[5] == cur_tmp[5]))
	{
	    CAPS_RST_CNT++;
	}
	else
	{
	    CAPS_RST_CNT = 0;
	}

	for(i=0;i<6;i++)
	{
	    pre_tmp[i] = cur_tmp[i];
	}
	*/
	//<-
	if((CAPS_RST_CNT >= 5) || (temp >= 2))
	{
		appI2CKeyInit();
		CAPS_RST_CNT = 0;
		temp = 0;
	}
	usCheckTouchKeyTimer_1s = 2;
}

////  Implementations of Private Functions /////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @note           Original name is appCapkeyIteCheckPage
/// @details
///////////////////////////////////////////////////////////////////////////////
static Bool appCapkeyIteCheckPage( BYTE page )
{
	if( page != s_ucCurrentPage )
	{
		if( appCapkeyIteWriteWord( CAPS_PSR, page ) == TRUE )
		{
			s_ucCurrentPage = page;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// @note           Original name is appCapkeyIteWriteWord
/// @details
///////////////////////////////////////////////////////////////////////////////
static Bool appCapkeyIteWriteWord( const BYTE registerStartAddr, const WORD WriteData )
{
	BYTE  xdata retry = 3;
	BYTE  xdata tempbuf[3];
	tempbuf[0] = registerStartAddr;
	tempbuf[1] = ( WriteData & 0x00FF );
	tempbuf[2] = ( WriteData & 0xFF00 ) >> 8;
	while( retry-- )
	{
		if( CPK_I2C_MasterStart( I2C_WRITE, ITE_ADDR ) == FALSE )
		{
			CPK_I2C_Stop();
			ForceDelay1ms(5);
			continue;
		}
		if( CPK_I2C_BurstWrite( 3, tempbuf ) == FALSE )
		{
			CPK_I2C_Stop();
			ForceDelay1ms(5);
			continue;
		}
		CPK_I2C_Stop();
		return TRUE;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// @note           Original name is appCapkeyIteReadWord
/// @details
///////////////////////////////////////////////////////////////////////////////
static Bool appCapkeyIteReadWord( const BYTE registerStartAddr, WORD *recWord )
{
	BYTE  xdata retry = 3;
	BYTE  xdata RegAddr = registerStartAddr;
	BYTE  xdata tempbuf[2];
	while( retry-- )
	{
		if( CPK_I2C_MasterStart( I2C_WRITE, ITE_ADDR ) == FALSE )
		{
			CPK_I2C_Stop();
			ForceDelay1ms(5);
			continue;   //return FALSE;
		}
		if( CPK_I2C_BurstWrite( 1, &RegAddr ) == FALSE )
		{
			CPK_I2C_Stop();
			ForceDelay1ms(5);
			continue;   //return FALSE;
		}
		if( CPK_I2C_MasterStart( I2C_READ, ITE_ADDR ) == FALSE )
		{
			CPK_I2C_Stop();
			ForceDelay1ms(5);
			continue;   //return FALSE;
		}
		if( CPK_I2C_BurstRead( 2, tempbuf ) == FALSE )
		{
			CPK_I2C_Stop();
			ForceDelay1ms(5);
			continue;   //return FALSE;
		}
		*recWord = ( WORD )( tempbuf[1] << 8 ) | tempbuf[0];
		return TRUE;
	}
	return FALSE;
}
