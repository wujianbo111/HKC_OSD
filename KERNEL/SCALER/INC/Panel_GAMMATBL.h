
#ifndef _GAMMATBL_H
#define _GAMMATBL_H
#if (PanelType==PanelLM220WE1)
#include "Gama_PanelLM220WE1.h"
//#elif(PanelType==PanelLTM230HT03)
//#include "Gama_PanelLTM230HT03.h"
#elif (PanelType == PanelLM230WF5TLD1)
#include  "Gama_PanelLM230WF5TLD1.h"
//#elif (PanelType==PanelTPM215HW01_HGE)      //110828 Rick add
//#include "Gama_PanelTPM215HW01_HGE.h"
#elif (PanelType==PanelM236H3LA3)
#include "Gama_PanelM236H3LA3.h"
#elif (PanelType==PanelLM275WF5)
#include "Gama_PanelLM275WF5.h"
#elif (PanelType==PanelBM190WX2)
#include "Gama_PanelBM190WX2.h"
#elif (PanelType==PanelLM185WH2)
#include "Gama_PanelLM185WH2.h"
#elif (PanelType==PanelAUOM240HW01VD)
#include "Gama_PanelAUOM240HW01VD.h"
#elif (PanelType==PanelBM215WF4)	//120112 by Bian
#include "Gama_PanelBM215WF4.h"
#elif (PanelType==PanelLM215WF3_S2A2)
#include "Gama_PanelLM215WF3_S2A2_.h"
#elif (PanelType==PanelBM230WF3_SJC2)
#include "Gama_PanelBM230WF3_SJC2_.h"
#elif (PanelType==PanelLM230WF5_T2F2)	//120417 Modify
#include "Gama_PanelLM230WF5_T2F2_.h"
#elif (PanelType==PanelLM215WF7_S2Z2) //120503 Modify
#include "Gama_PanelLM215WF7_S2Z2.h"
#elif (PanelType==PanelLM230WFA_S2Z4) //120503 Modify
#include "Gama_PanelLM230WFA_S2Z4.h"
#elif (PanelType==PanelLM270WF6_S2Z4) //120503 Modify
#include "Gama_PanelLM270WF6_S2Z4.h"
#elif (PanelType==PanelLM275WF5_S2A2)	//120503 Modify
#include "Gama_PanelLM275WF5_S2A2_.h"
#elif (PanelType==PanelBM200WD3_TJC1)	//120516 Modify
#include "Gama_PanelBM200WD3_TJC1.h"
#elif (PanelType==PanelLM190E09)	//120816 bian
#include "Gama_PanelLM190E09.h"
#elif (PanelType==PanelCMIM195FGE)	//120816 bian
#include "Gama_PanelCMIM195FGE.h"
#elif (PanelType==PanelBM230WF5_TJC3)	//120816 bian
#include "Gama_PanelBM230WF5_TJC3.h"
#elif (PanelType==PanelTPM215HW01HGJL02)	//120911 bian
#include "Gama_PanelTPM215HW01HGJL02.h"
#elif  ( PanelType==PanelHR215WU1)
#include "Gama_PanelHR215WU1.h"
#elif  ( PanelType==PanelHR215WU1_120)
#include "Gama_PanelHR215WU1_120.h"
#elif   PanelType==PanelLM240WU8_SLD1
#include "Gama_PanelLM240WU8_SLD1.h"
#elif   PanelType==PanelLTM240CT07
#include "Gama_PanelLTM240CT07.h"
#elif PanelType==PanelM280HKJ_L30
#include "Gama_PanelM280HKJ_L30.h"
#elif( PanelType==PanelM280HKJ_L30_VER32|| PanelType==PanelM280HKJ_L50_VER10) //GYP20150824
#include "Gama_PanelM280HKJ_L30.h"
#elif (PanelType==PanelAUOM240HW01V8||PanelType == PanelAUOM240HW01V80A||PanelType == PanelAUOM240HW01V80B)	//120911 bian
#include "Gama_PanelAUOM240HW01V8.h"
#elif (PanelType == PanelLTM270DL06)//petit  20130626
#include "Gama_PanelSAM27_LTM270DL06_QHD_60HZ.h"
#elif (PanelType == PanelLM250WQ1_S2A2)
#include "Gama_PanelSAM27_LTM270DL06_QHD_60HZ.h"
#elif (PanelType == PanelAUOM270DTN01_1||PanelType == PanelHSMB238_1DAN01||PanelType == PanelHSMB238_2DAN01)
#include "Gama_PanelAUOM270DTN01_1.h"
#elif (PanelType == Panel32W_BOEHV320QHM_C80)
#include "Gama_PanelAUOM270DTN01_1.h"
#elif (PanelType==PanelBM230WF5_T2G2)	//petit 20121121
#include "Gama_PanelBM230WF5_T2G2_.h"
#elif (PanelType==PanelTPM220Z1_ZGEL02)	//petit 20121122
#include "Gama_PanelTPM220Z1_ZGEL02.h"
#elif (PanelType==PanelTPM236H3_WU3110)	//petit 20121210
#include "Gama_TPM236H3_WU3110.h"
#elif (PanelType==PanelTPM236H3HGJL02)	//petit 20121210
#include "Gama_TPM236H3HGJL02.h"
#elif (PanelType==PanelTPM195WD1)	//120516 Modify
#include "Gama_PanelTPM195WD1.h"
#elif (PanelType==PanelAUOM240HW02V7)	//petit 20121211
#include "Gama_PanelAUOM240HW02V7.h"
#elif (PanelType==PanelBM230WF3_S2K2)
#include "Gama_PanelBM230WF3_S2K2.h"
#elif (PanelType==PanelAUOM240HTN01_2)	//petit 20130130
#include "Gama_PanelAUOM240HW02V7.h"
#elif (PanelType==PanelLM230WF3_SLK1)
#include "Gama_PanelLM230WF3_SLK1.h"
#elif (PanelType==PanelLM230WF3_S2L1)//Gino 20141023
#include "Gama_PanelLM230WF3_SLK1.h"
#elif (PanelType==PanelLM230WF3_S2LC)//20150916 YANPING.GUO
#include "Gama_PanelLM230WF3_SLK1.h"
#elif (PanelType==PanelLM215WF3_S2L1)//Gino 20141027
#include "Gama_PanelLM230WF3_SLK1.h"
#elif (PanelType==PanelLM215WF3_S2LC)//Gino 20141027
#include "Gama_PanelLM215WF3_S2LC.h"
#elif (PanelType==PanelLM215WF3_S3L1||PanelType==PanelLM215WF9_S1A3 )//Gino 20150126
#include "Gama_PanelLM230WF3_SLK1.h"
#elif (PanelType==PanelLM230WF3_S3L2)//GYP 20150126
#include "Gama_PanelLM230WF3_SLK1.h"
#elif (PanelType==PanelTPM207WF1_FHBN20)//Gino 20150126
#include "Gama_PanelLM230WF3_SLK1.h"
#elif (PanelType==PanelLM230WF3_SLN1)//Gino 20140516
#include "Gama_PanelLM230WF3_SLN1.h"
#elif (PanelType == PanelHR236WU1)
#include "Gama_PanelHR236WU1.h"
#elif (PanelType==PanelBM230WF5_TAE2)//petit 20130205
#include "Gama_PanelBM230WF3_S2K2.h"
#elif (PanelType==PanelLTM230HL08)//20140708 Gino
#include "Gama_PanelBM230WF3_S2K2.h"
#elif (PanelType==PanelTPM185B1_WX3401)//20140708 Gino
#include "Gama_PanelBM230WF3_S2K2.h"
#elif (PanelType==PanelTPM185WH2_WHBN10K)//yanping
#include "Gama_PanelTPM185WH2_WHBN10K.h"
#elif (PanelType==PanelMV238FHM_N10)//20141008 Gino
#include "Gama_PanelBM230WF3_S2K2.h"
#elif (PanelType==PanelLM250WF5_S2A2)
#include "Gama_PanelBM230WF3_S2K2.h"
#elif (PanelType==PanelLM250WF5_S2B2)
#include "Gama_PanelBM230WF3_S2K2.h"
#elif (PanelType==PanelTPM236H3_HL01)
#include "Gama_PanelBM230WF3_S2K2.h"
#elif (PanelType==PanelTPVSDC27|| PanelType==PanelTPVSDC23)
#include "Gama_PanelBM230WF3_S2K2.h"
#elif (PanelType==PanelCMIM270HGEL20)//petit 20130303
#include "Gama_PanelLM270WF6_S2Z4.h"
#elif (PanelType==PanelAUOM270HW01V2)//petit 20130303
#include "Gama_PanelLM270WF6_S2Z4.h"
#elif (PanelType==PanelTPM240WF1_HTN01)//20130410
#include "Gama_PanelAUOM240HW02V7.h"
#elif (PanelType==PanelTPM215HW01HTN01)//20130422
#include "Gama_PanelTPM215HW01HTN01.h"
#elif (PanelType==PanelTPM215HW01_HTN01_REV10CF)//20141213 Gino
#include "Gama_PanelTPM215HW01HTN01.h"
#elif (PanelType==PanelTPM215HW01HTN0110CF)//xuebo add new model 20140604
#include "Gama_PanelTPM215HW01HTN0110CF.h"
#elif (PanelType==PanelTPM270WF1_MWN1)//20130512
#include "Gama_PanelLM270WF6_S2Z4.h"
#elif (PanelType==PanelIVOM270MWN1)//20130516
#include "Gama_PanelLM270WF6_S2Z4.h"
#elif (PanelType==PanelTPM240WF1_HW01)//Jun 20130619
#include "Gama_PanelTPM240WF1_HW01.h"
#elif (PanelType==PanelAUOM190ETN01)// bian 20130701
#include "Gama_PanelAUOM190ETN01_HW01.h"
#elif (PanelType==PanelAUOM170ETN01)// Jun 20130730
#include "Gama_PanelAUOM170ETN01.h"
#elif (PanelType==PanelCMIM190CGE_L20)// bian 20130701
#include "Gama_PanelCMIM190CGE_L20.h"
#elif (PanelType==PanelAUOM270HTN01)//petit 20130712
#include "Gama_PanelAUOM240HW02V7.h"
#elif (PanelType==PanelINXM270HGE)//Gino 20140520
#include "Gama_PanelAUOM240HW02V7.h"
#elif (PanelType==PanelAUOM270HTN02)//fay 20131119
#include "Gama_PanelAUOM240HW02V7.h"
#elif (PanelType==PanelAUOT215HVN01_1)	//130826 xiandi
#include "Gama_PanelAUOT215HVN01_1.h"
#elif (PanelType==PanelTPM236H3_WU3100)	//130925 bian
#include "Gama_PanelTPM236H3_WU3100.h"
#elif (PanelType==PanelCMIM215HGE_L21)	//bian 20140104
#include "Gama_PanelCMIM215HGE_L21.h"
#elif (PanelType==PanelTPM236H3_WU3101)	//140106 bian
#include "Gama_PanelTPM236H3_WU3101.h"
#elif (PanelType==PanelTPM236H3_WU3101_REV4950)
#include "Gama_PanelTPM236H3_WU3101_REV4950.h"
#elif (PanelType==PanelTPM236WF1)
#include "Gama_PanelTPM236WF1.h"
#elif (PanelType==PanelTPM236H3L02)//20140103
#include "Gama_PanelTPM236H3L02.h"
#elif   PanelType==PanelLTM240CL04
#include "Gama_PanelLTM240CL04.h"
#elif   PanelType==PanelCMIM195FGE_L20||PanelType==PanelM195RTN01_V00H
#include "Gama_PanelCMIM195FGE_L20.h"
#elif (PanelType==PanelAUOM215HTN01||PanelType==PanelAUOM215HTN01_1)
#include "Gama_PanelAUOM215HTN01.h"
#elif (PanelType==PanelTPM215HW01_DAT01||PanelType==PanelTPM215HW01_DAT03||PanelType==PanelTPM215HW01_DAT01_R10R||PanelType==PanelTPM215HW01HTN0110CF_1)	//petit 20131222
#include "Gama_PanelTPM215HW01HGJL02.h"
#elif(PanelType==PanelTPM215HW01_HGEL02_TC1J)||(PanelType==PanelM215HTN01_V1)||(PanelType==PanelM215HAN01)||(PanelType==PanelMV236FH8)||(PanelType==PanelLSM236HP04_M01)
#include "Gama_PanelTPM215HW01HGJL02.h"
#elif(PanelType==PanelTPM215HW01_HGEL02) //yanping
#include "Gama_PanelTPM215HW01_HGEL02.h"
#elif(PanelType==PanelTPM215HW01_HGEL03||PanelType==PanelM238HV_V00000A)
#include "Gama_PanelTPM215HW01_HGEL03.h"
#elif (PanelType==PanelAUOM270HVN02)	//petit 20131222
#include "Gama_PanelAUOM240HW01V8.h"
#elif (PanelType==PanelLM270WF7_SSA1)
#include "Gama_PanelLM270WF7_SSA1.h"
#elif (PanelType==PanelTPM240WF1_HTN01_20FA)
#include "Gama_PanelAUOM240HW02V7.h"
#elif (PanelType==PanelTPM215WF1_WU3201)
#include "Gama_PanelTPM215WF1_WU3201.h"
#elif (PanelType==PanelTPM236H3_WU3101_REV4970)//20140826
#include "Gama_PanelHR236WU1.h"
#elif (PanelType==PanelM185B1WX3401K||PanelType==PanelTPM185WH2_N10_K)//20140922
#include "Gama_PanelTPM185B1WX3401K.h"
#elif (PanelType == PanelHR236WU1_310)
#include "Gama_PanelHR236WU1_310.h"
#elif (PanelType == PanelTPM236WF1_WU3301)
#include "Gama_PanelTPM236WF1_WU3301.h"
#elif (PanelType == PanelTPM236WF1_HJJP02)
#include "Gama_PanelTPM236WF1_HJPP02.h"
#elif (PanelType == PanelTPM215WF1_HJJP02)
#include "Gama_PanelTPM236WF1_HJPP02.h"
#elif (PanelType == PanelLTM270HP01)
#include "Gama_PanelLTM270HP01.h"
#elif (PanelType == PanelTPM236WF1_WU3301K_4831)
#include "Gama_PanelTPM236WF1_WU3301K_4831.h"
#elif (PanelType == PanelTPM236WF1_WU3301K_4832)
#include "Gama_PanelTPM236WF1_WU3301K_4832.h"
#elif (PanelType == PanelLM230WF3_S3L1 || PanelType == PanelLM230WF3_S3L1_VER01 || PanelType == PanelLM230WF3_S3L1_VER04|| PanelType == PanelLM230WF3_S3L1_Rev221)
#include "Gama_PanelLM230WF3_S3L1.h"
#elif (PanelType == PanelTPM236WF1_HJPP02_SC3G)
#include "Gama_PanelTPM236WF1_HJPP02_SC3G.h"
#elif (PanelType==PanelMV238FHM_N10_23P8)//20150104 Alpha
#include "Gama_PanelMV238FHM_N10_23P8.h"
#elif (PanelType==PanelM236HJJSUFFIX_L31)||(PanelType==PanelLSC490HN03)||(PanelType==PanelMV270FHM_N20)||(PanelType==PanelM270HVN02_1)
#include "Gama_PanelM236HJJSUFFIX_L31.h"
#elif (PanelType==PanelHSM270EB_300)
#include "Gama_PanelHSM270EB_300.h"
#elif (PanelType==PanelLM238WF2_S2H2)//20150203 Alpha
#include "Gama_PanelLM230WF3_SLK1.h"
#elif (PanelType == PanelAUOM320DVN01_0) //20150225 Alpha
#include "Gama_PanelAUOM320DVN01_0.h"
#elif (PanelType==PanelTPM215HW01DAT01)//20150310 Alpha
#include "Gama_PanelBM230WF3_S2K2.h"
#elif (PanelType==PanelM170ETN01)||(PanelType==PanelM215HJJ_N20)
#include "Gama_PanelBM230WF3_S2K2.h"
#elif (PanelType==PanelTPM270WF1_WU3300)//20150322 Alpha
#include "Gamma_PanelTPM270WF1_WU3300.h"
#elif ( PanelType	== PanelTPM270WF1_FHBN10)//20160115 yangping
#include "Gamma_PanelTPM270WF1_WU3300.h"
#elif (PanelType==PanelTPM236H3HGEL02)//20140103
#include "Gama_PanelTPM236H3HGEL02.h"
#elif (PanelType==PanelLM270WF5_S3A1 ||PanelType==PanelM270HTN02_V1)//20140103
#include "Gama_PanelLM270WF5_S3A1.h"
#elif (PanelType==PanelM270HTN02_V6 ||PanelType==PanelTPM238WF1FHBN10K || PanelType == PanelLM230HT11|| PanelType == PanelM236HJJ_P02)//20150625
#include "Gama_PanelTPM238WF1FHBN10K.h"
#elif (PanelType==PanelHSMB245_1HTN01||PanelType==PanelMV238FHM_N30)//20150625
#include "Gama_PanelHSMB245_1HTN01.h"
#elif (PanelType==PanelHSMB238_1DAN01||PanelType==PanelHSMB238_2DAN01)//20150625
#include "Gama_PanelHSMB238_1DAN01.h"
#elif (PanelType==PanelM200HJJ_L20)
#include "Gama_PanellM200HJJ_L20.h"
#elif (PanelType==PanelLM270WF5_S3AA)////20151207 Alpha
#include "Gama_PanelLM270WF5_S3AA.h"
#elif (PanelType==PanelLM270WF5_S3A2)////20151207 Alpha
#include "Gama_PanelLM270WF5_S3A2.h"
#elif (PanelType==PanelMV270QHB_N20)////20151207 Alpha
#include "Gama_PanelMV270QHB_N20.h"
#else
#message "Please Panel Gamma Table!"
#endif

#if USE_NORMAL_GAMMA_TBL	//120112 Modify

code BYTE *tAllGammaTab[][3] =
{
	// 22
	{
		tblGamma22_RN,
		tblGamma22_GN,
		tblGamma22_BN,
	},
	//	20
	{
		tblGamma20_RN,
		tblGamma20_GN,
		tblGamma20_BN,
	},
	//  24
	{
		tblGamma24_RN,
		tblGamma24_GN,
		tblGamma24_BN,
	},
};

#else	//120112 Modify

code BYTE *tAllGammaTab[][6] =
{
	// 22
	{
		tblGamma22_RN, tblGamma22_RN_2,
		tblGamma22_GN, tblGamma22_GN_2,
		tblGamma22_BN, tblGamma22_BN_2
	},
	//	20
	{
		tblGamma20_RN, tblGamma20_RN_2,
		tblGamma20_GN, tblGamma20_GN_2,
		tblGamma20_BN, tblGamma20_BN_2
	},
	//  24
	{
		tblGamma24_RN, tblGamma24_RN_2,
		tblGamma24_GN, tblGamma24_GN_2,
		tblGamma24_BN, tblGamma24_BN_2
	},
};

#endif


#endif
