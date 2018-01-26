#ifndef TESTREGISTRY
#define TESTREGISTRY

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"
#include <TlHelp32.h>
#include <stdio.h>
#include <tchar.h>

BOOL test_RegCloseKey();
BOOL test_RegCreateKeyExW();
BOOL test_RegCreateKeyW();
BOOL test_RegDeleteKeyExW();
BOOL test_RegDeleteKeyW();
BOOL test_RegDeleteTreeW();
BOOL test_RegDeleteValueW();
BOOL test_RegDisablePredefinedCacheEx();
BOOL test_RegEnumKeyExA();
BOOL test_RegEnumKeyExW();
BOOL test_RegEnumKeyW();
BOOL test_RegEnumValueW();
BOOL test_RegGetKeySecurity();
BOOL test_RegGetValueW();
BOOL test_RegLoadKeyA();
BOOL test_RegLoadKeyW();
BOOL test_RegNotifyChangeKeyValue();
BOOL test_RegOpenCurrentUser();
BOOL test_RegOpenKeyExW();
BOOL test_RegOpenKeyW();
BOOL test_RegOpenUserClassesRoot();
BOOL test_RegQueryInfoKeyW();
BOOL test_RegQueryValueExW();
BOOL test_RegSaveKeyExA();
BOOL test_RegSaveKeyExW();
BOOL test_RegSetKeySecurity();
BOOL test_RegSetValueExW();
BOOL test_RegUnLoadKeyA();
BOOL test_RegUnLoadKeyW();

/**
BOOL test_RegRestoreKeyA();
BOOL test_RegRestoreKeyW();
BOOL test_RegLoadMUIStringA();
BOOL test_RegLoadMUIStringW();
BOOL test_RegEnumValueA();
*/


#endif