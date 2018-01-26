#include "TestIO.h"


/**
* BOOL CancelIo(HANDLE hFile)
* ���� �ڵ鿡 ���� �������� ��� I/O �۾��� ����Ѵ�.
* @author : ������  
*
* @param  hFile ���� �ڵ�
* @return ����/���п���
*/
BOOL test_CancelIo(void)
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hFile = NULL;
	LPCWSTR fileName = L"������\\test_CancelIo.txt";
	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == INVALID_HANDLE_VALUE){ //���� ���� ����
		sprintf(msg, GetErrorMessage("CreateFile ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile ����", msg);

		return FALSE;
	}

	if(result = CancelIo(hFile)){
		strcpy(msg, "CancelIo ����");
		strcpy(buf, "CancelIo ����");

	}else{
		strcpy(msg, GetErrorMessage("CancelIo ���� : ", GetLastError()));
		strcpy(buf, "CancelIo ����");
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CancelIo ����", msg);


	if(!CloseHandle(hFile)){
		#ifdef OQADBGPRINT
		printf(GetErrorMessage("CloseHandle ���� : ", GetLastError()));
		#endif
	}
	if(!DeleteFileW(fileName)){
		#ifdef OQADBGPRINT
		printf(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
		#endif
	}

	return result;
}


/**
* BOOL CancelIoEx(HANDLE hFile, LPOVERLAPPED lpOverlapped)
* ���� �ڵ鿡 ���� ���� ���μ����� I/O �۾��� ����Ѵ�.
* @author : ������  
*
* @param  hFile ���� �ڵ�
* @param  lpOverlapped �񵿱� I / O�� ���Ǵ� �����Ͱ� ���� �� OVERLAPPED ������ ������ ���� ������
* @return ����/���п���
*/
BOOL test_CancelIoEx()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;

	HANDLE hFile = NULL;
	LPCWSTR fileName = L"������\\test_CancelIoEx.txt";
	OVERLAPPED Overlapped;
	LPOVERLAPPED lpOverlapped = NULL;

	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == INVALID_HANDLE_VALUE){ //���� ���� ����
		sprintf(msg, GetErrorMessage("CreateFile ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile ����", msg);

		return FALSE;
	}

	Overlapped.hEvent = NULL;
	Overlapped.Internal = 0;
	Overlapped.InternalHigh = 0;
	Overlapped.Offset = 0;
	Overlapped.OffsetHigh = 0;
	Overlapped.Pointer = NULL;
	
	if(result = CancelIoEx(hFile, lpOverlapped)){
		strcpy(msg, "CancelIoEx ����");
		strcpy(buf, "CancelIoEx ����");

	}else{
		if((errorCode = GetLastError()) == ERROR_NOT_FOUND){
			strcpy(msg, GetErrorMessage("CancelIoEx ���� : ", errorCode));
			strcat(msg, "\n��ҿ�û�� ���� ���� �������� �Ǵ���");
			strcpy(buf, "CancelIoEx ����");
		}else{
			strcpy(msg, GetErrorMessage("CancelIoEx ���� : ", errorCode));
			strcpy(buf, "CancelIoEx ����");
			result = FALSE;
		}

		printf("errorCode = %d\n", errorCode);
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CancelIoEx ����", msg);


	if(!CloseHandle(hFile)){
		#ifdef OQADBGPRINT
		printf(GetErrorMessage("CloseHandle ���� : ", GetLastError()));
		#endif
	}
	if(!DeleteFileW(fileName)){
		#ifdef OQADBGPRINT
		printf(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
		#endif
	}

	return result;
}


/**
* BOOL GetQueuedCompletionStatusEx(HANDLE CompletionPort, LPOVERLAPPED_ENTRY lpCompletionPortEntries, 
						ULONG ulCount, PULONG ulNumEntriesRemoved, DWORD dwMilliseconds,BOOL fAlertable)
* ���� �Ϸ� ��Ʈ �׸��� ���ÿ� �˻��Ѵ�.
* @author : ������  
*
* @param  CompletionPort CompletionPort �ڵ�
* @param  lpCompletionPortEntries OVERLAPPED_ENTRY ����ü�� �迭
* @param  ulCount ���� �� �׸��� �ִ� ��
* @param  ulNumEntriesRemoved ������ ���ŵ� �׸��� ���� �޴� ������ ���� ������
* @param  dwMilliseconds �Ϸ� ��Ŷ�� �Ϸ� ��Ʈ�� ǥ�� �� ������ ȣ���ڰ� �Ⲩ�� ��ٸ��� �ð� (�и� ��)
* @param  fAlertable �� �Ű� ������ FALSE �̸� ���� �ð��� ����ϰų� �׸��� �˻� �� ������ �Լ��� ��ȯ���� ����
* @return ����/���п���
*/
BOOL test_GetQueuedCompletionStatusEx()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode = 0;

	LPCWSTR fileName = L"������\\test_GetQueuedCompletionStatusEx.txt";
	HANDLE hCompletionPort = NULL, hFile = NULL;
	OVERLAPPED_ENTRY CompletionPortEntries;
	ULONG ulCount = 5;
	ULONG ulNumEntriesRemoved;
	DWORD dwMilliseconds = 10;


	//hCompletionPort = CreateIoCompletionPort(hFile, NULL, CompletionKey,  NumberOfConcurrentThreads);
	hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, NULL);

	if(NULL == hCompletionPort){
		strcpy(msg, "CreateIoCompletionPort ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateIoCompletionPort ����", msg);

		return FALSE;
	}


	CompletionPortEntries.dwNumberOfBytesTransferred = 0;
	ulNumEntriesRemoved = 0;

	result = GetQueuedCompletionStatusEx(hCompletionPort, &CompletionPortEntries, ulCount, &ulNumEntriesRemoved, dwMilliseconds, FALSE);

	if((errorCode = GetLastError()) == ERROR_ABANDONED_WAIT_0){
		strcpy(msg, GetErrorMessage("GetQueuedCompletionStatusEx ���� : ", errorCode));
		strcpy(buf, "GetQueuedCompletionStatusEx ����");
		result = FALSE;

	}else{
		sprintf(msg, "GetQueuedCompletionStatusEx ���� : ulNumEntriesRemoved = %u", ulNumEntriesRemoved);
		strcpy(buf, "GetQueuedCompletionStatusEx ����");
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetQueuedCompletionStatusEx ����", msg);

	CloseHandle(hCompletionPort);

	return result;
}


/**
* BOOL CancelSynchronousIo(HANDLE hThread)
* ������ �����尡 ���� �� �������� ���� I/O �۾��� ��� �� ������ ǥ���Ѵ�.
* @author : ������  
*
* @param  hThread ������ �ڵ�
* @return ����/���п���
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
		strcpy(msg, "CancelSynchronousIo ����");
		strcpy(buf, msg);

	}else{
		if((errorCode = GetLastError()) == ERROR_NOT_FOUND){
			strcpy(msg, GetErrorMessage("CancelSynchronousIo ���� : ", errorCode));
			strcat(msg, "\n��ҿ�û�� ���� ���� �������� �Ǵ���");
			strcpy(buf, "CancelSynchronousIo ����");
		}else{
			strcpy(msg, GetErrorMessage("CancelSynchronousIo ���� : ", errorCode));
			strcpy(buf, "CancelSynchronousIo ����");
			result = FALSE;
		}

		printf("errorCode = %d\n", errorCode);
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CancelSynchronousIo ����", msg);

	if(!CloseHandle(hThread)){
		#ifdef OQADBGPRINT
		printf(GetErrorMessage("CloseHandle ���� : ", GetLastError()));
		#endif
	}

	return result;
}