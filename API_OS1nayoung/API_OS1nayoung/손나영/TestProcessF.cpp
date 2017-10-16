#include "TestProcessF.h"
#include <TlHelp32.h>

BOOL test_SetProcessDEPPolicy(){
	
	BOOL result = true;
	
	char *buf = NULL;
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_SetProcessDEPPolicy\n");
	#endif

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

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_SetProcessAffinityUpdateMode\n");
	#endif

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

	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_SetProcessShutdownParameters\n");
	#endif

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

	char meg[BUFSIZ] = "FAIL";

	DWORD lpdwLevel;
	DWORD lpdwFlags;

	#ifdef OQADBGPRINT
	printf("test_GetProcessShutdownParameters\n");
	#endif

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

BOOL test_K32InitializeProcessForWsWatch(){

	char meg[BUFSIZ] = "FAIL";

	/** hFile�� ������ ���� */
	//HANDLE hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	HANDLE hFile = CreateFile(L"�ճ���\\test_K32InitializeProcessForWsWatch.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	hFile = CreateFile(L"�ճ���\\test_K32InitializeProcessForWsWatch.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

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

	//HANDLE hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test2.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test2.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	HANDLE hFile = CreateFile(L"�ճ���\\test_QueryProcessAffinityUpdateMode.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	hFile = CreateFile(L"�ճ���\\test_QueryProcessAffinityUpdateMode.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

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


/**
	process�� ���� �����ϴ� �����͸� ���� �޸� ������ ���� ���Ѽ� 
	page fault�� page swap ���� ���� ������ ���� �����ϰ� ��.
	process working set���� code pages�� data pages�� ���Ե�.
	set���� �����ϴ� ���� Trim
*/
BOOL test_GetProcessWorkingSetSize(){

	BOOL result;
	HANDLE hProcess;
	SIZE_T dwMin, dwMax;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	/** process �ĺ��� ������ */
	int num = GetCurrentProcessId();

	/**	PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		num : GetCurrentProcessId()		*/
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, num);

	/** OpenProcess() ����	*/
	if (!hProcess) {
		strcpy(buf, GetErrorMessage(" OpenProcess() : FAIL \n\n Error Message :", GetLastError()));
		return 1;
	}

	/**	process�� working set size�� ������	*/
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

BOOL test_GetProcessWorkingSetSizeEx(){
	
	BOOL result;
	HANDLE hProcess;
	SIZE_T dwMin, dwMax;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	/** process �ĺ��� ������ */
	int num = GetCurrentProcessId();

	/**	PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		num : GetCurrentProcessId()		*/
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, num);

	printf("aa");

	/** OpenProcess() ����	*/
	if (!hProcess) {
		strcpy(buf, GetErrorMessage(" OpenProcess() : FAIL \n\n Error Message :", GetLastError()));
		return 1;
	}

	printf("bb");

	/**	process�� working set size�� ������	*/
	result = GetProcessWorkingSetSizeEx(hProcess, &dwMin, &dwMax, (PDWORD)QUOTA_LIMITS_HARDWS_MIN_ENABLE);

	printf("cc");

	printf("dfs");
	Sleep(2000);
	if(result == ERROR_SUCCESS){
		sprintf(meg, " GetProcessWorkingSetSizeEx() : SUCCESS \n\n ProcessId : %d \n MinimumWorkingSetSize : %lu KB \n MaximumWorkingSetSize : %lu KB", num, dwMin, dwMax);
		strcpy(buf, "SUCCESS");

	}else{
		printf("sdfdf");
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