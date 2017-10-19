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

//3ÁÖÂ÷
BOOL test_GetProcessId();
BOOL test_GetProcessWorkingSetSize();
BOOL test_IsProcessInJob();
BOOL test_GetProcessHandleCount();
BOOL test_GetProcessDEPPolicy();
//BOOL test_GetProcessGroupAffinity();


BOOL test_GetProcessWorkingSetSizeEx();




#endif