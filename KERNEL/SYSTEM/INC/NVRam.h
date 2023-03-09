#if (!USEFLASH)
extern void NVRam_WriteByte(WORD addr, BYTE value);
extern void NVRam_WriteWord(WORD addr, WORD value);
extern void NVRam_ReadByte(WORD addr, BYTE *value);
extern void NVRam_ReadTbl(WORD addr, BYTE *buffer, BYTE count);

#elif (VGA_Write_EEPROM||DVI_Write_EEPROM|HDMI_Write_EEPROM)
extern void NVRam_WriteByte(WORD addr, BYTE value);
extern void NVRam_ReadByte(WORD addr, BYTE *value);

#ifdef  UseVGACableReadWriteAllPortsEDID
//extern void WriteDevice(BYTE DeviceType,WORD Address, BYTE* buf,BYTE Length);
extern void ReadDevice(BYTE DeviceType, WORD Address, BYTE* buf, BYTE Length);
#endif
#endif
