#include "TestSecurity.h"


/**
* BOOL WINAPI SetFileSecurity(
  _In_ LPCTSTR              lpFileName,
  _In_ SECURITY_INFORMATION SecurityInformation,
  _In_ PSECURITY_DESCRIPTOR pSecurityDescriptor
);
* �����̳� ���丮 ������Ʈ�� ������ ����. ���̻� ������ ����.
* @author : ������  
*
* @param  lpFileName			������ ������ ���� �Ǵ� ���丮�� �����ϴ� �� (null)�� ������ ���ڿ��� ���� ������
* @param  SecurityInformation	SECURITY_INFORMATION ����ü
* @param  pSecurityDescriptor	SECURITY_DESCRIPTOR ����ü�� ���� ������
* @return						����/���� ����
*/
BOOL test_SetFileSecurityW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;

	LPCWSTR pathName = L"������\\test_SetFileAttributesW";

	BYTE SDBuffer[4096] = {0, };
    DWORD SDLength = 4096, RC;
    SECURITY_DESCRIPTOR* SD = (SECURITY_DESCRIPTOR*)SDBuffer;

	DWORD nLengthNeeded = 512;

	BOOL bDaclDefaulted = TRUE, bDaclPresent = TRUE;
	LPBOOL lpbDaclDefaulted = &bDaclDefaulted, lpbDaclPresent = &bDaclPresent;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	CreateDirectory(pathName, NULL);

    // �ش� ������ �ʱ�ȭ �Ѵ�
    if(!InitializeSecurityDescriptor(SD, SECURITY_DESCRIPTOR_REVISION))
         return FALSE;

    // �� ACL �� �ϳ� �����Ѵ�.
    // SetEntriesInAcl �� �ְ�, ����� �ؾ��ϱ� ������ �ش� ��������
    // �µ��� LocalAlloc �� ����Ѵ�. SetEntriesInAcl ���� �����ϸ�
    // LocalFree �� ����ϵ��� �ǰ��ϹǷ�, �ű⿡ �����.
    PACL pACL = (PACL)LocalAlloc(LMEM_FIXED, sizeof(ACL));

    // �׳� �⺻ �ʱ�ȭ
    if(!InitializeAcl(pACL, MAX_PATH, ACL_REVISION))
    {
        LocalFree(pACL);
        return FALSE;
    }

    // ������ �� �� ����� �ٰ����� �ɼ��� �����Ѵ�.
    DWORD AccessOption = GENERIC_ALL | GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE;

    // �߰� �ϰ��� ����ڿ� ������ �����ش�. //Administrator �׸��� �����ϰ� �߰��Ѵ�.
    AddToACL(pACL, L"Everyone", AccessOption);
    //AddToACL(pACL, L"Administrator", AccessOption);
    AddToACL(pACL, L"SYSTEM", AccessOption);

    // ���� �Ӽ��� ������ ������, ������ ACL ������ �������ش�.
    if(!SetSecurityDescriptorDacl(SD, TRUE, pACL, TRUE))
    {
        LocalFree(pACL);
        return FALSE;
    }

    // �ش� �����̳�, ������ ������ �����Ų��.
    if(!(RC = SetFileSecurity(pathName, DACL_SECURITY_INFORMATION, SD))){ //setFileSecurity ����
		sprintf(msg, GetErrorMessage("SetFileSecurity ���� : ", GetLastError()));
		strcpy(buf, "SetFileSecurity ����");

		return FALSE;
	}

	//���߿� Set�ϰ� �� ������ �����ͼ� ��¥ set�ƴ��� Ȯ���� ����

	sprintf(msg, "SetFileSecurity ����");
	strcpy(buf, msg);

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "SetFileSecurity ����", msg);


    LocalFree(pACL);

	if(!RemoveDirectory(pathName)){
		#ifdef OQADBGPRINT
		printf("���丮 ���� ����\n");
		#endif
		#ifdef OQADBG
		MessageBoxA(NULL, GetErrorMessage("���� ���� ���� : ", GetLastError()), "test_SetFileSecurity", MB_OK);
		#endif
	}else{
		#ifdef OQADBGPRINT
		printf("���丮 ���� ���� : ");
		#endif
	}
    
	return RC;
}

/**
* BOOL WINAPI GetFileSecurity(
  _In_      LPCTSTR              lpFileName,
  _In_      SECURITY_INFORMATION RequestedInformation,
  _Out_opt_ PSECURITY_DESCRIPTOR pSecurityDescriptor,
  _In_      DWORD                nLength, 
  _Out_     LPDWORD              lpnLengthNeeded
);
* ���� �Ǵ� ���͸��� ���ȿ� ���� Ư�� ������ ��´�. ȹ��� ������ ȣ������ �׼��� ���� �� Ư�ǿ� ���� ���ѵȴ�. 
���̻� ������ ����.
* @author : ������  
*
* @param  lpFileName			���� ������ �˻� �� ���� �Ǵ� ���丮�� �����ϴ� �� (null)�� ������ ���ڿ��� ���� ������
* @param  RequestedInformation	��û�Ǵ� ���� ������ �ĺ� �ϴ� SECURITY_INFORMATION ��
* @param  pSecurityDescriptor	lpFileName �Ű� ������ ������ ��ü �� ���� ���� ���� ���纻�� �޴� ���ۿ� ���� ������
* @param  nLength				pSecurityDescriptor �Ű� ������ ����Ű�� ������ ũ�� (����Ʈ)
* @param  lpnLengthNeeded		��ü ���� �����ڸ� �����ϴ� �� �ʿ��� ����Ʈ ���� �޴� ������ ���� ������
* @return						����/���� ����
*/
BOOL test_GetFileSecurityW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;
	
	LPCWSTR pathName = L"������\\test_GetFileAttributesW";
	PSECURITY_DESCRIPTOR psd;
	PSID psid;
	BOOL OwnerDefaulted;
	SID_NAME_USE snu;
	DWORD sdsize;	
	wchar_t *AccountName, *DomainName;
	DWORD AccountLen, DomainLen;
	wchar_t userName[BUFSIZ];
	DWORD userNameSize = BUFSIZ;

	PACL pACL = NULL;

	GetUserName(userName, &userNameSize);
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* ���丮�� ���� */
	if(CreateDirectoryW(pathName, NULL)){
		strcpy(msg, GetErrorMessage("CreateDirectoryW ���� : ", GetLastError()));
		strcpy(buf, "CreateDirectoryW ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateDirectoryW ����", msg);

		return FALSE;
	}

	/* �ʱ�ȭ */
	psd = GlobalAlloc (GMEM_FIXED, 1000);
	AccountName = (wchar_t *)GlobalAlloc (GMEM_FIXED, 1000);
	DomainName = (wchar_t *)GlobalAlloc (GMEM_FIXED, 1000);

	AccountLen = DomainLen = 1000;

	/* ������ ���� ���� ��� */
	if(GetFileSecurityW(pathName, OWNER_SECURITY_INFORMATION, psd, 1000, & sdsize)){
		strcpy(msg, GetErrorMessage("GetFileSecurityW ���� : ", GetLastError()));
		strcpy(buf, "GetFileSecurityW ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetFileSecurityW ����", msg);

		return FALSE;
	}

	/* ������ SID ��� */
	if(GetSecurityDescriptorOwner(psd, &psid, &OwnerDefaulted)){
		strcpy(msg, GetErrorMessage("GetSecurityDescriptorOwner ���� : ", GetLastError()));
		strcpy(buf, "GetSecurityDescriptorOwner ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetSecurityDescriptorOwner ����", msg);

		return FALSE;
	}

	/* SID�� �̸����� ��ȯ */
	if(LookupAccountSidW(NULL, psid, AccountName, &AccountLen, DomainName, &DomainLen, &snu)){
		strcpy(msg, GetErrorMessage("LookupAccountSidW ���� : ", GetLastError()));
		strcpy(buf, "LookupAccountSidW ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "LookupAccountSidW ����", msg);

		return FALSE;
	}

	/* ǥ�� */
	#ifdef OQADBGPRINT
	wprintf(L"Owner Name : %s \n", AccountName);
	wprintf(L"Domain of Owner : %s \n", DomainName);
	#endif

	/* ���� ����� �̸�(������ �������� ����)�� ������ �̸��� �����ϸ� �������� �Ǵ��Ѵ�. */
	if(!wcscmp(userName, AccountName)){ 
		sprintf(msg, "GetFileSecurity ���� : ���� ������ : %S\n�α��� ����� : %S", AccountName, userName);
		strcpy(buf, "GetFileSecurity ����");

	}else{
		sprintf(msg, GetErrorMessage("GetFileSecurity ���� : ", GetLastError()));
		strcpy(buf, "GetFileSecurity ����");
		result = FALSE;	
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetFileSecurity ����", msg);

	/* �� ó�� */
	GlobalFree (psd);
	GlobalFree (AccountName);
	GlobalFree (DomainName);

	if(!RemoveDirectory(pathName)){
		#ifdef OQADBGPRINT
		printf("���丮 ���� ����\n");
		#endif
	}

	return result;
}


// AddToACL
// �־��� ACL (Access Control List )�� �ش� ������ �߰��ϰ�, ������ �����Ѵ�.
BOOL AddToACL(PACL& pACL, const wchar_t *AccountName, DWORD AccessOption)
{
    CHAR  sid[MAX_PATH] = {0};
    DWORD sidlen = MAX_PATH;
    WCHAR  dn[MAX_PATH] = {0};
    DWORD dnlen = MAX_PATH;
    SID_NAME_USE SNU;
    PACL temp = NULL;

    // �־��� ������ �̸��� ���� �ʿ��� SID �� ���Ѵ�.
    if(!LookupAccountName(NULL, AccountName, (PSID)sid, &sidlen, dn, &dnlen, &SNU))
        return FALSE;

    // Ư���� ������� accesss control �� ���� ������ �����ϴµ� ���Ǵ� ����.
    EXPLICIT_ACCESS ea = {0};
    ea.grfAccessPermissions = AccessOption;
    ea.grfAccessMode = SET_ACCESS;
    ea.grfInheritance= SUB_CONTAINERS_AND_OBJECTS_INHERIT;
    ea.Trustee.TrusteeForm = TRUSTEE_IS_SID;
    ea.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
    ea.Trustee.ptstrName  = (LPTSTR) (PSID)sid;

    // ���ο� ACL �� �����Ѵ�. ���� ������ �־����� ������ �ű⿡ �����Ͽ� �����Ѵ�.
    if(SetEntriesInAcl(1, &ea, pACL, &temp) != ERROR_SUCCESS)
        return FALSE;

    // ���� ACL �� �����ְ�, ���� �����Ѱɷ� ��ġ�Ѵ�.
    LocalFree(pACL);
    pACL = temp;

    return TRUE;
}


/**
* DWORD WINAPI GetSecurityDescriptorLength(
  _In_ PSECURITY_DESCRIPTOR pSecurityDescriptor
);
* ���������� ��ȿ�� ���� ���� ���� ���� (����Ʈ)�� ��ȯ�Ѵ�. ���̴� ���õ� ��� ������ ���̸� �����Ѵ�.
* @author : ������  
*
* @param  pSecurityDescriptor	�Լ��� �����ϴ� ������ SECURITY_DESCRIPTOR ����ü�� ���� ������. �����ʹ� ��ȿ�ϴٰ� ����
* @return						�Լ��� �����ϸ� �Լ��� SECURITY_DESCRIPTOR ����ü �� ���� (����Ʈ)�� ��ȯ
*/
BOOL test_GetSecurityDescriptorLength()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;

	LPCWSTR fileName = L"������\\test_GetSecurityDescriptorLength.txt";
	PSECURITY_DESCRIPTOR pSD;
	HANDLE hFile = NULL;
	PSID pOwner;
	PACL pDacl;
	DWORD SDLengh = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hFile = CreateFile(fileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	
	if(hFile == INVALID_HANDLE_VALUE){ //���� ���� ����
		sprintf(msg, GetErrorMessage("���� ���� ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile ����", msg);

		return FALSE;
	}


	if(GetSecurityInfo(hFile, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION, &pOwner, NULL, &pDacl, NULL, (LPVOID *)&pSD) != ERROR_SUCCESS){
		sprintf(msg, GetErrorMessage("GetSecurityInfo ���� : ", GetLastError()));
		strcpy(buf, "GetSecurityInfo ����");

		wresult(__FILE__, __LINE__ ,__FUNCTION__, buf, "GetSecurityInfo ����", msg);

		return FALSE;
	}

	if(SDLengh = GetSecurityDescriptorLength(pSD)){
		sprintf(msg, "GetSecurityDescriptorLength ���� : SDLengh = %d", SDLengh);
		strcpy(buf, "GetSecurityDescriptorLength ����");

	}else{
		sprintf(msg, GetErrorMessage("GetSecurityDescriptorLength ���� : ", GetLastError()));
		strcpy(buf, "GetSecurityDescriptorLength ����");

		result = FALSE;
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetSecurityDescriptorLength ����", msg);

	LocalFree(pSD);

	if(!CloseHandle(hFile)){
		#ifdef OQADBG
		MessageBoxA(NULL, GetErrorMessage("CloseHandle(hFile) ���� : ", GetLastError()), "test_GetFileAttributesW", MB_OK);
		#endif
	}
	if(!DeleteFileW(fileName)){
		#ifdef OQADBG
		MessageBoxA(NULL, GetErrorMessage("���� ���� ���� : ", GetLastError()), "test_GetFileAttributesW", MB_OK);
		#endif
	}


	return result;
}

/**
* DWORD WINAPI SetNamedSecurityInfo(
  _In_     LPTSTR               pObjectName,
  _In_     SE_OBJECT_TYPE       ObjectType,
  _In_     SECURITY_INFORMATION SecurityInfo,
  _In_opt_ PSID                 psidOwner,
  _In_opt_ PSID                 psidGroup,
  _In_opt_ PACL                 pDacl,
  _In_opt_ PACL                 pSacl
);
* ������ ���� ������ ������ ��ü�� ���� ���� �ڷ� �����Ѵ�. ȣ���ڴ� �̸����� ��ü�� �ĺ��Ѵ�.
* @author : ������  
*
* @param  pObjectName	���� ������ ������ ������Ʈ�� �̸��� ���� �ϴ� �� (null)�� ������ ���ڿ��� ���� ������
* @param  ObjectType	pObjectName �Ű� ������ ��� �� ��ü ������ ��Ÿ���� SE_OBJECT_TYPE �������� ��
* @param  SecurityInfo	������ ���� ������ ������ ��Ÿ���� ��Ʈ �÷��� ��Ʈ
* @param  psidOwner		��ü�� �����ڸ� �ĺ� �ϴ� SID ����ü�� ������
* @param  psidGroup		��ü�� �⺻ �׷��� �ĺ��ϴ� SID�� ���� ������
* @param  pDacl			��ü�� ���� �� DACL�� ���� ������
* @param  pSacl			��ü�� ���� �� SACL�� ���� ������
* @return				�Լ��� �����ϸ� �Լ��� ERROR_SUCCESS, �����ϸ� ���� �ڵ�
*/
BOOL test_SetNamedSecurityInfoW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;

	LPWSTR pathName = L"������\\test_SetNamedSecurityInfoW";

	PSID pOwner = NULL;
	PACL pDacl = NULL;
	DWORD ret = 0;

	/*BYTE SDBuffer[4096] = {0, };
    DWORD SDLength = 4096;
    SECURITY_DESCRIPTOR* SD = (SECURITY_DESCRIPTOR*)SDBuffer;

	DWORD nLengthNeeded = 512;

	BOOL bDaclDefaulted = TRUE, bDaclPresent = TRUE;
	LPBOOL lpbDaclDefaulted = &bDaclDefaulted, lpbDaclPresent = &bDaclPresent;*/


	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	CreateDirectory(pathName, NULL);

	 // �ش� ������ �ʱ�ȭ �Ѵ�
 //   if(!InitializeSecurityDescriptor(SD, SECURITY_DESCRIPTOR_REVISION))
 //        return FALSE;

 //   // �� ACL �� �ϳ� �����Ѵ�.
 //   // SetEntriesInAcl �� �ְ�, ����� �ؾ��ϱ� ������ �ش� ��������
 //   // �µ��� LocalAlloc �� ����Ѵ�. SetEntriesInAcl ���� �����ϸ�
 //   // LocalFree �� ����ϵ��� �ǰ��ϹǷ�, �ű⿡ �����.
 //   PACL pACL = (PACL)LocalAlloc(LMEM_FIXED, sizeof(ACL));

 //   // �׳� �⺻ �ʱ�ȭ
 //   if(!InitializeAcl(pACL, MAX_PATH, ACL_REVISION))
 //   {
 //       LocalFree(pACL);
 //       return FALSE;
 //   }

 //   // ������ �� �� ����� �ٰ����� �ɼ��� �����Ѵ�.
 //   DWORD AccessOption = GENERIC_ALL | GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE;

 //   // �߰� �ϰ��� ����ڿ� ������ �����ش�. //Administrator �׸��� �����ϰ� �߰��Ѵ�.
 //   AddToACL(pACL, L"Everyone", AccessOption);
 //   //AddToACL(pACL, L"Administrator", AccessOption);
 //   AddToACL(pACL, L"SYSTEM", AccessOption);

	// // ���� �Ӽ��� ������ ������, ������ ACL ������ �������ش�.
 //   if(!SetSecurityDescriptorDacl(SD, TRUE, pACL, TRUE))
 //   {
 //       LocalFree(pACL);
 //       return FALSE;
 //   }
	//pOwner = SD->Owner;
	//pACL = SD->Dacl;



	// �ش� �����̳�, ������ ������ �����Ų��.
	if((ret = SetNamedSecurityInfoW(pathName, SE_FILE_OBJECT, ATTRIBUTE_SECURITY_INFORMATION, NULL, NULL, NULL, NULL)) == ERROR_SUCCESS){ //SetNamedSecurityInfoW ����
		sprintf(msg, "SetNamedSecurityInfoW ����");
		strcpy(buf, msg);

	}else{ //SetNamedSecurityInfoW ����
		sprintf(msg, GetErrorMessage("SetNamedSecurityInfoW ���� : ", ret));
		strcpy(buf, "SetNamedSecurityInfoW ����");

		result = FALSE;
	}

	//���߿� Set�ϰ� �� ������ �����ͼ� ��¥ set�ƴ��� Ȯ���� ����


	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "SetNamedSecurityInfoW ����", msg);


    //LocalFree(pDacl);
	//LocalFree(pOwner);

	if(!RemoveDirectory(pathName)){
		#ifdef OQADBGPRINT
		printf("���丮 ���� ����\n");
		#endif
		#ifdef OQADBG
		MessageBoxA(NULL, GetErrorMessage("���� ���� ���� : ", GetLastError()), "test_SetNamedSecurityInfoW", MB_OK);
		#endif
	}else{
		#ifdef OQADBGPRINT
		printf("���丮 ���� ���� : ");
		#endif
	}
    
	return result;
}


/**
* DWORD WINAPI GetNamedSecurityInfo(
  _In_      LPTSTR               pObjectName,
  _In_      SE_OBJECT_TYPE       ObjectType,
  _In_      SECURITY_INFORMATION SecurityInfo,
  _Out_opt_ PSID                 *ppsidOwner,
  _Out_opt_ PSID                 *ppsidGroup,
  _Out_opt_ PACL                 *ppDacl,
  _Out_opt_ PACL                 *ppSacl,
  _Out_opt_ PSECURITY_DESCRIPTOR *ppSecurityDescriptor
);
* name���� ������ ��ü�� ���� ���� ���� ���� ���纻�� �˻��Ѵ�.
* @author : ������  
*
* @param  pObjectName			���� ������ ������ ������Ʈ�� �̸��� ���� �ϴ� �� (null)�� ������ ���ڿ��� ���� ������
* @param  ObjectType			pObjectName �Ű� ������ ��� �� ��ü ������ ��Ÿ���� SE_OBJECT_TYPE �������� ��
* @param  SecurityInfo			������ ���� ������ ������ ��Ÿ���� ��Ʈ �÷��� ��Ʈ
* @param  ppsidOwner			ppSecurityDescriptor ���� ��ȯ�� ���� �������� ������ SID�� ���� �����͸� �޴� ������ ���� ������ 
* @param  ppsidGroup			��ȯ�� ���� �������� �� �׷� SID�� ���� �����͸� �޴� ������ ���� ������
* @param  ppDacl				��ȯ �� ���� �����ڿ��� DACL�� ���� �����͸��޴� ������ ���� ������
* @param  ppSacl				��ȯ �� ���� ���� ���� SACL�� ���� �����͸��޴� ������ ���� ������
* @param  ppSecurityDescriptor	��ü�� ���� �����ڿ� ���� �����͸� �޴� ������ ���� ������
* @return						�Լ��� �����ϸ� �Լ��� ERROR_SUCCESS, �����ϸ� ���� �ڵ�
*/
BOOL test_GetNamedSecurityInfoW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;

	LPWSTR pathName = L"������\\test_GetNamedSecurityInfoW";

	PSECURITY_DESCRIPTOR pSD = NULL;
	PSID psid;
	BOOL OwnerDefaulted;
	wchar_t *AccountName = NULL, *DomainName = NULL;
	SID_NAME_USE snu;
	PSID pOwner = NULL;
	PACL pDacl = NULL;
	DWORD AccountLen = 1024, DomainLen = 1024;
	DWORD ret = 0;
	wchar_t userName[BUFSIZ];
	DWORD userNameSize = BUFSIZ;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* �׽�Ʈ�� ������ ���� �����ϱ� ������ Administrators�� �ϵ��ڵ� */
	//GetUserName(userName, &userNameSize);	
	wcscpy(userName, L"Administrators");

	/* ���������� �������� ���� ���丮�� �����Ѵ�. */
	CreateDirectory(pathName, NULL);

	//pSD = GlobalAlloc (GMEM_FIXED, 1000);
	AccountName = (wchar_t *)GlobalAlloc (GMEM_FIXED, AccountLen);
	DomainName = (wchar_t *)GlobalAlloc (GMEM_FIXED, DomainLen);



	/* �ش� �����̳�, ������ ������ �����Ų��. */
	ret = GetNamedSecurityInfoW(pathName, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION, &pOwner, NULL, &pDacl, NULL, &pSD);
	if(ret == ERROR_SUCCESS){
		/* ������ SID ��� */
		GetSecurityDescriptorOwner(pSD, &psid, &OwnerDefaulted);

		/* SID�� �̸����� ��ȯ */
		LookupAccountSid(NULL, psid, AccountName, &AccountLen, DomainName, &DomainLen, &snu);

		#ifdef OQADBGPRINT
		printf("AccountName = %S\n", AccountName);
		#endif

		/* ���� ����� �̸�(������)�� ������ ���丮�� ������ �̸��� �����ϸ� ���� */
		if(!wcscmp(userName, AccountName)){ 
			sprintf(msg, "GetNamedSecurityInfoW ���� : ���� ������ : %S\n�α��� ����� : %S", AccountName, userName);
			strcpy(buf, "GetNamedSecurityInfoW ����");

		/* �Լ��� ���������� �� �̸��� ���� ���� ���� ��� */
		}else{ 
			sprintf(msg, "GetNamedSecurityInfoW ���� : %S(������) != %S(�����)", AccountName, userName);
			strcpy(buf, "GetNamedSecurityInfoW ����");
			result = FALSE;	
		}

	/* �Լ� ���� */
	}else{
		sprintf(msg, GetErrorMessage("GetNamedSecurityInfoW ���� : ", ret));
		strcpy(buf, "GetNamedSecurityInfoW ����");

		result = FALSE;
	}


	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetNamedSecurityInfoW ����", msg);

	/* �ڿ� ���� */
	LocalFree(pSD);
    LocalFree(pDacl);
	LocalFree(pOwner);

	if(!RemoveDirectory(pathName)){
		#ifdef OQADBGPRINT
		printf("���丮 ���� ����\n");
		#endif
	}


	return result;
}


/**
* BOOL ConvertSidToStringSid(
  _In_  PSID   Sid,
  _Out_ LPTSTR *StringSid
);
* ���Ƚĺ���(SID)�� ǥ��, ����, �����ϱ� ������ ���� ���ڿ��� ��ȯ�Ѵ�.
* @author : ������  
*
* @param  Sid		��ȯ �� SID ����ü ������
* @param  StringSid	��ȯ�� SID ���ڿ��� ���� ������
* @return			����/���� ����
*/
BOOL test_ConvertSidToStringSidW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;


	char  sid[MAX_PATH] = {0};
    DWORD sidlen = MAX_PATH;
    WCHAR  dn[MAX_PATH] = {0};
    DWORD dnlen = MAX_PATH;
    SID_NAME_USE SNU;
    PACL pACL = NULL;
	wchar_t *AccountName = L"Administrators";
	DWORD AccessOption = GENERIC_ALL | GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE;


	PSID pSid = NULL;
	LPTSTR *StringSid = (LPTSTR *)malloc(sizeof(CHAR)*BUFSIZ);

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

    // �־��� ������ �̸��� ���� �ʿ��� SID �� ���Ѵ�.
	if(!LookupAccountName(NULL, AccountName, (PSID)sid, &sidlen, dn, &dnlen, &SNU)){
		sprintf(msg, GetErrorMessage("LookupAccountName ���� : ", GetLastError()));
		strcpy(buf, "LookupAccountName ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "LookupAccountName ����", msg);

		return FALSE;
	}

	pSid = sid;
	result = ConvertSidToStringSidW(pSid, StringSid);
	if(result){
		if((!wcscmp(*StringSid, L"S-1-5-32-544"))){
			sprintf(msg, "ConvertSidToStringSidW ���� : [%S]'s sid = %S", AccountName, *StringSid);
			strcpy(buf, "ConvertSidToStringSidW ����");

		/* �Լ��� ���������� administrators�� SID �� S-1-5-32-544�� �ƴ� */
		}else{
			sprintf(msg, "ConvertSidToStringSidW ���� : StringSid = %S", *StringSid);
			strcpy(buf, "ConvertSidToStringSidW ����");
			result = FALSE;	
		}
	}else{
		sprintf(msg, GetErrorMessage("ConvertSidToStringSidW ���� : ", GetLastError()));
		strcpy(buf, "ConvertSidToStringSidW ����");
		result = FALSE;	
	}

	isManual = FALSE;
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "ConvertSidToStringSidW ����", msg);

	//LocalFree(StringSid);

	return result;
}

/**
* BOOL WINAPI SetSecurityDescriptorGroup(
  _Inout_  PSECURITY_DESCRIPTOR pSecurityDescriptor,
  _In_opt_ PSID                 pGroup,
  _In_     BOOL                 bGroupDefaulted
);
* �ֿ� �׷� ������ ������ ���� ��ũ���͸� �̹� �����ϴ� ������ �׷������� ������ ���ȵ�ũ���ͷ� ��ü�Ѵ�.
* @author : ������  
*
* @param  pSecurityDescriptor	�׷��� ���� �ϴ� SECURITY_DESCRIPTOR ����ü�� ���� ������
* @param  pGroup				���� �������� �� �׷쿡 ���� SID ����ü�� ������
* @param  bGroupDefaulted		�׷� ������ �⺻ ��Ŀ���򿡼� �Ļ��Ǿ����� ����. �� ���� TRUE �̸� �⺻ ����
* @return						����/���� ����
*/
BOOL test_SetSecurityDescriptorGroup()
{
	BOOL result = TRUE;	 
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	PSID psid = NULL;
	SECURITY_DESCRIPTOR sd;
	BOOL GroupDefault = FALSE;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif


	if(!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION)){
		sprintf(msg, GetErrorMessage("InitializeSecurityDescriptor ���� : ", GetLastError()));
		strcpy(buf, "InitializeSecurityDescriptor ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "InitializeSecurityDescriptor ����", msg);

		return FALSE;
	}

	if(!IsValidSecurityDescriptor(&sd)){
		sprintf(msg, GetErrorMessage("IsValidSecurityDescriptor ���� : ", GetLastError()));
		strcpy(buf, "IsValidSecurityDescriptor ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "IsValidSecurityDescriptor ����", msg);

		return FALSE;
	}

	
	/*if(!GetSecurityDescriptorGroup(&sd, &psid, &GroupDefault)){
		sprintf(msg, GetErrorMessage("GetSecurityDescriptorGroup ���� : ", GetLastError()));
		strcpy(buf, "GetSecurityDescriptorGroup ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetSecurityDescriptorGroup ����", msg);

		return FALSE;
		
	}*/
	result = SetSecurityDescriptorGroup(&sd, psid, FALSE);

	if(result){
		sprintf(msg, "SetSecurityDescriptorGroup ����");
		strcpy(buf, "SetSecurityDescriptorGroup ����");

	}else{
		sprintf(msg, GetErrorMessage("SetSecurityDescriptorGroup ���� : ", GetLastError()));
		strcpy(buf, "SetSecurityDescriptorGroup ����");

		result = FALSE;
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "SetSecurityDescriptorGroup ����", msg);


	return result;
}

/**
* BOOL WINAPI SetSecurityDescriptorOwner(
  _Inout_  PSECURITY_DESCRIPTOR pSecurityDescriptor,
  _In_opt_ PSID                 pOwner,
  _In_     BOOL                 bOwnerDefaulted
);
* �ֿ� ������ ������ ������ ���� ��ũ���͸� �̹� �����ϴ� ������ ������������ ������ ���ȵ�ũ���ͷ� ��ü�Ѵ�.
* @author : ������  
*
* @param  pSecurityDescriptor	�׷��� ���� �ϴ� SECURITY_DESCRIPTOR ����ü�� ���� ������
* @param  pGroup				���� �������� �� �׷쿡 ���� SID ����ü�� ������
* @param  bOwnerDefaulted		������ ������ �⺻ ��Ŀ���򿡼� �Ļ��Ǿ����� ����. �� ���� TRUE �̸� �⺻ ����
* @return						����/���� ����
*/
BOOL test_SetSecurityDescriptorOwner()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	PSID psid = NULL;
	SECURITY_DESCRIPTOR sd;
	BOOL OwnerDefault = FALSE;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif


	if(!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION)){
		sprintf(msg, GetErrorMessage("InitializeSecurityDescriptor ���� : ", GetLastError()));
		strcpy(buf, "InitializeSecurityDescriptor ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "InitializeSecurityDescriptor ����", msg);

		return FALSE;
	}

	if(!IsValidSecurityDescriptor(&sd)){
		sprintf(msg, GetErrorMessage("IsValidSecurityDescriptor ���� : ", GetLastError()));
		strcpy(buf, "IsValidSecurityDescriptor ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "IsValidSecurityDescriptor ����", msg);

		return FALSE;
	}

	
	/*if(!GetSecurityDescriptorOwner(&sd, &psid, &OwnerDefault)){
		sprintf(msg, GetErrorMessage("GetSecurityDescriptorOwner ���� : ", GetLastError()));
		strcpy(buf, "GetSecurityDescriptorOwner ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetSecurityDescriptorOwner ����", msg);

		return FALSE;
		
	}*/
	result = SetSecurityDescriptorOwner(&sd, psid, FALSE);

	if(result){
		sprintf(msg, "SetSecurityDescriptorOwner ����");
		strcpy(buf, "SetSecurityDescriptorOwner ����");

	}else{
		sprintf(msg, GetErrorMessage("SetSecurityDescriptorOwner ���� : ", GetLastError()));
		strcpy(buf, "SetSecurityDescriptorOwner ����");

		result = FALSE;
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "SetSecurityDescriptorOwner ����", msg);


	return result;
}