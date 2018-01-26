/*
*	�ۼ��� : OQA1 ������
*/

#include "Paging.h"

//�� �������� MakeButton.h�� ���ǵǾ� ����
//int buttonCount; 
//HWND hBtn[MAX_TEST_BUTTON];
//extern const wchar_t funcName[MAX_TEST_BUTTON][TEST_FUNC_LEN];

unsigned int currentPage = 0;

void SelectPage(HWND hWnd, int buttonID) 
{
	int pageNumber = buttonID - PAGE_BUTTON_ID; //Ŭ���� ��������ȣ, 0���� ����
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
	//������ �������� ��Ȱ��ȭ ��Ų��.
	while((hPageBtn[i] != 0) && (i < MAX_PAGE_BUTTON)){
		EnableWindow(hPageBtn[i], TRUE);
		i++;
	}
	EnableWindow(hPageBtn[pageNumber], FALSE);


	//printf("���� �������� %d\n", currentPage);
	//printf("��ư %d ���� %d ���� HIDE�մϴ�..\n", currentPage*buttonPerPage, (currentPage+1)*buttonPerPage - 1);
	//printf("��ư %d ���� %d ���� SHOW�մϴ�..\n", pageNumber*buttonPerPage, (pageNumber+1)*buttonPerPage - 1);
	for(int i=0; i<buttonCount; i++){

		//Ŭ���� �������� ��ư���� ���δ�.
		if((i >= pageNumber*buttonPerPage) && (i <= (pageNumber+1)*buttonPerPage - 1)){ //�� ��쿡�� ��ư�� ������ ��.	
			SetFocus(hBtn[i]);
			ShowWindow(hBtn[i], SW_SHOW);

		}else{
			SetFocus(hBtn[i]);
			ShowWindow(hBtn[i], SW_HIDE);

		}
		currentPage = pageNumber;
		GetWindowRect(hWnd, &rec);
		InvalidateRect(hWnd, &rec, 0); //�������� �� �� �پ���
	}


}
