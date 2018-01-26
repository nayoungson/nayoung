#include "TestSemaphore.h"

/**
* HANDLE WINAPI OpenSemaphore(
  _In_ DWORD   dwDesiredAccess,
  _In_ BOOL    bInheritHandle,
  _In_ LPCTSTR lpName
);
* ������ ���� �������� ��ü�� ����.
* @author : ������  
*
* @param  dwDesiredAccess semaphore ��ü�� ���� �׼���
* @param  bInheritHandle �� ���� TRUE�̸�, �� ���μ������� ������ ���μ����� �ڵ��� ����Ѵ�.
* @param  lpName ������ ���������� �̸�
* @return �����ϸ� ��ȯ ���� �������� ��ü�� �ڵ�, �����ϸ� NULL
*/
BOOL test_OpenSemaphoreW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hSemaphore = NULL, hSemaphoreCreate = NULL;
	LONG lInitialCount = 10, lMaximumCount = 10;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* Semaphore�� ���� ���·� open �� �����ؾ� �� */
	if(OpenSemaphoreW(SEMAPHORE_ALL_ACCESS | SEMAPHORE_MODIFY_STATE, FALSE, L"test_OpenSemaphoreW")){
		sprintf(msg, "OpenSemaphoreW ���� : Semaphore�� ���� ���·� open �� �����ؾ� ��");
		strcpy(buf, "OpenSemaphoreW ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenSemaphoreW ����", msg);

		return FALSE;
	}

	/* Semaphore ���� ���� �� �׽�Ʈ �ߴ� */
	if(!(hSemaphoreCreate = CreateSemaphoreExW(NULL, lInitialCount, lMaximumCount, L"test_OpenSemaphoreW", 0, NULL))){
		sprintf(msg, GetErrorMessage("CreateSemaphoreExW ���� : ", GetLastError()));
		strcpy(buf, "CreateSemaphoreExW ����");;

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateSemaphoreExW ����", msg);

		return FALSE;
	}

	/* Semaphore ���� �� Open �� �����ؾ� �� */
	hSemaphore = OpenSemaphoreW(SEMAPHORE_ALL_ACCESS | SEMAPHORE_MODIFY_STATE, FALSE, L"test_OpenSemaphoreW");
	if(hSemaphore == NULL){
		strcpy(msg, GetErrorMessage("OpenSemaphoreW ���� : ", GetLastError()));
		strcpy(buf, "OpenSemaphoreW ����");

		result = FALSE;
	}else{
		sprintf(msg, "OpenSemaphoreW ���� : hSemaphoreCreate = %d\nhSemaphore = %d", hSemaphoreCreate, hSemaphore);
		strcpy(buf, "OpenSemaphoreW ����");
	}
	
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenSemaphoreW ����", msg);

	CloseHandle(hSemaphore);
	CloseHandle(hSemaphoreCreate);

	return result;
}


/**
* HANDLE WINAPI CreateSemaphoreEx(
  _In_opt_   LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
  _In_       LONG                  lInitialCount,
  _In_       LONG                  lMaximumCount,
  _In_opt_   LPCTSTR               lpName,
  _Reserved_ DWORD                 dwFlags,
  _In_       DWORD                 dwDesiredAccess
);
* ���� �Ǵ� ������ ���� �������� ��ü�� ����ų� ����.
* @author : ������  
*
* @param  lpSemaphoreAttributes SECURITY_ATTRIBUTES ����ü�� ���� ������
* @param  lInitialCount �������� ��ü�� �ʱ� ����.  �� ���� 0���� ũ�ų� ���� lMaximumCount ���� �۰ų� ���ƾ� ��.
* @param  lMaximumCount �������� ��ü�� �ִ� ����
* @param  lpName �������� ��ü�� �̸��� �����ϴ� �� ���ڷ� ������ ���ڿ��� ���� ������
* @param  dwFlags ����
* @param  dwDesiredAccess semaphore ��ü�� ���� �׼��� ����ũ
* @return �����ϸ� ��ȯ ���� �������� ��ü�� �ڵ�, �����ϸ� NULL
*/
BOOL test_CreateSemaphoreExW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hSemaphore = NULL;
	LONG lInitialCount = 1, lMaximumCount = 1;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	const int nThreadCount = 2;
	HANDLE hThread[nThreadCount];
	sharedVar = 0;

	/* 1�� �����常 ���� ������ ������� �����Ѵ�. */
	hSemaphore = CreateSemaphoreExW(NULL, lInitialCount, lMaximumCount, L"test_CreateSemaphoreExW", 0, NULL);

	/* 2���� �����带 �����ϰ� ���� hSemaphore �ڵ��� �ѱ��. */
	/* ������ ������ ���� �� �׽�Ʈ �ߴ� */
	if(!CreateMultipleThreads(hThread, ThreadFunc, hSemaphore, nThreadCount)){
		return FALSE;
	}

	/* ��� �����尡 ����� �� ���� busy-waiting�Ѵ�. */
	if(!BusyWaitingExitThread(hThread, 2)){
		return FALSE;
	}	

	/* ������� ���� �����尡 ������ for���� ������ �� �ڿ� �ٸ� �����尡 �����ڿ��� �����ϴ����� Ȯ���Ѵ�. */
	if(hSemaphore != NULL){ 
		if((sharedVar = BIG_INTEGER * 2)){
			sprintf(msg, "CreateSemaphoreExW ���� : hSemaphore = %d, sharedVar = %d", hSemaphore, sharedVar);
			strcpy(buf, "CreateSemaphoreExW ����");
		}else{
			sprintf(msg, "CreateSemaphoreExW ���� : sharedVar�� %d�� �ƴմϴ�.", BIG_INTEGER * 2);
			strcpy(buf, "CreateSemaphoreExW ����");
		}
		
	}else{
		strcpy(msg, GetErrorMessage("CreateSemaphoreExW ���� : ", GetLastError()));
		strcpy(buf, "CreateSemaphoreExW ����");

		result = FALSE;
		
	}
	
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateSemaphoreExW ����", msg);

	CloseHandle(hSemaphore);

	for(int i=0; i<nThreadCount; i++){
		CloseHandle(hThread[i]);
	}
	sharedVar = 0;

	return result;
}

/**
* HANDLE WINAPI CreateSemaphoreEx(
  _In_opt_   LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
  _In_       LONG                  lInitialCount,
  _In_       LONG                  lMaximumCount,
  _In_opt_   LPCTSTR               lpName,
  _Reserved_ DWORD                 dwFlags,
  _In_       DWORD                 dwDesiredAccess
);
* ���� �Ǵ� ������ ���� �������� ��ü�� ����ų� ����.
* @author : ������  
*
* @param  lpSemaphoreAttributes SECURITY_ATTRIBUTES ����ü�� ���� ������
* @param  lInitialCount �������� ��ü�� �ʱ� ����.  �� ���� 0���� ũ�ų� ���� lMaximumCount ���� �۰ų� ���ƾ� ��.
* @param  lMaximumCount �������� ��ü�� �ִ� ����
* @param  lpName �������� ��ü�� �̸��� �����ϴ� �� ���ڷ� ������ ���ڿ��� ���� ������
* @param  dwFlags ����
* @param  dwDesiredAccess semaphore ��ü�� ���� �׼��� ����ũ
* @return �����ϸ� ��ȯ ���� �������� ��ü�� �ڵ�, �����ϸ� NULL
*/
BOOL test_CreateSemaphoreExA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];	

	HANDLE hSemaphore = NULL;
	LONG lInitialCount = 1, lMaximumCount = 1;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	const int nThreadCount = 2;
	HANDLE hThread[nThreadCount];
	sharedVar = 0;

	/* 1�� �����常 ���� ������ ������� �����Ѵ�. */
	hSemaphore = CreateSemaphoreExA(NULL, lInitialCount, lMaximumCount, "test_CreateSemaphoreExA", 0, NULL);

	/* 2���� �����带 �����ϰ� ���� hSemaphore �ڵ��� �ѱ��. */
	/* ������ ������ ���� �� �׽�Ʈ �ߴ� */
	if(!CreateMultipleThreads(hThread, ThreadFunc, hSemaphore, nThreadCount)){
		return FALSE;
	}

	/* ��� �����尡 ����� �� ���� busy-waiting�Ѵ�. */
	if(!BusyWaitingExitThread(hThread, 2)){
		return FALSE;
	}	

	/* ������� ���� �����尡 ������ for���� ������ �� �ڿ� �ٸ� �����尡 �����ڿ��� �����ϴ����� Ȯ���Ѵ�. */
	if(hSemaphore != NULL){ 
		if((sharedVar = BIG_INTEGER * 2)){
			sprintf(msg, "CreateSemaphoreExA ���� : hSemaphore = %d, sharedVar = %d", hSemaphore, sharedVar);
			strcpy(buf, "CreateSemaphoreExA ����");
		}else{
			sprintf(msg, "CreateSemaphoreExA ���� : sharedVar�� %d�� �ƴմϴ�.", BIG_INTEGER * 2);
			strcpy(buf, "CreateSemaphoreExA ����");
		}
		
	}else{
		strcpy(msg, GetErrorMessage("CreateSemaphoreExA ���� : ", GetLastError()));
		strcpy(buf, "CreateSemaphoreExA ����");

		result = FALSE;
		
	}
	
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateSemaphoreExA ����", msg);

	CloseHandle(hSemaphore);

	for(int i=0; i<nThreadCount; i++){
		CloseHandle(hThread[i]);
	}
	sharedVar = 0;

	return result;
}