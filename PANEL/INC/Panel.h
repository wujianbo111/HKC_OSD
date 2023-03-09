#include "Board.h"
#if 1
	#if (PanelType==PanelCMOL201L01)
	    #include "PanelCMOL201_L01.h"  
	#elif (PanelType==PanelCMO190)
	    #include "PanelCMO190.h"
	#elif (PanelType==PanelCMO190W)
	    #include "PanelCMO190W.h"
	#elif (PanelType==PanelHSD170MGW1)
	    #include "PanelHSD170MGW1.h"
	#elif (PanelType==PanelCMOM220Z1_L03)
	    #include "PanelCMOM220Z1_L03.h"
	#elif (PanelType==PanelLTM190M2)
	    #include "PanelLTM190M2.h"
	#elif (PanelType==PanelCLAA201WA04)
	    #include "PanelCLAA201WA04.h"
	#elif (PanelType==PanelM190A1L02)
	    #include "PanelCMOM190A1L02.h"
	#elif (PanelType==PanelCLAA220WA01)
	    #include "PanelCLAA220WA01.h"
	#elif (PanelType==PanelCLAA220WA02)
	    #include "PanelCLAA220WA02.h"
	#elif (PanelType==PanelLTM220M1L01)
	    #include "PanelLTM220M1L01.h"
	#elif (PanelType==PanelHSD190MEN3_A00)
	    #include "PanelHSD190MEN3_A00.h"
	#elif (PanelType==PanelCLAA170WA02)
	    #include "PanelCLAA170WA02.h"
	#elif (PanelType==PanelM190Z1L01)
	    #include "PanelM190Z1L01.h"
	#elif ( PanelType  == PanelM156B1L01) 
	    #include "PanelM156B1L01.h"
	#elif ( PanelType == PanelHSD170MGW1 )
		#include "PanelHSD170MGW1.h"
	#elif ( PanelType 	== PanelCLAA170EA07P )
	      #include "PanelCLAA170EA07P.h"
	#elif ( PanelType 	== PanelCMOM220Z1_PS3 )//Amy2007.12.26   18:51:54
	      #include "PanelCMOM220Z1_PS3.h"
	#elif ( PanelType 	== PanelCMO220Z1M01 )//Amy2007.12.26   18:51:54
	      #include "PanelCMO220Z1M01.h"
	#elif ( PanelType 	== PanelCLAA185WA01 )
	      #include "PanelCLAA185WA01.h"
	#elif ( PanelType 	== PanelSVA156WX1 )
	      #include "PanelSVA156WX1.h"
	#elif ( PanelType 	== PanelM185B1L01 )
	      #include "PanelM185B1L01.h"
	#elif ( PanelType 	== PanelLM190E08 )
	      #include "PanelLM190E08.h"
	#elif ( PanelType 	== PanelM216H1L01 )
	      #include "PanelM216H1L01.h"
	#elif ( PanelType 	== PanelHT190WG1 )
	      #include "PanelHT190WG1.h"
	#elif ( PanelType 	== PanelLM185WH1TLA1 )
	      #include "PanelLM185WH1TLA1.h"
	#elif ( PanelType 	== PanelLTM230HT01 )
	      #include "PanelLTM230HT01.h"
	#elif ( PanelType 	== PanelLTM230HL08)//20140708 Gino
	      #include "PanelLTM230HL08.h"
	#elif ( PanelType 	== PanelTPM185B1_WX3401)//20140708 Gino
	      #include "PanelTPM185B1_WX3401.h"
    #elif ( PanelType 	== PanelTPM185WH2_WHBN10K)//yanping 20160311
	      #include "PanelTPM185WH2_WHBN10K.h"	  
	#elif ( PanelType 	== PanelLM230HT11)//20140708 Gino
	      #include "PanelLM230HT11.h"
        #elif (PanelType 	==PanelM236HJJ_P02)
		#include "PanelM236HJJ_P02.h"
#elif (PanelType 	==PanelM270HTN02_V6)
		#include "PanelM270HTN02_V6.h"	
#elif (PanelType 	==PanelM195RTN01_V00H)
		#include "PanelM195RTN01_V00H.h"	
#elif (PanelType 	==PanelM215HTN01_V1)
		#include "PanelM215HTN01_V1.h"	
#elif (PanelType 	==PanelLSC490HN03)
		#include "PanelLSC490HN03.h"			
#elif (PanelType==PanelM215HAN01)
		#include "PanelM215HAN01.h"
#elif (PanelType 	==PanelM238HV_V00000A)
		#include "PanelM238HV_V00000A.h"	
#elif (PanelType 	==PanelM270HTN02_V1)
		#include "PanelM270HTN02_V1.h"			
#elif (PanelType==PanelMV236FH8)
		#include "PanelMV236FH8.h"
#elif (PanelType==PanelLSM236HP04_M01)
		#include "PanelLSM236HP04_M01.h"		
        #elif (PanelType 	==PanelMV238FHM_N30)
		#include "PanelMV238FHM_N30.h"
        #elif (PanelType 	==PanelHSMB245_1HTN01)
		#include "PanelHSMB245_1HTN01.h"
	#elif (PanelType==PanelHSMB238_1DAN01)
	      #include "PanelHSMB238_1DAN01.h"
	#elif (PanelType==PanelHSMB238_2DAN01)
	      #include "PanelHSMB238_2DAN01.h"
	#elif ( PanelType 	== PanelMV238FHM_N10)//20141008 Gino
	      #include "PanelMV238FHM_N10.h"
	#elif ( PanelType	== PanelLM250WF5_S2A2)
		  #include "PanelLM250WF5_S2A2.h"
	#elif ( PanelType	== PanelLM250WF5_S2B2)
		  #include "PanelLM250WF5_S2B2.h"
	#elif ( PanelType	== PanelTPM236H3_HL01)
	  	  #include "PanelTPM236H3_HL01.h"
	#elif ( PanelType	== PanelTPVSDC27)
	  	  #include "PanelTPVSDC27.h"
    #elif ( PanelType	== PanelTPVSDC23)
	      #include "PanelTPVSDC23.h"
	#elif ( PanelType 	== PanelLM230WF1TLA3 )
	      #include "PanelLM230WF1TLA3.h"
	#elif ( PanelType 	== PanelCMOM236H1L01 )
	      #include "PanelCMOM236H1L01.h"
	#elif ( PanelType 	== PanelLM220WE1 )
	      #include "PanelLM220WE1.h"
	#elif (PanelType == PanelAUOM240HW01V0)
    	  #include "PanelAUOM240HW01V0.h"    
	#elif (PanelType==PanelAUOM185XW01)
    	  #include "PanelAUOM185XW01.h"    
	#elif (PanelType==PanelTPM215HW01)
         #include "PanelTPM215HW01.h"
       #elif (PanelType == PanelCMOM200O1L02)
         #include "PanelCMOM200O1L02.h"
        #elif (PanelType == PanelAUOM215HW01L07)
         #include "PanelAUOM215HW01L07.h"         
       #elif (PanelType == PanelAUOM215HW01V7)
         #include "PanelAUOM215HW01V7.h"
       #elif (PanelType == PanelAUOM240HW01V6||PanelType==PanelAUOM240HW01VB)
         #include "PanelAUOM240HW01V6.h"
	#elif (PanelType==PanelTPM215HW01H1PS1)
         #include "PanelTPM215HW01H1PS1.h"
	#elif (PanelType==PanelCMOM215H1L01)
         #include "PanelCMOM215H1L01.h"
       #elif (PanelType==PanelCMOM236H1L07)
         #include "PanelCMOM236H1L07.h" 
       //#elif (PanelType==PanelCMOM200O1L02)
         //#include "PanelCMOM200O1L02.h" 
       #elif (PanelType == PanelAUOM215HW01V6||PanelType == PanelAUOM215HW01VB)
         #include "PanelAUOM215HW01V6.h"		 
       #elif(PanelType==PanelTPM236H3L02 )
	   #include"PanelTPM236H3L02.h"
	   #elif(PanelType==PanelTPM200O1L02 )
	   #include"PanelTPM200O1L02.h"
	   #elif(PanelType==PanelM185XW01)
	   #include"PanelM185XW01.h"
	#elif(PanelType==PanelTPM215H1L01)
	#include "PanelTPM215H1L01.h" 
	#elif( PanelType  == PanelLM230WF1TLD1 )
	#include "PanelLM230WF1TLD1.h"	  
	#elif(PanelType==PanelAUOM156XW01V0)
	#include"PanelAUOM156XW01V0.h"
	#elif(PanelType==PanelAUOM240HW01V7)
	#include"PanelAUOM240HW01V7.h"
	#elif(PanelType==PanelAUOB156XW02V6 )
	#include"PanelAUOB156XW02V6.h"
	#elif(PanelType==PanelTPM185B1XW01)
	#include"PanelTPM185B1XW01.h"
	#elif(PanelType==PanelLM200WD3TLA1)
	#include "PanelLM200WD3TLA1.h"
	#elif(PanelType==PanelAUOM270HW01V0)
	#include"PanelAUOM270HW01V0.h"
	#elif(PanelType==PanelCMOM270HGEL10)
	#include"PanelCMOM270HGEL10.h"
	#elif(PanelType==PanelTPM200O1L02C1D)
	#include"PanelTPM200O1L02C1D.h"
	#elif(PanelType==PanelLM230WF5TLA1)
	#include"PanelLM230WF5TLA1.h"
	#elif(PanelType==PanelHSD190MEN4A02)
	#include"PanelHSD190MEN4A02.h"
	#elif(PanelType==PanelTPM190A1)
	#include"PanelTPM190A1.h"
	#elif(PanelType==PanelTMS190)
	#include"PanelTMS190.h"
	#elif(PanelType==PanelLM200WD3TLC4)
	#include"PanelLM200WD3TLC4.h"
	#elif(PanelType==PanelLM200WD3)
	#include"PanelLM200WD3.h"
	#elif(PanelType==PanelLM215WF1)
	#include"PanelLM215WF1.h"
	#elif(PanelType==PanelLM215WF4)
	#include"PanelLM215WF4TLE1.h"
	#elif(PanelType==PanelM215HW01)
	#include"PanelM215HW01.h"
	#elif(PanelType==PanelM185B3LA1)
	#include"PanelM185B3LA1.h"
	#elif(PanelType==PanelM236H3LA3)
	#include"PanelM236H3LA3.h"
    #elif(PanelType==PanelLM275WF5)
    #include"PanelLM275WF5.h"
    #elif (PanelType==PanelLM215WF3_S2A2)
    #include "PanelLM215WF3_S2A2.h"
    #elif (PanelType==PanelBM230WF3_SJC2)
    #include "PanelBM230WF3_SJC2.h"
    #elif (PanelType==PanelLM230WF5_T2F2)	//120417 Modify
    #include "PanelLM230WF5_T2F2.h"
    #elif PanelType==PanelLM215WF7_S2Z2	//120503 Modify
    #include "PanelLM215WF7_S2Z2.h"
    #elif PanelType==PanelLM230WFA_S2Z4 //120503 Modify
    #include "PanelLM230WFA_S2Z4.h"
    #elif PanelType==PanelLM270WF6_S2Z4 //120503 Modify
    #include "PanelLM270WF6_S2Z4.h"
	#elif (PanelType==PanelLM275WF5_S2A2)	//120503 Modify
	#include "PanelLM275WF5_S2A2.h"
	#elif(PanelType==PanelBM190WX2)
	#include"PanelBM190WX2.h"
	#elif(PanelType==PanelLM185WH2)
	#include"PanelLM185WH2.h"
	#elif(PanelType==PanelAUOM240HW01VD)
	#include"PanelAUOM240HW01VD.h"	
    #elif(PanelType==PanelBM215WF4)	//120112 by Bian
    #include"PanelBM215WF4.h"	
	#elif (PanelType==PanelBM200WD3_TJC1)	//120516 Modify
	#include "PanelBM200WD3_TJC1.h"
	#elif ( PanelType == PanelLM190E09 )//120816 bian
	 #include "PanelLM190E09.h"
  	#elif (PanelType==PanelCMIM195FGE)	//120816 bian
	#include "PanelCMIM195FGE.h"
	#elif ( PanelType == PanelBM230WF5_TJC3 )//120816 bian
	 #include "PanelBM230WF5_TJC3.h"
	#elif(PanelType==PanelTPM215HW01HGJL02)
	#include"PanelTPM215HW01HGJL02.h"
        #elif(PanelType==PanelHR215WU1)
        #include"PanelHR215WU1.h"
       #elif(PanelType==PanelHR215WU1_120)
       #include"PanelHR215WU1_120.h"
       #elif   PanelType==PanelLM240WU8_SLD1
        #include"PanelLM240WU8_SLD1.h"
	#elif	PanelType==PanelM215HW03V1	//131031 xiandi
		#include"PanelM215HW03V1.h"
        #elif PanelType==PanelM280HKJ_L30
        #include"PanelM280HKJ_L30.h"
	#elif PanelType==PanelM280HKJ_L30_VER32
        #include"PanelM280HKJ_L30_VER32.h"
	#elif PanelType==PanelM280HKJ_L50_VER10  //GYP20150824
        #include"PanelM280HKJ_L50_VER10.h"
        #elif   PanelType==PanelLTM240CT07
        #include"PanelLTM240CT07.h"
        #elif (PanelType == PanelAUOM240HW01V8||PanelType == PanelAUOM240HW01V80A)
	 #include "PanelAUOM240HW01V8.h"
        #elif (PanelType == PanelLTM270DL06)//petit  20130626
        #include "PanelLTM270DL06.h"
		#elif (PanelType == PanelLM250WQ1_S2A2)//Gino 20141023
        #include "PanelLM250WQ1_S2A2.h"
	#elif (PanelType == PanelBM230WF5_T2G2)//petit 20121121
	 #include "PanelBM230WF5_T2G2.h"
	 #elif (PanelType == PanelTPM220Z1_ZGEL02)//petit 20121122
	 #include "PanelTPM220Z1_ZGEL02.h"
	 #elif (PanelType == PanelTPM236H3_WU3110)//petit 20121211
	 #include "PanelTPM236H3_WU3110.h"
	 #elif (PanelType == PanelTPM236H3HGJL02)//petit 20121211
	 #include "PanelTPM236H3HGJL02.h"
	#elif (PanelType == PanelAUOM240HW02V7)//petit 20121211
	 #include "PanelAUOM240HW02V7.h"
	#elif (PanelType == PanelBM230WF3_S2K2)
 	#include "PanelBM230WF3_S2K2.h"
        #elif (PanelType == PanelLM230WF3_SLK1)
        #include "PanelLM230WF3_SLK1.h"
	 #elif (PanelType == PanelLM230WF3_SLN1)//Gino 20140516
        #include "PanelLM230WF3_SLN1.h"
        #elif (PanelType == PanelHR236WU1)
        #include "PanelHR236WU1.h"
       #elif (PanelType == PanelAUOM240HTN01_2)//petit 20130205
        #include "PanelAUOM240HTN01_2.h"	
	#elif (PanelType == PanelBM230WF5_TAE2)//petit 20130205
        #include "PanelBM230WF5_TAE2.h"	
        #elif (PanelType == PanelTPM195WD1)
        #include "PanelTPM195WD1.h" 
	#elif (PanelType == PanelCMIM270HGEL20)//20130303
        #include "PanelCMIM270HGEL20.h" 
	#elif (PanelType == PanelAUOM270HW01V2)//20130325
        #include "PanelAUOM270HW01V2.h" 
        #elif (PanelType == PanelTPM240WF1_HTN01)//20130410
        #include "PanelTPM240WF1_HTN01.h" 
        #elif (PanelType == PanelTPM215HW01HTN01)//Jean_20130420
        #include "PanelTPM215HW01HTN01.h" 
	#elif (PanelType == PanelTPM215HW01_HTN01_REV10CF)//20141213 Gino
        #include "PanelTPM215HW01_HTN01_REV10CF.h" 
	#elif (PanelType == PanelTPM215HW01HTN0110CF)//xuebo add new model 20140604
        #include "PanelTPM215HW01HTN0110CF.h" 
	#elif (PanelType == PanelTPM270WF1_MWN1)//20130512
        #include "PanelTPM270WF1_MWN1.h" 
	#elif (PanelType == PanelIVOM270MWN1)//20130516
        #include "PanelIVOM270MWN1.h" 
	#elif (PanelType == PanelTPM240WF1_HW01)//Jun 20130619
        #include "PanelTPM240WF1_HW01.h"
    #elif (PanelType == PanelCMIM190CGE_L20)//bian 20130701
	#include "PanelCMIM190CGE_L20.h" 
    #elif (PanelType == PanelAUOM190ETN01)//bian 20130701
	#include "PanelAUOM190ETN01.h"	
	#elif (PanelType == PanelAUOM270HTN01)//petit 20130712
	#include "PanelAUOM270HTN01.h"
	#elif (PanelType == PanelINXM270HGE)//Gino 20140520
	#include "PanelINXM270HGE.h"
	#elif (PanelType == PanelAUOM270HTN02)//fay 20131119
	#include "PanelAUOM270HTN02.h"
	#elif (PanelType == PanelAUOM170ETN01)//petit 20130731
	#include "PanelAUOM170ETN01.h"	
	#elif (PanelType == PanelAUOT215HVN01_1)	//130826 xiandi
	#include "PanelAUOT215HVN01_1.h"	
	#elif (PanelType == PanelTPM236H3_WU3100)	//130925 bian
	#include "PanelTPM236H3_WU3100.h"
	#elif (PanelType == PanelCMIM215HGE_L21)	//bian 20140204
	#include "PanelCMIM215HGE_L21.h"
	#elif (PanelType == PanelTPM236H3_WU3101)	//140106 bian
	#include "PanelTPM236H3_WU3101.h"
	#elif (PanelType == PanelTPM236WF1_WU3301)	//20141015 Gino
	#include "PanelTPM236WF1_WU3301.h"
	#elif (PanelType == PanelTPM236H3_WU3101_REV4950)	//140106 bian
	#include "PanelTPM236H3_WU3101_REV4950.h"
	#elif (PanelType == PanelTPM236WF1)
	#include "PanelTPM236WF1.h"
	#elif	PanelType==PanelLTM240CL04
	#include"PanelLTM240CL04.h"
	#elif (PanelType == PanelCMIM195FGE_L20)//petit 20130715
	#include "PanelCMIM195FGE_L20.h"	
	#elif (PanelType == PanelAUOM270HVN02)	//petit  20131107
	#include "PanelAUOM270HVN02.h"	
	#elif (PanelType == PanelAUOM215HTN01)	//petit  20131108
	#include "PanelAUOM215HTN01.h"	
	#elif (PanelType == PanelAUOM215HTN01_1)	//20140825 Gino
	#include "PanelAUOM215HTN01_1.h"	
	#elif (PanelType == PanelTPM215HW01_DAT01)	//petit  20131222
	#include "PanelTPM215HW01_DAT01.h"	
    #elif (PanelType == PanelTPM215HW01_HGEL02)	//yanping  20160312
	#include "PanelTPM215HW01_HGEL02.h"	
	#elif (PanelType==PanelTPM215HW01_DAT01_R10R) //YANPING.GUO 20150916
	#include "PanelTPM215HW01_DAT01_R10R.h"
    #elif (PanelType==PanelTPM215HW01HTN0110CF_1) //zhenwu.lian 20151209
	#include "PanelTPM215HW01HTN0110CF_1.h"
    #elif (PanelType==PanelTPM215HW01_HGEL02_TC1J) //zhenwu.lian 20160111
	#include "PanelTPM215HW01_HGEL02_TC1J.h"
	#elif (PanelType == PanelTPM215HW01_DAT03)	//Gino  20140822
	#include "PanelTPM215HW01_DAT03.h"	
	#elif (PanelType == PanelTPM215HW01_HGEL03)	//yanping  20160312
	#include "PanelTPM215HW01_HGEL03.h"	
	#elif (PanelType == PanelLM270WF7_SSA1)
   	#include "PanelLM270WF7_SSA1.h"
	#elif (PanelType == PanelAUOM270DTN01_1)//petit  20130626
	#include "PanelAUOM270DTN01_1.h"
	#elif (PanelType == Panel32W_BOEHV320QHM_C80)//petit  20130626
	#include "Panel32W_BOEHV320QHM_C80.h"
	#elif (PanelType == PanelTPM240WF1_HTN01_20FA)
	#include "PanelTPM240WF1_HTN01_20FA.h" 
	#elif ( PanelType== PanelTPM215WF1_WU3201)
	#include "PanelTPM215WF1_WU3201.h"
	#elif (PanelType == PanelTPM236H3_WU3101_REV4970)//20140826                   
	#include "PanelTPM236H3_WU3101_REV4970.h"
	#elif (PanelType == PanelM185B1WX3401K)//20140922 
	#include "PanelTPM185B1WX3401K.h"
	#elif (PanelType == PanelTPM185WH2_N10_K)
	#include "PanelTPM185WH2_N10_K.h"
	#elif (PanelType == PanelHR236WU1_310)
	#include "PanelHR236WU1_310.h" //20141008
   	#elif (PanelType == PanelAUOM240HW01V80B)
	#include "PanelAUOM240HW01V80B.h"
	#elif (PanelType == PanelTPM236WF1_HJJP02)
    #include "PanelTPM236WF1_HJJP02.h"
	#elif (PanelType == PanelLM230WF3_S2L1)
    #include "PanelLM230WF3_S2L1.h"
	#elif (PanelType == PanelLM230WF3_S2LC)
    #include "PanelLM230WF3_S2LC.h"
	#elif (PanelType == PanelLM215WF3_S2L1)
    #include "PanelLM215WF3_S2L1.h"
	#elif (PanelType == PanelLM215WF3_S2LC)
    #include "PanelLM215WF3_S2LC.h"
	#elif (PanelType == PanelLM215WF3_S3L1)
    #include "PanelLM215WF3_S3L1.h"
	#elif (PanelType == PanelLM215WF9_S1A3 )
    #include "PanelLM215WF9_S1A3.h"
	#elif (PanelType == PanelTPM207WF1_FHBN20)
    #include "PanelTPM207WF1_FHBN20.h"
    #elif (PanelType == PanelLTM270HP01)
    #include "PanelLTM270HP01.h"
    #elif (PanelType == PanelTPM236WF1_WU3301K_4831)	//20141015 Gino
    #include "PanelTPM236WF1_WU3301K_4831.h"
    #elif (PanelType == PanelTPM236WF1_WU3301K_4832)	//20141015 Gino
    #include "PanelTPM236WF1_WU3301K_4832.h"
    #elif (PanelType == PanelLM230WF3_S3L1)	//20141015 Gino
    #include "PanelLM230WF3_S3L1.h"
    #elif (PanelType == PanelLM230WF3_S3L2)	//20150512 GYP
    #include "PanelLM230WF3_S3L2.h"
    #elif (PanelType == PanelTPM236WF1_HJPP02_SC3G)
    #include "PanelTPM236WF1_HJPP02_SC3G.h"
    #elif (PanelType == PanelTPM215WF1_HJJP02)	//20141208 Gino
    #include "PanelTPM215WF1_HJJP02.h"
	#elif ( PanelType 	== PanelMV238FHM_N10_23P8)//20150104 Alpha
    #include "PanelMV238FHM_N10_23P8.h"	
    #elif (PanelType == PanelM236HJJSUFFIX_L31)
    #include "PanelM236HJJSUFFIX_L31.h"
    #elif (PanelType == PanelHSM270EB_300)
    #include "PanelHSM270EB_300.h"
    #elif (PanelType == PanelLM238WF2_S2H2)//20150203 Alpha
    #include "PanelLM238WF2_S2H2.h"
    #elif (PanelType == PanelAUOM320DVN01_0) //20150225 Alpha
    #include "PanelAUOM320DVN01_0.h"
    #elif (PanelType == PanelLM230WF3_S3L1_VER01) //20150302 Alpha 
    #include "PanelLM230WF3_S3L1_VER01.h"
    #elif ( PanelType	== PanelTPM215HW01DAT01)//20140708 Gino
    #include "PanelTPM215HW01DAT01.h"
    #elif ( PanelType	== PanelTPM270WF1_WU3300)//20140708 Gino
    #include "PanelTPM270WF1_WU3300.h"
	#elif (PanelType==PanelM170ETN01)		//shizhen
    #include "PanelM170ETN01.h"
    #elif (PanelType == PanelLM230WF3_S3L1_VER04) //20150602 Alpha 
    #include "PanelLM230WF3_S3L1_VER04.h"
	#elif (PanelType == PanelLM230WF3_S3L1_Rev221)
    #include "PanelLM230WF3_S3L1_Rev221.h"
    #elif(PanelType==PanelTPM236H3HGEL02 )
	#include"PanelTPM236H3HGEL02.h"
    #elif(PanelType==PanelLM270WF5_S3A1 )
    #include"PanelLM270WF5_S3A1.h"
	#elif (PanelType == PanelTPM238WF1FHBN10K)	//20150625 Alpha
    #include "PanelTPM238WF1FHBN10K.h"
	 #elif ( PanelType	== PanelTPM270WF1_FHBN10)//20140708 Gino
    #include "PanelTPM270WF1_FHBN10.h"
	#elif (PanelType == PanelM200HJJ_L20)
    #include "PanelM200HJJ_L20.h"
    #elif (PanelType == PanelLM270WF5_S3AA)
    #include "PanelLM270WF5_S3AA.h"
    #elif (PanelType == PanelLM270WF5_S3A2)
    #include "PanelLM270WF5_S3A2.h"
    #elif (PanelType==PanelHSMB238_1DAN01)
    #include "PanelHSMB238_1DAN01.h"
    #elif (PanelType==PanelHSMB238_2DAN01)
    #include "PanelHSMB238_2DAN01.h"
    #elif (PanelType ==PanelAUOM215HTN01_V1) 
    #include "PanelAUOM215HTN01_V1.h"	
#elif (PanelType 	==PanelMV270FHM_N20)
		#include "PanelMV270FHM_N20.h"	
#elif (PanelType 	==PanelM270HVN02_1)
		#include "PanelM270HVN02_1.h"	
#elif (PanelType 	==PanelM215HJJ_N20)
		#include "PanelM215HJJ_N20.h"			
#elif (PanelType 	==PanelLSM270HP06)
		#include "PanelLSM270HP06.h"	
#elif (PanelType 	==PanelMV270QHB_N20)
		#include "PanelMV270QHB_N20.h"		
#elif (PanelType == PanelST3151B01)      //2011.9.16 cc add
#include "PanelST3151B01.h"
#elif (PanelType == PanelLC238LF1L)      //2011.9.16 cc add
#include "PanelLC238LF1L.h"
#elif (PanelType == PanelST2151B01)      //2011.9.16 cc add
#include "PanelST2151B01.h"
#elif (PanelType == PanelLC270LF1L)      //2011.9.16 cc add
#include "PanelLC270LF1L.h"
#elif (PanelType == PanelM215HGE_L21)      //2011.9.16 cc add
#include "PanelM215HGE_L21_XJH.h"
#elif (PanelType == PanelDV185WHM_NM1)      //2011.9.16 cc add
#include "PanelDV185WHM_NM1.h"
#elif (PanelType == PanelM238HCJ_31)      //2011.9.16 cc add
#include "PanelM238HCJ_31.h"
	#endif
#endif


// 2017//02/20
#define EDID_1024x768				(PanelWidth== 1024&&PanelHeight==768)

#define EDID_1280x800				(PanelWidth== 1280&&PanelHeight==800)

#define EDID_1600x900				(PanelWidth== 1600&&PanelHeight==900)

#define EDID_1280x1024				(PanelWidth== 1280&&PanelHeight==1024)

#define EDID_1366x768				(PanelWidth== 1366&&PanelHeight==768)
 
#define EDID_1440x900				(PanelWidth== 1440&&PanelHeight==900)

#define EDID_1600x1200				(PanelWidth== 1600&&PanelHeight==1200)

#define EDID_1680x1050				(PanelWidth== 1680&&PanelHeight==1050)

#define EDID_1920x1080				(PanelWidth== 1920&&PanelHeight==1080)

#define EDID_1920x1200				(PanelWidth== 1920&&PanelHeight==1200)

#define EDID_2560x1440                 	(PanelWidth== 2560&&PanelHeight==1440)

//////////////////////////////////////////////senyo »úÖÖ//////////////////////////////////////////////////////////////


#define PANEL_TCON_CONFIG_LVDS_IMPEDANCE    ((PanelType==PanelLTM270DL06) || (PanelType==PanelLTM240CL04)||(PanelType==PanelLM250WQ1_S2A2)|| (PanelType == PanelLM230WF3_S2L1)||(PanelType == PanelLM230WF3_S2LC))

#ifndef PanelVsyncFreq
#define PanelVsyncFreq      (60) // 750+15 
#endif

#ifndef PanelMinVfreq
#define PanelMinVfreq   (500-12)
#endif

#ifndef PanelMaxVfreq
#define PanelMaxVfreq   (750+12)
#endif

#if (PanelType==PanelLTM190M2)
#define DITHER_COEFF    0xE4
#define DITHER_METHOD    0x12
#elif PanelType==PanelCLAA220WA02
#define DITHER_COEFF    0xE4
#define DITHER_METHOD    0x42
#elif PanelType==PanelTPM200O1L02
#define DITHER_COEFF    0xE4
#define DITHER_METHOD    0x40
#else
#define DITHER_COEFF    0x2D
#define DITHER_METHOD    0x12
#endif

#ifndef PanelminiLVDS
#define PanelminiLVDS       0
#endif

#ifndef PANEL_VCOM_ADJUST
#define PANEL_VCOM_ADJUST       0
#endif

#ifndef PANEL_SSC_MODULATION_DEF
   #if PanelType==PanelTPM236H3HGJL02
        #define PANEL_SSC_MODULATION_DEF   30 // unit: 1KHz, range 0~40 means 0~40KHz
   #else
        #define PANEL_SSC_MODULATION_DEF   40 // unit: 1KHz, range 0~40 means 0~40KHz
   #endif
#endif

#ifndef PANEL_SSC_PERCENTAGE_DEF
	#if PanelType ==PanelHSMB238_2DAN01||PanelType ==PanelHSMB238_1DAN01//PanelAUOM270HTN02//PanelLM230WF5_T2F2
		#define PANEL_SSC_PERCENTAGE_DEF   0
	#else
		#define PANEL_SSC_PERCENTAGE_DEF     20  // unit: 0.1%, range 0~30 means 0~3%
	#endif
#endif

#ifndef PANEL_SSC_MODULATION_MAX
	#if PanelType ==PanelHSMB238_2DAN01||PanelType ==PanelHSMB238_1DAN01//PanelAUOM270HTN02//PanelLM230WF5_T2F2
		#define PANEL_SSC_MODULATION_MAX   0
	#else
		#define PANEL_SSC_MODULATION_MAX    40 // unit: 1KHz, range 0~40 means 0~40KHz
	#endif
#endif

#ifndef PANEL_SSC_PERCENTAGE_MAX
	#if PanelType ==PanelHSMB238_2DAN01||PanelType ==PanelHSMB238_1DAN01//PanelAUOM270HTN02//PanelLM230WF5_T2F2
		#define PANEL_SSC_PERCENTAGE_MAX   	0
	#else
		#define PANEL_SSC_PERCENTAGE_MAX      30 // unit: 0.1%, range 0~30 means 0~3%
	#endif
#endif

#ifndef LVDS_FAIL_TARGET//130703 nick
#define LVDS_FAIL_TARGET    0x2A // 0x3F*2/3
#endif

#ifndef LVDS_VOLTAGE_TARGET
    #define LVDS_VOLTAGE_TARGET  IGT_TARGET_250  //IGT_TARGET_300
#endif
// 80 PIN IC double ,petit 20130816
#define DOUBLE_LVDS_CLK_SWING    (PanelDualPort&&(CHIP_ID==CHIP_TSUMF))	//110229 Modify

#if ENABLE_CHECK_PANEL_60HZ_MAX_VTOTAL

#if (PanelType == PanelTPVSDC27)
#define PanelMax60HZVTotal	1150
#elif (PanelType == PanelTPM236H3_HL01S_RevC5B)
#define PanelMax60HZVTotal	1220
#elif (PanelType == PanelTPM236H3_HL01S)
#define PanelMax60HZVTotal	1220
#endif

#endif

#ifndef SHORT_LINE_CHECK
#define SHORT_LINE_CHECK    0
#endif

#ifndef PANEL_SWAP_PN
#define PANEL_SWAP_PN       0
#endif

#ifndef PAIR_SWAP_B
#define PAIR_SWAP_B         0
#endif

#ifndef PANEL_SWAP_AB_PORT
#define PANEL_SWAP_AB_PORT  0 //0: non-swap, 0xFF: AB swap
#endif

#ifndef PANEL_SWAP_CD_PORT
#define PANEL_SWAP_CD_PORT  0//0: non-swap ,0xFF: CD swap
#endif

#ifndef PANEL_3D_PASSIVE
#define PANEL_3D_PASSIVE            0
#endif

#ifndef PANEL_3D_PASSIVE_4M
#define PANEL_3D_PASSIVE_4M         0
#endif
#ifndef PANEL_OUTPUT_FMT_3D_LR
#define PANEL_OUTPUT_FMT_3D_LR      0
#endif


#ifndef PANEL_OUTPUT_FMT_3D_CB
#define PANEL_OUTPUT_FMT_3D_CB      0
#endif

#ifndef PANEL_OUTPUT_FMT_3D_FS
#define PANEL_OUTPUT_FMT_3D_FS      0
#endif

#ifndef PANEL_OUTPUT_FMT_3D_TB
#define PANEL_OUTPUT_FMT_3D_TB      0
#endif

#ifndef PANEL_OUTPUT_FMT_3D_SBS
#define PANEL_OUTPUT_FMT_3D_SBS      0
#endif


#ifndef PANEL_QUAD_PORT
#define PANEL_QUAD_PORT      0
#endif

#ifndef LVDS_TI_BitModeSel
#define LVDS_TI_BitModeSel          LVDS_TI_8BIT // TI_10BIT:1 ,TI_8BIT:2,TI_6BIT:3
#endif

#ifndef LVDS_CH_A
#define LVDS_CH_A           0
#endif

#ifndef LVDS_CH_B
#define LVDS_CH_B           1
#endif

#ifndef LVDS_CH_C
#define LVDS_CH_C           2
#endif

#ifndef LVDS_CH_D
#define LVDS_CH_D           3
#endif

#ifndef LVDS_CH_A_SWAP
#define LVDS_CH_A_SWAP              LVDS_CH_A
#endif

#ifndef LVDS_CH_B_SWAP
#define LVDS_CH_B_SWAP              LVDS_CH_A
#endif

#ifndef LVDS_CH_C_SWAP
#define LVDS_CH_C_SWAP              LVDS_CH_C
#endif

#ifndef LVDS_CH_D_SWAP
#define LVDS_CH_D_SWAP              LVDS_CH_D
#endif

#ifndef DISABLE_SHORT_LINE_TUNE
#define DISABLE_SHORT_LINE_TUNE    0
#endif

#ifndef VCOM_TYPE		//120322 Modify
#define VCOM_TYPE        VCOM_RICHTEK
#endif

#ifndef TURNOFF_PANEL_BEFORE_DISABLE_LVDS_OUTPUT		//120703 Modify
#define TURNOFF_PANEL_BEFORE_DISABLE_LVDS_OUTPUT	0
#endif

#ifndef AFTER_DISABLE_PANEL_POWER_INSERT_WHITE
#define AFTER_DISABLE_PANEL_POWER_INSERT_WHITE        0
#endif

#ifndef LVDS_OUTPUT_DO_NOT_TURNOFF_PANEL_POWER
#define LVDS_OUTPUT_DO_NOT_TURNOFF_PANEL_POWER         0
#endif

#ifndef BOOST_CURRENT_LIMIT_VALUE
#define BOOST_CURRENT_LIMIT_VALUE   2
#endif

#ifndef ForwardVoltage_Of_EachLED
#define ForwardVoltage_Of_EachLED  33
#endif

#ifndef DISABLE_SHORT_FRAME_TUNE
#define DISABLE_SHORT_FRAME_TUNE   0
#endif
#define FUNC_ENABLE         (0xFF)
#define FUNC_DISABLE        (0)

#define LVDS_TI_10BIT       1
#define LVDS_TI_8BIT        2
#define LVDS_TI_6BIT        3

#ifndef Panel_VTT_3D // 121130 coding, need add to panel init
#define Panel_VTT_3D_120    1524//1480//1524    //20111114 xm, ASUS VG278H_1Chip, A512  //2011024 Xm, ASUS VG278H_1Chip, A039
#define Panel_VTT_3D_110    1663//1616//1663    //20111114 xm, ASUS VG278H_1Chip, A512   //2011024 Xm, ASUS VG278H_1Chip, A039
#define Panel_VTT_3D_100    1829//1776//1829    //20111114 xm, ASUS VG278H_1Chip, A512  //2011024 Xm, ASUS VG278H_1Chip, A039
#define Panel_VTT_3D        Panel_VTT_3D_120
#endif

#ifndef LVDS_PRE_EMPHASIS
#define LVDS_PRE_EMPHASIS	0
#endif

#ifndef PanelOffOnDelay
#define PanelOffOnDelay        1200 // T4 >= 500ms
#endif

#ifndef	NormalWhite
#define NormalWhite				1
#endif


