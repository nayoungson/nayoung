#include "TestRegistryPPT.h"


BOOL test_RegLoadKeyA(){

	HWND hWnd =0;
	HKEY newKey;
	LONG result;

	//HKEY hKey = HKEY_LOCAL_MACHINE;
	HKEY hKey = HKEY_CURRENT_USER;
	//HKEY hKey = HKEY_USERS;
	LPSTR lpSubKey = "SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position";
	LPSTR lpFile = "C:\\Users\\Tmax\\Desktop\\test\\dbg_log.dat";

	int wresult_value=0;
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

#ifdef OQADBGPRINT
	printf("test_RegLoadKeyA  \n");
#endif

	printf("a");
	result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",&newKey);

	if(result == ERROR_SUCCESS){
		printf("create ����");
		result = RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);
		printf("open ����");
		//create �� open �ϰ� ���� load�۾�
		result = RegLoadKeyA(hKey, lpSubKey, lpFile);
		printf("load��");
		if(result==ERROR_SUCCESS){
			strcpy(meg, "RegLoadKeyA() : PASS");
			wresult_value=1;
		}else{
			strcpy(meg, "RegLoadKeyA() : FAIL");

		}
	}

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegLoadKeyA", buf, "1", meg);

	return true;
}


BOOL test_RegUnLoadKeyA(){
	
	int wresult_value=0;
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	LONG result;
	//HKEY hKey = HKEY_LOCAL_MACHINE;
	HKEY hKey = HKEY_CURRENT_USER;
	LPSTR lpSubKey = "SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position";
	LPSTR lpFile = "C:\\Users\\Tmax\\Desktop\\test\\dbg_log.dat";
	
	RegLoadKeyA(hKey, lpSubKey, lpFile);

	result = RegUnLoadKeyA(hKey, lpSubKey);

	if(result == ERROR_SUCCESS){
		wresult_value=1;
		strcpy(meg, "RegUnLoadKeyA() : SUCCESS");
	}else
		strcpy(meg, "RegUnLoadKeyA() : FAIL");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegUnLoadKeyA", buf, "1", meg);

	return true;
}

BOOL test_RegUnLoadKeyW(){
	
	int wresult_value=0;
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	LONG result;
	//HKEY hKey = HKEY_LOCAL_MACHINE;
	HKEY hKey = HKEY_CURRENT_USER;
	LPCTSTR lpSubKey = L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position";
	LPCTSTR lpFile = TEXT("C:\\Users\\Tmax\\Desktop\\test\\dbg_log.dat");
	
	//RegUnLoadKeyW(hKey, lpSubKey, lpFile);

	result = RegUnLoadKeyW(hKey, lpSubKey);

	if(result == ERROR_SUCCESS){
		wresult_value=1;
		strcpy(meg, "RegUnLoadKeyA() : SUCCESS");
	}else
		strcpy(meg, "RegUnLoadKeyA() : FAIL");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegUnLoadKeyA", buf, "1", meg);

	return true;
}



/**
������Ʈ�� Ű Ʈ���� �����մϴ�.
���� �� ���� �� ������ ������ ��ģ �� ���� �������� Ű�� ����� �����Ǿ����� Ȯ���մϴ�.
���� �� Ű�� Ŭ������ �� ���� �޽��� �ڽ��� ȣ��Ǹ� �����Դϴ�.
*/
BOOL test_RegDeleteTreeW(){

	HKEY newKey;
	LSTATUS result;
	HKEY hKey = HKEY_CURRENT_USER;

	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_RegDeleteTreeW  \n");
	#endif

	result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest\\Position",&newKey);

	if(result == ERROR_SUCCESS){
		//printf("create ����");
		result = RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);
		if(result == ERROR_SUCCESS){
			//printf("open ����");
			result = RegDeleteTreeW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest");
			if(result == ERROR_SUCCESS){
				//printf("delete ����");
				result = RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);
				if(result != ERROR_SUCCESS){
					//printf("open �ȵǴϱ� ����");
					strcpy(meg, "RegDeleteTree() : SUCCESS");
				}else
					strcpy(meg, "RegDeleteTree() : FAIL");
			}else
				strcpy(meg, "RegDeleteTree() : FAIL");
		}else
			strcpy(meg, "RegOpenKeyEx() : FAIL");
	}else
		strcpy(meg, "RegCreateKey() : FAIL");
	
	wresult(__FILE__, __LINE__, "RegDeleteTree", meg, "RegDeleteTree() : SUCCESS", meg);
	return true;
}

BOOL test_RegEnumKeyExA(){
	HKEY key = HKEY_CURRENT_USER;
	char lpSubKey[MAX_PATH];
	char lpBuffer[MAX_PATH];
	DWORD i;
	LONG Result;
	DWORD Size;
	FILETIME FileTime;
	HWND hList = 0;
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_RegEnumKeyExW\n");
	#endif
	
	Result=ERROR_SUCCESS;
	#ifdef OQADBGPRINT
	printf("��RegEnumKeyExW() ��¡� \n");
	#endif

	for (i=0;Result==ERROR_SUCCESS;i++) {
		Size=MAX_PATH;
		Result=RegEnumKeyExA(key,i,lpSubKey,&Size,NULL,NULL,NULL,&FileTime);
		if (Result==ERROR_SUCCESS) {

			#ifdef OQADBGPRINT
			printf("K : %s \n",lpSubKey);
			#endif

			SendMessage(hList,LB_ADDSTRING,0,(LONG)lpBuffer);
		}
	}
	#ifdef OQADBGPRINT
	printf("\n");
	#endif

	strcpy(meg, " RegEnumKeyExW() : PASS \n\n �͹̳ο��� pluse_enum �� ����� Ȯ���Ͻʽÿ�.");
	wresult(__FILE__, __LINE__, "RegEnumKeyEx", "ERROR_SUCCESS", "ERROR_SUCCESS", meg);
	return true;
}

BOOL test_RegDisablePredefinedCacheEx(){
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_RegDisablePredefinedCacheEx \n");
	#endif

	if(RegDisablePredefinedCacheEx() == ERROR_SUCCESS)
		strcpy(meg, "RegDisablePredefinedCacheEx() : SUCCESS");	
	else 
		strcpy(meg, GetErrorMessage(" RegDisablePredefinedCacheEx() : FAIL \n\n Error Message :", GetLastError()));
	

	wresult(__FILE__, __LINE__, "RegDisablePredefinedCacheEx", meg, "RegDisablePredefinedCacheEx() : SUCCESS", meg);

	return true;
}

/**

BOOL test_RegOpenCurrentUser(){
	HKEY newKey;
	HKEY hKey = HKEY_CURRENT_USER;

	REGSAM samDesired = KEY_ALL_ACCESS ;
	PHKEY phkResult = NULL;

	RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest\\Position",&newKey);
	RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);

	RegOpenCurrentUser(samDesired, phkResult);


	//if(== ERROR_SUCCESS){
	
	RegCloseKey(newKey);

	return true;
}

*/


/**
	
	WER : Windows Error Reporting

	1. ������ event �߻�
	2. Windows�� WER ȣ��
	3. WER�� �����͸� �����ϰ� ������ �ۼ��ϸ� �ʿ��� ��� ����ڿ��� ���� ���� ���� �޽����� ǥ��
	4. WER�� ����ڰ� ������ ��� ������ Watson Server(microsoft)�� ����
	5. Watson ������ �߰� �����͸� ��û�ϸ� WER�� �����͸� �����ϰ� �ʿ��� ��� ����ڿ��� ���� ���θ� ���� �޽����� ǥ���մϴ�.
	6. ���� ���α׷��� ���� �� �ٽ� ������ ���� ��� �� ��� WER�� ��� �� �ݹ� �Լ��� �����ϸ鼭 �����Ͱ� ����Ǿ� Microsoft�� ���۵˴ϴ� (����ڰ� ���� �� ���).
	7. Microsoft���� ������ ���� ������ ����� ���ִ� ��� ����ڿ��� �˸��ϴ�.

*/

#define BUFFER 8192
BOOL test_RegGetValueW(){
	
	RECT rt;
	HKEY newKey;
	LONG result;
	DWORD BufferSize = BUFFER;

	char value[255];
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";
	int wresult_value = 0;

	#ifdef OQADBGPRINT
	printf("test_RegGetValueW\n");
	#endif

	/** Registry ���� */
	result = RegCreateKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL);
	if(result != ERROR_SUCCESS)
		strcpy(meg, " ������Ʈ�� CREATE ����");

	/** ������ Registry key�� value������ Left ���� */
	result = RegSetValueExW(newKey, L"Left",0,REG_DWORD,(LPBYTE)&rt.left,sizeof(LONG));
	if(result != ERROR_SUCCESS)
		strcpy(meg, " ������Ʈ�� SET ����");

	result = RegGetValueW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", L"Left", RRF_RT_REG_BINARY | RRF_RT_REG_DWORD, NULL, (LPDWORD)&value, &BufferSize);
	
	/** RegGetValueW ����, ���� ��� */ 
	if(result==ERROR_SUCCESS){
		wresult_value=1;
		strcpy(meg, " RegGetValueW : SUCCESS \n\n ");
	}else
		strcpy(meg, " RegGetValueW : FAIL");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegGetValueW", buf, "1", meg);
		
	return true;
}