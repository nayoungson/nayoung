#ifndef TESTQUERY
#define TESTQUERY
#pragma once

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include "../OSQA.h"
#include "../MyUtil.h"

BOOL test_QueryPerformanceCounter(void);
BOOL test_QueryPerformanceFrequency(void);

//������ʹ� API�Լ����� ���� 1���� �ó������� �����ϱ� ���� �Լ�
//int test_GetElapsedTimeByQuery(void);


#endif