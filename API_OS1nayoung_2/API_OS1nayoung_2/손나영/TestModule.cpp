#include "TestModule.h"

/**
* DWORD WINAPI GetModuleBaseName(
  _In_     HANDLE  hProcess,
  _In_opt_ HMODULE hModule,
  _Out_    LPTSTR  lpBaseName,
  _In_     DWORD   nSize
  );
* ������ ����� �⺻ �̸��� �˻�
* @author : �ճ���
*
* @param ����� �����ϴ� ���μ����� �ڵ�.  PROCESS_QUERY_INFORMATION �� PROCESS_VM_READ �׼��� ����.
* @param ��⿡ ���� �ڵ�.
* @param ����� �⺻ �̸��� �����ϴ� ���ۿ� ���� ������. 
* @param lpBaseName ���� �� ũ�� ( ���� ��).
* @return ���ۿ� ���� �� ���ڿ��� ���̸� ���ڷ� ����.
*/

BOOL test_K32GetModuleBaseNameA(){

	#ifdef OQADBGPRINT
	printf("test_K32GetModuleBaseNameA \n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	DWORD result;
	HANDLE hProcess;
	HMODULE hMod = NULL;

	int pid = GetCurrentProcessId();
	TCHAR szProcessName[MAX_PATH] = L"<unknown>";
	
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION  | PROCESS_VM_READ, FALSE, pid);
	result = K32GetModuleBaseNameA(hProcess, hMod, (LPSTR)szProcessName, sizeof(szProcessName)/sizeof(TCHAR) );

	if(result == 0){
		strcpy(msg, GetErrorMessage(" K32GetModuleBaseNameA() : FAIL \n\n Error Message :", GetLastError()));
	}else{

		sprintf(msg, " K32GetModuleBaseNameA() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}
	wresult(__FILE__, __LINE__, "K32GetModuleBaseNameA", buf, "SUCCESS", msg);
	return result;
}

/**
* DWORD WINAPI GetModuleBaseName(
  _In_     HANDLE  hProcess,
  _In_opt_ HMODULE hModule,
  _Out_    LPTSTR  lpBaseName,
  _In_     DWORD   nSize
  );
* ������ ����� �⺻ �̸��� �˻�
* @author : �ճ���
*
* @param ����� �����ϴ� ���μ����� �ڵ�.  PROCESS_QUERY_INFORMATION �� PROCESS_VM_READ �׼��� ����.
* @param ��⿡ ���� �ڵ�.
* @param ����� �⺻ �̸��� �����ϴ� ���ۿ� ���� ������. 
* @param lpBaseName ���� �� ũ�� ( ���� ��).
* @return ���ۿ� ���� �� ���ڿ��� ���̸� ���ڷ� ����.
*/

BOOL test_K32GetModuleBaseNameW(){

	#ifdef OQADBGPRINT
	printf("test_K32GetModuleBaseNameW \n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	DWORD result;
	HANDLE hProcess;
	HMODULE hMod = NULL;

	int pid = GetCurrentProcessId();
	TCHAR szProcessName[MAX_PATH] = L"<unknown>";

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE, pid);
	result = K32GetModuleBaseNameW(hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(TCHAR) );

	if(result == 0){
		strcpy(msg, GetErrorMessage(" GetModuleBaseNameW() : FAIL \n\n Error Message :", GetLastError()));
	}else{

		sprintf(msg, " GetModuleBaseNameW() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}
	wresult(__FILE__, __LINE__, "GetModuleBaseNameW", buf, "SUCCESS", msg);
	return result;
}



/**
* DWORD WINAPI GetModuleFileNameEx(
  _In_     HANDLE  hProcess,
  _In_opt_ HMODULE hModule,
  _Out_    LPTSTR  lpFilename,
  _In_     DWORD   nSize
  );
* ������ ����� �����ϴ� ������ ������ ��θ� �˻�
* @author : �ճ���
*
* @param hProcess ����� �����ϴ� ���μ����� �ڵ�.
* @param hModule ��⿡ ���� �ڵ�.
* @param lpFilename ��⿡ ���� ������ ��θ��޴� ���ۿ� ���� ������.
* @param nSize���ڷ� �� lpFilename ������ ũ��.
* @return ���ۿ� ���� �� ���ڿ��� ����.
*/

BOOL test_K32GetModuleFileNameExA(){

	#ifdef OQADBGPRINT
	printf("test_K32GetModuleFileNameExA \n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	DWORD result;
    HMODULE hMods[1024];
    HANDLE hProcess;
    DWORD cbNeeded;
    unsigned int i;

    // Print the process identifier.
	int pid = GetCurrentProcessId();

    // Get a handle to the process.

    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
        PROCESS_VM_READ,
        FALSE, pid);
    if (NULL == hProcess)
        return 1;

    // Get a list of all the modules in this process.

    DWORD cbCurrent = sizeof(hMods);
	
	// Ư�� ���μ������� �� ����� �ڵ��� ������ enumprocessmoduels
	if (EnumProcessModules(hProcess, hMods, cbCurrent, &cbNeeded)){
		DWORD cbAllowed = min(cbCurrent, cbNeeded);                   

		//for(i=0; i<(cbAllowed/sizeof(HMODULE)); i++){
		//�� ���� �ʰ� �Ϻθ� ���. cbAllowed �� ���� �ʹ� ����.
		for(i=0; i<1; i++){
			TCHAR szModName[MAX_PATH];

			// Get the full path to the module's file.

			result = K32GetModuleFileNameExA(hProcess, hMods[i], (LPSTR)szModName, sizeof(szModName)/sizeof(TCHAR));

			// if the function succeeds, the length of the string copied to he buffer is returned.
			if(result != 0){
				// Print the module name and handle value.
				sprintf(msg, "K32GetModuleFileNameExA() : SUCCESS \n\n%S(0x%08X)", (LPSTR)szModName, hMods[i]);
				strcpy(buf, "SUCCESS");
			}else{
				strcpy(msg, GetErrorMessage(" K32GetModuleFileNameExA() : FAIL \n\n Error Message :", GetLastError()));
			}
			
		}
		wresult(__FILE__, __LINE__, "K32GetModuleFileNameExA", buf, "SUCCESS", msg);
	}
	CloseHandle(hProcess);

	return result;
}


/**
* DWORD WINAPI GetModuleFileNameEx(
  _In_     HANDLE  hProcess,
  _In_opt_ HMODULE hModule,
  _Out_    LPTSTR  lpFilename,
  _In_     DWORD   nSize
  );
* ������ ����� �����ϴ� ������ ������ ��θ� �˻�
* @author : �ճ���
*
* @param hProcess ����� �����ϴ� ���μ����� �ڵ�.
* @param hModule ��⿡ ���� �ڵ�.
* @param lpFilename ��⿡ ���� ������ ��θ��޴� ���ۿ� ���� ������.
* @param nSize���ڷ� �� lpFilename ������ ũ��.
* @return ���ۿ� ���� �� ���ڿ��� ����.
*/
BOOL test_K32GetModuleFileNameExW(){

	#ifdef OQADBGPRINT
	printf("test_K32GetModuleFileNameExW \n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	DWORD result;
    HMODULE hMods[1024];
    HANDLE hProcess;
    DWORD cbNeeded;
    unsigned int i;

    // Print the process identifier.
	int pid = GetCurrentProcessId();

    // Get a handle to the process.

    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (NULL == hProcess)
        return 1;

    // Get a list of all the modules in this process.

    DWORD cbCurrent = sizeof(hMods);
	
	// Ư�� ���μ������� �� ����� �ڵ��� ������ enumprocessmoduels
	if (EnumProcessModules(hProcess, hMods, cbCurrent, &cbNeeded)){
		DWORD cbAllowed = min(cbCurrent, cbNeeded);                   

		//for(i=0; i<(cbAllowed/sizeof(HMODULE)); i++){
		//�� ���� �ʰ� �Ϻθ� ���. cbAllowed �� ���� �ʹ� ����.
		for(i=0; i<1; i++){
			TCHAR szModName[MAX_PATH];

			// Get the full path to the module's file.

			result = K32GetModuleFileNameExW(hProcess, hMods[i], szModName, sizeof(szModName)/sizeof(TCHAR));

			// if the function succeeds, the length of the string copied to he buffer is returned.
			if(result != 0){
				// Print the module name and handle value.
				sprintf(msg, "k32GetModuleFileNameExW() : SUCCESS \n\n%S(0x%08X)", szModName, hMods[i]);
				strcpy(buf, "SUCCESS");
			}else{
				strcpy(msg, GetErrorMessage(" k32GetModuleFileNameExW() : FAIL \n\n Error Message :", GetLastError()));
			}
			
		}
		wresult(__FILE__, __LINE__, "k32GetModuleFileNameExW", buf, "SUCCESS", msg);
	}
	CloseHandle(hProcess);

	return result;
}


/**
* BOOL WINAPI GetModuleInformation(
  _In_  HANDLE       hProcess,
  _In_  HMODULE      hModule,
  _Out_ LPMODULEINFO lpmodinfo,
  _In_  DWORD        cb
  );
* MODULEINFO ����ü �� ������ ��⿡ ���� ������ �˻�
* @author : �ճ���
*
* @param hProcess ����� �����ϴ� ���μ����� �ڵ�.
* @param hModule ��⿡ ���� �ڵ�.
* @param lpmodinfo ��⿡ ���� �������޴� MODULEINFO ����ü�� ���� ������ .
* @param cb MODULEINFO ����ü �� ũ�� ( ����Ʈ).
* @return �˻� ����/���� ����
*/

BOOL test_K32GetModuleInformation(){

	#ifdef OQADBGPRINT
	printf("test_K32GetModuleInformation \n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";
	int pid = GetCurrentProcessId();

	BOOL result;
	HANDLE hProcess;
	HMODULE hModule = NULL; // A handle to the module.
	MODULEINFO lpmodinfo;	// A pointer to the MODULEINFO structure that receives information about the module.

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

    if (hProcess == NULL)
        return FALSE;

	result = K32GetModuleInformation(hProcess, hModule, &lpmodinfo, sizeof(lpmodinfo));

	if(result != 0){
		sprintf(msg, " K32GetModuleInformation() : SUCCESS ");
		strcpy(buf, "SUCCESS");

	}else 
		strcpy(msg, GetErrorMessage(" K32GetModuleInformation() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "K32GetModuleInformation", buf, "SUCCESS", msg);

	return result;
}


/**
* DWORD WINAPI LoadModule(
  _In_ LPCSTR lpModuleName,
  _In_ LPVOID lpParameterBlock
  );
* ���� ���α׷����ε��ϰ� �����ϰų� ���� ���� ���α׷��� �� �ν��Ͻ��� ����. 16bit ����.
* @author : �ճ���
*
* @param lpModuleName ������ ���� ���α׷��� ���� �̸�
* @param lpParameterBlock �� ���� ���α׷��� �Ű� ���� ����� ���� �ϴ� ���� ���α׷� ���� LOADPARMS32 ������ ���� ������
* @return ���� �� 31���� ŭ
*/

/**
	loads and executes an application
	only with 16bit version. CreateProcess �Լ� ���.
	*/
BOOL test_LoadModule(){

	#ifdef OQADBGPRINT
	printf("test_LoadModule\n");
	#endif

	typedef struct tagLOADPARMS32 { 
		LPSTR lpEnvAddress;  // address of environment strings 
		LPSTR lpCmdLine;     // address of command line 
		LPSTR lpCmdShow;     // how to show new program 
		DWORD dwReserved;    // must be zero 
	} LOADPARMS32;

	//LPVOID lp;
	LOADPARMS32 lp;
	char CmdLine[2]={0,};
	WORD CmdShow[2]={2,SW_SHOWNORMAL};

	lp.lpEnvAddress = NULL;
	lp.lpCmdLine = CmdLine;
	lp.lpCmdShow = (LPSTR)&CmdShow;
	lp.dwReserved = 0;


	DWORD result;
	BOOL value = FALSE;

	int wresult_value=0;
	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";
	char BBB[BUFSIZ] = "FAIL";

	result = LoadModule("notepad.exe", &lp);

	// ���� �� �� return value is greater than 31 
	if(result>31){
		strcpy(msg, " LoadModule() : SUCCESS \n\n Notepad loaded");
		Sleep(500);

		HWND window;
		DWORD pid;
		HANDLE wndHandle;

		window = FindWindow(L"notepad", NULL);
		if(!window){
			strcpy(msg, GetErrorMessage(" FindWindow() : FAIL \n\n LoadModule �� FindWindow �Լ��� �ٽ� Ȯ���Ͻʽÿ�. \n Error Message :", GetLastError()));
			return FALSE;
		}
		GetWindowThreadProcessId(window, &pid);
		if(!pid){
			strcpy(msg, " GetWindowThreadProcessId() : FAIL \n\n LoadModule �� pid �ҷ����� ������ �ٽ� Ȯ���Ͻʽÿ�.");
			return FALSE;
		}

		wndHandle = OpenProcess(PROCESS_TERMINATE,FALSE, pid);

		BOOL result2;
		result2 = TerminateProcess(wndHandle, 0);

		if(result2 == 0)
			strcpy(msg, " LoadModule() : SUCCESS \n\n �ٸ�, �����Ų �޸����� ���������� ������� �ʾ�����, \n TerminateProcess �Լ��� �ٽ� Ȯ���Ͻʽÿ�.");

		wresult_value = 1;
		value = TRUE;

	}else if(result == 0){
		strcpy(msg, " LoadModule() : FAIL \n\n The system is out of memory or resources");

	}else if(result == ERROR_BAD_FORMAT){
		strcpy(msg, "  LoadModule() : FAIL \n\n The .exe file is invalid");

	}else if(result == ERROR_FILE_NOT_FOUND){
		strcpy(msg, "  LoadModule() : FAIL \n\n The specified file was not found");

	}else if(result == ERROR_PATH_NOT_FOUND){
		strcpy(msg, " LoadModule() : FAIL \n\n The specified path was not found");

	}else{
		strcpy(msg, GetErrorMessage("  LoadModule() : FAIL \n\n 16bit������ �����Ǵ� �Լ��Դϴ�.\n LoadModule ��� CreateProcess �Լ��� ����� �� �ֽ��ϴ�.\n\n Error Message :", GetLastError()));
	}

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "LoadModule", buf, "1", msg);

	return value;
}


/**
* BOOL WINAPI Module32First (
  _HANDLE hSnapshot, 
  _Inout_ LPMODULEENTRY32 lpme
  );
* ���μ����� ���õ� ù ��° ��⿡ ���� ������ �˻�
* @author : �ճ���
*
* @param hSnapshot CreateToolhelp32Snapshot �Լ��� ���� ���� ȣ�⿡�� ��ȯ �� ���� �� �ڵ�.
* @param lpme MODULEENTRY32 ����ü�� ���� ������ .
* @return �˻� ����/���� ����
*/

/**
		  ���μ����� ������ first ��⿡ ���� ���� ����
*/
BOOL test_Module32FirstW(){   //ù ��° ���� : CreateToolhelp32Snapshot �Լ��� �ҷ��;� �� 

	#ifdef OQADBGPRINT
	printf("test_Module32FirstW\n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	BOOL result;
	HANDLE hshot = NULL;
	
	MODULEENTRY32 me32 = {0};
	me32.dwSize = sizeof( MODULEENTRY32 );

	hshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
	result = Module32FirstW(hshot, &me32);

	if(result == TRUE){
		sprintf(msg, " Module32FirstW : PASS \n\n CreateToolhelp32Snapshot()�� first ��� ���� ���� \n first entry �� copy to the buffer");
		strcpy(buf, "SUCCESS");
	}else{
		CloseHandle(hshot);
		
	}
	wresult(__FILE__, __LINE__, "Module32FirstW", buf, "SUCCESS", msg);  

	return result;
}


/**
* BOOL WINAPI Module32Next(
  _In_  HANDLE          hSnapshot,
  _Out_ LPMODULEENTRY32 lpme
  );
* ���μ��� �Ǵ� ������� ������ ���� ��⿡ ���� ������ �˻�.
* @author : �ճ���
*
* @param hSnapshot CreateToolhelp32Snapshot �Լ��� ���� ���� ȣ�⿡�� ��ȯ �� ���� �� �ڵ�.
* @param lpme MODULEENTRY32 ����ü�� ���� ������.
* @return �˻� ����/���� ����
*/

BOOL test_Module32NextW(){   // ù ��° ���� : CreateToolhelp32Snapshot �Լ��� �ҷ��;� ��

	#ifdef OQADBGPRINT
	printf("test_Module32NextW\n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	BOOL result;
	HANDLE hshot = NULL;
	
	MODULEENTRY32 me32 = {0};
	me32.dwSize = sizeof( MODULEENTRY32 );

	hshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
	result = Module32NextW(hshot, &me32);

	if(result == TRUE){
		sprintf(msg, "Module32NextW : PASS \n\n CreateToolhelp32Snapshot()�� next ��� ���� ���� \n next entry �� copy to the buffer");
		strcpy(buf, "SUCCESS");
	}else{
		CloseHandle(hshot);
	}
	wresult(__FILE__, __LINE__, "Module32FirstW", buf, "SUCCESS", msg);  

	return result;
}
