#include "JMsubstitute.h"

SUBSTITUTE::SUBSTITUTE()
{
}

SUBSTITUTE::SUBSTITUTE(std::string InFile, std::string OutFile, char Mark, char EndMark)
{
	Init(InFile, OutFile, Mark, EndMark); 
}


void SUBSTITUTE::Init(std::string InFile, std::string OutFile, char Mark, char EndMark)
{
    InPut	= InFile;
    OutPut	= OutFile;
    
    Prompt    = Mark;
	EndPrompt = EndMark;
	
	if(EndMark == ' ')
		EndFlag = 0;
	else
		EndFlag = 1;
	
	Var.resize(0);
	OutVar.resize(0);
}

int SUBSTITUTE::AddVariable(std::string Name, std::string Value)
{
    if(Name.length() == 0)
    {
        std::clog << "Name length equal to 0!!! The Variable NOT added!!!" << std::endl;
        return 1;
    }

    if(Value.length() == 0)
    {
        std::clog << "Value length equal to 0!!! The Variable NOT added!!!" << std::endl;
        return 1;
    }

	VARIABLE TempVar;
	TempVar.Name  = Name;
	TempVar.Value = Value;

	Var.push_back(TempVar);

    return 0;
}

int SUBSTITUTE::AddVariable(std::string Name, double Value)
{
	std::string Str;
	std::stringstream ss;
	ss.precision(16);
	ss << Value;
	ss >> Str;
   
	return AddVariable(Name, Str);
}

int SUBSTITUTE::StripFromMarks(std::string &ToStrip)
{
	if(ToStrip[0] == Prompt) ToStrip = ToStrip.substr(1); 
	else
	{
		std::clog << "Wrong Variable Start Mark!!!" << std::endl;
		return 3;
	}
	
	if(EndPrompt != ' ' && EndPrompt != 9 && EndPrompt != 10 && EndPrompt != 11 && EndPrompt != 12 && EndPrompt != 13) // Ommit if EndPrompt is a whitespace
	{
		unsigned int Size = ToStrip.size();

		if(ToStrip[Size-1] == EndPrompt) ToStrip = ToStrip.substr(0, Size-1); 
		else
		{
			std::clog << "Wrong Variable End Mark!!!" << std::endl;
			return 3;
		}
	}

	return 0;
}

int SUBSTITUTE::Insert()
{
    // *** Clean Marks ***
    
    for(unsigned int i=0; i<Var.size(); i++)
    {
        if(Var[i].Name[0] == Prompt) Var[i].Name = Var[i].Name.substr(1); 
       
		if(EndPrompt != ' ' && EndPrompt != 9 && EndPrompt != 10 && EndPrompt != 11 && EndPrompt != 12 && EndPrompt != 13) // Ommit if EndPrompt is a whitespace
		{
			unsigned int Size = Var[i].Name.size();
			if(Var[i].Name[Size-1] == EndPrompt) Var[i].Name = Var[i].Name.substr(0, Size-1); 
		}
    }
    
    // *** Fill Tamplate ***
    
	int  len, pos;
    std::string line;
	
    std::ifstream in(InPut);
	
	if(!in)
    {
        std::clog << "Can't open Input file!!!" << std::endl;
		return 1;
    }
	
    std::ofstream out(OutPut);
    
    if(!out)
    {
        std::clog << "Can't write Output file!!!" << std::endl;
        return 2;
    }

    while(!in.eof())
    {
		getline(in, line);
		
		pos = 0;
		
        for(unsigned int l=0; l<line.length(); l++)
		{ 
			pos = line.find_first_of(Prompt, pos);
				
			if(pos == -1)
			{
				out << line << std::endl;
				break;
			}
			
			else
			{
				out << line.substr(0, pos);
				
                unsigned int i;

				for(i=0; i<Var.size(); i++)
				{
					len = strlen(Var[i].Name.c_str());
					
					if(EndFlag == 0 && !strcmp(line.substr(pos+1, len).c_str(), Var[i].Name.c_str())) //empty space separator
					{
						out << Var[i].Value;

						if( (pos + 1 + len + 1) == int(line.length()) )  out << std::endl;

						line = line.substr(pos + 1 + len);
						pos  = 0;
						break;
					}
					
					if(EndFlag == 1 && !strcmp(line.substr(pos+1, len).c_str(), Var[i].Name.c_str()) && line[pos+len+1] == EndPrompt) //end mark present
					{
						out << Var[i].Value;
						
                        if( (pos + 1 + len + 1) == int(line.length()) )  out << std::endl;

						line = line.substr(pos + 1 + len + 1);
						pos  = 0;
						break;
					}
				}

                if(i == Var.size()) // No Variable after Prompt
                {
                    out << Prompt;
                    line = line.substr(pos + 1);
                }   
			}
		}
    }
   
    out.close();
    in.close();
		
	return 0;
}

int SUBSTITUTE::Extract()
{
    //*** Clean Marks ***
    
    for(unsigned int i=0; i<Var.size(); i++)
    {
        if(Var[i].Name[0] == Prompt) Var[i].Name = Var[i].Name.substr(1); 
       
		if(EndPrompt != ' ' && EndPrompt != 9 && EndPrompt != 10 && EndPrompt != 11 && EndPrompt != 12 && EndPrompt != 13) // Ommit if EndPrompt is a whitespace
		{
			unsigned int Size = Var[i].Name.size();
			if(Var[i].Name[Size-1] == EndPrompt) Var[i].Name = Var[i].Name.substr(0, Size-1); 
		}
    }

    //*** Find Position of the Variables ***
    
    std::string line, word;
	unsigned int line_nr=0, word_nr;
	OUT_VARIABLE SingleVar;

    std::ifstream in(InPut);
	if(!in) return 1;
	
    std::ifstream in2(OutPut);
    if(!in2) return 2;
    
    while(!in.eof())
    {
		getline(in, line);

		std::stringstream ss;
		ss.str(line);

		word_nr = 0;
		
		while(!ss.eof()) //till the end of the line
		{
			ss >> word;
			word_nr++;
			
			if(word[0] == Prompt) 
			{
				//clog << "Line: " << line_nr << "\tWord: " << word_nr << "\t" << word << endl;
                //clog << "#" << line << "#" << endl;

				SingleVar.LineNr = line_nr;
				SingleVar.WordNr = word_nr;
				SingleVar.Word   = word;
                
				OutVar.push_back(SingleVar);
            
                word = "";
			}
		}
		
		line_nr++;
    }
 
	// *** Strip OutVar from Marks ***
	
	for(unsigned int i=0; i<OutVar.size(); i++)
	{
		if( StripFromMarks(OutVar[i].Word) ) return 3;
	}

	// *** Compare Var with OutVar ***

	std::vector <unsigned int> List;
	List.resize( Var.size() );

	for(unsigned int i=0; i<Var.size(); i++)
	{
		unsigned int Match = 0;

		for(unsigned int j=0; j<OutVar.size(); j++)	
		{
			if( 0 == Var[i].Name.compare(OutVar[j].Word) ) 
			{
				List[i] = j;
				Match++;
			}
		}

		if(Match == 0)
		{
			std::clog << "No Output Varible: " << Var[i].Name << "!!!" << std::endl;
			return 4;
		}

		if(Match > 1)
		{
			std::clog << "Too many Output Varibles: " << Var[i].Name << "!!!" << std::endl;
			return 5;
		}
	}

	// *** Extract ***

	for(unsigned int i=0; i<Var.size(); i++)
	{
		in2.clear();
		in2.seekg (0, std::ios::beg);

		for(unsigned int j=0; j<=OutVar[List[i]].LineNr; j++)	
		{
			getline(in2, line);
		}

		std::stringstream ss;
		ss.str(line);
		
		for(unsigned int j=0; j<OutVar[List[i]].WordNr-1; j++)	
		{
			ss >> word;
		}

		ss >> Var[i].Value;
	}

    in2.close();
    in.close();
		
	return 0;
}
