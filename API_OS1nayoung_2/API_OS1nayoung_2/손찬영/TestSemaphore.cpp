#include "TestSemaphore.h"

/**
* HANDLE WINAPI OpenSemaphore(
  _In_ DWORD   dwDesiredAccess,
  _In_ BOOL    bInheritHandle,
  _In_ LPCTSTR lpName
);
* 기존의 명명된 세마포어 개체를 연다.
* @author : 손찬영  
*
* @param  dwDesiredAccess semaphore 객체에 대한 액세스
* @param  bInheritHandle 이 값이 TRUE이면, 이 프로세스에서 생성된 프로세스가 핸들을 상속한다.
* @param  lpName 열리는 세마포어의 이름
* @return 성공하면 반환 값은 세마포어 객체의 핸들, 실패하면 NULL
*/
BOOL test_OpenSemaphoreW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hSemaphore = NULL, hSemaphoreCreate = NULL;
	LONG lInitialCount = 10, lMaximumCount = 10;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* Semaphore가 없는 상태로 open 시 실패해야 함 */
	if(OpenSemaphoreW(SEMAPHORE_ALL_ACCESS | SEMAPHORE_MODIFY_STATE, FALSE, L"test_OpenSemaphoreW")){
		sprintf(msg, "OpenSemaphoreW 성공 : Semaphore가 없는 상태로 open 시 실패해야 함");
		strcpy(buf, "OpenSemaphoreW 성공");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenSemaphoreW 실패", msg);

		return FALSE;
	}

	/* Semaphore 생성 실패 시 테스트 중단 */
	if(!(hSemaphoreCreate = CreateSemaphoreExW(NULL, lInitialCount, lMaximumCount, L"test_OpenSemaphoreW", 0, NULL))){
		sprintf(msg, GetErrorMessage("CreateSemaphoreExW 실패 : ", GetLastError()));
		strcpy(buf, "CreateSemaphoreExW 실패");;

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateSemaphoreExW 성공", msg);

		return FALSE;
	}

	/* Semaphore 생성 후 Open 시 성공해야 함 */
	hSemaphore = OpenSemaphoreW(SEMAPHORE_ALL_ACCESS | SEMAPHORE_MODIFY_STATE, FALSE, L"test_OpenSemaphoreW");
	if(hSemaphore == NULL){
		strcpy(msg, GetErrorMessage("OpenSemaphoreW 실패 : ", GetLastError()));
		strcpy(buf, "OpenSemaphoreW 실패");

		result = FALSE;
	}else{
		sprintf(msg, "OpenSemaphoreW 성공 : hSemaphoreCreate = %d\nhSemaphore = %d", hSemaphoreCreate, hSemaphore);
		strcpy(buf, "OpenSemaphoreW 성공");
	}
	
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenSemaphoreW 성공", msg);

	CloseHandle(hSemaphore);
	CloseHandle(hSemaphoreCreate);

	return result;
}


/**
* HANDLE WINAPI CreateSemaphoreEx(
  _In_opt_   LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
  _In_       LONG                  lInitialCount,
  _In_       LONG                  lMaximumCount,
  _In_opt_   LPCTSTR               lpName,
  _Reserved_ DWORD                 dwFlags,
  _In_       DWORD                 dwDesiredAccess
);
* 명명된 또는 명명되지 않은 세마포어 객체를 만들거나 연다.
* @author : 손찬영  
*
* @param  lpSemaphoreAttributes SECURITY_ATTRIBUTES 구조체에 대한 포인터
* @param  lInitialCount 세마포어 개체의 초기 개수.  이 값은 0보다 크거나 같고 lMaximumCount 보다 작거나 같아야 함.
* @param  lMaximumCount 세마포어 개체의 최대 개수
* @param  lpName 세마포어 객체의 이름을 지정하는 널 문자로 끝나는 문자열에 대한 포인터
* @param  dwFlags 예약
* @param  dwDesiredAccess semaphore 객체에 대한 액세스 마스크
* @return 성공하면 반환 값은 세마포어 객체의 핸들, 실패하면 NULL
*/
BOOL test_CreateSemaphoreExW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hSemaphore = NULL;
	LONG lInitialCount = 1, lMaximumCount = 1;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	const int nThreadCount = 2;
	HANDLE hThread[nThreadCount];
	sharedVar = 0;

	/* 1개 스레드만 접근 가능한 세마포어를 생성한다. */
	hSemaphore = CreateSemaphoreExW(NULL, lInitialCount, lMaximumCount, L"test_CreateSemaphoreExW", 0, NULL);

	/* 2개의 쓰레드를 생성하고 같은 hSemaphore 핸들을 넘긴다. */
	/* 스레드 생성에 실패 시 테스트 중단 */
	if(!CreateMultipleThreads(hThread, ThreadFunc, hSemaphore, nThreadCount)){
		return FALSE;
	}

	/* 모든 스레드가 종료될 때 까지 busy-waiting한다. */
	if(!BusyWaitingExitThread(hThread, 2)){
		return FALSE;
	}	

	/* 세마포어를 가진 스레드가 온전히 for문을 끝까지 돈 뒤에 다른 스레드가 공유자원에 접근하는지를 확인한다. */
	if(hSemaphore != NULL){ 
		if((sharedVar = BIG_INTEGER * 2)){
			sprintf(msg, "CreateSemaphoreExW 성공 : hSemaphore = %d, sharedVar = %d", hSemaphore, sharedVar);
			strcpy(buf, "CreateSemaphoreExW 성공");
		}else{
			sprintf(msg, "CreateSemaphoreExW 실패 : sharedVar가 %d가 아닙니다.", BIG_INTEGER * 2);
			strcpy(buf, "CreateSemaphoreExW 실패");
		}
		
	}else{
		strcpy(msg, GetErrorMessage("CreateSemaphoreExW 실패 : ", GetLastError()));
		strcpy(buf, "CreateSemaphoreExW 실패");

		result = FALSE;
		
	}
	
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateSemaphoreExW 성공", msg);

	CloseHandle(hSemaphore);

	for(int i=0; i<nThreadCount; i++){
		CloseHandle(hThread[i]);
	}
	sharedVar = 0;

	return result;
}

/**
* HANDLE WINAPI CreateSemaphoreEx(
  _In_opt_   LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
  _In_       LONG                  lInitialCount,
  _In_       LONG                  lMaximumCount,
  _In_opt_   LPCTSTR               lpName,
  _Reserved_ DWORD                 dwFlags,
  _In_       DWORD                 dwDesiredAccess
);
* 명명된 또는 명명되지 않은 세마포어 객체를 만들거나 연다.
* @author : 손찬영  
*
* @param  lpSemaphoreAttributes SECURITY_ATTRIBUTES 구조체에 대한 포인터
* @param  lInitialCount 세마포어 개체의 초기 개수.  이 값은 0보다 크거나 같고 lMaximumCount 보다 작거나 같아야 함.
* @param  lMaximumCount 세마포어 개체의 최대 개수
* @param  lpName 세마포어 객체의 이름을 지정하는 널 문자로 끝나는 문자열에 대한 포인터
* @param  dwFlags 예약
* @param  dwDesiredAccess semaphore 객체에 대한 액세스 마스크
* @return 성공하면 반환 값은 세마포어 객체의 핸들, 실패하면 NULL
*/
BOOL test_CreateSemaphoreExA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hSemaphore = NULL;
	LONG lInitialCount = 1, lMaximumCount = 1;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	const int nThreadCount = 2;
	HANDLE hThread[nThreadCount];
	sharedVar = 0;

	/* 1개 스레드만 접근 가능한 세마포어를 생성한다. */
	hSemaphore = CreateSemaphoreExA(NULL, lInitialCount, lMaximumCount, "test_CreateSemaphoreExA", 0, NULL);

	/* 2개의 쓰레드를 생성하고 같은 hSemaphore 핸들을 넘긴다. */
	/* 스레드 생성에 실패 시 테스트 중단 */
	if(!CreateMultipleThreads(hThread, ThreadFunc, hSemaphore, nThreadCount)){
		return FALSE;
	}

	/* 모든 스레드가 종료될 때 까지 busy-waiting한다. */
	if(!BusyWaitingExitThread(hThread, 2)){
		return FALSE;
	}	

	/* 세마포어를 가진 스레드가 온전히 for문을 끝까지 돈 뒤에 다른 스레드가 공유자원에 접근하는지를 확인한다. */
	if(hSemaphore != NULL){ 
		if((sharedVar = BIG_INTEGER * 2)){
			sprintf(msg, "CreateSemaphoreExA 성공 : hSemaphore = %d, sharedVar = %d", hSemaphore, sharedVar);
			strcpy(buf, "CreateSemaphoreExA 성공");
		}else{
			sprintf(msg, "CreateSemaphoreExA 실패 : sharedVar가 %d가 아닙니다.", BIG_INTEGER * 2);
			strcpy(buf, "CreateSemaphoreExA 실패");
		}
		
	}else{
		strcpy(msg, GetErrorMessage("CreateSemaphoreExA 실패 : ", GetLastError()));
		strcpy(buf, "CreateSemaphoreExA 실패");

		result = FALSE;
		
	}
	
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateSemaphoreExA 성공", msg);

	CloseHandle(hSemaphore);

	for(int i=0; i<nThreadCount; i++){
		CloseHandle(hThread[i]);
	}
	sharedVar = 0;

	return result;
}