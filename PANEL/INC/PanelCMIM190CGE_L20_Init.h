#define PanelName				"CMIM190CGE"//bian 20130605
#define PanelTTL    			0
#define PanelTCON   			0
#define PanelLVDS				0xff
#define PanelRSDS				0
#define PanelminiLVDS      		0 
#define PANEL_VCOM_ADJUST     	0x00


#define _PanelColorDepth		bPanelColorDepth
#define _ChangeModePanelVddOff	bChangeModePanelVddOff


#define PanelDualPort   		0xff
#define PanelSwapPort   		0xff

#define _PanelOutputControl1	0x10
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
#define _PanelOnTiming2    		250
#define _PanelOffTiming1 		250
#define _PanelOffTiming2 		20

#define _PanelHSyncWidth   		34
#define _PanelHSyncBackPorch 	46
#define _PanelVSyncWidth   		2
#define _PanelVSyncBackPorch 	14
#define _PanelHStart   			(_PanelHSyncWidth+_PanelHSyncBackPorch)
#define _PanelVStart   			(_PanelVSyncWidth+_PanelVSyncBackPorch)


#define _PanelWidth				1440
#define _PanelHeight			900
#define _PanelHTotal			1600
#define _PanelVTotal			926
#define _PanelMaxHTotal		 	1640
#define _PanelMinHTotal			1520//20130723
#define _PanelMaxVTotal			942
#define _PanelMinVTotal			905


#define _PanelDCLK				89
#define _PanelMaxDCLK			116
#define _PanelMinDCLK			64


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
