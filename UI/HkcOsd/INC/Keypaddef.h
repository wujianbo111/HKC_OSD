typedef enum
{
	KEY_POWER = BIT0, // power
	KEY_MENU	 = BIT1, //BIT1, // menu
	KEY_PLUS	 = BIT2, //BIT2, // right
	KEY_MINUS = BIT3, //BIT3, // left
	KEY_EXIT	 = BIT4, //BIT4, // exit/auto


	#if  (FEnterFunction==FEnter_POWER_MENU)
	KEY_FACTORY	= KEY_POWER | KEY_MENU,
	#elif (FEnterFunction==FEnter_POWER_EXIT)
	KEY_FACTORY	= KEY_POWER | KEY_EXIT,
	#endif

	KEY_NOTHING	= 0
} KeypadMaskType;


typedef enum
{
	BTN_Plus,
	BTN_Minus,
	BTN_Menu,
	BTN_Exit,
	BTN_Power,


	BTN_EndBTN,
	BTN_Repeat,



	#if Enable_Exit_LongPressKeyFunction
	BTN_ExitPressKey,
	#endif

	BTN_Nothing
} ButtonType;


//2006-02-22 #define KeypadMask (KEY_POWER|KEY_PLUS|KEY_MINUS|KEY_MENU|KEY_EXIT)

#define KeypadMask (KEY_POWER|KEY_PLUS|KEY_MINUS|KEY_MENU|KEY_EXIT)


