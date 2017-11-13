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

	#ifdef OQADBGPRINT
	printf("test_InitializeCriticalSectionEx\n");
	#endif

	int wresult_value=0;
	char *buf = NULL;
	char meg[BUFSIZ] = "FAIL";

	CRITICAL_SECTION crs;
	DWORD spincount = 0;
	DWORD flags = CRITICAL_SECTION_NO_DEBUG_INFO;
	BOOL result;

	result = InitializeCriticalSectionEx(&crs, spincount, flags);

	if(result != 0){ //����
		strcpy(meg, "Critical Section �ʱ�ȭ : PASS \n ");
		//�ʱ�ȭ�� critical section obcject�� �ٽ� �ʱ�ȭ�ϱ� ���� �����ؾ� ��. 
		//�׷��� ������ ���ǵ��� ���� ������ �߻��� �� ����.
		DeleteCriticalSection(&crs); 
		wresult_value = 1;
	}else
		strcpy(meg, "FAIL");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "InitializeCriticalSectionEx", buf, "1", meg);  

	return result;
}


BOOL test_InitializeCriticalSectionAndSpinCount(){

	#ifdef OQADBGPRINT
	printf("test_InitializeCriticalSectionAndSpinCount\n");
	#endif

	int wresult_value=0;
	char *buf = NULL;
	char meg[BUFSIZ] = "FAIL";

	CRITICAL_SECTION crs;
	DWORD spincount = 0x00000400;
	BOOL result;

	result = InitializeCriticalSectionAndSpinCount(&crs, spincount);

	if(result == TRUE){
		strcpy(meg, " Critical Section �ʱ�ȭ �� spincount ���� : PASS \n\n spincount : 0x00000400(1024)");

		//�ʱ�ȭ�� critical section obcject�� �ٽ� �ʱ�ȭ�ϱ� ���� �����ؾ� ��.
		//�׷��� ������ ���ǵ��� ���� ������ �߻��� �� ����.
		DeleteCriticalSection(&crs); 
		wresult_value=1;
	}else
		strcpy(meg, "FAIL");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "InitializeCriticalSectionAndSpinCount", buf,"1", meg);  

	return result;
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

	#ifdef OQADBGPRINT
	printf("test_TryEnterCriticalSection\n");
	#endif

	char buf[BUFSIZ] = "FAIL";
	char meg[BUFSIZ] = "FAIL";
	
	CRITICAL_SECTION crs;
	DWORD spincount=0;
	DWORD flags = CRITICAL_SECTION_NO_DEBUG_INFO;
	BOOL initial_result; // InitializeCriticalSectionEx ��� ����
	BOOL tryenter_result; // TryEnterCriticalSection ��� ����
	HWND hWnd = 0;

	initial_result = InitializeCriticalSectionEx(&crs, spincount, flags);
	tryenter_result = TryEnterCriticalSection(&crs);

	if(initial_result == TRUE){ // InitializeCriticalSectionEx�� �����̰�,
		if(tryenter_result == TRUE){ // TryEnterCriticalSection�� ������ ���

			strcpy(buf, "TryEnterCriticalSection : PASS");

			//���������� Delete�� ������ �����.
			DeleteCriticalSection(&crs);

		}else{ //TryEnterCriticalSection�� ������ ���
			strcpy(meg, "TryEnterCriticalSection ����");
		}
		
	}else{ // initial_result == FALSE�� ���.
		   // InitializeCriticalSectionEx ���� �� �ʱ�ȭ���� �ؾ���.
		//MessageBox(hWnd, L"�ʱ�ȭ ����. InitializeCriticalSection �Լ��� critical section�� ���� �ʱ�ȭ�ϼ���.", L"fail", MB_OK);
	}

	wresult(__FILE__, __LINE__, "InitializeCriticalSectionEx", buf, "TryEnterCriticalSection : PASS", meg);

	return tryenter_result;
}

/**
		critical section object�� ����
*/

BOOL test_DeleteCriticalSection(){   

	#ifdef OQADBGPRINT
	printf("test_DeleteCriticalSection\n");
	#endif

	HWND hWnd = 0;
	CRITICAL_SECTION crs;
	DWORD spincount=4000;
	DWORD flags = CRITICAL_SECTION_NO_DEBUG_INFO;
	BOOL initial_result; // InitializeCriticalSectionEx ��� ����
	BOOL tryenter_result; // TryEnterCriticalSection ��� ����

	char meg[BUFSIZ] = "FAIL";
	
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
			
		}
	}else{ // InitializeCriticalSectionEx�� ������ ���
		#ifdef OQADBG
		MessageBox(hWnd, L"�ʱ�ȭ ����. InitializeCriticalSection �Լ��� critical section�� ���� �ʱ�ȭ�ϼ���.", L"fail", MB_OK);
		#endif
		//wresult(__FILE__, __LINE__, "InitializeCriticalSectionEx", "0", "1", meg);
	}

	wresult(__FILE__, __LINE__, "InitializeCriticalSectionEx", "1", "1", meg);

	return tryenter_result;
}

