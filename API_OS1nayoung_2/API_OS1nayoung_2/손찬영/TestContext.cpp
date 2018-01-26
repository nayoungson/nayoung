#include "TestContext.h"

/**
* BOOL ZombifyActCtx(HANDLE hActCtx)
* ������ Ȱ��ȭ ���ؽ�Ʈ�� ��Ȱ��ȭ������ �Ҵ��� �������� ����
* @author : ������  
*
* @param  hActCtx Ȱ��ȭ���ؽ�Ʈ �ڵ�
* @return ���ؽ�Ʈ ����ȭ ����/���� ����
*/
BOOL test_ZombifyActCtx()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	ACTCTXA ActCtx = {sizeof(ActCtx)};
	ActCtx.lpSource = "������\\TestContext.manifest";
	HANDLE hCtx;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(MyCreateManifestFileA(ActCtx.lpSource))){

		if(!DeleteFileA(ActCtx.lpSource)){
			#ifdef OQADBGPRINT
			puts(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
			#endif
		}

		return FALSE;

	}

	if(!PathFileExistsA(ActCtx.lpSource)){
		#ifdef OQADBGPRINT
		printf("%s �Ŵ��佺Ʈ������ �ʿ��մϴ�.\n", ActCtx.lpSource);
		#endif

		wresult(__FILE__,__LINE__ ,__FUNCTION__, "���� ����", "���� ����", "������\\TestContext.manifest ���� ����");

		return FALSE;
	}

	if(INVALID_HANDLE_VALUE == (hCtx = CreateActCtxA(&ActCtx))){

		#ifdef OQADBGPRINT
		printf("CreateActCtxA ����\n");
		#endif
		
		printf("����..\n");
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "CreateActCtxA ����", "CreateActCtxA ����", "CreateActCtxA ����");


		if(!DeleteFileA(ActCtx.lpSource)){
			#ifdef OQADBGPRINT
			puts(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
			#endif
		}

		return FALSE;
	}


	result = ZombifyActCtx(hCtx);
	if(result){
		sprintf(msg, "ZombifyActCtx ����");
		strcpy(buf, "ZombifyActCtx ����");

	}else{

		sprintf(msg, GetErrorMessage("ZombifyActCtx ���� : ", GetLastError()));
		strcpy(buf, "ZombifyActCtx ����");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "ZombifyActCtx ����", msg);

	ReleaseActCtx(hCtx);

	if(!DeleteFileA(ActCtx.lpSource)){
		#ifdef OQADBGPRINT
		puts(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
		#endif
	}


	return result;
}


/**
* void AddRefActCtx(HANDLE hActCtx)
* ������ Ȱ�� ���ؽ�Ʈ�� ���� ī��Ʈ�� ������Ų��.
* @author : ������  
*
* @param  hActCtx Ȱ��ȭ���ؽ�Ʈ �ڵ�
* @return ����
*/
BOOL test_AddRefActCtx()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	ACTCTXA ActCtx = {sizeof(ActCtx)};
	ActCtx.lpSource = "������\\TestContext.manifest";
	HANDLE hCtx;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* ���� ManifestFiled�� �����Ѵ� */
	if(!(MyCreateManifestFileA(ActCtx.lpSource))){

		if(!DeleteFileA(ActCtx.lpSource)){
			#ifdef OQADBGPRINT
			puts(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
			#endif
		}

		return FALSE;

	}

	if(!PathFileExistsA(ActCtx.lpSource)){
		#ifdef OQADBGPRINT
		printf("%s �Ŵ��佺Ʈ������ �ʿ��մϴ�.\n", ActCtx.lpSource);
		#endif

		wresult(__FILE__,__LINE__ ,__FUNCTION__, "���� ����", "���� ����", "������\\TestContext.manifest ���� ����");

		return FALSE;
	}

	/* Ȱ��ȭ ���ؽ�Ʈ�� �����Ѵ� */
	if(INVALID_HANDLE_VALUE == (hCtx = CreateActCtxA(&ActCtx))){
		#ifdef OQADBGPRINT
		printf("CreateActCtxA ����\n");
		#endif
		wresult(__FILE__,__LINE__ ,__FUNCTION__, "CreateActCtxA ����", "CreateActCtxA ����", "CreateActCtxA ����");

		if(!DeleteFileA(ActCtx.lpSource)){ 
			#ifdef OQADBGPRINT
			puts(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
			#endif
		}

		return FALSE;
	}

	__try  
	{  
		AddRefActCtx(hCtx);

		sprintf(msg, "AddRefActCtx ����");
		strcpy(buf, "AddRefActCtx ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "AddRefActCtx ����", msg);

		ReleaseActCtx(hCtx);

		if(!DeleteFileA(ActCtx.lpSource)){
			#ifdef OQADBGPRINT
			puts(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
			#endif
		}
	}  
	__except(EXCEPTION_EXECUTE_HANDLER)  
	{  
		sprintf(msg, GetErrorMessage("AddRefActCtx ���� : ", GetLastError()));
		strcpy(buf, "AddRefActCtx ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "AddRefActCtx ����", msg);

		ReleaseActCtx(hCtx);

		if(!DeleteFileA(ActCtx.lpSource)){
			#ifdef OQADBGPRINT
			puts(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
			#endif
		}

		return FALSE;
    }  

	

	return result;
}

/**
* HANDLE CreateActCtxA(PACTCTX pActCtx)
* Ȱ��ȭ ���ؽ�Ʈ�� �����Ѵ�.
* @author : ������  
*
* @param  hActCtx Ȱ��ȭ���ؽ�Ʈ����ü�� ������
* @return Ȱ��ȭ ���ؽ�Ʈ�� ���� �ڵ� �Ǵ� INVALID_HANDLE_VALUE
*/
BOOL test_CreateActCtxA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	ACTCTXA ActCtx = {sizeof(ActCtx)};
	ActCtx.lpSource = "������\\TestContext.manifest";
	HANDLE hCtx;
	ULONG_PTR cookie = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if(!(MyCreateManifestFileA(ActCtx.lpSource))){

		if(!DeleteFileA(ActCtx.lpSource)){
			#ifdef OQADBGPRINT
			puts(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
			#endif
		}

		return FALSE;

	}

	if(!PathFileExistsA(ActCtx.lpSource)){
		#ifdef OQADBGPRINT
		printf("%s �Ŵ��佺Ʈ������ �ʿ��մϴ�.\n", ActCtx.lpSource);
		#endif

		wresult(__FILE__,__LINE__ ,__FUNCTION__, "���� ����", "���� ����", "������\\TestContext.manifest ���� ����");

		return FALSE;
	}

	/* AcCtx�� �����Ѵ� */
	hCtx = CreateActCtxA(&ActCtx);
	
	/* ActCtx�� �����Ǿ�� Activate�� �� �ִٰ� �����ϰ� �׽�Ʈ�Ѵ�. */
	if(INVALID_HANDLE_VALUE != hCtx && ActivateActCtx(hCtx, &cookie)){
		sprintf(msg, "CreateActCtx ���� : hCtx = %d", hCtx);
		strcpy(buf, "CreateActCtx ����");

	}else{

		sprintf(msg, GetErrorMessage("CreateActCtx ���� : ", GetLastError()));
		strcpy(buf, "CreateActCtx ����");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateActCtx ����", msg);

	ReleaseActCtx(hCtx);

	if(!DeleteFileA(ActCtx.lpSource)){
			#ifdef OQADBGPRINT
			puts(GetErrorMessage("DeleteFileW ���� : ", GetLastError()));
			#endif
		}

	return result;

}

/**
* HANDLE CopyContext(PCONTEXT Destination, DWORD ContextFlags, PCONTEXT Source)
* �ҽ� ���ؽ�Ʈ ���� (XState ����)�� �ʱ�ȭ �� ��� ���ؽ�Ʈ ������ �����Ѵ�.
* @author : ������  
*
* @param  Destination Source ���� ���� �� ���ؽ�Ʈ���޴� CONTEXT ����ü�� ���� ������
* @param  ContextFlags ��� ���� �� Source CONTEXT ������ �κ��� �����ϴ� �÷���
* @param  Source ���μ��� ���ؽ�Ʈ �����͸� ���� �� CONTEXT ����ü�� ������
* @return ���� ���� �� TRUE �� �� FALSE
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
		sprintf(msg, GetErrorMessage("InitializeContext ���� : ", GetLastError()));
		strcpy(buf, "InitializeContext ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "InitializeContext ����", msg);

		return FALSE;
	}

	//ContextFlags = CONTEXT_ALL;
	if(!InitializeContext(Buffer[1], ContextFlags, &pSource, &ContextLength)){
		sprintf(msg, GetErrorMessage("InitializeContext ���� : ", GetLastError()));
		strcpy(buf, "InitializeCo4ntext ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "InitializeContext ����", msg);

		return FALSE;
	}

	
	//Buffer[0]->ContextFlags += 1, Buffer[1]->ContextFlags;
	//Buffer[1]->ExtendedRegisters = 0;
	/* Buffer[1]�� Buffer[0] ���ؽ�Ʈ�� �����Ѵ�. */
	//printf("���� �� Buffer[0] = %d, Buffer[1] = %d\n", Buffer[0]->Eax, Buffer[1]->Eax);
	result = CopyContext(Buffer[1], ContextFlags, Buffer[0]);
	//printf("���� �� Buffer[0] = %d, Buffer[1] = %d\n", Buffer[0]->Eax, Buffer[1]->Eax);
	if(result){
		sprintf(msg, "CopyContext ���� : Buffer[0]->ContextFlags = %d\nBuffer[1]->ContextFlags = %d", Buffer[0]->ContextFlags, Buffer[1]->ContextFlags);
		strcpy(buf, "CopyContext ����");

	}else{
		sprintf(msg, GetErrorMessage("CopyContext ���� : ", GetLastError()));
		strcpy(buf, "CopyContext ����");

		result = FALSE;
	}

	free(Buffer[0]);
	free(Buffer[1]);

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CopyContext ����", msg);

	return result;
}

/**
* HANDLE InitializeContext(PVOID Buffer,  DWORD ContextFlags, PCONTEXT *Context, PWORD ContextLength)
* �ʿ��� ũ��� ������ ����Ͽ� ���� ������ CONTEXT ����ü�� �ʱ�ȭ�Ѵ�.
* @author : ������  
*
* @param  Buffer CONTEXT ����ü �� �ʱ�ȭ �� ���۸� ����Ű�� ������
* @param  ContextFlags Context ����ü�� ��� �κ��� �ʱ�ȭ�� ���� ��Ÿ���� ��
* @param  Context ���� ������ �ʱ�ȭ �� CONTEXT ����ü�� �ּҸ� �����ϴ� ������ ���� ������
* @param  ContextLength Buffer�� ����Ű�� ������ ���̸� ����Ʈ ������ ����
* @return ����/���� ����
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

	/* ContextFlags������ Buffer->ContextFlags�� �ʱ�ȭ �� ���� Ȯ���Ѵ� */
	if(result && (ContextFlags == Buffer->ContextFlags)){
		sprintf(msg, "InitializeContext ���� : Buffer->ContextFlags = %d", Buffer->ContextFlags);
		strcpy(buf, "InitializeContext ����");
	}else{
		sprintf(msg, GetErrorMessage("InitializeContext ���� : ", GetLastError()));
		strcpy(buf, "InitializeContext ����");

		result = FALSE;
	}

	free(Buffer);

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "InitializeContext ����", msg);

	return result;
}