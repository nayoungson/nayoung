#ifndef TESTFUNCTIONPPT
#define TESTFUNCTIONPPT


#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"
#include <ktmw32.h>

BOOL test_SetFileInformationByHandle();
BOOL test_SetCriticalSectionSpinCount();
BOOL test_GetVolumeInformationByHandleW();
BOOL test_FatalAppExitW();

//3����
BOOL test_FatalExit();
//BOOL test_CreateHardLinkTransactedA(); -BLOCK

#endif

