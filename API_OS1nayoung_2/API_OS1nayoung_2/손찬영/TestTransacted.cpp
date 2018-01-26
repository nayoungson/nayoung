#include "TestTransacted.h"


/**
* DWORD WINAPI GetCompressedFileSizeTransacted(
  _In_      LPCTSTR lpFileName,
  _Out_opt_ LPDWORD lpFileSizeHigh,
  _In_      HANDLE  hTransaction
);
* Ʈ����� ó���� ������ ������ �����ϴ� �� ��� �� ��ũ ���� ������ ���� ����Ʈ ���� �˻��Ѵ�. �������� ����.
* @author : ������  
*
* @param  lpFileName		������ �̸�
* @param  lpFileSizeHigh	���� �� ���� ũ���� ���� DWORD�� �޴� ������ ���� ������
* @param  hTransaction		Ʈ����� �ڵ�
* @return					�Լ��� �����ϸ� ��ȯ ���� ������ ������ �����ϴ� �� ��� �� ���� ��ũ ����� ����Ʈ ���� ���� DWORD
*/
BOOL test_GetCompressedFileSizeTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCTSTR lpFileName = L"������\\test_GetCompressedFileSizeTransactedW.txt";
	HANDLE  hTransaction, hFile;
	DWORD	ret = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hFile = MyCreateFile(lpFileName))){

		return FALSE;
	}
	CloseHandle(hFile);

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	ret = GetCompressedFileSizeTransactedW(lpFileName, NULL, hTransaction);

	if(INVALID_FILE_SIZE != ret){
		sprintf(msg, "GetCompressedFileSizeTransactedW ���� : ret = %lu", ret);
		strcpy(buf, "GetCompressedFileSizeTransactedW ����");
		
	}else{
		strcpy(msg, GetErrorMessage("GetCompressedFileSizeTransactedW ���� : ", GetLastError()));
		strcpy(buf, "GetCompressedFileSizeTransactedW ����");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetCompressedFileSizeTransactedW ����", msg);

	CloseHandle(hTransaction);
	DeleteFile(lpFileName);

	return result;
}

/**
* DWORD WINAPI GetCompressedFileSizeTransacted(
  _In_      LPCTSTR lpFileName,
  _Out_opt_ LPDWORD lpFileSizeHigh,
  _In_      HANDLE  hTransaction
);
* Ʈ����� ó���� ������ ������ �����ϴ� �� ��� �� ��ũ ���� ������ ���� ����Ʈ ���� �˻��Ѵ�. �������� ����.
* @author : ������  
*
* @param  lpFileName		������ �̸�
* @param  lpFileSizeHigh	���� �� ���� ũ���� ���� DWORD�� �޴� ������ ���� ������
* @param  hTransaction		Ʈ����� �ڵ�
* @return					�Լ��� �����ϸ� ��ȯ ���� ������ ������ �����ϴ� �� ��� �� ���� ��ũ ����� ����Ʈ ���� ���� DWORD
*/
BOOL test_GetCompressedFileSizeTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCSTR lpFileName = "������\\test_GetCompressedFileSizeTransactedA.txt";
	HANDLE  hTransaction, hFile;
	DWORD	ret = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hFile = MyCreateFileA(lpFileName))){

		return FALSE;
	}
	CloseHandle(hFile);

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	ret = GetCompressedFileSizeTransactedA(lpFileName, NULL, hTransaction);

	if(INVALID_FILE_SIZE != ret){
		sprintf(msg, "GetCompressedFileSizeTransactedW ���� : ret = %lu", ret);
		strcpy(buf, "GetCompressedFileSizeTransactedW ����");
		
	}else{
		strcpy(msg, GetErrorMessage("GetCompressedFileSizeTransactedW ���� : ", GetLastError()));
		strcpy(buf, "GetCompressedFileSizeTransactedW ����");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetCompressedFileSizeTransactedW ����", msg);

	CloseHandle(hTransaction);
	DeleteFileA(lpFileName);

	return result;
}

/**
* HANDLE WINAPI FindFirstStreamTransactedW(
  _In_       LPCWSTR            lpFileName,
  _In_       STREAM_INFO_LEVELS InfoLevel,
  _Out_      LPVOID             lpFindStreamData,
  _Reserved_ DWORD              dwFlags,
  _In_       HANDLE             hTransaction
);
* ������ ���� �Ǵ� ���͸��� ù ��° ��Ʈ���� Ʈ����� �������� �����Ѵ�. �������� ����.
* @author : ������  
*
* @param  lpFileName		������ ���� �̸�.
* @param  InfoLevel			��ȯ �� �������� ���� ����
* @param  lpFindStreamData	���� �����͸� �����ϴ� ���ۿ� ���� ������
* @param  dwFlags			����
* @param  hTransaction		Ʈ����� �ڵ�
* @return					�Լ��� �����ϸ� ��ȯ ���� ���Ŀ� FindNextStreamW �Լ��� ȣ�� �� �� ����� ���ִ� �˻� �ڵ�, �����ϸ� INVALID_HANDLE_VALUE
*/
BOOL test_FindFirstStreamTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hFile;
	LPCWSTR lpFileName = L"������\\test_FindFirstStreamTransactedW.txt";
	STREAM_INFO_LEVELS InfoLevel = FindStreamInfoStandard;
	WIN32_FIND_STREAM_DATA lpFindStreamData;
	HANDLE	hTransaction;
	HANDLE	handle = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hFile = MyCreateFile(lpFileName))){

		return FALSE;
	}
	CloseHandle(hFile);

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	handle = FindFirstStreamTransactedW(lpFileName, InfoLevel, (LPVOID)&lpFindStreamData, 0, hTransaction);

	if(INVALID_HANDLE_VALUE != handle){
		sprintf(msg, "FindFirstStreamTransactedW ���� : handle = %d", handle);
		strcpy(buf, "FindFirstStreamTransactedW ����");
		
	}else{
		strcpy(msg, GetErrorMessage("FindFirstStreamTransactedW ���� : ", GetLastError()));
		strcpy(buf, "FindFirstStreamTransactedW ����");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "FindFirstStreamTransactedW ����", msg);

	CloseHandle(hTransaction);
	CloseHandle(handle);
	DeleteFile(lpFileName);

	return result;
}

/**
* HANDLE WINAPI FindFirstFileTransacted(
  _In_       LPCTSTR            lpFileName,
  _In_       FINDEX_INFO_LEVELS fInfoLevelId,
  _Out_      LPVOID             lpFindFileData,
  _In_       FINDEX_SEARCH_OPS  fSearchOp,
  _Reserved_ LPVOID             lpSearchFilter,
  _In_       DWORD              dwAdditionalFlags,
  _In_       HANDLE             hTransaction
);
* Ư�� �̸��� ��ġ�ϴ� �̸��� ���� ���� �Ǵ� ���� ���丮�� �˻��� �۾����� �˻��ȴ�.
* @author : ������  
*
* @param  lpFileName		���丮 �Ǵ� ��� �� ���� �̸�
* @param  fInfoLevelId		��ȯ �� �������� ���� ����
* @param  lpFindFileData	�߰� �� �����̳� ���� ���丮�� ���� ������ �޴� WIN32_FIND_DATA ����ü�� ���� ������
* @param  fSearchOp			FINDEX_SEARCH_OPS ���� �� �� �� �ϳ�
* @param  lpSearchFilter	������ fSearchOp�� ����ȭ �� �˻� ������ �ʿ��� ��� �˻� ���ǿ� ���� ������
* @param  dwAdditionalFlags	�˻��� �����ϴ� �߰� �÷���
* @param  hTransaction		Ʈ����� �ڵ�
* @return					�Լ��� �����ϸ� ��ȯ ���� FindNextFile �Ǵ� FindClose �� ���� �ļ� ȣ�⿡�� ���Ǵ� �˻� �ڵ�
*/
BOOL test_FindFirstFileTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hFile;
	LPCWSTR lpFileName = L"������\\test_FindFirstFileTransactedW.txt";
	FINDEX_INFO_LEVELS fInfoLevelId = FindExInfoStandard;
	WIN32_FIND_DATA    lpFindFileData;
	FINDEX_SEARCH_OPS  fSearchOp = FindExSearchNameMatch;
	LPVOID             lpSearchFilter = NULL;
	DWORD              dwAdditionalFlags = FIND_FIRST_EX_CASE_SENSITIVE;
	HANDLE	hTransaction;
	HANDLE	handle = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hFile = MyCreateFile(lpFileName))){

		return FALSE;
	}
	CloseHandle(hFile);

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	handle = FindFirstFileTransactedW(lpFileName, fInfoLevelId, (LPVOID)&lpFindFileData, fSearchOp, lpSearchFilter, dwAdditionalFlags, hTransaction);

	if(INVALID_HANDLE_VALUE != handle){
		sprintf(msg, "FindFirstFileTransactedW ���� : handle = %d", handle);
		strcpy(buf, "FindFirstFileTransactedW ����");
		
	}else{
		strcpy(msg, GetErrorMessage("FindFirstFileTransactedW ���� : ", GetLastError()));
		strcpy(buf, "FindFirstFileTransactedW ����");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "FindFirstFileTransactedW ����", msg);

	CloseHandle(hTransaction);
	CloseHandle(handle);
	DeleteFile(lpFileName);

	return result;
}


/**
* HANDLE WINAPI FindFirstFileTransacted(
  _In_       LPCTSTR            lpFileName,
  _In_       FINDEX_INFO_LEVELS fInfoLevelId,
  _Out_      LPVOID             lpFindFileData,
  _In_       FINDEX_SEARCH_OPS  fSearchOp,
  _Reserved_ LPVOID             lpSearchFilter,
  _In_       DWORD              dwAdditionalFlags,
  _In_       HANDLE             hTransaction
);
* Ư�� �̸��� ��ġ�ϴ� �̸��� ���� ���� �Ǵ� ���� ���丮�� �˻��� �۾����� �˻��ȴ�.
* @author : ������  
*
* @param  lpFileName		���丮 �Ǵ� ��� �� ���� �̸�
* @param  fInfoLevelId		��ȯ �� �������� ���� ����
* @param  lpFindFileData	�߰� �� �����̳� ���� ���丮�� ���� ������ �޴� WIN32_FIND_DATA ����ü�� ���� ������
* @param  fSearchOp			FINDEX_SEARCH_OPS ���� �� �� �� �ϳ�
* @param  lpSearchFilter	������ fSearchOp�� ����ȭ �� �˻� ������ �ʿ��� ��� �˻� ���ǿ� ���� ������
* @param  dwAdditionalFlags	�˻��� �����ϴ� �߰� �÷���
* @param  hTransaction		Ʈ����� �ڵ�
* @return					�Լ��� �����ϸ� ��ȯ ���� FindNextFile �Ǵ� FindClose �� ���� �ļ� ȣ�⿡�� ���Ǵ� �˻� �ڵ�
*/
BOOL test_FindFirstFileTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hFile;
	LPCSTR lpFileName = "������\\test_FindFirstFileTransactedA.txt";
	FINDEX_INFO_LEVELS fInfoLevelId = FindExInfoStandard;
	WIN32_FIND_DATA    lpFindFileData;
	FINDEX_SEARCH_OPS  fSearchOp = FindExSearchNameMatch;
	LPVOID             lpSearchFilter = NULL;
	DWORD              dwAdditionalFlags = FIND_FIRST_EX_CASE_SENSITIVE;
	HANDLE	hTransaction;
	HANDLE	handle = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hFile = MyCreateFileA(lpFileName))){

		return FALSE;
	}
	CloseHandle(hFile);

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	handle = FindFirstFileTransactedA(lpFileName, fInfoLevelId, (LPVOID)&lpFindFileData, fSearchOp, lpSearchFilter, dwAdditionalFlags, hTransaction);

	if(INVALID_HANDLE_VALUE != handle){
		sprintf(msg, "FindFirstFileTransactedA ���� : handle = %d", handle);
		strcpy(buf, "FindFirstFileTransactedA ����");
		
	}else{
		strcpy(msg, GetErrorMessage("FindFirstFileTransactedA ���� : ", GetLastError()));
		strcpy(buf, "FindFirstFileTransactedA ����");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "FindFirstFileTransactedA ����", msg);

	CloseHandle(hTransaction);
	CloseHandle(handle);
	DeleteFileA(lpFileName);

	return result;
}


/**
* HANDLE WINAPI FindFirstFileNameTransactedW(
  _In_     LPCWSTR lpFileName,
  _In_     DWORD   dwFlags,
  _Inout_  LPDWORD StringLength,
  _Inout_  PWCHAR  LinkName,
  _In_opt_ HANDLE  hTransaction
);
* ������ ���Ͽ� ���� ��� �ϵ� ��ũ�� ���Ÿ� Ʈ����� �������� �ۼ��Ѵ�. ������� ����.
* @author : ������  
*
* @param  lpFileName	������ �̸�
* @param  dwFlags		����
* @param  StringLength	LinkName �Ű� ������ ����Ű�� ������ ũ��(���� ��)
* @param  LinkName		lpFileName�� ���� �߰� �� ù ��° ��ũ �̸��� ������ ���ۿ� ���� ������
* @param  hTransaction	Ʈ����� �ڵ�
* @return				�Լ��� �����ϸ� ��ȯ ���� FindNextFile �Ǵ� FindClose �� ���� �ļ� ȣ�⿡�� ���Ǵ� �˻� �ڵ�
*/
BOOL test_FindFirstFileNameTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hFile;
	LPCWSTR lpFileName = L"������\\test_FindFirstFileNameTransactedW.txt";
	DWORD   dwFlags = 0;
	DWORD StringLength = BUFSIZ;
	WCHAR  LinkName[BUFSIZ];
	HANDLE	hTransaction;
	HANDLE	handle = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hFile = MyCreateFile(lpFileName))){

		return FALSE;
	}
	CloseHandle(hFile);

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	handle = FindFirstFileNameTransactedW(lpFileName, dwFlags, &StringLength, LinkName, hTransaction);

	if(INVALID_HANDLE_VALUE != handle){
		sprintf(msg, "FindFirstFileTransactedW ���� : handle = %d\nLinkName = %S", handle, LinkName);
		strcpy(buf, "FindFirstFileTransactedW ����");
		
	}else{
		strcpy(msg, GetErrorMessage("FindFirstFileTransactedW ���� : ", GetLastError()));
		strcpy(buf, "FindFirstFileTransactedW ����");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "FindFirstFileTransactedW ����", msg);

	CloseHandle(hTransaction);
	CloseHandle(handle);
	DeleteFile(lpFileName);

	return result;
}