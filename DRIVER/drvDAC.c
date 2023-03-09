
#include "global.h"
#if MS_DAC

#if (CHIP_ID == CHIP_TSUMU ||CHIP_ID == CHIP_TSUMY || CHIP_ID == CHIP_TSUMB || CHIP_ID == CHIP_TSUM2)
#include "drvDAC_OLD.c"
#elif (CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD)
#include "drvDAC_C.c"
#elif (CHIP_ID == CHIP_TSUM9)||(CHIP_ID == CHIP_TSUMF)
#include "drvDAC_9.c"
#elif (CHIP_ID == CHIP_TSUMV || CHIP_ID == CHIP_TSUMY)
#else
#message "please implement DrvDAC for new chip"
#endif

#endif
