#include "TestProcessor.h"

BOOL test_GetMaximumProcessorCount(){

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	DWORD result = GetMaximumProcessorCount(ALL_PROCESSOR_GROUPS);

	#ifdef OQADBGPRINT
	printf("test_GetMaximumProcessorCount \n");
	#endif
	 
	if(result != 0){
		sprintf(meg, " GetMaximumProcessorCount() : SUCCESS \n\n 프로세서 최대값 = %d", result);
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(meg, GetErrorMessage(" GetMaximumProcessorCount() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "GetMaximumProcessorCount", buf, "SUCCESS", meg);

	/** To compile an application that uses this function, set _WIN32_WINNT >= 0x0601 */

	return true;
}

/**
	시스템 안이나 프로세서 그룹에서 active 상태의 프로세서들의 수를 검색
*/
BOOL test_GetActiveProcessorCount(){

	#ifdef OQADBGPRINT
	printf("test_GetActiveProcessorCount \n");
	#endif

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	/** 파라미터 ALL_PROCESSOR_GROUPS */
	DWORD result = GetActiveProcessorCount(ALL_PROCESSOR_GROUPS);

	if(result != 0){
		sprintf(meg, " GetActiveProcessorCount() : SUCCESS \n\n 활성 프로세서 개수 : %d", result);
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(meg, GetErrorMessage(" GetActiveProcessorCount() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "GetActiveProcessorCount", buf, "SUCCESS", meg);

	return true;
}

BOOL test_GetActiveProcessorGroupCount(){

	#ifdef OQADBGPRINT
	printf("test_GetActiveProcessorGroupCount \n");
	#endif

	char meg[BUFSIZ] = "FAIL";																							
	char buf[BUFSIZ];

	DWORD result = GetActiveProcessorGroupCount();

	if(result != 0){
		sprintf(meg, " GetActiveProcessorGroupCount() : SUCCESS \n\n 활성 프로세서 그룹 개수 : %d", result);
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(meg, GetErrorMessage(" GetActiveProcessorGroupCount() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "GetActiveProcessorGroupCount", buf, "SUCCESS", meg);

	return true;
}

/** information about the relationships of logical processors and related hardware */
BOOL test_GetLogicalProcessorInformationEx(){

	LONG rcb = 0x100;
	PVOID buffer;
	BOOL result;

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	printf("test_GetLogicalProcessorInformationEx \n");
	#endif

	if (buffer = new TCHAR[rcb]){
		result = GetLogicalProcessorInformationEx(RelationAll, (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)buf, (PDWORD)&rcb);

		if(result = TRUE){
			sprintf(meg, " GetLogicalProcessorInformationEx() : SUCCESS \n\n");
			strcpy(buf, "SUCCESS");
		}else 
			strcpy(meg, GetErrorMessage(" GetLogicalProcessorInformationEx() : FAIL \n\n Error Message :", GetLastError()));

		wresult(__FILE__, __LINE__, "GetLogicalProcessorInformationEx", buf, "SUCCESS", meg);
	}
	return true;
}

BOOL test_GetCurrentProcessorNumber(){

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	/** returns the processor number within the processor group to which the logical processor is assigned.*/
	DWORD result = GetCurrentProcessorNumber();

	#ifdef OQADBGPRINT
	printf("test_GetCurrentProcessorNumber \n");
	#endif

	if(result != -1){
		sprintf(meg, " GetCurrentProcessorNumber() : SUCCESS \n\n 현재 실행중인 thread의 number : %d", result);
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(meg, GetErrorMessage(" GetCurrentProcessorNumber() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "GetCurrentProcessorNumber", buf, "SUCCESS", meg);

	return true;
}





//노드 번호 검색
BOOL test_GetNumaProcessorNodeEx(){

	#ifdef OQADBGPRINT
	printf("test_GetNumaProcessorNodeEx \n");
	#endif

	BOOL result;

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	PROCESSOR_NUMBER processorNumber;
	USHORT NodeNumber;
	// uint16_t numaNode = 0;

	// Query the operating system to determine the NUMA node identifier for the current thread.
	GetCurrentProcessorNumberEx(&processorNumber);

	result = GetNumaProcessorNodeEx(&processorNumber, &NodeNumber);

	if (result != 0){
		sprintf(meg, " GetNumaProcessorNodeEx() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(meg, GetErrorMessage(" GetNumaProcessorNodeEx() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "GetNumaProcessorNodeEx", buf, "SUCCESS", meg);

	return true;
}

BOOL test_GetNumaNodeProcessorMask(){

	#ifdef OQADBGPRINT
	printf("test_GetNumaNodeProcessorMask \n");
	#endif

	BOOL result;
	//UCHAR Node;
	ULONGLONG ProcessorMask;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	result = GetNumaNodeProcessorMask(0, &ProcessorMask);

	if(result != 0){
		sprintf(meg, " GetNumaNodeProcessorMask() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(meg, GetErrorMessage(" GetNumaNodeProcessorMask() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "GetNumaNodeProcessorMask", buf, "SUCCESS", meg);

	return true;
}


BOOL test_GetNumaNodeProcessorMaskEx(){

	BOOL result = 0;

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	USHORT NodeNumber = 0;
	GROUP_AFFINITY ProcessorMask ;

	result = GetNumaNodeProcessorMaskEx(NodeNumber, &ProcessorMask);

	if (result != 0){
		sprintf(meg, " GetNumaNodeProcessorMaskEx() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(meg, GetErrorMessage(" GetNumaNodeProcessorMaskEx() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "GetNumaNodeProcessorMaskEx", buf, "SUCCESS", meg);

	return true;
}

BOOL test_GetCurrentProcessorNumberEx(){

	#ifdef OQADBGPRINT
	printf("test_GetCurrentProcessorNumberEx \n");
	#endif

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	DWORD result1, result2;
	PROCESSOR_NUMBER ProcNumber;

	GetCurrentProcessorNumberEx(&ProcNumber);

	result1 = GetActiveProcessorGroupCount();
	result2 = GetCurrentProcessorNumber();

	if(result1 != -1 && result2 != -1){
		sprintf(meg, "GetCurrentProcessorNumberEx() : SUCCESS \n\n활성 프로세서 그룹 개수 : %d \n현재 실행중인 thread의 number : %d", result1, result2);
		//sprintf(meg, " FlushProcessWriteBuffers() : SUCCESS \n\n Flush 전 __rdtsc = %d \n Flush 후 __rdtsc = %d ", t1, t2);
		strcpy(buf, "SUCCESS");
	}else{
		strcpy(buf, GetErrorMessage(" GetCurrentProcessorNumberEx() : FAIL \n\n Error Message :", GetLastError()));
	}
	wresult(__FILE__, __LINE__, "GetCurrentProcessorNumberEx", buf, "SUCCESS", meg);

	return true;
}