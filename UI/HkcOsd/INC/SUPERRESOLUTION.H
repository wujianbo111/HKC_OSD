#if CHIP_ID == CHIP_TSUM2
#include "SUPERRESOLUTION_2.h"
#elif CHIP_ID == CHIP_TSUMB
#include "SUPERRESOLUTION_B.h"
#elif CHIP_ID == CHIP_TSUMY	//121105 Modify
#include "SUPERRESOLUTION_Y.h"
#elif CHIP_ID == CHIP_TSUMV
#include "SUPERRESOLUTION_V.h"
#elif CHIP_ID == CHIP_TSUMU//20130522
#include "SUPERRESOLUTION_U.h"
#elif CHIP_ID == CHIP_TSUMC||CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF
#include "SUPERRESOLUTION_c.h"
#elif CHIP_ID == CHIP_TSUMD
#include "SUPERRESOLUTION_d.h"
#else
//#message "please implement SUPERRESOLUTION for new chip"
#endif

