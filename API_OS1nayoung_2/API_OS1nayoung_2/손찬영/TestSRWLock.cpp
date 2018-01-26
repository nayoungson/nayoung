#include "TestSRWLock.h"

unsigned long long sharedResource = 0; //여러 쓰레드에서 동시에 접근할 수 있는 자원
const unsigned long long expectNum = 1200000LL;
int sharedFlag = 0; //최근에 어떤 스레드가 실행되었는지 확인


/**
* VOID InitializeSRWLock(PSRWLOCK SRWLock)
* Slim Reader/Writer Lock을 초기화한다.
* @author : 손찬영  
*
* @param  SRWLock SRW lock의 포인터
* @return 없음
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
		strcpy(msg, "InitializeSRWLock 성공");

	}else{
		strcpy(msg, "InitializeSRWLock 실패");
		result = FALSE;
	}
	
	wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "InitializeSRWLock 성공", msg);

	return result;
}


/**
* VOID AcquireSRWLockShared(PSRWLOCK SRWLock)
* 공유 모드에서 슬림형 리더 / 라이터 (SRW) 잠금을 획득한다.
* @author : 손찬영  
*
* @param  SRWLock SRW lock의 포인터
* @return 없음
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
	printf("%d번째 쓰레드 핸들러 = %d\n%d번째 쓰레드 핸들러 = %d\n", READER_1, hThreadReader[READER_1], READER_2, hThreadReader[READER_2]);
	#endif

	while(TRUE){ //모든 쓰레드 종료까지 busy waiting
		GetExitCodeThread(hThreadReader[READER_1], &exitCode[READER_1]);
		GetExitCodeThread(hThreadReader[READER_2], &exitCode[READER_2]);


		//READER_1이 반복적으로 read하는동안, READER_2가 블록되지 않고 끝낼 수 있는 lock인지를 확인한다.
		if((exitCode[READER_1] == STILL_ACTIVE) && (exitCode[READER_2] != STILL_ACTIVE)){ //READER_1은 종료되지 않고, READER_2가 먼저 종료된 상태

			result = TRUE;
		}
		if((exitCode[READER_1] != STILL_ACTIVE) && (exitCode[READER_2] != STILL_ACTIVE)){
			break;
		}
	}

	if(result){
		strcpy(buf, "AcquireSRWLockShared 성공");
	}else{
		strcpy(buf, "AcquireSRWLockShared 실패");
	}

	strcpy(msg, buf);
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "AcquireSRWLockShared 성공", msg);
	
	CloseHandle(hThreadReader[READER_1]);
	CloseHandle(hThreadReader[READER_2]);
	
	return result;
}


/**
* VOID AcquireSRWLockExclusive(PSRWLOCK SRWLock)
* 단독 모드에서 슬림형 리더 / 라이터 (SRW) 잠금을 획득한다.
* @author : 손찬영  
*
* @param  SRWLock SRW lock의 포인터
* @return 없음
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
	hThreadWriter[WRITER_2] = CreateThread(NULL, 0, ThreadWriter, &ret[WRITER_2], 0, &ThreadID); //2개의 Wirter 스레드 생성

	#ifdef OQADBGPRINT
	printf("%d번째 쓰레드 핸들러 = %d\n%d번째 쓰레드 핸들러 = %d\n", WRITER_1, hThreadWriter[WRITER_1], WRITER_2, hThreadWriter[WRITER_2]);
	#endif

	while(TRUE){ //모든 쓰레드 종료까지 busy waiting
		for(int i=0; i<THREAD_CNT; i++){
			GetExitCodeThread(hThreadWriter[i], &exitCode[i]);
		}

		if((exitCode[0] != STILL_ACTIVE) && (exitCode[1] != STILL_ACTIVE)){
			break;
		}
	}
	
	sprintf(msg, "연산되어야 하는 값 = %lld\nsharedResource = %lld\n", expectNum * THREAD_CNT, sharedResource);
	if(sharedResource == expectNum * THREAD_CNT){
		strcpy(buf, "AcquireSRWLockExclusive 성공");
		
	}else{
		strcpy(buf, "AcquireSRWLockExclusive 실패");
		result = FALSE;
		
	}

	strcat(msg, buf);
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "AcquireSRWLockExclusive 성공", msg);
	
	CloseHandle(hThreadWriter[WRITER_1]);
	CloseHandle(hThreadWriter[WRITER_2]);

	return result;
}


/**
* VOID ReleaseSRWLockShared(PSRWLOCK SRWLock)
* 공유 모드에서 획득 한 슬림형 리더 / 라이터 (SRW) 잠금을 해제한다.
* @author : 손찬영  
*
* @param  SRWLock SRW lock의 포인터
* @return 없음
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

	strcpy(buf, "ReleaseSRWLockShared 성공");
	strcpy(msg, buf);
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ReleaseSRWLockShared 성공", msg);

	return result;
}


/**
* VOID ReleaseSRWLockExclusive(PSRWLOCK SRWLock)
* 단독 모드에서 획득 한 슬림형 리더 / 라이터 (SRW) 잠금을 해제한다.
* @author : 손찬영  
*
* @param  SRWLock SRW lock의 포인터
* @return 없음
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

	strcpy(buf, "ReleaseSRWLockExclusive 성공");
	strcpy(msg, buf);
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ReleaseSRWLockExclusive 성공", msg);

	return result;
}


/**
* VOID TryAcquireSRWLockShared(PSRWLOCK SRWLock)
* 공유 모드에서 슬림 리더/라이터 (SRW) 잠금을 획득 시도한다.
* @author : 손찬영  
*
* @param  SRWLock SRW lock의 포인터
* @return 없음
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
		strcpy(buf, "TryAcquireSRWLockShared 성공");
	}else{
		strcpy(buf, "TryAcquireSRWLockShared 실패");
	}
	strcpy(msg, buf);
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "TryAcquireSRWLockShared 성공", msg);

	return result;
}

/**
* VOID TryAcquireSRWLockShared(PSRWLOCK SRWLock)
* 단독 모드에서 슬림 리더/라이터 (SRW) 잠금을 획득 시도한다.
* @author : 손찬영  
*
* @param  SRWLock SRW lock의 포인터
* @return 없음
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
		strcpy(buf, "TryAcquireSRWLockExclusive 성공");
	}else{
		strcpy(buf, "TryAcquireSRWLockExclusive 실패");
	}
	strcpy(msg, buf);
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "TryAcquireSRWLockExclusive 성공", msg);

	return result;
}




DWORD WINAPI ThreadReader(LPVOID temp)
{
	THREADSRWLOCK *param;

	param = (THREADSRWLOCK *)temp;

	#ifdef OQADBGPRINT
	printf("ThreadReader 진입\n");
	#endif

	AcquireSRWLockShared(param->pSRWLock);
	#ifdef OQADBGPRINT
	printf("ThreadReader, Lock 진입\n");
	#endif
	
	for(int i=0; i<expectNum; i++){
		if((i%(expectNum/5)) == 0){
			#ifdef OQADBGPRINT
			printf("param->data = %d\n", param->data); //주기적으로 Read
			#endif
		}
		param->data = sharedFlag + i; //계속읽는다. 컴파일러가 수정하지 임의로 최적화하지 않도록 volatile변수로 선언
	}
	ReleaseSRWLockShared(param->pSRWLock);
	#ifdef OQADBGPRINT
	printf("ThreadReader, Lock 종료\n");
	#endif


	#ifdef OQADBGPRINT
	printf("%d번째 쓰레드 끝\n", param->threadNum);
	#endif

	
	return TRUE;
}

DWORD WINAPI ThreadReader2(LPVOID temp)
{
	THREADSRWLOCK *param;

	param = (THREADSRWLOCK *)temp;

	#ifdef OQADBGPRINT
	printf("ThreadReader2 진입\n");
	#endif

	AcquireSRWLockShared(param->pSRWLock);
	#ifdef OQADBGPRINT
	printf("ThreadReader2, Lock 진입\n");
	#endif
	
	param->data = sharedFlag + 1; //READER_2
	
	ReleaseSRWLockShared(param->pSRWLock);
	#ifdef OQADBGPRINT
	printf("ThreadReader2, Lock 종료\n");
	#endif


	#ifdef OQADBGPRINT
	printf("%d번째 쓰레드 끝\n", param->threadNum);
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
//	printf("ThreadWriter 진입\n");
//	#endif
//
//	//Sleep(1000);
//	AcquireSRWLockShared(param->pSRWLock);
//
//	#ifdef OQADBGPRINT
//	printf("ThreadWriter2, Lock 진입\n");
//	#endif
//	sharedFlag = 1;
//
//	ReleaseSRWLockShared(param->pSRWLock);
//	#ifdef OQADBGPRINT
//	printf("ThreadWriter2, Lock 종료\n");
//	#endif
//
//
//	#ifdef OQADBGPRINT
//	printf("%d번째 쓰레드 끝\n", param->threadNum);
//	#endif
//	
//	return TRUE;
//}


DWORD WINAPI ThreadWriter(LPVOID temp)
{
	THREADSRWLOCK *param;

	param = (THREADSRWLOCK *)temp;

	#ifdef OQADBGPRINT
	printf("ThreadWriter 진입\n");
	#endif

	#ifdef OQADBGPRINT
	printf("%d번째 쓰레드 시작\n", param->threadNum);
	#endif

	#ifdef OQADBGPRINT
	printf("[%d] : 연산 시작 전 sharedResource = %lld\n", param->threadNum, sharedResource);
	#endif

	
	AcquireSRWLockExclusive(param->pSRWLock);

	for(int i=0;i<expectNum; i++){
		sharedResource = sharedResource+1;
		sharedFlag = 0;
	}
	ReleaseSRWLockExclusive(param->pSRWLock);
	

	#ifdef OQADBGPRINT
	printf("[%d] : 연산 종료 후 sharedResource = %lld\n", param->threadNum, sharedResource);
	#endif

	#ifdef OQADBGPRINT
	printf("%d번째 쓰레드 끝\n", param->threadNum);
	#endif

	return TRUE;
}