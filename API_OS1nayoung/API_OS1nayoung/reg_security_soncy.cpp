/**
#include "TestRegistry3_advapi.h"
#include <Windows.h>

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

	printf("test_SetFileSecurityW\n");


	CreateDirectory(pathName, NULL);

    // �ش� ������ �ʱ�ȭ �Ѵ�
    if(!InitializeSecurityDescriptor(SD, SECURITY_DESCRIPTOR_REVISION))
         return FALSE;

    // �� ACL �� �ϳ� �����Ѵ�.
    // SetEntriesInAcl �� �ְ�, ����� �ؾ��ϱ� ������ �ش� ��������
    // �µ��� LocalAlloc �� ����Ѵ�. SetEntriesInAcl ���� �����ϸ�
    // LocalFree �� ����ϵ��� �ǰ��ϹǷ�, �ű⿡ �����.
    PACL pACL = (PACL)LocalAlloc(LMEM_FIXED, sizeof(ACL));
	 PACL pACL2 = (PACL)LocalAlloc(LMEM_FIXED, sizeof(ACL));

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

	wresult(__FILE__, __LINE__ , "SetFileSecurity", buf, "SetFileSecurity ����", msg);


    LocalFree(pACL);

	if(!RemoveDirectory(pathName)){
		printf("���丮 ���� ����\n");
		MessageBoxA(NULL, GetErrorMessage("���� ���� ���� : ", GetLastError()), "test_SetFileSecurity", MB_OK);
	}else{
		printf("���丮 ���� ����\n");
	}
    
	return RC;
}

BOOL test_GetFileSecurityW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;
	
	LPCWSTR pathName = L"������\\test_GetFileAttributesW";
	PSECURITY_DESCRIPTOR psd;
	PSID psid;
	SID_NAME_USE snu;
	DWORD sdsize;
	BOOL OwnerDefaulted;
	wchar_t *AccountName, *DomainName;
	DWORD AccountLen, DomainLen;
	wchar_t userName[BUFSIZ];
	DWORD userNameSize = BUFSIZ;

	PACL pACL = NULL;

	GetUserName(userName, &userNameSize);

	printf("test_GetFileSecurityW\n");

	CreateDirectory(pathName, NULL);
	*/
		
	/* �ʱ�ȭ */
	/**
	psd = GlobalAlloc (GMEM_FIXED, 1000);
	AccountName = (wchar_t *)GlobalAlloc (GMEM_FIXED, 1000);
	DomainName = (wchar_t *)GlobalAlloc (GMEM_FIXED, 1000);

	AccountLen = DomainLen = 1000;
	*/
	/* ������ ���� ���� ��� */
	//GetFileSecurity(pathName, OWNER_SECURITY_INFORMATION, psd, 1000, & sdsize);
	//
	/* ������ SID ��� */
	//GetSecurityDescriptorOwner(psd, &psid, &OwnerDefaulted);

	/* SID�� �̸����� ��ȯ */
	//LookupAccountSid(NULL, psid, AccountName, &AccountLen, DomainName, &DomainLen, &snu);

	/* ǥ�� */
	/**
	wprintf(L"Owner Name : %s \n", AccountName);
	wprintf(L"Domain of Owner : %s \n", DomainName);

	if(!wcscmp(userName, AccountName)){ //���� ����� �̸��� ������ �̸��� �����ϸ� ����
		sprintf(msg, "GetFileSecurity ����\n���� ������ : %S\n�α��� ����� : %S", AccountName, userName);
		strcpy(buf, "GetFileSecurity ����");

	}else{
		sprintf(msg, GetErrorMessage("GetFileSecurity ���� : ", GetLastError()));
		strcpy(buf, "GetFileSecurity ����");
	}

	wresult(__FILE__, __LINE__ , "GetFileSecurity", buf, "GetFileSecurity ����", msg);
	*/
	/* �� ó�� */
	/**
	GlobalFree (psd);
	GlobalFree (AccountName);
	GlobalFree (DomainName);

	if(!RemoveDirectory(pathName)){
		printf("���丮 ���� ����\n");
		MessageBoxA(NULL, GetErrorMessage("���� ���� ���� : ", GetLastError()), "test_GetFileSecurity", MB_OK);
	}else{
		printf("���丮 ���� ����\n");
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

	printf("test_GetFileSecurityW\n");

	hFile = CreateFile(fileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	
	if(hFile == INVALID_HANDLE_VALUE){ //���� ���� ����
		sprintf(msg, GetErrorMessage("���� ���� ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,"GetSecurityDescriptorLength", msg, "CreateFile ����", msg);

		return FALSE;
	}


	if(GetSecurityInfo(hFile, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION, &pOwner, NULL, &pDacl, NULL, (LPVOID *)&pSD) != ERROR_SUCCESS){
		sprintf(msg, GetErrorMessage("GetSecurityInfo ���� : ", GetLastError()));
		strcpy(buf, "GetSecurityInfo ����");

		wresult(__FILE__, __LINE__ , "GetSecurityDescriptorLength", buf, "GetSecurityInfo ����", msg);

		return FALSE;
	}

	if(SDLengh = GetSecurityDescriptorLength(pSD)){
		sprintf(msg, "GetSecurityDescriptorLength ����\nSDLengh = %d", SDLengh);
		strcpy(buf, "GetSecurityDescriptorLength ����");

	}else{
		sprintf(msg, GetErrorMessage("GetSecurityDescriptorLength ���� : ", GetLastError()));
		strcpy(buf, "GetSecurityDescriptorLength ����");

		result = FALSE;
	}

	wresult(__FILE__, __LINE__ , "GetSecurityDescriptorLength", buf, "GetSecurityDescriptorLength ����", msg);

	LocalFree(pSD);

	if(!CloseHandle(hFile)){
		MessageBoxA(NULL, GetErrorMessage("CloseHandle(hFile) ���� : ", GetLastError()), "test_GetFileAttributesW", MB_OK);
	}
	if(!DeleteFileW(fileName)){
		MessageBoxA(NULL, GetErrorMessage("���� ���� ���� : ", GetLastError()), "test_GetFileAttributesW", MB_OK);
	}


	return result;
}
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

	printf("test_SetNamedSecurityInfoW\n");

	//RemoveDirectory(pathName);
	CreateDirectory(pathName, NULL);

	// �ش� �����̳�, ������ ������ �����Ų��.
	if((ret = SetNamedSecurityInfoW(pathName, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION, &pOwner, NULL, pDacl, NULL)) == ERROR_SUCCESS){ //SetNamedSecurityInfoW ����
		sprintf(msg, "SetNamedSecurityInfoW ����");
		strcpy(buf, msg);

	}else{ //SetNamedSecurityInfoW ����
		sprintf(msg, GetErrorMessage("SetNamedSecurityInfoW ���� : ", ret));
		strcpy(buf, "SetNamedSecurityInfoW ����");

		result = FALSE;
	}

	//���߿� Set�ϰ� �� ������ �����ͼ� ��¥ set�ƴ��� Ȯ���� ����



	wresult(__FILE__, __LINE__ , "SetNamedSecurityInfoW", buf, "SetNamedSecurityInfoW ����", msg);


    //LocalFree(pDacl);
	//LocalFree(pOwner);

	if(!RemoveDirectory(pathName)){
		printf("���丮 ���� ����\n");
		MessageBoxA(NULL, GetErrorMessage("���� ���� ���� : ", GetLastError()), "test_SetFileSecurity", MB_OK);
	}else{
		printf("���丮 ���� ����\n");
	}
    
	return result;


	return result;
}
*/