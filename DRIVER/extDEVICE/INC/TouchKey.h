

#define Key_GetKeypadStatus()       TouchKey_GetKeyStatus()

#if I2CKEY_TYPE==I2CKEY_ITE
#include "IT7230_TouchKey.h"
#include "IT7230_I2C.h"
#include "IT7230_SettingTable.h"

#define TouchKey_Init   IT7230_Init
#define TouchKey_Check_ESD   IT7230_Check_ESD
#define TouchKey_GetKeyStatus    IT7230_GetKeyStatus
#define TouchKey_Restort_Reg   IT7230_Restort_Reg
#define TouchKey_InitStatus     IT7230_Init_Status
#elif I2CKEY_TYPE==I2CKEY_ENE
#include "ENE_TouchKey.h"
#include "ENE_I2C.h"
//#include "ENE_SettingTable.h"

#define TouchKey_Init                      appRegInit
#define TouchKey_Check_ESD        appCheckEneESD
#define TouchKey_GetKeyStatus    appGetI2CKeypadStatus

#elif I2CKEY_TYPE==I2CKEY_CYPRESS
#else
#message "please implement function for new touch key source"
#endif


