#include "TestSurface.h"

#include <winddi.h>

BOOL test_EngCreateDeviceSurface(){
	
	
	DHSURF dhsurf;
	SIZEL sizl;
	ULONG iFormatCompat;


	if(EngCreateDeviceSurface(dhsurf, sizl, iFormatCompat) != 0)
		printf("성공");
	else
		printf("실패");


	return true;
}