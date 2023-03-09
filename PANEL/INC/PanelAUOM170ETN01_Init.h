#define PanelName				"AUOM170ETN01"//jun 20130730
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

#define PanelDither           	8

#define PanelDClkDelay			0
#define PanelInvDClk			0
#define PanelInvDE				0
#define PanelInvHSync			0
#define PanelInvVSync			0

#define _PanelOnTiming1    		20// petit 20130715
#define _PanelOnTiming2    		550
#define _PanelOffTiming1 			150
#define _PanelOffTiming2 			20

#define _PanelHSyncWidth   		35
#define _PanelHSyncBackPorch 	21
#define _PanelVSyncWidth   		3
#define _PanelVSyncBackPorch 	7
#define _PanelHStart   			(_PanelHSyncWidth+_PanelHSyncBackPorch)
#define _PanelVStart   			(_PanelVSyncWidth+_PanelVSyncBackPorch)


#define _PanelWidth				1280
#define _PanelHeight			1024
#define _PanelHTotal			1688
#define _PanelVTotal			1066
#define _PanelMaxHTotal		 	2640
#define _PanelMinHTotal			_PanelHTotal//1460  petit 20130909
#define _PanelMaxVTotal			1873
#define _PanelMinVTotal			1036


#define _PanelDCLK				128
#define _PanelMaxDCLK			186
#define _PanelMinDCLK			104


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
