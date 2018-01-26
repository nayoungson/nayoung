#include "TestPalette.h"

////헤더충돌
//BOOL test_EngCreatePalette()
//{
//	BOOL result = TRUE;	
//	char msg[BUFSIZ];
//	char buf[BUFSIZ];
//
//	HPALETTE hPalette = NULL;
//	ULONG iMode;
//	ULONG cColors;
//	ULONG *pulColors;
//	FLONG flRed;
//	FLONG flGreen;
//	FLONG flBlue;
//
//#ifdef OQADBGPRINT
//	puts(__FUNCTION__);
//#endif
//
//	/*hPalette = EngCreatePalette(iMode, cColors, pulColors, flRed, flGreen, flBlue);
//	
//	if(NULL == hPalette){
//		sprintf(msg, "EngCreatePalette 실패");
//		strcpy(buf, "EngCreatePalette 실패");
//
//		result = FALSE;
//	}else{
//		sprintf(msg, "EngCreatePalette 성공 : hPalette = %d", hPalette);
//		strcpy(buf, "EngCreatePalette 성공");
//	}
//
//	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "EngCreatePalette 성공", msg);*/
//
//
//
//	return result;
//}
//
////헤더충돌
//BOOL test_EngDeletePalette()
//{
//	BOOL result = TRUE;	
//	char msg[BUFSIZ];
//	char buf[BUFSIZ];
//
//#ifdef OQADBGPRINT
//	puts(__FUNCTION__);
//#endif
//
//	return result;
//}

/**
* UINT GetNearestPaletteIndex(
  _In_ HPALETTE hpal,
  _In_ COLORREF crColor
);
* 지정된 색상 값과 가장 일치하는 지정된 논리 색상 표에서 항목의 색인을 검색한다.
* @author : 손찬영  
*
* @param  hpal		논리 팔레트의 핸들
* @param  crColor	일치시킬 색상. COLORREF 색상 값 을 만들려면 RGB 매크로를 사용
* @return			성공하면 반환 값은 논리 팔레트의 항목 인덱스, 실패하면 CLR_INVALID
*/
BOOL test_GetNearestPaletteIndex()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HPALETTE hpal, holdpal;
	COLORREF crColor = RGB(100, 100, 100);
	UINT entries= 0;

	LOGPALETTE lgpl;
	HDC hdc = GetDC(hWnd);

#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif

	//팔레트 지원 여부 확인
	/*if(!(GetDeviceCaps(GetDC(hWnd), RASTERCAPS) & RC_PALETTE)){
		strcpy(msg, __FUNCTION__);
		strcat(msg, " : Palette 지원하지 않음");
		strcpy(buf, "Palette 지원하지 않음");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetDeviceCaps 실패", msg);

		return FALSE;
	}*/


	//lglp 초기화
	lgpl.palNumEntries = 128;
	lgpl.palPalEntry->peRed = 100;
	lgpl.palPalEntry->peGreen = 100;
	lgpl.palPalEntry->peBlue = 100;
	lgpl.palPalEntry->peFlags = 0;
	lgpl.palVersion = 0x300;

	hpal = CreatePalette(&lgpl);

	if(NULL == hpal){
		strcpy(msg, __FUNCTION__);
		strcat(msg, " : CreatePalette 실패");
		strcpy(buf, "CreatePalette 실패");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CreatePalette 성공", msg);

		return FALSE;
	}
	holdpal = SelectPalette(hdc, hpal, FALSE);


	entries = GetNearestPaletteIndex(hpal, crColor);

	if(CLR_INVALID == entries){
		sprintf(msg, "GetNearestPaletteIndex 실패");
		strcpy(buf, "GetNearestPaletteIndex 실패");

		result = FALSE;

	}else{
		sprintf(msg, "GetNearestPaletteIndex 성공 : hPalette = %d", hpal);
		strcpy(buf, "GetNearestPaletteIndex 성공");
	}
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetNearestPaletteIndex 성공", msg);


	ReleaseDC(hWnd, hdc);

	return result;
}


/**
* UINT GetSystemPaletteEntries (
  _In_ HDC hdc,
  _In_ UINT iStartIndex,
  _In_ UINT nEntries,
  _Out_ LPPALETTEENTRY lppe
);
* 지정된 장치 컨텍스트 (DC)과 연관된 시스템 팔레트 팔레트 엔트리의 범위를 검색한다.
* @author : 손찬영  
*
* @param  hdc			디바이스 컨텍스트 핸들
* @param  iStartIndex	시스템 팔레트에서 검색 할 첫 번째 항목
* @param  nEntries		시스템 팔레트에서 검색 할 항목 수
* @param  lppe			팔레트 항목을 수신 할 PALETTEENTRY 구조체 의 배열을 가리키는 포인터
* @return				성공하면 반환 값은 논리 팔레트에서 검색 한 항목 수, 실패하면 0
*/
BOOL test_GetSystemPaletteEntries()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HDC hdc = GetDC(hWnd);
	UINT iStartIndex = 0;
	UINT nEntries = 0;
	LPPALETTEENTRY pe = NULL;

	HPALETTE hpal, holdpal;
	LOGPALETTE lgpl;

	UINT ret = 0;

#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif

	//팔레트 지원 여부 확인
	/*if(!(GetDeviceCaps(GetDC(hWnd), RASTERCAPS) & RC_PALETTE)){
		strcpy(msg, __FUNCTION__);
		strcat(msg, " : 팔레트 지원하지 않음");
		strcpy(buf, "팔레트 지원하지 않음");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetDeviceCaps 실패", msg);

		return FALSE;
	}*/

	//lglp 초기화
	lgpl.palNumEntries = 128;
	lgpl.palPalEntry->peRed = 100;
	lgpl.palPalEntry->peGreen = 100;
	lgpl.palPalEntry->peBlue = 100;
	lgpl.palPalEntry->peFlags = 0;
	lgpl.palVersion = 0x300;

	hpal = CreatePalette(&lgpl);

	if(NULL == hpal){
		strcpy(msg, __FUNCTION__);
		strcat(msg, " : CreatePalette 실패");
		strcpy(buf, "CreatePalette 실패");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CreatePalette 성공", msg);

		return FALSE;
	}

	holdpal = SelectPalette(hdc, hpal, FALSE);



	ret = GetSystemPaletteEntries(hdc, iStartIndex, nEntries, lgpl.palPalEntry);
	printf("ret = %d\n", ret);
	if(0 == ret){
		strcpy(msg, "GetSystemPaletteEntries 실패");
		strcpy(buf, "GetSystemPaletteEntries 실패");

		result = FALSE;

	}else{
		//sprintf(msg, "GetSystemPaletteEntries 성공 : pe.peBlue = %d", (int)pe.peBlue);
		sprintf(msg, "GetSystemPaletteEntries 성공 : entry = %d", ret);
		strcpy(buf, "GetSystemPaletteEntries 성공");
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetSystemPaletteEntries 성공", msg);

	//SelectPalette(hdc, holdpal, FALSE);
	DeleteObject(hpal);
	ReleaseDC(hWnd, hdc);

	return result;
}

/**
* UINT GetSystemPaletteUse(
  _In_ HDC hdc
);
* 지정된 장치 컨텍스트 (DC)를위한 시스템 (물리적) 팔레트의 현재 상태를 검색한다.
* @author : 손찬영  
*
* @param  hdc	디바이스 컨텍스트 핸들(색상 표를 지원하는 장치)
* @return		성공하면 반환 값은 시스템 팔레트의 현재 상태
*/
BOOL test_GetSystemPaletteUse()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	UINT ret = 0;
	HDC hdc = GetDC(hWnd);

	HPALETTE hpal, holdpal;
	LOGPALETTE lgpl;


#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif

	//lglp 초기화
	lgpl.palNumEntries = 128;
	lgpl.palPalEntry->peRed = 100;
	lgpl.palPalEntry->peGreen = 100;
	lgpl.palPalEntry->peBlue = 100;
	lgpl.palPalEntry->peFlags = 0;
	lgpl.palVersion = 0x300;

	hpal = CreatePalette(&lgpl);

	if(NULL == hpal){
		strcpy(msg, __FUNCTION__);
		strcat(msg, " : CreatePalette 실패");
		strcpy(buf, "CreatePalette 실패");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CreatePalette 성공", msg);

		return FALSE;
	}
	holdpal = SelectPalette(hdc, hpal, FALSE);

	ret = GetSystemPaletteUse(hdc);

	if(SYSPAL_ERROR == ret){
		sprintf(msg, "GetSystemPaletteUse 실패 : 유효하지 않거나 컬러팔레트 지원하지 않음");
		strcpy(buf, "GetSystemPaletteUse 실패");

		result = FALSE;

	}else if(SYSPAL_STATIC == ret || SYSPAL_NOSTATIC == ret){
		sprintf(msg, "GetSystemPaletteUse 성공");
		strcpy(buf, "GetSystemPaletteUse 성공");
	}else{
		sprintf(msg, "GetSystemPaletteUse 실패 : 알 수 없는 에러");
		strcpy(buf, "GetSystemPaletteUse 실패");

		result = FALSE;
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetSystemPaletteUse 성공", msg);

	SelectPalette(hdc, holdpal, FALSE);
	ReleaseDC(hWnd, hdc);
	return result;
}


/**
* UINT RealizePalette(
  _In_ HDC hdc
);
* 시스템 팔레트에 현재 논리 팔레트에서 팔레트 항목을 매핑한다.
* @author : 손찬영  
*
* @param  hdc	논리 팔레트가 선택된 장치 컨텍스트에 대한 핸들
* @return		성공하면 반환 값은 시스템 팔레트에 매핑 된 논리 팔레트의 항목 수, 실패 시 GDI_ERROR
*/
BOOL test_RealizePalette()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	UINT ret = 0;
	HDC hdc = GetDC(hWnd);

	HPALETTE hpal, holdpal;
	LOGPALETTE lgpl;

#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif

	//팔레트 지원 여부 확인
	/*if(!(GetDeviceCaps(GetDC(hWnd), RASTERCAPS) & RC_PALETTE)){
		strcpy(msg, __FUNCTION__);
		strcat(msg, " : 팔레트 지원하지 않음");
		strcpy(buf, "팔레트 지원하지 않음");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetDeviceCaps 실패", msg);

		return FALSE;
	}*/

	//lglp 초기화
	lgpl.palNumEntries = 128;
	lgpl.palPalEntry->peRed = 100;
	lgpl.palPalEntry->peGreen = 100;
	lgpl.palPalEntry->peBlue = 100;
	lgpl.palPalEntry->peFlags = 0;
	lgpl.palVersion = 0x300;

	hpal = CreatePalette(&lgpl);

	if(NULL == hpal){
		strcpy(msg, __FUNCTION__);
		strcat(msg, " : CreatePalette 실패");
		strcpy(buf, "CreatePalette 실패");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CreatePalette 성공", msg);

		return FALSE;
	}

	holdpal = SelectPalette(hdc, hpal, FALSE);

	ret = RealizePalette(hdc);	

	if(GDI_ERROR == ret){
		strcpy(msg, "RealizePalette 실패 : GDI_ERROR");
		strcpy(buf, "RealizePalette 실패");

		result = FALSE;

	}else if(0 <= ret){
		sprintf(msg, "RealizePalette 성공 : nEntry = %d", ret);
		strcpy(buf, "RealizePalette 성공");

	}else{
		sprintf(msg, "RealizePalette 실패 : 알 수 없는 에러(ret = %d)", ret);
		strcpy(buf, "RealizePalette 실패");

		result = FALSE;
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "RealizePalette 성공", msg);

	SelectPalette(hdc, holdpal, FALSE);
	ReleaseDC(hWnd, hdc);

	return result;
}


/**
* BOOL ResizePalette(
  _In_ HPALETTE hpal,
  _In_ UINT     nEntries
);
* 지정된 값을 기준으로 논리 팔레트의 크기를 늘리거나 줄인다.
* @author : 손찬영  
*
* @param  hpal		변경 될 팔레트의 핸들
* @param  nEntries	팔레트의 크기를 조정 한 후의 항목 수. 1024로 제한
* @return			성공/실패 여부
*/
BOOL test_ResizePalette()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HPALETTE hpal;
	COLORREF crColor = RGB(100, 100, 100);
	UINT entries= 128;

	LOGPALETTE lgpl;

#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif

	//lglp 초기화
	lgpl.palNumEntries = 128;
	lgpl.palPalEntry->peRed = 100;
	lgpl.palPalEntry->peGreen = 100;
	lgpl.palPalEntry->peBlue = 100;
	lgpl.palPalEntry->peFlags = 0;
	lgpl.palVersion = 0x300;

	hpal = CreatePalette(&lgpl);
	
	if(NULL == hpal){
		strcpy(msg, __FUNCTION__);
		strcat(msg, " : CreatePalette 실패");
		strcpy(buf, "CreatePalette 실패");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CreatePalette 성공", msg);

		return FALSE;
	}

	printf("entries = %d\n", entries);

	result = ResizePalette(hpal, entries);
	if(result){
		sprintf(msg, "ResizePalette 성공");
		strcpy(buf, "ResizePalette 성공");

	}else{
		sprintf(msg, "ResizePalette 실패");
		strcpy(buf, "ResizePalette 실패");

		result = FALSE;
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "ResizePalette 성공", msg);

	return result;
}