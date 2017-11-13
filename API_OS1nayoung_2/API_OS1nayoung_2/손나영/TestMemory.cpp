#include "TestMemory.h"
#include <WERAPI.H>
#include <Psapi.h>
#include <TlHelp32.h>

/**
	AllocateUserPhysicalPages() : 지정된 프로세스의 AWE(Address Windowing Extensions) 영역 내에서 매핑 및 매핑 해제 할 물리적 메모리 페이지를 할당
	// 페이지 크기의 차이로 인해 32 비트 응용 프로그램에서는 불가
	func(HANDLE hProcess, The size of the physical memory to allocate in paes→GetSystemInfo, PfnArray)
*/
#define MEMORY_REQUESTED 1024*1024
BOOL test_AllocateUserPhysicalPages(){

	#ifdef OQADBGPRINT
	printf("test_AllocateUserPhysicalPages\n");
	#endif

	BOOL result;                   // generic Boolean value
	ULONG_PTR NumberOfPages;        // number of pages to request
	ULONG_PTR NumberOfPagesInitial; // initial number of pages requested
	ULONG_PTR *aPFNs;               // page info; holds opaque data
	SYSTEM_INFO sSysInfo;           // useful system information

	int PFNArraySize;  
	char buf[BUFSIZ];
	char meg[BUFSIZ]="FAIL";
	
	GetSystemInfo(&sSysInfo);  // fill the system information structure

	NumberOfPages = MEMORY_REQUESTED/sSysInfo.dwPageSize;
	PFNArraySize = NumberOfPages * sizeof (ULONG_PTR);
	aPFNs = (ULONG_PTR *) HeapAlloc(GetProcessHeap(), 0, PFNArraySize);

	NumberOfPagesInitial = NumberOfPages;

	//HANDLE hProcess = GetCurrentProcess();
	//HANDLE h = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_TERMINATE,FALSE, pid);

	DWORD num = GetCurrentProcessId();

	/**	PROCESS_QUERY_INFORMATION : access right(security)
		FALSE : process do not inherit this handle	
		num : GetCurrentProcessId()		*/
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_TERMINATE , FALSE, num);

	//result = AllocateUserPhysicalPages(hProcess, &NumberOfPages,aPFNs);
	result = AllocateUserPhysicalPages(GetCurrentProcess(), &NumberOfPages, aPFNs);

	if(result == TRUE ){
		sprintf(meg, " AllocateUserPhysicalPages() : SUCCESS \n\n This computer has page size : %d \n Requesting a PFN array of %d bytes \n ", sSysInfo.dwPageSize, PFNArraySize);
		strcpy(buf, "SUCCESS");
	}else {
		strcpy(meg, GetErrorMessage(" AllocateUserPhysicalPages() : FAIL \n\n <64-bit Windows on Itanium 전용 시스템>\n\n cmd 창에서 wmic cpu get architecture 입력했을 때 \n 6(means Itanium)과 9(means x64)가 출력되어야 지원함 \n\n Error Message :" , GetLastError()));
		strcpy(buf, "FAIL");
	}
	if(NumberOfPagesInitial != NumberOfPages) {
		//printf("numberofpagesinitial function is 
		//printf(("Allocated only %p pages.\n"), NumberOfPages );
		return 0;
	}
	wresult(__FILE__, __LINE__, "AllocateUserPhysicalPages", buf, "SUCCESS", meg);

	return result;
}


BOOL test_AllocateUserPhysicalPagesNuma(){
	
	int PFNArraySize;
	char buf[BUFSIZ];
	char meg[BUFSIZ]="FAIL";
	
	BOOL result;
	ULONG_PTR *aPFNs;
	SYSTEM_INFO sSysInfo;
	ULONG_PTR NumberOfPages;

	//할당할 실제 메모리의 크기
	//출력 시 매개변수가 실제 할당된 페이지 수를 수신함. 요청된 수보다 적을 수 있음.
	NumberOfPages = MEMORY_REQUESTED/sSysInfo.dwPageSize;
	PFNArraySize = NumberOfPages * sizeof(ULONG_PTR);

	//할당된 메모리의 페이지 프레임 번호 저장하는 배열에 대한 포인터
	//최소한 ULONG_PTR데이터 형식의 NumberOfPages배 이상이어야 함.
	aPFNs = (ULONG_PTR *)HeapAlloc(GetProcessHeap(), 0, PFNArraySize);

	result = AllocateUserPhysicalPagesNuma(GetCurrentProcess(), &NumberOfPages, aPFNs, 0);

	if(result != FALSE){
		strcpy(buf, "SUCCESS");
		strcpy(meg, " AllocateUserPhysicalPagesNuma() : SUCCESS");
	}else{
		strcpy(buf, "FAIL");
		strcpy(meg, GetErrorMessage(" AllocateUserPhysicalPagesNuma() : FAIL  \n\n Error Message :" , GetLastError()));
	}
	wresult(__FILE__, __LINE__, "AllocateUserPhysicalPagesNuma", buf, "SUCCESS", meg);

	return true;
}


BOOL test_FreeUserPhysicalPages(){

	#ifdef OQADBGPRINT
	printf("test_FreeUserPhysicalPages\n");
	#endif

	BOOL result;                   // generic Boolean value
	ULONG_PTR NumberOfPages;        // number of pages to request
	ULONG_PTR NumberOfPagesInitial; // initial number of pages requested
	ULONG_PTR *aPFNs;               // page info; holds opaque data
	SYSTEM_INFO sSysInfo;           // useful system information

	int PFNArraySize;               // memory to request for PFN array
	char buf[BUFSIZ];
	char meg[BUFSIZ]="FAIL";

	GetSystemInfo(&sSysInfo);  // fill the system information structure

	//printf("This computer has page size %d.\n", sSysInfo.dwPageSize);

	/** Calculate the number of pages of memory to request.*/
	NumberOfPages = MEMORY_REQUESTED/sSysInfo.dwPageSize;
	//printf("Requesting %d pages of memory.\n", NumberOfPages);

	/** Calculate the size of the user PFN array.*/
	PFNArraySize = NumberOfPages * sizeof (ULONG_PTR);
	//printf("Requesting a PFN array of %d bytes.\n", PFNArraySize);

	aPFNs = (ULONG_PTR *) HeapAlloc(GetProcessHeap(), 0, PFNArraySize);

	// (aPFNs == NULL){
	//	sprintf("Failed to allocate on heap.\n"));
	//	return 0;
	//}

	// Enable the privilege.

	// Allocate the physical memory.
	NumberOfPagesInitial = NumberOfPages;

	// Free the physical pages.

	DWORD num = GetCurrentProcessId();
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_TERMINATE , FALSE, num);
	//result = AllocateUserPhysicalPages(hProcess, &NumberOfPages,aPFNs );

	result = FreeUserPhysicalPages(hProcess,&NumberOfPages,aPFNs);

	if(result == TRUE){
		sprintf(meg, " AllocateUserPhysicalPages() : SUCCESS \n\n This computer has page size : %d \n Requesting a PFN array of %d bytes \n ", sSysInfo.dwPageSize, PFNArraySize);
		strcpy(buf, "SUCCESS");
	}else{
		sprintf(meg, " FreeUserPhysicalPages() : FAIL \n\n <64-bit Windows on Itanium 전용 시스템> \n\n cmd 창에서 wmic cpu get architecture 입력했을 때 \n 6(means Itanium)과 9(means x64)가 출력되어야 지원함 ");
		strcpy(buf, "FAIL");
	}

	wresult(__FILE__, __LINE__, "FreeUserPhysicalPages", buf, "SUCCESS", meg);

	return true;
	
  }

// 매핑 해는 MapUserPhysicalPagesScatter
BOOL test_MapUserPhysicalPages(){

	#ifdef OQADBGPRINT
	printf("test_MapUserPhysicalPages\n");
	#endif

	BOOL result;                   // generic Boolean value
	ULONG_PTR NumberOfPages;        // number of pages to request
	ULONG_PTR NumberOfPagesInitial; // initial number of pages requested
	ULONG_PTR *aPFNs;               // page info; holds opaque data
	PVOID lpMemReserved;            // AWE window
	SYSTEM_INFO sSysInfo;           // useful system information

	int PFNArraySize;               // memory to request for PFN array
	char buf[BUFSIZ];
	char meg[BUFSIZ]="FAIL";
	
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
		sprintf(meg, " MapUserPhysicalPages() : SUCCESS \n\n This computer has page size : %d \n Requesting a PFN array of %d bytes \n ", sSysInfo.dwPageSize, PFNArraySize);
		strcpy(buf, "SUCCESS");
	}else{
		sprintf(meg, " MapUserPhysicalPages() : FAIL \n\n <64-bit Windows on Itanium 전용 시스템> \n\n cmd 창에서 wmic cpu get architecture 입력했을 때 \n 6(means Itanium)과 9(means x64)가 출력되어야 지원함 ");
		strcpy(buf, "FAIL");
	}

	wresult(__FILE__, __LINE__, "MapUserPhysicalPages", buf, "SUCCESS", meg);

	return true;
}

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
	char meg[BUFSIZ]="FAIL";

	DWORD  PageSize;
	ULONG HighestNodeNumber;
	ULONG NumberOfProcessors;
	PVOID* Buffers = NULL;
	SIZE_T AllocationSize = 0;

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
		sprintf(meg, "VirtualAllocExNuma() : FAIL \n\n Error : %d \n node number%u\n", GetLastError(), NodeNumber);

	}else{ //성공
		strcpy(meg, " VirtualAllocExNuma() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}

	wresult(__FILE__, __LINE__, "GetFinalPathNameByHandle", buf, "SUCCESS", meg);

	return true;
}


#define WER_MAX_MEM_BLOCK_SIZE (64 * 1024)
BOOL test_WerRegisterMemoryBlock(){

	#ifdef OQADBGPRINT
	printf("test_WerRegisterMemoryBlock\n");
	#endif

	int address = 0x0001;
	char buf[BUFSIZ];
	char meg[BUFSIZ]="FAIL";

	PVOID pv = &address;
	HRESULT result = WerRegisterMemoryBlock(&pv, WER_MAX_MEM_BLOCK_SIZE);

	if(result == S_OK){
		strcpy(buf, "SUCCESS");
		strcpy(meg, " WerRegisterMemoryBlock() : SUCCESS \n\n WER에서 error report를 만들때 수집하기 위한 memory block을 등록했습니다.");
	}else{
		strcpy(buf, "FAIL");
		strcpy(meg, GetErrorMessage(" WerRegisterMemoryBlock() : FAIL  \n\n Error Message :" , GetLastError()));
	}

	wresult(__FILE__, __LINE__, "WerRegisterMemoryBlock", buf, "SUCCESS", meg);

	return true;
}

BOOL test_WerUnregisterMemoryBlock(){

	#ifdef OQADBGPRINT
	printf("test_WerUnregisterMemoryBlock\n");
	#endif

	int address = 0x0001;
	char buf[BUFSIZ];
	char meg[BUFSIZ]="FAIL";

	PVOID pv = &address;
	HRESULT result = WerRegisterMemoryBlock(&pv, WER_MAX_MEM_BLOCK_SIZE);
	if(result == S_OK){
		result = WerUnregisterMemoryBlock(&pv);

		if(result == S_OK){
			strcpy(buf, "SUCCESS");
			strcpy(meg, " WerUnregisterMemoryBlock() : SUCCESS \n\n WER에서 error report를 만들때 수집하기 위한 memory block을 삭제했습니다.");
		}else{
			strcpy(buf, "FAIL");
			strcpy(meg, GetErrorMessage(" WerUnregisterMemoryBlock() : FAIL  \n\n Error Message :" , GetLastError()));
		}
	}else{
		strcpy(buf, "FAIL");
		strcpy(meg, GetErrorMessage(" WerRegisterMemoryBlock() : FAIL  \n\n  WerRegisterMemoryBlock부터 다시 하십시오.Error Message :" , GetLastError()));
	}
	wresult(__FILE__, __LINE__, "WerUnregisterMemoryBlock", buf, "SUCCESS", meg);

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
	char meg[BUFSIZ]="FAIL";
	
	GetSystemInfo(&sSysInfo);  // fill the system information structure

	NumberOfPages = MEMORY_REQUESTED/sSysInfo.dwPageSize;
	PFNArraySize = NumberOfPages * sizeof (ULONG_PTR);
	aPFNs = (ULONG_PTR *) HeapAlloc(GetProcessHeap(), 0, PFNArraySize);

	NumberOfPagesInitial = NumberOfPages;

	DWORD nnddPreferred = 




	return true;
}

**/


/**
	특정 프로세스의 메모리 사용에 대한 정보를 검색	
*/
BOOL test_K32GetProcessMemoryInfo(){

	#ifdef OQADBGPRINT
	printf("test_K32GetProcessMemoryInfo\n");
	#endif

	char buf[BUFSIZ];
	char meg[BUFSIZ]="FAIL";

	int result;
	int pid = GetCurrentProcessId();

	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc;

	hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid );
	if (NULL == hProcess)
		return 0;

	result = GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));

	if(result != 0){
		strcpy(buf, "SUCCESS");
		sprintf(meg, " K32GetProcessMemoryInfo() : SUCCESS \n\n Process ID : %u \n PageFaultCount: 0x%08X ", pid, pmc.PageFaultCount);
	}else{
		strcpy(buf, "FAIL");
		strcpy(meg, GetErrorMessage(" K32GetProcessMemoryInfo() : FAIL  \n\n Error Message :" , GetLastError()));
	}
	wresult(__FILE__, __LINE__, "K32GetProcessMemoryInfo", buf, "SUCCESS", meg);
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

	CloseHandle( hProcess );

	return true;
}

BOOL test_GetLargePageMinimum(){

	#ifdef OQADBGPRINT
	printf("test_GetLargePageMinimum\n");
	#endif

	char buf[BUFSIZ];
	char meg[BUFSIZ];

	SIZE_T size = GetLargePageMinimum();
	printf("%d", size);

	if(size != 0){
		sprintf(meg, " GetLargePageMinimum() : SUCCESS \n\n →minimum size of a large page : %d Byte", size);
		strcpy(buf, "SUCCESS");
	}else{
		sprintf(meg, " GetLargePageMinimum() : FAIL \n\n 이 프로세서는 large pages를 지원하지 않습니다.");
	}

	wresult(__FILE__, __LINE__, "GetLargePageMinimum", buf, "SUCCESS", meg);

	return true;
}

BOOL test_AddSecureMemoryCacheCallback(){
	
	#ifdef OQADBGPRINT
	printf("test_AddSecureMemoryCacheCallback\n");
	#endif

	char buf[BUFSIZ];
	char meg[BUFSIZ];

	PSECURE_MEMORY_CACHE_CALLBACK pfnCallBack = NULL;

	// 보안 메모리 범위가 해제되거나 보호가 변경될 때 호출되는 콜백 함수를 등록
	// BOOLEAN CALLBACK SecureMemoryCacheCallback(PVOID Addr, SIZE_T Range)
	BOOL result = AddSecureMemoryCacheCallback(pfnCallBack);

	if(result == TRUE){
		sprintf(meg, " AddSecureMemoryCacheCallback() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}else{
		sprintf(meg, " AddSecureMemoryCacheCallback() : FAIL \n\n ");

		result = FALSE;
	}
	
	// AddSecureMemoryCacheCallback함수로 등록된 콜백 함수의 등록을 취소
	result = RemoveSecureMemoryCacheCallback(pfnCallBack);

	if(result == FALSE)

	AddSecureMemoryCacheCallback(pfnCallBack);

	wresult(__FILE__, __LINE__, "GetLargePageMinimum", buf, "SUCCESS", meg);

	return result;
}

BOOL test_RemoveSecureMemoryCacheCallback(){

	#ifdef OQADBGPRINT
	printf("test_RemoveSecureMemoryCacheCallback\n");
	#endif

	char meg[BUFSIZ];
	char buf[BUFSIZ] = "FAIL";
	
	PSECURE_MEMORY_CACHE_CALLBACK pfnCallBack = NULL;

	// 보안 메모리 범위가 해제되거나 보호가 변경될 때 호출되는 콜백 함수를 등록
	// BOOLEAN CALLBACK SecureMemoryCacheCallback(PVOID Addr, SIZE_T Range)
	DWORD err = GetLastError();
	BOOL result = AddSecureMemoryCacheCallback(pfnCallBack);

	if(result == TRUE){

		result = RemoveSecureMemoryCacheCallback(pfnCallBack);
			if(result == TRUE){
				strcpy(buf, "SUCCESS");
				sprintf(meg, "RemoveSecureMemoryCacheCallback() : SUCCESS");
			}else
				sprintf(meg, "RemoveSecureMemoryCacheCallback() 실패 \n\nError Code : %d", err);
	
	}else{
		sprintf(meg, " RemoveSecureMemoryCacheCallback() : FAIL \n\n ");
		result = FALSE;
	}

	wresult(__FILE__, __LINE__, "RemoveSecureMemoryCacheCallback", buf, "SUCCESS", meg);

	return result;
}

// process id로 process의 memory 읽기. ReadProcessMemory의 편리한 버전
BOOL test_Toolhelp32ReadProcessMemory(){

	DWORD pid = GetCurrentProcessId();
	
	//HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, pid);

	LONGLONG addr = 0x04d2; //1234
	CHAR buffer[100];
	SIZE_T bytesRead;

	BOOL result;

	char meg[BUFSIZ];
	char buf[BUFSIZ] = "FAIL";

	//GetModuleHandle : 지정된 모듈에 대한 핸들 검색
	result = Toolhelp32ReadProcessMemory(pid, GetModuleHandle(NULL), &buffer, 100, 0);
	//result = ReadProcessMemory(hProcess, (LPCVOID)addr, &buffer, 100, 0);
	//result = WriteProcessMemory(hProcess, (LPVOID)addr, &buffer, 100, 0);

	int err = GetLastError();
	//if(result == FALSE){ //오류가 발생하면 0을 반환하도록 보장됨. 성공의 경우 다른 것을 반환할 수 있음. 그러니까 FALSE로 비교
	if(result == TRUE){
		strcpy(buf, "SUCCESS");
		sprintf(meg, "Toolhelp32ReadProcessMemory() : SUCCESS");
	}else{
		strcpy(meg, GetErrorMessage(" Toolhelp32ReadProcessMemory() : FAIL  \n\n Error Message :" , GetLastError()));
		result = FALSE;
	}

	wresult(__FILE__, __LINE__, "Toolhelp32ReadProcessMemory", buf, "SUCCESS", meg);

	return true;
}

//이언봉
BOOL test_GetNumaProximityNode(){
	char passmsg[100];
	char failmsg[100];
	BOOL result = 0;
	UCHAR NodeNumber;
	
	result = GetNumaProximityNode(0, &NodeNumber);
	if (result==0){
		strcpy(failmsg, GetErrorMessage("GetNumaProximityNode() 실패 :", GetLastError()));
		wresult(__FILE__,__LINE__, "GetNumaProximityNode", "fail", "pass", failmsg );
		return FALSE;
	}
	
	else{
		sprintf(passmsg, "GetNumaProximityNode() 성공. 결과 값은 %d", result);
		wresult(__FILE__,__LINE__, "GetNumaProximityNode", "pass", "pass", passmsg );
		return TRUE;
	}
}

BOOL test_GetNumaProximityNodeEx(){
	char passmsg[100];
	char failmsg[100];
	BOOL result = 0;
	USHORT NodeNumber;
	
	result = GetNumaProximityNodeEx(0, &NodeNumber);
	if (result==0){
		strcpy(failmsg, GetErrorMessage("GetNumaProximityNodeEx() 실패 :", GetLastError()));
		wresult(__FILE__,__LINE__, "GetNumaProximityNodeEx", "fail", "pass", failmsg );
		return FALSE;
	}
	
	else{
		sprintf(passmsg, "GetNumaProximityNodeEx() 성공. 결과 값은 %d", result);
		wresult(__FILE__,__LINE__, "GetNumaProximityNodeEx", "pass", "pass", passmsg );
		return TRUE;
	}
}