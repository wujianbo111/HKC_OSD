#include "types.h"
#include "i2cdef.h"
#include "board.h"//Fay 2013/5/27   
#include "i2c.h"//Fay 2013/5/27   
#include "global.h"
#include "GPIO_DEF.h"

#define NVRAM_DEVICE    0xA0

#if 0//( !USEFLASH)
void NVRam_WriteByte(WORD addr, BYTE value)
{
	Clr_EEPROM_WP(); //wumaozhong 20050331
	#if (EEPROM_TYPE >= EEPROM_24C32)
	rmBurstWriteBytes(addr, &value, 1);
	#else
	i2c_WriteTBL(NVRAM_DEVICE, addr, &value, 1);
	#endif
	Set_EEPROM_WP(); //wumaozhong 20050331
}


void NVRam_WriteWord(WORD addr, WORD value)
{
	Clr_EEPROM_WP();
	#if (EEPROM_TYPE >= EEPROM_24C32)
	rmBurstWriteBytes(addr, ( BYTE* )&value, 2);
	#else
	NVRAM_i2c_WriteTBL(NVRAM_DEVICE, addr, (BYTE*)&value, 2);
	#endif
	Set_EEPROM_WP();
}

void NVRam_ReadByte(WORD addr, BYTE *value)
{
	#if (EEPROM_TYPE >= EEPROM_24C32)
	rmSWBurstReadBytes(addr, value, 1);
	#else
	NVRAM_i2c_ReadTBL(NVRAM_DEVICE, addr, value, 1);
	#endif
}
void NVRam_ReadTbl(WORD addr, BYTE *buffer, BYTE count)
{
	#if (EEPROM_TYPE >= EEPROM_24C32)
	rmSWBurstReadBytes(addr, buffer, count);
	#else
	NVRAM_i2c_ReadTBL(NVRAM_DEVICE, addr, buffer, count);
	#endif
}

#elif (VGA_Write_EEPROM||DVI_Write_EEPROM|HDMI_Write_EEPROM)

void NVRam_WriteByte(WORD addr, BYTE value)
{
	#if (EEPROM_TYPE >= EEPROM_24C32)
	rmBurstWriteBytes(addr, &value, 1);
	#else
	NVRAM_i2c_WriteTBL(NVRAM_DEVICE, addr, &value, 1);
	#endif
}

void NVRam_ReadByte(WORD addr, BYTE *value)
{
	#if (EEPROM_TYPE >= EEPROM_24C32)
	rmSWBurstReadBytes(addr, value, 1);
	#else
	NVRAM_i2c_ReadTBL(NVRAM_DEVICE, addr, value, 1);
	#endif
}
#ifdef UseVGACableReadWriteAllPortsEDID
#if 0
void WriteDevice(BYTE DeviceType, WORD Address, BYTE* buf, BYTE Length) //Write Data To Device
{
	EnableReadDDCType = DeviceType;//Select Current IIC Port
	NVRAM_i2c_WriteTBL(0xA0, Address, buf, Length);//it takes about 48ms for EEPROM to write 32 Bytes.
	EnableReadDDCType = I2C_EEPROM;//Set IIC Port To UserData EEPRom
}
#endif
void ReadDevice(BYTE DeviceType, WORD Address, BYTE* buf, BYTE Length) //Read Data From Device
{
	EnableReadDDCType = DeviceType;//Select Current IIC Port
	NVRAM_i2c_ReadTBL(0xA0, Address, buf, Length);//Read Data From EEProm
	EnableReadDDCType = I2C_EEPROM;//Set IIC Port To UserData EEPRom
}
#endif
#endif

