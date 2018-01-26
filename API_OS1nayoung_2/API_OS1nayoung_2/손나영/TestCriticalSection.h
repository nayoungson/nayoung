#ifndef TESTCRITICALSECTION
#define TESTCRITICALSECTION

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

BOOL test_DeleteCriticalSection();
BOOL test_InitializeCriticalSectionAndSpinCount();
BOOL test_InitializeCriticalSectionEx();
BOOL test_TryEnterCriticalSection();

#endif