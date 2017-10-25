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

//3주차
BOOL test_GetProcessId();
BOOL test_GetProcessWorkingSetSize();
BOOL test_IsProcessInJob();
BOOL test_GetProcessHandleCount();
BOOL test_GetProcessDEPPolicy();

//4주차
BOOL test_FlushProcessWriteBuffers();
BOOL test_SetProcessPriorityBoost();
BOOL test_K32EnumProcesses();
BOOL test_K32EnumProcessModules();
BOOL test_K32EnumProcessModulesEx();
BOOL test_K32GetModuleBaseNameA();
BOOL test_K32GetModuleBaseNameW();

//BOOL test_GetProcessGroupAffinity();


BOOL test_GetProcessWorkingSetSizeEx();




#endif