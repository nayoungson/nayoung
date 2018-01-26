#ifndef TESTSECURITY
#define TESTSECURITY

#include <Windows.h>
#include <AccCtrl.h>
#include <Aclapi.h>
#include <sddl.h>
#include "../OSQA.h"
#include "../MyUtil.h"


BOOL test_SetFileSecurityW();
BOOL test_GetFileSecurityW();
BOOL test_GetSecurityDescriptorLength();
BOOL test_SetNamedSecurityInfoW();
BOOL test_GetNamedSecurityInfoW();
BOOL test_ConvertSidToStringSidW();

/* ���� */
BOOL test_SetSecurityDescriptorGroup();
BOOL test_SetSecurityDescriptorOwner();


PSID pSidGetOwnerSid(LPWSTR lpUser);


BOOL AddToACL(PACL& pACL, const wchar_t *AccountName, DWORD AccessOption); //SetFileSecurity���� ����ϱ� ����
#endif