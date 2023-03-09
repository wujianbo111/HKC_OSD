//#include <math.h>
//#include "types.h"

#if ENABLE_3DLUT
#include "global.h"
#include "drv3DLUT_C.h"

#if ENABLE_3DLUT_Test
code _3dLutSettingType t_3dLutRGBSettingValue[6] =
{
	{0x10, 0x40, 0x100, 0x3FF,  0x3FF,    0x00 },
	{0x20, 0x40, 0x100, 0x3FF,	0x3FF,	0x3FF },
	{0x30, 0x40, 0x100, 0x00,	0x3FF,	0x3FF },
	{0x40, 0x40, 0x100, 0x00,	0x00,	0x3FF },
	{0x50, 0x40, 0x100, 0x00,	0x3FF,	0x00 },
	{0x60, 0x40, 0x100, 0x3FF,	0x00,	0x00 },
};
#endif

code BYTE _3dLutSram[2][9][9] =
{
	{
		{1, 2, 1, 2, 1, 2, 1, 2, 1},
		{3, 4, 3, 4, 3, 4, 3, 4, 3},
		{1, 2, 1, 2, 1, 2, 1, 2, 1},
		{3, 4, 3, 4, 3, 4, 3, 4, 3},
		{1, 2, 1, 2, 1, 2, 1, 2, 1},
		{3, 4, 3, 4, 3, 4, 3, 4, 3},
		{1, 2, 1, 2, 1, 2, 1, 2, 1},
		{3, 4, 3, 4, 3, 4, 3, 4, 3},
		{1, 2, 1, 2, 1, 2, 1, 2, 1}
	},
	{
		{5, 6, 5, 6, 5, 6, 5, 6, 5},
		{7, 8, 7, 8, 7, 8, 7, 8, 7},
		{5, 6, 5, 6, 5, 6, 5, 6, 5},
		{7, 8, 7, 8, 7, 8, 7, 8, 7},
		{5, 6, 5, 6, 5, 6, 5, 6, 5},
		{7, 8, 7, 8, 7, 8, 7, 8, 7},
		{5, 6, 5, 6, 5, 6, 5, 6, 5},
		{7, 8, 7, 8, 7, 8, 7, 8, 7},
		{5, 6, 5, 6, 5, 6, 5, 6, 5}
	}
};

code BYTE _3dLutAddr[9][9][9] =
{
	{
		// B 000
		{  0,  0,  1,  1,  2,  2,  3,  3, 80},
		{  0,  0,  1,  1,  2,  2,  3,  3, 80},
		{  4,  4,  5,  5,  6,  6,  7,  7, 81},
		{  4,  4,  5,  5,  6,  6,  7,  7, 81},
		{  8,  8,  9,  9, 10, 10, 11, 11, 82},
		{  8,  8,  9,  9, 10, 10, 11, 11, 82},
		{ 12, 12, 13, 13, 14, 14, 15, 15, 83},
		{ 12, 12, 13, 13, 14, 14, 15, 15, 83},
		{100, 80, 101, 81, 102, 82, 103, 83, 120}
	},
	{
		// B 020
		{  0,  0,  1,  1,  2,  2,  3,  3, 64},
		{  0,  0,  1,  1,  2,  2,  3,  3, 64},
		{  4,  4,  5,  5,  6,  6,  7,  7, 65},
		{  4,  4,  5,  5,  6,  6,  7,  7, 65},
		{  8,  8,  9,  9, 10, 10, 11, 11, 66},
		{  8,  8,  9,  9, 10, 10, 11, 11, 66},
		{ 12, 12, 13, 13, 14, 14, 15, 15, 67},
		{ 12, 12, 13, 13, 14, 14, 15, 15, 67},
		{ 80, 64, 81, 65, 82, 66, 83, 67, 96}
	},
	{
		// B 040
		{ 16, 16, 17, 17, 18, 18, 19, 19, 84},
		{ 16, 16, 17, 17, 18, 18, 19, 19, 84},
		{ 20, 20, 21, 21, 22, 22, 23, 23, 85},
		{ 20, 20, 21, 21, 22, 22, 23, 23, 85},
		{ 24, 24, 25, 25, 26, 26, 27, 27, 86},
		{ 24, 24, 25, 25, 26, 26, 27, 27, 86},
		{ 28, 28, 29, 29, 30, 30, 31, 31, 87},
		{ 28, 28, 29, 29, 30, 30, 31, 31, 87},
		{104, 84, 105, 85, 106, 86, 107, 87, 121}
	},
	{
		// B 060
		{ 16, 16, 17, 17, 18, 18, 19, 19, 68},
		{ 16, 16, 17, 17, 18, 18, 19, 19, 68},
		{ 20, 20, 21, 21, 22, 22, 23, 23, 69},
		{ 20, 20, 21, 21, 22, 22, 23, 23, 69},
		{ 24, 24, 25, 25, 26, 26, 27, 27, 70},
		{ 24, 24, 25, 25, 26, 26, 27, 27, 70},
		{ 28, 28, 29, 29, 30, 30, 31, 31, 71},
		{ 28, 28, 29, 29, 30, 30, 31, 31, 71},
		{ 84, 68, 85, 69, 86, 70, 87, 71, 97}
	},
	{
		// B 080
		{ 32, 32, 33, 33, 34, 34, 35, 35, 88},
		{ 32, 32, 33, 33, 34, 34, 35, 35, 88},
		{ 36, 36, 37, 37, 38, 38, 39, 39, 89},
		{ 36, 36, 37, 37, 38, 38, 39, 39, 89},
		{ 40, 40, 41, 41, 42, 42, 43, 43, 90},
		{ 40, 40, 41, 41, 42, 42, 43, 43, 90},
		{ 44, 44, 45, 45, 46, 46, 47, 47, 91},
		{ 44, 44, 45, 45, 46, 46, 47, 47, 91},
		{108, 88, 109, 89, 110, 90, 111, 91, 122}
	},
	{
		// B 0A0
		{ 32, 32, 33, 33, 34, 34, 35, 35, 72},
		{ 32, 32, 33, 33, 34, 34, 35, 35, 72},
		{ 36, 36, 37, 37, 38, 38, 39, 39, 73},
		{ 36, 36, 37, 37, 38, 38, 39, 39, 73},
		{ 40, 40, 41, 41, 42, 42, 43, 43, 74},
		{ 40, 40, 41, 41, 42, 42, 43, 43, 74},
		{ 44, 44, 45, 45, 46, 46, 47, 47, 75},
		{ 44, 44, 45, 45, 46, 46, 47, 47, 75},
		{ 88, 72, 89, 73, 90, 74, 91, 75, 98}
	},
	{
		// B 0C0
		{ 48, 48, 49, 49, 50, 50, 51, 51, 92},
		{ 48, 48, 49, 49, 50, 50, 51, 51, 92},
		{ 52, 52, 53, 53, 54, 54, 55, 55, 93},
		{ 52, 52, 53, 53, 54, 54, 55, 55, 93},
		{ 56, 56, 57, 57, 58, 58, 59, 59, 94},
		{ 56, 56, 57, 57, 58, 58, 59, 59, 94},
		{ 60, 60, 61, 61, 62, 62, 63, 63, 95},
		{ 60, 60, 61, 61, 62, 62, 63, 63, 95},
		{112, 92, 113, 93, 114, 94, 115, 95, 123}
	},
	{
		// B 0E0
		{ 48, 48, 49, 49, 50, 50, 51, 51, 76},
		{ 48, 48, 49, 49, 50, 50, 51, 51, 76},
		{ 52, 52, 53, 53, 54, 54, 55, 55, 77},
		{ 52, 52, 53, 53, 54, 54, 55, 55, 77},
		{ 56, 56, 57, 57, 58, 58, 59, 59, 78},
		{ 56, 56, 57, 57, 58, 58, 59, 59, 78},
		{ 60, 60, 61, 61, 62, 62, 63, 63, 79},
		{ 60, 60, 61, 61, 62, 62, 63, 63, 79},
		{ 92, 76, 93, 77, 94, 78, 95, 79, 99}
	},
	{
		// B 100
		{ 64, 64, 65, 65, 66, 66, 67, 67, 96},
		{ 64, 64, 65, 65, 66, 66, 67, 67, 96},
		{ 68, 68, 69, 69, 70, 70, 71, 71, 97},
		{ 68, 68, 69, 69, 70, 70, 71, 71, 97},
		{ 72, 72, 73, 73, 74, 74, 75, 75, 98},
		{ 72, 72, 73, 73, 74, 74, 75, 75, 98},
		{ 76, 76, 77, 77, 78, 78, 79, 79, 99},
		{ 76, 76, 77, 77, 78, 78, 79, 79, 99},
		{116, 96, 117, 97, 118, 98, 119, 99, 124},
	},
};



#define  ENABLE_3DLUT_DEBUG  0
#if (ENABLE_3DLUT_DEBUG&&ENABLE_DEBUG)
#define LUT_printData(str, value)   printData(str, value)
#define LUT_printMsg(str)               printMsg(str)
#else
#define LUT_printData(str, value)
#define LUT_printMsg(str)
#endif


void drv3DLutSet(_3dLutSettingType *t3DSet)
{
	BYTE Ri = t3DSet->idxR >> 5;
	BYTE Gi = t3DSet->idxG >> 5;
	BYTE Bi = t3DSet->idxB >> 5;
	BYTE idxSram = _3dLutSram[Bi % 2][Gi][Ri] - 1;
	BYTE idxAddr = _3dLutAddr[Bi][Gi][Ri];
	msWriteByte(SC9_80, idxAddr);
	msWriteByte(SC9_81, idxSram);
	//printData("idxAddr===%x",idxAddr);
	//printData("idxSram===%x",idxSram);
	//printData("idxAddr===%x",t3DSet->valueR);
	//printData("idxSram===%x",t3DSet->valueG);
	//printData("idxSram===%x",t3DSet->valueB);
	//"10 bit table vaule to write sram for R/G/B channelas in burst write, R/G/B channel was used as burst write channel"
	msWriteBit(SC9_81, 1, _BIT5);
	msWrite2Byte(SC9_82, t3DSet->valueR);
	msWrite2Byte(SC9_84, t3DSet->valueG);
	msWrite2Byte(SC9_86, t3DSet->valueB);
}

#if ENABLE_3DLUT_Test
void drv3DLutSetTest(BYTE Number)
{
	LUT_printMsg("drv3DLutSetTest");
	drv3DLutSet(&t_3dLutRGBSettingValue[Number]);
}

void drv3DLutWriteReadTest(void)
{
	BYTE idxSram = 0;
	BYTE idxAddr = 0;
	for( idxSram = 0; idxSram < 8; idxSram ++ )
	{
		LUT_printData("@@@ Write idxSram=>%d", idxSram);
		msWriteByteMask(SC9_81, idxSram, BIT2 | BIT1 | BIT0);
		for( idxAddr = 0; idxAddr < 100; idxAddr++ )
		{
			LUT_printData("@@@ Write SRAM idxAddr=>%d", idxAddr);
			msWriteByte(SC9_80, idxAddr);
			msWriteBit(SC9_81, 1, _BIT5);  //Write
			msWrite2Byte(SC9_82, 0x3FF);
			msWrite2Byte(SC9_84, 0x00);
			msWrite2Byte(SC9_86, 0x177 );
			msWriteBit(SC9_81, 1, _BIT6);  //Read
			LUT_printData("### Read  R data=>%x", msRead2Byte(SC9_8A));
			LUT_printData("### Read  G data=>%x", msRead2Byte(SC9_8C));
			LUT_printData("### Read  B data=>%x", msRead2Byte(SC9_8E));
		}
	}
	msWriteBit(SC9_88, BIT0, BIT0);
}

#endif
void drv3DLutDeltaRatio(_3dLutDeltaEnum ratio)
{
	//reg_rgb_3d_lut_delta_x2x4
	//"00: sram format 8.2(default)01: sram format 9.110: sram format 1011: default"
	BYTE value;
	value = msReadByte(SC9_88);
	value &= (~(_BIT2 | _BIT3));
	value |= ((ratio & 0x3) << 2);
	msWriteByte(SC9_88, value);
}

void drv3DLutEnable(BYTE ucSrcIdx, BYTE enable)
{
	//rgb 3d lut sub window enable
	//rgb 3d lut main window enable
	BYTE mask;
	if( ucSrcIdx == MAIN_WINDOW )
		mask = _BIT0;
	else
		mask = _BIT1;
	msWriteBit(SC9_88, enable, mask);
}

void drv3DLutInit()
{
	//execute all sram initial write as 0; hardware auto clear after operation ready
	msWriteBit(SC9_81, 1, _BIT4);
}


void mStar_Setup3DLUT( void )
{
	//printData("mStar_Setup3DLUT");
	drv3DLutSet(NULL);
	drv3DLutDeltaRatio(0);
	drv3DLutEnable(0, 0);
	drv3DLutInit();
}

#endif
