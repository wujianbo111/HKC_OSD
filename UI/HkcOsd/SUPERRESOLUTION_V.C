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

extern   void SetColorBoostWin( BYTE mode );
extern void mStar_WaitForDataBlanking(void);	//120524 Modify

#if ENABLE_SUPERRESOLUTION

#define MainWin 1


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
    msWrite2Byte(SC3_10, 0x0011);           // boarder
    msWrite2Byte(SC3_12, 0x0000);           // boarder

	if(USER_PREF_SRDEMO==1)
    	msWriteByteMask(SC0_32,BIT4,BIT4);	// boarder Enable
    else		
		msWriteByteMask(SC0_32,0,BIT4);	// boarder Disable
}

Bool AdjustSuperResolution(void)
{
    Osd_SubWindow3(2,0,0x3BB,0x02);

    if (USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_OFF)
        {
            //g_ucSRDemo=0;
            Clr_SuperResFlag();
        }
    else
        {
            //g_ucSRDemo=1;		//120509 Modify
            Set_SuperResFlag();
        }

        msDlcOnOff(_DISABLE);
	 mStar_WaitForDataBlanking();	//120524 Modify

    if (SuperResFlag==0)	//120524 Modify
        {
        //--------------------------------BAND 2-----------------------------------
                    #if MainWin
                    //msWriteByteMask(SC7_20, 0, BIT0);      //Main peaking en. 
                    msWriteByteMask(SC7_3B, 0, 0x80);       //MWE peaking en.  
                    msWriteByteMask(SC7_21, 0, 0xF0);                   //[7:5]adaptive peaking en.     
                    #endif
        //--------------------------------ADAPTIVE GAIN-----------------------------------
                    msWriteByteMask(SC7_62, 0, 0xF0);                   //[7:5]adaptive peaking en.     
                    msWriteByteMask(SC7_63, 0, 0x07);                   //[7:5]adaptive peaking en.     
                   msWriteByteMask(SC7_64, 0, 0x3F);                    //over shoot limit.    
                   msWriteByteMask(SC7_66, 0, 0x3F);                    //over shoot limit.    
                   msWriteByteMask(SC7_68, 0, 0x3F);                    //over shoot limit.    
                   msWriteByteMask(SC7_6A, 0, 0x3F);                    //over shoot limit.    
                   msWriteByteMask(SC7_6C, 0, 0x3F);                    //over shoot limit.    
                   msWriteByteMask(SC7_6E, 0, 0x3F);                    //over shoot limit.    
                   msWriteByteMask(SC7_70, 0, 0x3F);                    //over shoot limit.    
                   msWriteByteMask(SC7_72, 0, 0x3F);                    //over shoot limit.    
                   msWriteByteMask(SC7_D0, 0, BIT7);       //MWE noise masking enable
                   msWriteByteMask(SC7_D0, 0, BIT6);       //MWE noise masking DITHER enable
                    msWriteByteMask(SC7_D0, 0, 0x1F);       //MWE noise masking gain
        
        //--------------------------------VPEAKING-----------------------------------
                    msWriteByteMask(SC7_60, 0,0xFF);          
                    msWriteByteMask(SC7_61, 0, 0xFF);   
			#if CHIP_ID == CHIP_TSUMV
			if(SrcInputType != Input_VGA)
			msWriteByteMask(SC7_23, 0x40,0x40); //20130513 for dot pattern color deviation problem. 
			else
			#endif					
                    msWriteByteMask(SC7_23, 0,0x40);           
                    msWriteByteMask(SC7_23, 0,0x3F);     

                    
                    // 120607 coding addition
                    if(InputColorFormat == INPUTCOLOR_RGB && !SETUP_PATH_R2Y())
                    {
                        msWriteByteMask(SC7_20, 0, BIT7);
                    }
                    else
                    {
                        msWriteByteMask(SC7_20, BIT7, BIT7);
                    }
		    if(SuperResFlag==0)//130306 Modify
		    {
			    if(UserPrefSharpness<DefSharpness
				#if CHIP_ID == CHIP_TSUMV
				|| CURRENT_INPUT_IS_DVI()//20130513 for DVI dot pattern color deviation problem.
				#endif
				)		
				    msAdjustSharpness( MAIN_WINDOW,  GetRealSharpness() ,1);
			    else
				    msAdjustSharpness( MAIN_WINDOW,  GetRealSharpness() ,0);		
		    }
        }
    else
        {
            // Settings for Different Strength
            if (USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_LOW)//(SuperResStep==3)
            {
                    //--------------------------------BAND 2-----------------------------------
#if MainWin
                                msWriteByteMask(SC7_20, 0x01, 0x01);      //Main peaking en. 
                                msWriteByteMask(SC7_3B, 0x00, 0x80);       //MWE peaking en.  
                                msWriteByteMask(SC7_21, 0xA0, 0xF0);                   //[7:5]adaptive peaking en.     
#endif
                    //--------------------------------ADAPTIVE GAIN-----------------------------------
                                msWriteByteMask(SC7_62, 0x01, 0xF0);                   //[7:5]adaptive peaking en.     
                                msWriteByteMask(SC7_63, 0x03, 0x07);                   //[7:5]adaptive peaking en.     
                               msWriteByteMask(SC7_64, 0x30, 0x3F);                    //over shoot limit.    
                               msWriteByteMask(SC7_66, 0x30, 0x3F);                    //over shoot limit.    
                               msWriteByteMask(SC7_68, 0x2E, 0x3F);                    //over shoot limit.    
                               msWriteByteMask(SC7_6A, 0x2E, 0x3F);                    //over shoot limit.    
                               msWriteByteMask(SC7_6C, 0x2C, 0x3F);                    //over shoot limit.    
                               msWriteByteMask(SC7_6E, 0x28, 0x3F);                    //over shoot limit.    
                               msWriteByteMask(SC7_70, 0x26, 0x3F);                    //over shoot limit.    
                               msWriteByteMask(SC7_72, 0x24, 0x3F);                    //over shoot limit.    
                               msWriteByteMask(SC7_D0, 0x80, 0x80);       //MWE noise masking enable
                               msWriteByteMask(SC7_D0, 0x40, 0x40);       //MWE noise masking DITHER enable
                                msWriteByteMask(SC7_D0, 0x01, 0x1F);       //MWE noise masking gain
                    
                    //--------------------------------VPEAKING-----------------------------------
                                msWriteByteMask(SC7_60, 0x10,0xFF);          
                                msWriteByteMask(SC7_61, 0x10, 0xFF);                                
                                msWriteByteMask(SC7_23, 0x40,0x40);           
                                msWriteByteMask(SC7_23, 0x14,0x3F);     
                            
            }
            else if (USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_MIDDLE)//(SuperResStep==2)
            {
                //--------------------------------BAND 2-----------------------------------
            #if MainWin
                            msWriteByteMask(SC7_20, 0x01, 0x01);      //Main peaking en. 
                            msWriteByteMask(SC7_3B, 0x00, 0x80);       //MWE peaking en.  
                            msWriteByteMask(SC7_21, 0xA0, 0xF0);                   //[7:5]adaptive peaking en.     
            #endif
                //--------------------------------ADAPTIVE GAIN-----------------------------------
                            msWriteByteMask(SC7_62, 0x01, 0xF0);                   //[7:5]adaptive peaking en.     
                            msWriteByteMask(SC7_63, 0x03, 0x07);                   //[7:5]adaptive peaking en.     
                           msWriteByteMask(SC7_64, 0x30, 0x3F);                    //over shoot limit.    
                           msWriteByteMask(SC7_66, 0x30, 0x3F);                    //over shoot limit.    
                           msWriteByteMask(SC7_68, 0x2E, 0x3F);                    //over shoot limit.    
                           msWriteByteMask(SC7_6A, 0x2E, 0x3F);                    //over shoot limit.    
                           msWriteByteMask(SC7_6C, 0x2C, 0x3F);                    //over shoot limit.    
                           msWriteByteMask(SC7_6E, 0x28, 0x3F);                    //over shoot limit.    
                           msWriteByteMask(SC7_70, 0x26, 0x3F);                    //over shoot limit.    
                           msWriteByteMask(SC7_72, 0x24, 0x3F);                    //over shoot limit.    
                           msWriteByteMask(SC7_D0, 0x80, 0x80);       //MWE noise masking enable
                           msWriteByteMask(SC7_D0, 0x40, 0x40);       //MWE noise masking DITHER enable
                            msWriteByteMask(SC7_D0, 0x01, 0x1F);       //MWE noise masking gain
                
                //--------------------------------VPEAKING-----------------------------------
                            msWriteByteMask(SC7_60, 0x20,0xFF);          
                            msWriteByteMask(SC7_61, 0x20, 0xFF);                                
                            msWriteByteMask(SC7_23, 0x40,0x40);           
                            msWriteByteMask(SC7_23, 0x14,0x3F);     

                            
            }
            else if (USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_HIGH)//(SuperResStep==1)
            {
                //--------------------------------BAND 2-----------------------------------
                            #if MainWin
                            msWriteByteMask(SC7_20, 0x01, 0x01);      //Main peaking en. 
                            msWriteByteMask(SC7_3B, 0x00, 0x80);       //MWE peaking en.  
                            msWriteByteMask(SC7_21, 0x80, 0xF0);                   //[7:5]adaptive peaking en.     
                            #endif
                //--------------------------------ADAPTIVE GAIN-----------------------------------
                            msWriteByteMask(SC7_62, 0x01, 0xF0);                   //[7:5]adaptive peaking en.     
                            msWriteByteMask(SC7_63, 0x03, 0x07);                   //[7:5]adaptive peaking en.     
                           msWriteByteMask(SC7_64, 0x30, 0x3F);                    //over shoot limit.    
                           msWriteByteMask(SC7_66, 0x30, 0x3F);                    //over shoot limit.    
                           msWriteByteMask(SC7_68, 0x2E, 0x3F);                    //over shoot limit.    
                           msWriteByteMask(SC7_6A, 0x2E, 0x3F);                    //over shoot limit.    
                           msWriteByteMask(SC7_6C, 0x2C, 0x3F);                    //over shoot limit.    
                           msWriteByteMask(SC7_6E, 0x28, 0x3F);                    //over shoot limit.    
                           msWriteByteMask(SC7_70, 0x26, 0x3F);                    //over shoot limit.    
                           msWriteByteMask(SC7_72, 0x24, 0x3F);                    //over shoot limit.    
                           msWriteByteMask(SC7_D0, 0x80, 0x80);       //MWE noise masking enable
                           msWriteByteMask(SC7_D0, 0x40, 0x40);       //MWE noise masking DITHER enable
                            msWriteByteMask(SC7_D0, 0x01, 0x1F);       //MWE noise masking gain
                
                //--------------------------------VPEAKING-----------------------------------
                            msWriteByteMask(SC7_60, 0x30,0xFF);          
                            msWriteByteMask(SC7_61, 0x30, 0xFF);                                
                            msWriteByteMask(SC7_23, 0x40,0x40);           
                            msWriteByteMask(SC7_23, 0x17,0x3F);     

                            //printMsg("SUPER_RESOLUTION_HIGH");
                            
            }

                    // 120607 coding addition
                    if(InputColorFormat == INPUTCOLOR_RGB && !SETUP_PATH_R2Y())
                    {
                        msWriteByteMask(SC7_20, 0, BIT7);
                    }
                    else
                    {
                        msWriteByteMask(SC7_20, BIT7, BIT7);
                    }
                msWriteByteMask(SC7_B8,BIT7,BIT7);// DLC
        }

            #if 1//ENABLE_SUPER_RESOLUTION
               // SET_PRESET_MODE_SUPER_RES_CHECK_FLAG();
                return FALSE;
            #endif
}


Bool SetSR_DEMOSize(BYTE ucSize,WORD DEMO_Hsize)
{
        if (ucSize == 1)  // H:5 V:5
        {
            mStar_WaitForDataBlanking();    //120204 Modify
            CSC_SUB_ENABLE(0);  //120204 Modify
            msAccSetup(DEMO_Hsize+HSTART_OFFSET, DISPLAY_WIDTH+HSTART_OFFSET, 0,  PanelHeight);	//120920 Modify
            msAccOnOff(1);
        }
    return TRUE;
}

#endif

