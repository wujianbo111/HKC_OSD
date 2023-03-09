#include "types.h"
#include "board.h"
#include "keypaddef.h"
#include "ms_reg.h"
#include "global.h"
#include "debug.h"
#include "misc.h"
#include "ms_rwreg.h"
#include "mcu.h"
#include "debug.h"
#include <math.h>    //MST_MCU
#include "menudef.h"
#include "GPIO_DEF.h"
#if USEFLASH
#include "userpref.h"
#endif

#if ENABLE_ANDROID_IR	//131008 Modify
#include "drv_ir.h"
#endif

#define KEYPAD_DEBUG   0		// 130506
#if KEYPAD_DEBUG&&ENABLE_DEBUG
#define KEYPAD_PrintData(str, value)   	printData(str, value)
#define KEYPAD_PrintMsg(str)           	printMsg(str)
#else
#define KEYPAD_PrintData(str, value)
#define KEYPAD_PrintMsg(str)
#endif



extern void SaveMonitorSetting(void);


//================================================================
xdata BYTE KeypadButton = BTN_Nothing;




#if 1
#ifdef ADCKEY_A0_VALUE
#define SARADC_MASK 		0xFF
#define KEY_TOL                      8///4


#ifndef GPIO_POWER_KEY
#define GPIO_POWER_KEY		1
#endif
/******************************************************
#define ADCKEY_A0_VALUE     0x00
#define ADCKEY_A1_VALUE     0x68
#define ADCKEY_A2_VALUE     0xFF

#define ADCKEY_B0_VALUE     0x00
#define ADCKEY_B1_VALUE     0x68
#define ADCKEY_B2_VALUE     0x78


#define ADCKEY_A0       KEY_MENU
#define ADCKEY_A1       KEY_PLUS
#define ADCKEY_A2       KEY_NOTHING

#define ADCKEY_B0       KEY_MINUS
#define ADCKEY_B1       KEY_EXIT
#define ADCKEY_B2       KEY_NOTHING
*******************************************************/


BYTE Key_GetKeypadStatus( void )
{
	BYTE u8Keypad = 0xFF;
	BYTE u8Temp = 0;
	BYTE u8Temp1 = 0;
	BYTE retry_Key = 5;
	u8Temp = KEYPAD_ADC_A  & SARADC_MASK; //  SAR0
	while(retry_Key && (u8Temp < (SARADC_MASK - 5)))
	{
		u8Temp = KEYPAD_ADC_A  & SARADC_MASK; //  SAR0
		Delay1ms(15);
		u8Temp1 = KEYPAD_ADC_A  & SARADC_MASK;
		if(abs(u8Temp - u8Temp1) < 5)
			break;
		retry_Key--;
	}
	// u8Temp = KEYPAD_ADC_A  & SARADC_MASK;
	if (abs(u8Temp - ADCKEY_A0_VALUE)  <= KEY_TOL)
		u8Keypad &= ~ADCKEY_A0;
	#if (ADCKEY_A1_VALUE!=0xFF)
	if (abs(u8Temp - ADCKEY_A1_VALUE)  <= KEY_TOL)
		u8Keypad &= ~ADCKEY_A1;
	#endif
	#if (ADCKEY_A2_VALUE!=0xFF)
	if (abs(u8Temp - ADCKEY_A2_VALUE)  <= KEY_TOL)
		u8Keypad &= ~ADCKEY_A2;
	#endif
	retry_Key = 5;
	u8Temp = KEYPAD_ADC_B  & SARADC_MASK; //  SAR0
	while(retry_Key && (u8Temp < (SARADC_MASK - 5)))
	{
		u8Temp = KEYPAD_ADC_B  & SARADC_MASK; //  SAR1
		Delay1ms(15);
		u8Temp1 = KEYPAD_ADC_B  & SARADC_MASK;
		if(abs(u8Temp - u8Temp1) < 5)
			break;
		retry_Key--;
	}
	//u8Temp1 = KEYPAD_ADC_B  & SARADC_MASK;
	if (abs(u8Temp - ADCKEY_B0_VALUE)  <= KEY_TOL)
		u8Keypad &= ~ADCKEY_B0;
	#if (ADCKEY_B1_VALUE!=0xFF)
	if (abs(u8Temp - ADCKEY_B1_VALUE)  <= KEY_TOL)
		u8Keypad &= ~ADCKEY_B1;
	#endif
	#if (ADCKEY_B2_VALUE!=0xFF)
	if (abs(u8Temp - ADCKEY_B2_VALUE)  <= KEY_TOL)
		u8Keypad &= ~ADCKEY_B2;
	#endif
	//POWER_KEY
	#if GPIO_POWER_KEY
	if (PowerKey == 0)
		u8Keypad &= ~KEY_POWER;
	#endif
	return u8Keypad;
}
#elif (ModelName==HJP07BF2_Project)
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp;                                       // temp1, retry_Key;
	temp = KEYPAD_ADC_A & 0xFF;
	if(temp != 0xFF)
	{
		Delay1ms(10);
		while (abs(temp - ( temp = KEYPAD_ADC_A & 0xFF)) > 5)
		{
			Delay1ms(15);
			temp = KEYPAD_ADC_A & 0xFF;
		}
	}
	if (temp >= 0x6A && temp <= 0x7A)
		keypad &= ~KEY_MENU;
	temp = KEYPAD_ADC_B & 0xFF;
	if(temp != 0xFF)
	{
		Delay1ms(10);
		while (abs(temp - ( temp = KEYPAD_ADC_B & 0xFF)) > 5)
		{
			Delay1ms(15);
			temp = KEYPAD_ADC_B & 0xFF;
		}
	}
	if (temp <= 0x0A)
		keypad &= ~KEY_MINUS; //keypad &= ~KEY_MENU;
	else if (temp >= 0x40 && temp <= 0x50)
		keypad &= ~KEY_PLUS;
	else if (temp >= 0x63 && temp <= 0x7D)
		keypad &= ~KEY_EXIT;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
}
#elif (ModelName == HH_TCL_T27N1_Project)||(ModelName==HH_TCL_T27N1_F_Project)
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	if(temp >=  0x00 && temp <= 0x09 )
	{
		keypad &= ~KEY_MENU;
	}
	else if (temp >=  0x62 && temp < 0x6F )
	{
		keypad &= ~KEY_EXIT;
	}
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	if(temp >=  0x00 && temp <= 0x09 )
	{
		keypad &= ~KEY_POWER;
	}
	if(temp >=  0x25 && temp < 0x35 )
	{
		keypad &= ~KEY_PLUS;
	}
	else if (temp >=  0x62 && temp < 0x6F )
	{
		keypad &= ~KEY_MINUS;
	}
	return keypad;
}
#elif (ModelName == HH_TSY_KF270F075P_F_Project)
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	if(temp >=  0x00 && temp <= 0x09 )
	{
		keypad &= ~KEY_MENU;
	}
	else if (temp >=  0x62 && temp < 0x6F )
	{
		keypad &= ~KEY_EXIT;
	}
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	if(temp >=  0x00 && temp <= 0x09 )
	{
		keypad &= ~KEY_POWER;
	}
	if(temp >=  0x25 && temp < 0x35 )
	{
		keypad &= ~KEY_PLUS;
	}
	else if (temp >=  0x62 && temp < 0x6F )
	{
		keypad &= ~KEY_MINUS;
	}
	return keypad;
}
#elif (ModelName == TOPSYNC_KF238F075P_Y)
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 5;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA // 090410
	if(temp < 60)
		printData("ADC2=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_MENU;
	else if(temp >= 0x60 && temp < 0x70)
		keypad &= ~KEY_PLUS;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA
	if(temp < 60)
		printData("ADC3=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_MINUS;
	else if(temp >= 0x60 && temp < 0x70)
		keypad &= ~KEY_EXIT;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
}

#elif (ModelName == MODEL_24P630F_CHD)
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 5;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA // 090410
	if(temp < 60)
		printData("ADC2=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_MENU;
	else if(temp >= 0x60 && temp < 0x70)
		keypad &= ~KEY_PLUS;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA
	if(temp < 60)
		printData("ADC3=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_MINUS;
	else if(temp >= 0x60 && temp < 0x70)
		keypad &= ~KEY_EXIT;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
}

#elif (ModelName == MODEL_FZ22LVD_FND)
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 5;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA // 090410
	if(temp < 60)
		printData("ADC2=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_MENU;
	else if(temp >= 0x60 && temp < 0x70)
		keypad &= ~KEY_PLUS;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA
	if(temp < 60)
		printData("ADC3=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_MINUS;
	else if(temp >= 0x60 && temp < 0x70)
		keypad &= ~KEY_EXIT;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
}

#elif (ModelName == X_STAR_NX2410F)
#if 			1	//2ke hu key
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 5;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA // 090410
	if(temp < 60)
		printData("ADC2=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_MENU;
	else if(temp >= 0x95 && temp < 0xA5)
		keypad &= ~KEY_PLUS;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA
	if(temp < 60)
		printData("ADC3=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_MINUS;
	else if(temp >= 0x95 && temp < 0xA5)
		keypad &= ~KEY_EXIT;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
}
#else
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 5;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA // 090410
	if(temp < 60)
		printData("ADC2=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_MENU;
	else if(temp >= 0x60 && temp < 0x70)
		keypad &= ~KEY_PLUS;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA
	if(temp < 60)
		printData("ADC3=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_MINUS;
	else if(temp >= 0x60 && temp < 0x70)
		keypad &= ~KEY_EXIT;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
}
#endif
#elif (ModelName == HH_HKC_T32M8C_C_Project)
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp;                                       // temp1, retry_Key;
	temp = KEYPAD_ADC_A & 0xFF;
	if(temp != 0xFF)
	{
		Delay1ms(10);
		while (abs(temp - ( temp = KEYPAD_ADC_A & 0xFF)) > 5)
		{
			Delay1ms(15);
			temp = KEYPAD_ADC_A & 0xFF;
		}
	}
	if (temp >= 0x6A && temp <= 0x7A)
		keypad &= ~KEY_MENU;
	temp = KEYPAD_ADC_B & 0xFF;
	if(temp != 0xFF)
	{
		Delay1ms(10);
		while (abs(temp - ( temp = KEYPAD_ADC_B & 0xFF)) > 5)
		{
			Delay1ms(15);
			temp = KEYPAD_ADC_B & 0xFF;
		}
	}
	if (temp <= 0x0A)
		keypad &= ~KEY_PLUS; //keypad &= ~KEY_MENU;
	else if (temp >= 0x40 && temp <= 0x50)
		keypad &= ~KEY_MINUS;
	else if (temp >= 0x63 && temp <= 0x7D)
		keypad &= ~KEY_EXIT;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
}

#elif (ModelName == HH_BOARD_DEMO_Project)
#if	 MainBoardType ==MainBorad_JRY_L5AFHD_FV1
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	if(temp >=  0x00 && temp <= 0x09 )
	{
		keypad &= ~KEY_MENU;//y
	}
	else if (temp >=  0x62 && temp < 0x6F )
	{
		keypad &= ~KEY_EXIT;//n
	}
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	if(temp >=  0x00 && temp <= 0x09 )
	{
		keypad &= ~KEY_POWER;
	}
	if(temp >=  0x29 && temp < 0x35 )
	{
		keypad &= ~KEY_PLUS;//--
	}
	else if (temp >=  0x62 && temp < 0x6F )
	{
		keypad &= ~KEY_MINUS;//s
	}
	return keypad;
}
#else
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 5;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA // 090410
	if(temp < 60)
		printData("ADC2=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_MENU;
	else if(temp >= 0x60 && temp < 0x70)
		keypad &= ~KEY_PLUS;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA
	if(temp < 60)
		printData("ADC3=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_MINUS;
	else if(temp >= 0x60 && temp < 0x70)
		keypad &= ~KEY_EXIT;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
}
#endif

#elif (ModelName == HH_HKC_27P630Q_U_Project)||(ModelName == HH_HKC_XXXXX_U2_Project)||(ModelName == HH_HKC_KF270F144P_Project)
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 5;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	if( temp < 0x10)
		keypad &= ~KEY_MENU;
	else if(temp >= 0x98 && temp < 0xAB)
		keypad &= ~KEY_EXIT;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	if( temp < 0x10)
		keypad &= ~KEY_POWER;
	else if(temp >= 0x4B && temp < 0x60)
		keypad &= ~KEY_PLUS;
	else if(temp >= 0x98 && temp < 0xAB)
		keypad &= ~KEY_MINUS;
	/*  if(PowerKey == 0 )
	  {
	      keypad &= ~KEY_MENU;
	  }
	  */
	return keypad;
}
#elif (ModelName == HH_HKC_XXXXX_U_Project)
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 5;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	if( temp < 0x10)
		keypad &= ~KEY_PLUS;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	if( temp < 0x10)
		keypad &= ~KEY_MINUS;
	else if(temp >= 0x40 && temp < 0x4A)
		keypad &= ~KEY_MENU;
	else if(temp >= 0x70 && temp < 0x78)
		keypad &= ~KEY_EXIT;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
}
#elif (ModelName == HH_TCL_DEMO_Project)
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp;                                       // temp1, retry_Key;
	temp = KEYPAD_ADC_A & 0xFF;
	if(temp != 0xFF)
	{
		Delay1ms(10);
		while (abs(temp - ( temp = KEYPAD_ADC_A & 0xFF)) > 5)
		{
			Delay1ms(15);
			temp = KEYPAD_ADC_A & 0xFF;
		}
	}
	if (temp >= 0x6A && temp <= 0x7A)
		keypad &= ~KEY_MENU;
	temp = KEYPAD_ADC_B & 0xFF;
	if(temp != 0xFF)
	{
		Delay1ms(10);
		while (abs(temp - ( temp = KEYPAD_ADC_B & 0xFF)) > 5)
		{
			Delay1ms(15);
			temp = KEYPAD_ADC_B & 0xFF;
		}
	}
	if (temp <= 0x0A)
		keypad &= ~KEY_PLUS; //keypad &= ~KEY_MENU;
	else if (temp >= 0x40 && temp <= 0x50)
		keypad &= ~KEY_MINUS;
	else if (temp >= 0x63 && temp <= 0x7D)
		keypad &= ~KEY_EXIT;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
}
#elif (MainBoardType == MainBoard_JRY_O58FHG_CV1)
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 5;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA // 090410
	if(temp < 60)
		printData("ADC2=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_NOTHING;
	else if(temp >= 0x40 && temp < 0x50)
		keypad &= ~KEY_NOTHING;
	else if(temp >= 0x68 && temp < 0x78)
		keypad &= ~KEY_MENU;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA
	if(temp < 60)
		printData("ADC3=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_PLUS;
	else if(temp >= 0x40 && temp < 0x50)
		keypad &= ~KEY_MINUS;
	else if(temp >= 0x68 && temp < 0x78)
		keypad &= ~KEY_EXIT;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
}
#elif (MainBoardType==MainBoard_JRY_O58FHG_BV1)
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 5;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA // 090410
	if(temp < 60)
		printData("ADC2=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_NOTHING;
	else if(temp >= 0x50 && temp < 0x5F)
		keypad &= ~KEY_MENU;
	else if(temp >= 0x2B && temp < 0x3A)
		keypad &= ~KEY_MINUS;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA
	if(temp < 60)
		printData("ADC3=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_EXIT;
	else if(temp >= 0x50 && temp < 0x5F)
		keypad &= ~KEY_PLUS;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
}
#elif (MainBoardType==MainBoard_JRY_W58VHN_NV1)
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 5;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA // 090410
	if(temp < 60)
		printData("ADC2=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_NOTHING;
	else if(temp >= 0x12 && temp < 0x1B)
		keypad &= ~KEY_MENU;
	else if(temp >= 0x25 && temp < 0x2F)
		keypad &= ~KEY_MINUS;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA
	if(temp < 60)
		printData("ADC3=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_PLUS;//;
	else if(temp >= 0x26 && temp < 0x30)
		keypad &= ~KEY_EXIT;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
}

#elif (ModelName==JRY_L58VHN_GV3)

BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp;                                       // temp1, retry_Key;
	temp = KEYPAD_ADC_A & 0xFF;
	if(temp != 0xFF)
	{
		Delay1ms(10);
		while (abs(temp - ( temp = KEYPAD_ADC_A & 0xFF)) > 5)
		{
			Delay1ms(15);
			temp = KEYPAD_ADC_A & 0xFF;
		}
	}
	if (temp <= 0x0A)
		keypad &= ~KEY_MINUS; //keypad &= ~KEY_PLUS;
	else if (temp >= 0x40 && temp <= 0x4F)
		keypad &= ~KEY_EXIT;
	temp = KEYPAD_ADC_B & 0xFF;
	if(temp != 0xFF)
	{
		Delay1ms(10);
		while (abs(temp - ( temp = KEYPAD_ADC_B & 0xFF)) > 5)
		{
			Delay1ms(15);
			temp = KEYPAD_ADC_B & 0xFF;
		}
	}
	if (temp <= 0x0A)
		keypad &= ~KEY_MENU; //keypad &= ~KEY_MENU;
	else if (temp >= 0x40 && temp <= 0x4F)
		keypad &= ~KEY_PLUS; //KEY_MINUS
	else if (temp >= 0x67 && temp <= 0x7A)
		keypad &= ~KEY_POWER;
	//if(PowerKey == 0 )
	//{
	//    keypad &= ~KEY_POWER;
	//}
	return keypad;
}
#elif (ModelName==JRY_L58CDT9_EV1)
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp;                                       // temp1, retry_Key;
	temp = KEYPAD_ADC_A & 0xFF;
	if(temp != 0xFF)
	{
		Delay1ms(10);
		while (abs(temp - ( temp = KEYPAD_ADC_A & 0xFF)) > 5)
		{
			Delay1ms(15);
			temp = KEYPAD_ADC_A & 0xFF;
		}
	}
	if (temp <= 0x0A)
		keypad &= ~KEY_EXIT; //keypad &= ~KEY_MENU;
	else if (temp >= 0x50 && temp <= 0x5A)
		keypad &= ~KEY_MINUS;
	temp = KEYPAD_ADC_B & 0xFF;
	if(temp != 0xFF)
	{
		Delay1ms(10);
		while (abs(temp - ( temp = KEYPAD_ADC_B & 0xFF)) > 5)
		{
			Delay1ms(15);
			temp = KEYPAD_ADC_B & 0xFF;
		}
	}
	if (temp <= 0x0A)
		keypad &= ~KEY_POWER; //keypad &= ~KEY_MENU;
	else if (temp >= 0x4B && temp <= 0x58)
		keypad &= ~KEY_MENU;
	else if (temp >= 0x63 && temp <= 0x7D)
		keypad &= ~KEY_PLUS;
	//if(PowerKey == 0 )
	//{
	//    keypad &= ~KEY_POWER;
	//}
	return keypad;
}

#elif (ModelName==JRY_L58CDT9_GV3)
#if (MainBoardType == MainBoard_JRY_L58CDT9_EV1)
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp;                                       // temp1, retry_Key;
	temp = KEYPAD_ADC_A & 0xFF;
	if(temp != 0xFF)
	{
		Delay1ms(10);
		while (abs(temp - ( temp = KEYPAD_ADC_A & 0xFF)) > 5)
		{
			Delay1ms(15);
			temp = KEYPAD_ADC_A & 0xFF;
		}
	}
	if (temp <= 0x0A)
		keypad &= ~KEY_EXIT; //keypad &= ~KEY_MENU;
	else if (temp >= 0x50 && temp <= 0x5A)
		keypad &= ~KEY_MINUS;
	temp = KEYPAD_ADC_B & 0xFF;
	if(temp != 0xFF)
	{
		Delay1ms(10);
		while (abs(temp - ( temp = KEYPAD_ADC_B & 0xFF)) > 5)
		{
			Delay1ms(15);
			temp = KEYPAD_ADC_B & 0xFF;
		}
	}
	if (temp <= 0x0A)
		keypad &= ~KEY_POWER; //keypad &= ~KEY_MENU;
	else if (temp >= 0x4B && temp <= 0x58)
		keypad &= ~KEY_MENU;
	else if (temp >= 0x63 && temp <= 0x7D)
		keypad &= ~KEY_PLUS;
	//if(PowerKey == 0 )
	//{
	//    keypad &= ~KEY_POWER;
	//}
	return keypad;
}
#else
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp;                                       // temp1, retry_Key;
	temp = KEYPAD_ADC_A & 0xFF;
	if(temp != 0xFF)
	{
		Delay1ms(10);
		while (abs(temp - ( temp = KEYPAD_ADC_A & 0xFF)) > 5)
		{
			Delay1ms(15);
			temp = KEYPAD_ADC_A & 0xFF;
		}
	}
	if (temp <= 0x0A)
		keypad &= ~KEY_PLUS; //keypad &= ~KEY_MENU;
	else if (temp >= 0x40 && temp <= 0x4F)
		keypad &= ~KEY_EXIT;
	temp = KEYPAD_ADC_B & 0xFF;
	if(temp != 0xFF)
	{
		Delay1ms(10);
		while (abs(temp - ( temp = KEYPAD_ADC_B & 0xFF)) > 5)
		{
			Delay1ms(15);
			temp = KEYPAD_ADC_B & 0xFF;
		}
	}
	if (temp <= 0x0A)
		keypad &= ~KEY_MENU; //keypad &= ~KEY_MENU;
	else if (temp >= 0x40 && temp <= 0x4F)
		keypad &= ~KEY_MINUS;
	else if (temp >= 0x67 && temp <= 0x7A)
		keypad &= ~KEY_POWER;
	//if(PowerKey == 0 )
	//{
	//    keypad &= ~KEY_POWER;
	//}
	return keypad;
}
#endif

#elif (ModelName==JRY_L58CDT9_PV1)

BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp;                                       // temp1, retry_Key;
	temp = KEYPAD_ADC_A & 0xFF;
	if(temp != 0xFF)
	{
		Delay1ms(10);
		while (abs(temp - ( temp = KEYPAD_ADC_A & 0xFF)) > 5)
		{
			Delay1ms(15);
			temp = KEYPAD_ADC_A & 0xFF;
		}
	}
	if (temp <= 0x0A)
		keypad &= ~KEY_PLUS; //keypad &= ~KEY_MENU;
	else if (temp >= 0x40 && temp <= 0x4F)
		keypad &= ~KEY_EXIT;
	temp = KEYPAD_ADC_B & 0xFF;
	if(temp != 0xFF)
	{
		Delay1ms(10);
		while (abs(temp - ( temp = KEYPAD_ADC_B & 0xFF)) > 5)
		{
			Delay1ms(15);
			temp = KEYPAD_ADC_B & 0xFF;
		}
	}
	if (temp <= 0x0A)
		keypad &= ~KEY_MENU; //keypad &= ~KEY_MENU;
	else if (temp >= 0x40 && temp <= 0x4F)
		keypad &= ~KEY_MINUS;
	else if (temp >= 0x67 && temp <= 0x7A)
		keypad &= ~KEY_POWER;
	//if(PowerKey == 0 )
	//{
	//    keypad &= ~KEY_POWER;
	//}
	return keypad;
}


#elif (MainBoardType == MainBoard_JRY_L58CDT9_NV1)
#if 1
BYTE Key_GetKeypadStatus(void)
{
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 5;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	if(temp > 0x6C && temp < 0x77) // 0x48
		keypad &= ~KEY_MENU;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	if(temp >= 0x00 && temp < 0x10)
		keypad &= ~KEY_EXIT;
	else if(temp > 0x43 && temp < 0x4D)
		keypad &= ~KEY_MINUS;
	else if(temp >= 0x65 && temp < 0x72)
		keypad &= ~KEY_PLUS;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
}
#endif
#elif (MainBoardType == MainBoard_L38CDMT9_GV1)

BYTE Key_GetKeypadStatus(void)
{
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 5;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	if(temp > 0x6C && temp < 0x77) // 0x48
		keypad &= ~KEY_MENU;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	if(temp >= 0x00 && temp < 0x10)
		keypad &= ~KEY_EXIT;
	else if(temp > 0x43 && temp < 0x4D)
		keypad &= ~KEY_PLUS;
	else if(temp >= 0x65 && temp < 0x72)
		keypad &= ~KEY_MINUS;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
}
#elif (MainBoardType == MainBoard_W38CDMT9_PV1)

BYTE Key_GetKeypadStatus(void)
{
	#if  0//  JRY  to  test
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 5;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA // 090410
	if(temp < 60)
		printData("ADC2=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_NOTHING;
	else if(temp >= 0x40 && temp < 0x50)
		keypad &= ~KEY_NOTHING;
	else if(temp >= 0x68 && temp < 0x78)
		keypad &= ~KEY_MENU;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA
	if(temp < 60)
		printData("ADC3=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_MINUS;
	else if(temp >= 0x40 && temp < 0x50)
		keypad &= ~KEY_EXIT;
	else if(temp >= 0x68 && temp < 0x78)
		keypad &= ~KEY_PLUS;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
	#else
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 5;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	if(  temp < 0x10 )
		keypad &= ~KEY_MINUS;
	else if(temp >= 0x40 && temp < 0x50)
		keypad &= ~KEY_PLUS;
	else if(temp >= 0xE5 && temp <= 0xF0)
		keypad &= ~KEY_EXIT;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
	#endif
}


#else
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 5;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA // 090410
	if(temp < 60)
		printData("ADC2=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_NOTHING;
	else if(temp >= 0x12 && temp < 0x1B)
		keypad &= ~KEY_MENU;
	else if(temp >= 0x25 && temp < 0x2F)
		keypad &= ~KEY_MINUS;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA
	if(temp < 60)
		printData("ADC3=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_PLUS;//;
	else if(temp >= 0x26 && temp < 0x30)
		keypad &= ~KEY_EXIT;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
}
#endif


#if (FEnterFunction==FEnter_AC_MENU)
void CheckFactoryKeyStatus(void)
{
	BYTE keypadStatus;
	keypadStatus = (Key_GetKeypadStatus() ^ KeypadMask) &KeypadMask;
	if (keypadStatus == KEY_MENU)
	{
		Set_FactoryModeFlag();
		Set_BurninModeFlag();
		#if !USEFLASH
		NVRam_WriteByte(nvrMonitorAddr(MonitorFlag), MonitorFlags);
		#else
		UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
		#endif
		Set_PowerOnFlag();
		Set_AutoColorFlag();
	}
}
#endif



#if HotInputSelect
Bool CheckSourceKeyStatus(void)
{
	BYTE keypadStatus;
	int i;
	if(UnsupportedModeFlag)
		return FALSE;
	for(i = 0; i < 33; i++) //  for(i=0;i<50;i++)
	{
		Delay1ms(50);
		keypadStatus = (Key_GetKeypadStatus()^KeypadMask)&KeypadMask;
		if (keypadStatus == KEY_EXIT)
		{
			SourceKeyCounter++;
			if(SourceKeyCounter > 30) //50
				break;
			else
				continue;
		}
		else
			break;
	}
	//printData("SourceKeyCounter  %d", SourceKeyCounter);
	return FALSE;
}
#endif


extern void Power_TurnOffLed(void);
extern void Power_TurnOnGreenLed(void);
extern Bool ExecuteKeyEvent(MenuItemActionType menuAction);
extern void Osd_Hide(void);
extern BYTE  xdata MenuPageIndex;


BOOL Key_ScanKeypad(void)
{
	BYTE keypadStatus = 0;
	if (gBoolVisualKey == 0)
	{
		keypadStatus = (Key_GetKeypadStatus() ^ KeypadMask) &KeypadMask;
		#if ENABLE_ANDROID_IR
		keypadStatus |= ( IR_GetIRKeypadStatus() ^ KeypadMask ) & KeypadMask;
		#endif
	}
	else if (gBoolVisualKey == 1)
	{
		gBoolVisualKey = 0;
		keypadStatus = (gByteVisualKey ^ KeypadMask) &KeypadMask;
	}
	#if ENABLE_DEBUG
	if(keypadStatus != 0)
	{
		printData("Kpd: keypadStatus = %x", keypadStatus);
//		KEYPAD_PrintData("Kpd: keypadStatus = %d",keypadStatus);
		KEYPAD_PrintData("Kpd: MenuPageIndex = %d", MenuPageIndex);
	}
	#endif
	if (keypadStatus)
	{
		{
			#if  (FEnterFunction==FEnter_POWER_MENU)||(FEnterFunction==FEnter_POWER_EXIT)
			if(keypadStatus == KEY_FACTORY && !PowerOnFlag)
			{
				Set_FactoryModeFlag();
				Set_BurninModeFlag();
				Set_DoBurninModeFlag();
				#if !USEFLASH
				NVRam_WriteByte(nvrMonitorAddr(MonitorFlag), MonitorFlags);
				#else
				UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
				#endif
				KeypadButton = BTN_Power;
			}
			else
			#endif
				if (keypadStatus == KEY_PLUS)
				{
					if (MenuPageIndex == RootMenu ) 	//120425 Modify
					{
						if (KeypadButton == BTN_Plus || KeypadButton == BTN_Repeat)
							KeypadButton = BTN_Repeat;
						else
							KeypadButton = BTN_Plus;
						Delay1ms(100);
					}
					else
						KeypadButton = BTN_Plus;
				}
				else if (keypadStatus == KEY_MINUS)
				{
					if (MenuPageIndex == RootMenu ) 	//120425 Modify
					{
						if (KeypadButton == BTN_Minus || KeypadButton == BTN_Repeat)
							KeypadButton = BTN_Repeat;
						else
							KeypadButton = BTN_Minus;
						Delay1ms(100);
					}
					else
						KeypadButton = BTN_Minus;
				}
				else if (keypadStatus == KEY_EXIT)
				{
					#if Enable_Exit_LongPressKeyFunction			////for long press key , if need ,please study
					if ( MenuPageIndex == RootMenu && KeypadButton == BTN_Nothing)
					{
						if ( g_HoldKeypadButton == BTN_Exit && g_HoldKeyCounter > 2 )
						{
							g_HoldKeyCounter = 0;
							g_HoldKeypadButton = BTN_EndBTN;
							KeypadButton = BTN_ExitPressKey;
						}
						else
						{
							//printData("KeypadButton==MINUS_1=", 1);
							if(g_HoldKeypadButton == BTN_EndBTN)
							{
								g_HoldKeypadButton = BTN_Exit;
							}
							KeypadButton = BTN_Nothing;
						}
					}
					else
					#endif
						if ((KeypadButton == BTN_Exit || KeypadButton == BTN_Repeat))
							KeypadButton = BTN_Repeat;
						else
						{
							KeypadButton = BTN_Exit;
						}
					Delay1ms ( 5 );
				}
				else if (keypadStatus == KEY_MENU)
				{
					{
						if(KeypadButton == BTN_Repeat || KeypadButton == BTN_Menu)
							KeypadButton = BTN_Repeat;
						else
						{
							KeypadButton = BTN_Menu;
						}
					}
					Delay1ms ( 5 );
				}
				else if (keypadStatus == KEY_POWER)
				{
					if (KeypadButton == BTN_Power || KeypadButton == BTN_Repeat)
					{
						KeypadButton = BTN_Repeat;
					}
					else
						KeypadButton = BTN_Power;
				}
				else
				{
					KeypadButton = BTN_Nothing;
				}
		}
	}
	else //check when key release
	{
		if (PowerKeyFlag)
		{
			Set_MainOSDFlag();
			KeypadButton = BTN_Power;
		}
		else
		{
			Clr_DoKeyCountFlag();
			PowerKeyCounter = 0;
		}
		#if Enable_ButtonKeyLongPressFunction//for long press key , if need ,please study
		if (MenuPageIndex == RootMenu)
		{
			if(g_HoldKeyCounter < 5)
			{
				#if Enable_Exit_LongPressKeyFunction
				if(g_HoldKeypadButton == BTN_Exit)
					KeypadButton = BTN_Exit;
				else
				#endif
					KeypadButton = BTN_Nothing;
			}
		}
		else
		{
			KeypadButton = BTN_Nothing;
		}
		g_HoldKeyCounter = 0;
		g_HoldKeypadButton = BTN_EndBTN;
		#else
		KeypadButton = BTN_Nothing;
		#endif
	}
	//printData("Kpd_End: KeypadButton = %d",KeypadButton);
	return TRUE;  ///  //// ///
}
#endif
#if 0
BYTE Key_GetKeypadStatus(void)  //charles
{
	BYTE keypad = 0xFF;
	BYTE temp, temp1, retry_Key;
	retry_Key = 5;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_A;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_A;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA // 090410
	if(temp < 60)
		printData("ADC2=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_NOTHING;
	else if(temp >= 0x40 && temp < 0x50)
		keypad &= ~KEY_NOTHING;
	else if(temp >= 0x68 && temp < 0x78)
		keypad &= ~KEY_MENU;
	retry_Key = 3;
	while (retry_Key)
	{
		temp = KEYPAD_ADC_B;
		Delay1ms(2);
		temp1 = KEYPAD_ADC_B;
		if (abs(temp - temp1) < 3)
			break;
		retry_Key--;
	}
	#if 0//DEBUG_PRINTDATA
	if(temp < 60)
		printData("ADC3=%d", temp);
	#endif
	if(  temp < 0x10 )
		keypad &= ~KEY_MINUS;
	else if(temp >= 0x40 && temp < 0x50)
		keypad &= ~KEY_PLUS;
	else if(temp >= 0x68 && temp < 0x78)
		keypad &= ~KEY_EXIT;
	if(PowerKey == 0 )
	{
		keypad &= ~KEY_POWER;
	}
	return keypad;
}
#endif
