#include "TestEvent.h"


/**
* HANDLE OpenEventW(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCTSTR lpName)
* ������ ���� �̺�Ʈ ��ü�� ����.
* @author : ������  
*
* @param  dwDesiredAccess �̺�Ʈ ��ü�� ���� �׼���
* @param  bInheritHandle �� ���� TRUE �̸��� ���μ������� ���� �� ���μ����� �ڵ��� ���
* @param  lpName ������ �̺�Ʈ�� �̸�
* @return �Լ��� �����ϸ� ��ȯ ���� �̺�Ʈ ��ü�� ���� �ڵ�, �����ϸ� NULL
*/
BOOL test_OpenEventW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;

	HANDLE hEvent = NULL;
	HANDLE hEventCreate = NULL;
	//hEvent = OpenEventW(EVENT_ALL_ACCESS, FALSE, L"MyEvent");
	
	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	///*
	//[TEST 1] �������� �ʴ� �̺�Ʈ�� ���� �õ�
	//*/
	//#ifdef OQADBG
	//MessageBoxA(NULL, "[TEST 1]\n�������� �ʴ� �̺�Ʈ ������ �õ��մϴ�.", "test_OpenEventW", MB_OK);
	//#endif
	//hEvent = OpenEventW(EVENT_ALL_ACCESS | EVENT_MODIFY_STATE, FALSE, L"MyEvent");
	//if(hEvent != NULL){ // �̺�Ʈ ���� ����
	//	sprintf(msg, "hEvent = %d", hEvent);
	//	strcpy(buf, "Event Open ����");

	//}else if(errorCode=GetLastError()){ // �̺�Ʈ ���� ����
	//	strcpy(msg, GetErrorMessage("OpenEvent ���� : ", errorCode));
	//	strcpy(buf, "Event Open ����");


	//}else{

	//}
	//wresult(__FILE__,__LINE__ ,"OpenEventW", buf, "Event Open ����", msg);

	/*
	[TEST 2] �̺�Ʈ�� �����ϰ� ���� Ȯ��
	*/
	#ifdef OQADBG
	MessageBoxA(NULL, "[TEST 2]\n�̺�Ʈ�� �����ϰ� ������ �õ��մϴ�.", "test_OpenEventW", MB_OK);
	#endif
	hEventCreate = CreateEvent(NULL, FALSE, FALSE, L"MyEvent");
	if(hEventCreate == NULL){ //�̺�Ʈ ���� ����
		strcpy(msg, GetErrorMessage("�̺�Ʈ ���� ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,"OpenEventW", msg, "Event ���� ����", msg);

		return FALSE;
	}
	hEvent = OpenEventW(EVENT_ALL_ACCESS | EVENT_MODIFY_STATE, FALSE, L"MyEvent");
	if(hEvent != NULL){ // �̺�Ʈ ���� ����
		sprintf(msg, "Event Open ���� : hEvent = %d", hEvent);
		strcpy(buf, "Event Open ����");

	}else if(errorCode=GetLastError()){
		strcpy(msg, GetErrorMessage("OpenEvent ���� : ", errorCode));
		strcpy(buf, "Event Open ����");
		result = FALSE;	

	}else{ //�˼����� ����
		sprintf(msg, "�� �� ���� ����\nhEvent = %d\nerrorCode = %d", hEvent, errorCode);
		strcpy(buf, msg);
		result = FALSE;	
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "Event Open ����", msg);

	CloseHandle(hEvent);
	CloseHandle(hEventCreate);

	return result;
}


/**
* BOOL PulseEvent(HANDLE hEvent)
* ������ �̺�Ʈ ��ü�� ��ȣ ���·� ���� �� ���� ������ ���� ������� �����带 ���� �� �Ŀ� ��ȣ�� ��ȣ������ ���·� �ٽ� �����Ѵ�. 
�� �Լ��� �ŷ��� �� �����Ƿ� ������� �ʾƾ� ��.
* @author : ������  
*
* @param  hEvent �̺�Ʈ ��ü�� ���� �ڵ�
* @return ����/���� ����
*/
BOOL test_PulseEvent()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	DWORD errorCode=0;

	HANDLE hEventCreate = NULL;
	HANDLE hEvent = NULL;
	HANDLE hThread[3];
	DWORD exitCode[3] = {0, 0, 0};
	DWORD ThreadID;

	THREADEVENT ret;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	hEventCreate = CreateEvent(NULL, TRUE, FALSE, NULL); //���� �̺�Ʈ(TRUE), ���ȣ����(FALSE)

	if(hEventCreate == NULL){ //�̺�Ʈ ���� ����
		strcpy(msg, GetErrorMessage("�̺�Ʈ ���� ���� : ", GetLastError()));
		wresult(__FILE__,__LINE__ ,__FUNCTION__, msg, "Event ���� ����", msg);

		return FALSE;
	}

	hEvent = hEventCreate;
	#ifdef OQADBGPRINT
	printf("test_PulseEvent hEvent = %d\n", hEvent);
	#endif

	ResetEvent(hEvent); //��ȣ�� ���ȣ���·� ����

	ret.hEvent = hEvent;

	hThread[0] = CreateThread(NULL, 0, ThreadFirst, &ret, 0, &ThreadID);
	hThread[1] = CreateThread(NULL, 0, ThreadSecond, &ret, 0, &ThreadID);
	hThread[2] = CreateThread(NULL, 0, ThreadThird, &ret, 0, &ThreadID);

	//CloseHandle(hEvent); 

	while(TRUE){ //��� ������ ������� busy waiting
		//printf("while��\n");
		for(int i=0; i<3; i++){
			GetExitCodeThread(hThread[i], &exitCode[i]);
		}

		if((exitCode[0] != STILL_ACTIVE) && (exitCode[1] != STILL_ACTIVE) && (exitCode[2] != STILL_ACTIVE)){
			break;
		}
	}
	//Sleep(SLEEP_SECOND * 1000);

	#ifdef OQADBGPRINT
	printf("while�� ����\n");
	#endif

	if(((ret.nowSecond[0] + SLEEP_SECOND)%60) == (ret.nowSecond[1]%60)){
		sprintf(msg, "PulseEvent ���� : ������1 �ð� : %lu\n������2 �ð� : %lu", ret.nowSecond[0], ret.nowSecond[1]);
		strcpy(buf, "PulseEvent ����");
	
	}else{
		sprintf(msg, "PulseEvent ����\n������1 �ð� : %lu\n������2 �ð� : %lu", ret.nowSecond[0], ret.nowSecond[1]);
		strcpy(buf, "PulseEvent ����");
		result = FALSE;	
	}
	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "PulseEvent ����", msg);

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hThread[2]);
	
	return result;
}

DWORD WINAPI ThreadFirst(LPVOID temp)
{
	THREADEVENT *threadReturn;
	SYSTEMTIME systemTimeNow;
	
	threadReturn = (THREADEVENT *)temp;
	#ifdef OQADBGPRINT
	printf("ThreadFirst hEvent = %d\n", threadReturn->hEvent);
	#endif

	#ifdef OQADBGPRINT
	printf("ù��° �����尡 Event�� set�մϴ�.\n3�� �ڿ� Thread2, Thread3�� ����� ����");
	#endif

	GetSystemTime(&systemTimeNow); //���� �ð� Ȯ��
	Sleep((SLEEP_SECOND) * 1000); //3�� ����
	
	#ifdef OQADBGPRINT
	printf("���� ����\n");
	#endif

	//SetEvent(hEvent); //��ȣ���·� ����
	#ifdef OQADBGPRINT
	printf("ù��° �����尡 PulseEvent�մϴ�.\n");
	#endif
	PulseEvent(threadReturn->hEvent);
	threadReturn->nowSecond[0] = systemTimeNow.wSecond;
	
	return systemTimeNow.wSecond;
}
DWORD WINAPI ThreadSecond(LPVOID temp)
{
	//HANDLE hEvent = (HANDLE)temp;
	THREADEVENT *threadReturn;
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	SYSTEMTIME systemTimeNow;

	threadReturn = (THREADEVENT *)temp;
	#ifdef OQADBGPRINT
	printf("ThreadSecond hEvent = %d\n", threadReturn->hEvent);
	#endif

	if(WaitForSingleObject(threadReturn->hEvent, INFINITE) == WAIT_FAILED){
		sprintf(msg, GetErrorMessage("Thread2 WaitForSingleObject ���� : ",GetLastError()));
		strcpy(buf, "ThreadSecond WaitForSingleObject ����");
		#ifdef OQADBGPRINT
		printf("%s\n", msg);
		#endif
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf,  "WaitForSingleObject ����", msg);
		return FALSE;
	}
	//����ð� �����ؼ� �� �ð��� Ȯ��
	GetSystemTime(&systemTimeNow); //���� �ð� Ȯ��
	threadReturn->nowSecond[1] = systemTimeNow.wSecond;

	#ifdef OQADBGPRINT
	printf("�ι�° �����尡 �Ͼ�ϴ�.\n");
	#endif
	
	return systemTimeNow.wSecond;
}
DWORD WINAPI ThreadThird(LPVOID temp)
{
	THREADEVENT *threadReturn;
	char msg[BUFSIZ];
	char buf[BUFSIZ];
	SYSTEMTIME systemTimeNow;

	threadReturn = (THREADEVENT *)temp;
	#ifdef OQADBGPRINT
	printf("ThreadThird hEvent = %d\n", threadReturn->hEvent);
	#endif
	if(WaitForSingleObject(threadReturn->hEvent, INFINITE) == WAIT_FAILED){
		sprintf(msg, GetErrorMessage("Thread3 WaitForSingleObject ���� : ",GetLastError()));
		strcpy(buf, "ThreadThird WaitForSingleObject ����");
		#ifdef OQADBGPRINT
		printf("%s\n", msg);
		#endif
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf,  "WaitForSingleObject ����", msg);

		return FALSE;
	}
	
	GetSystemTime(&systemTimeNow); //���� �ð� Ȯ��
	threadReturn->nowSecond[2] = systemTimeNow.wSecond;

	#ifdef OQADBGPRINT
	printf("����° �����尡 �Ͼ�ϴ�.\n");
	#endif
	
	return systemTimeNow.wSecond;
}


/**
* HANDLE CreateEventExW(LPSECURITY_ATTRIBUTES lpEventAttributes, LPCTSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess)
* ���� �Ǵ� ������ ���� �̺�Ʈ ��ü�� ����ų� ����.
* @author : ������  
*
* @param  lpEventAttributes SECURITY_ATTRIBUTES ����ü�� ���� ������
* @param  lpName �̺�Ʈ ��ü�� �̸�
* @param  dwFlags CREATE_EVENT_INITIAL_SET �Ǵ� CREATE_EVENT_MANUAL_RESET
* @param  dwDesiredAccess �̺�Ʈ ��ü�� �׼��� ����ũ
* @return �Լ��� �����ϸ� ��ȯ ���� �̺�Ʈ ��ü�� ���� �ڵ�, �����ϸ� ��ȯ ���� NULL
*/
BOOL test_CreateEventExW()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hEventCreate = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* ó�� SetEvent�ϴ� ���� ���� */
	if(SetEvent(hEventCreate)){
		strcpy(msg, "�̺�Ʈ ���� ���� SetEvent�� �����ؾ� �մϴ�.");
		strcpy(buf, "SetEvent ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetEvent ����", msg);

		return FALSE;
	}
	hEventCreate = CreateEventExW(NULL, NULL, CREATE_EVENT_INITIAL_SET, EVENT_ALL_ACCESS);

	/*�̺�Ʈ ���� �� SetEvent �� �����ϴ� ���� Ȯ���� */
	if((hEventCreate != NULL) && SetEvent(hEventCreate)){ 
		sprintf(msg, "CreateEventExW ���� : hEventCreate = %d", hEventCreate);
		strcpy(buf, "CreateEventExW ����");
		
	}else{ //�̺�Ʈ ���� ����
		strcpy(msg, GetErrorMessage("CreateEventExW ���� : ", GetLastError()));
		strcpy(buf, "CreateEventExW ����");

		result = FALSE;
		
	}
	

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateEventExW ����", msg);

	return result;
}

/**
* HANDLE CreateEventExA(LPSECURITY_ATTRIBUTES lpEventAttributes, LPCTSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess)
* ���� �Ǵ� ������ ���� �̺�Ʈ ��ü�� ����ų� ����.
* @author : ������  
*
* @param  lpEventAttributes SECURITY_ATTRIBUTES ����ü�� ���� ������
* @param  lpName �̺�Ʈ ��ü�� �̸�
* @param  dwFlags CREATE_EVENT_INITIAL_SET �Ǵ� CREATE_EVENT_MANUAL_RESET
* @param  dwDesiredAccess �̺�Ʈ ��ü�� �׼��� ����ũ
* @return �Լ��� �����ϸ� ��ȯ ���� �̺�Ʈ ��ü�� ���� �ڵ�, �����ϸ� ��ȯ ���� NULL
*/
BOOL test_CreateEventExA()
{
	BOOL result = TRUE;	
	char msg[BUFSIZ];
	char buf[BUFSIZ];

	HANDLE hEventCreate = NULL;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	/* ó�� SetEvent�ϴ� ���� ���� */
	if(SetEvent(hEventCreate)){
		strcpy(msg, "�̺�Ʈ ���� ���� SetEvent�� �����ؾ� �մϴ�.");
		strcpy(buf, "SetEvent ����");

		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "SetEvent ����", msg);

		return FALSE;
	}
	hEventCreate = CreateEventExA(NULL, NULL, CREATE_EVENT_INITIAL_SET, EVENT_ALL_ACCESS);

	/*�̺�Ʈ ���� �� SetEvent �� �����ϴ� ���� Ȯ���� */
	if((hEventCreate != NULL) && SetEvent(hEventCreate)){ 
		sprintf(msg, "CreateEventExA ���� : hEventCreate = %d", hEventCreate);
		strcpy(buf, "CreateEventExA ����");
		
	}else{ //�̺�Ʈ ���� ����
		strcpy(msg, GetErrorMessage("CreateEventExA ���� : ", GetLastError()));
		strcpy(buf, "CreateEventExA ����");

		result = FALSE;
		
	}
	

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "CreateEventExA ����", msg);

	return result;
}