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
		printf("create 정상");
		result = RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);
		printf("open 정상");
		//create → open 하고 나면 load작업
		result = RegLoadKeyA(hKey, lpSubKey, lpFile);
		printf("load됨");
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
레지스트리 키 트리를 삭제합니다.
생성 → 오픈 → 삭제의 과정을 거친 후 오픈 동작으로 키가 제대로 삭제되었는지 확인합니다.
삭제 후 키를 클릭했을 때 에러 메시지 박스가 호출되면 정상입니다.
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
		strcpy(meg, " RegGetValueW : SUCCESS \n\n ");
	}else
		strcpy(meg, " RegGetValueW : FAIL");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegGetValueW", buf, "1", meg);
		
	return true;
}