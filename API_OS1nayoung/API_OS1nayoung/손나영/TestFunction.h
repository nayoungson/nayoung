#ifndef TESTFUNCTION
#define TESTFUNCTION

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

#include <tchar.h>
#include <Shlwapi.h>
#define ID_BUTTON_CONTROL 1000

BOOL test_Beep();
BOOL test_CreateHardLinkW();				   
BOOL test_CreateJobObjectW();			
BOOL test_SetInformationJobObject();
BOOL test_FatalAppExitA();
BOOL test_GetProfileIntW();
BOOL test_SetHandleCount();
BOOL test_SetPriorityClass();
BOOL test_GetPriorityClass();

#endif

