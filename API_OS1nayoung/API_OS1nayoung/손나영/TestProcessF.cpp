#include "TestProcessF.h"
#include <TlHelp32.h>

BOOL test_SetProcessDEPPolicy(){
	
	BOOL result = true;
	
	char *buf = NULL;
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_SetProcessDEPPolicy\n");
	#endif

	// DEP(Data Execution Prevention) : 데이타 실행 방지
	// SetProcessDEPPolicy 함수는 32bit process를 위한 setting
	// 따라서, 현 windows 환경(64bit)에서는 fail 뜨는 것0이 정상

	// 파라미터 값 0 
	// DEP 시스템 정책이 Optln 이거나 OptOut, 또는 해당 프로세서에 DEP 사용할 때\
	// 값을 0으로 주면 → DEP가 비활성화 처리 됨
	if(SetProcessDEPPolicy(0))
		strcpy(meg, "SetProcessDEPPolicy() : SUCCESS");	
	else 
		strcpy(meg, GetErrorMessage(" SetProcessDEPPolicy() : FAIL \n\n \n(해당 함수는 32 bit 전용입니다. \n따라서 현재 테스트하고 있는 windows 환경이 \n64bit라면 fail이 정상입니다.)\n\nError Message :", GetLastError()));
		
	wresult(__FILE__, __LINE__, "SetProcessDEPPolicy", meg, "SetProcessDEPPolicy() : SUCCESS", meg);

	return true;
}

BOOL test_SetProcessAffinityUpdateMode(){

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_SetProcessAffinityUpdateMode\n");
	#endif

	// 0 : Disables dynamic update of the process affinity by the system.
	// PROCESS_AFFINITY_ENABLE_AUTO_UPDATE : Enables dynamic update of the process affinity by the system.
	// 프로세스의 유연성을 업데이트
	// 첫 번째 파라미터 : GetCurrentProcess함수 반환해야 함
	if(SetProcessAffinityUpdateMode(GetCurrentProcess(), 0)!=0){
		sprintf(meg, "SetProcessAffinityUpdateMode() : SUCCESS \n\n프로세스의 affinity 갱신 ▶ value 값 : 0 \n→ 시스템에 의한 프로세스 affinity 동적 갱신 불가로 설정 \n\n(PROCESS_AFFINITY_ENABLE_AUTO_UPDATE로 설정 시 \n시스템의 프로세스 선호도를 동적으로 업데이트 가능)");
		strcpy(buf, "SUCCESS");
	}else {
		strcpy(buf, GetErrorMessage(" SetProcessAffinityUpdateMode() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "SetProcessAffinityUpdateMode", buf, "SUCCESS", meg);
	return true;
}

BOOL test_SetProcessShutdownParameters(){

	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_SetProcessShutdownParameters\n");
	#endif

	// 현재 호출중인 프로세스의 종료 매개 변수를 설정
	// 첫 번째 파라미터 : 프로세스 종료 우선 순위. value 값 다섯 가지 중에 set.
	// 000 ~ 0FF 시스템은 마지막 종료 범위를 예약함	/ 100-1FF 응용 프로그램은 마지막 종료 범위를 예약함
	// 200-2FF 응용 프로그램이 "종료 범위"사이에 예약됨	/ 300-3FF 응용 프로그램이 첫 번째 종료 범위를 예약함
	// 400-4FF 시스템이 첫 번째 종료 범위를 예약함
	// 두 번째 파라미터 : SHUTDOWN_NORETRY → 시스템은 사용자에 대한 재시도 대화 상자를 표시하지 않고 프로세스를 종료
	if(SetProcessShutdownParameters(0x3ff, SHUTDOWN_NORETRY) != 0)
		strcpy(meg, "SetProcessShutdownParameters() : SUCCESS");	
	else 
		strcpy(meg, GetErrorMessage(" SetProcessShutdownParameters() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "SetProcessShutdownParameters", meg, "SetProcessShutdownParameters() : SUCCESS", meg);
	return true;
}

BOOL test_GetProcessShutdownParameters(){

	char meg[BUFSIZ] = "FAIL";

	DWORD lpdwLevel;
	DWORD lpdwFlags;

	#ifdef OQADBGPRINT
	printf("test_GetProcessShutdownParameters\n");
	#endif

	// 현재 호출 중인 프로세스의 종료 매개 변수를 검색. 함수 성공 시 nonzero.
	if(GetProcessShutdownParameters(&lpdwLevel, &lpdwFlags) != 0)
		strcpy(meg, "GetProcessShutdownParameters() : SUCCESS");	
	else 
		strcpy(meg, GetErrorMessage(" GetProcessShutdownParameters() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "GetProcessShutdownParameters", meg, "GetProcessShutdownParameters() : SUCCESS", meg);

	return true;
}

/**
BOOL test_K32EnumProcessModules(){
	
	HANDLE hFile = CreateFileW(L"C:\\Users\\Tmax\\Desktop\\test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD processId = GetProcessId(hFile);
	printf("%d", processId);

	return true;
}
*/

BOOL test_K32InitializeProcessForWsWatch(){

	char meg[BUFSIZ] = "FAIL";

	/** hFile에 생성한 파일 */
	//HANDLE hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	HANDLE hFile = CreateFile(L"손나영\\test_K32InitializeProcessForWsWatch.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	hFile = CreateFile(L"손나영\\test_K32InitializeProcessForWsWatch.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	BOOL result = InitializeProcessForWsWatch(hFile);
	
	#ifdef OQADBGPRINT
	printf("test_K32InitializeProcessForWsWatch\n");
	#endif

	if(result != 0)
		strcpy(meg, "InitializeProcessForWsWatch() : SUCCESS");	
	else 
		strcpy(meg, GetErrorMessage(" InitializeProcessForWsWatch() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "InitializeProcessForWsWatch", meg, "InitializeProcessForWsWatch() : SUCCESS", meg);

	return true;
}

BOOL test_QueryProcessAffinityUpdateMode(){

	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_QueryProcessAffinityUpdateMode\n");
	#endif

	//HANDLE hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test2.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test2.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	HANDLE hFile = CreateFile(L"손나영\\test_QueryProcessAffinityUpdateMode.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	hFile = CreateFile(L"손나영\\test_QueryProcessAffinityUpdateMode.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	BOOL result = QueryProcessAffinityUpdateMode(hFile, 0);

	#ifdef OQADBGPRINT
	printf("test_QueryProcessAffinityUpdateMode\n");
	#endif

	if(result != 0)
		strcpy(meg, "QueryProcessAffinityUpdateMode() : SUCCESS");	
	else 
		strcpy(meg, GetErrorMessage(" QueryProcessAffinityUpdateMode() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "QueryProcessAffinityUpdateMode", meg, "QueryProcessAffinityUpdateMode() : SUCCESS", meg);

	return true;
} 

BOOL test_GetProcessId(){

	BOOL result;
	HANDLE hProcess;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_GetProcessId\n");
	#endif

	/** process 식별자 가져옴 */
	DWORD num = GetCurrentProcessId();

	/**	PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		num : GetCurrentProcessId()		*/
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, num);

	/** OpenProcess() 실패	*/
	if (!hProcess) {
		strcpy(buf, GetErrorMessage(" OpenProcess() : FAIL \n\n Error Message :", GetLastError()));
		return 1;
	}
	
	result = GetProcessId(hProcess);
	
	if(result){
		sprintf(meg, " GetProcessId() : SUCCESS \n\n ProcessId : %d ", num);
		strcpy(buf, "SUCCESS");
	}else{
		strcpy(buf, GetErrorMessage(" GetProcessId() : FAIL \n\n Error Message :", GetLastError()));
	}
	wresult(__FILE__, __LINE__, "GetProcessId", buf, "SUCCESS", meg);

	return true;
}

/**
	process가 자주 참조하는 데이터를 물리 메모리 영역에 상주 시켜서 
	page fault나 page swap 과정 없이 데이터 참조 가능하게 함.
	process working set에는 code pages와 data pages가 포함됨.
	set에서 제외하는 과정 Trim
*/
BOOL test_GetProcessWorkingSetSize(){

	BOOL result;
	HANDLE hProcess;
	SIZE_T dwMin, dwMax;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_GetProcessWorkingSetSize\n");
	#endif

	/** process 식별자 가져옴 */
	int num = GetCurrentProcessId();

	/**	PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		num : GetCurrentProcessId()		*/
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, num);

	/** OpenProcess() 실패	*/
	if (!hProcess) {
		strcpy(buf, GetErrorMessage(" OpenProcess() : FAIL \n\n Error Message :", GetLastError()));
		return 1;
	}

	/**	process의 working set size를 가져옴	*/
	result = GetProcessWorkingSetSize(hProcess, &dwMin, &dwMax);

	if (result != 0){
		sprintf(meg, " GetProcessWorkingSetSize() : SUCCESS \n\n ProcessId : %d \n MinimumWorkingSetSize : %lu KB \n MaximumWorkingSetSize : %lu KB", num, dwMin, dwMax);
		strcpy(buf, "SUCCESS");

	}else 
		strcpy(buf, GetErrorMessage(" GetProcessWorkingSetSize() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "GetProcessWorkingSetSize", buf, "SUCCESS", meg);

    CloseHandle(hProcess);
	return true;
}

BOOL test_IsProcessInJob(){

	BOOL result;
	BOOL bInJob;
	HANDLE hProcess;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_IsProcessInJob\n");
	#endif

	/** process 식별자 가져옴 */
	int num = GetCurrentProcessId();

	/**	PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		num : GetCurrentProcessId()		*/
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, num);

	/** OpenProcess() 실패	*/
	if (!hProcess) {
		strcpy(buf, GetErrorMessage(" OpenProcess() : FAIL \n\n Error Message :", GetLastError()));
		return 1;
	}

	/** process가 지정된 작업에서 실행 중인지 여부 결정	*/
    result = IsProcessInJob(hProcess, 0, &bInJob);

	if(result != 0){
		sprintf(meg, " IsProcessInJob() : SUCCESS");
		strcpy(buf, "SUCCESS");

	}else 
		strcpy(buf, GetErrorMessage(" IsProcessInJob() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "IsProcessInJob", buf, "SUCCESS", meg);
	return true;
}

BOOL test_GetProcessGroupAffinity(){


	HANDLE hProcess;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_GetProcessGroupAffinity\n");
	#endif

	/** process 식별자 가져옴 */
	int pid = GetCurrentProcessId();

	/**	PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		num : GetCurrentProcessId()		*/
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, pid);

	/** OpenProcess() 실패	*/
	if (!hProcess) {
		strcpy(buf, GetErrorMessage(" OpenProcess() : FAIL \n\n Error Message :", GetLastError()));
		return 1;

	}
	return true;
}

BOOL test_GetProcessWorkingSetSizeEx(){
	
	BOOL result;
	HANDLE hProcess;
	SIZE_T dwMin, dwMax;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	/** process 식별자 가져옴 */
	int num = GetCurrentProcessId();

	/**	PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		num : GetCurrentProcessId()		*/
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, num);

	/** OpenProcess() 실패	*/
	if (!hProcess) {
		strcpy(buf, GetErrorMessage(" OpenProcess() : FAIL \n\n Error Message :", GetLastError()));
		return 1;
	}

	/**	process의 working set size를 가져옴	*/
	/** 0xC0000005: 0x00000000 위치를 기록하는 동안 액세스 위반이 발생했습니다. */
	result = GetProcessWorkingSetSizeEx(hProcess, &dwMin, &dwMax, 0);
	
	if(!result){
		sprintf(meg, " GetProcessWorkingSetSizeEx() : SUCCESS \n\n ProcessId : %d \n MinimumWorkingSetSize : %lu KB \n MaximumWorkingSetSize : %lu KB", num, dwMin, dwMax);
		strcpy(buf, "SUCCESS");
	}else{
		strcpy(buf, GetErrorMessage(" GetProcessWorkingSetSize() : FAIL \n\n Error Message :", GetLastError()));
	}
	wresult(__FILE__, __LINE__, "GetProcessWorkingSetSizeEx", buf, "SUCCESS", meg);

	return true;
}

BOOL test_GetProcessDEPPolicy(){

	HANDLE hProcess;

	int num = GetCurrentProcessId();

	/**	PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		num : GetCurrentProcessId()		*/
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, num);

	/** DEP Flags : 0 / PROCESS_DEP_ENABLE / PROCESS_DEP_DISABLE_ATL_THUNK_EMULATION */
	//if(GetProcessDEPPolicy(hProcess, &dwPolicy, 0) != FALSE){
	//	if (dwPolicy == PROCESS_DEP_ENABLE) {
	//	printf("a");
	//	}
	//}else
	//	printf("b");

	return true;
}

BOOL test_SetProcessPriorityBoost(){

	BOOL result;
	//HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION, FALSE, pe32.th32ProcessID);

	//result = SetProcessPriorityBoost(hProcess, TRUE);
	if(result != 0)
		printf("a");
	else
		printf("b");

	return true;
}



/** 지정된 process의 쓰기 캐쉬를 지움(flush) 
BOOL test_FlushProcessWriteBuffers(){
	
	FlushProcessWriteBuffers();
	printf("Sdfds");  // 실패상황

	return true;
}
*/