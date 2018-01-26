#include "TestTransacted.h"


/**
* DWORD WINAPI GetCompressedFileSizeTransacted(
  _In_      LPCTSTR lpFileName,
  _Out_opt_ LPDWORD lpFileSizeHigh,
  _In_      HANDLE  hTransaction
);
* 트랜잭션 처리로 지정된 파일을 저장하는 데 사용 된 디스크 저장 영역의 실제 바이트 수를 검색한다. 권장하지 않음.
* @author : 손찬영  
*
* @param  lpFileName		파일의 이름
* @param  lpFileSizeHigh	압축 된 파일 크기의 상위 DWORD를 받는 변수에 대한 포인터
* @param  hTransaction		트랜잭션 핸들
* @return					함수가 성공하면 반환 값은 지정된 파일을 저장하는 데 사용 된 실제 디스크 저장소 바이트 수의 하위 DWORD
*/
BOOL test_GetCompressedFileSizeTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCTSTR lpFileName = L"손찬영\\test_GetCompressedFileSizeTransactedW.txt";
	HANDLE  hTransaction, hFile;
	DWORD	ret = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hFile = MyCreateFile(lpFileName))){

		return FALSE;
	}
	CloseHandle(hFile);

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	ret = GetCompressedFileSizeTransactedW(lpFileName, NULL, hTransaction);

	if(INVALID_FILE_SIZE != ret){
		sprintf(msg, "GetCompressedFileSizeTransactedW 성공 : ret = %lu", ret);
		strcpy(buf, "GetCompressedFileSizeTransactedW 성공");
		
	}else{
		strcpy(msg, GetErrorMessage("GetCompressedFileSizeTransactedW 실패 : ", GetLastError()));
		strcpy(buf, "GetCompressedFileSizeTransactedW 실패");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetCompressedFileSizeTransactedW 성공", msg);

	CloseHandle(hTransaction);
	DeleteFile(lpFileName);

	return result;
}

/**
* DWORD WINAPI GetCompressedFileSizeTransacted(
  _In_      LPCTSTR lpFileName,
  _Out_opt_ LPDWORD lpFileSizeHigh,
  _In_      HANDLE  hTransaction
);
* 트랜잭션 처리로 지정된 파일을 저장하는 데 사용 된 디스크 저장 영역의 실제 바이트 수를 검색한다. 권장하지 않음.
* @author : 손찬영  
*
* @param  lpFileName		파일의 이름
* @param  lpFileSizeHigh	압축 된 파일 크기의 상위 DWORD를 받는 변수에 대한 포인터
* @param  hTransaction		트랜잭션 핸들
* @return					함수가 성공하면 반환 값은 지정된 파일을 저장하는 데 사용 된 실제 디스크 저장소 바이트 수의 하위 DWORD
*/
BOOL test_GetCompressedFileSizeTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCSTR lpFileName = "손찬영\\test_GetCompressedFileSizeTransactedA.txt";
	HANDLE  hTransaction, hFile;
	DWORD	ret = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hFile = MyCreateFileA(lpFileName))){

		return FALSE;
	}
	CloseHandle(hFile);

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	ret = GetCompressedFileSizeTransactedA(lpFileName, NULL, hTransaction);

	if(INVALID_FILE_SIZE != ret){
		sprintf(msg, "GetCompressedFileSizeTransactedW 성공 : ret = %lu", ret);
		strcpy(buf, "GetCompressedFileSizeTransactedW 성공");
		
	}else{
		strcpy(msg, GetErrorMessage("GetCompressedFileSizeTransactedW 실패 : ", GetLastError()));
		strcpy(buf, "GetCompressedFileSizeTransactedW 실패");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetCompressedFileSizeTransactedW 성공", msg);

	CloseHandle(hTransaction);
	DeleteFileA(lpFileName);

	return result;
}

/**
* HANDLE WINAPI FindFirstStreamTransactedW(
  _In_       LPCWSTR            lpFileName,
  _In_       STREAM_INFO_LEVELS InfoLevel,
  _Out_      LPVOID             lpFindStreamData,
  _Reserved_ DWORD              dwFlags,
  _In_       HANDLE             hTransaction
);
* 지정된 파일 또는 디렉터리의 첫 번째 스트림을 트랜잭션 연산으로 열거한다. 권장하지 않음.
* @author : 손찬영  
*
* @param  lpFileName		완전한 파일 이름.
* @param  InfoLevel			반환 된 데이터의 정보 수준
* @param  lpFindStreamData	파일 데이터를 수신하는 버퍼에 대한 포인터
* @param  dwFlags			예약
* @param  hTransaction		트랜잭션 핸들
* @return					함수가 성공하면 반환 값은 이후에 FindNextStreamW 함수를 호출 할 때 사용할 수있는 검색 핸들, 실패하면 INVALID_HANDLE_VALUE
*/
BOOL test_FindFirstStreamTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hFile;
	LPCWSTR lpFileName = L"손찬영\\test_FindFirstStreamTransactedW.txt";
	STREAM_INFO_LEVELS InfoLevel = FindStreamInfoStandard;
	WIN32_FIND_STREAM_DATA lpFindStreamData;
	HANDLE	hTransaction;
	HANDLE	handle = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hFile = MyCreateFile(lpFileName))){

		return FALSE;
	}
	CloseHandle(hFile);

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	handle = FindFirstStreamTransactedW(lpFileName, InfoLevel, (LPVOID)&lpFindStreamData, 0, hTransaction);

	if(INVALID_HANDLE_VALUE != handle){
		sprintf(msg, "FindFirstStreamTransactedW 성공 : handle = %d", handle);
		strcpy(buf, "FindFirstStreamTransactedW 성공");
		
	}else{
		strcpy(msg, GetErrorMessage("FindFirstStreamTransactedW 실패 : ", GetLastError()));
		strcpy(buf, "FindFirstStreamTransactedW 실패");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "FindFirstStreamTransactedW 성공", msg);

	CloseHandle(hTransaction);
	CloseHandle(handle);
	DeleteFile(lpFileName);

	return result;
}

/**
* HANDLE WINAPI FindFirstFileTransacted(
  _In_       LPCTSTR            lpFileName,
  _In_       FINDEX_INFO_LEVELS fInfoLevelId,
  _Out_      LPVOID             lpFindFileData,
  _In_       FINDEX_SEARCH_OPS  fSearchOp,
  _Reserved_ LPVOID             lpSearchFilter,
  _In_       DWORD              dwAdditionalFlags,
  _In_       HANDLE             hTransaction
);
* 특정 이름과 일치하는 이름을 가진 파일 또는 하위 디렉토리가 검색된 작업으로 검색된다.
* @author : 손찬영  
*
* @param  lpFileName		디렉토리 또는 경로 및 파일 이름
* @param  fInfoLevelId		반환 된 데이터의 정보 수준
* @param  lpFindFileData	발견 된 파일이나 서브 디렉토리에 관한 정보를 받는 WIN32_FIND_DATA 구조체에 대한 포인터
* @param  fSearchOp			FINDEX_SEARCH_OPS 열거 형 값 중 하나
* @param  lpSearchFilter	지정한 fSearchOp에 구조화 된 검색 정보가 필요한 경우 검색 조건에 대한 포인터
* @param  dwAdditionalFlags	검색을 제어하는 추가 플래그
* @param  hTransaction		트랜잭션 핸들
* @return					함수가 성공하면 반환 값은 FindNextFile 또는 FindClose 에 대한 후속 호출에서 사용되는 검색 핸들
*/
BOOL test_FindFirstFileTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hFile;
	LPCWSTR lpFileName = L"손찬영\\test_FindFirstFileTransactedW.txt";
	FINDEX_INFO_LEVELS fInfoLevelId = FindExInfoStandard;
	WIN32_FIND_DATA    lpFindFileData;
	FINDEX_SEARCH_OPS  fSearchOp = FindExSearchNameMatch;
	LPVOID             lpSearchFilter = NULL;
	DWORD              dwAdditionalFlags = FIND_FIRST_EX_CASE_SENSITIVE;
	HANDLE	hTransaction;
	HANDLE	handle = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hFile = MyCreateFile(lpFileName))){

		return FALSE;
	}
	CloseHandle(hFile);

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	handle = FindFirstFileTransactedW(lpFileName, fInfoLevelId, (LPVOID)&lpFindFileData, fSearchOp, lpSearchFilter, dwAdditionalFlags, hTransaction);

	if(INVALID_HANDLE_VALUE != handle){
		sprintf(msg, "FindFirstFileTransactedW 성공 : handle = %d", handle);
		strcpy(buf, "FindFirstFileTransactedW 성공");
		
	}else{
		strcpy(msg, GetErrorMessage("FindFirstFileTransactedW 실패 : ", GetLastError()));
		strcpy(buf, "FindFirstFileTransactedW 실패");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "FindFirstFileTransactedW 성공", msg);

	CloseHandle(hTransaction);
	CloseHandle(handle);
	DeleteFile(lpFileName);

	return result;
}


/**
* HANDLE WINAPI FindFirstFileTransacted(
  _In_       LPCTSTR            lpFileName,
  _In_       FINDEX_INFO_LEVELS fInfoLevelId,
  _Out_      LPVOID             lpFindFileData,
  _In_       FINDEX_SEARCH_OPS  fSearchOp,
  _Reserved_ LPVOID             lpSearchFilter,
  _In_       DWORD              dwAdditionalFlags,
  _In_       HANDLE             hTransaction
);
* 특정 이름과 일치하는 이름을 가진 파일 또는 하위 디렉토리가 검색된 작업으로 검색된다.
* @author : 손찬영  
*
* @param  lpFileName		디렉토리 또는 경로 및 파일 이름
* @param  fInfoLevelId		반환 된 데이터의 정보 수준
* @param  lpFindFileData	발견 된 파일이나 서브 디렉토리에 관한 정보를 받는 WIN32_FIND_DATA 구조체에 대한 포인터
* @param  fSearchOp			FINDEX_SEARCH_OPS 열거 형 값 중 하나
* @param  lpSearchFilter	지정한 fSearchOp에 구조화 된 검색 정보가 필요한 경우 검색 조건에 대한 포인터
* @param  dwAdditionalFlags	검색을 제어하는 추가 플래그
* @param  hTransaction		트랜잭션 핸들
* @return					함수가 성공하면 반환 값은 FindNextFile 또는 FindClose 에 대한 후속 호출에서 사용되는 검색 핸들
*/
BOOL test_FindFirstFileTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hFile;
	LPCSTR lpFileName = "손찬영\\test_FindFirstFileTransactedA.txt";
	FINDEX_INFO_LEVELS fInfoLevelId = FindExInfoStandard;
	WIN32_FIND_DATA    lpFindFileData;
	FINDEX_SEARCH_OPS  fSearchOp = FindExSearchNameMatch;
	LPVOID             lpSearchFilter = NULL;
	DWORD              dwAdditionalFlags = FIND_FIRST_EX_CASE_SENSITIVE;
	HANDLE	hTransaction;
	HANDLE	handle = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hFile = MyCreateFileA(lpFileName))){

		return FALSE;
	}
	CloseHandle(hFile);

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	handle = FindFirstFileTransactedA(lpFileName, fInfoLevelId, (LPVOID)&lpFindFileData, fSearchOp, lpSearchFilter, dwAdditionalFlags, hTransaction);

	if(INVALID_HANDLE_VALUE != handle){
		sprintf(msg, "FindFirstFileTransactedA 성공 : handle = %d", handle);
		strcpy(buf, "FindFirstFileTransactedA 성공");
		
	}else{
		strcpy(msg, GetErrorMessage("FindFirstFileTransactedA 실패 : ", GetLastError()));
		strcpy(buf, "FindFirstFileTransactedA 실패");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "FindFirstFileTransactedA 성공", msg);

	CloseHandle(hTransaction);
	CloseHandle(handle);
	DeleteFileA(lpFileName);

	return result;
}


/**
* HANDLE WINAPI FindFirstFileNameTransactedW(
  _In_     LPCWSTR lpFileName,
  _In_     DWORD   dwFlags,
  _Inout_  LPDWORD StringLength,
  _Inout_  PWCHAR  LinkName,
  _In_opt_ HANDLE  hTransaction
);
* 지정된 파일에 대한 모든 하드 링크의 열거를 트랜잭션 연산으로 작성한다. 권장되지 않음.
* @author : 손찬영  
*
* @param  lpFileName	파일의 이름
* @param  dwFlags		예약
* @param  StringLength	LinkName 매개 변수가 가리키는 버퍼의 크기(문자 수)
* @param  LinkName		lpFileName에 대해 발견 된 첫 번째 링크 이름을 저장할 버퍼에 대한 포인터
* @param  hTransaction	트랜잭션 핸들
* @return				함수가 성공하면 반환 값은 FindNextFile 또는 FindClose 에 대한 후속 호출에서 사용되는 검색 핸들
*/
BOOL test_FindFirstFileNameTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hFile;
	LPCWSTR lpFileName = L"손찬영\\test_FindFirstFileNameTransactedW.txt";
	DWORD   dwFlags = 0;
	DWORD StringLength = BUFSIZ;
	WCHAR  LinkName[BUFSIZ];
	HANDLE	hTransaction;
	HANDLE	handle = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hFile = MyCreateFile(lpFileName))){

		return FALSE;
	}
	CloseHandle(hFile);

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	handle = FindFirstFileNameTransactedW(lpFileName, dwFlags, &StringLength, LinkName, hTransaction);

	if(INVALID_HANDLE_VALUE != handle){
		sprintf(msg, "FindFirstFileTransactedW 성공 : handle = %d\nLinkName = %S", handle, LinkName);
		strcpy(buf, "FindFirstFileTransactedW 성공");
		
	}else{
		strcpy(msg, GetErrorMessage("FindFirstFileTransactedW 실패 : ", GetLastError()));
		strcpy(buf, "FindFirstFileTransactedW 실패");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "FindFirstFileTransactedW 성공", msg);

	CloseHandle(hTransaction);
	CloseHandle(handle);
	DeleteFile(lpFileName);

	return result;
}