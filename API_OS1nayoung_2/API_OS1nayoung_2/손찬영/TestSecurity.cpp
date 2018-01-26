#include "TestSecurity.h"


/**
* BOOL WINAPI SetFileSecurity(
  _In_ LPCTSTR              lpFileName,
  _In_ SECURITY_INFORMATION SecurityInformation,
  _In_ PSECURITY_DESCRIPTOR pSecurityDescriptor
);
* 파일이나 디렉토리 오브젝트의 보안을 설정. 더이상 사용되지 않음.
* @author : 손찬영  
*
* @param  lpFileName			보안이 설정된 파일 또는 디렉토리를 지정하는 널 (null)로 끝나는 문자열에 대한 포인터
* @param  SecurityInformation	SECURITY_INFORMATION 구조체
* @param  pSecurityDescriptor	SECURITY_DESCRIPTOR 구조체에 대한 포인터
* @return						성공/실패 여부
*/
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

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	CreateDirectory(pathName, NULL);

    // 해당 구조를 초기화 한다
    if(!InitializeSecurityDescriptor(SD, SECURITY_DESCRIPTOR_REVISION))
         return FALSE;

    // 빈 ACL 을 하나 생성한다.
    // SetEntriesInAcl 에 넣고, 지우고 해야하기 때문에 해당 구조에서
    // 맞도록 LocalAlloc 을 사용한다. SetEntriesInAcl 에서 생성하면
    // LocalFree 를 사용하도록 권고하므로, 거기에 맞춘다.
    PACL pACL = (PACL)LocalAlloc(LMEM_FIXED, sizeof(ACL));

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

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "SetFileSecurity 성공", msg);


    LocalFree(pACL);

	if(!RemoveDirectory(pathName)){
		#ifdef OQADBGPRINT
		printf("디렉토리 삭제 실패\n");
		#endif
		#ifdef OQADBG
		MessageBoxA(NULL, GetErrorMessage("폴더 삭제 실패 : ", GetLastError()), "test_SetFileSecurity", MB_OK);
		#endif
	}else{
		#ifdef OQADBGPRINT
		printf("디렉토리 삭제 성공 : ");
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
* 파일 또는 디렉터리의 보안에 대한 특정 정보를 얻는다. 획득된 정보는 호출자의 액세스 권한 및 특권에 의해 제한된다. 
더이상 사용되지 않음.
* @author : 손찬영  
*
* @param  lpFileName			보안 정보를 검색 할 파일 또는 디렉토리를 지정하는 널 (null)로 끝나는 문자열에 대한 포인터
* @param  RequestedInformation	요청되는 보안 정보를 식별 하는 SECURITY_INFORMATION 값
* @param  pSecurityDescriptor	lpFileName 매개 변수로 지정된 개체 의 보안 설명 자의 복사본을 받는 버퍼에 대한 포인터
* @param  nLength				pSecurityDescriptor 매개 변수가 가리키는 버퍼의 크기 (바이트)
* @param  lpnLengthNeeded		전체 보안 설명자를 저장하는 데 필요한 바이트 수를 받는 변수에 대한 포인터
* @return						성공/실패 여부
*/
BOOL test_GetFileSecurityW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;
	
	LPCWSTR pathName = L"손찬영\\test_GetFileAttributesW";
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

	/* 디렉토리를 생성 */
	if(CreateDirectoryW(pathName, NULL)){
		strcpy(msg, GetErrorMessage("CreateDirectoryW 실패 : ", GetLastError()));
		strcpy(buf, "CreateDirectoryW 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateDirectoryW 성공", msg);

		return FALSE;
	}

	/* 초기화 */
	psd = GlobalAlloc (GMEM_FIXED, 1000);
	AccountName = (wchar_t *)GlobalAlloc (GMEM_FIXED, 1000);
	DomainName = (wchar_t *)GlobalAlloc (GMEM_FIXED, 1000);

	AccountLen = DomainLen = 1000;

	/* 파일의 보안 정보 취득 */
	if(GetFileSecurityW(pathName, OWNER_SECURITY_INFORMATION, psd, 1000, & sdsize)){
		strcpy(msg, GetErrorMessage("GetFileSecurityW 실패 : ", GetLastError()));
		strcpy(buf, "GetFileSecurityW 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetFileSecurityW 성공", msg);

		return FALSE;
	}

	/* 소유자 SID 취득 */
	if(GetSecurityDescriptorOwner(psd, &psid, &OwnerDefaulted)){
		strcpy(msg, GetErrorMessage("GetSecurityDescriptorOwner 실패 : ", GetLastError()));
		strcpy(buf, "GetSecurityDescriptorOwner 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetSecurityDescriptorOwner 성공", msg);

		return FALSE;
	}

	/* SID를 이름으로 변환 */
	if(LookupAccountSidW(NULL, psid, AccountName, &AccountLen, DomainName, &DomainLen, &snu)){
		strcpy(msg, GetErrorMessage("LookupAccountSidW 실패 : ", GetLastError()));
		strcpy(buf, "LookupAccountSidW 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "LookupAccountSidW 성공", msg);

		return FALSE;
	}

	/* 표시 */
	#ifdef OQADBGPRINT
	wprintf(L"Owner Name : %s \n", AccountName);
	wprintf(L"Domain of Owner : %s \n", DomainName);
	#endif

	/* 현재 사용자 이름(관리자 권한으로 실행)과 소유자 이름이 동일하면 성공으로 판단한다. */
	if(!wcscmp(userName, AccountName)){ 
		sprintf(msg, "GetFileSecurity 성공 : 폴더 소유자 : %S\n로그인 사용자 : %S", AccountName, userName);
		strcpy(buf, "GetFileSecurity 성공");

	}else{
		sprintf(msg, GetErrorMessage("GetFileSecurity 실패 : ", GetLastError()));
		strcpy(buf, "GetFileSecurity 실패");
		result = FALSE;	
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetFileSecurity 성공", msg);

	/* 후 처리 */
	GlobalFree (psd);
	GlobalFree (AccountName);
	GlobalFree (DomainName);

	if(!RemoveDirectory(pathName)){
		#ifdef OQADBGPRINT
		printf("디렉토리 삭제 실패\n");
		#endif
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


/**
* DWORD WINAPI GetSecurityDescriptorLength(
  _In_ PSECURITY_DESCRIPTOR pSecurityDescriptor
);
* 구조적으로 유효한 보안 설명 자의 길이 (바이트)를 반환한다. 길이는 관련된 모든 구조의 길이를 포함한다.
* @author : 손찬영  
*
* @param  pSecurityDescriptor	함수가 리턴하는 길이의 SECURITY_DESCRIPTOR 구조체에 대한 포인터. 포인터는 유효하다고 가정
* @return						함수가 성공하면 함수는 SECURITY_DESCRIPTOR 구조체 의 길이 (바이트)를 반환
*/
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

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hFile = CreateFile(fileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	
	if(hFile == INVALID_HANDLE_VALUE){ //파일 열기 실패
		sprintf(msg, GetErrorMessage("파일 열기 실패 : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile 성공", msg);

		return FALSE;
	}


	if(GetSecurityInfo(hFile, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION, &pOwner, NULL, &pDacl, NULL, (LPVOID *)&pSD) != ERROR_SUCCESS){
		sprintf(msg, GetErrorMessage("GetSecurityInfo 실패 : ", GetLastError()));
		strcpy(buf, "GetSecurityInfo 실패");

		wresult(__FILE__, __LINE__ ,__FUNCTION__, buf, "GetSecurityInfo 성공", msg);

		return FALSE;
	}

	if(SDLengh = GetSecurityDescriptorLength(pSD)){
		sprintf(msg, "GetSecurityDescriptorLength 성공 : SDLengh = %d", SDLengh);
		strcpy(buf, "GetSecurityDescriptorLength 성공");

	}else{
		sprintf(msg, GetErrorMessage("GetSecurityDescriptorLength 실패 : ", GetLastError()));
		strcpy(buf, "GetSecurityDescriptorLength 실패");

		result = FALSE;
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetSecurityDescriptorLength 성공", msg);

	LocalFree(pSD);

	if(!CloseHandle(hFile)){
		#ifdef OQADBG
		MessageBoxA(NULL, GetErrorMessage("CloseHandle(hFile) 실패 : ", GetLastError()), "test_GetFileAttributesW", MB_OK);
		#endif
	}
	if(!DeleteFileW(fileName)){
		#ifdef OQADBG
		MessageBoxA(NULL, GetErrorMessage("파일 삭제 실패 : ", GetLastError()), "test_GetFileAttributesW", MB_OK);
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
* 지정된 보안 정보를 지정된 개체의 보안 설명 자로 설정한다. 호출자는 이름으로 객체를 식별한다.
* @author : 손찬영  
*
* @param  pObjectName	보안 정보를 설정할 오브젝트의 이름을 지정 하는 널 (null)로 끝나는 문자열에 대한 포인터
* @param  ObjectType	pObjectName 매개 변수로 명명 된 개체 유형을 나타내는 SE_OBJECT_TYPE 열거형의 값
* @param  SecurityInfo	설정할 보안 정보의 유형을 나타내는 비트 플래그 세트
* @param  psidOwner		개체의 소유자를 식별 하는 SID 구조체의 포인터
* @param  psidGroup		개체의 기본 그룹을 식별하는 SID에 대한 포인터
* @param  pDacl			개체에 대한 새 DACL에 대한 포인터
* @param  pSacl			개체에 대한 새 SACL에 대한 포인터
* @return				함수가 성공하면 함수는 ERROR_SUCCESS, 실패하면 에러 코드
*/
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

	 // 해당 구조를 초기화 한다
 //   if(!InitializeSecurityDescriptor(SD, SECURITY_DESCRIPTOR_REVISION))
 //        return FALSE;

 //   // 빈 ACL 을 하나 생성한다.
 //   // SetEntriesInAcl 에 넣고, 지우고 해야하기 때문에 해당 구조에서
 //   // 맞도록 LocalAlloc 을 사용한다. SetEntriesInAcl 에서 생성하면
 //   // LocalFree 를 사용하도록 권고하므로, 거기에 맞춘다.
 //   PACL pACL = (PACL)LocalAlloc(LMEM_FIXED, sizeof(ACL));

 //   // 그냥 기본 초기화
 //   if(!InitializeAcl(pACL, MAX_PATH, ACL_REVISION))
 //   {
 //       LocalFree(pACL);
 //       return FALSE;
 //   }

 //   // 권한을 줄 때 어떤것을 줄것인지 옵션을 지정한다.
 //   DWORD AccessOption = GENERIC_ALL | GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE;

 //   // 추가 하고픈 사용자와 권한을 적어준다. //Administrator 항목을 제외하고 추가한다.
 //   AddToACL(pACL, L"Everyone", AccessOption);
 //   //AddToACL(pACL, L"Administrator", AccessOption);
 //   AddToACL(pACL, L"SYSTEM", AccessOption);

	// // 보안 속성을 지정한 구조에, 생성한 ACL 정보를 설정해준다.
 //   if(!SetSecurityDescriptorDacl(SD, TRUE, pACL, TRUE))
 //   {
 //       LocalFree(pACL);
 //       return FALSE;
 //   }
	//pOwner = SD->Owner;
	//pACL = SD->Dacl;



	// 해당 파일이나, 폴더에 권한을 적용시킨다.
	if((ret = SetNamedSecurityInfoW(pathName, SE_FILE_OBJECT, ATTRIBUTE_SECURITY_INFORMATION, NULL, NULL, NULL, NULL)) == ERROR_SUCCESS){ //SetNamedSecurityInfoW 성공
		sprintf(msg, "SetNamedSecurityInfoW 성공");
		strcpy(buf, msg);

	}else{ //SetNamedSecurityInfoW 실패
		sprintf(msg, GetErrorMessage("SetNamedSecurityInfoW 실패 : ", ret));
		strcpy(buf, "SetNamedSecurityInfoW 실패");

		result = FALSE;
	}

	//나중에 Set하고 그 정보를 가져와서 진짜 set됐는지 확인할 예정


	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "SetNamedSecurityInfoW 성공", msg);


    //LocalFree(pDacl);
	//LocalFree(pOwner);

	if(!RemoveDirectory(pathName)){
		#ifdef OQADBGPRINT
		printf("디렉토리 삭제 실패\n");
		#endif
		#ifdef OQADBG
		MessageBoxA(NULL, GetErrorMessage("폴더 삭제 실패 : ", GetLastError()), "test_SetNamedSecurityInfoW", MB_OK);
		#endif
	}else{
		#ifdef OQADBGPRINT
		printf("디렉토리 삭제 성공 : ");
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
* name으로 지정된 개체에 대한 보안 설명 자의 복사본을 검색한다.
* @author : 손찬영  
*
* @param  pObjectName			보안 정보를 설정할 오브젝트의 이름을 지정 하는 널 (null)로 끝나는 문자열에 대한 포인터
* @param  ObjectType			pObjectName 매개 변수로 명명 된 개체 유형을 나타내는 SE_OBJECT_TYPE 열거형의 값
* @param  SecurityInfo			설정할 보안 정보의 유형을 나타내는 비트 플래그 세트
* @param  ppsidOwner			ppSecurityDescriptor 에서 반환된 보안 설명자의 소유자 SID에 대한 포인터를 받는 변수에 대한 포인터 
* @param  ppsidGroup			반환된 보안 설명자의 주 그룹 SID에 대한 포인터를 받는 변수에 대한 포인터
* @param  ppDacl				반환 된 보안 설명자에서 DACL에 대한 포인터를받는 변수에 대한 포인터
* @param  ppSacl				반환 된 보안 설명 자의 SACL에 대한 포인터를받는 변수에 대한 포인터
* @param  ppSecurityDescriptor	개체의 보안 설명자에 대한 포인터를 받는 변수에 대한 포인터
* @return						함수가 성공하면 함수는 ERROR_SUCCESS, 실패하면 에러 코드
*/
BOOL test_GetNamedSecurityInfoW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;

	LPWSTR pathName = L"손찬영\\test_GetNamedSecurityInfoW";

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

	/* 테스트를 관리자 모드로 실행하기 때문에 Administrators로 하드코딩 */
	//GetUserName(userName, &userNameSize);	
	wcscpy(userName, L"Administrators");

	/* 보안정보를 가져오기 위한 디렉토리를 생성한다. */
	CreateDirectory(pathName, NULL);

	//pSD = GlobalAlloc (GMEM_FIXED, 1000);
	AccountName = (wchar_t *)GlobalAlloc (GMEM_FIXED, AccountLen);
	DomainName = (wchar_t *)GlobalAlloc (GMEM_FIXED, DomainLen);



	/* 해당 파일이나, 폴더에 권한을 적용시킨다. */
	ret = GetNamedSecurityInfoW(pathName, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION, &pOwner, NULL, &pDacl, NULL, &pSD);
	if(ret == ERROR_SUCCESS){
		/* 소유자 SID 취득 */
		GetSecurityDescriptorOwner(pSD, &psid, &OwnerDefaulted);

		/* SID를 이름으로 변환 */
		LookupAccountSid(NULL, psid, AccountName, &AccountLen, DomainName, &DomainLen, &snu);

		#ifdef OQADBGPRINT
		printf("AccountName = %S\n", AccountName);
		#endif

		/* 현재 사용자 이름(관리자)과 생성한 디렉토리의 소유자 이름이 동일하면 성공 */
		if(!wcscmp(userName, AccountName)){ 
			sprintf(msg, "GetNamedSecurityInfoW 성공 : 폴더 소유자 : %S\n로그인 사용자 : %S", AccountName, userName);
			strcpy(buf, "GetNamedSecurityInfoW 성공");

		/* 함수는 성공했지만 두 이름이 서로 같지 않은 경우 */
		}else{ 
			sprintf(msg, "GetNamedSecurityInfoW 실패 : %S(소유자) != %S(사용자)", AccountName, userName);
			strcpy(buf, "GetNamedSecurityInfoW 실패");
			result = FALSE;	
		}

	/* 함수 실패 */
	}else{
		sprintf(msg, GetErrorMessage("GetNamedSecurityInfoW 실패 : ", ret));
		strcpy(buf, "GetNamedSecurityInfoW 실패");

		result = FALSE;
	}


	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetNamedSecurityInfoW 성공", msg);

	/* 자원 해제 */
	LocalFree(pSD);
    LocalFree(pDacl);
	LocalFree(pOwner);

	if(!RemoveDirectory(pathName)){
		#ifdef OQADBGPRINT
		printf("디렉토리 삭제 실패\n");
		#endif
	}


	return result;
}


/**
* BOOL ConvertSidToStringSid(
  _In_  PSID   Sid,
  _Out_ LPTSTR *StringSid
);
* 보안식별자(SID)를 표시, 저장, 전송하기 적합한 형식 문자열로 변환한다.
* @author : 손찬영  
*
* @param  Sid		변환 할 SID 구조체 포인터
* @param  StringSid	변환된 SID 문자열에 대한 포인터
* @return			성공/실패 여부
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

    // 주어진 유저의 이름을 토대로 필요한 SID 를 구한다.
	if(!LookupAccountName(NULL, AccountName, (PSID)sid, &sidlen, dn, &dnlen, &SNU)){
		sprintf(msg, GetErrorMessage("LookupAccountName 실패 : ", GetLastError()));
		strcpy(buf, "LookupAccountName 실패");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "LookupAccountName 성공", msg);

		return FALSE;
	}

	pSid = sid;
	result = ConvertSidToStringSidW(pSid, StringSid);
	if(result){
		if((!wcscmp(*StringSid, L"S-1-5-32-544"))){
			sprintf(msg, "ConvertSidToStringSidW 성공 : [%S]'s sid = %S", AccountName, *StringSid);
			strcpy(buf, "ConvertSidToStringSidW 성공");

		/* 함수는 성공했지만 administrators의 SID 가 S-1-5-32-544가 아님 */
		}else{
			sprintf(msg, "ConvertSidToStringSidW 실패 : StringSid = %S", *StringSid);
			strcpy(buf, "ConvertSidToStringSidW 실패");
			result = FALSE;	
		}
	}else{
		sprintf(msg, GetErrorMessage("ConvertSidToStringSidW 실패 : ", GetLastError()));
		strcpy(buf, "ConvertSidToStringSidW 실패");
		result = FALSE;	
	}

	isManual = FALSE;
	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "ConvertSidToStringSidW 성공", msg);

	//LocalFree(StringSid);

	return result;
}

/**
* BOOL WINAPI SetSecurityDescriptorGroup(
  _Inout_  PSECURITY_DESCRIPTOR pSecurityDescriptor,
  _In_opt_ PSID                 pGroup,
  _In_     BOOL                 bGroupDefaulted
);
* 주요 그룹 정보를 가지는 보안 디스크립터를 이미 존재하는 임의의 그룹정보를 가지는 보안디스크립터로 대체한다.
* @author : 손찬영  
*
* @param  pSecurityDescriptor	그룹을 설정 하는 SECURITY_DESCRIPTOR 구조체에 대한 포인터
* @param  pGroup				보안 설명자의 새 그룹에 대한 SID 구조체의 포인터
* @param  bGroupDefaulted		그룹 정보가 기본 메커니즘에서 파생되었는지 여부. 이 값이 TRUE 이면 기본 정보
* @return						성공/실패 여부
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
		sprintf(msg, GetErrorMessage("InitializeSecurityDescriptor 실패 : ", GetLastError()));
		strcpy(buf, "InitializeSecurityDescriptor 실패");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "InitializeSecurityDescriptor 성공", msg);

		return FALSE;
	}

	if(!IsValidSecurityDescriptor(&sd)){
		sprintf(msg, GetErrorMessage("IsValidSecurityDescriptor 실패 : ", GetLastError()));
		strcpy(buf, "IsValidSecurityDescriptor 실패");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "IsValidSecurityDescriptor 성공", msg);

		return FALSE;
	}

	
	/*if(!GetSecurityDescriptorGroup(&sd, &psid, &GroupDefault)){
		sprintf(msg, GetErrorMessage("GetSecurityDescriptorGroup 실패 : ", GetLastError()));
		strcpy(buf, "GetSecurityDescriptorGroup 실패");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetSecurityDescriptorGroup 성공", msg);

		return FALSE;
		
	}*/
	result = SetSecurityDescriptorGroup(&sd, psid, FALSE);

	if(result){
		sprintf(msg, "SetSecurityDescriptorGroup 성공");
		strcpy(buf, "SetSecurityDescriptorGroup 성공");

	}else{
		sprintf(msg, GetErrorMessage("SetSecurityDescriptorGroup 실패 : ", GetLastError()));
		strcpy(buf, "SetSecurityDescriptorGroup 실패");

		result = FALSE;
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "SetSecurityDescriptorGroup 성공", msg);


	return result;
}

/**
* BOOL WINAPI SetSecurityDescriptorOwner(
  _Inout_  PSECURITY_DESCRIPTOR pSecurityDescriptor,
  _In_opt_ PSID                 pOwner,
  _In_     BOOL                 bOwnerDefaulted
);
* 주요 소유자 정보를 가지는 보안 디스크립터를 이미 존재하는 임의의 소유자정보를 가지는 보안디스크립터로 대체한다.
* @author : 손찬영  
*
* @param  pSecurityDescriptor	그룹을 설정 하는 SECURITY_DESCRIPTOR 구조체에 대한 포인터
* @param  pGroup				보안 설명자의 새 그룹에 대한 SID 구조체의 포인터
* @param  bOwnerDefaulted		소유자 정보가 기본 메커니즘에서 파생되었는지 여부. 이 값이 TRUE 이면 기본 정보
* @return						성공/실패 여부
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
		sprintf(msg, GetErrorMessage("InitializeSecurityDescriptor 실패 : ", GetLastError()));
		strcpy(buf, "InitializeSecurityDescriptor 실패");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "InitializeSecurityDescriptor 성공", msg);

		return FALSE;
	}

	if(!IsValidSecurityDescriptor(&sd)){
		sprintf(msg, GetErrorMessage("IsValidSecurityDescriptor 실패 : ", GetLastError()));
		strcpy(buf, "IsValidSecurityDescriptor 실패");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "IsValidSecurityDescriptor 성공", msg);

		return FALSE;
	}

	
	/*if(!GetSecurityDescriptorOwner(&sd, &psid, &OwnerDefault)){
		sprintf(msg, GetErrorMessage("GetSecurityDescriptorOwner 실패 : ", GetLastError()));
		strcpy(buf, "GetSecurityDescriptorOwner 실패");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "GetSecurityDescriptorOwner 성공", msg);

		return FALSE;
		
	}*/
	result = SetSecurityDescriptorOwner(&sd, psid, FALSE);

	if(result){
		sprintf(msg, "SetSecurityDescriptorOwner 성공");
		strcpy(buf, "SetSecurityDescriptorOwner 성공");

	}else{
		sprintf(msg, GetErrorMessage("SetSecurityDescriptorOwner 실패 : ", GetLastError()));
		strcpy(buf, "SetSecurityDescriptorOwner 실패");

		result = FALSE;
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "SetSecurityDescriptorOwner 성공", msg);


	return result;
}