#include "TestNamespace.h"


/**
* VOID DeleteBoundaryDescriptor(HANDLE BoundaryDescriptor)
* 지정된 바운더리 디스크립터를 삭제한다.
* @author : 손찬영  
*
* @param  BoundaryDescriptor 바운더리 디스크립터 핸들
* @return 없음
*/
BOOL test_DeleteBoundaryDescriptor()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	PSID   RequiredSid;
	const wchar_t *AccountName = L"Administrators";
	DWORD sidlen = 0;
	WCHAR *domainName = NULL;
    DWORD domainNameLen = 0;
    SID_NAME_USE SNU;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	HANDLE hBoundaryDescriptor = NULL;
	LPCTSTR Name = L"CreateBoundaryDescriptor";


	/* 삭제를 확인하기 위해 바운더리 디스크립터를 생성 */
	hBoundaryDescriptor = CreateBoundaryDescriptorW(Name, 0);
	if(NULL == hBoundaryDescriptor){
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorW 실패 : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorW 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorW 성공", msg);
		
		return FALSE;
	}

	/* RequiredSid의 크기를 가져오기 위해 수행 */
	LookupAccountNameW(NULL, AccountName, NULL, &sidlen, NULL, &domainNameLen, &SNU);
	RequiredSid = (PSID) new BYTE[sidlen];
	domainName = (WCHAR *) new WCHAR[domainNameLen];

	/* RequiredSid를 얻기 위해 수행 */	
	if(!LookupAccountNameW(NULL, AccountName, RequiredSid, &sidlen, domainName, &domainNameLen, &SNU)){
        strcpy(msg, GetErrorMessage("LookupAccountName 실패 : ", GetLastError()));
		strcpy(buf, "LookupAccountName 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "LookupAccountName 성공", msg);
		
		return FALSE;
	}
	
	/* SID가 유효하지 않은 경우 테스트 중단 */
	if(!IsValidSid(RequiredSid)){
		strcpy(msg, GetErrorMessage("IsValidSid 실패 : ", GetLastError()));
		strcpy(buf, "IsValidSid 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "IsValidSid 성공", msg);
		
		return FALSE;
	}

	/* 바운더리 디스크립터에 SID 추가 */
	if(!AddSIDToBoundaryDescriptor(&hBoundaryDescriptor, RequiredSid)){
        strcpy(msg, GetErrorMessage("AddSIDToBoundaryDescriptor 실패 : ", GetLastError()));
		strcpy(buf, "AddSIDToBoundaryDescriptor 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "AddSIDToBoundaryDescriptor 성공", msg);
		
		return FALSE;
	}

	/* 바운더리 디스크립터 삭제 */
	DeleteBoundaryDescriptor(hBoundaryDescriptor);

	/* DeleteBoundaryDescriptor후에 hBoundaryDescriptor에 SID 추가 시도 시 실패하면 삭제된 것으로 확인 */
	result = AddSIDToBoundaryDescriptor(&hBoundaryDescriptor, RequiredSid);
	
	/* 바운더리 디스크립터 삭제 후 추가에 성공하면 삭제 실패로 간주함 */
	if(result){
        strcpy(msg, "DeleteBoundaryDescriptor 실패");
		strcpy(buf, "DeleteBoundaryDescriptor 실패");

		result = FALSE;
	}else{
		//sprintf(msg, GetErrorMessage("DeleteBoundaryDescriptor 성공\nAddSIDToBoundaryDescriptor 실패 :", GetLastError()));
		strcpy(msg, "DeleteBoundaryDescriptor 성공");	
		strcpy(buf, "DeleteBoundaryDescriptor 성공");	
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "DeleteBoundaryDescriptor 성공", msg);

	FreeSid(RequiredSid);
	delete domainName;
	

	return result;
}


/**
* VOID CreateBoundaryDescriptorW(LPCTSTR Name, ULONG Flags)
* 바운더리 디스크립터를 생성한다.
* @author : 손찬영  
*
* @param  Name 바운더리 디스크립터 이름
* @param  Flags 예약
* @return 없음
*/
BOOL test_CreateBoundaryDescriptorW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	SID   RequiredSid;
	const wchar_t *AccountName = L"Everyone";
	DWORD sidlen = MAX_PATH;
	WCHAR  dn[MAX_PATH] = {0};
    DWORD dnlen = MAX_PATH;
    SID_NAME_USE SNU;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	HANDLE hBoundaryDescriptor = NULL;
	LPCTSTR Name = L"test_CreateBoundaryDescriptorW";

	/* 바운더리 디스크립터 생성 */
	hBoundaryDescriptor = CreateBoundaryDescriptorW(Name, 0);

	/* RequiredSid를 얻기 위해 수행 */
	if(!LookupAccountName(NULL, AccountName, &RequiredSid, &sidlen, dn, &dnlen, &SNU)){
        strcpy(msg, GetErrorMessage("LookupAccountName 실패 : ", GetLastError()));
		strcpy(buf, "LookupAccountName 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "LookupAccountName 성공", msg);
		
		return FALSE;
	}

	/* 바운더리 디스크립터에 SID 추가 성공 시, 바운더리 디스크립터가 생성된 것을 보장*/
	result = AddSIDToBoundaryDescriptor(&hBoundaryDescriptor, &RequiredSid);

	if(NULL != hBoundaryDescriptor && result){
		sprintf(msg, "CreateBoundaryDescriptorW 성공 : hBoundaryDescriptor = %d", hBoundaryDescriptor);
		strcpy(buf, "CreateBoundaryDescriptorW 성공");	

	}else{
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorW 실패 : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorW 실패");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorW 성공", msg);

	CloseHandle(hBoundaryDescriptor);

	return result;
}

/**
* VOID CreateBoundaryDescriptorA(LPCTSTR Name, ULONG Flags)
* 바운더리 디스크립터를 생성한다.
* @author : 손찬영  
*
* @param  Name 바운더리 디스크립터 이름
* @param  Flags 예약
* @return 없음
*/
BOOL test_CreateBoundaryDescriptorA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	SID   RequiredSid;
	const wchar_t *AccountName = L"Everyone";
	DWORD sidlen = MAX_PATH;
	WCHAR  dn[MAX_PATH] = {0};
    DWORD dnlen = MAX_PATH;
    SID_NAME_USE SNU;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	HANDLE hBoundaryDescriptor = NULL;
	LPCSTR Name = "test_CreateBoundaryDescriptorA";

	/* 바운더리 디스크립터 생성 */
	hBoundaryDescriptor = CreateBoundaryDescriptorA(Name, 0);

	/* RequiredSid를 얻기 위해 수행 */
	if(!LookupAccountName(NULL, AccountName, &RequiredSid, &sidlen, dn, &dnlen, &SNU)){
        strcpy(msg, GetErrorMessage("LookupAccountName 실패 : ", GetLastError()));
		strcpy(buf, "LookupAccountName 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "LookupAccountName 성공", msg);
		
		return FALSE;
	}

	/* 바운더리 디스크립터에 SID 추가 성공 시, 바운더리 디스크립터가 생성된 것을 보장*/
	result = AddSIDToBoundaryDescriptor(&hBoundaryDescriptor, &RequiredSid);

	if(NULL != hBoundaryDescriptor && result){
		sprintf(msg, "CreateBoundaryDescriptorW 성공 : hBoundaryDescriptor = %d", hBoundaryDescriptor);
		strcpy(buf, "CreateBoundaryDescriptorW 성공");	

	}else{
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorW 실패 : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorW 실패");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorW 성공", msg);

	CloseHandle(hBoundaryDescriptor);

	return result;
}

/**
* BOOL WINAPI AddIntegrityLabelToBoundaryDescriptor (
  _Inout_HANDLE * BoundaryDescriptor,
  _In_ PSID IntegrityLabel
);
* 지정된 바운더리 디스크립터에 새로운 SID(보안 식별자)를 추가한다.
* @author : 손찬영  
*
* @param  BoundaryDescriptor	바운더리 디스크립터 핸들
* @param  IntegrityLabel		네임 스페이스의 필수 무결성 수준을 나타내는 SID 구조 의 포인터
* @return						성공/실패 여부
*/
BOOL test_AddIntegrityLabelToBoundaryDescriptor()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	SID   IntegrityLabel;
	const wchar_t *AccountName = L"Everyone";
	DWORD sidlen = MAX_PATH;
	WCHAR  dn[MAX_PATH] = {0};
    DWORD dnlen = MAX_PATH;
    SID_NAME_USE SNU;

	LPTSTR StringSid[BUFSIZ] = {0,};

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif


	HANDLE hBoundaryDescriptor = NULL;
	LPCTSTR Name = L"test_CreateBoundaryDescriptorW";

	hBoundaryDescriptor = CreateBoundaryDescriptorW(Name, 0);
	if(NULL == hBoundaryDescriptor){
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorW 실패 : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorW 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorW 성공", msg);
		
		return FALSE;
	}

	if(!LookupAccountName(NULL, AccountName, &IntegrityLabel, &sidlen, dn, &dnlen, &SNU)){
        strcpy(msg, GetErrorMessage("LookupAccountName 실패 : ", GetLastError()));
		strcpy(buf, "LookupAccountName 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "LookupAccountName 성공", msg);
		
		return FALSE;
	}
	result = AddIntegrityLabelToBoundaryDescriptor(&hBoundaryDescriptor, &IntegrityLabel);

	if(result){
		sprintf(msg, "AddIntegrityLabelToBoundaryDescriptor 성공");
		strcpy(buf, msg);	

	}else{
		strcpy(msg, GetErrorMessage("AddIntegrityLabelToBoundaryDescriptor 실패 : ", GetLastError()));
		strcpy(buf, "AddIntegrityLabelToBoundaryDescriptor 실패");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "AddIntegrityLabelToBoundaryDescriptor 성공", msg);

	CloseHandle(hBoundaryDescriptor);

	return result;

}


/**
* VOID AddSIDToBoundaryDescriptor(HANDLE *BoundaryDescriptor, PSID RequiredSid)
* 지정된 바운더리 디스크립터에 SID(보안 식별자)를 추가한다.
* @author : 손찬영  
*
* @param  BoundaryDescriptor 바운더리 디스크립터 핸들
* @param  RequiredSid SID 구조체에 대한 포인터
* @return 성공/실패 여부
*/
BOOL test_AddSIDToBoundaryDescriptor()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hBoundaryDescriptor = NULL;
	LPCTSTR Name = L"test_AddSIDToBoundaryDescriptor";
	SID   RequiredSid;

	const wchar_t *AccountName = L"Everyone";
	DWORD sidlen = MAX_PATH;
	WCHAR  dn[MAX_PATH] = {0};
    DWORD dnlen = MAX_PATH;
    SID_NAME_USE SNU;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hBoundaryDescriptor = CreateBoundaryDescriptorW(Name, 0);
	if(NULL == hBoundaryDescriptor){
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorW 실패 : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorW 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorW 성공", msg);
		
		return FALSE;
	}

	if(!LookupAccountName(NULL, AccountName, &RequiredSid, &sidlen, dn, &dnlen, &SNU)){
        strcpy(msg, GetErrorMessage("LookupAccountName 실패 : ", GetLastError()));
		strcpy(buf, "LookupAccountName 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "LookupAccountName 성공", msg);
		
		return FALSE;
	}

	result = AddSIDToBoundaryDescriptor(&hBoundaryDescriptor, &RequiredSid);

	if(result){
		sprintf(msg, "AddSIDToBoundaryDescriptor 성공");
		strcpy(buf, msg);	

	}else{
		strcpy(msg, GetErrorMessage("AddSIDToBoundaryDescriptor 실패 : ", GetLastError()));
		strcpy(buf, "AddSIDToBoundaryDescriptor 실패");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "AddSIDToBoundaryDescriptor 성공", msg);



	return result;
}

/**
* HANDLE OpenPrivateNamespaceW(LPVOID lpBoundaryDescriptor, LPCTSTR lpAliasPrefix)
* 개인 네임 스페이스를 연다.
* @author : 손찬영  
*
* @param  lpBoundaryDescriptor 네임 스페이스를 분리하는 방법을 정의하는 설명자
* @param  lpAliasPrefix 네임 스페이스의 접두사
* @return 기존 네임 스페이스의 핸들
*/
BOOL test_OpenPrivateNamespaceW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hBoundaryDescriptor = NULL, hNamespaceCreate = NULL, hNamespaceOpen = NULL;
	LPCTSTR Name = L"test_OpenPrivateNamespaceW";
	LPCTSTR lpAliasPrefix = L"CreatePrivateNamespaceW";
	LPCTSTR lpAliasPrefix2 = L"test_OpenPrivateNamespaceW";

	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hBoundaryDescriptor = CreateBoundaryDescriptorW(Name, 0);
	if(NULL == hBoundaryDescriptor){
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorW 실패 : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorW 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorW 성공", msg);
		
		return FALSE;
	}

	hNamespaceCreate = CreatePrivateNamespaceW(NULL, hBoundaryDescriptor, lpAliasPrefix);
	if(NULL == hNamespaceCreate){
		sprintf(msg, "CreatePrivateNamespaceW 실패");
		strcpy(buf, msg);	

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreatePrivateNamespaceW 성공", msg);

		return FALSE;
	}

	hNamespaceOpen = OpenPrivateNamespaceW(hBoundaryDescriptor, lpAliasPrefix2);
	if(NULL != hNamespaceOpen){
		sprintf(msg, "OpenPrivateNamespaceW 성공 : hNamespaceOpen = %d", hNamespaceOpen);
		strcpy(buf, "OpenPrivateNamespaceW 성공");	
	}else{
		strcpy(msg, GetErrorMessage("OpenPrivateNamespaceA 실패 : ", GetLastError()));
		strcpy(buf, "OpenPrivateNamespaceA 실패");
		
		result = FALSE;

	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenPrivateNamespaceW 성공", msg);

	
	CloseHandle(hNamespaceOpen);
	ClosePrivateNamespace(hNamespaceOpen, PRIVATE_NAMESPACE_FLAG_DESTROY);
	CloseHandle(hNamespaceCreate);
	ClosePrivateNamespace(hNamespaceCreate, PRIVATE_NAMESPACE_FLAG_DESTROY);
	CloseHandle(hBoundaryDescriptor);

	return result;
}

/**
* HANDLE OpenPrivateNamespaceA(LPVOID lpBoundaryDescriptor, LPCTSTR lpAliasPrefix)
* 개인 네임 스페이스를 연다.
* @author : 손찬영  
*
* @param  lpBoundaryDescriptor 네임 스페이스를 분리하는 방법을 정의하는 설명자
* @param  lpAliasPrefix 네임 스페이스의 접두사
* @return 기존 네임 스페이스의 핸들
*/
BOOL test_OpenPrivateNamespaceA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hBoundaryDescriptor = NULL, hNamespaceCreate = NULL, hNamespaceOpen = NULL;
	LPCTSTR Name = L"test_OpenPrivateNamespaceW";
	LPCTSTR lpAliasPrefix = L"CreatePrivateNamespaceW";
	LPCSTR lpAliasPrefix2 = "test_OpenPrivateNamespaceW";

	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hBoundaryDescriptor = CreateBoundaryDescriptorW(Name, 0);
	if(NULL == hBoundaryDescriptor){
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorW 실패 : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorW 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorW 성공", msg);
		
		return FALSE;
	}

	hNamespaceCreate = CreatePrivateNamespaceW(NULL, hBoundaryDescriptor, lpAliasPrefix);
	if(NULL == hNamespaceCreate){
		sprintf(msg, "CreatePrivateNamespaceW 실패");
		strcpy(buf, msg);	

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreatePrivateNamespaceW 성공", msg);

		return FALSE;
	}

	hNamespaceOpen = OpenPrivateNamespaceA(hBoundaryDescriptor, lpAliasPrefix2);
	if(NULL != hNamespaceOpen){
		sprintf(msg, "OpenPrivateNamespaceA 성공 : hNamespaceOpen = %d", hNamespaceOpen);
		strcpy(buf, "OpenPrivateNamespaceA 성공");	
	}else{
		strcpy(msg, GetErrorMessage("OpenPrivateNamespaceA 실패 : ", GetLastError()));
		strcpy(buf, "OpenPrivateNamespaceA 실패");
		
		result = FALSE;

	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenPrivateNamespaceA 성공", msg);

	
	CloseHandle(hNamespaceOpen);
	ClosePrivateNamespace(hNamespaceOpen, PRIVATE_NAMESPACE_FLAG_DESTROY);
	CloseHandle(hNamespaceCreate);
	ClosePrivateNamespace(hNamespaceCreate, PRIVATE_NAMESPACE_FLAG_DESTROY);
	CloseHandle(hBoundaryDescriptor);

	return result;
}

/**
* HANDLE CreatePrivateNamespaceW(LPSECURITY_ATTRIBUTES  lpPrivateNamespaceAttributes, LPVOID lpBoundaryDescriptor, LPCTSTR lpAliasPrefix)
* 비공개 네임 스페이스를 생성한다.
* @author : 손찬영  
*
* @param  lpPrivateNamespaceAttributes 네임 스페이스 개체의 보안 특성을 지정 하는 SECURITY_ATTRIBUTES 구조체에 대한 포인터
* @param  lpBoundaryDescriptor 네임 스페이스를 분리하는 방법을 정의하는 설명자
* @param  lpAliasPrefix 네임 스페이스의 접두사
* @return 생성된 네임 스페이스에 대한 핸들
*/
BOOL test_CreatePrivateNamespaceW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hBoundaryDescriptor = NULL, hNamespace = NULL;
	LPCTSTR Name = L"test_CreatePrivateNamespaceW";
	LPCTSTR lpAliasPrefix = L"test_CreatePrivateNamespaceW";

	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hBoundaryDescriptor = CreateBoundaryDescriptorW(Name, 0);
	if(NULL == hBoundaryDescriptor){
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorW 실패 : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorW 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorW 성공", msg);
		
		return FALSE;
	}

	hNamespace = CreatePrivateNamespaceW(NULL, hBoundaryDescriptor, lpAliasPrefix);
	/* 첫번째 CreatePrivateNamespaceW가 성공하고 두번째는 실패하는 것을 확인 */
	if(NULL != hNamespace){
		if(!CreatePrivateNamespaceW(NULL, hBoundaryDescriptor, lpAliasPrefix)){
			sprintf(msg, "CreatePrivateNamespaceW 성공 : hNamespace = %d", hNamespace);
			strcpy(buf, "CreatePrivateNamespaceW 성공");	
		
		/* 두번째 CreatePrivateNamespaceW도 성공한 경우는 실패 */
		}else{
			strcpy(msg, "CreatePrivateNamespaceW 실패 : 이미 존재하는 네임스페이스 재생성에 성공함");
			strcpy(buf, "CreatePrivateNamespaceW 실패");

			result = FALSE;
		}
	}else{
		strcpy(msg, GetErrorMessage("CreatePrivateNamespaceW 실패 : ", GetLastError()));
		strcpy(buf, "CreatePrivateNamespaceW 실패");
		
		result = FALSE;

	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreatePrivateNamespaceW 성공", msg);

	
	CloseHandle(hNamespace);
	ClosePrivateNamespace(hNamespace, PRIVATE_NAMESPACE_FLAG_DESTROY);
	CloseHandle(hBoundaryDescriptor);

	return result;

}

/**
* HANDLE CreatePrivateNamespaceA(LPSECURITY_ATTRIBUTES  lpPrivateNamespaceAttributes, LPVOID lpBoundaryDescriptor, LPCTSTR lpAliasPrefix)
* 비공개 네임 스페이스를 생성한다.
* @author : 손찬영  
*
* @param  lpPrivateNamespaceAttributes 네임 스페이스 개체의 보안 특성을 지정 하는 SECURITY_ATTRIBUTES 구조체에 대한 포인터
* @param  lpBoundaryDescriptor 네임 스페이스를 분리하는 방법을 정의하는 설명자
* @param  lpAliasPrefix 네임 스페이스의 접두사
* @return 생성된 네임 스페이스에 대한 핸들
*/
BOOL test_CreatePrivateNamespaceA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hBoundaryDescriptor = NULL, hNamespace = NULL;
	LPCSTR Name = "test_CreatePrivateNamespaceA";
	LPCSTR lpAliasPrefix = "test_CreatePrivateNamespaceA";

	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hBoundaryDescriptor = CreateBoundaryDescriptorA(Name, 0);
	if(NULL == hBoundaryDescriptor){
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorA 실패 : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorA 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorA 성공", msg);
		
		return FALSE;
	}

	hNamespace = CreatePrivateNamespaceA(NULL, hBoundaryDescriptor, lpAliasPrefix);
	/* 첫번째 CreatePrivateNamespaceA가 성공하고 두번째는 실패하는 것을 확인 */
	if(NULL != hNamespace){
		if(!CreatePrivateNamespaceA(NULL, hBoundaryDescriptor, lpAliasPrefix)){
			sprintf(msg, "CreatePrivateNamespaceA 성공 : hNamespace = %d", hNamespace);
			strcpy(buf, "CreatePrivateNamespaceA 성공");	
		
		/* 두번째 CreatePrivateNamespaceA도 성공한 경우는 실패 */
		}else{
			strcpy(msg, "CreatePrivateNamespaceA 실패 : 이미 존재하는 네임스페이스 재생성에 성공함");
			strcpy(buf, "CreatePrivateNamespaceA 실패");

			result = FALSE;
		}
	}else{
		strcpy(msg, GetErrorMessage("CreatePrivateNamespaceA 실패 : ", GetLastError()));
		strcpy(buf, "CreatePrivateNamespaceA 실패");
		
		result = FALSE;

	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreatePrivateNamespaceA 성공", msg);

	
	CloseHandle(hNamespace);
	ClosePrivateNamespace(hNamespace, PRIVATE_NAMESPACE_FLAG_DESTROY);
	CloseHandle(hBoundaryDescriptor);

	return result;
}

/**
* BOOLEAN ClosePrivateNamespace(HANDLE Handle, ULONG  Flags)
* 열린 네임 스페이스 핸들을 닫는다.
* @author : 손찬영  
*
* @param  Handle 네임 스페이스 핸들
* @param  Flags 이 매개 변수가 PRIVATE_NAMESPACE_FLAG_DESTROY (0x00000001)이면 네임 스페이스가 소멸
* @return 성공/실패여부
*/
BOOL test_ClosePrivateNamespace()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hBoundaryDescriptor = NULL, hNamespace = NULL;
	LPCTSTR Name = L"test_CreatePrivateNamespaceW";
	LPCTSTR lpAliasPrefix = L"test_CreatePrivateNamespaceW";

	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hBoundaryDescriptor = CreateBoundaryDescriptorW(Name, 0);
	if(NULL == hBoundaryDescriptor){
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorW 실패 : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorW 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorW 성공", msg);
		
		return FALSE;
	}

	hNamespace = CreatePrivateNamespaceW(NULL, hBoundaryDescriptor, lpAliasPrefix);
	if(NULL == hNamespace){
		strcpy(msg, GetErrorMessage("CreatePrivateNamespaceW 실패 : ", GetLastError()));
		strcpy(buf, "CreatePrivateNamespaceW 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreatePrivateNamespaceW 성공", msg);

		return FALSE;

	}
	
	/* ClosePrivateNamespace를 2회 시도하여 첫번째는 성공, 두번째는 실패하면 테스트 성공으로 판단 */
	if(ClosePrivateNamespace(hNamespace, PRIVATE_NAMESPACE_FLAG_DESTROY)){
		if(!ClosePrivateNamespace(hNamespace, PRIVATE_NAMESPACE_FLAG_DESTROY)){
			sprintf(msg, "ClosePrivateNamespace 성공");
			strcpy(buf, "ClosePrivateNamespace 성공");	
		
		}else{
			strcpy(msg, GetErrorMessage("ClosePrivateNamespace 실패 : ", GetLastError()));
		strcpy(buf, "ClosePrivateNamespace 실패");
		
		result = FALSE;
		}
	}else{
		strcpy(msg, GetErrorMessage("ClosePrivateNamespace 실패 : ", GetLastError()));
		strcpy(buf, "ClosePrivateNamespace 실패");
		
		result = FALSE;
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ClosePrivateNamespace 성공", msg);

	CloseHandle(hBoundaryDescriptor);

	return result;
}