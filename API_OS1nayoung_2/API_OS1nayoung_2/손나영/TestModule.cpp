#include "TestModule.h"
#include <TlHelp32.h>
#include <Psapi.h>


/**
	loads and executes an application
	only with 16bit version. CreateProcess 함수 사용.
	*/
BOOL test_LoadModule(){

	LPVOID lp;

	int wresult_value=0;
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

#ifdef OQADBGPRINT
	printf("test_LoadModule\n");
#endif

		
	// succeeds → return value is greater than 31
	if(LoadModule("Notepad.exe", &lp)>31){
		strcpy(meg, " LoadModule() : PASS \n\n Notepad loaded");
		wresult_value=1;
	}else

		strcpy(meg, GetErrorMessage("  LoadModule() : FAIL \n\n 16bit에서만 지원되는 함수입니다.\n LoadModule 대신 CreateProcess 함수를 사용할 수 있습니다.\n\n Error Message :", GetLastError()));
	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "LoadModule", buf, "1", meg);

	return true;
}

/**
		  프로세스와 연관된 first 모듈에 대한 정보 얻어옴
*/

BOOL test_Module32FirstW(){   //첫 번째 인자 : CreateToolhelp32Snapshot 함수로 불러와야 함 
	HANDLE hshot = NULL;
	BOOL result;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_Module32FirstW\n");
	#endif
	MODULEENTRY32 me32 = {0};
	me32.dwSize = sizeof( MODULEENTRY32 );

	hshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
	result = Module32FirstW(hshot, &me32);

	if(result){
		sprintf(meg, " Module32FirstW : PASS \n\n CreateToolhelp32Snapshot()로 first 모듈 정보 얻어옴 \n first entry → copy to the buffer");
		strcpy(buf, "SUCCESS");
	}else{
		CloseHandle(hshot);
		
	}
	wresult(__FILE__, __LINE__, "Module32FirstW", buf, "SUCCESS", meg);  
	return true;
}

BOOL test_Module32NextW(){   // 첫 번째 인자 : CreateToolhelp32Snapshot 함수로 불러와야 함
	HANDLE hshot = NULL;
	BOOL result;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_Module32NextW\n");
	#endif
	MODULEENTRY32 me32 = {0};
	me32.dwSize = sizeof( MODULEENTRY32 );

	hshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
	result = Module32NextW(hshot, &me32);

	if(result){
		sprintf(meg, "Module32NextW : PASS \n\n CreateToolhelp32Snapshot()로 next 모듈 정보 얻어옴 \n next entry → copy to the buffer");
		strcpy(buf, "SUCCESS");
	}else{
		CloseHandle(hshot);
	}
	wresult(__FILE__, __LINE__, "Module32FirstW", buf, "SUCCESS", meg);  
	return true;
}

BOOL test_K32GetModuleBaseNameA(){

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";


	HANDLE hProcess;
	HMODULE hMod = NULL;

	int pid = GetCurrentProcessId();
	TCHAR szProcessName[MAX_PATH] = L"<unknown>";

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE, pid);
	DWORD result = K32GetModuleBaseNameA(hProcess, hMod, (LPSTR)szProcessName, sizeof(szProcessName)/sizeof(TCHAR) );

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
	HMODULE hMod = NULL;

	int pid = GetCurrentProcessId();
	TCHAR szProcessName[MAX_PATH] = L"<unknown>";

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE, pid);
	DWORD result = K32GetModuleBaseNameW(hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(TCHAR) );

	if(result == 0){
		strcpy(meg, GetErrorMessage(" GetModuleBaseNameW() : FAIL \n\n Error Message :", GetLastError()));
	}else{

		sprintf(meg, " GetModuleBaseNameW() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}
	wresult(__FILE__, __LINE__, "GetModuleBaseNameW", buf, "SUCCESS", meg);
	return true;
}

BOOL test_K32GetModuleFileNameExA(){

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

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
	
	// 특정 프로세스에서 각 모듈의 핸들을 검색 enumprocessmoduels
	if (EnumProcessModules(hProcess, hMods, cbCurrent, &cbNeeded)){
		DWORD cbAllowed = min(cbCurrent, cbNeeded);                   

		//for(i=0; i<(cbAllowed/sizeof(HMODULE)); i++){
		//다 돌지 않고 일부만 출력. cbAllowed 다 돌면 너무 많음.
		for(i=0; i<1; i++){
			TCHAR szModName[MAX_PATH];

			// Get the full path to the module's file.

			DWORD result = K32GetModuleFileNameExA(hProcess, hMods[i], (LPSTR)szModName, sizeof(szModName)/sizeof(TCHAR));

			// if the function succeeds, the length of the string copied to he buffer is returned.
			if(result != 0){
				// Print the module name and handle value.
				sprintf(meg, "K32GetModuleFileNameExA() : SUCCESS \n\n%S(0x%08X)", (LPSTR)szModName, hMods[i]);
				strcpy(buf, "SUCCESS");
			}else{
				strcpy(meg, GetErrorMessage(" K32GetModuleFileNameExA() : FAIL \n\n Error Message :", GetLastError()));
			}
			
		}
		wresult(__FILE__, __LINE__, "K32GetModuleFileNameExA", buf, "SUCCESS", meg);
	}
	CloseHandle(hProcess);

	return true;
}

BOOL test_K32GetModuleFileNameExW(){

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

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
	
	// 특정 프로세스에서 각 모듈의 핸들을 검색 enumprocessmoduels
	if (EnumProcessModules(hProcess, hMods, cbCurrent, &cbNeeded)){
		DWORD cbAllowed = min(cbCurrent, cbNeeded);                   

		//for(i=0; i<(cbAllowed/sizeof(HMODULE)); i++){
		//다 돌지 않고 일부만 출력. cbAllowed 다 돌면 너무 많음.
		for(i=0; i<1; i++){
			TCHAR szModName[MAX_PATH];

			// Get the full path to the module's file.

			DWORD result = K32GetModuleFileNameExW(hProcess, hMods[i], szModName, sizeof(szModName)/sizeof(TCHAR));

			// if the function succeeds, the length of the string copied to he buffer is returned.
			if(result != 0){
				// Print the module name and handle value.
				sprintf(meg, "k32GetModuleFileNameExW() : SUCCESS \n\n%S(0x%08X)", szModName, hMods[i]);
				strcpy(buf, "SUCCESS");
			}else{
				strcpy(meg, GetErrorMessage(" k32GetModuleFileNameExW() : FAIL \n\n Error Message :", GetLastError()));
			}
			
		}
		wresult(__FILE__, __LINE__, "k32GetModuleFileNameExW", buf, "SUCCESS", meg);
	}
	CloseHandle(hProcess);

	return true;
}

BOOL test_K32GetModuleInformation(){

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";
	int pid = GetCurrentProcessId();

	BOOL result;
	HANDLE hProcess;
	HMODULE hModule = NULL; // A handle to the module.
	MODULEINFO lpmodinfo;	// A pointer to the MODULEINFO structure that receives information about the module.

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (NULL == hProcess)
        return 1;

	result = K32GetModuleInformation(hProcess, hModule, &lpmodinfo, sizeof(lpmodinfo));

	if(result != 0){
		sprintf(meg, " K32GetModuleInformation() : SUCCESS ");
		strcpy(buf, "SUCCESS");

	}else 
		strcpy(meg, GetErrorMessage(" K32GetModuleInformation() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "K32GetModuleInformation", buf, "SUCCESS", meg);

	return true;
}
