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
		strcpy(meg, " Beep \n\n ���� ��ġ�� ���� beep�� ����� Ȯ���Ͻʽÿ�");
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

	DeleteFile(L"�ճ���\\test_CreateHardLinkW.link"); //Delete���� ���� ���¿��� �ٽ� CreateHardLinkW�� �����ϸ� FAIL��. �ݵ�� �����ؾ� ��.
	DeleteFile(L"�ճ���\\test_CreateHardLinkW.txt");

	hFile = CreateFile(L"�ճ���\\test_CreateHardLinkW.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	BOOL result = CreateHardLinkW(L"�ճ���\\test_CreateHardLinkW.link", L"�ճ���\\test_CreateHardLinkW.txt", NULL);

	if(result){
		strcpy(meg, " CreateHardLinkW() : PASS \n\n CreateHardLinkW ���� \n(����ؼ� CreateHardLinkW ������ ���� ������ ������ �����մϴ�.)");
		wresult_value=1;

	}else{
		strcpy(meg, " CreateHardLinkW() : FAIL \n\n ���� ���� \n(������ �������� �����ߴ���, ��ΰ� �ùٸ��� Ȯ���Ͻʽÿ�.)");
	}

	CloseHandle(hFile);
	Sleep(3000);

	DeleteFile(L"�ճ���\\test_CreateHardLinkW.link"); //Delete���� ���� ���¿��� �ٽ� CreateHardLinkW�� �����ϸ� FAIL��. �ݵ�� �����ؾ� ��.
	DeleteFile(L"�ճ���\\test_CreateHardLinkW.txt");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "CreateHardLinkW", buf, "1", meg);

	return TRUE;
}


/** PathFileExists ��ٰ� �� gtest ���� ���� �� ���� ������ delete + handle ��ȯ �ݿ�. �� �ڵ�.
BOOL test_CreateHardLinkW(){

	BOOL FileExists_result;  //CreateHarkLink �ϱ� ���� test.txt(���� ����) �ִ��� Ȯ��
	BOOL FileExists_result2; // CreateHarkLink ���� �� test.txt(���� ����)  �ִ��� Ȯ��
	HWND hWnd = 0;

	int wresult_value=0;
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_CreateHardLinkW\n");
	#endif

	FileExists_result = PathFileExists(L"�ճ���\\test.txt"); //�����Ѵٸ� PathFileExists �Լ��� TRUE�� ��ȯ. 

	if(FileExists_result == TRUE){

		DeleteFile(L"�ճ���\\test.txt");
	#ifdef OQADBG
		MessageBox(hWnd, L"������ �����Ͽ� �����߽��ϴ�. \nCreateHardLinkW �Լ��� �����մϴ�.", L"���� ���� ����", MB_OK);
	#endif
	}
	Sleep(500);

	BOOL result = CreateHardLinkW(L"�ճ���\\test.txt", L"�ճ���\\dbg_log.dat", NULL);

	if(result){
		strcpy(meg, " CreateHardLinkW() : PASS \n\n CreateHardLinkW ���� \n(����ؼ� CreateHardLinkW ������ ���� ������ ������ �����մϴ�.)");
		wresult_value=1;

		DeleteFile(L"�ճ���\\test.txt"); //Delete���� ���� ���¿��� �ٽ� CreateHardLinkW�� �����ϸ� FAIL��. �ݵ�� �����ؾ� ��.

		Sleep(500);

		// ������ ���������� �����Ǿ������� Ȯ��
		FileExists_result2 = PathFileExists(L"�ճ���\\test.txt"); //�����Ѵٸ� PathFileExists �Լ��� TRUE�� ��ȯ. 

		if(FileExists_result2 == TRUE){

	#ifdef OQADBG
			MessageBox(hWnd, L"������ ���� �����մϴ�. \nCreateHardLinkW �Լ��� ������ ������ �����Ͻʽÿ�.", L"���� ����", MB_OK);
	#endif

		}else{		//������ �������� �ʴ� ���

	#ifdef OQADBG
			MessageBox(hWnd, L"���� ���� ����. \nCreateHardLinkW �� ������ ��ų �� �ֽ��ϴ�.", L"���� ����", MB_OK);
	#endif
		}
	}else{
		strcpy(meg, " CreateHardLinkW() : FAIL \n\n ���� ���� \n(������ �������� �����ߴ���, ��ΰ� �ùٸ��� Ȯ���Ͻʽÿ�.)");
	}
	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "CreateHardLinkW", buf, "1", meg);

	return true;
}
*/

/**
job object�� �����ϰų� ������
�����Ǹ� all 0���� �ʱ�ȭ + ��Ȱ�� + ���� ���μ��� ���� ����

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
Job Object : ��� �����ϰ� ������ ������ �� �ְ� �� ������ �� �ִ� Ŀ�� ��ü�̴�.  
�ϳ� �Ǵ� �� �̻��� ���μ������� ���� ������ �� �ִ�.
�� ��ü�� �⺻���� ����� �Ϸ��� ���μ������� �ϳ��� ������ ���� ������ �� �ְ� ���ִ� ���̴�.
�⺻������ �� ��ü�� ���μ����� ����� ������ �� ������ ���谡 �ξ��� ���μ����� ���� ������ ��� ���μ����� �ڼյ��� ������ �� ��ü�� �����ȴ�.
SetInformationJobObject �Լ� : job object ���ѻ����� ����
*/

BOOL test_SetInformationJobObject(){
	// CreateJobObject�� ���� ���� SetInformationJobObject�� �ڵ��� ��
	HANDLE hJob = CreateJobObject(NULL, L"job");

	BOOL result;
#ifdef OQADBGPRINT
	printf("test_SetInformationJobObject\n");
#endif
	// �⺻ ���� ������ ����
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
�޽��� �ϳ� ���� ���α׷��� ���� �����ع��� 
*/

BOOL test_FatalAppExitA(){ // ���� �ڵ鸵. Displays a message box and terminates the application when the message box is closed.
	//WinExec("C:\\Users\\Tmax\\Desktop\\test\\FatalAppExit_exe_file_test.exe", SW_SHOW);
	#ifdef OQADBGPRINT
	printf("test_FatalAppExitA\n");
	#endif
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

BOOL test_GetProfileIntW(){   //GetProfileInt ���� ��ȯ
	HKEY newKey;

	#ifdef OQADBGPRINT
	printf("test_GetProfileIntW\n");
	#endif
	RegCreateKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL);

	UINT result = GetProfileIntW(L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", L"Left", 0);

	if(result == 0)
		//������ ���
		wresult(__FILE__, __LINE__, "GetProfileIntW", "1", "1", "GetProfileIntW : PASS");  
	else
		//������ ���
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


/** debugger execution control ����.
	application ���� ���� ���۽����� �ߴ��ϴ� function.
	�޸𸮿� ���������� ����.
	���� debug�� ���� ����.	*/
//-------------------------------------------------------> exe���� ���� �����
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
		strcpy(meg, "SetPriorityClass : PASS \n\n ù ��° ���� : GetCurrentProcess() ���� �� \n Option : NORMAL_PRIORITY_CLASS ");
	else
		strcpy(meg, "FAIL");
	wresult(__FILE__, __LINE__, "SetPriorityClass", "1", "1", meg);

	return true;
}

//SetPriorityClass() �Ŀ� ����
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