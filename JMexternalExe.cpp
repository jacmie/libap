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

	std::string WinArg = "";
	for(int i=0; i<ArgNr; i++)	// Assign Args, Arg[0] = Proc name
    {
		WinArg += string(Arg[i]) + " ";
    }
	
    ProcResult = CreateProcess(Arg[0]/*"D:/Dropbox/C++/Programiki/Procesy/Process.exe"*/,    //The program
                        &WinArg[0],                                              	//Parameters to program
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
	
	switch (Pid) 
	{
  		case -1:
		{
			clog << "Couldn't run child process!!!" << endl;
			return 1;
    		
			//perror("fork");
    		//break;
		}

		case 0:
		{
			execvp(Arg[0], Arg);    // Searches for executable in System Variables, example: ls -l

			clog << "Process failed!!!" << endl;
			exit(127); // Command can not be found or executed
    		
			//execl("/bin/ls", "ls", (char *) 0);
    		//perror("exec");
    		//break;
		}

		default:
		{
    		clog << "Child id: " << Pid << endl;
    		//printf("Child id: %i\n", pid);
    		//fflush(NULL);
    		
			if (waitpid(Pid, &status, 0) != -1) printf("Child exited with status %i\n", status);
			else perror("waitpid");
    		
   	 		break;
		}
  	}
	/*
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
        //execv(Arg[0], Arg);     // Needs full Path of the executable
		execvp(Arg[0], Arg);    // Searches for executable in System Variables, example: ls -l

		clog << "Process failed!!!" << endl;
		exit(127); // Command can not be found or executed
	}
		
    // *** Parent ***
    
	if( Wait )
	{          
        clog << "Before Loop:\t" << Pid << "\t" << status << "\t" << waitpid( Pid, &status, WNOHANG ) << endl;

		while( waitpid( Pid, &status, WNOHANG ) == 0 / *Pid* / )
		{
            clog << "In loop:\t" << Pid << "\t" << status << "\t" << waitpid( Pid, &status, WNOHANG ) << endl;
			usleep( 20000 ); // 2ms
		}

        clog << "After Loop\t" << Pid << "\t" << status << "\t" << waitpid( Pid, &status, WNOHANG ) << endl;

        clog << "Wait END" << endl << endl;
	}

	else
	{
		signal(SIGCHLD, SIG_IGN);
	}*/
    
	ProcResult = 1;

#endif

    return ProcResult;
}

void test_fork_exec(void) 
{
  	pid_t pid;
  	int status;
  	puts("Testing fork/exec");
  	fflush(NULL);
  	pid = fork();
  
	switch (pid) 
	{
  		case -1:
		{
    		perror("fork");
    		break;
		}

		case 0:
		{
    		execl("/bin/ls", "ls", (char *) 0);
    		perror("exec");
    		break;
		}

		default:
		{
    		printf("Child id: %i\n", pid);
    		fflush(NULL);
    		
			if (waitpid(pid, &status, 0) != -1) printf("Child exited with status %i\n", status);
			else perror("waitpid");
    		
   	 		break;
		}
  	}
}

void test_posix_spawn(void) 
{
  	/*pid_t pid;
  	//char *argv[] = {"ls", (char *) 0};
  	int status;
  	puts("Testing posix_spawn");
  	fflush(NULL);
  	
	//status = posix_spawn(&pid, "/bin/ls", NULL, NULL, argv, environ);
  
	if (status == 0) 
	{
    	printf("Child id: %i\n", pid);
    	fflush(NULL);

    	if (waitpid(pid, &status, 0) != -1) printf("Child exited with status %i\n", status);
     	else perror("waitpid");
  	} 
	else printf("posix_spawn: %s\n", strerror(status));*/
}

int CreateProcess(std::vector <std::string> Arg, bool Wait=1)
{
	clog << "ssssssssssssssssssssssssss" << endl;
    
	unsigned int len = Arg[0].length();

	for(unsigned int i=1; i<Arg.size(); i++)
    {
		if( len < Arg[i].size() ) len = Arg[i].length();
    }

	clog << "len: " << len << endl;
	
	clog << "CCCCCCCCCCCCCCCCCCCCCCCCCC" << endl;
	
	DYNAMIC_ARRAY_2D <char> ArgPtr(Arg.size()+2, len);

	
	clog << "aaaaaaaaaaaaaaaaaaaaaaaaaa" << endl;
    //char **ArgPtr = new char *[Arg.size() + 2];
    //ArgPtr = new ARRAY_TYPE *[Arg.size() + 2];
    
    for(unsigned int i=0; i<Arg.size(); i++)	// Assign Args, Arg[0] = Proc name
    {
        //ArgPtr[i] = new char [Arg[i].length()];
        strcpy(ArgPtr.Array2d[i], Arg[i].c_str());
    }
		/*
	if(ArgPtr == NULL)
	{
		clog << "Bad Arguments array allocation!!!" << endl;
		return 0;
	}
	*/
	ArgPtr.Array2d[Arg.size()] = NULL;					// Last Arg NULL*/
	clog << "CCCCCCCCCCCCCCCCCCCCCCCCCC" << endl;
    
/*
  	pid_t pid;
  	//char *argv[] = {"ls", (char *) 0};
  	int status;
  	puts("Testing posix_spawn");
  	fflush(NULL);
  	
	std::string WinArg = "";
	for(unsigned int i=0; i<Arg.size(); i++)	// Assign Args, Arg[0] = Proc name
    {
		WinArg += Arg[i] + " ";
    }
  	char *argv = &WinArg[0];
	
	status = posix_spawn(&pid, Arg[0].c_str(), NULL, NULL, argv, environ);
  
	if (status == 0) 
	{
    	printf("Child id: %i\n", pid);
    	fflush(NULL);

    	if (waitpid(pid, &status, 0) != -1) printf("Child exited with status %i\n", status);
     	else perror("waitpid");
  	} 
	else printf("posix_spawn: %s\n", strerror(status));
*/
	CreateProcess(Arg.size(), ArgPtr.Array2d, Wait);

    ArgPtr.DelArray2d();
/*		
	if(ArgPtr == NULL)
	{
		clog << "No dynamic array of Args to delete!!!" << endl;
		return 0;
	}
        
	else 
	{
		for(unsigned int i=0; i<Arg.size(); i++)
			delete [] ArgPtr[i];
        
		delete [] ArgPtr;
	}
*/
	clog << "CCCCCCCCCCCCCCCCCCCCCCCCCC" << endl;
	return 1;
}

