extern void mStar_WriteDDC1(void);
extern void mStar_WriteDDC2(void);

#if 0//def WH_REQUEST
#if TESTEDID
extern void EreaseEDID(void);
#endif
#if EnablePreLoadEDID
extern void PreLoadEDID2VGA(void);
extern void PreLoadEdid3HDMI(void);
extern void PreLoadEdid2DVI(void);
#endif
#endif

#ifdef ReduceDDC
extern void mStar_InitDDC(void);
extern void mStar_CheckRAM(void);

#endif

extern void mStar_ClrDDC_WP(void); //2017/02/20
extern void mStar_SetDDC_WP(void);
extern void mStar_InitDDC(void);

#if WriteSN_Functiom_New
extern void ReLoadEDIDtoAddSN(void);
#endif

#if LoadAllPortSeriealnumberByOneVGAPort
extern void ReLoadEDIDtoAddSN(void);
#endif





