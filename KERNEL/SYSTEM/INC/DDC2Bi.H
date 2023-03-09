#include "drvDDC2Bi.h"
#include "drvDPRxApp.h"

extern void DDC2Bi_Init(void);
extern void DDC2Bi_CommandHandler(void);
extern  void DoDDCCI(BYTE Source);
#if  ENABLE_DP_INPUT	//121130 Modify
#if  DPENABLEMCCS
extern void msDP_DDC2BI(void);
#endif
#endif
extern void ISR_DDC2Bi(void);
//==========COMMAND TYPE=======================================
#define GETVCPFeature			0x01
#define SETVCPFeature			0x03
#define GetTimingRequest			0x07
#define SaveCurrentSetting		0x0C
#define GETVCPPage				0xC4
#define GETPagedVCP			    	0xC6
#define SETPagedVCP			    	0xC8
#define CapabilitiesRequest	    	0xF3
#define EnableApp				0xF5
#define AppTest					0xB1
#define NewControl           			0x02
#define ALL_Reset			    	0x04
#define BriCon_Reset           		0x05
#define Geometry_Reset			0x06
#define Color_Reset				0x08
#define ColorTempInc      			0x0B
#define ColorTempRequest 		0x0C
#define ADJ_Clock			    	0x0E
#define ADJ_Brightness			0x10
#define ADJ_Contrast				0x12
#define Select_Color_Preset		0x14
#define ADJ_Red_Gain			0x16
#define ADJ_Green_Gain			0x18
#define ADJ_Blue_Gain			0x1A
#define Auto_Setup			    	0x1E
#define Auto_Color			       0x1F
#define ADJ_HorizontalPos		0x20
#define ADJ_VerticalPos			0x30
#define ADJ_Phase				0x3E
#define ActiveControl            		0x52
#define Color_Temp				0x54
#define Select_InputSource		0x60
#define ADJ_SpeakerVolume 		0x62
#define ADJ_Language			0xCC//0x68
#define ADJ_Red_Blacklevel        	0x6C
#define ADJ_Green_Blacklevel     	0x6E
#define ADJ_Blue_Blacklevel      	0x70
#define AudioMute				0x8D
#define SyncType					0xA8
#define DDCCI_Settings			0xB0
#define FlatPanellayout               	0xB2
#define RGBOrdering				0xB4
#define MonitorType				0xB6
#define H_Frequency           		0xAC
#define V_Frequency           		0xAE
#define DisplayUsageTime        	0xC0
#define APEnableKey				0xC6
#define DisplayControlType   		0xC8
#define FWLevel               			0xC9
#define OSDEnable             		0xCA
#define PowerMode				0xD6
#define VCPVersion                 		0xDF
#define ADJ_ControlLock			0xE3
#if ENABLE_FREESYNC
#ifndef VCP_FREESYNC_MODE
#define VCP_FREESYNC_MODE						0xED
#endif
#define VCP_FREESYNC_MODE_DISABLE			0x00
#define VCP_FREESYNC_MODE_ENABLE				0x01
#define VCP_FREESYNC_MODE_MAX_VALUE			VCP_FREESYNC_MODE_ENABLE
#endif
#define HoursRunning				0xFA
#define ADJ_HotKey              		0xFB
#define ADJ_OSD_TurnOff        	 	0xFC
#define DisplayTime				0xFF
#define Contrast_Auto			0x37
#define ADJ_OSD_HorizontalPos	0x38
#define ADJ_OSD_VerticalPos		0x39
#define DefaultColorChange		0x3B
#define TEST_SaveCurrentSetting	0xF4
#define TEST_GETHTotal			0xF3
#define TEST_GETVTotal			0xF2
#define TEST_GETSrcMode		0xF1
//#define TEST_GETRegE1			0xE1
//#define TEST_GETHStart		0xF1
//#define TEST_GETVStart		0xF0
#define FactoryCommand			0xC0
#define ModeChangeRequest		0x11
#define GetTimingMode			0x14
#define EEPROMRead				0x09
#define EEPROMWrite				0x02
#define CommonDataEntry		0x05
#define TimingDataEntry			0x06
#define AssetRead				0x0B
#define AssetWrite				0x0E
#define WhiteBalanceRead		0x23
#define WhiteBalanceWrite		0x24
#define MPUReset					0x00


//Zhifeng.Wu Define For I-Menu
#define TPV_App_Command		0xF8
#define IMenu_Application		0xE1

#define ECO_Mode				0x11
#define Gamma					0x12
#define DCR						0x13

#define Full_Enhance				0x21
#define Nature_Skin				0x22
#define Sky_Blue					0x23
#define Green_Field				0x24
#define Auto_Detect				0x25
#define Demo					0x26


#define FrameSize				0x31
#define PB_Brightness			0x32
#define PB_Contrast				0x33
#define PB_Hue					0x34
#define PB_Saturation			0x35
#define PB_Hpos					0x36
#define PB_Vpos					0x37
#define PB_BrightFrame			0x38
#define PB_AutoPowerDown        0x41



#if ColorTool_Clear_Time
#define GetUserTime                        0x7E
#define AutoColorDDCCI                     0x1F
#define CleanUsedTime                      0x7D
#endif

//=========================================================
//#define ClockAdjRange		200
//#define AdjustClockRange		100
//#define MaxHStart			UserPrefAutoHStart+50
//#define MinHStart  			UserPrefAutoHStart-50
//#define MaxVStart			(2*StandardModeVStart)
//#define MinVStart	        		0
//#define MaxClock				(StandardModeHTotal+AdjustClockRange)  
//#define MinClock				(StandardModeHTotal-AdjustClockRange)  
#define MaxClockValue		(StandardModeHTotal+ClockAdjRange)
#define MinClockValue		(StandardModeHTotal-ClockAdjRange)
//#define MaxHStartValue	    (UserPrefHTotal-msRead2Byte(SPRHDC_H))
//#define MinHStartValue	    0x40
#define MaxHStartValue		(UserPrefAutoHStart+50)
#define MinHStartValue		(UserPrefAutoHStart-50)
//#define MaxVStartValue	    ((SrcVTotal-msRead2Byte(SPRVDC_H)))
//#define MinVStartValue	    (0x02)
//#define MaxVStartValue	    (2*StandardModeVStart)
//#define MinVStartValue	    (0x00)
#define MaxOsdHStartValue	100
#define MinOsdHStartValue	0
#define MaxOsdVStartValue	100
#define MinOsdVStartValue	0


// receive/transmit buffer syntax defines
#define LENGTH							0
#define COMMAND						1
#define DATA1							2
#define DATA2							3
#define CHKSUM							4
// DDC2Bi receive/transmit status bytes definitions
#define DDC2B_CLEAR						0
#define DDC2B_SRCADDRESS				1
#define DDC2B_COMMAND					2
#define DDC2B_RECBODY					3
#define DDC2B_WAITFORCK				4
#define DDC2B_COMPLETED				5
#define DDC2B_MSGON					6
#define DDC2B_OVER						7
// DDC2Bi standard definitions
#define DDC2B_DEST_ADDRESS				0x6e
#define DDC2B_SRC_ADDRESS				0x51
#define DDC2Bi_CONTROL_STATUS_FLAG		0x80
// checksum start values
#define INITRxCK			DDC2B_SRC_ADDRESS ^ DDC2B_DEST_ADDRESS
#define INITTxCK			0x50 ^ DDC2B_DEST_ADDRESS
#define INITNMVTxCK		0x50^DDC2B_SRC_ADDRESS
//interrupt flag
#define TXBI	 BIT4   // Annie 2006.7.6 BIT7
#define RCBI	 BIT3  // Annie 2006.7.6  BIT6
#define SlvBMI	BIT5
// maximum wait time (msec) for getting the transmit buffer
#define MAX_TXWAIT_DELAY						20
#define Response_Command_LENGTH      4


	#define LanTChineseCode			0x01
	#define LanEnglistCode 			0x02
	#define LanFrenchCode			0x03
	#define LanGermanCode			0x04
	#define LanItalianCode			0x05
	#define LanJapaneseCode			0x06
	#define LanKoreanCode			0x07
	#define LanPortugueseCode_Portugal		0x08
	#define LanRussianCode			0x09
	#define LanSpanishCode			0x0A
	#define LanSwedishCode			0x0B
	#define LanTurkishCode			0x0C
	#define LanSChineseCode			0x0D
	#define LanPortugueseCode_Brazil  0x0E
	#define LanCzechCode			0x12
	#define LanPolishCode			0x1E
	#define LanNorskCode				0x1D
	#define LanFinnishCode			0x16
	#define LanDanskCode			0x13
	#define LanDutchCode			0x14
//==============NewFactoryCommand=================

#define TPVFactoryCode		0xFE
#if NewFactoryCommand

#define SetOn				1
#define SetOff				0

//W & R================
#define TPV_AdjBrightness	0x10
#define TPV_AdjContrast		0x12
#define TPV_AdjRedGain		0x16
#define TPV_AdjGreenGain	0x18
#define TPV_AdjBlueGain		0x1A

#define TPV_SetDefLanguage			0xCC

	

#define TPV_SelectInput				0x60
#define TPV_SelectGamma			0x72
#define TPV_HDCPReadWriteStart		0xEA

//Write Only=============
#define TPV_RestorFactory		0x04
#define TPV_AutoConfig			0x1E
#define TPV_AutoColor			0x1F
#define TPV_SaveOrRecallColTmp	0x14
	#define ColorTempSRGB		0x01
	#define ColorTempNative		0x02
	#define ColorTemp4000K		0x03
	#define ColorTemp5000K		0x04
	#define ColorTemp6500K		0x05
	#define ColorTemp7500K		0x06/*Or 7800K*/
	#define ColorTemp8200K		0x07/*Or 8500K*/
	#define ColorTemp9300K		0x08
	#define ColorTemp10000K		0x09
	#define ColorTemp11500K		0x0A
	#define ColorTempUser		0x0B
	#define SaveAllColorTemp		0x00


#define TPV_FactoryAutoAlignment 0xE1
	#define SetFactoryMode		0xA0
	#define NVMInit				0xA1
	#define SetBurnMode			0xA2
	#define ClearBacklitTime	0xA3
	#define SetDPSAndICareEnable	0xA4	//130311 Modify
	#define SetProduceMode		0xA5
	#define LogoONOFF		    0xA7
	#define AdjPanelVCOM		0xA9
	#define HDCPReadWriteStart	0xE0
    #define MACADDRESSWrite       0xF0  // Nick add 20130204
#if Enable_Gamma
    #define AdjGammaMode        0x12 
#endif
#if 0//def WH_REQUEST
         #if 1//WH_REQUEST_DDCCI_POWERSAVING
	#define PowerOff 0x05
	#define ForceIntoPowerSaving 0x00
	#endif
#endif
	

#endif 

#if ENABLE_DeltaE
//**************************MSTAR COMMAND Code***************************//
#define MStar_Command         		    0xCC
#define MS_AutoGamma_OnOff           0x30
#define MS_AutoGamma_SetBGColor  0x31
#define MS_WR_PostGamma      	    0x32
#if ENABLE_USE_NewDeltaE
#define MS_GET_MODEL_NAME           0x36
#endif
#define MS_ColorEngine_OnOff   	    0x40
#define MS_LoadColorMode            0x42
#define MS_LoadPostGamma            0x44
#define MS_WR_ColorMatrix      	    0x84
#define MS_SAVE_ColorMatrix             0x86
#define MS_Read_ACK                         0x8E  
#define MS_WR_BLOCK                 0x90
#endif

