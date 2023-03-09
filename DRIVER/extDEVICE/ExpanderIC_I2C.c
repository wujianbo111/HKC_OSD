/* ****************************************************************************/
#include <intrins.h>
#include "types.h"
#include "board.h"
//#include "DebugMsg.h"
#include "ms_reg.h"
#include "ms_rwreg.h"
#include "misc.h"
#include "I2c.h"
#include "Global.h"
#include "UartControl.h"


#if ENABLE_ExpanderIO

void IO_IICDelay(void)
{
	// 5: 62KHz
	#if  Enable_Cache
	BYTE xdata i;
	for(i = 0; i < 70; i++)
	{
		_nop_();
		_nop_();
	}
	#else
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	#endif
}

Bool IO_i2c_Start(void)
{
	IO_Set_i2c_SDA();
	IO_IICDelay();
	IO_Set_i2c_SCL();
	IO_IICDelay();
	if (IO_i2c_SDALo() || IO_i2c_SCLLo())
		return FALSE;
	IO_Clr_i2c_SDA();
	IO_IICDelay();
	IO_Clr_i2c_SCL();
	IO_IICDelay();
	return TRUE;
}

void IO_i2c_Stop(void)
{
	IO_Clr_i2c_SCL();
	IO_IICDelay();
	IO_Clr_i2c_SDA();
	IO_IICDelay();
	IO_Set_i2c_SCL();
	IO_IICDelay();
	IO_Set_i2c_SDA();
	IO_IICDelay();
}

Bool IO_WaitAck(void)
{
	BYTE xdata i;
	for(i = 0; i < 5; i++) // max.340us
	{
		if(IO_i2c_SDALo())
			return TRUE;
		IO_IICDelay();
	}
	return FALSE;
}

Bool IO_i2c_SendByte(BYTE value)
{
	BYTE xdata i;
	Bool xdata result;
	for (i = 0; i < 8; i++) // Send data via i2c pin
	{
		if (value & BIT7)
			IO_Set_i2c_SDA();
		else
			IO_Clr_i2c_SDA();
		IO_IICDelay();
		IO_Set_i2c_SCL();
		IO_IICDelay();
		value <<= 1;
		IO_Clr_i2c_SCL();
	}
	IO_Set_i2c_SDA();
	IO_IICDelay();
	result = IO_WaitAck(); // see if ACK
	IO_Set_i2c_SCL();
	IO_IICDelay();
	IO_Clr_i2c_SCL();
	IO_IICDelay();
	IO_Clr_i2c_SDA();
	return result;
}

BYTE IO_i2c_ReceiveByte(const Bool ack)
{
	BYTE xdata i;
	BYTE xdata value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		IO_Set_i2c_SDA();
		IO_IICDelay();
		IO_Set_i2c_SCL();
		IO_IICDelay();
		if (IO_i2c_SDAHi())
			value |= BIT0;
		IO_Clr_i2c_SCL();
	}
	if (ack)
	{
		IO_Clr_i2c_SDA();
	}
	else
	{
		IO_Set_i2c_SDA();
	}
	IO_IICDelay();
	IO_Set_i2c_SCL();
	IO_IICDelay();
	IO_Clr_i2c_SCL();
	return value;
}

Bool IO_i2c_MasterStart(I2C_Direction direct, BYTE addr)
{
	BYTE xdata retry = 3;
	if (direct == I2C_READ) // Set I2C direction bit.
		addr |= BIT0;
	else
		addr &= ~BIT0;
	while (retry--)
	{
		if (IO_i2c_Start() == FALSE)
		{
			IO_i2c_Stop();
			continue;
		}
		if (IO_i2c_SendByte(addr) == TRUE) // send address success
			return TRUE;
		IO_i2c_Stop();
		ForceDelay1ms(1);
	}
	return FALSE;
}

Bool IO_ReadByte( BYTE add, BYTE *val )
{
	if(IO_i2c_MasterStart(I2C_WRITE, ExpanderIO_ADDRESS) == FALSE)
		return FALSE;
	if(IO_i2c_SendByte(add) == FALSE)
		return FALSE;
	if(IO_i2c_MasterStart(I2C_READ, ExpanderIO_ADDRESS) == FALSE)
		return FALSE;
	*val = IO_i2c_ReceiveByte(0);
	IO_i2c_Stop();
	return TRUE;
}
Bool IO_WriteByte(BYTE addr, BYTE val)
{
	if(IO_i2c_MasterStart(I2C_WRITE, ExpanderIO_ADDRESS) == FALSE)
		return FALSE;
	if(IO_i2c_SendByte(addr) == FALSE)
	{
		return FALSE;
	}
	if(IO_i2c_SendByte(val) == FALSE)
	{
		//VCOM_i2c_Stop();
		return FALSE;
	}
	IO_i2c_Stop();
	return TRUE;
}

void Switch1_WriteByte( BYTE addr, BYTE value )
{
	Clr_ExpanderIOFlag();
	if (IO_WriteByte( addr,  value))
		Set_ExpanderIOFlag();
}

BYTE Switch1_ReadByte(BYTE addr)
{
	BYTE xdata ucValue;
	Clr_ExpanderIOFlag();
	if(IO_ReadByte(addr, &ucValue) == TRUE)
		Set_ExpanderIOFlag();
	return ucValue;
}

void Switch1_WriteByteMask( WORD addr, BYTE value, BYTE ucMask )
{
	BYTE xdata uc;
	uc = Switch1_ReadByte( addr);
	uc = uc & ( ~ucMask );
	Switch1_WriteByte( addr, ( uc | ( value & ucMask ) )  );
}
#endif




#if 0//defined(ENABLE_AUDIO_STA38X)

Bool AUDIO_ReadByte( BYTE add, BYTE *val )
{
	Clr_ExpanderIOFlag();
	if(IO_i2c_MasterStart(I2C_WRITE, AUDIO_DSP_ADDRESS) == FALSE)
		return FALSE;
	if(IO_i2c_SendByte(add) == FALSE)
		return FALSE;
	if(IO_i2c_MasterStart(I2C_READ, AUDIO_DSP_ADDRESS) == FALSE)
		return FALSE;
	*val = IO_i2c_ReceiveByte(0);
	IO_i2c_Stop();
	Set_ExpanderIOFlag();
	return TRUE;
}

Bool AUDIO_WriteByte(BYTE addr, BYTE val)
{
	Clr_ExpanderIOFlag();
	if(IO_i2c_MasterStart(I2C_WRITE, AUDIO_DSP_ADDRESS) == FALSE)
		return FALSE;
	if(IO_i2c_SendByte(addr) == FALSE)
	{
		return FALSE;
	}
	if(IO_i2c_SendByte(val) == FALSE)
	{
		//VCOM_i2c_Stop();
		return FALSE;
	}
	IO_i2c_Stop();
	Set_ExpanderIOFlag();
	return TRUE;
}

#endif
