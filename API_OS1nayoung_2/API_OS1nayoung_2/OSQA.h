#ifndef OSQA
#define OSQA

#pragma comment(lib, "Ntdll.lib")

#include <Windows.h>
#include <iostream>
#include <cstring>
#include <WinUser.h>


//#define RESULTFILE      "c:\\dbg_log.dat"
#define RESULTFILE      "C:\\Users\\NAYOUNG\\Desktop\\dbg_log.txt"
void DisplayResourceNAMessageBox(char *message,char *result);
void wresult(char *fname,int line,char *testno, char *result, char *answer,char *message);

#endif