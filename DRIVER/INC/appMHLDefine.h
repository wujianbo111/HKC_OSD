
#if (ModelName == TSUMXX2_DEMO ||ModelName ==AOC_HF_G2590VQ||ModelName == AOC_HF_I2480SXHE||ModelName == AOC_HF_M2490VXH||ModelName == AOC_SY_T4017C|| ModelName == TSUMXXD_DEMO || ModelName == TSUMXXC_DEMO || ModelName == TSUMXX9_DEMO || ModelName ==AOC_A2272PW4T|| ModelName == AOC_A2472PW4T || ModelName == AOC_A2272PW4T_CMI || ModelName == AOC_A2472PW4T_TPM || ModelName ==  AOC_A2472PW4TN \
|| ModelName == AOC_G15||ModelName == SPT_CNC_O38CDMT9_GV1)
#include "appMHLDefine_Demo.h"
#elif ( ModelName == AOC_I2579VM || ModelName == AOC_P2379VWM || ModelName == AOC_P2779VM8 || ModelName == AOC_P2479VWM8 || ModelName == AOC_E2357FM || ModelName == AOC_I2757FM ||ModelName == AOC_I2779VM)
#include "appMHLDefine_P2779VM8.h"
#elif ModelName==AOC_M2879VM9
#include "appMHLDefine_M2879VM9.h"
#elif (ModelName == AOC_C2783FQ)
#include "appMHLDefine_C2783QF.h"
#elif (ModelName==AOC_I2475PWQU|| ModelName==AOC_I2275PWQU|| ModelName==AOC_I2375PQU || ModelName==AOC_I2490PXQ)
#include "appMHLDefine_I2475PWQU.h"
#elif ModelName==AOC_I2775PQU
#include "appMHLDefine_I2775PQU.h"
#else
#message "please coding appMHLDefine_xxx.h for your model"
#endif

