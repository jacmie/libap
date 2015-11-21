#include "JMSubstitute.h"

#include "JMconsole.h"
//extern CONSOLE con;

using namespace std;

Substitute::Substitute()
{
}
/*
Substitute::Substitute(string InFile, string OutFile)
{
    strcpy(InPut, InFile.c_str());
    strcpy(OutPut, OutFile.c_str());
    
    Prompt 	  = '@';
	EndPrompt = ' ';
}*/

Substitute::Substitute(string InFile, string OutFile, char Mark, char EndMark)
{
    strcpy(InPut, InFile.c_str());
    strcpy(OutPut, OutFile.c_str());
    
    Prompt    = Mark;
	EndPrompt = EndMark;
	
	if(EndMark == ' ')
		EndFlag = 0;
	else
		EndFlag = 1;
}

int Substitute::Insert(int n, Variables *Var)
{
    //*** Clean Marks ***
    
    for(int i=0; i<n; i++)
    {
        if(Var[i].Name[0] == Prompt)
        {
            for(int x=0; x<n-1; x++)
                Var[i].Name[x] = Var[i].Name[x+1];
        }
        
        //con << Var[i].Name << "\t" << Var[i].Value << endl;
    }
    
    //*** Fill Tamplate ***
    
	int  len, pos;
    string line;
	
    ifstream in(InPut);
	
	if(!in)
		return 2;
	
    ofstream out(OutPut);
    
    if(!out)
        return 3;
    
    while(!in.eof())
    {
		getline(in, line);
		
		pos = 0;
		
		while(1) //till the end of the line
		{
			pos = line.find_first_of(Prompt, pos);
				
			if(pos == -1)
			{
				out << line << endl;
				break;
			}
			
			else
			{
				out << line.substr(0, pos);
				
				for(int i=0; i<n; i++)
				{
					len = strlen(Var[i].Name.c_str());
					
					if(EndFlag == 0 && !strcmp(line.substr(pos+1, len).c_str(), Var[i].Name.c_str())) //empty space separator
					{
						//con << EndFlag << endl;
						
						out << Var[i].Value;
						
						line = line.substr(pos + 1 + len);
						pos  = 0;
						break;
					}
					
					if(EndFlag == 1 && !strcmp(line.substr(pos+1, len).c_str(), Var[i].Name.c_str()) && line[pos+len+1] == EndPrompt) //end mark present
					{
						//con << "EndFlag=" << EndFlag << "\t" << line.substr(pos+1, len) << "\t" << line[pos + 1 + len] << endl;
					
						out << Var[i].Value;
						
						line = line.substr(pos + 1 + len + 1);
						pos  = 0;
						break;
					}
				}
			}
		}
    }
   
    out.close();
    in.close();
		
	return 1;
}

