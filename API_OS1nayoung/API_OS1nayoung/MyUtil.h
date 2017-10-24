#ifndef MYUTIL
#define MYUTIL
#pragma once

#pragma comment(linker, "/entry:WinMainCRTStartup")
#pragma comment(linker, "/subsystem:console")
#pragma warning(disable:4996)

#include <Windows.h>
#include <stdio.h>
#include <string.h>

#include "OSQA.h"


//손나영
#include "손나영\TestCriticalSection.h"
#include "손나영\TestFunction.h"
#include "손나영\TestModule.h"
#include "손나영\TestRegistry.h"

#include "손나영\TestProcessor.h"
#include "손나영\TestProcessF.h"
#include "손나영\TestRegistryPPT.h"
#include "손나영\TestFunctionPPT.h"

#include "손나영\TestMemory.h"

#define BUTTON_POS_X 0
#define BUTTON_POS_Y 0
#define BUTTON_WIDTH 250
#define BUTTON_HEIGHT 30

#define SLEEP_SECOND 3
#define TEST_FUNC_COUNT 128
#define TEST_FUNC_LEN 30

typedef BOOL(*funcPtr)(void);

char *GetErrorMessage(const char *str, int errorCode);
wchar_t **AllocFuncNameList();
void ReadTestFuncList(wchar_t *funcName[TEST_FUNC_LEN]);
wchar_t **CreateButtonForTest(HWND hWnd, HINSTANCE g_hInst, wchar_t *funcName[TEST_FUNC_LEN]);
void FreeFuncNameList(wchar_t **funcName);

#endif