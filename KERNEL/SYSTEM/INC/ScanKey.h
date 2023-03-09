
#if Scan_Source==Cypress

#define OT_ADDR_Default         0x00 // brand-new chip
#define WriteFail       0x78
#define ReadFail        0x87
// read 2-byte at one time
/*
#define SK_Power    0x1000
#define SK_Plus         0x0004
#define SK_Minus        0x0008
#define SK_Menu         0x0002
#define SK_Mask     (SK_Power|SK_Plus|SK_Minus|SK_Menu)
*/

// read 1-byte at one time
#if MainBoardType==MainBoard_715G3329_A2
#ifdef TSUMXXNX
#define SK_Power   			0x10
#define SK_Exit     		0x04
#define SK_Plus       		0x01
#define SK_Minus     		0x02
#define SK_Menu     		0x08
#else
#define SK_Power   			0x10
#define SK_Exit     		0x08
#define SK_Plus       		0x04
#define SK_Minus     		0x02
#define SK_Menu     		0x01
#endif
#define ButtonAddress       0x89
#elif MainBoardType==MainBoard_712G3244_2
#define SK_Power   			0x10
#define SK_Exit     		0x04
#define SK_Plus       		0x01
#define SK_Minus     		0x02
#define SK_Menu     		0x08
#define ButtonAddress       0x89
#elif MainBoardType==MainBoard_715G3289_C2
#define SK_Power   		0x01
#define SK_Exit     		0x04
#define SK_Plus       		0x00
#define SK_Minus     		0x00
#define SK_Menu     		0x02
#define ButtonAddress       0x88
#define SliderAddress       0x8B
#define SliderMinusMaxValue        0x31 // 0~0x31 minus
#define SliderPlusMaxValue          0x64 // 0x32~0x64 plus 
#define SliderFingerOff     0x65
#elif MainBoardType==MainBoard_715G3598_M0A
#ifdef TSUMXXNX
#define SK_Power   			0x04
#define SK_Exit     		 	0x10
#define SK_Plus       			0x08
#define SK_Minus     			0x01
#define SK_Menu     			0x02
#else
#define SK_Power      		0x04//0x10
#define SK_Exit     			0x10//0x08 // up
#define SK_Plus       		0x08//0x04 // right
#define SK_Minus    		0x02 // left
#define SK_Menu     		0x01 // down    
#endif
#define ButtonAddress       	0x89

#elif MainBoardType==MainBoard_715G3598_1PLL
#define SK_Power      		0x04//0x10
#define SK_Exit     			0x10//0x08 // up
#define SK_Plus       		0x08//0x04 // right
#define SK_Minus    		0x01 // left
#define SK_Menu     		0x02 // down    
#define ButtonAddress       	0x89

#elif MainBoardType==MainBoard_715G3603_M0A
#define SK_Power   			0x04
#define SK_Exit     		 	0x10
#define SK_Plus       			0x08
#define SK_Minus     			0x01
#define SK_Menu     			0x02
#define ButtonAddress       	0x89

#elif MainBoardType==MainBoard_715G3244_TSUMU18NR || MainBoardType == MainBoard_715G3959_T		//110623 Modify
#define SK_Power   		0x10
#define SK_Exit     		       0x04
#define SK_Plus       		0x01
#define SK_Minus     		0x02
#define SK_Menu     		0x08

#define ButtonAddress       0x89

#else
#define SK_Power   		0x04//0x10
#define SK_Exit     		0x10//0x08 // up
#define SK_Plus       		0x08//0x04 // right
#define SK_Minus     		0x02 // left
#define SK_Menu     		0x01 // down
#define ButtonAddress       0x89
#endif



/*
#if MainBoardType	== MainBoard_715G3598_M0A
#define SK_Power   		0x10
#define SK_Exit     		0x08 // up
#define SK_Plus       		0x04 // right
#define SK_Minus     		0x02 // left
#define SK_Menu     		0x01 // down
#elif MainBoardType == MainBoard_715G3603_M0A
#define SK_Power   		0x04//0x10
#define SK_Exit     		0x10//0x08 // up
#define SK_Plus       		0x08//0x04 // right
#define SK_Minus     		0x02 // left
#define SK_Menu     		0x01 // down
#endif
*/

#define SK_Delay                3
#define SK_ResetDelay       50

#ifdef EnableSlider
#define SKPollingInterval   10
#else
#define SKPollingInterval   20
#endif

#define SKKeyError             100

typedef enum
{

	SKCase_SetButtonAddress,
	SKCase_ReadButton,
	SKCase_SetSliderAddress,
	SKCase_ReadSlider,

} SKReadCaseCntType;

typedef enum
{
	SKLEDBright_Off,
	SKLEDBright_Dark,
	SKLEDBright_Light,
	SKLEDBright_Light_Immediately, // 091012
} SKLEDBrightType;

extern void ScanKey_LEDBrightAction(void);

#else
#define InputSelectLed	BIT4     // 3
#define MenuLed			BIT1     // 6
#define PlusLed			BIT0
#define MinsLed			BIT6     // 1
#define GreenLed		       BIT2 //|BIT3      // 4		// Van 20070927   11:30
#define AmberLed		BIT3		//7				// Van 20070927   11:30
#define ExitLed                  BIT5

#endif

typedef enum
{
	KB_Mute,
	KB_1500Hz,
	KB_2000Hz,
	KB_3000Hz,
	KB_Nums
} KeyBuzzerFrequencyType;





extern void ScanKey_Init(void);
extern BYTE ScanKey_GetKeypadStatus(void);
extern BYTE ScanKey_FactoryKey(void);
extern void Buzzer_PWMfreq(void);

//extern BYTE ScanKey_GetLedStatus(void);

extern void ScanKey_SetLedStatus(BYTE LEDstatus);
//extern void Scan_KeyBuzzer(BYTE ucType);
//extern void Scan_KeyBuzzerHander(void);

extern void KeyLED_TurnOn(void);
extern void KeyLED_TurnOff(void);



#define OT_ADDR							0x58





