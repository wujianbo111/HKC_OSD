#ifdef _MSTAR_C_
#define _MSTARDEC_
#else
#define _MSTARDEC_  extern
#endif

#define BW_SCREEN_OFF   0
#define BW_SCREEN_WHITE 1
#define BW_SCREEN_BLACK 2

_MSTARDEC_ BYTE xdata iGenTuningFinished;
_MSTARDEC_  void  SettingInputColorimetry(void);
_MSTARDEC_  BYTE  IsColorspaceRGB(void);
_MSTARDEC_ void mStar_EnableModeChangeINT(Bool u8Enable);
_MSTARDEC_ void mStar_BlackWhiteScreenCtrl(BYTE u8Ctrl);
_MSTARDEC_ Bool mStar_SetCaptureWindow( void );
extern void mStar_Init(void);
//extern void mStar_ACOnInit(void);
extern Bool mStar_SetupMode(void);
extern void mStar_SetupFreeRunMode(void);
extern void mStar_PrepareForTimingChange(void);
extern void mStar_SetupInputPort(void);
extern void mStar_SetAnalogInputPort( Bool ToSOGPort );
extern void mStar_PowerDown(void);
extern void mStar_PowerUp(void);
extern void ScalerReset(void);
extern Bool mStar_SetPanelTiming(void);

//extern void CheckADC(void); // check DVI phase overflow
#if HotInputSelect
extern void mStar_PowerUp(void);
#endif
extern void SetPWMFreq(WORD freq);
extern void GPIOPWMSelect(void);
#ifdef ReduceDDC
extern void InitVccDetectPin(void);
extern void SystemVccOK(void);
extern void ScalerResetThenPowerDown(void);
extern void ScalerIntoDeepPowerDown(void);
#endif

#if (CHIP_ID==CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF)
_MSTARDEC_ void msTrimFROFromEfuse(void);
#if (ENABLE_XTAL_LESS)
_MSTARDEC_ Bool msStartRCOSC432MCal(void);
#endif
#endif


