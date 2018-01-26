#include "TestMemory.h"
#include <WERAPI.H>
#include <Psapi.h>
#include <TlHelp32.h>


/**
* BOOL WINAPI AddSecureMemoryCacheCallback(
  _In_ PSECURE_MEMORY_CACHE_CALLBACK pfnCallBack
  );
* ���� �޸� ������ �����ǰų� ��ȣ�� ���� �� �� ȣ��Ǵ� �ݹ� �Լ��� ���
* @author : �ճ���
*
* @param pfnCallBack ��� �� ���� ���α׷� ���� SecureMemoryCacheCallback �Լ��� ���� ������.
* @return �ݹ� �Լ� ��� ����/���� ����.
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


	// ���� �޸� ������ �����ǰų� ��ȣ�� ����� �� ȣ��Ǵ� �ݹ� �Լ��� ���
	// BOOLEAN CALLBACK SecureMemoryCacheCallback(PVOID Addr, SIZE_T Range)
	BOOL result = AddSecureMemoryCacheCallback(SecureMemoryCacheCallback);

	if(result == TRUE){
		sprintf(msg, " AddSecureMemoryCacheCallback() : SUCCESS");
		strcpy(buf, "SUCCESS");

	}else{
		sprintf(msg, " AddSecureMemoryCacheCallback() : FAIL");
		result = FALSE;
	}

	// AddSecureMemoryCacheCallback�Լ��� ��ϵ� �ݹ� �Լ��� ����� ���
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
* ������ ���μ����� AWE ( Address Windowing Extensions ) ���� ������ ���� �� ���� ���� �� ������ �޸� �������� �Ҵ�.
* Itanium ��� �ý����� 64 ��Ʈ Windows ���� �� FAIL ����.
* @author : �ճ���
*
* @param hProcess ���μ��� �ڵ�. PROCESS_VM_OPERATION ����.
* @param NumberOfPages �Ҵ� �� ���� �޸��� ũ�� (������). GetSystemInfo �Լ�.
* @param UserPfnArray �Ҵ� �� �޸��� ������ ������ ��ȣ�� �����ϴ� �迭�� ���� ������. �迭�� ũ��� �ּ��� ULONG_PTR ������ ���� �� NumberOfPages �� �̻�. ����X
* @return �Ҵ� ����/���� ����
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
		strcpy(msg, " AllocateUserPhysicalPages() : FAIL \n\n <64-bit Windows on Itanium ���� �ý���>\n\n cmd â���� wmic cpu get architecture �Է����� �� \n 6(means Itanium)�� 9(means x64)�� ��µǾ�� ������");
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
* ������ ���μ����� AWE ( Address Windowing Extensions ) ���� ������ ���� �� ���� ���� �� ���� �޸� �������� �Ҵ��ϰ� ���� �޸𸮿� ���� NUMA ��带 ����
* @author : �ճ���
*
* @param hProcess ���μ��� �ڵ�. PROCESS_VM_OPERATION ����.
* @param NumberOfPages �Ҵ� �� ���� �޸��� ũ�� (������). GetSystemInfo �Լ�.
* @param PageArray �Ҵ� �� �޸��� ������ ������ ��ȣ�� �����ϴ� �迭�� ���� ������. �Ҵ�Ǵ� �迭�� ũ��� �ּ��� ULONG_PTR ������ ���� �� NumberOfPages �� �̻�.
* @param nndPreferred ������ �޸𸮰� �־���ϴ� NUMA ���
* @return ������ �Ҵ� �� NUMA ��� ���� ����/���� ����.
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

	//�Ҵ��� ���� �޸��� ũ��
	//��� �� �Ű������� ���� �Ҵ�� ������ ���� ������. ��û�� ������ ���� �� ����.

	int err = GetLastError();

	//sSyinfo �������� �Լ�
	GetSystemInfo(&sSysInfo);
	//sSysInfo.dwPageSize = 1024;
	NumberOfPages = MEMORY_REQUESTED/sSysInfo.dwPageSize;
	//NumberOfPages = 
	PFNArraySize = NumberOfPages * sizeof(ULONG_PTR);

	//�Ҵ�� �޸��� ������ ������ ��ȣ �����ϴ� �迭�� ���� ������
	//�ּ��� ULONG_PTR������ ������ NumberOfPages�� �̻��̾�� ��.
	aPFNs = (ULONG_PTR *)HeapAlloc(GetProcessHeap(), 0, PFNArraySize);
	// 
	////���� �ο� SetPrivilege
	//if (OpenProcessToken(proccessHandle, typeOfAccess, &tokenHandle)){
	//	// Enabling RESTORE and BACKUP privileges
	//	SetPrivilege(tokenHandle, SE_ASSIGNPRIMARYTOKEN_NAME , TRUE);
	//	SetPrivilege(tokenHandle, SE_BACKUP_NAME , TRUE);
	//	printf(" ���� �ο� - ����");

	//}else{
	//	wprintf(L"Error getting the access token.\n");
	//}
	

	/*if(!LoggedSetLockPagesPrivilege(GetCurrentProcess(), TRUE)){
		printf("logged ����");
	}else
		printf("�̰� ����");*/

	DWORD num = GetCurrentProcessId();
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_TERMINATE , FALSE, num);

	//�Լ� ����
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
* Itanium ��� �ý����� 64 ��Ʈ Windows
* AllocateUserPhysicalPages �Ǵ� AllocateUserPhysicalPagesNuma�� �Ҵ��� ���� �޸� �������� ����.
* @author : �ճ���
*
* @param Process ���μ��� �ڵ�.
* @param NumberOfPages ���� �޸� ������ ũ��.
* @param UserPfnArray ���� �� �Ҵ� �� �޸��� ������ ������ ��ȣ �迭�� ���� ������.
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
		sprintf(msg, " FreeUserPhysicalPages() : FAIL \n\n <64-bit Windows on Itanium ���� �ý���> \n\n cmd â���� wmic cpu get architecture �Է����� �� \n 6(means Itanium)�� 9(means x64)�� ��µǾ�� ������ ");
		strcpy(buf, "FAIL");
	}

	wresult(__FILE__, __LINE__, "FreeUserPhysicalPages", buf, "SUCCESS", msg);

	return result;
	
  }

/**
* SIZE_T WINAPI GetLargePageMinimum(void);
* ū �������� �ּ� ũ�⸦ ������.
* @author : �ճ���
*
* @param void
* @return ū �������� �ּ� ũ��.
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

	if(size > 200000){ //���μ��� ū �������� ������ ���, ū �������� �ּ� ũ�⸦ ��ȯ. �Ϲ������� 2MB�̻�. ���� 2MB�̻��� ��� �������� ����. 
		sprintf(msg, " GetLargePageMinimum() : SUCCESS \n\n ��minimum size of a large page : %d Byte", size);
		strcpy(buf, "SUCCESS");
		result = TRUE;

	}else if(0 < size && size <= 200000){
		sprintf(msg, " GetLargePageMinimum() : SUCCESS \n\n ��minimum size of a large page : %d Byte \n (���� : �ּ� �������� ũ��� �پ��ϱ� �ϳ�, �Ϲ������δ� 2MB�̻��Դϴ�.)", size);
		strcpy(buf, "SUCCESS");
		result = TRUE;

	}else if(size == 0){
		sprintf(msg, " GetLargePageMinimum() : FAIL \n\n �� ���μ����� large pages�� �������� �ʽ��ϴ�.");
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
* Ư�� ���μ����� �޸� ��뿡 ���� ������ �˻�.
* @author : �ճ���
* 
* @param Process ���μ��� �ڵ�. PROCESS_QUERY_INFORMATION �Ǵ� PROCESS_QUERY_LIMITED_INFORMATION �Ǵ�PROCESS_VM_READ ���� �ʼ�.
* @param ppsmemCounters ���μ����� �޸� ��뿡 ���� ������ �ҷ����� PROCESS_MEMORY_COUNTERS �Ǵ� PROCESS_MEMORY_COUNTERS_EX ����ü�� ���� ������.
* @param cb ppsmemCounters�� ũ��. ����Ʈ.
* @return ���� �˻� ����/���� ����.
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
* Itanium ��� �ý����� 64 ��Ʈ Windows
* ���� �Ҵ� �� ���� �޸� �������� AWE ( Address Windowing Extensions ) ���� �� ������ �ּҿ� ����
* @author : �ճ���
*
* @param lpAddress ����� �� �޸� ������ ���� �ּҿ� ���� ������.
* @param NumberOfPages �������� ��ȯ �� ���� �޸� �� ���� �ּ� ������ ũ��.
* @param UserPfnArray ������ ������ ������ ��ȣ�� �迭�� ���� ������. NULL�̸� ������ �ּ� ������ ���� ������. ���� ������ �����Ϸ��� FreeUserPhysicalPages
* @return ���� ����/���� ����.
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
		sprintf(msg, " MapUserPhysicalPages() : FAIL \n\n <64-bit Windows on Itanium ���� �ý���> \n\n cmd â���� wmic cpu get architecture �Է����� �� \n 6(means Itanium)�� 9(means x64)�� ��µǾ�� ������ ");
		strcpy(buf, "FAIL");
	}

	wresult(__FILE__, __LINE__, "MapUserPhysicalPages", buf, "SUCCESS", msg);

	return result;
}


/**
* BOOL WINAPI RemoveSecureMemoryCacheCallback(
  _In_ PSECURE_MEMORY_CACHE_CALLBACK pfnCallBack
 );
* ������ AddSecureMemoryCacheCallback �Լ��� ��ϵ� �ݹ� �Լ��� ����� ���.
* @author : �ճ���
*
* @param pfnCallBack ���� �� ���� ���α׷� ���� SecureMemoryCacheCallback �Լ��� ���� ������
* @return
*/

BOOL test_RemoveSecureMemoryCacheCallback(){

	#ifdef OQADBGPRINT
	printf("test_RemoveSecureMemoryCacheCallback \n");
	#endif

	char msg[BUFSIZ];
	char buf[BUFSIZ] = "FAIL";
	
	PSECURE_MEMORY_CACHE_CALLBACK pfnCallBack = NULL;

	// ���� �޸� ������ �����ǰų� ��ȣ�� ����� �� ȣ��Ǵ� �ݹ� �Լ��� ���
	// BOOLEAN CALLBACK SecureMemoryCacheCallback(PVOID Addr, SIZE_T Range)
	DWORD err = GetLastError();
	BOOL result = AddSecureMemoryCacheCallback(SecureMemoryCacheCallback);

	if(result == TRUE){

		result = RemoveSecureMemoryCacheCallback(SecureMemoryCacheCallback);
			if(result == TRUE){
				strcpy(buf, "SUCCESS");
				sprintf(msg, "RemoveSecureMemoryCacheCallback() : SUCCESS");
			}else
				sprintf(msg, "RemoveSecureMemoryCacheCallback() ���� \n\nError Code : %d", err);
	
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
* �ٸ� ���μ����� �Ҵ� �� �޸𸮸� ���� ���α׷� ���� ���۷� ����
* @author : �ճ���
*
* @param th32ProcessID �޸𸮰� ����ǰ��ִ� ���μ����� �ĺ���. �� �Ű� ������ ���� ���μ����� �޸𸮸� �����ϱ� ���� 0 �� �� ����,
* @param lpBaseAddress ���� Ư�� ���μ����� �⺻ �ּ�.
* @param lpBuffer ������ ���μ����� �ּ� ���� ������ �����ϴ� ���ۿ� ���� ������.
* @param cbRead ������ ���μ������� ���� ����Ʈ ��.
* @param lpNumberOfBytesRead
* @return ������ ���ۿ� ���� �� ����Ʈ ��
*/

// process id�� process�� memory �б�. ReadProcessMemory�� ���� ����
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
	
	//GetModuleHandle : ������ ��⿡ ���� �ڵ� ������
	result = Toolhelp32ReadProcessMemory(pid, GetModuleHandle(NULL), &buffer, 100, 0);
	//result = ReadProcessMemory(hProcess, (LPCVOID)addr, &buffer, 100, 0);
	//result = WriteProcessMemory(hProcess, (LPVOID)addr, &buffer, 100, 0);

	int err = GetLastError();

	//if(result == FALSE){ //������ �߻��ϸ� 0�� ��ȯ�ϵ��� �����. ������ ��� �ٸ� ���� ��ȯ�� �� ����. �׷��ϱ� FALSE�� ��
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
* ������ ���μ����� ���� �ּ� �������� �޸� ������ ���¸� ����, Ŀ�� �Ǵ� �����ϰ� ���� �޸𸮿� ���� NUMA ��带 ����
* @author : �ճ���
*
* @param hProcess ���μ��� �ڵ�.
* @param lpAddress �Ҵ� �� ������ ������ ���� ���ϴ� ���� �ּҸ� �����ϴ� ������
* @param dwSize �Ҵ� �� �޸� ������ ũ�� (����Ʈ).
* @param flAllocationType �޸� �Ҵ� ����. 4����.
* @param flProtect �Ҵ� �� ������ ������ ���� �޸� ��ȣ
* @param nndPreferred ������ �޸𸮰� �־���ϴ� NUMA ���
* @return ���� ����/���� ����.
*/

/**
	���� �Ǵ� ������ process�� ���� �ּ� ������ �޸� ������ commit�ϰ�,
	������ �޸��� NUMA ��带 ����
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
		strcpy(buf, "FAIL");
		sprintf(msg, "VirtualAllocExNuma() : FAIL \n\n Error : %d \n node number%u\n", GetLastError(), NodeNumber);

	}else{ //����
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
* WER���� ���� ������ ���� �� ���� �� �޸� ����� ���
* @author : �ճ���
* 
* @param pvAddress �޸� ����� ���� �ּ�.
* @param dwSize �޸� ����� ũ�� (����Ʈ). �ִ�� WER_MAX_MEM_BLOCK_SIZE ����Ʈ.
* @return ��� ���� �� S_OK.
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
		strcpy(msg, " WerRegisterMemoryBlock() : SUCCESS \n\n WER���� error report�� ���鶧 �����ϱ� ���� memory block�� ����߽��ϴ�.");
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
* ���� ���α׷��� �������� �� ���� �� ������ ��Ͽ��� �޸� ����� ����
* @author : �ճ��� 
*
* @param pvAddress �޸� ����� ���� �ּ�. �޸� ����� WerRegisterMemoryBlock �Լ��� ����Ͽ� ��ϵǾ� �־�� ��.
* @return ���� ���� �� S_OK.
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
			strcpy(msg, " WerUnregisterMemoryBlock() : SUCCESS \n\n WER���� error report�� ���鶧 �����ϱ� ���� memory block�� �����߽��ϴ�.");
		}else{
			strcpy(buf, "FAIL");
			strcpy(msg, GetErrorMessage(" WerUnregisterMemoryBlock() : FAIL  \n\n Error Message :" , GetLastError()));
		}
	}else{
		strcpy(buf, "FAIL");
		strcpy(msg, GetErrorMessage(" WerRegisterMemoryBlock() : FAIL  \n\n  WerRegisterMemoryBlock���� �ٽ� �Ͻʽÿ�.Error Message :" , GetLastError()));
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








//�̾��
BOOL test_GetNumaProximityNode(){
	char passmsg[100];
	char failmsg[100];
	BOOL result = TRUE;
	UCHAR NodeNumber;
	
	result = GetNumaProximityNode(0, &NodeNumber);
	if (result==FALSE){
		strcpy(failmsg, GetErrorMessage("GetNumaProximityNode() ���� :", GetLastError()));
		wresult(__FILE__,__LINE__, "GetNumaProximityNode", "fail", "pass", failmsg );
		result = FALSE;
	}
	
	else{
		sprintf(passmsg, "GetNumaProximityNode() ����. ��� ���� %d", result);
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
		strcpy(failmsg, GetErrorMessage("GetNumaProximityNodeEx() ���� :", GetLastError()));
		wresult(__FILE__,__LINE__, "GetNumaProximityNodeEx", "fail", "pass", failmsg );
		result = FALSE;
	}
	
	else{
		sprintf(passmsg, "GetNumaProximityNodeEx() ����. ��� ���� %d", result);
		wresult(__FILE__,__LINE__, "GetNumaProximityNodeEx", "pass", "pass", passmsg );
	}
	return result;
}