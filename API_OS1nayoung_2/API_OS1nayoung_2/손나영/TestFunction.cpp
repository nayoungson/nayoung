#include "TestFunction.h"

/**
* BOOL WINAPI Beep(DWORD dwFreq, DWORD dwDuration)
* beep음 출력.
* @author : 손나영
*
* @param dwFreq 주파수.
* @param dwDuration 지속시간(ms).
* @return beep 음 출력 성공/실패 여부.
*/
BOOL test_Beep(){

	#ifdef OQADBGPRINT
	printf("test_Beep\n");
	#endif

	int wresult_value=0;
	char msg[BUFSIZ];
	char buf[BUFSIZ] = "FAIL";

	LSTATUS result; 

	DWORD dwFreq = 750;	//주파수
	DWORD dwDuration = 300;	//지속시간

	result = Beep(dwFreq, dwDuration);

	if(result != FALSE){ 
		sprintf(msg, " Beep() : SUCCESS \n\n 사운드 장치를 통해 beep음 출력을 확인하십시오");
		strcpy(buf, "SUCCESS");

	}else{
		strcpy(msg, " Beep : FAIL");
	}
	
	wresult(__FILE__, __LINE__, "Beep", buf, "SUCCESS", msg);

	return result;
}


/*
* BOOL WINAPI CreateHardLink(LPCTSTR lpFileName, LPCTSTR lpExistingFileName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
* 존재하는 파일 - 새 파일 사이의 하드 링크 생성.
* @author : 손나영
*
* @param lpFileName 새 파일명.
* @param lpExistingFileName 존재하는 파일명.
* @param lpSecurityAttributes NULL로 예약.
* @return 새 파일 생성 성공/실패 여부
*/

BOOL test_CreateHardLinkW(){
	
	#ifdef OQADBGPRINT
	printf("test_CreateHardLinkW\n");
	#endif

	HWND hWnd = 0;
	HANDLE hFile = NULL;
	BOOL result = FALSE;

	int wresult_value=0;
	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ];

	// Delete하지 않은 상태에서 다시 CreateHardLinkW를 진행하면 FAIL됨. 반드시 삭제해야 함.
	DeleteFile(L"손나영\\test_CreateHardLinkW.link"); 
	DeleteFile(L"손나영\\test_CreateHardLinkW.txt");

	// 파일 생성해서 hFile에 넣음
	hFile = CreateFile(L"손나영\\test_CreateHardLinkW.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// hFile에 들어간 파일을 기존 파일로 두고, 이를 통해 새 파일(.link) 생성
	result = CreateHardLinkW(L"손나영\\test_CreateHardLinkW.link", L"손나영\\test_CreateHardLinkW.txt", NULL);

	if(result != FALSE){ // 성공 
		sprintf(msg, " CreateHardLinkW() : SUCCESS \n\n CreateHardLinkW 성공 \n(계속해서 CreateHardLinkW 실행을 위해 생성한 파일을 삭제합니다.)");
		strcpy(buf, "SUCCESS");

	}else{ //실패
		strcpy(msg, " CreateHardLinkW() : FAIL \n\n 생성 실패 \n(관리자 권한으로 실행했는지, 경로가 올바른지 확인하십시오.)");
	}

	//반드시 핸들 닫아줘야 함
	CloseHandle(hFile);

	//다음 진행을 위해 삭제
	DeleteFile(L"손나영\\test_CreateHardLinkW.link"); //Delete하지 않은 상태에서 다시 CreateHardLinkW를 진행하면 FAIL됨. 반드시 삭제해야 함.
	DeleteFile(L"손나영\\test_CreateHardLinkW.txt");

	wresult(__FILE__, __LINE__, "CreateHardLinkW", buf, "SUCCESS", msg);
	return result;

	// author 참고용 → C:\Users\NAYOUNG\Documents\Visual Studio 2012\Projects\API_OS1nayoung_2\API_OS1nayoung_2\손나영
}

/**
* HANDLE WINAPI CreateJobObject(LPSECURITY_ATTRIBUTES lpJobAttributes, LPCTSTR lpName)
* job object를 생성 또는 오픈. 성공 시 모두 0으로 초기화 + 비활성 + 연결프로세스 없는 상태.
* @author : 손나영
*
* @param lpJobAttributes SECURITY_ATTRIBUTES 구조체 포인터. NULL이면 dafault 보안 설정 + 핸들 상속 불가.
* @param lpName job object 이름. NULL이면 특정 이름 없이 실행.
* @return job object에 대한 핸들. 핸들은 JOB_OBJECT_ALL_ACCESS 권한을 가짐.
*/

BOOL test_CreateJobObjectW(){

	#ifdef OQADBGPRINT
	printf("test_CreateJobObjectW\n");
	#endif

	char msg[BUFSIZ];
	char buf[BUFSIZ] = "FAIL";

	HANDLE result = NULL;
	BOOL return_value = FALSE;
	
	result = CreateJobObjectW(NULL, L"CreateJob_Object");

	if(result != NULL){ // 생성 또는 오픈 성공
		return_value = TRUE;
		strcpy(buf, "SUCCESS");
		sprintf(msg, " CreateJobObjectW() : SUCCESS");
		
	}else{
		return_value = FALSE;
		sprintf(msg, " CreateJobObjectW() : FAIL");
	}

	wresult(__FILE__, __LINE__, "CreateHardLinkW", buf, "SUCCESS", msg);
	return return_value;
}


/**
* void WINAPI FatalAppExit(UINT uAction, LPCTSTR lpMessageText)
* 메시지 박스 보여주고 박스 닫힐 때 실행창 종료.
* @author : 손나영
* 
* @param uAction 0이어야 함.
* @param lpMessageText 메시지 박스에 보여줄 내용.
* @return 없음.
*/

BOOL test_FatalAppExitA(){ 
	
	#ifdef OQADBGPRINT
	printf("test_FatalAppExitA\n");
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
	wresult(__FILE__, __LINE__, "FatalAppExitA", buf, "SUCCESS", msg);
	isManual = FALSE;

	return result;
}


/**
* DWORD WINAPI GetPriorityClass(HANDLE hProcess)
* 특정 프로세스의 priority class 가져옴. 프로세스의 각 스레드의 우선 순위 값과 함께 기본 우선 순위 수준을 결정.
* @author : 손나영
*
* @param hProcess 프로세스에 대한 핸들. PROCESS_QUERY_INFORMATION 또는 PROCESS_QUERY_LIMITED_INFORMATION 액세스 권한 필요
* @return 지정된 프로세스의 우선 순위 클랙스.
*/

BOOL test_GetPriorityClass(){

	#ifdef OQADBGPRINT
	printf("test_GetPriorityClass \n");
	#endif

	int wresult_value = 0;
	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	DWORD result = 0;

	// GetCurrentProcess 함수로 프로세스 핸들 가져옴.
	HANDLE hProcess = GetCurrentProcess();
	
	result = GetPriorityClass(hProcess);

	if(result != 0){ //성공 
		wresult_value=1;
		strcpy(msg, "GetPriorityClass : SUCCESS");
	}else // 실패
		strcpy(msg, "FAIL");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "GetPriorityClass", buf, "1", msg);

	return result;
}


/**
* UINT WINAPI GetProfileInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, INT nDefault)
* Win.ini 파일의 특정 섹션 속 키로부터 integer 가져옴. 16비트 전용 함수이고, 응용프로그램이 레지스트리에 초기화 정보를 저장해야 함.
* @author : 손나영
*
* @param lpAppName 키 이름을 포함하는 섹션명
* @param lpKeyName 값을 가져올 키의 이름. 문자열 형식. 문자열 변환해서 정수 반환.
* @param nDefault 초기화 파일에서 키 이름을 찾을 수 없는 경우 반환할 기본값
* @return Win.ini의 키 이름 뒤에 오는 문자열에 해당하는 정수. 키를 찾을 수 없으면 반환값이 기본 값. 키 값이 0보다 작으면 0으로 반환.
*/

BOOL test_GetProfileIntW(){   //GetProfileInt 정수 반환

	#ifdef OQADBGPRINT
	printf("test_GetProfileIntW\n");
	#endif

	HKEY newKey;

	RegCreateKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL);

	UINT result = GetProfileIntW(L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", L"Left", 0);


	// isdigit(판별할 문자)
	if(isdigit(result) != 0)
		//성공일 경우
		wresult(__FILE__, __LINE__, "GetProfileIntW", "1", "1", "GetProfileIntW : PASS");  
	else
		//실패일 경우
		wresult(__FILE__, __LINE__, "GetProfileIntW", "0", "1", "GetProfileIntW : FAIL");  
	return result;
}


/**
* UINT SetHandleCount(UINT uNumber)
* 처리할 수 있는 파일 핸들의 수를 설정. Win32에서는 default가 20인데, SetHandleCount 쓰면 225개까지 가능.
* @author : 손나영
*
* @param uNumber 처리할 수 있는 파일 핸들의 수.
* @return 실제로 사용할 수 있는 파일의 핸들 수.
*/

BOOL test_SetHandleCount(){

	#ifdef OQADBGPRINT
	printf("test_SetHandleCount\n");
	#endif
	
	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];
	int wresult_value=0;

	UINT result = 0;
	BOOL return_value = FALSE;

	// Win32에서는 default가 20인데, SetHandleCount 쓰면 225개까지 가능.
	result = SetHandleCount(225);

	if(result != 0){
		wresult_value = 1;
		return_value = TRUE;
		sprintf(msg, " SetHandleCount() : SUCCESS \n\n 실제 사용할 수 있는 파일의 핸들 수 : %d", result);
	}else
		strcpy(msg, " SetHandleCount() : FAIL");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "SetHandleCount", buf, "1", msg);

	return return_value;
}

/**
* BOOL WINAPI SetInformationJobObject(HANDLE hJob, JOBOBJECTINFOCLASS JobObjectInfoClass, LPVOID lpJobObjectInfo, DWORD cbJobObjectInfoLength)
* job object의 제한을 설정
* @author : 손나영
*
* @param hJob job의 제한을 설정하기 위한 핸들. CreateJobObject이나 OpenJobObject 함수가 이 핸들을 리턴함. JOB_OBJECT_SET_ATTRIBUTES권한 필수.
* @param JobObjectInfoClass 제한을 설정할 정보 클래스. 13가지.
* @param lpJobObjectInfo job을 설정하기 위한 제한 또는 job. 데이터의 포맷은 JobObjectInfoClass의 값에 의존.
* @param cbJobObjectInfoLength 설정될 job 정보의 크기. 바이트 단위.
* @return  제한 설정 성공/실패 여부.
*/

/**
* Job Object : 명명 가능하고 보안을 적용할 수 있고 또 공유할 수 있는 커널 객체이다.  
* 하나 또는 그 이상의 프로세스들을 묶어 관리할 수 있다.
* 잡 객체의 기본적인 기능은 일련의 프로세스들을 하나의 단위로 묶어 관리할 수 있게 해주는 것이다.
* 기본적으로 잡 객체와 프로세스의 관계는 끊어질 수 없으며 관계가 맺어진 프로세스에 의해 생성된 모든 프로세스와 자손들은 동일한 잡 객체와 연관된다.
*/

BOOL test_SetInformationJobObject(){

	#ifdef OQADBGPRINT
	printf("test_SetInformationJobObject\n");
	#endif

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	BOOL result = FALSE;

	// CreateJobObject의 리턴 값이 SetInformationJobObject의 핸들이 됨
	HANDLE hJob = CreateJobObject(NULL, L"job");
	JOBOBJECTINFOCLASS JobObjectInfoClass = JobObjectExtendedLimitInformation;

	// 기본 제한 사항을 설정
	JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli = { 0 };
	jeli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;

	result = SetInformationJobObject(hJob, JobObjectInfoClass, &jeli, sizeof(jeli));

	if(result != FALSE){
		strcpy(buf, "SUCCESS");
		strcpy(msg, "SetInformationJobObject() : SUCCESS");  

	}else{
		strcpy(msg, "SetInformationJobObject() : FAIL");  
	}

	wresult(__FILE__, __LINE__, "SetInformationJobObject", buf, "SUCCESS", msg);  
	return result;
}


/**
* BOOL WINAPI SetPriorityClass(HANDLE hProcess, DWORD  dwPriorityClass)
* 특정 프로세스의 priority class 설정. 프로세스의 각 스레드의 우선 순위 값과 함께 기본 우선 순위 수준을 결정.
* @author : 손나영
*
* @param hProcess 프로세스 핸들. PROCESS_SET_INFORMATION 권한 필수. 
* @param dwPriorityClass 프로세스 우선 순위 클래스. 8가지.
* @return 설정 성공/실패 여부.
*/

BOOL test_SetPriorityClass(){

	#ifdef OQADBGPRINT
	printf("test_SetPriorityClass\n");
	#endif

	int wresult_value=0;
	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	BOOL result = FALSE;
	BOOL return_value = FALSE;
	HANDLE hProcess = GetCurrentProcess();

	// PROCESS_MODE_BACKGROUND_BEGIN : Begin background processing mode.
	// This value can be specified only if hProcess is a handle to the current process. 
	// The function fails if the process is already in background processing mode.
	result = SetPriorityClass(hProcess, PROCESS_MODE_BACKGROUND_BEGIN);
	
	if(result != FALSE){
		wresult_value=1;
		return_value = TRUE;
		strcpy(msg, "SetPriorityClass : SUCCESS");
	}else
		strcpy(msg, "FAIL");

	sprintf(buf, "%d", wresult_value);

	wresult(__FILE__, __LINE__, "SetPriorityClass", buf, "1", msg);
	return return_value;
}


/**

INI 파일

INI파일에서 정보를 쓸 때는 WritePrivateProfileString



*/