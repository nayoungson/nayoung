#include "OSQA.h"

void wresult(char *fname,int line,char *function, char *result, char *answer,char *message)
{
        FILE *fp;
        char final[10];
		int ret;
		char *pValue2=NULL;
	    
        fopen_s(&fp,RESULTFILE ,"a");
				

		fprintf(fp, "[OSQA][%20s][%4d][%10s][%10s]",function,line,result, answer);
        ret = strcmp(result, answer);
        if(ret == 0){
				  strcpy_s(final,sizeof(final),"pass");
				  DisplayResourceNAMessageBox(message,final);
              }else{
			      strcpy_s(final,sizeof(final),"fail");
				  DisplayResourceNAMessageBox(message,final);
              }
       fprintf(fp, "[%8s]\n", final);
	   fclose(fp);
   

}


void DisplayResourceNAMessageBox(char *message,char *result)
{
	int msgboxID = MessageBoxA(0, message, result, 0);
}