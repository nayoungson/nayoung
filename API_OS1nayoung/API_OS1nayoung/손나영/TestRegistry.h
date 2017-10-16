#ifndef TESTREGISTRY
#define TESTREGISTRY

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"
#include <TlHelp32.h>

BOOL test_RegCloseKey();
BOOL test_RegCreateKeyExW();
BOOL test_RegDeleteKeyExW();
BOOL test_RegEnumValueW();
BOOL test_RegOpenKeyExW();
BOOL test_RegQueryInfoKeyW();
BOOL test_RegQueryValueExW();
BOOL test_RegSetValueExW();
BOOL test_RegDeleteValueW();
BOOL test_RegEnumKeyExW();
BOOL test_RegEnumKeyW();
BOOL test_RegCreateKeyW();
BOOL test_RegOpenKeyW();
BOOL test_RegDeleteKeyW();
BOOL test_RegNotifyChangeKeyValue();

#endif