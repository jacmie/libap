#ifndef _SUBSTITUTE_H_
#define _SUBSTITUTE_H_

#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "JMconvert.h"

struct VARIABLE
{  
    std::string Name;
    std::string Value;
};

class SUBSTITUTE
{
	std::string InPut;
	std::string OutPut;
    char Prompt, EndPrompt;
    bool EndFlag;
	std::vector <VARIABLE> Var;

    public:
        
    SUBSTITUTE();
    //SUBSTITUTE(std::string InFile, std::string OutFile);
    SUBSTITUTE(std::string InFile, std::string OutFile, char Mark = '@', char EndMark = ' ');
	void AddVariable(std::string Name, std::string Value);
	void AddVariable(std::string Name, double Value);
	int  Insert();
};

#endif
