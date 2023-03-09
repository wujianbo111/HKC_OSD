#define PanelName				"PanelM280HKJ_L30"//_M,_2,_3,_6,_H,_3,_L,_A,_3//PanelM236H3LA3

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
#if ModelName==AOC_E2271FW//petit 20121210
#define _PanelOutputControl1	0x90
#else
#define _PanelOutputControl1	0x10
#endif
#define _PanelOutputControl2	((PanelDualPort &BIT0) | (PanelSwapPort &BIT1))//Scaler Bank 0x43 Setting
//#define _PanelOSContol			0x80
//#define _PanelODRriving			0x55

#define PanelDither           	8

#define PanelDClkDelay			8
#define PanelInvDClk			0
#define PanelInvDE				0
#define PanelInvHSync			0
#define PanelInvVSync			0
//130708 petit
#if MainBoardType ==MainBoard_6124_M0A		//Fay 2013/12/4   
#define _PanelOnTiming1    		40
#else
#define _PanelOnTiming1    		20
#endif
#define _PanelOnTiming2    		550
#define _PanelOffTiming1 		250
#define _PanelOffTiming2 		10//20	//fay 20130822

#define _PanelHSyncWidth   		14
#define _PanelHSyncBackPorch 	31
#define _PanelVSyncWidth   		3
#define _PanelVSyncBackPorch 	13
#define _PanelHStart   			(_PanelHSyncWidth+_PanelHSyncBackPorch)
#define _PanelVStart   			(_PanelVSyncWidth+_PanelVSyncBackPorch)


#define _PanelWidth				1920
#define _PanelHeight			1080
#define _PanelHTotal			2200 
#define _PanelVTotal			1125 
#define _PanelMaxHTotal		 	2280//2300	//130910 fay
#define _PanelMinHTotal			2100
#define _PanelMaxVTotal			1130//1380	//130910 fay
#define _PanelMinVTotal			1115


#define _PanelDCLK				148//150  	//130910 fay
#define _PanelMaxDCLK			155//216 	//130910 fay
#define _PanelMinDCLK			135//50	//130910 fay


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

#define PanelMaxVfreq       610//625  // (750+13) // 75Hz		//Fay 2013/9/10   For Panel SPEC Update
#define PanelMinVfreq        570  //(500-13) // 50Hz

