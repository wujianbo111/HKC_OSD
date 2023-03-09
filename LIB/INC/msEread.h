/******************************************************************************
 Copyright (c) 2012 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: msEread.h
 [Date]:        09-Nov-2012
 [Comment]:
   Color adjust header file.
 [Reversion History]:
*******************************************************************************/

#ifndef _MSEREAD_H_
#define _MSEREAD_H_


// Check any valid HDCP key in Efuse
Bool msEread_IsHDCPKeyInEfuse(void);
#if !Init_HDCPKey
// Get HDCP key from Efuse
BYTE msEread_GetHDCPKeyFromEfuse(WORD wCount);
#endif

// Compare checksum is equal to Efuse or not
Bool msEread_CompareHDCPChecksumInEfuse(WORD u16Value);

// Get ADC bandgap trimming value from Efuse
BYTE msEread_GetADCBandgapTrimValFromEfuse(void);

// Get public data from Efuse
BYTE msEread_GetDataFromEfuse(WORD wCount);

// Set Combo initial value
void msEread_SetComboInitialValue(void);

// Set HDMI initial value
void msEread_SetHDMIInitialValue(void);

#if ENABLE_MHL
// Set MHL initial value
void msEread_SetMHLInitialValue(void);
#endif
// Get reserved value
BYTE msEread_GetReseredValue(void);

//#if defined(_EFUSE_TSUM9_)
#if CHIP_ID == CHIP_TSUM9 || CHIP_ID == CHIP_TSUMF
void msEread_SelectEfuse(BYTE u8EfuseSel);	// for TSUM9 only
#endif
//#endif

#endif
