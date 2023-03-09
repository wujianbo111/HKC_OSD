#include "types.h"   // nick check 130109

#ifndef __BD_7343__
#define __BD_7343__

#define MCU_SPEED_INDEX         IDX_MCU_CLK_MPLL_DIV // 172M
#define SPI_SPEED_INDEX         IDX_SPI_CLK_43MHZ
#define SPI_MODE                	  SPI_MODE_FR
#define HPD_INVERSE             0 // If it has BJT circuit on board, the HPD_INVERSE should be set to TRUE

#define SPI_SSC_EN              (SPI_SPEED_INDEX==IDX_SPI_CLK_SSC)// use memory clock source, need to enable memclk SSC, and divide it to the one closest & lower to SPI_SPEED_INDEX
#define SPI_SSC_SOURCE          0 // 0:mempll, 1:lpll (Current code flow for mempll only)
#define SPI_SSC_DIVIDER         4 // Target Freq => (MEMORY_CLOCK_MHZ*(100+PERCENTAGE)/(SPI_SSC_DIVIDER+1))

enum 
{
    UART0_GPIO40_41   = 0x00,
    UART0_GPIO34_35   = BIT1,
    UART0_GPIO02_00   = BIT2,
    UART1_GPIO20_21   = BIT4,
    UART1_GPIO32_33   = 0x00,
};


#define DFT_MUX_Uart0           UART0_GPIO40_41 // default mux uart 0 - VGA
#define DFT_MUX_Uart1           UART1_GPIO32_33

// Mapping to InputPortType
#define Input_DVI_C1            Input_Digital
#define Input_DVI_C2            Input_Nothing
#define Input_DVI_C3            Input_Nothing
#define Input_HDMI_C1           Input_Nothing//Input_Nothing
#define Input_HDMI_C2           Input_Nothing//Input_HDMI//
#define Input_HDMI_C3           Input_Nothing
#define Input_Displayport_C2    Input_Nothing
#define Input_Displayport_C3    Input_Nothing

// For Preprocessing
#define CInput_Nothing          0
#define CInput_Digital          1
#define CInput_Digital2         2
#define CInput_Digital3         3

#define CInput_DVI_C1           CInput_Digital//CInput_Nothing
#define CInput_DVI_C2           CInput_Nothing
#define CInput_DVI_C3           CInput_Nothing
#define CInput_HDMI_C1          CInput_Nothing//CInput_Digital2
#define CInput_HDMI_C2          CInput_Nothing//CInput_Nothing
#define CInput_HDMI_C3          CInput_Nothing
#define CInput_Displayport_C2   CInput_Nothing
#define CInput_Displayport_C3   CInput_Nothing

#define DVI_PORT                ( ((CInput_DVI_C1!=CInput_Nothing)?TMDS_PORT_A:TMDS_PORT_UNUSE) | ((CInput_DVI_C2!=CInput_Nothing)?TMDS_PORT_B:TMDS_PORT_UNUSE) | ((CInput_DVI_C3!=CInput_Nothing)?TMDS_PORT_C:TMDS_PORT_UNUSE) )
#define DVI_HPD_PORT            ( ((CInput_DVI_C1!=CInput_Nothing)?TMDS_PORT_A:TMDS_PORT_UNUSE) | ((CInput_DVI_C2!=CInput_Nothing)?TMDS_PORT_B:TMDS_PORT_UNUSE) | ((CInput_DVI_C3!=CInput_Nothing)?TMDS_PORT_C:TMDS_PORT_UNUSE) )
#define DVI_DDC_PORT            ( ((CInput_DVI_C1!=CInput_Nothing)?TMDS_PORT_A:TMDS_PORT_UNUSE) | ((CInput_DVI_C2!=CInput_Nothing)?TMDS_PORT_B:TMDS_PORT_UNUSE) | ((CInput_DVI_C3!=CInput_Nothing)?TMDS_PORT_C:TMDS_PORT_UNUSE) )
#define DVI_MASTER_PORT         ( ((CInput_DVI_C1!=CInput_Nothing)?TMDS_PORT_A:TMDS_PORT_UNUSE) | ((CInput_DVI_C2!=CInput_Nothing)?TMDS_PORT_B:TMDS_PORT_UNUSE) | ((CInput_DVI_C3!=CInput_Nothing)?TMDS_PORT_C:TMDS_PORT_UNUSE) )

//set to 0 if not DVI dual port enable
#define DVI_SLAVE_PORT          TMDS_PORT_UNUSE

#define HDMI_PORT               ( ((CInput_HDMI_C1!=CInput_Nothing)?TMDS_PORT_A:TMDS_PORT_UNUSE) | ((CInput_HDMI_C2!=CInput_Nothing)?TMDS_PORT_B:TMDS_PORT_UNUSE) | ((CInput_HDMI_C3!=CInput_Nothing)?TMDS_PORT_C:TMDS_PORT_UNUSE) )
#define HDMI_HPD_PORT           ( ((CInput_HDMI_C1!=CInput_Nothing)?TMDS_PORT_A:TMDS_PORT_UNUSE) | ((CInput_HDMI_C2!=CInput_Nothing)?TMDS_PORT_B:TMDS_PORT_UNUSE) | ((CInput_HDMI_C3!=CInput_Nothing)?TMDS_PORT_C:TMDS_PORT_UNUSE) )
#define HDMI_DDC_PORT           ( ((CInput_HDMI_C1!=CInput_Nothing)?TMDS_PORT_A:TMDS_PORT_UNUSE) | ((CInput_HDMI_C2!=CInput_Nothing)?TMDS_PORT_B:TMDS_PORT_UNUSE) | ((CInput_HDMI_C3!=CInput_Nothing)?TMDS_PORT_C:TMDS_PORT_UNUSE) )

// DDC port used
#define DDC_Port_D0             ((CInput_DVI_C1!=CInput_Nothing) || (CInput_HDMI_C1!=CInput_Nothing))
#define DDC_Port_D1             ((CInput_DVI_C2!=CInput_Nothing) || (CInput_HDMI_C2!=CInput_Nothing))
#define DDC_Port_D2             ((CInput_DVI_C3!=CInput_Nothing) || (CInput_HDMI_C3!=CInput_Nothing))

#define SERIAL_BAUD_RATE        9600ul

#define BrightnessPWM           _PWM7_ // Driving Non-LED BL Module
#define Init_BrightnessPWM()    { MEM_MSWRITE_BYTE_MASK(REG_020A,BIT7,BIT7);MEM_MSWRITE_BYTE_MASK(REG_0281,BIT3,BIT3);}

#if AudioFunc
#define VolumePWM               _PWM1_ // Not Finishhed Yet in CHIP_TSUMC
#define Init_VolumePWM()        (MEM_MSWRITE_BYTE_MASK(REG_0208,BIT1,BIT1), MEM_MSWRITE_BYTE_MASK(REG_0280,BIT1,BIT1))
#endif

#define PowerKey        			(_bit4_(MEM_MSREAD_BYTE(_REG_GPIOSAR_IN)))
#define Init_PowerKey() 			(MEM_MSWRITE_BIT(_REG_GPIOSAR_OEZ, 1, BIT0))
#define PM_POWERKEY_WAKEUP      GPIO20_INT

#define NonUsepin 

#if 0//EarphoneDet_Enable
#define HarphoneDet_Pin                 (_bit1_(MEM_MSREAD_BYTE(_REG_GPIOL_IN_H)))
#define Init_HarphoneDet_Pin()        MEM_MSWRITE_BIT(_REG_GPIOL_OEZ_H, 1, BIT1),  MEM_MSWRITE_BIT(_REG_GPIOL_OUT_H, 0, BIT1),MEM_MSWRITE_BIT(_REG_GPIOL_SEL_H, 0, BIT1)
#endif

//================================================================================================================
//================================================================================================================
// 1.Write protection:
#define hwDDC_WP_Pin            //Pull to Ground in Schematic
#define hwEEPROM_WP             //GPIO03
#define hwFlash_WP_Pin          //GPIO10

// ddc eeprom wp be pulled high to 5V, set to input for output high level
//130708 petit
#define hw_SetDDC_WP()                  (MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, 1, BIT6),MEM_MSWRITE_BIT(_REG_GPIO3_OUT, 1, BIT6))//, DDCWPActiveFlag=1)
#define hw_ClrDDC_WP()                  (MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, 0, BIT6),MEM_MSWRITE_BIT(_REG_GPIO3_OUT, 0, BIT6))//, DDCWPActiveFlag=0)
#define Init_hwDDC_WP_Pin()         (MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, 1, BIT6))//, DDCWPActiveFlag=1)

#define Set_EEPROM_WP()            //    MEM_MSWRITE_BIT(_REG_GPIO3_OUT, 1, BIT6)
#define Clr_EEPROM_WP()          // (MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, 0, BIT6),MEM_MSWRITE_BIT(_REG_GPIO3_OUT, 0, BIT6))
#define Init_hwEEPROM_WP()        // MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, 1, BIT6)

#define hw_SetFlashWP()             (MEM_MSWRITE_BIT(_REG_GPIO1_OEZ, 0, BIT0), MEM_MSWRITE_BIT(_REG_GPIO1_OUT, 0, BIT0))
#define hw_ClrFlashWP()                 (MEM_MSWRITE_BIT(_REG_GPIO1_OEZ, 0, BIT0), MEM_MSWRITE_BIT(_REG_GPIO1_OUT, 1, BIT0))
#define Init_hwFlash_WP_Pin()       (MEM_MSWRITE_BIT(_REG_GPIO1_OEZ, 0, BIT0), MEM_MSWRITE_BIT(_REG_GPIO1_OUT, 0, BIT0))

//================================================================================================================
//================================================================================================================
// 2.Backlight and panelon:
#define hwBlacklit_Pin          //GPIOL10
#define hwPanel_Pin             //GPIOL8

#define hw_SetBlacklit()        (MEM_MSWRITE_BIT(_REG_GPIOL_OUT_H, 0, BIT3), BackLightActiveFlag=1)
#define hw_ClrBlacklit()        (MEM_MSWRITE_BIT(_REG_GPIOL_OUT_H, 1, BIT3), BackLightActiveFlag=0)
#define Init_hwBlacklit_Pin()   (MEM_MSWRITE_BIT(_REG_GPIOL_OEZ_H, 0, BIT3), MEM_MSWRITE_BIT(_REG_GPIOL_SEL_H, 0, BIT3)) // output enable

#define hw_SetPanel()           MEM_MSWRITE_BIT(_REG_GPIOL_OUT_H, 1, BIT0)
#define hw_ClrPanel()           MEM_MSWRITE_BIT(_REG_GPIOL_OUT_H, 0, BIT0)
#define Init_hwPanel_Pin()      (MEM_MSWRITE_BIT(_REG_GPIOL_OEZ_H, 0, BIT0), MEM_MSWRITE_BIT(_REG_GPIOL_SEL_H, 0, BIT0)) // output enable

//================================================================================================================
//================================================================================================================
// 4.Detect Cable
#define CABLE_DETECT_VGA_USE_SAR        0
#define CABLE_DETECT_DVI_USE_SAR      0
#define CABLE_DETECT_HDMI_USE_SAR   0

#if CABLE_DETECT_VGA_USE_SAR
#define hwDSUBCable_Pin                 (KEYPAD_SAR3 > 128)
#define Init_hwDSUBCable_Pin()  
#define CABLE_DET_VGA_SAR               SAR3_EN // 2.8V
#define Init_hwDVICable_Pin()
#else
#define hwDSUBCable_Pin                     (_bit7_(MEM_MSREAD_BYTE(_REG_GPIOSAR_IN)))//(_bit7_(MEM_MSREAD_BYTE(_REG_GPIOSAR_IN)))  //SAR3
#define Init_hwDSUBCable_Pin()          (MEM_MSWRITE_BIT(_REG_GPIOSAR_OEZ, 1, BIT3))//(MEM_MSWRITE_BIT(_REG_GPIOSAR_OEZ, 1, BIT3))
#define CABLE_DET_VGA_SAR               0
#endif

#if CABLE_DETECT_DVI_USE_SAR
#define hwDVICable_Pin      			1
#define Init_hwDVICable_Pin()
#define CABLE_DET_DVI_SAR    			0//SAR6_EN
#else
#define hwDVICable_Pin 				(_bit5_(MEM_MSREAD_BYTE(_REG_GPIO5_IN)))//	0//(_bit0_(MEM_MSREAD_BYTE(_REG_GPIO3_IN)))
#define Init_hwDVICable_Pin() 		(MEM_MSWRITE_BIT(_REG_GPIO5_OEZ, 1, BIT5))	//(MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, 1, BIT0))
#define CABLE_DET_DVI_SAR    			0
#endif

#if ENABLE_HDMI
#define hwHDMICable_Pin   			(KEYPAD_SAR5)//(_bit0_(MEM_MSREAD_BYTE(_REG_GPIO3_IN)))
#define Init_hwHDMICable_Pin()  		(MEM_MSWRITE_BIT(REG_3A68,1,BIT5))//(MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, 1, BIT0))
#define CABLE_DET_HDMI_SAR    		SAR5_EN
#else
#define CABLE_DETECT_HDMI_USE_SAR    0
#define CABLE_DET_HDMI_SAR    0
#endif

#if (CInput_HDMI_C1!=CInput_Nothing)||(CInput_DVI_C1!=CInput_Nothing)
#define hwDVI0Cable_Pin                 0//(KEYPAD_SAR6)
#define Init_hwDVI0Cable_Pin()          //(MEM_MSWRITE_BIT(REG_3A68,1,BIT6)) // Enable SAR ch
#define CABLE_DET_DVI0_SAR              0//SAR6_EN
#else
#define hwDVI0Cable_Pin                 (_bit5_(MEM_MSREAD_BYTE(_REG_GPIO5_IN)))
#define Init_hwDVI0Cable_Pin()	  (MEM_MSWRITE_BIT(_REG_GPIO5_OEZ, 1, BIT5))
#define CABLE_DET_DVI0_SAR          0
#endif

#if (CInput_HDMI_C2!=CInput_Nothing)||(CInput_DVI_C2!=CInput_Nothing)
#define hwDVI1Cable_Pin                 0//(KEYPAD_SAR5)
#define Init_hwDVI1Cable_Pin()          //(MEM_MSWRITE_BIT(REG_3A68,1,BIT5)) // Enable SAR ch
#define CABLE_DET_DVI1_SAR              0//SAR5_EN
#else
#define hwDVI1Cable_Pin                 0
#define Init_hwDVI1Cable_Pin()
#define CABLE_DET_DVI1_SAR              0
#endif

#if (CInput_HDMI_C3!=CInput_Nothing)||(CInput_DVI_C3!=CInput_Nothing)
#define hwDVI2Cable_Pin                 0//(KEYPAD_SAR7)
#define Init_hwDVI2Cable_Pin()          //(MEM_MSWRITE_BIT(REG_3A68,1,BIT7)) // Enable SAR ch
#define CABLE_DET_DVI2_SAR              0//SAR7_EN
#else
#define hwDVI2Cable_Pin                 0
#define Init_hwDVI2Cable_Pin()
#define CABLE_DET_DVI2_SAR              0
#endif

#define CABLE_DET_SAR_EN              0 // (CABLE_DET_VGA_SAR)
#define CABLE_DET_SAR                   0
#define CABLE_DET_SAR2_EN             0//  (CABLE_DET_DVI0_SAR|CABLE_DET_DVI1_SAR|CABLE_DET_DVI2_SAR)



//================================================================================================================
//================================================================================================================

#define hwGreenLed_Pin                  // GPIO22
#define hwAmberLed_Pin                  // GPIO23

#define hw_SetGreenLed()                  {MEM_MSWRITE_BIT(_REG_GPIO2_OEZ,0,BIT2);MEM_MSWRITE_BIT(_REG_GPIO2_OUT,1,BIT2);}//  (MEM_MSWRITE_BIT(_REG_GPIO2_OEZ,0,BIT2),MEM_MSWRITE_BIT(_REG_GPIO2_OUT,0,BIT2))
#define hw_ClrGreenLed()                   {MEM_MSWRITE_BIT(_REG_GPIO2_OEZ,1,BIT2);MEM_MSWRITE_BIT(_REG_GPIO2_OUT,0,BIT2);}// MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, 1,BIT2)
#define Init_hwGreenLed_Pin()            MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, 1,BIT2)// output enable// output enable//  MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, 1,BIT2)// output enable

#define hw_SetAmberLed()                {MEM_MSWRITE_BIT(_REG_GPIO2_OEZ,0,BIT3);MEM_MSWRITE_BIT(_REG_GPIO2_OUT, 1, BIT3);}
#define hw_ClrAmberLed()                {MEM_MSWRITE_BIT(_REG_GPIO2_OEZ,1,BIT3);MEM_MSWRITE_BIT(_REG_GPIO2_OUT, 0, BIT3);}
#define Init_hwAmberLed_Pin()          MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, 1,BIT3)// output enable
//================================================================================================================
//================================================================================================================
// 6.Audio control:
#define hwMute_Pin                      //NO_USE_PIN       
            
#define hw_SetMute()                    ( MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, 0,BIT1),MEM_MSWRITE_BIT(_REG_GPIO0_OUT, TRUE,  BIT1))
#define hw_ClrMute()                    ( MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, 0,BIT1),MEM_MSWRITE_BIT(_REG_GPIO0_OUT, FALSE, BIT1))
#define Init_hwMute_Pin()		//MEM_MSWRITE_BIT(_REG_GPIO0_OEZ,0,BIT0)

#define Set_Audio_StandBy()    	
#define Clr_Audio_StandBy()    	
#define Init_Audio_StandBy()        			


#define hwAudio_SD_Pin()                //NO_USE_PIN
#define hw_SetAudio_SD()          		//MEM_MSWRITE_BIT(_REG_GPIO3_OUT,1,BIT1)
#define hw_ClrAudio_SD()              	//MEM_MSWRITE_BIT(_REG_GPIO3_OUT,0,BIT1)
#define Init_Audio_SD_Pin()           	//MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, 0,BIT1)

#define hwStandby_Pin()
#define hw_SetStandby()            
#define hw_ClrStandby()        
#define Init_SPIFGPIO_Pin()   			//{MEM_MSWRITE_BIT(REG_0206,BIT0,BIT0);}


//#define hwPW_Switch()
//#define hw_SetPW_Switch()        			(MEM_MSWRITE_BIT(_REG_GPIO0_OEZ,0,BIT1),MEM_MSWRITE_BIT(_REG_GPIO0_OUT,0,BIT1))
//#define hw_ClrPW_Switch()        			        (MEM_MSWRITE_BIT(_REG_GPIO0_OEZ,0,BIT1),MEM_MSWRITE_BIT(_REG_GPIO0_OUT,BIT1,BIT1))
//#define Init_hwPW_Switch()				 MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, 0,BIT1)
//================================================================================================================
//================================================================================================================
// I2C
#if USEFLASH//defined(UseVGACableReadWriteAllPortsEDID) //&&!defined(UseInternalDDCRam)

#define INIT_HWI2C_SDA_PIN()	(MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, TRUE, BIT3))
#define INIT_HWI2C_SCL_PIN()	(MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, TRUE, BIT3))

#define hw_Set_I2C_SDA_Pin		(MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, TRUE, BIT3))
#define hw_Clr_I2C_SDA_Pin		(MEM_MSWRITE_BIT(_REG_GPIO0_OUT, FALSE, BIT3), MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, FALSE, BIT3))
#define hw_I2C_SDA_HI                  (_bit3_(MEM_MSREAD_BYTE(_REG_GPIO0_IN)))
#define hw_I2C_SDA_LO                  (!hw_I2C_SDA_HI)


#define hw_Set_I2C_SCL_Pin		(MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, TRUE, BIT3))
#define hw_Clr_I2C_SCL_Pin		(MEM_MSWRITE_BIT(_REG_GPIO0_OUT, FALSE, BIT3), MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, FALSE, BIT3))
#define hw_I2C_SCL_HI		       (_bit3_(MEM_MSREAD_BYTE(_REG_GPIO0_IN)))
#define hw_I2C_SCL_LO			(!hw_I2C_SCL_HI)


#define Init_NVRAM_I2C_SDA_Pin()			{INIT_HWI2C_SDA_PIN();INIT_HW_VGAI2C_SDA_PIN();INIT_HW_DVII2C_SDA_PIN();}
#define Init_NVRAM_I2C_SCL_Pin()			{INIT_HWI2C_SCL_PIN();INIT_HW_VGAI2C_SCL_PIN();INIT_HW_DVII2C_SCL_PIN();}


#define INIT_HW_VGAI2C_SDA_PIN()    (MEM_MSWRITE_BIT(_REG_GPIO4_OEZ, TRUE, BIT1))
#define INIT_HW_VGAI2C_SCL_PIN()    (MEM_MSWRITE_BIT(_REG_GPIO4_OEZ, TRUE, BIT0))

#define Set_i2c_SDA_VGA()           (MEM_MSWRITE_BIT(_REG_GPIO4_OEZ, TRUE, BIT1))
#define Clr_i2c_SDA_VGA()           (MEM_MSWRITE_BIT(_REG_GPIO4_OUT, FALSE, BIT1), MEM_MSWRITE_BIT(_REG_GPIO4_OEZ, FALSE, BIT1))
#define i2c_SDAHi_VGA()             (_bit1_(MEM_MSREAD_BYTE(_REG_GPIO4_IN)))
#define i2c_SDALo_VGA()             (!i2c_SDAHi_VGA())

#define Set_i2c_SCL_VGA()           (MEM_MSWRITE_BIT(_REG_GPIO4_OEZ, TRUE, BIT0))
#define Clr_i2c_SCL_VGA()           (MEM_MSWRITE_BIT(_REG_GPIO4_OUT, FALSE, BIT0), MEM_MSWRITE_BIT(_REG_GPIO4_OEZ, FALSE, BIT0))
#define i2c_SCLHi_VGA()             (_bit0_(MEM_MSREAD_BYTE(_REG_GPIO4_IN)))
#define i2c_SCLLo_VGA()             (!i2c_SCLHi_VGA())

#define INIT_HW_DVII2C_SDA_PIN()    (MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, TRUE, BIT5))
#define INIT_HW_DVII2C_SCL_PIN()    (MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, TRUE, BIT4))

#define Set_i2c_SDA_DVI()           (MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, TRUE, BIT5))
#define Clr_i2c_SDA_DVI()           (MEM_MSWRITE_BIT(_REG_GPIO3_OUT, FALSE, BIT5), MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, FALSE, BIT5))
#define i2c_SDAHi_DVI()             (_bit5_(MEM_MSREAD_BYTE(_REG_GPIO3_IN)))
#define i2c_SDALo_DVI()             (!i2c_SDAHi_DVI())

#define Set_i2c_SCL_DVI()           (MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, TRUE, BIT4))
#define Clr_i2c_SCL_DVI()           (MEM_MSWRITE_BIT(_REG_GPIO3_OUT, FALSE, BIT4), MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, FALSE, BIT4))
#define i2c_SCLHi_DVI()             (_bit4_(MEM_MSREAD_BYTE(_REG_GPIO3_IN)))
#define i2c_SCLLo_DVI()             (!i2c_SCLHi_DVI())

#define Set_NVRAM_i2c_SDA()		      		((EnableReadDDCType==I2C_EEPROM)?hw_Set_I2C_SDA_Pin:((EnableReadDDCType==VGA_EDID)?Set_i2c_SDA_VGA():Set_i2c_SDA_DVI()))
#define Clr_NVRAM_i2c_SDA()		              	((EnableReadDDCType==I2C_EEPROM)?hw_Clr_I2C_SDA_Pin:((EnableReadDDCType==VGA_EDID)?Clr_i2c_SDA_VGA():Clr_i2c_SDA_DVI()))
#define NVRAM_i2c_SDA_IS_HI()			      	((EnableReadDDCType==I2C_EEPROM)?hw_I2C_SDA_HI:((EnableReadDDCType==VGA_EDID)?i2c_SDAHi_VGA():i2c_SDAHi_DVI()))
#define NVRAM_i2c_SDA_IS_LO()			      	((EnableReadDDCType==I2C_EEPROM)?hw_I2C_SDA_LO:((EnableReadDDCType==VGA_EDID)?i2c_SDALo_VGA():i2c_SDALo_DVI()))

#define Set_NVRAM_i2c_SCL()			      	((EnableReadDDCType==I2C_EEPROM)?hw_Set_I2C_SCL_Pin:((EnableReadDDCType==HDMI_EDID)?Set_i2c_SCL_VGA():Set_i2c_SCL_DVI()))
#define Clr_NVRAM_i2c_SCL()			      	((EnableReadDDCType==I2C_EEPROM)?hw_Clr_I2C_SCL_Pin:((EnableReadDDCType==HDMI_EDID)?Clr_i2c_SCL_VGA():Clr_i2c_SCL_DVI()))
#define NVRAM_i2c_SCL_IS_HI()			      	((EnableReadDDCType==I2C_EEPROM)?hw_I2C_SCL_HI:((EnableReadDDCType==HDMI_EDID)?i2c_SCLHi_VGA():i2c_SCLHi_DVI()))
#define NVRAM_i2c_SCL_IS_LO()			      	((EnableReadDDCType==I2C_EEPROM)?hw_I2C_SCL_LO:((EnableReadDDCType==HDMI_EDID)?i2c_SCLLo_VGA():i2c_SCLLo_DVI()))

#endif

#if !USEFLASH

#define Init_NVRAM_I2C_SCL_Pin()    (MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, TRUE, BIT4))
#define Init_NVRAM_I2C_SDA_Pin()    (MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, TRUE, BIT5))

#define Set_NVRAM_i2c_SDA()      	(MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, TRUE, BIT5))
#define Clr_NVRAM_i2c_SDA()       	(MEM_MSWRITE_BIT(_REG_GPIO0_OUT, FALSE, BIT5), MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, FALSE, BIT5))
#define NVRAM_i2c_SDA_IS_HI()     	(_bit5_(MEM_MSREAD_BYTE(_REG_GPIO0_IN)))
#define NVRAM_i2c_SDA_IS_LO()     	(!NVRAM_i2c_SDA_IS_HI())

#define Set_NVRAM_i2c_SCL()       	(MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, TRUE, BIT4))
#define Clr_NVRAM_i2c_SCL()       	(MEM_MSWRITE_BIT(_REG_GPIO0_OUT, FALSE, BIT4), MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, FALSE, BIT4))
#define NVRAM_i2c_SCL_IS_HI()     	(_bit4_(MEM_MSREAD_BYTE(_REG_GPIO0_IN)))
#define NVRAM_i2c_SCL_IS_LO()     	(!NVRAM_i2c_SCL_IS_HI())

#endif

#define V5_VDET     ()//    (_bit0_(MEM_MSREAD_BYTE(_REG_PMGPIOSAR_IN)))
#define Init_5V_VDET() //    (MEM_MSWRITE_BIT(_REG_PMGPIOSAR_OEZ, 1, BIT0))

//_REG_PMGPIO2_OEZ
#define Init_VCOM_I2C_SDA_Pin()    		//(MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, TRUE, BIT0))
#define Init_VCOM_I2C_SCL_Pin()    		//(MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, TRUE, BIT1))

#define HW_SET_VCOM_I2C_SDA()          	//(MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, TRUE, BIT0))
#define HW_CLR_VCOM_I2C_SDA()           //(MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, FALSE, BIT0), MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, FALSE, BIT0))
#define HW_GET_VCOM_I2C_SDA_HI()     	//(_bit0_(MEM_MSREAD_BYTE(_REG_PMGPIO0_IN)))
#define HW_GET_VCOM_I2C_SDA_Lo()     	//(!HW_GET_VCOM_I2C_SDA_HI())

#define HW_SET_VCOM_I2C_SCL()           //(MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, TRUE, BIT1))
#define HW_CLR_VCOM_I2C_SCL()           //(MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, FALSE, BIT1), MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, FALSE, BIT1))
#define HW_GET_VCOM_I2C_SCL_HI()    	//(_bit1_(MEM_MSREAD_BYTE(_REG_PMGPIO0_IN)))
#define HW_GET_VCOM_I2C_SCL_Lo()       	//(!HW_GET_VCOM_I2C_SCL_HI())

#if ENABLE_HDCP
#define hwHDCP_Hpd_Pin //GPIO36 = Port A, GPIO31 = Port B, GPIO52 = Port C
#if HPD_INVERSE
#define hw_Set_HdcpHpd()        //(MEM_MSWRITE_BIT(_REG_GPIO3_OUT, FALSE, BIT6), MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, FALSE, BIT6))
#define hw_Clr_HdcpHpd()        //(MEM_MSWRITE_BIT(_REG_GPIO3_OUT, TRUE, BIT6), MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, FALSE, BIT6))
#define Init_hwHDCP_Hpd_Pin()   //(MEM_MSWRITE_BIT(_REG_GPIO3_OUT, FALSE, BIT6), MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, FALSE, BIT6)) //default high
#define hw_Set_HdcpHpd2()       //(MEM_MSWRITE_BIT(_REG_GPIO3_OUT, FALSE, BIT1), MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, FALSE, BIT1))
#define hw_Clr_HdcpHpd2()       //(MEM_MSWRITE_BIT(_REG_GPIO3_OUT, TRUE, BIT1), MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, FALSE, BIT1))
#define Init_hwHDCP_Hpd2_Pin()  //(MEM_MSWRITE_BIT(_REG_GPIO3_OUT, FALSE, BIT1), MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, FALSE, BIT1)) //default high
#define hw_Set_HdcpHpd3()       //(MEM_MSWRITE_BIT(_REG_GPIO5_OUT, FALSE, BIT2), MEM_MSWRITE_BIT(_REG_GPIO5_OEZ, FALSE, BIT2))
#define hw_Clr_HdcpHpd3()       //(MEM_MSWRITE_BIT(_REG_GPIO5_OUT, TRUE, BIT2), MEM_MSWRITE_BIT(_REG_GPIO5_OEZ, FALSE, BIT2))
#define Init_hwHDCP_Hpd_Pin3()  //(MEM_MSWRITE_BIT(_REG_GPIO5_OUT, FALSE, BIT2), MEM_MSWRITE_BIT(_REG_GPIO5_OEZ, FALSE, BIT2)) //default high
#else

//DVI HPD
#define hw_Set_HdcpHpd()        	(MEM_MSWRITE_BIT(_REG_GPIO3_OUT, TRUE, BIT7), MEM_MSWRITE_BIT(_REG_GPIO3_OEZ,TRUE, BIT7))//, MEM_MSWRITE_BIT(REG_0262, FALSE, BIT3), MEM_MSWRITE_BIT(REG_0265, TRUE, BIT4))
#define hw_Clr_HdcpHpd()        	(MEM_MSWRITE_BIT(_REG_GPIO3_OUT, FALSE, BIT7), MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, FALSE, BIT7))//, MEM_MSWRITE_BIT(REG_0262, FALSE, BIT3), MEM_MSWRITE_BIT(REG_0265, FALSE, BIT4))
#define Init_hwHDCP_Hpd_Pin()   	(MEM_MSWRITE_BIT(_REG_GPIO3_OUT, TRUE, BIT7), MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, TRUE, BIT7))//, MEM_MSWRITE_BIT(REG_0262, FALSE, BIT3), MEM_MSWRITE_BIT(REG_0265, FALSE, BIT4)) //default low
//HDMI HPD
#define hw_Set_HdcpHpd2()         (MEM_MSWRITE_BIT(_REG_GPIO3_OUT, TRUE, BIT1), MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, TRUE, BIT1), MEM_MSWRITE_BIT(REG_0262, TRUE, BIT2), MEM_MSWRITE_BIT(REG_0265, TRUE, BIT3))
#define hw_Clr_HdcpHpd2()          (MEM_MSWRITE_BIT(_REG_GPIO3_OUT, FALSE, BIT1), MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, FALSE, BIT1), MEM_MSWRITE_BIT(REG_0262, TRUE, BIT2), MEM_MSWRITE_BIT(REG_0265, TRUE, BIT3))
#define Init_hwHDCP_Hpd2_Pin()  (MEM_MSWRITE_BIT(_REG_GPIO3_OUT, FALSE, BIT1), MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, FALSE, BIT1), MEM_MSWRITE_BIT(REG_0262, FALSE, BIT2), MEM_MSWRITE_BIT(REG_0265, FALSE, BIT3)) //default low

//DP HPD
#define hw_Set_HdcpHpd3()       	//(MEM_MSWRITE_BIT(_REG_GPIO5_OUT, TRUE, BIT2), MEM_MSWRITE_BIT(_REG_GPIO5_OEZ, FALSE, BIT2), MEM_MSWRITE_BIT(REG_0262, TRUE, BIT5), MEM_MSWRITE_BIT(REG_0265, TRUE, BIT5))
#define hw_Clr_HdcpHpd3()       	//(MEM_MSWRITE_BIT(_REG_GPIO5_OUT, FALSE, BIT2), MEM_MSWRITE_BIT(_REG_GPIO5_OEZ, FALSE, BIT2), MEM_MSWRITE_BIT(REG_0262, FALSE, BIT5), MEM_MSWRITE_BIT(REG_0265, FALSE, BIT5))
#define Init_hwHDCP_Hpd3_Pin()  	//(MEM_MSWRITE_BIT(_REG_GPIO5_OUT, TRUE, BIT2), MEM_MSWRITE_BIT(_REG_GPIO5_OEZ, FALSE, BIT2),  MEM_MSWRITE_BIT(REG_0262, TRUE, BIT5), MEM_MSWRITE_BIT(REG_0265, TRUE, BIT5)) //default low
#endif //HPD_INVERSE

#endif //ENABLE_HDCP



#if 1

//SARKEY_ENABLE_BIT
#define SAR0_EN     BIT0
#define SAR1_EN     BIT1
#define SAR2_EN     BIT2
#define SAR3_EN     BIT3
#define SARKEY_EN    (SAR1_EN|SAR2_EN)//(SAR1_EN|SAR2_EN)

#define SAR4_EN     BIT0
#define SAR5_EN     BIT1
#define SAR6_EN     BIT2
#define SAR7_EN     BIT3

#define KEYPAD_ADC_A        KEYPAD_SAR1//KEYPAD_SAR1
#define KEYPAD_ADC_B        KEYPAD_SAR2//KEYPAD_SAR2
//#define KEYPAD_ADC_C        KEYPAD_SAR3

#define AOVDV_VALUE     4
#endif
//#define LVDS_CHANNEL    (MOD_PORTB|MOD_PORTC)//(MOD_PORTA|MOD_PORTB|MOD_PORTC|MOD_PORTD)
//#define I_GEN_CH        CH2


// MHL PS_CTRL
#define SET_MHL_PS_CTRL_CHARGE0()    //(MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, TRUE, BIT1), MEM_MSWRITE_BIT(_REG_GPIO2_OUT, TRUE, BIT1))
#define CLR_MHL_PS_CTRL_CHARGE0()    //(MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, FALSE, BIT1), MEM_MSWRITE_BIT(_REG_GPIO2_OUT, FALSE, BIT1))

#define SET_MHL_PS_CTRL_CHARGE1()   // (MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, TRUE, BIT0), MEM_MSWRITE_BIT(_REG_GPIO2_OUT, TRUE, BIT0))
#define CLR_MHL_PS_CTRL_CHARGE1()    //(MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, FALSE, BIT0), MEM_MSWRITE_BIT(_REG_GPIO2_OUT, FALSE, BIT0))

#define SET_MHL_PS_CTRL_CHARGE2()    //(MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, TRUE, BIT4), MEM_MSWRITE_BIT(_REG_GPIO2_OUT, TRUE, BIT4))
#define CLR_MHL_PS_CTRL_CHARGE2()    //(MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, FALSE, BIT4), MEM_MSWRITE_BIT(_REG_GPIO2_OUT, FALSE, BIT4))




#endif

