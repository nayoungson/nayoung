#include "TestEventHG.h"

EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR TransferEvent = {0x1, 0x0, 0x0, 0x4, 0x0, 0x0, 0x5};
#define TransferEvent_value 0x1

EXTERN_C __declspec(selectany) const GUID ProviderGuid = {0xd8909c24, 0x5be9, 0x4502, {0x98, 0xca, 0xab, 0x7b, 0xdc, 0x24, 0x89, 0x9d}};

#define MAX_NAMEDVALUES          5  // Maximum array size
#define MAX_PAYLOAD_DESCRIPTORS  9 + (2 * MAX_NAMEDVALUES)


//
BOOL test_EventUnregister(){

	#ifdef OQADBGPRINT
	printf("test_EventUnregister \n");
	#endif

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	ULONG result;
	DWORD status = ERROR_SUCCESS;
	REGHANDLE RegistrationHandle = NULL; 
	EVENT_DATA_DESCRIPTOR Descriptors[MAX_PAYLOAD_DESCRIPTORS]; 

	// EventRegister() : Registers the provider.
	status = EventRegister(&ProviderGuid, NULL, NULL, &RegistrationHandle);

	if(ERROR_SUCCESS != status){
	//wprintf(L"EventRegister failed with %lu\n", status);
	}
	
	// EventWrite() : Use this function to write an event.
	// EventUnregister의 필수 선행 조건 아님.
	EventWrite(RegistrationHandle, &TransferEvent, (ULONG)MAX_PAYLOAD_DESCRIPTORS, &Descriptors[0]);

	if(status != ERROR_SUCCESS) {
	//wprintf(L"EventWrite failed with 0x%x", status);
	}
	
	// EventUnregister() : Removes the provider's registration.
	// EventRegister 후 값을 가져와야 정상 동작.
	result = EventUnregister(RegistrationHandle);

	int err = GetLastError();

	if(result == ERROR_SUCCESS){
		sprintf(meg, " EventUnregister() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}else {

		// Error Code가 6이면, it is meaning that handle is invalid.
		// EventUnregister() 함수의 파라미터 : EventRegister's return value.
		if(err == 6) 
			sprintf(meg, " EventUnregister() : FAIL \n\n Error Code = %d \n EventRegister 함수를 먼저 수행하십시오.");
		else
			sprintf(meg, " RegisterEventSource() : FAIL");
	}

	wresult(__FILE__, __LINE__, "EventUnregister", buf, "SUCCESS", meg);
	return result;
}

BOOL test_EventWriteTransfer(){

	#ifdef OQADBGPRINT
	printf("test_EventWriteTransfer \n");
	#endif

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	ULONG result;
	DWORD status = ERROR_SUCCESS;
	REGHANDLE RegistrationHandle = NULL; 
	EVENT_DATA_DESCRIPTOR Descriptors[MAX_PAYLOAD_DESCRIPTORS]; 

	int err = GetLastError();

	result = EventRegister(&ProviderGuid, NULL, NULL, &RegistrationHandle);

	// EventWriteTransfer()의 첫 번째 파라미터(핸들) -> handle of the provider. The handle comes from EventRegister.
	if(result == ERROR_SUCCESS){

		// Number of EVENT_DATA_DESCRIPTOR structures in UserData. The maximum number is 128.
		result = EventWriteTransfer(RegistrationHandle, &TransferEvent, NULL, (LPCGUID)EVENT_ACTIVITY_CTRL_GET_ID, (ULONG)MAX_PAYLOAD_DESCRIPTORS, &Descriptors[0]);

		if(result == ERROR_SUCCESS) {
			sprintf(meg, " EventWriteTransfer() : SUCCESS");
			strcpy(buf, "SUCCESS");
		}else
			sprintf(meg, " EventWriteTransfer() : FAIL \n\n EventRegister 함수를 먼저 수행하십시오.");

	}else
		sprintf(meg, " EventWriteTransfer() : FAIL");

	wresult(__FILE__, __LINE__, "EventUnregister", buf, "SUCCESS", meg);
	return result;
}

//EventWriteTransfer 함수에서 사용하는 현재 활동 식별자를 만들고, 쿼리, 설정함
BOOL test_EventActivityIdControl(){

	#ifdef OQADBGPRINT
	printf("test_EventActivityIdControl \n");
	#endif

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	ULONG result;
	GUID ActivityId = {0};

	result = EventActivityIdControl(EVENT_ACTIVITY_CTRL_GET_ID, &ActivityId);

	if(result == ERROR_SUCCESS){
		sprintf(meg, " EventActivityIdControl() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}else {
		strcpy(buf, GetErrorMessage(" EventActivityIdControl() : FAIL \n\n Error Message :", GetLastError()));
		return FALSE;
	}

	wresult(__FILE__, __LINE__, "EventActivityIdControl", buf, "SUCCESS", meg);
	return result;
}


#define PROVIDER_NAME L"MyEventProvider"
// TestEvenlog.h
// 지정된 event log 닫음
BOOL test_DeregisterEventSource(){

	#ifdef OQADBGPRINT
	printf("test_DeregisterEventSource \n");
	#endif

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	BOOL result;
	HANDLE hEventLog = NULL;

	// The source name (provider) must exist as a subkey of Application.
	hEventLog = RegisterEventSource(NULL, PROVIDER_NAME);

	if(hEventLog)
		result = DeregisterEventSource(hEventLog);

	if(result == FALSE){
		sprintf(meg, " RegisterEventSource() : FAIL");
		
	}else {
		sprintf(meg, " RegisterEventSource() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}


	wresult(__FILE__, __LINE__, "RegisterEventSource", buf, "SUCCESS", meg);
	return result;

}

BOOL test_RegisterEventSourceA(){

	#ifdef OQADBGPRINT
	printf("test_RegisterEventSourceA \n");
	#endif

	char meg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	HANDLE hEventLog = NULL;
	LPWSTR pInsertStrings[2] = {NULL, NULL};
	DWORD dwEventDataSize = 0;

	// The source name (provider) must exist as a subkey of Application.
	hEventLog = RegisterEventSource(NULL, PROVIDER_NAME);
	if(hEventLog == NULL){
		sprintf(meg, "hEventLog가 NULL값을 반환합니다.");
	}else if(hEventLog == (HANDLE)ERROR_ACCESS_DENIED){
		sprintf(meg, "hEventLog가 ERROR_ACCESS_DENIED를 반환합니다.");
	}else{
		sprintf(meg, " RegisterEventSource() : SUCCESS");
		strcpy(buf, "SUCCESS");
	}

	wresult(__FILE__, __LINE__, "RegisterEventSource", buf, "SUCCESS", meg);
	return true;

}


