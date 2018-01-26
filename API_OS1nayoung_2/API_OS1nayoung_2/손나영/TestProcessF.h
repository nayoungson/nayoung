#ifndef TESTPROCESSF
#define TESTPROCESSF

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"
#include <Psapi.h>

BOOL test_FlushProcessWriteBuffers();
BOOL test_GetMaximumProcessorGroupCount();
BOOL test_GetNumaNodeNumberFromHandle();
BOOL test_GetNumaProcessorNode();
BOOL test_GetProcessDEPPolicy();
BOOL test_GetProcessGroupAffinity();
BOOL test_GetProcessHandleCount();
BOOL test_GetProcessId();
BOOL test_GetProcessPriorityBoost();
BOOL test_GetProcessShutdownParameters();
BOOL test_GetProcessWorkingSetSize();
BOOL test_GetProcessWorkingSetSizeEx();
BOOL test_IsProcessInJob();
BOOL test_K32EnumProcesses();
BOOL test_K32EnumProcessModules();
BOOL test_K32EnumProcessModulesEx();
BOOL test_K32InitializeProcessForWsWatch();
BOOL test_QueryProcessAffinityUpdateMode();
BOOL test_SetProcessAffinityUpdateMode();
BOOL test_SetProcessDEPPolicy();
BOOL test_SetProcessPriorityBoost();
BOOL test_SetProcessShutdownParameters();







#endif