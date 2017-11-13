#include <windows.h>
#include <atlstr.h>



#include "손나영\TestCriticalSection.h"
#include "손나영\TestEventHG.h"
#include "손나영\TestFunction.h"
#include "손나영\TestFunctionPPT.h"
#include "손나영\TestMemory.h"
#include "손나영\TestModule.h"
#include "손나영\TestProcessF.h"
#include "손나영\TestProcessor.h"
#include "손나영\TestRegistry.h"

#pragma comment(linker, "/entry:WinMainCRTStartup")
#pragma comment(linker, "/subsystem:console")

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("7ip+FileZilla+v3 lite _ API TEST _ NAYOUNG");

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
	HKEY key=0;
	LONG ret=0;

	switch (iMessage) {  
	case WM_CREATE:
		
		

		CreateWindow(L"button", L"------------ 11/10 - 11/16 [1주차] ------------", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,0,250,40,hWnd,(HMENU)0,g_hInst,NULL);	
		CreateWindow(L"button", L"DeregisterEventSource", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,50,250,40,hWnd,(HMENU)1,g_hInst,NULL);
		CreateWindow(L"button", L"EventActivityIdControl", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,100,250,40,hWnd,(HMENU)2,g_hInst,NULL); 
		CreateWindow(L"button", L"EventUnregister", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,150,250,40,hWnd,(HMENU)3,g_hInst,NULL);
		CreateWindow(L"button", L"EventWriteTransfer", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,200,250,40,hWnd,(HMENU)4,g_hInst,NULL);
		CreateWindow(L"button", L"RegisterEventSourceA", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,250,250,40,hWnd,(HMENU)5,g_hInst,NULL);
		CreateWindow(L"button", L" ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,300,250,40,hWnd,(HMENU)6,g_hInst,NULL);	
		CreateWindow(L"button", L" ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,350,250,40,hWnd,(HMENU)7,g_hInst,NULL);	
		CreateWindow(L"button", L" ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,400,250,40,hWnd,(HMENU)8,g_hInst,NULL);	
		CreateWindow(L"button", L" ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,450,250,40,hWnd,(HMENU)9,g_hInst,NULL);
		CreateWindow(L"button", L" ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,500,250,40,hWnd,(HMENU)10,g_hInst,NULL);	
		CreateWindow(L"button", L" ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,550,250,40,hWnd,(HMENU)11,g_hInst,NULL);
		CreateWindow(L"button", L" ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,600,250,40,hWnd,(HMENU)12,g_hInst,NULL);	
		CreateWindow(L"button", L" ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,650,250,40,hWnd,(HMENU)13,g_hInst,NULL);	
		CreateWindow(L"button", L" ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,700,250,40,hWnd,(HMENU)14,g_hInst,NULL);	
		CreateWindow(L"button", L" ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,750,250,40,hWnd,(HMENU)15,g_hInst,NULL);	
		CreateWindow(L"button", L" ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,0,250,40,hWnd,(HMENU)16,g_hInst,NULL);	
		CreateWindow(L"button", L" ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,50,250,40,hWnd,(HMENU)17,g_hInst,NULL);	
		CreateWindow(L"button", L" ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,100,250,40,hWnd,(HMENU)18,g_hInst,NULL);	
		CreateWindow(L"button", L" ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,150,250,40,hWnd,(HMENU)19,g_hInst,NULL);
		CreateWindow(L"button", L" ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,200,250,40,hWnd,(HMENU)20,g_hInst,NULL);
		CreateWindow(L"button", L" ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300,250,250,40,hWnd,(HMENU)21,g_hInst,NULL);


		break;

	case WM_COMMAND:
		switch(LOWORD(wParam)){

		case 1: 
			test_DeregisterEventSource();
			break;	
		case 2:
			test_EventActivityIdControl();
			break;
		case 3:
			test_EventUnregister();
			break;
		case 4:
			test_EventWriteTransfer();
			break;
		case 5:
			test_RegisterEventSourceA();
			break;
		}
		return 0;

	case WM_DESTROY:
		system("pause");
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}