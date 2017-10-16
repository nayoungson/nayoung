#ifndef TESTPROCESSF
#define TESTPROCESSF

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"
#include <Psapi.h>


BOOL test_GetProcessShutdownParameters();
BOOL test_K32InitializeProcessForWsWatch();
BOOL test_QueryProcessAffinityUpdateMode();
BOOL test_SetProcessAffinityUpdateMode();
BOOL test_SetProcessDEPPolicy();
BOOL test_SetProcessShutdownParameters();


//3����
BOOL test_GetProcessWorkingSetSize();
BOOL test_GetProcessWorkingSetSizeEx();

#endif