#include "TestCrypt.h"


/**
* BOOL WINAPI CryptAcquireContext(
  _Out_ HCRYPTPROV *phProv,
  _In_  LPCTSTR    pszContainer,
  _In_  LPCTSTR    pszProvider,
  _In_  DWORD      dwProvType,
  _In_  DWORD      dwFlags
);
* Ư�� ��ȣȭ ���� ������ (CSP) ���� Ư�� Ű �����̳ʿ� ���� �ڵ��� ���� �´�. ������ ����.
* @author : ������  
*
* @param  phProv CSP�� �ڵ鿡 ���� ������. CSP ����� �������� CryptReleaseContext �Լ��� ȣ���Ͽ� �ڵ��� �����Ѵ�.
* @param  pszContainer Ű �����̳� �̸�
* @param  pszProvider ����� CSP�� �̸��� �����ϴ� Null ���� ���ڿ�.  NULL �̸� ����� �⺻ �����ڰ� ���
* @param  dwProvType ��� �� �������� ������ ����
* @param  dwFlags CRYPT_VERIFYCONTEXT, CRYPT_NEWKEYSET ��.
* @return ����/���� ����
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

	//Ű�� �������� �ʰ� ����
	if(CryptAcquireContext(
        &hCryptProv, 
        NULL, 
        NULL, 
        PROV_RSA_FULL, 
        0)) 
    {
        sprintf(msg, "CryptAcquireContext (���� Ű)���� : hCryptProv = %lu", hCryptProv);
		strcpy(buf, "CryptAcquireContext ����");

	}else{
		if ((errorCode = GetLastError()) == NTE_BAD_KEYSET)
		{
			//Ű�� ���� �õ�
			// No default container was found. Attempt to create it.
			if(CryptAcquireContext(
				&hCryptProv, 
				NULL, 
				NULL, 
				PROV_RSA_FULL, 
				CRYPT_NEWKEYSET)) 
			{
				sprintf(msg, "CryptAcquireContext (���� ��)���� : hCryptProv = %lu", hCryptProv);
				strcpy(buf, "CryptAcquireContext ����");

			//Ű�� ���� �Ŀ��� ����
			}else{ 
				strcpy(msg, GetErrorMessage("CryptAcquireContext ���� : ", errorCode));
				strcpy(buf, "CryptAcquireContext ����");

				result = FALSE;
			}
		
		//�ٸ� ������ ����
		}else{
			strcpy(msg, GetErrorMessage("CryptAcquireContext ���� : ", errorCode));
			strcpy(buf, "CryptAcquireContext ����");

			result = FALSE;
		}
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CryptAcquireContext ����", msg);

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
* �����Ϳ� �����Ѵ�. ��� ���� �˰����� ���Ī�̹Ƿ� �ӵ��� ������ ������ CryptoAPI�� �����Ϳ� ���� ���� �� �� ����. 
��� �����Ͱ� ���� �ؽõǰ� CryptSignHash�� �ؽÿ� �����ϴ� �� ����Ѵ�. �� �̻� ������ ����(deprecated).
* @author : ������  
*
* @param  hHash ���� �� �ؽ� ��ü�� �ڵ�
* @param  dwKeySpec ���� ���̴��� �����̳ʷκ��� ����ϴ� ����� Ű�� �ĺ��Ѵ�. AT_KEYEXCHANGE �Ǵ� AT_SIGNATURE
* @param  sDescription �� �Ű� ������ �� �̻� ������ �����Ƿ� ���� ������� ���� �Ϸ��� NULL�� ����
* @param  dwFlags CRYPT_NOHASHOID ��.
* @param  pbSignature ���� �����͸� �����ϴ� ���ۿ� ���� ������
* @param  pdwSigLen bSignature ���� �� ũ�� (����Ʈ)�� ���� �ϴ� DWORD ���� ������
* @return ����/���� ����
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
		sprintf(msg, GetErrorMessage("CryptAcquireContext ���� : ", GetLastError()));
		strcpy(buf, "CryptAcquireContext ����");

		wresult(__FILE__, __LINE__ , "CryptSignHashA", buf, "CryptAcquireContext ����", msg);

		return FALSE;
	}
	/*if(!CryptGetUserKey(hProv, AT_SIGNATURE, &hKey)){
		sprintf(msg, GetErrorMessage("CryptGetUserKey ���� : ", GetLastError()));
		strcpy(buf, "CryptGetUserKey ����");

		wresult(__FILE__, __LINE__ , "CryptSignHashA", buf, "CryptGetUserKey ����", msg);

		return FALSE;
	}*/

	/*if(!CryptExportKey(hKey, NULL, PUBLICKEYBLOB, 0, NULL, &dwBlobLen)){
		sprintf(msg, GetErrorMessage("CryptExportKey ���� : ", GetLastError()));
		strcpy(buf, "CryptExportKey ����");
		
		wresult(__FILE__, __LINE__ , "CryptSignHashA", buf, "CryptExportKey ����", msg);

		return FALSE;
	}*/

	/*if(!(pbKeyBlob = (BYTE*)malloc(dwBlobLen))){
		sprintf(msg, GetErrorMessage("malloc pbKeyBlob ���� : ", GetLastError()));
		strcpy(buf, "malloc pbKeyBlob ����");

		wresult(__FILE__, __LINE__ , "CryptSignHashA", buf, "malloc pbKeyBlob ����", msg);

		return FALSE;
	}*/

	/*if(!CryptExportKey(hKey, NULL, PUBLICKEYBLOB, 0, pbKeyBlob, &dwBlobLen)){
		sprintf(msg, GetErrorMessage("CryptExportKey ���� : ", GetLastError()));
		strcpy(buf, "CryptExportKey ����");

		wresult(__FILE__, __LINE__ , "CryptSignHashA", buf, "CryptExportKey ����", msg);

		return FALSE;
	}*/
	
	CryptGenKey(hProv, AT_SIGNATURE, CRYPT_NO_SALT, phKey);
	/*if(!CryptGenKey(hProv, CALG_RSA_SIGN, AT_SIGNATURE, phKey)){
		sprintf(msg, GetErrorMessage("CryptGenKey ���� : ", GetLastError()));
		strcpy(buf, "CryptGenKey ����");

		wresult(__FILE__, __LINE__ , "CryptSignHashA", buf, "CryptGenKey ����", msg);

		return FALSE;
	}*/

	if(!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)){
		sprintf(msg, GetErrorMessage("CryptCreateHash ���� : ", GetLastError()));
		strcpy(buf, "CryptCreateHash ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CryptCreateHash ����", msg);

		return FALSE;
	}

	if(!CryptHashData(hHash, pbBuffer, dwBufferLen, 0)){
		sprintf(msg, GetErrorMessage("CryptHashData ���� : ", GetLastError()));
		strcpy(buf, "CryptHashData ����");

		wresult(__FILE__, __LINE__ , "__FUNCTION__", buf, "CryptHashData ����", msg);

		return FALSE;
	}

	
	//if(!CryptSignHashA(hHash, AT_SIGNATURE, NULL, 0, NULL, &dwSigLen)){ //dwSigLen�� ��� ���� ����
	//	sprintf(msg, GetErrorMessage("CryptSignHashA ���� : ", GetLastError()));
	//	strcpy(buf, "CryptSignHashA ����");

	//	wresult(__FILE__, __LINE__ , "CryptSignHashA", buf, "CryptSignHashA ����", msg);

	//	return FALSE;
	//}

	dwSigLen= 0;
	CryptSignHashA(hHash, AT_SIGNATURE, NULL, 0, NULL, &dwSigLen);
	if(!(pbSignature = (BYTE *)HeapAlloc(GetProcessHeap(), 0, dwSigLen))){ //�����Ҵ� ����
		sprintf(msg, GetErrorMessage("HeapAlloc ���� : ", GetLastError()));
		strcpy(buf, "HeapAlloc ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "HeapAlloc ����", msg);

		return FALSE;
	}

	//if(CryptSignHashA(hHash, AT_SIGNATURE, NULL, 0, pbSignature, &dwSigLen)){
	if(CryptSignHashA(hHash, AT_SIGNATURE, NULL, 0, pbSignature, &dwSigLen)){
		strcpy(msg, "CryptSignHashA ���� : �޼����� ���� �Ϸ�");
		strcpy(buf, "CryptSignHashA ����");
	
	}else{
		sprintf(msg, GetErrorMessage("CryptSignHashA ���� : ", GetLastError()));
		strcpy(buf, "CryptSignHashA ����");
		
		result = FALSE;
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CryptSignHashA ����", msg);

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
* �ؽ� ��ü�� ������ Ȯ���Ѵ�. �� �Լ��� ȣ���ϱ� ���� CryptCreateHash�� ȣ���Ͽ� �ؽ� ��ü�� �ڵ��� ������ �Ѵ�. 
�� ���� CryptHashData �Ǵ� CryptHashSessionKey�� ����Ͽ� ������ �Ǵ� ���� Ű�� �ؽ� ��ü�� �߰��Ѵ�.
CryptVerifySignature�� �Ϸ�Ǹ� hHash �ڵ��� ����Ͽ� CryptDestroyHash�� ȣ�� �� �� �ִ�.  �� �̻� ������ ����(deprecated).
* @author : ������  
*
* @param  hHash			Ȯ���� �ؽ� ��ü�� ���� �ڵ�
* @param  pbSignature	���� �� ���� �������� �ּ�
* @param  dwSigLen		pbSignature ���� ������ �� ����Ʈ ��
* @param  hPubKey		������ �����ϴ� �� ����� ����Ű�� ���� �ڵ�
* @param  sDescription	�� �Ű� ������ �� �̻� ������ �ʾƾ��ϸ� ���� ��༺�� ���� �Ϸ��� NULL �� ����
* @param  dwFlags		CRYPT_NOHASHOID ��.
* @return ����/���� ����
*/
BOOL test_CryptVerifySignatureA()
{
	//printf("test_CryptVerifySignatureA �����մϴ�..\n");
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

	//printf("malloc �����մϴ�..\n");
	HCRYPTKEY *phKey = (HCRYPTKEY *)malloc(sizeof(HCRYPTKEY)*BUFSIZ*2);

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif


	printf("CryptAcquireContext �����մϴ�..\n");
	if(!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0)){
		printf("CryptAcquireContext ����..\n");
		sprintf(msg, GetErrorMessage("CryptAcquireContext ���� : ", GetLastError()));
		//sprintf(msg, "CryptAcquireContext ����");
		strcpy(buf, "CryptAcquireContext ����");

		//printf("wresult �����մϴ�..\n");
		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CryptAcquireContext ����", msg);
		//printf("return FALSE �����մϴ�..\n");

		return FALSE;
	}

	CryptGenKey(hProv, AT_SIGNATURE, CRYPT_NO_SALT, phKey);

	if(!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)){
		sprintf(msg, GetErrorMessage("CryptCreateHash ���� : ", GetLastError()));
		strcpy(buf, "CryptCreateHash ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CryptCreateHash ����", msg);

		return FALSE;
	}
	if(!CryptHashData(hHash, pbBuffer, dwBufferLen, 0)){
		sprintf(msg, GetErrorMessage("CryptHashData ���� : ", GetLastError()));
		strcpy(buf, "CryptHashData ����");

		wresult(__FILE__, __LINE__ , "__FUNCTION__", buf, "CryptHashData ����", msg);

		return FALSE;
	}

	dwSigLen= 0;
	CryptSignHashA(hHash, AT_SIGNATURE, NULL, 0, NULL, &dwSigLen);
	if(!(pbSignature = (BYTE *)HeapAlloc(GetProcessHeap(), 0, dwSigLen))){ //�����Ҵ� ����
		sprintf(msg, GetErrorMessage("HeapAlloc ���� : ", GetLastError()));
		strcpy(buf, "HeapAlloc ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "HeapAlloc ����", msg);

		return FALSE;
	}

	
	if(!CryptSignHashA(hHash, AT_SIGNATURE, NULL, 0, pbSignature, &dwSigLen)){
		sprintf(msg, GetErrorMessage("CryptSignHashA ���� : ", GetLastError()));
		strcpy(buf, "CryptSignHashA ����");

		wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CryptSignHashA ����", msg);

		return FALSE;
	
	}
	//printf("hHash = %d\npbSignature = %d\ndwSigLen = %d\nhPubKey = %d\n", hHash, *pbSignature, dwSigLen, *phKey);
	
	result = CryptVerifySignatureA(hHash, pbSignature, dwSigLen, *phKey, NULL, 0);
	if(result){
		sprintf(msg, "CryptVerifySignatureA ����");
		strcpy(buf, "CryptVerifySignatureA ����");
	
	}else{
		sprintf(msg, GetErrorMessage("CryptVerifySignatureA ���� : ", GetLastError()));
		strcpy(buf, "CryptVerifySignatureA ����");
		
		result = FALSE;
	}

	wresult(__FILE__, __LINE__ , __FUNCTION__, buf, "CryptVerifySignatureA ����", msg);

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