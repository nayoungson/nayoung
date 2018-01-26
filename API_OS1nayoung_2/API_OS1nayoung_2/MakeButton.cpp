/*
*	작성자 : OQA1 손찬영
*/

#include "MakeButton.h"

int buttonCount = 0; //버튼 갯수
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

int pageCount = 0; //페이지 갯수

void CreateButtonForTest(HWND hWnd, HINSTANCE g_hInst, HWND *hBtn)
{
	int posX = BUTTON_POS_X;
	int posY = BUTTON_POS_Y;
	int marginX = BUTTON_MARGIN_X;
	int marginY = BUTTON_MARGIN_Y;
	int hMenu=0;
	int btnLine = 1; //페이지 넘어가면 초기화
	TCHAR buttonName[TEST_FUNC_LEN];
	BOOL isPageChanged = FALSE;

	printf("Start : CreateButtonForTest()\n");
	while((funcName[hMenu][0] != L'\0') && (hMenu < MAX_TEST_BUTTON)){ //funcName은 '\0'으로 초기화 되어있음?

		wsprintf((LPWSTR)buttonName, TEXT("%s"), funcName[hMenu]);

		//printf("hMenu = %d, posX = %d, posY = %d\n", hMenu, posX, posY);
		hBtn[hMenu] = CreateWindow(L"button", buttonName, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, posX, posY, BUTTON_WIDTH, BUTTON_HEIGHT, hWnd, (HMENU)hMenu, g_hInst, NULL);
		//printf("hBtn[%d] = %p\n", hMenu, hBtn[hMenu]);
		
		posX = posX + BUTTON_WIDTH + BUTTON_MARGIN_X;
		hMenu++;
		if(((hMenu%BUTTON_PER_PAGE) == 0) && (hMenu != 0)){	//다른 페이지에 있는 버튼이면 좌표값을 초기화 한다.
			//printf("%d 버튼부터 다른 페이지 버튼입니다\n", hMenu);
			//wprintf(L"buttonName = %s", buttonName);
			//printf("hMenu = %d\n", hMenu);
			posX = BUTTON_POS_X;
			posY = BUTTON_POS_Y;
			isPageChanged = TRUE;
			btnLine = 0;
		}

		//printf("%d에서 페이지가 교체되었습니다.\n", hMenu);
		if(((btnLine%BUTTON_PER_LINE) == 0) && (btnLine != 0) && ((hMenu%BUTTON_PER_PAGE) != 0)){ //한 줄이 가득 차면 줄을 바꾼다
			//printf("%d번째 버튼에 줄바꿈합니다\n", hMenu);
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

	//버튼 개수 세기
	while(funcName[buttonCount][0] != L'\0'){ //값이 들어있는 동안
		buttonCount++;
	}
	pageCount = (int)ceil((double)buttonCount / buttonPerPage); // 페이지 총 개수 = 버튼 수 * 1/(페이지당 버튼 수) 올려야 함
	//printf("버튼갯수 = %d\n버튼퍼페이지 = %d\n페이지 갯수(pageCount) = %d\n", buttonCount, buttonPerPage, pageCount);

	//printf("페이지버튼 개수 = %d\n", pageCount);
	posX = (pageCount + 2)*PAGE_BUTTON_WIDTH + (pageCount + 1)*PAGE_BUTTON_MARGIN_X;
	posX = (WINDOW_WIDTH - posX) / 2;
	//printf("버튼 위치는 %d\n", posX);


	//[이전] 버튼을  생성 //PAGE_BUTTON_PREV_ID = 1025
	//printf("prev : %d번 버튼을 생성합니다...\n", PAGE_BUTTON_PREV_ID);
	CreateWindow(L"button", L"<", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, posX, posY, PAGE_BUTTON_WIDTH, PAGE_BUTTON_HEIGHT, hWnd, (HMENU)PAGE_BUTTON_PREV_ID, g_hInst, NULL);
	posX = posX + PAGE_BUTTON_WIDTH + PAGE_BUTTON_MARGIN_X;

	while(index < pageCount){ 
		wsprintf((LPWSTR)buttonName, TEXT("%d"), index+1);

		//printf("페이지 : %d번 버튼을 생성합니다...\n", pageButtonID);
		hPageBtn[index] = CreateWindow(L"button", buttonName, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, posX, posY, PAGE_BUTTON_WIDTH, PAGE_BUTTON_HEIGHT, hWnd, (HMENU)pageButtonID, g_hInst, NULL);
		posX = posX + PAGE_BUTTON_WIDTH + PAGE_BUTTON_MARGIN_X;
		pageButtonID++;

		index++;
		_wcsnset(buttonName, '\0', TEST_FUNC_LEN);
	}

	//[다음] 버튼을 생성 //PAGE_BUTTON_NEXT_ID = 1026
	//printf("next : %d번 버튼을 생성합니다...\n", PAGE_BUTTON_NEXT_ID);
	CreateWindow(L"button", L">", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, posX, posY, PAGE_BUTTON_WIDTH, PAGE_BUTTON_HEIGHT, hWnd, (HMENU)PAGE_BUTTON_NEXT_ID, g_hInst, NULL);
	
	//printf("다음 버튼 위치는 %d\n", posX);

	printf("End : CreateButtonForPaging()\n");
}

//CREATETAB CreateTabForTest(HWND hWnd, HINSTANCE g_hInst)
//{
//	TCITEM tie;
//	TCHAR *arNum[3] = {L"첫번째 페이지", L"두번째 페이지", L"세번째 페이지"};
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
//	tie.pszText = L"김유진";
//	TabCtrl_InsertItem(ret.hTab, 0, &tie);
//	tie.pszText = L"박영수";
//	TabCtrl_InsertItem(ret.hTab, 1, &tie);
//	tie.pszText = L"부유정";
//	TabCtrl_InsertItem(ret.hTab, 2, &tie);
//
//	return ret;
//}

