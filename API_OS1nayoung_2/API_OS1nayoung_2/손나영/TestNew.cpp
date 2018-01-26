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

	/* �Ķ���� ���� �� ��ŭ �׽�Ʈ�Լ��� ȣ�� */
	for(int i=0; i<nParam; i++){
		/* �׽�Ʈ ���� �� ��� ���� ���� */
		//for(int j=0; j<nParam; j++){
			testResult = test_RegCreateKeyW(hKey[i], lpSubKey, &phkResult);

			/*�α׿� ���ڰ��� ����ϱ� ���� ���ڿ� ����*/
		//	strcpy(result, testResult.result?"TRUE":"FALSE");
			strcpy(msg, __FUNCTION__);
		//	sprintf(buf, "(NULL, %s, \"%s\")", expect[i], lpName[j]);
			strcat(msg, buf);
			strcpy(buf, strstr(msg, "test_"));

			/* �׽�Ʈ�� ���� ����, �����ߴٸ� ���� �������� �α׷� ���� */
			log(__FILE__, __LINE__ , __FUNCTION__, result, expect[TRUE], buf, testResult.msg);

			/* 1���� �׽�Ʈ�� ���� �� run_test_{API�Լ���}()�� FALSE�� ������ */
			if(!testResult.result){
				caseResult = FALSE;
			}
		//}


	}

	return caseResult;

}
