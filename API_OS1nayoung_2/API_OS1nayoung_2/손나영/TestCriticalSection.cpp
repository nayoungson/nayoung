#include "TestCriticalSection.h"
#include <Windows.h>
#include <TlHelp32.h>

// 0911

/**
		critical section을 초기화하고 spin count, 부가기능 설정
		※ 하나의 공통 데이터(변수 등)를 특정 thread가 사용 중이라면, 다른 thread들이 접근하지 못하도록 EnterCriticalSection()으로 lock을 검.
		   이때 critical section을 임계영역이라 하는데, 이 부분을 초기화해주는 것이 InitializeCriticalSection.
		   CriticalSection은 multi thread에서 가장 일반적으로 사용되는 방법이며,
		   multi thread를 동기화하는 방법으로 CriticalSection, Mutex, Semaphore 등이 존재.
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

	if(result != 0){ //성공
		strcpy(meg, "Critical Section 초기화 : PASS \n ");
		//초기화된 critical section obcject는 다시 초기화하기 전에 삭제해야 함. 
		//그렇지 않으면 정의되지 않은 동작이 발생할 수 있음.
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
		strcpy(meg, " Critical Section 초기화 및 spincount 설정 : PASS \n\n spincount : 0x00000400(1024)");

		//초기화된 critical section obcject는 다시 초기화하기 전에 삭제해야 함.
		//그렇지 않으면 정의되지 않은 동작이 발생할 수 있음.
		DeleteCriticalSection(&crs); 
		wresult_value=1;
	}else
		strcpy(meg, "FAIL");

	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "InitializeCriticalSectionAndSpinCount", buf,"1", meg);  

	return result;
}
/**
		critical section object 권한을 해제 ( = critical section을 빠져나옴)
*/
void LeaveCriticalSection(){
	BOOL crs_block;
	CRITICAL_SECTION crs;

	LeaveCriticalSection(&crs);
	crs_block = false;
}

/**
		block처리(wait)되지 않고  Critical Section Object 권한을 요청
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
	BOOL initial_result; // InitializeCriticalSectionEx 결과 저장
	BOOL tryenter_result; // TryEnterCriticalSection 결과 저장
	HWND hWnd = 0;

	initial_result = InitializeCriticalSectionEx(&crs, spincount, flags);
	tryenter_result = TryEnterCriticalSection(&crs);

	if(initial_result == TRUE){ // InitializeCriticalSectionEx가 성공이고,
		if(tryenter_result == TRUE){ // TryEnterCriticalSection이 성공일 경우

			strcpy(buf, "TryEnterCriticalSection : PASS");

			//마지막에는 Delete로 삭제해 줘야함.
			DeleteCriticalSection(&crs);

		}else{ //TryEnterCriticalSection가 실패일 경우
			strcpy(meg, "TryEnterCriticalSection 실패");
		}
		
	}else{ // initial_result == FALSE인 경우.
		   // InitializeCriticalSectionEx 실패 → 초기화부터 해야함.
		//MessageBox(hWnd, L"초기화 실패. InitializeCriticalSection 함수로 critical section을 먼저 초기화하세요.", L"fail", MB_OK);
	}

	wresult(__FILE__, __LINE__, "InitializeCriticalSectionEx", buf, "TryEnterCriticalSection : PASS", meg);

	return tryenter_result;
}

/**
		critical section object를 삭제
*/

BOOL test_DeleteCriticalSection(){   

	#ifdef OQADBGPRINT
	printf("test_DeleteCriticalSection\n");
	#endif

	HWND hWnd = 0;
	CRITICAL_SECTION crs;
	DWORD spincount=4000;
	DWORD flags = CRITICAL_SECTION_NO_DEBUG_INFO;
	BOOL initial_result; // InitializeCriticalSectionEx 결과 저장
	BOOL tryenter_result; // TryEnterCriticalSection 결과 저장

	char meg[BUFSIZ] = "FAIL";
	
	initial_result = InitializeCriticalSectionAndSpinCount(&crs, spincount);
	
	if(initial_result != 0){ // InitializeCriticalSectionEx가 성공이고,
		DeleteCriticalSection(&crs);
		
		// TryEnterCriticalSection 또는 EnterCriticalSection 함수로 critical section의 ownership 요구.
		// 이때 진입이 되다면, 초기화는 제대로 됐으나 삭제가 제대로 되지 않은 것임을 확인 가능.

		/** 
			TryEnterCriticalSection
			if this function is successfully entered, the return value is nonzero. shortly : succes -> != 0
			if another thread already owns the critical section, the return value is zero. 
			this means -> not success x . already owns -> == 0
		*/

		tryenter_result = TryEnterCriticalSection(&crs); 
		if(tryenter_result == 0){
			#ifdef OQADBG
			MessageBox(hWnd, L"삭제 실패 \nDeleteCriticalSection 함수로 critical section을 먼저 삭제한 후, 다시 Initializ하세요.", L"fail", MB_OK);
			#endif
		}else{ // tryenter_result == FALSE → Critical Section이 정상 삭제되어 진입이 불가한 상태.
			strcpy(meg, " DeleteCriticalSection : PASS \n\n InitializeCriticalSectionAndSpinCount 초기화 후 → DeleteCriticalSection 삭제 ");
			
		}
	}else{ // InitializeCriticalSectionEx가 실패인 경우
		#ifdef OQADBG
		MessageBox(hWnd, L"초기화 실패. InitializeCriticalSection 함수로 critical section을 먼저 초기화하세요.", L"fail", MB_OK);
		#endif
		//wresult(__FILE__, __LINE__, "InitializeCriticalSectionEx", "0", "1", meg);
	}

	wresult(__FILE__, __LINE__, "InitializeCriticalSectionEx", "1", "1", meg);

	return tryenter_result;
}

