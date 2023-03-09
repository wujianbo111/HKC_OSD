#include "types.h"
#include "board.h"
#include "global.h"
#include "power.h"
#include "debug.h"
#include "debugDef.h"
#include "ddc2bi.h"
#include "Menudef.h"
#include "ms_reg.h"
#include "Ms_rwreg.h"
#include "GPIO_DEF.h"
#include "mcu.h"


#if ENABLE_DP_INPUT
#include "drvDPRxApp.h"
#endif

#if ENABLE_HDMI || ENABLE_FREESYNC
#include "msHDMI.h"
#endif
#if MS_DAC
#include "drvDAC.h"
#endif
#if 0//USEFLASH
extern WORD xdata ucFlashSaveCount;
#endif


#if ENABLE_UART1
#include "UartControl.h"
#endif
#if  ENABLE_ANDROID_IR	//131008 Modify
#include "drv_Ir.h"
#endif

#if ENABLE_DisplayPortTX
#include "drvDPTxApp.h"
#endif

#if ENABLE_FREESYNC
extern xdata Bool bHDMIFreesyncChk;
#endif
#if ! EANBLE_NEW_DCR_Functing
extern BYTE xdata DCRStepTransCnt; // 081205 dcr test
#endif
//#define ReSyncTick          255//54 // 0.2 Second for resynchorize dubug process
#if EXT_TIMER0_1MS || (ENABLE_MENULOAD && ML_USE_INT)||EXT_TIMER0_1S	//111223 Modify
#define EnableExt0Interrupt     	1
#define EnableTime0Interrupt        1
#elif ENABLE_SW_DOUBLE_BUFFER
#define EnableExt0Interrupt          1
#define EnableTime0Interrupt        1
#else
#define EnableExt0Interrupt     	0
#define EnableTime0Interrupt        1
#endif

#if UseINT
#define EnableExt1Interrupt     	1
#define EnableSerialPortInterrupt   1 // 0
#else
#define EnableExt1Interrupt     	0
#define EnableSerialPortInterrupt   1
#endif

#if ENABLE_UART1
#define EnableSerialPortInterrupt1  1
#else
#define EnableSerialPortInterrupt1  0
#endif


#if  ENABLE_ANDROID_IR	//131008 Modify
#define EnableTime1Interrupt        1
#else
#define EnableTime1Interrupt        0
#endif

#define EnableTime2Interrupt        0

#if CHIP_ID == CHIP_TSUM2 || CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD || CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF
#if ENABLE_MHL
#include "DRVMHL.h"
//extern xdata WORD g_u16S2PatchCnt;
//extern BYTE xdata g_u16S2PatchCntFlag;
//extern xdata WORD g_u16MHLHandlerCnt;
//extern bit g_u16MHLHandlerCntFlag;
#endif

#if ENABLE_SW_DOUBLE_BUFFER
extern XDATA StuSWDBCtrl SWDBCtrl;

void IsrML(void)
{
	SWDBCtrl.ucSWDB_Counter = 0;
	SWDBCtrl.ucSWDB_OnFire = 0;
	SWDBCtrl.ucSWDB_Num = 1;
	msRegs[REG_3C25] &= 0x3F;
}
#endif

#if 0
void IsrBDMA(void)
{
	if(_bit2_(msRegs[REG_3302]))
	{
		msRegs[REG_3302] = BIT2 | BIT3;
		msRegs[REG_12C4] = 0x00;
		msRegs[REG_2080] = 0x27;
	}
}
#endif
#endif

#if UseINT
void MuteVideoAndAudio(void)
{
	#if !ENABLE_ExpanderIO
	#if ENABLE_HDMI
	if( gScInfo.InputTmdsType == TMDS_HDMI )
	{
		hw_SetMute(); // for changed mode have "po-po"
	}
	#endif
	#endif
	#if ENABLE_DP_INPUT	//130603 william
	#if AudioFunc
	if(CURRENT_INPUT_IS_DISPLAYPORT())
	{
		hw_SetMute();
	}
	#endif
	#endif
	hw_ClrBlacklit();
	Set_InputTimingChangeFlag();
	Clr_ForcePowerSavingFlag();
	InputTimingStableCounter = 0;
	SrcFlags |= SyncLoss;
}

void IsrModeChangeCheck(void)
{
	BYTE xdata ucBank = MEM_SCREAD_BYTE(0x00);
	#if ((ENABLE_RTE && CHIP_ID==CHIP_TSUMF))
	bit INT_VsyncEdge;
	#endif
	MEM_SCWRITE_BYTE(0, 0); //bk0
	if (INT_STATUS_A_ISR((MEM_SCREAD_BYTE(SC0_CE)) & (BIT4 | BIT5 | BIT6 | BIT7)) || (INT_STATUS_B_ISR((MEM_SCREAD_BYTE(SC0_CF)) & (BIT2))))
	{
		INT_SCALER_A_ISR(0);//MEM_SCWRITE_BYTE(SC0_CE, 0); //disable INT
		INT_SCALER_B_ISR(0);//MEM_SCWRITE_BYTE(SC0_CF, 0); //disable INT
		INT_STATUS_CLEAR_ISR();
		if (!SyncLossState())
		{
			MuteVideoAndAudio();
		}
	}
	#if 0//ENABLE_FREESYNC
	else if (INT_STATUS_A_ISR((MEM_SCREAD_BYTE(SC0_CE))&BIT3))
	{
		MEM_SCWRITE_BYTE(SC0_CC, (MEM_SCREAD_BYTE(SC0_CC) & (~BIT3)));
		if(IS_HDMI_FREESYNC_ISR())
		{
			if(bHDMIFreesyncChk)
				MEM_SCWRITE_BYTE(SC0_E8, (MEM_SCREAD_BYTE(SC0_E8) & (~BIT1)) | BIT0); //Enable force P mode
			bHDMIFreesyncChk = FALSE;
		}
	}
	#endif
	#if ( (ENABLE_RTE && CHIP_ID==CHIP_TSUMF))
	INT_VsyncEdge = (Bool)(INT_STATUS_A_ISR(INT_VSYNC_EDGE));
	if(INT_VsyncEdge)
	{
		INT_VsyncEdge = 0;
		MEM_SCWRITE_BYTE(SC0_CC, (~INT_VSYNC_EDGE));
	}
	#endif
	MEM_SCWRITE_BYTE(0x00, ucBank);
}
#endif

#if EXT_TIMER0_1S   // 2012-05-23
void ms1SHandler( void )
{
	g_oneSecondFlag = 1;
	g_second++;
	if(g_second == 60)
	{
		g_oneMinuteFlag = 1;
		g_second = 0;
		g_minute++;
		if(g_minute == 60)
		{
			g_minute = 0;
			g_hour++;
			if(g_hour == 24)
				g_hour = 0;
		}
	}
}
#endif

#if EnableExt0Interrupt
void EXT0Interrupt(void)interrupt 0
{
	BYTE xdata ucStatus;
	ucStatus = msRegs[REG_2B10];
	#if ENABLE_MENULOAD && ML_USE_INT	//111223 Modify
	if( ucStatus & _BIT5 )
	{
		extern BYTE xdata u8ML_Status;
		u8ML_Status = msRegs[REG_3C27] & (ML_STS_BUSY | ML_STS_TRIG_ERR | ML_STS_CMD_ERR | ML_STS_DONE);
		msRegs[REG_3C25] = msRegs[REG_3C25] & ~(BIT7 | BIT6); //disable ML
	}
	#endif
	msRegs[REG_2B08] = ucStatus;
	msRegs[REG_2B08] = 0x00;
	#if CHIP_ID == CHIP_TSUM2 || CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD || CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF
	#if  ENABLE_SW_DOUBLE_BUFFER
	if(_bit5_(ucStatus))
		IsrML();
	#endif
	#endif
	#if EXT_TIMER0_1MS||EXT_TIMER0_1S
	if( ucStatus & _BIT0 )
		ms1SHandler();
	#endif
	IE0 = 0;
}
#endif
#if EnableTime0Interrupt
extern WORD ms_Counter;
extern xdata BYTE ReSyncCounter;
//extern BYTE Second;
extern BYTE xdata OsdCounter;
extern BYTE xdata HotKeyCounter;
extern BYTE xdata PowerDownCounter;
void Time0Interrupt(void)interrupt 1
{
	TH0 = g_ucTimer0_TH0;
	TL0 = g_ucTimer0_TL0; // timer 1 counter
	ms_Counter--;
	#if 0  //nick add for checking timer correct or not
	if(ms_Counter % 2)
	{
		hw_SetGreenLed();
	}
	else
	{
		hw_ClrGreenLed();
	}
	#endif
	#if ENABLE_DEBUG
	if (ReSyncCounter)
	{
		ReSyncCounter--;
	}
	#endif
	if(bDelayFlag)
	{
		if(-- DelayCounter == 0)
			bDelayFlag = 0;
	}
	// if(TimeOutCounter)
	//    TimeOutCounter--;
	if( bTimeOutCounterFlag )
		if( --u16TimeOutCounter == 0 )
			bTimeOutCounterFlag = 0;
	#if ENABLE_DP_INPUT
	#if DP_FastTraining&&(CHIP_ID==CHIP_TSUMU)      //#if CHIP_ID == CHIP_TSUMC		//130116_3 Henry For DC Off/On,Dp Source Can not Wake Up 	//130912 nick
	if(u16DPRxStableTimeout)
		u16DPRxStableTimeout--;
	#endif
	#if (CHIP_ID==CHIP_TSUMC ||CHIP_ID==CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)	//130912 nick
	if( bDPRxStableTimeoutFlag )
		if( --u16DPRxStableTimeout == 0 )
			bDPRxStableTimeoutFlag = 0;
	#endif
	#if DPCTS
	#if DP_FastTraining&&(CHIP_ID==CHIP_TSUMC ||CHIP_ID==CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)	//130912 nick
	if( bCDR_HPDCntFlag )
		if( --u16CDR_HPDCnt == 0 )
			bCDR_HPDCntFlag = 0;
	if( bSkew_HPDCntFlag )
		if( --u16Skew_HPDCnt == 0 )
			bSkew_HPDCntFlag = 0;
	#endif
	#if (CHIP_ID==CHIP_TSUMU)	//130912 nick
	if(CDR_HPDCnt)
		CDR_HPDCnt--;
	if(Skew_HPDCnt)
		Skew_HPDCnt--;
	#endif
	#if (CHIP_ID==CHIP_TSUM9 || CHIP_ID==CHIP_TSUMF)
	if(gDPInfo.bPacketTimer )
		gDPInfo.bPacketTimer --;
	#endif
	#if CHIP_ID == CHIP_TSUMC||CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF	//130912 nick
	#if 1
	if( bAudio_BWCntFlag )
		if( --u16Audio_BWCnt == 0 )
			bAudio_BWCntFlag = 0;
	#else
	if(Audio_BWCnt)           //20130716
		Audio_BWCnt--;
	#endif
	#endif
	#endif
	#endif
	#if ENABLE_TIME_MEASUREMENT   //need enable this if test Timer0
	if( g_u16TimeMeasurementCounter )
		g_u16TimeMeasurementCounter--;
	#endif
	#if MS_DAC && (CHIP_ID==CHIP_TSUMC ||CHIP_ID==CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)
	#if InitialDACByISR
	if( bDAC_DePopCountFlag )
	{
		if( (--w16DAC_DePopCounter) == 0 )
		{
			bDAC_DePopCountFlag = 0;
			bDAC_DePopFlag = 1;
		}
	}
	#endif
	#endif
	if(!g_bMcuPMClock) // system runs at normal speed
	{
		if(bPanelDelayFlag)
		{
			if(--PanelOffOnDelayCntr == 0)
				bPanelDelayFlag = 0;
		}
		#if ENABLE_MHL
		#if CHIP_ID == CHIP_TSUM2
		if(g_u16S2PatchCntFlag)
		{
			if(--g_u16S2PatchCnt == 0)
				g_u16S2PatchCntFlag = 0;
		}
		if(g_u16MHLHandlerCntFlag)
		{
			if(--g_u16MHLHandlerCnt == 0)
				g_u16MHLHandlerCntFlag = 0;
		}
		#elif (CHIP_ID == CHIP_TSUMC)||(CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF)
		mapi_mhl_CbusTimerInterrupt();
		#endif
		#endif
	}
	if (ms_Counter == 0)
	{
		Set_SecondFlag();
		ms_Counter = SystemTick;
	}
	if((ms_Counter % 10) == 0)
	{
		Set_ms10Flag();
		#if ENABLE_MHL_COUNT
		if(MHLActionCount)
			MHLActionCount++;
		#endif
		if((ms_Counter % 50) == 0)
		{
			Set_ms50Flag();
			#if CHIP_ID == CHIP_TSUM2
			if(FPLLTimeoutCounter)
				FPLLTimeoutCounter--;
			#endif
			#if  EANBLE_NEW_DCR_Functing
			if(( ms_Counter % 100 ) == 0 )
			{
				if ( DCRStepTransCnt )
				{
					DCRStepTransCnt --;
				}
			}
			#endif
			#if 0//ENABLE_FREESYNC
			if(( ms_Counter % 250 ) == 0 )
			{
				Set_ms250Flag();
			}
			#endif
			if ((ms_Counter % 500) == 0)
			{
				Set_ms500Flag();
			}
		}
	}
	if(TF0)
	{
		TH0 = g_ucTimer0_TH0;
		TL0 = g_ucTimer0_TL0; // timer 1 counter
	}
	TF0 = 0; // timer 1 flag
}
#endif
#if EnableExt1Interrupt
void EXT1Interrupt(void)interrupt 2
{
	BYTE xdata ucBank = MEM_SCREAD_BYTE(0x00);       //110926 Rick add to store the current bank - Verify A036, A039
	#if (ENABLE_DP_INPUT&& ((CHIP_ID == CHIP_TSUMC)||(CHIP_ID == CHIP_TSUMD)||(CHIP_ID == CHIP_TSUM9)||(CHIP_ID == CHIP_TSUMF)))
	if((_bit2_(msRegs[REG_2B2A])) || (_bit3_(msRegs[REG_2B2A])))
	{
		DPISR_AUX0();
	}
	#endif
	#if (CHIP_ID == CHIP_TSUMC)||(CHIP_ID == CHIP_TSUMD) ||(CHIP_ID == CHIP_TSUM9)||(CHIP_ID == CHIP_TSUMF)
	if(_bit7_(msRegs[REG_2B29]))
	{
		TMDSISR();
		#if ENABLE_DP_INPUT
		DPISR();
		#endif
	}
	#if ENABLE_MHL
	if(_bit0_(msRegs[REG_2B2A]))
	{
		mapi_mhl_IsrHandler();
	}
	#endif
	#endif
	#if CHIP_ID == CHIP_TSUMU
	#if ENABLE_DP_INPUT
	if(_bit6_(msRegs[REG_2B29]))
	{
		DPISR();    // read status
	}
	#endif
	#if ENABLE_DisplayPortTX
	if(_bit7_(msRegs[REG_2B29]))
	{
		DPISR_TX();    // read status
	}
	#endif
	#endif
	if( INT_STATUS_D2B_ISR() )  //if( DDC_MCCS_IRQ_DET() )
	{
		ISR_DDC2Bi();
	}
	#if UseINT
	if(INT_STATUS_DISP_ISR())
	{
		IsrModeChangeCheck();
	}
	#endif
	#if 0
	#if CHIP_ID == CHIP_TSUM2 || CHIP_ID == CHIP_TSUMC||CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF
	if(_bit0_(msRegs[REG_2B2A]))
		IsrBDMA();
	#elif CHIP_ID == CHIP_TSUMD
	if(_bit5_(msRegs[REG_2B2A]))
	{
		IsrBDMA();
	}
	#endif
	#endif
	#if ENABLE_ANDROID_IR	//131008 Modify
	{
		BYTE  final_status;                 // use idata to speedup
		final_status = msRegs[REG_2B29];    // read status
		if(IR_PinStatus(final_status))
		{
			IR_INT1();
		}
		msRegs[REG_2B29] = final_status;    // clear status
		msRegs[REG_2B29] = 0x00;
	}
	#endif
	MEM_SCWRITE_BYTE(0x00, ucBank);
	IE1 = 0;
	//  EX1=1;
}
#endif


#if EnableTime1Interrupt
void Time1Interrupt( void ) interrupt 3
{
	#if 0
	BYTE test;
	test++;
	if(test % 2)
		hw_SetDDC_WP();
	else
		hw_ClrDDC_WP();
	#endif
	TH1 = Timer1_TH1;  //200us reload
	TL1 = Timer1_TL1;  //200us reload
	#if ENABLE_ANDROID_IR	//131008 Modify
	if(IRstateHighCount > 32)
	{
		return;
	}
	if(IR_Pin)  //high
		IRstateHighCount++;
	else
		IRstateLowCount++;
	if(TF1)
	{
		TH1 = Timer1_TH1; //200us reload
		TL1 = Timer1_TL1; //200us reload
	}
	TF1 = 0;
	#endif
	#if ENABLE_TIME_MEASUREMENT  //need enable this if test Timer1
	if(bTimeMeasurementFlag)
	{
		if(--g_u16TimeMeasurementCounter == 0)
			bTimeMeasurementFlag = 0;
	}
	#endif
}
#endif


#if EnableSerialPortInterrupt


void SerialPortInterrupt(void)interrupt 4
{
	BYTE xdata sioData;
	if( RI )
	{
		RI = 0;
		sioData = SBUF;
		if( SIORxIndex < _UART_BUFFER_LENGTH_ )
		{
			ReSyncCounter = ReSyncTick;
			SIORxBuffer[SIORxIndex++] = sioData;
		}
	}
	if( TI )
	{
		TI = 0;
		TI0_FLAG = 1;
	}
}


#endif



#if EnableTime2Interrupt
void Time2Interrupt(void)interrupt 5
{
	TF2 = 0;
}
#endif


#if EnableSerialPortInterrupt1

#if ENABLE_UART_CONTROL

#define UART1UseChecksum		0
void SerialPortInterrupt1( void ) interrupt 16
{
	BYTE sioData;
	if( S1CON & RI1)
	{
		S1CON &= ~RI1;    // clear RI1
		sioData = S1BUF;
		if(rxARMUartIndex < (_ARM_UART_CMD_BUFFER_LENGTH_ - 1))
		{
			if(rxARMUartIndex == 0)
			{
				AndroidRxCounter = 2;
			}
			rxARMUartBuffer[rxARMUartIndex++] = sioData;
		}
		#if 0
		switch(rxARMUartStatus)
		{
			case ARM_UART_IDLE:
				rxARMUartIndex = 0;
				Checksum = sioData; // 20121101 ChunHan add
				rxARMUartBuffer[rxARMUartIndex++] = sioData;
				rxARMUartStatus = ARM_START_RECV;
				AndroidRxCounter = 3;
				break;
			case ARM_START_RECV:
				Checksum ^= sioData;    // 20121101 ChunHan add
				if(rxARMUartIndex > (_ARM_UART_CMD_BUFFER_LENGTH_ - 1))
				{
					rxARMUartStatus = ARM_UART_IDLE;
					break;
				}
				rxARMUartBuffer[rxARMUartIndex++] = sioData;
				if(rxARMUartIndex > ((ARM_UART_FIELD_PKTSIZE & ~DDC2Bi_CONTROL_STATUS_FLAG) + 3)) // 20121101 ChunHan modify
				{
					rxARMUartStatus = ARM_UART_IDLE;
					rxARMUartIndex = 0;
					rxARMUartFlag = 1;
				}
				else if((rxARMUartIndex > (rxARMUartBuffer[2] + 2) ) && ((rxARMUartBuffer[0] + rxARMUartBuffer[1]) == 0xFF))
				{
					rxARMUartStatus = ARM_UART_IDLE;
					rxARMUartIndex = 0;
					rxARMUartFlag = 1;
				}
				else
					AndroidRxCounter = 3;
				break;
			default:
				rxARMUartStatus = ARM_UART_IDLE;
				rxARMUartIndex = 0;
				break;
		}
		#endif
	}
	if( S1CON & TI1 )     // check TI1;
	{
		S1CON &= ~TI1;    // clear TI1
		TI1_FLAG = 1;
	}
}

#else
void SerialPortInterrupt1( void ) interrupt 16
{
	// SFR: 0x9B
	// s1con        [7]: 0:9-bit        1: 8-bit
	//              [6]: not used
	//              [5]: multiple processor enable
	//              [4]: reception enable
	//              [3]: tb81
	//              [2]: rb81
	//              [1]: ti1
	//              [0]: ri1
	BYTE ucTmp;
	if( S1CON & RI1 )     // check RI1;
	{
		S1CON &= ~RI1;    // clear RI1
		ucTmp = S1BUF;
		#if ENABLE_DEBUG
		if( SIORxIndex < _UART_BUFFER_LENGTH_  ) // Protect buffer overflow
		{
			ReSyncCounter = ReSyncTick;
			SIORxBuffer[SIORxIndex++] = ucTmp; // recieve byte
		}
		#endif
	}
	if( S1CON & TI1 )     // check TI1;
	{
		S1CON &= ~TI1;    // clear TI1
		TI1_FLAG = 1;
	}
}

#endif

#endif

