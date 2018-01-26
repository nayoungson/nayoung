#include "TestFileAttributes.h"


/**
* BOOL WINAPI GetFileAttributesEx(
  _In_  LPCTSTR                lpFileName,
  _In_  GET_FILEEX_INFO_LEVELS fInfoLevelId,
  _Out_ LPVOID                 lpFileInformation
);
* ������ ���� �Ǵ� ���丮�� �Ӽ��� �˻��Ѵ�.
* @author : ������  
*
* @param  lpFileName		���� �Ǵ� ���丮�� �̸�
* @param  fInfoLevelId		�˻� �� �Ӽ� ���� Ŭ����
* @param  lpFileInformation �Ӽ� �������޴� ���ۿ� ���� ������
* @return					����/���� ����
*/
BOOL test_GetFileAttributesExW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	DWORD fileAttributes = 0;
	LPCWSTR fileName = L"������\\test_GetFileAttributesExW.txt";
	HANDLE hFile = NULL;
	WIN32_FILE_ATTRIBUTE_DATA fileAttributesData;
	FILETIME fileTimeLocal;
	SYSTEMTIME systemTimeLocal, systemTimeNow;
	char createTime[BUFSIZ], nowTime[BUFSIZ];
	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* FILE_ATTRIBUTE_TEMPORARY �Ӽ����� ������ �����Ѵ�. */
	hFile = CreateFileW(fileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if(hFile == INVALID_HANDLE_VALUE){
		sprintf(msg, GetErrorMessage("���� ���� ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "CreateFileA ����", "CreateFile ����", msg);

		return FALSE;
	}

	/* ���� ���� ����� �ð��� ���. */
	GetSystemTime(&systemTimeNow); 

	/* ������ �Ӽ��� �����´� */
	result = GetFileAttributesExW(fileName, GetFileExInfoStandard, (void *)&fileAttributesData);

	/* �Լ� ���� */
	if(result == FALSE){ 
		strcpy(msg, GetErrorMessage("GetFileAttributesExW ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "GetFileAttributesExW ����", "GetFileAttributesExW ����", msg);

		return FALSE;
	}

	/* �ֱ� ���� �ð�(���ϻ����ð�)�� �������Ͻð����� ��ȯ�Ѵ� */
	if(!FileTimeToLocalFileTime(&fileAttributesData.ftLastWriteTime, &fileTimeLocal)){
		strcpy(msg, GetErrorMessage("FileTimeToLocalFileTime ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ , __FUNCTION__, "FileTimeToLocalFileTime ����", "FileTimeToLocalFileTime ����", msg);

		return FALSE;

	}

	/*�������Ͻð��� �ý��۽ð����� �����Ѵ� */
	if(!FileTimeToSystemTime(&fileTimeLocal, &systemTimeLocal)){
		strcpy(msg, GetErrorMessage("FileTimeToSystemTime ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "FileTimeToSystemTime ����", "FileTimeToSystemTime ����", msg);

		return FALSE;

	}
	/* ���� ���� �ð��� �Ӽ����� ������ ���� ���� �ð��� �����ϸ� �������� �Ǵ��Ѵ�. */
	if((systemTimeLocal.wHour == systemTimeNow.wHour+9) && (systemTimeLocal.wMinute == systemTimeNow.wMinute)){
		sprintf(msg, "GetFileAttributesExW ���� : (�����ð� %d : %d)", systemTimeLocal.wHour, systemTimeLocal.wMinute);
		strcpy(buf, "GetFileAttributesExW ����");

	}else{
		sprintf(msg, "GetFileAttributesExW ���� : (�����ð� %d : %d), (���Ͻð� %d : %d)", systemTimeNow.wHour+9, systemTimeNow.wMinute, systemTimeLocal.wHour, systemTimeLocal.wMinute);
		strcpy(buf, "GetFileAttributesExW ����");

		result = FALSE;

	}
	wresult(__FILE__,__LINE__ , __FUNCTION__, buf, "GetFileAttributesExW ����", msg);

	CloseHandle(hFile);
	if(!DeleteFileW(fileName)){
		#ifdef OQADBGPRINT
		printf(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
		#endif
	}

	return result;
}


/**
* DWORD WINAPI GetFileAttributes(
  _In_ LPCTSTR lpFileName
);
* ������ ���� �Ǵ� ���丮�� ���� �ý��� �Ӽ��� �˻��Ѵ�.
* @author : ������  
*
* @param  lpFileName		���� �Ǵ� ���丮�� �̸�
* @return					�Լ��� �����ϸ� ��ȯ ���� ������ �����̳� ���丮�� Ư���� ����
*/
BOOL test_GetFileAttributesW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	DWORD fileAttributes = 0;
	LPCWSTR fileName = L"������\\test_GetFileAttributesW.txt";
	HANDLE hFile = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* FILE_ATTRIBUTE_TEMPORARY �Ӽ����� ������ ���� */
	hFile = CreateFile(fileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	
	if(hFile == INVALID_HANDLE_VALUE){ //���� ���� ����
		sprintf(msg, GetErrorMessage("CreateFile ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile ����", msg);

		return FALSE;
	}

	fileAttributes = GetFileAttributesW(fileName);

	/* �Լ��� ���� */
	if(fileAttributes == INVALID_FILE_ATTRIBUTES){
		strcpy(msg, GetErrorMessage("GetFileAttributesW ���� : ", GetLastError()));
		result = FALSE;	
	
	}else{
		/* �Լ��� �����ϰ� �Ӽ��� FILE_ATTRIBUTE_TEMPORARY�̸� �������� �Ǵ� */
		if(fileAttributes & FILE_ATTRIBUTE_TEMPORARY){
			strcpy(msg, "GetFileAttributesW ����");
			strcpy(buf, msg);
		
		}else{
			sprintf(msg, "GetFileAttributesW ���� : fileAttributes = %d(������)", fileAttributes);
			strcpy(buf, "GetFileAttributesW ����");
			result = FALSE;	
		}
	}
	wresult(__FILE__,__LINE__ , __FUNCTION__, msg, "GetFileAttributesW ����", msg);


	CloseHandle(hFile);

	/* ���� �� ������ �����Ѵ� */
	if(!DeleteFileW(fileName)){
		#ifdef OQADBGPRINT
		printf(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
		#endif
	}

	return result;
}



/**
* BOOL WINAPI GetFileAttributesEx(
  _In_  LPCTSTR                lpFileName,
  _In_  GET_FILEEX_INFO_LEVELS fInfoLevelId,
  _Out_ LPVOID                 lpFileInformation
);
* ������ ���� �Ǵ� ���丮�� �Ӽ��� �˻��Ѵ�.
* @author : ������  
*
* @param  lpFileName		���� �Ǵ� ���丮�� �̸�
* @param  fInfoLevelId		�˻� �� �Ӽ� ���� Ŭ����
* @param  lpFileInformation �Ӽ� �������޴� ���ۿ� ���� ������
* @return					����/���� ����
*/
BOOL test_GetFileAttributesExA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	DWORD fileAttributes = 0;
	LPCSTR fileName = "������\\test_GetFileAttributesExA.txt";
	HANDLE hFile = NULL;
	WIN32_FILE_ATTRIBUTE_DATA fileAttributesData;
	FILETIME fileTimeLocal;
	SYSTEMTIME systemTimeLocal, systemTimeNow;
	char createTime[BUFSIZ], nowTime[BUFSIZ];
	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* FILE_ATTRIBUTE_TEMPORARY �Ӽ����� ������ �����Ѵ�. */
	hFile = CreateFileA(fileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if(hFile == INVALID_HANDLE_VALUE){
		sprintf(msg, GetErrorMessage("���� ���� ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "CreateFileA ����", "CreateFile ����", msg);

		return FALSE;
	}

	/* ���� ���� ����� �ð��� ���. */
	GetSystemTime(&systemTimeNow); 

	/* ������ �Ӽ��� �����´� */
	result = GetFileAttributesExA(fileName, GetFileExInfoStandard, (void *)&fileAttributesData);

	/* �Լ� ���� */
	if(result == FALSE){ 
		strcpy(msg, GetErrorMessage("GetFileAttributesExA ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "GetFileAttributesExA ����", "GetFileAttributesExA ����", msg);

		return FALSE;
	}

	/* �ֱ� ���� �ð�(���ϻ����ð�)�� �������Ͻð����� ��ȯ�Ѵ� */
	if(!FileTimeToLocalFileTime(&fileAttributesData.ftLastWriteTime, &fileTimeLocal)){
		strcpy(msg, GetErrorMessage("FileTimeToLocalFileTime ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ , __FUNCTION__, "FileTimeToLocalFileTime ����", "FileTimeToLocalFileTime ����", msg);

		return FALSE;

	}

	/*�������Ͻð��� �ý��۽ð����� �����Ѵ� */
	if(!FileTimeToSystemTime(&fileTimeLocal, &systemTimeLocal)){
		strcpy(msg, GetErrorMessage("FileTimeToSystemTime ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "FileTimeToSystemTime ����", "FileTimeToSystemTime ����", msg);

		return FALSE;

	}
	/* ���� ���� �ð��� �Ӽ����� ������ ���� ���� �ð��� �����ϸ� �������� �Ǵ��Ѵ�. */
	if((systemTimeLocal.wHour == systemTimeNow.wHour+9) && (systemTimeLocal.wMinute == systemTimeNow.wMinute)){
		sprintf(msg, "GetFileAttributesExA ���� : (�����ð� %d : %d)", systemTimeLocal.wHour, systemTimeLocal.wMinute);
		strcpy(buf, "GetFileAttributesExA ����");

	}else{
		sprintf(msg, "GetFileAttributesExA ���� : (�����ð� %d : %d), (���Ͻð� %d : %d)", systemTimeNow.wHour+9, systemTimeNow.wMinute, systemTimeLocal.wHour, systemTimeLocal.wMinute);
		strcpy(buf, "GetFileAttributesExA ����");

		result = FALSE;

	}
	wresult(__FILE__,__LINE__ , __FUNCTION__, buf, "GetFileAttributesExA ����", msg);

	CloseHandle(hFile);
	if(!DeleteFileA(fileName)){
		#ifdef OQADBGPRINT
		printf(GetErrorMessage("DeleteFileA ���� : ", GetLastError()));
		#endif
	}

	return result;
}




/**
* BOOL WINAPI GetFileAttributesTransacted(
  _In_  LPCTSTR                lpFileName,
  _In_  GET_FILEEX_INFO_LEVELS fInfoLevelId,
  _Out_ LPVOID                 lpFileInformation,
  _In_  HANDLE                 hTransaction
);
* ������ ���� �Ǵ� ���丮�� ���� �ý��� �Ӽ��� Ʈ����� �������� �˻��Ѵ�. �������� ����.
* @author : ������  
*
* @param  lpFileName		���� �Ǵ� ���丮�� �̸�
* @param  fInfoLevelId		�˻� �� �Ӽ� ������ ����.
* @param  lpFileInformation �Ӽ� �������޴� ���ۿ� ���� ������
* @param  hTransaction		Ʈ����� �ڵ�
* @return					����/���� ����
*/
BOOL test_GetFileAttributesTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	LPCTSTR lpFileName = L"������\\test_GetFileAttributesTransactedW.txt";
	DWORD   dwFileAttributes = FILE_ATTRIBUTE_HIDDEN;
	HANDLE  hTransaction, hFile;
	WIN32_FILE_ATTRIBUTE_DATA FileInformation;

	FILETIME fileTimeLocal;
	SYSTEMTIME systemTimeLocal, systemTimeNow;
	char createTime[BUFSIZ], nowTime[BUFSIZ];

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	hFile = CreateFileW(lpFileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	GetSystemTime(&systemTimeNow); //���� ���� ��� �ð��� ������
	
	if(hFile == INVALID_HANDLE_VALUE){ //���� ���� ����
		sprintf(msg, GetErrorMessage("CreateFileW ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile ����", msg);

		return FALSE;
	}
	CloseHandle(hFile);

	result = GetFileAttributesTransactedW(lpFileName, GetFileExInfoStandard, &FileInformation, hTransaction);

	if(!FileTimeToLocalFileTime(&FileInformation.ftLastWriteTime, &fileTimeLocal)){ //����Ÿ������ ���� �����ϸ�
		strcpy(msg, GetErrorMessage("FileTimeToLocalFileTime ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "FileTimeToLocalFileTime ����", "FileTimeToLocalFileTime ����", msg);

		return FALSE;

	}

	if(!FileTimeToSystemTime(&fileTimeLocal, &systemTimeLocal)){ //�ý��۽ð����� ���� ����
		strcpy(msg, GetErrorMessage("FileTimeToSystemTime ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "FileTimeToSystemTime ����", "FileTimeToSystemTime ����", msg);

		return FALSE;

	}

	sprintf(createTime, "�����ð� %d : %d\n", systemTimeLocal.wHour, systemTimeLocal.wMinute); //���� ���� �ð�
	sprintf(nowTime, "����ð� %d : %d", systemTimeNow.wHour+9, systemTimeNow.wMinute); //������� �ð�(UTC�ð�) + 9


	if(result){
		sprintf(msg, "GetFileAttributesTransactedW ���� : ");
		strcat(msg, createTime);
		strcat(msg, nowTime);
		strcpy(buf, "GetFileAttributesTransactedW ����");	

	}else{
		strcpy(msg, GetErrorMessage("GetFileAttributesTransactedW ���� : ", GetLastError()));
		strcpy(buf, "GetFileAttributesTransactedW ����");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetFileAttributesTransactedW ����", msg);

	CloseHandle(hTransaction);

	if(!DeleteFile(lpFileName)){
		#ifdef OQADBGPRINT
		printf("DeleteFile ����\n");
		#endif
	}

	return result;
	
}


/**
* BOOL WINAPI GetFileAttributesTransacted(
  _In_  LPCTSTR                lpFileName,
  _In_  GET_FILEEX_INFO_LEVELS fInfoLevelId,
  _Out_ LPVOID                 lpFileInformation,
  _In_  HANDLE                 hTransaction
);
* ������ ���� �Ǵ� ���丮�� ���� �ý��� �Ӽ��� Ʈ����� �������� �˻��Ѵ�. �������� ����.
* @author : ������  
*
* @param  lpFileName		���� �Ǵ� ���丮�� �̸�
* @param  fInfoLevelId		�˻� �� �Ӽ� ������ ����.
* @param  lpFileInformation �Ӽ� �������޴� ���ۿ� ���� ������
* @param  hTransaction		Ʈ����� �ڵ�
* @return					����/���� ����
*/
BOOL test_GetFileAttributesTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	LPCSTR lpFileName = "������\\test_GetFileAttributesTransactedA.txt";
	DWORD   dwFileAttributes = FILE_ATTRIBUTE_HIDDEN;
	HANDLE  hTransaction, hFile;
	WIN32_FILE_ATTRIBUTE_DATA FileInformation;

	FILETIME fileTimeLocal;
	SYSTEMTIME systemTimeLocal, systemTimeNow;
	char createTime[BUFSIZ], nowTime[BUFSIZ];

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	hFile = CreateFileA(lpFileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	GetSystemTime(&systemTimeNow); //���� ���� ��� �ð��� ������
	
	if(hFile == INVALID_HANDLE_VALUE){ //���� ���� ����
		sprintf(msg, GetErrorMessage("CreateFileW ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile ����", msg);

		return FALSE;
	}
	CloseHandle(hFile);

	result = GetFileAttributesTransactedA(lpFileName, GetFileExInfoStandard, &FileInformation, hTransaction);

	if(!FileTimeToLocalFileTime(&FileInformation.ftLastWriteTime, &fileTimeLocal)){ //����Ÿ������ ���� �����ϸ�
		strcpy(msg, GetErrorMessage("FileTimeToLocalFileTime ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "FileTimeToLocalFileTime ����", "FileTimeToLocalFileTime ����", msg);

		return FALSE;

	}

	if(!FileTimeToSystemTime(&fileTimeLocal, &systemTimeLocal)){ //�ý��۽ð����� ���� ����
		strcpy(msg, GetErrorMessage("FileTimeToSystemTime ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "FileTimeToSystemTime ����", "FileTimeToSystemTime ����", msg);

		return FALSE;

	}

	sprintf(createTime, "�����ð� %d : %d\n", systemTimeLocal.wHour, systemTimeLocal.wMinute); //���� ���� �ð�
	sprintf(nowTime, "����ð� %d : %d", systemTimeNow.wHour+9, systemTimeNow.wMinute); //������� �ð�(UTC�ð�) + 9


	if(result){
		sprintf(msg, "GetFileAttributesTransactedA ���� : ");
		strcat(msg, createTime);
		strcat(msg, nowTime);
		strcpy(buf, "GetFileAttributesTransactedA ����");	

	}else{
		strcpy(msg, GetErrorMessage("GetFileAttributesTransactedA ���� : ", GetLastError()));
		strcpy(buf, "GetFileAttributesTransactedA ����");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetFileAttributesTransactedA ����", msg);

	CloseHandle(hTransaction);

	if(!DeleteFileA(lpFileName)){
		#ifdef OQADBGPRINT
		printf("DeleteFile ����\n");
		#endif
	}

	return result;
}


/**
* BOOL WINAPI SetFileAttributesTransacted(
  _In_ LPCTSTR lpFileName,
  _In_ DWORD   dwFileAttributes,
  _In_ HANDLE  hTransaction
);
* ���� �Ǵ� ���丮�� �Ӽ��� Ʈ����� �������� �����Ѵ�. �������� ����.
* @author : ������  
*
* @param  lpFileName		�Ӽ��� ������ ������ �̸�
* @param  dwFileAttributes	���Ͽ� ���� ������ ���� Ư��
* @param  hTransaction		Ʈ����� �ڵ�
* @return					����/���� ����
*/
BOOL test_SetFileAttributesTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	LPCTSTR lpFileName = L"������\\test_SetFileAttributesTransactedW.txt";
	DWORD   dwFileAttributes = FILE_ATTRIBUTE_HIDDEN;
	HANDLE  hTransaction, hFile;

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	hFile = CreateFileW(lpFileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	
	if(hFile == INVALID_HANDLE_VALUE){ //���� ���� ����
		sprintf(msg, GetErrorMessage("CreateFileW ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile ����", msg);

		return FALSE;
	}
	CloseHandle(hFile);

	result = SetFileAttributesTransactedW(lpFileName, dwFileAttributes, hTransaction);

	if(result){
		strcpy(msg, "SetFileAttributesTransactedW ����");
		strcpy(buf, "SetFileAttributesTransactedW ����");	

	}else{
		strcpy(msg, GetErrorMessage("SetFileAttributesTransactedW ���� : ", GetLastError()));
		strcpy(buf, "SetFileAttributesTransactedW ����");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetFileAttributesTransactedW ����", msg);

	CloseHandle(hTransaction);

	if(!DeleteFile(lpFileName)){
		#ifdef OQADBGPRINT
		printf("DeleteFile ����\n");
		#endif
	}

	return result;
}


/**
* BOOL WINAPI SetFileAttributesTransacted(
  _In_ LPCTSTR lpFileName,
  _In_ DWORD   dwFileAttributes,
  _In_ HANDLE  hTransaction
);
* ���� �Ǵ� ���丮�� �Ӽ��� Ʈ����� �������� �����Ѵ�. �������� ����.
* @author : ������  
*
* @param  lpFileName		�Ӽ��� ������ ������ �̸�
* @param  dwFileAttributes	���Ͽ� ���� ������ ���� Ư��
* @param  hTransaction		Ʈ����� �ڵ�
* @return					����/���� ����
*/
BOOL test_SetFileAttributesTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	LPCSTR lpFileName = "������\\test_SetFileAttributesTransactedA.txt";
	DWORD   dwFileAttributes = FILE_ATTRIBUTE_HIDDEN;
	HANDLE  hTransaction, hFile;

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	hFile = CreateFileA(lpFileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	
	if(hFile == INVALID_HANDLE_VALUE){ //���� ���� ����
		sprintf(msg, GetErrorMessage("CreateFileW ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile ����", msg);

		return FALSE;
	}
	CloseHandle(hFile);

	result = SetFileAttributesTransactedA(lpFileName, dwFileAttributes, hTransaction);

	if(result){
		strcpy(msg, "SetFileAttributesTransactedA ����");
		strcpy(buf, "SetFileAttributesTransactedA ����");	

	}else{
		strcpy(msg, GetErrorMessage("SetFileAttributesTransactedA ���� : ", GetLastError()));
		strcpy(buf, "SetFileAttributesTransactedA ����");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetFileAttributesTransactedA ����", msg);

	CloseHandle(hTransaction);

	if(!DeleteFileA(lpFileName)){
		#ifdef OQADBGPRINT
		printf("DeleteFile ����\n");
		#endif
	}

	return result;
}

