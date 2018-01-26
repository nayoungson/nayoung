#ifndef TESTFUNCTIONPPT
#define TESTFUNCTIONPPT

#pragma comment(lib, "KtmW32.lib")

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"


BOOL test_CreateHardLinkTransactedA();
BOOL test_CreateHardLinkTransactedW();
BOOL test_CreateSymbolicLinkTransactedA();
BOOL test_CreateSymbolicLinkTransactedW();
BOOL test_FatalAppExitW();
BOOL test_FatalExit();
BOOL test_FreeLibraryAndExitThread();  //kerneldll block
BOOL test_GetApplicationRestartSettings();
BOOL test_GetFinalPathNameByHandleA();
BOOL test_GetVolumeInformationByHandleW();
BOOL test_ReadThreadProfilingData();
BOOL test_RegisterApplicationRestart();
BOOL test_RegLoadMUIStringA();
BOOL test_RegLoadMUIStringW();
BOOL test_SetCriticalSectionSpinCount();
BOOL test_SetFileInformationByHandle();
BOOL test_SetStdHandleEx();
BOOL test_UnregisterApplicationRestart();
BOOL test_WerRegisterMemoryBlock();
BOOL test_WerUnregisterMemoryBlock();

#endif

