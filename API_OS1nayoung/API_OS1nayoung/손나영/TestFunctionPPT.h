#ifndef TESTFUNCTIONPPT
#define TESTFUNCTIONPPT

#pragma comment(lib, "KtmW32.lib")

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"


BOOL test_SetFileInformationByHandle();
BOOL test_SetCriticalSectionSpinCount();
BOOL test_GetVolumeInformationByHandleW();
BOOL test_FatalAppExitW();

//3주차
BOOL test_FatalExit();
BOOL test_GetFinalPathNameByHandleA();

//14주차
BOOL test_CreateHardLinkTransactedA();
BOOL test_WerRegisterMemoryBlock();
BOOL test_WerUnregisterMemoryBlock();



#endif

