#include "TestModule.h"

/**
* DWORD WINAPI GetModuleBaseName(
  _In_     HANDLE  hProcess,
  _In_opt_ HMODULE hModule,
  _Out_    LPTSTR  lpBaseName,
  _In_     DWORD   nSize
  );
* 지정된 모듈의 기본 이름을 검색
* @author : 손나영
*
* @param 모듈을 포함하는 프로세스의 핸들.  PROCESS_QUERY_INFORMATION 및 PROCESS_VM_READ 액세스 권한.
* @param 모듈에 대한 핸들.
* @param 모듈의 기본 이름을 수신하는 버퍼에 대한 포인터. 
* @param lpBaseName 버퍼 의 크기 ( 문자 수).
* @return 버퍼에 복사 된 문자열의 길이를 문자로 지정.
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
* 지정된 모듈의 기본 이름을 검색
* @author : 손나영
*
* @param 모듈을 포함하는 프로세스의 핸들.  PROCESS_QUERY_INFORMATION 및 PROCESS_VM_READ 액세스 권한.
* @param 모듈에 대한 핸들.
* @param 모듈의 기본 이름을 수신하는 버퍼에 대한 포인터. 
* @param lpBaseName 버퍼 의 크기 ( 문자 수).
* @return 버퍼에 복사 된 문자열의 길이를 문자로 지정.
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
* 지정된 모듈을 포함하는 파일의 완전한 경로를 검색
* @author : 손나영
*
* @param hProcess 모듈을 포함하는 프로세스의 핸들.
* @param hModule 모듈에 대한 핸들.
* @param lpFilename 모듈에 대한 완전한 경로를받는 버퍼에 대한 포인터.
* @param nSize문자로 된 lpFilename 버퍼의 크기.
* @return 버퍼에 복사 된 문자열의 길이.
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
	
	// 특정 프로세스에서 각 모듈의 핸들을 가져옴 enumprocessmoduels
	if (EnumProcessModules(hProcess, hMods, cbCurrent, &cbNeeded)){
		DWORD cbAllowed = min(cbCurrent, cbNeeded);                   

		//for(i=0; i<(cbAllowed/sizeof(HMODULE)); i++){
		//다 돌지 않고 일부만 출력. cbAllowed 다 돌면 너무 많음.
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
* 지정된 모듈을 포함하는 파일의 완전한 경로를 검색
* @author : 손나영
*
* @param hProcess 모듈을 포함하는 프로세스의 핸들.
* @param hModule 모듈에 대한 핸들.
* @param lpFilename 모듈에 대한 완전한 경로를받는 버퍼에 대한 포인터.
* @param nSize문자로 된 lpFilename 버퍼의 크기.
* @return 버퍼에 복사 된 문자열의 길이.
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
	
	// 특정 프로세스에서 각 모듈의 핸들을 가져옴 enumprocessmoduels
	if (EnumProcessModules(hProcess, hMods, cbCurrent, &cbNeeded)){
		DWORD cbAllowed = min(cbCurrent, cbNeeded);                   

		//for(i=0; i<(cbAllowed/sizeof(HMODULE)); i++){
		//다 돌지 않고 일부만 출력. cbAllowed 다 돌면 너무 많음.
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
* MODULEINFO 구조체 의 지정된 모듈에 대한 정보를 검색
* @author : 손나영
*
* @param hProcess 모듈을 포함하는 프로세스의 핸들.
* @param hModule 모듈에 대한 핸들.
* @param lpmodinfo 모듈에 관한 정보를받는 MODULEINFO 구조체에 대한 포인터 .
* @param cb MODULEINFO 구조체 의 크기 ( 바이트).
* @return 검색 성공/실패 여부
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
* 응용 프로그램을로드하고 실행하거나 기존 응용 프로그램의 새 인스턴스를 생성. 16bit 전용.
* @author : 손나영
*
* @param lpModuleName 실행할 응용 프로그램의 파일 이름
* @param lpParameterBlock 새 응용 프로그램의 매개 변수 블록을 정의 하는 응용 프로그램 정의 LOADPARMS32 구조에 대한 포인터
* @return 성공 시 31보다 큼
*/

/**
	loads and executes an application
	only with 16bit version. CreateProcess 함수 사용.
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

	// 성공 시 → return value is greater than 31 
	if(result>31){
		strcpy(msg, " LoadModule() : SUCCESS \n\n Notepad loaded");
		Sleep(500);

		HWND window;
		DWORD pid;
		HANDLE wndHandle;

		window = FindWindow(L"notepad", NULL);
		if(!window){
			strcpy(msg, GetErrorMessage(" FindWindow() : FAIL \n\n LoadModule 전 FindWindow 함수를 다시 확인하십시오. \n Error Message :", GetLastError()));
			return FALSE;
		}
		GetWindowThreadProcessId(window, &pid);
		if(!pid){
			strcpy(msg, " GetWindowThreadProcessId() : FAIL \n\n LoadModule 전 pid 불러오는 과정을 다시 확인하십시오.");
			return FALSE;
		}

		wndHandle = OpenProcess(PROCESS_TERMINATE,FALSE, pid);

		BOOL result2;
		result2 = TerminateProcess(wndHandle, 0);

		if(result2 == 0)
			strcpy(msg, " LoadModule() : SUCCESS \n\n 다만, 실행시킨 메모장이 정상적으로 종료되지 않았으니, \n TerminateProcess 함수를 다시 확인하십시오.");

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
		strcpy(msg, GetErrorMessage("  LoadModule() : FAIL \n\n 16bit에서만 지원되는 함수입니다.\n LoadModule 대신 CreateProcess 함수를 사용할 수 있습니다.\n\n Error Message :", GetLastError()));
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
* 프로세스와 관련된 첫 번째 모듈에 대한 정보를 검색
* @author : 손나영
*
* @param hSnapshot CreateToolhelp32Snapshot 함수에 대한 이전 호출에서 반환 된 스냅 샷 핸들.
* @param lpme MODULEENTRY32 구조체에 대한 포인터 .
* @return 검색 성공/실패 여부
*/

/**
		  프로세스와 연관된 first 모듈에 대한 정보 얻어옴
*/
BOOL test_Module32FirstW(){   //첫 번째 인자 : CreateToolhelp32Snapshot 함수로 불러와야 함 

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
		sprintf(msg, " Module32FirstW : PASS \n\n CreateToolhelp32Snapshot()로 first 모듈 정보 얻어옴 \n first entry → copy to the buffer");
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
* 프로세스 또는 스레드와 연관된 다음 모듈에 대한 정보를 검색.
* @author : 손나영
*
* @param hSnapshot CreateToolhelp32Snapshot 함수에 대한 이전 호출에서 반환 된 스냅 샷 핸들.
* @param lpme MODULEENTRY32 구조체에 대한 포인터.
* @return 검색 성공/실패 여부
*/

BOOL test_Module32NextW(){   // 첫 번째 인자 : CreateToolhelp32Snapshot 함수로 불러와야 함

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
		sprintf(msg, "Module32NextW : PASS \n\n CreateToolhelp32Snapshot()로 next 모듈 정보 얻어옴 \n next entry → copy to the buffer");
		strcpy(buf, "SUCCESS");
	}else{
		CloseHandle(hshot);
	}
	wresult(__FILE__, __LINE__, "Module32FirstW", buf, "SUCCESS", msg);  

	return result;
}
