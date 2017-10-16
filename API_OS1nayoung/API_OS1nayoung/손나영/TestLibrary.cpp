#include "TestLibrary.h"
#include <Windows.h>
#include <TlHelp32.h>

// 0911

BOOL test_FreeLibraryAndExitThread(){
	HMODULE hModule;
	TCHAR Dir[MAX_PATH];
	char msg[BUFSIZ];
	DWORD exitCode;
	BOOL exitcode_result;

	DWORD result;
	int chk=0;
	char buf[BUFSIZ];

	printf("test_LoadLibraryW()\n");
	result=GetCurrentDirectoryW(MAX_PATH, Dir);

	printf("%S\n", Dir);

	if(result==NULL){ //GetCurrentDirectoryW 실패
		strcpy(msg, GetErrorMessage("GetCurrentDirectoryW() 실패 :", GetLastError()));

	}else{
		lstrcat(Dir,_T("\\손나영\\test.dll"));
		hModule=LoadLibraryW(Dir);
		if(hModule!=NULL){
			chk = 1;
			printf("sdfsfd \n");
			sprintf(msg, "LoadLibraryW() 성공");
			
			exitcode_result = GetExitCodeThread(hModule,&exitCode);

			printf("%d \n", exitcode_result);

			if(exitCode == STILL_ACTIVE){
				printf("진행중");
			}else{
				printf("진행 중 아님");
			}

			printf("%d\n", exitcode_result);

			FreeLibraryAndExitThread(hModule, exitcode_result);

			printf("22sdfsfd");
		}else{ //LoadLibraryW 실패
			strcpy(msg, GetErrorMessage("LoadLibraryW() 실패 :", GetLastError()));
		}
		sprintf(buf, "%d", chk);
		wresult(__FILE__,__LINE__ ,"LoadLibraryW", buf,"1", msg);
	}
	return true;
}

BOOL test_LoadLibraryW(void) //LoadLibraryW 완료
{
	HMODULE hModule;
	TCHAR Dir[MAX_PATH];
	char msg[BUFSIZ];

	DWORD result;
	int chk=0;
	char buf[BUFSIZ];

	printf("test_LoadLibraryW()\n");
	result=GetCurrentDirectoryW(MAX_PATH, Dir);

	if(result==NULL){ //GetCurrentDirectoryW 실패
		strcpy(msg, GetErrorMessage("GetCurrentDirectoryW() 실패 :", GetLastError()));

	}else{
		lstrcat(Dir,_T("\\부유정\\test.dll"));
		hModule=LoadLibraryW(Dir);
		if(hModule!=NULL){
			chk = 1;
			sprintf(msg, "LoadLibraryW() 성공");

		}else{ //LoadLibraryW 실패
			strcpy(msg, GetErrorMessage("LoadLibraryW() 실패 :", GetLastError()));
		}
		sprintf(buf, "%d", chk);
		wresult(__FILE__,__LINE__ ,"LoadLibraryW", buf,"1", msg);
	}
	return true;
}
