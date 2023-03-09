#ifndef _MSOVD_H_
#define _MSOVD_H_

#ifdef _MSOVD_C_
#define _MSOVDDEC_
#else
#define _MSOVDDEC_ extern
#endif



typedef enum
{
	_OD_Disable,
	_OD_Enable

} ODStatusType;

_MSOVDDEC_ BYTE code tOverDrive[];


//*************************************************************************************************
//Description: OD look-up table loader.
//
//           ex: msLoadODT(tOverDrive)
//
//           It provides two kinds of format (normal and compressed) for OD look-up table.
//           The look-up table and OD lib should be located in the same bank!!
_MSOVDDEC_ void msOverDriverInit(void);
_MSOVDDEC_ void msLoadODTable( BYTE *pODTbl);
//_MSOVDDEC_ void msLoad_MultiODTable(void);
_MSOVDDEC_ void msOverDriveOnOff(BOOL bEnable);
_MSOVDDEC_ void msOverDriveDummy();
_MSOVDDEC_ void msRTE_LoadLUT(void);

//*************************************************************************************************

#endif
