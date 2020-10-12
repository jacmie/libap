#include <string.h>
#include <iostream>
#include <fstream>

struct Variables
{  
    std::string Name;
    std::string Value;
};

class Substitute
{
    char InPut[255];
    char OutPut[255];
    char Prompt, EndPrompt;
    bool EndFlag;
	
    public:
        
    Substitute();
    //Substitute(std::string InFile, std::string OutFile);
    Substitute(std::string InFile, std::string OutFile, char Mark = '@', char EndMark = ' ');
    int Insert(int n, Variables *Var);
	
	//Error types:
	//1 - Ok
	//2 - in  stream couldn't open
	//3 - out stream couldn't open
	//4 - no such variable name???
};
