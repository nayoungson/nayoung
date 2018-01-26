#include "TestSRWLock.h"

unsigned long long sharedResource = 0; //���� �����忡�� ���ÿ� ������ �� �ִ� �ڿ�
const unsigned long long expectNum = 1200000LL;
int sharedFlag = 0; //�ֱٿ� � �����尡 ����Ǿ����� Ȯ��


/**
* VOID InitializeSRWLock(PSRWLOCK SRWLock)
* Slim Reader/Writer Lock�� �ʱ�ȭ�Ѵ�.
* @author : ������  
*
* @param  SRWLock SRW lock�� ������
* @return ����
*/
BOOL test_InitializeSRWLock()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];

	SRWLOCK SRWLock = SRWLOCK_INIT;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif
	

	SRWLock.Ptr = "test_InitializeSRWLock";
	InitializeSRWLock(&SRWLock);

	if(SRWLock.Ptr == NULL){
		strcpy(msg, "InitializeSRWLock ����");

	}else{
		strcpy(msg, "InitializeSRWLock ����");
		result = FALSE;
	}
	
	wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "InitializeSRWLock ����", msg);

	return result;
}


/**
* VOID AcquireSRWLockShared(PSRWLOCK SRWLock)
* ���� ��忡�� ������ ���� / ������ (SRW) ����� ȹ���Ѵ�.
* @author : ������  
*
* @param  SRWLock SRW lock�� ������
* @return ����
*/
BOOL test_AcquireSRWLockShared()
{
	BOOL result = FALSE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	SRWLOCK SRWLock;
	PSRWLOCK pSRWLock = &SRWLock;

	HANDLE hThreadReader[THREAD_CNT];
	DWORD exitCode[THREAD_CNT] = {0, 0};
	DWORD ThreadID;
	enum {READER_1, READER_2};
	THREADSRWLOCK ret[THREAD_CNT];
	
	sharedFlag = READER_1;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	InitializeSRWLock(pSRWLock);

	ret[READER_1].pSRWLock = pSRWLock;
	ret[READER_1].threadNum = READER_1;
	ret[READER_1].data = -1;
	hThreadReader[READER_1] = CreateThread(NULL, 0, ThreadReader, &ret[READER_1], 0, &ThreadID);

	ret[READER_2].pSRWLock = pSRWLock;
	ret[READER_2].threadNum = READER_2;
	ret[READER_2].data = -1;
	hThreadReader[READER_2] = CreateThread(NULL, 0, ThreadReader2, &ret[READER_2], 0, &ThreadID);

	#ifdef OQADBGPRINT
	printf("%d��° ������ �ڵ鷯 = %d\n%d��° ������ �ڵ鷯 = %d\n", READER_1, hThreadReader[READER_1], READER_2, hThreadReader[READER_2]);
	#endif

	while(TRUE){ //��� ������ ������� busy waiting
		GetExitCodeThread(hThreadReader[READER_1], &exitCode[READER_1]);
		GetExitCodeThread(hThreadReader[READER_2], &exitCode[READER_2]);


		//READER_1�� �ݺ������� read�ϴµ���, READER_2�� ��ϵ��� �ʰ� ���� �� �ִ� lock������ Ȯ���Ѵ�.
		if((exitCode[READER_1] == STILL_ACTIVE) && (exitCode[READER_2] != STILL_ACTIVE)){ //READER_1�� ������� �ʰ�, READER_2�� ���� ����� ����

			result = TRUE;
		}
		if((exitCode[READER_1] != STILL_ACTIVE) && (exitCode[READER_2] != STILL_ACTIVE)){
			break;
		}
	}

	if(result){
		strcpy(buf, "AcquireSRWLockShared ����");
	}else{
		strcpy(buf, "AcquireSRWLockShared ����");
	}

	strcpy(msg, buf);
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "AcquireSRWLockShared ����", msg);
	
	CloseHandle(hThreadReader[READER_1]);
	CloseHandle(hThreadReader[READER_2]);
	
	return result;
}


/**
* VOID AcquireSRWLockExclusive(PSRWLOCK SRWLock)
* �ܵ� ��忡�� ������ ���� / ������ (SRW) ����� ȹ���Ѵ�.
* @author : ������  
*
* @param  SRWLock SRW lock�� ������
* @return ����
*/
BOOL test_AcquireSRWLockExclusive()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	SRWLOCK SRWLock;
	PSRWLOCK pSRWLock = &SRWLock;

	HANDLE hThreadWriter[THREAD_CNT];
	DWORD exitCode[THREAD_CNT] = {0, 0};
	DWORD ThreadID;
	enum {WRITER_1, WRITER_2};
	THREADSRWLOCK ret[THREAD_CNT];
	
	sharedResource = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	InitializeSRWLock(pSRWLock);

	ret[WRITER_1].pSRWLock = pSRWLock;
	ret[WRITER_1].threadNum = WRITER_1;
	hThreadWriter[WRITER_1] = CreateThread(NULL, 0, ThreadWriter, &ret[WRITER_1], 0, &ThreadID);

	ret[WRITER_2].pSRWLock = pSRWLock;
	ret[WRITER_2].threadNum = WRITER_2;
	hThreadWriter[WRITER_2] = CreateThread(NULL, 0, ThreadWriter, &ret[WRITER_2], 0, &ThreadID); //2���� Wirter ������ ����

	#ifdef OQADBGPRINT
	printf("%d��° ������ �ڵ鷯 = %d\n%d��° ������ �ڵ鷯 = %d\n", WRITER_1, hThreadWriter[WRITER_1], WRITER_2, hThreadWriter[WRITER_2]);
	#endif

	while(TRUE){ //��� ������ ������� busy waiting
		for(int i=0; i<THREAD_CNT; i++){
			GetExitCodeThread(hThreadWriter[i], &exitCode[i]);
		}

		if((exitCode[0] != STILL_ACTIVE) && (exitCode[1] != STILL_ACTIVE)){
			break;
		}
	}
	
	sprintf(msg, "����Ǿ�� �ϴ� �� = %lld\nsharedResource = %lld\n", expectNum * THREAD_CNT, sharedResource);
	if(sharedResource == expectNum * THREAD_CNT){
		strcpy(buf, "AcquireSRWLockExclusive ����");
		
	}else{
		strcpy(buf, "AcquireSRWLockExclusive ����");
		result = FALSE;
		
	}

	strcat(msg, buf);
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "AcquireSRWLockExclusive ����", msg);
	
	CloseHandle(hThreadWriter[WRITER_1]);
	CloseHandle(hThreadWriter[WRITER_2]);

	return result;
}


/**
* VOID ReleaseSRWLockShared(PSRWLOCK SRWLock)
* ���� ��忡�� ȹ�� �� ������ ���� / ������ (SRW) ����� �����Ѵ�.
* @author : ������  
*
* @param  SRWLock SRW lock�� ������
* @return ����
*/
BOOL test_ReleaseSRWLockShared()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	SRWLOCK SRWLock;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	InitializeSRWLock(&SRWLock);
	AcquireSRWLockShared(&SRWLock);
	ReleaseSRWLockShared(&SRWLock);

	strcpy(buf, "ReleaseSRWLockShared ����");
	strcpy(msg, buf);
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ReleaseSRWLockShared ����", msg);

	return result;
}


/**
* VOID ReleaseSRWLockExclusive(PSRWLOCK SRWLock)
* �ܵ� ��忡�� ȹ�� �� ������ ���� / ������ (SRW) ����� �����Ѵ�.
* @author : ������  
*
* @param  SRWLock SRW lock�� ������
* @return ����
*/
BOOL test_ReleaseSRWLockExclusive()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	SRWLOCK SRWLock;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	InitializeSRWLock(&SRWLock);
	AcquireSRWLockExclusive(&SRWLock);
	ReleaseSRWLockExclusive(&SRWLock);

	strcpy(buf, "ReleaseSRWLockExclusive ����");
	strcpy(msg, buf);
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ReleaseSRWLockExclusive ����", msg);

	return result;
}


/**
* VOID TryAcquireSRWLockShared(PSRWLOCK SRWLock)
* ���� ��忡�� ���� ����/������ (SRW) ����� ȹ�� �õ��Ѵ�.
* @author : ������  
*
* @param  SRWLock SRW lock�� ������
* @return ����
*/
BOOL test_TryAcquireSRWLockShared()
{
	BOOL result = FALSE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	SRWLOCK SRWLock;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	Sleep(1000);
	InitializeSRWLock(&SRWLock);
	result = TryAcquireSRWLockShared(&SRWLock);

	if(result){ 
		strcpy(buf, "TryAcquireSRWLockShared ����");
	}else{
		strcpy(buf, "TryAcquireSRWLockShared ����");
	}
	strcpy(msg, buf);
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "TryAcquireSRWLockShared ����", msg);

	return result;
}

/**
* VOID TryAcquireSRWLockShared(PSRWLOCK SRWLock)
* �ܵ� ��忡�� ���� ����/������ (SRW) ����� ȹ�� �õ��Ѵ�.
* @author : ������  
*
* @param  SRWLock SRW lock�� ������
* @return ����
*/
BOOL test_TryAcquireSRWLockExclusive()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	SRWLOCK SRWLock;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	result = TryAcquireSRWLockExclusive(&SRWLock);

	if(result){
		strcpy(buf, "TryAcquireSRWLockExclusive ����");
	}else{
		strcpy(buf, "TryAcquireSRWLockExclusive ����");
	}
	strcpy(msg, buf);
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "TryAcquireSRWLockExclusive ����", msg);

	return result;
}




DWORD WINAPI ThreadReader(LPVOID temp)
{
	THREADSRWLOCK *param;

	param = (THREADSRWLOCK *)temp;

	#ifdef OQADBGPRINT
	printf("ThreadReader ����\n");
	#endif

	AcquireSRWLockShared(param->pSRWLock);
	#ifdef OQADBGPRINT
	printf("ThreadReader, Lock ����\n");
	#endif
	
	for(int i=0; i<expectNum; i++){
		if((i%(expectNum/5)) == 0){
			#ifdef OQADBGPRINT
			printf("param->data = %d\n", param->data); //�ֱ������� Read
			#endif
		}
		param->data = sharedFlag + i; //����д´�. �����Ϸ��� �������� ���Ƿ� ����ȭ���� �ʵ��� volatile������ ����
	}
	ReleaseSRWLockShared(param->pSRWLock);
	#ifdef OQADBGPRINT
	printf("ThreadReader, Lock ����\n");
	#endif


	#ifdef OQADBGPRINT
	printf("%d��° ������ ��\n", param->threadNum);
	#endif

	
	return TRUE;
}

DWORD WINAPI ThreadReader2(LPVOID temp)
{
	THREADSRWLOCK *param;

	param = (THREADSRWLOCK *)temp;

	#ifdef OQADBGPRINT
	printf("ThreadReader2 ����\n");
	#endif

	AcquireSRWLockShared(param->pSRWLock);
	#ifdef OQADBGPRINT
	printf("ThreadReader2, Lock ����\n");
	#endif
	
	param->data = sharedFlag + 1; //READER_2
	
	ReleaseSRWLockShared(param->pSRWLock);
	#ifdef OQADBGPRINT
	printf("ThreadReader2, Lock ����\n");
	#endif


	#ifdef OQADBGPRINT
	printf("%d��° ������ ��\n", param->threadNum);
	#endif

	return TRUE;
}
//DWORD WINAPI ThreadWriter2(LPVOID temp)
//{
//	THREADSRWLOCK *param;
//
//	param = (THREADSRWLOCK *)temp;
//
//	#ifdef OQADBGPRINT
//	printf("ThreadWriter ����\n");
//	#endif
//
//	//Sleep(1000);
//	AcquireSRWLockShared(param->pSRWLock);
//
//	#ifdef OQADBGPRINT
//	printf("ThreadWriter2, Lock ����\n");
//	#endif
//	sharedFlag = 1;
//
//	ReleaseSRWLockShared(param->pSRWLock);
//	#ifdef OQADBGPRINT
//	printf("ThreadWriter2, Lock ����\n");
//	#endif
//
//
//	#ifdef OQADBGPRINT
//	printf("%d��° ������ ��\n", param->threadNum);
//	#endif
//	
//	return TRUE;
//}


DWORD WINAPI ThreadWriter(LPVOID temp)
{
	THREADSRWLOCK *param;

	param = (THREADSRWLOCK *)temp;

	#ifdef OQADBGPRINT
	printf("ThreadWriter ����\n");
	#endif

	#ifdef OQADBGPRINT
	printf("%d��° ������ ����\n", param->threadNum);
	#endif

	#ifdef OQADBGPRINT
	printf("[%d] : ���� ���� �� sharedResource = %lld\n", param->threadNum, sharedResource);
	#endif

	
	AcquireSRWLockExclusive(param->pSRWLock);

	for(int i=0;i<expectNum; i++){
		sharedResource = sharedResource+1;
		sharedFlag = 0;
	}
	ReleaseSRWLockExclusive(param->pSRWLock);
	

	#ifdef OQADBGPRINT
	printf("[%d] : ���� ���� �� sharedResource = %lld\n", param->threadNum, sharedResource);
	#endif

	#ifdef OQADBGPRINT
	printf("%d��° ������ ��\n", param->threadNum);
	#endif

	return TRUE;
}