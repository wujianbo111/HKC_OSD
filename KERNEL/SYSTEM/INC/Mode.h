//#include "board.h"
//#include "global.h"
#define bVSyncNegative			BIT0
#define bHSyncNegative			BIT1
#define bHSyncLoss			    BIT2
#define bVSyncLoss			    BIT3
#define bInterlaceMode			BIT4
#define bUnsupportMode			BIT5
#define bUserMode		   	    BIT6
#define bNativeMode			BIT7
#define bShrinkMode			BIT7

#ifndef SHARP_VGA_50Hz_Timing
#define SHARP_VGA_50Hz_Timing 		1
#endif

enum
{
	IP_MUX_ADC,
	IP_MUX_DVI_A,
	IP_MUX_DVI_B,
	IP_MUX_DP_A,
	IP_MUX_DP_B,
	IP_MUX_RESERVE_D,
	IP_MUX_RESERVE_E,
	IP_MUX_RESERVE_F,
	IP_MUX_RESERVE_G,
	IP_MUX_RESERVE_H,
	IP_MUX_RESERVE_I,
	IP_MUX_RESERVE_J,
};

enum
{
	CLK_ADC_BUFF_DIV2,
	CLK_DVI_BUFF_DIV2,
	DP_STRM_CLK,
	CLK_DVI_BUFF,

};


#if 			0
/*
typedef enum
{
#if INPUT_TYPE == INPUT_1A
        Input_ANALOG,
        Input_Nums,
        Input_Digital,
        Input_Digital2,
        Input_VGA = Input_ANALOG,
        Input_DVI = Input_Nums,
        Input_HDMI = Input_Nums,
        Input_Displayport = Input_Nums,

        Input_DVI2 = Input_Nums,
        Input_DVI3 = Input_Nums,
        Input_HDMI2 = Input_Nums ,
        Input_HDMI3 = Input_Nums ,
        Input_Displayport2=Input_Nums,
        Input_Displayport3  = Input_Nums,
        Input_TMDS_Nums = 0,
#elif INPUT_TYPE == INPUT_1H
			Input_Digital,
			Input_Nums,
	        Input_ANALOG,
			Input_Digital2,
			Input_Nothing,
			Input_VGA = Input_Nums,
			Input_DVI = Input_Nums,
			Input_HDMI = Input_Digital,
			Input_Displayport = Input_Nums,

			Input_DVI2 = Input_Nums,
			Input_DVI3 = Input_Nums,
			Input_HDMI2 = Input_Nums ,
			Input_HDMI3 = Input_Nums ,
			Input_Displayport2=Input_Nums,
			Input_Displayport3	= Input_Nums,
			Input_TMDS_Nums = 0,

#elif INPUT_TYPE == INPUT_1A1D

    #if CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD ||CHIP_ID==CHIP_TSUM9||CHIP_ID==CHIP_TSUMF
        Input_ANALOG,
        Input_Digital,
        Input_Nums,
        Input_Digital2,
        Input_Nothing,
        Input_VGA = Input_ANALOG,
        Input_DVI = Input_Digital,
        Input_DVI2 = Input_Nums,
        Input_DVI3 = Input_Nums,
        Input_HDMI1 = Input_Nums ,
        Input_HDMI2 = Input_Nums ,
        Input_HDMI3 = Input_Nums ,
        Input_Displayport2=Input_Nums,
        Input_Displayport3  = Input_Nums,
        Input_HDMI = Input_Nums,
        Input_Displayport = Input_Nums,
        Input_TMDS_Nums = 1,
   #else
        Input_ANALOG,
        Input_Digital,
        Input_Nums,
        Input_Digital2,
        Input_VGA = Input_ANALOG,
        Input_DVI = Input_Digital,
        Input_HDMI = Input_Nums,
        Input_Displayport = Input_Nums,
       Input_DVI2 = Input_Nums,
       Input_DVI3 = Input_Nums,
       Input_HDMI2 = Input_Nums ,
       Input_HDMI3 = Input_Nums ,
       Input_Displayport2=Input_Nums,
       Input_Displayport3  = Input_Nums,
        Input_TMDS_Nums = 1,
   #endif
#elif INPUT_TYPE == INPUT_1A2D
        Input_ANALOG,
        Input_Digital,
        Input_Digital2,
        Input_Nums,
        Input_VGA = Input_ANALOG,
        Input_DVI = Input_Digital,
        Input_HDMI = Input_Digital2,
        Input_Displayport = Input_Nums,

        Input_DVI2 = Input_Nums,
        Input_DVI3 = Input_Nums,
        Input_HDMI2 = Input_Nums ,
        Input_HDMI3 = Input_Nums ,
        Input_Displayport2=Input_Nums,
        Input_Displayport3  = Input_Nums,
        Input_TMDS_Nums = 2,
#elif INPUT_TYPE == INPUT_1A1D1H
#if CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD ||CHIP_ID==CHIP_TSUM9

        Input_ANALOG,
        Input_Digital,
        Input_Digital2,
        Input_Nums,
        Input_Digital3,
        Input_Nothing,

        Input_VGA           = Input_ANALOG,
        Input_DVI            = Input_Digital,//Input_Nothing,//Input_Digital2,
        Input_DVI2          =Input_Nothing,// Input_DVI_C2,
        Input_DVI3          = Input_Nothing,
        Input_HDMI         = Input_Nothing,
        Input_HDMI2       = Input_Digital2,
        Input_HDMI3       = Input_Nothing,
        Input_Displayport =Input_Nothing,
        Input_Displayport2=Input_Nothing,
		Input_Displayport3=Input_Nothing,
        Input_TMDS_Nums = 2,
#else
        Input_ANALOG,
        Input_Digital,
        Input_Digital2,
        Input_Nums,
	    Input_Nothing=Input_Nums,
        Input_VGA = Input_ANALOG,
        Input_DVI = Input_Digital,
        Input_HDMI = Input_Digital2,
        Input_Displayport = Input_Nums,

        Input_DVI2 = Input_Nums,
        Input_DVI3 = Input_Nums,
        Input_HDMI2 = Input_Nums ,
        Input_HDMI3 = Input_Nums ,
        Input_Displayport2=Input_Nums,
        Input_Displayport3  = Input_Nums,
        Input_TMDS_Nums = 2,
#endif
#elif INPUT_TYPE == INPUT_1A2H

    #if CHIP_ID==CHIP_TSUMC ||CHIP_ID==CHIP_TSUM9||CHIP_ID==CHIP_TSUMF
        Input_ANALOG,
        Input_Digital,
        Input_Digital2,
        Input_Nums,
        Input_Nothing,
        Input_VGA = Input_ANALOG,
        Input_DVI = Input_Nothing,
        Input_HDMI = Input_Digital,
        Input_DVI1 = Input_Nothing,
        Input_DVI2 = Input_Digital2,
        Input_DVI3 = Input_Nothing,
        Input_HDMI1 = Input_Digital ,
        Input_HDMI2 = Input_Digital2 ,
        Input_HDMI3 = Input_Nothing ,
        Input_Displayport2=Input_Nothing,
        Input_Displayport3  = Input_Nothing,
        Input_Displayport = Input_Nums,
        Input_TMDS_Nums = 2,
    #elif CHIP_ID==CHIP_TSUMD

        Input_ANALOG,
        Input_Digital,
        Input_Digital2,
        Input_Nums,
        Input_Digital3,
        Input_Nothing,

        Input_VGA           = Input_ANALOG,
        Input_DVI            = Input_Nothing,//Input_Digital,//Input_Nothing,//Input_Digital2,	//130607 nick
        Input_DVI2          =Input_Nothing,// Input_DVI_C2,
        Input_DVI3          = Input_Nothing,
        Input_HDMI         = Input_Digital,
        Input_HDMI2       = Input_Nothing,
        Input_HDMI3       = Input_Digital2,
        Input_Displayport =Input_Nothing,
        Input_Displayport2=Input_Nothing,
        Input_Displayport3  = Input_Nothing,
        Input_TMDS_Nums = 2,

   #else
        Input_ANALOG,
        Input_Digital,
        Input_Digital2,
        Input_Nums,
        Input_VGA = Input_ANALOG,
        Input_DVI = Input_Digital,
        Input_HDMI = Input_Digital2,
        Input_Displayport = Input_Nums,


        Input_DVI2 = Input_Nums,
        Input_DVI3 = Input_Nums,
        Input_HDMI2 = Input_Nums ,
        Input_HDMI3 = Input_Nums ,
        Input_Displayport2=Input_Nums,
        Input_Displayport3  = Input_Nums,
        Input_TMDS_Nums = 2,
   #endif
 #elif INPUT_TYPE == INPUT_2H

    #if CHIP_ID==CHIP_TSUMC ||CHIP_ID==CHIP_TSUM9||CHIP_ID==CHIP_TSUMF
    	Input_Digital,
    	Input_Digital2,
    	Input_Nums,
    	Input_ANALOG,
    	Input_Nothing,
    	Input_VGA = Input_Nothing,
    	Input_DVI = Input_Nothing,
    	Input_HDMI = Input_Digital,
    	Input_DVI1 = Input_Nothing,
    	Input_DVI2 = Input_Digital2,
    	Input_DVI3 = Input_Nothing,
    	Input_HDMI1 = Input_Digital ,
    	Input_HDMI2 = Input_Digital2 ,
    	Input_HDMI3 = Input_Nothing ,
    	Input_Displayport2=Input_Nothing,
    	Input_Displayport3	= Input_Nothing,
    	Input_Displayport = Input_Nums,
    	Input_TMDS_Nums = 2,

   #else
        Input_Digital,
        Input_Digital2,
        Input_Nums,
	    Input_ANALOG,
		Input_Nothing,
        Input_VGA = Input_Nothing,
        Input_DVI = Input_Digital,
        Input_HDMI = Input_Digital2,
        Input_Displayport = Input_Nums,
        Input_DVI2 = Input_Nums,
        Input_DVI3 = Input_Nums,
        Input_HDMI2 = Input_Nums ,
        Input_HDMI3 = Input_Nums ,
        Input_Displayport2=Input_Nums,
        Input_Displayport3  = Input_Nums,
        Input_TMDS_Nums = 2,
   #endif
#elif INPUT_TYPE == INPUT_1A1H
 	#if CHIP_ID==CHIP_TSUMC || CHIP_ID==CHIP_TSUMD || CHIP_ID==CHIP_TSUM9|| CHIP_ID==CHIP_TSUMF
	#if ( MainBoardType ==  MainBoard_JRY_L58CDT9_EV1)
		Input_ANALOG,
		Input_Digital,
		Input_Nums,
		Input_Digital2,
		Input_Nothing,
		Input_VGA = Input_ANALOG,
		Input_DVI = Input_Nothing,
		Input_DVI2 = Input_Nothing,
		Input_DVI3 = Input_Nothing,
		Input_HDMI1 = Input_Nothing ,
		Input_HDMI2 = Input_Digital ,
		Input_HDMI3 = Input_Nothing ,
		Input_Displayport2=Input_Nothing,
		Input_Displayport3	= Input_Nothing,
		Input_HDMI = Input_Nums,
		Input_Displayport = Input_Nums,
		Input_TMDS_Nums = 1
	#else
		Input_ANALOG,
		Input_Digital,
		Input_Nums,
		Input_Digital2,
		Input_Nothing,
		Input_VGA = Input_ANALOG,
		Input_DVI = Input_Nothing,
		Input_DVI2 = Input_Nothing,
		Input_DVI3 = Input_Nothing,
		Input_HDMI1 = Input_Nothing ,
		Input_HDMI2 = Input_Digital ,
		Input_HDMI3 = Input_Nothing ,
		Input_Displayport2=Input_Nothing,
		Input_Displayport3  = Input_Nothing,
		Input_HDMI = Input_Digital,
		Input_Displayport = Input_Nums,
		Input_TMDS_Nums = 1
	#endif
	#else
        Input_ANALOG,
        Input_Digital,
        Input_Nums,
        Input_Digital2,
        Input_VGA = Input_ANALOG,
        Input_DVI = Input_Nums,
        Input_HDMI = Input_Digital,
        Input_Displayport = Input_Nums,

        Input_DVI2 = Input_Nums,
        Input_DVI3 = Input_Nums,
        Input_HDMI2 = Input_Nums ,
        Input_HDMI3 = Input_Nums ,
        Input_Displayport2=Input_Nums,
        Input_Displayport3  = Input_Nums,
        Input_TMDS_Nums = 1,
    #endif
#elif INPUT_TYPE == INPUT_1A1D1DP
    #if CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD	//131113 fay

			Input_ANALOG,
			Input_Digital,
			Input_Displayport3,
			Input_Nums,
			Input_Digital2,
			Input_Digital3,
			Input_Nothing,

			Input_VGA			= Input_ANALOG,
			Input_DVI			 = Input_Digital,//Input_Nothing,//Input_Digital2,
			Input_DVI2			=Input_Nothing,// Input_DVI_C2,
			Input_DVI3			= Input_Nothing,
			Input_HDMI		   = Input_Nothing,
			Input_HDMI2 	  = Input_Nothing,
			Input_HDMI3 	  = Input_Nothing,
			Input_Displayport =Input_Nothing,
			Input_Displayport2=Input_Nothing,
			Input_TMDS_Nums = 2,
		#elif   CHIP_ID==CHIP_TSUM9 || CHIP_ID==CHIP_TSUMF
	       	Input_ANALOG,
			Input_Digital,
			Input_Displayport3,
			Input_Nums,
			Input_Digital2,
			Input_Digital3,
			Input_Nothing,

			Input_VGA			= Input_ANALOG,
			Input_DVI			 = Input_Nothing,//Input_Nothing,//Input_Digital2,
			Input_DVI2			=Input_Nothing,// Input_DVI_C2,
			Input_DVI3			= Input_Nothing,
			Input_HDMI		   = Input_Nothing,
			Input_HDMI2 	  = Input_Nothing,
			Input_HDMI3 	  = Input_Nothing,
			Input_Displayport =Input_Digital,
			Input_Displayport2=Input_Nothing,
			Input_TMDS_Nums = 2,
    #else
			Input_ANALOG,
			Input_Digital,
			Input_Displayport,
			Input_Nums,
			Input_Digital2,
			Input_VGA = Input_ANALOG,
			Input_DVI = Input_Digital,
			Input_HDMI = Input_Digital2,

			Input_DVI2 = Input_Nums,
			Input_DVI3 = Input_Nums,
			Input_HDMI2 = Input_Nums ,
			Input_HDMI3 = Input_Nums ,
			Input_Displayport2=Input_Nums,
			Input_Displayport3	= Input_Nums,
			Input_TMDS_Nums = 2,
     #endif
#elif INPUT_TYPE == INPUT_1A1DP
    #if CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD||CHIP_ID==CHIP_TSUMU	//20151126 Alpha

				 Input_ANALOG,
				 Input_Digital,
				 Input_Nums,
				 Input_Digital2,
				 Input_Digital3,
				 Input_Nothing,

				 Input_VGA			 = Input_ANALOG,
				 Input_DVI			  = Input_Nothing,//Input_Nothing,//Input_Digital2,
				 Input_DVI2 		 =Input_Nothing,// Input_DVI_C2,
				 Input_DVI3 		 = Input_Nothing,
				 Input_HDMI 		= Input_Nothing,
				 Input_HDMI2	   = Input_Nothing,
				 Input_HDMI3	   = Input_Nothing,
				 Input_Displayport =Input_Digital,
				 Input_Displayport2=Input_Nothing,
                 Input_Displayport3	= Input_Nothing,
				 Input_TMDS_Nums = 2,
		#elif   CHIP_ID==CHIP_TSUM9 ||CHIP_ID==CHIP_TSUMF
				 Input_ANALOG,
				 Input_Digital,
				 Input_Nums,
				 Input_Digital2,
				 Input_Digital3,
				 Input_Nothing,

				 Input_VGA			 = Input_ANALOG,
				 Input_DVI			  = Input_Nothing,//Input_Nothing,//Input_Digital2,
				 Input_DVI2 		 =Input_Nothing,// Input_DVI_C2,
				 Input_DVI3 		 = Input_Nothing,
				 Input_HDMI 		= Input_Nothing,
				 Input_HDMI2	   = Input_Nothing,
				 Input_HDMI3	   = Input_Nothing,
				 Input_Displayport =Input_Digital,
				 Input_Displayport2=Input_Nothing,
		         Input_Displayport3	= Input_Nothing,
				 Input_TMDS_Nums = 2,
    #else
				 Input_ANALOG,
				 Input_Digital,
				 Input_Nums,
				 Input_Digital2,
				 Input_VGA = Input_ANALOG,
				 Input_DVI = Input_Nothing,
				 Input_HDMI = Input_Nothing,

				 Input_DVI2 = Input_Nums,
				 Input_DVI3 = Input_Nums,
				 Input_HDMI2 = Input_Nums ,
				 Input_HDMI3 = Input_Nums ,
	             Input_Displayport=Input_Digital,
				 Input_Displayport2=Input_Nums,
				 Input_Displayport3  = Input_Nums,
				 Input_TMDS_Nums = 2,
     #endif

#elif INPUT_TYPE == INPUT_1A2H1DP

    #if CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD ||CHIP_ID==CHIP_TSUM9 ||CHIP_ID==CHIP_TSUMF

        Input_ANALOG,
        Input_Digital,
        Input_Digital2,
        Input_Displayport3,
        Input_Nums,
        Input_Digital3,
        Input_Nothing,

        Input_VGA           = Input_ANALOG,
        Input_DVI            = Input_Nothing,//Input_Nothing,//Input_Digital2,
        Input_DVI2          =Input_Nothing,// Input_DVI_C2,
        Input_DVI3          = Input_Nothing,
        Input_HDMI         = Input_Digital,
        Input_HDMI2       = Input_Digital2,
        Input_HDMI3       = Input_Nothing,
        Input_Displayport =Input_Nothing,
        Input_Displayport2=Input_Nothing,
        //Input_Displayport3=Input_Digital3,
        Input_TMDS_Nums = 2,
    #else

        Input_ANALOG,
        Input_Digital,
        Input_Digital2,
        Input_Displayport,
        Input_Nums,
        Input_VGA = Input_ANALOG,
        Input_DVI = Input_Nums,
        Input_HDMI = Input_Nums,

        Input_DVI2 = Input_Nums,
        Input_DVI3 = Input_Nums,
        Input_HDMI2 = Input_Digital ,
        Input_HDMI3 = Input_Digital2 ,
        Input_Displayport2=Input_Nums,
        Input_Displayport3  = Input_Nums,
        Input_TMDS_Nums = 3,

     #endif
#elif INPUT_TYPE == INPUT_2H1DP

    #if CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD ||CHIP_ID==CHIP_TSUM9 ||CHIP_ID==CHIP_TSUMF

        Input_Digital,
        Input_Digital2,
        Input_Displayport3,
        Input_Nums,
          Input_ANALOG,
        Input_Digital3,
        Input_Nothing,

        Input_VGA           = Input_ANALOG,
        Input_DVI            = Input_Nothing,//Input_Nothing,//Input_Digital2,
        Input_DVI2          =Input_Nothing,// Input_DVI_C2,
        Input_DVI3          = Input_Nothing,
        Input_HDMI         = Input_Digital,
        Input_HDMI2       = Input_Digital2,
        Input_HDMI3       = Input_Nothing,
        Input_Displayport =Input_Nothing,
        Input_Displayport2=Input_Nothing,
        //Input_Displayport3=Input_Digital3,
        Input_TMDS_Nums = 2,
    #else

        Input_Digital,
        Input_Digital2,
        Input_Displayport,
        Input_Nums,
         Input_ANALOG,
        Input_VGA = Input_ANALOG,
        Input_DVI = Input_Nums,
        Input_HDMI = Input_Digital,

        Input_DVI2 = Input_Nums,
        Input_DVI3 = Input_Nums,
        Input_HDMI2 = Input_Digital2 ,
        Input_HDMI3 = Input_Nums ,
        Input_Displayport2=Input_Nums,
        Input_Displayport3  = Input_Nums,
        Input_TMDS_Nums = 2,

     #endif
#elif INPUT_TYPE == INPUT_1D1H1DP
#if CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD ||CHIP_ID==CHIP_TSUM9 ||CHIP_ID==CHIP_TSUMF
    Input_Digital,
    Input_Digital2,
    Input_Displayport3,
    Input_Nums,
    Input_ANALOG,
    Input_Digital3,
    Input_Nothing,
    Input_VGA           = Input_ANALOG,
    Input_DVI            = Input_Nothing,//Input_Nothing,//Input_Digital2,
    Input_DVI2          =Input_Nothing,// Input_DVI_C2,
    Input_DVI3          = Input_Nothing,
    Input_HDMI         = Input_Digital,
    Input_HDMI2       = Input_Digital2,
    Input_HDMI3       = Input_Nothing,
    Input_Displayport =Input_Nothing,
    Input_Displayport2=Input_Nothing,
    //Input_Displayport3=Input_Digital3,
    Input_TMDS_Nums = 1,
#else
    Input_Digital,
    Input_Digital2,
    Input_Displayport,
    Input_Nums,
    Input_ANALOG,
    Input_VGA = Input_ANALOG,
    Input_DVI = Input_Digital,
    Input_HDMI = Input_Digital2,

    Input_DVI2 = Input_Nums,
    Input_DVI3 = Input_Nums,
    Input_HDMI2 = Input_Nums ,
    Input_HDMI3 = Input_Nums ,
    Input_Displayport2=Input_Nums,
    Input_Displayport3  = Input_Nums,
    Input_TMDS_Nums = 1,
 #endif

#elif INPUT_TYPE == INPUT_1A1D1H1DP
    #if CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD ||CHIP_ID==CHIP_TSUM9 ||CHIP_ID==CHIP_TSUMF
        Input_ANALOG,
        Input_Digital,
        Input_Digital2,
        Input_Displayport3,
        Input_Nums,
        Input_Digital3,
        Input_Nothing,

        Input_VGA           = Input_ANALOG,
        Input_DVI            = Input_Nothing,//Input_Nothing,//Input_Digital2,
        Input_DVI2          =Input_Nothing,// Input_DVI_C2,
        Input_DVI3          = Input_Nothing,
        Input_HDMI         = Input_Digital,
        Input_HDMI2       = Input_Digital2,
        Input_HDMI3       = Input_Nothing,
        Input_Displayport =Input_Nothing,
        Input_Displayport2=Input_Nothing,
        //Input_Displayport3=Input_Digital3,
        Input_TMDS_Nums = 1,
    #else
        Input_ANALOG,
        Input_Digital,
        Input_Digital2,
        Input_Displayport,
        Input_Nums,
        Input_VGA = Input_ANALOG,
        Input_DVI = Input_Digital,
        Input_HDMI = Input_Digital2,

        Input_DVI2 = Input_Nums,
        Input_DVI3 = Input_Nums,
        Input_HDMI2 = Input_Nums ,
        Input_HDMI3 = Input_Nums ,
        Input_Displayport2=Input_Nums,
        Input_Displayport3  = Input_Nums,
        Input_TMDS_Nums = 1,
     #endif
#elif INPUT_TYPE == INPUT_1A1H1DP	//131031 xiandi
	#if CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD ||CHIP_ID==CHIP_TSUM9 ||CHIP_ID==CHIP_TSUMF

		Input_ANALOG,
		Input_Digital,
		Input_Displayport,
		Input_Nums,
		Input_Digital2,
		Input_Digital3,
		Input_Nothing,
		Input_VGA			= Input_ANALOG,
		Input_DVI			= Input_Nothing,
		Input_DVI1 			= Input_Nothing,
		Input_DVI2 		 	= Input_Nothing,
		Input_DVI3 		 	= Input_Nothing,
		Input_HDMI 			= Input_Nothing,
		Input_HDMI2	   		= Input_Nothing,
		Input_HDMI3	   		= Input_Digital,
		Input_Displayport2	= Input_Nothing,
		Input_Displayport3 	= Input_Nothing,
		Input_TMDS_Nums 	= 1,

	#else
		Input_ANALOG,
		Input_Digital,
		Input_Displayport,
		Input_Nums,
		Input_Digital2,
		Input_VGA = Input_ANALOG,
		Input_HDMI = Input_Nums,

		Input_DVI = Input_Nums,
		Input_DVI2 = Input_Nums,
		Input_DVI3 = Input_Nums,
		Input_HDMI2 = Input_Nums ,
		Input_HDMI3 = Input_Digital ,
		Input_Displayport2=Input_Nums,
		Input_Displayport3  = Input_Nums,
		Input_TMDS_Nums = 1,
 	#endif

#endif
}InputPortType;
*/
#else
/************************************************************************************/
#if	     0				//2 使用以下定义端口
#define INPUT_TYPE_SEL              			(INPUT_0A|INPUT_3C)
#define DVI_PORT_PRIORITY       			4 //
#define HDMI_A_PORT_PRIORITY      		4 //
#define HDMI_B_PORT_PRIORITY   			1 //
#define HDMI_C_PORT_PRIORITY   			2 //
#define DP_PORT_PRIORITY        			3 //
#endif

//1 测试功能添加

typedef enum
{
	#if (INPUT_TYPE_SEL&INPUT_0A)
	Input_ANALOG,
	#endif
	#if (INPUT_TYPE_SEL >= INPUT_1C)
	Input_DIGHTAL1,
	#endif
	#if (INPUT_TYPE_SEL >= INPUT_2C)
	Input_DIGHTAL2,
	#endif
	#if (INPUT_TYPE_SEL >= INPUT_3C)
	Input_DIGHTAL3,
	#endif
	Input_Nums,
	Input_Nothing = 0xFF,
///////////////////////////////
///////////////////////////////
	#if ENABLE_VGA_INPUT
	Input_VGA           = 	Input_ANALOG,
	#else
	Input_VGA           = 	Input_Nums,
	#endif

	#if ENABLE_DVI_INPUT
	Input_DVI          	  = 	DVI_PORT_PRIORITY,
	#else
	Input_DVI			=	Input_Nums,
	#endif

	Input_HDMI  = HDMI_A_PORT_PRIORITY,
	Input_HDMI2 = HDMI_B_PORT_PRIORITY,
	Input_HDMI3 = HDMI_C_PORT_PRIORITY,


	#if CHIP_ID>=CHIP_TSUMC
	Input_Displayport   = Input_Nums,
	Input_Displayport3  = DP_PORT_PRIORITY,
	#else
	Input_Displayport   =  DP_PORT_PRIORITY,
	Input_Displayport3  = Input_Nums,
	#endif


	Input_Digital = Input_DIGHTAL1,
	#if (INPUT_TYPE_SEL >= INPUT_2C)
	Input_Digital2 =  Input_DIGHTAL2,
	#else
	Input_Digital2 = Input_Nums,
	#endif
	#if (INPUT_TYPE_SEL >= INPUT_3C)
	Input_Digital3 = Input_DIGHTAL3,
	#else
	Input_Digital3 = Input_Nums,
	#endif

	Input_DVI2 = Input_Nums,
	Input_DVI3 = Input_Nums,
	Input_Displayport2 = Input_Nums,

	#if    (INPUT_TYPE_SEL >= INPUT_3C)
	Input_TMDS_Nums = 3,
	#elif (INPUT_TYPE_SEL >= INPUT_2C)
	Input_TMDS_Nums = 2,
	#elif (INPUT_TYPE_SEL >= INPUT_1C)
	Input_TMDS_Nums = 1,
	#else
	Input_TMDS_Nums = 0,
	#endif
} InputPortType;

#endif



typedef enum
{
	#if ENABLE_VGA_INPUT
	INPUT_PRIORITY_VGA,
	#endif
	#if ENABLE_DVI_INPUT
	INPUT_PRIORITY_DVI,		//=(DVI_PORT_PRIORITY+ENABLE_AUTO_SELECT_SOURCE),
	#endif
	#if ENABLE_HDMI_INPUT
	INPUT_PRIORITY_HDMI,	//=(HDMI_PORT_PRIORITY+ENABLE_AUTO_SELECT_SOURCE),
	#endif
	#if ENABLE_HDMI2ND_INPUT
	INPUT_PRIORITY_HDMI2ND,  //=(HDMI2ND_PORT_PRIORITY+ENABLE_AUTO_SELECT_SOURCE),
	#endif
	#if ENABLE_DPlay_INPUT
	INPUT_PRIORITY_DP,		//=(DP_PORT_PRIORITY+ENABLE_AUTO_SELECT_SOURCE),
	#endif
	#if 1//Enable_AutoInput_Menu
	INPUT_PRIORITY_AUTO,
	#endif
	INPUT_PRIORITY_NUMS,	//=(Input_Nums+ENABLE_AUTO_SELECT_SOURCE),
} InputPortPriorityType;


/************************************************************************************/


// HpVp->3,  HpVn->2, HnVp->1, HnVn->0

#define SyncHpVp 		8  // Sync Polarity
#define SyncHpVn 		4
#define SyncHnVp  		2
#define SyncHnVn  		1


#if 0
typedef enum
{
	Res_640x350,
	Res_640x400,
	Res_720x400,
	Res_640x480,
	Res_800x600,
	Res_832x624,
	Res_884x930, //0909
	Res_1024x768,
	Res_1280x1024,
	Res_1600x1200,
	Res_1152x864,
	Res_1152x870,
	Res_1280x720,
	Res_1280x960,
	Res_720x480,
	Res_800x1209,
	Res_1440x900,	// for Wide panel
	Res_1400x1050,
	Res_1680x1050,

	Max_Res
} ResolutionType;
#endif

typedef enum
{
	Res_640x350, //0
	Res_640x400,
	Res_720x400,
	Res_640x480,
	//Res_720x483, // 120424 coding reserved Res_720x483
	Res_700x570,
	Res_720x576,// 5
	Res_800x600,
	Res_832x624,
	Res_884x930, //0909
	Res_1024x768,
	Res_1280x1024, //10
	Res_1600x1200,
	Res_1152x864,
	Res_1152x870,
	Res_1280x720,
	Res_1280x960, //15
	Res_720x480,
	Res_800x1209,
	Res_1792x1344,
	Res_1400x1050,
	Res_1920x1080,//20
	Res_1920x1200,

	Res_848x480,   //2005-07-26
	Res_1280x768,  //2005-07-26
	Res_1360x768,
	Res_1366x768,//25
	Res_1440x900,

	Res_1680x1050,
	Res_1280x800,
	Res_1600x900,
	Res_1600x1024, //30

	#if  ENABLE_DUAL_LINK
	Res_640x480_2D,
	Res_800x600_2D,
	Res_1280x960_2D,
	Res_1024x768_2D,
	Res_1440x900_2D, //35

	Res_1920x1080_2D,
	Res_2560x1440,//20130801 nick
	#endif

	#if SHARP_VGA_50Hz_Timing
	Res_1152x900,
	#endif

	Max_Res
} ResolutionType;
//===20120814  for 3D mode table use ,need to check with table list===//


typedef enum
{
	MODE_848X480_60Hz_VESA,       // 0

	MODE_1280X768_60Hz_VESA_RB,
	MODE_1280X768_60Hz_VESA,
	MODE_1280X768_75Hz_VESA,
	MODE_1280X768_85Hz_VESA,
	MODE_1280x960_60Hz_VESA,     // 5

	MODE_1280x960_60Hz_VESA1,
	MODE_1280x960_70Hz_VESA,
	MODE_1280x960_72Hz_VESA,
	MODE_1280x960_75Hz_VESA,
	MODE_1280x960_85Hz_VESA,       // 10

	MODE_1360x768_60_VGA,
	MODE_1366x768_60_VESA,
	MODE_1440x900_60_VESA_RB,
	MODE_1440x900_60_VESA,
	MODE_1440x900_75_VESA,         //15

	MODE_1440x900_85_VESA,
	MODE_1680x1050_60_VESA_RB,
	MODE_1680x1050_60_VESA,
	MODE_1680x1050_75_VESA,
	MODE_640x350_70_IMB,         //20

	MODE_640x350_85_VESA,
	MODE_720x400_70_VGA,
	MODE_720x400_85_VESA,
	MODE_640x400_85_VESA,
	MODE_640x480_60_VESA,//25

	MODE_640x480_66_MAC,
	MODE_640x480_67_ATI,
	MODE_640x480_72_VESA,
	MODE_640x480_75_VESA,
	MODE_640x480_85_VESA,//30

	MODE_800x600_56_VESA,
	MODE_800x600_60_VESA,
	MODE_800x600_72_VESA,
	MODE_800x600_75_VESA,
	MODE_800x600_85_VESA, //35

	MODE_832x624_75_MAC,
	MODE_1024x768_60_VESA,
	MODE_1024x768_60_VESA1,
	MODE_1024x768_70_VESA,
	MODE_1024x768_75_VESA,    // 40

	MODE_1024x768_75_MAC,
	MODE_1024x768_85_VESA,
	MODE_1152x864_60_VESA,
	MODE_1152x864_70_VESA,
	MODE_1152x864_70_ATI,    //45


	MODE_1152x864_75_VESA,
	MODE_1152x864_85_VESA,
	MODE_1152x870_75_MAC,
	MODE_1280x720_60_VESA,
	MODE_1280x720_60_VESA1,    //50

	MODE_1280x720_70_VESA,
	MODE_1280x720_75_VESA,
	MODE_1280x1024_60_VESA,
	MODE_1280x1024_75_VESA,
	MODE_1280x1024_85_VESA,   //55


	#if 1// #ifdef PanelType_1600x900
	MODE_1600x900_60_VESA_RB,
	MODE_1600x900_60_VESA,
	MODE_1600x900_75_VESA,
	#endif
	MODE_1600x1200_60_VESA,
	MODE_1600x1200_65_VESA,//60

	MODE_1600x1200_70_VESA,
	MODE_1600x1200_75_VESA,

	MODE_1400x1050_75_VESA,
	MODE_1400x1050_85_VESA,
	MODE_1792x1344_60_VESA, //65


	MODE_1920x1080_60_VESA,
	MODE_1920x1200_60_VESA_RB,
	MODE_1920x1200_60_VESA,
	MODE_720x480_60_YCBCR,

	#ifndef PanelType_1600x900
	//  MODE_884x930_60_VESA,
	#endif
	MODE_800x1209_60_TPV, //70


	MODE_1024x768_72_VESA,
	MODE_1280x1024_72_VESA,
	MODE_1280x1024_70_VESA,
	MODE_720x480_60_YPBPR,
	MODE_1920x1080_50_YPBPR,   //75
	MODE_1920x1080_60_NTSC,
	MODE_700x570_50Hz_TV,
	MODE_1152x870_60Hz_MAC,
	MODE_720x576_50Hz_YCBCR,
	MODE_720x480_60Hz_VIDEO,  //80

	MODE_1280x720_60Hz_VIDEO,
	MODE_1920x1080_60Hz_PAL,
	MODE_1920x1080_60Hz_NTSC,
	MODE_832x624_75Hz_MAC,
	MODE_720x576_75Hz_VESA,  //85
	MODE_720x576_50Hz_VESA,
	MODE_1280x800_60Hz_VESA,
	MODE_1280x800_60Hz_VESA1,
	MODE_1280x800_60Hz_VESA2,
	MODE_1280x800_75Hz_VESA,   //90

	MODE_1280x800_76Hz_VESA,
	MODE_1920x1080_59Hz_VESA,
	MODE_1920x1080_59Hz_VESA1,
	MODE_1600x1024_60Hz_NVIDIA,
	MODE_1920x1080_50Hz_MK, 	 //95	//130917 Henry add For MK Chrma K-8256
	MODE_1920x1080_75Hz,
	#if  ENABLE_DUAL_LINK		//130108_21 Follow Mode.c
	MODE_640x480_100Hz_RB,
	MODE_640x480_100Hz,
	MODE_640x480_120Hz_RB,
	MODE_640x480_120Hz,
	MODE_800x600_100Hz_RB, //100
	MODE_800x600_100Hz,
	MODE_800x600_120Hz_VESA_RB,
	MODE_800x600_120Hz_VESA,
	MODE_1280x960_100Hz_RB,
	MODE_1280x960_100Hz,  //105
	MODE_1024x768_100Hz_RB,
	MODE_1024x768_100Hz,
	MODE_1024x768_120Hz_VESA_RB,
	MODE_1024x768_120Hz,
	MODE_1440x900_120Hz_VESA_RB, //110
	MODE_1440x900_120Hz,
	MODE_1920x1080P_120Hz_RB,
	MODE_1920x1080P_120Hz,
	MODE_1920x1080P_110Hz_RB,
	MODE_1920x1080P_110Hz,    //115
	MODE_1920x1080P_100Hz_RB,
	MODE_1920x1080P_100Hz,
	MODE_1920x1080P_144Hz,
	MODE_2560x1440_60Hz, //20130801 nick
	#endif
	#if IIYAMASeries
	MODE_640x400_56,
	MODE_848x480_75_CVT,    // 140
	MODE_1152x864_70,
	MODE_1280x1024_70,
	#endif

	Mode_1400_1050_60_VESA_RB,
	Mode_1400_1050_60_VESA,

	#if SHARP_VGA_50Hz_Timing
	MODE_640x400_56,
	MODE_640x400_70,    // 140
	MODE_720x400_50,

	MODE_1024x768_50,
	MODE_1152x900_66,
	MODE_1152x900_66_SOG,

	MODE_1280x768_50,
	MODE_1280x960_50,
	MODE_1400x1050_50,

	MODE_1600x1200_50,
	MODE_1680x1050_50,
	#endif

	MODE_Max // It can't bigger than 128

} ModeIdentifyType;

#define HDMI_3D_TIMING_START_INDEX  MODE_1920x1080_24FP

typedef struct
{
	BYTE fFlags;
	BYTE InputType;
	WORD HPeiod;
	WORD VTotal;
	BYTE ModeIndex;
	WORD VFreq;  //130909 nick add
	#if ENABLE_CHECK_TMDS_DE
	WORD TMDSWidth;
	WORD TMDSHeight;
	WORD TMDSHStart;
	WORD TMDSVStart;
	#endif
} InputTimingType;
typedef struct
{
	WORD DispWidth;
	WORD DispHeight;
} InputResolutionType;
typedef struct
{
	BYTE Flags;
	ResolutionType ResIndex;
	WORD HFreq;
	WORD VFreq;
	WORD HTotal;
	WORD VTotal;
	WORD HStart;
	WORD VStart;
} InputModeType;
extern WORD GetStandardModeWidth(void);
extern WORD GetStandardModeHeight(void);
extern WORD GetStandardModeGroup(void);
extern WORD GetStandardModeHTotal(void);
//extern WORD GetStandardModeHFreq(void);
extern WORD GetStandardModeVFreq(void);
extern WORD GetStandardModeHStart(void);
extern WORD GetStandardModeVStart(void);
#if (CHIP_ID==CHIP_TSUMU) || (CHIP_ID==CHIP_TSUM2) ||(CHIP_ID==CHIP_TSUMC)||(CHIP_ID==CHIP_TSUMD)
extern WORD GetStandardModeVTotal(void);
#endif
