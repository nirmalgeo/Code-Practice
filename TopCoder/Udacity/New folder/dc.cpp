#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <DbgHelp.h>
#include <iostream>
#define TRACE_MAX_STACK_FRAMES 1024
#define TRACE_MAX_FUNCTION_NAME_LENGTH 1024

void printStackTrace(HANDLE);

// To ensure correct resolution of symbols, add Psapi.lib to TARGETLIBS
// and compile with -DPSAPI_VERSION=1

void PrintProcessNameAndID( DWORD processID )
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    // Get a handle to the process.

   /* HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processID );
*/

	 HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS,
                                   FALSE, processID );

	 hProcess = NULL;
	  printStackTrace( hProcess);
	  return;

    // Get the process name.

    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), 
             &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName, 
                               sizeof(szProcessName)/sizeof(TCHAR) );
        }
    }

	if( !_tcscmp(szProcessName, TEXT("<unknown>")))
	{
		CloseHandle(hProcess);
		return;

	}

    // Print the process name and identifier.
	if( _tcscmp(szProcessName, _T("Exe_Application.exe")) == 0 )
	 {
    _tprintf( TEXT("\n \n *******PROCESS %s  (PID: %u)********\n"), szProcessName, processID );
	 unsigned int   i;
     void         * stack[ 100 ];
     unsigned short frames;
     SYMBOL_INFO  * symbol;
    // HANDLE         process;

	 //process = GetCurrentProcess();
	 //GetStartupInfo
	 
		 printStackTrace( hProcess);
	 }

	/*
		 SymInitialize( hProcess, NULL, TRUE );
		 frames               = CaptureStackBackTrace( 0, 100, stack, NULL );
		 symbol               = ( SYMBOL_INFO * )calloc( sizeof( SYMBOL_INFO ) + 256 * sizeof( char ), 1 );
		 symbol->MaxNameLen   = 255;
		 symbol->SizeOfStruct = sizeof( SYMBOL_INFO );

		 for( i = 0; i < frames; i++ )
		 {
			 SymFromAddr( hProcess, ( DWORD64 )( stack[ i ] ), 0, symbol );

			 printf( "\t %i: %s - 0x%0X %0X\n", frames - i - 1, symbol->Name, symbol->Address, symbol->ModBase );
		 }

		 free( symbol );
	 }

	 else
	 { 
		 printStackTrace(hProcess);
	 }


*/


    // Release the handle to the process.

    CloseHandle( hProcess );
	//Sleep(1000);
}





void printStackTrace( HANDLE process)
{
    void *stack[TRACE_MAX_STACK_FRAMES];
	DWORD64 baseAddress =0;
   //process = GetCurrentProcess();
	//PCSTR szImageName= "Exe_Application.exe";
	std::cout << "test";

	  process = CreateFile(_T("C:\\Users\\nireapen\\documents\\visual studio 2012\\Projects\\Exe_Application\\x64\\Debug\\Exe_Application.exe"),GENERIC_READ, 0, NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);
	//process = CreateFile(_T("Exe_Application.exe"),GENERIC_READ, 0, NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);
	std::cout << "\n Error in create file:" << GetLastError() ;
	Sleep(2000);
	TCHAR *szImageName = TEXT("Exe_Application.exe");
	//PCSTR szImageName= "C:\\Users\\nireapen\\documents\\visual studio 2012\\Projects\\Exe_Application\\x64\\Debug\\Exe_Application.exe";
	SymInitialize(process, NULL, TRUE);
	//if( ! SymLoadModuleEx(process, NULL, (PCSTR)szImageName, NULL, baseAddress, 0, NULL, 0))
	//{
	//	std::cout << "\n Error in SymLoadModuleEx" << GetLastError();
	////	return;
	//}

   
    WORD numberOfFrames = CaptureStackBackTrace(0, 100, stack, NULL);
    //SYMBOL_INFO *symbol = (SYMBOL_INFO *)malloc(sizeof(SYMBOL_INFO)+(TRACE_MAX_FUNCTION_NAME_LENGTH - 1) * sizeof(TCHAR));
	SYMBOL_INFO *symbol = new SYMBOL_INFO();
    symbol->MaxNameLen = TRACE_MAX_FUNCTION_NAME_LENGTH;
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    DWORD displacement;
    //IMAGEHLP_LINE64 *line = (IMAGEHLP_LINE64 *)malloc(sizeof(IMAGEHLP_LINE64));
	IMAGEHLP_LINE64 *line= new IMAGEHLP_LINE64();
    line->SizeOfStruct = sizeof(IMAGEHLP_LINE64);
    for (int i = 0; i < numberOfFrames; i++)
    {
        DWORD64 address = (DWORD64)(stack[i]);
		//std::cout<< "\n Process Address:" << address;
		//address = 0x1000000;
        SymFromAddr(process, address, NULL, symbol);
        if (SymGetLineFromAddr64(process, address, &displacement, line))
        {
			printf("\tat %s in %s: line: %lu: address: 0x%0X\n", symbol->Name, line->FileName, line->LineNumber, symbol->Address);
        }
        else
        {
            printf("\tSymGetLineFromAddr64 returned error code %lu.\n", GetLastError());
           printf("\tat %s, address 0x%0X.\n", symbol->Name, symbol->Address);
        }
    }
}






int main( void )
{
    // Get the list of process identifiers.

    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
    {
        return 1;
    }


    // Calculate how many process identifiers were returned.

    cProcesses = cbNeeded / sizeof(DWORD);

    // Print the name and process identifier for each process.

  //  for ( i = 0; i < cProcesses; i++ )
   // {
		for ( i = 0; i < 2; i++ )
		{
        if( aProcesses[i] != 0 )
        {
            PrintProcessNameAndID( aProcesses[i] );
        }
    }
	getchar();
    return 0;
}