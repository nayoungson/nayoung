#ifndef TESTIO
#define TESTIO
#pragma once

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

BOOL test_CancelIo(void);

BOOL test_CancelIoEx();
BOOL test_GetQueuedCompletionStatusEx();
BOOL test_CancelSynchronousIo();


#endif