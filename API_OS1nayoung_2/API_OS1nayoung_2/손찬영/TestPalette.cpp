#include "TestPalette.h"

////����浹
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
//		sprintf(msg, "EngCreatePalette ����");
//		strcpy(buf, "EngCreatePalette ����");
//
//		result = FALSE;
//	}else{
//		sprintf(msg, "EngCreatePalette ���� : hPalette = %d", hPalette);
//		strcpy(buf, "EngCreatePalette ����");
//	}
//
//	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "EngCreatePalette ����", msg);*/
//
//
//
//	return result;
//}
//
////����浹
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
* ������ ���� ���� ���� ��ġ�ϴ� ������ �� ���� ǥ���� �׸��� ������ �˻��Ѵ�.
* @author : ������  
*
* @param  hpal		�� �ȷ�Ʈ�� �ڵ�
* @param  crColor	��ġ��ų ����. COLORREF ���� �� �� ������� RGB ��ũ�θ� ���
* @return			�����ϸ� ��ȯ ���� �� �ȷ�Ʈ�� �׸� �ε���, �����ϸ� CLR_INVALID
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

	//�ȷ�Ʈ ���� ���� Ȯ��
	/*if(!(GetDeviceCaps(GetDC(hWnd), RASTERCAPS) & RC_PALETTE)){
		strcpy(msg, __FUNCTION__);
		strcat(msg, " : Palette �������� ����");
		strcpy(buf, "Palette �������� ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetDeviceCaps ����", msg);

		return FALSE;
	}*/


	//lglp �ʱ�ȭ
	lgpl.palNumEntries = 128;
	lgpl.palPalEntry->peRed = 100;
	lgpl.palPalEntry->peGreen = 100;
	lgpl.palPalEntry->peBlue = 100;
	lgpl.palPalEntry->peFlags = 0;
	lgpl.palVersion = 0x300;

	hpal = CreatePalette(&lgpl);

	if(NULL == hpal){
		strcpy(msg, __FUNCTION__);
		strcat(msg, " : CreatePalette ����");
		strcpy(buf, "CreatePalette ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CreatePalette ����", msg);

		return FALSE;
	}
	holdpal = SelectPalette(hdc, hpal, FALSE);


	entries = GetNearestPaletteIndex(hpal, crColor);

	if(CLR_INVALID == entries){
		sprintf(msg, "GetNearestPaletteIndex ����");
		strcpy(buf, "GetNearestPaletteIndex ����");

		result = FALSE;

	}else{
		sprintf(msg, "GetNearestPaletteIndex ���� : hPalette = %d", hpal);
		strcpy(buf, "GetNearestPaletteIndex ����");
	}
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetNearestPaletteIndex ����", msg);


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
* ������ ��ġ ���ؽ�Ʈ (DC)�� ������ �ý��� �ȷ�Ʈ �ȷ�Ʈ ��Ʈ���� ������ �˻��Ѵ�.
* @author : ������  
*
* @param  hdc			����̽� ���ؽ�Ʈ �ڵ�
* @param  iStartIndex	�ý��� �ȷ�Ʈ���� �˻� �� ù ��° �׸�
* @param  nEntries		�ý��� �ȷ�Ʈ���� �˻� �� �׸� ��
* @param  lppe			�ȷ�Ʈ �׸��� ���� �� PALETTEENTRY ����ü �� �迭�� ����Ű�� ������
* @return				�����ϸ� ��ȯ ���� �� �ȷ�Ʈ���� �˻� �� �׸� ��, �����ϸ� 0
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

	//�ȷ�Ʈ ���� ���� Ȯ��
	/*if(!(GetDeviceCaps(GetDC(hWnd), RASTERCAPS) & RC_PALETTE)){
		strcpy(msg, __FUNCTION__);
		strcat(msg, " : �ȷ�Ʈ �������� ����");
		strcpy(buf, "�ȷ�Ʈ �������� ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetDeviceCaps ����", msg);

		return FALSE;
	}*/

	//lglp �ʱ�ȭ
	lgpl.palNumEntries = 128;
	lgpl.palPalEntry->peRed = 100;
	lgpl.palPalEntry->peGreen = 100;
	lgpl.palPalEntry->peBlue = 100;
	lgpl.palPalEntry->peFlags = 0;
	lgpl.palVersion = 0x300;

	hpal = CreatePalette(&lgpl);

	if(NULL == hpal){
		strcpy(msg, __FUNCTION__);
		strcat(msg, " : CreatePalette ����");
		strcpy(buf, "CreatePalette ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CreatePalette ����", msg);

		return FALSE;
	}

	holdpal = SelectPalette(hdc, hpal, FALSE);



	ret = GetSystemPaletteEntries(hdc, iStartIndex, nEntries, lgpl.palPalEntry);
	printf("ret = %d\n", ret);
	if(0 == ret){
		strcpy(msg, "GetSystemPaletteEntries ����");
		strcpy(buf, "GetSystemPaletteEntries ����");

		result = FALSE;

	}else{
		//sprintf(msg, "GetSystemPaletteEntries ���� : pe.peBlue = %d", (int)pe.peBlue);
		sprintf(msg, "GetSystemPaletteEntries ���� : entry = %d", ret);
		strcpy(buf, "GetSystemPaletteEntries ����");
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetSystemPaletteEntries ����", msg);

	//SelectPalette(hdc, holdpal, FALSE);
	DeleteObject(hpal);
	ReleaseDC(hWnd, hdc);

	return result;
}

/**
* UINT GetSystemPaletteUse(
  _In_ HDC hdc
);
* ������ ��ġ ���ؽ�Ʈ (DC)������ �ý��� (������) �ȷ�Ʈ�� ���� ���¸� �˻��Ѵ�.
* @author : ������  
*
* @param  hdc	����̽� ���ؽ�Ʈ �ڵ�(���� ǥ�� �����ϴ� ��ġ)
* @return		�����ϸ� ��ȯ ���� �ý��� �ȷ�Ʈ�� ���� ����
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

	//lglp �ʱ�ȭ
	lgpl.palNumEntries = 128;
	lgpl.palPalEntry->peRed = 100;
	lgpl.palPalEntry->peGreen = 100;
	lgpl.palPalEntry->peBlue = 100;
	lgpl.palPalEntry->peFlags = 0;
	lgpl.palVersion = 0x300;

	hpal = CreatePalette(&lgpl);

	if(NULL == hpal){
		strcpy(msg, __FUNCTION__);
		strcat(msg, " : CreatePalette ����");
		strcpy(buf, "CreatePalette ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CreatePalette ����", msg);

		return FALSE;
	}
	holdpal = SelectPalette(hdc, hpal, FALSE);

	ret = GetSystemPaletteUse(hdc);

	if(SYSPAL_ERROR == ret){
		sprintf(msg, "GetSystemPaletteUse ���� : ��ȿ���� �ʰų� �÷��ȷ�Ʈ �������� ����");
		strcpy(buf, "GetSystemPaletteUse ����");

		result = FALSE;

	}else if(SYSPAL_STATIC == ret || SYSPAL_NOSTATIC == ret){
		sprintf(msg, "GetSystemPaletteUse ����");
		strcpy(buf, "GetSystemPaletteUse ����");
	}else{
		sprintf(msg, "GetSystemPaletteUse ���� : �� �� ���� ����");
		strcpy(buf, "GetSystemPaletteUse ����");

		result = FALSE;
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetSystemPaletteUse ����", msg);

	SelectPalette(hdc, holdpal, FALSE);
	ReleaseDC(hWnd, hdc);
	return result;
}


/**
* UINT RealizePalette(
  _In_ HDC hdc
);
* �ý��� �ȷ�Ʈ�� ���� �� �ȷ�Ʈ���� �ȷ�Ʈ �׸��� �����Ѵ�.
* @author : ������  
*
* @param  hdc	�� �ȷ�Ʈ�� ���õ� ��ġ ���ؽ�Ʈ�� ���� �ڵ�
* @return		�����ϸ� ��ȯ ���� �ý��� �ȷ�Ʈ�� ���� �� �� �ȷ�Ʈ�� �׸� ��, ���� �� GDI_ERROR
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

	//�ȷ�Ʈ ���� ���� Ȯ��
	/*if(!(GetDeviceCaps(GetDC(hWnd), RASTERCAPS) & RC_PALETTE)){
		strcpy(msg, __FUNCTION__);
		strcat(msg, " : �ȷ�Ʈ �������� ����");
		strcpy(buf, "�ȷ�Ʈ �������� ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetDeviceCaps ����", msg);

		return FALSE;
	}*/

	//lglp �ʱ�ȭ
	lgpl.palNumEntries = 128;
	lgpl.palPalEntry->peRed = 100;
	lgpl.palPalEntry->peGreen = 100;
	lgpl.palPalEntry->peBlue = 100;
	lgpl.palPalEntry->peFlags = 0;
	lgpl.palVersion = 0x300;

	hpal = CreatePalette(&lgpl);

	if(NULL == hpal){
		strcpy(msg, __FUNCTION__);
		strcat(msg, " : CreatePalette ����");
		strcpy(buf, "CreatePalette ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CreatePalette ����", msg);

		return FALSE;
	}

	holdpal = SelectPalette(hdc, hpal, FALSE);

	ret = RealizePalette(hdc);	

	if(GDI_ERROR == ret){
		strcpy(msg, "RealizePalette ���� : GDI_ERROR");
		strcpy(buf, "RealizePalette ����");

		result = FALSE;

	}else if(0 <= ret){
		sprintf(msg, "RealizePalette ���� : nEntry = %d", ret);
		strcpy(buf, "RealizePalette ����");

	}else{
		sprintf(msg, "RealizePalette ���� : �� �� ���� ����(ret = %d)", ret);
		strcpy(buf, "RealizePalette ����");

		result = FALSE;
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "RealizePalette ����", msg);

	SelectPalette(hdc, holdpal, FALSE);
	ReleaseDC(hWnd, hdc);

	return result;
}


/**
* BOOL ResizePalette(
  _In_ HPALETTE hpal,
  _In_ UINT     nEntries
);
* ������ ���� �������� �� �ȷ�Ʈ�� ũ�⸦ �ø��ų� ���δ�.
* @author : ������  
*
* @param  hpal		���� �� �ȷ�Ʈ�� �ڵ�
* @param  nEntries	�ȷ�Ʈ�� ũ�⸦ ���� �� ���� �׸� ��. 1024�� ����
* @return			����/���� ����
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

	//lglp �ʱ�ȭ
	lgpl.palNumEntries = 128;
	lgpl.palPalEntry->peRed = 100;
	lgpl.palPalEntry->peGreen = 100;
	lgpl.palPalEntry->peBlue = 100;
	lgpl.palPalEntry->peFlags = 0;
	lgpl.palVersion = 0x300;

	hpal = CreatePalette(&lgpl);
	
	if(NULL == hpal){
		strcpy(msg, __FUNCTION__);
		strcat(msg, " : CreatePalette ����");
		strcpy(buf, "CreatePalette ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CreatePalette ����", msg);

		return FALSE;
	}

	printf("entries = %d\n", entries);

	result = ResizePalette(hpal, entries);
	if(result){
		sprintf(msg, "ResizePalette ����");
		strcpy(buf, "ResizePalette ����");

	}else{
		sprintf(msg, "ResizePalette ����");
		strcpy(buf, "ResizePalette ����");

		result = FALSE;
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "ResizePalette ����", msg);

	return result;
}