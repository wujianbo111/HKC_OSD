
// 111214
mcuSetSpiSpeed()
{
	#if CHIP_ID==CHIP_TSUMY
	msWriteByteMask(REG_08E0, ucIndex << 4,  _BIT7 | _BIT6 | _BIT5 | _BIT4);
	#else
	msWriteByteMask(REG_08E0, ucIndex << 4, _BIT5 | _BIT4);
	#endif
}

msPM_PowerUpMacro()
{
	#if ( CHIP_ID == CHIP_TSUMB )
	msWriteByteMask(REG_1E25, 0x00, BIT2);              //[2]ckg_mclk_gate
	msWriteByteMask(REG_1E28, 0x00, BIT4 | BIT0); //[0]CLK_MEMPLL_gate [4]clk_led216_gate
	#endif
}

msPM_PowerDownMacro()
{
	#if ( CHIP_ID == CHIP_TSUMB )
	msWriteByteMask(REG_1E25, BIT2, BIT2);              //[2]ckg_mclk_gate
	msWriteByteMask(REG_1E28, BIT4 | BIT0, BIT4 | BIT0); //[0]CLK_MEMPLL_gate [4]clk_led216_gate
	#endif
}


msAudioLineout_SourceSel()
{
	#if ( CHIP_ID == CHIP_TSUMB )
	if( src == E_LINEOUT_FROM_LINEIN1 )
	{
		msWriteByteMask( REG_05E7, 0, BIT0 | BIT2 ); //line in source, earphone out
	}
	else
	{
		msWriteByteMask( REG_05E7, BIT0 | BIT2, BIT0 | BIT1 | BIT2 ); //HDMI source, earphone out
		msWriteByteMask( REG_1B07, 0, BIT0 | BIT1 );
	}
	#endif
}

mStar_Init()
{
	#if CHIP_ID==CHIP_TSUMB
	msWriteByte(REG_1EF0, 0x3E);
	msWriteByte(REG_1EF1, 0xC8);
	msWriteByte(REG_1EF6, 0x01);
	msWriteByte(REG_1EF8, 0x01);
	#endif
}

// AE
//    msWriteByte( REG_05E5, 0xAA ); // [7:6]:256Fs, [5]:MCLK output, [3]:I2S encoder clock, [1]:S/PDIF encoder clock
// MINE
//     msWriteByte( REG_05E5, 0x6A ); // [7:6]:128Fs, [5]:MCLK output, [3]:I2S encoder clock, [1]:S/PDIF encoder clock

