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
* ������ thread�� ������ ��´�.
* @author : ������  
*
* @param  hThread	���ؽ�Ʈ�� �˻��� �������� �ڵ�
* @param  lpContext ������ �������� ������ ���ؽ�Ʈ�� ���� �ϴ� CONTEXT ����ü�� ������
* @return ����/���� ����
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

	/* ������ ���� ���� �� �׽�Ʈ �ߴ� */
	hThread = CreateThread(NULL, 0, &ThreadProc, NULL, 0, NULL);
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("CreateThread ���� : ", GetLastError()));
		strcpy(buf, "CreateThread ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateThread ����", msg);

		return FALSE;
	}

	/* Context ����ü �ʱ�ȭ */
	memset(&context, 0, sizeof(context));
	memset(&expectContext, 0, sizeof(expectContext));


	/* context ������ �������� �����ϸ� �׽�Ʈ ���� */
	if(!GetThreadContext(hThread, &context)){
		strcpy(msg, GetErrorMessage("GetThreadContext ���� : ", GetLastError()));
		strcpy(buf, "GetThreadContext ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetThreadContext ����", msg);

		return FALSE;
	}

	
	//memcpy(&expectContext, &context, sizeof(context));
	//expectContext.ContextFlags = 2;

	///* ����ϴ� Context�� Set�Ѵ�. ���н� �׽�Ʈ �ߴ� */
	//if(!SetThreadContext(hThread, &expectContext)){
	//	strcpy(msg, GetErrorMessage("SetThreadContext ���� : ", GetLastError()));
	//	strcpy(buf, "SetThreadContext ����");
	//
	//	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetThreadContext ����", msg);

	//	return FALSE;
	//}

	/* expectContext�� ���ؽ�Ʈ ������ �����´�. */
	if(!GetThreadContext(hThread, &expectContext)){
		strcpy(msg, GetErrorMessage("GetThreadContext ���� : ", GetLastError()));
		strcpy(buf, "GetThreadContext ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetThreadContext ����", msg);

		return FALSE;
	}

	/* expectContext�� context�� �����ϸ� �������� �Ǵ��Ѵ�. */
	if(!memcmp(&expectContext, &context, sizeof(context))){
		sprintf(msg, "GetThreadContext ���� : context.ContextFlags = %d", context.ContextFlags);
		strcpy(buf, "GetThreadContext ����");

	/* expectContext�� context�� ���� �ٸ� ���⼭ ContextFlags���� Ȯ�� */
	}else{
		sprintf(msg, "GetThreadContext ���� : context.ContextFlags = %d, expectContext.ContextFlags = %d", context.ContextFlags, expectContext.ContextFlags);
		strcpy(buf, "GetThreadContext ����");

		result = FALSE;	
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetThreadContext ����", msg);

	CloseHandle(hThread);	

	return result;
}

/**
* BOOL SetThreadLocale(
  _In_ LCID Locale
);
* ȣ���ϴ� thread�� ������ �������� �����Ѵ�.
* @author : ������  
*
* @param  Locale	������ �� �����ϴ� ������ �ĺ���. LOCALE_CUSTOM_DEFAULT ��.
* @return ����/���� ����
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

	/* �ʱ� �������� �����´� */
	locale = GetThreadLocale();

	/* ����ϴ� ������ ���� ���� �����ϰ� + 1�� �����Ѵ� */
	expectLocale = locale+1;

	/* SetThreadLocale �Լ� ���� */
	if(!SetThreadLocale(expectLocale)){
		strcpy(msg, GetErrorMessage("SetThreadLocale ���� : ", GetLastError()));
		strcpy(buf, "SetThreadLocale ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetThreadLocale ����", msg);

		return FALSE;
	}

	/* Set�� �� �ٽ� �������� �����´� */
	changeLocale = GetThreadLocale();

	/* ���ϴ� locale������ set ���� */
	if(expectLocale == changeLocale){
		sprintf(msg, "SetThreadLocale ���� : originLocale = %d, changeLocale = %d", locale, changeLocale);
		strcpy(buf, "SetThreadLocale ����");

	/* ���ϴ� locale������ set ���� */
	}else{
		sprintf(msg, "SetThreadLocale ���� : changeLocale = %d, expectLocale = %d", changeLocale, expectLocale);
		strcpy(buf, "SetThreadLocale ����");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "SetThreadLocale ����", msg);


	/* ���� �����Ϸ� ���� �� ���� */
	SetThreadLocale(locale);

	return result;
}


/**
* EXECUTION_STATE WINAPI SetThreadExecutionState(
  _In_ EXECUTION_STATE esFlags
);
* ���� ���α׷��� ��� ������ �ý��ۿ� �˸���. 
���� ���α׷��� ����Ǵ� ���� �ý����� ���� ���� ���ų� ���÷��̰� ������ ���� ���� �� �� �ִ�.
* @author : ������  
*
* @param  esFlags	�������� ���� �䱸 ����. ES_AWAYMODE_REQUIRED ��.
* @return �����ϸ� ��ȯ ���� �������� ���� ���� ����, ���� �� NULL
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
		strcpy(msg, "SetThreadExecutionState ����");
		strcpy(buf, msg);
	
	}else{ //���� ������� ����
		strcpy(msg, GetErrorMessage("SetThreadExecutionState ���� : ", GetLastError()));
		strcpy(buf, "SetThreadExecutionState ����");

		result = FALSE;	
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "SetThreadExecutionState ����", msg);

	return result;
}

/**
* DWORD WINAPI Wow64SuspendThread(
  _In_ HANDLE hThread
);
* ������ WOW64 �����带 �Ͻ� �ߴ��Ѵ�.
* @author : ������  
*
* @param  hThread	�Ͻ� �ߴ� �� �������� �ڵ�
* @return �����ϸ� ��ȯ ���� �������� ���� �Ͻ� �ߴ� Ƚ��, ���� �� -1
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

	
	/* ������ ���� ���� �� �׽�Ʈ �ߴ� */
	hThread = CreateThread(NULL, 0, ThreadWow64Suspend, NULL, 0, &ThreadID);
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("CreateThread ���� : ", GetLastError()));
		strcpy(buf, "CreateThread ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateThread ����", msg);

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
		sprintf(msg, "Wow64SuspendThread ���� : suspnedCount = %d", suspendCount);
		strcpy(buf, "Wow64SuspendThread ����");

	}else{
		sprintf(msg, "Wow64SuspendThread ����\nsuspnedCount = %d", suspendCount);
		strcpy(buf, "Wow64SuspendThread ����");

		result = FALSE;
	}
	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "Wow64SuspendThread ����", msg);

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
* ������ thread�� thread �ĺ��ڸ� �����´�.
* @author : ������  
*
* @param  Thread	�����忡 ���� �ڵ�
* @return �����ϸ� ��ȯ ���� ������ID, ���� �� 0
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

	/* ������ ���� ���� �� �׽�Ʈ �ߴ� */
	hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, &expectThreadID);
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("CreateThread ���� : ", GetLastError()));
		strcpy(buf, "CreateThread ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateThread ����", msg);

		return FALSE;
	}

	ThreadID = GetThreadId(hThread);
	if(NULL != ThreadID){
		/* ������ ���̵� ���� ��� �������� �Ǵ� */
		if(expectThreadID == ThreadID){
			sprintf(msg, "GetThreadId ���� : ThreadID = %d", ThreadID, expectThreadID);
			strcpy(buf, "GetThreadId ����");

		/* �Լ��� ���������� ������ ���̵� ���� �ٸ� */
		}else{
			sprintf(msg, "GetThreadId ����\nThreadID = %d\nexpectThreadID = %d", ThreadID, expectThreadID);
			strcpy(buf, "GetThreadId ����");

			result = FALSE;
		}

	/* �Լ� ���� */
	}else{
		strcpy(msg, GetErrorMessage("GetThreadId ���� : ", GetLastError()));
		strcpy(buf, "GetThreadId ����");

		result = FALSE;
	}

	#ifdef OQADBGPRINT
	printf("expectThreadID = %d\nThreadID = %d\n", expectThreadID, ThreadID);
	#endif
	
	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetThreadId ����", msg);

	CloseHandle(hThread);

	return result;
}

/**
* DWORD WINAPI GetProcessIdOfThread(
  _In_ HANDLE Thread
);
* ������ thread�� ������ ���μ����� ���μ��� �ĺ��ڸ� �����´�.
* @author : ������  
*
* @param  Thread	�����忡 ���� �ڵ�
* @return �����ϸ� ��ȯ ���� ������� ������ ���μ����� ���μ��� ID, ���� �� 0
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

	/* ���� ���μ����� �ǻ� �ڵ��� �����´�. */
	hCurrentProcess = GetCurrentProcess();

	/* ���� ���μ����� ID�� �������� ���ϸ� �׽�Ʈ �ߴ� */
	expectProcessID = GetProcessId(hCurrentProcess);
	if(NULL == expectProcessID){
		strcpy(msg, GetErrorMessage("GetProcessId ���� : ", GetLastError()));
		strcpy(buf, "GetProcessId ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetProcessId ����", msg);

		return FALSE;
	}

	/* ������ ���� ���� �� �׽�Ʈ �ߴ� */
	hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, &ThreadID);
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("CreateThread ���� : ", GetLastError()));
		strcpy(buf, "CreateThread ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateThread ����", msg);

		return FALSE;
	}

	/* ������ �������� ���μ��� ID�� �����´�. */
	ProcessID = GetProcessIdOfThread(hThread);
	if(NULL != ProcessID){
		/* ���μ��� ���� �����ϸ� ���� */
		if(expectProcessID == ProcessID){
			sprintf(msg, "GetProcessIdOfThread ���� : ProcessID = %d", ProcessID, expectProcessID);
			strcpy(buf, "GetProcessIdOfThread ����");

		/* �Լ��� ���������� ���μ������� �������� ���� */
		}else{
			sprintf(msg, "GetProcessIdOfThread ����\nProcessID = %d\nexpectProcessID = %d", ProcessID, expectProcessID);
			strcpy(buf, "GetProcessIdOfThread ����");

			result = FALSE;
		}

	/* �Լ� ���� */
	}else{
		strcpy(msg, GetErrorMessage("GetProcessIdOfThread ���� : ", GetLastError()));
		strcpy(buf, "GetProcessIdOfThread ����");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetProcessIdOfThread ����", msg);

	CloseHandle(hThread);

	return result;
}

/**
* BOOL GetThreadIdealProcessorEx(
  _In_  HANDLE            hThread,
  _Out_ PPROCESSOR_NUMBER lpIdealProcessor
);
* ������ thread�� �̻����� ���μ����� ���μ��� ��ȣ
* @author : ������  
*
* @param  Thread			�̻����� ���μ����� �˻� �� ������ �ڵ�
* @param  lpIdealProcessor	�̻����� ���μ��� ��ȣ�� �ޱ� ���� PROCESSOR_NUMBER ����ü�� ������
* @return					����/���� ����
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


	/* ������ ���� ���� �� �׽�Ʈ �ߴ� */
	hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, &ThreadID);
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("CreateThread ���� : ", GetLastError()));
		strcpy(buf, "CreateThread ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateThread ����", msg);

		return FALSE;
	}

	result = GetThreadIdealProcessorEx(hThread, &IdealProcessor);

	
	if(result){
		sprintf(msg, "GetThreadIdealProcessorEx ���� : IdealProcessor.Number = %d, IdealProcessor.Group = %d", IdealProcessor.Number, IdealProcessor.Group);
		strcpy(buf, "GetThreadIdealProcessorEx ����");

	}else{
		sprintf(msg, GetErrorMessage("GetThreadIdealProcessorEx ���� :", GetLastError()));
		strcpy(buf, "GetThreadIdealProcessorEx ���� :");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetThreadIdealProcessorEx ����", msg);

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
* ������ thread�� thread ���������� ��ȿ�ϰ� �Ѵ�.
* @author : ������  
*
* @param  ThreadHandle				�������ϸ��� �����ϰ� �ϰ� ���� thread�� �ڵ�
* @param  Flags						���ؽ�Ʈ ��ȯ ���� ���� ������ �������ϸ� �����͸� �������� �� �Ű� ������ THREAD_PROFILING_FLAG_DISPATCH
* @param  HardwareCounters			�ϵ���� ���� ī���� �����͸� �������� ���� �� �ϵ���� ī���͸� �ĺ��ϴ� ��Ʈ ����ũ�� �� �Ű� ������ ����
* @param  PerformanceDataHandle		ReadThreadProfilingData �� DisableThreadProfiling �Լ��� ȣ�� �� �� ����ϴ� �������� �ڵ�
* @return							ȣ���� �����ϸ� ERROR_SUCCESS�� ��ȯ, ���� �� �ý��� ���� �ڵ�
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

	/* PerformanceData ����ü�� �ʱ�ȭ�Ѵ�. */
	PerformanceData.Size = sizeof(PerformanceData);
	PerformanceData.Version = PERFORMANCE_DATA_VERSION;

	/* ���� ������ �ڵ��� ��´�. */
	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("OpenThread ���� : ", GetLastError()));
		strcpy(buf, "OpenThread ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenThread ����", msg);

		return FALSE;
	}
	
	/* ThreadProfiling�� Ȱ��ȭ�Ѵ�. */
	ret = EnableThreadProfiling(hThread, 0, THREAD_PROFILING_FLAG_DISPATCH, &PerformanceDataHandle);

	if(ERROR_SUCCESS == ret){

		/* ������ PerformanceDataHandle�� ������ �������ϸ������͸� �о���⿡ �����ϸ� ���� */
		retRead = ReadThreadProfilingData(PerformanceDataHandle, READ_THREAD_PROFILING_FLAG_HARDWARE_COUNTERS, &PerformanceData);
		if(ERROR_SUCCESS == retRead){
				sprintf(msg, "EnableThreadProfiling ���� : PerformanceDataHandle = %d", PerformanceDataHandle);
				strcpy(buf, "EnableThreadProfiling ����");
		
		/* �о�� �ڵ�� ReadThreadProfilingData ���� */
		}else{
			sprintf(msg, GetErrorMessage("ReadThreadProfilingData ����, (Winerror.h) : ", retRead));
			strcpy(buf, "ReadThreadProfilingData ����");

			result = FALSE;
		}

	/* EnableThreadProfiling�Լ� ���� */
	}else{
		sprintf(msg, GetErrorMessage("EnableThreadProfiling ����, (Winerror.h) : ", ret));
		strcpy(buf, "EnableThreadProfiling ����");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "EnableThreadProfiling ����", msg);

	DisableThreadProfiling(PerformanceDataHandle);
	CloseHandle(hThread);

	return result;
}


/**
* DWORD APIENTRY DisableThreadProfiling(
  _In_ HANDLE PerformanceDataHandle
);
* ������ �������ϸ��� ��Ȱ��ȭ�Ѵ�.
* @author : ������  
*
* @param  PerformanceDataHandle		EnableThreadProfiling �Լ��� ��ȯ �� �ڵ�
* @return							ȣ���� �����ϸ� ERROR_SUCCESS�� ��ȯ, ���� �� �ý��� ���� �ڵ�
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

	/* ���� ������ �ڵ��� ��´�. */
	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("OpenThread ���� : ", GetLastError()));
		strcpy(buf, "OpenThread ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenThread ����", msg);

		return FALSE;
	}

	/* enable ���� diable ���� �� �׽�Ʈ ���� */
	ret = DisableThreadProfiling(PerformanceDataHandle);
	if(ERROR_SUCCESS == ret){
		sprintf(msg, "DisableThreadProfiling ���� : Enable ������ Disable�� �����ؾ� ��");
		strcpy(buf, "DisableThreadProfiling ����");

		wresult(__FILE__,__LINE__, __FUNCTION__, buf, "DisableThreadProfiling ����", msg);
		
		return FALSE;
	}

	/* ThreadProfiling�� Ȱ��ȭ���� �� �׽�Ʈ �ߴ� */
	ret = EnableThreadProfiling(hThread, 0, THREAD_PROFILING_FLAG_DISPATCH, &PerformanceDataHandle);
	if(ERROR_SUCCESS != ret){
		sprintf(msg, GetErrorMessage("EnableThreadProfiling ����, (Winerror.h) : ", ret));
		strcpy(buf, "EnableThreadProfiling ����");

		wresult(__FILE__,__LINE__, __FUNCTION__, buf, "EnableThreadProfiling ����", msg);
		
		return FALSE;
	}

	/* ThreadProfiling�� ��Ȱ��ȭ �Ѵ�. */
	ret = DisableThreadProfiling(PerformanceDataHandle);

	if(ERROR_SUCCESS == ret){
		strcpy(buf, "DisableThreadProfiling ����");
		strcpy(msg, buf);

	}else{
		sprintf(msg, GetErrorMessage("DisableThreadProfiling ����, (Winerror.h) : ", ret));
		strcpy(buf, "DisableThreadProfiling ����");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "DisableThreadProfiling ����", msg);

	
	CloseHandle(hThread);

	return result;
}


/**
* BOOL GetThreadGroupAffinity(
  _In_  HANDLE          hThread,
  _Out_ PGROUP_AFFINITY GroupAffinity
);
* ������ �������� ���μ��� �׷� ��ȣ���� �˻��Ѵ�.
* @author : ������  
*
* @param  hThread			���μ��� �׷� ��ȣ���� �ʿ��� �����忡 ���� �ڵ�
* @param  GroupAffinity		�������� �׷� ��ȣ���� �����ϴ� GROUP_AFFINITY ����ü�� ������
* @return					����/���� ����
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

	/* ���� ������ �ڵ��� ��´�. */
	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("OpenThread ���� : ", GetLastError()));
		strcpy(buf, "OpenThread ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenThread ����", msg);

		return FALSE;
	}

	/* -1�� �ʱ�ȭ �� ���� ���ϴ� ���� Ȯ���Ѵ�. */
	GroupAffinity.Group = -1;
	result = GetThreadGroupAffinity(hThread, &GroupAffinity);

	if(result){
		if(GroupAffinity.Group >= 0){
			sprintf(msg, "GetThreadGroupAffinity ���� : GroupAffinity.Group = %d", GroupAffinity.Group);
			strcpy(buf, "GetThreadGroupAffinity ����");

		/* �׷��� 0���� ���� ��� */
		}else{
			sprintf(msg, "GetThreadGroupAffinity ���� : �׷� ���� 0���� ����(GroupAffinity.Group = %d)", GroupAffinity.Group);
			strcpy(buf, "GetThreadGroupAffinity ����");

			result = FALSE;
		}

	/* �Լ� ���� */
	}else{
		sprintf(msg, GetErrorMessage("GetThreadGroupAffinity ���� : ", GetLastError()));
		strcpy(buf, "GetThreadGroupAffinity ����");

		result = FALSE;
	}
	

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetThreadGroupAffinity ����", msg);

	
	CloseHandle(hThread);

	return result;
}

/**
* BOOL SetThreadGroupAffinity(
  _In_            HANDLE          hThread,
  _In_      const GROUP_AFFINITY  *GroupAffinity,
  _Out_opt_       PGROUP_AFFINITY PreviousGroupAffinity
);
* ������ �����忡 ���� ���μ��� �׷� ��ȣ���� �����Ѵ�.
* @author : ������  
*
* @param  hThread					�����忡 ���� �ڵ�.
* @param  GroupAffinity				������ �����忡 ���� ���μ��� �׷� ��ȣ���� ���� �ϴ� GROUP_AFFINITY ����ü
* @param  PreviousGroupAffinity		�������� ���� �׷� ��ȣ���� �����ϴ� GROUP_AFFINITY ����ü�� ������
* @return							����/���� ����
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

	/* ���� ������ �ڵ��� ��´�. */
	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("OpenThread ���� : ", GetLastError()));
		strcpy(buf, "OpenThread ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenThread ����", msg);

		return FALSE;
	}

	/* ���� �������� GroupAffinity�� �������� ���� �� �׽�Ʈ �ߴ� */
	if(!GetThreadGroupAffinity(hThread, &GroupAffinity)){
		sprintf(msg, GetErrorMessage("GetThreadGroupAffinity ���� : ", GetLastError()));
		strcpy(buf, "GetThreadGroupAffinity ����");

		wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetThreadGroupAffinity ����", msg);

		return FALSE;
	}
	#ifdef OQADBGPRINT
	printf("Group = %d\nMask = %08x\n", GroupAffinity.Group, GroupAffinity.Mask);
	#endif

	/* set�� GroupAffinity ����ü�� �ʱ�ȭ �Ѵ�. */
	ZeroMemory( &newGroupAffinity, sizeof(GROUP_AFFINITY));
	newGroupAffinity = GroupAffinity;
	printf("newGroupAffinity mast = %d, group = %d\n", newGroupAffinity.Mask, newGroupAffinity.Group);

	/* set�� GroupAffinity ����ü�� Mask�� ����ϴ� Mask������ �����Ѵ�. */
	newGroupAffinity.Mask = expectMask;


	result = SetThreadGroupAffinity(hThread, &newGroupAffinity, NULL);
	if(result){
		GetThreadGroupAffinity(hThread, &GroupAffinity);
		/* Set�Լ��� �����ϰ�, set�� �׷찪��, get�� �׷찪�� ������ ���� */
		if(expectMask == GroupAffinity.Mask){
			sprintf(msg, "SetThreadGroupAffinity ���� : GroupAffinity.Mask = %d", GroupAffinity.Mask);
			strcpy(buf, "SetThreadGroupAffinity ����");

		/* set�Լ��� ���������� set �õ��� ����ũ��, get�� �׷찪�� �ٸ��� ���� */
		}else{
			sprintf(msg, "SetThreadGroupAffinity ����\nGroupAffinity.Mask = %d\nexpectGroup = %d", GroupAffinity.Mask, expectMask);
			strcpy(buf, "SetThreadGroupAffinity ����");

			result = FALSE;
		}
		
	/* �Լ� ���� */
	}else{
		sprintf(msg, GetErrorMessage("SetThreadGroupAffinity ���� : ", GetLastError()));
		strcpy(buf, "SetThreadGroupAffinity ����");

		result = FALSE;
	}


	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "SetThreadGroupAffinity ����", msg);

	
	CloseHandle(hThread);

	return result;
}


/**
* BOOL WINAPI GetThreadIOPendingFlag(
  _In_    HANDLE hThread,
  _Inout_ PBOOL  lpIOIsPending
);
* ������ �����忡 �������� I/O ��û�� �ִ��� ���θ� Ȯ���Ѵ�.
* @author : ������  
*
* @param  hThread					�ش� �������� �ڵ�
* @param  lpIOIsPending				������ �����忡 �ϳ� �̻��� I/O ��û�� ���� ���̸� �Լ��� TRUE�� �����ϴ� ������ ���� �������̰ų� �׷��� ������ FALSE
* @return							����/���� ����
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

	
	/* ���� ������ �ڵ��� ��´�. */
	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("OpenThread ���� : ", GetLastError()));
		strcpy(buf, "OpenThread ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenThread ����", msg);

		return FALSE;
	}

	result = GetThreadIOPendingFlag(hThread, &lpIOIsPending);	
	if(result){
		strcpy(buf, "GetThreadIOPendingFlag ����");
		strcpy(msg, buf);

	}else{
		sprintf(msg, GetErrorMessage("GetThreadIOPendingFlag ���� : ", GetLastError()));
		strcpy(buf, "GetThreadIOPendingFlag ����");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetThreadIOPendingFlag ����", msg);

	
	CloseHandle(hThread);

	return result;
}


/**
* BOOL WINAPI GetThreadSelectorEntry(
  _In_  HANDLE      hThread,
  _In_  DWORD       dwSelector,
  _Out_ LPLDT_ENTRY lpSelectorEntry
);
* ������ ������ �� thread�� ����� ���̺� ��Ʈ���� �����´�.
* @author : ������  
*
* @param  hThread			������ �����͸� ������ thread�� �ڵ�
* @param  dwSelector		�������� ������ ���̺��� ��ȸ �� ���� �Ǵ� ���� ���ñ� ��	
* @param  lpSelectorEntry	������ �����Ͱ� ������ �������� ��ũ���� ���̺� �׸��� �������ִ� ��� ��ũ���� ���̺� �׸��� ���纻���޴� LDT_ENTRY ����ü�� ���� ������		
* @return					����/���� ����, ���� �� lpSelectorEntry �Ű� ������ ����Ű�� ����ü�� ������ ������ ���̺� �׸��� ���纻�� ����
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

	
	/* ���� ������ �ڵ��� ��´�. */
	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("OpenThread ���� : ", GetLastError()));
		strcpy(buf, "OpenThread ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenThread ����", msg);

		return FALSE;
	}

	/* ����ü�� �ʱ�ȭ�Ѵ�. */
	context.ContextFlags = CONTEXT_SEGMENTS;

	/* GetThreadContext ���� �� �׽�Ʈ �ߴ� */
	if(!GetThreadContext(hThread, &context)){
		strcpy(buf, "GetThreadContext ����");
		strcpy(msg, buf);

		wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetThreadContext ����", msg);
		return FALSE;
	}

	/* LDT_ENTRY ����ü�� -1�� �ʱ�ȭ�Ѵ�. */
	des.BaseLow = -1;
	des.HighWord.Bytes.BaseHi = -1;
	des.LimitLow = -1;
	result = GetThreadSelectorEntry(hThread, context.SegFs, &des);

	if(result){
		/* �ʵ� ���� ��� 0 �̻��̸� LDT_ENTRY ����ü�� ���� �������µ� �����ߴٰ� �Ǵ��Ѵ�. */
		if((des.BaseLow >= 0) && (des.HighWord.Bytes.BaseHi >= 0) && (des.LimitLow >= 0)){
			strcpy(buf, "GetThreadSelectorEntry ����");
			sprintf(msg, "GetThreadSelectorEntry ���� : des.BaseLow = %d, des.HighWord.Bytes.BaseHi= %d, des.LimitLow = %d", 
							des.BaseLow, des.HighWord.Bytes.BaseHi, des.LimitLow);
		
		/* �Լ��� ���������� 0 ������ �ʵ尪�� ���� */
		}else{
			strcpy(buf, "GetThreadSelectorEntry ����");
			sprintf(msg, "GetThreadSelectorEntry ���� : des.BaseLow = %d, des.HighWord.Bytes.BaseHi= %d, des.LimitLow = %d", 
							des.BaseLow, des.HighWord.Bytes.BaseHi, des.LimitLow);

			result = FALSE;
		}

	/* �Լ� ���� */
	}else{
		sprintf(msg, GetErrorMessage("GetThreadSelectorEntry ���� : ", GetLastError()));
		strcpy(buf, "GetThreadSelectorEntry ����");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetThreadSelectorEntry ����", msg);

	
	CloseHandle(hThread);

	return result;
}


/**
* BOOL WINAPI SetThreadStackGuarantee(
  _Inout_ PULONG StackSizeInBytes
);
* ���� ���� �÷ο� ���� �߻��� ����� ���ִ� ȣ�� ������ �Ǵ� ���̹��� ���õ� ������ �ּ� ũ�⸦ �����մϴ�.
���� �����÷� ���ܸ� ó�� �� �� �����ϴ�.
* @author : ������  
*
* @param  StackSizeInBytes	������ ũ��(����Ʈ). ���� ��, �� ���� ���� ������ ũ�� (����Ʈ)�� ����
* @return					����/���� ����
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
		strcpy(buf, "SetThreadStackGuarantee ����");
		strcpy(msg, buf);

	}else{
		sprintf(msg, GetErrorMessage("SetThreadStackGuarantee ���� : ", GetLastError()));
		strcpy(buf, "SetThreadStackGuarantee ����");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "SetThreadStackGuarantee ����", msg);

	return result;
}


/**
* BOOL SetThreadIdealProcessorEx(
  _In_      HANDLE            hThread,
  _In_      PPROCESSOR_NUMBER lpIdealProcessor,
  _Out_opt_ PPROCESSOR_NUMBER lpPreviousIdealProcessor
);
* ������ �����忡 ���� �̻����� ���μ����� �����ϰ� �ʿ信 ���� ������ �̻����� ���μ����� �˻��Ѵ�.
* @author : ������  
*
* @param  hThread					�̻����� ���μ����� �����ϴ� ������ �ڵ�
* @param  lpIdealProcessor			���ϴ� �̻����� ���μ����� ���μ��� ��ȣ�� ���� �ϴ� PROCESSOR_NUMBER ����ü�� ���� ������ 
* @param  lpPreviousIdealProcessor	������ �̻����� ���μ����� ���� �ϱ����� PROCESSOR_NUMBER ����ü�� ���� ������
* @return							����/���� ����
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


	/* ���� ������ �ڵ��� ��´�. */
	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("OpenThread ���� : ", GetLastError()));
		strcpy(buf, "OpenThread ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenThread ����", msg);

		return FALSE;
	}
	/* ����ü �ʱ�ȭ */
	expectProcessor.Group = 0;
	expectProcessor.Number = 3; //�ش� ���� ���� �ÿ� Ȯ�� ����
	expectProcessor.Reserved = 0;

	
	result = SetThreadIdealProcessorEx(hThread, &expectProcessor, NULL);

	/* GetThreadIdealProcessorEx ���� �� �׽�Ʈ �ߴ� */
	if(!GetThreadIdealProcessorEx(hThread, &Processor)){
		strcpy(msg, GetErrorMessage("GetThreadIdealProcessorEx ���� : ", GetLastError()));
		strcpy(buf, "GetThreadIdealProcessorEx ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetThreadIdealProcessorEx ����", msg);

		return FALSE;
	}



	if(result){
		/* �Լ��� �����ϰ� Set�� ���� Get�� ���� ���� */
		if(expectProcessor.Number == Processor.Number){
			sprintf(msg, "SetThreadProcessorEx ���� : Number = %d", Processor.Number);
			strcpy(buf, "SetThreadProcessorEx ����");

			/* �Լ��� ���������� Set �õ��� ���� Get�� ���� ���� �ٸ� */
		}else{
			sprintf(msg, "SetThreadProcessorEx ���� : (Processor.Number = %d, expectProcessor.Number = %d)", 
				Processor.Number, expectProcessor.Number);
			strcpy(buf, "SetThreadProcessorEx ����");

			result = FALSE;
		}

	/* SetThreadIdealProcessorEx �Լ� ���� */
	}else{
		sprintf(msg, GetErrorMessage("SetThreadProcessorEx ���� : ", GetLastError()));
		strcpy(buf, "SetThreadProcessorEx ����");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "SetThreadProcessorEx ����", msg);


	return result;
}


/**
* DWORD APIENTRY QueryThreadProfiling(
  _In_  HANDLE   ThreadHandle,
  _Out_ PBOOLEAN Enabled
);
* ������ thread�� thread ���������� ��ȿ�ϰ����� ����� �����Ѵ�.
* @author : ������  
*
* @param  ThreadHandle	�����ִ� �����忡 ���� �ڵ�
* @param  Enabled		������ �������ϸ��� ������ �����忡 ���� ��밡���ϸ� TRUE
* @return				�����ϸ� ERROR_SUCCESS�� ��ȯ, ���� �� �ý��� ���� �ڵ�
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

	/* ���� ������ �ڵ��� ��´�. */
	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("OpenThread ���� : ", GetLastError()));
		strcpy(buf, "OpenThread ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenThread ����", msg);

		return FALSE;
	}


	/* ThreadProfiling�� Ȱ��ȭ�Ѵ�. */
	ret = EnableThreadProfiling(hThread, 0, THREAD_PROFILING_FLAG_DISPATCH, &PerformanceDataHandle);
	if(ERROR_SUCCESS != ret){
		strcpy(msg, GetErrorMessage("EnableThreadProfiling ���� : ", ret));
		strcpy(buf, "EnableThreadProfiling ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "EnableThreadProfiling ����", msg);

		return FALSE;
	}
	
	/* enable �� QueryThreadProfiling�� �ٽ� Ȯ�� */
	ret = QueryThreadProfiling(hThread, &Enabled);
	if(ERROR_SUCCESS != ret){
		strcpy(msg, GetErrorMessage("QueryThreadProfiling ���� : ", ret));
		strcpy(buf, "QueryThreadProfiling ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "QueryThreadProfiling ����", msg);

		return FALSE;

	}	

	/* Enable ��, Enabled ���� TRUE���� �� */
	if(Enabled){
		QueryEnable = TRUE;
	}

	/* ThreadProfiling�� ��Ȱ��ȭ�Ѵ�. */
	if(ERROR_SUCCESS != (ret = DisableThreadProfiling(PerformanceDataHandle))){
		strcpy(msg, GetErrorMessage("EnableThreadProfiling ���� : ", ret));
		strcpy(buf, "EnableThreadProfiling ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "EnableThreadProfiling ����", msg);

		return FALSE;
	}

	/* disable �� QueryThreadProfiling�� �ٽ� Ȯ�� */
	ret = QueryThreadProfiling(hThread, &Enabled);
	if(ERROR_SUCCESS != ret){
		strcpy(msg, GetErrorMessage("QueryThreadProfiling ���� : ", ret));
		strcpy(buf, "QueryThreadProfiling ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "QueryThreadProfiling ����", msg);

		return FALSE;

	}	

	/* disable ��, Enabled ���� FALSE���� �� */
	if(!Enabled){
		QueryDisable = TRUE;
	}

	/* enable, disable�� ���� ���� ��Ȯ�� ������ ���  �������� �Ǵ� */
	if(QueryEnable && QueryDisable){

		strcpy(msg, "QueryThreadProfiling ���� : QueryEnable = TRUE, QueryDisable = TRUE");
		strcpy(buf, "QueryThreadProfiling ����");

	/* �� �� �ϳ��� ���� �߸� ������ ���� ���� */
	}else{
		sprintf(msg, "QueryThreadProfiling ���� : QueryEnable = %s, QueryDisable = %s", 
			QueryEnable?"TRUE":"FALSE", QueryDisable?"TRUE":"FALSE");
		strcpy(buf, "QueryThreadProfiling ����");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "QueryThreadProfiling ����", msg);

	
	CloseHandle(hThread);
	 

	return result;
}

/**
* BOOL WINAPI QueryThreadCycleTime(
  _In_  HANDLE   ThreadHandle,
  _Out_ PULONG64 CycleTime
);
* ������ thread�� ����Ŭ �ð��� �����´�.
* @author : ������  
*
* @param  ThreadHandle	�����忡 ���� �ڵ�
* @param  CycleTime		�����尡 ����ϴ� CPU Ŭ�� ����Ŭ ��
* @return				����/���� ����
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


	/* ���� ������ �ڵ��� ��´�. */
	hThread = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
	if(NULL == hThread){
		strcpy(msg, GetErrorMessage("OpenThread ���� : ", GetLastError()));
		strcpy(buf, "OpenThread ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenThread ����", msg);

		return FALSE;
	}

	result = QueryThreadCycleTime(hThread, &CycleTime);

	if(result){
		/* �Լ��� �����ϰ� ����ŬŸ���� 0���� ũ�� �������� �Ǵ��Ѵ�. */
		if(CycleTime > 0){
			sprintf(msg, "QueryThreadCycleTime ���� : CycleTime = %u", CycleTime);
			strcpy(buf, "QueryThreadCycleTime ����");

		/* �Լ��� ���������� ����ŬŸ���� 0 ������ ��� ���� */
		}else{
			sprintf(msg, "QueryThreadCycleTime ���� : CycleTime = %u", CycleTime);
			strcpy(buf, "QueryThreadCycleTime ����");

			result = FALSE;
		}

	/* �Լ� ���� */
	}else{
		strcpy(msg, GetErrorMessage("QueryThreadCycleTime ���� : ", GetLastError()));
		strcpy(buf, "QueryThreadCycleTime ����");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "QueryThreadCycleTime ����", msg);

	CloseHandle(hThread);

	return result;
}
