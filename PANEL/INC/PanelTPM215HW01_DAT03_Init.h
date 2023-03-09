#define PanelName				"TPM215HW01-DAT03"//20140730

#define PanelTTL    			0
#define PanelTCON   			0
#define PanelLVDS				0xff
#define PanelRSDS				0
#define PanelminiLVDS      		0 
#define PANEL_VCOM_ADJUST     	0x00


#define _PanelColorDepth		bPanelColorDepth
#define _ChangeModePanelVddOff	bChangeModePanelVddOff


#define PanelDualPort   		0xff

#if MainBoardType==MainBoard_7219_M0C
#define PanelSwapPort		0
#else
#define PanelSwapPort		0xFF
#endif
#if MainBoardType==MainBoard_5276_M0A//petit 20130326
#define _PanelOutputControl1	0x90
#else
#define _PanelOutputControl1	0x10
#endif
#define _PanelOutputControl2	((PanelDualPort &BIT0) | (PanelSwapPort &BIT1))//Scaler Bank 0x43 Setting
//#define _PanelOSContol			0x80
//#define _PanelODRriving			0x55

#define PanelDither           	8

#define PanelDClkDelay			0
#define PanelInvDClk			0
#define PanelInvDE				0
#define PanelInvHSync			0
#define PanelInvVSync			0

#define _PanelOnTiming1    		20
#define _PanelOnTiming2    		500
#define _PanelOffTiming1 		250
#define _PanelOffTiming2 		20

#define _PanelHSyncWidth   		20
#define _PanelHSyncBackPorch 	18
#define _PanelVSyncWidth   		1
#define _PanelVSyncBackPorch 	1
#define _PanelHStart   			(_PanelHSyncWidth+_PanelHSyncBackPorch)
#define _PanelVStart   			(_PanelVSyncWidth+_PanelVSyncBackPorch)


#define _PanelWidth				1920
#define _PanelHeight			1080
#define _PanelHTotal			2120 
#define _PanelVTotal			1130 
#define _PanelMaxHTotal		 	2150
#define _PanelMinHTotal			1984
#define _PanelMaxVTotal			1170
#define _PanelMinVTotal			1084


#define _PanelDCLK				144  
#define _PanelMaxDCLK			180 
#define _PanelMinDCLK			110


#define _DefBurstModeFreq		250

#define _DefMinDutyValue		0x30
#define _DefMaxDutyValue		0xFF

#define _STEPL					0x69
#define _STEPH					0x00
#define _SPANL					0xF4
#define _SPANH					0x01

#define _PanelLVDSSwing1		0x15// 283mV //For old chip

#define _PanelLVDSSwing2			1// 0:242.37mV    1:339.33mV    2:387mV    3:169.67mV    //For TSUMXXN&TSUMXXQ type ic auto tune target voltage
#define _PanelLVDSSwing				(_PanelLVDSSwing1|_PanelLVDSSwing2<<6)

