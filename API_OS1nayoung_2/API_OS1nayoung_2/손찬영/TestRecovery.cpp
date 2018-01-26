#include "TestRecovery.h"

/**
* HRESULT UnregisterApplicationRecoveryCallback(void)
* ���� ��Ͽ��� ���� ���α׷��� Ȱ�� �ν��Ͻ��� �����Ѵ�.
* @author : ������  
*
* @param  ����
* @return ������ S_OK, ���� ���� ��, E_FAIL
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
		sprintf(msg, "UnregisterApplicationRecoveryCallback ����");
		strcpy(buf, "UnregisterApplicationRecoveryCallback ����");	

	}else if(E_FAIL == hResult){
		strcpy(msg, "UnregisterApplicationRecoveryCallback ���� : E_FAIL");
		strcpy(buf, "UnregisterApplicationRecoveryCallback ����");
		
		result = FALSE;
	}else{
		strcpy(msg, "UnregisterApplicationRecoveryCallback ���� : �� �� ���� ����");
		strcpy(buf, "UnregisterApplicationRecoveryCallback ����");
		
		result = FALSE;

	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "UnregisterApplicationRecoveryCallback ����", msg);

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
		sprintf(msg, "ApplicationRecoveryInProgress ����");
		strcpy(buf, "ApplicationRecoveryInProgress ����");	

	}else if(E_FAIL == hResult){
		printf("S_FALSE == hResult\n");
		strcpy(msg, "ApplicationRecoveryInProgress ���� : Windows ���������� ���� �ݹ� �Լ��� ȣ�� �� �Ŀ� ���� �Լ��� ȣ�� �� �� �ֽ��ϴ�.");
		strcpy(buf, "ApplicationRecoveryInProgress ����");
		
		result = FALSE;
	}else if(E_INVALIDARG == hResult){
		strcpy(msg, "ApplicationRecoveryInProgress ���� : pbCancelled cannot be NULL.");
		strcpy(buf, "ApplicationRecoveryInProgress ����");
		
		result = FALSE;
	
	}else{
		sprintf(msg, "ApplicationRecoveryInProgress ���� : �� �� ���� ����\nhResult = %d", hResult);
		strcpy(buf, "ApplicationRecoveryInProgress ����");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ApplicationRecoveryInProgress ����", msg);*/
	return 0;
}


/**
* HRESULT RegisterApplicationRecoveryCallback(APPLICATION_RECOVERY_CALLBACK pRecoveryCallback,PVOID pvParameter, DWORD dwPingInterval, DWORD dwFlags)
* ������ ���� ���� ���α׷��� Ȱ�� �ν��Ͻ��� ����Ѵ�.
* @author : ������  
*
* @param  pRecoveryCallback ���� �ݹ� �Լ��� ���� ������
* @param  pvParameter �ݹ� �Լ��� ������ ������ ���� ������
* @param  dwPingInterval ���� �� ���� (�и� ��)
* @param  dwFlags ����
* @return ������ S_OK, ���� ���� ��, E_FAIL, ping ���� 5���ʰ� ��, E_INVALIDARG
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
		sprintf(msg, "RegisterApplicationRecoveryCallback ����");
		strcpy(buf, "RegisterApplicationRecoveryCallback ����");	

	}else if(E_FAIL == hResult){
		strcpy(msg, "RegisterApplicationRecoveryCallback ���� : ���� ����; ��Ͽ� �����߽��ϴ�.");
		strcpy(buf, "RegisterApplicationRecoveryCallback ����");
		
		result = FALSE;
	}else if(E_INVALIDARG == hResult){
		strcpy(msg, "RegisterApplicationRecoveryCallback ���� : ping ������ 5 ���� �ʰ� �� �� �����ϴ�.");
		strcpy(buf, "RegisterApplicationRecoveryCallback ����");
		
		result = FALSE;
	
	}else{
		strcpy(msg, "RegisterApplicationRecoveryCallback ���� : �� �� ���� ����");
		strcpy(buf, "RegisterApplicationRecoveryCallback ����");
		
		result = FALSE;

	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "RegisterApplicationRecoveryCallback ����", msg);

	UnregisterApplicationRecoveryCallback();

	return result;
}

/**
* HRESULT GetApplicationRecoveryCallback(HANDLE hProcess, APPLICATION_RECOVERY_CALLBACK *pRecoveryCallback, PVOID *ppvParameter, PDWORD pdwPingInterval, PDWORD pdwFlags)
* ������ ���μ����� ���� ��� �� �ݹ� ��ƾ�� ���� �����͸� �˻��Ѵ�.
* @author : ������  
*
* @param  hProcess ���μ����� ���� �ڵ�. 
* @param  pRecoveryCallback ���� �ݹ� �Լ��� ���� ������
* @param  ppvParameter �ݹ� �Ű� ������ ���� ������
* @param  pdwPingInterval 100 ������ �������� ���� �� ����
* @param  pdwFlags ����
* @return ������ S_OK, ���� ���� ��, E_FAIL, �Ű����� ��ȿ���� ���� ���, E_INVALIDARG.
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


	/* ApplicationRecoveryCallback �Լ��� ����Ѵ� */
	if(S_OK != (hResult = RegisterApplicationRecoveryCallback(RecoveryCallback, NULL, expectPingInterval, 0))){
		sprintf(msg, "RegisterApplicationRecoveryCallback ����");
		strcpy(buf, "RegisterApplicationRecoveryCallback ����");	

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "RegisterApplicationRecoveryCallback ����", msg);

		return FALSE;
	}

	
	/* ��ϵǾ��ִ� ApplicationRecoveryCallback ������ �����´� */
	if(S_OK == (hResult = GetApplicationRecoveryCallback(hProcess, &RecoveryCallback, ppvParameter, &dwPingInterval, &dwFlags))){
		
		/* dwPingInterval�� 0���� �ʱ�ȭ �ϰ� ������ ��ϵ� �����͹� ������ �������� �������� �Ǵ��Ѵ�. */
		if(dwPingInterval == expectPingInterval){
			sprintf(msg, "GetApplicationRecoveryCallback ���� : dwPingInterval = %d", dwPingInterval);
			strcpy(buf, "GetApplicationRecoveryCallback ����");	

		/* �Լ��� ���������� ����� �� ���͹��� Get�� �� ���͹��� ���� �ٸ� ��� */
		}else{
			sprintf(msg, "GetApplicationRecoveryCallback ���� : dwPingInterval = %d, expectPingInterval = %d", dwPingInterval, expectPingInterval);
			strcpy(buf, "GetApplicationRecoveryCallback ����");

			result = FALSE;
		}

	}else if(S_FALSE == hResult){
		strcpy(msg, "GetApplicationRecoveryCallback ���� : ���� ���α׷��� ������ ���� ������� �ʾҽ��ϴ�.");
		strcpy(buf, "GetApplicationRecoveryCallback ����");
		
		result = FALSE;

	/* �ϳ� �̻��� �Ű� ������ ��ȿ���� �ʽ��ϴ�. */
	}else if(E_INVALIDARG == hResult){
		strcpy(msg, "GetApplicationRecoveryCallback ���� : �ϳ� �̻��� �Ű� ������ ��ȿ���� �ʽ��ϴ�.");
		strcpy(buf, "GetApplicationRecoveryCallback ����");
		
		result = FALSE;
	
	}else if(HRESULT_FROM_WIN32(ERROR_NOT_FOUND) == hResult){
		strcpy(msg, "GetApplicationRecoveryCallback ���� : ��Ұ� �����ϴ�.");
		strcpy(buf, "GetApplicationRecoveryCallback ����");
		
		result = FALSE;
	}else{
		sprintf(msg, "GetApplicationRecoveryCallback ���� : �� �� ���� ����\nhResult = %d", hResult);
		strcpy(buf, "GetApplicationRecoveryCallback ����");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetApplicationRecoveryCallback ����", msg);

	UnregisterApplicationRecoveryCallback();

	return result;
}

/**
* HRESULT ApplicationRecoveryInProgress(PBOOL pbCanceled)
* ȣ�� ���� ���α׷��� ��� �����͸� �����ϰ� ������ ��Ÿ����.
* @author : ������  
*
* @param  pbCanceled ����ڰ� ���� ���μ����� ����ߴ��� ����
* @return ������ S_OK, Windows ���������� ���� �ݹ� �Լ��� ȣ�� �� �Ŀ� ���� �Լ��� ȣ�� ���� E_FAIL, �Ű����� ��ȿ���� ���� ���, E_INVALIDARG.
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
		sprintf(msg, "WerReportCreate ����");
		strcpy(buf, "WerReportCreate ����");	

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "WerReportCreate ����", msg);

		return FALSE;
	}

	if(S_OK != WerReportSubmit(hReport, consent, dwFlags, NULL)){
		sprintf(msg, "WerReportCreate ����");
		strcpy(buf, "WerReportCreate ����");	

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "WerReportCreate ����", msg);

		return FALSE;
	}*/
	
	if(S_OK != (hResult = RegisterApplicationRecoveryCallback(RecoveryCallback, NULL, dwPingInterval, 0))){
		sprintf(msg, "RegisterApplicationRecoveryCallback ����");
		strcpy(buf, "RegisterApplicationRecoveryCallback ����");	

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "RegisterApplicationRecoveryCallback ����", msg);

		return FALSE;
	}
	if(S_OK == (hResult = ApplicationRecoveryInProgress(&bCanceled))){
		sprintf(msg, "ApplicationRecoveryInProgress ����");
		strcpy(buf, "ApplicationRecoveryInProgress ����");	

	}else if(E_FAIL == hResult){
		printf("S_FALSE == hResult\n");
		strcpy(msg, "ApplicationRecoveryInProgress ���� : Windows ���������� ���� �ݹ� �Լ��� ȣ�� �� �Ŀ� ���� �Լ��� ȣ�� �� �� �ֽ��ϴ�.");
		strcpy(buf, "ApplicationRecoveryInProgress ����");
		
		result = FALSE;
	}else if(E_INVALIDARG == hResult){
		strcpy(msg, "ApplicationRecoveryInProgress ���� : pbCancelled cannot be NULL.");
		strcpy(buf, "ApplicationRecoveryInProgress ����");
		
		result = FALSE;
	
	}else{
		sprintf(msg, "ApplicationRecoveryInProgress ���� : �� �� ���� ����\nhResult = %d", hResult);
		strcpy(buf, "ApplicationRecoveryInProgress ����");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ApplicationRecoveryInProgress ����", msg);
	

	//UnregisterApplicationRecoveryCallback();

	//WerReportCloseHandle(hReport);

	return result;
}

/**
* VOID ApplicationRecoveryFinished(BOOL bSuccess)
* ȣ�� ���� ���α׷��� ������ ������ �Ϸ������� ��Ÿ����.
* @author : ������  
*
* @param  bSuccess �����Ͱ� ���������� �����Ǿ����� ��Ÿ������ TRUE �� ����
* @return ����
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

		sprintf(msg, "ApplicationRecoveryFinished ����");
		strcpy(buf, "ApplicationRecoveryFinished ����");	

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ApplicationRecoveryFinished ����", msg);
	}
	catch(int exceptionCode){
		strcpy(msg, "ApplicationRecoveryFinished ����");
		strcpy(buf, "ApplicationRecoveryFinished ����");
		
		result = FALSE;

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ApplicationRecoveryFinished ����", msg);

		return result;
	}	

	//wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ApplicationRecoveryInProgress ����", msg);

	return result;
}