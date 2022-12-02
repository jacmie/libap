#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#ifdef _WIN32
	#include <windows.h>
	#include <direct.h>
	#include <io.h>
#else
	#include <unistd.h>
	#include <pwd.h>
	#include <spawn.h>
	#include <sys/wait.h>
#endif

//#include "JMdynArray.h"

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
    
    if(std::string(input) != "")
    {
        strcat(Command, " < ");
        strcat(Command, input);
    }
    
    if(std::string(log) != "")
    {
        strcat(Command, " > ");
        strcat(Command, log);
    }
    
    strcat(Command, "\n");
    
    std::cout << Command;
    
    FILE *pipe;
          
    if (( pipe = popen(Command, mode)) == NULL)
    {
        std::clog << "Pipe error!!!" << std::endl;
        return -1;
    }
    
    if(std::string(mode) == "w")
    {
        fputs(buffer, pipe);
        fputs("\n", pipe);
    }
    
    if(std::string(mode) == "r")
    {
        if( NULL == fgets(buffer, sizeof(buffer), pipe) )
        {
            std::clog << "Couldn't get return value via the pipe!!!" << std::endl;
            return -2;
        }
    }
    
    fflush(pipe);
  
    pclose(pipe);

	return 1;
}

int CreateProcess(int ArgNr, char **Arg, bool Wait=1)
{
#ifdef _WIN32
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

	std::string WinArg = "";
	for(int i=0; i<ArgNr; i++)	// Assign Args, Arg[0] = Proc name
    {
		WinArg += std::string(Arg[i]) + " ";
    }
	
    int ProcResult = CreateProcess(Arg[0],    	//The program
                        &WinArg[0],             //Parameters to program
                        NULL,                  	//Security parametr to controll subprogram
                        NULL,                   //Security parametr to controll subprogram
                        FALSE,                  //Dziedziczenie wskaznika i praw od procesu macierzystego
                        NORMAL_PRIORITY_CLASS, 
                        NULL,                   //Environment block PATH, itc.
                        NULL,                   //Current directory for process
                        &si, 
                        &pi);
                        
    if(!ProcResult)
    {
	    std::clog << "Process failed!!!" << std::endl << std::endl;
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
            std::clog << "Executed command but couldn't get exit code.\nCommand=%s\n" << std::endl;
            return 2;
        }
    }
	
	return 0; //success
#else
  
	pid_t Pid;
  	int status;

	status = posix_spawnp(&Pid, Arg[0], NULL, NULL, Arg, environ);
	if(status) return status;

	/* Alternative
	int Pid = fork();
	int status;
	
	if(Pid == -1) 
	{
		clog << "Couldn't run child process!!!" << endl;
		return 1;
	}

    // *** Child ***

	if (Pid == 0) 
	{
		execvp(Arg[0], Arg);    // Searches also for executable in System Variables, example: ls -l

		clog << "Process failed!!!" << endl;
		exit(127); // Command can not be found or executed
	}*/

    // *** Parent ***
    
	if( Wait )
	{          
		while( waitpid(Pid, &status, WNOHANG) == 0 ) usleep(20000); // 2ms
	}

	else
	{
		signal(SIGCHLD, SIG_IGN);
	}
    
	return 0; // success
#endif
}

int CreateProcess(std::vector <std::string> &Arg, bool Wait=1)
{
	std::vector <char*> Ptr;
	for (unsigned int i=0; i<Arg.size(); i++) 
	{
  		Ptr.push_back(&Arg[i][0]);
	}
  	Ptr.push_back(0);

	return CreateProcess(Arg.size(), &Ptr[0], Wait);
}

