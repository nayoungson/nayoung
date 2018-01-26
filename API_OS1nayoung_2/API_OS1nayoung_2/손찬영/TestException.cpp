#include "TestException.h"


/**
* void WINAPI RaiseException(
  _In_       DWORD     dwExceptionCode,
  _In_       DWORD     dwExceptionFlags,
  _In_       DWORD     nNumberOfArguments,
  _In_ const ULONG_PTR *lpArguments
);
* ȣ�� �����忡�� ���ܸ� �߻���Ų��.
* @author : ������  
*
* @param  dwExceptionCode		�߻��� ������ ���� ���α׷� ���� ���� �ڵ�
* @param  dwExceptionFlags		���� �÷���. �� ���� ��ӵǴ� ���ܸ� ��Ÿ���� ���� 0, �� �������� ���ܸ� ��Ÿ���� ���� EXCEPTION_NONCONTINUABLE
* @param  nNumberOfArguments	lpArguments �迭 �� �μ� ����
* @param  lpArguments			�μ��� �迭
* @return						����
*/
BOOL test_RaiseException()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	//char buf[BUFSIZ];
	DWORD errorCode=0;

	//FilterFuncion Finally Except
	__try { 
		#ifdef OQADBGPRINT
		printf("test_RaiseException\n");
		#endif
		RaiseException( EXCEPTION_EXECUTE_HANDLER, // exception code 
			0, // continuable exception 
			0, NULL); // no arguments 

	} 
	__except ( EXCEPTION_EXECUTE_HANDLER ) { 
		#ifdef OQADBGPRINT
		printf("���� �߻�\n"); // this is printed last 
		#endif
		sprintf(msg, "���� �߻� ����");
		wresult(__FILE__,__LINE__ ,"RaiseException", msg, "���� �߻� ����", msg);

		return TRUE;
	}
	result = FALSE;
	sprintf(msg, "���� �߻� ����");
	wresult(__FILE__,__LINE__ ,"RaiseException", msg, "���� �߻� ����", msg);

	return result;
}


/**
* VOID WINAPI RaiseFailFastException(
  _In_opt_ PEXCEPTION_RECORD pExceptionRecord,
  _In_opt_ PCONTEXT          pContextRecord,
  _In_     DWORD             dwFlags
);
* ��� ���� ó���� (������ �Ǵ� ���� ���)�� ��ȸ�ϴ� ���ܸ� �߻���Ų��.
�� ���ܸ� �߻� ��Ű�� ���� ���α׷��� ����ǰ� Windows �������� ��� ������ ��� Windows �������� ȣ��ȴ�.
* @author : ������  
*
* @param  pExceptionRecord	���� ������ ��� �ִ� EXCEPTION_RECORD ����ü�� ���� ������
* @param  pContextRecord	���ؽ�Ʈ ������ ���� �ϴ� CONTEXT ����ü�� ���� ������
* @param  dwFlags			�� �Լ��� ������ �����ϴ� �÷���.
* @return					����
*/
 BOOL test_RaiseFailFastException() //�����Ұ�
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	DWORD errorCode=0;

	

	#ifdef OQADBGPRINT
		printf("test_RaiseFailFastException\n");
	#endif

	//result = FastCallFunction(1, 2, 3, 4);
	
	if(!result){
		result = FALSE;
		sprintf(msg, "���� �߻� ����");

	}else{
		//result = FALSE;
		sprintf(msg, "���� �߻� ����");

	}
	

	//wresult(__FILE__,__LINE__ ,__FUNCTION__ , msg, "���� �߻� ����", msg);

	return FALSE;

}

 BOOL __fastcall FastCallFunction(int a, int b, int c, int d)
 {
	 char msg[BUFSIZ];
	 PEXCEPTION_RECORD exceptionRecord;
	 //FilterFuncion Finally Except
//	 __try { 
//#ifdef OQADBGPRINT
//		 printf("test_RaiseException\n");
//#endif
//
//		 if(!(exceptionRecord = (PEXCEPTION_RECORD)malloc(sizeof(EXCEPTION_RECORD)*BUFSIZ))){
//		 printf(" exceptionRecord malloc fail\n");
//		 wresult(__FILE__,__LINE__ ,__FUNCTION__ , "exceptionRecord malloc ����", "exceptionRecord malloc ����", msg);
//
//		 return FALSE;
//		 }
//
//		 //RaiseException( EXCEPTION_EXECUTE_HANDLER, // exception code 
//		 //	0, // continuable exception 
//		 //	0, NULL); // no arguments 
//		 //exceptionRecord->ExceptionCode = EXCEPTION_EXECUTE_HANDLER;
//		// exceptionRecord.ExceptionFlags = 0;
//		// exceptionRecord.NumberParameters = 0;
//
//		// exceptionRecord.ExceptionAddress = NULL;
//		// exceptionRecord.ExceptionInformation[0] = NULL;
//		// exceptionRecord.ExceptionRecord = NULL;
//	
//		 RaiseFailFastException(NULL, NULL, 0);
//
//
//	 	//RaiseFailFastException(&exceptionRecord, NULL, 0);
//	 	//RaiseFailFastException(exceptionRecord, NULL, 0);
//
//	 } 
//	 //__except ( EXCEPTION_EXECUTE_HANDLER ) { 
//	 __except ( EXCEPTION_EXECUTE_HANDLER ) { 
//	 	#ifdef OQADBGPRINT
//	 	printf("���� �߻�\n"); // this is printed last 
//	 	#endif
//	 	sprintf(msg, "���� �߻� ����");
//	 	wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "���� �߻� ����", msg);
//
//	 	return TRUE;
//	 }

	 try{
		 //throw 1;
		 if(!(exceptionRecord = (PEXCEPTION_RECORD)malloc(sizeof(EXCEPTION_RECORD)*BUFSIZ))){
		 printf(" exceptionRecord malloc fail\n");
		 wresult(__FILE__,__LINE__ ,__FUNCTION__ , "exceptionRecord malloc ����", "exceptionRecord malloc ����", msg);

		 return FALSE;
		 }
		 exceptionRecord->ExceptionCode = EXCEPTION_EXECUTE_HANDLER;
		 RaiseFailFastException(exceptionRecord, NULL, 0);
		 //throw 1;

	 }catch(int exception){
		 printf("exceptionCode = %d\n", exception);

		 return TRUE;
	 }
	 
	 return FALSE;
 }