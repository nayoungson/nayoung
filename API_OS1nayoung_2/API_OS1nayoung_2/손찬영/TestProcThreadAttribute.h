#ifndef TESTPROCTHREADATTRIBUTE
#define TESTPROCTHREADATTRIBUTE
#pragma once


#include <Windows.h>
#include <stdio.h>
#include "../MyUtil.h"
#include "../OSQA.h"

BOOL test_InitializeProcThreadAttributeList(void);
BOOL test_UpdateProcThreadAttribute(void);
BOOL test_DeleteProcThreadAttributeList(void);

#endif