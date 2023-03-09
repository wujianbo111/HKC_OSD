
#define _DRVOSD_C

#include "types.h"
#include "board.h"
#include "ms_reg.h"
#include "drvOSD.h"
#include "ms_rwreg.h"
#include "msosd.h"
#include "halrwreg.h"
extern  xdata BYTE  OsdFontColor;

#if 0//ENABLE_OSD_ROTATION
WORD drvOSD_GetTxtCAStart(BYTE u8Wnd, BYTE u8XPos, BYTE u8YPos)
{
	BYTE u8LineOffset = msReadByte((u8Wnd << 5) + OSD2_12);
	WORD u16CABase = msRead2Byte((u8Wnd << 5) + OSD2_10);
	if ((msReadByte(OSD1_03) >> 6) == 1) //for 90 degree only
		u16CABase = GET_CABASE_90_0(u16CABase, u8LineOffset);
	return (u16CABase + (WORD)u8YPos * u8LineOffset + u8XPos);
}
#endif

#if defined(_MANHATTAN_OSD_)
void drvOSD_DrawVContinuousChar(BYTE u8Wnd, BYTE u8XPos, BYTE u8YPos, BYTE u8Char, BYTE u8Num)
{
	WORD u16TempValue;
	BYTE i;
	BYTE u8DrawCode = (!(u8YPos & BIT7));
	u8YPos &= 0x7F;
	//u8Wnd<<=5;
	//u16TempValue=msRead2Byte((u8Wnd)+OSD2_10)+(WORD)u8YPos*msReadByte((u8Wnd)+OSD2_12)+u8XPos; // get real address
	u16TempValue = GET_TXT_CASTART(u8Wnd, u8XPos, u8YPos); // get real address
#define LINE_OFFSET u8Wnd
	LINE_OFFSET = msReadByte((u8Wnd << 5) + OSD2_12);
	for (i = 0; i < u8Num; i++)
	{
		WRITE_CAFSRAM_ADDR();
		msWrite2Byte(PORT_ATTR_ADDR, u16TempValue);
		WRITE_ATTRIBUTE();
		msWriteByte(PORT_ATTR_DATA, OsdFontColor);
		u16TempValue += LINE_OFFSET;
	}
	if (u8DrawCode)
	{
		for(i = 0; i < u8Num; i++)
		{
			u16TempValue -= LINE_OFFSET;
			WRITE_CAFSRAM_ADDR();
			msWrite2Byte(PORT_CODE_ADDR, u16TempValue);
			WRITE_CODE();
			msWriteByte(PORT_CODE_DATA, u8Char);
		}
	}
#undef LINE_OFFSET
}
#endif
void drvOSD_DrawBlankPlane(BYTE u8Wnd, BYTE u8XPos, BYTE u8YPos, BYTE u8Width, BYTE u8Height)
{
	BYTE xdata i, j;
	WORD xdata u16TempValue;
	BYTE xdata IsDrawCode = (!(u8YPos & BIT7));
	u8YPos &= 0x7F;
	//u8Wnd<<=5;
	//u16TempValue=msRead2Byte((u8Wnd)+OSD2_10)+(WORD)u8YPos*msReadByte((u8Wnd)+OSD2_12)+u8XPos; // get real address
	u16TempValue = GET_TXT_CASTART(u8Wnd, u8XPos, u8YPos); // get real address
#define LINE_OFFSET u8Wnd
	LINE_OFFSET = msReadByte((u8Wnd << 5) + OSD2_12);
	for (i = 0; i < u8Height; i++)
	{
		WRITE_CAFSRAM_ADDR();
		msWrite2Byte(PORT_ATTR_ADDR, u16TempValue);
		WRITE_ATTRIBUTE();
		for(j = 0; j < u8Width; j++)
		{
			msWriteByte(PORT_ATTR_DATA, OsdFontColor);
		}
		u16TempValue += LINE_OFFSET;
	}
	if (!IsDrawCode)
		return;
	u16TempValue -= (LINE_OFFSET * u8Height); // recover real address
	for (i = 0; i < u8Height; i++)
	{
		WRITE_CAFSRAM_ADDR();
		msWrite2Byte(PORT_CODE_ADDR, u16TempValue);
		WRITE_CODE();
		for(j = 0; j < u8Width; j++)
		{
			msWriteByte(PORT_CODE_DATA, SPACE_FONT);
		}
		u16TempValue += LINE_OFFSET;
	}
#undef LINE_OFFSET
}

void drvOSD_SetWndLineOffset(BYTE u8Wnd, BYTE u8LineOffset)
{
	msWriteByte((u8Wnd << 5) + OSD2_12, u8LineOffset);
}
#if !ENABLE_MENULOAD//||!ENABLE_SW_DOUBLE_BUFFER
void drvOSD_SetWndHPosition(BYTE u8Wnd, WORD u16HStart, WORD u16HEnd)
{
	u8Wnd <<= 5;
	msWrite2Byte((u8Wnd) + OSD2_04, u16HStart);
	msWrite2Byte((u8Wnd) + OSD2_08, u16HEnd);
}
void drvOSD_SetWndVPosition(BYTE u8Wnd, WORD u16VStart, WORD u16VEnd)
{
	u8Wnd <<= 5;
	msWrite2Byte((u8Wnd) + OSD2_06, u16VStart);
	msWrite2Byte((u8Wnd) + OSD2_0A, u16VEnd);
}
#endif
WORD drvOSD_GetWndInfo(BYTE u8Wnd, BYTE u8Info)
{
	u8Wnd <<= 5;
	if (u8Info == OSD_WND_INFO_H_START)
		return  msRead2Byte((u8Wnd) + OSD2_04);
	if (u8Info == OSD_WND_INFO_V_START)
		return msRead2Byte((u8Wnd) + OSD2_06);
	if (u8Info == OSD_WND_INFO_V_END)
		return msRead2Byte((u8Wnd) + OSD2_0A);
	if (u8Info == OSD_WND_INFO_LINE_OFFSET)
		return msReadByte((u8Wnd) + OSD2_12);
	if (u8Info == OSD_WND_INFO_CABASE)
		return msRead2Byte((u8Wnd) + OSD2_10);
	return 0;
}
void drvOSD_SetWndOn(BYTE u8Wnd, Bool u8On)
{
	msWriteByteMask((u8Wnd << 5) + OSD2_00, (u8On ? BIT0 : 0), BIT0);
}
void drvOSD_SetWndCtrl(BYTE u8Wnd, BYTE u8CtrlType, WORD u16Value, WORD u16Mask)
{
	u8Wnd <<= 5;
	if (u8CtrlType == OSD_WND_CTRL0)
		msWrite2ByteMask((u8Wnd) + OSD2_00, u16Value, u16Mask);
	else if (u8CtrlType == OSD_WND_CTRL1)
		msWrite2ByteMask((u8Wnd) + OSD2_02, u16Value, u16Mask);
	else if (u8CtrlType == OSD_WND_CTRL2)
		msWrite2ByteMask((u8Wnd) + OSD2_14, u16Value, u16Mask);
	else if (u8CtrlType == OSD_WND_CTRL3)
		msWrite2ByteMask((u8Wnd) + OSD2_1A, u16Value, u16Mask);
}
void drvOSD_SetWndFixAlpha(BYTE u8Wnd, BYTE u8Lvl, BYTE u8Value)
{
	u8Wnd <<= 5;
	if (u8Lvl == OSD_ALPHA_OUT)
		msWriteByteMask((u8Wnd) + OSD2_0C, u8Value, 0x3F);
	else if (u8Lvl == OSD_ALPHA_LV1)
		msWriteByteMask((u8Wnd) + OSD2_0D, u8Value, 0x3F);
	else if (u8Lvl == OSD_ALPHA_LV2)
		msWriteByteMask((u8Wnd) + OSD2_19, u8Value, 0x3F);
}
void drvOSD_SetWndFixColor(BYTE u8Wnd, BYTE u8Red, BYTE u8Green, BYTE u8Blue)
{
	u8Wnd <<= 5;
	msWriteByte((u8Wnd) + OSD2_16, u8Red);
	msWriteByte((u8Wnd) + OSD2_17, u8Green);
	msWriteByte((u8Wnd) + OSD2_18, u8Blue);
}
void drvOSD_SetWndShiftPixel(BYTE u8Wnd, u8X, u8Y)
{
	u8Wnd <<= 5;
	msWriteByte((u8Wnd) + OSD2_0E, u8X);
	msWriteByte((u8Wnd) + OSD2_0F, u8Y);
}
void drvOSD_SetWndCABaseAddr(BYTE u8Wnd, WORD u16Addr)
{
	msWrite2Byte((u8Wnd << 5) + OSD2_10, u16Addr);
}
void drvOSD_SetWndFixAttr(BYTE u8Wnd, BYTE u8Enable, BYTE u8Attr)
{
	u8Wnd <<= 5;
	#if CHIP_ID>=CHIP_TSUM2
	msWriteByteMask((u8Wnd) + OSD2_15, (u8Enable ? (BIT7 | BIT6) : 0), BIT7 | BIT6);
	#else
	#endif
	msWriteByte((u8Wnd) + OSD2_1A, u8Attr);
	msWriteByteMask((u8Wnd) + OSD2_1B, (u8Enable ? BIT7 : 0), BIT7);
}
#if CHIP_ID >= CHIP_TSUM2
#define DEF_ARRANGE_WIN(i) void OSDArrangeWin##i(WORD hs, WORD he, WORD vs, WORD ve) { \
		SET_OSD_WIN_REG_WIN##i##_HEND_PIX(he); \
		SET_OSD_WIN_REG_WIN##i##_HSTR_PIX(hs); \
		SET_OSD_WIN_REG_WIN##i##_VEND_PIX(ve); \
		SET_OSD_WIN_REG_WIN##i##_VSTR_PIX(vs); }

#define DEF_BLENDING_WIN(i) void OSDBlendingWin##i(BYTE r_gd, BYTE g_gd, BYTE b_gd, BYTE fix_r, BYTE fix_g, BYTE fix_b, BYTE l1a_sel, BYTE fix_al1, BYTE l2a_sel, BYTE fix_al2, BYTE outa_sel, BYTE fix_aout) { \
		SET_OSD_WIN_REG_WIN##i##_CLR_B_SEL(b_gd); \
		SET_OSD_WIN_REG_WIN##i##_CLR_G_SEL(g_gd); \
		SET_OSD_WIN_REG_WIN##i##_CLR_R_SEL(r_gd); \
		SET_OSD_WIN_REG_WIN##i##_FIX_CLR_R(fix_r); \
		SET_OSD_WIN_REG_WIN##i##_FIX_CLR_G(fix_g); \
		SET_OSD_WIN_REG_WIN##i##_FIX_CLR_B(fix_b); \
		SET_OSD_WIN_REG_WIN##i##_FIX_ALPHA_LV1(fix_al1); \
		SET_OSD_WIN_REG_WIN##i##_FIX_ALPHA_LV2(fix_al2); \
		SET_OSD_WIN_REG_WIN##i##_FIX_ALPHA_OUT(fix_aout); \
		SET_OSD_WIN_REG_WIN##i##_LV1_A_SEL(l1a_sel); \
		SET_OSD_WIN_REG_WIN##i##_LV2_A_SEL(l2a_sel); \
		SET_OSD_WIN_REG_WIN##i##_OUT_A_SEL(outa_sel); }
#if 0
SET_OSD_WIN_REG_WIN0_CLR_B_SEL(r_gd);
\
SET_OSD_WIN_REG_WIN0_CLR_G_SEL(g_gd);
\
SET_OSD_WIN_REG_WIN0_CLR_R_SEL(b_gd);
\
SET_OSD_WIN_REG_WIN0_FIX_CLR_R(fix_r);
SET_OSD_WIN_REG_WIN0_FIX_CLR_G(fix_g);
SET_OSD_WIN_REG_WIN0_FIX_CLR_B(fix_b);
SET_OSD_WIN_REG_WIN0_FIX_ALPHA_LV1(fix_al1);
\
SET_OSD_WIN_REG_WIN0_FIX_ALPHA_LV2(fix_al2);
\
SET_OSD_WIN_REG_WIN0_FIX_ALPHA_OUT(fix_aout);
\
SET_OSD_WIN_REG_WIN0_LV1_A_SEL(l1a_sel);
\
SET_OSD_WIN_REG_WIN0_LV2_A_SEL(l2a_sel);
\
SET_OSD_WIN_REG_WIN0_OUT_A_SEL(outa_sel);
}
#endif


#define DEF_CONF_SRAM_WIN(i) void OSDConfSramWin##i(BYTE fh, WORD base_addr, BYTE l_off, BYTE sh_x, BYTE sh_y) { \
		SET_OSD_WIN_REG_WIN##i##_CHARHIGH(fh); \
		SET_OSD_WIN_REG_WIN##i##_BASE(base_addr); \
		SET_OSD_WIN_REG_WIN##i##_LINE_OFFSET(l_off); \
		SET_OSD_WIN_REG_WIN##i##_SHIFT_PIX_X(sh_x); \
		SET_OSD_WIN_REG_WIN##i##_SHIFT_PIX_Y(sh_y); }
#if 0
SET_OSD_WIN_REG_WIN0_CHARHIGH(fh);
\
SET_OSD_WIN_REG_WIN0_BASE(base_addr);
\
SET_OSD_WIN_REG_WIN0_LINE_OFFSET(l_off);
\
SET_OSD_WIN_REG_WIN0_SHIFT_PIX_X(sh_x);
\
SET_OSD_WIN_REG_WIN0_SHIFT_PIX_Y(sh_y);
}
#endif

#define DEF_CONF_SRAM_TEXT_WIN(i) void OSDConfSramTextWin##i(BYTE fh, WORD base_addr, BYTE l_off, BYTE sh_x, BYTE sh_y) { \
		SET_OSD_WIN_REG_WIN##i##_CHARHIGH(fh); \
		SET_OSD_WIN_REG_WIN##i##_BASE_TX(base_addr); \
		SET_OSD_WIN_REG_WIN##i##_LINE_OFFSET_TX(l_off); \
		SET_OSD_WIN_REG_WIN##i##_SHIFT_PIX_X(sh_x); \
		SET_OSD_WIN_REG_WIN##i##_SHIFT_PIX_Y(sh_y); }
#if 0
SET_OSD_WIN_REG_WIN0_CHARHIGH(fh);
\
SET_OSD_WIN_REG_WIN0_BASE_TX(base_addr);
\
SET_OSD_WIN_REG_WIN0_LINE_OFFSET_TX(l_off);
\
SET_OSD_WIN_REG_WIN0_SHIFT_PIX_X(sh_x);
\
SET_OSD_WIN_REG_WIN0_SHIFT_PIX_Y(sh_y);
}
#endif

#define DEF_CONF_GD_TG(i) void OSDConfGDTimingGenerator##i(unsigned hs, unsigned he, unsigned vs, unsigned ve) { \
		_CTRL_OSD_GD_REGISTERS(); \
		SET_OSD_GD_REG_GD_TG##i##_HST(hs); \
		SET_OSD_GD_REG_GD_TG##i##_VST(vs); \
		SET_OSD_GD_REG_GD_TG##i##_HEND(he); \
		SET_OSD_GD_REG_GD_TG##i##_VEND(ve); }
#if 0
SET_OSD_GD_REG_GD_TG0_HST(hs);
\
SET_OSD_GD_REG_GD_TG0_VST(vs);
\
SET_OSD_GD_REG_GD_TG0_HEND(he);
\
SET_OSD_GD_REG_GD_TG0_VEND(ve);
}
#endif


void OSDSetMask0(BYTE item, BYTE v)
{
	_CTRL_OSD_CTRL_REGISTERS();
	SET_OSD_CTRL_REG_TRIG_MODE(_TRIG_MODE_P0_ADDR);
	SET_OSD_CTRL_REG_WR_PORT(item);
	SET_OSD_CTRL_REG_TRIG_MODE(_TRIG_MODE_P0_MASK);
	SET_OSD_CTRL_REG_WR_PORT(v);
}

/*
void OSDSetColorKey0(BYTE item, BYTE v)
{
    _CTRL_OSD_CTRL_REGISTERS();
    SET_OSD_CTRL_REG_TRIG_MODE(_TRIG_MODE_P0_ADDR);
    SET_OSD_CTRL_REG_WR_PORT(item);
    SET_OSD_CTRL_REG_TRIG_MODE(_TRIG_MODE_P0_CKEY);
    SET_OSD_CTRL_REG_WR_PORT(v);
}
*/

void OSDConfGDCurveH(BYTE ci, BYTE pixel_init, BYTE delta_init,
                     BYTE step, BYTE data_sign, BYTE delta_sign, BYTE delta, WORD length0, WORD length1,
                     BYTE hv_sign, BYTE overflow_en, BYTE md)
{
	BYTE tmp;
	_CTRL_OSD_GD_REGISTERS();
	CLR_OSD_GD_REG_CURVE_RDATA_EN();
	_CTRL_OSD_CTRL_REGISTERS();
	SET_OSD_CTRL_REG_TRIG_MODE(_TRIG_MODE_GD_ADDR);
	ci <<= 1;
	SET_OSD_CTRL_REG_WR_PORT(ci);
	SET_OSD_CTRL_REG_TRIG_MODE(_TRIG_MODE_GD_DATA);
	SET_OSD_CTRL_REG_WR_PORT(pixel_init);
	SET_OSD_CTRL_REG_WR_PORT(delta_init);
	SET_OSD_CTRL_REG_WR_PORT(step);
	tmp = ( (0 != data_sign) << 7 ) | ( (0 != delta_sign) << 6 ) | ( delta & 0x3f );
	SET_OSD_CTRL_REG_WR_PORT(tmp);
	SET_OSD_CTRL_REG_WR_PORT(length0 & 0xff);
	tmp = ( (length1 & 0x0f) << 4 ) | ( (length0 & 0x700) >> 8 );
	SET_OSD_CTRL_REG_WR_PORT(tmp);
	tmp = ( ( 0 != hv_sign ) << 7 ) | ( (length1 & 0x7f0) >> 4 );
	SET_OSD_CTRL_REG_WR_PORT(tmp);
	tmp = ( (0 != overflow_en) << 7 ) | (md & 0x3);
	SET_OSD_CTRL_REG_WR_PORT(tmp);
}


void OSDConfGDCurveV(BYTE ci, BYTE pixel_init, BYTE delta_init,
                     BYTE step, BYTE data_sign, BYTE delta_sign, BYTE delta, WORD length0, WORD length1,
                     BYTE overflow_en, BYTE md)
{
	BYTE tmp;
	_CTRL_OSD_GD_REGISTERS();
	CLR_OSD_GD_REG_CURVE_RDATA_EN();
	_CTRL_OSD_CTRL_REGISTERS();
	SET_OSD_CTRL_REG_TRIG_MODE(_TRIG_MODE_GD_ADDR);
	ci <<= 1;
	ci++;
	SET_OSD_CTRL_REG_WR_PORT(ci);
	SET_OSD_CTRL_REG_TRIG_MODE(_TRIG_MODE_GD_DATA);
	SET_OSD_CTRL_REG_WR_PORT(pixel_init);
	SET_OSD_CTRL_REG_WR_PORT(delta_init);
	SET_OSD_CTRL_REG_WR_PORT(step);
	tmp = ( (0 != data_sign) << 7 ) | ( (0 != delta_sign) << 6 ) | ( delta & 0x3f );
	SET_OSD_CTRL_REG_WR_PORT(tmp);
	SET_OSD_CTRL_REG_WR_PORT(length0);
	tmp = ( (length1 & 0x0f) << 4 ) | ( (length0 & 0x700) >> 8 );
	SET_OSD_CTRL_REG_WR_PORT(tmp);
	tmp = ( (length1 & 0x7f0) >> 4 );
	SET_OSD_CTRL_REG_WR_PORT(tmp);
	tmp = ( (0 != overflow_en) << 7 ) | (md & 0x3);
	SET_OSD_CTRL_REG_WR_PORT(tmp);
}

void OSDGDCurveSelectionForWindow(BYTE gi, BYTE wi, BYTE ci)
{
#define SET_GDX_WINY_CURV_SEL(gi, wi, ci) SET_OSD_GD_REG_GD##gi##_WIN##wi##_CUR_SEL(ci);
#define DEF_SET_GD_WINX_CURV_SEL(gi, wi, ci) switch (wi) { \
		case 0: SET_GDX_WINY_CURV_SEL(gi, 0, ci); break; \
		case 1: SET_GDX_WINY_CURV_SEL(gi, 1, ci); break; \
		case 2: SET_GDX_WINY_CURV_SEL(gi, 2, ci); break; \
		case 3: SET_GDX_WINY_CURV_SEL(gi, 3, ci); break; \
		case 4: SET_GDX_WINY_CURV_SEL(gi, 4, ci); break; \
		case 5: SET_GDX_WINY_CURV_SEL(gi, 5, ci); break; \
		case 6: SET_GDX_WINY_CURV_SEL(gi, 6, ci); break; \
		case 7: SET_GDX_WINY_CURV_SEL(gi, 7, ci); break; \
		default: ; }
#define DEF_SET_GDX_WINY_CURV_SEL(gi, wi, ci) switch (gi) { \
		case 0: DEF_SET_GD_WINX_CURV_SEL(0, wi, ci); break; \
		case 1: DEF_SET_GD_WINX_CURV_SEL(1, wi, ci); break; \
		case 2: DEF_SET_GD_WINX_CURV_SEL(2, wi, ci); break; \
		case 3: DEF_SET_GD_WINX_CURV_SEL(3, wi, ci); break; \
		case 4: DEF_SET_GD_WINX_CURV_SEL(4, wi, ci); break; \
		case 5: DEF_SET_GD_WINX_CURV_SEL(5, wi, ci); break; \
		default: ; }
	#if 0
	SET_OSD_GD_REG_GD0_WIN0_CUR_SEL(V);
	#endif
	_CTRL_OSD_GD_REGISTERS();
	DEF_SET_GDX_WINY_CURV_SEL(gi, wi, ci);
}

void drvOSD_SetGDEngineEnableWnd(void)
{
	BYTE i;
	for (i = 0; i < 255; i++)
	{
		OSDSetMask0(i, 0);
	}
	#if 0
	OSDGDCurveSelectionForWindow(OSD_GD_EG3, OSD_CURSOR_WND, 0);
//OSDConfGDCurveH( ci, Hpixel_init, Hdelta_init, Hstep, Hdata_sign, Hdelta_sign, Hdelta, Hlength0, Hlength1, hv_sign, Hoverflow_en, Hmd );
	OSDConfGDCurveH( 0,        0x00,        0x00,     0,          0,           0,      0,   0xffff,   0xffff,       0,            0,   0 );
//OSDConfGDCurveV( ci, Vpixel_init, Vdelta_init, Vstep, Vdata_sign, Vdelta_sign, Vdelta, Vlength0, Vlength1, Voverflow_en, Vmd );
	OSDConfGDCurveV( 0,        0xFF,        0x0F,     0,          1,           0,      0,       18,        0,            0,   0 );
	OSDGDCurveSelectionForWindow(OSD_GD_EG4, OSD_MAIN_WND, 1);
//OSDConfGDCurveH( ci, Hpixel_init, Hdelta_init, Hstep, Hdata_sign, Hdelta_sign, Hdelta, Hlength0, Hlength1, hv_sign, Hoverflow_en, Hmd );
	OSDConfGDCurveH( 1,        0x00,        0x00,     0,          0,           0,      0,   0xffff,   0xffff,       0,            0,   0 );
//OSDConfGDCurveV( ci, Vpixel_init, Vdelta_init, Vstep, Vdata_sign, Vdelta_sign, Vdelta, Vlength0, Vlength1, Voverflow_en, Vmd );
	OSDConfGDCurveV( 1,        0xFF,        0x03,     0,          1,           0,      0,       90,   216 - 90,            0,   0 );
	#endif
}

#elif CHIP_ID == CHIP_TSUMV

void drvOSD_SetGDEngineEnableWnd(BYTE u8GDEngine, WORD u16EnableFlags, WORD u16Mask)
{
	BYTE xdata u8Bank = msReadByte(OSD1_00);
	WORD xdata u16Addr;
	msWriteByte(OSD1_00, 0x01); //subbank 1
	if (u8GDEngine < OSD_GD_EG4)
		u16Addr = OSD1_44 + u8GDEngine;
	else
		u16Addr = OSD1_EC + (u8GDEngine - OSD_GD_EG4); // gd4/gd5 //110627
	if (u16EnableFlags & 0xFF) //for wnd
	{
		msWriteByteMask(u16Addr, (u16EnableFlags & 0xFF), (u16Mask & 0xFF));
	}
	u16EnableFlags &= 0x0F00;
	u16Mask &= 0x0F00;
	if (u16Mask) //for timing gen
	{
		if (u8GDEngine & 0x01) //GD1/GD3/GD5
		{
			u16EnableFlags >>= 4;
			u16Mask >>= 4;
		}
		else //GD0/GD2/GD4
		{
			u16EnableFlags >>= 8;
			u16Mask >>= 8;
		}
		msWriteByteMask(OSD1_EE + (u8GDEngine >> 1), u16EnableFlags, u16Mask); //110627
	}
	msWriteByte(OSD1_00, u8Bank);
}
#endif

void drvOSD_FrameColorEnable(Bool bEnable)
{
	msWriteByteMask(SC0_32, (bEnable ? BIT0 : 0), BIT0);
}
void drvOSD_FrameColorRGB(BYTE u8Red, BYTE u8Green, BYTE u8Blue)
{
	msWriteByte(SC0_33, u8Red);
	msWriteByte(SC0_34, u8Green);
	msWriteByte(SC0_35, u8Blue);
}

// wait for coding
//extern void Osd_LoadColorPalette( void );

void drvOSD_uncall(void)
{
	drvOSD_DrawBlankPlane(0, 0, 0, 0, 0);
	drvOSD_GetWndInfo(0, 0);
	drvOSD_SetWndOn(0, 0);
	drvOSD_SetWndCtrl(0, 0, 0, 0);
	drvOSD_SetWndFixAlpha(0, 0, 0);
	drvOSD_SetWndFixColor(0, 0, 0, 0);
	drvOSD_SetWndShiftPixel(0, 0, 0);
	drvOSD_SetWndCABaseAddr(0, 0);
	drvOSD_SetWndFixAttr(0, 0, 0);
	drvOSD_SetWndLineOffset(0, 0);
	//Osd_LoadColorPalette();
}
