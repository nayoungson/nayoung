/*
*	�ۼ��� : OQA1 ������
*/

#include "MakeButton.h"

int buttonCount = 0; //��ư ����
HWND hBtn[MAX_TEST_BUTTON] = {0, };
HWND hPageBtn[MAX_PAGE_BUTTON] = {0, };

const wchar_t funcName[MAX_TEST_BUTTON][TEST_FUNC_LEN]={

L"--------",
//L"DeregisterEventSource",
//L"EnumDependentServicesA",
//L"EventActivityIdControl",
//L"EventUnregister",
//L"EventWriteTransfer",
//L"RegisterEventSourceA",
//L"ReportEventA",
//L"GetEnhMetaFileA",
//L"GetEnhMetaFileW",
//L"GetMetaFileA",
//L"GetMetaFileW",
//L"GetKeyboardType",
//L"GetPriorityClipboardFormat",
//L"MapVirtualKeyA",
//L"MapVirtualKeyExA",
//L"VkKeyScanA",

L"GetConsoleAliasA",
L"GetConsoleAliasesA",
L"GetConsoleAliasesLengthA",
L"GetConsoleAliasesLengthW",
L"GetConsoleAliasesW",
L"GetConsoleAliasExesA",
L"GetConsoleAliasExesLengthA",
L"GetConsoleAliasExesLengthW",
L"GetConsoleAliasExesW",
L"GetConsoleAliasW",
L"GetConsoleFontSize",
L"GetConsoleHistoryInfo",
L"GetConsoleOriginalTitleA",
L"GetConsoleOriginalTitleW",
L"GetConsoleScreenBufferInfoEx",
L"GetConsoleSelectionInfo",
L"GetConsoleTitleA",
L"GetCurrentConsoleFont",
L"GetCurrentConsoleFontEx",
L"GetLargestConsoleWindowSize",
L"GetNumberOfConsoleMouseButtons",
L"SetConsoleHistoryInfo",
L"SetConsoleScreenBufferInfoEx",
L"SetCurrentConsoleFontEx",



//L"InitializeCriticalSectionAndSpinCount",
//L"InitializeCriticalSectionEx",
//L"TryEnterCriticalSection",
//
//L"DeregisterEventSource",
//L"EnumDependentServicesA",
//L"EventActivityIdControl",
//L"EventUnregister",
//L"EventWriteTransfer",
//L"RegisterEventSourceA",
//L"ReportEventA",
//
//L"Beep",
//L"CreateHardLinkW",
//L"CreateJobObjectW",
//L"FatalAppExitA",
//L"GetPriorityClass",
//L"GetProfileIntW",
//L"SetHandleCount",
//L"SetInformationJobObject",
//L"SetPriorityClass",
//
//L"CreateHardLinkTransactedA",
//L"CreateHardLinkTransactedW",
//L"CreateSymbolicLinkTransactedA",
//L"CreateSymbolicLinkTransactedW",
//L"FatalAppExitW",
//L"FatalExit",
////L"FreeLibraryAndExitThread",  //kerneldll block
//L"GetApplicationRestartSettings",
//L"GetFinalPathNameByHandleA",
//L"GetVolumeInformationByHandleW",
//L"ReadThreadProfilingData",
//L"RegisterApplicationRestart",
////L"RegLoadMUIStringA",
////L"RegLoadMUIStringW",
//L"SetCriticalSectionSpinCount",
//L"SetFileInformationByHandle",
//L"SetStdHandleEx",
//L"UnregisterApplicationRestart",
//
//L"RegCloseKey",
//L"RegCreateKeyExW",
//L"RegCreateKeyW",
//L"RegDeleteKeyExW",
//L"RegDeleteKeyW",
//L"RegDeleteTreeW",
//L"RegDeleteValueW",
//L"RegDisablePredefinedCacheEx",
//L"RegEnumKeyExA",
//L"RegEnumKeyExW",
//L"RegEnumKeyW",
//L"RegEnumValueW",
//L"RegGetKeySecurity",
//L"RegGetValueW",
//L"RegLoadKeyA",
//L"RegLoadKeyW",
//L"RegNotifyChangeKeyValue",
//L"RegOpenCurrentUser",
//L"RegOpenKeyExW",
//L"RegOpenKeyW",
//L"RegOpenUserClassesRoot",
//L"RegQueryInfoKeyW",
//L"RegQueryValueExW",
//L"RegSaveKeyExA",
//L"RegSaveKeyExW",
//L"RegSetKeySecurity",
//L"RegSetValueExW",
//L"RegUnLoadKeyA",
//L"RegUnLoadKeyW",
//
//L"AddSecureMemoryCacheCallback",
//L"AllocateUserPhysicalPages",
//L"AllocateUserPhysicalPagesNuma",
//L"FreeUserPhysicalPages",
//L"GetLargePageMinimum",
//L"GetNumaProximityNode",
//L"GetNumaProximityNodeEx",
//L"K32GetProcessMemoryInfo",
//L"MapUserPhysicalPages",
//L"RemoveSecureMemoryCacheCallback",
//L"Toolhelp32ReadProcessMemory",
//L"VirtualAllocExNuma",
//L"WerRegisterMemoryBlock",
//L"WerUnregisterMemoryBlock",
//
//L"GetEnhMetaFileA",
//L"GetEnhMetaFileW",
//L"GetMetaFileA",
//L"GetMetaFileW",
//
//
//L"K32GetModuleBaseNameA",
//L"K32GetModuleBaseNameW",
//L"K32GetModuleFileNameExA",
//L"K32GetModuleFileNameExW",
//L"K32GetModuleInformation",
//L"LoadModule",
//L"Module32FirstW",
//L"Module32NextW",
//
//
//L"GetActiveProcessorCount",
//L"GetActiveProcessorGroupCount",
//L"GetCurrentProcessorNumber",
//L"GetCurrentProcessorNumberEx",
//L"GetLogicalProcessorInformationEx",
//L"GetMaximumProcessorCount",
//L"GetNumaNodeProcessorMask",
//L"GetNumaNodeProcessorMaskEx",
//L"GetNumaProcessorNodeEx",
//
//
//L"FlushProcessWriteBuffers",
//L"GetMaximumProcessorGroupCount",
//L"GetNumaNodeNumberFromHandle",
//L"GetNumaProcessorNode",
//L"GetProcessDEPPolicy",
//L"GetProcessGroupAffinity",
//L"GetProcessHandleCount",
//L"GetProcessId",
//L"GetProcessPriorityBoost",
//L"GetProcessShutdownParameters",
//L"GetProcessWorkingSetSize",
//L"GetProcessWorkingSetSizeEx",
//L"IsProcessInJob",
//L"K32EnumProcesses",
//L"K32EnumProcessModules",
//L"K32EnumProcessModulesEx",
//L"K32InitializeProcessForWsWatch",
//L"QueryProcessAffinityUpdateMode",
//L"SetProcessAffinityUpdateMode",
//L"SetProcessDEPPolicy",
//L"SetProcessPriorityBoost",
//L"SetProcessShutdownParameters",
//
//
//L"GetKeyboardType",
//L"GetPriorityClipboardFormat",
//L"MapVirtualKeyA",
//L"MapVirtualKeyExA",
//L"VkKeyScanA",


};

int pageCount = 0; //������ ����

void CreateButtonForTest(HWND hWnd, HINSTANCE g_hInst, HWND *hBtn)
{
	int posX = BUTTON_POS_X;
	int posY = BUTTON_POS_Y;
	int marginX = BUTTON_MARGIN_X;
	int marginY = BUTTON_MARGIN_Y;
	int hMenu=0;
	int btnLine = 1; //������ �Ѿ�� �ʱ�ȭ
	TCHAR buttonName[TEST_FUNC_LEN];
	BOOL isPageChanged = FALSE;

	printf("Start : CreateButtonForTest()\n");
	while((funcName[hMenu][0] != L'\0') && (hMenu < MAX_TEST_BUTTON)){ //funcName�� '\0'���� �ʱ�ȭ �Ǿ�����?

		wsprintf((LPWSTR)buttonName, TEXT("%s"), funcName[hMenu]);

		//printf("hMenu = %d, posX = %d, posY = %d\n", hMenu, posX, posY);
		hBtn[hMenu] = CreateWindow(L"button", buttonName, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, posX, posY, BUTTON_WIDTH, BUTTON_HEIGHT, hWnd, (HMENU)hMenu, g_hInst, NULL);
		//printf("hBtn[%d] = %p\n", hMenu, hBtn[hMenu]);
		
		posX = posX + BUTTON_WIDTH + BUTTON_MARGIN_X;
		hMenu++;
		if(((hMenu%BUTTON_PER_PAGE) == 0) && (hMenu != 0)){	//�ٸ� �������� �ִ� ��ư�̸� ��ǥ���� �ʱ�ȭ �Ѵ�.
			//printf("%d ��ư���� �ٸ� ������ ��ư�Դϴ�\n", hMenu);
			//wprintf(L"buttonName = %s", buttonName);
			//printf("hMenu = %d\n", hMenu);
			posX = BUTTON_POS_X;
			posY = BUTTON_POS_Y;
			isPageChanged = TRUE;
			btnLine = 0;
		}

		//printf("%d���� �������� ��ü�Ǿ����ϴ�.\n", hMenu);
		if(((btnLine%BUTTON_PER_LINE) == 0) && (btnLine != 0) && ((hMenu%BUTTON_PER_PAGE) != 0)){ //�� ���� ���� ���� ���� �ٲ۴�
			//printf("%d��° ��ư�� �ٹٲ��մϴ�\n", hMenu);
			posX = BUTTON_POS_X;
			posY = posY + BUTTON_HEIGHT + BUTTON_MARGIN_Y;
			
		}
		btnLine++;
		_wcsnset(buttonName, '\0', TEST_FUNC_LEN);
		isPageChanged = FALSE;
	}

	printf("End : CreateButtonForTest()\n");
}

void CreateButtonForPaging(HWND hWnd, HINSTANCE g_hInst)
{
	int buttonPerPage = BUTTON_PER_PAGE;
	int index = 0;
	TCHAR buttonName[TEST_FUNC_LEN];
	//int buttonCount = 0;
	int posX = PAGE_BUTTON_POS_X;
	int posY = PAGE_BUTTON_POS_Y;
	int margin = 30;
	int pageButtonID = PAGE_BUTTON_ID;

	printf("Start : CreateButtonForPaging()\n");

	//��ư ���� ����
	while(funcName[buttonCount][0] != L'\0'){ //���� ����ִ� ����
		buttonCount++;
	}
	pageCount = (int)ceil((double)buttonCount / buttonPerPage); // ������ �� ���� = ��ư �� * 1/(�������� ��ư ��) �÷��� ��
	//printf("��ư���� = %d\n��ư�������� = %d\n������ ����(pageCount) = %d\n", buttonCount, buttonPerPage, pageCount);

	//printf("��������ư ���� = %d\n", pageCount);
	posX = (pageCount + 2)*PAGE_BUTTON_WIDTH + (pageCount + 1)*PAGE_BUTTON_MARGIN_X;
	posX = (WINDOW_WIDTH - posX) / 2;
	//printf("��ư ��ġ�� %d\n", posX);


	//[����] ��ư��  ���� //PAGE_BUTTON_PREV_ID = 1025
	//printf("prev : %d�� ��ư�� �����մϴ�...\n", PAGE_BUTTON_PREV_ID);
	CreateWindow(L"button", L"<", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, posX, posY, PAGE_BUTTON_WIDTH, PAGE_BUTTON_HEIGHT, hWnd, (HMENU)PAGE_BUTTON_PREV_ID, g_hInst, NULL);
	posX = posX + PAGE_BUTTON_WIDTH + PAGE_BUTTON_MARGIN_X;

	while(index < pageCount){ 
		wsprintf((LPWSTR)buttonName, TEXT("%d"), index+1);

		//printf("������ : %d�� ��ư�� �����մϴ�...\n", pageButtonID);
		hPageBtn[index] = CreateWindow(L"button", buttonName, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, posX, posY, PAGE_BUTTON_WIDTH, PAGE_BUTTON_HEIGHT, hWnd, (HMENU)pageButtonID, g_hInst, NULL);
		posX = posX + PAGE_BUTTON_WIDTH + PAGE_BUTTON_MARGIN_X;
		pageButtonID++;

		index++;
		_wcsnset(buttonName, '\0', TEST_FUNC_LEN);
	}

	//[����] ��ư�� ���� //PAGE_BUTTON_NEXT_ID = 1026
	//printf("next : %d�� ��ư�� �����մϴ�...\n", PAGE_BUTTON_NEXT_ID);
	CreateWindow(L"button", L">", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, posX, posY, PAGE_BUTTON_WIDTH, PAGE_BUTTON_HEIGHT, hWnd, (HMENU)PAGE_BUTTON_NEXT_ID, g_hInst, NULL);
	
	//printf("���� ��ư ��ġ�� %d\n", posX);

	printf("End : CreateButtonForPaging()\n");
}

//CREATETAB CreateTabForTest(HWND hWnd, HINSTANCE g_hInst)
//{
//	TCITEM tie;
//	TCHAR *arNum[3] = {L"ù��° ������", L"�ι�° ������", L"����° ������"};
//	CREATETAB ret;
//
//	InitCommonControls();
//
//	ret.hTab = CreateWindow(WC_TABCONTROL, L"", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
//		0, 0, 0, 0, hWnd, (HMENU)PAGE_BUTTON_ID, g_hInst, NULL);
//
//	ret.hStatic = CreateWindow(L"static", arNum[0], WS_CHILD | WS_VISIBLE,
//		0, 0, 0, 0, hWnd, (HMENU)PAGE_BUTTON_ID, g_hInst, NULL);
//
//	tie.mask = TCIF_TEXT;
//	tie.pszText = L"������";
//	TabCtrl_InsertItem(ret.hTab, 0, &tie);
//	tie.pszText = L"�ڿ���";
//	TabCtrl_InsertItem(ret.hTab, 1, &tie);
//	tie.pszText = L"������";
//	TabCtrl_InsertItem(ret.hTab, 2, &tie);
//
//	return ret;
//}

