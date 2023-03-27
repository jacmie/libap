#ifndef SUBSTITUTE_H
#define SUBSTITUTE_H

#include <string>
#include <vector>

namespace ap {

class SUBSTITUTE
{
	struct VARIABLE
	{  
    	std::string name;
    	std::string value;
	};

	struct OUT_VARIABLE
	{  
		unsigned int lineNr;
		unsigned int wordNr;
    	std::string  word;
	};

	std::string inPut;
	std::string outPut;
    char prompt, endPrompt;
    bool endFlag;
	std::vector <OUT_VARIABLE> outVar;

	unsigned int allLinesNr = 0;
    
	public:
	
	std::vector <VARIABLE> var;

    SUBSTITUTE() = default;
    SUBSTITUTE(std::string inFile, std::string outFile, char mark = '@', char endMark = ' ');
    void Init(std::string inFile, std::string outFile, char mark = '@', char endMark = ' ');
	int  AddVariable(std::string name, std::string value);
	int  AddVariable(std::string name, double value);
	int  StripFromMarks(std::string &toStrip);
	int  Insert();
    int  Extract();
};

} // namespace ap

#endif
