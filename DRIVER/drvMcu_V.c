
///////////////////////////////////////
// DRVMCU_V VERSION: V02
////////////////////////////////////////
#include "global.h"

void Init_WDT( BYTE bEnable )
{
	msWriteByteMask( REG_3C66, BIT2, BIT2); //clear watchdog reset flag
	msWriteByteMask( REG_3C66, 0x00, BIT2);
	if( bEnable )
	{
		#if( ENABLE_WATCH_DOG )
		// initialize the watchdog timer reset interval
		{
			WORD wdt_sel_high;
			wdt_sel_high = 65536 - ( CRYSTAL_CLOCK / 65536 ) * WATCH_DOG_RESET_TIME;
			msWriteByte( REG_3C62, LOBYTE( wdt_sel_high ) );
			msWriteByte( REG_3C63, HIBYTE( wdt_sel_high ) );
			msWriteBit(REG_2B00, FALSE, _BIT1);//MASK DISABLE // Jonson 20110713
		}
		#endif  // end of #if( ENABLE_WATCH_DOG )
		msWriteByte( REG_3C60, 0xAA );
		msWriteByte( REG_3C61, 0x55 );
	}
	else
	{
		msWriteByte( REG_3C60, 0x55 );
		msWriteByte( REG_3C61, 0xAA );
		msWriteBit(REG_2B00, TRUE, _BIT1);//MASK ENABLE // Jonson 20110713
	}
}

//-------------------------------------------------------------------------------------------------
// spi clock
// SPI clock setting
//
// reg_reserved0[5:0]
//
// h0027    h0026   31  0   reg_reserved0   "Reserved.reg_reserved0[5:0]: for spi clock selectionreg_reserved0[8]: for spi new cycle"
//
//
// reg_ckg_spi[6]
//  0: Crystal clock
//  1: PLL clock
//
// reg_ckg_spi[4:2], clock selection
//
#if ENABLE_DEBUG
DWORD code g_mcuSpiFreqTable[] =
{
	CLOCK_4MHZ,       // 0
	CLOCK_27MHZ,      // 1
	CLOCK_36MHZ,      // 2
	CLOCK_43MHZ,      // 3
	CLOCK_54MHZ,      // 4
	CLOCK_86MHZ,      // 5
	CRYSTAL_CLOCK,    // 6
};
#endif

// ucIndex ( PLL clock selection, whenever change, please make sure reg_ckg_spi[5]=0;)
//          1: 36   MHz pass
//          2: 43   MHz pass
//          3: 54   MHz, don't use, reserved for future
//          3: 86   MHz, don't use, reserved for future
//          4: Crystal clock
void mcuSetSpiSpeed( BYTE ucIndex )
{
	if( ucIndex == IDX_SPI_CLK_XTAL)
	{
		msWriteByteMask( REG_08E0, 0, _BIT2 );
	}
	else
	{
		msWriteByteMask( REG_08E0, ucIndex << 3, _BIT5 | _BIT4 | _BIT3);
		msWriteByteMask( REG_08E0, _BIT2, _BIT2 );
	}
}

/*
SPI model select.
0x0: Normal mode, (SPI command is 0x03)
0x1: Enable fast read mode, (SPI command is 0x0B)
0x2: Enable address single & data dual mode, (SPI command is 0x3B)
0x3: Enable address dual & data dual mode, (SPI command is 0xBB)
0xa: Enable address single & data quad mode, (SPI command is 0x6B) (Reserved)
0xb: Enable address quad & data quad mode, (SPI command is 0xEB)
(Reserved
*/
void mcuSetSpiMode( BYTE ucMode )
{
	BYTE ucValue;
	switch( ucMode )
	{
		case SPI_MODE_FR:
			ucValue = 0x01;
			break;
		case SPI_MODE_SADD:
			ucValue = 0x02;
			break;
		case SPI_MODE_DADD:
			ucValue = 0x03;
			break;
		case SPI_MODE_SAQD:
			ucValue = 0x0A;
			msWriteByteMask(REG_0223, _BIT6, _BIT6);
			break;
		case SPI_MODE_QAQD:
			ucValue = 0x0B;
			msWriteByteMask( REG_0223, _BIT6, _BIT6 );
			break;
		case SPI_MODE_NORMAL:
		default:
			ucValue = 0x00;
	}
	msWriteByte( REG_08E4, ucValue );
	#if DEBUG_PRINTDATA
	printData( "SPI Mode = %d ", ucMode );
	#endif
}

DWORD code g_mcuPLLFreqTable[] =
{
	CLOCK_4MHZ,            // 0
	CLOCK_0MHZ,            // 1
	CLOCK_0MHZ,            // 2,
	CLOCK_108MHZ,          // 3,
	CLOCK_86MHZ,           // 4,
	CLOCK_54MHZ,           // 5,   mem_clock
	CLOCK_27MHZ,           // 6,   mem_clock/2
	CLOCK_XTAL,            // 7
};
void mcuSetMcuSpeed( BYTE ucSpeedIdx )
{
	DWORD u32Freq;
	WORD u16Divider0;
	WORD u16Divider1;
	u32Freq = g_mcuPLLFreqTable[ucSpeedIdx];
	u16Divider0 = 1024 - (( _SMOD * u32Freq + u32Freq ) / SERIAL_BAUD_RATE ) / 64;
	u16Divider1 = 1024 - (( u32Freq ) / SERIAL_BAUD_RATE ) / 32;
	if ( ucSpeedIdx == IDX_MCU_CLK_XTAL )
		msWriteByteMask( REG_PM_BC, 0, _BIT0 );
	else
	{
		msWriteByteMask( REG_PM_BB, ucSpeedIdx, ( _BIT2 | _BIT1 | _BIT0 ) );
		msWriteByteMask( REG_PM_BC, _BIT0, _BIT0 );
	}
	// Scaler WDT
	msWriteByte(SC0_00, 0x00);
	msWriteByte(SC0_B2, (u32Freq * 4) / CRYSTAL_CLOCK);
	#if ENABLE_DEBUG
	ES = 0;
	IEN2 &= ~ES1;
	S0RELH = HIBYTE( u16Divider0 );
	S0RELL = LOBYTE( u16Divider0 );
	// ENABLE_UART1
	S1RELH = HIBYTE( u16Divider1 );
	S1RELL = LOBYTE( u16Divider1 );
	#if ENABLE_UART1
	IEN2 |= ES1;
	#else
	ES = 1;
	#endif
	printData( "MCU freq = %d MHz ", u32Freq / 1000 / 1000 );
	#endif
	#if !EXT_TIMER0_1MS
	// timer
	TR0 = 0;
	ET0 = 0;
	u32Freq = u32Freq / 1000;
	u16Divider0 = ( 65536 - ( u32Freq * INT_PERIOD + 6 ) / 12 );
	TH0 = g_ucTimer0_TH0 = HIBYTE( u16Divider0 );
	TL0 = g_ucTimer0_TL0 = LOBYTE( u16Divider0 );
	TR0 = 1;
	ET0 = 1;
	#endif
}
//=========================================================
void mcuSetSystemSpeed(BYTE u8Mode)
{
	if (g_u8SystemSpeedMode != u8Mode)
	{
		//MCU speed >= SPI speed
		switch(u8Mode)
		{
			case SPEED_4MHZ_MODE:
				mcuSetSpiSpeed(IDX_SPI_CLK_4MHZ); //spi speed down 1st
				mcuSetSpiMode( SPI_MODE_NORMAL );
				mcuSetMcuSpeed(IDX_MCU_CLK_4MHZ);
				g_bMcuPMClock = 1; // 120618 coding addition
				break;
			case SPEED_XTAL_MODE:
				if (g_u8SystemSpeedMode > SPEED_XTAL_MODE)
				{
					mcuSetSpiSpeed( IDX_SPI_CLK_XTAL );
					mcuSetSpiMode( SPI_MODE_NORMAL );
					mcuSetMcuSpeed( IDX_MCU_CLK_XTAL );
				}
				else
				{
					mcuSetMcuSpeed( IDX_MCU_CLK_XTAL );
					mcuSetSpiMode( SPI_MODE_NORMAL );
					mcuSetSpiSpeed( IDX_SPI_CLK_XTAL );
				}
				g_bMcuPMClock = 1; // 120618 coding addition
				break;
			default: //normal
				mcuSetSpiMode( SPI_MODE );
				msWriteByte( REG_1EDC, 0x00 );
				msWriteByte( REG_1ED1, BIT2 );
				msWriteByte( REG_1ED2, 0x0F );
				ForceDelay1ms(10);
				mcuSetMcuSpeed( MCU_SPEED_INDEX );
				mcuSetSpiSpeed( SPI_SPEED_INDEX );
				g_bMcuPMClock = 0; // 120618 coding addition
				break;
		}
		g_u8SystemSpeedMode = u8Mode;
		//SetForceDelayLoop();
	}
}
