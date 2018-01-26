#ifndef TESTTHREAD
#define TESTTHREAD
#pragma once


#include <Windows.h>
#include <stdio.h>
#include "../MyUtil.h"
#include "../OSQA.h"

BOOL test_GetThreadContext(void);
BOOL test_SetThreadLocale(void);
BOOL test_SetThreadExecutionState(void);

BOOL test_Wow64SuspendThread();
BOOL test_GetThreadId();
BOOL test_GetProcessIdOfThread();
BOOL test_GetThreadIdealProcessorEx();
BOOL test_EnableThreadProfiling();
BOOL test_DisableThreadProfiling();
BOOL test_GetThreadGroupAffinity();
BOOL test_SetThreadGroupAffinity();

BOOL test_GetThreadIOPendingFlag();
BOOL test_GetThreadSelectorEntry();

BOOL test_SetThreadStackGuarantee();
BOOL test_SetThreadIdealProcessorEx();
BOOL test_QueryThreadProfiling();
BOOL test_QueryThreadCycleTime();


DWORD WINAPI ThreadProc(LPVOID lpParam);
DWORD WINAPI ThreadWow64Suspend(LPVOID temp);
#endif