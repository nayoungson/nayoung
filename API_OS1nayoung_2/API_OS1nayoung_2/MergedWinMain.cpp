/*
*	작성자 : OQA1 손찬영
*/

#include "MergedWinMain.h"
#include "Paging.h"
#include "OS1HeaderList.h"
#include "OSQA.h"


HWND hWnd, hWndPaint;
BOOL isManual = FALSE;


HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("OS1 API TEST");
LPCTSTR paintWindow = TEXT("PAINT WINDOW");

extern int buttonCount; //버튼 갯수
extern HWND hBtn[MAX_TEST_BUTTON];


int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow )
{
	MSG Message;
	WNDCLASS WndClass, WndClass2;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass( &WndClass );

	hWnd = CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL); 
	ShowWindow( hWnd, nCmdShow );

	WndClass2.cbClsExtra = 0;
	WndClass2.cbWndExtra = 0;
	WndClass2.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass2.hCursor = LoadCursor(NULL,IDC_ARROW);
	WndClass2.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	WndClass2.hInstance = hInstance;
	WndClass2.lpfnWndProc = WndProc2;
	WndClass2.lpszClassName = paintWindow;
	WndClass2.lpszMenuName = NULL;
	WndClass2.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass( &WndClass2 );
	hWndPaint = CreateWindow(paintWindow, paintWindow, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, PAINT_WINDOW_WIDTH, PAINT_WINDOW_HEIGHT, NULL, NULL, hInstance, NULL); 
	//ShowWindow( hWndPaint, nCmdShow );

	while( GetMessage( &Message, NULL, 0, 0 ) )
	{
		TranslateMessage( &Message );
		DispatchMessage( &Message );
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam )
{
	WORD index;
	int pageNextID = 0, pagePrevID = 0;
	static int autoFuncCount = AUTO_TEST_BUTTON;

	//PAINTSTRUCT ps;
	//HDC hdc;

	switch( iMessage ){
		
	case WM_CREATE:
		CreateButtonForTest(hWnd, g_hInst, hBtn);
		CreateButtonForPaging(hWnd, g_hInst);
		SelectPage(hWnd, PAGE_BUTTON_ID); //0번 페이지를 클릭한 것처럼..초기화

		//실제 autobutton 갯수를 센다.
		for(int i=0; i<AUTO_TEST_BUTTON; i++){
			if(!autoFuncTable[i][0] && i > 0){ //만약에 비어있다면,
				autoFuncCount = i;
				printf("autoFuncCount = %d\n", autoFuncCount);
				break;
			}
		}

		break;

	case WM_COMMAND:
		index = LOWORD(wParam);
		//printf("index = %d\n", LOWORD(wParam));

		

		//auto test 버튼 클릭 시,
		if((0 <= index) && (index < autoFuncCount)){
			//printf("---------------------------[START AUTO_TEST%d]---------------------------\n",index+1);
			for(int i=0; i<AUTO_TEST_PER_BUTTON; i++){
				//printf("autoFuncTable[%d][%d]()\n", index, i);
				if(!autoFuncTable[index][i]) //가리키는 함수 없으면 break;
					break;
				
				autoFuncTable[index][i]();
				
			}
			//printf("---------------------------[END AUTO_TEST%d]---------------------------\n",index+1);
		}
		else if((autoFuncCount <= index) && (index < MAX_TEST_BUTTON+1)){ //일반 테스트 버튼
			//if(funcTable[index]){
				//#ifdef OQADBGPRINT
				//printf("[CLICK (%d)] : ", index);
				//#endif
				//printf("autoFuncTable[%d]()\n", index - autoFuncCount);
				funcTable[index - autoFuncCount]();
			//}
		}
		//else if(index == PAGE_BUTTON_PREV_ID){ //이전 버튼을 클릭
		//	pagePrevID = currentPage + PAGE_BUTTON_ID + 1;
		//	//SelectPage(hWnd, currentPage + PAGE_BUTTON_ID - 1); 
		//
		//}else if(index == PAGE_BUTTON_NEXT_ID){ //다음 버튼을 클릭
		//	pageNextID = currentPage + PAGE_BUTTON_ID + 1;
		//	//SelectPage(hWnd, pageNextID); 
		//
		//}else{ // 페이지 버튼, 마지막 페이지 버튼을 알 수 없어 일단 else로..
		//	//SelectPage(hWnd, index);
		//}

		return 0;

	case WM_DESTROY:
		//FreeFuncNameList(funcName);
		system("pause");
		PostQuitMessage(0);

		return 0;
	}
	return( DefWindowProc( hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK WndProc2( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam )
{

	PAINTSTRUCT ps;
	HDC hdc;
	HPEN Pen;
	POINT pt = {0, }, margin = {0, };
	int nLine = 0;
	DWORD Style[] = {1, 3, 1, 3, 1, 3, 1, 3, 1, 3};
	LOGBRUSH logbrush;

	switch( iMessage ){
		
	case WM_CREATE:
		

		break;

	case WM_COMMAND:


		return 0;

	case WM_PAINT: 
		pt.x = 0;
		pt.y = 0;
		margin.x = 50;
		margin.y = 50;

		hdc = BeginPaint(hWndPaint, &ps);

		logbrush.lbStyle=BS_SOLID;
		logbrush. lbColor = RGB(195, 195, 195);
		logbrush.lbHatch = 0;
		Pen = ExtCreatePen(PS_GEOMETRIC | PS_USERSTYLE, 1, &logbrush, 10, Style);
		
		
		SelectObject(hdc, Pen);
		SetROP2(hdc, R2_XORPEN);

		for(; pt.x <= PAINT_WINDOW_WIDTH; pt.x+=margin.x){
			//printf("(%d, 0)부터 (%d, %d)까지\n", pt.x, pt.x, PAINT_WINDOW_HEIGHT);
			MoveToEx(hdc, pt.x, 0, NULL);
			LineTo(hdc, pt.x, PAINT_WINDOW_HEIGHT);
		}

		for(; pt.y <= PAINT_WINDOW_HEIGHT; pt.y+=margin.y){
			//printf("(0, %d)부터 (%d, %d)까지\n", pt.y, PAINT_WINDOW_HEIGHT, pt.y);
			MoveToEx(hdc, 0, pt.y, NULL);
			LineTo(hdc, PAINT_WINDOW_WIDTH, pt.y);

		}
		EndPaint(hWndPaint, &ps);

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);

		return 0;
	}
	return( DefWindowProc( hWnd, iMessage, wParam, lParam));
}