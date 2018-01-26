#include "TestMetafile.h"

/**
* HENHMETAFILE GetEnhMetaFile(
  _In_ LPCTSTR lpszMetaFile
  );
* ������ ���Ͽ� ����� ��ȭ �� ������ �ĺ��ϴ� ��Ÿ ���� �ڵ��� ����
* @author : �ճ���
*
* @param lpszMetaFile Ȯ�� ��Ÿ ������ �̸��� �����ϴ� Null ���� ���ڿ��� ���� ������.
* @return enhanced metafile�� ���� �ڵ�.
*/

// Creating a handle tha identifies the enhanced-format metafile stored in the specified file.
BOOL test_GetEnhMetaFileA(){

	#ifdef OQADBGPRINT
	printf("test_GetEnhMetaFileA \n");
	#endif

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";	

	BOOL result = FALSE;
	//HENHMETAFILE hemf = GetEnhMetaFileA("C:\\Users\\NAYOUNG\\Desktop\\Tmax\\TestEnh.emf"); 
	HENHMETAFILE hemf = GetEnhMetaFileA("�ճ���\\TestEnh.emf"); 

	// if want to convert the file, it can use the SetWinMetaFileBits function.
	// SetWinMetaFileBits();

	if(hemf != NULL){
		result = TRUE;
		strcpy(buf, "SUCCESS");
		sprintf(msg, " GetEnhMetaFileA() : SUCCESS");

		// if the app no longer needs an handle, it should call th DeleteEnhMetaFile function.
		// DeleteEnhMetaFile()
		DeleteEnhMetaFile(hemf);

	}else{
		sprintf(msg, " GetEnhMetaFileA() : FAIL");
	}

	wresult(__FILE__, __LINE__, "GetEnhMetaFileA", buf, "SUCCESS", msg);

	return result;
}


/**
* HENHMETAFILE GetEnhMetaFile(
  _In_ LPCTSTR lpszMetaFile
  );
* ������ ���Ͽ� ����� ��ȭ �� ������ �ĺ��ϴ� ��Ÿ ���� �ڵ��� ����
* @author : �ճ���
*
* @param lpszMetaFile Ȯ�� ��Ÿ ������ �̸��� �����ϴ� Null ���� ���ڿ��� ���� ������.
* @return enhanced metafile�� ���� �ڵ�.
*/

// Creating a handle tha identifies the enhanced-format metafile stored in the specified file.
BOOL test_GetEnhMetaFileW(){

	#ifdef OQADBGPRINT
	printf("test_GetEnhMetaFileW \n");
	#endif

	char buf[BUFSIZ] = "FAIL";	
	char msg[BUFSIZ] = "FAIL";	

	BOOL result = FALSE;
	//HENHMETAFILE hemf = GetEnhMetaFileW(L"C:\\Users\\NAYOUNG\\Desktop\\Tmax\\TestEnh.emf"); 
	HENHMETAFILE hemf = GetEnhMetaFileW(L"�ճ���\\TestEnh.emf"); 

	// if want to convert the file, it can use the SetWinMetaFileBits function.
	// SetWinMetaFileBits();

	if(hemf != NULL){
		// hemf function is 
		result = TRUE;
		strcpy(buf, "SUCCESS");
		sprintf(msg, " GetEnhMetaFileW() : SUCCESS");

		// if the app no longer needs an handle, it should call th DeleteEnhMetaFile function.
		// DeleteEnhMetaFile()
		DeleteEnhMetaFile(hemf);

	}else{
		sprintf(msg, " GetEnhMetaFileW() : FAIL");
	}

	wresult(__FILE__, __LINE__, "GetEnhMetaFileW", buf, "SUCCESS", msg);

	return result;
}


/**
* HENHMETAFILE GetMetaFile (
  _In_ LPCTSTR lpszMetaFile
  );
* ������ ���Ͽ� ����� ��Ÿ ������ �ĺ��ϴ� �ڵ��� ����.
* @author : �ճ���
*
* @param lpszMetaFile ��Ÿ ������ �̸��� �����ϴ� Null ���� ���ڿ��� ���� ������
* @return metafile�� ���� �ڵ�..
*/
BOOL test_GetMetaFileA(){

	#ifdef OQADBGPRINT
	printf("test_GetMetaFileA \n");
	#endif

	char buf[BUFSIZ] = "FAIL";	
	char msg[BUFSIZ] = "FAIL";	

	BOOL result = FALSE;
	//HMETAFILE hemf = GetMetaFileA("C:\\Users\\NAYOUNG\\Desktop\\Tmax\\TestEnh.emf");
	HMETAFILE hemf = GetMetaFileA("�ճ���\\TestEnh.emf");

	if(hemf != NULL){
		result = TRUE;
		strcpy(buf, "SUCCESS");
		sprintf(msg, " GetMetaFileA() : SUCCESS");

		// if the app no longer needs an handle, it should call th DeleteEnhMetaFile function.
		// DeleteEnhMetaFile()
		DeleteMetaFile(hemf);

	}else{
		if(GetLastError() == 0)
			strcpy(msg, " GetMetaFileW() : FAIL \n\n GetMetaFile �Լ��� Win32 API���� ���̻� �������� �ʽ��ϴ�. \n 16-bit ȣȯ�� ���ؼ��� �����ִ� �����Դϴ�. \n GetEnhMetaFile �Լ��� ����Ͻʽÿ�");
		else
			sprintf(msg, " GetMetaFileW() : FAIL");
	}

	wresult(__FILE__, __LINE__, "GetMetaFileA", buf, "SUCCESS", msg);

	return result;
}


/**
* HENHMETAFILE GetMetaFile (
  _In_ LPCTSTR lpszMetaFile
  );
* ������ ���Ͽ� ����� ��Ÿ ������ �ĺ��ϴ� �ڵ��� ����.
* @author : �ճ���
*
* @param lpszMetaFile ��Ÿ ������ �̸��� �����ϴ� Null ���� ���ڿ��� ���� ������
* @return metafile�� ���� �ڵ�.
*/
BOOL test_GetMetaFileW(){

	#ifdef OQADBGPRINT
	printf("test_GetMetaFileW \n");
	#endif

	char buf[BUFSIZ] = "FAIL";	
	char msg[BUFSIZ] = "FAIL";	

	BOOL result = FALSE;
	//HMETAFILE hemf = GetMetaFileW(L"C:\\Users\\NAYOUNG\\Desktop\\Tmax\\TestEnh.emf");
	HMETAFILE hemf = GetMetaFileW(L"�ճ���\\TestEnh.emf");

	if(hemf != NULL){
		result = TRUE;
		strcpy(buf, "SUCCESS");
		sprintf(msg, " GetMetaFileW() : SUCCESS");

		// if the app no longer needs an handle, it should call th DeleteEnhMetaFile function.
		// DeleteEnhMetaFile()
		DeleteMetaFile(hemf);

	}else{
		if(GetLastError() == 0)
			strcpy(msg, " GetMetaFileW() : FAIL \n\n GetMetaFile �Լ��� Win32 API���� ���̻� �������� �ʽ��ϴ�. \n 16-bit ȣȯ�� ���ؼ��� �����ִ� �����Դϴ�. \n GetEnhMetaFile �Լ��� ����Ͻʽÿ�");
		else
			sprintf(msg, " GetMetaFileW() : FAIL");
	}

	wresult(__FILE__, __LINE__, "GetMetaFileW", buf, "SUCCESS", msg);

	return result;
}