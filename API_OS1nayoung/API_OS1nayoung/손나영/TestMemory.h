#ifndef TESTMEMORY
#define TESTMEMORY

#pragma comment(lib, "Kernel32.lib")

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

//BOOL LoggedSetLockPagesPrivilege();

BOOL test_AllocateUserPhysicalPages();
BOOL test_FreeUserPhysicalPages();
BOOL test_MapUserPhysicalPages();
BOOL test_GetLargePageMinimum();

BOOL test_GetApplicationRestartSettings();

BOOL test_VirtualAllocExNuma();
BOOL test_AllocateUserPhysicalPagesNuma();

#endif