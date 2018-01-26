#include "TestProcThreadAttribute.h"


/**
* BOOL WINAPI InitializeProcThreadAttributeList(
  _Out_opt_  LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList,
  _In_       DWORD                        dwAttributeCount,
  _Reserved_ DWORD                        dwFlags,
  _Inout_    PSIZE_T                      lpSize
);
* 프로세스 및 스레드 생성을 위해 지정된 특성 목록을 초기화한다.
* @author : 손찬영  
*
* @param  lpAttributeList	속성리스트 지정된 수의 속성을 지원하는 데 필요한 버퍼 크기를 결정하려면이 매개 변수를 NULL로 지정할 수 있다.
* @param  dwAttributeCount	목록에 추가 할 속성의 수
* @param  dwFlags			예약
* @param  lpSize			pAttributeList가 NULL이 아닌 경우이 매개 변수는 입력시 lpAttributeList 버퍼의 크기 (바이트)를 지정
* @return					성공/실패 여부
*/
BOOL test_InitializeProcThreadAttributeList(void)
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	//UCHAR buffer[4096];  
	//LPPROC_THREAD_ATTRIBUTE_LIST attr = (LPPROC_THREAD_ATTRIBUTE_LIST) buffer; 
	LPPROC_THREAD_ATTRIBUTE_LIST attr;
	SIZE_T size = 0; 
	//ULONG policy = PROCESS_CREATION_MITIGATION_POLICY_WIN32K_SYSTEM_CALL_DISABLE_ALWAYS_ON; 

	GROUP_AFFINITY GrpAffinity = { 0 };
    //GrpAffinity.Mask = 1;


#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif

	/* size를 얻기 위해 NULL로 함수를 호출한다. */
	InitializeProcThreadAttributeList(NULL, 1, 0, &size);
	attr = (LPPROC_THREAD_ATTRIBUTE_LIST)  new UCHAR[size];

	/* 초기 화 전 업데이트 성공 시 테스트 중단 */
	if(UpdateProcThreadAttribute(attr, 0, PROC_THREAD_ATTRIBUTE_GROUP_AFFINITY, &GrpAffinity, sizeof(GrpAffinity), NULL, NULL)){
		sprintf(msg, "초기화 전 UpdateProcThreadAttribute 성공");
		strcpy(buf, "UpdateProcThreadAttribute 성공");

		wresult(__FILE__,__LINE__, __FUNCTION__, buf, "UpdateProcThreadAttribute 실패", msg);

		return FALSE;
	}
	
	/* 초기화 후, 업데이트 성공 시 초기화 성공한 것으로 판단한다. */
	if(InitializeProcThreadAttributeList(attr, 1, 0, &size)){

		if(UpdateProcThreadAttribute(attr , 0, PROC_THREAD_ATTRIBUTE_GROUP_AFFINITY, &GrpAffinity, sizeof(GrpAffinity), NULL, NULL)){
			strcpy(buf, "InitializeProcThreadAttributeList 성공");
			strcpy(msg, buf);
		
		/* 초기화 후 업데이트 실패 */
		}else{
			sprintf(msg, GetErrorMessage("초기화 후 UpdateProcThreadAttribute 실패 : ", GetLastError()));
			strcpy(buf, "UpdateProcThreadAttribute 실패");

			result = FALSE;
		}


	}else{
		sprintf(msg, GetErrorMessage("InitializeProcThreadAttributeList 실패 : ", GetLastError()));
		strcpy(buf, "InitializeProcThreadAttributeList 실패");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "InitializeProcThreadAttributeList 성공", msg);

	return result;
}


/**
* BOOL WINAPI UpdateProcThreadAttribute(
  _Inout_   LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList,
  _In_      DWORD                        dwFlags,
  _In_      DWORD_PTR                    Attribute,
  _In_      PVOID                        lpValue,
  _In_      SIZE_T                       cbSize,
  _Out_opt_ PVOID                        lpPreviousValue,
  _In_opt_  PSIZE_T                      lpReturnSize
);
* 프로세스 및 스레드 생성을 위해 속성 목록에서 지정된 속성을 업데이트한다.
* @author : 손찬영  
*
* @param  lpAttributeList	InitializeProcThreadAttributeList 함수에 의해 작성된 속성 목록에 대한 포인터
* @param  dwFlags			예약
* @param  Attribute			속성리스트로 갱신하는 속성 키. PROC_THREAD_ATTRIBUTE_GROUP_AFFINITY 등
* @param  lpValue			속성 값을 가리키는 포인터.
* @param  cbSize			lpValue 매개 변수로 지정된 속성 값의 크기
* @param  lpPreviousValue	예약		
* @param  lpReturnSize		예약
* @return					성공/실패 여부
*/
BOOL test_UpdateProcThreadAttribute(void)
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	UCHAR buffer[4096];  
	LPPROC_THREAD_ATTRIBUTE_LIST attr = (LPPROC_THREAD_ATTRIBUTE_LIST) buffer; 
	SIZE_T size = 0; 
	GROUP_AFFINITY GrpAffinity = { 0 };
    GrpAffinity.Mask = 1;


#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif

	/* size를 얻기 위해 NULL로 함수를 호출한다. */
	InitializeProcThreadAttributeList(NULL, 1, 0, &size);

	attr = (LPPROC_THREAD_ATTRIBUTE_LIST)  new UCHAR[size];

	/* attr 구조체를 초기화한다 */
	if(!InitializeProcThreadAttributeList(attr, 1, 0, &size)){
		sprintf(msg, GetErrorMessage("InitializeProcThreadAttributeList 실패 : ", GetLastError()));
		strcpy(buf, "InitializeProcThreadAttributeList 실패");

		wresult(__FILE__,__LINE__, __FUNCTION__, buf, "InitializeProcThreadAttributeList 성공", msg);

		return FALSE;
	}
	
	if(UpdateProcThreadAttribute(attr , 0, PROC_THREAD_ATTRIBUTE_GROUP_AFFINITY, &GrpAffinity, sizeof(GrpAffinity), NULL, NULL)){ 
		strcpy(buf, "UpdateProcThreadAttribute 성공");
		strcpy(msg, buf);

	}else{
		sprintf(msg, GetErrorMessage("UpdateProcThreadAttribute 실패 : ", GetLastError()));
		strcpy(buf, "UpdateProcThreadAttribute 실패");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "UpdateProcThreadAttribute 성공", msg);

	return result;
}

/**
* VOID WINAPI DeleteProcThreadAttributeList(
  _Inout_ LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList
);
* 프로세스 및 스레드 생성을 위해 지정된 속성 목록을 삭제한다.
* @author : 손찬영  
*
* @param  lpAttributeList	속성리스트. 이 목록은 InitializeProcThreadAttributeList 함수에 의해 생성
* @return					없음
*/
BOOL test_DeleteProcThreadAttributeList(void)
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	
	DWORD errorCode = 0;

	UCHAR buffer[4096];  
	LPPROC_THREAD_ATTRIBUTE_LIST attr = (LPPROC_THREAD_ATTRIBUTE_LIST) buffer; 
	SIZE_T size = 0; 
	ULONG policy = PROCESS_CREATION_MITIGATION_POLICY_WIN32K_SYSTEM_CALL_DISABLE_ALWAYS_ON; 

	
#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif


	/* size를 얻기 위해 NULL로 함수를 호출한다. */
	InitializeProcThreadAttributeList(NULL, 1, 0, &size);
	attr = (LPPROC_THREAD_ATTRIBUTE_LIST)  new UCHAR[size];

	/* attr를 초기화한다. */
	if(!InitializeProcThreadAttributeList(attr, 1, 0, &size)){
		sprintf(msg, GetErrorMessage("InitializeProcThreadAttributeList 실패 : ", GetLastError()));
		strcpy(buf, "InitializeProcThreadAttributeList 실패");

		wresult(__FILE__,__LINE__, __FUNCTION__, buf, "InitializeProcThreadAttributeList 성공", msg);

		return FALSE;
	}

	/* 초기화 후 업데이트 시 성공해야 함*/
	if(UpdateProcThreadAttribute(attr , 0, PROC_THREAD_ATTRIBUTE_MITIGATION_POLICY, &policy, sizeof(policy), NULL, NULL)){
		
		/* 삭제 시도 */
		DeleteProcThreadAttributeList(attr);

		/* 삭제 후 업데이트 실패하면 성공 */
		if(!UpdateProcThreadAttribute(attr , 0, PROC_THREAD_ATTRIBUTE_MITIGATION_POLICY, &policy, sizeof(policy), NULL, NULL)){
			strcpy(buf, "DeleteProcThreadAttributeList 성공");
			sprintf(msg, buf);

		/* 삭제 후 업데이트 성공하면 실패로 간주한다 */
		}else{
			sprintf(msg, GetErrorMessage("DeleteProcThreadAttributeList 실패 : ", GetLastError()));
			strcpy(buf, "DeleteProcThreadAttributeList 실패");

			result = FALSE;
		}

	/* 삭제 전에 업데이트 시도 시 성공해야 함 (실패하면 테스트 중단) */
	}else{
		
		sprintf(msg, GetErrorMessage("UpdateProcThreadAttribute 실패 : ", GetLastError()));
		strcpy(buf, "UpdateProcThreadAttribute 실패");

		wresult(__FILE__,__LINE__, __FUNCTION__, buf, "UpdateProcThreadAttribute 성공", msg);

		return FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "DeleteProcThreadAttributeList 성공", msg);

	return result;
}