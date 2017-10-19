#include <windows.h>
#include <atlstr.h>

#include "MyUtil.h"


#pragma comment(linker, "/entry:WinMainCRTStartup")
#pragma comment(linker, "/subsystem:console")

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("API_OS1nayoung");

HWND hList;

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdParam,int nCmdShow)
{
	MSG Message;
	HWND hWnd=0;
	WNDCLASS WndClass;
	g_hInst=hInstance;

	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	while (GetMessage(&Message,NULL,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message); 
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{

	switch (iMessage) {  
	case WM_CREATE:

		CreateWindow(L"button", L"------------ 9/22 - 9/28 [1주차] ------------", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,0,250,40,hWnd,(HMENU)0,g_hInst,NULL);	
		CreateWindow(L"button", L"SetFileInformationByHandle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,50,250,40,hWnd,(HMENU)1,g_hInst,NULL);
		CreateWindow(L"button", L"SetCriticalSectionSpinCount", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,100,250,40,hWnd,(HMENU)2,g_hInst,NULL); 
		CreateWindow(L"button", L"RegDeleteTreeW", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,150,250,40,hWnd,(HMENU)3,g_hInst,NULL);
		CreateWindow(L"button", L"RegEnumKeyExA", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,200,250,40,hWnd,(HMENU)4,g_hInst,NULL);	
		CreateWindow(L"button", L"SetProcessAffinityUpdateMode", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,250,250,40,hWnd,(HMENU)5,g_hInst,NULL);
		CreateWindow(L"button", L"SetProcessDEPPolicy", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,300,250,40,hWnd,(HMENU)6,g_hInst,NULL);	
		CreateWindow(L"button", L"SetProcessShutdownParameters", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,350,250,40,hWnd,(HMENU)7,g_hInst,NULL);	
		CreateWindow(L"button", L"RegDisablePredefinedCacheEx", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,400,250,40,hWnd,(HMENU)8,g_hInst,NULL);	
		CreateWindow(L"button", L"GetProcessShutdownParameters", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,450,250,40,hWnd,(HMENU)9,g_hInst,NULL);

		CreateWindow(L"button", L"------------ 9/29 - 10/5 [2주차] ------------", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,500,250,40,hWnd,(HMENU)10,g_hInst,NULL);	
		CreateWindow(L"button", L"LoadModule", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,550,250,40,hWnd,(HMENU)11,g_hInst,NULL);
		CreateWindow(L"button", L"GetVolumeInformationByHandleW", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,600,250,40,hWnd,(HMENU)12,g_hInst,NULL);	
		CreateWindow(L"button", L"K32InitializeProcessForWsWatch", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,650,250,40,hWnd,(HMENU)13,g_hInst,NULL);	
		CreateWindow(L"button", L"FatalAppExitW", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,700,250,40,hWnd,(HMENU)14,g_hInst,NULL);	
		CreateWindow(L"button", L"QueryProcessAffinityUpdateMode", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,750,250,40,hWnd,(HMENU)15,g_hInst,NULL);	
		CreateWindow(L"button", L"GetActiveProcessorCount", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,0,250,40,hWnd,(HMENU)16,g_hInst,NULL);	
		CreateWindow(L"button", L"GetActiveProcessorGroupCount", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,50,250,40,hWnd,(HMENU)17,g_hInst,NULL);	
		CreateWindow(L"button", L"GetCurrentProcessorNumber", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,100,250,40,hWnd,(HMENU)18,g_hInst,NULL);	
		CreateWindow(L"button", L"GetLogicalProcessorInformationEx", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,150,250,40,hWnd,(HMENU)19,g_hInst,NULL);
		CreateWindow(L"button", L"GetMaximumProcessorCount", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,200,250,40,hWnd,(HMENU)20,g_hInst,NULL);
		CreateWindow(L"button", L"RegGetValueW", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,250,250,40,hWnd,(HMENU)21,g_hInst,NULL);



		CreateWindow(L"button", L"------------ 10/6 - 10/13 [3주차] ------------", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,300,250,40,hWnd,(HMENU)22,g_hInst,NULL);
		CreateWindow(L"button", L"GetProcessId", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,350,250,40,hWnd,(HMENU)23,g_hInst,NULL);
		CreateWindow(L"button", L"GetProcessWorkingSetSize", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,400,250,40,hWnd,(HMENU)24,g_hInst,NULL);
		CreateWindow(L"button", L"IsProcessInJob", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,450,250,40,hWnd,(HMENU)25,g_hInst,NULL);
		CreateWindow(L"button", L"GetMaximumProcessorGroupCount", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,500,250,40,hWnd,(HMENU)26,g_hInst,NULL);
		CreateWindow(L"button", L"GetNumaProcessorNode", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,550,250,40,hWnd,(HMENU)27,g_hInst,NULL);
		CreateWindow(L"button", L"GetNumaNodeNumberFromHandle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,600,250,40,hWnd,(HMENU)28,g_hInst,NULL);
		CreateWindow(L"button", L"RegOpenCurrentUser", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,650,250,40,hWnd,(HMENU)29,g_hInst,NULL);
		CreateWindow(L"button", L"FatalExit", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,700,250,40,hWnd,(HMENU)30,g_hInst,NULL);
		CreateWindow(L"button", L"AllocateUserPhysicalPages", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,750,250,40,hWnd,(HMENU)31,g_hInst,NULL);
		CreateWindow(L"button", L"FreeUserPhysicalPages", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 580,0,250,40,hWnd,(HMENU)32,g_hInst,NULL);
		CreateWindow(L"button", L"MapUserPhysicalPages", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 580,50,250,40,hWnd,(HMENU)33,g_hInst,NULL);
		CreateWindow(L"button", L"GetLargePageMinimum", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 580,100,250,40,hWnd,(HMENU)34,g_hInst,NULL);
		CreateWindow(L"button", L"GetFinalPathNameByHandleA", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 580,150,250,40,hWnd,(HMENU)35,g_hInst,NULL);
		CreateWindow(L"button", L"GetApplicationRestartSettings", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 580,200,250,40,hWnd,(HMENU)36,g_hInst,NULL);

		
		//CreateWindow(L"button", L"GetProcessWorkingSetSizeEx", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,400,250,40,hWnd,(HMENU)25,g_hInst,NULL);
		//CreateWindow(L"button", L"GetProcessDEPPolicy", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,450,250,40,hWnd,(HMENU)26,g_hInst,NULL);

		CreateWindow(L"button", L"test_Module32FirstW", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1140,0,250,40,hWnd,(HMENU)50,g_hInst,NULL);
		CreateWindow(L"button", L"test_Module32NextW", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1140,50,250,40,hWnd,(HMENU)51,g_hInst,NULL);
	
		break;

	case WM_COMMAND:
		switch(LOWORD(wParam)){
			
		case 11:			test_LoadModule();							break;
		case 12:			test_GetVolumeInformationByHandleW();		break;
		case 13:			test_K32InitializeProcessForWsWatch();		break;
		case 14:			test_FatalAppExitW();						break;
		case 15:			test_QueryProcessAffinityUpdateMode();		break;
		case 16:			test_GetActiveProcessorCount();				break;
		case 17:			test_GetActiveProcessorGroupCount();		break;
		case 18:			test_GetCurrentProcessorNumber();			break;
		case 19:			test_GetLogicalProcessorInformationEx();	break;
		case 20:			test_GetMaximumProcessorCount();			break;
		case 21:			test_RegGetValueW();						break;
		case 23:			test_GetProcessId();						break;
		case 24:			test_GetProcessWorkingSetSize();			break;
		case 25:			test_IsProcessInJob();						break;
		case 26:			test_GetMaximumProcessorGroupCount();		break;
		case 27:			test_GetNumaProcessorNode();				break;
		case 28:			test_GetNumaNodeNumberFromHandle();			break;
		case 29:			test_RegOpenCurrentUser();					break;
		case 30:			test_FatalExit();							break;
		// 1018
		case 31:			test_AllocateUserPhysicalPages();			break;
		case 32:			test_FreeUserPhysicalPages();				break;
		case 33:			test_MapUserPhysicalPages();				break;
		case 34:			test_GetLargePageMinimum();					break;
		case 35:			test_GetFinalPathNameByHandleA();			break;
		case 36:			test_GetApplicationRestartSettings();		break;

		case 50:			test_Module32FirstW();						break;
		case 51:			test_Module32NextW();						break;
		}		
		return 0;


	case WM_DESTROY:
		system("pause");
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}