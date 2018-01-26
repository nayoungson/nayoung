/*
*	작성자 : OQA1 손찬영
*/

#ifndef MYUTIL
#define MYUTIL
#pragma once

//#ifdef OQADBGPRINT
#pragma comment(linker, "/entry:WinMainCRTStartup") //cmd 창 호출을 위해 작성
#pragma comment(linker, "/subsystem:console") //cmd 창 호출을 위해 작성
//#endif

#pragma warning(disable:4996) //secure함수워닝 비활성화

#pragma comment(lib, "ktmw32.lib")

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <ktmw32.h> // For CreateTransaction()

#include "OSQA.h"

#define SLEEP_SECOND 3

struct _TESTCASE{
	char msg[BUFSIZ]; //성공, 실패 메세지
	int result; //성공 = 1, 실패 = 0, 중단 = -1
};

typedef struct _TESTCASE TESTCASE;


char *GetErrorMessage(const char *str, int errorCode);
//
//#ifndef MYUTIL
//#define MYUTIL
//#pragma once
//
//#pragma comment(linker, "/entry:WinMainCRTStartup")
//#pragma comment(linker, "/subsystem:console")
//#pragma warning(disable:4996)
//
//#include <Windows.h>
//#include <stdio.h>
//#include <string.h>
//
//#include "OSQA.h"
//
//#define SLEEP_SECOND 3
//
//char *GetErrorMessage(const char *str, int errorCode);
//BOOL WinRefresh(HWND hwnd); //hWnd를 새로그린다.
//
//struct _TESTCASE{
//	char msg[BUFSIZ]; //성공, 실패 메세지
//	int result; //성공 = 1, 실패 = 0, 중단 = -1
//};
//
//typedef struct _TESTCASE TESTCASE;

//손나영
//#include "손나영\TestCriticalSection.h"
//#include "손나영\TestEventHG.h"
//#include "손나영\TestFunction.h"
//#include "손나영\TestFunctionPPT.h"
//#include "손나영\TestMemory.h"
//#include "손나영\TestModule.h"
//#include "손나영\TestProcessF.h"
//#include "손나영\TestProcessor.h"
//#include "손나영\TestRegistry.h"

//
//#define BUTTON_POS_X 0
//#define BUTTON_POS_Y 0
//#define BUTTON_WIDTH 250
//#define BUTTON_HEIGHT 30
//
//#define SLEEP_SECOND 3
//#define TEST_FUNC_COUNT 128
//#define TEST_FUNC_LEN 30

typedef BOOL(*funcPtr)(void);

//wchar_t **AllocFuncNameList();
//void ReadTestFuncList(wchar_t *funcName[TEST_FUNC_LEN]);
//wchar_t **CreateButtonForTest(HWND hWnd, HINSTANCE g_hInst, wchar_t *funcName[TEST_FUNC_LEN]);
//void FreeFuncNameList(wchar_t **funcName);


void SetPaintMessage(int nCount, POINT *point, const char *color, const char *shape, char *msg);


#endif
