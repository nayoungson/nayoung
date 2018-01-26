#ifndef TESTPROCESSOR
#define TESTPROCESSOR

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"


BOOL test_GetActiveProcessorCount();
BOOL test_GetActiveProcessorGroupCount();
BOOL test_GetCurrentProcessorNumber();
BOOL test_GetCurrentProcessorNumberEx();
BOOL test_GetLogicalProcessorInformationEx();
BOOL test_GetMaximumProcessorCount();
BOOL test_GetNumaNodeProcessorMask();
BOOL test_GetNumaNodeProcessorMaskEx();
BOOL test_GetNumaProcessorNodeEx();


#endif