
#include "global.h"

#if 0
#if (MS_PM) // 120525 coding, modified to avoid iic clock too slow
#if ENE_IC_TYPE == SB357X
#define CPK_IIC_DELAY_COUNT     ((g_bMcuPMClock)?(2):(60))
#elif ENE_IC_TYPE == SB358X      //Moidfy By TPV EE Request 20150922
#define CPK_IIC_DELAY_COUNT     ((g_bMcuPMClock)?(2):(120))
#else
#define CPK_IIC_DELAY_COUNT     ((g_bMcuPMClock)?(2):(30))
#endif
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
			return FALSE;
		CPK_IIC_Delay();
	}
	if( HW_CPK_I2C_SDA_PIN_IS_LO() )
		return FALSE;
	else
		return TRUE;
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

BYTE CPK_I2C_ReceiveByte( BOOL bAck )
{
	BYTE ucReceive = 0;
	BYTE ucMask = 0x80;
	//CPK_I2C_SET_SDA(_HIGH);
	HW_SET_CPK_I2C_SDA_PIN();
	while( ucMask )
	{
		HW_SET_CPK_I2C_SCL_PIN();
		CPK_IIC_Delay();
		if( HW_CPK_I2C_SDA_PIN_IS_HI() )
			ucReceive |= ucMask;
		HW_CLR_CPK_I2C_SCL_PIN();
		CPK_IIC_Delay();
		ucMask >>= 1; // next
	} // while
	if( bAck ) // acknowledge
	{
		HW_CLR_CPK_I2C_SDA_PIN();
	}
	else // non-acknowledge
	{
		HW_SET_CPK_I2C_SDA_PIN();
	}
	CPK_IIC_Delay();
	HW_SET_CPK_I2C_SCL_PIN();
	CPK_IIC_Delay();
	HW_CLR_CPK_I2C_SCL_PIN();
	CPK_IIC_Delay();
	return ucReceive;
}


Bool CPK_I2C_BurstWrite( BYTE count, BYTE *buffer )
{
	while( count-- )
	{
		if( CPK_I2C_SendByte( *( buffer++ ) ) == TRUE )
		{
			//CPK_I2C_Stop();
			return TRUE;
		}
	}
	return FALSE;
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
	BYTE ucDummy; // loop dummy
	if( direct == I2C_READ ) // check i2c read or write
		addr = I2C_DEVICE_ADR_READ( addr ); // read
	else
		addr = I2C_DEVICE_ADR_WRITE( addr ); // write
	ucDummy = I2C_ACCESS_DUMMY_TIME;
	while( ucDummy-- )
	{
		if( CPK_I2C_Start() == FALSE )
		{
			Delay1ms( 1 );
			continue;
		}
		if( CPK_I2C_SendByte( addr ) == CPK_I2C_ACKNOWLEDGE ) // check acknowledge
			return TRUE;
		CPK_I2C_Stop();
		Delay1ms( 1 );
	} // while
	return FALSE;
}

#endif


