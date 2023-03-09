#define _MCU_C_

#include "board.h"
#include "types.h"
#include "misc.h"
#include "debug.h"
#include "ms_rwreg.h"
#include "ms_reg.h"
#include "Reg52.h"
#if ENABLE_HDCP
#include "msHDCP.h"
#endif
#include "global.h"
#include "power.h"
#include "mcu.h"
#include "GPIO_DEF.h"
//////////////////////////////////
#include "drvMcu.h"
/////////////////////////////////
#if ENABLE_UART1
#include "UartControl.h"
#endif


//extern xdata BYTE xfr_regs[256];
void Init_MCU(void)
{
	EA = 0;
	#if( ENABLE_WATCH_DOG )	//130716 xiandi follow demo code
	Init_WDT( _ENABLE );
	#else
	Init_WDT( _DISABLE );
	#endif  // end of #if( ENABLE_WATCH_DOG )
	Init_IOPorts();
	Init_ExternalInterrupt();
	Init_Timer();
	Init_SerialPort();
	EA = 1;
	#if ENABLE_DEBUG && ((CHIP_ID==CHIP_TSUMC)||(CHIP_ID==CHIP_TSUMD)||(CHIP_ID == CHIP_TSUM9)|| (CHIP_ID == CHIP_TSUMF))
	mcuSetUartMux(DFT_MUX_Uart0, DFT_MUX_Uart1);
	#endif
	mcuSetSystemSpeed(SPEED_XTAL_MODE);
	#if Enable_Cache
	CACHE_ENABLE();
	#else
	CACHE_DISABLE();
	#endif
	//MCU_EnableCache(TRUE);
	//g_u8SystemSpeedMode=SPEED_XTAL_MODE;
}
#if 0//( ENABLE_WATCH_DOG )	//130702 xiandi
void ClearWDT( void )
{
	msWriteBit( REG_3C66, 1, _BIT1 );
}
#endif  // end of #if( ENABLE_WATCH_DOG )

// Initialize I/O setting
void Init_IOPorts(void)
{
	hw_SetDDC_WP();
	hw_SetFlashWP();
	hw_ClrBlacklit();
	hw_ClrPanel();
	Init_hwDDC_WP_Pin();
	Init_hwFlash_WP_Pin();
	Init_hwBlacklit_Pin();
	Init_hwPanel_Pin();
	Init_PowerKey();
	Init_hwDSUBCable_Pin();
	Init_hwDVICable_Pin();
	#if (CHIP_ID == CHIP_TSUM9/*|| CHIP_ID == CHIP_TSUMF*/)
	DVI5V_GPIO_Sel();
	Init_PowerKey();
	#endif
	#if HDMI_PRETEST
	Init_hwCEC_Pin();
	#endif
	#if ENABLE_HDMI
	Init_hwHDMICable_Pin();
	#endif
	#if ENABLE_DP_INPUT
	Init_hwDPCable_Pin() ;
	#endif
	#if !USEFLASH
	Set_EEPROM_WP();
	Init_NVRAM_I2C_SCL_Pin();
	Init_NVRAM_I2C_SDA_Pin();
	Init_hwEEPROM_WP();
	Init_5V_VDET();   // for MHL Detect
	#endif
	#if ENABLE_MHL
	#if CHIP_ID==CHIP_TSUM2
	Init_MHL_PS_CTRL_Pin(); // default set to discharge
	Init_HYBRID_MHL_HDMI_Cable_Detect_Pin();
	#else
	CLR_MHL_PS_CTRL_CHARGE0();
	CLR_MHL_PS_CTRL_CHARGE1();
	CLR_MHL_PS_CTRL_CHARGE2();
	Init_hwDVI0Cable_Pin();
	Init_hwDVI1Cable_Pin();
	Init_hwDVI2Cable_Pin();
	#endif
	#endif
	#if PanelminiLVDS ||PANEL_VCOM_ADJUST	//110229 Modify
	Init_VCOM_I2C_SCL_Pin();
	Init_VCOM_I2C_SDA_Pin();
	#if PANEL_VCOM_ADJUST	//121211 Modify
	HW_CLR_VCOM_I2C_SCL();
	HW_CLR_VCOM_I2C_SDA();
	#endif
	#endif
	#if ENABLE_HDCP
	#if ENABLE_MHL
	#if CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF// demo board	// 130717 william For G15 compiling warning
	#if ENABLE_MHL_C1
	hw_Set_MHLTriStateHpd();
	#endif
	#if ENABLE_MHL_C2
	hw_Set_MHLTriStateHpd2();
	#endif
	#if ENABLE_MHL_C3
	hw_Set_MHLTriStateHpd3();
	#endif
	#endif
	#else
	hw_Set_HdcpHpd();
	Init_hwHDCP_Hpd_Pin();
	#if (ENABLE_DVI_INPUT+ENABLE_HDMI_INPUT+ENABLE_HDMI2ND_INPUT>1)
	hw_Set_HdcpHpd2();
	Init_hwHDCP_Hpd2_Pin();		//130808 xiandi
	#endif
	#endif
	// 130607 nick add
	hw_Set_HdcpHpd();	//130607 nick
	hw_Set_HdcpHpd2();
	hw_Set_HdcpHpd3();
	#endif
	hw_SetMute();
	Init_hwMute_Pin();
	Init_Audio_SD_Pin();
	hw_ClrGreenLed();
	hw_ClrAmberLed();
	Init_hwGreenLed_Pin();
	Init_hwAmberLed_Pin();
	#if ENABLE_DP_INPUT && ENABLE_DP_PS_CTRL
	Init_DP_PS_CTRL_CHARGE();
	SET_DP_PS_CTRL_CHARGE();
	#endif
	#if EarphoneDet_Enable
	Init_HarphoneDet_Pin();
	#endif
	#if Enable_CheckVcc5V
	Init_DetectVCC5V_Pin();
	#endif
}
/* initialize 8051 CPU timer & interrupt routine */
/* TCON.7(   TF1): Timer 1 overflow flag */
/* TCON.6(   TR1): Timer 1 stop/start bit */
/* TCON.5(   TF0): Timer 0 overflow flag */
/* TCON.4(   TR0): Timer 0 stop/start bit */
/* TCON.3(   IE1): Timer 1 INT1 interrupt flag */
/* TCON.2(   IT1): Timer 1 INT1 interrupt style setup*/
/* TCON.1(   IE0): Timer 0 /INT0 interrupt flag */
/* TCON.0(   IT0): Timer 0 /INT0 interrupt style setup */
void Init_ExternalInterrupt(void)
{
	//INT0
	#if EXT_TIMER0_1MS ||EXT_TIMER0_1S|| (ENABLE_MENULOAD && ML_USE_INT)||ENABLE_SW_DOUBLE_BUFFER	//111223 Modify
	#if EXT_TIMER0_1MS||EXT_TIMER0_1S
	INT_FIQ_TIMER0_ENABLE(TRUE);//msWriteByteMask( REG_2B00, 0, _BIT0 );
	#endif
	#if (ENABLE_MENULOAD && ML_USE_INT)
	msWriteByteMask( REG_2B00, 0, _BIT5 );
	#endif
	IT0 = 0; // 0:Level  1: falling edge trigger
	IE0 = 0;
	EX0 = 1; // enable external interrupt 0
	#else
	IT0 = 0;
	IE0 = 0;
	EX0 = 0;  // disable external interrupt 0
	#endif
	//INT1
	#if UseINT
	INT_SYNC_CHANGE_TRIGGER_TYPE();//msWriteByteMask( SC0_CA, _BIT1 | _BIT0, _BIT1 | _BIT0); // BIT0 for level trigger, BIT1 for active high
	/*
	#if CHIP_ID>=CHIP_TSUMV
	msWriteByteMask( REG_2B18, 0, _BIT1 ); // disp_int
	#else
	msWriteByteMask( REG_2B19, 0, _BIT2 ); // disp_int
	#endif
	*/
	INT_IRQ_DISP_ENABLE(TRUE); // disp_int
	IT1 = 0;//1; // set external interrupt 0 & 1 as falling edge trigger
	IE1 = 0;  // interrupt flag
	EX1 = 1;  // enable external interrupt 1
	#else
	IT1 = 0;
	IE1 = 0;
	EX1 = 0;
	#endif
	PX0 = 1;	//
	PX1 = 1;	//
	#if (MS_PM)&& ENABLE_DEBUG
	PS = 1;
	#endif
	#if 1//(ENABLE_DEBUG)  // 20130327 test for PM DC off ISR become busy when debug off
	IP0 = _BIT0 | _BIT4;
	IP1 = _BIT0 | _BIT4;
	#else
	IP0 = _BIT2;
	IP1 = _BIT0 | _BIT2 | _BIT4;
	#endif
}

void Init_Timer(void)
{
	WORD clock_period = ClockPeriod;
	/* -------------initialize Timer 0 -----------------------------*/
	g_ucTimer0_TH0 = clock_period >> 8;
	g_ucTimer0_TL0 = clock_period & 0xFF;
	ET0 = 1; // enable timer 0 interrupt
	TH0 = g_ucTimer0_TH0;
	TL0 = g_ucTimer0_TL0; // timer 0 counter
	TF0 = 0; // timer 1 flag
	/* -------------initialize Timer 0 -----------------------------*/
	ET1 = 0; // disable timer 1 interrupt
	TH1 = 0;
	TL1 = 0; // timer 1 counter
	TF1 = 0; // timer 1 flag
	// setup Timer mode
	// TMOD=0x11;  // set timer 1 as timer(1) , timer 0 as counter(5)
	TMOD = 0x21;
	// enable/disable timer
	TR0 = 1; // disable timer 0
	TR1 = 0; // disable timer 1
	#if EXT_TIMER0_1MS
	TR0 = 0;
	msWriteByte( REG_3C80, 0xEE );
	msWriteByte( REG_3C81, 0x37 );
	msWriteByte( REG_3C82, 0x00 );
	msWriteByte( REG_3C83, 0x00 );
	msWriteByte( REG_3C89, 0x03 );
	#endif
	#if EXT_TIMER0_1S
	mcuExTimer();
	#endif
	#if 0//EnableTime1Interrupt
	TR1 = 0;
	ET1 = 0;
	TH1 = g_ucTimer0_TH0;
	TL1 = g_ucTimer0_TL0;
	TMOD = 0x11;
	TR1 = 1;
	ET1 = 1;
	#endif
}


#if EXT_TIMER0_1S   // 2012-05-23-1
BYTE xdata g_second = 0;
BYTE xdata g_minute = 0;
BYTE xdata g_hour = 0;

// 130410 coding modified for avoid data race in isr and main, it must be bit data type.
bit g_oneSecondFlag = 0;
bit g_oneMinuteFlag = 0; //20130110 nick

void mcuExTimer()
{
	g_second = 0;
	g_minute = 0;
	g_hour = 0;
	g_oneSecondFlag = 0;
	g_oneMinuteFlag = 0; //20130110 nick
	// 1Hz interrupt
	msWriteByte(REG_3C80, CRYSTAL_CLOCK);
	msWriteByte(REG_3C81, CRYSTAL_CLOCK >> 8);
	msWriteByte(REG_3C82, CRYSTAL_CLOCK >> 16);
	msWriteByte(REG_3C83, CRYSTAL_CLOCK >> 24);
	msWriteByte(REG_3C89, 0x03);
}
#endif

/*----------Timer 2 -------------------*/
/* T2CON.7(   TF2): overflow flag */
/* T2CON.6(  EXF2): extern enable flag */
/* T2CON.5(  RCLK): receive clock */
/* T2CON.4(  TCLK): transfer clock */
/* T2CON.3( EXEN2): extern enable flag */
/* T2CON.2(   TR2): stop/start timer 2 */
/* T2CON.1(  C_T2): intern clock(0)/extern counter(1) switch */
/* T2CON.0(CP_RL2): capture flag */
void Init_SerialPort(void)
{
	ADCON |= _BIT7; 			// use S0RELH, S0RELL as baudrate generator
	SCON = 0x50;				// mode 1, 8-bit UART, enable receive
	PCON |= _BIT7;
	TI = 0;                     // clear transfer flag
	ES = 0;                     // disable uart interrupt
	//RI = 0;   //nick check 20130205
	TI0_FLAG = 0;
	#if 0
	#if ENABLE_DEBUG
	ES = 1; 					// enable uart interrupt
	// default baudrate-xtal
	// uart0
	S0RELH = HIBYTE( S0REL );
	S0RELL = LOBYTE( S0REL );
	// ENABLE_UART1
	S1RELH = HIBYTE( S1REL );
	S1RELL = LOBYTE( S1REL );
	#else
	ES = 0;                     // disable uart interrupt
	IEN2 &= ~ES1;
	#endif
	#endif
	#if 0//ENABLE_UART1
	S1CON &= ~TI1;	  // clear TI1
	S1CON &= ~RI1;	  // clear TI1
	#endif
	#if ENABLE_UART1
	S1CON = ( _BIT7 | _BIT4 );
	IEN2 = ES1;
	TI1_FLAG = 0;
	#endif
	#if ENABLE_DEBUG
	ReSyncCounter = 0;
	SIORxIndex = 0;
	#endif
}

#if 0
void MCU_EnableCache(Bool u8Enable)
{
	#if Enable_Cache
	if (u8Enable)
	{
		msWriteBit( REG_1018, 1, _BIT3 );
		msWriteBit( REG_2BA0, 0, _BIT0 );
	}
	else
	{
		msWriteBit( REG_2BA0, 1, _BIT0 );
		msWriteBit( REG_1018, 0, _BIT3 );
	}
	#else
	msWriteBit( REG_2BA0, 1, _BIT0 );
	msWriteBit( REG_1018, 0, _BIT3 );
	#endif
}
#endif

