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
	
	#ifdef OQADBGPRINT
	printf("test_FatalExit \n");
	#endif

	/*
	HWND hWnd =0;
	MessageBox(hWnd, L"message box. \n\n [Ȯ��]Ŭ�� �� â�� ����˴ϴ�.", L"test", MB_OK);
    FatalExit(-1);
	*/

	WinExec("�ճ���\\FatalExit_exe_file_test.exe", SW_SHOW);

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

	hFile = CreateFile(L"�ճ���\\test_GetFinalPathNameByHandleA.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
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

	//C:\Users\Tmax\Documents\Visual Studio 2012\Projects\API_OS1nayoung\API_OS1nayoung\�ճ���

	//������ ���ϵ� ����(CreateHardLink��)
	DeleteFile(L"�ճ���\\CreateHardLinkTransactedA.link"); //Delete���� ���� ���¿��� �ٽ� CreateHardLinkW�� �����ϸ� FAIL��. �ݵ�� �����ؾ� ��.
	DeleteFile(L"�ճ���\\CreateHardLinkTransactedA.txt");

	//CreateHardLinkTransactedA�� ���ؼ� �̸� ���� ����
	hFile = CreateFile(L"�ճ���\\CreateHardLinkTransactedA.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	CloseHandle(hFile);

	//handle �����
	//hTranscation = CreateTransaction(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	hTranscation = CreateTransaction(NULL, 0, TRANSACTION_DO_NOT_PROMOTE, 0,0,0, NULL);

	//handle ���� ���� Ȯ��
	if(hTranscation == INVALID_HANDLE_VALUE){
		strcpy(meg, "CreateTransaction�� �����߽��ϴ�. \n CreateHardLinkTransactedA�� ������ �� �����ϴ�. ");
	}else{
		//CreateHardLinkTransactedA �� Ȯ���� ����
		//DeleteFileTransactedA("�ճ���\\CreateHardLinkTransactedA.link", hTranscation);

		//CreateHardLinkTransactedA ����
		BOOL result = CreateHardLinkTransactedA("�ճ���\\CreateHardLinkTransactedA.link", "�ճ���\\CreateHardLinkTransactedA.txt", NULL, hTranscation);

		//CreateHardLinkTransactedA�� 0�� �ƴϸ� ����
		if(result != 0){
			strcpy(meg, "CreateHardLinkTransactedA() : PASS");
			wresult_value=1;

		}else{
			strcpy(meg, "CreateHardLinkTransactedA() : FAIL");
			printf("���� �ڵ� : %d \n", GetLastError());
			printf(GetErrorMessage("CreateHardLinkTransactedA() : FAIL \nError Message : ", GetLastError()));
		}
	}

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "CreateHardLinkTransactedA", buf, "1", meg);

	//CreateHardLinkTransactedA�Ѱ� ����
	DeleteFileTransactedA("�ճ���\\CreateHardLinkTransactedA.link", hTranscation);

	//���� Ȯ���� ����(CreateHardLink��)
	DeleteFile(L"�ճ���\\CreateHardLinkTransactedA.link"); //Delete���� ���� ���¿��� �ٽ� CreateHardLinkW�� �����ϸ� FAIL��. �ݵ�� �����ؾ� ��.
	DeleteFile(L"�ճ���\\CreateHardLinkTransactedA.txt");

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

	//C:\Users\Tmax\Documents\Visual Studio 2012\Projects\API_OS1nayoung\API_OS1nayoung\�ճ���

	//������ ���ϵ� ����(CreateHardLink��)
	DeleteFile(L"�ճ���\\CreateHardLinkTransactedW.link"); //Delete���� ���� ���¿��� �ٽ� CreateHardLinkW�� �����ϸ� FAIL��. �ݵ�� �����ؾ� ��.
	DeleteFile(L"�ճ���\\CreateHardLinkTransactedW.txt");

	//CreateHardLinkTransactedA�� ���ؼ� �̸� ���� ����
	hFile = CreateFile(L"�ճ���\\CreateHardLinkTransactedW.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	CloseHandle(hFile);

	//handle �����
	//hTranscation = CreateTransaction(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	hTranscation = CreateTransaction(NULL, 0, TRANSACTION_DO_NOT_PROMOTE, 0,0,0, NULL);

	//handle ���� ���� Ȯ��
	if(hTranscation == INVALID_HANDLE_VALUE){
		strcpy(meg, "CreateTransaction�� �����߽��ϴ�. \nCreateHardLinkTransactedW�� ������ �� �����ϴ�. ");
	}else{
		//CreateHardLinkTransactedA �� Ȯ���� ����
		//DeleteFileTransactedA("�ճ���\\CreateHardLinkTransactedA.link", hTranscation);

		//CreateHardLinkTransactedA ����
		BOOL result = CreateHardLinkTransactedW(L"�ճ���\\CreateHardLinkTransactedW.link", L"�ճ���\\CreateHardLinkTransactedW.txt", NULL, hTranscation);

		//CreateHardLinkTransactedA�� 0�� �ƴϸ� ����
		if(result != 0){
			strcpy(meg, "CreateHardLinkTransactedW() : PASS");
			wresult_value=1;

		}else{
			strcpy(meg, "CreateHardLinkTransactedW() : FAIL");
			printf("���� �ڵ� : %d \n", GetLastError());
			printf(GetErrorMessage("CreateHardLinkTransactedW() : FAIL \nError Message : ", GetLastError()));
		}
	}

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "CreateHardLinkTransactedW", buf, "1", meg);

	//CreateHardLinkTransactedA�Ѱ� ����
	DeleteFileTransactedW(L"�ճ���\\CreateHardLinkTransactedW.link", hTranscation);

	//���� Ȯ���� ����(CreateHardLink��)
	DeleteFile(L"�ճ���\\CreateHardLinkTransactedW.link"); //Delete���� ���� ���¿��� �ٽ� CreateHardLinkW�� �����ϸ� FAIL��. �ݵ�� �����ؾ� ��.
	DeleteFile(L"�ճ���\\CreateHardLinkTransactedW.txt");

	CloseHandle(hFile);

	return TRUE;
}


/**
	Ư�� process�� ��ϵ� ����� ���� �˻�
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
			sprintf(meg, " GetApplicationRestartSettings() : SUCCESS \n\n ��RegisterApplicationRestart �� success \n GetApplicationRestartSettings �� success");
			strcpy(buf, "SUCCESS");
		}else
			sprintf(meg, " GetApplicationRestartSettings() : FAIL \n\n ��RegisterApplicationRestart �� success \n GetApplicationRestartSettings �� fail");
	}else
		sprintf(meg, "GetApplicationRestartSettings() : FAIL \n\n ��RegisterApplicationRestart �� fail \n GetApplicationRestartSettings �� fail");


	// ����� : Returns S_OK instead of ERROR_INSUFFICIENT_BUFFER when pBuffer is NULL and size is 0.
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