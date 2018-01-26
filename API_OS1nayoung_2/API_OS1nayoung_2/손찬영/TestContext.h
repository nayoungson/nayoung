#ifndef TESTCONTEXT
#define TESTCONTEXT

#include <Windows.h>
#include <Shlwapi.h>
#include "../OSQA.h"
#include "../MyUtil.h"

#pragma comment(lib, "Shlwapi.lib")

BOOL test_ZombifyActCtx();
BOOL test_AddRefActCtx();
BOOL test_InitializeContext();
BOOL test_CreateActCtxA();
BOOL test_CopyContext();

#endif