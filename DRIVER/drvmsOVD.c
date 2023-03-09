
#include "global.h"

#if CHIP_ID == CHIP_TSUMU
#include "drvmsOVD_U.c"
#elif CHIP_ID == CHIP_TSUMB
#include "drvmsOVD_B.c"
#elif CHIP_ID == CHIP_TSUM2
#include "drvmsOVD_2.c"
#elif CHIP_ID == CHIP_TSUMC
#include "drvmsOVD_C.c"
#elif CHIP_ID == CHIP_TSUMD
#include "drvmsOVD_D.c"
#elif CHIP_ID == CHIP_TSUMF
#include "drvmsOVD_F.c"
//#elif CHIP_ID == CHIP_TSUMV || CHIP_ID == CHIP_TSUMY
#else
#message "please check if need OD function for your project"
BYTE code msOVDDummy[] = {0};
void msOverDriveDummy()
{
	BYTE x = msOVDDummy;
}
#endif

