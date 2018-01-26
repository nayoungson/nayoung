#include "TestFunction.h"

/**
* BOOL WINAPI Beep(DWORD dwFreq, DWORD dwDuration)
* beep�� ���.
* @author : �ճ���
*
* @param dwFreq ���ļ�.
* @param dwDuration ���ӽð�(ms).
* @return beep �� ��� ����/���� ����.
*/
BOOL test_Beep(){

	#ifdef OQADBGPRINT
	printf("test_Beep\n");
	#endif

	int wresult_value=0;
	char msg[BUFSIZ];
	char buf[BUFSIZ] = "FAIL";

	LSTATUS result; 

	DWORD dwFreq = 750;	//���ļ�
	DWORD dwDuration = 300;	//���ӽð�

	result = Beep(dwFreq, dwDuration);

	if(result != FALSE){ 
		sprintf(msg, " Beep() : SUCCESS \n\n ���� ��ġ�� ���� beep�� ����� Ȯ���Ͻʽÿ�");
		strcpy(buf, "SUCCESS");

	}else{
		strcpy(msg, " Beep : FAIL");
	}
	
	wresult(__FILE__, __LINE__, "Beep", buf, "SUCCESS", msg);

	return result;
}


/*
* BOOL WINAPI CreateHardLink(LPCTSTR lpFileName, LPCTSTR lpExistingFileName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
* �����ϴ� ���� - �� ���� ������ �ϵ� ��ũ ����.
* @author : �ճ���
*
* @param lpFileName �� ���ϸ�.
* @param lpExistingFileName �����ϴ� ���ϸ�.
* @param lpSecurityAttributes NULL�� ����.
* @return �� ���� ���� ����/���� ����
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

	// Delete���� ���� ���¿��� �ٽ� CreateHardLinkW�� �����ϸ� FAIL��. �ݵ�� �����ؾ� ��.
	DeleteFile(L"�ճ���\\test_CreateHardLinkW.link"); 
	DeleteFile(L"�ճ���\\test_CreateHardLinkW.txt");

	// ���� �����ؼ� hFile�� ����
	hFile = CreateFile(L"�ճ���\\test_CreateHardLinkW.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// hFile�� �� ������ ���� ���Ϸ� �ΰ�, �̸� ���� �� ����(.link) ����
	result = CreateHardLinkW(L"�ճ���\\test_CreateHardLinkW.link", L"�ճ���\\test_CreateHardLinkW.txt", NULL);

	if(result != FALSE){ // ���� 
		sprintf(msg, " CreateHardLinkW() : SUCCESS \n\n CreateHardLinkW ���� \n(����ؼ� CreateHardLinkW ������ ���� ������ ������ �����մϴ�.)");
		strcpy(buf, "SUCCESS");

	}else{ //����
		strcpy(msg, " CreateHardLinkW() : FAIL \n\n ���� ���� \n(������ �������� �����ߴ���, ��ΰ� �ùٸ��� Ȯ���Ͻʽÿ�.)");
	}

	//�ݵ�� �ڵ� �ݾ���� ��
	CloseHandle(hFile);

	//���� ������ ���� ����
	DeleteFile(L"�ճ���\\test_CreateHardLinkW.link"); //Delete���� ���� ���¿��� �ٽ� CreateHardLinkW�� �����ϸ� FAIL��. �ݵ�� �����ؾ� ��.
	DeleteFile(L"�ճ���\\test_CreateHardLinkW.txt");

	wresult(__FILE__, __LINE__, "CreateHardLinkW", buf, "SUCCESS", msg);
	return result;

	// author ����� �� C:\Users\NAYOUNG\Documents\Visual Studio 2012\Projects\API_OS1nayoung_2\API_OS1nayoung_2\�ճ���
}

/**
* HANDLE WINAPI CreateJobObject(LPSECURITY_ATTRIBUTES lpJobAttributes, LPCTSTR lpName)
* job object�� ���� �Ǵ� ����. ���� �� ��� 0���� �ʱ�ȭ + ��Ȱ�� + �������μ��� ���� ����.
* @author : �ճ���
*
* @param lpJobAttributes SECURITY_ATTRIBUTES ����ü ������. NULL�̸� dafault ���� ���� + �ڵ� ��� �Ұ�.
* @param lpName job object �̸�. NULL�̸� Ư�� �̸� ���� ����.
* @return job object�� ���� �ڵ�. �ڵ��� JOB_OBJECT_ALL_ACCESS ������ ����.
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

	if(result != NULL){ // ���� �Ǵ� ���� ����
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
* �޽��� �ڽ� �����ְ� �ڽ� ���� �� ����â ����.
* @author : �ճ���
* 
* @param uAction 0�̾�� ��.
* @param lpMessageText �޽��� �ڽ��� ������ ����.
* @return ����.
*/

BOOL test_FatalAppExitA(){ 
	
	#ifdef OQADBGPRINT
	printf("test_FatalAppExitA\n");
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
	wresult(__FILE__, __LINE__, "FatalAppExitA", buf, "SUCCESS", msg);
	isManual = FALSE;

	return result;
}


/**
* DWORD WINAPI GetPriorityClass(HANDLE hProcess)
* Ư�� ���μ����� priority class ������. ���μ����� �� �������� �켱 ���� ���� �Բ� �⺻ �켱 ���� ������ ����.
* @author : �ճ���
*
* @param hProcess ���μ����� ���� �ڵ�. PROCESS_QUERY_INFORMATION �Ǵ� PROCESS_QUERY_LIMITED_INFORMATION �׼��� ���� �ʿ�
* @return ������ ���μ����� �켱 ���� Ŭ����.
*/

BOOL test_GetPriorityClass(){

	#ifdef OQADBGPRINT
	printf("test_GetPriorityClass \n");
	#endif

	int wresult_value = 0;
	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	DWORD result = 0;

	// GetCurrentProcess �Լ��� ���μ��� �ڵ� ������.
	HANDLE hProcess = GetCurrentProcess();
	
	result = GetPriorityClass(hProcess);

	if(result != 0){ //���� 
		wresult_value=1;
		strcpy(msg, "GetPriorityClass : SUCCESS");
	}else // ����
		strcpy(msg, "FAIL");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "GetPriorityClass", buf, "1", msg);

	return result;
}


/**
* UINT WINAPI GetProfileInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, INT nDefault)
* Win.ini ������ Ư�� ���� �� Ű�κ��� integer ������. 16��Ʈ ���� �Լ��̰�, �������α׷��� ������Ʈ���� �ʱ�ȭ ������ �����ؾ� ��.
* @author : �ճ���
*
* @param lpAppName Ű �̸��� �����ϴ� ���Ǹ�
* @param lpKeyName ���� ������ Ű�� �̸�. ���ڿ� ����. ���ڿ� ��ȯ�ؼ� ���� ��ȯ.
* @param nDefault �ʱ�ȭ ���Ͽ��� Ű �̸��� ã�� �� ���� ��� ��ȯ�� �⺻��
* @return Win.ini�� Ű �̸� �ڿ� ���� ���ڿ��� �ش��ϴ� ����. Ű�� ã�� �� ������ ��ȯ���� �⺻ ��. Ű ���� 0���� ������ 0���� ��ȯ.
*/

BOOL test_GetProfileIntW(){   //GetProfileInt ���� ��ȯ

	#ifdef OQADBGPRINT
	printf("test_GetProfileIntW\n");
	#endif

	HKEY newKey;

	RegCreateKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL);

	UINT result = GetProfileIntW(L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", L"Left", 0);


	// isdigit(�Ǻ��� ����)
	if(isdigit(result) != 0)
		//������ ���
		wresult(__FILE__, __LINE__, "GetProfileIntW", "1", "1", "GetProfileIntW : PASS");  
	else
		//������ ���
		wresult(__FILE__, __LINE__, "GetProfileIntW", "0", "1", "GetProfileIntW : FAIL");  
	return result;
}


/**
* UINT SetHandleCount(UINT uNumber)
* ó���� �� �ִ� ���� �ڵ��� ���� ����. Win32������ default�� 20�ε�, SetHandleCount ���� 225������ ����.
* @author : �ճ���
*
* @param uNumber ó���� �� �ִ� ���� �ڵ��� ��.
* @return ������ ����� �� �ִ� ������ �ڵ� ��.
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

	// Win32������ default�� 20�ε�, SetHandleCount ���� 225������ ����.
	result = SetHandleCount(225);

	if(result != 0){
		wresult_value = 1;
		return_value = TRUE;
		sprintf(msg, " SetHandleCount() : SUCCESS \n\n ���� ����� �� �ִ� ������ �ڵ� �� : %d", result);
	}else
		strcpy(msg, " SetHandleCount() : FAIL");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "SetHandleCount", buf, "1", msg);

	return return_value;
}

/**
* BOOL WINAPI SetInformationJobObject(HANDLE hJob, JOBOBJECTINFOCLASS JobObjectInfoClass, LPVOID lpJobObjectInfo, DWORD cbJobObjectInfoLength)
* job object�� ������ ����
* @author : �ճ���
*
* @param hJob job�� ������ �����ϱ� ���� �ڵ�. CreateJobObject�̳� OpenJobObject �Լ��� �� �ڵ��� ������. JOB_OBJECT_SET_ATTRIBUTES���� �ʼ�.
* @param JobObjectInfoClass ������ ������ ���� Ŭ����. 13����.
* @param lpJobObjectInfo job�� �����ϱ� ���� ���� �Ǵ� job. �������� ������ JobObjectInfoClass�� ���� ����.
* @param cbJobObjectInfoLength ������ job ������ ũ��. ����Ʈ ����.
* @return  ���� ���� ����/���� ����.
*/

/**
* Job Object : ��� �����ϰ� ������ ������ �� �ְ� �� ������ �� �ִ� Ŀ�� ��ü�̴�.  
* �ϳ� �Ǵ� �� �̻��� ���μ������� ���� ������ �� �ִ�.
* �� ��ü�� �⺻���� ����� �Ϸ��� ���μ������� �ϳ��� ������ ���� ������ �� �ְ� ���ִ� ���̴�.
* �⺻������ �� ��ü�� ���μ����� ����� ������ �� ������ ���谡 �ξ��� ���μ����� ���� ������ ��� ���μ����� �ڼյ��� ������ �� ��ü�� �����ȴ�.
*/

BOOL test_SetInformationJobObject(){

	#ifdef OQADBGPRINT
	printf("test_SetInformationJobObject\n");
	#endif

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	BOOL result = FALSE;

	// CreateJobObject�� ���� ���� SetInformationJobObject�� �ڵ��� ��
	HANDLE hJob = CreateJobObject(NULL, L"job");
	JOBOBJECTINFOCLASS JobObjectInfoClass = JobObjectExtendedLimitInformation;

	// �⺻ ���� ������ ����
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
* Ư�� ���μ����� priority class ����. ���μ����� �� �������� �켱 ���� ���� �Բ� �⺻ �켱 ���� ������ ����.
* @author : �ճ���
*
* @param hProcess ���μ��� �ڵ�. PROCESS_SET_INFORMATION ���� �ʼ�. 
* @param dwPriorityClass ���μ��� �켱 ���� Ŭ����. 8����.
* @return ���� ����/���� ����.
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

INI ����

INI���Ͽ��� ������ �� ���� WritePrivateProfileString



*/