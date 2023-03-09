#include "types.h"   // nick check 130109

#ifndef __BD_7343__
#define __BD_7343__


#define BoardName "JRY-L9BQHD-AV1"


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
#define Input_DVI_C1            Input_Nothing
#define Input_DVI_C2            Input_Nothing
#define Input_DVI_C3            Input_Nothing
#define Input_HDMI_C1           Input_Nothing//Input_Nothing
#define Input_HDMI_C2           Input_Digital//Input_HDMI//
#define Input_HDMI_C3           Input_Digital2
#define Input_Displayport_C2    Input_Nothing
#define Input_Displayport_C3    Input_Displayport

// For Preprocessing
#define CInput_Nothing          0
#define CInput_Digital          1
#define CInput_Digital2         2
#define CInput_Digital3         3

#define CInput_DVI_C1           CInput_Nothing//CInput_Nothing
#define CInput_DVI_C2           CInput_Nothing
#define CInput_DVI_C3           CInput_Nothing
#define CInput_HDMI_C1          CInput_Nothing//CInput_Digital2
#define CInput_HDMI_C2          CInput_Digital//CInput_Nothing
#define CInput_HDMI_C3          CInput_Digital2
#define CInput_Displayport_C2   CInput_Nothing
#define CInput_Displayport_C3   CInput_Nothing

#define DVI_PORT                ( ((CInput_DVI_C1!=CInput_Nothing)?TMDS_PORT_A:TMDS_PORT_UNUSE) | ((CInput_DVI_C2!=CInput_Nothing)?TMDS_PORT_B:TMDS_PORT_UNUSE) | ((CInput_DVI_C3!=CInput_Nothing)?TMDS_PORT_C:TMDS_PORT_UNUSE) )
#define DVI_HPD_PORT            ( ((CInput_DVI_C1!=CInput_Nothing)?TMDS_PORT_A:TMDS_PORT_UNUSE) | ((CInput_DVI_C2!=CInput_Nothing)?TMDS_PORT_B:TMDS_PORT_UNUSE) | ((CInput_DVI_C3!=CInput_Nothing)?TMDS_PORT_C:TMDS_PORT_UNUSE) )
#define DVI_DDC_PORT            ( ((CInput_DVI_C1!=CInput_Nothing)?TMDS_PORT_A:TMDS_PORT_UNUSE) | ((CInput_DVI_C2!=CInput_Nothing)?TMDS_PORT_B:TMDS_PORT_UNUSE) | ((CInput_DVI_C3!=CInput_Nothing)?TMDS_PORT_C:TMDS_PORT_UNUSE) )
#define DVI_MASTER_PORT         ( ((CInput_DVI_C1!=CInput_Nothing)?TMDS_PORT_A:TMDS_PORT_UNUSE) | ((CInput_DVI_C2!=CInput_Nothing)?TMDS_PORT_B:TMDS_PORT_UNUSE) | ((CInput_DVI_C3!=CInput_Nothing)?TMDS_PORT_C:TMDS_PORT_UNUSE) )

//set to 0 if not DVI dual port enable
#define DVI_SLAVE_PORT          TMDS_PORT_UNUSE//TMDS_PORT_UNUSE

#define HDMI_PORT               ( ((CInput_HDMI_C1!=CInput_Nothing)?TMDS_PORT_A:TMDS_PORT_UNUSE) | ((CInput_HDMI_C2!=CInput_Nothing)?TMDS_PORT_B:TMDS_PORT_UNUSE) | ((CInput_HDMI_C3!=CInput_Nothing)?TMDS_PORT_C:TMDS_PORT_UNUSE) )
#define HDMI_HPD_PORT           ( ((CInput_HDMI_C1!=CInput_Nothing)?TMDS_PORT_A:TMDS_PORT_UNUSE) | ((CInput_HDMI_C2!=CInput_Nothing)?TMDS_PORT_B:TMDS_PORT_UNUSE) | ((CInput_HDMI_C3!=CInput_Nothing)?TMDS_PORT_C:TMDS_PORT_UNUSE) )
#define HDMI_DDC_PORT           ( ((CInput_HDMI_C1!=CInput_Nothing)?TMDS_PORT_A:TMDS_PORT_UNUSE) | ((CInput_HDMI_C2!=CInput_Nothing)?TMDS_PORT_B:TMDS_PORT_UNUSE) | ((CInput_HDMI_C3!=CInput_Nothing)?TMDS_PORT_C:TMDS_PORT_UNUSE) )

// DDC port used
#define DDC_Port_D0             ((CInput_DVI_C1!=CInput_Nothing) || (CInput_HDMI_C1!=CInput_Nothing))
#define DDC_Port_D1             ((CInput_DVI_C2!=CInput_Nothing) || (CInput_HDMI_C2!=CInput_Nothing))
#define DDC_Port_D2             ((CInput_DVI_C3!=CInput_Nothing) || (CInput_HDMI_C3!=CInput_Nothing))

#define SERIAL_BAUD_RATE        9600ul

#define BrightnessPWM          		_PWM3_
#define Init_BrightnessPWM()    	{ MEM_MSWRITE_BYTE_MASK(REG_1B0B,BIT5,BIT5);}//MEM_MSWRITE_BYTE_MASK(REG_0280,BIT5,BIT5);}

#if AudioFunc
#define VolumePWM               		_PWM6_
#define Init_VolumePWM() 		{ MEM_MSWRITE_BYTE_MASK(REG_1B08,BIT6,BIT6);}//(MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, 0, BIT1),MEM_MSWRITE_BIT(_REG_GPIO0_OUT, 0, BIT1));//{MEM_MSWRITE_BYTE_MASK(REG_1B08,BIT6,BIT6);}
#endif

#define PowerKey               		(_bit3_(msReadByte(_REG_PMGPIO0_IN)))//  (MEM_MSREAD_BYTE(REG_3A20))
#define Init_PowerKey()     		MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, 1, BIT3)

#define NonUsepin

#if EarphoneDet_Enable
#define HarphoneDet_Pin           (_bit7_(MEM_MSREAD_BYTE(_REG_PMGPIO2_IN)))
#define Init_HarphoneDet_Pin()    (MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, 1, BIT7),MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, 0, BIT7))//,MEM_MSWRITE_BIT(_REG_GPIO0_SEL, 0, BIT1)
#endif

#if PowerSaving_PinContal
#define hw_SetPowerSaving_Pin()                  (MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, 0, BIT1),MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, 1, BIT1))//, DDCWPActiveFlag=1)
#define hw_ClrPowerSaving_Pin()                  (MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, 0, BIT1),MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, 0, BIT1))//, DDCWPActiveFlag=0)
#define Init_PowerSaving_Pin()    			(MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, 1, BIT1),MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, 1, BIT1))//,MEM_MSWRITE_BIT(_REG_GPIO0_SEL, 0, BIT1)
#endif

//========================================================
// 1.Write protection:
#define hwDDC_WP_Pin
#define hwEEPROM_WP          // GPIO04
#define hwFlash_WP_Pin       // GPIO07

// ddc eeprom wp be pulled high to 5V, set to input for output high level
#define hw_SetDDC_WP()                  (MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, 1, BIT4),MEM_MSWRITE_BIT(_REG_GPIO3_OUT, 1, BIT4))//, DDCWPActiveFlag=1)
#define hw_ClrDDC_WP()                  (MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, 0, BIT4),MEM_MSWRITE_BIT(_REG_GPIO3_OUT, 0, BIT4))//, DDCWPActiveFlag=0)
#define Init_hwDDC_WP_Pin()         (MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, 1, BIT4))//, DDCWPActiveFlag=1)

#define hw_SetDDC_WP()                  (MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, 1, BIT4),MEM_MSWRITE_BIT(_REG_GPIO3_OUT, 1, BIT4))//, DDCWPActiveFlag=1)
#define hw_ClrDDC_WP()                  (MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, 0, BIT4),MEM_MSWRITE_BIT(_REG_GPIO3_OUT, 0, BIT4))//, DDCWPActiveFlag=0)
#define Init_hwDDC_WP_Pin()         (MEM_MSWRITE_BIT(_REG_GPIO3_OEZ, 1, BIT4))//, DDCWPActiveFlag=1)

#define hw_SetFlashWP()         	MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, 0, BIT7)
#define hw_ClrFlashWP()         	MEM_MSWRITE_BIT(_REG_PMGPIO0_OUT, 1, BIT7)
#define Init_hwFlash_WP_Pin()   	MEM_MSWRITE_BIT(_REG_PMGPIO0_OEZ, 0, BIT7) // output enable
//========================================================
// 2.Backlight and panelon:
#define hwBlacklit_Pin      // GPIO05
#define hwPanel_Pin         // GPIO12

#define hw_SetBlacklit()    		(MEM_MSWRITE_BIT(_REG_GPIO2_OUT, 0, BIT7), BackLightActiveFlag=1)
#define hw_ClrBlacklit()    			(MEM_MSWRITE_BIT(_REG_GPIO2_OUT, 1, BIT7), BackLightActiveFlag=0)
#define Init_hwBlacklit_Pin()   		MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, 0, BIT7) // output enable

#define hw_SetPanel()       		MEM_MSWRITE_BIT(_REG_GPIO2_OUT, 1, BIT6)
#define hw_ClrPanel()       			MEM_MSWRITE_BIT(_REG_GPIO2_OUT, 0, BIT6)//(_REG_GPIO1_OUT, 0, BIT2)
#define Init_hwPanel_Pin()  		MEM_MSWRITE_BIT(_REG_GPIO2_OEZ, 0, BIT6) // output enable
//========================================================
#define CABLE_DETECT_VGA_USE_SAR    0
#define CABLE_DETECT_DVI_USE_SAR    0
// 4.Detect Cable
#define hwDSUBCable_Pin        	0//(_bit6_(MEM_MSREAD_BYTE(_REG_GPIO2_IN)))
#define Init_hwDSUBCable_Pin()  	//(MEM_MSWRITE_BIT(_REG_GPIO2_OEZ,1,BIT6)) // input enable

#define hwDVICable_Pin      		(_bit2_(MEM_MSREAD_BYTE(_REG_GPIO0_IN)))
#define Init_hwDVICable_Pin()   	(MEM_MSWRITE_BIT(_REG_GPIO0_OEZ,1,BIT2)) // input enable

#if ENABLE_HDMI
#define hwHDMICable_Pin			(_bit2_(MEM_MSREAD_BYTE(_REG_GPIO3_IN)))
#define Init_hwHDMICable_Pin()	(MEM_MSWRITE_BIT(_REG_GPIO3_OEZ,1,BIT2))
#endif

#if ENABLE_DP_INPUT
#define hwDPCable_Pin        		(_bit8_(MEM_MSREAD_BYTE(_REG_PMGPIO3_IN)))
#define Init_hwDPCable_Pin()  		(MEM_MSWRITE_BIT(_REG_PMGPIO3_OEZ, 1, BIT8))
#endif
//========================================================
// 5.Led
#define hwGreenLed_Pin      // GPIO01
#define hwAmberLed_Pin     // GPIO00
#define hw_SetGreenLed()            MEM_MSWRITE_BIT(_REG_GPIO1_OUT,1,BIT0)
#define hw_ClrGreenLed()            MEM_MSWRITE_BIT(_REG_GPIO1_OUT,0,BIT0)
#define Init_hwGreenLed_Pin()     MEM_MSWRITE_BIT(_REG_GPIO1_OEZ,0,BIT0) // output enable

#define hw_SetAmberLed()           MEM_MSWRITE_BIT(_REG_GPIO1_OUT, 1, BIT1)
#define hw_ClrAmberLed()           MEM_MSWRITE_BIT(_REG_GPIO1_OUT, 0, BIT1)
#define Init_hwAmberLed_Pin()   MEM_MSWRITE_BIT(_REG_GPIO1_OEZ, 0, BIT1) // output enable
//========================================================
// 6.Audio control:
#define hwMute_Pin
#define hw_SetMute()			(MEM_MSWRITE_BIT(_REG_GPIO0_OUT, 1, BIT0),MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, 0, BIT0))
#define hw_ClrMute()			(MEM_MSWRITE_BIT(_REG_GPIO0_OUT, 0, BIT0),MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, 0, BIT0))
#define Init_hwMute_Pin()		MEM_MSWRITE_BIT(_REG_GPIO0_OEZ, 1, BIT0)

#define hw_SetStandbyOn()		//MEM_MSWRITE_BIT(_REG_GPIO0_OUT,1,BIT0)
#define hw_ClrStandbyOn()		//MEM_MSWRITE_BIT(_REG_GPIO0_OUT,0,BIT0)
#define Init_hwStandby_WP_Pin()	//MEM_MSWRITE_BIT(_REG_GPIO0_OEZ,0,BIT0)

#define hw_SetStandbyOn()		//MEM_MSWRITE_BIT(_REG_GPIO0_OUT,1,BIT0)
#define hw_ClrStandbyOn()		//MEM_MSWRITE_BIT(_REG_GPIO0_OUT,0,BIT0)
#define Init_hwStandby_WP_Pin()	//MEM_MSWRITE_BIT(_REG_GPIO0_OEZ,0,BIT0)

//#define EarphoneDet_Enable			0


#define hwAudio_SD_Pin()                //NO_USE_PIN
#define hw_SetAudio_SD()                
#define hw_ClrAudio_SD()                
#define Init_Audio_SD_Pin()              

#define CABLE_DET_SAR_EN               0// (CABLE_DET_VGA_SAR)
#define CABLE_DET_SAR                   KEYPAD_SAR3	//	130718 william	//0
#define CABLE_DET_SAR2_EN          0//     (CABLE_DET_DVI0_SAR|CABLE_DET_DVI1_SAR|CABLE_DET_DVI2_SAR)


//========================================================
// I2C
#if 1 //&&!defined(UseInternalDDCRam)

#define Init_NVRAM_I2C_SDA_Pin()			{INIT_HWI2C_SDA_PIN();INIT_HW_VGAI2C_SDA_PIN();INIT_HW_HDMI2I2C_SDA_PIN();INIT_HW_HDMII2C_SDA_PIN();}
#define Init_NVRAM_I2C_SCL_Pin()			{INIT_HWI2C_SCL_PIN();INIT_HW_VGAI2C_SCL_PIN();INIT_HW_HDMI2I2C_SCL_PIN();INIT_HW_HDMII2C_SCL_PIN();}


#define INIT_HWI2C_SDA_PIN()	(MEM_MSWRITE_BIT(_REG_GPIO1_OEZ, TRUE, BIT2))
#define INIT_HWI2C_SCL_PIN()	(MEM_MSWRITE_BIT(_REG_GPIO1_OEZ, TRUE, BIT2))

#define hw_Set_I2C_SDA_Pin		(MEM_MSWRITE_BIT(_REG_GPIO1_OUT, TRUE, BIT2), MEM_MSWRITE_BIT(_REG_GPIO1_OEZ, FALSE, BIT2))
#define hw_Clr_I2C_SDA_Pin		(MEM_MSWRITE_BIT(_REG_GPIO1_OUT, FALSE, BIT2), MEM_MSWRITE_BIT(_REG_GPIO1_OEZ, FALSE, BIT2))
#define hw_I2C_SDA_HI                  (_bit2_(MEM_MSREAD_BYTE(_REG_GPIO1_IN)))
#define hw_I2C_SDA_LO                  (!hw_I2C_SDA_HI)


#define hw_Set_I2C_SCL_Pin		(MEM_MSWRITE_BIT(_REG_GPIO1_OUT, TRUE, BIT2), MEM_MSWRITE_BIT(_REG_GPIO1_OEZ, FALSE, BIT2))
#define hw_Clr_I2C_SCL_Pin		(MEM_MSWRITE_BIT(_REG_GPIO1_OUT, FALSE, BIT2), MEM_MSWRITE_BIT(_REG_GPIO1_OEZ, FALSE, BIT2))
#define hw_I2C_SCL_HI		       (_bit2_(MEM_MSREAD_BYTE(_REG_GPIO1_IN)))
#define hw_I2C_SCL_LO			(!hw_I2C_SCL_HI)


#define INIT_HW_VGAI2C_SDA_PIN()    		(MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, TRUE, BIT2))
#define INIT_HW_VGAI2C_SCL_PIN()    		(MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, TRUE, BIT1))

#define Set_i2c_SDA_VGA()           (MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, TRUE, BIT2))
#define Clr_i2c_SDA_VGA()           (MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, FALSE, BIT2), MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, FALSE, BIT2))
#define i2c_SDAHi_VGA()             (_bit2_(MEM_MSREAD_BYTE(_REG_PMGPIO2_IN)))
#define i2c_SDALo_VGA()             (!i2c_SDAHi_VGA())

#define Set_i2c_SCL_VGA()           (MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, TRUE, BIT1))
#define Clr_i2c_SCL_VGA()           (MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, FALSE, BIT1), MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, FALSE, BIT1))
#define i2c_SCLHi_VGA()             (_bit1_(MEM_MSREAD_BYTE(_REG_PMGPIO2_IN)))
#define i2c_SCLLo_VGA()             (!i2c_SCLHi_VGA())

#define INIT_HW_HDMII2C_SDA_PIN()    		(MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT1))
#define INIT_HW_HDMII2C_SCL_PIN()    		(MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT0))

#define Set_i2c_SDA_HDMI()           			(MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT1))
#define Clr_i2c_SDA_HDMI()           			(MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, FALSE, BIT1), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, FALSE, BIT1))
#define i2c_SDAHi_HDMI()              			(_bit1_(MEM_MSREAD_BYTE(_REG_PMGPIO1_IN)))
#define i2c_SDALo_HDMI()              			(!i2c_SDAHi_HDMI())

#define Set_i2c_SCL_HDMI()           			(MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT0))
#define Clr_i2c_SCL_HDMI()           			(MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, FALSE, BIT0), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, FALSE, BIT0))
#define i2c_SCLHi_HDMI()             				(_bit0_(MEM_MSREAD_BYTE(_REG_PMGPIO1_IN)))
#define i2c_SCLLo_HDMI()             				(!i2c_SCLHi_HDMI())


#define INIT_HW_HDMI2I2C_SDA_PIN()    	(MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT7))
#define INIT_HW_HDMI2I2C_SCL_PIN()    	(MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT6))

#define Set_i2c_SDA_HDMI2()           		(MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT7))
#define Clr_i2c_SDA_HDMI2()           			(MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, FALSE, BIT7), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, FALSE, BIT7))
#define i2c_SDAHi_HDMI2()              			(_bit7_(MEM_MSREAD_BYTE(_REG_PMGPIO1_IN)))
#define i2c_SDALo_HDMI2()              		(!i2c_SDAHi_HDMI2())

#define Set_i2c_SCL_HDMI2()           			(MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT6))
#define Clr_i2c_SCL_HDMI2()           			(MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, FALSE, BIT6), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, FALSE, BIT6))
#define i2c_SCLHi_HDMI2()             			(_bit6_(MEM_MSREAD_BYTE(_REG_PMGPIO1_IN)))
#define i2c_SCLLo_HDMI2()             			(!i2c_SCLHi_HDMI2())

#define Set_NVRAM_i2c_SDA()		      		((EnableReadDDCType==I2C_EEPROM)?hw_Set_I2C_SDA_Pin:((EnableReadDDCType==HDMI_EDID)?Set_i2c_SDA_HDMI():((EnableReadDDCType==HDMI2_EDID)?Set_i2c_SDA_HDMI2():Set_i2c_SDA_VGA())))
#define Clr_NVRAM_i2c_SDA()		              ((EnableReadDDCType==I2C_EEPROM)?hw_Clr_I2C_SDA_Pin:((EnableReadDDCType==HDMI_EDID)?Clr_i2c_SDA_HDMI():((EnableReadDDCType==HDMI2_EDID)?Clr_i2c_SDA_HDMI2():Clr_i2c_SDA_VGA())))
#define NVRAM_i2c_SDA_IS_HI()			((EnableReadDDCType==I2C_EEPROM)?hw_I2C_SDA_HI:((EnableReadDDCType==HDMI_EDID)?i2c_SDAHi_HDMI():((EnableReadDDCType==HDMI2_EDID)?i2c_SDAHi_HDMI2():i2c_SDAHi_VGA())))
#define NVRAM_i2c_SDA_IS_LO()			((EnableReadDDCType==I2C_EEPROM)?hw_I2C_SDA_LO:((EnableReadDDCType==HDMI_EDID)?i2c_SDALo_HDMI():((EnableReadDDCType==HDMI2_EDID)?i2c_SDALo_HDMI2():i2c_SDALo_VGA())))

#define Set_NVRAM_i2c_SCL()			      	((EnableReadDDCType==I2C_EEPROM)?hw_Set_I2C_SCL_Pin:((EnableReadDDCType==HDMI_EDID)?Set_i2c_SCL_HDMI():((EnableReadDDCType==HDMI2_EDID)?Set_i2c_SCL_HDMI2():Set_i2c_SCL_VGA())))
#define Clr_NVRAM_i2c_SCL()			      	((EnableReadDDCType==I2C_EEPROM)?hw_Clr_I2C_SCL_Pin:((EnableReadDDCType==HDMI_EDID)?Clr_i2c_SCL_HDMI():((EnableReadDDCType==HDMI2_EDID)?Clr_i2c_SCL_HDMI2():Clr_i2c_SCL_VGA())))
#define NVRAM_i2c_SCL_IS_HI()			((EnableReadDDCType==I2C_EEPROM)?hw_I2C_SCL_HI:((EnableReadDDCType==HDMI_EDID)?i2c_SCLHi_HDMI():((EnableReadDDCType==HDMI2_EDID)?i2c_SCLHi_HDMI2():i2c_SCLHi_VGA())))
#define NVRAM_i2c_SCL_IS_LO()			((EnableReadDDCType==I2C_EEPROM)?hw_I2C_SCL_LO:((EnableReadDDCType==HDMI_EDID)?i2c_SCLLo_HDMI():((EnableReadDDCType==HDMI2_EDID)?i2c_SCLLo_HDMI2():i2c_SCLLo_VGA())))

#endif

#if !USEFLASH
#define hwI2C_SCL_Pin       // GPIO03
#define hwI2C_SDA_Pin      // GPIO02
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

#if ENABLE_HDCP

#define hw_Set_HdcpHpd()        //(MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, FALSE, BIT0), MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, FALSE, BIT0))//(MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, FALSE, BIT5), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, FALSE, BIT5))  //(MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, FALSE, BIT0), MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, FALSE, BIT0))   
#define hw_Clr_HdcpHpd()          //(MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, TRUE, BIT0), MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, FALSE, BIT0))//(MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, TRUE, BIT5), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT5))   //(MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, TRUE, BIT0), MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, FALSE, BIT0))
#define Init_hwHDCP_Hpd_Pin()	//(MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, TRUE, BIT0), MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, FALSE, BIT0))		//

#define hw_Set_HdcpHpd2()           (MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, FALSE, BIT5), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, FALSE, BIT5))   
#define hw_Clr_HdcpHpd2()            (MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, TRUE, BIT5), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, FALSE, BIT5))
#define Init_hwHDCP_Hpd_Pin2()    (MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, TRUE, BIT5), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, FALSE, BIT5))

#define hw_Set_HdcpHpd3()         (MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, FALSE, BIT0), MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, FALSE, BIT0)) //(MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, FALSE, BIT5), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, FALSE, BIT5)) // (MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, FALSE, BIT5), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, FALSE, BIT5))  
#define hw_Clr_HdcpHpd3()           (MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, TRUE, BIT0), MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, FALSE, BIT0))// (MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, TRUE, BIT5), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, TRUE, BIT5)) // (MEM_MSWRITE_BIT(_REG_PMGPIO1_OUT, TRUE, BIT5), MEM_MSWRITE_BIT(_REG_PMGPIO1_OEZ, FALSE, BIT5))
#define Init_hwHDCP_Hpd_Pin3()  (MEM_MSWRITE_BIT(_REG_PMGPIO2_OUT, TRUE, BIT0), MEM_MSWRITE_BIT(_REG_PMGPIO2_OEZ, FALSE, BIT0))
#endif


// MHL PS_CTRL
#define SET_MHL_PS_CTRL_CHARGE0()    //(MEM_MSWRITE_BIT(_REG_PMGPIO3_OEZ, TRUE, BIT7))
#define CLR_MHL_PS_CTRL_CHARGE0()    //(MEM_MSWRITE_BIT(_REG_PMGPIO3_OUT, FALSE, BIT7), MEM_MSWRITE_BIT(_REG_PMGPIO3_OEZ, FALSE, BIT7))

#define SET_MHL_PS_CTRL_CHARGE1()    //(MEM_MSWRITE_BIT(_REG_PMGPIO3_OEZ, TRUE, BIT7))
#define CLR_MHL_PS_CTRL_CHARGE1()    //(MEM_MSWRITE_BIT(_REG_PMGPIO3_OUT, FALSE, BIT7), MEM_MSWRITE_BIT(_REG_PMGPIO3_OEZ, FALSE, BIT7))

#define SET_MHL_PS_CTRL_CHARGE2()    //(MEM_MSWRITE_BIT(_REG_PMGPIO3_OEZ, TRUE, BIT7))
#define CLR_MHL_PS_CTRL_CHARGE2()    //(MEM_MSWRITE_BIT(_REG_PMGPIO3_OUT, FALSE, BIT7), MEM_MSWRITE_BIT(_REG_PMGPIO3_OEZ, FALSE, BIT7))

//SARKEY_ENABLE_BIT
#define SAR0_EN     BIT0
#define SAR1_EN     BIT1
#define SAR2_EN     BIT2
#define SAR3_EN     BIT3
#define SARKEY_EN   (SAR1_EN|SAR2_EN)//|SAR0_EN)

#define KEYPAD_ADC_A        KEYPAD_SAR1
#define KEYPAD_ADC_B        KEYPAD_SAR2
#define AOVDV_VALUE     4

#define LVDS_CHANNEL    (MOD_PORTA|MOD_PORTB|MOD_PORTC|MOD_PORTD)//(MOD_PORTD|MOD_PORTC)//(MOD_PORTA|MOD_PORTB|MOD_PORTC|MOD_PORTD)
#define I_GEN_CH        CH3_CLK

#endif

