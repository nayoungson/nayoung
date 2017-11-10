#include "TestRegistry.h"

BOOL test_RegCreateKeyExW(){
	HKEY newKey;
	LSTATUS result;

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	printf("test_RegCreateKeyExW\n");
	#endif

	result = RegCreateKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL);

	if(result == ERROR_SUCCESS){
		strcpy(meg, " RegCreateKeyExW : PASS \n\n 레지스트리 편집기(RegEdit) 실행\n HKEY_CURRENT_USER > SOFTWARE > NAYOUNG_API_TEST 확인");
			
	}else
		strcpy(meg, " 레지스트리 키 생성 실패");

	wresult(__FILE__, __LINE__, "RegCreateKeyExW", _itoa(result, buf, 10), _itoa(ERROR_SUCCESS, buf, 10), meg);
		 
	return true;
}

BOOL test_RegSetValueExW(){ 
	
	RECT rt;
	HKEY newKey;

	LSTATUS result = RegCreateKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL);

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	printf("test_RegSetValueExW\n");
	#endif

	if(result == ERROR_SUCCESS){
		
		RegSetValueExW(newKey, L"Top",0,REG_DWORD,(LPBYTE)&rt.top,sizeof(LONG));
		RegSetValueExW(newKey, L"Right",0,REG_DWORD,(LPBYTE)&rt.right,sizeof(LONG));
		RegSetValueExW(newKey, L"Bottom",0,REG_DWORD,(LPBYTE)&rt.bottom,sizeof(LONG));
		RegSetValueExW(newKey, L"Left",0,REG_DWORD,(LPBYTE)&rt.left,sizeof(LONG));

		RegCloseKey(newKey);
		
		strcpy(meg, " RegSetValueExw : PASS \n\n NAYOUNG_API_TEST > RegiTest 아래 Top, Right, Bottom, Left 생성 \n 값 데이터 : 0   단위 : 16진수");
	}else
		strcpy(meg, " 레지스트리 값 set 실패");

	wresult(__FILE__, __LINE__, "RegCreateKeyEx", _itoa(result, buf, 10), _itoa(ERROR_SUCCESS, buf, 10), meg);
			
	return true;
}

BOOL test_RegOpenKeyExW(){
	HKEY hKey = HKEY_CURRENT_USER;
	HKEY newKey;
	HWND hWnd =0;

	LSTATUS Create_Result;
	LSTATUS Open_Result;

	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_RegOpenKeyExW\n");
	#endif

	Create_Result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",&newKey);

	if(Create_Result == ERROR_SUCCESS){

		Open_Result = RegOpenKeyExW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);
		if(Open_Result == ERROR_SUCCESS){
			strcpy(meg, " RegOpenKeyEx() : PASS \n\n SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position 위치를 확인하십시오.");
		}else
			strcpy(meg, " RegOpenKeyEx() : FAIL \n\n Create는 정상 완료되었으나 Open에서 실패했습니다.");
	}else{
		#ifdef OQADBG
		MessageBox(hWnd, L" RegCreateKey() : FAIL \n\n Create 실패 \n RegCreateKey()를 다시 확인하십시오.", L"KeyCreate 실패", MB_OK);
		#endif
	}
	wresult(__FILE__, __LINE__, "RegOpenKeyEx", "ERROR_SUCCESS", "ERROR_SUCCESS", meg);
	return true;
}

// 4 RegEnumValueW 완료 *
BOOL test_RegEnumValueW() 
{
	HKEY key=0;
	TCHAR lpValue[MAX_PATH];
	DWORD i=0;
	DWORD Size;
	HWND hList=0;
	//HKEY newKey;

	LSTATUS result;

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	printf("test_RegEnumValueW\n");
	#endif

	// TCHAR lpBuffer[MAX_PATH];
	// LONG result;

	/* 값의 목록을 조사해 리스트 박스에 채워 넣음
	result=TRUE;
	for (i=0;result==TRUE;i++) {
		Size=MAX_PATH;
		result=RegEnumValue(key,i,lpValue,&Size,NULL,NULL,NULL,NULL);
		if (result==TRUE) {
			//wsprintf(lpBuffer,"V : %s",lpValue);
			SendMessage(hList,LB_ADDSTRING,0,(LONG)lpBuffer);
		}
	}
	*/

	if((result = RegEnumValueW(key,i,lpValue,&Size,NULL,NULL,NULL,NULL)) != ERROR){
		strcpy(meg, " RegEnumValueW : PASS \n\n 두 번째 인자 dwIndex = 0 → 첫 번째 값만 RegEnum");

	}else
		strcpy(meg, "FAIL");

	wresult(__FILE__, __LINE__, "RegEnumValueW", _itoa(result, buf, 10), _itoa(ERROR_SUCCESS, buf, 10), meg);
	return true;
}



// RegQueryInfoKeyW 완료 *
BOOL test_RegQueryInfoKeyW(){  
	HKEY newKey=0;
	FILETIME FileTime;
	DWORD dwValueNumer;

	LSTATUS result;

	char meg[BUFSIZ] = "FAIL";
	// char buf[BUFSIZ];

	// LONG result;

	/**
	result = RegOpenKeyEx(HKEY_CURRENT_USER,"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);

	if(result == TRUE){
		RegQueryInfoKey(newKey, NULL, 0, 0, NULL, NULL, NULL, &dwValueNumer, NULL, NULL, NULL, &FileTime);
	}
	*/

	#ifdef OQADBGPRINT
	printf("test_RegQueryInfoKeyW\n");
	#endif

	if((result = RegQueryInfoKeyW(newKey, NULL, 0, 0, NULL, NULL, NULL, &dwValueNumer, NULL, NULL, NULL, &FileTime)) != ERROR){
		strcpy(meg, "RegQueryInfoKeyW : PASS");

	}else
		strcpy(meg, "RegQueryInfoKeyW : FAIL");

	wresult(__FILE__, __LINE__, "RegQueryInfoKeyW", "ERROR_SUCCESS", "ERROR_SUCCESS", meg);

	return true;
}


//RegQueryValueExW 완료 
BOOL test_RegQueryValueExW(){ 
	RECT rt;
	DWORD Size;
	HKEY newKey;
	//LONG result;
	HWND hWnd=0;

	BOOL result;

	char meg[BUFSIZ] = "FAIL";


	#ifdef OQADBGPRINT
	printf("test_RegQueryValueExW\n");
	#endif

	Size=sizeof(LONG);

	RegOpenKeyEx(HKEY_CURRENT_USER,L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);

	if((result = RegQueryValueExW(newKey, L"Left", 0, NULL,(LPBYTE)&rt.left, &Size)) == FALSE){
			//RegCloseKey(newKey);

			//MoveWindow(hWnd, rt.left, rt.top, rt.right-rt.left, rt.bottom-rt.top, TRUE);

			strcpy(meg, "RegQueryValueExW : PASS");
			
		}else
			strcpy(meg, "RegQueryValueExW : FAIL");

	wresult(__FILE__, __LINE__, "RegQueryValueExW", meg, "RegQueryValueExW : PASS", meg);
	return true;
}


// RegCloseKey 완료 *
BOOL test_RegCloseKey(){
	HKEY newKey=0;
	HWND hWnd = 0;
	LSTATUS pre_result;
	LSTATUS closekey_result;

	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_RegCloseKey\n");
	#endif

	pre_result = RegCreateKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL);

	if(pre_result == ERROR_SUCCESS){
		closekey_result = RegCloseKey(newKey);
			if(closekey_result == ERROR_SUCCESS){
				strcpy(meg, " RegCloseKey : PASS \n\n RegCreateKeyW로 key 생성 후 → RegCloseKey 성공");
			}else
				strcpy(meg, "RegCloseKey  : FAIL \n\n RegCreateKeyW 성공했으나 → RegCloseKey 실패");
	}else{
		#ifdef OQADBG
		MessageBox(hWnd, L"RegCreateKeyW함수 실패로 인해 RegCloseKey 함수를 진행할 수 없습니다. Regsitry key를 다시 생성하십시오", L"fail", MB_OK);
		#endif
	}
	wresult(__FILE__, __LINE__, "RegCloseKey", meg, " RegCloseKey : PASS \n\n RegCreateKeyW로 key 생성 후 → RegCloseKey 성공", meg);

	return true;
}

//RegDeleteKeyExW 완료 *
BOOL test_RegDeleteKeyExW(){  
	LSTATUS result;

	char meg[BUFSIZ] = "FAIL";

 	
	#ifdef OQADBGPRINT
	printf("test_RegDeleteKeyExW\n");
	#endif

	result = RegDeleteKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", KEY_WOW64_32KEY, 0);

	//if(RegCreateKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL)) == ERROR_SUCCESS){
	if(result == ERROR_SUCCESS){
		strcpy(meg, " RegDeleteKeyExW \n\n SOFTWARE > NAYOUNG_API_TEST > RegiTest 아래 Position 삭제");

	}else
		strcpy(meg, " RegDeleteKeyExW : FAIL");

	wresult(__FILE__, __LINE__, "RegDeleteKeyExW", meg, " RegDeleteKeyExW \n\n SOFTWARE > NAYOUNG_API_TEST > RegiTest 아래 Position 삭제", meg);
	return true;
}



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


BOOL test_RegDeleteValueW(){
	HKEY hKey = HKEY_CURRENT_USER;
	HKEY newKey;
	RECT rt;
	HWND hWnd =0;

	LSTATUS Create_Result;
	LSTATUS Open_Result;
	LSTATUS Delete_Result;

	char meg[BUFSIZ] = "FAIL";
	#ifdef OQADBGPRINT
	printf("test_RegDeleteValueW\n");
	#endif

	Create_Result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest\\Position",&newKey);
		
	if(Create_Result == ERROR_SUCCESS){
		
		Open_Result = RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);
		if(Open_Result == ERROR_SUCCESS){

			RegSetValueExW(newKey, L"Top",0,REG_DWORD,(LPBYTE)&rt.top,sizeof(LONG));
			RegSetValueExW(newKey, L"Right",0,REG_DWORD,(LPBYTE)&rt.right,sizeof(LONG));
			RegSetValueExW(newKey, L"Bottom",0,REG_DWORD,(LPBYTE)&rt.bottom,sizeof(LONG));
			RegSetValueExW(newKey, L"Left",0,REG_DWORD,(LPBYTE)&rt.left,sizeof(LONG));

			Delete_Result = RegDeleteValueW(newKey, L"Left");

			if(Delete_Result == ERROR_SUCCESS){
				//MessageBox(hWnd, L" RegDeleteValueW() : PASS \n\n Left Key 삭제 시도 → 성공 \n 남은 Key : Top, Right, Bottom", L"Registry_2 성공", MB_OK);
				strcpy(meg, " RegDeleteValueW() : PASS \n\n Left Key 삭제 시도 → 성공 \n 남은 Key : Top, Right, Bottom");

				//마지막에 Key를 닫아줘야 함
				RegCloseKey(newKey);
			}else
				strcpy(meg, " RegDeleteValueW() : FAIL \n\n Create성공 → Open 성공 → Set 성공 → Delete 실패 \n RegDeleteValueW()가 잘못되었습니다.");
				//MessageBox(hWnd, L" RegDeleteValueW() : FAIL \n\n Create성공 → Open 성공 → Set 성공 → Delete 실패 \n RegDeleteValueW()가 잘못되었습니다.", L"KeyDelete 실패", MB_OK);	
		}else
			strcpy(meg, " RegOpenKeyEx() : FAIL \n\n Create성공 → Open 실패 \n RegOpenKeyEx()가 잘못되었습니다.");
			//MessageBox(hWnd, L" RegOpenKeyEx() : FAIL \n\n Create성공 → Open 실패 \n RegOpenKeyEx()가 잘못되었습니다.", L"KeyOpen 실패", MB_OK);	
	}else
		strcpy(meg, " RegCreateKey() : FAIL \n\n Create 실패 \n RegCreateKey()가 잘못되었습니다.");
		//MessageBox(hWnd, L" RegCreateKey() : FAIL \n\n Create 실패 \n RegCreateKey()가 잘못되었습니다.");	
	
	wresult(__FILE__, __LINE__, "RegDeleteValueW", meg, " RegDeleteValueW() : PASS \n\n Left Key 삭제 시도 → 성공 \n 남은 Key : Top, Right, Bottom", meg);
	return true;
}

// 0911 배정 2/3
// 지정된 열려있는 레지스트리 키의 하위 키를 열거(Ex)
BOOL test_RegEnumKeyExW(){
	HKEY key = HKEY_CURRENT_USER;
	TCHAR lpSubKey[MAX_PATH];
	TCHAR lpBuffer[MAX_PATH];
	DWORD i;
	LONG Result;
	DWORD Size;
	FILETIME FileTime;
	HWND hList = 0;
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_RegEnumKeyExW\n");
	#endif

	SendMessage(hList,LB_RESETCONTENT,0,0);
	SendMessage(hList,LB_ADDSTRING,0,(LPARAM)" ^^^ 한 단계 위로 ^^^ ");
	
	Result=ERROR_SUCCESS;
	#ifdef OQADBGPRINT
	printf("▼RegEnumKeyExW() 출력▼ \n");
	#endif

	for (i=0;Result==ERROR_SUCCESS;i++) {
		Size=MAX_PATH;
		Result=RegEnumKeyEx(key,i,lpSubKey,&Size,NULL,NULL,NULL,&FileTime);
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

	strcpy(meg, " RegEnumKeyExW() : PASS \n\n 터미널에서 pluse_enum 값 출력을 확인하십시오.");
	wresult(__FILE__, __LINE__, "RegEnumKeyEx", meg, " RegEnumKeyExW() : PASS \n\n 터미널에서 pluse_enum 값 출력을 확인하십시오.", meg);
	return true;
}

// 0911 배정 3/3
// 지정된 열려있는 레지스트리 키의 하위 키를 열거
BOOL test_RegEnumKeyW(){

	HKEY Key = HKEY_CURRENT_USER;
	DWORD dwIndex = 0;
	TCHAR lpName[MAX_PATH];
	DWORD lpBuffer = 255;
	LONG Result;
	DWORD i;
	HWND hList = 0;
	DWORD Size;
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_RegEnumKeyW\n");
	#endif

	Result=ERROR_SUCCESS;

	#ifdef OQADBGPRINT
	printf("▼RegEnumKeyW() 출력▼ \n");
	#endif

	for (i=0;Result==ERROR_SUCCESS;i++) {
		Size=MAX_PATH;
		Result=RegEnumKeyW(Key,i,lpName,lpBuffer);
		if (Result==ERROR_SUCCESS) {
			#ifdef OQADBGPRINT
			printf("K : %s \n",lpName);
			#endif
			SendMessage(hList,LB_ADDSTRING,0,(LONG)lpBuffer);
		}
	}
	#ifdef OQADBGPRINT
	printf("\n");
	#endif

	strcpy(meg, " RegEnumKeyW() : PASS \n\n 터미널에서 pluse_enum 값 출력을 확인하십시오.");
	wresult(__FILE__, __LINE__, "RegEnumKeyEx", meg, " RegEnumKeyW() : PASS \n\n 터미널에서 pluse_enum 값 출력을 확인하십시오.", meg);
	return true;
}


BOOL test_RegCreateKeyW(){

	HWND hWnd =0;
	HKEY newKey;
	HKEY hKey = HKEY_CURRENT_USER;

	LSTATUS Create_Result;

	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_RegCreateKeyW  \n");
	#endif

	Create_Result = RegCreateKeyW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",&newKey);

	if(Create_Result == ERROR_SUCCESS){
		strcpy(meg, " RegCreateKeyW() : PASS");

	}else
		#ifdef OQADBG
		MessageBox(hWnd, L" RegCreateKeyW() : FAIL \n\n Create 실패 \n RegCreateKey()를 다시 확인하십시오.", L"KeyCreate 실패", MB_OK);
		#endif
	wresult(__FILE__, __LINE__, "RegCreateKeyW", meg, " RegCreateKeyW() : PASS", meg);

	return true;
}

/**
providing only for compatibility with 16-bit versions of Windows
app should use the RegOpenKeyEx func.
RegOpenKeyEx func is in TestRegistry.cpp file.
*/




BOOL test_RegOpenKeyW(){
	
	HWND hWnd =0;
	HKEY newKey;
	HKEY hKey = HKEY_CURRENT_USER;

	LSTATUS Create_Result;
	LSTATUS Open_Result;

	int wresult_value=0;
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_RegOpenKeyW\n");
	#endif


	Create_Result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",&newKey);

	if(Create_Result == ERROR_SUCCESS){
		Open_Result = RegOpenKeyW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position", &newKey);

		if(Open_Result == ERROR_SUCCESS){
			strcpy(meg, " RegOpenKeyW() : PASS \n\n SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position 위치를 확인하십시오.");

			wresult_value=1;
		}else
			strcpy(meg, " RegOpenKeyW() : FAIL \n\n Create는 정상 완료되었으나 Open에서 실패했습니다.");
	}else
		#ifdef OQADBG
		MessageBox(hWnd, L" RegCreateKey() : FAIL \n\n Create 실패 \n RegCreateKey()를 다시 확인하십시오.", L"KeyCreate 실패", MB_OK);
		#endif
	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegOpenKeyW", buf, "1", meg);
	return true;

}

BOOL test_RegDeleteKeyW(){
	HKEY hKey = HKEY_CURRENT_USER;
	HKEY newKey;
	RECT rt;

	LSTATUS Create_Result;
	LSTATUS Open_Result;
	LSTATUS Delete_Result;

	int wresult_value=0;
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_RegDeleteKeyW\n");
	#endif


	Create_Result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",&newKey);

	if(Create_Result == ERROR_SUCCESS){

		// test_RegDeleteKeyW 에서는 Key 만들어서 삭제하기 때문에 굳이 아래 set을 할 필요는 없음. 바로 delete 들어가도 OK.
		Open_Result = RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);
		if(Open_Result == ERROR_SUCCESS){

			RegSetValueExW(newKey, L"Top",0,REG_DWORD,(LPBYTE)&rt.top,sizeof(LONG));
			RegSetValueExW(newKey, L"Right",0,REG_DWORD,(LPBYTE)&rt.right,sizeof(LONG));
			RegSetValueExW(newKey, L"Bottom",0,REG_DWORD,(LPBYTE)&rt.bottom,sizeof(LONG));
			RegSetValueExW(newKey, L"Left",0,REG_DWORD,(LPBYTE)&rt.left,sizeof(LONG));

			Delete_Result = RegDeleteKeyW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position");

			if(Delete_Result == ERROR_SUCCESS){
				strcpy(meg, " RegDeleteKeyW() : PASS \n\n Left Key 삭제 시도 → 성공 \n 남은 Key : Top, Right, Bottom");
				wresult_value=1;

				//마지막에 Key를 닫아줘야 함
				RegCloseKey(newKey);
			}else
				strcpy(meg, " RegDeleteKeyW() : FAIL \n\n Create성공 → Open 성공 → Set 성공 → Delete 실패 \n RegDeleteKeyW()가 잘못되었습니다.");
		}else
			strcpy(meg, " RegOpenKeyEx() : FAIL \n\n Create성공 → Open 실패 \n RegOpenKeyEx()가 잘못되었습니다.");
	}else
		strcpy(meg, GetErrorMessage("RegCreateKey() 실패 : \n\n RegCreateKey()가 잘못되었습니다. \n", GetLastError()));

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegDeleteKeyW", buf, "1", meg);

	return true;
}

//레지스트리 키or 속성 변경 사항을 caller에 알림
BOOL test_RegNotifyChangeKeyValue(){
	HKEY key = NULL;
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_RegNotifyChangeKeyValue\n");
	#endif


	LRESULT result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE", 0, STANDARD_RIGHTS_READ | KEY_QUERY_VALUE | KEY_NOTIFY, &key);

	if(result != ERROR_SUCCESS) {
		#ifdef OQADBGPRINT
		printf("Open 실패 \n RegOpenKeyEx()가 잘못되었습니다.");
		#endif

		return -1;
	}
	DWORD regFilter = REG_NOTIFY_CHANGE_NAME | REG_NOTIFY_CHANGE_ATTRIBUTES | REG_NOTIFY_CHANGE_LAST_SET | REG_NOTIFY_CHANGE_SECURITY;
	// REG_NOTIFY_CHANGE_NAME - 레지스트리 키가 변경, 삭제, 추가가 되는 경우
	// REG_NOTIFY_CHANGE_ATTRIBUTES - 레지스트리 키의 속성이 변경되는 경우 (사용권한설정 등)
	// REG_NOTIFY_CHANGE_LAST_SET - 레지스트리에 접근하고 있는 경우
	// REG_NOTIFY_CHANGE_SECURITY -  레지스트리 사용 권한 설정이 변경되는 경우

	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	//printf("Start Notify Change Key Value.\n");
	// 임시로 5번 루프가 반복되도록 했다.
	for(int i=0; i < 1; ++i) {
		result = RegNotifyChangeKeyValue(key, true, regFilter, hEvent, true);

		if (result != ERROR_SUCCESS) {
			#ifdef OQADBGPRINT
			printf("[ERROR] RegNotifyChangeKeyValue.\n");
			#endif

			return -1;
		}else{ //result == ERROR_SUCCESS
			strcpy(meg, " RegNotifyChangeKeyValue() : PASS");
		}
		wresult(__FILE__, __LINE__, "RegNotifyChangeKeyValue", meg, " RegNotifyChangeKeyValue() : PASS", meg);

	}
	RegCloseKey(key);
	CloseHandle(hEvent);

	return true;
}
/**
BOOL test_RegLoadMUIStringA(){



	RegLoadMUIStringA(syscall.Handle(k), pname, &buf[0], uint32(len(buf)), &buflen, 0, pdir);

	return true;
}
*/


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
	////KEY 삭제해야함. 권한.

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
	////KEY 삭제해야함. 권한.

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
		strcpy(meg, GetErrorMessage(" Registry Load에 실패했습니다. \n\n Load한 후 다시 Unload를 시도해 주십시오. \n 그래도 실행되지 않는다면 관리자 권한을 체크하십시오", GetLastError()));
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
		 strcpy(meg, GetErrorMessage(" Registry Load에 실패했습니다. \n\n Load한 후 다시 Unload를 시도해 주십시오. \n 그래도 실행되지 않는다면 관리자 권한을 체크하십시오", GetLastError()));
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
			strcpy(meg, GetErrorMessage(" Registry Key 오픈 실패 \n\n RegOpenKeyEx 함수를 다시 확인하세요", GetLastError()));
		}
	}else
		strcpy(meg, GetErrorMessage(" Registry Key 생성 실패 \n\n RegCreateKey 함수를 다시 확인하세요", GetLastError()));

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
			strcpy(meg, GetErrorMessage(" Registry Key 오픈 실패 \n\n RegOpenKeyEx 함수를 다시 확인하세요", GetLastError()));
		}
	}else
		strcpy(meg, GetErrorMessage(" Registry Key 생성 실패 \n\n RegCreateKey 함수를 다시 확인하세요", GetLastError()));

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
			strcpy(meg, GetErrorMessage(" Registry Key 오픈 실패 \n\n RegOpenKeyEx 함수를 다시 확인하세요", GetLastError()));
		}
	}else
		strcpy(meg, GetErrorMessage(" Registry Key 생성 실패 \n\n RegCreateKey 함수를 다시 확인하세요", GetLastError()));

	wresult(__FILE__, __LINE__, "RegRestoreKeyA", buf, "SUCCESS", meg);

	DeleteFileA(lpFile);
	RegCloseKey(hKey);

	return true;

}
*/

/**
레지스트리 키 트리를 삭제합니다.
생성 → 오픈 → 삭제의 과정을 거친 후 오픈 동작으로 키가 제대로 삭제되었는지 확인합니다.
삭제 후 키를 클릭했을 때 에러 메시지 박스가 호출되면 정상입니다.
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
		//printf("create 성공");
		result = RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);
		if(result == ERROR_SUCCESS){
			//printf("open 성공");
			result = RegDeleteTreeW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest");
			if(result == ERROR_SUCCESS){
				//printf("delete 성공");
				result = RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_2\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);
				if(result != ERROR_SUCCESS){
					//printf("open 안되니까 성공");
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

BOOL test_RegEnumKeyEx(){

	#ifdef OQADBGPRINT
	printf("test_
		\n");
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
	printf("▼RegEnumKeyExW() 출력▼ \n");
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

	strcpy(meg, " RegEnumKeyExW() : PASS \n\n 터미널에서 pluse_enum 값 출력을 확인하십시오.");
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

	/** Registry 생성 */
	result = RegCreateKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL);
	if(result != ERROR_SUCCESS)
		strcpy(meg, " 레지스트리 CREATE 실패");

	/** 생성한 Registry key에 value값으로 Left 넣음 */
	result = RegSetValueExW(newKey, L"Left",0,REG_DWORD,(LPBYTE)&rt.left,sizeof(LONG));
	if(result != ERROR_SUCCESS)
		strcpy(meg, " 레지스트리 SET 실패");

	result = RegGetValueW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", L"Left", RRF_RT_REG_BINARY | RRF_RT_REG_DWORD, NULL, (LPDWORD)&value, &BufferSize);
	
	/** RegGetValueW 성공, 실패 경우 */ 
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

	1. 문제점 event 발생
	2. Windows가 WER 호출
	3. WER는 데이터를 수집하고 보고서를 작성하며 필요한 경우 사용자에게 동의 여부 묻는 메시지를 표시
	4. WER은 사용자가 동의한 경우 보고서를 Watson Server(microsoft)로 보냄
	5. Watson 서버가 추가 데이터를 요청하면 WER은 데이터를 수집하고 필요한 경우 사용자에게 동의 여부를 묻는 메시지를 표시합니다.
	6. 응용 프로그램이 복구 및 다시 시작을 위해 등록 된 경우 WER은 등록 된 콜백 함수를 실행하면서 데이터가 압축되어 Microsoft에 전송됩니다 (사용자가 동의 한 경우).
	7. Microsoft에서 문제에 대한 응답을 사용할 수있는 경우 사용자에게 알립니다.

*/


BOOL test_RegOpenCurrentUser(){
	/** 사용자 current thread의 핸들 검색 */

	#ifdef OQADBGPRINT
	printf("test_RegOpenCurrentUser \n");
	#endif

	HKEY keyCurrentUser;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";
	int wresult_value = 0;

	/** 첫 번째 parameter : REGSAM형 → KEY_READ : Combination of KEY_QUERY_VALUE(하위 키 데이터를 쿼리 가능), KEY_ENUMERATE_SUB_KEYS(하위 키 열거), and KEY_NOTIFY(변경 통지) access.*/
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
		strcpy(meg, " OpenProcessToken() 비정상 \n\n process와 연관된 Access Token을 다시 여십시오 ");
		
		sprintf(buf, "%d", wresult_value);
		wresult(__FILE__, __LINE__, "RegOpenUserClassesRoot", buf, "1", meg);

		return result;
	}



BOOL test_RegRestoreKeyA(){

#ifdef OQADBGPRINT
	printf("test_RegRestoreKeyA \n");
#endif

	/** 두 번째 파라미터 lpFile : name of the file with the registry information. 
	created by using the RegSaveKey function. 
	→ RegSaveKey(hKey, lpFile, lpSecurityAttributes(NULL이면 default security descriptor 가져옴))	
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

	/** 두 번째 파라미터 lpFile : name of the file with the registry information. 
	created by using the RegSaveKey function. 
	→ RegSaveKey(hKey, lpFile, lpSecurityAttributes(NULL이면 default security descriptor 가져옴))	
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
		strcpy(meg, "RegLoadMUIStringA : FAIL \n\n pcbData가 너무 작습니다.");
	else if(result == ERROR_CALL_NOT_IMPLEMENTED)
		strcpy(meg, "RegLoadMUIStringA : FAIL \n\n ANSI version → 정상");
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
	//	strcpy(meg, "RegLoadMUIStringW : SUCCESS");
	//}else if(result == ERROR_MORE_DATA)
	//	strcpy(meg, "RegLoadMUIStringW : FAIL \n\n pcbData가 너무 작습니다.");
	//else if(result == ERROR_CALL_NOT_IMPLEMENTED)
	//	strcpy(meg, "RegLoadMUIStringW : FAIL \n\n ANSI version → 정상");
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
		strcpy(meg, "RegLoadMUIStringW : FAIL \n\n pcbData가 너무 작습니다.");
	else if(result == ERROR_CALL_NOT_IMPLEMENTED)
		strcpy(meg, "RegLoadMUIStringW : FAIL \n\n ANSI version → 정상");
	else
		strcpy(meg, "RegLoadMUIStringW : FAIL");
	
	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegLoadMUIStringW", buf, "1", meg);

	return result;
}  

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383
BOOL test_RegEnumValueAs(){

	//DWORD   cType;
	LSTATUS result;
	HKEY hKey=HKEY_CURRENT_USER;
	//DWORD cchValue = MAX_VALUE_NAME; 

	//int i = 1;
	int wresult_value = 0;
	int err = GetLastError();
	char meg[BUFSIZ] = "FAIL";
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
				strcpy(meg, " RegEnumValueA : PASS \n\n 두 번째 인자 dwIndex = 0 → 첫 번째 값만 RegEnum");
				wresult_value=1;
			}else if(result == ERROR_NO_MORE_ITEMS){
				strcpy(meg, " 사용할 수 있는 값이 더 이상 없습니다.");
			}else if(result == ERROR_MORE_DATA){
				strcpy(meg, " lpData 버퍼가 값을 받기에 너무 작습니다.");
			}else{
				strcpy(meg, "FAIL");
				printf("err : %d" ,err);
			}
		}
	}
	printf("err : %d" ,err);

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegLoadMUIStringW", buf, "1", meg);

	return result;
}

BOOL test_RegEnumValueA(){

	HKEY hKey = HKEY_CURRENT_USER;
	TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string 
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
    DWORD    cchClassName = MAX_PATH;  // size of class string 
    DWORD    cSubKeys=0;               // number of subkeys 
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
 
    
    retCode = RegQueryInfoKey(hKey, achClass,&cchClassName, NULL, &cSubKeys, &cbMaxSubKey, &cchMaxClass, &cValues, &cchMaxValue, &cbMaxValueData, &cbSecurityDescriptor, &ftLastWriteTime);  

    if(cSubKeys){
        printf( "\nNumber of subkeys: %d\n", cSubKeys);
		

        for(i=0; i<cSubKeys; i++) { 
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i, achKey, &cbName, NULL, NULL, NULL, &ftLastWriteTime); 
            if(retCode == ERROR_SUCCESS) {
                _tprintf(TEXT("(%d) %s\n"), i+1, achKey);
            }
        }
    } 
 
    // Enumerate the key values. 

    if (cValues == 0) 
    {
        printf( "\nNumber of values: %d\n", cValues);

        for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++) 
        { 
            cchValue = MAX_VALUE_NAME; 
            achValue[0] = '\0'; 
            retCode = RegEnumValue(hKey, i, 
                achValue, 
                &cchValue, 
                NULL, 
                NULL,
                NULL,
                NULL);
 
            if (retCode == ERROR_SUCCESS ) 
            { 
                _tprintf(TEXT("(%d) %s\n"), i+1, achValue); 
            } 
        }
    }
	
	printf("벨류 0이어서 나옴");

	return true;
}
