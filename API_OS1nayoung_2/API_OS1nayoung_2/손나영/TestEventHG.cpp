#include "TestEventHG.h"
#include <winddi.h>

EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR TransferEvent = {0x1, 0x0, 0x0, 0x4, 0x0, 0x0, 0x5};
#define TransferEvent_value 0x1

EXTERN_C __declspec(selectany) const GUID ProviderGuid = {0xd8909c24, 0x5be9, 0x4502, {0x98, 0xca, 0xab, 0x7b, 0xdc, 0x24, 0x89, 0x9d}};

#define MAX_NAMEDVALUES          5  // Maximum array size
#define MAX_PAYLOAD_DESCRIPTORS  9 + (2 * MAX_NAMEDVALUES)


/**
* BOOL DeregisterEventSource(HANDLE hEventLog)
* 특정 이벤트 로그를 닫음.
* @author : 손나영
*
* @param hEventLog 이벤트 로그 핸들. RegisterEventSource 함수가 리턴.
* @return 이벤트 로그 닫힘 성공/실패 여부.
*/

#define PROVIDER_NAME L"MyEventProvider"
BOOL test_DeregisterEventSource(){

	#ifdef OQADBGPRINT
	printf("test_DeregisterEventSource \n");
	#endif

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	BOOL result = FALSE;
	HANDLE hEventLog = NULL;

	// The source name (provider) must exist as a subkey of Application.
	hEventLog = RegisterEventSource(NULL, PROVIDER_NAME);

	if(hEventLog == NULL){ // 이벤트 소스 등록 실패
		strcpy(msg, " RegisterEventSource 함수를 다시 확인하십시오.");

	}else if(hEventLog == (HANDLE)ERROR_ACCESS_DENIED){ // 이벤트 소스 등록 실패. 접근 실패.
		strcpy(msg, " 접근이 금지되었습니다. \n return 값 : ERROR_ACCESS_DENIED \n\n RegisterEventSource 함수를 다시 확인하십시오. ");

	}else{ //이벤트 소스 등록 성공
		result = DeregisterEventSource(hEventLog);

		if(result != FALSE){ // 이벤트 로그 닫기 성공
			strcpy(buf, "SUCCESS");
			strcpy(msg, " DeregisterEventSource() : SUCCESS");
			
		}else{	// 이벤트 로그 닫기 실패
			strcpy(buf, GetErrorMessage(" DeregisterEventSource() : FAIL \n\n Error Message :", GetLastError()));
		}
	}

	wresult(__FILE__, __LINE__, "DeregisterEventSource", buf, "SUCCESS", msg);
	return result;
}

/**
* BOOL WINAPI EnumDependentServices(SC_HANDLE hService, DWORD dwServiceState, LPENUM_SERVICE_STATUS lpServices, DWORD cbBufSize, LPDWORD pcbBytesNeeded, LPDWORD lpServicesReturned)
* 지정된 서비스에 의존하는 각 서비스의 이름과 상태를 가져옴
* @author : 손나영
*
* @param hService 서비스의 핸들. OpenService 또는 CreateService 함수의 리턴값.
* @param dwServiceState 열거될 서비스의 상태. SERVICE_ACTIVE 또는 SERVICE_INACTIVE 또는 SERVICE_STATE_ALL.
* @param lpServices DB에서 각 종속 서비스에 대한 이름 및 서비스 상태 정보를 받는 _LPENUM_SERVICE_STATUS 구조체의 배열에 대한 포인터.
* @param cbBufSize 매개 변수 lpServices를 가리키는 버퍼의 크기(바이트).
* @param pcbBytesNeeded 서비스 항목 배열을 저장하는 데 필요한 바이트 수를 받는 변수에 대한 포인터.
* @param lpServicesReturned 리턴된 서비스 항목의 수를 수신하는 변수에 대한 포인터.
* @return 가져오기 성공/실패 여부
*/
BOOL test_EnumDependentServicesA(){

	#ifdef OQADBGPRINT
	printf("test_EnumDependentServicesA \n");
	#endif

	// 구조간단 정리
	// EnumDependentServicesA 함수의 첫 번째 파라미터가 
	// → OpenService 또는 CreateService 함수의 리턴값. 
	// → 이때 OpenService 함수의 첫 번째 파라미터가 OpenSCManager 함수의 리턴값.

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	
	SC_HANDLE hSCManager; // OpenSCManager함수 SC_HANDLE.
	SC_HANDLE hresult; // CreateService함수와 OpenService함수의 SC_HANDLE

	//_LPENUM_SERVICE_STATUS 구조체
	typedef struct _LPENUM_SERVICE_STATUS {
		LPTSTR         lpServiceName;
		LPTSTR         lpDisplayName;
		SERVICE_STATUS ServiceStatus;
	} ENUM_SERVICE_STATUS, *LPENUM_SERVICE_STATUS;

	BOOL result = FALSE;
	DWORD lpServicesReturned;
	DWORD dwBytesNeeded;
	LPENUM_SERVICE_STATUSA lpServices = NULL;

	// OpenSCManager() : 특정 PC에서 서비스 제어 매니저에 대해 연결하고, 그 특정 서비스 제어 매니저 데이터베이스를 오픈.
	hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS); 

	if (hSCManager == NULL){
		strcpy(msg, GetErrorMessage("OpenSCManager 함수를 다시 확인하십시오.(%d)\n", GetLastError()));
	}
	
	// 서비스 생성 및 오픈.
	hresult = CreateService(hSCManager, L"ChromeSetup", L"CreateService API", SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, L"C:\\Users\\NAYOUNG\\Downloads", NULL, NULL, NULL, NULL, NULL);  
	hresult = OpenService(hSCManager, L"ChromeSetup", SERVICE_STOP | SERVICE_QUERY_STATUS | SERVICE_ENUMERATE_DEPENDENTS);  

	if (hresult == NULL){ 
		printf("OpenService failed (%d)\n", GetLastError()); 
		CloseServiceHandle(hSCManager);
	}   

	result = EnumDependentServicesA(hresult, SERVICE_ACTIVE, lpServices, 0, &dwBytesNeeded, &lpServicesReturned);

	if(result != FALSE){
		// If the Enum call succeeds, then there are no dependent
		// services, so do nothing.
		sprintf(msg, " EnumDependentServicesA() : SUCCESS");
		strcpy(buf, "SUCCESS");

	}else {
		strcpy(buf, GetErrorMessage(" EnumDependentServicesA() : FAIL \n\n Error Message : ", GetLastError()));
		//return FALSE;
	}

	wresult(__FILE__, __LINE__, "EnumDependentServicesA", buf, "SUCCESS", msg);
	return result;
}


/**
* ULONG EventActivityIdControl(ULONG  ControlCode, LPGUID ActivityId)
* EventWriteTransfer 함수에서 사용하는 현재 활동 식별자를 생성, 쿼리, 설정함.
* @author : 손나영
*
* @param ControlCode 최근 acitve 상태의 식별자를 생성, 쿼리, 설정하고자 할 때의 특정 제어 코드. 5가지.
* @param ActivityId 고유 식별 GUID.
* @return 생성, 쿼리, 설정 모두 성공 시 ERROR_SUCCESS
*/

BOOL test_EventActivityIdControl(){

	#ifdef OQADBGPRINT
	printf("test_EventActivityIdControl \n");
	#endif

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	ULONG result;
	GUID ActivityId = {0};
	//
	result = EventActivityIdControl(EVENT_ACTIVITY_CTRL_GET_ID, &ActivityId);

	if(result == ERROR_SUCCESS){
		sprintf(msg, " EventActivityIdControl() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}else {
		strcpy(buf, GetErrorMessage(" EventActivityIdControl() : FAIL \n\n Error Message :", GetLastError()));
		//return FALSE;
	}

	wresult(__FILE__, __LINE__, "EventActivityIdControl", buf, "SUCCESS", msg);
	return result;
}

/**
* ULONG EventUnregister(REGHANDLE RegHandle)
* provider의 등록을 삭제하며, 프로세스가 종료되기 전에 함수를 호출해야 함.
* @author : 손나영
*
* @param RegHandle EventRegister 함수에 의해 리턴된 registration 핸들.
* @return 등록된 provider의 삭제 성공 시 ERROR_SUCCESS
*
*/
BOOL test_EventUnregister(){

	#ifdef OQADBGPRINT
	printf("test_EventUnregister \n");
	#endif

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	ULONG result;
	REGHANDLE RegHandle = NULL; 
	EVENT_DATA_DESCRIPTOR Descriptors[MAX_PAYLOAD_DESCRIPTORS]; 

	// EventRegister() : Registers the provider.
	result = EventRegister(&ProviderGuid, NULL, NULL, &RegHandle);

	if(result != ERROR_SUCCESS){
		strcpy(msg, "EventRegister 함수를 다시 확인하십시오.");
		//return FALSE;
	}

	// EventWrite() : Use this function to write an event.
	// EventUnregister의 필수 선행 조건 아님.
	result = EventWrite(RegHandle, &TransferEvent, (ULONG)MAX_PAYLOAD_DESCRIPTORS, &Descriptors[0]);

	if(result != ERROR_SUCCESS) {
		//strcpy(msg, "EventWrite 함수 실패. EventUnregister의 필수 선행조건 아님");
	}

	// provider의 등록 삭제
	result = EventUnregister(RegHandle);

	if(result == ERROR_SUCCESS){
		sprintf(msg, " EventUnregister() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}else {
		sprintf(msg, " EventUnregister() : FAIL");
	}

	wresult(__FILE__, __LINE__, "EventUnregister", buf, "SUCCESS", msg);
	return result;
}


/**
* ULONG EventWriteTransfer(REGHANDLE RegHandle, PCEVENT_DESCRIPTOR EventDescriptor, LPCGUID ActivityId, LPCGUID RelatedActivityId, ULONG UserDataCount,PEVENT_DATA_DESCRIPTOR UserData)
* end-to-end 시나리오에서 이벤트를 돌때 이벤트를 함께 link.
* @author : 손나영
*
* @param RegHandle EventRegister 함수에 의해 리턴된 registration 핸들.
* @param EventDescriptor 쓰기를 위한 이벤를 식별하는 메타데이터.
* @param ActivityId 고유 식별 GUID. NULL이면 ETW는 로컬 스토리지 스레드로부터 식벽자를 얻음.
* @param RelatedActivityId 이전 컴포넌트로부터의 activity 식별자. EventActivityIdControl 함수의 첫 파라미터인 ControlCode. 5가지.
* @param UserDataCount 다음 파라미터인 UserData에서EVENT_DATA_DESCRIPTOR 구초제의 수. 최대 128.
* @param UserData 쓰기를 위한 이벤트 데이터. 앞 파라미터인 UserDataCount가 0이면 이 파라미터를 NULL로 설정.
* @return link 성공 시 ERROR_SUCCESS
*/
BOOL test_EventWriteTransfer(){

	#ifdef OQADBGPRINT
	printf("test_EventWriteTransfer \n");
	#endif

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	ULONG result;
	DWORD status = ERROR_SUCCESS;
	REGHANDLE RegistrationHandle = NULL; 
	EVENT_DATA_DESCRIPTOR Descriptors[MAX_PAYLOAD_DESCRIPTORS]; 

	int err = GetLastError();

	result = EventRegister(&ProviderGuid, NULL, NULL, &RegistrationHandle);

	// EventRegister 성공
	if(result == ERROR_SUCCESS){

		// 이벤트 link 실행
		result = EventWriteTransfer(RegistrationHandle, &TransferEvent, NULL, (LPCGUID)EVENT_ACTIVITY_CTRL_GET_ID, (ULONG)MAX_PAYLOAD_DESCRIPTORS, &Descriptors[0]);

		if(result == ERROR_SUCCESS) { // EventWriteTransfer 성공
			sprintf(msg, " EventWriteTransfer() : SUCCESS");
			strcpy(buf, "SUCCESS");
		
		// 아래 - EventWriteTransfer 실패 경우
		}else if(result == ERROR_INVALID_PARAMETER){
			strcpy(msg, " EventWriteTransfer() : FAIL \n\n 하나 이상의 매개 변수가 유효하지 않습니다.");

		}else if(result == ERROR_INVALID_HANDLE){
			strcpy(msg, " EventWriteTransfer() : FAIL \n\n 공급자의 등록 핸들이 유효하지 않습니다.");

		}else if(result == ERROR_ARITHMETIC_OVERFLOW){
			strcpy(msg, " EventWriteTransfer() : FAIL \n\n 이벤트 크기가 허용 된 최대 크기 (64k - 헤더)보다 큽니다.");

		}else if(result == ERROR_MORE_DATA){
			strcpy(msg, " EventWriteTransfer() : FAIL \n\n 세션 버퍼 크기가 이벤트에 비해 너무 작습니다.");

		}else if(result == ERROR_NOT_ENOUGH_MEMORY){
			strcpy(msg, " EventWriteTransfer() : FAIL \n\n 채워진 버퍼가 디스크로 플러시하려고 시도하지만 디스크 IO가 충분히 빠르게 발생하지 않고 있습니다.");

		}else{
			strcpy(msg, " EventWriteTransfer() : FAIL");
		}

	// EventRegister 실패
	}else 
		strcpy(msg, " EventRegister 함수를 먼저 수행하십시오.");

	wresult(__FILE__, __LINE__, "EventUnregister", buf, "SUCCESS", msg);
	return result;
}

/**
* int WINAPI GetKeyboardType(
  _In_ int nTypeFlag
  );
* 키보드에 대한 정보 출력
* @author : 손나영
*
* @param nTypeFlag 출력할 키보드 정보의 타입. 0(키보드 유형) / 1(키보드 하위 유형) / 2(키보드의 기능 키 수)
* @return 요구되는 정보를 지정.
*/

BOOL test_GetKeyboardType(){

	#ifdef OQADBGPRINT
	printf("test_GetKeyboardType \n");
	#endif

	int result = FALSE;
	int result1, result2, result3;
	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	result1 = GetKeyboardType(0);
	result2 = GetKeyboardType(1);
	result3 = GetKeyboardType(2);

	if(result1 != 0 && result3 != 0){
		strcpy(buf, "SUCCESS");
		sprintf(msg, " GetKeyboardType(0) : SUCCESS \n 키보드 유형은 %d입니다. \n\n GetKeyboardType(1) : SUCCESS \n 키보드 하위 유형은 %d입니다. \n\n GetKeyboardType(2) : SUCCESS \n 키보드의 기능 키 수는 %d입니다.", result1, result2, result3);
		result = TRUE;
	}else{
		sprintf(msg, " GetKeyboardType() : FAIL \n\n 키보드 유형은 %d입니다. \n 키보드 하위 유형은 %d입니다. \n 키보드의 기능 키 수는 %d입니다.", result1, result2, result3);
	}

	wresult(__FILE__, __LINE__, "GetKeyboardType", buf, "SUCCESS", msg);
	return result;
}



/**
* int WINAPI GetPriorityClipboardFormat(
  _In_ UINT *paFormatPriorityList,
  _In_ int  cFormats
  );
* 지정된 리스트 내에서 이용 가능한 최초의 클립 보드 형식을 얻어옴.
* @author : 손나영
*
* @param paFormatPriorityList 클립보드 배열. 우선 순위에 따라 형식이 지정됨.
* @param cFormats
* @return
*/

BOOL test_GetPriorityClipboardFormat(){

	#ifdef OQADBGPRINT
	printf("test_GetPriorityClipboardFormat \n");
	#endif

	BOOL result = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	static UINT auPriorityList[] = {CF_OWNERDISPLAY, CF_TEXT, CF_ENHMETAFILE, CF_BITMAP}; 

	int uFormat = GetPriorityClipboardFormat(auPriorityList, 4); 

	if(uFormat){
		strcpy(buf, "SUCCESS");
		strcpy(msg, " GetPriorityClipboardFormat() : SUCCESS");
		result = TRUE;

	}else if(uFormat == NULL){
		strcpy(buf, "SUCCESS");
		strcpy(msg, " GetPriorityClipboardFormat() : SUCCESS \n\n 클립보드가 비어 있어 가져올 클립보드 포맷이 없습니다.");

	}else if(uFormat == -1){
		strcpy(msg, " GetPriorityClipboardFormat() : FAIL \n\n 클립보드에 데이터는 있지만 지정된 형식이 아닙니다.");

	}else{
		sprintf(msg, " GetPriorityClipboardFormat() : FAIL \n\n Error Code : %d", GetLastError());
	}

	wresult(__FILE__, __LINE__, "GetPriorityClipboardFormat", buf, "SUCCESS", msg);
	return result;
}


/** 
* UINT WINAPI MapVirtualKey(
  _In_ UINT uCode,
  _In_ UINT uMapType
  );
* 가상 키 코드를 스캔 코드 또는 문자 값으로 변환 (매핑)하거나 스캔 코드를 가상 키 코드로 변환.
  지정된 코드를 변환하는 데 사용할 자판 배열의 핸들을 지정하려면 MapVirtualKeyEx 함수를 사용.
* @author : 손나영
* 
* @param uCode 키 의 가상 키 코드 또는 스캔 코드. 이 값의 해석 방법은 uMapType 매개 변수 의 값에 따라 다름.
* @param uMapType 수행 할 번역. 이 매개 변수의 값은 uCode 매개 변수 의 값에 따라 다름. 4가지.
* @return  uCode 및 uMapType 의 값에 따라 스캔 코드, 가상 키 코드 또는 문자 값. 변환이 없으면 0.
*/

BOOL test_MapVirtualKeyA(){

	#ifdef OQADBGPRINT
	printf("test_MapVirtualKeyA \n");
	#endif

	BOOL return_value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	//첫 번째 파라미터
	// 0x01 -> Left mouse button
	UINT uCode = 0x01;
	
	// 두 번째 파라미터
	//MAPVK_VK_TO_CHAR(2) : uCode 는 가상 키 코드이며 반환 값의 하위 단어에서 변경되지 않은 문자 값으로 변환
	//MAPVK_VK_TO_VSC(0) : uCode 는 가상 키 코드이며 스캔 코드로 변환
	//MAPVK_VSC_TO_VK(1) : uCode 는 스캔 코드이며 왼쪽 및 오른쪽 키를 구별하지 않는 가상 키 코드로 변환
	//MAPVK_VSC_TO_VK_EX(3) : uCode 는 스캔 코드이며 왼쪽 및 오른쪽 키를 구별하는 가상 키 코드로 변환
	UINT uMapType = MAPVK_VSC_TO_VK_EX;

	// MapVirtualKeyA 함수 수행
	UINT result = MapVirtualKeyA(uCode, uMapType);

	if(result == 0){ //변환 X 경우
		sprintf(msg, " MapVirtualKeyA() : FAIL ");
		
	}else{
		strcpy(buf, "SUCCESS");
		strcpy(msg, " MapVirtualKeyA() : SUCCESS");
		return_value = TRUE;
	}

	wresult(__FILE__, __LINE__, "MapVirtualKeyA", buf, "SUCCESS", msg);
	return return_value;
}

/** 
* UINT WINAPI MapVirtualKeyEx (
  _In_UINT uCode,
  _In_UINT uMapType,
  _Inout_opt_ HKL dwhkl
  );
* 가상 키 코드를 스캔 코드 또는 문자 값으로 변환 (매핑)하거나 스캔 코드를 가상 키 코드로 변환/
  이 함수는 입력 언어와 입력 로캘 식별자를 사용하여 코드를 변환함.
* @author : 손나영
*
* @param uCode 키의 가상 키 코드 또는 스캔 코드.
* @param uMapType 수행 할 번역. 이 매개 변수의 값은 uCode 매개 변수 의 값에 따라 다름. 5가지.
* @param dwhkl 지정된 코드를 변환하는 데 사용할 입력 로캘 식별자.  이전에 LoadKeyboardLayout 함수에서 반환 된 입력 로캘 식별자일 수 있음.
* @return uCode 및 uMapType 의 값에 따라 스캔 코드, 가상 키 코드 또는 문자 값. 변환이 없으면 반환 값은 0. 
*/

BOOL test_MapVirtualKeyExA(){

	#ifdef OQADBGPRINT
	printf("test_MapVirtualKeyExA \n");
	#endif

	BOOL return_value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	// 첫 번째 파라미터
	// 0x01 -> Left mouse button
	UINT uCode = 0x01;
	
	// 두 번째 파라미터
	//MAPVK_VK_TO_CHAR(2) : uCode 는 가상 키 코드이며 반환 값의 하위 단어에서 변경되지 않은 문자 값으로 변환
	//MAPVK_VK_TO_VSC(0) : uCode 는 가상 키 코드이며 스캔 코드로 변환
	//MAPVK_VK_TO_VSC_EX(4) : UCODE의 파라미터는 가상 키 코드 및 스캔 코드로 번역
	//MAPVK_VSC_TO_VK(1) : uCode 는 스캔 코드이며 왼쪽 및 오른쪽 키를 구별하지 않는 가상 키 코드로 변환
	//MAPVK_VSC_TO_VK_EX(3) : uCode 는 스캔 코드이며 왼쪽 및 오른쪽 키를 구별하는 가상 키 코드로 변환
	UINT uMapType = MAPVK_VSC_TO_VK_EX;

	// 세 번째 파라미터
	HKL dwhkl = LoadKeyboardLayout((LPCWSTR)"00000429", 1);

	// MapVirtualKeyA 함수 수행
	UINT result = MapVirtualKeyExA(uCode, uMapType, dwhkl);
	
	if(result == 0){ //변환 X 경우
		sprintf(msg, " MapVirtualKeyExA() : FAIL ");
		
	}else{
		strcpy(buf, "SUCCESS");
		strcpy(msg, " MapVirtualKeyExA() : SUCCESS");
		return_value = TRUE;
	}

	wresult(__FILE__, __LINE__, "MapVirtualKeyExA", buf, "SUCCESS", msg);
	return return_value;
}

/**
* HANDLE RegisterEventSource(LPCTSTR lpUNCServerName, LPCTSTR lpSourceName)
* 특정 이벤트 로그에 등록된 핸들 가져옴
* @author : 손나영
*
* @param lpUNCServerName 작업을 수행 할 원격 서버의 UNC (범용 명명 규칙) 이름. NULL이면 로컬 컴퓨터.
* @param lpSourceName 핸들을 가져올 이벤트 소스 의 이름. 원본 이름은 Eventlog 레지스트리 키 아래의 로그 하위 키 여야 함.
* @return 이벤트 로그에 대한 핸들.
*/
BOOL test_RegisterEventSourceA(){

	#ifdef OQADBGPRINT
	printf("test_RegisterEventSourceA \n");
	#endif

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	HANDLE result = NULL;
	BOOL return_value = FALSE;

	// test_DeregisterEventSource() 위에 정의함 → #define PROVIDER_NAME L"MyEventProvider"
	// 이벤트 로그에 등록된 핸들 가져옴
	result = RegisterEventSourceA(NULL, (LPCSTR)PROVIDER_NAME);

	if(result == NULL){ // NULL 반환, 실패
		strcpy(msg, "hEventLog가 NULL값을 반환합니다.");

	}else if(result == (HANDLE)ERROR_ACCESS_DENIED){ // 실패
		strcpy(msg, "hEventLog가 ERROR_ACCESS_DENIED를 반환합니다.");

	}else{ // 성공
		return_value = TRUE;
		strcpy(buf, "SUCCESS");
		sprintf(msg, " RegisterEventSourceA() : SUCCESS");
	}

	wresult(__FILE__, __LINE__, "RegisterEventSourceA", buf, "SUCCESS", msg);
	return return_value;
}


/** 
* BOOL ReportEvent(HANDLE  hEventLog, WORD wType, WORD wCategory, DWORD dwEventID, PSID lpUserSid, WORD wNumStrings, DWORD dwDataSize, LPCTSTR *lpStrings, LPVOID lpRawData)
* 특정 이벤트 로그의 끝에 엔트리 작성
* @author : 손나영
*
* @param hEventLog 이벤트 로그 핸들. RegisterEventSource 함수가 리턴.
* @param wType 이벤트가 로그되는 타입. 6가지.
* @param wCategory 이벤트 카테고리
* @param dwEventID 이벤트 식별자
* @param lpUserSid 최근 사용자의 보안 식별자에 대한 포인터
* @param wNumStrings lpStrings 파라미터에 의해 포인트되는 배열에서 삽입 스트링의 수
* @param dwDataSize 로그에 쓸 특정 이벤트 행(바이너리) 데이터의 바이트 수
* @param *lpStrings 이벤트 뷰어에서 문자열을 사용자에게 표시하기 전에, 메시지에 병합되는 Null 종료 문자열 배열을 포함하는 버퍼에 대한 포인터
* @param lpRawData 행(바이너리) 데이터를 포함하는 버퍼에 대한 포인터
* @return 엔트리 작성 성공/실패 여부
*/

CONST LPWSTR lpRawData = L"test_ReportEventA";
BOOL test_ReportEventA(){

	#ifdef OQADBGPRINT
	printf("test_ReportEventA \n");
	#endif

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	BOOL result;
	HANDLE hEventLog = NULL;
	LPWSTR pInsertStrings[2] = {NULL, NULL};
	DWORD dwEventDataSize = 0;

	// ReportEvent함수의 이벤트 로그 핸들. RegisterEventSource 함수가 리턴.
	hEventLog = RegisterEventSource(NULL, PROVIDER_NAME);
	if(hEventLog == NULL){ // 선행 조건인 RegisterEventSource 실패

		strcpy(msg, GetErrorMessage(" RegisterEventSource 함수를 먼저 확인하십시오. \n\n Error Message :", GetLastError()));
		result = FALSE;

	}else{ // 선행 조건인 RegisterEventSource 성공
		dwEventDataSize = ((DWORD)wcslen(lpRawData) + 1) * sizeof(WCHAR);

		// 엔트리 작성 성공
		result = ReportEvent(hEventLog, EVENTLOG_ERROR_TYPE, 1,0, NULL, 0, dwEventDataSize, NULL, lpRawData);

		if (result != FALSE){
			strcpy(buf, "SUCCESS");
			strcpy(msg, " ReportEventA() : SUCCESS");

		}else{ //엔트리 작성 실패
			strcpy(msg, " ReportEventA() : FALSE");
		}
	}

	wresult(__FILE__, __LINE__, "ReportEventA", buf, "SUCCESS", msg);
	return result;
}


/**
* SHORT WINAPI VkKeyScan(
  _In_ TCHAR ch
  );
* 문자를 해당 가상 키 코드로 변환하고 현재 키보드의 상태를 전환.
  이 함수는 VkKeyScanEx 함수 로 대체되었으나, 키보드 레이아웃을 지정하지 않아도 VkKeyScan을 사용할 수 있음.
* @author : 손나영
*
* @param ch 문자를 가상 키 코드로 변환.
* @return 반환 값의 하위 바이트에는 가상 키 코드가 포함되고 상위 바이트에는 다음 플래그 비트의 조합이 될 수있는 시프트 상태(1/2/4/8/16/32)가 포함.
*/

BOOL test_VkKeyScanA(){

	#ifdef OQADBGPRINT
	printf("test_VkKeyScanA \n");
	#endif

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";
	char lobyte_msg[BUFSIZ] = "FAIL";

	BOOL result = FALSE;

	CHAR ch = 'a';
	ch = toupper(ch);
	
	SHORT code = VkKeyScanA(ch);  // VkKeyScan() : 문자 → 가상 키 코드 변환 + 현재 키보드 상태 전환
	BYTE lobyte = LOBYTE(code); // LOBYTE : 지정된 값에서 하위 바이트 검색. 하위 바이트에는 가상 키 코드가 포함됨.
	BYTE hibyte = HIBYTE(code); // HIBYTE : 지정된 16비트 치의 상위 바이트를 가져옴

	SHORT codelist[6] = {1, 2, 4, 8, 16, 32}; // 상위 바이트에는 다음 6가지 중 한 가지가 포함됨. 플래그 비트의 조합이 될 수 있는 시프트 상태.

	for(int i= 0; i<6; i++){
		if(hibyte == codelist[i] && lobyte != 0){  //상위 바이트가 6가지 중 하나와 일치하고 하위 바이트(가상 키 코드)가 0이 아닐 때.
			strcpy(buf, "SUCCESS");
			sprintf(msg, " VkKeyScanA() : SUCCESS \n\n 변환할 문자 : %c \n 상위바이트 : %d \n 하위 바이트 %d", ch, codelist[i], lobyte);
			result = TRUE;
			break;

		}else{
			strcpy(msg, " VkKeyScanA() : FAIL");
			result = FALSE;
		}
	}

	/**
	가상 키 코드
	GetKeyState()

	반환 값은 다음과 같이 지정된 가상 키의 상태를 지정.

	상위 비트가 1이면 -> 키 작동 X. 
				1이 아니면 -> 키 작동 O.
	하위 비트가 1이면 -> 키 토글. CAPS LOCK 같은 키는 켜져 있으면 토글됨.
				0DLAUS -> 키 꺼져있고 불안정. 키를 누르면 토글 키의 표시등이 켜지며 토글되지 않으면 꺼짐.
	*/
	wresult(__FILE__, __LINE__, "VkKeyScanA", buf, "SUCCESS", msg);
	return result;
}