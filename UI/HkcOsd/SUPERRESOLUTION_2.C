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
    RegTblType code tSR_OffCtrl[]=
    {
            {SC7_64,0x05,BIT0},
            {SCA_40,0x00,BIT0},
            {SC9_02,0x00,0xFF},
		{REG_1E2E, BIT4,BIT4},	//120504 Modify
		{SC0_5A,0x00,BIT6},   	//120504 Modify
		{SC7_20, 0x01,0x01},	//120509 Modify
		{SC7_21, 0x40,0xFF},
		{SC7_22, 0x00,0xFF},
		{SC7_60, 0xFF,0xFF},
		{SC7_61, 0xFF,0xFF},
		{SC7_62, 0x00,0xFF},
		{SC7_63, 0x00,0xFF},
		{SC7_66, 0x00,0xFF},
		{SC7_68, 0xFF,0xFF},
		{SC7_69, 0xFF,0xFF},
		{SC7_6C, 0x00,0xFF},
		{SC7_6D, 0x00,0xFF},
		{SC7_6E, 0x00,0xFF},
		{SC7_6F, 0x00,0xFF},
		{SC7_70, 0x00,0xFF},
		{SC7_71, 0x00,0xFF},
		{SC7_72, 0x00,0xFF},
		{SC7_73, 0x00,0xFF},
		{SCA_20,0x10,0xBF},  
		{SCA_21,0x00,0xFF},  
		{SCA_22,0x00,0xFF},  
		{SCA_23,0x00,0xFF},  
		{SCA_26,0xFF,0xFF},  
		{SCA_27,0xFF,0xFF},  
		{SCA_28,0x00,0xFF},  
		{SCA_29,0x00,0xFF},  
		{SCA_2A,0xFF,0xFF},  
		{SCA_2B,0xFF,0xFF},  
		{SCA_30,0x1C,0xFF},  
		{SCA_31,0x20,0xFF},  
		{SCA_32,0x24,0xFF},  
		{SCA_33,0x28,0xFF},  
		{SCA_34,0x24,0xFF},  
		{SCA_35,0x20,0xFF},  
		{SCA_36,0x18,0xFF},  
		{SCA_37,0x10,0xFF},  
		{REG_0C00,0x08,0xFF},
        {SC9_04,0x00,0xFF},
        {SC9_05,0x00,0xFF},
        {SC9_06,0x00,0xFF},
        {SC9_08,0x00,0xFF},
        {SC9_09,0x00,0xFF},
        {SC9_0A,0x00,0xFF},
        {SC9_0B,0x00,0xFF},
        {SC9_0C,0x00,0xFF},
        {SC9_0D,0x00,0xFF},
        {SC9_0E,0x00,0xFF},
        {SC9_0F,0x00,0xFF},
        {SC9_10,0x00,0xFF},
        {SC9_11,0x00,0xFF},
        {SC9_12,0x00,0xFF},
        {SC9_13,0x00,0xFF},
        {SC9_14,0x00,0xFF},
        {SC9_15,0x00,0xFF},
        {SC9_16,0x00,0xFF},
        {SC9_17,0x00,0xFF},
        {SC9_18,0x00,0xFF},
        {SC9_10,0x00,0xFF},
        {SC9_1A,0x00,0xFF},
        {SC9_1B,0x00,0xFF},
        {SC9_1C,0x00,0xFF},
        {SC9_1D,0x00,0xFF},
        {SC9_1E,0x00,0xFF},
        {SC9_1F,0x00,0xFF},
        {SC9_20,0x8C,0xFF},
        {SC9_21,0x28,0xFF},
        {SC9_22,0x8C,0xFF},
        {SC9_23,0x8C,0xFF},
        {SC9_24,0x8C,0xFF},
        {SC9_25,0x28,0xFF},
    };
    
    RegTblType code tSR_HPeakingMax[]=
    { 
        {SC7_20, 0x01,0x01},
        {SC7_21, 0xA0,0xFF},
        {SC7_22, 0x00,0xFF},
        {SC7_23, 0x0F,0xFF},
        {SC7_60, 0x20,0xFF},
        {SC7_61, 0x20,0xFF},
        {SC7_62, 0x10,0xFF},
        {SC7_63, 0x04,0xFF},
        {SC7_64, 0x05,0xFF},
        {SC7_66, 0xC6,0xFF},
        {SC7_68, 0x20,0xFF},
        {SC7_69, 0x20,0xFF},
        {SC7_6C, 0x20,0xFF},
        {SC7_6D, 0x20,0xFF},
        {SC7_6E, 0x20,0xFF},
        {SC7_6F, 0x20,0xFF},
        {SC7_70, 0x20,0xFF},
        {SC7_71, 0x20,0xFF},
        {SC7_72, 0x20,0xFF},
        {SC7_73, 0x20,0xFF},
    
    };
    
    RegTblType code tSR_HPeakingMid[]=
    {
        {SC7_20,0x01,0x01},     
        {SC7_21,0xA0,0xFF},     
        {SC7_22,0x00,0xFF},     
        {SC7_23,0x0F,0xFF},     
        {SC7_60,0x20,0xFF},     
        {SC7_61,0x20,0xFF},     
        {SC7_62,0x10,0xFF},     
        {SC7_63,0x04,0xFF},     
        {SC7_64,0x05,0xFF},     
        {SC7_66,0xE1,0xFF},     
        {SC7_68,0x20,0xFF},     
        {SC7_69,0x20,0xFF},     
        {SC7_6C,0x20,0xFF},     
        {SC7_6D,0x20,0xFF},     
        {SC7_6E,0x20,0xFF},     
        {SC7_6F,0x20,0xFF},     
        {SC7_70,0x20,0xFF},     
        {SC7_71,0x20,0xFF},     
        {SC7_72,0x20,0xFF},     
        {SC7_73,0x20,0xFF},     
    };
    
    RegTblType code tSR_HPeakingLow[]=
    {
        {SC7_20,0x00,0x01},
        {SC7_21,0xA0,0x0F},
        {SC7_22,0x00,0x0F},
        {SC7_23,0x0F,0x0F},
        {SC7_60,0x20,0x0F},
        {SC7_61,0x20,0x0F},
        {SC7_62,0x10,0x0F},
        {SC7_63,0x04,0x0F},
        {SC7_64,0x05,0x0F},
        {SC7_66,0xC6,0x0F},
        {SC7_68,0x20,0x0F},
        {SC7_69,0x20,0x0F},
        {SC7_6C,0x20,0x0F},
        {SC7_6D,0x20,0x0F},
        {SC7_6E,0x20,0x0F},
        {SC7_6F,0x20,0x0F},
        {SC7_70,0x20,0x0F},
        {SC7_71,0x20,0x0F},
        {SC7_72,0x20,0x0F},
        {SC7_73,0x20,0x0F},
    };
    
    RegTblType code tSR_VPeakingMax[]=
    { 
        {SCA_20,0x9B,0xBF},     //  V peaking have some problem
        {SCA_21,0xE0,0xFF},   
        {SCA_22,0x07,0xFF},   
        {SCA_23,0x0F,0xFF},   
        {SCA_26,0x18,0xFF},   
        {SCA_27,0x18,0xFF},   
        {SCA_28,0x00,0xFF},   
        {SCA_29,0x00,0xFF},   
        {SCA_2A,0x18,0xFF},   
        {SCA_2B,0x18,0xFF},   
        {SCA_30,0x1C,0xFF},   
        {SCA_31,0x20,0xFF},   
        {SCA_32,0x24,0xFF},   
        {SCA_33,0x28,0xFF},   
        {SCA_34,0x24,0xFF},   
        {SCA_35,0x20,0xFF},   
        {SCA_36,0x18,0xFF},   
        {SCA_40,0x01,0xFF},   
        {SCA_37,0x10,0xFF},   
        {REG_1E2E, 0x00,BIT4},
        {SC0_5A, 0x46,0xFF},   
        {REG_0C00, 0x08,0xFF},
    
    };
    
    RegTblType code tSR_VPeakingMid[]=
    {
        {SCA_20,0x9B,0xBF},  
        {SCA_21,0xE0,0xFF},  
        {SCA_22,0x03,0xFF},  
        {SCA_23,0x0B,0xFF},  
        {SCA_26,0x18,0xFF},  
        {SCA_27,0x18,0xFF},  
        {SCA_28,0x00,0xFF},  
        {SCA_29,0x00,0xFF},  
        {SCA_2A,0x18,0xFF},  
        {SCA_2B,0x18,0xFF},  
        {SCA_30,0x1C,0xFF},  
        {SCA_31,0x20,0xFF},  
        {SCA_32,0x24,0xFF},  
        {SCA_33,0x28,0xFF},  
        {SCA_34,0x24,0xFF},  
        {SCA_35,0x20,0xFF},  
        {SCA_36,0x18,0xFF},  
        {SCA_40,0x01,0xFF},  
        {SCA_37,0x10,0xFF},  
        {REG_1E2E, 0x00,BIT4},
        {SC0_5A,0x46,0xFF},  
        {REG_0C00,0x08,0xFF},
    
    };
    
    RegTblType code tSR_VPeakingLow[]=
    {
        {SCA_20,0x9B,0xBF},  
        {SCA_21,0xE0,0xFF},  
        {SCA_22,0x07,0xFF},  
        {SCA_23,0x1B,0xFF},  
        {SCA_26,0x18,0xFF},  
        {SCA_27,0x18,0xFF},  
        {SCA_28,0x00,0xFF},  
        {SCA_29,0x00,0xFF},  
        {SCA_2A,0x18,0xFF},  
        {SCA_2B,0x18,0xFF},  
        {SCA_30,0x1C,0xFF},  
        {SCA_31,0x20,0xFF},  
        {SCA_32,0x24,0xFF},  
        {SCA_33,0x28,0xFF},  
        {SCA_34,0x24,0xFF},  
        {SCA_35,0x20,0xFF},  
        {SCA_36,0x18,0xFF},  
        {SCA_40,0x01,0xFF},  
        {SCA_37,0x10,0xFF},  
        {REG_1E2E,0x00,BIT4},
        {SC0_5A,0x46,0xFF},  
        {REG_0C00,0x08,0xFF},
    
    };
    
    RegTblType code tSR_ColorMax[]=
    {
        {SC9_02,0x31,0xFF},
        {SC9_04,0x20,0xFF},
        {SC9_05,0x20,0xFF},
        {SC9_06,0x20,0xFF},
        {SC9_08,0x20,0xFF},
        {SC9_09,0x20,0xFF},
        {SC9_0A,0x20,0xFF},
        {SC9_0B,0x20,0xFF},
        {SC9_0C,0x20,0xFF},
        {SC9_0D,0x20,0xFF},
        {SC9_0E,0x00,0xFF},
        {SC9_0F,0x00,0xFF},
        {SC9_10,0x00,0xFF},
        {SC9_11,0x00,0xFF},
        {SC9_12,0x00,0xFF},
        {SC9_13,0x00,0xFF},
        {SC9_14,0x08,0xFF},
        {SC9_15,0x08,0xFF},
        {SC9_16,0x08,0xFF},
        {SC9_17,0x08,0xFF},
        {SC9_18,0x08,0xFF},
        {SC9_10,0x08,0xFF},
        {SC9_1A,0x00,0xFF},
        {SC9_1B,0x00,0xFF},
        {SC9_1C,0x00,0xFF},
        {SC9_1D,0x00,0xFF},
        {SC9_1E,0x00,0xFF},
        {SC9_1F,0x00,0xFF},
        {SC9_20,0x8C,0xFF},
        {SC9_21,0x28,0xFF},
        {SC9_22,0x8C,0xFF},
        {SC9_23,0x8C,0xFF},
        {SC9_24,0x28,0xFF},
        {SC9_25,0x8C,0xFF},
    
    };
    
    RegTblType code tSR_ColorMid[]=
    {
        {SC9_02,0x31,0xFF}, 
        {SC9_04,0x20,0xFF}, 
        {SC9_05,0x20,0xFF}, 
        {SC9_06,0x20,0xFF}, 
        {SC9_08,0x20,0xFF}, 
        {SC9_09,0x20,0xFF}, 
        {SC9_0A,0x20,0xFF}, 
        {SC9_0B,0x20,0xFF}, 
        {SC9_0C,0x20,0xFF}, 
        {SC9_0D,0x20,0xFF}, 
        {SC9_0E,0x04,0xFF}, 
        {SC9_0F,0x00,0xFF}, 
        {SC9_10,0x00,0xFF}, 
        {SC9_11,0x00,0xFF}, 
        {SC9_12,0x00,0xFF}, 
        {SC9_13,0x08,0xFF}, 
        {SC9_14,0x06,0xFF}, 
        {SC9_15,0x02,0xFF}, 
        {SC9_16,0x08,0xFF}, 
        {SC9_17,0x00,0xFF}, 
        {SC9_18,0x00,0xFF}, 
        {SC9_10,0x04,0xFF}, 
        {SC9_1A,0x40,0xFF}, 
        {SC9_1B,0x50,0xFF}, 
        {SC9_1C,0x00,0xFF}, 
        {SC9_1D,0x00,0xFF}, 
        {SC9_1E,0x00,0xFF}, 
        {SC9_1F,0x48,0xFF}, 
        {SC9_20,0x88,0xFF}, 
        {SC9_21,0x28,0xFF}, 
        {SC9_22,0x0C,0xFF}, 
        {SC9_23,0xAC,0xFF}, 
        {SC9_24,0x28,0xFF}, 
        {SC9_25,0x8C,0xFF}, 
    
    };
    
    RegTblType code tSR_ColorLow[]=
    {
        {SC9_02,0x31,0xFF},
        {SC9_04,0x20,0xFF},
        {SC9_05,0x20,0xFF},
        {SC9_06,0x20,0xFF},
        {SC9_08,0x20,0xFF},
        {SC9_09,0x20,0xFF},
        {SC9_0A,0x20,0xFF},
        {SC9_0B,0x20,0xFF},
        {SC9_0C,0x20,0xFF},
        {SC9_0D,0x20,0xFF},
        {SC9_0E,0x00,0xFF},
        {SC9_0F,0x00,0xFF},
        {SC9_10,0x00,0xFF},
        {SC9_11,0x00,0xFF},
        {SC9_12,0x00,0xFF},
        {SC9_13,0x00,0xFF},
        {SC9_14,0x04,0xFF},
        {SC9_15,0x04,0xFF},
        {SC9_16,0x04,0xFF},
        {SC9_17,0x04,0xFF},
        {SC9_18,0x04,0xFF},
        {SC9_10,0x04,0xFF},
        {SC9_1A,0x00,0xFF},
        {SC9_1B,0x00,0xFF},
        {SC9_1C,0x00,0xFF},
        {SC9_1D,0x00,0xFF},
        {SC9_1E,0x00,0xFF},
        {SC9_1F,0x00,0xFF},
        {SC9_20,0x8C,0xFF},
        {SC9_21,0x28,0xFF},
        {SC9_22,0x8C,0xFF},
        {SC9_23,0x8C,0xFF},
        {SC9_24,0x28,0xFF},
        {SC9_25,0x8C,0xFF},
    };
#endif


#if ENABLE_SUPERRESOLUTION
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
/*

#define WAIT_V_OUTPUT_BLANKING_START()   { if(!SyncLossState()&&PanelOnFlag){SetTimOutConter(30);while(((msReadByte(SC0_E0)&BIT0)==0)&&bTimeOutCounterFlag);\
                                        SetTimOutConter(30);while(((msReadByte(SC0_E0)&BIT0)!=0)&&bTimeOutCounterFlag);}}//20130227 modify for DC OFF issue
*/
void Osd_SubWindow3(WORD xPos, WORD yPos,WORD width, WORD height)
{
    xPos=xPos;
    yPos=yPos;

    width=width;
    height=height;

    msWriteByteMask(SC3_71, 0x00    ,BIT2); // select sub
    msWriteByte(SC3_70, 0x00);              // MWE 3X3 disable.

    #if DEBUG_MSG
       //printMsg("Osd_SubWindow3");
    #endif
    
    msWriteByteMask(SC3_71, 0x00    ,BIT0); // MWE offset disable.
    msWriteByteMask(SC3_3B, 0x00    ,BIT0); // peaking dis.
    msWriteByteMask(SC3_B6, 0x00    ,BIT6); // curve dis

    msWriteByte(SC3_10, 0x00);              // peaking dis.
    msWrite2Byte(SC3_1A, 0x0436);
    //msWrite2Byte(SC3_1F, 0x01);

    msWriteByte(SC3_47, 0xFF);              // boarder  Color.
    WAIT_V_OUTPUT_BLANKING_START();			//121213 Modify
    msWrite2Byte(SC3_10, 0x0011);           // boarder
    msWrite2Byte(SC3_12, 0x0000);           // boarder

}

Bool AdjustSuperResolution(void)
{
    XDATA BYTE i=0;
   
    Osd_SubWindow3(2,0,0x3BB,0x02);

#if DEBUG_MSG
    //printMsg("**AdjustSuperResolution**");
#endif

    if (UserPrefECOMode==ECO_Standard && UserPrefColorTemp==CTEMP_Warm1)
    {
        XDATA BYTE index;
        XDATA BYTE *ucTable; 
         if (USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_HIGH)
        {
            ucTable = t_demoMWEDLC_VideoSportsLevel1_Table;
            #if DEBUG_MSG
               // printMsg("MWEDLC_High_Table..........");
            #endif
        }
        else if (USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_MIDDLE)
        {
            ucTable = t_demoMWEDLC_VideoSportsLevel2_Table;
            #if DEBUG_MSG
                //printMsg("MWEDLC_High_Table..........");            
            #endif
        }
        else
        {
            ucTable = t_demoMWEDLC_VideoSportsLevel3_Table;
            #if DEBUG_MSG
               // printMsg("MWEDLC_Level3_Table........");
            #endif
        }
        for(index=0;index<16;index++)
        {
            msWriteByte((SC8_AE+index), ucTable[index]);
        }                
    }
    
   // if ((USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_OFF) || USER_PREF_INPUT_COLOR_FORMAT == INPUT_COLOR_YPBPR || (PRESET_MODE_SUPER_RES_CHECK_FLAG==0))
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
        msWriteByteMask(SC7_B8,0,BIT7);	//120509 Modify
        for(i=0;i<sizeof(tSR_OffCtrl)/sizeof(RegTblType);i++)
            msWriteByteMask(tSR_OffCtrl[i].wReg,tSR_OffCtrl[i].ucValue,tSR_OffCtrl[i].ucMask);

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
        #if DEBUG_MSG
           // printMsg("SUPER_RESOLUTION_OFF_!!");
        #endif
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
            #if DEBUG_MSG
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
            #if DEBUG_MSG
                    //printMsg("SUPER_RESOLUTION_MIDDLE_!!");
            #endif
        }
        else if (USER_PREF_SUPER_RESOLUTION==SUPER_RESOLUTION_HIGH)//(SuperResStep==1)
        {
            for(i=0;i<sizeof(tSR_HPeakingMax)/sizeof(RegTblType);i++)
                msWriteByteMask(tSR_HPeakingMax[i].wReg,tSR_HPeakingMax[i].ucValue,tSR_HPeakingMax[i].ucMask);
            for(i=0;i<sizeof(tSR_VPeakingMax)/sizeof(RegTblType);i++)
                msWriteByteMask(tSR_VPeakingMax[i].wReg,tSR_VPeakingMax[i].ucValue,tSR_VPeakingMax[i].ucMask);
            for(i=0;i<sizeof(tSR_ColorMax)/sizeof(RegTblType);i++)
                msWriteByteMask(tSR_ColorMax[i].wReg,tSR_ColorMax[i].ucValue,tSR_ColorMax[i].ucMask);
                #if DEBUG_MSG
                    // printMsg("SUPER_RESOLUTION_HIGH_!!");
                #endif
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
            //msAdjustSubBrightness( SUB_WINDOW, 0xFF, 0xFF, 0xFF );
            //msWriteByte( SC8_68, 0xFF );
            //msWriteByte( SC8_6A, 0xFF );
            //msWriteByte( SC8_6C, 0xFF );
            //msWriteByte( SC8_80, 0x00 );
            CSC_SUB_ENABLE(0);  //120204 Modify
            msAccSetup(DEMO_Hsize+HSTART_OFFSET, DISPLAY_WIDTH+HSTART_OFFSET, 0,  PanelHeight);	//121115 Modify
            msAccOnOff(1);
        }
    return TRUE;
}

#endif

