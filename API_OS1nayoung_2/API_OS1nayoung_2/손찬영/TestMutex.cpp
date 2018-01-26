#include "TestMutex.h"


/**
* HANDLE CreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCTSTR lpName)
* ���� �Ǵ� ������ ���� ���ؽ� ��ü�� ����ų� ����.
* @author : ������  
*
* @param  lpMutexAttributes SECURITY_ATTRIBUTES ����ü�� ���� ������
* @param  bInitialOwner �� ���� TRUE �̰� ȣ���ڰ� ���ؽ��� ���� ��� ȣ�� ������� ���ؽ� ��ü�� �ʱ� �������� ��´�.
* @param  lpName ���ؽ� ��ü�� �̸�
* @return ������ ���ؽ� ��ü�� ���� �ڵ�
*/
BOOL test_CreateMutexA(void)
{
	BOOL result = TRUE;	
	char msg[BUFSIZ], buf[BUFSIZ];

	HANDLE hMutex = NULL;
	LPSTR lpName = "test_CreateMutexW";

	const int nThreadCount = 2;
	HANDLE hThread[nThreadCount];
	
	sharedVar = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hMutex = CreateMutexA(NULL, FALSE, lpName);

	/* 2���� �����带 �����ϰ� ���� hMutex �ڵ��� �ѱ��. */
	/* ������ ������ ���� �� �׽�Ʈ �ߴ� */
	if(!CreateMultipleThreads(hThread, ThreadFunc, hMutex, nThreadCount)){
		return FALSE;
	}
	
	
	/* ��� �����尡 ����� �� ���� busy-waiting�Ѵ�. */
	if(!BusyWaitingExitThread(hThread, 2)){
		return FALSE;
	}

	/* ���ؽ��� ���� �����尡 ������ for���� ������ �� �ڿ� �ٸ� �����尡 �����ڿ��� �����ϴ����� Ȯ���Ѵ�. */
	if((NULL != hMutex)){
		if((sharedVar = BIG_INTEGER * 2)){
			sprintf(msg, "CreateMutexA ���� : hMutex = %d, sharedVar = %d", hMutex, sharedVar);
			strcpy(buf, "CreateMutexA ����");
		}else{
			sprintf(msg, "CreateMutexA ���� : sharedVar�� %d�� �ƴմϴ�.", BIG_INTEGER * 2);
			strcpy(buf, "CreateMutexA ����");
		}

	}else{ //���ؽ� ���� ����
		sprintf(msg, GetErrorMessage("CreateMutexA ���� : ", GetLastError()));
		strcpy(buf, "CreateMutexA ����");
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateMutexA ����", msg);

	CloseHandle(hMutex); //������ ���ؽ� ���� �� ����

	for(int i=0; i<nThreadCount; i++){
		CloseHandle(hThread[i]);
	}

	sharedVar = 0;

	return result;
}

/**
* HANDLE CreateMutexW(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCTSTR lpName)
* ���� �Ǵ� ������ ���� ���ؽ� ��ü�� ����ų� ����.
* @author : ������  
*
* @param  lpMutexAttributes SECURITY_ATTRIBUTES ����ü�� ���� ������
* @param  bInitialOwner �� ���� TRUE �̰� ȣ���ڰ� ���ؽ��� ���� ��� ȣ�� ������� ���ؽ� ��ü�� �ʱ� �������� ��´�.
* @param  lpName ���ؽ� ��ü�� �̸�
* @return ������ ���ؽ� ��ü�� ���� �ڵ�
*/
BOOL test_CreateMutexW(void)
{
	BOOL result = TRUE;	
	char msg[BUFSIZ], buf[BUFSIZ];

	HANDLE hMutex = NULL;
	LPWSTR lpName = L"test_CreateMutexA";

	const int nThreadCount = 2;
	HANDLE hThread[nThreadCount];
	
	sharedVar = 0;
	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hMutex = CreateMutexW(NULL, FALSE, lpName);

	/* 2���� �����带 �����ϰ� ���� hMutex �ڵ��� �ѱ��. */
	/* ������ ������ ���� �� �׽�Ʈ �ߴ� */
	if(!CreateMultipleThreads(hThread, ThreadFunc, hMutex, nThreadCount)){
		return FALSE;
	}
	
	
	/* ��� �����尡 ����� �� ���� busy-waiting�Ѵ�. */
	if(!BusyWaitingExitThread(hThread, 2)){
		return FALSE;
	}

	/* ���ؽ��� ���� �����尡 ������ for���� ������ �� �ڿ� �ٸ� �����尡 �����ڿ��� �����ϴ����� Ȯ���Ѵ�. */
	if((NULL != hMutex)){
		if((sharedVar = BIG_INTEGER * 2)){
			sprintf(msg, "CreateMutexW ���� : hMutex = %d, sharedVar = %d", hMutex, sharedVar);
			strcpy(buf, "CreateMutexW ����");
		}else{
			sprintf(msg, "CreateMutexW ���� : sharedVar�� %d�� �ƴմϴ�.", BIG_INTEGER * 2);
			strcpy(buf, "CreateMutexW ����");
		}

	}else{ //���ؽ� ���� ����
		sprintf(msg, GetErrorMessage("CreateMutexW ���� : ", GetLastError()));
		strcpy(buf, "CreateMutexW ����");
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateMutexW ����", msg);

	CloseHandle(hMutex); //������ ���ؽ� ���� �� ����

	for(int i=0; i<nThreadCount; i++){
		CloseHandle(hThread[i]);
	}

	sharedVar = 0;

	return result;
}

/**
* HANDLE OpenMutexW(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCTSTR lpName)
* ������ ���� ���ؽ� ��ü�� ����.
* @author : ������  
*
* @param  dwDesiredAccess ���ؽ� ��ü�� ���� �׼���
* @param  bInheritHandle �� ���� TRUE �̸�, ���μ������� ���� �� ���μ����� �ڵ��� ����Ѵ�.
* @param  lpName ������ ���ؽ��� �̸�
* @return ���ؽ� ��ü�� �ڵ�
*/
BOOL test_OpenMutexW(void)
{
	LPSECURITY_ATTRIBUTES lpMutexAttributes = NULL;
	BOOL bInitialOwner = FALSE;
	LPCTSTR lpName = L"test_OpenMutexW";
	HANDLE hMutex = 0;
	HANDLE hMutexCreate = 0;
	BOOL result = TRUE;	

	char msg[BUFSIZ];
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* Mutex ���� ���·� Open �õ� �� �����ؾ� �� */
	if(OpenMutexW(MUTEX_ALL_ACCESS, FALSE, lpName)){
		sprintf(msg, "OpenMutexW ���� : Mutex�� ���� ���·� open �� �����ؾ� ��");
		strcpy(buf, "OpenMutexW ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenMutexW ����", msg);

		return FALSE;
	}
	
	
	/* Mutex ���� ���� �� �׽�Ʈ �ߴ� */
	if(!(hMutexCreate = CreateMutexW(NULL, FALSE, lpName))){
		sprintf(msg, GetErrorMessage("CreateMutexW ���� : ", GetLastError()));
		strcpy(buf, "CreateMutexW ����");;

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateMutexW ����", msg);

		return FALSE;
	}

	/* Mutex ���� �� Open �� �����ؾ� �� */
	hMutex = OpenMutexW(MUTEX_ALL_ACCESS, FALSE, lpName);
	if(NULL != hMutex){ 
		sprintf(msg, "OpenMutexW ���� : hMutex = %d", hMutex);
		strcpy(buf, "OpenMutexW ����");

	}else{ //���ؽ� ���� ����
		sprintf(msg, GetErrorMessage("OpenMutexW ���� : ", GetLastError()));
		strcpy(buf, "OpenMutexW ����");

		result = FALSE;
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenMutexW ����", msg);

	CloseHandle(hMutex); //������ ���ؽ� ���� �� ����
	CloseHandle(hMutexCreate);

	return result;
}


/**
* HANDLE OpenMutexA(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCTSTR lpName)
* ������ ���� ���ؽ� ��ü�� ����.
* @author : ������  
*
* @param  dwDesiredAccess ���ؽ� ��ü�� ���� �׼���
* @param  bInheritHandle �� ���� TRUE �̸�, ���μ������� ���� �� ���μ����� �ڵ��� ����Ѵ�.
* @param  lpName ������ ���ؽ��� �̸�
* @return ���ؽ� ��ü�� �ڵ�
*/
BOOL test_OpenMutexA()
{
	LPSECURITY_ATTRIBUTES lpMutexAttributes = NULL;
	BOOL bInitialOwner = FALSE;
	LPSTR lpName = "test_OpenMutexA";
	HANDLE hMutex = 0;
	HANDLE hMutexCreate = 0;
	BOOL result = TRUE;	

	char msg[BUFSIZ];
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* Mutex ���� ���·� Open �õ� �� �����ؾ� �� */
	if(OpenMutexA(MUTEX_ALL_ACCESS, FALSE, lpName)){
		sprintf(msg, "OpenMutexW ���� : Mutex�� ���� ���·� open �� �����ؾ� ��");
		strcpy(buf, "OpenMutexW ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenMutexW ����", msg);

		return FALSE;
	}
	
	
	/* Mutex ���� ���� �� �׽�Ʈ �ߴ� */
	if(!(hMutexCreate = CreateMutexA(NULL, FALSE, lpName))){
		sprintf(msg, GetErrorMessage("CreateMutexA ���� : ", GetLastError()));
		strcpy(buf, "CreateMutexA ����");;

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateMutexA ����", msg);

		return FALSE;
	}

	/* Mutex ���� �� Open �� �����ؾ� �� */
	hMutex = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, lpName);
	if(NULL != hMutex){ 
		sprintf(msg, "OpenMutexA ���� : hMutex = %d", hMutex);
		strcpy(buf, "OpenMutexA ����");

	}else{ //���ؽ� ���� ����
		sprintf(msg, GetErrorMessage("OpenMutexA ���� : ", GetLastError()));
		strcpy(buf, "OpenMutexA ����");

		result = FALSE;
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "OpenMutexA ����", msg);

	CloseHandle(hMutex); //������ ���ؽ� ���� �� ����
	CloseHandle(hMutexCreate);

	return result;
}

/**
* HANDLE CreateMutexExW(LPSECURITY_ATTRIBUTES lpMutexAttributes, LPCTSTR lpName,  DWORD dwFlags, DWORD dwDesiredAccess)
* ���� �Ǵ� ������ ���� ���ؽ� ��ü�� ����ų� ����.
* @author : ������  
*
* @param  lpMutexAttributes SECURITY_ATTRIBUTES ����ü�� ���� ������
* @param  lpName ���ؽ� ��ü�� �̸�
* @param  dwFlags CREATE_MUTEX_INITIAL_OWNER �̰ų� 0
* @param  dwDesiredAccess ���ؽ� ��ü�� �׼��� ����ũ
* @return ���ؽ� ��ü�� �ڵ�
*/
BOOL test_CreateMutexExW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ], buf[BUFSIZ];

	HANDLE hMutex = NULL;
	LPWSTR lpName = L"test_CreateMutexExW";

	const int nThreadCount = 2;
	HANDLE hThread[nThreadCount];
	
	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	sharedVar = 0;

	hMutex = CreateMutexExW(NULL, lpName, 0, MUTEX_ALL_ACCESS | MUTEX_MODIFY_STATE);

	/* 2���� �����带 �����ϰ� ���� hMutex �ڵ��� �ѱ��. */
	/* ������ ������ ���� �� �׽�Ʈ �ߴ� */
	if(!CreateMultipleThreads(hThread, ThreadFunc, hMutex, nThreadCount)){
		return FALSE;
	}	
	
	/* ��� �����尡 ����� �� ���� busy-waiting�Ѵ�. */
	if(!BusyWaitingExitThread(hThread, 2)){
		return FALSE;
	}

	/* ���ؽ��� ���� �����尡 ������ for���� ������ �� �ڿ� �ٸ� �����尡 �����ڿ��� �����ϴ����� Ȯ���Ѵ�. */
	if((NULL != hMutex)){
		if((sharedVar = BIG_INTEGER * 2)){
			sprintf(msg, "CreateMutexExW ���� : hMutex = %d, sharedVar = %d", hMutex, sharedVar);
			strcpy(buf, "CreateMutexExW ����");
		}else{
			sprintf(msg, "CreateMutexExW ���� : sharedVar�� %d�� �ƴմϴ�.", BIG_INTEGER * 2);
			strcpy(buf, "CreateMutexExW ����");
		}

	}else{ //���ؽ� ���� ����
		sprintf(msg, GetErrorMessage("CreateMutexExW ���� : ", GetLastError()));
		strcpy(buf, "CreateMutexExW ����");
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateMutexExW ����", msg);

	CloseHandle(hMutex); //������ ���ؽ� ���� �� ����

	for(int i=0; i<nThreadCount; i++){
		CloseHandle(hThread[i]);
	}

	sharedVar = 0;

	return result;
}

/**
* HANDLE CreateMutexExA(LPSECURITY_ATTRIBUTES lpMutexAttributes, LPCTSTR lpName,  DWORD dwFlags, DWORD dwDesiredAccess)
* ���� �Ǵ� ������ ���� ���ؽ� ��ü�� ����ų� ����.
* @author : ������  
*
* @param  lpMutexAttributes SECURITY_ATTRIBUTES ����ü�� ���� ������
* @param  lpName ���ؽ� ��ü�� �̸�
* @param  dwFlags CREATE_MUTEX_INITIAL_OWNER �̰ų� 0
* @param  dwDesiredAccess ���ؽ� ��ü�� �׼��� ����ũ
* @return ���ؽ� ��ü�� �ڵ�
*/
BOOL test_CreateMutexExA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ], buf[BUFSIZ];

	HANDLE hMutex = NULL;
	LPSTR lpName = "test_CreateMutexExW";

	const int nThreadCount = 2;
	HANDLE hThread[nThreadCount];
	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	sharedVar = 0;

	hMutex = CreateMutexExA(NULL, lpName, 0, MUTEX_ALL_ACCESS | MUTEX_MODIFY_STATE);

	
	/* 2���� �����带 �����ϰ� ���� hMutex �ڵ��� �ѱ��. */
	/* ������ ������ ���� �� �׽�Ʈ �ߴ� */
	if(!CreateMultipleThreads(hThread, ThreadFunc, hMutex, nThreadCount)){
		return FALSE;
	}
	
	
	/* ��� �����尡 ����� �� ���� busy-waiting�Ѵ�. */
	if(!BusyWaitingExitThread(hThread, 2)){
		return FALSE;
	}

	/* ���ؽ��� ���� �����尡 ������ for���� ������ �� �ڿ� �ٸ� �����尡 �����ڿ��� �����ϴ����� Ȯ���Ѵ�. */
	if((NULL != hMutex)){
		if((sharedVar = BIG_INTEGER * 2)){
			sprintf(msg, "CreateMutexExA ���� : hMutex = %d, sharedVar = %d", hMutex, sharedVar);
			strcpy(buf, "CreateMutexExA ����");
		}else{
			sprintf(msg, "CreateMutexExA ���� : sharedVar�� %d�� �ƴմϴ�.", BIG_INTEGER * 2);
			strcpy(buf, "CreateMutexExA ����");
		}

	}else{ //���ؽ� ���� ����
		sprintf(msg, GetErrorMessage("CreateMutexExA ���� : ", GetLastError()));
		strcpy(buf, "CreateMutexExA ����");
		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateMutexExA ����", msg);

	CloseHandle(hMutex); //������ ���ؽ� ���� �� ����

	for(int i=0; i<nThreadCount; i++){
		CloseHandle(hThread[i]);
	}

	sharedVar = 0;

	return result;
}


