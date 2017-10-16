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
		strcpy(buf, GetErrorMessage(" GetMaximumProcessorCount() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "GetMaximumProcessorCount", buf, "SUCCESS", meg);

	/** To compile an application that uses this function, set _WIN32_WINNT >= 0x0601 */

	return true;
}

BOOL test_GetMaximumProcessorGroupCount(){

	char meg[BUFSIZ] = "FAIL";																							
	char buf[BUFSIZ];

	DWORD result = GetMaximumProcessorGroupCount();

	#ifdef OQADBGPRINT
	printf("test_GetMaximumProcessorGroupCount \n");
	#endif

	if(result != 0){
		sprintf(meg, " GetMaximumProcessorGroupCount() : SUCCESS \n\n 프로세서 그룹 최대 개수 : %d", result);
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(buf, GetErrorMessage(" GetMaximumProcessorGroupCount() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "GetMaximumProcessorGroupCount", buf, "SUCCESS", meg);

	return true;
}

BOOL test_GetActiveProcessorCount(){

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	DWORD result = GetActiveProcessorCount(ALL_PROCESSOR_GROUPS);

	#ifdef OQADBGPRINT
	printf("test_GetActiveProcessorCount \n");
	#endif

	if(result != 0){
		sprintf(meg, " GetActiveProcessorCount() : SUCCESS \n\n 활성 프로세서 개수 : %d", result);
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(buf, GetErrorMessage(" GetActiveProcessorCount() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "GetActiveProcessorCount", buf, "SUCCESS", meg);

	return true;
}

BOOL test_GetActiveProcessorGroupCount(){

	char meg[BUFSIZ] = "FAIL";																							
	char buf[BUFSIZ];

	DWORD result = GetActiveProcessorGroupCount();

	#ifdef OQADBGPRINT
	printf("test_GetActiveProcessorGroupCount \n");
	#endif

	if(result != 0){
		sprintf(meg, " GetActiveProcessorGroupCount() : SUCCESS \n\n 활성 프로세서 그룹 개수 : %d", result);
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(buf, GetErrorMessage(" GetActiveProcessorGroupCount() : FAIL \n\n Error Message :", GetLastError()));
	
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
			strcpy(buf, GetErrorMessage(" GetLogicalProcessorInformationEx() : FAIL \n\n Error Message :", GetLastError()));

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
		strcpy(buf, GetErrorMessage(" GetCurrentProcessorNumber() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "GetCurrentProcessorNumber", buf, "SUCCESS", meg);

	return true;
}

/** 
	node number for the specified processor.
	NUMA(Non-Uniform Memory Access) NODE : 
*/
BOOL test_GetNumaProcessorNode(){
	
	BOOL result;
	
	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	/** processor가 존재하지 않는다면 node number(두 번째 파라미터)는 0xFF */
	DWORD processorNumber = GetCurrentProcessorNumber();

	if(processorNumber != -1){
		// 255
		UCHAR nodeNumber = 255;
		result = GetNumaProcessorNode((UCHAR)processorNumber, &nodeNumber);

		if(result != 0){
			sprintf(meg, " GetNumaProcessorNode() : SUCCESS \n\n number of processor the current thread : %d", processorNumber);
			strcpy(buf, "SUCCESS");
		}else 
			strcpy(buf, GetErrorMessage(" GetCurrentProcessorNumber() : FAIL \n\n Error Message :", GetLastError()));
	}else
		strcpy(buf, GetErrorMessage(" processor number 조회에 실패했습니다. \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "GetCurrentProcessorNumber", buf, "SUCCESS", meg);
	return true;
}

BOOL test_GetNumaNodeNumberFromHandle(){

	BOOL result;

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	USHORT nodeNumber = 255;
	HANDLE hFile = CreateFile(L"C:\\Users\\Tmax\\Desktop\\test_GetNumaNodeNumberFromHandle.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	result = GetNumaNodeNumberFromHandle(hFile, &nodeNumber);

	if(result != 0){
			sprintf(meg, " GetNumaNodeNumberFromHandle() : SUCCESS");
			strcpy(buf, "SUCCESS");
	}else 
			strcpy(buf, GetErrorMessage(" GetNumaNodeNumberFromHandle() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "GetNumaNodeNumberFromHandle", buf, "SUCCESS", meg);

	return true;
}