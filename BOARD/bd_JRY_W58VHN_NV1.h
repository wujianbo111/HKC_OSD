#ifndef __BD_RY_W58VHN_NV1__
#define __BD_RY_W58VHN_NV1__

#define MCU_SPEED_INDEX     	IDX_MCU_CLK_108MHZ
#define SPI_SPEED_INDEX     	IDX_SPI_CLK_43MHZ
#define SPI_MODE            	SPI_MODE_FR

#define DVI_PORT                TMDS_PORT_A
#define DVI_HPD_PORT            TMDS_PORT_A
#define DVI_DDC_PORT            TMDS_PORT_A
#define DVI_MASTER_PORT         TMDS_PORT_A
//set to 0 if not DVI dual port enable
#define DVI_SLAVE_PORT          TMDS_PORT_UNUSE

#define HDMI_PORT               TMDS_PORT_UNUSE
#define HDMI_HPD_PORT           TMDS_PORT_UNUSE
#define HDMI_DDC_PORT           TMDS_PORT_UNUSE

#define SERIAL_BAUD_RATE           9600

#define BrightnessPWM          _PWM2_
#define Init_BrightnessPWM()    { MEM_MSWRITE_BYTE_MASK(REG_1B0A,BIT6,BIT6);MEM_MSWRITE_BYTE_MASK(REG_0280,BIT5,BIT5);}

#if AudioFunc

#define VolumePWM               _PWM6_
#define Init_VolumePWM()    { MEM_MSWRITE_BYTE_MASK(REG_0227,BIT7,BIT7);MEM_MSWRITE_BYTE_MASK(REG_0280,BIT2,BIT2);}//petit 20130816 open drain
#endif

#define PowerKey          		(_bit3_(MEM_MSREAD_BYTE(_REG_PMGPIOSAR_IN)))
#define Init_PowerKey()     	MEM_MSWRITE_BIT(_REG_PMGPIOSAR_OEZ, 1, BIT7)

#define NonUsepin           	(MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, TRUE, BIT1))

//========================================================
// 1.Write protection:
#define hwDDC_WP_Pin           
#define hwEEPROM_WP
#define hwFlash_WP_Pin

#define hw_SetDDC_WP()      	(MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, BIT2, BIT2))
#define hw_ClrDDC_WP()      	(MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, 0, BIT2),MEM_MSWRITE_BIT(_REG_GPIO2_OUT, 0, BIT2))
#define Init_hwDDC_WP_Pin()     (MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, BIT2, BIT2))


#define Set_EEPROM_WP()
#define Clr_EEPROM_WP()
#define Init_hwEEPROM_WP()

#define hw_SetFlashWP()         MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, 0, BIT7)
#define hw_ClrFlashWP()         MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, 1, BIT7)
#define Init_hwFlash_WP_Pin()   MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, 0, BIT7)
//========================================================
// 2.Backlight and panelon:
#define hwBlacklit_Pin      // GPIO05
#define hwPanel_Pin         // GPIO12



#define hw_SetBlacklit()    {MEM_MSWRITE_BIT(_REG_GPIO0_OUT, 0, BIT5); BackLightActiveFlag=1;}
#define hw_ClrBlacklit()    {MEM_MSWRITE_BIT(_REG_GPIO0_OUT, 1, BIT5); BackLightActiveFlag=0;}
#define Init_hwBlacklit_Pin()   MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, 0, BIT5)

#define hw_SetPanel()       MEM_MSWRITE_BIT(_REG_GPIO0_OUT, 1, BIT4)//{MEM_MSWRITE_BIT(_REG_GPIO1_OEZ, 0, BIT2);MEM_MSWRITE_BIT(_REG_GPIO1_OUT, 0, BIT2);}
#define hw_ClrPanel()       MEM_MSWRITE_BIT(_REG_GPIO0_OUT, 0, BIT4)//MEM_MSWRITE_BIT(_REG_GPIO1_OEZ, 1, BIT2)
#define Init_hwPanel_Pin()  MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, 0, BIT4) // output enable
//========================================================
// 4.Detect Cable

#define hwDSUBCable_Pin   			(_bit6_(MEM_MSREAD_BYTE(_REG_PMGPIO1_IN)))     
#define Init_hwDSUBCable_Pin() 		(MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ,1,BIT6)) 
//#define CABLE_DET_VGA_SAR    SAR3_EN

#define hwDVICable_Pin      		(_bit4_(MEM_MSREAD_BYTE(_REG_PMGPIO0_IN)))
#define Init_hwDVICable_Pin()		(MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ,1,BIT4))
//#define CABLE_DET_DVI_SAR    SAR3_EN
#if ENABLE_HDMI
#define CABLE_DETECT_HDMI_USE_SAR    0
#define hwHDMICable_Pin
#define Init_hwHDMICable_Pin()
#define CABLE_DET_HDMI_SAR    0
#else
#define CABLE_DETECT_HDMI_USE_SAR    0
#define CABLE_DET_HDMI_SAR    0
#endif

#define CABLE_DET_SAR_EN    (CABLE_DET_HDMI_SAR)
#define CABLE_DET_SAR         0// KEYPAD_SAR3

//========================================================
// 5.Led
#define hwGreenLed_Pin
#define hwAmberLed_Pin


#define hw_SetGreenLed()          	(MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT,BIT0,BIT0),MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ,0,BIT0))
#define hw_ClrGreenLed()            (MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT,0,BIT0),MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ,0,BIT0))
#define Init_hwGreenLed_Pin()   	MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, BIT0, BIT0)

#define hw_SetAmberLed()         	(MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT,BIT1,BIT1),MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ,0,BIT1))
#define hw_ClrAmberLed()           	(MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT,0,BIT1),MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ,0,BIT1))
#define Init_hwAmberLed_Pin()   	MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, 0, BIT1)



//========================================================
// 6.Audio control:

#define hwMute_Pin
#define hw_SetMute()
#define hw_ClrMute()
#define Init_hwMute_Pin()

#define hwAudio_SD_Pin()
#define hw_SetAudio_SD()
#define hw_ClrAudio_SD()
#define Init_Audio_SD_Pin()

#define hwStandby_Pin()
#define hw_SetStandby()            
#define hw_ClrStandby()        
//========================================================
// I2C
#if 1//defined(UseVGACableReadWriteAllPortsEDID) //&&!defined(UseInternalDDCRam)
#if USEFLASH//defined(UseVGACableReadWriteAllPortsEDID) //&&!defined(UseInternalDDCRam)

#define INIT_HWI2C_SDA_PIN()	NonUsepin
#define INIT_HWI2C_SCL_PIN()	NonUsepin

#define hw_Set_I2C_SDA_Pin		NonUsepin
#define hw_Clr_I2C_SDA_Pin		NonUsepin
#define hw_I2C_SDA_HI                  NonUsepin
#define hw_I2C_SDA_LO                  NonUsepin


#define hw_Set_I2C_SCL_Pin		NonUsepin
#define hw_Clr_I2C_SCL_Pin		NonUsepin
#define hw_I2C_SCL_HI		       NonUsepin
#define hw_I2C_SCL_LO			NonUsepin


#define Init_NVRAM_I2C_SDA_Pin()			{INIT_HWI2C_SDA_PIN();INIT_HW_HDMII2C_SDA_PIN();INIT_HW_VGAI2C_SDA_PIN();}
#define Init_NVRAM_I2C_SCL_Pin()			{INIT_HWI2C_SCL_PIN();INIT_HW_HDMII2C_SCL_PIN();INIT_HW_VGAI2C_SCL_PIN();}


#define INIT_HW_HDMII2C_SDA_PIN()    (MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT2))
#define INIT_HW_HDMII2C_SCL_PIN()    (MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT3))

#define Set_i2c_SDA_HDMI()           (MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT2))
#define Clr_i2c_SDA_HDMI()           (MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, FALSE, BIT2), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, FALSE, BIT2))
#define i2c_SDAHi_HDMI()             (_bit2_(MEM_MSREAD_BYTE(_REG_PMGPIO1_IN)))
#define i2c_SDALo_HDMI()             (!i2c_SDAHi_HDMI())

#define Set_i2c_SCL_HDMI()           (MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT3))
#define Clr_i2c_SCL_HDMI()           (MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, FALSE, BIT3), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, FALSE, BIT3))
#define i2c_SCLHi_HDMI()             (_bit3_(MEM_MSREAD_BYTE(_REG_PMGPIO1_IN)))
#define i2c_SCLLo_HDMI()             (!i2c_SCLHi_HDMI())


#define INIT_HW_VGAI2C_SDA_PIN()    (MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, TRUE, BIT1))
#define INIT_HW_VGAI2C_SCL_PIN()    (MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, TRUE, BIT2))

#define Set_i2c_SDA_VGA()           (MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, TRUE, BIT1))
#define Clr_i2c_SDA_VGA()           (MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, FALSE, BIT1), MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, FALSE, BIT1))
#define i2c_SDAHi_VGA()             (_bit1_(MEM_MSREAD_BYTE(_REG_PMGPIO2_IN)))
#define i2c_SDALo_VGA()             (!i2c_SDAHi_VGA())

#define Set_i2c_SCL_VGA()           (MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, TRUE, BIT2))
#define Clr_i2c_SCL_VGA()           (MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, FALSE, BIT2), MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, FALSE, BIT2))
#define i2c_SCLHi_VGA()             (_bit2_(MEM_MSREAD_BYTE(_REG_PMGPIO2_IN)))
#define i2c_SCLLo_VGA()             (!i2c_SCLHi_VGA())

#define Set_NVRAM_i2c_SDA()		      		((EnableReadDDCType==I2C_EEPROM)?hw_Set_I2C_SDA_Pin:((EnableReadDDCType==DVI_EDID)?Set_i2c_SDA_HDMI():Set_i2c_SDA_VGA()))
#define Clr_NVRAM_i2c_SDA()		              	((EnableReadDDCType==I2C_EEPROM)?hw_Clr_I2C_SDA_Pin:((EnableReadDDCType==DVI_EDID)?Clr_i2c_SDA_HDMI():Clr_i2c_SDA_VGA()))
#define NVRAM_i2c_SDA_IS_HI()			      	((EnableReadDDCType==I2C_EEPROM)?hw_I2C_SDA_HI:((EnableReadDDCType==DVI_EDID)?i2c_SDAHi_HDMI():i2c_SDAHi_VGA()))
#define NVRAM_i2c_SDA_IS_LO()			      	((EnableReadDDCType==I2C_EEPROM)?hw_I2C_SDA_LO:((EnableReadDDCType==DVI_EDID)?i2c_SDALo_HDMI():i2c_SDALo_VGA()))

#define Set_NVRAM_i2c_SCL()			      	((EnableReadDDCType==I2C_EEPROM)?hw_Set_I2C_SCL_Pin:((EnableReadDDCType==DVI_EDID)?Set_i2c_SCL_HDMI():Set_i2c_SCL_VGA()))
#define Clr_NVRAM_i2c_SCL()			      	((EnableReadDDCType==I2C_EEPROM)?hw_Clr_I2C_SCL_Pin:((EnableReadDDCType==DVI_EDID)?Clr_i2c_SCL_HDMI():Clr_i2c_SCL_VGA()))
#define NVRAM_i2c_SCL_IS_HI()			      	((EnableReadDDCType==I2C_EEPROM)?hw_I2C_SCL_HI:((EnableReadDDCType==DVI_EDID)?i2c_SCLHi_HDMI():i2c_SCLHi_VGA()))
#define NVRAM_i2c_SCL_IS_LO()			      	((EnableReadDDCType==I2C_EEPROM)?hw_I2C_SCL_LO:((EnableReadDDCType==DVI_EDID)?i2c_SCLLo_HDMI():i2c_SCLLo_VGA()))

#endif

/*
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
//*/
#endif

#if !USEFLASH
#define hwI2C_SCL_Pin
#define hwI2C_SDA_Pin
#define Init_hwI2C_SCL_Pin()    (MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, TRUE, BIT3))
#define Init_hwI2C_SDA_Pin()    (MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, TRUE, BIT2))

#define Set_i2c_SDA()          (MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, TRUE, BIT2))
#define Clr_i2c_SDA()          (MEM_MSWRITE_BIT(_REG_GPIO0_OUT, FALSE, BIT2), MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, FALSE, BIT2))
#define i2c_SDAHi()     (_bit2_(MEM_MSREAD_BYTE(_REG_GPIO0_IN)))
#define i2c_SDALo()     (!i2c_SDAHi())
#define Set_i2c_SCL()          (MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, TRUE, BIT3))
#define Clr_i2c_SCL()          (MEM_MSWRITE_BIT(_REG_GPIO0_OUT, FALSE, BIT3), MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, FALSE, BIT3))
#define i2c_SCLHi()     (_bit3_(MEM_MSREAD_BYTE(_REG_GPIO0_IN)))
#define i2c_SCLLo()     (!i2c_SCLHi())
#endif


#define Init_VCOM_I2C_SDA_Pin()    		(MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, TRUE, BIT0))
#define Init_VCOM_I2C_SCL_Pin()    		(MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, TRUE, BIT2))
#define HW_SET_VCOM_I2C_SDA()          	(MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, TRUE, BIT0))
#define HW_CLR_VCOM_I2C_SDA()           (MEM_MSWRITE_BIT(_REG_GPIO2_OUT, FALSE, BIT0), MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, FALSE, BIT0))
#define HW_GET_VCOM_I2C_SDA_HI()     	(_bit0_(MEM_MSREAD_BYTE(_REG_GPIO2_IN)))
#define HW_GET_VCOM_I2C_SDA_Lo()     	(!HW_GET_VCOM_I2C_SDA_HI())
#define HW_SET_VCOM_I2C_SCL()           (MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, TRUE, BIT2))
#define HW_CLR_VCOM_I2C_SCL()           (MEM_MSWRITE_BIT(_REG_GPIO2_OUT, FALSE, BIT2), MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, FALSE, BIT2))
#define HW_GET_VCOM_I2C_SCL_HI()     	(_bit2_(MEM_MSREAD_BYTE(_REG_GPIO2_IN)))
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
#define SARKEY_EN   (SAR1_EN|SAR2_EN)

#define KEYPAD_ADC_A        KEYPAD_SAR1
#define KEYPAD_ADC_B        KEYPAD_SAR2
#define AOVDV_VALUE     4

#define LVDS_CHANNEL    (MOD_PORTB|MOD_PORTC)//(MOD_PORTA|MOD_PORTB|MOD_PORTC|MOD_PORTD)
#define I_GEN_CH        CH3_CLK

#endif

