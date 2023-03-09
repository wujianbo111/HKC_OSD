/******************************************************************************
 Copyright (c) 2008 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: CapactiveKeypad.h
 [Date]:        12-May-2008
 [Comment]:
   Capactive Keypad control header file.
 [Reversion History]:
*******************************************************************************/
#ifndef _CAPACTIVEKEYPAD_ENE_H_
#define _CAPACTIVEKEYPAD_ENE_H_



//#define ENABLE_POWERLED_CONTROL     0
//#define TOUCH_KEY_CTRL_LED  0
//#define KeyLed_POWER_ORANGE    1


//
#define SB358X_HOST
#define SB358x_SMBus_addr       		0x80        //SB358x SMBus device address.
#define SB358x_write_word_cmd   	0x00        //SB358x SMBus write word command.
#define SB358x_write_byte_cmd   		0x01        //SB358x SMBus write byte command.   
#define SB358x_read_byte_cmd    		0x81        //SB358x SMBus read  byte command.   
#define SB358x_write_cmd   			0x00        //SB358x SMBus write byte command. 
#define SB358x_read_cmd    			0x80        //SB358x SMBus read  byte command.

#define PWM_Base_Clock                      	0xBA        //set PWM base clock= (1/6MHz)*0xBA= 32KHz.
#define PWM_cycle_length                 	0xFF        //set PWM cycle length= 256cycles, so PWM clock= 1/[(1/32KHz)*256]= 125Hz.
#define PWM_DutyCycle_OFF               	255         //OFF duty cycle.
#define PWM_DutyCycle_20        		200         //50% PWM duty cycle.
#define PWM_DutyCycle_50        		128         //50% PWM duty cycle.
#define PWM_DutyCycle_100       		0           //100% PWM duty cycle.

//*******************ENE LED  Type********************************
#define ENE_LED_GPIO				1
#define ENE_LED_LEVEL			2
//**************************************************************
#ifndef ENE_LED_TYPE//stone 20141124
#define ENE_LED_TYPE  ENE_LED_GPIO
#endif

// Definition of SB357x SMBUS commands
#define PWM_LED_ON_CMD           0x01
#define PWM_LED_OFF_CMD          0x02
#define GPIO_LED_HIGH_CMD        0x03
#define PWM_LEVEL_OFF_CMD        0x03
#define GPIO_LED_LOW_CMD         0x04
#define PWM_LEVEL_ON_CMD         0x05
#define PWM_BLINK_ON_CMD         0x06
#define PWM_BLINK_OFF_CMD        0x07
#define PWM_CLEAR_INT_CMD        0x08


//*******************ENE KEY  Type********************************
#define SB358X			1
#define SB357X			2
//**************************************************************
#ifndef ENE_IC_TYPE//stone 20141202
#define ENE_IC_TYPE  SB358X
#endif


extern  Bool ENE_I2C_ReadByte(WORD wAddr, BYTE *buffer );
extern void ENE_I2C_WriteByte(WORD wAddr, BYTE ucValue);
extern Bool appCapkeyEneReadTbl(BYTE ucAddrH, BYTE ucAddrL, BYTE* buffer, BYTE ucBufLen);
extern void ENE_I2C_WriteBlock(WORD wAddr, BYTE ucBufLen, BYTE* buffer);

#if ENE_LED_TYPE == ENE_LED_GPIO
extern void GPIO_Init(WORD GPIOPort, WORD GPIOOutput);
extern void GPIO_LED_ON(WORD GPIOOutput);
extern void GPIO_LED_OFF(WORD GPIOOutput);
#else
extern void PWM_LED_LEVEL_Setting(BYTE ucLevel);
extern void PWM_LED_LEVEL_ON(WORD PWMPort);
extern void PWM_LED_LEVEL_OFF(WORD PWMPort);
#endif


extern void appRegInit( void );		//Stone
extern BYTE appGetI2CKeypadStatus( void );

extern void appCheckEneESD( void ) ;

extern void TurnOffLED(void);
//extern void TurnOnLED(void);
extern void TurnonGREENLED(void);
extern void TurnonAMBERLED(void);



#endif

