#ifndef TSUMXXD_DEMO_H
#define TSUMXXD_DEMO_H
////////////////////////////////////////////////////////////
// BOARD SELECTION
////////////////////////////////////////////////////////////
#define CHIP_ID     CHIP_TSUMD
#define MainBoardType   MainBoard_TSUML887DS_1//MainBoard_TSUML88CMC2, MainBoard_TSUML887DC4_1, MainBoard_TSUMP387MT9_1, MainBoard_TSUMP387MT9_1_DP, MainBoard_tsuml88bdc2_1

////////////////////////////////////////////////////////////
// INPUT_TYPE SELECTION
////////////////////////////////////////////////////////////
#define DVI_PN_SWAP                     1
#define HDMI_PN_SWAP                    1
#define ENABLE_AUTOEQ                   0
#if MainBoardType == MainBoard_TSUML887DS_1
#ifdef FPGA
#define INPUT_TYPE                      INPUT_1A//HDMI+DP
#define ENABLE_HDMI                     0//((Input_HDMI_C1 != Input_Nothing)||(Input_HDMI_C2 != Input_Nothing)||(Input_HDMI_C3 != Input_Nothing))
#define ENABLE_HDMI_1_4                 0
#define ENABLE_MHL_C1                   0
#define ENABLE_MHL_C2                   0
#define ENABLE_MHL_C3                   0
#define ENABLE_MHL                      0//(ENABLE_MHL_C1|ENABLE_MHL_C2|ENABLE_MHL_C3)
#define ENABLE_DVI                      0//((Input_DVI_C1 != Input_Nothing)||(Input_DVI_C2 != Input_Nothing)||(Input_DVI_C3 != Input_Nothing))
#define ENABLE_DP_INPUT                 0//((Input_Displayport_C2 != Input_Nothing)||(Input_Displayport_C3 != Input_Nothing))

#else
#define INPUT_TYPE                      INPUT_1A2C//HDMI+DP
#define ENABLE_HDMI                     1//((Input_HDMI_C1 != Input_Nothing)||(Input_HDMI_C2 != Input_Nothing)||(Input_HDMI_C3 != Input_Nothing))
#define ENABLE_HDMI_1_4                 1
#define ENABLE_MHL_C1                   1
#define ENABLE_MHL_C2                   0
#define ENABLE_MHL_C3                   0
#define ENABLE_MHL                      (ENABLE_MHL_C1|ENABLE_MHL_C2|ENABLE_MHL_C3)
#define ENABLE_DVI                      0//((Input_DVI_C1 != Input_Nothing)||(Input_DVI_C2 != Input_Nothing)||(Input_DVI_C3 != Input_Nothing))
#define ENABLE_DP_INPUT                 1//((Input_Displayport_C2 != Input_Nothing)||(Input_Displayport_C3 != Input_Nothing))
#endif
#else
#message "please define Junior new board type for Port_Func_Enable"
#endif

#define MS_VGA_SOG_EN               1// confirmed
//#define _NEW_SOG_WAKEUP_DET_

//#define ENABLE_RTE  1

////////////////////////////////////////////////////////////
// PANEL SELECTION
////////////////////////////////////////////////////////////
#ifdef FPGA
#define PanelType                         PanelAU20SVGA//PanelCMIM236HGJ_L21//PanelAU20SVGA // 800x600
#else
#define PanelType                         PanelCMIM236HGJ_L21//PanelLM230WF5TLD1//PanelLM220WE1//PanelTPM215HW01_HGE//PanelLM230WF5TLD1//PanelLM270WF4TLA1
#endif
////////////////////////////////////////////////////////////
// BRIGHTNESS CONTROL
////////////////////////////////////////////////////////////
#define BrightFreqByVfreq               1 // set brightness freq. by input Vfreq.
#define BRIGHTNESS_INVERSE          0
#define BRIGHTNESS_FREQ                     240 // unit: Hz
#define BRIGHTNESS_VSYNC_ALIGN       1
////////////////////////////////////////////////////////////

// AUDIO
////////////////////////////////////////////////////////////
#define AudioFunc                           1
#define VOLUME_INVERSE                  0
#define VOLUME_FREQ                        30000 // unit: Hz
#define VOLUME_VSYNC_ALIGN              0

////////////////////////////////////////////////////////////
// OSD
////////////////////////////////////////////////////////////
#define DisplayLogo                         NoBrand
#define LANGUAGE_TYPE                   ASIA//SIXTEEN

////////////////////////////////////////////////////////////
// SYSTEM
////////////////////////////////////////////////////////////
#define AUTO_DATA_PATH   0
#define ENABLE_DSC  1
#define FACTORYALIGN_TYPE               FACTORYALIGN_DDCCI

#define ENABLE_POWEROFF_1X_MCU_CLK          0


#define ENABLE_FACTORY_SSCADJ           1
#if INPUT_TYPE > INPUT_1A
#define ENABLE_HDCP                     1
#define HDCPKEY_IN_Flash                1
#else
#define ENABLE_HDCP                     0
#define HDCPKEY_IN_Flash                0
#endif


//#define ENABLE_HK_DATA_ON_DRAM    1

#define ENABLE_TOUCH_PANEL     0
#define ENABLE_TOUCH_PANEL_DATA_FROM_USB     0
#define ENABLE_TOUCH_PANEL_CTRL_OSD     0

#define ENABLE_POWER_BOARD_CONTROL  0 // control power board enter to saving mode

// 120410 coding test for touch key
//#define ENABLE_TOUCH_KEY    1
//#define TOUCH_KEY_CTRL_LED  1
////////////////////////////////////////////////////////////
// POWERMANAGEMENT
////////////////////////////////////////////////////////////
#define MS_PM                                   0
#define PM_MCUSLEEP                     0
#define LED_PWM                             0

////////////////////////////////////////////////////////////
// SI
////////////////////////////////////////////////////////////
#define ODM_NAME                    ODM_AOC

////////////////////////////////////////////////////////////
// INFORMATION
////////////////////////////////////////////////////////////
#define ChipName                            "TSUMD"
#define Model                               "XXXXXXXXX"
#define FWVersion                           "000"
#define ChangeDate                          "20120612"

///////////////////////////////////////////////////////////////
// SYSTEM DEBUG
//////////////////////////////////////////////////////////////
//#define HDCPKEY_USE_CODE    1
#define DISABLE_AUTO_SWITCH     0 // for MHL test

///////////////////////////////////////////////////////////////
#define ENABLE_3DLUT           0
#define ENABLE_DP_AUDIO   0

#endif

