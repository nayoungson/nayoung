#ifndef TESTMUTEX
#define TESTMUTEX
#pragma once

#include <Windows.h>
#include <stdio.h>
#include "../OSQA.h"
#include "../MyUtil.h"

BOOL test_CreateMutexA(void);
BOOL test_CreateMutexW(void);
BOOL test_OpenMutexW(void);
BOOL test_OpenMutexA();
BOOL test_CreateMutexExW();
BOOL test_CreateMutexExA();



#endif