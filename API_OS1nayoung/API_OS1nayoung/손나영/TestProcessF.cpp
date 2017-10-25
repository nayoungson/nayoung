#include "TestProcessF.h"
#include <TlHelp32.h>

BOOL test_SetProcessDEPPolicy(){
	
	#ifdef OQADBGPRINT
	printf("test_SetProcessDEPPolicy\n");
	#endif

	BOOL result = true;
	
	char *buf = NULL;
	char meg[BUFSIZ] = "FAIL";
	
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

	#ifdef OQADBGPRINT
	printf("test_SetProcessAffinityUpdateMode\ n");
	#endif

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

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

	#ifdef OQADBGPRINT
	printf("test_SetProcessShutdownParameters\n");
	#endif

	char meg[BUFSIZ] = "FAIL";

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

	#ifdef OQADBGPRINT
	printf("test_GetProcessShutdownParameters\n");
	#endif

	char meg[BUFSIZ] = "FAIL";

	DWORD lpdwLevel;
	DWORD lpdwFlags;

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

/**
	지정된 process의 working set을 모니터링 시작(초기화)
*/
BOOL test_K32InitializeProcessForWsWatch(){

	#ifdef OQADBGPRINT
	printf("test_K32InitializeProcessForWsWatch\n");
	#endif

	char meg[BUFSIZ] = "FAIL";

	/** hFile에 생성한 파일 */
	HANDLE hFile = CreateFile(L"손나영\\test_K32InitializeProcessForWsWatch.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	//HANDLE hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	hFile = CreateFile(L"손나영\\test_K32InitializeProcessForWsWatch.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	BOOL result = InitializeProcessForWsWatch(hFile);
	
	if(result != 0)
		strcpy(meg, "InitializeProcessForWsWatch() : SUCCESS");	
	else 
		strcpy(meg, GetErrorMessage(" InitializeProcessForWsWatch() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "InitializeProcessForWsWatch", meg, "InitializeProcessForWsWatch() : SUCCESS", meg);

	//추가된 페이지 검색하려면 GetWsChangesEx() function.
	return true;
}

/**
	특정 프로세스의 update mode 검색
*/
BOOL test_QueryProcessAffinityUpdateMode(){

	#ifdef OQADBGPRINT
	printf("test_QueryProcessAffinityUpdateMode\n");
	#endif

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";
	
	DWORD Flags = PROCESS_AFFINITY_ENABLE_AUTO_UPDATE;

	/** hFile에 생성한 파일 */
	HANDLE hFile = CreateFile(L"손나영\\test_QueryProcessAffinityUpdateMode.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//HANDLE hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test2.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test2.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	hFile = CreateFile(L"손나영\\test_QueryProcessAffinityUpdateMode.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	/** 두 번째 파라미터 0 : 시스템에 의한 프로세스 affinity의 동적 갱신 불가 
					    PROCESS_AFFINITY_ENABLE_AUTO_UPDATE : 시스템에 의한 프로세스 affinity의 동적 갱신 가능	*/
	BOOL result = QueryProcessAffinityUpdateMode(hFile, &Flags);

	if(result != 0){
		
		sprintf(meg, "QueryProcessAffinityUpdateMode() : SUCCESS \n\n affinity update mode : %u", Flags);	
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(meg, GetErrorMessage(" QueryProcessAffinityUpdateMode() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "QueryProcessAffinityUpdateMode", buf, "SUCCESS", meg);

	return true;
} 

BOOL test_GetProcessId(){

	#ifdef OQADBGPRINT
	printf("test_GetProcessId\n");
	#endif

	BOOL result;
	HANDLE hProcess;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";
	
	/** process 식별자 가져옴 */
	DWORD pid = GetCurrentProcessId();

	/**	PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		pid : GetCurrentProcessId()		*/
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, pid);

	/** OpenProcess() 실패	*/
	if (!hProcess) {
		strcpy(buf, GetErrorMessage(" OpenProcess() : FAIL \n\n Error Message :", GetLastError()));
		return 1;
	}
	
	result = GetProcessId(hProcess);
	
	if(result){
		sprintf(meg, " GetProcessId() : SUCCESS \n\n ProcessId : %d ", pid);
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

	#ifdef OQADBGPRINT
	printf("test_GetProcessWorkingSetSize\n");
	#endif

	BOOL result;
	HANDLE hProcess;
	SIZE_T dwMin, dwMax;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	/** process 식별자 가져옴 */
	int pid = GetCurrentProcessId();

	/**	PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		pid : GetCurrentProcessId()		*/
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, pid);

	/** OpenProcess() 실패	*/
	if (!hProcess) {
		strcpy(buf, GetErrorMessage(" OpenProcess() : FAIL \n\n Error Message :", GetLastError()));
		return 1;
	}

	/**	process의 working set size를 가져옴	*/
	result = GetProcessWorkingSetSize(hProcess, &dwMin, &dwMax);

	if (result != 0){
		sprintf(meg, " GetProcessWorkingSetSize() : SUCCESS \n\n ProcessId : %d \n MinimumWorkingSetSize : %lu KB \n MaximumWorkingSetSize : %lu KB", pid, dwMin, dwMax);
		strcpy(buf, "SUCCESS");

	}else 
		strcpy(buf, GetErrorMessage(" GetProcessWorkingSetSize() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "GetProcessWorkingSetSize", buf, "SUCCESS", meg);

    CloseHandle(hProcess);

	return true;
}

BOOL test_IsProcessInJob(){

	#ifdef OQADBGPRINT
	printf("test_IsProcessInJob\n");
	#endif

	BOOL result;
	BOOL bInJob;
	HANDLE hProcess;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";
	
	/** process 식별자 가져옴 */
	int pid = GetCurrentProcessId();

	/**	PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		pid : GetCurrentProcessId()		*/
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, pid);

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


BOOL test_GetProcessHandleCount(){

	#ifdef OQADBGPRINT
	printf("test_GetProcessHandleCount\n");
	#endif

	BOOL result;
	DWORD handlecount;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";
	int pid = GetCurrentProcessId();

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, pid);
	result = GetProcessHandleCount(hProcess, &handlecount);
	
	/** OpenProcess() 실패	*/
	if (!hProcess) {
		strcpy(buf, GetErrorMessage(" OpenProcess() : FAIL \n\n Error Message :", GetLastError()));
		return 1;
	}

	if(result != 0){
		sprintf(meg, " GetProcessHandleCount() : SUCCESS \n\n ProcessID : %d \n HandleCount : %d", pid, handlecount);
		
		strcpy(buf, "SUCCESS");

	}else 
		strcpy(buf, GetErrorMessage(" GetProcessHandleCount() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "GetProcessHandleCount", buf, "SUCCESS", meg);

	return true;
}

/** 32bit 프로세서만 지원 */
BOOL test_GetProcessDEPPolicy(){

	#ifdef OQADBGPRINT
	printf("test_GetProcessDEPPolicy\n");
	#endif

	int pid;
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	HANDLE hProcess;
	DWORD flags;
	BOOL permanent;

	/**	hProcess
		PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		pid : GetCurrentProcessId()		*/
	
	pid = GetCurrentProcessId();
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, pid);
	flags = PROCESS_DEP_ENABLE;
	
	/** OpenProcess() 실패	*/
	if (!hProcess) {
		strcpy(buf, GetErrorMessage(" OpenProcess() : FAIL \n\n Error Message :", GetLastError()));
		return 1;
	}

	/** DEP Flags : 0 / PROCESS_DEP_ENABLE / PROCESS_DEP_DISABLE_ATL_THUNK_EMULATION */
	if(GetProcessDEPPolicy(hProcess, &flags, &permanent) == TRUE){
		sprintf(meg, " GetProcessDEPPolicy() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}else{
		strcpy(buf, GetErrorMessage(" GetProcessDEPPolicy() : FAIL \n\n Error Message :", GetLastError()));
	}
	wresult(__FILE__, __LINE__, "GetProcessDEPPolicy", buf, "SUCCESS", meg);

	return true;
}

/** 현재 프로세스의 스레드를 실행중인 각 프로세서의 쓰기 큐를 플러시합니다. */
BOOL test_FlushProcessWriteBuffers(){

	#ifdef OQADBGPRINT
	printf("test_FlushProcessWriteBuffers\n");
	#endif

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	//__rdtsc : 프로세서 시간 스탬프 반환. 마지막 재설정 후 클록 주기 수 기록.

	unsigned __int64 t1 = __rdtsc();
	FlushProcessWriteBuffers();
	unsigned __int64 t2 = __rdtsc() ;
	
	printf("%d \n", t1);
	printf("%d \n", t2);

	if(t1 != t2){
		sprintf(meg, " FlushProcessWriteBuffers() : SUCCESS");
		//sprintf(meg, " FlushProcessWriteBuffers() : SUCCESS \n\n Flush 전 __rdtsc = %d \n Flush 후 __rdtsc = %d ", t1, t2);
		strcpy(buf, "SUCCESS");
	}else{
		strcpy(buf, GetErrorMessage(" FlushProcessWriteBuffers() : FAIL \n\n Error Message :", GetLastError()));
	}
	wresult(__FILE__, __LINE__, "FlushProcessWriteBuffers", buf, "SUCCESS", meg);

	return true;
}


BOOL test_SetProcessPriorityBoost(){
	
	#ifdef OQADBGPRINT
	printf("test_SetProcessPriorityBoost\n");
	#endif

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";
	int pid = GetCurrentProcessId();

	BOOL result;
	// This handle must have the PROCESS_SET_INFORMATION access right.
	HANDLE hProcess = OpenProcess(PROCESS_SET_INFORMATION , FALSE, pid);

	// To restore normal behavior, call SetProcessPriorityBoost with DisablePriorityBoost set to FALSE.
	result = SetProcessPriorityBoost(hProcess, FALSE);

	if(result != 0){
		sprintf(meg, " SetProcessPriorityBoost() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}else{
		strcpy(meg, GetErrorMessage(" SetProcessPriorityBoost() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "SetProcessPriorityBoost", buf, "SUCCESS", meg);

	return true;
}


BOOL test_K32EnumProcesses(){

	#ifdef OQADBGPRINT
	printf("test_K32EnumProcesses\n");
	#endif

	DWORD arProc[1024],cb;
	BOOL result;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	// 프로세스의 목록을 배열에 구하고 개수를 계산한다.
	result = EnumProcesses(arProc,sizeof(arProc),&cb);
	
	if(result != 0){
		sprintf(meg, " EnumProcesses() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}else{
		strcpy(meg, GetErrorMessage(" EnumProcesses() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "EnumProcesses", buf, "SUCCESS", meg);

	return true;
}

BOOL test_K32EnumProcessModules(){

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	DWORD arProc[1024];
	DWORD cb;

	HMODULE hModule;
	HANDLE hProcess;
	BOOL result;

	// 프로세스의 목록을 배열에 구하고 개수를 계산한다.
	EnumProcesses(arProc,sizeof(arProc),&cb);

	int pid = GetCurrentProcessId();

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE, pid);

	if(hProcess){

		// 첫번째 모듈(=프로세스 그 자체)의 이름을 구해 출력한다.
		result=EnumProcessModules(hProcess,&hModule,sizeof(hModule),&cb);

		if(result != 0){
			sprintf(meg, " EnumProcessModules() : SUCCESS");
			strcpy(buf, "SUCCESS");
		}else{
			strcpy(meg, GetErrorMessage(" EnumProcessModules() : FAIL \n\n Error Message :", GetLastError()));
		}
	}else
		strcpy(meg, GetErrorMessage(" 프로세스를 open하지 못했습니다. \n\n OpenProcess 함수를 다시 체크하십시오. \n\n Error Message :", GetLastError()));
	wresult(__FILE__, __LINE__, "EnumProcessModules", buf, "SUCCESS", meg);

	return true;
}

BOOL test_K32EnumProcessModulesEx(){

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	DWORD arProc[1024];
	DWORD cb;

	HMODULE hModule;
	HANDLE hProcess;
	BOOL result;

	// 프로세스의 목록을 배열에 구하고 개수를 계산한다.
	EnumProcesses(arProc,sizeof(arProc),&cb);

	int pid = GetCurrentProcessId();

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE, pid);

	if(hProcess){

		// 첫번째 모듈(=프로세스 그 자체)의 이름을 구해 출력한다.
		result=EnumProcessModulesEx(hProcess, &hModule, sizeof(hModule), &cb, LIST_MODULES_ALL);

		if(result != 0){
			sprintf(meg, " EnumProcessModulesEx() : SUCCESS");
			strcpy(buf, "SUCCESS");
		}else{
			strcpy(meg, GetErrorMessage(" EnumProcessModulesEx() : FAIL \n\n Error Message :", GetLastError()));
		}
	}else
		strcpy(meg, GetErrorMessage(" 프로세스를 open하지 못했습니다. \n\n OpenProcess 함수를 다시 체크하십시오. \n\n Error Message :", GetLastError()));
	wresult(__FILE__, __LINE__, "EnumProcessModulesEx", buf, "SUCCESS", meg);

	return true;
}



BOOL test_K32GetModuleBaseNameA(){

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";


	HANDLE hProcess;
	HMODULE hMod;

	int pid = GetCurrentProcessId();
	TCHAR szProcessName[MAX_PATH] = L"<unknown>";

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE, pid);
	DWORD result = GetModuleBaseNameA(hProcess, hMod, (LPSTR)szProcessName, sizeof(szProcessName)/sizeof(TCHAR) );

	if(result == 0){
		strcpy(meg, GetErrorMessage(" K32GetModuleBaseNameA() : FAIL \n\n Error Message :", GetLastError()));
	}else{

		sprintf(meg, " K32GetModuleBaseNameA() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}
	wresult(__FILE__, __LINE__, "K32GetModuleBaseNameA", buf, "SUCCESS", meg);
	return true;
}

BOOL test_K32GetModuleBaseNameW(){

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	HANDLE hProcess;
	HMODULE hMod;

	int pid = GetCurrentProcessId();
	TCHAR szProcessName[MAX_PATH] = L"<unknown>";

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE, pid);
	DWORD result = GetModuleBaseNameW(hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(TCHAR) );

	if(result == 0){
		strcpy(meg, GetErrorMessage(" GetModuleBaseNameW() : FAIL \n\n Error Message :", GetLastError()));
	}else{

		sprintf(meg, " GetModuleBaseNameW() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}
	wresult(__FILE__, __LINE__, "GetModuleBaseNameW", buf, "SUCCESS", meg);
	return true;
}













/**
BOOL test_GetProcessGroupAffinity(){

	int pid;
	
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	HANDLE hProcess;
	USHORT gcount;
	USHORT *garray;

	pid = GetCurrentProcessId();
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, pid);

	/** OpenProcess() 실패	
	if (!hProcess) {
		strcpy(buf, GetErrorMessage(" OpenProcess() : FAIL \n\n Error Message :", GetLastError()));
		return 1;
	}

	if (GetProcessGroupAffinity(hProcess, &gcount, garray) != 0){
		printf("ds");
	}else{
		printf("%d", GetLastError());
		strcpy(meg, GetErrorMessage(" GetProcessGroupAffinity() : FAIL \n\n Error Message : ", GetLastError()));
	}
	/**
	if (GetProcessGroupAffinity(hProcess, &gcount, garray) == 0) {
		DWORD err = GetLastError();

		if (err == ERROR_INSUFFICIENT_BUFFER) {
			gcount = gcount * sizeof(garray[0]);

			if (GetProcessGroupAffinity(hProcess, &gcount, garray) != 0) {
				printf("sdf");
				strcpy(buf, "SUCCESS");

				CloseHandle(hProcess);
				return 0;
			}
		} 
	}
	

	CloseHandle(hProcess);

	wresult(__FILE__, __LINE__, "GetProcessDEPPolicy", buf, "SUCCESS", meg);
	return true;
}

*/

BOOL test_GetProcessWorkingSetSizeEx(){
	
	BOOL result;
	HANDLE hProcess;
	SIZE_T dwMin, dwMax;
	//PDWORD Flags = QUOTA_LIMITS_HARDWS_MIN_DISABLE;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	/** process 식별자 가져옴 */
	int pid = GetCurrentProcessId();

	/**	PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		pid : GetCurrentProcessId()		*/
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, pid);

	/** OpenProcess() 실패	*/
	if (!hProcess) {
		strcpy(buf, GetErrorMessage(" OpenProcess() : FAIL \n\n Error Message :", GetLastError()));
		return 1;
	}

	/**	process의 working set size를 가져옴	*/
	/** 0xC0000005: 0x00000000 위치를 기록하는 동안 액세스 위반이 발생했습니다. */
	//result = GetProcessWorkingSetSizeEx(hProcess, &dwMin, &dwMax, QUOTA_LIMITS_HARDWS_MIN_DISABLE);
	

	/*if(!result){
		sprintf(meg, " GetProcessWorkingSetSizeEx() : SUCCESS \n\n ProcessId : %d \n MinimumWorkingSetSize : %lu KB \n MaximumWorkingSetSize : %lu KB", pid, dwMin, dwMax);
		strcpy(buf, "SUCCESS");
	}else{
		strcpy(buf, GetErrorMessage(" GetProcDNessWorkingSetSize() : FAIL \n\n Error Message :", GetLastError()));
	}
	wresult(__FILE__, __LINE__, "GetProcessWorkingSetSizeEx", buf, "SUCCESS", meg);
*/
	return true;
}



/** 지정된 process의 쓰기 캐쉬를 지움(flush) 
BOOL test_FlushProcessWriteBuffers(){
	
	FlushProcessWriteBuffers();
	printf("Sdfds");  // 실패상황

	return true;
}
*/

