
//LONG __cdecl InterlockedExchange(
//_Inout_ LONG volatile *Target,
//_In_ LONG Value
//);
//Target에 있는 값을 Value에 있는 값으로 원자적 연산을 통해 대입한다.

#include "TestInterlocked.h"

/**
* BOOL InterlockedCompareExchange(LONG volatile *Destination, LONG Exchange, LONG Comparand)
* Destination과 Comparand를 비교하여 같은 경우 Destination에 Excahnge값을 원자적 연산으로 대입한다.
* @author : 손찬영  
*
* @param  Destination 목적값의 포인터
* @param  Exchange 교환할 값
* @param  Comparand 비교할 값
* @return 값 교환 성공/실패 여부
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

	//sprintf(msg, "[TEST 1] : value값이 exchange값으로 변경되지 않는 경우\n");
	//sprintf(msgbuf, "[기존값] *destination : %d, exchange : %d, comparand : %d\n", *destination, exchange, comparand);
	//strcat(msg, msgbuf);
	//InterlockedCompareExchange(destination, exchange, comparand); //(0, 1, 1)

	///*
	//test1 : value값이 exchange값으로 변경되지 않는 경우를 확인
	//*/
	//if(*destination == 0){ //기존의 값이 유지되면 pass
	//	sprintf(msgbuf, "[함수 실행 후] *destination : %d\n", *destination);
	//	
	//}else if(*destination == 1){
	//	sprintf(msg, "FAIL : 값이 변경되었습니다.\n");
	//	result = FALSE;
	//}
	//strcat(msg, msgbuf);

	//wresult(__FILE__,__LINE__ ,"InterlockedCompareExchange", (char *)_itoa(*destination, buf, 10), (char *)_itoa(0, buf, 10), (char *)msg);

	/*
	test2 : value값이 exchange값으로 변경되는 경우를 확인
	*/
	var = 0;
	exchange = 1;
	comparand = 0;

	sprintf(msg, "[TEST 2] : value값이 exchange값으로 변경되는 경우\n");
	sprintf(msgbuf, "[기존값] *destination : %d, exchange : %d, comparand : %d\n", *destination, exchange, comparand);
	strcat(msg, msgbuf);
	InterlockedCompareExchange(destination, exchange, comparand); //(0, 1, 0)

	if(*destination == exchange){
		sprintf(msgbuf, "[함수 실행 후] *destination : %d\n", *destination);
	
	}else if(*destination != exchange){
		sprintf(msgbuf, "FAIL : 값이 변경되었습니다.\n");
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
* Target에 있는 값을 Value에 있는 값으로 원자적 연산을 통해 대입한다.
* @author : 손찬영  
*
* @param  Target 교환되는 값의 포인터
* @param  Value 교환할 값
* @return 값 교환 성공/실패 여부
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

	sprintf(msg, "[기존값] *Target : %d, Value : %d\n", *Target, value);
	InterlockedExchange(Target,value);	

	if(*Target == value){

		sprintf(msgbuf, "값이 정상적으로 변경되었습니다.\n[변경된값] *Target : %d, Value : %d", *Target, value);

	}else{
		sprintf(msgbuf, "값이 변경되지 않았습니다.\n[변경된값] *Target : %d, Value : %d", *Target, value);
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
* Destination과 Comparand를 비교하여 같은 경우 Destination에 Excahnge값을 원자적 연산으로 대입한다(64bit값을 비교).
* @author : 손찬영  
*
* @param  Destination 목적값의 포인터
* @param  Exchange 교환할 값
* @param  Comparand 비교할 값
* @return 값 교환 성공/실패 여부
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

	sprintf(msg, "value값을 exchange값으로 변경\n");
	sprintf(msgbuf, "[기존값] *destination : %lld, exchange : %lld, comparand : %lld\n", *destination, exchange, comparand);
	strcat(msg, msgbuf);
	InterlockedCompareExchange64(destination, exchange, comparand); //(0, 1, 0)

	if(*destination == exchange){
		sprintf(msgbuf, "[함수 실행 후] *destination : %lld\n", *destination);
	
	}else if(*destination != exchange){
		sprintf(msgbuf, "FAIL : 값이 변경되지 않음\n");
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
* 두 개의 32 비트 값을 원자적으로 더한다.
* @author : 손찬영  
*
* @param  Addend 더할 변수에 대한 포인터
* @param  Value 더할 값
* @return 성공/실패 여부
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
	LONG volatile *pAddend = &addend; //더할 값
	LONG value = 1; //더해질 변수

	#ifdef OQADBGPRINT
	puts(__FUNCTION__);
	#endif

	sprintf(msg, "[기존값] *pAddend : %d, Value : %d\n", *pAddend, value);
	InterlockedExchangeAdd(pAddend, value);	

	if(*pAddend == value){

		sprintf(msgbuf, "값이 정상적으로 변경되었습니다.\n[변경된값] *pAddend : %d, Value : %d", *pAddend, value);

	}else{
		sprintf(msgbuf, "값이 변경되지 않았습니다.\n[변경된값] *pAddend : %d, Value : %d", *pAddend, value);
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
* 싱글링크드리스트 앞에 리스트를 원자적으로 삽입한다.
* @author : 손찬영  
*
* @param  ListHead 싱글링크드리스트의 헤드를 나타내는 SLIST_HEADER 구조체의 포인터
* @param  List 삽입할 리스트의 첫번째 엔트리를 나타내는 SLIST_ENTRY 구조체의 포인터 
* @param  ListEnd 삽입할 리스트의 마지막 엔트리를 나타내는 SLIST_ENTRY 구조체의 포인터 
* @param  Count 삽입 할 리스트의 엔트리 수
* @return 성공/실패 여부
*/
BOOL test_InterlockedPushListSList()
{
	BOOL result = TRUE;
	char msg[BUFSIZ] = {0, };
	char buf[BUFSIZ] = {0, };
	DWORD errorCode = 0;

	PSLIST_HEADER pListHeadFirst, pListHeadSecond;
	PSLIST_ENTRY  pFirstEntry, pListEntry;
	PSLIST_ENTRY  pList, pListEnd; //삽입할 리스트의 첫번째 엔트리와 마지막엔트리
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
		strcpy(buf, "pListHead malloc 실패");
		strcpy(msg, buf);
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "pListHead malloc 성공", msg);

        return FALSE;
    }
    InitializeSListHead(pListHeadFirst);
	InitializeSListHead(pListHeadSecond);

	#ifdef OQADBGPRINT
	printf("InitializeSListHead complete.\n");
	#endif

	/*
	 각 링크드리스트에 5개(MAX_ITEM_COUNT/2)의 아이템을 넣는다.
	*/
	for( Count = 1; Count <= (MAX_ITEM_COUNT/2); Count += 1 )
    {
		#ifdef OQADBGPRINT
		printf("Count = %d\n", Count);
		#endif
		//SLIST_ENTRY는 반드시 _aligned_malloc을 이용해 할당하며, MEMORY_ALLOCATION_ALIGNMENT를 사용하도록 한다.
		pProgramItemFirst = (PPROGRAM_ITEM)_aligned_malloc(sizeof(PROGRAM_ITEM), MEMORY_ALLOCATION_ALIGNMENT);
		pProgramItemSecond = (PPROGRAM_ITEM)_aligned_malloc(sizeof(PROGRAM_ITEM), MEMORY_ALLOCATION_ALIGNMENT);
		if( NULL == pProgramItemFirst || NULL == pProgramItemSecond)
		{
			#ifdef OQADBGPRINT
			printf("Memory allocation failed.\n");
			#endif
			strcpy(buf, "pProgramItem malloc 실패");
			strcpy(msg, buf);
			wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "pProgramItem malloc 성공", msg);
			return FALSE;
		}
		
		pProgramItemFirst->Signature = Count;
		pFirstEntry = InterlockedPushEntrySList(pListHeadFirst, &(pProgramItemFirst->ItemEntry)); //첫번째 리스트에 1, 2, 3, 4, 5를 집어넣음
		#ifdef OQADBGPRINT
		printf("First List Push Entry = %p\n", &pProgramItemFirst->ItemEntry);
		#endif
		pProgramItemSecond->Signature = Count+5;
		pFirstEntry = InterlockedPushEntrySList(pListHeadSecond, &(pProgramItemSecond->ItemEntry));  //두번째 리스트에 6, 7, 8, 9, 10을 집어넣음
		#ifdef OQADBGPRINT
		printf("Second List Push Entry = %p\n", &pProgramItemSecond->ItemEntry);
		#endif

		

		if(Count == 1){ //두번째 리스트의 첫번째 아이템
			pList = &(pProgramItemSecond->ItemEntry);
		}
		if(Count == (MAX_ITEM_COUNT/2)){ //두번째 리스트의 마지막 아이템
			pListEnd = &(pProgramItemSecond->ItemEntry);
		}

		//printf("pList = %p, pListEnd = %p\n", pList, pListEnd);

	}

#ifdef OQADBGPRINT
	printf("InterlockedPushListSList 진입 직전\n");
#endif
	pFirstEntry = InterlockedPushListSList(pListHeadFirst, pListEnd, pList, MAX_ITEM_COUNT - (MAX_ITEM_COUNT/2)); //Stack형태로 들어가기 때문에, 마지막아이템이 첫번째 아이템으로 들어간다.

	#ifdef OQADBGPRINT
	printf("InterlockedPushListSList 끝\n");
#endif

	/*
	리스트에서 10개의 아이템을 제거하고 시그니쳐를 출력한다.
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

			strcpy(buf, "리스트가 비어있음");
			strcpy(msg, buf);
			wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "리스트가 비어있지 않음", msg);

			return FALSE;
			//break;
		}
		pProgramItemFirst = (PPROGRAM_ITEM)pListEntry;
		#ifdef OQADBGPRINT
		printf("[Signature is %d]\n", pProgramItemFirst->Signature);
		#endif
		signature[Count] = pProgramItemFirst->Signature;

		// 이 예는 SLIST_ENTRY구조체가 구조의 첫번째 멤버라고 가정한다.
		// 만약 당신의 구조체가 이 컨벤션과 같지 않다면,
		// 당신은 free하기 전 구조체의 시작 주소를 계산해야 한다.

		_aligned_free(pListEntry);
	}

	// 아이템이 비워졌는지 확인한다.
	pListEntry = InterlockedFlushSList(pListHeadFirst);
	pFirstEntry = InterlockedPopEntrySList(pListHeadFirst);
	if (pFirstEntry != NULL)
	{
		#ifdef OQADBGPRINT
		printf("Error: List is not empty.\n");
		#endif

		strcpy(buf, "리스트가 비어있지 않음");
		strcpy(msg, buf);
		wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "리스트가 비어있음", msg);

		return FALSE;
	}

	for( Count = 10; Count >= 1; Count -= 1 ){
		if(signature[Count] != Count){
			result = FALSE;
		}
	}

	if(!result){
		strcpy(buf, "InterlockedPushListSList 실패");
		strcpy(msg, buf);

	}else{
		strcpy(buf, "InterlockedPushListSList 성공");
		strcpy(msg, buf);
	}

	wresult(__FILE__,__LINE__ ,__FUNCTION__, buf, "InterlockedPushListSList 성공", msg);

	return result;
}
