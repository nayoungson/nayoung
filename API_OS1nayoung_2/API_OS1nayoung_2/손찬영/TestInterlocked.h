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


//test_InterlockedPushListSList �̱۸�ũ�帮��Ʈ�� ������
// ����ü�� ����Ʈ���������� ���ȴ�.
// ù��° ����� SLIST_ENTRY ����ü�̸�, �߰����� ����� �����ͷ� ���ȴ�.
// ���⼭�� �����͸� ������ signature�� ����ߴ�.
typedef struct _PROGRAM_ITEM {
    SLIST_ENTRY ItemEntry;
    ULONG Signature; 
} PROGRAM_ITEM, *PPROGRAM_ITEM;


#endif