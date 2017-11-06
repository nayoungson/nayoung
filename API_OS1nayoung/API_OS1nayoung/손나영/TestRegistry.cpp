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
		strcpy(meg, " RegCreateKeyExW : PASS \n\n ������Ʈ�� ������(RegEdit) ����\n HKEY_CURRENT_USER > SOFTWARE > NAYOUNG_API_TEST Ȯ��");
			
	}else
		strcpy(meg, " ������Ʈ�� Ű ���� ����");

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
		
		strcpy(meg, " RegSetValueExw : PASS \n\n NAYOUNG_API_TEST > RegiTest �Ʒ� Top, Right, Bottom, Left ���� \n �� ������ : 0   ���� : 16����");
	}else
		strcpy(meg, " ������Ʈ�� �� set ����");

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
			strcpy(meg, " RegOpenKeyEx() : PASS \n\n SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position ��ġ�� Ȯ���Ͻʽÿ�.");
		}else
			strcpy(meg, " RegOpenKeyEx() : FAIL \n\n Create�� ���� �Ϸ�Ǿ����� Open���� �����߽��ϴ�.");
	}else{
		#ifdef OQADBG
		MessageBox(hWnd, L" RegCreateKey() : FAIL \n\n Create ���� \n RegCreateKey()�� �ٽ� Ȯ���Ͻʽÿ�.", L"KeyCreate ����", MB_OK);
		#endif
	}
	wresult(__FILE__, __LINE__, "RegOpenKeyEx", "ERROR_SUCCESS", "ERROR_SUCCESS", meg);
	return true;
}

// 4 RegEnumValueW �Ϸ� *
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

	/* ���� ����� ������ ����Ʈ �ڽ��� ä�� ����
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
		strcpy(meg, " RegEnumValueW : PASS \n\n �� ��° ���� dwIndex = 0 �� ù ��° ���� RegEnum");

	}else
		strcpy(meg, "FAIL");

	wresult(__FILE__, __LINE__, "RegEnumValueW", _itoa(result, buf, 10), _itoa(ERROR_SUCCESS, buf, 10), meg);
	return true;
}



// RegQueryInfoKeyW �Ϸ� *
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


//RegQueryValueExW �Ϸ� 
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


// RegCloseKey �Ϸ� *
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
				strcpy(meg, " RegCloseKey : PASS \n\n RegCreateKeyW�� key ���� �� �� RegCloseKey ����");
			}else
				strcpy(meg, "RegCloseKey  : FAIL \n\n RegCreateKeyW ���������� �� RegCloseKey ����");
	}else{
		#ifdef OQADBG
		MessageBox(hWnd, L"RegCreateKeyW�Լ� ���з� ���� RegCloseKey �Լ��� ������ �� �����ϴ�. Regsitry key�� �ٽ� �����Ͻʽÿ�", L"fail", MB_OK);
		#endif
	}
	wresult(__FILE__, __LINE__, "RegCloseKey", meg, " RegCloseKey : PASS \n\n RegCreateKeyW�� key ���� �� �� RegCloseKey ����", meg);

	return true;
}

//RegDeleteKeyExW �Ϸ� *
BOOL test_RegDeleteKeyExW(){  
	LSTATUS result;

	char meg[BUFSIZ] = "FAIL";

 	
	#ifdef OQADBGPRINT
	printf("test_RegDeleteKeyExW\n");
	#endif

	result = RegDeleteKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", KEY_WOW64_32KEY, 0);

	//if(RegCreateKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\NAYOUNG_API_TEST\\RegiTest\\Position", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&newKey, NULL)) == ERROR_SUCCESS){
	if(result == ERROR_SUCCESS){
		strcpy(meg, " RegDeleteKeyExW \n\n SOFTWARE > NAYOUNG_API_TEST > RegiTest �Ʒ� Position ����");

	}else
		strcpy(meg, " RegDeleteKeyExW : FAIL");

	wresult(__FILE__, __LINE__, "RegDeleteKeyExW", meg, " RegDeleteKeyExW \n\n SOFTWARE > NAYOUNG_API_TEST > RegiTest �Ʒ� Position ����", meg);
	return true;
}



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
				//MessageBox(hWnd, L" RegDeleteValueW() : PASS \n\n Left Key ���� �õ� �� ���� \n ���� Key : Top, Right, Bottom", L"Registry_2 ����", MB_OK);
				strcpy(meg, " RegDeleteValueW() : PASS \n\n Left Key ���� �õ� �� ���� \n ���� Key : Top, Right, Bottom");

				//�������� Key�� �ݾ���� ��
				RegCloseKey(newKey);
			}else
				strcpy(meg, " RegDeleteValueW() : FAIL \n\n Create���� �� Open ���� �� Set ���� �� Delete ���� \n RegDeleteValueW()�� �߸��Ǿ����ϴ�.");
				//MessageBox(hWnd, L" RegDeleteValueW() : FAIL \n\n Create���� �� Open ���� �� Set ���� �� Delete ���� \n RegDeleteValueW()�� �߸��Ǿ����ϴ�.", L"KeyDelete ����", MB_OK);	
		}else
			strcpy(meg, " RegOpenKeyEx() : FAIL \n\n Create���� �� Open ���� \n RegOpenKeyEx()�� �߸��Ǿ����ϴ�.");
			//MessageBox(hWnd, L" RegOpenKeyEx() : FAIL \n\n Create���� �� Open ���� \n RegOpenKeyEx()�� �߸��Ǿ����ϴ�.", L"KeyOpen ����", MB_OK);	
	}else
		strcpy(meg, " RegCreateKey() : FAIL \n\n Create ���� \n RegCreateKey()�� �߸��Ǿ����ϴ�.");
		//MessageBox(hWnd, L" RegCreateKey() : FAIL \n\n Create ���� \n RegCreateKey()�� �߸��Ǿ����ϴ�.");	
	
	wresult(__FILE__, __LINE__, "RegDeleteValueW", meg, " RegDeleteValueW() : PASS \n\n Left Key ���� �õ� �� ���� \n ���� Key : Top, Right, Bottom", meg);
	return true;
}

// 0911 ���� 2/3
// ������ �����ִ� ������Ʈ�� Ű�� ���� Ű�� ����(Ex)
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
	SendMessage(hList,LB_ADDSTRING,0,(LPARAM)" ^^^ �� �ܰ� ���� ^^^ ");
	
	Result=ERROR_SUCCESS;
	#ifdef OQADBGPRINT
	printf("��RegEnumKeyExW() ��¡� \n");
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

	strcpy(meg, " RegEnumKeyExW() : PASS \n\n �͹̳ο��� pluse_enum �� ����� Ȯ���Ͻʽÿ�.");
	wresult(__FILE__, __LINE__, "RegEnumKeyEx", meg, " RegEnumKeyExW() : PASS \n\n �͹̳ο��� pluse_enum �� ����� Ȯ���Ͻʽÿ�.", meg);
	return true;
}

// 0911 ���� 3/3
// ������ �����ִ� ������Ʈ�� Ű�� ���� Ű�� ����
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
	printf("��RegEnumKeyW() ��¡� \n");
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

	strcpy(meg, " RegEnumKeyW() : PASS \n\n �͹̳ο��� pluse_enum �� ����� Ȯ���Ͻʽÿ�.");
	wresult(__FILE__, __LINE__, "RegEnumKeyEx", meg, " RegEnumKeyW() : PASS \n\n �͹̳ο��� pluse_enum �� ����� Ȯ���Ͻʽÿ�.", meg);
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
		MessageBox(hWnd, L" RegCreateKeyW() : FAIL \n\n Create ���� \n RegCreateKey()�� �ٽ� Ȯ���Ͻʽÿ�.", L"KeyCreate ����", MB_OK);
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
			strcpy(meg, " RegOpenKeyW() : PASS \n\n SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position ��ġ�� Ȯ���Ͻʽÿ�.");

			wresult_value=1;
		}else
			strcpy(meg, " RegOpenKeyW() : FAIL \n\n Create�� ���� �Ϸ�Ǿ����� Open���� �����߽��ϴ�.");
	}else
		#ifdef OQADBG
		MessageBox(hWnd, L" RegCreateKey() : FAIL \n\n Create ���� \n RegCreateKey()�� �ٽ� Ȯ���Ͻʽÿ�.", L"KeyCreate ����", MB_OK);
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

		// test_RegDeleteKeyW ������ Key ���� �����ϱ� ������ ���� �Ʒ� set�� �� �ʿ�� ����. �ٷ� delete ���� OK.
		Open_Result = RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);
		if(Open_Result == ERROR_SUCCESS){

			RegSetValueExW(newKey, L"Top",0,REG_DWORD,(LPBYTE)&rt.top,sizeof(LONG));
			RegSetValueExW(newKey, L"Right",0,REG_DWORD,(LPBYTE)&rt.right,sizeof(LONG));
			RegSetValueExW(newKey, L"Bottom",0,REG_DWORD,(LPBYTE)&rt.bottom,sizeof(LONG));
			RegSetValueExW(newKey, L"Left",0,REG_DWORD,(LPBYTE)&rt.left,sizeof(LONG));

			Delete_Result = RegDeleteKeyW(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position");

			if(Delete_Result == ERROR_SUCCESS){
				strcpy(meg, " RegDeleteKeyW() : PASS \n\n Left Key ���� �õ� �� ���� \n ���� Key : Top, Right, Bottom");
				wresult_value=1;

				//�������� Key�� �ݾ���� ��
				RegCloseKey(newKey);
			}else
				strcpy(meg, " RegDeleteKeyW() : FAIL \n\n Create���� �� Open ���� �� Set ���� �� Delete ���� \n RegDeleteKeyW()�� �߸��Ǿ����ϴ�.");
		}else
			strcpy(meg, " RegOpenKeyEx() : FAIL \n\n Create���� �� Open ���� \n RegOpenKeyEx()�� �߸��Ǿ����ϴ�.");
	}else
		strcpy(meg, GetErrorMessage("RegCreateKey() ���� : \n\n RegCreateKey()�� �߸��Ǿ����ϴ�. \n", GetLastError()));

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegDeleteKeyW", buf, "1", meg);

	return true;
}

//������Ʈ�� Űor �Ӽ� ���� ������ caller�� �˸�
BOOL test_RegNotifyChangeKeyValue(){
	HKEY key = NULL;
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_RegNotifyChangeKeyValue\n");
	#endif


	LRESULT result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE", 0, STANDARD_RIGHTS_READ | KEY_QUERY_VALUE | KEY_NOTIFY, &key);

	if(result != ERROR_SUCCESS) {
		#ifdef OQADBGPRINT
		printf("Open ���� \n RegOpenKeyEx()�� �߸��Ǿ����ϴ�.");
		#endif

		return -1;
	}
	DWORD regFilter = REG_NOTIFY_CHANGE_NAME | REG_NOTIFY_CHANGE_ATTRIBUTES | REG_NOTIFY_CHANGE_LAST_SET | REG_NOTIFY_CHANGE_SECURITY;
	// REG_NOTIFY_CHANGE_NAME - ������Ʈ�� Ű�� ����, ����, �߰��� �Ǵ� ���
	// REG_NOTIFY_CHANGE_ATTRIBUTES - ������Ʈ�� Ű�� �Ӽ��� ����Ǵ� ��� (�����Ѽ��� ��)
	// REG_NOTIFY_CHANGE_LAST_SET - ������Ʈ���� �����ϰ� �ִ� ���
	// REG_NOTIFY_CHANGE_SECURITY -  ������Ʈ�� ��� ���� ������ ����Ǵ� ���

	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	//printf("Start Notify Change Key Value.\n");
	// �ӽ÷� 5�� ������ �ݺ��ǵ��� �ߴ�.
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

