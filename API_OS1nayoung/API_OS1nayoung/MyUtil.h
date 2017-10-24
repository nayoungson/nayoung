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


//�ճ���
#include "�ճ���\TestCriticalSection.h"
#include "�ճ���\TestFunction.h"
#include "�ճ���\TestModule.h"
#include "�ճ���\TestRegistry.h"

#include "�ճ���\TestProcessor.h"
#include "�ճ���\TestProcessF.h"
#include "�ճ���\TestRegistryPPT.h"
#include "�ճ���\TestFunctionPPT.h"

#include "�ճ���\TestMemory.h"

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