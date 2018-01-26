#include "TestRtlCapture.h"


/**
* VOID WINAPI RtlCaptureContext(
  _Out_ PCONTEXT ContextRecord
);
* 호출 원래의 컨텍스트에서 컨텍스트 레코드를 검색한다.
* @author : 손찬영  
*
* @param  ContextRecord CONTEXT 구조체에 대한 포인터
* @return				없음
*/
BOOL test_RtlCaptureContext()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	PCONTEXT contextRecord = (PCONTEXT)malloc(sizeof(CONTEXT)*BUFSIZ);

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	RtlCaptureContext(contextRecord);

	if(contextRecord != NULL){
		sprintf(msg, "RtlCaptureContext 성공 : %d", contextRecord->ContextFlags);
		strcpy(buf, "RtlCaptureContext 성공");

	}else{
		sprintf(msg, "RtlCaptureContext 실패");
		strcpy(buf, msg);
		result = FALSE;	
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "RtlCaptureContext 성공", msg);

	return result;
}



/**
* USHORT RtlCaptureStackBackTrace(
  _In_      ULONG  FramesToSkip,
  _In_      ULONG  FramesToCapture,
  _Out_     PVOID  *BackTrace,
  _Out_opt_ PULONG BackTraceHash
);
* 스택을 걸어 각 프레임에 대한 정보를 기록하여 스택 백 트레이스를 캡처한다.
* @author : 손찬영  
*
* @param  FramesToSkip		백 트레이스의 시작 부분에서 건너 뛸 프레임 수
* @param  FramesToCapture	캡처 할 프레임 수
* @param  BackTrace			현재 스택 추적에서 캡처 된 포인터의 배열
* @param  BackTraceHash		해시 테이블을 구성하는 데 사용할 수있는 선택적 값
* @return					캡처 된 프레임의 수
*/
BOOL test_RtlCaptureStackBackTrace()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	
	USHORT nCapCnt = 0;
	const ULONG FramesToCapture = 10;
	PVOID BackTrace[FramesToCapture] = {NULL, };

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	nCapCnt = RtlCaptureStackBackTrace(0, FramesToCapture, BackTrace, NULL);

	/*for(USHORT i=0; i<FramesToCapture; i++){
		//읽어올 정보..
	}*/
	if(FramesToCapture == nCapCnt){
		sprintf(msg, "RtlCaptureStackBackTrace 성공 : nCapCnt = %d", nCapCnt);
		strcpy(buf, "RtlCaptureStackBackTrace 성공");

	}else{
		sprintf(msg, "RtlCaptureStackBackTrace 실패\nnCapCnt = %d", nCapCnt);
		strcpy(buf, "RtlCaptureStackBackTrace 실패");

		result = FALSE;
	}


	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "RtlCaptureStackBackTrace 성공", msg);

	return result;
}