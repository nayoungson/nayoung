#include "TestProcessF.h"
#include <TlHelp32.h>

BOOL test_SetProcessDEPPolicy(){
	
	#ifdef OQADBGPRINT
	printf("test_SetProcessDEPPolicy\n");
	#endif

	BOOL result = true;
	
	char *buf = NULL;
	char meg[BUFSIZ] = "FAIL";
	
	// DEP(Data Execution Prevention) : ����Ÿ ���� ����
	// SetProcessDEPPolicy �Լ��� 32bit process�� ���� setting
	// ����, �� windows ȯ��(64bit)������ fail �ߴ� ��0�� ����

	// �Ķ���� �� 0 
	// DEP �ý��� ��å�� Optln �̰ų� OptOut, �Ǵ� �ش� ���μ����� DEP ����� ��\
	// ���� 0���� �ָ� �� DEP�� ��Ȱ��ȭ ó�� ��
	if(SetProcessDEPPolicy(0))
		strcpy(meg, "SetProcessDEPPolicy() : SUCCESS");	
	else 
		strcpy(meg, GetErrorMessage(" SetProcessDEPPolicy() : FAIL \n\n \n(�ش� �Լ��� 32 bit �����Դϴ�. \n���� ���� �׽�Ʈ�ϰ� �ִ� windows ȯ���� \n64bit��� fail�� �����Դϴ�.)\n\nError Message :", GetLastError()));
		
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
	// ���μ����� �������� ������Ʈ
	// ù ��° �Ķ���� : GetCurrentProcess�Լ� ��ȯ�ؾ� ��
	if(SetProcessAffinityUpdateMode(GetCurrentProcess(), 0)!=0){
		sprintf(meg, "SetProcessAffinityUpdateMode() : SUCCESS \n\n���μ����� affinity ���� �� value �� : 0 \n�� �ý��ۿ� ���� ���μ��� affinity ���� ���� �Ұ��� ���� \n\n(PROCESS_AFFINITY_ENABLE_AUTO_UPDATE�� ���� �� \n�ý����� ���μ��� ��ȣ���� �������� ������Ʈ ����)");
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

	// ���� ȣ������ ���μ����� ���� �Ű� ������ ����
	// ù ��° �Ķ���� : ���μ��� ���� �켱 ����. value �� �ټ� ���� �߿� set.
	// 000 ~ 0FF �ý����� ������ ���� ������ ������	/ 100-1FF ���� ���α׷��� ������ ���� ������ ������
	// 200-2FF ���� ���α׷��� "���� ����"���̿� �����	/ 300-3FF ���� ���α׷��� ù ��° ���� ������ ������
	// 400-4FF �ý����� ù ��° ���� ������ ������
	// �� ��° �Ķ���� : SHUTDOWN_NORETRY �� �ý����� ����ڿ� ���� ��õ� ��ȭ ���ڸ� ǥ������ �ʰ� ���μ����� ����
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

	// ���� ȣ�� ���� ���μ����� ���� �Ű� ������ �˻�. �Լ� ���� �� nonzero.
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
	������ process�� working set�� ����͸� ����(�ʱ�ȭ)
*/
BOOL test_K32InitializeProcessForWsWatch(){

	#ifdef OQADBGPRINT
	printf("test_K32InitializeProcessForWsWatch\n");
	#endif

	char meg[BUFSIZ] = "FAIL";

	/** hFile�� ������ ���� */
	HANDLE hFile = CreateFile(L"�ճ���\\test_K32InitializeProcessForWsWatch.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	//HANDLE hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	hFile = CreateFile(L"�ճ���\\test_K32InitializeProcessForWsWatch.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	BOOL result = InitializeProcessForWsWatch(hFile);
	
	if(result != 0)
		strcpy(meg, "InitializeProcessForWsWatch() : SUCCESS");	
	else 
		strcpy(meg, GetErrorMessage(" InitializeProcessForWsWatch() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "InitializeProcessForWsWatch", meg, "InitializeProcessForWsWatch() : SUCCESS", meg);

	//�߰��� ������ �˻��Ϸ��� GetWsChangesEx() function.
	return true;
}

/**
	Ư�� ���μ����� update mode �˻�
*/
BOOL test_QueryProcessAffinityUpdateMode(){

	#ifdef OQADBGPRINT
	printf("test_QueryProcessAffinityUpdateMode\n");
	#endif

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";
	
	DWORD Flags = PROCESS_AFFINITY_ENABLE_AUTO_UPDATE;

	/** hFile�� ������ ���� */
	HANDLE hFile = CreateFile(L"�ճ���\\test_QueryProcessAffinityUpdateMode.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//HANDLE hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test2.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test2.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	hFile = CreateFile(L"�ճ���\\test_QueryProcessAffinityUpdateMode.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	/** �� ��° �Ķ���� 0 : �ý��ۿ� ���� ���μ��� affinity�� ���� ���� �Ұ� 
					    PROCESS_AFFINITY_ENABLE_AUTO_UPDATE : �ý��ۿ� ���� ���μ��� affinity�� ���� ���� ����	*/
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
	
	/** process �ĺ��� ������ */
	DWORD pid = GetCurrentProcessId();

	/**	PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		pid : GetCurrentProcessId()		*/
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, pid);

	/** OpenProcess() ����	*/
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
	process�� ���� �����ϴ� �����͸� ���� �޸� ������ ���� ���Ѽ� 
	page fault�� page swap ���� ���� ������ ���� �����ϰ� ��.
	process working set���� code pages�� data pages�� ���Ե�.
	set���� �����ϴ� ���� Trim
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

	/** process �ĺ��� ������ */
	int pid = GetCurrentProcessId();

	/**	PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		pid : GetCurrentProcessId()		*/
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, pid);

	/** OpenProcess() ����	*/
	if (!hProcess) {
		strcpy(buf, GetErrorMessage(" OpenProcess() : FAIL \n\n Error Message :", GetLastError()));
		return 1;
	}

	/**	process�� working set size�� ������	*/
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
	
	/** process �ĺ��� ������ */
	int pid = GetCurrentProcessId();

	/**	PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		pid : GetCurrentProcessId()		*/
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, pid);

	/** OpenProcess() ����	*/
	if (!hProcess) {
		strcpy(buf, GetErrorMessage(" OpenProcess() : FAIL \n\n Error Message :", GetLastError()));
		return 1;
	}

	/** process�� ������ �۾����� ���� ������ ���� ����	*/
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
	
	/** OpenProcess() ����	*/
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

/** 32bit ���μ����� ���� */
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
	
	/** OpenProcess() ����	*/
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

/** ���� ���μ����� �����带 �������� �� ���μ����� ���� ť�� �÷����մϴ�. */
BOOL test_FlushProcessWriteBuffers(){

	#ifdef OQADBGPRINT
	printf("test_FlushProcessWriteBuffers\n");
	#endif

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	//__rdtsc : ���μ��� �ð� ������ ��ȯ. ������ �缳�� �� Ŭ�� �ֱ� �� ���.

	unsigned __int64 t1 = __rdtsc();
	FlushProcessWriteBuffers();
	unsigned __int64 t2 = __rdtsc() ;
	
	printf("%d \n", t1);
	printf("%d \n", t2);

	if(t1 != t2){
		sprintf(meg, " FlushProcessWriteBuffers() : SUCCESS");
		//sprintf(meg, " FlushProcessWriteBuffers() : SUCCESS \n\n Flush �� __rdtsc = %d \n Flush �� __rdtsc = %d ", t1, t2);
		strcpy(buf, "SUCCESS");
	}else{
		strcpy(buf, GetErrorMessage(" FlushProcessWriteBuffers() : FAIL \n\n Error Message :", GetLastError()));
	}
	wresult(__FILE__, __LINE__, "FlushProcessWriteBuffers", buf, "SUCCESS", meg);

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

	/** OpenProcess() ����	
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

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	/** process �ĺ��� ������ */
	int pid = GetCurrentProcessId();

	/**	PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		pid : GetCurrentProcessId()		*/
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, pid);

	/** OpenProcess() ����	*/
	if (!hProcess) {
		strcpy(buf, GetErrorMessage(" OpenProcess() : FAIL \n\n Error Message :", GetLastError()));
		return 1;
	}

	/**	process�� working set size�� ������	*/
	/** 0xC0000005: 0x00000000 ��ġ�� ����ϴ� ���� �׼��� ������ �߻��߽��ϴ�. */
	result = GetProcessWorkingSetSizeEx(hProcess, &dwMin, &dwMax, 0);
	
	if(!result){
		sprintf(meg, " GetProcessWorkingSetSizeEx() : SUCCESS \n\n ProcessId : %d \n MinimumWorkingSetSize : %lu KB \n MaximumWorkingSetSize : %lu KB", pid, dwMin, dwMax);
		strcpy(buf, "SUCCESS");
	}else{
		strcpy(buf, GetErrorMessage(" GetProcessWorkingSetSize() : FAIL \n\n Error Message :", GetLastError()));
	}
	wresult(__FILE__, __LINE__, "GetProcessWorkingSetSizeEx", buf, "SUCCESS", meg);

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


/** ������ process�� ���� ĳ���� ����(flush) 
BOOL test_FlushProcessWriteBuffers(){
	
	FlushProcessWriteBuffers();
	printf("Sdfds");  // ���л�Ȳ

	return true;
}
*/

