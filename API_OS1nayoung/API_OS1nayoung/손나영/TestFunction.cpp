#include "TestFunction.h"


BOOL test_Beep(){
	LSTATUS result; 

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

#ifdef OQADBGPRINT
	printf("test_Beep\n");
#endif
	result = Beep(750, 300);

	if(result != ERROR){
		strcpy(meg, " Beep \n\n 사운드 장치를 통해 beep음 출력을 확인하십시오");
	}else
		strcpy(meg, " Beep : FAIL");

	wresult(__FILE__, __LINE__, "Beep", _itoa(result, buf, 10), _itoa(ERROR_SUCCESS, buf, 10), meg);

	return true;
}


BOOL test_CreateHardLinkW(){

	HWND hWnd = 0;
	HANDLE hFile = NULL;

	int wresult_value=0;
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_CreateHardLinkW\n");
	#endif

	DeleteFile(L"손나영\\test_CreateHardLinkW.link"); //Delete하지 않은 상태에서 다시 CreateHardLinkW를 진행하면 FAIL됨. 반드시 삭제해야 함.
	DeleteFile(L"손나영\\test_CreateHardLinkW.txt");

	hFile = CreateFile(L"손나영\\test_CreateHardLinkW.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	BOOL result = CreateHardLinkW(L"손나영\\test_CreateHardLinkW.link", L"손나영\\test_CreateHardLinkW.txt", NULL);

	if(result){
		strcpy(meg, " CreateHardLinkW() : PASS \n\n CreateHardLinkW 성공 \n(계속해서 CreateHardLinkW 실행을 위해 생성한 파일을 삭제합니다.)");
		wresult_value=1;

	}else{
		strcpy(meg, " CreateHardLinkW() : FAIL \n\n 생성 실패 \n(관리자 권한으로 실행했는지, 경로가 올바른지 확인하십시오.)");
	}

	CloseHandle(hFile);
	Sleep(3000);

	DeleteFile(L"손나영\\test_CreateHardLinkW.link"); //Delete하지 않은 상태에서 다시 CreateHardLinkW를 진행하면 FAIL됨. 반드시 삭제해야 함.
	DeleteFile(L"손나영\\test_CreateHardLinkW.txt");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "CreateHardLinkW", buf, "1", meg);

	return TRUE;
}


/** PathFileExists 썼다가 → gtest 에러 나서 → 빼고 무조건 delete + handle 반환 반영. 위 코드.
BOOL test_CreateHardLinkW(){

	BOOL FileExists_result;  //CreateHarkLink 하기 전에 test.txt(복사 파일) 있는지 확인
	BOOL FileExists_result2; // CreateHarkLink 수행 후 test.txt(복사 파일)  있는지 확인
	HWND hWnd = 0;

	int wresult_value=0;
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_CreateHardLinkW\n");
	#endif

	FileExists_result = PathFileExists(L"손나영\\test.txt"); //존재한다면 PathFileExists 함수가 TRUE를 반환. 

	if(FileExists_result == TRUE){

		DeleteFile(L"손나영\\test.txt");
	#ifdef OQADBG
		MessageBox(hWnd, L"파일이 존재하여 삭제했습니다. \nCreateHardLinkW 함수를 진행합니다.", L"기존 파일 삭제", MB_OK);
	#endif
	}
	Sleep(500);

	BOOL result = CreateHardLinkW(L"손나영\\test.txt", L"손나영\\dbg_log.dat", NULL);

	if(result){
		strcpy(meg, " CreateHardLinkW() : PASS \n\n CreateHardLinkW 성공 \n(계속해서 CreateHardLinkW 실행을 위해 생성한 파일을 삭제합니다.)");
		wresult_value=1;

		DeleteFile(L"손나영\\test.txt"); //Delete하지 않은 상태에서 다시 CreateHardLinkW를 진행하면 FAIL됨. 반드시 삭제해야 함.

		Sleep(500);

		// 파일이 정상적으로 삭제되었는지를 확인
		FileExists_result2 = PathFileExists(L"손나영\\test.txt"); //존재한다면 PathFileExists 함수가 TRUE를 반환. 

		if(FileExists_result2 == TRUE){

	#ifdef OQADBG
			MessageBox(hWnd, L"파일이 아직 존재합니다. \nCreateHardLinkW 함수로 생성한 파일을 삭제하십시오.", L"삭제 실패", MB_OK);
	#endif

		}else{		//파일이 존재하지 않는 경우

	#ifdef OQADBG
			MessageBox(hWnd, L"파일 삭제 성공. \nCreateHardLinkW 를 재진행 시킬 수 있습니다.", L"삭제 성공", MB_OK);
	#endif
		}
	}else{
		strcpy(meg, " CreateHardLinkW() : FAIL \n\n 생성 실패 \n(관리자 권한으로 실행했는지, 경로가 올바른지 확인하십시오.)");
	}
	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "CreateHardLinkW", buf, "1", meg);

	return true;
}
*/

/**
job object를 생성하거나 오픈함
생성되면 all 0으로 초기화 + 비활성 + 관련 프로세스 없는 상태

*/

BOOL test_CreateJobObjectW(){
	HANDLE CreJobObject = CreateJobObjectW(NULL, L"CreateJob_Object");
#ifdef OQADBGPRINT
	printf("test_CreateJobObjectW\n");
#endif
	if(CreJobObject){
		wresult(__FILE__, __LINE__, "CreateJobObjectW", "1", "1", "CreateJobObjectW : PASS");  
	}else{
		wresult(__FILE__, __LINE__, "CreateJobObjectW", "0", "1", "CreateJobObjectW : FAIL");  
	}
	return true;

}



/**
Job Object : 명명 가능하고 보안을 적용할 수 있고 또 공유할 수 있는 커널 객체이다.  
하나 또는 그 이상의 프로세스들을 묶어 관리할 수 있다.
잡 객체의 기본적인 기능은 일련의 프로세스들을 하나의 단위로 묶어 관리할 수 있게 해주는 것이다.
기본적으로 잡 객체와 프로세스의 관계는 끊어질 수 없으며 관계가 맺어진 프로세스에 의해 생성된 모든 프로세스와 자손들은 동일한 잡 객체와 연관된다.
SetInformationJobObject 함수 : job object 제한사항을 설정
*/

BOOL test_SetInformationJobObject(){
	// CreateJobObject의 리턴 값이 SetInformationJobObject의 핸들이 됨
	HANDLE hJob = CreateJobObject(NULL, L"job");

	BOOL result;
#ifdef OQADBGPRINT
	printf("test_SetInformationJobObject\n");
#endif
	// 기본 제한 사항을 설정
	JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli = { 0 };
	jeli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;

	result = SetInformationJobObject(hJob, JobObjectExtendedLimitInformation, &jeli, sizeof(jeli));

	if(result){
		wresult(__FILE__, __LINE__, "SetInformationJobObject", "1", "1", "SetInformationJobObject : PASS");  
	}else{
		wresult(__FILE__, __LINE__, "SetInformationJobObject", "0", "1", "SetInformationJobObject : FAIL");  
	}
	return true;
}

/**
BOOL Search_Process(){

}
*/


/**
메시지 하나 띄우고 프로그램을 강제 종료해버림 
*/

BOOL test_FatalAppExitA(){ // 에러 핸들링. Displays a message box and terminates the application when the message box is closed.
	//WinExec("C:\\Users\\Tmax\\Desktop\\test\\FatalAppExit_exe_file_test.exe", SW_SHOW);
	#ifdef OQADBGPRINT
	printf("test_FatalAppExitA\n");
	#endif
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

BOOL test_GetProfileIntW(){   //GetProfileInt 정수 반환
	HKEY newKey;

	#ifdef OQADBGPRINT
	printf("test_GetProfileIntW\n");
	#endif
	RegCreateKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL);

	UINT result = GetProfileIntW(L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", L"Left", 0);

	if(result == 0)
		//성공일 경우
		wresult(__FILE__, __LINE__, "GetProfileIntW", "1", "1", "GetProfileIntW : PASS");  
	else
		//실패일 경우
		wresult(__FILE__, __LINE__, "GetProfileIntW", "0", "1", "GetProfileIntW : FAIL");  
	return true;
}





BOOL test_SetHandleCount(){
	UINT result = 0;

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	printf("test_SetHandleCount\n");
	#endif

	result = SetHandleCount(0xabcd);

	if(result != ERROR){
		strcpy(meg, " SetHandleCount : PASS");
	}else
		strcpy(meg, " SetHandleCount : FAIL");

	wresult(__FILE__, __LINE__, "SetHandleCount", (char *)_itoa(result, buf, 10), (char *)_itoa(result, buf, 10), meg);

	return true;
}


/** debugger execution control 전송.
	application 실행 도중 갑작스럽게 중단하는 function.
	메모리에 남아있지는 않음.
	보통 debug를 위해 사용됨.	*/
//-------------------------------------------------------> exe파일 새로 만들기
/**
BOOL test_FatalExit(){
	FatalExit(-1);

	return true;
}
*/




BOOL test_SetPriorityClass(){
	HANDLE hProcess = GetCurrentProcess();

	BOOL result;

	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_SetPriorityClass\n");
	#endif

	result = SetPriorityClass(hProcess, NORMAL_PRIORITY_CLASS);
	
	if(result)
		strcpy(meg, "SetPriorityClass : PASS \n\n 첫 번째 인자 : GetCurrentProcess() 리턴 값 \n Option : NORMAL_PRIORITY_CLASS ");
	else
		strcpy(meg, "FAIL");
	wresult(__FILE__, __LINE__, "SetPriorityClass", "1", "1", meg);

	return true;
}

//SetPriorityClass() 후에 진행
BOOL test_GetPriorityClass(){
	HANDLE hProcess = GetCurrentProcess();
	LSTATUS result;

	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_GetPriorityClass\n");
	#endif

	result = GetPriorityClass(hProcess);

	if(result)
		strcpy(meg, "GetPriorityClass : PASS");
	else
		strcpy(meg, "FAIL");
	wresult(__FILE__, __LINE__, "GetPriorityClass", "1", "1", meg);
	return true;
}