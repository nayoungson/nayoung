#include "TestException.h"


/**
* void WINAPI RaiseException(
  _In_       DWORD     dwExceptionCode,
  _In_       DWORD     dwExceptionFlags,
  _In_       DWORD     nNumberOfArguments,
  _In_ const ULONG_PTR *lpArguments
);
* 호출 스레드에서 예외를 발생시킨다.
* @author : 손찬영  
*
* @param  dwExceptionCode		발생한 예외의 응용 프로그램 정의 예외 코드
* @param  dwExceptionFlags		예외 플래그. 이 값은 계속되는 예외를 나타내는 경우는 0, 비 연속적인 예외를 나타내는 경우는 EXCEPTION_NONCONTINUABLE
* @param  nNumberOfArguments	lpArguments 배열 의 인수 개수
* @param  lpArguments			인수의 배열
* @return						없음
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
		printf("예외 발생\n"); // this is printed last 
		#endif
		sprintf(msg, "예외 발생 성공");
		wresult(__FILE__,__LINE__ ,"RaiseException", msg, "예외 발생 성공", msg);

		return TRUE;
	}
	result = FALSE;
	sprintf(msg, "예외 발생 실패");
	wresult(__FILE__,__LINE__ ,"RaiseException", msg, "예외 발생 성공", msg);

	return result;
}


/**
* VOID WINAPI RaiseFailFastException(
  _In_opt_ PEXCEPTION_RECORD pExceptionRecord,
  _In_opt_ PCONTEXT          pContextRecord,
  _In_     DWORD             dwFlags
);
* 모든 예외 처리기 (프레임 또는 벡터 기반)를 우회하는 예외를 발생시킨다.
이 예외를 발생 시키면 응용 프로그램이 종료되고 Windows 오류보고가 사용 가능한 경우 Windows 오류보고가 호출된다.
* @author : 손찬영  
*
* @param  pExceptionRecord	예외 정보가 들어 있는 EXCEPTION_RECORD 구조체에 대한 포인터
* @param  pContextRecord	컨텍스트 정보를 포함 하는 CONTEXT 구조체에 대한 포인터
* @param  dwFlags			이 함수의 동작을 제어하는 플래그.
* @return					없음
*/
 BOOL test_RaiseFailFastException() //구현불가
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
		sprintf(msg, "예외 발생 실패");

	}else{
		//result = FALSE;
		sprintf(msg, "예외 발생 성공");

	}
	

	//wresult(__FILE__,__LINE__ ,__FUNCTION__ , msg, "예외 발생 성공", msg);

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
//		 wresult(__FILE__,__LINE__ ,__FUNCTION__ , "exceptionRecord malloc 실패", "exceptionRecord malloc 성공", msg);
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
//	 	printf("예외 발생\n"); // this is printed last 
//	 	#endif
//	 	sprintf(msg, "예외 발생 성공");
//	 	wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "예외 발생 성공", msg);
//
//	 	return TRUE;
//	 }

	 try{
		 //throw 1;
		 if(!(exceptionRecord = (PEXCEPTION_RECORD)malloc(sizeof(EXCEPTION_RECORD)*BUFSIZ))){
		 printf(" exceptionRecord malloc fail\n");
		 wresult(__FILE__,__LINE__ ,__FUNCTION__ , "exceptionRecord malloc 실패", "exceptionRecord malloc 성공", msg);

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