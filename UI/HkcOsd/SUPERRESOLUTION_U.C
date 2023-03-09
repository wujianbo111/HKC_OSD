#include "types.h"
#include "board.h"
#include "global.h"
#include "ms_reg.h"
#include "debug.h"
#include "misc.h"
#include "ms_rwreg.h"
#include "mcu.h"
#include "menufunc.h"
#if MWEFunction
#include "MsDLC.H"
#include "MsACE.H"
#include "MsRegTV.h"
#include "Panel.h"
#endif
Bool SetSR_DEMOSize(BYTE ucSize,WORD DEMO_Hsize);

extern   void SetColorBoostWin( BYTE mode );
#if ENABLE_SUPERRESOLUTION
void mStar_AdjustContrast(BYTE contrast);//20130427
#endif

#if ENABLE_SUPERRESOLUTION
    RegTblType code tSR_OffCtrl[]=
    {
        {SC7_3B, 0x00, 0x04},
        {SC7_3B, 0x00, 0x02},
        {SC7_3B, 0x00, 0x01},
        {SC7_3C, 0x00, 0xF0},
        {SC7_3C, 0x00, 0x0F},
        {SC7_3D, 0x00, 0xC0},
        {SC7_3D, 0x00, 0x1F},
        {SC7_3F, 0x00, 0xC0},
        {SC7_3F, 0x00, 0x1F},
};
    
    RegTblType code tSR_HPeakingMax[]=
    {
        {SC7_3B, 0x00, 0x04},
        {SC7_3B, 0x02, 0x02},
        {SC7_3B, 0x01, 0x01},
        {SC7_3C, 0x80, 0xF0},
        {SC7_3C, 0x08, 0x0F},
        {SC7_3D, 0x00, 0xC0},
        {SC7_3D, 0x00, 0x1F},
        {SC7_3F, 0x00, 0xC0},
        {SC7_3F, 0x1F, 0x1F},
};
    
    RegTblType code tSR_HPeakingMid[]=
    {
        {SC7_3B, 0x00, 0x04},
        {SC7_3B, 0x02, 0x02},
        {SC7_3B, 0x01, 0x01},
        {SC7_3C, 0x80, 0xF0},
        {SC7_3C, 0x08, 0x0F},
        {SC7_3D, 0x00, 0xC0},
        {SC7_3D, 0x00, 0x1F},
        {SC7_3F, 0x00, 0xC0}, //{SC7_3F, 0x80, 0xC0}, nick
        {SC7_3F, 0x18, 0x1F}, // xiandi 20130826
};
    
    RegTblType code tSR_HPeakingLow[]=
    {
        {SC7_3B, 0x00, 0x04},
        {SC7_3B, 0x02, 0x02},
        {SC7_3B, 0x01, 0x01},
        {SC7_3C, 0x80, 0xF0},
        {SC7_3C, 0x08, 0x0F},
        {SC7_3D, 0x00, 0xC0},
        {SC7_3D, 0x00, 0x1F},
        {SC7_3F, 0x00, 0xC0},
        {SC7_3F, 0x0E, 0x1F},
};
#endif
#if 1
void Osd_SubWindow3(WORD xPos, WORD yPos,WORD width, WORD height)
{
    xPos=xPos;
    yPos=yPos;

    width=width;
    height=height;

    msWriteByteMask(SC3_71, 0x00    ,BIT2); // select sub
    //msWriteByte(SC3_70, 0x00);              // MWE 3X3 disable.	//?/?

    #if 0//DEBUG_MSG
       //printMsg("Osd_SubWindow3");
    #endif
    
    msWriteByteMask(SC3_71, BIT0    ,BIT0); // MWE offset disable.
    msWriteByteMask(SC3_3B, 0x00    ,BIT0); // peaking dis.
    msWriteByteMask(SC3_B6, 0x00    ,BIT6); // curve dis

    //msWriteByte(SC3_10, 0x00);              // peaking dis.
    //msWrite2Byte(SC3_1A, 0x0436);
    //msWrite2Byte(SC3_1F, 0x01);

    msWriteByte(SC3_47, 0xFF);              // boarder Color.
    msWrite2Byte(SC3_10, 0x0100); //msWrite2Byte(SC3_10, 0x1100); // boarder   20130503 follow AOC FW spec.  //130813 henry
    msWrite2Byte(SC3_12, 0x0000);           // boarder

	if(USER_PREF_SRDEMO==1)
    	msWriteByteMask(SC0_32,BIT4,BIT4);	// boarder Enable
    else		
		msWriteByteMask(SC0_32,0,BIT4);	// boarder Disable
}

#endif

#if ENABLE_SUPERRESOLUTION
/*

#define WAIT_V_OUTPUT_BLANKING_START()   { if(!SyncLossState()&&PanelOnFlag){SetTimOutConter(30);while(((msReadByte(SC0_E0)&BIT0)==0)&&bTimeOutCounterFlag);\
                                        SetTimOutConter(30);while(((msReadByte(SC0_E0)&BIT0)!=0)&&bTimeOutCounterFlag);}}	//130530 Nick
*/
Bool AdjustSuperResolution(void)
{
    XDATA BYTE i=0;
   
    Osd_SubWindow3(2,0,0x3BB,0x02);
	
   // if ((USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_OFF) || USER_PREF_INPUT_COLOR_FORMAT == INPUT_COLOR_YPBPR || (PRESET_MODE_SUPER_RES_CHECK_FLAG==0))
    if (USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_OFF)
        {
        	//g_ucSRDemo=0;	//?/?
        	Clr_SuperResFlag();
        }
    else
        {
        	//g_ucSRDemo=1;		//120509 Modify
	        Set_SuperResFlag();
    	}
		
        msDlcOnOff(_DISABLE);

    if (SuperResFlag==0)
    {
		WAIT_V_OUTPUT_BLANKING_START(); 	  //130608 xiandi
        for(i=0;i<sizeof(tSR_OffCtrl)/sizeof(RegTblType);i++)
            msWriteByteMask(tSR_OffCtrl[i].wReg,tSR_OffCtrl[i].ucValue,tSR_OffCtrl[i].ucMask);

        msAdjustSharpness( MAIN_WINDOW, GetRealSharpness(), 0 );   
        
        #if 0//DEBUG_MSG
           // printMsg("SUPER_RESOLUTION_OFF_!!");
        #endif
		mStar_AdjustContrast(UserPrefContrast);
		WAIT_V_OUTPUT_BLANKING_START();		//130530 Nick
		msAccOnOff(0);
		WAIT_V_OUTPUT_BLANKING_START();		//130530 Nick
		CSC_SUB_ENABLE(_DISABLE);				//130530 Nick
		WAIT_V_OUTPUT_BLANKING_START();    	//130530 Nick
    }
    else
    {
        // Settings for Different Strength
        if (USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_LOW)//(SuperResStep==3)
        {
            for(i=0;i<sizeof(tSR_HPeakingLow)/sizeof(RegTblType);i++)
                msWriteByteMask(tSR_HPeakingLow[i].wReg,tSR_HPeakingLow[i].ucValue,tSR_HPeakingLow[i].ucMask);
   
            msWriteByteMask(SC3_B8,BIT7,BIT7);// DLC
            #if 0//DEBUG_MSG
                //printMsg("SUPER_RESOLUTION_LOW_!!");
            #endif
        }
        else if (USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_MIDDLE)//(SuperResStep==2)
        {
            for(i=0;i<sizeof(tSR_HPeakingMid)/sizeof(RegTblType);i++)
                msWriteByteMask(tSR_HPeakingMid[i].wReg,tSR_HPeakingMid[i].ucValue,tSR_HPeakingMid[i].ucMask);
            msWriteByteMask(SC3_B8,BIT7,BIT7);// DLC
            #if 0//DEBUG_MSG
                    //printMsg("SUPER_RESOLUTION_MIDDLE_!!");
            #endif
        }
        else if (USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_HIGH)//(SuperResStep==1)
        {
            for(i=0;i<sizeof(tSR_HPeakingMax)/sizeof(RegTblType);i++)
                msWriteByteMask(tSR_HPeakingMax[i].wReg,tSR_HPeakingMax[i].ucValue,tSR_HPeakingMax[i].ucMask);
            msWriteByteMask(SC3_B8,BIT7,BIT7);// DLC
                #if 0//DEBUG_MSG
                    // printMsg("SUPER_RESOLUTION_HIGH_!!");
                #endif
        }

    	//130530 Nick

		
		if(USER_PREF_SRDEMO==1)
		{
			WAIT_V_OUTPUT_BLANKING_START();
			if(SETUP_PATH_RGB())	//130608 xiandi
				CSC_SUB_ENABLE(_ENABLE);
			else
				CSC_SUB_ENABLE(_DISABLE);
			msAdjustSubBrightness( SUB_WINDOW, DefClearVisionSubBrightness, DefClearVisionSubBrightness, DefClearVisionSubBrightness );  //130813 henry
			msAdjustVideoContrast( SUB_WINDOW, UserPrefContrast );	//130812 henry
			WAIT_V_OUTPUT_BLANKING_START();
			msAccOnOff(1);
			WAIT_V_OUTPUT_BLANKING_START();
		}
		else
		{
			WAIT_V_OUTPUT_BLANKING_START();
			SetSR_DEMOSize(1,DISPLAY_WIDTH);//20130503
			WAIT_V_OUTPUT_BLANKING_START();
			if(SETUP_PATH_RGB())	//130608 xiandi
				CSC_SUB_ENABLE(_ENABLE);
			else
				CSC_SUB_ENABLE(_DISABLE);
			msAdjustSubBrightness( SUB_WINDOW, DefClearVisionSubBrightness, DefClearVisionSubBrightness, DefClearVisionSubBrightness );  //130813 henry
			msAdjustVideoContrast( SUB_WINDOW,  UserPrefContrast );	//130812 henry
			WAIT_V_OUTPUT_BLANKING_START();
			msAccOnOff(1);
			WAIT_V_OUTPUT_BLANKING_START();
		}
    }
	msAdjustVideoRGB(SUB_WINDOW, UserPrefRedColor,UserPrefGreenColor,UserPrefBlueColor);
            #if 1//ENABLE_SUPER_RESOLUTION
               // SET_PRESET_MODE_SUPER_RES_CHECK_FLAG();
                return FALSE;
            #endif
}
#endif

#if 0
Bool SetSR_DEMOSize(BYTE ucSize,WORD DEMO_Hsize)
{
        if (ucSize == 1)  // H:5 V:5
        {
            //msAdjustSubBrightness( SUB_WINDOW, 0xFF, 0xFF, 0xFF );
            //msWriteByte( SC8_68, 0xFF );
            //msWriteByte( SC8_6A, 0xFF );
            //msWriteByte( SC8_6C, 0xFF );
            //msWriteByte( SC8_80, 0x00 );
            mStar_WaitForDataBlanking();    //120204 Modify
            CSC_SUB_ENABLE(_ENABLE);
            //CSC_SUB_ENABLE(0);  //120204 Modify
            msAccSetup(DEMO_Hsize+HSTART_OFFSET, DISPLAY_WIDTH+HSTART_OFFSET, 0,  PanelHeight);	//120920 Modify
            msAccOnOff(1);
        }
    return TRUE;
}
#else
Bool SetSR_DEMOSize(BYTE ucSize,WORD DEMO_Hsize)
{
    if (ucSize == 1)
    {
    
        WAIT_V_OUTPUT_BLANKING_START();	//130530 Nick
      // Set_VPeakingSize(0,DEMO_Hsize, 0,  PanelHeight);//petit 20130503 follow AOC FW spec.
        msAccSetup(HSTART_OFFSET, DEMO_Hsize+HSTART_OFFSET, 2,  PanelHeight-1);//petit 20130503 follow AOC FW spec.      
    }
    return TRUE;
}

#endif

