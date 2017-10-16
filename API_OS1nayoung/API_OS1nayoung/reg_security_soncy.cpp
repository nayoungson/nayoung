/**
#include "TestRegistry3_advapi.h"
#include <Windows.h>

BOOL test_SetFileSecurityW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;

	LPCWSTR pathName = L"손찬영\\test_SetFileAttributesW";

	BYTE SDBuffer[4096] = {0, };
    DWORD SDLength = 4096, RC;
    SECURITY_DESCRIPTOR* SD = (SECURITY_DESCRIPTOR*)SDBuffer;

	DWORD nLengthNeeded = 512;

	BOOL bDaclDefaulted = TRUE, bDaclPresent = TRUE;
	LPBOOL lpbDaclDefaulted = &bDaclDefaulted, lpbDaclPresent = &bDaclPresent;

	printf("test_SetFileSecurityW\n");


	CreateDirectory(pathName, NULL);

    // 해당 구조를 초기화 한다
    if(!InitializeSecurityDescriptor(SD, SECURITY_DESCRIPTOR_REVISION))
         return FALSE;

    // 빈 ACL 을 하나 생성한다.
    // SetEntriesInAcl 에 넣고, 지우고 해야하기 때문에 해당 구조에서
    // 맞도록 LocalAlloc 을 사용한다. SetEntriesInAcl 에서 생성하면
    // LocalFree 를 사용하도록 권고하므로, 거기에 맞춘다.
    PACL pACL = (PACL)LocalAlloc(LMEM_FIXED, sizeof(ACL));
	 PACL pACL2 = (PACL)LocalAlloc(LMEM_FIXED, sizeof(ACL));

    // 그냥 기본 초기화
    if(!InitializeAcl(pACL, MAX_PATH, ACL_REVISION))
    {
        LocalFree(pACL);
        return FALSE;
    }

    // 권한을 줄 때 어떤것을 줄것인지 옵션을 지정한다.
    DWORD AccessOption = GENERIC_ALL | GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE;

    // 추가 하고픈 사용자와 권한을 적어준다. //Administrator 항목을 제외하고 추가한다.
    AddToACL(pACL, L"Everyone", AccessOption);
    //AddToACL(pACL, L"Administrator", AccessOption);
    AddToACL(pACL, L"SYSTEM", AccessOption);

    // 보안 속성을 지정한 구조에, 생성한 ACL 정보를 설정해준다.
    if(!SetSecurityDescriptorDacl(SD, TRUE, pACL, TRUE))
    {
        LocalFree(pACL);
        return FALSE;
    }

    // 해당 파일이나, 폴더에 권한을 적용시킨다.
    if(!(RC = SetFileSecurity(pathName, DACL_SECURITY_INFORMATION, SD))){ //setFileSecurity 실패
		sprintf(msg, GetErrorMessage("SetFileSecurity 실패 : ", GetLastError()));
		strcpy(buf, "SetFileSecurity 실패");

		return FALSE;
	}

	//나중에 Set하고 그 정보를 가져와서 진짜 set됐는지 확인할 예정

	sprintf(msg, "SetFileSecurity 성공");
	strcpy(buf, msg);

	wresult(__FILE__, __LINE__ , "SetFileSecurity", buf, "SetFileSecurity 성공", msg);


    LocalFree(pACL);

	if(!RemoveDirectory(pathName)){
		printf("디렉토리 삭제 실패\n");
		MessageBoxA(NULL, GetErrorMessage("폴더 삭제 실패 : ", GetLastError()), "test_SetFileSecurity", MB_OK);
	}else{
		printf("디렉토리 삭제 성공\n");
	}
    
	return RC;
}

BOOL test_GetFileSecurityW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;
	
	LPCWSTR pathName = L"손찬영\\test_GetFileAttributesW";
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
		
	/* 초기화 */
	/**
	psd = GlobalAlloc (GMEM_FIXED, 1000);
	AccountName = (wchar_t *)GlobalAlloc (GMEM_FIXED, 1000);
	DomainName = (wchar_t *)GlobalAlloc (GMEM_FIXED, 1000);

	AccountLen = DomainLen = 1000;
	*/
	/* 파일의 보안 정보 취득 */
	//GetFileSecurity(pathName, OWNER_SECURITY_INFORMATION, psd, 1000, & sdsize);
	//
	/* 소유자 SID 취득 */
	//GetSecurityDescriptorOwner(psd, &psid, &OwnerDefaulted);

	/* SID를 이름으로 변환 */
	//LookupAccountSid(NULL, psid, AccountName, &AccountLen, DomainName, &DomainLen, &snu);

	/* 표시 */
	/**
	wprintf(L"Owner Name : %s \n", AccountName);
	wprintf(L"Domain of Owner : %s \n", DomainName);

	if(!wcscmp(userName, AccountName)){ //현재 사용자 이름과 소유자 이름이 동일하면 성공
		sprintf(msg, "GetFileSecurity 성공\n폴더 소유자 : %S\n로그인 사용자 : %S", AccountName, userName);
		strcpy(buf, "GetFileSecurity 성공");

	}else{
		sprintf(msg, GetErrorMessage("GetFileSecurity 실패 : ", GetLastError()));
		strcpy(buf, "GetFileSecurity 실패");
	}

	wresult(__FILE__, __LINE__ , "GetFileSecurity", buf, "GetFileSecurity 성공", msg);
	*/
	/* 후 처리 */
	/**
	GlobalFree (psd);
	GlobalFree (AccountName);
	GlobalFree (DomainName);

	if(!RemoveDirectory(pathName)){
		printf("디렉토리 삭제 실패\n");
		MessageBoxA(NULL, GetErrorMessage("폴더 삭제 실패 : ", GetLastError()), "test_GetFileSecurity", MB_OK);
	}else{
		printf("디렉토리 삭제 성공\n");
	}

	return result;
}


// AddToACL
// 주어진 ACL (Access Control List )에 해당 유저를 추가하고, 권한을 설정한다.
BOOL AddToACL(PACL& pACL, const wchar_t *AccountName, DWORD AccessOption)
{
    CHAR  sid[MAX_PATH] = {0};
    DWORD sidlen = MAX_PATH;
    WCHAR  dn[MAX_PATH] = {0};
    DWORD dnlen = MAX_PATH;
    SID_NAME_USE SNU;
    PACL temp = NULL;

    // 주어진 유저의 이름을 토대로 필요한 SID 를 구한다.
    if(!LookupAccountName(NULL, AccountName, (PSID)sid, &sidlen, dn, &dnlen, &SNU))
        return FALSE;

    // 특정한 사용자의 accesss control 에 대한 정보를 가공하는데 사용되는 구조.
    EXPLICIT_ACCESS ea = {0};
    ea.grfAccessPermissions = AccessOption;
    ea.grfAccessMode = SET_ACCESS;
    ea.grfInheritance= SUB_CONTAINERS_AND_OBJECTS_INHERIT;
    ea.Trustee.TrusteeForm = TRUSTEE_IS_SID;
    ea.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
    ea.Trustee.ptstrName  = (LPTSTR) (PSID)sid;

    // 새로운 ACL 을 생성한다. 만약 기존에 주어진게 있으면 거기에 머지하여 생성한다.
    if(SetEntriesInAcl(1, &ea, pACL, &temp) != ERROR_SUCCESS)
        return FALSE;

    // 기존 ACL 을 지워주고, 새로 생성한걸로 대치한다.
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

	LPCWSTR fileName = L"손찬영\\test_GetSecurityDescriptorLength.txt";
	PSECURITY_DESCRIPTOR pSD;
	HANDLE hFile = NULL;
	PSID pOwner;
	PACL pDacl;
	DWORD SDLengh = 0;

	printf("test_GetFileSecurityW\n");

	hFile = CreateFile(fileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	
	if(hFile == INVALID_HANDLE_VALUE){ //파일 열기 실패
		sprintf(msg, GetErrorMessage("파일 열기 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,"GetSecurityDescriptorLength", msg, "CreateFile 성공", msg);

		return FALSE;
	}


	if(GetSecurityInfo(hFile, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION, &pOwner, NULL, &pDacl, NULL, (LPVOID *)&pSD) != ERROR_SUCCESS){
		sprintf(msg, GetErrorMessage("GetSecurityInfo 실패 : ", GetLastError()));
		strcpy(buf, "GetSecurityInfo 실패");

		wresult(__FILE__, __LINE__ , "GetSecurityDescriptorLength", buf, "GetSecurityInfo 성공", msg);

		return FALSE;
	}

	if(SDLengh = GetSecurityDescriptorLength(pSD)){
		sprintf(msg, "GetSecurityDescriptorLength 성공\nSDLengh = %d", SDLengh);
		strcpy(buf, "GetSecurityDescriptorLength 성공");

	}else{
		sprintf(msg, GetErrorMessage("GetSecurityDescriptorLength 실패 : ", GetLastError()));
		strcpy(buf, "GetSecurityDescriptorLength 실패");

		result = FALSE;
	}

	wresult(__FILE__, __LINE__ , "GetSecurityDescriptorLength", buf, "GetSecurityDescriptorLength 성공", msg);

	LocalFree(pSD);

	if(!CloseHandle(hFile)){
		MessageBoxA(NULL, GetErrorMessage("CloseHandle(hFile) 실패 : ", GetLastError()), "test_GetFileAttributesW", MB_OK);
	}
	if(!DeleteFileW(fileName)){
		MessageBoxA(NULL, GetErrorMessage("파일 삭제 실패 : ", GetLastError()), "test_GetFileAttributesW", MB_OK);
	}


	return result;
}
BOOL test_SetNamedSecurityInfoW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;

	LPWSTR pathName = L"손찬영\\test_SetNamedSecurityInfoW";

	PSID pOwner = NULL;
	PACL pDacl = NULL;
	DWORD ret = 0;

	printf("test_SetNamedSecurityInfoW\n");

	//RemoveDirectory(pathName);
	CreateDirectory(pathName, NULL);

	// 해당 파일이나, 폴더에 권한을 적용시킨다.
	if((ret = SetNamedSecurityInfoW(pathName, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION, &pOwner, NULL, pDacl, NULL)) == ERROR_SUCCESS){ //SetNamedSecurityInfoW 성공
		sprintf(msg, "SetNamedSecurityInfoW 성공");
		strcpy(buf, msg);

	}else{ //SetNamedSecurityInfoW 실패
		sprintf(msg, GetErrorMessage("SetNamedSecurityInfoW 실패 : ", ret));
		strcpy(buf, "SetNamedSecurityInfoW 실패");

		result = FALSE;
	}

	//나중에 Set하고 그 정보를 가져와서 진짜 set됐는지 확인할 예정



	wresult(__FILE__, __LINE__ , "SetNamedSecurityInfoW", buf, "SetNamedSecurityInfoW 성공", msg);


    //LocalFree(pDacl);
	//LocalFree(pOwner);

	if(!RemoveDirectory(pathName)){
		printf("디렉토리 삭제 실패\n");
		MessageBoxA(NULL, GetErrorMessage("폴더 삭제 실패 : ", GetLastError()), "test_SetFileSecurity", MB_OK);
	}else{
		printf("디렉토리 삭제 성공\n");
	}
    
	return result;


	return result;
}
*/