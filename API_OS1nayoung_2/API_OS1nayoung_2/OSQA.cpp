#include "OSQA.h"

char *filePath = (char *)malloc(sizeof(char)*BUFSIZ);
const char *logFileName = "dbg_log.txt";


void wresult(char *fname,int line,char *function, char *result, char *answer,char *message)
{
	
	char final[10];
	int ret;
	static bool isCalled = false;
	errno_t err;
	static FILE *fp = NULL;
	

	if(!isCalled){
		SetFilePath();
	}

	if((err = fopen_s(&fp, filePath ,"a+"))){
		#ifdef OQADBGPRINT
		printf("File Open Error\n");
		printf("���� ���� ��� = %s\n", filePath);
		#endif

		return;
	}
	if(!isCalled){
		#ifdef OQADBGPRINT
		printf("���� ���� ��� = %s\n", filePath);
		#endif
		
		
		fprintf(fp, "[OSQA]\t[%30s]\t[%6s]\t[%30s]\t[%30s]\t[%10s]\t[%50s]\n","�Լ��̸�","����","�������", "������", "�׽�Ʈ���", "�޼�������");
		isCalled = true;
	}
	if(fp != NULL){
		fprintf(fp, "[OSQA]\t[%30s]\t[%6d]\t[%30s]\t[%30s]\t",function,line,result, answer);
	}
	ret = strcmp(result, answer);


	if(ret == 0){
		strcpy_s(final,sizeof(final),"pass");
		DisplayResourceNAMessageBox(message,final);

	}else{
		strcpy_s(final,sizeof(final),"fail");
		DisplayResourceNAMessageBox(message,final);
	}


	fprintf(fp, "[%10s]\t", final);

	fprintf(fp, "[%50s]\n", message);
	fclose(fp);
}

void SetFilePath()
{
	DWORD dwVersion = 0; 
	DWORD dwMinorVersion = 0; 
	char userName[BUFSIZ];
	DWORD userNameSize = BUFSIZ;

	GetUserNameA(userName, &userNameSize);
	dwVersion = GetVersion();

	dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

	if(dwMinorVersion == 2){ //��10
		#ifdef OQADBGPRINT
		printf("��10�Դϴ�..\n");
		#endif
		strcpy(filePath, "C:\\Users\\");
		//strcpy(filePath, "d:\\");
		strcat(filePath, userName);
		strcat(filePath, "\\Desktop\\");
	
		
	}else{ //��7, ����
		#ifdef OQADBGPRINT
		printf("��10�� �ƴմϴ�..\n");
		#endif
		strcpy(filePath, "\\Desktop\\");
	}
	strcat(filePath, logFileName);
}

void DisplayResourceNAMessageBox(char *message,char *result)
{
	//if(isManual == TRUE){
	#ifdef OQADBG
		MessageBoxA(hWnd, message, result, MB_OK);
	#endif
	//}
}
