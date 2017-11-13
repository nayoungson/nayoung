#ifndef TESTCRITICALSECTION
#define TESTCRITICALSECTION

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

BOOL test_InitializeCriticalSectionEx();
BOOL test_TryEnterCriticalSection();
BOOL test_DeleteCriticalSection();

BOOL test_InitializeCriticalSectionAndSpinCount();
#endif