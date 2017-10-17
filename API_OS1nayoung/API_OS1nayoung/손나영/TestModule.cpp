#include "TestModule.h"
#include <TlHelp32.h>
#include <Psapi.h>


/**
	loads and executes an application
	only with 16bit version. CreateProcess �Լ� ���.
	*/
BOOL test_LoadModule(){

	LPVOID lp;

	int wresult_value=0;
	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

#ifdef OQADBGPRINT
	printf("test_LoadModule\n");
#endif

		
	// succeeds �� return value is greater than 31
	if(LoadModule("Notepad.exe", &lp)>31){
		strcpy(meg, " LoadModule() : PASS \n\n Notepad loaded");
		wresult_value=1;
	}else

		strcpy(meg, GetErrorMessage("  LoadModule() : FAIL \n\n 16bit������ �����Ǵ� �Լ��Դϴ�.\n LoadModule ��� CreateProcess �Լ��� ����� �� �ֽ��ϴ�.\n\n Error Message :", GetLastError()));
	sprintf(buf, "%d", wresult_value);
	wresult(__FILE__, __LINE__, "LoadModule", buf, "1", meg);

	return true;
}

/**
		  ���μ����� ������ first ��⿡ ���� ���� ����
*/

BOOL test_Module32FirstW(){   //ù ��° ���� : CreateToolhelp32Snapshot �Լ��� �ҷ��;� �� 
	HANDLE hshot = NULL;
	BOOL result;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_Module32FirstW\n");
	#endif
	MODULEENTRY32 me32 = {0};
	me32.dwSize = sizeof( MODULEENTRY32 );

	hshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
	result = Module32FirstW(hshot, &me32);

	if(result){
		sprintf(meg, " Module32FirstW : PASS \n\n CreateToolhelp32Snapshot()�� first ��� ���� ���� \n first entry �� copy to the buffer");
		strcpy(buf, "SUCCESS");
	}else{
		CloseHandle(hshot);
		
	}
	wresult(__FILE__, __LINE__, "Module32FirstW", buf, "SUCCESS", meg);  
	return true;
}

BOOL test_Module32NextW(){   // ù ��° ���� : CreateToolhelp32Snapshot �Լ��� �ҷ��;� ��
	HANDLE hshot = NULL;
	BOOL result;

	char buf[BUFSIZ];
	char meg[BUFSIZ] = "FAIL";

	#ifdef OQADBGPRINT
	printf("test_Module32NextW\n");
	#endif
	MODULEENTRY32 me32 = {0};
	me32.dwSize = sizeof( MODULEENTRY32 );

	hshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
	result = Module32NextW(hshot, &me32);

	if(result){
		sprintf(meg, "Module32NextW : PASS \n\n CreateToolhelp32Snapshot()�� next ��� ���� ���� \n next entry �� copy to the buffer");
		strcpy(buf, "SUCCESS");
	}else{
		CloseHandle(hshot);
	}
	wresult(__FILE__, __LINE__, "Module32FirstW", buf, "SUCCESS", meg);  
	return true;
}



/**
BOOL test_K32GetModuleFileNameExW(){

    HMODULE hMods[1024];
    HANDLE hProcess;
    DWORD cbNeeded;
    unsigned int i;

    // Print the process identifier.

    printf("\nProcess ID: %u\n", processID);

    // Get a handle to the process.

    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
        PROCESS_VM_READ,
        FALSE, processID);
    if (NULL == hProcess)
        return 1;

    // Get a list of all the modules in this process.

    DWORD cbCurrent = sizeof(hMods);

    if (EnumProcessModules(hProcess, hMods, cbCurrent, &cbNeeded))
    {
        DWORD cbAllowed = min(cbCurrent, cbNeeded);                   

        for (i = 0; i < (cbAllowed / sizeof(HMODULE)); i++)
        {
            TCHAR szModName[MAX_PATH];

            // Get the full path to the module's file.

            if (GetModuleFileNameEx(hProcess, hMods[i], szModName,
                sizeof(szModName) / sizeof(TCHAR)))
            {
                // Print the module name and handle value.

                _tprintf(TEXT("\t%s (0x%08X)\n"), szModName, hMods[i]);
            }
        }
    }

    // Release the handle to the process.

    CloseHandle(hProcess);

    return 0;
}

	return true;
}
*/


