#include "TestCriticalSection.h"
#include <Windows.h>
#include <TlHelp32.h>

// 0911

/**
		critical section�� �ʱ�ȭ�ϰ� spin count, �ΰ���� ����
		�� �ϳ��� ���� ������(���� ��)�� Ư�� thread�� ��� ���̶��, �ٸ� thread���� �������� ���ϵ��� EnterCriticalSection()���� lock�� ��.
		   �̶� critical section�� �Ӱ迵���̶� �ϴµ�, �� �κ��� �ʱ�ȭ���ִ� ���� InitializeCriticalSection.
		   CriticalSection�� multi thread���� ���� �Ϲ������� ���Ǵ� ����̸�,
		   multi thread�� ����ȭ�ϴ� ������� CriticalSection, Mutex, Semaphore ���� ����.
*/
BOOL test_InitializeCriticalSectionEx(){
	CRITICAL_SECTION crs;
	DWORD spincount = 0;
	DWORD flags = CRITICAL_SECTION_NO_DEBUG_INFO;
	BOOL result;
	
	char real_result[BUFSIZ];

	int c;
	#ifdef OQADBGPRINT
	printf("test_InitializeCriticalSectionEx\n");
	#endif
	char meg[BUFSIZ] = "FAIL";

	result = InitializeCriticalSectionEx(&crs, spincount, flags);
	if(result != 0){
		strcpy(meg, "Critical Section �ʱ�ȭ : PASS \n ");
		c = 1;
		//�ʱ�ȭ�� critical section obcject�� �ٽ� �ʱ�ȭ�ϱ� ���� �����ؾ� ��. 
		//�׷��� ������ ���ǵ��� ���� ������ �߻��� �� ����.
		DeleteCriticalSection(&crs); 
	}else
		strcpy(meg, "FAIL");
	sprintf(real_result, "%d", c);
	wresult(__FILE__, __LINE__, "InitializeCriticalSectionEx",real_result , "1", meg);  

	return true;
}


BOOL test_InitializeCriticalSectionAndSpinCount(){
	CRITICAL_SECTION crs;
	DWORD spincount = 0x00000400;
	BOOL result;
	
	char meg[BUFSIZ] = "FAIL";
	#ifdef OQADBGPRINT
	printf("test_InitializeCriticalSectionAndSpinCount\n");
	#endif
	result = InitializeCriticalSectionAndSpinCount(&crs, spincount);
	if(result == TRUE){
		strcpy(meg, " Critical Section �ʱ�ȭ �� spincount ���� : PASS \n\n spincount : 0x00000400(1024)");

		//�ʱ�ȭ�� critical section obcject�� �ٽ� �ʱ�ȭ�ϱ� ���� �����ؾ� ��.
		//�׷��� ������ ���ǵ��� ���� ������ �߻��� �� ����.
		DeleteCriticalSection(&crs); 
	}else
		strcpy(meg, "FAIL");
	wresult(__FILE__, __LINE__, "InitializeCriticalSectionAndSpinCount", "1", "1", meg);  

	return true;
}
/**
		critical section object ������ ���� ( = critical section�� ��������)
*/
void LeaveCriticalSection(){
	BOOL crs_block;
	CRITICAL_SECTION crs;

	LeaveCriticalSection(&crs);
	crs_block = false;
}

/**
		blockó��(wait)���� �ʰ�  Critical Section Object ������ ��û
*/
BOOL test_TryEnterCriticalSection(){
	CRITICAL_SECTION crs;
	DWORD spincount=0;
	DWORD flags = CRITICAL_SECTION_NO_DEBUG_INFO;
	BOOL initial_result; // InitializeCriticalSectionEx ��� ����
	BOOL tryenter_result; // TryEnterCriticalSection ��� ����
	HWND hWnd = 0;

	char meg[BUFSIZ] = "FAIL";
	#ifdef OQADBGPRINT
	printf("test_TryEnterCriticalSection\n");
	#endif
	initial_result = InitializeCriticalSectionEx(&crs, spincount, flags);
	tryenter_result = TryEnterCriticalSection(&crs);
	if(initial_result == TRUE){ // InitializeCriticalSectionEx�� �����̰�,
		if(tryenter_result == TRUE){ // TryEnterCriticalSection�� ������ ���
			strcpy(meg, "TryEnterCriticalSection : PASS");
			//���������� Delete�� ������ �����.
			DeleteCriticalSection(&crs);
		}else{ //TryEnterCriticalSection�� ������ ���
			strcpy(meg, "TryEnterCriticalSection ����");
			wresult(__FILE__, __LINE__, "TryEnterCriticalSection", "0", "1", meg);
		}
		wresult(__FILE__, __LINE__, "InitializeCriticalSectionEx", "1", "1", meg);
	}else{ // initial_result == FALSE�� ���.
		   // InitializeCriticalSectionEx ���� �� �ʱ�ȭ���� �ؾ���.
		MessageBox(hWnd, L"�ʱ�ȭ ����. InitializeCriticalSection �Լ��� critical section�� ���� �ʱ�ȭ�ϼ���.", L"fail", MB_OK);
		//wresult(__FILE__, __LINE__, "InitializeCriticalSectionEx", "0", "1", meg);
	}
	return true;
}

/**
		critical section object�� ����
*/

BOOL test_DeleteCriticalSection(){   
	CRITICAL_SECTION crs;
	DWORD spincount=4000;
	DWORD flags = CRITICAL_SECTION_NO_DEBUG_INFO;
	BOOL initial_result; // InitializeCriticalSectionEx ��� ����
	BOOL tryenter_result; // TryEnterCriticalSection ��� ����

	HWND hWnd = 0;

	char meg[BUFSIZ] = "FAIL";
	#ifdef OQADBGPRINT
	printf("test_DeleteCriticalSection\n");
	#endif
	initial_result = InitializeCriticalSectionAndSpinCount(&crs, spincount);
	
	if(initial_result != 0){ // InitializeCriticalSectionEx�� �����̰�,
		DeleteCriticalSection(&crs);
		
		// TryEnterCriticalSection �Ǵ� EnterCriticalSection �Լ��� critical section�� ownership �䱸.
		// �̶� ������ �Ǵٸ�, �ʱ�ȭ�� ����� ������ ������ ����� ���� ���� ������ Ȯ�� ����.

		/** 
			TryEnterCriticalSection
			if this function is successfully entered, the return value is nonzero. shortly : succes -> != 0
			if another thread already owns the critical section, the return value is zero. 
			this means -> not success x . already owns -> == 0
		*/

		tryenter_result = TryEnterCriticalSection(&crs); 
		if(tryenter_result == 0){
			#ifdef OQADBG
			MessageBox(hWnd, L"���� ���� \nDeleteCriticalSection �Լ��� critical section�� ���� ������ ��, �ٽ� Initializ�ϼ���.", L"fail", MB_OK);
			#endif
		}else{ // tryenter_result == FALSE �� Critical Section�� ���� �����Ǿ� ������ �Ұ��� ����.
			strcpy(meg, " DeleteCriticalSection : PASS \n\n InitializeCriticalSectionAndSpinCount �ʱ�ȭ �� �� DeleteCriticalSection ���� ");
			wresult(__FILE__, __LINE__, "InitializeCriticalSectionEx", "1", "1", meg);
		}
	}else{ // InitializeCriticalSectionEx�� ������ ���
		#ifdef OQADBG
		MessageBox(hWnd, L"�ʱ�ȭ ����. InitializeCriticalSection �Լ��� critical section�� ���� �ʱ�ȭ�ϼ���.", L"fail", MB_OK);
		#endif
		//wresult(__FILE__, __LINE__, "InitializeCriticalSectionEx", "0", "1", meg);
	}
	return true;
}

