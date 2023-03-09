/******************************************************************************
 Copyright (c) 2005 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: Msflash.c
 [Date]:        25-Apr-2003
 [Comment]:
   MST Flash subroutines.
 [Reversion History]:
*******************************************************************************/
#define _MSFLASH_C_

#include <intrins.h>
#include "types.h"
#include "board.h"
#include "misc.h"
#include "global.h"
#include "ms_reg.h"
#include "ms_rwreg.h"
#include "msflash.h"
#include "misc.h"
#include "Mcu.h"
#include "GPIO_DEF.h"
#if ENABLE_DEBUG
#include "debug.h"
#endif

#define _FLASH_CODE_VERSION_    0x100

#define FLASH_DEBUG    0
#if FLASH_DEBUG && ENABLE_DEBUG
#define FLASH_printData(str, value)   printData(str, value)
#define FLASH_printMsg(str)           printMsg(str)
#else
#define FLASH_printData(str, value)
#define FLASH_printMsg(str)
#endif

//#define CacheStatus()   (_bit3_(MEM_MSREAD_BYTE(REG_1018)))
//#define EnableCache()  (MEM_MSWRITE_BIT(REG_1018, BIT3, BIT3), MEM_MSWRITE_BIT(REG_2BA0, 0, BIT0))
//#define DisableCache()  (MEM_MSWRITE_BIT(REG_2BA0, BIT0, BIT0), MEM_MSWRITE_BIT(REG_1018, 0, BIT3))

Bool xdata bFlashWriteFactory = FALSE;
Bool xdata bFlashEraseBufferFinish = FALSE; // // jeff add it in 2009 0907
BYTE xdata g_ucFlashDeviceID = 0;
BYTE xdata g_FlashSize = FLASH_SIZE_2M;
///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Check current MsFlash.c code version
// <Returns> : MsFlash.c version number
///////////////////////////////////////////////////////////////////////////////
WORD FlashVersionCheck( void )
{
	BYTE ucTemp = 0;
	if( ucTemp )
	{
		Flash_GetBufferAddr();
		Flash_AllocateBufferAddr();
		Flash_CheckBufferType();
		Flash_ClearModeSet();
		Flash_WriteFactorySet( &ucTemp, 0 );
		Flash_ReadFactorySet( &ucTemp, 0 );
		Flash_WriteMonitorSet( &ucTemp, 0 );
		Flash_ReadMonitorSet( &ucTemp, 0 );
		Flash_WriteMonitorSet2( &ucTemp, 0 );
		Flash_ReadMonitorSet2( &ucTemp, 0 );
		Flash_WriteModeSet( 0, &ucTemp );
		Flash_ReadModeSet( 0, &ucTemp );
	}
	return _FLASH_CODE_VERSION_;
}

///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Clear SPI Buffer.
///////////////////////////////////////////////////////////////////////////////
#if 0
void CleanSPI_SI_BUF( void )
{
	BYTE i = 0;
	for( i = 0; i < 8; i ++ )
		SPI_SI_BUF[i] = 0x00;
}
#endif

void drvFlashWaitSPINotBusy(void)
{
	BYTE u8Retry = 100;
	while(!(SPI_STATUS & BIT0) && u8Retry--)
		ForceDelay1ms(1);
	if (SPI_STATUS & BIT0)
		SPI_CLR_STATUS = 0x01; //clr int
	//printData("u8Retry=%d",u8Retry);
}

///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Return true when flash type is PMC .
///////////////////////////////////////////////////////////////////////////////
Bool FlashTypeIs_PMC( void )
{
	BYTE ucID = 0;
	// 1st
	SPI_SI_BUF[0] = PMC_READ_ID;
	// 2nd
	SPI_SI_BUF[1] = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
	SPI_CTRL1       = (EN_2ND_CMD | EN_AUTO_CHECK | RDSR_IN_2ND);
	SET_WBF_SIZE(1, 1, 0);
	SET_RBF_SIZE(3, 1, 0);
	SPI_TRIGGER  = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
	ucID = SPI_SO_BUF[1];
	if( ucID == FLASH_PMC )
	{
		if( SPI_SO_BUF[2] == PM25_LD020 )
			g_ucFlashDeviceID = PM25_LD020;
		else if( SPI_SO_BUF[2] == PM25_LV020 )
			g_ucFlashDeviceID = PM25_LV020;
		else if( SPI_SO_BUF[2] == PM25_LQ020 )
			g_ucFlashDeviceID = PM25_LQ020;
		return TRUE;
	}
	return FALSE;
}
///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Return true when flash type is SST.
///////////////////////////////////////////////////////////////////////////////
Bool FlashTypeIs_SST( void )
{
	BYTE ucID = 0;
	// 1st
	SPI_SI_BUF[0] = SST_READ_ID;
	// 2nd
	SPI_SI_BUF[1] = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
	SPI_CTRL1       = (EN_2ND_CMD | EN_AUTO_CHECK | RDSR_IN_2ND);
	SET_WBF_SIZE(1, 1, 0);
	SET_RBF_SIZE(3, 1, 0);
	SPI_TRIGGER  = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
	ucID = SPI_SO_BUF[0];
	if( ucID == FLASH_SST )
		return TRUE;
	return FALSE;
}
///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Return true when flash type is MXIC.
///////////////////////////////////////////////////////////////////////////////
Bool FlashTypeIs_MXIC( void )
{
	BYTE ucID = 0;
	// 1st
	SPI_SI_BUF[0] = MXIC_READ_ID;
	// 2nd
	SPI_SI_BUF[1] = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
	SPI_CTRL1       = (EN_2ND_CMD | EN_AUTO_CHECK | RDSR_IN_2ND);
	SET_WBF_SIZE(1, 1, 0);
	SET_RBF_SIZE(3, 1, 0);
	SPI_TRIGGER  = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
	ucID = SPI_SO_BUF[0];
	if( ucID == FLASH_MXIC )
		return TRUE;
	return FALSE;
}
///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Return true when flash type is EON.
///////////////////////////////////////////////////////////////////////////////
Bool FlashTypeIs_EON( void )
{
	BYTE ucID = 0;
	// 1st
	SPI_SI_BUF[0] = EON_READ_ID;
	// 2nd
	SPI_SI_BUF[1] = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
	SPI_CTRL1       = (EN_2ND_CMD | EN_AUTO_CHECK | RDSR_IN_2ND);
	SET_WBF_SIZE(1, 1, 0);
	SET_RBF_SIZE(3, 1, 0);
	SPI_TRIGGER  = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
	ucID = SPI_SO_BUF[0];
	if( ucID == FLASH_EON )
		return TRUE;
	return FALSE;
}
///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Return true when flash type is AMIC.
///////////////////////////////////////////////////////////////////////////////
Bool FlashTypeIs_AMIC( void )
{
	BYTE ucID = 0;
	// 1st
	SPI_SI_BUF[0] = AMIC_READ_ID;
	// 2nd
	SPI_SI_BUF[1] = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
	SPI_CTRL1       = (EN_2ND_CMD | EN_AUTO_CHECK | RDSR_IN_2ND);
	SET_WBF_SIZE(1, 1, 0);
	SET_RBF_SIZE(3, 1, 0);
	SPI_TRIGGER  = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
	ucID = SPI_SO_BUF[0];
	if( ucID == FLASH_AMIC )
		return TRUE;
	return FALSE;
}
///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Return true when flash type is WINBOND.
///////////////////////////////////////////////////////////////////////////////
Bool FlashTypeIs_WINBOND( void )
{
	BYTE ucID = 0;
	// 1st
	SPI_SI_BUF[0] = WINBOND_READ_ID;
	// 2nd
	SPI_SI_BUF[1] = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
	SPI_CTRL1       = (EN_2ND_CMD | EN_AUTO_CHECK | RDSR_IN_2ND);
	SET_WBF_SIZE(1, 1, 0);
	SET_RBF_SIZE(3, 1, 0);
	SPI_TRIGGER  = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
	ucID = SPI_SO_BUF[0];
	//FLASH_printData("W9F-2:%x",SPI_SO_BUF[2]);
	if( ucID == FLASH_WINBOND )
	{
		ucID = SPI_SO_BUF[2];
		if(ucID == W25X05CL)
			g_ucFlashDeviceID = W25X05CL;
		else if(ucID == W25X10CL)
			g_ucFlashDeviceID = W25X10CL;
		else if(ucID == W25X20CL)
			g_ucFlashDeviceID = W25X20CL;
		else if(ucID == W25X40BV)
			g_ucFlashDeviceID = W25X40BV;
		return TRUE;
	}
	return FALSE;
}

BYTE ReadFlashUniqueID_Winbond(void)
{
	// 1st
	SPI_SI_BUF[0] = WINBOND_READ_UNIQUE_ID; // with 4 dummy bytes
	// 2nd
	SPI_SI_BUF[5] = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
	SPI_CTRL1       = (EN_2ND_CMD | EN_AUTO_CHECK | RDSR_IN_2ND);
	SET_WBF_SIZE(5, 1, 0);
	SET_RBF_SIZE(1, 1, 0);
	SPI_TRIGGER  = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
	return SPI_SO_BUF[0];
}

BYTE ReadFlashDeviceID_MXIC( void )
{
	// 1st
	SPI_SI_BUF[0] = MXIC_RES;
	SPI_SI_BUF[1] = 0x00;
	SPI_SI_BUF[2] = 0x00;
	SPI_SI_BUF[3] = 0x00;
	// 2nd
	SPI_SI_BUF[4] = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
	SPI_CTRL1       = (EN_2ND_CMD | EN_AUTO_CHECK | RDSR_IN_2ND);
	SET_WBF_SIZE(4, 1, 0);
	SET_RBF_SIZE(1, 1, 0);
	SPI_TRIGGER  = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
	return SPI_SO_BUF[0];
}

///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Return true when flash type is GIGA DEVICE .
///////////////////////////////////////////////////////////////////////////////
Bool FlashTypeIs_GigaDevice( void )
{
	BYTE ucID = 0;
	// 1st
	SPI_SI_BUF[0] = GIGADEVICE_READ_ID;
	// 2nd
	SPI_SI_BUF[1] = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE;
	SPI_CTRL1       = (EN_2ND_CMD | EN_AUTO_CHECK | RDSR_IN_2ND);
	SET_WBF_SIZE(1, 1, 0);
	SET_RBF_SIZE(3, 1, 0);
	SPI_TRIGGER  = 0x01;
	drvFlashWaitSPINotBusy();
	ucID = SPI_SO_BUF[0];
	if( ucID == FLASH_GIGADEVICE )
	{
		if( SPI_SO_BUF[2] == GD25M21B )
			g_ucFlashDeviceID = GD25M21B;
		else if( SPI_SO_BUF[2] == GD25M41B )
			g_ucFlashDeviceID = GD25M41B;
		return TRUE;
	}
	return FALSE;
}

#if Enable_FMFlash_Save
///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Return true when flash type is FMSH.
///////////////////////////////////////////////////////////////////////////////
Bool FlashTypeIs_FMSH(void)
{
	BYTE ucID = 0;
	// 1st
	SPI_SI_BUF[0] = FMSH_READ_ID;
	// 2nd
	SPI_SI_BUF[1] = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
	SPI_CTRL1       = (EN_2ND_CMD | EN_AUTO_CHECK | RDSR_IN_2ND);
	SET_WBF_SIZE(1, 1, 0);
	SET_RBF_SIZE(3, 1, 0);
	SPI_TRIGGER  = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
	ucID = SPI_SO_BUF[0];
	if( ucID == FLASH_FMSH)
	{
		if( SPI_SO_BUF[2] == FM25Q04)
			g_ucFlashDeviceID = FM25Q04;
		else if( SPI_SO_BUF[2] == FM25Q02)
			g_ucFlashDeviceID = FM25Q02;
		return TRUE;
	}
	return FALSE;
}
#endif

#define FLASH_IS_MXIC(id)     (id == FLASH_MXIC)
#define FLASH_IS_WINBOND(id)    (id == FLASH_WINBOND)
#define FLASH_IS_GIGADEVICE(id)     (id == FLASH_GIGADEVICE)
#if Enable_FMFlash_Save
#define FLASH_IS_FMSH(id)     (id == FLASH_FMSH)
#endif

#define MXIC_FLASH_4M()   (g_ucFlashDeviceID == MX_4026 || g_ucFlashDeviceID == MX_4025)
#define WINBOND_FLASH_4M()  (g_ucFlashDeviceID == W25X40BV || g_ucFlashDeviceID == W25X41CL)
#define GIGADEVICE_FLASH_4M()   (g_ucFlashDeviceID == GD25M41B)
void CheckFlashSize(FlashID)
{
	if(FLASH_IS_MXIC(FlashID) && MXIC_FLASH_4M())
		g_FlashSize = FLASH_SIZE_4M;
	else if(FLASH_IS_WINBOND(FlashID) && WINBOND_FLASH_4M())
		g_FlashSize = FLASH_SIZE_4M;
	else if(FLASH_IS_GIGADEVICE(FlashID) && GIGADEVICE_FLASH_4M())
		g_FlashSize = FLASH_SIZE_4M;
	else
		g_FlashSize = FLASH_SIZE_2M;
	#if 0//need Modify
	g_FlashSize = FLASH_SIZE_4M;
	#endif
}

///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Read flash Manufacturer ID include PMC, MXIC, EON, and SST.
//                Return FLASH_UNKNOW if not found
// <Returns> : Manufacturer ID.
///////////////////////////////////////////////////////////////////////////////
BYTE ReadFlashID( void )
{
	BYTE ucID;
	FlashVersionCheck();
	if( FlashTypeIs_PMC() )
		ucID = FLASH_PMC;
	else if( FlashTypeIs_MXIC() )
	{
		ucID = ReadFlashDeviceID_MXIC();
		if( ucID == MX_2026 /*||( ucID == 0x12 )*/)//20130521 for I2460 new 4m flash
			g_ucFlashDeviceID = MX_2026;
		else if( ucID == MX_4026 )
			g_ucFlashDeviceID = MX_4026;
		else if( ucID == MX_4025 )
			g_ucFlashDeviceID = MX_4025;
		else
			g_ucFlashDeviceID = MX_2025;
		ucID = FLASH_MXIC;
		FLASH_printData( "   g_ucFlashDeviceID[%x]", g_ucFlashDeviceID );
	}
	else if( FlashTypeIs_EON() )
		ucID = FLASH_EON;
	else if( FlashTypeIs_SST() )
		ucID = FLASH_SST;
	else if( FlashTypeIs_AMIC() )
		ucID = FLASH_AMIC;
	else if( FlashTypeIs_WINBOND() )
	{
		ucID = FLASH_WINBOND;
		if(g_ucFlashDeviceID == W25X20CL)
		{
			if(W25X21CL == ReadFlashUniqueID_Winbond())
				g_ucFlashDeviceID = W25X21CL;
		}
		else if(g_ucFlashDeviceID == W25X40BV)
		{
			if(W25X41CL == ReadFlashUniqueID_Winbond())
				g_ucFlashDeviceID = W25X41CL;
		}
		FLASH_printData( "   WinbondUniqueID[%x]", g_ucFlashDeviceID );
	}
	else if(FlashTypeIs_GigaDevice())
		ucID = FLASH_GIGADEVICE;
	#if 	Enable_FMFlash_Save
	else if(FlashTypeIs_FMSH())
		ucID = FLASH_FMSH;
	#endif
	else
		ucID = FLASH_UNKNOW;
	CheckFlashSize(ucID);
	return ucID;
}

#if 1//USEFLASH //------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Read flash status register.
//
// <Returns> : Flash status register.
///////////////////////////////////////////////////////////////////////////////
BYTE FlashReadSR( void )
{
	SPI_SI_BUF[0]   = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
	SPI_CTRL1       = (RDSR_IN_1ST | EN_AUTO_CHECK);
	SET_WBF_SIZE(1, 0, 0);
	SET_RBF_SIZE(1, 0, 0);
	SPI_TRIGGER     = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
	return SPI_SO_BUF[0];
}
///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Flash Write enable
//Prior to any Byte-Program, AAI-Program, Sector-Erase, Block-Erase, or Chip-Erase operation, the Write-Enable (WREN)
//instruction must be executed.
//Wait WIP(SR[0]) clear then send WREN command
///////////////////////////////////////////////////////////////////////////////
//void FlashWriteEnable( void )
//{}

///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Write value to flash status register
// <Parameter>:  -  <Flow>  -  <Description>
//-----------------------------------------------------------------------------
//  value  -    In    -   which value write to flash status register
///////////////////////////////////////////////////////////////////////////////
void FlashWriteSR( BYTE value )
{
	if( g_ucFlashID == FLASH_SST )
	{
		// 1st
		SPI_SI_BUF[0]   = EWSR;
		// 2nd
		SPI_SI_BUF[1]   = WRSR;
		SPI_SI_BUF[2]   = value;
		// 3rd
		SPI_SI_BUF[3]   = RDSR;
		SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
		SPI_CTRL1       = (EN_2ND_CMD | EN_3RD_CMD | RDSR_IN_3RD | EN_AUTO_CHECK);
		SET_WBF_SIZE(1, 2, 1);
		SET_RBF_SIZE(0, 0, 1);
	}
	else if( g_ucFlashID == FLASH_AMIC )
	{
		BYTE SSR = FlashReadSR();
		if( SSR & 0x40 ) //_BIT6)
		{
			// 1st
			SPI_SI_BUF[0]   = WREN;
			// 2nd
			SPI_SI_BUF[1] = 0x90;
			SPI_SI_BUF[2] = 0x00;
			SPI_SI_BUF[3] = 0x28;
			SPI_SI_BUF[4] = 0x00;
			SPI_SI_BUF[5] = 0x3B;
			SPI_SI_BUF[6] = 0x00;
			SPI_SI_BUF[7] = 0x28;
			SPI_SI_BUF[8] = 0xFF;
			// 3rd
			SPI_SI_BUF[9]   = RDSR;
			SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
			SPI_CTRL1       = (EN_2ND_CMD | EN_3RD_CMD | RDSR_IN_3RD | EN_AUTO_CHECK);
			SET_WBF_SIZE(1, 8, 1);
			SET_RBF_SIZE(0, 0, 1);
			SPI_TRIGGER     = 0x01; //start flash programming
			drvFlashWaitSPINotBusy();
			// 1st
			SPI_SI_BUF[0]   = WRSR;
			SPI_SI_BUF[1]   = value;
			// 2nd
			SPI_SI_BUF[2]   = RDSR;
			SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
			SPI_CTRL1       = (EN_2ND_CMD | RDSR_IN_2ND | EN_AUTO_CHECK);
			SET_WBF_SIZE(2, 1, 0);
			SET_RBF_SIZE(0, 1, 0);
		}
		else
		{
			// 1st
			SPI_SI_BUF[0]   = WREN;
			// 2nd
			SPI_SI_BUF[1]   = WRSR;
			SPI_SI_BUF[2]   = value;
			// 3rd
			SPI_SI_BUF[3]   = RDSR;
			SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
			SPI_CTRL1       = (EN_2ND_CMD | EN_3RD_CMD | RDSR_IN_3RD | EN_AUTO_CHECK);
			SET_WBF_SIZE(1, 2, 1);
			SET_RBF_SIZE(0, 0, 1);
		}
	}
	#if !Enable_GDFlash_Save
	else if( g_ucFlashID == FLASH_GIGADEVICE && (g_ucFlashDeviceID == GD25M21B || g_ucFlashDeviceID == GD25M41B))
	{
		BYTE SR15_8;
		SPI_SI_BUF[0]   = RDSR;
		SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
		SPI_CTRL1       = (RDSR_IN_1ST | EN_AUTO_CHECK);
		SET_WBF_SIZE(1, 0, 0);
		SET_RBF_SIZE(2, 0, 0);
		SPI_TRIGGER     = 0x01; //start flash programming
		drvFlashWaitSPINotBusy();
		// recover status register S15~S8
		SR15_8 = SPI_SO_BUF[1];
		// 1st
		SPI_SI_BUF[0]   = WREN;
		// 2nd
		SPI_SI_BUF[1]   = WRSR;
		SPI_SI_BUF[2]   = value;
		SPI_SI_BUF[3]   = SR15_8;
		// 3rd
		SPI_SI_BUF[4]   = RDSR;
		SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
		SPI_CTRL1       = (EN_2ND_CMD | EN_3RD_CMD | RDSR_IN_3RD | EN_AUTO_CHECK);
		SET_WBF_SIZE(1, 3, 1);
		SET_RBF_SIZE(0, 0, 1);
	}
	#endif
	else
	{
		// 1st
		SPI_SI_BUF[0]   = WREN;
		// 2nd
		SPI_SI_BUF[1]   = WRSR;
		SPI_SI_BUF[2]   = value;
		// 3rd
		SPI_SI_BUF[3]   = RDSR;
		SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
		SPI_CTRL1       = (EN_2ND_CMD | EN_3RD_CMD | RDSR_IN_3RD | EN_AUTO_CHECK);
		SET_WBF_SIZE(1, 2, 1);
		SET_RBF_SIZE(0, 0, 1);
	}
	SPI_TRIGGER     = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
}
///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Only used in PMC type flash. To disable protect of specific sector.
//                     if wAddr < FDATA_FACTORY_ADDR will not unprotect
// <Parameter>:  <Description>
//  wAddr : Which sector address will be unportect
///////////////////////////////////////////////////////////////////////////////
void FlashPMCUnprotectEnable( WORD wAddr )
{
	if( wAddr < FDATA_START_ADDR )
		return;
	if( g_ucFlashDeviceID == PM25_LD020 || g_ucFlashDeviceID == PM25_LQ020)
	{
		// 1st
		SPI_SI_BUF[0]   = WREN;
		// 2nd
		SPI_SI_BUF[1]   = PMC_UNPROTECT;
		SPI_SI_BUF[2]   = TOTAL_BANK_NUM - 1;
		SPI_SI_BUF[3]   = ( wAddr >> 8 ) & 0x0f0;
		SPI_SI_BUF[4]   = 0x00;
		// 3rd
		SPI_SI_BUF[5]   = RDSR;
		SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
		SPI_CTRL1       = (EN_2ND_CMD | EN_3RD_CMD | RDSR_IN_3RD | EN_AUTO_CHECK);
		SET_WBF_SIZE(1, 4, 1);
		SET_RBF_SIZE(0, 0, 1);
		/*
		SPI_SI_BUF[0] = WREN;
		SPI_CTRL = 0xF8;
		SPI_SI_BUF[0] = PMC_UNPROTECT;
		SPI_SI_BUF[1] = TOTAL_BANK_NUM - 1; //(wAddr>>16)&0x0ff;
		SPI_SI_BUF[2] = ( wAddr >> 8 ) & 0x0f0;
		SPI_SI_BUF[3] = 0x00; //wAddr&0x0ff;
		SPI_CTRL = 0xFB;
		*/
	}
	else
	{
		hw_ClrFlashWP();
		Delay1ms( 1 );
		// 1st
		SPI_SI_BUF[0] = PMC_UNPROTECT;
		SPI_SI_BUF[1] = TOTAL_BANK_NUM - 1; //(wAddr>>16)&0x0ff;
		SPI_SI_BUF[2] = ( wAddr >> 8 ) & 0x0ff;
		SPI_SI_BUF[3] = wAddr & 0x0ff;
		// 2nd
		SPI_SI_BUF[4]   = RDSR;
		SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
		SPI_CTRL1       = (EN_2ND_CMD | RDSR_IN_2ND | EN_AUTO_CHECK);
		SET_WBF_SIZE(4, 1, 0);
		SET_RBF_SIZE(0, 1, 0);
		/*
		SPI_SI_BUF[0] = PMC_UNPROTECT;
		SPI_SI_BUF[1] = TOTAL_BANK_NUM - 1; //(wAddr>>16)&0x0ff;
		SPI_SI_BUF[2] = ( wAddr >> 8 ) & 0x0ff;
		SPI_SI_BUF[3] = wAddr & 0x0ff;
		SPI_CTRL = 0xBB;
		*/
	}
	SPI_TRIGGER     = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
}
///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Only used in PMC type flash. To disable un-protect of specific sector.
///////////////////////////////////////////////////////////////////////////////
void FlashPMCUnprotectDisable( void )
{
	// 1st
	SPI_SI_BUF[0] = PMC_PROTECT;
	// 2nd
	SPI_SI_BUF[1] = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
	SPI_CTRL1       = (EN_2ND_CMD | RDSR_IN_2ND | EN_AUTO_CHECK);
	SET_WBF_SIZE(1, 1, 0);
	SET_RBF_SIZE(0, 1, 0);
	SPI_TRIGGER     = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
	/*
	SPI_SI_BUF[0] = PMC_PROTECT;
	SPI_CTRL = 0xF8;
	*/
}


void FlashDisableStausProtect_MXIC2026( void )
{
	if( g_ucFlashID == FLASH_MXIC && (g_ucFlashDeviceID == MX_2026 || g_ucFlashDeviceID == MX_4026) )
	{
		hw_ClrFlashWP();
		Delay1ms( 1 );
		FlashWriteSR( 0x7F );
		if( bFlashWriteFactory )
			FlashWriteSR( UNPROTECT_MXIC2026_3A_3F ); 	//130710 for new request
		else
			FlashWriteSR( FLASH_MXIC2026_USER_AREA ); 	//130710 for new request
	}
}
//130710 for new request
#define FlashEnableWP_PMC     FlashPMCUnprotectDisable

void FlashEnableWP_EON(BYTE SRValue)
{
	if(( SRValue & 0x94 ) != 0x94 )
	{
		//FLASH_printData("  EnableWP_EON_SR[%x] W_94",SSR);
		hw_ClrFlashWP();
		Delay1ms( 1 );
		FlashWriteSR( 0x94 );
	}
}

void FlashEnableWP_AMIC(BYTE SRValue)
{
	if(( SRValue & 0xFC ) != 0xE8 )
	{
		//FLASH_printData("  EnableWP_AMIC_SR[%x] E8_0",SSR);
		hw_ClrFlashWP();
		Delay1ms( 1 );
		FlashWriteSR( 0xE8 );
		//FLASH_printData("  EnableWP_AMIC_SR[%x] E8_1",SSR);
	}
}

void FlashEnableWP_WINBOND(BYTE SRValue)
{
	if(g_ucFlashDeviceID == W25X21CL || g_ucFlashDeviceID == W25X41CL)
	{
		if((SRValue & FLASH_WINBOND_X21_X41_USER_AREA) != FLASH_WINBOND_X21_X41_USER_AREA)
		{
			hw_ClrFlashWP();
			Delay1ms( 1 );
			FlashWriteSR( FLASH_WINBOND_X21_X41_USER_AREA );
		}
	}
	else if(g_ucFlashDeviceID == W25X40BV)
	{
		if((SRValue & 0xAC) != 0xAC)
		{
			hw_ClrFlashWP();
			Delay1ms( 1 );
			FlashWriteSR( 0xAC ); // protect lower 256K(0~0x3FFFF)
		}
	}
	else if(g_ucFlashDeviceID == W25X20BV)
	{
		if((SRValue & 0xA8) != 0xA8)
		{
			hw_ClrFlashWP();
			Delay1ms( 1 );
			FlashWriteSR( 0xA8 ); // protect lower 128K(0~0x1FFFF)
		}
	}
	else if(g_ucFlashDeviceID == W25X10BV)
	{
		if((SRValue & 0xA4) != 0xA4)
		{
			hw_ClrFlashWP();
			Delay1ms( 1 );
			FlashWriteSR( 0xA4 ); // protect lower 64K(0~0x0FFFF)
		}
	}
	else
	{
		if((SRValue & 0x8C) != 0x8C)
		{
			hw_ClrFlashWP();
			Delay1ms( 1 );
			FlashWriteSR( 0x8C ); // protect all
		}
	}
}

#define FLASH_SR_PROTECT_WHOLE_AREA     ((g_FlashSize == FLASH_SIZE_2M)?(0x8C):(0x9C))
void FlashEnableWP_OTHERS(BYTE SRValue)
{
	if(( SRValue & FLASH_SR_PROTECT_WHOLE_AREA ) != FLASH_SR_PROTECT_WHOLE_AREA )
	{
		//FLASH_printData("  EnableWP__SR[%x] W_8C",SSR);
		hw_ClrFlashWP();
		Delay1ms( 1 );
		FlashWriteSR( FLASH_SR_PROTECT_WHOLE_AREA );
	}
}

#if !Enable_GDFlash_Save
void FlashEnableWP_GigaDevice_GD25M21B_GD25M41B(BYTE SRValue)
{
	// all block set to protect
	if((SRValue & 0xFC) != 0xFC)
	{
		hw_ClrFlashWP();
		Delay1ms( 1 );
		FlashWriteSR( 0xFC );
	}
	// setor lock
	// 1st
	SPI_SI_BUF[0] = GIGADEVICE_PROTECT;
	// 2nd
	SPI_SI_BUF[1] = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE;
	SPI_CTRL1       = (EN_2ND_CMD | RDSR_IN_2ND | EN_AUTO_CHECK);
	SET_WBF_SIZE(1, 1, 0);
	SET_RBF_SIZE(0, 1, 0);
	SPI_TRIGGER     = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
}
#endif

#define FlashDisableWP_PMC      		FlashPMCUnprotectEnable
#define FlashDisableWP_MXIC_MX2026      FlashDisableStausProtect_MXIC2026
void FlashDisableWP_EON(BYTE SRValue)
{
	hw_ClrFlashWP();
	Delay1ms( 1 );
	if( bFlashWriteFactory )
	{
		//FLASH_printData("  _EON_SR[%x] W_00",SSR);
		FlashWriteSR( 0x00 );
	}
	else
	{
		if(( SRValue & 0x94 ) != 0x94 )
		{
			//FLASH_printData("  _EON_SR[%x] W_94",SSR);
			FlashWriteSR( 0x94 );
		}
	}
}
void FlashDisableWP_WINBOND_W25X21CL(void)
{
	// X21CL: // 0xC0: protect range 0~0x39FFF; 0xE0: 0~0x3BFFF
	// X41CL: // 0xC0: protect range 0~0x79FFF; 0xE0: 0~0x7BFFF
	hw_ClrFlashWP();
	Delay1ms( 1 );
	if( bFlashWriteFactory )
	{
		FlashWriteSR( UNPROTECT_WINBOND_X21_3A_3F );
	}
	else
	{
		FlashWriteSR( FLASH_WINBOND_X21_X41_USER_AREA );
	}
}

void FlashDisableWP_OTHERS(BYTE SRValue)
{
	hw_ClrFlashWP();
	Delay1ms( 1 );
	if( SRValue != 0x00 )
	{
		FlashWriteSR( 0x00 );
	}
}


#if !Enable_GDFlash_Save
// use sector unlock to disable write protection
void FlashDisableWP_GigaDevice_GD25M21B_GD25M41B(WORD wAddr)
{
	// 1st
	SPI_SI_BUF[0]   = WREN;
	// 2nd
	SPI_SI_BUF[1]   = GIGADEVICE_UNPROTECT;
	SPI_SI_BUF[2]   = TOTAL_BANK_NUM - 1;
	SPI_SI_BUF[3]   = ( wAddr >> 8 ) & 0x0f0;
	SPI_SI_BUF[4]   = 0x00;
	// 3rd
	SPI_SI_BUF[5]   = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
	SPI_CTRL1       = (EN_2ND_CMD | EN_3RD_CMD | RDSR_IN_3RD | EN_AUTO_CHECK);
	SET_WBF_SIZE(1, 4, 1);
	SET_RBF_SIZE(0, 0, 1);
	SPI_TRIGGER     = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
}
#endif

///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Enable flash write protect
///////////////////////////////////////////////////////////////////////////////
void FlashEnableWP( void ) 	//130710 for new request
{
	BYTE SSR;
	SSR = FlashReadSR();
	if( g_ucFlashID == FLASH_PMC )
	{
		FlashEnableWP_PMC();//FlashPMCUnprotectDisable();
	}
	else if( g_ucFlashID == FLASH_EON )
	{
		FlashEnableWP_EON(SSR);
	}
	else if( g_ucFlashID == FLASH_AMIC )
	{
		FlashEnableWP_AMIC(SSR);
	}
	else if( g_ucFlashID == FLASH_MXIC && (g_ucFlashDeviceID == MX_2026 || g_ucFlashDeviceID == MX_4026) )
	{
		//SRAM type auto protect when write finish
	}
	else if( g_ucFlashID == FLASH_WINBOND )
	{
		FlashEnableWP_WINBOND(SSR);
	}
	#if !Enable_GDFlash_Save
	else if( g_ucFlashID == FLASH_GIGADEVICE && (g_ucFlashDeviceID == GD25M21B || g_ucFlashDeviceID == GD25M41B) )
	{
		FlashEnableWP_GigaDevice_GD25M21B_GD25M41B(SSR);
	}
	#endif
	else
	{
		FlashEnableWP_OTHERS(SSR);
	}
	//FlashWriteDisable();
	hw_SetFlashWP();
}
///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Disable flash write protect
///////////////////////////////////////////////////////////////////////////////
void FlashDisableWP( WORD wAddr ) 	//130710 for new request
{
	BYTE SSR;
	if( wAddr < FDATA_START_ADDR )
		return;
	SSR = FlashReadSR();
	if( g_ucFlashID == FLASH_PMC )
	{
		FlashDisableWP_PMC(wAddr);//FlashPMCUnprotectEnable( wAddr );
	}
	else if( g_ucFlashID == FLASH_EON )
	{
		FlashDisableWP_EON(SSR);
	}
	else if( g_ucFlashID == FLASH_AMIC )
	{
		;
	}
	else if( g_ucFlashID == FLASH_MXIC && (g_ucFlashDeviceID == MX_2026 || g_ucFlashDeviceID == MX_4026) )
	{
		FlashDisableWP_MXIC_MX2026();//FlashDisableStausProtect_MXIC2026();
	}
	else if( g_ucFlashID == FLASH_WINBOND && (g_ucFlashDeviceID == W25X21CL || g_ucFlashDeviceID == W25X41CL)) // just 21CL needs to change SR
	{
		FlashDisableWP_WINBOND_W25X21CL();
	}
	#if !Enable_GDFlash_Save
	else if( g_ucFlashID == FLASH_GIGADEVICE && (g_ucFlashDeviceID == GD25M21B || g_ucFlashDeviceID == GD25M41B) )
	{
		FlashDisableWP_GigaDevice_GD25M21B_GD25M41B(wAddr);
	}
	#endif
	else
	{
		FlashDisableWP_OTHERS(SSR);
	}
}

///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Flash erase function
// <Parameter>:  -  <Flow>  -  <Description>
//-----------------------------------------------------------------------------
//  bDoWP   -   In  -   Doing FlashDisableWP at start and FlashEnableWP at end
//  wAddr   -   In  -   Erase 4K BYTE sector address
///////////////////////////////////////////////////////////////////////////////
void FlashSectorErase( Bool bDoWP, WORD wAddr )
{
	bit bcachestatus;
	if( wAddr < FDATA_START_ADDR )
		return;
	bcachestatus = CACHE_STATUS();//CacheStatus();
	if( bcachestatus )
		CACHE_DISABLE();//DisableCache();
	if( bDoWP )
		FlashDisableWP( wAddr );
	// 1st
	SPI_SI_BUF[0]   = WREN;
	// 2nd
	if( g_ucFlashID == FLASH_SST )
		SPI_SI_BUF[1] = SST_ERASE_SECTOR;
	else if( g_ucFlashID == FLASH_PMC )
		SPI_SI_BUF[1] = PMC_ERASE_SECTOR;
	else if( g_ucFlashID == FLASH_MXIC )
		SPI_SI_BUF[1] = MXIC_ERASE_SECTOR;
	else if( g_ucFlashID == FLASH_EON )
		SPI_SI_BUF[1] = EON_ERASE_SECTOR;
	else if( g_ucFlashID == FLASH_AMIC )
		SPI_SI_BUF[1] = AMIC_ERASE_SECTOR;
	else if( g_ucFlashID == FLASH_WINBOND )
		SPI_SI_BUF[1] = WINBOND_ERASE_SECTOR;
	else
		SPI_SI_BUF[1] = SST_ERASE_SECTOR;
	SPI_SI_BUF[2] = TOTAL_BANK_NUM - 1; //(wAddr>>16)&0x0ff;
	SPI_SI_BUF[3] = ( wAddr >> 8 ) & 0x0ff;
	SPI_SI_BUF[4] = wAddr & 0x0ff;
	// 3rd
	SPI_SI_BUF[5]   = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
	SPI_CTRL1       = (EN_2ND_CMD | EN_3RD_CMD | RDSR_IN_3RD | EN_AUTO_CHECK);
	SET_WBF_SIZE(1, 4, 1);
	SET_RBF_SIZE(0, 0, 1);
	SPI_TRIGGER     = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
	/*
	FlashWriteEnable();
	if( g_ucFlashID == FLASH_SST )
	    SPI_SI_BUF[0] = SST_ERASE_SECTOR;
	else if( g_ucFlashID == FLASH_PMC )
	    SPI_SI_BUF[0] = PMC_ERASE_SECTOR;
	else if( g_ucFlashID == FLASH_MXIC )
	    SPI_SI_BUF[0] = MXIC_ERASE_SECTOR;
	else if( g_ucFlashID == FLASH_EON )
	    SPI_SI_BUF[0] = EON_ERASE_SECTOR;
	else if( g_ucFlashID == FLASH_AMIC )
	    SPI_SI_BUF[0] = AMIC_ERASE_SECTOR;
	else
	    SPI_SI_BUF[0] = SST_ERASE_SECTOR;

	SPI_SI_BUF[1] = TOTAL_BANK_NUM - 1; //(wAddr>>16)&0x0ff;
	SPI_SI_BUF[2] = ( wAddr >> 8 ) & 0x0ff;
	SPI_SI_BUF[3] = wAddr & 0x0ff;

	SPI_CTRL = 0xFB; //0xFC;
	*/
	if( bDoWP )
		FlashEnableWP();
	if( bcachestatus )
		CACHE_ENABLE();//EnableCache();
}

///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Write one byte to flash
// <Parameter>: -  <Flow>   -   <Description>
//-----------------------------------------------------------------------------
//  bDoWP   -   In  -   Doing FlashDisableWP at start and FlashEnableWP at end
//  wAddr   -   In  -   Flash Address to be write, high byte address will be (TOTAL_BANK_NUM-1)
//                      wAddr < FDATA_FACTORY_ADDR will be limit, so address < 0x3B000 will be limit
//  value   -   In  -   The value write to flash
///////////////////////////////////////////////////////////////////////////////
void FlashWriteByte( Bool bDoWP, WORD wAddr, BYTE value )
{
	bit bcachestatus;
	if( wAddr < FDATA_START_ADDR )
		return;
	bcachestatus = CACHE_STATUS();//CacheStatus();
	if( bcachestatus )
		CACHE_DISABLE();//DisableCache();
	if( bDoWP )
		FlashDisableWP( wAddr );
	else
		FlashDisableStausProtect_MXIC2026();
	// 1st
	SPI_SI_BUF[0]   = WREN;
	// 2nd
	SPI_SI_BUF[1] = BYTE_WRITE;
	SPI_SI_BUF[2] = TOTAL_BANK_NUM - 1; //(wAddr>>16)&0x0ff;
	SPI_SI_BUF[3] = ( wAddr >> 8 ) & 0x0ff;
	SPI_SI_BUF[4] = wAddr & 0x0ff;
	SPI_SI_BUF[5] = value;
	// 3rd
	SPI_SI_BUF[6]   = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
	SPI_CTRL1       = (EN_2ND_CMD | EN_3RD_CMD | RDSR_IN_3RD | EN_AUTO_CHECK);
	SET_WBF_SIZE(1, 5, 1);
	SET_RBF_SIZE(0, 0, 1);
	SPI_TRIGGER     = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
	/*
	FlashWriteEnable();
	//CleanSPI_SI_BUF();
	//MCU_CACHE_CTL = 0x00;
	SPI_SI_BUF[0] = BYTE_WRITE;
	SPI_SI_BUF[1] = TOTAL_BANK_NUM - 1; //(wAddr>>16)&0x0ff;
	SPI_SI_BUF[2] = ( wAddr >> 8 ) & 0x0ff;
	SPI_SI_BUF[3] = wAddr & 0x0ff;
	SPI_SI_BUF[4] = value;
	SPI_CTRL = 0xFC;
	//MCU_CACHE_CTL = 0x20;
	//retry=10;
	//while((SPI_CTRL&BIT7)&&retry--)
	//  ForceDelay1ms(1);
	*/
	if( bDoWP )
		FlashEnableWP();
	//FLASH_printData("value=%x\n",value);
	//FLASH_printData("S4=%x",SPI_SI_BUF[4]);
	if( bcachestatus )
		CACHE_ENABLE();//EnableCache();
}

#if HDCPKEY_IN_Flash
void FlashHDCPWriteByte( WORD wAddr, BYTE value )
{
	bit bcachestatus;
	if( wAddr < FDATA_START_ADDR )
		return;
	bcachestatus = CACHE_STATUS();//CacheStatus();
	if( bcachestatus )
		CACHE_DISABLE();//DisableCache();
	FlashDisableStausProtect_MXIC2026();//For MXIC 2026
	// 1st
	SPI_SI_BUF[0]   = WREN;
	// 2nd
	SPI_SI_BUF[1] = BYTE_WRITE;
	SPI_SI_BUF[2] = TOTAL_BANK_NUM - 1; //(wAddr>>16)&0x0ff;
	SPI_SI_BUF[3] = ( wAddr >> 8 ) & 0x0ff;
	SPI_SI_BUF[4] = wAddr & 0x0ff;
	SPI_SI_BUF[5] = value;
	// 3rd
	SPI_SI_BUF[6]   = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
	SPI_CTRL1       = (EN_2ND_CMD | EN_3RD_CMD | RDSR_IN_3RD | EN_AUTO_CHECK);
	SET_WBF_SIZE(1, 5, 1);
	SET_RBF_SIZE(0, 0, 1);
	SPI_TRIGGER     = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
	/*
	FlashWriteEnable();
	SPI_SI_BUF[0] = BYTE_WRITE;
	SPI_SI_BUF[1] = TOTAL_BANK_NUM - 1; //(wAddr>>16)&0x0ff;
	SPI_SI_BUF[2] = ( wAddr >> 8 ) & 0x0ff;
	SPI_SI_BUF[3] = wAddr & 0x0ff;
	SPI_SI_BUF[4] = value;
	SPI_CTRL = 0xFC;
	*/
	if( bcachestatus )
		CACHE_ENABLE();//EnableCache();
}
#endif
///////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Read one byte from flash.
// <Returns> : Data value in the address
// <Parameter>:  -  <Flow>  -  <Description>
//-----------------------------------------------------------------------------
//  wAddr   -   In  -   Only in the same bank ot MsFlash.c
///////////////////////////////////////////////////////////////////////////////
#define xfr_FlashCode ((BYTE code*)0x0000)
BYTE FlashReadByte( WORD wAddr )
{
	return xfr_FlashCode[wAddr];
}

#if  ENABLE_USE_ISPTOOL_Write_HDCP
BYTE FlashReadHDCPByte(DWORD address)
{
	SPI_SI_BUF[0]   = (SPI_MODE == SPI_MODE_FR) ? H_READ : READ;
	SPI_SI_BUF[1]   = (address >> 16) & 0xff;
	SPI_SI_BUF[2]   = (address >> 8) & 0xff;
	SPI_SI_BUF[3]   = address & 0xff;
	//2nd
	SPI_SI_BUF[4]   = RDSR;
	if(SPI_MODE == SPI_MODE_FR)
		SPI_SI_BUF[5]   = RDSR;
	SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
	SPI_CTRL1       = (EN_2ND_CMD | RDSR_IN_2ND | EN_AUTO_CHECK);
	SET_WBF_SIZE( (SPI_MODE == SPI_MODE_FR) ? 5 : 4, 1, 0);
	SET_WBF_SIZE( 5, 1, 0);
	SET_RBF_SIZE(1, 1, 0);
	SPI_TRIGGER     = 0x01; //start flash programming
	drvFlashWaitSPINotBusy();
	return SPI_SO_BUF[0];
}
#endif

//////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Write a table to flash
// <Parameter>:     -   <Flow>  -   <Description>
// ---------------------------------------------------------------------------
//  bDoWP   -   In  -   Doing FlashDisableWP at start and FlashEnableWP at end
//  wAddr   -   In  -   Flash Address to be write, high byte address will be (TOTAL_BANK_NUM-1)
//                      wAddr < FDATA_FACTORY_ADDR will be limit, so address < 0x3B000 will be limit
//  buffer  -   In  -   Data pointer of the table
//  count   -   In  -   Number of data
//////////////////////////////////////////////////////////////////////////////
void Flash_WriteTbl( Bool bDoWP, WORD wAddr, BYTE *buffer, WORD count )
{
	WORD i = 0;
	bit bcachestatus;
	if( wAddr < FDATA_START_ADDR )
		return;
	bcachestatus = CACHE_STATUS();//CacheStatus();
	if( bcachestatus )
		CACHE_DISABLE();//DisableCache();
	if( bDoWP )
		FlashDisableWP( wAddr ); // 2005/5/11 ?Wと 10:19:39 by keng
	//MCU_CACHE_CTL = 0x00;
	while( count > 0 )
	{
		FlashDisableStausProtect_MXIC2026();
		// 1st
		SPI_SI_BUF[0]   = WREN;
		// 2nd
		SPI_SI_BUF[1] = BYTE_WRITE;
		SPI_SI_BUF[2] = TOTAL_BANK_NUM - 1; //(wAddr>>16)&0x0ff;
		SPI_SI_BUF[3] = ( wAddr >> 8 ) & 0x0ff;
		SPI_SI_BUF[4] = wAddr & 0x0ff;
		SPI_SI_BUF[5] = *( buffer + ( i++ ) );
		// 3rd
		SPI_SI_BUF[6]   = RDSR;
		SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
		SPI_CTRL1       = (EN_2ND_CMD | EN_3RD_CMD | RDSR_IN_3RD | EN_AUTO_CHECK);
		SET_WBF_SIZE(1, 5, 1);
		SET_RBF_SIZE(0, 0, 1);
		SPI_TRIGGER     = 0x01; //start flash programming
		drvFlashWaitSPINotBusy();
		/*
		FlashWriteEnable();
		SPI_SI_BUF[0] = BYTE_WRITE;
		SPI_SI_BUF[1] = TOTAL_BANK_NUM - 1; //(wAddr>>16)&0x0ff;
		SPI_SI_BUF[2] = ( wAddr >> 8 ) & 0x0ff;
		SPI_SI_BUF[3] = wAddr & 0x0ff;
		SPI_SI_BUF[4] = *( buffer + ( i++ ) );
		SPI_CTRL = 0xFC;
		*/
		wAddr += 1;
		count -= 1;
	}
	//MCU_CACHE_CTL = 0x20;
	if( bDoWP )
		FlashEnableWP();// 2005/5/11 ?Wと 10:19:43 by keng
	if( bcachestatus )
		CACHE_ENABLE();//EnableCache();
}
void Flash_MoveTbl( Bool bDoWP, WORD wSrcAddr, WORD wDestAddr, WORD count )
{
	BYTE ucTemp;
	bit bcachestatus;
	if( wDestAddr < FDATA_START_ADDR )
		return;
	bcachestatus = CACHE_STATUS();//CacheStatus();
	if( bcachestatus )
		CACHE_DISABLE();//DisableCache();
	if( bDoWP )
		FlashDisableWP( wDestAddr ); // 2005/5/11 ?Wと 10:19:39 by keng
	while( count > 0 )
	{
		ucTemp = FlashReadByte( wSrcAddr );
		FlashDisableStausProtect_MXIC2026();
		// 1st
		SPI_SI_BUF[0]   = WREN;
		// 2nd
		SPI_SI_BUF[1] = BYTE_WRITE;
		SPI_SI_BUF[2] = TOTAL_BANK_NUM - 1; //(wAddr>>16)&0x0ff;
		SPI_SI_BUF[3] = ( wDestAddr >> 8 ) & 0x0ff;
		SPI_SI_BUF[4] = wDestAddr & 0x0ff;
		SPI_SI_BUF[5] = ucTemp;
		// 3rd
		SPI_SI_BUF[6]   = RDSR;
		SPI_CTRL0       = SPI_CTRL_VALUE; //ctrl en FSP/reset
		SPI_CTRL1       = (EN_2ND_CMD | EN_3RD_CMD | RDSR_IN_3RD | EN_AUTO_CHECK);
		SET_WBF_SIZE(1, 5, 1);
		SET_RBF_SIZE(0, 0, 1);
		SPI_TRIGGER     = 0x01; //start flash programming
		drvFlashWaitSPINotBusy();
		/*
		FlashWriteEnable();
		SPI_SI_BUF[0] = BYTE_WRITE;
		SPI_SI_BUF[1] = TOTAL_BANK_NUM - 1; //(wDestAddr>>16)&0x0ff; // bank 3
		SPI_SI_BUF[2] = ( wDestAddr >> 8 ) & 0x0ff;
		SPI_SI_BUF[3] = wDestAddr & 0x0ff;
		SPI_SI_BUF[4] = ucTemp;
		SPI_CTRL = 0xFC;
		*/
		wSrcAddr += 1;
		wDestAddr += 1;
		count -= 1;
	}
	if( bDoWP )
		FlashEnableWP();// 2005/5/11 ?Wと 10:19:43 by keng
	if( bcachestatus )
		CACHE_ENABLE();//EnableCache();
}
//////////////////////////////////////////////////////////////////////////////
// <DRV><Description>: Read a table from flash
// <Parameter>:     -   <Flow>  -   <Description>
// ---------------------------------------------------------------------------
//  wAddr   -   In  -   Flash Address
//  buffer  -   Out -   Data point of the table
//  count   -   In  -   Number of BYTE data
//////////////////////////////////////////////////////////////////////////////
void Flash_ReadTbl( WORD wAddr, BYTE *buffer, WORD count )
{
	WORD i;
	for( i = 0; i < count; i++ )
		*( buffer + i ) = xfr_FlashCode[wAddr + i];
}


//////////////////////////////////////////////////////////////////////////////
// <API><Description>: Search specific FLASH_BUFFTER_TYPE form FDATA_BUF_ADDR(x)
// <Returns> : Specific buffer address when found; 0 when not found
// <Parameter>:     -   <Flow>  -   <Description>
// ---------------------------------------------------------------------------
//  ucType  -   In  -   buffer type, such as FBufType_MonitorSetting, FBufType_TimingMode ..
//////////////////////////////////////////////////////////////////////////////
WORD Flash_SearchBufferAddr( FLASH_BUFFTER_TYPE ucType )
{
	BYTE ucTemp;
	for( ucTemp = 0; ucTemp < FDATA_DYNAMIC_SECTOR_NUM; ucTemp++ )
	{
		if( FlashReadByte( FDATA_BUF_ADDR( ucTemp ) ) == ucType )
			return FDATA_BUF_ADDR( ucTemp );
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////
// <API><Description>: Compare the FlashReadByte(wAddr + i*wRange)==ucIdent
//                                 FlashReadByte(wAddr + i*wRange + wRange - 1) == ucChecksum
//                     return i if equal ,else return IDENT_NOT_FOUND
// Search index from wStartIdx to wEndIdx to replace i. Can from 0 search to 255(include)
// Also can from 255 to 0(include)
// <Returns> : Specific buffer address when found; IDENT_NOT_FOUND when not found
// <Parameter>:     -   <Flow>  -   <Description>
// ---------------------------------------------------------------------------
//  wAddr       -   In  -   Flash start Address
//  wStartIdx   -   In  -   wAddr + wStartIdx*wRange
//  wEndIdx     -   In  -   wAddr + wEndIdx*wRange
//  wRange      -   In  -   Each search range
//  ucIdent     -   In  -   Data of want to compare
//  ucChecksum  -   In  -   Data of want to compare
//////////////////////////////////////////////////////////////////////////////
WORD Flash_SearchIdentChecksum( WORD wAddr, WORD wStartIdx, WORD wEndIdx, WORD wRange, BYTE ucIdent, BYTE ucChecksum )
{
	WORD i;
	if( wStartIdx < wEndIdx )
	{
		i = wStartIdx;
		while( i >= wStartIdx && i <= wEndIdx )
		{
			if( FlashReadByte( wAddr + i * wRange ) == ucIdent && FlashReadByte( wAddr + i * wRange + wRange - 1 ) == ucChecksum )
				return i;
			i++;
		}
	}
	else
	{
		i = wStartIdx;
		while( i >= wEndIdx && i <= wStartIdx )
		{
			if( FlashReadByte( wAddr + i * wRange ) == ucIdent && FlashReadByte( wAddr + i * wRange + wRange - 1 ) == ucChecksum )
				return i;
			i--;
		}
	}
	//FLASH_printMsg("------- IDENT_CHECKSUM_NOT_FOUND -------");
	return IDENT_NOT_FOUND;
}

//////////////////////////////////////////////////////////////////////////////
//  <API><Description>: Get each buffer address and assign to variable
//  FLASH_MonitorSettingAddr
//  FLASH_MonitorSetting2Addr
//  FLASH_TimingModeAddr
//  FLASH_FactorySettingAddr
//  FLASH_FreeBufferAddr
//////////////////////////////////////////////////////////////////////////////
void Flash_GetBufferAddr(void)
{
	WORD wAddr;
	FLASH_HDCP_EDIDAddr = FDATA_HDCPKEY_START_ADDR;
	FLASH_FactorySettingAddr = FDATA_FACTORY_ADDR;
	FLASH_MonitorSettingAddr = 0;
	FLASH_MonitorSetting2Addr = 0;
	FLASH_TimingModeAddr = 0;
	FLASH_FreeBufferAddr = 0;
	FLASH_printData("_FGBA_ FLASH_FactorySettingAddr %x ", (WORD)(FLASH_FactorySettingAddr));
	wAddr = Flash_SearchBufferAddr(FBufType_MonitorSetting);
	if(wAddr)
	{
		FLASH_MonitorSettingAddr = wAddr;
		FLASH_printData("_FGBA_ FLASH_MonitorSettingAddr %x ", (WORD)(FLASH_MonitorSettingAddr));
	}
	wAddr = Flash_SearchBufferAddr(FBufType_MonitorSetting2);
	if(wAddr)
	{
		FLASH_MonitorSetting2Addr = wAddr;
		FLASH_printData("_FGBA_ FLASH_MonitorSetting2Addr %x ", (WORD)(FLASH_MonitorSetting2Addr));
	}
	wAddr = Flash_SearchBufferAddr(FBufType_TimingMode);
	if(wAddr)
	{
		FLASH_TimingModeAddr = wAddr;
		FLASH_printData("_FGBA_ FLASH_TimingModeAddr %x ", (WORD)(FLASH_TimingModeAddr));
	}
	wAddr = Flash_SearchBufferAddr(FBufType_EmptyBuffer);
	if(wAddr)
	{
		FLASH_FreeBufferAddr = wAddr;
		FLASH_printData("FLASH_FreeBufferAddr %x ", (WORD)(FLASH_FreeBufferAddr));
	}
	// 091022 coding, free buffer type should be 0xff or 0x00
	else
	{
		if((wAddr = Flash_SearchBufferAddr(FBufType_FullBuffer)) >= FDATA_DYNAMIC_ADDR)
			FLASH_FreeBufferAddr = wAddr;
	}
	return;
}


//////////////////////////////////////////////////////////////////////////////
// <API><Description>: After execute Flash_GetBufferAddr, makesure each address reasonable
//////////////////////////////////////////////////////////////////////////////
void Flash_AllocateBufferAddr(void)
{
	BYTE ucTemp;
	if(FLASH_MonitorSettingAddr == 0)
	{
		for(ucTemp = 0; ucTemp < FDATA_DYNAMIC_SECTOR_NUM; ucTemp++)
		{
			#if 0
			FLASH_printData("Flash_Allocate 01 %x ", (WORD)(FLASH_TimingModeAddr >> 8));
			FLASH_printData("Flash_Allocate 02 %x ", (WORD)(FLASH_FreeBufferAddr >> 8));
			FLASH_printData("Flash_Allocate 03 %x ", (WORD)(FDATA_BUF_ADDR(ucTemp) >> 8));
			#endif
			if(FDATA_BUF_ADDR(ucTemp) != FLASH_TimingModeAddr
			        && FDATA_BUF_ADDR(ucTemp) != FLASH_FreeBufferAddr
			        && FDATA_BUF_ADDR(ucTemp) != FLASH_MonitorSetting2Addr)
			{
				FLASH_MonitorSettingAddr = FDATA_BUF_ADDR(ucTemp);
				break;
			}
		}
		FLASH_printData("_FABA_ FLASH_MonitorSettingAddr %x ", (WORD)(FLASH_MonitorSettingAddr));
	}
	if(FLASH_MonitorSetting2Addr == 0)
	{
		for(ucTemp = 0; ucTemp < FDATA_DYNAMIC_SECTOR_NUM; ucTemp++)
		{
			if(FDATA_BUF_ADDR(ucTemp) != FLASH_MonitorSettingAddr
			        && FDATA_BUF_ADDR(ucTemp) != FLASH_TimingModeAddr
			        && FDATA_BUF_ADDR(ucTemp) != FLASH_FreeBufferAddr)
			{
				FLASH_MonitorSetting2Addr = FDATA_BUF_ADDR(ucTemp);
				break;
			}
		}
		FLASH_printData("_FABA_ FLASH_MonitorSetting2Addr %x ", (WORD)(FLASH_MonitorSetting2Addr));
	}
	if(FLASH_TimingModeAddr == 0)
	{
		for(ucTemp = 0; ucTemp < FDATA_DYNAMIC_SECTOR_NUM; ucTemp++)
		{
			if(FDATA_BUF_ADDR(ucTemp) != FLASH_MonitorSettingAddr
			        && FDATA_BUF_ADDR(ucTemp) != FLASH_FreeBufferAddr
			        && FDATA_BUF_ADDR(ucTemp) != FLASH_MonitorSetting2Addr)
			{
				FLASH_TimingModeAddr = FDATA_BUF_ADDR(ucTemp);
				break;
			}
		}
		FLASH_printData("_FABA_ FLASH_TimingModeAddr %x ", (WORD)(FLASH_TimingModeAddr));
	}
	if(FLASH_FreeBufferAddr == 0)
	{
		for(ucTemp = 0; ucTemp < FDATA_DYNAMIC_SECTOR_NUM; ucTemp++)
		{
			if(FDATA_BUF_ADDR(ucTemp) != FLASH_MonitorSettingAddr
			        && FDATA_BUF_ADDR(ucTemp) != FLASH_TimingModeAddr
			        && FDATA_BUF_ADDR(ucTemp) != FLASH_MonitorSetting2Addr)
			{
				FLASH_FreeBufferAddr = FDATA_BUF_ADDR(ucTemp);
				break;
			}
		}
		FLASH_printData("_FABA_ FLASH_FreeBufferAddr %x ", (WORD)(FLASH_FreeBufferAddr));
	}
	if(FLASH_MonitorSettingAddr == 0 || FLASH_MonitorSetting2Addr == 0 || FLASH_TimingModeAddr == 0 || FLASH_FreeBufferAddr == 0)
	{
		FLASH_MonitorSettingAddr = FDATA_BUF_ADDR(0);
		FLASH_MonitorSetting2Addr = FDATA_BUF_ADDR(1);
		FLASH_TimingModeAddr = FDATA_BUF_ADDR(2);
		FLASH_FreeBufferAddr = FDATA_BUF_ADDR(3);
		FLASH_printMsg("_FABA_ Addr NEW");
		FLASH_printData("_FABA_ FLASH_MonitorSettingAddr %x ", (WORD)(FLASH_MonitorSettingAddr));
		FLASH_printData("_FABA_ FLASH_MonitorSetting2Addr %x ", (WORD)(FLASH_MonitorSetting2Addr));
		FLASH_printData("_FABA_ FLASH_TimingModeAddr %x ", (WORD)(FLASH_TimingModeAddr));
		FLASH_printData("_FABA_ FLASH_FactorySettingAddr %x ", (WORD)(FLASH_FactorySettingAddr));
		FLASH_printData("_FABA_ FLASH_FreeBufferAddr %x ", (WORD)(FLASH_FreeBufferAddr));
		#if 1//((CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF)&& ENABLE_CABLE_5V_EDID)
		FLASH_printData( "_FABA_ FLASH_HDCP_EDIDAddr %x ", ( WORD )( FLASH_HDCP_EDIDAddr) );
		#endif
	}

}

//////////////////////////////////////////////////////////////////////////////
// <API><Description>: Check each buffer type correct or not,
//				  Erase the sector when type wrong
//////////////////////////////////////////////////////////////////////////////
void Flash_CheckBufferType(void)
{

	{ 
	    bFlashWriteFactory= TRUE;
		FlashSectorErase(  TRUE, FLASH_HDCP_EDIDAddr );
		FlashWriteByte( TRUE, FLASH_HDCP_EDIDAddr, FBufType_HDCP_EDID);
		bFlashWriteFactory = FALSE;
		FLASH_printMsg( "Flash_CheckBufferType SetHDCPType" );
		
B}ufType_FactorySetting !=FlashReadByte(FLASH_FactorySettingAddr))
	{	bFlashWriteFactory = TRUE; 
	#
	if 0
		 if(FlashReadByte(HDCPKEYSET_START)==0xFF&&FlashReadByte(HDCPKEYSET_START+1)==0xFF
		&&FlashReadByte(HDCPKEYSET_START+2 )= =0xF F& &FlashReadByte(HDCPKEYSET_STAR T +3 )= =0xFF
		        && FlashReadByte(HDCPKEYSET_START + 4) == 0xFF )	 		//charles test 1125    
	#        en dif    
			FlashSectorErase(TRUE, FLASH_FactorySettingAddr);
			FlashWriteByte(TRUE,FLASH_FactorySettingAddr, FBufType_FactorySetting);
		bFlashWriteFactory =  FALSE;
		FLASH_printMsg("Flash_CheckBufferType SetFactoryType");
	}
	if(FBufType_MonitorSetting!=FlashReadByte(FLASH_MonitorSettingAddr))
	{	FlashSectorErase(TRUE, F LA SH_MonitorSettingAddr);
		
	FlashWriteByte(TRUE,FLASH_MonitorSettingAddr, FBufType_MonitorSetting);
		FLASH_printMsg("Flas h_CheckBufferType SetMonitorType");
	}
	if(FBufType_MonitorSetting2!=FlashReadByte(FLASH_MonitorSetting2Addr))
	{	FlashSectorErase(TRUE, FL AS H_MonitorSetting2Addr);
		
	FlashWriteByte(TRUE,FLASH_MonitorSetting2Addr, FBufType_MonitorSetting2);
		FLASH_printMsg("Flas h_CheckBufferType SetMonitorSetting2Type");
	}
	if(FBufType_TimingMode!=FlashReadByte(FLASH_TimingModeAddr))
	{	FlashSectorErase(TRU E,  FLASH_TimingModeAddr);
		
	FlashWriteByte(TRUE,FLASH_TimingModeAddr, FBufType_TimingMode);
		FLASH_printMsg("Flas h_CheckBufferType SetTimingModeAddrType");
	}



//////////////////////////////////////////////////////////////////////////////
// <API><Description>: Clear all timing mode save in flash
//////////////////////////////////////////////////////////////////////////////
void Flash_ClearModeSet(void)
{
	FLASH_printMsg("_FCMS_ Flash_ClearModeSet");

	FlashWriteByte(TRUE, FLASH_TimingModeAddr,FBufType_TimingMode);
} 

//////////////////////////////////////////////////////////////////////////////
// <API><Description>:	Write Factory setting, HDCP Key, DDCA, DDCD key to free buffer,
//                  Exchange buffer address FLASH_FreeBufferAddr and FLASH_FactorySettingAddr
//////////////////////////////////////////////////////////////////////////////
BYTE Flash_GetKeyIndex(FLASH_KEY_TYPE ucType, Bool bWrite)
{
    BYTE ucIndex, ucStatus, ucSize=0;
	WORD wAddr;  
	
	{
	    ucSize = FACTORY_SECTOR_SIZE/FACTORY_SIZE;
		wAddr  = FACTORY_STATUS_ADDR ; 
		
	
	    eif(ucType == FLASH_KEY_GAMMA)
	{
	    ucSize = GAMMA_SECTOR_SIZE/GAMMA_SIZE;
		wAddr  = GAMMA_STATUS_ADDR ; 
		
	if    
	#if 1/HIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF) && ENABLE_CABLE_5V_EDID)
	    else if(ucType == FLASH_KEY_HDCP)
	{
	    ucSize = HDCPKEY_SECTOR_SIZE/HDCPKEY_SIZE;
		wAddr  = HDCPKEY_STATUS_ADDR ; 
		
	
	{
	    ucSize = DDCAKEY_SECTOR_SIZE/DDCAKEY_SIZE;
		wAddr  = DDCAKEY_STATUS_ADDR ; 
		
	else if(ucType == FLASH_KEY_DDCD)
	{
	    ucSize = DDCDKEY_SECTOR_SIZE/DDCDKEY_SIZE;
		wAddr  = DDCDKEY_STATUS_ADDR ; 
		
	lse if(ucType == FLASH_KEY_DDCH)
	 {
	    ucSize = DDCHKEY_SECTOR_SIZE/DDCHKEY_SIZE;
		wAddr  = DDCHKEY_STATUS_ADDR ; 
		
	e
	    else if(ucType == FLASH_KEY_DDCDP)
	{
	    ucSize = DDCDPKEY_SECTOR_SIZE/DDCDPKEY_SIZE;
		wAddr  = DDCDPKEY_STATUS_ADDR ; 
		
	if
	    for(ucIndex=0;ucIndex<ucSize;ucIndex++)
	{      
	    ucStatus = FlashReadByte(wAddr+ucIndex);
		if(bWrite)  
		{
		    if( ucStatus == FLASH_KEY_EMPTY || ucStatus == FLASH_KEY_WRITE)
			    break;
				
		else
		{
		    if( ucStatus == FLASH_KEY_VALID)
			    break;
				
		
	
	{
	    if(bWrite)
		    ucIndex = ucSize - 1;
			
		    ucIndex = 0;
			
	
	
//////////////////////////////////////////////////////////////////////////////
// <API><Description>:	Write Factory setting, HDCP Key, DDCA, DDCD key to free buffer,
//                  Exchange buffer address FLASH_FreeBufferAddr and FLASH_FactorySettingAddr
//////////////////////////////////////////////////////////////////////////////
void Flash_BackupFactorySetToBuffer(BYTE ucBufferType)
{
	BYTE xdata ucKeyIndex;
	WORD wAddr;


#if 1//((CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF) && ENABLE_CABLE_5V_EDID)
		 if( ucBufferType == FBufType_HDCP_EDID )
    {
	    ucKeyIndex = Flash_GetKeyIndex(FLASH_KEY_HDCP, FALSE);
		if(FlashReadByte(HDCPKEY_STATUS_ADDR+ucKeyIndex) == FLASH_KEY_VALID
		&& FlashReadByte(HDCPKEY_BUF_STATUS_ A DDR) == FLASH_KEY_EMPTY)
		        {
		    Flash_MoveTbl( FALSE, HDCPKEYSET_START + ucKeyIndex * HDCPKEY_SIZE, HDCPKEYSET_BUF_START, HDCPKEY_SIZE );
			hWriteByte(FALSE, HDCPKEY_BUF_STATUS_ADDR, FLASH_KEY_VALID);
			FLASH_printMsg("  _HDCP_ ");
			}
		
		if(FlashReadByte(DDCAKEY_STATUS_ADDR+ucKeyIndex) == FLASH_KEY_VALID
		&& FlashReadByte(DDCAKEY_BUF_STATUS_ A DDR) == FLASH_KEY_EMPTY)
		        {
		    Flash_MoveTbl( FALSE, DDCAKEYSET_START + ucKeyIndex * DDCAKEY_SIZE, DDCAKEYSET_BUF_START, DDCAKEY_SIZE );
			FlashWriteByte(FALSE, DDCAKEY_BUF_STATUS_ADDR, FLASH_KEY_VALID);
			FLASH_printMsg("  _DDCA_ ");
			
		
		if(FlashReadByte(DDCDKEY_STATUS_ADDR+ucKeyIndex) == FLASH_KEY_VALID
		&& FlashReadByte(DDCDKEY_BUF_STATUS_ A DDR) == FLASH_KEY_EMPTY)
		        {
		    Flash_MoveTbl( FALSE, DDCDKEYSET_START + ucKeyIndex * DDCDKEY_SIZE, DDCDKEYSET_BUF_START, DDCDKEY_SIZE );
			FlashWriteByte(FALSE, DDCDKEY_BUF_STATUS_ADDR, FLASH_KEY_VALID);
			FLASH_printMsg("  _DDCD_ ");
			
		
	      if(FlashReadByte(DDCHKEY_STATUS_ADDR+ucKeyIndex) == FLASH_KEY_VALID
		&& FlashReadByte(DDCHKEY_BUF_STATUS_ A DDR) == FLASH_KEY_EMPTY)
		        {
		    Flash_MoveTbl( FALSE, DDCHKEYSET_START + ucKeyIndex * DDCHKEY_SIZE, DDCHKEYSET_BUF_START, DDCHKEY_SIZE );
			FlashWriteByte(FALSE, DDCHKEY_BUF_STATUS_ADDR, FLASH_KEY_VALID);
			FLASH_printMsg("  _DDCH_ ");
			
		
		FlashEnableWP();
		FlashWriteByte( TRUE, FLASH_HDCP_EDIDAddr, 0x00 );
		wAddr = FLASH_FreeBufferAddr;
		FLASH_FreeBufferAddr = FLASH_HDCP_EDIDAddr;
		FLASH_HDCP_EDIDAddr = wAddr;
		
	f
		 if( ucBufferType == FBufType_FactorySetting )
    {	
 { ucKeyIndex = Flash_GetKeyIndex(FLASH_KEY_FACTORY, FALSE);
		(FlashReadByte(FACTORY_STATUS_ADDR+ucKeyIndex) == FLASH_KEY_VALID
			&& FlashReadByte(FACTORY_BUF_STATUS _ ADDR) == FLASH_KEY_EMPTY)
		        
			Flash_MoveTbl(FALSE, FACTORY_START+(WORD)ucKeyIndex*FACTORY_SIZE, FACTORY_BUF_START, FACTORY_SIZE);
			FlashWriteByte(FALSE, FACTORY_BUF_ S TATUS_ADDR, FLAS H _KEY_VALID);
			FLASH_printMsg( "  _FACT_ " );
		}
	    
			ucKeyIndex = Flash_GetKeyIndex(FLASH_KEY_GAMMA, FALSE);
		if(FlashReadByte(GAMMA_STATUS_ADDR+ucKeyIndex) == FLASH_KEY_VALID
			&& FlashReadByte(GAMMA_BUF_STATUS _ ADDR) == FLASH_KEY_EMPTY)
		        
			Flash_MoveTbl(FALSE, GAMMA_START+(WORD)ucKeyIndex*GAMMA_SIZE, GAMMA_BUF_START, GAMMA_SIZE);
			FlashWriteByte(FALSE, GAMMA_BUF_ S TATUS_ADDR, FLAS H _KEY_VALID);
			FLASH_printMsg("  _GAMMA_ ");
		}
		
		if(FlashReadByte(HDCPKEY_STATUS_ADDR+ucKeyIndex) == FLASH_KEY_VALID
			&& FlashReadByte(HDCPKEY_BUF_STATUS _ ADDR) == FLASH_KEY_EMPTY)
		        
			Flash_MoveTbl(FALSE, HDCPKEYSET_START+(WORD)ucKeyIndex*HDCPKEY_SIZE, HDCPKEYSET_BUF_START, HDCPKEY_SIZE);
			FlashWriteByte(FALSE, HDCPKEY_BUF_STA T US_ADDR, FLASH_K E Y_VALID);
			FLASH_printMsg("  _HDCP_ ");
		}
		
		if(FlashReadByte(DDCAKEY_STATUS_ADDR+ucKeyIndex) == FLASH_KEY_VALID
			&& FlashReadByte(DDCAKEY_BUF_STATUS _ ADDR) == FLASH_KEY_EMPTY)
		        
			Flash_MoveTbl(FALSE, DDCAKEYSET_START+(WORD)ucKeyIndex*DDCAKEY_SIZE, DDCAKEYSET_BUF_START, DDCAKEY_SIZE);
			FlashWriteByte(FALSE, DDCAKEY_BUF_STA T US_ADDR, FLASH_K E Y_VALID);
			FLASH_printMsg("  _DDCA_ ");
		}
		
		if(FlashReadByte(DDCDKEY_STATUS_ADDR+ucKeyIndex) == FLASH_KEY_VALID
			&& FlashReadByte(DDCDKEY_BUF_STATUS _ ADDR) == FLASH_KEY_EMPTY)
		        
			Flash_MoveTbl(FALSE, DDCDKEYSET_START+(WORD)ucKeyIndex*DDCDKEY_SIZE, DDCDKEYSET_BUF_START, DDCDKEY_SIZE);
			FlashWriteByte(FALSE, DDCDKEY_BUF_STA T US_ADDR, FLASH_K E Y_VALID);
			FLASH_printMsg("  _DDCD_ ");
		}
		
		{
			Flash_MoveTbl( FALSE, DDCHKEYSET_START, DDCHKEYSET_BUF_START, DDCHKEY_SIZE );
			FlashWriteByte( FALSE, DDCHKEY_BUF_STATUS_ADDR, FLASH_KEY_VALID );
			FLASH_printMsg( "  _DDCH_ " );
		}
	#endif
		#if 0//((CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF) && ENABLE_CABLE_5V_EDID)
		
		if(FlashReadByte(DDCDPKEY_STATUS_ADDR+ucKeyIndex) == FLASH_KEY_VALID
			&& FlashReadByte(DDCDPKEY_BUF_STATUS _ ADDR) == FLASH_KEY_EMPTY)
		        
			Flash_MoveTbl(FALSE, DDCDPKEYSET_START+(WORD)ucKeyIndex*DDCDPKEY_SIZE, DDCDPKEYSET_BUF_START, DDCDPKEY_SIZE);
			FlashWriteByte(FALSE, DDCDPKEY_BUF_STA T US_ADDR, FLASH_K E Y_VALID);
			FLASH_printMsg("  _DDCDP_ ");
		}
	#endif
			FlashWriteByte( FALSE, FLASH_FreeBufferAddr, FBufType_FactorySetting );
		FlashEnableWP();
		FlashWriteByte( TRUE, FLASH_FactorySettingAddr, 0x00 );
		wAddr = FLASH_FreeBufferAddr;
		FLASH_FreeBufferAddr = FLASH_FactorySettingAddr;
		FLASH_FactorySettingAddr = wAddr;
	}
	


//////////////////////////////////////////////////////////////////////////////
// <API><Description>:	Write HDCP ,DDCA or DDCD key to flash,
//					Need set correct type of key.
//                  wIndex from 0 to (key size / ucBufSize) or (key size / ucBufSize+1)
//                  The last write wLen = (key size % ucBufSize)
//                  Will backup to free buffer if write to index = (MAX_HDCPKEYSET_NUM-1)
// <Parameter>: 	- 	<Flow>	-	<Description>
// ---------------------------------------------------------------------------
//  ucType          -    In		-	FLASH_KEY_HDCP, FLASH_KEY_DDCA or FLASH_KEY_DDCD
//  wIndex			-    In		-	From 0 ~ x
//  ucBufSize	    -    In		-	Size of buf
//  *buf			-    In		-	point to the data of each set
//  wLen			-    In		-	Length of this time write buffer, wBufSize>=wLen
//////////////////////////////////////////////////////////////////////////////
void Flash_Write_Factory_KeySet(FLASH_KEY_TYPE ucType, WORD wIndex, WORD wBufSize, BYTE* buf, WORD wLen)
{
	BYTE xdata ucKeyIndex;
	WORD xdata wKEY_SIZE;
	WORD xdata wKEYSET_START;
	WORD xdata wKEYSET_BUF_START;
	WORD xdata wKEYSET_STATUS_ADDR;
	WORD xdata wKEYSET_BUF_STATUS_ADDR;

	
	{
		wKEY_SIZE				= FACTORY_SIZE;
		wKEYSET_START			= FACTORY_START + (WORD)ucKeyIndex*FACTORY_SIZE;
		wKEYSET_BUF_START		= FACTORY_BUF_START;  
		wKEYSET_STATUS_ADDR 	= FACTORY_STATUS_ADDR + ucKeyIndex;
		wKEYSET_BUF_STATUS_ADDR = FACTORY_BUF_STATUS_ADDR;
	}
#if 0    
		elseucType == FLASH_KEY_GAMMA)
	{
		wKEY_SIZE				= GAMMA_SIZE;
		wKEYSET_START			= GAMMA_START + (WORD)ucKeyIndex*GAMMA_SIZE;
		wKEYSET_BUF_START		= GAMMA_BUF_START;  
		wKEYSET_STATUS_ADDR 	= GAMMA_STATUS_ADDR + ucKeyIndex;
		wKEYSET_BUF_STATUS_ADDR = GAMMA_BUF_STATUS_ADDR;
	}
#endif  
	
		else if(ucType == FLASH_KEY_HDCP)
	{
		wKEY_SIZE				= HDCPKEY_SIZE;
		wKEYSET_START			= HDCPKEYSET_START + (WORD)ucKeyIndex*HDCPKEY_SIZE;
		wKEYSET_BUF_START		= HDCPKEYSET_BUF_START;  
		wKEYSET_STATUS_ADDR 	= HDCPKEY_STATUS_ADDR + ucKeyIndex;
		wKEYSET_BUF_STATUS_ADDR = HDCPKEY_BUF_STATUS_ADDR;
	}
	else if(ucType == FLASH_KEY_DDCA)
	{
		wKEY_SIZE				= DDCAKEY_SIZE;
		wKEYSET_START			= DDCAKEYSET_START + (WORD)ucKeyIndex*DDCAKEY_SIZE;
		wKEYSET_BUF_START		= DDCAKEYSET_BUF_START;  
		wKEYSET_STATUS_ADDR 	= DDCAKEY_STATUS_ADDR + ucKeyIndex;;
		wKEYSET_BUF_STATUS_ADDR = DDCAKEY_BUF_STATUS_ADDR;
	}
	else if(ucType == FLASH_KEY_DDCD)
	{
		wKEY_SIZE				= DDCDKEY_SIZE;
		wKEYSET_START			= DDCDKEYSET_START + (WORD)ucKeyIndex*DDCDKEY_SIZE;
		wKEYSET_BUF_START		= DDCDKEYSET_BUF_START;  
		wKEYSET_STATUS_ADDR 	= DDCDKEY_STATUS_ADDR + ucKeyIndex;;
		wKEYSET_BUF_STATUS_ADDR = DDCDKEY_BUF_STATUS_ADDR;
	}
    else if(ucType == FLASH_KEY_DDCH)
	{
	    wKEY_SIZE               = DDCHKEY_SIZE;
		wKEYSET_START           = DDCHKEYSET_START + (WORD)ucKeyIndex*DDCHKEY_SIZE;
		wKEYSET_BUF_START       = DDCHKEYSET_BUF_START;  
		wKEYSET_STATUS_ADDR     = DDCHKEY_STATUS_ADDR + ucKeyIndex;;
		wKEYSET_BUF_STATUS_ADDR = DDCHKEY_BUF_STATUS_ADDR;
		
	
		else if(ucType == FLASH_KEY_DDCDP)
	{
		wKEY_SIZE				= DDCDPKEY_SIZE;
		wKEYSET_START			= DDCDPKEYSET_START + (WORD)ucKeyIndex*DDCDPKEY_SIZE;
		wKEYSET_BUF_START		= DDCDPKEYSET_BUF_START;  
		wKEYSET_STATUS_ADDR 	= DDCDPKEY_STATUS_ADDR + ucKeyIndex;;
		wKEYSET_BUF_STATUS_ADDR = DDCDPKEY_BUF_STATUS_ADDR;
	}
#endif
		else
		return;


	{
		if( wIndex == 0x00 )
		{
			// FLASH_printData("  _FWFK_StatusAddr [%x] ",wKEYSET_STATUS_ADDR);
			 FlashWriteByte(TRUE, wKEYSET_STATUS_ADDR, FLASH_KEY_WRITE);
           g_wKEYSET_START         = wKEYSET_START;
			
		Flash_WriteTbl( TRUE, wKEYSET_START + wIndex * wBufSize, buf, wLen );
		if(( wIndex * wBufSize + wLen ) >= wKEY_SIZE ) // check write end
		{
			FlashWriteByte( TRUE, wKEYSET_STATUS_ADDR, FLASH_KEY_VALID );
			if(ucKeyIndex>0)
				FlashWriteBy t e(TRUE, wKEYSET_STATUS_ADDR-1, FLASH_KEY_INVALID);
		}  
	}
	else
	{
		if( wIndex == 0x00 )
		{
			FlashSectorErase(TRUE, FLASH_FreeBufferAddr);
			FlashWriteByte(TRUE, wKEYSET_BUF_STATUS_ADDR, FLASH_KEY_WRITE);
            g_wKEYSET_START         = 0xF000;
			

		if(( wIndex * wBufSize + wLen ) >= wKEY_SIZE ) // check write end
		{
			FlashWriteByte( TRUE, wKEYSET_BUF_STATUS_ADDR, FLASH_KEY_VALID );
			//FLASH_printData("  _FWFK_buffer write End [%x] ",ucType);
			#if 1//((CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF) && ENABLE_CABLE_5V_EDID)
           		 if( ucType >= FLASH_KEY_HDCP && ucType <= FLASH_KEY_DDCH )
	 		Flash_BackupFactorySetToBuffer( FBufType_HDCP_EDID );
	
			#endif
				Flash_BackupFactorySetToBuffer(FBufType_FactorySetting);
				FlashSectorErase( TRUE, FLASH_FreeBufferAddr );
			if 1//((CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF) && ENABLE_CABLE_5V_EDID)
            		if( ucType >= FLASH_KEY_HDCP && ucType <= FLASH_KEY_DDCH )
				Flash_BackupFactorySetToBuffer( FBufType_HDCP_EDID );
	
			#endif
				Flash_BackupFactorySetToBuffer(FBufType_FactorySetting);
				FlashSectorErase( TRUE, FLASH_FreeBufferAddr );    //charles test
		}

	bFlashWriteFactory = FALSE;
}


//////////////////////////////////////////////////////////////////////////////
// <API><Description>:	Read HDCP ,DDCA or DDCD key each wLen from flash,
//					Need set correct ucType.
//                  wIndex from 0 to (key size / wBufSize) or (key size / wBufSize+1)
//                  The last read wLen = (key size % wBufSize)
// <Returns> : return TRUE when found key ident and CheckSum
// <Parameter>: 	- 	<Flow>	-	<Description>
// ---------------------------------------------------------------------------
//  ucType          -    In		-	FLASH_KEY_HDCP, FLASH_KEY_DDCA or FLASH_KEY_DDCD
//  wIndex			-    In		-	From 0 ~ x
//  wBufSize	    -    In		-	Size of buf
//  *buf			-    In		-	point to the data of each set
//  wLen			-    In		-	Length of this time write buffer, wBufSize>=wLen
//////////////////////////////////////////////////////////////////////////////
Bool Flash_Read_Factory_KeySet(FLASH_KEY_TYPE ucType, Bool bReadVaild, WORD wIndex, WORD wBufSize, BYTE* buf, WORD wLen)		//110311 Modify
{
	BYTE xdata ucKeyIndex;
	WORD xdata wKEY_SIZE;
	WORD xdata wKEYSET_START;
	WORD xdata wKEYSET_STATUS_ADDR;

		ucKeyIndex = Flash_GetKeyIndex(ucType, FALSE);
	else
		ucKeyIndex = Flash_GetKeyIndex(ucType, TRUE);

	{
		wKEY_SIZE			= FACTORY_SIZE;
		wKEYSET_START		= FACTORY_START + (WORD)ucKeyIndex*FACTORY_SIZE;
		wKEYSET_STATUS_ADDR = FACTORY_STATUS_ADDR + ucKey I ndex;
	}
#if 0    
		else ucType == FLASH_KEY_GAMMA )
	{
		wKEY_SIZE			= GAMMA_SIZE;
		wKEYSET_START		= GAMMA_START + (WORD)ucKeyIndex*GAMMA_SIZE;
		wKEYSET_STATUS_ADDR = GAMMA_STATUS_ADDR + ucKey I ndex;
	}
#endif    
	#if 1/HIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF) && ENABLE_CABLE_5V_EDID)
		else if(ucType == FLASH_KEY_HDCP)
	{
		wKEY_SIZE			= HDCPKEY_SIZE;
		wKEYSET_START		= HDCPKEYSET_START + (WORD)ucKeyIndex*HDCPKEY_SIZE;
		wKEYSET_STATUS_ADDR = HDCPKEY_STATUS_ADDR + ucKeyInd e x;
	}
	else if( ucType == FLASH_KEY_DDCA )
	{
		wKEY_SIZE			= DDCAKEY_SIZE;
		wKEYSET_START		= DDCAKEYSET_START + (WORD)ucKeyIndex*DDCAKEY_SIZE;;
		wKEYSET_STATUS_ADDR = DDCAKEY_STATUS_ADDR + ucKeyInd e x;
	}
	else if( ucType == FLASH_KEY_DDCD )
	{
		wKEY_SIZE		= DDCDKEY_SIZE;
		wKEYSET_START		= DDCDKEYSET_START + (WORD)ucKeyIndex*DDCDKEY_SIZE;;
		wKEYSET_STATUS_ADDR = DDCDKEY_STATUS_ADDR + ucKeyInd e x;
	}
	else if( ucType == FLASH_KEY_DDCH )
	{
		wKEY_SIZE		= DDCHKEY_SIZE;
		wKEYSET_START		= DDCHKEYSET_START + (WORD)ucKeyIndex*DDCHKEY_SIZE;;
		wKEYSET_STATUS_ADDR = DDCHKEY_STATUS_ADDR + ucKeyInd e x;
	}
#else
		else if( ucType == FLASH_KEY_DDCDP )
	{
		wKEY_SIZE		= DDCDPKEY_SIZE;
		wKEYSET_START		= DDCDPKEYSET_START + (WORD)ucKeyIndex*DDCDPKEY_SIZE;;
		wKEYSET_STATUS_ADDR = DDCDPKEY_STATUS_ADDR + ucKeyInd e x;
	}
#endif
		else
		return FALSE;

	{
		//FLASH_printData("  Flash_ReadDDCAKeySet Succ [%x]",wKEYSET_START+i*wKEY_SIZE+1+wIndex*wBufSize);
		if(bReadVaild && FlashReadByte(wKEYSET_STATUS_ADDR) != FLASH_KEY_VALID)
			return FALSE;
		else
			Flash_ReadTbl(wKEYSET_START+wIndex*wBufSize, buf, wLen);
		    return TRUE;
	}
	else
	{
		// FLASH_printData("  Flash_ReadKeySet Fail ucType[%x h]",ucType);
		return FALSE;
	}
}




//////////////////////////////////////////////////////////////////////////////
// <API><Description>:	Write Factory setting to flash,
//					It will exchange buffer when not found empty space
//////////////////////////////////////////////////////////////////////////////
void Flash_WriteFactorySet(BYTE* pbuf,BYTE ucLen)
{ 
    Flash_Write_Factory_KeySet(FLASH_KEY_FACTORY, 0, FACTORY_SIZE, pbuf, ucLen);
	
//////////////////////////////////////////////////////////////////////////////
// <API><Description>:	Read latest factory setting struct from flash.
// <Returns> : return TRUE when found factory setting
//////////////////////////////////////////////////////////////////////////////
Bool Flash_ReadFactorySet(BYTE* pbuf,BYTE ucLen)
{ 
    return Flash_Read_Factory_KeySet(FLASH_KEY_FACTORY, TRUE, 0, FACTORY_SIZE, pbuf, ucLen);	//110311 Modify
	
//////////////////////////////////////////////////////////////////////////////
// <API><Description>:	Write Monitor setting struct to flash,
//					It will exchange buffer when buffer full
//////////////////////////////////////////////////////////////////////////////
void Flash_WriteMonitorSet(BYTE* buf,BYTE len)
{ 
	WORD wAddr;
	WORD i;

	if(i != IDENT_NOT_FOUND)// Found the empty index  
	{
	 	//MonitorSetting.Ident= FLASH_IDENTDATA;
		//MonitorSetting.CheckSum	= FLASH_CHECKSUM;
	   wAddr = MONITORSET_START + i*MONITORSET_SIZE;
		WriteTbl(TRUE, wAddr, (BYTE* ) buf, len);
		FLASH_printData("_FWMS_0 wAddr %x",wAddr);
        if(i>0) 
		{  
		    wAddr = MONITORSET_START + (i-1)*MONITORSET_SIZE;
			FlashWriteByte(TRUE, wAddr,FL A SH _ IDENTDATA_CLEAR);
			 
		
	else
	{
	ashSectorErase(TRUE, FLASH_FreeBufferAddr);
		Flash_WriteTbl(TRUE, MONITORSET_BUF_START, (BYTE*)buf, len);
		FLASH_printData("_FWMS_1 wAddr %x",MONITORSET_BUF_START);
		FLASH_printData("FLASH_FreeBufferAd dr11 wAddr %x",FLASH_FreeBufferAddr);
		FlashWriteByte(TRUE, FLASH_FreeBufferAddr,FBufType _MonitorSetting);
		FlashWriteByte(TRUE, FLASH_MonitorSettingA ddr,0x00);
		wAddr = FLASH_FreeBufferAddr; 
		FLASH_FreeBufferAddr = FLASH_MonitorSettingAddr;
		FLASH_MonitorSettingAddr = wAddr;
    }
	
//////////////////////////////////////////////////////////////////////////////
// <API><Description>:	Read latest Monitor setting struct from flash.
//					1.Got monitor setting index by check flash identity
//					2.If not found read CheckSum to got correct one
//					3.read the Monitor setting struct
// <Returns> : return TRUE when found MonitorSetting
//////////////////////////////////////////////////////////////////////////////
Bool Flash_ReadMonitorSet(BYTE* buf,BYTE len)
{ 
    WORD i;
	
	if(i != IDENT_NOT_FOUND)  
	{
		Flash_ReadTbl(MONITORSET_START + i*MONITORSET_SIZE, buf, len);
		FLASH_printData("_FRMS_ wAddr %x", M ONITORSET_START + i*MONITORSET_SIZE);
	    return TRUE;   
		
	else
	{
	    i = Flash_SearchIdentChecksum(MONITORSET_START, (MAX_MONITORSET_NUM-1), 0, MONITORSET_SIZE, FLASH_IDENTDATA_CLEAR, FLASH_CHECKSUM);
		if(i != IDENT_NOT_FOUND)  
		{
			Flash_ReadTbl(MONITORSET_START + i*MONITORSET_SIZE, buf, len);
		 //   FLASH_printMsg("_FRMS_ Only C h ecksum Correct! ");
			/	FLASH_printData("_FRMS_ wAddr %x",MONITORSET_START + i*MONITORSET_SIZE);
			    return TRUE;
			
		else
		    return FALSE;
			
	


//////////////////////////////////////////////////////////////////////////////
// <API><Description>:	Flash_WriteMonitorSet2 isues to save MonitorSetting2
//					It will exchange buffer when buffer full
//////////////////////////////////////////////////////////////////////////////
void Flash_WriteMonitorSet2(BYTE* buf,BYTE len)
{ 
	WORD wAddr;
	WORD i;

	if(i != IDENT_NOT_FOUND)  
	{
	ddr = MONITORSET2_START + i*MONITORSET2_SIZE;
		Flash_WriteTbl(TRUE, wAddr, ( B YTE*)buf, len);
		//FLASH_printData("_FWMS2_ wAddr %x",wAddr);
    }
	else
	{
	ashSectorErase(TRUE, FLASH_FreeBufferAddr);
		Flash_WriteTbl(TRUE, MONITORSET2_BUF_START, (BYTE*)buf, len);
		//FLASH_printData("_FWMS2_ wAddr %x",MONITORSET2_BUF_START);
		FlashWriteByte(TRUE, FLASH_FreeBufferAddr,FBufType_MonitorSetting2);
		FlashWriteByte(TRUE, FLASH_MonitorSetting2 Addr,0x00);
		wAddr = FLASH_FreeBufferAddr; 
		FLASH_FreeBufferAddr = FLASH_MonitorSetting2Addr;
		FLASH_MonitorSetting2Addr = wAddr;
    }
	

//////////////////////////////////////////////////////////////////////////////
// <API><Description>:	Read MonitorSetting2 struct from flash.
//					1.Got monitor setting index by check flash identity
// <Returns> : return TRUE when found MonitorSetting2
//////////////////////////////////////////////////////////////////////////////
Bool Flash_ReadMonitorSet2(BYTE* buf,BYTE len)
{ 
    Bool bFound=FALSE;
	D i;  

	if(i != IDENT_NOT_FOUND)  
	{
		Flash_ReadTbl(MONITORSET2_START + i*MONITORSET2_SIZE, buf, len);
		//FLASH_printData("_FRMS2_ wAddr %x " ,MONITORSET2_START + i*MONITORSET2_SIZE);
	    return TRUE;
		
	else
	{
	    FLASH_printMsg("  Flash_ReadMonitorSet2 Fail");
		return FALSE;
		
	


//////////////////////////////////////////////////////////////////////////////
// <API><Description>:	Check exit timing mode number and compare to MAX_MODESET_NUM.
// <Returns> : return TRUE when saved timing mode size equal to MAX_MODESET_NUM
//////////////////////////////////////////////////////////////////////////////
Bool Flash_CheckModeFull(void)
{
    BYTE i,wExitModeCount=0;
	//check  buffer full  
	(i=0;i < MAX_MODESET_NUM; i++)
	{   
		if(FlashReadByte(MODESET_START+i*MODESET_SIZE)==FLASH_IDENTDATA && FlashReadByte(MODESET_START+i*MODESET_SIZE+MODESET_SIZE-1)==FLASH_CHECKSUM)
            wExitModeCount++;                
			
	if(wExitModeCount == MAX_MODESET_NUM)
	    return TRUE;
		
	    return FALSE;
		
//////////////////////////////////////////////////////////////////////////////
// <API><Description>:	Clear all user mode ident.
//
//////////////////////////////////////////////////////////////////////////////
void Flash_ClearUserModeSpace(void)
{
    BYTE i,ucIdent=0;
	//check  buffer   full
	(i=0;i < MAX_MODESET_NUM; i++)
	{   
	    ucIdent = FlashReadByte(MODESET_START+i*MODESET_SIZE);
		ucIdent == FLASH_IDENTDATA)    
        {
		lashReadByte(MODESET_START+i*MODESET_SIZE+1)&0x80)==0x80)
                FlashWriteByte(TRU E ,   MODESET_STAR T +i * MODES ET _SIZE, 0x00); // Clear Identdata.
				    
		
	SH_printMsg("Flash_ClearUserModeSpace");
}

//////////////////////////////////////////////////////////////////////////////
// <API><Description>:	Write timing mode with index to flash
//					1.Search the timing mode from timing buffer
//					2.Clear the timing ident
//					3.Find empty timing mode bufer
//					4.Exchange buffer if FLASH_TimingModeAddr buffer full
//					5.Write timing struct to empty buffer
// <Parameter>: 	- 	<Flow>	-	<Description>
// ---------------------------------------------------------------------------
//  index			-    In		-	timing index, UserMode need |_BIT7 in index
//  *buf			-    In		-	point to the address of timing struct
//////////////////////////////////////////////////////////////////////////////
void Flash_WriteModeSet(BYTE index,BYTE *buf)
{ 
	WORD i=0, j=0;
	WORD w A ddr;  
	xdata ModeSettingType modeSetting;

    // find orginal mode index in flash
	(i=0;i < MAX_MODESET_NUM; i++)
	{   
		if(FlashReadByte(MODESET_START+i*MODESET_SIZE)==FLASH_IDENTDATA && FlashReadByte(MODESET_START+i*MODESET_SIZE+MODESET_SIZE-1)==FLASH_CHECKSUM)
		{                
			if(FlashReadByte(MODESET_START+i*MODESET_SIZE+1)==index)
			{        
				FlashWriteByte(TRUE, MODESET_START+i*MODESET_SIZE, 0x00); // Clear Identdata.
				FLASH_printData("_FWMS_ Clear inde x   % x",i);
			} 
		}
	}

	i = Flash_SearchIdentChecksum(MODESET_START, 0, (MAX_MODESET_NUM-1), MODESET_SIZE, FLASH_EMPTYDATA, FLASH_EMPTYDATA);
	if(i != IDENT_NOT_FOUND)  
	{
	    FLASH_printData("_FWMS_ write to empty Addr %x",MODESET_START+i*MODESET_SIZE);
		Flash_WriteTbl(TRUE, MODESET_START+i*MODESET_SIZ E, buf, MODES E T _ SIZE);
		    
	else
	{
	    if(Flash_CheckModeFull())
		    Flash_ClearUserModeSpace();
			
		0;i < MAX_MODESET_NUM; i++)
		{   
			if(FlashReadByte(MODESET_START+i*MODESET_SIZE)==FLASH_IDENTDATA  && FlashReadByte(MODESET_START+i*MODESET_SIZE+MODESET_SIZE-1)==FLASH_CHECKSUM)
			{                
				Flash_ReadTbl(MODESET_START+i*MODESET_SIZE, (BYTE*)&modeSetting, MODESET_SIZE);
				Flash_WriteTbl(TRUE, MODESE T _ B UF_START+j*MODESET_SIZE, (BYTE*)&modeSetting, MODESET_SIZE);
				j++;    
			}
		}
        if(j < (MAX_MODESET_NUM-1))
		{  
		    FLASH_printData("_FWMS_ write to empty Addr %x",MODESET_BUF_START+j*MODESET_SIZE);
			Flash_WriteTbl(TRUE, MODESET_BUF_START+j*MODESET _SIZE, buf, MODES E T _ SIZE);
			    
		
		riteByte(TRUE, FLASH_FreeBufferAddr,FBufType_TimingMode);
		FlashWriteByte(TRUE, FLASH_TimingModeAddr, 0x00);
		wAddr = FLASH_FreeBufferAddr; 
		FLASH_FreeBufferAddr = FLASH_TimingModeAddr;
		FLASH_TimingModeAddr = wAddr;
		//i=j;//Write empty one index

		FLASH_printData("_FWMS_ Buffer exchange FreeAddr %x ",(W ORD)(FLASH_FreeBufferAddr>> 8) );
    }   
	


//////////////////////////////////////////////////////////////////////////////
// <API><Description>:	Read timing mode with index from flash
//					1.Search the timing mode from timing buffer by compare FLASH_IDENTDATA&TimingIndex
//					2.No update & return when not found
//					3.Read timing mode from buffer
//					4.upper level function check timing mode FLASH_IDENTDATA to makesure
// <Returns> : return TRUE when found the timing mode index
// <Parameter>: 	- 	<Flow>	-	<Description>
// ---------------------------------------------------------------------------
//  index			-    In		-	timing index, UserMode need |_BIT7 in index
//  *buf			-    In		-	point to the address of timing mode struct
//////////////////////////////////////////////////////////////////////////////
Bool Flash_ReadModeSet(BYTE index,BYTE *buf)
{ 
    WORD i;
	
	{   
	    if(FlashReadByte(MODESET_START+i*MODESET_SIZE)==FLASH_IDENTDATA
		    && FlashReadByte(MODESET_S T A R T+i*MODESET_S IZ E+MODESET_SIZE-1)==FLASH_CHECKSUM
		        && FlashReadByte(MODESET_START + i * MODESET_SIZE + 1)==index)    
		    {        
		    break;
			
		
	
	{
	    FLASH_printMsg("_FRMS_ RModeSet Not Found");
		return FALSE;
		
		FLASH_printData("_FRMS_ RModeSet=%x",i);
	FLASH_printData("_FRMS_ ModeR=%x",(MO DESET_START+i*MODESET_SIZE)&0xFFFF);
	Flash_ReadTbl(MODESET_START+i*MODE SET_SIZE, buf,   M O DESET_SIZE);  
    return TRUE;    
	

#endif//USEFLASH



