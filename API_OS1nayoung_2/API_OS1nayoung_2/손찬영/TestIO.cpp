#include "TestIO.h"


/**
* BOOL CancelIo(HANDLE hFile)
* 파일 핸들에 대해 보류중인 모든 I/O 작업을 취소한다.
* @author : 손찬영  
*
* @param  hFile 파일 핸들
* @return 성공/실패여부
*/
BOOL test_CancelIo(void)
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hFile = NULL;
	LPCWSTR fileName = L"손찬영\\test_CancelIo.txt";
	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == INVALID_HANDLE_VALUE){ //파일 열기 실패
		sprintf(msg, GetErrorMessage("CreateFile 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile 성공", msg);

		return FALSE;
	}

	if(result = CancelIo(hFile)){
		strcpy(msg, "CancelIo 성공");
		strcpy(buf, "CancelIo 성공");

	}else{
		strcpy(msg, GetErrorMessage("CancelIo 실패 : ", GetLastError()));
		strcpy(buf, "CancelIo 실패");
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CancelIo 성공", msg);


	if(!CloseHandle(hFile)){
		#ifdef OQADBGPRINT
		printf(GetErrorMessage("CloseHandle 실패 : ", GetLastError()));
		#endif
	}
	if(!DeleteFileW(fileName)){
		#ifdef OQADBGPRINT
		printf(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
		#endif
	}

	return result;
}


/**
* BOOL CancelIoEx(HANDLE hFile, LPOVERLAPPED lpOverlapped)
* 파일 핸들에 대해 현재 프로세스의 I/O 작업만 취소한다.
* @author : 손찬영  
*
* @param  hFile 파일 핸들
* @param  lpOverlapped 비동기 I / O에 사용되는 데이터가 포함 된 OVERLAPPED 데이터 구조에 대한 포인터
* @return 성공/실패여부
*/
BOOL test_CancelIoEx()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;

	HANDLE hFile = NULL;
	LPCWSTR fileName = L"손찬영\\test_CancelIoEx.txt";
	OVERLAPPED Overlapped;
	LPOVERLAPPED lpOverlapped = NULL;

	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == INVALID_HANDLE_VALUE){ //파일 열기 실패
		sprintf(msg, GetErrorMessage("CreateFile 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile 성공", msg);

		return FALSE;
	}

	Overlapped.hEvent = NULL;
	Overlapped.Internal = 0;
	Overlapped.InternalHigh = 0;
	Overlapped.Offset = 0;
	Overlapped.OffsetHigh = 0;
	Overlapped.Pointer = NULL;
	
	if(result = CancelIoEx(hFile, lpOverlapped)){
		strcpy(msg, "CancelIoEx 성공");
		strcpy(buf, "CancelIoEx 성공");

	}else{
		if((errorCode = GetLastError()) == ERROR_NOT_FOUND){
			strcpy(msg, GetErrorMessage("CancelIoEx 성공 : ", errorCode));
			strcat(msg, "\n취소요청이 없는 경우는 성공으로 판단함");
			strcpy(buf, "CancelIoEx 성공");
		}else{
			strcpy(msg, GetErrorMessage("CancelIoEx 실패 : ", errorCode));
			strcpy(buf, "CancelIoEx 실패");
			result = FALSE;
		}

		printf("errorCode = %d\n", errorCode);
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CancelIoEx 성공", msg);


	if(!CloseHandle(hFile)){
		#ifdef OQADBGPRINT
		printf(GetErrorMessage("CloseHandle 실패 : ", GetLastError()));
		#endif
	}
	if(!DeleteFileW(fileName)){
		#ifdef OQADBGPRINT
		printf(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
		#endif
	}

	return result;
}


/**
* BOOL GetQueuedCompletionStatusEx(HANDLE CompletionPort, LPOVERLAPPED_ENTRY lpCompletionPortEntries, 
						ULONG ulCount, PULONG ulNumEntriesRemoved, DWORD dwMilliseconds,BOOL fAlertable)
* 여러 완료 포트 항목을 동시에 검색한다.
* @author : 손찬영  
*
* @param  CompletionPort CompletionPort 핸들
* @param  lpCompletionPortEntries OVERLAPPED_ENTRY 구조체의 배열
* @param  ulCount 제거 할 항목의 최대 수
* @param  ulNumEntriesRemoved 실제로 제거된 항목의 수를 받는 변수에 대한 포인터
* @param  dwMilliseconds 완료 패킷이 완료 포트에 표시 될 때까지 호출자가 기꺼이 기다리는 시간 (밀리 초)
* @param  fAlertable 이 매개 변수가 FALSE 이면 제한 시간이 경과하거나 항목을 검색 할 때까지 함수가 반환되지 않음
* @return 성공/실패여부
*/
BOOL test_GetQueuedCompletionStatusEx()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode = 0;

	LPCWSTR fileName = L"손찬영\\test_GetQueuedCompletionStatusEx.txt";
	HANDLE hCompletionPort = NULL, hFile = NULL;
	OVERLAPPED_ENTRY CompletionPortEntries;
	ULONG ulCount = 5;
	ULONG ulNumEntriesRemoved;
	DWORD dwMilliseconds = 10;


	//hCompletionPort = CreateIoCompletionPort(hFile, NULL, CompletionKey,  NumberOfConcurrentThreads);
	hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, NULL);

	if(NULL == hCompletionPort){
		strcpy(msg, "CreateIoCompletionPort 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateIoCompletionPort 성공", msg);

		return FALSE;
	}


	CompletionPortEntries.dwNumberOfBytesTransferred = 0;
	ulNumEntriesRemoved = 0;

	result = GetQueuedCompletionStatusEx(hCompletionPort, &CompletionPortEntries, ulCount, &ulNumEntriesRemoved, dwMilliseconds, FALSE);

	if((errorCode = GetLastError()) == ERROR_ABANDONED_WAIT_0){
		strcpy(msg, GetErrorMessage("GetQueuedCompletionStatusEx 실패 : ", errorCode));
		strcpy(buf, "GetQueuedCompletionStatusEx 실패");
		result = FALSE;

	}else{
		sprintf(msg, "GetQueuedCompletionStatusEx 성공 : ulNumEntriesRemoved = %u", ulNumEntriesRemoved);
		strcpy(buf, "GetQueuedCompletionStatusEx 성공");
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetQueuedCompletionStatusEx 성공", msg);

	CloseHandle(hCompletionPort);

	return result;
}


/**
* BOOL CancelSynchronousIo(HANDLE hThread)
* 지정된 스레드가 발행 한 보류중인 동기 I/O 작업을 취소 된 것으로 표시한다.
* @author : 손찬영  
*
* @param  hThread 쓰레드 핸들
* @return 성공/실패여부
*/
BOOL test_CancelSynchronousIo()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode = 0;

	HANDLE hThread = NULL;
	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());

	if(result = CancelSynchronousIo(hThread)){
		strcpy(msg, "CancelSynchronousIo 성공");
		strcpy(buf, msg);

	}else{
		if((errorCode = GetLastError()) == ERROR_NOT_FOUND){
			strcpy(msg, GetErrorMessage("CancelSynchronousIo 성공 : ", errorCode));
			strcat(msg, "\n취소요청이 없는 경우는 성공으로 판단함");
			strcpy(buf, "CancelSynchronousIo 성공");
		}else{
			strcpy(msg, GetErrorMessage("CancelSynchronousIo 실패 : ", errorCode));
			strcpy(buf, "CancelSynchronousIo 실패");
			result = FALSE;
		}

		printf("errorCode = %d\n", errorCode);
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CancelSynchronousIo 성공", msg);

	if(!CloseHandle(hThread)){
		#ifdef OQADBGPRINT
		printf(GetErrorMessage("CloseHandle 실패 : ", GetLastError()));
		#endif
	}

	return result;
}