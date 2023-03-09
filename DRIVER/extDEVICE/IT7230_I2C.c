
#include "global.h"

#if 0
#if (MS_PM) // 120525 coding, modified to avoid iic clock too slow
#define CPK_IIC_DELAY_COUNT     ((g_bMcuPMClock)?(2):(30))
#else
#define CPK_IIC_DELAY_COUNT     (30)
#endif

void CPK_IIC_Delay( void )
{
#message "please check touch key IIC clock speed"
	BYTE i;
	BYTE count = CPK_IIC_DELAY_COUNT;
	for( i = 0; i < count; i ++ ) // check iic clock freq
	{
		_nop_();
		_nop_();
		_nop_();
		_nop_();
	}
}

Bool Wait_SK_IIC_Ack( void )
{
	BYTE i;
	for( i = 0; i < 10; i++ )
	{
		if( HW_CPK_I2C_SDA_PIN_IS_LO() )
			return TRUE;
		CPK_IIC_Delay();
	}
	if( HW_CPK_I2C_SDA_PIN_IS_LO() )
		return TRUE;
	else
		return FALSE;
}

//////////////////////////////////////////////////////
// I2C start signal.
// <comment>
//  SCL ________
//              \_________
//  SDA _____
//           \____________
//
// Return value: None
//////////////////////////////////////////////////////
Bool CPK_I2C_Start( void )
{
	HW_SET_CPK_I2C_SDA_PIN();
	HW_SET_CPK_I2C_SCL_PIN();
	CPK_IIC_Delay();
	if( HW_CPK_I2C_SDA_PIN_IS_LO() || HW_CPK_I2C_SCL_PIN_IS_LO() )
		return FALSE;
	HW_CLR_CPK_I2C_SDA_PIN();
	CPK_IIC_Delay();
	HW_CLR_CPK_I2C_SCL_PIN();
	CPK_IIC_Delay();
	return TRUE;
}
/////////////////////////////////////////
// I2C stop signal.
// <comment>
//              ____________
//  SCL _______/
//                 _________
//  SDA __________/
/////////////////////////////////////////
// Setup i2c Stop condition
void CPK_I2C_Stop( void )
{
	// SCL=L, SDA=L, Stop condition.
	HW_CLR_CPK_I2C_SCL_PIN();
	HW_CLR_CPK_I2C_SDA_PIN();
	CPK_IIC_Delay();
	HW_SET_CPK_I2C_SCL_PIN();
	CPK_IIC_Delay();
	HW_SET_CPK_I2C_SDA_PIN();
	CPK_IIC_Delay();
	CPK_IIC_Delay();
}
//////////////////////////////////////////////////////////////////////////
// I2C send byte to device. (Non Salve Address)
//
// Arguments: ucVal - send byte
// Return value: I2C acknowledge bit
//               CPK_I2C_ACKNOWLEDGE/CPK_I2C_NON_ACKNOWLEDGE
//////////////////////////////////////////////////////////////////////////
Bool CPK_I2C_SendByte( BYTE value )
{
	BYTE i;
	Bool bresult;
	for( i = 0; i < 8; i++ ) // Send data via i2c pin
	{
		if( value & BIT7 )
			HW_SET_CPK_I2C_SDA_PIN();
		else
			HW_CLR_CPK_I2C_SDA_PIN();
		CPK_IIC_Delay();
		HW_SET_CPK_I2C_SCL_PIN();
		value <<= 1;
		CPK_IIC_Delay();
		HW_CLR_CPK_I2C_SCL_PIN();
	}
	HW_SET_CPK_I2C_SDA_PIN();
	CPK_IIC_Delay();
	bresult = Wait_SK_IIC_Ack();
	HW_SET_CPK_I2C_SCL_PIN();
	CPK_IIC_Delay();
	HW_CLR_CPK_I2C_SCL_PIN();
	CPK_IIC_Delay();
	HW_CLR_CPK_I2C_SDA_PIN();
	return bresult;
}
//////////////////////////////////////////////////////////////////////////
// I2C receive byte from device.
//
// Return value: receive byte
//////////////////////////////////////////////////////////////////////////
BYTE CPK_I2C_ReceiveByte( const Bool ack )
{
	BYTE i;
	BYTE value = 0;
	for( i = 0; i < 8; i++ )
	{
		value <<= 1;
		HW_SET_CPK_I2C_SDA_PIN();
		CPK_IIC_Delay();
		HW_SET_CPK_I2C_SCL_PIN();
		CPK_IIC_Delay();
		if( HW_CPK_I2C_SDA_PIN_IS_HI() )
			value |= BIT0;
		HW_CLR_CPK_I2C_SCL_PIN();
		CPK_IIC_Delay();
	}
	if( ack )
		HW_CLR_CPK_I2C_SDA_PIN();
	else
		HW_SET_CPK_I2C_SDA_PIN();
	CPK_IIC_Delay();
	HW_SET_CPK_I2C_SCL_PIN();
	CPK_IIC_Delay();
	HW_CLR_CPK_I2C_SCL_PIN();
	return value;
}

Bool CPK_I2C_BurstWrite( BYTE count, BYTE *buffer )
{
	while( count-- )
	{
		if( CPK_I2C_SendByte( *( buffer++ ) ) == FALSE )
		{
			CPK_I2C_Stop();
			return FALSE;
		}
	}
	return TRUE;
}
Bool CPK_I2C_BurstRead( BYTE count, BYTE * buffer )
{
	BYTE i;
	for( i = 0; i < count - 1; i++ )
		*( buffer + i ) = CPK_I2C_ReceiveByte( 1 );
	*( buffer + i ) = CPK_I2C_ReceiveByte( 0 );
	CPK_I2C_Stop();
	return TRUE;
}

Bool CPK_I2C_MasterStart( I2C_Direction direct, BYTE addr )
{
	if( direct == I2C_READ ) // Set I2C direction bit.
		addr |= BIT0;
	else
		addr &= ~BIT0;
	if( CPK_I2C_Start() == FALSE )
		return FALSE;
	if( CPK_I2C_SendByte( addr ) == TRUE ) // send address success
		return TRUE;
	CPK_I2C_Stop();
	return FALSE;
}

static void I2CInit(void)
{
	HW_SET_CPK_I2C_SCL_PIN();
	HW_SET_CPK_I2C_SDA_PIN();
	isInit = TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//------I2C bus hardware reset , Should be let SCL=0(low) over the 4ms.----//
/////////////////////////////////////////////////////////////////////////////
void IT7230_I2C_Reset(void)
{
	HW_SET_CPK_I2C_SCL_PIN();
	ForceDelay1ms(2);
	HW_CLR_CPK_I2C_SCL_PIN();
	ForceDelay1ms(6);
	HW_SET_CPK_I2C_SCL_PIN();
	ForceDelay1ms(2);
}

Bool IT7230_I2C_WriteWord(const BYTE registerStartAddr, const WORD WriteData)
{
	BYTE WriteDataArray[3];
	WriteDataArray[0] = registerStartAddr;
	WriteDataArray[1] = ( WriteData & 0x00FF );
	WriteDataArray[2] = ( WriteData & 0xFF00 ) >> 8;
	if (!isInit)
		I2CInit();
	if( CPK_I2C_MasterStart( I2C_WRITE, I2C_DEVICE_ADDR ) == FALSE )
		return FALSE;
	if( CPK_I2C_BurstWrite( 3, WriteDataArray ) == FALSE )
		return FALSE;
	CPK_I2C_Stop();
	return TRUE;
}

Bool IT7230_I2C_ReadWord(const BYTE registerStartAddr, WORD* recWord)
{
	#if 0
	BYTE WriteDataArray[2];
	WriteDataArray[0] = registerStartAddr;
	if (!isInit)
		I2CInit();
	if( CPK_I2C_MasterStart( I2C_WRITE, I2C_DEVICE_ADDR ) == FALSE )
		return FALSE;
	if( CPK_I2C_BurstWrite( 1, WriteDataArray ) == FALSE )
		return FALSE;
	if( CPK_I2C_MasterStart( I2C_READ, I2C_DEVICE_ADDR ) == FALSE )
		return FALSE;
	CPK_I2C_BurstRead(2, WriteDataArray);
	*recWord = (WORD)(WriteDataArray[1] << 8) | WriteDataArray[0];
	CPK_I2C_Stop();
	return TRUE;
	#else
	BYTE retry = 3;
	BYTE RegAddr = registerStartAddr;
	xdata BYTE tempbuf[2];
	if (!isInit)
		I2CInit();
	while( retry-- )
	{
		if( CPK_I2C_MasterStart( I2C_WRITE, I2C_DEVICE_ADDR ) == FALSE )
		{
			CPK_I2C_Stop();
			//ForceDelay1ms(5);
			continue;   //return FALSE;
		}
		if( CPK_I2C_BurstWrite( 1, &RegAddr ) == FALSE )
		{
			CPK_I2C_Stop();
			//ForceDelay1ms(5);
			continue;   //return FALSE;
		}
		if( CPK_I2C_MasterStart( I2C_READ, I2C_DEVICE_ADDR ) == FALSE )
		{
			CPK_I2C_Stop();
			//ForceDelay1ms(5);
			continue;   //return FALSE;
		}
		if( CPK_I2C_BurstRead( 2, tempbuf ) == FALSE )
		{
			CPK_I2C_Stop();
			//ForceDelay1ms(5);
			continue;   //return FALSE;
		}
		*recWord = ( WORD )tempbuf[1] << 8 | tempbuf[0];
		return TRUE;
	}
	return FALSE;
	#endif
}

Bool IT7230_I2C_Device_Addr_Check(void)
{
	if( CPK_I2C_MasterStart( I2C_WRITE, I2C_DEVICE_ADDR ) == FALSE )
		return FALSE;
	CPK_I2C_Stop();
	return TRUE;
}

#endif


