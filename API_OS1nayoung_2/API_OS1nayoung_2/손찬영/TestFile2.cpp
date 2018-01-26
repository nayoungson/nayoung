#include "TestFile2.h"

/**
* BOOL MoveFileTransactedW(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine, 
LPVOID lpData, DWORD dwFlags, HANDLE hTransaction)
* �ڽ��� �����Ͽ� ���� �����̳� ���丮�� Ʈ����� �������� �̵��Ѵ�. ������� ����.
* @author : ������  
*
* @param  lpExistingFileName ���� ��ǻ�Ϳ��ִ� ���� ���� �Ǵ� ���͸��� ���� �̸�
* @param  lpNewFileName ���� �Ǵ� ���丮�� �� �̸�
* @param  lpProgressRoutine ������ �ٸ� �κ��� �̵� �� ������ ȣ�� �Ǵ� CopyProgressRoutine �ݹ� �Լ��� ���� ������
* @param  lpData CopyProgressRoutine �ݹ� �Լ��� ������ �μ�
* @param  dwFlags �̵� �ɼ�
* @param  hTransaction Ʈ����� �ڵ�
* @return ����/���п���
*/
BOOL test_MoveFileTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCTSTR            lpExistingFileName = L"������\\test_MoveFileTransactedW.txt";
	LPCTSTR            lpNewFileName = L"������\\test_MoveFileTransactedW_moved.txt";
	LPPROGRESS_ROUTINE lpProgressRoutine = NULL;
	LPVOID             lpData = NULL;
	DWORD              dwFlags = MOVEFILE_COPY_ALLOWED;
	HANDLE  hTransaction, hFile;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hTransaction = MyCreateTransaction())){
		return FALSE;
	}
	if(!(hFile = MyCreateFile(lpExistingFileName))){
		return FALSE;
	}
	if(!CloseHandle(hFile)){
		strcpy(msg, GetErrorMessage("CloseHandle ���� : ", GetLastError()));
		strcpy(buf, "CloseHandle ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CloseHandle ����", msg);
		
		return FALSE;
	}

	result = MoveFileTransactedW(lpExistingFileName, lpNewFileName, lpProgressRoutine, lpData, dwFlags, hTransaction);

	if(result){
		sprintf(msg, "MoveFileTransactedW ����");
		strcpy(buf, "MoveFileTransactedW ����");
		
	}else{
		strcpy(msg, GetErrorMessage("MoveFileTransactedW ���� : ", GetLastError()));
		strcpy(buf, "MoveFileTransactedW ����");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "MoveFileTransactedW ����", msg);

	CloseHandle(hTransaction);

	
	if(!DeleteFileW(lpExistingFileName)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
		#endif
	}

	return result;
}

/**
* BOOL MoveFileTransactedA(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine, 
LPVOID lpData, DWORD dwFlags, HANDLE hTransaction)
* �ڽ��� �����Ͽ� ���� �����̳� ���丮�� Ʈ����� �������� �̵��Ѵ�. ������� ����.
* @author : ������  
*
* @param  lpExistingFileName ���� ��ǻ�Ϳ��ִ� ���� ���� �Ǵ� ���͸��� ���� �̸�
* @param  lpNewFileName ���� �Ǵ� ���丮�� �� �̸�
* @param  lpProgressRoutine ������ �ٸ� �κ��� �̵� �� ������ ȣ�� �Ǵ� CopyProgressRoutine �ݹ� �Լ��� ���� ������
* @param  lpData CopyProgressRoutine �ݹ� �Լ��� ������ �μ�
* @param  dwFlags �̵� �ɼ�
* @param  hTransaction Ʈ����� �ڵ�
* @return ����/���п���
*/
BOOL test_MoveFileTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCSTR            lpExistingFileName = "������\\test_MoveFileTransactedW.txt";
	LPCSTR            lpNewFileName = "������\\test_MoveFileTransactedW_moved.txt";
	LPPROGRESS_ROUTINE lpProgressRoutine = NULL;
	LPVOID             lpData = NULL;
	DWORD              dwFlags = MOVEFILE_COPY_ALLOWED;
	HANDLE  hTransaction, hFile;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hTransaction = MyCreateTransaction())){
		return FALSE;
	}
	if(!(hFile = MyCreateFileA(lpExistingFileName))){
		return FALSE;
	}
	if(!CloseHandle(hFile)){
		strcpy(msg, GetErrorMessage("CloseHandle ���� : ", GetLastError()));
		strcpy(buf, "CloseHandle ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CloseHandle ����", msg);
		
		return FALSE;
	}

	result = MoveFileTransactedA(lpExistingFileName, lpNewFileName, lpProgressRoutine, lpData, dwFlags, hTransaction);

	if(result){
		sprintf(msg, "MoveFileTransactedW ����");
		strcpy(buf, "MoveFileTransactedW ����");
		
	}else{
		strcpy(msg, GetErrorMessage("MoveFileTransactedW ���� : ", GetLastError()));
		strcpy(buf, "MoveFileTransactedW ����");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "MoveFileTransactedW ����", msg);

	CloseHandle(hTransaction);

	
	if(!DeleteFileA(lpExistingFileName)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileA ���� : ", GetLastError()));
		#endif
	}

	return result;
}

/**
* BOOL CopyFileTransactedW(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine, 
LPVOID lpData, LPBOOL pbCancel, DWORD dwCopyFlags, HANDLE hTransaction)
* ���� ������ Ʈ����� ó���� �� ���Ͽ� �����Ͽ� �ݹ� �Լ��� ���� ���� ��Ȳ�� ���� ���α׷��� �˸���. �������� ����.
* @author : ������  
*
* @param  lpExistingFileName ���� ������ �̸�
* @param  lpNewFileName �� ���� �̸�
* @param  lpProgressRoutine ������ �ٸ� �κ��� ���� �� ������ ȣ��Ǵ� LPPROGRESS_ROUTINE ������ �ݹ� �Լ��� ������
* @param  lpData CopyProgressRoutine �ݹ� �Լ��� ������ �μ�
* @param  pbCancel ���� �۾� �߿� �� �÷��׸� TRUE �� ���� �ϸ� �۾��� ���
* @param  dwCopyFlags ������ �����ϴ� ����� �����ϴ� �÷���
* @param  hTransaction Ʈ����� �ڵ�
* @return ����/���п���
*/
BOOL test_CopyFileTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCTSTR            lpExistingFileName = L"������\\test_CopyFileTransactedW.txt";
	LPCTSTR            lpNewFileName = L"������\\test_CopyFileTransactedW_copied.txt";
	LPPROGRESS_ROUTINE lpProgressRoutine = NULL;
	LPVOID             lpData = NULL;
	LPBOOL             pbCancel = NULL;
	DWORD              dwCopyFlags = COPY_FILE_OPEN_SOURCE_FOR_WRITE;
	HANDLE  hTransaction, hFile;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hTransaction = MyCreateTransaction())){
		return FALSE;
	}
	if(!(hFile = MyCreateFile(lpExistingFileName))){
		return FALSE;
	}
	if(!CloseHandle(hFile)){
		strcpy(msg, GetErrorMessage("CloseHandle ���� : ", GetLastError()));
		strcpy(buf, "CloseHandle ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CloseHandle ����", msg);
		
		return FALSE;
	}

	result = CopyFileTransactedW(lpExistingFileName, lpNewFileName, lpProgressRoutine, lpData, pbCancel, dwCopyFlags, hTransaction);

	if(result){
		sprintf(msg, "CopyFileTransactedW ����");
		strcpy(buf, "CopyFileTransactedW ����");
		
	}else{
		strcpy(msg, GetErrorMessage("CopyFileTransactedW ���� : ", GetLastError()));
		strcpy(buf, "CopyFileTransactedW ����");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CopyFileTransactedW ����", msg);

	CloseHandle(hTransaction);
	
	
	if(!DeleteFileW(lpExistingFileName)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileA ���� : ", GetLastError()));
		#endif
	}
	return result;
}

/**
* BOOL CopyFileTransactedA(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine, 
LPVOID lpData, LPBOOL pbCancel, DWORD dwCopyFlags, HANDLE hTransaction)
* ���� ������ Ʈ����� ó���� �� ���Ͽ� �����Ͽ� �ݹ� �Լ��� ���� ���� ��Ȳ�� ���� ���α׷��� �˸���. �������� ����.
* @author : ������  
*
* @param  lpExistingFileName ���� ������ �̸�
* @param  lpNewFileName �� ���� �̸�
* @param  lpProgressRoutine ������ �ٸ� �κ��� ���� �� ������ ȣ��Ǵ� LPPROGRESS_ROUTINE ������ �ݹ� �Լ��� ������
* @param  lpData CopyProgressRoutine �ݹ� �Լ��� ������ �μ�
* @param  pbCancel ���� �۾� �߿� �� �÷��׸� TRUE �� ���� �ϸ� �۾��� ���
* @param  dwCopyFlags ������ �����ϴ� ����� �����ϴ� �÷���
* @param  hTransaction Ʈ����� �ڵ�
* @return ����/���п���
*/
BOOL test_CopyFileTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCSTR            lpExistingFileName = "������\\test_CopyFileTransactedA.txt";
	LPCSTR            lpNewFileName = "������\\test_CopyFileTransactedA_copied.txt";
	LPPROGRESS_ROUTINE lpProgressRoutine = NULL;
	LPVOID             lpData = NULL;
	LPBOOL             pbCancel = NULL;
	DWORD              dwCopyFlags = COPY_FILE_OPEN_SOURCE_FOR_WRITE;
	HANDLE  hTransaction, hFile;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hTransaction = MyCreateTransaction())){
		return FALSE;
	}
	if(!(hFile = MyCreateFileA(lpExistingFileName))){
		return FALSE;
	}
	if(!CloseHandle(hFile)){
		strcpy(msg, GetErrorMessage("CloseHandle ���� : ", GetLastError()));
		strcpy(buf, "CloseHandle ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CloseHandle ����", msg);
		
		return FALSE;
	}

	result = CopyFileTransactedA(lpExistingFileName, lpNewFileName, lpProgressRoutine, lpData, pbCancel, dwCopyFlags, hTransaction);

	if(result){
		sprintf(msg, "CopyFileTransactedA ����");
		strcpy(buf, "CopyFileTransactedA ����");
		
	}else{
		strcpy(msg, GetErrorMessage("CopyFileTransactedA ���� : ", GetLastError()));
		strcpy(buf, "CopyFileTransactedA ����");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CopyFileTransactedA ����", msg);

	CloseHandle(hTransaction);
	
	
	if(!DeleteFileA(lpExistingFileName)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileA ���� : ", GetLastError()));
		#endif
	}

	return result;
}

/**
* BOOL DeleteFileTransactedW(LPCTSTR lpFileName, HANDLE hTransaction)
* Ʈ����� �� �۾����� ���� ������ �����Ѵ�. �������� ����.
* @author : ������  
*
* @param  lpFileName ������ ������ �̸�
* @param  hTransaction Ʈ����� �ڵ�
* @return ����/���п���
*/
BOOL test_DeleteFileTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCTSTR lpExistingFileName = L"������\\test_DeleteFileTransactedW.txt";
	HANDLE  hTransaction, hFile;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hTransaction = MyCreateTransaction())){
		return FALSE;
	}
	if(!(hFile = MyCreateFile(lpExistingFileName))){
		return FALSE;
	}
	if(!CloseHandle(hFile)){
		strcpy(msg, GetErrorMessage("CloseHandle ���� : ", GetLastError()));
		strcpy(buf, "CloseHandle ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CloseHandle ����", msg);
		
		return FALSE;
	}

	result = DeleteFileTransactedW(lpExistingFileName, hTransaction);

	if(result){
		sprintf(msg, "DeleteFileTransactedW ����");
		strcpy(buf, "DeleteFileTransactedW ����");
		
	}else{
		strcpy(msg, GetErrorMessage("DeleteFileTransactedW ���� : ", GetLastError()));
		strcpy(buf, "DeleteFileTransactedW ����");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "DeleteFileTransactedW ����", msg);

	CloseHandle(hTransaction);

	if(!DeleteFileW(lpExistingFileName)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
		#endif
	}

	return result;
}

/**
* BOOL DeleteFileTransactedA(LPCTSTR lpFileName, HANDLE hTransaction)
* Ʈ����� �� �۾����� ���� ������ �����Ѵ�. �������� ����.
* @author : ������  
*
* @param  lpFileName ������ ������ �̸�
* @param  hTransaction Ʈ����� �ڵ�
* @return ����/���п���
*/
BOOL test_DeleteFileTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCSTR lpExistingFileName = "������\\test_DeleteFileTransactedW.txt";
	HANDLE  hTransaction, hFile;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hTransaction = MyCreateTransaction())){
		return FALSE;
	}
	if(!(hFile = MyCreateFileA(lpExistingFileName))){
		return FALSE;
	}
	if(!CloseHandle(hFile)){
		strcpy(msg, GetErrorMessage("CloseHandle ���� : ", GetLastError()));
		strcpy(buf, "CloseHandle ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CloseHandle ����", msg);
		
		return FALSE;
	}

	result = DeleteFileTransactedA(lpExistingFileName, hTransaction);

	if(result){
		sprintf(msg, "DeleteFileTransactedW ����");
		strcpy(buf, "DeleteFileTransactedW ����");
		
	}else{
		strcpy(msg, GetErrorMessage("DeleteFileTransactedW ���� : ", GetLastError()));
		strcpy(buf, "DeleteFileTransactedW ����");
		
		result = FALSE;
	}
		
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "DeleteFileTransactedW ����", msg);

	CloseHandle(hTransaction);

	if(!DeleteFileA(lpExistingFileName)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
		#endif
	}

	return result;
}

/**
* HANDLE CreateFileTransactedW(LPCTSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, 
LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile,
HANDLE hTransaction, PUSHORT pusMiniVersion, PVOID pExtendedParameter)
* ����, ���� ��Ʈ�� �Ǵ� ���丮�� Ʈ����� �۾����� �����ϰų� ����. �� �Լ��� ��ü�� �׼����ϴµ� ����� ���ִ� �ڵ��� ��ȯ�Ѵ�. �������� ����.
* @author : ������  
*
* @param  lpFileName ���ų� �� ���� �̸�
* @param  dwDesiredAccess �б�, ����, �� �� �Ǵ� �� �� (0)�� ��� �� ���ִ� ��ü�� ���� �׼�������
* @param  dwShareMode ��ü�� ���� ���. �б�, ����, �� ��, ����, ��� �Ǵ� ����
* @param  lpSecurityAttributes SECURITY_ATTRIBUTES ����ü�� ���� ������
* @param  dwCreationDisposition �����ϰ� �������� �ʴ� ������ ���ϴ� �۾�
* @param  dwFlagsAndAttributes ���� �Ӽ� �� �÷��� FILE_ATTRIBUTE_NORMAL �� ���� �Ϲ����� �⺻��
* @param  hTemplateFile GENERIC_READ �׼��� ���� ���ִ� ���ø�Ʈ ���Ͽ� ���� ��ȿ�� �ڵ�
* @param  hTransaction Ʈ����� �ڵ�
* @param  pusMiniVersion �̴� ������ ������
* @param  pExtendedParameter ����
* @return ���� �� �ڵ� ����, ���� �� INVALID_HANDLE_VALUE 
*/
BOOL test_CreateFileTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCWSTR lpFileName = L"������\\test_CreateFileTransactedW.txt";
	HANDLE  hTransaction, hFile;
	PUSHORT pusMiniVersion = NULL;
	PVOID pExtendedParameter = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hTransaction = MyCreateTransaction())){
		return FALSE;
	}
	

	hFile = CreateFileTransactedW(lpFileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL, hTransaction, pusMiniVersion, pExtendedParameter);

	if(INVALID_HANDLE_VALUE != hFile){ //���� ���� ����
		sprintf(msg, "CreateFileTransactedW ����");
		strcpy(buf, "CreateFileTransactedW ����");

	}else{
		strcpy(msg, GetErrorMessage("CreateFileTransactedW ���� : ", GetLastError()));
		strcpy(buf, "CreateFileTransactedW ����");
		
		result = FALSE;
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateFileTransactedW ����", msg);

	CloseHandle(hTransaction);

	if(!DeleteFileW(lpFileName)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
		#endif
	}

	return result;

}


/**
* HANDLE CreateFileTransactedA(LPCTSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, 
LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile,
HANDLE hTransaction, PUSHORT pusMiniVersion, PVOID pExtendedParameter)
* ����, ���� ��Ʈ�� �Ǵ� ���丮�� Ʈ����� �۾����� �����ϰų� ����. �� �Լ��� ��ü�� �׼����ϴµ� ����� ���ִ� �ڵ��� ��ȯ�Ѵ�. �������� ����.
* @author : ������  
*
* @param  lpFileName ���ų� �� ���� �̸�
* @param  dwDesiredAccess �б�, ����, �� �� �Ǵ� �� �� (0)�� ��� �� ���ִ� ��ü�� ���� �׼�������
* @param  dwShareMode ��ü�� ���� ���. �б�, ����, �� ��, ����, ��� �Ǵ� ����
* @param  lpSecurityAttributes SECURITY_ATTRIBUTES ����ü�� ���� ������
* @param  dwCreationDisposition �����ϰ� �������� �ʴ� ������ ���ϴ� �۾�
* @param  dwFlagsAndAttributes ���� �Ӽ� �� �÷��� FILE_ATTRIBUTE_NORMAL �� ���� �Ϲ����� �⺻��
* @param  hTemplateFile GENERIC_READ �׼��� ���� ���ִ� ���ø�Ʈ ���Ͽ� ���� ��ȿ�� �ڵ�
* @param  hTransaction Ʈ����� �ڵ�
* @param  pusMiniVersion �̴� ������ ������
* @param  pExtendedParameter ����
* @return ���� �� �ڵ� ����, ���� �� INVALID_HANDLE_VALUE 
*/
BOOL test_CreateFileTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCSTR lpFileName = "������\\test_CreateFileTransactedA.txt";
	HANDLE  hTransaction, hFile;
	PUSHORT pusMiniVersion = NULL;
	PVOID pExtendedParameter = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hTransaction = MyCreateTransaction())){
		return FALSE;
	}
	

	hFile = CreateFileTransactedA(lpFileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL, hTransaction, pusMiniVersion, pExtendedParameter);

	if(INVALID_HANDLE_VALUE != hFile){ //���� ���� ����
		sprintf(msg, "CreateFileTransactedA ����");
		strcpy(buf, "CreateFileTransactedA ����");

	}else{
		strcpy(msg, GetErrorMessage("CreateFileTransactedA ���� : ", GetLastError()));
		strcpy(buf, "CreateFileTransactedA ����");
		
		result = FALSE;
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateFileTransactedA ����", msg);

	CloseHandle(hTransaction);

	if(!DeleteFileA(lpFileName)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileA ���� : ", GetLastError()));
		#endif
	}

	return result;
}


/**
* BOOL WriteFileGather(HANDLE hFile, FILE_SEGMENT_ELEMENT aSegmentArray[], DWORD nNumberOfBytesToWrite, 
LPDWORD lpReserved, LPOVERLAPPED lpOverlapped)
* ���� �迭���� �����͸� �˻��ϰ� �����͸� ���Ͽ� ����. �񵿱� ����.
* @author : ������  
*
* @param  hFile ���� �ڵ�
* @param  aSegmentArray �����͸� �����ϴ� FILE_SEGMENT_ELEMENT ���� �� �迭�� ���� ������
* @param  nNumberOfBytesToWrite ��� �� �� ����Ʈ ��
* @param  lpReserved ����
* @param  lpOverlapped OVERLAPPED ������ ������ ���� ������
* @return ����/���� ����
*/
BOOL test_WriteFileGather()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode = 0;

	const unsigned int PAGE_NUM = 512;
	HANDLE hFile = NULL;
	LPCTSTR lpFileName = L"������\\test_WriteFileGather.txt";
	FILE_SEGMENT_ELEMENT SegElement[PAGE_NUM + 1];
	BYTE * BufList[PAGE_NUM];
	OVERLAPPED         ov = {0};
	BYTE * BaseAddress;
	BOOL ovResult = FALSE;
	

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif
	
	/* �� �������� �غ� */
	BaseAddress = (BYTE *)VirtualAlloc (NULL, PAGE_NUM * sizeof(BYTE), MEM_COMMIT, PAGE_READWRITE);
	for (int i = 0; i <PAGE_NUM; i ++) {
		BufList [i] = BaseAddress + sizeof(BYTE) * i;
		FillMemory (BufList [i], sizeof(BYTE), i % 256);
	}

	/* ���� ����� */
	if(!(hFile = CreateFile (lpFileName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_ARCHIVE | FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING,	NULL))){

		sprintf(msg, GetErrorMessage("CreateFile ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile ����", msg);

		return FALSE;
	}

	/* WriteFileGather �� �Է� ������ �ʱ�ȭ */
	for (int i = 0; i <PAGE_NUM; i ++) SegElement[i].Buffer = (PVOID64)BufList[i];
	SegElement[PAGE_NUM].Alignment = (ULONGLONG) NULL;
	SegElement[PAGE_NUM].Buffer = (PVOID64) NULL;

	ov.Offset = 0;
	ov.OffsetHigh = 0;
	ov.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);

	/* ���Ͽ� ���� */
	result = WriteFileGather (hFile, SegElement, 0, NULL, &ov);
	WaitForSingleObject (ov.hEvent, 3000);
	
	/* ����/���� �Ǵ� */
	if(result){ 
		sprintf(msg, "WriteFileGather ���� : Overlapped.internal = %d", ov.Internal);
		strcpy(buf, "WriteFileGather ����");

	}else{
		errorCode = GetLastError();

		if(ERROR_IO_PENDING == errorCode){ //I/O�۾��� �Ϸ���� ����

			for(int i=0; i<512; i++){
				ovResult = HasOverlappedIoCompleted(&ov);

				if(ovResult){ //I/O completed..
					sprintf(msg, "WriteFileGather ����");
					strcpy(buf, "WriteFileGather ����");

					break;
				}
			}
			if(!ovResult){ // I/O Completed�� ��ٷ����� �Ϸ���� �ʴ� ���
				strcpy(msg, GetErrorMessage("WriteFileGather ���� : ", GetLastError()));
				strcpy(buf, "WriteFileGather ����");

				result = FALSE;
			}
		}else{ //�� ���� ������ ����
			strcpy(msg, GetErrorMessage("WriteFileGather ���� : ", GetLastError()));
			strcpy(buf, "WriteFileGather ����");

			result = FALSE;
		}
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "WriteFileGather ����", msg);

	CloseHandle(hFile);
	VirtualFree (BaseAddress, 0, MEM_RELEASE);
	CloseHandle (ov.hEvent);

	if(!DeleteFileW(lpFileName)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
		#endif
	}

	return result;
}