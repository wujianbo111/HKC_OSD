
#ifndef _DPRxApp_H_
#define _DPRxApp_H_

#if CHIP_ID == CHIP_TSUMU
#include "drvDPRxApp_U.h"
#elif CHIP_ID==CHIP_TSUMC
#include "drvDPRxApp_C.h"
#elif CHIP_ID==CHIP_TSUMD
#include "drvDPRxApp_C.h"
#elif (CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF)
#include "drvDPRxApp_9.h"
#else
//#message "please implement appmStar for new chip"
#endif

#endif
