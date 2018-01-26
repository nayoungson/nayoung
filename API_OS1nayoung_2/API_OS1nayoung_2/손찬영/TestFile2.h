#ifndef TESTFILE2
#define TESTFILE2

#include <Windows.h>
#include "../OSQA.h"
#include "../MyUtil.h"


BOOL test_MoveFileTransactedW();
BOOL test_MoveFileTransactedA();
BOOL test_CopyFileTransactedW();
BOOL test_CopyFileTransactedA();
BOOL test_DeleteFileTransactedW();
BOOL test_DeleteFileTransactedA();
BOOL test_CreateFileTransactedW();
BOOL test_CreateFileTransactedA();

BOOL test_WriteFileGather();

#endif