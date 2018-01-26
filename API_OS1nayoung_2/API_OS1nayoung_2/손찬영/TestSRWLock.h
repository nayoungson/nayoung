#ifndef TESTSRWLOCK
#define TESTSRWLOCK

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

#define THREAD_CNT 2


//extern SRWLOCK wait[THREAD_CNT];

typedef struct _THREADSRWLOCK{
	PSRWLOCK pSRWLock;
	int threadNum;
	volatile unsigned long long int data;
	
}THREADSRWLOCK;

BOOL test_InitializeSRWLock();

BOOL test_AcquireSRWLockShared();
BOOL test_AcquireSRWLockExclusive();
BOOL test_TryAcquireSRWLockShared();
BOOL test_TryAcquireSRWLockExclusive();
BOOL test_ReleaseSRWLockShared();
BOOL test_ReleaseSRWLockExclusive();

DWORD WINAPI ThreadReader(LPVOID temp);
DWORD WINAPI ThreadReader2(LPVOID temp);
DWORD WINAPI ThreadWriter(LPVOID temp);
//DWORD WINAPI ThreadWriter2(LPVOID temp);


#endif