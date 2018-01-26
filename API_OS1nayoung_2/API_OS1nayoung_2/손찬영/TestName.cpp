#include "TestName.h"


/**
* BOOL WINAPI SetComputerName(
  _In_ LPCTSTR lpComputerName
);
* ���� ��ǻ�Ϳ� ���� �� NetBIOS �̸��� �����Ѵ�. �̸��� ������Ʈ���� ����Ǹ� �̸� ������ ������ ����ڰ� ��ǻ�͸� �ٽ� ������ �� ����ȴ�.
* @author : ������  
*
* @param  lpComputerName	������ ��ǻ�͸� ������ �� ����Ǵ� ��ǻ�� �̸�
* @return					����/���� ����
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

	/* �����ϰ��� �ϴ� ��ǻ�� �̸� */
	wcscpy(expectComputerName, L"OQATEST");
	printf("expectComputerName = %S\n", expectComputerName);


	/* �Լ� ���� �� ��ǻ���̸� ���󺹱͸� ���� ���� */
	/* ������ GetComputerName�� ipconfig /all�� HOST�̸��� �����´�(����� �Ŀ� ������Ʈ���� �ִ� ������ �����) */
	if(!GetComputerNameW(oldComputerName, &nSize)){
		strcpy(msg, GetErrorMessage("GetComputerName ���� : ", GetLastError()));
		strcpy(buf, "GetComputerName ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetComputerName ����", msg);

		return FALSE;
	}

	if(result = SetComputerNameW(expectComputerName)){

		/* �ٲٱ� �õ��� ���� ������Ʈ�� ���� �����ϸ� �������� �Ǵ� */
		if(!GetRegLocalMachineValueW(L"SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName", L"ComputerName", newComputerName)){
			return FALSE;
		}
		printf("newComputerName = %S\n", newComputerName);
		if(!wcscmp(newComputerName, expectComputerName)){
			sprintf(msg, "SetComputerNameW ���� : (expectComputerName = %S) = (NewName = %S)", expectComputerName, newComputerName);
			strcpy(buf, "SetComputerNameW ����");

		/* set�Լ��� ���������� ���� ���� ��������� ���� */
		}else{
			sprintf(msg, "SetComputerNameW ���� : (expectComputerName = %S) != (NewName = %S)", expectComputerName, newComputerName);
			strcpy(buf, "SetComputerNameW ����");

			result = FALSE;
		}

	}else{
		strcpy(msg, GetErrorMessage("SetComputerNameW ���� : ", GetLastError()));
		strcpy(buf, "SetComputerNameW ����");
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetComputerNameW ����", msg);


	/* ������ ��ǻ�� �̸����� ���󺹱� �� */
	printf("oldComputerName = %S\n", oldComputerName);
	if(!SetComputerNameW(oldComputerName)){
		#ifdef OQADBGPRINT
		printf("���� �̸����� �������� �ʾ���. ����� �� �̸��� �����.\n");
		#endif
	}

	return result;
}


/**
* BOOL WINAPI SetComputerName(
  _In_ LPCTSTR lpComputerName
);
* ���� ��ǻ�Ϳ� ���� �� NetBIOS �̸��� �����Ѵ�. �̸��� ������Ʈ���� ����Ǹ� �̸� ������ ������ ����ڰ� ��ǻ�͸� �ٽ� ������ �� ����ȴ�.
* @author : ������  
*
* @param  lpComputerName	������ ��ǻ�͸� ������ �� ����Ǵ� ��ǻ�� �̸�
* @return					����/���� ����
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

	/* �����ϰ��� �ϴ� ��ǻ�� �̸� */
	strcpy(expectComputerName, "OQATEST");
	printf("expectComputerName = %s\n", expectComputerName);


	/* �Լ� ���� �� ��ǻ���̸� ���󺹱͸� ���� ���� */
	/* ������ GetComputerName�� ipconfig /all�� HOST�̸��� �����´�(����� �Ŀ� ������Ʈ���� �ִ� ������ �����) */
	if(!GetComputerNameA(oldComputerName, &nSize)){
		strcpy(msg, GetErrorMessage("GetComputerName ���� : ", GetLastError()));
		strcpy(buf, "GetComputerName ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetComputerName ����", msg);

		return FALSE;
	}

	if(result = SetComputerNameA(expectComputerName)){

		/* �ٲٱ� �õ��� ���� ������Ʈ�� ���� �����ϸ� �������� �Ǵ� */
		if(!GetRegLocalMachineValueA("SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName", "ComputerName", newComputerName)){
			return FALSE;
		}
		printf("newComputerName = %S\n", newComputerName);
		if(!strcmp(newComputerName, expectComputerName)){
			sprintf(msg, "SetComputerNameA ���� : (expectComputerName = %s) = (NewName = %s)", expectComputerName, newComputerName);
			strcpy(buf, "SetComputerNameA ����");

		/* set�Լ��� ���������� ���� ���� ��������� ���� */
		}else{
			sprintf(msg, "SetComputerNameA ���� : (expectComputerName = %s) != (NewName = %s)", expectComputerName, newComputerName);
			strcpy(buf, "SetComputerNameA ����");

			result = FALSE;
		}

	}else{
		strcpy(msg, GetErrorMessage("SetComputerNameA ���� : ", GetLastError()));
		strcpy(buf, "SetComputerNameA ����");
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetComputerNameA ����", msg);


	/* ������ ��ǻ�� �̸����� ���󺹱� �� */
	if(!SetComputerNameA(oldComputerName)){
		#ifdef OQADBGPRINT
		printf("���� �̸����� �������� �ʾ���. ����� �� �̸��� �����.\n");
		#endif
	}

	return result;
}



/**
* BOOL WINAPI SetComputerNameEx(
  _In_ COMPUTER_NAME_FORMAT NameType,
  _In_ LPCTSTR              lpBuffer
);
* ���� ��ǻ�Ϳ� ���� �� NetBIOS �Ǵ� DNS �̸��� �����Ѵ�.
* @author : ������  
*
* @param  NameType	������ �̸��� ����.ComputerNamePhysicalDnsDomain ��.
* @param  lpBuffer	���ο� �̸�.
* @return			����/���� ����
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

	/* �����ϰ��� �ϴ� ��ǻ�� �̸� */
	wcscpy(expectComputerName, L"OQATEST");
	printf("expectComputerName = %S\n", expectComputerName);


	/* �Լ� ���� �� ��ǻ���̸� ���󺹱͸� ���� ���� */
	/* ������ GetComputerName�� ipconfig /all�� HOST�̸��� �����´�(����� �Ŀ� ������Ʈ���� �ִ� ������ �����) */
	if(!GetComputerNameExW(ComputerNamePhysicalDnsHostname, oldComputerName, &nSize)){
		strcpy(msg, GetErrorMessage("GetComputerNameEx ���� : ", GetLastError()));
		strcpy(buf, "GetComputerNameEx ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetComputerNameEx ����", msg);

		return FALSE;
	}

	if(result = SetComputerNameExW(ComputerNamePhysicalDnsHostname, expectComputerName)){

		/* �ٲٱ� �õ��� ���� ������Ʈ�� ���� �����ϸ� �������� �Ǵ� */
		if(!GetRegLocalMachineValueW(L"SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName", L"ComputerName", newComputerName)){
			return FALSE;
		}
		printf("newComputerName = %S\n", newComputerName);
		if(!wcscmp(newComputerName, expectComputerName)){
			sprintf(msg, "SetComputerNameExW ���� : (expectComputerName = %S) = (NewName = %S)", expectComputerName, newComputerName);
			strcpy(buf, "SetComputerNameExW ����");

		/* set�Լ��� ���������� ���� ���� ��������� ���� */
		}else{
			sprintf(msg, "SetComputerNameExW ���� : (expectComputerName = %S) != (NewName = %S)", expectComputerName, newComputerName);
			strcpy(buf, "SetComputerNameExW ����");

			result = FALSE;
		}

	}else{
		strcpy(msg, GetErrorMessage("SetComputerNameExW ���� : ", GetLastError()));
		strcpy(buf, "SetComputerNameExW ����");
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetComputerNameW ����", msg);


	/* ������ ��ǻ�� �̸����� ���󺹱� �� */
	printf("oldComputerName = %S\n", oldComputerName);
	if(!SetComputerNameExW(ComputerNamePhysicalDnsHostname, oldComputerName)){
		#ifdef OQADBGPRINT
		printf("���� �̸����� �������� �ʾ���. ����� �� �̸��� �����.\n");
		#endif
	}

	return result;
}

/**
* BOOL WINAPI SetComputerNameEx(
  _In_ COMPUTER_NAME_FORMAT NameType,
  _In_ LPCTSTR              lpBuffer
);
* ���� ��ǻ�Ϳ� ���� �� NetBIOS �Ǵ� DNS �̸��� �����Ѵ�.
* @author : ������  
*
* @param  NameType	������ �̸��� ����.ComputerNamePhysicalDnsDomain ��.
* @param  lpBuffer	���ο� �̸�.
* @return			����/���� ����
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

	/* �����ϰ��� �ϴ� ��ǻ�� �̸� */
	strcpy(expectComputerName, "OQATEST");
	printf("expectComputerName = %S\n", expectComputerName);


	/* �Լ� ���� �� ��ǻ���̸� ���󺹱͸� ���� ���� */
	/* ������ GetComputerName�� ipconfig /all�� HOST�̸��� �����´�(����� �Ŀ� ������Ʈ���� �ִ� ������ �����) */
	if(!GetComputerNameExA(ComputerNamePhysicalDnsHostname, oldComputerName, &nSize)){
		strcpy(msg, GetErrorMessage("GetComputerNameEx ���� : ", GetLastError()));
		strcpy(buf, "GetComputerNameEx ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetComputerNameEx ����", msg);

		return FALSE;
	}
	printf("oldComputerName = %s\n", oldComputerName);
	printf("SetComputerNameExA����.. expectComputerName = %S\n", expectComputerName); //����..

	if(result = SetComputerNameExA(ComputerNamePhysicalDnsHostname, (LPTSTR)expectComputerName)){

		/* �ٲٱ� �õ��� ���� ������Ʈ�� ���� �����ϸ� �������� �Ǵ� */
		if(!GetRegLocalMachineValueA("SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName", "ComputerName", newComputerName)){
			return FALSE;
		}
		printf("newComputerName = %s\n", newComputerName);
		if(!strcmp(newComputerName, expectComputerName)){
			sprintf(msg, "SetComputerNameExA ���� : (expectComputerName = %s) = (NewName = %s)", expectComputerName, newComputerName);
			strcpy(buf, "SetComputerNameExA ����");

		/* set�Լ��� ���������� ���� ���� ��������� ���� */
		}else{
			sprintf(msg, "SetComputerNameExA ���� : (expectComputerName = %s) != (NewName = %s)", expectComputerName, newComputerName);
			strcpy(buf, "SetComputerNameExA ����");

			result = FALSE;
		}

	}else{
		strcpy(msg, GetErrorMessage("SetComputerNameExA ���� : ", GetLastError()));
		strcpy(buf, "SetComputerNameExA ����");
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetComputerNameExA ����", msg);


	/* ������ ��ǻ�� �̸����� ���󺹱� �� */
	printf("oldComputerName = %s\n", oldComputerName);
	if(!SetComputerNameExA(ComputerNamePhysicalDnsHostname, (LPTSTR)oldComputerName)){
		#ifdef OQADBGPRINT
		printf("���� �̸����� �������� �ʾ���. ����� �� �̸��� �����.\n");
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
* ������ �̸��� ����� ���ִ� ������ �̸��� ã�´�.
* @author : ������  
*
* @param  lpNameToResolve	�ذ��� �̸��� ����Ű�� ������
* @param  lpLocaleName		�� �Լ��� �Է� �̸��� ��ġ�ϴ� ������ �̸��� �˻��ϴ� ������ ������
* @param  cchLocaleName		lpLocaleName���� ǥ�õ� ������ ũ�� (����) 
* @return					�������� ���, ���� null ĳ���͸� ������, ������ ���� ������ ������ ������, ���� �� 0
*/
BOOL test_ResolveLocaleName()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCWSTR lpNameToResolve = L"ko"; //������ ��ȯ�� ���� ������ ���� �������
	LPCWSTR expectName = L"ko-KR";
	wchar_t lpLocaleName[LOCALE_NAME_MAX_LENGTH];
	int     cchLocaleName = LOCALE_NAME_MAX_LENGTH, ret = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	ret = ResolveLocaleName(lpNameToResolve, lpLocaleName, cchLocaleName);

	/* lpNameToResolve�� "ko" �� "ko-kr"�� ��ȯ�Ǹ� ���� */
	if(ret > 0){
		if(!wcscmp(expectName, lpLocaleName)){
			sprintf(msg, "ResolveLocaleName ���� : localeName = %S", lpLocaleName);
			strcpy(buf, "ResolveLocaleName ����");	


		/* �Լ��� ���������� ��ȯ�� ������ */
		}else{
			sprintf(msg, "ResolveLocaleName ���� : expectName = %S, result = %S", expectName, lpLocaleName);
			strcpy(buf, "ResolveLocaleName ����");

			result = FALSE;	
		}

	/* �Լ� ���� */
	}else{
		strcpy(msg, GetErrorMessage("ResolveLocaleName ���� : ", GetLastError()));
		strcpy(buf, "ResolveLocaleName ����");
		
		result = FALSE;	

	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ResolveLocaleName ����", msg);

	return result;
}


/**
* int GetUserDefaultLocaleName(
  _Out_ LPWSTR lpLocaleName,
  _In_  int    cchLocaleName
);
* ������� �⺻ ������ �̸��� �˻��Ѵ�. 
* @author : ������  
*
* @param  lpLocaleName		������ �̸��� �˻��ϴ� ������ ������
* @param  cchLocaleName		lpLocaleName���� ǥ�õ� ������ ũ�� (����)
* @return					�������� ���, ���� null ĳ���͸� ������, ������ ���� ������ ������ ������, ���� �� 0
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

	/* �ѱ� ko-KR���� �޾ƿ��� ���� Ȯ���Ѵ� */
	if(ret > 0){
		if(!wcscmp(expectName, lpLocaleName)){
			sprintf(msg, "GetUserDefaultLocaleName ���� : lpLocaleName = %S", lpLocaleName);
			strcpy(buf, "GetUserDefaultLocaleName ����");
		
		/* ������ ���� ko-KR�� �ƴ� */
		}else{
			sprintf(msg, "GetUserDefaultLocaleName ���� : expectName = %S, result = %S", expectName, lpLocaleName);
			strcpy(buf, "GetUserDefaultLocaleName ����");

			result = FALSE;	
		}

	/* GetUserDefaultLocaleName �Լ��� ���� */
	}else{
		strcpy(msg, GetErrorMessage("GetUserDefaultLocaleName ���� : ", GetLastError()));
		strcpy(buf, "GetUserDefaultLocaleName ����");
		
		result = FALSE;	

	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetUserDefaultLocaleName ����", msg);


	return result;
}

/**
* int GetSystemDefaultLocaleName(
  _Out_ LPWSTR lpLocaleName,
  _In_  int    cchLocaleName
);
* �ý����� ����Ʈ ������ ���� �����´�.
* @author : ������  
*
* @param  lpLocaleName		������ �̸��� �˻��ϴ� ������ ������
* @param  cchLocaleName		lpLocaleName���� ǥ�õ� ������ ũ�� (����)
* @return					�������� ���, ���� null ĳ���͸� ������, ������ ���� ������ ������ ������, ���� �� 0
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

	/* �ѱ� ko-KR���� �޾ƿ��� ���� Ȯ���Ѵ� */
	if(ret > 0){
		if(!wcscmp(expectName, lpLocaleName)){
			sprintf(msg, "GetSystemDefaultLocaleName ���� : lpLocaleName = %S", lpLocaleName);
			strcpy(buf, "GetSystemDefaultLocaleName ����");
		
		/* ������ ���� ko-KR�� �ƴ� */
		}else{
			sprintf(msg, "GetSystemDefaultLocaleName ���� : expectName = %S, result = %S", expectName, lpLocaleName);
			strcpy(buf, "GetSystemDefaultLocaleName ����");

			result = FALSE;	
		}

	/* GetUserDefaultLocaleName �Լ��� ���� */
	}else{
		strcpy(msg, GetErrorMessage("GetSystemDefaultLocaleName ���� : ", GetLastError()));
		strcpy(buf, "GetSystemDefaultLocaleName ����");
		
		result = FALSE;	

	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetSystemDefaultLocaleName ����", msg);


	return result;
}

/**
* BOOL WINAPI DnsHostnameToComputerName(
  _In_    LPCTSTR Hostname,
  _Out_   LPTSTR  ComputerName,
  _Inout_ LPDWORD nSize
);
* DNS ��Ÿ�� ȣ��Ʈ �̸��� NetBIOS ��Ÿ�� ��ǻ�� �̸����� ��ȯ�Ѵ�.
* @author : ������  
*
* @param  Hostname		DNS �̸�. DNS �̸��� ��ȿ�� ��ȯ ������ �̸��� �ƴϸ� �Լ��� �����Ѵ�.
* @param  ComputerName	��ǻ�� �̸����޴� ���ۿ� ���� ������
* @param  nSize			�Է½� ������ ũ�⸦ TCHAR�� ����, ��½�, ���� �� ���ڸ� �����ϰ� ��� ���ۿ� ����� TCHAR�� ���� ����
* @return				����/���� ����
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
		/* Hostname �빮�� ��ȯ �� = ComputerName�̸� ���� */
		if(!wcscmp(wcsupr(Hostname), ComputerName)){
			sprintf(msg, "DnsHostnameToComputerNameW ���� : ComputerName = %S", ComputerName);
			strcpy(buf, "DnsHostnameToComputerNameW ����");
		
		}else{
			sprintf(msg, "DnsHostnameToComputerNameW ���� : ComputerName = %S, wcsupr(Hostname) = %S", ComputerName, wcsupr(Hostname));
			strcpy(buf, "DnsHostnameToComputerNameW ����");

			result = FALSE;
		}

	}else{
		strcpy(msg, GetErrorMessage("DnsHostnameToComputerNameW ���� : ", GetLastError()));
		strcpy(buf, "DnsHostnameToComputerNameW ����");
		
		result = FALSE;
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "DnsHostnameToComputerNameW ����", msg);

	return result;
}

/**
* BOOL WINAPI DnsHostnameToComputerName(
  _In_    LPCTSTR Hostname,
  _Out_   LPTSTR  ComputerName,
  _Inout_ LPDWORD nSize
);
* DNS ��Ÿ�� ȣ��Ʈ �̸��� NetBIOS ��Ÿ�� ��ǻ�� �̸����� ��ȯ�Ѵ�.
* @author : ������  
*
* @param  Hostname		DNS �̸�. DNS �̸��� ��ȿ�� ��ȯ ������ �̸��� �ƴϸ� �Լ��� �����Ѵ�.
* @param  ComputerName	��ǻ�� �̸����޴� ���ۿ� ���� ������
* @param  nSize			�Է½� ������ ũ�⸦ TCHAR�� ����, ��½�, ���� �� ���ڸ� �����ϰ� ��� ���ۿ� ����� TCHAR�� ���� ����
* @return				����/���� ����
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
		/* Hostname �빮�� ��ȯ �� = ComputerName�̸� ���� */
		if(!strcmp(strupr(Hostname), ComputerName)){
			sprintf(msg, "DnsHostnameToComputerNameA ���� : ComputerName = %s", ComputerName);
			strcpy(buf, "DnsHostnameToComputerNameA ����");
		
		}else{
			sprintf(msg, "DnsHostnameToComputerNameA ���� : ComputerName = %s, strupr(Hostname) = %s", ComputerName, strupr(Hostname));
			strcpy(buf, "DnsHostnameToComputerNameA ����");

			result = FALSE;
		}

	}else{
		strcpy(msg, GetErrorMessage("DnsHostnameToComputerNameA ���� : ", GetLastError()));
		strcpy(buf, "DnsHostnameToComputerNameA ����");
		
		result = FALSE;
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "DnsHostnameToComputerNameA ����", msg);

	return result;
}


/**
* DWORD WINAPI GetLongPathNameTransacted(
  _In_  LPCTSTR lpszShortPath,
  _Out_ LPTSTR  lpszLongPath,
  _In_  DWORD   cchBuffer,
  _In_  HANDLE  hTransaction
);
* ������ ��θ� Ʈ����� �� �������� �� �������� ��ȯ�Ѵ�. �������� ����.
* @author : ������  
*
* @param  lpszShortPath		��ȯ �� ���
* @param  lpszLongPath		�� ��θ� ���� �� ���ۿ� ���� ������
* @param  cchBuffer			lpszLongPath�� ����Ű�� ������ ũ��
* @param  hTransaction		Ʈ����� �ڵ�
* @return					����/���� ����
*/
BOOL test_GetLongPathNameTransactedW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCWSTR lpszShortPath = L"������\\test_GetLongPathNameTransactedW.txt";
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
		sprintf(msg, "GetLongPathNameTransactedW ���� : LongPath = %S", LongPath);
		strcpy(buf, "GetLongPathNameTransactedW ����");

	}else{
		strcpy(msg, GetErrorMessage("GetLongPathNameTransactedW ���� : ", GetLastError()));
		strcpy(buf, "GetLongPathNameTransactedW ����");
		
		result = FALSE;
		
		
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetLongPathNameTransactedW ����", msg);

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
* ������ ��θ� Ʈ����� �� �������� �� �������� ��ȯ�Ѵ�. �������� ����.
* @author : ������  
*
* @param  lpszShortPath		��ȯ �� ���
* @param  lpszLongPath		�� ��θ� ���� �� ���ۿ� ���� ������
* @param  cchBuffer			lpszLongPath�� ����Ű�� ������ ũ��
* @param  hTransaction		Ʈ����� �ڵ�
* @return					���� �� ��ȯ ���� ���� null ���� �� ���� �ϰ� lpszLongPath�� ���� �� ���ڿ��� ����, ���� �� 0
*/
BOOL test_GetLongPathNameTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	LPCSTR	lpszShortPath = "������\\test_GetLongPathNameTransactedA.txt";
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
		sprintf(msg, "GetLongPathNameTransactedA ���� : LongPath = %s", LongPath);
		strcpy(buf, "GetLongPathNameTransactedA ����");

	}else{
		strcpy(msg, GetErrorMessage("GetLongPathNameTransactedA ���� : ", GetLastError()));
		strcpy(buf, "GetLongPathNameTransactedA ����");
		
		result = FALSE;
		
		
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetLongPathNameTransactedA ����", msg);

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
* ������ ������ ��ü ��ο� ���� �̸��� Ʈ����� �������� �˻��Ѵ�. �������� ����.
* @author : ������  
*
* @param  lpFileName		������ �̸�
* @param  nBufferLength		����̺� �� ��ο� ���� �� (null) ���� ���ڿ��� ���� �� ������ ũ��
* @param  lpBuffer			����̺� �� ��ο� ���� �� ���� ���ڿ��� �����ϴ� ���ۿ� ���� ������
* @param  lpFilePart		����� ���� ���� �̸� ���� ��� �� �ּ� ( lpBuffer ) �� �����ϴ� ���ۿ� ���� ������
* @param  hTransaction		Ʈ����� �ڵ�
* @return					���ϸ� ��ȯ ���� ���� �� ���ڸ� �����ϰ� lpBuffer�� ���� �� ���ڿ��� ����, ���� �� 0
*/
BOOL test_GetFullPathNameTransactedW()
{

	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode = 0;

	LPCTSTR lpFileName = L"������\\test_GetFullPathNameTransactedW.txt";
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
		sprintf(msg, "GetFullPathNameTransactedW ���� : Buffer = %S", lpBuffer);
		strcpy(buf, "GetFullPathNameTransactedW ����");

	}else{
		strcpy(msg, GetErrorMessage("GetFullPathNameTransactedW ���� : ", GetLastError()));
		strcpy(buf, "GetFullPathNameTransactedW ����");
		
		result = FALSE;
		
		
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetFullPathNameTransactedW ����", msg);

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
* ������ ������ ��ü ��ο� ���� �̸��� Ʈ����� �������� �˻��Ѵ�. �������� ����.
* @author : ������  
*
* @param  lpFileName		������ �̸�
* @param  nBufferLength		����̺� �� ��ο� ���� �� (null) ���� ���ڿ��� ���� �� ������ ũ��
* @param  lpBuffer			����̺� �� ��ο� ���� �� ���� ���ڿ��� �����ϴ� ���ۿ� ���� ������
* @param  lpFilePart		����� ���� ���� �̸� ���� ��� �� �ּ� ( lpBuffer ) �� �����ϴ� ���ۿ� ���� ������
* @param  hTransaction		Ʈ����� �ڵ�
* @return					���ϸ� ��ȯ ���� ���� �� ���ڸ� �����ϰ� lpBuffer�� ���� �� ���ڿ��� ����, ���� �� 0
*/
BOOL test_GetFullPathNameTransactedA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode = 0;

	LPCSTR lpFileName = "������\\test_GetFullPathNameTransactedA.txt";
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
		sprintf(msg, "GetFullPathNameTransactedA ���� : Buffer = %s", lpBuffer);
		strcpy(buf, "GetFullPathNameTransactedA ����");

	}else{
		strcpy(msg, GetErrorMessage("GetFullPathNameTransactedA ���� : ", GetLastError()));
		strcpy(buf, "GetFullPathNameTransactedA ����");
		
		result = FALSE;
		
		
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetFullPathNameTransactedA ����", msg);

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
		strcpy(msg, GetErrorMessage("RegOpenKeyExW ���� : ", GetLastError()));
		strcpy(buf, "RegOpenKeyExW ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "RegOpenKeyExW ����", msg);

		return FALSE;
	}

	if(RegQueryValueExW(hKey, valueName, NULL, NULL, (LPBYTE)szDeaultPath, &dwBufLen)){
		strcpy(msg, GetErrorMessage("RegQueryValueExW ���� : ", GetLastError()));
		strcpy(buf, "RegQueryValueExW ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "RegQueryValueExW ����", msg);

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
		strcpy(msg, GetErrorMessage("RegOpenKeyExW ���� : ", GetLastError()));
		strcpy(buf, "RegOpenKeyExW ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "RegOpenKeyExW ����", msg);

		return FALSE;
	}

	if(RegQueryValueExA(hKey, valueName, NULL, NULL, (LPBYTE)szDeaultPath, &dwBufLen)){
		strcpy(msg, GetErrorMessage("RegQueryValueExW ���� : ", GetLastError()));
		strcpy(buf, "RegQueryValueExW ����");
	
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "RegQueryValueExW ����", msg);

		return FALSE;
	}

	strcpy(value, szDeaultPath);
	RegCloseKey(hKey);

	return TRUE;
}