#ifndef TESTMODULE
#define TESTMODULE

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

#include <TlHelp32.h>
#include <Psapi.h>

BOOL test_K32GetModuleBaseNameA();
BOOL test_K32GetModuleBaseNameW();
BOOL test_K32GetModuleFileNameExA();
BOOL test_K32GetModuleFileNameExW();
BOOL test_K32GetModuleInformation();
BOOL test_LoadModule();
BOOL test_Module32FirstW();
BOOL test_Module32NextW();

#endif