//******************************************************************************
//  Copyright (c) 2003-2008 MStar Semiconductor, Inc.
//  All rights reserved.
//
//  [Module Name]:
//      DPTxApp.c
//  [Abstract]:
//      This module contains code for DisplayPort receiver's application level
//      procedure and subroutin
//  [Author(s)]:
//      Vincent Kuo
//  [Reversion History]:
//      Initial release:    06 May, 2008
//*******************************************************************************

#ifndef _DPTXAPP_C_
#define _DPTXAPP_C_

#include "global.h"
#include "msflash.h"
#include "DDC2Bi.h"
#include <math.h>
#include <string.h>
#include "drvDPTxApp.h"


#if ENABLE_DisplayPortTX
//-------------------------------------------------------------------------------------------------
//  Local Structures & define
//-------------------------------------------------------------------------------------------------
enum
{
	eDPTXSTATE_STARTUP,  //0
	eDPTXSTATE_CHECKEDID, // 1
	eDPTXSTATE_TRAINING, // 2
	eDPTXSTATE_CHECKTIMING, // 3
	eDPTXSTATE_NORMAL, // 4
	eDPTXSTATE_POWERSAVE, // 5
	eDPTXSTATE_DPIDLE  // 6
};

#define  DPTX_DEBUG  1
#if (DPTX_DEBUG&&ENABLE_DEBUG)
#define DPTX_printData(str, value)   printData(str, value)
#define DPTX_printMsg(str)               printMsg(str)
#else
#define DPTX_printData(str, value)
#define DPTX_printMsg(str)
#endif

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
DPTX_INFO _DPTXDATATYPE_ gDPTXInfo;
BYTE _DPTXDATATYPE_ DPTXState = 20;
BYTE _DPTXDATATYPE_ HPDSense = 0;
BYTE _DPTXDATATYPE_ HPDSense1T = 0;
static BYTE _DPTXDATATYPE_ m_DPTXState = eDPTXSTATE_STARTUP;
//BYTE code  TXREADEDID[256];
BYTE xdata RX_EDID[128] = {0};

void DPTxInit(void)
{
	#if 0
	msWriteByte(0x0500, 0x00);
	msWriteByte(0x0501, 0x00);
	msWriteByte(0x2329, 0x40);
// ###############    DP TX PHY Init ########################
//Analog power-on and clock-gen enable
	msWriteByte(0x2408, 0x03);
	msWriteByte(0x2300, 0x00);
	msWriteByte(0x2301, 0x00);
	msWriteByte(0x2302, 0x00);
	msWriteByte(0x2303, 0x06);  //[2]:1: PLL POWER DOWN [1]: 1:Rterm POWER DOWN
	msWriteByte(0x2304, 0x00);
	msWriteByte(0x2305, 0x00);
	msWriteByte(0x2220, 0x00);
	msWriteByte(0x2221, 0x00);
	msWriteByte(0x2222, 0x00);
	msWriteByte(0x2223, 0x00);
//TX clock synthesizer setting  BK22:DP_DPHY_TOP
	msWriteByte(0x223C, 0x00);
	msWriteByte(0x223D, 0x42);
	msWriteByte(0x223A, 0x00);
	msWriteByte(0x223B, 0x10);
// kujo patch
	msWriteByte(0x2335, 0x3C);  // OVEN
	msWriteByte(0x2316, 0x08);  // SW
	msWriteByte(0x2318, 0x02);  // PRE
	#if DP32G
	msWriteByte(0x22C0, 0xAA);  // 3.24G
	msWriteByte(0x22C1, 0xAA);  // 3.24G
	msWriteByte(0x22C2, 0x2A);  // 3.24G
	#else
	#if DP29G
	msWriteByte(0x22C0, 0xA2);  // 2.97G
	msWriteByte(0x22C1, 0x8B);  // 2.97G
	msWriteByte(0x22C2, 0x2E);  // 2.97G
	#else
	#if DP27G
	msWriteByte(0x22C0, 0x33);  // 2.7G
	msWriteByte(0x22C1, 0x33);  // 2.7G
	msWriteByte(0x22C2, 0x33);  // 2.7G
	#else
	msWriteByte(0x22C0, 0x55);  // 1.62G
	msWriteByte(0x22C1, 0x55);  // 1.62G
	msWriteByte(0x22C2, 0x55);  // 1.62G
	#endif
	#endif
	#endif
	msWriteByte(0x22C4, 0x00);
	msWriteByte(0x22C5, 0x00);
	msWriteByte(0x22C6, 0x00);
	msWriteByte(0x22C7, 0x00);
	msWriteByte(0x22C8, 0x04);
//Configure DP TX mode and enable TX clock gen.
	msWriteByte(0x0568, 0x02);  // DP_TX_MODE
	msWriteByte(0x130A, 0xFF);  //DP ENABLE CLOCK
	msWriteByte(0x130B, 0xFF);  //DP ENABLE CLOCK
//MSA refer to BK14_BE~BK14_CE setting in dp_reg_dpcd_main.xls
//DP TX Function Enable
	msWriteByte(0x14D4, 0x01);  //AV ENABLE
	msWriteByte(0x1316, 0x03); //DP [5:4]=00=1 lane ,  [3:0]=3=8bits color bits
//DP TX Training P1
//NarutoWriteWord(0x142b,0x01);
	#endif
	msWriteByte( REG_1382, 0xFF );  // mask INT
	msWriteByte( REG_1383, 0xFF );  // mask INT
	msWriteByte( REG_1386, 0xFF );  // clear INT
	msWriteByte( REG_1387, 0xFF );  // clear INT
	msWriteByte( REG_1386, 0x00 );  // clear INT
	msWriteByte( REG_1387, 0x00 );  // clear INT
//### Enable DP TX
	msWriteByte(REG_15D4, 0x01); //156A[0] = 1
//### Enable DP TX transceiver #########
	#if !eDPTXU03
	msWriteByte(REG_138A, 0x08); // [3]: 1: enable SW control, 0: by hardware [2]: 0: not idle, 1: idle
	#endif
	msWriteByte(REG_15E6, 0x24); // [5]: MISC1[2] override control
// Choose one depend on video source is active or not
	//msWriteByte(0x15D1,0x01); //1568[8] = 1 => override value         // No video source => no MSA, just VBID
	msWriteByte(REG_15D1, 0x0C); //1568[11:10]: short line, DE for 1080p@120Hz or 2560x1440, [8] = 0 => override value         // Has video source -> MSA and VBID
//No video and audio stream
	msWriteByte(REG_15D2, 0x01); //1569[0] = 1 => Enable video mute override control
	msWriteByteMask(REG_15D1, BIT0, BIT0); //1568[8] = 1 => override value, video mute
// ###############    AUX Init    ###########################
	msWriteByte(REG_138A, msReadByte(REG_138A) | 0x03); //  [0]:overwrite enable [1]:DP force HPD High
	msWriteByte(REG_130A, 0x60); // [5]:TX AUX CLK EN [6]:TX XTAL CLK EN
	msWriteByte(REG_1348, 0x20); // INV AUXOEN
	msWriteByte(REG_1303, 0x01); // [0]: AUX Reset
	msWriteByte(REG_1303, 0x00); // [0]: AUX Reset
//	msWriteByte(REG_130E,0x04); // [3:2] = 01  set  aux clk = crystal /2
	msWriteByte(REG_1322, 0x30); // Timeout thr  // christ tao modify
	msWriteByte(REG_1323, 0x4B); // Timeout thr  [6]: reg_aux_reply_by_mcu // christ tao modify
	msWriteByte(REG_132D, 0x00); // [1]:new method
	msWriteByte(REG_1339, 0x0D); // DPTX AUX OVER SAMPLE = BK35_99
	msWriteByte(REG_1326, 0x08); // [6:0] DPTX AUX PHY UI	= BK35_98[7:1]
	msWriteByte(REG_134D, 0x02); // [3:1] =001 AUX Rx Debounce clk selection
	msWriteByte(REG_134C, 0x38); // [6] : reg_aux_rx_sel
	msWriteByte(REG_138E, msReadByte(REG_138E) & 0xFC); // [1][0]:0 reg_pd_aux_rterm
	DPTX_printMsg("DP TX Init!!!");
	DPTxIRQEnable(TRUE);
}

//**************************************************************************
//  [Function Name]:
//                  DPTxIRQEnable(Bool bEnable)
//  [Description]
//                  DPTxIRQEnable
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void DPTxIRQEnable( Bool bEnable )
{
	if( bEnable )
	{
		msWriteByte( REG_1386, 0xFF );  // clear INT
		msWriteByte( REG_1387, 0xFF );  // clear INT
		msWriteByte( REG_1386, 0x00 );  // clear INT
		msWriteByte( REG_1387, 0x00 );  // clear INT
		msWriteByte(REG_1382, msReadByte(REG_1382) & 0xFB); // Short Pause HPD
		msWriteByte(REG_1382, msReadByte(REG_1382) & 0xFD); // Long Pause HPD
		msWriteByteMask( REG_2B19, ~( _BIT7 ), _BIT7 ); //DP
	}
	else
	{
		msWriteByteMask( REG_2B19, ( _BIT7), _BIT7 );   //DP
	}
}

//=================================================================
//=================================================================
#if 0//eDPTXU03, AUX no length test
BYTE DPCDWRITEBYTENOLENS (BYTE ADDR2, BYTE ADDR1, BYTE ADDR0, BYTE TXDATA)
{
	BYTE RPYCMD;
	msWriteByte(REG_1340, 0x08); // [3:0] CMD  NR:9 NW:8
	msWriteByte(REG_1344, ADDR2 & 0x0F); // [3:0] ADDR[19:16]
	msWriteByte(REG_1343, ADDR1); // ADDR[15:8]
	msWriteByte(REG_1342, ADDR0); // ADDR[7:0]
	msWriteByte(REG_1347, 0x00); // [7:4] LEN [3:0]
	msWriteByte(REG_1338, TXDATA); // Write DATA PORT
	msWriteByte(REG_1334, 0x01); // [0]:No lens
	msWriteByte(REG_1336, 0x08); // Fire CMD
	msWriteByte(REG_1336, 0x00); // Fire CMD
	while ( ((msReadByte(REG_133E) & 0x41) == 0)) // 133E[6]=1 rply complete ,133E[0] AUX RX Timeout IRQ
	{
		Delay4us();
	}
	RPYCMD = (msReadByte(REG_133E) & 0x01) ? 0xFF : msReadByte(REG_132E) & 0x0F; // Reply CMD
	msWriteByte(REG_1347, 0x01); // Clear Pointer
	msWriteByte(REG_133E, 0xFF); // Clear IRQ
	msWriteByte(REG_1334, 0x00); // [0]:No lens
	if((msReadByte(REG_133E) & 0x01) | (RPYCMD != 0x00))
	{
		DPTX_printMsg("W DPCD Fail!!!");
	}
	return RPYCMD;
}

#endif

BYTE DPCDREADBYTE (BYTE ADDR2, BYTE ADDR1, BYTE ADDR0)
{
	BYTE RPYCMD, RXDATA;
	msWriteByte(REG_1340, 0x09); // [3:0] CMD  NR:9 NW:8
	msWriteByte(REG_1344, ADDR2 & 0x0F); // [3:0] ADDR[19:16]
	msWriteByte(REG_1343, ADDR1); // ADDR[15:8]
	msWriteByte(REG_1342, ADDR0); // ADDR[7:0]
	msWriteByte(REG_1347, 0x00); // [7:4] LEN [3:0]
	msWriteByte(REG_1336, 0x08); // Fire CMD
	while ( ((msReadByte(REG_133E) & 0x41) == 0)) // 133E[6]=1 rply complete ,133E[0] AUX RX Timeout IRQ
	{
		Delay4us();
	}
	RPYCMD = (msReadByte(REG_133E) & 0x01) ? 0xFF : msReadByte(REG_132E) & 0x0F; // Reply CMD
	msWriteByte(REG_132D, 0x01);      // Read pulse
	RXDATA = msReadByte(REG_132C); // Reply DATA
	msWriteByte(REG_1347, 0x01); // Clear Pointer
	msWriteByte(REG_133E, 0xFF); // Clear IRQ  [0]AUX RX Timeout IRQ
	return RXDATA;
}

BYTE DPCDWRITEBYTE (BYTE ADDR2, BYTE ADDR1, BYTE ADDR0, BYTE TXDATA)
{
	BYTE RPYCMD;
	msWriteByte(REG_1340, 0x08); // [3:0] CMD  NR:9 NW:8
	msWriteByte(REG_1344, ADDR2 & 0x0F); // [3:0] ADDR[19:16]
	msWriteByte(REG_1343, ADDR1); // ADDR[15:8]
	msWriteByte(REG_1342, ADDR0); // ADDR[7:0]
	msWriteByte(REG_1347, 0x00); // [7:4] LEN [3:0]
	msWriteByte(REG_1338, TXDATA); // Write DATA PORT
	msWriteByte(REG_1336, 0x08); // Fire CMD
	msWriteByte(REG_1336, 0x00); // Fire CMD
	while ( ((msReadByte(REG_133E) & 0x41) == 0)) // 133E[6]=1 rply complete ,133E[0] AUX RX Timeout IRQ
	{
		Delay4us();
	}
	RPYCMD = (msReadByte(REG_133E) & 0x01) ? 0xFF : msReadByte(REG_132E) & 0x0F; // Reply CMD
	msWriteByte(REG_1347, 0x01); // Clear Pointer
	msWriteByte(REG_133E, 0xFF); // Clear IRQ
	if((msReadByte(REG_133E) & 0x01) | (RPYCMD != 0x00))
	{
		DPTX_printMsg("W DPCD Fail!!!");
	}
	return RPYCMD;
}

void DPCDWRITEBYTES (BYTE ADDR2, BYTE ADDR1, BYTE ADDR0,  BYTE LEN, BYTE *TXDATA)
{
	BYTE RPYCMD, i = 0;
	msWriteByte(REG_1340, 0x08); // [3:0] CMD  NR:9 NW:8
	msWriteByte(REG_1344, ADDR2 & 0x0F); // [3:0] ADDR[19:16]
	msWriteByte(REG_1343, ADDR1); // ADDR[15:8]
	msWriteByte(REG_1342, ADDR0); // ADDR[7:0]
	msWriteByte(REG_1347, (LEN & 0x0F) << 4); // [7:4] LEN [3:0]
	for(i = 0; i <= LEN; i++)
	{
		msWriteByte(REG_1338, TXDATA[i]); // Write DATA PORT
	}
	msWriteByte(REG_1336, 0x08); // Fire CMD
	msWriteByte(REG_1336, 0x00); // Fire CMD
	while ( ((msReadByte(REG_133E) & 0x41) == 0)) // 133E[6]=1 rply complete ,133E[0] AUX RX Timeout IRQ
	{
		Delay4us();
	}
	RPYCMD = (msReadByte(REG_133E) & 0x01) ? 0xFF : msReadByte(REG_132E) & 0x0F; // Reply CMD
	msWriteByte(REG_1347, 0x01); // Clear Pointer
	msWriteByte(REG_133E, 0xFF); // Clear IRQ
	if((msReadByte(REG_133E) & 0x01) | (RPYCMD != 0x00))
	{
		DPTX_printMsg("W DPCD Fail!!!");
	}
	// return RPYCMD;
}


BYTE DPCDWRITEBYTE1 (BYTE CMD, BYTE ADDR2, BYTE ADDR1, BYTE ADDR0, BYTE TXDATA,  BYTE LEN, BYTE* RXDATA)
{
	BYTE xdata Temp[16] = 0;
	BYTE xdata i = 0;
	BYTE RPYCMD;
	msWriteByte(REG_1340, CMD); // [3:0] CMD  NR:9 NW:8 : 4 MOT
	msWriteByte(REG_1344, ADDR2 & 0x0F); // [3:0] ADDR[19:16]
	msWriteByte(REG_1343, ADDR1); // ADDR[15:8]
	msWriteByte(REG_1342, ADDR0); // ADDR[7:0]
	msWriteByte(REG_1347, (LEN & 0x0F) << 4); // [7:4] LEN [3:0]
	msWriteByte(REG_1338, TXDATA); // Write DATA PORT
	msWriteByte(REG_1336, 0x08); // Fire CMD
	msWriteByte(REG_1336, 0x00); // Fire CMD
	while ( ((msReadByte(REG_133E) & 0x41) == 0)) // 133E[6]=1 rply complete ,133E[0] AUX RX Timeout IRQ
	{
		Delay4us();
	}
	RPYCMD = (msReadByte(REG_133E) & 0x01) ? 0xFF : msReadByte(REG_132E) & 0x0F; // Reply CMD
	for(i = 0; i < (LEN + 1); i++)
	{
		msWriteByte(REG_132D, 0x01);               // Read pulse
		*(RXDATA + i) = msReadByte(REG_132C); // Reply DATA
	}
	msWriteByte(REG_1347, 0x01); // Clear Pointer
	msWriteByte(REG_133E, 0xFF); // Clear IRQ
	if((msReadByte(REG_133E) & 0x01) | (RPYCMD != 0x00))
	{
		DPTX_printMsg("W DPCD Fail!!!");
	}
	return RPYCMD;
}


void AUXREADBYTES (BYTE ADDR2, BYTE ADDR1, BYTE ADDR0, BYTE LEN, BYTE* RXDATA)
{
	BYTE RPYCMD;
	BYTE i;
	msWriteByte(REG_1340, (ADDR2 & 0xF0) >> 4); // [3:0] CMD  NR:9 NW:8
	msWriteByte(REG_1344, ADDR2 & 0x0F); // [3:0] ADDR[19:16]
	msWriteByte(REG_1343, ADDR1); // ADDR[15:8]
	msWriteByte(REG_1342, ADDR0); // ADDR[7:0]
	msWriteByte(REG_1347, (LEN & 0x0F) << 4); // [7:4] LEN [3:0]
	msWriteByte(REG_1336, 0x08); // Fire CMD
	while ( ((msReadByte(REG_133E) & 0x41) == 0)) // 133E[6]=1 rply complete ,133E[0] AUX RX Timeout IRQ
	{
		Delay4us();
	}
	RPYCMD = (msReadByte(REG_133E) & 0x01) ? 0xFF : msReadByte(REG_132E) & 0x0F; // Reply CMD
	//Delay10us(1);
	for(i = 0; i < (LEN + 1); i++)
	{
		msWriteByte(REG_132D, 0x01);               // Read pulse
		*(RXDATA + i) = msReadByte(REG_132C); // Reply DATA
	}
	msWriteByte(REG_1347, 0x01); // Clear Pointer
	msWriteByte(REG_133E, 0xFF); // Clear IRQ
}

/*
BYTE AUXWRITEBYTES (BYTE ADDR2, BYTE ADDR1, BYTE ADDR0, BYTE LEN, BYTE* TXDATA)
{
    BYTE RPYCMD;
    BYTE i;
    msWriteByte(REG_1340,(ADDR2&0xF0)>>4); // [3:0] CMD  NR:9 NW:8
    msWriteByte(REG_1344,ADDR2&0x0F); // [3:0] ADDR[19:16]
    msWriteByte(REG_1343,ADDR1); // ADDR[15:8]
    msWriteByte(REG_1342,ADDR0); // ADDR[7:0]
    msWriteByte(REG_1347,(LEN&0x0F)<<4); // [7:4] LEN [3:0]
    for (i=0;i<(LEN+1);i++)
    {
       msWriteByte(REG_1338,*(TXDATA+i)); // Write DATA PORT
    }
    msWriteByte(REG_1336,0x08); // Fire CMD
    msWriteByte(REG_1336,0x00); // Fire CMD
    while ( ((msReadByte(REG_133E)&0x41)==0)) // 133E[6]=1 rply complete ,133E[0] AUX RX Timeout IRQ
   {Delay4us();}
    RPYCMD=(msReadByte(REG_133E)&0x01)?0xFF:msReadByte(REG_132E)&0x0F;  // Reply CMD
    msWriteByte(REG_1347,0x01); // Clear Pointer
    msWriteByte(REG_133E,0xFF); // Clear IRQ
    return RPYCMD;
}
*/
void DPAUXTest (BYTE ADDR2, BYTE ADDR1, BYTE ADDR0)
{
	BYTE i;
	BYTE RXBUF[16];
	//BYTE TXBUF[16];
	DPTX_printMsg("AUX =");
	/*
	   for(i=0;i<16;i++)
	   {DPTX_printData("_%x_",DPCDREADBYTE(ADDR2,ADDR1,ADDR0+i));}

	   DPCDWRITEBYTE(ADDR2,ADDR1,ADDR0,0x06);
	   Delay1ms(1);
	   TXBUF[0]=0x0A;TXBUF[1]=0x02;
	   AUXWRITEBYTES(0x80|ADDR2,ADDR1,ADDR0,0x01,TXBUF);
	   Delay1ms(1);
	*/
	AUXREADBYTES(0x90 | ADDR2, ADDR1, ADDR0, 0x0F, RXBUF);
	for(i = 0; i < 16; i++)
	{
		DPTX_printData("%x", RXBUF[i]);
	}
}

#if 1
void DPTXSetMSA (BYTE timingidx)
{
	msWriteByte(REG_136E, 0x01); // Enable A/V M/N Gen [0]:video
	//msWriteByte(REG_1406,0x00); // Set TX LANE0
	//msWriteByte(REG_15BC,0xFF); // Enable attribute
	msWriteByte(REG_15CE, 0x20); // [8] MISC0 value for 8 bits
	//msWriteByte(REG_15CE,0x00); // [8] MISC0 value for 6 bits
	#if 0//(PANEL_SELECT == PaneleDPHestia_FHD_120HZ)
	if(g_SetupPathInfo.ucSCFmtIn == SC_FMT_IN_3D_PF)
	{
		DPTX_printMsg("$DPTx 3D");
		msWriteByte(REG_15CF, 0x02); // [9] MISC1 value
	}
	#endif
	msWriteByte(REG_154E, 0x03); // Video color depth for 8 bits
	//msWriteByte(REG_154E,0x04); // Video color depth for 6 bits
	/*
	1526[5:0] = reg_ping_pong_switch_ls_delay_cycle
	                 = 1/Freq_vclk*N*Freq_ls + 4
	                 = (Freq_ls/Freq_vclk)*N + 4
	limitation:
	0 < reg_ping_pong_switch_ls_delay_cycle < 64
	Freq_ls = 270M for HBR
	Freq_ls = 162M for RBR
	N = 6 for 1 lane
	N = 10 for 2 lanes
	N = 14 for 4 lanes
	*/
	/*  (270/85)*14+4 */
	//msWriteByte(REG_154C,0x18); // pingpong delay
	msWriteByte(REG_154C, eDPTXPingPongV & 0x3F); // pingpong delay
	DPTX_printData("PingPong %x", eDPTXPingPongV);
	switch(timingidx)
	{
		case DP_800X600_60HZ:
			DPTX_printMsg("DP TX SET MSA DP_800X600_60HZ");
			// ###############   SET MSA   ###########################
			// 800X600@60  Htotal=1056  HBLANK=256 HFP=40 HPWS=128 HBP=88
			//                      Vtotal=628   VBLANK=28   VFP=1  VPWS=4     HBP=23
			msWriteByte(REG_15BE, 0x20); // [0] Hotoal LSB 1056=0x420
			msWriteByte(REG_15BF, 0x04); // [0] Htotal MSB 1056=0x420
			msWriteByte(REG_15C0, 0xA8); // [1] HStart LSB 40+128=168=0xA8
			msWriteByte(REG_15C1, 0x00); // [1] HStart MSB 40+128=168=0xA8
			msWriteByte(REG_15C2, 0x80); // [2] HPWS LSB 128=0x80
			msWriteByte(REG_15C3, 0x00); // [2] HPWS MSB 128=0x80
			msWriteByte(REG_15C4, 0x74); // [3] Votoal LSB 628=0x274
			msWriteByte(REG_15C5, 0x02); // [3] Vtotal MSB 628=0x274
			msWriteByte(REG_15C6, 0x1B); // [4] VStart LSB 4+23=27=0x1B
			msWriteByte(REG_15C7, 0x00); // [4] VStart MSB 4+23=27=0x1B
			msWriteByte(REG_15C8, 0x04); // [5] VPWS LSB 4=0x04
			msWriteByte(REG_15C9, 0x00); // [5] VPWS MSB 4=0x04
			msWriteByte(REG_15CA, 0x20); // [6] HWidth LSB 800=0x320
			msWriteByte(REG_15CB, 0x03); // [6] HWidth MSB 800=0x320
			msWriteByte(REG_15CC, 0x58); // [7] VHeight LSB 600=0x258
			msWriteByte(REG_15CD, 0x02); // [7] VHeight MSB 600=0x258
			break;
		case DP_1024X768_60HZ:
			DPTX_printMsg("DP TX SET MSA DP_1024X768_60HZ");
			// ###############   SET MSA   ###########################
			// 1024X768@60  Htotal=1344 HBLANK=320 HFP=24 HPWS=136 HBP=160
			//                       Vtotal=806   VBLANK=38   VFP=3  VPWS=6     HBP=29
			//msWriteByte(REG_15BC,0x00); // Enable Attribute
			//msWriteByte(REG_15BD,0x00);  // Enable Attribute
			msWriteByte(REG_15BE, 0x40); // [0] Hotoal LSB 1344=0x540
			msWriteByte(REG_15BF, 0x05); // [0] Htotal MSB 1344=0x540
			msWriteByte(REG_15C0, 0x28); // [1] HStart LSB 136+160=296=0x128
			msWriteByte(REG_15C1, 0x01); // [1] HStart MSB 136+160=296=0x128
			msWriteByte(REG_15C2, 0x88); // [2] HPWS LSB 136=0x88
			msWriteByte(REG_15C3, 0x00); // [2] HPWS MSB 136=0x88
			msWriteByte(REG_15C4, 0x26); // [3] Votoal LSB 806=0x326
			msWriteByte(REG_15C5, 0x03); // [3] Vtotal MSB 806=0x326
			msWriteByte(REG_15C6, 0x23); // [4] VStart LSB 6+29=35=0x23
			msWriteByte(REG_15C7, 0x00); // [4] VStart MSB 6+29=35=0x23
			msWriteByte(REG_15C8, 0x06); // [5] VPWS LSB 6=0x06
			msWriteByte(REG_15C9, 0x00); // [5] VPWS MSB 6=0x06
			msWriteByte(REG_15CA, 0x00); // [6] HWidth LSB 1024=0x400
			msWriteByte(REG_15CB, 0x04); // [6] HWidth MSB 1024=0x400
			msWriteByte(REG_15CC, 0x00); // [7] VHeight LSB 768=0x300
			msWriteByte(REG_15CD, 0x03); // [7] VHeight MSB 768=0x300
			break;
		case DP_1280X800_60HZ:
			DPTX_printMsg("DP TX SET MSA DP_1280X800_60HZ");
			// ###############   SET MSA   ###########################
			// 1280X800    Htotal=1440  HBLANK=160    HFP=48   HPWS=32   HBP=80
			//   71M           Vtotal=823    VBLANK=23     VFP=3     VPWS=6     HBP=14
			msWriteByte(REG_15BE, 0xA0); // [0] Hotoal LSB 1440=0x5A0
			msWriteByte(REG_15BF, 0x05); // [0] Htotal MSB 1440=0x5A0
			msWriteByte(REG_15C0, 0x70); // [1] HStart LSB 32+80=112=0x70
			msWriteByte(REG_15C1, 0x00); // [1] HStart MSB 32+80=112=0x70
			msWriteByte(REG_15C2, 0x20); // [2] HPWS LSB 32=0x20
			msWriteByte(REG_15C3, 0x00); // [2] HPWS MSB 32=0x20
			msWriteByte(REG_15C4, 0x37); // [3] Votoal LSB 823=0x337
			msWriteByte(REG_15C5, 0x03); // [3] Vtotal MSB 823=0x337
			msWriteByte(REG_15C6, 0x14); // [4] VStart LSB 6+14=20=0x14
			msWriteByte(REG_15C7, 0x00); // [4] VStart MSB 6+14=20=0x14
			msWriteByte(REG_15C8, 0x06); // [5] VPWS LSB 6=0x06
			msWriteByte(REG_15C9, 0x00); // [5] VPWS MSB 6=0x06
			msWriteByte(REG_15CA, 0x00); // [6] HWidth LSB 1280=0x500
			msWriteByte(REG_15CB, 0x05); // [6] HWidth MSB 1280=0x500
			msWriteByte(REG_15CC, 0x20); // [7] VHeight LSB 800=0x320
			msWriteByte(REG_15CD, 0x03); // [7] VHeight MSB 800=0x320
			break;
		case DP_1360X768_60HZ:
			DPTX_printMsg("DP TX SET MSA DP_1360X768_60HZ");
			// ###############   SET MSA   ###########################
			// 1360X768    Htotal=1792  HBLANK=432   HFP=64   HPWS=112  HBP=256
			//   85.5M        Vtotal=795   VBLANK=27     VFP=3     VPWS=6     HBP=18
			msWriteByte(REG_15BE, 0x00); // [0] Hotoal LSB 1792=0x700
			msWriteByte(REG_15BF, 0x07); // [0] Htotal MSB 1792=0x700
			msWriteByte(REG_15C0, 0x70); // [1] HStart LSB 112+256=368=0x170
			msWriteByte(REG_15C1, 0x01); // [1] HStart MSB 112+256=368=0x170
			msWriteByte(REG_15C2, 0x70); // [2] HPWS LSB 112=0x70
			msWriteByte(REG_15C3, 0x00); // [2] HPWS MSB 112=0x70
			msWriteByte(REG_15C4, 0x1B); // [3] Votoal LSB 795=0x31B
			msWriteByte(REG_15C5, 0x03); // [3] Vtotal MSB 795=0x31B
			msWriteByte(REG_15C6, 0x18); // [4] VStart LSB 6+18=24=0x18
			msWriteByte(REG_15C7, 0x00); // [4] VStart MSB 6+18=24=0x18
			msWriteByte(REG_15C8, 0x06); // [5] VPWS LSB 6=0x06
			msWriteByte(REG_15C9, 0x00); // [5] VPWS MSB 6=0x06
			msWriteByte(REG_15CA, 0x56); // [6] HWidth LSB 1366=0x556
			msWriteByte(REG_15CB, 0x05); // [6] HWidth MSB 1366=0x556
			msWriteByte(REG_15CC, 0x00); // [7] VHeight LSB 768=0x300
			msWriteByte(REG_15CD, 0x03); // [7] VHeight MSB 768=0x300
			break;
		case DP_480P:
			DPTX_printMsg("DP TX SET MSA DP_480P");
			// ###############   SET MSA   ###########################
			// 720X480P  Htotal=858  HBLANK=138 HFP=16 HPWS=62 HBP=60
			//                 Vtotal=525  VBLANK=45   VFP=9   VPWS=6    HBP=30
			msWriteByte(REG_15BE, 0x5A); // [0] Hotoal LSB 858=0x35A
			msWriteByte(REG_15BF, 0x03); // [0] Htotal MSB 858=0x35A
			msWriteByte(REG_15C0, 0x7A); // [1] HStart LSB 62+60=122=0x7A
			msWriteByte(REG_15C1, 0x00); // [1] HStart MSB 62+60=122=0x7A
			msWriteByte(REG_15C2, 0x3E); // [2] HPWS LSB 62=0x3E
			msWriteByte(REG_15C3, 0x00); // [2] HPWS MSB 62=0x3E
			msWriteByte(REG_15C4, 0x0D); // [3] Votoal LSB 525=0x20D
			msWriteByte(REG_15C5, 0x02); // [3] Vtotal MSB 525=0x20D
			msWriteByte(REG_15C6, 0x24); // [4] VStart LSB 6+30=36=0x24
			msWriteByte(REG_15C7, 0x00); // [4] VStart MSB 6+30=36=0x24
			msWriteByte(REG_15C8, 0x06); // [5] VPWS LSB 6=0x06
			msWriteByte(REG_15C9, 0x00); // [5] VPWS MSB 6=0x06
			msWriteByte(REG_15CA, 0xD0); // [6] HWidth LSB 720=0x2D0
			msWriteByte(REG_15CB, 0x02); // [6] HWidth MSB 720=0x2D0
			msWriteByte(REG_15CC, 0xE0); // [7] VHeight LSB 480=0x1E0
			msWriteByte(REG_15CD, 0x01); // [7] VHeight MSB 480=0x1E0
			break;
		case DP_720P:
			DPTX_printMsg("DP TX SET MSA DP_720P");
			// ###############   SET MSA   ###########################
			// 1280X720P  Htotal=1650  HBLANK=370  HFP=110  HPWS=40  HBP=220
			//                   Vtotal=750    VBLANK=30    VFP=5     VPWS=5    HBP=20
			msWriteByte(REG_15BE, 0x72); // [0] Hotoal LSB 1650=0x672
			msWriteByte(REG_15BF, 0x06); // [0] Htotal MSB 1650=0x672
			msWriteByte(REG_15C0, 0x04); // [1] HStart LSB 40+220=260=0x104
			msWriteByte(REG_15C1, 0x01); // [1] HStart MSB 40+220=260=0x104
			msWriteByte(REG_15C2, 0x28); // [2] HPWS LSB 40=0x28
			msWriteByte(REG_15C3, 0x00); // [2] HPWS MSB 40=0x28
			msWriteByte(REG_15C4, 0xEE); // [3] Votoal LSB 750=0x2EE
			msWriteByte(REG_15C5, 0x02); // [3] Vtotal MSB 750=0x2EE
			msWriteByte(REG_15C6, 0x19); // [4] VStart LSB 5+20=25=0x19
			msWriteByte(REG_15C7, 0x00); // [4] VStart MSB 5+20=25=0x19
			msWriteByte(REG_15C8, 0x05); // [5] VPWS LSB 5=0x05
			msWriteByte(REG_15C9, 0x00); // [5] VPWS MSB 5=0x05
			msWriteByte(REG_15CA, 0x00); // [6] HWidth LSB 1280=0x500
			msWriteByte(REG_15CB, 0x05); // [6] HWidth MSB 1280=0x500
			msWriteByte(REG_15CC, 0xD0); // [7] VHeight LSB 720=0x2D0
			msWriteByte(REG_15CD, 0x02); // [7] VHeight MSB 720=0x2D0
			break;
		case DP_1080P:
			DPTX_printMsg("DP TX SET MSA DP_1080P");
			// ###############   SET MSA   ###########################
			// 1920X1080P  Htotal=2200  HBLANK=280  HFP=88  HPWS=44  HBP=148
			//                     Vtotal=1125  VBLANK=45   VFP=4    VPWS=5    VBP=36
			msWriteByte(REG_15BE, 0x98); // [0] Hotoal LSB 2200=0x898
			msWriteByte(REG_15BF, 0x08); // [0] Htotal MSB 2200=0x898
			msWriteByte(REG_15C0, 0xC0); // [1] HStart LSB 44+148=192=0xC0
			msWriteByte(REG_15C1, 0x00); // [1] HStart MSB 44+148=192=0xC0
			msWriteByte(REG_15C2, 0x2C); // [2] HPWS LSB 44=0x2C
			msWriteByte(REG_15C3, 0x00); // [2] HPWS MSB 44=0x2C
			msWriteByte(REG_15C4, 0x65); // [3] Votoal LSB 1125=0x465
			msWriteByte(REG_15C5, 0x04); // [3] Vtotal MSB 1125=0x465
			msWriteByte(REG_15C6, 0x29); // [4] VStart LSB 5+36=41=0x29
			msWriteByte(REG_15C7, 0x00); // [4] VStart MSB 5+36=41=0x29
			msWriteByte(REG_15C8, 0x05); // [5] VPWS LSB 5=0x05
			msWriteByte(REG_15C9, 0x00); // [5] VPWS MSB 5=0x05
			msWriteByte(REG_15CA, 0x80); // [6] HWidth LSB 1920=0x780
			msWriteByte(REG_15CB, 0x07); // [6] HWidth MSB 1920=0x780
			msWriteByte(REG_15CC, 0x38); // [7] VHeight LSB 1080=0x438
			msWriteByte(REG_15CD, 0x04); // [7] VHeight MSB 1080=0x438
			break;
		case DP_1080P_120HZ:
			DPTX_printMsg("DP TX SET MSA DP_1080P");
			// ###############   SET MSA   ###########################
			// 1920X1080P  Htotal=2200  HBLANK=280  HFP=88  HPWS=44  HBP=148
			//                     Vtotal=1125  VBLANK=45   VFP=4    VPWS=5    VBP=36
			msWriteByte(REG_15BE, 0x98); // [0] Hotoal LSB 2200=0x898
			msWriteByte(REG_15BF, 0x08); // [0] Htotal MSB 2200=0x898
			msWriteByte(REG_15C0, 0xC0); // [1] HStart LSB 44+148=192=0xC0
			msWriteByte(REG_15C1, 0x00); // [1] HStart MSB 44+148=192=0xC0
			msWriteByte(REG_15C2, 0x2C); // [2] HPWS LSB 44=0x2C
			msWriteByte(REG_15C3, 0x00); // [2] HPWS MSB 44=0x2C
			msWriteByte(REG_15C4, 0x65); // [3] Votoal LSB 1125=0x465
			msWriteByte(REG_15C5, 0x04); // [3] Vtotal MSB 1125=0x465
			msWriteByte(REG_15C6, 0x29); // [4] VStart LSB 5+36=41=0x29
			msWriteByte(REG_15C7, 0x00); // [4] VStart MSB 5+36=41=0x29
			msWriteByte(REG_15C8, 0x05); // [5] VPWS LSB 5=0x05
			msWriteByte(REG_15C9, 0x00); // [5] VPWS MSB 5=0x05
			msWriteByte(REG_15CA, 0x80); // [6] HWidth LSB 1920=0x780
			msWriteByte(REG_15CB, 0x07); // [6] HWidth MSB 1920=0x780
			msWriteByte(REG_15CC, 0x38); // [7] VHeight LSB 1080=0x438
			msWriteByte(REG_15CD, 0x04); // [7] VHeight MSB 1080=0x438
			break;
		case DP_2560X1440_60Hz:
			DPTX_printMsg("DP TX SET MSA DP_2560x1440");
			// ###############   SET MSA   ###########################
			// 1920X1080P  Htotal=2720  HBLANK=160  HFP=48  HPWS=32  HBP=80
			//                     Vtotal=1481  VBLANK=41   VFP=3    VPWS=5    VBP=33
			msWriteByte(REG_15BE, 0xA0); // [0] Hotoal LSB 2720=0xAA0
			msWriteByte(REG_15BF, 0x0A); // [0] Htotal MSB 2720=0xAA0
			msWriteByte(REG_15C0, 0x70); // [1] HStart LSB 32+80=112=0x70
			msWriteByte(REG_15C1, 0x00); // [1] HStart MSB 32+80=112=0x70
			msWriteByte(REG_15C2, 0x20); // [2] HPWS LSB 32=0x20
			msWriteByte(REG_15C3, 0x00); // [2] HPWS MSB 32=0x20
			msWriteByte(REG_15C4, 0xC9); // [3] Votoal LSB 1481=0x5C9
			msWriteByte(REG_15C5, 0x05); // [3] Vtotal MSB 1481=0x5C9
			msWriteByte(REG_15C6, 0x26); // [4] VStart LSB 5+33=38=0x26
			msWriteByte(REG_15C7, 0x00); // [4] VStart MSB 5+33=38=0x26
			msWriteByte(REG_15C8, 0x05); // [5] VPWS LSB 5=0x05
			msWriteByte(REG_15C9, 0x00); // [5] VPWS MSB 5=0x05
			msWriteByte(REG_15CA, 0x00); // [6] HWidth LSB 2560=0xA00
			msWriteByte(REG_15CB, 0x0A); // [6] HWidth MSB 2560=0xA00
			msWriteByte(REG_15CC, 0xA0); // [7] VHeight LSB 1440=0x5A0
			msWriteByte(REG_15CD, 0x05); // [7] VHeight MSB 1440=0x5A0
			break;
	}
	msWriteByteMask(REG_15D1, 0, BIT0); //1568[8] = 1 => override value, video unmute
	#if EN_DPTX_SSC
	/*
	SSC synthesizer:
	ssc_dn => 0: spread up and down, 1: spread down only

	hkr_set = mpll_clk/ssc_clk_out, N.F=(5,19)
	hkr_span = mpll_clk*2^19/(ssc_clk*4*hkr_set),
		   = ssc_clk_out/(ssc_clk*4)
	hkr_step = hkr_set*deviation/hkr_span

	For example
	mpll_clk =432M, ssc_clk =33K, ssc_clkout = 135M
	hkr_set = 432/135 = 3.2 => 24'h199999 (1677721) (N.F=5.19)
	hkr_span = 135M/(33K*4) = 1022 =0x3FE
	hkr_step = hkr_set*deviation/hkr_span,
		  = 1677721*0.5%/(1022*2) = 4.104

	deviation=?%= (1022*2)*hkr_step/1677721
	Get hkr_step = 4, deviation = 0.487%
	Get hkr_step = 5, deviation = 0.609%
	Get hkr_step = 6, deviation = 0.730%
	Get hkr_step = 7, deviation = 0.852%
	Get hkr_step = 8, deviation = 0.974%
	*/
// DownSpread HBR 0.487%
	msWriteByte(REG_1360, 0x99); // DP TX SSC freq
	msWriteByte(REG_1361, 0x99); // DP TX SSC freq
	msWriteByte(REG_1362, 0x19); // DP TX SSC freq
	msWriteByte(REG_1364, 0x04); // DP TX SSC STEP
	msWriteByte(REG_1365, 0x00); // DP TX SSC STEP
	msWriteByte(REG_1366, 0xFE); // DP TX SSC SPAN
	msWriteByte(REG_1367, 0x03); // DP TX SSC SPAN
	msWriteByte(REG_1368, 0x09); // [0]: Load SSC [1]:SSC sync Control [3]:DN only
	msWriteByte(REG_1368, 0x08); // [0]: Load SSC [1]:SSC sync Control [3]:DN only
	DPTX_printMsg("EN_DPTX_SSC");
	#endif
}
#endif

BOOL DPTXTrainingFlow(BYTE LinkRate, BYTE LaneCnt)
{
	BYTE xdata DATA[4] = {0};
	//DWORD VCO,LINKRATE;
	BYTE i;
	//DPTX_printMsg("DPCD_100");    //CCJ mark
	//DPAUXTest(0x00,0x01,0x00);	  //CCJ mark
	// ###################################################
	// #################  Training Stage #######################
	DPTX_printMsg(">>Start Training Flow!!");
	// ###################################################
	msWriteByte(REG_1300, 0x02); //Video M generation enable 1300[1]
	msWriteByte(REG_15EC, 0x00); //Video N Value 1576[15:0] = 16'h8000 , 1577[7:0] = 8'h0
	msWriteByte(REG_15ED, 0x80); //Video N Value 1576[15:0] = 16'h8000 , 1577[7:0] = 8'h0
	msWriteByte(REG_15EE, 0x00); //Video N Value 1576[15:0] = 16'h8000 , 1577[7:0] = 8'h0
	//msWriteByte(REG_130A,msReadByte(REG_130A)|0x80);  // TX synthesizer enable 1305[7] => 1: Enable, 0: Disable
	msWriteByte(REG_130A, 0xFF); //Enable DP TX clock gen 1305[15:0] = 16'hffff
	msWriteByte(REG_130B, 0xFF); //Enable DP TX clock gen 1305[15:0] = 16'hffff
	msWriteByte(REG_13A6, msReadByte(REG_13A6) & 0xEF); //1353[4]  => TXPLL power down
	msWriteByte(REG_138E, 0x00); //1347[15:0]  => DP power down control
	msWriteByte(REG_138F, 0x00); //1347[15:0]  => DP power down control
	msWriteByte(REG_154A, 0x02); //Enhance Frame Mode
	#if 0//eDPTXU03, AUX no length test
	DPTX_printMsg("[TEST AUX]");
	DPCDWRITEBYTENOLENS(0x00, 0x01, 0x00, 0x06);
	DPTX_printData("DPCD_100=%x_", DPCDREADBYTE(0x00, 0x01, 0x00));
	DPCDWRITEBYTENOLENS(0x00, 0x01, 0x00, 0x0A);
	DPTX_printData("DPCD_100=%x_", DPCDREADBYTE(0x00, 0x01, 0x00));
	#endif
	switch(LinkRate)
	{
		/*
		Input divider => 1353[6:5]  DP TX PLL input divider. 00:/1, 01:/2, 10:/4, 11:/8
		loop divider => 1353[13:8]
		output divider => 1353[15:14] DP TX PLL output divider. 00:/1, 01:/2, 10:/4, 11:/8

		1. RBR (1.62G)
		input divider = /1 = 1353[6:5]=0b'00
		output divider = /2 = 1353[15:14]=0b'01
		loop divider[3:0] = 4'h5   = 1353[11:8]
		loop divider[5:4] = 2'b01 = 1353[13:12]
		REG_13A6=0x00;
		REG_13A7=0x55; 0101_0101
		2. HBR (2.7G)
		input divider = /1 = 1353[6:5]=0b'00
		output divider = /1 = 1353[15:14]=0b'00
		loop divider[3:0] = 4'h5   = 1353[11:8]
		loop divider[5:4] = 2'b01 = 1353[13:12]
		REG_13A6=0x00;
		REG_13A7=0x15; 0001_0101
		*/
		case  DPTXRBR:
			//TX PLL Divider Setting
			msWriteByte(REG_13A6, msReadByte(REG_13A6) & 0x9F); // [6:5]=00
			msWriteByte(REG_13A7, 0x55);
			//TX synthesizer Value for RBR , 1330[15:0]= 16'h5547; 1331[7:0] = 8'h15;
			msWriteByte(REG_1360, 0x47);
			msWriteByte(REG_1361, 0x55);
			msWriteByte(REG_1362, 0x15);
			msWriteByte(REG_1368, 0x01); //Load SET value to synthesizer: 1334[0]
			msWriteByte(REG_1368, 0x00); // End
			DPCDWRITEBYTE(0x00, 0x01, 0x00, 0x06); //1.62G
			break;
		case DPTXHBR:
			//TX PLL Divider Setting
			msWriteByte(REG_13A6, msReadByte(REG_13A6) & 0x9F); // [6:5]=00
			msWriteByte(REG_13A7, 0x15);
			//TX synthesizer Value for HBR , 1330[15:0]= 16'h9988; 1331[7:0] = 8'h19;
			msWriteByte(REG_1360, 0x88);
			msWriteByte(REG_1361, 0x99);
			msWriteByte(REG_1362, 0x19);
			msWriteByte(REG_1368, 0x01); //Load SET value to synthesizer: 1334[0]
			msWriteByte(REG_1368, 0x00); // End
			DPCDWRITEBYTE(0x00, 0x01, 0x00, 0x0A); //2.70G
			break;
		case DPTXHBRx11:
			DPCDWRITEBYTE(0x00, 0x01, 0x00, 0x0B); //2.97G
			break;
		case DPTXHBRx12:
			DPCDWRITEBYTE(0x00, 0x01, 0x00, 0x0C); //3.24G
			break;
	}
	DPTX_printData("DPCD_100=%x_", DPCDREADBYTE(0x00, 0x01, 0x00));
	switch(LaneCnt)
	{
		case DPTX1L:
			msWriteByte(REG_1506, 0x00); //Lane number select : 1503[1:0]:00
			msWriteByte(REG_1352, 0x04);   //1329~2c[2:0] [2]: DP TX FIFO enable, [1:0]: Lane 0 FIFO select.
			DPCDWRITEBYTE(0x00, 0x01, 0x01, 0x81); // 1 Lane [7]:Enhance Frame
			break;
		case DPTX2L:
			msWriteByte(REG_1506, 0x01); //Lane number select : 1503[1:0] :01
			msWriteByte(REG_1352, 0x04);   //1329~2c[2:0] [2]: DP TX FIFO enable, [1:0]: Lane 0 FIFO select.
			msWriteByte(REG_1354, 0x05);   //1329~2c[2:0] [2]: DP TX FIFO enable, [1:0]: Lane 0 FIFO select.
			DPCDWRITEBYTE(0x00, 0x01, 0x01, 0x82); // 2 Lane [7]:Enhance Frame
			break;
		case DPTX4L:
			msWriteByte(REG_1506, 0x02); //Lane number select : 1503[1:0] :11
			msWriteByte(REG_1352, 0x04);   //1329~2c[2:0] [2]: DP TX FIFO enable, [1:0]: Lane 0 FIFO select.
			msWriteByte(REG_1354, 0x05);   //1329~2c[2:0] [2]: DP TX FIFO enable, [1:0]: Lane 0 FIFO select.
			msWriteByte(REG_1356, 0x06);   //1329~2c[2:0] [2]: DP TX FIFO enable, [1:0]: Lane 0 FIFO select.
			msWriteByte(REG_1358, 0x07);   //1329~2c[2:0] [2]: DP TX FIFO enable, [1:0]: Lane 0 FIFO select.
			DPCDWRITEBYTE(0x00, 0x01, 0x01, 0x84); // 4 Lane [7]:Enhance Frame
			break;
	}
	DPTX_printData("DPCD_101=%x_", DPCDREADBYTE(0x00, 0x01, 0x01));
	//DPAUXTest(0x00,0x01,0x00);
	//msWriteByte(0x2303,0x00); //[2]:0: PLL POWER ON [1]: 0:Rterm POWER ON
	//VCO Frequency: {0x2217[5:0], 0x2216[7:0]}*24/1536*80
	//VCO=((msReadByte(0x2217)&0x3F)<<8)+(msReadByte(0x2216)&0xFF);
	//LINKRATE=(VCO*1920*2)/1536;
	//DPTX_printData("DP TX VCO %x",VCO);
	//DPTX_printData("DP TX LinkRate %d",LINKRATE);
//###### Training Pattern 01 ############################
// 1515[9:8] 00: reserved, 01: pattern 1 , 10: pattern 2 , 11: pattern 3
	DPTX_printMsg("[TP01]>>");
//###############################################
	msWriteByte(REG_152B, 0x01); // DP TX SEND P1 PATTERN
	#if FASTTRINING
	for(i = 0; i < 100; i++)
	{
		Delay4us();
	}
	#else
	DPCDWRITEBYTES(0x00, 0x01, 0x03, 0x03, DATA);
	msWriteByte(REG_1390, 0);
	msWriteByte(REG_1391, 0);
	msWriteByte(REG_1392, 0);
	msWriteByte(REG_1393, 0);
	DPCDWRITEBYTE(0x00, 0x01, 0x02, 0x01); // DPCD P1 ENABLE
	//DPAUXTest(0x00,0x02,0x00);                    // Read Status
	//DPTX_printData("DPCD202=%x_",DPCDREADBYTE(0x00,0x02,0x02));
	for(i = 0; i < 100; i++)
	{
		Delay4us();
	}
	#endif
	{
		BYTE xdata V_Level = 0;
		BYTE xdata i = 0, j = 0, k = 0;
		BYTE xdata States = 0;
		BYTE xdata VSwim[4] = {0x00, 0x04, 0x08, 0x0F};
		while(1)
		{
			States = DPTxCheckLockCDR(LaneCnt);
			if(States == FALSE)
			{
				V_Level++;
				if(++j >= 5)
					return  FALSE;
			}
			else
			{
				break;
			}
			//V_Level = (DPCDREADBYTE(0x00,0x02,0x06))&0x03;
			DPTX_printData("V_Level = %x", V_Level);
			for(i = 0; i <= 3; i++)
				DATA[i] = V_Level;
			msWriteByte(REG_1390, VSwim[V_Level]);
			msWriteByte(REG_1391, VSwim[V_Level]);
			msWriteByte(REG_1392, VSwim[V_Level]);
			msWriteByte(REG_1393, VSwim[V_Level]);
			DPCDWRITEBYTES(0x00, 0x01, 0x03, 0x03, DATA);
		}
	}
//###### Training Pattern 02 ############################
// 1515[9:8] 00: reserved, 01: pattern 1 , 10: pattern 2 , 11: pattern 3
	DPTX_printMsg("[TP02]>>");
//###############################################
	msWriteByte(REG_152B, 0x02); // DP TX SEND P2 PATTERN
	#if FASTTRINING
	for(i = 0; i < 100; i++)
	{
		Delay4us();
	}
	#else
	DPCDWRITEBYTE(0x00, 0x01, 0x02, 0x02); // DPCD P2 ENABLE
	for(i = 0; i < 100; i++)
	{
		Delay4us();
	}
	#endif
	Delay1ms(100);
	//DPAUXTest(0x00,0x02,0x00);            // Read Status
	DPTX_printData("DPCD202=%x_", DPCDREADBYTE(0x00, 0x02, 0x02));
// DownSpreading
	/*
	Down spreading: 0x22c8[2] = 0x1
	Span: {0x22c7, 0x22c6} = 0x1ff
	Step: {0x22c5,0x22c4} = 0x10
	Set: {0x22c2, 0x22c1, 0x22c0} = 0x333333
	*/
//###### Disable Training Pattern #########################
// 1515[9:8] 00: reserved, 01: pattern 1 , 10: pattern 2 , 11: pattern 3
	DPTX_printMsg("[DISABLE TP]");
//### Enable DP TX
//       msWriteByte(REG_15D4,0x01); //156A[0] = 1
//###############################################
	DPCDWRITEBYTE(0x00, 0x01, 0x02, 0x00);   // DPCD TRAINING DISABLE
	msWriteByte(REG_152B, 0x00);                        // DP TX DISABLE TRAINING
	DPTX_printMsg("DPCD_200");
	DPAUXTest(0x00, 0x02, 0x00);                     // Read Status
	if(DPTxCheckLock(LaneCnt)) // LOCK OK
	{
		DPTX_printMsg("Training PASS");
		return TRUE;
	}
	else
	{
		DPTX_printMsg("Training Fail");
		return FALSE;
	}
}


//**************************************************************************
//  [Function Name]:
//                  DPTxEDIDRead()
//  [Description]
//                  DPTxEDIDRead
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************

void DPTxEDIDRead(void)
{
	WORD xdata i = 0;
	DPTX_printMsg("DP TX READ EDID!!!");
	DPCDWRITEBYTE1(0x04, 0x00, 0x00, 0x50, 0x00, 0x00, RX_EDID );
	DPCDWRITEBYTE1(0x05, 0x00, 0x00, 0x50, 0x00, 0x0F,  RX_EDID);
	DPCDWRITEBYTE1(0x05, 0x00, 0x00, 0x50, 0x00, 0x0F, (RX_EDID + 0x10));
	DPCDWRITEBYTE1(0x05, 0x00, 0x00, 0x50, 0x00, 0x0F, (RX_EDID + 0x20));
	DPCDWRITEBYTE1(0x05, 0x00, 0x00, 0x50, 0x00, 0x0F, (RX_EDID + 0x30));
	DPCDWRITEBYTE1(0x05, 0x00, 0x00, 0x50, 0x00, 0x0F, (RX_EDID + 0x40));
	DPCDWRITEBYTE1(0x05, 0x00, 0x00, 0x50, 0x00, 0x0F, (RX_EDID + 0x50));
	DPCDWRITEBYTE1(0x05, 0x00, 0x00, 0x50, 0x00, 0x0F, (RX_EDID + 0x60));
	DPCDWRITEBYTE1(0x05, 0x00, 0x00, 0x50, 0x00, 0x0F, (RX_EDID + 0x70));
	//	for(i=0;i<0x80;i++)
	//	{       DPTX_printData(" %x:", i);
	//		  DPTX_printData(" %x",RX_EDID[i]);
	//	}
	#if 0
	if(RX_EDID[0x7E] == 1)
	{
		DPCDWRITEBYTE1(0x05, 0x00, 0x00, 0x50, 0x00, 0x0F, (RX_EDID + 0x80));
		DPCDWRITEBYTE1(0x05, 0x00, 0x00, 0x50, 0x00, 0x0F, (RX_EDID + 0x90));
		DPCDWRITEBYTE1(0x05, 0x00, 0x00, 0x50, 0x00, 0x0F, (RX_EDID + 0xA0));
		DPCDWRITEBYTE1(0x05, 0x00, 0x00, 0x50, 0x00, 0x0F, (RX_EDID + 0xB0));
		DPCDWRITEBYTE1(0x05, 0x00, 0x00, 0x50, 0x00, 0x0F, (RX_EDID + 0xC0));
		DPCDWRITEBYTE1(0x05, 0x00, 0x00, 0x50, 0x00, 0x0F, (RX_EDID + 0xD0));
		DPCDWRITEBYTE1(0x05, 0x00, 0x00, 0x50, 0x00, 0x0F, (RX_EDID + 0xE0));
		DPCDWRITEBYTE1(0x05, 0x00, 0x00, 0x50, 0x00, 0x0F, (RX_EDID + 0xF0));
		//	for(i=0;i<0x80;i++)
		//	{       DPTX_printData(" %x:", i+0x80);
		//		  DPTX_printData(" %x",RX_EDID[i+0x80]);
		//	}
	}
	#endif
}


//**************************************************************************
//  [Function Name]:
//                  DPTxOutputEnable(Bool bEnable)
//  [Description]
//                  DPTxOutputEnable
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void DPTxOutputEnable(Bool bEnable)
{
	if(bEnable)
	{
		DPTX_printMsg("DPTX Enable!");
	}
	else
	{
		DPTX_printMsg("DPTX Disable!");
	}
}
//**************************************************************************
//  [Function Name]:
//                  DPTxCheckLockCDR()
//  [Description]
//                  DPTxCheckLockCDR
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BOOL DPTxCheckLockCDR(BYTE LaneCnt)
{
	BYTE xdata State_1A = 0, State_1B = 0;
	State_1A = DPCDREADBYTE(0x00, 0x02, 0x02);
	State_1B = DPCDREADBYTE(0x00, 0x02, 0x03);
	switch(LaneCnt)
	{
		case DPTX1L:
			if(State_1A == 0x01) // LOCK OK
				return TRUE;
			else
				return FALSE;
			break;
		case DPTX2L:
			if(State_1A == 0x11) // LOCK OK
				return TRUE;
			else
				return FALSE;
			break;
		case DPTX4L:
			if(( State_1A == 0x11) && (State_1B == 0x11)) // LOCK OK
				return TRUE;
			else
				return FALSE;
			break;
		default:
			return FALSE;
			break;
	}
}
//**************************************************************************
//  [Function Name]:
//                  DPTxCheckLock()
//  [Description]
//                  DPTxCheckLock
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BOOL DPTxCheckLock(BYTE LaneCnt)
{
	switch(LaneCnt)
	{
		case DPTX1L:
			if(DPCDREADBYTE(0x00, 0x02, 0x02) == 0x07) // LOCK OK
				return TRUE;
			else
				return FALSE;
			break;
		case DPTX2L:
			if(DPCDREADBYTE(0x00, 0x02, 0x02) == 0x77) // LOCK OK
				return TRUE;
			else
				return FALSE;
			break;
		case DPTX4L:
			if( (DPCDREADBYTE(0x00, 0x02, 0x02) == 0x77) && (DPCDREADBYTE(0x00, 0x02, 0x03) == 0x77)) // LOCK OK
				return TRUE;
			else
				return FALSE;
			break;
		default:
			return FALSE;
			break;
	}
}


//**************************************************************************
//  [Function Name]:
//                  DPTXPrintState(BYTE state)
//  [Description]
//                  DPTXPrintState
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************

void DPTXPrintState(BYTE state)
{
	#if !ENABLE_DEBUG
	state = state;
	#endif
	DPTX_printData(">> DPTX_State %x", state);
	/*
	    switch(state)
	    {
		case eDPTXSTATE_STARTUP:
			DPTX_printMsg("##  DPTX_STARTUP! ##");break;
		case eDPTXSTATE_CHECKEDID:
			DPTX_printMsg("## DPTX_CHECKEDID! ##");break;
		case eDPTXSTATE_TRAINING:
			DPTX_printMsg("## DPTX_TRAINING!##");break;
		case  eDPTXSTATE_CHECKTIMING:
			DPTX_printMsg("## DPTX_CHECKTIMING! ##");break;
		case eDPTXSTATE_NORMAL:
			DPTX_printMsg("## DPTX_NORMAL! ##");break;
		case eDPTXSTATE_POWERSAVE:
			DPTX_printMsg("## DPTX_POWERSAVE! ##");break;
		case eDPTXSTATE_DPIDLE:
			DPTX_printMsg("## DPTX_DPIDLE! ##");break;
	    }
	*/
}


//**************************************************************************
//  [Function Name]:
//                  DPAUX_TEST()
//  [Description]
//                  DPAUX_TEST
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void DPAUX_TEST(void)
{
	BYTE xdata Temp;
	BYTE xdata Address[4] = {0};
	BYTE data i = 0;
	if(msReadByte(REG_15FE) & 0x01)
	{
		Address[0] = msReadByte(REG_15FA);
		Address[1] = msReadByte(REG_15FB);
		Address[2] = msReadByte(REG_15FC);
		Address[3] = msReadByte(REG_15FD);    //Length
		if((Address[0] & 0xF0) == 0x90)
		{
			for(i = 0; i <= Address[3]; i++)
			{
				Temp = DPCDREADBYTE(Address[0], Address[1], Address[2] + i);
				DPTX_printData(">>AUX Data = %x", Temp);
			}
		}
		else if((Address[0] & 0xF0) == 0x80)
		{
			DPCDWRITEBYTE(Address[0], Address[1], Address[2], Address[3] );
		}
		msWriteByte(REG_15FE, 0);
	}
}
//**************************************************************************
//  [Function Name]:
//                  DPTxCheckCRC()
//  [Description]
//                  DPTxCheckCRC
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void DPTxCheckCRC(void)
{
	BYTE xdata Temp[6] = 0;
	BYTE xdata i = 0;
	WORD xdata Time_Out = 0xFFFF;
	msWriteByteMask(REG_1371, BIT0, BIT0);
	DPCDWRITEBYTE(0x00, 0x02, 0x70, 0x01);
	Delay1ms(20);
	while(!(DPCDREADBYTE(0x00, 0x02, 0x46) & 0x0F))
	{
		if((--Time_Out) == 0)
		{
			DPTX_printMsg(" CRC Time Out  ");
			msWriteByteMask(REG_1371, 0, BIT0);
			return;
		}
	}
	if(DPCDREADBYTE(0x00, 0x02, 0x46) & 0x0F)
	{
		AUXREADBYTES(0x90, 0x02, 0x40, 6, Temp);
		for(i = 0; i < 6; i++)
		{
			DPTX_printData("Rx=%x", Temp[i]);
			DPTX_printData("Tx=%x", msReadByte(REG_1374 + i));
		}
	}
	msWriteByteMask(REG_1371, 0, BIT0);
}


//**************************************************************************
//  [Function Name]:
//                  DPRxHandle()
//  [Description]
//                  DPRxHandle
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void DPTxHandle(void)
{
	static BOOL bdp_mute_flag = FALSE;
	HPDSense = msReadByte(REG_138D) & 0x01;
	if(DPTXState != m_DPTXState)
	{
		DPTXPrintState(m_DPTXState);
	}
	DPTXState = m_DPTXState;
	msWriteByte(REG_152C, m_DPTXState);
	switch(m_DPTXState)
	{
		case eDPTXSTATE_STARTUP:             // 0
			DPTxOutputEnable(TRUE);
			gDPTXInfo.bAudioMute = TRUE;
			m_DPTXState = eDPTXSTATE_CHECKEDID;
			break;
		case eDPTXSTATE_CHECKEDID:        // 1
			if(HPDSense == 0x01 && PanelOnFlag/*InputTimingStableFlag*/) // Aaron test
			{
				DPTXCheckCap();
				m_DPTXState = eDPTXSTATE_TRAINING;
			}
			else
			{
				Delay1ms(10);
				m_DPTXState = eDPTXSTATE_CHECKEDID;
			}
			break;
		case eDPTXSTATE_TRAINING:           // 2
			DPTXTraining();
			break;
		case eDPTXSTATE_CHECKTIMING:    // 3
			DPTXSetMSA(eDPTXTiming);
			gDPTXInfo.bReTraining = 0;
			m_DPTXState = eDPTXSTATE_NORMAL;
			break;
		case eDPTXSTATE_NORMAL:             // 4
			DPTX_CheckHPD();
			#if 1
			if(SyncLossState() && ( !bdp_mute_flag) && ( !FreeRunModeFlag))
			{
				bdp_mute_flag = TRUE;
				msWriteByteMask(REG_15D1, BIT0, BIT0); // mute display
				DPTX_printMsg("@DP mute!");
			}
			if(!SyncLossState() && InputTimingStableFlag && bdp_mute_flag && ((msReadByte(REG_3854) == 0xF4) || !(msReadByte(REG_3818)&BIT3)))
			{
				#if EN_FPLL_FASTLOCK
				if( (msReadByte(REG_3854) == 0xF4) && (msReadByte(REG_3818)&BIT3) ) // fpll fast lock
				{
					TimeOutCounter = 250;
					while( (msReadWord(REG_3855) != 0x1F4) && TimeOutCounter);
					msWriteByteMask(REG_38E1, 0, BIT7 | BIT3);
					TimeOutCounter = 250;
					while( (msReadWord(REG_3855) != 0x1F4) && TimeOutCounter);
				}
				#endif
				bdp_mute_flag = FALSE;
				msWriteByteMask(REG_15D1, 0, BIT0); // mute display
				DPTX_printMsg("@DP unmute!");
			}
			#endif
			if( gDPTXInfo.bReTraining)   //CCJ 20110815
			{
				gDPTXInfo.bReTraining = 0;
				m_DPTXState = eDPTXSTATE_CHECKEDID;
			}
			break;
		case eDPTXSTATE_POWERSAVE:      // 5
			break;
		case eDPTXSTATE_DPIDLE:             // 6
			DPTX_CheckHPD();
			break;
		default:
			break;
	}
	HPDSense1T = HPDSense;
}
//**************************************************************************
//  [Function Name]:
//                  DPTXCheckCap()
//  [Description]
//                   DPTXCheckCap()
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void DPTXCheckCap(void)
{
	BYTE xdata RXBUF[12] = {0};
	BYTE xdata i = 0;
	//DPTxEDIDRead();
	Delay1ms(100);   //CCJ  delay to read Aux
	AUXREADBYTES(0x90 | 00, 00, 00, 0x0F, RXBUF);
	for(i = 0; i < 12; i++)
	{
		DPTX_printData("%x", RXBUF[i]);
	}
	gDPTXInfo.bLinkRate = RXBUF[1];
	gDPTXInfo.bLinkLane = RXBUF[2] & 0x0F;
}
//**************************************************************************
//  [Function Name]:
//                  DPTXTraining()
//  [Description]
//                   DPTXTraining()
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void DPTXTraining(void)
{
	BYTE xdata Lane;
	BOOL xdata  Result;
	if(gDPTXInfo.bLinkLane == 1)
		Lane = DPTX1L;
	else  if(gDPTXInfo.bLinkLane == 2)
		Lane = DPTX2L;
	else  if(gDPTXInfo.bLinkLane == 4)
		Lane = DPTX4L;
	while(1)
	{
		if((gDPTXInfo.bLinkRate == 0x0A) || (gDPTXInfo.bLinkRate == 0x14))
		{
			Result = DPTXTrainingFlow(DPTXHBR, Lane);
			if(Result == FALSE)
				gDPTXInfo.bLinkRate = 0x06;
			else
			{
				m_DPTXState = eDPTXSTATE_CHECKTIMING;     //Next State
				return;
			}
		}
		else if(gDPTXInfo.bLinkRate == 0x06)
		{
			Result = DPTXTrainingFlow(DPTXRBR, Lane);
			if(Result == FALSE)
			{
				DPTX_printMsg(" =====> DP TX  Training Fail <====== ");
				m_DPTXState = eDPTXSTATE_DPIDLE;
			}
			else
			{
				m_DPTXState = eDPTXSTATE_CHECKTIMING;	   //Next State
			}
			return;
		}
		else
		{
			DPTXTrainingFlow(DPTXHBR, DPTX4L);
			return;
		}
	}
}
//**************************************************************************
//  [Function Name]:
//                  DPTX_CheckHPD()
//  [Description]
//                   DPTX_CheckHPD()
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void  DPTX_CheckHPD(void)
{
	if(gDPTXInfo.bPlugOut )
	{
		gDPTXInfo.bPlugOut = 0;
		m_DPTXState = eDPTXSTATE_CHECKEDID;
	}
	if(gDPTXInfo.bHPD)
	{
		gDPTXInfo.bHPD = 0;
		if(!DPTxCheckLock(eDPTXMinLane))
		{
			m_DPTXState = eDPTXSTATE_TRAINING;
		}
	}
}
//**************************************************************************
//  [Function Name]:
//                  DPISR_TX()
//  [Description]
//                  DPISR_TX
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void DPISR_TX(void)
{
	if( msRegs[REG_1380] & BIT2 )
	{
		gDPTXInfo.bHPD = 1;
		msRegs[REG_152D] += 1;
		msRegs[REG_1386] = BIT2;
		msRegs[REG_1386] = 0;
	}
	if( msRegs[REG_1380] & BIT1 )
	{
		gDPTXInfo.bPlugOut = 1;
		msRegs[REG_152E] += 1;
		msRegs[REG_1386] = BIT1;
		msRegs[REG_1386] = 0;
	}
}

#else
code BYTE dptxDummyData[1] = {0x00};
void msDpTxDummy()
{
	BYTE x = dptxDummyData;
}
#endif
#endif
