#include "ap_substitute.h"

#include <fstream>
#include <iostream>
#include <sstream>

ap::SUBSTITUTE::SUBSTITUTE(std::string inFile, std::string outFile, char mark, char endMark) {
	Init(inFile, outFile, mark, endMark); 
}

void ap::SUBSTITUTE::Init(std::string inFile, std::string outFile, char mark, char endMark) {
    inPut	  = inFile;
    outPut	  = outFile;
    
    prompt    = mark;
	endPrompt = endMark;
	
	if(endMark == ' ')	endFlag = 0;
	else				endFlag = 1;
	
	var.resize(0);
	outVar.resize(0);
}

int ap::SUBSTITUTE::AddVariable(std::string name, std::string value) {
    if(name.length() == 0) {
        std::clog << "Name length equal to 0!!! The Variable NOT added!!!" << std::endl;
        return 1;
    }

    if(value.length() == 0) {
        std::clog << "Value length equal to 0!!! The Variable NOT added!!!" << std::endl;
        return 1;
    }

	VARIABLE tempVar;
	tempVar.name  = name;
	tempVar.value = value;

	var.push_back(tempVar);

    return 0;
}

int ap::SUBSTITUTE::AddVariable(std::string name, double value) {
	std::string str;
	std::stringstream ss;
	ss.precision(16);
	ss << value;
	ss >> str;
   
	return AddVariable(name, str);
}

int ap::SUBSTITUTE::StripFromMarks(std::string &toStrip) {
	if(toStrip[0] == prompt) toStrip = toStrip.substr(1); 
	else {
		std::clog << "Wrong Variable Start Mark!!!" << std::endl;
		return 3;
	}
	
	if(endPrompt != ' ' && endPrompt != 9 && endPrompt != 10 && endPrompt != 11 && endPrompt != 12 && endPrompt != 13) { // Ommit if endPrompt is a whitespace
		unsigned int size = toStrip.size();

		if(toStrip[size-1] == endPrompt) toStrip = toStrip.substr(0, size-1); 
		else {
			std::clog << "Wrong Variable End Mark!!!" << std::endl;
			return 3;
		}
	}

	return 0;
}

int ap::SUBSTITUTE::Insert() {
    // *** Clean Marks ***
    
    for(unsigned int i=0; i<var.size(); i++) {
        if(var[i].name[0] == prompt) var[i].name = var[i].name.substr(1); 
       
		if(endPrompt != ' ' && endPrompt != 9 && endPrompt != 10 && endPrompt != 11 && endPrompt != 12 && endPrompt != 13) { // Ommit if EndPrompt is a whitespace
			unsigned int size = var[i].name.size();
			if(var[i].name[size-1] == endPrompt) var[i].name = var[i].name.substr(0, size-1); 
		}
    }
    
    // *** Fill Tamplate ***
    
	int  len, pos;
    std::string line;
	
    std::ifstream in(inPut);
	
	if(!in) {
        std::clog << "Can't open Input file!!!" << std::endl;
		return 1;
    }
	
    std::ofstream out(outPut);
    
    if(!out) {
        std::clog << "Can't write Output file!!!" << std::endl;
        return 2;
    }

    while(!in.eof()) {
		getline(in, line);
		pos = 0;
		
        for(unsigned int l=0; l<line.length(); l++) { 
			pos = line.find_first_of(prompt, pos);
				
			if(pos == -1) {
				out << line << std::endl;
				break;
			}
			
			else {
				out << line.substr(0, pos);
                unsigned int i;

				for(i=0; i<var.size(); i++) {
					len = var[i].name.length();
					
					if(endFlag == 0 && !var[i].name.compare( line.substr(pos+1, len) ))  { //empty space separator
						out << var[i].value;

						if( (pos + 1 + len + 1) == int(line.length()) )  out << std::endl;

						line = line.substr(pos + 1 + len);
						pos  = 0;
						break;
					}
					
					if(endFlag == 1 && !var[i].name.compare( line.substr(pos+1, len) ) && line[pos+len+1] == endPrompt) { //end mark present
						out << var[i].value;
						
                        if( (pos + 1 + len + 1) == int(line.length()) )  out << std::endl;

						line = line.substr(pos + 1 + len + 1);
						pos  = 0;
						break;
					}
				}

                if(i == var.size()) { // No Variable after prompt
                    out << prompt;
                    line = line.substr(pos + 1);
                }   
			}
		}
    }
   
    out.close();
    in.close();
		
	return 0;
}

int ap::SUBSTITUTE::Extract() {
    // *** Clean Marks ***
    for(unsigned int i=0; i<var.size(); i++) {
        if(var[i].name[0] == prompt) var[i].name = var[i].name.substr(1); 
       
		if(endPrompt != ' ' && endPrompt != 9 && endPrompt != 10 && endPrompt != 11 && endPrompt != 12 && endPrompt != 13) { // Ommit if EndPrompt is a whitespace
			unsigned int size = var[i].name.size();
			if(var[i].name[size-1] == endPrompt) var[i].name = var[i].name.substr(0, size-1); 
		}
    }

    // *** Find Position of the Variables ***
    std::string line, word;
	unsigned int lineNr=0, wordNr;
	OUT_VARIABLE singleVar;

    std::ifstream in(inPut);
	if(!in) return 1;
	
    std::ifstream in2(outPut);
    if(!in2) return 2;
    
    while(!in.eof()) {
		getline(in, line);

		std::stringstream ss;
		ss.str(line);

		wordNr = 0;
		
		while(!ss.eof()) { //till the end of the line
			ss >> word;
			wordNr++;
			
			if(word[0] == prompt) {
				singleVar.lineNr = lineNr;
				singleVar.wordNr = wordNr;
				singleVar.word   = word;
                
				outVar.push_back(singleVar);
            
                word = "";
			}
		}
		
		lineNr++;
    }
 
	// *** Strip OutVar from Marks ***
	for(unsigned int i=0; i<outVar.size(); i++) {
		if( StripFromMarks(outVar[i].word) ) return 3;
	}

	// *** Compare Var with OutVar ***
	std::vector <unsigned int> list;
	list.resize( var.size() );

	for(unsigned int i=0; i<var.size(); i++) {
		unsigned int match = 0;

		for(unsigned int j=0; j<outVar.size(); j++)	{
			if( 0 == var[i].name.compare(outVar[j].word) ) {
				list[i] = j;
				match++;
			}
		}

		if(match == 0) {
			std::clog << "No Output Varible: " << var[i].name << "!!!" << std::endl;
			return 4;
		}

		if(match > 1) {
			std::clog << "Too many Output Varibles: " << var[i].name << "!!!" << std::endl;
			return 5;
		}
	}

	// *** Extract ***
	for(unsigned int i=0; i<var.size(); i++) {
		in2.clear();
		in2.seekg (0, std::ios::beg);

		for(unsigned int j=0; j<=outVar[list[i]].lineNr; j++) { getline(in2, line);	}

		std::stringstream ss;
		ss.str(line);
		
		for(unsigned int j=0; j<outVar[list[i]].wordNr-1; j++) { ss >> word; }

		ss >> var[i].value;
	}

    in2.close();
    in.close();
		
	return 0;
}
