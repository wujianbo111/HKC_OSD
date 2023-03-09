// ****************************************************************************
// IT7230_TouchKey.c
// Create date  :   20120104
// Modifications:   20120402
// Version      :   IT7230_0006
// Definitions  :
// Copyright (c) 2009 ITE Tech. Inc. All Rights Reserved.
// ****************************************************************************

//#include "ITE_types.h"
#include "IT7230_TouchKey.h"
#include "IT7230_SettingTable.c"
#include "keypaddef.h"

static BYTE xdata current_page = 0;
static BYTE xdata ITE7230InitState = 0;
static WORD xdata wCAPS_PDR_BACKUP;
static WORD xdata wCAPS_RTR_BACKUP;
static WORD xdata wCAPS_CTR_BACKUP;
static WORD xdata wCAPS_S2OHCR_CHECK;
static WORD xdata wCAPS_PCR_CHECK;
static WORD xdata wSTAGE_NUM;

#if ENABLE_LOW_CONTACT
static BYTE xdata bTKLowContactFlag = TRUE;
#endif


/////////////////////////////////////////////////////////////////////////////
//----Return It7230 ITE7230InitState                                      ---//
/////////////////////////////////////////////////////////////////////////////
BYTE IT7230_Init_Status(void)
{
	return ITE7230InitState;
}
/////////////////////////////////////////////////////////////////////////////
static void IT7230_CheckPage(BYTE page)
{
	BYTE i;
	if ( page != current_page)
	{
		for (i = 0; i < Retry; i++)
		{
			if( IT7230_I2C_WriteWord(CAPS_PSR, page) )
			{
				current_page = page;
				break;
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
//----Read IT7230 registers , IT7230_CheckPage() & retry 3 Timer-----------//
/////////////////////////////////////////////////////////////////////////////
WORD IT7230_CapS_Read_Reg(BYTE page, BYTE addr_byte)
{
	WORD data_word = 0;
	BYTE i;
	IT7230_CheckPage(page);
	for (i = 0; i < Retry; i++)
	{
		if(IT7230_I2C_ReadWord(addr_byte, &data_word))
		{
			break;
		}
	}
	return data_word;
}
/////////////////////////////////////////////////////////////////////////////
//----Write IT7230 registers ,IT7230_CheckPage() & retry 3 Timer-----------//
/////////////////////////////////////////////////////////////////////////////
void IT7230_CapS_Write_Reg(BYTE page, BYTE addr_byte, WORD data_word)
{
	BYTE i = 0x00;
	IT7230_CheckPage(page);
	for (i = 0; i < Retry; i++)
	{
		if(IT7230_I2C_WriteWord(addr_byte, data_word))
		{
			break;
		}
	}
	//When the "reset" bit of PCR register is 1, current_page is set to 0.
	if ( (CAPS_PCR == addr_byte) && (1 == page) && (data_word & 0x0001))
		current_page = 0;
}
/////////////////////////////////////////////////////////////////////////////
//----Write IT7230 Initial Table
/////////////////////////////////////////////////////////////////////////////
void IT7230_Init_CapS_Table(void)
{
	BYTE i = 0x00;
	while (i < (sizeof(asInitCapSReg) / sizeof(sInitCapSReg)))
	{
		IT7230_CapS_Write_Reg(asInitCapSReg[i].page, asInitCapSReg[i].reg, asInitCapSReg[i].value);
		//*********************************************************************//
		//---Backup these Registers for "IT7230_Check_ESD()",It is necessary---//
		switch (asInitCapSReg[i].reg)
		{
			case CAPS_RTR:
				wCAPS_RTR_BACKUP = asInitCapSReg[i].value ;
				break;
			case CAPS_CTR:
				wCAPS_CTR_BACKUP = asInitCapSReg[i].value ;
				break;
			case CAPS_PDR:
				wCAPS_PDR_BACKUP = asInitCapSReg[i].value ;
				break;
			case CAPS_PCR:
				wCAPS_PCR_CHECK = asInitCapSReg[i].value ;
				break;
			default:
				break;
		}
		//********************************************************************//
		i++;
		if (1 == i)
		{
			ForceDelay1ms(2);//Delay 1ms.
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
//----Restort Reg after the "IT7230_Init()" function ,It is necessary---//
/////////////////////////////////////////////////////////////////////////////
void IT7230_Restort_Reg(void)
{
	#if ENABLE_LOW_CONTACT
	BYTE i;
	WORD wCAPS_SXOHCR, wCAPS_SXCHAIER;
	#endif
	//Restore RTR/CTR/CFER
	if(IT7230_Init_Status() == PRE_RESTORT)
	{
		IT7230_CapS_Write_Reg(PAGE_1, CAPS_PDR, wCAPS_PDR_BACKUP);
		IT7230_CapS_Write_Reg(PAGE_1, CAPS_RTR, wCAPS_RTR_BACKUP);
		IT7230_CapS_Write_Reg(PAGE_1, CAPS_CTR, wCAPS_CTR_BACKUP);
		IT7230_CapS_Write_Reg(PAGE_1, CAPS_CFER, 0xC000);
		IT7230_CapS_Read_Reg(PAGE_0, CAPS_SIR);
		//---To detect AC ON contact,  ---//
		#if ENABLE_LOW_CONTACT
		if( bTKLowContactFlag )
		{
			for( i = 0 ; i < wSTAGE_NUM ; i++)
			{
				wCAPS_SXOHCR = IT7230_CapS_Read_Reg(PAGE_0, CAPS_S0OHCR + (i * 0x10));
				IT7230_CapS_Write_Reg(PAGE_0, CAPS_S0OLUR + (i * 0x10), wCAPS_SXOHCR);
			}
			wCAPS_SXCHAIER = IT7230_CapS_Read_Reg(PAGE_0, CAPS_SXCHAIER);
			IT7230_CapS_Write_Reg(PAGE_0, CAPS_SXCLAIER, wCAPS_SXCHAIER);
		}
		#endif
		//----------------------------------------------------------//
		wCAPS_S2OHCR_CHECK = (IT7230_CapS_Read_Reg(PAGE_0, CAPS_S2HTR));
		ITE7230InitState   = FINISH_RESTORT;
	}
}

/* If the return value is non-zero, this value represent the time interval
 * prior to calling IT7230_Restort_Reg. The system program must call
 * the function IT7230_Restort_Reg after passing through the time by the
 * return value(ms) of this function.
 * If the return value is zero, that means this function has an error and
 * the system program doesn't have to call the function IT7230_Restort_Reg.
 *
 * An Example for calling this function.
 *
 * .....
 * tmrRestoreTouchKeyStatus = IT7230_Init();
 * if(tmrRestoreTouchKeyStatus) {
 * 	Set flagDoRestoreTouchKeyStatus.
 * 	Set a timer with tmrRestoreTouchKeyStatus.
 * } else {
 * 	Clear flagDoRestoreTouchKeyStatus.
 * }
 * // to do system functions
 * ....
 * if( flagDoRestoreTouchKeyStatus && (!tmrRestoreTouchKeyStatus))
 * 	IT7230_Restort_Reg();
 * ....
*/
BYTE IT7230_Init()
{
	WORD wDecimationRate = 0;
	ITE7230InitState = NON_INIT;
	// Initialize the global variables.
	wSTAGE_NUM          = 0;
	wCAPS_S2OHCR_CHECK  = 0;
	wCAPS_PCR_CHECK     = 0;
	wCAPS_PDR_BACKUP    = 0;
	wCAPS_RTR_BACKUP    = 0;
	wCAPS_CTR_BACKUP    = 0;

    //*********************************************************************//
	!IT7230_I2C_Device_Addr_Check())//non_Ack
	
	#if DEBUG_SCANKEY
            printMsg("IT7230_Init No_Key");
 	   
		if
		
		****************************************************************//
    
    IT7230_Init_CapS_Table();
	Check Init_CapS_Table are	if( (IT7230_CapS_Read_Reg(PAGE_1, CAPS_PDR) != wCAPS_PDR_BACKUP )||
	    (IT7230_CapS_Read_Reg(PAGE_1, CAPS_CTR) != wCAPS_CTR_BACKUP )||
		(IT7230_CapS_Read_Reg(PAGE_1, CAPS_RTR) != wCAPS_RTR_BACKUP )|| 
	    	(IT7230_CapS_Read_Reg(PAGE_1, CAPS_PCR) != wCAPS_PCR_CHECK	)) 
	         
	        if DEBUG_SCANKEY
            printMsg("IT7230_Init WTbleFail");
 	       #endif
		urn 0;
		
		
	cimationRate = (( wCAPS_PCR_CHECK >> 8 )& 0x0F);
 
    //*************************************** * *****************************//
	IT7230_CapS_Write_Reg(PAGE_1, CAPS_RTR, 0x0000);
	IT7230_CapS_Write_Reg(PAGE_1, CAPS_CTR, 0x0000);
	IT7230_CapS_Write_Reg(PAGE_1, CAPS_PDR, 0x1FFF);
	230_CapS_Write_Reg(PAGE_1, CAPS_CFER,0x4000);
	
    ITE7230InitState = PRE_RESTORT; 
	 DEBUG_SCANKEY
        #endif
	***************************************************************//
	-Waiting for Calibration Tune CDC,It is necessary.
	
	 wDecimationRate == 0x00 )	{
		return (12);//(550); // 120430 modified, 12 means 12x50ms = 600ms
	}
	else if( wDecimationRate == 0x04 )
	{
		return (8);//(350); // 120430 modified, 8 means 8x50ms = 400ms
	}
	else
	{
		return (6);//(250); // 120430 modified, 6 means 6x50ms = 300ms
	}
    
    
}
/////////////////////////////////////////////////////////////////////////////////
//----Please check the function about the 1~2 seconds----//
/////////////////////////////////////////////////////////////////////////////

/* If the return value is non-zero, this value represent the time interval
 * prior to calling IT7230_Restort_Reg(). The system program must call the
 * function IT7230_Restort_Reg() after passing through the time by the
 * return value(ms) of this function.
 * If the return value is zero, that means the function IT7230_Init hasn't
 * been called or it returns zero, so the system program doesn't have to call
 * the function IT7230_Restort_Reg.
 * The system program designer can see the previous example to learn how to
 * use it.
 *
*/ 
BYTE IT7230_Check_ESD(void)
{

    #if MOBILE_INTERFERENCE
	D    Current_temp;
    static  BYTE uErrorCount = 0;
    BOOL    uErrorFlag = FALSE;
	#endif
	
	    
	turn IT7230_Init();  
	}   

  f( IT7230_Init_Status() == FINISH_RESTORT )
	    if ( wCAPS_S2OHCR_CHECK != IT7230_CapS_Read_Reg(PAGE_0, CAPS_S2HTR)) 
		{
		turn IT7230_Init();
	
		}
	}
	if( (IT7230_Init_Status() == FINISH_RESTORT) || (IT7230_Init_Status() == PRE_RESTORT))
	
	

     {
	    for( i = 0 ; i < wSTAGE_NUM ; i++ )
	
		nt_temp = IT7230_CapS_Read_Reg(PAGE_0, CAPS_S0CDC_CMP+0x10*i);
            if( (Current_temp == 0x0000 )||( Current_temp== 0xFFFF ))
			{    
			ount++;   
                 uErrorFlag = TRUE;
                break ;
				
				

        if(uErrorFlag)
		    if( uErrorCount >= 2 )
		    {
			    uErrorCount = 0;
			
				return IT7230_Init();
				
			
		{
		   uErrorCount = 0; 
		}
			
		
	#endif

	/////////////////////////////////////////////////////////////////////////
//----Setting the "CAPS_GPIOOR" Reg to Change LED status ----                                                             //
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//----Get the Touch Key Status,offer polling and interrupt mode---// 
/////////////////////////////////////////////////////////////////////////////
BYTE IT7230_GetKeyStatus(void)
{	
    WORD wTKeyStatus = 0 ;
   BYTE keypad = 0xff;
	if( IT7230_Init_Status() == FINISH_RESTORT )
	{
	    #ifdef ENABLE_IT7230_INTPIN
	    if( !INTPin )//interrupt mode
		#endif
		{
		    wTKeyStatus = IT7230_CapS_Read_Reg(PAGE_0, CAPS_SXCHSR)&TPREG_KEYPADMASK;
		
			if(wTKeyStatus)
			    if( wTKeyStatus == TPREG_POWER )
			    {
				    keypad &= ~KEY_POWER;
				}
					 if( wTKeyStatus == TPREG_MENU )
				{
				    keypad &= ~KEY_MENU;
				}
					 if( wTKeyStatus == TPREG_MINUS )
				{
				    keypad &= ~KEY_MINUS;
				}
					 if( wTKeyStatus == TPREG_PLUS )
				{
				    keypad &= ~KEY_PLUS;
				}
					 if( wTKeyStatus == TPREG_AUTO )
				{
				    keypad &= ~KEY_EXIT;
				}
					ction==FEnter_POWER_MENU)		
				else if(( wTKeyStatus == TPREG_FACTORY ) && !PowerOnFlag )
  		           {
				    keypad &= ~KEY_FACTORY;
				}
					unction==FEnter_POWER_EXIT)		
				else if(( wTKeyStatus == TPREG_FACTORY ) && !PowerOnFlag )
  		           {
		    keypad &= ~KEY_FACTORY;
				}				
					
lse }if(( wTKeyStatus == TPREG_OSDLOCK ) && !PowerOnFlag )
  		          {
				    keypad &= ~KEY_LOCK;
				}
					
				{
				    keypad= 0xff;
				}                            
					 
				O
			else // no key pressed
			            {
			    if(IT7230_GetLowContactFlag())
			    {
				    if(!TouchKeyLowContactDetectCntr)
				    {
					    IT7230_SetLowContactFlag(FALSE); // close low contact detect
					    IT7230_SetLowContactCalibration(); // disable low contact register
						
						sableLowContact");
 					       #endif
						        }
						            else
					{
					    if(IT7230_GetLowContactStatus())
					    {
						    if(!TouchKeyLowContactDelay) // 120417 coding addition
						    {
							    TouchKeyLowContactDelay = IT7230_SetLowContactCalibration();
							
								tCal:%d", TouchKeyLowContactDelay);
 							       #endif
								                }
								                }
							
						
					
				  
			
			    }
		
	eturn keypad;
	//////////////////////////////////////////////////////////////////////////
#if ENABLE_LOW_CONTACT
void IT7230_SetLowContactFlag(BOOL LowContactFlag)
{
    bTKLowContactFlag = LowContactFlag;
}
	/////////////////////////////////////////////////////////////////////////
BOOL IT7230_GetLowContactFlag(void)
{
    return bTKLowContactFlag;
}
	/////////////////////////////////////////////////////////////////////////
WORD IT7230_GetLowContactStatus(void)
{
    WORD wLowContactStatus = 0;

	if( bTKLowContactFlag )
	    if( IT7230_Init_Status() == FINISH_RESTORT )
	    {
		    wLowContactStatus = IT7230_CapS_Read_Reg(PAGE_0, CAPS_SXCLSR);
		}
			
		
	return wLowContactStatus ;
	/////////////////////////////////////////////////////////////////////////
BYTE IT7230_SetLowContactCalibration(void)  
{

    WORD wDecimationRate;
	
	for( i=0; i< wSTAGE_NUM ; i++)
	    IT 7 230_ CapS_Write_Reg(PAGE_0, CAPS_S0OLUR+(i*0x10), 0x7000);
	}
		    
	IT7230_CapS_Write_Reg(PAGE_0, CAPS_SXCLAIER, 0x0000);//DISENABLE Low Contact
	if( !bTKLowContactFlag )
	    return 0;
	}
		imationRate = (( wCAPS_PCR_CHECK >> 8 )& 0x0F);
	
	//***************************************** ****************************//
	IT7230_CapS_Write_Reg(PAGE_1, CAPS_RTR, 0x0000);
	IT7230_CapS_Write_Reg(PAGE_1, CAPS_CTR, 0x0000);
	IT7230_CapS_Write_Reg(PAGE_1, CAPS_PDR, 0x1FFF);
	IT7230_CapS_Write_Reg(PAGE_1, CAPS_CFER,0x4000);
	
	 
	ITE7230InitState = PRE_RESTORT;
	
	//---Waiting for Calibration Tune CDC,It is necessary.
	
            return (12);//(550); // 120430 modified, 12 means 12x50ms = 600ms
	}
		ecimationRate == 0x04 )
	{
		return (8);//(350); // 120430 modified, 8 means 8x50ms = 400ms
	}
	else
	{
		return (6);//(250); // 120430 modified, 6 means 6x50ms = 300ms
	}

	return 0;
}#endif
/////////////////////////////////////////////////////////////////////////////
