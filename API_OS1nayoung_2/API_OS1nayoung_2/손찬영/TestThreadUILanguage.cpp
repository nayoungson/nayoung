#include "TestThreadUILanguage.h"


/**
* LANGID GetThreadUILanguage(void);
* ���� �����忡 ���� ù ��° ����� �������̽� ��� �� ��� �ĺ��ڸ� ��ȯ�Ѵ�.
* @author : ������  
*
* @param  ����
* @return SetThreadUILanguage �Ǵ� SetThreadPreferredUILanguages�� ���� ������� ��������� ����� ����� �ĺ��ڸ� ��ȯ
*/
BOOL test_GetThreadUILanguage()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	LANGID LangId = 0, ret = 0;
	const LANGID expectLangId = MAKELANGID(LANG_KOREAN, SUBLANG_KOREAN);

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	ret = GetThreadUILanguage();
	#ifdef OQADBGPRINT
	printf("Set�� �� ���� ��= %d\n", ret);
	#endif


	if(expectLangId == ret){
		sprintf(msg, "GetThreadUILanguage ���� : LangId = %d", ret);
		strcpy(buf, "GetThreadUILanguage ����");
		
	}else{
		sprintf(msg, GetErrorMessage("GetThreadUILanguage ���� :", GetLastError()));
		strcpy(buf, "GetThreadUILanguage ����");
		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetThreadUILanguage ����", msg);

	return result;
}


/**
* LANGID SetThreadUILanguage(
  _In_ LANGID LangId
);
* ���� �������� ����� �������̽� �� �����Ѵ�.
* @author : ������  
*
* @param  LangId	�������� ����� �������̽� �� ���� ��� �ĺ���
* @return			�������� ��� �Է� ��� �ĺ��ڸ� ����, �Է� ��� �ĺ��ڰ� 0�� �ƴϰ� �Լ��� �����ϸ� ��ȯ ���� �Է� ��� �ĺ��ڿ� �ٸ�.
*/
BOOL test_SetThreadUILanguage()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	LANGID LangId = 0, ret = 0;
	const LANGID expectLangId = MAKELANGID(LANG_ENGLISH, SUBLANG_NEUTRAL);
	LANGID backupLangId;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	backupLangId = GetThreadUILanguage();
	#ifdef OQADBGPRINT
	printf("ó�� Get�� �� ���� ��= %d\n", backupLangId);
	#endif

	ret = SetThreadUILanguage(expectLangId);
	#ifdef OQADBGPRINT
	printf("Set�� �� ���� ��= %d\n", ret);
	#endif

	LangId = GetThreadUILanguage();

	#ifdef OQADBGPRINT
	printf("Get�� LangId = %d\n", LangId);
	printf("���ϴ� LangId�� = %d\n", expectLangId);
	#endif

	if(expectLangId == ret && ret == LangId){
		sprintf(msg, "SetThreadUILanguage ���� : LangId = %d", LangId);
		strcpy(buf, "SetThreadUILanguage ����");
		
	}else{
		sprintf(msg, GetErrorMessage("SetThreadUILanguage ���� :", GetLastError()));
		strcpy(buf, "SetThreadUILanguage ����");
		result = FALSE;
	}
	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "SetThreadUILanguage ����", msg);

	if(backupLangId != SetThreadUILanguage(backupLangId)){
		#ifdef OQADBGPRINT
		printf("LangId ���� ����.. �ٸ� language���� �Լ��� ������ �� �ֽ��ϴ�.\n");
		#endif
	}

	return result;

}


/**
* BOOL GetThreadPreferredUILanguages(
  _In_      DWORD   dwFlags,
  _Out_     PULONG  pulNumLanguages,
  _Out_opt_ PZZWSTR pwszLanguagesBuffer,
  _Inout_   PULONG  pcchLanguagesBuffer
);
* ���� �����忡 ���� ������ �⺻ UI �� �˻��Ѵ�.
* @author : ������  
*
* @param  dwFlags				��� ���� �� ���͸��� �ĺ��ϴ� �÷���
* @param  pulNumLanguages		pwszLanguagesBuffer ���� �˻� �� ��� ���� ����Ű�� ������
* @param  pwszLanguagesBuffer	������ ������ �⺻ UI ����Ʈ ���۸� ����Ű�� ������
* @param  pcchLanguagesBuffer	pwszLanguagesBuffer�� ����Ű�� ��� ������ ũ�⸦ ���ڷ� ����Ű�� ������
* @return						����/���� ����
*/
BOOL test_GetThreadPreferredUILanguages()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	ULONG  ulNumLanguages = BUFSIZ;
	WCHAR LanguagesBuffer[BUFSIZ] = {0, };
	ULONG  cchLanguagesBuffer = BUFSIZ;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	result = GetThreadPreferredUILanguages(MUI_LANGUAGE_ID & MUI_MERGE_USER_FALLBACK, &ulNumLanguages, (PZZWSTR)&LanguagesBuffer, &cchLanguagesBuffer);

	if(result){
		strcpy(buf, "GetThreadPreferredUILanguages ����");
		strcpy(msg, buf);
		
	}else{
		sprintf(msg, GetErrorMessage("GetThreadPreferredUILanguages ���� :", GetLastError()));
		strcpy(buf, "GetThreadPreferredUILanguages ����");
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetThreadPreferredUILanguages ����", msg);

	return result;
}


/**
* BOOL SetThreadPreferredUILanguages(
  _In_      DWORD    dwFlags,
  _In_opt_  PCZZWSTR pwszLanguagesBuffer,
  _Out_opt_ PULONG   pulNumLanguages
);
* ���� �����忡 ���� ������ �⺻ UI �� �����Ѵ�.
* @author : ������  
*
* @param  dwFlags				������ �� ���� ���� �� ���͸��� �ĺ��ϴ� �÷���
* @param  pwszLanguagesBuffer	dwFlags�� ���� �����Ǵ� ���Ŀ���, ���� ���̰�, null�� �ܶ� ����������Ʈ�� ������, double�� ������ ���� ��Ʈ���� ������ ������
* @param  pulNumLanguages		������ �⺻ UI ��� ��Ͽ��� �Լ��� ���� �� ��� ���� ����Ű�� ������
* @return						����/���� ����
*/
BOOL test_SetThreadPreferredUILanguages()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	SetThreadPreferredUILanguages(MUI_LANGUAGE_ID, NULL, NULL);

	if(SetThreadPreferredUILanguages(MUI_LANGUAGE_ID, NULL, NULL)){
		strcpy(buf, "SetThreadPreferredUILanguages ����");
		
	}else{
		strcpy(buf, "SetThreadPreferredUILanguages ����");
		
		result = FALSE;
	}
	strcpy(msg, buf);

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "SetThreadPreferredUILanguages ����", msg);

	return result;
}


