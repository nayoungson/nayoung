#ifndef TESTFILEATTRIBUTES
#define TESTFILEATTRIBUTES

#pragma comment(lib, "KtmW32.lib")

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

BOOL test_GetFileAttributesExW();
BOOL test_GetFileAttributesW();

BOOL test_GetFileAttributesExA();

BOOL test_GetFileAttributesTransactedW();
BOOL test_GetFileAttributesTransactedA();
BOOL test_SetFileAttributesTransactedW();
BOOL test_SetFileAttributesTransactedA();



#endif