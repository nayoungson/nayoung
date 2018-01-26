#include "TestNamespace.h"


/**
* VOID DeleteBoundaryDescriptor(HANDLE BoundaryDescriptor)
* ������ �ٿ���� ��ũ���͸� �����Ѵ�.
* @author : ������  
*
* @param  BoundaryDescriptor �ٿ���� ��ũ���� �ڵ�
* @return ����
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


	/* ������ Ȯ���ϱ� ���� �ٿ���� ��ũ���͸� ���� */
	hBoundaryDescriptor = CreateBoundaryDescriptorW(Name, 0);
	if(NULL == hBoundaryDescriptor){
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorW ���� : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorW ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorW ����", msg);
		
		return FALSE;
	}

	/* RequiredSid�� ũ�⸦ �������� ���� ���� */
	LookupAccountNameW(NULL, AccountName, NULL, &sidlen, NULL, &domainNameLen, &SNU);
	RequiredSid = (PSID) new BYTE[sidlen];
	domainName = (WCHAR *) new WCHAR[domainNameLen];

	/* RequiredSid�� ��� ���� ���� */	
	if(!LookupAccountNameW(NULL, AccountName, RequiredSid, &sidlen, domainName, &domainNameLen, &SNU)){
        strcpy(msg, GetErrorMessage("LookupAccountName ���� : ", GetLastError()));
		strcpy(buf, "LookupAccountName ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "LookupAccountName ����", msg);
		
		return FALSE;
	}
	
	/* SID�� ��ȿ���� ���� ��� �׽�Ʈ �ߴ� */
	if(!IsValidSid(RequiredSid)){
		strcpy(msg, GetErrorMessage("IsValidSid ���� : ", GetLastError()));
		strcpy(buf, "IsValidSid ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "IsValidSid ����", msg);
		
		return FALSE;
	}

	/* �ٿ���� ��ũ���Ϳ� SID �߰� */
	if(!AddSIDToBoundaryDescriptor(&hBoundaryDescriptor, RequiredSid)){
        strcpy(msg, GetErrorMessage("AddSIDToBoundaryDescriptor ���� : ", GetLastError()));
		strcpy(buf, "AddSIDToBoundaryDescriptor ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "AddSIDToBoundaryDescriptor ����", msg);
		
		return FALSE;
	}

	/* �ٿ���� ��ũ���� ���� */
	DeleteBoundaryDescriptor(hBoundaryDescriptor);

	/* DeleteBoundaryDescriptor�Ŀ� hBoundaryDescriptor�� SID �߰� �õ� �� �����ϸ� ������ ������ Ȯ�� */
	result = AddSIDToBoundaryDescriptor(&hBoundaryDescriptor, RequiredSid);
	
	/* �ٿ���� ��ũ���� ���� �� �߰��� �����ϸ� ���� ���з� ������ */
	if(result){
        strcpy(msg, "DeleteBoundaryDescriptor ����");
		strcpy(buf, "DeleteBoundaryDescriptor ����");

		result = FALSE;
	}else{
		//sprintf(msg, GetErrorMessage("DeleteBoundaryDescriptor ����\nAddSIDToBoundaryDescriptor ���� :", GetLastError()));
		strcpy(msg, "DeleteBoundaryDescriptor ����");	
		strcpy(buf, "DeleteBoundaryDescriptor ����");	
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "DeleteBoundaryDescriptor ����", msg);

	FreeSid(RequiredSid);
	delete domainName;
	

	return result;
}


/**
* VOID CreateBoundaryDescriptorW(LPCTSTR Name, ULONG Flags)
* �ٿ���� ��ũ���͸� �����Ѵ�.
* @author : ������  
*
* @param  Name �ٿ���� ��ũ���� �̸�
* @param  Flags ����
* @return ����
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

	/* �ٿ���� ��ũ���� ���� */
	hBoundaryDescriptor = CreateBoundaryDescriptorW(Name, 0);

	/* RequiredSid�� ��� ���� ���� */
	if(!LookupAccountName(NULL, AccountName, &RequiredSid, &sidlen, dn, &dnlen, &SNU)){
        strcpy(msg, GetErrorMessage("LookupAccountName ���� : ", GetLastError()));
		strcpy(buf, "LookupAccountName ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "LookupAccountName ����", msg);
		
		return FALSE;
	}

	/* �ٿ���� ��ũ���Ϳ� SID �߰� ���� ��, �ٿ���� ��ũ���Ͱ� ������ ���� ����*/
	result = AddSIDToBoundaryDescriptor(&hBoundaryDescriptor, &RequiredSid);

	if(NULL != hBoundaryDescriptor && result){
		sprintf(msg, "CreateBoundaryDescriptorW ���� : hBoundaryDescriptor = %d", hBoundaryDescriptor);
		strcpy(buf, "CreateBoundaryDescriptorW ����");	

	}else{
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorW ���� : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorW ����");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorW ����", msg);

	CloseHandle(hBoundaryDescriptor);

	return result;
}

/**
* VOID CreateBoundaryDescriptorA(LPCTSTR Name, ULONG Flags)
* �ٿ���� ��ũ���͸� �����Ѵ�.
* @author : ������  
*
* @param  Name �ٿ���� ��ũ���� �̸�
* @param  Flags ����
* @return ����
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

	/* �ٿ���� ��ũ���� ���� */
	hBoundaryDescriptor = CreateBoundaryDescriptorA(Name, 0);

	/* RequiredSid�� ��� ���� ���� */
	if(!LookupAccountName(NULL, AccountName, &RequiredSid, &sidlen, dn, &dnlen, &SNU)){
        strcpy(msg, GetErrorMessage("LookupAccountName ���� : ", GetLastError()));
		strcpy(buf, "LookupAccountName ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "LookupAccountName ����", msg);
		
		return FALSE;
	}

	/* �ٿ���� ��ũ���Ϳ� SID �߰� ���� ��, �ٿ���� ��ũ���Ͱ� ������ ���� ����*/
	result = AddSIDToBoundaryDescriptor(&hBoundaryDescriptor, &RequiredSid);

	if(NULL != hBoundaryDescriptor && result){
		sprintf(msg, "CreateBoundaryDescriptorW ���� : hBoundaryDescriptor = %d", hBoundaryDescriptor);
		strcpy(buf, "CreateBoundaryDescriptorW ����");	

	}else{
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorW ���� : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorW ����");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorW ����", msg);

	CloseHandle(hBoundaryDescriptor);

	return result;
}

/**
* BOOL WINAPI AddIntegrityLabelToBoundaryDescriptor (
  _Inout_HANDLE * BoundaryDescriptor,
  _In_ PSID IntegrityLabel
);
* ������ �ٿ���� ��ũ���Ϳ� ���ο� SID(���� �ĺ���)�� �߰��Ѵ�.
* @author : ������  
*
* @param  BoundaryDescriptor	�ٿ���� ��ũ���� �ڵ�
* @param  IntegrityLabel		���� �����̽��� �ʼ� ���Ἲ ������ ��Ÿ���� SID ���� �� ������
* @return						����/���� ����
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
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorW ���� : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorW ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorW ����", msg);
		
		return FALSE;
	}

	if(!LookupAccountName(NULL, AccountName, &IntegrityLabel, &sidlen, dn, &dnlen, &SNU)){
        strcpy(msg, GetErrorMessage("LookupAccountName ���� : ", GetLastError()));
		strcpy(buf, "LookupAccountName ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "LookupAccountName ����", msg);
		
		return FALSE;
	}
	result = AddIntegrityLabelToBoundaryDescriptor(&hBoundaryDescriptor, &IntegrityLabel);

	if(result){
		sprintf(msg, "AddIntegrityLabelToBoundaryDescriptor ����");
		strcpy(buf, msg);	

	}else{
		strcpy(msg, GetErrorMessage("AddIntegrityLabelToBoundaryDescriptor ���� : ", GetLastError()));
		strcpy(buf, "AddIntegrityLabelToBoundaryDescriptor ����");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "AddIntegrityLabelToBoundaryDescriptor ����", msg);

	CloseHandle(hBoundaryDescriptor);

	return result;

}


/**
* VOID AddSIDToBoundaryDescriptor(HANDLE *BoundaryDescriptor, PSID RequiredSid)
* ������ �ٿ���� ��ũ���Ϳ� SID(���� �ĺ���)�� �߰��Ѵ�.
* @author : ������  
*
* @param  BoundaryDescriptor �ٿ���� ��ũ���� �ڵ�
* @param  RequiredSid SID ����ü�� ���� ������
* @return ����/���� ����
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
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorW ���� : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorW ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorW ����", msg);
		
		return FALSE;
	}

	if(!LookupAccountName(NULL, AccountName, &RequiredSid, &sidlen, dn, &dnlen, &SNU)){
        strcpy(msg, GetErrorMessage("LookupAccountName ���� : ", GetLastError()));
		strcpy(buf, "LookupAccountName ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "LookupAccountName ����", msg);
		
		return FALSE;
	}

	result = AddSIDToBoundaryDescriptor(&hBoundaryDescriptor, &RequiredSid);

	if(result){
		sprintf(msg, "AddSIDToBoundaryDescriptor ����");
		strcpy(buf, msg);	

	}else{
		strcpy(msg, GetErrorMessage("AddSIDToBoundaryDescriptor ���� : ", GetLastError()));
		strcpy(buf, "AddSIDToBoundaryDescriptor ����");
		
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "AddSIDToBoundaryDescriptor ����", msg);



	return result;
}

/**
* HANDLE OpenPrivateNamespaceW(LPVOID lpBoundaryDescriptor, LPCTSTR lpAliasPrefix)
* ���� ���� �����̽��� ����.
* @author : ������  
*
* @param  lpBoundaryDescriptor ���� �����̽��� �и��ϴ� ����� �����ϴ� ������
* @param  lpAliasPrefix ���� �����̽��� ���λ�
* @return ���� ���� �����̽��� �ڵ�
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
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorW ���� : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorW ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorW ����", msg);
		
		return FALSE;
	}

	hNamespaceCreate = CreatePrivateNamespaceW(NULL, hBoundaryDescriptor, lpAliasPrefix);
	if(NULL == hNamespaceCreate){
		sprintf(msg, "CreatePrivateNamespaceW ����");
		strcpy(buf, msg);	

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreatePrivateNamespaceW ����", msg);

		return FALSE;
	}

	hNamespaceOpen = OpenPrivateNamespaceW(hBoundaryDescriptor, lpAliasPrefix2);
	if(NULL != hNamespaceOpen){
		sprintf(msg, "OpenPrivateNamespaceW ���� : hNamespaceOpen = %d", hNamespaceOpen);
		strcpy(buf, "OpenPrivateNamespaceW ����");	
	}else{
		strcpy(msg, GetErrorMessage("OpenPrivateNamespaceA ���� : ", GetLastError()));
		strcpy(buf, "OpenPrivateNamespaceA ����");
		
		result = FALSE;

	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenPrivateNamespaceW ����", msg);

	
	CloseHandle(hNamespaceOpen);
	ClosePrivateNamespace(hNamespaceOpen, PRIVATE_NAMESPACE_FLAG_DESTROY);
	CloseHandle(hNamespaceCreate);
	ClosePrivateNamespace(hNamespaceCreate, PRIVATE_NAMESPACE_FLAG_DESTROY);
	CloseHandle(hBoundaryDescriptor);

	return result;
}

/**
* HANDLE OpenPrivateNamespaceA(LPVOID lpBoundaryDescriptor, LPCTSTR lpAliasPrefix)
* ���� ���� �����̽��� ����.
* @author : ������  
*
* @param  lpBoundaryDescriptor ���� �����̽��� �и��ϴ� ����� �����ϴ� ������
* @param  lpAliasPrefix ���� �����̽��� ���λ�
* @return ���� ���� �����̽��� �ڵ�
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
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorW ���� : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorW ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorW ����", msg);
		
		return FALSE;
	}

	hNamespaceCreate = CreatePrivateNamespaceW(NULL, hBoundaryDescriptor, lpAliasPrefix);
	if(NULL == hNamespaceCreate){
		sprintf(msg, "CreatePrivateNamespaceW ����");
		strcpy(buf, msg);	

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreatePrivateNamespaceW ����", msg);

		return FALSE;
	}

	hNamespaceOpen = OpenPrivateNamespaceA(hBoundaryDescriptor, lpAliasPrefix2);
	if(NULL != hNamespaceOpen){
		sprintf(msg, "OpenPrivateNamespaceA ���� : hNamespaceOpen = %d", hNamespaceOpen);
		strcpy(buf, "OpenPrivateNamespaceA ����");	
	}else{
		strcpy(msg, GetErrorMessage("OpenPrivateNamespaceA ���� : ", GetLastError()));
		strcpy(buf, "OpenPrivateNamespaceA ����");
		
		result = FALSE;

	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenPrivateNamespaceA ����", msg);

	
	CloseHandle(hNamespaceOpen);
	ClosePrivateNamespace(hNamespaceOpen, PRIVATE_NAMESPACE_FLAG_DESTROY);
	CloseHandle(hNamespaceCreate);
	ClosePrivateNamespace(hNamespaceCreate, PRIVATE_NAMESPACE_FLAG_DESTROY);
	CloseHandle(hBoundaryDescriptor);

	return result;
}

/**
* HANDLE CreatePrivateNamespaceW(LPSECURITY_ATTRIBUTES  lpPrivateNamespaceAttributes, LPVOID lpBoundaryDescriptor, LPCTSTR lpAliasPrefix)
* ����� ���� �����̽��� �����Ѵ�.
* @author : ������  
*
* @param  lpPrivateNamespaceAttributes ���� �����̽� ��ü�� ���� Ư���� ���� �ϴ� SECURITY_ATTRIBUTES ����ü�� ���� ������
* @param  lpBoundaryDescriptor ���� �����̽��� �и��ϴ� ����� �����ϴ� ������
* @param  lpAliasPrefix ���� �����̽��� ���λ�
* @return ������ ���� �����̽��� ���� �ڵ�
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
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorW ���� : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorW ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorW ����", msg);
		
		return FALSE;
	}

	hNamespace = CreatePrivateNamespaceW(NULL, hBoundaryDescriptor, lpAliasPrefix);
	/* ù��° CreatePrivateNamespaceW�� �����ϰ� �ι�°�� �����ϴ� ���� Ȯ�� */
	if(NULL != hNamespace){
		if(!CreatePrivateNamespaceW(NULL, hBoundaryDescriptor, lpAliasPrefix)){
			sprintf(msg, "CreatePrivateNamespaceW ���� : hNamespace = %d", hNamespace);
			strcpy(buf, "CreatePrivateNamespaceW ����");	
		
		/* �ι�° CreatePrivateNamespaceW�� ������ ���� ���� */
		}else{
			strcpy(msg, "CreatePrivateNamespaceW ���� : �̹� �����ϴ� ���ӽ����̽� ������� ������");
			strcpy(buf, "CreatePrivateNamespaceW ����");

			result = FALSE;
		}
	}else{
		strcpy(msg, GetErrorMessage("CreatePrivateNamespaceW ���� : ", GetLastError()));
		strcpy(buf, "CreatePrivateNamespaceW ����");
		
		result = FALSE;

	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreatePrivateNamespaceW ����", msg);

	
	CloseHandle(hNamespace);
	ClosePrivateNamespace(hNamespace, PRIVATE_NAMESPACE_FLAG_DESTROY);
	CloseHandle(hBoundaryDescriptor);

	return result;

}

/**
* HANDLE CreatePrivateNamespaceA(LPSECURITY_ATTRIBUTES  lpPrivateNamespaceAttributes, LPVOID lpBoundaryDescriptor, LPCTSTR lpAliasPrefix)
* ����� ���� �����̽��� �����Ѵ�.
* @author : ������  
*
* @param  lpPrivateNamespaceAttributes ���� �����̽� ��ü�� ���� Ư���� ���� �ϴ� SECURITY_ATTRIBUTES ����ü�� ���� ������
* @param  lpBoundaryDescriptor ���� �����̽��� �и��ϴ� ����� �����ϴ� ������
* @param  lpAliasPrefix ���� �����̽��� ���λ�
* @return ������ ���� �����̽��� ���� �ڵ�
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
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorA ���� : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorA ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorA ����", msg);
		
		return FALSE;
	}

	hNamespace = CreatePrivateNamespaceA(NULL, hBoundaryDescriptor, lpAliasPrefix);
	/* ù��° CreatePrivateNamespaceA�� �����ϰ� �ι�°�� �����ϴ� ���� Ȯ�� */
	if(NULL != hNamespace){
		if(!CreatePrivateNamespaceA(NULL, hBoundaryDescriptor, lpAliasPrefix)){
			sprintf(msg, "CreatePrivateNamespaceA ���� : hNamespace = %d", hNamespace);
			strcpy(buf, "CreatePrivateNamespaceA ����");	
		
		/* �ι�° CreatePrivateNamespaceA�� ������ ���� ���� */
		}else{
			strcpy(msg, "CreatePrivateNamespaceA ���� : �̹� �����ϴ� ���ӽ����̽� ������� ������");
			strcpy(buf, "CreatePrivateNamespaceA ����");

			result = FALSE;
		}
	}else{
		strcpy(msg, GetErrorMessage("CreatePrivateNamespaceA ���� : ", GetLastError()));
		strcpy(buf, "CreatePrivateNamespaceA ����");
		
		result = FALSE;

	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreatePrivateNamespaceA ����", msg);

	
	CloseHandle(hNamespace);
	ClosePrivateNamespace(hNamespace, PRIVATE_NAMESPACE_FLAG_DESTROY);
	CloseHandle(hBoundaryDescriptor);

	return result;
}

/**
* BOOLEAN ClosePrivateNamespace(HANDLE Handle, ULONG  Flags)
* ���� ���� �����̽� �ڵ��� �ݴ´�.
* @author : ������  
*
* @param  Handle ���� �����̽� �ڵ�
* @param  Flags �� �Ű� ������ PRIVATE_NAMESPACE_FLAG_DESTROY (0x00000001)�̸� ���� �����̽��� �Ҹ�
* @return ����/���п���
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
		strcpy(msg, GetErrorMessage("CreateBoundaryDescriptorW ���� : ", GetLastError()));
		strcpy(buf, "CreateBoundaryDescriptorW ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateBoundaryDescriptorW ����", msg);
		
		return FALSE;
	}

	hNamespace = CreatePrivateNamespaceW(NULL, hBoundaryDescriptor, lpAliasPrefix);
	if(NULL == hNamespace){
		strcpy(msg, GetErrorMessage("CreatePrivateNamespaceW ���� : ", GetLastError()));
		strcpy(buf, "CreatePrivateNamespaceW ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreatePrivateNamespaceW ����", msg);

		return FALSE;

	}
	
	/* ClosePrivateNamespace�� 2ȸ �õ��Ͽ� ù��°�� ����, �ι�°�� �����ϸ� �׽�Ʈ �������� �Ǵ� */
	if(ClosePrivateNamespace(hNamespace, PRIVATE_NAMESPACE_FLAG_DESTROY)){
		if(!ClosePrivateNamespace(hNamespace, PRIVATE_NAMESPACE_FLAG_DESTROY)){
			sprintf(msg, "ClosePrivateNamespace ����");
			strcpy(buf, "ClosePrivateNamespace ����");	
		
		}else{
			strcpy(msg, GetErrorMessage("ClosePrivateNamespace ���� : ", GetLastError()));
		strcpy(buf, "ClosePrivateNamespace ����");
		
		result = FALSE;
		}
	}else{
		strcpy(msg, GetErrorMessage("ClosePrivateNamespace ���� : ", GetLastError()));
		strcpy(buf, "ClosePrivateNamespace ����");
		
		result = FALSE;
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ClosePrivateNamespace ����", msg);

	CloseHandle(hBoundaryDescriptor);

	return result;
}