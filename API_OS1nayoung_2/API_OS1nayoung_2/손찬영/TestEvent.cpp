#include "TestEvent.h"


/**
* HANDLE OpenEventW(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCTSTR lpName)
* 기존의 명명된 이벤트 객체를 연다.
* @author : 손찬영  
*
* @param  dwDesiredAccess 이벤트 객체에 대한 액세스
* @param  bInheritHandle 이 값이 TRUE 이면이 프로세스에서 생성 된 프로세스가 핸들을 상속
* @param  lpName 열리는 이벤트의 이름
* @return 함수가 성공하면 반환 값은 이벤트 객체에 대한 핸들, 실패하면 NULL
*/
BOOL test_OpenEventW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;

	HANDLE hEvent = NULL;
	HANDLE hEventCreate = NULL;
	//hEvent = OpenEventW(EVENT_ALL_ACCESS, FALSE, L"MyEvent");
	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	///*
	//[TEST 1] 존재하지 않는 이벤트를 오픈 시도
	//*/
	//#ifdef OQADBG
	//MessageBoxA(NULL, "[TEST 1]\n존재하지 않는 이벤트 오픈을 시도합니다.", "test_OpenEventW", MB_OK);
	//#endif
	//hEvent = OpenEventW(EVENT_ALL_ACCESS | EVENT_MODIFY_STATE, FALSE, L"MyEvent");
	//if(hEvent != NULL){ // 이벤트 오픈 성공
	//	sprintf(msg, "hEvent = %d", hEvent);
	//	strcpy(buf, "Event Open 성공");

	//}else if(errorCode=GetLastError()){ // 이벤트 오픈 실패
	//	strcpy(msg, GetErrorMessage("OpenEvent 실패 : ", errorCode));
	//	strcpy(buf, "Event Open 실패");


	//}else{

	//}
	//wresult(__FILE__,__LINE__ ,"OpenEventW", buf, "Event Open 실패", msg);

	/*
	[TEST 2] 이벤트를 생성하고 오픈 확인
	*/
	#ifdef OQADBG
	MessageBoxA(NULL, "[TEST 2]\n이벤트를 생성하고 오픈을 시도합니다.", "test_OpenEventW", MB_OK);
	#endif
	hEventCreate = CreateEvent(NULL, FALSE, FALSE, L"MyEvent");
	if(hEventCreate == NULL){ //이벤트 생성 실패
		strcpy(msg, GetErrorMessage("이벤트 생성 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,"OpenEventW", msg, "Event 생성 성공", msg);

		return FALSE;
	}
	hEvent = OpenEventW(EVENT_ALL_ACCESS | EVENT_MODIFY_STATE, FALSE, L"MyEvent");
	if(hEvent != NULL){ // 이벤트 오픈 성공
		sprintf(msg, "Event Open 성공 : hEvent = %d", hEvent);
		strcpy(buf, "Event Open 성공");

	}else if(errorCode=GetLastError()){
		strcpy(msg, GetErrorMessage("OpenEvent 실패 : ", errorCode));
		strcpy(buf, "Event Open 실패");
		result = FALSE;	

	}else{ //알수없는 에러
		sprintf(msg, "알 수 없는 에러\nhEvent = %d\nerrorCode = %d", hEvent, errorCode);
		strcpy(buf, msg);
		result = FALSE;	
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "Event Open 성공", msg);

	CloseHandle(hEvent);
	CloseHandle(hEventCreate);

	return result;
}


/**
* BOOL PulseEvent(HANDLE hEvent)
* 지정된 이벤트 객체를 신호 상태로 설정 한 다음 적절한 수의 대기중인 스레드를 해제 한 후에 신호를 신호가없는 상태로 다시 설정한다. 
이 함수는 신뢰할 수 없으므로 사용하지 않아야 함.
* @author : 손찬영  
*
* @param  hEvent 이벤트 객체에 대한 핸들
* @return 성공/실패 여부
*/
BOOL test_PulseEvent()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;

	HANDLE hEventCreate = NULL;
	HANDLE hEvent = NULL;
	HANDLE hThread[3];
	DWORD exitCode[3] = {0, 0, 0};
	DWORD ThreadID;

	THREADEVENT ret;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hEventCreate = CreateEvent(NULL, TRUE, FALSE, NULL); //수동 이벤트(TRUE), 비신호상태(FALSE)

	if(hEventCreate == NULL){ //이벤트 생성 실패
		strcpy(msg, GetErrorMessage("이벤트 생성 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "Event 생성 성공", msg);

		return FALSE;
	}

	hEvent = hEventCreate;
	#ifdef OQADBGPRINT
	printf("test_PulseEvent hEvent = %d\n", hEvent);
	#endif

	ResetEvent(hEvent); //신호를 비신호상태로 설정

	ret.hEvent = hEvent;

	hThread[0] = CreateThread(NULL, 0, ThreadFirst, &ret, 0, &ThreadID);
	hThread[1] = CreateThread(NULL, 0, ThreadSecond, &ret, 0, &ThreadID);
	hThread[2] = CreateThread(NULL, 0, ThreadThird, &ret, 0, &ThreadID);

	//CloseHandle(hEvent); 

	while(TRUE){ //모든 쓰레드 종료까지 busy waiting
		//printf("while문\n");
		for(int i=0; i<3; i++){
			GetExitCodeThread(hThread[i], &exitCode[i]);
		}

		if((exitCode[0] != STILL_ACTIVE) && (exitCode[1] != STILL_ACTIVE) && (exitCode[2] != STILL_ACTIVE)){
			break;
		}
	}
	//Sleep(SLEEP_SECOND * 1000);

	#ifdef OQADBGPRINT
	printf("while문 종료\n");
	#endif

	if(((ret.nowSecond[0] + SLEEP_SECOND)%60) == (ret.nowSecond[1]%60)){
		sprintf(msg, "PulseEvent 성공 : 스레드1 시간 : %lu\n스레드2 시간 : %lu", ret.nowSecond[0], ret.nowSecond[1]);
		strcpy(buf, "PulseEvent 성공");
	
	}else{
		sprintf(msg, "PulseEvent 실패\n스레드1 시간 : %lu\n스레드2 시간 : %lu", ret.nowSecond[0], ret.nowSecond[1]);
		strcpy(buf, "PulseEvent 실패");
		result = FALSE;	
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "PulseEvent 성공", msg);

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hThread[2]);
	
	return result;
}

DWORD WINAPI ThreadFirst(LPVOID temp)
{
	THREADEVENT *threadReturn;
	SYSTEMTIME systemTimeNow;
	
	threadReturn = (THREADEVENT *)temp;
	#ifdef OQADBGPRINT
	printf("ThreadFirst hEvent = %d\n", threadReturn->hEvent);
	#endif

	#ifdef OQADBGPRINT
	printf("첫번째 쓰레드가 Event를 set합니다.\n3초 뒤에 Thread2, Thread3이 깨어나면 성공");
	#endif

	GetSystemTime(&systemTimeNow); //현재 시간 확인
	Sleep((SLEEP_SECOND) * 1000); //3초 슬립
	
	#ifdef OQADBGPRINT
	printf("슬립 종료\n");
	#endif

	//SetEvent(hEvent); //신호상태로 변경
	#ifdef OQADBGPRINT
	printf("첫번째 쓰레드가 PulseEvent합니다.\n");
	#endif
	PulseEvent(threadReturn->hEvent);
	threadReturn->nowSecond[0] = systemTimeNow.wSecond;
	
	return systemTimeNow.wSecond;
}
DWORD WINAPI ThreadSecond(LPVOID temp)
{
	//HANDLE hEvent = (HANDLE)temp;
	THREADEVENT *threadReturn;
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	SYSTEMTIME systemTimeNow;

	threadReturn = (THREADEVENT *)temp;
	#ifdef OQADBGPRINT
	printf("ThreadSecond hEvent = %d\n", threadReturn->hEvent);
	#endif

	if(WaitForSingleObject(threadReturn->hEvent, INFINITE) == WAIT_FAILED){
		sprintf(msg, GetErrorMessage("Thread2 WaitForSingleObject 실패 : ",GetLastError()));
		strcpy(buf, "ThreadSecond WaitForSingleObject 실패");
		#ifdef OQADBGPRINT
		printf("%s\n", msg);
		#endif
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf,  "WaitForSingleObject 성공", msg);
		return FALSE;
	}
	//여기시간 측정해서 두 시간차 확인
	GetSystemTime(&systemTimeNow); //현재 시간 확인
	threadReturn->nowSecond[1] = systemTimeNow.wSecond;

	#ifdef OQADBGPRINT
	printf("두번째 쓰레드가 일어납니다.\n");
	#endif
	
	return systemTimeNow.wSecond;
}
DWORD WINAPI ThreadThird(LPVOID temp)
{
	THREADEVENT *threadReturn;
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	SYSTEMTIME systemTimeNow;

	threadReturn = (THREADEVENT *)temp;
	#ifdef OQADBGPRINT
	printf("ThreadThird hEvent = %d\n", threadReturn->hEvent);
	#endif
	if(WaitForSingleObject(threadReturn->hEvent, INFINITE) == WAIT_FAILED){
		sprintf(msg, GetErrorMessage("Thread3 WaitForSingleObject 실패 : ",GetLastError()));
		strcpy(buf, "ThreadThird WaitForSingleObject 실패");
		#ifdef OQADBGPRINT
		printf("%s\n", msg);
		#endif
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf,  "WaitForSingleObject 성공", msg);

		return FALSE;
	}
	
	GetSystemTime(&systemTimeNow); //현재 시간 확인
	threadReturn->nowSecond[2] = systemTimeNow.wSecond;

	#ifdef OQADBGPRINT
	printf("세번째 쓰레드가 일어납니다.\n");
	#endif
	
	return systemTimeNow.wSecond;
}


/**
* HANDLE CreateEventExW(LPSECURITY_ATTRIBUTES lpEventAttributes, LPCTSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess)
* 명명된 또는 명명되지 않은 이벤트 객체를 만들거나 연다.
* @author : 손찬영  
*
* @param  lpEventAttributes SECURITY_ATTRIBUTES 구조체에 대한 포인터
* @param  lpName 이벤트 객체의 이름
* @param  dwFlags CREATE_EVENT_INITIAL_SET 또는 CREATE_EVENT_MANUAL_RESET
* @param  dwDesiredAccess 이벤트 객체의 액세스 마스크
* @return 함수가 성공하면 반환 값은 이벤트 객체에 대한 핸들, 실패하면 반환 값은 NULL
*/
BOOL test_CreateEventExW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hEventCreate = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* 처음 SetEvent하는 경우는 실패 */
	if(SetEvent(hEventCreate)){
		strcpy(msg, "이벤트 생성 전에 SetEvent가 실패해야 합니다.");
		strcpy(buf, "SetEvent 성공");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetEvent 실패", msg);

		return FALSE;
	}
	hEventCreate = CreateEventExW(NULL, NULL, CREATE_EVENT_INITIAL_SET, EVENT_ALL_ACCESS);

	/*이벤트 생성 후 SetEvent 시 성공하는 것을 확인함 */
	if((hEventCreate != NULL) && SetEvent(hEventCreate)){ 
		sprintf(msg, "CreateEventExW 성공 : hEventCreate = %d", hEventCreate);
		strcpy(buf, "CreateEventExW 성공");
		
	}else{ //이벤트 생성 실패
		strcpy(msg, GetErrorMessage("CreateEventExW 실패 : ", GetLastError()));
		strcpy(buf, "CreateEventExW 실패");

		result = FALSE;
		
	}
	

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateEventExW 성공", msg);

	return result;
}

/**
* HANDLE CreateEventExA(LPSECURITY_ATTRIBUTES lpEventAttributes, LPCTSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess)
* 명명된 또는 명명되지 않은 이벤트 객체를 만들거나 연다.
* @author : 손찬영  
*
* @param  lpEventAttributes SECURITY_ATTRIBUTES 구조체에 대한 포인터
* @param  lpName 이벤트 객체의 이름
* @param  dwFlags CREATE_EVENT_INITIAL_SET 또는 CREATE_EVENT_MANUAL_RESET
* @param  dwDesiredAccess 이벤트 객체의 액세스 마스크
* @return 함수가 성공하면 반환 값은 이벤트 객체에 대한 핸들, 실패하면 반환 값은 NULL
*/
BOOL test_CreateEventExA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hEventCreate = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* 처음 SetEvent하는 경우는 실패 */
	if(SetEvent(hEventCreate)){
		strcpy(msg, "이벤트 생성 전에 SetEvent가 실패해야 합니다.");
		strcpy(buf, "SetEvent 성공");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetEvent 실패", msg);

		return FALSE;
	}
	hEventCreate = CreateEventExA(NULL, NULL, CREATE_EVENT_INITIAL_SET, EVENT_ALL_ACCESS);

	/*이벤트 생성 후 SetEvent 시 성공하는 것을 확인함 */
	if((hEventCreate != NULL) && SetEvent(hEventCreate)){ 
		sprintf(msg, "CreateEventExA 성공 : hEventCreate = %d", hEventCreate);
		strcpy(buf, "CreateEventExA 성공");
		
	}else{ //이벤트 생성 실패
		strcpy(msg, GetErrorMessage("CreateEventExA 실패 : ", GetLastError()));
		strcpy(buf, "CreateEventExA 실패");

		result = FALSE;
		
	}
	

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateEventExA 성공", msg);

	return result;
}