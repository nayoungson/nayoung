#include "TestWer.h"


/**
* HRESULT WINAPI WerUnregisterFile(
  _In_ PCWSTR pwzFilePath
);
* ���� ���μ����� ���� ���� �� ������ �߰� �� ���� ��Ͽ��� ������ �����Ѵ�.
* @author : ������  
*
* @param  pwzFilePath	������ ��ü ���
* @return				������ S_OK, ���� �� WER_E_INVALID_STATE �Ǵ� WER_E_NOT_FOUND
*/
BOOL test_WerUnregisterFile()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	HRESULT ret = 0;

	LPCWSTR pwzFilePath = L"������\\test_WerUnregisterFile.txt";
	WER_REGISTER_FILE_TYPE regFileType = WerRegFileTypeUserDocument;
	DWORD dwFlags = WER_FILE_ANONYMOUS_DATA;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(S_OK != (WerRegisterFile(pwzFilePath, regFileType, dwFlags))){
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "WerRegisterFile ����", "WerRegisterFile ����", "WerRegisterFile ����");

		return FALSE;
	}

	ret = WerUnregisterFile(pwzFilePath);

	if(S_OK == ret){
		sprintf(msg, "WerUnregisterFile ����");
		strcpy(buf, "WerUnregisterFile ����");

	}else if(WER_E_INVALID_STATE == ret){
		strcpy(msg, "WerUnregisterFile ���� : WER_E_INVALID_STATE");
		strcpy(buf, "WerUnregisterFile ����");

		result = FALSE;

	}else if(WER_E_NOT_FOUND == ret){
		strcpy(msg, "WerUnregisterFile ���� : WER_E_NOT_FOUND");
		strcpy(buf, "WerUnregisterFile ����");

		result = FALSE;

	}else{
		sprintf(msg, "WerUnregisterFile ���� : �� �� ���� ����\nret=%ld", ret);
		strcpy(buf, "WerUnregisterFile ����");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "WerUnregisterFile ����", msg);

	return result;
}

/**
* HRESULT WINAPI WerRegisterFile(
  _In_ PCWSTR                 pwzFile,
  _In_ WER_REGISTER_FILE_TYPE regFileType,
  _In_ DWORD                  dwFlags
);
* WER���� ���� ������ ���� �� ���� �� ������ ����Ѵ�.
* @author : ������  
*
* @param  pwzFilePath	������ ��ü ���
* @param  regFileType	���� ����
* @param  dwFlags		WER_FILE_ANONYMOUS_DATA �Ǵ� WER_FILE_DELETE_WHEN_DONE
* @return				������ S_OK, ���� �� WER_E_INVALID_STATE �Ǵ� HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER)
*/
BOOL test_WerRegisterFile()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	HRESULT ret = 0;

	LPCWSTR pwzFilePath = L"������\\test_WerRegisterFile.txt";
	WER_REGISTER_FILE_TYPE regFileType = WerRegFileTypeUserDocument;
	DWORD dwFlags = WER_FILE_ANONYMOUS_DATA;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	ret = WerRegisterFile(pwzFilePath, regFileType, dwFlags);

	if(S_OK == ret){
		sprintf(msg, "WerRegisterFile ����");
		strcpy(buf, "WerRegisterFile ����");

	}else if(WER_E_INVALID_STATE == ret){
		strcpy(msg, "WerRegisterFile ���� : WER_E_INVALID_STATE");
		strcpy(buf, "WerRegisterFile ����");

		result = FALSE;

	}else if(HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER) == ret){
		strcpy(msg, "WerRegisterFile ���� : ERROR_INSUFFICIENT_BUFFER");
		strcpy(buf, "WerRegisterFile ����");

		result = FALSE;

	}else{
		sprintf(msg, "WerRegisterFile ���� : �� �� ���� ����\nret=%ld", ret);
		strcpy(buf, "WerRegisterFile ����");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "WerRegisterFile ����", msg);

	return result;
}