/*
*	작성자 : OQA1 손찬영
*/

#include "Paging.h"

//이 변수들은 MakeButton.h에 정의되어 있음
//int buttonCount; 
//HWND hBtn[MAX_TEST_BUTTON];
//extern const wchar_t funcName[MAX_TEST_BUTTON][TEST_FUNC_LEN];

unsigned int currentPage = 0;

void SelectPage(HWND hWnd, int buttonID) 
{
	int pageNumber = buttonID - PAGE_BUTTON_ID; //클릭한 페이지번호, 0부터 시작
	int buttonPerPage = BUTTON_PER_PAGE;
	int i=0;
	RECT rec;
	
	if(pageNumber < 0){
		pageNumber = 0;
	}
	if(pageNumber > pageCount - 1){ 
		//printf("pageNumber = %d, pageCount = %d", pageNumber, pageCount);
		pageNumber = pageCount - 1;
	}
	//선택한 페이지를 비활성화 시킨다.
	while((hPageBtn[i] != 0) && (i < MAX_PAGE_BUTTON)){
		EnableWindow(hPageBtn[i], TRUE);
		i++;
	}
	EnableWindow(hPageBtn[pageNumber], FALSE);


	//printf("기존 페이지는 %d\n", currentPage);
	//printf("버튼 %d 부터 %d 까지 HIDE합니다..\n", currentPage*buttonPerPage, (currentPage+1)*buttonPerPage - 1);
	//printf("버튼 %d 부터 %d 까지 SHOW합니다..\n", pageNumber*buttonPerPage, (pageNumber+1)*buttonPerPage - 1);
	for(int i=0; i<buttonCount; i++){

		//클릭한 페이지의 버튼들을 보인다.
		if((i >= pageNumber*buttonPerPage) && (i <= (pageNumber+1)*buttonPerPage - 1)){ //이 경우에는 버튼이 보여야 함.	
			SetFocus(hBtn[i]);
			ShowWindow(hBtn[i], SW_SHOW);

		}else{
			SetFocus(hBtn[i]);
			ShowWindow(hBtn[i], SW_HIDE);

		}
		currentPage = pageNumber;
		GetWindowRect(hWnd, &rec);
		InvalidateRect(hWnd, &rec, 0); //깜빡임이 좀 더 줄어든다
	}


}
