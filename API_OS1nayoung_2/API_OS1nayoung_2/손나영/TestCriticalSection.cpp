#include "TestCriticalSection.h"
#include <Windows.h>
#include <TlHelp32.h>

/**
* void WINAPI DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
* �������� ���� critical section object�� ���� ���� ��� ���ҽ��� ����(delete)��.
* @author : �ճ���
*
* @param lpCriticalSection critical section object�� ������. �̴� �ݵ�� ������ InitializeCriticalSection �Լ��� �ʱ�ȭ�� object���� ��.
* @return ����. ���� TryEnterCriticalSection �Լ��� ���� ���θ� �Ǵ��Ͽ� DeleteCriticalSection ����(���� �ƴ���) ���� Ȯ��.

*/
BOOL test_DeleteCriticalSection(){   

	#ifdef OQADBGPRINT
	printf("test_DeleteCriticalSection\n");
	#endif

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ];

	BOOL result = FALSE;
	HWND hWnd = 0;

	CRITICAL_SECTION lpCriticalSection;
	DWORD dwSpinCount = 4000;
	DWORD Flags = CRITICAL_SECTION_NO_DEBUG_INFO;
	
	// �ʱ�ȭ
	// DeleteCriticalSection�� �Ķ���� �� InitializeCriticalSection(Ex)�� �ʱ�ȭ�� object
	result = InitializeCriticalSectionEx(&lpCriticalSection, dwSpinCount, Flags);

	// �ʱ�ȭ ������ ���
	if(result == FALSE){	
		strcpy(msg, "�ʱ�ȭ ����. InitializeCriticalSection �Լ��� critical section�� ���� �ʱ�ȭ�ϼ���.");
		//return FALSE;

	// �ʱ�ȭ ������ ���
	}else{	
		
		// ���� ����. ���� ����/���� ���δ� ����X. ������ ���� �ʾҴٸ� �翬�� try �����̹Ƿ�.
		DeleteCriticalSection(&lpCriticalSection);

		result = TryEnterCriticalSection(&lpCriticalSection);
		
		// Try ���� �� ���� O
		if(result == FALSE){ 
			strcpy(buf, "SUCCESS");
			strcpy(msg, "DeleteCriticalSection() : SUCCESS");
			result = TRUE;
			
		// Try ���� �� ���� X
		}else{
			sprintf(msg, "DeleteCriticalSection() : FAIL");
		}
	}

	wresult(__FILE__, __LINE__, "DeleteCriticalSection", buf, "SUCCESS", msg);
	return result;
}


/**
* BOOL WINAPI InitializeCriticalSectionAndSpinCount(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount)
* critical section object�� �ʱ�ȭ�ϰ�, spin count�� �Է�.
* @author : �ճ���
*
* @param lpCriticalSection critical section object�� ������.
* @param dwSpinCount critical section object�� spin count.
* @return �ʱ�ȭ �� spin count ���� ����/���� ����.
*/
BOOL test_InitializeCriticalSectionAndSpinCount(){

	#ifdef OQADBGPRINT
	printf("test_InitializeCriticalSectionAndSpinCount\n");
	#endif

	int wresult_value=0;
	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";

	BOOL result = FALSE;
	CRITICAL_SECTION lpCriticalSection;
	DWORD dwSpinCount = 0x00000400;	//1024
	
	// �ʱ�ȭ
	// spincount : �̱� ���μ��� �ý����� ���, spin count�� ���õǰ� 0���� ���� ����. ���⼭�� 1024�� ������ ��. 
	result = InitializeCriticalSectionAndSpinCount(&lpCriticalSection, dwSpinCount);

	if(result != FALSE){
		strcpy(msg, " InitializeCriticalSectionAndSpinCount() : SUCCESS \n\n spincount : 0x00000400(1024)");

		//�ʱ�ȭ�� critical section obcject�� �ٽ� �ʱ�ȭ�ϱ� ���� �����ؾ� ��.
		//�׷��� ������ ���ǵ��� ���� ������ �߻��� �� ����.
		DeleteCriticalSection(&lpCriticalSection); 

		wresult_value=1;
	}else
		strcpy(msg, "InitializeCriticalSectionAndSpinCount() : FAIL");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "InitializeCriticalSectionAndSpinCount", buf,"1", msg);  
	return result;
}


/**
* BOOL WINAPI InitializeCriticalSectionEx(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount, DWORD Flags)
* critical section object�� spin count�� �ɼ� flag�� �ΰ� �ʱ�ȭ.
* @author : �ճ���
*
* @param lpCriticalSection critical section object�� ������.
* @param dwSpinCount critical section object�� spin count.
* @param Flags �ɼ� �÷���. 0�Ǵ� CRITICAL_SECTION_NO_DEBUG_INFO.
* @return �ʱ�ȭ ����/���� ����.
*/
BOOL test_InitializeCriticalSectionEx(){

	#ifdef OQADBGPRINT
	printf("test_InitializeCriticalSectionEx\n");
	#endif

	int wresult_value=0;
	char buf[BUFSIZ] ="FAIL";
	char msg[BUFSIZ] = "FAIL";

	BOOL result = FALSE;
	CRITICAL_SECTION lpCriticalSection;
	DWORD dwSpinCount = 0;
	DWORD Flags = CRITICAL_SECTION_NO_DEBUG_INFO; 

	// spincount : �̱� ���μ��� �ý����� ���, spin count�� ���õǰ� 0���� ���� ����.
	// This flags(CRITICAL_SECTION_NO_DEBUG_INFO) mean that the critical section is created without debug information.
	result = InitializeCriticalSectionEx(&lpCriticalSection, dwSpinCount, Flags);

	if(result != FALSE){ // �ʱ�ȭ ����
		strcpy(msg, "InitializeCriticalSectionEx () : SUCCESS");
		
		//�ʱ�ȭ�� critical section obcject�� �ٽ� �ʱ�ȭ�ϱ� ���� �����ؾ� ��. 
		//�׷��� ������ ���ǵ��� ���� ������ �߻��� �� ����.
		DeleteCriticalSection(&lpCriticalSection); 
		wresult_value = 1;

	}else // �ʱ�ȭ ����
		strcpy(msg, "FAIL");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "InitializeCriticalSectionEx", buf, "1", msg);  
	return result;
}


/**
* BOOL WINAPI TryEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
* �������� critical section�� ������ �õ�.
* @author : �ճ���
*
* @param lpCriticalSection critical section object�� ������.
* @return ���� �Ǵ� �ֱ� �����尡 �̹� critical section�� �����ϰ� �ִ��� ����/���� ����.
*/
BOOL test_TryEnterCriticalSection(){

	#ifdef OQADBGPRINT
	printf("test_TryEnterCriticalSection \n");
	#endif

	char buf[BUFSIZ] = "FAIL";
	char msg[BUFSIZ] = "FAIL";
	
	BOOL result = FALSE;
	HWND hWnd = 0;
	CRITICAL_SECTION lpCriticalSection;
	DWORD dwSpinCount = 0;
	DWORD Flags = CRITICAL_SECTION_NO_DEBUG_INFO;

	// spincount : �̱� ���μ��� �ý����� ���, spin count�� ���õǰ� 0���� ���� ����. ���⼭�� 1024�� ������ ��. 
	// This flags(CRITICAL_SECTION_NO_DEBUG_INFO) mean that the critical section is created without debug information.
	result = InitializeCriticalSectionEx(&lpCriticalSection, dwSpinCount, Flags);

	if(result == FALSE){	//�ʱ�ȭ ����
		strcpy(msg, "�ʱ�ȭ ����. InitializeCriticalSection �Լ��� critical section�� ���� �ʱ�ȭ�ϼ���.");
		//return FALSE;

	}else{	//�ʱ�ȭ ����
		result = TryEnterCriticalSection(&lpCriticalSection);
		
		if(result == FALSE){ // Try ����
			sprintf(msg, "TryEnterCriticalSection() : FAIL");
		}else{	// Try ����
			strcpy(buf, "SUCCESS");
			strcpy(msg, "TryEnterCriticalSection() : SUCCESS");

			//���������� Delete�� ������ �����.
			DeleteCriticalSection(&lpCriticalSection);
		}
	}

	wresult(__FILE__, __LINE__, "InitializeCriticalSectionEx", buf, "SUCCESS", msg);
	return result;
}

/**
		critical section�� �ʱ�ȭ�ϰ� spin count, �ΰ���� ����
		�� �ϳ��� ���� ������(���� ��)�� Ư�� thread�� ��� ���̶��, �ٸ� thread���� �������� ���ϵ��� EnterCriticalSection()���� lock�� ��.
		   �̶� critical section�� �Ӱ迵���̶� �ϴµ�, �� �κ��� �ʱ�ȭ���ִ� ���� InitializeCriticalSection.
		   CriticalSection�� multi thread���� ���� �Ϲ������� ���Ǵ� ����̸�,
		   multi thread�� ����ȭ�ϴ� ������� CriticalSection, Mutex, Semaphore ���� ����.
*/

/**
void LeaveCriticalSection(){

	// critical section object ������ ���� ( = critical section�� ��������) 

	BOOL crs_block;
	CRITICAL_SECTION crs;

	LeaveCriticalSection(&crs);
	crs_block = false;
}
*/