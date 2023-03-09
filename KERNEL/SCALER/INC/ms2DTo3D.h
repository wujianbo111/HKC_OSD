#ifndef _MS_2DTo3D_H_
#define _MS_2DTo3D_H_

#ifdef _MS_2DTo3D_C_
#define MS_2DTo3DDec
#else
#define MS_2DTo3DDec   extern
#endif

#define MAX_3DOFFSET		127
#define MAX_3DGAIN			31
#define ARTIFICIAL_FACTOR					0x0//artificial detection dominate factor(max = 0x0f)

#if CHIP_ID==CHIP_TSUM2  //20120814
typedef struct
{
	BYTE ucOffset;
	BYTE ucDepth;
} Sc2DTo3DInfo;

MS_2DTo3DDec xdata Sc2DTo3DInfo g_Sc2DTo3DInfo;

MS_2DTo3DDec void Sc2DTo3DInit(void);
MS_2DTo3DDec BYTE Sc2DTo3DGetDepth(void);
MS_2DTo3DDec void  Sc2DTo3DSetGain(BYTE ucDepth);
MS_2DTo3DDec void Sc2DTo3DSetPixelGain(BYTE gain);

MS_2DTo3DDec void Sc2DTo3DOff(void);

MS_2DTo3DDec BYTE Sc2DTo3DGetOffset(void);
MS_2DTo3DDec void Sc2DTo3DSetOffset(BYTE offset);
MS_2DTo3DDec void Sc2DTo3DPwrOff(void);
MS_2DTo3DDec void Sc2DTo3DPwrOn(void);
MS_2DTo3DDec void Sc2DTo3DEnable(void);
MS_2DTo3DDec void Sc2DTo3DDisable(void);
#endif

#undef MS_2DTo3DDec
#endif
