#include "TestConsole.h"
#include <strsafe.h>


/**
 �ڿ��� ���� �Ҵ�� ����� �̰� 
 ���� ���� : ��ü���� Ʋ�� ����, �Ϻ� ���� ����. ���� �� ����� �������� �ʰ� �ּ� ó��.
 */


/*
	* DWORD WINAPI GetConsoleAlias(
  _In_  LPTSTR lpSource,
  _Out_ LPTSTR lpTargetBuffer,
  _In_  DWORD  TargetBufferLength,
  _In_  LPTSTR lpExeName
);
	* ������ �ܼ� ��Ī �� ���� ���Ͽ� ���� �ؽ�Ʈ�� �˻�
	* @author �ճ���
	*
	* @param lpSource �ܼ� ��Ī
	* @param lpTargetBuffer ���� ������
	* @param TargetBufferLength ���� �������� ������
	* @param lpExeName ���� ���ϸ�
	* return �ܼ� ��Ī �� ���� ������ �ؽ�Ʈ �˻簡 ���� ����. ������ ��� 0�� �ƴ� ���� ��ȯ.
*/
BOOL test_GetConsoleAliasA(){

	#ifdef OQADBGPRINT
	printf("test_GetConsoleAliasW \n");
	#endif

	BOOL value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	LPSTR Source = "tmax";
	LPSTR Target ="tmax_target";
	LPSTR ExeName = "cmd.exe";

	//add�� �ݵ�� ����� ��.
	AddConsoleAliasA(Source, Target, ExeName);
	
	// source, target, exename �� �� �� �ʿ� x. ���� �۾��ϸ� ������� ��.

	LPSTR lpSource = "tmax";
	LPSTR lpTargetBuffer = (LPSTR)malloc(sizeof(LPTSTR)* 256);
	LPSTR lpExeName = "cmd.exe";
	DWORD  TargetBufferLength = 256;

	DWORD result = 0;
	result = GetConsoleAliasA(lpSource, lpTargetBuffer, TargetBufferLength, lpExeName);

	if(result != 0){

		sprintf(msg, " GetConsoleAliasA() : SUCCESS");
		strcpy(buf, "SUCCESS");
		value = TRUE;

	}else{
		strcpy(msg, GetErrorMessage(" GetConsoleAliasA() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetConsoleAliasA", buf, "SUCCESS", msg);

	return value;

}

/*
	* DWORD WINAPI GetConsoleAliases(
  _Out_ LPTSTR lpAliasBuffer,
  _In_  DWORD  AliasBufferLength,
  _In_  LPTSTR lpExeName
);
	* ������ ���� ���Ͽ� ���� ���ǵ� ��� �ܼ� ��Ī�� �˻�
	* @author �ճ���
	*
	* @param  lpTargetBuffer ��Ī�� ���� ���� ������
	* @param  TargetBufferLength ���� ������ ������
	* @param  lpExeName ���� ���ϸ�
	* return ���� �� 0�� �ƴ� ���� ��ȯ
*/
BOOL test_GetConsoleAliasesA(){

	#ifdef OQADBGPRINT
	printf("test_GetConsoleAliasesA \n");
	#endif

	BOOL value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	LPSTR Source = "tmax";
	LPSTR Target = "tmax_target";
	LPSTR ExeName = "cmd.exe";

	//add�� �ݵ�� ����� ��.
	AddConsoleAliasA(Source, Target, ExeName);

	LPSTR lpTargetBuffer = (LPSTR)malloc(sizeof(LPTSTR)* 256);
	DWORD  TargetBufferLength = 256;
	LPSTR lpExeName = "cmd.exe";

	DWORD result = 0;
	result = GetConsoleAliasesA(lpTargetBuffer, TargetBufferLength, lpExeName);
	//sprintf(msg, "%d.", result);

	if(result != 0){

		sprintf(msg, " GetConsoleAliasesA() : SUCCESS");
		strcpy(buf, "SUCCESS");
		value = TRUE;

	}else{
		strcpy(msg, GetErrorMessage(" GetConsoleAliasesA() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetConsoleAliasesA", buf, "SUCCESS", msg);

	return value;
}

/*
	* DWORD WINAPI GetConsoleAliasesLength(
  _In_ LPTSTR lpExeName
);
	* ���ۿ� �ʿ��� ����� ��ȯ�Ѵ�.
	* @author �ճ���
	*
	* @param  ExeName ���� ���ϸ�
	* return ���� ���Ͽ� ���� ���ǵ� ��� �ܼ� ��Ī�� �����ϴµ� �ʿ��� ���� ����� ��ȯ�Ѵ�.
*/
BOOL test_GetConsoleAliasesLengthA(){

	#ifdef OQADBGPRINT
	printf("test_GetConsoleAliasesA \n");
	#endif
	
	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	DWORD result = 0;
	BOOL value = FALSE;

	LPSTR Source = "tmax";
	LPSTR Target = "tmax_target";
	LPSTR ExeName = "cmd.exe";

	AddConsoleAliasA(Source, Target, ExeName);
	result = GetConsoleAliasesLengthA(ExeName);

	if(result != 0){

		sprintf(msg, " GetConsoleAliasesLengthA() : SUCCESS \n\n result �� : %lu", result);
		strcpy(buf, "SUCCESS");
		value = TRUE;

	}else{
		strcpy(msg, GetErrorMessage(" GetConsoleAliasesLengthA() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetConsoleAliasesLengthA", buf, "SUCCESS", msg);

	return value;
}

/*
	* DWORD WINAPI GetConsoleAliasesLength(
  _In_ LPTSTR lpExeName
);
	* GetConsoleAliases �Լ����� ����ϴ� ���ۿ� �ʿ��� ����� �˻�
	* @author �ճ���
	*
	* @param  ExeName �ܼ� ��Ī�� �˻��� ���� ������ �̸�
	* return ���� ���Ͽ� ���� ���ǵ� ��� �ܼ� ��Ī�� �����ϴµ� �ʿ��� ���� ����� ��ȯ.
*/

BOOL test_GetConsoleAliasesLengthW(){

	#ifdef OQADBGPRINT
	printf("GetConsoleAliasesLengthW \n");
	#endif
	
	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	DWORD result = 0;
	BOOL value = FALSE;

	LPWSTR Source = L"tmax";
	LPWSTR Target = L"tmax_target";
	LPWSTR ExeName = L"cmd.exe";

	AddConsoleAliasW(Source, Target, ExeName);
	result = GetConsoleAliasesLengthW(ExeName);

	if(result != 0){

		sprintf(msg, " GetConsoleAliasesLengthW() : SUCCESS \n\n result �� : %lu", result);
		strcpy(buf, "SUCCESS");
		value = TRUE;

	}else{
		strcpy(msg, GetErrorMessage(" GetConsoleAliasesLengthW() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetConsoleAliasesLengthW", buf, "SUCCESS", msg);

	return value;

}


/*
	* DWORD WINAPI GetConsoleAliases(
  _Out_ LPTSTR lpAliasBuffer,
  _In_  DWORD  AliasBufferLength,


  _In_  LPTSTR lpExeName
);
	* ������ ���� ���Ͽ� ���� ���ǵ� ��� �ܼ� ��Ī�� �˻�
	* @author �ճ���
	*
	* @param  lpTargetBuffer ��Ī�� ���� ���� ������
	* @param  TargetBufferLength ���� ������ ������
	* @param  lpExeName ���� ���ϸ�
	* return ���� �� 0�� �ƴ� ���� ��ȯ
*/
BOOL test_GetConsoleAliasesW(){

	#ifdef OQADBGPRINT
	printf("test_GetConsoleAliasesW \n");
	#endif

	BOOL value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	LPTSTR Source = L"tmax";
	LPTSTR Target = L"tmax_target";
	LPTSTR ExeName = L"cmd.exe";

	//add�� �ݵ�� ����� ��.
	AddConsoleAliasW(Source, Target, ExeName);

	LPTSTR lpTargetBuffer = (LPTSTR)malloc(sizeof(LPTSTR)* 256);
	DWORD  TargetBufferLength = 256;
	LPTSTR lpExeName = L"cmd.exe";

	DWORD result = 0;
	result = GetConsoleAliasesW(lpTargetBuffer, TargetBufferLength, lpExeName);
	//sprintf(msg, "%d.", result);

	if(result != 0){

		sprintf(msg, " GetConsoleAliasesW() : SUCCESS");
		strcpy(buf, "SUCCESS");
		value = TRUE;

	}else{
		strcpy(msg, GetErrorMessage(" GetConsoleAliasesW() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetConsoleAliasesW", buf, "SUCCESS", msg);

	return value;
}


/*
	* DWORD WINAPI GetConsoleAliasExes(
  _Out_ LPTSTR lpExeNameBuffer,
  _In_  DWORD  ExeNameBufferLength
);
	* �ܼ� ��Ī�� ���ǵ� ��� ���� ���ϸ��� �˻�
	* @author �ճ���
	*
	* @param lpTargetBuffer ���� ���ϸ��� ���� ���� ������
	* @param TargetBufferLength ���� �������� ������
	* return ���� �� 0�� �ƴ� ���� ��ȯ�Ѵ�.
*/
BOOL test_GetConsoleAliasExesA(){

	#ifdef OQADBGPRINT
	printf("test_GetConsoleAliasW \n");
	#endif

	DWORD result = 0;
	BOOL value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	LPSTR Source = "tmax";
	LPSTR Target = "tmax_target";
	LPSTR ExeName = "cmd.exe";

	AddConsoleAliasA(Source, Target, ExeName);

	LPSTR lpTargetBuffer = (LPSTR)malloc(sizeof(LPTSTR)* 256);
	DWORD  TargetBufferLength = 256;

	result = GetConsoleAliasExesA(lpTargetBuffer, TargetBufferLength);
	//sprintf(msg, "%d.", result);

	if(result != 0){

		sprintf(msg, " GetConsoleAliasExesA() : SUCCESS");
		strcpy(buf, "SUCCESS");
		value = TRUE;

	}else{
		strcpy(msg, GetErrorMessage(" GetConsoleAliasExesA() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetConsoleAliasExesA", buf, "SUCCESS", msg);

	return value;

}

/*
	* DWORD WINAPI GetConsoleAliasExesLength(void);
	* GetConsoleAliasExes �Լ����� ����ϴ� ���ۿ� �ʿ��� ũ�⸦ �˻�
	* @author : �ճ���
	*
	* return �ܼ� ��Ī�� ���ǵ� ��� ���� ������ �̸��� �����ϴ� �� �ʿ��� ���� ����� ��ȯ
*/
BOOL test_GetConsoleAliasExesLengthA()
{
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	DWORD result = 0;
	BOOL value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	LPSTR Source = "tmax";
	LPSTR Target = "tmax_target";
	LPSTR ExeName = "cmd.exe";

	AddConsoleAliasA(Source, Target, ExeName);

	result = GetConsoleAliasExesLengthA();
	sprintf(buf, "result ���� %lu�Դϴ�.\n", result);

	if(result != 0){

		sprintf(msg, " GetConsoleAliasExesLengthA() : SUCCESS \n\n result �� : %lu", result);
		strcpy(buf, "SUCCESS");
		value = TRUE;

	}else{
		strcpy(msg, GetErrorMessage(" GetConsoleAliasExesLengthA() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetConsoleAliasExesLengthA", buf, "SUCCESS", msg);

	return value;
}

/*
	* DWORD WINAPI GetConsoleAliasExesLength(void);
	* GetConsoleAliasExes �Լ����� ����ϴ� ���ۿ� �ʿ��� ũ�⸦ �˻�
	* @author : �ճ���
	*
	* return �ܼ� ��Ī�� ���ǵ� ��� ���� ������ �̸��� �����ϴ� �� �ʿ��� ���� ����� ��ȯ
*/
BOOL test_GetConsoleAliasExesLengthW()
{
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	DWORD result = 0;
	BOOL value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	LPTSTR Source = L"tmax";
	LPTSTR Target = L"tmax_target";
	LPTSTR ExeName = L"cmd.exe";

	AddConsoleAliasW(Source, Target, ExeName);

	result = GetConsoleAliasExesLengthW();
	sprintf(buf, "result ���� %lu�Դϴ�.\n", result);

	if(result != 0){

		sprintf(msg, " GetConsoleAliasExesLengthW() : SUCCESS \n\n result �� : %lu", result);
		strcpy(buf, "SUCCESS");
		value = TRUE;

	}else{
		strcpy(msg, GetErrorMessage(" GetConsoleAliasExesLengthW() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetConsoleAliasExesLengthW", buf, "SUCCESS", msg);

	return value;
}

/*
	* DWORD WINAPI GetConsoleAliasExes(
  _Out_ LPTSTR lpExeNameBuffer,
  _In_  DWORD  ExeNameBufferLength
);
	* �ܼ� ��Ī�� ���ǵ� ��� ���� ���ϸ��� �˻�
	* @author �ճ���
	*
	* @param lpTargetBuffer ���� ���ϸ��� ���� ���� ������
	* @param TargetBufferLength ���� �������� ������
	* return ���� �� 0�� �ƴ� ���� ��ȯ�Ѵ�.
*/
BOOL test_GetConsoleAliasExesW(){

	#ifdef OQADBGPRINT
	printf("test_GetConsoleAliasW \n");
	#endif

	BOOL value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	LPTSTR Source = L"tmax";
	LPTSTR Target = L"tmax_target";
	LPTSTR ExeName = L"cmd.exe";

	AddConsoleAliasW(Source, Target, ExeName);

	LPTSTR lpTargetBuffer = (LPTSTR)malloc(sizeof(LPTSTR)* 256);
	DWORD  TargetBufferLength = 256;

	DWORD result = 0;

	result = GetConsoleAliasExesW(lpTargetBuffer, TargetBufferLength);
	//sprintf(msg, "%d.", result);

	if(result != 0){

		sprintf(msg, " GetConsoleAliasExesW() : SUCCESS");
		strcpy(buf, "SUCCESS");
		value = TRUE;

	}else{
		strcpy(msg, GetErrorMessage(" GetConsoleAliasExesW() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetConsoleAliasExesW", buf, "SUCCESS", msg);

	return value;

}


/*
	* DWORD WINAPI GetConsoleAlias(
  _In_  LPTSTR lpSource,
  _Out_ LPTSTR lpTargetBuffer,
  _In_  DWORD  TargetBufferLength,
  _In_  LPTSTR lpExeName
);
	* ������ �ܼ� ��Ī �� ���� ���Ͽ� ���� �ؽ�Ʈ�� �˻�
	* @author �ճ���
	*
	* @param lpSource �ܼ� ��Ī
	* @param lpTargetBuffer ���� ������
	* @param TargetBufferLength ���� �������� ������
	* @param lpExeName ���� ���ϸ�
	* return �ܼ� ��Ī �� ���� ������ �ؽ�Ʈ �˻簡 ���� ����. ������ ��� 0�� �ƴ� ���� ��ȯ.
*/
BOOL test_GetConsoleAliasW(){

	#ifdef OQADBGPRINT
	printf("test_GetConsoleAliasW \n");
	#endif

	BOOL value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	LPTSTR Source = L"tmax";
	LPTSTR Target = L"tmax_target";
	LPTSTR ExeName = L"cmd.exe";

	//add�� �ݵ�� ����� ��.
	AddConsoleAliasW(Source, Target, ExeName);
	
	// source, target, exename �� �� �� �ʿ� x. ���� �۾��ϸ� ������� ��.

	LPTSTR lpSource = L"tmax";
	LPTSTR lpTargetBuffer = (LPTSTR)malloc(sizeof(LPTSTR)* 256);
	DWORD  TargetBufferLength = 256;
	LPTSTR lpExeName = L"cmd.exe";

	DWORD result = 0;
	result = GetConsoleAliasW(lpSource, lpTargetBuffer, TargetBufferLength, lpExeName);

	if(result != 0){

		sprintf(msg, " GetConsoleAliasW() : SUCCESS");
		strcpy(buf, "SUCCESS");
		value = TRUE;

	}else{
		strcpy(msg, GetErrorMessage(" GetConsoleAliasW() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetConsoleAliasW", buf, "SUCCESS", msg);

	return value;

}
/*
	* COORD WINAPI GetConsoleFontSize(
  _In_ HANDLE hConsoleOutput,
  _In_ DWORD  nFont
);
	* ������ �ܼ� ȭ�� ���ۿ��� ����ϴ� �۲��� ũ�⸦ �˻�
	* @author : �ճ���
	*
	* @param hConsoleOutput �ܼ� ȭ�� ���ۿ� ���� �ڵ�. GENERIC_READ ������ �־�� ��.
	* @param nFont ũ�⸦ �˻��� �۲��� �ε���. �ε����� GetCurrentConsoleFont �Լ��� ȣ���Ͽ� ������.
	* @return ���� ������ �� ������ �ʺ�� ���̸� �����ϴ� coord ������ ��ȯ. ���� �� �ʺ�� ���̰� 0.
*/
BOOL test_GetConsoleFontSize(){

	#ifdef OQADBGPRINT
	printf("test_GetConsoleFontSize \n");
	#endif

	BOOL value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	CONSOLE_FONT_INFO GETFONT;
	SHORT Font_X = 0;
	SHORT Font_Y = 0;

	///printf("x�� %d y�� %d\n", Font_X, Font_Y);
	HANDLE StdHandle = GetStdHandle (STD_OUTPUT_HANDLE | GENERIC_READ);
	GetCurrentConsoleFont (StdHandle, FALSE, &GETFONT);
	COORD Fontsize = GetConsoleFontSize (StdHandle, GETFONT.nFont);

	Font_X = Fontsize.X;
	Font_Y = Fontsize.Y;

	///printf("x�� %d y�� %d\n", Font_X, Font_Y);
	sprintf(msg, "x�� %d y�� %d\n", Font_X, Font_Y);

	if(Font_X != 0 && Font_Y != 0){

		sprintf(msg, " GetConsoleFontSize() : SUCCESS \n\n Font Size : x = %d, y = %d\n", Font_X, Font_Y);
		strcpy(buf, "SUCCESS");
		value = TRUE;

	}else{
		strcpy(msg, GetErrorMessage(" GetConsoleFontSize() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetConsoleFontSize", buf, "SUCCESS", msg);

	return value;
}

/*
	* BOOL WINAPI GetConsoleHistoryInfo(
  _Out_ PCONSOLE_HISTORY_INFO lpConsoleHistoryInfo
);
	* ȣ�� ���μ����� �ֿܼ� ���� ��� ������ �˻��Ѵ�.
	* @author : �ճ���
	*
	* @param  lpConsoleHistoryInfo ȣ�� ���μ����� �ֿܼ� ���� ��� ������ �޴� CONSOLE_HISTORY_INFO ����ü�� ���� ������
	* return �����θ� ���� �˻� ����/���� ����. ���� �� 0�� �ƴ� ���� ��ȯ.
*/
BOOL test_GetConsoleHistoryInfo(){

	#ifdef OQADBGPRINT
	printf("test_GetConsoleHistoryInfo \n");
	#endif

	BOOL value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	DWORD result = 0;
	CONSOLE_HISTORY_INFO lpConsoleHistoryInfo;
	
	/*typedef struct {
		UINT  cbSize;
		UINT  HistoryBufferSize;
		UINT  NumberOfHistoryBuffers;
		DWORD dwFlags;
	} CONSOLE_HISTORY_INFO, *PCONSOLE_HISTORY_INFO;*/

	lpConsoleHistoryInfo.cbSize = sizeof(CONSOLE_HISTORY_INFO);
	lpConsoleHistoryInfo.HistoryBufferSize = 0;
	lpConsoleHistoryInfo.NumberOfHistoryBuffers = 0;
	lpConsoleHistoryInfo.dwFlags = 0;

	//SetConsoleHistoryInfo(&lpConsoleHistoryInfo);
	result = GetConsoleHistoryInfo(&lpConsoleHistoryInfo);

	if(result != 0){
	
		sprintf(msg, " GetConsoleHistoryInfo() : SUCCESS");
		strcpy(buf, "SUCCESS");
		value = TRUE;

	}else{
		strcpy(msg, GetErrorMessage(" GetConsoleHistoryInfo() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetConsoleHistoryInfo", buf, "SUCCESS", msg);
	return value;
}

/*
* DWORD WINAPI GetConsoleOriginalTitle(
  _Out_ LPTSTR lpConsoleTitle,
  _In_  DWORD  nSize
 );
* ���� �ܼ� â�� ���� ������ �˻�
* @author : �ճ���
*
* @param  lpConsoleTitle  ���� ������ �޾ƿ��� ���� ������
* return ���ۿ� ����� ���ڿ� ���̸� ��ȯ
*/
BOOL test_GetConsoleOriginalTitleA(){

	#ifdef OQADBGPRINT
	printf("test_GetConsoleOriginalTitleA \n");
	#endif

	BOOL value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	SetConsoleTitleA("New Title");
	TCHAR buffer[4096];
	DWORD OriginTitle = GetConsoleOriginalTitleA((LPSTR)buffer, 4096);

	if( OriginTitle != 0 ){
		sprintf(msg, " GetConsoleOriginalTitleA() : SUCCESS \n\n Console â�� OginalTitle : %s", buffer);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
		strcpy(buf, "SUCCESS");
		value = TRUE;

	//}else if(sizeof(buffer) <= sizeof(OriginTitle)){    : �Ʒ��� ���� �ǹ�
	}else if(OriginTitle == 0){ 

		//GetLastError�� ERROR_SUCCESS�� ��ȯ
		strcpy(msg, GetErrorMessage(" GetConsoleOriginalTitleA() : FAIL \n\n Error Message :", GetLastError()));

	}else{
		strcpy(msg, GetErrorMessage(" GetConsoleOriginalTitleA() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetConsoleOriginalTitleA", buf, "SUCCESS", msg);

	return value;
}

/*
* DWORD WINAPI GetConsoleOriginalTitle(
  _Out_ LPTSTR lpConsoleTitle,
  _In_  DWORD  nSize
 );
* ���� �ܼ� â�� ���� ������ �˻�
* @author : �ճ���
*
* @param  lpConsoleTitle  ���� ������ �޾ƿ��� ���� ������
* return ���ۿ� ����� ���ڿ� ���̸� ��ȯ
*/
BOOL test_GetConsoleOriginalTitleW(){
	
	#ifdef OQADBGPRINT
	printf("test_GetConsoleOriginalTitleW \n");
	#endif

	BOOL value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

    SetConsoleTitleW(L"New Title");
    WCHAR buffer[ 4096 ];
	DWORD OriginTitle = 0;
	OriginTitle = GetConsoleOriginalTitleW(buffer, 4096);
	//sprintf(msg, "Original Title�� %s\n", buffer);


	if( OriginTitle != 0 ){
		sprintf(msg, " GetConsoleOriginalTitleW() : SUCCESS \n\n Console â�� OginalTitle : %S", buffer);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
		strcpy(buf, "SUCCESS");
		value = TRUE;

	//}else if(sizeof(buffer) <= sizeof(OriginTitle)){    : �Ʒ��� ���� �ǹ�
	}else if(OriginTitle == 0){ 

		//GetLastError�� ERROR_SUCCESS�� ��ȯ
		strcpy(msg, GetErrorMessage(" GetConsoleOriginalTitleW() : FAIL \n\n Error Message :", GetLastError()));

	}else{
		strcpy(msg, GetErrorMessage(" GetConsoleOriginalTitleW() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetCurrentConsoleFontEx", buf, "SUCCESS", msg);

	return value;
}


/*
	* BOOL WINAPI GetConsoleScreenBufferInfoEx(
  _In_  HANDLE                        hConsoleOutput,
  _Out_ PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx
);
	* ������ �ܼ� ȭ�� ���ۿ� ���� Ȯ�� ������ �˻�
	* @author : �ճ���
	*
	* @param hcon : �ܼ� ��ũ�� ���� �ڵ�
	* @param  bi : CONSOLE_SCREEN_BUFFER_INFOEX ����
	* return: 0�� �ƴ� ���� ��ȯ
*/

BOOL test_GetConsoleScreenBufferInfoEx(){

	#ifdef OQADBGPRINT
	printf("test_GetConsoleScreenBufferInfoEx \n");
	#endif

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	BOOL result = 0;
	BOOL value = FALSE;

	CONSOLE_SCREEN_BUFFER_INFOEX bi;
	bi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);

	bi.ColorTable[8] = 0xff11ff; // violet
	///bi.ColorTable[15] = 0xffffff; // white
	bi.ColorTable[15] = 0xBDBDBD;

   // SetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &bi);  
	
    result = GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &bi);  
    //wprintf(L"Window: %u x %u\n", csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1);  

	if(result != 0){

		//bi.ColorTable[ 8] = 0xff11ff; // violet
		/////bi.ColorTable[15] = 0xffffff; // white
		//bi.ColorTable[15] = 0xBDBDBD;
		//SetConsoleScreenBufferInfoEx(hcon, &bi);
		//SetConsoleTextAttribute(hcon, 8);

		strcpy(msg, " GetConsoleScreenBufferInfoEx() : SUCCESS");
		strcpy(buf, "SUCCESS");
		value = TRUE;
	}
	else{
		strcpy(msg, GetErrorMessage(" GetConsoleScreenBufferInfoEx() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetConsoleScreenBufferInfoEx", buf, "SUCCESS", msg);

	return value;
}


/*
	* BOOL WINAPI GetConsoleSelectionInfo(
  _Out_ PCONSOLE_SELECTION_INFO lpConsoleSelectionInfo
);
	* ���� �ܼ� ���� �׸� ���� ������ �˻�
	* @author : �ճ���
	*
	* @param  lpConsoleSelectionInfo : CONSOLE_SELECTION_INFO ������ ���� ������
	* return ���� �˻� ���� ���� ����. ���� �� 0�� �ƴ� ���� ��ȯ.
*/
BOOL test_GetConsoleSelectionInfo(){

	#ifdef OQADBGPRINT
	printf("test_GetConsoleSelectionInfo \n");
	#endif

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";
	
	DWORD result = 0;
	BOOL value = FALSE;
	CONSOLE_SELECTION_INFO lpConsoleSelectionInfo;

	lpConsoleSelectionInfo.dwFlags = 0x0008;
	lpConsoleSelectionInfo.dwSelectionAnchor.X = 300;
	lpConsoleSelectionInfo.dwSelectionAnchor.Y = 400;
	lpConsoleSelectionInfo.srSelection.Top = 100;  
    lpConsoleSelectionInfo.srSelection.Left = 0; 
    lpConsoleSelectionInfo.srSelection.Bottom = 110;
    lpConsoleSelectionInfo.srSelection.Right = 790; 
	
	result = GetConsoleSelectionInfo(&lpConsoleSelectionInfo);

	if(result != 0){
		sprintf(msg, " GetConsoleSelectionInfo() : SUCCESS");
		strcpy(buf, "SUCCESS");
		value = TRUE;
		

	}else if(result == 0){
		strcpy(msg, GetErrorMessage(" GetConsoleSelectionInfo() : FAIL \n\n Error Message :", GetLastError()));

	}else{
		strcpy(msg, " GetConsoleSelectionInfo() : FAIL \n\n �׽�Ʈ �ڵ� ������ �ٽ� Ȯ���Ͻʽÿ�.");
	}

	wresult(__FILE__, __LINE__, "GetConsoleSelectionInfo", buf, "SUCCESS", msg);
	return value;

}




/**
	* DWORD WINAPI GetConsoleTitle(LPTSTR lpConsoleTitle,DWORD  nSize);
	* ���� �ܼ� â Ÿ��Ʋ �˻�
	* @author : �ճ���
	*
	* @param  lpConsoleTitle �ܼ�Ÿ��Ʋ ������
	* @param  nSize ���� ������
	* return �ܼ� â Ÿ��Ʋ ���� 
*/

BOOL test_GetConsoleTitleA(){

	#ifdef OQADBGPRINT
	printf("test_GetConsoleTitleA \n");
	#endif

	DWORD result = 0;
	BOOL value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	TCHAR *title = NULL;
	TCHAR lpConsoleTitle[MAX_PATH];

	
	//�ܼ� â ������ �����ϴ� �Լ� SetConsolTitle
	SetConsoleTitleA("GetConsoleTile_OS1");
	result = GetConsoleTitleA((LPSTR)lpConsoleTitle, MAX_PATH);


	// �����ڵ� �� ��Ƽ����Ʈ
	/*int iLen = WideCharToMultiByte(CP_ACP, 0, lpConsoleTitle, -1, title, 0, NULL, NULL);
	title = new char[iLen+1];
	WideCharToMultiByte(CP_ACP, 0, lpConsoleTitle, -1, title, iLen, NULL, NULL);*/

	if(result == 0){
		strcpy(msg, GetErrorMessage(" GetConsoleTitleA() : FAIL \n\n Error Message :", GetLastError()));

	}else{
		sprintf(msg, " GetConsoleTitleA() : SUCCESS \n\n �ܼ� Ÿ��Ʋ ���� : %d", result);
		strcpy(buf, "SUCCESS");
		value = TRUE;
	}

	wresult(__FILE__, __LINE__, "GetConsoleTitleA", buf, "SUCCESS", msg);
	return value;
}


/*
	* BOOL WINAPI GetCurrentConsoleFont(
  _In_  HANDLE             hConsoleOutput,
  _In_  BOOL               bMaximumWindow,
  _Out_ PCONSOLE_FONT_INFO lpConsoleCurrentFont
);
	* ���� �ܼ� �۲ÿ� ���� ������ �˻�
	* @author �ճ���
	*
	* @param  hOut �ܼ� ��ũ�� ���� �ڵ� 
	* @param  CFI CONSOLE_FONT_INFO ���� ������
	* return ���� �˻� ���� ����. ���� �� 0�� �ƴ� ���� ��ȯ.
	*/

BOOL test_GetCurrentConsoleFont(){

	#ifdef OQADBGPRINT
	printf("test_GetCurrentConsoleFont \n");
	#endif

	BOOL value = TRUE;

	BOOL result = 0;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	CONSOLE_FONT_INFO CFI;
	COORD FontSize;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CFI.nFont = 0;
	CFI.dwFontSize.X = 0;
	CFI.dwFontSize.Y = 0;
	FontSize.X = 0;
	FontSize.Y = 0;
	result = GetCurrentConsoleFont(hOut, false, &CFI);
	FontSize = GetConsoleFontSize(hOut,CFI.nFont);
	

	if(result == 0){
		strcpy(msg, GetErrorMessage(" GetCurrentConsoleFont() : FAIL \n\n Error Message :", GetLastError()));

	}else{
		sprintf(msg, " GetCurrentConsoleFont() : SUCCESS");
		strcpy(buf, "SUCCESS");
		value = TRUE;
	}

	wresult(__FILE__, __LINE__, "GetCurrentConsoleFont", buf, "SUCCESS", msg);
	return value;
}

/**
* BOOL WINAPI GetCurrentConsoleFontEx(
  _In_  HANDLE               hConsoleOutput,
  _In_  BOOL                 bMaximumWindow,
  _Out_ PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx
 );
* ���� �ܼ� �۲ÿ� ���� Ȯ�� ������ �˻�
* @author : �ճ���
*
* @param hConsoleOutput �ܼ� ��ũ�� ���� �ڵ�
* @param bMaximumWindow TRUE�� �۲� ������ �ִ� â ũ��� �˻��ǰ� FALSE �̸� ���� â ũ�⿡ ���� �۲� ������ �˻���
* @param lpConsoleCurrentFontEx CONSOLE_FONT_INFOEX ���� ������
* return ���� �� 0�� �ƴ� ���� ��ȯ
*/
BOOL test_GetCurrentConsoleFontEx(){

	#ifdef OQADBGPRINT
	printf("test_GetCurrentConsoleFontEx \n");
	#endif

	BOOL value = TRUE;
	BOOL result = 0;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_FONT_INFOEX orig = {0};
	CONSOLE_FONT_INFOEX current = {0};
	COORD FontSize = {16, 12};	

	orig.cbSize = sizeof(CONSOLE_FONT_INFOEX);

	/*
	current.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	FontSize.X = 10;
	FontSize.Y = 10;
	current.nFont = 11; 
	current.dwFontSize = FontSize;
	current.FontWeight = FW_NORMAL; 
	current.FontFamily = FF_DONTCARE; 
	SetCurrentConsoleFontEx(hStdout,FALSE,&current);
	*/

	// RRRRRRRRRRRRRRRRRR : 0���� �����ϰ� GET?

	result = GetCurrentConsoleFontEx(hStdout,FALSE,&orig);

	if (result != 0){

		sprintf(msg, " GetCurrentConsoleFontEx() : SUCCESS \n\n");
		strcpy(buf, "SUCCESS");
		value = TRUE;

	}else{
		strcpy(msg, GetErrorMessage(" GetCurrentConsoleFontEx() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetCurrentConsoleFontEx", buf, "SUCCESS", msg);

	//���� ��Ʈ�� ���ư�
	//SetCurrentConsoleFontEx(hStdout, FALSE, &orig);

	return value;
}

/**
* COORD WINAPI GetLargestConsoleWindowSize(
  _In_ HANDLE hConsoleOutput
  );
* ���� �۲� �� ���÷��� ũ�⿡ ���� ���� ū �ܼ� â ũ�⸦ �˻��Ѵ�.
* @author : �ճ���
*
* @param  hConsoleOutput �ܼ� ��ũ�� ���� �ڵ�
* return �ִ� ���� �ܼ� â�� �¿� ��
*/
BOOL test_GetLargestConsoleWindowSize(){

	#ifdef OQADBGPRINT
	printf("test_GetLargestConsoleWindowSize \n");
	#endif

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	//SMALL_RECT rect;
	BOOL value = FALSE;
	HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	
	//�ܼ� Ÿ��Ʋ�� test�� ����
	//SetConsoleTitleA("test");

	//HWND hWnd = FindWindowA(NULL, "test");
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD NewSBSize = GetLargestConsoleWindowSize(hOut);
	/*SMALL_RECT DisplayArea = {0, 0, 0, 0};

	SetConsoleScreenBufferSize(hOut, NewSBSize);
	DisplayArea.Right = NewSBSize.X - 1;
	DisplayArea.Bottom = NewSBSize.Y - 1;

	SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);
	ShowWindow(hWnd, SW_MAXIMIZE);*/

	if(NewSBSize.X != 0 && NewSBSize.Y != 0){ 
		 
		sprintf(msg, " GetLargestConsoleWindowSize() : SUCCESS \n\n X : %d \n Y : %d", NewSBSize.X, NewSBSize.Y);
		strcpy(buf, "SUCCESS");
		value = TRUE;

	}else{
		strcpy(msg, GetErrorMessage(" GetLargestConsoleWindowSize() : FAIL \n\n Error Message :", GetLastError()));
	} 

	wresult(__FILE__, __LINE__, "SetConsoleScreenBufferInfoEx", buf, "SUCCESS", msg);

	/*rect.Left = 0;                   
	rect.Right = 80 - 1;        
	rect.Top = 0;
	rect.Bottom = 25 - 1;  

	SetConsoleWindowInfo( hStdOut, TRUE, &rect );*/

	return value;
}


/**
* BOOL WINAPI GetNumberOfConsoleMouseButtons(
  _Out_ LPDWORD lpNumberOfMouseButtons
  );
* ���� �ֿܼ��� ����ϴ� ���콺 ��ư ���� �˻�
* @author : �ճ���
*
* @param  lpNumberOfMouseButtons ���콺 ��ư ���� �ޱ� ���� ���� ������
* return ���� �� 0�� �ƴ� ���� ��ȯ
*/

BOOL test_GetNumberOfConsoleMouseButtons(){

	#ifdef OQADBGPRINT
	printf("test_GetNumberOfConsoleMouseButtons \n");
	#endif

	BOOL value = FALSE;

	DWORD result = 0;
	DWORD dwNumber = 2;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	result = GetNumberOfConsoleMouseButtons(&dwNumber);
	sprintf(buf, "%d", dwNumber);

	if(result != 0){
		strcpy(msg, " GetNumberOfConsoleMouseButtons() : SUCCESS");
		strcpy(buf, "SUCCESS");
		value = TRUE;

	}else{
		strcpy(msg, GetErrorMessage(" GetNumberOfConsoleMouseButtons() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetNumberOfConsoleMouseButtons", buf, "SUCCESS", msg);

	return value;
}



/**
* BOOL WINAPI SetConsoleHistoryInfo(_In_ PCONSOLE_HISTORY_INFO lpConsoleHistoryInfo);
* ȣ�� ���μ����� �ֿܼ� ���� ��� ������ ����
* @author : �ճ���
*
* @param lpConsoleHistoryInfo CONSOLE_HISTORY_INFO ����ü ������
* return ������ ��� 0�� �ƴ� ���� ��ȯ
*/

BOOL test_SetConsoleHistoryInfo(){

	#ifdef OQADBGPRINT
	printf("test_SetConsoleHistoryInfo \n");
	#endif

	DWORD result = 0;
	BOOL value = FALSE;

	CONSOLE_HISTORY_INFO chi;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	chi.cbSize = sizeof(CONSOLE_HISTORY_INFO);
	chi.HistoryBufferSize = 0;
	chi.NumberOfHistoryBuffers = 0;
	chi.dwFlags = 0;

	result = SetConsoleHistoryInfo(&chi);

	if(result != 0){
		strcpy(msg, " SetConsoleHistoryInfo() : SUCCESS");
		strcpy(buf, "SUCCESS");
		value = TRUE;
	}

	else{
		strcpy(msg, GetErrorMessage(" SetConsoleHistoryInfo() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "SetConsoleHistoryInfo", buf, "SUCCESS", msg);

	return value;
}


/**
	* BOOL WINAPI SetConsoleScreenBufferInfoEx(
	  _In_ HANDLE                        hConsoleOutput,
	  _In_ PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx
	  );
	* ������ �ܼ� ȭ�� ���ۿ� ���� Ȯ�� ������ ����
	* @author : �ճ���
	*
	* @param  hConsoleOutput �ܼ� ��ũ�� ���� �ڵ�
	* @param  lpConsoleScreenBufferInfoEx CONSOLE_SCREEN_BUFFER_INFOEX ����
	* return ������ ��� 0�� �ƴ� ���� ��ȯ
*/

BOOL test_SetConsoleScreenBufferInfoEx(){

	#ifdef OQADBGPRINT
	printf("test_SetConsoleScreenBufferInfoEx \n");
	#endif

	BOOL result = 0;
	BOOL value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	/*CONSOLE_SCREEN_BUFFER_INFOEX bi;
	bi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	char msg[128] = "GetConsoleScreenBufferInfoEx�� ����Ǿ����ϴ�.";
	char msg2[128] = "GetConsoleScreenBufferInfoEx�� �����Ͽ����ϴ�.";
	*/

	CONSOLE_SCREEN_BUFFER_INFOEX csbi;  
    csbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);  

	//get���� ���;���
    GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);  
    //wprintf(L"Window: %u x %u\n", csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1);  

    result = SetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);  
	
	if(result != 0){

		//bi.ColorTable[ 8] = 0xff11ff; // violet
		/////bi.ColorTable[15] = 0xffffff; // white
		//bi.ColorTable[15] = 0xBDBDBD;
		//SetConsoleScreenBufferInfoEx(hcon, &bi);
		//SetConsoleTextAttribute(hcon, 8);

		strcpy(msg, " SetConsoleScreenBufferInfoEx() : SUCCESS");
		strcpy(buf, "SUCCESS");
		value = TRUE;
	}
	else{
		strcpy(msg, GetErrorMessage(" SetConsoleScreenBufferInfoEx() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "SetConsoleScreenBufferInfoEx", buf, "SUCCESS", msg);

	/*bi.ColorTable[15] = 0xffffff;
	SetConsoleScreenBufferInfoEx(hcon, &bi);*/

	return value;
}

/**
	* BOOL WINAPI SetCurrentConsoleFontEx(
  _In_ HANDLE               hConsoleOutput,
  _In_ BOOL                 bMaximumWindow,
  _In_ PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx
);
	* ���� �ܼ� �۲ÿ� ���� Ȯ�� ������ ����
	* @author �ճ���
	*
	* @param hConsoleOutput �ܼ� ��ũ�� ���� �ڵ�
	* @param bMaximumWindow TRUE�̸� �۲� ������ �ִ� â ũ��� ������. FASLE�̸� ���� â ũ�⿡ ���� �۲� ������ ������.
	* @param lpConsoleCurrentFontEx CONSOLE_FONT_INFOEX ���� ������
	* return ������ ��� 0�� �ƴ� ���� ��ȯ
*/

BOOL test_SetCurrentConsoleFontEx(){

	#ifdef OQADBGPRINT
	printf("test_SetCurrentConsoleFontEx \n");
	#endif

	BOOL result = 0;
	BOOL value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";


	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX cfi1, cfi2;
    cfi1.cbSize = sizeof(cfi1);
    cfi2.cbSize = sizeof(cfi2);

	GetCurrentConsoleFontEx(out, false, &cfi1);
	result = SetCurrentConsoleFontEx(out, false, &cfi1);

	//HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
	//HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//CONSOLE_FONT_INFOEX orig;

	////printf("�⺻ ������ : %d \n ", orig.dwFontSize.X);
	//CONSOLE_FONT_INFO CFI;
	//COORD FontSize2;
	//HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	//result = GetCurrentConsoleFont(hOut, false, &CFI);
	//FontSize2 = GetConsoleFontSize(hOut,CFI.nFont);

	//printf("\n\n\n ������ : %d \n\n\n", FontSize2);

	//CONSOLE_FONT_INFOEX current = {0}; 
	//COORD FontSize = {13,13};	
	//orig.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	//current.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	//FontSize.X = 13;
	//FontSize.Y = 13;

	//printf("��Ʈ������x : %d ��Ʈ ������ y : %d", FontSize.X, FontSize.Y);
	//
	//current.nFont = 11; 
	//current.dwFontSize = FontSize;
	//current.FontWeight = FW_NORMAL;
	//current.FontFamily = FF_DONTCARE;


	//result = SetCurrentConsoleFontEx(hStdout, FALSE, &current);

	if(result != 0){
		strcpy(msg, " SetCurrentConsoleFontEx() : SUCCESS");
		strcpy(buf, "SUCCESS");
		value = TRUE;
	
	}else{
		strcpy(msg, GetErrorMessage(" SetCurrentConsoleFontEx() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "SetCurrentConsoleFontEx", buf, "SUCCESS", msg);
	
	Sleep(1000);
	GetCurrentConsoleFontEx(out, false, &cfi2);
	SetCurrentConsoleFontEx(out, false, &cfi2);

	//������� �ǵ�����
	//SetCurrentConsoleFontEx(hStdout,FALSE,&orig);
	
	return value;
}