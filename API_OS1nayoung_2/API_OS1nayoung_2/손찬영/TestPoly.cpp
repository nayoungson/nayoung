#include "TestPoly.h"

/**
* HRGN CreatePolyPolygonRgn(
  _In_ const POINT *lppt,
  _In_ const INT   *lpPolyCounts,
  _In_       int   nCount,
  _In_       int   fnPolyFillMode
);
* 다각형의 연속으로 이루어진 영역을 생성한다. 다각형은 겹칠 수 있음.
* @author : 손찬영  
*
* @param  lppt 논리적 단위로 폴리곤의 정점을 정의하는 POINT 구조체 의 배열을 가리키는 포인터
* @param  lpPolyCounts 각 배열은 lppt가 가리키는 배열의 다각형 중 하나의 점 수를 지정하는 정수 배열에 대한 포인터
* @param  nCount lpPolyCounts가 가리키는 배열의 총 정수
* @param  fnPolyFillMode 영역에있는 픽셀을 확인하는 데 사용되는 채우기 모드
* @return 성공하면 반환 값은 영역 핸들, 실패하면 0
*/
BOOL test_CreatePolyPolygonRgn()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	POINT pt[] = {{0, 0}, {200, 0}, {200, 200}};
	POINT *ppt = pt;
	INT   polyCounts = 3;
	int   nCount = 1;
	int   fnPolyFillMod = ALTERNATE;
	HRGN hRgn = NULL;

	int test[3];
	int *ptest = test;

#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif

	hRgn = CreatePolyPolygonRgn(pt, &polyCounts, nCount, fnPolyFillMod);
	//폴리곤 그려지는지 확인하기 위해 작성
	ShowWindow( hWndPaint, SW_SHOW );
	SetWindowPos(hWndPaint, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
	HDC hdc = GetDC(hWndPaint);
	InvertRgn(hdc, hRgn);

	if(NULL == hRgn){
		sprintf(msg, "CreatePolyPolygonRgn 실패");
		strcpy(buf, "CreatePolyPolygonRgn 실패");

		result = FALSE;
	}else{
		/*sprintf(msg, "CreatePolyPolygonRgn 성공\n좌표 : (%d, %d), (%d, %d), (%d, %d)\n모양 : 삼각형\n색상 : 검정",
			pt[0].x, pt[0].y, pt[1].x, pt[1].y, pt[2].x, pt[2].y);*/
		SetPaintMessage(sizeof(pt)/sizeof(POINT), &pt[0], "검정", "채워진 삼각형", msg);
		strcpy(buf, "CreatePolyPolygonRgn 성공");
	}

	isManual = TRUE;
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CreatePolyPolygonRgn 성공", msg);
	isManual = FALSE;

	ShowWindow( hWndPaint, SW_HIDE );
	ReleaseDC(hWndPaint, hdc);
	DeleteObject(hRgn);

	return result;
}

/**
* HRGN CreatePolygonRgn(
  _In_ const POINT *lppt,
  _In_       int   cPoints,
  _In_       int   fnPolyFillMode
);
* 함수 다각형 영역을 생성한다.
* @author : 손찬영  
*
* @param  lppt 논리적 단위로 폴리곤의 정점을 정의하는 POINT 구조체 의 배열을 가리키는 포인터
* @param  cPoints 배열의 포인트 수
* @param  fnPolyFillMode 영역에있는 픽셀을 확인하는 데 사용되는 채우기 모드
* @return 성공하면 반환 값은 영역 핸들, 실패하면 NULL
*/
BOOL test_CreatePolygonRgn()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	POINT pt[4] = {{0, 0}, {200, 0}, {200, 200}, {0, 200}};
	INT   cPoints = 4;
	int   fnPolyFillMod = ALTERNATE;
	HRGN hRgn = NULL;

#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif

	hRgn = CreatePolygonRgn(pt, cPoints, fnPolyFillMod);
	ShowWindow( hWndPaint, SW_SHOW );
	SetWindowPos(hWndPaint, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
	HDC hdc = GetDC(hWndPaint);
	InvertRgn(hdc, hRgn);

	if(NULL == hRgn){
		sprintf(msg, "CreatePolygonRgn 실패");
		strcpy(buf, "CreatePolygonRgn 실패");

		result = FALSE;
	}else{
		SetPaintMessage(sizeof(pt)/sizeof(POINT), &pt[0], "검정", "채워진 사각형", msg);
		strcpy(buf, "CreatePolygonRgn 성공");
	}

	isManual = TRUE;
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CreatePolygonRgn 성공", msg);
	isManual = FALSE;


	ShowWindow( hWndPaint, SW_HIDE );
	ReleaseDC(hWndPaint, hdc);
	DeleteObject(hRgn);

	return result;
}


/**
* BOOL PolyPolygon(
  _In_       HDC   hdc,
  _In_ const POINT *lpPoints,
  _In_ const INT   *lpPolyCounts,
  _In_       int   nCount
);
* 닫힌 다각형의 시리즈를 그린다. 각 다각형은 현재 펜을 사용하여 윤곽이 지정되고 현재 브러시 및 다각형 채우기 모드를 사용하여 채워진다.
* @author : 손찬영  
*
* @param  hdc 디바이스 컨텍스트 핸들
* @param  lpPoints 논리적 좌표로 폴리곤의 정점을 정의하는 POINT 구조체 의 배열을 가리키는 포인터
* @param  lpPolyCounts 각 다각형의 점 수를 지정하는 정수 배열에 대한 포인터
* @param  nCount 총 폴리곤 수
* @return 성공/실패 여부
*/
BOOL test_PolyPolygon()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	POINT pt[3] = {{75, 75}, {75, 175}, {175, 175}};
	INT   polyCounts = 3;
	int   nCount = 1;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	
	
	ShowWindow( hWndPaint, SW_SHOW );
	SetWindowPos(hWndPaint, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
	HDC hdc = GetDC(hWndPaint);
	result = PolyPolygon(hdc, pt, &polyCounts, nCount);

	if(result){
		SetPaintMessage(sizeof(pt)/sizeof(POINT), &pt[0], "검정", "빈 삼각형", msg);
		strcpy(buf, "PolyPolygon 성공");
		
	}else{
		sprintf(msg, "PolyPolygon 실패");
		strcpy(buf, "PolyPolygon 실패");

		result = FALSE;
		
	}

	isManual = TRUE;
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "PolyPolygon 성공", msg);
	isManual = FALSE;

	ShowWindow( hWndPaint, SW_HIDE );
	ReleaseDC(hWndPaint, hdc);

	return result;
}

/**
* BOOL PolyPolyline(
  _In_       HDC   hdc,
  _In_ const POINT *lppt,
  _In_ const DWORD *lpdwPolyPoints,
  _In_       DWORD cCount
);
* 연결된 일련의 여러 선 세그먼트를 그린다.
* @author : 손찬영  
*
* @param  hdc 디바이스 컨텍스트 핸들
* @param  lppt 논리 단위로 폴리 라인의 정점을 포함하는 POINT 구조체 의 배열을 가리키는 포인터
* @param  lpdwPolyPoints 해당 폴리 라인 에 대한 lppt 배열 의 점 수를 지정하는 변수 배열에 대한 포인터
* @param  cCount lpdwPolyPoints 항목의 수.
* @return 성공/실패 여부
*/
BOOL test_PolyPolyline()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	POINT pt[2] = {{0, 0}, {100, 100}};
	DWORD   polyCounts = 2;
	DWORD   nCount = 1;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	ShowWindow( hWndPaint, SW_SHOW );
	SetWindowPos(hWndPaint, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
	HDC hdc = GetDC(hWndPaint);

	result = PolyPolyline(hdc, pt, &polyCounts, nCount);
	
	if(result){
		SetPaintMessage(sizeof(pt)/sizeof(POINT), &pt[0], "검정", "대각선", msg);
		strcpy(buf, "PolyPolyline 성공");
		
	}else{
		sprintf(msg, "PolyPolyline 실패");
		strcpy(buf, "PolyPolyline 실패");

		result = FALSE;
		
	}
	isManual = TRUE;
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "PolyPolyline 성공", msg);
	isManual = FALSE;

	ShowWindow( hWndPaint, SW_HIDE );
	ReleaseDC(hWndPaint, hdc);

	return result;
}


/**
* BOOL PolyTextOut(
  _In_       HDC      hdc,
  _In_ const POLYTEXT *pptxt,
  _In_       int      cStrings
);

* 현재 지정된 디바이스 컨텍스트에서 선택된 폰트 및 텍스트 색상을 사용하여 여러 문자열을 그린다.
* @author : 손찬영  
*
* @param  hdc 디바이스 컨텍스트 핸들
* @param  pptxt 가져올 문자열을 설명하는 POLYTEXT 구조체 의 배열을 가리키는 포인터
* @param  cStrings POLYTEXT의 의 구조체 배열의 수
* @return 성공/실패 여부
*/
BOOL test_PolyTextOutA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	POLYTEXTA ptxt;
	POINT pt;
	int cStrings = 1;
	char *text = "HELLO";
	int *dx;
	RECT rect = {0, };

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif


	ptxt.x = 50;
	ptxt.y = 150;
	ptxt.n = strlen(text);
	ptxt.lpstr = text;
	ptxt.uiFlags = ETO_OPAQUE;

	ptxt.rcl = rect; //텍스트의 사각형 범위를 설정

	dx = (int *)malloc(sizeof(int)*strlen(text));
	for(int i=0; i<strlen(text); i++){
		dx[i] = 50; //글자간격을  설정
	}
	ptxt.pdx = dx;	

	pt.x = ptxt.x;
	pt.y = ptxt.y;

	ShowWindow( hWndPaint, SW_SHOW );
	SetWindowPos(hWndPaint, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
	HDC hdc = GetDC(hWndPaint);


	result = PolyTextOutA(hdc, &ptxt, cStrings);
	
	if(result){
		SetPaintMessage(sizeof(pt)/sizeof(POINT), &pt, "검정(자간 50)", text, msg);
		strcpy(buf, "PolyTextOutA 성공");
		
	}else{
		sprintf(msg, "PolyTextOutA 실패");
		strcpy(buf, "PolyTextOutA 실패");

		result = FALSE;
		
	}

	isManual = TRUE;
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "PolyTextOutA 성공", msg);
	isManual = FALSE;
	

	ShowWindow( hWndPaint, SW_HIDE );
	ReleaseDC(hWndPaint, hdc);

	return result;
}

/**
* BOOL PolyTextOut(
  _In_       HDC      hdc,
  _In_ const POLYTEXT *pptxt,
  _In_       int      cStrings
);

* 현재 지정된 디바이스 컨텍스트에서 선택된 폰트 및 텍스트 색상을 사용하여 여러 문자열을 그린다.
* @author : 손찬영  
*
* @param  hdc 디바이스 컨텍스트 핸들
* @param  pptxt 가져올 문자열을 설명하는 POLYTEXT 구조체 의 배열을 가리키는 포인터
* @param  cStrings POLYTEXT의 의 구조체 배열의 수
* @return 성공/실패 여부
*/
BOOL test_PolyTextOutW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	POLYTEXT ptxt;
	POINT pt;
	int cStrings = 1;
	wchar_t *text = L"HELLO";
	char *textA = "HELLO";
	int *dx;
	RECT rect = {0, };

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif


	ptxt.x = 50;
	ptxt.y = 150;
	ptxt.n = wcslen(text);
	ptxt.lpstr = text;
	ptxt.uiFlags = ETO_OPAQUE;

	ptxt.rcl = rect;

	dx = (int *)malloc(sizeof(int)*wcslen(text));
	for(int i=0; i<wcslen(text); i++){
		dx[i] = 50; //글자간격을  설정
	}
	ptxt.pdx = dx;

	pt.x = ptxt.x;
	pt.y = ptxt.y;

	ShowWindow( hWndPaint, SW_SHOW );
	SetWindowPos(hWndPaint, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
	HDC hdc = GetDC(hWndPaint);

	result = PolyTextOutW(hdc, &ptxt, cStrings);
	
	if(result){

		SetPaintMessage(sizeof(pt)/sizeof(POINT), &pt, "검정(자간 50)", textA, msg);
		strcpy(buf, "PolyTextOutW 성공");
		
	}else{
		sprintf(msg, "PolyTextOutW 실패");
		strcpy(buf, "PolyTextOutW 실패");

		result = FALSE;
		
	}

	isManual = TRUE;
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "PolyTextOutW 성공", msg);
	isManual = FALSE;

	

	ShowWindow( hWndPaint, SW_HIDE );
	ReleaseDC(hWndPaint, hdc);

	return result;
}

/**
* BOOL Polygon(
  _In_       HDC   hdc,
  _In_ const POINT *lpPoints,
  _In_       int   nCount
);
* 선에 의해 연결된 둘 개 이상의 정점으로 이루어지는 다각형을 그린다.
폴리곤은 현재 펜을 사용하여 윤곽선이 그려지고 현재 브러시 및 다각형 채우기 모드를 사용하여 채워진다.
* @author : 손찬영  
*
* @param  hdc 디바이스 컨텍스트 핸들
* @param  lpPoints 논리적 좌표로 폴리곤의 정점을 지정하는 POINT 구조체 의 배열을 가리키는 포인터
* @param  nCount 배열의 정점 수
* @return 성공/실패 여부
*/
BOOL test_Polygon()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	POINT pt[4] = {{75, 75}, {75, 125}, {125, 125}, {125, 75}};
	int   nCount = 4; //point 갯수


#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif

	ShowWindow( hWndPaint, SW_SHOW );
	SetWindowPos(hWndPaint, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
	HDC hdc = GetDC(hWndPaint);

	result = Polygon(hdc, pt, nCount);

	if(result){
		SetPaintMessage(sizeof(pt)/sizeof(POINT), &pt[0], "검정", "빈 사각형", msg);
		strcpy(buf, "Polygon 성공");
		
	}else{
		sprintf(msg, "Polygon 실패");
		strcpy(buf, "Polygon 실패");

		result = FALSE;		
	}

	isManual = TRUE;
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "Polygon 성공", msg);
	isManual = FALSE;
	

	
	ShowWindow( hWndPaint, SW_HIDE );
	ReleaseDC(hWndPaint, hdc);
	DeleteDC(hdc);

	return result;
}


/**
* BOOL PolylineTo(
  _In_       HDC   hdc,
  _In_ const POINT *lppt,
  _In_       DWORD cCount
);
* 하나 이상의 직선을 그린다.
* @author : 손찬영  
*
* @param  hdc 디바이스 컨텍스트 핸들
* @param  lppt 행의 정점을 논리적 단위로 포함하는 POINT 구조체 의 배열을 가리키는 포인터
* @param  cCount 배열의 포인트 수
* @return 성공/실패 여부
*/
BOOL test_PolylineTo()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	POINT pt[3] = {{50, 100}, {100, 150}, {150, 100}};
	int   nCount = 3; //point 갯수


#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif

	ShowWindow( hWndPaint, SW_SHOW );
	SetWindowPos(hWndPaint, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
	HDC hdc = GetDC(hWndPaint);

	MoveToEx(hdc, pt[0].x, pt[0].y, NULL);
	result = PolylineTo(hdc, pt, nCount);

	if(result){
		SetPaintMessage(sizeof(pt)/sizeof(POINT), &pt[0], "검정", "대각선", msg);
		strcpy(buf, "PolylineTo 성공");
		
	}else{
		sprintf(msg, "PolylineTo 실패");
		strcpy(buf, "PolylineTo 실패");

		result = FALSE;		
	}

	isManual = TRUE;
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "PolylineTo 성공", msg);
	isManual = FALSE;
	

	
	ShowWindow( hWndPaint, SW_HIDE );
	ReleaseDC(hWndPaint, hdc);
	DeleteDC(hdc);

	return result;
}