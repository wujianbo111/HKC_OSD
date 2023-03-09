#include "types.h"
#include "Common.h"
#include "debugDef.h"
#include "board.h"
#include "global.h"
#include "ms_reg.h"
#include "ms_rwreg.h"
#include "msosd.h"
#include "NVRam.h"
#include "i2c.h"
#include "misc.h"
#include "adjust.h"
#include "userPref.h"
#include "autofunc.h"
#include "menudef.h"
#include "menufunc.h"
#include "msace.h"
#include "msdlc.h"
#include "msflash.h"
#include "keypaddef.h"
#include "mcu.h"
#include "power.h"
#include "GPIO_DEF.h"
//BYTE SIORxBuffer[4];
#include "gamma.h"
#include "drvgpio.h"





#if ENABLE_DEBUG
#if  ENABLE_DEBUG&&CHIP_ID==CHIP_TSUM2// 120403 coding, addition for eland uart debug
extern void ElandWriteWord (WORD waddr, WORD wdata);
extern WORD ElandReadWord (WORD waddr);
extern BYTE ElandReadHalfWord(WORD ucaddr);
extern Bool ElandWriteHalfWord (WORD ucaddr, BYTE ucdata);
extern void mhal_mhl_SetHPD(Bool bflag);
extern Bool ElandWriteWordMask(WORD reg, WORD val, WORD mask);
#endif
#endif
#define DEBUG_Massage    0
#if ENABLE_DEBUG&&DEBUG_Massage
#define DB_printData(str, value)   printData(str, value)
#define DB_printMsg(str)           printData(str, 1)
#else
#define DB_printData(str, value)
#define DB_printMsg(str)
#endif

BYTE xdata SIORxIndex = 0;
BYTE xdata ReSyncCounter;
//void printData(char *str, WORD value);
//void printMsg(char *str);
//void putSIOChar(unsigned char sendData);
//BYTE xdata pReg[123];
extern Bool xdata bFlashWriteFactory;
#if DEBUG_VIRTUAL_KEY
BYTE xdata KeyDebug = 0xFF;
#endif
#if Enable_Gamma
//extern void mStar_InitGamma(void);
#endif
extern void Power_PowerOffSystem(void);
extern BYTE OT_WriteI2C(BYTE I2CAddr7Bit, BYTE *Buffer, BYTE BytesToSend);
extern BYTE OT_ReadI2C(BYTE I2CAddr7Bit, BYTE *Buffer, BYTE BytesToRead);
#if 1//ndef WH_REQUEST
BYTE AOCAlign(void);
#endif
#if ENABLE_HDCP
#if HDCPKEY_IN_Flash
extern WORD CRC16(BYTE nData, WORD nCRC);
#endif
#endif

extern Bool NVRAM_i2c_SendByte(BYTE value);
extern Bool ExecuteKeyEvent(MenuItemActionType menuAction);
#if DEBUG_SELFTEST
#define FailAddr(Addr)     printData(#Addr" Fail[0x%x]", Addr)
#define READ_LVDS_SSC_STEP() (msRead2Byte(REG_382E))
#define READ_LVDS_SSC_SPAN() (msRead2Byte(REG_3830))
#define READ_LPLL_SET() (((DWORD)msReadByte(REG_3820)<<16)|msRead2Byte(REG_381E))
#define SSC_MODULATION()    ((float)429ul*1024ul*131072ul/READ_LVDS_SSC_SPAN()/READ_LPLL_SET())
#define SSC_PERCENTAGE()    ((float)READ_LVDS_SSC_STEP()*READ_LVDS_SSC_SPAN()*1000ul/READ_LPLL_SET())

void SelfTest(void)
{
	WORD wval;
	#if 0
	if(PanelTypeNumAddr <= ProductModeAddr)
		FailAddr(PanelTypeNumAddr);
	if(PanelSettingAddr <= PanelTypeNumAddr)
		FailAddr(PanelSettingAddr);
	if(FactorySettingAddr <= PanelSettingAddr)
		FailAddr(FactorySettingAddr);
	#else
	if(FactorySettingAddr <= ProductModeAddr)
		FailAddr(FactorySettingAddr);
	#endif
	if(MonitorSettingAddr <= FactorySettingAddr)
		FailAddr(MonitorSettingAddr);
	if(ModeSettingAddr <= MonitorSettingAddr)
		FailAddr(ModeSettingAddr);
	if(ModeInfoAddr <= ModeSettingAddr)
		FailAddr(ModeInfoAddr);
	if(EndAddr <= ModeSettingAddr)
		FailAddr(EndAddr);
	if(BlacklitTimeAddr <= EndAddr)
		FailAddr(BlacklitTimeAddr);
	if(CheckBoardAddr <= BlacklitTimeAddr)
		FailAddr(CheckBoardAddr);
	//printMsg("===EEPROM FINISH===");
	wval = SSC_MODULATION();
	if(wval > PANEL_SSC_MODULATION_DEF)
		printData("SSC Fail Over40K:%d", wval);
	wval = SSC_PERCENTAGE();
	if(wval > PANEL_SSC_PERCENTAGE_DEF)
		printData("SSC Fail Over2:%d", wval);
	// printMsg("===LVDS SSC FINISH===");
}
#endif
void ExecTestCommand( void )
{
	BYTE ucTest = 0;
	BYTE ucPara1 = SIORxBuffer[2];
	BYTE ucPara2 = SIORxBuffer[3];
	BYTE ucPara3 = SIORxBuffer[4];
	switch( SIORxBuffer[1] )
	{
		case 0x01:
			MenuPageIndex = RootMenu;
			MenuItemIndex = 0;
			ExecuteKeyEvent(MIA_RedrawMenu);
			break;
		case 0x02:
			MenuPageIndex = RootMenu;
			MenuItemIndex = 0;
			ExecuteKeyEvent(MIA_RedrawMenu);
			break;
		case 0x10:
		{
			DB_printData("DB_MenuPageIndex:%d", MenuPageIndex);
			DB_printData("DB_SrcInputType:%d", SrcInputType);
			DB_printData("DB_OsdCounter:%d", OsdCounter);
			DB_printData("DB_OsdTimeoutFlag:%d", OsdTimeoutFlag);
			break;
		}
		#if Enable_Expansion
		case 0x09:
		{
			// AdjustExpansionMode(0);
			break;
		}
		#endif
		case 0x50:
			if( DebugOnlyFlag )
			{
				Clr_DebugOnlyFlag();
				DB_printMsg( "<Free>");
			}
			else
			{
				Set_DebugOnlyFlag();
				DB_printMsg( "<Debug>");
			}
			break;
			#if DEBUG_SELFTEST
		case 0x99:
		{
			SelfTest();
			break;
		}
		#endif
		#if DEBUG_VIRTUAL_KEY
		case 0x63: // Keypad_Enter
			KeyDebug = KEY_EXIT;
			printMsg("KEY_EXIT");
			break;
		case 0x72: // Keypad_LEFT
			KeyDebug = KEY_MINUS;
			printMsg("KEY_MINUS");
			break;
		case 0x73: // Keypad_MENU
			KeyDebug = KEY_MENU;
			printMsg("KEY_MENU");
			break;
		case 0x74: // Keypad_RIGHT
			KeyDebug = KEY_PLUS;
			printMsg("KEY_PLUS");
			break;
		case 0x76: // Keypad_POWER
			KeyDebug = KEY_POWER;
			printMsg("KEY_POWER");
			break;
			#endif
	}
}

void ProcessCommand(void)
{
	switch( UART_CMD )
	{
		case kWrite_MST_Bank_n:
		{
			#if ENABLE_MHL && ENABLE_DEBUG&&CHIP_ID==CHIP_TSUM2// 120403 coding, addition for eland uart debug
			if(UART_CMD_MS_BANK & 0x80)
			{
				//ElandWriteHalfWord((UART_CMD_MS_BANK & 0x0F) << 8|UART_CMD_MS_REGINDEX, UART_CMD_MS_REGDATA);
			}
			else
			#endif
			{
				const volatile BYTE ucBank = scReadByte( SC0_00 ); // store original bank
				scWriteByte( SC0_00, UART_CMD_MS_BANK );
				scWriteByte( UART_CMD_MS_REGINDEX, UART_CMD_MS_REGDATA );
				scWriteByte( SC0_00, ucBank ); // restore original bank
			}
			putSIOChar( 0xF1 );
			break;
		}
		case kRead_MST_Bank_n:
		{
			#if ENABLE_MHL && ENABLE_DEBUG&&CHIP_ID==CHIP_TSUM2// 120403 coding, addition for eland uart debug
			if(UART_CMD_MS_BANK & 0x80)
			{
				UART_CMD_MS_REGDATA = ElandReadHalfWord((UART_CMD_MS_BANK & 0x0F) << 8 | UART_CMD_MS_REGINDEX);
			}
			else
			#endif
			{
				const volatile BYTE ucBank = scReadByte( SC0_00 ); // store original bank
				scWriteByte( SC0_00, UART_CMD_MS_BANK );
				UART_CMD_MS_REGDATA = scReadByte( UART_CMD_MS_REGINDEX );
				scWriteByte( SC0_00, ucBank ); // restore original bank
			}
			putSIOChar( 0xF2 );
			putSIOChar( UART_CMD_MS_REGDATA );
			break;
		}
		case kWrite_MCU_XDATA:
		{
			msWriteByte( MAKEWORD( UART_CMD_MCU_IDX_H, UART_CMD_MCU_IDX_L ), UART_CMD_MCU_DATA );
			putSIOChar( 0xF1 );
			break;
		}
		case kRead_MCU_XDATA:
		{
			UART_CMD_MCU_DATA = msReadByte( MAKEWORD( UART_CMD_MCU_IDX_H, UART_CMD_MCU_IDX_L ) );
			putSIOChar( 0xF2 );
			putSIOChar( UART_CMD_MCU_DATA );
			break;
		}
		case kTest_Command:
		{
			ExecTestCommand();
			break;
		}
		#if !USEFLASH
		case kWrite_EEPROM:
		{
			WORD uwEEADDR;
			uwEEADDR = MAKEWORD(SIORxBuffer[1], SIORxBuffer[2]);
			#if 0//ENABLE_HDCP
			if (uwEEADDR >= RM_HDCP_KEY_BASEADDR1)
				g_wHDCP_KeyChkSum += g_UartCommand.Buffer[_UART_CMD_INDEX3_];
			#endif // ENABLE_HDCP
			NVRam_WriteByte(uwEEADDR, SIORxBuffer[3]);
			//if (!g_bDebugASCIICommandFlag)
			putSIOChar(0xF1);
			//printData("EEPROM[0x%x]=", uwEEADDR);
			//printData("0x%x \r\n", SIORxBuffer[_UART_CMD_INDEX3_]);
			break;
		}
		case kRead_EEPROM:
		{
			WORD uwEEADDR;
			uwEEADDR = MAKEWORD(SIORxBuffer[1], SIORxBuffer[2]);
			//uwEEADDR = g_UartCommand.Buffer[_UART_CMD_INDEX1_] & 0x0E;
			//uwEEADDR = (uwEEADDR << 7) + g_UartCommand.Buffer[_UART_CMD_INDEX2_];
			NVRam_ReadByte(uwEEADDR, &SIORxBuffer[3]);
			putSIOChar(0xF2);
			putSIOChar(SIORxBuffer[3]);
			//if (g_bDebugASCIICommandFlag)
			//{
			//printData("EEPROM[0x%x]=", uwEEADDR);
			//printData("0x%x \r\n", SIORxBuffer[_UART_CMD_INDEX3_]);
			//}
			break;
		}
		#endif
		default:
			break;
	}
}

Bool GetCommand(void)
{
	if( ReSyncCounter )
	{
		if( SIORxIndex > 2 && SIORxIndex == UART_CMD_LENGTH )
		{
			Set_RxBusyFlag();
			return TRUE;
		}
	}
	else if( SIORxIndex )
	{
		Clr_RxBusyFlag();
		SIORxIndex = 0;
	}
	return FALSE;
}

void DebugHandler(void)
{
	if( !ES )
		return;
	if( GetCommand() )
	{
		ProcessCommand();
		SIORxIndex = 0;
		Clr_RxBusyFlag();
	}
}



#define SIO_ID1     SIORxBuffer[0]
#define SIO_TYPE1   SIORxBuffer[1]
#define SIO_TYPE2   SIORxBuffer[2]
#define SIO_CMD1    SIORxBuffer[3]
#define SIO_CMD2    SIORxBuffer[4]
#define SIO_DATA1   SIORxBuffer[5]
#define SIO_DATA2   SIORxBuffer[6]
#define SIO_DATA3       SIORxBuffer[7]
#define SIOData10   (SIO_DATA1-0x30)*256
#define SIOData11   ((SIO_DATA1-0x41)+10)*256
#define SIOData20   (SIO_DATA2-0x30)*16
#define SIOData21   ((SIO_DATA2-0x41)+10)*16
#define SIOData30   (SIO_DATA3-0x30)
#define SIOData31   (SIO_DATA3-0x41)+10
//extern void Read6500KSetting(void);    //20050921  WMZ
//extern void Read9300KSetting(void);
//extern void ReadSRGBSetting(void);
//extern Bool ResetAllSetting(void);
//extern Bool SetToEnglish(void);
//extern Bool SetToSimpleChinese(void);
#if 1//ndef WH_REQUEST
BYTE AOCAlign(void)
{
	WORD sioData;
	if (SIO_ID1 == 'W')
	{
		// adjust
		if ((SIO_TYPE1 == '9') && (SIO_TYPE2 == '8'))
		{
			// ascii to integer
			sioData = ((SIO_DATA1 >= '0') && (SIO_DATA1 <= '9')) ? SIOData10 : SIOData11;
			sioData += ((SIO_DATA2 >= '0') && (SIO_DATA2 <= '9')) ? SIOData20 : SIOData21;
			sioData += ((SIO_DATA3 >= '0') && (SIO_DATA3 <= '9')) ? SIOData30 : SIOData31;
			// red
			if ((SIO_CMD1 == '0') && (SIO_CMD2 == '1'))
				// R Gain
			{
				UserPrefRedColor = sioData; // for CT
				// mStar_AdjustRedColor(UserPrefRedColor);
				mStar_AdjustRedColor(UserPrefRedColor, UserPrefContrast);
			}
			// green
			else if ((SIO_CMD1 == '0') && (SIO_CMD2 == '4'))
				// G Gain
			{
				UserPrefGreenColor = sioData; // for CT
				//mStar_AdjustGreenColor(UserPrefGreenColor);
				mStar_AdjustGreenColor(UserPrefGreenColor, UserPrefContrast);
			}
			// blue
			else if ((SIO_CMD1 == '0') && (SIO_CMD2 == '7'))
				// B Gain
			{
				UserPrefBlueColor = sioData; // for CT
				// mStar_AdjustBlueColor(UserPrefBlueColor);
				//mStar_AdjustBlueColor(UserPrefGreenColor,UserPrefContrast);
				mStar_AdjustBlueColor(UserPrefBlueColor, UserPrefContrast); //0727
			}
			// contrast
			else if ((SIO_CMD1 == '1') && (SIO_CMD2 == '4'))
				// Contrast
			{
				UserPrefContrast = sioData;
				//UserPrefContrast=((WORD)(MaxContrastValue-MinContrastValue))*UserPrefContrast/100+MinContrastValue;
				UserPrefContrast = UserPrefContrast + MinContrastValue;
				mStar_AdjustContrast(UserPrefContrast);
			}
			// black level
			else if ((SIO_CMD1 == '1') && (SIO_CMD2 == '5'))
				// Black level
			{}
			// brightness
			else if ((SIO_CMD1 == '1') && (SIO_CMD2 == '6'))
				// Brightness
			{
				UserPrefBrightness = sioData;
				mStar_AdjustBrightness(UserPrefBrightness);
			}
			// reset language
			else if ((SIO_CMD1 == 'R') && (SIO_CMD2 == 'L'))
				// Black level
			{
				#if  LANGUAGE_TYPE == All14Language_AddJap		//120322 Modify
				if (sioData == 0x03)
				{
					UserPrefLanguage = LANG_France;
				}
				else if (sioData == 0x04)
				{
					UserPrefLanguage = LANG_German;
				}
				else if (sioData == 0x05)
				{
					UserPrefLanguage = LANG_Italian;
				}
				else if (sioData == 0x0A)
				{
					UserPrefLanguage = LANG_Spanish;
				}
				else if (sioData == 0x0B)
				{
					UserPrefLanguage = LANG_Swedish;
				}
				else if (sioData == 0x0D)
				{
					UserPrefLanguage = LANG_SChina;
				}
				else if (sioData == 0x1E)
				{
					UserPrefLanguage = LANG_Polish;
				}
				else if (sioData == 0x0E)
				{
					UserPrefLanguage = LANG_Portugues;
				}
				else if (sioData == 0x09)
				{
					UserPrefLanguage = LANG_Russia;
				}
				else if (sioData == 0x07)
				{
					UserPrefLanguage = LANG_Korea;
				}
				else if (sioData == 0x01)
				{
					UserPrefLanguage = LANG_TChina;
				}
				else if (sioData == 0x12)
				{
					UserPrefLanguage = LANG_Czech;
				}
				else
					// default
				{
					UserPrefLanguage = LANG_English;
				}
				#endif
				#if !USEFLASH
				NVRam_WriteByte(nvrMonitorAddr(Language), UserPrefLanguage);
				#else
				UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
				#endif
			}
		}
		// save & recall color temperature
		else if ((SIO_TYPE1 == 'A') && (SIO_TYPE2 == '0'))
		{
			//  save cool
			if ((SIO_CMD1 == 'C') && (SIO_CMD2 == '1'))
			{
				UserPrefColorTemp = CTEMP_Cool1;
				UserPrefRedColorCool1 = UserPrefRedColor;
				UserPrefGreenColorCool1 = UserPrefGreenColor;
				UserPrefBlueColorCool1 = UserPrefBlueColor;
				#if USEFLASH
				UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit | bFlashSaveFactoryBit);
				#else
				SaveFactorySetting();
				SaveMonitorSetting();
				#endif
				//NVRam_WriteByte(Factory9300KContrastAddr, UserPrefContrast);
				//NVRam_WriteByte(Factory9300KBrightnessAddr, UserPrefBrightness);
			}
			// save warm
			else if ((SIO_CMD1 == 'A') && (SIO_CMD2 == '8'))
			{
				UserPrefColorTemp = CTEMP_Warm1;
				UserPrefRedColorWarm1 = UserPrefRedColor;
				UserPrefGreenColorWarm1 = UserPrefGreenColor;
				UserPrefBlueColorWarm1 = UserPrefBlueColor;
				#if USEFLASH
				UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit | bFlashSaveFactoryBit);
				#else
				SaveFactorySetting();
				SaveMonitorSetting();
				#endif
				//NVRam_WriteByte(Factory6500KContrastAddr, UserPrefContrast);
				//NVRam_WriteByte(Factory6500KBrightnessAddr, UserPrefBrightness);
			}
			#if CT_7500K_ENABLE
			// save normal:
			else if ((SIO_CMD1 == 'A') && (SIO_CMD2 == '5'))
			{
				UserPrefColorTemp = CTEMP_Normal;
				UserPrefRedColorNormal = UserPrefRedColor;
				UserPrefGreenColorNormal = UserPrefGreenColor;
				UserPrefBlueColorNormal = UserPrefBlueColor;
				#if USEFLASH
				UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit | bFlashSaveFactoryBit);
				#else
				SaveFactorySetting();
				SaveMonitorSetting();
				#endif
				//NVRam_WriteByte(FactorySRGBContrastAddr, UserPrefContrast);
				//NVRam_WriteByte(FactorySRGBBrightnessAddr, UserPrefBrightness);
			}
			#endif
			#if CT_sRGB_ENABLE
			// save sRGB:
			else if ((SIO_CMD1 == 'C') && (SIO_CMD2 == 'S'))
			{
				UserPrefColorTemp = CTEMP_SRGB;
				UserPrefRedColorSRGB = UserPrefRedColor;
				UserPrefGreenColorSRGB = UserPrefGreenColor;
				UserPrefBlueColorSRGB = UserPrefBlueColor;
				#if USEFLASH
				UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit | bFlashSaveFactoryBit);
				#else
				SaveFactorySetting();
				SaveMonitorSetting();
				#endif
				//NVRam_WriteByte(FactorySRGBContrastAddr, UserPrefContrast);
				//NVRam_WriteByte(FactorySRGBBrightnessAddr, UserPrefBrightness);
			}
			#endif
			// recall cool
			else if ((SIO_CMD1 == 'B') && (SIO_CMD2 == '9'))
			{
				UserPrefColorTemp = CTEMP_Cool1;
				UserPrefRedColor = UserPrefRedColorCool1;
				UserPrefGreenColor = UserPrefGreenColorCool1;
				UserPrefBlueColor = UserPrefBlueColorCool1;
				ReadColorTempSetting(); // 2006/11/10 6:59PM by KK  ReadCool1Setting();
				mStar_AdjustBrightness(UserPrefBrightness);
				mStar_AdjustContrast(UserPrefContrast);
			}
			// recall warm
			else if ((SIO_CMD1 == 'B') && (SIO_CMD2 == '8'))
			{
				UserPrefColorTemp = CTEMP_Warm1;
				UserPrefRedColor = UserPrefRedColorWarm1;
				UserPrefGreenColor = UserPrefGreenColorWarm1;
				UserPrefBlueColor = UserPrefBlueColorWarm1;
				ReadColorTempSetting(); // 2006/11/10 6:59PM by KK ReadWarm1Setting();
				mStar_AdjustBrightness(UserPrefBrightness);
				mStar_AdjustContrast(UserPrefContrast);
			}
			#if CT_7500K_ENABLE
			// recall normal
			else if ((SIO_CMD1 == 'B') && (SIO_CMD2 == '6'))
			{
				UserPrefColorTemp = CTEMP_Normal;
				UserPrefRedColor = UserPrefRedColorNormal;
				UserPrefGreenColor = UserPrefGreenColorNormal;
				UserPrefBlueColor = UserPrefBlueColorNormal;
				ReadColorTempSetting(); // 2006/11/10 6:59PM by KK ReadNormalSetting();
				mStar_AdjustBrightness(UserPrefBrightness);
				mStar_AdjustContrast(UserPrefContrast);
			}
			#endif
			// 20050114 wumaozhong
			#if SRGB
			#if CT_sRGB_ENABLE
			else if ((SIO_CMD1 == 'B') && (SIO_CMD2 == 'S'))
			{
				UserPrefColorTemp = CTEMP_SRGB;
				UserPrefRedColor = UserPrefRedColorSRGB;
				UserPrefGreenColor = UserPrefGreenColorSRGB;
				UserPrefBlueColor = UserPrefBlueColorSRGB;
				ReadColorTempSetting(); // 2006/11/10 6:59PM by KK ReadSRGBSetting();
				mStar_AdjustBrightness(UserPrefBrightness);
				mStar_AdjustContrast(UserPrefContrast);
			}
			#endif
			#endif
			else if (SIO_CMD1 == 'B' && SIO_CMD2 == '5')
				// Reset
			{
				ResetAllSetting();
			}
		}
		else if (SIO_TYPE1 == 'F')
		{
			sioData = ((SIO_DATA1 >= '0') && (SIO_DATA1 <= '9')) ? SIOData10 : SIOData11;
			sioData += ((SIO_DATA2 >= '0') && (SIO_DATA2 <= '9')) ? SIOData20 : SIOData21;
			sioData += ((SIO_DATA3 >= '0') && (SIO_DATA3 <= '9')) ? SIOData30 : SIOData31;
			if (SIO_TYPE2 == '0')
			{
				if (SIO_CMD1 == '0' && SIO_CMD2 == '1')
				{
					if (mStar_AutoColor())
					{
						#if USEFLASH
						UserPref_EnableFlashSaveBit(bFlashSaveFactoryBit);
						#else
						SaveFactorySetting();
						//  SaveMonitorSetting();
						#endif
					}
				}
				else if (SIO_CMD1 == '0' && SIO_CMD2 == '2')
				{
					if (mStar_AutoGeomtry())
					{
						#if USEFLASH
						UserPref_EnableFlashSaveBit(bFlashSaveModeBit);
						#else
						SaveModeSetting();
						#endif
					}
				}
			}
			else if (SIO_TYPE2 == '3')
			{
				if (SIO_CMD1 == '0' && SIO_CMD2 == '0')
				{
					Clr_BurninModeFlag();
					#if !USEFLASH
					NVRam_WriteByte(nvrMonitorAddr(MonitorFlag), MonitorFlags);
					#else
					UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
					#endif
				}
				else if (SIO_CMD1 == '0' && SIO_CMD2 == '1')
				{
					Set_BurninModeFlag();
					#if !USEFLASH
					NVRam_WriteByte(nvrMonitorAddr(MonitorFlag), MonitorFlags);
					#else
					UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
					#endif
				}
				else if (SIO_CMD1 == '0' && SIO_CMD2 == '4')
				{
					#if  LANGUAGE_TYPE == All14Language_AddJap		//120322 Modify
					if (sioData == 0x03)
					{
						UserPrefLanguage = LANG_France;
					}
					else if (sioData == 0x04)
					{
						UserPrefLanguage = LANG_German;
					}
					else if (sioData == 0x05)
					{
						UserPrefLanguage = LANG_Italian;
					}
					else if (sioData == 0x0A)
					{
						UserPrefLanguage = LANG_Spanish;
					}
					else if (sioData == 0x0B)
					{
						UserPrefLanguage = LANG_Swedish;
					}
					else if (sioData == 0x0D)
					{
						UserPrefLanguage = LANG_SChina;
					}
					else if (sioData == 0x1E)
					{
						UserPrefLanguage = LANG_Polish;
					}
					else if (sioData == 0x08)
					{
						UserPrefLanguage = LANG_Portugues;
					}
					else if (sioData == 0x09)
					{
						UserPrefLanguage = LANG_Russia;
					}
					else if (sioData == 0x07)
					{
						UserPrefLanguage = LANG_Korea;
					}
					else if (sioData == 0x01)
					{
						UserPrefLanguage = LANG_TChina;
					}
					else if (sioData == 0x12)
					{
						UserPrefLanguage = LANG_Czech;
					}
					else
						// default
					{
						UserPrefLanguage = LANG_English;
					}
					#endif
					#if !USEFLASH
					NVRam_WriteByte(nvrMonitorAddr(Language), UserPrefLanguage);
					#else
					UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
					#endif
				}
				else if (SIO_CMD1 == 'P' && SIO_CMD2 == 'M' && SIO_DATA1 == 'O')
				{
					#if USEFLASH
					FactoryProductModeValue = ProductModeOnValue;
					UserPref_EnableFlashSaveBit(bFlashSaveFactoryBit);
					#else
					//WORD temp=ProductModeOnValue;
					//NVRam_WriteTbl(ProductModeAddr, (BYTE*)(&temp), 2);
					NVRam_WriteWord(ProductModeAddr, ProductModeOnValue);
					#endif
				}
			}
			else if (SIO_TYPE2 == '5')
			{
				if (SIO_CMD1 == '0' && SIO_CMD2 == '0')
				{
					#if USEFLASH
					#else
					SaveBlacklitTime();
					#endif
				}
			}
			else if (SIO_TYPE2 == '7')
			{
				if (SIO_CMD1 == '0' && SIO_CMD2 == '1')
				{
					//Set_ISPFlag();
				}
			}
			else if (SIO_TYPE2 == '9')
			{
				if (SIO_CMD1 == 'E' && SIO_CMD2 == 'N')
				{
					Set_FactoryModeFlag();
					Set_AutoColorFlag();
					UserPrefContrast = DefContrast;
					UserPrefBrightness = DefBrightness;
					UserPrefECOMode = ECO_Standard;
					#if Enable_Gamma
					UserPrefGamaMode = GAMA1;
					mStar_SetupGamma( GAMA1 );
					#endif
					UserPrefDcrMode = 0;
					#if Enable_YCM_Mode
					UserPrefYColor = DefColor;
					UserPrefCColor = DefColor;
					UserPrefMColor = DefColor;
					#endif
					UserPrefRedColorUser = DefColor;
					UserPrefGreenColorUser = DefColor;
					UserPrefBlueColorUser = DefColor;
					#if MWEFunction
					UserPrefHue = 50;
					UserPrefSaturation = 0x80;
					UserPrefSubContrast = DefSubContrast;
					UserPrefSubBrightness = DefSubBrightness;
					msAdjustSharpness(SUB_WINDOW, 11, 1);
					msAdjustSubBrightness( SUB_WINDOW, UserPrefSubBrightness, UserPrefSubBrightness, UserPrefSubBrightness );
					msAdjustVideoContrast( SUB_WINDOW, DefContrastBase + UserPrefContrast );
					msAdjustVideoHue( SUB_WINDOW, UserPrefHue );
					msAdjustVideoSaturation( SUB_WINDOW, UserPrefSaturation );
					#endif
					mStar_AdjustContrast(UserPrefContrast);
					mStar_AdjustBrightness(UserPrefBrightness);
					#if USEFLASH
					UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
					#else
					SaveMonitorSetting();
					#endif
				}
				else if (SIO_CMD1 == '0' && SIO_CMD2 == 'E')
				{
					Clr_FactoryModeFlag();
				}
			}
			else if (SIO_TYPE2 == 'B')//  //'W'	'F'	'B'	'P'	'D'	'0'	'0'	'0'
			{
				if (SIO_CMD1 == 'P' && SIO_CMD2 == 'D' && SIO_DATA1 == '0') //Power Down
				{
					Power_PowerOffSystem();
					Power_TurnOnAmberLed();
				}
			}
		}
		#if ENABLE_HDCP
		#if HDCPKEY_IN_Flash//Zhifeng.Wu 20071127
		else if (SIO_TYPE1 == 'H' && SIO_TYPE2 == 'S')
		{
			if ((SIO_CMD1 == 'T') && (SIO_CMD2 == 'R'))
			{
				// HDCP WRITE START
				#if 0//DetectSystemVcc
				#if UseWDT
				DisableWDT();
				#endif
				#endif
				Set_WriteHDCPcodeFlag();
				TCRCvalue = 0;
				//Flash_Erase_FreeBuffer(FLASH_KEY_HDCP,0); // jeff add it in 2009 0907
				bFlashWriteFactory = TRUE;
				#if 0//Enable_Cache
				MCU_DisableCache();
				#endif
				FlashSectorErase(TRUE, HDCPKEYSET_START);
				FlashDisableWP(HDCPKEYSET_START);
				Power_TurnOffLed();
			}
		}
		else if (SIO_TYPE1 == 'H' && WriteHDCPcodeFlag)
			// WRITE HDCP DATA
		{
			#if 0
			WORD wTemp;
			if(SIO_TYPE2 < (HDCPKEY_SIZE / HDCP_BLOCK_LENGTH))
				Flash_Write_Factory_KeySet(FLASH_KEY_HDCP, SIO_TYPE2, HDCP_BLOCK_LENGTH, (BYTE*) &SIORxBuffer[3], HDCP_BLOCK_LENGTH);
			else if(SIO_TYPE2 == (HDCPKEY_SIZE / HDCP_BLOCK_LENGTH))
			{
				Flash_Write_Factory_KeySet(FLASH_KEY_HDCP, SIO_TYPE2, HDCP_BLOCK_LENGTH, (BYTE*) &SIORxBuffer[3], HDCPKEY_SIZE % HDCP_BLOCK_LENGTH);
				for(wTemp = 0; wTemp < HDCPKEY_SIZE; wTemp++)
				{
					TCRCvalue = CRC16(FlashReadByte(HDCPKEYSET_START + wTemp), TCRCvalue);
				}
				Set_LoadHDCPKeyFlag();
				hw_SetGreenLed();
			}
			#else
			BYTE i;
			for (i = 0; i < HDCP_BLOCK_LENGTH; i++)
			{
				//SIO_TYPE2==HDCP BANK NO	  SIORxBuffer[3+i]==HDCP DATA
				if(HDCP_BLOCK_LENGTH * SIO_TYPE2 + i < HDCPKEY_SIZE)
				{
					FlashHDCPWriteByte((HDCPKEYSET_START + HDCP_BLOCK_LENGTH * SIO_TYPE2 + i), SIORxBuffer[3 + i]);
					TCRCvalue = CRC16(FlashReadByte(HDCPKEYSET_START + HDCP_BLOCK_LENGTH * SIO_TYPE2 + i), TCRCvalue);
				}
			}
			if (SIO_TYPE2 == HDCPKEY_SIZE / HDCP_BLOCK_LENGTH) //HDCP WRITE END
			{
				Set_LoadHDCPKeyFlag();
				bFlashWriteFactory = FALSE;
				FlashEnableWP();
				#if 0//Enable_Cache
				MCU_EnableCache();
				#endif
				Power_TurnOnGreenLed();
			}
			#endif
		}
		#endif
		#endif
	}
	else if ((SIO_TYPE1 == 'V') && (SIO_TYPE2 == 'K'))
	{
		sioData = ((SIO_DATA1 >= '0') && (SIO_DATA1 <= '9')) ? SIOData10 : SIOData11;
		sioData += ((SIO_DATA2 >= '0') && (SIO_DATA2 <= '9')) ? SIOData20 : SIOData21;
		sioData += ((SIO_DATA3 >= '0') && (SIO_DATA3 <= '9')) ? SIOData30 : SIOData31;
		gByteVisualKey = 0xff;
		if ((SIO_CMD1 == '0') && (SIO_CMD2 == '0'))
		{
			if (sioData < 16)
			{
				if (((SIO_DATA3 >= '0') && (SIO_DATA3 <= '9')) || ((SIO_DATA3 >= 'A') && (SIO_DATA3 >= 'F')))
				{
					if (SIO_DATA3 == '0')
					{
						gByteVisualKey &= ~KEY_EXIT;
					}
					else if (SIO_DATA3 == '1')
					{
						gByteVisualKey &= ~KEY_PLUS;
					}
					else if (SIO_DATA3 == '2')
					{
						gByteVisualKey &= ~KEY_MINUS;
					}
					else if (SIO_DATA3 == '3')
					{
						gByteVisualKey &= ~KEY_MENU;
					}
					else if (SIO_DATA3 == '4')
					{
						gByteVisualKey &= ~KEY_POWER;
					}
					else
						gByteVisualKey = 0xff;
				}
			}
			else if ((SIO_DATA1 == '0') && (sioData > 16)) {}
			gBoolVisualKey = 1;
		} //End Virual  key
	}
	return SIORxIndex;
}
#endif
