#include "TestRegistry.h"
#include <atlstr.h>

// ���� �ο� �Լ�.
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
	//	printf("AdjustTokenPrivileges error: %u\n", GetLastError());
		return FALSE;
	}

	if(GetLastError() == ERROR_NOT_ALL_ASSIGNED){
	//	printf("The token does not have the specified privilege. \n");
		return FALSE;
	}

	return TRUE;
}


/**
* LONG WINAPI RegCloseKey(
  _In_ HKEY hKey
  );
* Ư�� ������Ʈ�� Ű �ڵ� �ݱ�.
* @author : �ճ���
*
* @param hKey ���� �ڵ�. �� ���� RegCreateKeyEx, RegOpenKeyEx �Լ� ������ Ű�� ���� �־�� ��.
* @return �ڵ� �ݱ� ����/���� ����
*/

BOOL test_RegCloseKey(){

	#ifdef OQADBGPRINT
	printf("test_RegCloseKey \n");
	#endif

	HKEY hKey = HKEY_CURRENT_USER;
	HKEY phkResult = 0;
	LONG result = FALSE;

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	// Ŭ������ key�� ���� ����(�Ǵ� ����)�� ��� ��. 
	result = RegCreateKeyExW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&phkResult, NULL);

	if(result == ERROR_SUCCESS){ // ���� ���� �� ��� ����.
		result = RegCloseKey(hKey); // newKey Ŭ���� ����.

			if(result == ERROR_SUCCESS){ // Ŭ���� ���� ��.
				strcpy(buf, "SUCCESS");
				strcpy(msg, " RegCloseKey : SUCCESS");

			}else{ // ���� ���� �� Ŭ���� ���� ��.
				strcpy(msg, "RegCloseKey  : FAIL \n\n RegCreateKeyW ���������� �� RegCloseKey ����");
				return FALSE;
			}
	}else{
		strcpy(msg, "RegCreateKeyExW �Լ��� �ٽ� Ȯ���Ͻʽÿ�. \n key Ŭ���� �� ���� ���� �Ǵ� ���µǾ�� �մϴ�.");
		return FALSE;
	}

	wresult(__FILE__, __LINE__, "RegCloseKey", buf, "SUCCESS", msg);
	return result;
}

/**
* LONG WINAPI RegCreateKeyEx(
  _In_       HKEY                  hKey,
  _In_       LPCTSTR               lpSubKey,
  _Reserved_ DWORD                 Reserved,
  _In_opt_   LPTSTR                lpClass,
  _In_       DWORD                 dwOptions,
  _In_       REGSAM                samDesired,
  _In_opt_   LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  _Out_      PHKEY                 phkResult,
  _Out_opt_  LPDWORD               lpdwDisposition
  );
* Ư�� ������Ʈ�� Ű ����. �̹� �����ϸ� ����.
* @author : �ճ���

* @param hKey ������ ������Ʈ�� Ű �ڵ�. ���� Ű ��Ͽ��� ���� ����.
* @param lpSubKey ���� �Ǵ� �����ϴ� ����Ű��.
* @param Reserved ������ 0.
* @param lpClass Ű�� ����� ���� Ŭ���� Ÿ��. ������ �� ����. NULL.
* @param dwOptions 4���� �ɼ� �� �ϳ�.
* @param samDesired �����Ǵ� Ű ���� ������ �����ϴ� ����ũ. 
* @param lpSecurityAttributes ���ϵǴ� �ڵ��� �ڽ� ���μ����� ���� ��ӵǴ��� �� �Ǵ��� �����ϴ� SECURITY_ATTRIBUTES ����ü�� ���� ������.
* @param phkResult ���� �Ǵ� �����Ǵ� Ű �ڵ��� �޴� ������ ���� ������. �̹� ���ǵ� Ű�� �ƴ϶�� RegCloseKey �Լ��� �ڵ� �� ������ call.
* @param lpdwDisposition 2���� �ɼ� �� �ϳ�. ���� NULL�̸� � ������ ��ȯ���� ����.
* @return ���� ����/���� ����
*/
BOOL test_RegCreateKeyExW(){

	#ifdef OQADBGPRINT
	printf("test_RegCreateKeyExW \n");
	#endif

	HKEY phkResult;
	LONG result = NULL;
	HKEY hKey = HKEY_CURRENT_USER;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	result = RegCreateKeyExW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&phkResult, NULL);

	if(result == ERROR_SUCCESS){ // ���� ���� ��
		strcpy(buf, "SUCCESS");
		strcpy(msg, " RegCreateKeyExW : SUCCESS");
			
	}else{ // ���� ���� ��
		strcpy(msg, " RegCreateKeyExW : FAIL");
		return FALSE;
	}

	wresult(__FILE__, __LINE__, "RegCreateKeyExW", buf, "SUCCESS", msg);	 
	return result;
}


/**
* LONG WINAPI RegCreateKey(
  _In_     HKEY    hKey,
  _In_opt_ LPCTSTR lpSubKey,
  _Out_    PHKEY   phkResult
  );
* Ư�� ������Ʈ�� Ű ����. �̹� �����Ѵٸ� ����.
* @author : �ճ���
*
* @param hKey ������ ������Ʈ�� Ű �ڵ�. ���� Ű ��Ͽ��� ���� ����.
* @param lpSubKey ���� �Ǵ� �����ϴ� ����Ű��.
* @param phkResult ���� �Ǵ� �����Ǵ� Ű �ڵ��� �޴� ������ ���� ������. �̹� ���ǵ� Ű�� �ƴ϶�� RegCloseKey �Լ��� �ڵ� �� ������ call.
* @return ���� ����/���� ����
*/

BOOL test_RegCreateKeyW(){

	#ifdef OQADBGPRINT
	printf("test_RegCreateKeyW  \n");
	#endif

	HKEY phkResult;
	LONG result = FALSE;
	HKEY hKey = HKEY_CURRENT_USER;

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	result = RegCreateKeyW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",&phkResult);

	if(result == ERROR_SUCCESS){
		strcpy(buf, "SUCCESS");
		strcpy(msg, " RegCreateKeyW() : SUCCESS");
		
	}else{
		strcpy(msg, " RegCreateKeyW() : FAIL");
		return FALSE;
	}
		
	wresult(__FILE__, __LINE__, "RegCreateKeyW", buf, "SUCCESS", msg);
	return result;
}


/**
* LONG WINAPI RegDeleteKeyEx(
  _In_       HKEY    hKey,
  _In_       LPCTSTR lpSubKey,
  _In_       REGSAM  samDesired,
  _Reserved_ DWORD   Reserved
  );
* Ư�� ������Ʈ���� ����Ű ����
* @author : �ճ���
*
* @param hKey ������ ������Ʈ�� Ű �ڵ�. ���� Ű ��Ͽ��� ���� ����.
* @param lpSubKey ���� �Ǵ� �����ϴ� ����Ű��.
* @param samDesired �����Ǵ� Ű ���� ������ �����ϴ� ����ũ. 
* @param Reserved ������ 0.
* @return ���� ����/���� ����.
*/

BOOL test_RegDeleteKeyExW(){  

	#ifdef OQADBGPRINT
	printf("test_RegDeleteKeyExW \n");
	#endif

	HKEY phkResult;
	LONG result = FALSE;
	HKEY hKey = HKEY_CURRENT_USER;

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	//���� �� ���� ����.
	result = RegCreateKeyW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",&phkResult);

	if(result == ERROR_SUCCESS){ // ���� ���� �� ��� ����.

		result = RegDeleteKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", KEY_WOW64_32KEY, 0);

		//if(RegCreateKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL)) == ERROR_SUCCESS){
		if(result == ERROR_SUCCESS){ //���� ���� ��.
			strcpy(buf, "SUCCESS");
			strcpy(msg, " RegDeleteKeyExW() : SUCCESS");

		}else{ // ���� ���� ��.
			strcpy(msg, " RegDeleteKeyExW : FAIL");
			return FALSE;
		}

	}else{ // ���� �� ���� ���� ��.
		strcpy(msg, "RegCreateKeyExW �Լ��� �ٽ� Ȯ���Ͻʽÿ�. \n ������ Ű�� ���ٸ� ���� �����ؾ� �մϴ�.");
		return FALSE;
	}

	wresult(__FILE__, __LINE__, "RegDeleteKeyExW", buf, "SUCCESS", msg);
	return result;
}

/**
* LONG WINAPI RegDeleteKey(
  _In_ HKEY    hKey,
  _In_ LPCTSTR lpSubKey
  );
* ���� Ű�� �� ���� ����
* @author : �ճ���
*
* @param hKey ������ ������Ʈ�� Ű �ڵ�. ���� Ű ��Ͽ��� ���� ����.
* @param lpSubKey ���� �Ǵ� �����ϴ� ����Ű��.
* @return ���� ����/���� ����
*/

BOOL test_RegDeleteKeyW(){

	#ifdef OQADBGPRINT
	printf("test_RegDeleteKeyW\n");
	#endif

	HKEY newKey;
	LONG result = FALSE;
	HKEY hKey = HKEY_CURRENT_USER;

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";


	result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",&newKey);

	if(result == ERROR_SUCCESS){
		result = RegDeleteKeyW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position");

		if(result == ERROR_SUCCESS){
			strcpy(msg, " RegDeleteKeyW() : SUCCESS");
			strcpy(buf, "SUCCESS");

			result = TRUE;

			//�������� Key�� �ݾ���� ��
			RegCloseKey(newKey);

		}else{
			strcpy(msg, " RegDeleteKeyW() : FAIL \n\n Create���� �� Open ���� �� Set ���� �� Delete ���� \n RegDeleteKeyW()�� �߸��Ǿ����ϴ�.");

			return FALSE;
		}

	}else{
		strcpy(msg, " RegOpenKeyEx() : FAIL \n\n Create���� �� Open ���� \n RegOpenKeyEx()�� �߸��Ǿ����ϴ�.");
		return FALSE;
	}

	wresult(__FILE__, __LINE__, "RegDeleteKeyW", buf, "SUCCESS", msg);
	return result;
}


/**
* LONG WINAPI RegDeleteTree(
  _In_     HKEY    hKey,
  _In_opt_ LPCTSTR lpSubKey
  );
* Ư�� Ű�� ����Ű�� ���� ��������� ����.
* @author : �ճ���

* @param hKey ������ ������Ʈ�� Ű �ڵ�. ���� Ű ��Ͽ��� ���� ����.
* @param lpSubKey ���� �Ǵ� �����ϴ� ����Ű��. NULL �̸� hKey�� ������ ����.
* @return ���� ����/���� ����
*/

/**
������Ʈ�� Ű Ʈ���� �����մϴ�.
���� �� ���� �� ������ ������ ��ģ �� ���� �������� Ű�� ����� �����Ǿ����� Ȯ���մϴ�.
���� �� REGEDIT���� Ű�� Ŭ������ �� ���� �޽��� �ڽ��� ȣ��Ǹ� �����Դϴ�.
*/

BOOL test_RegDeleteTreeW(){

	#ifdef OQADBGPRINT
	printf("test_RegDeleteTreeW \n");
	#endif

	HKEY newKey;
	LONG result = FALSE;
	HKEY hKey = HKEY_CURRENT_USER;

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	// ���� Ű ����.
	result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest\\Position",&newKey);

	// Ű�� ���������� �����Ǹ�, (�̶� �ݵ�� ���� Ű �����ؾ� ��. �� ������ Ȯ������ �ʾҴٰ� hKey�� �Ʒ��� ����Ǹ� ���� �� ��.
	if(result == ERROR_SUCCESS){ 
		result = RegDeleteTreeW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest"); // ��������� ���� ����.

		// ������ �����Ͽ� ERROR_SUCCESS�� ��ȯ�ϸ�, 
		if(result == ERROR_SUCCESS){ 
			result = RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey); // �����ߴ� Ű�� ������ ����.

			// �� �����Ǿ� ���¿� �����ϸ� �� RegDeleteTreeW �׽�Ʈ ����.
			// �̶� REGEDIT Ȯ���� ����, HKEY_CURRENT_USER\\SOFTWARE\\NAYOUNG_API_TEST_2 ������ ����. 
			if(result != ERROR_SUCCESS){ 
				strcpy(msg, "RegDeleteTreeW() : SUCCESS");
				strcpy(buf, "SUCCESS");
				//result = TRUE;

			// ���� �� ERROR_SUCCESS�� ��ȯ�Ͽ� ������ �� �˾����� ���¿� ������ ���� ��Ȳ.
			}else {
				strcpy(msg, "RegDeleteTreeW() : FAIL");
				return FALSE;
			}

		// ���� ����. = RegDeleteTreeW ����.
		}else {
			strcpy(msg, "RegDeleteTreeW() : FAIL");
			return FALSE;
		}

	// Ű ���� �������� ����.	
	}else {
		strcpy(msg, "RegCreateKey �Լ��� �ٽ� Ȯ���Ͻʽÿ�.");
		return FALSE;
	}

	wresult(__FILE__, __LINE__, "RegDeleteTree", buf, "SUCCESS", msg);
	return result;
}


/**
* LONG WINAPI RegDeleteValue(
  _In_     HKEY    hKey,
  _In_opt_ LPCTSTR lpValueName
  );
* Ư�� ������Ʈ�� Ű�� �̸� ���� ����.
* @author : �ճ���
*
* @param hKey ������ ������Ʈ�� Ű �ڵ�. ���� Ű ��Ͽ��� ���� ����.
* @param lpValueName ������ ������Ʈ�� �̸�. NULL�̰ų� �� ���ڿ��̸� RegSetValue�Լ��� ���� ������ ���� ������.
* @return
*/

BOOL test_RegDeleteValueW(){

	#ifdef OQADBGPRINT
	printf("test_RegDeleteValueW\n");
	#endif

	HKEY hKey = HKEY_CURRENT_USER;
	HKEY newKey;
	RECT rt;
	HWND hWnd =0;

	LONG result = FALSE;
	
	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";
	
	// ������Ʈ�� Ű �������� ����. 
	result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest\\Position",&newKey);

	if(result == ERROR_SUCCESS){ // ������ �����ϸ� 
		RegSetValueExW(newKey, L"Top",0,REG_DWORD,(LPBYTE)&rt.top,sizeof(LONG)); // ���� set.
		//RegSetValueExW(newKey, L"Right",0,REG_DWORD,(LPBYTE)&rt.right,sizeof(LONG));
		//RegSetValueExW(newKey, L"Bottom",0,REG_DWORD,(LPBYTE)&rt.bottom,sizeof(LONG));
		//RegSetValueExW(newKey, L"Left",0,REG_DWORD,(LPBYTE)&rt.left,sizeof(LONG));

		result = RegDeleteValueW(newKey, L"TOP");

		if(result == ERROR_SUCCESS){
			strcpy(buf, "SUCCESS");
			strcpy(msg, " RegDeleteValueW() : SUCCESS");
			result = TRUE;

			//�������� Key�� �ݾ���� ��
			RegCloseKey(newKey);

		}else
			strcpy(msg, " RegDeleteValueW() : FAIL");
		
	}else
		strcpy(msg, " RegCreateKey �Լ��� �ٽ� üũ�Ͻʽÿ�.");
	
	wresult(__FILE__, __LINE__, "RegDeleteValueW", buf, "SUCCESS", msg);
	return result;
}


/**
* LONG WINAPI RegDisablePredefinedCacheEx(void);
* ���� ���μ����� �̸� ���� �� ������Ʈ�� �ڵ鿡 ���� �ڵ� ĳ���� ��Ȱ��ȭ.
* @author : �ճ���
*
* @param void.
* @return ��Ȱ��ȭ ����/���� ����.
*/

BOOL test_RegDisablePredefinedCacheEx(){

	#ifdef OQADBGPRINT
	printf("test_RegDisablePredefinedCacheEx \n");
	#endif

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	LONG result = FALSE;

	result = RegDisablePredefinedCacheEx();

	if(result == ERROR_SUCCESS){ // ��Ȱ��ȭ ����
		strcpy(buf, "SUCCESS");
		strcpy(msg, "RegDisablePredefinedCacheEx() : SUCCESS");	

	}else{
		strcpy(msg, " RegDisablePredefinedCacheEx() : FAIL");
		return FALSE;
	}

	wresult(__FILE__, __LINE__, "RegDisablePredefinedCacheEx", buf, "SUCCESS", msg);

	return result;
}


/**
* LONG WINAPI RegEnumKeyEx(
  _In_        HKEY      hKey,
  _In_        DWORD     dwIndex,
  _Out_       LPTSTR    lpName,
  _Inout_     LPDWORD   lpcName,
  _Reserved_  LPDWORD   lpReserved,
  _Inout_     LPTSTR    lpClass,
  _Inout_opt_ LPDWORD   lpcClass,
  _Out_opt_   PFILETIME lpftLastWriteTime
 );
* Ư�� ���� ������Ʈ�� Ű�� ���� Ű�� ����.
* @author : �ճ���
*
* @param hKey ������ ������Ʈ�� Ű �ڵ�. ���� Ű ��Ͽ��� ���� ����.
* @param dwIndex ������ ���� Ű�� �ε���. �� �Ű� ������ RegEnumKeyEx �Լ� �� ���� ù ��° ȣ�⿡ ���� 0�̾���ϸ� ���� ȣ�⿡ ���� ������.
* @param lpName ���� NULL ���ڸ� �����Ͽ� ���� Ű�� �̸��� �����ϴ� ���ۿ� ���� ������.
* @param lpcName lpName �Ű� ������ ������ ������ ũ�⸦ ���� �� ��Ÿ�� ������ ���� ������ .
* @param lpReserved ������ NULL.
* @param lpClass ���� �� ���� Ű�� ����� ���� Ŭ�������޴� ���ۿ� ���� ������. NULL ����.
* @param lpcClass lpClass �Ű� ������ ������ ���� ũ�⸦ ���ڷ� �����ϴ� ������ ���� ������. lpClass�� NULL�� ��쿡�� NULL ����.
* @param lpftLastWriteTime ���� �� ���� Ű�� ���������� ��� �� �ð����޴� FILETIME ����ü�� ���� ������. NULL ����.
* @return ���� ����/���� ����.
*/

BOOL test_RegEnumKeyExA(){

	#ifdef OQADBGPRINT
	printf("test_RegEnumKeyExA \n");
	#endif

	DWORD i;
	LONG result = FALSE;
	DWORD Size;
	FILETIME FileTime;
	HWND hList = 0;
	HKEY key = HKEY_CURRENT_USER;

	char lpSubKey[MAX_PATH];
	char lpBuffer[MAX_PATH];

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	//printf("��RegEnumKeyExA() ��¡� \n");
	#endif

	for (i=0;result==ERROR_SUCCESS;i++) {
		Size=MAX_PATH;

		result=RegEnumKeyExA(key,i,lpSubKey,&Size,NULL,NULL,NULL,&FileTime);
		if (result==ERROR_SUCCESS) {

			#ifdef OQADBGPRINT
			//printf("K : %s \n",lpSubKey);
			#endif

			SendMessage(hList,LB_ADDSTRING,0,(LONG)lpBuffer);
		}
	}
	#ifdef OQADBGPRINT
	//printf("\n");
	#endif

	strcpy(msg, " RegEnumKeyExA() : SUCCESS");
	wresult(__FILE__, __LINE__, "RegEnumKeyExA", "ERROR_SUCCESS", "ERROR_SUCCESS", msg);
	return result;
}


/**
* LONG WINAPI RegEnumKeyEx(
  _In_        HKEY      hKey,
  _In_        DWORD     dwIndex,
  _Out_       LPTSTR    lpName,
  _Inout_     LPDWORD   lpcName,
  _Reserved_  LPDWORD   lpReserved,
  _Inout_     LPTSTR    lpClass,
  _Inout_opt_ LPDWORD   lpcClass,
  _Out_opt_   PFILETIME lpftLastWriteTime
 );
* Ư�� ���� ������Ʈ�� Ű�� ���� Ű�� ����.
* @author : �ճ���
*
* @param hKey ������ ������Ʈ�� Ű �ڵ�. ���� Ű ��Ͽ��� ���� ����.
* @param dwIndex ������ ���� Ű�� �ε���. �� �Ű� ������ RegEnumKeyEx �Լ� �� ���� ù ��° ȣ�⿡ ���� 0�̾���ϸ� ���� ȣ�⿡ ���� ������.
* @param lpName ���� NULL ���ڸ� �����Ͽ� ���� Ű�� �̸��� �����ϴ� ���ۿ� ���� ������.
* @param lpcName lpName �Ű� ������ ������ ������ ũ�⸦ ���� �� ��Ÿ�� ������ ���� ������ .
* @param lpReserved ������ NULL.
* @param lpClass ���� �� ���� Ű�� ����� ���� Ŭ�������޴� ���ۿ� ���� ������. NULL ����.
* @param lpcClass lpClass �Ű� ������ ������ ���� ũ�⸦ ���ڷ� �����ϴ� ������ ���� ������. lpClass�� NULL�� ��쿡�� NULL ����.
* @param lpftLastWriteTime ���� �� ���� Ű�� ���������� ��� �� �ð����޴� FILETIME ����ü�� ���� ������. NULL ����.
* @return ���� ����/���� ����.
*/

BOOL test_RegEnumKeyExW(){

	#ifdef OQADBGPRINT
	printf("test_RegEnumKeyExA \n");
	#endif

	DWORD i;
	LONG result = FALSE;
	DWORD Size;
	FILETIME FileTime;
	HWND hList = 0;
	HKEY key = HKEY_CURRENT_USER;

	TCHAR lpSubKey[MAX_PATH];
	TCHAR lpBuffer[MAX_PATH];

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	//printf("��RegEnumKeyExW() ��¡� \n");
	#endif

	for (i=0;result==ERROR_SUCCESS;i++) {
		Size=MAX_PATH;

		result=RegEnumKeyExW(key,i,lpSubKey,&Size,NULL,NULL,NULL,&FileTime);
		if (result==ERROR_SUCCESS) {

			#ifdef OQADBGPRINT
			//printf("K : %s \n",lpSubKey);
			#endif

			SendMessage(hList,LB_ADDSTRING,0,(LONG)lpBuffer);
		}
	}
	#ifdef OQADBGPRINT
	//printf("\n");
	#endif

	strcpy(msg, " RegEnumKeyExW() : SUCCESS");
	wresult(__FILE__, __LINE__, "RegEnumKeyExW", "ERROR_SUCCESS", "ERROR_SUCCESS", msg);
	return result;
}


/**
* LONG WINAPI RegEnumKey(
  _In_  HKEY   hKey,
  _In_  DWORD  dwIndex,
  _Out_ LPTSTR lpName,
  _In_  DWORD  cchName
  );
* Ư�� ���� ������Ʈ�� Ű�� ���� Ű�� ����. 16��Ʈ ���� �Լ��̹Ƿ� RegEnumKeyEx �Լ� ���.
* @author : �ճ���
*
* @param hKey ������ ������Ʈ�� Ű �ڵ�. ���� Ű ��Ͽ��� ���� ����.
* @param dwIndex ������ ���� Ű�� �ε���. �� �Ű� ������ RegEnumKeyEx �Լ� �� ���� ù ��° ȣ�⿡ ���� 0�̾���ϸ� ���� ȣ�⿡ ���� ������.
* @param lpName ���� NULL ���ڸ� �����Ͽ� ���� Ű�� �̸��� �����ϴ� ���ۿ� ���� ������.
* @param cchName lpName�Ķ���Ϳ� ���� ���� �������� ���̺�. TCHAR.
* @return ���� ����/���� ����
*/

BOOL test_RegEnumKeyW(){

	#ifdef OQADBGPRINT
	printf("test_RegEnumKeyW\n");
	#endif

	HKEY Key = HKEY_CURRENT_USER;
	DWORD dwIndex = 0;
	TCHAR lpName[MAX_PATH];
	DWORD lpBuffer = 255;
	LONG result = ERROR_SUCCESS;
	DWORD i;
	HWND hList = 0;
	DWORD Size;

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	//printf("��RegEnumKeyW() ��¡� \n");
	#endif

	for (i=0;result==ERROR_SUCCESS;i++) {
		Size=MAX_PATH;
		result=RegEnumKeyW(Key,i,lpName,lpBuffer);

		if (result==ERROR_SUCCESS) {

			strcpy(buf, "SUCCESS");
			strcpy(msg, " RegEnumKeyW() : SUCCESS");

			#ifdef OQADBGPRINT
			//printf("K : %s \n",lpName);
			#endif
			SendMessage(hList,LB_ADDSTRING,0,(LONG)lpBuffer);

		//}else{
		//	strcpy(msg, " RegEnumKeyW() : FAIL");
		//	//return FALSE;
		//}
		}
	}
	wresult(__FILE__, __LINE__, "RegEnumKeyW", buf, "SUCCESS", msg);
	return result;
}


/**
* LONG WINAPI RegEnumValue(
  _In_        HKEY    hKey,
  _In_        DWORD   dwIndex,
  _Out_       LPTSTR  lpValueName,
  _Inout_     LPDWORD lpcchValueName,
  _Reserved_  LPDWORD lpReserved,
  _Out_opt_   LPDWORD lpType,
  _Out_opt_   LPBYTE  lpData,
  _Inout_opt_ LPDWORD lpcbData
  );
* Ư�� ���� ������Ʈ�� Ű�� ���� ����. �� �Լ��� ȣ�� �� ������ Ű�� ���� �ϳ��� �ε��� �� �̸��� ������ ����� ����.
* @author : �ճ���
*
* @param hKey ������ ������Ʈ�� Ű �ڵ�. ���� Ű ��Ͽ��� ���� ����.
* @param dwIndex ���� �ε���. �� �Ű� ������ RegEnumValue �Լ� �� ���� ù ��° ȣ�⿡ ���� 0�̾���ϸ� ���� ȣ�⿡ ���� ����.
* @param lpValueName ���� �̸��� Null�� ������ ���ڿ� �ι޴� ���ۿ� ���� ������ . �� ���۴� ���� �� ���� �� ���� �Ҹ�ŭ ����� Ŀ����.
* @param lpcchValueName lpValueName �Ű� ������ ����Ű�� ������ ũ�� �� ���ڷ� ��Ÿ�� ���� �� ���� ������ .
* @param lpReserved �� �Ű� ������ ����Ǿ� �����Ƿ� NULL �̾�� ��.
* @param lpType ������ ���� ����� ������ ������ ��Ÿ���� �ڵ带 �����ϴ� ������ ���� ������.
* @param lpData �� �׸� ���� �����͸� �����ϴ� ���ۿ� ���� ������. �� �Ű� ������ �����Ͱ� �ʿ����� ���� ��� NULL �� �� ����.
* @param lpcbData lpData �Ű� ������ ����Ű�� ���� ũ�� �� ����Ʈ ������ �����ϴ� ������ ������ .
* @return ���� �� ERROR_SUCCESS ��ȯ.
*/

BOOL test_RegEnumValueW(){

	#ifdef OQADBGPRINT
	printf("test_RegEnumValueW\n");
	#endif

	#define MAX_KEY_LENGTH 255
	#define MAX_VALUE_NAME 16383

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	HKEY key = HKEY_CURRENT_USER;
	TCHAR lpSubKey[MAX_PATH];
	TCHAR lpValue[MAX_PATH];
	TCHAR lpBuffer[MAX_PATH];
	DWORD i;
	LONG Result;
	DWORD Size;
	FILETIME FileTime; 


	Result=ERROR_SUCCESS;
	for (i=0;Result==ERROR_SUCCESS;i++) {
		Size=MAX_PATH;
		Result=RegEnumValue(key,i,lpValue,&Size,NULL,NULL,NULL,NULL);
		if (Result==ERROR_SUCCESS) {
			wsprintf(lpBuffer, L"V : %s",lpValue);
		}
	}

	if(Result == ERROR_SUCCESS){
		strcpy(buf, "SUCCESS");
		strcpy(msg, " RegEnumValueW : SUCCESS \n\n �� ��° ���� dwIndex = 0 �� ù ��° ���� RegEnum");

	}else if(Result == ERROR_NO_MORE_ITEMS){
		strcpy(msg, "If there are no more values available, the function returns ERROR_NO_MORE_ITEMS.");

	}else if(Result == ERROR_MORE_DATA){
		strcpy(msg, "If the lpData buffer is too small to receive the value");

	}else{
		strcpy(msg, "RegEnumValueW : FAIL");
	}
	
	wresult(__FILE__, __LINE__, "RegEnumValueW", buf, "SUCCESS", msg);
	return true;
}


/**
* LONG WINAPI RegGetKeySecurity(
  _In_      HKEY                 hKey,
  _In_      SECURITY_INFORMATION SecurityInformation,
  _Out_opt_ PSECURITY_DESCRIPTOR pSecurityDescriptor,
  _Inout_   LPDWORD              lpcbSecurityDescriptor
  );
* ������Ʈ�� Ű�� protecting�ϴ� security descriptor�� �� ���纻 ������.
* @author : �ճ���
*
* @param hKey ������ ������Ʈ�� Ű �ڵ�. ���� Ű ��Ͽ��� ���� ����.
* @param SecurityInformation SECURITY_INFORMATION�� ��û�� ���� ������ ��Ÿ���� ��. 
* @param pSecurityDescriptor ��û�� ���� ���� ���� ���纻�� �޴� ���ۿ� ���� ������.
* @param lpcbSecurityDescriptor pSecurityDescriptor �Ű� ������ ����Ű�� ������ ũ�� (����Ʈ)�� �����ϴ� ������ ���� ������ .
* @return �������� ����/���� ����.
*/

BOOL test_RegGetKeySecurity(){

	#ifdef OQADBGPRINT
	printf("test_RegGetKeySecurity \n");
	#endif
	
	int wresult_value=0;
	int err = GetLastError();

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	LONG result = FALSE;
	HKEY newKey;
	HKEY hKey = HKEY_CURRENT_USER;
	DWORD dwSdSizeNeeded = 4000;
	PSECURITY_DESCRIPTOR psdNew = NULL;
	SECURITY_INFORMATION si = DACL_SECURITY_INFORMATION;

	RegCloseKey(hKey);

	//�ݵ�� ��������� ��
	result = RegOpenKeyW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position", &newKey);

	if(result != ERROR_SUCCESS){
		sprintf(msg, " RegOpenKeyW�Լ��� �ٽ� Ȯ���Ͻʽÿ� \n\n Error Code : %d", err);
	}

	result = RegGetKeySecurity(hKey, si, psdNew, &dwSdSizeNeeded);

	if (result == ERROR_SUCCESS ){
		strcpy(buf, "SUCCESS");
		sprintf(msg, " RegGetKeySecurity() : SUCCESS");

	}else if(result == ERROR_INSUFFICIENT_BUFFER){
		sprintf(msg, " RegGetKeySecurity() : FAIL \n\n Buffer�� ũ�Ⱑ �ʹ� �۽��ϴ�.");

	}else
		sprintf(msg, " RegGetKeySecurity() : FAIL \n\n Error Code : %d", err);

	RegCloseKey(hKey);

	wresult(__FILE__, __LINE__, "RegGetKeySecurity", buf, "SUCCESS", msg);
	return result;
}


/**
* LONG WINAPI RegGetValue(
  _In_        HKEY    hkey,
  _In_opt_    LPCTSTR lpSubKey,
  _In_opt_    LPCTSTR lpValue,
  _In_opt_    DWORD   dwFlags,
  _Out_opt_   LPDWORD pdwType,
  _Out_opt_   PVOID   pvData,
  _Inout_opt_ LPDWORD pcbData
  );
* Ư�� ������Ʈ�� ���� Ÿ�԰� �����͸� ������.
* @author : �ճ���
*
* @param hKey ������ ������Ʈ�� Ű �ڵ�. ���� Ű ��Ͽ��� ���� ����.
* @param lpSubKey ���� �Ǵ� �����ϴ� ����Ű��.
* @param lpValue ������Ʈ�� �� �̸�. NULL�̰ų� �� ��Ʈ���̸� Ű�� ����Ʈ ���� Ÿ�԰� �����͸� ������.
* @param dwFlags ��ȸ �� ���� ������ ������ �����ϴ� �÷���. 10+4����.
* @param pdwType ������ ���� ����� ������ ������ ��Ÿ���� �ڵ带 �����ϴ� ������ ���� ������. ������ �ʿ����� ������ NULL.
* @param pvData ���� �����͸��޴� ���ۿ� ���� ������. �����Ͱ� �ʿ����� ������ NULL.
* @param pcbData pvData �Ű� ������ ����Ű�� ������ ũ�� �� ����Ʈ ������ �����ϴ� ������ ������. pcbData NULL�� ��쿡�� pvData NULL ����.
* @return �������� ����/���� ����.
*/

#define BUFFER 8192
BOOL test_RegGetValueW(){
	
	#ifdef OQADBGPRINT
	printf("test_RegGetValueW \n");
	#endif

	RECT rt;
	HKEY hKey = HKEY_CURRENT_USER;
	HKEY newKey;
	LONG result = FALSE;
	DWORD BufferSize = BUFFER;

	char value[255];
	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	// Registry ����
	result = RegCreateKeyExW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL);
	if(result != ERROR_SUCCESS){
		strcpy(msg, " ������Ʈ�� CREATE ����");
		result = FALSE;
	}

	// ������ Registry key�� value������ Top ����
	result = RegSetValueExW(newKey, L"Top",0,REG_DWORD,(LPBYTE)&rt.left,sizeof(LONG));
	if(result != ERROR_SUCCESS){
		strcpy(msg, " ������Ʈ�� SET ����");
		result = FALSE;
	}

	result = RegGetValueW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", L"TOP", RRF_RT_REG_BINARY | RRF_RT_REG_DWORD, NULL, (LPDWORD)&value, &BufferSize);
	
	// RegGetValueW ����, ���� ���
	if(result==ERROR_SUCCESS){
		strcpy(buf, "SUCCESS");
		strcpy(msg, " RegGetValueW : SUCCESS");
	}else{
		strcpy(msg, " RegGetValueW : FAIL");
		result = FALSE;
	}
	
	wresult(__FILE__, __LINE__, "RegGetValueW", buf, "SUCCESS", msg);
	return result;
}


/**
* LONG WINAPI RegLoadKey(
  _In_     HKEY    hKey,
  _In_opt_ LPCTSTR lpSubKey,
  _In_     LPCTSTR lpFile
  );
* HKEY_USERS �Ǵ� HKEY_LOCAL_MACHINE �Ʒ��� ����Ű�� �����ϰ� ����Ű ���� Ư�� key hive �����͸� �ε���.
* @author : �ճ���
*
* @param hKey ������ ������Ʈ�� Ű �ڵ�. HKEY_USERS �Ǵ� HKEY_LOCAL_MACHINE �̰ų� RegConnectRegistry�� ��ȯ.
* @param lpSubKey ���� �Ǵ� �����ϴ� ����Ű��.
* @param lpFile ������Ʈ�� �����Ͱ� ����ִ� ���� �̸�. RegSaveKey�� ���� ���� �����̾�� ��. ������ ������ �̸����� ������ �ۼ���.
* @return �ε� ����/���� ����.
*/

BOOL test_RegLoadKeyA(){

	#ifdef OQADBGPRINT
	printf("test_RegLoadKeyA \n");
	#endif

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	LONG result = FALSE;
    HANDLE proccessHandle = GetCurrentProcess();     // get the handle to the current proccess
    DWORD typeOfAccess = TOKEN_ADJUST_PRIVILEGES;   //  requiered to enable or disable the privilege
    HANDLE tokenHandle;                             //  handle to the opened access token

    HKEY hKey = HKEY_LOCAL_MACHINE;
    LPSTR lpSubKey = "NAYOUNG_API_1";
    LPSTR lpFile = "C:\\load4.reg";

    if (OpenProcessToken(proccessHandle, typeOfAccess, &tokenHandle)){
        // Enabling RESTORE and BACKUP privileges
        SetPrivilege(tokenHandle, SE_RESTORE_NAME , TRUE);
        SetPrivilege(tokenHandle, SE_BACKUP_NAME , TRUE);

    }else{
       // wprintf(L"Error getting the access token.\n");
    }

	result = RegLoadKeyA(hKey, lpSubKey, lpFile);

    if (result == ERROR_SUCCESS){
		sprintf(msg, "RegLoadKeyA() : SUCCESS");
		strcpy(buf, "SUCCESS");
		result = TRUE;

    }else{
        strcpy(msg, " RegLoadKeyA() : FAIL \n\n Error Message :");
	}

	wresult(__FILE__, __LINE__, "RegLoadKeyA", buf, "SUCCESS", msg);
    return result;
}


/**
* LONG WINAPI RegLoadKey(
  _In_     HKEY    hKey,
  _In_opt_ LPCTSTR lpSubKey,
  _In_     LPCTSTR lpFile
  );
* HKEY_USERS �Ǵ� HKEY_LOCAL_MACHINE �Ʒ��� ����Ű�� �����ϰ� ����Ű ���� Ư�� key hive �����͸� �ε���.
* @author : �ճ���
*
* @param hKey ������ ������Ʈ�� Ű �ڵ�. HKEY_USERS �Ǵ� HKEY_LOCAL_MACHINE �̰ų� RegConnectRegistry�� ��ȯ.
* @param lpSubKey ���� �Ǵ� �����ϴ� ����Ű��.
* @param lpFile ������Ʈ�� �����Ͱ� ����ִ� ���� �̸�. RegSaveKey�� ���� ���� �����̾�� ��. ������ ������ �̸����� ������ �ۼ���.
* @return �ε� ����/���� ����.
*/

BOOL test_RegLoadKeyW(){

	#ifdef OQADBGPRINT
	printf("test_RegLoadKeyW \n");
	#endif

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	LONG result = FALSE;
    HANDLE proccessHandle = GetCurrentProcess();     // get the handle to the current proccess
    DWORD typeOfAccess = TOKEN_ADJUST_PRIVILEGES;   //  requiered to enable or disable the privilege
    HANDLE tokenHandle;                             //  handle to the opened access token

    HKEY hKey = HKEY_LOCAL_MACHINE;
    LPCWSTR lpSubKey = L"NAYOUNG_API_1";
    LPCWSTR lpFile = L"C:\\load4.reg";

     if (OpenProcessToken(proccessHandle, typeOfAccess, &tokenHandle)){
        // Enabling RESTORE and BACKUP privileges
        SetPrivilege(tokenHandle, SE_RESTORE_NAME , TRUE);
        SetPrivilege(tokenHandle, SE_BACKUP_NAME , TRUE);

    }else{
       // wprintf(L"Error getting the access token.\n");
    }

	result = RegLoadKeyW(hKey, lpSubKey, lpFile);

    if (result == ERROR_SUCCESS){
		sprintf(msg, "RegLoadKeyW() : SUCCESS");
		strcpy(buf, "SUCCESS");
		result = TRUE;

    }else{
        strcpy(msg, " RegLoadKeyW() : FAIL");
	}

	wresult(__FILE__, __LINE__, "RegLoadKeyW", buf, "SUCCESS", msg);
    return result;
}


/**
* LONG WINAPI RegNotifyChangeKeyValue (
  _In_HKEY hKey,
  _In_ BOOL bWatchSubtree,
  _In_ DWORD dwNotifyFilter,
  _In_opt_ HANDLE hEvent,
  _In_ BOOL fAsynchronous
  );
* ������ ������Ʈ�� Ű�� �Ӽ� �Ǵ� ���뿡 ���� ���� ������ ȣ���ڿ��� �˸�
* @author : �ճ���
*
* @param hKey ������ ������Ʈ�� Ű �ڵ�. HKEY_USERS �Ǵ� HKEY_LOCAL_MACHINE �̰ų� RegConnectRegistry�� ��ȯ.
* @param bWatchSubtree �� �Ű� ������ TRUE�̸� �Լ��� ������ Ű�� ���� Ű�� ���� ������ ����. �Ű� ������ FALSE �� ��� �Լ��� ������ Ű������ ���� ������ ����.
* @param dwNotifyFilter �����ؾ� �� ���� ������ ��Ÿ���� ��. 5����.
* @param hEvent fAsynchronous�� TRUE�� ��� ��ȯ, FALSE�� ����.
* @param fAsynchronous  TRUE�� ��� ��ȯ, FALSE�� ������ �߻��� ������ ��ȯ X.
*/

BOOL test_RegNotifyChangeKeyValue(){

	#ifdef OQADBGPRINT
	printf("test_RegNotifyChangeKeyValue \n");
	#endif

	HKEY newKey;
	LONG result = FALSE;
	HANDLE hEvent = NULL;
	DWORD regFilter = NULL;
	HKEY hKey = HKEY_CURRENT_USER;

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	// Registry ����
	result = RegCreateKeyExW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL);
	if(result != ERROR_SUCCESS){
		strcpy(msg, " ������Ʈ�� CREATE ����");
		result = FALSE;
	}

	regFilter = REG_NOTIFY_CHANGE_NAME | REG_NOTIFY_CHANGE_ATTRIBUTES | REG_NOTIFY_CHANGE_LAST_SET | REG_NOTIFY_CHANGE_SECURITY;
	// REG_NOTIFY_CHANGE_NAME - ������Ʈ�� Ű�� ����, ����, �߰��� �Ǵ� ���
	// REG_NOTIFY_CHANGE_ATTRIBUTES - ������Ʈ�� Ű�� �Ӽ��� ����Ǵ� ��� (�����Ѽ��� ��)
	// REG_NOTIFY_CHANGE_LAST_SET - ������Ʈ���� �����ϰ� �ִ� ���
	// REG_NOTIFY_CHANGE_SECURITY -  ������Ʈ�� ��� ���� ������ ����Ǵ� ���

	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	// �ӽ÷� 5�� ������ �ݺ��ǵ��� ��.
	for(int i=0; i < 1; ++i) {
		result = RegNotifyChangeKeyValue(newKey, true, regFilter, hEvent, true);

		if (result != ERROR_SUCCESS) {
			strcpy(msg, " RegNotifyChangeKeyValue() : FAIL");

			return -1;
		}else{ //result == ERROR_SUCCESS
			strcpy(buf, "SUCCESS");
			strcpy(msg, " RegNotifyChangeKeyValue() : SUCCESS");

			result = TRUE;
		}

		wresult(__FILE__, __LINE__, "RegNotifyChangeKeyValue", buf, "SUCCESS", msg);

	}

	RegCloseKey(hKey);
	CloseHandle(hEvent);

	return result;
}


/**
* LONG WINAPI RegOpenCurrentUser(
  _In_  REGSAM samDesired,
  _Out_ PHKEY  phkResult
  );
* ���� �����尡 �����ϰ��ִ� ������� HKEY_CURRENT_USER Ű�� ���� �ڵ��� ������
* @author : �ճ���
*
* @param samDesired Ű�� ���� ���ϴ� �׼��� ������ �����ϴ� ����ũ. Ű�� ���� �����ڰ� ȣ�� ���μ����� ���� ��û �� �׼����� ������� ������ �Լ��� ����.
* @param phkResult ���� Ű�� �ڵ����޴� ������ ���� ������. ��ȯ �� �ڵ��� �� �̻� �ʿ����� ������ RegCloseKey �Լ��� ȣ���Ͽ� �ڵ� �ݱ�.
* @return �������� ����/���� ����.
*/

BOOL test_RegOpenCurrentUser(){

	#ifdef OQADBGPRINT
	printf("test_RegOpenCurrentUser \n");
	#endif

	HKEY keyCurrentUser;

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	// KEY_READ : Combination of KEY_QUERY_VALUE(���� Ű �����͸� ���� ����), 
	// KEY_ENUMERATE_SUB_KEYS(���� Ű ����) and KEY_NOTIFY(���� ����) 
	LONG result = RegOpenCurrentUser(KEY_READ, &keyCurrentUser);

	if(result==ERROR_SUCCESS){
		strcpy(msg, " RegOpenCurrentUser : SUCCESS");
		strcpy(buf, "SUCCESS");
		result = TRUE;

	}else{
		strcpy(msg, " RegOpenCurrentUser : FAIL");
	}

	RegCloseKey(keyCurrentUser);

	wresult(__FILE__, __LINE__, "RegOpenCurrentUser", buf, "SUCCESS", msg);
	return result;
}


/**
* LONG WINAPI RegOpenKeyEx(
  _In_     HKEY    hKey,
  _In_opt_ LPCTSTR lpSubKey,
  _In_     DWORD   ulOptions,
  _In_     REGSAM  samDesired,
  _Out_    PHKEY   phkResult
  );
* Ư�� ������Ʈ�� Ű ����
* @param hKey ������ ������Ʈ�� Ű �ڵ�. HKEY_USERS �Ǵ� HKEY_LOCAL_MACHINE �̰ų� RegConnectRegistry�� ��ȯ.
* @param lpSubKey ���� �Ǵ� �����ϴ� ����Ű��.
* @param ulOptions Ű�� ������ �� ������ �ɼ� - REG_OPTION_OPEN_LINK
* @param samDesired Ű�� ���� ���ϴ� �׼��� ������ �����ϴ� ����ũ. Ű�� ���� �����ڰ� ȣ�� ���μ����� ���� ��û �� �׼����� ������� ������ �Լ��� ����.
* @param phkResult ���� Ű�� �ڵ����޴� ������ ���� ������. ��ȯ �� �ڵ��� �� �̻� �ʿ����� ������ RegCloseKey �Լ��� ȣ���Ͽ� �ڵ� �ݱ�.
* @return Ű ���� ����/���� ����
*/

BOOL test_RegOpenKeyExW(){

	#ifdef OQADBGPRINT
	printf("test_RegOpenKeyExW\n");
	#endif

	HKEY newKey;
	LONG result = FALSE;
	HKEY hKey = HKEY_CURRENT_USER;

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",&newKey);

	if(result == ERROR_SUCCESS){
		result = RegOpenKeyExW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);

		if(result == ERROR_SUCCESS){
			strcpy(buf, "SUCCESS");
			strcpy(msg, " RegOpenKeyEx() : SUCCESS");
			result = TRUE;

		}else
			strcpy(msg, " RegOpenKeyEx() : FAIL");

	}else{
		strcpy(msg, " ������Ʈ�� ���� ���� \n\n RegCreateKeyEx�Լ��� �ٽ� Ȯ���Ͻʽÿ�.");
	}

	// �ڵ� �ݱ�.
	RegCloseKey(hKey);

	wresult(__FILE__, __LINE__, "RegOpenKeyExW", buf, "SUCCESS", msg);
	return result;
}


/**
* LONG WINAPI RegOpenKeyEx(
  _In_     HKEY    hKey,
  _In_opt_ LPCTSTR lpSubKey,
  _Out_    PHKEY   phkResult
  );
* Ư�� ������Ʈ�� Ű ����
* @param hKey ������ ������Ʈ�� Ű �ڵ�. HKEY_USERS �Ǵ� HKEY_LOCAL_MACHINE �̰ų� RegConnectRegistry�� ��ȯ.
* @param lpSubKey ���� �Ǵ� �����ϴ� ����Ű��.
* @param phkResult ���� Ű�� �ڵ����޴� ������ ���� ������. ��ȯ �� �ڵ��� �� �̻� �ʿ����� ������ RegCloseKey �Լ��� ȣ���Ͽ� �ڵ� �ݱ�.
* @return Ű ���� ����/���� ����
*/

BOOL test_RegOpenKeyW(){

	#ifdef OQADBGPRINT
	printf("test_RegOpenKeyW\n");
	#endif

	HKEY newKey;
	LONG result = FALSE;
	HKEY hKey = HKEY_CURRENT_USER;

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",&newKey);
	if(result != ERROR_SUCCESS){
		strcpy(msg, " ������Ʈ�� CREATE ����");
		result = FALSE;
	}

	result = RegOpenKeyW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position", &newKey);
	if(result == ERROR_SUCCESS){
		strcpy(buf, "SUCCESS");
		strcpy(msg, " RegOpenKeyW() : SUCCESS");
		result = TRUE;

	}else{
		strcpy(msg, " RegOpenKeyW() : FAIL");
		result = FALSE;
	}

	// �ڵ� �ݱ�.
	RegCloseKey(hKey);

	wresult(__FILE__, __LINE__, "RegOpenKeyW", buf, "SUCCESS", msg);
	return result;
}


/**
* LONG WINAPI RegOpenUserClassesRoot(
  _In_       HANDLE hToken,
  _Reserved_ DWORD  dwOptions,
  _In_       REGSAM samDesired,
  _Out_      PHKEY  phkResult
  );
* ������ ����ڿ� ���� HKEY_CLASSES_ROOT Ű�� ���� �ڵ��� ������.
* @author : �ճ���
*
* @param hToken ����ڸ� �ĺ��ϴ� primary �Ǵ� impersonation �׼��� ��ū�� ���� �ڵ�.
* @param dwOptions ������ 0
* @param samDesired Ű�� ���� ���ϴ� �׼��� ������ �����ϴ� ����ũ. Ű�� ���� �����ڰ� ȣ�� ���μ����� ���� ��û �� �׼����� ������� ������ �Լ��� ����.
* @param phkResult ���� Ű�� �ڵ����޴� ������ ���� ������. ��ȯ �� �ڵ��� �� �̻� �ʿ����� ������ RegCloseKey �Լ��� ȣ���Ͽ� �ڵ� �ݱ�.
* @return �������� ����/���� ����
*/

BOOL test_RegOpenUserClassesRoot(){

	#ifdef OQADBGPRINT
	printf("test_RegOpenUserClassesRoot \n");
	#endif

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	HANDLE proccessHandle = GetCurrentProcess();     // get the handle to the current proccess
	DWORD typeOfAccess = TOKEN_QUERY;   //  requiered to enable or disable the privilege
	HANDLE tokenHandle;                             //  handle to the opened access token

	HKEY newKey;
	LONG result = FALSE;

	if (OpenProcessToken(proccessHandle, typeOfAccess, &tokenHandle) != 0){

		result = RegOpenUserClassesRoot(tokenHandle, 0, KEY_ALL_ACCESS, &newKey);

		if(result == ERROR_SUCCESS){
			strcpy(buf, "SUCCESS");
			strcpy(msg, " RegOpenUserClassesRoot : SUCCESS");
			result = TRUE;

		}else{
			strcpy(msg, " RegOpenUserClassesRoot : FAIL");
			result = FALSE;
		}
	}else
		strcpy(msg, " OpenProcessToken() ������ \n\n process�� ������ Access Token�� �ٽ� ���ʽÿ� ");

	wresult(__FILE__, __LINE__, "RegOpenUserClassesRoot", buf, "SUCCESS", msg);
	return result;
}


/**
* LONG WINAPI RegQueryInfoKey(
  _In_        HKEY      hKey,
  _Out_opt_   LPTSTR    lpClass,
  _Inout_opt_ LPDWORD   lpcClass,
  _Reserved_  LPDWORD   lpReserved,
  _Out_opt_   LPDWORD   lpcSubKeys,
  _Out_opt_   LPDWORD   lpcMaxSubKeyLen,
  _Out_opt_   LPDWORD   lpcMaxClassLen,
  _Out_opt_   LPDWORD   lpcValues,
  _Out_opt_   LPDWORD   lpcMaxValueNameLen,
  _Out_opt_   LPDWORD   lpcMaxValueLen,
  _Out_opt_   LPDWORD   lpcbSecurityDescriptor,
  _Out_opt_   PFILETIME lpftLastWriteTime
 );
* Ư�� ������Ʈ�� Ű�� ���� ������ ������.
* @author : �ճ���
*
* @param hKey ������ ������Ʈ�� Ű �ڵ�. HKEY_USERS �Ǵ� HKEY_LOCAL_MACHINE �̰ų� RegConnectRegistry�� ��ȯ.
* @param lpClass Ű�� ����� ���� Ŭ�������޴� ���ۿ� ���� ������. NULL ����. 
* @param lpcClass lpClass �Ű� ������ ����Ű�� ������ ũ�� �� ���ڷ� ��Ÿ�� ���� �� ���� ������. NULL�̸� ���� �Լ��� ERROR_INVALID_PARAMETER ��ȯ.
* @param lpReserved ������ NULL.
* @param lpcSubKeys ������ Ű�� ���� �� ���� Ű �����޴� ������ ���� ������. NULL ����.
* @param lpcMaxSubKeyLen ���� �� �̸��� ���� Ű�� ���� Ű ũ�⸦ ���� �ڵ� ���ڷ� �����ϰ� ���� null ���ڸ� �������� �ʴ� ������ ���� ������. NULL ����.
* @param lpcMaxClassLen ���� �ڵ� ���ڷ� ���� Ű Ŭ������ �����ϴ� ���� �� ���ڿ��� ũ�⸦�޴� ������ ���� ������. NULL ����.
* @param lpcValues Ű�� ������ ���� �����޴� ������ ���� ������. NULL ����.
* @param lpcMaxValueNameLen Ű�� ���� �� �� �̸��� ũ�⸦ ���� �ڵ� ���ڷι޴� ������ ���� ������. NULL ����. 
* @param lpcMaxValueLen Ű�� �� �߿��� ���� �� ������ ���� ����� ũ�� (����Ʈ)���޴� ������ ���� ������. �̤Ť�= ==������
* @param lpcbSecurityDescriptor
* @param lpftLastWriteTime
* @return ������ �������� ����/���� ����.
*/

BOOL test_RegQueryInfoKeyW(){

	#ifdef OQADBGPRINT
	printf("test_RegQueryInfoKeyW \n");
	#endif

	#define MAX_KEY_LENGTH 255
	#define MAX_VALUE_NAME 16383

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";
	
	LONG result = FALSE;
	HKEY newKey = 0;
	HKEY hKey = HKEY_CURRENT_USER;
	DWORD cSubKeys, cValues;
	
	RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",&newKey);
	RegOpenKeyW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position", &newKey);

	// Ű�� ���� ����Ű�� ���� ���� ����
	
	result=	RegQueryInfoKeyW(hKey,NULL,NULL,NULL,&cSubKeys,NULL,NULL,&cValues,NULL,NULL,NULL,NULL);
			
	if(result == ERROR_SUCCESS){
		strcpy(buf, "SUCCESS");
		strcpy(msg, "RegQueryInfoKeyW : SUCCESS");
		result = TRUE;

	}else if(result == ERROR_MORE_DATA){
		strcpy(msg, "RegQueryInfoKeyW : FAIL \n\n lpClass buffer�� Ŭ������ �̸��� �ޱ⿡�� �ʹ� �۽��ϴ�.");
		result = FALSE;

	}else{
		strcpy(msg, "RegQueryInfoKeyW : FAIL \n\n Error Code : %d");
		result = FALSE;
	}

	wresult(__FILE__, __LINE__, "RegQueryInfoKeyW", buf, "SUCCESS", msg);
	return result;
}


/**
* LONG WINAPI RegQueryValueEx(
  _In_        HKEY    hKey,
  _In_opt_    LPCTSTR lpValueName,
  _Reserved_  LPDWORD lpReserved,
  _Out_opt_   LPDWORD lpType,
  _Out_opt_   LPBYTE  lpData,
  _Inout_opt_ LPDWORD lpcbData
  );
* ���µ� ������Ʈ�� Ű�� ����� Ư�� �� �̸��� Ÿ�԰� �����͸� ������.
* @author : �ճ���
*
* @param hKey hKey ������ ������Ʈ�� Ű �ڵ�. HKEY_USERS �Ǵ� HKEY_LOCAL_MACHINE �̰ų� RegConnectRegistry�� ��ȯ.
* @param lpValueName ������Ʈ�� ���� �̸�.
* @param lpReserved ������ NULL.
* @param lpType ������ ���� ����� ������ ������ ��Ÿ���� �ڵ带 �����ϴ� ������ ���� ������.
* @param lpData ���� �����͸��޴� ���ۿ� ���� ������. NULL ����.
* @param lpcbData lpData �Ű� ������ ����Ű�� ���� ũ�� �� ����Ʈ ������ �����ϴ� ������ ���� ������. NULL�� ��쿡�� lpData NULL.
* @return �������� ����/���� ����
*/

BOOL test_RegQueryValueExW(){ 

	#ifdef OQADBGPRINT
	printf("test_RegQueryValueExW \n");
	#endif

	RECT rt;
	DWORD Size;
	HKEY newKey;
	HKEY hKey = HKEY_CURRENT_USER;
	LONG result = FALSE;

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	Size=sizeof(LONG);

	result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",&newKey);
	if(result != ERROR_SUCCESS){
		strcpy(msg, " ������Ʈ�� CREATE ����");
		result = FALSE;
	}

	result = RegSetValueExW(newKey, L"Top",0,REG_DWORD,(LPBYTE)&rt.top,sizeof(LONG)); // ���� set.
	if(result != ERROR_SUCCESS){ 
		strcpy(msg, " ������Ʈ�� SET ����");
		result = FALSE;
	}

	result = RegQueryValueExW(newKey, L"Top", 0, NULL,(LPBYTE)&rt.left, &Size);
	if(result == ERROR_SUCCESS){
		strcpy(buf, "SUCCESS");
		strcpy(msg, "RegQueryValueExW : SUCCESS");
		result = TRUE;

	}else{
		strcpy(msg, "RegQueryValueExW : FAIL");
		result = FALSE;
	}

	RegCloseKey(newKey);
	wresult(__FILE__, __LINE__, "RegQueryValueExW", buf, "SUCCESS", msg);

	return result;
}


/**
* LONG WINAPI RegSaveKeyEx(
  _In_     HKEY                  hKey,
  _In_     LPCTSTR               lpFile,
  _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  _In_     DWORD                 Flags
 );
* Ư�� ���˿���, Ư�� Ű�� ����Ű�� ��� �͵�, �׸��� ������Ʈ�� ������ ������ save.
* @author : �ճ���
*
* @param hKey ���µ� ������Ʈ���� �ڵ�.
* @param lpFile �̸� ���ǵ� HKEY_CLASSES_ROOT Ű�� �������� ����.
* @param lpSecurityAttributes ������ Ű�� ���� Ű�� ������ ������ �̸��Դϴ�. ������ �̹� ������ �Լ��� �����մϴ�.
* @param Flags ����� Ű �Ǵ� ���̺� ����. 3����.
* @return save ����/���� ����.
*/

BOOL test_RegSaveKeyExA(){

	#ifdef OQADBGPRINT
	printf("test_RegSaveKeyExA \n");
	#endif

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	HKEY hKey = HKEY_CURRENT_USER;
	HKEY newKey;
	LONG result = FALSE;

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

	// RegSaveKeyEx ���� ��, ������ �̹� ������ �� ��° �Ķ������ ������ �����ϹǷ� �ݵ�� ����.
	// ������ Ȥ�� ����� �������� �ʾ��� ���� ������ ���� �ٽ�.
	DeleteFileA(lpFile);

	result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",&newKey);
	if(result != ERROR_SUCCESS){
		strcpy(msg, " ������Ʈ�� CREATE ����");
		result = FALSE;
	}

	result = RegSaveKeyExA(newKey, lpFile, NULL, REG_LATEST_FORMAT);
	if (result == ERROR_SUCCESS){
		strcpy(msg, "RegSaveKeyExA() : SUCCESS");
		strcpy(buf, "SUCCESS");
		
	}else{
		strcpy(msg, " RegSaveKeyExA() : FAIL");

		return FALSE;
	}

	// ���� RegSaveKeyEx ���� ��, ������ �̹� ������ �� ��° �Ķ������ ������ �����ϹǷ� �ݵ�� ����.
	DeleteFileA(lpFile);
	RegCloseKey(hKey);

	wresult(__FILE__, __LINE__, "RegSaveKeyExA", buf, "SUCCESS", msg);
	return true;
}


/**
* LONG WINAPI RegSaveKeyEx(
  _In_     HKEY                  hKey,
  _In_     LPCTSTR               lpFile,
  _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  _In_     DWORD                 Flags
 );
* Ư�� ���˿���, Ư�� Ű�� ����Ű�� ��� �͵�, �׸��� ������Ʈ�� ������ ������ save.
* @author : �ճ���
*
* @param hKey ���µ� ������Ʈ���� �ڵ�.
* @param lpFile �̸� ���ǵ� HKEY_CLASSES_ROOT Ű�� �������� ����.
* @param lpSecurityAttributes ������ Ű�� ���� Ű�� ������ ������ �̸��Դϴ�. ������ �̹� ������ �Լ��� �����մϴ�.
* @param Flags ����� Ű �Ǵ� ���̺� ����. 3����.
* @return save ����/���� ����.
*/

BOOL test_RegSaveKeyExW(){

	#ifdef OQADBGPRINT
	printf("test_RegSaveKeyExW \n");
	#endif

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	HKEY hKey = HKEY_CURRENT_USER;
	HKEY newKey;
	LONG result = FALSE;

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

	// RegSaveKeyEx ���� ��, ������ �̹� ������ �� ��° �Ķ������ ������ �����ϹǷ� �ݵ�� ����.
	// ������ Ȥ�� ����� �������� �ʾ��� ���� ������ ���� �ٽ�.
	DeleteFileW(lpFile);

	result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",&newKey);
	if(result != ERROR_SUCCESS){
		strcpy(msg, " ������Ʈ�� CREATE ����");
		result = FALSE;
	}

	result = RegSaveKeyExW(newKey, lpFile, NULL, REG_LATEST_FORMAT);
	if (result == ERROR_SUCCESS){
		strcpy(msg, "RegSaveKeyExW() : SUCCESS");
		strcpy(buf, "SUCCESS");
		
	}else{
		strcpy(msg, " RegSaveKeyExW() : FAIL");

		return FALSE;
	}

	// ���� RegSaveKeyEx ���� ��, ������ �̹� ������ �� ��° �Ķ������ ������ �����ϹǷ� �ݵ�� ����.
	DeleteFileW(lpFile);
	RegCloseKey(hKey);

	wresult(__FILE__, __LINE__, "RegSaveKeyExW", buf, "SUCCESS", msg);
	return true;
}


/**
* LONG WINAPI RegSetKeySecurity(
  _In_ HKEY                 hKey,
  _In_ SECURITY_INFORMATION SecurityInformation,
  _In_ PSECURITY_DESCRIPTOR pSecurityDescriptor
  );
* ���µ� ������Ʈ�� Ű�� ���� ����
* @author : �ճ���
*
* @param hKey ���µ� ������Ʈ���� �ڵ�.
* @param SecurityInformation ������ ���� ������ ������ ��Ÿ���� ��Ʈ �÷��� ��Ʈ. SECURITY_INFORMATION ��Ʈ �÷��� �� ���� ����. 
* @param pSecurityDescriptor ������ Ű�� ������ ���� �Ӽ� �� ���� �ϴ� SECURITY_DESCRIPTOR ����ü�� ���� ������.
* @return  ���� ���� ����/���� ����.
*/

BOOL test_RegSetKeySecurity(){

	#ifdef OQADBGPRINT
	printf("test_RegSetKeySecurity\n");
	#endif

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	LONG result = FALSE;
	HKEY hKey = HKEY_CURRENT_USER;
	PSECURITY_DESCRIPTOR psdNew;
	SECURITY_INFORMATION si = DACL_SECURITY_INFORMATION;
	DWORD dwSdSizeNeeded = 1000;

	//hKey ���� ����.(R)
	RegGetKeySecurity(hKey, si, &psdNew, &dwSdSizeNeeded);
	result = RegSetKeySecurity(hKey, si, &psdNew);

	if(result == ERROR_SUCCESS){
		strcpy(buf, "SUCCESS");
		sprintf(msg, " RegSetKeySecurity() : SUCCESS");

	}else if(result == ERROR_INSUFFICIENT_BUFFER){
		sprintf(msg, " RegSetKeySecurity() : FAIL \n\n Buffer�� ũ�Ⱑ �ʹ� �۽��ϴ�.");
		result = FALSE;

	}else{
		strcpy(msg, "RegSetKeySecurity() : FAIL");
		result = FALSE;
	}

	// �ݾ���� ��.
	RegCloseKey(hKey);
	wresult(__FILE__, __LINE__, "RegSetKeySecurity", buf, "SUCCESS", msg);

	return result;
}


/**
* LONG WINAPI RegSetValueEx(
  _In_             HKEY    hKey,
  _In_opt_         LPCTSTR lpValueName,
  _Reserved_       DWORD   Reserved,
  _In_             DWORD   dwType,
  _In_       const BYTE    *lpData,
  _In_             DWORD   cbData
  );
* ������Ʈ�� Ű �Ʒ��� Ư�� ���� ������ �� Ÿ���� ����.
* @author : �ճ���
*
* @param hKey ������ ������Ʈ�� Ű �ڵ�. ���� Ű ��Ͽ��� ���� ����.
* @param lpValueName ������ �� �̸�.
* @param Reserved ������ 0.
* @param dwType lpData �Ű������� ����Ű�� ������ ����.
* @param *lpData ������ ������.
* @param cbData lpData �Ű������� ����Ű�� ������ ũ��. ����Ʈ. 
* @return ���� ����/���� ����.
*/

BOOL test_RegSetValueExW(){ 

	#ifdef OQADBGPRINT
	printf("test_RegSetValueExW \n");
	#endif

	RECT rt;
	HKEY newKey;
	HKEY hKey = HKEY_CURRENT_USER;
	LONG result = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",&newKey);
	if(result != ERROR_SUCCESS){
		strcpy(msg, " ������Ʈ�� CREATE ����");
		result = FALSE;
	}

	result = RegSetValueExW(newKey, L"Top",0,REG_DWORD,(LPBYTE)&rt.top,sizeof(LONG)); // ���� set.
	if(result == ERROR_SUCCESS){ 
		strcpy(buf, "SUCCESS");
		strcpy(msg, " RegSetValueExw : SUCCESS");
		result = TRUE;

	}else{
		strcpy(msg, " RegSetValueExw : FAIL");
		result = FALSE;	
	}

	// �ݾ���� ��.
	RegCloseKey(hKey);
	wresult(__FILE__, __LINE__, "RegSetValueExW", buf, "SUCCESS", msg);

	return result;
}


/**
* LONG WINAPI RegUnLoadKey(
  _In_     HKEY    hKey,
  _In_opt_ LPCTSTR lpSubKey
 );
* ������Ʈ���� ����Ű�� Ư�� Ű�� ��ε�
* @author : �ճ���
*
* @param hKey ��ε� �� Ư�� Ű�� �ڵ�. HKEY_LOCAL_MACHINE �Ǵ� HKEY_USERS ����.
* @param lpSubKey ��ε��� ����Ű �̸�.
* @return ��ε� ����/���� ����.
*/

BOOL test_RegUnLoadKeyA(){

	#ifdef OQADBGPRINT
	printf("test_RegUnLoadKeyA \n");
	#endif

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	HANDLE proccessHandle = GetCurrentProcess();     // get the handle to the current proccess
	DWORD typeOfAccess = TOKEN_ADJUST_PRIVILEGES;   //  requiered to enable or disable the privilege
	HANDLE tokenHandle;                             //  handle to the opened access token

	LONG result = FALSE;
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

	// �ε� ����.
	result = RegLoadKeyA(hKey, subKeyName, pHive);
	if(result == ERROR_SUCCESS){

		result = RegUnLoadKeyA(hKey, subKeyName);
		if (result == ERROR_SUCCESS){
			strcpy(msg, "RegUnLoadKeyA() : SUCCESS");
			strcpy(buf, "SUCCESS");
			result = TRUE;

		}else{
			strcpy(msg, " RegUnLoadKeyA() : FAIL");
			result = FALSE;
		}

	}else{
		strcpy(msg, " Registry Load�� �����߽��ϴ�. \n RegLoadKeyA �Լ��� �ٽ� Ȯ���Ͻʽÿ�,");
		result = FALSE;
	}

	wresult(__FILE__, __LINE__, "RegUnLoadKeyA", buf, "SUCCESS", msg);
	return result;
}


/**
* LONG WINAPI RegUnLoadKey(
  _In_     HKEY    hKey,
  _In_opt_ LPCTSTR lpSubKey
 );
* ������Ʈ���� ����Ű�� Ư�� Ű�� ��ε�
* @author : �ճ���
*
* @param hKey ��ε� �� Ư�� Ű�� �ڵ�. HKEY_LOCAL_MACHINE �Ǵ� HKEY_USERS ����.
* @param lpSubKey ��ε��� ����Ű �̸�.
* @return ��ε� ����/���� ����.
*/

BOOL test_RegUnLoadKeyW(){
	
	#ifdef OQADBGPRINT
	printf("test_RegUnLoadKeyW \n");
	#endif

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	HANDLE proccessHandle = GetCurrentProcess();     // get the handle to the current proccess
	DWORD typeOfAccess = TOKEN_ADJUST_PRIVILEGES;   //  requiered to enable or disable the privilege
	HANDLE tokenHandle;                             //  handle to the opened access token

	LONG result = FALSE;
	HKEY hKey = HKEY_LOCAL_MACHINE;
	LPCWSTR subKeyName = L"NAYOUNG_API_PPT";
	LPCWSTR pHive = L"C:\\test_RegUnLoadKeyA.reg";

	if (OpenProcessToken(proccessHandle, typeOfAccess, &tokenHandle)){
		// Enabling RESTORE and BACKUP privileges
		SetPrivilege(tokenHandle, SE_RESTORE_NAME, TRUE);
		SetPrivilege(tokenHandle, SE_BACKUP_NAME, TRUE);

	}else{
		//wprintf(L"Error getting the access token.\n");
	}

	// �ε� ����.
	result = RegLoadKeyW(hKey, subKeyName, pHive);
	if(result == ERROR_SUCCESS){

		result = RegUnLoadKeyW(hKey, subKeyName);
		if (result == ERROR_SUCCESS){
			strcpy(msg, "RegUnLoadKeyW() : SUCCESS");
			strcpy(buf, "SUCCESS");
			result = TRUE;

		}else{
			strcpy(msg, " RegUnLoadKeyW() : FAIL");
			result = FALSE;
		}

	}else{
		strcpy(msg, " Registry Load�� �����߽��ϴ�. \n RegUnLoadKeyW �Լ��� �ٽ� Ȯ���Ͻʽÿ�,");
		result = FALSE;
	}

	wresult(__FILE__, __LINE__, "RegUnLoadKeyW", buf, "SUCCESS", msg);
	return result;
}


/**
BOOL test_RegRestoreKeyA(){

	#ifdef OQADBGPRINT
	printf("test_RegRestoreKeyA \n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

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
				sprintf(msg, "RegRestoreKeyA() : SUCCESS");
				strcpy(buf, "SUCCESS");
			}else{
				printf("%d", GetLastError());
				strcpy(msg, GetErrorMessage(" RegRestoreKeyA() : FAIL \n\n Error Message :", GetLastError()));
			}
		}else{
			strcpy(msg, GetErrorMessage(" Registry Key ���� ���� \n\n RegOpenKeyEx �Լ��� �ٽ� Ȯ���ϼ���", GetLastError()));
		}
	}else
		strcpy(msg, GetErrorMessage(" Registry Key ���� ���� \n\n RegCreateKey �Լ��� �ٽ� Ȯ���ϼ���", GetLastError()));

	wresult(__FILE__, __LINE__, "RegRestoreKeyA", buf, "SUCCESS", msg);

	DeleteFileA(lpFile);
	RegCloseKey(hKey);

	return true;

}
*/

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

/**
BOOL test_RegRestoreKeyA(){

#ifdef OQADBGPRINT
	printf("test_RegRestoreKeyA \n");
#endif

	/** �� ��° �Ķ���� lpFile : name of the file with the registry information. 
	created by using the RegSaveKey function. 
	�� RegSaveKey(hKey, lpFile, lpSecurityAttributes(NULL�̸� default security descriptor ������))	
	

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";
	int wresult_value = 0;
	LSTATUS result;
	HKEY newKey = 0;
	LPSTR lpFile = "�ճ���\\test_RegSaveKeyExA.reg";

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

	if(RegSaveKeyExA(hKey, lpFile, NULL, REG_LATEST_FORMAT) == ERROR_SUCCESS){

		RegCloseKey(hKey);
		result = RegRestoreKeyA(hKey, lpFile, REG_FORCE_RESTORE);

		if(result == ERROR_SUCCESS){
			wresult_value=1;
			strcpy(msg, "RegRestoreKeyA : SUCCESS");
		}else
			strcpy(msg, "RegRestoreKeyA : FAIL");
	}else
		strcpy(msg, "RegSaveKeyEx���� �ٽ� �Ͻʽÿ�.");
	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegRestoreKeyA", buf, "1", msg);

	RegCloseKey(hKey);
	CloseHandle(tokenHandle);

	return true;
}


BOOL test_RegRestoreKeyW(){

#ifdef OQADBGPRINT
	printf("test_RegRestoreKeyW \n");
#endif
	*/
	/** �� ��° �Ķ���� lpFile : name of the file with the registry information. 
	created by using the RegSaveKey function. 
	�� RegSaveKey(hKey, lpFile, lpSecurityAttributes(NULL�̸� default security descriptor ������))	
	*/
	/**
	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";
	int wresult_value = 0;
	LSTATUS result;
	//HKEY newKey;
	LPCTSTR lpFile = L"�ճ���\\test_RegSaveKeyExA.reg";

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

	if(RegSaveKeyExW(hKey, lpFile, NULL, REG_LATEST_FORMAT) == ERROR_SUCCESS){

		RegCloseKey(hKey);
		//RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",&newKey);
		//RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);
		//RegSaveKeyExA(hKey, lpFile, NULL, REG_LATEST_FORMAT);

		RegCloseKey(hKey);
		result = RegRestoreKeyW(hKey, lpFile, REG_FORCE_RESTORE);

		if(result == ERROR_SUCCESS){
			wresult_value=1;
			strcpy(msg, "RegRestoreKeyW : SUCCESS");
		}else
			strcpy(msg, "RegRestoreKeyW : FAIL");
	}else
		strcpy(msg, "RegSaveKeyEx���� �ٽ� �Ͻʽÿ�.");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegRestoreKeyW", buf, "1", msg);

	RegCloseKey(hKey);
	CloseHandle(tokenHandle);

	return true;
}
*/
/**
//#define UNICODE
//#define _WIN32_WINNT 0x0600 
BOOL test_RegLoadMUIStringA(){

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";
	int wresult_value = 0;

	HKEY hKEY = HKEY_CURRENT_USER;
	LPSTR pszValue = "value";
	LPSTR pszOutBuf = NULL;
	DWORD cbOutBuf = sizeof(pszOutBuf);
	LPDWORD pcbData = &cbOutBuf;
	DWORD flags = REG_MUI_STRING_TRUNCATE;
	//LPCSTR pszDirectory = "C:\\Users\\Tmax\\Desktop\\test";
	LPCSTR pszDirectory = "C:\\";

	LONG result = RegLoadMUIStringA(hKEY, pszValue, pszOutBuf, cbOutBuf, pcbData, flags, pszDirectory);
	DWORD err = GetLastError();

	if(result == ERROR_SUCCESS){
		wresult_value=1;
		strcpy(msg, "RegLoadMUIStringA : SUCCESS");
	}else if(result == ERROR_MORE_DATA)
		strcpy(msg, "RegLoadMUIStringA : FAIL \n\n pcbData�� �ʹ� �۽��ϴ�.");
	else if(result == ERROR_CALL_NOT_IMPLEMENTED)
		strcpy(msg, "RegLoadMUIStringA : FAIL \n\n ANSI version �� ����");
	else
		strcpy(msg, "RegLoadMUIStringA : FAIL");
	
	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegLoadMUIString", buf, "1", msg);

	return true;
}

#include <SubAuth.h>

BOOL test_RegLoadMUIStringW(){
	
	//int wresult_value = 0;
	//char buf[BUFSIZ];
	//char msg[BUFSIZ] = "FAIL";

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
	//	strcpy(msg, "RegLoadMUIStringW : SUCCESS");
	//}else if(result == ERROR_MORE_DATA)
	//	strcpy(msg, "RegLoadMUIStringW : FAIL \n\n pcbData�� �ʹ� �۽��ϴ�.");
	//else if(result == ERROR_CALL_NOT_IMPLEMENTED)
	//	strcpy(msg, "RegLoadMUIStringW : FAIL \n\n ANSI version �� ����");
	//else
	//	strcpy(msg, "RegLoadMUIStringW : FAIL");

	//sprintf(buf, "%d", wresult_value);
	//wresult(__FILE__, __LINE__, "RegLoadMUIStringW", buf, "1", msg);
	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";
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
		strcpy(msg, "RegLoadMUIStringW : SUCCESS");
	}else if(result == ERROR_MORE_DATA)
		strcpy(msg, "RegLoadMUIStringW : FAIL \n\n pcbData�� �ʹ� �۽��ϴ�.");
	else if(result == ERROR_CALL_NOT_IMPLEMENTED)
		strcpy(msg, "RegLoadMUIStringW : FAIL \n\n ANSI version �� ����");
	else
		strcpy(msg, "RegLoadMUIStringW : FAIL");
	
	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegLoadMUIStringW", buf, "1", msg);

	return result;
}  
*/

//#define MAX_KEY_LENGTH 255
//#define MAX_VALUE_NAME 16383
/**
BOOL test_RegEnumValueAs(){

	/**
	//DWORD   cType;
	LSTATUS result;
	HKEY hKey=HKEY_CURRENT_USER;
	//DWORD cchValue = MAX_VALUE_NAME; 

	//int i = 1;
	int wresult_value = 0;
	int err = GetLastError();
	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];
	//char  achValue[MAX_VALUE_NAME]; 
    
	//cchValue = MAX_VALUE_NAME; 
	//achValue[0] = '\0'; 

	TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string 
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
    DWORD    cchClassName = MAX_PATH;  // size of class string 
    DWORD    cSubKeys;               // number of subkeys 
    DWORD    cbMaxSubKey;              // longest subkey size 
    DWORD    cchMaxClass;              // longest class string 
    DWORD    cValues;              // number of values for key 
    DWORD    cchMaxValue;          // longest value name 
    DWORD    cbMaxValueData;       // longest value data 
    DWORD    cbSecurityDescriptor; // size of security descriptor 
    FILETIME ftLastWriteTime;      // last write time 
 
    DWORD i, retCode; 
 
    TCHAR  achValue[MAX_VALUE_NAME]; 
    DWORD cchValue = MAX_VALUE_NAME; 

	HKEY newKey = 0;

	RegCreateKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL);
	RECT rt;

	RegSetValueExW(newKey, L"Top",0,REG_DWORD,(LPBYTE)&rt.top,sizeof(LONG));
	RegSetValueExW(newKey, L"Right",0,REG_DWORD,(LPBYTE)&rt.right,sizeof(LONG));
	RegSetValueExW(newKey, L"Bottom",0,REG_DWORD,(LPBYTE)&rt.bottom,sizeof(LONG));
	RegSetValueExW(newKey, L"Left",0,REG_DWORD,(LPBYTE)&rt.left,sizeof(LONG));

	retCode = RegQueryInfoKey(
        HKEY_CURRENT_USER,                    // key handle 
        achClass,                // buffer for class name 
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime);       // last write time 

	printf("ũ�� : %d", cValues);

	if(retCode == ERROR_SUCCESS)
		printf(" ����");

	if(cValues){
		printf( "\nNumber of values: %d\n", cValues);

		for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++){ 
			result = RegEnumValue(hKey, i, achValue, &cchValue, NULL, NULL,NULL,NULL);

			if(result == ERROR_SUCCESS){
				strcpy(msg, " RegEnumValueA : PASS \n\n �� ��° ���� dwIndex = 0 �� ù ��° ���� RegEnum");
				wresult_value=1;
			}else if(result == ERROR_NO_MORE_ITEMS){
				strcpy(msg, " ����� �� �ִ� ���� �� �̻� �����ϴ�.");
			}else if(result == ERROR_MORE_DATA){
				strcpy(msg, " lpData ���۰� ���� �ޱ⿡ �ʹ� �۽��ϴ�.");
			}else{
				strcpy(msg, "FAIL");
				printf("err : %d" ,err);
			}
		}
	}
	printf("err : %d" ,err);

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegLoadMUIStringW", buf, "1", msg);
	
	return true;
}
*/


//
//BOOL test_RegSetKeySecurity(){
//
//#ifdef OQADBGPRINT
//	printf("test_RegGetKeySecurity\n");
//#endif
//
//	int wresult_value=0;
//	int err = GetLastError();
//
//	char buf[BUFSIZ];
//	char msg[BUFSIZ] = "FAIL";
//
//	LONG result;
//	HKEY newKey;
//	HKEY hKey;
//	DWORD dwSdSizeNeeded;
//	PSECURITY_DESCRIPTOR psdNew = NULL;
//	SECURITY_INFORMATION si = DACL_SECURITY_INFORMATION;
//
//	RegCloseKey(hKey);
//
//	result = RegCreateKey(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",&hKey);
//	if(result != ERROR_SUCCESS){
//		sprintf(msg, " RegCreateKey�Լ��� �ٽ� Ȯ���Ͻʽÿ� \n\n Error Code : %d", err);
//		return FALSE;
//	}
//
//	//�ݵ�� ��������� ��
//	result = RegOpenKeyW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position", &hKey);
//	if(result != ERROR_SUCCESS){
//		sprintf(msg, " RegOpenKeyW�Լ��� �ٽ� Ȯ���Ͻʽÿ� \n\n Error Code : %d", err);
//		//return FALSE;
//	}
//
//	result = RegSetKeySecurity(hKey, si, psdNew);
//
//	if(result == ERROR_SUCCESS){
//		strcpy(buf, "SUCCESS");
//		sprintf(msg, " RegSetKeySecurity() : SUCCESS");
//	}else if(result == ERROR_INSUFFICIENT_BUFFER){
//		sprintf(msg, " RegSetKeySecurity() : FAIL \n\n Buffer�� ũ�Ⱑ �ʹ� �۽��ϴ�.");
//	}else
//		sprintf(msg, GetErrorMessage(" RegSetKeySecurity() : FAIL \n\n Error Code : %s", result));
//
//	RegCloseKey(hKey);
//	wresult(__FILE__, __LINE__, "RegSetKeySecurity", buf, "SUCCESS", msg);
//
//	return result;
//}

/** RegEnumKeyEx �Լ�
LONG RegEnum(HKEY numKey){ 
	
	TCHAR lpSubKey[MAX_PATH];
	DWORD i;
	DWORD Size;
	FILETIME FileTime;

	LONG result;

	RegOpenKeyEx(HKEY_CURRENT_USER,"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",0, KEY_ALL_ACCESS, &numKey);

	result=ERROR_SUCCESS;
	
	for (i=0;result==ERROR_SUCCESS;i++) {
		Size=MAX_PATH;
		result=RegEnumKeyEx(numKey,i,lpSubKey,&Size,NULL,NULL,NULL,&FileTime);
	}
	return 0;
}
*/

/**
providing only for compatibility with 16-bit versions of Windows
app should use the RegOpenKeyEx func.
RegOpenKeyEx func is in TestRegistry.cpp file.
*/

/**
BOOL test_RegLoadMUIStringA(){



	RegLoadMUIStringA(syscall.Handle(k), pname, &buf[0], uint32(len(buf)), &buflen, 0, pdir);

	return true;
}
*/