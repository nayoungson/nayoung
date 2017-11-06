#ifndef TESTREGISTRYPPT
#define TESTREGISTRYPPT

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

BOOL test_RegDeleteTreeW();
BOOL test_RegEnumKeyExA();

BOOL test_RegDisablePredefinedCacheEx();
BOOL test_RegGetValueW();

//4ÁÖÂ÷

BOOL test_RegLoadKeyA();
BOOL test_RegLoadKeyW();
BOOL test_RegUnLoadKeyA();
BOOL test_RegUnLoadKeyW();
BOOL test_RegSaveKeyExA();
BOOL test_RegSaveKeyExW();
BOOL test_RegRestoreKeyA();
BOOL test_RegRestoreKeyW();

BOOL test_RegOpenCurrentUser();
BOOL test_RegOpenUserClassesRoot();
BOOL test_RegLoadMUIStringA();
BOOL test_RegLoadMUIStringW();

#endif