#ifndef TESTINTERLOCKED
#define TESTINTERLOCKED
#pragma once

#include <Windows.h>
#include <stdio.h>
#include "../OSQA.h"

#define MAX_ITEM_COUNT 10

BOOL test_InterlockedCompareExchange(void);
BOOL test_InterlockedExchange(void);


//MS_PPT
BOOL test_InterlockedCompareExchange64();
BOOL test_InterlockedExchangeAdd();
BOOL test_InterlockedPushListSList();


//test_InterlockedPushListSList 싱글링크드리스트의 아이템
// 구조체는 리스트아이템으로 사용된다.
// 첫번째 멤버는 SLIST_ENTRY 구조체이며, 추가적인 멤버는 데이터로 사용된다.
// 여기서는 데이터를 간단한 signature로 사용했다.
typedef struct _PROGRAM_ITEM {
    SLIST_ENTRY ItemEntry;
    ULONG Signature; 
} PROGRAM_ITEM, *PPROGRAM_ITEM;


#endif