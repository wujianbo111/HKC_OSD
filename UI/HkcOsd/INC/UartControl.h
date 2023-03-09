#ifndef _UARTControl_H_
#define _UARTControl_H_


typedef enum
{
	ARM_UART_IDLE = 0x00,
	ARM_START_RECV,
	ARM_UART_COMPLETED,
} ARMUartState;

typedef enum
{
	ARM_CMD_IDLE = 0x00,
	ARM_CMD_CHANGE_PM_WAKEUP,///1
	ARM_CMD_CHANGE_PM_SHUTDOWN,///2
	ARM_CMD_CHANGE_PM_SUSPENDN,///3
	ARM_CMD_GET_PM_STATUS,///4
	ARM_CMD_RESET_SLEEP_TIMER,///5
	ARM_CMD_SCALER_CHANGE_SRC,//6
	ARM_CMD_SCALER_SET_BRIGHTNESS,//7
	ARM_CMD_SCALER_NOTE_EDID_INFO,//
	RETURN_SCALER_SRC_STATUS,///8
	RETURN_SERIAL_NUMBER,///9

	RETURN_BLIGHTNESS,	// 11
	RETURN_USB,	// 12
	RETURN_ACK,	// 13
	ARM_CMD_CHANGE_DISPLAY,	// 14	//130708 gordon
	ARM_CMD_CHANGE_BRIGHTNESS,	// 15	//130717 gordon

} ARMCMDState;

typedef enum
{
	ARM_IDLE = 0x00,
	ARM_PowerOn,
	ARM_DCOff,
	ARM_DCOff_Complete,
	ARM_ForceOff,	//130529 Nick
	ARM_EscPowerSave,
	ARM_ChangeSource,
	ARM_AndroidSleeping,
	ARM_AndroidWakeup,
	ARM_WaitAndroid,
	ARM_Normal,
	ARM_SaveData,
	ARM_GetData,	//130717 gordon

} ARMStageState;
/////////////////////////////////////////////
// Uart command structure
/////////////////////////////////////////////
typedef enum _ARMCommadEnumType
{
	_ARM_UART_CMD_HEAD0_,
	_ARM_UART_CMD_HEAD1_,
	_ARM_UART_CMD_INDEX0_,
	_ARM_UART_CMD_INDEX1_,
	_ARM_UART_CMD_INDEX2_,
	_ARM_UART_CMD_INDEX3_,
	_ARM_UART_CMD_INDEX4_,
	_ARM_UART_CMD_INDEX5_,
	_ARM_UART_CMD_INDEX6_,
	_ARM_UART_CMD_CHECKSUM_,
} ARMCommadEnumType;

#define ARM_SYNC_R				0x01
#define ARM_SYNC_W				0x03

#define ARM_CMD_S2A				0xDC
#define ARM_CMD_A2S				0xDD
#define FCode08					0xE8
#define FCode10					0xF0

#define ARM_UART_FIELD_HEAD0 		(rxARMUartBuffer[_ARM_UART_CMD_HEAD0_])
#define ARM_UART_FIELD_HEAD1 		(rxARMUartBuffer[_ARM_UART_CMD_HEAD1_])
#define ARM_UART_FIELD_PKTSIZE		(rxARMUartBuffer[_ARM_UART_CMD_INDEX0_])
#define ARM_UART_FIELD_SYNC			(rxARMUartBuffer[_ARM_UART_CMD_INDEX1_])
#define ARM_UART_FIELD_NULL			(rxARMUartBuffer[_ARM_UART_CMD_INDEX2_])
#define ARM_UART_FIELD_COMMAND		(rxARMUartBuffer[_ARM_UART_CMD_INDEX3_])
#define ARM_UART_FIELD_EXIT			(rxARMUartBuffer[_ARM_UART_CMD_INDEX4_])
#define ARM_UART_FIELD_DAT1			(rxARMUartBuffer[_ARM_UART_CMD_INDEX5_])
#define ARM_UART_FIELD_DAT2			(rxARMUartBuffer[_ARM_UART_CMD_INDEX6_])

#define RW_PM_STATE					0x81
#define RESET_SLEEP_TIMER			0x82
#define R_SCALRE_SOURCE				0x82
#define SCLARE_CHANGE_SOURC			0x83

#define ARM_CMD_					0xDC
#define ShutdownState				0x81
#define SuspendState				0x82

#define LeaveAndroidSrc		0x01
#define EnterAndroidSrc		0x02

#define AndroidOff                   0x0
#define Booting				0x01
#define PowerOnReady		0x02
#define Wakeup				0x03	// 20121031 ChunHan add


#define ShutdownIn			0x81
#define ShutdownComplete	0x82
#define IntoSuspendMode		0x83
#define SuspendComplete		0x84
#define CancelShutdown		0x85
#define BootMenu                     0x86
//130708 gordon
#define ImageRotation			0x85
#define landscape 		0x01
#define portrait		0x02


#define ACK1                0xC2
#define ACK2                0x3D




#define ANDROID_Set_Backlight				0x85
#define ANDROID_Set_LANGUAGE				0x83	//130806 xiandi
#define ANDROID_Set_USBHUB				       0x84	//130806 xiandi

#define ANDROID_Get_Source				0x81		//130821 gordon
#define ANDROID_Get_USBHub				0x82		//130821 gordon
#define ANDROID_Get_Backlight				0x83
#define ANDROID_Get_SN				0x84			//130821 gordon
#define ANDROID_Get_MAC				0x85			//130821 gordon

#define AndroidPreProcess()  (((ARM_UART_FIELD_HEAD0==0x6E)&&(ARM_UART_FIELD_HEAD1==0x51)) ||(ARM_UART_FIELD_HEAD0+ARM_UART_FIELD_HEAD1==0xFF))	//130529 Nick
#define AndroidSaveEEPROM() (ARM_UART_FIELD_DAT1== 0xFF)	//130710 gordon
#if 0
#define Android_Pre2 0xF5
#define Android_Command9 0x82
#define Android_GetSN()  ((ARM_UART_FIELD_SYNC == ARM_SYNC_R) &&(ARM_UART_FIELD_COMMAND == ARM_CMD_A2S) && (ARM_UART_FIELD_EXIT==ANDROID_Get_SN))		//130821 gordon
#define Android_GetMAC()  ((ARM_UART_FIELD_SYNC == ARM_SYNC_R) &&(ARM_UART_FIELD_COMMAND == ARM_CMD_A2S) && (ARM_UART_FIELD_EXIT==ANDROID_Get_MAC))		//130821 gordon
#define Android_GetScalerStatus()  ((ARM_UART_FIELD_SYNC == ARM_SYNC_R) && (ARM_UART_FIELD_COMMAND == ARM_CMD_A2S) && (ARM_UART_FIELD_EXIT == ANDROID_Get_Source) )

#define Android_SendAndroidStatus()  ((ARM_UART_FIELD_SYNC == ARM_SYNC_W) && (ARM_UART_FIELD_COMMAND == ARM_CMD_A2S) && (ARM_UART_FIELD_EXIT == RW_PM_STATE) )

#define Android_SetBrightness()  ((ARM_UART_FIELD_SYNC == ARM_SYNC_W) &&(ARM_UART_FIELD_COMMAND == ARM_CMD_A2S) && (ARM_UART_FIELD_EXIT==ANDROID_Set_Backlight))
#define Android_SetLanguage()  ((ARM_UART_FIELD_SYNC == ARM_SYNC_W) &&(ARM_UART_FIELD_COMMAND == ARM_CMD_A2S) && (ARM_UART_FIELD_EXIT==ANDROID_Set_LANGUAGE))
#define Android_SetUSBHub()  ((ARM_UART_FIELD_SYNC == ARM_SYNC_W) &&(ARM_UART_FIELD_COMMAND == ARM_CMD_A2S) && (ARM_UART_FIELD_EXIT==ANDROID_Set_USBHUB))
#define Android_GetBrightness()  ((ARM_UART_FIELD_SYNC == ARM_SYNC_R) &&(ARM_UART_FIELD_COMMAND == ARM_CMD_A2S) && (ARM_UART_FIELD_EXIT==ANDROID_Get_Backlight))
#define Android_GetUSBHub()  ((ARM_UART_FIELD_SYNC == ARM_SYNC_R) &&(ARM_UART_FIELD_COMMAND == ARM_CMD_A2S) && (ARM_UART_FIELD_EXIT==ANDROID_Get_USBHub))



//For Return Command9	//130625 Gordon
#define Android_SendAck()  ((ARM_UART_FIELD_HEAD0 + ARM_UART_FIELD_HEAD1 == 0xFF) && (ARM_UART_FIELD_PKTSIZE == 0x82)  && (ARM_UART_FIELD_SYNC == 0x01) && (ARM_UART_FIELD_NULL == EnterAndroidSrc))
//130806 xiandi
#define SetLanEnglish		0x00
#define SetLanFrench		0x01
#define SetLanSpanish		0x02
#define SetLanPortuguese	0x08
#define SetLanGerman		0x04
#define SetLanItalian		0x05
#define SetLanDutch			0x09
#define SetLanSwedish		0x0A
#define SetLanFinnish		0x0B
#define SetLanPolish		0x0C
#define SetLanCzech			0x0D
#define SetLanRussian		0x0F
#define SetLanKorean		0x11
#define SetLanTChinese 		0x12
#define SetLanSChinese 		0x13
#define SetLanJapanese 		0x14

#else
#define Android_Pre2 0xFE
#define Android_Command9 0x83

#define Android_GetSN()  ((ARM_UART_FIELD_SYNC == ARM_SYNC_R) && (ARM_UART_FIELD_COMMAND == FCode08))
#define Android_GetMAC()  ((ARM_UART_FIELD_SYNC == ARM_SYNC_R) && (ARM_UART_FIELD_COMMAND == FCode10))
#define Android_GetScalerStatus()  ((ARM_UART_FIELD_SYNC == ARM_SYNC_R) && (ARM_UART_FIELD_COMMAND == ARM_CMD_A2S) && (ARM_UART_FIELD_EXIT == R_SCALRE_SOURCE) && (ARM_UART_FIELD_DAT2 == 0x00))
#define Android_SendAndroidStatus()  ((ARM_UART_FIELD_SYNC == ARM_SYNC_W) && (ARM_UART_FIELD_COMMAND == ARM_CMD_A2S) && (ARM_UART_FIELD_EXIT == RW_PM_STATE) )

#define Android_SetBrightness()  ((ARM_UART_FIELD_SYNC == ARM_SYNC_W) &&(ARM_UART_FIELD_COMMAND == ARM_CMD_A2S) && (ARM_UART_FIELD_EXIT==ANDROID_Set_Backlight))
#define Android_SetLanguage()  ((ARM_UART_FIELD_SYNC == ARM_SYNC_W) &&(ARM_UART_FIELD_COMMAND == ARM_CMD_A2S) && (ARM_UART_FIELD_EXIT==ANDROID_Set_LANGUAGE))
#define Android_SetUSBHub()  ((ARM_UART_FIELD_SYNC == ARM_SYNC_W) &&(ARM_UART_FIELD_COMMAND == ARM_CMD_A2S) && (ARM_UART_FIELD_EXIT==ANDROID_Set_USBHUB))
#define Android_GetBrightness()  ((ARM_UART_FIELD_SYNC == ARM_SYNC_R) &&(ARM_UART_FIELD_COMMAND == ARM_CMD_A2S) && (ARM_UART_FIELD_EXIT==ANDROID_Get_Backlight))
#define Android_GetUSBHub()  ((ARM_UART_FIELD_SYNC == ARM_SYNC_R) &&(ARM_UART_FIELD_COMMAND == ARM_CMD_A2S) && (ARM_UART_FIELD_EXIT==ANDROID_Get_USBHub))


#define Android_SendAck()  ((ARM_UART_FIELD_HEAD0 + ARM_UART_FIELD_HEAD1 == 0xFF) && (ARM_UART_FIELD_PKTSIZE == 1))

#endif











#define _ARM_UART_CMD_BUFFER_LENGTH_	 25//  50
extern BYTE xdata txARMUartBuffer[_ARM_UART_CMD_BUFFER_LENGTH_];
extern BYTE xdata rxARMUartBuffer[_ARM_UART_CMD_BUFFER_LENGTH_];
//extern BYTE xdata ErgoUartRxBuffer[_ARM_UART_CMD_BUFFER_LENGTH_];
extern BYTE xdata txARMUartIndex;
extern BYTE xdata rxARMUartIndex;
extern BYTE xdata rxARMUartStatus;
extern BYTE xdata rxARMUartLength;
extern BYTE xdata rxARMUartFlag;
extern BYTE xdata ARMCommand;
extern BYTE xdata ARMStage;
extern BYTE xdata ARM_PM_Status;

extern void putSIOChar( unsigned char sendData );
extern void appARMSenserInitRx( void );
extern void appARMHandler(void);
extern void appARMInit(void);


#endif
