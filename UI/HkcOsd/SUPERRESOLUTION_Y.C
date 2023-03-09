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
    #include "Panel.h"
#endif

Bool SetSR_DEMOSize(BYTE ucSize,WORD DEMO_Hsize);
#if ENABLE_SUPERRESOLUTION
void mStar_AdjustContrast(BYTE contrast);//20130427
#endif
//extern   void SetColorBoostWin( BYTE mode );
extern 	Bool SetColorEngineToOff(void);
extern 	Bool SetDisplayModeToWeb(void);
extern 	void mStar_WaitForDataBlanking(void);
#if ENABLE_SUPERRESOLUTION
    RegTblType code tSR_OffCtrl[]=
    {
		{SC0_5E, 0x00,0xF3},	 //  H peaking 
		{SC3_3B, 0x00,0x87},
		{SC0_5C, 0x01,0x01},	//20130427 	
		{SC0_5D, 0x00,0x1F},		
		{SC3_50, 0x20,0xFF},	//20130427 				
		{SC3_41, 0x00,0x1F},		
		{SC3_51, 0x00,0xFF},		
		{SC3_3E, 0xFF,0xFF},	//20130427 		
		{SC3_3F, 0x00,0xFF},
		{SC3_52, 0x00,0x01},		
		{SC3_4E, 0x00,0xFF},
		{SC3_4F, 0x00,0xFF},		
		{SC3_3C, 0x00,0xE0},		
		{SC3_C0, 0x00,0x3F},		
		{SC3_C1, 0x00,0x3F},
		{SC3_C2, 0x00,0x3F},
		{SC3_C3, 0x00,0x3F},  
		{SC3_C4, 0x00,0x3F},  
		{SC3_C5, 0x00,0x3F},  
		{SC3_C6, 0x00,0x3F},  
		{SC3_C7, 0x00,0x3F},  
		{SC3_C8, 0x00,0x3F},  
		{SC3_C9, 0x00,0x3F},  
		{SC3_CA, 0x00,0x3F},  
		{SC3_CB, 0x00,0x3F},  
		{SC3_CC, 0x00,0x3F},  
		{SC3_CD, 0x00,0x3F},  
		{SC3_CE, 0x00,0x3F},  
		{SC3_CF, 0x00,0x3F},  

		{SCA_18, 0x00,0xFF},     //  V peaking  Range
        {SCA_19, 0x00,0x0F},   
        {SCA_1A, 0x00,0xFF},          
        {SCA_1B, 0x00,0x0F}, 
        {SCA_1C, 0x00,0xFF},
        {SCA_1D, 0x00,0x07},   
        {SCA_1E, 0x00,0xFF},          
        {SCA_1F, 0x00,0x07}, 
        
		{SCA_20, 0x00,0xF3},     //  V peaking 
        {SCA_21, 0x00,0xF3},   
        {SCA_22, 0x00,0x9F},          
        {SCA_24, 0x00,0x1F},          
        {SCA_26, 0x00,0xFF},          
        {SCA_27, 0x00,0xFF},         
        {SCA_29, 0x00,0x07},    
        {SCA_30, 0x00,0x3F},   
        {SCA_31, 0x00,0x3F},   
        {SCA_32, 0x00,0x3F},   
        {SCA_33, 0x00,0x3F},   
        {SCA_34, 0x00,0x3F},   
        {SCA_35, 0x00,0x3F},   
        {SCA_36, 0x00,0x3F},   
        {SCA_37, 0x00,0x3F}, 

		{SC3_4B, 0x00,0xDF},  
 
    };
    
    RegTblType code tSR_HPeakingMax[]=
    { 
        {SC0_5E, 0x82,0xF3},
		{SC3_3B, 0x05,0x87},
		{SC0_5C, 0x01,0x01},			
		{SC0_5D, 0x00,0x1F},			
		{SC3_50, 0x00,0xFF},	
		
		{SC3_41, 0x1E,0x1F},		
		{SC3_51, 0xF8,0xFF},	
		
		{SC3_3E, 0x3F,0xFF},		
		{SC3_3F, 0x3F,0xFF},
		{SC3_52, 0x01,0x01},		
		{SC3_4E, 0x3F,0xFF},
		{SC3_4F, 0x3F,0xFF},		
		{SC3_3C, 0x60,0xE0},	
		
		{SC3_C0, 0x21,0x3F},		
		{SC3_C1, 0x21,0x3F},
		{SC3_C2, 0x21,0x3F},
		{SC3_C3, 0x23,0x3F},  
		{SC3_C4, 0x25,0x3F},  
		{SC3_C5, 0x28,0x3F},  
		{SC3_C6, 0x2D,0x3F},  
		{SC3_C7, 0x3C,0x3F},  
		{SC3_C8, 0x3F,0x3F},  
		{SC3_C9, 0x3F,0x3F},  
		{SC3_CA, 0x3F,0x3F},  
		{SC3_CB, 0x3F,0x3F},  
		{SC3_CC, 0x3F,0x3F},  
		{SC3_CD, 0x3C,0x3F},  
		{SC3_CE, 0x28,0x3F},  
		{SC3_CF, 0x10,0x3F}, 
    
    };
    
    RegTblType code tSR_HPeakingMid[]=
    {
        {SC0_5E, 0x82,0xF3},
		{SC3_3B, 0x05,0x87},
		{SC0_5C, 0x01,0x01},			
		{SC0_5D, 0x00,0x1F},			
		{SC3_50, 0x00,0xFF},	
		
		{SC3_41, 0x1C,0x1F},		
		{SC3_51, 0xF0,0xFF},	
		
		{SC3_3E, 0x2F,0xFF},		
		{SC3_3F, 0x2F,0xFF},
		{SC3_52, 0x01,0x01},		
		{SC3_4E, 0x2F,0xFF},
		{SC3_4F, 0x2F,0xFF},		
		{SC3_3C, 0x60,0xE0},	
		
		{SC3_C0, 0x21,0x3F},		
		{SC3_C1, 0x21,0x3F},
		{SC3_C2, 0x21,0x3F},
		{SC3_C3, 0x23,0x3F},  
		{SC3_C4, 0x25,0x3F},  
		{SC3_C5, 0x28,0x3F},  
		{SC3_C6, 0x2D,0x3F},  
		{SC3_C7, 0x3C,0x3F},  
		{SC3_C8, 0x3F,0x3F},  
		{SC3_C9, 0x3F,0x3F},  
		{SC3_CA, 0x3F,0x3F},  
		{SC3_CB, 0x3F,0x3F},  
		{SC3_CC, 0x3F,0x3F},  
		{SC3_CD, 0x3C,0x3F},  
		{SC3_CE, 0x28,0x3F},  
		{SC3_CF, 0x21,0x3F},    
    };
    
    RegTblType code tSR_HPeakingLow[]=
    {
        {SC0_5E, 0x82,0xF3},
		{SC3_3B, 0x05,0x87},
		{SC0_5C, 0x01,0x01},			
		{SC0_5D, 0x00,0x1F},			
		{SC3_50, 0x00,0xFF},	
		
		{SC3_41, 0x0F,0x1F},		
		{SC3_51, 0xEB,0xFF},	
		
		{SC3_3E, 0x1F,0xFF},		
		{SC3_3F, 0x1F,0xFF},
		{SC3_52, 0x01,0x01},		
		{SC3_4E, 0x1F,0xFF},
		{SC3_4F, 0x1F,0xFF},		
		{SC3_3C, 0x60,0xE0},	
		
		{SC3_C0, 0x21,0x3F},		
		{SC3_C1, 0x21,0x3F},
		{SC3_C2, 0x21,0x3F},
		{SC3_C3, 0x23,0x3F},  
		{SC3_C4, 0x25,0x3F},  
		{SC3_C5, 0x28,0x3F},  
		{SC3_C6, 0x2D,0x3F},  
		{SC3_C7, 0x3C,0x3F},  
		{SC3_C8, 0x3F,0x3F},  
		{SC3_C9, 0x3F,0x3F},  
		{SC3_CA, 0x3F,0x3F},  
		{SC3_CB, 0x3F,0x3F},  
		{SC3_CC, 0x3F,0x3F},  
		{SC3_CD, 0x3C,0x3F},  
		{SC3_CE, 0x28,0x3F},  
		{SC3_CF, 0x21,0x3F},    
    };
    
    RegTblType code tSR_VPeakingMax[]=
    { 
        {SCA_20, 0xA2,0xF3},     //  V peaking 
        {SCA_21, 0x83,0xF3},   
        {SCA_22, 0x17,0x9F},            
        {SCA_24, 0x0D,0x1F},          
        {SCA_26, 0x3F,0xFF},          
        {SCA_27, 0x3F,0xFF},           
        {SCA_29, 0x01,0x07},         
        {SCA_30, 0x36,0x3F},   
        {SCA_31, 0x34,0x3F},   
        {SCA_32, 0x20,0x3F},   
        {SCA_33, 0x25,0x3F},   
        {SCA_34, 0x21,0x3F},   
        {SCA_35, 0x28,0x3F},   
        {SCA_36, 0x25,0x3F}, 
        
        {SCA_37, 0x18,0x3F}, 
    
    };
    
    RegTblType code tSR_VPeakingMid[]=
    {
        {SCA_20, 0xA2,0xF3},     //  V peaking 
        {SCA_21, 0x83,0xF3},   
        {SCA_22, 0x17,0x9F},             
        {SCA_24, 0x0C,0x1F},          
        {SCA_26, 0x2F,0xFF},          
        {SCA_27, 0x2F,0xFF},            
        {SCA_29, 0x01,0x07},         
        {SCA_30, 0x36,0x3F},   
        {SCA_31, 0x34,0x3F},   
        {SCA_32, 0x20,0x3F},   
        {SCA_33, 0x25,0x3F},   
        {SCA_34, 0x21,0x3F},   
        {SCA_35, 0x28,0x3F},   
        {SCA_36, 0x25,0x3F},         
        {SCA_37, 0x20,0x3F}, 
    
    };
    
    RegTblType code tSR_VPeakingLow[]=
    {
        {SCA_20, 0xA2,0xF3},     //  V peaking 
        {SCA_21, 0x83,0xF3},   
        {SCA_22, 0x17,0x9F},            
        {SCA_24, 0x0B,0x1F},          
        {SCA_26, 0x1F,0xFF},          
        {SCA_27, 0x1F,0xFF},            
        {SCA_29, 0x01,0x07},         
        {SCA_30, 0x36,0x3F},   
        {SCA_31, 0x34,0x3F},   
        {SCA_32, 0x20,0x3F},   
        {SCA_33, 0x25,0x3F},   
        {SCA_34, 0x21,0x3F},   
        {SCA_35, 0x28,0x3F},   
        {SCA_36, 0x25,0x3F},   
        {SCA_37, 0x20,0x3F}, 
    
    };
    
    RegTblType code tSR_ColorMax[]=
    {
        {SC3_4B, 0xC2,0xDF},      
    };
    
    RegTblType code tSR_ColorMid[]=
    {        
        {SC3_4B, 0xC2,0xDF},      
    };
    
    RegTblType code tSR_ColorLow[]=
    {        
        {SC3_4B, 0xC2,0xDF},          
    };
#endif


#if 0//ENABLE_SUPERRESOLUTION
    BYTE code t_demoMWEDLC_VideoSportsLevel1_Table[]=
    {
        0x05,0x0C,0x10,0x1E,0x30,0x44,0x59,0x6E,0x85,0x9A,0xAD,0xBC,0xCD,0xDE,0xED,0xF8,
        0x87,0x9B,0x0F,0xC2,0xBD,0x4E,0xC6,0xFD,0xF3,0x3E,0xE9,0x35,0x75,0xED,0x76,0x8D,
        0xC1,0x74,0xD4,0x3C,0x3A,0x18,0xE0,0x0A,0xD6,0xE3,0x33,0x0C,0x0A,0x84,0xB7,0xA0,
    };
    BYTE code t_demoMWEDLC_VideoSportsLevel2_Table[]=
    {
        0x00,0x08,0x15,0x25,0x36,0x47,0x59,0x6C,0x80,0x93,0xA3,0xB3,0xC4,0xD3,0xE2,0xF1,
        0x87,0x9B,0x0F,0xC2,0xBD,0x4E,0xC6,0xFD,0xF3,0x3E,0xE9,0x35,0x75,0xED,0x76,0x8D,
        0xC1,0x74,0xD4,0x3C,0x3A,0x18,0xE0,0x0A,0xD6,0xE3,0x33,0x0C,0x0A,0x84,0xB7,0xA0,
    };
    BYTE code t_demoMWEDLC_VideoSportsLevel3_Table[]=
    {
        0x00,0x0A,0x1A,0x2A,0x3A,0x4A,0x5B,0x6C,0x7D,0x90,0xA1,0xB2,0xC3,0xD4,0xE5,0xF0,
        0x87,0x9B,0x0F,0xC2,0xBD,0x4E,0xC6,0xFD,0xF3,0x3E,0xE9,0x35,0x75,0xED,0x76,0x8D,
        0xC1,0x74,0xD4,0x3C,0x3A,0x18,0xE0,0x0A,0xD6,0xE3,0x33,0x0C,0x0A,0x84,0xB7,0xA0,
    };
#endif


#if ENABLE_SUPERRESOLUTION

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
    msWrite2Byte(SC3_10, 0x1100); // boarder   20130503 follow AOC FW spec.
    msWrite2Byte(SC3_12, 0x0000);           // boarder

	if(USER_PREF_SRDEMO==1)
    	msWriteByteMask(SC0_32,BIT4,BIT4);	// boarder Enable
    else		
		msWriteByteMask(SC0_32,0,BIT4);	// boarder Disable
}

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

    if (SuperResFlag==0 )
    {
        for(i=0;i<sizeof(tSR_OffCtrl)/sizeof(RegTblType);i++)
            msWriteByteMask(tSR_OffCtrl[i].wReg,tSR_OffCtrl[i].ucValue,tSR_OffCtrl[i].ucMask);

        msWriteByteMask(SC3_B8,0,BIT7);	//120509 Modify
        msAdjustSharpness( MAIN_WINDOW, GetRealSharpness(), 0 );        
        #if 0//DEBUG_MSG
           // printMsg("SUPER_RESOLUTION_OFF_!!");
        #endif
		mStar_AdjustContrast(UserPrefContrast);
		mStar_WaitForDataBlanking();
		msAccOnOff(0);
    }
    else
    {
        // Settings for Different Strength
        if (USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_LOW)//(SuperResStep==3)
        {
            for(i=0;i<sizeof(tSR_HPeakingLow)/sizeof(RegTblType);i++)
                msWriteByteMask(tSR_HPeakingLow[i].wReg,tSR_HPeakingLow[i].ucValue,tSR_HPeakingLow[i].ucMask);
            for(i=0;i<sizeof(tSR_VPeakingLow)/sizeof(RegTblType);i++)
                msWriteByteMask(tSR_VPeakingLow[i].wReg,tSR_VPeakingLow[i].ucValue,tSR_VPeakingLow[i].ucMask);
            for(i=0;i<sizeof(tSR_ColorLow)/sizeof(RegTblType);i++)
                msWriteByteMask(tSR_ColorLow[i].wReg,tSR_ColorLow[i].ucValue,tSR_ColorLow[i].ucMask);
   
            msWriteByteMask(SC3_B8,BIT7,BIT7);// DLC
            #if 0//DEBUG_MSG
                //printMsg("SUPER_RESOLUTION_LOW_!!");
            #endif
        }
        else if (USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_MIDDLE)//(SuperResStep==2)
        {
            for(i=0;i<sizeof(tSR_HPeakingMid)/sizeof(RegTblType);i++)
                msWriteByteMask(tSR_HPeakingMid[i].wReg,tSR_HPeakingMid[i].ucValue,tSR_HPeakingMid[i].ucMask);
            for(i=0;i<sizeof(tSR_VPeakingMid)/sizeof(RegTblType);i++)
                msWriteByteMask(tSR_VPeakingMid[i].wReg,tSR_VPeakingMid[i].ucValue,tSR_VPeakingMid[i].ucMask);
            for(i=0;i<sizeof(tSR_ColorMid)/sizeof(RegTblType);i++)
                msWriteByteMask(tSR_ColorMid[i].wReg,tSR_ColorMid[i].ucValue,tSR_ColorMid[i].ucMask);
            msWriteByteMask(SC3_B8,BIT7,BIT7);// DLC
        }
        else if (USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_HIGH)//(SuperResStep==1)
        {
            for(i=0;i<sizeof(tSR_HPeakingMax)/sizeof(RegTblType);i++)
                msWriteByteMask(tSR_HPeakingMax[i].wReg,tSR_HPeakingMax[i].ucValue,tSR_HPeakingMax[i].ucMask);
            for(i=0;i<sizeof(tSR_VPeakingMax)/sizeof(RegTblType);i++)
                msWriteByteMask(tSR_VPeakingMax[i].wReg,tSR_VPeakingMax[i].ucValue,tSR_VPeakingMax[i].ucMask);
            for(i=0;i<sizeof(tSR_ColorMax)/sizeof(RegTblType);i++)
                msWriteByteMask(tSR_ColorMax[i].wReg,tSR_ColorMax[i].ucValue,tSR_ColorMax[i].ucMask);
            msWriteByteMask(SC3_B8,BIT7,BIT7);// DLC
        }
		
		if(USER_PREF_SRDEMO==1)
		{
			mStar_WaitForDataBlanking();
			msAccOnOff(1);
			CSC_SUB_ENABLE(_ENABLE);
		}
		else
		{
			mStar_WaitForDataBlanking();
			SetSR_DEMOSize(1,DISPLAY_WIDTH);//20130503
			msAccOnOff(1);
			CSC_SUB_ENABLE(_ENABLE);
		}
		msAdjustVideoContrast( SUB_WINDOW, UserPrefContrast );	//130624 Modify
		msAdjustSubBrightness(SUB_WINDOW, 0x80, 0x80, 0x80);	//130624 Modify
    }
	msAdjustVideoRGB(SUB_WINDOW, UserPrefRedColor,UserPrefGreenColor,UserPrefBlueColor);

            #if 1//ENABLE_SUPER_RESOLUTION
               // SET_PRESET_MODE_SUPER_RES_CHECK_FLAG();
                return FALSE;
            #endif
}


Bool Set_VPeakingSize( WORD phstart_point, WORD phend_point, WORD pvstart_point, WORD pvend_point)
{
	msWrite2Byte(SCA_18,phstart_point);	
    msWrite2Byte(SCA_1A,phend_point);	
    msWrite2Byte(SCA_1C,pvstart_point);
    msWrite2Byte(SCA_1E,pvend_point);	
    return TRUE;
}

Bool SetSR_DEMOSize(BYTE ucSize,WORD DEMO_Hsize)
{
    if (ucSize == 1)
    {
        Set_VPeakingSize(0,DEMO_Hsize, 0,  PanelHeight);//petit 20130503 follow AOC FW spec.
        msAccSetup(HSTART_OFFSET, DEMO_Hsize+HSTART_OFFSET, 0,  PanelHeight);//petit 20130503 follow AOC FW spec.
    }
    return TRUE;
}

#endif


