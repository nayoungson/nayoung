#include "TestRtlCapture.h"


/**
* VOID WINAPI RtlCaptureContext(
  _Out_ PCONTEXT ContextRecord
);
* ȣ�� ������ ���ؽ�Ʈ���� ���ؽ�Ʈ ���ڵ带 �˻��Ѵ�.
* @author : ������  
*
* @param  ContextRecord CONTEXT ����ü�� ���� ������
* @return				����
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
		sprintf(msg, "RtlCaptureContext ���� : %d", contextRecord->ContextFlags);
		strcpy(buf, "RtlCaptureContext ����");

	}else{
		sprintf(msg, "RtlCaptureContext ����");
		strcpy(buf, msg);
		result = FALSE;	
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "RtlCaptureContext ����", msg);

	return result;
}



/**
* USHORT RtlCaptureStackBackTrace(
  _In_      ULONG  FramesToSkip,
  _In_      ULONG  FramesToCapture,
  _Out_     PVOID  *BackTrace,
  _Out_opt_ PULONG BackTraceHash
);
* ������ �ɾ� �� �����ӿ� ���� ������ ����Ͽ� ���� �� Ʈ���̽��� ĸó�Ѵ�.
* @author : ������  
*
* @param  FramesToSkip		�� Ʈ���̽��� ���� �κп��� �ǳ� �� ������ ��
* @param  FramesToCapture	ĸó �� ������ ��
* @param  BackTrace			���� ���� �������� ĸó �� �������� �迭
* @param  BackTraceHash		�ؽ� ���̺��� �����ϴ� �� ����� ���ִ� ������ ��
* @return					ĸó �� �������� ��
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
		//�о�� ����..
	}*/
	if(FramesToCapture == nCapCnt){
		sprintf(msg, "RtlCaptureStackBackTrace ���� : nCapCnt = %d", nCapCnt);
		strcpy(buf, "RtlCaptureStackBackTrace ����");

	}else{
		sprintf(msg, "RtlCaptureStackBackTrace ����\nnCapCnt = %d", nCapCnt);
		strcpy(buf, "RtlCaptureStackBackTrace ����");

		result = FALSE;
	}


	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "RtlCaptureStackBackTrace ����", msg);

	return result;
}