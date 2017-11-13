#ifndef TESTMODULE
#define TESTMODULE

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

BOOL test_LoadModule();
BOOL test_Module32FirstW();
BOOL test_Module32NextW();

//4ÁÖÂ÷
BOOL test_K32GetModuleBaseNameA();
BOOL test_K32GetModuleBaseNameW();
BOOL test_K32GetModuleFileNameExA();
BOOL test_K32GetModuleFileNameExW();
BOOL test_K32GetModuleInformation();

#endif