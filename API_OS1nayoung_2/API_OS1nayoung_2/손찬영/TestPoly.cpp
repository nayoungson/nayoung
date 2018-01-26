#include "TestPoly.h"

/**
* HRGN CreatePolyPolygonRgn(
  _In_ const POINT *lppt,
  _In_ const INT   *lpPolyCounts,
  _In_       int   nCount,
  _In_       int   fnPolyFillMode
);
* �ٰ����� �������� �̷���� ������ �����Ѵ�. �ٰ����� ��ĥ �� ����.
* @author : ������  
*
* @param  lppt ���� ������ �������� ������ �����ϴ� POINT ����ü �� �迭�� ����Ű�� ������
* @param  lpPolyCounts �� �迭�� lppt�� ����Ű�� �迭�� �ٰ��� �� �ϳ��� �� ���� �����ϴ� ���� �迭�� ���� ������
* @param  nCount lpPolyCounts�� ����Ű�� �迭�� �� ����
* @param  fnPolyFillMode �������ִ� �ȼ��� Ȯ���ϴ� �� ���Ǵ� ä��� ���
* @return �����ϸ� ��ȯ ���� ���� �ڵ�, �����ϸ� 0
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
	//������ �׷������� Ȯ���ϱ� ���� �ۼ�
	ShowWindow( hWndPaint, SW_SHOW );
	SetWindowPos(hWndPaint, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
	HDC hdc = GetDC(hWndPaint);
	InvertRgn(hdc, hRgn);

	if(NULL == hRgn){
		sprintf(msg, "CreatePolyPolygonRgn ����");
		strcpy(buf, "CreatePolyPolygonRgn ����");

		result = FALSE;
	}else{
		/*sprintf(msg, "CreatePolyPolygonRgn ����\n��ǥ : (%d, %d), (%d, %d), (%d, %d)\n��� : �ﰢ��\n���� : ����",
			pt[0].x, pt[0].y, pt[1].x, pt[1].y, pt[2].x, pt[2].y);*/
		SetPaintMessage(sizeof(pt)/sizeof(POINT), &pt[0], "����", "ä���� �ﰢ��", msg);
		strcpy(buf, "CreatePolyPolygonRgn ����");
	}

	isManual = TRUE;
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CreatePolyPolygonRgn ����", msg);
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
* �Լ� �ٰ��� ������ �����Ѵ�.
* @author : ������  
*
* @param  lppt ���� ������ �������� ������ �����ϴ� POINT ����ü �� �迭�� ����Ű�� ������
* @param  cPoints �迭�� ����Ʈ ��
* @param  fnPolyFillMode �������ִ� �ȼ��� Ȯ���ϴ� �� ���Ǵ� ä��� ���
* @return �����ϸ� ��ȯ ���� ���� �ڵ�, �����ϸ� NULL
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
		sprintf(msg, "CreatePolygonRgn ����");
		strcpy(buf, "CreatePolygonRgn ����");

		result = FALSE;
	}else{
		SetPaintMessage(sizeof(pt)/sizeof(POINT), &pt[0], "����", "ä���� �簢��", msg);
		strcpy(buf, "CreatePolygonRgn ����");
	}

	isManual = TRUE;
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CreatePolygonRgn ����", msg);
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
* ���� �ٰ����� �ø�� �׸���. �� �ٰ����� ���� ���� ����Ͽ� ������ �����ǰ� ���� �귯�� �� �ٰ��� ä��� ��带 ����Ͽ� ä������.
* @author : ������  
*
* @param  hdc ����̽� ���ؽ�Ʈ �ڵ�
* @param  lpPoints ���� ��ǥ�� �������� ������ �����ϴ� POINT ����ü �� �迭�� ����Ű�� ������
* @param  lpPolyCounts �� �ٰ����� �� ���� �����ϴ� ���� �迭�� ���� ������
* @param  nCount �� ������ ��
* @return ����/���� ����
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
		SetPaintMessage(sizeof(pt)/sizeof(POINT), &pt[0], "����", "�� �ﰢ��", msg);
		strcpy(buf, "PolyPolygon ����");
		
	}else{
		sprintf(msg, "PolyPolygon ����");
		strcpy(buf, "PolyPolygon ����");

		result = FALSE;
		
	}

	isManual = TRUE;
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "PolyPolygon ����", msg);
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
* ����� �Ϸ��� ���� �� ���׸�Ʈ�� �׸���.
* @author : ������  
*
* @param  hdc ����̽� ���ؽ�Ʈ �ڵ�
* @param  lppt �� ������ ���� ������ ������ �����ϴ� POINT ����ü �� �迭�� ����Ű�� ������
* @param  lpdwPolyPoints �ش� ���� ���� �� ���� lppt �迭 �� �� ���� �����ϴ� ���� �迭�� ���� ������
* @param  cCount lpdwPolyPoints �׸��� ��.
* @return ����/���� ����
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
		SetPaintMessage(sizeof(pt)/sizeof(POINT), &pt[0], "����", "�밢��", msg);
		strcpy(buf, "PolyPolyline ����");
		
	}else{
		sprintf(msg, "PolyPolyline ����");
		strcpy(buf, "PolyPolyline ����");

		result = FALSE;
		
	}
	isManual = TRUE;
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "PolyPolyline ����", msg);
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

* ���� ������ ����̽� ���ؽ�Ʈ���� ���õ� ��Ʈ �� �ؽ�Ʈ ������ ����Ͽ� ���� ���ڿ��� �׸���.
* @author : ������  
*
* @param  hdc ����̽� ���ؽ�Ʈ �ڵ�
* @param  pptxt ������ ���ڿ��� �����ϴ� POLYTEXT ����ü �� �迭�� ����Ű�� ������
* @param  cStrings POLYTEXT�� �� ����ü �迭�� ��
* @return ����/���� ����
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

	ptxt.rcl = rect; //�ؽ�Ʈ�� �簢�� ������ ����

	dx = (int *)malloc(sizeof(int)*strlen(text));
	for(int i=0; i<strlen(text); i++){
		dx[i] = 50; //���ڰ�����  ����
	}
	ptxt.pdx = dx;	

	pt.x = ptxt.x;
	pt.y = ptxt.y;

	ShowWindow( hWndPaint, SW_SHOW );
	SetWindowPos(hWndPaint, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
	HDC hdc = GetDC(hWndPaint);


	result = PolyTextOutA(hdc, &ptxt, cStrings);
	
	if(result){
		SetPaintMessage(sizeof(pt)/sizeof(POINT), &pt, "����(�ڰ� 50)", text, msg);
		strcpy(buf, "PolyTextOutA ����");
		
	}else{
		sprintf(msg, "PolyTextOutA ����");
		strcpy(buf, "PolyTextOutA ����");

		result = FALSE;
		
	}

	isManual = TRUE;
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "PolyTextOutA ����", msg);
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

* ���� ������ ����̽� ���ؽ�Ʈ���� ���õ� ��Ʈ �� �ؽ�Ʈ ������ ����Ͽ� ���� ���ڿ��� �׸���.
* @author : ������  
*
* @param  hdc ����̽� ���ؽ�Ʈ �ڵ�
* @param  pptxt ������ ���ڿ��� �����ϴ� POLYTEXT ����ü �� �迭�� ����Ű�� ������
* @param  cStrings POLYTEXT�� �� ����ü �迭�� ��
* @return ����/���� ����
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
		dx[i] = 50; //���ڰ�����  ����
	}
	ptxt.pdx = dx;

	pt.x = ptxt.x;
	pt.y = ptxt.y;

	ShowWindow( hWndPaint, SW_SHOW );
	SetWindowPos(hWndPaint, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
	HDC hdc = GetDC(hWndPaint);

	result = PolyTextOutW(hdc, &ptxt, cStrings);
	
	if(result){

		SetPaintMessage(sizeof(pt)/sizeof(POINT), &pt, "����(�ڰ� 50)", textA, msg);
		strcpy(buf, "PolyTextOutW ����");
		
	}else{
		sprintf(msg, "PolyTextOutW ����");
		strcpy(buf, "PolyTextOutW ����");

		result = FALSE;
		
	}

	isManual = TRUE;
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "PolyTextOutW ����", msg);
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
* ���� ���� ����� �� �� �̻��� �������� �̷������ �ٰ����� �׸���.
�������� ���� ���� ����Ͽ� �������� �׷����� ���� �귯�� �� �ٰ��� ä��� ��带 ����Ͽ� ä������.
* @author : ������  
*
* @param  hdc ����̽� ���ؽ�Ʈ �ڵ�
* @param  lpPoints ���� ��ǥ�� �������� ������ �����ϴ� POINT ����ü �� �迭�� ����Ű�� ������
* @param  nCount �迭�� ���� ��
* @return ����/���� ����
*/
BOOL test_Polygon()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	POINT pt[4] = {{75, 75}, {75, 125}, {125, 125}, {125, 75}};
	int   nCount = 4; //point ����


#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif

	ShowWindow( hWndPaint, SW_SHOW );
	SetWindowPos(hWndPaint, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
	HDC hdc = GetDC(hWndPaint);

	result = Polygon(hdc, pt, nCount);

	if(result){
		SetPaintMessage(sizeof(pt)/sizeof(POINT), &pt[0], "����", "�� �簢��", msg);
		strcpy(buf, "Polygon ����");
		
	}else{
		sprintf(msg, "Polygon ����");
		strcpy(buf, "Polygon ����");

		result = FALSE;		
	}

	isManual = TRUE;
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "Polygon ����", msg);
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
* �ϳ� �̻��� ������ �׸���.
* @author : ������  
*
* @param  hdc ����̽� ���ؽ�Ʈ �ڵ�
* @param  lppt ���� ������ ���� ������ �����ϴ� POINT ����ü �� �迭�� ����Ű�� ������
* @param  cCount �迭�� ����Ʈ ��
* @return ����/���� ����
*/
BOOL test_PolylineTo()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	POINT pt[3] = {{50, 100}, {100, 150}, {150, 100}};
	int   nCount = 3; //point ����


#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif

	ShowWindow( hWndPaint, SW_SHOW );
	SetWindowPos(hWndPaint, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
	HDC hdc = GetDC(hWndPaint);

	MoveToEx(hdc, pt[0].x, pt[0].y, NULL);
	result = PolylineTo(hdc, pt, nCount);

	if(result){
		SetPaintMessage(sizeof(pt)/sizeof(POINT), &pt[0], "����", "�밢��", msg);
		strcpy(buf, "PolylineTo ����");
		
	}else{
		sprintf(msg, "PolylineTo ����");
		strcpy(buf, "PolylineTo ����");

		result = FALSE;		
	}

	isManual = TRUE;
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "PolylineTo ����", msg);
	isManual = FALSE;
	

	
	ShowWindow( hWndPaint, SW_HIDE );
	ReleaseDC(hWndPaint, hdc);
	DeleteDC(hdc);

	return result;
}