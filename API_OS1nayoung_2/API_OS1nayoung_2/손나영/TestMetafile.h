#ifndef TESTMETAFILE
#define TESTMETAFILE

#pragma comment(lib, "Kernel32.lib")

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

BOOL test_GetEnhMetaFileA();
BOOL test_GetEnhMetaFileW();
BOOL test_GetMetaFileA();
BOOL test_GetMetaFileW();

#endif