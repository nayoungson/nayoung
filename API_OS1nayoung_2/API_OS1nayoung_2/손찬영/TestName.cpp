#include "TestName.h"


/**
* BOOL WINAPI SetComputerName(
  _In_ LPCTSTR lpComputerName
);
* 로컬 컴퓨터에 대한 새 NetBIOS 이름을 설정한다. 이름은 레지스트리에 저장되며 이름 변경은 다음에 사용자가 컴퓨터를 다시 시작할 때 적용된다.
* @author : 손찬영  
*
* @param  lpComputerName	다음에 컴퓨터를 시작할 때 적용되는 컴퓨터 이름
* @return					성공/실패 여부
*/
BOOL test_SetComputerNameW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	wchar_t oldComputerName[MAX_COMPUTERNAME_LENGTH]= {0, };
	wchar_t expectComputerName[MAX_COMPUTERNAME_LENGTH] = {0, };
	wchar_t newComputerName[MAX_COMPUTERNAME_LENGTH] = {0, };
	DWORD nSize = MAX_COMPUTERNAME_LENGTH;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* 변경하고자 하는 컴퓨터 이름 */
	wcscpy(expectComputerName, L"OQATEST");
	printf("expectComputerName = %S\n", expectComputerName);


	/* 함수 종료 전 컴퓨터이름 원상복귀를 위해 저장 */
	/* 실제로 GetComputerName은 ipconfig /all의 HOST이름을 가져온다(재부팅 후에 레지스트리에 있는 값으로 변경됨) */
	if(!GetComputerNameW(oldComputerName, &nSize)){
		strcpy(msg, GetErrorMessage("GetComputerName 실패 : ", GetLastError()));
		strcpy(buf, "GetComputerName 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetComputerName 성공", msg);

		return FALSE;
	}

	if(result = SetComputerNameW(expectComputerName)){

		/* 바꾸기 시도한 값과 레지스트리 값이 동일하면 성공으로 판단 */
		if(!GetRegLocalMachineValueW(L"SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName", L"ComputerName", newComputerName)){
			return FALSE;
		}
		printf("newComputerName = %S\n", newComputerName);
		if(!wcscmp(newComputerName, expectComputerName)){
			sprintf(msg, "SetComputerNameW 성공 : (expectComputerName = %S) = (NewName = %S)", expectComputerName, newComputerName);
			strcpy(buf, "SetComputerNameW 성공");

		/* set함수는 성공했지만 실제 값이 변경되지는 않음 */
		}else{
			sprintf(msg, "SetComputerNameW 실패 : (expectComputerName = %S) != (NewName = %S)", expectComputerName, newComputerName);
			strcpy(buf, "SetComputerNameW 실패");

			result = FALSE;
		}

	}else{
		strcpy(msg, GetErrorMessage("SetComputerNameW 실패 : ", GetLastError()));
		strcpy(buf, "SetComputerNameW 실패");
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetComputerNameW 성공", msg);


	/* 기존의 컴퓨터 이름으로 원상복귀 함 */
	printf("oldComputerName = %S\n", oldComputerName);
	if(!SetComputerNameW(oldComputerName)){
		#ifdef OQADBGPRINT
		printf("기존 이름으로 복원되지 않았음. 재부팅 시 이름이 변경됨.\n");
		#endif
	}

	return result;
}


/**
* BOOL WINAPI SetComputerName(
  _In_ LPCTSTR lpComputerName
);
* 로컬 컴퓨터에 대한 새 NetBIOS 이름을 설정한다. 이름은 레지스트리에 저장되며 이름 변경은 다음에 사용자가 컴퓨터를 다시 시작할 때 적용된다.
* @author : 손찬영  
*
* @param  lpComputerName	다음에 컴퓨터를 시작할 때 적용되는 컴퓨터 이름
* @return					성공/실패 여부
*/
BOOL test_SetComputerNameA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	char oldComputerName[MAX_COMPUTERNAME_LENGTH]= {0, };
	char expectComputerName[MAX_COMPUTERNAME_LENGTH] = {0, };
	char newComputerName[MAX_COMPUTERNAME_LENGTH] = {0, };
	DWORD nSize = MAX_COMPUTERNAME_LENGTH;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* 변경하고자 하는 컴퓨터 이름 */
	strcpy(expectComputerName, "OQATEST");
	printf("expectComputerName = %s\n", expectComputerName);


	/* 함수 종료 전 컴퓨터이름 원상복귀를 위해 저장 */
	/* 실제로 GetComputerName은 ipconfig /all의 HOST이름을 가져온다(재부팅 후에 레지스트리에 있는 값으로 변경됨) */
	if(!GetComputerNameA(oldComputerName, &nSize)){
		strcpy(msg, GetErrorMessage("GetComputerName 실패 : ", GetLastError()));
		strcpy(buf, "GetComputerName 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetComputerName 성공", msg);

		return FALSE;
	}

	if(result = SetComputerNameA(expectComputerName)){

		/* 바꾸기 시도한 값과 레지스트리 값이 동일하면 성공으로 판단 */
		if(!GetRegLocalMachineValueA("SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName", "ComputerName", newComputerName)){
			return FALSE;
		}
		printf("newComputerName = %S\n", newComputerName);
		if(!strcmp(newComputerName, expectComputerName)){
			sprintf(msg, "SetComputerNameA 성공 : (expectComputerName = %s) = (NewName = %s)", expectComputerName, newComputerName);
			strcpy(buf, "SetComputerNameA 성공");

		/* set함수는 성공했지만 실제 값이 변경되지는 않음 */
		}else{
			sprintf(msg, "SetComputerNameA 실패 : (expectComputerName = %s) != (NewName = %s)", expectComputerName, newComputerName);
			strcpy(buf, "SetComputerNameA 실패");

			result = FALSE;
		}

	}else{
		strcpy(msg, GetErrorMessage("SetComputerNameA 실패 : ", GetLastError()));
		strcpy(buf, "SetComputerNameA 실패");
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetComputerNameA 성공", msg);


	/* 기존의 컴퓨터 이름으로 원상복귀 함 */
	if(!SetComputerNameA(oldComputerName)){
		#ifdef OQADBGPRINT
		printf("기존 이름으로 복원되지 않았음. 재부팅 시 이름이 변경됨.\n");
		#endif
	}

	return result;
}



/**
* BOOL WINAPI SetComputerNameEx(
  _In_ COMPUTER_NAME_FORMAT NameType,
  _In_ LPCTSTR              lpBuffer
);
* 로컬 컴퓨터에 대한 새 NetBIOS 또는 DNS 이름을 설정한다.
* @author : 손찬영  
*
* @param  NameType	설정할 이름의 유형.ComputerNamePhysicalDnsDomain 등.
* @param  lpBuffer	새로운 이름.
* @return			성공/실패 여부
*/
BOOL test_SetComputerNameExW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	wchar_t oldComputerName[MAX_COMPUTERNAME_LENGTH]= {0, };
	wchar_t expectComputerName[MAX_COMPUTERNAME_LENGTH] = {0, };
	wchar_t newComputerName[MAX_COMPUTERNAME_LENGTH] = {0, };
	DWORD nSize = MAX_COMPUTERNAME_LENGTH;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* 변경하고자 하는 컴퓨터 이름 */
	wcscpy(expectComputerName, L"OQATEST");
	printf("expectComputerName = %S\n", expectComputerName);


	/* 함수 종료 전 컴퓨터이름 원상복귀를 위해 저장 */
	/* 실제로 GetComputerName은 ipconfig /all의 HOST이름을 가져온다(재부팅 후에 레지스트리에 있는 값으로 변경됨) */
	if(!GetComputerNameExW(ComputerNamePhysicalDnsHostname, oldComputerName, &nSize)){
		strcpy(msg, GetErrorMessage("GetComputerNameEx 실패 : ", GetLastError()));
		strcpy(buf, "GetComputerNameEx 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetComputerNameEx 성공", msg);

		return FALSE;
	}

	if(result = SetComputerNameExW(ComputerNamePhysicalDnsHostname, expectComputerName)){

		/* 바꾸기 시도한 값과 레지스트리 값이 동일하면 성공으로 판단 */
		if(!GetRegLocalMachineValueW(L"SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName", L"ComputerName", newComputerName)){
			return FALSE;
		}
		printf("newComputerName = %S\n", newComputerName);
		if(!wcscmp(newComputerName, expectComputerName)){
			sprintf(msg, "SetComputerNameExW 성공 : (expectComputerName = %S) = (NewName = %S)", expectComputerName, newComputerName);
			strcpy(buf, "SetComputerNameExW 성공");

		/* set함수는 성공했지만 실제 값이 변경되지는 않음 */
		}else{
			sprintf(msg, "SetComputerNameExW 실패 : (expectComputerName = %S) != (NewName = %S)", expectComputerName, newComputerName);
			strcpy(buf, "SetComputerNameExW 실패");

			result = FALSE;
		}

	}else{
		strcpy(msg, GetErrorMessage("SetComputerNameExW 실패 : ", GetLastError()));
		strcpy(buf, "SetComputerNameExW 실패");
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetComputerNameW 성공", msg);


	/* 기존의 컴퓨터 이름으로 원상복귀 함 */
	printf("oldComputerName = %S\n", oldComputerName);
	if(!SetComputerNameExW(ComputerNamePhysicalDnsHostname, oldComputerName)){
		#ifdef OQADBGPRINT
		printf("기존 이름으로 복원되지 않았음. 재부팅 시 이름이 변경됨.\n");
		#endif
	}

	return result;
}

/**
* BOOL WINAPI SetComputerNameEx(
  _In_ COMPUTER_NAME_FORMAT NameType,
  _In_ LPCTSTR              lpBuffer
);
* 로컬 컴퓨터에 대한 새 NetBIOS 또는 DNS 이름을 설정한다.
* @author : 손찬영  
*
* @param  NameType	설정할 이름의 유형.ComputerNamePhysicalDnsDomain 등.
* @param  lpBuffer	새로운 이름.
* @return			성공/실패 여부
*/
BOOL test_SetComputerNameExA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	char oldComputerName[MAX_COMPUTERNAME_LENGTH]= {0, };
	char expectComputerName[MAX_COMPUTERNAME_LENGTH] = {0, };
	char newComputerName[MAX_COMPUTERNAME_LENGTH] = {0, };
	DWORD nSize = MAX_COMPUTERNAME_LENGTH;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* 변경하고자 하는 컴퓨터 이름 */
	strcpy(expectComputerName, "OQATEST");
	printf("expectComputerName = %S\n", expectComputerName);


	/* 함수 종료 전 컴퓨터이름 원상복귀를 위해 저장 */
	/* 실제로 GetComputerName은 ipconfig /all의 HOST이름을 가져온다(재부팅 후에 레지스트리에 있는 값으로 변경됨) */
	if(!GetComputerNameExA(ComputerNamePhysicalDnsHostname, oldComputerName, &nSize)){
		strcpy(msg, GetErrorMessage("GetComputerNameEx 실패 : ", GetLastError()));
		strcpy(buf, "GetComputerNameEx 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetComputerNameEx 성공", msg);

		return FALSE;
	}
	printf("oldComputerName = %s\n", oldComputerName);
	printf("SetComputerNameExA직전.. expectComputerName = %S\n", expectComputerName); //정상..

	if(result = SetComputerNameExA(ComputerNamePhysicalDnsHostname, (LPTSTR)expectComputerName)){

		/* 바꾸기 시도한 값과 레지스트리 값이 동일하면 성공으로 판단 */
		if(!GetRegLocalMachineValueA("SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName", "ComputerName", newComputerName)){
			return FALSE;
		}
		printf("newComputerName = %s\n", newComputerName);
		if(!strcmp(newComputerName, expectComputerName)){
			sprintf(msg, "SetComputerNameExA 성공 : (expectComputerName = %s) = (NewName = %s)", expectComputerName, newComputerName);
			strcpy(buf, "SetComputerNameExA 성공");

		/* set함수는 성공했지만 실제 값이 변경되지는 않음 */
		}else{
			sprintf(msg, "SetComputerNameExA 실패 : (expectComputerName = %s) != (NewName = %s)", expectComputerName, newComputerName);
			strcpy(buf, "SetComputerNameExA 실패");

			result = FALSE;
		}

	}else{
		strcpy(msg, GetErrorMessage("SetComputerNameExA 실패 : ", GetLastError()));
		strcpy(buf, "SetComputerNameExA 실패");
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetComputerNameExA 성공", msg);


	/* 기존의 컴퓨터 이름으로 원상복귀 함 */
	printf("oldComputerName = %s\n", oldComputerName);
	if(!SetComputerNameExA(ComputerNamePhysicalDnsHostname, (LPTSTR)oldComputerName)){
		#ifdef OQADBGPRINT
		printf("기존 이름으로 복원되지 않았음. 재부팅 시 이름이 변경됨.\n");
		#endif
	}

	return result;
}


/**
* int ResolveLocaleName(
  _In_opt_  LPCWSTR lpNameToResolve,
  _Out_opt_ LPWSTR  lpLocaleName,
  _In_      int     cchLocaleName
);
* 제공된 이름에 사용할 수있는 로케일 이름을 찾는다.
* @author : 손찬영  
*
* @param  lpNameToResolve	해결할 이름을 가리키는 포인터
* @param  lpLocaleName		이 함수가 입력 이름과 일치하는 로케일 이름을 검색하는 버퍼의 포인터
* @param  cchLocaleName		lpLocaleName으로 표시된 버퍼의 크기 (문자) 
* @return					성공했을 경우, 종료 null 캐릭터를 포함한, 로케일 명을 포함한 버퍼의 사이즈, 실패 시 0
*/
BOOL test_ResolveLocaleName()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCWSTR lpNameToResolve = L"ko"; //로케일 변환을 위한 적당한 값을 집어넣음
	LPCWSTR expectName = L"ko-KR";
	wchar_t lpLocaleName[LOCALE_NAME_MAX_LENGTH];
	int     cchLocaleName = LOCALE_NAME_MAX_LENGTH, ret = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	ret = ResolveLocaleName(lpNameToResolve, lpLocaleName, cchLocaleName);

	/* lpNameToResolve의 "ko" 가 "ko-kr"로 변환되면 성공 */
	if(ret > 0){
		if(!wcscmp(expectName, lpLocaleName)){
			sprintf(msg, "ResolveLocaleName 성공 : localeName = %S", lpLocaleName);
			strcpy(buf, "ResolveLocaleName 성공");	


		/* 함수는 성공했지만 변환은 실패함 */
		}else{
			sprintf(msg, "ResolveLocaleName 실패 : expectName = %S, result = %S", expectName, lpLocaleName);
			strcpy(buf, "ResolveLocaleName 실패");

			result = FALSE;	
		}

	/* 함수 실패 */
	}else{
		strcpy(msg, GetErrorMessage("ResolveLocaleName 실패 : ", GetLastError()));
		strcpy(buf, "ResolveLocaleName 실패");
		
		result = FALSE;	

	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ResolveLocaleName 성공", msg);

	return result;
}


/**
* int GetUserDefaultLocaleName(
  _Out_ LPWSTR lpLocaleName,
  _In_  int    cchLocaleName
);
* 사용자의 기본 로케일 이름을 검색한다. 
* @author : 손찬영  
*
* @param  lpLocaleName		로케일 이름을 검색하는 버퍼의 포인터
* @param  cchLocaleName		lpLocaleName으로 표시된 버퍼의 크기 (문자)
* @return					성공했을 경우, 종료 null 캐릭터를 포함한, 로케일 명을 포함한 버퍼의 사이즈, 실패 시 0
*/
BOOL test_GetUserDefaultLocaleName()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	wchar_t lpLocaleName[LOCALE_NAME_MAX_LENGTH] = {0, };
	const wchar_t *expectName = L"ko-KR";
	int    cchLocaleName = LOCALE_NAME_MAX_LENGTH, ret = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	ret = GetUserDefaultLocaleName(lpLocaleName, cchLocaleName);

	/* 한국 ko-KR값을 받아오는 것을 확인한다 */
	if(ret > 0){
		if(!wcscmp(expectName, lpLocaleName)){
			sprintf(msg, "GetUserDefaultLocaleName 성공 : lpLocaleName = %S", lpLocaleName);
			strcpy(buf, "GetUserDefaultLocaleName 성공");
		
		/* 가져온 값이 ko-KR이 아님 */
		}else{
			sprintf(msg, "GetUserDefaultLocaleName 실패 : expectName = %S, result = %S", expectName, lpLocaleName);
			strcpy(buf, "GetUserDefaultLocaleName 실패");

			result = FALSE;	
		}

	/* GetUserDefaultLocaleName 함수가 실패 */
	}else{
		strcpy(msg, GetErrorMessage("GetUserDefaultLocaleName 실패 : ", GetLastError()));
		strcpy(buf, "GetUserDefaultLocaleName 실패");
		
		result = FALSE;	

	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetUserDefaultLocaleName 성공", msg);


	return result;
}

/**
* int GetSystemDefaultLocaleName(
  _Out_ LPWSTR lpLocaleName,
  _In_  int    cchLocaleName
);
* 시스템의 디폴트 로케일 명을 가져온다.
* @author : 손찬영  
*
* @param  lpLocaleName		로케일 이름을 검색하는 버퍼의 포인터
* @param  cchLocaleName		lpLocaleName으로 표시된 버퍼의 크기 (문자)
* @return					성공했을 경우, 종료 null 캐릭터를 포함한, 로케일 명을 포함한 버퍼의 사이즈, 실패 시 0
*/
BOOL test_GetSystemDefaultLocaleName()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	wchar_t lpLocaleName[LOCALE_NAME_MAX_LENGTH] = {0, };
	const wchar_t *expectName = L"ko-KR";
	int    cchLocaleName = LOCALE_NAME_MAX_LENGTH, ret = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	ret = GetSystemDefaultLocaleName(lpLocaleName, cchLocaleName);

	/* 한국 ko-KR값을 받아오는 것을 확인한다 */
	if(ret > 0){
		if(!wcscmp(expectName, lpLocaleName)){
			sprintf(msg, "GetSystemDefaultLocaleName 성공 : lpLocaleName = %S", lpLocaleName);
			strcpy(buf, "GetSystemDefaultLocaleName 성공");
		
		/* 가져온 값이 ko-KR이 아님 */
		}else{
			sprintf(msg, "GetSystemDefaultLocaleName 실패 : expectName = %S, result = %S", expectName, lpLocaleName);
			strcpy(buf, "GetSystemDefaultLocaleName 실패");

			result = FALSE;	
		}

	/* GetUserDefaultLocaleName 함수가 실패 */
	}else{
		strcpy(msg, GetErrorMessage("GetSystemDefaultLocaleName 실패 : ", GetLastError()));
		strcpy(buf, "GetSystemDefaultLocaleName 실패");
		
		result = FALSE;	

	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetSystemDefaultLocaleName 성공", msg);


	return result;
}

/**
* BOOL WINAPI DnsHostnameToComputerName(
  _In_    LPCTSTR Hostname,
  _Out_   LPTSTR  ComputerName,
  _Inout_ LPDWORD nSize
);
* DNS 스타일 호스트 이름을 NetBIOS 스타일 컴퓨터 이름으로 변환한다.
* @author : 손찬영  
*
* @param  Hostname		DNS 이름. DNS 이름이 유효한 변환 가능한 이름이 아니면 함수가 실패한다.
* @param  ComputerName	컴퓨터 이름을받는 버퍼에 대한 포인터
* @param  nSize			입력시 버퍼의 크기를 TCHAR로 지정, 출력시, 종결 널 문자를 제외하고 대상 버퍼에 복사된 TCHAR의 수를 수신
* @return				성공/실패 여부
*/
BOOL test_DnsHostnameToComputerNameW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	wchar_t Hostname[32] = L"oqa_test_123", ComputerName[32] = {0, };
	DWORD nSize=32;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif
	
	result = DnsHostnameToComputerNameW(Hostname, ComputerName, &nSize);
 
	if(result){
		/* Hostname 대문자 변환 값 = ComputerName이면 성공 */
		if(!wcscmp(wcsupr(Hostname), ComputerName)){
			sprintf(msg, "DnsHostnameToComputerNameW 성공 : ComputerName = %S", ComputerName);
			strcpy(buf, "DnsHostnameToComputerNameW 성공");
		
		}else{
			sprintf(msg, "DnsHostnameToComputerNameW 실패 : ComputerName = %S, wcsupr(Hostname) = %S", ComputerName, wcsupr(Hostname));
			strcpy(buf, "DnsHostnameToComputerNameW 실패");

			result = FALSE;
		}

	}else{
		strcpy(msg, GetErrorMessage("DnsHostnameToComputerNameW 실패 : ", GetLastError()));
		strcpy(buf, "DnsHostnameToComputerNameW 실패");
		
		result = FALSE;
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "DnsHostnameToComputerNameW 성공", msg);

	return result;
}

/**
* BOOL WINAPI DnsHostnameToComputerName(
  _In_    LPCTSTR Hostname,
  _Out_   LPTSTR  ComputerName,
  _Inout_ LPDWORD nSize
);
* DNS 스타일 호스트 이름을 NetBIOS 스타일 컴퓨터 이름으로 변환한다.
* @author : 손찬영  
*
* @param  Hostname		DNS 이름. DNS 이름이 유효한 변환 가능한 이름이 아니면 함수가 실패한다.
* @param  ComputerName	컴퓨터 이름을받는 버퍼에 대한 포인터
* @param  nSize			입력시 버퍼의 크기를 TCHAR로 지정, 출력시, 종결 널 문자를 제외하고 대상 버퍼에 복사된 TCHAR의 수를 수신
* @return				성공/실패 여부
*/
BOOL test_DnsHostnameToComputerNameA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	char Hostname[32] = "oqa_test_123", ComputerName[32] = {0, };
	DWORD nSize=32;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif
	
	result = DnsHostnameToComputerNameA(Hostname, ComputerName, &nSize);
 
	if(result){
		/* Hostname 대문자 변환 값 = ComputerName이면 성공 */
		if(!strcmp(strupr(Hostname), ComputerName)){
			sprintf(msg, "DnsHostnameToComputerNameA 성공 : ComputerName = %s", ComputerName);
			strcpy(buf, "DnsHostnameToComputerNameA 성공");
		
		}else{
			sprintf(msg, "DnsHostnameToComputerNameA 실패 : ComputerName = %s, strupr(Hostname) = %s", ComputerName, strupr(Hostname));
			strcpy(buf, "DnsHostnameToComputerNameA 실패");

			result = FALSE;
		}

	}else{
		strcpy(msg, GetErrorMessage("DnsHostnameToComputerNameA 실패 : ", GetLastError()));
		strcpy(buf, "DnsHostnameToComputerNameA 실패");
		
		result = FALSE;
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "DnsHostnameToComputerNameA 성공", msg);

	return result;
}


/**
* DWORD WINAPI GetLongPathNameTransacted(
  _In_  LPCTSTR lpszShortPath,
  _Out_ LPTSTR  lpszLongPath,
  _In_  DWORD   cchBuffer,
  _In_  HANDLE  hTransaction
);
* 지정된 경로를 트랜잭션 된 연산으로 긴 형식으로 변환한다. 권장하지 않음.
* @author : 손찬영  
*
* @param  lpszShortPath		변환 할 경로
* @param  lpszLongPath		긴 경로를 수신 할 버퍼에 대한 포인터
* @param  cchBuffer			lpszLongPath가 가리키는 버퍼의 크기
* @param  hTransaction		트랜잭션 핸들
* @return					성공/실패 여부
*/
BOOL test_GetLongPathNameTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCWSTR lpszShortPath = L"손찬영\\test_GetLongPathNameTransactedW.txt";
	wchar_t LongPath[128] = L"";

	DWORD   cchBuffer = 128;
	HANDLE  hTransaction = NULL, hFile;
	DWORD	ret = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hFile = MyCreateFile(lpszShortPath))){

		return FALSE;
	}
	CloseHandle(hFile);

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}
	GetLongPathNameTransactedW(lpszShortPath, LongPath, cchBuffer, hTransaction);
	ret = GetLongPathNameTransactedW(lpszShortPath, LongPath, cchBuffer, hTransaction);

	if(0 != ret){
		sprintf(msg, "GetLongPathNameTransactedW 성공 : LongPath = %S", LongPath);
		strcpy(buf, "GetLongPathNameTransactedW 성공");

	}else{
		strcpy(msg, GetErrorMessage("GetLongPathNameTransactedW 실패 : ", GetLastError()));
		strcpy(buf, "GetLongPathNameTransactedW 실패");
		
		result = FALSE;
		
		
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetLongPathNameTransactedW 성공", msg);

	CloseHandle(hTransaction);
	DeleteFile(lpszShortPath);

	return result;
}

/**
* DWORD WINAPI GetLongPathNameTransacted(
  _In_  LPCTSTR lpszShortPath,
  _Out_ LPTSTR  lpszLongPath,
  _In_  DWORD   cchBuffer,
  _In_  HANDLE  hTransaction
);
* 지정된 경로를 트랜잭션 된 연산으로 긴 형식으로 변환한다. 권장하지 않음.
* @author : 손찬영  
*
* @param  lpszShortPath		변환 할 경로
* @param  lpszLongPath		긴 경로를 수신 할 버퍼에 대한 포인터
* @param  cchBuffer			lpszLongPath가 가리키는 버퍼의 크기
* @param  hTransaction		트랜잭션 핸들
* @return					성공 시 반환 값은 종료 null 문자 를 제외 하고 lpszLongPath에 복사 된 문자열의 길이, 실패 시 0
*/
BOOL test_GetLongPathNameTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCSTR	lpszShortPath = "손찬영\\test_GetLongPathNameTransactedA.txt";
	char	LongPath[64] = "";
	DWORD   cchBuffer = 64;
	HANDLE  hTransaction = NULL, hFile = NULL;
	DWORD	ret = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hFile = MyCreateFileA(lpszShortPath))){

		return FALSE;
	}
	CloseHandle(hFile);

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	GetLongPathNameTransactedA(lpszShortPath, LongPath, cchBuffer, hTransaction);
	ret = GetLongPathNameTransactedA(lpszShortPath, LongPath, cchBuffer, hTransaction);

	if(0 != ret){
		sprintf(msg, "GetLongPathNameTransactedA 성공 : LongPath = %s", LongPath);
		strcpy(buf, "GetLongPathNameTransactedA 성공");

	}else{
		strcpy(msg, GetErrorMessage("GetLongPathNameTransactedA 실패 : ", GetLastError()));
		strcpy(buf, "GetLongPathNameTransactedA 실패");
		
		result = FALSE;
		
		
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetLongPathNameTransactedA 성공", msg);

	CloseHandle(hTransaction);

	DeleteFileA(lpszShortPath);

	return result;
}


/**
* DWORD WINAPI GetFullPathNameTransacted(
  _In_  LPCTSTR lpFileName,
  _In_  DWORD   nBufferLength,
  _Out_ LPTSTR  lpBuffer,
  _Out_ LPTSTR  *lpFilePart,
  _In_  HANDLE  hTransaction
);
* 지정된 파일의 전체 경로와 파일 이름을 트랜잭션 연산으로 검색한다. 권장하지 않음.
* @author : 손찬영  
*
* @param  lpFileName		파일의 이름
* @param  nBufferLength		드라이브 및 경로에 대한 널 (null) 종료 문자열을 수신 할 버퍼의 크기
* @param  lpBuffer			드라이브 및 경로에 대해 널 종료 문자열을 수신하는 버퍼에 대한 포인터
* @param  lpFilePart		경로의 최종 파일 이름 구성 요소 의 주소 ( lpBuffer ) 를 수신하는 버퍼에 대한 포인터
* @param  hTransaction		트랜잭션 핸들
* @return					공하면 반환 값은 종료 널 문자를 제외하고 lpBuffer에 복사 된 문자열의 길이, 실패 시 0
*/
BOOL test_GetFullPathNameTransactedW()
{

	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode = 0;

	LPCTSTR lpFileName = L"손찬영\\test_GetFullPathNameTransactedW.txt";
	DWORD   nBufferLength = MAX_PATH;
	wchar_t  lpBuffer[MAX_PATH];
	HANDLE  hTransaction, hFile;
	DWORD	ret = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hFile = MyCreateFile(lpFileName))){

		return FALSE;
	}
	CloseHandle(hFile);

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	ret = GetFullPathNameTransactedW(lpFileName, nBufferLength, lpBuffer, NULL, hTransaction);

	printf("ret = %d\n", ret);
	if(0 != ret){
		sprintf(msg, "GetFullPathNameTransactedW 성공 : Buffer = %S", lpBuffer);
		strcpy(buf, "GetFullPathNameTransactedW 성공");

	}else{
		strcpy(msg, GetErrorMessage("GetFullPathNameTransactedW 실패 : ", GetLastError()));
		strcpy(buf, "GetFullPathNameTransactedW 실패");
		
		result = FALSE;
		
		
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetFullPathNameTransactedW 성공", msg);

	CloseHandle(hTransaction);
	DeleteFile(lpFileName);

	return result;
}

/**
* DWORD WINAPI GetFullPathNameTransacted(
  _In_  LPCTSTR lpFileName,
  _In_  DWORD   nBufferLength,
  _Out_ LPTSTR  lpBuffer,
  _Out_ LPTSTR  *lpFilePart,
  _In_  HANDLE  hTransaction
);
* 지정된 파일의 전체 경로와 파일 이름을 트랜잭션 연산으로 검색한다. 권장하지 않음.
* @author : 손찬영  
*
* @param  lpFileName		파일의 이름
* @param  nBufferLength		드라이브 및 경로에 대한 널 (null) 종료 문자열을 수신 할 버퍼의 크기
* @param  lpBuffer			드라이브 및 경로에 대해 널 종료 문자열을 수신하는 버퍼에 대한 포인터
* @param  lpFilePart		경로의 최종 파일 이름 구성 요소 의 주소 ( lpBuffer ) 를 수신하는 버퍼에 대한 포인터
* @param  hTransaction		트랜잭션 핸들
* @return					공하면 반환 값은 종료 널 문자를 제외하고 lpBuffer에 복사 된 문자열의 길이, 실패 시 0
*/
BOOL test_GetFullPathNameTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode = 0;

	LPCSTR lpFileName = "손찬영\\test_GetFullPathNameTransactedA.txt";
	DWORD   nBufferLength = MAX_PATH;
	char  lpBuffer[MAX_PATH];
	HANDLE  hTransaction, hFile;
	DWORD	ret = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(hFile = MyCreateFileA(lpFileName))){

		return FALSE;
	}
	CloseHandle(hFile);

	if(!(hTransaction = MyCreateTransaction())){

		return FALSE;
	}

	ret = GetFullPathNameTransactedA(lpFileName, nBufferLength, lpBuffer, NULL, hTransaction);

	printf("ret = %d\n", ret);
	if(0 != ret){
		sprintf(msg, "GetFullPathNameTransactedA 성공 : Buffer = %s", lpBuffer);
		strcpy(buf, "GetFullPathNameTransactedA 성공");

	}else{
		strcpy(msg, GetErrorMessage("GetFullPathNameTransactedA 실패 : ", GetLastError()));
		strcpy(buf, "GetFullPathNameTransactedA 실패");
		
		result = FALSE;
		
		
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetFullPathNameTransactedA 성공", msg);

	CloseHandle(hTransaction);
	DeleteFileA(lpFileName);

	return result;
}


BOOL GetRegLocalMachineValueW(wchar_t *path, wchar_t *valueName, wchar_t *value)
{
	HKEY hKey;
	wchar_t szDeaultPath[_MAX_PATH] = {0, };
	DWORD dwBufLen = MAX_PATH;
	char msg[BUFSIZ], buf[BUFSIZ];

	if(RegOpenKeyExW(HKEY_LOCAL_MACHINE, path, 0, KEY_READ, &hKey)){
		strcpy(msg, GetErrorMessage("RegOpenKeyExW 실패 : ", GetLastError()));
		strcpy(buf, "RegOpenKeyExW 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "RegOpenKeyExW 성공", msg);

		return FALSE;
	}

	if(RegQueryValueExW(hKey, valueName, NULL, NULL, (LPBYTE)szDeaultPath, &dwBufLen)){
		strcpy(msg, GetErrorMessage("RegQueryValueExW 실패 : ", GetLastError()));
		strcpy(buf, "RegQueryValueExW 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "RegQueryValueExW 성공", msg);

		return FALSE;
	}

	wcscpy(value, szDeaultPath);
	RegCloseKey(hKey);

	return TRUE;
}

BOOL GetRegLocalMachineValueA(char *path, char *valueName, char *value)
{
	HKEY hKey;
	char szDeaultPath[_MAX_PATH] = {0, };
	DWORD dwBufLen = MAX_PATH;
	char msg[BUFSIZ], buf[BUFSIZ];

	if(RegOpenKeyExA(HKEY_LOCAL_MACHINE, path, 0, KEY_READ, &hKey)){
		strcpy(msg, GetErrorMessage("RegOpenKeyExW 실패 : ", GetLastError()));
		strcpy(buf, "RegOpenKeyExW 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "RegOpenKeyExW 성공", msg);

		return FALSE;
	}

	if(RegQueryValueExA(hKey, valueName, NULL, NULL, (LPBYTE)szDeaultPath, &dwBufLen)){
		strcpy(msg, GetErrorMessage("RegQueryValueExW 실패 : ", GetLastError()));
		strcpy(buf, "RegQueryValueExW 실패");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "RegQueryValueExW 성공", msg);

		return FALSE;
	}

	strcpy(value, szDeaultPath);
	RegCloseKey(hKey);

	return TRUE;
}