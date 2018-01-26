#include "TestProcessor.h"

/** 
* DWORD GetActiveProcessorCount(
  _In_ WORD GroupNumber
  ); 
* 프로세서 그룹 또는 시스템의 활성 프로세서 수를 반환.
* @author : 손나영
*
* @param GroupNumber 프로세서 그룹 번호.
* @return 프로세서 수
*/

//시스템 안이나 프로세서 그룹에서 active 상태의 프로세서들의 수를 가져옴
BOOL test_GetActiveProcessorCount(){
	
	#ifdef OQADBGPRINT
	printf("test_GetActiveProcessorCount\n");
	#endif

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	/** 파라미터 ALL_PROCESSOR_GROUPS */
	DWORD result = GetActiveProcessorCount(ALL_PROCESSOR_GROUPS);

	if(result != 0){
		sprintf(msg, " GetActiveProcessorCount() : SUCCESS \n\n 활성 프로세서 개수 : %d", result);
		strcpy(buf, "SUCCESS");
	}else{
		strcpy(msg, GetErrorMessage(" GetActiveProcessorCount() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetActiveProcessorCount", buf, "SUCCESS", msg);
	return result;
}



/** 
* WORD GetActiveProcessorGroupCount(void);
* 시스템의 활성 프로세서 그룹 수를 반환
* @author : 손나영
*
* @param void
* @return 시스템의 활성 프로세서 그룹 수
*/

BOOL test_GetActiveProcessorGroupCount(){

	#ifdef OQADBGPRINT
	printf("test_GetActiveProcessorGroupCount \n");
	#endif

	char msg[BUFSIZ] = "FAIL";																							
	char buf[BUFSIZ];

	DWORD result = GetActiveProcessorGroupCount();

	if(result != 0){
		sprintf(msg, " GetActiveProcessorGroupCount() : SUCCESS \n\n 활성 프로세서 그룹 개수 : %d", result);
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(msg, GetErrorMessage(" GetActiveProcessorGroupCount() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "GetActiveProcessorGroupCount", buf, "SUCCESS", msg);

	return result;
}

/**
* DWORD WINAPI GetCurrentProcessorNumber(void);
* 이 함수를 호출 할 때 현재 스레드가 실행 중이던 프로세서의 번호를 가져옴.
* @author : 손나영
*
* @param void
* @return  실행 중이던 프로세서의 번호.
*/

BOOL test_GetCurrentProcessorNumber(){
	
	#ifdef OQADBGPRINT
	printf("test_GetCurrentProcessorNumber \n");
	#endif

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	/** returns the processor number within the processor group to which the logical processor is assigned.*/
	DWORD result = GetCurrentProcessorNumber();

	if(result != -1){
		sprintf(msg, " GetCurrentProcessorNumber() : SUCCESS \n\n 현재 실행중인 thread의 number : %d", result);
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(msg, GetErrorMessage(" GetCurrentProcessorNumber() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "GetCurrentProcessorNumber", buf, "SUCCESS", msg);

	return result;
}

/**
* VOID GetCurrentProcessorNumberEx(
  _Out_ PPROCESSOR_NUMBER ProcNumber
  );
* 호출 스레드가 실행중인 논리 프로세서의 프로세서 그룹 및 번호를 검색.
* @author : 손나영
*
* @param 논리 프로세서가 할당 된 프로세서 그룹과 해당 그룹 내의 논리 프로세서 번호를 수신 하는 PROCESSOR_NUMBER 구조체에 대한 포인터 .
* @return 없음.
*/

BOOL test_GetCurrentProcessorNumberEx(){

	#ifdef OQADBGPRINT
	printf("test_GetCurrentProcessorNumberEx \n");
	#endif

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	BOOL result = FALSE;
	DWORD result1, result2;
	PROCESSOR_NUMBER ProcNumber;

	//돌고있는 스레드가 실행중인 논리 프로세서의 그룹 및 번호 가져옴
	GetCurrentProcessorNumberEx(&ProcNumber);

	result1 = GetActiveProcessorGroupCount();
	result2 = GetCurrentProcessorNumber();

	if(result1 != -1 && result2 != -1){
		sprintf(msg, "GetCurrentProcessorNumberEx() : SUCCESS \n\n활성 프로세서 그룹 개수 : %d \n현재 실행중인 thread의 number : %d", result1, result2);
		//sprintf(msg, " FlushProcessWriteBuffers() : SUCCESS \n\n Flush 전 __rdtsc = %d \n Flush 후 __rdtsc = %d ", t1, t2);
		strcpy(buf, "SUCCESS");
		result = TRUE;
	}else{
		strcpy(buf, GetErrorMessage(" GetCurrentProcessorNumberEx() : FAIL \n\n Error Message :", GetLastError()));
	}
	wresult(__FILE__, __LINE__, "GetCurrentProcessorNumberEx", buf, "SUCCESS", msg);

	return result;
}                       


/**
* BOOL GetLogicalProcessorInformationEx(
  _In_      LOGICAL_PROCESSOR_RELATIONSHIP           RelationshipType,
  _Out_opt_ PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX Buffer,
  _Inout_   PDWORD                                   ReturnedLength
  );
* 논리 프로세서 및 관련 하드웨어의 관계에 대한 정보를 검색 
* @author : 손나영
*
* @param RelationshipType 검색 할 관계의 유형
* @param Buffer SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX 구조체 의 배열을받는 버퍼에 대한 포인터
* @ReturnedLength 입력시, Buffer가 가리키는 버퍼의 길이를 바이트 단위로 지정
* @return 검색 성공 시 TRUE 반환과 동시에, 하나 이상의 SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX 구조가 출력 버퍼에 기록됨.
*/

/** information about the relationships of logical processors and related hardware .*/
BOOL test_GetLogicalProcessorInformationEx(){

	#ifdef OQADBGPRINT
	printf("test_GetLogicalProcessorInformationEx \n");
	#endif

	BOOL result = FALSE;
	DWORD len = sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX);

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";
	char * slpi = new char[sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)];

	result = GetLogicalProcessorInformationEx(RelationAll, (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)slpi, &len);

	if(result == FALSE){
		//while(result == FALSE)
		delete[] slpi;

		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER){
			slpi = new char[len];

			result = GetLogicalProcessorInformationEx(RelationAll, (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)slpi, &len);

			if(result == TRUE){
				sprintf(msg, " GetLogicalProcessorInformationEx() : SUCCESS");
				strcpy(buf, "SUCCESS");
				result = TRUE;
			}
		}else{
			strcpy(msg, GetErrorMessage(" GetLogicalProcessorInformationEx() : FAIL \n\n Error Message :", GetLastError()));
		}

	}else if(result==TRUE){
		sprintf(msg, " GetLogicalProcessorInformationEx() : SUCCESS");
		strcpy(buf, "SUCCESS");
		result = TRUE;
	}

	wresult(__FILE__, __LINE__, "GetLogicalProcessorInformationEx", buf, "SUCCESS", msg);
	return result;
}

/**
* DWORD GetMaximumProcessorCount(
  _In_ WORD GroupNumber
);
* 프로세서 그룹 또는 시스템이 가질 수있는 논리 프로세서의 최대 수를 반환
* @author : 손나영
*
* @param GroupNumber 프로세서 그룹 번호.
* @return 프로세서 수
*/

BOOL test_GetMaximumProcessorCount(){

	#ifdef OQADBGPRINT
	printf("test_GetMaximumProcessorCount\n");
	#endif

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	DWORD result = GetMaximumProcessorCount(ALL_PROCESSOR_GROUPS);

	#ifdef OQADBGPRINT
	printf("test_GetMaximumProcessorCount \n");
	#endif
	 
	if(result != 0){
		sprintf(msg, " GetMaximumProcessorCount() : SUCCESS \n\n 프로세서 최대값 = %d", result);
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(msg, GetErrorMessage(" GetMaximumProcessorCount() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "GetMaximumProcessorCount", buf, "SUCCESS", msg);

	/** To compile an application that uses this function, set _WIN32_WINNT >= 0x0601 */

	return result;
}


/**
* BOOL WINAPI GetNumaNodeProcessorMask(
  _In_  UCHAR      Node,
  _Out_ PULONGLONG ProcessorMask
 );
* 지정된 노드의 프로세서 마스크를 검색함.
* @author : 손나영
*
* @param Node 노드 번호.
* @param ProcessorMask 노드의 프로세서 마스크.
* @return 마스크 검색 성공/실패 여부.
*/

BOOL test_GetNumaNodeProcessorMask(){

	#ifdef OQADBGPRINT
	printf("test_GetNumaNodeProcessorMask \n");
	#endif

	BOOL result;
	//UCHAR Node;
	ULONGLONG ProcessorMask;

	char buf[BUFSIZ];
	char msg[BUFSIZ] = "FAIL";

	result = GetNumaNodeProcessorMask(0, &ProcessorMask);

	if(result != 0){
		sprintf(msg, " GetNumaNodeProcessorMask() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(msg, GetErrorMessage(" GetNumaNodeProcessorMask() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "GetNumaNodeProcessorMask", buf, "SUCCESS", msg);

	return result;
}


/**
* BOOL GetNumaNodeProcessorMaskEx(
  _In_  USHORT          Node,
  _Out_ PGROUP_AFFINITY ProcessorMask
  );
* 노드가 속한 프로세서 그룹에 관계없이 노드의 프로세서 마스크를 검색
* @author : 손나영
*
* @param Node 노드 번호.
* @param ProcessorMask 지정된 노드에 대한 프로세서 마스크를받는 GROUP_AFFINITY 구조체에 대한 포인터 .
* @return 마스크 검색 성공/실패 여부.
*/

BOOL test_GetNumaNodeProcessorMaskEx(){
	
	#ifdef OQADBGPRINT
	printf("test_GetNumaNodeProcessorMaskEx \n");
	#endif

	BOOL result = 0;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	USHORT NodeNumber = 0;
	GROUP_AFFINITY ProcessorMask ;

	result = GetNumaNodeProcessorMaskEx(NodeNumber, &ProcessorMask);

	if (result != 0){
		sprintf(msg, " GetNumaNodeProcessorMaskEx() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(msg, GetErrorMessage(" GetNumaNodeProcessorMaskEx() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "GetNumaNodeProcessorMaskEx", buf, "SUCCESS", msg);

	return result;
}

         
/**
* BOOL GetNumaProcessorNodeEx(
  _In_  PPROCESSOR_NUMBER Processor,
  _Out_ PUSHORT           NodeNumber
  );
* 지정된 논리 프로세서 의 USHORT 값 으로 노드 번호를 검색.
* @author : 손나영
*
* @param Processor 논리 프로세서와 할당 된 프로세서 그룹을 나타내는 PROCESSOR_NUMBER 구조체에 대한 포인터.
* @param NodeNumber 노드 번호를받을 변수에 대한 포인터.
* @return 노드 번호 검색 성공/실패 여부.
*/

//노드 번호 가져옴
BOOL test_GetNumaProcessorNodeEx(){

	#ifdef OQADBGPRINT
	printf("test_GetNumaProcessorNodeEx \n");
	#endif

	BOOL result;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	PROCESSOR_NUMBER processorNumber;
	USHORT NodeNumber;
	// uint16_t numaNode = 0;

	// Query the operating system to determine the NUMA node identifier for the current thread.
	GetCurrentProcessorNumberEx(&processorNumber);

	result = GetNumaProcessorNodeEx(&processorNumber, &NodeNumber);

	if (result != 0){
		sprintf(msg, " GetNumaProcessorNodeEx() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(msg, GetErrorMessage(" GetNumaProcessorNodeEx() : FAIL \n\n Error Message :", GetLastError()));

	wresult(__FILE__, __LINE__, "GetNumaProcessorNodeEx", buf, "SUCCESS", msg);

	return result;
}


