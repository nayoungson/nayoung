#include "TestThreadUILanguage.h"


/**
* LANGID GetThreadUILanguage(void);
* 현재 스레드에 대한 첫 번째 사용자 인터페이스 언어 의 언어 식별자를 반환한다.
* @author : 손찬영  
*
* @param  없음
* @return SetThreadUILanguage 또는 SetThreadPreferredUILanguages에 의해 스레드와 명시적으로 연결된 언어의 식별자를 반환
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
	printf("Set한 후 리턴 값= %d\n", ret);
	#endif


	if(expectLangId == ret){
		sprintf(msg, "GetThreadUILanguage 성공 : LangId = %d", ret);
		strcpy(buf, "GetThreadUILanguage 성공");
		
	}else{
		sprintf(msg, GetErrorMessage("GetThreadUILanguage 실패 :", GetLastError()));
		strcpy(buf, "GetThreadUILanguage 실패");
		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetThreadUILanguage 성공", msg);

	return result;
}


/**
* LANGID SetThreadUILanguage(
  _In_ LANGID LangId
);
* 현재 스레드의 사용자 인터페이스 언어를 설정한다.
* @author : 손찬영  
*
* @param  LangId	스레드의 사용자 인터페이스 언어에 대한 언어 식별자
* @return			성공했을 경우 입력 언어 식별자를 리턴, 입력 언어 식별자가 0이 아니고 함수가 실패하면 반환 값은 입력 언어 식별자와 다름.
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
	printf("처음 Get한 후 리턴 값= %d\n", backupLangId);
	#endif

	ret = SetThreadUILanguage(expectLangId);
	#ifdef OQADBGPRINT
	printf("Set한 후 리턴 값= %d\n", ret);
	#endif

	LangId = GetThreadUILanguage();

	#ifdef OQADBGPRINT
	printf("Get한 LangId = %d\n", LangId);
	printf("원하는 LangId값 = %d\n", expectLangId);
	#endif

	if(expectLangId == ret && ret == LangId){
		sprintf(msg, "SetThreadUILanguage 성공 : LangId = %d", LangId);
		strcpy(buf, "SetThreadUILanguage 성공");
		
	}else{
		sprintf(msg, GetErrorMessage("SetThreadUILanguage 실패 :", GetLastError()));
		strcpy(buf, "SetThreadUILanguage 실패");
		result = FALSE;
	}
	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "SetThreadUILanguage 성공", msg);

	if(backupLangId != SetThreadUILanguage(backupLangId)){
		#ifdef OQADBGPRINT
		printf("LangId 복원 실패.. 다른 language관련 함수가 실패할 수 있습니다.\n");
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
* 현재 스레드에 대한 스레드 기본 UI 언어를 검색한다.
* @author : 손찬영  
*
* @param  dwFlags				언어 형식 및 필터링을 식별하는 플래그
* @param  pulNumLanguages		pwszLanguagesBuffer 에서 검색 한 언어 수를 가리키는 포인터
* @param  pwszLanguagesBuffer	가져온 스레드 기본 UI 언어리스트 버퍼를 가리키는 포인터
* @param  pcchLanguagesBuffer	pwszLanguagesBuffer가 가리키는 언어 버퍼의 크기를 문자로 가리키는 포인터
* @return						성공/실패 여부
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
		strcpy(buf, "GetThreadPreferredUILanguages 성공");
		strcpy(msg, buf);
		
	}else{
		sprintf(msg, GetErrorMessage("GetThreadPreferredUILanguages 실패 :", GetLastError()));
		strcpy(buf, "GetThreadPreferredUILanguages 실패");
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "GetThreadPreferredUILanguages 성공", msg);

	return result;
}


/**
* BOOL SetThreadPreferredUILanguages(
  _In_      DWORD    dwFlags,
  _In_opt_  PCZZWSTR pwszLanguagesBuffer,
  _Out_opt_ PULONG   pulNumLanguages
);
* 현재 스레드에 대한 스레드 기본 UI 언어를 설정한다.
* @author : 손찬영  
*
* @param  dwFlags				설정할 언어에 대한 형식 및 필터링을 식별하는 플래그
* @param  pwszLanguagesBuffer	dwFlags에 의해 지정되는 형식에서, 순서 붙이고, null로 단락 지어진리스트를 포함한, double로 끝나는 복수 스트링의 버퍼의 포인터
* @param  pulNumLanguages		스레드 기본 UI 언어 목록에서 함수가 설정 한 언어 수를 가리키는 포인터
* @return						성공/실패 여부
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
		strcpy(buf, "SetThreadPreferredUILanguages 성공");
		
	}else{
		strcpy(buf, "SetThreadPreferredUILanguages 실패");
		
		result = FALSE;
	}
	strcpy(msg, buf);

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "SetThreadPreferredUILanguages 성공", msg);

	return result;
}


