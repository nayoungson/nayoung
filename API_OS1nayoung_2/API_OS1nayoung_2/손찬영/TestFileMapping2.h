#ifndef TESTFILEMAPPING2
#define TESTFILEMAPPING2

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

BOOL test_OpenFileMappingW();

BOOL test_MapViewOfFileExNuma();
BOOL test_CreateFileMappingNumaW();
BOOL test_CreateFileMappingNumaA();

BOOL test_GetNumaAvailableMemoryNode();
BOOL test_GetNumaAvailableMemoryNodeEx();

#endif