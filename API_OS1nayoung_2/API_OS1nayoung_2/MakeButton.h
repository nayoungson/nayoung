/*
*	�ۼ��� : OQA1 ������
*/

#ifndef MAKEBUTTON
#define MAKEBUTTON

//#pragma comment(lib,"Comctl32.lib") //for InitCommonControls()

#include <Windows.h>
//#include <CommCtrl.h>
#include "Paging.h"
#include <math.h>
#include "OS1HeaderList.h"

#define WINDOW_WIDTH 1130
#define WINDOW_HEIGHT 500
#define PAINT_WINDOW_WIDTH 370
#define PAINT_WINDOW_HEIGHT 390

#define BUTTON_POS_X 10
#define BUTTON_POS_Y 10
#define BUTTON_WIDTH 250
#define BUTTON_HEIGHT 30
#define BUTTON_MARGIN_X 30
#define BUTTON_MARGIN_Y 10

#define PAGE_BUTTON_POS_X 200
#define PAGE_BUTTON_POS_Y 400
#define PAGE_BUTTON_WIDTH 30
#define PAGE_BUTTON_HEIGHT 30
#define PAGE_BUTTON_MARGIN_X 10
#define PAGE_BUTTON_MARGIN_Y 40

#define PAGE_BUTTON_PREV_ID (MAX_TEST_BUTTON+1)  //2049
#define PAGE_BUTTON_NEXT_ID (PAGE_BUTTON_PREV_ID+1) //2050
#define PAGE_BUTTON_ID (PAGE_BUTTON_NEXT_ID+1) //1�� ������ ��ư ID //2051���� ����

#define BUTTON_PER_PAGE 36 //������ �� ��ư ����
#define BUTTON_PER_LINE 4 //������ �� ��ư ����

#define MAX_PAGE_BUTTON 128 //������ ��ư �ִ� ����
#define MAX_TEST_BUTTON 2048 //�׽�Ʈ �Լ� �ִ� ����
#define AUTO_TEST_BUTTON 15 //�����׽�Ʈ ��ư ����
#define	AUTO_TEST_PER_BUTTON 50 //��ư1���� �ڵ� �׽�Ʈ�ϴ� �Լ� ����
#define TEST_FUNC_LEN 1024 //�Լ� 1�� �̸� ���� �ִ밪


typedef BOOL (*funcPtr)(void);

typedef struct _CREATETAB{
	HWND hTab;
	HWND hStatic;
} CREATETAB;

extern int buttonCount; //��ư ����
extern int pageCount; //������ ����
extern HWND hBtn[];
extern HWND hPageBtn[];

//�� ������ MakeButton.cpp���� �ʱ�ȭ�մϴ�.
extern const wchar_t funcName[MAX_TEST_BUTTON][TEST_FUNC_LEN];

const funcPtr autoFuncTable[AUTO_TEST_BUTTON][AUTO_TEST_PER_BUTTON]={
	{

	}
};

//�� ������ ���� funcName ���� ����, ������ ����(���η� test_������ �߰���)�ؾ��մϴ�.
const funcPtr funcTable[MAX_TEST_BUTTON]={ //[return type : BOOL, parameter : (void)]���� �Լ��� ����Ű�� ������

//test_DeregisterEventSource,
//test_EnumDependentServicesA,
//test_EventActivityIdControl,
//test_EventUnregister,
//test_EventWriteTransfer,
//test_RegisterEventSourceA,
//test_ReportEventA,
//test_GetEnhMetaFileA,
//test_GetEnhMetaFileW,
//test_GetMetaFileA,
//test_GetMetaFileW,
//test_GetKeyboardType,
//test_GetPriorityClipboardFormat,
//test_MapVirtualKeyA,
//test_MapVirtualKeyExA,
//test_VkKeyScanA,

test_GetConsoleAliasA,
test_GetConsoleAliasesA,
test_GetConsoleAliasesLengthA,
test_GetConsoleAliasesLengthW,
test_GetConsoleAliasesW,
test_GetConsoleAliasExesA,
test_GetConsoleAliasExesLengthA,
test_GetConsoleAliasExesLengthW,
test_GetConsoleAliasExesW,
test_GetConsoleAliasW,
test_GetConsoleFontSize,
test_GetConsoleHistoryInfo,
test_GetConsoleOriginalTitleA,
test_GetConsoleOriginalTitleW,
test_GetConsoleScreenBufferInfoEx,
test_GetConsoleSelectionInfo,
test_GetConsoleTitleA,
test_GetCurrentConsoleFont,
test_GetCurrentConsoleFontEx,
test_GetLargestConsoleWindowSize,
test_GetNumberOfConsoleMouseButtons,
test_SetConsoleHistoryInfo,
test_SetConsoleScreenBufferInfoEx,
test_SetCurrentConsoleFontEx,
test_SetCurrentConsoleFontEx,

//test_InitializeCriticalSectionAndSpinCount,
//test_InitializeCriticalSectionEx,
//test_TryEnterCriticalSection,
//
//test_DeregisterEventSource,
//test_EnumDependentServicesA,
//test_EventActivityIdControl,
//test_EventUnregister,
//test_EventWriteTransfer,
//test_RegisterEventSourceA,
//test_ReportEventA,
//
//test_Beep,
//test_CreateHardLinkW,
//test_CreateJobObjectW,
//test_FatalAppExitA,
//test_GetPriorityClass,
//test_GetProfileIntW,
//test_SetHandleCount,
//test_SetInformationJobObject,
//test_SetPriorityClass,
//
//test_CreateHardLinkTransactedA,
//test_CreateHardLinkTransactedW,
//test_CreateSymbolicLinkTransactedA,
//test_CreateSymbolicLinkTransactedW,
//test_FatalAppExitW,
//test_FatalExit,
////test_FreeLibraryAndExitThread,  //kerneldll block
//test_GetApplicationRestartSettings,
//test_GetFinalPathNameByHandleA,
//test_GetVolumeInformationByHandleW,
//test_ReadThreadProfilingData,
//test_RegisterApplicationRestart,
////test_RegLoadMUIStringA,
////test_RegLoadMUIStringW,
//test_SetCriticalSectionSpinCount,
//test_SetFileInformationByHandle,
//test_SetStdHandleEx,
//test_UnregisterApplicationRestart,
//
//test_RegCloseKey,
//test_RegCreateKeyExW,
//test_RegCreateKeyW,
//test_RegDeleteKeyExW,
//test_RegDeleteKeyW,
//test_RegDeleteTreeW,
//test_RegDeleteValueW,
//test_RegDisablePredefinedCacheEx,
//test_RegEnumKeyExA,
//test_RegEnumKeyExW,
//test_RegEnumKeyW,
//test_RegEnumValueW,
//test_RegGetKeySecurity,
//test_RegGetValueW,
//test_RegLoadKeyA,
//test_RegLoadKeyW,
//test_RegNotifyChangeKeyValue,
//test_RegOpenCurrentUser,
//test_RegOpenKeyExW,
//test_RegOpenKeyW,
//test_RegOpenUserClassesRoot,
//test_RegQueryInfoKeyW,
//test_RegQueryValueExW,
//test_RegSaveKeyExA,
//test_RegSaveKeyExW,
//test_RegSetKeySecurity,
//test_RegSetValueExW,
//test_RegUnLoadKeyA,
//test_RegUnLoadKeyW,
//
//
//test_AddSecureMemoryCacheCallback,
//test_AllocateUserPhysicalPages,
//test_AllocateUserPhysicalPagesNuma,
//test_FreeUserPhysicalPages,
//test_GetLargePageMinimum,
//test_GetNumaProximityNode,
//test_GetNumaProximityNodeEx,
//test_K32GetProcessMemoryInfo,
//test_MapUserPhysicalPages,
//test_RemoveSecureMemoryCacheCallback,
//test_Toolhelp32ReadProcessMemory,
//test_VirtualAllocExNuma,
//test_WerRegisterMemoryBlock,
//test_WerUnregisterMemoryBlock,
//
//test_GetEnhMetaFileA,
//test_GetEnhMetaFileW,
//test_GetMetaFileA,
//test_GetMetaFileW,
//
//
//test_K32GetModuleBaseNameA,
//test_K32GetModuleBaseNameW,
//test_K32GetModuleFileNameExA,
//test_K32GetModuleFileNameExW,
//test_K32GetModuleInformation,
//test_LoadModule,
//test_Module32FirstW,
//test_Module32NextW,
//
//
//test_GetActiveProcessorCount,
//test_GetActiveProcessorGroupCount,
//test_GetCurrentProcessorNumber,
//test_GetCurrentProcessorNumberEx,
//test_GetLogicalProcessorInformationEx,
//test_GetMaximumProcessorCount,
//test_GetNumaNodeProcessorMask,
//test_GetNumaNodeProcessorMaskEx,
//test_GetNumaProcessorNodeEx,
//
//
//
//test_FlushProcessWriteBuffers,
//test_GetMaximumProcessorGroupCount,
//test_GetNumaNodeNumberFromHandle,
//test_GetNumaProcessorNode,
//test_GetProcessDEPPolicy,
//test_GetProcessGroupAffinity,
//test_GetProcessHandleCount,
//test_GetProcessId,
//test_GetProcessPriorityBoost,
//test_GetProcessShutdownParameters,
//test_GetProcessWorkingSetSize,
//test_GetProcessWorkingSetSizeEx,
//test_IsProcessInJob,
//test_K32EnumProcesses,
//test_K32EnumProcessModules,
//test_K32EnumProcessModulesEx,
//test_K32InitializeProcessForWsWatch,
//test_QueryProcessAffinityUpdateMode,
//test_SetProcessAffinityUpdateMode,
//test_SetProcessDEPPolicy,
//test_SetProcessPriorityBoost,
//test_SetProcessShutdownParameters,
//
//
//test_GetKeyboardType,
//test_GetPriorityClipboardFormat,
//test_MapVirtualKeyA,
//test_MapVirtualKeyExA,
//test_VkKeyScanA,
//test_VkKeyScanA,


};


void CreateButtonForTest(HWND hWnd, HINSTANCE g_hInst, HWND *hBtn);
void CreateButtonForPaging(HWND hWnd, HINSTANCE g_hInst);
//CREATETAB CreateTabForTest(HWND hWnd, HINSTANCE g_hInst);



#endif