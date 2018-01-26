#include "TestProcessor.h"

/** 
* DWORD GetActiveProcessorCount(
  _In_ WORD GroupNumber
  ); 
* ���μ��� �׷� �Ǵ� �ý����� Ȱ�� ���μ��� ���� ��ȯ.
* @author : �ճ���
*
* @param GroupNumber ���μ��� �׷� ��ȣ.
* @return ���μ��� ��
*/

//�ý��� ���̳� ���μ��� �׷쿡�� active ������ ���μ������� ���� ������
BOOL test_GetActiveProcessorCount(){
	
	#ifdef OQADBGPRINT
	printf("test_GetActiveProcessorCount\n");
	#endif

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ];

	/** �Ķ���� ALL_PROCESSOR_GROUPS */
	DWORD result = GetActiveProcessorCount(ALL_PROCESSOR_GROUPS);

	if(result != 0){
		sprintf(msg, " GetActiveProcessorCount() : SUCCESS \n\n Ȱ�� ���μ��� ���� : %d", result);
		strcpy(buf, "SUCCESS");
	}else{
		strcpy(msg, GetErrorMessage(" GetActiveProcessorCount() : FAIL \n\n Error Message :", GetLastError()));
	}

	wresult(__FILE__, __LINE__, "GetActiveProcessorCount", buf, "SUCCESS", msg);
	return result;
}



/** 
* WORD GetActiveProcessorGroupCount(void);
* �ý����� Ȱ�� ���μ��� �׷� ���� ��ȯ
* @author : �ճ���
*
* @param void
* @return �ý����� Ȱ�� ���μ��� �׷� ��
*/

BOOL test_GetActiveProcessorGroupCount(){

	#ifdef OQADBGPRINT
	printf("test_GetActiveProcessorGroupCount \n");
	#endif

	char msg[BUFSIZ] = "FAIL";																							
	char buf[BUFSIZ];

	DWORD result = GetActiveProcessorGroupCount();

	if(result != 0){
		sprintf(msg, " GetActiveProcessorGroupCount() : SUCCESS \n\n Ȱ�� ���μ��� �׷� ���� : %d", result);
		strcpy(buf, "SUCCESS");
	}else 
		strcpy(msg, GetErrorMessage(" GetActiveProcessorGroupCount() : FAIL \n\n Error Message :", GetLastError()));
	
	wresult(__FILE__, __LINE__, "GetActiveProcessorGroupCount", buf, "SUCCESS", msg);

	return result;
}

/**
* DWORD WINAPI GetCurrentProcessorNumber(void);
* �� �Լ��� ȣ�� �� �� ���� �����尡 ���� ���̴� ���μ����� ��ȣ�� ������.
* @author : �ճ���
*
* @param void
* @return  ���� ���̴� ���μ����� ��ȣ.
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
		sprintf(msg, " GetCurrentProcessorNumber() : SUCCESS \n\n ���� �������� thread�� number : %d", result);
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
* ȣ�� �����尡 �������� �� ���μ����� ���μ��� �׷� �� ��ȣ�� �˻�.
* @author : �ճ���
*
* @param �� ���μ����� �Ҵ� �� ���μ��� �׷�� �ش� �׷� ���� �� ���μ��� ��ȣ�� ���� �ϴ� PROCESSOR_NUMBER ����ü�� ���� ������ .
* @return ����.
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

	//�����ִ� �����尡 �������� �� ���μ����� �׷� �� ��ȣ ������
	GetCurrentProcessorNumberEx(&ProcNumber);

	result1 = GetActiveProcessorGroupCount();
	result2 = GetCurrentProcessorNumber();

	if(result1 != -1 && result2 != -1){
		sprintf(msg, "GetCurrentProcessorNumberEx() : SUCCESS \n\nȰ�� ���μ��� �׷� ���� : %d \n���� �������� thread�� number : %d", result1, result2);
		//sprintf(msg, " FlushProcessWriteBuffers() : SUCCESS \n\n Flush �� __rdtsc = %d \n Flush �� __rdtsc = %d ", t1, t2);
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
* �� ���μ��� �� ���� �ϵ������ ���迡 ���� ������ �˻� 
* @author : �ճ���
*
* @param RelationshipType �˻� �� ������ ����
* @param Buffer SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX ����ü �� �迭���޴� ���ۿ� ���� ������
* @ReturnedLength �Է½�, Buffer�� ����Ű�� ������ ���̸� ����Ʈ ������ ����
* @return �˻� ���� �� TRUE ��ȯ�� ���ÿ�, �ϳ� �̻��� SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX ������ ��� ���ۿ� ��ϵ�.
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
* ���μ��� �׷� �Ǵ� �ý����� ���� ���ִ� �� ���μ����� �ִ� ���� ��ȯ
* @author : �ճ���
*
* @param GroupNumber ���μ��� �׷� ��ȣ.
* @return ���μ��� ��
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
		sprintf(msg, " GetMaximumProcessorCount() : SUCCESS \n\n ���μ��� �ִ밪 = %d", result);
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
* ������ ����� ���μ��� ����ũ�� �˻���.
* @author : �ճ���
*
* @param Node ��� ��ȣ.
* @param ProcessorMask ����� ���μ��� ����ũ.
* @return ����ũ �˻� ����/���� ����.
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
* ��尡 ���� ���μ��� �׷쿡 ������� ����� ���μ��� ����ũ�� �˻�
* @author : �ճ���
*
* @param Node ��� ��ȣ.
* @param ProcessorMask ������ ��忡 ���� ���μ��� ����ũ���޴� GROUP_AFFINITY ����ü�� ���� ������ .
* @return ����ũ �˻� ����/���� ����.
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
* ������ �� ���μ��� �� USHORT �� ���� ��� ��ȣ�� �˻�.
* @author : �ճ���
*
* @param Processor �� ���μ����� �Ҵ� �� ���μ��� �׷��� ��Ÿ���� PROCESSOR_NUMBER ����ü�� ���� ������.
* @param NodeNumber ��� ��ȣ������ ������ ���� ������.
* @return ��� ��ȣ �˻� ����/���� ����.
*/

//��� ��ȣ ������
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


