#include "global.h"
#if 0

#if CHIP_ID == CHIP_TSUM2
#include "SUPERRESOLUTION_2.C"
#elif CHIP_ID == CHIP_TSUMB
#include "SUPERRESOLUTION_B.C"
#elif CHIP_ID == CHIP_TSUMY	//121105 Modify
#include "SUPERRESOLUTION_Y.C"
#elif CHIP_ID == CHIP_TSUMV
#include "SUPERRESOLUTION_V.C"
#elif CHIP_ID == CHIP_TSUMU//20130522
#include "SUPERRESOLUTION_U.C"
#elif CHIP_ID == CHIP_TSUMC ||CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF
#include "SUPERRESOLUTION_C.C"
#elif CHIP_ID == CHIP_TSUMD
#include "SUPERRESOLUTION_D.C"
#else
#message "please implement SUPERRESOLUTION for new chip"
#endif
#else
BYTE code msCLearVersionData[] = {0};

void msClearVersionDummy(void)	//130529 Nick
{
    BYTE xdata i = msCLearVersionData[0];
}

#endif



