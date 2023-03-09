#ifndef _MSOVD_H_
#define _MSOVD_H_

#ifdef _MSOVD_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

//*************************************************************************************************
// Description: OD look-up table loader.
//
// ex: msLoadODT(tOverDrive)
//
// It provides two kinds of format (normal and compressed) for OD look-up table.
// The look-up table and OD lib should be located in the same bank!!

//INTERFACE code BYTE* tOverDrive_AllTbl[];

INTERFACE void msOverDriverInit(void);
INTERFACE void msLoadODTable( BYTE *pODTbl);
INTERFACE void msLoad_MultiODTable(BYTE u8Index);
INTERFACE void msOverDriveOnOff(Bool bEnable);
INTERFACE void msRTE_LoadLUT(void);
INTERFACE void msODWatchTrackPointValue(Bool bAfterOD);
INTERFACE void msOverDriveDummy();

//extern void msODFunction(void);
#undef INTERFACE
#endif
