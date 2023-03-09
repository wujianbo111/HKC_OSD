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


void Set_SRSize(void)
{
	WORD xdata sr_sub_xstart, sr_sub_xend, sr_sub_ystart, sr_sub_yend;
	
	sr_sub_xstart = msRead2Byte(SC3_18);
	sr_sub_xend = msRead2Byte(SC3_1C);
	sr_sub_ystart = msRead2Byte(SC3_1E);
	sr_sub_yend = msRead2Byte(SC3_1A);

	msWrite2Byte(SCA_18, sr_sub_xstart);     				//Hde start
	msWrite2Byte(SCA_1A, sr_sub_xend);     				//Hde end
	msWrite2Byte(SCA_1C, sr_sub_ystart);   				//Vde start
	msWrite2Byte(SCA_1E, sr_sub_yend);   				//Vde end
	
    msWriteByte(SC3_10, 0x00);              // peaking dis.
    //msWrite2Byte(SC3_1A, 0x0436);
    //msWrite2Byte(SC3_1F, 0x01);

    msWriteByte(SC3_47, 0xFF);              // boarder  Color.
    mStar_WaitForDataBlanking();	//120524 Modify
    msWrite2Byte(SC3_10, 0x0011);           // boarder
    msWrite2Byte(SC3_12, 0x0000);           // boarder


    
}
#endif

#if ENABLE_SUPERRESOLUTION

Bool AdjustSuperResolution(void)
{
	Set_SRSize();


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
        //--------------------------------BAND 1-----------------------------------
                    msWriteByteMask(SC0_5E, 0, BIT1); 

                    #if MainWin
                    msWriteByteMask(SC0_5C, BIT0, BIT0 | BIT2 | BIT7);      //MWE peaking en. 
                    msWriteByteMask(SC3_3B, 0, BIT1| BIT7);      //MWE peaking en. 
                    #else // sub win
                    msWriteByteMask(SC3_3B, 0, BIT0 | BIT2 | BIT7);      //MWE peaking en. 
                    #endif
                    
                    //msWriteByteMask(SC3_41, 0x0F, 0x1F);      //MWE peaking coef.
                    msWriteByte(SC3_3E, 0xFF);                  //over shoot limit.
                    msWriteByte(SC3_3F, 0xFF);                  //under shoot limit.
                    
        //--------------------------------BAND 2-----------------------------------
                    msWriteByteMask(SC3_52, 0,BIT0);                    //Main band2 paeking enable and coef 
                    
                    #if MainWin
                    msWriteByteMask(SC3_50, 0x2B,0xDF);                     //Main band2 paeking enable and coef   
                    #else // sub win
                    msWriteByteMask(SC3_51, 0x2B,0xDF);                     //MWE band2 paeking enable and coef   
                    #endif
                    
                    msWriteByte(SC3_4E, 0xFF);                  //Band2 Over shoot limit
                    msWriteByte(SC3_4F, 0xFF);                  //Band2 under shoot limit
                    msWriteByteMask(SC0_5E, 0, BIT7);           //Peaking Step.     ????????????????????
                    
        //--------------------------------ADAPTIVE GAIN-----------------------------------
                    msWriteByteMask(SC3_3C, 0, 0xE0);                   //[7:5]adaptive peaking en.     
                    msWriteByte(SC3_C0, 0);                     //over shoot limit.     
                    msWriteByte(SC3_C1, 0);                     //over shoot limit.     
                    msWriteByte(SC3_C2, 0);                     //over shoot limit.     
                    msWriteByte(SC3_C3, 0);                     //over shoot limit.     
                    msWriteByte(SC3_C4, 0);                     //over shoot limit.
                    msWriteByte(SC3_C5, 0);                     //over shoot limit.
                    msWriteByte(SC3_C6, 0);                     //over shoot limit.
                    msWriteByte(SC3_C7, 0);                     //over shoot limit.
                    msWriteByte(SC3_C8, 0);                     //over shoot limit.
                    msWriteByte(SC3_C9, 0);                     //over shoot limit.
                    msWriteByte(SC3_CA, 0);                     //over shoot limit.
                    msWriteByte(SC3_CB, 0);                     //over shoot limit.
                    msWriteByte(SC3_CC, 0);                     //over shoot limit.
                    msWriteByte(SC3_CD, 0);                     //over shoot limit.
                    msWriteByte(SC3_CE, 0);                     //over shoot limit.
                    msWriteByte(SC3_CF, 0);                     //over shoot limit.
        
        //--------------------------------NM_MWE_EN-----------------------------------
                    msWriteByteMask(SC3_4B, 0, BIT7);       //MWE noise masking enable
                    msWriteByteMask(SC3_4B, 0, 0x1F);       //MWE noise masking gain
                    msWriteByteMask(SC3_4B, 0, BIT6);       //MWE noise masking DITHER enable
        
        //--------------------------------VPEAKING-----------------------------------
                    #if MainWin
                    msWriteByteMask(SCA_20, 0,BIT7|BIT0|BIT1);           //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
                    msWriteByteMask(SCA_20, BIT4,BIT4|BIT5);            //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
                    msWriteByte(SCA_22, 0x08);                                  //[4:0]:MWE Window Post Filter Y channel Coefficient
                    #else // sub win
                    msWriteByteMask(SCA_20, 0,BIT7|BIT6);           //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
                    msWriteByteMask(SCA_20, BIT4,BIT4|BIT5);            //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
                    msWriteByte(SCA_21, 0);                         //[1]:MWE Window Adaptive Peaking Enable [0]:MWE Window Post Filter Enable [7:4]:??????????
                    msWriteByteMask(SCA_22, 0,BIT7);            //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
                    msWriteByte(SCA_24, 0x08);                                  //[4:0]:MWE Window Post Filter Y channel Coefficient
                    #endif

                    //msWriteByte(SCA_23, 0x00);                                    //??????????????
                    msWriteByte(SCA_26, 0xFF);                                  //[7:0]:Peaking Range Overshoot Limit
                    msWriteByte(SCA_27, 0xFF);                                  //[7:0]:Peaking Range Undershoot Limit
                    msWriteByteMask(SCA_29, 0, 0x07);                                   //[2:0]:Adaptive Peaking Gain Step
                            
        //--------------------------------VER_LUT-----------------------------------
                    msWriteByte(SCA_30, 0);                     //Vertical differential adaptive LUT 0 
                    msWriteByte(SCA_31, 0);                     //Vertical differential adaptive LUT 1
                    msWriteByte(SCA_32, 0);                     //Vertical differential adaptive LUT 2  
                    msWriteByte(SCA_33, 0);                     //Vertical differential adaptive LUT 3  
                    msWriteByte(SCA_34, 0);                     //Vertical differential adaptive LUT 4  
                    msWriteByte(SCA_35, 0);                     //Vertical differential adaptive LUT 5  
                    msWriteByte(SCA_36, 0);                     //Vertical differential adaptive LUT 6  
                    msWriteByte(SCA_37, 0);                     //Vertical differential adaptive LUT 7  

                    msAdjustSharpness( MAIN_WINDOW, GetRealSharpness(), 0 );
                    
                    // 120607 coding addition
                    if(InputColorFormat == INPUTCOLOR_RGB && !SETUP_PATH_R2Y())
                    {
                        msWriteByteMask(SC7_20, 0, BIT7);
                    }
                    else
                    {
                        msWriteByteMask(SC7_20, BIT7, BIT7);
                    }
        }
    else
        {
            // Settings for Different Strength
            if (USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_LOW)//(SuperResStep==3)
            {
                //--------------------------------BAND 1-----------------------------------
                            msWriteByteMask(SC0_5E, BIT1, BIT1); 

                            #if MainWin
                            msWriteByteMask(SC0_5C, BIT0 , BIT0 );       //MWE peaking en.     
                             msWriteByteMask(SC3_3B, BIT1, BIT1| BIT7);       //MWE peaking en.     
                             msWriteByteMask(SC0_5D, 0x0A, 0x1F);        //MWE peaking coef.
                             
                            #else //sun Win                             
                            msWriteByteMask(SC3_3B, BIT0 | BIT2, BIT0 | BIT2 | BIT7);       //MWE peaking en.     
                            msWriteByteMask(SC3_41, 0x0F, 0x1F);        //MWE peaking coef.
                            #endif
                            
                            msWriteByte(SC3_3E, 0x1F);                  //over shoot limit.
                            msWriteByte(SC3_3F, 0x1F);                  //under shoot limit.
                            
                //--------------------------------BAND 2-----------------------------------
                            msWriteByteMask(SC3_52, BIT0,BIT0);                     //Main band2 paeking enable and coef    
                            #if MainWin
                            msWriteByteMask(SC3_50, 0xD1,0xDF);                     //Main band2 paeking enable and coef  
                            #else //sun Win                             
                            msWriteByteMask(SC3_51, 0xCE,0xDF);                     //Main band2 paeking enable and coef  
                            #endif
                            
                            msWriteByte(SC3_4E, 0x1F);                  //Band2 Over shoot limit
                            msWriteByte(SC3_4F, 0x1F);                  //Band2 under shoot limit
                            msWriteByteMask(SC0_5E, BIT7, BIT7);            //Peaking Step.     ????????????????????
                            
                //--------------------------------ADAPTIVE GAIN-----------------------------------
                            msWriteByteMask(SC3_3C, 0x60, 0xE0);                    //[7:5]adaptive peaking en.     
                            msWriteByte(SC3_C0, 0x21);                  //over shoot limit.     
                            msWriteByte(SC3_C1, 0x21);                  //over shoot limit.     
                            msWriteByte(SC3_C2, 0x21);                  //over shoot limit.     
                            msWriteByte(SC3_C3, 0x23);                  //over shoot limit.     
                            msWriteByte(SC3_C4, 0x25);                  //over shoot limit.
                            msWriteByte(SC3_C5, 0x28);                  //over shoot limit.
                            msWriteByte(SC3_C6, 0x2D);                  //over shoot limit.
                            msWriteByte(SC3_C7, 0x3C);                  //over shoot limit.
                            msWriteByte(SC3_C8, 0x3F);                  //over shoot limit.
                            msWriteByte(SC3_C9, 0x3F);                  //over shoot limit.
                            msWriteByte(SC3_CA, 0x3F);                  //over shoot limit.
                            msWriteByte(SC3_CB, 0x3F);                  //over shoot limit.
                            msWriteByte(SC3_CC, 0x3F);                  //over shoot limit.
                            msWriteByte(SC3_CD, 0x3c);                  //over shoot limit.
                            msWriteByte(SC3_CE, 0x28);                  //over shoot limit.
                            msWriteByte(SC3_CF, 0x21);                  //over shoot limit.
                
                //--------------------------------NM_MWE_EN-----------------------------------
                            msWriteByteMask(SC3_4B, BIT7, BIT7);        //MWE noise masking enable
                            msWriteByteMask(SC3_4B, 0x02, 0x1F);        //MWE noise masking gain
                            msWriteByteMask(SC3_4B, BIT6, BIT6);        //MWE noise masking DITHER enable
                
                //--------------------------------VPEAKING-----------------------------------
                            #if MainWin
                            if(CURRENT_INPUT_IS_TMDS())
                                {
                                if(gScInfo.InputColor == INPUT_RGB)
                                    {
                                    msWriteByteMask(SCA_20, BIT0|BIT1,BIT7|BIT0|BIT1|BIT6);           //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
									msWriteByteMask(SC0_5E, 0, BIT0); 
                                    }
                                else
                                    {
                                    msWriteByteMask(SCA_20, BIT6|BIT0|BIT1,BIT6|BIT7|BIT0|BIT1);           //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
									msWriteByteMask(SC0_5E, BIT0, BIT0); 
                                    }
                                }
                            else
                                {
                                msWriteByteMask(SCA_20, BIT0|BIT1,BIT7|BIT0|BIT1);           //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
                                }
                            
                            msWriteByte(SCA_22, 0x0B);                                  //[4:0]:MWE Window Post Filter Y channel Coefficient
                            #else // sub win
                            msWriteByteMask(SCA_20, BIT7,BIT7|BIT6);           //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
                            msWriteByteMask(SCA_20, BIT4|BIT5,BIT4|BIT5);           //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
                            msWriteByte(SCA_21, BIT7|BIT1|BIT0);                        //[1]:MWE Window Adaptive Peaking Enable [0]:MWE Window Post Filter Enable [7:4]:??????????
                            msWriteByteMask(SCA_22, 0,BIT7);            //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
                            msWriteByte(SCA_24, 0x0B);                                  //[4:0]:MWE Window Post Filter Y channel Coefficient
                            #endif

                
                            //msWriteByte(SCA_23, 0x00);                                    //??????????????
                            msWriteByte(SCA_26, 0x1F);                                  //[7:0]:Peaking Range Overshoot Limit
                            msWriteByte(SCA_27, 0x1F);                                  //[7:0]:Peaking Range Undershoot Limit
                            msWriteByteMask(SCA_29, 0x01, 0x07);                                    //[2:0]:Adaptive Peaking Gain Step
                                    
                //--------------------------------VER_LUT-----------------------------------
                            msWriteByte(SCA_30, 0x36);                  //Vertical differential adaptive LUT 0 
                            msWriteByte(SCA_31, 0x34);                  //Vertical differential adaptive LUT 1
                            msWriteByte(SCA_32, 0x20);                      //Vertical differential adaptive LUT 2  
                            msWriteByte(SCA_33, 0x25);                  //Vertical differential adaptive LUT 3  
                            msWriteByte(SCA_34, 0x21);                  //Vertical differential adaptive LUT 4  
                            msWriteByte(SCA_35, 0x28);                  //Vertical differential adaptive LUT 5  
                            msWriteByte(SCA_36, 0x25);                  //Vertical differential adaptive LUT 6  
                            msWriteByte(SCA_37, 0x20);                  //Vertical differential adaptive LUT 7  

                           // printMsg("SUPER_RESOLUTION_LOW");
                            
            }
            else if (USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_MIDDLE)//(SuperResStep==2)
            {
                //--------------------------------BAND 1-----------------------------------
                            msWriteByteMask(SC0_5E, BIT1, BIT1); 
                            #if MainWin
                            msWriteByteMask(SC0_5C, BIT0 , BIT0 );       //MWE peaking en.   
                            msWriteByteMask(SC3_3B, BIT1, BIT1| BIT7);       //MWE peaking en.   
                            msWriteByteMask(SC0_5D, 0x0A, 0x1F);        //MWE peaking coef.
                            #else
                            msWriteByteMask(SC3_3B, BIT0 | BIT2, BIT0 | BIT2 | BIT7);       //MWE peaking en.   
                            msWriteByteMask(SC3_41, 0x1C, 0x1F);        //MWE peaking coef.
                            #endif
                            
                            msWriteByte(SC3_3E, 0x2F);                  //over shoot limit.
                            msWriteByte(SC3_3F, 0x2F);                  //under shoot limit.
                            
                //--------------------------------BAND 2-----------------------------------
                            msWriteByteMask(SC3_52, BIT0,BIT0);                     //Main band2 paeking enable and coef    
                            #if MainWin
                            msWriteByteMask(SC3_50, 0xD8,0xDF);                     //Main band2 paeking enable and coef        
                            #else
                            msWriteByteMask(SC3_51, 0xD0,0xDF);                     //Main band2 paeking enable and coef        
                            #endif
                            
                            msWriteByte(SC3_4E, 0x2F);                  //Band2 Over shoot limit
                            msWriteByte(SC3_4F, 0x2F);                  //Band2 under shoot limit
                            msWriteByteMask(SC0_5E, BIT7, BIT7);            //Peaking Step.     ????????????????????
                            
                //--------------------------------ADAPTIVE GAIN-----------------------------------
                            msWriteByteMask(SC3_3C, 0x60, 0xE0);                    //[7:5]adaptive peaking en.     
                            msWriteByte(SC3_C0, 0x21);                  //over shoot limit.     
                            msWriteByte(SC3_C1, 0x21);                  //over shoot limit.     
                            msWriteByte(SC3_C2, 0x21);                  //over shoot limit.     
                            msWriteByte(SC3_C3, 0x23);                  //over shoot limit.     
                            msWriteByte(SC3_C4, 0x25);                  //over shoot limit.
                            msWriteByte(SC3_C5, 0x28);                  //over shoot limit.
                            msWriteByte(SC3_C6, 0x2D);                  //over shoot limit.
                            msWriteByte(SC3_C7, 0x3C);                  //over shoot limit.
                            msWriteByte(SC3_C8, 0x3F);                  //over shoot limit.
                            msWriteByte(SC3_C9, 0x3F);                  //over shoot limit.
                            msWriteByte(SC3_CA, 0x3F);                  //over shoot limit.
                            msWriteByte(SC3_CB, 0x3F);                  //over shoot limit.
                            msWriteByte(SC3_CC, 0x3F);                  //over shoot limit.
                            msWriteByte(SC3_CD, 0x3c);                  //over shoot limit.
                            msWriteByte(SC3_CE, 0x28);                  //over shoot limit.
                            msWriteByte(SC3_CF, 0x21);                  //over shoot limit.
                
                //--------------------------------NM_MWE_EN-----------------------------------
                            msWriteByteMask(SC3_4B, BIT7, BIT7);        //MWE noise masking enable
                            msWriteByteMask(SC3_4B, 0x02, 0x1F);        //MWE noise masking gain
                            msWriteByteMask(SC3_4B, BIT6, BIT6);        //MWE noise masking DITHER enable
                
                //--------------------------------VPEAKING-----------------------------------

                            #if MainWin
                            if(CURRENT_INPUT_IS_TMDS())
                                {
                                if(gScInfo.InputColor == INPUT_RGB)
                                    {
                                    msWriteByteMask(SCA_20, BIT0|BIT1,BIT7|BIT0|BIT1|BIT6);           //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
									msWriteByteMask(SC0_5E, 0, BIT0); 
                                    }
                                else
                                    {
                                    msWriteByteMask(SCA_20, BIT6|BIT0|BIT1,BIT6|BIT7|BIT0|BIT1);           //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
									msWriteByteMask(SC0_5E, BIT0, BIT0); 
                                    }
                                }
                            else
                                {
                                msWriteByteMask(SCA_20, BIT0|BIT1,BIT7|BIT0|BIT1);           //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
                                }
                            
                            msWriteByte(SCA_22, 0x0C);                                  //[4:0]:MWE Window Post Filter Y channel Coefficient
                            #else // sub win
                            msWriteByteMask(SCA_20, BIT7,BIT7|BIT6);            //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
                            msWriteByteMask(SCA_20, BIT4|BIT5,BIT4|BIT5);           //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
                            msWriteByte(SCA_21, BIT7|BIT1|BIT0);                        //[1]:MWE Window Adaptive Peaking Enable [0]:MWE Window Post Filter Enable [7:4]:??????????
                            msWriteByteMask(SCA_22, 0,BIT7);            //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
                            msWriteByte(SCA_24, 0x0C);                                  //[4:0]:MWE Window Post Filter Y channel Coefficient
                            #endif

                
                            //msWriteByte(SCA_23, 0x00);                                    //??????????????
                            msWriteByte(SCA_26, 0x2F);                                  //[7:0]:Peaking Range Overshoot Limit
                            msWriteByte(SCA_27, 0x2F);                                  //[7:0]:Peaking Range Undershoot Limit
                            msWriteByteMask(SCA_29, 0x01, 0x07);                                    //[2:0]:Adaptive Peaking Gain Step
                                    
                //--------------------------------VER_LUT-----------------------------------
                            msWriteByte(SCA_30, 0x36);                  //Vertical differential adaptive LUT 0 
                            msWriteByte(SCA_31, 0x34);                  //Vertical differential adaptive LUT 1
                            msWriteByte(SCA_32, 0x20);                      //Vertical differential adaptive LUT 2  
                            msWriteByte(SCA_33, 0x25);                  //Vertical differential adaptive LUT 3  
                            msWriteByte(SCA_34, 0x21);                  //Vertical differential adaptive LUT 4  
                            msWriteByte(SCA_35, 0x28);                  //Vertical differential adaptive LUT 5  
                            msWriteByte(SCA_36, 0x25);                  //Vertical differential adaptive LUT 6  
                            msWriteByte(SCA_37, 0x20);                  //Vertical differential adaptive LUT 7  
                            //printMsg("SUPER_RESOLUTION_MIDDLE");
                            
            }
            else if (USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_HIGH)//(SuperResStep==1)
            {
                //--------------------------------BAND 1-----------------------------------
                            msWriteByteMask(SC0_5E, BIT1, BIT1); 


                            #if MainWin
                            msWriteByteMask(SC0_5C, BIT0 , BIT0 );       //MWE peaking en.    
                            msWriteByteMask(SC3_3B, BIT1, BIT1| BIT7);       //MWE peaking en.    
                            msWriteByteMask(SC0_5D, 0x0A, 0x1F);        //MWE peaking coef.
                            #else
                            msWriteByteMask(SC3_3B, BIT0 | BIT2, BIT0 | BIT2 | BIT7);       //MWE peaking en.    
                            msWriteByteMask(SC3_41, 0x1E, 0x1F);        //MWE peaking coef.
                            #endif
                            
                            
                            msWriteByte(SC3_3E, 0x3F);                  //over shoot limit.
                            msWriteByte(SC3_3F, 0x3F);                  //under shoot limit.
                            
                //--------------------------------BAND 2-----------------------------------
                            msWriteByteMask(SC3_52, BIT0,BIT0);                     //Main band2 paeking enable and coef   
                            #if MainWin
                            msWriteByteMask(SC3_50, 0xDF,0xDF);                     //Main band2 paeking enable and coef        
                            #else
                            msWriteByteMask(SC3_51, 0xD8,0xDF);                     //Main band2 paeking enable and coef        
                            #endif
                            
                            msWriteByte(SC3_4E, 0x3F);                  //Band2 Over shoot limit
                            msWriteByte(SC3_4F, 0x3F);                  //Band2 under shoot limit
                            msWriteByteMask(SC0_5E, BIT7, BIT7);            //Peaking Step.     ????????????????????
                            
                //--------------------------------ADAPTIVE GAIN-----------------------------------
                            msWriteByteMask(SC3_3C, 0x60, 0xE0);                    //[7:5]adaptive peaking en.     
                            msWriteByte(SC3_C0, 0x21);                  //over shoot limit.     
                            msWriteByte(SC3_C1, 0x21);                  //over shoot limit.     
                            msWriteByte(SC3_C2, 0x21);                  //over shoot limit.     
                            msWriteByte(SC3_C3, 0x23);                  //over shoot limit.     
                            msWriteByte(SC3_C4, 0x25);                  //over shoot limit.
                            msWriteByte(SC3_C5, 0x28);                  //over shoot limit.
                            msWriteByte(SC3_C6, 0x2D);                  //over shoot limit.
                            msWriteByte(SC3_C7, 0x3C);                  //over shoot limit.
                            msWriteByte(SC3_C8, 0x3F);                  //over shoot limit.
                            msWriteByte(SC3_C9, 0x3F);                  //over shoot limit.
                            msWriteByte(SC3_CA, 0x3F);                  //over shoot limit.
                            msWriteByte(SC3_CB, 0x3F);                  //over shoot limit.
                            msWriteByte(SC3_CC, 0x3F);                  //over shoot limit.
                            msWriteByte(SC3_CD, 0x3c);                  //over shoot limit.
                            msWriteByte(SC3_CE, 0x28);                  //over shoot limit.
                            msWriteByte(SC3_CF, 0x10);                  //over shoot limit.
                            
                //--------------------------------NM_MWE_EN-----------------------------------
                            msWriteByteMask(SC3_4B, BIT7, BIT7);        //MWE noise masking enable
                            msWriteByteMask(SC3_4B, 0x02, 0x1F);        //MWE noise masking gain
                            msWriteByteMask(SC3_4B, BIT6, BIT6);        //MWE noise masking DITHER enable
                
                //--------------------------------VPEAKING-----------------------------------
                            #if MainWin
                            
                                if(CURRENT_INPUT_IS_TMDS())
                                    {
                                    if(gScInfo.InputColor == INPUT_RGB)
                                        {
                                        msWriteByteMask(SCA_20, BIT0|BIT1,BIT7|BIT0|BIT1|BIT6);           //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
										msWriteByteMask(SC0_5E, 0, BIT0); 
                                        }
                                    else
                                        {
                                        msWriteByteMask(SCA_20, BIT6|BIT0|BIT1,BIT6|BIT7|BIT0|BIT1);           //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
										msWriteByteMask(SC0_5E, BIT0, BIT0); 
                                        }
                                    }
                                else
                                    {
                                    msWriteByteMask(SCA_20, BIT0|BIT1,BIT7|BIT0|BIT1);           //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
                                    }
                            msWriteByte(SCA_22, 0x0D);                                  //[4:0]:MWE Window Post Filter Y channel Coefficient
                            #else // sub win
                            msWriteByteMask(SCA_20, BIT7,BIT7|BIT6);            //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
                            msWriteByteMask(SCA_20, BIT4|BIT5,BIT4|BIT5);           //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
                            msWriteByte(SCA_21, BIT7|BIT1|BIT0);                        //[1]:MWE Window Adaptive Peaking Enable [0]:MWE Window Post Filter Enable [7:4]:??????????
                            msWriteByteMask(SCA_22, 0,BIT7);            //[7]:SPF line-buffer sram active [1]:Main Window Adaptive Peaking Enable 
                            msWriteByte(SCA_24, 0x0D);                                  //[4:0]:MWE Window Post Filter Y channel Coefficient
                            #endif

                            //msWriteByte(SCA_23, 0x00);                                    //??????????????
                            msWriteByte(SCA_26, 0x3F);                                  //[7:0]:Peaking Range Overshoot Limit
                            msWriteByte(SCA_27, 0x3F);                                  //[7:0]:Peaking Range Undershoot Limit
                            msWriteByteMask(SCA_29, 0x01, 0x07);                                    //[2:0]:Adaptive Peaking Gain Step
                                    
                //--------------------------------VER_LUT-----------------------------------
                            msWriteByte(SCA_30, 0x36);                  //Vertical differential adaptive LUT 0 
                            msWriteByte(SCA_31, 0x34);                  //Vertical differential adaptive LUT 1
                            msWriteByte(SCA_32, 0x20);                      //Vertical differential adaptive LUT 2  
                            msWriteByte(SCA_33, 0x25);                  //Vertical differential adaptive LUT 3  
                            msWriteByte(SCA_34, 0x21);                  //Vertical differential adaptive LUT 4  
                            msWriteByte(SCA_35, 0x28);                  //Vertical differential adaptive LUT 5  
                            msWriteByte(SCA_36, 0x25);                  //Vertical differential adaptive LUT 6  
                            msWriteByte(SCA_37, 0x18);                  //Vertical differential adaptive LUT 7  

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
#endif


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
            CSC_SUB_ENABLE(0);  //120204 Modify
            msAccSetup(DEMO_Hsize+HSTART_OFFSET, DISPLAY_WIDTH+HSTART_OFFSET, 0,  PanelHeight);	//120920 Modify
            msAccOnOff(1);
        }
    return TRUE;
}


