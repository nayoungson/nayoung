#include "TestProcThreadAttribute.h"


/**
* BOOL WINAPI InitializeProcThreadAttributeList(
  _Out_opt_  LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList,
  _In_       DWORD                        dwAttributeCount,
  _Reserved_ DWORD                        dwFlags,
  _Inout_    PSIZE_T                      lpSize
);
* ���μ��� �� ������ ������ ���� ������ Ư�� ����� �ʱ�ȭ�Ѵ�.
* @author : ������  
*
* @param  lpAttributeList	�Ӽ�����Ʈ ������ ���� �Ӽ��� �����ϴ� �� �ʿ��� ���� ũ�⸦ �����Ϸ����� �Ű� ������ NULL�� ������ �� �ִ�.
* @param  dwAttributeCount	��Ͽ� �߰� �� �Ӽ��� ��
* @param  dwFlags			����
* @param  lpSize			pAttributeList�� NULL�� �ƴ� ����� �Ű� ������ �Է½� lpAttributeList ������ ũ�� (����Ʈ)�� ����
* @return					����/���� ����
*/
BOOL test_InitializeProcThreadAttributeList(void)
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	//UCHAR buffer[4096];  
	//LPPROC_THREAD_ATTRIBUTE_LIST attr = (LPPROC_THREAD_ATTRIBUTE_LIST) buffer; 
	LPPROC_THREAD_ATTRIBUTE_LIST attr;
	SIZE_T size = 0; 
	//ULONG policy = PROCESS_CREATION_MITIGATION_POLICY_WIN32K_SYSTEM_CALL_DISABLE_ALWAYS_ON; 

	GROUP_AFFINITY GrpAffinity = { 0 };
    //GrpAffinity.Mask = 1;


#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif

	/* size�� ��� ���� NULL�� �Լ��� ȣ���Ѵ�. */
	InitializeProcThreadAttributeList(NULL, 1, 0, &size);
	attr = (LPPROC_THREAD_ATTRIBUTE_LIST)  new UCHAR[size];

	/* �ʱ� ȭ �� ������Ʈ ���� �� �׽�Ʈ �ߴ� */
	if(UpdateProcThreadAttribute(attr, 0, PROC_THREAD_ATTRIBUTE_GROUP_AFFINITY, &GrpAffinity, sizeof(GrpAffinity), NULL, NULL)){
		sprintf(msg, "�ʱ�ȭ �� UpdateProcThreadAttribute ����");
		strcpy(buf, "UpdateProcThreadAttribute ����");

		wresult(__FILE__,__LINE__, __FUNCTION__, buf, "UpdateProcThreadAttribute ����", msg);

		return FALSE;
	}
	
	/* �ʱ�ȭ ��, ������Ʈ ���� �� �ʱ�ȭ ������ ������ �Ǵ��Ѵ�. */
	if(InitializeProcThreadAttributeList(attr, 1, 0, &size)){

		if(UpdateProcThreadAttribute(attr , 0, PROC_THREAD_ATTRIBUTE_GROUP_AFFINITY, &GrpAffinity, sizeof(GrpAffinity), NULL, NULL)){
			strcpy(buf, "InitializeProcThreadAttributeList ����");
			strcpy(msg, buf);
		
		/* �ʱ�ȭ �� ������Ʈ ���� */
		}else{
			sprintf(msg, GetErrorMessage("�ʱ�ȭ �� UpdateProcThreadAttribute ���� : ", GetLastError()));
			strcpy(buf, "UpdateProcThreadAttribute ����");

			result = FALSE;
		}


	}else{
		sprintf(msg, GetErrorMessage("InitializeProcThreadAttributeList ���� : ", GetLastError()));
		strcpy(buf, "InitializeProcThreadAttributeList ����");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "InitializeProcThreadAttributeList ����", msg);

	return result;
}


/**
* BOOL WINAPI UpdateProcThreadAttribute(
  _Inout_   LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList,
  _In_      DWORD                        dwFlags,
  _In_      DWORD_PTR                    Attribute,
  _In_      PVOID                        lpValue,
  _In_      SIZE_T                       cbSize,
  _Out_opt_ PVOID                        lpPreviousValue,
  _In_opt_  PSIZE_T                      lpReturnSize
);
* ���μ��� �� ������ ������ ���� �Ӽ� ��Ͽ��� ������ �Ӽ��� ������Ʈ�Ѵ�.
* @author : ������  
*
* @param  lpAttributeList	InitializeProcThreadAttributeList �Լ��� ���� �ۼ��� �Ӽ� ��Ͽ� ���� ������
* @param  dwFlags			����
* @param  Attribute			�Ӽ�����Ʈ�� �����ϴ� �Ӽ� Ű. PROC_THREAD_ATTRIBUTE_GROUP_AFFINITY ��
* @param  lpValue			�Ӽ� ���� ����Ű�� ������.
* @param  cbSize			lpValue �Ű� ������ ������ �Ӽ� ���� ũ��
* @param  lpPreviousValue	����		
* @param  lpReturnSize		����
* @return					����/���� ����
*/
BOOL test_UpdateProcThreadAttribute(void)
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	UCHAR buffer[4096];  
	LPPROC_THREAD_ATTRIBUTE_LIST attr = (LPPROC_THREAD_ATTRIBUTE_LIST) buffer; 
	SIZE_T size = 0; 
	GROUP_AFFINITY GrpAffinity = { 0 };
    GrpAffinity.Mask = 1;


#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif

	/* size�� ��� ���� NULL�� �Լ��� ȣ���Ѵ�. */
	InitializeProcThreadAttributeList(NULL, 1, 0, &size);

	attr = (LPPROC_THREAD_ATTRIBUTE_LIST)  new UCHAR[size];

	/* attr ����ü�� �ʱ�ȭ�Ѵ� */
	if(!InitializeProcThreadAttributeList(attr, 1, 0, &size)){
		sprintf(msg, GetErrorMessage("InitializeProcThreadAttributeList ���� : ", GetLastError()));
		strcpy(buf, "InitializeProcThreadAttributeList ����");

		wresult(__FILE__,__LINE__, __FUNCTION__, buf, "InitializeProcThreadAttributeList ����", msg);

		return FALSE;
	}
	
	if(UpdateProcThreadAttribute(attr , 0, PROC_THREAD_ATTRIBUTE_GROUP_AFFINITY, &GrpAffinity, sizeof(GrpAffinity), NULL, NULL)){ 
		strcpy(buf, "UpdateProcThreadAttribute ����");
		strcpy(msg, buf);

	}else{
		sprintf(msg, GetErrorMessage("UpdateProcThreadAttribute ���� : ", GetLastError()));
		strcpy(buf, "UpdateProcThreadAttribute ����");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "UpdateProcThreadAttribute ����", msg);

	return result;
}

/**
* VOID WINAPI DeleteProcThreadAttributeList(
  _Inout_ LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList
);
* ���μ��� �� ������ ������ ���� ������ �Ӽ� ����� �����Ѵ�.
* @author : ������  
*
* @param  lpAttributeList	�Ӽ�����Ʈ. �� ����� InitializeProcThreadAttributeList �Լ��� ���� ����
* @return					����
*/
BOOL test_DeleteProcThreadAttributeList(void)
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	
	DWORD errorCode = 0;

	UCHAR buffer[4096];  
	LPPROC_THREAD_ATTRIBUTE_LIST attr = (LPPROC_THREAD_ATTRIBUTE_LIST) buffer; 
	SIZE_T size = 0; 
	ULONG policy = PROCESS_CREATION_MITIGATION_POLICY_WIN32K_SYSTEM_CALL_DISABLE_ALWAYS_ON; 

	
#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif


	/* size�� ��� ���� NULL�� �Լ��� ȣ���Ѵ�. */
	InitializeProcThreadAttributeList(NULL, 1, 0, &size);
	attr = (LPPROC_THREAD_ATTRIBUTE_LIST)  new UCHAR[size];

	/* attr�� �ʱ�ȭ�Ѵ�. */
	if(!InitializeProcThreadAttributeList(attr, 1, 0, &size)){
		sprintf(msg, GetErrorMessage("InitializeProcThreadAttributeList ���� : ", GetLastError()));
		strcpy(buf, "InitializeProcThreadAttributeList ����");

		wresult(__FILE__,__LINE__, __FUNCTION__, buf, "InitializeProcThreadAttributeList ����", msg);

		return FALSE;
	}

	/* �ʱ�ȭ �� ������Ʈ �� �����ؾ� ��*/
	if(UpdateProcThreadAttribute(attr , 0, PROC_THREAD_ATTRIBUTE_MITIGATION_POLICY, &policy, sizeof(policy), NULL, NULL)){
		
		/* ���� �õ� */
		DeleteProcThreadAttributeList(attr);

		/* ���� �� ������Ʈ �����ϸ� ���� */
		if(!UpdateProcThreadAttribute(attr , 0, PROC_THREAD_ATTRIBUTE_MITIGATION_POLICY, &policy, sizeof(policy), NULL, NULL)){
			strcpy(buf, "DeleteProcThreadAttributeList ����");
			sprintf(msg, buf);

		/* ���� �� ������Ʈ �����ϸ� ���з� �����Ѵ� */
		}else{
			sprintf(msg, GetErrorMessage("DeleteProcThreadAttributeList ���� : ", GetLastError()));
			strcpy(buf, "DeleteProcThreadAttributeList ����");

			result = FALSE;
		}

	/* ���� ���� ������Ʈ �õ� �� �����ؾ� �� (�����ϸ� �׽�Ʈ �ߴ�) */
	}else{
		
		sprintf(msg, GetErrorMessage("UpdateProcThreadAttribute ���� : ", GetLastError()));
		strcpy(buf, "UpdateProcThreadAttribute ����");

		wresult(__FILE__,__LINE__, __FUNCTION__, buf, "UpdateProcThreadAttribute ����", msg);

		return FALSE;
	}

	wresult(__FILE__,__LINE__, __FUNCTION__, buf, "DeleteProcThreadAttributeList ����", msg);

	return result;
}