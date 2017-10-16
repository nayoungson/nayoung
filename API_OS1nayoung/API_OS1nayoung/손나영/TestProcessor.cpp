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