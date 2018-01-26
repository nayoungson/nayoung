#include "TestMutex.h"


/**
* HANDLE CreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCTSTR lpName)
* 명명된 또는 명명되지 않은 뮤텍스 개체를 만들거나 연다.
* @author : 손찬영  
*
* @param  lpMutexAttributes SECURITY_ATTRIBUTES 구조체에 대한 포인터
* @param  bInitialOwner 이 값이 TRUE 이고 호출자가 뮤텍스를 만든 경우 호출 스레드는 뮤텍스 개체의 초기 소유권을 얻는다.
* @param  lpName 뮤텍스 개체의 이름
* @return 생성된 뮤텍스 개체에 대한 핸들
*/
BOOL test_CreateMutexA(void)
{
	BOOL result = TRUE;	
	char msg[BUFSIZ], buf[BUFSIZ];

	HANDLE hMutex = NULL;
	LPSTR lpName = "test_CreateMutexW";

	const int nThreadCount = 2;
	HANDLE hThread[nThreadCount];
	
	sharedVar = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hMutex = CreateMutexA(NULL, FALSE, lpName);

	/* 2개의 쓰레드를 생성하고 같은 hMutex 핸들을 넘긴다. */
	/* 스레드 생성에 실패 시 테스트 중단 */
	if(!CreateMultipleThreads(hThread, ThreadFunc, hMutex, nThreadCount)){
		return FALSE;
	}
	
	
	/* 모든 스레드가 종료될 때 까지 busy-waiting한다. */
	if(!BusyWaitingExitThread(hThread, 2)){
		return FALSE;
	}

	/* 뮤텍스를 가진 스레드가 온전히 for문을 끝까지 돈 뒤에 다른 스레드가 공유자원에 접근하는지를 확인한다. */
	if((NULL != hMutex)){
		if((sharedVar = BIG_INTEGER * 2)){
			sprintf(msg, "CreateMutexA 성공 : hMutex = %d, sharedVar = %d", hMutex, sharedVar);
			strcpy(buf, "CreateMutexA 성공");
		}else{
			sprintf(msg, "CreateMutexA 실패 : sharedVar가 %d가 아닙니다.", BIG_INTEGER * 2);
			strcpy(buf, "CreateMutexA 실패");
		}

	}else{ //뮤텍스 생성 실패
		sprintf(msg, GetErrorMessage("CreateMutexA 실패 : ", GetLastError()));
		strcpy(buf, "CreateMutexA 실패");
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateMutexA 성공", msg);

	CloseHandle(hMutex); //생성한 뮤텍스 제거 후 종료

	for(int i=0; i<nThreadCount; i++){
		CloseHandle(hThread[i]);
	}

	sharedVar = 0;

	return result;
}

/**
* HANDLE CreateMutexW(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCTSTR lpName)
* 명명된 또는 명명되지 않은 뮤텍스 개체를 만들거나 연다.
* @author : 손찬영  
*
* @param  lpMutexAttributes SECURITY_ATTRIBUTES 구조체에 대한 포인터
* @param  bInitialOwner 이 값이 TRUE 이고 호출자가 뮤텍스를 만든 경우 호출 스레드는 뮤텍스 개체의 초기 소유권을 얻는다.
* @param  lpName 뮤텍스 개체의 이름
* @return 생성된 뮤텍스 개체에 대한 핸들
*/
BOOL test_CreateMutexW(void)
{
	BOOL result = TRUE;	
	char msg[BUFSIZ], buf[BUFSIZ];

	HANDLE hMutex = NULL;
	LPWSTR lpName = L"test_CreateMutexA";

	const int nThreadCount = 2;
	HANDLE hThread[nThreadCount];
	
	sharedVar = 0;
	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hMutex = CreateMutexW(NULL, FALSE, lpName);

	/* 2개의 쓰레드를 생성하고 같은 hMutex 핸들을 넘긴다. */
	/* 스레드 생성에 실패 시 테스트 중단 */
	if(!CreateMultipleThreads(hThread, ThreadFunc, hMutex, nThreadCount)){
		return FALSE;
	}
	
	
	/* 모든 스레드가 종료될 때 까지 busy-waiting한다. */
	if(!BusyWaitingExitThread(hThread, 2)){
		return FALSE;
	}

	/* 뮤텍스를 가진 스레드가 온전히 for문을 끝까지 돈 뒤에 다른 스레드가 공유자원에 접근하는지를 확인한다. */
	if((NULL != hMutex)){
		if((sharedVar = BIG_INTEGER * 2)){
			sprintf(msg, "CreateMutexW 성공 : hMutex = %d, sharedVar = %d", hMutex, sharedVar);
			strcpy(buf, "CreateMutexW 성공");
		}else{
			sprintf(msg, "CreateMutexW 실패 : sharedVar가 %d가 아닙니다.", BIG_INTEGER * 2);
			strcpy(buf, "CreateMutexW 실패");
		}

	}else{ //뮤텍스 생성 실패
		sprintf(msg, GetErrorMessage("CreateMutexW 실패 : ", GetLastError()));
		strcpy(buf, "CreateMutexW 실패");
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateMutexW 성공", msg);

	CloseHandle(hMutex); //생성한 뮤텍스 제거 후 종료

	for(int i=0; i<nThreadCount; i++){
		CloseHandle(hThread[i]);
	}

	sharedVar = 0;

	return result;
}

/**
* HANDLE OpenMutexW(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCTSTR lpName)
* 기존의 명명된 뮤텍스 개체를 연다.
* @author : 손찬영  
*
* @param  dwDesiredAccess 뮤텍스 개체에 대한 액세스
* @param  bInheritHandle 이 값이 TRUE 이면, 프로세스에서 생성 된 프로세스가 핸들을 상속한다.
* @param  lpName 열리는 뮤텍스의 이름
* @return 뮤텍스 개체의 핸들
*/
BOOL test_OpenMutexW(void)
{
	LPSECURITY_ATTRIBUTES lpMutexAttributes = NULL;
	BOOL bInitialOwner = FALSE;
	LPCTSTR lpName = L"test_OpenMutexW";
	HANDLE hMutex = 0;
	HANDLE hMutexCreate = 0;
	BOOL result = TRUE;	

	char msg[BUFSIZ];
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* Mutex 없는 상태로 Open 시도 시 실패해야 함 */
	if(OpenMutexW(MUTEX_ALL_ACCESS, FALSE, lpName)){
		sprintf(msg, "OpenMutexW 성공 : Mutex가 없는 상태로 open 시 실패해야 함");
		strcpy(buf, "OpenMutexW 성공");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenMutexW 실패", msg);

		return FALSE;
	}
	
	
	/* Mutex 생성 실패 시 테스트 중단 */
	if(!(hMutexCreate = CreateMutexW(NULL, FALSE, lpName))){
		sprintf(msg, GetErrorMessage("CreateMutexW 실패 : ", GetLastError()));
		strcpy(buf, "CreateMutexW 실패");;

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateMutexW 성공", msg);

		return FALSE;
	}

	/* Mutex 생성 후 Open 시 성공해야 함 */
	hMutex = OpenMutexW(MUTEX_ALL_ACCESS, FALSE, lpName);
	if(NULL != hMutex){ 
		sprintf(msg, "OpenMutexW 성공 : hMutex = %d", hMutex);
		strcpy(buf, "OpenMutexW 성공");

	}else{ //뮤텍스 오픈 실패
		sprintf(msg, GetErrorMessage("OpenMutexW 실패 : ", GetLastError()));
		strcpy(buf, "OpenMutexW 실패");

		result = FALSE;
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenMutexW 성공", msg);

	CloseHandle(hMutex); //생성한 뮤텍스 제거 후 종료
	CloseHandle(hMutexCreate);

	return result;
}


/**
* HANDLE OpenMutexA(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCTSTR lpName)
* 기존의 명명된 뮤텍스 개체를 연다.
* @author : 손찬영  
*
* @param  dwDesiredAccess 뮤텍스 개체에 대한 액세스
* @param  bInheritHandle 이 값이 TRUE 이면, 프로세스에서 생성 된 프로세스가 핸들을 상속한다.
* @param  lpName 열리는 뮤텍스의 이름
* @return 뮤텍스 개체의 핸들
*/
BOOL test_OpenMutexA()
{
	LPSECURITY_ATTRIBUTES lpMutexAttributes = NULL;
	BOOL bInitialOwner = FALSE;
	LPSTR lpName = "test_OpenMutexA";
	HANDLE hMutex = 0;
	HANDLE hMutexCreate = 0;
	BOOL result = TRUE;	

	char msg[BUFSIZ];
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* Mutex 없는 상태로 Open 시도 시 실패해야 함 */
	if(OpenMutexA(MUTEX_ALL_ACCESS, FALSE, lpName)){
		sprintf(msg, "OpenMutexW 성공 : Mutex가 없는 상태로 open 시 실패해야 함");
		strcpy(buf, "OpenMutexW 성공");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenMutexW 실패", msg);

		return FALSE;
	}
	
	
	/* Mutex 생성 실패 시 테스트 중단 */
	if(!(hMutexCreate = CreateMutexA(NULL, FALSE, lpName))){
		sprintf(msg, GetErrorMessage("CreateMutexA 실패 : ", GetLastError()));
		strcpy(buf, "CreateMutexA 실패");;

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateMutexA 성공", msg);

		return FALSE;
	}

	/* Mutex 생성 후 Open 시 성공해야 함 */
	hMutex = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, lpName);
	if(NULL != hMutex){ 
		sprintf(msg, "OpenMutexA 성공 : hMutex = %d", hMutex);
		strcpy(buf, "OpenMutexA 성공");

	}else{ //뮤텍스 오픈 실패
		sprintf(msg, GetErrorMessage("OpenMutexA 실패 : ", GetLastError()));
		strcpy(buf, "OpenMutexA 실패");

		result = FALSE;
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenMutexA 성공", msg);

	CloseHandle(hMutex); //생성한 뮤텍스 제거 후 종료
	CloseHandle(hMutexCreate);

	return result;
}

/**
* HANDLE CreateMutexExW(LPSECURITY_ATTRIBUTES lpMutexAttributes, LPCTSTR lpName,  DWORD dwFlags, DWORD dwDesiredAccess)
* 명명된 또는 명명되지 않은 뮤텍스 개체를 만들거나 연다.
* @author : 손찬영  
*
* @param  lpMutexAttributes SECURITY_ATTRIBUTES 구조체에 대한 포인터
* @param  lpName 뮤텍스 개체의 이름
* @param  dwFlags CREATE_MUTEX_INITIAL_OWNER 이거나 0
* @param  dwDesiredAccess 뮤텍스 개체의 액세스 마스크
* @return 뮤텍스 개체의 핸들
*/
BOOL test_CreateMutexExW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ], buf[BUFSIZ];

	HANDLE hMutex = NULL;
	LPWSTR lpName = L"test_CreateMutexExW";

	const int nThreadCount = 2;
	HANDLE hThread[nThreadCount];
	
	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	sharedVar = 0;

	hMutex = CreateMutexExW(NULL, lpName, 0, MUTEX_ALL_ACCESS | MUTEX_MODIFY_STATE);

	/* 2개의 쓰레드를 생성하고 같은 hMutex 핸들을 넘긴다. */
	/* 스레드 생성에 실패 시 테스트 중단 */
	if(!CreateMultipleThreads(hThread, ThreadFunc, hMutex, nThreadCount)){
		return FALSE;
	}	
	
	/* 모든 스레드가 종료될 때 까지 busy-waiting한다. */
	if(!BusyWaitingExitThread(hThread, 2)){
		return FALSE;
	}

	/* 뮤텍스를 가진 스레드가 온전히 for문을 끝까지 돈 뒤에 다른 스레드가 공유자원에 접근하는지를 확인한다. */
	if((NULL != hMutex)){
		if((sharedVar = BIG_INTEGER * 2)){
			sprintf(msg, "CreateMutexExW 성공 : hMutex = %d, sharedVar = %d", hMutex, sharedVar);
			strcpy(buf, "CreateMutexExW 성공");
		}else{
			sprintf(msg, "CreateMutexExW 실패 : sharedVar가 %d가 아닙니다.", BIG_INTEGER * 2);
			strcpy(buf, "CreateMutexExW 실패");
		}

	}else{ //뮤텍스 생성 실패
		sprintf(msg, GetErrorMessage("CreateMutexExW 실패 : ", GetLastError()));
		strcpy(buf, "CreateMutexExW 실패");
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateMutexExW 성공", msg);

	CloseHandle(hMutex); //생성한 뮤텍스 제거 후 종료

	for(int i=0; i<nThreadCount; i++){
		CloseHandle(hThread[i]);
	}

	sharedVar = 0;

	return result;
}

/**
* HANDLE CreateMutexExA(LPSECURITY_ATTRIBUTES lpMutexAttributes, LPCTSTR lpName,  DWORD dwFlags, DWORD dwDesiredAccess)
* 명명된 또는 명명되지 않은 뮤텍스 개체를 만들거나 연다.
* @author : 손찬영  
*
* @param  lpMutexAttributes SECURITY_ATTRIBUTES 구조체에 대한 포인터
* @param  lpName 뮤텍스 개체의 이름
* @param  dwFlags CREATE_MUTEX_INITIAL_OWNER 이거나 0
* @param  dwDesiredAccess 뮤텍스 개체의 액세스 마스크
* @return 뮤텍스 개체의 핸들
*/
BOOL test_CreateMutexExA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ], buf[BUFSIZ];

	HANDLE hMutex = NULL;
	LPSTR lpName = "test_CreateMutexExW";

	const int nThreadCount = 2;
	HANDLE hThread[nThreadCount];
	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	sharedVar = 0;

	hMutex = CreateMutexExA(NULL, lpName, 0, MUTEX_ALL_ACCESS | MUTEX_MODIFY_STATE);

	
	/* 2개의 쓰레드를 생성하고 같은 hMutex 핸들을 넘긴다. */
	/* 스레드 생성에 실패 시 테스트 중단 */
	if(!CreateMultipleThreads(hThread, ThreadFunc, hMutex, nThreadCount)){
		return FALSE;
	}
	
	
	/* 모든 스레드가 종료될 때 까지 busy-waiting한다. */
	if(!BusyWaitingExitThread(hThread, 2)){
		return FALSE;
	}

	/* 뮤텍스를 가진 스레드가 온전히 for문을 끝까지 돈 뒤에 다른 스레드가 공유자원에 접근하는지를 확인한다. */
	if((NULL != hMutex)){
		if((sharedVar = BIG_INTEGER * 2)){
			sprintf(msg, "CreateMutexExA 성공 : hMutex = %d, sharedVar = %d", hMutex, sharedVar);
			strcpy(buf, "CreateMutexExA 성공");
		}else{
			sprintf(msg, "CreateMutexExA 실패 : sharedVar가 %d가 아닙니다.", BIG_INTEGER * 2);
			strcpy(buf, "CreateMutexExA 실패");
		}

	}else{ //뮤텍스 생성 실패
		sprintf(msg, GetErrorMessage("CreateMutexExA 실패 : ", GetLastError()));
		strcpy(buf, "CreateMutexExA 실패");
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateMutexExA 성공", msg);

	CloseHandle(hMutex); //생성한 뮤텍스 제거 후 종료

	for(int i=0; i<nThreadCount; i++){
		CloseHandle(hThread[i]);
	}

	sharedVar = 0;

	return result;
}


