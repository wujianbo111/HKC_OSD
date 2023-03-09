
#ifndef _DRVOSD_H
#define _DRVOSD_H

#ifdef _DRVOSD_C
#define INTERFACE
#else
#define INTERFACE   extern
#endif

#define SPACE_FONT      0x00

#define OSD_WIN0        0
#define OSD_WIN1        1
#define OSD_WIN2        2
#define OSD_WIN3        3
#define OSD_WIN4        4
#define OSD_WIN5        5
#define OSD_WIN6        6
#define OSD_WIN7        7

#define OSD_WND_CTRL0               0
#define OSD_WND_CTRL1               1
#define OSD_WND_CTRL2               2
#define OSD_WND_CTRL3               3

#define OSD_WND_INFO_H_START        0
#define OSD_WND_INFO_V_START        1
#define OSD_WND_INFO_V_END          2
#define OSD_WND_INFO_LINE_OFFSET    3
#define OSD_WND_INFO_CABASE         4
#define OSD_WND_INFO_H_END			5

#define OSD_GD_WIN0_EN_BIT          BIT0
#define OSD_GD_WIN1_EN_BIT          BIT1
#define OSD_GD_WIN2_EN_BIT          BIT2
#define OSD_GD_WIN3_EN_BIT          BIT3
#define OSD_GD_WIN4_EN_BIT          BIT4
#define OSD_GD_WIN5_EN_BIT          BIT5
#define OSD_GD_WIN6_EN_BIT          BIT6
#define OSD_GD_WIN7_EN_BIT          BIT7
#define OSD_GD_TG0_EN_BIT           BIT8
#define OSD_GD_TG1_EN_BIT           BIT9
#define OSD_GD_TG2_EN_BIT           BIT10
#define OSD_GD_TG3_EN_BIT           BIT11

#define OSD_GD_EG0                  0x0000ul
#define OSD_GD_EG1                  0x0001ul
#define OSD_GD_EG2                  0x0002ul
#define OSD_GD_EG3                  0x0003ul
#define OSD_GD_EG4                  0x0004ul
#define OSD_GD_EG5                  0x0005ul
#define OSD_A_FIX                   0x0006ul
#define OSD_COLOR_FIX               0x0006ul

#define OSD_ALPHA_LV1               0
#define OSD_ALPHA_LV2               1
#define OSD_ALPHA_OUT               2

//OSD Wnd Ctrl 0
#define OWC0_CA_DUP_MODE            BIT1
#define OWC0_FP_MODE                BIT2
#define OWC0_GROUP_SEL0             0
#define OWC0_GROUP_SEL1             BIT3
#define OWC0_OUT_ALPHA_SRC(GD_EG)   ((GD_EG)<<4)
#define OWC0_LV1_ALPHA_SRC(GD_EG)   ((GD_EG)<<8)
#define OWC0_LV2_ALPHA_SRC(GD_EG)   ((GD_EG)<<12)
#define OWC0MASK_CA_DUP_MODE        OWC0_CA_DUP_MODE
#define OWC0MASK_FP_MODE            OWC0_FP_MODE
#define OWC0MASK_GROUP_SEL          OWC0_GROUP_SEL1
#define OWC0MASK_OUT_ALPHA_SRC      (BIT6|BIT5|BIT4)
#define OWC0MASK_LV1_ALPHA_SRC      (BIT10|BIT9|BIT8)
#define OWC0MASK_LV2_ALPHA_SRC      (BIT14|BIT13|BIT12)
#define OWC0MASK_ALL                (OWC0MASK_CA_DUP_MODE|OWC0MASK_FP_MODE|OWC0MASK_GROUP_SEL|OWC0MASK_OUT_ALPHA_SRC|OWC0MASK_LV1_ALPHA_SRC|OWC0MASK_LV2_ALPHA_SRC)
//OSD Wnd Ctrl 1
#define OWC1_FONT_HEIGHT(height)    (height-1)
#define OWC1_44MODE_TRS_EN          BIT14
#define OWC1_1BP_44MODE_EN          BIT15
#define OWC1MASK_FONT_HEIGHT        (0x001F)
#define OWC1MASK_44MODE_TRS_EN      BIT14
#define OWC1MASK_1BP_44MODE_EN      BIT15
#define OWC1MASK_ALL                (OWC1MASK_FONT_HEIGHT|OWC1MASK_44MODE_TRS_EN|OWC1MASK_1BP_44MODE_EN)
//OSD Wnd Ctrl 2
#define OWC2_GD_COLOR_R(GD_EG)      ((GD_EG))
#define OWC2_GD_COLOR_G(GD_EG)      ((GD_EG)<<4)
#define OWC2_GD_COLOR_B(GD_EG)      ((GD_EG)<<8)
#define OWC2MASK_GD_COLOR_R         (BIT0|BIT1|BIT2)
#define OWC2MASK_GD_COLOR_G         (BIT4|BIT5|BIT6)
#define OWC2MASK_GD_COLOR_B         (BIT8|BIT9|BIT10)
#define OWC2MASK_ALL                (OWC2MASK_GD_COLOR_R|OWC2MASK_GD_COLOR_G|OWC2MASK_GD_COLOR_B)
//OSD Wnd Ctrl 3
#define OWC3_1BPP_ATTR_BIT1         BIT8
#define OWC3_LV1_KM_SWITCH          BIT11
#define OWC3_TRANS_INV              BIT12
#define OWC3_CKEY_INV               BIT13
#define OWC3MASK_1BPP_ATTR_BIT1     BIT8
#define OWC3MASK_LV1_KM_SWITCH      BIT11
#define OWC3MASK_TRANS_INV          BIT12
#define OWC3MASK_CKEY_INV           BIT13
#define OWC3MASK_ALL                (OWC3MASK_1BPP_ATTR_BIT1|OWC3MASK_LV1_KM_SWITCH|OWC3MASK_TRANS_INV|OWC3MASK_CKEY_INV)


// for OSD rotation
#define GET_CABASE_0_90(u16Base,u8LineOffset)           (u16Base+u8LineOffset-1)
#define GET_CABASE_90_0(u16Base,u8LineOffset)           (u16Base+1-u8LineOffset)

#define GET_CABASE_0_180(u16Base,u8LineOffset,u8H)      (u16Base+(WORD)u8LineOffset*u8H-1)
#define GET_CABASE_180_0(u16Base,u8LineOffset,u8H)      (u16Base+1-(WORD)u8LineOffset*u8H)

#define GET_CABASE_0_270(u16Base,u8LineOffset,u8H)      (u16Base+(WORD)u8LineOffset*(u8H-1))
#define GET_CABASE_270_0(u16Base,u8LineOffset,u8H)      (u16Base-(WORD)u8LineOffset*(u8H-1))
#if 0//ENABLE_OSD_ROTATION
INTERFACE WORD drvOSD_GetTxtCAStart(BYTE u8Wnd, BYTE u8XPos, BYTE u8YPos);
#define GET_TXT_CASTART(u8Wnd,u8XPos,u8YPos) drvOSD_GetTxtCAStart(u8Wnd,u8XPos,u8YPos)
#else //u8Wnd*0x20=u8Wnd<<5
#define GET_TXT_CASTART(u8Wnd,u8XPos,u8YPos) (msRead2Byte((u8Wnd<<5)+OSD2_10)+(WORD)u8YPos*msReadByte((u8Wnd<<5)+OSD2_12)+u8XPos)
#endif
INTERFACE void drvOSD_DrawVContinuousChar(BYTE u8Wnd, BYTE u8XPos, BYTE u8YPos, BYTE u8Char, BYTE u8Num);
INTERFACE void drvOSD_DrawBlankPlane(BYTE u8Wnd, BYTE u8XPos, BYTE u8YPos, BYTE u8Width, BYTE u8Height);
INTERFACE void drvOSD_SetWndLineOffset(BYTE u8Wnd, BYTE u8LineOffset);
#if !ENABLE_MENULOAD//||!ENABLE_SW_DOUBLE_BUFFER
INTERFACE void drvOSD_SetWndHPosition(BYTE u8Wnd, WORD u16HStart, WORD u16HEnd);
INTERFACE void drvOSD_SetWndVPosition(BYTE u8Wnd, WORD u16VStart, WORD u16VEnd);
#endif
INTERFACE WORD drvOSD_GetWndInfo(BYTE u8Wnd, BYTE u8Dir);
INTERFACE void drvOSD_SetWndOn(BYTE u8Wnd, Bool u8On);
INTERFACE void drvOSD_SetWndCtrl(BYTE u8Wnd, BYTE u8CtrlType, WORD u16Value, WORD u16Mask);
INTERFACE void drvOSD_SetWndFixAlpha(BYTE u8Wnd, BYTE u8Lvl, BYTE u8Value);
INTERFACE void drvOSD_SetWndFixColor(BYTE u8Wnd, BYTE u8Red, BYTE u8Green, BYTE u8Blue);
INTERFACE void drvOSD_SetWndCABaseAddr(BYTE u8Wnd, WORD u16Addr);
INTERFACE void drvOSD_SetWndFixAttr(BYTE u8Wnd, BYTE u8Enable, BYTE u8Attr);
INTERFACE void drvOSD_SetWndShiftPixel(BYTE u8Wnd, u8X, u8Y);
INTERFACE WORD drvOSD_GetWndInfo(BYTE u8Wnd, BYTE u8Dir);
#if CHIP_ID >= CHIP_TSUM2
INTERFACE void drvOSD_SetGDEngineEnableWnd();
#elif CHIP_ID == CHIP_TSUMV
INTERFACE void drvOSD_SetGDEngineEnableWnd(BYTE u8GDEngine, WORD u16EnableFlags, WORD u16Mask);
#endif
INTERFACE void drvOSD_FrameColorEnable(Bool bEnable);
INTERFACE void drvOSD_FrameColorRGB(BYTE u8Red, BYTE u8Green, BYTE u8Blue);
INTERFACE void drvOSD_uncall(void);

#undef INTERFACE

#if CHIP_ID >= CHIP_TSUM2

#define _TRIG_MODE_INIT_ADDR    0
#define _TRIG_MODE_CODE         1
#define _TRIG_MODE_ATTR         2
#define _TRIG_MODE_FONT         3
#define _TRIG_MODE_ERASE        4
#define _TRIG_MODE_READ         5
#define _TRIG_MODE_END_ADDR     6
#define _TRIG_MODE_DUP_CODE     7
#define _TRIG_MODE_DUP_ATTR     8

#define _TRIG_MODE_P0_ADDR      10
#define _TRIG_MODE_P0_MASK      11
#define _TRIG_MODE_P0_CKEY      12
#define _TRIG_MODE_P0_COLOR     13
#define _TRIG_MODE_P0_ERASE     14
#define _TRIG_MODE_P0_READ      15

#define _TRIG_MODE_P1_ADDR      20
#define _TRIG_MODE_P1_CKEY      21
#define _TRIG_MODE_P1_COLOR     22
#define _TRIG_MODE_P1_ERASE     23
#define _TRIG_MODE_P1_READ      24

#define _TRIG_MODE_GD_ADDR      0x1E
#define _TRIG_MODE_GD_DATA      0x1F



#define _CTRL_OSD_CTRL_REGISTERS() msWriteByte( 0x1C00, 0x0 );
#define /*REG_1C00[1:0];h0000[1:0]=h0*/ GET_OSD_CTRL_REG_OSD_SUBBANK() \
	( msReadByte( 0x1C00 ) & 0x03 )
#define /*REG_1C00[1:0];h0000[1:0]=h0*/ SET_OSD_CTRL_REG_OSD_SUBBANK( V ) \
	msWriteByteMask( 0x1C00, (V), 0x03 );
/*
OSD BK1C subbank:
0: OSD_ctrl
1: OSD_gd*/
#define /*REG_1C02[0:0];h0001[0:0]=h1*/ GET_OSD_CTRL_REG_OSD_EN() \
	( 0 != ( msReadByte( 0x1C02 ) & 0x01 ) )
#define /*REG_1C02[0:0];h0001[0:0]=h1*/ SET_OSD_CTRL_REG_OSD_EN() \
	msWriteByteMask( 0x1C02, 0xFF, 0x01 );
#define /*REG_1C02[0:0];h0001[0:0]=h1*/ CLR_OSD_CTRL_REG_OSD_EN() \
	msWriteByteMask( 0x1C02, 0x0, 0x01 );
#define /*REG_1C02[0:0];h0001[0:0]=h1*/ ASG_OSD_CTRL_REG_OSD_EN( V ) \
	msWriteByteMask( 0x1C02, ( 0 != (V) )? 0x01: 0, 0x01 );
/*
OSD osd_en*/
#define /*REG_1C02[1:1];h0001[1:1]=h0*/ GET_OSD_CTRL_REG_OSD_FORCE_BLEND() \
	( 0 != ( msReadByte( 0x1C02 ) & 0x02 ) )
#define /*REG_1C02[1:1];h0001[1:1]=h0*/ SET_OSD_CTRL_REG_OSD_FORCE_BLEND() \
	msWriteByteMask( 0x1C02, 0xFF, 0x02 );
#define /*REG_1C02[1:1];h0001[1:1]=h0*/ CLR_OSD_CTRL_REG_OSD_FORCE_BLEND() \
	msWriteByteMask( 0x1C02, 0x0, 0x02 );
#define /*REG_1C02[1:1];h0001[1:1]=h0*/ ASG_OSD_CTRL_REG_OSD_FORCE_BLEND( V ) \
	msWriteByteMask( 0x1C02, ( 0 != (V) )? 0x02: 0, 0x02 );
/*
OSD font force blend*/
#define /*REG_1C02[2:2];h0001[2:2]=h0*/ GET_OSD_CTRL_REG_OSD2IP_EN() \
	( 0 != ( msReadByte( 0x1C02 ) & 0x04 ) )
#define /*REG_1C02[2:2];h0001[2:2]=h0*/ SET_OSD_CTRL_REG_OSD2IP_EN() \
	msWriteByteMask( 0x1C02, 0xFF, 0x04 );
#define /*REG_1C02[2:2];h0001[2:2]=h0*/ CLR_OSD_CTRL_REG_OSD2IP_EN() \
	msWriteByteMask( 0x1C02, 0x0, 0x04 );
#define /*REG_1C02[2:2];h0001[2:2]=h0*/ ASG_OSD_CTRL_REG_OSD2IP_EN( V ) \
	msWriteByteMask( 0x1C02, ( 0 != (V) )? 0x04: 0, 0x04 );
/*
OSD osd to ip enable*/
#define /*REG_1C02[4:3];h0001[4:3]=h0*/ GET_OSD_CTRL_REG_OSD_FT_SEL() \
	( ( msReadByte( 0x1C02 ) & 0x18 ) >>  3 )
#define /*REG_1C02[4:3];h0001[4:3]=h0*/ SET_OSD_CTRL_REG_OSD_FT_SEL( V ) \
	msWriteByteMask( 0x1C02, ((V) <<  3), 0x18 );
/*
OSD front clk select:
0: mclk 200
1: mpll 172
2: odclk
3: idclk*/
#define /*REG_1C02[5:5];h0001[5:5]=h0*/ GET_OSD_CTRL_REG_VS_ORI() \
	( 0 != ( msReadByte( 0x1C02 ) & 0x20 ) )
#define /*REG_1C02[5:5];h0001[5:5]=h0*/ SET_OSD_CTRL_REG_VS_ORI() \
	msWriteByteMask( 0x1C02, 0xFF, 0x20 );
#define /*REG_1C02[5:5];h0001[5:5]=h0*/ CLR_OSD_CTRL_REG_VS_ORI() \
	msWriteByteMask( 0x1C02, 0x0, 0x20 );
#define /*REG_1C02[5:5];h0001[5:5]=h0*/ ASG_OSD_CTRL_REG_VS_ORI( V ) \
	msWriteByteMask( 0x1C02, ( 0 != (V) )? 0x20: 0, 0x20 );
/*
OSD osd vs use original vs signal*/
#define /*REG_1C02[6:6];h0001[6:6]=h0*/ GET_OSD_CTRL_REG_VS_INV() \
	( 0 != ( msReadByte( 0x1C02 ) & 0x40 ) )
#define /*REG_1C02[6:6];h0001[6:6]=h0*/ SET_OSD_CTRL_REG_VS_INV() \
	msWriteByteMask( 0x1C02, 0xFF, 0x40 );
#define /*REG_1C02[6:6];h0001[6:6]=h0*/ CLR_OSD_CTRL_REG_VS_INV() \
	msWriteByteMask( 0x1C02, 0x0, 0x40 );
#define /*REG_1C02[6:6];h0001[6:6]=h0*/ ASG_OSD_CTRL_REG_VS_INV( V ) \
	msWriteByteMask( 0x1C02, ( 0 != (V) )? 0x40: 0, 0x40 );
/*
OSD osd vs inverse*/
#define /*REG_1C02[7:7];h0001[7:7]=h1*/ GET_OSD_CTRL_REG_OSD_VST_DELAY() \
	( 0 != ( msReadByte( 0x1C02 ) & 0x80 ) )
#define /*REG_1C02[7:7];h0001[7:7]=h1*/ SET_OSD_CTRL_REG_OSD_VST_DELAY() \
	msWriteByteMask( 0x1C02, 0xFF, 0x80 );
#define /*REG_1C02[7:7];h0001[7:7]=h1*/ CLR_OSD_CTRL_REG_OSD_VST_DELAY() \
	msWriteByteMask( 0x1C02, 0x0, 0x80 );
#define /*REG_1C02[7:7];h0001[7:7]=h1*/ ASG_OSD_CTRL_REG_OSD_VST_DELAY( V ) \
	msWriteByteMask( 0x1C02, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
OSD osd vst delay*/
#define /*REG_1C03[0:0];h0001[8:8]=h0*/ GET_OSD_CTRL_REG_OSD_ALPHA_INV() \
	( 0 != ( msReadByte( 0x1C03 ) & 0x01 ) )
#define /*REG_1C03[0:0];h0001[8:8]=h0*/ SET_OSD_CTRL_REG_OSD_ALPHA_INV() \
	msWriteByteMask( 0x1C03, 0xFF, 0x01 );
#define /*REG_1C03[0:0];h0001[8:8]=h0*/ CLR_OSD_CTRL_REG_OSD_ALPHA_INV() \
	msWriteByteMask( 0x1C03, 0x0, 0x01 );
#define /*REG_1C03[0:0];h0001[8:8]=h0*/ ASG_OSD_CTRL_REG_OSD_ALPHA_INV( V ) \
	msWriteByteMask( 0x1C03, ( 0 != (V) )? 0x01: 0, 0x01 );
/*
OSD osd to sc alpha inverse*/
#define /*REG_1C03[1:1];h0001[9:9]=h1*/ GET_OSD_CTRL_REG_OSD_DE_END_INT_EN() \
	( 0 != ( msReadByte( 0x1C03 ) & 0x02 ) )
#define /*REG_1C03[1:1];h0001[9:9]=h1*/ SET_OSD_CTRL_REG_OSD_DE_END_INT_EN() \
	msWriteByteMask( 0x1C03, 0xFF, 0x02 );
#define /*REG_1C03[1:1];h0001[9:9]=h1*/ CLR_OSD_CTRL_REG_OSD_DE_END_INT_EN() \
	msWriteByteMask( 0x1C03, 0x0, 0x02 );
#define /*REG_1C03[1:1];h0001[9:9]=h1*/ ASG_OSD_CTRL_REG_OSD_DE_END_INT_EN( V ) \
	msWriteByteMask( 0x1C03, ( 0 != (V) )? 0x02: 0, 0x02 );
/*
enable osd de end interrupt*/
#define /*REG_1C03[2:2];h0001[10:10]=h0*/ GET_OSD_CTRL_REG_WR_OVER_DIS() \
	( 0 != ( msReadByte( 0x1C03 ) & 0x04 ) )
#define /*REG_1C03[2:2];h0001[10:10]=h0*/ SET_OSD_CTRL_REG_WR_OVER_DIS() \
	msWriteByteMask( 0x1C03, 0xFF, 0x04 );
#define /*REG_1C03[2:2];h0001[10:10]=h0*/ CLR_OSD_CTRL_REG_WR_OVER_DIS() \
	msWriteByteMask( 0x1C03, 0x0, 0x04 );
#define /*REG_1C03[2:2];h0001[10:10]=h0*/ ASG_OSD_CTRL_REG_WR_OVER_DIS( V ) \
	msWriteByteMask( 0x1C03, ( 0 != (V) )? 0x04: 0, 0x04 );
/*
OSD wr priority is over display for both cafsram/psram*/
#define /*REG_1C03[3:3];h0001[11:11]=h0*/ GET_OSD_CTRL_REG_TST_PAT_MODE() \
	( 0 != ( msReadByte( 0x1C03 ) & 0x08 ) )
#define /*REG_1C03[3:3];h0001[11:11]=h0*/ SET_OSD_CTRL_REG_TST_PAT_MODE() \
	msWriteByteMask( 0x1C03, 0xFF, 0x08 );
#define /*REG_1C03[3:3];h0001[11:11]=h0*/ CLR_OSD_CTRL_REG_TST_PAT_MODE() \
	msWriteByteMask( 0x1C03, 0x0, 0x08 );
#define /*REG_1C03[3:3];h0001[11:11]=h0*/ ASG_OSD_CTRL_REG_TST_PAT_MODE( V ) \
	msWriteByteMask( 0x1C03, ( 0 != (V) )? 0x08: 0, 0x08 );
/*
OSD test pattern mode*/
#define /*REG_1C03[4:4];h0001[12:12]=h0*/ GET_OSD_CTRL_REG_OSD2IP_DE_SEL() \
	( 0 != ( msReadByte( 0x1C03 ) & 0x10 ) )
#define /*REG_1C03[4:4];h0001[12:12]=h0*/ SET_OSD_CTRL_REG_OSD2IP_DE_SEL() \
	msWriteByteMask( 0x1C03, 0xFF, 0x10 );
#define /*REG_1C03[4:4];h0001[12:12]=h0*/ CLR_OSD_CTRL_REG_OSD2IP_DE_SEL() \
	msWriteByteMask( 0x1C03, 0x0, 0x10 );
#define /*REG_1C03[4:4];h0001[12:12]=h0*/ ASG_OSD_CTRL_REG_OSD2IP_DE_SEL( V ) \
	msWriteByteMask( 0x1C03, ( 0 != (V) )? 0x10: 0, 0x10 );
/*
OSD to IP de select:
0 : hs inverse
1: IP de*/
#define /*REG_1C03[7:6];h0001[15:14]=h0*/ GET_OSD_CTRL_REG_ROT_ANGLE() \
	( ( msReadByte( 0x1C03 ) & 0xC0 ) >>  6 )
#define /*REG_1C03[7:6];h0001[15:14]=h0*/ SET_OSD_CTRL_REG_ROT_ANGLE( V ) \
	msWriteByteMask( 0x1C03, ((V) <<  6), 0xC0 );
/*
0 : not rotate      1: 90  2: 180 3: 270*/
#define /*REG_1C04[11:0];h0002[11:0]=h0*/ GET_OSD_CTRL_REG_OSD_HSIZE() \
	( msReadByte( 0x1C04 ) | ( (msReadByte( 0x1C05 ) & 0x0F) <<  8 ) )
#define /*REG_1C04[11:0];h0002[11:0]=h0*/ SET_OSD_CTRL_REG_OSD_HSIZE( V ) \
	{ msWriteByte( 0x1C04, (V) ); msWriteByteMask( 0x1C05, ((V) >>  8), 0x0F ); }
/*
OSD hsize (unit : pix) */
#define /*REG_1C06[11:0];h0003[11:0]=h0*/ GET_OSD_CTRL_REG_OSD_VSIZE() \
	( msReadByte( 0x1C06 ) | ( (msReadByte( 0x1C07 ) & 0x0F) <<  8 ) )
#define /*REG_1C06[11:0];h0003[11:0]=h0*/ SET_OSD_CTRL_REG_OSD_VSIZE( V ) \
	{ msWriteByte( 0x1C06, (V) ); msWriteByteMask( 0x1C07, ((V) >>  8), 0x0F ); }
/*
OSD vsize (unit : line)*/
#define /*REG_1C08[11:0];h0004[11:0]=h0*/ GET_OSD_CTRL_REG_FONT_BASE_ENTRY() \
	( msReadByte( 0x1C08 ) | ( (msReadByte( 0x1C09 ) & 0x0F) <<  8 ) )
#define /*REG_1C08[11:0];h0004[11:0]=h0*/ SET_OSD_CTRL_REG_FONT_BASE_ENTRY( V ) \
	{ msWriteByte( 0x1C08, (V) ); msWriteByteMask( 0x1C09, ((V) >>  8), 0x0F ); }
/*
OSD font start addr(entry) in sram*/
#define /*REG_1C0A[9:0];h0005[9:0]=h0*/ GET_OSD_CTRL_REG_2BPP_STR_UNIT() \
	( msReadByte( 0x1C0A ) | ( (msReadByte( 0x1C0B ) & 0x03) <<  8 ) )
#define /*REG_1C0A[9:0];h0005[9:0]=h0*/ SET_OSD_CTRL_REG_2BPP_STR_UNIT( V ) \
	{ msWriteByte( 0x1C0A, (V) ); msWriteByteMask( 0x1C0B, ((V) >>  8), 0x03 ); }
/*
OSD 2bpp start unit (unit : reg_unit_size)*/
#define /*REG_1C0C[9:0];h0006[9:0]=h0*/ GET_OSD_CTRL_REG_3BPP_STR_UNIT() \
	( msReadByte( 0x1C0C ) | ( (msReadByte( 0x1C0D ) & 0x03) <<  8 ) )
#define /*REG_1C0C[9:0];h0006[9:0]=h0*/ SET_OSD_CTRL_REG_3BPP_STR_UNIT( V ) \
	{ msWriteByte( 0x1C0C, (V) ); msWriteByteMask( 0x1C0D, ((V) >>  8), 0x03 ); }
/*
OSD 3bpp start unit (unit : reg_unit_size)*/
#define /*REG_1C0E[9:0];h0007[9:0]=h0*/ GET_OSD_CTRL_REG_4BPP_STR_UNIT() \
	( msReadByte( 0x1C0E ) | ( (msReadByte( 0x1C0F ) & 0x03) <<  8 ) )
#define /*REG_1C0E[9:0];h0007[9:0]=h0*/ SET_OSD_CTRL_REG_4BPP_STR_UNIT( V ) \
	{ msWriteByte( 0x1C0E, (V) ); msWriteByteMask( 0x1C0F, ((V) >>  8), 0x03 ); }
/*
OSD 4bpp start unit (unit : reg_unit_size)*/
#define /*REG_1C0B[5:4];h0005[13:12]=h0*/ GET_OSD_CTRL_REG_UNIT_SIZE() \
	( ( msReadByte( 0x1C0B ) & 0x30 ) >>  4 )
#define /*REG_1C0B[5:4];h0005[13:12]=h0*/ SET_OSD_CTRL_REG_UNIT_SIZE( V ) \
	msWriteByteMask( 0x1C0B, ((V) <<  4), 0x30 );
/*
OSD basic unit size :
0 : 1 entry
1 : 2 entry
2 : 3 entry
3 : 4 entry*/
#define /*REG_1C12[0:0];h0009[0:0]=h0*/ GET_OSD_CTRL_REG_MASK_FF_UF_FLAG() \
	( 0 != ( msReadByte( 0x1C12 ) & 0x01 ) )
#define /*REG_1C12[0:0];h0009[0:0]=h0*/ SET_OSD_CTRL_REG_MASK_FF_UF_FLAG() \
	msWriteByteMask( 0x1C12, 0xFF, 0x01 );
#define /*REG_1C12[0:0];h0009[0:0]=h0*/ CLR_OSD_CTRL_REG_MASK_FF_UF_FLAG() \
	msWriteByteMask( 0x1C12, 0x0, 0x01 );
#define /*REG_1C12[0:0];h0009[0:0]=h0*/ ASG_OSD_CTRL_REG_MASK_FF_UF_FLAG( V ) \
	msWriteByteMask( 0x1C12, ( 0 != (V) )? 0x01: 0, 0x01 );
/*
OSD ff_uf_flag mask enable*/
#define /*REG_1C16[5:0];h000b[5:0]=h1e*/ GET_OSD_CTRL_REG_HDE_PIPE() \
	( msReadByte( 0x1C16 ) & 0x3F )
#define /*REG_1C16[5:0];h000b[5:0]=h1e*/ SET_OSD_CTRL_REG_HDE_PIPE( V ) \
	msWriteByteMask( 0x1C16, (V), 0x3F );
/*
control the distance between hs and 1st hde*/
#define /*REG_1C18[0:0];h000c[0:0]=h0*/ GET_OSD_CTRL_REG_3D_EN() \
	( 0 != ( msReadByte( 0x1C18 ) & 0x01 ) )
#define /*REG_1C18[0:0];h000c[0:0]=h0*/ SET_OSD_CTRL_REG_3D_EN() \
	msWriteByteMask( 0x1C18, 0xFF, 0x01 );
#define /*REG_1C18[0:0];h000c[0:0]=h0*/ CLR_OSD_CTRL_REG_3D_EN() \
	msWriteByteMask( 0x1C18, 0x0, 0x01 );
#define /*REG_1C18[0:0];h000c[0:0]=h0*/ ASG_OSD_CTRL_REG_3D_EN( V ) \
	msWriteByteMask( 0x1C18, ( 0 != (V) )? 0x01: 0, 0x01 );
/*
OSD 3D line shift mode enable*/
#define /*REG_1C18[1:1];h000c[1:1]=h0*/ GET_OSD_CTRL_REG_3D_LINE_INV() \
	( 0 != ( msReadByte( 0x1C18 ) & 0x02 ) )
#define /*REG_1C18[1:1];h000c[1:1]=h0*/ SET_OSD_CTRL_REG_3D_LINE_INV() \
	msWriteByteMask( 0x1C18, 0xFF, 0x02 );
#define /*REG_1C18[1:1];h000c[1:1]=h0*/ CLR_OSD_CTRL_REG_3D_LINE_INV() \
	msWriteByteMask( 0x1C18, 0x0, 0x02 );
#define /*REG_1C18[1:1];h000c[1:1]=h0*/ ASG_OSD_CTRL_REG_3D_LINE_INV( V ) \
	msWriteByteMask( 0x1C18, ( 0 != (V) )? 0x02: 0, 0x02 );
/*
3D inverse the shift line (odd / even)*/
#define /*REG_1C19[5:0];h000c[13:8]=h0*/ GET_OSD_CTRL_REG_3D_SHIFT_CNT() \
	( msReadByte( 0x1C19 ) & 0x3F )
#define /*REG_1C19[5:0];h000c[13:8]=h0*/ SET_OSD_CTRL_REG_3D_SHIFT_CNT( V ) \
	msWriteByteMask( 0x1C19, (V), 0x3F );
/*
3D shift cnt(unit: pix)*/
#define /*REG_1C20[0:0];h0010[0:0]=h0*/ GET_OSD_CTRL_REG_GDT0_EN() \
	( 0 != ( msReadByte( 0x1C20 ) & 0x01 ) )
#define /*REG_1C20[0:0];h0010[0:0]=h0*/ SET_OSD_CTRL_REG_GDT0_EN() \
	msWriteByteMask( 0x1C20, 0xFF, 0x01 );
#define /*REG_1C20[0:0];h0010[0:0]=h0*/ CLR_OSD_CTRL_REG_GDT0_EN() \
	msWriteByteMask( 0x1C20, 0x0, 0x01 );
#define /*REG_1C20[0:0];h0010[0:0]=h0*/ ASG_OSD_CTRL_REG_GDT0_EN( V ) \
	msWriteByteMask( 0x1C20, ( 0 != (V) )? 0x01: 0, 0x01 );
/*
grading window enable*/
#define /*REG_1C20[6:4];h0010[6:4]=h0*/ GET_OSD_CTRL_REG_GDT0_CLR_R_SEL() \
	( ( msReadByte( 0x1C20 ) & 0x70 ) >>  4 )
#define /*REG_1C20[6:4];h0010[6:4]=h0*/ SET_OSD_CTRL_REG_GDT0_CLR_R_SEL( V ) \
	msWriteByteMask( 0x1C20, ((V) <<  4), 0x70 );
/*
grading window color R select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr r
7.transparent*/
#define /*REG_1C21[6:4];h0010[14:12]=h0*/ GET_OSD_CTRL_REG_GDT0_CLR_G_SEL() \
	( ( msReadByte( 0x1C21 ) & 0x70 ) >>  4 )
#define /*REG_1C21[6:4];h0010[14:12]=h0*/ SET_OSD_CTRL_REG_GDT0_CLR_G_SEL( V ) \
	msWriteByteMask( 0x1C21, ((V) <<  4), 0x70 );
/*
grading window color G select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr g
7.transparent*/
#define /*REG_1C21[2:0];h0010[10:8]=h0*/ GET_OSD_CTRL_REG_GDT0_CLR_B_SEL() \
	( msReadByte( 0x1C21 ) & 0x07 )
#define /*REG_1C21[2:0];h0010[10:8]=h0*/ SET_OSD_CTRL_REG_GDT0_CLR_B_SEL( V ) \
	msWriteByteMask( 0x1C21, (V), 0x07 );
/*
grading window color B select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr b
7.transparent*/
#define /*REG_1C22[7:0];h0011[7:0]=h0*/ GET_OSD_CTRL_REG_GDT0_FIX_CLR_R() \
	( msReadByte( 0x1C22 ) )
#define /*REG_1C22[7:0];h0011[7:0]=h0*/ SET_OSD_CTRL_REG_GDT0_FIX_CLR_R( V ) \
	msWriteByte( 0x1C22, (V) );
/*
for lv2 blending : fix grading color R*/
#define /*REG_1C23[7:0];h0011[15:8]=h0*/ GET_OSD_CTRL_REG_GDT0_FIX_CLR_G() \
	( msReadByte( 0x1C23 ) )
#define /*REG_1C23[7:0];h0011[15:8]=h0*/ SET_OSD_CTRL_REG_GDT0_FIX_CLR_G( V ) \
	msWriteByte( 0x1C23, (V) );
/*
for lv2 blending : fix grading color G*/
#define /*REG_1C24[7:0];h0012[7:0]=h0*/ GET_OSD_CTRL_REG_GDT0_FIX_CLR_B() \
	( msReadByte( 0x1C24 ) )
#define /*REG_1C24[7:0];h0012[7:0]=h0*/ SET_OSD_CTRL_REG_GDT0_FIX_CLR_B( V ) \
	msWriteByte( 0x1C24, (V) );
/*
for lv2 blending : fix grading color B*/
#define /*REG_1C28[0:0];h0014[0:0]=h0*/ GET_OSD_CTRL_REG_GDT1_EN() \
	( 0 != ( msReadByte( 0x1C28 ) & 0x01 ) )
#define /*REG_1C28[0:0];h0014[0:0]=h0*/ SET_OSD_CTRL_REG_GDT1_EN() \
	msWriteByteMask( 0x1C28, 0xFF, 0x01 );
#define /*REG_1C28[0:0];h0014[0:0]=h0*/ CLR_OSD_CTRL_REG_GDT1_EN() \
	msWriteByteMask( 0x1C28, 0x0, 0x01 );
#define /*REG_1C28[0:0];h0014[0:0]=h0*/ ASG_OSD_CTRL_REG_GDT1_EN( V ) \
	msWriteByteMask( 0x1C28, ( 0 != (V) )? 0x01: 0, 0x01 );
/*
grading window enable*/
#define /*REG_1C28[6:4];h0014[6:4]=h0*/ GET_OSD_CTRL_REG_GDT1_CLR_R_SEL() \
	( ( msReadByte( 0x1C28 ) & 0x70 ) >>  4 )
#define /*REG_1C28[6:4];h0014[6:4]=h0*/ SET_OSD_CTRL_REG_GDT1_CLR_R_SEL( V ) \
	msWriteByteMask( 0x1C28, ((V) <<  4), 0x70 );
/*
grading window color R select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr r
7.transparent*/
#define /*REG_1C29[6:4];h0014[14:12]=h0*/ GET_OSD_CTRL_REG_GDT1_CLR_G_SEL() \
	( ( msReadByte( 0x1C29 ) & 0x70 ) >>  4 )
#define /*REG_1C29[6:4];h0014[14:12]=h0*/ SET_OSD_CTRL_REG_GDT1_CLR_G_SEL( V ) \
	msWriteByteMask( 0x1C29, ((V) <<  4), 0x70 );
/*
grading window color G select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr g
7.transparent*/
#define /*REG_1C29[2:0];h0014[10:8]=h0*/ GET_OSD_CTRL_REG_GDT1_CLR_B_SEL() \
	( msReadByte( 0x1C29 ) & 0x07 )
#define /*REG_1C29[2:0];h0014[10:8]=h0*/ SET_OSD_CTRL_REG_GDT1_CLR_B_SEL( V ) \
	msWriteByteMask( 0x1C29, (V), 0x07 );
/*
grading window color B select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr b
7.transparent*/
#define /*REG_1C2A[7:0];h0015[7:0]=h0*/ GET_OSD_CTRL_REG_GDT1_FIX_CLR_R() \
	( msReadByte( 0x1C2A ) )
#define /*REG_1C2A[7:0];h0015[7:0]=h0*/ SET_OSD_CTRL_REG_GDT1_FIX_CLR_R( V ) \
	msWriteByte( 0x1C2A, (V) );
/*
for lv2 blending : fix grading color R*/
#define /*REG_1C2B[7:0];h0015[15:8]=h0*/ GET_OSD_CTRL_REG_GDT1_FIX_CLR_G() \
	( msReadByte( 0x1C2B ) )
#define /*REG_1C2B[7:0];h0015[15:8]=h0*/ SET_OSD_CTRL_REG_GDT1_FIX_CLR_G( V ) \
	msWriteByte( 0x1C2B, (V) );
/*
for lv2 blending : fix grading color G*/
#define /*REG_1C2C[7:0];h0016[7:0]=h0*/ GET_OSD_CTRL_REG_GDT1_FIX_CLR_B() \
	( msReadByte( 0x1C2C ) )
#define /*REG_1C2C[7:0];h0016[7:0]=h0*/ SET_OSD_CTRL_REG_GDT1_FIX_CLR_B( V ) \
	msWriteByte( 0x1C2C, (V) );
/*
for lv2 blending : fix grading color B*/
#define /*REG_1C30[0:0];h0018[0:0]=h0*/ GET_OSD_CTRL_REG_GDT2_EN() \
	( 0 != ( msReadByte( 0x1C30 ) & 0x01 ) )
#define /*REG_1C30[0:0];h0018[0:0]=h0*/ SET_OSD_CTRL_REG_GDT2_EN() \
	msWriteByteMask( 0x1C30, 0xFF, 0x01 );
#define /*REG_1C30[0:0];h0018[0:0]=h0*/ CLR_OSD_CTRL_REG_GDT2_EN() \
	msWriteByteMask( 0x1C30, 0x0, 0x01 );
#define /*REG_1C30[0:0];h0018[0:0]=h0*/ ASG_OSD_CTRL_REG_GDT2_EN( V ) \
	msWriteByteMask( 0x1C30, ( 0 != (V) )? 0x01: 0, 0x01 );
/*
grading window enable*/
#define /*REG_1C30[6:4];h0018[6:4]=h0*/ GET_OSD_CTRL_REG_GDT2_CLR_R_SEL() \
	( ( msReadByte( 0x1C30 ) & 0x70 ) >>  4 )
#define /*REG_1C30[6:4];h0018[6:4]=h0*/ SET_OSD_CTRL_REG_GDT2_CLR_R_SEL( V ) \
	msWriteByteMask( 0x1C30, ((V) <<  4), 0x70 );
/*
grading window color R select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr r
7.transparent*/
#define /*REG_1C31[6:4];h0018[14:12]=h0*/ GET_OSD_CTRL_REG_GDT2_CLR_G_SEL() \
	( ( msReadByte( 0x1C31 ) & 0x70 ) >>  4 )
#define /*REG_1C31[6:4];h0018[14:12]=h0*/ SET_OSD_CTRL_REG_GDT2_CLR_G_SEL( V ) \
	msWriteByteMask( 0x1C31, ((V) <<  4), 0x70 );
/*
grading window color G select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr g
7.transparent*/
#define /*REG_1C31[2:0];h0018[10:8]=h0*/ GET_OSD_CTRL_REG_GDT2_CLR_B_SEL() \
	( msReadByte( 0x1C31 ) & 0x07 )
#define /*REG_1C31[2:0];h0018[10:8]=h0*/ SET_OSD_CTRL_REG_GDT2_CLR_B_SEL( V ) \
	msWriteByteMask( 0x1C31, (V), 0x07 );
/*
grading window color B select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr b
7.transparent*/
#define /*REG_1C32[7:0];h0019[7:0]=h0*/ GET_OSD_CTRL_REG_GDT2_FIX_CLR_R() \
	( msReadByte( 0x1C32 ) )
#define /*REG_1C32[7:0];h0019[7:0]=h0*/ SET_OSD_CTRL_REG_GDT2_FIX_CLR_R( V ) \
	msWriteByte( 0x1C32, (V) );
/*
for lv2 blending : fix grading color R*/
#define /*REG_1C33[7:0];h0019[15:8]=h0*/ GET_OSD_CTRL_REG_GDT2_FIX_CLR_G() \
	( msReadByte( 0x1C33 ) )
#define /*REG_1C33[7:0];h0019[15:8]=h0*/ SET_OSD_CTRL_REG_GDT2_FIX_CLR_G( V ) \
	msWriteByte( 0x1C33, (V) );
/*
for lv2 blending : fix grading color G*/
#define /*REG_1C34[7:0];h001a[7:0]=h0*/ GET_OSD_CTRL_REG_GDT2_FIX_CLR_B() \
	( msReadByte( 0x1C34 ) )
#define /*REG_1C34[7:0];h001a[7:0]=h0*/ SET_OSD_CTRL_REG_GDT2_FIX_CLR_B( V ) \
	msWriteByte( 0x1C34, (V) );
/*
for lv2 blending : fix grading color B*/
#define /*REG_1C38[0:0];h001c[0:0]=h0*/ GET_OSD_CTRL_REG_GDT3_EN() \
	( 0 != ( msReadByte( 0x1C38 ) & 0x01 ) )
#define /*REG_1C38[0:0];h001c[0:0]=h0*/ SET_OSD_CTRL_REG_GDT3_EN() \
	msWriteByteMask( 0x1C38, 0xFF, 0x01 );
#define /*REG_1C38[0:0];h001c[0:0]=h0*/ CLR_OSD_CTRL_REG_GDT3_EN() \
	msWriteByteMask( 0x1C38, 0x0, 0x01 );
#define /*REG_1C38[0:0];h001c[0:0]=h0*/ ASG_OSD_CTRL_REG_GDT3_EN( V ) \
	msWriteByteMask( 0x1C38, ( 0 != (V) )? 0x01: 0, 0x01 );
/*
grading window enable*/
#define /*REG_1C38[6:4];h001c[6:4]=h0*/ GET_OSD_CTRL_REG_GDT3_CLR_R_SEL() \
	( ( msReadByte( 0x1C38 ) & 0x70 ) >>  4 )
#define /*REG_1C38[6:4];h001c[6:4]=h0*/ SET_OSD_CTRL_REG_GDT3_CLR_R_SEL( V ) \
	msWriteByteMask( 0x1C38, ((V) <<  4), 0x70 );
/*
grading window color R select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr r
7.transparent*/
#define /*REG_1C39[6:4];h001c[14:12]=h0*/ GET_OSD_CTRL_REG_GDT3_CLR_G_SEL() \
	( ( msReadByte( 0x1C39 ) & 0x70 ) >>  4 )
#define /*REG_1C39[6:4];h001c[14:12]=h0*/ SET_OSD_CTRL_REG_GDT3_CLR_G_SEL( V ) \
	msWriteByteMask( 0x1C39, ((V) <<  4), 0x70 );
/*
grading window color G select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr g
7.transparent*/
#define /*REG_1C39[2:0];h001c[10:8]=h0*/ GET_OSD_CTRL_REG_GDT3_CLR_B_SEL() \
	( msReadByte( 0x1C39 ) & 0x07 )
#define /*REG_1C39[2:0];h001c[10:8]=h0*/ SET_OSD_CTRL_REG_GDT3_CLR_B_SEL( V ) \
	msWriteByteMask( 0x1C39, (V), 0x07 );
/*
grading window color B select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr b
7.transparent*/
#define /*REG_1C3A[7:0];h001d[7:0]=h0*/ GET_OSD_CTRL_REG_GDT3_FIX_CLR_R() \
	( msReadByte( 0x1C3A ) )
#define /*REG_1C3A[7:0];h001d[7:0]=h0*/ SET_OSD_CTRL_REG_GDT3_FIX_CLR_R( V ) \
	msWriteByte( 0x1C3A, (V) );
/*
for lv2 blending : fix grading color R*/
#define /*REG_1C3B[7:0];h001d[15:8]=h0*/ GET_OSD_CTRL_REG_GDT3_FIX_CLR_G() \
	( msReadByte( 0x1C3B ) )
#define /*REG_1C3B[7:0];h001d[15:8]=h0*/ SET_OSD_CTRL_REG_GDT3_FIX_CLR_G( V ) \
	msWriteByte( 0x1C3B, (V) );
/*
for lv2 blending : fix grading color G*/
#define /*REG_1C3C[7:0];h001e[7:0]=h0*/ GET_OSD_CTRL_REG_GDT3_FIX_CLR_B() \
	( msReadByte( 0x1C3C ) )
#define /*REG_1C3C[7:0];h001e[7:0]=h0*/ SET_OSD_CTRL_REG_GDT3_FIX_CLR_B( V ) \
	msWriteByte( 0x1C3C, (V) );
/*
for lv2 blending : fix grading color B*/
#define /*REG_1C51[4:4];h0028[12:12]=*/ GET_OSD_CTRL_REG_OUT_FF_BIST_FAIL() \
	( 0 != ( msReadByte( 0x1C51 ) & 0x10 ) )
/*
2 p ff bist fail*/
#define /*REG_1C51[5:5];h0028[13:13]=*/ GET_OSD_CTRL_REG_PSRAM0_BIST_FAIL() \
	( 0 != ( msReadByte( 0x1C51 ) & 0x20 ) )
/*
psram0 bist fail*/
#define /*REG_1C51[6:6];h0028[14:14]=*/ GET_OSD_CTRL_REG_PSRAM1_BIST_FAIL() \
	( 0 != ( msReadByte( 0x1C51 ) & 0x40 ) )
/*
psram1 bist fail*/
#define /*REG_1C51[7:7];h0028[15:15]=*/ GET_OSD_CTRL_REG_CAFSRAM_BIST_FAIL() \
	( 0 != ( msReadByte( 0x1C51 ) & 0x80 ) )
/*
cafsram bist fail*/
#define /*REG_1C60[35:0];h0030[35:0]= */ GET_OSD_CTRL_REG_CAFSRAM_RD() \
	( msReadByte( 0x1C60 ) | ( msReadByte( 0x1C61 ) <<  8 ) | ( msReadByte( 0x1C62 ) <<  16 ) | ( msReadByte( 0x1C63 ) <<  24 ) | ( (msReadByte( 0x1C64 ) & 0x0F) <<  32 ) )
/*
*/
#define /*REG_1C65[7:7];h0032[15:15]=h0*/ GET_OSD_CTRL_REG_CAFSRAM_RD_SEL() \
	( 0 != ( msReadByte( 0x1C65 ) & 0x80 ) )
#define /*REG_1C65[7:7];h0032[15:15]=h0*/ SET_OSD_CTRL_REG_CAFSRAM_RD_SEL() \
	msWriteByteMask( 0x1C65, 0xFF, 0x80 );
#define /*REG_1C65[7:7];h0032[15:15]=h0*/ CLR_OSD_CTRL_REG_CAFSRAM_RD_SEL() \
	msWriteByteMask( 0x1C65, 0x0, 0x80 );
#define /*REG_1C65[7:7];h0032[15:15]=h0*/ ASG_OSD_CTRL_REG_CAFSRAM_RD_SEL( V ) \
	msWriteByteMask( 0x1C65, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
reg cafsram_rdata_sel, 1 : [71:36] 0: [35:0]*/
#define /*REG_1C65[2:2];h0032[10:10]=*/ GET_OSD_CTRL_REG_CAF_RD_FLAG() \
	( 0 != ( msReadByte( 0x1C65 ) & 0x04 ) )
/*
*/
#define /*REG_1C65[1:1];h0032[9:9]=*/  GET_OSD_CTRL_REG_CAF_WR_FLAG() \
	( 0 != ( msReadByte( 0x1C65 ) & 0x02 ) )
/*
flag = 1 while write processing. Flag = 0 when write finish*/
#define /*REG_1C66[13:0];h0033[13:0]=h0*/ GET_OSD_CTRL_REG_WR_PORT() \
	( msReadByte( 0x1C66 ) | ( (msReadByte( 0x1C67 ) & 0x3F) <<  8 ) )
#define /*REG_1C66[13:0];h0033[13:0]=h0*/ SET_OSD_CTRL_REG_WR_PORT( V ) \
	{ msWriteByte( 0x1C66, (V) ); msWriteByteMask( 0x1C67, ((V) >>  8), 0x3F ); }
/*
when trig mode :
5'd0 : initial write addr or read addr
       [13:2] for sram entry , [1:0] for code/attr initial high low
5'd1 : [9:8] [7:0] code write data
5'd2 : [7:0] attribute write data
5'd3 : [7:0] font write data
5'd4 : [0] erase trig
5'd5 : [0] read trig
5'd10 : [7:0] psram0 write addr
5'd11 : [0] psram0 mask write data
5'd12 : [0] psram0 color key write data
5'd13 : [7:0] psram0 color write data
5'd14 : [0] psram0 erase trig
5'd15 : [0] psram0 read trig
5'd20 : [7:0] psram1 write addr
5'd21 : [0] psram1 color key write data
5'd22 : [7:0] psram1 color write data
5'd23 : [0] psram1 erase trig
5'd24 : [0] psram1 read trig*/
#define /*REG_1C68[4:0];h0034[4:0]=h0*/ GET_OSD_CTRL_REG_TRIG_MODE() \
	( msReadByte( 0x1C68 ) & 0x1F )
#define /*REG_1C68[4:0];h0034[4:0]=h0*/ SET_OSD_CTRL_REG_TRIG_MODE( V ) \
	msWriteByteMask( 0x1C68, (V), 0x1F );
/*
trig mode :
5'd0 : write cafsram addr
5'd1 : write code
5'd2 : wriet attribute
5'd3 : write font
5'd4 : cafsram erase trig
5'd5 : cafsram read trig
5'd10 : write psram0 addr
5'd11 : write psram0 mask
5'd12 : write psram0 color key
5'd13 : write psram0 color
5'd14 : psram0 erase trig
5'd15 : psram0 read trig
5'd20 :  psram1 addr
5'd21 : write psram1 color key
5'd22 : write psram1 color
5'd23 : psram1 erase trig
5'd24 : psram1 read trig*/
#define /*REG_1C6D[7:7];h0036[15:15]=h0*/ GET_OSD_CTRL_REG_FONT_WR_MODE() \
	( 0 != ( msReadByte( 0x1C6D ) & 0x80 ) )
#define /*REG_1C6D[7:7];h0036[15:15]=h0*/ SET_OSD_CTRL_REG_FONT_WR_MODE() \
	msWriteByteMask( 0x1C6D, 0xFF, 0x80 );
#define /*REG_1C6D[7:7];h0036[15:15]=h0*/ CLR_OSD_CTRL_REG_FONT_WR_MODE() \
	msWriteByteMask( 0x1C6D, 0x0, 0x80 );
#define /*REG_1C6D[7:7];h0036[15:15]=h0*/ ASG_OSD_CTRL_REG_FONT_WR_MODE( V ) \
	msWriteByteMask( 0x1C6D, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
font write data mode : 0 : for 1/2/3 bpp
                                 1: for 4bpp*/
#define /*REG_1C70[25:0];h0038[25:0]=*/ GET_OSD_CTRL_REG_PSRAM0_RD() \
	( msReadByte( 0x1C70 ) | ( msReadByte( 0x1C71 ) <<  8 ) | ( msReadByte( 0x1C72 ) <<  16 ) | ( (msReadByte( 0x1C73 ) & 0x03) <<  24 ) )
/*
palette0 read data*/
#define /*REG_1C75[2:2];h003a[10:10]=*/ GET_OSD_CTRL_REG_P0_RD_FLAG() \
	( 0 != ( msReadByte( 0x1C75 ) & 0x04 ) )
/*
*/
#define /*REG_1C75[1:1];h003a[9:9]=*/  GET_OSD_CTRL_REG_P0_ERS_FLAG() \
	( 0 != ( msReadByte( 0x1C75 ) & 0x02 ) )
/*
erase all data with 0*/
#define /*REG_1C80[24:0];h0040[24:0]=*/ GET_OSD_CTRL_REG_PSRAM1_RD() \
	( msReadByte( 0x1C80 ) | ( msReadByte( 0x1C81 ) <<  8 ) | ( msReadByte( 0x1C82 ) <<  16 ) | ( (msReadByte( 0x1C83 ) & 0x01) <<  24 ) )
/*
palette1 read data*/
#define /*REG_1C85[2:2];h0042[10:10]=*/ GET_OSD_CTRL_REG_P1_RD_FLAG() \
	( 0 != ( msReadByte( 0x1C85 ) & 0x04 ) )
/*
*/
#define /*REG_1C85[1:1];h0042[9:9]=*/  GET_OSD_CTRL_REG_P1_ERS_FLAG() \
	( 0 != ( msReadByte( 0x1C85 ) & 0x02 ) )
/*
erase all data with 0*/
#define /*REG_1CA0[15:0];h0050[15:0]=hff00*/ GET_OSD_CTRL_REG_DUMMY_50() \
	( msReadByte( 0x1CA0 ) | ( msReadByte( 0x1CA1 ) <<  8 ) )
#define /*REG_1CA0[15:0];h0050[15:0]=hff00*/ SET_OSD_CTRL_REG_DUMMY_50( V ) \
	{ msWriteByte( 0x1CA0, (V) ); msWriteByte( 0x1CA1, ((V) >>  8) ); }
/*
dummy register*/
#define /*REG_1CA2[15:0];h0051[15:0]=hff00*/ GET_OSD_CTRL_REG_DUMMY_51() \
	( msReadByte( 0x1CA2 ) | ( msReadByte( 0x1CA3 ) <<  8 ) )
#define /*REG_1CA2[15:0];h0051[15:0]=hff00*/ SET_OSD_CTRL_REG_DUMMY_51( V ) \
	{ msWriteByte( 0x1CA2, (V) ); msWriteByte( 0x1CA3, ((V) >>  8) ); }
/*
dummy register*/


#define _CTRL_OSD_GD_REGISTERS() msWriteByte( 0x1C00, 0x1 );
#define /*REG_1C02[0:0];h0001[0:0]=h0*/ GET_OSD_GD_REG_FWRESET() \
	( 0 != ( msReadByte( 0x1C02 ) & 0x01 ) )
#define /*REG_1C02[0:0];h0001[0:0]=h0*/ SET_OSD_GD_REG_FWRESET() \
	msWriteByteMask( 0x1C02, 0xFF, 0x01 );
#define /*REG_1C02[0:0];h0001[0:0]=h0*/ CLR_OSD_GD_REG_FWRESET() \
	msWriteByteMask( 0x1C02, 0x0, 0x01 );
#define /*REG_1C02[0:0];h0001[0:0]=h0*/ ASG_OSD_GD_REG_FWRESET( V ) \
	msWriteByteMask( 0x1C02, ( 0 != (V) )? 0x01: 0, 0x01 );
/*
GD SW reset*/
#define /*REG_1C04[11:0];h0002[11:0]=h0*/ GET_OSD_GD_REG_GD_TG0_HST() \
	( msReadByte( 0x1C04 ) | ( (msReadByte( 0x1C05 ) & 0x0F) <<  8 ) )
#define /*REG_1C04[11:0];h0002[11:0]=h0*/ SET_OSD_GD_REG_GD_TG0_HST( V ) \
	{ msWriteByte( 0x1C04, (V) ); msWriteByteMask( 0x1C05, ((V) >>  8), 0x0F ); }
/*
Horizontal start pixel of GD Timing Generator 0*/
#define /*REG_1C06[11:0];h0003[11:0]=h0*/ GET_OSD_GD_REG_GD_TG0_HEND() \
	( msReadByte( 0x1C06 ) | ( (msReadByte( 0x1C07 ) & 0x0F) <<  8 ) )
#define /*REG_1C06[11:0];h0003[11:0]=h0*/ SET_OSD_GD_REG_GD_TG0_HEND( V ) \
	{ msWriteByte( 0x1C06, (V) ); msWriteByteMask( 0x1C07, ((V) >>  8), 0x0F ); }
/*
Horizontal end pixel of GD Timing Generator 0*/
#define /*REG_1C08[11:0];h0004[11:0]=h0*/ GET_OSD_GD_REG_GD_TG0_VST() \
	( msReadByte( 0x1C08 ) | ( (msReadByte( 0x1C09 ) & 0x0F) <<  8 ) )
#define /*REG_1C08[11:0];h0004[11:0]=h0*/ SET_OSD_GD_REG_GD_TG0_VST( V ) \
	{ msWriteByte( 0x1C08, (V) ); msWriteByteMask( 0x1C09, ((V) >>  8), 0x0F ); }
/*
Vertical start pixel of GD Timing Generator 0*/
#define /*REG_1C0A[11:0];h0005[11:0]=h0*/ GET_OSD_GD_REG_GD_TG0_VEND() \
	( msReadByte( 0x1C0A ) | ( (msReadByte( 0x1C0B ) & 0x0F) <<  8 ) )
#define /*REG_1C0A[11:0];h0005[11:0]=h0*/ SET_OSD_GD_REG_GD_TG0_VEND( V ) \
	{ msWriteByte( 0x1C0A, (V) ); msWriteByteMask( 0x1C0B, ((V) >>  8), 0x0F ); }
/*
Veritcal end pixel of GD Timing Generator 0*/
#define /*REG_1C0C[11:0];h0006[11:0]=h0*/ GET_OSD_GD_REG_GD_TG1_HST() \
	( msReadByte( 0x1C0C ) | ( (msReadByte( 0x1C0D ) & 0x0F) <<  8 ) )
#define /*REG_1C0C[11:0];h0006[11:0]=h0*/ SET_OSD_GD_REG_GD_TG1_HST( V ) \
	{ msWriteByte( 0x1C0C, (V) ); msWriteByteMask( 0x1C0D, ((V) >>  8), 0x0F ); }
/*
Horizontal start pixel of GD Timing Generator 1*/
#define /*REG_1C0E[11:0];h0007[11:0]=h0*/ GET_OSD_GD_REG_GD_TG1_HEND() \
	( msReadByte( 0x1C0E ) | ( (msReadByte( 0x1C0F ) & 0x0F) <<  8 ) )
#define /*REG_1C0E[11:0];h0007[11:0]=h0*/ SET_OSD_GD_REG_GD_TG1_HEND( V ) \
	{ msWriteByte( 0x1C0E, (V) ); msWriteByteMask( 0x1C0F, ((V) >>  8), 0x0F ); }
/*
Horizontal end pixel of GD Timing Generator 1*/
#define /*REG_1C10[11:0];h0008[11:0]=h0*/ GET_OSD_GD_REG_GD_TG1_VST() \
	( msReadByte( 0x1C10 ) | ( (msReadByte( 0x1C11 ) & 0x0F) <<  8 ) )
#define /*REG_1C10[11:0];h0008[11:0]=h0*/ SET_OSD_GD_REG_GD_TG1_VST( V ) \
	{ msWriteByte( 0x1C10, (V) ); msWriteByteMask( 0x1C11, ((V) >>  8), 0x0F ); }
/*
Vertical start pixel of GD Timing Generator 1*/
#define /*REG_1C12[11:0];h0009[11:0]=h0*/ GET_OSD_GD_REG_GD_TG1_VEND() \
	( msReadByte( 0x1C12 ) | ( (msReadByte( 0x1C13 ) & 0x0F) <<  8 ) )
#define /*REG_1C12[11:0];h0009[11:0]=h0*/ SET_OSD_GD_REG_GD_TG1_VEND( V ) \
	{ msWriteByte( 0x1C12, (V) ); msWriteByteMask( 0x1C13, ((V) >>  8), 0x0F ); }
/*
Veritcal end pixel of GD Timing Generator 1*/
#define /*REG_1C14[11:0];h000a[11:0]=h0*/ GET_OSD_GD_REG_GD_TG2_HST() \
	( msReadByte( 0x1C14 ) | ( (msReadByte( 0x1C15 ) & 0x0F) <<  8 ) )
#define /*REG_1C14[11:0];h000a[11:0]=h0*/ SET_OSD_GD_REG_GD_TG2_HST( V ) \
	{ msWriteByte( 0x1C14, (V) ); msWriteByteMask( 0x1C15, ((V) >>  8), 0x0F ); }
/*
Horizontal start pixel of GD Timing Generator 2*/
#define /*REG_1C16[11:0];h000b[11:0]=h0*/ GET_OSD_GD_REG_GD_TG2_HEND() \
	( msReadByte( 0x1C16 ) | ( (msReadByte( 0x1C17 ) & 0x0F) <<  8 ) )
#define /*REG_1C16[11:0];h000b[11:0]=h0*/ SET_OSD_GD_REG_GD_TG2_HEND( V ) \
	{ msWriteByte( 0x1C16, (V) ); msWriteByteMask( 0x1C17, ((V) >>  8), 0x0F ); }
/*
Horizontal end pixel of GD Timing Generator 2*/
#define /*REG_1C18[11:0];h000c[11:0]=h0*/ GET_OSD_GD_REG_GD_TG2_VST() \
	( msReadByte( 0x1C18 ) | ( (msReadByte( 0x1C19 ) & 0x0F) <<  8 ) )
#define /*REG_1C18[11:0];h000c[11:0]=h0*/ SET_OSD_GD_REG_GD_TG2_VST( V ) \
	{ msWriteByte( 0x1C18, (V) ); msWriteByteMask( 0x1C19, ((V) >>  8), 0x0F ); }
/*
Vertical start pixel of GD Timing Generator 2*/
#define /*REG_1C1A[11:0];h000d[11:0]=h0*/ GET_OSD_GD_REG_GD_TG2_VEND() \
	( msReadByte( 0x1C1A ) | ( (msReadByte( 0x1C1B ) & 0x0F) <<  8 ) )
#define /*REG_1C1A[11:0];h000d[11:0]=h0*/ SET_OSD_GD_REG_GD_TG2_VEND( V ) \
	{ msWriteByte( 0x1C1A, (V) ); msWriteByteMask( 0x1C1B, ((V) >>  8), 0x0F ); }
/*
Veritcal end pixel of GD Timing Generator 2*/
#define /*REG_1C1C[11:0];h000e[11:0]=h0*/ GET_OSD_GD_REG_GD_TG3_HST() \
	( msReadByte( 0x1C1C ) | ( (msReadByte( 0x1C1D ) & 0x0F) <<  8 ) )
#define /*REG_1C1C[11:0];h000e[11:0]=h0*/ SET_OSD_GD_REG_GD_TG3_HST( V ) \
	{ msWriteByte( 0x1C1C, (V) ); msWriteByteMask( 0x1C1D, ((V) >>  8), 0x0F ); }
/*
Horizontal start pixel of GD Timing Generator 3*/
#define /*REG_1C1E[11:0];h000f[11:0]=h0*/ GET_OSD_GD_REG_GD_TG3_HEND() \
	( msReadByte( 0x1C1E ) | ( (msReadByte( 0x1C1F ) & 0x0F) <<  8 ) )
#define /*REG_1C1E[11:0];h000f[11:0]=h0*/ SET_OSD_GD_REG_GD_TG3_HEND( V ) \
	{ msWriteByte( 0x1C1E, (V) ); msWriteByteMask( 0x1C1F, ((V) >>  8), 0x0F ); }
/*
Horizontal end pixel of GD Timing Generator 3*/
#define /*REG_1C20[11:0];h0010[11:0]=h0*/ GET_OSD_GD_REG_GD_TG3_VST() \
	( msReadByte( 0x1C20 ) | ( (msReadByte( 0x1C21 ) & 0x0F) <<  8 ) )
#define /*REG_1C20[11:0];h0010[11:0]=h0*/ SET_OSD_GD_REG_GD_TG3_VST( V ) \
	{ msWriteByte( 0x1C20, (V) ); msWriteByteMask( 0x1C21, ((V) >>  8), 0x0F ); }
/*
Vertical start pixel of GD Timing Generator 3*/
#define /*REG_1C22[11:0];h0011[11:0]=h0*/ GET_OSD_GD_REG_GD_TG3_VEND() \
	( msReadByte( 0x1C22 ) | ( (msReadByte( 0x1C23 ) & 0x0F) <<  8 ) )
#define /*REG_1C22[11:0];h0011[11:0]=h0*/ SET_OSD_GD_REG_GD_TG3_VEND( V ) \
	{ msWriteByte( 0x1C22, (V) ); msWriteByteMask( 0x1C23, ((V) >>  8), 0x0F ); }
/*
Veritcal end pixel of GD Timing Generator 3*/
#define /*REG_1C24[3:0];h0012[3:0]=hf*/ GET_OSD_GD_REG_GD0_WIN0_CUR_SEL() \
	( msReadByte( 0x1C24 ) & 0x0F )
#define /*REG_1C24[3:0];h0012[3:0]=hf*/ SET_OSD_GD_REG_GD0_WIN0_CUR_SEL( V ) \
	msWriteByteMask( 0x1C24, (V), 0x0F );
/*
Curve Select for OSD Window 0 of Gradient Color Engine 0.*/
#define /*REG_1C24[7:4];h0012[7:4]=hf*/ GET_OSD_GD_REG_GD0_WIN1_CUR_SEL() \
	( ( msReadByte( 0x1C24 ) & 0xF0 ) >>  4 )
#define /*REG_1C24[7:4];h0012[7:4]=hf*/ SET_OSD_GD_REG_GD0_WIN1_CUR_SEL( V ) \
	msWriteByteMask( 0x1C24, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 1 of Gradient Color Engine 0.*/
#define /*REG_1C25[3:0];h0012[11:8]=hf*/ GET_OSD_GD_REG_GD0_WIN2_CUR_SEL() \
	( msReadByte( 0x1C25 ) & 0x0F )
#define /*REG_1C25[3:0];h0012[11:8]=hf*/ SET_OSD_GD_REG_GD0_WIN2_CUR_SEL( V ) \
	msWriteByteMask( 0x1C25, (V), 0x0F );
/*
Curve Select for OSD Window 2 of Gradient Color Engine 0.*/
#define /*REG_1C25[7:4];h0012[15:12]=hf*/ GET_OSD_GD_REG_GD0_WIN3_CUR_SEL() \
	( ( msReadByte( 0x1C25 ) & 0xF0 ) >>  4 )
#define /*REG_1C25[7:4];h0012[15:12]=hf*/ SET_OSD_GD_REG_GD0_WIN3_CUR_SEL( V ) \
	msWriteByteMask( 0x1C25, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 3 of Gradient Color Engine 0.*/
#define /*REG_1C26[3:0];h0013[3:0]=hf*/ GET_OSD_GD_REG_GD0_WIN4_CUR_SEL() \
	( msReadByte( 0x1C26 ) & 0x0F )
#define /*REG_1C26[3:0];h0013[3:0]=hf*/ SET_OSD_GD_REG_GD0_WIN4_CUR_SEL( V ) \
	msWriteByteMask( 0x1C26, (V), 0x0F );
/*
Curve Select for OSD Window 4 of Gradient Color Engine 0.*/
#define /*REG_1C26[7:4];h0013[7:4]=hf*/ GET_OSD_GD_REG_GD0_WIN5_CUR_SEL() \
	( ( msReadByte( 0x1C26 ) & 0xF0 ) >>  4 )
#define /*REG_1C26[7:4];h0013[7:4]=hf*/ SET_OSD_GD_REG_GD0_WIN5_CUR_SEL( V ) \
	msWriteByteMask( 0x1C26, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 5 of Gradient Color Engine 0.*/
#define /*REG_1C27[3:0];h0013[11:8]=hf*/ GET_OSD_GD_REG_GD0_WIN6_CUR_SEL() \
	( msReadByte( 0x1C27 ) & 0x0F )
#define /*REG_1C27[3:0];h0013[11:8]=hf*/ SET_OSD_GD_REG_GD0_WIN6_CUR_SEL( V ) \
	msWriteByteMask( 0x1C27, (V), 0x0F );
/*
Curve Select for OSD Window 6 of Gradient Color Engine 0.*/
#define /*REG_1C27[7:4];h0013[15:12]=hf*/ GET_OSD_GD_REG_GD0_WIN7_CUR_SEL() \
	( ( msReadByte( 0x1C27 ) & 0xF0 ) >>  4 )
#define /*REG_1C27[7:4];h0013[15:12]=hf*/ SET_OSD_GD_REG_GD0_WIN7_CUR_SEL( V ) \
	msWriteByteMask( 0x1C27, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 7 of Gradient Color Engine 0.*/
#define /*REG_1C28[3:0];h0014[3:0]=hf*/ GET_OSD_GD_REG_GD0_TG0_CUR_SEL() \
	( msReadByte( 0x1C28 ) & 0x0F )
#define /*REG_1C28[3:0];h0014[3:0]=hf*/ SET_OSD_GD_REG_GD0_TG0_CUR_SEL( V ) \
	msWriteByteMask( 0x1C28, (V), 0x0F );
/*
Curve Select for Timing Gen0 of Gradient Color Engine 0.*/
#define /*REG_1C28[7:4];h0014[7:4]=hf*/ GET_OSD_GD_REG_GD0_TG1_CUR_SEL() \
	( ( msReadByte( 0x1C28 ) & 0xF0 ) >>  4 )
#define /*REG_1C28[7:4];h0014[7:4]=hf*/ SET_OSD_GD_REG_GD0_TG1_CUR_SEL( V ) \
	msWriteByteMask( 0x1C28, ((V) <<  4), 0xF0 );
/*
Curve Select for Timing Gen1 of Gradient Color Engine 0.*/
#define /*REG_1C29[3:0];h0014[11:8]=hf*/ GET_OSD_GD_REG_GD0_TG2_CUR_SEL() \
	( msReadByte( 0x1C29 ) & 0x0F )
#define /*REG_1C29[3:0];h0014[11:8]=hf*/ SET_OSD_GD_REG_GD0_TG2_CUR_SEL( V ) \
	msWriteByteMask( 0x1C29, (V), 0x0F );
/*
Curve Select for Timing Gen2 of Gradient Color Engine 0.*/
#define /*REG_1C29[7:4];h0014[15:12]=hf*/ GET_OSD_GD_REG_GD0_TG3_CUR_SEL() \
	( ( msReadByte( 0x1C29 ) & 0xF0 ) >>  4 )
#define /*REG_1C29[7:4];h0014[15:12]=hf*/ SET_OSD_GD_REG_GD0_TG3_CUR_SEL( V ) \
	msWriteByteMask( 0x1C29, ((V) <<  4), 0xF0 );
/*
Curve Select for Timing Gen3 of Gradient Color Engine 0.*/
#define /*REG_1C2A[3:0];h0015[3:0]=hf*/ GET_OSD_GD_REG_GD1_WIN0_CUR_SEL() \
	( msReadByte( 0x1C2A ) & 0x0F )
#define /*REG_1C2A[3:0];h0015[3:0]=hf*/ SET_OSD_GD_REG_GD1_WIN0_CUR_SEL( V ) \
	msWriteByteMask( 0x1C2A, (V), 0x0F );
/*
Curve Select for OSD Window 0 of Gradient Color Engine 1.*/
#define /*REG_1C2A[7:4];h0015[7:4]=hf*/ GET_OSD_GD_REG_GD1_WIN1_CUR_SEL() \
	( ( msReadByte( 0x1C2A ) & 0xF0 ) >>  4 )
#define /*REG_1C2A[7:4];h0015[7:4]=hf*/ SET_OSD_GD_REG_GD1_WIN1_CUR_SEL( V ) \
	msWriteByteMask( 0x1C2A, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 1 of Gradient Color Engine 1.*/
#define /*REG_1C2B[3:0];h0015[11:8]=hf*/ GET_OSD_GD_REG_GD1_WIN2_CUR_SEL() \
	( msReadByte( 0x1C2B ) & 0x0F )
#define /*REG_1C2B[3:0];h0015[11:8]=hf*/ SET_OSD_GD_REG_GD1_WIN2_CUR_SEL( V ) \
	msWriteByteMask( 0x1C2B, (V), 0x0F );
/*
Curve Select for OSD Window 2 of Gradient Color Engine 1.*/
#define /*REG_1C2B[7:4];h0015[15:12]=hf*/ GET_OSD_GD_REG_GD1_WIN3_CUR_SEL() \
	( ( msReadByte( 0x1C2B ) & 0xF0 ) >>  4 )
#define /*REG_1C2B[7:4];h0015[15:12]=hf*/ SET_OSD_GD_REG_GD1_WIN3_CUR_SEL( V ) \
	msWriteByteMask( 0x1C2B, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 3 of Gradient Color Engine 1.*/
#define /*REG_1C2C[3:0];h0016[3:0]=hf*/ GET_OSD_GD_REG_GD1_WIN4_CUR_SEL() \
	( msReadByte( 0x1C2C ) & 0x0F )
#define /*REG_1C2C[3:0];h0016[3:0]=hf*/ SET_OSD_GD_REG_GD1_WIN4_CUR_SEL( V ) \
	msWriteByteMask( 0x1C2C, (V), 0x0F );
/*
Curve Select for OSD Window 4 of Gradient Color Engine 1.*/
#define /*REG_1C2C[7:4];h0016[7:4]=hf*/ GET_OSD_GD_REG_GD1_WIN5_CUR_SEL() \
	( ( msReadByte( 0x1C2C ) & 0xF0 ) >>  4 )
#define /*REG_1C2C[7:4];h0016[7:4]=hf*/ SET_OSD_GD_REG_GD1_WIN5_CUR_SEL( V ) \
	msWriteByteMask( 0x1C2C, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 5 of Gradient Color Engine 1.*/
#define /*REG_1C2D[3:0];h0016[11:8]=hf*/ GET_OSD_GD_REG_GD1_WIN6_CUR_SEL() \
	( msReadByte( 0x1C2D ) & 0x0F )
#define /*REG_1C2D[3:0];h0016[11:8]=hf*/ SET_OSD_GD_REG_GD1_WIN6_CUR_SEL( V ) \
	msWriteByteMask( 0x1C2D, (V), 0x0F );
/*
Curve Select for OSD Window 6 of Gradient Color Engine 1.*/
#define /*REG_1C2D[7:4];h0016[15:12]=hf*/ GET_OSD_GD_REG_GD1_WIN7_CUR_SEL() \
	( ( msReadByte( 0x1C2D ) & 0xF0 ) >>  4 )
#define /*REG_1C2D[7:4];h0016[15:12]=hf*/ SET_OSD_GD_REG_GD1_WIN7_CUR_SEL( V ) \
	msWriteByteMask( 0x1C2D, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 7 of Gradient Color Engine 1.*/
#define /*REG_1C2E[3:0];h0017[3:0]=hf*/ GET_OSD_GD_REG_GD1_TG0_CUR_SEL() \
	( msReadByte( 0x1C2E ) & 0x0F )
#define /*REG_1C2E[3:0];h0017[3:0]=hf*/ SET_OSD_GD_REG_GD1_TG0_CUR_SEL( V ) \
	msWriteByteMask( 0x1C2E, (V), 0x0F );
/*
Curve Select for Timing Gen0 of Gradient Color Engine 1.*/
#define /*REG_1C2E[7:4];h0017[7:4]=hf*/ GET_OSD_GD_REG_GD1_TG1_CUR_SEL() \
	( ( msReadByte( 0x1C2E ) & 0xF0 ) >>  4 )
#define /*REG_1C2E[7:4];h0017[7:4]=hf*/ SET_OSD_GD_REG_GD1_TG1_CUR_SEL( V ) \
	msWriteByteMask( 0x1C2E, ((V) <<  4), 0xF0 );
/*
Curve Select for Timing Gen1 of Gradient Color Engine 1.*/
#define /*REG_1C2F[3:0];h0017[11:8]=hf*/ GET_OSD_GD_REG_GD1_TG2_CUR_SEL() \
	( msReadByte( 0x1C2F ) & 0x0F )
#define /*REG_1C2F[3:0];h0017[11:8]=hf*/ SET_OSD_GD_REG_GD1_TG2_CUR_SEL( V ) \
	msWriteByteMask( 0x1C2F, (V), 0x0F );
/*
Curve Select for Timing Gen2 of Gradient Color Engine 1.*/
#define /*REG_1C2F[7:4];h0017[15:12]=hf*/ GET_OSD_GD_REG_GD1_TG3_CUR_SEL() \
	( ( msReadByte( 0x1C2F ) & 0xF0 ) >>  4 )
#define /*REG_1C2F[7:4];h0017[15:12]=hf*/ SET_OSD_GD_REG_GD1_TG3_CUR_SEL( V ) \
	msWriteByteMask( 0x1C2F, ((V) <<  4), 0xF0 );
/*
Curve Select for Timing Gen3 of Gradient Color Engine 1.*/
#define /*REG_1C30[3:0];h0018[3:0]=hf*/ GET_OSD_GD_REG_GD2_WIN0_CUR_SEL() \
	( msReadByte( 0x1C30 ) & 0x0F )
#define /*REG_1C30[3:0];h0018[3:0]=hf*/ SET_OSD_GD_REG_GD2_WIN0_CUR_SEL( V ) \
	msWriteByteMask( 0x1C30, (V), 0x0F );
/*
Curve Select for OSD Window 0 of Gradient Color Engine 2.*/
#define /*REG_1C30[7:4];h0018[7:4]=hf*/ GET_OSD_GD_REG_GD2_WIN1_CUR_SEL() \
	( ( msReadByte( 0x1C30 ) & 0xF0 ) >>  4 )
#define /*REG_1C30[7:4];h0018[7:4]=hf*/ SET_OSD_GD_REG_GD2_WIN1_CUR_SEL( V ) \
	msWriteByteMask( 0x1C30, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 1 of Gradient Color Engine 2.*/
#define /*REG_1C31[3:0];h0018[11:8]=hf*/ GET_OSD_GD_REG_GD2_WIN2_CUR_SEL() \
	( msReadByte( 0x1C31 ) & 0x0F )
#define /*REG_1C31[3:0];h0018[11:8]=hf*/ SET_OSD_GD_REG_GD2_WIN2_CUR_SEL( V ) \
	msWriteByteMask( 0x1C31, (V), 0x0F );
/*
Curve Select for OSD Window 2 of Gradient Color Engine 2.*/
#define /*REG_1C31[7:4];h0018[15:12]=hf*/ GET_OSD_GD_REG_GD2_WIN3_CUR_SEL() \
	( ( msReadByte( 0x1C31 ) & 0xF0 ) >>  4 )
#define /*REG_1C31[7:4];h0018[15:12]=hf*/ SET_OSD_GD_REG_GD2_WIN3_CUR_SEL( V ) \
	msWriteByteMask( 0x1C31, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 3 of Gradient Color Engine 2.*/
#define /*REG_1C32[3:0];h0019[3:0]=hf*/ GET_OSD_GD_REG_GD2_WIN4_CUR_SEL() \
	( msReadByte( 0x1C32 ) & 0x0F )
#define /*REG_1C32[3:0];h0019[3:0]=hf*/ SET_OSD_GD_REG_GD2_WIN4_CUR_SEL( V ) \
	msWriteByteMask( 0x1C32, (V), 0x0F );
/*
Curve Select for OSD Window 4 of Gradient Color Engine 2.*/
#define /*REG_1C32[7:4];h0019[7:4]=hf*/ GET_OSD_GD_REG_GD2_WIN5_CUR_SEL() \
	( ( msReadByte( 0x1C32 ) & 0xF0 ) >>  4 )
#define /*REG_1C32[7:4];h0019[7:4]=hf*/ SET_OSD_GD_REG_GD2_WIN5_CUR_SEL( V ) \
	msWriteByteMask( 0x1C32, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 5 of Gradient Color Engine 2.*/
#define /*REG_1C33[3:0];h0019[11:8]=hf*/ GET_OSD_GD_REG_GD2_WIN6_CUR_SEL() \
	( msReadByte( 0x1C33 ) & 0x0F )
#define /*REG_1C33[3:0];h0019[11:8]=hf*/ SET_OSD_GD_REG_GD2_WIN6_CUR_SEL( V ) \
	msWriteByteMask( 0x1C33, (V), 0x0F );
/*
Curve Select for OSD Window 6 of Gradient Color Engine 2.*/
#define /*REG_1C33[7:4];h0019[15:12]=hf*/ GET_OSD_GD_REG_GD2_WIN7_CUR_SEL() \
	( ( msReadByte( 0x1C33 ) & 0xF0 ) >>  4 )
#define /*REG_1C33[7:4];h0019[15:12]=hf*/ SET_OSD_GD_REG_GD2_WIN7_CUR_SEL( V ) \
	msWriteByteMask( 0x1C33, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 7 of Gradient Color Engine 2.*/
#define /*REG_1C34[3:0];h001a[3:0]=hf*/ GET_OSD_GD_REG_GD2_TG0_CUR_SEL() \
	( msReadByte( 0x1C34 ) & 0x0F )
#define /*REG_1C34[3:0];h001a[3:0]=hf*/ SET_OSD_GD_REG_GD2_TG0_CUR_SEL( V ) \
	msWriteByteMask( 0x1C34, (V), 0x0F );
/*
Curve Select for Timing Gen0 of Gradient Color Engine 2.*/
#define /*REG_1C34[7:4];h001a[7:4]=hf*/ GET_OSD_GD_REG_GD2_TG1_CUR_SEL() \
	( ( msReadByte( 0x1C34 ) & 0xF0 ) >>  4 )
#define /*REG_1C34[7:4];h001a[7:4]=hf*/ SET_OSD_GD_REG_GD2_TG1_CUR_SEL( V ) \
	msWriteByteMask( 0x1C34, ((V) <<  4), 0xF0 );
/*
Curve Select for Timing Gen1 of Gradient Color Engine 2.*/
#define /*REG_1C35[3:0];h001a[11:8]=hf*/ GET_OSD_GD_REG_GD2_TG2_CUR_SEL() \
	( msReadByte( 0x1C35 ) & 0x0F )
#define /*REG_1C35[3:0];h001a[11:8]=hf*/ SET_OSD_GD_REG_GD2_TG2_CUR_SEL( V ) \
	msWriteByteMask( 0x1C35, (V), 0x0F );
/*
Curve Select for Timing Gen2 of Gradient Color Engine 2.*/
#define /*REG_1C35[7:4];h001a[15:12]=hf*/ GET_OSD_GD_REG_GD2_TG3_CUR_SEL() \
	( ( msReadByte( 0x1C35 ) & 0xF0 ) >>  4 )
#define /*REG_1C35[7:4];h001a[15:12]=hf*/ SET_OSD_GD_REG_GD2_TG3_CUR_SEL( V ) \
	msWriteByteMask( 0x1C35, ((V) <<  4), 0xF0 );
/*
Curve Select for Timing Gen3 of Gradient Color Engine 2.*/
#define /*REG_1C36[3:0];h001b[3:0]=hf*/ GET_OSD_GD_REG_GD3_WIN0_CUR_SEL() \
	( msReadByte( 0x1C36 ) & 0x0F )
#define /*REG_1C36[3:0];h001b[3:0]=hf*/ SET_OSD_GD_REG_GD3_WIN0_CUR_SEL( V ) \
	msWriteByteMask( 0x1C36, (V), 0x0F );
/*
Curve Select for OSD Window 0 of Gradient Color Engine 3.*/
#define /*REG_1C36[7:4];h001b[7:4]=hf*/ GET_OSD_GD_REG_GD3_WIN1_CUR_SEL() \
	( ( msReadByte( 0x1C36 ) & 0xF0 ) >>  4 )
#define /*REG_1C36[7:4];h001b[7:4]=hf*/ SET_OSD_GD_REG_GD3_WIN1_CUR_SEL( V ) \
	msWriteByteMask( 0x1C36, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 1 of Gradient Color Engine 3.*/
#define /*REG_1C37[3:0];h001b[11:8]=hf*/ GET_OSD_GD_REG_GD3_WIN2_CUR_SEL() \
	( msReadByte( 0x1C37 ) & 0x0F )
#define /*REG_1C37[3:0];h001b[11:8]=hf*/ SET_OSD_GD_REG_GD3_WIN2_CUR_SEL( V ) \
	msWriteByteMask( 0x1C37, (V), 0x0F );
/*
Curve Select for OSD Window 2 of Gradient Color Engine 3.*/
#define /*REG_1C37[7:4];h001b[15:12]=hf*/ GET_OSD_GD_REG_GD3_WIN3_CUR_SEL() \
	( ( msReadByte( 0x1C37 ) & 0xF0 ) >>  4 )
#define /*REG_1C37[7:4];h001b[15:12]=hf*/ SET_OSD_GD_REG_GD3_WIN3_CUR_SEL( V ) \
	msWriteByteMask( 0x1C37, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 3 of Gradient Color Engine 3.*/
#define /*REG_1C38[3:0];h001c[3:0]=hf*/ GET_OSD_GD_REG_GD3_WIN4_CUR_SEL() \
	( msReadByte( 0x1C38 ) & 0x0F )
#define /*REG_1C38[3:0];h001c[3:0]=hf*/ SET_OSD_GD_REG_GD3_WIN4_CUR_SEL( V ) \
	msWriteByteMask( 0x1C38, (V), 0x0F );
/*
Curve Select for OSD Window 4 of Gradient Color Engine 3.*/
#define /*REG_1C38[7:4];h001c[7:4]=hf*/ GET_OSD_GD_REG_GD3_WIN5_CUR_SEL() \
	( ( msReadByte( 0x1C38 ) & 0xF0 ) >>  4 )
#define /*REG_1C38[7:4];h001c[7:4]=hf*/ SET_OSD_GD_REG_GD3_WIN5_CUR_SEL( V ) \
	msWriteByteMask( 0x1C38, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 5 of Gradient Color Engine 3.*/
#define /*REG_1C39[3:0];h001c[11:8]=hf*/ GET_OSD_GD_REG_GD3_WIN6_CUR_SEL() \
	( msReadByte( 0x1C39 ) & 0x0F )
#define /*REG_1C39[3:0];h001c[11:8]=hf*/ SET_OSD_GD_REG_GD3_WIN6_CUR_SEL( V ) \
	msWriteByteMask( 0x1C39, (V), 0x0F );
/*
Curve Select for OSD Window 6 of Gradient Color Engine 3.*/
#define /*REG_1C39[7:4];h001c[15:12]=hf*/ GET_OSD_GD_REG_GD3_WIN7_CUR_SEL() \
	( ( msReadByte( 0x1C39 ) & 0xF0 ) >>  4 )
#define /*REG_1C39[7:4];h001c[15:12]=hf*/ SET_OSD_GD_REG_GD3_WIN7_CUR_SEL( V ) \
	msWriteByteMask( 0x1C39, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 7 of Gradient Color Engine 3.*/
#define /*REG_1C3A[3:0];h001d[3:0]=hf*/ GET_OSD_GD_REG_GD3_TG0_CUR_SEL() \
	( msReadByte( 0x1C3A ) & 0x0F )
#define /*REG_1C3A[3:0];h001d[3:0]=hf*/ SET_OSD_GD_REG_GD3_TG0_CUR_SEL( V ) \
	msWriteByteMask( 0x1C3A, (V), 0x0F );
/*
Curve Select for Timing Gen0 of Gradient Color Engine 3.*/
#define /*REG_1C3A[7:4];h001d[7:4]=hf*/ GET_OSD_GD_REG_GD3_TG1_CUR_SEL() \
	( ( msReadByte( 0x1C3A ) & 0xF0 ) >>  4 )
#define /*REG_1C3A[7:4];h001d[7:4]=hf*/ SET_OSD_GD_REG_GD3_TG1_CUR_SEL( V ) \
	msWriteByteMask( 0x1C3A, ((V) <<  4), 0xF0 );
/*
Curve Select for Timing Gen1 of Gradient Color Engine 3.*/
#define /*REG_1C3B[3:0];h001d[11:8]=hf*/ GET_OSD_GD_REG_GD3_TG2_CUR_SEL() \
	( msReadByte( 0x1C3B ) & 0x0F )
#define /*REG_1C3B[3:0];h001d[11:8]=hf*/ SET_OSD_GD_REG_GD3_TG2_CUR_SEL( V ) \
	msWriteByteMask( 0x1C3B, (V), 0x0F );
/*
Curve Select for Timing Gen2 of Gradient Color Engine 3.*/
#define /*REG_1C3B[7:4];h001d[15:12]=hf*/ GET_OSD_GD_REG_GD3_TG3_CUR_SEL() \
	( ( msReadByte( 0x1C3B ) & 0xF0 ) >>  4 )
#define /*REG_1C3B[7:4];h001d[15:12]=hf*/ SET_OSD_GD_REG_GD3_TG3_CUR_SEL( V ) \
	msWriteByteMask( 0x1C3B, ((V) <<  4), 0xF0 );
/*
Curve Select for Timing Gen3 of Gradient Color Engine 3.*/
#define /*REG_1C3C[3:0];h001e[3:0]=hf*/ GET_OSD_GD_REG_GD4_WIN0_CUR_SEL() \
	( msReadByte( 0x1C3C ) & 0x0F )
#define /*REG_1C3C[3:0];h001e[3:0]=hf*/ SET_OSD_GD_REG_GD4_WIN0_CUR_SEL( V ) \
	msWriteByteMask( 0x1C3C, (V), 0x0F );
/*
Curve Select for OSD Window 0 of Gradient Color Engine 4.*/
#define /*REG_1C3C[7:4];h001e[7:4]=hf*/ GET_OSD_GD_REG_GD4_WIN1_CUR_SEL() \
	( ( msReadByte( 0x1C3C ) & 0xF0 ) >>  4 )
#define /*REG_1C3C[7:4];h001e[7:4]=hf*/ SET_OSD_GD_REG_GD4_WIN1_CUR_SEL( V ) \
	msWriteByteMask( 0x1C3C, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 1 of Gradient Color Engine 4.*/
#define /*REG_1C3D[3:0];h001e[11:8]=hf*/ GET_OSD_GD_REG_GD4_WIN2_CUR_SEL() \
	( msReadByte( 0x1C3D ) & 0x0F )
#define /*REG_1C3D[3:0];h001e[11:8]=hf*/ SET_OSD_GD_REG_GD4_WIN2_CUR_SEL( V ) \
	msWriteByteMask( 0x1C3D, (V), 0x0F );
/*
Curve Select for OSD Window 2 of Gradient Color Engine 4.*/
#define /*REG_1C3D[7:4];h001e[15:12]=hf*/ GET_OSD_GD_REG_GD4_WIN3_CUR_SEL() \
	( ( msReadByte( 0x1C3D ) & 0xF0 ) >>  4 )
#define /*REG_1C3D[7:4];h001e[15:12]=hf*/ SET_OSD_GD_REG_GD4_WIN3_CUR_SEL( V ) \
	msWriteByteMask( 0x1C3D, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 3 of Gradient Color Engine 4.*/
#define /*REG_1C3E[3:0];h001f[3:0]=hf*/ GET_OSD_GD_REG_GD4_WIN4_CUR_SEL() \
	( msReadByte( 0x1C3E ) & 0x0F )
#define /*REG_1C3E[3:0];h001f[3:0]=hf*/ SET_OSD_GD_REG_GD4_WIN4_CUR_SEL( V ) \
	msWriteByteMask( 0x1C3E, (V), 0x0F );
/*
Curve Select for OSD Window 4 of Gradient Color Engine 4.*/
#define /*REG_1C3E[7:4];h001f[7:4]=hf*/ GET_OSD_GD_REG_GD4_WIN5_CUR_SEL() \
	( ( msReadByte( 0x1C3E ) & 0xF0 ) >>  4 )
#define /*REG_1C3E[7:4];h001f[7:4]=hf*/ SET_OSD_GD_REG_GD4_WIN5_CUR_SEL( V ) \
	msWriteByteMask( 0x1C3E, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 5 of Gradient Color Engine 4.*/
#define /*REG_1C3F[3:0];h001f[11:8]=hf*/ GET_OSD_GD_REG_GD4_WIN6_CUR_SEL() \
	( msReadByte( 0x1C3F ) & 0x0F )
#define /*REG_1C3F[3:0];h001f[11:8]=hf*/ SET_OSD_GD_REG_GD4_WIN6_CUR_SEL( V ) \
	msWriteByteMask( 0x1C3F, (V), 0x0F );
/*
Curve Select for OSD Window 6 of Gradient Color Engine 4.*/
#define /*REG_1C3F[7:4];h001f[15:12]=hf*/ GET_OSD_GD_REG_GD4_WIN7_CUR_SEL() \
	( ( msReadByte( 0x1C3F ) & 0xF0 ) >>  4 )
#define /*REG_1C3F[7:4];h001f[15:12]=hf*/ SET_OSD_GD_REG_GD4_WIN7_CUR_SEL( V ) \
	msWriteByteMask( 0x1C3F, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 7 of Gradient Color Engine 4.*/
#define /*REG_1C40[3:0];h0020[3:0]=hf*/ GET_OSD_GD_REG_GD4_TG0_CUR_SEL() \
	( msReadByte( 0x1C40 ) & 0x0F )
#define /*REG_1C40[3:0];h0020[3:0]=hf*/ SET_OSD_GD_REG_GD4_TG0_CUR_SEL( V ) \
	msWriteByteMask( 0x1C40, (V), 0x0F );
/*
Curve Select for Timing Gen0 of Gradient Color Engine 4.*/
#define /*REG_1C40[7:4];h0020[7:4]=hf*/ GET_OSD_GD_REG_GD4_TG1_CUR_SEL() \
	( ( msReadByte( 0x1C40 ) & 0xF0 ) >>  4 )
#define /*REG_1C40[7:4];h0020[7:4]=hf*/ SET_OSD_GD_REG_GD4_TG1_CUR_SEL( V ) \
	msWriteByteMask( 0x1C40, ((V) <<  4), 0xF0 );
/*
Curve Select for Timing Gen1 of Gradient Color Engine 4.*/
#define /*REG_1C41[3:0];h0020[11:8]=hf*/ GET_OSD_GD_REG_GD4_TG2_CUR_SEL() \
	( msReadByte( 0x1C41 ) & 0x0F )
#define /*REG_1C41[3:0];h0020[11:8]=hf*/ SET_OSD_GD_REG_GD4_TG2_CUR_SEL( V ) \
	msWriteByteMask( 0x1C41, (V), 0x0F );
/*
Curve Select for Timing Gen2 of Gradient Color Engine 4.*/
#define /*REG_1C41[7:4];h0020[15:12]=hf*/ GET_OSD_GD_REG_GD4_TG3_CUR_SEL() \
	( ( msReadByte( 0x1C41 ) & 0xF0 ) >>  4 )
#define /*REG_1C41[7:4];h0020[15:12]=hf*/ SET_OSD_GD_REG_GD4_TG3_CUR_SEL( V ) \
	msWriteByteMask( 0x1C41, ((V) <<  4), 0xF0 );
/*
Curve Select for Timing Gen3 of Gradient Color Engine 4.*/
#define /*REG_1C42[3:0];h0021[3:0]=hf*/ GET_OSD_GD_REG_GD5_WIN0_CUR_SEL() \
	( msReadByte( 0x1C42 ) & 0x0F )
#define /*REG_1C42[3:0];h0021[3:0]=hf*/ SET_OSD_GD_REG_GD5_WIN0_CUR_SEL( V ) \
	msWriteByteMask( 0x1C42, (V), 0x0F );
/*
Curve Select for OSD Window 0 of Gradient Color Engine 5.*/
#define /*REG_1C42[7:4];h0021[7:4]=hf*/ GET_OSD_GD_REG_GD5_WIN1_CUR_SEL() \
	( ( msReadByte( 0x1C42 ) & 0xF0 ) >>  4 )
#define /*REG_1C42[7:4];h0021[7:4]=hf*/ SET_OSD_GD_REG_GD5_WIN1_CUR_SEL( V ) \
	msWriteByteMask( 0x1C42, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 1 of Gradient Color Engine 5.*/
#define /*REG_1C43[3:0];h0021[11:8]=hf*/ GET_OSD_GD_REG_GD5_WIN2_CUR_SEL() \
	( msReadByte( 0x1C43 ) & 0x0F )
#define /*REG_1C43[3:0];h0021[11:8]=hf*/ SET_OSD_GD_REG_GD5_WIN2_CUR_SEL( V ) \
	msWriteByteMask( 0x1C43, (V), 0x0F );
/*
Curve Select for OSD Window 2 of Gradient Color Engine 5.*/
#define /*REG_1C43[7:4];h0021[15:12]=hf*/ GET_OSD_GD_REG_GD5_WIN3_CUR_SEL() \
	( ( msReadByte( 0x1C43 ) & 0xF0 ) >>  4 )
#define /*REG_1C43[7:4];h0021[15:12]=hf*/ SET_OSD_GD_REG_GD5_WIN3_CUR_SEL( V ) \
	msWriteByteMask( 0x1C43, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 3 of Gradient Color Engine 5.*/
#define /*REG_1C44[3:0];h0022[3:0]=hf*/ GET_OSD_GD_REG_GD5_WIN4_CUR_SEL() \
	( msReadByte( 0x1C44 ) & 0x0F )
#define /*REG_1C44[3:0];h0022[3:0]=hf*/ SET_OSD_GD_REG_GD5_WIN4_CUR_SEL( V ) \
	msWriteByteMask( 0x1C44, (V), 0x0F );
/*
Curve Select for OSD Window 4 of Gradient Color Engine 5.*/
#define /*REG_1C44[7:4];h0022[7:4]=hf*/ GET_OSD_GD_REG_GD5_WIN5_CUR_SEL() \
	( ( msReadByte( 0x1C44 ) & 0xF0 ) >>  4 )
#define /*REG_1C44[7:4];h0022[7:4]=hf*/ SET_OSD_GD_REG_GD5_WIN5_CUR_SEL( V ) \
	msWriteByteMask( 0x1C44, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 5 of Gradient Color Engine 5.*/
#define /*REG_1C45[3:0];h0022[11:8]=hf*/ GET_OSD_GD_REG_GD5_WIN6_CUR_SEL() \
	( msReadByte( 0x1C45 ) & 0x0F )
#define /*REG_1C45[3:0];h0022[11:8]=hf*/ SET_OSD_GD_REG_GD5_WIN6_CUR_SEL( V ) \
	msWriteByteMask( 0x1C45, (V), 0x0F );
/*
Curve Select for OSD Window 6 of Gradient Color Engine 5.*/
#define /*REG_1C45[7:4];h0022[15:12]=hf*/ GET_OSD_GD_REG_GD5_WIN7_CUR_SEL() \
	( ( msReadByte( 0x1C45 ) & 0xF0 ) >>  4 )
#define /*REG_1C45[7:4];h0022[15:12]=hf*/ SET_OSD_GD_REG_GD5_WIN7_CUR_SEL( V ) \
	msWriteByteMask( 0x1C45, ((V) <<  4), 0xF0 );
/*
Curve Select for OSD Window 7 of Gradient Color Engine 5.*/
#define /*REG_1C46[3:0];h0023[3:0]=hf*/ GET_OSD_GD_REG_GD5_TG0_CUR_SEL() \
	( msReadByte( 0x1C46 ) & 0x0F )
#define /*REG_1C46[3:0];h0023[3:0]=hf*/ SET_OSD_GD_REG_GD5_TG0_CUR_SEL( V ) \
	msWriteByteMask( 0x1C46, (V), 0x0F );
/*
Curve Select for Timing Gen0 of Gradient Color Engine 5.*/
#define /*REG_1C46[7:4];h0023[7:4]=hf*/ GET_OSD_GD_REG_GD5_TG1_CUR_SEL() \
	( ( msReadByte( 0x1C46 ) & 0xF0 ) >>  4 )
#define /*REG_1C46[7:4];h0023[7:4]=hf*/ SET_OSD_GD_REG_GD5_TG1_CUR_SEL( V ) \
	msWriteByteMask( 0x1C46, ((V) <<  4), 0xF0 );
/*
Curve Select for Timing Gen1 of Gradient Color Engine 5.*/
#define /*REG_1C47[3:0];h0023[11:8]=hf*/ GET_OSD_GD_REG_GD5_TG2_CUR_SEL() \
	( msReadByte( 0x1C47 ) & 0x0F )
#define /*REG_1C47[3:0];h0023[11:8]=hf*/ SET_OSD_GD_REG_GD5_TG2_CUR_SEL( V ) \
	msWriteByteMask( 0x1C47, (V), 0x0F );
/*
Curve Select for Timing Gen2 of Gradient Color Engine 5.*/
#define /*REG_1C47[7:4];h0023[15:12]=hf*/ GET_OSD_GD_REG_GD5_TG3_CUR_SEL() \
	( ( msReadByte( 0x1C47 ) & 0xF0 ) >>  4 )
#define /*REG_1C47[7:4];h0023[15:12]=hf*/ SET_OSD_GD_REG_GD5_TG3_CUR_SEL( V ) \
	msWriteByteMask( 0x1C47, ((V) <<  4), 0xF0 );
/*
Curve Select for Timing Gen3 of Gradient Color Engine 5.*/
#define /*REG_1CC0[6:6];h0060[6:6]=*/  GET_OSD_GD_REG_CURVE_BIST_FAIL() \
	( 0 != ( msReadByte( 0x1CC0 ) & 0x40 ) )
/*
Curve SRAM Bist Fail*/
#define /*REG_1CC0[7:7];h0060[7:7]=*/  GET_OSD_GD_REG_CURVE_WRITE_FINISH() \
	( 0 != ( msReadByte( 0x1CC0 ) & 0x80 ) )
/*
Curve SRAM Write finish*/
#define /*REG_1CC4[7:0];h0062[7:0]=*/  GET_OSD_GD_REG_CURVE_RDATA() \
	( msReadByte( 0x1CC4 ) )
/*
Curve SRAM Read Data*/
#define /*REG_1CC5[2:0];h0062[10:8]=h0*/ GET_OSD_GD_REG_CURVE_RDATA_SEL() \
	( msReadByte( 0x1CC5 ) & 0x07 )
#define /*REG_1CC5[2:0];h0062[10:8]=h0*/ SET_OSD_GD_REG_CURVE_RDATA_SEL( V ) \
	msWriteByteMask( 0x1CC5, (V), 0x07 );
/*
Curve SRAM Read Data Select*/
#define /*REG_1CC5[7:7];h0062[15:15]=h0*/ GET_OSD_GD_REG_CURVE_RDATA_EN() \
	( 0 != ( msReadByte( 0x1CC5 ) & 0x80 ) )
#define /*REG_1CC5[7:7];h0062[15:15]=h0*/ SET_OSD_GD_REG_CURVE_RDATA_EN() \
	msWriteByteMask( 0x1CC5, 0xFF, 0x80 );
#define /*REG_1CC5[7:7];h0062[15:15]=h0*/ CLR_OSD_GD_REG_CURVE_RDATA_EN() \
	msWriteByteMask( 0x1CC5, 0x0, 0x80 );
#define /*REG_1CC5[7:7];h0062[15:15]=h0*/ ASG_OSD_GD_REG_CURVE_RDATA_EN( V ) \
	msWriteByteMask( 0x1CC5, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
Curve SRAM Data Enable*/
#define /*REG_1CFA[15:0];h007d[15:0]=h0*/ GET_OSD_GD_REG_DUMMY0() \
	( msReadByte( 0x1CFA ) | ( msReadByte( 0x1CFB ) <<  8 ) )
#define /*REG_1CFA[15:0];h007d[15:0]=h0*/ SET_OSD_GD_REG_DUMMY0( V ) \
	{ msWriteByte( 0x1CFA, (V) ); msWriteByte( 0x1CFB, ((V) >>  8) ); }
/*
Dummy0*/
#define /*REG_1CFC[15:0];h007e[15:0]=h0*/ GET_OSD_GD_REG_DUMMY1() \
	( msReadByte( 0x1CFC ) | ( msReadByte( 0x1CFD ) <<  8 ) )
#define /*REG_1CFC[15:0];h007e[15:0]=h0*/ SET_OSD_GD_REG_DUMMY1( V ) \
	{ msWriteByte( 0x1CFC, (V) ); msWriteByte( 0x1CFD, ((V) >>  8) ); }
/*
Dummy1*/
#define /*REG_1CFE[15:0];h007f[15:0]=*/ GET_OSD_GD_REG_DUMMY0_READ() \
	( msReadByte( 0x1CFE ) | ( msReadByte( 0x1CFF ) <<  8 ) )
/*
Dummy0 Read register*/


#define _CTRL_OSD_WIN_REGISTERS()
#define /*REG_1D00[0:0];h0000[0:0]=h0*/ GET_OSD_WIN_REG_WIN0_EN() \
	( 0 != ( msReadByte( 0x1D00 ) & 0x01 ) )
#define /*REG_1D00[0:0];h0000[0:0]=h0*/ SET_OSD_WIN_REG_WIN0_EN() \
	msWriteByteMask( 0x1D00, 0xFF, 0x01 );
#define /*REG_1D00[0:0];h0000[0:0]=h0*/ CLR_OSD_WIN_REG_WIN0_EN() \
	msWriteByteMask( 0x1D00, 0x0, 0x01 );
#define /*REG_1D00[0:0];h0000[0:0]=h0*/ ASG_OSD_WIN_REG_WIN0_EN( V ) \
	msWriteByteMask( 0x1D00, ( 0 != (V) )? 0x01: 0, 0x01 );
/*
OSD Window display.
0: window off.
1: window on.*/
#define /*REG_1D00[1:1];h0000[1:1]=h0*/ GET_OSD_WIN_REG_WIN0_CA_DUP_MODE() \
	( 0 != ( msReadByte( 0x1D00 ) & 0x02 ) )
#define /*REG_1D00[1:1];h0000[1:1]=h0*/ SET_OSD_WIN_REG_WIN0_CA_DUP_MODE() \
	msWriteByteMask( 0x1D00, 0xFF, 0x02 );
#define /*REG_1D00[1:1];h0000[1:1]=h0*/ CLR_OSD_WIN_REG_WIN0_CA_DUP_MODE() \
	msWriteByteMask( 0x1D00, 0x0, 0x02 );
#define /*REG_1D00[1:1];h0000[1:1]=h0*/ ASG_OSD_WIN_REG_WIN0_CA_DUP_MODE( V ) \
	msWriteByteMask( 0x1D00, ( 0 != (V) )? 0x02: 0, 0x02 );
/*
window duplicate ca base address*/
#define /*REG_1D00[2:2];h0000[2:2]=h0*/ GET_OSD_WIN_REG_WIN0_FP_MODE() \
	( 0 != ( msReadByte( 0x1D00 ) & 0x04 ) )
#define /*REG_1D00[2:2];h0000[2:2]=h0*/ SET_OSD_WIN_REG_WIN0_FP_MODE() \
	msWriteByteMask( 0x1D00, 0xFF, 0x04 );
#define /*REG_1D00[2:2];h0000[2:2]=h0*/ CLR_OSD_WIN_REG_WIN0_FP_MODE() \
	msWriteByteMask( 0x1D00, 0x0, 0x04 );
#define /*REG_1D00[2:2];h0000[2:2]=h0*/ ASG_OSD_WIN_REG_WIN0_FP_MODE( V ) \
	msWriteByteMask( 0x1D00, ( 0 != (V) )? 0x04: 0, 0x04 );
/*
0: window use "font + text + PG" combination
1: window use "font + PG" combination*/
#define /*REG_1D00[3:3];h0000[3:3]=h0*/ GET_OSD_WIN_REG_WIN0_CA_DUP_MODE_TX() \
	( 0 != ( msReadByte( 0x1D00 ) & 0x08 ) )
#define /*REG_1D00[3:3];h0000[3:3]=h0*/ SET_OSD_WIN_REG_WIN0_CA_DUP_MODE_TX() \
	msWriteByteMask( 0x1D00, 0xFF, 0x08 );
#define /*REG_1D00[3:3];h0000[3:3]=h0*/ CLR_OSD_WIN_REG_WIN0_CA_DUP_MODE_TX() \
	msWriteByteMask( 0x1D00, 0x0, 0x08 );
#define /*REG_1D00[3:3];h0000[3:3]=h0*/ ASG_OSD_WIN_REG_WIN0_CA_DUP_MODE_TX( V ) \
	msWriteByteMask( 0x1D00, ( 0 != (V) )? 0x08: 0, 0x08 );
/*
window duplicate ca base address for text*/
#define /*REG_1D00[6:4];h0000[6:4]=h0*/ GET_OSD_WIN_REG_WIN0_OUT_A_SEL() \
	( ( msReadByte( 0x1D00 ) & 0x70 ) >>  4 )
#define /*REG_1D00[6:4];h0000[6:4]=h0*/ SET_OSD_WIN_REG_WIN0_OUT_A_SEL( V ) \
	msWriteByteMask( 0x1D00, ((V) <<  4), 0x70 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_out*/
#define /*REG_1D00[7:7];h0000[7:7]=h0*/ GET_OSD_WIN_REG_WIN0_TX_EN() \
	( 0 != ( msReadByte( 0x1D00 ) & 0x80 ) )
#define /*REG_1D00[7:7];h0000[7:7]=h0*/ SET_OSD_WIN_REG_WIN0_TX_EN() \
	msWriteByteMask( 0x1D00, 0xFF, 0x80 );
#define /*REG_1D00[7:7];h0000[7:7]=h0*/ CLR_OSD_WIN_REG_WIN0_TX_EN() \
	msWriteByteMask( 0x1D00, 0x0, 0x80 );
#define /*REG_1D00[7:7];h0000[7:7]=h0*/ ASG_OSD_WIN_REG_WIN0_TX_EN( V ) \
	msWriteByteMask( 0x1D00, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
OSD Window display.
0: window font only.
1: window turn on font and text.*/
#define /*REG_1D01[2:0];h0000[10:8]=h0*/ GET_OSD_WIN_REG_WIN0_LV1_A_SEL() \
	( msReadByte( 0x1D01 ) & 0x07 )
#define /*REG_1D01[2:0];h0000[10:8]=h0*/ SET_OSD_WIN_REG_WIN0_LV1_A_SEL( V ) \
	msWriteByteMask( 0x1D01, (V), 0x07 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_lv1*/
#define /*REG_1D01[6:4];h0000[14:12]=h0*/ GET_OSD_WIN_REG_WIN0_LV2_A_SEL() \
	( ( msReadByte( 0x1D01 ) & 0x70 ) >>  4 )
#define /*REG_1D01[6:4];h0000[14:12]=h0*/ SET_OSD_WIN_REG_WIN0_LV2_A_SEL( V ) \
	msWriteByteMask( 0x1D01, ((V) <<  4), 0x70 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_lv1*/
#define /*REG_1D02[4:0];h0001[4:0]=h11*/ GET_OSD_WIN_REG_WIN0_CHARHIGH() \
	( msReadByte( 0x1D02 ) & 0x1F )
#define /*REG_1D02[4:0];h0001[4:0]=h11*/ SET_OSD_WIN_REG_WIN0_CHARHIGH( V ) \
	msWriteByteMask( 0x1D02, (V), 0x1F );
/*
OSD font height (unit : line) .*/
#define /*REG_1D03[5:5];h0001[13:13]=h0*/ GET_OSD_WIN_REG_WIN0_44MODE_TRS_EN_TX() \
	( 0 != ( msReadByte( 0x1D03 ) & 0x20 ) )
#define /*REG_1D03[5:5];h0001[13:13]=h0*/ SET_OSD_WIN_REG_WIN0_44MODE_TRS_EN_TX() \
	msWriteByteMask( 0x1D03, 0xFF, 0x20 );
#define /*REG_1D03[5:5];h0001[13:13]=h0*/ CLR_OSD_WIN_REG_WIN0_44MODE_TRS_EN_TX() \
	msWriteByteMask( 0x1D03, 0x0, 0x20 );
#define /*REG_1D03[5:5];h0001[13:13]=h0*/ ASG_OSD_WIN_REG_WIN0_44MODE_TRS_EN_TX( V ) \
	msWriteByteMask( 0x1D03, ( 0 != (V) )? 0x20: 0, 0x20 );
/*
enable window 44 mode transparent for text*/
#define /*REG_1D03[6:6];h0001[14:14]=h0*/ GET_OSD_WIN_REG_WIN0_44MODE_TRS_EN() \
	( 0 != ( msReadByte( 0x1D03 ) & 0x40 ) )
#define /*REG_1D03[6:6];h0001[14:14]=h0*/ SET_OSD_WIN_REG_WIN0_44MODE_TRS_EN() \
	msWriteByteMask( 0x1D03, 0xFF, 0x40 );
#define /*REG_1D03[6:6];h0001[14:14]=h0*/ CLR_OSD_WIN_REG_WIN0_44MODE_TRS_EN() \
	msWriteByteMask( 0x1D03, 0x0, 0x40 );
#define /*REG_1D03[6:6];h0001[14:14]=h0*/ ASG_OSD_WIN_REG_WIN0_44MODE_TRS_EN( V ) \
	msWriteByteMask( 0x1D03, ( 0 != (V) )? 0x40: 0, 0x40 );
/*
enable window 44 mode transparent*/
#define /*REG_1D03[7:7];h0001[15:15]=h0*/ GET_OSD_WIN_REG_WIN0_1BP_44MODE() \
	( 0 != ( msReadByte( 0x1D03 ) & 0x80 ) )
#define /*REG_1D03[7:7];h0001[15:15]=h0*/ SET_OSD_WIN_REG_WIN0_1BP_44MODE() \
	msWriteByteMask( 0x1D03, 0xFF, 0x80 );
#define /*REG_1D03[7:7];h0001[15:15]=h0*/ CLR_OSD_WIN_REG_WIN0_1BP_44MODE() \
	msWriteByteMask( 0x1D03, 0x0, 0x80 );
#define /*REG_1D03[7:7];h0001[15:15]=h0*/ ASG_OSD_WIN_REG_WIN0_1BP_44MODE( V ) \
	msWriteByteMask( 0x1D03, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
OSD 1bpp use atribute [7:4] or [3:0] mode*/
#define /*REG_1D04[11:0];h0002[11:0]=h0*/ GET_OSD_WIN_REG_WIN0_HSTR_PIX() \
	( msReadByte( 0x1D04 ) | ( (msReadByte( 0x1D05 ) & 0x0F) <<  8 ) )
#define /*REG_1D04[11:0];h0002[11:0]=h0*/ SET_OSD_WIN_REG_WIN0_HSTR_PIX( V ) \
	{ msWriteByte( 0x1D04, (V) ); msWriteByteMask( 0x1D05, ((V) >>  8), 0x0F ); }
/*
OSD window Hori7ontal start positions (pixel)*/
#define /*REG_1D06[11:0];h0003[11:0]=h0*/ GET_OSD_WIN_REG_WIN0_VSTR_PIX() \
	( msReadByte( 0x1D06 ) | ( (msReadByte( 0x1D07 ) & 0x0F) <<  8 ) )
#define /*REG_1D06[11:0];h0003[11:0]=h0*/ SET_OSD_WIN_REG_WIN0_VSTR_PIX( V ) \
	{ msWriteByte( 0x1D06, (V) ); msWriteByteMask( 0x1D07, ((V) >>  8), 0x0F ); }
/*
OSD window Vertical start positions (pixel)*/
#define /*REG_1D08[11:0];h0004[11:0]=h0*/ GET_OSD_WIN_REG_WIN0_HEND_PIX() \
	( msReadByte( 0x1D08 ) | ( (msReadByte( 0x1D09 ) & 0x0F) <<  8 ) )
#define /*REG_1D08[11:0];h0004[11:0]=h0*/ SET_OSD_WIN_REG_WIN0_HEND_PIX( V ) \
	{ msWriteByte( 0x1D08, (V) ); msWriteByteMask( 0x1D09, ((V) >>  8), 0x0F ); }
/*
OSD window Hori7ontal end positions (pixel)*/
#define /*REG_1D09[7:6];h0004[15:14]=h0*/ GET_OSD_WIN_REG_WIN0_HDUP() \
	( ( msReadByte( 0x1D09 ) & 0xC0 ) >>  6 )
#define /*REG_1D09[7:6];h0004[15:14]=h0*/ SET_OSD_WIN_REG_WIN0_HDUP( V ) \
	msWriteByteMask( 0x1D09, ((V) <<  6), 0xC0 );
/*
window vertical duplicate ratio
0: 1x
1: 2x
2: 3x
3: 4x*/
#define /*REG_1D0A[11:0];h0005[11:0]=h0*/ GET_OSD_WIN_REG_WIN0_VEND_PIX() \
	( msReadByte( 0x1D0A ) | ( (msReadByte( 0x1D0B ) & 0x0F) <<  8 ) )
#define /*REG_1D0A[11:0];h0005[11:0]=h0*/ SET_OSD_WIN_REG_WIN0_VEND_PIX( V ) \
	{ msWriteByte( 0x1D0A, (V) ); msWriteByteMask( 0x1D0B, ((V) >>  8), 0x0F ); }
/*
OSD window Vertical end positions (pixel)*/
#define /*REG_1D0B[7:6];h0005[15:14]=h0*/ GET_OSD_WIN_REG_WIN0_VDUP() \
	( ( msReadByte( 0x1D0B ) & 0xC0 ) >>  6 )
#define /*REG_1D0B[7:6];h0005[15:14]=h0*/ SET_OSD_WIN_REG_WIN0_VDUP( V ) \
	msWriteByteMask( 0x1D0B, ((V) <<  6), 0xC0 );
/*
window vertical duplicate ratio
0: 1x
1: 2x
2: 3x
3: 4x*/
#define /*REG_1D0C[5:0];h0006[5:0]=h0*/ GET_OSD_WIN_REG_WIN0_FIX_ALPHA_OUT() \
	( msReadByte( 0x1D0C ) & 0x3F )
#define /*REG_1D0C[5:0];h0006[5:0]=h0*/ SET_OSD_WIN_REG_WIN0_FIX_ALPHA_OUT( V ) \
	msWriteByteMask( 0x1D0C, (V), 0x3F );
/*
OSD fix_alpha for output*/
#define /*REG_1D0D[5:0];h0006[13:8]=h0*/ GET_OSD_WIN_REG_WIN0_FIX_ALPHA_LV1() \
	( msReadByte( 0x1D0D ) & 0x3F )
#define /*REG_1D0D[5:0];h0006[13:8]=h0*/ SET_OSD_WIN_REG_WIN0_FIX_ALPHA_LV1( V ) \
	msWriteByteMask( 0x1D0D, (V), 0x3F );
/*
OSD fix_alpha for lv1*/
#define /*REG_1D0E[4:0];h0007[4:0]=h0*/ GET_OSD_WIN_REG_WIN0_SHIFT_PIX_X() \
	( msReadByte( 0x1D0E ) & 0x1F )
#define /*REG_1D0E[4:0];h0007[4:0]=h0*/ SET_OSD_WIN_REG_WIN0_SHIFT_PIX_X( V ) \
	msWriteByteMask( 0x1D0E, (V), 0x1F );
/*
OSD Font Shift Select by x pixel.*/
#define /*REG_1D0F[4:0];h0007[12:8]=h0*/ GET_OSD_WIN_REG_WIN0_SHIFT_PIX_Y() \
	( msReadByte( 0x1D0F ) & 0x1F )
#define /*REG_1D0F[4:0];h0007[12:8]=h0*/ SET_OSD_WIN_REG_WIN0_SHIFT_PIX_Y( V ) \
	msWriteByteMask( 0x1D0F, (V), 0x1F );
/*
OSD Font Shift Select by y pixel (unit : 1line).*/
#define /*REG_1D10[13:0];h0008[13:0]=h0*/ GET_OSD_WIN_REG_WIN0_BASE() \
	( msReadByte( 0x1D10 ) | ( (msReadByte( 0x1D11 ) & 0x3F) <<  8 ) )
#define /*REG_1D10[13:0];h0008[13:0]=h0*/ SET_OSD_WIN_REG_WIN0_BASE( V ) \
	{ msWriteByte( 0x1D10, (V) ); msWriteByteMask( 0x1D11, ((V) >>  8), 0x3F ); }
/*
OSD code-attribute Base Address.
[13:2] for sram entry, [1:0] for low(0) ~ high(3)  18 bits*/
#define /*REG_1D12[7:0];h0009[7:0]=h0*/ GET_OSD_WIN_REG_WIN0_LINE_OFFSET() \
	( msReadByte( 0x1D12 ) )
#define /*REG_1D12[7:0];h0009[7:0]=h0*/ SET_OSD_WIN_REG_WIN0_LINE_OFFSET( V ) \
	msWriteByte( 0x1D12, (V) );
/*
OSD code buffer line offset value( unit : 1ca (or 1/4 entry)).*/
#define /*REG_1D13[7:0];h0009[15:8]=h0*/ GET_OSD_WIN_REG_WIN0_LINE_OFFSET_TX() \
	( msReadByte( 0x1D13 ) )
#define /*REG_1D13[7:0];h0009[15:8]=h0*/ SET_OSD_WIN_REG_WIN0_LINE_OFFSET_TX( V ) \
	msWriteByte( 0x1D13, (V) );
/*
OSD code buffer line offset value for text
( unit : 1ca (or 1/4 entry)).*/
#define /*REG_1D14[2:0];h000a[2:0]=h0*/ GET_OSD_WIN_REG_WIN0_CLR_R_SEL() \
	( msReadByte( 0x1D14 ) & 0x07 )
#define /*REG_1D14[2:0];h000a[2:0]=h0*/ SET_OSD_WIN_REG_WIN0_CLR_R_SEL( V ) \
	msWriteByteMask( 0x1D14, (V), 0x07 );
/*
grading color R select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr r */
#define /*REG_1D14[6:4];h000a[6:4]=h0*/ GET_OSD_WIN_REG_WIN0_CLR_G_SEL() \
	( ( msReadByte( 0x1D14 ) & 0x70 ) >>  4 )
#define /*REG_1D14[6:4];h000a[6:4]=h0*/ SET_OSD_WIN_REG_WIN0_CLR_G_SEL( V ) \
	msWriteByteMask( 0x1D14, ((V) <<  4), 0x70 );
/*
grading color G select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr g*/
#define /*REG_1D15[2:0];h000a[10:8]=h0*/ GET_OSD_WIN_REG_WIN0_CLR_B_SEL() \
	( msReadByte( 0x1D15 ) & 0x07 )
#define /*REG_1D15[2:0];h000a[10:8]=h0*/ SET_OSD_WIN_REG_WIN0_CLR_B_SEL( V ) \
	msWriteByteMask( 0x1D15, (V), 0x07 );
/*
grading color B select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr b*/
#define /*REG_1D15[4:4];h000a[12:12]=h0*/ GET_OSD_WIN_REG_WIN0_TRANS_INV() \
	( 0 != ( msReadByte( 0x1D15 ) & 0x10 ) )
#define /*REG_1D15[4:4];h000a[12:12]=h0*/ SET_OSD_WIN_REG_WIN0_TRANS_INV() \
	msWriteByteMask( 0x1D15, 0xFF, 0x10 );
#define /*REG_1D15[4:4];h000a[12:12]=h0*/ CLR_OSD_WIN_REG_WIN0_TRANS_INV() \
	msWriteByteMask( 0x1D15, 0x0, 0x10 );
#define /*REG_1D15[4:4];h000a[12:12]=h0*/ ASG_OSD_WIN_REG_WIN0_TRANS_INV( V ) \
	msWriteByteMask( 0x1D15, ( 0 != (V) )? 0x10: 0, 0x10 );
/*
inverse transparent define*/
#define /*REG_1D15[5:5];h000a[13:13]=h0*/ GET_OSD_WIN_REG_WIN0_CKEY_INV() \
	( 0 != ( msReadByte( 0x1D15 ) & 0x20 ) )
#define /*REG_1D15[5:5];h000a[13:13]=h0*/ SET_OSD_WIN_REG_WIN0_CKEY_INV() \
	msWriteByteMask( 0x1D15, 0xFF, 0x20 );
#define /*REG_1D15[5:5];h000a[13:13]=h0*/ CLR_OSD_WIN_REG_WIN0_CKEY_INV() \
	msWriteByteMask( 0x1D15, 0x0, 0x20 );
#define /*REG_1D15[5:5];h000a[13:13]=h0*/ ASG_OSD_WIN_REG_WIN0_CKEY_INV( V ) \
	msWriteByteMask( 0x1D15, ( 0 != (V) )? 0x20: 0, 0x20 );
/*
inverse color key define*/
#define /*REG_1D15[6:6];h000a[14:14]=h0*/ GET_OSD_WIN_REG_WIN0_FIX_ATRB_EN_TX() \
	( 0 != ( msReadByte( 0x1D15 ) & 0x40 ) )
#define /*REG_1D15[6:6];h000a[14:14]=h0*/ SET_OSD_WIN_REG_WIN0_FIX_ATRB_EN_TX() \
	msWriteByteMask( 0x1D15, 0xFF, 0x40 );
#define /*REG_1D15[6:6];h000a[14:14]=h0*/ CLR_OSD_WIN_REG_WIN0_FIX_ATRB_EN_TX() \
	msWriteByteMask( 0x1D15, 0x0, 0x40 );
#define /*REG_1D15[6:6];h000a[14:14]=h0*/ ASG_OSD_WIN_REG_WIN0_FIX_ATRB_EN_TX( V ) \
	msWriteByteMask( 0x1D15, ( 0 != (V) )? 0x40: 0, 0x40 );
/*
enable uniform window attribute mode for text*/
#define /*REG_1D15[7:7];h000a[15:15]=h0*/ GET_OSD_WIN_REG_WIN0_FIX_ATRB_EN() \
	( 0 != ( msReadByte( 0x1D15 ) & 0x80 ) )
#define /*REG_1D15[7:7];h000a[15:15]=h0*/ SET_OSD_WIN_REG_WIN0_FIX_ATRB_EN() \
	msWriteByteMask( 0x1D15, 0xFF, 0x80 );
#define /*REG_1D15[7:7];h000a[15:15]=h0*/ CLR_OSD_WIN_REG_WIN0_FIX_ATRB_EN() \
	msWriteByteMask( 0x1D15, 0x0, 0x80 );
#define /*REG_1D15[7:7];h000a[15:15]=h0*/ ASG_OSD_WIN_REG_WIN0_FIX_ATRB_EN( V ) \
	msWriteByteMask( 0x1D15, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
enable uniform window attribute mode*/
#define /*REG_1D16[7:0];h000b[7:0]=h0*/ GET_OSD_WIN_REG_WIN0_FIX_CLR_R() \
	( msReadByte( 0x1D16 ) )
#define /*REG_1D16[7:0];h000b[7:0]=h0*/ SET_OSD_WIN_REG_WIN0_FIX_CLR_R( V ) \
	msWriteByte( 0x1D16, (V) );
/*
for lv2 blending : fix grading color R*/
#define /*REG_1D17[7:0];h000b[15:8]=h0*/ GET_OSD_WIN_REG_WIN0_FIX_CLR_G() \
	( msReadByte( 0x1D17 ) )
#define /*REG_1D17[7:0];h000b[15:8]=h0*/ SET_OSD_WIN_REG_WIN0_FIX_CLR_G( V ) \
	msWriteByte( 0x1D17, (V) );
/*
for lv2 blending : fix grading color G*/
#define /*REG_1D18[7:0];h000c[7:0]=h0*/ GET_OSD_WIN_REG_WIN0_FIX_CLR_B() \
	( msReadByte( 0x1D18 ) )
#define /*REG_1D18[7:0];h000c[7:0]=h0*/ SET_OSD_WIN_REG_WIN0_FIX_CLR_B( V ) \
	msWriteByte( 0x1D18, (V) );
/*
for lv2 blending : fix grading color B*/
#define /*REG_1D19[5:0];h000c[13:8]=h0*/ GET_OSD_WIN_REG_WIN0_FIX_ALPHA_LV2() \
	( msReadByte( 0x1D19 ) & 0x3F )
#define /*REG_1D19[5:0];h000c[13:8]=h0*/ SET_OSD_WIN_REG_WIN0_FIX_ALPHA_LV2( V ) \
	msWriteByteMask( 0x1D19, (V), 0x3F );
/*
for lv2 blending : fix alpha level 2*/
#define /*REG_1D1A[7:0];h000d[7:0]=h0*/ GET_OSD_WIN_REG_WIN0_FIX_ATRB() \
	( msReadByte( 0x1D1A ) )
#define /*REG_1D1A[7:0];h000d[7:0]=h0*/ SET_OSD_WIN_REG_WIN0_FIX_ATRB( V ) \
	msWriteByte( 0x1D1A, (V) );
/*
uniform window attribute*/
#define /*REG_1D1B[7:0];h000d[15:8]=h0*/ GET_OSD_WIN_REG_WIN0_FIX_ATRB_TX() \
	( msReadByte( 0x1D1B ) )
#define /*REG_1D1B[7:0];h000d[15:8]=h0*/ SET_OSD_WIN_REG_WIN0_FIX_ATRB_TX( V ) \
	msWriteByte( 0x1D1B, (V) );
/*
uniform window attribute for text*/
#define /*REG_1D1C[3:0];h000e[3:0]=h0*/ GET_OSD_WIN_REG_WIN0_MONO_PREFIX() \
	( msReadByte( 0x1D1C ) & 0x0F )
#define /*REG_1D1C[3:0];h000e[3:0]=h0*/ SET_OSD_WIN_REG_WIN0_MONO_PREFIX( V ) \
	msWriteByteMask( 0x1D1C, (V), 0x0F );
/*
register for Mono font prefix atrribute*/
#define /*REG_1D1C[7:4];h000e[7:4]=h0*/ GET_OSD_WIN_REG_WIN0_MONO_PREFIX_TX() \
	( ( msReadByte( 0x1D1C ) & 0xF0 ) >>  4 )
#define /*REG_1D1C[7:4];h000e[7:4]=h0*/ SET_OSD_WIN_REG_WIN0_MONO_PREFIX_TX( V ) \
	msWriteByteMask( 0x1D1C, ((V) <<  4), 0xF0 );
/*
register for Mono font prefix atrribute for text*/
#define /*REG_1D1D[7:0];h000e[15:8]=hf0*/ GET_OSD_WIN_REG_WIN0_DUMMY() \
	( msReadByte( 0x1D1D ) )
#define /*REG_1D1D[7:0];h000e[15:8]=hf0*/ SET_OSD_WIN_REG_WIN0_DUMMY( V ) \
	msWriteByte( 0x1D1D, (V) );
/*
dummy_register_win0*/
#define /*REG_1D1E[13:0];h000f[13:0]=h0*/ GET_OSD_WIN_REG_WIN0_BASE_TX() \
	( msReadByte( 0x1D1E ) | ( (msReadByte( 0x1D1F ) & 0x3F) <<  8 ) )
#define /*REG_1D1E[13:0];h000f[13:0]=h0*/ SET_OSD_WIN_REG_WIN0_BASE_TX( V ) \
	{ msWriteByte( 0x1D1E, (V) ); msWriteByteMask( 0x1D1F, ((V) >>  8), 0x3F ); }
/*
OSD code-attribute Base Address. Fot text
[13:2] for sram entry, [1:0] for low(0) ~ high(3)  18 bits*/
#define /*REG_1D20[0:0];h0010[0:0]=h0*/ GET_OSD_WIN_REG_WIN1_EN() \
	( 0 != ( msReadByte( 0x1D20 ) & 0x01 ) )
#define /*REG_1D20[0:0];h0010[0:0]=h0*/ SET_OSD_WIN_REG_WIN1_EN() \
	msWriteByteMask( 0x1D20, 0xFF, 0x01 );
#define /*REG_1D20[0:0];h0010[0:0]=h0*/ CLR_OSD_WIN_REG_WIN1_EN() \
	msWriteByteMask( 0x1D20, 0x0, 0x01 );
#define /*REG_1D20[0:0];h0010[0:0]=h0*/ ASG_OSD_WIN_REG_WIN1_EN( V ) \
	msWriteByteMask( 0x1D20, ( 0 != (V) )? 0x01: 0, 0x01 );
/*
OSD Window display.
0: window off.
1: window on.*/
#define /*REG_1D20[1:1];h0010[1:1]=h0*/ GET_OSD_WIN_REG_WIN1_CA_DUP_MODE() \
	( 0 != ( msReadByte( 0x1D20 ) & 0x02 ) )
#define /*REG_1D20[1:1];h0010[1:1]=h0*/ SET_OSD_WIN_REG_WIN1_CA_DUP_MODE() \
	msWriteByteMask( 0x1D20, 0xFF, 0x02 );
#define /*REG_1D20[1:1];h0010[1:1]=h0*/ CLR_OSD_WIN_REG_WIN1_CA_DUP_MODE() \
	msWriteByteMask( 0x1D20, 0x0, 0x02 );
#define /*REG_1D20[1:1];h0010[1:1]=h0*/ ASG_OSD_WIN_REG_WIN1_CA_DUP_MODE( V ) \
	msWriteByteMask( 0x1D20, ( 0 != (V) )? 0x02: 0, 0x02 );
/*
window duplicate ca base address*/
#define /*REG_1D20[2:2];h0010[2:2]=h0*/ GET_OSD_WIN_REG_WIN1_FP_MODE() \
	( 0 != ( msReadByte( 0x1D20 ) & 0x04 ) )
#define /*REG_1D20[2:2];h0010[2:2]=h0*/ SET_OSD_WIN_REG_WIN1_FP_MODE() \
	msWriteByteMask( 0x1D20, 0xFF, 0x04 );
#define /*REG_1D20[2:2];h0010[2:2]=h0*/ CLR_OSD_WIN_REG_WIN1_FP_MODE() \
	msWriteByteMask( 0x1D20, 0x0, 0x04 );
#define /*REG_1D20[2:2];h0010[2:2]=h0*/ ASG_OSD_WIN_REG_WIN1_FP_MODE( V ) \
	msWriteByteMask( 0x1D20, ( 0 != (V) )? 0x04: 0, 0x04 );
/*
0: window use "font + text + PG" combination
1: window use "font + PG" combination*/
#define /*REG_1D20[3:3];h0010[3:3]=h0*/ GET_OSD_WIN_REG_WIN1_CA_DUP_MODE_TX() \
	( 0 != ( msReadByte( 0x1D20 ) & 0x08 ) )
#define /*REG_1D20[3:3];h0010[3:3]=h0*/ SET_OSD_WIN_REG_WIN1_CA_DUP_MODE_TX() \
	msWriteByteMask( 0x1D20, 0xFF, 0x08 );
#define /*REG_1D20[3:3];h0010[3:3]=h0*/ CLR_OSD_WIN_REG_WIN1_CA_DUP_MODE_TX() \
	msWriteByteMask( 0x1D20, 0x0, 0x08 );
#define /*REG_1D20[3:3];h0010[3:3]=h0*/ ASG_OSD_WIN_REG_WIN1_CA_DUP_MODE_TX( V ) \
	msWriteByteMask( 0x1D20, ( 0 != (V) )? 0x08: 0, 0x08 );
/*
window duplicate ca base address for text*/
#define /*REG_1D20[6:4];h0010[6:4]=h0*/ GET_OSD_WIN_REG_WIN1_OUT_A_SEL() \
	( ( msReadByte( 0x1D20 ) & 0x70 ) >>  4 )
#define /*REG_1D20[6:4];h0010[6:4]=h0*/ SET_OSD_WIN_REG_WIN1_OUT_A_SEL( V ) \
	msWriteByteMask( 0x1D20, ((V) <<  4), 0x70 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_out*/
#define /*REG_1D20[7:7];h0010[7:7]=h0*/ GET_OSD_WIN_REG_WIN1_TX_EN() \
	( 0 != ( msReadByte( 0x1D20 ) & 0x80 ) )
#define /*REG_1D20[7:7];h0010[7:7]=h0*/ SET_OSD_WIN_REG_WIN1_TX_EN() \
	msWriteByteMask( 0x1D20, 0xFF, 0x80 );
#define /*REG_1D20[7:7];h0010[7:7]=h0*/ CLR_OSD_WIN_REG_WIN1_TX_EN() \
	msWriteByteMask( 0x1D20, 0x0, 0x80 );
#define /*REG_1D20[7:7];h0010[7:7]=h0*/ ASG_OSD_WIN_REG_WIN1_TX_EN( V ) \
	msWriteByteMask( 0x1D20, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
OSD Window display.
0: window font only.
1: window turn on font and text.*/
#define /*REG_1D21[2:0];h0010[10:8]=h0*/ GET_OSD_WIN_REG_WIN1_LV1_A_SEL() \
	( msReadByte( 0x1D21 ) & 0x07 )
#define /*REG_1D21[2:0];h0010[10:8]=h0*/ SET_OSD_WIN_REG_WIN1_LV1_A_SEL( V ) \
	msWriteByteMask( 0x1D21, (V), 0x07 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_lv1*/
#define /*REG_1D21[6:4];h0010[14:12]=h0*/ GET_OSD_WIN_REG_WIN1_LV2_A_SEL() \
	( ( msReadByte( 0x1D21 ) & 0x70 ) >>  4 )
#define /*REG_1D21[6:4];h0010[14:12]=h0*/ SET_OSD_WIN_REG_WIN1_LV2_A_SEL( V ) \
	msWriteByteMask( 0x1D21, ((V) <<  4), 0x70 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_lv1*/
#define /*REG_1D22[4:0];h0011[4:0]=h11*/ GET_OSD_WIN_REG_WIN1_CHARHIGH() \
	( msReadByte( 0x1D22 ) & 0x1F )
#define /*REG_1D22[4:0];h0011[4:0]=h11*/ SET_OSD_WIN_REG_WIN1_CHARHIGH( V ) \
	msWriteByteMask( 0x1D22, (V), 0x1F );
/*
OSD font height (unit : line) .*/
#define /*REG_1D23[5:5];h0011[13:13]=h0*/ GET_OSD_WIN_REG_WIN1_44MODE_TRS_EN_TX() \
	( 0 != ( msReadByte( 0x1D23 ) & 0x20 ) )
#define /*REG_1D23[5:5];h0011[13:13]=h0*/ SET_OSD_WIN_REG_WIN1_44MODE_TRS_EN_TX() \
	msWriteByteMask( 0x1D23, 0xFF, 0x20 );
#define /*REG_1D23[5:5];h0011[13:13]=h0*/ CLR_OSD_WIN_REG_WIN1_44MODE_TRS_EN_TX() \
	msWriteByteMask( 0x1D23, 0x0, 0x20 );
#define /*REG_1D23[5:5];h0011[13:13]=h0*/ ASG_OSD_WIN_REG_WIN1_44MODE_TRS_EN_TX( V ) \
	msWriteByteMask( 0x1D23, ( 0 != (V) )? 0x20: 0, 0x20 );
/*
enable window 44 mode transparent for text*/
#define /*REG_1D23[6:6];h0011[14:14]=h0*/ GET_OSD_WIN_REG_WIN1_44MODE_TRS_EN() \
	( 0 != ( msReadByte( 0x1D23 ) & 0x40 ) )
#define /*REG_1D23[6:6];h0011[14:14]=h0*/ SET_OSD_WIN_REG_WIN1_44MODE_TRS_EN() \
	msWriteByteMask( 0x1D23, 0xFF, 0x40 );
#define /*REG_1D23[6:6];h0011[14:14]=h0*/ CLR_OSD_WIN_REG_WIN1_44MODE_TRS_EN() \
	msWriteByteMask( 0x1D23, 0x0, 0x40 );
#define /*REG_1D23[6:6];h0011[14:14]=h0*/ ASG_OSD_WIN_REG_WIN1_44MODE_TRS_EN( V ) \
	msWriteByteMask( 0x1D23, ( 0 != (V) )? 0x40: 0, 0x40 );
/*
enable window 44 mode transparent*/
#define /*REG_1D23[7:7];h0011[15:15]=h0*/ GET_OSD_WIN_REG_WIN1_1BP_44MODE() \
	( 0 != ( msReadByte( 0x1D23 ) & 0x80 ) )
#define /*REG_1D23[7:7];h0011[15:15]=h0*/ SET_OSD_WIN_REG_WIN1_1BP_44MODE() \
	msWriteByteMask( 0x1D23, 0xFF, 0x80 );
#define /*REG_1D23[7:7];h0011[15:15]=h0*/ CLR_OSD_WIN_REG_WIN1_1BP_44MODE() \
	msWriteByteMask( 0x1D23, 0x0, 0x80 );
#define /*REG_1D23[7:7];h0011[15:15]=h0*/ ASG_OSD_WIN_REG_WIN1_1BP_44MODE( V ) \
	msWriteByteMask( 0x1D23, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
OSD 1bpp use atribute [7:4] or [3:0] mode*/
#define /*REG_1D24[11:0];h0012[11:0]=h0*/ GET_OSD_WIN_REG_WIN1_HSTR_PIX() \
	( msReadByte( 0x1D24 ) | ( (msReadByte( 0x1D25 ) & 0x0F) <<  8 ) )
#define /*REG_1D24[11:0];h0012[11:0]=h0*/ SET_OSD_WIN_REG_WIN1_HSTR_PIX( V ) \
	{ msWriteByte( 0x1D24, (V) ); msWriteByteMask( 0x1D25, ((V) >>  8), 0x0F ); }
/*
OSD window Hori7ontal start positions (pixel)*/
#define /*REG_1D26[11:0];h0013[11:0]=h0*/ GET_OSD_WIN_REG_WIN1_VSTR_PIX() \
	( msReadByte( 0x1D26 ) | ( (msReadByte( 0x1D27 ) & 0x0F) <<  8 ) )
#define /*REG_1D26[11:0];h0013[11:0]=h0*/ SET_OSD_WIN_REG_WIN1_VSTR_PIX( V ) \
	{ msWriteByte( 0x1D26, (V) ); msWriteByteMask( 0x1D27, ((V) >>  8), 0x0F ); }
/*
OSD window Vertical start positions (pixel)*/
#define /*REG_1D28[11:0];h0014[11:0]=h0*/ GET_OSD_WIN_REG_WIN1_HEND_PIX() \
	( msReadByte( 0x1D28 ) | ( (msReadByte( 0x1D29 ) & 0x0F) <<  8 ) )
#define /*REG_1D28[11:0];h0014[11:0]=h0*/ SET_OSD_WIN_REG_WIN1_HEND_PIX( V ) \
	{ msWriteByte( 0x1D28, (V) ); msWriteByteMask( 0x1D29, ((V) >>  8), 0x0F ); }
/*
OSD window Hori7ontal end positions (pixel)*/
#define /*REG_1D29[7:6];h0014[15:14]=h0*/ GET_OSD_WIN_REG_WIN1_HDUP() \
	( ( msReadByte( 0x1D29 ) & 0xC0 ) >>  6 )
#define /*REG_1D29[7:6];h0014[15:14]=h0*/ SET_OSD_WIN_REG_WIN1_HDUP( V ) \
	msWriteByteMask( 0x1D29, ((V) <<  6), 0xC0 );
/*
window vertical duplicate ratio
0: 1x
1: 2x
2: 3x
3: 4x*/
#define /*REG_1D2A[11:0];h0015[11:0]=h0*/ GET_OSD_WIN_REG_WIN1_VEND_PIX() \
	( msReadByte( 0x1D2A ) | ( (msReadByte( 0x1D2B ) & 0x0F) <<  8 ) )
#define /*REG_1D2A[11:0];h0015[11:0]=h0*/ SET_OSD_WIN_REG_WIN1_VEND_PIX( V ) \
	{ msWriteByte( 0x1D2A, (V) ); msWriteByteMask( 0x1D2B, ((V) >>  8), 0x0F ); }
/*
OSD window Vertical end positions (pixel)*/
#define /*REG_1D2B[7:6];h0015[15:14]=h0*/ GET_OSD_WIN_REG_WIN1_VDUP() \
	( ( msReadByte( 0x1D2B ) & 0xC0 ) >>  6 )
#define /*REG_1D2B[7:6];h0015[15:14]=h0*/ SET_OSD_WIN_REG_WIN1_VDUP( V ) \
	msWriteByteMask( 0x1D2B, ((V) <<  6), 0xC0 );
/*
window vertical duplicate ratio
0: 1x
1: 2x
2: 3x
3: 4x*/
#define /*REG_1D2C[5:0];h0016[5:0]=h0*/ GET_OSD_WIN_REG_WIN1_FIX_ALPHA_OUT() \
	( msReadByte( 0x1D2C ) & 0x3F )
#define /*REG_1D2C[5:0];h0016[5:0]=h0*/ SET_OSD_WIN_REG_WIN1_FIX_ALPHA_OUT( V ) \
	msWriteByteMask( 0x1D2C, (V), 0x3F );
/*
OSD fix_alpha for output*/
#define /*REG_1D2D[5:0];h0016[13:8]=h0*/ GET_OSD_WIN_REG_WIN1_FIX_ALPHA_LV1() \
	( msReadByte( 0x1D2D ) & 0x3F )
#define /*REG_1D2D[5:0];h0016[13:8]=h0*/ SET_OSD_WIN_REG_WIN1_FIX_ALPHA_LV1( V ) \
	msWriteByteMask( 0x1D2D, (V), 0x3F );
/*
OSD fix_alpha for lv1*/
#define /*REG_1D2E[4:0];h0017[4:0]=h0*/ GET_OSD_WIN_REG_WIN1_SHIFT_PIX_X() \
	( msReadByte( 0x1D2E ) & 0x1F )
#define /*REG_1D2E[4:0];h0017[4:0]=h0*/ SET_OSD_WIN_REG_WIN1_SHIFT_PIX_X( V ) \
	msWriteByteMask( 0x1D2E, (V), 0x1F );
/*
OSD Font Shift Select by x pixel.*/
#define /*REG_1D2F[4:0];h0017[12:8]=h0*/ GET_OSD_WIN_REG_WIN1_SHIFT_PIX_Y() \
	( msReadByte( 0x1D2F ) & 0x1F )
#define /*REG_1D2F[4:0];h0017[12:8]=h0*/ SET_OSD_WIN_REG_WIN1_SHIFT_PIX_Y( V ) \
	msWriteByteMask( 0x1D2F, (V), 0x1F );
/*
OSD Font Shift Select by y pixel (unit : 1line).*/
#define /*REG_1D30[13:0];h0018[13:0]=h0*/ GET_OSD_WIN_REG_WIN1_BASE() \
	( msReadByte( 0x1D30 ) | ( (msReadByte( 0x1D31 ) & 0x3F) <<  8 ) )
#define /*REG_1D30[13:0];h0018[13:0]=h0*/ SET_OSD_WIN_REG_WIN1_BASE( V ) \
	{ msWriteByte( 0x1D30, (V) ); msWriteByteMask( 0x1D31, ((V) >>  8), 0x3F ); }
/*
OSD code-attribute Base Address.
[13:2] for sram entry, [1:0] for low(0) ~ high(3)  18 bits*/
#define /*REG_1D32[7:0];h0019[7:0]=h0*/ GET_OSD_WIN_REG_WIN1_LINE_OFFSET() \
	( msReadByte( 0x1D32 ) )
#define /*REG_1D32[7:0];h0019[7:0]=h0*/ SET_OSD_WIN_REG_WIN1_LINE_OFFSET( V ) \
	msWriteByte( 0x1D32, (V) );
/*
OSD code buffer line offset value( unit : 1ca (or 1/4 entry)).*/
#define /*REG_1D33[7:0];h0019[15:8]=h0*/ GET_OSD_WIN_REG_WIN1_LINE_OFFSET_TX() \
	( msReadByte( 0x1D33 ) )
#define /*REG_1D33[7:0];h0019[15:8]=h0*/ SET_OSD_WIN_REG_WIN1_LINE_OFFSET_TX( V ) \
	msWriteByte( 0x1D33, (V) );
/*
OSD code buffer line offset value for text
( unit : 1ca (or 1/4 entry)).*/
#define /*REG_1D34[2:0];h001a[2:0]=h0*/ GET_OSD_WIN_REG_WIN1_CLR_R_SEL() \
	( msReadByte( 0x1D34 ) & 0x07 )
#define /*REG_1D34[2:0];h001a[2:0]=h0*/ SET_OSD_WIN_REG_WIN1_CLR_R_SEL( V ) \
	msWriteByteMask( 0x1D34, (V), 0x07 );
/*
grading color R select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr r */
#define /*REG_1D34[6:4];h001a[6:4]=h0*/ GET_OSD_WIN_REG_WIN1_CLR_G_SEL() \
	( ( msReadByte( 0x1D34 ) & 0x70 ) >>  4 )
#define /*REG_1D34[6:4];h001a[6:4]=h0*/ SET_OSD_WIN_REG_WIN1_CLR_G_SEL( V ) \
	msWriteByteMask( 0x1D34, ((V) <<  4), 0x70 );
/*
grading color G select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr g*/
#define /*REG_1D35[2:0];h001a[10:8]=h0*/ GET_OSD_WIN_REG_WIN1_CLR_B_SEL() \
	( msReadByte( 0x1D35 ) & 0x07 )
#define /*REG_1D35[2:0];h001a[10:8]=h0*/ SET_OSD_WIN_REG_WIN1_CLR_B_SEL( V ) \
	msWriteByteMask( 0x1D35, (V), 0x07 );
/*
grading color B select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr b*/
#define /*REG_1D35[4:4];h001a[12:12]=h0*/ GET_OSD_WIN_REG_WIN1_TRANS_INV() \
	( 0 != ( msReadByte( 0x1D35 ) & 0x10 ) )
#define /*REG_1D35[4:4];h001a[12:12]=h0*/ SET_OSD_WIN_REG_WIN1_TRANS_INV() \
	msWriteByteMask( 0x1D35, 0xFF, 0x10 );
#define /*REG_1D35[4:4];h001a[12:12]=h0*/ CLR_OSD_WIN_REG_WIN1_TRANS_INV() \
	msWriteByteMask( 0x1D35, 0x0, 0x10 );
#define /*REG_1D35[4:4];h001a[12:12]=h0*/ ASG_OSD_WIN_REG_WIN1_TRANS_INV( V ) \
	msWriteByteMask( 0x1D35, ( 0 != (V) )? 0x10: 0, 0x10 );
/*
inverse transparent define*/
#define /*REG_1D35[5:5];h001a[13:13]=h0*/ GET_OSD_WIN_REG_WIN1_CKEY_INV() \
	( 0 != ( msReadByte( 0x1D35 ) & 0x20 ) )
#define /*REG_1D35[5:5];h001a[13:13]=h0*/ SET_OSD_WIN_REG_WIN1_CKEY_INV() \
	msWriteByteMask( 0x1D35, 0xFF, 0x20 );
#define /*REG_1D35[5:5];h001a[13:13]=h0*/ CLR_OSD_WIN_REG_WIN1_CKEY_INV() \
	msWriteByteMask( 0x1D35, 0x0, 0x20 );
#define /*REG_1D35[5:5];h001a[13:13]=h0*/ ASG_OSD_WIN_REG_WIN1_CKEY_INV( V ) \
	msWriteByteMask( 0x1D35, ( 0 != (V) )? 0x20: 0, 0x20 );
/*
inverse color key define*/
#define /*REG_1D35[6:6];h001a[14:14]=h0*/ GET_OSD_WIN_REG_WIN1_FIX_ATRB_EN_TX() \
	( 0 != ( msReadByte( 0x1D35 ) & 0x40 ) )
#define /*REG_1D35[6:6];h001a[14:14]=h0*/ SET_OSD_WIN_REG_WIN1_FIX_ATRB_EN_TX() \
	msWriteByteMask( 0x1D35, 0xFF, 0x40 );
#define /*REG_1D35[6:6];h001a[14:14]=h0*/ CLR_OSD_WIN_REG_WIN1_FIX_ATRB_EN_TX() \
	msWriteByteMask( 0x1D35, 0x0, 0x40 );
#define /*REG_1D35[6:6];h001a[14:14]=h0*/ ASG_OSD_WIN_REG_WIN1_FIX_ATRB_EN_TX( V ) \
	msWriteByteMask( 0x1D35, ( 0 != (V) )? 0x40: 0, 0x40 );
/*
enable uniform window attribute mode for text*/
#define /*REG_1D35[7:7];h001a[15:15]=h0*/ GET_OSD_WIN_REG_WIN1_FIX_ATRB_EN() \
	( 0 != ( msReadByte( 0x1D35 ) & 0x80 ) )
#define /*REG_1D35[7:7];h001a[15:15]=h0*/ SET_OSD_WIN_REG_WIN1_FIX_ATRB_EN() \
	msWriteByteMask( 0x1D35, 0xFF, 0x80 );
#define /*REG_1D35[7:7];h001a[15:15]=h0*/ CLR_OSD_WIN_REG_WIN1_FIX_ATRB_EN() \
	msWriteByteMask( 0x1D35, 0x0, 0x80 );
#define /*REG_1D35[7:7];h001a[15:15]=h0*/ ASG_OSD_WIN_REG_WIN1_FIX_ATRB_EN( V ) \
	msWriteByteMask( 0x1D35, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
enable uniform window attribute mode*/
#define /*REG_1D36[7:0];h001b[7:0]=h0*/ GET_OSD_WIN_REG_WIN1_FIX_CLR_R() \
	( msReadByte( 0x1D36 ) )
#define /*REG_1D36[7:0];h001b[7:0]=h0*/ SET_OSD_WIN_REG_WIN1_FIX_CLR_R( V ) \
	msWriteByte( 0x1D36, (V) );
/*
for lv2 blending : fix grading color R*/
#define /*REG_1D37[7:0];h001b[15:8]=h0*/ GET_OSD_WIN_REG_WIN1_FIX_CLR_G() \
	( msReadByte( 0x1D37 ) )
#define /*REG_1D37[7:0];h001b[15:8]=h0*/ SET_OSD_WIN_REG_WIN1_FIX_CLR_G( V ) \
	msWriteByte( 0x1D37, (V) );
/*
for lv2 blending : fix grading color G*/
#define /*REG_1D38[7:0];h001c[7:0]=h0*/ GET_OSD_WIN_REG_WIN1_FIX_CLR_B() \
	( msReadByte( 0x1D38 ) )
#define /*REG_1D38[7:0];h001c[7:0]=h0*/ SET_OSD_WIN_REG_WIN1_FIX_CLR_B( V ) \
	msWriteByte( 0x1D38, (V) );
/*
for lv2 blending : fix grading color B*/
#define /*REG_1D39[5:0];h001c[13:8]=h0*/ GET_OSD_WIN_REG_WIN1_FIX_ALPHA_LV2() \
	( msReadByte( 0x1D39 ) & 0x3F )
#define /*REG_1D39[5:0];h001c[13:8]=h0*/ SET_OSD_WIN_REG_WIN1_FIX_ALPHA_LV2( V ) \
	msWriteByteMask( 0x1D39, (V), 0x3F );
/*
for lv2 blending : fix alpha level 2*/
#define /*REG_1D3A[7:0];h001d[7:0]=h0*/ GET_OSD_WIN_REG_WIN1_FIX_ATRB() \
	( msReadByte( 0x1D3A ) )
#define /*REG_1D3A[7:0];h001d[7:0]=h0*/ SET_OSD_WIN_REG_WIN1_FIX_ATRB( V ) \
	msWriteByte( 0x1D3A, (V) );
/*
uniform window attribute*/
#define /*REG_1D3B[7:0];h001d[15:8]=h0*/ GET_OSD_WIN_REG_WIN1_FIX_ATRB_TX() \
	( msReadByte( 0x1D3B ) )
#define /*REG_1D3B[7:0];h001d[15:8]=h0*/ SET_OSD_WIN_REG_WIN1_FIX_ATRB_TX( V ) \
	msWriteByte( 0x1D3B, (V) );
/*
uniform window attribute for text*/
#define /*REG_1D3C[3:0];h001e[3:0]=h0*/ GET_OSD_WIN_REG_WIN1_MONO_PREFIX() \
	( msReadByte( 0x1D3C ) & 0x0F )
#define /*REG_1D3C[3:0];h001e[3:0]=h0*/ SET_OSD_WIN_REG_WIN1_MONO_PREFIX( V ) \
	msWriteByteMask( 0x1D3C, (V), 0x0F );
/*
register for Mono font prefix atrribute*/
#define /*REG_1D3C[7:4];h001e[7:4]=h0*/ GET_OSD_WIN_REG_WIN1_MONO_PREFIX_TX() \
	( ( msReadByte( 0x1D3C ) & 0xF0 ) >>  4 )
#define /*REG_1D3C[7:4];h001e[7:4]=h0*/ SET_OSD_WIN_REG_WIN1_MONO_PREFIX_TX( V ) \
	msWriteByteMask( 0x1D3C, ((V) <<  4), 0xF0 );
/*
register for Mono font prefix atrribute for text*/
#define /*REG_1D3D[7:0];h001e[15:8]=hf0*/ GET_OSD_WIN_REG_WIN1_DUMMY() \
	( msReadByte( 0x1D3D ) )
#define /*REG_1D3D[7:0];h001e[15:8]=hf0*/ SET_OSD_WIN_REG_WIN1_DUMMY( V ) \
	msWriteByte( 0x1D3D, (V) );
/*
dummy_register_win1*/
#define /*REG_1D3E[13:0];h001f[13:0]=h0*/ GET_OSD_WIN_REG_WIN1_BASE_TX() \
	( msReadByte( 0x1D3E ) | ( (msReadByte( 0x1D3F ) & 0x3F) <<  8 ) )
#define /*REG_1D3E[13:0];h001f[13:0]=h0*/ SET_OSD_WIN_REG_WIN1_BASE_TX( V ) \
	{ msWriteByte( 0x1D3E, (V) ); msWriteByteMask( 0x1D3F, ((V) >>  8), 0x3F ); }
/*
OSD code-attribute Base Address. Fot text
[13:2] for sram entry, [1:0] for low(0) ~ high(3)  18 bits*/
#define /*REG_1D40[0:0];h0020[0:0]=h0*/ GET_OSD_WIN_REG_WIN2_EN() \
	( 0 != ( msReadByte( 0x1D40 ) & 0x01 ) )
#define /*REG_1D40[0:0];h0020[0:0]=h0*/ SET_OSD_WIN_REG_WIN2_EN() \
	msWriteByteMask( 0x1D40, 0xFF, 0x01 );
#define /*REG_1D40[0:0];h0020[0:0]=h0*/ CLR_OSD_WIN_REG_WIN2_EN() \
	msWriteByteMask( 0x1D40, 0x0, 0x01 );
#define /*REG_1D40[0:0];h0020[0:0]=h0*/ ASG_OSD_WIN_REG_WIN2_EN( V ) \
	msWriteByteMask( 0x1D40, ( 0 != (V) )? 0x01: 0, 0x01 );
/*
OSD Window display.
0: window off.
1: window on.*/
#define /*REG_1D40[1:1];h0020[1:1]=h0*/ GET_OSD_WIN_REG_WIN2_CA_DUP_MODE() \
	( 0 != ( msReadByte( 0x1D40 ) & 0x02 ) )
#define /*REG_1D40[1:1];h0020[1:1]=h0*/ SET_OSD_WIN_REG_WIN2_CA_DUP_MODE() \
	msWriteByteMask( 0x1D40, 0xFF, 0x02 );
#define /*REG_1D40[1:1];h0020[1:1]=h0*/ CLR_OSD_WIN_REG_WIN2_CA_DUP_MODE() \
	msWriteByteMask( 0x1D40, 0x0, 0x02 );
#define /*REG_1D40[1:1];h0020[1:1]=h0*/ ASG_OSD_WIN_REG_WIN2_CA_DUP_MODE( V ) \
	msWriteByteMask( 0x1D40, ( 0 != (V) )? 0x02: 0, 0x02 );
/*
window duplicate ca base address*/
#define /*REG_1D40[2:2];h0020[2:2]=h0*/ GET_OSD_WIN_REG_WIN2_FP_MODE() \
	( 0 != ( msReadByte( 0x1D40 ) & 0x04 ) )
#define /*REG_1D40[2:2];h0020[2:2]=h0*/ SET_OSD_WIN_REG_WIN2_FP_MODE() \
	msWriteByteMask( 0x1D40, 0xFF, 0x04 );
#define /*REG_1D40[2:2];h0020[2:2]=h0*/ CLR_OSD_WIN_REG_WIN2_FP_MODE() \
	msWriteByteMask( 0x1D40, 0x0, 0x04 );
#define /*REG_1D40[2:2];h0020[2:2]=h0*/ ASG_OSD_WIN_REG_WIN2_FP_MODE( V ) \
	msWriteByteMask( 0x1D40, ( 0 != (V) )? 0x04: 0, 0x04 );
/*
0: window use "font + text + PG" combination
1: window use "font + PG" combination*/
#define /*REG_1D40[3:3];h0020[3:3]=h0*/ GET_OSD_WIN_REG_WIN2_CA_DUP_MODE_TX() \
	( 0 != ( msReadByte( 0x1D40 ) & 0x08 ) )
#define /*REG_1D40[3:3];h0020[3:3]=h0*/ SET_OSD_WIN_REG_WIN2_CA_DUP_MODE_TX() \
	msWriteByteMask( 0x1D40, 0xFF, 0x08 );
#define /*REG_1D40[3:3];h0020[3:3]=h0*/ CLR_OSD_WIN_REG_WIN2_CA_DUP_MODE_TX() \
	msWriteByteMask( 0x1D40, 0x0, 0x08 );
#define /*REG_1D40[3:3];h0020[3:3]=h0*/ ASG_OSD_WIN_REG_WIN2_CA_DUP_MODE_TX( V ) \
	msWriteByteMask( 0x1D40, ( 0 != (V) )? 0x08: 0, 0x08 );
/*
window duplicate ca base address for text*/
#define /*REG_1D40[6:4];h0020[6:4]=h0*/ GET_OSD_WIN_REG_WIN2_OUT_A_SEL() \
	( ( msReadByte( 0x1D40 ) & 0x70 ) >>  4 )
#define /*REG_1D40[6:4];h0020[6:4]=h0*/ SET_OSD_WIN_REG_WIN2_OUT_A_SEL( V ) \
	msWriteByteMask( 0x1D40, ((V) <<  4), 0x70 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_out*/
#define /*REG_1D40[7:7];h0020[7:7]=h0*/ GET_OSD_WIN_REG_WIN2_TX_EN() \
	( 0 != ( msReadByte( 0x1D40 ) & 0x80 ) )
#define /*REG_1D40[7:7];h0020[7:7]=h0*/ SET_OSD_WIN_REG_WIN2_TX_EN() \
	msWriteByteMask( 0x1D40, 0xFF, 0x80 );
#define /*REG_1D40[7:7];h0020[7:7]=h0*/ CLR_OSD_WIN_REG_WIN2_TX_EN() \
	msWriteByteMask( 0x1D40, 0x0, 0x80 );
#define /*REG_1D40[7:7];h0020[7:7]=h0*/ ASG_OSD_WIN_REG_WIN2_TX_EN( V ) \
	msWriteByteMask( 0x1D40, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
OSD Window display.
0: window font only.
1: window turn on font and text.*/
#define /*REG_1D41[2:0];h0020[10:8]=h0*/ GET_OSD_WIN_REG_WIN2_LV1_A_SEL() \
	( msReadByte( 0x1D41 ) & 0x07 )
#define /*REG_1D41[2:0];h0020[10:8]=h0*/ SET_OSD_WIN_REG_WIN2_LV1_A_SEL( V ) \
	msWriteByteMask( 0x1D41, (V), 0x07 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_lv1*/
#define /*REG_1D41[6:4];h0020[14:12]=h0*/ GET_OSD_WIN_REG_WIN2_LV2_A_SEL() \
	( ( msReadByte( 0x1D41 ) & 0x70 ) >>  4 )
#define /*REG_1D41[6:4];h0020[14:12]=h0*/ SET_OSD_WIN_REG_WIN2_LV2_A_SEL( V ) \
	msWriteByteMask( 0x1D41, ((V) <<  4), 0x70 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_lv1*/
#define /*REG_1D42[4:0];h0021[4:0]=h11*/ GET_OSD_WIN_REG_WIN2_CHARHIGH() \
	( msReadByte( 0x1D42 ) & 0x1F )
#define /*REG_1D42[4:0];h0021[4:0]=h11*/ SET_OSD_WIN_REG_WIN2_CHARHIGH( V ) \
	msWriteByteMask( 0x1D42, (V), 0x1F );
/*
OSD font height (unit : line) .*/
#define /*REG_1D43[5:5];h0021[13:13]=h0*/ GET_OSD_WIN_REG_WIN2_44MODE_TRS_EN_TX() \
	( 0 != ( msReadByte( 0x1D43 ) & 0x20 ) )
#define /*REG_1D43[5:5];h0021[13:13]=h0*/ SET_OSD_WIN_REG_WIN2_44MODE_TRS_EN_TX() \
	msWriteByteMask( 0x1D43, 0xFF, 0x20 );
#define /*REG_1D43[5:5];h0021[13:13]=h0*/ CLR_OSD_WIN_REG_WIN2_44MODE_TRS_EN_TX() \
	msWriteByteMask( 0x1D43, 0x0, 0x20 );
#define /*REG_1D43[5:5];h0021[13:13]=h0*/ ASG_OSD_WIN_REG_WIN2_44MODE_TRS_EN_TX( V ) \
	msWriteByteMask( 0x1D43, ( 0 != (V) )? 0x20: 0, 0x20 );
/*
enable window 44 mode transparent for text*/
#define /*REG_1D43[6:6];h0021[14:14]=h0*/ GET_OSD_WIN_REG_WIN2_44MODE_TRS_EN() \
	( 0 != ( msReadByte( 0x1D43 ) & 0x40 ) )
#define /*REG_1D43[6:6];h0021[14:14]=h0*/ SET_OSD_WIN_REG_WIN2_44MODE_TRS_EN() \
	msWriteByteMask( 0x1D43, 0xFF, 0x40 );
#define /*REG_1D43[6:6];h0021[14:14]=h0*/ CLR_OSD_WIN_REG_WIN2_44MODE_TRS_EN() \
	msWriteByteMask( 0x1D43, 0x0, 0x40 );
#define /*REG_1D43[6:6];h0021[14:14]=h0*/ ASG_OSD_WIN_REG_WIN2_44MODE_TRS_EN( V ) \
	msWriteByteMask( 0x1D43, ( 0 != (V) )? 0x40: 0, 0x40 );
/*
enable window 44 mode transparent*/
#define /*REG_1D43[7:7];h0021[15:15]=h0*/ GET_OSD_WIN_REG_WIN2_1BP_44MODE() \
	( 0 != ( msReadByte( 0x1D43 ) & 0x80 ) )
#define /*REG_1D43[7:7];h0021[15:15]=h0*/ SET_OSD_WIN_REG_WIN2_1BP_44MODE() \
	msWriteByteMask( 0x1D43, 0xFF, 0x80 );
#define /*REG_1D43[7:7];h0021[15:15]=h0*/ CLR_OSD_WIN_REG_WIN2_1BP_44MODE() \
	msWriteByteMask( 0x1D43, 0x0, 0x80 );
#define /*REG_1D43[7:7];h0021[15:15]=h0*/ ASG_OSD_WIN_REG_WIN2_1BP_44MODE( V ) \
	msWriteByteMask( 0x1D43, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
OSD 1bpp use atribute [7:4] or [3:0] mode*/
#define /*REG_1D44[11:0];h0022[11:0]=h0*/ GET_OSD_WIN_REG_WIN2_HSTR_PIX() \
	( msReadByte( 0x1D44 ) | ( (msReadByte( 0x1D45 ) & 0x0F) <<  8 ) )
#define /*REG_1D44[11:0];h0022[11:0]=h0*/ SET_OSD_WIN_REG_WIN2_HSTR_PIX( V ) \
	{ msWriteByte( 0x1D44, (V) ); msWriteByteMask( 0x1D45, ((V) >>  8), 0x0F ); }
/*
OSD window Hori7ontal start positions (pixel)*/
#define /*REG_1D46[11:0];h0023[11:0]=h0*/ GET_OSD_WIN_REG_WIN2_VSTR_PIX() \
	( msReadByte( 0x1D46 ) | ( (msReadByte( 0x1D47 ) & 0x0F) <<  8 ) )
#define /*REG_1D46[11:0];h0023[11:0]=h0*/ SET_OSD_WIN_REG_WIN2_VSTR_PIX( V ) \
	{ msWriteByte( 0x1D46, (V) ); msWriteByteMask( 0x1D47, ((V) >>  8), 0x0F ); }
/*
OSD window Vertical start positions (pixel)*/
#define /*REG_1D48[11:0];h0024[11:0]=h0*/ GET_OSD_WIN_REG_WIN2_HEND_PIX() \
	( msReadByte( 0x1D48 ) | ( (msReadByte( 0x1D49 ) & 0x0F) <<  8 ) )
#define /*REG_1D48[11:0];h0024[11:0]=h0*/ SET_OSD_WIN_REG_WIN2_HEND_PIX( V ) \
	{ msWriteByte( 0x1D48, (V) ); msWriteByteMask( 0x1D49, ((V) >>  8), 0x0F ); }
/*
OSD window Hori7ontal end positions (pixel)*/
#define /*REG_1D49[7:6];h0024[15:14]=h0*/ GET_OSD_WIN_REG_WIN2_HDUP() \
	( ( msReadByte( 0x1D49 ) & 0xC0 ) >>  6 )
#define /*REG_1D49[7:6];h0024[15:14]=h0*/ SET_OSD_WIN_REG_WIN2_HDUP( V ) \
	msWriteByteMask( 0x1D49, ((V) <<  6), 0xC0 );
/*
window vertical duplicate ratio
0: 1x
1: 2x
2: 3x
3: 4x*/
#define /*REG_1D4A[11:0];h0025[11:0]=h0*/ GET_OSD_WIN_REG_WIN2_VEND_PIX() \
	( msReadByte( 0x1D4A ) | ( (msReadByte( 0x1D4B ) & 0x0F) <<  8 ) )
#define /*REG_1D4A[11:0];h0025[11:0]=h0*/ SET_OSD_WIN_REG_WIN2_VEND_PIX( V ) \
	{ msWriteByte( 0x1D4A, (V) ); msWriteByteMask( 0x1D4B, ((V) >>  8), 0x0F ); }
/*
OSD window Vertical end positions (pixel)*/
#define /*REG_1D4B[7:6];h0025[15:14]=h0*/ GET_OSD_WIN_REG_WIN2_VDUP() \
	( ( msReadByte( 0x1D4B ) & 0xC0 ) >>  6 )
#define /*REG_1D4B[7:6];h0025[15:14]=h0*/ SET_OSD_WIN_REG_WIN2_VDUP( V ) \
	msWriteByteMask( 0x1D4B, ((V) <<  6), 0xC0 );
/*
window vertical duplicate ratio
0: 1x
1: 2x
2: 3x
3: 4x*/
#define /*REG_1D4C[5:0];h0026[5:0]=h0*/ GET_OSD_WIN_REG_WIN2_FIX_ALPHA_OUT() \
	( msReadByte( 0x1D4C ) & 0x3F )
#define /*REG_1D4C[5:0];h0026[5:0]=h0*/ SET_OSD_WIN_REG_WIN2_FIX_ALPHA_OUT( V ) \
	msWriteByteMask( 0x1D4C, (V), 0x3F );
/*
OSD fix_alpha for output*/
#define /*REG_1D4D[5:0];h0026[13:8]=h0*/ GET_OSD_WIN_REG_WIN2_FIX_ALPHA_LV1() \
	( msReadByte( 0x1D4D ) & 0x3F )
#define /*REG_1D4D[5:0];h0026[13:8]=h0*/ SET_OSD_WIN_REG_WIN2_FIX_ALPHA_LV1( V ) \
	msWriteByteMask( 0x1D4D, (V), 0x3F );
/*
OSD fix_alpha for lv1*/
#define /*REG_1D4E[4:0];h0027[4:0]=h0*/ GET_OSD_WIN_REG_WIN2_SHIFT_PIX_X() \
	( msReadByte( 0x1D4E ) & 0x1F )
#define /*REG_1D4E[4:0];h0027[4:0]=h0*/ SET_OSD_WIN_REG_WIN2_SHIFT_PIX_X( V ) \
	msWriteByteMask( 0x1D4E, (V), 0x1F );
/*
OSD Font Shift Select by x pixel.*/
#define /*REG_1D4F[4:0];h0027[12:8]=h0*/ GET_OSD_WIN_REG_WIN2_SHIFT_PIX_Y() \
	( msReadByte( 0x1D4F ) & 0x1F )
#define /*REG_1D4F[4:0];h0027[12:8]=h0*/ SET_OSD_WIN_REG_WIN2_SHIFT_PIX_Y( V ) \
	msWriteByteMask( 0x1D4F, (V), 0x1F );
/*
OSD Font Shift Select by y pixel (unit : 1line).*/
#define /*REG_1D50[13:0];h0028[13:0]=h0*/ GET_OSD_WIN_REG_WIN2_BASE() \
	( msReadByte( 0x1D50 ) | ( (msReadByte( 0x1D51 ) & 0x3F) <<  8 ) )
#define /*REG_1D50[13:0];h0028[13:0]=h0*/ SET_OSD_WIN_REG_WIN2_BASE( V ) \
	{ msWriteByte( 0x1D50, (V) ); msWriteByteMask( 0x1D51, ((V) >>  8), 0x3F ); }
/*
OSD code-attribute Base Address.
[13:2] for sram entry, [1:0] for low(0) ~ high(3)  18 bits*/
#define /*REG_1D52[7:0];h0029[7:0]=h0*/ GET_OSD_WIN_REG_WIN2_LINE_OFFSET() \
	( msReadByte( 0x1D52 ) )
#define /*REG_1D52[7:0];h0029[7:0]=h0*/ SET_OSD_WIN_REG_WIN2_LINE_OFFSET( V ) \
	msWriteByte( 0x1D52, (V) );
/*
OSD code buffer line offset value( unit : 1ca (or 1/4 entry)).*/
#define /*REG_1D53[7:0];h0029[15:8]=h0*/ GET_OSD_WIN_REG_WIN2_LINE_OFFSET_TX() \
	( msReadByte( 0x1D53 ) )
#define /*REG_1D53[7:0];h0029[15:8]=h0*/ SET_OSD_WIN_REG_WIN2_LINE_OFFSET_TX( V ) \
	msWriteByte( 0x1D53, (V) );
/*
OSD code buffer line offset value for text
( unit : 1ca (or 1/4 entry)).*/
#define /*REG_1D54[2:0];h002a[2:0]=h0*/ GET_OSD_WIN_REG_WIN2_CLR_R_SEL() \
	( msReadByte( 0x1D54 ) & 0x07 )
#define /*REG_1D54[2:0];h002a[2:0]=h0*/ SET_OSD_WIN_REG_WIN2_CLR_R_SEL( V ) \
	msWriteByteMask( 0x1D54, (V), 0x07 );
/*
grading color R select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr r */
#define /*REG_1D54[6:4];h002a[6:4]=h0*/ GET_OSD_WIN_REG_WIN2_CLR_G_SEL() \
	( ( msReadByte( 0x1D54 ) & 0x70 ) >>  4 )
#define /*REG_1D54[6:4];h002a[6:4]=h0*/ SET_OSD_WIN_REG_WIN2_CLR_G_SEL( V ) \
	msWriteByteMask( 0x1D54, ((V) <<  4), 0x70 );
/*
grading color G select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr g*/
#define /*REG_1D55[2:0];h002a[10:8]=h0*/ GET_OSD_WIN_REG_WIN2_CLR_B_SEL() \
	( msReadByte( 0x1D55 ) & 0x07 )
#define /*REG_1D55[2:0];h002a[10:8]=h0*/ SET_OSD_WIN_REG_WIN2_CLR_B_SEL( V ) \
	msWriteByteMask( 0x1D55, (V), 0x07 );
/*
grading color B select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr b*/
#define /*REG_1D55[4:4];h002a[12:12]=h0*/ GET_OSD_WIN_REG_WIN2_TRANS_INV() \
	( 0 != ( msReadByte( 0x1D55 ) & 0x10 ) )
#define /*REG_1D55[4:4];h002a[12:12]=h0*/ SET_OSD_WIN_REG_WIN2_TRANS_INV() \
	msWriteByteMask( 0x1D55, 0xFF, 0x10 );
#define /*REG_1D55[4:4];h002a[12:12]=h0*/ CLR_OSD_WIN_REG_WIN2_TRANS_INV() \
	msWriteByteMask( 0x1D55, 0x0, 0x10 );
#define /*REG_1D55[4:4];h002a[12:12]=h0*/ ASG_OSD_WIN_REG_WIN2_TRANS_INV( V ) \
	msWriteByteMask( 0x1D55, ( 0 != (V) )? 0x10: 0, 0x10 );
/*
inverse transparent define*/
#define /*REG_1D55[5:5];h002a[13:13]=h0*/ GET_OSD_WIN_REG_WIN2_CKEY_INV() \
	( 0 != ( msReadByte( 0x1D55 ) & 0x20 ) )
#define /*REG_1D55[5:5];h002a[13:13]=h0*/ SET_OSD_WIN_REG_WIN2_CKEY_INV() \
	msWriteByteMask( 0x1D55, 0xFF, 0x20 );
#define /*REG_1D55[5:5];h002a[13:13]=h0*/ CLR_OSD_WIN_REG_WIN2_CKEY_INV() \
	msWriteByteMask( 0x1D55, 0x0, 0x20 );
#define /*REG_1D55[5:5];h002a[13:13]=h0*/ ASG_OSD_WIN_REG_WIN2_CKEY_INV( V ) \
	msWriteByteMask( 0x1D55, ( 0 != (V) )? 0x20: 0, 0x20 );
/*
inverse color key define*/
#define /*REG_1D55[6:6];h002a[14:14]=h0*/ GET_OSD_WIN_REG_WIN2_FIX_ATRB_EN_TX() \
	( 0 != ( msReadByte( 0x1D55 ) & 0x40 ) )
#define /*REG_1D55[6:6];h002a[14:14]=h0*/ SET_OSD_WIN_REG_WIN2_FIX_ATRB_EN_TX() \
	msWriteByteMask( 0x1D55, 0xFF, 0x40 );
#define /*REG_1D55[6:6];h002a[14:14]=h0*/ CLR_OSD_WIN_REG_WIN2_FIX_ATRB_EN_TX() \
	msWriteByteMask( 0x1D55, 0x0, 0x40 );
#define /*REG_1D55[6:6];h002a[14:14]=h0*/ ASG_OSD_WIN_REG_WIN2_FIX_ATRB_EN_TX( V ) \
	msWriteByteMask( 0x1D55, ( 0 != (V) )? 0x40: 0, 0x40 );
/*
enable uniform window attribute mode for text*/
#define /*REG_1D55[7:7];h002a[15:15]=h0*/ GET_OSD_WIN_REG_WIN2_FIX_ATRB_EN() \
	( 0 != ( msReadByte( 0x1D55 ) & 0x80 ) )
#define /*REG_1D55[7:7];h002a[15:15]=h0*/ SET_OSD_WIN_REG_WIN2_FIX_ATRB_EN() \
	msWriteByteMask( 0x1D55, 0xFF, 0x80 );
#define /*REG_1D55[7:7];h002a[15:15]=h0*/ CLR_OSD_WIN_REG_WIN2_FIX_ATRB_EN() \
	msWriteByteMask( 0x1D55, 0x0, 0x80 );
#define /*REG_1D55[7:7];h002a[15:15]=h0*/ ASG_OSD_WIN_REG_WIN2_FIX_ATRB_EN( V ) \
	msWriteByteMask( 0x1D55, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
enable uniform window attribute mode*/
#define /*REG_1D56[7:0];h002b[7:0]=h0*/ GET_OSD_WIN_REG_WIN2_FIX_CLR_R() \
	( msReadByte( 0x1D56 ) )
#define /*REG_1D56[7:0];h002b[7:0]=h0*/ SET_OSD_WIN_REG_WIN2_FIX_CLR_R( V ) \
	msWriteByte( 0x1D56, (V) );
/*
for lv2 blending : fix grading color R*/
#define /*REG_1D57[7:0];h002b[15:8]=h0*/ GET_OSD_WIN_REG_WIN2_FIX_CLR_G() \
	( msReadByte( 0x1D57 ) )
#define /*REG_1D57[7:0];h002b[15:8]=h0*/ SET_OSD_WIN_REG_WIN2_FIX_CLR_G( V ) \
	msWriteByte( 0x1D57, (V) );
/*
for lv2 blending : fix grading color G*/
#define /*REG_1D58[7:0];h002c[7:0]=h0*/ GET_OSD_WIN_REG_WIN2_FIX_CLR_B() \
	( msReadByte( 0x1D58 ) )
#define /*REG_1D58[7:0];h002c[7:0]=h0*/ SET_OSD_WIN_REG_WIN2_FIX_CLR_B( V ) \
	msWriteByte( 0x1D58, (V) );
/*
for lv2 blending : fix grading color B*/
#define /*REG_1D59[5:0];h002c[13:8]=h0*/ GET_OSD_WIN_REG_WIN2_FIX_ALPHA_LV2() \
	( msReadByte( 0x1D59 ) & 0x3F )
#define /*REG_1D59[5:0];h002c[13:8]=h0*/ SET_OSD_WIN_REG_WIN2_FIX_ALPHA_LV2( V ) \
	msWriteByteMask( 0x1D59, (V), 0x3F );
/*
for lv2 blending : fix alpha level 2*/
#define /*REG_1D5A[7:0];h002d[7:0]=h0*/ GET_OSD_WIN_REG_WIN2_FIX_ATRB() \
	( msReadByte( 0x1D5A ) )
#define /*REG_1D5A[7:0];h002d[7:0]=h0*/ SET_OSD_WIN_REG_WIN2_FIX_ATRB( V ) \
	msWriteByte( 0x1D5A, (V) );
/*
uniform window attribute*/
#define /*REG_1D5B[7:0];h002d[15:8]=h0*/ GET_OSD_WIN_REG_WIN2_FIX_ATRB_TX() \
	( msReadByte( 0x1D5B ) )
#define /*REG_1D5B[7:0];h002d[15:8]=h0*/ SET_OSD_WIN_REG_WIN2_FIX_ATRB_TX( V ) \
	msWriteByte( 0x1D5B, (V) );
/*
uniform window attribute for text*/
#define /*REG_1D5C[3:0];h002e[3:0]=h0*/ GET_OSD_WIN_REG_WIN2_MONO_PREFIX() \
	( msReadByte( 0x1D5C ) & 0x0F )
#define /*REG_1D5C[3:0];h002e[3:0]=h0*/ SET_OSD_WIN_REG_WIN2_MONO_PREFIX( V ) \
	msWriteByteMask( 0x1D5C, (V), 0x0F );
/*
register for Mono font prefix atrribute*/
#define /*REG_1D5C[7:4];h002e[7:4]=h0*/ GET_OSD_WIN_REG_WIN2_MONO_PREFIX_TX() \
	( ( msReadByte( 0x1D5C ) & 0xF0 ) >>  4 )
#define /*REG_1D5C[7:4];h002e[7:4]=h0*/ SET_OSD_WIN_REG_WIN2_MONO_PREFIX_TX( V ) \
	msWriteByteMask( 0x1D5C, ((V) <<  4), 0xF0 );
/*
register for Mono font prefix atrribute for text*/
#define /*REG_1D5D[7:0];h002e[15:8]=hf0*/ GET_OSD_WIN_REG_WIN2_DUMMY() \
	( msReadByte( 0x1D5D ) )
#define /*REG_1D5D[7:0];h002e[15:8]=hf0*/ SET_OSD_WIN_REG_WIN2_DUMMY( V ) \
	msWriteByte( 0x1D5D, (V) );
/*
dummy_register_win2*/
#define /*REG_1D5E[13:0];h002f[13:0]=h0*/ GET_OSD_WIN_REG_WIN2_BASE_TX() \
	( msReadByte( 0x1D5E ) | ( (msReadByte( 0x1D5F ) & 0x3F) <<  8 ) )
#define /*REG_1D5E[13:0];h002f[13:0]=h0*/ SET_OSD_WIN_REG_WIN2_BASE_TX( V ) \
	{ msWriteByte( 0x1D5E, (V) ); msWriteByteMask( 0x1D5F, ((V) >>  8), 0x3F ); }
/*
OSD code-attribute Base Address. Fot text
[13:2] for sram entry, [1:0] for low(0) ~ high(3)  18 bits*/
#define /*REG_1D60[0:0];h0030[0:0]=h0*/ GET_OSD_WIN_REG_WIN3_EN() \
	( 0 != ( msReadByte( 0x1D60 ) & 0x01 ) )
#define /*REG_1D60[0:0];h0030[0:0]=h0*/ SET_OSD_WIN_REG_WIN3_EN() \
	msWriteByteMask( 0x1D60, 0xFF, 0x01 );
#define /*REG_1D60[0:0];h0030[0:0]=h0*/ CLR_OSD_WIN_REG_WIN3_EN() \
	msWriteByteMask( 0x1D60, 0x0, 0x01 );
#define /*REG_1D60[0:0];h0030[0:0]=h0*/ ASG_OSD_WIN_REG_WIN3_EN( V ) \
	msWriteByteMask( 0x1D60, ( 0 != (V) )? 0x01: 0, 0x01 );
/*
OSD Window display.
0: window off.
1: window on.*/
#define /*REG_1D60[1:1];h0030[1:1]=h0*/ GET_OSD_WIN_REG_WIN3_CA_DUP_MODE() \
	( 0 != ( msReadByte( 0x1D60 ) & 0x02 ) )
#define /*REG_1D60[1:1];h0030[1:1]=h0*/ SET_OSD_WIN_REG_WIN3_CA_DUP_MODE() \
	msWriteByteMask( 0x1D60, 0xFF, 0x02 );
#define /*REG_1D60[1:1];h0030[1:1]=h0*/ CLR_OSD_WIN_REG_WIN3_CA_DUP_MODE() \
	msWriteByteMask( 0x1D60, 0x0, 0x02 );
#define /*REG_1D60[1:1];h0030[1:1]=h0*/ ASG_OSD_WIN_REG_WIN3_CA_DUP_MODE( V ) \
	msWriteByteMask( 0x1D60, ( 0 != (V) )? 0x02: 0, 0x02 );
/*
window duplicate ca base address*/
#define /*REG_1D60[2:2];h0030[2:2]=h0*/ GET_OSD_WIN_REG_WIN3_FP_MODE() \
	( 0 != ( msReadByte( 0x1D60 ) & 0x04 ) )
#define /*REG_1D60[2:2];h0030[2:2]=h0*/ SET_OSD_WIN_REG_WIN3_FP_MODE() \
	msWriteByteMask( 0x1D60, 0xFF, 0x04 );
#define /*REG_1D60[2:2];h0030[2:2]=h0*/ CLR_OSD_WIN_REG_WIN3_FP_MODE() \
	msWriteByteMask( 0x1D60, 0x0, 0x04 );
#define /*REG_1D60[2:2];h0030[2:2]=h0*/ ASG_OSD_WIN_REG_WIN3_FP_MODE( V ) \
	msWriteByteMask( 0x1D60, ( 0 != (V) )? 0x04: 0, 0x04 );
/*
0: window use "font + text + PG" combination
1: window use "font + PG" combination*/
#define /*REG_1D60[3:3];h0030[3:3]=h0*/ GET_OSD_WIN_REG_WIN3_CA_DUP_MODE_TX() \
	( 0 != ( msReadByte( 0x1D60 ) & 0x08 ) )
#define /*REG_1D60[3:3];h0030[3:3]=h0*/ SET_OSD_WIN_REG_WIN3_CA_DUP_MODE_TX() \
	msWriteByteMask( 0x1D60, 0xFF, 0x08 );
#define /*REG_1D60[3:3];h0030[3:3]=h0*/ CLR_OSD_WIN_REG_WIN3_CA_DUP_MODE_TX() \
	msWriteByteMask( 0x1D60, 0x0, 0x08 );
#define /*REG_1D60[3:3];h0030[3:3]=h0*/ ASG_OSD_WIN_REG_WIN3_CA_DUP_MODE_TX( V ) \
	msWriteByteMask( 0x1D60, ( 0 != (V) )? 0x08: 0, 0x08 );
/*
window duplicate ca base address for text*/
#define /*REG_1D60[6:4];h0030[6:4]=h0*/ GET_OSD_WIN_REG_WIN3_OUT_A_SEL() \
	( ( msReadByte( 0x1D60 ) & 0x70 ) >>  4 )
#define /*REG_1D60[6:4];h0030[6:4]=h0*/ SET_OSD_WIN_REG_WIN3_OUT_A_SEL( V ) \
	msWriteByteMask( 0x1D60, ((V) <<  4), 0x70 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_out*/
#define /*REG_1D60[7:7];h0030[7:7]=h0*/ GET_OSD_WIN_REG_WIN3_TX_EN() \
	( 0 != ( msReadByte( 0x1D60 ) & 0x80 ) )
#define /*REG_1D60[7:7];h0030[7:7]=h0*/ SET_OSD_WIN_REG_WIN3_TX_EN() \
	msWriteByteMask( 0x1D60, 0xFF, 0x80 );
#define /*REG_1D60[7:7];h0030[7:7]=h0*/ CLR_OSD_WIN_REG_WIN3_TX_EN() \
	msWriteByteMask( 0x1D60, 0x0, 0x80 );
#define /*REG_1D60[7:7];h0030[7:7]=h0*/ ASG_OSD_WIN_REG_WIN3_TX_EN( V ) \
	msWriteByteMask( 0x1D60, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
OSD Window display.
0: window font only.
1: window turn on font and text.*/
#define /*REG_1D61[2:0];h0030[10:8]=h0*/ GET_OSD_WIN_REG_WIN3_LV1_A_SEL() \
	( msReadByte( 0x1D61 ) & 0x07 )
#define /*REG_1D61[2:0];h0030[10:8]=h0*/ SET_OSD_WIN_REG_WIN3_LV1_A_SEL( V ) \
	msWriteByteMask( 0x1D61, (V), 0x07 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_lv1*/
#define /*REG_1D61[6:4];h0030[14:12]=h0*/ GET_OSD_WIN_REG_WIN3_LV2_A_SEL() \
	( ( msReadByte( 0x1D61 ) & 0x70 ) >>  4 )
#define /*REG_1D61[6:4];h0030[14:12]=h0*/ SET_OSD_WIN_REG_WIN3_LV2_A_SEL( V ) \
	msWriteByteMask( 0x1D61, ((V) <<  4), 0x70 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_lv1*/
#define /*REG_1D62[4:0];h0031[4:0]=h11*/ GET_OSD_WIN_REG_WIN3_CHARHIGH() \
	( msReadByte( 0x1D62 ) & 0x1F )
#define /*REG_1D62[4:0];h0031[4:0]=h11*/ SET_OSD_WIN_REG_WIN3_CHARHIGH( V ) \
	msWriteByteMask( 0x1D62, (V), 0x1F );
/*
OSD font height (unit : line) .*/
#define /*REG_1D63[5:5];h0031[13:13]=h0*/ GET_OSD_WIN_REG_WIN3_44MODE_TRS_EN_TX() \
	( 0 != ( msReadByte( 0x1D63 ) & 0x20 ) )
#define /*REG_1D63[5:5];h0031[13:13]=h0*/ SET_OSD_WIN_REG_WIN3_44MODE_TRS_EN_TX() \
	msWriteByteMask( 0x1D63, 0xFF, 0x20 );
#define /*REG_1D63[5:5];h0031[13:13]=h0*/ CLR_OSD_WIN_REG_WIN3_44MODE_TRS_EN_TX() \
	msWriteByteMask( 0x1D63, 0x0, 0x20 );
#define /*REG_1D63[5:5];h0031[13:13]=h0*/ ASG_OSD_WIN_REG_WIN3_44MODE_TRS_EN_TX( V ) \
	msWriteByteMask( 0x1D63, ( 0 != (V) )? 0x20: 0, 0x20 );
/*
enable window 44 mode transparent for text*/
#define /*REG_1D63[6:6];h0031[14:14]=h0*/ GET_OSD_WIN_REG_WIN3_44MODE_TRS_EN() \
	( 0 != ( msReadByte( 0x1D63 ) & 0x40 ) )
#define /*REG_1D63[6:6];h0031[14:14]=h0*/ SET_OSD_WIN_REG_WIN3_44MODE_TRS_EN() \
	msWriteByteMask( 0x1D63, 0xFF, 0x40 );
#define /*REG_1D63[6:6];h0031[14:14]=h0*/ CLR_OSD_WIN_REG_WIN3_44MODE_TRS_EN() \
	msWriteByteMask( 0x1D63, 0x0, 0x40 );
#define /*REG_1D63[6:6];h0031[14:14]=h0*/ ASG_OSD_WIN_REG_WIN3_44MODE_TRS_EN( V ) \
	msWriteByteMask( 0x1D63, ( 0 != (V) )? 0x40: 0, 0x40 );
/*
enable window 44 mode transparent*/
#define /*REG_1D63[7:7];h0031[15:15]=h0*/ GET_OSD_WIN_REG_WIN3_1BP_44MODE() \
	( 0 != ( msReadByte( 0x1D63 ) & 0x80 ) )
#define /*REG_1D63[7:7];h0031[15:15]=h0*/ SET_OSD_WIN_REG_WIN3_1BP_44MODE() \
	msWriteByteMask( 0x1D63, 0xFF, 0x80 );
#define /*REG_1D63[7:7];h0031[15:15]=h0*/ CLR_OSD_WIN_REG_WIN3_1BP_44MODE() \
	msWriteByteMask( 0x1D63, 0x0, 0x80 );
#define /*REG_1D63[7:7];h0031[15:15]=h0*/ ASG_OSD_WIN_REG_WIN3_1BP_44MODE( V ) \
	msWriteByteMask( 0x1D63, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
OSD 1bpp use atribute [7:4] or [3:0] mode*/
#define /*REG_1D64[11:0];h0032[11:0]=h0*/ GET_OSD_WIN_REG_WIN3_HSTR_PIX() \
	( msReadByte( 0x1D64 ) | ( (msReadByte( 0x1D65 ) & 0x0F) <<  8 ) )
#define /*REG_1D64[11:0];h0032[11:0]=h0*/ SET_OSD_WIN_REG_WIN3_HSTR_PIX( V ) \
	{ msWriteByte( 0x1D64, (V) ); msWriteByteMask( 0x1D65, ((V) >>  8), 0x0F ); }
/*
OSD window Hori7ontal start positions (pixel)*/
#define /*REG_1D66[11:0];h0033[11:0]=h0*/ GET_OSD_WIN_REG_WIN3_VSTR_PIX() \
	( msReadByte( 0x1D66 ) | ( (msReadByte( 0x1D67 ) & 0x0F) <<  8 ) )
#define /*REG_1D66[11:0];h0033[11:0]=h0*/ SET_OSD_WIN_REG_WIN3_VSTR_PIX( V ) \
	{ msWriteByte( 0x1D66, (V) ); msWriteByteMask( 0x1D67, ((V) >>  8), 0x0F ); }
/*
OSD window Vertical start positions (pixel)*/
#define /*REG_1D68[11:0];h0034[11:0]=h0*/ GET_OSD_WIN_REG_WIN3_HEND_PIX() \
	( msReadByte( 0x1D68 ) | ( (msReadByte( 0x1D69 ) & 0x0F) <<  8 ) )
#define /*REG_1D68[11:0];h0034[11:0]=h0*/ SET_OSD_WIN_REG_WIN3_HEND_PIX( V ) \
	{ msWriteByte( 0x1D68, (V) ); msWriteByteMask( 0x1D69, ((V) >>  8), 0x0F ); }
/*
OSD window Hori7ontal end positions (pixel)*/
#define /*REG_1D69[7:6];h0034[15:14]=h0*/ GET_OSD_WIN_REG_WIN3_HDUP() \
	( ( msReadByte( 0x1D69 ) & 0xC0 ) >>  6 )
#define /*REG_1D69[7:6];h0034[15:14]=h0*/ SET_OSD_WIN_REG_WIN3_HDUP( V ) \
	msWriteByteMask( 0x1D69, ((V) <<  6), 0xC0 );
/*
window vertical duplicate ratio
0: 1x
1: 2x
2: 3x
3: 4x*/
#define /*REG_1D6A[11:0];h0035[11:0]=h0*/ GET_OSD_WIN_REG_WIN3_VEND_PIX() \
	( msReadByte( 0x1D6A ) | ( (msReadByte( 0x1D6B ) & 0x0F) <<  8 ) )
#define /*REG_1D6A[11:0];h0035[11:0]=h0*/ SET_OSD_WIN_REG_WIN3_VEND_PIX( V ) \
	{ msWriteByte( 0x1D6A, (V) ); msWriteByteMask( 0x1D6B, ((V) >>  8), 0x0F ); }
/*
OSD window Vertical end positions (pixel)*/
#define /*REG_1D6B[7:6];h0035[15:14]=h0*/ GET_OSD_WIN_REG_WIN3_VDUP() \
	( ( msReadByte( 0x1D6B ) & 0xC0 ) >>  6 )
#define /*REG_1D6B[7:6];h0035[15:14]=h0*/ SET_OSD_WIN_REG_WIN3_VDUP( V ) \
	msWriteByteMask( 0x1D6B, ((V) <<  6), 0xC0 );
/*
window vertical duplicate ratio
0: 1x
1: 2x
2: 3x
3: 4x*/
#define /*REG_1D6C[5:0];h0036[5:0]=h0*/ GET_OSD_WIN_REG_WIN3_FIX_ALPHA_OUT() \
	( msReadByte( 0x1D6C ) & 0x3F )
#define /*REG_1D6C[5:0];h0036[5:0]=h0*/ SET_OSD_WIN_REG_WIN3_FIX_ALPHA_OUT( V ) \
	msWriteByteMask( 0x1D6C, (V), 0x3F );
/*
OSD fix_alpha for output*/
#define /*REG_1D6D[5:0];h0036[13:8]=h0*/ GET_OSD_WIN_REG_WIN3_FIX_ALPHA_LV1() \
	( msReadByte( 0x1D6D ) & 0x3F )
#define /*REG_1D6D[5:0];h0036[13:8]=h0*/ SET_OSD_WIN_REG_WIN3_FIX_ALPHA_LV1( V ) \
	msWriteByteMask( 0x1D6D, (V), 0x3F );
/*
OSD fix_alpha for lv1*/
#define /*REG_1D6E[4:0];h0037[4:0]=h0*/ GET_OSD_WIN_REG_WIN3_SHIFT_PIX_X() \
	( msReadByte( 0x1D6E ) & 0x1F )
#define /*REG_1D6E[4:0];h0037[4:0]=h0*/ SET_OSD_WIN_REG_WIN3_SHIFT_PIX_X( V ) \
	msWriteByteMask( 0x1D6E, (V), 0x1F );
/*
OSD Font Shift Select by x pixel.*/
#define /*REG_1D6F[4:0];h0037[12:8]=h0*/ GET_OSD_WIN_REG_WIN3_SHIFT_PIX_Y() \
	( msReadByte( 0x1D6F ) & 0x1F )
#define /*REG_1D6F[4:0];h0037[12:8]=h0*/ SET_OSD_WIN_REG_WIN3_SHIFT_PIX_Y( V ) \
	msWriteByteMask( 0x1D6F, (V), 0x1F );
/*
OSD Font Shift Select by y pixel (unit : 1line).*/
#define /*REG_1D70[13:0];h0038[13:0]=h0*/ GET_OSD_WIN_REG_WIN3_BASE() \
	( msReadByte( 0x1D70 ) | ( (msReadByte( 0x1D71 ) & 0x3F) <<  8 ) )
#define /*REG_1D70[13:0];h0038[13:0]=h0*/ SET_OSD_WIN_REG_WIN3_BASE( V ) \
	{ msWriteByte( 0x1D70, (V) ); msWriteByteMask( 0x1D71, ((V) >>  8), 0x3F ); }
/*
OSD code-attribute Base Address.
[13:2] for sram entry, [1:0] for low(0) ~ high(3)  18 bits*/
#define /*REG_1D72[7:0];h0039[7:0]=h0*/ GET_OSD_WIN_REG_WIN3_LINE_OFFSET() \
	( msReadByte( 0x1D72 ) )
#define /*REG_1D72[7:0];h0039[7:0]=h0*/ SET_OSD_WIN_REG_WIN3_LINE_OFFSET( V ) \
	msWriteByte( 0x1D72, (V) );
/*
OSD code buffer line offset value( unit : 1ca (or 1/4 entry)).*/
#define /*REG_1D73[7:0];h0039[15:8]=h0*/ GET_OSD_WIN_REG_WIN3_LINE_OFFSET_TX() \
	( msReadByte( 0x1D73 ) )
#define /*REG_1D73[7:0];h0039[15:8]=h0*/ SET_OSD_WIN_REG_WIN3_LINE_OFFSET_TX( V ) \
	msWriteByte( 0x1D73, (V) );
/*
OSD code buffer line offset value for text
( unit : 1ca (or 1/4 entry)).*/
#define /*REG_1D74[2:0];h003a[2:0]=h0*/ GET_OSD_WIN_REG_WIN3_CLR_R_SEL() \
	( msReadByte( 0x1D74 ) & 0x07 )
#define /*REG_1D74[2:0];h003a[2:0]=h0*/ SET_OSD_WIN_REG_WIN3_CLR_R_SEL( V ) \
	msWriteByteMask( 0x1D74, (V), 0x07 );
/*
grading color R select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr r */
#define /*REG_1D74[6:4];h003a[6:4]=h0*/ GET_OSD_WIN_REG_WIN3_CLR_G_SEL() \
	( ( msReadByte( 0x1D74 ) & 0x70 ) >>  4 )
#define /*REG_1D74[6:4];h003a[6:4]=h0*/ SET_OSD_WIN_REG_WIN3_CLR_G_SEL( V ) \
	msWriteByteMask( 0x1D74, ((V) <<  4), 0x70 );
/*
grading color G select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr g*/
#define /*REG_1D75[2:0];h003a[10:8]=h0*/ GET_OSD_WIN_REG_WIN3_CLR_B_SEL() \
	( msReadByte( 0x1D75 ) & 0x07 )
#define /*REG_1D75[2:0];h003a[10:8]=h0*/ SET_OSD_WIN_REG_WIN3_CLR_B_SEL( V ) \
	msWriteByteMask( 0x1D75, (V), 0x07 );
/*
grading color B select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr b*/
#define /*REG_1D75[4:4];h003a[12:12]=h0*/ GET_OSD_WIN_REG_WIN3_TRANS_INV() \
	( 0 != ( msReadByte( 0x1D75 ) & 0x10 ) )
#define /*REG_1D75[4:4];h003a[12:12]=h0*/ SET_OSD_WIN_REG_WIN3_TRANS_INV() \
	msWriteByteMask( 0x1D75, 0xFF, 0x10 );
#define /*REG_1D75[4:4];h003a[12:12]=h0*/ CLR_OSD_WIN_REG_WIN3_TRANS_INV() \
	msWriteByteMask( 0x1D75, 0x0, 0x10 );
#define /*REG_1D75[4:4];h003a[12:12]=h0*/ ASG_OSD_WIN_REG_WIN3_TRANS_INV( V ) \
	msWriteByteMask( 0x1D75, ( 0 != (V) )? 0x10: 0, 0x10 );
/*
inverse transparent define*/
#define /*REG_1D75[5:5];h003a[13:13]=h0*/ GET_OSD_WIN_REG_WIN3_CKEY_INV() \
	( 0 != ( msReadByte( 0x1D75 ) & 0x20 ) )
#define /*REG_1D75[5:5];h003a[13:13]=h0*/ SET_OSD_WIN_REG_WIN3_CKEY_INV() \
	msWriteByteMask( 0x1D75, 0xFF, 0x20 );
#define /*REG_1D75[5:5];h003a[13:13]=h0*/ CLR_OSD_WIN_REG_WIN3_CKEY_INV() \
	msWriteByteMask( 0x1D75, 0x0, 0x20 );
#define /*REG_1D75[5:5];h003a[13:13]=h0*/ ASG_OSD_WIN_REG_WIN3_CKEY_INV( V ) \
	msWriteByteMask( 0x1D75, ( 0 != (V) )? 0x20: 0, 0x20 );
/*
inverse color key define*/
#define /*REG_1D75[6:6];h003a[14:14]=h0*/ GET_OSD_WIN_REG_WIN3_FIX_ATRB_EN_TX() \
	( 0 != ( msReadByte( 0x1D75 ) & 0x40 ) )
#define /*REG_1D75[6:6];h003a[14:14]=h0*/ SET_OSD_WIN_REG_WIN3_FIX_ATRB_EN_TX() \
	msWriteByteMask( 0x1D75, 0xFF, 0x40 );
#define /*REG_1D75[6:6];h003a[14:14]=h0*/ CLR_OSD_WIN_REG_WIN3_FIX_ATRB_EN_TX() \
	msWriteByteMask( 0x1D75, 0x0, 0x40 );
#define /*REG_1D75[6:6];h003a[14:14]=h0*/ ASG_OSD_WIN_REG_WIN3_FIX_ATRB_EN_TX( V ) \
	msWriteByteMask( 0x1D75, ( 0 != (V) )? 0x40: 0, 0x40 );
/*
enable uniform window attribute mode for text*/
#define /*REG_1D75[7:7];h003a[15:15]=h0*/ GET_OSD_WIN_REG_WIN3_FIX_ATRB_EN() \
	( 0 != ( msReadByte( 0x1D75 ) & 0x80 ) )
#define /*REG_1D75[7:7];h003a[15:15]=h0*/ SET_OSD_WIN_REG_WIN3_FIX_ATRB_EN() \
	msWriteByteMask( 0x1D75, 0xFF, 0x80 );
#define /*REG_1D75[7:7];h003a[15:15]=h0*/ CLR_OSD_WIN_REG_WIN3_FIX_ATRB_EN() \
	msWriteByteMask( 0x1D75, 0x0, 0x80 );
#define /*REG_1D75[7:7];h003a[15:15]=h0*/ ASG_OSD_WIN_REG_WIN3_FIX_ATRB_EN( V ) \
	msWriteByteMask( 0x1D75, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
enable uniform window attribute mode*/
#define /*REG_1D76[7:0];h003b[7:0]=h0*/ GET_OSD_WIN_REG_WIN3_FIX_CLR_R() \
	( msReadByte( 0x1D76 ) )
#define /*REG_1D76[7:0];h003b[7:0]=h0*/ SET_OSD_WIN_REG_WIN3_FIX_CLR_R( V ) \
	msWriteByte( 0x1D76, (V) );
/*
for lv2 blending : fix grading color R*/
#define /*REG_1D77[7:0];h003b[15:8]=h0*/ GET_OSD_WIN_REG_WIN3_FIX_CLR_G() \
	( msReadByte( 0x1D77 ) )
#define /*REG_1D77[7:0];h003b[15:8]=h0*/ SET_OSD_WIN_REG_WIN3_FIX_CLR_G( V ) \
	msWriteByte( 0x1D77, (V) );
/*
for lv2 blending : fix grading color G*/
#define /*REG_1D78[7:0];h003c[7:0]=h0*/ GET_OSD_WIN_REG_WIN3_FIX_CLR_B() \
	( msReadByte( 0x1D78 ) )
#define /*REG_1D78[7:0];h003c[7:0]=h0*/ SET_OSD_WIN_REG_WIN3_FIX_CLR_B( V ) \
	msWriteByte( 0x1D78, (V) );
/*
for lv2 blending : fix grading color B*/
#define /*REG_1D79[5:0];h003c[13:8]=h0*/ GET_OSD_WIN_REG_WIN3_FIX_ALPHA_LV2() \
	( msReadByte( 0x1D79 ) & 0x3F )
#define /*REG_1D79[5:0];h003c[13:8]=h0*/ SET_OSD_WIN_REG_WIN3_FIX_ALPHA_LV2( V ) \
	msWriteByteMask( 0x1D79, (V), 0x3F );
/*
for lv2 blending : fix alpha level 2*/
#define /*REG_1D7A[7:0];h003d[7:0]=h0*/ GET_OSD_WIN_REG_WIN3_FIX_ATRB() \
	( msReadByte( 0x1D7A ) )
#define /*REG_1D7A[7:0];h003d[7:0]=h0*/ SET_OSD_WIN_REG_WIN3_FIX_ATRB( V ) \
	msWriteByte( 0x1D7A, (V) );
/*
uniform window attribute*/
#define /*REG_1D7B[7:0];h003d[15:8]=h0*/ GET_OSD_WIN_REG_WIN3_FIX_ATRB_TX() \
	( msReadByte( 0x1D7B ) )
#define /*REG_1D7B[7:0];h003d[15:8]=h0*/ SET_OSD_WIN_REG_WIN3_FIX_ATRB_TX( V ) \
	msWriteByte( 0x1D7B, (V) );
/*
uniform window attribute for text*/
#define /*REG_1D7C[3:0];h003e[3:0]=h0*/ GET_OSD_WIN_REG_WIN3_MONO_PREFIX() \
	( msReadByte( 0x1D7C ) & 0x0F )
#define /*REG_1D7C[3:0];h003e[3:0]=h0*/ SET_OSD_WIN_REG_WIN3_MONO_PREFIX( V ) \
	msWriteByteMask( 0x1D7C, (V), 0x0F );
/*
register for Mono font prefix atrribute*/
#define /*REG_1D7C[7:4];h003e[7:4]=h0*/ GET_OSD_WIN_REG_WIN3_MONO_PREFIX_TX() \
	( ( msReadByte( 0x1D7C ) & 0xF0 ) >>  4 )
#define /*REG_1D7C[7:4];h003e[7:4]=h0*/ SET_OSD_WIN_REG_WIN3_MONO_PREFIX_TX( V ) \
	msWriteByteMask( 0x1D7C, ((V) <<  4), 0xF0 );
/*
register for Mono font prefix atrribute for text*/
#define /*REG_1D7D[7:0];h003e[15:8]=hf0*/ GET_OSD_WIN_REG_WIN3_DUMMY() \
	( msReadByte( 0x1D7D ) )
#define /*REG_1D7D[7:0];h003e[15:8]=hf0*/ SET_OSD_WIN_REG_WIN3_DUMMY( V ) \
	msWriteByte( 0x1D7D, (V) );
/*
dummy_register_win3*/
#define /*REG_1D7E[13:0];h003f[13:0]=h0*/ GET_OSD_WIN_REG_WIN3_BASE_TX() \
	( msReadByte( 0x1D7E ) | ( (msReadByte( 0x1D7F ) & 0x3F) <<  8 ) )
#define /*REG_1D7E[13:0];h003f[13:0]=h0*/ SET_OSD_WIN_REG_WIN3_BASE_TX( V ) \
	{ msWriteByte( 0x1D7E, (V) ); msWriteByteMask( 0x1D7F, ((V) >>  8), 0x3F ); }
/*
OSD code-attribute Base Address. Fot text
[13:2] for sram entry, [1:0] for low(0) ~ high(3)  18 bits*/
#define /*REG_1D80[0:0];h0040[0:0]=h0*/ GET_OSD_WIN_REG_WIN4_EN() \
	( 0 != ( msReadByte( 0x1D80 ) & 0x01 ) )
#define /*REG_1D80[0:0];h0040[0:0]=h0*/ SET_OSD_WIN_REG_WIN4_EN() \
	msWriteByteMask( 0x1D80, 0xFF, 0x01 );
#define /*REG_1D80[0:0];h0040[0:0]=h0*/ CLR_OSD_WIN_REG_WIN4_EN() \
	msWriteByteMask( 0x1D80, 0x0, 0x01 );
#define /*REG_1D80[0:0];h0040[0:0]=h0*/ ASG_OSD_WIN_REG_WIN4_EN( V ) \
	msWriteByteMask( 0x1D80, ( 0 != (V) )? 0x01: 0, 0x01 );
/*
OSD Window display.
0: window off.
1: window on.*/
#define /*REG_1D80[1:1];h0040[1:1]=h0*/ GET_OSD_WIN_REG_WIN4_CA_DUP_MODE() \
	( 0 != ( msReadByte( 0x1D80 ) & 0x02 ) )
#define /*REG_1D80[1:1];h0040[1:1]=h0*/ SET_OSD_WIN_REG_WIN4_CA_DUP_MODE() \
	msWriteByteMask( 0x1D80, 0xFF, 0x02 );
#define /*REG_1D80[1:1];h0040[1:1]=h0*/ CLR_OSD_WIN_REG_WIN4_CA_DUP_MODE() \
	msWriteByteMask( 0x1D80, 0x0, 0x02 );
#define /*REG_1D80[1:1];h0040[1:1]=h0*/ ASG_OSD_WIN_REG_WIN4_CA_DUP_MODE( V ) \
	msWriteByteMask( 0x1D80, ( 0 != (V) )? 0x02: 0, 0x02 );
/*
window duplicate ca base address*/
#define /*REG_1D80[2:2];h0040[2:2]=h0*/ GET_OSD_WIN_REG_WIN4_FP_MODE() \
	( 0 != ( msReadByte( 0x1D80 ) & 0x04 ) )
#define /*REG_1D80[2:2];h0040[2:2]=h0*/ SET_OSD_WIN_REG_WIN4_FP_MODE() \
	msWriteByteMask( 0x1D80, 0xFF, 0x04 );
#define /*REG_1D80[2:2];h0040[2:2]=h0*/ CLR_OSD_WIN_REG_WIN4_FP_MODE() \
	msWriteByteMask( 0x1D80, 0x0, 0x04 );
#define /*REG_1D80[2:2];h0040[2:2]=h0*/ ASG_OSD_WIN_REG_WIN4_FP_MODE( V ) \
	msWriteByteMask( 0x1D80, ( 0 != (V) )? 0x04: 0, 0x04 );
/*
0: window use "font + text + PG" combination
1: window use "font + PG" combination*/
#define /*REG_1D80[3:3];h0040[3:3]=h0*/ GET_OSD_WIN_REG_WIN4_CA_DUP_MODE_TX() \
	( 0 != ( msReadByte( 0x1D80 ) & 0x08 ) )
#define /*REG_1D80[3:3];h0040[3:3]=h0*/ SET_OSD_WIN_REG_WIN4_CA_DUP_MODE_TX() \
	msWriteByteMask( 0x1D80, 0xFF, 0x08 );
#define /*REG_1D80[3:3];h0040[3:3]=h0*/ CLR_OSD_WIN_REG_WIN4_CA_DUP_MODE_TX() \
	msWriteByteMask( 0x1D80, 0x0, 0x08 );
#define /*REG_1D80[3:3];h0040[3:3]=h0*/ ASG_OSD_WIN_REG_WIN4_CA_DUP_MODE_TX( V ) \
	msWriteByteMask( 0x1D80, ( 0 != (V) )? 0x08: 0, 0x08 );
/*
window duplicate ca base address for text*/
#define /*REG_1D80[6:4];h0040[6:4]=h0*/ GET_OSD_WIN_REG_WIN4_OUT_A_SEL() \
	( ( msReadByte( 0x1D80 ) & 0x70 ) >>  4 )
#define /*REG_1D80[6:4];h0040[6:4]=h0*/ SET_OSD_WIN_REG_WIN4_OUT_A_SEL( V ) \
	msWriteByteMask( 0x1D80, ((V) <<  4), 0x70 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_out*/
#define /*REG_1D80[7:7];h0040[7:7]=h0*/ GET_OSD_WIN_REG_WIN4_TX_EN() \
	( 0 != ( msReadByte( 0x1D80 ) & 0x80 ) )
#define /*REG_1D80[7:7];h0040[7:7]=h0*/ SET_OSD_WIN_REG_WIN4_TX_EN() \
	msWriteByteMask( 0x1D80, 0xFF, 0x80 );
#define /*REG_1D80[7:7];h0040[7:7]=h0*/ CLR_OSD_WIN_REG_WIN4_TX_EN() \
	msWriteByteMask( 0x1D80, 0x0, 0x80 );
#define /*REG_1D80[7:7];h0040[7:7]=h0*/ ASG_OSD_WIN_REG_WIN4_TX_EN( V ) \
	msWriteByteMask( 0x1D80, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
OSD Window display.
0: window font only.
1: window turn on font and text.*/
#define /*REG_1D81[2:0];h0040[10:8]=h0*/ GET_OSD_WIN_REG_WIN4_LV1_A_SEL() \
	( msReadByte( 0x1D81 ) & 0x07 )
#define /*REG_1D81[2:0];h0040[10:8]=h0*/ SET_OSD_WIN_REG_WIN4_LV1_A_SEL( V ) \
	msWriteByteMask( 0x1D81, (V), 0x07 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_lv1*/
#define /*REG_1D81[6:4];h0040[14:12]=h0*/ GET_OSD_WIN_REG_WIN4_LV2_A_SEL() \
	( ( msReadByte( 0x1D81 ) & 0x70 ) >>  4 )
#define /*REG_1D81[6:4];h0040[14:12]=h0*/ SET_OSD_WIN_REG_WIN4_LV2_A_SEL( V ) \
	msWriteByteMask( 0x1D81, ((V) <<  4), 0x70 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_lv1*/
#define /*REG_1D82[4:0];h0041[4:0]=h11*/ GET_OSD_WIN_REG_WIN4_CHARHIGH() \
	( msReadByte( 0x1D82 ) & 0x1F )
#define /*REG_1D82[4:0];h0041[4:0]=h11*/ SET_OSD_WIN_REG_WIN4_CHARHIGH( V ) \
	msWriteByteMask( 0x1D82, (V), 0x1F );
/*
OSD font height (unit : line) .*/
#define /*REG_1D83[5:5];h0041[13:13]=h0*/ GET_OSD_WIN_REG_WIN4_44MODE_TRS_EN_TX() \
	( 0 != ( msReadByte( 0x1D83 ) & 0x20 ) )
#define /*REG_1D83[5:5];h0041[13:13]=h0*/ SET_OSD_WIN_REG_WIN4_44MODE_TRS_EN_TX() \
	msWriteByteMask( 0x1D83, 0xFF, 0x20 );
#define /*REG_1D83[5:5];h0041[13:13]=h0*/ CLR_OSD_WIN_REG_WIN4_44MODE_TRS_EN_TX() \
	msWriteByteMask( 0x1D83, 0x0, 0x20 );
#define /*REG_1D83[5:5];h0041[13:13]=h0*/ ASG_OSD_WIN_REG_WIN4_44MODE_TRS_EN_TX( V ) \
	msWriteByteMask( 0x1D83, ( 0 != (V) )? 0x20: 0, 0x20 );
/*
enable window 44 mode transparent for text*/
#define /*REG_1D83[6:6];h0041[14:14]=h0*/ GET_OSD_WIN_REG_WIN4_44MODE_TRS_EN() \
	( 0 != ( msReadByte( 0x1D83 ) & 0x40 ) )
#define /*REG_1D83[6:6];h0041[14:14]=h0*/ SET_OSD_WIN_REG_WIN4_44MODE_TRS_EN() \
	msWriteByteMask( 0x1D83, 0xFF, 0x40 );
#define /*REG_1D83[6:6];h0041[14:14]=h0*/ CLR_OSD_WIN_REG_WIN4_44MODE_TRS_EN() \
	msWriteByteMask( 0x1D83, 0x0, 0x40 );
#define /*REG_1D83[6:6];h0041[14:14]=h0*/ ASG_OSD_WIN_REG_WIN4_44MODE_TRS_EN( V ) \
	msWriteByteMask( 0x1D83, ( 0 != (V) )? 0x40: 0, 0x40 );
/*
enable window 44 mode transparent*/
#define /*REG_1D83[7:7];h0041[15:15]=h0*/ GET_OSD_WIN_REG_WIN4_1BP_44MODE() \
	( 0 != ( msReadByte( 0x1D83 ) & 0x80 ) )
#define /*REG_1D83[7:7];h0041[15:15]=h0*/ SET_OSD_WIN_REG_WIN4_1BP_44MODE() \
	msWriteByteMask( 0x1D83, 0xFF, 0x80 );
#define /*REG_1D83[7:7];h0041[15:15]=h0*/ CLR_OSD_WIN_REG_WIN4_1BP_44MODE() \
	msWriteByteMask( 0x1D83, 0x0, 0x80 );
#define /*REG_1D83[7:7];h0041[15:15]=h0*/ ASG_OSD_WIN_REG_WIN4_1BP_44MODE( V ) \
	msWriteByteMask( 0x1D83, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
OSD 1bpp use atribute [7:4] or [3:0] mode*/
#define /*REG_1D84[11:0];h0042[11:0]=h0*/ GET_OSD_WIN_REG_WIN4_HSTR_PIX() \
	( msReadByte( 0x1D84 ) | ( (msReadByte( 0x1D85 ) & 0x0F) <<  8 ) )
#define /*REG_1D84[11:0];h0042[11:0]=h0*/ SET_OSD_WIN_REG_WIN4_HSTR_PIX( V ) \
	{ msWriteByte( 0x1D84, (V) ); msWriteByteMask( 0x1D85, ((V) >>  8), 0x0F ); }
/*
OSD window Hori7ontal start positions (pixel)*/
#define /*REG_1D86[11:0];h0043[11:0]=h0*/ GET_OSD_WIN_REG_WIN4_VSTR_PIX() \
	( msReadByte( 0x1D86 ) | ( (msReadByte( 0x1D87 ) & 0x0F) <<  8 ) )
#define /*REG_1D86[11:0];h0043[11:0]=h0*/ SET_OSD_WIN_REG_WIN4_VSTR_PIX( V ) \
	{ msWriteByte( 0x1D86, (V) ); msWriteByteMask( 0x1D87, ((V) >>  8), 0x0F ); }
/*
OSD window Vertical start positions (pixel)*/
#define /*REG_1D88[11:0];h0044[11:0]=h0*/ GET_OSD_WIN_REG_WIN4_HEND_PIX() \
	( msReadByte( 0x1D88 ) | ( (msReadByte( 0x1D89 ) & 0x0F) <<  8 ) )
#define /*REG_1D88[11:0];h0044[11:0]=h0*/ SET_OSD_WIN_REG_WIN4_HEND_PIX( V ) \
	{ msWriteByte( 0x1D88, (V) ); msWriteByteMask( 0x1D89, ((V) >>  8), 0x0F ); }
/*
OSD window Hori7ontal end positions (pixel)*/
#define /*REG_1D89[7:6];h0044[15:14]=h0*/ GET_OSD_WIN_REG_WIN4_HDUP() \
	( ( msReadByte( 0x1D89 ) & 0xC0 ) >>  6 )
#define /*REG_1D89[7:6];h0044[15:14]=h0*/ SET_OSD_WIN_REG_WIN4_HDUP( V ) \
	msWriteByteMask( 0x1D89, ((V) <<  6), 0xC0 );
/*
window vertical duplicate ratio
0: 1x
1: 2x
2: 3x
3: 4x*/
#define /*REG_1D8A[11:0];h0045[11:0]=h0*/ GET_OSD_WIN_REG_WIN4_VEND_PIX() \
	( msReadByte( 0x1D8A ) | ( (msReadByte( 0x1D8B ) & 0x0F) <<  8 ) )
#define /*REG_1D8A[11:0];h0045[11:0]=h0*/ SET_OSD_WIN_REG_WIN4_VEND_PIX( V ) \
	{ msWriteByte( 0x1D8A, (V) ); msWriteByteMask( 0x1D8B, ((V) >>  8), 0x0F ); }
/*
OSD window Vertical end positions (pixel)*/
#define /*REG_1D8B[7:6];h0045[15:14]=h0*/ GET_OSD_WIN_REG_WIN4_VDUP() \
	( ( msReadByte( 0x1D8B ) & 0xC0 ) >>  6 )
#define /*REG_1D8B[7:6];h0045[15:14]=h0*/ SET_OSD_WIN_REG_WIN4_VDUP( V ) \
	msWriteByteMask( 0x1D8B, ((V) <<  6), 0xC0 );
/*
window vertical duplicate ratio
0: 1x
1: 2x
2: 3x
3: 4x*/
#define /*REG_1D8C[5:0];h0046[5:0]=h0*/ GET_OSD_WIN_REG_WIN4_FIX_ALPHA_OUT() \
	( msReadByte( 0x1D8C ) & 0x3F )
#define /*REG_1D8C[5:0];h0046[5:0]=h0*/ SET_OSD_WIN_REG_WIN4_FIX_ALPHA_OUT( V ) \
	msWriteByteMask( 0x1D8C, (V), 0x3F );
/*
OSD fix_alpha for output*/
#define /*REG_1D8D[5:0];h0046[13:8]=h0*/ GET_OSD_WIN_REG_WIN4_FIX_ALPHA_LV1() \
	( msReadByte( 0x1D8D ) & 0x3F )
#define /*REG_1D8D[5:0];h0046[13:8]=h0*/ SET_OSD_WIN_REG_WIN4_FIX_ALPHA_LV1( V ) \
	msWriteByteMask( 0x1D8D, (V), 0x3F );
/*
OSD fix_alpha for lv1*/
#define /*REG_1D8E[4:0];h0047[4:0]=h0*/ GET_OSD_WIN_REG_WIN4_SHIFT_PIX_X() \
	( msReadByte( 0x1D8E ) & 0x1F )
#define /*REG_1D8E[4:0];h0047[4:0]=h0*/ SET_OSD_WIN_REG_WIN4_SHIFT_PIX_X( V ) \
	msWriteByteMask( 0x1D8E, (V), 0x1F );
/*
OSD Font Shift Select by x pixel.*/
#define /*REG_1D8F[4:0];h0047[12:8]=h0*/ GET_OSD_WIN_REG_WIN4_SHIFT_PIX_Y() \
	( msReadByte( 0x1D8F ) & 0x1F )
#define /*REG_1D8F[4:0];h0047[12:8]=h0*/ SET_OSD_WIN_REG_WIN4_SHIFT_PIX_Y( V ) \
	msWriteByteMask( 0x1D8F, (V), 0x1F );
/*
OSD Font Shift Select by y pixel (unit : 1line).*/
#define /*REG_1D90[13:0];h0048[13:0]=h0*/ GET_OSD_WIN_REG_WIN4_BASE() \
	( msReadByte( 0x1D90 ) | ( (msReadByte( 0x1D91 ) & 0x3F) <<  8 ) )
#define /*REG_1D90[13:0];h0048[13:0]=h0*/ SET_OSD_WIN_REG_WIN4_BASE( V ) \
	{ msWriteByte( 0x1D90, (V) ); msWriteByteMask( 0x1D91, ((V) >>  8), 0x3F ); }
/*
OSD code-attribute Base Address.
[13:2] for sram entry, [1:0] for low(0) ~ high(3)  18 bits*/
#define /*REG_1D92[7:0];h0049[7:0]=h0*/ GET_OSD_WIN_REG_WIN4_LINE_OFFSET() \
	( msReadByte( 0x1D92 ) )
#define /*REG_1D92[7:0];h0049[7:0]=h0*/ SET_OSD_WIN_REG_WIN4_LINE_OFFSET( V ) \
	msWriteByte( 0x1D92, (V) );
/*
OSD code buffer line offset value( unit : 1ca (or 1/4 entry)).*/
#define /*REG_1D93[7:0];h0049[15:8]=h0*/ GET_OSD_WIN_REG_WIN4_LINE_OFFSET_TX() \
	( msReadByte( 0x1D93 ) )
#define /*REG_1D93[7:0];h0049[15:8]=h0*/ SET_OSD_WIN_REG_WIN4_LINE_OFFSET_TX( V ) \
	msWriteByte( 0x1D93, (V) );
/*
OSD code buffer line offset value for text
( unit : 1ca (or 1/4 entry)).*/
#define /*REG_1D94[2:0];h004a[2:0]=h0*/ GET_OSD_WIN_REG_WIN4_CLR_R_SEL() \
	( msReadByte( 0x1D94 ) & 0x07 )
#define /*REG_1D94[2:0];h004a[2:0]=h0*/ SET_OSD_WIN_REG_WIN4_CLR_R_SEL( V ) \
	msWriteByteMask( 0x1D94, (V), 0x07 );
/*
grading color R select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr r */
#define /*REG_1D94[6:4];h004a[6:4]=h0*/ GET_OSD_WIN_REG_WIN4_CLR_G_SEL() \
	( ( msReadByte( 0x1D94 ) & 0x70 ) >>  4 )
#define /*REG_1D94[6:4];h004a[6:4]=h0*/ SET_OSD_WIN_REG_WIN4_CLR_G_SEL( V ) \
	msWriteByteMask( 0x1D94, ((V) <<  4), 0x70 );
/*
grading color G select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr g*/
#define /*REG_1D95[2:0];h004a[10:8]=h0*/ GET_OSD_WIN_REG_WIN4_CLR_B_SEL() \
	( msReadByte( 0x1D95 ) & 0x07 )
#define /*REG_1D95[2:0];h004a[10:8]=h0*/ SET_OSD_WIN_REG_WIN4_CLR_B_SEL( V ) \
	msWriteByteMask( 0x1D95, (V), 0x07 );
/*
grading color B select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr b*/
#define /*REG_1D95[4:4];h004a[12:12]=h0*/ GET_OSD_WIN_REG_WIN4_TRANS_INV() \
	( 0 != ( msReadByte( 0x1D95 ) & 0x10 ) )
#define /*REG_1D95[4:4];h004a[12:12]=h0*/ SET_OSD_WIN_REG_WIN4_TRANS_INV() \
	msWriteByteMask( 0x1D95, 0xFF, 0x10 );
#define /*REG_1D95[4:4];h004a[12:12]=h0*/ CLR_OSD_WIN_REG_WIN4_TRANS_INV() \
	msWriteByteMask( 0x1D95, 0x0, 0x10 );
#define /*REG_1D95[4:4];h004a[12:12]=h0*/ ASG_OSD_WIN_REG_WIN4_TRANS_INV( V ) \
	msWriteByteMask( 0x1D95, ( 0 != (V) )? 0x10: 0, 0x10 );
/*
inverse transparent define*/
#define /*REG_1D95[5:5];h004a[13:13]=h0*/ GET_OSD_WIN_REG_WIN4_CKEY_INV() \
	( 0 != ( msReadByte( 0x1D95 ) & 0x20 ) )
#define /*REG_1D95[5:5];h004a[13:13]=h0*/ SET_OSD_WIN_REG_WIN4_CKEY_INV() \
	msWriteByteMask( 0x1D95, 0xFF, 0x20 );
#define /*REG_1D95[5:5];h004a[13:13]=h0*/ CLR_OSD_WIN_REG_WIN4_CKEY_INV() \
	msWriteByteMask( 0x1D95, 0x0, 0x20 );
#define /*REG_1D95[5:5];h004a[13:13]=h0*/ ASG_OSD_WIN_REG_WIN4_CKEY_INV( V ) \
	msWriteByteMask( 0x1D95, ( 0 != (V) )? 0x20: 0, 0x20 );
/*
inverse color key define*/
#define /*REG_1D95[6:6];h004a[14:14]=h0*/ GET_OSD_WIN_REG_WIN4_FIX_ATRB_EN_TX() \
	( 0 != ( msReadByte( 0x1D95 ) & 0x40 ) )
#define /*REG_1D95[6:6];h004a[14:14]=h0*/ SET_OSD_WIN_REG_WIN4_FIX_ATRB_EN_TX() \
	msWriteByteMask( 0x1D95, 0xFF, 0x40 );
#define /*REG_1D95[6:6];h004a[14:14]=h0*/ CLR_OSD_WIN_REG_WIN4_FIX_ATRB_EN_TX() \
	msWriteByteMask( 0x1D95, 0x0, 0x40 );
#define /*REG_1D95[6:6];h004a[14:14]=h0*/ ASG_OSD_WIN_REG_WIN4_FIX_ATRB_EN_TX( V ) \
	msWriteByteMask( 0x1D95, ( 0 != (V) )? 0x40: 0, 0x40 );
/*
enable uniform window attribute mode for text*/
#define /*REG_1D95[7:7];h004a[15:15]=h0*/ GET_OSD_WIN_REG_WIN4_FIX_ATRB_EN() \
	( 0 != ( msReadByte( 0x1D95 ) & 0x80 ) )
#define /*REG_1D95[7:7];h004a[15:15]=h0*/ SET_OSD_WIN_REG_WIN4_FIX_ATRB_EN() \
	msWriteByteMask( 0x1D95, 0xFF, 0x80 );
#define /*REG_1D95[7:7];h004a[15:15]=h0*/ CLR_OSD_WIN_REG_WIN4_FIX_ATRB_EN() \
	msWriteByteMask( 0x1D95, 0x0, 0x80 );
#define /*REG_1D95[7:7];h004a[15:15]=h0*/ ASG_OSD_WIN_REG_WIN4_FIX_ATRB_EN( V ) \
	msWriteByteMask( 0x1D95, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
enable uniform window attribute mode*/
#define /*REG_1D96[7:0];h004b[7:0]=h0*/ GET_OSD_WIN_REG_WIN4_FIX_CLR_R() \
	( msReadByte( 0x1D96 ) )
#define /*REG_1D96[7:0];h004b[7:0]=h0*/ SET_OSD_WIN_REG_WIN4_FIX_CLR_R( V ) \
	msWriteByte( 0x1D96, (V) );
/*
for lv2 blending : fix grading color R*/
#define /*REG_1D97[7:0];h004b[15:8]=h0*/ GET_OSD_WIN_REG_WIN4_FIX_CLR_G() \
	( msReadByte( 0x1D97 ) )
#define /*REG_1D97[7:0];h004b[15:8]=h0*/ SET_OSD_WIN_REG_WIN4_FIX_CLR_G( V ) \
	msWriteByte( 0x1D97, (V) );
/*
for lv2 blending : fix grading color G*/
#define /*REG_1D98[7:0];h004c[7:0]=h0*/ GET_OSD_WIN_REG_WIN4_FIX_CLR_B() \
	( msReadByte( 0x1D98 ) )
#define /*REG_1D98[7:0];h004c[7:0]=h0*/ SET_OSD_WIN_REG_WIN4_FIX_CLR_B( V ) \
	msWriteByte( 0x1D98, (V) );
/*
for lv2 blending : fix grading color B*/
#define /*REG_1D99[5:0];h004c[13:8]=h0*/ GET_OSD_WIN_REG_WIN4_FIX_ALPHA_LV2() \
	( msReadByte( 0x1D99 ) & 0x3F )
#define /*REG_1D99[5:0];h004c[13:8]=h0*/ SET_OSD_WIN_REG_WIN4_FIX_ALPHA_LV2( V ) \
	msWriteByteMask( 0x1D99, (V), 0x3F );
/*
for lv2 blending : fix alpha level 2*/
#define /*REG_1D9A[7:0];h004d[7:0]=h0*/ GET_OSD_WIN_REG_WIN4_FIX_ATRB() \
	( msReadByte( 0x1D9A ) )
#define /*REG_1D9A[7:0];h004d[7:0]=h0*/ SET_OSD_WIN_REG_WIN4_FIX_ATRB( V ) \
	msWriteByte( 0x1D9A, (V) );
/*
uniform window attribute*/
#define /*REG_1D9B[7:0];h004d[15:8]=h0*/ GET_OSD_WIN_REG_WIN4_FIX_ATRB_TX() \
	( msReadByte( 0x1D9B ) )
#define /*REG_1D9B[7:0];h004d[15:8]=h0*/ SET_OSD_WIN_REG_WIN4_FIX_ATRB_TX( V ) \
	msWriteByte( 0x1D9B, (V) );
/*
uniform window attribute for text*/
#define /*REG_1D9C[3:0];h004e[3:0]=h0*/ GET_OSD_WIN_REG_WIN4_MONO_PREFIX() \
	( msReadByte( 0x1D9C ) & 0x0F )
#define /*REG_1D9C[3:0];h004e[3:0]=h0*/ SET_OSD_WIN_REG_WIN4_MONO_PREFIX( V ) \
	msWriteByteMask( 0x1D9C, (V), 0x0F );
/*
register for Mono font prefix atrribute*/
#define /*REG_1D9C[7:4];h004e[7:4]=h0*/ GET_OSD_WIN_REG_WIN4_MONO_PREFIX_TX() \
	( ( msReadByte( 0x1D9C ) & 0xF0 ) >>  4 )
#define /*REG_1D9C[7:4];h004e[7:4]=h0*/ SET_OSD_WIN_REG_WIN4_MONO_PREFIX_TX( V ) \
	msWriteByteMask( 0x1D9C, ((V) <<  4), 0xF0 );
/*
register for Mono font prefix atrribute for text*/
#define /*REG_1D9D[7:0];h004e[15:8]=hf0*/ GET_OSD_WIN_REG_WIN4_DUMMY() \
	( msReadByte( 0x1D9D ) )
#define /*REG_1D9D[7:0];h004e[15:8]=hf0*/ SET_OSD_WIN_REG_WIN4_DUMMY( V ) \
	msWriteByte( 0x1D9D, (V) );
/*
dummy_register_win4*/
#define /*REG_1D9E[13:0];h004f[13:0]=h0*/ GET_OSD_WIN_REG_WIN4_BASE_TX() \
	( msReadByte( 0x1D9E ) | ( (msReadByte( 0x1D9F ) & 0x3F) <<  8 ) )
#define /*REG_1D9E[13:0];h004f[13:0]=h0*/ SET_OSD_WIN_REG_WIN4_BASE_TX( V ) \
	{ msWriteByte( 0x1D9E, (V) ); msWriteByteMask( 0x1D9F, ((V) >>  8), 0x3F ); }
/*
OSD code-attribute Base Address. Fot text
[13:2] for sram entry, [1:0] for low(0) ~ high(3)  18 bits*/
#define /*REG_1DA0[0:0];h0050[0:0]=h0*/ GET_OSD_WIN_REG_WIN5_EN() \
	( 0 != ( msReadByte( 0x1DA0 ) & 0x01 ) )
#define /*REG_1DA0[0:0];h0050[0:0]=h0*/ SET_OSD_WIN_REG_WIN5_EN() \
	msWriteByteMask( 0x1DA0, 0xFF, 0x01 );
#define /*REG_1DA0[0:0];h0050[0:0]=h0*/ CLR_OSD_WIN_REG_WIN5_EN() \
	msWriteByteMask( 0x1DA0, 0x0, 0x01 );
#define /*REG_1DA0[0:0];h0050[0:0]=h0*/ ASG_OSD_WIN_REG_WIN5_EN( V ) \
	msWriteByteMask( 0x1DA0, ( 0 != (V) )? 0x01: 0, 0x01 );
/*
OSD Window display.
0: window off.
1: window on.*/
#define /*REG_1DA0[1:1];h0050[1:1]=h0*/ GET_OSD_WIN_REG_WIN5_CA_DUP_MODE() \
	( 0 != ( msReadByte( 0x1DA0 ) & 0x02 ) )
#define /*REG_1DA0[1:1];h0050[1:1]=h0*/ SET_OSD_WIN_REG_WIN5_CA_DUP_MODE() \
	msWriteByteMask( 0x1DA0, 0xFF, 0x02 );
#define /*REG_1DA0[1:1];h0050[1:1]=h0*/ CLR_OSD_WIN_REG_WIN5_CA_DUP_MODE() \
	msWriteByteMask( 0x1DA0, 0x0, 0x02 );
#define /*REG_1DA0[1:1];h0050[1:1]=h0*/ ASG_OSD_WIN_REG_WIN5_CA_DUP_MODE( V ) \
	msWriteByteMask( 0x1DA0, ( 0 != (V) )? 0x02: 0, 0x02 );
/*
window duplicate ca base address*/
#define /*REG_1DA0[2:2];h0050[2:2]=h0*/ GET_OSD_WIN_REG_WIN5_FP_MODE() \
	( 0 != ( msReadByte( 0x1DA0 ) & 0x04 ) )
#define /*REG_1DA0[2:2];h0050[2:2]=h0*/ SET_OSD_WIN_REG_WIN5_FP_MODE() \
	msWriteByteMask( 0x1DA0, 0xFF, 0x04 );
#define /*REG_1DA0[2:2];h0050[2:2]=h0*/ CLR_OSD_WIN_REG_WIN5_FP_MODE() \
	msWriteByteMask( 0x1DA0, 0x0, 0x04 );
#define /*REG_1DA0[2:2];h0050[2:2]=h0*/ ASG_OSD_WIN_REG_WIN5_FP_MODE( V ) \
	msWriteByteMask( 0x1DA0, ( 0 != (V) )? 0x04: 0, 0x04 );
/*
0: window use "font + text + PG" combination
1: window use "font + PG" combination*/
#define /*REG_1DA0[3:3];h0050[3:3]=h0*/ GET_OSD_WIN_REG_WIN5_CA_DUP_MODE_TX() \
	( 0 != ( msReadByte( 0x1DA0 ) & 0x08 ) )
#define /*REG_1DA0[3:3];h0050[3:3]=h0*/ SET_OSD_WIN_REG_WIN5_CA_DUP_MODE_TX() \
	msWriteByteMask( 0x1DA0, 0xFF, 0x08 );
#define /*REG_1DA0[3:3];h0050[3:3]=h0*/ CLR_OSD_WIN_REG_WIN5_CA_DUP_MODE_TX() \
	msWriteByteMask( 0x1DA0, 0x0, 0x08 );
#define /*REG_1DA0[3:3];h0050[3:3]=h0*/ ASG_OSD_WIN_REG_WIN5_CA_DUP_MODE_TX( V ) \
	msWriteByteMask( 0x1DA0, ( 0 != (V) )? 0x08: 0, 0x08 );
/*
window duplicate ca base address for text*/
#define /*REG_1DA0[6:4];h0050[6:4]=h0*/ GET_OSD_WIN_REG_WIN5_OUT_A_SEL() \
	( ( msReadByte( 0x1DA0 ) & 0x70 ) >>  4 )
#define /*REG_1DA0[6:4];h0050[6:4]=h0*/ SET_OSD_WIN_REG_WIN5_OUT_A_SEL( V ) \
	msWriteByteMask( 0x1DA0, ((V) <<  4), 0x70 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_out*/
#define /*REG_1DA0[7:7];h0050[7:7]=h0*/ GET_OSD_WIN_REG_WIN5_TX_EN() \
	( 0 != ( msReadByte( 0x1DA0 ) & 0x80 ) )
#define /*REG_1DA0[7:7];h0050[7:7]=h0*/ SET_OSD_WIN_REG_WIN5_TX_EN() \
	msWriteByteMask( 0x1DA0, 0xFF, 0x80 );
#define /*REG_1DA0[7:7];h0050[7:7]=h0*/ CLR_OSD_WIN_REG_WIN5_TX_EN() \
	msWriteByteMask( 0x1DA0, 0x0, 0x80 );
#define /*REG_1DA0[7:7];h0050[7:7]=h0*/ ASG_OSD_WIN_REG_WIN5_TX_EN( V ) \
	msWriteByteMask( 0x1DA0, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
OSD Window display.
0: window font only.
1: window turn on font and text.*/
#define /*REG_1DA1[2:0];h0050[10:8]=h0*/ GET_OSD_WIN_REG_WIN5_LV1_A_SEL() \
	( msReadByte( 0x1DA1 ) & 0x07 )
#define /*REG_1DA1[2:0];h0050[10:8]=h0*/ SET_OSD_WIN_REG_WIN5_LV1_A_SEL( V ) \
	msWriteByteMask( 0x1DA1, (V), 0x07 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_lv1*/
#define /*REG_1DA1[6:4];h0050[14:12]=h0*/ GET_OSD_WIN_REG_WIN5_LV2_A_SEL() \
	( ( msReadByte( 0x1DA1 ) & 0x70 ) >>  4 )
#define /*REG_1DA1[6:4];h0050[14:12]=h0*/ SET_OSD_WIN_REG_WIN5_LV2_A_SEL( V ) \
	msWriteByteMask( 0x1DA1, ((V) <<  4), 0x70 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_lv1*/
#define /*REG_1DA2[4:0];h0051[4:0]=h11*/ GET_OSD_WIN_REG_WIN5_CHARHIGH() \
	( msReadByte( 0x1DA2 ) & 0x1F )
#define /*REG_1DA2[4:0];h0051[4:0]=h11*/ SET_OSD_WIN_REG_WIN5_CHARHIGH( V ) \
	msWriteByteMask( 0x1DA2, (V), 0x1F );
/*
OSD font height (unit : line) .*/
#define /*REG_1DA3[5:5];h0051[13:13]=h0*/ GET_OSD_WIN_REG_WIN5_44MODE_TRS_EN_TX() \
	( 0 != ( msReadByte( 0x1DA3 ) & 0x20 ) )
#define /*REG_1DA3[5:5];h0051[13:13]=h0*/ SET_OSD_WIN_REG_WIN5_44MODE_TRS_EN_TX() \
	msWriteByteMask( 0x1DA3, 0xFF, 0x20 );
#define /*REG_1DA3[5:5];h0051[13:13]=h0*/ CLR_OSD_WIN_REG_WIN5_44MODE_TRS_EN_TX() \
	msWriteByteMask( 0x1DA3, 0x0, 0x20 );
#define /*REG_1DA3[5:5];h0051[13:13]=h0*/ ASG_OSD_WIN_REG_WIN5_44MODE_TRS_EN_TX( V ) \
	msWriteByteMask( 0x1DA3, ( 0 != (V) )? 0x20: 0, 0x20 );
/*
enable window 44 mode transparent for text*/
#define /*REG_1DA3[6:6];h0051[14:14]=h0*/ GET_OSD_WIN_REG_WIN5_44MODE_TRS_EN() \
	( 0 != ( msReadByte( 0x1DA3 ) & 0x40 ) )
#define /*REG_1DA3[6:6];h0051[14:14]=h0*/ SET_OSD_WIN_REG_WIN5_44MODE_TRS_EN() \
	msWriteByteMask( 0x1DA3, 0xFF, 0x40 );
#define /*REG_1DA3[6:6];h0051[14:14]=h0*/ CLR_OSD_WIN_REG_WIN5_44MODE_TRS_EN() \
	msWriteByteMask( 0x1DA3, 0x0, 0x40 );
#define /*REG_1DA3[6:6];h0051[14:14]=h0*/ ASG_OSD_WIN_REG_WIN5_44MODE_TRS_EN( V ) \
	msWriteByteMask( 0x1DA3, ( 0 != (V) )? 0x40: 0, 0x40 );
/*
enable window 44 mode transparent*/
#define /*REG_1DA3[7:7];h0051[15:15]=h0*/ GET_OSD_WIN_REG_WIN5_1BP_44MODE() \
	( 0 != ( msReadByte( 0x1DA3 ) & 0x80 ) )
#define /*REG_1DA3[7:7];h0051[15:15]=h0*/ SET_OSD_WIN_REG_WIN5_1BP_44MODE() \
	msWriteByteMask( 0x1DA3, 0xFF, 0x80 );
#define /*REG_1DA3[7:7];h0051[15:15]=h0*/ CLR_OSD_WIN_REG_WIN5_1BP_44MODE() \
	msWriteByteMask( 0x1DA3, 0x0, 0x80 );
#define /*REG_1DA3[7:7];h0051[15:15]=h0*/ ASG_OSD_WIN_REG_WIN5_1BP_44MODE( V ) \
	msWriteByteMask( 0x1DA3, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
OSD 1bpp use atribute [7:4] or [3:0] mode*/
#define /*REG_1DA4[11:0];h0052[11:0]=h0*/ GET_OSD_WIN_REG_WIN5_HSTR_PIX() \
	( msReadByte( 0x1DA4 ) | ( (msReadByte( 0x1DA5 ) & 0x0F) <<  8 ) )
#define /*REG_1DA4[11:0];h0052[11:0]=h0*/ SET_OSD_WIN_REG_WIN5_HSTR_PIX( V ) \
	{ msWriteByte( 0x1DA4, (V) ); msWriteByteMask( 0x1DA5, ((V) >>  8), 0x0F ); }
/*
OSD window Hori7ontal start positions (pixel)*/
#define /*REG_1DA6[11:0];h0053[11:0]=h0*/ GET_OSD_WIN_REG_WIN5_VSTR_PIX() \
	( msReadByte( 0x1DA6 ) | ( (msReadByte( 0x1DA7 ) & 0x0F) <<  8 ) )
#define /*REG_1DA6[11:0];h0053[11:0]=h0*/ SET_OSD_WIN_REG_WIN5_VSTR_PIX( V ) \
	{ msWriteByte( 0x1DA6, (V) ); msWriteByteMask( 0x1DA7, ((V) >>  8), 0x0F ); }
/*
OSD window Vertical start positions (pixel)*/
#define /*REG_1DA8[11:0];h0054[11:0]=h0*/ GET_OSD_WIN_REG_WIN5_HEND_PIX() \
	( msReadByte( 0x1DA8 ) | ( (msReadByte( 0x1DA9 ) & 0x0F) <<  8 ) )
#define /*REG_1DA8[11:0];h0054[11:0]=h0*/ SET_OSD_WIN_REG_WIN5_HEND_PIX( V ) \
	{ msWriteByte( 0x1DA8, (V) ); msWriteByteMask( 0x1DA9, ((V) >>  8), 0x0F ); }
/*
OSD window Hori7ontal end positions (pixel)*/
#define /*REG_1DA9[7:6];h0054[15:14]=h0*/ GET_OSD_WIN_REG_WIN5_HDUP() \
	( ( msReadByte( 0x1DA9 ) & 0xC0 ) >>  6 )
#define /*REG_1DA9[7:6];h0054[15:14]=h0*/ SET_OSD_WIN_REG_WIN5_HDUP( V ) \
	msWriteByteMask( 0x1DA9, ((V) <<  6), 0xC0 );
/*
window vertical duplicate ratio
0: 1x
1: 2x
2: 3x
3: 4x*/
#define /*REG_1DAA[11:0];h0055[11:0]=h0*/ GET_OSD_WIN_REG_WIN5_VEND_PIX() \
	( msReadByte( 0x1DAA ) | ( (msReadByte( 0x1DAB ) & 0x0F) <<  8 ) )
#define /*REG_1DAA[11:0];h0055[11:0]=h0*/ SET_OSD_WIN_REG_WIN5_VEND_PIX( V ) \
	{ msWriteByte( 0x1DAA, (V) ); msWriteByteMask( 0x1DAB, ((V) >>  8), 0x0F ); }
/*
OSD window Vertical end positions (pixel)*/
#define /*REG_1DAB[7:6];h0055[15:14]=h0*/ GET_OSD_WIN_REG_WIN5_VDUP() \
	( ( msReadByte( 0x1DAB ) & 0xC0 ) >>  6 )
#define /*REG_1DAB[7:6];h0055[15:14]=h0*/ SET_OSD_WIN_REG_WIN5_VDUP( V ) \
	msWriteByteMask( 0x1DAB, ((V) <<  6), 0xC0 );
/*
window vertical duplicate ratio
0: 1x
1: 2x
2: 3x
3: 4x*/
#define /*REG_1DAC[5:0];h0056[5:0]=h0*/ GET_OSD_WIN_REG_WIN5_FIX_ALPHA_OUT() \
	( msReadByte( 0x1DAC ) & 0x3F )
#define /*REG_1DAC[5:0];h0056[5:0]=h0*/ SET_OSD_WIN_REG_WIN5_FIX_ALPHA_OUT( V ) \
	msWriteByteMask( 0x1DAC, (V), 0x3F );
/*
OSD fix_alpha for output*/
#define /*REG_1DAD[5:0];h0056[13:8]=h0*/ GET_OSD_WIN_REG_WIN5_FIX_ALPHA_LV1() \
	( msReadByte( 0x1DAD ) & 0x3F )
#define /*REG_1DAD[5:0];h0056[13:8]=h0*/ SET_OSD_WIN_REG_WIN5_FIX_ALPHA_LV1( V ) \
	msWriteByteMask( 0x1DAD, (V), 0x3F );
/*
OSD fix_alpha for lv1*/
#define /*REG_1DAE[4:0];h0057[4:0]=h0*/ GET_OSD_WIN_REG_WIN5_SHIFT_PIX_X() \
	( msReadByte( 0x1DAE ) & 0x1F )
#define /*REG_1DAE[4:0];h0057[4:0]=h0*/ SET_OSD_WIN_REG_WIN5_SHIFT_PIX_X( V ) \
	msWriteByteMask( 0x1DAE, (V), 0x1F );
/*
OSD Font Shift Select by x pixel.*/
#define /*REG_1DAF[4:0];h0057[12:8]=h0*/ GET_OSD_WIN_REG_WIN5_SHIFT_PIX_Y() \
	( msReadByte( 0x1DAF ) & 0x1F )
#define /*REG_1DAF[4:0];h0057[12:8]=h0*/ SET_OSD_WIN_REG_WIN5_SHIFT_PIX_Y( V ) \
	msWriteByteMask( 0x1DAF, (V), 0x1F );
/*
OSD Font Shift Select by y pixel (unit : 1line).*/
#define /*REG_1DB0[13:0];h0058[13:0]=h0*/ GET_OSD_WIN_REG_WIN5_BASE() \
	( msReadByte( 0x1DB0 ) | ( (msReadByte( 0x1DB1 ) & 0x3F) <<  8 ) )
#define /*REG_1DB0[13:0];h0058[13:0]=h0*/ SET_OSD_WIN_REG_WIN5_BASE( V ) \
	{ msWriteByte( 0x1DB0, (V) ); msWriteByteMask( 0x1DB1, ((V) >>  8), 0x3F ); }
/*
OSD code-attribute Base Address.
[13:2] for sram entry, [1:0] for low(0) ~ high(3)  18 bits*/
#define /*REG_1DB2[7:0];h0059[7:0]=h0*/ GET_OSD_WIN_REG_WIN5_LINE_OFFSET() \
	( msReadByte( 0x1DB2 ) )
#define /*REG_1DB2[7:0];h0059[7:0]=h0*/ SET_OSD_WIN_REG_WIN5_LINE_OFFSET( V ) \
	msWriteByte( 0x1DB2, (V) );
/*
OSD code buffer line offset value( unit : 1ca (or 1/4 entry)).*/
#define /*REG_1DB3[7:0];h0059[15:8]=h0*/ GET_OSD_WIN_REG_WIN5_LINE_OFFSET_TX() \
	( msReadByte( 0x1DB3 ) )
#define /*REG_1DB3[7:0];h0059[15:8]=h0*/ SET_OSD_WIN_REG_WIN5_LINE_OFFSET_TX( V ) \
	msWriteByte( 0x1DB3, (V) );
/*
OSD code buffer line offset value for text
( unit : 1ca (or 1/4 entry)).*/
#define /*REG_1DB4[2:0];h005a[2:0]=h0*/ GET_OSD_WIN_REG_WIN5_CLR_R_SEL() \
	( msReadByte( 0x1DB4 ) & 0x07 )
#define /*REG_1DB4[2:0];h005a[2:0]=h0*/ SET_OSD_WIN_REG_WIN5_CLR_R_SEL( V ) \
	msWriteByteMask( 0x1DB4, (V), 0x07 );
/*
grading color R select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr r */
#define /*REG_1DB4[6:4];h005a[6:4]=h0*/ GET_OSD_WIN_REG_WIN5_CLR_G_SEL() \
	( ( msReadByte( 0x1DB4 ) & 0x70 ) >>  4 )
#define /*REG_1DB4[6:4];h005a[6:4]=h0*/ SET_OSD_WIN_REG_WIN5_CLR_G_SEL( V ) \
	msWriteByteMask( 0x1DB4, ((V) <<  4), 0x70 );
/*
grading color G select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr g*/
#define /*REG_1DB5[2:0];h005a[10:8]=h0*/ GET_OSD_WIN_REG_WIN5_CLR_B_SEL() \
	( msReadByte( 0x1DB5 ) & 0x07 )
#define /*REG_1DB5[2:0];h005a[10:8]=h0*/ SET_OSD_WIN_REG_WIN5_CLR_B_SEL( V ) \
	msWriteByteMask( 0x1DB5, (V), 0x07 );
/*
grading color B select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr b*/
#define /*REG_1DB5[4:4];h005a[12:12]=h0*/ GET_OSD_WIN_REG_WIN5_TRANS_INV() \
	( 0 != ( msReadByte( 0x1DB5 ) & 0x10 ) )
#define /*REG_1DB5[4:4];h005a[12:12]=h0*/ SET_OSD_WIN_REG_WIN5_TRANS_INV() \
	msWriteByteMask( 0x1DB5, 0xFF, 0x10 );
#define /*REG_1DB5[4:4];h005a[12:12]=h0*/ CLR_OSD_WIN_REG_WIN5_TRANS_INV() \
	msWriteByteMask( 0x1DB5, 0x0, 0x10 );
#define /*REG_1DB5[4:4];h005a[12:12]=h0*/ ASG_OSD_WIN_REG_WIN5_TRANS_INV( V ) \
	msWriteByteMask( 0x1DB5, ( 0 != (V) )? 0x10: 0, 0x10 );
/*
inverse transparent define*/
#define /*REG_1DB5[5:5];h005a[13:13]=h0*/ GET_OSD_WIN_REG_WIN5_CKEY_INV() \
	( 0 != ( msReadByte( 0x1DB5 ) & 0x20 ) )
#define /*REG_1DB5[5:5];h005a[13:13]=h0*/ SET_OSD_WIN_REG_WIN5_CKEY_INV() \
	msWriteByteMask( 0x1DB5, 0xFF, 0x20 );
#define /*REG_1DB5[5:5];h005a[13:13]=h0*/ CLR_OSD_WIN_REG_WIN5_CKEY_INV() \
	msWriteByteMask( 0x1DB5, 0x0, 0x20 );
#define /*REG_1DB5[5:5];h005a[13:13]=h0*/ ASG_OSD_WIN_REG_WIN5_CKEY_INV( V ) \
	msWriteByteMask( 0x1DB5, ( 0 != (V) )? 0x20: 0, 0x20 );
/*
inverse color key define*/
#define /*REG_1DB5[6:6];h005a[14:14]=h0*/ GET_OSD_WIN_REG_WIN5_FIX_ATRB_EN_TX() \
	( 0 != ( msReadByte( 0x1DB5 ) & 0x40 ) )
#define /*REG_1DB5[6:6];h005a[14:14]=h0*/ SET_OSD_WIN_REG_WIN5_FIX_ATRB_EN_TX() \
	msWriteByteMask( 0x1DB5, 0xFF, 0x40 );
#define /*REG_1DB5[6:6];h005a[14:14]=h0*/ CLR_OSD_WIN_REG_WIN5_FIX_ATRB_EN_TX() \
	msWriteByteMask( 0x1DB5, 0x0, 0x40 );
#define /*REG_1DB5[6:6];h005a[14:14]=h0*/ ASG_OSD_WIN_REG_WIN5_FIX_ATRB_EN_TX( V ) \
	msWriteByteMask( 0x1DB5, ( 0 != (V) )? 0x40: 0, 0x40 );
/*
enable uniform window attribute mode for text*/
#define /*REG_1DB5[7:7];h005a[15:15]=h0*/ GET_OSD_WIN_REG_WIN5_FIX_ATRB_EN() \
	( 0 != ( msReadByte( 0x1DB5 ) & 0x80 ) )
#define /*REG_1DB5[7:7];h005a[15:15]=h0*/ SET_OSD_WIN_REG_WIN5_FIX_ATRB_EN() \
	msWriteByteMask( 0x1DB5, 0xFF, 0x80 );
#define /*REG_1DB5[7:7];h005a[15:15]=h0*/ CLR_OSD_WIN_REG_WIN5_FIX_ATRB_EN() \
	msWriteByteMask( 0x1DB5, 0x0, 0x80 );
#define /*REG_1DB5[7:7];h005a[15:15]=h0*/ ASG_OSD_WIN_REG_WIN5_FIX_ATRB_EN( V ) \
	msWriteByteMask( 0x1DB5, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
enable uniform window attribute mode*/
#define /*REG_1DB6[7:0];h005b[7:0]=h0*/ GET_OSD_WIN_REG_WIN5_FIX_CLR_R() \
	( msReadByte( 0x1DB6 ) )
#define /*REG_1DB6[7:0];h005b[7:0]=h0*/ SET_OSD_WIN_REG_WIN5_FIX_CLR_R( V ) \
	msWriteByte( 0x1DB6, (V) );
/*
for lv2 blending : fix grading color R*/
#define /*REG_1DB7[7:0];h005b[15:8]=h0*/ GET_OSD_WIN_REG_WIN5_FIX_CLR_G() \
	( msReadByte( 0x1DB7 ) )
#define /*REG_1DB7[7:0];h005b[15:8]=h0*/ SET_OSD_WIN_REG_WIN5_FIX_CLR_G( V ) \
	msWriteByte( 0x1DB7, (V) );
/*
for lv2 blending : fix grading color G*/
#define /*REG_1DB8[7:0];h005c[7:0]=h0*/ GET_OSD_WIN_REG_WIN5_FIX_CLR_B() \
	( msReadByte( 0x1DB8 ) )
#define /*REG_1DB8[7:0];h005c[7:0]=h0*/ SET_OSD_WIN_REG_WIN5_FIX_CLR_B( V ) \
	msWriteByte( 0x1DB8, (V) );
/*
for lv2 blending : fix grading color B*/
#define /*REG_1DB9[5:0];h005c[13:8]=h0*/ GET_OSD_WIN_REG_WIN5_FIX_ALPHA_LV2() \
	( msReadByte( 0x1DB9 ) & 0x3F )
#define /*REG_1DB9[5:0];h005c[13:8]=h0*/ SET_OSD_WIN_REG_WIN5_FIX_ALPHA_LV2( V ) \
	msWriteByteMask( 0x1DB9, (V), 0x3F );
/*
for lv2 blending : fix alpha level 2*/
#define /*REG_1DBA[7:0];h005d[7:0]=h0*/ GET_OSD_WIN_REG_WIN5_FIX_ATRB() \
	( msReadByte( 0x1DBA ) )
#define /*REG_1DBA[7:0];h005d[7:0]=h0*/ SET_OSD_WIN_REG_WIN5_FIX_ATRB( V ) \
	msWriteByte( 0x1DBA, (V) );
/*
uniform window attribute*/
#define /*REG_1DBB[7:0];h005d[15:8]=h0*/ GET_OSD_WIN_REG_WIN5_FIX_ATRB_TX() \
	( msReadByte( 0x1DBB ) )
#define /*REG_1DBB[7:0];h005d[15:8]=h0*/ SET_OSD_WIN_REG_WIN5_FIX_ATRB_TX( V ) \
	msWriteByte( 0x1DBB, (V) );
/*
uniform window attribute for text*/
#define /*REG_1DBC[3:0];h005e[3:0]=h0*/ GET_OSD_WIN_REG_WIN5_MONO_PREFIX() \
	( msReadByte( 0x1DBC ) & 0x0F )
#define /*REG_1DBC[3:0];h005e[3:0]=h0*/ SET_OSD_WIN_REG_WIN5_MONO_PREFIX( V ) \
	msWriteByteMask( 0x1DBC, (V), 0x0F );
/*
register for Mono font prefix atrribute*/
#define /*REG_1DBC[7:4];h005e[7:4]=h0*/ GET_OSD_WIN_REG_WIN5_MONO_PREFIX_TX() \
	( ( msReadByte( 0x1DBC ) & 0xF0 ) >>  4 )
#define /*REG_1DBC[7:4];h005e[7:4]=h0*/ SET_OSD_WIN_REG_WIN5_MONO_PREFIX_TX( V ) \
	msWriteByteMask( 0x1DBC, ((V) <<  4), 0xF0 );
/*
register for Mono font prefix atrribute for text*/
#define /*REG_1DBD[7:0];h005e[15:8]=hf0*/ GET_OSD_WIN_REG_WIN5_DUMMY() \
	( msReadByte( 0x1DBD ) )
#define /*REG_1DBD[7:0];h005e[15:8]=hf0*/ SET_OSD_WIN_REG_WIN5_DUMMY( V ) \
	msWriteByte( 0x1DBD, (V) );
/*
dummy_register_win5*/
#define /*REG_1DBE[13:0];h005f[13:0]=h0*/ GET_OSD_WIN_REG_WIN5_BASE_TX() \
	( msReadByte( 0x1DBE ) | ( (msReadByte( 0x1DBF ) & 0x3F) <<  8 ) )
#define /*REG_1DBE[13:0];h005f[13:0]=h0*/ SET_OSD_WIN_REG_WIN5_BASE_TX( V ) \
	{ msWriteByte( 0x1DBE, (V) ); msWriteByteMask( 0x1DBF, ((V) >>  8), 0x3F ); }
/*
OSD code-attribute Base Address. Fot text
[13:2] for sram entry, [1:0] for low(0) ~ high(3)  18 bits*/
#define /*REG_1DC0[0:0];h0060[0:0]=h0*/ GET_OSD_WIN_REG_WIN6_EN() \
	( 0 != ( msReadByte( 0x1DC0 ) & 0x01 ) )
#define /*REG_1DC0[0:0];h0060[0:0]=h0*/ SET_OSD_WIN_REG_WIN6_EN() \
	msWriteByteMask( 0x1DC0, 0xFF, 0x01 );
#define /*REG_1DC0[0:0];h0060[0:0]=h0*/ CLR_OSD_WIN_REG_WIN6_EN() \
	msWriteByteMask( 0x1DC0, 0x0, 0x01 );
#define /*REG_1DC0[0:0];h0060[0:0]=h0*/ ASG_OSD_WIN_REG_WIN6_EN( V ) \
	msWriteByteMask( 0x1DC0, ( 0 != (V) )? 0x01: 0, 0x01 );
/*
OSD Window display.
0: window off.
1: window on.*/
#define /*REG_1DC0[1:1];h0060[1:1]=h0*/ GET_OSD_WIN_REG_WIN6_CA_DUP_MODE() \
	( 0 != ( msReadByte( 0x1DC0 ) & 0x02 ) )
#define /*REG_1DC0[1:1];h0060[1:1]=h0*/ SET_OSD_WIN_REG_WIN6_CA_DUP_MODE() \
	msWriteByteMask( 0x1DC0, 0xFF, 0x02 );
#define /*REG_1DC0[1:1];h0060[1:1]=h0*/ CLR_OSD_WIN_REG_WIN6_CA_DUP_MODE() \
	msWriteByteMask( 0x1DC0, 0x0, 0x02 );
#define /*REG_1DC0[1:1];h0060[1:1]=h0*/ ASG_OSD_WIN_REG_WIN6_CA_DUP_MODE( V ) \
	msWriteByteMask( 0x1DC0, ( 0 != (V) )? 0x02: 0, 0x02 );
/*
window duplicate ca base address*/
#define /*REG_1DC0[2:2];h0060[2:2]=h0*/ GET_OSD_WIN_REG_WIN6_FP_MODE() \
	( 0 != ( msReadByte( 0x1DC0 ) & 0x04 ) )
#define /*REG_1DC0[2:2];h0060[2:2]=h0*/ SET_OSD_WIN_REG_WIN6_FP_MODE() \
	msWriteByteMask( 0x1DC0, 0xFF, 0x04 );
#define /*REG_1DC0[2:2];h0060[2:2]=h0*/ CLR_OSD_WIN_REG_WIN6_FP_MODE() \
	msWriteByteMask( 0x1DC0, 0x0, 0x04 );
#define /*REG_1DC0[2:2];h0060[2:2]=h0*/ ASG_OSD_WIN_REG_WIN6_FP_MODE( V ) \
	msWriteByteMask( 0x1DC0, ( 0 != (V) )? 0x04: 0, 0x04 );
/*
0: window use "font + text + PG" combination
1: window use "font + PG" combination*/
#define /*REG_1DC0[3:3];h0060[3:3]=h0*/ GET_OSD_WIN_REG_WIN6_CA_DUP_MODE_TX() \
	( 0 != ( msReadByte( 0x1DC0 ) & 0x08 ) )
#define /*REG_1DC0[3:3];h0060[3:3]=h0*/ SET_OSD_WIN_REG_WIN6_CA_DUP_MODE_TX() \
	msWriteByteMask( 0x1DC0, 0xFF, 0x08 );
#define /*REG_1DC0[3:3];h0060[3:3]=h0*/ CLR_OSD_WIN_REG_WIN6_CA_DUP_MODE_TX() \
	msWriteByteMask( 0x1DC0, 0x0, 0x08 );
#define /*REG_1DC0[3:3];h0060[3:3]=h0*/ ASG_OSD_WIN_REG_WIN6_CA_DUP_MODE_TX( V ) \
	msWriteByteMask( 0x1DC0, ( 0 != (V) )? 0x08: 0, 0x08 );
/*
window duplicate ca base address for text*/
#define /*REG_1DC0[6:4];h0060[6:4]=h0*/ GET_OSD_WIN_REG_WIN6_OUT_A_SEL() \
	( ( msReadByte( 0x1DC0 ) & 0x70 ) >>  4 )
#define /*REG_1DC0[6:4];h0060[6:4]=h0*/ SET_OSD_WIN_REG_WIN6_OUT_A_SEL( V ) \
	msWriteByteMask( 0x1DC0, ((V) <<  4), 0x70 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_out*/
#define /*REG_1DC0[7:7];h0060[7:7]=h0*/ GET_OSD_WIN_REG_WIN6_TX_EN() \
	( 0 != ( msReadByte( 0x1DC0 ) & 0x80 ) )
#define /*REG_1DC0[7:7];h0060[7:7]=h0*/ SET_OSD_WIN_REG_WIN6_TX_EN() \
	msWriteByteMask( 0x1DC0, 0xFF, 0x80 );
#define /*REG_1DC0[7:7];h0060[7:7]=h0*/ CLR_OSD_WIN_REG_WIN6_TX_EN() \
	msWriteByteMask( 0x1DC0, 0x0, 0x80 );
#define /*REG_1DC0[7:7];h0060[7:7]=h0*/ ASG_OSD_WIN_REG_WIN6_TX_EN( V ) \
	msWriteByteMask( 0x1DC0, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
OSD Window display.
0: window font only.
1: window turn on font and text.*/
#define /*REG_1DC1[2:0];h0060[10:8]=h0*/ GET_OSD_WIN_REG_WIN6_LV1_A_SEL() \
	( msReadByte( 0x1DC1 ) & 0x07 )
#define /*REG_1DC1[2:0];h0060[10:8]=h0*/ SET_OSD_WIN_REG_WIN6_LV1_A_SEL( V ) \
	msWriteByteMask( 0x1DC1, (V), 0x07 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_lv1*/
#define /*REG_1DC1[6:4];h0060[14:12]=h0*/ GET_OSD_WIN_REG_WIN6_LV2_A_SEL() \
	( ( msReadByte( 0x1DC1 ) & 0x70 ) >>  4 )
#define /*REG_1DC1[6:4];h0060[14:12]=h0*/ SET_OSD_WIN_REG_WIN6_LV2_A_SEL( V ) \
	msWriteByteMask( 0x1DC1, ((V) <<  4), 0x70 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_lv1*/
#define /*REG_1DC2[4:0];h0061[4:0]=h11*/ GET_OSD_WIN_REG_WIN6_CHARHIGH() \
	( msReadByte( 0x1DC2 ) & 0x1F )
#define /*REG_1DC2[4:0];h0061[4:0]=h11*/ SET_OSD_WIN_REG_WIN6_CHARHIGH( V ) \
	msWriteByteMask( 0x1DC2, (V), 0x1F );
/*
OSD font height (unit : line) .*/
#define /*REG_1DC3[5:5];h0061[13:13]=h0*/ GET_OSD_WIN_REG_WIN6_44MODE_TRS_EN_TX() \
	( 0 != ( msReadByte( 0x1DC3 ) & 0x20 ) )
#define /*REG_1DC3[5:5];h0061[13:13]=h0*/ SET_OSD_WIN_REG_WIN6_44MODE_TRS_EN_TX() \
	msWriteByteMask( 0x1DC3, 0xFF, 0x20 );
#define /*REG_1DC3[5:5];h0061[13:13]=h0*/ CLR_OSD_WIN_REG_WIN6_44MODE_TRS_EN_TX() \
	msWriteByteMask( 0x1DC3, 0x0, 0x20 );
#define /*REG_1DC3[5:5];h0061[13:13]=h0*/ ASG_OSD_WIN_REG_WIN6_44MODE_TRS_EN_TX( V ) \
	msWriteByteMask( 0x1DC3, ( 0 != (V) )? 0x20: 0, 0x20 );
/*
enable window 44 mode transparent for text*/
#define /*REG_1DC3[6:6];h0061[14:14]=h0*/ GET_OSD_WIN_REG_WIN6_44MODE_TRS_EN() \
	( 0 != ( msReadByte( 0x1DC3 ) & 0x40 ) )
#define /*REG_1DC3[6:6];h0061[14:14]=h0*/ SET_OSD_WIN_REG_WIN6_44MODE_TRS_EN() \
	msWriteByteMask( 0x1DC3, 0xFF, 0x40 );
#define /*REG_1DC3[6:6];h0061[14:14]=h0*/ CLR_OSD_WIN_REG_WIN6_44MODE_TRS_EN() \
	msWriteByteMask( 0x1DC3, 0x0, 0x40 );
#define /*REG_1DC3[6:6];h0061[14:14]=h0*/ ASG_OSD_WIN_REG_WIN6_44MODE_TRS_EN( V ) \
	msWriteByteMask( 0x1DC3, ( 0 != (V) )? 0x40: 0, 0x40 );
/*
enable window 44 mode transparent*/
#define /*REG_1DC3[7:7];h0061[15:15]=h0*/ GET_OSD_WIN_REG_WIN6_1BP_44MODE() \
	( 0 != ( msReadByte( 0x1DC3 ) & 0x80 ) )
#define /*REG_1DC3[7:7];h0061[15:15]=h0*/ SET_OSD_WIN_REG_WIN6_1BP_44MODE() \
	msWriteByteMask( 0x1DC3, 0xFF, 0x80 );
#define /*REG_1DC3[7:7];h0061[15:15]=h0*/ CLR_OSD_WIN_REG_WIN6_1BP_44MODE() \
	msWriteByteMask( 0x1DC3, 0x0, 0x80 );
#define /*REG_1DC3[7:7];h0061[15:15]=h0*/ ASG_OSD_WIN_REG_WIN6_1BP_44MODE( V ) \
	msWriteByteMask( 0x1DC3, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
OSD 1bpp use atribute [7:4] or [3:0] mode*/
#define /*REG_1DC4[11:0];h0062[11:0]=h0*/ GET_OSD_WIN_REG_WIN6_HSTR_PIX() \
	( msReadByte( 0x1DC4 ) | ( (msReadByte( 0x1DC5 ) & 0x0F) <<  8 ) )
#define /*REG_1DC4[11:0];h0062[11:0]=h0*/ SET_OSD_WIN_REG_WIN6_HSTR_PIX( V ) \
	{ msWriteByte( 0x1DC4, (V) ); msWriteByteMask( 0x1DC5, ((V) >>  8), 0x0F ); }
/*
OSD window Hori7ontal start positions (pixel)*/
#define /*REG_1DC6[11:0];h0063[11:0]=h0*/ GET_OSD_WIN_REG_WIN6_VSTR_PIX() \
	( msReadByte( 0x1DC6 ) | ( (msReadByte( 0x1DC7 ) & 0x0F) <<  8 ) )
#define /*REG_1DC6[11:0];h0063[11:0]=h0*/ SET_OSD_WIN_REG_WIN6_VSTR_PIX( V ) \
	{ msWriteByte( 0x1DC6, (V) ); msWriteByteMask( 0x1DC7, ((V) >>  8), 0x0F ); }
/*
OSD window Vertical start positions (pixel)*/
#define /*REG_1DC8[11:0];h0064[11:0]=h0*/ GET_OSD_WIN_REG_WIN6_HEND_PIX() \
	( msReadByte( 0x1DC8 ) | ( (msReadByte( 0x1DC9 ) & 0x0F) <<  8 ) )
#define /*REG_1DC8[11:0];h0064[11:0]=h0*/ SET_OSD_WIN_REG_WIN6_HEND_PIX( V ) \
	{ msWriteByte( 0x1DC8, (V) ); msWriteByteMask( 0x1DC9, ((V) >>  8), 0x0F ); }
/*
OSD window Hori7ontal end positions (pixel)*/
#define /*REG_1DC9[7:6];h0064[15:14]=h0*/ GET_OSD_WIN_REG_WIN6_HDUP() \
	( ( msReadByte( 0x1DC9 ) & 0xC0 ) >>  6 )
#define /*REG_1DC9[7:6];h0064[15:14]=h0*/ SET_OSD_WIN_REG_WIN6_HDUP( V ) \
	msWriteByteMask( 0x1DC9, ((V) <<  6), 0xC0 );
/*
window vertical duplicate ratio
0: 1x
1: 2x
2: 3x
3: 4x*/
#define /*REG_1DCA[11:0];h0065[11:0]=h0*/ GET_OSD_WIN_REG_WIN6_VEND_PIX() \
	( msReadByte( 0x1DCA ) | ( (msReadByte( 0x1DCB ) & 0x0F) <<  8 ) )
#define /*REG_1DCA[11:0];h0065[11:0]=h0*/ SET_OSD_WIN_REG_WIN6_VEND_PIX( V ) \
	{ msWriteByte( 0x1DCA, (V) ); msWriteByteMask( 0x1DCB, ((V) >>  8), 0x0F ); }
/*
OSD window Vertical end positions (pixel)*/
#define /*REG_1DCB[7:6];h0065[15:14]=h0*/ GET_OSD_WIN_REG_WIN6_VDUP() \
	( ( msReadByte( 0x1DCB ) & 0xC0 ) >>  6 )
#define /*REG_1DCB[7:6];h0065[15:14]=h0*/ SET_OSD_WIN_REG_WIN6_VDUP( V ) \
	msWriteByteMask( 0x1DCB, ((V) <<  6), 0xC0 );
/*
window vertical duplicate ratio
0: 1x
1: 2x
2: 3x
3: 4x*/
#define /*REG_1DCC[5:0];h0066[5:0]=h0*/ GET_OSD_WIN_REG_WIN6_FIX_ALPHA_OUT() \
	( msReadByte( 0x1DCC ) & 0x3F )
#define /*REG_1DCC[5:0];h0066[5:0]=h0*/ SET_OSD_WIN_REG_WIN6_FIX_ALPHA_OUT( V ) \
	msWriteByteMask( 0x1DCC, (V), 0x3F );
/*
OSD fix_alpha for output*/
#define /*REG_1DCD[5:0];h0066[13:8]=h0*/ GET_OSD_WIN_REG_WIN6_FIX_ALPHA_LV1() \
	( msReadByte( 0x1DCD ) & 0x3F )
#define /*REG_1DCD[5:0];h0066[13:8]=h0*/ SET_OSD_WIN_REG_WIN6_FIX_ALPHA_LV1( V ) \
	msWriteByteMask( 0x1DCD, (V), 0x3F );
/*
OSD fix_alpha for lv1*/
#define /*REG_1DCE[4:0];h0067[4:0]=h0*/ GET_OSD_WIN_REG_WIN6_SHIFT_PIX_X() \
	( msReadByte( 0x1DCE ) & 0x1F )
#define /*REG_1DCE[4:0];h0067[4:0]=h0*/ SET_OSD_WIN_REG_WIN6_SHIFT_PIX_X( V ) \
	msWriteByteMask( 0x1DCE, (V), 0x1F );
/*
OSD Font Shift Select by x pixel.*/
#define /*REG_1DCF[4:0];h0067[12:8]=h0*/ GET_OSD_WIN_REG_WIN6_SHIFT_PIX_Y() \
	( msReadByte( 0x1DCF ) & 0x1F )
#define /*REG_1DCF[4:0];h0067[12:8]=h0*/ SET_OSD_WIN_REG_WIN6_SHIFT_PIX_Y( V ) \
	msWriteByteMask( 0x1DCF, (V), 0x1F );
/*
OSD Font Shift Select by y pixel (unit : 1line).*/
#define /*REG_1DD0[13:0];h0068[13:0]=h0*/ GET_OSD_WIN_REG_WIN6_BASE() \
	( msReadByte( 0x1DD0 ) | ( (msReadByte( 0x1DD1 ) & 0x3F) <<  8 ) )
#define /*REG_1DD0[13:0];h0068[13:0]=h0*/ SET_OSD_WIN_REG_WIN6_BASE( V ) \
	{ msWriteByte( 0x1DD0, (V) ); msWriteByteMask( 0x1DD1, ((V) >>  8), 0x3F ); }
/*
OSD code-attribute Base Address.
[13:2] for sram entry, [1:0] for low(0) ~ high(3)  18 bits*/
#define /*REG_1DD2[7:0];h0069[7:0]=h0*/ GET_OSD_WIN_REG_WIN6_LINE_OFFSET() \
	( msReadByte( 0x1DD2 ) )
#define /*REG_1DD2[7:0];h0069[7:0]=h0*/ SET_OSD_WIN_REG_WIN6_LINE_OFFSET( V ) \
	msWriteByte( 0x1DD2, (V) );
/*
OSD code buffer line offset value( unit : 1ca (or 1/4 entry)).*/
#define /*REG_1DD3[7:0];h0069[15:8]=h0*/ GET_OSD_WIN_REG_WIN6_LINE_OFFSET_TX() \
	( msReadByte( 0x1DD3 ) )
#define /*REG_1DD3[7:0];h0069[15:8]=h0*/ SET_OSD_WIN_REG_WIN6_LINE_OFFSET_TX( V ) \
	msWriteByte( 0x1DD3, (V) );
/*
OSD code buffer line offset value for text
( unit : 1ca (or 1/4 entry)).*/
#define /*REG_1DD4[2:0];h006a[2:0]=h0*/ GET_OSD_WIN_REG_WIN6_CLR_R_SEL() \
	( msReadByte( 0x1DD4 ) & 0x07 )
#define /*REG_1DD4[2:0];h006a[2:0]=h0*/ SET_OSD_WIN_REG_WIN6_CLR_R_SEL( V ) \
	msWriteByteMask( 0x1DD4, (V), 0x07 );
/*
grading color R select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr r */
#define /*REG_1DD4[6:4];h006a[6:4]=h0*/ GET_OSD_WIN_REG_WIN6_CLR_G_SEL() \
	( ( msReadByte( 0x1DD4 ) & 0x70 ) >>  4 )
#define /*REG_1DD4[6:4];h006a[6:4]=h0*/ SET_OSD_WIN_REG_WIN6_CLR_G_SEL( V ) \
	msWriteByteMask( 0x1DD4, ((V) <<  4), 0x70 );
/*
grading color G select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr g*/
#define /*REG_1DD5[2:0];h006a[10:8]=h0*/ GET_OSD_WIN_REG_WIN6_CLR_B_SEL() \
	( msReadByte( 0x1DD5 ) & 0x07 )
#define /*REG_1DD5[2:0];h006a[10:8]=h0*/ SET_OSD_WIN_REG_WIN6_CLR_B_SEL( V ) \
	msWriteByteMask( 0x1DD5, (V), 0x07 );
/*
grading color B select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr b*/
#define /*REG_1DD5[4:4];h006a[12:12]=h0*/ GET_OSD_WIN_REG_WIN6_TRANS_INV() \
	( 0 != ( msReadByte( 0x1DD5 ) & 0x10 ) )
#define /*REG_1DD5[4:4];h006a[12:12]=h0*/ SET_OSD_WIN_REG_WIN6_TRANS_INV() \
	msWriteByteMask( 0x1DD5, 0xFF, 0x10 );
#define /*REG_1DD5[4:4];h006a[12:12]=h0*/ CLR_OSD_WIN_REG_WIN6_TRANS_INV() \
	msWriteByteMask( 0x1DD5, 0x0, 0x10 );
#define /*REG_1DD5[4:4];h006a[12:12]=h0*/ ASG_OSD_WIN_REG_WIN6_TRANS_INV( V ) \
	msWriteByteMask( 0x1DD5, ( 0 != (V) )? 0x10: 0, 0x10 );
/*
inverse transparent define*/
#define /*REG_1DD5[5:5];h006a[13:13]=h0*/ GET_OSD_WIN_REG_WIN6_CKEY_INV() \
	( 0 != ( msReadByte( 0x1DD5 ) & 0x20 ) )
#define /*REG_1DD5[5:5];h006a[13:13]=h0*/ SET_OSD_WIN_REG_WIN6_CKEY_INV() \
	msWriteByteMask( 0x1DD5, 0xFF, 0x20 );
#define /*REG_1DD5[5:5];h006a[13:13]=h0*/ CLR_OSD_WIN_REG_WIN6_CKEY_INV() \
	msWriteByteMask( 0x1DD5, 0x0, 0x20 );
#define /*REG_1DD5[5:5];h006a[13:13]=h0*/ ASG_OSD_WIN_REG_WIN6_CKEY_INV( V ) \
	msWriteByteMask( 0x1DD5, ( 0 != (V) )? 0x20: 0, 0x20 );
/*
inverse color key define*/
#define /*REG_1DD5[6:6];h006a[14:14]=h0*/ GET_OSD_WIN_REG_WIN6_FIX_ATRB_EN_TX() \
	( 0 != ( msReadByte( 0x1DD5 ) & 0x40 ) )
#define /*REG_1DD5[6:6];h006a[14:14]=h0*/ SET_OSD_WIN_REG_WIN6_FIX_ATRB_EN_TX() \
	msWriteByteMask( 0x1DD5, 0xFF, 0x40 );
#define /*REG_1DD5[6:6];h006a[14:14]=h0*/ CLR_OSD_WIN_REG_WIN6_FIX_ATRB_EN_TX() \
	msWriteByteMask( 0x1DD5, 0x0, 0x40 );
#define /*REG_1DD5[6:6];h006a[14:14]=h0*/ ASG_OSD_WIN_REG_WIN6_FIX_ATRB_EN_TX( V ) \
	msWriteByteMask( 0x1DD5, ( 0 != (V) )? 0x40: 0, 0x40 );
/*
enable uniform window attribute mode for text*/
#define /*REG_1DD5[7:7];h006a[15:15]=h0*/ GET_OSD_WIN_REG_WIN6_FIX_ATRB_EN() \
	( 0 != ( msReadByte( 0x1DD5 ) & 0x80 ) )
#define /*REG_1DD5[7:7];h006a[15:15]=h0*/ SET_OSD_WIN_REG_WIN6_FIX_ATRB_EN() \
	msWriteByteMask( 0x1DD5, 0xFF, 0x80 );
#define /*REG_1DD5[7:7];h006a[15:15]=h0*/ CLR_OSD_WIN_REG_WIN6_FIX_ATRB_EN() \
	msWriteByteMask( 0x1DD5, 0x0, 0x80 );
#define /*REG_1DD5[7:7];h006a[15:15]=h0*/ ASG_OSD_WIN_REG_WIN6_FIX_ATRB_EN( V ) \
	msWriteByteMask( 0x1DD5, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
enable uniform window attribute mode*/
#define /*REG_1DD6[7:0];h006b[7:0]=h0*/ GET_OSD_WIN_REG_WIN6_FIX_CLR_R() \
	( msReadByte( 0x1DD6 ) )
#define /*REG_1DD6[7:0];h006b[7:0]=h0*/ SET_OSD_WIN_REG_WIN6_FIX_CLR_R( V ) \
	msWriteByte( 0x1DD6, (V) );
/*
for lv2 blending : fix grading color R*/
#define /*REG_1DD7[7:0];h006b[15:8]=h0*/ GET_OSD_WIN_REG_WIN6_FIX_CLR_G() \
	( msReadByte( 0x1DD7 ) )
#define /*REG_1DD7[7:0];h006b[15:8]=h0*/ SET_OSD_WIN_REG_WIN6_FIX_CLR_G( V ) \
	msWriteByte( 0x1DD7, (V) );
/*
for lv2 blending : fix grading color G*/
#define /*REG_1DD8[7:0];h006c[7:0]=h0*/ GET_OSD_WIN_REG_WIN6_FIX_CLR_B() \
	( msReadByte( 0x1DD8 ) )
#define /*REG_1DD8[7:0];h006c[7:0]=h0*/ SET_OSD_WIN_REG_WIN6_FIX_CLR_B( V ) \
	msWriteByte( 0x1DD8, (V) );
/*
for lv2 blending : fix grading color B*/
#define /*REG_1DD9[5:0];h006c[13:8]=h0*/ GET_OSD_WIN_REG_WIN6_FIX_ALPHA_LV2() \
	( msReadByte( 0x1DD9 ) & 0x3F )
#define /*REG_1DD9[5:0];h006c[13:8]=h0*/ SET_OSD_WIN_REG_WIN6_FIX_ALPHA_LV2( V ) \
	msWriteByteMask( 0x1DD9, (V), 0x3F );
/*
for lv2 blending : fix alpha level 2*/
#define /*REG_1DDA[7:0];h006d[7:0]=h0*/ GET_OSD_WIN_REG_WIN6_FIX_ATRB() \
	( msReadByte( 0x1DDA ) )
#define /*REG_1DDA[7:0];h006d[7:0]=h0*/ SET_OSD_WIN_REG_WIN6_FIX_ATRB( V ) \
	msWriteByte( 0x1DDA, (V) );
/*
uniform window attribute*/
#define /*REG_1DDB[7:0];h006d[15:8]=h0*/ GET_OSD_WIN_REG_WIN6_FIX_ATRB_TX() \
	( msReadByte( 0x1DDB ) )
#define /*REG_1DDB[7:0];h006d[15:8]=h0*/ SET_OSD_WIN_REG_WIN6_FIX_ATRB_TX( V ) \
	msWriteByte( 0x1DDB, (V) );
/*
uniform window attribute for text*/
#define /*REG_1DDC[3:0];h006e[3:0]=h0*/ GET_OSD_WIN_REG_WIN6_MONO_PREFIX() \
	( msReadByte( 0x1DDC ) & 0x0F )
#define /*REG_1DDC[3:0];h006e[3:0]=h0*/ SET_OSD_WIN_REG_WIN6_MONO_PREFIX( V ) \
	msWriteByteMask( 0x1DDC, (V), 0x0F );
/*
register for Mono font prefix atrribute*/
#define /*REG_1DDC[7:4];h006e[7:4]=h0*/ GET_OSD_WIN_REG_WIN6_MONO_PREFIX_TX() \
	( ( msReadByte( 0x1DDC ) & 0xF0 ) >>  4 )
#define /*REG_1DDC[7:4];h006e[7:4]=h0*/ SET_OSD_WIN_REG_WIN6_MONO_PREFIX_TX( V ) \
	msWriteByteMask( 0x1DDC, ((V) <<  4), 0xF0 );
/*
register for Mono font prefix atrribute for text*/
#define /*REG_1DDD[7:0];h006e[15:8]=hf0*/ GET_OSD_WIN_REG_WIN6_DUMMY() \
	( msReadByte( 0x1DDD ) )
#define /*REG_1DDD[7:0];h006e[15:8]=hf0*/ SET_OSD_WIN_REG_WIN6_DUMMY( V ) \
	msWriteByte( 0x1DDD, (V) );
/*
dummy_register_win6*/
#define /*REG_1DDE[13:0];h006f[13:0]=h0*/ GET_OSD_WIN_REG_WIN6_BASE_TX() \
	( msReadByte( 0x1DDE ) | ( (msReadByte( 0x1DDF ) & 0x3F) <<  8 ) )
#define /*REG_1DDE[13:0];h006f[13:0]=h0*/ SET_OSD_WIN_REG_WIN6_BASE_TX( V ) \
	{ msWriteByte( 0x1DDE, (V) ); msWriteByteMask( 0x1DDF, ((V) >>  8), 0x3F ); }
/*
OSD code-attribute Base Address. Fot text
[13:2] for sram entry, [1:0] for low(0) ~ high(3)  18 bits*/
#define /*REG_1DE0[0:0];h0070[0:0]=h0*/ GET_OSD_WIN_REG_WIN7_EN() \
	( 0 != ( msReadByte( 0x1DE0 ) & 0x01 ) )
#define /*REG_1DE0[0:0];h0070[0:0]=h0*/ SET_OSD_WIN_REG_WIN7_EN() \
	msWriteByteMask( 0x1DE0, 0xFF, 0x01 );
#define /*REG_1DE0[0:0];h0070[0:0]=h0*/ CLR_OSD_WIN_REG_WIN7_EN() \
	msWriteByteMask( 0x1DE0, 0x0, 0x01 );
#define /*REG_1DE0[0:0];h0070[0:0]=h0*/ ASG_OSD_WIN_REG_WIN7_EN( V ) \
	msWriteByteMask( 0x1DE0, ( 0 != (V) )? 0x01: 0, 0x01 );
/*
OSD Window display.
0: window off.
1: window on.*/
#define /*REG_1DE0[1:1];h0070[1:1]=h0*/ GET_OSD_WIN_REG_WIN7_CA_DUP_MODE() \
	( 0 != ( msReadByte( 0x1DE0 ) & 0x02 ) )
#define /*REG_1DE0[1:1];h0070[1:1]=h0*/ SET_OSD_WIN_REG_WIN7_CA_DUP_MODE() \
	msWriteByteMask( 0x1DE0, 0xFF, 0x02 );
#define /*REG_1DE0[1:1];h0070[1:1]=h0*/ CLR_OSD_WIN_REG_WIN7_CA_DUP_MODE() \
	msWriteByteMask( 0x1DE0, 0x0, 0x02 );
#define /*REG_1DE0[1:1];h0070[1:1]=h0*/ ASG_OSD_WIN_REG_WIN7_CA_DUP_MODE( V ) \
	msWriteByteMask( 0x1DE0, ( 0 != (V) )? 0x02: 0, 0x02 );
/*
window duplicate ca base address*/
#define /*REG_1DE0[2:2];h0070[2:2]=h0*/ GET_OSD_WIN_REG_WIN7_FP_MODE() \
	( 0 != ( msReadByte( 0x1DE0 ) & 0x04 ) )
#define /*REG_1DE0[2:2];h0070[2:2]=h0*/ SET_OSD_WIN_REG_WIN7_FP_MODE() \
	msWriteByteMask( 0x1DE0, 0xFF, 0x04 );
#define /*REG_1DE0[2:2];h0070[2:2]=h0*/ CLR_OSD_WIN_REG_WIN7_FP_MODE() \
	msWriteByteMask( 0x1DE0, 0x0, 0x04 );
#define /*REG_1DE0[2:2];h0070[2:2]=h0*/ ASG_OSD_WIN_REG_WIN7_FP_MODE( V ) \
	msWriteByteMask( 0x1DE0, ( 0 != (V) )? 0x04: 0, 0x04 );
/*
0: window use "font + text + PG" combination
1: window use "font + PG" combination*/
#define /*REG_1DE0[3:3];h0070[3:3]=h0*/ GET_OSD_WIN_REG_WIN7_CA_DUP_MODE_TX() \
	( 0 != ( msReadByte( 0x1DE0 ) & 0x08 ) )
#define /*REG_1DE0[3:3];h0070[3:3]=h0*/ SET_OSD_WIN_REG_WIN7_CA_DUP_MODE_TX() \
	msWriteByteMask( 0x1DE0, 0xFF, 0x08 );
#define /*REG_1DE0[3:3];h0070[3:3]=h0*/ CLR_OSD_WIN_REG_WIN7_CA_DUP_MODE_TX() \
	msWriteByteMask( 0x1DE0, 0x0, 0x08 );
#define /*REG_1DE0[3:3];h0070[3:3]=h0*/ ASG_OSD_WIN_REG_WIN7_CA_DUP_MODE_TX( V ) \
	msWriteByteMask( 0x1DE0, ( 0 != (V) )? 0x08: 0, 0x08 );
/*
window duplicate ca base address for text*/
#define /*REG_1DE0[6:4];h0070[6:4]=h0*/ GET_OSD_WIN_REG_WIN7_OUT_A_SEL() \
	( ( msReadByte( 0x1DE0 ) & 0x70 ) >>  4 )
#define /*REG_1DE0[6:4];h0070[6:4]=h0*/ SET_OSD_WIN_REG_WIN7_OUT_A_SEL( V ) \
	msWriteByteMask( 0x1DE0, ((V) <<  4), 0x70 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_out*/
#define /*REG_1DE0[7:7];h0070[7:7]=h0*/ GET_OSD_WIN_REG_WIN7_TX_EN() \
	( 0 != ( msReadByte( 0x1DE0 ) & 0x80 ) )
#define /*REG_1DE0[7:7];h0070[7:7]=h0*/ SET_OSD_WIN_REG_WIN7_TX_EN() \
	msWriteByteMask( 0x1DE0, 0xFF, 0x80 );
#define /*REG_1DE0[7:7];h0070[7:7]=h0*/ CLR_OSD_WIN_REG_WIN7_TX_EN() \
	msWriteByteMask( 0x1DE0, 0x0, 0x80 );
#define /*REG_1DE0[7:7];h0070[7:7]=h0*/ ASG_OSD_WIN_REG_WIN7_TX_EN( V ) \
	msWriteByteMask( 0x1DE0, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
OSD Window display.
0: window font only.
1: window turn on font and text.*/
#define /*REG_1DE1[2:0];h0070[10:8]=h0*/ GET_OSD_WIN_REG_WIN7_LV1_A_SEL() \
	( msReadByte( 0x1DE1 ) & 0x07 )
#define /*REG_1DE1[2:0];h0070[10:8]=h0*/ SET_OSD_WIN_REG_WIN7_LV1_A_SEL( V ) \
	msWriteByteMask( 0x1DE1, (V), 0x07 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_lv1*/
#define /*REG_1DE1[6:4];h0070[14:12]=h0*/ GET_OSD_WIN_REG_WIN7_LV2_A_SEL() \
	( ( msReadByte( 0x1DE1 ) & 0x70 ) >>  4 )
#define /*REG_1DE1[6:4];h0070[14:12]=h0*/ SET_OSD_WIN_REG_WIN7_LV2_A_SEL( V ) \
	msWriteByteMask( 0x1DE1, ((V) <<  4), 0x70 );
/*
OSD  alpha_source select
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: reg_fix_alpha_lv1*/
#define /*REG_1DE2[4:0];h0071[4:0]=h11*/ GET_OSD_WIN_REG_WIN7_CHARHIGH() \
	( msReadByte( 0x1DE2 ) & 0x1F )
#define /*REG_1DE2[4:0];h0071[4:0]=h11*/ SET_OSD_WIN_REG_WIN7_CHARHIGH( V ) \
	msWriteByteMask( 0x1DE2, (V), 0x1F );
/*
OSD font height (unit : line) .*/
#define /*REG_1DE3[5:5];h0071[13:13]=h0*/ GET_OSD_WIN_REG_WIN7_44MODE_TRS_EN_TX() \
	( 0 != ( msReadByte( 0x1DE3 ) & 0x20 ) )
#define /*REG_1DE3[5:5];h0071[13:13]=h0*/ SET_OSD_WIN_REG_WIN7_44MODE_TRS_EN_TX() \
	msWriteByteMask( 0x1DE3, 0xFF, 0x20 );
#define /*REG_1DE3[5:5];h0071[13:13]=h0*/ CLR_OSD_WIN_REG_WIN7_44MODE_TRS_EN_TX() \
	msWriteByteMask( 0x1DE3, 0x0, 0x20 );
#define /*REG_1DE3[5:5];h0071[13:13]=h0*/ ASG_OSD_WIN_REG_WIN7_44MODE_TRS_EN_TX( V ) \
	msWriteByteMask( 0x1DE3, ( 0 != (V) )? 0x20: 0, 0x20 );
/*
enable window 44 mode transparent for text*/
#define /*REG_1DE3[6:6];h0071[14:14]=h0*/ GET_OSD_WIN_REG_WIN7_44MODE_TRS_EN() \
	( 0 != ( msReadByte( 0x1DE3 ) & 0x40 ) )
#define /*REG_1DE3[6:6];h0071[14:14]=h0*/ SET_OSD_WIN_REG_WIN7_44MODE_TRS_EN() \
	msWriteByteMask( 0x1DE3, 0xFF, 0x40 );
#define /*REG_1DE3[6:6];h0071[14:14]=h0*/ CLR_OSD_WIN_REG_WIN7_44MODE_TRS_EN() \
	msWriteByteMask( 0x1DE3, 0x0, 0x40 );
#define /*REG_1DE3[6:6];h0071[14:14]=h0*/ ASG_OSD_WIN_REG_WIN7_44MODE_TRS_EN( V ) \
	msWriteByteMask( 0x1DE3, ( 0 != (V) )? 0x40: 0, 0x40 );
/*
enable window 44 mode transparent*/
#define /*REG_1DE3[7:7];h0071[15:15]=h0*/ GET_OSD_WIN_REG_WIN7_1BP_44MODE() \
	( 0 != ( msReadByte( 0x1DE3 ) & 0x80 ) )
#define /*REG_1DE3[7:7];h0071[15:15]=h0*/ SET_OSD_WIN_REG_WIN7_1BP_44MODE() \
	msWriteByteMask( 0x1DE3, 0xFF, 0x80 );
#define /*REG_1DE3[7:7];h0071[15:15]=h0*/ CLR_OSD_WIN_REG_WIN7_1BP_44MODE() \
	msWriteByteMask( 0x1DE3, 0x0, 0x80 );
#define /*REG_1DE3[7:7];h0071[15:15]=h0*/ ASG_OSD_WIN_REG_WIN7_1BP_44MODE( V ) \
	msWriteByteMask( 0x1DE3, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
OSD 1bpp use atribute [7:4] or [3:0] mode*/
#define /*REG_1DE4[11:0];h0072[11:0]=h0*/ GET_OSD_WIN_REG_WIN7_HSTR_PIX() \
	( msReadByte( 0x1DE4 ) | ( (msReadByte( 0x1DE5 ) & 0x0F) <<  8 ) )
#define /*REG_1DE4[11:0];h0072[11:0]=h0*/ SET_OSD_WIN_REG_WIN7_HSTR_PIX( V ) \
	{ msWriteByte( 0x1DE4, (V) ); msWriteByteMask( 0x1DE5, ((V) >>  8), 0x0F ); }
/*
OSD window Hori7ontal start positions (pixel)*/
#define /*REG_1DE6[11:0];h0073[11:0]=h0*/ GET_OSD_WIN_REG_WIN7_VSTR_PIX() \
	( msReadByte( 0x1DE6 ) | ( (msReadByte( 0x1DE7 ) & 0x0F) <<  8 ) )
#define /*REG_1DE6[11:0];h0073[11:0]=h0*/ SET_OSD_WIN_REG_WIN7_VSTR_PIX( V ) \
	{ msWriteByte( 0x1DE6, (V) ); msWriteByteMask( 0x1DE7, ((V) >>  8), 0x0F ); }
/*
OSD window Vertical start positions (pixel)*/
#define /*REG_1DE8[11:0];h0074[11:0]=h0*/ GET_OSD_WIN_REG_WIN7_HEND_PIX() \
	( msReadByte( 0x1DE8 ) | ( (msReadByte( 0x1DE9 ) & 0x0F) <<  8 ) )
#define /*REG_1DE8[11:0];h0074[11:0]=h0*/ SET_OSD_WIN_REG_WIN7_HEND_PIX( V ) \
	{ msWriteByte( 0x1DE8, (V) ); msWriteByteMask( 0x1DE9, ((V) >>  8), 0x0F ); }
/*
OSD window Hori7ontal end positions (pixel)*/
#define /*REG_1DE9[7:6];h0074[15:14]=h0*/ GET_OSD_WIN_REG_WIN7_HDUP() \
	( ( msReadByte( 0x1DE9 ) & 0xC0 ) >>  6 )
#define /*REG_1DE9[7:6];h0074[15:14]=h0*/ SET_OSD_WIN_REG_WIN7_HDUP( V ) \
	msWriteByteMask( 0x1DE9, ((V) <<  6), 0xC0 );
/*
window vertical duplicate ratio
0: 1x
1: 2x
2: 3x
3: 4x*/
#define /*REG_1DEA[11:0];h0075[11:0]=h0*/ GET_OSD_WIN_REG_WIN7_VEND_PIX() \
	( msReadByte( 0x1DEA ) | ( (msReadByte( 0x1DEB ) & 0x0F) <<  8 ) )
#define /*REG_1DEA[11:0];h0075[11:0]=h0*/ SET_OSD_WIN_REG_WIN7_VEND_PIX( V ) \
	{ msWriteByte( 0x1DEA, (V) ); msWriteByteMask( 0x1DEB, ((V) >>  8), 0x0F ); }
/*
OSD window Vertical end positions (pixel)*/
#define /*REG_1DEB[7:6];h0075[15:14]=h0*/ GET_OSD_WIN_REG_WIN7_VDUP() \
	( ( msReadByte( 0x1DEB ) & 0xC0 ) >>  6 )
#define /*REG_1DEB[7:6];h0075[15:14]=h0*/ SET_OSD_WIN_REG_WIN7_VDUP( V ) \
	msWriteByteMask( 0x1DEB, ((V) <<  6), 0xC0 );
/*
window vertical duplicate ratio
0: 1x
1: 2x
2: 3x
3: 4x*/
#define /*REG_1DEC[5:0];h0076[5:0]=h0*/ GET_OSD_WIN_REG_WIN7_FIX_ALPHA_OUT() \
	( msReadByte( 0x1DEC ) & 0x3F )
#define /*REG_1DEC[5:0];h0076[5:0]=h0*/ SET_OSD_WIN_REG_WIN7_FIX_ALPHA_OUT( V ) \
	msWriteByteMask( 0x1DEC, (V), 0x3F );
/*
OSD fix_alpha for output*/
#define /*REG_1DED[5:0];h0076[13:8]=h0*/ GET_OSD_WIN_REG_WIN7_FIX_ALPHA_LV1() \
	( msReadByte( 0x1DED ) & 0x3F )
#define /*REG_1DED[5:0];h0076[13:8]=h0*/ SET_OSD_WIN_REG_WIN7_FIX_ALPHA_LV1( V ) \
	msWriteByteMask( 0x1DED, (V), 0x3F );
/*
OSD fix_alpha for lv1*/
#define /*REG_1DEE[4:0];h0077[4:0]=h0*/ GET_OSD_WIN_REG_WIN7_SHIFT_PIX_X() \
	( msReadByte( 0x1DEE ) & 0x1F )
#define /*REG_1DEE[4:0];h0077[4:0]=h0*/ SET_OSD_WIN_REG_WIN7_SHIFT_PIX_X( V ) \
	msWriteByteMask( 0x1DEE, (V), 0x1F );
/*
OSD Font Shift Select by x pixel.*/
#define /*REG_1DEF[4:0];h0077[12:8]=h0*/ GET_OSD_WIN_REG_WIN7_SHIFT_PIX_Y() \
	( msReadByte( 0x1DEF ) & 0x1F )
#define /*REG_1DEF[4:0];h0077[12:8]=h0*/ SET_OSD_WIN_REG_WIN7_SHIFT_PIX_Y( V ) \
	msWriteByteMask( 0x1DEF, (V), 0x1F );
/*
OSD Font Shift Select by y pixel (unit : 1line).*/
#define /*REG_1DF0[13:0];h0078[13:0]=h0*/ GET_OSD_WIN_REG_WIN7_BASE() \
	( msReadByte( 0x1DF0 ) | ( (msReadByte( 0x1DF1 ) & 0x3F) <<  8 ) )
#define /*REG_1DF0[13:0];h0078[13:0]=h0*/ SET_OSD_WIN_REG_WIN7_BASE( V ) \
	{ msWriteByte( 0x1DF0, (V) ); msWriteByteMask( 0x1DF1, ((V) >>  8), 0x3F ); }
/*
OSD code-attribute Base Address.
[13:2] for sram entry, [1:0] for low(0) ~ high(3)  18 bits*/
#define /*REG_1DF2[7:0];h0079[7:0]=h0*/ GET_OSD_WIN_REG_WIN7_LINE_OFFSET() \
	( msReadByte( 0x1DF2 ) )
#define /*REG_1DF2[7:0];h0079[7:0]=h0*/ SET_OSD_WIN_REG_WIN7_LINE_OFFSET( V ) \
	msWriteByte( 0x1DF2, (V) );
/*
OSD code buffer line offset value( unit : 1ca (or 1/4 entry)).*/
#define /*REG_1DF3[7:0];h0079[15:8]=h0*/ GET_OSD_WIN_REG_WIN7_LINE_OFFSET_TX() \
	( msReadByte( 0x1DF3 ) )
#define /*REG_1DF3[7:0];h0079[15:8]=h0*/ SET_OSD_WIN_REG_WIN7_LINE_OFFSET_TX( V ) \
	msWriteByte( 0x1DF3, (V) );
/*
OSD code buffer line offset value for text
( unit : 1ca (or 1/4 entry)).*/
#define /*REG_1DF4[2:0];h007a[2:0]=h0*/ GET_OSD_WIN_REG_WIN7_CLR_R_SEL() \
	( msReadByte( 0x1DF4 ) & 0x07 )
#define /*REG_1DF4[2:0];h007a[2:0]=h0*/ SET_OSD_WIN_REG_WIN7_CLR_R_SEL( V ) \
	msWriteByteMask( 0x1DF4, (V), 0x07 );
/*
grading color R select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr r */
#define /*REG_1DF4[6:4];h007a[6:4]=h0*/ GET_OSD_WIN_REG_WIN7_CLR_G_SEL() \
	( ( msReadByte( 0x1DF4 ) & 0x70 ) >>  4 )
#define /*REG_1DF4[6:4];h007a[6:4]=h0*/ SET_OSD_WIN_REG_WIN7_CLR_G_SEL( V ) \
	msWriteByteMask( 0x1DF4, ((V) <<  4), 0x70 );
/*
grading color G select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr g*/
#define /*REG_1DF5[2:0];h007a[10:8]=h0*/ GET_OSD_WIN_REG_WIN7_CLR_B_SEL() \
	( msReadByte( 0x1DF5 ) & 0x07 )
#define /*REG_1DF5[2:0];h007a[10:8]=h0*/ SET_OSD_WIN_REG_WIN7_CLR_B_SEL( V ) \
	msWriteByteMask( 0x1DF5, (V), 0x07 );
/*
grading color B select :
0: gd_engine 0
1: gd_engine 1
?K.
5: gd_engine 5
6: fix clr b*/
#define /*REG_1DF5[4:4];h007a[12:12]=h0*/ GET_OSD_WIN_REG_WIN7_TRANS_INV() \
	( 0 != ( msReadByte( 0x1DF5 ) & 0x10 ) )
#define /*REG_1DF5[4:4];h007a[12:12]=h0*/ SET_OSD_WIN_REG_WIN7_TRANS_INV() \
	msWriteByteMask( 0x1DF5, 0xFF, 0x10 );
#define /*REG_1DF5[4:4];h007a[12:12]=h0*/ CLR_OSD_WIN_REG_WIN7_TRANS_INV() \
	msWriteByteMask( 0x1DF5, 0x0, 0x10 );
#define /*REG_1DF5[4:4];h007a[12:12]=h0*/ ASG_OSD_WIN_REG_WIN7_TRANS_INV( V ) \
	msWriteByteMask( 0x1DF5, ( 0 != (V) )? 0x10: 0, 0x10 );
/*
inverse transparent define*/
#define /*REG_1DF5[5:5];h007a[13:13]=h0*/ GET_OSD_WIN_REG_WIN7_CKEY_INV() \
	( 0 != ( msReadByte( 0x1DF5 ) & 0x20 ) )
#define /*REG_1DF5[5:5];h007a[13:13]=h0*/ SET_OSD_WIN_REG_WIN7_CKEY_INV() \
	msWriteByteMask( 0x1DF5, 0xFF, 0x20 );
#define /*REG_1DF5[5:5];h007a[13:13]=h0*/ CLR_OSD_WIN_REG_WIN7_CKEY_INV() \
	msWriteByteMask( 0x1DF5, 0x0, 0x20 );
#define /*REG_1DF5[5:5];h007a[13:13]=h0*/ ASG_OSD_WIN_REG_WIN7_CKEY_INV( V ) \
	msWriteByteMask( 0x1DF5, ( 0 != (V) )? 0x20: 0, 0x20 );
/*
inverse color key define*/
#define /*REG_1DF5[6:6];h007a[14:14]=h0*/ GET_OSD_WIN_REG_WIN7_FIX_ATRB_EN_TX() \
	( 0 != ( msReadByte( 0x1DF5 ) & 0x40 ) )
#define /*REG_1DF5[6:6];h007a[14:14]=h0*/ SET_OSD_WIN_REG_WIN7_FIX_ATRB_EN_TX() \
	msWriteByteMask( 0x1DF5, 0xFF, 0x40 );
#define /*REG_1DF5[6:6];h007a[14:14]=h0*/ CLR_OSD_WIN_REG_WIN7_FIX_ATRB_EN_TX() \
	msWriteByteMask( 0x1DF5, 0x0, 0x40 );
#define /*REG_1DF5[6:6];h007a[14:14]=h0*/ ASG_OSD_WIN_REG_WIN7_FIX_ATRB_EN_TX( V ) \
	msWriteByteMask( 0x1DF5, ( 0 != (V) )? 0x40: 0, 0x40 );
/*
enable uniform window attribute mode for text*/
#define /*REG_1DF5[7:7];h007a[15:15]=h0*/ GET_OSD_WIN_REG_WIN7_FIX_ATRB_EN() \
	( 0 != ( msReadByte( 0x1DF5 ) & 0x80 ) )
#define /*REG_1DF5[7:7];h007a[15:15]=h0*/ SET_OSD_WIN_REG_WIN7_FIX_ATRB_EN() \
	msWriteByteMask( 0x1DF5, 0xFF, 0x80 );
#define /*REG_1DF5[7:7];h007a[15:15]=h0*/ CLR_OSD_WIN_REG_WIN7_FIX_ATRB_EN() \
	msWriteByteMask( 0x1DF5, 0x0, 0x80 );
#define /*REG_1DF5[7:7];h007a[15:15]=h0*/ ASG_OSD_WIN_REG_WIN7_FIX_ATRB_EN( V ) \
	msWriteByteMask( 0x1DF5, ( 0 != (V) )? 0x80: 0, 0x80 );
/*
enable uniform window attribute mode*/
#define /*REG_1DF6[7:0];h007b[7:0]=h0*/ GET_OSD_WIN_REG_WIN7_FIX_CLR_R() \
	( msReadByte( 0x1DF6 ) )
#define /*REG_1DF6[7:0];h007b[7:0]=h0*/ SET_OSD_WIN_REG_WIN7_FIX_CLR_R( V ) \
	msWriteByte( 0x1DF6, (V) );
/*
for lv2 blending : fix grading color R*/
#define /*REG_1DF7[7:0];h007b[15:8]=h0*/ GET_OSD_WIN_REG_WIN7_FIX_CLR_G() \
	( msReadByte( 0x1DF7 ) )
#define /*REG_1DF7[7:0];h007b[15:8]=h0*/ SET_OSD_WIN_REG_WIN7_FIX_CLR_G( V ) \
	msWriteByte( 0x1DF7, (V) );
/*
for lv2 blending : fix grading color G*/
#define /*REG_1DF8[7:0];h007c[7:0]=h0*/ GET_OSD_WIN_REG_WIN7_FIX_CLR_B() \
	( msReadByte( 0x1DF8 ) )
#define /*REG_1DF8[7:0];h007c[7:0]=h0*/ SET_OSD_WIN_REG_WIN7_FIX_CLR_B( V ) \
	msWriteByte( 0x1DF8, (V) );
/*
for lv2 blending : fix grading color B*/
#define /*REG_1DF9[5:0];h007c[13:8]=h0*/ GET_OSD_WIN_REG_WIN7_FIX_ALPHA_LV2() \
	( msReadByte( 0x1DF9 ) & 0x3F )
#define /*REG_1DF9[5:0];h007c[13:8]=h0*/ SET_OSD_WIN_REG_WIN7_FIX_ALPHA_LV2( V ) \
	msWriteByteMask( 0x1DF9, (V), 0x3F );
/*
for lv2 blending : fix alpha level 2*/
#define /*REG_1DFA[7:0];h007d[7:0]=h0*/ GET_OSD_WIN_REG_WIN7_FIX_ATRB() \
	( msReadByte( 0x1DFA ) )
#define /*REG_1DFA[7:0];h007d[7:0]=h0*/ SET_OSD_WIN_REG_WIN7_FIX_ATRB( V ) \
	msWriteByte( 0x1DFA, (V) );
/*
uniform window attribute*/
#define /*REG_1DFB[7:0];h007d[15:8]=h0*/ GET_OSD_WIN_REG_WIN7_FIX_ATRB_TX() \
	( msReadByte( 0x1DFB ) )
#define /*REG_1DFB[7:0];h007d[15:8]=h0*/ SET_OSD_WIN_REG_WIN7_FIX_ATRB_TX( V ) \
	msWriteByte( 0x1DFB, (V) );
/*
uniform window attribute for text*/
#define /*REG_1DFC[3:0];h007e[3:0]=h0*/ GET_OSD_WIN_REG_WIN7_MONO_PREFIX() \
	( msReadByte( 0x1DFC ) & 0x0F )
#define /*REG_1DFC[3:0];h007e[3:0]=h0*/ SET_OSD_WIN_REG_WIN7_MONO_PREFIX( V ) \
	msWriteByteMask( 0x1DFC, (V), 0x0F );
/*
register for Mono font prefix atrribute*/
#define /*REG_1DFC[7:4];h007e[7:4]=h0*/ GET_OSD_WIN_REG_WIN7_MONO_PREFIX_TX() \
	( ( msReadByte( 0x1DFC ) & 0xF0 ) >>  4 )
#define /*REG_1DFC[7:4];h007e[7:4]=h0*/ SET_OSD_WIN_REG_WIN7_MONO_PREFIX_TX( V ) \
	msWriteByteMask( 0x1DFC, ((V) <<  4), 0xF0 );
/*
register for Mono font prefix atrribute for text*/
#define /*REG_1DFD[7:0];h007e[15:8]=hf0*/ GET_OSD_WIN_REG_WIN7_DUMMY() \
	( msReadByte( 0x1DFD ) )
#define /*REG_1DFD[7:0];h007e[15:8]=hf0*/ SET_OSD_WIN_REG_WIN7_DUMMY( V ) \
	msWriteByte( 0x1DFD, (V) );
/*
dummy_register_win7*/
#define /*REG_1DFE[13:0];h007f[13:0]=h0*/ GET_OSD_WIN_REG_WIN7_BASE_TX() \
	( msReadByte( 0x1DFE ) | ( (msReadByte( 0x1DFF ) & 0x3F) <<  8 ) )
#define /*REG_1DFE[13:0];h007f[13:0]=h0*/ SET_OSD_WIN_REG_WIN7_BASE_TX( V ) \
	{ msWriteByte( 0x1DFE, (V) ); msWriteByteMask( 0x1DFF, ((V) >>  8), 0x3F ); }
/*
OSD code-attribute Base Address. Fot text
[13:2] for sram entry, [1:0] for low(0) ~ high(3)  18 bits*/


#define DEF_READ_ARRANGE_WIN(i) void OSDReadArrangeWin##i(WORD* hs, WORD* he, WORD* vs, WORD* ve) { \
		_CTRL_OSD_WIN_REGISTERS(); \
		*he = GET_OSD_WIN_REG_WIN##i##_HEND_PIX(); \
		*hs = GET_OSD_WIN_REG_WIN##i##_HSTR_PIX(); \
		*ve = GET_OSD_WIN_REG_WIN##i##_VEND_PIX(); \
		*vs = GET_OSD_WIN_REG_WIN##i##_VSTR_PIX(); }
#if 0
*he = GET_OSD_WIN_REG_WIN0_HEND_PIX();
\
*hs = GET_OSD_WIN_REG_WIN0_HSTR_PIX();
\
*ve = GET_OSD_WIN_REG_WIN0_VEND_PIX();
\
*vs = GET_OSD_WIN_REG_WIN0_VSTR_PIX();
}
#endif

#define DEF_READ_BLENDING_WIN(i) void OSDReadBlendingWin##i(BYTE* r_gd, BYTE* g_gd, BYTE* b_gd, BYTE* fix_r, BYTE* fix_g, BYTE* fix_b, BYTE* l1a_sel, BYTE* fix_al1, BYTE* l2a_sel, BYTE* fix_al2, BYTE* outa_sel, BYTE* fix_aout) { \
		_CTRL_OSD_WIN_REGISTERS(); \
		*r_gd = GET_OSD_WIN_REG_WIN##i##_CLR_B_SEL(); \
		*g_gd = GET_OSD_WIN_REG_WIN##i##_CLR_G_SEL(); \
		*b_gd = GET_OSD_WIN_REG_WIN##i##_CLR_R_SEL(); \
		*fix_r = GET_OSD_WIN_REG_WIN##i##_FIX_CLR_R(); \
		*fix_g = GET_OSD_WIN_REG_WIN##i##_FIX_CLR_G(); \
		*fix_b = GET_OSD_WIN_REG_WIN##i##_FIX_CLR_B(); \
		*fix_al1 = GET_OSD_WIN_REG_WIN##i##_FIX_ALPHA_LV1(); \
		*fix_al2 = GET_OSD_WIN_REG_WIN##i##_FIX_ALPHA_LV2(); \
		*fix_aout = GET_OSD_WIN_REG_WIN##i##_FIX_ALPHA_OUT(); \
		*l1a_sel = GET_OSD_WIN_REG_WIN##i##_LV1_A_SEL(); \
		*l2a_sel = GET_OSD_WIN_REG_WIN##i##_LV2_A_SEL(); \
		*outa_sel = GET_OSD_WIN_REG_WIN##i##_OUT_A_SEL(); }
#if 0
GET_OSD_WIN_REG_WIN0_CLR_B_SEL(r_gd);
\
GET_OSD_WIN_REG_WIN0_CLR_G_SEL(g_gd);
\
GET_OSD_WIN_REG_WIN0_CLR_R_SEL(b_gd);
\
GET_OSD_WIN_REG_WIN0_FIX_CLR_R(fix_r);
GET_OSD_WIN_REG_WIN0_FIX_CLR_G(fix_g);
GET_OSD_WIN_REG_WIN0_FIX_CLR_B(fix_b);
GET_OSD_WIN_REG_WIN0_FIX_ALPHA_LV1(fix_al1);
\
GET_OSD_WIN_REG_WIN0_FIX_ALPHA_LV2(fix_al2);
\
GET_OSD_WIN_REG_WIN0_FIX_ALPHA_OUT(fix_aout);
\
GET_OSD_WIN_REG_WIN0_
GET_OSD_WIN_REG_WIN0_LV1_A_SEL(l1a_sel);
\
GET_OSD_WIN_REG_WIN0_LV2_A_SEL(l2a_sel);
\
GET_OSD_WIN_REG_WIN0_OUT_A_SEL(outa_sel);
}
#endif


#define DEF_READ_CONF_SRAM_WIN(i) void OSDReadConfSramWin##i(BYTE* fh, WORD* base_addr, BYTE* l_off, BYTE* sh_x, BYTE* sh_y) { \
		_CTRL_OSD_WIN_REGISTERS(); \
		*fh = GET_OSD_WIN_REG_WIN##i##_CHARHIGH(); \
		*base_addr = GET_OSD_WIN_REG_WIN##i##_BASE(); \
		*l_off = GET_OSD_WIN_REG_WIN##i##_LINE_OFFSET(); \
		*sh_x = GET_OSD_WIN_REG_WIN##i##_SHIFT_PIX_X(); \
		*sh_y = GET_OSD_WIN_REG_WIN##i##_SHIFT_PIX_Y(); }
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

#define DEF_READ_CONF_SRAM_TEXT_WIN(i) void OSDReadConfSramTextWin##i(BYTE* fh, WORD* base_addr, BYTE* l_off, BYTE* sh_x, BYTE* sh_y) { \
		_CTRL_OSD_WIN_REGISTERS(); \
		*fh = GET_OSD_WIN_REG_WIN##i##_CHARHIGH(); \
		*base_addr = GET_OSD_WIN_REG_WIN##i##_BASE_TX(); \
		*l_off = GET_OSD_WIN_REG_WIN##i##_LINE_OFFSET_TX(); \
		*sh_x = GET_OSD_WIN_REG_WIN##i##_SHIFT_PIX_X(); \
		*sh_y = GET_OSD_WIN_REG_WIN##i##_SHIFT_PIX_Y(); }
#if 0
SET_OSD_WIN_REG_WIN0_CHARHIGH(fh);
\
SET_OSD_WIN_REG_WIN0_BASE_TX(V);
\
SET_OSD_WIN_REG_WIN0_LINE_OFFSET_TX(l_off);
\
SET_OSD_WIN_REG_WIN0_SHIFT_PIX_X(sh_x);
\
SET_OSD_WIN_REG_WIN0_SHIFT_PIX_Y(sh_y);
}
#endif


#define DEF_READ_CONF_GD_TG(i) void OSDReadConfGDTimingGenerator##i(unsigned* hs, unsigned* he, unsigned* vs, unsigned* ve) { \
		_CTRL_OSD_GD_REGISTERS(); \
		*hs = GET_OSD_GD_REG_GD_TG##i##_HST(); \
		*vs = GET_OSD_GD_REG_GD_TG##i##_VST(); \
		*he = GET_OSD_GD_REG_GD_TG##i##_HEND(); \
		*ve = GET_OSD_GD_REG_GD_TG##i##_VEND(); }
#if 0
GET_OSD_GD_REG_GD_TG0_HST(hs);
\
GET_OSD_GD_REG_GD_TG0_VST(vs);
\
GET_OSD_GD_REG_GD_TG0_HEND(he);
\
GET_OSD_GD_REG_GD_TG0_VEND(ve);
}
#endif



#endif



#endif ///_DRVOSD_H

