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
	#include <spawn.h>
	#include <sys/wait.h>
#endif

#include "JMdynArray.h"

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
        clog << "Pipe error!!!" << endl;
        return -1;
    }
    
    if(string(mode) == "w")
    {
        fputs(buffer, pipe);
        fputs("\n", pipe);
    }
    
    if(string(mode) == "r")
    {
        if( NULL == fgets(buffer, sizeof(buffer), pipe) )
        {
            clog << "Couldn't get return value via the pipe!!!" << endl;
            return -2;
        }
    }
    
    fflush(pipe);
  
    pclose(pipe);

	return 1;
}

int CreateProcess(int ArgNr, char **Arg, bool Wait=1)
{
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

	std::string WinArg = "";
	for(int i=0; i<ArgNr; i++)	// Assign Args, Arg[0] = Proc name
    {
		WinArg += string(Arg[i]) + " ";
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
	
	return 0; //success
#else
  
	clog << "***" << endl;
	pid_t Pid;
  	int status;

	clog << Arg[0] << endl;
	for(int i=0; i<ArgNr; i++)
	{
		clog << Arg[i] << " ";
	}
	clog << endl;

	status = posix_spawn(&Pid, Arg[0], NULL, NULL, Arg, environ);
	clog << "***1" << endl;
	clog << "status " << status << endl;
	if(status) return status;
	clog << "***2" << endl;


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
		clog << "***S" << endl;
		signal(SIGCHLD, SIG_IGN);
	}
    
	clog << "***E" << endl;
	return 0; // success
#endif
}

int CreateProcess(std::vector <std::string> Arg, bool Wait=1)
{
	// --- Find the longest Argument ---
/*	unsigned int len = Arg[0].length();

	for(unsigned int i=1; i<Arg.size(); i++)
    {
		if( len < Arg[i].size() ) len = Arg[i].length();
    }

	// --- Declare Arguments Arrays ---
	vector < vector <string> > Arr; 
	 
	DYNAMIC_ARRAY_2D <char> ArgPtr;
	if( !ArgPtr.InitArray2d(Arg.size()+2, len) ) return 10;
	
   	// --- Assign Arguments --- 
    for(unsigned int i=0; i<Arg.size(); i++)	// Assign Args, Arg[0] = Proc name
    {
        strcpy(ArgPtr.Array2d[i], Arg[i].c_str());
    }
	
	ArgPtr.Array2d[Arg.size()] = NULL;			// Last Arg NULL
*/
	// === Run Process ===
	//int Ret = CreateProcess(Arg.size(), ArgPtr.Array2d, Wait);

	vector <char*> p(Arg.size());
	
	//char *ptr = malloc(myCharVector.size()+1);
	for (unsigned int i=0; i<Arg.size(); i++) 
	{
  		p[i] = &Arg[i][0];
		clog << p[i] << " ";
	}
  	p[Arg.size()] = 0;
	clog << endl;
	for (unsigned int i=0; i<Arg.size(); i++) 
	{
		clog << &p[i] << " ";
	}
	//p[Arg.size()] = 0;
	clog << endl << Arg.size() << endl;

	//= &Arg[0];
	int Ret = CreateProcess(Arg.size(), &p[0], Wait);
	
	for (unsigned int i=0; i<Arg.size(); i++) 
	{
		clog << &p[i] << " ";
	}
	clog << endl;

	// --- Delete Arguments Arrays ---
    //if( !ArgPtr.DelArray2d() ) return 20;

	return Ret;
}

