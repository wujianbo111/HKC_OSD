
extern void Osd_SetWindowSize(BYTE width, BYTE height);
extern void Osd_SetTransparence(BYTE value);
extern void Osd_SetPosition( BYTE xPos, BYTE yPos );
extern void Osd_Show(void);
extern void Osd_Hide(void);

extern void SetOSDWindosw(BYTE ucSubWin, BYTE u8HStart, BYTE u8HEnd, BYTE u8VStart, BYTE u8VEnd, BYTE u8Color);
extern void ClrOSDWindosw(BYTE ucSubWin);
extern BYTE Osd_DoubleBuffer(Bool u8Enable);
extern void Osd_SetTextMonoColor(BYTE foreColor, BYTE backColor);
extern void Osd_SetTextColor(BYTE foreColor, BYTE backColor);
extern void Osd_Set256TextColor(BYTE foreColor, BYTE backColor);

#define OSD_IS_SHOWED()				(msReadByte((OSD_MAIN_WND<<5)+OSD2_00)&BIT0)//20130516

#if 0//CHIP_ID<CHIP_TSUMV
extern void SetOsdGraduallyBackGround( BYTE Win_Num, BYTE GDRValue, BYTE GDGValue, BYTE GDBValue, BYTE GDDelta, BYTE GDDERange, BYTE GDControl, BYTE GDRInit, BYTE GDGInit, BYTE GDBInit);
#endif

