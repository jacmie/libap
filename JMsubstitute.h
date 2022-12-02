#ifndef SUBSTITUTE_H
#define SUBSTITUTE_H

#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct VARIABLE
{  
    std::string Name;
    std::string Value;
};

struct OUT_VARIABLE
{  
	unsigned int LineNr;
	unsigned int WordNr;
    std::string Word;
};

class SUBSTITUTE
{
	std::string InPut;
	std::string OutPut;
    char Prompt, EndPrompt;
    bool EndFlag;
	std::vector <OUT_VARIABLE> OutVar;

	unsigned int AllLinesNr = 0;
    
	public:
	
	std::vector <VARIABLE> Var;
       
    SUBSTITUTE();
    SUBSTITUTE(std::string InFile, std::string OutFile, char Mark = '@', char EndMark = ' ');
    void Init(std::string InFile, std::string OutFile, char Mark = '@', char EndMark = ' ');
	int  AddVariable(std::string Name, std::string Value);
	int  AddVariable(std::string Name, double Value);
	int  StripFromMarks(std::string &ToStrip);
	int  Insert();
    int  Extract();
};

#endif
