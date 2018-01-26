#ifndef TESTNAMESPACE
#define TESTNAMESPACE

#include <Windows.h>
#include <Sddl.h> // for ConvertSidToStringSid()
#include "../OSQA.h"
#include "../MyUtil.h"


BOOL test_DeleteBoundaryDescriptor();
BOOL test_CreateBoundaryDescriptorW();
BOOL test_CreateBoundaryDescriptorA();
BOOL test_AddIntegrityLabelToBoundaryDescriptor();


BOOL test_AddSIDToBoundaryDescriptor();
BOOL test_OpenPrivateNamespaceW();
BOOL test_OpenPrivateNamespaceA();
BOOL test_CreatePrivateNamespaceW();
BOOL test_CreatePrivateNamespaceA();
BOOL test_ClosePrivateNamespace();


#endif