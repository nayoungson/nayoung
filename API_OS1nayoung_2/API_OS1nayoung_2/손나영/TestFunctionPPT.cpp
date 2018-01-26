#include "TestFunctionPPT.h"
#include <ktmw32.h>
#include <stdio.h>
#include <strsafe.h>
#include <WinError.h>

/**
* BOOL WINAPI CreateHardLinkTransacted(
  _In_       LPCTSTR               lpFileName,				�� ���ϸ�
  _In_       LPCTSTR               lpExistingFileName,		���� ���ϸ�		
  _Reserved_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,	������ NULL
  _In_       HANDLE                hTransaction				Ʈ����� �ڵ�
  );
* ���� ���ϰ� �� ���� ���� �ϵ� ��ũ�� ó���� �۾����� ����. NTFS ���� �ý��ۿ����� ����. ���丮 X. ���ϸ� O.
* @author : �ճ���

* @param lpFileName �� ���ϸ�
* @param lpExistingFileName ���� ���ϸ�
* @param lpSecurityAttributes ������ NULL
* @param hTransaction Ʈ����� �ڵ�
* @return �ϵ帵ũ ���� ����/���� ����.
*/

BOOL test_CreateHardLinkTransactedA(){

	#ifdef OQADBGPRINT
	printf("test_CreateHardLinkTransactedA\n");
	#endif

	HWND hWnd = 0;
	HANDLE hFile = NULL;
	HANDLE hTranscation;
	BOOL result = FALSE;

	int wresult_value=0;
	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

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
		strcpy(msg, "CreateTransaction�� �����߽��ϴ�. \n CreateHardLinkTransactedA�� ������ �� �����ϴ�. ");
	}else{
		//CreateHardLinkTransactedA �� Ȯ���� ����
		//DeleteFileTransactedA("�ճ���\\CreateHardLinkTransactedA.link", hTranscation);

		//CreateHardLinkTransactedA ����
		result = CreateHardLinkTransactedA("�ճ���\\CreateHardLinkTransactedA.link", "�ճ���\\CreateHardLinkTransactedA.txt", NULL, hTranscation);

		//CreateHardLinkTransactedA�� 0�� �ƴϸ� ����
		if(result != FALSE){
			result = TRUE;
			wresult_value=1;
			strcpy(msg, "CreateHardLinkTransactedA() : SUCCESS");

		}else{
			strcpy(msg, "CreateHardLinkTransactedA() : FAIL");
			printf("���� �ڵ� : %d \n", GetLastError());
			printf(GetErrorMessage("CreateHardLinkTransactedA() : FAIL \nError Message : ", GetLastError()));
		}
	}

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "CreateHardLinkTransactedA", buf, "1", msg);
	
	CloseHandle(hFile);

	//���� Ȯ���� ����(CreateHardLink��)
	DeleteFile(L"�ճ���\\CreateHardLinkTransactedA.link"); //Delete���� ���� ���¿��� �ٽ� CreateHardLinkW�� �����ϸ� FAIL��. �ݵ�� �����ؾ� ��.
	DeleteFile(L"�ճ���\\CreateHardLinkTransactedA.txt");

	return result;
}

/**
* BOOL WINAPI CreateHardLinkTransacted(
  _In_       LPCTSTR               lpFileName,				�� ���ϸ�
  _In_       LPCTSTR               lpExistingFileName,		���� ���ϸ�		
  _Reserved_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,	������ NULL
  _In_       HANDLE                hTransaction				Ʈ����� �ڵ�
  );
* ���� ���ϰ� �� ���� ���� �ϵ� ��ũ�� ó���� �۾����� ����. NTFS ���� �ý��ۿ����� ����. ���丮 X. ���ϸ� O.
* @author : �ճ���

* @param lpFileName �� ���ϸ�
* @param lpExistingFileName ���� ���ϸ�
* @param lpSecurityAttributes ������ NULL
* @param hTransaction Ʈ����� �ڵ�
* @return �ϵ帵ũ ���� ����/���� ����.
*/

BOOL test_CreateHardLinkTransactedW(){

	#ifdef OQADBGPRINT
	printf("test_CreateHardLinkTransactedW\n");
	#endif

	HWND hWnd = 0;
	HANDLE hFile = NULL;
	HANDLE hTranscation;
	BOOL result = FALSE;

	int wresult_value=0;
	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

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
		strcpy(msg, "CreateTransaction�� �����߽��ϴ�. \nCreateHardLinkTransactedW�� ������ �� �����ϴ�. ");

	}else{
		//CreateHardLinkTransactedA �� Ȯ���� ����
		//DeleteFileTransactedA("�ճ���\\CreateHardLinkTransactedA.link", hTranscation);

		//CreateHardLinkTransactedA ����
		result = CreateHardLinkTransactedW(L"�ճ���\\CreateHardLinkTransactedW.link", L"�ճ���\\CreateHardLinkTransactedW.txt", NULL, hTranscation);

		//CreateHardLinkTransactedA�� 0�� �ƴϸ� ����
		if(result != FALSE){
			result = TRUE;
			wresult_value=1;
			strcpy(msg, "CreateHardLinkTransactedW() : SUCCESS");

		}else{
			strcpy(msg, "CreateHardLinkTransactedW() : FAIL");
			printf("���� �ڵ� : %d \n", GetLastError());
			printf(GetErrorMessage("CreateHardLinkTransactedW() : FAIL \nError Message : ", GetLastError()));
		}
	}

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "CreateHardLinkTransactedW", buf, "1", msg);
	
	CloseHandle(hFile);

	//���� Ȯ���� ����(CreateHardLink��)
	DeleteFile(L"�ճ���\\CreateHardLinkTransactedW.link"); //Delete���� ���� ���¿��� �ٽ� CreateHardLinkW�� �����ϸ� FAIL��. �ݵ�� �����ؾ� ��.
	DeleteFile(L"�ճ���\\CreateHardLinkTransactedW.txt");

	return result;
}


/**
* BOOLEAN WINAPI CreateSymbolicLinkTransacted(
  _In_ LPTSTR lpSymlinkFileName,
  _In_ LPTSTR lpTargetFileName,
  _In_ DWORD  dwFlags,
  _In_ HANDLE hTransaction
  );
* Ʈ����� ���۷��̼����� �ɺ��� ��ũ ����
* @author : �ճ���
*
* @param lpSymlinkFileName ������ �ɺ��� ��ũ��
* @param lpTargetFileName �ɺ��� ��ũ�� ���� Ÿ�ٸ�. lpTargetFileName�� ����� ��ġ���� ������ ��ũ�� ���� ��ũ�� ó����. �׷��� ������ ��ũ�� ��� ��ũ�� ��޵�.
* @param dwFlags ��ũ ����� lpTargetFileName�� ���丮���� ����. 0�̸� ����, SYMBOLIC_LINK_FLAG_DIRECTORY�̸� ���丮.
* @param hTransaction Ʈ����� �ڵ�. CreateTransaction �Լ��� ���� ��ȯ��.
* @return �ɺ��� ��ũ ���� ����/���� ����
*/

BOOL test_CreateSymbolicLinkTransactedA(){

	#ifdef OQADBGPRINT
	printf("test_CreateSymbolicLinkTransactedA\n");
	#endif

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	HWND hWnd = 0;
	HANDLE hTranscation;
	BOOL result = FALSE;

	//CreateSymbolicLinkTransacted �Լ��� �� ��° �Ķ����(�ڵ�). CreateTransaction ���ϰ�.
	hTranscation = CreateTransaction(NULL, 0, TRANSACTION_DO_NOT_PROMOTE, 0,0,0, NULL);

	if(hTranscation == INVALID_HANDLE_VALUE){
		strcpy(msg, "CreateTransaction�� �����߽��ϴ�. \nCreateHardLinkTransactedA�� ������ �� �����ϴ�. ");

	}else{

		//BOOL result = CreateSymbolicLinkTransactedA("C:\\Users\\Tmax\\Desktop\\test\\test.link", "C:\\Users\\Tmax\\Desktop\\test\\test.txt", 0x0, hTranscation);
		result = CreateSymbolicLinkTransactedA("�ճ���\\test.link", "�ճ���\\test.txt", 0x0, hTranscation);

		//CreateSymbolicLinkTransactedW�� 0�� �ƴϸ� ����
		if(result != FALSE){
			strcpy(msg, "CreateSymbolicLinkTransactedA() : SUCCESS");
			strcpy(buf, "SUCCESS");
			result = TRUE;

		}else{
			strcpy(msg, "CreateSymbolicLinkTransactedA() : FAIL");
			printf("���� �ڵ� : %d \n", GetLastError());
			printf(GetErrorMessage("CreateSymbolicLinkTransactedA() : FAIL \nError Message : ", GetLastError()));

			//return FALSE;
		}
	}

	CloseHandle(hTranscation);

	wresult(__FILE__, __LINE__, "CreateSymbolicLinkTransactedA", buf, "SUCCESS", msg);
	return result;
}


/**
* BOOLEAN WINAPI CreateSymbolicLinkTransacted(
  _In_ LPTSTR lpSymlinkFileName,
  _In_ LPTSTR lpTargetFileName,
  _In_ DWORD  dwFlags,
  _In_ HANDLE hTransaction
  );
* Ʈ����� ���۷��̼����� �ɺ��� ��ũ ����
* @author : �ճ���
*
* @param lpSymlinkFileName ������ �ɺ��� ��ũ��
* @param lpTargetFileName �ɺ��� ��ũ�� ���� Ÿ�ٸ�. lpTargetFileName�� ����� ��ġ���� ������ ��ũ�� ���� ��ũ�� ó����. �׷��� ������ ��ũ�� ��� ��ũ�� ��޵�.
* @param dwFlags ��ũ ����� lpTargetFileName�� ���丮���� ����. 0�̸� ����, SYMBOLIC_LINK_FLAG_DIRECTORY�̸� ���丮.
* @param hTransaction Ʈ����� �ڵ�. CreateTransaction �Լ��� ���� ��ȯ��.
* @return �ɺ��� ��ũ ���� ����/���� ����
*/

BOOL test_CreateSymbolicLinkTransactedW(){

	#ifdef OQADBGPRINT
	printf("CreateSymbolicLinkTransactedW \n");
	#endif

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	HWND hWnd = 0;
	HANDLE hTranscation;
	BOOL result = FALSE;

	//CreateSymbolicLinkTransacted �Լ��� �� ��° �Ķ����(�ڵ�). CreateTransaction ���ϰ�.
	hTranscation = CreateTransaction(NULL, 0, TRANSACTION_DO_NOT_PROMOTE, 0,0,0, NULL);

	if(hTranscation == INVALID_HANDLE_VALUE){
		strcpy(msg, " CreateTransaction�� �����߽��ϴ�. \n CreateSymbolicLinkTransactedW�� ������ �� �����ϴ�. ");

	}else{

		//BOOL result = CreateSymbolicLinkTransactedA("C:\\Users\\Tmax\\Desktop\\test\\test.link", "C:\\Users\\Tmax\\Desktop\\test\\test.txt", 0x0, hTranscation);
		result = CreateSymbolicLinkTransactedW(L"�ճ���\\test.link", L"�ճ���\\test.txt", 0x0, hTranscation);

		//CreateSymbolicLinkTransactedW�� 0�� �ƴϸ� ����
		if(result != FALSE){
			strcpy(msg, "CreateSymbolicLinkTransactedW() : SUCCESS");
			strcpy(buf, "SUCCESS");
			result = TRUE;

		}else{
			strcpy(msg, "CreateSymbolicLinkTransactedW() : FAIL");
			printf("���� �ڵ� : %d \n", GetLastError());
			printf(GetErrorMessage("CreateSymbolicLinkTransactedW() : FAIL \nError Message : ", GetLastError()));

			//return FALSE;
		}
	}

	CloseHandle(hTranscation);

	wresult(__FILE__, __LINE__, "CreateSymbolicLinkTransactedW", buf, "SUCCESS", msg);
	return result;
}


/**
* void WINAPI FatalAppExit(
  _In_ UINT    uAction,
  _In_ LPCTSTR lpMessageText
  );
* �޽��� �ڽ� �����ְ� �ڽ� ���� �� ����â ����.
* @author : �ճ���
* 
* @param uAction 0�̾�� ��.
* @param lpMessageText �޽��� �ڽ��� ������ ����.
* @return ����.
*/
BOOL test_FatalAppExitW(){ // ���� �ڵ鸵

	#ifdef OQADBGPRINT
	printf("test_FatalAppExit \n");
	#endif

	// ���� ���� �Լ��� �Բ� �׽�Ʈ�ϰ� �ִ� ���� â�� �����Ű�⿡�� ��ȿ�����̶� �Ǵ��Ͽ�,
	// WinExec �Լ��� FatalAppExit �ҷ��� �׽�Ʈ ����.
	// �׷��� �� �Լ������� �ش� �׽�Ʈ ������ ������ WinExec �Լ��� ����� ����Ǹ� ���� �Ǵ�.
	
	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	UINT result = FALSE;

	result = WinExec("�ճ���\\FatalAppExit_exe_file_test.exe", SW_SHOW);

	if(result > 31){
		strcpy(msg, "�������� Ȯ���Ͻʽÿ�");
		strcpy(buf, "SUCCESS");
		//sprintf(msg, " WinExec �� FatalAppExit() : SUCCESS");
		result = TRUE;
	
	}else{
		strcpy(msg, " ���� ������ ������ �ʽ��ϴ�. \n\n WinExec �Լ��� �ٽ� Ȯ���ϰų�, ���� ���� ���� ���θ� Ȯ���Ͻʽÿ�.");
	}

	// �������� Ȯ���ؾ� �ϴ� ��� isManual �߰�_OQA1
	isManual = TRUE; 
	wresult(__FILE__, __LINE__, "FatalAppExitW", buf, "SUCCESS", msg);
	isManual = FALSE;

	return result;
}


/**
* void WINAPI FatalExit(
  _In_ int ExitCode
  );
* ���� ��� ����ŷ� ����. ���ø����̼� ���� ���� �ߴ�.
* @author : �ճ���
*
* @param ExitCode ���� �ڵ�
* @return ����
*/

/** debugger execution control ����.
	application ���� ���� ���۽����� �ߴ��ϴ� function.
	�޸𸮿� ���������� ����.
	���� debug�� ���� ����.	*/

BOOL test_FatalExit(){
	
	#ifdef OQADBGPRINT
	printf("test_FatalExit \n");
	#endif

	char msg[BUFSIZ];
	char buf[BUFSIZ] = "FAIL";

	BOOL result = FALSE;

	result = WinExec("�ճ���\\FatalExit_exe_file_test.exe", SW_SHOW);

	if(result > 31){
		strcpy(msg, "�������� Ȯ���Ͻʽÿ�");
		strcpy(buf, "SUCCESS");
		//strcpy(msg, " WinExec �� FatalAppExit() : SUCCESS");
		result = TRUE;
	
	}else{
		//strcpy(msg, " WinExec �� FatalAppExit() : FAIL");
	}

	isManual = TRUE; 
	wresult(__FILE__, __LINE__, "FatalAppExitA", buf, "SUCCESS", msg);
	isManual = FALSE;

	return result;
}


/**
* HRESULT WINAPI GetApplicationRestartSettings(
  _In_      HANDLE hProcess,
  _Out_opt_ PWSTR  pwzCommandline,
  _Inout_   PDWORD pcchSize,
  _Out_opt_ PDWORD pdwFlags
  );
* Ư�� ���μ����� ��ϵ� ����� ������ ������
* @author : �ճ���
*
* @param hProcess �ü��� �ڵ�. PROCESS_VM_READ ���� �ʼ�.
* @param pwzCommandline RegisterApplicationRestart�Լ��� �ҷ��� �� ���ø����̼��� ������ ����� �ڸ�� ������ �޴� ������ ������. pcchSize�� 0�� �� �� �Ķ���ʹ� NULL ����.
* @param pcchSize pwzCommandLine�� ũ�� ����. character.
* @param pdwFlags  RegisterApplicationRestart�Լ��� �ҷ��� �� ���ø����̼ǿ��� ������ �÷��׸� �޴� ������ ���� ������.
* @return ���� �������� ���� �� S_OK.
*/

BOOL test_GetApplicationRestartSettings(){

	#ifdef OQADBGPRINT
	printf("test_GetApplicationRestartSettings\n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ];

	HRESULT result = NULL;
	HANDLE hProcess = GetCurrentProcess();
	WCHAR pwzCommandline[RESTART_MAX_CMD_LINE + 1];
	DWORD pcchSize = sizeof(pwzCommandline) / sizeof(WCHAR);
	DWORD pdwFlags = 0;
	BOOL return_value = FALSE;

	// RegisterApplicationRestart ���� ����
	result = RegisterApplicationRestart(L"/restart -f .\\filename.ext", 0);

	if (result == S_OK) { // RegisterApplicationRestart ���� ��. 
						  // �Ǵ� SUCCEED(result) / FAIL(result)�ε� ����.

		// GetApplicationRestartSettings�Լ� ����
		result = GetApplicationRestartSettings(hProcess, pwzCommandline, &pcchSize, &pdwFlags);

		if(result == S_OK){ // ����
			strcpy(msg, " GetApplicationRestartSettings() : SUCCESS");
			strcpy(buf, "SUCCESS");
			return_value = TRUE;

		}else if(result == E_INVALIDARG){
			strcpy(msg, " GetApplicationRestartSettings() : SUCCESS \n\n Error Code : E_INVALIDARG \n ���� �� �̻��� �Ķ���Ͱ� ��ȿ���� �ʽ��ϴ�.");

		}else if(result == ERROR_NOT_FOUND){
			strcpy(msg, " GetApplicationRestartSettings() : SUCCESS \n\n Error Code : ERROR_NOT_FOUND \n �� ���� ���α׷��� ������ϴµ� ��ϵ��� �ʾҽ��ϴ�.");

		}else if(result == ERROR_INSUFFICIENT_BUFFER){
			strcpy(msg, " GetApplicationRestartSettings() : SUCCESS \n\n Error Code : ERROR_INSUFFICIENT_BUFFER \n �� pwzCommandLine�� ũ�Ⱑ �ʹ� �۽��ϴ�.");

		}else 
			strcpy(msg, " GetApplicationRestartSettings() : FAIL");

	}else if(result == E_FAIL){
		strcpy(msg, "Error Code : E_FAIL \n RegisterApplicationRestart �Լ��� �ٽ� Ȯ���Ͻʽÿ�.");

	}else if(result == E_INVALIDARG){
		strcpy(msg, "Error Code : E_INVALIDARG \n RegisterApplicationRestart �Լ��� �ٽ� Ȯ���Ͻʽÿ�.");

	}else
		strcpy(msg, "RegisterApplicationRestart �Լ��� �ٽ� Ȯ���Ͻʽÿ�.");

	wresult(__FILE__, __LINE__, "GetApplicationRestartSettings", buf, "SUCCESS", msg);
	return return_value;
}


/**
* DWORD WINAPI GetFinalPathNameByHandle(
  _In_  HANDLE hFile,
  _Out_ LPTSTR lpszFilePath,
  _In_  DWORD  cchFilePath,
  _In_  DWORD  dwFlags
  );
* Ư�� ������ ������ ��� ������.
* @author : �ճ���
*
* @param hFile ���� �Ǵ� ���͸��� �ڵ�
* @param lpszFilePath hFile�� ��θ� �޴� ���ۿ� ���� ������
* @param cchFilePath lpszFilePath�� ������. NULL �������� X.
* @param dwFlags ��� Ȯ��. 2+4=6����.
* @return ���� ��� Ÿ��.
*/

#define BUFSIZE MAX_PATH
BOOL test_GetFinalPathNameByHandleA(){

	#ifdef OQADBGPRINT
	printf("test_GetFinalPathNameByHandleA\n");
	#endif

	HANDLE hFile = NULL;
	DWORD result = 0;
	TCHAR lpszFilePath[BUFSIZE];
	BOOL return_value = FALSE;

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ];

	// �׽�Ʈ�� �� ���� ���� �����Ͽ� handle�� in.
	hFile = CreateFile(L"�ճ���\\test_GetFinalPathNameByHandleA.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile ==INVALID_HANDLE_VALUE){
		sprintf(msg, "Could not open file (error %d\n)", GetLastError());
		return 0;
	}

	// dwFlags �� VOLUME_NAME_NT : ���� ��ġ ��ο� �Բ� ��θ� ����.
	result = GetFinalPathNameByHandleA(hFile, (LPSTR)lpszFilePath, BUFSIZE, VOLUME_NAME_NT);

	// ���� �� ��ȯ���� ���ŵ� ���ڿ��� ����. null �������� ����.
	if(result < BUFSIZE)	{
		sprintf(msg, " GetFinalPathNameByHandle() : SUCCESS \n\nThe final path :  %s \n", lpszFilePath);
		strcpy(buf, "SUCCESS");
	}

	// ���� �� TCHAR�� �ʿ��� ���� ũ��. null ����.
	else{
		sprintf(msg, " GetFinalPathNameByHandle() : FAIL \n\n The required buffer size is %d.\n", result);
		//return FALSE;
	}

	// �ڵ� �ݱ�
	CloseHandle(hFile);

	wresult(__FILE__, __LINE__, "GetFinalPathNameByHandle", buf, "SUCCESS", msg);
	return return_value;
}


/**
* BOOL WINAPI GetVolumeInformationByHandleW(
  _In_      HANDLE  hFile,
  _Out_opt_ LPWSTR  lpVolumeNameBuffer,
  _In_      DWORD   nVolumeNameSize,
  _Out_opt_ LPDWORD lpVolumeSerialNumber,
  _Out_opt_ LPDWORD lpMaximumComponentLength,
  _Out_opt_ LPDWORD lpFileSystemFlags,
  _Out_opt_ LPWSTR  lpFileSystemNameBuffer,
  _In_      DWORD   nFileSystemNameSize
  );  
* Ư�� ���ϰ� ����� ���� �ý��� �� ������ ���� ������ ������
* @author : �ճ���
*
* @param hFile ���� �ڵ�
* @param lpVolumeNameBuffer Ư�� �������� �޴� ���ۿ� ���� ������. ������ �ִ� ������� MAX_PATH + 1.
* @param nVolumeNameSize WCHAR���� ������ ������ ����. ������ �ִ� ������� MAX_PATH +1. ������ ���۰� �������� ���� ��쿣 �� �Ķ���� ���� ����.
* @param lpVolumeSerialNumber ���� �ø��� �ѹ��� �޴� ������ ���� ������.
* @param lpMaximumComponentLength Ư�� ���� �ý����� �����ϴ� ���ϸ� ������Ʈ�� �ִ� ���̸� �޴� ������ ���� ������. WCHAR.
* @param lpFileSystemFlags Ư�� ���� �ý��۰� �����ִ� �÷��׸� �޴� ������ ���� ������. 19����. FILE_FILE_COMPRESSION and FILE_VOL_IS_COMPRESSED�� ��ȣ��Ÿ��.
* @param lpFileSystemNameBuffer FAT �Ǵ� NTFS ���� �ý��ۿ��� ���� �ý����� �̸��� �޴� ���ۿ� ���� ������. ���� ������� nFileSystemNameSize �Ķ���Ϳ� ����.
* @param nFileSystemNameSize ���� �ý��� �̸� ������ ����. WCHAR. �ִ� ������� MAX_PATH+1.
* @return ��� ���� �������� ����/���� ����
*/

#define BUFSIZE MAX_PATH
BOOL test_GetVolumeInformationByHandleW(){

	#ifdef OQADBGPRINT
	printf("test_GetVolumeInformationByHandleW \n");
	#endif

	BOOL result = FALSE;
	TCHAR Volume[MAX_PATH];

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZE] = "FAIL";

	//HANDLE hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test_GetVolumeInformationByHandleW.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hFile = CreateFile(L"�ճ���\\test_GetVolumeInformationByHandleW.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//�Ķ����(���� �ڵ�, ���� �̸� ���� ����, ���� �̸� ���� ����, �ø��� �ѹ�, ���� ������� �̸� ����, ..)
	result = GetVolumeInformationByHandleW(hFile,Volume,MAX_PATH,NULL,NULL,NULL,NULL,0);

	//��û�� ��� ������ �������� ��ȯ ���� != 0
	if(result != 0){
		result = TRUE;
		sprintf(msg, "GetVolumeInformationByHandleW() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}
	else{
		result = FALSE;
		strcpy(msg, GetErrorMessage(" GetVolumeInformationByHandleW() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetVolumeInformationByHandleW", buf, "SUCCESS", msg);
	return result;
}


/**
* DWORD APIENTRY ReadThreadProfilingData(
  _In_  HANDLE            PerformanceDataHandle,
  _In_  DWORD             Flags,
  _Out_ PPERFORMANCE_DATA PerformanceData
  );
* ������� ����Ǿ� �ִ� Ư�� �������ϸ� �����͸� ����.
* @author : �ճ���
*
* @param PerformanceDataHandle EnableThreadProfiling�Լ��� ������ �ڵ�.
* @param Flags �ϳ� �Ǵ� �� �̻��� �÷��� ����. EnableThreadProfilingȣ���� �� ���� �Ǿ� �־�� ��.
* @param PerformanceData ������ �������ϸ��� �ϵ���� ī��Ʈ �����͸� �����ϴ� PERFORMANCE_DATA ����ü.
* @return ȣ�⿡ ���� �� ERROR_SUCCESS.
*/

BOOL test_ReadThreadProfilingData(){

	#ifdef OQADBGPRINT
	printf("test_ReadThreadProfilingData \n");
	#endif

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZE] = "FAIL";

	HANDLE pdi;
	HANDLE currentThread = GetCurrentThread();
	OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());

	BOOL return_value = FALSE;
	DWORD result = EnableThreadProfiling(currentThread, 0, 65535, &pdi );

	_PERFORMANCE_DATA pdo;
	ZeroMemory(&pdo, sizeof(pdo));
	pdo.Version = PERFORMANCE_DATA_VERSION;
	pdo.Size = 288;
	result = ReadThreadProfilingData( pdi, READ_THREAD_PROFILING_FLAG_HARDWARE_COUNTERS, &pdo );

	// Disable thread profiling
	DisableThreadProfiling( currentThread );

	result =  ReadThreadProfilingData( pdi, READ_THREAD_PROFILING_FLAG_HARDWARE_COUNTERS, &pdo );

	if(result == ERROR_SUCCESS){
		return_value = TRUE;
		sprintf(msg, "ReadThreadProfilingData() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}
	else{
		result = FALSE;
		strcpy(msg, " ReadThreadProfilingData() : FAIL ");
	}

	wresult(__FILE__, __LINE__, "ReadThreadProfilingData", buf, "SUCCESS", msg);
	return return_value;
}


/**
* HRESULT WINAPI RegisterApplicationRestart(
  _In_opt_ PCWSTR pwzCommandline,
  _In_     DWORD  dwFlags
  );
* ������� ���� ���� ���α׷��� active �ν��Ͻ� ���
* @author : �ճ���
*
* @param pwzCommandline ����۵� �� ���� ���α׷��� ����� ���ڸ� Ư���ϴ� �����ڵ� ���ڿ��� ���� ������. �ִ� ũ��� RESTART_MAX_CMD_LINE ���ڿ�. �ڸ�� ���ο� ���� ���ϸ� ���� X.
						�Ű������� NULL�̰ų� �� ���ڿ��̸� ������ ��ϵ� ����� ����. ���ڿ� ���� ������ ���ڸ� ����ǥ�� ����� ��.
* @param dwFlags �Ķ���ʹ� 0 �Ǵ� 1�� �Ǵ� 4����.
* @return ��� ���� �� ERROR_SUCCESS.
*/

BOOL test_RegisterApplicationRestart(){

	#ifdef OQADBGPRINT
	printf("test_RegisterApplicationRestart \n");
	#endif

	int wresult_value=0;
	char buf[BUFSIZ];
	char msg[BUFSIZ];

	HRESULT result;
	
	result = RegisterApplicationRestart(L"avc", RESTART_NO_CRASH|RESTART_NO_HANG);

	if(result == S_OK){
		strcpy(msg, "RegisterApplicationRestart() : SUCCESS");
		wresult_value=1;

	}else{
		strcpy(msg, "RegisterApplicationRestart() : FAIL");
		printf("���� �ڵ� : %d \n", GetLastError());
		printf(GetErrorMessage("RegisterApplicationRestart() : FAIL \nError Message : ", GetLastError()));
	}

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegisterApplicationRestart", buf, "1", msg);

	return result;
}


/**
* DWORD WINAPI SetCriticalSectionSpinCount(
  _Inout_ LPCRITICAL_SECTION lpCriticalSection,
  _In_    DWORD              dwSpinCount
  );
* Ư�� critical section�� ���� ���� ī��Ʈ ����.
* @author : �ճ���
*
* @param lpCriticalSection critical section object�� ���� ������.
* @param dwSpinCount critical section object�� ��Ų ī��Ʈ. �̱� ���μ��� �ý����� ���, spin count�� ���õǰ� 0���� ���� ����.
* @return critical section�� ���� ȸ�� ���� ��ȯ.
*/

BOOL test_SetCriticalSectionSpinCount(){

	#ifdef OQADBGPRINT
	printf("test_SetCriticalSectionSpinCount\n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	DWORD result = 0;
	CRITICAL_SECTION lpCriticalSection;

	// spincount�� 4000���� set
	// short duration�� critical section�� ���� spin count �۰� ���������μ� ���� ��� ����
	// �Լ� ���� �� critical section�� ���� ȸ�� ���� ��ȯ. result�� ����.
	result = SetCriticalSectionSpinCount(&lpCriticalSection, 4000);

	if(result != 0){
		sprintf(msg, "SetCriticalSectionSpinCount() : SUCCESS \n\ncritical section�� ���� spin �� : %d", result);
		strcpy(buf, "SUCCESS");
	}else {
		sprintf(msg, GetErrorMessage("SetCriticalSectionSpinCount() : FAIL \n\n Error Message :", GetLastError()));
		strcpy(buf, "FAIL");
	}

	wresult(__FILE__, __LINE__, "SetCriticalSectionSpinCount", buf, "SUCCESS", msg);
	return true;
}

/**
* BOOL WINAPI SetFileInformationByHandle(
  _In_ HANDLE                    hFile,
  _In_ FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
  _In_ LPVOID                    lpFileInformation,
  _In_ DWORD                     dwBufferSize
  );
* Ư�� ������ ������ ����
* @author : �ճ���
*
* @param hFile ������ ������ ������ �ڵ�. ������ ���� ������ �㰡�� �Բ� ���µǾ� �־�� �ϸ�, pipe �ڵ��� �Ұ�.
* @param FileInformationClass ������ ������ Ÿ���� Ư���ϴ� FILE_INFO_BY_HANDLE_CLASS ������.
* @param lpFileInformation Ư�� ���� ���� Ŭ������ �����ϱ� ���� ������ �����ϴ� ���ۿ� ���� ������. �� �Ű� ������ ����Ű�� ������ FileInformationClass�� ������ Ŭ������ �ش�.
* @param dwBufferSize lpFileInformation �� ũ��. ����Ʈ. 
* @return ���� ���� ����/���� ����
*/

BOOL test_SetFileInformationByHandle(){

	#ifdef OQADBGPRINT
	printf("test_SetFileInformationByHandle \n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	HANDLE hFile = NULL;
	BOOL result = FALSE;

	// ���� ���� �����ؼ� �ڵ鿡 ����.
	// HANDLE hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test_GetVolumeInformationByHandleW.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	hFile = CreateFile(L"tempfile", GENERIC_READ | GENERIC_WRITE | DELETE, 0 , NULL, CREATE_ALWAYS, 0, NULL);

	if (hFile != INVALID_HANDLE_VALUE){ // �ڵ��� ��ȿ�� ��� ��� ����
		FILE_DISPOSITION_INFO lpFileInformation;
		lpFileInformation.DeleteFile = TRUE; 

		result = SetFileInformationByHandle( hFile, FileDispositionInfo, &lpFileInformation, sizeof(FILE_DISPOSITION_INFO));

		if (result != FALSE){ // ����
			strcpy(msg, "SetFileInformationByHandle() : SUCCESS");
			strcpy(buf, "SUCCESS");
			//result = TRUE;

		}else{ //����
			strcpy(buf, GetErrorMessage("SetFileInformationByHandle() : FAIL \n\n Error Message :", GetLastError()));
		}

		// �ڵ� �ݱ�.
		CloseHandle(hFile); 

	}else {
		strcpy(buf, GetErrorMessage("SetFileInformationByHandle() : FAIL could not create tempfile !\nError Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "SetFileInformationByHandle", buf, "SUCCESS", msg);
	return result;
}


/**
* BOOL WINAPI SetStdHandleEx ( 
    DWORD dwStdHandle, 
    HANDLE hNewHandle, 
    HANDLE* phOldHandle 
  );
* Ư�� ǥ�� ����̽��� �ڵ��� �����ϰ� ���� ���� ����
* @author : �ճ���
*
* @param dwStdHandle ��ü�� ǥ�� �ڵ�. STD_INPUT_HANDLE�̳� STD_OUTPUT_HANDLE, �Ǵ� STD_ERROR_HANDLE ����.
* @param hNewHandle �� �ڵ�.
* @param phOldHandle ���� ���� ���� �ڵ鿡 ���� ������.
* @return ���� ����/���� ����.
*/
BOOL test_SetStdHandleEx(){

	#ifdef OQADBGPRINT
	printf("test_SetStdHandleEx \n");
	#endif

	char msg[BUFSIZ] = "FAIL";																							
	char buf[BUFSIZ] = "FAIL";

	BOOL result = FALSE;
	DWORD dwStdHandle = STD_OUTPUT_HANDLE;
	HANDLE hNewHandle = NULL;
	
	result = SetStdHandleEx(dwStdHandle, hNewHandle, NULL);

	if(result != FALSE){
		sprintf(msg, " SetStdHandleEx() : SUCCESS");
		strcpy(buf, "SUCCESS");
		//result = TRUE;
	}else{
		strcpy(msg, GetErrorMessage(" SetStdHandleEx() : FAIL ", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "SetStdHandleEx", buf, "SUCCESS", msg);
	return result;
}

/**
* HRESULT WINAPI UnregisterApplicationRestart(void);
* ����� ����Ʈ���� ���� ���α׷��� active �ν��Ͻ��� ����
* @author : �ճ���
*
* @param void
* @return ���� ���� �� S_OK.
*/
BOOL test_UnregisterApplicationRestart(){

	#ifdef OQADBGPRINT
	printf("test_RegisterApplicationRestart\n");
	#endif

	int wresult_value=0;
	char buf[BUFSIZ];
	char msg[BUFSIZ];

	HRESULT result = FALSE;
	
	result = UnregisterApplicationRestart();

	if(result == S_OK){
		strcpy(msg, "UnregisterApplicationRestart() : SUCCESS");
		wresult_value=1;
		//result == TRUE;
	}else{
		strcpy(msg, "UnregisterApplicationRestart() : FAIL");
		printf("���� �ڵ� : %d \n", GetLastError());
		printf(GetErrorMessage("UnregisterApplicationRestart() : FAIL \nError Message : ", GetLastError()));
	}

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "UnregisterApplicationRestart", buf, "1", msg);

	return result;
}


/**

BOOL test_FreeLibraryAndExitThread(){

	//HMODULE handle;


	//FreeLibraryAndExitThread(handle, 0);


	return true;
}*/