
#ifndef _MS_3DLUT_H_
#define _MS_3DLUT_H_
#define ENABLE_3DLUT_Test          1

typedef struct
{
	WORD idxR;      /* Index, 0x00, 0x20, 0x40, ... 0x100 */
	WORD idxG;
	WORD idxB;
	WORD valueR;    /* Value, 10 bits, 1's complement */
	WORD valueG;
	WORD valueB;

} _3dLutSettingType;

typedef enum
{
	e3dLutDelta1X = 0,
	e3dLutDelta2X,
	e3dLutDelta4X,
	e3dLutDelta8X
} _3dLutDeltaEnum;

#if ENABLE_3DLUT_Test
extern code _3dLutSettingType t_3dLutRGBSettingValue[6];
extern void drv3DLutSetTest(BYTE Number);
extern void drv3DLutWriteReadTest(void);
#endif
extern void drv3DLutSet(_3dLutSettingType *t3DSet);
extern void drv3DLutDeltaRatio(_3dLutDeltaEnum ratio);
extern void ms3DLutEnable(BYTE window, BYTE enable);
extern void drv3DLutInit();

extern void mStar_Setup3DLUT( void );

#endif

