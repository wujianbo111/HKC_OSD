
extern void i2c_WriteTBL(BYTE deviceID, WORD addr, BYTE *buffer, BYTE count);
extern void i2c_ReadTBL(BYTE deviceID, WORD addr, BYTE *buffer, BYTE count);

extern void NVRAM_i2c_WriteTBL(BYTE deviceID, WORD addr, BYTE *buffer, BYTE count);
extern void NVRAM_i2c_ReadTBL(BYTE deviceID, WORD addr, BYTE *buffer, BYTE count);

extern void rmBurstWriteBytes(WORD wIndex, BYTE *pBuf, WORD ucBufLen);
extern void rmSWBurstReadBytes(WORD wIndex, BYTE *pBuf, BYTE ucBufLen);


#if	UseI2cByTableFunc
extern WORD code  IOEZ_REGADD[];
extern BYTE code  IO_bit_SDA[];
extern BYTE code  IO_bit_SCL[];

#define Init_NVRAM_I2C_SDA_Pin()			(MEM_MSWRITE_BIT(IOEZ_REGADD[EnableReadDDCType], OUTPUT, IO_bit_SDA[EnableReadDDCType]))
#define Init_NVRAM_I2C_SCL_Pin()			(MEM_MSWRITE_BIT(IOEZ_REGADD[EnableReadDDCType], OUTPUT, IO_bit_SCL[EnableReadDDCType]))

#define DisEn_NVRAM_I2C_SDA_Pin()		(MEM_MSWRITE_BIT(IOEZ_REGADD[EnableReadDDCType], INPUT, IO_bit_SDA[EnableReadDDCType]))
#define DisEN_NVRAM_I2C_SCL_Pin()		(MEM_MSWRITE_BIT(IOEZ_REGADD[EnableReadDDCType], INPUT, IO_bit_SCL[EnableReadDDCType]))
#endif




