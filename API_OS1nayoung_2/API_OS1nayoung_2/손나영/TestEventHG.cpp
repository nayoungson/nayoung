#include "TestEventHG.h"
#include <winddi.h>

EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR TransferEvent = {0x1, 0x0, 0x0, 0x4, 0x0, 0x0, 0x5};
#define TransferEvent_value 0x1

EXTERN_C __declspec(selectany) const GUID ProviderGuid = {0xd8909c24, 0x5be9, 0x4502, {0x98, 0xca, 0xab, 0x7b, 0xdc, 0x24, 0x89, 0x9d}};

#define MAX_NAMEDVALUES          5  // Maximum array size
#define MAX_PAYLOAD_DESCRIPTORS  9 + (2 * MAX_NAMEDVALUES)


/**
* BOOL DeregisterEventSource(HANDLE hEventLog)
* Ư�� �̺�Ʈ �α׸� ����.
* @author : �ճ���
*
* @param hEventLog �̺�Ʈ �α� �ڵ�. RegisterEventSource �Լ��� ����.
* @return �̺�Ʈ �α� ���� ����/���� ����.
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

	if(hEventLog == NULL){ // �̺�Ʈ �ҽ� ��� ����
		strcpy(msg, " RegisterEventSource �Լ��� �ٽ� Ȯ���Ͻʽÿ�.");

	}else if(hEventLog == (HANDLE)ERROR_ACCESS_DENIED){ // �̺�Ʈ �ҽ� ��� ����. ���� ����.
		strcpy(msg, " ������ �����Ǿ����ϴ�. \n return �� : ERROR_ACCESS_DENIED \n\n RegisterEventSource �Լ��� �ٽ� Ȯ���Ͻʽÿ�. ");

	}else{ //�̺�Ʈ �ҽ� ��� ����
		result = DeregisterEventSource(hEventLog);

		if(result != FALSE){ // �̺�Ʈ �α� �ݱ� ����
			strcpy(buf, "SUCCESS");
			strcpy(msg, " DeregisterEventSource() : SUCCESS");
			
		}else{	// �̺�Ʈ �α� �ݱ� ����
			strcpy(buf, GetErrorMessage(" DeregisterEventSource() : FAIL \n\n Error Message :", GetLastError()));
		}
	}

	wresult(__FILE__, __LINE__, "DeregisterEventSource", buf, "SUCCESS", msg);
	return result;
}

/**
* BOOL WINAPI EnumDependentServices(SC_HANDLE hService, DWORD dwServiceState, LPENUM_SERVICE_STATUS lpServices, DWORD cbBufSize, LPDWORD pcbBytesNeeded, LPDWORD lpServicesReturned)
* ������ ���񽺿� �����ϴ� �� ������ �̸��� ���¸� ������
* @author : �ճ���
*
* @param hService ������ �ڵ�. OpenService �Ǵ� CreateService �Լ��� ���ϰ�.
* @param dwServiceState ���ŵ� ������ ����. SERVICE_ACTIVE �Ǵ� SERVICE_INACTIVE �Ǵ� SERVICE_STATE_ALL.
* @param lpServices DB���� �� ���� ���񽺿� ���� �̸� �� ���� ���� ������ �޴� _LPENUM_SERVICE_STATUS ����ü�� �迭�� ���� ������.
* @param cbBufSize �Ű� ���� lpServices�� ����Ű�� ������ ũ��(����Ʈ).
* @param pcbBytesNeeded ���� �׸� �迭�� �����ϴ� �� �ʿ��� ����Ʈ ���� �޴� ������ ���� ������.
* @param lpServicesReturned ���ϵ� ���� �׸��� ���� �����ϴ� ������ ���� ������.
* @return �������� ����/���� ����
*/
BOOL test_EnumDependentServicesA(){

	#ifdef OQADBGPRINT
	printf("test_EnumDependentServicesA \n");
	#endif

	// �������� ����
	// EnumDependentServicesA �Լ��� ù ��° �Ķ���Ͱ� 
	// �� OpenService �Ǵ� CreateService �Լ��� ���ϰ�. 
	// �� �̶� OpenService �Լ��� ù ��° �Ķ���Ͱ� OpenSCManager �Լ��� ���ϰ�.

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	
	SC_HANDLE hSCManager; // OpenSCManager�Լ� SC_HANDLE.
	SC_HANDLE hresult; // CreateService�Լ��� OpenService�Լ��� SC_HANDLE

	//_LPENUM_SERVICE_STATUS ����ü
	typedef struct _LPENUM_SERVICE_STATUS {
		LPTSTR         lpServiceName;
		LPTSTR         lpDisplayName;
		SERVICE_STATUS ServiceStatus;
	} ENUM_SERVICE_STATUS, *LPENUM_SERVICE_STATUS;

	BOOL result = FALSE;
	DWORD lpServicesReturned;
	DWORD dwBytesNeeded;
	LPENUM_SERVICE_STATUSA lpServices = NULL;

	// OpenSCManager() : Ư�� PC���� ���� ���� �Ŵ����� ���� �����ϰ�, �� Ư�� ���� ���� �Ŵ��� �����ͺ��̽��� ����.
	hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS); 

	if (hSCManager == NULL){
		strcpy(msg, GetErrorMessage("OpenSCManager �Լ��� �ٽ� Ȯ���Ͻʽÿ�.(%d)\n", GetLastError()));
	}
	
	// ���� ���� �� ����.
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
* EventWriteTransfer �Լ����� ����ϴ� ���� Ȱ�� �ĺ��ڸ� ����, ����, ������.
* @author : �ճ���
*
* @param ControlCode �ֱ� acitve ������ �ĺ��ڸ� ����, ����, �����ϰ��� �� ���� Ư�� ���� �ڵ�. 5����.
* @param ActivityId ���� �ĺ� GUID.
* @return ����, ����, ���� ��� ���� �� ERROR_SUCCESS
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
* provider�� ����� �����ϸ�, ���μ����� ����Ǳ� ���� �Լ��� ȣ���ؾ� ��.
* @author : �ճ���
*
* @param RegHandle EventRegister �Լ��� ���� ���ϵ� registration �ڵ�.
* @return ��ϵ� provider�� ���� ���� �� ERROR_SUCCESS
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
		strcpy(msg, "EventRegister �Լ��� �ٽ� Ȯ���Ͻʽÿ�.");
		//return FALSE;
	}

	// EventWrite() : Use this function to write an event.
	// EventUnregister�� �ʼ� ���� ���� �ƴ�.
	result = EventWrite(RegHandle, &TransferEvent, (ULONG)MAX_PAYLOAD_DESCRIPTORS, &Descriptors[0]);

	if(result != ERROR_SUCCESS) {
		//strcpy(msg, "EventWrite �Լ� ����. EventUnregister�� �ʼ� �������� �ƴ�");
	}

	// provider�� ��� ����
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
* end-to-end �ó��������� �̺�Ʈ�� ���� �̺�Ʈ�� �Բ� link.
* @author : �ճ���
*
* @param RegHandle EventRegister �Լ��� ���� ���ϵ� registration �ڵ�.
* @param EventDescriptor ���⸦ ���� �̺��� �ĺ��ϴ� ��Ÿ������.
* @param ActivityId ���� �ĺ� GUID. NULL�̸� ETW�� ���� ���丮�� ������κ��� �ĺ��ڸ� ����.
* @param RelatedActivityId ���� ������Ʈ�κ����� activity �ĺ���. EventActivityIdControl �Լ��� ù �Ķ������ ControlCode. 5����.
* @param UserDataCount ���� �Ķ������ UserData����EVENT_DATA_DESCRIPTOR �������� ��. �ִ� 128.
* @param UserData ���⸦ ���� �̺�Ʈ ������. �� �Ķ������ UserDataCount�� 0�̸� �� �Ķ���͸� NULL�� ����.
* @return link ���� �� ERROR_SUCCESS
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

	// EventRegister ����
	if(result == ERROR_SUCCESS){

		// �̺�Ʈ link ����
		result = EventWriteTransfer(RegistrationHandle, &TransferEvent, NULL, (LPCGUID)EVENT_ACTIVITY_CTRL_GET_ID, (ULONG)MAX_PAYLOAD_DESCRIPTORS, &Descriptors[0]);

		if(result == ERROR_SUCCESS) { // EventWriteTransfer ����
			sprintf(msg, " EventWriteTransfer() : SUCCESS");
			strcpy(buf, "SUCCESS");
		
		// �Ʒ� - EventWriteTransfer ���� ���
		}else if(result == ERROR_INVALID_PARAMETER){
			strcpy(msg, " EventWriteTransfer() : FAIL \n\n �ϳ� �̻��� �Ű� ������ ��ȿ���� �ʽ��ϴ�.");

		}else if(result == ERROR_INVALID_HANDLE){
			strcpy(msg, " EventWriteTransfer() : FAIL \n\n �������� ��� �ڵ��� ��ȿ���� �ʽ��ϴ�.");

		}else if(result == ERROR_ARITHMETIC_OVERFLOW){
			strcpy(msg, " EventWriteTransfer() : FAIL \n\n �̺�Ʈ ũ�Ⱑ ��� �� �ִ� ũ�� (64k - ���)���� Ů�ϴ�.");

		}else if(result == ERROR_MORE_DATA){
			strcpy(msg, " EventWriteTransfer() : FAIL \n\n ���� ���� ũ�Ⱑ �̺�Ʈ�� ���� �ʹ� �۽��ϴ�.");

		}else if(result == ERROR_NOT_ENOUGH_MEMORY){
			strcpy(msg, " EventWriteTransfer() : FAIL \n\n ä���� ���۰� ��ũ�� �÷����Ϸ��� �õ������� ��ũ IO�� ����� ������ �߻����� �ʰ� �ֽ��ϴ�.");

		}else{
			strcpy(msg, " EventWriteTransfer() : FAIL");
		}

	// EventRegister ����
	}else 
		strcpy(msg, " EventRegister �Լ��� ���� �����Ͻʽÿ�.");

	wresult(__FILE__, __LINE__, "EventUnregister", buf, "SUCCESS", msg);
	return result;
}

/**
* int WINAPI GetKeyboardType(
  _In_ int nTypeFlag
  );
* Ű���忡 ���� ���� ���
* @author : �ճ���
*
* @param nTypeFlag ����� Ű���� ������ Ÿ��. 0(Ű���� ����) / 1(Ű���� ���� ����) / 2(Ű������ ��� Ű ��)
* @return �䱸�Ǵ� ������ ����.
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
		sprintf(msg, " GetKeyboardType(0) : SUCCESS \n Ű���� ������ %d�Դϴ�. \n\n GetKeyboardType(1) : SUCCESS \n Ű���� ���� ������ %d�Դϴ�. \n\n GetKeyboardType(2) : SUCCESS \n Ű������ ��� Ű ���� %d�Դϴ�.", result1, result2, result3);
		result = TRUE;
	}else{
		sprintf(msg, " GetKeyboardType() : FAIL \n\n Ű���� ������ %d�Դϴ�. \n Ű���� ���� ������ %d�Դϴ�. \n Ű������ ��� Ű ���� %d�Դϴ�.", result1, result2, result3);
	}

	wresult(__FILE__, __LINE__, "GetKeyboardType", buf, "SUCCESS", msg);
	return result;
}



/**
* int WINAPI GetPriorityClipboardFormat(
  _In_ UINT *paFormatPriorityList,
  _In_ int  cFormats
  );
* ������ ����Ʈ ������ �̿� ������ ������ Ŭ�� ���� ������ ����.
* @author : �ճ���
*
* @param paFormatPriorityList Ŭ������ �迭. �켱 ������ ���� ������ ������.
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
		strcpy(msg, " GetPriorityClipboardFormat() : SUCCESS \n\n Ŭ�����尡 ��� �־� ������ Ŭ������ ������ �����ϴ�.");

	}else if(uFormat == -1){
		strcpy(msg, " GetPriorityClipboardFormat() : FAIL \n\n Ŭ�����忡 �����ʹ� ������ ������ ������ �ƴմϴ�.");

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
* ���� Ű �ڵ带 ��ĵ �ڵ� �Ǵ� ���� ������ ��ȯ (����)�ϰų� ��ĵ �ڵ带 ���� Ű �ڵ�� ��ȯ.
  ������ �ڵ带 ��ȯ�ϴ� �� ����� ���� �迭�� �ڵ��� �����Ϸ��� MapVirtualKeyEx �Լ��� ���.
* @author : �ճ���
* 
* @param uCode Ű �� ���� Ű �ڵ� �Ǵ� ��ĵ �ڵ�. �� ���� �ؼ� ����� uMapType �Ű� ���� �� ���� ���� �ٸ�.
* @param uMapType ���� �� ����. �� �Ű� ������ ���� uCode �Ű� ���� �� ���� ���� �ٸ�. 4����.
* @return  uCode �� uMapType �� ���� ���� ��ĵ �ڵ�, ���� Ű �ڵ� �Ǵ� ���� ��. ��ȯ�� ������ 0.
*/

BOOL test_MapVirtualKeyA(){

	#ifdef OQADBGPRINT
	printf("test_MapVirtualKeyA \n");
	#endif

	BOOL return_value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	//ù ��° �Ķ����
	// 0x01 -> Left mouse button
	UINT uCode = 0x01;
	
	// �� ��° �Ķ����
	//MAPVK_VK_TO_CHAR(2) : uCode �� ���� Ű �ڵ��̸� ��ȯ ���� ���� �ܾ�� ������� ���� ���� ������ ��ȯ
	//MAPVK_VK_TO_VSC(0) : uCode �� ���� Ű �ڵ��̸� ��ĵ �ڵ�� ��ȯ
	//MAPVK_VSC_TO_VK(1) : uCode �� ��ĵ �ڵ��̸� ���� �� ������ Ű�� �������� �ʴ� ���� Ű �ڵ�� ��ȯ
	//MAPVK_VSC_TO_VK_EX(3) : uCode �� ��ĵ �ڵ��̸� ���� �� ������ Ű�� �����ϴ� ���� Ű �ڵ�� ��ȯ
	UINT uMapType = MAPVK_VSC_TO_VK_EX;

	// MapVirtualKeyA �Լ� ����
	UINT result = MapVirtualKeyA(uCode, uMapType);

	if(result == 0){ //��ȯ X ���
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
* ���� Ű �ڵ带 ��ĵ �ڵ� �Ǵ� ���� ������ ��ȯ (����)�ϰų� ��ĵ �ڵ带 ���� Ű �ڵ�� ��ȯ/
  �� �Լ��� �Է� ���� �Է� ��Ķ �ĺ��ڸ� ����Ͽ� �ڵ带 ��ȯ��.
* @author : �ճ���
*
* @param uCode Ű�� ���� Ű �ڵ� �Ǵ� ��ĵ �ڵ�.
* @param uMapType ���� �� ����. �� �Ű� ������ ���� uCode �Ű� ���� �� ���� ���� �ٸ�. 5����.
* @param dwhkl ������ �ڵ带 ��ȯ�ϴ� �� ����� �Է� ��Ķ �ĺ���.  ������ LoadKeyboardLayout �Լ����� ��ȯ �� �Է� ��Ķ �ĺ����� �� ����.
* @return uCode �� uMapType �� ���� ���� ��ĵ �ڵ�, ���� Ű �ڵ� �Ǵ� ���� ��. ��ȯ�� ������ ��ȯ ���� 0. 
*/

BOOL test_MapVirtualKeyExA(){

	#ifdef OQADBGPRINT
	printf("test_MapVirtualKeyExA \n");
	#endif

	BOOL return_value = FALSE;

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	// ù ��° �Ķ����
	// 0x01 -> Left mouse button
	UINT uCode = 0x01;
	
	// �� ��° �Ķ����
	//MAPVK_VK_TO_CHAR(2) : uCode �� ���� Ű �ڵ��̸� ��ȯ ���� ���� �ܾ�� ������� ���� ���� ������ ��ȯ
	//MAPVK_VK_TO_VSC(0) : uCode �� ���� Ű �ڵ��̸� ��ĵ �ڵ�� ��ȯ
	//MAPVK_VK_TO_VSC_EX(4) : UCODE�� �Ķ���ʹ� ���� Ű �ڵ� �� ��ĵ �ڵ�� ����
	//MAPVK_VSC_TO_VK(1) : uCode �� ��ĵ �ڵ��̸� ���� �� ������ Ű�� �������� �ʴ� ���� Ű �ڵ�� ��ȯ
	//MAPVK_VSC_TO_VK_EX(3) : uCode �� ��ĵ �ڵ��̸� ���� �� ������ Ű�� �����ϴ� ���� Ű �ڵ�� ��ȯ
	UINT uMapType = MAPVK_VSC_TO_VK_EX;

	// �� ��° �Ķ����
	HKL dwhkl = LoadKeyboardLayout((LPCWSTR)"00000429", 1);

	// MapVirtualKeyA �Լ� ����
	UINT result = MapVirtualKeyExA(uCode, uMapType, dwhkl);
	
	if(result == 0){ //��ȯ X ���
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
* Ư�� �̺�Ʈ �α׿� ��ϵ� �ڵ� ������
* @author : �ճ���
*
* @param lpUNCServerName �۾��� ���� �� ���� ������ UNC (���� ��� ��Ģ) �̸�. NULL�̸� ���� ��ǻ��.
* @param lpSourceName �ڵ��� ������ �̺�Ʈ �ҽ� �� �̸�. ���� �̸��� Eventlog ������Ʈ�� Ű �Ʒ��� �α� ���� Ű ���� ��.
* @return �̺�Ʈ �α׿� ���� �ڵ�.
*/
BOOL test_RegisterEventSourceA(){

	#ifdef OQADBGPRINT
	printf("test_RegisterEventSourceA \n");
	#endif

	char msg[BUFSIZ] = "FAIL";
	char buf[BUFSIZ] = "FAIL";

	HANDLE result = NULL;
	BOOL return_value = FALSE;

	// test_DeregisterEventSource() ���� ������ �� #define PROVIDER_NAME L"MyEventProvider"
	// �̺�Ʈ �α׿� ��ϵ� �ڵ� ������
	result = RegisterEventSourceA(NULL, (LPCSTR)PROVIDER_NAME);

	if(result == NULL){ // NULL ��ȯ, ����
		strcpy(msg, "hEventLog�� NULL���� ��ȯ�մϴ�.");

	}else if(result == (HANDLE)ERROR_ACCESS_DENIED){ // ����
		strcpy(msg, "hEventLog�� ERROR_ACCESS_DENIED�� ��ȯ�մϴ�.");

	}else{ // ����
		return_value = TRUE;
		strcpy(buf, "SUCCESS");
		sprintf(msg, " RegisterEventSourceA() : SUCCESS");
	}

	wresult(__FILE__, __LINE__, "RegisterEventSourceA", buf, "SUCCESS", msg);
	return return_value;
}


/** 
* BOOL ReportEvent(HANDLE  hEventLog, WORD wType, WORD wCategory, DWORD dwEventID, PSID lpUserSid, WORD wNumStrings, DWORD dwDataSize, LPCTSTR *lpStrings, LPVOID lpRawData)
* Ư�� �̺�Ʈ �α��� ���� ��Ʈ�� �ۼ�
* @author : �ճ���
*
* @param hEventLog �̺�Ʈ �α� �ڵ�. RegisterEventSource �Լ��� ����.
* @param wType �̺�Ʈ�� �α׵Ǵ� Ÿ��. 6����.
* @param wCategory �̺�Ʈ ī�װ�
* @param dwEventID �̺�Ʈ �ĺ���
* @param lpUserSid �ֱ� ������� ���� �ĺ��ڿ� ���� ������
* @param wNumStrings lpStrings �Ķ���Ϳ� ���� ����Ʈ�Ǵ� �迭���� ���� ��Ʈ���� ��
* @param dwDataSize �α׿� �� Ư�� �̺�Ʈ ��(���̳ʸ�) �������� ����Ʈ ��
* @param *lpStrings �̺�Ʈ ���� ���ڿ��� ����ڿ��� ǥ���ϱ� ����, �޽����� ���յǴ� Null ���� ���ڿ� �迭�� �����ϴ� ���ۿ� ���� ������
* @param lpRawData ��(���̳ʸ�) �����͸� �����ϴ� ���ۿ� ���� ������
* @return ��Ʈ�� �ۼ� ����/���� ����
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

	// ReportEvent�Լ��� �̺�Ʈ �α� �ڵ�. RegisterEventSource �Լ��� ����.
	hEventLog = RegisterEventSource(NULL, PROVIDER_NAME);
	if(hEventLog == NULL){ // ���� ������ RegisterEventSource ����

		strcpy(msg, GetErrorMessage(" RegisterEventSource �Լ��� ���� Ȯ���Ͻʽÿ�. \n\n Error Message :", GetLastError()));
		result = FALSE;

	}else{ // ���� ������ RegisterEventSource ����
		dwEventDataSize = ((DWORD)wcslen(lpRawData) + 1) * sizeof(WCHAR);

		// ��Ʈ�� �ۼ� ����
		result = ReportEvent(hEventLog, EVENTLOG_ERROR_TYPE, 1,0, NULL, 0, dwEventDataSize, NULL, lpRawData);

		if (result != FALSE){
			strcpy(buf, "SUCCESS");
			strcpy(msg, " ReportEventA() : SUCCESS");

		}else{ //��Ʈ�� �ۼ� ����
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
* ���ڸ� �ش� ���� Ű �ڵ�� ��ȯ�ϰ� ���� Ű������ ���¸� ��ȯ.
  �� �Լ��� VkKeyScanEx �Լ� �� ��ü�Ǿ�����, Ű���� ���̾ƿ��� �������� �ʾƵ� VkKeyScan�� ����� �� ����.
* @author : �ճ���
*
* @param ch ���ڸ� ���� Ű �ڵ�� ��ȯ.
* @return ��ȯ ���� ���� ����Ʈ���� ���� Ű �ڵ尡 ���Եǰ� ���� ����Ʈ���� ���� �÷��� ��Ʈ�� ������ �� ���ִ� ����Ʈ ����(1/2/4/8/16/32)�� ����.
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
	
	SHORT code = VkKeyScanA(ch);  // VkKeyScan() : ���� �� ���� Ű �ڵ� ��ȯ + ���� Ű���� ���� ��ȯ
	BYTE lobyte = LOBYTE(code); // LOBYTE : ������ ������ ���� ����Ʈ �˻�. ���� ����Ʈ���� ���� Ű �ڵ尡 ���Ե�.
	BYTE hibyte = HIBYTE(code); // HIBYTE : ������ 16��Ʈ ġ�� ���� ����Ʈ�� ������

	SHORT codelist[6] = {1, 2, 4, 8, 16, 32}; // ���� ����Ʈ���� ���� 6���� �� �� ������ ���Ե�. �÷��� ��Ʈ�� ������ �� �� �ִ� ����Ʈ ����.

	for(int i= 0; i<6; i++){
		if(hibyte == codelist[i] && lobyte != 0){  //���� ����Ʈ�� 6���� �� �ϳ��� ��ġ�ϰ� ���� ����Ʈ(���� Ű �ڵ�)�� 0�� �ƴ� ��.
			strcpy(buf, "SUCCESS");
			sprintf(msg, " VkKeyScanA() : SUCCESS \n\n ��ȯ�� ���� : %c \n ��������Ʈ : %d \n ���� ����Ʈ %d", ch, codelist[i], lobyte);
			result = TRUE;
			break;

		}else{
			strcpy(msg, " VkKeyScanA() : FAIL");
			result = FALSE;
		}
	}

	/**
	���� Ű �ڵ�
	GetKeyState()

	��ȯ ���� ������ ���� ������ ���� Ű�� ���¸� ����.

	���� ��Ʈ�� 1�̸� -> Ű �۵� X. 
				1�� �ƴϸ� -> Ű �۵� O.
	���� ��Ʈ�� 1�̸� -> Ű ���. CAPS LOCK ���� Ű�� ���� ������ ��۵�.
				0DLAUS -> Ű �����ְ� �Ҿ���. Ű�� ������ ��� Ű�� ǥ�õ��� ������ ��۵��� ������ ����.
	*/
	wresult(__FILE__, __LINE__, "VkKeyScanA", buf, "SUCCESS", msg);
	return result;
}