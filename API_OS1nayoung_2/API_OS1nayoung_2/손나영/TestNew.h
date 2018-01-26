#ifndef TESTNEW
#define TESTNEW
#pragma once

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include "../OSQA.h"
#include "../MyUtil.h"

TESTCASE test_RegCreateKeyW(HKEY hKey, LPCTSTR lpSubKey, PHKEY phkResult);

BOOL run_test_RegCreateKeyW();



#endif