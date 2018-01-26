#include "TestFileMapping2.h"


/**
* HANDLE OpenFileMappingW(DWORD dwDesiredAccess, BOOL bInheritHandle,  LPCTSTR lpName)
* 명명된 파일 매핑 개체를 연다.
* @author : 손찬영  
*
* @param  dwDesiredAccess 파일 매핑 객체에 대한 액세스
* @param  bInheritHandle 이 매개 변수가 TRUE 이면 CreateProcess 함수로 만든 프로세스 가 핸들을 상속 할 수 있음
* @param  lpName 열 파일 매핑 개체의 이름
* @return 함수가 성공하면 반환 값은 지정된 파일 매핑 객체에 대한 열린 핸들, 실패하면 NULL
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
	LPCWSTR fileName =  L"손찬영\\test_OpenFileMappingW.txt";
	BOOL isCpMsg=FALSE;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif
	
	//임의의 파일을 연다.
	//Communications Resources를 위한 오픈시에는 OPEN_EXISTING여야 함.
	//출처 https://msdn.microsoft.com/en-us/library/windows/desktop/aa363858(v=vs.85).aspx
	hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 
	
	if(hFile == INVALID_HANDLE_VALUE){ //파일 열기 실패
		#ifdef OQADBGPRINT
		printf("hFile == INVALID_HANDLE_VALUE\n");
		#endif
		if((errorCode = GetLastError()) == ERROR_FILE_NOT_FOUND){ //파일이 존재하지 않으면 새로 생성하고 다시 OPEN_EXISTING로 연다.
			#ifdef OQADBGPRINT
			printf("errorCode == ERROR_FILE_NOT_FOUND\n");
			#endif
			hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
			CloseHandle(hFile);

			hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 
		}
		if(hFile == INVALID_HANDLE_VALUE){ //파일을 생성하고 다시 열기 시도했음에도 실패하는 경우는 종료
			#ifdef OQADBGPRINT
			printf("생성하고 다시 열었는데 또 실패\n");
			#endif
			sprintf(msg, GetErrorMessage("CreateFile 실패 : ", errorCode));
			strcpy(buf, "CreateFile 실패");

			wresult(__FILE__,__LINE__ , __FUNCTION__, msg, "CreateFile 성공", msg);

			return FALSE;
		}
	}

	///*
	//[TEST 1] 존재하지 않는 파일매핑을 오픈 시도
	//*/
	//	
	//// "MyFileMap"은 Create와 Open이 동일해야 함.
	//#ifdef OQADBG
	//MessageBoxA(NULL, "[TEST 1]\n존재하지 않는 파일맵 오픈을 시도합니다.", "test_OpenFileMappingW", MB_OK);
	//#endif

	//hFileMapOpen = OpenFileMappingW(FILE_MAP_READ, NULL, L"MyFileMap");
	//if(hFileMapOpen != NULL){ // 파일맵 오픈 성공
	//	sprintf(msg, "hFileMapOpen = %d", hFileMapOpen);
	//	strcpy(buf, "FileMapping Open 성공");

	//}else if(errorCode=GetLastError()){ // 이벤트 오픈 실패
	//	strcpy(msg, GetErrorMessage(" FileMapping Open 실패 : ", errorCode));
	//	strcpy(buf, "FileMapping Open 실패");
	//	result = FALSE;	

	//}else{
	//	sprintf(msg, "알 수 없는 에러\nhFileMapOpen = %d\nerrorCode=%d", hFileMapOpen, errorCode);
	//	result = FALSE;	

	//}
	//wresult(__FILE__,__LINE__ ,"OpenFileMappingW", buf, "FileMapping Open 실패", msg);

	/*
	[TEST 2] 파일을 매핑하고 오픈 확인
	*/

	#ifdef OQADBG
	MessageBoxA(NULL, "[TEST 2]\n파일맵을 생성하고 오픈을 시도합니다.", "test_OpenFileMappingW", MB_OK);
	#endif
	hFileMapCreate = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, sizeof(int), L"MyFileMap");
	if(hFileMapCreate == NULL){ //파일맵 생성 실패
		strcpy(msg, GetErrorMessage("CreateFileMapping 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ , __FUNCTION__, msg, "CreateFileMapping 성공", msg);

		return FALSE;
	}
	hFileMapOpen = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"MyFileMap");
	if(hFileMapOpen != NULL){ // 파일맵 오픈 성공
		sprintf(msg, "OpenFileMappingW 성공 : hFileMapCreate = %d\nhFileMapOpen = %d", hFileMapCreate, hFileMapOpen);
		strcpy(buf, "OpenFileMappingW 성공");

	}else{
		strcpy(msg, GetErrorMessage("OpenFileMappingW 실패 : ", GetLastError()));
		strcpy(buf, "OpenFileMappingW 실패");
		result = FALSE;	
	}

	wresult(__FILE__,__LINE__ , __FUNCTION__, buf, "OpenFileMappingW 성공", msg);


	CloseHandle(hFile);
	CloseHandle(hFileMapOpen);
	CloseHandle(hFileMapCreate);
	
	DeleteFile(fileName);

	return result;
}


/**
* LPVOID MapViewOfFileExNuma(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh,  
DWORD dwFileOffsetLow, SIZE_T dwNumberOfBytesToMap, LPVOID lpBaseAddress, DWORD nndPreferred)
* 파일 매핑보기를 호출 프로세스의 주소 공간에 매핑하고 실제 메모리에 대한 NUMA 노드를 지정한다.
* @author : 손찬영  
*
* @param  hFileMappingObject 파일 매핑 객체에 대한 핸들
* @param  dwDesiredAccess 페이지의 페이지 보호를 결정하는 파일 매핑 객체에 대한 액세스
* @param  dwFileOffsetHigh 보기가 시작될 파일 상위 오프셋
* @param  dwFileOffsetLow 보기가 시작될 파일 하위 오프셋
* @param  dwNumberOfBytesToMap 뷰에 매핑 할 파일 매핑의 바이트 수
* @param  lpBaseAddress 맵핑이 시작되는 호출 프로세스 주소 공간의 메모리 주소에 대한 포인터
* @param  nndPreferred 물리적 메모리가 있어야하는 NUMA 노드
* @return 성공하면 반환 값은 매핑 된 뷰의 시작 주소, 실패하면 NULL
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
	LPCWSTR fileName =  L"손찬영\\test_MapViewOfFileExNuma.txt";
	BOOL isCpMsg=FALSE;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	//hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//if(hFile == INVALID_HANDLE_VALUE){ //파일 열기 실패
	//	sprintf(msg, GetErrorMessage("CreateFile 실패 : ", GetLastError()));
	//	wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile 성공", msg);

	//	return FALSE;
	//}

	//hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 

	//if(hFile == INVALID_HANDLE_VALUE){ //파일 열기 실패
	//	#ifdef OQADBGPRINT
	//	printf("hFile == INVALID_HANDLE_VALUE\n");
	//	#endif
	//	if((errorCode = GetLastError()) == ERROR_FILE_NOT_FOUND){ //파일이 존재하지 않으면 새로 생성하고 다시 OPEN_EXISTING로 연다.
	//		#ifdef OQADBGPRINT
	//		printf("errorCode == ERROR_FILE_NOT_FOUND\n");
	//		#endif
	//		hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	//		CloseHandle(hFile);

	//		hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 
	//	}
	//	if(hFile == INVALID_HANDLE_VALUE){ //파일을 생성하고 다시 열기 시도했음에도 실패하는 경우는 종료
	//		#ifdef OQADBGPRINT
	//		printf("생성하고 다시 열었는데 또 실패\n");
	//		#endif
	//		sprintf(msg, GetErrorMessage("CreateFile 실패 : ", errorCode));
	//		strcpy(buf, "CreateFile 실패");

	//		wresult(__FILE__,__LINE__ , __FUNCTION__, msg, "CreateFile 성공", msg);

	//		return FALSE;
	//	}
	//}

	hFileMapCreate = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, sizeof(int), L"test_MapViewOfFileExNuma");
	if(NULL == hFileMapCreate){ //파일맵 생성 실패
		strcpy(msg, GetErrorMessage("CreateFileMapping 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFileMapping 성공", msg);

		return FALSE;
	}

	hFileMapOpen = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"test_MapViewOfFileExNuma");
	if(NULL == hFileMapOpen){ // 파일맵 오픈 실패
		strcpy(msg, GetErrorMessage("OpenFileMappingW 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "OpenFileMappingW 성공", msg);

		return FALSE;
	}

	if(NULL == MapViewOfFileExNuma(hFileMapOpen, FILE_MAP_ALL_ACCESS, 0, 0, 0, NULL, 0)){
		strcpy(msg, GetErrorMessage("MapViewOfFileExNuma 실패 : ", GetLastError()));
		strcpy(buf, "MapViewOfFileExNuma 실패");

		result = FALSE;

	}else{
		strcpy(msg, "MapViewOfFileExNuma 성공");
		strcpy(buf, msg);
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "MapViewOfFileExNuma 성공", msg);

	
	CloseHandle(hFileMapOpen);
	CloseHandle(hFileMapCreate);

	if(!DeleteFileW(fileName)){
		#ifdef OQADBGPRINT
		printf(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
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
* 지정된 파일에 대해 이름이 있거나 이름이없는 파일 매핑 객체를 만들거나 열어 실제 메모리에 대한 NUMA 노드를 지정한다.
* @author : 손찬영  
*
* @param  hFile 파일 매핑 객체를 만들 파일의 핸들
* @param  lpFileMappingAttributes 반환 된 핸들을 자식 프로세스가 상속 할 수 있는지 여부를 결정 하는 SECURITY_ATTRIBUTES 구조체에 대한 포인터
* @param  flProtect 파일 매핑 개체의 페이지 보호를 지정
* @param  dwMaximumSizeHigh 파일 매핑 개체의 최대 크기의 상위 DWORD
* @param  dwMaximumSizeLow 파일 매핑 개체의 최대 크기의 하위 DWORD
* @param  lpName 파일 매핑 객체의 이름
* @param  nndPreferred 물리적 메모리가 있어야하는 NUMA 노드
* @return 성공하면 반환 값은 파일 매핑 객체의 핸들, 실패하면 NULL
*/
BOOL test_CreateFileMappingNumaW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hFile = NULL;
	LPCWSTR fileName =  L"손찬영\\test_CreateFileMappingNumaW.txt";
	HANDLE hFileMapCreate = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hFileMapCreate = CreateFileMappingNumaW(hFile, NULL, PAGE_READWRITE, 0, sizeof(int), L"test_MapViewOfFileExNuma", NUMA_NO_PREFERRED_NODE);
	if(NULL != hFileMapCreate){ //파일맵 생성 성공
		sprintf(msg, "CreateFileMappingNumaW 성공 : hFileMapCreate = %d", hFileMapCreate);
		strcpy(buf, "CreateFileMappingNumaW 성공");		
		
	}else{
		strcpy(msg, GetErrorMessage("CreateFileMappingNumaW 실패 : ", GetLastError()));
		strcpy(buf, "CreateFileMappingNumaW 실패");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateFileMappingNumaW 성공", msg);

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
* 지정된 파일에 대해 이름이 있거나 이름이없는 파일 매핑 객체를 만들거나 열어 실제 메모리에 대한 NUMA 노드를 지정한다.
* @author : 손찬영  
*
* @param  hFile 파일 매핑 객체를 만들 파일의 핸들
* @param  lpFileMappingAttributes 반환 된 핸들을 자식 프로세스가 상속 할 수 있는지 여부를 결정 하는 SECURITY_ATTRIBUTES 구조체에 대한 포인터
* @param  flProtect 파일 매핑 개체의 페이지 보호를 지정
* @param  dwMaximumSizeHigh 파일 매핑 개체의 최대 크기의 상위 DWORD
* @param  dwMaximumSizeLow 파일 매핑 개체의 최대 크기의 하위 DWORD
* @param  lpName 파일 매핑 객체의 이름
* @param  nndPreferred 물리적 메모리가 있어야하는 NUMA 노드
* @return 성공하면 반환 값은 파일 매핑 객체의 핸들, 실패하면 NULL
*/
BOOL test_CreateFileMappingNumaA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hFile = NULL;
	LPCWSTR fileName =  L"손찬영\\test_CreateFileMappingNumaW.txt";
	HANDLE hFileMapCreate = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hFileMapCreate = CreateFileMappingNumaA(hFile, NULL, PAGE_READWRITE, 0, sizeof(int), "test_CreateFileMappingNumaA", NUMA_NO_PREFERRED_NODE);
	if(NULL != hFileMapCreate){ //파일맵 생성 성공
		sprintf(msg, "CreateFileMappingNumaA 성공 : hFileMapCreate = %d", hFileMapCreate);
		strcpy(buf, "CreateFileMappingNumaA 성공");		
		
	}else{
		strcpy(msg, GetErrorMessage("CreateFileMappingNumaA 실패 : ", GetLastError()));
		strcpy(buf, "CreateFileMappingNumaA 실패");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateFileMappingNumaA 성공", msg);

	return result;
}


/**
* BOOL WINAPI GetNumaAvailableMemoryNode(
  _In_  UCHAR      Node,
  _Out_ PULONGLONG AvailableBytes
);
* 지정된 파일에 대해 이름이 있거나 이름이없는 파일 매핑 객체를 만들거나 열어 실제 메모리에 대한 NUMA 노드를 지정한다.
* @author : 손찬영  
*
* @param  Node 노드의 번호
* @param  AvailableBytes 노드의 사용 가능한 메모리 양 (바이트)
* @return 성공/실패 여부
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
	if(result){ //파일맵 생성 성공
		sprintf(msg, "GetNumaAvailableMemoryNode 성공 : Node = %d\nAvailableBytes = %llu", Node, AvailableBytes);
		strcpy(buf, "GetNumaAvailableMemoryNode 성공");		
		
	}else{
		strcpy(msg, GetErrorMessage("GetNumaAvailableMemoryNode 실패 : ", GetLastError()));
		strcpy(buf, "GetNumaAvailableMemoryNode 실패");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetNumaAvailableMemoryNode 성공", msg);

	return result;

}

/**
* BOOL GetNumaAvailableMemoryNodeEx(
  _In_  USHORT     Node,
  _Out_ PULONGLONG AvailableBytes
);
* 지정된 파일에 대해 이름이 있거나 이름이없는 파일 매핑 객체를 만들거나 열어 실제 메모리에 대한 NUMA 노드를 지정한다.
* @author : 손찬영  
*
* @param  Node 노드의 번호
* @param  AvailableBytes 노드의 사용 가능한 메모리 양 (바이트)
* @return 성공/실패 여부
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
	if(result){ //파일맵 생성 성공
		sprintf(msg, "GetNumaAvailableMemoryNodeEx 성공 : Node = %hd\nAvailableBytes = %llu", Node, AvailableBytes);
		strcpy(buf, "GetNumaAvailableMemoryNodeEx 성공");		
		
	}else{
		strcpy(msg, GetErrorMessage("GetNumaAvailableMemoryNodeEx 실패 : ", GetLastError()));
		strcpy(buf, "GetNumaAvailableMemoryNodeEx 실패");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetNumaAvailableMemoryNodeEx 성공", msg);

	return result;

}