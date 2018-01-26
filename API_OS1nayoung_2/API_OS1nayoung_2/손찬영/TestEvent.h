#ifndef TESTEVENT
#define TESTEVENT

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"

BOOL test_OpenEventW();
BOOL test_PulseEvent();

BOOL test_CreateEventExW();
BOOL test_CreateEventExA();

DWORD WINAPI ThreadFirst(LPVOID temp);
DWORD WINAPI ThreadSecond(LPVOID temp);
DWORD WINAPI ThreadThird(LPVOID temp);

//HANDLE hEvent;

typedef struct _THREADEVENT{
	HANDLE hEvent;
	DWORD nowSecond[3];
}THREADEVENT;

#endif