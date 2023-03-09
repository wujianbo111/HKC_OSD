/******************************************************************************
 Copyright (c) 2008 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: CapactiveKeypad.h
 [Date]:        12-May-2008
 [Comment]:
   Capactive Keypad control header file.
 [Reversion History]:
*******************************************************************************/
#ifndef _CAPACTIVEKEYPADI2C_H_
#define _CAPACTIVEKEYPADI2C_H_

#include <i2cdef.h>

#ifdef __cplusplus
extern "C" {
#endif

void CPK_IIC_Delay( void );
Bool Wait_SK_IIC_Ack( void );
Bool CPK_I2C_Start( void );
void CPK_I2C_Stop( void );
Bool CPK_I2C_SendByte( BYTE value );
BYTE CPK_I2C_ReceiveByte( const Bool ack );
Bool CPK_I2C_BurstWrite( BYTE count, BYTE *buffer );
Bool CPK_I2C_BurstRead( BYTE count, BYTE * buffer );
Bool CPK_I2C_MasterStart( I2C_Direction direct, BYTE addr );

#ifdef __cplusplus
}   // extern "C"
#endif

#endif
