#include "TestRecovery.h"

/**
* HRESULT UnregisterApplicationRecoveryCallback(void)
* 복구 목록에서 응용 프로그램의 활성 인스턴스를 제거한다.
* @author : 손찬영  
*
* @param  없음
* @return 성공시 S_OK, 내부 오류 시, E_FAIL
*/
BOOL test_UnregisterApplicationRecoveryCallback()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HRESULT hResult = -1;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif


	if(S_OK == (hResult = UnregisterApplicationRecoveryCallback())){
		sprintf(msg, "UnregisterApplicationRecoveryCallback 성공");
		strcpy(buf, "UnregisterApplicationRecoveryCallback 성공");	

	}else if(E_FAIL == hResult){
		strcpy(msg, "UnregisterApplicationRecoveryCallback 실패 : E_FAIL");
		strcpy(buf, "UnregisterApplicationRecoveryCallback 실패");
		
		result = FALSE;
	}else{
		strcpy(msg, "UnregisterApplicationRecoveryCallback 실패 : 알 수 없는 에러");
		strcpy(buf, "UnregisterApplicationRecoveryCallback 실패");
		
		result = FALSE;

	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "UnregisterApplicationRecoveryCallback 성공", msg);

	return result;
}



DWORD WINAPI ApplicationRecoveryCallback (PVOID pvParameter)
{
	/*BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HRESULT hResult;
	BOOL bCanceled = FALSE;

	if(S_OK == (hResult = ApplicationRecoveryInProgress(&bCanceled))){
		sprintf(msg, "ApplicationRecoveryInProgress 성공");
		strcpy(buf, "ApplicationRecoveryInProgress 성공");	

	}else if(E_FAIL == hResult){
		printf("S_FALSE == hResult\n");
		strcpy(msg, "ApplicationRecoveryInProgress 실패 : Windows 오류보고에서 복구 콜백 함수를 호출 한 후에 만이 함수를 호출 할 수 있습니다.");
		strcpy(buf, "ApplicationRecoveryInProgress 실패");
		
		result = FALSE;
	}else if(E_INVALIDARG == hResult){
		strcpy(msg, "ApplicationRecoveryInProgress 실패 : pbCancelled cannot be NULL.");
		strcpy(buf, "ApplicationRecoveryInProgress 실패");
		
		result = FALSE;
	
	}else{
		sprintf(msg, "ApplicationRecoveryInProgress 실패 : 알 수 없는 에러\nhResult = %d", hResult);
		strcpy(buf, "ApplicationRecoveryInProgress 실패");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ApplicationRecoveryInProgress 성공", msg);*/
	return 0;
}


/**
* HRESULT RegisterApplicationRecoveryCallback(APPLICATION_RECOVERY_CALLBACK pRecoveryCallback,PVOID pvParameter, DWORD dwPingInterval, DWORD dwFlags)
* 복구를 위해 응용 프로그램의 활성 인스턴스를 등록한다.
* @author : 손찬영  
*
* @param  pRecoveryCallback 복구 콜백 함수에 대한 포인터
* @param  pvParameter 콜백 함수에 전달할 변수에 대한 포인터
* @param  dwPingInterval 복구 핑 간격 (밀리 초)
* @param  dwFlags 예약
* @return 성공시 S_OK, 내부 오류 시, E_FAIL, ping 간격 5분초과 시, E_INVALIDARG
*/
BOOL test_RegisterApplicationRecoveryCallback()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	APPLICATION_RECOVERY_CALLBACK pRecoveryCallback = ApplicationRecoveryCallback;
	DWORD dwPingInterval = RECOVERY_DEFAULT_PING_INTERVAL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	HRESULT hResult = -1;


	if(S_OK == (hResult = RegisterApplicationRecoveryCallback(pRecoveryCallback, NULL, dwPingInterval, 0))){
		sprintf(msg, "RegisterApplicationRecoveryCallback 성공");
		strcpy(buf, "RegisterApplicationRecoveryCallback 성공");	

	}else if(E_FAIL == hResult){
		strcpy(msg, "RegisterApplicationRecoveryCallback 실패 : 내부 오류; 등록에 실패했습니다.");
		strcpy(buf, "RegisterApplicationRecoveryCallback 실패");
		
		result = FALSE;
	}else if(E_INVALIDARG == hResult){
		strcpy(msg, "RegisterApplicationRecoveryCallback 실패 : ping 간격은 5 분을 초과 할 수 없습니다.");
		strcpy(buf, "RegisterApplicationRecoveryCallback 실패");
		
		result = FALSE;
	
	}else{
		strcpy(msg, "RegisterApplicationRecoveryCallback 실패 : 알 수 없는 에러");
		strcpy(buf, "RegisterApplicationRecoveryCallback 실패");
		
		result = FALSE;

	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "RegisterApplicationRecoveryCallback 성공", msg);

	UnregisterApplicationRecoveryCallback();

	return result;
}

/**
* HRESULT GetApplicationRecoveryCallback(HANDLE hProcess, APPLICATION_RECOVERY_CALLBACK *pRecoveryCallback, PVOID *ppvParameter, PDWORD pdwPingInterval, PDWORD pdwFlags)
* 지정된 프로세스에 대해 등록 된 콜백 루틴에 대한 포인터를 검색한다.
* @author : 손찬영  
*
* @param  hProcess 프로세스에 대한 핸들. 
* @param  pRecoveryCallback 복구 콜백 함수에 대한 포인터
* @param  ppvParameter 콜백 매개 변수에 대한 포인터
* @param  pdwPingInterval 100 나노초 간격으로 복구 핑 간격
* @param  pdwFlags 예약
* @return 성공시 S_OK, 내부 오류 시, E_FAIL, 매개변수 유효하지 않은 경우, E_INVALIDARG.
*/
BOOL test_GetApplicationRecoveryCallback()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	HRESULT hResult = -1;
	HANDLE hProcess = GetCurrentProcess();
	APPLICATION_RECOVERY_CALLBACK RecoveryCallback = ApplicationRecoveryCallback;
	DWORD Parameter = 0;
	PVOID pvParameter = &Parameter;
	PVOID *ppvParameter = &pvParameter;
	//DWORD dwPingInterval = RECOVERY_DEFAULT_PING_INTERVAL;
	DWORD expectPingInterval = 3456;
	DWORD dwPingInterval = 0;
	DWORD dwFlags = 0;


	/* ApplicationRecoveryCallback 함수를 등록한다 */
	if(S_OK != (hResult = RegisterApplicationRecoveryCallback(RecoveryCallback, NULL, expectPingInterval, 0))){
		sprintf(msg, "RegisterApplicationRecoveryCallback 실패");
		strcpy(buf, "RegisterApplicationRecoveryCallback 실패");	

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "RegisterApplicationRecoveryCallback 성공", msg);

		return FALSE;
	}

	
	/* 등록되어있는 ApplicationRecoveryCallback 정보를 가져온다 */
	if(S_OK == (hResult = GetApplicationRecoveryCallback(hProcess, &RecoveryCallback, ppvParameter, &dwPingInterval, &dwFlags))){
		
		/* dwPingInterval을 0으로 초기화 하고 기존에 등록된 핑인터벌 값으로 가져오면 성공으로 판단한다. */
		if(dwPingInterval == expectPingInterval){
			sprintf(msg, "GetApplicationRecoveryCallback 성공 : dwPingInterval = %d", dwPingInterval);
			strcpy(buf, "GetApplicationRecoveryCallback 성공");	

		/* 함수는 성공했지만 등록한 핑 인터벌과 Get한 핑 인터벌이 서로 다른 경우 */
		}else{
			sprintf(msg, "GetApplicationRecoveryCallback 실패 : dwPingInterval = %d, expectPingInterval = %d", dwPingInterval, expectPingInterval);
			strcpy(buf, "GetApplicationRecoveryCallback 실패");

			result = FALSE;
		}

	}else if(S_FALSE == hResult){
		strcpy(msg, "GetApplicationRecoveryCallback 실패 : 응용 프로그램이 복구를 위해 등록하지 않았습니다.");
		strcpy(buf, "GetApplicationRecoveryCallback 실패");
		
		result = FALSE;

	/* 하나 이상의 매개 변수가 유효하지 않습니다. */
	}else if(E_INVALIDARG == hResult){
		strcpy(msg, "GetApplicationRecoveryCallback 실패 : 하나 이상의 매개 변수가 유효하지 않습니다.");
		strcpy(buf, "GetApplicationRecoveryCallback 실패");
		
		result = FALSE;
	
	}else if(HRESULT_FROM_WIN32(ERROR_NOT_FOUND) == hResult){
		strcpy(msg, "GetApplicationRecoveryCallback 실패 : 요소가 없습니다.");
		strcpy(buf, "GetApplicationRecoveryCallback 실패");
		
		result = FALSE;
	}else{
		sprintf(msg, "GetApplicationRecoveryCallback 실패 : 알 수 없는 에러\nhResult = %d", hResult);
		strcpy(buf, "GetApplicationRecoveryCallback 실패");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetApplicationRecoveryCallback 성공", msg);

	UnregisterApplicationRecoveryCallback();

	return result;
}

/**
* HRESULT ApplicationRecoveryInProgress(PBOOL pbCanceled)
* 호출 응용 프로그램이 계속 데이터를 복구하고 있음을 나타낸다.
* @author : 손찬영  
*
* @param  pbCanceled 사용자가 복구 프로세스를 취소했는지 여부
* @return 성공시 S_OK, Windows 오류보고에서 복구 콜백 함수를 호출 한 후에 만이 함수를 호출 가능 E_FAIL, 매개변수 유효하지 않은 경우, E_INVALIDARG.
*/
BOOL test_ApplicationRecoveryInProgress()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	BOOL bCanceled = TRUE;
	HRESULT hResult = -1;
	PCWSTR                  pwzEventType = L"MyEvent";
	WER_REPORT_TYPE         repType = WerReportNonCritical;
	HREPORT                 hReport = NULL;

	//for WerReportSubmit function
	WER_CONSENT        consent = WerConsentNotAsked;
	DWORD              dwFlags = WER_SUBMIT_HONOR_RECOVERY;

	//for RegisterApplicationRecoveryCallback function
	APPLICATION_RECOVERY_CALLBACK RecoveryCallback = ApplicationRecoveryCallback;
	DWORD dwPingInterval = RECOVERY_MAX_PING_INTERVAL;

	/*if(S_OK != WerReportCreate(pwzEventType, repType, NULL, &hReport)){
		sprintf(msg, "WerReportCreate 실패");
		strcpy(buf, "WerReportCreate 실패");	

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "WerReportCreate 성공", msg);

		return FALSE;
	}

	if(S_OK != WerReportSubmit(hReport, consent, dwFlags, NULL)){
		sprintf(msg, "WerReportCreate 실패");
		strcpy(buf, "WerReportCreate 실패");	

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "WerReportCreate 성공", msg);

		return FALSE;
	}*/
	
	if(S_OK != (hResult = RegisterApplicationRecoveryCallback(RecoveryCallback, NULL, dwPingInterval, 0))){
		sprintf(msg, "RegisterApplicationRecoveryCallback 실패");
		strcpy(buf, "RegisterApplicationRecoveryCallback 실패");	

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "RegisterApplicationRecoveryCallback 성공", msg);

		return FALSE;
	}
	if(S_OK == (hResult = ApplicationRecoveryInProgress(&bCanceled))){
		sprintf(msg, "ApplicationRecoveryInProgress 성공");
		strcpy(buf, "ApplicationRecoveryInProgress 성공");	

	}else if(E_FAIL == hResult){
		printf("S_FALSE == hResult\n");
		strcpy(msg, "ApplicationRecoveryInProgress 실패 : Windows 오류보고에서 복구 콜백 함수를 호출 한 후에 만이 함수를 호출 할 수 있습니다.");
		strcpy(buf, "ApplicationRecoveryInProgress 실패");
		
		result = FALSE;
	}else if(E_INVALIDARG == hResult){
		strcpy(msg, "ApplicationRecoveryInProgress 실패 : pbCancelled cannot be NULL.");
		strcpy(buf, "ApplicationRecoveryInProgress 실패");
		
		result = FALSE;
	
	}else{
		sprintf(msg, "ApplicationRecoveryInProgress 실패 : 알 수 없는 에러\nhResult = %d", hResult);
		strcpy(buf, "ApplicationRecoveryInProgress 실패");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ApplicationRecoveryInProgress 성공", msg);
	

	//UnregisterApplicationRecoveryCallback();

	//WerReportCloseHandle(hReport);

	return result;
}

/**
* VOID ApplicationRecoveryFinished(BOOL bSuccess)
* 호출 응용 프로그램이 데이터 복구를 완료했음을 나타낸다.
* @author : 손찬영  
*
* @param  bSuccess 데이터가 성공적으로 복구되었음을 나타내려면 TRUE 를 지정
* @return 없음
*/
BOOL test_ApplicationRecoveryFinished()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	BOOL bSuccess = TRUE;
	HRESULT hResult = -1;
	PCWSTR                  pwzEventType = L"MyEvent";
	WER_REPORT_TYPE         repType = WerReportNonCritical;


	try{
		ApplicationRecoveryFinished(bSuccess);

		sprintf(msg, "ApplicationRecoveryFinished 성공");
		strcpy(buf, "ApplicationRecoveryFinished 성공");	

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ApplicationRecoveryFinished 성공", msg);
	}
	catch(int exceptionCode){
		strcpy(msg, "ApplicationRecoveryFinished 실패");
		strcpy(buf, "ApplicationRecoveryFinished 실패");
		
		result = FALSE;

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ApplicationRecoveryFinished 성공", msg);

		return result;
	}	

	//wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ApplicationRecoveryInProgress 성공", msg);

	return result;
}