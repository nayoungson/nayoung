#ifndef OSQA
#define OSQA
#pragma once

#include <Windows.h>
#include <iostream>
#include <cstring>
#include <WinUser.h>

//#define RESULTFILE      "c:\\dbg_log.dat"   //wine
#define RESULTFILE      "C:\\Users\\Tmax\\Desktop\\dbg_log.txt"  //win10

void DisplayResourceNAMessageBox(char *message,char *result);
void wresult(char *fname,int line,char *testno, char *result, char *answer,char *message);

#endif