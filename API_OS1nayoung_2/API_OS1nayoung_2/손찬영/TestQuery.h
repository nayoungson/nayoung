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

//여기부터는 API함수들을 묶어 1개의 시나리오로 수행하기 위한 함수
//int test_GetElapsedTimeByQuery(void);


#endif