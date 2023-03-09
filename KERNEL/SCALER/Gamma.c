#include "board.h"

#if Enable_Gamma || ENABLE_GAMMA_FIX_PANEL_NOISE
#define _GAMMA_C_
#include "types.h"
#include "drvGamma.h"
//#include "Panel_GAMMATBL.h"
#include "ms_reg.h"
#include "gamma.h"
#include "ms_rwreg.h"
#include "Common.h"
#include "Global.h"
#include "Menudef.h"
#include "adjust.h"
#include "misc.h"



BYTE xdata GammaContent = GAMA_Nums;

void mStar_SetupGamma( BYTE GamaMode )
{
	#if CHIP_ID ==CHIP_TSUMC || CHIP_ID ==CHIP_TSUMD || CHIP_ID ==CHIP_TSUM9|| CHIP_ID == CHIP_TSUMF	//130509 Modify
	if(GammaContent == GamaMode && PanelOnFlag)
	#else
	if(GammaContent == GamaMode)
	#endif
		return;
	mStar_WaitForDataBlanking();
	drvGammaOnOff(_DISABLE, MAIN_WINDOW );
	drvGammaOnOff(_DISABLE, SUB_WINDOW );
	#if GAMMA_BYPASS
	if(GamaMode != GAMA1)
	#endif
	{
		#if ENABLE_GAMMA_FIX_PANEL_NOISE
		drvGammaLoadTbl( GAMA1 );
		#else
		drvGammaLoadTbl( GamaMode );
		#endif
		mStar_WaitForDataBlanking();
		drvGammaOnOff(_ENABLE, MAIN_WINDOW );
		drvGammaOnOff(_ENABLE, SUB_WINDOW );
	}
	GammaContent = GamaMode;
}

#endif
