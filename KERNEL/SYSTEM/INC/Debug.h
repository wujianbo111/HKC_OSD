#include "Common.h"

extern xdata BYTE SIORxIndex;
extern xdata BYTE ReSyncCounter;
#if 1//ndef WH_REQUEST
extern BYTE AOCAlign(void);
#endif
extern void DebugHandler(void);
#if DEBUG_VIRTUAL_KEY
extern BYTE xdata KeyDebug;
#endif


