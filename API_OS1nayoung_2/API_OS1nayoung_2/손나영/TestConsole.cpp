#include "TestConsole.h"
#include <strsafe.h>


/**
 박영수 전임 할당분 담당자 이관 
 수정 내용 : 전체적인 틀은 유지, 일부 내용 수정. 수정 전 내용들 삭제하지 않고 주석 처리.
 */


/*
	* DWORD WINAPI GetConsoleAlias(
  _In_  LPTSTR lpSource,
  _Out_ LPTSTR lpTargetBuffer,
  _In_  DWORD  TargetBufferLength,
  _In_  LPTSTR lpExeName
);
	* 지정된 콘솔 별칭 및 실행 파일에 대한 텍스트를 검색
	* @author 손나영
	*
	* @param lpSource 콘솔 별칭
	* @param lpTargetBuffer 버퍼 포인터
	* @param TargetBufferLength 버퍼 포인터의 사이즈
	* @param lpExeName 실행 파일명
	* return 콘솔 별칭 및 실행 파일의 텍스트 검사가 성공 여부. 성공일 경우 0이 아닌 값을 반환.
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

	//add를 반드시 해줘야 함.
	AddConsoleAliasA(Source, Target, ExeName);
	
	// source, target, exename 두 번 쓸 필요 x. 수정 작업하면 깔끔해질 듯.

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
	* 지정된 실행 파일에 대해 정의된 모든 콘솔 별칭을 검색
	* @author 손나영
	*
	* @param  lpTargetBuffer 별칭을 받을 버퍼 포인터
	* @param  TargetBufferLength 버퍼 포인터 사이즈
	* @param  lpExeName 실행 파일명
	* return 성공 시 0이 아닌 값을 반환
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

	//add를 반드시 해줘야 함.
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
	* 버퍼에 필요한 사이즈를 반환한다.
	* @author 손나영
	*
	* @param  ExeName 실행 파일명
	* return 실행 파일에 대해 정의돈 모든 콘솔 별칭을 저장하는데 필요한 버퍼 사이즈를 반환한다.
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

		sprintf(msg, " GetConsoleAliasesLengthA() : SUCCESS \n\n result 값 : %lu", result);
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
	* GetConsoleAliases 함수에서 사용하는 버퍼에 필요한 사이즈를 검색
	* @author 손나영
	*
	* @param  ExeName 콘솔 별칭을 검색할 실행 파일의 이름
	* return 실행 파일에 대해 정의돈 모든 콘솔 별칭을 저장하는데 필요한 버퍼 사이즈를 반환.
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

		sprintf(msg, " GetConsoleAliasesLengthW() : SUCCESS \n\n result 값 : %lu", result);
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
	* 지정된 실행 파일에 대해 정의된 모든 콘솔 별칭을 검색
	* @author 손나영
	*
	* @param  lpTargetBuffer 별칭을 받을 버퍼 포인터
	* @param  TargetBufferLength 버퍼 포인터 사이즈
	* @param  lpExeName 실행 파일명
	* return 성공 시 0이 아닌 값을 반환
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

	//add를 반드시 해줘야 함.
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
	* 콘솔 별칭이 정의된 모든 실행 파일명을 검색
	* @author 손나영
	*
	* @param lpTargetBuffer 실행 파일명을 받을 버퍼 포인터
	* @param TargetBufferLength 버퍼 포인터의 사이즈
	* return 성공 시 0이 아닌 값을 반환한다.
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
	* GetConsoleAliasExes 함수에서 사용하는 버퍼에 필요한 크기를 검색
	* @author : 손나영
	*
	* return 콘솔 별칭이 정의된 모든 실행 파일의 이름을 저장하는 데 필요한 버퍼 사이즈를 반환
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
	sprintf(buf, "result 값은 %lu입니다.\n", result);

	if(result != 0){

		sprintf(msg, " GetConsoleAliasExesLengthA() : SUCCESS \n\n result 값 : %lu", result);
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
	* GetConsoleAliasExes 함수에서 사용하는 버퍼에 필요한 크기를 검색
	* @author : 손나영
	*
	* return 콘솔 별칭이 정의된 모든 실행 파일의 이름을 저장하는 데 필요한 버퍼 사이즈를 반환
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
	sprintf(buf, "result 값은 %lu입니다.\n", result);

	if(result != 0){

		sprintf(msg, " GetConsoleAliasExesLengthW() : SUCCESS \n\n result 값 : %lu", result);
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
	* 콘솔 별칭이 정의된 모든 실행 파일명을 검색
	* @author 손나영
	*
	* @param lpTargetBuffer 실행 파일명을 받을 버퍼 포인터
	* @param TargetBufferLength 버퍼 포인터의 사이즈
	* return 성공 시 0이 아닌 값을 반환한다.
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
	* 지정된 콘솔 별칭 및 실행 파일에 대한 텍스트를 검색
	* @author 손나영
	*
	* @param lpSource 콘솔 별칭
	* @param lpTargetBuffer 버퍼 포인터
	* @param TargetBufferLength 버퍼 포인터의 사이즈
	* @param lpExeName 실행 파일명
	* return 콘솔 별칭 및 실행 파일의 텍스트 검사가 성공 여부. 성공일 경우 0이 아닌 값을 반환.
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

	//add를 반드시 해줘야 함.
	AddConsoleAliasW(Source, Target, ExeName);
	
	// source, target, exename 두 번 쓸 필요 x. 수정 작업하면 깔끔해질 듯.

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
	* 지정된 콘솔 화면 버퍼에서 사용하는 글꼴의 크기를 검색
	* @author : 손나영
	*
	* @param hConsoleOutput 콘솔 화면 버퍼에 대한 핸들. GENERIC_READ 권한이 있어야 함.
	* @param nFont 크기를 검색할 글꼴의 인덱스. 인덱스는 GetCurrentConsoleFont 함수를 호출하여 가져옴.
	* @return 논리적 단위로 각 문자의 너비와 높이를 포함하는 coord 구조를 반환. 실패 시 너비와 높이가 0.
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

	///printf("x는 %d y는 %d\n", Font_X, Font_Y);
	HANDLE StdHandle = GetStdHandle (STD_OUTPUT_HANDLE | GENERIC_READ);
	GetCurrentConsoleFont (StdHandle, FALSE, &GETFONT);
	COORD Fontsize = GetConsoleFontSize (StdHandle, GETFONT.nFont);

	Font_X = Fontsize.X;
	Font_Y = Fontsize.Y;

	///printf("x는 %d y는 %d\n", Font_X, Font_Y);
	sprintf(msg, "x는 %d y는 %d\n", Font_X, Font_Y);

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
	* 호출 프로세스의 콘솔에 대한 기록 설정을 검색한다.
	* @author : 손나영
	*
	* @param  lpConsoleHistoryInfo 호출 프로세스의 콘솔에 대한 기록 설정을 받는 CONSOLE_HISTORY_INFO 구조체에 대한 포인터
	* return 히스로리 설정 검색 성공/실패 여부. 성공 시 0이 아닌 값을 반환.
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
* 현재 콘솔 창의 원래 제목을 검색
* @author : 손나영
*
* @param  lpConsoleTitle  원래 제목을 받아오는 버퍼 포인터
* return 버퍼에 복사된 문자열 길이를 반환
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
		sprintf(msg, " GetConsoleOriginalTitleA() : SUCCESS \n\n Console 창의 OginalTitle : %s", buffer);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
		strcpy(buf, "SUCCESS");
		value = TRUE;

	//}else if(sizeof(buffer) <= sizeof(OriginTitle)){    : 아래와 같은 의미
	}else if(OriginTitle == 0){ 

		//GetLastError는 ERROR_SUCCESS를 반환
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
* 현재 콘솔 창의 원래 제목을 검색
* @author : 손나영
*
* @param  lpConsoleTitle  원래 제목을 받아오는 버퍼 포인터
* return 버퍼에 복사된 문자열 길이를 반환
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
	//sprintf(msg, "Original Title은 %s\n", buffer);


	if( OriginTitle != 0 ){
		sprintf(msg, " GetConsoleOriginalTitleW() : SUCCESS \n\n Console 창의 OginalTitle : %S", buffer);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
		strcpy(buf, "SUCCESS");
		value = TRUE;

	//}else if(sizeof(buffer) <= sizeof(OriginTitle)){    : 아래와 같은 의미
	}else if(OriginTitle == 0){ 

		//GetLastError는 ERROR_SUCCESS를 반환
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
	* 지정된 콘솔 화면 버퍼에 대한 확장 정보를 검색
	* @author : 손나영
	*
	* @param hcon : 콘솔 스크린 버퍼 핸들
	* @param  bi : CONSOLE_SCREEN_BUFFER_INFOEX 구조
	* return: 0이 아닌 값을 반환
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
	* 현재 콘솔 선택 항목에 대한 정보를 검색
	* @author : 손나영
	*
	* @param  lpConsoleSelectionInfo : CONSOLE_SELECTION_INFO 구조에 대한 포인터
	* return 정보 검색 성공 실패 여부. 성공 시 0이 아닌 값을 반환.
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
		strcpy(msg, " GetConsoleSelectionInfo() : FAIL \n\n 테스트 코드 내용을 다시 확인하십시오.");
	}

	wresult(__FILE__, __LINE__, "GetConsoleSelectionInfo", buf, "SUCCESS", msg);
	return value;

}




/**
	* DWORD WINAPI GetConsoleTitle(LPTSTR lpConsoleTitle,DWORD  nSize);
	* 현재 콘솔 창 타이틀 검색
	* @author : 손나영
	*
	* @param  lpConsoleTitle 콘솔타이틀 포인터
	* @param  nSize 버퍼 사이즈
	* return 콘솔 창 타이틀 길이 
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

	
	//콘솔 창 제목을 설정하는 함수 SetConsolTitle
	SetConsoleTitleA("GetConsoleTile_OS1");
	result = GetConsoleTitleA((LPSTR)lpConsoleTitle, MAX_PATH);


	// 유니코드 → 멀티바이트
	/*int iLen = WideCharToMultiByte(CP_ACP, 0, lpConsoleTitle, -1, title, 0, NULL, NULL);
	title = new char[iLen+1];
	WideCharToMultiByte(CP_ACP, 0, lpConsoleTitle, -1, title, iLen, NULL, NULL);*/

	if(result == 0){
		strcpy(msg, GetErrorMessage(" GetConsoleTitleA() : FAIL \n\n Error Message :", GetLastError()));

	}else{
		sprintf(msg, " GetConsoleTitleA() : SUCCESS \n\n 콘솔 타이틀 길이 : %d", result);
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
	* 현재 콘솔 글꼴에 대한 정보를 검색
	* @author 손나영
	*
	* @param  hOut 콘솔 스크린 버퍼 핸들 
	* @param  CFI CONSOLE_FONT_INFO 구조 포인터
	* return 정보 검색 성공 여부. 성공 시 0이 아닌 값을 반환.
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
* 현재 콘솔 글꼴에 대한 확장 정보를 검색
* @author : 손나영
*
* @param hConsoleOutput 콘솔 스크린 버퍼 핸들
* @param bMaximumWindow TRUE면 글꼴 정보가 최대 창 크기로 검색되고 FALSE 이면 현재 창 크기에 대한 글꼴 정보가 검색됨
* @param lpConsoleCurrentFontEx CONSOLE_FONT_INFOEX 구조 포인터
* return 성공 시 0이 아닌 값을 반환
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

	// RRRRRRRRRRRRRRRRRR : 0으로 설정하고 GET?

	result = GetCurrentConsoleFontEx(hStdout,FALSE,&orig);

	if (result != 0){

		sprintf(msg, " GetCurrentConsoleFontEx() : SUCCESS \n\n");
		strcpy(buf, "SUCCESS");
		value = TRUE;

	}else{
		strcpy(msg, GetErrorMessage(" GetCurrentConsoleFontEx() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetCurrentConsoleFontEx", buf, "SUCCESS", msg);

	//원래 폰트로 돌아감
	//SetCurrentConsoleFontEx(hStdout, FALSE, &orig);

	return value;
}

/**
* COORD WINAPI GetLargestConsoleWindowSize(
  _In_ HANDLE hConsoleOutput
  );
* 현재 글꼴 및 디스플레이 크기에 따라 가장 큰 콘솔 창 크기를 검색한다.
* @author : 손나영
*
* @param  hConsoleOutput 콘솔 스크린 버퍼 핸들
* return 최대 가능 콘솔 창의 좌우 값
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
	
	//콘솔 타이틀을 test로 설정
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
* 현재 콘솔에서 사용하는 마우스 버튼 수를 검색
* @author : 손나영
*
* @param  lpNumberOfMouseButtons 마우스 버튼 수를 받기 위한 변수 포인터
* return 성공 시 0이 아닌 값을 반환
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
* 호출 프로세스의 콘솔에 대한 기록 설정을 설정
* @author : 손나영
*
* @param lpConsoleHistoryInfo CONSOLE_HISTORY_INFO 구조체 포인터
* return 성공일 경우 0이 아닌 값을 반환
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
	* 지정된 콘솔 화면 버퍼에 대한 확장 정보를 설정
	* @author : 손나영
	*
	* @param  hConsoleOutput 콘솔 스크린 버퍼 핸들
	* @param  lpConsoleScreenBufferInfoEx CONSOLE_SCREEN_BUFFER_INFOEX 구조
	* return 성공일 경우 0이 아닌 값을 반환
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
	char msg[128] = "GetConsoleScreenBufferInfoEx가 실행되었습니다.";
	char msg2[128] = "GetConsoleScreenBufferInfoEx가 실패하였습니다.";
	*/

	CONSOLE_SCREEN_BUFFER_INFOEX csbi;  
    csbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);  

	//get으로 얻어와야함
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
	* 현재 콘솔 글꼴에 대한 확장 정보를 설정
	* @author 손나영
	*
	* @param hConsoleOutput 콘솔 스크린 버퍼 핸들
	* @param bMaximumWindow TRUE이면 글꼴 정보가 최대 창 크기로 설정됨. FASLE이면 현재 창 크기에 대한 글꼴 정보가 설정됨.
	* @param lpConsoleCurrentFontEx CONSOLE_FONT_INFOEX 구조 포인터
	* return 성공일 경우 0이 아닌 값을 반환
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

	////printf("기본 사이즈 : %d \n ", orig.dwFontSize.X);
	//CONSOLE_FONT_INFO CFI;
	//COORD FontSize2;
	//HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	//result = GetCurrentConsoleFont(hOut, false, &CFI);
	//FontSize2 = GetConsoleFontSize(hOut,CFI.nFont);

	//printf("\n\n\n 사이즈 : %d \n\n\n", FontSize2);

	//CONSOLE_FONT_INFOEX current = {0}; 
	//COORD FontSize = {13,13};	
	//orig.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	//current.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	//FontSize.X = 13;
	//FontSize.Y = 13;

	//printf("폰트사이즈x : %d 폰트 사이즈 y : %d", FontSize.X, FontSize.Y);
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

	//원래대로 되돌리기
	//SetCurrentConsoleFontEx(hStdout,FALSE,&orig);
	
	return value;
}