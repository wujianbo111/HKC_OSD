/******************************************************************************
 Copyright (c) 2008 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: CapactiveKeypad.h
 [Date]:        12-May-2008
 [Comment]:
   Capactive Keypad control header file.
 [Reversion History]:
*******************************************************************************/
#ifndef _ENE_I2C_H
#define _ENE_I2C_H

#include "i2cdef.h"
void CPK_IIC_Delay( void );
Bool Wait_SK_IIC_Ack( void );
Bool CPK_I2C_Start( void );
void CPK_I2C_Stop( void );
Bool CPK_I2C_SendByte( BYTE value );
BYTE CPK_I2C_ReceiveByte( const Bool ack );
Bool CPK_I2C_BurstWrite( BYTE count, BYTE *buffer );
Bool CPK_I2C_BurstRead( BYTE count, BYTE * buffer );
Bool CPK_I2C_MasterStart( I2C_Direction direct, BYTE addr );


#define I2C_DEVICE_ADR_WRITE(slave_adr)   	(slave_adr & ~_BIT0)
#define I2C_DEVICE_ADR_READ(slave_adr)    	(slave_adr | _BIT0)


#define CPK_I2C_ACKNOWLEDGE     		_LOW
#define CPK_I2C_NON_ACKNOWLEDGE 		_HIGH
#endif

