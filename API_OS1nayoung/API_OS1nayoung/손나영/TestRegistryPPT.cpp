#include "TestRegistryPPT.h"

BOOL SetPrivilege(HANDLE hToken, LPCWSTR nameOfPrivilege,BOOL bEnablePrivilege){
	TOKEN_PRIVILEGES tp;
	LUID luid;

	if (!LookupPrivilegeValue(NULL,nameOfPrivilege,&luid)){
		printf("LookupPrivilegeValue error: %u\n", GetLastError());
		return FALSE;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;

	if (bEnablePrivilege)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;

	if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL)){
		printf("AdjustTokenPrivileges error: %u\n", GetLastError());
		return FALSE;
	}

	if(GetLastError() == ERROR_NOT_ALL_ASSIGNED){
		printf("The token does not have the specified privilege. \n");
		return FALSE;
	}

	return TRUE;
}

BOOL test_RegLoadKeyA(){


	#ifdef OQADBGPRINT
	printf("test_RegLoadKeyA \n");
	#endif

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";
	DWORD errorCode = 0;

    HANDLE proccessHandle = GetCurrentProcess();     // get the handle to the current proccess
    DWORD typeOfAccess = TOKEN_ADJUST_PRIVILEGES;   //  requiered to enable or disable the privilege
    HANDLE tokenHandle;                             //  handle to the opened access token

    HKEY hKey = HKEY_LOCAL_MACHINE;
    LPSTR subKeyName = "NAYOUNG_API_1";
    LPSTR pHive = "C:\\load4.reg";

    if (OpenProcessToken(proccessHandle, typeOfAccess, &tokenHandle)){
        // Enabling RESTORE and BACKUP privileges
        SetPrivilege(tokenHandle, SE_RESTORE_NAME , TRUE);
        SetPrivilege(tokenHandle, SE_BACKUP_NAME , TRUE);

    }else{
       // wprintf(L"Error getting the access token.\n");
    }

	//if((RegDeleteKeyExA(hKey, "\\NAYOUNG_API_PPT",KEY_WOW64_32KEY,0)) == ERROR_SUCCESS)
	//	printf("a");
	//else
	//	printf("b");
	////KEY �����ؾ���. ����.

	LONG loadKeyA = RegLoadKeyA(hKey, subKeyName, pHive);

    if (loadKeyA == FALSE){
		sprintf(meg, "RegLoadKeyA() : SUCCESS");
		strcpy(buf, "SUCCESS");
    }else{
		errorCode = GetLastError();
		printf("errorCode = %d\n", errorCode);
        strcpy(meg, GetErrorMessage(" RegLoadKeyA() : FAIL \n\n Error Message :", errorCode));
	}
	wresult(__FILE__, __LINE__, "RegLoadKeyA", buf, "SUCCESS", meg);

    return true;
}

BOOL test_RegLoadKeyW(){

	#ifdef OQADBGPRINT
	printf("test_RegLoadKeyW \n");
	#endif

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

    HANDLE proccessHandle = GetCurrentProcess();     // get the handle to the current proccess
    DWORD typeOfAccess = TOKEN_ADJUST_PRIVILEGES;   //  requiered to enable or disable the privilege
    HANDLE tokenHandle;                             //  handle to the opened access token

    HKEY hKey = HKEY_LOCAL_MACHINE;
    LPCWSTR subKeyName = L"NAYOUNG_API_1";
    LPCWSTR pHive = L"C:\\load44.reg";

    if (OpenProcessToken(proccessHandle, typeOfAccess, &tokenHandle)){
        // Enabling RESTORE and BACKUP privileges
        SetPrivilege(tokenHandle, SE_RESTORE_NAME , TRUE);
        SetPrivilege(tokenHandle, SE_BACKUP_NAME , TRUE);

    }else{
       // wprintf(L"Error getting the access token.\n");
    }
	
	//if((RegDeleteKeyExA(hKey, "\\NAYOUNG_API_PPT",KEY_WOW64_32KEY,0)) == ERROR_SUCCESS)
	//	printf("a");
	//else
	//	printf("b");
	////KEY �����ؾ���. ����.

	LONG loadKeyA = RegLoadKeyW(hKey, subKeyName, pHive);

    if (loadKeyA == FALSE){
		sprintf(meg, "RegLoadKeyW() : SUCCESS");
		strcpy(buf, "SUCCESS");
    }else{
        strcpy(meg, GetErrorMessage(" RegLoadKeyW() : FAIL \n\n Error Message :", GetLastError()));
	}
	wresult(__FILE__, __LINE__, "RegLoadKeyW", buf, "SUCCESS", meg);

    return true;
}

BOOL test_RegUnLoadKeyA(){

	#ifdef OQADBGPRINT
	printf("test_RegUnLoadKeyA \n");
	#endif

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

    HANDLE proccessHandle = GetCurrentProcess();     // get the handle to the current proccess
    DWORD typeOfAccess = TOKEN_ADJUST_PRIVILEGES;   //  requiered to enable or disable the privilege
    HANDLE tokenHandle;                             //  handle to the opened access token

    HKEY hKey = HKEY_LOCAL_MACHINE;
    LPSTR subKeyName = "NAYOUNG_API_PPT";
	LPSTR pHive = "C:\\test_RegUnLoadKeyA.reg";

	if (OpenProcessToken(proccessHandle, typeOfAccess, &tokenHandle)){
		// Enabling RESTORE and BACKUP privileges
		SetPrivilege(tokenHandle, SE_RESTORE_NAME, TRUE);
		SetPrivilege(tokenHandle, SE_BACKUP_NAME, TRUE);

	}else{
		//wprintf(L"Error getting the access token.\n");
	}

	LONG loadKeyA = RegLoadKeyA(hKey, subKeyName, pHive);

	if(loadKeyA == ERROR_SUCCESS){

		LONG unloadKeyA = RegUnLoadKeyA(hKey, subKeyName);

		if (unloadKeyA == ERROR_SUCCESS){
			sprintf(meg, "RegUnLoadKeyA() : SUCCESS");
			strcpy(buf, "SUCCESS");
		}else{
			strcpy(meg, GetErrorMessage(" RegUnLoadKeyA() : FAIL \n\n Error Message :", GetLastError()));
		}
	}else
		strcpy(meg, GetErrorMessage(" Registry Load�� �����߽��ϴ�. \n\n Load�� �� �ٽ� Unload�� �õ��� �ֽʽÿ�. \n �׷��� ������� �ʴ´ٸ� ������ ������ üũ�Ͻʽÿ�", GetLastError()));
	wresult(__FILE__, __LINE__, "RegUnLoadKeyA", buf, "SUCCESS", meg);

	return true;
}

BOOL test_RegUnLoadKeyW(){
	
	#ifdef OQADBGPRINT
	printf("test_RegUnLoadKeyW \n");
	#endif

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

    HANDLE proccessHandle = GetCurrentProcess();     // get the handle to the current proccess
    DWORD typeOfAccess = TOKEN_ADJUST_PRIVILEGES;   //  requiered to enable or disable the privilege
    HANDLE tokenHandle;                             //  handle to the opened access token

    HKEY hKey = HKEY_LOCAL_MACHINE;
    LPCWSTR subKeyName = L"NAYOUNG_API_PPT";
	 LPCWSTR pHive = L"C:\\test_RegUnLoadKeyW.reg";

	 if (OpenProcessToken(proccessHandle, typeOfAccess, &tokenHandle)){
		 // Enabling RESTORE and BACKUP privileges
		 SetPrivilege(tokenHandle, SE_RESTORE_NAME, TRUE);
		 SetPrivilege(tokenHandle, SE_BACKUP_NAME, TRUE);

	 }else{
		// wprintf(L"Error getting the access token.\n");
	 }

	 LONG loadKeyW = RegLoadKeyW(hKey, subKeyName, pHive);

	 if(loadKeyW == ERROR_SUCCESS){

		 LONG unloadKeyW = RegUnLoadKeyW(hKey, subKeyName);

		 if (unloadKeyW == ERROR_SUCCESS){
			 sprintf(meg, "RegUnLoadKeyW() : SUCCESS");
			 strcpy(buf, "SUCCESS");
		 }else{
			 strcpy(meg, GetErrorMessage(" RegUnLoadKeyW() : FAIL \n\n Error Message :", GetLastError()));
		 }
	 }else
		 strcpy(meg, GetErrorMessage(" Registry Load�� �����߽��ϴ�. \n\n Load�� �� �ٽ� Unload�� �õ��� �ֽʽÿ�. \n �׷��� ������� �ʴ´ٸ� ������ ������ üũ�Ͻʽÿ�", GetLastError()));
	 wresult(__FILE__, __LINE__, "RegUnLoadKeyW", buf, "SUCCESS", meg);

	 return true;
}

BOOL test_RegSaveKeyExA(){

	#ifdef OQADBGPRINT
	printf("test_RegSaveKeyExA \n");
	#endif

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	HKEY hKey = HKEY_CURRENT_USER;
	HKEY newKey;

    HANDLE proccessHandle = GetCurrentProcess();     // get the handle to the current proccess
    DWORD typeOfAccess = TOKEN_ADJUST_PRIVILEGES;   //  requiered to enable or disable the privilege
    HANDLE tokenHandle;                             //  handle to the opened access token
	
	LPSTR lpFile = "C:\\test_RegSaveKeyExA.reg";

	if (OpenProcessToken(proccessHandle, typeOfAccess, &tokenHandle)){
		// Enabling RESTORE and BACKUP privileges
		SetPrivilege(tokenHandle, SE_BACKUP_NAME, TRUE);

	}else{
	//	wprintf(L"Error getting the access token.\n");
	}

	DeleteFileA(lpFile);

	if(RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",&newKey)==ERROR_SUCCESS){

		if(RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey) == ERROR_SUCCESS){

			LONG result = RegSaveKeyExA(hKey, lpFile, NULL, REG_LATEST_FORMAT);

			if (result == ERROR_SUCCESS){
				sprintf(meg, "RegSaveKeyExA() : SUCCESS");
				strcpy(buf, "SUCCESS");
			}else{
				printf("%d", GetLastError());
				strcpy(meg, GetErrorMessage(" RegSaveKeyExA() : FAIL \n\n Error Message :", GetLastError()));
			}
		}else{
			strcpy(meg, GetErrorMessage(" Registry Key ���� ���� \n\n RegOpenKeyEx �Լ��� �ٽ� Ȯ���ϼ���", GetLastError()));
		}
	}else
		strcpy(meg, GetErrorMessage(" Registry Key ���� ���� \n\n RegCreateKey �Լ��� �ٽ� Ȯ���ϼ���", GetLastError()));

	wresult(__FILE__, __LINE__, "RegSaveKeyExA", buf, "SUCCESS", meg);

	DeleteFileA(lpFile);
	RegCloseKey(hKey);

	return true;
}

BOOL test_RegSaveKeyExW(){

	#ifdef OQADBGPRINT
	printf("test_RegSaveKeyExW \n");
	#endif

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	HKEY hKey = HKEY_CURRENT_USER;
	HKEY newKey;

    HANDLE proccessHandle = GetCurrentProcess();     // get the handle to the current proccess
    DWORD typeOfAccess = TOKEN_ADJUST_PRIVILEGES;   //  requiered to enable or disable the privilege
    HANDLE tokenHandle;                             //  handle to the opened access token

	LPCWSTR lpFile = L"C:\\test_RegSaveKeyExW.reg";

	if (OpenProcessToken(proccessHandle, typeOfAccess, &tokenHandle)){
		// Enabling RESTORE and BACKUP privileges
		SetPrivilege(tokenHandle, SE_BACKUP_NAME, TRUE);

	}else{
	//	wprintf(L"Error getting the access token.\n");
	}

	DeleteFile(lpFile);

	if(RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",&newKey)==ERROR_SUCCESS){

		if(RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey) == ERROR_SUCCESS){

			LONG result = RegSaveKeyExW(hKey, lpFile, NULL, REG_LATEST_FORMAT);

			if (result == ERROR_SUCCESS){
				sprintf(meg, "RegSaveKeyExW() : SUCCESS");
				strcpy(buf, "SUCCESS");
			}else{
				printf("%d", GetLastError());
				strcpy(meg, GetErrorMessage(" RegSaveKeyExW() : FAIL \n\n Error Message :", GetLastError()));
			}
		}else{
			strcpy(meg, GetErrorMessage(" Registry Key ���� ���� \n\n RegOpenKeyEx �Լ��� �ٽ� Ȯ���ϼ���", GetLastError()));
		}
	}else
		strcpy(meg, GetErrorMessage(" Registry Key ���� ���� \n\n RegCreateKey �Լ��� �ٽ� Ȯ���ϼ���", GetLastError()));

	wresult(__FILE__, __LINE__, "RegSaveKeyExW", buf, "SUCCESS", meg);

	DeleteFile(lpFile);
	RegCloseKey(hKey);

	return true;
}

/**
BOOL test_RegRestoreKeyA(){

	#ifdef OQADBGPRINT
	printf("test_RegRestoreKeyA \n");
	#endif

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	HKEY hKey = HKEY_CURRENT_USER;
	HKEY newKey;

    HANDLE proccessHandle = GetCurrentProcess();     // get the handle to the current proccess
    DWORD typeOfAccess = TOKEN_ADJUST_PRIVILEGES;   //  requiered to enable or disable the privilege
    HANDLE tokenHandle;                             //  handle to the opened access token

	LPSTR lpFile = "C:\\test_RegRestoreKeyA.reg";

	if (OpenProcessToken(proccessHandle, typeOfAccess, &tokenHandle)){
		// Enabling RESTORE and BACKUP privileges
		SetPrivilege(tokenHandle, SE_BACKUP_NAME, TRUE);

	}else{
		wprintf(L"Error getting the access token.\n");
	}

	DeleteFileA(lpFile);

	if(RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",&newKey)==ERROR_SUCCESS){

		if(RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey) == ERROR_SUCCESS){

			LONG result = RegRestoreKeyA(hKey, lpFile, 0);

			if (result == ERROR_SUCCESS){
				sprintf(meg, "RegRestoreKeyA() : SUCCESS");
				strcpy(buf, "SUCCESS");
			}else{
				printf("%d", GetLastError());
				strcpy(meg, GetErrorMessage(" RegRestoreKeyA() : FAIL \n\n Error Message :", GetLastError()));
			}
		}else{
			strcpy(meg, GetErrorMessage(" Registry Key ���� ���� \n\n RegOpenKeyEx �Լ��� �ٽ� Ȯ���ϼ���", GetLastError()));
		}
	}else
		strcpy(meg, GetErrorMessage(" Registry Key ���� ���� \n\n RegCreateKey �Լ��� �ٽ� Ȯ���ϼ���", GetLastError()));

	wresult(__FILE__, __LINE__, "RegRestoreKeyA", buf, "SUCCESS", meg);

	DeleteFileA(lpFile);
	RegCloseKey(hKey);

	return true;

}
*/

/**
������Ʈ�� Ű Ʈ���� �����մϴ�.
���� �� ���� �� ������ ������ ��ģ �� ���� �������� Ű�� ����� �����Ǿ����� Ȯ���մϴ�.
���� �� Ű�� Ŭ������ �� ���� �޽��� �ڽ��� ȣ��Ǹ� �����Դϴ�.
*/

BOOL test_RegDeleteTreeW(){

	#ifdef OQADBGPRINT
	printf("test_RegDeleteTreeW \n");
	#endif

	#ifdef OQADBGPRINT
	printf("test_RegDeleteTreeW \n");
	#endif

	HKEY newKey;
	LSTATUS result;
	HKEY hKey = HKEY_CURRENT_USER;

	char meg[BUFSIZ] = "FAIL";

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

	#ifdef OQADBGPRINT
	printf("test_RegEnumKeyExA \n");
	#endif

	HKEY key = HKEY_CURRENT_USER;
	char lpSubKey[MAX_PATH];
	char lpBuffer[MAX_PATH];
	DWORD i;
	LONG Result;
	DWORD Size;
	FILETIME FileTime;
	HWND hList = 0;
	char meg[BUFSIZ] = "FAIL";

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

#define BUFFER 8192
BOOL test_RegGetValueW(){
	
	#ifdef OQADBGPRINT
	printf("test_RegGetValueW\n");
	#endif

	RECT rt;
	HKEY newKey;
	LONG result;
	DWORD BufferSize = BUFFER;

	char value[255];
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";
	int wresult_value = 0;

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
		strcpy(meg, " RegGetValueW : SUCCESS");
	}else
		strcpy(meg, " RegGetValueW : FAIL");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegGetValueW", buf, "1", meg);
		
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


BOOL test_RegOpenCurrentUser(){
	/** ����� current thread�� �ڵ� �˻� */

	#ifdef OQADBGPRINT
	printf("test_RegOpenCurrentUser \n");
	#endif

	HKEY keyCurrentUser;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";
	int wresult_value = 0;

	/** ù ��° parameter : REGSAM�� �� KEY_READ : Combination of KEY_QUERY_VALUE(���� Ű �����͸� ���� ����), KEY_ENUMERATE_SUB_KEYS(���� Ű ����), and KEY_NOTIFY(���� ����) access.*/
	LONG result = RegOpenCurrentUser(KEY_READ, &keyCurrentUser);

	if(result==ERROR_SUCCESS){
		strcpy(meg, " RegOpenCurrentUser : SUCCESS");
		wresult_value=1;
	}else
		strcpy(meg, " RegOpenCurrentUser : FAIL");

	RegCloseKey(keyCurrentUser);

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegOpenCurrentUser", buf, "1", meg);

	return true;
}


BOOL test_RegOpenUserClassesRoot(){

	#ifdef OQADBGPRINT
	printf("test_RegOpenUserClassesRoot \n");

	#endif
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";
	int wresult_value = 0;

	HANDLE proccessHandle = GetCurrentProcess();     // get the handle to the current proccess
	DWORD typeOfAccess = TOKEN_QUERY;   //  requiered to enable or disable the privilege
	HANDLE tokenHandle;                             //  handle to the opened access token
	
	HKEY newKey;
	LONG result = 0;
	DWORD err = GetLastError();

	if (OpenProcessToken(proccessHandle, typeOfAccess, &tokenHandle) != 0){

		result = RegOpenUserClassesRoot(tokenHandle, 0, KEY_ALL_ACCESS, &newKey);

		if(result == ERROR_SUCCESS){
			strcpy(meg, " RegOpenUserClassesRoot : SUCCESS");
			wresult_value=1;
		
		}else
			strcpy(meg, " RegOpenUserClassesRoot : FAIL");

	}else
		strcpy(meg, " OpenProcessToken() ������ \n\n process�� ������ Access Token�� �ٽ� ���ʽÿ� ");
		
		sprintf(buf, "%d", wresult_value);
		wresult(__FILE__, __LINE__, "RegOpenUserClassesRoot", buf, "1", meg);

		return result;
	}



BOOL test_RegRestoreKeyA(){

#ifdef OQADBGPRINT
	printf("test_RegRestoreKeyA \n");
#endif

	/** �� ��° �Ķ���� lpFile : name of the file with the registry information. 
	created by using the RegSaveKey function. 
	�� RegSaveKey(hKey, lpFile, lpSecurityAttributes(NULL�̸� default security descriptor ������))	
	*/

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";
	int wresult_value = 0;
	LSTATUS result;
	HKEY newKey;
	LPSTR lpFile = "C:\\test_RegSaveKeyExA.reg";

	HANDLE proccessHandle = GetCurrentProcess();     // get the handle to the current proccess
	DWORD typeOfAccess = TOKEN_ADJUST_PRIVILEGES;   //  requiered to enable or disable the privilege
	HANDLE tokenHandle;                             //  handle to the opened access token

	HKEY hKey = HKEY_CURRENT_USER;

	if (OpenProcessToken(proccessHandle, typeOfAccess, &tokenHandle)){
		// Enabling RESTORE and BACKUP privileges
		SetPrivilege(tokenHandle, SE_RESTORE_NAME, TRUE);
		SetPrivilege(tokenHandle, SE_BACKUP_NAME, TRUE);

	}else{
		//wprintf(L"Error getting the access token.\n");
	}

	RegCloseKey(hKey);
	//RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",&newKey);
	//RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);
	//RegSaveKeyExA(hKey, lpFile, NULL, REG_LATEST_FORMAT);

	RegCloseKey(hKey);
	result = RegRestoreKeyA(hKey, lpFile, REG_FORCE_RESTORE);

	if(result == ERROR_SUCCESS){
		wresult_value=1;
		strcpy(meg, "RegRestoreKeyA : SUCCESS");
	}else
		strcpy(meg, "RegRestoreKeyA : FAIL");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegRestoreKeyA", buf, "1", meg);

	RegCloseKey(hKey);
	CloseHandle(tokenHandle);

	return true;
}


BOOL test_RegRestoreKeyW(){

#ifdef OQADBGPRINT
	printf("test_RegRestoreKeyW \n");
#endif

	/** �� ��° �Ķ���� lpFile : name of the file with the registry information. 
	created by using the RegSaveKey function. 
	�� RegSaveKey(hKey, lpFile, lpSecurityAttributes(NULL�̸� default security descriptor ������))	
	*/

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";
	int wresult_value = 0;
	LSTATUS result;
	//HKEY newKey;
	LPCTSTR lpFile = L"C:\\test_RegSaveKeyExA.reg";

	HANDLE proccessHandle = GetCurrentProcess();     // get the handle to the current proccess
	DWORD typeOfAccess = TOKEN_ADJUST_PRIVILEGES;   //  requiered to enable or disable the privilege
	HANDLE tokenHandle;                             //  handle to the opened access token

	HKEY hKey = HKEY_CURRENT_USER;

	if (OpenProcessToken(proccessHandle, typeOfAccess, &tokenHandle)){
		// Enabling RESTORE and BACKUP privileges
		SetPrivilege(tokenHandle, SE_RESTORE_NAME, TRUE);
		SetPrivilege(tokenHandle, SE_BACKUP_NAME, TRUE);

	}else{
		//wprintf(L"Error getting the access token.\n");
	}

	RegCloseKey(hKey);
	//RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",&newKey);
	//RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);
	//RegSaveKeyExA(hKey, lpFile, NULL, REG_LATEST_FORMAT);

	RegCloseKey(hKey);
	result = RegRestoreKeyW(hKey, lpFile, REG_FORCE_RESTORE);

	if(result == ERROR_SUCCESS){
		wresult_value=1;
		strcpy(meg, "RegRestoreKeyW : SUCCESS");
	}else
		strcpy(meg, "RegRestoreKeyW : FAIL");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegRestoreKeyW", buf, "1", meg);

	RegCloseKey(hKey);
	CloseHandle(tokenHandle);

	return true;
}

//#define UNICODE
//#define _WIN32_WINNT 0x0600 
BOOL test_RegLoadMUIStringA(){

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";
	int wresult_value = 0;

	HKEY hKEY = HKEY_CURRENT_USER;
	LPSTR pszValue = "value";
	LPSTR pszOutBuf = NULL;
	DWORD cbOutBuf = sizeof(pszOutBuf);
	LPDWORD pcbData = &cbOutBuf;
	DWORD flags = REG_MUI_STRING_TRUNCATE;
	LPCSTR pszDirectory = "C:\\Users\\Tmax\\Desktop\\test";

	LONG result = RegLoadMUIStringA(hKEY, pszValue, pszOutBuf, cbOutBuf, pcbData, flags, pszDirectory);
	DWORD err = GetLastError();

	if(result == ERROR_SUCCESS){
		wresult_value=1;
		strcpy(meg, "RegLoadMUIStringA : SUCCESS");
	}else if(result == ERROR_MORE_DATA)
		strcpy(meg, "RegLoadMUIStringA : FAIL \n\n pcbData�� �ʹ� �۽��ϴ�.");
	else if(result == ERROR_CALL_NOT_IMPLEMENTED)
		strcpy(meg, "RegLoadMUIStringA : FAIL \n\n ANSI version �� ����");
	else
		strcpy(meg, "RegLoadMUIStringA : FAIL");
	
	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegLoadMUIString", buf, "1", meg);

	return true;
}

#include <SubAuth.h>

BOOL test_RegLoadMUIStringW(){
	
	//int wresult_value = 0;
	//char buf[BUFSIZ];
	//char meg[BUFSIZ] = "FAIL";

	//DWORD err = GetLastError();
	////DWORD dwSize = 0;
	////LONG result = RegLoadMUIStringW(HKEY_CURRENT_USER, pszValue, cbOutBuf, MAX_PATH, &dwSize, NULL, NULL);

	//BOOL result;
	//DWORD size;
	//TCHAR pszOutBuf[MAX_PATH]; //3

	//HKEY hKey = HKEY_CURRENT_USER;
	//HKEY newKey;
	//RECT rt;
	//HWND hWnd =0;
	//RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest\\Position",&newKey);
	//RegSetValueExW(newKey, L"Top",0,REG_DWORD,(LPBYTE)&rt.top,sizeof(LONG));

	////REG_MUI_STRING_TRUNCATE : ���ڿ��� pszOutBuf ������ ��� ������ ũ�⿡ �°� �߸�.�� flags �����Ǹ� pcbData�� null
	////result = RegLoadMUIStringW(HKEY_CURRENT_CONFIG, L"display",	pszOutBuf, sizeof(pszOutBuf), (LPDWORD)&pszOutBuf, REG_MUI_STRING_TRUNCATE, NULL);
	////result = RegLoadMUIStringW(hKey, L"Top", pszOutBuf, MAX_PATH, NULL, NULL, NULL);

	//UNICODE_STRING valueW, baseDirW;
 //   WCHAR *pwszBuffer;
 //   DWORD cbData = MAX_PATH * sizeof(WCHAR);
 // 
 //   valueW.Buffer = baseDirW.Buffer = pwszBuffer = NULL;
 //  
 //   result = RegLoadMUIStringW(hKey, valueW.Buffer, pwszBuffer, cbData, (LPDWORD)REG_MUI_STRING_TRUNCATE, NULL, baseDirW.Buffer);

	//if(result == ERROR_SUCCESS){
	//	wresult_value=1;
	//	strcpy(meg, "RegLoadMUIStringW : SUCCESS");
	//}else if(result == ERROR_MORE_DATA)
	//	strcpy(meg, "RegLoadMUIStringW : FAIL \n\n pcbData�� �ʹ� �۽��ϴ�.");
	//else if(result == ERROR_CALL_NOT_IMPLEMENTED)
	//	strcpy(meg, "RegLoadMUIStringW : FAIL \n\n ANSI version �� ����");
	//else
	//	strcpy(meg, "RegLoadMUIStringW : FAIL");

	//sprintf(buf, "%d", wresult_value);
	//wresult(__FILE__, __LINE__, "RegLoadMUIStringW", buf, "1", meg);
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";
	int wresult_value = 0;

	HKEY hKEY = HKEY_CURRENT_USER;
	LPCWSTR pszValue = L"value";
	LPWSTR pszOutBuf = NULL;
	DWORD cbOutBuf = sizeof(pszOutBuf);
	LPDWORD pcbData = &cbOutBuf;
	DWORD flags = REG_MUI_STRING_TRUNCATE;
	LPCWSTR pszDirectory = L"C:\\Users\\Tmax\\Desktop\\test";

	LONG result = RegLoadMUIStringW(hKEY, pszValue, pszOutBuf, cbOutBuf, pcbData, flags, pszDirectory);
	DWORD err = GetLastError();

	printf("%d", err);
	if(result == ERROR_SUCCESS){
		wresult_value=1;
		strcpy(meg, "RegLoadMUIStringW : SUCCESS");
	}else if(result == ERROR_MORE_DATA)
		strcpy(meg, "RegLoadMUIStringW : FAIL \n\n pcbData�� �ʹ� �۽��ϴ�.");
	else if(result == ERROR_CALL_NOT_IMPLEMENTED)
		strcpy(meg, "RegLoadMUIStringW : FAIL \n\n ANSI version �� ����");
	else
		strcpy(meg, "RegLoadMUIStringW : FAIL");
	
	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegLoadMUIStringW", buf, "1", meg);

	return result;
}  