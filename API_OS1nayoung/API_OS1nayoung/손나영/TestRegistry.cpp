#include "TestRegistry.h"
#include <Windows.h>
#include <TlHelp32.h>

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

		Open_Result = RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);
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

