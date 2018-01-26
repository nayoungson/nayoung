#include "TestCrypt.h"


/**
* BOOL WINAPI CryptAcquireContext(
  _Out_ HCRYPTPROV *phProv,
  _In_  LPCTSTR    pszContainer,
  _In_  LPCTSTR    pszProvider,
  _In_  DWORD      dwProvType,
  _In_  DWORD      dwFlags
);
* 특정 암호화 서비스 공급자 (CSP) 내의 특정 키 컨테이너에 대한 핸들을 가져 온다. 사용되지 않음.
* @author : 손찬영  
*
* @param  phProv CSP의 핸들에 대한 포인터. CSP 사용을 마쳤으면 CryptReleaseContext 함수를 호출하여 핸들을 해제한다.
* @param  pszContainer 키 컨테이너 이름
* @param  pszProvider 사용할 CSP의 이름을 포함하는 Null 종료 문자열.  NULL 이면 사용자 기본 공급자가 사용
* @param  dwProvType 취득 할 공급자의 유형을 지정
* @param  dwFlags CRYPT_VERIFYCONTEXT, CRYPT_NEWKEYSET 등.
* @return 성공/실패 여부
*/
BOOL test_CryptAcquireContextW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode = 0;

	HCRYPTPROV hCryptProv = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	//키셋 생성하지 않고 성공
	if(CryptAcquireContext(
        &hCryptProv, 
        NULL, 
        NULL, 
        PROV_RSA_FULL, 
        0)) 
    {
        sprintf(msg, "CryptAcquireContext (기존 키)성공 : hCryptProv = %lu", hCryptProv);
		strcpy(buf, "CryptAcquireContext 성공");

	}else{
		if ((errorCode = GetLastError()) == NTE_BAD_KEYSET)
		{
			//키셋 생성 시도
			// No default container was found. Attempt to create it.
			if(CryptAcquireContext(
				&hCryptProv, 
				NULL, 
				NULL, 
				PROV_RSA_FULL, 
				CRYPT_NEWKEYSET)) 
			{
				sprintf(msg, "CryptAcquireContext (생성 후)성공 : hCryptProv = %lu", hCryptProv);
				strcpy(buf, "CryptAcquireContext 성공");

			//키셋 생성 후에도 실패
			}else{ 
				strcpy(msg, GetErrorMessage("CryptAcquireContext 실패 : ", errorCode));
				strcpy(buf, "CryptAcquireContext 실패");

				result = FALSE;
			}
		
		//다른 이유로 실패
		}else{
			strcpy(msg, GetErrorMessage("CryptAcquireContext 실패 : ", errorCode));
			strcpy(buf, "CryptAcquireContext 실패");

			result = FALSE;
		}
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CryptAcquireContext 성공", msg);

	return result;
}

/**
* BOOL WINAPI CryptSignHash(
  _In_    HCRYPTHASH hHash,
  _In_    DWORD      dwKeySpec,
  _In_    LPCTSTR    sDescription,
  _In_    DWORD      dwFlags,
  _Out_   BYTE       *pbSignature,
  _Inout_ DWORD      *pdwSigLen
);
* 데이터에 서명한다. 모든 서명 알고리즘이 비대칭이므로 속도가 느리기 때문에 CryptoAPI는 데이터에 직접 서명 할 수 없다. 
대신 데이터가 먼저 해시되고 CryptSignHash가 해시에 서명하는 데 사용한다. 더 이상 사용되지 않음(deprecated).
* @author : 손찬영  
*
* @param  hHash 서명 할 해시 객체의 핸들
* @param  dwKeySpec 프로 바이더의 컨테이너로부터 사용하는 비공개 키를 식별한다. AT_KEYEXCHANGE 또는 AT_SIGNATURE
* @param  sDescription 이 매개 변수는 더 이상 사용되지 않으므로 보안 취약점을 방지 하려면 NULL로 설정
* @param  dwFlags CRYPT_NOHASHOID 등.
* @param  pbSignature 서명 데이터를 수신하는 버퍼에 대한 포인터
* @param  pdwSigLen bSignature 버퍼 의 크기 (바이트)를 지정 하는 DWORD 값의 포인터
* @return 성공/실패 여부
*/
BOOL test_CryptSignHashA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;

	HCRYPTPROV hProv;
	BYTE *pbBuffer= (BYTE *)"The data that is to be hashed and signed.";
	DWORD dwBufferLen = strlen((char *)pbBuffer)+1;
	HCRYPTHASH hHash;      
	BYTE *pbSignature;
	DWORD dwSigLen;

	HCRYPTKEY *phKey = (HCRYPTKEY *)malloc(sizeof(HCRYPTKEY)*BUFSIZ);

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0)){
		sprintf(msg, GetErrorMessage("CryptAcquireContext 실패 : ", GetLastError()));
		strcpy(buf, "CryptAcquireContext 실패");

		wresult(__FILE__, __LINE__ , "CryptSignHashA", buf, "CryptAcquireContext 성공", msg);

		return FALSE;
	}
	/*if(!CryptGetUserKey(hProv, AT_SIGNATURE, &hKey)){
		sprintf(msg, GetErrorMessage("CryptGetUserKey 실패 : ", GetLastError()));
		strcpy(buf, "CryptGetUserKey 실패");

		wresult(__FILE__, __LINE__ , "CryptSignHashA", buf, "CryptGetUserKey 성공", msg);

		return FALSE;
	}*/

	/*if(!CryptExportKey(hKey, NULL, PUBLICKEYBLOB, 0, NULL, &dwBlobLen)){
		sprintf(msg, GetErrorMessage("CryptExportKey 실패 : ", GetLastError()));
		strcpy(buf, "CryptExportKey 실패");
		
		wresult(__FILE__, __LINE__ , "CryptSignHashA", buf, "CryptExportKey 성공", msg);

		return FALSE;
	}*/

	/*if(!(pbKeyBlob = (BYTE*)malloc(dwBlobLen))){
		sprintf(msg, GetErrorMessage("malloc pbKeyBlob 실패 : ", GetLastError()));
		strcpy(buf, "malloc pbKeyBlob 실패");

		wresult(__FILE__, __LINE__ , "CryptSignHashA", buf, "malloc pbKeyBlob 성공", msg);

		return FALSE;
	}*/

	/*if(!CryptExportKey(hKey, NULL, PUBLICKEYBLOB, 0, pbKeyBlob, &dwBlobLen)){
		sprintf(msg, GetErrorMessage("CryptExportKey 실패 : ", GetLastError()));
		strcpy(buf, "CryptExportKey 실패");

		wresult(__FILE__, __LINE__ , "CryptSignHashA", buf, "CryptExportKey 성공", msg);

		return FALSE;
	}*/
	
	CryptGenKey(hProv, AT_SIGNATURE, CRYPT_NO_SALT, phKey);
	/*if(!CryptGenKey(hProv, CALG_RSA_SIGN, AT_SIGNATURE, phKey)){
		sprintf(msg, GetErrorMessage("CryptGenKey 실패 : ", GetLastError()));
		strcpy(buf, "CryptGenKey 실패");

		wresult(__FILE__, __LINE__ , "CryptSignHashA", buf, "CryptGenKey 성공", msg);

		return FALSE;
	}*/

	if(!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)){
		sprintf(msg, GetErrorMessage("CryptCreateHash 실패 : ", GetLastError()));
		strcpy(buf, "CryptCreateHash 실패");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CryptCreateHash 성공", msg);

		return FALSE;
	}

	if(!CryptHashData(hHash, pbBuffer, dwBufferLen, 0)){
		sprintf(msg, GetErrorMessage("CryptHashData 실패 : ", GetLastError()));
		strcpy(buf, "CryptHashData 실패");

		wresult(__FILE__, __LINE__ , "__FUNCTION__", buf, "CryptHashData 성공", msg);

		return FALSE;
	}

	
	//if(!CryptSignHashA(hHash, AT_SIGNATURE, NULL, 0, NULL, &dwSigLen)){ //dwSigLen을 얻기 위해 수행
	//	sprintf(msg, GetErrorMessage("CryptSignHashA 실패 : ", GetLastError()));
	//	strcpy(buf, "CryptSignHashA 실패");

	//	wresult(__FILE__, __LINE__ , "CryptSignHashA", buf, "CryptSignHashA 성공", msg);

	//	return FALSE;
	//}

	dwSigLen= 0;
	CryptSignHashA(hHash, AT_SIGNATURE, NULL, 0, NULL, &dwSigLen);
	if(!(pbSignature = (BYTE *)HeapAlloc(GetProcessHeap(), 0, dwSigLen))){ //동적할당 실패
		sprintf(msg, GetErrorMessage("HeapAlloc 실패 : ", GetLastError()));
		strcpy(buf, "HeapAlloc 실패");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "HeapAlloc 성공", msg);

		return FALSE;
	}

	//if(CryptSignHashA(hHash, AT_SIGNATURE, NULL, 0, pbSignature, &dwSigLen)){
	if(CryptSignHashA(hHash, AT_SIGNATURE, NULL, 0, pbSignature, &dwSigLen)){
		strcpy(msg, "CryptSignHashA 성공 : 메세지에 서명 완료");
		strcpy(buf, "CryptSignHashA 성공");
	
	}else{
		sprintf(msg, GetErrorMessage("CryptSignHashA 실패 : ", GetLastError()));
		strcpy(buf, "CryptSignHashA 실패");
		
		result = FALSE;
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CryptSignHashA 성공", msg);

	return result;
}


/**
* BOOL WINAPI CryptVerifySignature(
  _In_ HCRYPTHASH hHash,
  _In_ BYTE       *pbSignature,
  _In_ DWORD      dwSigLen,
  _In_ HCRYPTKEY  hPubKey,
  _In_ LPCTSTR    sDescription,
  _In_ DWORD      dwFlags
);
* 해시 개체의 서명을 확인한다. 이 함수를 호출하기 전에 CryptCreateHash를 호출하여 해시 객체의 핸들을 만들어야 한다. 
그 다음 CryptHashData 또는 CryptHashSessionKey를 사용하여 데이터 또는 세션 키를 해시 객체에 추가한다.
CryptVerifySignature가 완료되면 hHash 핸들을 사용하여 CryptDestroyHash만 호출 할 수 있다.  더 이상 사용되지 않음(deprecated).
* @author : 손찬영  
*
* @param  hHash			확인할 해시 객체에 대한 핸들
* @param  pbSignature	검증 할 서명 데이터의 주소
* @param  dwSigLen		pbSignature 서명 데이터 의 바이트 수
* @param  hPubKey		서명을 인증하는 데 사용할 공용키에 대한 핸들
* @param  sDescription	이 매개 변수는 더 이상 사용되지 않아야하며 보안 취약성을 방지 하려면 NULL 로 설정
* @param  dwFlags		CRYPT_NOHASHOID 등.
* @return 성공/실패 여부
*/
BOOL test_CryptVerifySignatureA()
{
	//printf("test_CryptVerifySignatureA 진입합니다..\n");
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;

	HCRYPTPROV hProv;
	BYTE *pbBuffer= (BYTE *)"The data that is to be hashed and signed.";
	DWORD dwBufferLen = strlen((char *)pbBuffer) + 1;
	HCRYPTHASH hHash;      
	BYTE *pbSignature;
	DWORD dwSigLen;

	//printf("malloc 수행합니다..\n");
	HCRYPTKEY *phKey = (HCRYPTKEY *)malloc(sizeof(HCRYPTKEY)*BUFSIZ*2);

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif


	printf("CryptAcquireContext 수행합니다..\n");
	if(!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0)){
		printf("CryptAcquireContext 실패..\n");
		sprintf(msg, GetErrorMessage("CryptAcquireContext 실패 : ", GetLastError()));
		//sprintf(msg, "CryptAcquireContext 실패");
		strcpy(buf, "CryptAcquireContext 실패");

		//printf("wresult 수행합니다..\n");
		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CryptAcquireContext 성공", msg);
		//printf("return FALSE 수행합니다..\n");

		return FALSE;
	}

	CryptGenKey(hProv, AT_SIGNATURE, CRYPT_NO_SALT, phKey);

	if(!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)){
		sprintf(msg, GetErrorMessage("CryptCreateHash 실패 : ", GetLastError()));
		strcpy(buf, "CryptCreateHash 실패");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CryptCreateHash 성공", msg);

		return FALSE;
	}
	if(!CryptHashData(hHash, pbBuffer, dwBufferLen, 0)){
		sprintf(msg, GetErrorMessage("CryptHashData 실패 : ", GetLastError()));
		strcpy(buf, "CryptHashData 실패");

		wresult(__FILE__, __LINE__ , "__FUNCTION__", buf, "CryptHashData 성공", msg);

		return FALSE;
	}

	dwSigLen= 0;
	CryptSignHashA(hHash, AT_SIGNATURE, NULL, 0, NULL, &dwSigLen);
	if(!(pbSignature = (BYTE *)HeapAlloc(GetProcessHeap(), 0, dwSigLen))){ //동적할당 실패
		sprintf(msg, GetErrorMessage("HeapAlloc 실패 : ", GetLastError()));
		strcpy(buf, "HeapAlloc 실패");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "HeapAlloc 성공", msg);

		return FALSE;
	}

	
	if(!CryptSignHashA(hHash, AT_SIGNATURE, NULL, 0, pbSignature, &dwSigLen)){
		sprintf(msg, GetErrorMessage("CryptSignHashA 실패 : ", GetLastError()));
		strcpy(buf, "CryptSignHashA 실패");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CryptSignHashA 성공", msg);

		return FALSE;
	
	}
	//printf("hHash = %d\npbSignature = %d\ndwSigLen = %d\nhPubKey = %d\n", hHash, *pbSignature, dwSigLen, *phKey);
	
	result = CryptVerifySignatureA(hHash, pbSignature, dwSigLen, *phKey, NULL, 0);
	if(result){
		sprintf(msg, "CryptVerifySignatureA 성공");
		strcpy(buf, "CryptVerifySignatureA 성공");
	
	}else{
		sprintf(msg, GetErrorMessage("CryptVerifySignatureA 실패 : ", GetLastError()));
		strcpy(buf, "CryptVerifySignatureA 실패");
		
		result = FALSE;
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CryptVerifySignatureA 성공", msg);

	//free(phKey);

	//-------------------------------------------------------------------
	// Destroy the hash object.

	if(hHash) 
		CryptDestroyHash(hHash);

	//-------------------------------------------------------------------
	// Release the provider handle.

	if(hProv) 
		CryptReleaseContext(hProv, 0);

	return result;
}