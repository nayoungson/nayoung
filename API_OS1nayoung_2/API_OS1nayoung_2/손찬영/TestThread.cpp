#include "TestThread.h"

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	return (DWORD)TRUE;
}

/**
* BOOL WINAPI GetThreadContext(
  _In_    HANDLE    hThread,
  _Inout_ LPCONTEXT lpContext
);
* 지정된 thread의 문맥을 얻는다.
* @author : 손찬영  
*
* @param  hThread	컨텍스트를 검색할 스레드의 핸들
* @param  lpContext 지정된 스레드의 적절한 컨텍스트를 수신 하는 CONTEXT 구조체의 포인터
* @return 성공/실패 여부
*/
BOOL test_GetThreadContext(void)
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	CONTEXT context, expectContext;
	HANDLE hThread = NULL;
	DWORD ret=0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* 스레드 생성 실패 시 테스트 중단 */
	hThread = CreateThread(NULL, 0, &ThreadProc, NULL, 0, NULL);
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("CreateThread 실패 : ", GetLastError()));
		strcpy(buf, "CreateThread 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateThread 성공", msg);

		return FALSE;
	}

	/* Context 구조체 초기화 */
	memset(&context, 0, sizeof(context));
	memset(&expectContext, 0, sizeof(expectContext));


	/* context 정보를 가져오기 실패하면 테스트 실패 */
	if(!GetThreadContext(hThread, &context)){
		strcpy(msg, GetErrorMessage("GetThreadContext 실패 : ", GetLastError()));
		strcpy(buf, "GetThreadContext 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetThreadContext 성공", msg);

		return FALSE;
	}

	
	//memcpy(&expectContext, &context, sizeof(context));
	//expectContext.ContextFlags = 2;

	///* 기대하는 Context로 Set한다. 실패시 테스트 중단 */
	//if(!SetThreadContext(hThread, &expectContext)){
	//	strcpy(msg, GetErrorMessage("SetThreadContext 실패 : ", GetLastError()));
	//	strcpy(buf, "SetThreadContext 실패");
	//
	//	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetThreadContext 성공", msg);

	//	return FALSE;
	//}

	/* expectContext에 컨텍스트 정보를 가져온다. */
	if(!GetThreadContext(hThread, &expectContext)){
		strcpy(msg, GetErrorMessage("GetThreadContext 실패 : ", GetLastError()));
		strcpy(buf, "GetThreadContext 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetThreadContext 성공", msg);

		return FALSE;
	}

	/* expectContext와 context가 동일하면 성공으로 판단한다. */
	if(!memcmp(&expectContext, &context, sizeof(context))){
		sprintf(msg, "GetThreadContext 성공 : context.ContextFlags = %d", context.ContextFlags);
		strcpy(buf, "GetThreadContext 성공");

	/* expectContext와 context가 서로 다름 여기서 ContextFlags값만 확인 */
	}else{
		sprintf(msg, "GetThreadContext 실패 : context.ContextFlags = %d, expectContext.ContextFlags = %d", context.ContextFlags, expectContext.ContextFlags);
		strcpy(buf, "GetThreadContext 실패");

		result = FALSE;	
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetThreadContext 성공", msg);

	CloseHandle(hThread);	

	return result;
}

/**
* BOOL SetThreadLocale(
  _In_ LCID Locale
);
* 호출하는 thread의 현재의 로케일을 설정한다.
* @author : 손찬영  
*
* @param  Locale	로케일 을 지정하는 로케일 식별자. LOCALE_CUSTOM_DEFAULT 등.
* @return 성공/실패 여부
*/
BOOL test_SetThreadLocale(void)
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LCID locale, expectLocale, changeLocale = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* 초기 로케일을 가져온다 */
	locale = GetThreadLocale();

	/* 기대하는 로케일 값을 기존 로케일값 + 1로 지정한다 */
	expectLocale = locale+1;

	/* SetThreadLocale 함수 실패 */
	if(!SetThreadLocale(expectLocale)){
		strcpy(msg, GetErrorMessage("SetThreadLocale 실패 : ", GetLastError()));
		strcpy(buf, "SetThreadLocale 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetThreadLocale 성공", msg);

		return FALSE;
	}

	/* Set한 뒤 다시 로케일을 가져온다 */
	changeLocale = GetThreadLocale();

	/* 원하는 locale값으로 set 성공 */
	if(expectLocale == changeLocale){
		sprintf(msg, "SetThreadLocale 성공 : originLocale = %d, changeLocale = %d", locale, changeLocale);
		strcpy(buf, "SetThreadLocale 성공");

	/* 원하는 locale값으로 set 실패 */
	}else{
		sprintf(msg, "SetThreadLocale 실패 : changeLocale = %d, expectLocale = %d", changeLocale, expectLocale);
		strcpy(buf, "SetThreadLocale 실패");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "SetThreadLocale 성공", msg);


	/* 기존 로케일로 복원 후 종료 */
	SetThreadLocale(locale);

	return result;
}


/**
* EXECUTION_STATE WINAPI SetThreadExecutionState(
  _In_ EXECUTION_STATE esFlags
);
* 응용 프로그램이 사용 중임을 시스템에 알린다. 
응용 프로그램이 실행되는 동안 시스템이 절전 모드로 들어가거나 디스플레이가 꺼지는 것을 방지 할 수 있다.
* @author : 손찬영  
*
* @param  esFlags	스레드의 실행 요구 사항. ES_AWAYMODE_REQUIRED 등.
* @return 성공하면 반환 값은 스레드의 이전 실행 상태, 실패 시 NULL
*/
BOOL test_SetThreadExecutionState(void)
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	//Television recording is beginning. Enable away mode and prevent the sleep idle time-out.
	EXECUTION_STATE esFlags = ES_SYSTEM_REQUIRED | ES_CONTINUOUS;
	EXECUTION_STATE ret = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(ret = SetThreadExecutionState(esFlags)){
		strcpy(msg, "SetThreadExecutionState 성공");
		strcpy(buf, msg);
	
	}else{ //절전 방지모드 실패
		strcpy(msg, GetErrorMessage("SetThreadExecutionState 실패 : ", GetLastError()));
		strcpy(buf, "SetThreadExecutionState 실패");

		result = FALSE;	
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "SetThreadExecutionState 성공", msg);

	return result;
}

/**
* DWORD WINAPI Wow64SuspendThread(
  _In_ HANDLE hThread
);
* 지정된 WOW64 스레드를 일시 중단한다.
* @author : 손찬영  
*
* @param  hThread	일시 중단 될 스레드의 핸들
* @return 성공하면 반환 값은 스레드의 이전 일시 중단 횟수, 실패 시 -1
*/
BOOL test_Wow64SuspendThread()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hThread = NULL;
	DWORD ThreadID;

	DWORD suspendCount = -1;
	const int expectSuspend = 10;


	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	
	/* 스레드 생성 실패 시 테스트 중단 */
	hThread = CreateThread(NULL, 0, ThreadWow64Suspend, NULL, 0, &ThreadID);
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("CreateThread 실패 : ", GetLastError()));
		strcpy(buf, "CreateThread 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateThread 성공", msg);

		return FALSE;
	}
	Sleep(1000);
	for(int i=0; i<expectSuspend; i++){
		suspendCount = Wow64SuspendThread(hThread);
	}
	Sleep(1000);
	for(int i=0; i<expectSuspend; i++){
		ResumeThread(hThread);
	}
	
	if(!BusyWaitingExitThread(&hThread, 1)){
		return FALSE;
	}

	if(suspendCount == expectSuspend-1){
		sprintf(msg, "Wow64SuspendThread 성공 : suspnedCount = %d", suspendCount);
		strcpy(buf, "Wow64SuspendThread 성공");

	}else{
		sprintf(msg, "Wow64SuspendThread 실패\nsuspnedCount = %d", suspendCount);
		strcpy(buf, "Wow64SuspendThread 실패");

		result = FALSE;
	}
	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "Wow64SuspendThread 성공", msg);

	CloseHandle(hThread);

	return result;
}

/* Wow64Suspen */
DWORD WINAPI ThreadWow64Suspend(LPVOID temp)
{
	for(int i=0; i<20; i++){
		printf("i = %d\n", i);
		Sleep(100);
	}
	return 0;
}

/**
* DWORD WINAPI GetThreadId(
  _In_ HANDLE Thread
);
* 지정된 thread의 thread 식별자를 가져온다.
* @author : 손찬영  
*
* @param  Thread	스레드에 대한 핸들
* @return 성공하면 반환 값은 스레드ID, 실패 시 0
*/
BOOL test_GetThreadId()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hThread = NULL;
	DWORD expectThreadID = 0;
	DWORD ThreadID = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* 스레드 생성 실패 시 테스트 중단 */
	hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, &expectThreadID);
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("CreateThread 실패 : ", GetLastError()));
		strcpy(buf, "CreateThread 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateThread 성공", msg);

		return FALSE;
	}

	ThreadID = GetThreadId(hThread);
	if(NULL != ThreadID){
		/* 스레드 아이디가 같은 경우 성공으로 판단 */
		if(expectThreadID == ThreadID){
			sprintf(msg, "GetThreadId 성공 : ThreadID = %d", ThreadID, expectThreadID);
			strcpy(buf, "GetThreadId 성공");

		/* 함수는 성공했지만 스레드 아이디가 서로 다름 */
		}else{
			sprintf(msg, "GetThreadId 실패\nThreadID = %d\nexpectThreadID = %d", ThreadID, expectThreadID);
			strcpy(buf, "GetThreadId 실패");

			result = FALSE;
		}

	/* 함수 실패 */
	}else{
		strcpy(msg, GetErrorMessage("GetThreadId 실패 : ", GetLastError()));
		strcpy(buf, "GetThreadId 실패");

		result = FALSE;
	}

	#ifdef OQADBGPRINT
	printf("expectThreadID = %d\nThreadID = %d\n", expectThreadID, ThreadID);
	#endif
	
	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetThreadId 성공", msg);

	CloseHandle(hThread);

	return result;
}

/**
* DWORD WINAPI GetProcessIdOfThread(
  _In_ HANDLE Thread
);
* 지정된 thread에 관련한 프로세스의 프로세스 식별자를 가져온다.
* @author : 손찬영  
*
* @param  Thread	스레드에 대한 핸들
* @return 성공하면 반환 값은 스레드와 연관된 프로세스의 프로세스 ID, 실패 시 0
*/
BOOL test_GetProcessIdOfThread()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hThread = NULL, hCurrentProcess = NULL;

	DWORD expectProcessID = 0;
	DWORD ProcessID = 0;
	DWORD ThreadID;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* 현재 프로세스의 의사 핸들을 가져온다. */
	hCurrentProcess = GetCurrentProcess();

	/* 현재 프로세스의 ID를 가져오지 못하면 테스트 중단 */
	expectProcessID = GetProcessId(hCurrentProcess);
	if(NULL == expectProcessID){
		strcpy(msg, GetErrorMessage("GetProcessId 실패 : ", GetLastError()));
		strcpy(buf, "GetProcessId 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetProcessId 성공", msg);

		return FALSE;
	}

	/* 스레드 생성 실패 시 테스트 중단 */
	hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, &ThreadID);
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("CreateThread 실패 : ", GetLastError()));
		strcpy(buf, "CreateThread 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateThread 성공", msg);

		return FALSE;
	}

	/* 생성한 스레드의 프로세스 ID를 가져온다. */
	ProcessID = GetProcessIdOfThread(hThread);
	if(NULL != ProcessID){
		/* 프로세스 값이 동일하면 성공 */
		if(expectProcessID == ProcessID){
			sprintf(msg, "GetProcessIdOfThread 성공 : ProcessID = %d", ProcessID, expectProcessID);
			strcpy(buf, "GetProcessIdOfThread 성공");

		/* 함수는 성공했지만 프로세스값이 동일하지 않음 */
		}else{
			sprintf(msg, "GetProcessIdOfThread 실패\nProcessID = %d\nexpectProcessID = %d", ProcessID, expectProcessID);
			strcpy(buf, "GetProcessIdOfThread 실패");

			result = FALSE;
		}

	/* 함수 실패 */
	}else{
		strcpy(msg, GetErrorMessage("GetProcessIdOfThread 실패 : ", GetLastError()));
		strcpy(buf, "GetProcessIdOfThread 실패");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetProcessIdOfThread 성공", msg);

	CloseHandle(hThread);

	return result;
}

/**
* BOOL GetThreadIdealProcessorEx(
  _In_  HANDLE            hThread,
  _Out_ PPROCESSOR_NUMBER lpIdealProcessor
);
* 지정된 thread의 이상적인 프로세서의 프로세서 번호
* @author : 손찬영  
*
* @param  Thread			이상적인 프로세서를 검색 할 스레드 핸들
* @param  lpIdealProcessor	이상적인 프로세서 번호를 받기 위한 PROCESSOR_NUMBER 구조체의 포인터
* @return					성공/실패 여부
*/
BOOL test_GetThreadIdealProcessorEx()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hThread = NULL;

	DWORD ThreadID;
	PROCESSOR_NUMBER IdealProcessor;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif


	/* 스레드 생성 실패 시 테스트 중단 */
	hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, &ThreadID);
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("CreateThread 실패 : ", GetLastError()));
		strcpy(buf, "CreateThread 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateThread 성공", msg);

		return FALSE;
	}

	result = GetThreadIdealProcessorEx(hThread, &IdealProcessor);

	
	if(result){
		sprintf(msg, "GetThreadIdealProcessorEx 성공 : IdealProcessor.Number = %d, IdealProcessor.Group = %d", IdealProcessor.Number, IdealProcessor.Group);
		strcpy(buf, "GetThreadIdealProcessorEx 성공");

	}else{
		sprintf(msg, GetErrorMessage("GetThreadIdealProcessorEx 실패 :", GetLastError()));
		strcpy(buf, "GetThreadIdealProcessorEx 실패 :");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetThreadIdealProcessorEx 성공", msg);

	CloseHandle(hThread);

	return result;
}


/**
* DWORD APIENTRY EnableThreadProfiling(
  _In_  HANDLE  ThreadHandle,
  _In_  DWORD   Flags,
  _In_  DWORD64 HardwareCounters,
  _Out_ HANDLE  PerformanceDataHandle
);
* 지정된 thread로 thread 프로파일을 유효하게 한다.
* @author : 손찬영  
*
* @param  ThreadHandle				프로파일링을 가능하게 하고 싶은 thread의 핸들
* @param  Flags						컨텍스트 전환 수와 같은 스레드 프로파일링 데이터를 받으려면 이 매개 변수를 THREAD_PROFILING_FLAG_DISPATCH
* @param  HardwareCounters			하드웨어 성능 카운터 데이터를 받으려면 수집 할 하드웨어 카운터를 식별하는 비트 마스크로 이 매개 변수를 설정
* @param  PerformanceDataHandle		ReadThreadProfilingData 및 DisableThreadProfiling 함수를 호출 할 때 사용하는 불투명한 핸들
* @return							호출이 성공하면 ERROR_SUCCESS를 반환, 실패 시 시스템 오류 코드
*/
BOOL test_EnableThreadProfiling()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hThread = NULL;
	HANDLE  PerformanceDataHandle = NULL;
	PERFORMANCE_DATA PerformanceData = {0, };
	DWORD ret = NULL, retRead = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* PerformanceData 구조체를 초기화한다. */
	PerformanceData.Size = sizeof(PerformanceData);
	PerformanceData.Version = PERFORMANCE_DATA_VERSION;

	/* 현재 스레드 핸들을 얻는다. */
	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("OpenThread 실패 : ", GetLastError()));
		strcpy(buf, "OpenThread 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenThread 성공", msg);

		return FALSE;
	}
	
	/* ThreadProfiling을 활성화한다. */
	ret = EnableThreadProfiling(hThread, 0, THREAD_PROFILING_FLAG_DISPATCH, &PerformanceDataHandle);

	if(ERROR_SUCCESS == ret){

		/* 가져온 PerformanceDataHandle로 스레드 프로파일링데이터를 읽어오기에 성공하면 성공 */
		retRead = ReadThreadProfilingData(PerformanceDataHandle, READ_THREAD_PROFILING_FLAG_HARDWARE_COUNTERS, &PerformanceData);
		if(ERROR_SUCCESS == retRead){
				sprintf(msg, "EnableThreadProfiling 성공 : PerformanceDataHandle = %d", PerformanceDataHandle);
				strcpy(buf, "EnableThreadProfiling 성공");
		
		/* 읽어온 핸들로 ReadThreadProfilingData 실패 */
		}else{
			sprintf(msg, GetErrorMessage("ReadThreadProfilingData 실패, (Winerror.h) : ", retRead));
			strcpy(buf, "ReadThreadProfilingData 실패");

			result = FALSE;
		}

	/* EnableThreadProfiling함수 실패 */
	}else{
		sprintf(msg, GetErrorMessage("EnableThreadProfiling 실패, (Winerror.h) : ", ret));
		strcpy(buf, "EnableThreadProfiling 실패");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "EnableThreadProfiling 성공", msg);

	DisableThreadProfiling(PerformanceDataHandle);
	CloseHandle(hThread);

	return result;
}


/**
* DWORD APIENTRY DisableThreadProfiling(
  _In_ HANDLE PerformanceDataHandle
);
* 스레드 프로파일링을 비활성화한다.
* @author : 손찬영  
*
* @param  PerformanceDataHandle		EnableThreadProfiling 함수가 반환 한 핸들
* @return							호출이 성공하면 ERROR_SUCCESS를 반환, 실패 시 시스템 오류 코드
*/
BOOL test_DisableThreadProfiling()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hThread = NULL;
	HANDLE  PerformanceDataHandle = NULL;
	DWORD ret = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* 현재 스레드 핸들을 얻는다. */
	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("OpenThread 실패 : ", GetLastError()));
		strcpy(buf, "OpenThread 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenThread 성공", msg);

		return FALSE;
	}

	/* enable 전에 diable 성공 시 테스트 실패 */
	ret = DisableThreadProfiling(PerformanceDataHandle);
	if(ERROR_SUCCESS == ret){
		sprintf(msg, "DisableThreadProfiling 성공 : Enable 전에는 Disable이 실패해야 함");
		strcpy(buf, "DisableThreadProfiling 성공");

		wresult(__FILE__,__LINE__, __FUNCTION__, buf, "DisableThreadProfiling 실패", msg);
		
		return FALSE;
	}

	/* ThreadProfiling을 활성화실패 시 테스트 중단 */
	ret = EnableThreadProfiling(hThread, 0, THREAD_PROFILING_FLAG_DISPATCH, &PerformanceDataHandle);
	if(ERROR_SUCCESS != ret){
		sprintf(msg, GetErrorMessage("EnableThreadProfiling 실패, (Winerror.h) : ", ret));
		strcpy(buf, "EnableThreadProfiling 실패");

		wresult(__FILE__,__LINE__, __FUNCTION__, buf, "EnableThreadProfiling 성공", msg);
		
		return FALSE;
	}

	/* ThreadProfiling을 비활성화 한다. */
	ret = DisableThreadProfiling(PerformanceDataHandle);

	if(ERROR_SUCCESS == ret){
		strcpy(buf, "DisableThreadProfiling 성공");
		strcpy(msg, buf);

	}else{
		sprintf(msg, GetErrorMessage("DisableThreadProfiling 실패, (Winerror.h) : ", ret));
		strcpy(buf, "DisableThreadProfiling 실패");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "DisableThreadProfiling 성공", msg);

	
	CloseHandle(hThread);

	return result;
}


/**
* BOOL GetThreadGroupAffinity(
  _In_  HANDLE          hThread,
  _Out_ PGROUP_AFFINITY GroupAffinity
);
* 지정된 스레드의 프로세서 그룹 선호도를 검색한다.
* @author : 손찬영  
*
* @param  hThread			프로세서 그룹 선호도가 필요한 스레드에 대한 핸들
* @param  GroupAffinity		스레드의 그룹 선호도를 수신하는 GROUP_AFFINITY 구조체의 포인터
* @return					성공/실패 여부
*/
BOOL test_GetThreadGroupAffinity()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hThread = NULL;
	GROUP_AFFINITY GroupAffinity;


	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* 현재 스레드 핸들을 얻는다. */
	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("OpenThread 실패 : ", GetLastError()));
		strcpy(buf, "OpenThread 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenThread 성공", msg);

		return FALSE;
	}

	/* -1로 초기화 후 값이 변하는 것을 확인한다. */
	GroupAffinity.Group = -1;
	result = GetThreadGroupAffinity(hThread, &GroupAffinity);

	if(result){
		if(GroupAffinity.Group >= 0){
			sprintf(msg, "GetThreadGroupAffinity 성공 : GroupAffinity.Group = %d", GroupAffinity.Group);
			strcpy(buf, "GetThreadGroupAffinity 성공");

		/* 그룹이 0보다 작은 경우 */
		}else{
			sprintf(msg, "GetThreadGroupAffinity 실패 : 그룹 값이 0보다 작음(GroupAffinity.Group = %d)", GroupAffinity.Group);
			strcpy(buf, "GetThreadGroupAffinity 실패");

			result = FALSE;
		}

	/* 함수 실패 */
	}else{
		sprintf(msg, GetErrorMessage("GetThreadGroupAffinity 실패 : ", GetLastError()));
		strcpy(buf, "GetThreadGroupAffinity 실패");

		result = FALSE;
	}
	

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetThreadGroupAffinity 성공", msg);

	
	CloseHandle(hThread);

	return result;
}

/**
* BOOL SetThreadGroupAffinity(
  _In_            HANDLE          hThread,
  _In_      const GROUP_AFFINITY  *GroupAffinity,
  _Out_opt_       PGROUP_AFFINITY PreviousGroupAffinity
);
* 지정된 스레드에 대한 프로세서 그룹 선호도를 설정한다.
* @author : 손찬영  
*
* @param  hThread					스레드에 대한 핸들.
* @param  GroupAffinity				지정된 스레드에 사용될 프로세서 그룹 선호도를 지정 하는 GROUP_AFFINITY 구조체
* @param  PreviousGroupAffinity		스레드의 이전 그룹 선호도를 수신하는 GROUP_AFFINITY 구조체의 포인터
* @return							성공/실패 여부
*/
BOOL test_SetThreadGroupAffinity()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hThread = NULL;
	GROUP_AFFINITY GroupAffinity, newGroupAffinity;
	KAFFINITY expectMask = 2;


	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* 현재 스레드 핸들을 얻는다. */
	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("OpenThread 실패 : ", GetLastError()));
		strcpy(buf, "OpenThread 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenThread 성공", msg);

		return FALSE;
	}

	/* 현재 스레드의 GroupAffinity를 가져오기 실패 시 테스트 중단 */
	if(!GetThreadGroupAffinity(hThread, &GroupAffinity)){
		sprintf(msg, GetErrorMessage("GetThreadGroupAffinity 실패 : ", GetLastError()));
		strcpy(buf, "GetThreadGroupAffinity 실패");

		wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetThreadGroupAffinity 성공", msg);

		return FALSE;
	}
	#ifdef OQADBGPRINT
	printf("Group = %d\nMask = %08x\n", GroupAffinity.Group, GroupAffinity.Mask);
	#endif

	/* set할 GroupAffinity 구조체를 초기화 한다. */
	ZeroMemory( &newGroupAffinity, sizeof(GROUP_AFFINITY));
	newGroupAffinity = GroupAffinity;
	printf("newGroupAffinity mast = %d, group = %d\n", newGroupAffinity.Mask, newGroupAffinity.Group);

	/* set할 GroupAffinity 구조체의 Mask를 기대하는 Mask값으로 대입한다. */
	newGroupAffinity.Mask = expectMask;


	result = SetThreadGroupAffinity(hThread, &newGroupAffinity, NULL);
	if(result){
		GetThreadGroupAffinity(hThread, &GroupAffinity);
		/* Set함수가 성공하고, set한 그룹값과, get한 그룹값이 같으면 성공 */
		if(expectMask == GroupAffinity.Mask){
			sprintf(msg, "SetThreadGroupAffinity 성공 : GroupAffinity.Mask = %d", GroupAffinity.Mask);
			strcpy(buf, "SetThreadGroupAffinity 성공");

		/* set함수가 성공했으나 set 시도한 마스크과, get한 그룹값이 다르면 실패 */
		}else{
			sprintf(msg, "SetThreadGroupAffinity 실패\nGroupAffinity.Mask = %d\nexpectGroup = %d", GroupAffinity.Mask, expectMask);
			strcpy(buf, "SetThreadGroupAffinity 실패");

			result = FALSE;
		}
		
	/* 함수 실패 */
	}else{
		sprintf(msg, GetErrorMessage("SetThreadGroupAffinity 실패 : ", GetLastError()));
		strcpy(buf, "SetThreadGroupAffinity 실패");

		result = FALSE;
	}


	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "SetThreadGroupAffinity 성공", msg);

	
	CloseHandle(hThread);

	return result;
}


/**
* BOOL WINAPI GetThreadIOPendingFlag(
  _In_    HANDLE hThread,
  _Inout_ PBOOL  lpIOIsPending
);
* 지정된 스레드에 보류중인 I/O 요청이 있는지 여부를 확인한다.
* @author : 손찬영  
*
* @param  hThread					해당 스레드의 핸들
* @param  lpIOIsPending				지정된 스레드에 하나 이상의 I/O 요청이 보류 중이면 함수가 TRUE로 설정하는 변수에 대한 포인터이거나 그렇지 않으면 FALSE
* @return							성공/실패 여부
*/
BOOL test_GetThreadIOPendingFlag()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hThread = NULL;
	BOOL lpIOIsPending = FALSE;


	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	
	/* 현재 스레드 핸들을 얻는다. */
	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("OpenThread 실패 : ", GetLastError()));
		strcpy(buf, "OpenThread 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenThread 성공", msg);

		return FALSE;
	}

	result = GetThreadIOPendingFlag(hThread, &lpIOIsPending);	
	if(result){
		strcpy(buf, "GetThreadIOPendingFlag 성공");
		strcpy(msg, buf);

	}else{
		sprintf(msg, GetErrorMessage("GetThreadIOPendingFlag 실패 : ", GetLastError()));
		strcpy(buf, "GetThreadIOPendingFlag 실패");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetThreadIOPendingFlag 성공", msg);

	
	CloseHandle(hThread);

	return result;
}


/**
* BOOL WINAPI GetThreadSelectorEntry(
  _In_  HANDLE      hThread,
  _In_  DWORD       dwSelector,
  _Out_ LPLDT_ENTRY lpSelectorEntry
);
* 지정된 셀렉터 및 thread의 기술자 테이블 엔트리를 가져온다.
* @author : 손찬영  
*
* @param  hThread			지정된 셀렉터를 포함한 thread의 핸들
* @param  dwSelector		스레드의 설명자 테이블에서 조회 할 전역 또는 로컬 선택기 값	
* @param  lpSelectorEntry	지정된 셀렉터가 지정된 스레드의 디스크립터 테이블에 항목을 가지고있는 경우 디스크립터 테이블 항목의 복사본을받는 LDT_ENTRY 구조체에 대한 포인터		
* @return					성공/실패 여부, 성공 시 lpSelectorEntry 매개 변수가 가리키는 구조체는 지정된 설명자 테이블 항목의 복사본을 받음
*/
BOOL test_GetThreadSelectorEntry()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hThread = NULL;
	CONTEXT context;
	LDT_ENTRY des;


	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	
	/* 현재 스레드 핸들을 얻는다. */
	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("OpenThread 실패 : ", GetLastError()));
		strcpy(buf, "OpenThread 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenThread 성공", msg);

		return FALSE;
	}

	/* 구조체를 초기화한다. */
	context.ContextFlags = CONTEXT_SEGMENTS;

	/* GetThreadContext 실패 시 테스트 중단 */
	if(!GetThreadContext(hThread, &context)){
		strcpy(buf, "GetThreadContext 실패");
		strcpy(msg, buf);

		wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetThreadContext 성공", msg);
		return FALSE;
	}

	/* LDT_ENTRY 구조체를 -1로 초기화한다. */
	des.BaseLow = -1;
	des.HighWord.Bytes.BaseHi = -1;
	des.LimitLow = -1;
	result = GetThreadSelectorEntry(hThread, context.SegFs, &des);

	if(result){
		/* 필드 값이 모두 0 이상이면 LDT_ENTRY 구조체의 값을 가져오는데 성공했다고 판단한다. */
		if((des.BaseLow >= 0) && (des.HighWord.Bytes.BaseHi >= 0) && (des.LimitLow >= 0)){
			strcpy(buf, "GetThreadSelectorEntry 성공");
			sprintf(msg, "GetThreadSelectorEntry 성공 : des.BaseLow = %d, des.HighWord.Bytes.BaseHi= %d, des.LimitLow = %d", 
							des.BaseLow, des.HighWord.Bytes.BaseHi, des.LimitLow);
		
		/* 함수는 성공했지만 0 이하인 필드값이 존재 */
		}else{
			strcpy(buf, "GetThreadSelectorEntry 실패");
			sprintf(msg, "GetThreadSelectorEntry 실패 : des.BaseLow = %d, des.HighWord.Bytes.BaseHi= %d, des.LimitLow = %d", 
							des.BaseLow, des.HighWord.Bytes.BaseHi, des.LimitLow);

			result = FALSE;
		}

	/* 함수 실패 */
	}else{
		sprintf(msg, GetErrorMessage("GetThreadSelectorEntry 실패 : ", GetLastError()));
		strcpy(buf, "GetThreadSelectorEntry 실패");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetThreadSelectorEntry 성공", msg);

	
	CloseHandle(hThread);

	return result;
}


/**
* BOOL WINAPI SetThreadStackGuarantee(
  _Inout_ PULONG StackSizeInBytes
);
* 스택 오버 플로우 예외 발생시 사용할 수있는 호출 스레드 또는 파이버와 관련된 스택의 최소 크기를 설정합니다.
스택 오버플로 예외를 처리 할 때 유용하다.
* @author : 손찬영  
*
* @param  StackSizeInBytes	스택의 크기(바이트). 리턴 시, 이 값은 이전 스택의 크기 (바이트)로 설정
* @return					성공/실패 여부
*/
BOOL test_SetThreadStackGuarantee()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	ULONG StackSizeInBytes = 1024;

	//CONTEXT context;
	//NT_TIB *tib;
	//DWORD_PTR stackBase, stackLimit;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	result = SetThreadStackGuarantee(&StackSizeInBytes);
	
	/*GetThreadContext(GetCurrentThread(), &context);

	tib = (NT_TIB *)NtCurrentTeb();
	stackBase = (DWORD_PTR)tib->StackBase;
	stackLimit = (DWORD_PTR)tib->StackLimit;


	printf("tib->StackLimit - tib->StackBase = %d\n", (int)tib->StackLimit - (int)tib->StackBase);*/

	if(result){
		strcpy(buf, "SetThreadStackGuarantee 성공");
		strcpy(msg, buf);

	}else{
		sprintf(msg, GetErrorMessage("SetThreadStackGuarantee 실패 : ", GetLastError()));
		strcpy(buf, "SetThreadStackGuarantee 실패");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "SetThreadStackGuarantee 성공", msg);

	return result;
}


/**
* BOOL SetThreadIdealProcessorEx(
  _In_      HANDLE            hThread,
  _In_      PPROCESSOR_NUMBER lpIdealProcessor,
  _Out_opt_ PPROCESSOR_NUMBER lpPreviousIdealProcessor
);
* 지정된 스레드에 대해 이상적인 프로세서를 설정하고 필요에 따라 이전의 이상적인 프로세서를 검색한다.
* @author : 손찬영  
*
* @param  hThread					이상적인 프로세서를 설정하는 스레드 핸들
* @param  lpIdealProcessor			원하는 이상적인 프로세서의 프로세서 번호를 지정 하는 PROCESSOR_NUMBER 구조체에 대한 포인터 
* @param  lpPreviousIdealProcessor	이전의 이상적인 프로세서를 수신 하기위한 PROCESSOR_NUMBER 구조체에 대한 포인터
* @return							성공/실패 여부
*/
BOOL test_SetThreadIdealProcessorEx()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hThread = NULL;
	PROCESSOR_NUMBER Processor, expectProcessor;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif


	/* 현재 스레드 핸들을 얻는다. */
	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("OpenThread 실패 : ", GetLastError()));
		strcpy(buf, "OpenThread 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenThread 성공", msg);

		return FALSE;
	}
	/* 구조체 초기화 */
	expectProcessor.Group = 0;
	expectProcessor.Number = 3; //해당 변수 변경 시에 확인 가능
	expectProcessor.Reserved = 0;

	
	result = SetThreadIdealProcessorEx(hThread, &expectProcessor, NULL);

	/* GetThreadIdealProcessorEx 실패 시 테스트 중단 */
	if(!GetThreadIdealProcessorEx(hThread, &Processor)){
		strcpy(msg, GetErrorMessage("GetThreadIdealProcessorEx 실패 : ", GetLastError()));
		strcpy(buf, "GetThreadIdealProcessorEx 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetThreadIdealProcessorEx 성공", msg);

		return FALSE;
	}



	if(result){
		/* 함수가 성공하고 Set한 값과 Get한 값이 같음 */
		if(expectProcessor.Number == Processor.Number){
			sprintf(msg, "SetThreadProcessorEx 성공 : Number = %d", Processor.Number);
			strcpy(buf, "SetThreadProcessorEx 성공");

			/* 함수는 성공했으나 Set 시도한 값과 Get한 값이 서로 다름 */
		}else{
			sprintf(msg, "SetThreadProcessorEx 실패 : (Processor.Number = %d, expectProcessor.Number = %d)", 
				Processor.Number, expectProcessor.Number);
			strcpy(buf, "SetThreadProcessorEx 실패");

			result = FALSE;
		}

	/* SetThreadIdealProcessorEx 함수 실패 */
	}else{
		sprintf(msg, GetErrorMessage("SetThreadProcessorEx 실패 : ", GetLastError()));
		strcpy(buf, "SetThreadProcessorEx 실패");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "SetThreadProcessorEx 성공", msg);


	return result;
}


/**
* DWORD APIENTRY QueryThreadProfiling(
  _In_  HANDLE   ThreadHandle,
  _Out_ PBOOLEAN Enabled
);
* 지정된 thread로 thread 프로파일을 유효하게할지 어떨지를 결정한다.
* @author : 손찬영  
*
* @param  ThreadHandle	관심있는 스레드에 대한 핸들
* @param  Enabled		스레드 프로파일링이 지정된 스레드에 대해 사용가능하면 TRUE
* @return				성공하면 ERROR_SUCCESS를 반환, 실패 시 시스템 오류 코드
*/
BOOL test_QueryThreadProfiling()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hThread = NULL;
	DWORD ret = 0;
	BOOLEAN Enabled = 3;
	BOOL QueryEnable = FALSE, QueryDisable = FALSE;

	HANDLE  PerformanceDataHandle = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* 현재 스레드 핸들을 얻는다. */
	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("OpenThread 실패 : ", GetLastError()));
		strcpy(buf, "OpenThread 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenThread 성공", msg);

		return FALSE;
	}


	/* ThreadProfiling을 활성화한다. */
	ret = EnableThreadProfiling(hThread, 0, THREAD_PROFILING_FLAG_DISPATCH, &PerformanceDataHandle);
	if(ERROR_SUCCESS != ret){
		strcpy(msg, GetErrorMessage("EnableThreadProfiling 실패 : ", ret));
		strcpy(buf, "EnableThreadProfiling 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "EnableThreadProfiling 성공", msg);

		return FALSE;
	}
	
	/* enable 후 QueryThreadProfiling를 다시 확인 */
	ret = QueryThreadProfiling(hThread, &Enabled);
	if(ERROR_SUCCESS != ret){
		strcpy(msg, GetErrorMessage("QueryThreadProfiling 실패 : ", ret));
		strcpy(buf, "QueryThreadProfiling 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "QueryThreadProfiling 성공", msg);

		return FALSE;

	}	

	/* Enable 후, Enabled 값이 TRUE여야 함 */
	if(Enabled){
		QueryEnable = TRUE;
	}

	/* ThreadProfiling을 비활성화한다. */
	if(ERROR_SUCCESS != (ret = DisableThreadProfiling(PerformanceDataHandle))){
		strcpy(msg, GetErrorMessage("EnableThreadProfiling 실패 : ", ret));
		strcpy(buf, "EnableThreadProfiling 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "EnableThreadProfiling 성공", msg);

		return FALSE;
	}

	/* disable 후 QueryThreadProfiling를 다시 확인 */
	ret = QueryThreadProfiling(hThread, &Enabled);
	if(ERROR_SUCCESS != ret){
		strcpy(msg, GetErrorMessage("QueryThreadProfiling 실패 : ", ret));
		strcpy(buf, "QueryThreadProfiling 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "QueryThreadProfiling 성공", msg);

		return FALSE;

	}	

	/* disable 후, Enabled 값이 FALSE여야 함 */
	if(!Enabled){
		QueryDisable = TRUE;
	}

	/* enable, disable에 따라 값을 정확히 가져온 경우  성공으로 판단 */
	if(QueryEnable && QueryDisable){

		strcpy(msg, "QueryThreadProfiling 성공 : QueryEnable = TRUE, QueryDisable = TRUE");
		strcpy(buf, "QueryThreadProfiling 성공");

	/* 둘 중 하나라도 값을 잘못 가져온 경우는 실패 */
	}else{
		sprintf(msg, "QueryThreadProfiling 실패 : QueryEnable = %s, QueryDisable = %s", 
			QueryEnable?"TRUE":"FALSE", QueryDisable?"TRUE":"FALSE");
		strcpy(buf, "QueryThreadProfiling 실패");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "QueryThreadProfiling 성공", msg);

	
	CloseHandle(hThread);
	 

	return result;
}

/**
* BOOL WINAPI QueryThreadCycleTime(
  _In_  HANDLE   ThreadHandle,
  _Out_ PULONG64 CycleTime
);
* 지정된 thread의 사이클 시간을 가져온다.
* @author : 손찬영  
*
* @param  ThreadHandle	스레드에 대한 핸들
* @param  CycleTime		스레드가 사용하는 CPU 클럭 사이클 수
* @return				성공/실패 여부
*/
BOOL test_QueryThreadCycleTime()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hThread = NULL;
	ULONG64 CycleTime = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif


	/* 현재 스레드 핸들을 얻는다. */
	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("OpenThread 실패 : ", GetLastError()));
		strcpy(buf, "OpenThread 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenThread 성공", msg);

		return FALSE;
	}

	result = QueryThreadCycleTime(hThread, &CycleTime);

	if(result){
		/* 함수가 성공하고 사이클타임이 0보다 크면 성공으로 판단한다. */
		if(CycleTime > 0){
			sprintf(msg, "QueryThreadCycleTime 성공 : CycleTime = %u", CycleTime);
			strcpy(buf, "QueryThreadCycleTime 성공");

		/* 함수가 성공했지만 사이클타임이 0 이하인 경우 실패 */
		}else{
			sprintf(msg, "QueryThreadCycleTime 실패 : CycleTime = %u", CycleTime);
			strcpy(buf, "QueryThreadCycleTime 실패");

			result = FALSE;
		}

	/* 함수 실패 */
	}else{
		strcpy(msg, GetErrorMessage("QueryThreadCycleTime 실패 : ", GetLastError()));
		strcpy(buf, "QueryThreadCycleTime 실패");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "QueryThreadCycleTime 성공", msg);

	CloseHandle(hThread);

	return result;
}
