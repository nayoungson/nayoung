#ifndef TESTMEMORY
#define TESTMEMORY

#pragma comment(lib, "Kernel32.lib")

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

//BOOL LoggedSetLockPagesPrivilege();
BOOL test_AddSecureMemoryCacheCallback();
BOOL test_AllocateUserPhysicalPages();
BOOL test_AllocateUserPhysicalPagesNuma();
BOOL test_FreeUserPhysicalPages();
BOOL test_GetLargePageMinimum();
BOOL test_GetNumaProximityNode();
BOOL test_GetNumaProximityNodeEx();
BOOL test_K32GetProcessMemoryInfo();
BOOL test_MapUserPhysicalPages();
BOOL test_RemoveSecureMemoryCacheCallback();
BOOL test_Toolhelp32ReadProcessMemory();
BOOL test_VirtualAllocExNuma();
BOOL test_WerRegisterMemoryBlock();
BOOL test_WerUnregisterMemoryBlock();

BOOLEAN CALLBACK SecureMemoryCacheCallback(PVOID Addr, SIZE_T Range);




#endif