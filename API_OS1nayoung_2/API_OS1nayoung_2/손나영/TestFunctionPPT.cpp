#include "TestFunctionPPT.h"
#include <ktmw32.h>
#include <stdio.h>
#include <strsafe.h>
#include <WinError.h>

/**
* BOOL WINAPI CreateHardLinkTransacted(
  _In_       LPCTSTR               lpFileName,				새 파일명
  _In_       LPCTSTR               lpExistingFileName,		기존 파일명		
  _Reserved_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,	무조건 NULL
  _In_       HANDLE                hTransaction				트랜잭션 핸들
  );
* 기존 파일과 새 파일 간의 하드 링크를 처리된 작업으로 설정. NTFS 파일 시스템에서만 지원. 디렉토리 X. 파일만 O.
* @author : 손나영

* @param lpFileName 새 파일명
* @param lpExistingFileName 기존 파일명
* @param lpSecurityAttributes 무조건 NULL
* @param hTransaction 트랜잭션 핸들
* @return 하드링크 설정 성공/실패 여부.
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
		strcpy(msg, "CreateTransaction에 실패했습니다. \n CreateHardLinkTransactedA를 진행할 수 없습니다. ");
	}else{
		//CreateHardLinkTransactedA 전 확실히 삭제
		//DeleteFileTransactedA("손나영\\CreateHardLinkTransactedA.link", hTranscation);

		//CreateHardLinkTransactedA 수행
		result = CreateHardLinkTransactedA("손나영\\CreateHardLinkTransactedA.link", "손나영\\CreateHardLinkTransactedA.txt", NULL, hTranscation);

		//CreateHardLinkTransactedA가 0이 아니면 성공
		if(result != FALSE){
			result = TRUE;
			wresult_value=1;
			strcpy(msg, "CreateHardLinkTransactedA() : SUCCESS");

		}else{
			strcpy(msg, "CreateHardLinkTransactedA() : FAIL");
			printf("에러 코드 : %d \n", GetLastError());
			printf(GetErrorMessage("CreateHardLinkTransactedA() : FAIL \nError Message : ", GetLastError()));
		}
	}

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "CreateHardLinkTransactedA", buf, "1", msg);
	
	CloseHandle(hFile);

	//파일 확실히 삭제(CreateHardLink때)
	DeleteFile(L"손나영\\CreateHardLinkTransactedA.link"); //Delete하지 않은 상태에서 다시 CreateHardLinkW를 진행하면 FAIL됨. 반드시 삭제해야 함.
	DeleteFile(L"손나영\\CreateHardLinkTransactedA.txt");

	return result;
}

/**
* BOOL WINAPI CreateHardLinkTransacted(
  _In_       LPCTSTR               lpFileName,				새 파일명
  _In_       LPCTSTR               lpExistingFileName,		기존 파일명		
  _Reserved_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,	무조건 NULL
  _In_       HANDLE                hTransaction				트랜잭션 핸들
  );
* 기존 파일과 새 파일 간의 하드 링크를 처리된 작업으로 설정. NTFS 파일 시스템에서만 지원. 디렉토리 X. 파일만 O.
* @author : 손나영

* @param lpFileName 새 파일명
* @param lpExistingFileName 기존 파일명
* @param lpSecurityAttributes 무조건 NULL
* @param hTransaction 트랜잭션 핸들
* @return 하드링크 설정 성공/실패 여부.
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
		strcpy(msg, "CreateTransaction에 실패했습니다. \nCreateHardLinkTransactedW를 진행할 수 없습니다. ");

	}else{
		//CreateHardLinkTransactedA 전 확실히 삭제
		//DeleteFileTransactedA("손나영\\CreateHardLinkTransactedA.link", hTranscation);

		//CreateHardLinkTransactedA 수행
		result = CreateHardLinkTransactedW(L"손나영\\CreateHardLinkTransactedW.link", L"손나영\\CreateHardLinkTransactedW.txt", NULL, hTranscation);

		//CreateHardLinkTransactedA가 0이 아니면 성공
		if(result != FALSE){
			result = TRUE;
			wresult_value=1;
			strcpy(msg, "CreateHardLinkTransactedW() : SUCCESS");

		}else{
			strcpy(msg, "CreateHardLinkTransactedW() : FAIL");
			printf("에러 코드 : %d \n", GetLastError());
			printf(GetErrorMessage("CreateHardLinkTransactedW() : FAIL \nError Message : ", GetLastError()));
		}
	}

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "CreateHardLinkTransactedW", buf, "1", msg);
	
	CloseHandle(hFile);

	//파일 확실히 삭제(CreateHardLink때)
	DeleteFile(L"손나영\\CreateHardLinkTransactedW.link"); //Delete하지 않은 상태에서 다시 CreateHardLinkW를 진행하면 FAIL됨. 반드시 삭제해야 함.
	DeleteFile(L"손나영\\CreateHardLinkTransactedW.txt");

	return result;
}


/**
* BOOLEAN WINAPI CreateSymbolicLinkTransacted(
  _In_ LPTSTR lpSymlinkFileName,
  _In_ LPTSTR lpTargetFileName,
  _In_ DWORD  dwFlags,
  _In_ HANDLE hTransaction
  );
* 트랜잭션 오퍼레이션으로 심볼릭 링크 생성
* @author : 손나영
*
* @param lpSymlinkFileName 생성될 심볼릭 링크명
* @param lpTargetFileName 심볼릭 링크를 만들 타겟명. lpTargetFileName에 연결된 장치명이 있으면 링크가 절대 링크로 처리됨. 그렇지 않으면 링크가 상대 링크로 취급됨.
* @param dwFlags 링크 대상인 lpTargetFileName이 디렉토리인지 여부. 0이면 파일, SYMBOLIC_LINK_FLAG_DIRECTORY이면 디렉토리.
* @param hTransaction 트랜잭션 핸들. CreateTransaction 함수에 의해 반환됨.
* @return 심볼릭 링크 생성 성공/실패 여부
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

	//CreateSymbolicLinkTransacted 함수의 네 번째 파라미터(핸들). CreateTransaction 리턴값.
	hTranscation = CreateTransaction(NULL, 0, TRANSACTION_DO_NOT_PROMOTE, 0,0,0, NULL);

	if(hTranscation == INVALID_HANDLE_VALUE){
		strcpy(msg, "CreateTransaction에 실패했습니다. \nCreateHardLinkTransactedA를 진행할 수 없습니다. ");

	}else{

		//BOOL result = CreateSymbolicLinkTransactedA("C:\\Users\\Tmax\\Desktop\\test\\test.link", "C:\\Users\\Tmax\\Desktop\\test\\test.txt", 0x0, hTranscation);
		result = CreateSymbolicLinkTransactedA("손나영\\test.link", "손나영\\test.txt", 0x0, hTranscation);

		//CreateSymbolicLinkTransactedW가 0이 아니면 성공
		if(result != FALSE){
			strcpy(msg, "CreateSymbolicLinkTransactedA() : SUCCESS");
			strcpy(buf, "SUCCESS");
			result = TRUE;

		}else{
			strcpy(msg, "CreateSymbolicLinkTransactedA() : FAIL");
			printf("에러 코드 : %d \n", GetLastError());
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
* 트랜잭션 오퍼레이션으로 심볼릭 링크 생성
* @author : 손나영
*
* @param lpSymlinkFileName 생성될 심볼릭 링크명
* @param lpTargetFileName 심볼릭 링크를 만들 타겟명. lpTargetFileName에 연결된 장치명이 있으면 링크가 절대 링크로 처리됨. 그렇지 않으면 링크가 상대 링크로 취급됨.
* @param dwFlags 링크 대상인 lpTargetFileName이 디렉토리인지 여부. 0이면 파일, SYMBOLIC_LINK_FLAG_DIRECTORY이면 디렉토리.
* @param hTransaction 트랜잭션 핸들. CreateTransaction 함수에 의해 반환됨.
* @return 심볼릭 링크 생성 성공/실패 여부
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

	//CreateSymbolicLinkTransacted 함수의 네 번째 파라미터(핸들). CreateTransaction 리턴값.
	hTranscation = CreateTransaction(NULL, 0, TRANSACTION_DO_NOT_PROMOTE, 0,0,0, NULL);

	if(hTranscation == INVALID_HANDLE_VALUE){
		strcpy(msg, " CreateTransaction에 실패했습니다. \n CreateSymbolicLinkTransactedW를 진행할 수 없습니다. ");

	}else{

		//BOOL result = CreateSymbolicLinkTransactedA("C:\\Users\\Tmax\\Desktop\\test\\test.link", "C:\\Users\\Tmax\\Desktop\\test\\test.txt", 0x0, hTranscation);
		result = CreateSymbolicLinkTransactedW(L"손나영\\test.link", L"손나영\\test.txt", 0x0, hTranscation);

		//CreateSymbolicLinkTransactedW가 0이 아니면 성공
		if(result != FALSE){
			strcpy(msg, "CreateSymbolicLinkTransactedW() : SUCCESS");
			strcpy(buf, "SUCCESS");
			result = TRUE;

		}else{
			strcpy(msg, "CreateSymbolicLinkTransactedW() : FAIL");
			printf("에러 코드 : %d \n", GetLastError());
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
* 메시지 박스 보여주고 박스 닫힐 때 실행창 종료.
* @author : 손나영
* 
* @param uAction 0이어야 함.
* @param lpMessageText 메시지 박스에 보여줄 내용.
* @return 없음.
*/
BOOL test_FatalAppExitW(){ // 에러 핸들링

	#ifdef OQADBGPRINT
	printf("test_FatalAppExit \n");
	#endif

	// 여러 개의 함수를 함께 테스트하고 있는 현재 창을 종료시키기에는 비효율적이라 판단하여,
	// WinExec 함수로 FatalAppExit 불러서 테스트 진행.
	// 그래서 현 함수에서는 해당 테스트 파일이 열리는 WinExec 함수가 제대로 실행되면 성공 판단.
	
	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	UINT result = FALSE;

	result = WinExec("손나영\\FatalAppExit_exe_file_test.exe", SW_SHOW);

	if(result > 31){
		strcpy(msg, "수동으로 확인하십시오");
		strcpy(buf, "SUCCESS");
		//sprintf(msg, " WinExec → FatalAppExit() : SUCCESS");
		result = TRUE;
	
	}else{
		strcpy(msg, " 실행 파일이 열리지 않습니다. \n\n WinExec 함수를 다시 확인하거나, 실행 파일 존재 여부를 확인하십시오.");
	}

	// 수동으로 확인해야 하는 경우 isManual 추가_OQA1
	isManual = TRUE; 
	wresult(__FILE__, __LINE__, "FatalAppExitW", buf, "SUCCESS", msg);
	isManual = FALSE;

	return result;
}


/**
* void WINAPI FatalExit(
  _In_ int ExitCode
  );
* 실행 제어를 디버거로 전송. 어플리케이션 실행 도중 중단.
* @author : 손나영
*
* @param ExitCode 오류 코드
* @return 없음
*/

/** debugger execution control 전송.
	application 실행 도중 갑작스럽게 중단하는 function.
	메모리에 남아있지는 않음.
	보통 debug를 위해 사용됨.	*/

BOOL test_FatalExit(){
	
	#ifdef OQADBGPRINT
	printf("test_FatalExit \n");
	#endif

	char msg[BUFSIZ];
	char buf[BUFSIZ] = "FAIL";

	BOOL result = FALSE;

	result = WinExec("손나영\\FatalExit_exe_file_test.exe", SW_SHOW);

	if(result > 31){
		strcpy(msg, "수동으로 확인하십시오");
		strcpy(buf, "SUCCESS");
		//strcpy(msg, " WinExec → FatalAppExit() : SUCCESS");
		result = TRUE;
	
	}else{
		//strcpy(msg, " WinExec → FatalAppExit() : FAIL");
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
* 특정 프로세스에 등록된 재시작 정보를 가져옴
* @author : 손나영
*
* @param hProcess 플세스 핸들. PROCESS_VM_READ 권한 필수.
* @param pwzCommandline RegisterApplicationRestart함수가 불러질 때 어플리케이션이 지정한 재시작 코멘드 라인을 받는 버퍼의 포인터. pcchSize가 0일 때 이 파라미터는 NULL 가능.
* @param pcchSize pwzCommandLine의 크기 지정. character.
* @param pdwFlags  RegisterApplicationRestart함수가 불러질 때 어플리케이션에서 지정한 플래그를 받는 변수에 대한 포인터.
* @return 정보 가져오기 성공 시 S_OK.
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

	// RegisterApplicationRestart 먼저 수행
	result = RegisterApplicationRestart(L"/restart -f .\\filename.ext", 0);

	if (result == S_OK) { // RegisterApplicationRestart 성공 시. 
						  // 또는 SUCCEED(result) / FAIL(result)로도 가능.

		// GetApplicationRestartSettings함수 수행
		result = GetApplicationRestartSettings(hProcess, pwzCommandline, &pcchSize, &pdwFlags);

		if(result == S_OK){ // 성공
			strcpy(msg, " GetApplicationRestartSettings() : SUCCESS");
			strcpy(buf, "SUCCESS");
			return_value = TRUE;

		}else if(result == E_INVALIDARG){
			strcpy(msg, " GetApplicationRestartSettings() : SUCCESS \n\n Error Code : E_INVALIDARG \n →한 개 이상의 파라미터가 유효하지 않습니다.");

		}else if(result == ERROR_NOT_FOUND){
			strcpy(msg, " GetApplicationRestartSettings() : SUCCESS \n\n Error Code : ERROR_NOT_FOUND \n → 응용 프로그램이 재시작하는데 등록되지 않았습니다.");

		}else if(result == ERROR_INSUFFICIENT_BUFFER){
			strcpy(msg, " GetApplicationRestartSettings() : SUCCESS \n\n Error Code : ERROR_INSUFFICIENT_BUFFER \n → pwzCommandLine의 크기가 너무 작습니다.");

		}else 
			strcpy(msg, " GetApplicationRestartSettings() : FAIL");

	}else if(result == E_FAIL){
		strcpy(msg, "Error Code : E_FAIL \n RegisterApplicationRestart 함수를 다시 확인하십시오.");

	}else if(result == E_INVALIDARG){
		strcpy(msg, "Error Code : E_INVALIDARG \n RegisterApplicationRestart 함수를 다시 확인하십시오.");

	}else
		strcpy(msg, "RegisterApplicationRestart 함수를 다시 확인하십시오.");

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
* 특정 파일의 마지막 경로 가져옴.
* @author : 손나영
*
* @param hFile 파일 또는 디렉터리의 핸들
* @param lpszFilePath hFile의 경로를 받는 버퍼에 대한 포인터
* @param cchFilePath lpszFilePath의 사이즈. NULL 포함하지 X.
* @param dwFlags 결과 확인. 2+4=6가지.
* @return 리턴 결과 타입.
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

	// 테스트에 쓸 파일 먼저 생성하여 handle에 in.
	hFile = CreateFile(L"손나영\\test_GetFinalPathNameByHandleA.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile ==INVALID_HANDLE_VALUE){
		sprintf(msg, "Could not open file (error %d\n)", GetLastError());
		return 0;
	}

	// dwFlags → VOLUME_NAME_NT : 볼륨 장치 경로와 함께 경로를 리턴.
	result = GetFinalPathNameByHandleA(hFile, (LPSTR)lpszFilePath, BUFSIZE, VOLUME_NAME_NT);

	// 성공 시 반환값은 수신된 문자열의 길이. null 포함하지 않음.
	if(result < BUFSIZE)	{
		sprintf(msg, " GetFinalPathNameByHandle() : SUCCESS \n\nThe final path :  %s \n", lpszFilePath);
		strcpy(buf, "SUCCESS");
	}

	// 실패 시 TCHAR에 필요한 버퍼 크기. null 포함.
	else{
		sprintf(msg, " GetFinalPathNameByHandle() : FAIL \n\n The required buffer size is %d.\n", result);
		//return FALSE;
	}

	// 핸들 닫기
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
* 특정 파일과 연결된 파일 시스템 및 볼륨에 대한 정보를 가져옴
* @author : 손나영
*
* @param hFile 파일 핸들
* @param lpVolumeNameBuffer 특정 볼륨명을 받는 버퍼에 대한 포인터. 버퍼의 최대 사이즈는 MAX_PATH + 1.
* @param nVolumeNameSize WCHAR에서 볼륨명 버퍼의 길이. 버퍼의 최대 사이즈는 MAX_PATH +1. 볼륨명 버퍼가 제공되지 않을 경우엔 이 파라미터 무시 가능.
* @param lpVolumeSerialNumber 볼륨 시리얼 넘버를 받는 변수에 대한 포인터.
* @param lpMaximumComponentLength 특정 파일 시스템을 제공하는 파일명 컴포넌트의 최대 길이를 받는 변수에 대한 포인터. WCHAR.
* @param lpFileSystemFlags 특정 파일 시스템과 관계있는 플래그를 받는 변수에 대한 포인터. 19가지. FILE_FILE_COMPRESSION and FILE_VOL_IS_COMPRESSED는 상호배타적.
* @param lpFileSystemNameBuffer FAT 또는 NTFS 파일 시스템에서 파일 시스템의 이름을 받는 버퍼에 대한 포인터. 버퍼 사이즈는 nFileSystemNameSize 파라미터에 의해.
* @param nFileSystemNameSize 파일 시스템 이름 버퍼의 길이. WCHAR. 최대 사이즈는 MAX_PATH+1.
* @return 모든 정보 가져오기 성공/실패 여부
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
	HANDLE hFile = CreateFile(L"손나영\\test_GetVolumeInformationByHandleW.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//파라미터(파일 핸들, 볼륨 이름 수신 버퍼, 볼륨 이름 버퍼 길이, 시리얼 넘버, 파일 구성요소 이름 길이, ..)
	result = GetVolumeInformationByHandleW(hFile,Volume,MAX_PATH,NULL,NULL,NULL,NULL,0);

	//요청된 모든 정보를 가져오면 반환 값은 != 0
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
* 스레드와 연결되어 있는 특정 프로파일링 데이터를 읽음.
* @author : 손나영
*
* @param PerformanceDataHandle EnableThreadProfiling함수가 리턴한 핸들.
* @param Flags 하나 또는 그 이상의 플래그 따름. EnableThreadProfiling호출할 때 셋팅 되어 있어야 함.
* @param PerformanceData 스레드 프로파일링과 하드웨어 카운트 데이터를 포함하는 PERFORMANCE_DATA 구조체.
* @return 호출에 성공 시 ERROR_SUCCESS.
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
* 재시작을 위한 응용 프로그램의 active 인스턴스 등록
* @author : 손나영
*
* @param pwzCommandline 재시작될 때 응용 프로그램의 명령줄 인자를 특정하는 유니코드 문자열에 대한 포인터. 최대 크기는 RESTART_MAX_CMD_LINE 문자열. 코멘드 라인에 실행 파일명 포함 X.
						매개변수가 NULL이거나 빈 문자열이면 이전에 등록된 명령줄 제거. 인자에 공백 있으면 인자를 따옴표로 묶어야 함.
* @param dwFlags 파라미터는 0 또는 1개 또는 4가지.
* @return 등록 성공 시 ERROR_SUCCESS.
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
		printf("에러 코드 : %d \n", GetLastError());
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
* 특정 critical section을 위한 스핀 카운트 설정.
* @author : 손나영
*
* @param lpCriticalSection critical section object에 대한 포인터.
* @param dwSpinCount critical section object의 스킨 카운트. 싱글 프로세서 시스템의 경우, spin count는 무시되고 0으로 설정 가능.
* @return critical section의 이전 회전 수를 반환.
*/

BOOL test_SetCriticalSectionSpinCount(){

	#ifdef OQADBGPRINT
	printf("test_SetCriticalSectionSpinCount\n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	DWORD result = 0;
	CRITICAL_SECTION lpCriticalSection;

	// spincount를 4000으로 set
	// short duration의 critical section을 위해 spin count 작게 설정함으로서 성능 향상 가능
	// 함수 실행 시 critical section의 이전 회전 수를 반환. result에 저장.
	result = SetCriticalSectionSpinCount(&lpCriticalSection, 4000);

	if(result != 0){
		sprintf(msg, "SetCriticalSectionSpinCount() : SUCCESS \n\ncritical section의 이전 spin 수 : %d", result);
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
* 특정 파일의 정보를 설정
* @author : 손나영
*
* @param hFile 정보를 변경할 파일의 핸들. 변경을 위해 적당한 허가와 함께 오픈되어 있어야 하며, pipe 핸들은 불가.
* @param FileInformationClass 변경할 정보의 타입을 특정하는 FILE_INFO_BY_HANDLE_CLASS 열거형.
* @param lpFileInformation 특정 파일 정보 클래스를 변경하기 위한 정보를 포함하는 버퍼에 대한 포인터. 이 매개 변수가 가리키는 구조는 FileInformationClass에 지정된 클래스에 해당.
* @param dwBufferSize lpFileInformation 의 크기. 바이트. 
* @return 정보 설정 성공/실패 여부
*/

BOOL test_SetFileInformationByHandle(){

	#ifdef OQADBGPRINT
	printf("test_SetFileInformationByHandle \n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	HANDLE hFile = NULL;
	BOOL result = FALSE;

	// 파일 먼저 생성해서 핸들에 저장.
	// HANDLE hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test_GetVolumeInformationByHandleW.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	hFile = CreateFile(L"tempfile", GENERIC_READ | GENERIC_WRITE | DELETE, 0 , NULL, CREATE_ALWAYS, 0, NULL);

	if (hFile != INVALID_HANDLE_VALUE){ // 핸들이 유효할 경우 계속 진행
		FILE_DISPOSITION_INFO lpFileInformation;
		lpFileInformation.DeleteFile = TRUE; 

		result = SetFileInformationByHandle( hFile, FileDispositionInfo, &lpFileInformation, sizeof(FILE_DISPOSITION_INFO));

		if (result != FALSE){ // 성공
			strcpy(msg, "SetFileInformationByHandle() : SUCCESS");
			strcpy(buf, "SUCCESS");
			//result = TRUE;

		}else{ //실패
			strcpy(buf, GetErrorMessage("SetFileInformationByHandle() : FAIL \n\n Error Message :", GetLastError()));
		}

		// 핸들 닫기.
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
* 특정 표준 디바이스의 핸들을 설정하고 이전 것을 리턴
* @author : 손나영
*
* @param dwStdHandle 대체할 표준 핸들. STD_INPUT_HANDLE이나 STD_OUTPUT_HANDLE, 또는 STD_ERROR_HANDLE 가능.
* @param hNewHandle 새 핸들.
* @param phOldHandle 이전 값을 받을 핸들에 대한 포인터.
* @return 리턴 성공/실패 여부.
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
* 재시작 리스트에서 응용 프로그램의 active 인스턴스를 삭제
* @author : 손나영
*
* @param void
* @return 삭제 성공 시 S_OK.
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
		printf("에러 코드 : %d \n", GetLastError());
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