#include "setgetkey.h"


/**
- 다음 조건이 충족되는 경우에만 성공합니다.
키의 소유자 또는 그룹이 설정되면 발신자에게 WRITE_OWNER 권한이 있거나 SE_TAKE_OWNERSHIP_NAME 권한이 있어야합니다.
키의 임의 액세스 제어 목록 (DACL)이 설정되는 경우 호출자는 WRITE_DAC 권한을 갖고 있거나 개체의 소유자 여야합니다.
키의 시스템 액세스 제어 목록 (SACL)이 설정되어 있으면 호출자는 SE_SECURITY_NAME 권한이 있어야합니다.
*/


BOOL test_RegSetKeySecurity(){
	
	HKEY newKey;
	HKEY hKey = HKEY_CURRENT_USER;
	
	BOOL SetKey_result;
	LSTATUS Create_Result;
	LSTATUS Open_Result;

	int wresult_value=0;
	char buf[BUFSIZ]; 
	char meg[BUFSIZ] = "FAIL";

	//BYTE SDBuffer[4096] = {0, };
	//SECURITY_DESCRIPTOR* sd = (SECURITY_DESCRIPTOR*)SDBuffer;

	PSECURITY_DESCRIPTOR pSD = 0;

	Create_Result = RegCreateKey(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",&newKey);

	if(Create_Result == ERROR_SUCCESS){

		Open_Result = RegOpenKeyEx(hKey, L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position",0, KEY_ALL_ACCESS, &newKey);
		if(Open_Result == ERROR_SUCCESS){

			SetKey_result = RegSetKeySecurity(hKey, DACL_SECURITY_INFORMATION, pSD);
			if(SetKey_result == ERROR_SUCCESS){
				strcpy(meg, "RegSetKeySecurity() : PASS");
				wresult_value = 1;
				RegCloseKey(newKey);
			}else{
				strcpy(meg, "RegSetKeySecurity() : FAIL");
				wresult_value = 2;
			}

		}else{// Open_Result != ERROR_SUCCESS
			strcpy(meg, " RegOpenKeyEx() : FAIL \n\n Create성공 → Open 실패 \n RegOpenKeyEx()가 잘못되었습니다.");
		}

	}else{
		strcpy(meg, " RegCreateKey() : FAIL \n\n Create 실패 \n RegCreateKey()가 잘못되었습니다.");
	}
	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegSetKeySecurity", buf, "1", meg);

	return true;
}

BOOL test_RegSetKeySecurity_2(){

	DWORD ret;
	DWORD retval;

	HKEY key = 0;
	HWND hWnd = 0;
	PACL pAcl = NULL;

	SECURITY_DESCRIPTOR sd;
	ACCESS_ALLOWED_ACE* pAce = NULL;

	char buf[BUFSIZ]; 
	char meg[BUFSIZ] = "FAIL";
	int wresult_value = 0;

	if( !InitializeSecurityDescriptor( &sd, SECURITY_DESCRIPTOR_REVISION )){
		retval = -1;
		goto cleanup;
	}

	if( !SetSecurityDescriptorDacl( &sd, TRUE, pAcl, FALSE )){
		retval = -1;
		goto cleanup;
	}

	ret = RegSetKeySecurity( key, DACL_SECURITY_INFORMATION, &sd );

	if( ret == ERROR_SUCCESS ){
		retval = 0;
		strcpy(meg, "RegSetKeySecurity() : PASS");
		wresult_value = 1;
	}else{
		retval = -1;
		strcpy(meg, "RegSetKeySecurity() : FAIL");
		wresult_value = 2;
	}

cleanup:
	if( pAce != NULL )
		GlobalFree( pAce );

	if( pAcl != NULL )
		GlobalFree( pAcl );

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "RegSetKeySecurity", buf, "1", meg);

	return true;
}

BOOL test_RegGetKeySecurity(){


	return true;
}

