#include "TestQuery.h"


/**
* BOOL QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount)
* ���� ī������ ���� ���� �˻���. �� ���� �ð� ���� ������ ����� ���ִ� ���ػ�(<1us) �ð� ������.
* @author : ������  
*
* @param  lpPerformanceCount count���� ���� ���� ī���� ���� �޴� ������ ���� ������
* @return ����/���� ����
*/
BOOL test_QueryPerformanceCounter()
{		
	const int sleepMilSecond = 3000;
	LARGE_INTEGER frequency;
	LARGE_INTEGER beginTime;
	LARGE_INTEGER endTime;
	_int64 elapsed = 0;
	const _int64 expect = sleepMilSecond/1000; //����ϴ� �ҿ� �ð�

	char msg[BUFSIZ];
	char buf[BUFSIZ];
	BOOL result = TRUE;

#ifdef OQADBGPRINT
	puts(__FUNCTION__);
#endif

	/* ���� ī���� ��� ������ ���� Ȯ���Ѵ�. */
	if(!QueryPerformanceFrequency(&frequency)){
		strcpy(msg, GetErrorMessage("QueryPerformanceFrequency ���� : ", GetLastError()));
		strcpy(buf, "QueryPerformanceFrequency ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "QueryPerformanceFrequency ����", msg);

		return FALSE;
	}

	/* Sleep�ϱ� ��, ���� ī���͸� �����´�. */
	if(!QueryPerformanceCounter(&beginTime)){
		strcpy(msg, GetErrorMessage("QueryPerformanceCounter(&beginTime) ���� : ", GetLastError()));
		strcpy(buf, "QueryPerformanceCounter ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "QueryPerformanceCounter ����", msg);

		return FALSE;
	}

	/* N�� �����Ѵ�. */
	Sleep(sleepMilSecond);

	/* N�� ���� ī���͸� �����´�. */
	if(!QueryPerformanceCounter(&endTime)){
		strcpy(msg, GetErrorMessage("QueryPerformanceCounter(&endTime) ���� : ", GetLastError()));
		strcpy(buf, "QueryPerformanceCounter ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "QueryPerformanceCounter ����", msg);

		return FALSE;
	}

	/* ī���͸� �ҿ�ð��� ��ȯ�Ѵ�. */
	elapsed = endTime.QuadPart - beginTime.QuadPart;
	elapsed = (__int64)(elapsed / (double)frequency.QuadPart);

	/* ���ð��� ���� �ҿ�ð��� �����ϸ� ���� */
	if(expect == elapsed){
		sprintf(msg, "QueryPerformanceCounter ���� : �ҿ�ð� %d��", expect);
		strcpy(buf, "QueryPerformanceCounter ����");
	
	}else{
		sprintf(msg, "QueryPerformanceCounter ���� : ���ð� %��, �ҿ�ð� %d��", expect, elapsed);
		strcpy(buf, "QueryPerformanceCounter ����");

		result = FALSE;
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "QueryPerformanceCounter ����", msg);

	return result;
}


/**
* BOOL QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency)
* ���� ī������ �󵵸� �˻��Ѵ�. ���� ī������ �󵵴� �ý��� ���ý� �����Ǿ� ������ ��� ���μ������� �ϰ��ȴ�.
* @author : ������  
*
* @param  lpFrequency ���� ���� ī���� �󵵸� �ʴ� ī��Ʈ�ι޴� ������ ���� �������Դϴ�. 
*					  �ϵ��� ���ػ� ���� ī���͸� �������� �ʴ� ����� �Ű� ������ 0.
* @return ����/���� ����
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
		sprintf(msg, "�� ��⿡�� Ÿ�̸� ��� ����\nlpFrequency.QuadPart = %llu", (__int64)lpFrequency.QuadPart);
		strcpy(buf, "Ÿ�̸� ��밡��");

	}else{
		sprintf(msg, GetErrorMessage("QueryPerformanceFrequency ���� : ", GetLastError()));
		strcpy(buf, "Ÿ�̸� ���Ұ�");
		result = FALSE;	
	}

	wresult(__FILE__, __LINE__, __FUNCTION__, buf, "Ÿ�̸� ��밡��", msg);

	return result;
}