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

	// spincount�� 4000���� set
	// short duration�� critical section�� ���� spin count �۰� ���������μ� ���� ��� ����
	// �Լ� ���� �� critical section�� ���� ȸ�� ���� ��ȯ. result�� ����.
	result = SetCriticalSectionSpinCount(&lpCriticalSection, 4000);

	if(result){
		sprintf(meg, "SetCriticalSectionSpinCount() : SUCCESS \n\ncritical section�� ���� spin �� : %d", result);
		strcpy(buf, "SUCCESS");
	}else {
		sprintf(meg, GetErrorMessage("SetCriticalSectionSpinCount() : FAIL \n\n Error Message :", GetLastError()));
		strcpy(buf, "FAIL");
	}

	wresult(__FILE__, __LINE__, "SetCriticalSectionSpinCount", buf, "SUCCESS", meg);
	return true;
}


/**
������ ���ϰ� ������ ���� �ý��� �� ������ ���� ������ �˻�.
�˻��� �Ϸ�Ǹ� ��ȯ���� != 0
*/

#define BUFSIZE MAX_PATH

/**
	Ư�� ������ ���� �ý��� �� ������ ���� ���� �˻�

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
	HANDLE hFile = CreateFile(L"�ճ���\\test_GetVolumeInformationByHandleW.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//�Ķ����(���� �ڵ�, ���� �̸� ���� ����, ���� �̸� ���� ����, �ø��� �ѹ�, ���� ������� �̸� ����, ..)
	result = GetVolumeInformationByHandleW(hFile,Volume,MAX_PATH,NULL,NULL,NULL,NULL,0);

	//��û�� ��� ������ �˻��Ǹ� ��ȯ ���� != 0
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
	message box�� ����, �� box�� ���� �� ���� ���α׷��� �Բ� ����.
	return value�� ����.
*/
BOOL test_FatalAppExitW(){ // ���� �ڵ鸵

	#ifdef OQADBGPRINT
	printf("test_FatalAppExitW \n");
	#endif

	//WinExec("C:\\Users\\Tmax\\Desktop\\test\\FatalAppExit_exe_file_test.exe", SW_SHOW);
	WinExec("�ճ���\\FatalAppExit_exe_file_test.exe", SW_SHOW);

	//BOOL result;
	//char msg[BUFSIZ];
	//HWND hWnd = 0;

	/**
	result = SearchProcess();

	if(result == TRUE){
	wresult(__FILE__,__LINE__ ,"AssignProcessToJobObject", "1", "1",msg);
	//MessageBox(hWnd, L"FatalAppExitA ����", L"����", MB_OK);
	}
	*/
	return true;
}

BOOL test_FatalExit(){

	HWND hWnd =0;
	MessageBox(hWnd, L"message box. \n\n [Ȯ��]Ŭ�� �� â�� ����˴ϴ�.", L"test", MB_OK);
    FatalExit(-1);

	return true;
}