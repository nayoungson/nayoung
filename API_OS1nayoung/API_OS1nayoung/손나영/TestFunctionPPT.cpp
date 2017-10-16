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
	result = GetVolumeInformationByHandleW(hFile,Volume,MAX_PATH,NULL,NULL,NULL,NULL,0);


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


BOOL test_FatalAppExitW(){ // 에러 핸들링. Displays a message box and terminates the application when the message box is closed.
	//WinExec("C:\\Users\\Tmax\\Desktop\\test\\FatalAppExit_exe_file_test.exe", SW_SHOW);
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