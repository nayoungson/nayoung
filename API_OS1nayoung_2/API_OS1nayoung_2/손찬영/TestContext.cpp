#include "TestContext.h"

/**
* BOOL ZombifyActCtx(HANDLE hActCtx)
* 지정된 활성화 컨텍스트를 비활성화하지만 할당을 해제하지 않음
* @author : 손찬영  
*
* @param  hActCtx 활성화컨텍스트 핸들
* @return 컨텍스트 좀비화 성공/실패 여부
*/
BOOL test_ZombifyActCtx()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	ACTCTXA ActCtx = {sizeof(ActCtx)};
	ActCtx.lpSource = "손찬영\\TestContext.manifest";
	HANDLE hCtx;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(MyCreateManifestFileA(ActCtx.lpSource))){

		if(!DeleteFileA(ActCtx.lpSource)){
			#ifdef OQADBGPRINT
			puts(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
			#endif
		}

		return FALSE;

	}

	if(!PathFileExistsA(ActCtx.lpSource)){
		#ifdef OQADBGPRINT
		printf("%s 매니페스트파일이 필요합니다.\n", ActCtx.lpSource);
		#endif

		wresult(__FILE__,__LINE__ ,__FUNCTION__, "파일 없음", "파일 있음", "손찬영\\TestContext.manifest 파일 없음");

		return FALSE;
	}

	if(INVALID_HANDLE_VALUE == (hCtx = CreateActCtxA(&ActCtx))){

		#ifdef OQADBGPRINT
		printf("CreateActCtxA 실패\n");
		#endif
		
		printf("실패..\n");
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "CreateActCtxA 실패", "CreateActCtxA 성공", "CreateActCtxA 실패");


		if(!DeleteFileA(ActCtx.lpSource)){
			#ifdef OQADBGPRINT
			puts(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
			#endif
		}

		return FALSE;
	}


	result = ZombifyActCtx(hCtx);
	if(result){
		sprintf(msg, "ZombifyActCtx 성공");
		strcpy(buf, "ZombifyActCtx 성공");

	}else{

		sprintf(msg, GetErrorMessage("ZombifyActCtx 실패 : ", GetLastError()));
		strcpy(buf, "ZombifyActCtx 실패");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ZombifyActCtx 성공", msg);

	ReleaseActCtx(hCtx);

	if(!DeleteFileA(ActCtx.lpSource)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
		#endif
	}


	return result;
}


/**
* void AddRefActCtx(HANDLE hActCtx)
* 지정된 활성 콘텍스트의 참조 카운트를 증가시킨다.
* @author : 손찬영  
*
* @param  hActCtx 활성화컨텍스트 핸들
* @return 없음
*/
BOOL test_AddRefActCtx()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	ACTCTXA ActCtx = {sizeof(ActCtx)};
	ActCtx.lpSource = "손찬영\\TestContext.manifest";
	HANDLE hCtx;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* 더미 ManifestFiled을 생성한다 */
	if(!(MyCreateManifestFileA(ActCtx.lpSource))){

		if(!DeleteFileA(ActCtx.lpSource)){
			#ifdef OQADBGPRINT
			puts(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
			#endif
		}

		return FALSE;

	}

	if(!PathFileExistsA(ActCtx.lpSource)){
		#ifdef OQADBGPRINT
		printf("%s 매니페스트파일이 필요합니다.\n", ActCtx.lpSource);
		#endif

		wresult(__FILE__,__LINE__ ,__FUNCTION__, "파일 없음", "파일 있음", "손찬영\\TestContext.manifest 파일 없음");

		return FALSE;
	}

	/* 활성화 컨텍스트를 생성한다 */
	if(INVALID_HANDLE_VALUE == (hCtx = CreateActCtxA(&ActCtx))){
		#ifdef OQADBGPRINT
		printf("CreateActCtxA 실패\n");
		#endif
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "CreateActCtxA 실패", "CreateActCtxA 성공", "CreateActCtxA 실패");

		if(!DeleteFileA(ActCtx.lpSource)){ 
			#ifdef OQADBGPRINT
			puts(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
			#endif
		}

		return FALSE;
	}

	__try  
	{  
		AddRefActCtx(hCtx);

		sprintf(msg, "AddRefActCtx 성공");
		strcpy(buf, "AddRefActCtx 성공");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "AddRefActCtx 성공", msg);

		ReleaseActCtx(hCtx);

		if(!DeleteFileA(ActCtx.lpSource)){
			#ifdef OQADBGPRINT
			puts(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
			#endif
		}
	}  
	__except(EXCEPTION_EXECUTE_HANDLER)  
	{  
		sprintf(msg, GetErrorMessage("AddRefActCtx 실패 : ", GetLastError()));
		strcpy(buf, "AddRefActCtx 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "AddRefActCtx 성공", msg);

		ReleaseActCtx(hCtx);

		if(!DeleteFileA(ActCtx.lpSource)){
			#ifdef OQADBGPRINT
			puts(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
			#endif
		}

		return FALSE;
    }  

	

	return result;
}

/**
* HANDLE CreateActCtxA(PACTCTX pActCtx)
* 활성화 컨텍스트를 생성한다.
* @author : 손찬영  
*
* @param  hActCtx 활성화컨텍스트구조체의 포인터
* @return 활성화 컨텍스트에 대한 핸들 또는 INVALID_HANDLE_VALUE
*/
BOOL test_CreateActCtxA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	ACTCTXA ActCtx = {sizeof(ActCtx)};
	ActCtx.lpSource = "손찬영\\TestContext.manifest";
	HANDLE hCtx;
	ULONG_PTR cookie = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(MyCreateManifestFileA(ActCtx.lpSource))){

		if(!DeleteFileA(ActCtx.lpSource)){
			#ifdef OQADBGPRINT
			puts(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
			#endif
		}

		return FALSE;

	}

	if(!PathFileExistsA(ActCtx.lpSource)){
		#ifdef OQADBGPRINT
		printf("%s 매니페스트파일이 필요합니다.\n", ActCtx.lpSource);
		#endif

		wresult(__FILE__,__LINE__ ,__FUNCTION__, "파일 없음", "파일 있음", "손찬영\\TestContext.manifest 파일 없음");

		return FALSE;
	}

	/* AcCtx를 생성한다 */
	hCtx = CreateActCtxA(&ActCtx);
	
	/* ActCtx가 생성되어야 Activate할 수 있다고 가정하고 테스트한다. */
	if(INVALID_HANDLE_VALUE != hCtx && ActivateActCtx(hCtx, &cookie)){
		sprintf(msg, "CreateActCtx 성공 : hCtx = %d", hCtx);
		strcpy(buf, "CreateActCtx 성공");

	}else{

		sprintf(msg, GetErrorMessage("CreateActCtx 실패 : ", GetLastError()));
		strcpy(buf, "CreateActCtx 실패");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateActCtx 성공", msg);

	ReleaseActCtx(hCtx);

	if(!DeleteFileA(ActCtx.lpSource)){
			#ifdef OQADBGPRINT
			puts(GetErrorMessage("DeleteFileW 실패 : ", GetLastError()));
			#endif
		}

	return result;

}

/**
* HANDLE CopyContext(PCONTEXT Destination, DWORD ContextFlags, PCONTEXT Source)
* 소스 컨텍스트 구조 (XState 포함)를 초기화 된 대상 컨텍스트 구조에 복사한다.
* @author : 손찬영  
*
* @param  Destination Source 에서 복사 한 컨텍스트를받는 CONTEXT 구조체에 대한 포인터
* @param  ContextFlags 대상에 복사 될 Source CONTEXT 구조의 부분을 지정하는 플래그
* @param  Source 프로세서 컨텍스트 데이터를 복사 할 CONTEXT 구조체의 포인터
* @return 복사 성공 시 TRUE 그 외 FALSE
*/
BOOL test_CopyContext()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	CONTEXT Destination, Source, *Buffer[2];
	PCONTEXT pDestination = &Destination, pSource = &Source;
	DWORD    ContextFlags = CONTEXT_ALL;	
	DWORD    ContextLength = 1024;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	Destination.ContextFlags = 0;

	InitializeContext(NULL, ContextFlags, &pDestination, &ContextLength);

	Buffer[0] = (CONTEXT *)malloc(sizeof(CONTEXT)*ContextLength);
	Buffer[1] = (CONTEXT *)malloc(sizeof(CONTEXT)*ContextLength);

	if(!InitializeContext(Buffer[0], ContextFlags, &pDestination, &ContextLength)){
		sprintf(msg, GetErrorMessage("InitializeContext 실패 : ", GetLastError()));
		strcpy(buf, "InitializeContext 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "InitializeContext 성공", msg);

		return FALSE;
	}

	//ContextFlags = CONTEXT_ALL;
	if(!InitializeContext(Buffer[1], ContextFlags, &pSource, &ContextLength)){
		sprintf(msg, GetErrorMessage("InitializeContext 실패 : ", GetLastError()));
		strcpy(buf, "InitializeCo4ntext 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "InitializeContext 성공", msg);

		return FALSE;
	}

	
	//Buffer[0]->ContextFlags += 1, Buffer[1]->ContextFlags;
	//Buffer[1]->ExtendedRegisters = 0;
	/* Buffer[1]에 Buffer[0] 컨텍스트를 복사한다. */
	//printf("복사 전 Buffer[0] = %d, Buffer[1] = %d\n", Buffer[0]->Eax, Buffer[1]->Eax);
	result = CopyContext(Buffer[1], ContextFlags, Buffer[0]);
	//printf("복사 후 Buffer[0] = %d, Buffer[1] = %d\n", Buffer[0]->Eax, Buffer[1]->Eax);
	if(result){
		sprintf(msg, "CopyContext 성공 : Buffer[0]->ContextFlags = %d\nBuffer[1]->ContextFlags = %d", Buffer[0]->ContextFlags, Buffer[1]->ContextFlags);
		strcpy(buf, "CopyContext 성공");

	}else{
		sprintf(msg, GetErrorMessage("CopyContext 실패 : ", GetLastError()));
		strcpy(buf, "CopyContext 실패");

		result = FALSE;
	}

	free(Buffer[0]);
	free(Buffer[1]);

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CopyContext 성공", msg);

	return result;
}

/**
* HANDLE InitializeContext(PVOID Buffer,  DWORD ContextFlags, PCONTEXT *Context, PWORD ContextLength)
* 필요한 크기와 정렬을 사용하여 버퍼 내부의 CONTEXT 구조체를 초기화한다.
* @author : 손찬영  
*
* @param  Buffer CONTEXT 구조체 를 초기화 할 버퍼를 가리키는 포인터
* @param  ContextFlags Context 구조체의 어느 부분을 초기화할 지를 나타내는 값
* @param  Context 버퍼 내에서 초기화 된 CONTEXT 구조체의 주소를 수신하는 변수에 대한 포인터
* @param  ContextLength Buffer가 가리키는 버퍼의 길이를 바이트 단위로 지정
* @return 성공/실패 여부
*/
BOOL test_InitializeContext()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	CONTEXT Context, *Buffer;
	PCONTEXT pContext = &Context;
	DWORD    ContextFlags = CONTEXT_ALL;	
	DWORD    ContextLength = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	InitializeContext(NULL, ContextFlags, &pContext, &ContextLength);
	Buffer = (CONTEXT *)malloc(sizeof(CONTEXT)*ContextLength);

	Buffer->ContextFlags = 0;
	result = InitializeContext(Buffer, ContextFlags, &pContext, &ContextLength);

	/* ContextFlags값으로 Buffer->ContextFlags가 초기화 된 것을 확인한다 */
	if(result && (ContextFlags == Buffer->ContextFlags)){
		sprintf(msg, "InitializeContext 성공 : Buffer->ContextFlags = %d", Buffer->ContextFlags);
		strcpy(buf, "InitializeContext 성공");
	}else{
		sprintf(msg, GetErrorMessage("InitializeContext 실패 : ", GetLastError()));
		strcpy(buf, "InitializeContext 실패");

		result = FALSE;
	}

	free(Buffer);

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "InitializeContext 성공", msg);

	return result;
}