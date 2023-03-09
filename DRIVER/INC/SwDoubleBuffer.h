
#ifndef _SW_DOUBLE_BUFFER_H
#define _SW_DOUBLE_BUFFER_H

#ifdef _SW_DOUBLE_BUFFER_C
#define INTERFACE
#else
#define INTERFACE   extern
#endif

#define SWDB_MAX_SIZE  99

typedef struct
{
	BYTE ucSWDB_OnFire;
	BYTE ucSWDB_Mode;
	BYTE ucSWDB_Mode_Log;
	BYTE ucSWDB_LastSCBank;
	BYTE ucSWDB_Num;
	BYTE ucSWDB_Counter;
	BYTE ucSWDB_Buffer[SWDB_MAX_SIZE];
} StuSWDBCtrl;

typedef enum _DBTYPE
{
	eDB_NORMAL_MODE     = 0x00,
	eDB_SUCCESSIVE_MODE = 0x40,
	eDB_BURST_MODE      = 0x80,
} DB_TYPE;



INTERFACE void msSWDBInit(void);
INTERFACE void msSWDBMode(DB_TYPE type);
INTERFACE void msSWDBWriteByte(WORD wReg, BYTE ucVal);
INTERFACE void msSWDBWrite2Byte(WORD wReg, WORD wVal);
INTERFACE void msSWDBWrite3Byte(WORD wReg, DWORD dwValue);
INTERFACE void msSWDBWriteByteMask(WORD wReg, BYTE ucVal, BYTE ucMask);
INTERFACE void msSWDBWrite2ByteMask(WORD wReg, WORD wVal, WORD wMask);
#if ENABLE_SW_DOUBLE_BUFFER
INTERFACE void msSWDBWriteBit(WORD wReg, BOOL bBit, BYTE ucBitPos);
#endif
#if CHIP_ID == CHIP_TSUMF
INTERFACE void msSWDBWriteToRegisterByOsdEnd(void);
#endif
INTERFACE void msSWDBWriteToRegister(void);
INTERFACE void msSWDBWaitForRdy(void);

#undef INTERFACE

#endif
