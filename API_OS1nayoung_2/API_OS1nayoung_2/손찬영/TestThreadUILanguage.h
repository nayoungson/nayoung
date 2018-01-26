#ifndef TESTTHREADUILANGUAGE
#define TESTTHREADUILANGUAGE
#pragma once


#include <Windows.h>
#include <stdio.h>
#include "../MyUtil.h"
#include "../OSQA.h"

BOOL test_GetThreadUILanguage();
BOOL test_SetThreadUILanguage();

BOOL test_GetThreadPreferredUILanguages();
BOOL test_SetThreadPreferredUILanguages();
#endif