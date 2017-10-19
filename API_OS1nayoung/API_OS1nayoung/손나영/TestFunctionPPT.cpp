#include "TestFunctionPPT.h"


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
	printf("test_FatalAppExitW \n");
	#endif

	/*
	HWND hWnd =0;
	MessageBox(hWnd, L"message box. \n\n [확인]클릭 시 창이 종료됩니다.", L"test", MB_OK);
    FatalExit(-1);
	*/

	WinExec("손나영\\FatalExit_exe_file_test.exe", SW_SHOW);

	return true;
}

/**
BOOL test_CreateHardLinkTransactedA(){

	HWND hWnd = 0;
	HANDLE hFile = NULL;
	HANDLE hTransaction;

	int wresult_value=0;
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_CreateHardLinkW\n");
	#endif

	DeleteFile(L"손나영\\CreateHardLinkTransactedA.link"); //Delete하지 않은 상태에서 다시 CreateHardLinkW를 진행하면 FAIL됨. 반드시 삭제해야 함.
	DeleteFile(L"손나영\\CreateHardLinkTransactedA.txt");

	hFile = CreateFile(L"손나영\\CreateHardLinkTransactedA.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	hTransaction = CreateTransaction(NULL, NULL, 0, 0, 0, 0, NULL);

	BOOL result = CreateHardLinkTransactedA("손나영\\CreateHardLinkTransactedA.link", "손나영\\CreateHardLinkTransactedA.txt", NULL, hTransaction);

	if(result){
		strcpy(meg, " CreateHardLinkTransactedA() : PASS \n\n CreateHardLinkTransactedA 성공 \n(계속해서 CreateHardLinkW 실행을 위해 생성한 파일을 삭제합니다.)");
		wresult_value=1;

	}else{
		strcpy(meg, " CreateHardLinkTransactedA() : FAIL \n\n 생성 실패 \n(관리자 권한으로 실행했는지, 경로가 올바른지 확인하십시오.)");
	}

	CloseHandle(hFile);

	DeleteFile(L"손나영\\test_CreateHardLinkTransactedA.link"); //Delete하지 않은 상태에서 다시 CreateHardLinkW를 진행하면 FAIL됨. 반드시 삭제해야 함.
	DeleteFile(L"손나영\\test_CreateHardLinkTransactedA.txt");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "test_CreateHardLinkTransactedA", buf, "1", meg);

	return TRUE;
}
*/