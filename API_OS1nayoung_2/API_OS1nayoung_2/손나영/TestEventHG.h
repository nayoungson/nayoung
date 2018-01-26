#ifndef TESTEVENTHG
#define TESTEVENTHG

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"


#include <evntprov.h>


BOOL test_DeregisterEventSource();
BOOL test_EnumDependentServicesA();
BOOL test_EventActivityIdControl();
BOOL test_EventUnregister();
BOOL test_EventWriteTransfer();
BOOL test_RegisterEventSourceA();
BOOL test_ReportEventA();

BOOL test_GetKeyboardType();
BOOL test_GetPriorityClipboardFormat();
BOOL test_MapVirtualKeyA();
BOOL test_MapVirtualKeyExA();
BOOL test_VkKeyScanA();


#endif