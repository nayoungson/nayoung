#include "TestGetOEMCP.h"

//UINT GetOEMCP(void); 
//� ü���� ���� ������ ���� ��� ������ü (OEM) �ڵ� ������ �ĺ��ڸ� �˻��մϴ�.


/**
* UINT GetOEMCP(void)
* � ü���� ���� ������ ���� ��� ������ü (OEM) �ڵ� ������ �ĺ��ڸ� �˻��Ѵ�.
* @author : ������  
*
* @return � ü���� ���� ���� OEM �ڵ� ������ �ĺ���
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
		sprintf(msg, "GetOEMCP() ���ϰ� : %d\n\nks_c_5601-1987\nANSI/OEM Korean (Unified Hangul Code)", testResult);
		sprintf(buf, "GetOEMCP ����");
	
	}else if(testResult == 65001){
		sprintf(msg, "GetOEMCP() ���ϰ� : 65001\nutf-8\nUnicode (UTF-8)", testResult);
		sprintf(buf, "GetOEMCP ����");
	
	}else if(errorCode = GetLastError()){
		sprintf(msg, GetErrorMessage("GetOEMCP ���� : ", errorCode));
		strcpy(buf, "GetOEMCP ����");
		result = FALSE;	

	}else{
		sprintf(msg, "GetOEMCP() ���ϰ� : %d\n�ڵ��������� �����ϼ���.", testResult);
		sprintf(buf, "GetOEMCP ����");
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "GetOEMCP ����", msg);

	return result;
}