#ifndef TESTREGISTRY4
#define TESTREGISTRY4

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

//BOOL test_RegLoadKeyA();
//BOOL test_RegUnLoadKeyA();
//BOOL test_RegUnLoadKeyW();
BOOL test_RegDeleteTreeW();
BOOL test_RegEnumKeyExA();

BOOL test_RegDisablePredefinedCacheEx();
BOOL test_RegGetValueW();

//3ÁÖÂ÷
BOOL test_RegRestoreKeyA();
BOOL test_RegLoadKeyA();
BOOL test_RegOpenCurrentUser();

#endif