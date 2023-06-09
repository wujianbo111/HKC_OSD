/******************************************************************************
 Copyright (c) 2004 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: Ir.c
 [Date]:        04-Feb-2004
 [Comment]:
   Remote control subroutines.
 [Reversion History]:
*******************************************************************************/
#include "board.h"
#if ENABLE_ANDROID_IR	//131008 Modify
#define _IR_C_

// System
#include <intrins.h>

// Internal
#include "drv_ir.h"
#include "Global.h"

extern void putSIOChar(unsigned char sendData);
extern void printData(char *str, WORD value);

extern xdata BYTE MenuItemIndex;

typedef enum
{
	IR_KEY_EXIT            	= ~BIT4,
	IR_KEY_MINUS           	= ~BIT1,
	IR_KEY_PLUS  		= ~BIT2,
	IR_KEY_MENU 		= ~BIT3,
	IR_KEY_POWER 		= ~BIT0,
	IR_KEY_SOURCE 		= ~BIT6,
	IR_KEY_NOTHING        = 0xFF
} IRKeypadType;

typedef enum
{
	#if ModelName==AOC_S23P
	IRKEY_POWER = 0x18
	#else
	IRKEY_POWER = 0x01
	#endif
};


BYTE code IRDecodeTable_Normal[] =
{
	IRKEY_POWER, IR_KEY_POWER,

	0xFF
};

BYTE code IRDecodeTable_OPlay[] =
{
	0xFF
};

#define IR_DEBOUNCE()   (IRstateLowCount>16 || IRstateHighCount>16)
#define IR_LEADER_CODE()   ((IRstateLowCount>40) && (IRstateHighCount>20))
#define IR_REPEAT_CODE()  ((IRstateLowCount>40) && (IRstateHighCount>8))
#define IR_DATA_CODE_1()  ((IRstateLowCount>=0) && (IRstateHighCount>6))
#define IR_DATA_CODE_0()  ((IRstateLowCount>=0) && (IRstateHighCount>1))
#define IR_DATA_COMPLETE()   (IR_Data_Count == 32)

void IR_INT1(void)
{
	#if 0
	BYTE test;
	test++;
	if(test % 2)
		hw_SetFlashWP();
	else
		hw_ClrFlashWP();
	#endif
	if(IR_DEBOUNCE())
		IR_Step = 0;
	switch(IR_Step)
	{
		case 0 :
			if(IR_LEADER_CODE())
			{
				IR_Step = 1;
				IR_Data_Count = 0;
				IR_TempValue.valDW = 0;
			}
			else if(IR_REPEAT_CODE() && IRCodeTranCompleteFlag)
			{
				IR_RepeatFlag ++;
			}
			break;
		case 1 :
			if(IR_DATA_CODE_1())
			{
				IR_TempValue.valDW = (IR_TempValue.valDW << 1) | 0x01;
				IR_Data_Count++;
			}
			else if(IR_DATA_CODE_0())
			{
				IR_TempValue.valDW = (IR_TempValue.valDW << 1);
				IR_Data_Count++;
			}
			if(IR_DATA_COMPLETE())
			{
				IR_Step = 0;
				#if 0//IR_ENABLE_DEBUG
				IR_DebugKey = IR_TempValue.valDW;
				#endif
				//if(IR_CUSTOM == IR_CUSTOM_CODE)
				//IR_GotKey = IR_TempValue.valB[1];
				IR_Value.valDW = IR_TempValue.valDW;
				//IR_Value.valB[2] = IR_TempValue.valB[2];
				IRCodeTranCompleteFlag = 0;
			}
			break;
	}
	IRstateHighCount = 0;
	IRstateLowCount = 0;
}


void IR_InitVariables(void)
{
	IRstateHighCount = 0;
	IRstateLowCount = 0;
	IR_Step = 0;
	#if IR_ENABLE_DEBUG
	IR_DebugKey = 0;
	#endif
	IRCodeTranCompleteFlag = 0;
}
void IR_Init(void)
{
	IR_InitVariables();
	//need modify
	#if (MainBoardType== MainBoard_6038_M0A || MainBoardType== MainBoard_7414_M0A)
	EXTINT1_EN_GPIO01(_ENABLE);  //set GPIO01 at input mode
	INT_IRQ_SOURCE_1_ENABLE(TRUE);
	INT_IRQ_SEL_HL_TRIGGER(TRUE);
	#endif
	/* -------------initialize Timer 1 -----------------------------*/
	// remove to set mcu clock for normal/PM should re-calculate value
	//Timer1_TH1 = PERIOD_200uS >> 8;
	//Timer1_TL1 = PERIOD_200uS & 0xFF;
	//TH1=Timer1_TH1;  //200us reload
	//TL1=Timer1_TL1;  //200us reload
	TMOD = 0x11;
	IT1 = 1; // edge trigger
	TR1 = 1;  // enable timer 1
	ET1 = 1;      //enable    TIMER1
	PX0 = 0; //
	PX1 = 1; //
	PT0 = 0; //
	PT1 = 1; //
	IP0 = IP0 | _BIT2 | _BIT3;
	IP1 = IP1 | _BIT2 | _BIT3;
}

BYTE IR_Decode(BYTE inputkey )
{
	BYTE i, temp;
	i = 0;
	temp = IR_KEY_NOTHING;
	{
		while(IRDecodeTable_Normal[i] != 0xFF)
		{
			if(IRDecodeTable_Normal[i] == inputkey)
			{
				temp = IRDecodeTable_Normal[i + 1];
				break;
			}
			i += 2;
		}
	}
	return temp;
}

BYTE IR_GetIRKeypadStatus( void )
{
	BYTE i, temp = IR_KEY_NOTHING;
	BYTE IR_CustomCodeHigh = 0, IR_CustomCodeLow = 0;
	BYTE IR_TransData, IR_TransDataH, IR_TransDataL, IR_GotKey = 0;
	IR_TransDataH = IR_Value.valB[0];
	IR_TransDataL = IR_Value.valB[1];
	if((IR_TransDataH << 8 | IR_TransDataL) == IR_CUSTOM_CODE)
	{
		IR_TransData = IR_Value.valB[2];
		for (i = 0; i < 8; i++)
		{
			IR_GotKey <<= 1;
			if (IR_TransData & BIT0)
			{
				IR_GotKey |= BIT0;
			}
			IR_TransData >>= 1;
		}
	}
	IRCodeTranCompleteFlag = 1;
	if(IR_GotKey)
	{
		temp = IR_Decode(IR_GotKey);
		IR_RepeatKey = temp;
		IR_GotKey = 0;
		IR_Value.valDW = 0;
	}
	else
	{
		IR_RepeatFlag = 0;
	}
	#if IR_ENABLE_DEBUG
	if(IR_DebugKey)
	{
		//printData("IR_CUSTOM CODE:%x", IR_CUSTOM);
		//printData("IR_DATA CODE:%x", IR_DATA);
		IR_DebugKey = 0;
	}
	if(temp != IR_KEY_NOTHING)
	{
		//printData("IR:%x", temp);
	}
	#endif
	return temp;
}
#if ModelName!=AOC_S23P
void IR_EXit(void)
{
	INT_IRQ_SOURCE_1_ENABLE(FALSE);
	INT_IRQ_SEL_HL_TRIGGER(FALSE);
	hw_SetIRSwitch();
}
#endif
#endif
