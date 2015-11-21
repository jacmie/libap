#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//#include <FL/fl_ask.H>

using namespace std;

int Call(char *buffer)
{
    char call[256];
    
    strcpy(call, "call ");
    strcat(call, buffer);
    
    return system(call);
}

int Pipe(char *Program, char *input, char *log, char *buffer, char *mode)
{
    char Command[256];

    strcpy(Command, Program);
    
    if(string(input) != " ")
    {
        strcat(Command, " < ");
        strcat(Command, input);
    }
    
    if(string(log) != " ")
    {
        strcat(Command, " > ");
        strcat(Command, log);
    }
    
    strcat(Command, "\n");
    
    cout << Command;
    
    FILE *pipe;
          
    if (( pipe = popen(Command, mode)) == NULL)
    {
        cout << "Pipe error!!!" << endl;
        system("pause");
        return -1;
    }
    
    if(string(mode) == "w")
    {
        fputs(buffer, pipe);
        fputs("\n", pipe);
    }
    
    if(string(mode) == "r")
    {
        fgets(buffer, sizeof(buffer), pipe);
    }
    
    fflush(pipe);
  
    pclose(pipe);

	return 1;
}
	
int CreateProcess(bool Wait, char *Proc, char *Arg)
{
    int ProcResult;
    DWORD exitCode;
    STARTUPINFO si;
	PROCESS_INFORMATION pi;
	
	SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX /*|SEM_NOOPENFILEERRORBOX*/);
    //_set_abort_behavior(0,_WRITE_ABORT_MSG);

	ZeroMemory( &si, sizeof(si) );
		si.dwFlags = STARTF_USESHOWWINDOW; 
		si.wShowWindow = SW_HIDE;
		si.cb = sizeof(si);
	   
	ZeroMemory( &pi, sizeof(pi) );
		
    ProcResult = CreateProcess( Proc/*"D:/Dropbox/C++/Programiki/Procesy/Process.exe"*/,    //The program
                        Arg,                                              //Parameters to program
                        NULL,                                               //Security parametr to controll subprogram
                        NULL,                                               //Security parametr to controll subprogram
                        FALSE,                                              //Dziedziczenie wskaznika i praw od procesu macierzystego
                        NORMAL_PRIORITY_CLASS, 
                        NULL,                                               //Environment block PATH, itc.
                        NULL,                                               //Current directory for process
                        &si, 
                        &pi);
                        
    if(!ProcResult)
    {
		//fl_message("Unable to execute!\nProcess: %s\nArgs: %s", Proc, Arg);
	    //cout << "Unable to execute." << endl << endl;
        return 1;
    }
           
    else if(Wait)
    {             
        WaitForSingleObject(pi.hProcess, INFINITE);
        
        ProcResult = GetExitCodeProcess(pi.hProcess, &exitCode);
        
        // Close the handles.
        CloseHandle( pi.hProcess );
        CloseHandle( pi.hThread );
 
        if (!ProcResult)
        {
            // Could not get exit code.
			//fl_message("Executed command but couldn't get exit code!");
            //cout << "Executed command but couldn't get exit code.\nCommand=%s\n" << endl;
            return 2;
        }
    }

    return 0;
}

int CreateProcess(bool Wait, string Proc, string Arg)
{
	char *CstrProc = new char[Proc.length() + 1];
	strcpy(CstrProc, Proc.c_str());
	char *CstrArg = new char[Arg.length() + 1];
	strcpy(CstrArg, Arg.c_str());
	
	return CreateProcess(Wait, CstrProc, CstrArg);
}