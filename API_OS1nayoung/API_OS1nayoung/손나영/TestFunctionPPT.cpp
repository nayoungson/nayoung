#include "TestFunctionPPT.h"
#include <ktmw32.h>

BOOL test_SetFileInformationByHandle(){

	/** setting function the file information */
	/** function(hFile, FileDispositionInfo, FILE_DISPOSITION_INFO     ,information, dwbuffersize) */

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_SetFileInformationByHandle\n");
	#endif

	HANDLE hFile = CreateFile(L"tempfile", GENERIC_READ | GENERIC_WRITE | DELETE, 0 , NULL, CREATE_ALWAYS, 0, NULL);
	// HANDLE hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test_GetVolumeInformationByHandleW.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (hFile != INVALID_HANDLE_VALUE){
		FILE_DISPOSITION_INFO fdi;
		fdi.DeleteFile = TRUE; // marking for deletion

		BOOL fResult = SetFileInformationByHandle( hFile, FileDispositionInfo, &fdi, sizeof(FILE_DISPOSITION_INFO) );

		if (fResult){
			// File will be deleted upon CloseHandle.
			sprintf(meg, "SetFileInformationByHandle() : SUCCESS");
			strcpy(buf, "SUCCESS");

		}else{
			strcpy(buf, GetErrorMessage("SetFileInformationByHandle() : FAIL \n\n Error Message :", GetLastError()));
		}
		CloseHandle(hFile); 

		// At this point, the file is closed and deleted by the system.
	}else {
		strcpy(buf, GetErrorMessage("SetFileInformationByHandle() : FAIL could not create tempfile !\nError Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "SetFileInformationByHandle", buf, "SUCCESS", meg);
	
	return true;
}


BOOL test_SetCriticalSectionSpinCount(){

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	DWORD result = 0;
	CRITICAL_SECTION lpCriticalSection;

#ifdef OQADBGPRINT
	printf("test_SetCriticalSectionSpinCount\n");
#endif

	// spincount를 4000으로 set
	// short duration의 critical section을 위해 spin count 작게 설정함으로서 성능 향상 가능
	// 함수 실행 시 critical section의 이전 회전 수를 반환. result에 저장.
	result = SetCriticalSectionSpinCount(&lpCriticalSection, 4000);

	if(result){
		sprintf(meg, "SetCriticalSectionSpinCount() : SUCCESS \n\ncritical section의 이전 spin 수 : %d", result);
		strcpy(buf, "SUCCESS");
	}else {
		sprintf(meg, GetErrorMessage("SetCriticalSectionSpinCount() : FAIL \n\n Error Message :", GetLastError()));
		strcpy(buf, "FAIL");
	}

	wresult(__FILE__, __LINE__, "SetCriticalSectionSpinCount", buf, "SUCCESS", meg);
	return true;
}


/**
지정된 파일과 연관된 파일 시스템 및 볼륨에 대한 정보를 검색.
검색이 완료되면 반환값은 != 0
*/

#define BUFSIZE MAX_PATH

/**
	특정 파일의 파일 시스템 및 볼륨에 대한 정보 검색

	*/
BOOL test_GetVolumeInformationByHandleW(){

	#ifdef OQADBGPRINT
	printf("test_GetVolumeInformationByHandleW \n");
	#endif

	BOOL result;
	TCHAR Volume[MAX_PATH];

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZE] = "FAIL";

	//HANDLE hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test_GetVolumeInformationByHandleW.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hFile = CreateFile(L"손나영\\test_GetVolumeInformationByHandleW.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//파라미터(파일 핸들, 볼륨 이름 수신 버퍼, 볼륨 이름 버퍼 길이, 시리얼 넘버, 파일 구성요소 이름 길이, ..)
	result = GetVolumeInformationByHandleW(hFile,Volume,MAX_PATH,NULL,NULL,NULL,NULL,0);

	//요청된 모든 정보가 검색되면 반환 값은 != 0
	if(result != 0){
		sprintf(meg, "GetVolumeInformationByHandleW() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}
	else{
		strcpy(meg, GetErrorMessage(" GetVolumeInformationByHandleW() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetVolumeInformationByHandleW", buf, "SUCCESS", meg);
	return true;
}

/**
	message box를 띄우고, 이 box가 닫힐 때 응용 프로그램도 함께 종료.
	return value가 없음.
*/
BOOL test_FatalAppExitW(){ // 에러 핸들링

	#ifdef OQADBGPRINT
	printf("test_FatalAppExitW \n");
	#endif

	//WinExec("C:\\Users\\Tmax\\Desktop\\test\\FatalAppExit_exe_file_test.exe", SW_SHOW);
	WinExec("손나영\\FatalAppExit_exe_file_test.exe", SW_SHOW);

	//BOOL result;
	//char msg[BUFSIZ];
	//HWND hWnd = 0;

	/**
	result = SearchProcess();

	if(result == TRUE){
	wresult(__FILE__,__LINE__ ,"AssignProcessToJobObject", "1", "1",msg);
	//MessageBox(hWnd, L"FatalAppExitA 성공", L"성공", MB_OK);
	}
	*/
	return true;
}

BOOL test_FatalExit(){
	
	#ifdef OQADBGPRINT
	printf("test_FatalExit \n");
	#endif

	/*
	HWND hWnd =0;
	MessageBox(hWnd, L"message box. \n\n [확인]클릭 시 창이 종료됩니다.", L"test", MB_OK);
    FatalExit(-1);
	*/

	WinExec("손나영\\FatalExit_exe_file_test.exe", SW_SHOW);

	return true;
}

#define BUFSIZE MAX_PATH
BOOL test_GetFinalPathNameByHandleA(){

	#ifdef OQADBGPRINT
	printf("test_GetFinalPathNameByHandleA\n");
	#endif

	HANDLE hFile;
	DWORD dwRet;
	TCHAR Path[BUFSIZE];

	char buf[BUFSIZ];
	char meg[BUFSIZ];

	hFile = CreateFile(L"손나영\\test_GetFinalPathNameByHandleA.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile ==INVALID_HANDLE_VALUE){
		sprintf(meg, "Could not open file (error %d\n)", GetLastError());
		return 0;
	}

	dwRet = GetFinalPathNameByHandle(hFile,Path,BUFSIZE,VOLUME_NAME_NT);
	if(dwRet < BUFSIZE)	{
		sprintf(meg, " GetFinalPathNameByHandle() : SUCCESS \n\nThe final path :%S \n", Path);
		strcpy(buf, "SUCCESS");
	}
	else{
		sprintf(meg, " GetFinalPathNameByHandle() : FAIL \n\n The required buffer size is %d.\n", dwRet);
	}
	CloseHandle(hFile);

	wresult(__FILE__, __LINE__, "GetFinalPathNameByHandle", buf, "SUCCESS", meg);

	return true;
}


BOOL test_CreateHardLinkTransactedA(){

	#ifdef OQADBGPRINT
	printf("test_GetFinalPathNameByHandleA\n");
	#endif

	HWND hWnd = 0;
	HANDLE hFile = NULL;
	HANDLE hTranscation;

	int wresult_value=0;
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_CreateHardLinkTransactedA\n");
	#endif

	//C:\Users\Tmax\Documents\Visual Studio 2012\Projects\API_OS1nayoung\API_OS1nayoung\손나영

	//생성한 파일들 삭제(CreateHardLink때)
	DeleteFile(L"손나영\\CreateHardLinkTransactedA.link"); //Delete하지 않은 상태에서 다시 CreateHardLinkW를 진행하면 FAIL됨. 반드시 삭제해야 함.
	DeleteFile(L"손나영\\CreateHardLinkTransactedA.txt");

	//CreateHardLinkTransactedA을 위해서 미리 파일 생성
	hFile = CreateFile(L"손나영\\CreateHardLinkTransactedA.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	CloseHandle(hFile);

	//handle 만들기
	//hTranscation = CreateTransaction(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	hTranscation = CreateTransaction(NULL, 0, TRANSACTION_DO_NOT_PROMOTE, 0,0,0, NULL);

	//handle 오류 여부 확인
	if(hTranscation == INVALID_HANDLE_VALUE){
		strcpy(meg, "CreateTransaction에 실패했습니다. \n CreateHardLinkTransactedA를 진행할 수 없습니다. ");
	}else{
		//CreateHardLinkTransactedA 전 확실히 삭제
		//DeleteFileTransactedA("손나영\\CreateHardLinkTransactedA.link", hTranscation);

		//CreateHardLinkTransactedA 수행
		BOOL result = CreateHardLinkTransactedA("손나영\\CreateHardLinkTransactedA.link", "손나영\\CreateHardLinkTransactedA.txt", NULL, hTranscation);

		//CreateHardLinkTransactedA가 0이 아니면 성공
		if(result != 0){
			strcpy(meg, "CreateHardLinkTransactedA() : PASS");
			wresult_value=1;

		}else{
			strcpy(meg, "CreateHardLinkTransactedA() : FAIL");
			printf("에러 코드 : %d \n", GetLastError());
			printf(GetErrorMessage("CreateHardLinkTransactedA() : FAIL \nError Message : ", GetLastError()));
		}
	}

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "CreateHardLinkTransactedA", buf, "1", meg);

	//CreateHardLinkTransactedA한거 삭제
	DeleteFileTransactedA("손나영\\CreateHardLinkTransactedA.link", hTranscation);

	//파일 확실히 삭제(CreateHardLink때)
	DeleteFile(L"손나영\\CreateHardLinkTransactedA.link"); //Delete하지 않은 상태에서 다시 CreateHardLinkW를 진행하면 FAIL됨. 반드시 삭제해야 함.
	DeleteFile(L"손나영\\CreateHardLinkTransactedA.txt");

	CloseHandle(hFile);

	return TRUE;
}


BOOL test_CreateHardLinkTransactedW(){

	#ifdef OQADBGPRINT
	printf("test_CreateHardLinkTransactedW\n");
	#endif


	HWND hWnd = 0;
	HANDLE hFile = NULL;
	HANDLE hTranscation;

	int wresult_value=0;
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_CreateHardLinkTransactedW\n");
	#endif

	//C:\Users\Tmax\Documents\Visual Studio 2012\Projects\API_OS1nayoung\API_OS1nayoung\손나영

	//생성한 파일들 삭제(CreateHardLink때)
	DeleteFile(L"손나영\\CreateHardLinkTransactedW.link"); //Delete하지 않은 상태에서 다시 CreateHardLinkW를 진행하면 FAIL됨. 반드시 삭제해야 함.
	DeleteFile(L"손나영\\CreateHardLinkTransactedW.txt");

	//CreateHardLinkTransactedA을 위해서 미리 파일 생성
	hFile = CreateFile(L"손나영\\CreateHardLinkTransactedW.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	CloseHandle(hFile);

	//handle 만들기
	//hTranscation = CreateTransaction(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	hTranscation = CreateTransaction(NULL, 0, TRANSACTION_DO_NOT_PROMOTE, 0,0,0, NULL);

	//handle 오류 여부 확인
	if(hTranscation == INVALID_HANDLE_VALUE){
		strcpy(meg, "CreateTransaction에 실패했습니다. \nCreateHardLinkTransactedW를 진행할 수 없습니다. ");
	}else{
		//CreateHardLinkTransactedA 전 확실히 삭제
		//DeleteFileTransactedA("손나영\\CreateHardLinkTransactedA.link", hTranscation);

		//CreateHardLinkTransactedA 수행
		BOOL result = CreateHardLinkTransactedW(L"손나영\\CreateHardLinkTransactedW.link", L"손나영\\CreateHardLinkTransactedW.txt", NULL, hTranscation);

		//CreateHardLinkTransactedA가 0이 아니면 성공
		if(result != 0){
			strcpy(meg, "CreateHardLinkTransactedW() : PASS");
			wresult_value=1;

		}else{
			strcpy(meg, "CreateHardLinkTransactedW() : FAIL");
			printf("에러 코드 : %d \n", GetLastError());
			printf(GetErrorMessage("CreateHardLinkTransactedW() : FAIL \nError Message : ", GetLastError()));
		}
	}

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "CreateHardLinkTransactedW", buf, "1", meg);

	//CreateHardLinkTransactedA한거 삭제
	DeleteFileTransactedW(L"손나영\\CreateHardLinkTransactedW.link", hTranscation);

	//파일 확실히 삭제(CreateHardLink때)
	DeleteFile(L"손나영\\CreateHardLinkTransactedW.link"); //Delete하지 않은 상태에서 다시 CreateHardLinkW를 진행하면 FAIL됨. 반드시 삭제해야 함.
	DeleteFile(L"손나영\\CreateHardLinkTransactedW.txt");

	CloseHandle(hFile);

	return TRUE;
}


/**
	특정 process에 등록된 재시작 정보 검색
*/
BOOL test_GetApplicationRestartSettings(){

	#ifdef OQADBGPRINT
	printf("test_GetApplicationRestartSettings\n");
	#endif

	HRESULT hr = S_OK;
	WCHAR wsCommandLine[RESTART_MAX_CMD_LINE + 1];
	DWORD cchCmdLine = sizeof(wsCommandLine) / sizeof(WCHAR);
	DWORD dwFlags = 0;
	LPWSTR pwsCmdLine = NULL;

	char buf[BUFSIZ];
	char meg[BUFSIZ];

	hr = RegisterApplicationRestart(L"/restart -f .\\filename.ext", 0);

	if (SUCCEEDED(hr))    {
		hr = GetApplicationRestartSettings(GetCurrentProcess(), wsCommandLine, &cchCmdLine, &dwFlags);

		if(SUCCEEDED(hr)){
			sprintf(meg, " GetApplicationRestartSettings() : SUCCESS \n\n ▶RegisterApplicationRestart → success \n GetApplicationRestartSettings → success");
			strcpy(buf, "SUCCESS");
		}else
			sprintf(meg, " GetApplicationRestartSettings() : FAIL \n\n ▶RegisterApplicationRestart → success \n GetApplicationRestartSettings → fail");
	}else
		sprintf(meg, "GetApplicationRestartSettings() : FAIL \n\n ▶RegisterApplicationRestart → fail \n GetApplicationRestartSettings → fail");


	// 참고용 : Returns S_OK instead of ERROR_INSUFFICIENT_BUFFER when pBuffer is NULL and size is 0.
	/**
	hr = GetApplicationRestartSettings(GetCurrentProcess(), (PWSTR)pwsCmdLine, &cchCmdLine, &dwFlags);

	if(SUCCEEDED(hr)){
		pwsCmdLine = (LPWSTR)malloc(cchCmdLine * sizeof(WCHAR));

		if(pwsCmdLine){
			hr = GetApplicationRestartSettings(GetCurrentProcess(), (PWSTR)pwsCmdLine, &cchCmdLine, &dwFlags);
			if(FAILED(hr)){
				wprintf(L"GetApplicationRestartSettings failed with 0x%x\n", hr);
			}
			wprintf(L"Command line: %s\n", pwsCmdLine);
		}else {
			wprintf(L"Allocating the command-line buffer failed.\n");
		}
	}else{
		if (hr != HRESULT_FROM_WIN32(ERROR_NOT_FOUND)){ // Not a restart.
			wprintf(L"GetApplicationRestartSettings failed with 0x%x\n", hr);

		}
	}
	*/

	wresult(__FILE__, __LINE__, "GetApplicationRestartSettings", buf, "SUCCESS", meg);

	return true;
}