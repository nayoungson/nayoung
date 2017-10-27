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

    if (loadKeyA == ERROR_SUCCESS){
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
    LPCWSTR pHive = L"C:\\load4.reg";

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

    if (loadKeyA == ERROR_SUCCESS){
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


/**
BOOL test_RegRestoreKeyA(){

	/** �� ��° �Ķ���� lpFile : name of the file with the registry information. 
								  created by using the RegSaveKey function. 
								  �� RegSaveKey(hKey, lpFile, lpSecurityAttributes(NULL�̸� default security descriptor ������))	
	LONG result2;
	HKEY newKey;
	LSTATUS result;

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];
	

	#ifdef OQADBGPRINT
	printf("test_RegCreateKeyExW\n");
	#endif

	result = RegCreateKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL);

	if(result == ERROR_SUCCESS){
		printf("create����");
			
	}else
		printf("create����");

	Sleep(2000);

	LPCTSTR lpFile = L"C:\\Users\\Tmax\\Desktop\\test\\dbg_log.dat";

	//result2 = RegSaveKey(HKEY_CURRENT_USER, lpFile, NULL);
	
	//if(result2 == ERROR_SUCCESS)
	//	printf("save ����");
	//else{
	//	printf("save ����");
	//	strcpy(meg, GetErrorMessage(" GetProcessId() : FAIL \n\n Error Message :", GetLastError()));
	//}
	//wresult(__FILE__, __LINE__, "GetProcessId", buf, "SUCCESS", meg);
		

	Sleep(2000);

	result = RegRestoreKeyA(HKEY_CURRENT_USER, (LPSTR)(LPCTSTR)result, REG_FORCE_RESTORE);

	if(result == ERROR_SUCCESS)
		printf("restore ����");
	else
		printf("restore ����");
	return true;
}
*/
