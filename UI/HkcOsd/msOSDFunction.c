#include "global.h"
#include "msosd.h"
#include "drvosd.h"
#include "adjust.h"
// setup osd window size
/*

#define WAIT_V_OUTPUT_BLANKING_START()   { if(!SyncLossState()&&PanelOnFlag){SetTimOutConter(30);while(((msReadByte(SC0_E0)&BIT0)==0)&&bTimeOutCounterFlag);\
                                        SetTimOutConter(30);while(((msReadByte(SC0_E0)&BIT0)!=0)&&bTimeOutCounterFlag);}}//20130227 modify for DC OFF issue
*/
void Osd_SetWindowSize(BYTE width, BYTE height)
{
	OsdWindowWidth = width;
	OsdWindowHeight = height;
	#if CHIP_ID>=CHIP_TSUMV
	//bReset=bReset;
	drvOSD_SetWndLineOffset(OSD_MAIN_WND, OsdWindowWidth); //for OSD_MAIN_WND only
	#if 0//ENABLE_OSD_ROTATION //reset CABase addr after line offset was set
	if (MENU_ROTATION_FLAG)
		drvOSD_SetWndCABaseAddr(OSD_MAIN_WND, GET_CABASE_0_90(OSD_MAIN_WND_CA_BASE, OsdWindowWidth));
	else
		drvOSD_SetWndCABaseAddr(OSD_MAIN_WND, OSD_MAIN_WND_CA_BASE);
	#endif
	#else
	msWriteByte(OSD1_06, OsdWindowWidth - 1);
	msWriteByte(OSD1_07, OsdWindowHeight - 1);
	//if(bReset)
	{
		//msWriteByte(OSD2_A0, 0xDE); // clear osd content
		//ForceDelay1ms(3);
	}
	msWriteByte(OSD2_A0, 0xBE);
	#endif
}

#if CHIP_ID>=CHIP_TSUMV
// setup osd parence
void Osd_SetTransparence(BYTE value)
{
	if(value == 0)
	{
		msWriteByte(OSD2_2C, 0x3F);
		msWriteByte(OSD2_6C, 0x3F);
	}
	else if(value == 1)
	{
		msWriteByte(OSD2_2C, 0x32);
		msWriteByte(OSD2_6C, 0x32);
	}
	else if(value == 2)
	{
		msWriteByte(OSD2_2C, 0x28);
		msWriteByte(OSD2_6C, 0x28);
	}
	else if(value == 3)
	{
		msWriteByte(OSD2_2C, 0x21);
		msWriteByte(OSD2_6C, 0x21);
	}
	else if(value == 4)
	{
		msWriteByte(OSD2_2C, 0x1A);
		msWriteByte(OSD2_6C, 0x1A);
	}
	//msWriteByte(BLENDL, value);
}
#elif CHIP_ID==CHIP_TSUMB
void Osd_SetTransparence(BYTE value)
{
	if(value > 0)
		value = value + 1;
	if(value == 2)
		msWriteByte(OSD2_4A, 0x40 );
	else if(value == 3)
		msWriteByte(OSD2_4A, 0x60 );
	else if(value == 4)
		msWriteByte(OSD2_4A, 0x80 );
	else if(value == 5)
		msWriteByte(OSD2_4A, 0xA0);
	else
		msWriteByte(OSD2_4A, 0x00 );
}

#else
void Osd_SetTransparence(BYTE value)
{
	if(value > 0)
		value = value + 1;
	msWriteByte(REG_2F4C, (0x00 | value) );
}

#endif

// setup
#define MainMenuOSD_Height  	21
#define OSD_TRANSPARENT_SHIFT  	7
#if CHIP_ID>=CHIP_TSUMV
#define OSD_WINDOW(Addr)    ((OSD_MAIN_WND<<5)+Addr)
void Osd_SetPosition( BYTE xPos, BYTE yPos )
{
	#if 0//ENABLE_MENULOAD	//111223 Modify
	WORD  HposValue, VposValue;
	if(PanelWidth < (( WORD )OsdWindowWidth * 12))	//120115 Modify
		HposValue = 0;
	else
		HposValue = (( DWORD )xPos * ( PanelWidth - ( WORD )OsdWindowWidth * 12 ) ) / 100;
	yPos = 100 - yPos;
	VposValue = (( DWORD )yPos * ( PanelHeight - ( WORD )OsdWindowHeight * 18 ) ) / 100;
	if( yPos == 100 && OsdWindowHeight == MainMenuOSD_Height )
		VposValue += OSD_TRANSPARENT_SHIFT;
	if (ucOSDMenuMoveType)
	{
		WORD wTemp = VposValue + ( WORD )OsdWindowHeight * 18;
		mStar_WaitForDataBlanking();
		if (ucOSDMenuMoveType == OSDMoveType_Setting)
		{
			//drvOSD_SetWndVPosition(OSD_MAIN_WND, wTemp, VposValue+( WORD )OsdWindowHeight * 18);
			msML_WaitReady();
			msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_04), HposValue);
			msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_05), HposValue >> 8);
			if(PanelWidth < (( WORD )OsdWindowWidth * 12))	//120115 Modify
			{
				msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_08), (HposValue + PanelWidth));
				msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_09), (HposValue + PanelWidth) >> 8);
			}
			else
			{
				msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_08), (HposValue + ( WORD )OsdWindowWidth * 12));
				msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_09), (HposValue + ( WORD )OsdWindowWidth * 12) >> 8);
			}
			msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_06), wTemp);
			msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_07), wTemp >> 8);
			msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_0A), (VposValue + ( WORD )OsdWindowHeight * 18));
			msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_0B), (VposValue + ( WORD )OsdWindowHeight * 18) >> 8);
			msML_Trigger(ML_TRIG_OUT_VDE_END);// Vde-end-OP
		}
		else if (ucOSDMenuMoveType == OSDMoveType_Main)
		{
			do
			{
				wTemp--;
				Delay1ms(OSDMoveSpeed);
				//drvOSD_SetWndVPosition(OSD_MAIN_WND, wTemp, posValue+( WORD )OsdWindowHeight * 18);
				//msML_WaitReady();
				msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_04), HposValue);
				msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_05), HposValue >> 8);
				if(PanelWidth < (( WORD )OsdWindowWidth * 12))	//120115 Modify
				{
					msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_08), (HposValue + PanelWidth));
					msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_09), (HposValue + PanelWidth) >> 8);
				}
				else
				{
					msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_08), (HposValue + ( WORD )OsdWindowWidth * 12));
					msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_09), (HposValue + ( WORD )OsdWindowWidth * 12) >> 8);
				}
				msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_06), wTemp);
				msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_07), wTemp >> 8);
				msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_0A), (VposValue + ( WORD )OsdWindowHeight * 18));
				msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_0B), (VposValue + ( WORD )OsdWindowHeight * 18) >> 8);
				msML_Trigger(ML_TRIG_OUT_VDE_END);// Vde-end-OP
			}
			while(wTemp != VposValue);
		}
		else if (ucOSDMenuMoveType == OSDMoveType_Root)
		{
			do
			{
				VposValue++;
				Delay1ms(OSDMoveSpeed);
				//drvOSD_SetWndVPosition(OSD_MAIN_WND, posValue, wTemp);
				//msML_WaitReady();
				msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_04), HposValue);
				msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_05), HposValue >> 8);
				if(PanelWidth < (( WORD )OsdWindowWidth * 12))	//120115 Modify
				{
					msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_08), (HposValue + PanelWidth));
					msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_09), (HposValue + PanelWidth) >> 8);
				}
				else
				{
					msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_08), (HposValue + ( WORD )OsdWindowWidth * 12));
					msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_09), (HposValue + ( WORD )OsdWindowWidth * 12) >> 8);
				}
				msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_06), VposValue);
				msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_07), VposValue >> 8);
				msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_0A), wTemp);
				msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_0B), wTemp >> 8);
				msML_Trigger(ML_TRIG_OUT_VDE_END);// Vde-end-OP
			}
			while(wTemp != VposValue);
		}
	}
	else
	{
		#if CHIP_ID==CHIP_TSUMV
		mStar_WaitForDataBlanking();
		#endif
		msML_WaitReady();
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_04), HposValue);
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_05), HposValue >> 8);
		if(PanelWidth < (( WORD )OsdWindowWidth * 12))	//120115 Modify
		{
			msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_08), (HposValue + PanelWidth));
			msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_09), (HposValue + PanelWidth) >> 8);
		}
		else
		{
			msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_08), (HposValue + ( WORD )OsdWindowWidth * 12));
			msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_09), (HposValue + ( WORD )OsdWindowWidth * 12) >> 8);
		}
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_06), VposValue);
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_07), VposValue >> 8);
		{
			msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_0A), (VposValue + ( WORD )OsdWindowHeight * 18));
			msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW(OSD2_0B), (VposValue + ( WORD )OsdWindowHeight * 18) >> 8);
		}
		msML_Trigger(ML_TRIG_OUT_VDE_END);// Vde-end-OP
	}
	mStar_WaitForDataBlanking();   // 20111226 Nick for input select Item OSD issue
	#elif ENABLE_SW_DOUBLE_BUFFER
	WORD HposValue, VposValue;
	if(PanelWidth < (( WORD )OsdWindowWidth * 12)) //120115 Modify
		HposValue = 0;
	else
		HposValue = (( DWORD )xPos * ( PanelWidth - ( WORD )OsdWindowWidth * 12 ) ) / 100;
	yPos = 100 - yPos;
	VposValue = (( DWORD )yPos * ( PanelHeight - ( WORD )OsdWindowHeight * 18 ) ) / 100;
	if( yPos == 100 && OsdWindowHeight == MainMenuOSD_Height )
		VposValue += OSD_TRANSPARENT_SHIFT;
	{
		//msSWDBWaitForRdy();
		DB_Mode(eDB_NORMAL_MODE);
		DB_WB(OSD_WINDOW(OSD2_04), HposValue);
		DB_WB(OSD_WINDOW(OSD2_05), HposValue >> 8);
		if(PanelWidth < (( WORD )OsdWindowWidth * 12)) //120115 Modify
		{
			DB_WB(OSD_WINDOW(OSD2_08), (HposValue + PanelWidth));
			DB_WB(OSD_WINDOW(OSD2_09), (HposValue + PanelWidth) >> 8);
		}
		else
		{
			DB_WB(OSD_WINDOW(OSD2_08), (HposValue + ( WORD )OsdWindowWidth * 12));
			DB_WB(OSD_WINDOW(OSD2_09), (HposValue + ( WORD )OsdWindowWidth * 12) >> 8);
		}
		DB_WB(OSD_WINDOW(OSD2_06), VposValue);
		DB_WB(OSD_WINDOW(OSD2_07), VposValue >> 8);
		DB_WB(OSD_WINDOW(OSD2_0A), (VposValue + ( WORD )OsdWindowHeight * 18));
		DB_WB(OSD_WINDOW(OSD2_0B), (VposValue + ( WORD )OsdWindowHeight * 18) >> 8);
		#if CHIP_ID==CHIP_TSUMF // TSUMF no VDE end trig source, instead by OSD_VDE_End sw polling & trigger
		msSWDBWriteToRegisterByOsdEnd();
		#else
		msSWDBWriteToRegister();
		#endif
		msSWDBWaitForRdy();
	}
	//mStar_WaitForDataBlanking();   // 20111226 Nick for input select Item OSD issue
	#else
	WORD posValue;
	if(PanelWidth < (( WORD )OsdWindowWidth * 12))	//120115 Modify
		posValue = 0;
	else
		posValue = (( DWORD )xPos * ( PanelWidth - ( WORD )OsdWindowWidth * 12 ) ) / 100;
	//mStar_WaitForDataBlanking();                //110901 Rick add for avoid the garbage while change osd position
	if(PanelWidth < (( WORD )OsdWindowWidth * 12))	//120115 Modify
		drvOSD_SetWndHPosition(OSD_MAIN_WND, posValue, posValue + PanelWidth );
	else
		drvOSD_SetWndHPosition(OSD_MAIN_WND, posValue, posValue + ( WORD )OsdWindowWidth * 12);
	yPos = 100 - yPos;
	posValue = (( DWORD )yPos * ( PanelHeight - ( WORD )OsdWindowHeight * 18 ) ) / 100;
	// 100811 coding addition for main menu osd
	if( yPos == 100 && OsdWindowHeight == MainMenuOSD_Height )
		posValue += OSD_TRANSPARENT_SHIFT;
	//mStar_WaitForDataBlanking();                //110901 Rick add for avoid the garbage while change osd position
	if (ucOSDMenuMoveType)
	{
		WORD wTemp = posValue + ( WORD )OsdWindowHeight * 18;
		mStar_WaitForDataBlanking();
		if (ucOSDMenuMoveType == OSDMoveType_Setting)
		{
			drvOSD_SetWndVPosition(OSD_MAIN_WND, wTemp, posValue + ( WORD )OsdWindowHeight * 18);
		}
		else if (ucOSDMenuMoveType == OSDMoveType_Main)
		{
			do
			{
				wTemp--;
				Delay1ms(OSDMoveSpeed);
				drvOSD_SetWndVPosition(OSD_MAIN_WND, wTemp, posValue + ( WORD )OsdWindowHeight * 18);
			}
			while(wTemp != posValue);
		}
		else if (ucOSDMenuMoveType == OSDMoveType_Root)
		{
			do
			{
				posValue++;
				Delay1ms(OSDMoveSpeed);
				drvOSD_SetWndVPosition(OSD_MAIN_WND, posValue, wTemp);
			}
			while(wTemp != posValue);
		}
	}
	else
		drvOSD_SetWndVPosition(OSD_MAIN_WND, posValue, posValue + ( WORD )OsdWindowHeight * 18);
	#endif
}
#else
#define ScalingDown_PIPESHIFT    10
WORD drvOsdGetPipeDelay( void )
{
	WORD  xdata OPBackPorch;
	BYTE  xdata PIPESHIFT;
	PIPESHIFT = msReadByte( OSD1_4B );
	OPBackPorch = msRead2Byte(SC0_12);
	//if(g_SetupPathInfo.bScalingUpV)
	#if CHIP_ID == CHIP_TSUMY      //111005 Rick modified OSD Position formula - A041
	OPBackPorch = (PIPESHIFT - OPBackPorch - 23); //*2;
	#elif CHIP_ID == CHIP_TSUMB
	#if ENABLE_RTE           //120417 Rick modified pipedelay value while enable OSD2_4B[7]
	OPBackPorch = (PIPESHIFT - OPBackPorch - 35 - 50); //*2;
	#else
	OPBackPorch = (PIPESHIFT - OPBackPorch - 35); //*2;
	#endif
	#else
	OPBackPorch = (PIPESHIFT - OPBackPorch - 38) * 2;
	#endif
	//else
	//OPBackPorch=(PIPESHIFT-OPBackPorch-38+ScalingDown_PIPESHIFT)*2;
	return OPBackPorch;
}

#define OSDFlyPos       11*18	//120830 Modify
void Osd_SetPosition( BYTE xPos, BYTE yPos )
{
	WORD  xdata posValue;
	BYTE xdata wOSDFlyPos = 0; 	//120830 Modify
	#if DoubleXSize
	posValue = (( DWORD )xPos * ( PanelWidth - ( WORD )OsdWindowWidth * 12 * 2 ) ) / 100 + ( ( PanelHStart / PANEL_H_DIV ) - 48 );
	#else
	posValue = (( DWORD )xPos * ( PanelWidth - ( WORD )OsdWindowWidth * 12 ) ) / 100 - drvOsdGetPipeDelay(); //);
	#endif
	msWriteByte( OSD1_02, posValue & 0xFF );
	msWriteByte( OSD1_03, posValue >> 8 );
	posValue = ( PanelWidth - ( WORD )OsdWindowWidth * 12 ) - 4;
	msWriteByte( OSD2_0A, posValue & 0xFF );
	msWriteByte( OSD2_0B, (msReadByte(OSD2_0B) & 0x80) | (posValue >> 8) );
	yPos = 100 - yPos;
	#if DoubleYSize
	posValue = (( DWORD )yPos * ( PanelHeight - ( WORD )OsdWindowHeight * 18 * 2 ) ) / 100;
	#else
	posValue = (( DWORD )yPos * ( PanelHeight - ( WORD )OsdWindowHeight * 18 ) ) / 100;
	#endif
	// 100811 coding addition for main menu osd
	if( yPos == 100 && OsdWindowHeight == MainMenuOSD_Height )
		posValue += OSD_TRANSPARENT_SHIFT;
	//120830 Modify
	if ((ucOSDMenuMoveType == OSDMoveType_Main)
	        || (ucOSDMenuMoveType == OSDMoveType_Root))
	{
		wOSDFlyPos = OSDFlyPos;
	}
	if (wOSDFlyPos)
	{
		//BYTE ucTemp= msReadByte(OSD1_01);
		WORD wTemp;
		while(wOSDFlyPos)
		{
			//msWriteByte( OSD1_01, 0x01 );
			//printData("-- wOSDFlyPos[0x%x]", wOSDFlyPos);
			//if (wOSDFlyPos%18 == 1)
			//    mStar_WaitForDataBlanking();
			//Delay1ms(OSDMoveSpeed);
			if (wOSDFlyPos % 18 == 1)
			{
				Delay1ms(OSDMoveSpeed);
				#if CHIP_ID == CHIP_TSUMY
				WAIT_V_OUTPUT_BLANKING_START();
				#else
				mStar_WaitForDataBlanking();
				#endif
			}
			if (ucOSDMenuMoveType == OSDMoveType_Root)
			{
				wTemp = ( posValue + (OSDFlyPos - wOSDFlyPos));
				// 0x0FF-->0x100
				msWriteByte( OSD1_04, wTemp & 0xFF );
				msWriteByte( OSD1_05, wTemp >> 8 );
				if (wOSDFlyPos < 0x12)
				{
					msWriteByte( OSD1_07, 0x01 );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0x24)
				{
					msWriteByte( OSD1_07, 0x02 );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0x36)
				{
					msWriteByte( OSD1_07, 0x03 );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0x48)
				{
					msWriteByte( OSD1_07, 0x04 );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0x5A)
				{
					msWriteByte( OSD1_07, 0x05 );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0x6C)
				{
					msWriteByte( OSD1_07, 0x06 );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0x7E)
				{
					msWriteByte( OSD1_07, 0x07 );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0x90)
				{
					msWriteByte( OSD1_07, 0x08 );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0xA2)
				{
					msWriteByte( OSD1_07, 0x09 );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0xB4)
				{
					msWriteByte( OSD1_07, 0x0A );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos <= 0xC6)
				{
					msWriteByte( OSD1_07, 0x0B );		//110317 Modify for the garbage on the bottom
				}
			}
			else if (ucOSDMenuMoveType == OSDMoveType_Main)
			{
				wTemp = ( posValue + wOSDFlyPos);
				// 0x100-->0x0FF
				msWriteByte( OSD1_04, wTemp & 0xFF );
				msWriteByte( OSD1_05, wTemp >> 8 );
				if (wOSDFlyPos == 0x01)
				{
					msWriteByte( OSD1_07, 0x0B );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0x12)
				{
					msWriteByte( OSD1_07, 0x0B );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0x24)
				{
					msWriteByte( OSD1_07, 0x0A );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0x36)
				{
					msWriteByte( OSD1_07, 0x09 );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0x48)
				{
					msWriteByte( OSD1_07, 0x08 );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0x5A)
				{
					msWriteByte( OSD1_07, 0x07 );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0x6C)
				{
					msWriteByte( OSD1_07, 0x06 );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0x7E)
				{
					msWriteByte( OSD1_07, 0x05 );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0x90)
				{
					msWriteByte( OSD1_07, 0x04 );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0xA2)
				{
					msWriteByte( OSD1_07, 0x03 );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos < 0xB4)
				{
					msWriteByte( OSD1_07, 0x02 );		//110317 Modify for the garbage on the bottom
				}
				else if (wOSDFlyPos <= 0xC6)
				{
					msWriteByte( OSD1_07, 0x01 );		//110317 Modify for the garbage on the bottom
				}
			}
			wOSDFlyPos--;
			//msWriteByte( OSD1_01, 0x03 );
		}
		//msWriteByte( OSD1_01, 0x01 );
		// 0x100-->0x0FF
		// if ( (posValue == 0x0FF || posValue == 0x1FF || posValue == 0x2FF)
		// 0x0FF-->0x100
		//     ||(posValue == 0x100 || posValue == 0x200 || posValue == 0x300))
		{
			// mStar_WaitForDataBlanking();
		}
		msWriteByte( OSD1_04, wTemp & 0xFF );
		msWriteByte( OSD1_05, wTemp >> 8 );
		//msWriteByte( OSD1_01, ucTemp );
		ucOSDMenuMoveType = OSDMoveType_Ini;
	}
	else
	{
		msWriteByte( OSD1_04, posValue & 0xFF );
		msWriteByte( OSD1_05, posValue >> 8 );
	}
}

#endif

void Osd_Show(void)
{
	#if CHIP_ID>=CHIP_TSUMV
	Delay1ms(20);	//111223 Modify
	drvOSD_SetWndOn(OSD_MAIN_WND, TRUE);
	#if HotInputSelect
	if(MenuPageIndex == HotInputSelectMenu)// 20130523 miff only for hotinputselectMenu garbage & show gradationally.
		drvOSD_SetWndOn(OSD_CURSOR_WND, TRUE);
	#endif
	#else
	BYTE u8RegByte;
	u8RegByte = (DoubleXSize << 4) | (DoubleYSize << 6) | MWIN_B; //|0x8
	#if 0//ENABLE_OSD_ROTATION
	if (MENU_ROTATION_FLAG
        #if ENABLE_COLOR_DEMO_MODE
	        && g_u8MenuPageIndex != MENU_ROOT
        #endif
	   )
		u8RegByte |= BIT1; //rotation bit
	#endif
	msWriteByte(OSD1_0C, u8RegByte);
	#endif
	#if defined(DCRClearBacklight)
	if((MenuPageIndex == AutoMenu || MenuPageIndex == MainMenu) && UserPrefDcrMode)
	{
		if(!BackLightActiveFlag)
			hw_SetBlacklit();
	}
	#endif
}

void Osd_Hide(void)
{
	#if CHIP_ID>=CHIP_TSUMV
	drvOSD_SetWndOn(OSD_MAIN_WND, FALSE);
	drvOSD_SetWndOn(OSD_CURSOR_WND, FALSE);
	#else
	#if DEBUG_OSD
	msWriteByte( IOSDC1, ( DoubleXSize << 4 ) | ( DoubleYSize << 6 ) | MWIN_B );
	#else
	msWriteByte( IOSDC1, 0x00 );
	#endif
	#endif
}

#if 1
extern xdata BYTE OsdFontColor  ;
extern BYTE  xdata MenuPageIndex ;


#if 0
#define OSD_WINDOW_ADDR(OsdWND,Addr)    ((OsdWND<<5)+Addr)
void SetOSDWindosw(BYTE ucSubWin, BYTE u8HStart, BYTE u8HEnd, BYTE u8VStart, BYTE u8VEnd, BYTE u8Color)
{
	#if CHIP_ID>=CHIP_TSUMV
	// WAIT_V_OUTPUT_BLANKING_START(); //Jison wait 1 frame to avoid the last text garbage
	//drvOSD_SetWndOn(ucSubWin, FALSE);
	{
		WORD xdata u16MainHStart = drvOSD_GetWndInfo(OSD_MAIN_WND, OSD_WND_INFO_H_START);
		WORD xdata u16MainVStart = drvOSD_GetWndInfo(OSD_MAIN_WND, OSD_WND_INFO_V_START);
		if (bMoveCURSORFlag)
		{
			drvOSD_SetWndCABaseAddr(ucSubWin, 0x046);//clear
			WAIT_V_OUTPUT_BLANKING_START();
		}
		else
			drvOSD_SetWndCABaseAddr(ucSubWin, drvOSD_GetWndInfo(OSD_MAIN_WND, OSD_WND_INFO_CABASE) +
			                        (WORD)u8VStart * drvOSD_GetWndInfo(OSD_MAIN_WND, OSD_WND_INFO_LINE_OFFSET) + u8HStart);
		#if ENABLE_MENULOAD	//111223 Modify
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW_ADDR(ucSubWin, OSD2_04), (u16MainHStart + (WORD)u8HStart * 12));
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW_ADDR(ucSubWin, OSD2_05), (u16MainHStart + (WORD)u8HStart * 12) >> 8);
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW_ADDR(ucSubWin, OSD2_08), (u16MainHStart + ((WORD)u8HEnd + 1) * 12));
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW_ADDR(ucSubWin, OSD2_09), (u16MainHStart + ((WORD)u8HEnd + 1) * 12) >> 8);
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW_ADDR(ucSubWin, OSD2_06), (u16MainVStart + (WORD)u8VStart * 18));
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW_ADDR(ucSubWin, OSD2_07), (u16MainVStart + (WORD)u8VStart * 18) >> 8);
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW_ADDR(ucSubWin, OSD2_0A), (u16MainVStart + ((WORD)u8VEnd + 1) * 18));
		msML_WriteByte(ML_MODE_NORMAL, OSD_WINDOW_ADDR(ucSubWin, OSD2_0B), (u16MainVStart + ((WORD)u8VEnd + 1) * 18) >> 8);
		msML_Trigger(ML_TRIG_SW);// Vde-end-OP

		#elif ENABLE_SW_DOUBLE_BUFFER
		//msSWDBWaitForRdy();
		DB_Mode(ML_MODE_NORMAL);
		DB_WB(OSD_WINDOW_ADDR(ucSubWin, OSD2_04), (u16MainHStart + (WORD)u8HStart * 12));
		DB_WB(OSD_WINDOW_ADDR(ucSubWin, OSD2_05), (u16MainHStart + (WORD)u8HStart * 12) >> 8);
		DB_WB(OSD_WINDOW_ADDR(ucSubWin, OSD2_08), (u16MainHStart + ((WORD)u8HEnd + 1) * 12));
		DB_WB(OSD_WINDOW_ADDR(ucSubWin, OSD2_09), (u16MainHStart + ((WORD)u8HEnd + 1) * 12) >> 8);
		DB_WB(OSD_WINDOW_ADDR(ucSubWin, OSD2_06), (u16MainVStart + (WORD)u8VStart * 18));
		DB_WB(OSD_WINDOW_ADDR(ucSubWin, OSD2_07), (u16MainVStart + (WORD)u8VStart * 18) >> 8);
		DB_WB(OSD_WINDOW_ADDR(ucSubWin, OSD2_0A), (u16MainVStart + ((WORD)u8VEnd + 1) * 18));
		DB_WB(OSD_WINDOW_ADDR(ucSubWin, OSD2_0B), (u16MainVStart + ((WORD)u8VEnd + 1) * 18) >> 8);
		msSWDBWriteToRegister();
		msSWDBWaitForRdy();
		#else
		drvOSD_SetWndHPosition(ucSubWin, u16MainHStart + (WORD)u8HStart * 12, u16MainHStart + ((WORD)u8HEnd + 1) * 12);
		drvOSD_SetWndVPosition(ucSubWin, u16MainVStart + (WORD)u8VStart * 18, u16MainVStart + ((WORD)u8VEnd + 1) * 18);
		#endif
	}
	drvOSD_SetWndFixAttr(ucSubWin, _ENABLE, u8Color);
	//WAIT_V_OUTPUT_BLANKING_START(); //Jison wait 1 frame to avoid the last text garbage
	#if HotInputSelect
	if(MenuPageIndex != HotInputSelectMenu)// 20130523 miff only for hotinputselectMenu garbage & show gradationally.
	#endif
		WAIT_V_OUTPUT_BLANKING_START();//fay 20131218
	drvOSD_SetWndOn(ucSubWin, TRUE);
	#else    // Wind as 0 ~3
	if (OSD_CURSOR_WND == ucSubWin)
		ucSubWin = SUB_WIN_00;
	ucSubWin = SUBW0C + ucSubWin * 6;
	mStar_WriteOSDByte(ucSubWin + 1, u8HStart);
	mStar_WriteOSDByte(ucSubWin + 2, u8HEnd);
	mStar_WriteOSDByte(ucSubWin + 3, u8VStart);
	mStar_WriteOSDByte(ucSubWin + 4, u8VEnd);
	mStar_WriteOSDByte(ucSubWin + 5, u8Color);
	if ((ucSubWin | BKMASKOSD1) == SUBW1C)
		mStar_WriteOSDByte(ucSubWin + 0, 0x03);
	else
		mStar_WriteOSDByte(ucSubWin + 0, 0x01);
	#endif
}

void ClrOSDWindosw(BYTE ucSubWin)
{
	#if CHIP_ID>=CHIP_TSUMV
	drvOSD_SetWndOn(ucSubWin, FALSE);
	#else
	// Wind as 0 ~3
	if (OSD_CURSOR_WND == ucSubWin)
		ucSubWin = SUB_WIN_00;
	ucSubWin = SUBW0C + ucSubWin * 6;
	mStar_WriteOSDByte(ucSubWin + 0, 0x00);
	mStar_WriteOSDByte(ucSubWin + 1, 0x00);
	mStar_WriteOSDByte(ucSubWin + 2, 0x00);
	mStar_WriteOSDByte(ucSubWin + 3, 0x00);
	mStar_WriteOSDByte(ucSubWin + 4, 0x00);
	mStar_WriteOSDByte(ucSubWin + 5, 0x00);
	#endif
}
#endif
BYTE Osd_DoubleBuffer(Bool u8Enable)
{
	#if CHIP_ID>=CHIP_TSUMV
	u8Enable = 0;
	return u8Enable;
	#else
	BYTE u8Org = msReadByte(OSD1_01);
	msWriteByte(OSD1_01, (u8Enable ? 0x05 : 0));
	return (u8Org);
	#endif
}

#if 1
void Osd_SetTextMonoColor(BYTE foreColor, BYTE backColor)
{
	OsdFontColor = (foreColor & 0xF) << 4 | (backColor & 0xF);
}
void Osd_SetTextColor(BYTE foreColor, BYTE backColor)
{
	// OsdFontColor=(foreColor&0xF)<<4|(backColor&0xF);
	OsdFontColor = (foreColor & 0x0) | (backColor & 0xFF);
}
void Osd_Set256TextColor(BYTE foreColor, BYTE backColor)
{
	if(backColor == Color_2)
		OsdFontColor = foreColor;
	else if(backColor == Color_2G)
	{
		#if CHIP_ID>=CHIP_TSUMV
		OsdFontColor = (foreColor & 0xF0) | 0x01;
		#else
		OsdFontColor = foreColor;
		#endif
	}
	else if(backColor == Color_4)
		OsdFontColor = foreColor << 2;
	else if(backColor == Color_8)
		OsdFontColor = foreColor << 3;
	else if(backColor == Color_8G)
		OsdFontColor = (foreColor << 3) | BIT1;
	else if(backColor == Color_2T)
		OsdFontColor = foreColor | 0x00;
	else if(backColor == Color_4T)
		OsdFontColor = foreColor << 2 | 0x01;
	else// (backColor==Color_8T)
		OsdFontColor = foreColor << 3 | 0x01;
}
#endif

#if 0//CHIP_ID<CHIP_TSUMV
void SetOsdGraduallyBackGround( BYTE Win_Num, BYTE GDRValue, BYTE GDGValue, BYTE GDBValue, BYTE GDDelta, BYTE GDDERange, BYTE GDControl, BYTE GDRInit, BYTE GDGInit, BYTE GDBInit)
{
	if (Win_Num > 4) return;
	switch (Win_Num)
	{
		case SUB_WIN_00:
			Win_Num = OSD_GD00;
			break;
		case SUB_WIN_01:
			Win_Num = OSD_GD01;
			break;
		case SUB_WIN_02:
			Win_Num = OSD_GD02;
			break;
		case SUB_WIN_03:
			Win_Num = OSD_GD03;
			break;
	}
	mStar_WriteOSDByte( Win_Num + 0, GDRValue);
	mStar_WriteOSDByte( Win_Num + 1, GDGValue );
	mStar_WriteOSDByte( Win_Num + 2, GDBValue );
	mStar_WriteOSDByte( Win_Num + 3, GDDelta );
	mStar_WriteOSDByte( Win_Num + 4, GDDelta );
	mStar_WriteOSDByte( Win_Num + 5, GDDERange );
	mStar_WriteOSDByte( Win_Num + 6, GDDERange );
	mStar_WriteOSDByte( Win_Num + 7, GDDERange );
	mStar_WriteOSDByte( Win_Num + 8, GDDERange );
	mStar_WriteOSDByte( Win_Num + 9, GDControl );
	mStar_WriteOSDByte( Win_Num + 10, GDRInit );
	mStar_WriteOSDByte( Win_Num + 11, GDGInit );
	mStar_WriteOSDByte( Win_Num + 12, GDBInit );
}
#endif


#endif

