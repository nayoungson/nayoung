#include "TestGetOEMCP.h"

//UINT GetOEMCP(void); 
//운영 체제에 대한 현재의 원래 장비 제조업체 (OEM) 코드 페이지 식별자를 검색합니다.


/**
* UINT GetOEMCP(void)
* 운영 체제에 대한 현재의 원래 장비 제조업체 (OEM) 코드 페이지 식별자를 검색한다.
* @author : 손찬영  
*
* @return 운영 체제에 대한 현재 OEM 코드 페이지 식별자
*/
BOOL test_GetOEMCP(void)
{
	BOOL result = TRUE;

	char msg[BUFSIZ];
	char buf[BUFSIZ];
	UINT testResult = 0;
	
	DWORD errorCode=0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	testResult=GetOEMCP();

	if(testResult == CODEPAGE_WINDOW){		
		sprintf(msg, "GetOEMCP() 리턴값 : %d\n\nks_c_5601-1987\nANSI/OEM Korean (Unified Hangul Code)", testResult);
		sprintf(buf, "GetOEMCP 성공");
	
	}else if(testResult == 65001){
		sprintf(msg, "GetOEMCP() 리턴값 : 65001\nutf-8\nUnicode (UTF-8)", testResult);
		sprintf(buf, "GetOEMCP 성공");
	
	}else if(errorCode = GetLastError()){
		sprintf(msg, GetErrorMessage("GetOEMCP 실패 : ", errorCode));
		strcpy(buf, "GetOEMCP 실패");
		result = FALSE;	

	}else{
		sprintf(msg, "GetOEMCP() 리턴값 : %d\n코드페이지를 참조하세요.", testResult);
		sprintf(buf, "GetOEMCP 성공");
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetOEMCP 성공", msg);

	return result;
}