#ifndef MERGEDWINAPI
#define MERGEDWINAPI

#include <Windows.h>
//#include "Paging.h"
//#include "OS1HeaderList.h"
//#include "OSQA.h"

extern HWND hWnd;
extern HWND hWndPaint;
extern BOOL isManual;

typedef struct _PAINT{
	POINT *point;
	char *color;
	char *shape;
}PAINT;

extern PAINT Paint;


LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
LRESULT CALLBACK WndProc2( HWND, UINT, WPARAM, LPARAM );

#endif