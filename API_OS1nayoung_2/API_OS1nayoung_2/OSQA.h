#ifndef OSQA
#define OSQA
#pragma once

#pragma comment(lib, "Ntdll.lib")

#include <Windows.h>
#include <iostream>
#include <cstring>
#include <WinUser.h>
#include "MergedWinMain.h"

extern char *filePath;
extern const char *logFileName;

#pragma warning (disable:4996)

void DisplayResourceNAMessageBox(char *message,char *result);
void wresult(char *fname,int line,char *function, char *result, char *answer,char *message);
void log(char *fname,int line,char *function, char *result, char *answer,char *message, char *failReason);
void SetFilePath();

#endif


/**
#ifndef OSQA
#define OSQA

#pragma comment(lib, "Ntdll.lib")

#include <Windows.h>
#include <iostream>
#include <cstring>
#include <WinUser.h>
#include "MergedWinMain.h"

#pragma warning (disable:4996)

extern char *filePath;
extern const char *logFileName;

//#define RESULTFILE      "c:\\dbg_log.dat"
#define RESULTFILE      "C:\\Users\\NAYOUNG\\Desktop\\dbg_log.txt"
void DisplayResourceNAMessageBox(char *message,char *result);
void wresult(char *fname,int line,char *testno, char *result, char *answer,char *message);
void log(char *fname,int line,char *function, char *result, char *answer,char *message, char *failReason);
void SetFilePath();

#endif


*/