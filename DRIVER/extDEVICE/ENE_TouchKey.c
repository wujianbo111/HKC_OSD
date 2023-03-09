/******************************************************************************
 Copyright (c) 2008 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: CapactiveKeypad.c
 [Date]:        12-May-2008
 [Comment]:
   Capactive Keypad control subroutines.
 [Reversion History]:
*******************************************************************************/

//#include "ITE_types.h"
#include "ENE_TouchKey.h"
#include "keypaddef.h"
#include "ENE_SettingTable.h"
#include "Power.h"
#include "ENE_I2C.h"


#define CAPACTIVE_KEY_DEBUG                     0
#if ENABLE_DEBUG&&CAPACTIVE_KEY_DEBUG
#define CAPACTIVE_KEY_PRINTF(str, value)        printData(str, value)
#define CAPACTIVE_KEY_PUTSTR(str)                   printMsg(str)
#else
#define CAPACTIVE_KEY_PRINTF(str, value)
#define CAPACTIVE_KEY_PUTSTR(str)
#endif
#define WRITE_BURST_MAX_LENGTH          32

#define I2C_ACKNOWLEDGE           		_LOW
#define I2C_NON_ACKNOWLEDGE       	_HIGH
#define I2C_ACCESS_DUMMY_TIME   	3


////  Prototypes of Private Variables /////////////////////////////////////////
WORD xdata g_wOneTouchDataRegs;
BYTE xdata s_ucKeyErrorCnt = 0;

BYTE xdata uc_BtnScanEn0 = 0;
BYTE xdata uc_BtnScanEn1 = 0;
//BYTE xdata uc_BtnScanEn2=0;  //130813 henry
BYTE xdata pData[5];

BYTE xdata GreenLedOn = 0;
BYTE xdata AmberLedOn = 0;

////  Prototypes of Private Functions /////////////////////////////////////////

extern void GetKeySignal(BYTE key, WORD *realsignal, WORD *delta, WORD *realrawcnt);

Bool appCapkeyEneReadReg(BYTE ucAddrH, BYTE ucAddrL, BYTE* buffer, BYTE ucBufLen )
{
	BYTE xdata ucCmmandCode;
	BYTE xdata ucDummy; // loop dummy
	BYTE xdata ucDummyData;
	ucCmmandCode = SB358x_read_cmd | ucBufLen;
	ucDummy = I2C_ACCESS_DUMMY_TIME;
	while(ucDummy--)
	{
		if( CPK_I2C_MasterStart( I2C_WRITE, SB358x_SMBus_addr) == FALSE)
			continue;
		if (CPK_I2C_SendByte(SB358x_write_word_cmd) == I2C_NON_ACKNOWLEDGE) // check non-acknowledge
			continue;
		if (CPK_I2C_SendByte(ucAddrH) == I2C_NON_ACKNOWLEDGE) // check non-acknowledge
			continue;
		if (CPK_I2C_SendByte(ucAddrL) == I2C_NON_ACKNOWLEDGE) // check non-acknowledge
			continue;
		CPK_I2C_Stop();
		if( CPK_I2C_MasterStart( I2C_WRITE, SB358x_SMBus_addr) == FALSE )
			continue;
		if (CPK_I2C_SendByte(SB358x_read_cmd | ucBufLen) == I2C_NON_ACKNOWLEDGE) // check non-acknowledge
			continue;
		if( CPK_I2C_MasterStart( I2C_READ, SB358x_SMBus_addr) == FALSE )
			continue;
		if (ucBufLen >= 3)
		{
			ucDummyData = CPK_I2C_ReceiveByte( TRUE );  // read Byte count N
		}
		if( CPK_I2C_BurstRead( ucBufLen, buffer ) == FALSE )
		{
			CPK_I2C_Stop();
			continue;   //return FALSE;
		}
		return TRUE;
	} // while
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// @details
///////////////////////////////////////////////////////////////////////////////
Bool appCapkeyEneWriteReg(BYTE ucAddrH, BYTE ucAddrL, BYTE* buffer, BYTE ucBufLen)
{
	BYTE xdata ucCmmandCode;
	BYTE xdata ucDummy; // loop dummy
	if (ucBufLen < 3)
		ucCmmandCode = SB358x_write_cmd | ucBufLen;
	else
		ucCmmandCode = 0x03;
	ucDummy = I2C_ACCESS_DUMMY_TIME;
	while(ucDummy--)
	{
		if (CPK_I2C_MasterStart( I2C_WRITE, SB358x_SMBus_addr) == FALSE)
			continue;
		if (CPK_I2C_SendByte(SB358x_write_word_cmd) == I2C_NON_ACKNOWLEDGE) // check non-acknowledge
			continue;
		if (CPK_I2C_SendByte(ucAddrH) == I2C_NON_ACKNOWLEDGE) // check non-acknowledge
			continue;
		if (CPK_I2C_SendByte(ucAddrL) == I2C_NON_ACKNOWLEDGE) // check non-acknowledge
			continue;
		CPK_I2C_Stop();
		if (CPK_I2C_MasterStart( I2C_WRITE, SB358x_SMBus_addr) == FALSE)
			continue;
		if (CPK_I2C_SendByte(ucCmmandCode) == I2C_NON_ACKNOWLEDGE) // check non-acknowledge
			continue;
		// if (ucBufLen>=3)
		// {
		//     if (CPK_I2C_SendByte(ucBufLen) == I2C_NON_ACKNOWLEDGE) // check non-acknowledge
		//         continue;
		//  }
		if( CPK_I2C_BurstWrite( ucBufLen, buffer ) == TRUE )
		{
			CPK_I2C_Stop();
			continue;
		}
		CPK_I2C_Stop();
		return TRUE;
	} // while
	return FALSE;
}


////  Implementations of Public Functions /////////////////////////////////////
Bool ENE_I2C_ReadByte(WORD wAddr, BYTE *buffer )
{
	Bool bResult = TRUE;
	BYTE  ucAddrH, ucAddrL;
	ucAddrH = ( wAddr & 0xFF00 ) >> 8;
	ucAddrL = ( wAddr & 0x00FF );
	bResult = appCapkeyEneReadReg( ucAddrH, ucAddrL, buffer, 1 );
	return	bResult;
}

void ENE_I2C_WriteByte(WORD wAddr, BYTE ucValue)
{
	BYTE  ucAddrH, ucAddrL;
	ucAddrH = ( wAddr & 0xFF00 ) >> 8;
	ucAddrL = ( wAddr & 0x00FF );
	appCapkeyEneWriteReg( ucAddrH, ucAddrL, &ucValue, 1);
}

Bool appCapkeyEneReadTbl(BYTE ucAddrH, BYTE ucAddrL, BYTE* buffer, BYTE ucBufLen)
{
	Bool bResult = FALSE;
	bResult = appCapkeyEneReadReg( ucAddrH, ucAddrL, buffer, ucBufLen);
	return bResult;
}

void ENE_I2C_WriteBlock(WORD wAddr, BYTE ucBufLen, BYTE* buffer)
{
	BYTE  xdata ucAddrH = 0;
	BYTE xdata ucAddrL = 0;
	while(ucBufLen)
	{
		ucAddrH = ( wAddr & 0xFF00 ) >> 8;
		ucAddrL = ( wAddr & 0x00FF );
		appCapkeyEneWriteReg( ucAddrH, ucAddrL, (buffer++), 1 );
		ucBufLen--;
		wAddr++;
	}
	#if ENE_IC_TYPE == SB357X
	ForceDelay1ms(15);
	#endif
}


#if ENE_IC_TYPE == SB358X

void CPK_I2CInit(void)
{
	Init_HW_SET_CPK_I2C_SCL_Pin();
	Init_HW_SET_CPK_I2C_SCL_Pin();
}

void Reset_SB358xIC()
{
	/** Send Low pulse to SB358x's REST# pin to reset SB358x IC. **/
	CPK_I2CInit();
	ForceDelay1ms(30);
	HW_CLR_CPK_RESET_PIN();
	ForceDelay1ms(1);
	HW_SET_CPK_RESET_PIN();   // 20130529 Annie For ESD
	// HW_CLR_CPK_RESET_PIN();
	ForceDelay1ms(30);
}

void SB358x_reg_init(void)
{
	BYTE retrycnt = 3;
	Reset_SB358xIC();
	//stop SB358x scanning.
	ENE_I2C_WriteByte(0xA0, 0x00);
	// Initialize Delta Reg., range= 0x54~0x7D
	ENE_I2C_WriteBlock(0x54, 42, sb358x_delta_reg_table);
	// Initialize Scan Reg., range= 0x080~0x09F
	ENE_I2C_WriteBlock(0x80, 32, sb358x_scan_reg_table);
	uc_BtnScanEn0 = sb358x_scan_reg_table[29];
	uc_BtnScanEn1 = sb358x_scan_reg_table[30];
	//	uc_BtnScanEn2 = sb358x_senario_reg_table[0];  //130813 henry
	// Clear all INT pending flag, range= 0x0A4~00A5
	ENE_I2C_WriteBlock(0xA4, 3, sb358x_Pending_Flag_reg_table);
	// Initialize GPIO mode select Reg., range= 0x100~0101
	ENE_I2C_WriteBlock(0x100, 2, sb358x_gpio_mode_select_reg_table);
	// Initialize GPIO PWM Reg., range= 0x104~0x109
	ENE_I2C_WriteBlock(0x104, 6, sb358x_gpio_pwm_output_reg_table);
	// Initialize GPIO PWM Reg., range= 0x10A~0x10F
	ENE_I2C_WriteBlock(0x10A, 6, sb358x_PWM_Mode_config_table);
	// Initialize Senario Related Reg., range= 0x110~0x147
	ENE_I2C_WriteBlock(0x110, 56, sb358x_senario_reg_table);
	// Enable INT, range= 0xA7, 0xA8
	ENE_I2C_WriteBlock(0xA7, 2, sb358x_low_power_reg_table);
	//for(i=0; i < 56;i++)
	//    ENE_I2C_ReadByte(0x110+i, &ucCTM_CustomerData[i+0x10]);
	// Initialize Auto PWM Reg., range= 0x148~0x19D
	ENE_I2C_WriteBlock(0x148, 86, sb358x_auto_pwm_reg_table);
	// Initialize MISC Reg., range= 0x1A0
	ENE_I2C_WriteByte(0x1A0, sb358x_gpio_misc_reg_table[0]);
	//enable SB358x scanning, one button-on & disable sleep function.
	ENE_I2C_WriteByte(0xA0, 0x01);
}

void appRegInit(void)
{
	SB358x_reg_init();
}

///////////////////////////////////////////////////////////////////////////////
/// @note           Original name is appGetI2CKeypadInt
/// @details        Get I2C Key INT status
///////////////////////////////////////////////////////////////////////////////
Bool appGetI2CKeypadInt( void )
{
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// @details        Get I2C Key Button status
///////////////////////////////////////////////////////////////////////////////
BYTE appGetI2CKeypadStatus( void )
{
	BYTE xdata ucKeyStatus[2];
	BYTE keypad = 0xFF;
	WORD XDATA ucFactoryKey = TPREG_FACTORY;
	if(appGetI2CKeypadInt())
	{
		if( appCapkeyEneReadTbl( 0x00, 0xA1, (BYTE*)&ucKeyStatus, sizeof(ucKeyStatus) ) == TRUE )
		{
			s_ucKeyErrorCnt = 0;
			g_wOneTouchDataRegs = ucKeyStatus;
			g_wOneTouchDataRegs = (WORD)ucKeyStatus[0] << 8 | ucKeyStatus[1];
			if(g_wOneTouchDataRegs & TPREG_POWER)
				;
			else
			{
				keypad = 0xFF;                 //110328 Modify
			}
			g_wOneTouchDataRegs &= TPREG_KEYPADMASK;
			if( (g_wOneTouchDataRegs == ucFactoryKey) && !PowerOnFlag)
			{
				keypad &= ~(KEY_FACTORY);
			}
			else if(( g_wOneTouchDataRegs == TPREG_OSDLOCK ) && !PowerOnFlag )
			{
				keypad &= ~KEY_LOCK;
			}
			else if( g_wOneTouchDataRegs == TPREG_Recovery)
			{
				keypad &= ~KEY_Recovery;
			}
			else if( g_wOneTouchDataRegs == TPREG_POWER)
			{
				keypad &= ~KEY_POWER;
			}
			else if( g_wOneTouchDataRegs == TPREG_MENU )
			{
				keypad &= ~KEY_MENU;
			}
			else if( g_wOneTouchDataRegs == TPREG_DOWN)
			{
				keypad &= ~KEY_MINUS;
			}
			else if( g_wOneTouchDataRegs == TPREG_UP )
			{
				keypad &= ~KEY_PLUS;
			}
			else if( g_wOneTouchDataRegs ==  TPREG_EXIT)
			{
				keypad &= ~KEY_EXIT;
			}
			//else if( g_wOneTouchDataRegs ==  TPREG_PIVOT)
			//{
			//	keypad &= ~KEY_PIVOT;
			//}
			else
			{
				keypad = 0xff;
			}
		}
	}
	else
	{
		s_ucKeyErrorCnt ++;
	}
	if( s_ucKeyErrorCnt >= 100 )
	{
		// g_bENEKeyRepeatStatus = FALSE;
		s_ucKeyErrorCnt = 0;
		//appI2CKeyInit();
	}
	return keypad;
}


#if ENE_LED_TYPE == ENE_LED_GPIO
void GPIO_Init(WORD GPIOPort, WORD GPIOOutput)
{
	//Set output signal to HIGH(OFF) or LOW(ON)
	ENE_I2C_ReadByte(0x104, &pData[0]);
	ENE_I2C_ReadByte(0x105, &pData[1]);
	pData[0] |= (GPIOPort & 0xFF);
	pData[1] |= (GPIOPort >> 8);
	pData[0] &= ~(GPIOOutput & 0xFF);
	pData[1] &= ~(GPIOOutput >> 8);
	ENE_I2C_WriteByte(0x104, pData[0]);
	ENE_I2C_WriteByte(0x105, pData[1]);
	//Enable output signal
	ENE_I2C_ReadByte(0x108, &pData[0]);
	ENE_I2C_ReadByte(0x109, &pData[1]);
	ENE_I2C_WriteByte(0x108, pData[0] | (GPIOPort & 0xFF));
	ENE_I2C_WriteByte(0x109, pData[1] | (GPIOPort >> 8));
	//Set GPIO mode select - 0: GPIO mode, 1: PWM mode
	GPIOPort = ~GPIOPort;
	ENE_I2C_ReadByte(0x100, &pData[0]);
	ENE_I2C_ReadByte(0x101, &pData[1]);
	ENE_I2C_WriteByte(0x100, pData[0] & (GPIOPort & 0xFF));
	ENE_I2C_WriteByte(0x101, pData[1] & (GPIOPort >> 8));
}

void GPIO_LED_ON(WORD GPIOOutput)
{
	ENE_I2C_ReadByte(0x104, &pData[0]);
	ENE_I2C_ReadByte(0x105, &pData[1]);
	//reverse input data
	GPIOOutput = ~GPIOOutput;
	pData[0] = pData[0] & (GPIOOutput & 0xFF);
	pData[1] = pData[1] & (GPIOOutput >> 8);
	//Set output signal to high/low
	ENE_I2C_WriteByte(0x104, pData[0]);
	ENE_I2C_WriteByte(0x105, pData[1]);
}

void GPIO_LED_OFF(WORD GPIOOutput)
{
	ENE_I2C_ReadByte(0x104, &pData[0]);
	ENE_I2C_ReadByte(0x105, &pData[1]);
	pData[0] = pData[0] | (GPIOOutput & 0xFF);
	pData[1] = pData[1] | (GPIOOutput >> 8);
	//Set output signal to high/low
	ENE_I2C_WriteByte(0x104, pData[0]);
	ENE_I2C_WriteByte(0x105, pData[1]);
	//Disable output signal
	ENE_I2C_ReadByte(0x108, &pData[0]);
	ENE_I2C_ReadByte(0x109, &pData[1]);
	ENE_I2C_WriteByte(0x108, pData[0] & (~GPIOOutput & 0xFF));
	ENE_I2C_WriteByte(0x109, pData[1] & (~GPIOOutput >> 8));
}
#else
void PWM_LED_LEVEL_Setting(BYTE ucLevel)
{
	// Set Auto PWM Linear Formula 0 parameters
	ENE_I2C_WriteByte(0x0150, 0xFF);             // cycle length
	ENE_I2C_WriteByte(0x0151, 0xFF);             // Start high length
	ENE_I2C_WriteByte(0x0152, sb358x_LED_level_table[ucLevel] );   // End high length
	ENE_I2C_WriteByte(0x0153, 0x00);             // Start wait time(unit: 50ms) = LED OFF
	ENE_I2C_WriteByte(0x0154, 0x00);             // End  wait time (unit: 50ms) = LED ON
	ENE_I2C_WriteByte(0x0155, 0xFF);             // First change value
	ENE_I2C_WriteByte(0x0156, 0xFF);             // Second change value
	ENE_I2C_WriteByte(0x0157, 0x00);             // Change time(unit: 1ms)
}

void PWM_LED_LEVEL_ON(WORD PWMPort)
{
	WORD i;
	#if 0
	// Workaround for the blink issue: PWM_LED_OFF to PWM_LED_ON
	ENE_I2C_ReadByte(0x104, &pData[0]);
	ENE_I2C_ReadByte(0x105, &pData[1]);
	ENE_I2C_ReadByte(0x108, &pData[2]);
	ENE_I2C_ReadByte(0x109, &pData[3]);
	pData[0] = pData[0] | (PWMPort & 0xFF);
	pData[1] = pData[1] | (PWMPort >> 8);
	ENE_I2C_WriteByte(0x104, pData[0]);
	ENE_I2C_WriteByte(0x105, pData[1]);
	pData[0] = pData[2] | (PWMPort & 0xFF);
	pData[1] = pData[3] | (PWMPort >> 8);
	ENE_I2C_WriteByte(0x108, pData[0]);
	ENE_I2C_WriteByte(0x109, pData[1]);
	//disable PWM mode for specified bits
	ENE_I2C_ReadByte(0x100, &pData[0]);
	ENE_I2C_ReadByte(0x101, &pData[1]);
	ENE_I2C_WriteByte(0x0100, pData[0] & (~PWMPort & 0xFF));
	ENE_I2C_WriteByte(0x0101, pData[1] & (~PWMPort >> 8));
	#endif
	for(i = 0; i < 16 ; i++)
	{
		if (PWMPort & (0x01 << i))
		{
			ENE_I2C_WriteByte(0x110 + 4 * i,   0xDF);
			ENE_I2C_WriteByte(0x110 + 4 * i + 1, 0x14);
		}
	}
	// Start PWM function for specified bits
	ENE_I2C_ReadByte(0x100, &pData[0]);
	ENE_I2C_ReadByte(0x101, &pData[1]);
	ENE_I2C_WriteByte(0x0100, pData[0] | (PWMPort & 0xFF));
	ENE_I2C_WriteByte(0x0101, pData[1] | (PWMPort >> 8));
}

void PWM_LED_LEVEL_OFF(WORD PWMPort)
{
	ENE_I2C_ReadByte(0x100, &pData[0]);
	ENE_I2C_ReadByte(0x101, &pData[1]);
	pData[0] = (pData[0] & ~(PWMPort & 0xFF));
	pData[1] = (pData[1] & ~(PWMPort >> 8));
	//disable PWM mode of specified ports
	ENE_I2C_WriteByte(0x0100, pData[0]);
	ENE_I2C_WriteByte(0x0101, pData[1]);
}
#endif

#if defined (ENABLE_KeySignal)	//130808 henry follow ENE FAE request
WORD xdata g_PreKeyStatus = 0;     // global variable
#define ENE_WORD(val) (((val&0xFF00)>>8)|((val&0x00FF)<<8))
Bool ENE358x_I2C_ReadWord(WORD wAddr, BYTE *buffer )
{
	Bool bResult = TRUE;
	BYTE  ucAddrH, ucAddrL;
	ucAddrH = ( wAddr & 0xFF00 ) >> 8;
	ucAddrL = ( wAddr & 0x00FF );
	bResult = appCapkeyEneReadReg( ucAddrH, ucAddrL, buffer, 2 );
	return	bResult;
}
void GetKeySignal(BYTE key, WORD *realsignal, WORD *delta, WORD *realrawcnt) //20130716_1648_SYS#1
{
	unsigned int rawcnt, threshold, baseline;
	*delta = (sb358x_delta_reg_table[key * 2 + 1] << 8) | (sb358x_delta_reg_table[key * 2]);
	ENE358x_I2C_ReadWord(0x00 + (key * 2), (BYTE *)&rawcnt);
	ENE358x_I2C_ReadWord(0x2A + (key * 2), (BYTE *)&threshold);
	threshold = ENE_WORD(threshold);
	rawcnt = ENE_WORD(rawcnt);
	baseline = threshold - *delta;
	if (rawcnt >= baseline)
		*realsignal  = rawcnt - baseline;
	else
		*realsignal  = 0;
	*realrawcnt = rawcnt;
}
#endif


/*********************************************************
 CheckESDFailure()
 Check if register content has been destroyed by ESD
*********************************************************/
BYTE CheckESDFailure()	//130808 henry follow ENE FAE request
{
	#if defined(ENABLE_KeySignal)
	{
		WORD xdata tempRealsignal = 0;
		WORD xdata tempdelta;
		WORD xdata temprawcnt;
		//WORD xdata tempKeyStatus;	//2014 .11. 07 request by Armingle
		//WORD xdata j;
		//WORD xdata PosTriKey;
		//BYTE   xdata i;
#define DUMMY_PORT 7
		// check dummy port
		GetKeySignal(DUMMY_PORT, &tempRealsignal, &tempdelta, &temprawcnt);


		if ((temprawcnt > 19000) || (temprawcnt < 10000))
			return 1;

		if(ENE_I2C_ReadByte(0xA0, &pData[0]) == 0)
		{
			return 1;
		}
		if(ENE_I2C_ReadByte(0x9D, &pData[1]) == 0)
		{
			return 1;
		}
		if(ENE_I2C_ReadByte(0x9E, &pData[2]) == 0)
		{
			return 1;
		}
		if ((pData[0] != 0x01) || (pData[1] != uc_BtnScanEn0) || (pData[2] != uc_BtnScanEn1)) //Modify By ENE FAE Request 20150922
		{
			return(1);  // SB358x host mode initialize
		}
	}
	#else
	if(ENE_I2C_ReadByte(0xA0, &pData[0]) == 0)
	{
		return 1;
	}
	if(ENE_I2C_ReadByte(0x9D, &pData[1]) == 0)
	{
		return 1;
	}
	if(ENE_I2C_ReadByte(0x9E, &pData[2]) == 0)
	{
		return 1;
	}
	if ((pData[0] != 0x01) || (pData[1] != uc_BtnScanEn0) || (pData[2] != uc_BtnScanEn1))
	{
		return(1);  // SB358x host mode initialize
	}
	#endif
	return(0); // normal status
}
#if ENE_LED_TYPE == ENE_LED_GPIO
void GPIO_LED_LOW(WORD GPIOPort)
{
	//Enable output signal
	ENE_I2C_ReadByte(0x108, &pData[0]);
	ENE_I2C_ReadByte(0x109, &pData[1]);
	ENE_I2C_WriteByte(0x108, pData[0] | (GPIOPort & 0xFF));
	ENE_I2C_WriteByte(0x109, pData[1] | (GPIOPort >> 8));
	ENE_I2C_ReadByte(0x104, &pData[0]);
	ENE_I2C_ReadByte(0x105, &pData[1]);
	//reverse input data
	GPIOPort = ~GPIOPort;
	pData[0] = pData[0] & (GPIOPort & 0xFF);
	pData[1] = pData[1] & (GPIOPort >> 8);
	//Set output signal to high/low
	ENE_I2C_WriteByte(0x104, pData[0]);
	ENE_I2C_WriteByte(0x105, pData[1]);
}
#endif
void appCheckEneESD(void)
{
	if(CheckESDFailure())
	{
		//HW_CLR_CPK_RESET_PIN();	//130808 henry follow ENE FAE request
		//Delay1ms(100);			//130808 henry follow ENE FAE request
		//HW_SET_CPK_RESET_PIN();	//130808 henry follow ENE FAE request
		appRegInit();                          //SB358x host mode initialize
		if(PowerSavingFlag)//20130516 for turn on the led.
		#if ENE_LED_TYPE == ENE_LED_GPIO  //Modify By ENE FAE Request 20150922
			GPIO_LED_LOW(AMBERLED);
		else
			GPIO_LED_LOW(WhiteLED);
		#else
		{
			PWM_LED_LEVEL_Setting(3);
			PWM_LED_LEVEL_ON(AMBERLED);
		}
		else
		{
			PWM_LED_LEVEL_Setting(3);
			PWM_LED_LEVEL_ON(WhiteLED);
		}
		#endif
		//printData("ENE ESD Faile", 0);
	}
}

//MP0:0x1
void TurnOffLED(void)
{
	#if ENE_LED_TYPE == ENE_LED_GPIO
	GPIO_LED_OFF(WhiteLED);
	GPIO_LED_OFF(AMBERLED);
	#else
	PWM_LED_LEVEL_OFF(WhiteLED);
	PWM_LED_LEVEL_OFF(AMBERLED);
	#endif
}

void TurnonGREENLED(void)
{
	#if ENE_LED_TYPE == ENE_LED_GPIO
	GPIO_Init(0x01, 0x01 );
	GPIO_LED_OFF(AMBERLED);
	GPIO_LED_ON(WhiteLED);
	#else
	PWM_LED_LEVEL_Setting(3);
	PWM_LED_LEVEL_OFF(AMBERLED);
	PWM_LED_LEVEL_ON(WhiteLED);
	#endif
}

void TurnonAMBERLED(void)
{
	#if ENE_LED_TYPE == ENE_LED_GPIO
	GPIO_Init(0x1000, 0x01 );
	GPIO_LED_OFF(WhiteLED);
	GPIO_LED_ON(AMBERLED);
	#else
	PWM_LED_LEVEL_Setting(3);
	PWM_LED_LEVEL_OFF(WhiteLED);
	PWM_LED_LEVEL_ON(AMBERLED);
	#endif
}
#else
// Definition of SB357x SMBUS commands
#define PWM_LED_ON_CMD           0x01
#define PWM_LED_OFF_CMD          0x02
#define GPIO_LED_HIGH_CMD        0x03
#define PWM_LEVEL_OFF_CMD        0x03
#define GPIO_LED_LOW_CMD         0x04
#define PWM_LEVEL_ON_CMD         0x05
#define PWM_BLINK_ON_CMD         0x06
#define PWM_BLINK_OFF_CMD        0x07
#define PWM_CLEAR_INT_CMD        0x08

//**********************************************************************************
//                                                                                 *
//  Function   : GPIO_LED_LOW (LEN ON)                                             *
//  Description: Set corresponding GPIO to LOW                                     *
//  Parameters : GPIOPort: 1: LOW, 0: don't change  	 	  					   *
//  Return     : None.                                                             *
//  Note       : None.                                                             *
//                                                                                 *
//**********************************************************************************
void GPIO_LED_LOW(WORD GPIOPort)
{
	pData[0] = GPIO_LED_LOW_CMD;
	pData[1] = GPIOPort;
	pData[2] = 0xFA;
	ENE_I2C_WriteBlock(0x8380, 3, &pData[0]);
}
//**********************************************************************************
//                                                                                 *
//  Function   : GPIO_LED_HIGH (LEN OFF)                                           *
//  Description: Set corresponding GPIO to HIGH                                    *
//  Parameters : GPIOPort: 1: HIGH, 0: don't change  	 	  					   *
//  Return     : None.                                                             *
//  Note       : None.                                                             *
//                                                                                 *
//**********************************************************************************
void GPIO_LED_HIGH(WORD GPIOPort)
{
	pData[0] = GPIO_LED_HIGH_CMD;
	pData[1] = GPIOPort;
	pData[2] = 0xFA;
	ENE_I2C_WriteBlock(0x8380, 3, &pData[0]);
}
//**********************************************************************************
//                                                                                 *
//  Function   : PWM_LED_ON                                                        *
//  Description: Turn on LED with PWM mode(Fade on).                           			   *
//  Parameters : PWMPort: PWM from HIGH to LOW for PWM ports	  				   *
//  Return     : None.                                                             *
//  Note       : None.                                                             *
//                                                                                 *
//**********************************************************************************
void PWM_LED_ON(WORD PWMPort)
{
	pData[0] = PWM_LED_ON_CMD;
	pData[1] = PWMPort;
	pData[2] = 0xFA;
	ENE_I2C_WriteBlock(0x8380, 3, &pData[0]);
}

//**********************************************************************************
//                                                                                 *
//  Function   : PWM_LED_OFF                                                       *
//  Description: Turn off LED with PWM mode(Fade off).                           			   *
//  Parameters : PWMPort: PWM from LOW to HIGH for PWM ports   	   				   *
//  Return     : None.                                                             *
//  Note       : None.                                                             *
//                                                                                 *
//**********************************************************************************
void PWM_LED_OFF(WORD PWMPort)
{
	pData[0] = PWM_LED_OFF_CMD;
	pData[1] = PWMPort;
	pData[2] = 0xFA;
	ENE_I2C_WriteBlock(0x8380, 3, &pData[0]);
}
//**********************************************************************************
//                                                                                 *
//  Function   : PWM_LED_Blinking_ON                                               *
//  Description: Turn on LED with PWM mode(Blinking).                  			   *
//  Parameters :
//                  PWMPort: Blinking ports	  			                    	   *
//                  ONTime: Blinking ON time  				                           *
//                  OFFTime: Blinking OFF time
//  Return     : None.                                                             *
//  Note       : None.                                                             *
//                                                                                 *
//**********************************************************************************
void PWM_LED_Blinking_ON(WORD PWMPort, BYTE ONTime, BYTE OFFTime)
{
	pData[0] = PWM_BLINK_ON_CMD;
	pData[1] = PWMPort;
	pData[2] = ONTime;
	pData[3] = OFFTime;
	pData[4] = 0xFA;
	ENE_I2C_WriteBlock(0x8380, 5, &pData[0]);
}

//**********************************************************************************
//                                                                                 *
//  Function   : PWM_LED_Blinking_OFF                                              *
//  Description: Turn off LED                                       			   *
//  Parameters : PWMPort: Blinking ports	  			                    	   *
//  Return     : None.                                                             *
//  Note       : None.                                                             *
//                                                                                 *
//**********************************************************************************
void PWM_LED_Blinking_OFF(WORD PWMPort)
{
	pData[0] = PWM_BLINK_OFF_CMD;
	pData[1] = PWMPort;
	pData[2] = 0xFA;
	ENE_I2C_WriteBlock(0x8380, 3, &pData[0]);
}

//**********************************************************************************
//                                                                                 *
//  Function   : PWM_LED_LEVEL_ON                                                  *
//  Description: Turn on LED with PWM mode(Level ON).                  			   *
//  Parameters : PWMPort: LED ports	  			                    	           *
//                      ucLevel: LED level (from 0 to 10)
//  Return     : None.                                                             *
//  Note       : None.                                                             *
//                                                                                 *
//**********************************************************************************
void PWM_LED_LEVEL_ON(WORD PWMPort, BYTE ucLevel)
{
	pData[0] = PWM_LEVEL_ON_CMD;
	pData[1] = PWMPort;
	pData[2] = sb357x_LED_level_table[ucLevel];
	pData[3] = 0xFA;
	ENE_I2C_WriteBlock(0x8380, 4, &pData[0]);
}

//**********************************************************************************
//                                                                                 *
//  Function   : PWM_LED_LEVEL_OFF                                                 *
//  Description: Turn off LED                                       			   *
//  Parameters : PWMPort: LED ports	  			                            	   *
//  Return     : None.                                                             *
//  Note       : None.                                                             *
//                                                                                 *
//**********************************************************************************
void PWM_LED_LEVEL_OFF(WORD PWMPort)
{
	pData[0] = PWM_LEVEL_OFF_CMD;
	pData[1] = PWMPort;
	pData[2] = 0xFA;
	ENE_I2C_WriteBlock(0x8380, 3, &pData[0]);
}
void RampOnLED(void)
{
	PWM_LED_ON(RAMP_LED);
}
void RampOffLED(void)
{
	PWM_LED_OFF(RAMP_LED);
}

void TurnOffLED(void)
{
	if(GreenLedOn)
		PWM_LED_OFF(WHILTE_LED);
	if(AmberLedOn)
		PWM_LED_OFF(AMBER_LED);
	GreenLedOn = 0;
	AmberLedOn = 0;
}
void TurnonGREENLED(void)
{
	if(AmberLedOn)
		PWM_LED_OFF(AMBER_LED);
	if(!GreenLedOn)
		PWM_LED_ON(WHILTE_LED);
	GreenLedOn = 1;
	AmberLedOn = 0;
}

void TurnonAMBERLED(void)
{
	if(GreenLedOn)
		PWM_LED_OFF(WHILTE_LED);
	if(!AmberLedOn)
		PWM_LED_ON(AMBER_LED);
	GreenLedOn = 0;
	AmberLedOn = 1;
}

//**********************************************************************************
//                                                                                 *
//  Function   : GetKeyStatus                                                      *
//  Description: Get all key status                                      		   *
//  Parameters : uiStatus (defined in SB357x_setting_table.h)              	       *
//  Return     : None                                                              *
//  Note       : None.                                                             *
//                                                                                 *
//**********************************************************************************
void GetKeyStatus(WORD *uiStatus)
{
	ENE_I2C_ReadByte(0x8011, &pData[0]);     //get button status.
	ENE_I2C_ReadByte(0x8012, &pData[1]);     //get button status.
	*uiStatus = ((WORD)pData[1] << 8) | pData[0];
}

//**********************************************************************************
//                                                                                 *
//  Function   : ClearINTStatus                                                          *
//  Description: Clear INT status, Pull INT to HIGH                        		   *
//  Parameters :                                                        	       *
//  Return     : None                                                              *
//  Note       : None.                                                             *
//                                                                                 *
//**********************************************************************************
void ClearINTStatus()
{
	pData[0] = PWM_CLEAR_INT_CMD;
	pData[1] = 0x00;
	pData[2] = 0xFA;
	ENE_I2C_WriteBlock(0x8380, 3, &pData[0]);
}

//**********************************************************************************
//                                                                                 *
//  Function   : CheckResetFlag                                                    *
//  Description: Check if ResetFlag is set                                 		   *
//  Parameters :                                                        	       *
//  Return     : 1: has been reset, 0: no reset                                    *
//  Note       : None.                                                             *
//                                                                                 *
//**********************************************************************************
BYTE CheckResetFlag()
{
	ENE_I2C_ReadByte(0x8330, &pData[0]);     //get Reset Flag
	if (pData[0] == 0xAA)
		return 1;
	else
		return 0;
}
//**********************************************************************************
//                                                                                 *
//  Function   : ClearResetFlag                                                    *
//  Description: Clear ResetFlag                                         		   *
//  Parameters :                                                        	       *
//  Return     : None                                                              *
//  Note       : None.                                                             *
//                                                                                 *
//**********************************************************************************
void ClearResetFlag()
{
	ENE_I2C_WriteByte(0x8330, 0x00);
}

void Reset_SB357xIC()
{
	/** Send Low pulse to SB357x's REST# pin to reset SB357x IC. **/
	HW_CLR_CPK_RESET_PIN();
	ForceDelay1ms(20);
	HW_SET_CPK_RESET_PIN();
	ForceDelay1ms(300);
}

//**********************************************************************************
//                                                                                 *
//  Function   : SB357x_reg_init                                                   *
//  Description: Register initialation of SB357x HOST mode.                        *
//  Parameters : None.                                                             *
//  Return     : None.                                                             *
//  Note       : This Function code is only for HOST model's SB357x IC.            *
//                                                                                 *
//**********************************************************************************
void SB357x_reg_init(void)
{
	//  BYTE i;
	BYTE a = 0;
	Reset_SB357xIC();
	//disable reg check
	//ENE357x_I2C_ReadByte(0x8080,  &pData[0]);
	//ENE357x_I2C_WriteByte(0x8080, (pData[0] & 0xF9));
	ForceDelay1ms(100);
	//disable scan
	ENE_I2C_WriteByte(0xFA20, 0x00);
	//disable baseline adjustment
	//ENE357x_I2C_ReadByte(0xFA18,  &pData[0]);
	//ENE357x_I2C_WriteByte(0xFA18, pData[0] & ~0x03);
	/*
	// Initialize scan parameter, range= 0xFA00 ~0xFA1F
	ENE357x_I2C_WriteBlock(0xFA00, 32, code_scan_init_table);

	// initial delta table
	for (i=0; i< 23; i++)
	{
	ENE357x_I2C_WriteByte(0xFB5C+i*2, code_delta_init_table[i]>> 8);
	ENE357x_I2C_WriteByte(0xFB5D+i*2, code_delta_init_table[i]&0xFF);
	}
	*/
	//enable baseline adjustment
	ENE_I2C_ReadByte(0xFA18,  &pData[0]);
	ENE_I2C_WriteByte(0xFA18, pData[0] | 0x03);
	//enable scan
	ENE_I2C_WriteByte(0xFA20, 0x01);
	if(a)	//no use func
	{
		appCapkeyEneReadTbl(0, 0, 0, 0);
		ClearINTStatus();
		CheckResetFlag();
		ClearResetFlag();
		GPIO_LED_HIGH(0);
		GPIO_LED_LOW(0);
		PWM_LED_ON(0);
		PWM_LED_OFF(0);
		PWM_LED_Blinking_ON(0, 0, 0);
		PWM_LED_Blinking_OFF(0);
		PWM_LED_LEVEL_ON(0, 0);
		PWM_LED_LEVEL_OFF(0);
		RampOnLED();
		RampOffLED();
		GetKeySignal(0, 0, 0, 0);
	}
}
void appRegInit(void)
{
	SB357x_reg_init();
}

BYTE appGetI2CKeypadStatus( void )
{
	WORD xdata ucKeyStatus;
	BYTE keypad = 0xFF;
	WORD XDATA ucFactoryKey = TPREG_FACTORY;
	GetKeyStatus(&ucKeyStatus);
	if(ucKeyStatus & TPREG_POWER)
		;
	else
	{
		keypad = 0xFF;
	}
	ucKeyStatus &= TPREG_KEYPADMASK;
	if( (ucKeyStatus == ucFactoryKey) && !PowerOnFlag)
	{
		keypad &= ~(KEY_FACTORY);
	}
	else if(( ucKeyStatus == TPREG_OSDLOCK ) && !PowerOnFlag )
	{
		keypad &= ~KEY_LOCK;
	}
	else if( ucKeyStatus == TPREG_Recovery)
	{
		keypad &= ~KEY_Recovery;
	}
	else if( ucKeyStatus == TPREG_POWER)
	{
		keypad &= ~KEY_POWER;
	}
	else if( ucKeyStatus == TPREG_MENU )
	{
		keypad &= ~KEY_MENU;
	}
	else if( ucKeyStatus == TPREG_DOWN)
	{
		keypad &= ~KEY_MINUS;
	}
	else if( ucKeyStatus == TPREG_UP )
	{
		keypad &= ~KEY_PLUS;
	}
	else if( ucKeyStatus ==  TPREG_EXIT)
	{
		keypad &= ~KEY_EXIT;
	}
	//else if( g_wOneTouchDataRegs ==  TPREG_PIVOT)
	//{
	//	keypad &= ~KEY_PIVOT;
	//}
	else
	{
		keypad = 0xff;
	}
	return keypad;
}

#if defined (ENABLE_KeySignal)	//130808 henry follow ENE FAE request
//**********************************************************************************
//                                                                                 *
//  Function   : GetKeySignal                                                      *
//  Description: Get signal, delta, SNR, Sensitivity for specified port 		   *
//  Parameters : key: sensor key number (MPx) 			                   	       *
//  Return     : None                                                              *
//  Note       : None.                                                             *
//                                                                                 *
//**********************************************************************************
void GetKeySignal(BYTE key, WORD *realsignal, WORD *delta, WORD *realrawcnt) //20140918 modified to I2C_ReadByte
{
	unsigned int rawcnt, threshold, baseline;
	//ENE_I2C_ReadWord(0xFB5C+(key*2), (BYTE *)delta);
	//ENE_I2C_ReadWord(0xFB00+(key*2), (BYTE *)&rawcnt);
	//ENE_I2C_ReadWord(0xFB2E+(key*2), (BYTE *)&threshold);
	ENE_I2C_ReadByte(0xFB5C + (key * 2),   (BYTE *)delta);
	ENE_I2C_ReadByte(0xFB5C + (key * 2) + 1, ((BYTE *)delta) + 1);
	ENE_I2C_ReadByte(0xFB00 + (key * 2),   (BYTE *)&rawcnt);
	ENE_I2C_ReadByte(0xFB00 + (key * 2) + 1, ((BYTE *)&rawcnt) + 1);
	ENE_I2C_ReadByte(0xFB2E+(key * 2),   (BYTE *)&threshold);
	ENE_I2C_ReadByte(0xFB2E+(key * 2) + 1, ((BYTE *)&threshold) + 1);
	baseline = threshold - *delta;
	if (rawcnt >= baseline)
		*realsignal  = rawcnt - baseline;
	else
		*realsignal  = 0;
	*realrawcnt = rawcnt;
}
#endif

//**********************************************************************************
//                                                                                 *
//  Function   : CheckESDFailure                                                   *
//  Description: Check if register content has been destroyed by ESD   			   *
//  Parameters : PWMPort: LED ports	  			                            	   *
//  Return     : 0: Pass                                                           *
//               1: Fail                                                           *
//  Note       : None.                                                             *
//                                                                                 *
//**********************************************************************************
BYTE CheckESDFailure()
{
	return(0); // normal status
}

void appCheckEneESD(void)
{
	if(CheckESDFailure())
	{
		appRegInit();
		/*
		if(PowerSavingFlag)//20130516 for turn on the led.
		GPIO_LED_LOW(AMBERLED);
		   	else
			GPIO_LED_LOW(WhiteLED);
		   	//printData("ENE ESD Faile", 0);
		   */
	}
}
#endif



////  Implementations of Private Functions /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
