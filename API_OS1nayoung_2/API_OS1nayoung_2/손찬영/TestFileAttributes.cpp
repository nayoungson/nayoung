#include "TestFileAttributes.h"


/**
* BOOL WINAPI GetFileAttributesEx(
  _In_  LPCTSTR                lpFileName,
  _In_  GET_FILEEX_INFO_LEVELS fInfoLevelId,
  _Out_ LPVOID                 lpFileInformation
);
* 지정된 파일 또는 디렉토리의 속성을 검색한다.
* @author : 손찬영  
*
* @param  lpFileName		파일 또는 디렉토리의 이름
* @param  fInfoLevelId		검색 할 속성 정보 클래스
* @param  lpFileInformation 속성 정보를받는 버퍼에 대한 포인터
* @return					성공/실패 여부
*/
BOOL test_GetFileAttributesExW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	DWORD fileAttributes = 0;
	LPCWSTR fileName = L"손찬영\\test_GetFileAttributesExW.txt";
	HANDLE hFile = NULL;
	WIN32_FILE_ATTRIBUTE_DATA fileAttributesData;
	FILETIME fileTimeLocal;
	SYSTEMTIME systemTimeLocal, systemTimeNow;
	char createTime[BUFSIZ], nowTime[BUFSIZ];
	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* FILE_ATTRIBUTE_TEMPORARY 속성으로 파일을 생성한다. */
	hFile = CreateFileW(fileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if(hFile == INVALID_HANDLE_VALUE){
		sprintf(msg, GetErrorMessage("파일 열기 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "CreateFileA 실패", "CreateFile 성공", msg);

		return FALSE;
	}

	/* 파일 생성 당시의 시간을 잰다. */
	GetSystemTime(&systemTimeNow); 

	/* 파일의 속성을 가져온다 */
	result = GetFileAttributesExW(fileName, GetFileExInfoStandard, (void *)&fileAttributesData);

	/* 함수 실패 */
	if(result == FALSE){ 
		strcpy(msg, GetErrorMessage("GetFileAttributesExW 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "GetFileAttributesExW 실패", "GetFileAttributesExW 성공", msg);

		return FALSE;
	}

	/* 최근 수정 시간(파일생성시간)을 로컬파일시간으로 변환한다 */
	if(!FileTimeToLocalFileTime(&fileAttributesData.ftLastWriteTime, &fileTimeLocal)){
		strcpy(msg, GetErrorMessage("FileTimeToLocalFileTime 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ , __FUNCTION__, "FileTimeToLocalFileTime 실패", "FileTimeToLocalFileTime 성공", msg);

		return FALSE;

	}

	/*로컬파일시간을 시스템시간으로 변경한다 */
	if(!FileTimeToSystemTime(&fileTimeLocal, &systemTimeLocal)){
		strcpy(msg, GetErrorMessage("FileTimeToSystemTime 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "FileTimeToSystemTime 실패", "FileTimeToSystemTime 성공", msg);

		return FALSE;

	}
	/* 파일 생성 시간과 속성으로 가져온 파일 생성 시간이 동일하면 성공으로 판단한다. */
	if((systemTimeLocal.wHour == systemTimeNow.wHour+9) && (systemTimeLocal.wMinute == systemTimeNow.wMinute)){
		sprintf(msg, "GetFileAttributesExW 성공 : (생성시간 %d : %d)", systemTimeLocal.wHour, systemTimeLocal.wMinute);
		strcpy(buf, "GetFileAttributesExW 성공");

	}else{
		sprintf(msg, "GetFileAttributesExW 실패 : (측정시간 %d : %d), (파일시간 %d : %d)", systemTimeNow.wHour+9, systemTimeNow.wMinute, systemTimeLocal.wHour, systemTimeLocal.wMinute);
		strcpy(buf, "GetFileAttributesExW 실패");

		result = FALSE;

	}
	wresult(__FILE__,__LINE__ , __FUNCTION__, buf, "GetFileAttributesExW 성공", msg);

	CloseHandle(hFile);
	if(!DeleteFileW(fileName)){
		#ifdef OQADBGPRINT
		printf(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
		#endif
	}

	return result;
}


/**
* DWORD WINAPI GetFileAttributes(
  _In_ LPCTSTR lpFileName
);
* 지정된 파일 또는 디렉토리의 파일 시스템 속성을 검색한다.
* @author : 손찬영  
*
* @param  lpFileName		파일 또는 디렉토리의 이름
* @return					함수가 성공하면 반환 값에 지정된 파일이나 디렉토리의 특성이 포함
*/
BOOL test_GetFileAttributesW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	DWORD fileAttributes = 0;
	LPCWSTR fileName = L"손찬영\\test_GetFileAttributesW.txt";
	HANDLE hFile = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* FILE_ATTRIBUTE_TEMPORARY 속성으로 파일을 연다 */
	hFile = CreateFile(fileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	
	if(hFile == INVALID_HANDLE_VALUE){ //파일 열기 실패
		sprintf(msg, GetErrorMessage("CreateFile 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile 성공", msg);

		return FALSE;
	}

	fileAttributes = GetFileAttributesW(fileName);

	/* 함수가 실패 */
	if(fileAttributes == INVALID_FILE_ATTRIBUTES){
		strcpy(msg, GetErrorMessage("GetFileAttributesW 실패 : ", GetLastError()));
		result = FALSE;	
	
	}else{
		/* 함수가 성공하고 속성이 FILE_ATTRIBUTE_TEMPORARY이면 성공으로 판단 */
		if(fileAttributes & FILE_ATTRIBUTE_TEMPORARY){
			strcpy(msg, "GetFileAttributesW 성공");
			strcpy(buf, msg);
		
		}else{
			sprintf(msg, "GetFileAttributesW 실패 : fileAttributes = %d(십진수)", fileAttributes);
			strcpy(buf, "GetFileAttributesW 실패");
			result = FALSE;	
		}
	}
	wresult(__FILE__,__LINE__ , __FUNCTION__, msg, "GetFileAttributesW 성공", msg);


	CloseHandle(hFile);

	/* 종료 전 파일을 삭제한다 */
	if(!DeleteFileW(fileName)){
		#ifdef OQADBGPRINT
		printf(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
		#endif
	}

	return result;
}



/**
* BOOL WINAPI GetFileAttributesEx(
  _In_  LPCTSTR                lpFileName,
  _In_  GET_FILEEX_INFO_LEVELS fInfoLevelId,
  _Out_ LPVOID                 lpFileInformation
);
* 지정된 파일 또는 디렉토리의 속성을 검색한다.
* @author : 손찬영  
*
* @param  lpFileName		파일 또는 디렉토리의 이름
* @param  fInfoLevelId		검색 할 속성 정보 클래스
* @param  lpFileInformation 속성 정보를받는 버퍼에 대한 포인터
* @return					성공/실패 여부
*/
BOOL test_GetFileAttributesExA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	DWORD fileAttributes = 0;
	LPCSTR fileName = "손찬영\\test_GetFileAttributesExA.txt";
	HANDLE hFile = NULL;
	WIN32_FILE_ATTRIBUTE_DATA fileAttributesData;
	FILETIME fileTimeLocal;
	SYSTEMTIME systemTimeLocal, systemTimeNow;
	char createTime[BUFSIZ], nowTime[BUFSIZ];
	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* FILE_ATTRIBUTE_TEMPORARY 속성으로 파일을 생성한다. */
	hFile = CreateFileA(fileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if(hFile == INVALID_HANDLE_VALUE){
		sprintf(msg, GetErrorMessage("파일 열기 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "CreateFileA 실패", "CreateFile 성공", msg);

		return FALSE;
	}

	/* 파일 생성 당시의 시간을 잰다. */
	GetSystemTime(&systemTimeNow); 

	/* 파일의 속성을 가져온다 */
	result = GetFileAttributesExA(fileName, GetFileExInfoStandard, (void *)&fileAttributesData);

	/* 함수 실패 */
	if(result == FALSE){ 
		strcpy(msg, GetErrorMessage("GetFileAttributesExA 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "GetFileAttributesExA 실패", "GetFileAttributesExA 성공", msg);

		return FALSE;
	}

	/* 최근 수정 시간(파일생성시간)을 로컬파일시간으로 변환한다 */
	if(!FileTimeToLocalFileTime(&fileAttributesData.ftLastWriteTime, &fileTimeLocal)){
		strcpy(msg, GetErrorMessage("FileTimeToLocalFileTime 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ , __FUNCTION__, "FileTimeToLocalFileTime 실패", "FileTimeToLocalFileTime 성공", msg);

		return FALSE;

	}

	/*로컬파일시간을 시스템시간으로 변경한다 */
	if(!FileTimeToSystemTime(&fileTimeLocal, &systemTimeLocal)){
		strcpy(msg, GetErrorMessage("FileTimeToSystemTime 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "FileTimeToSystemTime 실패", "FileTimeToSystemTime 성공", msg);

		return FALSE;

	}
	/* 파일 생성 시간과 속성으로 가져온 파일 생성 시간이 동일하면 성공으로 판단한다. */
	if((systemTimeLocal.wHour == systemTimeNow.wHour+9) && (systemTimeLocal.wMinute == systemTimeNow.wMinute)){
		sprintf(msg, "GetFileAttributesExA 성공 : (생성시간 %d : %d)", systemTimeLocal.wHour, systemTimeLocal.wMinute);
		strcpy(buf, "GetFileAttributesExA 성공");

	}else{
		sprintf(msg, "GetFileAttributesExA 실패 : (측정시간 %d : %d), (파일시간 %d : %d)", systemTimeNow.wHour+9, systemTimeNow.wMinute, systemTimeLocal.wHour, systemTimeLocal.wMinute);
		strcpy(buf, "GetFileAttributesExA 실패");

		result = FALSE;

	}
	wresult(__FILE__,__LINE__ , __FUNCTION__, buf, "GetFileAttributesExA 성공", msg);

	CloseHandle(hFile);
	if(!DeleteFileA(fileName)){
		#ifdef OQADBGPRINT
		printf(GetErrorMessage("DeleteFileA 실패 : ", GetLastError()));
		#endif
	}

	return result;
}




/**
* BOOL WINAPI GetFileAttributesTransacted(
  _In_  LPCTSTR                lpFileName,
  _In_  GET_FILEEX_INFO_LEVELS fInfoLevelId,
  _Out_ LPVOID                 lpFileInformation,
  _In_  HANDLE                 hTransaction
);
* 지정된 파일 또는 디렉토리의 파일 시스템 속성을 트랜잭션 조작으로 검색한다. 권장하지 않음.
* @author : 손찬영  
*
* @param  lpFileName		파일 또는 디렉토리의 이름
* @param  fInfoLevelId		검색 할 속성 정보의 레벨.
* @param  lpFileInformation 속성 정보를받는 버퍼에 대한 포인터
* @param  hTransaction		트랜잭션 핸들
* @return					성공/실패 여부
*/
BOOL test_GetFileAttributesTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	LPCTSTR lpFileName = L"손찬영\\test_GetFileAttributesTransactedW.txt";
	DWORD   dwFileAttributes = FILE_ATTRIBUTE_HIDDEN;
	HANDLE  hTransaction, hFile;
	WIN32_FILE_ATTRIBUTE_DATA FileInformation;

	FILETIME fileTimeLocal;
	SYSTEMTIME systemTimeLocal, systemTimeNow;
	char createTime[BUFSIZ], nowTime[BUFSIZ];

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	hFile = CreateFileW(lpFileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	GetSystemTime(&systemTimeNow); //파일 생성 당시 시간을 저장함
	
	if(hFile == INVALID_HANDLE_VALUE){ //파일 열기 실패
		sprintf(msg, GetErrorMessage("CreateFileW 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile 성공", msg);

		return FALSE;
	}
	CloseHandle(hFile);

	result = GetFileAttributesTransactedW(lpFileName, GetFileExInfoStandard, &FileInformation, hTransaction);

	if(!FileTimeToLocalFileTime(&FileInformation.ftLastWriteTime, &fileTimeLocal)){ //로컬타임으로 변경 실패하면
		strcpy(msg, GetErrorMessage("FileTimeToLocalFileTime 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "FileTimeToLocalFileTime 실패", "FileTimeToLocalFileTime 성공", msg);

		return FALSE;

	}

	if(!FileTimeToSystemTime(&fileTimeLocal, &systemTimeLocal)){ //시스템시간으로 변경 실패
		strcpy(msg, GetErrorMessage("FileTimeToSystemTime 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "FileTimeToSystemTime 실패", "FileTimeToSystemTime 성공", msg);

		return FALSE;

	}

	sprintf(createTime, "생성시간 %d : %d\n", systemTimeLocal.wHour, systemTimeLocal.wMinute); //파일 생성 시간
	sprintf(nowTime, "현재시간 %d : %d", systemTimeNow.wHour+9, systemTimeNow.wMinute); //생성당시 시간(UTC시간) + 9


	if(result){
		sprintf(msg, "GetFileAttributesTransactedW 성공 : ");
		strcat(msg, createTime);
		strcat(msg, nowTime);
		strcpy(buf, "GetFileAttributesTransactedW 성공");	

	}else{
		strcpy(msg, GetErrorMessage("GetFileAttributesTransactedW 실패 : ", GetLastError()));
		strcpy(buf, "GetFileAttributesTransactedW 실패");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetFileAttributesTransactedW 성공", msg);

	CloseHandle(hTransaction);

	if(!DeleteFile(lpFileName)){
		#ifdef OQADBGPRINT
		printf("DeleteFile 실패\n");
		#endif
	}

	return result;
	
}


/**
* BOOL WINAPI GetFileAttributesTransacted(
  _In_  LPCTSTR                lpFileName,
  _In_  GET_FILEEX_INFO_LEVELS fInfoLevelId,
  _Out_ LPVOID                 lpFileInformation,
  _In_  HANDLE                 hTransaction
);
* 지정된 파일 또는 디렉토리의 파일 시스템 속성을 트랜잭션 조작으로 검색한다. 권장하지 않음.
* @author : 손찬영  
*
* @param  lpFileName		파일 또는 디렉토리의 이름
* @param  fInfoLevelId		검색 할 속성 정보의 레벨.
* @param  lpFileInformation 속성 정보를받는 버퍼에 대한 포인터
* @param  hTransaction		트랜잭션 핸들
* @return					성공/실패 여부
*/
BOOL test_GetFileAttributesTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	LPCSTR lpFileName = "손찬영\\test_GetFileAttributesTransactedA.txt";
	DWORD   dwFileAttributes = FILE_ATTRIBUTE_HIDDEN;
	HANDLE  hTransaction, hFile;
	WIN32_FILE_ATTRIBUTE_DATA FileInformation;

	FILETIME fileTimeLocal;
	SYSTEMTIME systemTimeLocal, systemTimeNow;
	char createTime[BUFSIZ], nowTime[BUFSIZ];

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	hFile = CreateFileA(lpFileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	GetSystemTime(&systemTimeNow); //파일 생성 당시 시간을 저장함
	
	if(hFile == INVALID_HANDLE_VALUE){ //파일 열기 실패
		sprintf(msg, GetErrorMessage("CreateFileW 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile 성공", msg);

		return FALSE;
	}
	CloseHandle(hFile);

	result = GetFileAttributesTransactedA(lpFileName, GetFileExInfoStandard, &FileInformation, hTransaction);

	if(!FileTimeToLocalFileTime(&FileInformation.ftLastWriteTime, &fileTimeLocal)){ //로컬타임으로 변경 실패하면
		strcpy(msg, GetErrorMessage("FileTimeToLocalFileTime 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "FileTimeToLocalFileTime 실패", "FileTimeToLocalFileTime 성공", msg);

		return FALSE;

	}

	if(!FileTimeToSystemTime(&fileTimeLocal, &systemTimeLocal)){ //시스템시간으로 변경 실패
		strcpy(msg, GetErrorMessage("FileTimeToSystemTime 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "FileTimeToSystemTime 실패", "FileTimeToSystemTime 성공", msg);

		return FALSE;

	}

	sprintf(createTime, "생성시간 %d : %d\n", systemTimeLocal.wHour, systemTimeLocal.wMinute); //파일 생성 시간
	sprintf(nowTime, "현재시간 %d : %d", systemTimeNow.wHour+9, systemTimeNow.wMinute); //생성당시 시간(UTC시간) + 9


	if(result){
		sprintf(msg, "GetFileAttributesTransactedA 성공 : ");
		strcat(msg, createTime);
		strcat(msg, nowTime);
		strcpy(buf, "GetFileAttributesTransactedA 성공");	

	}else{
		strcpy(msg, GetErrorMessage("GetFileAttributesTransactedA 실패 : ", GetLastError()));
		strcpy(buf, "GetFileAttributesTransactedA 실패");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetFileAttributesTransactedA 성공", msg);

	CloseHandle(hTransaction);

	if(!DeleteFileA(lpFileName)){
		#ifdef OQADBGPRINT
		printf("DeleteFile 실패\n");
		#endif
	}

	return result;
}


/**
* BOOL WINAPI SetFileAttributesTransacted(
  _In_ LPCTSTR lpFileName,
  _In_ DWORD   dwFileAttributes,
  _In_ HANDLE  hTransaction
);
* 파일 또는 디렉토리의 속성을 트랜잭션 조작으로 설정한다. 권장하지 않음.
* @author : 손찬영  
*
* @param  lpFileName		속성을 설정할 파일의 이름
* @param  dwFileAttributes	파일에 대해 설정할 파일 특성
* @param  hTransaction		트랜잭션 핸들
* @return					성공/실패 여부
*/
BOOL test_SetFileAttributesTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	LPCTSTR lpFileName = L"손찬영\\test_SetFileAttributesTransactedW.txt";
	DWORD   dwFileAttributes = FILE_ATTRIBUTE_HIDDEN;
	HANDLE  hTransaction, hFile;

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	hFile = CreateFileW(lpFileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	
	if(hFile == INVALID_HANDLE_VALUE){ //파일 열기 실패
		sprintf(msg, GetErrorMessage("CreateFileW 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile 성공", msg);

		return FALSE;
	}
	CloseHandle(hFile);

	result = SetFileAttributesTransactedW(lpFileName, dwFileAttributes, hTransaction);

	if(result){
		strcpy(msg, "SetFileAttributesTransactedW 성공");
		strcpy(buf, "SetFileAttributesTransactedW 성공");	

	}else{
		strcpy(msg, GetErrorMessage("SetFileAttributesTransactedW 실패 : ", GetLastError()));
		strcpy(buf, "SetFileAttributesTransactedW 실패");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetFileAttributesTransactedW 성공", msg);

	CloseHandle(hTransaction);

	if(!DeleteFile(lpFileName)){
		#ifdef OQADBGPRINT
		printf("DeleteFile 실패\n");
		#endif
	}

	return result;
}


/**
* BOOL WINAPI SetFileAttributesTransacted(
  _In_ LPCTSTR lpFileName,
  _In_ DWORD   dwFileAttributes,
  _In_ HANDLE  hTransaction
);
* 파일 또는 디렉토리의 속성을 트랜잭션 조작으로 설정한다. 권장하지 않음.
* @author : 손찬영  
*
* @param  lpFileName		속성을 설정할 파일의 이름
* @param  dwFileAttributes	파일에 대해 설정할 파일 특성
* @param  hTransaction		트랜잭션 핸들
* @return					성공/실패 여부
*/
BOOL test_SetFileAttributesTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	LPCSTR lpFileName = "손찬영\\test_SetFileAttributesTransactedA.txt";
	DWORD   dwFileAttributes = FILE_ATTRIBUTE_HIDDEN;
	HANDLE  hTransaction, hFile;

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	hFile = CreateFileA(lpFileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	
	if(hFile == INVALID_HANDLE_VALUE){ //파일 열기 실패
		sprintf(msg, GetErrorMessage("CreateFileW 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile 성공", msg);

		return FALSE;
	}
	CloseHandle(hFile);

	result = SetFileAttributesTransactedA(lpFileName, dwFileAttributes, hTransaction);

	if(result){
		strcpy(msg, "SetFileAttributesTransactedA 성공");
		strcpy(buf, "SetFileAttributesTransactedA 성공");	

	}else{
		strcpy(msg, GetErrorMessage("SetFileAttributesTransactedA 실패 : ", GetLastError()));
		strcpy(buf, "SetFileAttributesTransactedA 실패");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetFileAttributesTransactedA 성공", msg);

	CloseHandle(hTransaction);

	if(!DeleteFileA(lpFileName)){
		#ifdef OQADBGPRINT
		printf("DeleteFile 실패\n");
		#endif
	}

	return result;
}

