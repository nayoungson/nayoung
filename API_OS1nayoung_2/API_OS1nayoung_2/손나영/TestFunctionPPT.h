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
BOOL test_GetApplicationRestartSettings();

//4주차
BOOL test_CreateHardLinkTransactedA();
BOOL test_CreateHardLinkTransactedW();
BOOL test_WerRegisterMemoryBlock();
BOOL test_WerUnregisterMemoryBlock();

//5주차
BOOL test_RegisterApplicationRestart();
BOOL test_UnregisterApplicationRestart();
BOOL test_CreateSymbolicLinkTransactedA();
BOOL test_CreateSymbolicLinkTransactedW();

BOOL test_RegLoadMUIStringA();
BOOL test_RegLoadMUIStringW();


#endif

