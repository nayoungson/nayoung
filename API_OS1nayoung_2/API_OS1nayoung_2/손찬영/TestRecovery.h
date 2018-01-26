#ifndef TESTRECOVERY
#define TESTRECOVERY

#pragma comment(lib, "Wer.lib") // for WerReportCreate()

#include <Windows.h>
#include <Werapi.h>
#include "../OSQA.h"
#include "../MyUtil.h"

BOOL test_UnregisterApplicationRecoveryCallback();
BOOL test_RegisterApplicationRecoveryCallback();
BOOL test_GetApplicationRecoveryCallback();
BOOL test_ApplicationRecoveryInProgress();
BOOL test_ApplicationRecoveryFinished();


DWORD WINAPI ApplicationRecoveryCallback (PVOID pvParameter);
#endif