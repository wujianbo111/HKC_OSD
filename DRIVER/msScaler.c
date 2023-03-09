


#include "global.h"

#if CHIP_ID == CHIP_TSUMU
#include "msScaler_U.c"
#elif CHIP_ID == CHIP_TSUM2
#include "msScaler_2.c"
#elif CHIP_ID == CHIP_TSUMC
#include "msScaler_C.c"
#elif CHIP_ID == CHIP_TSUMD
#include "msScaler_D.c"
#elif CHIP_ID == CHIP_TSUM9
#include "msScaler_9.c"
#elif CHIP_ID == CHIP_TSUMF
#include "msScaler_F.c"
#elif CHIP_ID == CHIP_TSUML||CHIP_ID == CHIP_TSUMB||CHIP_ID == CHIP_TSUMY||CHIP_ID == CHIP_TSUMV


#else
#message "please implement msScaler for new chip"
#endif

