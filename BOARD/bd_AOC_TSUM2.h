
#ifndef __BD_MSTMCU__
#define __BD_MSTMCU__

#define MCU_SPEED_INDEX     IDX_MCU_CLK_108MHZ
#define SPI_SPEED_INDEX     IDX_SPI_CLK_43MHZ
#define SPI_MODE            SPI_MODE_FR

#define DVI_PORT                TMDS_PORT_A
#define DVI_HPD_PORT           TMDS_PORT_A
#define DVI_DDC_PORT            TMDS_PORT_A
#define DVI_MASTER_PORT         TMDS_PORT_A
//set to 0 if not DVI dual port enable
#define DVI_SLAVE_PORT          TMDS_PORT_UNUSE

#define HDMI_PORT               TMDS_PORT_B//TMDS_PORT_UNUSE
#define HDMI_HPD_PORT           TMDS_PORT_B//TMDS_PORT_UNUSE
#define HDMI_DDC_PORT           TMDS_PORT_B//TMDS_PORT_UNUSE

#define SERIAL_BAUD_RATE           9600

#define BrightnessPWM          _PWM4_
#define Init_BrightnessPWM()    { MEM_MSWRITE_BYTE_MASK(REG_0213,BIT1,BIT1);MEM_MSWRITE_BYTE_MASK(REG_0280,BIT0,BIT0);}

#if AudioFunc
#define VolumePWM               _PWM5_
#define Init_VolumePWM()      { MEM_MSWRITE_BYTE_MASK(REG_0213,BIT7,BIT7);MEM_MSWRITE_BYTE_MASK(REG_0280,BIT1,BIT1);}
#endif

#if 1
#define PowerKey         (_bit0_(MEM_MSREAD_BYTE(_REG_PMGPIO0_IN)))
#define Init_PowerKey()     (MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, 1, BIT0))
#else
#define PowerKey               (_bit0_(MEM_MSREAD_BYTE(_REG_PMGPIOSAR_IN)))
#define Init_PowerKey()     MEM_MSWRITE_BIT(_REG_PMGPIOSAR_OEZ, 1, BIT0)
#endif




#define NonUsepin           

//========================================================
// 1.Write protection:
#define hwDDC_WP_Pin           
#define hwEEPROM_WP          // GPIO04
#define hwFlash_WP_Pin       // GPIO07

// ddc eeprom wp be pulled high to 5V, set to input for output high level
#define hw_SetDDC_WP()      (MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, 1, BIT5))
#define hw_ClrDDC_WP()      (MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, 0, BIT5), MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, 0, BIT5))
#define Init_hwDDC_WP_Pin()     (MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, 1, BIT5))

#define Set_EEPROM_WP()     MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, 1, BIT0) //MEM_MSWRITE_BIT(_REG_GPIO0_OUT, 1, BIT4)
#define Clr_EEPROM_WP()      MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, 0, BIT0)//MEM_MSWRITE_BIT(_REG_GPIO0_OUT, 0, BIT4)
#define Init_hwEEPROM_WP()  MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, 0, BIT0)//MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, 0, BIT4) // output enable

#define hw_SetFlashWP()         MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, 1, BIT0)//MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, 1, BIT7)
#define hw_ClrFlashWP()          MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, 0, BIT0)//MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, 0, BIT7)
#define Init_hwFlash_WP_Pin()   MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, 0, BIT0)//MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, 0, BIT7) // output enable
//========================================================
// 2.Backlight and panelon:
#define hwBlacklit_Pin     
#define hwPanel_Pin        
#if 0 // MST144A_A01A
#define hw_SetBlacklit()    (MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, 0, BIT5), BackLightActiveFlag=1)//{MEM_MSWRITE_BIT(_REG_GPIO0_OUT, 1, BIT5); BackLightActiveFlag=1;}
#define hw_ClrBlacklit()    (MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, 1, BIT5), BackLightActiveFlag=0)//{MEM_MSWRITE_BIT(_REG_GPIO0_OUT, 0, BIT5); BackLightActiveFlag=0;}
#define Init_hwBlacklit_Pin()   MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, 0, BIT5) // output enable

#define hw_SetPanel()          MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, 0, BIT4)  //GPIO12 output value
#define hw_ClrPanel()          MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, 1, BIT4)
#define Init_hwPanel_Pin()     MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, 0, BIT4)
#else
#define hw_SetBlacklit()    (MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, 0, BIT3), BackLightActiveFlag=1)//{MEM_MSWRITE_BIT(_REG_GPIO0_OUT, 1, BIT5); BackLightActiveFlag=1;}
#define hw_ClrBlacklit()    (MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, 1, BIT3), BackLightActiveFlag=0)//{MEM_MSWRITE_BIT(_REG_GPIO0_OUT, 0, BIT5); BackLightActiveFlag=0;}
#define Init_hwBlacklit_Pin()   MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, 0, BIT3) // output enable


#define hw_SetPanel()          MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, 1, BIT6)  //GPIO12 output value
#define hw_ClrPanel()          MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, 0, BIT6)
#define Init_hwPanel_Pin()     MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, 0, BIT6)
#endif
//========================================================
// 4.Detect Cable
#define CABLE_DETECT_VGA_USE_SAR    1
#define CABLE_DETECT_DVI_USE_SAR    1

#if CABLE_DETECT_VGA_USE_SAR
#define hwDSUBCable_Pin        
#define Init_hwDSUBCable_Pin()  
#define CABLE_DET_VGA_SAR    SAR3_EN
#else
#define hwDSUBCable_Pin        //(_bit2_(MEM_MSREAD_BYTE(_REG_PMGPIO0_IN)))
#define Init_hwDSUBCable_Pin()  //(MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ,1,BIT2)) // input enable
#define CABLE_DET_VGA_SAR    0
#endif
#if CABLE_DETECT_DVI_USE_SAR
#define hwDVICable_Pin      
#define Init_hwDVICable_Pin()
#define CABLE_DET_DVI_SAR    SAR3_EN
#else
#define hwDVICable_Pin      //(_bit3_(MEM_MSREAD_BYTE(_REG_PMGPIO0_IN)))
#define Init_hwDVICable_Pin()   //(MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ,1,BIT3)) // input enable
#define CABLE_DET_DVI_SAR    0
#endif

#if ENABLE_HDMI
#define CABLE_DETECT_HDMI_USE_SAR    0
#define hwHDMICable_Pin
#define Init_hwHDMICable_Pin()
#define CABLE_DET_HDMI_SAR    0
#else
#define CABLE_DETECT_HDMI_USE_SAR    0
#define CABLE_DET_HDMI_SAR    0
#endif

#define CABLE_DET_SAR_EN    (CABLE_DET_VGA_SAR|CABLE_DET_DVI_SAR|CABLE_DET_HDMI_SAR)
#define CABLE_DET_SAR           KEYPAD_SAR3

//========================================================
// 5.Led

#define hwGreenLed_Pin      // GPIO01
#define hwAmberLed_Pin     // GPIO00

#define hw_SetGreenLed()            {MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ,0,BIT1);MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT,1,BIT1);}//MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT,1,BIT1)
#define hw_ClrGreenLed()            MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT,0,BIT1)//MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT,0,BIT1)
#define Init_hwGreenLed_Pin()   MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ,0,BIT1)//MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ,0,BIT1) // output enable

#define hw_SetAmberLed()           MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, 0, BIT2)//MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, 0, BIT0)
#define hw_ClrAmberLed()           MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, 1, BIT2)//MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, 1, BIT0)
#define Init_hwAmberLed_Pin()   MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, 0, BIT2)//MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, 0, BIT0) // output enable

//========================================================
// 6.Audio control:
#define hwMute_Pin             
#define hw_SetMute()           MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, 0, BIT4)
#define hw_ClrMute()           MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, 1, BIT4)
#define Init_hwMute_Pin()   MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, 0, BIT4)

#define hwAudio_SD_Pin() //GPIO02
#define hw_SetAudio_SD()            		MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, 0, BIT5)
#define hw_ClrAudio_SD()        		MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, 1, BIT5)
#define Init_Audio_SD_Pin()			MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, 0, BIT5)

#define hwStandby_Pin()
#define hw_SetStandby()            
#define hw_ClrStandby()        
//========================================================
// I2C
#if defined(UseVGACableReadWriteAllPortsEDID) //&&!defined(UseInternalDDCRam)

 #define Set_i2c_SDA_VGA()          (MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, TRUE, BIT1))
#define Clr_i2c_SDA_VGA()          (MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, FALSE, BIT1), MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, FALSE, BIT1))
#define i2c_SDAHi_VGA()     (_bit1_(MEM_MSREAD_BYTE(_REG_PMGPIO2_IN)))
#define i2c_SDALo_VGA()     (!i2c_SDAHi())
#define Set_i2c_SCL_VGA()          (MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, TRUE, BIT2))
#define Clr_i2c_SCL_VGA()          (MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, FALSE, BIT2), MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, FALSE, BIT2))
#define i2c_SCLHi_VGA()     (_bit2_(MEM_MSREAD_BYTE(_REG_PMGPIO2_IN)))
#define i2c_SCLLo_VGA()     (!i2c_SCLHi())

#define Set_i2c_SDA_DVI()          (MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT2))
#define Clr_i2c_SDA_DVI()          (MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, FALSE, BIT2), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, FALSE, BIT2))
#define i2c_SDAHi_DVI()     (_bit2_(MEM_MSREAD_BYTE(_REG_PMGPIO1_IN)))
#define i2c_SDALo_DVI()     (!i2c_SDAHi())
#define Set_i2c_SCL_DVI()          (MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT3))
#define Clr_i2c_SCL_DVI()          (MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, FALSE, BIT3), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, FALSE, BIT3))
#define i2c_SCLHi_DVI()     (_bit3_(MEM_MSREAD_BYTE(_REG_PMGPIO1_IN)))
#define i2c_SCLLo_DVI()     (!i2c_SCLHi())

 #define Set_i2c_SDA()       ((LoadEDIDSelectPort == DVI1)?(Set_i2c_SDA_DVI()):(Set_i2c_SDA_VGA()))
#define Clr_i2c_SDA()       ((LoadEDIDSelectPort == DVI1)?(Clr_i2c_SDA_DVI()):(Clr_i2c_SDA_VGA()))
#define i2c_SDAHi()         ((LoadEDIDSelectPort == DVI1)?(i2c_SDAHi_DVI()):(i2c_SDAHi_VGA()))
#define i2c_SDALo()         ((LoadEDIDSelectPort == DVI1)?(i2c_SDALo_DVI()):(i2c_SDALo_VGA()))

#define Set_i2c_SCL()           ((LoadEDIDSelectPort == DVI1)?(Set_i2c_SCL_DVI()):(Set_i2c_SCL_VGA()))
#define Clr_i2c_SCL()           ((LoadEDIDSelectPort == DVI1)?(Clr_i2c_SCL_DVI()):(Clr_i2c_SCL_VGA()))
#define i2c_SCLHi()         ((LoadEDIDSelectPort == DVI1)?(i2c_SCLHi_DVI()):(i2c_SCLHi_VGA()))
#define i2c_SCLLo()         ((LoadEDIDSelectPort == DVI1)?(i2c_SCLLo_DVI()):(i2c_SCLLo_VGA()))
#endif

#if !USEFLASH

#define Init_NVRAM_I2C_SCL_Pin()    (MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT6))
#define Init_NVRAM_I2C_SDA_Pin()    (MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT7))

#define Set_NVRAM_i2c_SDA()          (MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT7))
#define Clr_NVRAM_i2c_SDA()          (MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, FALSE, BIT7), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, FALSE, BIT7))
#define NVRAM_i2c_SDA_IS_HI()     (_bit7_(MEM_MSREAD_BYTE(_REG_PMGPIO1_IN)))
#define NVRAM_i2c_SDA_IS_LO()     (!NVRAM_i2c_SDA_IS_HI())

#define Set_NVRAM_i2c_SCL()          (MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT6))
#define Clr_NVRAM_i2c_SCL()          (MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, FALSE, BIT6), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, FALSE, BIT6))
#define NVRAM_i2c_SCL_IS_HI()     (_bit6_(MEM_MSREAD_BYTE(_REG_PMGPIO1_IN)))
#define NVRAM_i2c_SCL_IS_LO()     (!NVRAM_i2c_SCL_IS_HI())

#endif


//_REG_PMGPIO2_OEZ
#define Init_VCOM_I2C_SDA_Pin()    		(MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, TRUE, BIT0))
#define Init_VCOM_I2C_SCL_Pin()    		(MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, TRUE, BIT1))

#define HW_SET_VCOM_I2C_SDA()          	(MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, TRUE, BIT0))
#define HW_CLR_VCOM_I2C_SDA()           (MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, FALSE, BIT0), MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, FALSE, BIT0))
#define HW_GET_VCOM_I2C_SDA_HI()     	(_bit0_(MEM_MSREAD_BYTE(_REG_PMGPIO0_IN)))
#define HW_GET_VCOM_I2C_SDA_Lo()     	(!HW_GET_VCOM_I2C_SDA_HI())

#define HW_SET_VCOM_I2C_SCL()           (MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, TRUE, BIT1))
#define HW_CLR_VCOM_I2C_SCL()           (MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, FALSE, BIT1), MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, FALSE, BIT1))
#define HW_GET_VCOM_I2C_SCL_HI()     	(_bit1_(MEM_MSREAD_BYTE(_REG_PMGPIO0_IN)))
#define HW_GET_VCOM_I2C_SCL_Lo()       	(!HW_GET_VCOM_I2C_SCL_HI())



#if ENABLE_HDCP
#define hwHDCP_Hpd_Pin      
#define hw_Set_HdcpHpd() 		
#define hw_Clr_HdcpHpd() 		
#define Init_hwHDCP_Hpd_Pin()

#define hw_Set_HdcpHpd2() 
#define hw_Clr_HdcpHpd2() 
#define Init_hwHDCP_Hpd_Pin2()

#define hw_Set_HdcpHpd3() 
#define hw_Clr_HdcpHpd3() 
#define Init_hwHDCP_Hpd_Pin3()
#endif



//SARKEY_ENABLE_BIT
#define SAR0_EN     BIT0
#define SAR1_EN     BIT1
#define SAR2_EN     BIT2
#define SAR3_EN     BIT3
#define SARKEY_EN   0

//#define SARKEY_EN   (SAR0_EN|SAR1_EN|SAR2_EN)

#define KEYPAD_ADC_A        KEYPAD_SAR1
#define KEYPAD_ADC_B        KEYPAD_SAR2
#define AOVDV_VALUE     4


#define LVDS_CHANNEL    (MOD_PORTB|MOD_PORTC)//(MOD_PORTA|MOD_PORTB|MOD_PORTC|MOD_PORTD)
#define I_GEN_CH        CH3_CLK

#define V5_VDET         (_bit0_(MEM_MSREAD_BYTE(_REG_PMGPIOSAR_IN)))
#define Init_5V_VDET()     (MEM_MSWRITE_BIT(_REG_PMGPIOSAR_OEZ, 1, BIT0))


#if ENABLE_MHL
// SWI2C for Eland
#if 1 // tpv board
#define SET_SWI2C_SCL()       MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, TRUE, BIT4)//MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, TRUE, BIT4)         //PMGPIO24
#define CLR_SWI2C_SCL()       (MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT,FALSE, BIT4), MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ,FALSE, BIT4))//MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT,FALSE, BIT4)
#define IS_SWI2C_SCL_HI()     (_bit4_(MEM_MSREAD_BYTE(_REG_PMGPIO2_IN)))
#define IS_SWI2C_SCL_LO()     (!IS_SWI2C_SCL_HI())

#define SET_SWI2C_SDA()       MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, TRUE, BIT3)//MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, TRUE, BIT3)         //PMGPIO23
#define CLR_SWI2C_SDA()       (MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT,FALSE, BIT3), MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ,FALSE, BIT3))//MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT,FALSE, BIT3)
#define IS_SWI2C_SDA_HI()     (_bit3_(MEM_MSREAD_BYTE(_REG_PMGPIO2_IN)))
#define IS_SWI2C_SDA_LO()     (!IS_SWI2C_SDA_HI())

#define SET_SWI2C_SCL_IN()    MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, TRUE, BIT4)
#define SET_SWI2C_SCL_OUT()   MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ,FALSE, BIT4)
#define SET_SWI2C_SDA_IN()    MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, TRUE, BIT3)
#define SET_SWI2C_SDA_OUT()   MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ,FALSE, BIT3)
//#define SET_SWI2C_BUS_OUT()   MEM_MSWRITE_BYTE_MASK(_REG_PMGPIO2_OEZ, 0x00, BIT6|BIT7)

// MHL cable detect
#define SET_MHL_CABLE_DETECT()    MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT1)    // PMGPIO11
#define IS_MHL_CABLE_HI()     (_bit1_(MEM_MSREAD_BYTE(_REG_PMGPIO1_IN)))
#define IS_MHL_CABLE_LO()     (!IS_MHL_CABLE_HI())


//#define SET_MHL_PS_CTRL_HI()            		MEM_MSWRITE_BIT(_REG_PMGPIO3_OUT, 1, BIT7)
//#define SET_MHL_PS_CTRL_LO()        		MEM_MSWRITE_BIT(_REG_PMGPIO3_OUT, 0, BIT7)
//#define INit_SET_MHL_PS_CTRL()			MEM_MSWRITE_BIT(_REG_PMGPIO3_OEZ, 0, BIT7)


#define Init_MHL_PS_CTRL_Pin()  (MEM_MSWRITE_BIT(_REG_PMGPIO3_OUT, FALSE, BIT7), MEM_MSWRITE_BIT(_REG_PMGPIO3_OEZ, FALSE, BIT7))//(MEM_MSWRITE_BIT(_REG_PMGPIO3_OEZ, TRUE, BIT7))
#define Set_MHL_PS_CTRL_CHARGE()    (MEM_MSWRITE_BIT(_REG_PMGPIO3_OEZ, TRUE, BIT7))
#define Clr_MHL_PS_CTRL_CHARGE()    (MEM_MSWRITE_BIT(_REG_PMGPIO3_OUT, FALSE, BIT7), MEM_MSWRITE_BIT(_REG_PMGPIO3_OEZ, FALSE, BIT7))

#else
#define SET_SWI2C_SCL()       MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, TRUE, BIT7)         //PMGPIO27
#define CLR_SWI2C_SCL()       MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT,FALSE, BIT7)
#define IS_SWI2C_SCL_HI()     (_bit7_(MEM_MSREAD_BYTE(_REG_PMGPIO2_IN)))
#define IS_SWI2C_SCL_LO()     (!IS_SWI2C_SCL_HI())

#define SET_SWI2C_SDA()       MEM_MSWRITE_BIT(_REG_PMGPIO3_OUT, TRUE, BIT6)         //PMGPIO36
#define CLR_SWI2C_SDA()       MEM_MSWRITE_BIT(_REG_PMGPIO3_OUT,FALSE, BIT6)
#define IS_SWI2C_SDA_HI()     (_bit6_(MEM_MSREAD_BYTE(_REG_PMGPIO3_IN)))
#define IS_SWI2C_SDA_LO()     (!IS_SWI2C_SDA_HI())

#define SET_SWI2C_SCL_IN()    MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, TRUE, BIT7)
#define SET_SWI2C_SCL_OUT()   MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ,FALSE, BIT7)
#define SET_SWI2C_SDA_IN()    MEM_MSWRITE_BIT(_REG_PMGPIO3_OEZ, TRUE, BIT6)
#define SET_SWI2C_SDA_OUT()   MEM_MSWRITE_BIT(_REG_PMGPIO3_OEZ,FALSE, BIT6)
//#define SET_SWI2C_BUS_OUT()   MEM_MSWRITE_BYTE_MASK(_REG_PMGPIO2_OEZ, 0x00, BIT6|BIT7)

// MHL cable detect
#define SET_MHL_CABLE_DETECT()    MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT4)    // PMGPIO14
#define IS_MHL_CABLE_HI()     (_bit4_(MEM_MSREAD_BYTE(_REG_PMGPIO1_IN)))
#define IS_MHL_CABLE_LO()     (!IS_MHL_CABLE_HI())

// MHL PS_CTRL
//#define SET_MHL_PS_CTRL_OUT()    MEM_MSWRITE_BIT(_REG_PMGPIO3_OEZ, FALSE, BIT7)    // PMGPIO37
#define SET_MHL_PS_CTRL_HI()    MEM_MSWRITE_BIT(_REG_PMGPIO3_OUT, TRUE, BIT7)
#define SET_MHL_PS_CTRL_LO()    {MEM_MSWRITE_BIT(_REG_PMGPIO3_OUT, FALSE, BIT7); MEM_MSWRITE_BIT(_REG_PMGPIO3_OEZ, FALSE, BIT7);}
#endif // #if ENABLE_MHL
#endif

#endif


