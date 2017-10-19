#ifndef TESTMEMORY
#define TESTMEMORY

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

//BOOL LoggedSetLockPagesPrivilege();

BOOL test_AllocateUserPhysicalPages();
BOOL test_FreeUserPhysicalPages();
BOOL test_MapUserPhysicalPages();
BOOL test_GetLargePageMinimum();
BOOL test_GetFinalPathNameByHandleA();
BOOL test_GetApplicationRestartSettings();


#endif