#ifndef __PanelM216H1L01__
    #define __PanelM216H1L01__
    #define PanelName               _M,_2,_1,_6,_H,_1,_L,_0,_1//M216H1L01
    #define PANEL_TYPE	        PANEL_22_WIDE
	
    #define PanelDither		8
    
    #define PanelTTL			0
    #define PanelTCON		0
    #define PanelLVDS		0xFF
    #define PanelRSDS		0
    #define PanelminiLVDS      0 
	#define PANEL_VCOM_ADJUST        0x00

    #define LVDS_TIMode		0xff
    #define PanelDualPort		0xFF
    #define PanelSwapPort		0xFF
    #define PanelSwapOddML		0
    #define PanelSwapEvenML		0
    #define PanelSwapOddRB		0//xFF
    #define PanelSwapEvenRB		0//xFF
    #define PanelSwapMLSB		0

    #define PanelDClkDelay    8
    #define PanelInvDE      0
    #define PanelInvDClk    0
    #define PanelInvHSync   0
    #define PanelInvVSync   0
    // driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
    #define PanelDCLKCurrent  1 // Dclk current
    #define PanelDECurrent    1 // DE signal current
    #define PanelOddDataCurrent 1 // Odd data current
    #define PanelEvenDataCurrent  1 // Even data current

    #define PanelOnTiming1		20//60//20 // time between panel & data while turn on power
    #define PanelOnTiming2		450//350//220 // time between data & back light while turn on power
    #define PanelOffTiming1		100//350//220 // 2005/5/3// time between back light & data while turn off power 
    #define PanelOffTiming2		20//20//25 // 2005/5/3//10 // time between data & panel while turn off power 

    #define PanelHSyncWidth		25
    #define PanelHSyncBackPorch	85
    
    #define PanelVSyncWidth		3
    #define PanelVSyncBackPorch	13
    
    #define PanelHStart   (PanelHSyncWidth+PanelHSyncBackPorch)
    #define PanelVStart   (PanelVSyncWidth+PanelVSyncBackPorch)


    #define PanelWidth    1920
    #define PanelHeight   1080
    #define PanelHTotal   2100  
    #define PanelVTotal   1130 
    #define PanelMaxHTotal     2176
    #define PanelMinHTotal     2048
    #define PanelMaxVTotal     2047 
    #define PanelMinVTotal    1088

    
    #define PanelDCLK            140  //  120
    #define PanelMaxDCLK          170//170 // 160 // 150 //  162  //
    #define PanelMinDCLK          116//   100
    //HSYNC
    #define GPOA_VStart   0
    #define GPOA_VEnd   0
    #define GPOA_HStart   0
    #define GPOA_HEnd   0
    #define GPOA_Control  0
#endif
