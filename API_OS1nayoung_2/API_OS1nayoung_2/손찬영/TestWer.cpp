#include "TestWer.h"


/**
* HRESULT WINAPI WerUnregisterFile(
  _In_ PCWSTR pwzFilePath
);
* 현재 프로세스에 대해 생성 된 보고서에 추가 할 파일 목록에서 파일을 제거한다.
* @author : 손찬영  
*
* @param  pwzFilePath	파일의 전체 경로
* @return				성공시 S_OK, 실패 시 WER_E_INVALID_STATE 또는 WER_E_NOT_FOUND
*/
BOOL test_WerUnregisterFile()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	HRESULT ret = 0;

	LPCWSTR pwzFilePath = L"손찬영\\test_WerUnregisterFile.txt";
	WER_REGISTER_FILE_TYPE regFileType = WerRegFileTypeUserDocument;
	DWORD dwFlags = WER_FILE_ANONYMOUS_DATA;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(S_OK != (WerRegisterFile(pwzFilePath, regFileType, dwFlags))){
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "WerRegisterFile 실패", "WerRegisterFile 성공", "WerRegisterFile 실패");

		return FALSE;
	}

	ret = WerUnregisterFile(pwzFilePath);

	if(S_OK == ret){
		sprintf(msg, "WerUnregisterFile 성공");
		strcpy(buf, "WerUnregisterFile 성공");

	}else if(WER_E_INVALID_STATE == ret){
		strcpy(msg, "WerUnregisterFile 실패 : WER_E_INVALID_STATE");
		strcpy(buf, "WerUnregisterFile 실패");

		result = FALSE;

	}else if(WER_E_NOT_FOUND == ret){
		strcpy(msg, "WerUnregisterFile 실패 : WER_E_NOT_FOUND");
		strcpy(buf, "WerUnregisterFile 실패");

		result = FALSE;

	}else{
		sprintf(msg, "WerUnregisterFile 실패 : 알 수 없는 에러\nret=%ld", ret);
		strcpy(buf, "WerUnregisterFile 실패");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "WerUnregisterFile 성공", msg);

	return result;
}

/**
* HRESULT WINAPI WerRegisterFile(
  _In_ PCWSTR                 pwzFile,
  _In_ WER_REGISTER_FILE_TYPE regFileType,
  _In_ DWORD                  dwFlags
);
* WER에서 오류 보고서를 만들 때 수집 할 파일을 등록한다.
* @author : 손찬영  
*
* @param  pwzFilePath	파일의 전체 경로
* @param  regFileType	파일 유형
* @param  dwFlags		WER_FILE_ANONYMOUS_DATA 또는 WER_FILE_DELETE_WHEN_DONE
* @return				성공시 S_OK, 실패 시 WER_E_INVALID_STATE 또는 HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER)
*/
BOOL test_WerRegisterFile()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	HRESULT ret = 0;

	LPCWSTR pwzFilePath = L"손찬영\\test_WerRegisterFile.txt";
	WER_REGISTER_FILE_TYPE regFileType = WerRegFileTypeUserDocument;
	DWORD dwFlags = WER_FILE_ANONYMOUS_DATA;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	ret = WerRegisterFile(pwzFilePath, regFileType, dwFlags);

	if(S_OK == ret){
		sprintf(msg, "WerRegisterFile 성공");
		strcpy(buf, "WerRegisterFile 성공");

	}else if(WER_E_INVALID_STATE == ret){
		strcpy(msg, "WerRegisterFile 실패 : WER_E_INVALID_STATE");
		strcpy(buf, "WerRegisterFile 실패");

		result = FALSE;

	}else if(HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER) == ret){
		strcpy(msg, "WerRegisterFile 실패 : ERROR_INSUFFICIENT_BUFFER");
		strcpy(buf, "WerRegisterFile 실패");

		result = FALSE;

	}else{
		sprintf(msg, "WerRegisterFile 실패 : 알 수 없는 에러\nret=%ld", ret);
		strcpy(buf, "WerRegisterFile 실패");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "WerRegisterFile 성공", msg);

	return result;
}