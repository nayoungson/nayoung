#ifndef TESTEXCEPTION
#define TESTEXCEPTION

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

BOOL test_RaiseException();
BOOL test_RaiseFailFastException();

BOOL __fastcall FastCallFunction(int a, int b, int c, int d);

DWORD FilterFunction();

#endif