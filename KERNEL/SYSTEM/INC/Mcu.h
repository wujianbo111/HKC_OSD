#ifndef _MCU_H_
#define _MCU_H_

#ifdef _MCU_C_
#define _MCUDEC_
#else
#define _MCUDEC_    extern
#endif

_MCUDEC_ void Init_MCU( void );
_MCUDEC_ void Init_ExternalInterrupt( void );
_MCUDEC_ void Init_Timer( void );
_MCUDEC_ void Init_SerialPort( void );
_MCUDEC_ void Init_IOPorts( void );
//_MCUDEC_ void MCU_EnableCache(Bool u8Enable);
_MCUDEC_ XDATA BYTE TI1_FLAG;

#if EXT_TIMER0_1S   // 2012-05-23
_MCUDEC_ BYTE xdata g_second;
_MCUDEC_ BYTE xdata g_minute;
_MCUDEC_ BYTE xdata g_hour;
_MCUDEC_ bit g_oneSecondFlag;
_MCUDEC_ bit g_oneMinuteFlag;

_MCUDEC_ void mcuExTimer();
#endif

#endif
