extern xdata BYTE KeypadButton;
#ifdef PowerKeyDeBounce
extern bit PushPowerKeyFlag;
extern BYTE xdata PushPowerKeyDeBounce;
#endif
extern BOOL Key_ScanKeypad(void);
#if (FEnterFunction==FEnter_AC_MENU)
extern void CheckFactoryKeyStatus(void);
#endif
