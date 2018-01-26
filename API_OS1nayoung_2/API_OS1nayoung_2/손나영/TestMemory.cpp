#include "TestMemory.h"
#include <WERAPI.H>
#include <Psapi.h>
#include <TlHelp32.h>


/**
* BOOL WINAPI AddSecureMemoryCacheCallback(
  _In_ PSECURE_MEMORY_CACHE_CALLBACK pfnCallBack
  );
* 보안 메모리 범위가 해제되거나 보호가 변경 될 때 호출되는 콜백 함수를 등록
* @author : 손나영
*
* @param pfnCallBack 등록 할 응용 프로그램 정의 SecureMemoryCacheCallback 함수에 대한 포인터.
* @return 콜백 함수 등록 성공/실패 여부.
*/

BOOLEAN CALLBACK SecureMemoryCacheCallback(PVOID Addr,SIZE_T Range){
	return TRUE;
}

BOOL test_AddSecureMemoryCacheCallback(){

	#ifdef OQADBGPRINT
	printf("test_AddSecureMemoryCacheCallback\n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ];


	// 보안 메모리 범위가 해제되거나 보호가 변경될 때 호출되는 콜백 함수를 등록
	// BOOLEAN CALLBACK SecureMemoryCacheCallback(PVOID Addr, SIZE_T Range)
	BOOL result = AddSecureMemoryCacheCallback(SecureMemoryCacheCallback);

	if(result == TRUE){
		sprintf(msg, " AddSecureMemoryCacheCallback() : SUCCESS");
		strcpy(buf, "SUCCESS");

	}else{
		sprintf(msg, " AddSecureMemoryCacheCallback() : FAIL");
		result = FALSE;
	}

	// AddSecureMemoryCacheCallback함수로 등록된 콜백 함수의 등록을 취소
	result = RemoveSecureMemoryCacheCallback(SecureMemoryCacheCallback);

	if(result == FALSE){
		AddSecureMemoryCacheCallback(SecureMemoryCacheCallback);
	}

	wresult(__FILE__, __LINE__, "AddSecureMemoryCacheCallback", buf, "SUCCESS", msg);
	return result;
}


/**
* BOOL WINAPI AllocateUserPhysicalPages (
  _HANDLE hProcess,
  _Inout_ PULONG_PTR NumberOfPages,
  _Out_ PULONG_PTR UserPfnArray
  );
* 지정된 프로세스의 AWE ( Address Windowing Extensions ) 영역 내에서 매핑 및 매핑 해제 할 물리적 메모리 페이지를 할당.
* Itanium 기반 시스템의 64 비트 Windows 지원 → FAIL 상태.
* @author : 손나영
*
* @param hProcess 프로세스 핸들. PROCESS_VM_OPERATION 권한.
* @param NumberOfPages 할당 할 실제 메모리의 크기 (페이지). GetSystemInfo 함수.
* @param UserPfnArray 할당 된 메모리의 페이지 프레임 번호를 저장하는 배열에 대한 포인터. 배열의 크기는 최소한 ULONG_PTR 데이터 형식 의 NumberOfPages 배 이상. 변경X
* @return 할당 성공/실패 여부
*/

#define MEMORY_REQUESTED 1024*1024
BOOL test_AllocateUserPhysicalPages(){

	#ifdef OQADBGPRINT
	printf("test_AllocateUserPhysicalPages \n");
	#endif

	BOOL result;                   // generic Boolean value
	ULONG_PTR NumberOfPages;        // number of pages to request
	ULONG_PTR NumberOfPagesInitial; // initial number of pages requested
	ULONG_PTR *UserPfnArray;               // page info; holds opaque data
	SYSTEM_INFO sSysInfo = {0, };           // useful system information

	int PFNArraySize;  
	char buf[BUFSIZ];
	char msg[BUFSIZ]="FAIL";
	
	GetSystemInfo(&sSysInfo);  // fill the system information structure

	NumberOfPages = MEMORY_REQUESTED/sSysInfo.dwPageSize;
	PFNArraySize = NumberOfPages * sizeof (ULONG_PTR);
	UserPfnArray = (ULONG_PTR *) HeapAlloc(GetProcessHeap(), 0, PFNArraySize);

	NumberOfPagesInitial = NumberOfPages;

	//HANDLE hProcess = GetCurrentProcess();
	//HANDLE h = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_TERMINATE,FALSE, pid);

	DWORD num = GetCurrentProcessId();

	/**	PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		num : GetCurrentProcessId()		*/
	HANDLE hProcess = OpenProcess(PROCESS_VM_OPERATION, FALSE, num);

	//result = AllocateUserPhysicalPages(hProcess, &NumberOfPages,aPFNs);
	result = AllocateUserPhysicalPages(hProcess, &NumberOfPages, UserPfnArray);

	if(result == TRUE ){
		sprintf(msg, " AllocateUserPhysicalPages() : SUCCESS \n\n This computer has page size : %d \n Requesting a PFN array of %d bytes \n ", sSysInfo.dwPageSize, PFNArraySize);
		strcpy(buf, "SUCCESS");
	}else {
		strcpy(msg, " AllocateUserPhysicalPages() : FAIL \n\n <64-bit Windows on Itanium 전용 시스템>\n\n cmd 창에서 wmic cpu get architecture 입력했을 때 \n 6(means Itanium)과 9(means x64)가 출력되어야 지원함");
		strcpy(buf, "FAIL");
	}
	if(NumberOfPagesInitial != NumberOfPages) {
		//printf("numberofpagesinitial function is 
		//printf(("Allocated only %p pages.\n"), NumberOfPages );
		return 0;
	}
	wresult(__FILE__, __LINE__, "AllocateUserPhysicalPages", buf, "SUCCESS", msg);

	return result;
}


/** 
* BOOL WINAPI AllocateUserPhysicalPagesNuma(
  _In_    HANDLE     hProcess,
  _Inout_ PULONG_PTR NumberOfPages,
  _Out_   PULONG_PTR PageArray,
  _In_    DWORD      nndPreferred
  );
* 지정된 프로세스의 AWE ( Address Windowing Extensions ) 영역 내에서 매핑 및 매핑 해제 할 실제 메모리 페이지를 할당하고 실제 메모리에 대한 NUMA 노드를 지정
* @author : 손나영
*
* @param hProcess 프로세스 핸들. PROCESS_VM_OPERATION 권한.
* @param NumberOfPages 할당 할 실제 메모리의 크기 (페이지). GetSystemInfo 함수.
* @param PageArray 할당 된 메모리의 페이지 프레임 번호를 저장하는 배열에 대한 포인터. 할당되는 배열의 크기는 최소한 ULONG_PTR 데이터 형식 의 NumberOfPages 배 이상.
* @param nndPreferred 물리적 메모리가 있어야하는 NUMA 노드
* @return 페이지 할당 및 NUMA 노드 지정 성공/실패 여부.
*/

BOOL test_AllocateUserPhysicalPagesNuma(){
	
	int PFNArraySize;
	char buf[BUFSIZ];
	char msg[BUFSIZ]="FAIL";

	BOOL result;
	BOOL return_result = FALSE;
	ULONG_PTR *aPFNs;
	SYSTEM_INFO sSysInfo = {0, };
	ULONG_PTR NumberOfPages;

	HANDLE proccessHandle = GetCurrentProcess();     // get the handle to the current proccess
    DWORD typeOfAccess = TOKEN_ADJUST_PRIVILEGES;   //  requiered to enable or disable the privilege
//    HANDLE tokenHandle;                             //  handle to the opened access token

	//할당할 실제 메모리의 크기
	//출력 시 매개변수가 실제 할당된 페이지 수를 수신함. 요청된 수보다 적을 수 있음.

	int err = GetLastError();

	//sSyinfo 가져오는 함수
	GetSystemInfo(&sSysInfo);
	//sSysInfo.dwPageSize = 1024;
	NumberOfPages = MEMORY_REQUESTED/sSysInfo.dwPageSize;
	//NumberOfPages = 
	PFNArraySize = NumberOfPages * sizeof(ULONG_PTR);

	//할당된 메모리의 페이지 프레임 번호 저장하는 배열에 대한 포인터
	//최소한 ULONG_PTR데이터 형식의 NumberOfPages배 이상이어야 함.
	aPFNs = (ULONG_PTR *)HeapAlloc(GetProcessHeap(), 0, PFNArraySize);
	// 
	////권한 부여 SetPrivilege
	//if (OpenProcessToken(proccessHandle, typeOfAccess, &tokenHandle)){
	//	// Enabling RESTORE and BACKUP privileges
	//	SetPrivilege(tokenHandle, SE_ASSIGNPRIMARYTOKEN_NAME , TRUE);
	//	SetPrivilege(tokenHandle, SE_BACKUP_NAME , TRUE);
	//	printf(" 권한 부여 - 성공");

	//}else{
	//	wprintf(L"Error getting the access token.\n");
	//}
	

	/*if(!LoggedSetLockPagesPrivilege(GetCurrentProcess(), TRUE)){
		printf("logged 실패");
	}else
		printf("이건 성공");*/

	DWORD num = GetCurrentProcessId();
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_TERMINATE , FALSE, num);

	//함수 실행
	result = AllocateUserPhysicalPagesNuma(hProcess, &NumberOfPages, aPFNs, 0);

	if(result == TRUE){
		return_result = TRUE;
		strcpy(buf, "SUCCESS");
		strcpy(msg, " AllocateUserPhysicalPagesNuma() : SUCCESS");

	}else if(result == ERROR_PRIVILEGE_NOT_HELD){
		strcpy(buf, "FAIL");
		strcpy(msg, " AllocateUserPhysicalPagesNuma() : ERROR_PRIVILEGE_NOT_HELD");

	}else{
		printf("error code : %d %c", err, result);
		strcpy(buf, "FAIL");
		strcpy(msg, GetErrorMessage(" AllocateUserPhysicalPagesNuma() : FAIL  \n\n Error Message :" , GetLastError()));
	}


	wresult(__FILE__, __LINE__, "AllocateUserPhysicalPagesNuma", buf, "SUCCESS", msg);
	return return_result;
}


/** 
* BOOL WINAPI FreeUserPhysicalPages(
  _In_    HANDLE     hProcess,
  _Inout_ PULONG_PTR NumberOfPages,
  _In_    PULONG_PTR UserPfnArray
 );
* Itanium 기반 시스템의 64 비트 Windows
* AllocateUserPhysicalPages 또는 AllocateUserPhysicalPagesNuma로 할당한 실제 메모리 페이지를 해제.
* @author : 손나영
*
* @param Process 프로세스 핸들.
* @param NumberOfPages 물리 메모리 페이지 크기.
* @param UserPfnArray 해제 할 할당 된 메모리의 페이지 프레임 번호 배열에 대한 포인터.
* @return
*/

BOOL test_FreeUserPhysicalPages(){

	#ifdef OQADBGPRINT
	printf("test_FreeUserPhysicalPages\n");
	#endif

	BOOL result = FALSE;                   // generic Boolean value
	ULONG_PTR NumberOfPages;        // number of pages to request
	ULONG_PTR NumberOfPagesInitial; // initial number of pages requested
	ULONG_PTR *aPFNs;               // page info; holds opaque data
	SYSTEM_INFO sSysInfo;           // useful system information

	int PFNArraySize = 0;               // memory to request for PFN array
	char buf[BUFSIZ];
	char msg[BUFSIZ]="FAIL";

	GetSystemInfo(&sSysInfo);
	DWORD num = GetCurrentProcessId();
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_TERMINATE , FALSE, num);
	NumberOfPages = MEMORY_REQUESTED/sSysInfo.dwPageSize;
	PFNArraySize = NumberOfPages * sizeof (ULONG_PTR);
	aPFNs = (ULONG_PTR *) HeapAlloc(GetProcessHeap(), 0, PFNArraySize);
	GetSystemInfo(&sSysInfo);  // fill the system information structure

	

	

	//printf("This computer has page size %d.\n", sSysInfo.dwPageSize);

	/** Calculate the number of pages of memory to request.*/
	NumberOfPages = MEMORY_REQUESTED/sSysInfo.dwPageSize;
	//printf("Requesting %d pages of memory.\n", NumberOfPages);

	/** Calculate the size of the user PFN array.*/
	PFNArraySize = NumberOfPages * sizeof (ULONG_PTR);
	//printf("Requesting a PFN array of %d bytes.\n", PFNArraySize);

	AllocateUserPhysicalPagesNuma(hProcess, &NumberOfPages, aPFNs, 0);

	// (aPFNs == NULL){
	//	sprintf("Failed to allocate on heap.\n"));
	//	return 0;
	//}A

	// Enable the privilege.

	// Allocate the physical memory.
	NumberOfPagesInitial = NumberOfPages;

	// Free the physical pages.

	num = GetCurrentProcessId();
	hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_TERMINATE , FALSE, num);
	//result = AllocateUserPhysicalPages(hProcess, &NumberOfPages,aPFNs );

	result = FreeUserPhysicalPages(hProcess,&NumberOfPages,aPFNs);

	if(result == TRUE){
		sprintf(msg, " FreeUserPhysicalPages() : SUCCESS \n\n This computer has page size : %d \n Requesting a PFN array of %d bytes \n ", sSysInfo.dwPageSize, PFNArraySize);
		strcpy(buf, "SUCCESS");
	}else{
		sprintf(msg, " FreeUserPhysicalPages() : FAIL \n\n <64-bit Windows on Itanium 전용 시스템> \n\n cmd 창에서 wmic cpu get architecture 입력했을 때 \n 6(means Itanium)과 9(means x64)가 출력되어야 지원함 ");
		strcpy(buf, "FAIL");
	}

	wresult(__FILE__, __LINE__, "FreeUserPhysicalPages", buf, "SUCCESS", msg);

	return result;
	
  }

/**
* SIZE_T WINAPI GetLargePageMinimum(void);
* 큰 페이지의 최소 크기를 가져옴.
* @author : 손나영
*
* @param void
* @return 큰 페이지의 최소 크기.
*/

BOOL test_GetLargePageMinimum(){

	#ifdef OQADBGPRINT
	printf("test_GetLargePageMinimum\n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ];

	BOOL result = FALSE;
	SIZE_T size = GetLargePageMinimum();
	printf("%d", size);

	if(size > 200000){ //프로서가 큰 페이지를 지원할 경우, 큰 페이지의 최소 크기를 반환. 일반적으로 2MB이상. 따라서 2MB이상일 경우 성공으로 간주. 
		sprintf(msg, " GetLargePageMinimum() : SUCCESS \n\n →minimum size of a large page : %d Byte", size);
		strcpy(buf, "SUCCESS");
		result = TRUE;

	}else if(0 < size && size <= 200000){
		sprintf(msg, " GetLargePageMinimum() : SUCCESS \n\n →minimum size of a large page : %d Byte \n (참고 : 최소 페이지의 크기는 다양하긴 하나, 일반적으로는 2MB이상입니다.)", size);
		strcpy(buf, "SUCCESS");
		result = TRUE;

	}else if(size == 0){
		sprintf(msg, " GetLargePageMinimum() : FAIL \n\n 이 프로세서는 large pages를 지원하지 않습니다.");
		result = FALSE;

	}else{
		sprintf(msg, " GetLargePageMinimum() : FAIL");
		result = FALSE;
	}

	wresult(__FILE__, __LINE__, "GetLargePageMinimum", buf, "SUCCESS", msg);
	return result;
}

/**
* BOOL WINAPI GetProcessMemoryInfo(
  _In_  HANDLE                   Process,
  _Out_ PPROCESS_MEMORY_COUNTERS ppsmemCounters,
  _In_  DWORD                    cb
 );
* 특정 프로세스의 메모리 사용에 대한 정보를 검색.
* @author : 손나영
* 
* @param Process 프로세스 핸들. PROCESS_QUERY_INFORMATION 또는 PROCESS_QUERY_LIMITED_INFORMATION 또는PROCESS_VM_READ 권한 필수.
* @param ppsmemCounters 프로세스의 메모리 사용에 대한 정보를 불러오는 PROCESS_MEMORY_COUNTERS 또는 PROCESS_MEMORY_COUNTERS_EX 구조체에 대한 포인터.
* @param cb ppsmemCounters의 크기. 바이트.
* @return 정보 검색 성공/실패 여부.
*/

BOOL test_K32GetProcessMemoryInfo(){

	#ifdef OQADBGPRINT
	printf("test_K32GetProcessMemoryInfo \n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ]="FAIL";
	int pid = GetCurrentProcessId();

	BOOL result = FALSE;
	HANDLE hProcess;
	
	//typedef struct _PROCESS_MEMORY_COUNTERS {
	//	DWORD  cb;
	//	DWORD  PageFaultCount;
	//	SIZE_T PeakWorkingSetSize;
	//	SIZE_T WorkingSetSize;
	//	SIZE_T QuotaPeakPagedPoolUsage;
	//	SIZE_T QuotaPagedPoolUsage;
	//	SIZE_T QuotaPeakNonPagedPoolUsage;
	//	SIZE_T QuotaNonPagedPoolUsage;
	//	SIZE_T PagefileUsage;
	//	SIZE_T PeakPagefileUsage;
	//} PROCESS_MEMORY_COUNTERS, *PPROCESS_MEMORY_COUNTERS;


	PROCESS_MEMORY_COUNTERS pmc;

	hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid );
	if (NULL == hProcess)
		return 0;

	result = GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));

	if(result != 0){
		strcpy(buf, "SUCCESS");
		sprintf(msg, " K32GetProcessMemoryInfo() : SUCCESS \n\n Process ID : %u \n PageFaultCount: 0x%08X ", pid, pmc.PageFaultCount);

		result = TRUE;
	}else{
		strcpy(buf, "FAIL");
		strcpy(msg, GetErrorMessage(" K32GetProcessMemoryInfo() : FAIL  \n\n Error Message :" , GetLastError()));

		result = FALSE;

	}
	wresult(__FILE__, __LINE__, "K32GetProcessMemoryInfo", buf, "SUCCESS", msg);
	/**
		printf( "\tPageFaultCount: 0x%08X\n", pmc.PageFaultCount );
		printf( "\tPeakWorkingSetSize: 0x%08X\n", pmc.PeakWorkingSetSize );
		printf( "\tWorkingSetSize: 0x%08X\n", pmc.WorkingSetSize );
		printf( "\tQuotaPeakPagedPoolUsage: 0x%08X\n", pmc.QuotaPeakPagedPoolUsage );
		printf( "\tQuotaPagedPoolUsage: 0x%08X\n", pmc.QuotaPagedPoolUsage );
		printf( "\tQuotaPeakNonPagedPoolUsage: 0x%08X\n", pmc.QuotaPeakNonPagedPoolUsage );
		printf( "\tQuotaNonPagedPoolUsage: 0x%08X\n", pmc.QuotaNonPagedPoolUsage );
		printf( "\tPagefileUsage: 0x%08X\n", pmc.PagefileUsage ); 
		printf( "\tPeakPagefileUsage: 0x%08X\n", pmc.PeakPagefileUsage );
	*/

	CloseHandle(hProcess);

	return result;
}


/**
* BOOL WINAPI MapUserPhysicalPages(
  _In_ PVOID      lpAddress,
  _In_ ULONG_PTR  NumberOfPages,
  _In_ PULONG_PTR UserPfnArray
  );
* Itanium 기반 시스템의 64 비트 Windows
* 전에 할당 된 실제 메모리 페이지를 AWE ( Address Windowing Extensions ) 영역 의 지정된 주소에 매핑
* @author : 손나영
*
* @param lpAddress 재맵핑 할 메모리 영역의 시작 주소에 대한 포인터.
* @param NumberOfPages 페이지를 변환 할 실제 메모리 및 가상 주소 공간의 크기.
* @param UserPfnArray 물리적 페이지 프레임 번호의 배열에 대한 포인터. NULL이면 지정된 주소 범위가 매핑 해제됨. 실제 페이지 해제하려면 FreeUserPhysicalPages
* @return 매핑 성공/실패 여부.
*/

BOOL test_MapUserPhysicalPages(){

	#ifdef OQADBGPRINT
	printf("test_MapUserPhysicalPages\n");
	#endif

	BOOL result = FALSE;                   // generic Boolean value
	ULONG_PTR NumberOfPages;        // number of pages to request
	ULONG_PTR NumberOfPagesInitial; // initial number of pages requested
	ULONG_PTR *aPFNs;               // page info; holds opaque data
	PVOID lpMemReserved;            // AWE window
	SYSTEM_INFO sSysInfo;           // useful system information

	int PFNArraySize;               // memory to request for PFN array
	char buf[BUFSIZ];
	char msg[BUFSIZ]="FAIL";
	
	GetSystemInfo(&sSysInfo);  // fill the system information structure
	//_tprintf(_T("This computer has page size %d.\n"), sSysInfo.dwPageSize);

	// Calculate the number of pages of memory to request.

	NumberOfPages = MEMORY_REQUESTED/sSysInfo.dwPageSize;
	//_tprintf (_T("Requesting %d pages of memory.\n"), NumberOfPages);

	// Calculate the size of the user PFN array.

	PFNArraySize = NumberOfPages * sizeof (ULONG_PTR);
	//_tprintf (_T("Requesting a PFN array of %d bytes.\n"), PFNArraySize);

	aPFNs = (ULONG_PTR *) HeapAlloc(GetProcessHeap(), 0, PFNArraySize);
	NumberOfPagesInitial = NumberOfPages;
	lpMemReserved = VirtualAlloc( NULL,MEMORY_REQUESTED,MEM_RESERVE | MEM_PHYSICAL,PAGE_READWRITE );

	if(lpMemReserved == NULL){
		#ifdef OQADBG
		MessageBox(hWnd, L"Cannot reserve memory", L"fail", MB_OK);
		#endif
	}

	result = MapUserPhysicalPages(lpMemReserved,NumberOfPages,aPFNs);

	if(result == TRUE){
		sprintf(msg, " MapUserPhysicalPages() : SUCCESS \n\n This computer has page size : %d \n Requesting a PFN array of %d bytes \n ", sSysInfo.dwPageSize, PFNArraySize);
		strcpy(buf, "SUCCESS");
		
	}else{
		sprintf(msg, " MapUserPhysicalPages() : FAIL \n\n <64-bit Windows on Itanium 전용 시스템> \n\n cmd 창에서 wmic cpu get architecture 입력했을 때 \n 6(means Itanium)과 9(means x64)가 출력되어야 지원함 ");
		strcpy(buf, "FAIL");
	}

	wresult(__FILE__, __LINE__, "MapUserPhysicalPages", buf, "SUCCESS", msg);

	return result;
}


/**
* BOOL WINAPI RemoveSecureMemoryCacheCallback(
  _In_ PSECURE_MEMORY_CACHE_CALLBACK pfnCallBack
 );
* 이전에 AddSecureMemoryCacheCallback 함수로 등록된 콜백 함수의 등록을 취소.
* @author : 손나영
*
* @param pfnCallBack 제거 할 응용 프로그램 정의 SecureMemoryCacheCallback 함수에 대한 포인터
* @return
*/

BOOL test_RemoveSecureMemoryCacheCallback(){

	#ifdef OQADBGPRINT
	printf("test_RemoveSecureMemoryCacheCallback \n");
	#endif

	char msg[BUFSIZ];
	char buf[BUFSIZ] = "FAIL";
	
	PSECURE_MEMORY_CACHE_CALLBACK pfnCallBack = NULL;

	// 보안 메모리 범위가 해제되거나 보호가 변경될 때 호출되는 콜백 함수를 등록
	// BOOLEAN CALLBACK SecureMemoryCacheCallback(PVOID Addr, SIZE_T Range)
	DWORD err = GetLastError();
	BOOL result = AddSecureMemoryCacheCallback(SecureMemoryCacheCallback);

	if(result == TRUE){

		result = RemoveSecureMemoryCacheCallback(SecureMemoryCacheCallback);
			if(result == TRUE){
				strcpy(buf, "SUCCESS");
				sprintf(msg, "RemoveSecureMemoryCacheCallback() : SUCCESS");
			}else
				sprintf(msg, "RemoveSecureMemoryCacheCallback() 실패 \n\nError Code : %d", err);
	
	}else{
		sprintf(msg, " RemoveSecureMemoryCacheCallback() : FAIL \n\n ");
		result = FALSE;
	}

	wresult(__FILE__, __LINE__, "RemoveSecureMemoryCacheCallback", buf, "SUCCESS", msg);

	return result;
}


/**
* BOOL WINAPI Toolhelp32ReadProcessMemory(
  _In_  DWORD   th32ProcessID,
  _In_  LPCVOID lpBaseAddress,
  _Out_ LPVOID  lpBuffer,
  _In_  SIZE_T  cbRead,
  _Out_ SIZE_T  lpNumberOfBytesRead
 );
* 다른 프로세스에 할당 된 메모리를 응용 프로그램 제공 버퍼로 복사
* @author : 손나영
*
* @param th32ProcessID 메모리가 복사되고있는 프로세스의 식별자. 이 매개 변수는 현재 프로세스의 메모리를 복사하기 위해 0 일 수 있음,
* @param lpBaseAddress 읽을 특정 프로세스의 기본 주소.
* @param lpBuffer 지정된 프로세스의 주소 공간 내용을 수신하는 버퍼에 대한 포인터.
* @param cbRead 지정된 프로세스에서 읽을 바이트 수.
* @param lpNumberOfBytesRead
* @return 지정된 버퍼에 복사 된 바이트 수
*/

// process id로 process의 memory 읽기. ReadProcessMemory의 편리한 버전
BOOL test_Toolhelp32ReadProcessMemory(){

	#ifdef OQADBGPRINT
	printf("test_Toolhelp32ReadProcessMemory\n");
	#endif

	char msg[BUFSIZ];
	char buf[BUFSIZ] = "FAIL";
	
	BOOL result = FALSE;
	CHAR buffer[100];
	LONGLONG addr = 0x04d2; //1234
	DWORD pid = GetCurrentProcessId();
	
	//GetModuleHandle : 지정된 모듈에 대한 핸들 가져옴
	result = Toolhelp32ReadProcessMemory(pid, GetModuleHandle(NULL), &buffer, 100, 0);
	//result = ReadProcessMemory(hProcess, (LPCVOID)addr, &buffer, 100, 0);
	//result = WriteProcessMemory(hProcess, (LPVOID)addr, &buffer, 100, 0);

	int err = GetLastError();

	//if(result == FALSE){ //오류가 발생하면 0을 반환하도록 보장됨. 성공의 경우 다른 것을 반환할 수 있음. 그러니까 FALSE로 비교
	if(result == TRUE){
		strcpy(buf, "SUCCESS");
		sprintf(msg, "Toolhelp32ReadProcessMemory() : SUCCESS");
	}else{
		strcpy(msg, GetErrorMessage(" Toolhelp32ReadProcessMemory() : FAIL  \n\n Error  :" , GetLastError()));
		result = FALSE;
	}

	wresult(__FILE__, __LINE__, "Toolhelp32ReadProcessMemory", buf, "SUCCESS", msg);
	return result;
}


/**
* LPVOID WINAPI VirtualAllocExNuma(
  _In_     HANDLE hProcess,
  _In_opt_ LPVOID lpAddress,
  _In_     SIZE_T dwSize,
  _In_     DWORD  flAllocationType,
  _In_     DWORD  flProtect,
  _In_     DWORD  nndPreferred
  );
* 지정된 프로세스의 가상 주소 공간에서 메모리 영역의 상태를 예약, 커밋 또는 변경하고 실제 메모리에 대한 NUMA 노드를 지정
* @author : 손나영
*
* @param hProcess 프로세스 핸들.
* @param lpAddress 할당 할 페이지 영역에 대해 원하는 시작 주소를 지정하는 포인터
* @param dwSize 할당 할 메모리 영역의 크기 (바이트).
* @param flAllocationType 메모리 할당 유형. 4가지.
* @param flProtect 할당 할 페이지 영역에 대한 메모리 보호
* @param nndPreferred 물리적 메모리가 있어야하는 NUMA 노드
* @return 지정 성공/실패 여부.
*/

/**
	예비 또는 지정된 process의 가상 주소 공간에 메모리 영역을 commit하고,
	물리적 메모리의 NUMA 노드를 지정
*/
//#define _WIN32_WINNT 0x0602
BOOL test_VirtualAllocExNuma(){

	#ifdef OQADBGPRINT
	printf("test_VirtualAllocExNuma\n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ]="FAIL";

	DWORD  PageSize;
	ULONG HighestNodeNumber;
	ULONG NumberOfProcessors;
	PVOID* Buffers = NULL;
	SIZE_T AllocationSize = 0;
	BOOL result = FALSE;

	if(AllocationSize == 0){
		AllocationSize = 16*1024*1024;
	}

	// processor와 시스템 페이지 사이즈를 가져옴

	SYSTEM_INFO SystemInfo;
	GetSystemInfo (&SystemInfo);
	NumberOfProcessors = SystemInfo.dwNumberOfProcessors;
	PageSize = SystemInfo.dwPageSize;

	// 가장 높은 노드 번호를 가져옴
	if (!GetNumaHighestNodeNumber(&HighestNodeNumber)){
		// printf("GetNumaHighestNodeNumber failed: %d\n", GetLastError());
	}

	if(HighestNodeNumber == 0){
		// printf("Not a NUMA system - exiting");

	}

	// Allocate array of pointers to memory blocks.
	Buffers = (PVOID*) malloc (sizeof(PVOID)*NumberOfProcessors);

	if (Buffers == NULL){
		//		printf("Allocating array of buffers failed");
	}
	ZeroMemory (Buffers, sizeof(PVOID)*NumberOfProcessors);

	UCHAR i = 0;
	UCHAR NodeNumber;

	if(!GetNumaProcessorNode(i, &NodeNumber)){
		// printf("GetNumaProcessorNode failed: %d\n", GetLastError());

	}

	DWORD num = GetCurrentProcessId();
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_TERMINATE , FALSE, num);

	/**
		commit하고 물리적 메모리의 NUMA 노드를 지정
		VirtualAllocExNuma(hProces, NULL:영역을 할당할 위치를 결정, →:다음 페이지 경계까지 반올림, 메모리 타입 할당:가상 주고 공간 예약|커밋, 
						   Memory Protection Constants:읽기쓰기 활성화, 실제 메모리가 상주해야하는 NUMA 노드)
	*/
	PCHAR Buffer = (PCHAR)VirtualAllocExNuma(hProcess,NULL,AllocationSize,MEM_RESERVE | MEM_COMMIT,PAGE_READWRITE,NodeNumber);

	if(Buffer == NULL){
		strcpy(buf, "FAIL");
		sprintf(msg, "VirtualAllocExNuma() : FAIL \n\n Error : %d \n node number%u\n", GetLastError(), NodeNumber);

	}else{ //성공
		strcpy(msg, " VirtualAllocExNuma() : SUCCESS");
		strcpy(buf, "SUCCESS");
		result = TRUE;
	}

	wresult(__FILE__, __LINE__, "GetFinalPathNameByHandle", buf, "SUCCESS", msg);

	return result;
}


/**
* HRESULT WINAPI WerRegisterMemoryBlock(
  _In_ PVOID pvAddress,
  _In_ DWORD dwSize
  );
* WER에서 오류 보고서를 만들 때 수집 할 메모리 블록을 등록
* @author : 손나영
* 
* @param pvAddress 메모리 블록의 시작 주소.
* @param dwSize 메모리 블록의 크기 (바이트). 최대는 WER_MAX_MEM_BLOCK_SIZE 바이트.
* @return 등록 성공 시 S_OK.
*/


#define WER_MAX_MEM_BLOCK_SIZE (64 * 1024)
BOOL test_WerRegisterMemoryBlock(){

	#ifdef OQADBGPRINT
	printf("test_WerRegisterMemoryBlock\n");
	#endif

	int address = 0x0001;
	char buf[BUFSIZ];
	char msg[BUFSIZ]="FAIL";

	PVOID pv = &address;
	HRESULT result = WerRegisterMemoryBlock(&pv, WER_MAX_MEM_BLOCK_SIZE);

	if(result == S_OK){
		strcpy(buf, "SUCCESS");
		strcpy(msg, " WerRegisterMemoryBlock() : SUCCESS \n\n WER에서 error report를 만들때 수집하기 위한 memory block을 등록했습니다.");
		result = TRUE;

	}else{
		strcpy(buf, "FAIL");
		strcpy(msg, GetErrorMessage(" WerRegisterMemoryBlock() : FAIL  \n\n Error Message :" , GetLastError()));
		result = FALSE;
	}

	wresult(__FILE__, __LINE__, "WerRegisterMemoryBlock", buf, "SUCCESS", msg);
	return result;
}


/**
* HRESULT WINAPI WerUnregisterMemoryBlock(
  _In_ PVOID pvAddress
  );
* 응용 프로그램의 오류보고 중 수집 할 데이터 목록에서 메모리 블록을 제거
* @author : 손나영 
*
* @param pvAddress 메모리 블록의 시작 주소. 메모리 블록은 WerRegisterMemoryBlock 함수를 사용하여 등록되어 있어야 함.
* @return 제거 성공 시 S_OK.
*/

BOOL test_WerUnregisterMemoryBlock(){

	#ifdef OQADBGPRINT
	printf("test_WerUnregisterMemoryBlock\n");
	#endif

	int address = 0x0001;
	char buf[BUFSIZ];
	char msg[BUFSIZ]="FAIL";

	PVOID pv = &address;
	HRESULT result = WerRegisterMemoryBlock(&pv, WER_MAX_MEM_BLOCK_SIZE);
	if(result == S_OK){
		result = WerUnregisterMemoryBlock(&pv);

		if(result == S_OK){
			strcpy(buf, "SUCCESS");
			strcpy(msg, " WerUnregisterMemoryBlock() : SUCCESS \n\n WER에서 error report를 만들때 수집하기 위한 memory block을 삭제했습니다.");
		}else{
			strcpy(buf, "FAIL");
			strcpy(msg, GetErrorMessage(" WerUnregisterMemoryBlock() : FAIL  \n\n Error Message :" , GetLastError()));
		}
	}else{
		strcpy(buf, "FAIL");
		strcpy(msg, GetErrorMessage(" WerRegisterMemoryBlock() : FAIL  \n\n  WerRegisterMemoryBlock부터 다시 하십시오.Error Message :" , GetLastError()));
	}
	wresult(__FILE__, __LINE__, "WerUnregisterMemoryBlock", buf, "SUCCESS", msg);

	return true;
}
/**
BOOL test_AllocateUserPhysicalPagesNuma(){

	SYSTEM_INFO siSysInfo;

	GetSystemInfo(&siSysInfo);

	printf("Hardware information: \n");  
	printf("OEM ID: %u\n", siSysInfo.dwOemId);
	printf("Number of processors: %u\n", siSysInfo.dwNumberOfProcessors); 
	printf("Page size: %u\n", siSysInfo.dwPageSize); 
	printf("Processor type: %u\n", siSysInfo.dwProcessorType); 
	printf("Minimum application address: %lx\n", siSysInfo.lpMinimumApplicationAddress); 
	printf("Maximum application address: %lx\n", siSysInfo.lpMaximumApplicationAddress); 
	printf("Active processor mask: %u\n", siSysInfo.dwActiveProcessorMask); 

#define MEMORY_REQUESTED 1024*1024


	BOOL result;                   // generic Boolean value
	ULONG_PTR NumberOfPages;        // number of pages to request
	ULONG_PTR NumberOfPagesInitial; // initial number of pages requested
	ULONG_PTR *aPFNs;               // page info; holds opaque data
	SYSTEM_INFO sSysInfo;           // useful system information

	int PFNArraySize;  
	char buf[BUFSIZ];
	char msg[BUFSIZ]="FAIL";
	
	GetSystemInfo(&sSysInfo);  // fill the system information structure

	NumberOfPages = MEMORY_REQUESTED/sSysInfo.dwPageSize;
	PFNArraySize = NumberOfPages * sizeof (ULONG_PTR);
	aPFNs = (ULONG_PTR *) HeapAlloc(GetProcessHeap(), 0, PFNArraySize);

	NumberOfPagesInitial = NumberOfPages;

	DWORD nnddPreferred = 




	return true;
}

**/








//이언봉
BOOL test_GetNumaProximityNode(){
	char passmsg[100];
	char failmsg[100];
	BOOL result = TRUE;
	UCHAR NodeNumber;
	
	result = GetNumaProximityNode(0, &NodeNumber);
	if (result==FALSE){
		strcpy(failmsg, GetErrorMessage("GetNumaProximityNode() 실패 :", GetLastError()));
		wresult(__FILE__,__LINE__, "GetNumaProximityNode", "fail", "pass", failmsg );
		result = FALSE;
	}
	
	else{
		sprintf(passmsg, "GetNumaProximityNode() 성공. 결과 값은 %d", result);
		wresult(__FILE__,__LINE__, "GetNumaProximityNode", "pass", "pass", passmsg );
	}
	return result;
	
}

BOOL test_GetNumaProximityNodeEx(){
	char passmsg[100];
	char failmsg[100];
	BOOL result = TRUE;
	USHORT NodeNumber;
	
	result = GetNumaProximityNodeEx(0, &NodeNumber);
	if (result==0){
		strcpy(failmsg, GetErrorMessage("GetNumaProximityNodeEx() 실패 :", GetLastError()));
		wresult(__FILE__,__LINE__, "GetNumaProximityNodeEx", "fail", "pass", failmsg );
		result = FALSE;
	}
	
	else{
		sprintf(passmsg, "GetNumaProximityNodeEx() 성공. 결과 값은 %d", result);
		wresult(__FILE__,__LINE__, "GetNumaProximityNodeEx", "pass", "pass", passmsg );
	}
	return result;
}