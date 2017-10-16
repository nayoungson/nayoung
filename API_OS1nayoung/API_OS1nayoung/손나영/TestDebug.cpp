#include "TestFunction.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <atlstr.h>

BOOL test_DebugBreak(){
	BOOL result = true;

	__try{
		DebugBreak();
	}
	__except(EXCEPTION_EXECUTE_HANDLER) {
			
	}
	return result;
}


/**
		 디버그 메시지를 확인하는데 쓰이는 가장 범용적인 도구. 
		 DebugView on 으로도 확인 가능/
*/
BOOL test_OutputDebugStringA()
{
	BOOL result = true;
	//HWND hWnd=0;
	//char str[255];
	//char buffer[255];
	//char outputDebugStringBuffer[1000] = {0};

	//ULONG_PTR args[1];
	//args[0] = (ULONG_PTR)outputDebugStringBuffer;
	//char meg[BUFSIZ] = "FAIL";
	
	/**
	__try{
		wsprintf(str, L"캡션 메시지: %s", L"OutputDebugStringA");
		OutputDebugString(L"DSF");
	}
	__except(EXCEPTION_EXECUTE_HANDLER) {
			//wresult(__FILE__, __LINE__, "OutputDebugStringA", "program", "program",meg);
			MessageBox(hWnd, L"OutputDebugStringA", L"Dialog Box", MB_OK);

	}
	*/

	//OutputDebugString( _T( "info. information" ) );
	OutputDebugString(L"디버그 테스트");
 
	
	int nCnt = 0;
	CString strText;
	strText.Format( _T( "info. nCnt value [ %d ]" ), nCnt );
	OutputDebugString( strText );



 return result;

}

BOOL test_OutputDebugStringW()
{
	BOOL result = true;
	//HWND hWnd=0;
	//char str[255];
	//char buffer[255];
	//char outputDebugStringBuffer[1000] = {0};

	//ULONG_PTR args[1];
	//args[0] = (ULONG_PTR)outputDebugStringBuffer;
	//char meg[BUFSIZ] = "FAIL";
	
/**
	__try{
		wsprintf(str, L"캡션 메시지: %s", L"OutputDebugStringA");
		OutputDebugString("ㅗㅑㅕㅎ");
	}
	__except(EXCEPTION_EXECUTE_HANDLER) {
			//wresult(__FILE__, __LINE__, "OutputDebugStringA", "program", "program",meg);
			MessageBox(hWnd, L"OutputDebugStringA", L"Dialog Box", MB_OK);

	}
	*/

	//OutputDebugString( _T( "info. information" ) );
	OutputDebugString(L"디버그 테스트");
 
	int nCnt = 0;
	CString strText;
	strText.Format( _T( "info. nCnt value [ %d ]" ), nCnt );
	OutputDebugString( strText );

 return result;

}