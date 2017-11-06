#ifndef TESTPROCESSOR
#define TESTPROCESSOR

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

BOOL test_GetMaximumProcessorCount();
BOOL test_GetActiveProcessorCount();
BOOL test_GetActiveProcessorGroupCount();
BOOL test_GetLogicalProcessorInformationEx();
BOOL test_GetCurrentProcessorNumber();

//3주차
BOOL test_GetNumaProcessorNodeEx();
BOOL test_GetCurrentProcessorNumberEx();

//4주차
BOOL test_GetNumaNodeProcessorMask();
BOOL test_GetNumaNodeProcessorMaskEx();
#endif