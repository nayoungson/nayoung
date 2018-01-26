/*
*	작성자 : OQA1 손찬영
*/

#include "MyUtil.h"
#include <tlhelp32.h>

char *GetErrorMessage(const char *str, int errorCode) //할말, 에러코드
{
	wchar_t errMsg[BUFSIZ]; //char로 바꿔야 되는 문자열
	char *buf = NULL; //char로 변환된 문자열
	char *msg = (char *)malloc(sizeof(char)* BUFSIZ); //buf+errMsg
	int i=0;

#ifdef OQADBGPRINT
	printf("System Error Codes : %d (0x%x)\n", errorCode, errorCode);
#endif
	//FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS ,NULL, errorCode, 0, errMsg, 1024, NULL);

	int iLen = WideCharToMultiByte(CP_ACP, 0, errMsg, -1, buf, 0, NULL, NULL);
	buf = new char[iLen+1];
	WideCharToMultiByte(CP_ACP, 0, errMsg, -1, buf, iLen, NULL, NULL);


	while(buf[i++] != '\n'){
		if(i > 255){
			sprintf(buf, "알 수 없음(에러코드 : %d (0x%x))", errorCode, errorCode);
			break;
		}
	}
	buf[i-2] = '\0';
	
	if(str != NULL){
		strcpy(msg, str);
	}
	strcat(msg, buf);

	//free(msg);
	delete buf;

	return msg;
}

//BOOL SearchProcess(TCHAR* pro_exe)
//{
//	char msg[BUFSIZ];
//	HANDLE hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//	if(hSnapshot!=INVALID_HANDLE_VALUE)
//	{
//		PROCESSENTRY32 Pro_Entry32;
//		BOOL bProcessFound;
//		Pro_Entry32.dwSize=sizeof(PROCESSENTRY32);
//		bProcessFound=Process32FirstW(hSnapshot,&Pro_Entry32);
//		if(bProcessFound)
//		{
//			while(1)
//			{
//				bProcessFound=Process32NextW(hSnapshot,&Pro_Entry32);
//				if(bProcessFound==FALSE&&GetLastError()==ERROR_NO_MORE_FILES)
//				{
//					return 2;
//				}
//				else if(bProcessFound==FALSE)
//				{
//					strcpy(msg,GetErrorMessage("Process32NEXTW Fail : ",GetLastError()));
//					wresult(__FILE__,__LINE__ ,"Process32NEXTW", "FAIL", "PASS",msg);
//					return FALSE;
//				}
//				if(lstrcmp(Pro_Entry32.szExeFile,pro_exe)==0)
//				{
//					return TRUE;
//				}
//			}
//		}
//		else if(GetLastError()==ERROR_NO_MORE_FILES)
//		{
//			wresult(__FILE__,__LINE__ ,"Process32NEXTW", "PASS", "PASS","더이상 프로세스가 없습니다.");
//			return 2;
//		}	
//		else
//		{
//			strcpy(msg,GetErrorMessage("Process32FirstW Fail : ",GetLastError()));
//			wresult(__FILE__,__LINE__ ,"Process32NEXTW", "FAIL", "PASS",msg);		
//			return FALSE;		
//		}
//	}
//	else
//	{
//		wresult(__FILE__,__LINE__ ,"Process32NEXTW", "FAIL", "PASS","스냅샷 핸들을 얻어오지 못하였습니다.");	
//		return FALSE;
//	}
//}
//
//HANDLE Create_WriteFile(TCHAR* FileName,TCHAR* FileContents,char* FuncName)
//{
//	HANDLE hFile;
//	char msg[BUFSIZ]={0,};
//	DWORD result;
//	char temp[BUFSIZ]={0,};
//
//	hFile=CreateFileW(FileName,FILE_GENERIC_READ|FILE_GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
//
//	if(hFile==INVALID_HANDLE_VALUE)
//	{
//		strcpy(msg,GetErrorMessage("CreateFileW Fail : ",GetLastError()));
//		wresult(__FILE__,__LINE__ ,FuncName, "FAIL", "PASS",msg);	
//		return FALSE;
//	}
//
//	if(WriteFile(hFile,FileContents,lstrlen(FileContents)*sizeof(wchar_t),&result,NULL)==FALSE)
//	{
//		strcpy(msg,GetErrorMessage("WriteFile Fail : ",GetLastError()));
//		wresult(__FILE__,__LINE__ ,FuncName, "FAIL", "PASS",msg);
//		return FALSE;
//	}
//
//	return hFile;
//}


//HANDLE MyCreateTransaction()
//{
//	BOOL result = FALSE;
//	char msg[BUFSIZ];
//
//	HANDLE hTransaction = NULL;
//
//	hTransaction = CreateTransaction(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
//
//	if(INVALID_HANDLE_VALUE == hTransaction){ //파일 열기 실패
//		sprintf(msg, GetErrorMessage("CreateTransaction 실패 : ", GetLastError()));
//		wresult(__FILE__,__LINE__ , __FUNCTION__, msg, "CreateTransaction 성공", msg);
//
//		return INVALID_HANDLE_VALUE;
//	}
//
//	return hTransaction;
//
//}
//
//HANDLE MyCreateFile(const wchar_t *fileName)
//{
//	BOOL result = FALSE;
//	char msg[BUFSIZ];
//
//	HANDLE hFile = NULL;
//
//
//	hFile = CreateFileW(fileName, GENERIC_READ | GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//
//	if(hFile == INVALID_HANDLE_VALUE){ //파일 열기 실패
//		sprintf(msg, GetErrorMessage("파일 열기 실패 : ", GetLastError()));
//		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile 성공", msg);
//
//		return FALSE;
//	}
//	
//	return hFile;
//
//}
//
//HANDLE MyCreateFileA(const char *fileName)
//{
//	BOOL result = FALSE;
//	char msg[BUFSIZ];
//
//	HANDLE hFile = NULL;
//
//
//	hFile = CreateFileA(fileName, GENERIC_READ | GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//
//	if(hFile == INVALID_HANDLE_VALUE){ //파일 열기 실패
//		sprintf(msg, GetErrorMessage("파일 열기 실패 : ", GetLastError()));
//		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile 성공", msg);
//
//		return FALSE;
//	}
//	
//	return hFile;
//}
//
//HANDLE MyCreateFileOverlapped(const wchar_t *fileName)
//{
//	BOOL result = FALSE;
//	char msg[BUFSIZ];
//
//	HANDLE hFile = NULL;
//
//
//	hFile = CreateFileW(fileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING, NULL);
//
//	if(hFile == INVALID_HANDLE_VALUE){ //파일 열기 실패
//		sprintf(msg, GetErrorMessage("파일 열기 실패 : ", GetLastError()));
//		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "CreateFile 성공", msg);
//
//		return FALSE;
//	}
//	
//	return hFile;
//
//}
//
//BOOL MyCreateManifestFile(const wchar_t *fileName)
//{
//	BOOL result = TRUE;
//	char msg[BUFSIZ];
//	HANDLE hFile = NULL;
//	const char *Data = "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\"?>\
//						<assembly xmlns=\"urn:schemas-microsoft-com:asm.v1\" manifestVersion=\"1.0\">\
//						</assembly>";
//
//	if(FALSE == (hFile = MyCreateFile(fileName))){
//
//		return FALSE;
//	}
//	result = WriteFile(hFile, Data, strlen(Data) * sizeof(char), NULL, NULL);
//
//	if(!result){
//		sprintf(msg, GetErrorMessage("WriteFile 실패 : ", GetLastError()));
//		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "WriteFile 성공", msg);
//
//		CloseHandle(hFile);
//
//		return FALSE;
//	}
//
//	CloseHandle(hFile);
//
//	return result;
//	
//}
//
//BOOL MyCreateManifestFileA(const char *fileName)
//{
//	BOOL result = TRUE;
//	char msg[BUFSIZ];
//	HANDLE hFile = NULL;
//	const char *Data = "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\"?>\
//						<assembly xmlns=\"urn:schemas-microsoft-com:asm.v1\" manifestVersion=\"1.0\">\
//						</assembly>";
//
//	if(FALSE == (hFile = MyCreateFileA(fileName))){
//
//		return FALSE;
//	}
//	result = WriteFile(hFile, Data, strlen(Data) * sizeof(char), NULL, NULL);
//
//	if(!result){
//		sprintf(msg, GetErrorMessage("WriteFile 실패 : ", GetLastError()));
//		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "WriteFile 성공", msg);
//
//		CloseHandle(hFile);
//
//		return FALSE;
//	}
//
//	CloseHandle(hFile);
//
//	return result;
//	
//}
//
//ULONG ProcIDFromWnd(HWND hwnd)
//{
//	ULONG idProc;
//	GetWindowThreadProcessId(hwnd,&idProc);
//	return idProc;
//}
//
//HWND GetWindHandle(DWORD pid)
//{
//	HWND tempHwnd=FindWindow(NULL,NULL);
//	while(tempHwnd!=NULL)
//	{
//		if(GetParent(tempHwnd)==NULL)
//		{
//			if(pid==ProcIDFromWnd(tempHwnd))
//			{
//				return tempHwnd;
//			}
//		}
//		tempHwnd=GetWindow(tempHwnd,GW_HWNDNEXT);
//	}
//	return NULL;
//}
//
//BOOL WinRefresh(HWND hwnd)
//{
//
//	RECT ControlWindowRect;
//
//	ZeroMemory(&ControlWindowRect, sizeof(RECT));
//
//	if(GetClientRect(hwnd, &ControlWindowRect)==0)
//	{
//		return FALSE;
//	}
//
//	if(InvalidateRect(hwnd, &ControlWindowRect, TRUE)==0)
//	{
//		return FALSE;
//	}
//
//	return TRUE;
//}
//
//
//void SetPaintMessage(int nCount, POINT *point, const char *color, const char *shape, char *msg)
//{
//	char buf[BUFSIZ] = {0, }, temp[BUFSIZ]= {0, };
//
//	strcpy(buf, "좌표 : ");
//	for(int i=0; i<nCount; i++){
//		sprintf(temp, "(%d, %d) ", point[i].x, point[i].y);
//		strcat(buf, temp);
//	}
//	sprintf(temp, "\n색상 : %s\n", color);
//	strcat(buf, temp);
//	sprintf(temp, "모양 : %s", shape);
//	strcat(buf, temp);
//
//	//printf("%s", buf);
//
//	strcpy(msg, buf);
//	
//	return;
//}