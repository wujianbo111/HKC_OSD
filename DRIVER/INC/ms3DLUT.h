

#if CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF
#include "drv3DLUT_C.h"
#else
//#message "please implement 3D_LUT for new chip"
#endif


#if !ENABLE_3DLUT
extern void ms3DLUT_Dummy(void);
#endif


