#include "TestMemory.h"

/**
	AllocateUserPhysicalPages() : ������ ���μ����� AWE(Address Windowing Extensions) ���� ������ ���� �� ���� ���� �� ������ �޸� �������� �Ҵ�
	// ������ ũ���� ���̷� ���� 32 ��Ʈ ���� ���α׷������� �Ұ�
	func(HANDLE hProcess, The size of the physical memory to allocate in paes��GetSystemInfo, PfnArray)
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
	char meg[BUFSIZ];
	
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
	result = AllocateUserPhysicalPages(hProcess, &NumberOfPages,aPFNs);

	if(result == TRUE ){
		sprintf(meg, " AllocateUserPhysicalPages() : SUCCESS \n\n This computer has page size : %d \n Requesting a PFN array of %d bytes \n ", sSysInfo.dwPageSize, PFNArraySize);
		strcpy(buf, "SUCCESS");
	}else {
		strcpy(meg, GetErrorMessage(" AllocateUserPhysicalPages() : FAIL \n\n <64-bit Windows on Itanium ���� �ý���>\n\n cmd â���� wmic cpu get architecture �Է����� �� \n 6(means Itanium)�� 9(means x64)�� ��µǾ�� ������ \n\n Error Message :" , GetLastError()));

	}
	if(NumberOfPagesInitial != NumberOfPages) {
		//printf(("Allocated only %p pages.\n"), NumberOfPages );
		return 0;
	}
	wresult(__FILE__, __LINE__, "AllocateUserPhysicalPages", buf, "SUCCESS", meg);

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
	char meg[BUFSIZ];

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
		sprintf(meg, " FreeUserPhysicalPages() : FAIL \n\n <64-bit Windows on Itanium ���� �ý���> \n\n cmd â���� wmic cpu get architecture �Է����� �� \n 6(means Itanium)�� 9(means x64)�� ��µǾ�� ������ ");
	}

	wresult(__FILE__, __LINE__, "FreeUserPhysicalPages", buf, "SUCCESS", meg);

	return true;
	
  }

// ���� �ش� MapUserPhysicalPagesScatter
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
	char meg[BUFSIZ];
	
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
		sprintf(meg, " MapUserPhysicalPages() : FAIL \n\n <64-bit Windows on Itanium ���� �ý���> \n\n cmd â���� wmic cpu get architecture �Է����� �� \n 6(means Itanium)�� 9(means x64)�� ��µǾ�� ������ ");
	}

	wresult(__FILE__, __LINE__, "MapUserPhysicalPages", buf, "SUCCESS", meg);

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
		sprintf(meg, " GetLargePageMinimum() : SUCCESS \n\n ��minimum size of a large page : %d Byte", size);
		strcpy(buf, "SUCCESS");
	}else{
		sprintf(meg, " GetLargePageMinimum() : FAIL \n\n �� ���μ����� large pages�� �������� �ʽ��ϴ�.");
	}

	wresult(__FILE__, __LINE__, "GetLargePageMinimum", buf, "SUCCESS", meg);

	return true;
}

#define BUFSIZE MAX_PATH
BOOL test_GetFinalPathNameByHandleA(){

	#ifdef OQADBGPRINT
	printf("test_GetFinalPathNameByHandleA\n");
	#endif

	HANDLE hFile;
	DWORD dwRet;
	TCHAR Path[BUFSIZE];

	char buf[BUFSIZ];
	char meg[BUFSIZ];

	hFile = CreateFile(L"�ճ���\\test_GetFinalPathNameByHandleA.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile ==INVALID_HANDLE_VALUE){
		sprintf(meg, "Could not open file (error %d\n)", GetLastError());
		return 0;
	}

	dwRet = GetFinalPathNameByHandle(hFile,Path,BUFSIZE,VOLUME_NAME_NT);
	if(dwRet < BUFSIZE)	{
		sprintf(meg, " GetFinalPathNameByHandle() : SUCCESS \n\nThe final path :%S \n", Path);
		strcpy(buf, "SUCCESS");
	}
	else{
		sprintf(meg, " GetFinalPathNameByHandle() : FAIL \n\n The required buffer size is %d.\n", dwRet);
	}
	CloseHandle(hFile);

	wresult(__FILE__, __LINE__, "GetFinalPathNameByHandle", buf, "SUCCESS", meg);

	return true;
}

/**
	Ư�� process�� ��ϵ� ����� ���� �˻�
*/
BOOL test_GetApplicationRestartSettings(){

	#ifdef OQADBGPRINT
	printf("test_GetApplicationRestartSettings\n");
	#endif

	HRESULT hr = S_OK;
	WCHAR wsCommandLine[RESTART_MAX_CMD_LINE + 1];
	DWORD cchCmdLine = sizeof(wsCommandLine) / sizeof(WCHAR);
	DWORD dwFlags = 0;
	LPWSTR pwsCmdLine = NULL;

	char buf[BUFSIZ];
	char meg[BUFSIZ];

	hr = RegisterApplicationRestart(L"/restart -f .\\filename.ext", 0);

	if (SUCCEEDED(hr))    {
		hr = GetApplicationRestartSettings(GetCurrentProcess(), wsCommandLine, &cchCmdLine, &dwFlags);

		if(SUCCEEDED(hr)){
			sprintf(meg, " GetApplicationRestartSettings() : SUCCESS \n\n ��RegisterApplicationRestart �� success \n GetApplicationRestartSettings �� success");
			strcpy(buf, "SUCCESS");
		}else
			sprintf(meg, " GetApplicationRestartSettings() : FAIL \n\n ��RegisterApplicationRestart �� success \n GetApplicationRestartSettings �� fail");
	}else
		sprintf(meg, "GetApplicationRestartSettings() : FAIL \n\n ��RegisterApplicationRestart �� fail \n GetApplicationRestartSettings �� fail");


	// ����� : Returns S_OK instead of ERROR_INSUFFICIENT_BUFFER when pBuffer is NULL and size is 0.
	/**
	hr = GetApplicationRestartSettings(GetCurrentProcess(), (PWSTR)pwsCmdLine, &cchCmdLine, &dwFlags);

	if(SUCCEEDED(hr)){
		pwsCmdLine = (LPWSTR)malloc(cchCmdLine * sizeof(WCHAR));

		if(pwsCmdLine){
			hr = GetApplicationRestartSettings(GetCurrentProcess(), (PWSTR)pwsCmdLine, &cchCmdLine, &dwFlags);
			if(FAILED(hr)){
				wprintf(L"GetApplicationRestartSettings failed with 0x%x\n", hr);
			}
			wprintf(L"Command line: %s\n", pwsCmdLine);
		}else {
			wprintf(L"Allocating the command-line buffer failed.\n");
		}
	}else{
		if (hr != HRESULT_FROM_WIN32(ERROR_NOT_FOUND)){ // Not a restart.
			wprintf(L"GetApplicationRestartSettings failed with 0x%x\n", hr);

		}
	}
	*/

	wresult(__FILE__, __LINE__, "GetApplicationRestartSettings", buf, "SUCCESS", meg);

	return true;
}

/**
	���� �Ǵ� ������ process�� ���� �ּ� ������ �޸� ������ commit�ϰ�,
	������ �޸��� NUMA ��带 ����
*/
#define _WIN32_WINNT 0x0602
BOOL test_VirtualAllocExNuma(){

	#ifdef OQADBGPRINT
	printf("test_VirtualAllocExNuma\n");
	#endif

	char buf[BUFSIZ];
	char meg[BUFSIZ];

	DWORD  PageSize;
	ULONG HighestNodeNumber;
	ULONG NumberOfProcessors;
	PVOID* Buffers = NULL;
	SIZE_T AllocationSize = 0;

	if(AllocationSize == 0){
		AllocationSize = 16*1024*1024;
	}

	// processor�� �ý��� ������ ����� ������

	SYSTEM_INFO SystemInfo;
	GetSystemInfo (&SystemInfo);
	NumberOfProcessors = SystemInfo.dwNumberOfProcessors;
	PageSize = SystemInfo.dwPageSize;

	// ���� ���� ��� ��ȣ�� ������
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
		commit�ϰ� ������ �޸��� NUMA ��带 ����
		VirtualAllocExNuma(hProces, NULL:������ �Ҵ��� ��ġ�� ����, ��:���� ������ ������ �ݿø�, �޸� Ÿ�� �Ҵ�:���� �ְ� ���� ����|Ŀ��, 
						   Memory Protection Constants:�б⾲�� Ȱ��ȭ, ���� �޸𸮰� �����ؾ��ϴ� NUMA ���)
	*/
	PCHAR Buffer = (PCHAR)VirtualAllocExNuma(hProcess,NULL,AllocationSize,MEM_RESERVE | MEM_COMMIT,PAGE_READWRITE,NodeNumber);

	if(Buffer == NULL){
		sprintf(meg, "VirtualAllocExNuma() : FAIL \n\n Error : %d \n node number%u\n", GetLastError(), NodeNumber);

	}else{ //����
		strcpy(meg, " VirtualAllocExNuma() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}

	wresult(__FILE__, __LINE__, "GetFinalPathNameByHandle", buf, "SUCCESS", meg);

	return true;
}


BOOL test_AllocateUserPhysicalPagesNuma(){
	
	char buf[BUFSIZ];
	char meg[BUFSIZ];
	int PFNArraySize;               // memory to request for PFN array
	
	BOOL result;
	UCHAR i = 0;
	UCHAR NodeNumber;

	DWORD num = GetCurrentProcessId();
	printf("%d", num);
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_TERMINATE , FALSE, num);
	
	ULONG_PTR NumberOfPages;        // number of pages to request
	ULONG_PTR NumberOfPagesInitial; // initial number of pages requested
	ULONG_PTR *aPFNs;               // page info; holds opaque data
	SYSTEM_INFO sSysInfo;           // useful system information

	GetSystemInfo(&sSysInfo);  // fill the system information structure

	NumberOfPages = MEMORY_REQUESTED/sSysInfo.dwPageSize;
	PFNArraySize = NumberOfPages * sizeof (ULONG_PTR);
	
	aPFNs = (ULONG_PTR *) HeapAlloc(GetProcessHeap(), 0, PFNArraySize);

	NumberOfPagesInitial = NumberOfPages;

	if(!GetNumaProcessorNode(i,&NodeNumber)){
		// printf("GetNumaProcessorNode failed: %d\n", GetLastError());
	}

	result = AllocateUserPhysicalPagesNuma(hProcess,&NumberOfPages,aPFNs,NodeNumber);

	if(result == TRUE){
		printf("sdfds");
	}else{
		strcpy(meg, GetErrorMessage(" AllocateUserPhysicalPagesNuma() : FAIL  \n\n Error Message :" , GetLastError()));
	}
	wresult(__FILE__, __LINE__, "AllocateUserPhysicalPagesNuma", buf, "SUCCESS", meg);
	return true;
}