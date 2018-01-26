#include "TestFile2.h"

/**
* BOOL MoveFileTransactedW(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine, 
LPVOID lpData, DWORD dwFlags, HANDLE hTransaction)
* 자식을 포함하여 기존 파일이나 디렉토리를 트랜잭션 연산으로 이동한다. 권장되지 않음.
* @author : 손찬영  
*
* @param  lpExistingFileName 로컬 컴퓨터에있는 기존 파일 또는 디렉터리의 현재 이름
* @param  lpNewFileName 파일 또는 디렉토리의 새 이름
* @param  lpProgressRoutine 파일의 다른 부분이 이동 될 때마다 호출 되는 CopyProgressRoutine 콜백 함수에 대한 포인터
* @param  lpData CopyProgressRoutine 콜백 함수에 전달할 인수
* @param  dwFlags 이동 옵션
* @param  hTransaction 트랜잭션 핸들
* @return 성공/실패여부
*/
BOOL test_MoveFileTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCTSTR            lpExistingFileName = L"손찬영\\test_MoveFileTransactedW.txt";
	LPCTSTR            lpNewFileName = L"손찬영\\test_MoveFileTransactedW_moved.txt";
	LPPROGRESS_ROUTINE lpProgressRoutine = NULL;
	LPVOID             lpData = NULL;
	DWORD              dwFlags = MOVEFILE_COPY_ALLOWED;
	HANDLE  hTransaction, hFile;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hTransaction = MyCreateTransaction())){
		return FALSE;
	}
	if(!(hFile = MyCreateFile(lpExistingFileName))){
		return FALSE;
	}
	if(!CloseHandle(hFile)){
		strcpy(msg, GetErrorMessage("CloseHandle 실패 : ", GetLastError()));
		strcpy(buf, "CloseHandle 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CloseHandle 성공", msg);
		
		return FALSE;
	}

	result = MoveFileTransactedW(lpExistingFileName, lpNewFileName, lpProgressRoutine, lpData, dwFlags, hTransaction);

	if(result){
		sprintf(msg, "MoveFileTransactedW 성공");
		strcpy(buf, "MoveFileTransactedW 성공");
		
	}else{
		strcpy(msg, GetErrorMessage("MoveFileTransactedW 실패 : ", GetLastError()));
		strcpy(buf, "MoveFileTransactedW 실패");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "MoveFileTransactedW 성공", msg);

	CloseHandle(hTransaction);

	
	if(!DeleteFileW(lpExistingFileName)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
		#endif
	}

	return result;
}

/**
* BOOL MoveFileTransactedA(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine, 
LPVOID lpData, DWORD dwFlags, HANDLE hTransaction)
* 자식을 포함하여 기존 파일이나 디렉토리를 트랜잭션 연산으로 이동한다. 권장되지 않음.
* @author : 손찬영  
*
* @param  lpExistingFileName 로컬 컴퓨터에있는 기존 파일 또는 디렉터리의 현재 이름
* @param  lpNewFileName 파일 또는 디렉토리의 새 이름
* @param  lpProgressRoutine 파일의 다른 부분이 이동 될 때마다 호출 되는 CopyProgressRoutine 콜백 함수에 대한 포인터
* @param  lpData CopyProgressRoutine 콜백 함수에 전달할 인수
* @param  dwFlags 이동 옵션
* @param  hTransaction 트랜잭션 핸들
* @return 성공/실패여부
*/
BOOL test_MoveFileTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCSTR            lpExistingFileName = "손찬영\\test_MoveFileTransactedW.txt";
	LPCSTR            lpNewFileName = "손찬영\\test_MoveFileTransactedW_moved.txt";
	LPPROGRESS_ROUTINE lpProgressRoutine = NULL;
	LPVOID             lpData = NULL;
	DWORD              dwFlags = MOVEFILE_COPY_ALLOWED;
	HANDLE  hTransaction, hFile;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hTransaction = MyCreateTransaction())){
		return FALSE;
	}
	if(!(hFile = MyCreateFileA(lpExistingFileName))){
		return FALSE;
	}
	if(!CloseHandle(hFile)){
		strcpy(msg, GetErrorMessage("CloseHandle 실패 : ", GetLastError()));
		strcpy(buf, "CloseHandle 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CloseHandle 성공", msg);
		
		return FALSE;
	}

	result = MoveFileTransactedA(lpExistingFileName, lpNewFileName, lpProgressRoutine, lpData, dwFlags, hTransaction);

	if(result){
		sprintf(msg, "MoveFileTransactedW 성공");
		strcpy(buf, "MoveFileTransactedW 성공");
		
	}else{
		strcpy(msg, GetErrorMessage("MoveFileTransactedW 실패 : ", GetLastError()));
		strcpy(buf, "MoveFileTransactedW 실패");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "MoveFileTransactedW 성공", msg);

	CloseHandle(hTransaction);

	
	if(!DeleteFileA(lpExistingFileName)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileA 실패 : ", GetLastError()));
		#endif
	}

	return result;
}

/**
* BOOL CopyFileTransactedW(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine, 
LPVOID lpData, LPBOOL pbCancel, DWORD dwCopyFlags, HANDLE hTransaction)
* 기존 파일을 트랜잭션 처리로 새 파일에 복사하여 콜백 함수를 통해 진행 상황을 응용 프로그램에 알린다. 권장하지 않음.
* @author : 손찬영  
*
* @param  lpExistingFileName 기존 파일의 이름
* @param  lpNewFileName 새 파일 이름
* @param  lpProgressRoutine 파일의 다른 부분이 복사 될 때마다 호출되는 LPPROGRESS_ROUTINE 유형의 콜백 함수의 포인터
* @param  lpData CopyProgressRoutine 콜백 함수에 전달할 인수
* @param  pbCancel 복사 작업 중에 이 플래그를 TRUE 로 설정 하면 작업이 취소
* @param  dwCopyFlags 파일을 복사하는 방법을 지정하는 플래그
* @param  hTransaction 트랜잭션 핸들
* @return 성공/실패여부
*/
BOOL test_CopyFileTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCTSTR            lpExistingFileName = L"손찬영\\test_CopyFileTransactedW.txt";
	LPCTSTR            lpNewFileName = L"손찬영\\test_CopyFileTransactedW_copied.txt";
	LPPROGRESS_ROUTINE lpProgressRoutine = NULL;
	LPVOID             lpData = NULL;
	LPBOOL             pbCancel = NULL;
	DWORD              dwCopyFlags = COPY_FILE_OPEN_SOURCE_FOR_WRITE;
	HANDLE  hTransaction, hFile;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hTransaction = MyCreateTransaction())){
		return FALSE;
	}
	if(!(hFile = MyCreateFile(lpExistingFileName))){
		return FALSE;
	}
	if(!CloseHandle(hFile)){
		strcpy(msg, GetErrorMessage("CloseHandle 실패 : ", GetLastError()));
		strcpy(buf, "CloseHandle 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CloseHandle 성공", msg);
		
		return FALSE;
	}

	result = CopyFileTransactedW(lpExistingFileName, lpNewFileName, lpProgressRoutine, lpData, pbCancel, dwCopyFlags, hTransaction);

	if(result){
		sprintf(msg, "CopyFileTransactedW 성공");
		strcpy(buf, "CopyFileTransactedW 성공");
		
	}else{
		strcpy(msg, GetErrorMessage("CopyFileTransactedW 실패 : ", GetLastError()));
		strcpy(buf, "CopyFileTransactedW 실패");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CopyFileTransactedW 성공", msg);

	CloseHandle(hTransaction);
	
	
	if(!DeleteFileW(lpExistingFileName)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileA 실패 : ", GetLastError()));
		#endif
	}
	return result;
}

/**
* BOOL CopyFileTransactedA(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine, 
LPVOID lpData, LPBOOL pbCancel, DWORD dwCopyFlags, HANDLE hTransaction)
* 기존 파일을 트랜잭션 처리로 새 파일에 복사하여 콜백 함수를 통해 진행 상황을 응용 프로그램에 알린다. 권장하지 않음.
* @author : 손찬영  
*
* @param  lpExistingFileName 기존 파일의 이름
* @param  lpNewFileName 새 파일 이름
* @param  lpProgressRoutine 파일의 다른 부분이 복사 될 때마다 호출되는 LPPROGRESS_ROUTINE 유형의 콜백 함수의 포인터
* @param  lpData CopyProgressRoutine 콜백 함수에 전달할 인수
* @param  pbCancel 복사 작업 중에 이 플래그를 TRUE 로 설정 하면 작업이 취소
* @param  dwCopyFlags 파일을 복사하는 방법을 지정하는 플래그
* @param  hTransaction 트랜잭션 핸들
* @return 성공/실패여부
*/
BOOL test_CopyFileTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCSTR            lpExistingFileName = "손찬영\\test_CopyFileTransactedA.txt";
	LPCSTR            lpNewFileName = "손찬영\\test_CopyFileTransactedA_copied.txt";
	LPPROGRESS_ROUTINE lpProgressRoutine = NULL;
	LPVOID             lpData = NULL;
	LPBOOL             pbCancel = NULL;
	DWORD              dwCopyFlags = COPY_FILE_OPEN_SOURCE_FOR_WRITE;
	HANDLE  hTransaction, hFile;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hTransaction = MyCreateTransaction())){
		return FALSE;
	}
	if(!(hFile = MyCreateFileA(lpExistingFileName))){
		return FALSE;
	}
	if(!CloseHandle(hFile)){
		strcpy(msg, GetErrorMessage("CloseHandle 실패 : ", GetLastError()));
		strcpy(buf, "CloseHandle 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CloseHandle 성공", msg);
		
		return FALSE;
	}

	result = CopyFileTransactedA(lpExistingFileName, lpNewFileName, lpProgressRoutine, lpData, pbCancel, dwCopyFlags, hTransaction);

	if(result){
		sprintf(msg, "CopyFileTransactedA 성공");
		strcpy(buf, "CopyFileTransactedA 성공");
		
	}else{
		strcpy(msg, GetErrorMessage("CopyFileTransactedA 실패 : ", GetLastError()));
		strcpy(buf, "CopyFileTransactedA 실패");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CopyFileTransactedA 성공", msg);

	CloseHandle(hTransaction);
	
	
	if(!DeleteFileA(lpExistingFileName)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileA 실패 : ", GetLastError()));
		#endif
	}

	return result;
}

/**
* BOOL DeleteFileTransactedW(LPCTSTR lpFileName, HANDLE hTransaction)
* 트랜잭션 된 작업으로 기존 파일을 삭제한다. 권장하지 않음.
* @author : 손찬영  
*
* @param  lpFileName 삭제할 파일의 이름
* @param  hTransaction 트랜잭션 핸들
* @return 성공/실패여부
*/
BOOL test_DeleteFileTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCTSTR lpExistingFileName = L"손찬영\\test_DeleteFileTransactedW.txt";
	HANDLE  hTransaction, hFile;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hTransaction = MyCreateTransaction())){
		return FALSE;
	}
	if(!(hFile = MyCreateFile(lpExistingFileName))){
		return FALSE;
	}
	if(!CloseHandle(hFile)){
		strcpy(msg, GetErrorMessage("CloseHandle 실패 : ", GetLastError()));
		strcpy(buf, "CloseHandle 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CloseHandle 성공", msg);
		
		return FALSE;
	}

	result = DeleteFileTransactedW(lpExistingFileName, hTransaction);

	if(result){
		sprintf(msg, "DeleteFileTransactedW 성공");
		strcpy(buf, "DeleteFileTransactedW 성공");
		
	}else{
		strcpy(msg, GetErrorMessage("DeleteFileTransactedW 실패 : ", GetLastError()));
		strcpy(buf, "DeleteFileTransactedW 실패");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "DeleteFileTransactedW 성공", msg);

	CloseHandle(hTransaction);

	if(!DeleteFileW(lpExistingFileName)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
		#endif
	}

	return result;
}

/**
* BOOL DeleteFileTransactedA(LPCTSTR lpFileName, HANDLE hTransaction)
* 트랜잭션 된 작업으로 기존 파일을 삭제한다. 권장하지 않음.
* @author : 손찬영  
*
* @param  lpFileName 삭제할 파일의 이름
* @param  hTransaction 트랜잭션 핸들
* @return 성공/실패여부
*/
BOOL test_DeleteFileTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCSTR lpExistingFileName = "손찬영\\test_DeleteFileTransactedW.txt";
	HANDLE  hTransaction, hFile;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hTransaction = MyCreateTransaction())){
		return FALSE;
	}
	if(!(hFile = MyCreateFileA(lpExistingFileName))){
		return FALSE;
	}
	if(!CloseHandle(hFile)){
		strcpy(msg, GetErrorMessage("CloseHandle 실패 : ", GetLastError()));
		strcpy(buf, "CloseHandle 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CloseHandle 성공", msg);
		
		return FALSE;
	}

	result = DeleteFileTransactedA(lpExistingFileName, hTransaction);

	if(result){
		sprintf(msg, "DeleteFileTransactedW 성공");
		strcpy(buf, "DeleteFileTransactedW 성공");
		
	}else{
		strcpy(msg, GetErrorMessage("DeleteFileTransactedW 실패 : ", GetLastError()));
		strcpy(buf, "DeleteFileTransactedW 실패");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "DeleteFileTransactedW 성공", msg);

	CloseHandle(hTransaction);

	if(!DeleteFileA(lpExistingFileName)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
		#endif
	}

	return result;
}

/**
* HANDLE CreateFileTransactedW(LPCTSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, 
LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile,
HANDLE hTransaction, PUSHORT pusMiniVersion, PVOID pExtendedParameter)
* 파일, 파일 스트림 또는 디렉토리를 트랜잭션 작업으로 생성하거나 연다. 이 함수는 객체에 액세스하는데 사용할 수있는 핸들을 반환한다. 권장하지 않음.
* @author : 손찬영  
*
* @param  lpFileName 쓰거나 열 파일 이름
* @param  dwDesiredAccess 읽기, 쓰기, 둘 다 또는 둘 다 (0)로 요약 할 수있는 객체에 대한 액세스권한
* @param  dwShareMode 객체의 공유 모드. 읽기, 쓰기, 둘 다, 삭제, 모두 또는 없음
* @param  lpSecurityAttributes SECURITY_ATTRIBUTES 구조체에 대한 포인터
* @param  dwCreationDisposition 존재하고 존재하지 않는 파일을 취하는 작업
* @param  dwFlagsAndAttributes 파일 속성 및 플래그 FILE_ATTRIBUTE_NORMAL 이 가장 일반적인 기본값
* @param  hTemplateFile GENERIC_READ 액세스 권한 이있는 템플리트 파일에 대한 유효한 핸들
* @param  hTransaction 트랜잭션 핸들
* @param  pusMiniVersion 미니 버전이 열린다
* @param  pExtendedParameter 예약
* @return 성공 시 핸들 리턴, 실패 시 INVALID_HANDLE_VALUE 
*/
BOOL test_CreateFileTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCWSTR lpFileName = L"손찬영\\test_CreateFileTransactedW.txt";
	HANDLE  hTransaction, hFile;
	PUSHORT pusMiniVersion = NULL;
	PVOID pExtendedParameter = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hTransaction = MyCreateTransaction())){
		return FALSE;
	}
	

	hFile = CreateFileTransactedW(lpFileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL, hTransaction, pusMiniVersion, pExtendedParameter);

	if(INVALID_HANDLE_VALUE != hFile){ //파일 열기 실패
		sprintf(msg, "CreateFileTransactedW 성공");
		strcpy(buf, "CreateFileTransactedW 성공");

	}else{
		strcpy(msg, GetErrorMessage("CreateFileTransactedW 실패 : ", GetLastError()));
		strcpy(buf, "CreateFileTransactedW 실패");
		
		result = FALSE;
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateFileTransactedW 성공", msg);

	CloseHandle(hTransaction);

	if(!DeleteFileW(lpFileName)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
		#endif
	}

	return result;

}


/**
* HANDLE CreateFileTransactedA(LPCTSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, 
LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile,
HANDLE hTransaction, PUSHORT pusMiniVersion, PVOID pExtendedParameter)
* 파일, 파일 스트림 또는 디렉토리를 트랜잭션 작업으로 생성하거나 연다. 이 함수는 객체에 액세스하는데 사용할 수있는 핸들을 반환한다. 권장하지 않음.
* @author : 손찬영  
*
* @param  lpFileName 쓰거나 열 파일 이름
* @param  dwDesiredAccess 읽기, 쓰기, 둘 다 또는 둘 다 (0)로 요약 할 수있는 객체에 대한 액세스권한
* @param  dwShareMode 객체의 공유 모드. 읽기, 쓰기, 둘 다, 삭제, 모두 또는 없음
* @param  lpSecurityAttributes SECURITY_ATTRIBUTES 구조체에 대한 포인터
* @param  dwCreationDisposition 존재하고 존재하지 않는 파일을 취하는 작업
* @param  dwFlagsAndAttributes 파일 속성 및 플래그 FILE_ATTRIBUTE_NORMAL 이 가장 일반적인 기본값
* @param  hTemplateFile GENERIC_READ 액세스 권한 이있는 템플리트 파일에 대한 유효한 핸들
* @param  hTransaction 트랜잭션 핸들
* @param  pusMiniVersion 미니 버전이 열린다
* @param  pExtendedParameter 예약
* @return 성공 시 핸들 리턴, 실패 시 INVALID_HANDLE_VALUE 
*/
BOOL test_CreateFileTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCSTR lpFileName = "손찬영\\test_CreateFileTransactedA.txt";
	HANDLE  hTransaction, hFile;
	PUSHORT pusMiniVersion = NULL;
	PVOID pExtendedParameter = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hTransaction = MyCreateTransaction())){
		return FALSE;
	}
	

	hFile = CreateFileTransactedA(lpFileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL, hTransaction, pusMiniVersion, pExtendedParameter);

	if(INVALID_HANDLE_VALUE != hFile){ //파일 열기 실패
		sprintf(msg, "CreateFileTransactedA 성공");
		strcpy(buf, "CreateFileTransactedA 성공");

	}else{
		strcpy(msg, GetErrorMessage("CreateFileTransactedA 실패 : ", GetLastError()));
		strcpy(buf, "CreateFileTransactedA 실패");
		
		result = FALSE;
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateFileTransactedA 성공", msg);

	CloseHandle(hTransaction);

	if(!DeleteFileA(lpFileName)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileA 실패 : ", GetLastError()));
		#endif
	}

	return result;
}


/**
* BOOL WriteFileGather(HANDLE hFile, FILE_SEGMENT_ELEMENT aSegmentArray[], DWORD nNumberOfBytesToWrite, 
LPDWORD lpReserved, LPOVERLAPPED lpOverlapped)
* 버퍼 배열에서 데이터를 검색하고 데이터를 파일에 쓴다. 비동기 동작.
* @author : 손찬영  
*
* @param  hFile 파일 핸들
* @param  aSegmentArray 데이터를 포함하는 FILE_SEGMENT_ELEMENT 버퍼 의 배열에 대한 포인터
* @param  nNumberOfBytesToWrite 기록 할 총 바이트 수
* @param  lpReserved 예약
* @param  lpOverlapped OVERLAPPED 데이터 구조에 대한 포인터
* @return 성공/실패 여부
*/
BOOL test_WriteFileGather()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode = 0;

	const unsigned int PAGE_NUM = 512;
	HANDLE hFile = NULL;
	LPCTSTR lpFileName = L"손찬영\\test_WriteFileGather.txt";
	FILE_SEGMENT_ELEMENT SegElement[PAGE_NUM + 1];
	BYTE * BufList[PAGE_NUM];
	OVERLAPPED         ov = {0};
	BYTE * BaseAddress;
	BOOL ovResult = FALSE;
	

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif
	
	/* 쓸 데이터의 준비 */
	BaseAddress = (BYTE *)VirtualAlloc (NULL, PAGE_NUM * sizeof(BYTE), MEM_COMMIT, PAGE_READWRITE);
	for (int i = 0; i <PAGE_NUM; i ++) {
		BufList [i] = BaseAddress + sizeof(BYTE) * i;
		FillMemory (BufList [i], sizeof(BYTE), i % 256);
	}

	/* 파일 만들기 */
	if(!(hFile = CreateFile (lpFileName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_ARCHIVE | FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING,	NULL))){

		sprintf(msg, GetErrorMessage("CreateFile 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile 성공", msg);

		return FALSE;
	}

	/* WriteFileGather 에 입력 정보의 초기화 */
	for (int i = 0; i <PAGE_NUM; i ++) SegElement[i].Buffer = (PVOID64)BufList[i];
	SegElement[PAGE_NUM].Alignment = (ULONGLONG) NULL;
	SegElement[PAGE_NUM].Buffer = (PVOID64) NULL;

	ov.Offset = 0;
	ov.OffsetHigh = 0;
	ov.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);

	/* 파일에 쓰기 */
	result = WriteFileGather (hFile, SegElement, 0, NULL, &ov);
	WaitForSingleObject (ov.hEvent, 3000);
	
	/* 성공/실패 판단 */
	if(result){ 
		sprintf(msg, "WriteFileGather 성공 : Overlapped.internal = %d", ov.Internal);
		strcpy(buf, "WriteFileGather 성공");

	}else{
		errorCode = GetLastError();

		if(ERROR_IO_PENDING == errorCode){ //I/O작업이 완료되지 않음

			for(int i=0; i<512; i++){
				ovResult = HasOverlappedIoCompleted(&ov);

				if(ovResult){ //I/O completed..
					sprintf(msg, "WriteFileGather 성공");
					strcpy(buf, "WriteFileGather 성공");

					break;
				}
			}
			if(!ovResult){ // I/O Completed를 기다렸으나 완료되지 않는 경우
				strcpy(msg, GetErrorMessage("WriteFileGather 실패 : ", GetLastError()));
				strcpy(buf, "WriteFileGather 실패");

				result = FALSE;
			}
		}else{ //그 밖의 이유로 실패
			strcpy(msg, GetErrorMessage("WriteFileGather 실패 : ", GetLastError()));
			strcpy(buf, "WriteFileGather 실패");

			result = FALSE;
		}
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "WriteFileGather 성공", msg);

	CloseHandle(hFile);
	VirtualFree (BaseAddress, 0, MEM_RELEASE);
	CloseHandle (ov.hEvent);

	if(!DeleteFileW(lpFileName)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
		#endif
	}

	return result;
}