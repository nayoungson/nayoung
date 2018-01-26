#include "TestMetafile.h"

/**
* HENHMETAFILE GetEnhMetaFile(
  _In_ LPCTSTR lpszMetaFile
  );
* 지정된 파일에 저장된 강화 된 포맷을 식별하는 메타 파일 핸들을 생성
* @author : 손나영
*
* @param lpszMetaFile 확장 메타 파일의 이름을 지정하는 Null 종료 문자열에 대한 포인터.
* @return enhanced metafile에 대한 핸들.
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
	HENHMETAFILE hemf = GetEnhMetaFileA("손나영\\TestEnh.emf"); 

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
* 지정된 파일에 저장된 강화 된 포맷을 식별하는 메타 파일 핸들을 생성
* @author : 손나영
*
* @param lpszMetaFile 확장 메타 파일의 이름을 지정하는 Null 종료 문자열에 대한 포인터.
* @return enhanced metafile에 대한 핸들.
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
	HENHMETAFILE hemf = GetEnhMetaFileW(L"손나영\\TestEnh.emf"); 

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
* 지정된 파일에 저장된 메타 파일을 식별하는 핸들을 만듦.
* @author : 손나영
*
* @param lpszMetaFile 메타 파일의 이름을 지정하는 Null 종료 문자열에 대한 포인터
* @return metafile에 대한 핸들..
*/
BOOL test_GetMetaFileA(){

	#ifdef OQADBGPRINT
	printf("test_GetMetaFileA \n");
	#endif

	char buf[BUFSIZ] = "FAIL";	
	char msg[BUFSIZ] = "FAIL";	

	BOOL result = FALSE;
	//HMETAFILE hemf = GetMetaFileA("C:\\Users\\NAYOUNG\\Desktop\\Tmax\\TestEnh.emf");
	HMETAFILE hemf = GetMetaFileA("손나영\\TestEnh.emf");

	if(hemf != NULL){
		result = TRUE;
		strcpy(buf, "SUCCESS");
		sprintf(msg, " GetMetaFileA() : SUCCESS");

		// if the app no longer needs an handle, it should call th DeleteEnhMetaFile function.
		// DeleteEnhMetaFile()
		DeleteMetaFile(hemf);

	}else{
		if(GetLastError() == 0)
			strcpy(msg, " GetMetaFileW() : FAIL \n\n GetMetaFile 함수는 Win32 API에서 더이상 제공하지 않습니다. \n 16-bit 호환을 위해서만 남아있는 상태입니다. \n GetEnhMetaFile 함수를 사용하십시오");
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
* 지정된 파일에 저장된 메타 파일을 식별하는 핸들을 만듦.
* @author : 손나영
*
* @param lpszMetaFile 메타 파일의 이름을 지정하는 Null 종료 문자열에 대한 포인터
* @return metafile에 대한 핸들.
*/
BOOL test_GetMetaFileW(){

	#ifdef OQADBGPRINT
	printf("test_GetMetaFileW \n");
	#endif

	char buf[BUFSIZ] = "FAIL";	
	char msg[BUFSIZ] = "FAIL";	

	BOOL result = FALSE;
	//HMETAFILE hemf = GetMetaFileW(L"C:\\Users\\NAYOUNG\\Desktop\\Tmax\\TestEnh.emf");
	HMETAFILE hemf = GetMetaFileW(L"손나영\\TestEnh.emf");

	if(hemf != NULL){
		result = TRUE;
		strcpy(buf, "SUCCESS");
		sprintf(msg, " GetMetaFileW() : SUCCESS");

		// if the app no longer needs an handle, it should call th DeleteEnhMetaFile function.
		// DeleteEnhMetaFile()
		DeleteMetaFile(hemf);

	}else{
		if(GetLastError() == 0)
			strcpy(msg, " GetMetaFileW() : FAIL \n\n GetMetaFile 함수는 Win32 API에서 더이상 제공하지 않습니다. \n 16-bit 호환을 위해서만 남아있는 상태입니다. \n GetEnhMetaFile 함수를 사용하십시오");
		else
			sprintf(msg, " GetMetaFileW() : FAIL");
	}

	wresult(__FILE__, __LINE__, "GetMetaFileW", buf, "SUCCESS", msg);

	return result;
}