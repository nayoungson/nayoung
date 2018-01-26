#include "TestQuery.h"


/**
* BOOL QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount)
* 성능 카운터의 현재 값을 검색함. 이 값은 시간 간격 측정에 사용할 수있는 고해상도(<1us) 시간 스탬프.
* @author : 손찬영  
*
* @param  lpPerformanceCount count에서 현재 성능 카운터 값을 받는 변수에 대한 포인터
* @return 성공/실패 여부
*/
BOOL test_QueryPerformanceCounter()
{		
	const int sleepMilSecond = 3000;
	LARGE_INTEGER frequency;
	LARGE_INTEGER beginTime;
	LARGE_INTEGER endTime;
	_int64 elapsed = 0;
	const _int64 expect = sleepMilSecond/1000; //기대하는 소요 시간

	char msg[BUFSIZ];
	char buf[BUFSIZ];
	BOOL result = TRUE;

#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif

	/* 성능 카운터 사용 가능한 것을 확인한다. */
	if(!QueryPerformanceFrequency(&frequency)){
		strcpy(msg, GetErrorMessage("QueryPerformanceFrequency 실패 : ", GetLastError()));
		strcpy(buf, "QueryPerformanceFrequency 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "QueryPerformanceFrequency 성공", msg);

		return FALSE;
	}

	/* Sleep하기 전, 시작 카운터를 가져온다. */
	if(!QueryPerformanceCounter(&beginTime)){
		strcpy(msg, GetErrorMessage("QueryPerformanceCounter(&beginTime) 실패 : ", GetLastError()));
		strcpy(buf, "QueryPerformanceCounter 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "QueryPerformanceCounter 성공", msg);

		return FALSE;
	}

	/* N초 슬립한다. */
	Sleep(sleepMilSecond);

	/* N초 후의 카운터를 가져온다. */
	if(!QueryPerformanceCounter(&endTime)){
		strcpy(msg, GetErrorMessage("QueryPerformanceCounter(&endTime) 실패 : ", GetLastError()));
		strcpy(buf, "QueryPerformanceCounter 실패");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "QueryPerformanceCounter 성공", msg);

		return FALSE;
	}

	/* 카운터를 소요시간을 변환한다. */
	elapsed = endTime.QuadPart - beginTime.QuadPart;
	elapsed = (__int64)(elapsed / (double)frequency.QuadPart);

	/* 기대시간과 실제 소요시간이 동일하면 성공 */
	if(expect == elapsed){
		sprintf(msg, "QueryPerformanceCounter 성공 : 소요시간 %d초", expect);
		strcpy(buf, "QueryPerformanceCounter 성공");
	
	}else{
		sprintf(msg, "QueryPerformanceCounter 실패 : 기대시간 %초, 소요시간 %d초", expect, elapsed);
		strcpy(buf, "QueryPerformanceCounter 실패");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "QueryPerformanceCounter 성공", msg);

	return result;
}


/**
* BOOL QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency)
* 성능 카운터의 빈도를 검색한다. 성능 카운터의 빈도는 시스템 부팅시 고정되어 있으며 모든 프로세서에서 일관된다.
* @author : 손찬영  
*
* @param  lpFrequency 현재 성능 카운터 빈도를 초당 카운트로받는 변수에 대한 포인터입니다. 
*					  하드웨어가 고해상도 성능 카운터를 지원하지 않는 경우이 매개 변수는 0.
* @return 성공/실패 여부
*/
BOOL test_QueryPerformanceFrequency()
{
	LARGE_INTEGER lpFrequency;
	BOOL result = TRUE;

	char msg[BUFSIZ];
	char buf[BUFSIZ];

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	if((result =QueryPerformanceFrequency(&lpFrequency))){
		sprintf(msg, "이 기기에서 타이머 사용 가능\nlpFrequency.QuadPart = %llu", (__int64)lpFrequency.QuadPart);
		strcpy(buf, "타이머 사용가능");

	}else{
		sprintf(msg, GetErrorMessage("QueryPerformanceFrequency 실패 : ", GetLastError()));
		strcpy(buf, "타이머 사용불가");
		result = FALSE;	
	}

	wresult(__FILE__, __LINE__, __FUNCTION__, buf, "타이머 사용가능", msg);

	return result;
}