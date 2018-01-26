
//LONG __cdecl InterlockedExchange(
//_Inout_ LONG volatile *Target,
//_In_ LONG Value
//);
//Target�� �ִ� ���� Value�� �ִ� ������ ������ ������ ���� �����Ѵ�.

#include "TestInterlocked.h"

/**
* BOOL InterlockedCompareExchange(LONG volatile *Destination, LONG Exchange, LONG Comparand)
* Destination�� Comparand�� ���Ͽ� ���� ��� Destination�� Excahnge���� ������ �������� �����Ѵ�.
* @author : ������  
*
* @param  Destination �������� ������
* @param  Exchange ��ȯ�� ��
* @param  Comparand ���� ��
* @return �� ��ȯ ����/���� ����
*/
BOOL test_InterlockedCompareExchange()
{
	LONG volatile var = 0;
	LONG volatile *destination = &var;
	LONG exchange = 1;
	LONG comparand = 1;

	BOOL result = TRUE;

	char msg[BUFSIZ];
	char msgbuf[BUFSIZ];
	char buf[BUFSIZ];
	char expect[BUFSIZ];

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	//sprintf(msg, "[TEST 1] : value���� exchange������ ������� �ʴ� ���\n");
	//sprintf(msgbuf, "[������] *destination : %d, exchange : %d, comparand : %d\n", *destination, exchange, comparand);
	//strcat(msg, msgbuf);
	//InterlockedCompareExchange(destination, exchange, comparand); //(0, 1, 1)

	///*
	//test1 : value���� exchange������ ������� �ʴ� ��츦 Ȯ��
	//*/
	//if(*destination == 0){ //������ ���� �����Ǹ� pass
	//	sprintf(msgbuf, "[�Լ� ���� ��] *destination : %d\n", *destination);
	//	
	//}else if(*destination == 1){
	//	sprintf(msg, "FAIL : ���� ����Ǿ����ϴ�.\n");
	//	result = FALSE;
	//}
	//strcat(msg, msgbuf);

	//wresult(__FILE__,__LINE__ ,"InterlockedCompareExchange", (char *)_itoa(*destination, buf, 10), (char *)_itoa(0, buf, 10), (char *)msg);

	/*
	test2 : value���� exchange������ ����Ǵ� ��츦 Ȯ��
	*/
	var = 0;
	exchange = 1;
	comparand = 0;

	sprintf(msg, "[TEST 2] : value���� exchange������ ����Ǵ� ���\n");
	sprintf(msgbuf, "[������] *destination : %d, exchange : %d, comparand : %d\n", *destination, exchange, comparand);
	strcat(msg, msgbuf);
	InterlockedCompareExchange(destination, exchange, comparand); //(0, 1, 0)

	if(*destination == exchange){
		sprintf(msgbuf, "[�Լ� ���� ��] *destination : %d\n", *destination);
	
	}else if(*destination != exchange){
		sprintf(msgbuf, "FAIL : ���� ����Ǿ����ϴ�.\n");
		result = FALSE;
	}

	strcat(msg, msgbuf);
	sprintf(buf, "%d", *destination);
	sprintf(expect, "%d", exchange);
	wresult(__FILE__,__LINE__ ,"InterlockedCompareExchange", buf, expect, msg);

	return result;
}


/**
* BOOL InterlockedExchange(LONG volatile *Target, LONG Value)
* Target�� �ִ� ���� Value�� �ִ� ������ ������ ������ ���� �����Ѵ�.
* @author : ������  
*
* @param  Target ��ȯ�Ǵ� ���� ������
* @param  Value ��ȯ�� ��
* @return �� ��ȯ ����/���� ����
*/
BOOL test_InterlockedExchange()
{
	LONG volatile var = 0;
	LONG volatile *Target = &var;
	LONG value = 1;

	BOOL result = TRUE;
	char msg[BUFSIZ];
	char msgbuf[BUFSIZ];
	char buf[BUFSIZ];
	char expect[BUFSIZ];

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	sprintf(msg, "[������] *Target : %d, Value : %d\n", *Target, value);
	InterlockedExchange(Target,value);	

	if(*Target == value){

		sprintf(msgbuf, "���� ���������� ����Ǿ����ϴ�.\n[����Ȱ�] *Target : %d, Value : %d", *Target, value);

	}else{
		sprintf(msgbuf, "���� ������� �ʾҽ��ϴ�.\n[����Ȱ�] *Target : %d, Value : %d", *Target, value);
		result = FALSE;
	}
	strcat(msg, msgbuf);

	sprintf(buf, "%d", *Target);
	sprintf(expect, "%d", value);
	wresult(__FILE__,__LINE__ ,"InterlockedExchange", buf, expect, msg);

	return result;
}

/**
* BOOL InterlockedCompareExchange64(LONG volatile *Destination, LONG Exchange, LONG Comparand)
* Destination�� Comparand�� ���Ͽ� ���� ��� Destination�� Excahnge���� ������ �������� �����Ѵ�(64bit���� ��).
* @author : ������  
*
* @param  Destination �������� ������
* @param  Exchange ��ȯ�� ��
* @param  Comparand ���� ��
* @return �� ��ȯ ����/���� ����
*/
BOOL test_InterlockedCompareExchange64()
{
	LONGLONG volatile var = 0;
	LONGLONG volatile *destination = &var;
	LONGLONG exchange = 1;
	LONGLONG comparand = 1;

	BOOL result = TRUE;

	char msg[BUFSIZ];
	char msgbuf[BUFSIZ];
	char buf[BUFSIZ];
	char expect[BUFSIZ];


	var = 0;
	exchange = 1;
	comparand = 0;

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	sprintf(msg, "value���� exchange������ ����\n");
	sprintf(msgbuf, "[������] *destination : %lld, exchange : %lld, comparand : %lld\n", *destination, exchange, comparand);
	strcat(msg, msgbuf);
	InterlockedCompareExchange64(destination, exchange, comparand); //(0, 1, 0)

	if(*destination == exchange){
		sprintf(msgbuf, "[�Լ� ���� ��] *destination : %lld\n", *destination);
	
	}else if(*destination != exchange){
		sprintf(msgbuf, "FAIL : ���� ������� ����\n");
		result = FALSE;
	}

	strcat(msg, msgbuf);
	sprintf(buf, "%lld", *destination);
	sprintf(expect, "%lld", exchange);
	wresult(__FILE__,__LINE__ ,"InterlockedCompareExchange", buf, expect, msg);

	return result;
}


/**
* BOOL InterlockedExchangeAdd(LONG volatile *Addend, LONG Value)
* �� ���� 32 ��Ʈ ���� ���������� ���Ѵ�.
* @author : ������  
*
* @param  Addend ���� ������ ���� ������
* @param  Value ���� ��
* @return ����/���� ����
*/
BOOL test_InterlockedExchangeAdd()
{
	BOOL result = TRUE;
	char msg[BUFSIZ] = {0, };
	char msgbuf[BUFSIZ];
	char buf[BUFSIZ] = {0, };
	char expect[BUFSIZ];
	DWORD errorCode = 0;

	LONG volatile addend = 0;
	LONG volatile *pAddend = &addend; //���� ��
	LONG value = 1; //������ ����

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	sprintf(msg, "[������] *pAddend : %d, Value : %d\n", *pAddend, value);
	InterlockedExchangeAdd(pAddend, value);	

	if(*pAddend == value){

		sprintf(msgbuf, "���� ���������� ����Ǿ����ϴ�.\n[����Ȱ�] *pAddend : %d, Value : %d", *pAddend, value);

	}else{
		sprintf(msgbuf, "���� ������� �ʾҽ��ϴ�.\n[����Ȱ�] *pAddend : %d, Value : %d", *pAddend, value);
		result = FALSE;
	}
	strcat(msg, msgbuf);

	sprintf(buf, "%d", *pAddend);
	sprintf(expect, "%d", value);
	wresult(__FILE__,__LINE__ ,"InterlockedExchange", buf, expect, msg);

	return result;
}


/**
* BOOL InterlockedPushListSList(PSLIST_HEADER ListHead, PSLIST_ENTRY  List, PSLIST_ENTRY  ListEnd, ULONG Count)
* �̱۸�ũ�帮��Ʈ �տ� ����Ʈ�� ���������� �����Ѵ�.
* @author : ������  
*
* @param  ListHead �̱۸�ũ�帮��Ʈ�� ��带 ��Ÿ���� SLIST_HEADER ����ü�� ������
* @param  List ������ ����Ʈ�� ù��° ��Ʈ���� ��Ÿ���� SLIST_ENTRY ����ü�� ������ 
* @param  ListEnd ������ ����Ʈ�� ������ ��Ʈ���� ��Ÿ���� SLIST_ENTRY ����ü�� ������ 
* @param  Count ���� �� ����Ʈ�� ��Ʈ�� ��
* @return ����/���� ����
*/
BOOL test_InterlockedPushListSList()
{
	BOOL result = TRUE;
	char msg[BUFSIZ] = {0, };
	char buf[BUFSIZ] = {0, };
	DWORD errorCode = 0;

	PSLIST_HEADER pListHeadFirst, pListHeadSecond;
	PSLIST_ENTRY  pFirstEntry, pListEntry;
	PSLIST_ENTRY  pList, pListEnd; //������ ����Ʈ�� ù��° ��Ʈ���� ��������Ʈ��
	ULONG         Count;
	PPROGRAM_ITEM pProgramItemFirst, pProgramItemSecond;
	ULONG signature[MAX_ITEM_COUNT + 1] = {0, };

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	pListHeadFirst = (PSLIST_HEADER)_aligned_malloc(sizeof(SLIST_HEADER), MEMORY_ALLOCATION_ALIGNMENT);
	pListHeadSecond = (PSLIST_HEADER)_aligned_malloc(sizeof(SLIST_HEADER), MEMORY_ALLOCATION_ALIGNMENT);
    if( NULL == pListHeadFirst || NULL == pListHeadSecond )
    {
		#ifdef OQADBGPRINT
        printf("Memory allocation failed.\n");
		#endif
		strcpy(buf, "pListHead malloc ����");
		strcpy(msg, buf);
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "pListHead malloc ����", msg);

        return FALSE;
    }
    InitializeSListHead(pListHeadFirst);
	InitializeSListHead(pListHeadSecond);

	#ifdef OQADBGPRINT
	printf("InitializeSListHead complete.\n");
	#endif

	/*
	 �� ��ũ�帮��Ʈ�� 5��(MAX_ITEM_COUNT/2)�� �������� �ִ´�.
	*/
	for( Count = 1; Count <= (MAX_ITEM_COUNT/2); Count += 1 )
    {
		#ifdef OQADBGPRINT
		printf("Count = %d\n", Count);
		#endif
		//SLIST_ENTRY�� �ݵ�� _aligned_malloc�� �̿��� �Ҵ��ϸ�, MEMORY_ALLOCATION_ALIGNMENT�� ����ϵ��� �Ѵ�.
		pProgramItemFirst = (PPROGRAM_ITEM)_aligned_malloc(sizeof(PROGRAM_ITEM), MEMORY_ALLOCATION_ALIGNMENT);
		pProgramItemSecond = (PPROGRAM_ITEM)_aligned_malloc(sizeof(PROGRAM_ITEM), MEMORY_ALLOCATION_ALIGNMENT);
		if( NULL == pProgramItemFirst || NULL == pProgramItemSecond)
		{
			#ifdef OQADBGPRINT
			printf("Memory allocation failed.\n");
			#endif
			strcpy(buf, "pProgramItem malloc ����");
			strcpy(msg, buf);
			wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "pProgramItem malloc ����", msg);
			return FALSE;
		}
		
		pProgramItemFirst->Signature = Count;
		pFirstEntry = InterlockedPushEntrySList(pListHeadFirst, &(pProgramItemFirst->ItemEntry)); //ù��° ����Ʈ�� 1, 2, 3, 4, 5�� �������
		#ifdef OQADBGPRINT
		printf("First List Push Entry = %p\n", &pProgramItemFirst->ItemEntry);
		#endif
		pProgramItemSecond->Signature = Count+5;
		pFirstEntry = InterlockedPushEntrySList(pListHeadSecond, &(pProgramItemSecond->ItemEntry));  //�ι�° ����Ʈ�� 6, 7, 8, 9, 10�� �������
		#ifdef OQADBGPRINT
		printf("Second List Push Entry = %p\n", &pProgramItemSecond->ItemEntry);
		#endif

		

		if(Count == 1){ //�ι�° ����Ʈ�� ù��° ������
			pList = &(pProgramItemSecond->ItemEntry);
		}
		if(Count == (MAX_ITEM_COUNT/2)){ //�ι�° ����Ʈ�� ������ ������
			pListEnd = &(pProgramItemSecond->ItemEntry);
		}

		//printf("pList = %p, pListEnd = %p\n", pList, pListEnd);

	}

#ifdef OQADBGPRINT
	printf("InterlockedPushListSList ���� ����\n");
#endif
	pFirstEntry = InterlockedPushListSList(pListHeadFirst, pListEnd, pList, MAX_ITEM_COUNT - (MAX_ITEM_COUNT/2)); //Stack���·� ���� ������, �������������� ù��° ���������� ����.

	#ifdef OQADBGPRINT
	printf("InterlockedPushListSList ��\n");
#endif

	/*
	����Ʈ���� 10���� �������� �����ϰ� �ñ״��ĸ� ����Ѵ�.
	*/
	for( Count = 10; Count >= 1; Count -= 1 )
	{
		#ifdef OQADBGPRINT
		printf("Pop Count = %d\n", Count);
		#endif
		pListEntry = InterlockedPopEntrySList(pListHeadFirst);
		printf("Pop pListEntry = %p\n", pListEntry);

		if( NULL == pListEntry )
		{
			#ifdef OQADBGPRINT
			printf("List is empty.\n");
			#endif

			strcpy(buf, "����Ʈ�� �������");
			strcpy(msg, buf);
			wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "����Ʈ�� ������� ����", msg);

			return FALSE;
			//break;
		}
		pProgramItemFirst = (PPROGRAM_ITEM)pListEntry;
		#ifdef OQADBGPRINT
		printf("[Signature is %d]\n", pProgramItemFirst->Signature);
		#endif
		signature[Count] = pProgramItemFirst->Signature;

		// �� ���� SLIST_ENTRY����ü�� ������ ù��° ������ �����Ѵ�.
		// ���� ����� ����ü�� �� �����ǰ� ���� �ʴٸ�,
		// ����� free�ϱ� �� ����ü�� ���� �ּҸ� ����ؾ� �Ѵ�.

		_aligned_free(pListEntry);
	}

	// �������� ��������� Ȯ���Ѵ�.
	pListEntry = InterlockedFlushSList(pListHeadFirst);
	pFirstEntry = InterlockedPopEntrySList(pListHeadFirst);
	if (pFirstEntry != NULL)
	{
		#ifdef OQADBGPRINT
		printf("Error: List is not empty.\n");
		#endif

		strcpy(buf, "����Ʈ�� ������� ����");
		strcpy(msg, buf);
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "����Ʈ�� �������", msg);

		return FALSE;
	}

	for( Count = 10; Count >= 1; Count -= 1 ){
		if(signature[Count] != Count){
			result = FALSE;
		}
	}

	if(!result){
		strcpy(buf, "InterlockedPushListSList ����");
		strcpy(msg, buf);

	}else{
		strcpy(buf, "InterlockedPushListSList ����");
		strcpy(msg, buf);
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "InterlockedPushListSList ����", msg);

	return result;
}
