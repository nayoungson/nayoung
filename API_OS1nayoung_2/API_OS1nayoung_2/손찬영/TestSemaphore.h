#ifndef TESTSEMAPHORE
#define TESTSEMAPHORE

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

BOOL test_OpenSemaphoreW();
BOOL test_CreateSemaphoreExW();
BOOL test_CreateSemaphoreExA();

#endif