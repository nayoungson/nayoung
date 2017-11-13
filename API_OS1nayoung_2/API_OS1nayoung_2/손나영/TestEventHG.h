#ifndef TESTEVENTHG
#define TESTEVENTHG

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

#include <evntprov.h>

BOOL test_EventActivityIdControl();
BOOL test_DeregisterEventSource();
BOOL test_EventUnregister();
BOOL test_EventWriteTransfer();
BOOL test_RegisterEventSourceA();

#endif