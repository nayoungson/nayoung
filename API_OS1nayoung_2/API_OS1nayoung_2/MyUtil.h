/*
*	�ۼ��� : OQA1 ������
*/

#ifndef MYUTIL
#define MYUTIL
#pragma once

//#ifdef OQADBGPRINT
#pragma comment(linker, "/entry:WinMainCRTStartup") //cmd â ȣ���� ���� �ۼ�
#pragma comment(linker, "/subsystem:console") //cmd â ȣ���� ���� �ۼ�
//#endif

#pragma warning(disable:4996) //secure�Լ����� ��Ȱ��ȭ

#pragma comment(lib, "ktmw32.lib")

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <ktmw32.h> // For CreateTransaction()

#include "OSQA.h"

#define SLEEP_SECOND 3

struct _TESTCASE{
	char msg[BUFSIZ]; //����, ���� �޼���
	int result; //���� = 1, ���� = 0, �ߴ� = -1
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
//BOOL WinRefresh(HWND hwnd); //hWnd�� ���α׸���.
//
//struct _TESTCASE{
//	char msg[BUFSIZ]; //����, ���� �޼���
//	int result; //���� = 1, ���� = 0, �ߴ� = -1
//};
//
//typedef struct _TESTCASE TESTCASE;

//�ճ���
//#include "�ճ���\TestCriticalSection.h"
//#include "�ճ���\TestEventHG.h"
//#include "�ճ���\TestFunction.h"
//#include "�ճ���\TestFunctionPPT.h"
//#include "�ճ���\TestMemory.h"
//#include "�ճ���\TestModule.h"
//#include "�ճ���\TestProcessF.h"
//#include "�ճ���\TestProcessor.h"
//#include "�ճ���\TestRegistry.h"

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
