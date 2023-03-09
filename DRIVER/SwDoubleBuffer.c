
#include "global.h"

#if ENABLE_SW_DOUBLE_BUFFER

#define _SW_DOUBLE_BUFFER_C
#define DB_DEBUG    0
#if ENABLE_DEBUG&&DB_DEBUG
#define DB_DEBUG_printData(str, value)   printData(str, value)
#define DB_DEBUG_printMsg(str)           printMsg(str)
#else
#define DB_DEBUG_printData(str, value)
#define DB_DEBUG_printMsg(str)
#endif

enum
{
	SW_DB_SW_TRIG,
	SW_DB_OVSYNC_TRIG,
	SW_DB_IVSYNC_TRIG,
	SW_DB_OVDE_TRIG,
};

#if (CHIP_ID == CHIP_TSUMC) || (CHIP_ID == CHIP_TSUMD)||(CHIP_ID == CHIP_TSUM9)||(CHIP_ID == CHIP_TSUMF)
XDATA StuSWDBCtrl SWDBCtrl _at_ XDATA_SWDB_ADDR_START;
#else
XDATA StuSWDBCtrl SWDBCtrl _at_ (0x45FF - sizeof(StuSWDBCtrl));
#endif

#if (CHIP_ID == CHIP_TSUMF)
#define SW_DB_TRIG_MODE     SW_DB_OVSYNC_TRIG
#else
#define SW_DB_TRIG_MODE     SW_DB_OVDE_TRIG
#endif

void msSWDBInit(void)
{
	SWDBCtrl.ucSWDB_Mode = eDB_NORMAL_MODE;
	SWDBCtrl.ucSWDB_Mode_Log = eDB_NORMAL_MODE;
	SWDBCtrl.ucSWDB_Num = 1;
	SWDBCtrl.ucSWDB_Counter = 0;
	SWDBCtrl.ucSWDB_OnFire = 0;
	SWDBCtrl.ucSWDB_LastSCBank = 0xFF;
	msWriteByteMask(REG_3C25, SW_DB_TRIG_MODE << 4, BIT5 | BIT4);
	msWrite2ByteMask(REG_3C24, ((WORD)&SWDBCtrl.ucSWDB_Buffer[0]) & 0x7FF, 0x07FF);
	msWriteBit(REG_2B00, 0, BIT5);
}

void msSWDBWaitForRdy(void)
{
	XDATA BYTE dlycnt = 60;
	while(SWDBCtrl.ucSWDB_OnFire)
	{
		dlycnt--;
		if(!dlycnt)
		{
			DB_DEBUG_printMsg("ML Time out, switch to SW Trig Mode !!");
			msWriteByteMask(REG_3C25, SW_DB_SW_TRIG << 4, BIT5 | BIT4);
			msWriteByteMask(REG_3C25, BIT6, BIT6);
			while(SWDBCtrl.ucSWDB_OnFire);
			msWriteByteMask(REG_3C25, 0x00, 0xC0);
			msWriteByteMask(REG_3C25, SW_DB_TRIG_MODE << 4, BIT5 | BIT4);
			SWDBCtrl.ucSWDB_Counter = 0;
			SWDBCtrl.ucSWDB_OnFire = 0;
			break;
		}
		ForceDelay1ms(1);
	}
}

#if CHIP_ID==CHIP_TSUMF // TSUMF no VDE end trig source, instead by OSD_VDE_End sw polling & trigger
void msSWDBWriteToRegisterByOsdEnd(void)
{
	XDATA BYTE index;
	WORD retry = 0xffff;
	msSWDBWaitForRdy();
	if(SWDBCtrl.ucSWDB_Counter)
	{
		index = SWDBCtrl.ucSWDB_Counter;
		msWrite2ByteMask(REG_3C26, ((WORD)&SWDBCtrl.ucSWDB_Buffer[index - 1]) & 0x7FF, 0x07FF);
		msWriteByteMask(REG_3C25, SW_DB_SW_TRIG << 4, BIT5 | BIT4);
		// wait OSD VDE end
		while( retry-- && ( MEM_MSREAD_BYTE(REG_2B24)&BIT0 ) && !InputTimingChangeFlag );
		retry = 0xffff;
		while( retry-- && !( MEM_MSREAD_BYTE(REG_2B24)&BIT0 ) && !InputTimingChangeFlag );
		// SWDB sw trigger
		MEM_MSWRITE_BYTE(REG_3C25, MEM_MSREAD_BYTE(REG_3C25) | 0xC0);
		while(SWDBCtrl.ucSWDB_OnFire);
		msWriteByteMask(REG_3C25, 0x00, 0xC0);
		msWriteByteMask(REG_3C25, SW_DB_TRIG_MODE << 4, BIT5 | BIT4);
		SWDBCtrl.ucSWDB_Counter = 0;
		SWDBCtrl.ucSWDB_OnFire = 0;
	}
}
#endif


void msSWDBWriteToRegister(void)
{
	XDATA BYTE index;
	msSWDBWaitForRdy();
	if(SWDBCtrl.ucSWDB_Counter)
	{
		index = SWDBCtrl.ucSWDB_Counter;
		msWrite2ByteMask(REG_3C26, ((WORD)&SWDBCtrl.ucSWDB_Buffer[index - 1]) & 0x7FF, 0x07FF);
		SWDBCtrl.ucSWDB_OnFire = 1;
		msWriteByte(REG_3C25, msReadByte(REG_3C25) | 0xC0);
	}
}

void msSWDBMode(DB_TYPE type)
{
	SWDBCtrl.ucSWDB_Mode = type;
}

static BOOL msSWDBNewModeBufChk(WORD wReg)
{
	BOOL NewMode = FALSE;
	XDATA BYTE size = 4;
	if((SWDBCtrl.ucSWDB_Mode_Log != SWDBCtrl.ucSWDB_Mode)
	        || (SWDBCtrl.ucSWDB_Counter == 0))
	{
		NewMode = TRUE;
	}
	else
	{
		switch(SWDBCtrl.ucSWDB_Mode)
		{
			case eDB_SUCCESSIVE_MODE:
				if((wReg >> 8) != (SWDBCtrl.ucSWDB_Buffer[SWDBCtrl.ucSWDB_Num - 1] & 0x3F))
					NewMode = TRUE;
				break;
			case eDB_BURST_MODE:
				if(((wReg >> 8) != (SWDBCtrl.ucSWDB_Buffer[SWDBCtrl.ucSWDB_Num - 1] & 0x3F))
				        || ((wReg & 0xFF) != (SWDBCtrl.ucSWDB_Buffer[SWDBCtrl.ucSWDB_Num + 1])))
					NewMode = TRUE;
				break;
			default:
				break;
		}
	}
	// if buffer size is not large enough then write to register first
	if(SWDBCtrl.ucSWDB_Mode == eDB_NORMAL_MODE)
		size = 3;
	else if(SWDBCtrl.ucSWDB_Mode == eDB_SUCCESSIVE_MODE)
		size = NewMode ? 4 : 2;
	else if(SWDBCtrl.ucSWDB_Mode == eDB_BURST_MODE)
		size = NewMode ? 4 : 1;
	if( (SWDBCtrl.ucSWDB_Counter + size) >= SWDB_MAX_SIZE )
	{
		DB_DEBUG_printMsg("SWDB buffer is Full !!");
		msSWDBWriteToRegister();
		msSWDBWaitForRdy();
		NewMode = TRUE;
	}
	if(NewMode)
		SWDBCtrl.ucSWDB_Num = SWDBCtrl.ucSWDB_Counter + 1;
	return NewMode;
}
void msSWDBWriteByte(WORD wReg, BYTE ucValue)
{
	XDATA BYTE index, SWDBModeChg;
	XDATA BYTE SCBank, SCAddr, SCVal;
	msSWDBWaitForRdy();
	if( wReg & _BIT15 ) // Scaler bank
	{
		SCBank = (wReg >> 8) & 0x7F;
		SCAddr = (wReg & 0xFF);
		SCVal = ucValue;
		if(SWDBCtrl.ucSWDB_LastSCBank != SCBank)
		{
			SWDBCtrl.ucSWDB_LastSCBank = SCBank;
			msSWDBWriteByte(0x2F00, SCBank);
			msSWDBWriteByte(0x2F00 | SCAddr, SCVal);
		}
		else
			msSWDBWriteByte(0x2F00 | SCAddr, SCVal);
	}
	else
	{
		SWDBModeChg = msSWDBNewModeBufChk(wReg);
		index  = SWDBCtrl.ucSWDB_Counter;
		switch(SWDBCtrl.ucSWDB_Mode)
		{
			case eDB_NORMAL_MODE:
				SWDBCtrl.ucSWDB_Mode_Log = SWDBCtrl.ucSWDB_Mode;
				SWDBCtrl.ucSWDB_Buffer[index] = (wReg >> 8) | eDB_NORMAL_MODE;
				SWDBCtrl.ucSWDB_Buffer[index + 1] = (wReg & 0xFF);
				SWDBCtrl.ucSWDB_Buffer[index + 2] = ucValue;
				SWDBCtrl.ucSWDB_Counter += 3;
				break;
			case eDB_SUCCESSIVE_MODE:
				if(SWDBModeChg)
				{
					SWDBCtrl.ucSWDB_Mode_Log = SWDBCtrl.ucSWDB_Mode;
					SWDBCtrl.ucSWDB_Buffer[SWDBCtrl.ucSWDB_Num - 1] = (wReg >> 8) | eDB_SUCCESSIVE_MODE;
					SWDBCtrl.ucSWDB_Buffer[SWDBCtrl.ucSWDB_Num] = 0;
					SWDBCtrl.ucSWDB_Buffer[index + 2] = (wReg & 0xFF);
					SWDBCtrl.ucSWDB_Buffer[index + 3] = ucValue;
					SWDBCtrl.ucSWDB_Counter += 4;
				}
				else
				{
					SWDBCtrl.ucSWDB_Buffer[SWDBCtrl.ucSWDB_Num - 1] = (wReg >> 8) | eDB_SUCCESSIVE_MODE;
					SWDBCtrl.ucSWDB_Buffer[SWDBCtrl.ucSWDB_Num]++;
					SWDBCtrl.ucSWDB_Buffer[index ] = (wReg & 0xFF);
					SWDBCtrl.ucSWDB_Buffer[index + 1] = ucValue;
					SWDBCtrl.ucSWDB_Counter += 2;
				}
				break;
			case eDB_BURST_MODE:
				if(SWDBModeChg)
				{
					SWDBCtrl.ucSWDB_Mode_Log = SWDBCtrl.ucSWDB_Mode;
					SWDBCtrl.ucSWDB_Buffer[SWDBCtrl.ucSWDB_Num - 1] = (wReg >> 8) | eDB_BURST_MODE;
					SWDBCtrl.ucSWDB_Buffer[SWDBCtrl.ucSWDB_Num] = 0;
					SWDBCtrl.ucSWDB_Buffer[SWDBCtrl.ucSWDB_Num + 1] = (wReg & 0xFF);
					SWDBCtrl.ucSWDB_Buffer[index + 3] = ucValue;
					SWDBCtrl.ucSWDB_Counter += 4;
				}
				else
				{
					SWDBCtrl.ucSWDB_Buffer[SWDBCtrl.ucSWDB_Num - 1] = (wReg >> 8) | eDB_BURST_MODE;
					SWDBCtrl.ucSWDB_Buffer[SWDBCtrl.ucSWDB_Num]++;
					SWDBCtrl.ucSWDB_Buffer[SWDBCtrl.ucSWDB_Num + 1 ] = (wReg & 0xFF);
					SWDBCtrl.ucSWDB_Buffer[index] = ucValue;
					SWDBCtrl.ucSWDB_Counter += 1;
				}
				break;
		}
	}
}


void msSWDBWrite2Byte(WORD wReg, WORD wValue)
{
	msSWDBWriteByte(wReg, wValue );
	msSWDBWriteByte(wReg + 1, wValue >> 8);
}

void msSWDBWrite3Byte(WORD wReg, DWORD dwValue)
{
	msSWDBWrite2Byte( wReg, dwValue & 0xFFFF );
	msSWDBWriteByte( wReg + 2, ( BYTE )( dwValue >> 16 ) );
}

void msSWDBWriteByteMask(WORD wReg, BYTE ucVal, BYTE ucMask)
{
	msSWDBWriteByte(wReg, (msReadByte( wReg ) & ( ~ucMask ) ) | (ucVal & ucMask) );
}


void msSWDBWrite2ByteMask(WORD wReg, WORD wVal, WORD wMask)
{
	msSWDBWriteByteMask(wReg, (BYTE)wVal, (BYTE)wMask);
	msSWDBWriteByteMask(wReg + 1, (BYTE)(wVal >> 8), (BYTE)(wMask >> 8));
}

void msSWDBWriteBit(WORD wReg, BOOL bBit, BYTE ucBitPos)
{
	XDATA BYTE u8Value;
	u8Value = msReadByte( wReg );
	if( bBit )
	{
		u8Value = u8Value | ucBitPos;
	}
	else
	{
		u8Value = u8Value & ( ~ucBitPos );
	}
	msSWDBWriteByte( wReg, u8Value );
}
#endif

