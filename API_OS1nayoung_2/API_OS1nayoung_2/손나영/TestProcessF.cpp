#include "TestProcessF.h"
#include <TlHelp32.h>


/**
* VOID WINAPI FlushProcessWriteBuffers(void);
* 현재 프로세스의 스레드를 실행중인 각 프로세서의 쓰기 큐를 플러시
* @author : 손나영
*
* @param void
* @return 없음.
*/

BOOL test_FlushProcessWriteBuffers(){

	#ifdef OQADBGPRINT
	printf("test_FlushProcessWriteBuffers\n");
	#endif

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	BOOL result = FALSE;

	//__rdtsc : 프로세서 시간 스탬프 반환. 마지막 재설정 후 클록 주기 수 기록.

	unsigned __int64 t1 = __rdtsc();
	FlushProcessWriteBuffers();
	unsigned __int64 t2 = __rdtsc() ;
	
	if(t1 != t2){
		sprintf(msg, " FlushProcessWriteBuffers() : SUCCESS");
		//sprintf(msg, " FlushProcessWriteBuffers() : SUCCESS \n\n Flush 전 __rdtsc = %d \n Flush 후 __rdtsc = %d ", t1, t2);
		strcpy(buf, "SUCCESS");
		result = TRUE;
	}else{
		strcpy(buf, GetErrorMessage(" FlushProcessWriteBuffers() : FAIL \n\n Error Message :", GetLastError()));
	}
	wresult(__FILE__, __LINE__, "FlushProcessWriteBuffers", buf, "SUCCESS", msg);

	return result;
}


/**
* WORD GetMaximumProcessorGroupCount(void);
* 시스템이 가질 수있는 프로세서 그룹의 최대 수를 반환
* @author : 손나영
*
* @param void
* @return 시스템이 가질 수있는 프로세서 그룹의 최대 수
*/

BOOL test_GetMaximumProcessorGroupCount(){

	char msg[BUFSIZ] = "FAIL";																							
	char buf[BUFSIZ];

	DWORD result = GetMaximumProcessorGroupCount();
	BOOL re_result;

	#ifdef OQADBGPRINT
	printf("test_GetMaximumProcessorGroupCount \n");
	#endif
	
	if(result != 0){
		sprintf(msg, " GetMaximumProcessorGroupCount() : SUCCESS \n\n 프로세서 그룹 최대 개수 : %d", result);
		strcpy(buf, "SUCCESS");
		re_result = TRUE;

	}else 
		strcpy(msg, GetErrorMessage(" GetMaximumProcessorGroupCount() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "GetMaximumProcessorGroupCount", buf, "SUCCESS", msg);

	return re_result;
}

/**
* BOOL GetNumaNodeNumberFromHandle(
  _In_  HANDLE  hFile,
  _Out_ PUSHORT NodeNumber
  );
* 지정된 파일 핸들이 나타내는 파일 또는 I / O 장치와 연관된 NUMA 노드를 검색
* @author : 손나영
*
* @param 파일 또는 I / O 장치에 대한 핸들
* @param 지정된 파일 핸들과 연관된 NUMA 노드의 번호를 수신하는 변수에 대한 포인터.
* @return 검색 성공/실패 여부
*/

BOOL test_GetNumaNodeNumberFromHandle(){

	#ifdef OQADBGPRINT
	printf("test_GetNumaNodeNumberFromHandle \n");
	#endif

	BOOL result;
	BOOL re_result;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	USHORT nodeNumber = 255;
	HANDLE hFile = CreateFile(L"손나영\\test_GetNumaNodeNumberFromHandle.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	result = GetNumaNodeNumberFromHandle(hFile, &nodeNumber);

	if(result != 0){
			sprintf(msg, " GetNumaNodeNumberFromHandle() : SUCCESS");
			strcpy(buf, "SUCCESS");
			re_result = TRUE;
	}else 
			strcpy(msg, GetErrorMessage(" GetNumaNodeNumberFromHandle() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "GetNumaNodeNumberFromHandle", buf, "SUCCESS", msg);

	return re_result;
}


/**
* BOOL WINAPI GetNumaProcessorNode(
  _In_  UCHAR  Processor,
  _Out_ PUCHAR NodeNumber
  );
* 지정된 프로세서의 노드 번호를 검색.
* @author : 손나영
*
* @param Processor 프로세서 번호.
* @param NodeNumber 노드 번호. 프로세서가 존재하지 않으면이 매개 변수는 0xFF.
* @return 검색 성공/실패 여부
*/

/** 
	node number for the specified processor.
	NUMA(Non-Uniform Memory Access) NODE : 
	NUMA 아키텍처는 각 프로세서 그룹에 자체 메모리가 있으며 자체 I/O 채널이 있는 경우도 있다. 
	그러나 각 CPU는 일관된 방법으로 다른 그룹과 연결된 메모리에 액세스 한다. 각 그룹을 NUMA노드라 한다.  
	하나의 CPU 소켓에 코어 여러개가 들어가 있을 수 있기에 같은 지역 메모리를 사용하는 CPU 코어들을 묶어서 하나의 NUMA 노드로 친다.
	8코어 4소켓 CPU라면 (하이퍼스레딩을 가정하지 않을 때에) 0~7번 코어는 NUMA 노드 0번, 8~15번 코어는 NUMA 노드 1번과 같은 방식.

*/
BOOL test_GetNumaProcessorNode(){
	
	#ifdef OQADBGPRINT
	printf("test_GetNumaProcessorNode \n");
	#endif

	BOOL result;
	BOOL re_result;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	/** processor가 존재하지 않는다면 node number(두 번째 파라미터)는 0xFF */
	DWORD processorNumber = GetCurrentProcessorNumber();

	if(processorNumber != -1){
		// 255
		UCHAR nodeNumber = 255;
		result = GetNumaProcessorNode((UCHAR)processorNumber, &nodeNumber);

		if(result != 0){
			sprintf(msg, " GetNumaProcessorNode() : SUCCESS \n\n number of processor the current thread : %d", processorNumber);
			strcpy(buf, "SUCCESS");
			re_result = TRUE;

		}else 
			strcpy(buf, GetErrorMessage(" GetCurrentProcessorNumber() : FAIL \n\n Error Message :", GetLastError()));
	}else
		strcpy(msg, GetErrorMessage(" processor number 조회에 실패했습니다. \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "GetCurrentProcessorNumber", buf, "SUCCESS", msg);
	return re_result;
}


/**
* BOOL WINAPI GetProcessDEPPolicy(
  _In_  HANDLE  hProcess,
  _Out_ LPDWORD lpFlags,
  _Out_ PBOOL   lpPermanent
  );
* 지정된 32 비트 프로세스에 대한 DEP (데이터 실행 방지) 및 DEP-ATL 썽크 에뮬레이션 설정을 가져옴.
* @author : 손나영
*
* @param hProcess 프로세스에 대한 핸들. PROCESS_QUERY_INFORMATION 권한 필요.
* @param lpFlags 플래그 종류 3가지.
* @param lpPermanent DEP가 지정된 프로세스에 대해 영구적으로 활성화 또는 비활성화 된 경우 TRUE. 그렇지 않으면 FALSE.
* @return 가져오기 성공/실패 여부
*/

/** 32bit 프로세서만 지원 */
BOOL test_GetProcessDEPPolicy(){

	#ifdef OQADBGPRINT
	printf("test_GetProcessDEPPolicy\n");
	#endif

	int pid;
	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	HANDLE hProcess;
	DWORD flags;
	BOOL permanent;
	BOOL result = FALSE;

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
		sprintf(msg, " GetProcessDEPPolicy() : SUCCESS");
		strcpy(buf, "SUCCESS");
		result = TRUE;
	}else{
		strcpy(buf, GetErrorMessage(" GetProcessDEPPolicy() : FAIL \n\n Error Message :", GetLastError()));
	}
	wresult(__FILE__, __LINE__, "GetProcessDEPPolicy", buf, "SUCCESS", msg);

	return result;
}


/**
* BOOL GetProcessGroupAffinity(
  _In_    HANDLE  hProcess,
  _Inout_ PUSHORT GroupCount,
  _Out_   PUSHORT GroupArray
  );
* 지정된 프로세스의 프로세서 그룹 선호도를 가져옴.
* @author : 손나영
*
* @param hProcess 프로세스에 대한 핸들. PROCESS_QUERY_INFORMATION 또는 PROCESS_QUERY_LIMITED_INFORMATION 권한 필요.
* @param GroupCount 입력시 GroupArray 배열 의 요소 수를 지정. 출력시 배열에 기록 된 프로세서 그룹 수를 지정. 
					배열이 너무 작 으면이 함수는 ERROR_INSUFFICIENT_BUFFER로 실패하고 GroupCount 매개 변수를 필요한 요소 수로 설정
* @param GroupArray 프로세서 그룹 번호 배열
* @return 가져오기 성공/실패 여부
*/

#define WIN32_WINNT 0x0601
BOOL test_GetProcessGroupAffinity(){

	#ifdef OQADBGPRINT
	printf("test_GetProcessGroupAffinity \n");
	#endif

	int pid;
	int wresult_value = 0;

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	HANDLE hProcess;
	USHORT gcount = GetMaximumProcessorGroupCount();
	USHORT *garray = &gcount; //!

	pid = GetCurrentProcessId();
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);

	if(!hProcess){
		DWORD err = GetLastError();

		switch(err){
		case ERROR_ACCESS_DENIED:
			sprintf(msg, "Process Open 실패 \n\n ProcessID : %ld \n Error : ERROR_ACCESS_DENIED");
			break;
		case ERROR_INVALID_PARAMETER:
			sprintf(msg, "Process Open 실패 \n\n ProcessID : %ld \n Error : ERROR_INVALID_PARAMETER");
			break;
		default:
			sprintf(msg, "Process Open 실패 \n\n ProcessID : %ld");
		}
		return FALSE;
	}
	if(GetProcessGroupAffinity(hProcess, &gcount, garray) == 0){
		DWORD err = GetLastError();

		//gcount가 너무 작으면 ERROR_INSUFFICIENT_BUFFER 발생
		if(err == ERROR_INSUFFICIENT_BUFFER){
			garray = (USHORT *)realloc(garray, gcount * sizeof(garray[0]));
			if (garray == NULL) {
				sprintf(msg, "GetProcessGroupAffinity() 실패 → ERROR : ERROR_INSUFFICIENT_BUFFER \n → garray == NULL인 경우");
				gcount = 0;
				CloseHandle(hProcess);
				return FALSE;
			}
			if(GetProcessGroupAffinity(hProcess, &gcount, garray) == 0){
				DWORD err = GetLastError();
				printf("GetProcessGroupAffinity() 실패 → ERROR : ERROR_INSUFFICIENT_BUFFER \n → garray != NULL인 경우");
				CloseHandle(hProcess);
				return FALSE;
			}
		} else {
			sprintf(msg, "GetProcessGroupAffinity() : FAIL \n\n ProcessID : %ld \n error 0x%08x(%d)\n\n error code 998 → ", pid, (unsigned int) err, err);
			CloseHandle(hProcess);
		}
	}else{
		wresult_value = 1;
		sprintf(msg, "GetProcessGroupAffinity() : SUCCESS \n\nProcessID : %ld ", pid);
	}
	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "GetProcessGroupAffinity", buf, "1", msg);

	return TRUE;
}


/**
* BOOL WINAPI GetProcessHandleCount(
  _In_    HANDLE hProcess,
  _Inout_ PDWORD pdwHandleCount
  );
* 지정된 프로세스에 속한 열려있는 핸들 수를 검색
* @author : 손나영
*
* @param hProcess 핸들 수를 요청한 프로세스의 핸들. 핸들에는 PROCESS_QUERY_INFORMATION 또는 PROCESS_QUERY_LIMITED_INFORMATION 액세스 권한이 있어야 함.
* @param pdwHandleCount 지정된 프로세스에 속한 열린 핸들 수를 수신하는 변수에 대한 포인터.
* @return 검색 성공/실패 여부
*/

BOOL test_GetProcessHandleCount(){

	#ifdef OQADBGPRINT
	printf("test_GetProcessHandleCount\n");
	#endif

	BOOL result = FALSE;
	DWORD handlecount;

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";
	int pid = GetCurrentProcessId();

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, pid);
	result = GetProcessHandleCount(hProcess, &handlecount);
	
	/** OpenProcess() 실패	*/
	if (!hProcess) {
		strcpy(buf, GetErrorMessage(" OpenProcess() : FAIL \n\n Error Message :", GetLastError()));
		return 1;
	}

	if(result != 0){
		sprintf(msg, " GetProcessHandleCount() : SUCCESS \n\n ProcessID : %d \n HandleCount : %d", pid, handlecount);
		strcpy(buf, "SUCCESS");
		result = TRUE;

	}else{
		strcpy(buf, GetErrorMessage(" GetProcessHandleCount() : FAIL \n\n Error Message :", GetLastError()));
		result = FALSE;
	}

	wresult(__FILE__, __LINE__, "GetProcessHandleCount", buf, "SUCCESS", msg);
	return result;
}

/**
* DWORD WINAPI GetProcessId(
  _In_ HANDLE Process
  );
* 지정된 프로세스의 프로세스 ID를 검색
* @author : 손나영
*
* @param Process 프로세스에 대한 핸들. 핸들에는 PROCESS_QUERY_INFORMATION 또는 PROCESS_QUERY_LIMITED_INFORMATION 액세스 권한 있어야 함.
* @return 지정된 프로세스의 프로세스 ID
*/

BOOL test_GetProcessId(){

	#ifdef OQADBGPRINT
	printf("test_GetProcessId\n");
	#endif

	BOOL result;
	HANDLE hProcess;

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";
	
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
		sprintf(msg, " GetProcessId() : SUCCESS \n\n ProcessId : %d ", pid);
		strcpy(buf, "SUCCESS");
	}else{
		strcpy(buf, GetErrorMessage(" GetProcessId() : FAIL \n\n Error Message :", GetLastError()));
		return FALSE;
	}
	wresult(__FILE__, __LINE__, "GetProcessId", buf, "SUCCESS", msg);

	return TRUE;
}


/**
* BOOL WINAPI GetProcessPriorityBoost(
  _In_  HANDLE hProcess,
  _Out_ PBOOL  pDisablePriorityBoost
  );
* 지정된 프로세스의 priority boost control 상태를 얻어옴.
* @author : 손나영
*
* @param hProcess 프로세스에 대한 핸들. 이 핸들에는 PROCESS_QUERY_INFORMATION 또는 PROCESS_QUERY_LIMITED_INFORMATION 액세스 권한 이 있어야 함.
* @param pDisablePriorityBoost priority boost 제어 상태를받는 변수에 대한 포인터.
* @return 검색 성공/실패 여부.

*/

BOOL test_GetProcessPriorityBoost(){
	
	#ifdef OQADBGPRINT
	printf("test_SetProcessPriorityBoost\n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";
	int pid = GetCurrentProcessId();
	LONG err = GetLastError();

	BOOL result;
	BOOL set_result;
	BOOL re_result = FALSE;
	// This handle must have the PROCESS_SET_INFORMATION access right.
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_QUERY_LIMITED_INFORMATION , FALSE, pid);

	set_result = SetProcessPriorityBoost(hProcess, FALSE);

	// To restore normal behavior, call SetProcessPriorityBoost with DisablePriorityBoost set to FALSE.
	result = GetProcessPriorityBoost(hProcess, &set_result);

	if(result == 0){
		strcpy(msg, GetErrorMessage(" GetProcessPriorityBoost() : FAIL \n\n Error Message :", GetLastError()));
		printf("에러코드 : %d" ,GetLastError());
	}else{
		re_result = TRUE;
		sprintf(msg, " GetProcessPriorityBoost() : SUCCESS");
		strcpy(buf, "SUCCESS");
		
	}

	wresult(__FILE__, __LINE__, "GetProcessPriorityBoost", buf, "SUCCESS", msg);

	return re_result;
}


/**
* BOOL WINAPI GetProcessShutdownParameters(
  _Out_ LPDWORD lpdwLevel,
  _Out_ LPDWORD lpdwFlags
  );
* 현재 호출중인 프로세스의 종료 매개 변수를 검색
* @author : 손나영
*
* @param lpdwLevel 종료 우선 순위 수준을받는 변수에 대한 포인터. 높은 숫자가 먼저 종료됩니다. 5가지. 모든 프로세스는 종료 레벨 0x280에서 시작.
* @param lpdwFlags 종료 플래그를받는 변수를 가리키는 포인터. SHUTDOWN_NORETRY일 수 있음.
* @return 검색 성공/실패 여부

*/

BOOL test_GetProcessShutdownParameters(){

	#ifdef OQADBGPRINT
	printf("test_GetProcessShutdownParameters\n");
	#endif

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	BOOL result = FALSE;
	DWORD lpdwLevel = 0x280;
	DWORD lpdwFlags = SHUTDOWN_NORETRY;

	// 현재 호출 중인 프로세스의 종료 매개 변수를 가져옴. 함수 성공 시 nonzero.
	result = GetProcessShutdownParameters(&lpdwLevel, &lpdwFlags);
	if(result != 0){
		strcpy(buf, "SUCCESS");
		strcpy(msg, "GetProcessShutdownParameters() : SUCCESS");	
		result = TRUE;
	}else{ 
		strcpy(msg, GetErrorMessage(" GetProcessShutdownParameters() : FAIL \n\n Error Message :", GetLastError()));
		result = FALSE;
	}

	wresult(__FILE__, __LINE__, "GetProcessShutdownParameters", buf, "SUCCESS", msg);
	return result;
}


/**
* BOOL WINAPI GetProcessWorkingSetSize(
  _In_  HANDLE  hProcess,
  _Out_ PSIZE_T lpMinimumWorkingSetSize,
  _Out_ PSIZE_T lpMaximumWorkingSetSize
  );
* 지정된 프로세스의 최소와 최대 working set size를 검색
* @author : 손나영

* @param hProcess 작업 집합 크기를 가져올 프로세스의 핸들. 핸들에는 PROCESS_QUERY_INFORMATION 또는 PROCESS_QUERY_LIMITED_INFORMATION 액세스 권한 이 있어야 함.
* @param lpMinimumWorkingSetSize  지정된 프로세스의 최소 작업 집합 크기를 바이트 단위로받는 변수에 대한 포인터.
* @param lpMaximumWorkingSetSize 지정된 프로세스의 최대 작업 세트 크기를 바이트 단위로받는 변수에 대한 포인터.
* @return 검색 성공/실패 여부
*/

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
	char msg[BUFSIZ] = "FAIL";

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
		sprintf(msg, " GetProcessWorkingSetSize() : SUCCESS \n\n ProcessId : %d \n MinimumWorkingSetSize : %lu KB \n MaximumWorkingSetSize : %lu KB", pid, dwMin, dwMax);
		strcpy(buf, "SUCCESS");

	}else 
		strcpy(buf, GetErrorMessage(" GetProcessWorkingSetSize() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "GetProcessWorkingSetSize", buf, "SUCCESS", msg);

    CloseHandle(hProcess);

	return result;
}


/**
* BOOL WINAPI GetProcessWorkingSetSizeEx(
  _In_  HANDLE  hProcess,
  _Out_ PSIZE_T lpMinimumWorkingSetSize,
  _Out_ PSIZE_T lpMaximumWorkingSetSize,
  _Out_ PDWORD  Flags
  );
* 지정된 프로세스의 최소, 최대 working set size를 검색
* @author : 손나영
*
* @param hProcess 작업 집합 크기를 가져올 프로세스의 핸들. 핸들에는 PROCESS_QUERY_INFORMATION 또는 PROCESS_QUERY_LIMITED_INFORMATION 액세스 권한 이 있어야 함.
* @param lpMinimumWorkingSetSize  지정된 프로세스의 최소 작업 집합 크기를 바이트 단위로받는 변수에 대한 포인터.
* @param lpMaximumWorkingSetSize 지정된 프로세스의 최대 작업 세트 크기를 바이트 단위로받는 변수에 대한 포인터.
* @param Flags 최소 및 최대 작업 세트 크기의 적용을 제어하는 ​​플래그. 4가지.
* @return 검색 성공/실패 여부
*/

BOOL test_GetProcessWorkingSetSizeEx(){

	#ifdef OQADBGPRINT
	printf("test_GetProcessWorkingSetSizeEx\n");
	#endif

	BOOL result;
	HANDLE hProcess;
	SIZE_T dwMin, dwMax;
	DWORD flags = QUOTA_LIMITS_HARDWS_MIN_DISABLE;

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

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
	result = GetProcessWorkingSetSizeEx(hProcess, &dwMin, &dwMax, &flags);

	if (result != 0){
		sprintf(msg, " GetProcessWorkingSetSizeEx() : SUCCESS \n\n ProcessId : %d \n MinimumWorkingSetSize : %lu KB \n MaximumWorkingSetSize : %lu KB", pid, dwMin, dwMax);
		strcpy(buf, "SUCCESS");

	}else {
		strcpy(buf, GetErrorMessage(" GetProcessWorkingSetSizeEx() : FAIL \n\n Error Message :", GetLastError()));
		return FALSE;
	}
	wresult(__FILE__, __LINE__, "GetProcessWorkingSetSizeEx", buf, "SUCCESS", msg);

    CloseHandle(hProcess);

	return result;
}


/**
* BOOL WINAPI IsProcessInJob(
  _In_     HANDLE ProcessHandle,
  _In_opt_ HANDLE JobHandle,
  _Out_    PBOOL  Result
  );
* 프로세스가 지정된 작업에서 실행 중인지 여부를 결정
* @author : 손나영
*
* @param ProcessHandle 테스트 할 프로세스의 핸들. 핸들에는 PROCESS_QUERY_INFORMATION 또는 PROCESS_QUERY_LIMITED_INFORMATION 액세스 권한이 있어야 함.
* @param JobHandle 작업에 대한 핸들. 이 매개 변수가 NULL이면 함수는 프로세스가 모든 작업에서 실행 중인지 여부를 테스트.
* @param Result 프로세스가 작업에서 실행중인 경우 TRUE를 수신하는 값을 가리키는 포인터이며, 그렇지 않으면 FALSE.
* @return 실행중인지 여부 결정 성공/실패 여부
*/

BOOL test_IsProcessInJob(){

	#ifdef OQADBGPRINT
	printf("test_IsProcessInJob\n");
	#endif

	BOOL result;
	BOOL bInJob;
	HANDLE hProcess;

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";
	
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
		sprintf(msg, " IsProcessInJob() : SUCCESS");
		strcpy(buf, "SUCCESS");

	}else 
		strcpy(buf, GetErrorMessage(" IsProcessInJob() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "IsProcessInJob", buf, "SUCCESS", msg);

	return result;
}


/**
* BOOL WINAPI EnumProcesses(
  _Out_ DWORD *pProcessIds,
  _In_  DWORD cb,
  _Out_ DWORD *pBytesReturned
  );
* 시스템의 각 프로세스 오브젝트에 대한 프로세스 ID를 검색.
* @author : 손나영
*
* @param pProcessIds 프로세스 식별자 목록을 수신하는 배열에 대한 포인터.
* @param cb pProcessIds 배열 의 크기 ( 바이트).
* @param pBytesReturned pProcessIds 배열 에서 반환 된 바이트 수.
* @return ID 검색 성공/실패 여부.
*/

BOOL test_K32EnumProcesses(){

	#ifdef OQADBGPRINT
	printf("test_K32EnumProcesses\n");
	#endif

	DWORD arProc[1024],cb;
	BOOL result;
	BOOL re_result = FALSE;

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	// 프로세스의 목록을 배열에 구하고 개수를 계산한다.
	result = K32EnumProcesses(arProc,sizeof(arProc),&cb);
	
	if(result != 0){
		re_result = TRUE;
		sprintf(msg, " EnumProcesses() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}else{
		strcpy(msg, GetErrorMessage(" EnumProcesses() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "EnumProcesses", buf, "SUCCESS", msg);

	return re_result;
}

/** 
* BOOL WINAPI EnumProcessModules(
  _In_  HANDLE  hProcess,
  _Out_ HMODULE *lphModule,
  _In_  DWORD   cb,
  _Out_ LPDWORD lpcbNeeded
  );
* 지정된 프로세스의 각 모듈에 대한 핸들을 검색
*
* @param hProcess 프로세스에 대한 핸들.
* @param lphModule 모듈 핸들 목록을받는 배열.
* @param cb lphModule 배열 의 크기 ( 바이트).
* @param lpcbNeeded lphModule 배열 에 모든 모듈 핸들을 저장하는 데 필요한 바이트 수.
* @return 핸들 검색 성공/실패 여부.
*/

BOOL test_K32EnumProcessModules(){

	#ifdef OQADBGPRINT
	printf("test_K32EnumProcessModules\n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	DWORD arProc[1024];
	DWORD cb;

	HMODULE hModule;
	HANDLE hProcess;
	BOOL result;
	BOOL re_result;

	// 프로세스의 목록을 배열에 구하고 개수를 계산한다.
	EnumProcesses(arProc,sizeof(arProc),&cb);

	int pid = GetCurrentProcessId();

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE, pid);

	if(hProcess){

		// 첫번째 모듈(=프로세스 그 자체)의 이름을 구해 출력한다.
		result=K32EnumProcessModules(hProcess,&hModule,sizeof(hModule),&cb);

		if(result != 0){
			sprintf(msg, " EnumProcessModules() : SUCCESS");
			strcpy(buf, "SUCCESS");
			re_result = TRUE;
		}else{
			strcpy(msg, GetErrorMessage(" EnumProcessModules() : FAIL \n\n Error Message :", GetLastError()));
		}
	}else
		strcpy(msg, GetErrorMessage(" 프로세스를 open하지 못했습니다. \n\n OpenProcess 함수를 다시 체크하십시오. \n\n Error Message :", GetLastError()));
	wresult(__FILE__, __LINE__, "EnumProcessModules", buf, "SUCCESS", msg);

	return re_result;
}

/**
* BOOL WINAPI EnumProcessModulesEx(
  _In_  HANDLE  hProcess,
  _Out_ HMODULE *lphModule,
  _In_  DWORD   cb,
  _Out_ LPDWORD lpcbNeeded,
  _In_  DWORD   dwFilterFlag
  );
* 지정된 필터 조건을 충족시키는 지정된 프로세스의 각 모듈에 대한 핸들을 검색.
* @author : 손나영
*
* @param hProcess 프로세스에 대한 핸들.
* @param lphModule 모듈 핸들 목록을받는 배열.
* @param cb lphModule 배열 의 크기 ( 바이트).
* @param lpcbNeeded lphModule 배열 에 모든 모듈 핸들을 저장하는 데 필요한 바이트 수.
* @param dwFilterFlag 필터 기준. 4가지.
* @return  모듈에 대한 핸들 검색 성공/실패 여부.
*/

BOOL test_K32EnumProcessModulesEx(){

	#ifdef OQADBGPRINT
	printf("test_K32EnumProcessModulesEx\n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	DWORD arProc[1024];
	DWORD cb;

	HMODULE hModule;
	HANDLE hProcess;
	BOOL result;
	BOOL re_result;

	// 프로세스의 목록을 배열에 구하고 개수를 계산한다.
	EnumProcesses(arProc,sizeof(arProc),&cb);

	int pid = GetCurrentProcessId();

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE, pid);

	if(hProcess){

		// 첫번째 모듈(=프로세스 그 자체)의 이름을 구해 출력한다.
		result=K32EnumProcessModulesEx(hProcess, &hModule, sizeof(hModule), &cb, LIST_MODULES_ALL);

		if(result != 0){
			re_result = TRUE;
			sprintf(msg, " EnumProcessModulesEx() : SUCCESS");
			strcpy(buf, "SUCCESS");
		}else{
			strcpy(msg, GetErrorMessage(" EnumProcessModulesEx() : FAIL \n\n Error Message :", GetLastError()));
		}
	}else
		strcpy(msg, GetErrorMessage(" 프로세스를 open하지 못했습니다. \n\n OpenProcess 함수를 다시 체크하십시오. \n\n Error Message :", GetLastError()));
	wresult(__FILE__, __LINE__, "EnumProcessModulesEx", buf, "SUCCESS", msg);

	return re_result;
}


/**
* BOOL WINAPI InitializeProcessForWsWatch(
  _In_ HANDLE hProcess
  );
* 지정된 process의 working set을 모니터링 시작(초기화).
* @author : 손나영
*
* @param hProcess 프로세스에 대한 핸들. 핸들에는 PROCESS_QUERY_INFORMATION 액세스 권한이 있어야 함.
* @return 모니터링 시작 성공/실패 여부.
*/

BOOL test_K32InitializeProcessForWsWatch(){

	#ifdef OQADBGPRINT
	printf("test_K32InitializeProcessForWsWatch\n");
	#endif

	char msg[BUFSIZ] = "FAIL";

	/** hFile에 생성한 파일 */
	HANDLE hFile = CreateFile(L"손나영\\test_K32InitializeProcessForWsWatch.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	//HANDLE hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	hFile = CreateFile(L"손나영\\test_K32InitializeProcessForWsWatch.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	BOOL result = K32InitializeProcessForWsWatch(hFile);
	
	if(result != 0)
		strcpy(msg, "InitializeProcessForWsWatch() : SUCCESS");	
	else 
		strcpy(msg, GetErrorMessage(" InitializeProcessForWsWatch() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "InitializeProcessForWsWatch", msg, "InitializeProcessForWsWatch() : SUCCESS", msg);

	//추가된 페이지 가져오려면 GetWsChangesEx() function.
	return result;
}


/**
* BOOL WINAPI QueryProcessAffinityUpdateMode(
  _In_      HANDLE ProcessHandle,
  _Out_opt_ DWORD  lpdwFlags
  );
* 특정 프로세스의 affinity 업데이트 모드를 불러옴.
* @author : 손나영
*
* @param ProcessHandle 프로세스에 대한 핸들. 핸들에는 PROCESS_QUERY_INFORMATION 또는 PROCESS_QUERY_LIMITED_INFORMATION 액세스 권한이 있어야 함.
* @param lpdwFlags affinity 없데이트 모드.2가지.
* @return 업데이트 모드 불러오기 성공/실패 여부.
*/

/**
	특정 프로세스의 update mode 가져옴
*/
BOOL test_QueryProcessAffinityUpdateMode(){

	#ifdef OQADBGPRINT
	printf("test_QueryProcessAffinityUpdateMode\n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";
	
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
		
		sprintf(msg, "QueryProcessAffinityUpdateMode() : SUCCESS \n\n affinity update mode : %u", Flags);	
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(msg, GetErrorMessage(" QueryProcessAffinityUpdateMode() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "QueryProcessAffinityUpdateMode", buf, "SUCCESS", msg);

	return result;
} 


/**
* BOOL WINAPI SetProcessAffinityUpdateMode(
  _In_ HANDLE ProcessHandle,
  _In_ DWORD  dwFlags
  );
* 지정된 프로세스의 affinity 업데이트 모드 설정.
* @author : 손나영
*
* @param ProcessHandle 프로세스에 대한 핸들. 이 핸들은 GetCurrentProcess 함수에서 반환해야 함.
* @param dwFlags affinity 업데이트 모드. 2가지.
* @return  업데이트 모드 설정 성공/실패 여부.
*/

BOOL test_SetProcessAffinityUpdateMode(){

	#ifdef OQADBGPRINT
	printf("test_SetProcessAffinityUpdateMode \n");
	#endif

	BOOL result;
	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	// 0 : Disables dynamic update of the process affinity by the system.
	// PROCESS_AFFINITY_ENABLE_AUTO_UPDATE : Enables dynamic update of the process affinity by the system.
	// 프로세스의 유연성을 업데이트
	// 첫 번째 파라미터 : GetCurrentProcess함수 반환해야 함

	result = SetProcessAffinityUpdateMode(GetCurrentProcess(), 0);
	if(result != 0){
		sprintf(msg, "SetProcessAffinityUpdateMode() : SUCCESS \n\n프로세스의 affinity 갱신 ▶ value 값 : 0 \n→ 시스템에 의한 프로세스 affinity 동적 갱신 불가로 설정 \n\n(PROCESS_AFFINITY_ENABLE_AUTO_UPDATE로 설정 시 \n시스템의 프로세스 선호도를 동적으로 업데이트 가능)");
		strcpy(buf, "SUCCESS");
	}else {
		strcpy(buf, GetErrorMessage(" SetProcessAffinityUpdateMode() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "SetProcessAffinityUpdateMode", buf, "SUCCESS", msg);
	return result;
}

/**
* BOOL WINAPI SetProcessDEPPolicy(
  _In_ DWORD dwFlags
  );
* 32 비트 프로세스에 대한 데이터 실행 방지 (DEP) 및 DEP-ATL thunk emulation 설정을 변경.
* @author : 손나영
*
* @param dwFlags 3가지.
* @return 변경 성공/실패 여부.
*/


BOOL test_SetProcessDEPPolicy(){
	
	#ifdef OQADBGPRINT
	printf("test_SetProcessDEPPolicy\n");
	#endif

	BOOL result = FALSE;
	
	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";
	
	// DEP(Data Execution Prevention) : 데이타 실행 방지
	// SetProcessDEPPolicy 함수는 32bit process를 위한 setting
	// 따라서, 현 windows 환경(64bit)에서는 fail 뜨는 것0이 정상

	// 파라미터 값 0 
	// DEP 시스템 정책이 Optln 이거나 OptOut, 또는 해당 프로세서에 DEP 사용할 때\
	// 값을 0으로 주면 → DEP가 비활성화 처리 됨
	
	result = SetProcessDEPPolicy(0);
	
	if(result != FALSE)
		strcpy(msg, "SetProcessDEPPolicy() : SUCCESS");	
	else 
		strcpy(msg, " SetProcessDEPPolicy() : FAIL \n\n \n(해당 함수는 32 bit 전용입니다");
		
	wresult(__FILE__, __LINE__, "SetProcessDEPPolicy", msg, "SetProcessDEPPolicy() : SUCCESS", msg);

	return result;
}


/**
* BOOL WINAPI SetProcessPriorityBoost(
  _In_ HANDLE hProcess,
  _In_ BOOL   DisablePriorityBoost
  );
* 시스템이 지정된 프로세스의 스레드 우선 순위를 일시적으로 높이는 기능을 비활성화하거나 활성화.
* @author : 손나영
*
* @param hProcess 프로세스에 대한 핸들. 이 핸들에는 PROCESS_SET_INFORMATION 액세스 권한이 있어야 함.
* @param DisablePriorityBoost 이 매개 변수가 TRUE이면 동적 부스팅이 비활성화됨. 매개 변수가 FALSE이면 동적 부스터가 활성화 됨.
* @return 활성화 또는 비활성화 성공/실패 여부.
*/

BOOL test_SetProcessPriorityBoost(){
	
	#ifdef OQADBGPRINT
	printf("test_SetProcessPriorityBoost\n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";
	int pid = GetCurrentProcessId();

	BOOL re_result = FALSE;
	BOOL result;
	// This handle must have the PROCESS_SET_INFORMATION access right.
	HANDLE hProcess = OpenProcess(PROCESS_SET_INFORMATION , FALSE, pid);

	// To restore normal behavior, call SetProcessPriorityBoost with DisablePriorityBoost set to FALSE.
	result = SetProcessPriorityBoost(hProcess, FALSE);

	if(result != 0){
		re_result = TRUE;
		sprintf(msg, " SetProcessPriorityBoost() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}else{
		strcpy(msg, GetErrorMessage(" SetProcessPriorityBoost() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "SetProcessPriorityBoost", buf, "SUCCESS", msg);

	return re_result;
}


/**
* BOOL WINAPI SetProcessShutdownParameters(
  _In_ DWORD dwLevel,
  _In_ DWORD dwFlags
  );
* 현재 호출중인 프로세스의 종료 매개 변수를 설정하라. 이 함수는 시스템의 다른 프로세스와 관련된 프로세스의 종료 순서를 셋팅함.
* @author : 손나영
*
* @param 시스템의 다른 프로세스와 관련된 프로세스의 종료 우선 순위. 모든 프로세스는 종료 레벨 0x280에서 시작.
* @param SHUTDOWN_NORETRY일 수 있음.
* @return 종료 순서 셋팅 성공/실패 여부.
*/

BOOL test_SetProcessShutdownParameters(){

	#ifdef OQADBGPRINT
	printf("test_SetProcessShutdownParameters\n");
	#endif

	BOOL result;
	char msg[BUFSIZ] = "FAIL";

	// 현재 호출중인 프로세스의 종료 매개 변수를 설정
	// 첫 번째 파라미터 : 프로세스 종료 우선 순위. value 값 다섯 가지 중에 set.
	// 000 ~ 0FF 시스템은 마지막 종료 범위를 예약함	/ 100-1FF 응용 프로그램은 마지막 종료 범위를 예약함
	// 200-2FF 응용 프로그램이 "종료 범위"사이에 예약됨	/ 300-3FF 응용 프로그램이 첫 번째 종료 범위를 예약함
	// 400-4FF 시스템이 첫 번째 종료 범위를 예약함
	// 두 번째 파라미터 : SHUTDOWN_NORETRY → 시스템은 사용자에 대한 재시도 대화 상자를 표시하지 않고 프로세스를 종료
	
	result = SetProcessShutdownParameters(0x3ff, SHUTDOWN_NORETRY);
	if(result != 0)
		strcpy(msg, "SetProcessShutdownParameters() : SUCCESS");	
	else 
		strcpy(msg, GetErrorMessage(" SetProcessShutdownParameters() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "SetProcessShutdownParameters", msg, "SetProcessShutdownParameters() : SUCCESS", msg);
	return result;
}
