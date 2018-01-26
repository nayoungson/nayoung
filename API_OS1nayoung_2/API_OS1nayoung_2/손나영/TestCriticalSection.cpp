#include "TestCriticalSection.h"
#include <Windows.h>
#include <TlHelp32.h>

/**
* void WINAPI DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
* 소유되지 않은 critical section object에 의해 사용된 모든 리소스를 해제(delete)함.
* @author : 손나영
*
* @param lpCriticalSection critical section object의 포인터. 이는 반드시 이전에 InitializeCriticalSection 함수로 초기화된 object여야 함.
* @return 없음. 따라서 TryEnterCriticalSection 함수로 진입 여부를 판단하여 DeleteCriticalSection 성공(해제 됐는지) 여부 확인.

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
	
	// 초기화
	// DeleteCriticalSection의 파라미터 → InitializeCriticalSection(Ex)로 초기화된 object
	result = InitializeCriticalSectionEx(&lpCriticalSection, dwSpinCount, Flags);

	// 초기화 실패의 경우
	if(result == FALSE){	
		strcpy(msg, "초기화 실패. InitializeCriticalSection 함수로 critical section을 먼저 초기화하세요.");
		//return FALSE;

	// 초기화 성공의 경우
	}else{	
		
		// 삭제 진행. 삭제 성공/실패 여부는 보지X. 삭제가 되지 않았다면 당연히 try 성공이므로.
		DeleteCriticalSection(&lpCriticalSection);

		result = TryEnterCriticalSection(&lpCriticalSection);
		
		// Try 실패 → 삭제 O
		if(result == FALSE){ 
			strcpy(buf, "SUCCESS");
			strcpy(msg, "DeleteCriticalSection() : SUCCESS");
			result = TRUE;
			
		// Try 성공 → 삭제 X
		}else{
			sprintf(msg, "DeleteCriticalSection() : FAIL");
		}
	}

	wresult(__FILE__, __LINE__, "DeleteCriticalSection", buf, "SUCCESS", msg);
	return result;
}


/**
* BOOL WINAPI InitializeCriticalSectionAndSpinCount(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount)
* critical section object를 초기화하고, spin count를 입력.
* @author : 손나영
*
* @param lpCriticalSection critical section object의 포인터.
* @param dwSpinCount critical section object의 spin count.
* @return 초기화 및 spin count 설정 성공/실패 여부.
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
	
	// 초기화
	// spincount : 싱글 프로세서 시스템의 경우, spin count는 무시되고 0으로 설정 가능. 여기서는 1024로 설정해 봄. 
	result = InitializeCriticalSectionAndSpinCount(&lpCriticalSection, dwSpinCount);

	if(result != FALSE){
		strcpy(msg, " InitializeCriticalSectionAndSpinCount() : SUCCESS \n\n spincount : 0x00000400(1024)");

		//초기화된 critical section obcject는 다시 초기화하기 전에 삭제해야 함.
		//그렇지 않으면 정의되지 않은 동작이 발생할 수 있음.
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
* critical section object를 spin count와 옵션 flag를 두고 초기화.
* @author : 손나영
*
* @param lpCriticalSection critical section object의 포인터.
* @param dwSpinCount critical section object의 spin count.
* @param Flags 옵션 플래그. 0또는 CRITICAL_SECTION_NO_DEBUG_INFO.
* @return 초기화 성공/실패 여부.
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

	// spincount : 싱글 프로세서 시스템의 경우, spin count는 무시되고 0으로 설정 가능.
	// This flags(CRITICAL_SECTION_NO_DEBUG_INFO) mean that the critical section is created without debug information.
	result = InitializeCriticalSectionEx(&lpCriticalSection, dwSpinCount, Flags);

	if(result != FALSE){ // 초기화 성공
		strcpy(msg, "InitializeCriticalSectionEx () : SUCCESS");
		
		//초기화된 critical section obcject는 다시 초기화하기 전에 삭제해야 함. 
		//그렇지 않으면 정의되지 않은 동작이 발생할 수 있음.
		DeleteCriticalSection(&lpCriticalSection); 
		wresult_value = 1;

	}else // 초기화 실패
		strcpy(msg, "FAIL");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "InitializeCriticalSectionEx", buf, "1", msg);  
	return result;
}


/**
* BOOL WINAPI TryEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
* 막힘없이 critical section에 진입을 시도.
* @author : 손나영
*
* @param lpCriticalSection critical section object의 포인터.
* @return 진입 또는 최근 스레드가 이미 critical section을 소유하고 있는지 성공/실패 여부.
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

	// spincount : 싱글 프로세서 시스템의 경우, spin count는 무시되고 0으로 설정 가능. 여기서는 1024로 설정해 봄. 
	// This flags(CRITICAL_SECTION_NO_DEBUG_INFO) mean that the critical section is created without debug information.
	result = InitializeCriticalSectionEx(&lpCriticalSection, dwSpinCount, Flags);

	if(result == FALSE){	//초기화 실패
		strcpy(msg, "초기화 실패. InitializeCriticalSection 함수로 critical section을 먼저 초기화하세요.");
		//return FALSE;

	}else{	//초기화 성공
		result = TryEnterCriticalSection(&lpCriticalSection);
		
		if(result == FALSE){ // Try 실패
			sprintf(msg, "TryEnterCriticalSection() : FAIL");
		}else{	// Try 성공
			strcpy(buf, "SUCCESS");
			strcpy(msg, "TryEnterCriticalSection() : SUCCESS");

			//마지막에는 Delete로 삭제해 줘야함.
			DeleteCriticalSection(&lpCriticalSection);
		}
	}

	wresult(__FILE__, __LINE__, "InitializeCriticalSectionEx", buf, "SUCCESS", msg);
	return result;
}

/**
		critical section을 초기화하고 spin count, 부가기능 설정
		※ 하나의 공통 데이터(변수 등)를 특정 thread가 사용 중이라면, 다른 thread들이 접근하지 못하도록 EnterCriticalSection()으로 lock을 검.
		   이때 critical section을 임계영역이라 하는데, 이 부분을 초기화해주는 것이 InitializeCriticalSection.
		   CriticalSection은 multi thread에서 가장 일반적으로 사용되는 방법이며,
		   multi thread를 동기화하는 방법으로 CriticalSection, Mutex, Semaphore 등이 존재.
*/

/**
void LeaveCriticalSection(){

	// critical section object 권한을 해제 ( = critical section을 빠져나옴) 

	BOOL crs_block;
	CRITICAL_SECTION crs;

	LeaveCriticalSection(&crs);
	crs_block = false;
}
*/