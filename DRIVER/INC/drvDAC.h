

#ifndef _DRVDAC_H_
#define _DRVDAC_H_

#if (CHIP_ID == CHIP_TSUMU ||CHIP_ID == CHIP_TSUMY || CHIP_ID == CHIP_TSUMB || CHIP_ID == CHIP_TSUM2)
#include "drvDAC_OLD.h"
#elif (CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD)
#include "drvDAC_C.h"
#elif (CHIP_ID == CHIP_TSUM9)||(CHIP_ID == CHIP_TSUMF)
#include "drvDAC_9.h"
#else
#message "please implement DrvDAC.h for new chip"
#endif

#endif
