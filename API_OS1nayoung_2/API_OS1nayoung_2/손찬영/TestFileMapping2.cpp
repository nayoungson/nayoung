#include "TestFileMapping2.h"


/**
* HANDLE OpenFileMappingW(DWORD dwDesiredAccess, BOOL bInheritHandle,  LPCTSTR lpName)
* ���� ���� ���� ��ü�� ����.
* @author : ������  
*
* @param  dwDesiredAccess ���� ���� ��ü�� ���� �׼���
* @param  bInheritHandle �� �Ű� ������ TRUE �̸� CreateProcess �Լ��� ���� ���μ��� �� �ڵ��� ��� �� �� ����
* @param  lpName �� ���� ���� ��ü�� �̸�
* @return �Լ��� �����ϸ� ��ȯ ���� ������ ���� ���� ��ü�� ���� ���� �ڵ�, �����ϸ� NULL
*/
BOOL test_OpenFileMappingW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;

	HANDLE hFile = NULL;
	HANDLE hFileMapOpen = NULL;
	HANDLE hFileMapCreate = NULL;
	LPCWSTR fileName =  L"������\\test_OpenFileMappingW.txt";
	BOOL isCpMsg=FALSE;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif
	
	//������ ������ ����.
	//Communications Resources�� ���� ���½ÿ��� OPEN_EXISTING���� ��.
	//��ó https://msdn.microsoft.com/en-us/library/windows/desktop/aa363858(v=vs.85).aspx
	hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 
	
	if(hFile == INVALID_HANDLE_VALUE){ //���� ���� ����
		#ifdef OQADBGPRINT
		printf("hFile == INVALID_HANDLE_VALUE\n");
		#endif
		if((errorCode = GetLastError()) == ERROR_FILE_NOT_FOUND){ //������ �������� ������ ���� �����ϰ� �ٽ� OPEN_EXISTING�� ����.
			#ifdef OQADBGPRINT
			printf("errorCode == ERROR_FILE_NOT_FOUND\n");
			#endif
			hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
			CloseHandle(hFile);

			hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 
		}
		if(hFile == INVALID_HANDLE_VALUE){ //������ �����ϰ� �ٽ� ���� �õ��������� �����ϴ� ���� ����
			#ifdef OQADBGPRINT
			printf("�����ϰ� �ٽ� �����µ� �� ����\n");
			#endif
			sprintf(msg, GetErrorMessage("CreateFile ���� : ", errorCode));
			strcpy(buf, "CreateFile ����");

			wresult(__FILE__,__LINE__ , __FUNCTION__, msg, "CreateFile ����", msg);

			return FALSE;
		}
	}

	///*
	//[TEST 1] �������� �ʴ� ���ϸ����� ���� �õ�
	//*/
	//	
	//// "MyFileMap"�� Create�� Open�� �����ؾ� ��.
	//#ifdef OQADBG
	//MessageBoxA(NULL, "[TEST 1]\n�������� �ʴ� ���ϸ� ������ �õ��մϴ�.", "test_OpenFileMappingW", MB_OK);
	//#endif

	//hFileMapOpen = OpenFileMappingW(FILE_MAP_READ, NULL, L"MyFileMap");
	//if(hFileMapOpen != NULL){ // ���ϸ� ���� ����
	//	sprintf(msg, "hFileMapOpen = %d", hFileMapOpen);
	//	strcpy(buf, "FileMapping Open ����");

	//}else if(errorCode=GetLastError()){ // �̺�Ʈ ���� ����
	//	strcpy(msg, GetErrorMessage(" FileMapping Open ���� : ", errorCode));
	//	strcpy(buf, "FileMapping Open ����");
	//	result = FALSE;	

	//}else{
	//	sprintf(msg, "�� �� ���� ����\nhFileMapOpen = %d\nerrorCode=%d", hFileMapOpen, errorCode);
	//	result = FALSE;	

	//}
	//wresult(__FILE__,__LINE__ ,"OpenFileMappingW", buf, "FileMapping Open ����", msg);

	/*
	[TEST 2] ������ �����ϰ� ���� Ȯ��
	*/

	#ifdef OQADBG
	MessageBoxA(NULL, "[TEST 2]\n���ϸ��� �����ϰ� ������ �õ��մϴ�.", "test_OpenFileMappingW", MB_OK);
	#endif
	hFileMapCreate = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, sizeof(int), L"MyFileMap");
	if(hFileMapCreate == NULL){ //���ϸ� ���� ����
		strcpy(msg, GetErrorMessage("CreateFileMapping ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ , __FUNCTION__, msg, "CreateFileMapping ����", msg);

		return FALSE;
	}
	hFileMapOpen = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"MyFileMap");
	if(hFileMapOpen != NULL){ // ���ϸ� ���� ����
		sprintf(msg, "OpenFileMappingW ���� : hFileMapCreate = %d\nhFileMapOpen = %d", hFileMapCreate, hFileMapOpen);
		strcpy(buf, "OpenFileMappingW ����");

	}else{
		strcpy(msg, GetErrorMessage("OpenFileMappingW ���� : ", GetLastError()));
		strcpy(buf, "OpenFileMappingW ����");
		result = FALSE;	
	}

	wresult(__FILE__,__LINE__ , __FUNCTION__, buf, "OpenFileMappingW ����", msg);


	CloseHandle(hFile);
	CloseHandle(hFileMapOpen);
	CloseHandle(hFileMapCreate);
	
	DeleteFile(fileName);

	return result;
}


/**
* LPVOID MapViewOfFileExNuma(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh,  
DWORD dwFileOffsetLow, SIZE_T dwNumberOfBytesToMap, LPVOID lpBaseAddress, DWORD nndPreferred)
* ���� ���κ��⸦ ȣ�� ���μ����� �ּ� ������ �����ϰ� ���� �޸𸮿� ���� NUMA ��带 �����Ѵ�.
* @author : ������  
*
* @param  hFileMappingObject ���� ���� ��ü�� ���� �ڵ�
* @param  dwDesiredAccess �������� ������ ��ȣ�� �����ϴ� ���� ���� ��ü�� ���� �׼���
* @param  dwFileOffsetHigh ���Ⱑ ���۵� ���� ���� ������
* @param  dwFileOffsetLow ���Ⱑ ���۵� ���� ���� ������
* @param  dwNumberOfBytesToMap �信 ���� �� ���� ������ ����Ʈ ��
* @param  lpBaseAddress ������ ���۵Ǵ� ȣ�� ���μ��� �ּ� ������ �޸� �ּҿ� ���� ������
* @param  nndPreferred ������ �޸𸮰� �־���ϴ� NUMA ���
* @return �����ϸ� ��ȯ ���� ���� �� ���� ���� �ּ�, �����ϸ� NULL
*/
BOOL test_MapViewOfFileExNuma()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;

	HANDLE hFile = NULL;
	HANDLE hFileMapOpen = NULL;
	HANDLE hFileMapCreate = NULL;
	LPCWSTR fileName =  L"������\\test_MapViewOfFileExNuma.txt";
	BOOL isCpMsg=FALSE;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	//hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//if(hFile == INVALID_HANDLE_VALUE){ //���� ���� ����
	//	sprintf(msg, GetErrorMessage("CreateFile ���� : ", GetLastError()));
	//	wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile ����", msg);

	//	return FALSE;
	//}

	//hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 

	//if(hFile == INVALID_HANDLE_VALUE){ //���� ���� ����
	//	#ifdef OQADBGPRINT
	//	printf("hFile == INVALID_HANDLE_VALUE\n");
	//	#endif
	//	if((errorCode = GetLastError()) == ERROR_FILE_NOT_FOUND){ //������ �������� ������ ���� �����ϰ� �ٽ� OPEN_EXISTING�� ����.
	//		#ifdef OQADBGPRINT
	//		printf("errorCode == ERROR_FILE_NOT_FOUND\n");
	//		#endif
	//		hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	//		CloseHandle(hFile);

	//		hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 
	//	}
	//	if(hFile == INVALID_HANDLE_VALUE){ //������ �����ϰ� �ٽ� ���� �õ��������� �����ϴ� ���� ����
	//		#ifdef OQADBGPRINT
	//		printf("�����ϰ� �ٽ� �����µ� �� ����\n");
	//		#endif
	//		sprintf(msg, GetErrorMessage("CreateFile ���� : ", errorCode));
	//		strcpy(buf, "CreateFile ����");

	//		wresult(__FILE__,__LINE__ , __FUNCTION__, msg, "CreateFile ����", msg);

	//		return FALSE;
	//	}
	//}

	hFileMapCreate = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, sizeof(int), L"test_MapViewOfFileExNuma");
	if(NULL == hFileMapCreate){ //���ϸ� ���� ����
		strcpy(msg, GetErrorMessage("CreateFileMapping ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFileMapping ����", msg);

		return FALSE;
	}

	hFileMapOpen = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"test_MapViewOfFileExNuma");
	if(NULL == hFileMapOpen){ // ���ϸ� ���� ����
		strcpy(msg, GetErrorMessage("OpenFileMappingW ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "OpenFileMappingW ����", msg);

		return FALSE;
	}

	if(NULL == MapViewOfFileExNuma(hFileMapOpen, FILE_MAP_ALL_ACCESS, 0, 0, 0, NULL, 0)){
		strcpy(msg, GetErrorMessage("MapViewOfFileExNuma ���� : ", GetLastError()));
		strcpy(buf, "MapViewOfFileExNuma ����");

		result = FALSE;

	}else{
		strcpy(msg, "MapViewOfFileExNuma ����");
		strcpy(buf, msg);
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "MapViewOfFileExNuma ����", msg);

	
	CloseHandle(hFileMapOpen);
	CloseHandle(hFileMapCreate);

	if(!DeleteFileW(fileName)){
		#ifdef OQADBGPRINT
		printf(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
		puts("");
		#endif
	}
	return result;
}

/**
* HANDLE WINAPI CreateFileMappingNuma(
  _In_     HANDLE                hFile,
  _In_opt_ LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
  _In_     DWORD                 flProtect,
  _In_     DWORD                 dwMaximumSizeHigh,
  _In_     DWORD                 dwMaximumSizeLow,
  _In_opt_ LPCTSTR               lpName,
  _In_     DWORD                 nndPreferred
);
* ������ ���Ͽ� ���� �̸��� �ְų� �̸��̾��� ���� ���� ��ü�� ����ų� ���� ���� �޸𸮿� ���� NUMA ��带 �����Ѵ�.
* @author : ������  
*
* @param  hFile ���� ���� ��ü�� ���� ������ �ڵ�
* @param  lpFileMappingAttributes ��ȯ �� �ڵ��� �ڽ� ���μ����� ��� �� �� �ִ��� ���θ� ���� �ϴ� SECURITY_ATTRIBUTES ����ü�� ���� ������
* @param  flProtect ���� ���� ��ü�� ������ ��ȣ�� ����
* @param  dwMaximumSizeHigh ���� ���� ��ü�� �ִ� ũ���� ���� DWORD
* @param  dwMaximumSizeLow ���� ���� ��ü�� �ִ� ũ���� ���� DWORD
* @param  lpName ���� ���� ��ü�� �̸�
* @param  nndPreferred ������ �޸𸮰� �־���ϴ� NUMA ���
* @return �����ϸ� ��ȯ ���� ���� ���� ��ü�� �ڵ�, �����ϸ� NULL
*/
BOOL test_CreateFileMappingNumaW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hFile = NULL;
	LPCWSTR fileName =  L"������\\test_CreateFileMappingNumaW.txt";
	HANDLE hFileMapCreate = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hFileMapCreate = CreateFileMappingNumaW(hFile, NULL, PAGE_READWRITE, 0, sizeof(int), L"test_MapViewOfFileExNuma", NUMA_NO_PREFERRED_NODE);
	if(NULL != hFileMapCreate){ //���ϸ� ���� ����
		sprintf(msg, "CreateFileMappingNumaW ���� : hFileMapCreate = %d", hFileMapCreate);
		strcpy(buf, "CreateFileMappingNumaW ����");		
		
	}else{
		strcpy(msg, GetErrorMessage("CreateFileMappingNumaW ���� : ", GetLastError()));
		strcpy(buf, "CreateFileMappingNumaW ����");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateFileMappingNumaW ����", msg);

	return result;
}

/**
* HANDLE WINAPI CreateFileMappingNuma(
  _In_     HANDLE                hFile,
  _In_opt_ LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
  _In_     DWORD                 flProtect,
  _In_     DWORD                 dwMaximumSizeHigh,
  _In_     DWORD                 dwMaximumSizeLow,
  _In_opt_ LPCTSTR               lpName,
  _In_     DWORD                 nndPreferred
);
* ������ ���Ͽ� ���� �̸��� �ְų� �̸��̾��� ���� ���� ��ü�� ����ų� ���� ���� �޸𸮿� ���� NUMA ��带 �����Ѵ�.
* @author : ������  
*
* @param  hFile ���� ���� ��ü�� ���� ������ �ڵ�
* @param  lpFileMappingAttributes ��ȯ �� �ڵ��� �ڽ� ���μ����� ��� �� �� �ִ��� ���θ� ���� �ϴ� SECURITY_ATTRIBUTES ����ü�� ���� ������
* @param  flProtect ���� ���� ��ü�� ������ ��ȣ�� ����
* @param  dwMaximumSizeHigh ���� ���� ��ü�� �ִ� ũ���� ���� DWORD
* @param  dwMaximumSizeLow ���� ���� ��ü�� �ִ� ũ���� ���� DWORD
* @param  lpName ���� ���� ��ü�� �̸�
* @param  nndPreferred ������ �޸𸮰� �־���ϴ� NUMA ���
* @return �����ϸ� ��ȯ ���� ���� ���� ��ü�� �ڵ�, �����ϸ� NULL
*/
BOOL test_CreateFileMappingNumaA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hFile = NULL;
	LPCWSTR fileName =  L"������\\test_CreateFileMappingNumaW.txt";
	HANDLE hFileMapCreate = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hFileMapCreate = CreateFileMappingNumaA(hFile, NULL, PAGE_READWRITE, 0, sizeof(int), "test_CreateFileMappingNumaA", NUMA_NO_PREFERRED_NODE);
	if(NULL != hFileMapCreate){ //���ϸ� ���� ����
		sprintf(msg, "CreateFileMappingNumaA ���� : hFileMapCreate = %d", hFileMapCreate);
		strcpy(buf, "CreateFileMappingNumaA ����");		
		
	}else{
		strcpy(msg, GetErrorMessage("CreateFileMappingNumaA ���� : ", GetLastError()));
		strcpy(buf, "CreateFileMappingNumaA ����");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateFileMappingNumaA ����", msg);

	return result;
}


/**
* BOOL WINAPI GetNumaAvailableMemoryNode(
  _In_  UCHAR      Node,
  _Out_ PULONGLONG AvailableBytes
);
* ������ ���Ͽ� ���� �̸��� �ְų� �̸��̾��� ���� ���� ��ü�� ����ų� ���� ���� �޸𸮿� ���� NUMA ��带 �����Ѵ�.
* @author : ������  
*
* @param  Node ����� ��ȣ
* @param  AvailableBytes ����� ��� ������ �޸� �� (����Ʈ)
* @return ����/���� ����
*/
BOOL test_GetNumaAvailableMemoryNode()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	UCHAR Node = 0;
	ULONGLONG AvailableBytes;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	result = GetNumaAvailableMemoryNode(Node, &AvailableBytes);
	if(result){ //���ϸ� ���� ����
		sprintf(msg, "GetNumaAvailableMemoryNode ���� : Node = %d\nAvailableBytes = %llu", Node, AvailableBytes);
		strcpy(buf, "GetNumaAvailableMemoryNode ����");		
		
	}else{
		strcpy(msg, GetErrorMessage("GetNumaAvailableMemoryNode ���� : ", GetLastError()));
		strcpy(buf, "GetNumaAvailableMemoryNode ����");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetNumaAvailableMemoryNode ����", msg);

	return result;

}

/**
* BOOL GetNumaAvailableMemoryNodeEx(
  _In_  USHORT     Node,
  _Out_ PULONGLONG AvailableBytes
);
* ������ ���Ͽ� ���� �̸��� �ְų� �̸��̾��� ���� ���� ��ü�� ����ų� ���� ���� �޸𸮿� ���� NUMA ��带 �����Ѵ�.
* @author : ������  
*
* @param  Node ����� ��ȣ
* @param  AvailableBytes ����� ��� ������ �޸� �� (����Ʈ)
* @return ����/���� ����
*/
BOOL test_GetNumaAvailableMemoryNodeEx()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	USHORT Node = 0;
	ULONGLONG AvailableBytes;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	result = GetNumaAvailableMemoryNodeEx(Node, &AvailableBytes);
	if(result){ //���ϸ� ���� ����
		sprintf(msg, "GetNumaAvailableMemoryNodeEx ���� : Node = %hd\nAvailableBytes = %llu", Node, AvailableBytes);
		strcpy(buf, "GetNumaAvailableMemoryNodeEx ����");		
		
	}else{
		strcpy(msg, GetErrorMessage("GetNumaAvailableMemoryNodeEx ���� : ", GetLastError()));
		strcpy(buf, "GetNumaAvailableMemoryNodeEx ����");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetNumaAvailableMemoryNodeEx ����", msg);

	return result;

}