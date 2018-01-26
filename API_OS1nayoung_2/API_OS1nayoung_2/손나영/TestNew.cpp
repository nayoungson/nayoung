#include "TestNew.h"

TESTCASE test_RegCreateKeyW(HKEY hKey, LPCTSTR lpSubKey, PHKEY phkResult){
	
	LONG result;
	TESTCASE testResult;

	result = RegCreateKeyW(hKey,lpSubKey, phkResult);

	if(result == ERROR_SUCCESS){
		sprintf(testResult.msg, " RegCreateKeyW() : SUCCESS");

	}else{
		sprintf(testResult.msg, " RegCreateKeyW() : FAIL");
		testResult.result = FALSE;
	}

	return testResult;
}

BOOL run_test_RegCreateKeyW(){

	const int nParam = 2;
	HKEY hKey[nParam] = {HKEY_CURRENT_USER, NULL};
	LPCTSTR lpSubKey =  L"SOFTWARE\\NAYOUNG_API_TEST_3\\RegiTest\\Position";
	HKEY phkResult;

	char msg[BUFSIZ], buf[BUFSIZ];
	char *expect[2] = {"FALSE", "TRUE"};
	char result[BUFSIZ];
	TESTCASE testResult;
	BOOL caseResult = TRUE;

	/* 파라미터 묶음 수 만큼 테스트함수를 호출 */
	for(int i=0; i<nParam; i++){
		/* 테스트 수행 후 결과 값을 받음 */
		//for(int j=0; j<nParam; j++){
			testResult = test_RegCreateKeyW(hKey[i], lpSubKey, &phkResult);

			/*로그에 인자값을 출력하기 위한 문자열 생성*/
		//	strcpy(result, testResult.result?"TRUE":"FALSE");
			strcpy(msg, __FUNCTION__);
		//	sprintf(buf, "(NULL, %s, \"%s\")", expect[i], lpName[j]);
			strcat(msg, buf);
			strcpy(buf, strstr(msg, "test_"));

			/* 테스트한 인자 값과, 실패했다면 실패 사유까지 로그로 남김 */
			log(__FILE__, __LINE__ , __FUNCTION__, result, expect[TRUE], buf, testResult.msg);

			/* 1개의 테스트라도 실패 시 run_test_{API함수명}()은 FALSE를 리턴함 */
			if(!testResult.result){
				caseResult = FALSE;
			}
		//}


	}

	return caseResult;

}
