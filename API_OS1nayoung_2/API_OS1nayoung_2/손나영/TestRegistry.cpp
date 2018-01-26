#include "TestRegistry.h"
#include <atlstr.h>

// 권한 부여 함수.
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
* 특정 레지스트리 키 핸들 닫기.
* @author : 손나영
*
* @param hKey 닫을 핸들. 그 전에 RegCreateKeyEx, RegOpenKeyEx 함수 등으로 키가 열려 있어야 함.
* @return 핸들 닫기 성공/실패 여부
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

	// 클로즈할 key를 먼저 생성(또는 오픈)해 줘야 함. 
	result = RegCreateKeyExW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&phkResult, NULL);

	if(result == ERROR_SUCCESS){ // 생성 성공 시 계속 진행.
		result = RegCloseKey(hKey); // newKey 클로즈 진행.

			if(result == ERROR_SUCCESS){ // 클로즈 성공 시.
				strcpy(buf, "SUCCESS");
				strcpy(msg, " RegCloseKey : SUCCESS");

			}else{ // 생성 성공 후 클로즈 실패 시.
				strcpy(msg, "RegCloseKey  : FAIL \n\n RegCreateKeyW 성공했으나 → RegCloseKey 실패");
				return FALSE;
			}
	}else{
		strcpy(msg, "RegCreateKeyExW 함수를 다시 확인하십시오. \n key 클로즈 전 먼저 생성 또는 오픈되어야 합니다.");
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
* 특정 레지스트리 키 생성. 이미 존재하면 오픈.
* @author : 손나영

* @param hKey 오픈할 레지스트리 키 핸들. 기존 키 목록에서 선택 가능.
* @param lpSubKey 오픈 또는 생성하는 보조키명.
* @param Reserved 무조건 0.
* @param lpClass 키의 사용자 정의 클래스 타입. 무시할 수 있음. NULL.
* @param dwOptions 4가지 옵션 중 하나.
* @param samDesired 생성되는 키 접근 권한을 지정하는 마스크. 
* @param lpSecurityAttributes 리턴되는 핸들이 자식 프로세스에 의해 상속되는지 안 되는지 결정하는 SECURITY_ATTRIBUTES 구조체에 대한 포인터.
* @param phkResult 오픈 또는 생성되는 키 핸들을 받는 변수에 대한 포인터. 이미 정의된 키가 아니라면 RegCloseKey 함수를 핸들 쓴 다음에 call.
* @param lpdwDisposition 2가지 옵션 중 하나. 만약 NULL이면 어떤 정보도 반환되지 않음.
* @return 생성 성공/실패 여부
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

	if(result == ERROR_SUCCESS){ // 생성 성공 시
		strcpy(buf, "SUCCESS");
		strcpy(msg, " RegCreateKeyExW : SUCCESS");
			
	}else{ // 생성 실패 시
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
* 특정 레지스트리 키 생성. 이미 존재한다면 오픈.
* @author : 손나영
*
* @param hKey 오픈할 레지스트리 키 핸들. 기존 키 목록에서 선택 가능.
* @param lpSubKey 오픈 또는 생성하는 보조키명.
* @param phkResult 오픈 또는 생성되는 키 핸들을 받는 변수에 대한 포인터. 이미 정의된 키가 아니라면 RegCloseKey 함수를 핸들 쓴 다음에 call.
* @return 생성 성공/실패 여부
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
* 특정 레지스트리의 서브키 삭제
* @author : 손나영
*
* @param hKey 오픈할 레지스트리 키 핸들. 기존 키 목록에서 선택 가능.
* @param lpSubKey 오픈 또는 생성하는 보조키명.
* @param samDesired 생성되는 키 접근 권한을 지정하는 마스크. 
* @param Reserved 무조건 0.
* @return 삭제 성공/실패 여부.
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

	//생성 및 오픈 먼저.
	result = RegCreateKeyW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",&phkResult);

	if(result == ERROR_SUCCESS){ // 생성 성공 시 계속 진행.

		result = RegDeleteKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", KEY_WOW64_32KEY, 0);

		//if(RegCreateKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL)) == ERROR_SUCCESS){
		if(result == ERROR_SUCCESS){ //삭제 성공 시.
			strcpy(buf, "SUCCESS");
			strcpy(msg, " RegDeleteKeyExW() : SUCCESS");

		}else{ // 삭제 실패 시.
			strcpy(msg, " RegDeleteKeyExW : FAIL");
			return FALSE;
		}

	}else{ // 생성 및 오픈 실패 시.
		strcpy(msg, "RegCreateKeyExW 함수를 다시 확인하십시오. \n 생성된 키가 없다면 먼저 생성해야 합니다.");
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
* 서브 키와 그 값을 삭제
* @author : 손나영
*
* @param hKey 오픈할 레지스트리 키 핸들. 기존 키 목록에서 선택 가능.
* @param lpSubKey 오픈 또는 생성하는 보조키명.
* @return 삭제 성공/실패 여부
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

			//마지막에 Key를 닫아줘야 함
			RegCloseKey(newKey);

		}else{
			strcpy(msg, " RegDeleteKeyW() : FAIL \n\n Create성공 → Open 성공 → Set 성공 → Delete 실패 \n RegDeleteKeyW()가 잘못되었습니다.");

			return FALSE;
		}

	}else{
		strcpy(msg, " RegOpenKeyEx() : FAIL \n\n Create성공 → Open 실패 \n RegOpenKeyEx()가 잘못되었습니다.");
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
* 특정 키의 서브키와 값을 재귀적으로 삭제.
* @author : 손나영

* @param hKey 오픈할 레지스트리 키 핸들. 기존 키 목록에서 선택 가능.
* @param lpSubKey 오픈 또는 생성하는 보조키명. NULL 이면 hKey를 삭제해 버림.
* @return 삭제 성공/실패 여부
*/

/**
레지스트리 키 트리를 삭제합니다.
생성 → 오픈 → 삭제의 과정을 거친 후 오픈 동작으로 키가 제대로 삭제되었는지 확인합니다.
삭제 후 REGEDIT에서 키를 클릭했을 때 에러 메시지 박스가 호출되면 정상입니다.
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

	// 먼저 키 생성.
	result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest\\Position",&newKey);

	// 키가 성공적으로 생성되면, (이때 반드시 하위 키 생성해야 함. 이 과정을 확인하지 않았다가 hKey에 아래가 적용되면 절대 안 됨.
	if(result == ERROR_SUCCESS){ 
		result = RegDeleteTreeW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest"); // 재귀적으로 삭제 진행.

		// 삭제에 성공하여 ERROR_SUCCESS를 반환하면, 
		if(result == ERROR_SUCCESS){ 
			result = RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey); // 삭제했던 키를 오픈해 보기.

			// 잘 삭제되어 오픈에 실패하면 → RegDeleteTreeW 테스트 성공.
			// 이때 REGEDIT 확인해 보면, HKEY_CURRENT_USER\\SOFTWARE\\NAYOUNG_API_TEST_2 까지만 있음. 
			if(result != ERROR_SUCCESS){ 
				strcpy(msg, "RegDeleteTreeW() : SUCCESS");
				strcpy(buf, "SUCCESS");
				//result = TRUE;

			// 삭제 때 ERROR_SUCCESS를 반환하여 성공한 줄 알았지만 오픈에 성공해 버린 상황.
			}else {
				strcpy(msg, "RegDeleteTreeW() : FAIL");
				return FALSE;
			}

		// 삭제 실패. = RegDeleteTreeW 실패.
		}else {
			strcpy(msg, "RegDeleteTreeW() : FAIL");
			return FALSE;
		}

	// 키 생성 과정부터 실패.	
	}else {
		strcpy(msg, "RegCreateKey 함수를 다시 확인하십시오.");
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
* 특정 레지스트리 키의 이름 값을 삭제.
* @author : 손나영
*
* @param hKey 오픈할 레지스트리 키 핸들. 기존 키 목록에서 선택 가능.
* @param lpValueName 삭제할 레지스트리 이름. NULL이거나 빈 문자열이면 RegSetValue함수에 의해 설정된 값이 삭제됨.
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
	
	// 레지스트리 키 생성부터 실행. 
	result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest\\Position",&newKey);

	if(result == ERROR_SUCCESS){ // 생성에 성공하면 
		RegSetValueExW(newKey, L"Top",0,REG_DWORD,(LPBYTE)&rt.top,sizeof(LONG)); // 하위 set.
		//RegSetValueExW(newKey, L"Right",0,REG_DWORD,(LPBYTE)&rt.right,sizeof(LONG));
		//RegSetValueExW(newKey, L"Bottom",0,REG_DWORD,(LPBYTE)&rt.bottom,sizeof(LONG));
		//RegSetValueExW(newKey, L"Left",0,REG_DWORD,(LPBYTE)&rt.left,sizeof(LONG));

		result = RegDeleteValueW(newKey, L"TOP");

		if(result == ERROR_SUCCESS){
			strcpy(buf, "SUCCESS");
			strcpy(msg, " RegDeleteValueW() : SUCCESS");
			result = TRUE;

			//마지막에 Key를 닫아줘야 함
			RegCloseKey(newKey);

		}else
			strcpy(msg, " RegDeleteValueW() : FAIL");
		
	}else
		strcpy(msg, " RegCreateKey 함수를 다시 체크하십시오.");
	
	wresult(__FILE__, __LINE__, "RegDeleteValueW", buf, "SUCCESS", msg);
	return result;
}


/**
* LONG WINAPI RegDisablePredefinedCacheEx(void);
* 현재 프로세스에 미리 정의 된 레지스트리 핸들에 대한 핸들 캐싱을 비활성화.
* @author : 손나영
*
* @param void.
* @return 비활성화 성공/실패 여부.
*/

BOOL test_RegDisablePredefinedCacheEx(){

	#ifdef OQADBGPRINT
	printf("test_RegDisablePredefinedCacheEx \n");
	#endif

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	LONG result = FALSE;

	result = RegDisablePredefinedCacheEx();

	if(result == ERROR_SUCCESS){ // 비활성화 성공
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
* 특정 오픈 레지스트리 키의 하위 키를 열거.
* @author : 손나영
*
* @param hKey 오픈할 레지스트리 키 핸들. 기존 키 목록에서 선택 가능.
* @param dwIndex 가져올 하위 키의 인덱스. 이 매개 변수는 RegEnumKeyEx 함수 에 대한 첫 번째 호출에 대해 0이어야하며 이후 호출에 대해 증가됨.
* @param lpName 종료 NULL 문자를 포함하여 서브 키의 이름을 수신하는 버퍼에 대한 포인터.
* @param lpcName lpName 매개 변수로 지정된 버퍼의 크기를 문자 로 나타낸 변수에 대한 포인터 .
* @param lpReserved 무조건 NULL.
* @param lpClass 열거 된 하위 키의 사용자 정의 클래스를받는 버퍼에 대한 포인터. NULL 가능.
* @param lpcClass lpClass 매개 변수로 지정된 버퍼 크기를 문자로 지정하는 변수에 대한 포인터. lpClass가 NULL인 경우에만 NULL 가능.
* @param lpftLastWriteTime 열거 형 하위 키가 마지막으로 기록 된 시간을받는 FILETIME 구조체에 대한 포인터. NULL 가능.
* @return 열거 성공/실패 여부.
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
	//printf("▼RegEnumKeyExA() 출력▼ \n");
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
* 특정 오픈 레지스트리 키의 하위 키를 열거.
* @author : 손나영
*
* @param hKey 오픈할 레지스트리 키 핸들. 기존 키 목록에서 선택 가능.
* @param dwIndex 가져올 하위 키의 인덱스. 이 매개 변수는 RegEnumKeyEx 함수 에 대한 첫 번째 호출에 대해 0이어야하며 이후 호출에 대해 증가됨.
* @param lpName 종료 NULL 문자를 포함하여 서브 키의 이름을 수신하는 버퍼에 대한 포인터.
* @param lpcName lpName 매개 변수로 지정된 버퍼의 크기를 문자 로 나타낸 변수에 대한 포인터 .
* @param lpReserved 무조건 NULL.
* @param lpClass 열거 된 하위 키의 사용자 정의 클래스를받는 버퍼에 대한 포인터. NULL 가능.
* @param lpcClass lpClass 매개 변수로 지정된 버퍼 크기를 문자로 지정하는 변수에 대한 포인터. lpClass가 NULL인 경우에만 NULL 가능.
* @param lpftLastWriteTime 열거 형 하위 키가 마지막으로 기록 된 시간을받는 FILETIME 구조체에 대한 포인터. NULL 가능.
* @return 열거 성공/실패 여부.
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
	//printf("▼RegEnumKeyExW() 출력▼ \n");
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
* 특정 오픈 레지스트리 키의 하위 키를 열거. 16비트 전용 함수이므로 RegEnumKeyEx 함수 사용.
* @author : 손나영
*
* @param hKey 오픈할 레지스트리 키 핸들. 기존 키 목록에서 선택 가능.
* @param dwIndex 가져올 하위 키의 인덱스. 이 매개 변수는 RegEnumKeyEx 함수 에 대한 첫 번째 호출에 대해 0이어야하며 이후 호출에 대해 증가됨.
* @param lpName 종료 NULL 문자를 포함하여 서브 키의 이름을 수신하는 버퍼에 대한 포인터.
* @param cchName lpName파라미터에 의한 버퍼 포인터의 사이브. TCHAR.
* @return 열거 성공/실패 여부
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
	//printf("▼RegEnumKeyW() 출력▼ \n");
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
* 특정 오픈 레지스트리 키의 값을 열거. 이 함수는 호출 될 때마다 키에 대해 하나의 인덱스 값 이름과 데이터 블록을 복사.
* @author : 손나영
*
* @param hKey 오픈할 레지스트리 키 핸들. 기존 키 목록에서 선택 가능.
* @param dwIndex 값의 인덱스. 이 매개 변수는 RegEnumValue 함수 에 대한 첫 번째 호출에 대해 0이어야하며 이후 호출에 대해 증가.
* @param lpValueName 값의 이름을 Null로 끝나는 문자열 로받는 버퍼에 대한 포인터 . 이 버퍼는 종료 널 문자 를 포함 할만큼 충분히 커야함.
* @param lpcchValueName lpValueName 매개 변수가 가리키는 버퍼의 크기 를 문자로 나타낸 변수 에 대한 포인터 .
* @param lpReserved 이 매개 변수는 예약되어 있으므로 NULL 이어야 함.
* @param lpType 지정된 값에 저장된 데이터 유형을 나타내는 코드를 수신하는 변수에 대한 포인터.
* @param lpData 값 항목에 대한 데이터를 수신하는 버퍼에 대한 포인터. 이 매개 변수는 데이터가 필요하지 않은 경우 NULL 일 수 있음.
* @param lpcbData lpData 매개 변수가 가리키는 버퍼 크기 를 바이트 단위로 지정하는 변수의 포인터 .
* @return 성공 시 ERROR_SUCCESS 반환.
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
		strcpy(msg, " RegEnumValueW : SUCCESS \n\n 두 번째 인자 dwIndex = 0 → 첫 번째 값만 RegEnum");

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
* 레지스트리 키를 protecting하는 security descriptor가 의 복사본 가져옴.
* @author : 손나영
*
* @param hKey 오픈할 레지스트리 키 핸들. 기존 키 목록에서 선택 가능.
* @param SecurityInformation SECURITY_INFORMATION의 요청된 보안 정보를 나타내는 값. 
* @param pSecurityDescriptor 요청한 보안 설명 자의 복사본을 받는 버퍼에 대한 포인터.
* @param lpcbSecurityDescriptor pSecurityDescriptor 매개 변수가 가리키는 버퍼의 크기 (바이트)를 지정하는 변수에 대한 포인터 .
* @return 가져오기 성공/실패 여부.
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

	//반드시 오픈해줘야 함
	result = RegOpenKeyW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position", &newKey);

	if(result != ERROR_SUCCESS){
		sprintf(msg, " RegOpenKeyW함수를 다시 확인하십시오 \n\n Error Code : %d", err);
	}

	result = RegGetKeySecurity(hKey, si, psdNew, &dwSdSizeNeeded);

	if (result == ERROR_SUCCESS ){
		strcpy(buf, "SUCCESS");
		sprintf(msg, " RegGetKeySecurity() : SUCCESS");

	}else if(result == ERROR_INSUFFICIENT_BUFFER){
		sprintf(msg, " RegGetKeySecurity() : FAIL \n\n Buffer의 크기가 너무 작습니다.");

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
* 특정 레지스트리 값의 타입과 데이터를 가져옴.
* @author : 손나영
*
* @param hKey 오픈할 레지스트리 키 핸들. 기존 키 목록에서 선택 가능.
* @param lpSubKey 오픈 또는 생성하는 보조키명.
* @param lpValue 레지스트리 값 이름. NULL이거나 빈 스트링이면 키의 디폴트 값의 타입과 데이터를 가져옴.
* @param dwFlags 조회 할 값의 데이터 유형을 제한하는 플래그. 10+4가지.
* @param pdwType 지정된 값에 저장된 데이터 유형을 나타내는 코드를 수신하는 변수에 대한 포인터. 유형이 필요하지 않으면 NULL.
* @param pvData 값의 데이터를받는 버퍼에 대한 포인터. 데이터가 필요하지 않으면 NULL.
* @param pcbData pvData 매개 변수가 가리키는 버퍼의 크기 를 바이트 단위로 지정하는 변수의 포인터. pcbData NULL일 경우에만 pvData NULL 가능.
* @return 가져오기 성공/실패 여부.
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

	// Registry 생성
	result = RegCreateKeyExW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL);
	if(result != ERROR_SUCCESS){
		strcpy(msg, " 레지스트리 CREATE 실패");
		result = FALSE;
	}

	// 생성한 Registry key에 value값으로 Top 넣음
	result = RegSetValueExW(newKey, L"Top",0,REG_DWORD,(LPBYTE)&rt.left,sizeof(LONG));
	if(result != ERROR_SUCCESS){
		strcpy(msg, " 레지스트리 SET 실패");
		result = FALSE;
	}

	result = RegGetValueW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", L"TOP", RRF_RT_REG_BINARY | RRF_RT_REG_DWORD, NULL, (LPDWORD)&value, &BufferSize);
	
	// RegGetValueW 성공, 실패 경우
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
* HKEY_USERS 또는 HKEY_LOCAL_MACHINE 아래에 서브키를 생성하고 서브키 내의 특정 key hive 데이터를 로드함.
* @author : 손나영
*
* @param hKey 오픈할 레지스트리 키 핸들. HKEY_USERS 또는 HKEY_LOCAL_MACHINE 이거나 RegConnectRegistry로 반환.
* @param lpSubKey 오픈 또는 생성하는 보조키명.
* @param lpFile 레지스트리 데이터가 들어있는 파일 이름. RegSaveKey로 만든 로컬 파일이어야 함. 없으면 지정된 이름으로 파일이 작성됨.
* @return 로드 성공/실패 여부.
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
* HKEY_USERS 또는 HKEY_LOCAL_MACHINE 아래에 서브키를 생성하고 서브키 내의 특정 key hive 데이터를 로드함.
* @author : 손나영
*
* @param hKey 오픈할 레지스트리 키 핸들. HKEY_USERS 또는 HKEY_LOCAL_MACHINE 이거나 RegConnectRegistry로 반환.
* @param lpSubKey 오픈 또는 생성하는 보조키명.
* @param lpFile 레지스트리 데이터가 들어있는 파일 이름. RegSaveKey로 만든 로컬 파일이어야 함. 없으면 지정된 이름으로 파일이 작성됨.
* @return 로드 성공/실패 여부.
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
* 지정된 레지스트리 키의 속성 또는 내용에 대한 변경 사항을 호출자에게 알림
* @author : 손나영
*
* @param hKey 오픈할 레지스트리 키 핸들. HKEY_USERS 또는 HKEY_LOCAL_MACHINE 이거나 RegConnectRegistry로 반환.
* @param bWatchSubtree 이 매개 변수가 TRUE이면 함수는 지정된 키와 하위 키의 변경 내용을 보고. 매개 변수가 FALSE 인 경우 함수는 지정된 키에서만 변경 사항을 보고.
* @param dwNotifyFilter 보고해야 할 변경 내용을 나타내는 값. 5가지.
* @param hEvent fAsynchronous가 TRUE면 즉시 반환, FALSE면 무시.
* @param fAsynchronous  TRUE면 즉시 반환, FALSE면 변경이 발생할 때까지 반환 X.
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

	// Registry 생성
	result = RegCreateKeyExW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL);
	if(result != ERROR_SUCCESS){
		strcpy(msg, " 레지스트리 CREATE 실패");
		result = FALSE;
	}

	regFilter = REG_NOTIFY_CHANGE_NAME | REG_NOTIFY_CHANGE_ATTRIBUTES | REG_NOTIFY_CHANGE_LAST_SET | REG_NOTIFY_CHANGE_SECURITY;
	// REG_NOTIFY_CHANGE_NAME - 레지스트리 키가 변경, 삭제, 추가가 되는 경우
	// REG_NOTIFY_CHANGE_ATTRIBUTES - 레지스트리 키의 속성이 변경되는 경우 (사용권한설정 등)
	// REG_NOTIFY_CHANGE_LAST_SET - 레지스트리에 접근하고 있는 경우
	// REG_NOTIFY_CHANGE_SECURITY -  레지스트리 사용 권한 설정이 변경되는 경우

	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	// 임시로 5번 루프가 반복되도록 함.
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
* 현재 스레드가 가장하고있는 사용자의 HKEY_CURRENT_USER 키에 대한 핸들을 가져옴
* @author : 손나영
*
* @param samDesired 키에 대한 원하는 액세스 권한을 지정하는 마스크. 키의 보안 설명자가 호출 프로세스에 대해 요청 된 액세스를 허용하지 않으면 함수가 실패.
* @param phkResult 열린 키의 핸들을받는 변수에 대한 포인터. 반환 된 핸들이 더 이상 필요하지 않으면 RegCloseKey 함수를 호출하여 핸들 닫기.
* @return 가져오기 성공/실패 여부.
*/

BOOL test_RegOpenCurrentUser(){

	#ifdef OQADBGPRINT
	printf("test_RegOpenCurrentUser \n");
	#endif

	HKEY keyCurrentUser;

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	// KEY_READ : Combination of KEY_QUERY_VALUE(하위 키 데이터를 쿼리 가능), 
	// KEY_ENUMERATE_SUB_KEYS(하위 키 열거) and KEY_NOTIFY(변경 통지) 
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
* 특정 레지스트리 키 오픈
* @param hKey 오픈할 레지스트리 키 핸들. HKEY_USERS 또는 HKEY_LOCAL_MACHINE 이거나 RegConnectRegistry로 반환.
* @param lpSubKey 오픈 또는 생성하는 보조키명.
* @param ulOptions 키를 오픈할 때 적용할 옵션 - REG_OPTION_OPEN_LINK
* @param samDesired 키에 대한 원하는 액세스 권한을 지정하는 마스크. 키의 보안 설명자가 호출 프로세스에 대해 요청 된 액세스를 허용하지 않으면 함수가 실패.
* @param phkResult 열린 키의 핸들을받는 변수에 대한 포인터. 반환 된 핸들이 더 이상 필요하지 않으면 RegCloseKey 함수를 호출하여 핸들 닫기.
* @return 키 오픈 성공/실패 여부
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
		strcpy(msg, " 레지스트리 생성 실패 \n\n RegCreateKeyEx함수를 다시 확인하십시오.");
	}

	// 핸들 닫기.
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
* 특정 레지스트리 키 오픈
* @param hKey 오픈할 레지스트리 키 핸들. HKEY_USERS 또는 HKEY_LOCAL_MACHINE 이거나 RegConnectRegistry로 반환.
* @param lpSubKey 오픈 또는 생성하는 보조키명.
* @param phkResult 열린 키의 핸들을받는 변수에 대한 포인터. 반환 된 핸들이 더 이상 필요하지 않으면 RegCloseKey 함수를 호출하여 핸들 닫기.
* @return 키 오픈 성공/실패 여부
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
		strcpy(msg, " 레지스트리 CREATE 실패");
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

	// 핸들 닫기.
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
* 지정된 사용자에 대한 HKEY_CLASSES_ROOT 키에 대한 핸들을 가져옴.
* @author : 손나영
*
* @param hToken 사용자를 식별하는 primary 또는 impersonation 액세스 토큰에 대한 핸들.
* @param dwOptions 무조건 0
* @param samDesired 키에 대한 원하는 액세스 권한을 지정하는 마스크. 키의 보안 설명자가 호출 프로세스에 대해 요청 된 액세스를 허용하지 않으면 함수가 실패.
* @param phkResult 열린 키의 핸들을받는 변수에 대한 포인터. 반환 된 핸들이 더 이상 필요하지 않으면 RegCloseKey 함수를 호출하여 핸들 닫기.
* @return 가져오기 성공/실패 여부
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
		strcpy(msg, " OpenProcessToken() 비정상 \n\n process와 연관된 Access Token을 다시 여십시오 ");

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
* 특정 레지스트리 키에 대한 정보를 가져옴.
* @author : 손나영
*
* @param hKey 오픈할 레지스트리 키 핸들. HKEY_USERS 또는 HKEY_LOCAL_MACHINE 이거나 RegConnectRegistry로 반환.
* @param lpClass 키의 사용자 정의 클래스를받는 버퍼에 대한 포인터. NULL 가능. 
* @param lpcClass lpClass 매개 변수가 가리키는 버퍼의 크기 를 문자로 나타낸 변수 에 대한 포인터. NULL이면 다음 함수는 ERROR_INVALID_PARAMETER 반환.
* @param lpReserved 무조건 NULL.
* @param lpcSubKeys 지정된 키에 포함 된 하위 키 수를받는 변수에 대한 포인터. NULL 가능.
* @param lpcMaxSubKeyLen 가장 긴 이름을 갖는 키의 하위 키 크기를 유니 코드 문자로 수신하고 종료 null 문자를 포함하지 않는 변수에 대한 포인터. NULL 가능.
* @param lpcMaxClassLen 유니 코드 문자로 하위 키 클래스를 지정하는 가장 긴 문자열의 크기를받는 변수에 대한 포인터. NULL 가능.
* @param lpcValues 키와 연관된 값의 수를받는 변수에 대한 포인터. NULL 가능.
* @param lpcMaxValueNameLen 키의 가장 긴 값 이름의 크기를 유니 코드 문자로받는 변수에 대한 포인터. NULL 가능. 
* @param lpcMaxValueLen 키의 값 중에서 가장 긴 데이터 구성 요소의 크기 (바이트)를받는 변수에 대한 포인터. ㅜㅕㅣ= ==ㅑㅑㅏ
* @param lpcbSecurityDescriptor
* @param lpftLastWriteTime
* @return 정보를 가져오기 성공/실패 여부.
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

	// 키에 속한 서브키와 값의 개수 조사
	
	result=	RegQueryInfoKeyW(hKey,NULL,NULL,NULL,&cSubKeys,NULL,NULL,&cValues,NULL,NULL,NULL,NULL);
			
	if(result == ERROR_SUCCESS){
		strcpy(buf, "SUCCESS");
		strcpy(msg, "RegQueryInfoKeyW : SUCCESS");
		result = TRUE;

	}else if(result == ERROR_MORE_DATA){
		strcpy(msg, "RegQueryInfoKeyW : FAIL \n\n lpClass buffer가 클레스의 이름을 받기에는 너무 작습니다.");
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
* 오픈된 레지스트리 키와 연결된 특정 값 이름의 타입과 데이터를 가져옴.
* @author : 손나영
*
* @param hKey hKey 오픈할 레지스트리 키 핸들. HKEY_USERS 또는 HKEY_LOCAL_MACHINE 이거나 RegConnectRegistry로 반환.
* @param lpValueName 레지스트리 값의 이름.
* @param lpReserved 무조건 NULL.
* @param lpType 지정된 값에 저장된 데이터 유형을 나타내는 코드를 수신하는 변수에 대한 포인터.
* @param lpData 값의 데이터를받는 버퍼에 대한 포인터. NULL 가능.
* @param lpcbData lpData 매개 변수가 가리키는 버퍼 크기 를 바이트 단위로 지정하는 변수에 대한 포인터. NULL일 결우에만 lpData NULL.
* @return 가져오기 성공/실패 여부
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
		strcpy(msg, " 레지스트리 CREATE 실패");
		result = FALSE;
	}

	result = RegSetValueExW(newKey, L"Top",0,REG_DWORD,(LPBYTE)&rt.top,sizeof(LONG)); // 하위 set.
	if(result != ERROR_SUCCESS){ 
		strcpy(msg, " 레지스트리 SET 실패");
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
* 특정 포맷에서, 특정 키와 서브키의 모든 것들, 그리고 레지스트리 파일의 값들을 save.
* @author : 손나영
*
* @param hKey 오픈된 레지스트리의 핸들.
* @param lpFile 미리 정의된 HKEY_CLASSES_ROOT 키는 지원하지 않음.
* @param lpSecurityAttributes 지정된 키와 하위 키를 저장할 파일의 이름입니다. 파일이 이미 있으면 함수가 실패합니다.
* @param Flags 저장된 키 또는 하이브 형식. 3가지.
* @return save 성공/실패 여부.
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

	// RegSaveKeyEx 진행 때, 파일이 이미 있으면 두 번째 파라미터의 오류로 실패하므로 반드시 삭제.
	// 이전에 혹시 제대로 삭제되지 않았을 수도 있으니 삭제 다시.
	DeleteFileA(lpFile);

	result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",&newKey);
	if(result != ERROR_SUCCESS){
		strcpy(msg, " 레지스트리 CREATE 실패");
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

	// 다음 RegSaveKeyEx 진행 때, 파일이 이미 있으면 두 번째 파라미터의 오류로 실패하므로 반드시 삭제.
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
* 특정 포맷에서, 특정 키와 서브키의 모든 것들, 그리고 레지스트리 파일의 값들을 save.
* @author : 손나영
*
* @param hKey 오픈된 레지스트리의 핸들.
* @param lpFile 미리 정의된 HKEY_CLASSES_ROOT 키는 지원하지 않음.
* @param lpSecurityAttributes 지정된 키와 하위 키를 저장할 파일의 이름입니다. 파일이 이미 있으면 함수가 실패합니다.
* @param Flags 저장된 키 또는 하이브 형식. 3가지.
* @return save 성공/실패 여부.
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

	// RegSaveKeyEx 진행 때, 파일이 이미 있으면 두 번째 파라미터의 오류로 실패하므로 반드시 삭제.
	// 이전에 혹시 제대로 삭제되지 않았을 수도 있으니 삭제 다시.
	DeleteFileW(lpFile);

	result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",&newKey);
	if(result != ERROR_SUCCESS){
		strcpy(msg, " 레지스트리 CREATE 실패");
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

	// 다음 RegSaveKeyEx 진행 때, 파일이 이미 있으면 두 번째 파라미터의 오류로 실패하므로 반드시 삭제.
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
* 오픈된 레지스트리 키의 보안 설정
* @author : 손나영
*
* @param hKey 오픈된 레지스트리의 핸들.
* @param SecurityInformation 설정할 보안 정보의 유형을 나타내는 비트 플래그 세트. SECURITY_INFORMATION 비트 플래그 의 조합 가능. 
* @param pSecurityDescriptor 지정된 키에 설정할 보안 속성 을 지정 하는 SECURITY_DESCRIPTOR 구조체에 대한 포인터.
* @return  보안 설정 성공/실패 여부.
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

	//hKey 조금 위험.(R)
	RegGetKeySecurity(hKey, si, &psdNew, &dwSdSizeNeeded);
	result = RegSetKeySecurity(hKey, si, &psdNew);

	if(result == ERROR_SUCCESS){
		strcpy(buf, "SUCCESS");
		sprintf(msg, " RegSetKeySecurity() : SUCCESS");

	}else if(result == ERROR_INSUFFICIENT_BUFFER){
		sprintf(msg, " RegSetKeySecurity() : FAIL \n\n Buffer의 크기가 너무 작습니다.");
		result = FALSE;

	}else{
		strcpy(msg, "RegSetKeySecurity() : FAIL");
		result = FALSE;
	}

	// 닫아줘야 함.
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
* 레지스트리 키 아래에 특정 값의 데이터 및 타입을 설정.
* @author : 손나영
*
* @param hKey 오픈할 레지스트리 키 핸들. 기존 키 목록에서 선택 가능.
* @param lpValueName 설정할 값 이름.
* @param Reserved 무조건 0.
* @param dwType lpData 매개변수가 가리키는 데이터 형식.
* @param *lpData 저장할 데이터.
* @param cbData lpData 매개변수가 가리키는 정보의 크기. 바이트. 
* @return 설정 성공/실패 여부.
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
		strcpy(msg, " 레지스트리 CREATE 실패");
		result = FALSE;
	}

	result = RegSetValueExW(newKey, L"Top",0,REG_DWORD,(LPBYTE)&rt.top,sizeof(LONG)); // 하위 set.
	if(result == ERROR_SUCCESS){ 
		strcpy(buf, "SUCCESS");
		strcpy(msg, " RegSetValueExw : SUCCESS");
		result = TRUE;

	}else{
		strcpy(msg, " RegSetValueExw : FAIL");
		result = FALSE;	
	}

	// 닫아줘야 함.
	RegCloseKey(hKey);
	wresult(__FILE__, __LINE__, "RegSetValueExW", buf, "SUCCESS", msg);

	return result;
}


/**
* LONG WINAPI RegUnLoadKey(
  _In_     HKEY    hKey,
  _In_opt_ LPCTSTR lpSubKey
 );
* 레지스트리의 서브키와 특정 키를 언로드
* @author : 손나영
*
* @param hKey 언로드 할 특정 키의 핸들. HKEY_LOCAL_MACHINE 또는 HKEY_USERS 가능.
* @param lpSubKey 언로드할 서브키 이름.
* @return 언로드 성공/실패 여부.
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

	// 로드 먼저.
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
		strcpy(msg, " Registry Load에 실패했습니다. \n RegLoadKeyA 함수를 다시 확인하십시오,");
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
* 레지스트리의 서브키와 특정 키를 언로드
* @author : 손나영
*
* @param hKey 언로드 할 특정 키의 핸들. HKEY_LOCAL_MACHINE 또는 HKEY_USERS 가능.
* @param lpSubKey 언로드할 서브키 이름.
* @return 언로드 성공/실패 여부.
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

	// 로드 먼저.
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
		strcpy(msg, " Registry Load에 실패했습니다. \n RegUnLoadKeyW 함수를 다시 확인하십시오,");
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
			strcpy(msg, GetErrorMessage(" Registry Key 오픈 실패 \n\n RegOpenKeyEx 함수를 다시 확인하세요", GetLastError()));
		}
	}else
		strcpy(msg, GetErrorMessage(" Registry Key 생성 실패 \n\n RegCreateKey 함수를 다시 확인하세요", GetLastError()));

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

	1. 문제점 event 발생
	2. Windows가 WER 호출
	3. WER는 데이터를 수집하고 보고서를 작성하며 필요한 경우 사용자에게 동의 여부 묻는 메시지를 표시
	4. WER은 사용자가 동의한 경우 보고서를 Watson Server(microsoft)로 보냄
	5. Watson 서버가 추가 데이터를 요청하면 WER은 데이터를 수집하고 필요한 경우 사용자에게 동의 여부를 묻는 메시지를 표시합니다.
	6. 응용 프로그램이 복구 및 다시 시작을 위해 등록 된 경우 WER은 등록 된 콜백 함수를 실행하면서 데이터가 압축되어 Microsoft에 전송됩니다 (사용자가 동의 한 경우).
	7. Microsoft에서 문제에 대한 응답을 사용할 수있는 경우 사용자에게 알립니다.

*/

/**
BOOL test_RegRestoreKeyA(){

#ifdef OQADBGPRINT
	printf("test_RegRestoreKeyA \n");
#endif

	/** 두 번째 파라미터 lpFile : name of the file with the registry information. 
	created by using the RegSaveKey function. 
	→ RegSaveKey(hKey, lpFile, lpSecurityAttributes(NULL이면 default security descriptor 가져옴))	
	

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";
	int wresult_value = 0;
	LSTATUS result;
	HKEY newKey = 0;
	LPSTR lpFile = "손나영\\test_RegSaveKeyExA.reg";

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
		strcpy(msg, "RegSaveKeyEx부터 다시 하십시오.");
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
	/** 두 번째 파라미터 lpFile : name of the file with the registry information. 
	created by using the RegSaveKey function. 
	→ RegSaveKey(hKey, lpFile, lpSecurityAttributes(NULL이면 default security descriptor 가져옴))	
	*/
	/**
	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";
	int wresult_value = 0;
	LSTATUS result;
	//HKEY newKey;
	LPCTSTR lpFile = L"손나영\\test_RegSaveKeyExA.reg";

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
		strcpy(msg, "RegSaveKeyEx부터 다시 하십시오.");

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
		strcpy(msg, "RegLoadMUIStringA : FAIL \n\n pcbData가 너무 작습니다.");
	else if(result == ERROR_CALL_NOT_IMPLEMENTED)
		strcpy(msg, "RegLoadMUIStringA : FAIL \n\n ANSI version → 정상");
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

	////REG_MUI_STRING_TRUNCATE : 문자열은 pszOutBuf 버퍼의 사용 가능한 크기에 맞게 잘림.이 flags 지정되면 pcbData는 null
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
	//	strcpy(msg, "RegLoadMUIStringW : FAIL \n\n pcbData가 너무 작습니다.");
	//else if(result == ERROR_CALL_NOT_IMPLEMENTED)
	//	strcpy(msg, "RegLoadMUIStringW : FAIL \n\n ANSI version → 정상");
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
		strcpy(msg, "RegLoadMUIStringW : FAIL \n\n pcbData가 너무 작습니다.");
	else if(result == ERROR_CALL_NOT_IMPLEMENTED)
		strcpy(msg, "RegLoadMUIStringW : FAIL \n\n ANSI version → 정상");
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

	printf("크기 : %d", cValues);

	if(retCode == ERROR_SUCCESS)
		printf(" 성공");

	if(cValues){
		printf( "\nNumber of values: %d\n", cValues);

		for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++){ 
			result = RegEnumValue(hKey, i, achValue, &cchValue, NULL, NULL,NULL,NULL);

			if(result == ERROR_SUCCESS){
				strcpy(msg, " RegEnumValueA : PASS \n\n 두 번째 인자 dwIndex = 0 → 첫 번째 값만 RegEnum");
				wresult_value=1;
			}else if(result == ERROR_NO_MORE_ITEMS){
				strcpy(msg, " 사용할 수 있는 값이 더 이상 없습니다.");
			}else if(result == ERROR_MORE_DATA){
				strcpy(msg, " lpData 버퍼가 값을 받기에 너무 작습니다.");
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
//		sprintf(msg, " RegCreateKey함수를 다시 확인하십시오 \n\n Error Code : %d", err);
//		return FALSE;
//	}
//
//	//반드시 오픈해줘야 함
//	result = RegOpenKeyW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position", &hKey);
//	if(result != ERROR_SUCCESS){
//		sprintf(msg, " RegOpenKeyW함수를 다시 확인하십시오 \n\n Error Code : %d", err);
//		//return FALSE;
//	}
//
//	result = RegSetKeySecurity(hKey, si, psdNew);
//
//	if(result == ERROR_SUCCESS){
//		strcpy(buf, "SUCCESS");
//		sprintf(msg, " RegSetKeySecurity() : SUCCESS");
//	}else if(result == ERROR_INSUFFICIENT_BUFFER){
//		sprintf(msg, " RegSetKeySecurity() : FAIL \n\n Buffer의 크기가 너무 작습니다.");
//	}else
//		sprintf(msg, GetErrorMessage(" RegSetKeySecurity() : FAIL \n\n Error Code : %s", result));
//
//	RegCloseKey(hKey);
//	wresult(__FILE__, __LINE__, "RegSetKeySecurity", buf, "SUCCESS", msg);
//
//	return result;
//}

/** RegEnumKeyEx 함수
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