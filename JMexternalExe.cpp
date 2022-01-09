#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#ifdef WIN32 
	#include <windows.h>
	#include <direct.h>
	#include <io.h>
#else
	#include <unistd.h>
	#include <pwd.h>
	#include <sys/wait.h>
#endif

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
    
    if(string(input) != "")
    {
        strcat(Command, " < ");
        strcat(Command, input);
    }
    
    if(string(log) != "")
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

int CreateProcess(int ArgNr, char **Arg, bool Wait=1)
{
    int ProcResult;

#ifdef WIN32

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

    ProcResult = CreateProcess( Arg[0]/*"D:/Dropbox/C++/Programiki/Procesy/Process.exe"*/,    //The program
                        Arg,                                              	//Parameters to program
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
	    clog << "Process failed!!!" << endl << endl;
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
            clog << "Executed command but couldn't get exit code.\nCommand=%s\n" << endl;
            return 2;
        }
    }

/* 
	STARTUPINFO		suInfo;		// Process startup information
	PROCESS_INFORMATION	prInfo;		// Process information

	memset(&suInfo, 0, sizeof(suInfo));
	suInfo.cb = sizeof(suInfo);
	if( iHide )
		{
		suInfo.dwFlags = STARTF_USESHOWWINDOW; 
		suInfo.wShowWindow = SW_HIDE; 
		}
	
	string com = command;
	for(int i=0; i<iarg; i++)
		{
		com += " \"";
		com += argvv[i];
		com += "\"";
		}

	ProcResult = CreateProcess(NULL, (char*)com.c_str(), NULL, NULL, FALSE,
                  NORMAL_PRIORITY_CLASS, NULL, NULL, &suInfo, &prInfo);

	if( iWait )
		{          
		DWORD ExitCode = 0;
		do
			{
			if( GetExitCodeProcess( prInfo.hProcess, &ExitCode ) == 0 )break;
			if( iFun )Idle();
			MiliSleep( 20 );
			}
		while( ExitCode == STILL_ACTIVE );
		}
*/

#else

	int Pid = fork();
	int status;
	
	if(Pid == -1) 
	{
		clog << "Couldn't run child process!!!" << endl;
		return 1;
	}

	if (Pid == 0) 
	{
		execv(Arg[0], Arg);

		clog << "Process failed!!!" << endl;
		return(127); // Command can not be found or executed
	}
		
	if( Wait )
	{          
		while( waitpid( Pid, &status, WNOHANG ) == Pid )
		{
			usleep( 20000 ); // 2ms
		}
	}

	else
	{
		signal(SIGCHLD, SIG_IGN);
	}

	ProcResult = 1;

#endif

    return ProcResult;
}

int CreateProcess(std::vector <std::string> Arg, bool Wait=1)
{
    char *ArgPtr[Arg.size() + 2];
    
    for(unsigned int i=0; i<Arg.size(); i++)	// Assign Args, Arg[0] = Proc name
    {
        ArgPtr[i] = new char [Arg[i].length()];
        strcpy(ArgPtr[i], Arg[i].c_str());
    }
	
	ArgPtr[Arg.size()] = NULL;					// Last Arg NULL
	
	return CreateProcess(Arg.size(), ArgPtr, Wait);
}

