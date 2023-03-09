#ifndef _BOARD_H

#define CHIP_TSUML      0
#define CHIP_TSUMU      1
#define CHIP_TSUMB      2
#define CHIP_TSUMY      3
#define CHIP_TSUMV      4
#define CHIP_TSUM2      5
#define CHIP_TSUMC      6
#define CHIP_TSUMD      7
#define CHIP_TSUMJ      8
#define CHIP_TSUM9      9
#define CHIP_TSUMF      10

//////-------------------------------------

#define INPUT_0A        				BIT0	//0//BIT0    
#define INPUT_1C        				BIT1    // digital portx1
#define INPUT_2C        				BIT2    // digital portx2
#define INPUT_3C        				BIT3    // digital portx3

/////-------------------------------------

#define _BOARD_H
//****************************************************************
#ifndef ModelName
#define  ModelName      JRY_TESTBOARD_C_BOARD//Debug Mode need define
#endif

#include "LOGO_DEFINE.H"
//==============================================================
#include "MODEL_DEFINE.H"
//*******************PanelType Define********************************
#include "PANEL_DEFINE.H"
//***********************MainBoardType  Type*****************************
#include "BOARD_DEFINE.H"

//*****************************************************************



#define INPUT_1A       		0
#define INPUT_1A1D     		1
#define INPUT_1A2D	  		2
#define INPUT_1A1H          3
#define INPUT_1A2H          4
#define INPUT_2A2D          5
#define INPUT_1A1D1H      	6
#define INPUT_1A1D1DP      	7
#define INPUT_1A1H1DP       8
#define INPUT_1A1D1H1DP     9

#define INPUT_1A2C         10 // 1A, combo portx2
#define INPUT_1A3C         11 // 1A, combo portx3
#define INPUT_2H           12 // 20141208 Alpha
#define INPUT_1A1DP        13 //20151126 Alpha
#define INPUT_1H           14 // 20160907  Alpha
#define INPUT_1A2H1DP      15
#define INPUT_1D1H1DP      16


#define PANEL_17						0
#define PANEL_17_WIDE					1
#define PANEL_19						2
#define PANEL_19_WIDE					3
#define PANEL_20_WIDE					4
#define PANEL_22_WIDE         			5

//*****************************************************************

//*******************Language Define********************************
//English,Spanish,France,German,Italian,Portugues,Russia,SChina,
#define ASIA							1
//English,Spanish,France,Portugues,Russia,SChina,TChina,Korea,
#define EUROPE							2
//English,Spanish,France,German,Italian,Russia,Swedish,Polish,Czech,

#define All13Language					3	//gy:090824:for 13 Language(Add ASIS and EUROPE Together)
//English,German,France,Italian,Spanish,Swedish,Polish,Czech,Russia,Portugues,Korea,TChina,SChina

#define All14Language_AddJap			4
//English,German,France,Italian,Spanish,Swedish,Polish,Czech,Russia,Portugues,Korea,TChina,SChina,Japan
//*****************************************************************

//*******************Scankey Type********************************

#define I2CKEY_NONEUSE                   0
#define I2CKEY_CYPRESS                   1
#define I2CKEY_ITE                       2
#define I2CKEY_ENE                       3
//*****************************************************************

//*******************VCOM TYPE************************************

#define VCOM_RICHTEK              		0
#define VCOM_MAXIM              		1   //MAX9668
#define VCOM_SMIM              		    2   //SM4053B
#define VCOM_TPSIM              		3   //TPS65178A

//*****************************************************************
//*******************EEPROM TYPE
#define EEPROM_24C04        0
#define EEPROM_24C16        1
#define EEPROM_24C32        2
//*****************************************************************
//=================================================================
//1 进工厂模式
#define FEnter_AC_MENU	   					0
#define FEnter_POWER_MENU	  				1
#define FEnter_POWER_EXIT	  				2
//==================================================================
//1 低蓝光模式
#define LowBlueLight_Off						0		//3关闭低蓝光			
#define LowBlueLight_ColorTemp				1		//3低蓝光在色温下
#define LowBlueLight_Misc_Guage				2		//3 低蓝光在其他菜单下
#define LowBlueLight_Misc_Group				3		//3 低蓝光在其他菜单下
#define LowBlueLight_SharpFunc				4		//3SHARP低蓝光调节方式
//==================================================================
//2 导航键显示

#define	OsdHelpKey_Off							0
#define	OsdHelpKey_Under						1
#define	OsdHelpKey_Right						2
//==================================================================
#ifndef BJ_REQUEST // 130117_1 For BJ Factory Special Suntion and define
#define BJ_REQUEST		0
#endif


#if(ModelName==TSUMXXV_DEMO)
#include"TSUMXXV_DEMO.h"
#elif(ModelName==TSUMXXB_DEMO)
#include"TSUMXXB_DEMO.h"
#elif(ModelName==TSUMXX2_DEMO)
#include"TSUMXX2_DEMO.h"



//====new chip demo define ===//
#elif(ModelName==TSUMXXC_DEMO)
#include"TSUMXXC_DEMO.h"
#elif(ModelName==TSUMXXD_DEMO)
#include"TSUMXXD_DEMO.h"
#elif(ModelName==TSUMXX9_DEMO)
#include"TSUMXX9_DEMO.h"
#elif(ModelName==TSUMXXF_DEMO)
#include"TSUMXXF_DEMO.h"
#elif (ModelName == AOC_SY_T4017C)
#include "AOC_SY_T4017C.h"

#elif (ModelName==HKC_W8787_BV1)
#include "HKC_W8787_BV1.h"
//====new chip demo define ===//
#elif (ModelName==SPT_CNC_O38CDMT9_GV1)
#include"SPT_CNC_O38CDMT9_GV1.h"
#elif (ModelName==SPT_CNC_JRY_L8787_BV1)
#include"SPT_CNC_JRY_L8787_BV1.h"
#elif (ModelName==LEYI_JRY_LQ570S_BV1)
#include"LEYI_JRY_LQ570S_BV1.h"
#elif (ModelName==HKC_L58CDT9_NV1)
#include"HKC_L58CDT9_NV1.h"
#elif (ModelName==HKC_O587HT9_NV1)
#include"HKC_O587HT9_NV1.h"
#elif (ModelName==YWPK_L58CDT9_NV1)
#include"YWPK_L58CDT9_NV1.h"
#elif (ModelName==JRY_L58VHN_GV3)//20140103
#include"JRY_L58VHN_GV3.h"
#elif (ModelName==JRY_L58CDT9_GV3)//20140103
#include"JRY_L58CDT9_GV3.h"
#elif (ModelName==JRY_L58CDT9_EV1)//20140103
#include"JRY_L58CDT9_EV1.h"
#elif (ModelName==JRY_L58CDT9_PV1)//20140103
#include"JRY_L58CDT9_PV1.h"
#elif (ModelName==JRY_L58CDT9_KV1)//20140103
#include"JRY_L58CDT9_KV1.h"
#elif (ModelName==JRY_L58CDT9_AV6)//20140103
#include"JRY_L58CDT9_AV6.h"
#elif (ModelName==JuFeng_Project)//20140103
#include"JuFeng_Project.h"
#elif (ModelName==HUNTKEY_F2272WHS)//20140103
#include"HUNTKEY_F2272WHS.h"
#elif (ModelName==JRY_L58CDT9_GV2)
#include"JRY_L58CDT9_GV2.h"
#elif (ModelName==HJP07BF2_Project)//20140103
#include"HJP07BF2_Project.h"
#elif (ModelName==MODEL_HJP400MA_CDHS)//20140103
#include"MODEL_HJP400MA_CDHS.h"
#elif (ModelName==MODEL_HJP220MA_CDHS)//20140103
#include"MODEL_HJP220MA_CDHS.h"

#elif (ModelName==HH_TCL_T27N1_Project)//20140103
#include"HH_TCL_T27N1_Project.h"
#elif (ModelName==HH_TCL_T27N1_F_Project)//20140103
#include"HH_TCL_T27N1_F_Project.h"
#elif (ModelName==HH_TSY_KF270F075P_F_Project)//20140103
#include"HH_TSY_KF270F075P_F_Project.h"
#elif (ModelName==HH_HKC_27P630Q_U_Project)//20140103
#include"HH_HKC_27P630Q_U_Project.h"
#elif (ModelName==HH_HKC_T32M8C_C_Project)//20140103
#include"HH_HKC_T32M8C_C_Project.h"
#elif (ModelName==X_STAR_NX2410F)//20140103
#include"X_STAR_NX2410F.h"
#elif (ModelName==TOPSYNC_KF238F075P_Y)//20140103
#include"TOPSYNC_KF238F075P_Y.h"
#elif (ModelName==TOPSYNC_KF270W075P)//20140103
#include"TOPSYNC_KF270W075P.h"
#elif (ModelName==MODEL_HS245HFB)//20140103
#include"MODEL_HS245HFB.h"
#elif (ModelName==MODEL_GF238F060P_Y)//20140103
#include"MODEL_GF238F060P_Y.h"
#elif (ModelName==MODEL_NM2400W)//20140103
#include"MODEL_NM2400W.h"
#elif (ModelName==MODEL_HS225HFB)//20140103
#include"MODEL_HS225HFB.h"
#elif (ModelName==MODEL_HS275HFB)//20140103
#include"MODEL_HS275HFB.h"

#elif (ModelName==MODEL_24P630F_CHD)//20140103
#include"MODEL_24P630F_CHD.h"
#elif (ModelName==JRY_TESTBOARD_F_BOARD)//20140103
#include"JRY_TESTBOARD_F_BOARD.h"
#elif (ModelName==JRY_TESTBOARD_C_BOARD)//20140103
#include"JRY_TESTBOARD_C_BOARD.h"
#elif (ModelName==JRY_TESTBOARD_9_BOARD)//20140103
#include"JRY_TESTBOARD_9_BOARD.h"


#elif (ModelName==MODEL_FZ22LVD_FND)//20140103
#include"MODEL_FZ22LVD_FND.h"

#elif (ModelName==MODEL_T24_TCL)//20140103
#include"MODEL_T24_TCL.h"
#elif (ModelName==MODEL_T24N2_TCL)//20140103
#include"MODEL_T24N2_TCL.h"
#elif (ModelName==HH_HKC_XXXXX_U_Project)//20140103
#include"HH_HKC_XXXXX_U_Project.h"
#elif (ModelName==HH_HKC_XXXXX_U2_Project)//20140103
#include"HH_HKC_XXXXX_U2_Project.h"
#elif (ModelName==HH_HKC_KF270F144P_Project)//20140103
#include"HH_HKC_KF270F144P_Project.h"
#elif (ModelName==HH_TCL_DEMO_Project)//20140103
#include"HH_TCL_DEMO_Project.h"
#elif (ModelName==HH_BOARD_DEMO_Project)//20140103
#include"HH_BOARD_DEMO_Project.h"

#endif


#include "DefaultUserRequestOption.h"

#include "DefaultCompilerOption.h"



#ifndef BURST_MODE
#define BURST_MODE 				0
#endif
#ifndef HKC_INPUTSELECT_MODE
#define HKC_INPUTSELECT_MODE 				0
#endif

#ifndef Display_Checksum
#define Display_Checksum 				1
#endif


//#define ENABLE_USE_ISPTOOL_Write_HDCP	     (1&&HDCPKEY_IN_Flash)




#if AudioFunc && (CHIP_ID==CHIP_TSUMU || CHIP_ID == CHIP_TSUMB|| CHIP_ID == CHIP_TSUM2||CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD||CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF)//20131022 JUN Follow Demo Code For VGA Linein No Audio
#define MS_DAC				1
#define InitialDACByISR                 1&MS_DAC
#define CheckInitialDACTime             0&MS_DAC
#define DAC_support_LineoutOnly         0&MS_DAC
#else
#define MS_DAC				0
#endif


#ifndef	UseI2cByTableFunc
//3使用数组方式配置I2C  ，无需在板参设定
#define	UseI2cByTableFunc			0
#endif

#if  UseI2cByTableFunc
//2 TSUMC TSUMD TSUM9 TSUMF
#ifndef I2C_GPIO40_41
#define I2C_GPIO40_41	VGA_Write_EEPROM
#endif
#ifndef I2C_GPIO34_35
#define I2C_GPIO34_35	(DVI_Write_EEPROM||HDMI_Write_EEPROM)
#endif
#ifndef I2C_GPIO32_33
#define I2C_GPIO32_33	(DVI_Write_EEPROM&&HDMI_Write_EEPROM)
#endif
//2 TSUMU TSUMV
#ifndef I2C_GPIO21_22
#define I2C_GPIO21_22	0
#endif
#ifndef I2C_GPIO12_13
#define I2C_GPIO12_13	0
#endif
#ifndef I2C_GPIO16_17
#define I2C_GPIO16_17	0
#endif
#ifndef I2C_GPIO10_11
#define I2C_GPIO10_11	0
#endif
#endif


//*****************************************************************

#define CompressPropFont		1


//*****************************************************************
#if DisplayLogo==NoBrand
#define DisplayPowerOnLogo 		0
#else
#define DisplayPowerOnLogo   	1
#endif
//*****************************************************************
//When Released Plesease Remember To Set DEBUG Flags To Be 0!!!!!!!!!
#define ENable_LoadEDIDSelectPort  1

//#define  DEBUG_EN
#ifdef DEBUG_EN
#define ENABLE_DEBUG        	1
#message "Please remember to disable the debug function!"//Zhifeng.Wu Please don't canel it,just only a message to remind you to disable it ,thanks.
#else
#define ENABLE_DEBUG			0
#if 0//ENABLE_DEBUG
#message "Please remember to disable the debug function!"
#endif
#endif
#define DEBUG_ALLBANK				0//ENABLE_DEBUG
#define DEBUG_IOPORT				0//ENABLE_DEBUG
#define DEBUG_MSTMCU				0//ENABLE_DEBUG
#define DEBUG_FLASH					0
#define DEBUG_DETECT				0
#define DEBUG_PRINTDATA		     	ENABLE_DEBUG
#define DEBUG_MSG					ENABLE_DEBUG
#define DPS_DEBUG                   		0

#define DEBUG_INPUTPORT     	    		0
#define DEBUG_FINDMODE				0
#define DEBUG_INPUTTIMING 			0
#define DEBUG_TIMEINGCHANGE		    0
#define DEBUG_SAVEMODE			    0
#define DEBUG_CAPTUREWIN       	   	 0
#define DEBUG_DE					0
#define DEBUG_HDMI					0
#define DEBUG_OSD					0
#define DEBUG_FLASHADDR			    0
#define DDCCI_ENABLE_DEBUG		    0
#define DEBUG_PRINT_ENABLE          0
#define DEBUG_HDMI_MHL_CABLE_DETECT 0//     1

#if MS_PM
#define DEBUG_PM    			0
#endif
#define DEBUG_HOTSWITCH             0// ENABLE_DEBUG // 120426 coding debug
#define DEBUG_VIRTUAL_KEY			0

//*****************************************************************
//HDMI


#if  ENABLE_HDMI
#define G2_G3_HDMI_AUDIO_FADING			0///1
#define FixDVIPort 						0
#define ENABLE_CEC						0
#define ENABLE_CEC_INT					0
#define HDMIAUTODETECT          		0
#define HDMICOLORTEST					1
#define ENABLE_CTSNSYNC			     	1
#define CheckCTSStable                 	0
#define ENABLE_CTS_INT                  1
#define ENABLE_CTSN_FILTER				1

#define EN_HDMI_NEW_PIXEL_REPETITION    1
#define ENABLE_HDMI_SW_CTS_STABLE		0
#define ENABLE_HDMI_SW_AUDCLK_CHECK		0
#define ENABLE_AUDIO_AUTO_MUTE   		1 // auto mute setting
#define ENABLE_AUDIO_AUTO_FADING   		1 // auto fading setting
#define ENABLE_HAYDN_FADING_BY_HDMI_STATUS        0
#else
#define G2_G3_HDMI_AUDIO_FADING			0
#define FixDVIPort						0
#define ENABLE_CEC						0
#define ENABLE_CEC_INT					0
#define HDMIAUTODETECT             		0
#define HDMICOLORTEST					0
#define ENABLE_CTSNSYNC					0
#define ENABLE_CTS_INT                  0
#define ENABLE_CTSN_FILTER				0

#define CheckCTSStable                  0
#define EN_HDMI_NEW_PIXEL_REPETITION    0
#define ENABLE_HDMI_SW_CTS_STABLE		0
#define ENABLE_HDMI_SW_AUDCLK_CHECK		0
#define ENABLE_AUDIO_AUTO_MUTE   		0 // auto mute setting
#define ENABLE_AUDIO_AUTO_FADING   		0 // auto fading setting
#define ENABLE_HAYDN_FADING_BY_HDMI_STATUS        0
#endif

#ifndef Init_HDCPKey
#define Init_HDCPKey    	           0//0:def code key     1 use flash
#endif

#define ENABLE_USE_ISPTOOL_Write_HDCP			(1&&Init_HDCPKey)

#if ENABLE_USE_ISPTOOL_Write_HDCP
#if 1
#define IspWriteHDCPkey_Addre         	   0x1F000//  0x1F000
#else
#define IspWriteHDCPkey_Addre         	   0x39000//  2M
#endif
#endif


#if 0
#define PANEL_WIDTH                 _PanelWidth
#define PANEL_HEIGHT                _PanelHeight
#else
#define PANEL_WIDTH                 PanelWidth
#define PANEL_HEIGHT                PanelHeight
#endif

#define ECO							1
#define ChipTSU						1     //MST81*   #define ChipTSU 0
#define ChipTSUM_G      			1       // for Gaultier IC
#define SRGB						1
#define MST_MCU						1
#define AOCKey						1
#if !Init_HDCPKey
//	#message "Please remember to disable the default HDCP key!"//Zhifeng.Wu Please don't canel it,just only a message to remind you to disable it ,thanks.
#endif
#define Enable_YMC					0
#define MWEFunction					1
#define DisplayInputInfo			1// 1: show input info ; 0:show energyStar logo

#define Enable_SubWin				!Enable_OsdEngine1// 1: yuhjinn test sub-win only
#define Enable_GDColor      		!Enable_OsdEngine1
#define CenterTitleText				!Enable_OsdEngine1
#define TestAutoSwitch  			1



#define EnableNewHotKey    //edit by lizzie.ding,100525  for ECO+DCR hotkey,if not define this,there is no DCR hotkey
#ifdef EnableNewHotKey
#define HotExpansionAdjust		Enable_Func_AdjExpansion
#define UnifyHotDcrEco			HotExpansionAdjust
#else
#define HotExpansionAdjust  	0
#define UnifyHotDcrEco		 	0
#endif

#if Dual
#define HotInputSelect	 		1
#else
#define HotInputSelect	 		0
#endif

#define DATA_LENGTH_20_BYTE//For HDCP Tool Send 20Byte Data One Block	 
#if 1//def WH_REQUEST
#define Enable_ProductModeAdjust   	0//Zhifeng.Wu Design For Manufacture
#else
#define Enable_ProductModeAdjust	0//Zhifeng.Wu Design For Manufacture
#endif
#define NewFactoryCommand			0
#if 1//Dual   for PE request,all mode have to support Singal port write EDID,100701
//#define UseVGACableReadWriteAllPortsEDID  // edit by lizzie.ding  100525 , for dual model have support  Singal port write EDID
#endif

#define PanelSSCFunction

#if 1// 2011.8.12   11:40:26 AOC require
#define ESaverPowerDownFunc     	1
#else
#define ESaverPowerDownFunc       	0
#endif

#ifndef ENABLE_CABLESTATUSCHANGE_CAUSESYNCSTATUS
#define ENABLE_CABLESTATUSCHANGE_CAUSESYNCSTATUS	0
#endif

//*****************************************************************

#if MST_MCU
#define DirectBus				1
#define DDRBus					0
#else
#define DirectBus				0
#define DDRBus					1
#endif

#define PropFontUseCommonArea    	0

#include "reg52.h"
#if (MainBoardType == MainBoard_TSUML887DC4_1)
#define USEFLASH    0
#include "bd_TSUML887DC4-1.h"
#elif (MainBoardType == MainBoard_TSUMP387MT9_1_DP)
#define USEFLASH    0
#include "bd_TSUMP387MT9-1_DP.h"
#elif (MainBoardType == MainBoard_TSUMP387MT9_1)
#define USEFLASH    0
#include "bd_TSUMP387MT9-1.h"
#elif (MainBoardType == MainBoard_tsuml88bdc2_1)
#define USEFLASH    0
#include "bd_tsuml88bdc2-1.h"
#elif (MainBoardType == MainBoard_TSUML88CMC2)
#define USEFLASH    0
#include "bd_TSUML88CMC2.h"
#elif (MainBoardType == MainBoard_TSUML18CN2)
#define USEFLASH    0
#include "bd_TSUML18CN2.h"
#elif (MainBoardType == MainBoard_TSUML887DS_1)
#define USEFLASH    0
#include "bd_TSUML887DS_1.h"
#elif (MainBoardType == MainBoard_TSUMP58CG_1)
#define USEFLASH    0
#include "bd_TSUMP58CG_1.h"
#elif (MainBoardType == MainBoard_W38CDMT9_DV2)
#define USEFLASH    				1
#include "bd_W38CDMT9_DV2.h"
#elif (MainBoardType == MainBoard_W38CDMT9_QV1)
#define USEFLASH    				1
#include "bd_W38CDMT9_QV1.h"
#elif (MainBoardType == MainBoard_W587HT9_DV1)
#define USEFLASH    				1
#include "bd_W587HT9_DV1.h"
#elif (MainBoardType == MainBoard_W38CDMT9_PV1)
#define USEFLASH    				1
#include "bd_W38CDMT9_PV1.h"
#elif (MainBoardType == MainBoard_W58CDT9_JV1)
#define USEFLASH    				1
#include "bd_W58CDT9_JV1.h"
#elif (MainBoardType == MainBoard_JRY_W58VHN_NV1)
#define USEFLASH    1
#include "bd_JRY_W58VHN_NV1.h"
#elif (MainBoardType == MainBoard_MST9570S_DEMO)
#define USEFLASH    1
#include "bd_JRY_MST9570S_BV1.h"//#include "BD_MST_MST9570S.h"
#elif (MainBoardType == MainBoard_JRY_WQ570)
#define USEFLASH    1
#include "bd_WQ570.h"
#elif (MainBoardType == MainBoard_JRY_W8787_BV1)
#define USEFLASH    1
#include "bd_W8787_BV1.h"
#elif (MainBoardType == MainBoard_L38CDMT9_GV1)
#define USEFLASH    1
#include "bd_L38CDMT9_GV1.h"
#elif (MainBoardType == MainBoard_JRY_L8787_BV1)
#define USEFLASH    1
#include "bd_JRY_L8787_BV1.h"
#elif (MainBoardType == MainBoard_JRY_L58CDT9_NV1)
#define USEFLASH    1
#include "bd_L58CDT9_NV1.h"
#elif (MainBoardType == MainBoard_JRY_L58VHN_GV3)
#define USEFLASH    1
#include "bd_L58VHN_GV3.h"
#elif (MainBoardType == MainBoard_JRY_W58CDT9_GV3)
#define USEFLASH    1
#include "bd_JRY_W58CDT9_GV3.h"
#elif (MainBoardType == MainBoard_JRY_L58CDT9_EV1)
#define USEFLASH    1
#include "bd_JRY_L58CDT9_EV1.h"
#elif (MainBoardType == MainBoard_JRY_L58CDT9_PV1)
#define USEFLASH    1
#include "bd_JRY_L58CDT9_PV1.h"
#elif (MainBoardType == MainBoard_TSUMO58FDT9_1)
#define USEFLASH    1
#include "bd_TSUMO58FDT9_1.h"
#elif (MainBoardType == MainBoard_JRY_W58CDT9_AV6)
#define USEFLASH    1
#include "bd_L58CDT9_AV6.h"
#elif (MainBoardType == MainBoard_JRY_L58CDT9_BV2)
#define USEFLASH    1
#include "bd_L58CDT9_BV2.h"
#elif (MainBoardType == MainBoard_JRY_L58CDT9_LV1)
#define USEFLASH    1
#include "bd_L58CDT9_LV1.h"
#elif (MainBoardType == MainBoard_XY_W58CDT9_AV7)
#define USEFLASH    1
#include "bd_XY_W58CDT9_AV7.h"
#elif (MainBoardType == MainBoard_JRY_L9BQHD_AV1)
#define USEFLASH    1
#include "bd_JRY_L9BQHD_AV1.h"
#elif (MainBoardType == MainBoard_JRY_F9BQHD_BV1)
#define USEFLASH    1
#include "bd_JRY_F9BQHD_BV1.h"
#elif (MainBoardType == MainBoard_JRY_L5AFHD_EV1)
#define USEFLASH    1
#include "bd_JRY_L5AFHD_EV1.h"
#elif (MainBoardType == MainBorad_JRY_L5AFHD_FV1)
#define USEFLASH    1
#include "bd_JRY_L5AFHD_FV1.h"
#elif (MainBoardType == MainBorad_JRY_L58CDT9_GV2)
#define USEFLASH    1
#include "bd_JRY_L58CDT9_GV2_XJH.h"
#elif (MainBoardType == MainBorad_JRY_L58CDT9_GV3)
#define USEFLASH    1
#include "bd_JRY_L58CDT9_GV3.h"
#elif (MainBoardType == MainBoard_JRY_F5DFHD_AV1)
#define USEFLASH    1
#include "bd_JRY_F5DFHD_AV1.h"


#elif (MainBoardType == MainBoard_JRY_W58CDT9_AV7)
#define USEFLASH    1
#include "bd_JRY_W58CDT9_AV7.h"
#endif



#ifndef ENABLE_DP_INPUT
#define ENABLE_DP_INPUT 0
#endif



#if CHIP_ID==CHIP_TSUMB || CHIP_ID==CHIP_TSUMY
#define USE_ADC_DVI_INT             1
#else
#define USE_ADC_DVI_INT             0
#endif


#ifndef ENABLE_SUPERRESOLUTION
#define ENABLE_SUPERRESOLUTION 0
#endif


//#define HDMI_RB_SWAP                                0
//#define HDMI_PN_SWAP					0

// 120106 coding addition, default set adc dithering to disable
#ifndef ENABLE_ADC_DITHERING
#define ENABLE_ADC_DITHERING    0
#endif

//I_Gen_Tuning Target Select

#if (CHIP_ID == CHIP_TSUMY)||(CHIP_ID == CHIP_TSUMU)//20130418 from BJ
#define IGT_TARGET_250  0
#define IGT_TARGET_300  1
#define IGT_TARGET_350  2
#define IGT_TARGET_200  3
#elif (CHIP_ID == CHIP_TSUMC)||(CHIP_ID == CHIP_TSUMD||CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF) // 130530 JUN Modify
#define IGT_TARGET_250  0
#define IGT_TARGET_350  1
#define IGT_TARGET_300  2
#define IGT_TARGET_200  3
#else
#define IGT_TARGET_250  0
#define IGT_TARGET_300  1
#define IGT_TARGET_200  2
#define IGT_TARGET_350  3
#endif
//I_Gen_Tuning CH Source Select

#if (CHIP_ID == CHIP_TSUMC)||(CHIP_ID == CHIP_TSUMD) ||(CHIP_ID == CHIP_TSUM9)||(CHIP_ID == CHIP_TSUMF)
#define CH2             0
#define CH6             1
#define CH8             2
#else
#define CH3_CLK         0
#define CH9_CLK         1
#define CH15_CLK        2
#define CH21_CLK        3
#endif

//LVDS_CHANNEL select
#define MOD_PORTA       BIT0
#define MOD_PORTB       BIT1
#define MOD_PORTC       BIT2
#define MOD_PORTD       BIT3

//TMDS PORT
#define TMDS_PORT_UNUSE 0
#define TMDS_PORT_A     BIT0
#define TMDS_PORT_B     BIT1
#define TMDS_PORT_C     BIT2

//OD mode
#if (CHIP_ID == CHIP_TSUMC)
#define OD_MODE_444             0
#define OD_MODE_565             1
#define OD_MODE_666             4
#define OD_MODE_485             5
#define OD_MODE_555             6
#define OD_MODE_888             7
#elif (CHIP_ID == CHIP_TSUMF)
#define OD_MODE_444             0
#define OD_MODE_565             1
#define OD_MODE_666             4
#define OD_MODE_485        		5
#define OD_MODE_555             6
#elif (CHIP_ID == CHIP_TSUMU)
//Junior does not support 444 mode
#define OD_MODE_444             0
#define OD_MODE_565             1
#define OD_MODE_333             5   //compress mode
#define OD_MODE_555             6
#else
#if CHIP_ID != CHIP_TSUMD            //Junior does not support 444 mode
#define OD_MODE_444             0
#endif
#define OD_MODE_565             1
#define OD_MODE_333             5   //compress mode
#define OD_MODE_555             6
#endif






#define OD_HSCAL_EN     _ENABLE	//130607 nick

#if (CHIP_ID == CHIP_TSUMF)
#define OD_VSCAL_EN             _ENABLE
#else
#define OD_VSCAL_EN             _DISABLE
#endif


#ifndef OD_MODE
#if CHIP_ID == CHIP_TSUMC ||(CHIP_ID == CHIP_TSUMF)
#define OD_MODE                                         OD_MODE_485
#else
#define OD_MODE                                         OD_MODE_333
#endif
#endif

////////////////////////////////////////////////////////
// Frame buffer setting
////////////////////////////////////////////////////////
#define FRAME_BUFFER        0
#define FRAME_BFFLESS       1

#if 1 // 120525 coding modified


#ifndef ENABLE_RTE
#define ENABLE_RTE        0
#endif

#ifndef ENABLE_4step_OD  // For gaming model request add 4 step OD table
#define ENABLE_4step_OD 0
#endif

#else
#ifndef FRAME_BFF_SEL
#if CHIP_ID==CHIP_TSUMU
#define FRAME_BFF_SEL    	FRAME_BFFLESS//   FRAME_BUFFER
#define ENABLE_RTE        1
#elif CHIP_ID==CHIP_TSUM2
#define FRAME_BFF_SEL       FRAME_BUFFER
//#define ENABLE_RTE        0
#else
#define FRAME_BFF_SEL  	FRAME_BFFLESS
#define ENABLE_RTE        0
#endif
#endif
#endif

#if CHIP_ID==CHIP_TSUMU
#define PANEL_H_DIV             2 // H relative parameters(display timing) divided by 1 or 2
#define DOWN_COUNTER_V_SYNC     ((FRAME_BFF_SEL == FRAME_BFFLESS)?0:1)
//#define DOWN_COUNTER_V_SYNC     1
#else
#define PANEL_H_DIV             1 // H relative parameters(display timing) divided by 1 or 2
#define DOWN_COUNTER_V_SYNC     0
#endif

#ifndef ENABLE_MHL_COUNT
#define ENABLE_MHL_COUNT    0
#endif
#ifndef ENABLE_FPS_RTS
#define ENABLE_FPS_RTS                  0
#endif


#if CHIP_ID == CHIP_TSUM2 ||CHIP_ID == CHIP_TSUMC ||CHIP_ID == CHIP_TSUMD ||CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF
#define ENABLE_SW_DOUBLE_BUFFER   1
#else
#define ENABLE_SW_DOUBLE_BUFFER   0
#endif

#ifndef ENABLE_HK_CODE_ON_DRAM
#define ENABLE_HK_CODE_ON_DRAM  0
#endif



#ifndef _TMDS_DE_MODE_EN_
#define _TMDS_DE_MODE_EN_   1
#endif

#define EN_V4TAP_SCALING    	0 //(CHIP_ID==CHIP_TSUMB || CHIP_ID==CHIP_TSUMY) //for vertical 4-tap scaling mode

#define EXT_TIMER0_1MS          0       // external timer 0 for 1ms interrupt
#ifndef ENABLE_3D_FUNCTION
#define ENABLE_3D_FUNCTION  	0
#endif
#ifndef I2CKEY_TYPE//petit 20130314
#define I2CKEY_TYPE  	I2CKEY_NONEUSE
#endif

#ifndef Enable_CheckVcc5V
#define Enable_CheckVcc5V  	0
#endif


// 3D glasses type
#define GLASSES_NONE    0
#define GLASSES_IR      1
#define GLASSES_INTEL   2
#define GLASSES_NVIDIA  3

#ifndef GLASSES_TYPE
#define GLASSES_TYPE          GLASSES_NONE
#endif

#ifndef MST_ASSERT
#define MST_ASSERT(_test_)
#endif

#if ( (CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF) && ENABLE_XTAL_LESS)
#define XTAL_CLOCK_KHZ              (12000ul)
#define CRYSTAL_CLOCK               (12000000ul)
#else
#define XTAL_CLOCK_KHZ              (14318ul)
#define CRYSTAL_CLOCK               (14318000ul)
#endif

// 110905 coding, addition for getting more V to reduce output dclk
#define DECREASE_V_SCALING  1
#define INT_PERIOD		1// timer interrupt: unit = 1ms
//#define BaudRatePeriod	(0x10000 - (((unsigned long)CPU_CLOCK_MHZ * 1000000)/((unsigned long) SERIAL_BAUD_RATE / 10 * 32) + 5) / 10)
#define SystemTick		1000	// 1 second
#define UseINT			1
#define UsesRGB			0
#define ClockPeriod 	(0x10000-(((unsigned long)XTAL_CLOCK_KHZ*INT_PERIOD)/12))    // Interrupt every 1ms for Time 0
#define BaudRatePeriod  (0x10000-(((unsigned long)XTAL_CLOCK_KHZ * 1000+(DWORD)SERIAL_BAUD_RATE*16)/((DWORD)SERIAL_BAUD_RATE*32)))
#define T1BaudRatePeriod    (0x100-(((unsigned long)XTAL_CLOCK_KHZ * 1000+(DWORD)SERIAL_BAUD_RATE*192)/((DWORD)SERIAL_BAUD_RATE*384)))
#define HFreq(hPeriod)  (((DWORD)XTAL_CLOCK_KHZ*10+hPeriod/2)/hPeriod)
#define VFreq(hFreq, vTotal)    ((((DWORD)hFreq*1000+SrcVTotal/2)/SrcVTotal))
#define MST_HPeriod_UINT    (XTAL_CLOCK_KHZ*16)
#define VFreqIn         (((VFreq( HFreq( SrcHPeriod ), SrcVTotal )+5)/10) * ((SrcFlags&bInterlaceMode)?2:1))

// define wait for checking
#define _IP_POWER_CTRL_

////////////////////////////////////////////////////////////
// TSUM9 AC POWER ON FLAG
////////////////////////////////////////////////////////////
#if (CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF)
#define AC_POWER_ON_FLAG    (_bit7_(MEM_MSREAD_BYTE(REG_0183)))
#if !ENABLE_MHL
#define _BIT(a)                         (BIT0 << a)
#define MASKBIT(a)                      (_BIT((1?a) +1) -_BIT((0?a)))
#define MASKSET(a, b, c)                ((a &~c) | (b &c))
#define ABS_MINUS(a, b)                 ((a > b)? (a -b): (b -a))

#endif
#endif


#ifndef ENABLE_WATCH_DOG
#define ENABLE_WATCH_DOG         	0
#define WATCH_DOG_RESET_TIME    (5)   // unit: second
#endif

#ifndef MS_VGA_SOG_EN
#define MS_VGA_SOG_EN            	0
#endif

#ifndef ENABLE_TOUCH_PANEL_CTRL
#define ENABLE_TOUCH_PANEL_CTRL     0
#endif

#ifndef ENABLE_ADC_RESET
#define ENABLE_ADC_RESET   1
#endif

#ifndef CABLE_DETECT_VGA_USE_SAR
#define CABLE_DETECT_VGA_USE_SAR    0
#endif

#ifndef CABLE_DETECT_DVI_USE_SAR
#define CABLE_DETECT_DVI_USE_SAR    0
#endif

#ifndef CABLE_DETECT_HDMI_USE_SAR
#define CABLE_DETECT_HDMI_USE_SAR   0
#endif

#ifndef EANBLE_MUTE_ON_OFF
#define EANBLE_MUTE_ON_OFF                 1
#endif


#endif


