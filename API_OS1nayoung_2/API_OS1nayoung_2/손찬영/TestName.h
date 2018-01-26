#ifndef TESTNAME
#define TESTNAME

#pragma comment(lib, "Lz32.lib") //For GetExpandedName()

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

BOOL test_SetComputerNameW();
BOOL test_SetComputerNameExW();
BOOL test_SetComputerNameExA();
BOOL test_SetComputerNameA();
BOOL test_ResolveLocaleName();
BOOL test_GetUserDefaultLocaleName();
BOOL test_GetSystemDefaultLocaleName();

BOOL test_DnsHostnameToComputerNameW();
BOOL test_AddLocalAlternateComputerNameW();
BOOL test_AddLocalAlternateComputerNameA();
BOOL test_DnsHostnameToComputerNameA();
BOOL test_GetNumaAvailableMemoryNode();

BOOL test_GetLongPathNameTransactedW();
BOOL test_GetLongPathNameTransactedA();
BOOL test_GetFullPathNameTransactedW();
BOOL test_GetFullPathNameTransactedA();

/* SetComputerName ���� �Լ����� ������Ʈ�� Ű���� ��Ȯ�� Set�Ǿ������� Ȯ���ϱ� ���� ����� */
BOOL GetRegLocalMachineValueW(wchar_t *path, wchar_t *valueName, wchar_t *value);
BOOL GetRegLocalMachineValueA(char *path, char *valueName, char *value);

#endif