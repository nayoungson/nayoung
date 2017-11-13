/*
*	�ۼ��� : OQA1 ������
*/

#include "MyUtil.h"

char *GetErrorMessage(const char *str, int errorCode) //�Ҹ�, �����ڵ�
{
	wchar_t errMsg[BUFSIZ]; //char�� �ٲ�� �Ǵ� ���ڿ�
	char *buf = NULL; //char�� ��ȯ�� ���ڿ�
	char *msg = (char *)malloc(sizeof(char)* BUFSIZ); //buf+errMsg
	int i=0;

	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL, errorCode, 0, errMsg, 1024, NULL);

	int iLen = WideCharToMultiByte(CP_ACP, 0, errMsg, -1, buf, 0, NULL, NULL);
	buf = new char[iLen+1];
	WideCharToMultiByte(CP_ACP, 0, errMsg, -1, buf, iLen, NULL, NULL);


	while(buf[i++] != '\n');
	buf[i-2] = '\0';
	
	if(str != NULL){
		strcpy(msg, str);
	}
	strcat(msg, buf);

	return msg;
}
