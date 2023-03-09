#include "types.h"
#include "i2cdef.h"
#include "board.h"
#include "debug.h"
#include "misc.h"
#include "global.h"
#include <math.h>
#include <intrins.h>
#include "GPIO_DEF.h"
#include "ms_reg.h"
#include "ms_rwreg.h"

#define i2cSlaveAddr(deviceID, addr)    deviceID|((addr>>8)<<1)
#define i2cWordAddr(addr)       		addr&0xFF

#define NVRAM_RETRY     2

#if	UseI2cByTableFunc

#include "GPIO_DEF.h"
#include "ms_reg.h"
#include "ms_rwreg.h"

#message "Çë×¢ÒâÅäÖÃ I2C IO¿Ú"

#if CHIP_ID>=CHIP_TSUMV
#define FREE_I2C_PIN_IOO		_REG_GPIO2_OUT
#define FREE_I2C_PIN_IOI			_REG_GPIO2_IN
#define FREE_I2C_PIN_OEZ		_REG_GPIO2_OEZ
#define FREE_I2C_PIN_ADD		_BIT0
#else
#define FREE_I2C_PIN_IOO		_REG_GPIO2_OUT
#define FREE_I2C_PIN_IOI			_REG_GPIO2_IN
#define FREE_I2C_PIN_OEZ		_REG_GPIO2_OEZ
#define FREE_I2C_PIN_ADD		_BIT0
#endif


#if CHIP_ID>=CHIP_TSUMV


//1  A  41 40 D0 35 34 D1 33 32
WORD code  IOO_REGADD[] =
{
	#if I2C_GPIO40_41
	(_REG_GPIO4_OUT),
	#endif
	#if I2C_GPIO34_35
	(_REG_GPIO3_OUT),
	#endif
	#if I2C_GPIO32_33
	(_REG_GPIO3_OUT),
	#endif
	(FREE_I2C_PIN_IOO),
};
WORD code  IOI_REGADD[] =
{
	#if I2C_GPIO40_41
	(_REG_GPIO4_IN),
	#endif
	#if I2C_GPIO34_35
	(_REG_GPIO3_IN),
	#endif
	#if I2C_GPIO32_33
	(_REG_GPIO3_IN),
	#endif
	(FREE_I2C_PIN_IOI),
};

BYTE code IO_bit_SDA[] =
{
	#if I2C_GPIO40_41
	(_BIT1),
	#endif
	#if I2C_GPIO34_35
	(_BIT5),
	#endif
	#if I2C_GPIO32_33
	(_BIT3),
	#endif
	(FREE_I2C_PIN_ADD),
};
BYTE code IO_bit_SCL[] =
{
	#if I2C_GPIO40_41
	(_BIT0),
	#endif
	#if I2C_GPIO34_35
	(_BIT4),
	#endif
	#if I2C_GPIO32_33
	(_BIT2),
	#endif
	(FREE_I2C_PIN_ADD),
};
WORD code  IOEZ_REGADD[] =
{
	#if I2C_GPIO40_41
	(_REG_GPIO4_OEZ),
	#endif
	#if I2C_GPIO34_35
	(_REG_GPIO3_OEZ),
	#endif
	#if I2C_GPIO32_33
	(_REG_GPIO3_OEZ),
	#endif
	(FREE_I2C_PIN_OEZ),
};


#else


//1   A 22 21  D0	 13 12 		D1  17 16   D2  11 10
WORD code  IOO_REGADD[] =
{
	#if I2C_GPIO21_22
	(_REG_PMGPIO2_OUT),//A0
	#endif
	#if I2C_GPIO12_13
	(_REG_PMGPIO1_OUT),//D0
	#endif
	#if I2C_GPIO16_17
	(_REG_PMGPIO1_OUT),//D1
	#endif
	#if I2C_GPIO10_11
	(_REG_PMGPIO1_OUT),//D2
	#endif
	(FREE_I2C_PIN_IOO),	//N/A
};
WORD code  IOI_REGADD[] =
{
	#if I2C_GPIO21_22
	(_REG_PMGPIO2_IN),
	#endif
	#if I2C_GPIO12_13
	(_REG_PMGPIO1_IN),
	#endif
	#if I2C_GPIO16_17
	(_REG_PMGPIO1_IN),
	#endif
	#if I2C_GPIO10_11
	(_REG_PMGPIO1_IN),
	#endif
	(FREE_I2C_PIN_IOI),
};

BYTE code IO_bit_SDA[] =
{
	#if I2C_GPIO21_22
	(_BIT2),
	#endif
	#if I2C_GPIO12_13
	(_BIT3),
	#endif
	#if I2C_GPIO16_17
	(_BIT7),
	#endif
	#if I2C_GPIO10_11
	(_BIT1),
	#endif
	(FREE_I2C_PIN_ADD),
};
BYTE code IO_bit_SCL[] =
{
	#if I2C_GPIO21_22
	(_BIT1),
	#endif
	#if I2C_GPIO12_13
	(_BIT2),
	#endif
	#if I2C_GPIO16_17
	(_BIT6),
	#endif
	#if I2C_GPIO10_11
	(_BIT0),
	#endif
	(FREE_I2C_PIN_ADD),
};
WORD code  IOEZ_REGADD[] =
{
	#if I2C_GPIO21_22
	(_REG_PMGPIO2_OEZ),
	#endif
	#if I2C_GPIO12_13
	(_REG_PMGPIO1_OEZ),
	#endif
	#if I2C_GPIO16_17
	(_REG_PMGPIO1_OEZ),
	#endif
	#if I2C_GPIO10_11
	(_REG_PMGPIO1_OEZ),
	#endif
	(FREE_I2C_PIN_OEZ),
};


#endif

#define Set_NVRAM_i2c_SDA()		    		(MEM_MSWRITE_BIT(IOEZ_REGADD[EnableReadDDCType], TRUE, IO_bit_SDA[EnableReadDDCType]))
#define Clr_NVRAM_i2c_SDA()		    		(MEM_MSWRITE_BIT(IOO_REGADD[EnableReadDDCType], FALSE, IO_bit_SDA[EnableReadDDCType]),\
        MEM_MSWRITE_BIT(IOEZ_REGADD[EnableReadDDCType], FALSE, IO_bit_SDA[EnableReadDDCType]))
#define NVRAM_i2c_SDA_IS_HI()		    	(MEM_MSREAD_BYTE(IOI_REGADD[EnableReadDDCType])&IO_bit_SDA[EnableReadDDCType])
#define NVRAM_i2c_SDA_IS_LO()		    	(!NVRAM_i2c_SDA_IS_HI())


#define Set_NVRAM_i2c_SCL()		    		(MEM_MSWRITE_BIT(IOEZ_REGADD[EnableReadDDCType], TRUE, IO_bit_SCL[EnableReadDDCType]))
#define Clr_NVRAM_i2c_SCL()		    		(MEM_MSWRITE_BIT(IOO_REGADD[EnableReadDDCType], FALSE, IO_bit_SCL[EnableReadDDCType]),\
        MEM_MSWRITE_BIT(IOEZ_REGADD[EnableReadDDCType], FALSE, IO_bit_SCL[EnableReadDDCType]))
#define NVRAM_i2c_SCL_IS_HI()		   	(MEM_MSREAD_BYTE(IOI_REGADD[EnableReadDDCType])&IO_bit_SCL[EnableReadDDCType])
#define NVRAM_i2c_SCL_IS_LO()			(!NVRAM_i2c_SCL_IS_HI())


//3  ¡ä?¡¤?¡¤¡§2?¨ª¡§
/*
#define Set_NVRAM_i2c_SDA()		    		(MEM_MSWRITE_BIT(IOO_REGADD[EnableReadDDCType], TRUE, IO_bit_SDA[EnableReadDDCType]))
#define Clr_NVRAM_i2c_SDA()		    		(MEM_MSWRITE_BIT(IOO_REGADD[EnableReadDDCType], FALSE, IO_bit_SDA[EnableReadDDCType]))
#define NVRAM_i2c_SDA_IS_HI()		    	(MEM_MSREAD_BYTE(IOI_REGADD[EnableReadDDCType])&IO_bit_SDA[EnableReadDDCType])
#define NVRAM_i2c_SDA_IS_LO()		    	(!NVRAM_i2c_SDA_IS_HI())

#define Set_NVRAM_i2c_SCL()		    		(MEM_MSWRITE_BIT(IOO_REGADD[EnableReadDDCType], TRUE, IO_bit_SCL[EnableReadDDCType]))
#define Clr_NVRAM_i2c_SCL()		    		(MEM_MSWRITE_BIT(IOO_REGADD[EnableReadDDCType], FALSE, IO_bit_SCL[EnableReadDDCType]))
#define NVRAM_i2c_SCL_IS_HI()		   	(MEM_MSREAD_BYTE(IOI_REGADD[EnableReadDDCType])&IO_bit_SCL[EnableReadDDCType])
#define NVRAM_i2c_SCL_IS_LO()			(!NVRAM_i2c_SCL_IS_HI())
*/

#endif






#if 0//!USEFLASH  || (defined(UseVGACableReadWriteAllPortsEDID)&&!defined(ReduceDDC)) && !((CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF) && ENABLE_CABLE_5V_EDID)
#define I2C_CHECK	1

#if I2C_CHECK
#define I2C_CHECK_PIN_DUMMY	500//150//100  

void i2cSCL_Chk(void)
{
	BYTE ucDummy = I2C_CHECK_PIN_DUMMY; // initialize dummy
	while (i2c_SCLLo() && (ucDummy--))
		; // check SCL pull high
}
#else
#define i2cSCL_Chk()
#endif

Bool CheckIICAck(void)
{
	BYTE i;
	for(i = 0; i < 100; i++)
	{
		if(i2c_SDALo())
			return TRUE;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
	}
	if(i2c_SDALo())
		return TRUE;
	else
		return FALSE;
}

//====================================
// Setup i2c Start condition
Bool i2c_Start(void)
{
	Set_i2c_SDA();
	Delay4us();
	Set_i2c_SCL();
	Delay4us();
	i2cSCL_Chk();
	if (i2c_SDALo() || i2c_SCLLo())
		return FALSE;
	Clr_i2c_SDA();
	Delay4us();
	Clr_i2c_SCL();
	return TRUE;
}
//=============================================
// Setup i2c Stop condition
void i2c_Stop(void)
{
	// SCL=L, SDA=L, Stop condition.
	Clr_i2c_SCL();
	Delay4us();
	Clr_i2c_SDA();
	Delay4us();
	Set_i2c_SCL();
	Delay4us();
	i2cSCL_Chk();
	Set_i2c_SDA();
}

//============================================
Bool i2c_SendByte(BYTE value)
{
	BYTE i;
	Bool result;
	for (i = 0; i < 8; i++) // Send data via i2c pin
	{
		if (value & BIT7)
			Set_i2c_SDA();
		else
			Clr_i2c_SDA();
		Delay4us();
		Set_i2c_SCL();
		i2cSCL_Chk();
		value <<= 1;
		Clr_i2c_SCL();
	}
	Set_i2c_SDA();
	Delay4us();
	result = CheckIICAck();
	Set_i2c_SCL();
	i2cSCL_Chk();
	Clr_i2c_SCL();
	Delay4us();
	Clr_i2c_SDA();
	return result;
}

//============================================
BYTE i2c_ReceiveByte(const Bool ack)
{
	BYTE i;
	BYTE value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		Set_i2c_SDA();
		#if Enable_Cache// 090417
		Delay4us();
		#endif
		Set_i2c_SCL();
		Delay4us();
		i2cSCL_Chk();
		if (i2c_SDAHi())
			value |= BIT0;
		Clr_i2c_SCL();
	}
	if (ack)
		Clr_i2c_SDA();
	else
		Set_i2c_SDA();
	Delay4us();
	Set_i2c_SCL();
	Delay4us();
	i2cSCL_Chk();
	Clr_i2c_SCL();
	return value;
}
#if (defined(UseVGACableReadWriteAllPortsEDID)&&!defined(ReduceDDC)) //!USEFLASH
Bool i2c_BurstWrite(BYTE count, BYTE *buffer)
{
	while (count--)
	{
		if (i2c_SendByte(*(buffer++)) == FALSE)
			return FALSE;
	}
	return TRUE;
}
Bool i2c_BurstRead(BYTE count, BYTE * buffer)
{
	BYTE i;
	for (i = 0; i < count - 1; i++)
		*(buffer + i) = i2c_ReceiveByte(1);
	*(buffer + i) = i2c_ReceiveByte(0);
	i2c_Stop();
	return TRUE;
}
#endif
// 090413 modified for iic
Bool i2c_MasterStart(I2C_Direction direct, BYTE addr)
{
	BYTE retry = NVRAM_RETRY;
	if (direct == I2C_READ) // Set I2C direction bit.
		addr |= BIT0;
	else
		addr &= ~BIT0;
	while (retry--)
	{
		if (i2c_Start() == FALSE)
			continue;
		if (i2c_SendByte(addr) == TRUE) // send address success
			return TRUE;
		i2c_Stop();
		ForceDelay1ms(2);
	}
	return FALSE;
}

#if (defined(UseVGACableReadWriteAllPortsEDID)&&(!defined(ReduceDDC)))
#define	PageWriteLength		((LoadEDIDSelectPort<EEPROM)?8:16)
#define	PageWriteDelayTime		((LoadEDIDSelectPort<EEPROM)?3:12) //edit by lizzie,100429.for the problem: use HDMI/VGA Cable write all port EDID ,the time to write 32byte is too long
//ATMEL 24C02 Page Write Buffer is 8 Bytes.
//MicroChip 24C02 Page Write Buffer is 16 Bytes.
//ST 24C02 Page Write Buffer is 16 Bytes.
#else
#define	PageWriteLength		16
#define	PageWriteDelayTime	12 //edit by lizzie,100429.for the problem: use HDMI/VGA Cable write all port EDID ,the time to write 32byte is too long
#endif
#if (defined(UseVGACableReadWriteAllPortsEDID)&&!defined(ReduceDDC))
#if 0//def WH_REQUEST
#if ENABLE_HDMI
void i2c_WriteTBL(BYTE deviceID, WORD addr, BYTE *buffer, WORD count)
#else
void i2c_WriteTBL(BYTE deviceID, WORD addr, BYTE *buffer, BYTE count)
#endif
#else
void i2c_WriteTBL(BYTE deviceID, WORD addr, BYTE *buffer, BYTE count)
#endif
{
	BYTE slaveAddr;
	BYTE wordAddr;
	BYTE offset = 0;
	BYTE tempSize;
	Bool succ = TRUE;
	while (count)
	{
		slaveAddr = i2cSlaveAddr(deviceID, addr + offset);
		wordAddr = i2cWordAddr(addr + offset);
		if (i2c_MasterStart(I2C_WRITE, slaveAddr) == FALSE)
			break;
		if (i2c_BurstWrite(1, &wordAddr) == FALSE)
			break;
		tempSize = PageWriteLength - (wordAddr & (PageWriteLength - 1)); //0x10-(wordAddr&0xF);
		if (count > tempSize)
		{
			if (i2c_BurstWrite(tempSize, (BYTE*)(buffer + offset)) == FALSE)
				break;
			i2c_Stop();
			count -= tempSize;
			offset += tempSize;
		}
		else if (count > PageWriteLength) //0x10)
		{
			if (i2c_BurstWrite(0x10, (BYTE*)(buffer + offset)) == FALSE)
				break;
			i2c_Stop();
			count -= PageWriteLength; //0x10;
			offset += PageWriteLength; //0x10;
		}
		else
		{
			if (i2c_BurstWrite(count, (BYTE*)(buffer + offset)) == FALSE)
				break;
			i2c_Stop();
			count = 0;
		}
		ForceDelay1ms(PageWriteDelayTime);//edit by lizzie,100429.for the problem: use HDMI/VGA Cable write all port EDID ,the time to write 32byte is too long
	}
	i2c_Stop();
}

void i2c_ReadTBL(BYTE deviceID, WORD addr, BYTE *buffer, BYTE count)
{
	WORD retry = NVRAM_RETRY;
	BYTE slaveAddr;
	BYTE wordAddr;
	slaveAddr = i2cSlaveAddr(deviceID, addr);
	wordAddr = i2cWordAddr(addr);
	while (retry--)
	{
		if (i2c_MasterStart(I2C_WRITE, slaveAddr) == FALSE)
			continue;
		if (i2c_BurstWrite(1, &wordAddr) == FALSE)
			continue;
		if (i2c_MasterStart(I2C_READ, slaveAddr) == FALSE)
			continue;
		if (i2c_BurstRead(count, buffer) == FALSE)
			continue;
		return;
	}
}
#endif
//2004/02/20 num4--Start



#endif





#if 0//!USEFLASH
void NVRAM_i2c_Delay(void)
{
	BYTE i;
	for(i = 0; i < 100; i++) // 100: 59K
		_nop_();
}
void NVRAM_i2C_Intial(void)
{
	BYTE i;
	Set_NVRAM_i2c_SDA();
	NVRAM_i2c_Delay();
	Set_NVRAM_i2c_SCL();
	NVRAM_i2c_Delay();
	for(i = 0; i < 10; i++)
	{
		Set_NVRAM_i2c_SCL();
		NVRAM_i2c_Delay();
		Clr_NVRAM_i2c_SDA();
		NVRAM_i2c_Delay();
		Clr_NVRAM_i2c_SCL();
		NVRAM_i2c_Delay();
		Set_NVRAM_i2c_SCL();
		NVRAM_i2c_Delay();
		Set_NVRAM_i2c_SDA();
		NVRAM_i2c_Delay();
	}
	while(i++ < 100)
	{
		if(NVRAM_i2c_SDA_IS_HI())
			break;
		Set_NVRAM_i2c_SCL();
		NVRAM_i2c_Delay();
		Clr_NVRAM_i2c_SDA();
		NVRAM_i2c_Delay();
		Clr_NVRAM_i2c_SCL();
		NVRAM_i2c_Delay();
		Set_NVRAM_i2c_SCL();
		NVRAM_i2c_Delay();
		Set_NVRAM_i2c_SDA();
		NVRAM_i2c_Delay();
	}
}


#define NVRAM_I2C_CHECK	0

#if NVRAM_I2C_CHECK
#define NVRAM_I2C_CHECK_PIN_DUMMY	500//150//100  

void NVRAM_i2cSCL_Chk(void)
{
	BYTE ucDummy = NVRAM_I2C_CHECK_PIN_DUMMY; // initialize dummy
	while (NVRAM_i2c_SCL_IS_LO() && (ucDummy--))
		; // check SCL pull high
}
#else
#define NVRAM_i2cSCL_Chk()
#endif


Bool NVRAM_CheckIICAck(void)
{
	BYTE i;
	for(i = 0; i < 100; i++)
	{
		if(NVRAM_i2c_SDA_IS_LO())
			return TRUE;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
	}
	if(NVRAM_i2c_SDA_IS_LO())
		return TRUE;
	else
		return FALSE;
}

//====================================
// Setup i2c Start condition
Bool NVRAM_i2c_Start(void)
{
	Set_NVRAM_i2c_SDA();
	NVRAM_i2c_Delay();
	Set_NVRAM_i2c_SCL();
	NVRAM_i2c_Delay();
	NVRAM_i2cSCL_Chk();
	if (NVRAM_i2c_SDA_IS_LO() || NVRAM_i2c_SCL_IS_LO())
		return FALSE;
	Clr_NVRAM_i2c_SDA();
	NVRAM_i2c_Delay();
	Clr_NVRAM_i2c_SCL();
	return TRUE;
}
//=============================================
// Setup i2c Stop condition
void NVRAM_i2c_Stop(void)
{
	// SCL=L, SDA=L, Stop condition.
	Clr_NVRAM_i2c_SCL();
	NVRAM_i2c_Delay();
	Clr_NVRAM_i2c_SDA();
	NVRAM_i2c_Delay();
	Set_NVRAM_i2c_SCL();
	NVRAM_i2c_Delay();
	NVRAM_i2cSCL_Chk();
	Set_NVRAM_i2c_SDA();
}

//============================================
Bool NVRAM_i2c_SendByte(BYTE value)
{
	BYTE i;
	Bool result;
	for (i = 0; i < 8; i++) // Send data via i2c pin
	{
		if (value & BIT7)
			Set_NVRAM_i2c_SDA();
		else
			Clr_NVRAM_i2c_SDA();
		NVRAM_i2c_Delay();
		Set_NVRAM_i2c_SCL();
		NVRAM_i2c_Delay();
		NVRAM_i2cSCL_Chk();
		value <<= 1;
		Clr_NVRAM_i2c_SCL();
	}
	Set_NVRAM_i2c_SDA();
	NVRAM_i2c_Delay();
	result = NVRAM_CheckIICAck();
	Set_NVRAM_i2c_SCL();
	NVRAM_i2c_Delay();
	NVRAM_i2cSCL_Chk();
	Clr_NVRAM_i2c_SCL();
	NVRAM_i2c_Delay();
	Clr_NVRAM_i2c_SDA();
	return result;
}

//============================================
BYTE NVRAM_i2c_ReceiveByte(const Bool ack)
{
	BYTE i;
	BYTE value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		Set_NVRAM_i2c_SDA();
		#if Enable_Cache// 090417
		NVRAM_i2c_Delay();
		#endif
		Set_NVRAM_i2c_SCL();
		NVRAM_i2c_Delay();
		NVRAM_i2cSCL_Chk();
		if (NVRAM_i2c_SDA_IS_HI())
			value |= BIT0;
		Clr_NVRAM_i2c_SCL();
	}
	if (ack)
		Clr_NVRAM_i2c_SDA();
	else
		Set_NVRAM_i2c_SDA();
	NVRAM_i2c_Delay();
	Set_NVRAM_i2c_SCL();
	NVRAM_i2c_Delay();
	NVRAM_i2cSCL_Chk();
	Clr_NVRAM_i2c_SCL();
	return value;
}

Bool NVRAM_i2c_MasterStart(I2C_Direction direct, BYTE addr)
{
	BYTE retry = NVRAM_RETRY;
	if (direct == I2C_READ) // Set I2C direction bit.
		addr |= BIT0;
	else
		addr &= ~BIT0;
	while (retry--)
	{
		if (NVRAM_i2c_Start() == FALSE)
			continue;
		if (NVRAM_i2c_SendByte(addr) == TRUE) // send address success
		{
			//printMsg("SendByte TRUE");
			return TRUE;
		}
		NVRAM_i2c_Stop();
		//printMsg("SendByte Fail");
		ForceDelay1ms(2);
	}
	return FALSE;
}

#if EEPROM_TYPE >= EEPROM_24C32
#define	NVRAMPageWriteLength		32
#else
#define	NVRAMPageWriteLength		16
#endif
#define	NVRAMPageWriteDelayTime	12 //edit by lizzie,100429.for the problem: use HDMI/VGA Cable write all port EDID ,the time to write 32byte is too long

#if EEPROM_TYPE >= EEPROM_24C32
void rmSWPageWrite(WORD wIndex, BYTE *pBuf, BYTE ucBufLen)
{
	BYTE ucDummy; // loop dummy
	//CHECK_PROTECT;
	ucDummy = NVRAM_RETRY;
	while(ucDummy--)
	{
		if (NVRAM_i2c_MasterStart(I2C_WRITE, 0xA0) == FALSE)
			continue;
		if (NVRAM_i2c_SendByte(HIBYTE(wIndex)) == FALSE) // check non-acknowledge
			continue;
		if (NVRAM_i2c_SendByte(LOBYTE(wIndex)) == FALSE) // check non-acknowledge
			continue;
		while(ucBufLen--) // loop of writting data
		{
			NVRAM_i2c_SendByte(*pBuf); // send byte
			pBuf++; // next byte pointer
		} // while
		break;
	} // while
	NVRAM_i2c_Stop();
}

void rmSWBurstReadBytes(WORD wIndex, BYTE *pBuf, BYTE ucBufLen)
{
	BYTE ucDummy; // loop dummy
	ucDummy = NVRAM_RETRY;
	while(ucDummy--)
	{
		if (NVRAM_i2c_MasterStart(I2C_WRITE, 0xA0) == FALSE)
			continue;
		if (NVRAM_i2c_SendByte(HIBYTE(wIndex)) == FALSE) // check non-acknowledge
			continue;
		if (NVRAM_i2c_SendByte(LOBYTE(wIndex)) == FALSE) // check non-acknowledge
			continue;
		if (NVRAM_i2c_MasterStart(I2C_READ, 0xA0) == FALSE)
			continue;
		while(ucBufLen) // loop to burst read
		{
			ucBufLen--;
			*pBuf = NVRAM_i2c_ReceiveByte(ucBufLen); // receive byte
			pBuf++; // next byte pointer
		} // while
		break;
	} // while
	NVRAM_i2c_Stop();
	while(ucBufLen--) // if read error, fill 0xff
	{
		*pBuf = 0xff; // clear
		pBuf++; // next byte pointer
	} // while
}

void rmBurstWriteBytes(WORD wIndex, BYTE *pBuf, WORD ucBufLen)
{
	BYTE ucWriteCount; // write counter
	BYTE ucRemainLen; // i2c word address
	//CHECK_PROTECT;
	while(1)
	{
		// check page write roll over
		if (ucBufLen > NVRAMPageWriteLength)
			ucWriteCount = NVRAMPageWriteLength;
		else
			ucWriteCount = ucBufLen;
		// check word address higher than page write bits
		ucRemainLen = LOBYTE(wIndex) % NVRAMPageWriteLength;
		if (ucRemainLen) // check ramain
		{
			ucRemainLen = NVRAMPageWriteLength - ucRemainLen;
			if (ucWriteCount > ucRemainLen) // check not roll over
				ucWriteCount = ucRemainLen;
		}
		// EEPROM page write
		rmSWPageWrite(wIndex, pBuf, ucWriteCount);
		// check end of buffer
		ucBufLen -= ucWriteCount;
		if (ucBufLen == 0)
			break;
		wIndex += ucWriteCount; // next word address
		pBuf += ucWriteCount; // next buffer pointer
		ForceDelay1ms(NVRAMPageWriteDelayTime);//edit by lizzie,100429.for the problem: use HDMI/VGA Cable write all port EDID ,the time to write 32byte is too long
	} // while
}
#else
Bool NVRAM_i2c_BurstWrite(BYTE count, BYTE *buffer)
{
	while (count--)
	{
		if (NVRAM_i2c_SendByte(*(buffer++)) == FALSE)
			return FALSE;
	}
	return TRUE;
}

Bool NVRAM_i2c_BurstRead(BYTE count, BYTE * buffer)
{
	BYTE i;
	for (i = 0; i < count - 1; i++)
		*(buffer + i) = NVRAM_i2c_ReceiveByte(1);
	*(buffer + i) = NVRAM_i2c_ReceiveByte(0);
	NVRAM_i2c_Stop();
	return TRUE;
}

void NVRAM_i2c_WriteTBL(BYTE deviceID, WORD addr, BYTE *buffer, BYTE count)
{
	BYTE slaveAddr;
	BYTE wordAddr;
	BYTE offset = 0;
	BYTE tempSize;
	Bool succ = TRUE;
	while (count)
	{
		slaveAddr = i2cSlaveAddr(deviceID, addr + offset);
		wordAddr = i2cWordAddr(addr + offset);
		if (NVRAM_i2c_MasterStart(I2C_WRITE, slaveAddr) == FALSE)
			break;
		if (NVRAM_i2c_BurstWrite(1, &wordAddr) == FALSE)
			break;
		tempSize = NVRAMPageWriteLength - (wordAddr & (NVRAMPageWriteLength - 1)); //0x10-(wordAddr&0xF);
		if (count > tempSize)
		{
			if (NVRAM_i2c_BurstWrite(tempSize, (BYTE*)(buffer + offset)) == FALSE)
				break;
			NVRAM_i2c_Stop();
			count -= tempSize;
			offset += tempSize;
		}
		else if (count > NVRAMPageWriteLength) //0x10)
		{
			if (NVRAM_i2c_BurstWrite(0x10, (BYTE*)(buffer + offset)) == FALSE)
				break;
			NVRAM_i2c_Stop();
			count -= NVRAMPageWriteLength; //0x10;
			offset += NVRAMPageWriteLength; //0x10;
		}
		else
		{
			if (NVRAM_i2c_BurstWrite(count, (BYTE*)(buffer + offset)) == FALSE)
				break;
			NVRAM_i2c_Stop();
			count = 0;
		}
		ForceDelay1ms(NVRAMPageWriteDelayTime);//edit by lizzie,100429.for the problem: use HDMI/VGA Cable write all port EDID ,the time to write 32byte is too long
	}
	NVRAM_i2c_Stop();
}

void NVRAM_i2c_ReadTBL(BYTE deviceID, WORD addr, BYTE *buffer, BYTE count)
{
	WORD retry = NVRAM_RETRY;
	BYTE slaveAddr;
	BYTE wordAddr;
	slaveAddr = i2cSlaveAddr(deviceID, addr);
	wordAddr = i2cWordAddr(addr);
	while (retry--)
	{
		if (NVRAM_i2c_MasterStart(I2C_WRITE, slaveAddr) == FALSE)
			continue;
		if (NVRAM_i2c_BurstWrite(1, &wordAddr) == FALSE)
			continue;
		if (NVRAM_i2c_MasterStart(I2C_READ, slaveAddr) == FALSE)
			continue;
		if (NVRAM_i2c_BurstRead(count, buffer) == FALSE)
			continue;
		return;
	}
}

#endif
#else

#if (VGA_Write_EEPROM||DVI_Write_EEPROM||HDMI_Write_EEPROM)//LoadDefault_DVI_EDIDTo24C02//def Internal_EDID_Write_To_24C02

#if USEFLASH
#define	NVRAMPageWriteLength		16

#define	NVRAMPageWriteDelayTime	5

Bool NVRAM_CheckIICAck(void)
{
	BYTE i;
	for(i = 0; i < 100; i++)
	{
		if(NVRAM_i2c_SDA_IS_LO())
			return TRUE;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
	}
	if(NVRAM_i2c_SDA_IS_LO())
		return TRUE;
	else
		return FALSE;
}
/////////////////////////////////////////
void NVRAM_i2c_Delay(void)
{
	BYTE i;
	for(i = 0; i < 100; i++) // 100: 59K
		_nop_();
}
//====================================
// Setup i2c Start condition
Bool NVRAM_i2c_Start(void)
{
	Set_NVRAM_i2c_SDA();
	NVRAM_i2c_Delay();
	Set_NVRAM_i2c_SCL();
	NVRAM_i2c_Delay();
	//NVRAM_i2cSCL_Chk();
	if (NVRAM_i2c_SDA_IS_LO() || NVRAM_i2c_SCL_IS_LO())
		return FALSE;
	Clr_NVRAM_i2c_SDA();
	NVRAM_i2c_Delay();
	Clr_NVRAM_i2c_SCL();
	return TRUE;
}
//============================================
Bool NVRAM_i2c_SendByte(BYTE value)
{
	BYTE i;
	Bool result;
	for (i = 0; i < 8; i++) // Send data via i2c pin
	{
		if (value & BIT7)
			Set_NVRAM_i2c_SDA();
		else
			Clr_NVRAM_i2c_SDA();
		NVRAM_i2c_Delay();
		Set_NVRAM_i2c_SCL();
		NVRAM_i2c_Delay();
		//NVRAM_i2cSCL_Chk();
		value <<= 1;
		Clr_NVRAM_i2c_SCL();
	}
	Set_NVRAM_i2c_SDA();
	NVRAM_i2c_Delay();
	result = NVRAM_CheckIICAck();
	Set_NVRAM_i2c_SCL();
	NVRAM_i2c_Delay();
	//NVRAM_i2cSCL_Chk();
	Clr_NVRAM_i2c_SCL();
	NVRAM_i2c_Delay();
	Clr_NVRAM_i2c_SDA();
	return result;
}

//============================================
BYTE NVRAM_i2c_ReceiveByte(const Bool ack)
{
	BYTE i;
	BYTE value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		Set_NVRAM_i2c_SDA();
		#if Enable_Cache// 090417
		NVRAM_i2c_Delay();
		#endif
		Set_NVRAM_i2c_SCL();
		NVRAM_i2c_Delay();
		//NVRAM_i2cSCL_Chk();
		if (NVRAM_i2c_SDA_IS_HI())
			value |= BIT0;
		Clr_NVRAM_i2c_SCL();
	}
	if (ack)
		Clr_NVRAM_i2c_SDA();
	else
		Set_NVRAM_i2c_SDA();
	NVRAM_i2c_Delay();
	Set_NVRAM_i2c_SCL();
	NVRAM_i2c_Delay();
	//NVRAM_i2cSCL_Chk();
	Clr_NVRAM_i2c_SCL();
	return value;
}
// Setup i2c Stop condition
void NVRAM_i2c_Stop(void)
{
	// SCL=L, SDA=L, Stop condition.
	Clr_NVRAM_i2c_SCL();
	NVRAM_i2c_Delay();
	Clr_NVRAM_i2c_SDA();
	NVRAM_i2c_Delay();
	Set_NVRAM_i2c_SCL();
	NVRAM_i2c_Delay();
	//NVRAM_i2cSCL_Chk();
	Set_NVRAM_i2c_SDA();
}
Bool NVRAM_i2c_BurstRead(BYTE count, BYTE * buffer)
{
	BYTE i;
	for (i = 0; i < count - 1; i++)
		*(buffer + i) = NVRAM_i2c_ReceiveByte(1);
	*(buffer + i) = NVRAM_i2c_ReceiveByte(0);
	NVRAM_i2c_Stop();
	return TRUE;
}
//=============================================


Bool NVRAM_i2c_BurstWrite(BYTE count, BYTE *buffer)
{
	while (count--)
	{
		if (NVRAM_i2c_SendByte(*(buffer++)) == FALSE)
			return FALSE;
	}
	return TRUE;
}
Bool NVRAM_i2c_MasterStart(I2C_Direction direct, BYTE addr)
{
	BYTE retry = NVRAM_RETRY;
	if (direct == I2C_READ) // Set I2C direction bit.
		addr |= BIT0;
	else
		addr &= ~BIT0;
	while (retry--)
	{
		if (NVRAM_i2c_Start() == FALSE)
			continue;
		if (NVRAM_i2c_SendByte(addr) == TRUE) // send address success
		{
			//printMsg("SendByte TRUE");
			return TRUE;
		}
		NVRAM_i2c_Stop();
		//printMsg("SendByte Fail");
		ForceDelay1ms(2);
	}
	return FALSE;
}
void NVRAM_i2c_WriteTBL(BYTE deviceID, WORD addr, BYTE *buffer, BYTE count)
{
	BYTE slaveAddr;
	BYTE wordAddr;
	BYTE offset = 0;
	BYTE tempSize;
	Bool succ = TRUE;
	while (count)
	{
		slaveAddr = i2cSlaveAddr(deviceID, addr + offset);
		wordAddr = i2cWordAddr(addr + offset);
		if (NVRAM_i2c_MasterStart(I2C_WRITE, slaveAddr) == FALSE)
			break;
		if (NVRAM_i2c_BurstWrite(1, &wordAddr) == FALSE)
			break;
		tempSize = NVRAMPageWriteLength - (wordAddr & (NVRAMPageWriteLength - 1)); //0x10-(wordAddr&0xF);
		if (count > tempSize)
		{
			if (NVRAM_i2c_BurstWrite(tempSize, (BYTE*)(buffer + offset)) == FALSE)
				break;
			NVRAM_i2c_Stop();
			count -= tempSize;
			offset += tempSize;
		}
		else if (count > NVRAMPageWriteLength) //0x10)
		{
			if (NVRAM_i2c_BurstWrite(0x10, (BYTE*)(buffer + offset)) == FALSE)
				break;
			NVRAM_i2c_Stop();
			count -= NVRAMPageWriteLength; //0x10;
			offset += NVRAMPageWriteLength; //0x10;
		}
		else
		{
			if (NVRAM_i2c_BurstWrite(count, (BYTE*)(buffer + offset)) == FALSE)
				break;
			NVRAM_i2c_Stop();
			count = 0;
		}
		ForceDelay1ms(NVRAMPageWriteDelayTime);//edit by lizzie,100429.for the problem: use HDMI/VGA Cable write all port EDID ,the time to write 32byte is too long
	}
	NVRAM_i2c_Stop();
}
void NVRAM_i2c_ReadTBL(BYTE deviceID, WORD addr, BYTE *buffer, BYTE count)
{
	WORD retry = NVRAM_RETRY;
	BYTE slaveAddr;
	BYTE wordAddr;
	slaveAddr = i2cSlaveAddr(deviceID, addr);
	wordAddr = i2cWordAddr(addr);
	while (retry--)
	{
		if (NVRAM_i2c_MasterStart(I2C_WRITE, slaveAddr) == FALSE)
			continue;
		if (NVRAM_i2c_BurstWrite(1, &wordAddr) == FALSE)
			continue;
		if (NVRAM_i2c_MasterStart(I2C_READ, slaveAddr) == FALSE)
			continue;
		if (NVRAM_i2c_BurstRead(count, buffer) == FALSE)
			continue;
		return;
	}
}
#endif
#endif

#endif


