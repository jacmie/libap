#include "JMfilesHandling.h"

using namespace std;
//namespace fs = std::filesystem;

bool DirExists(std::string DirName)
{
    return FileExists(DirName);
}

bool FileExists(std::string FileName)
{
    ifstream istr(FileName);

    if(istr)
    {
        istr.close();
    	return 1;
    }

    return 0;
}

std::string Browse(const char *Filt, int DialogType)
{
    Fl_Native_File_Chooser *ch = new Fl_Native_File_Chooser();
    ch -> filter(Filt);
    ch -> type(DialogType);
    ch -> show();

    std::string FileName;

    if(ch -> filename())
    {
    	FileName = ch -> filename();
    }

    else
    {
	    FileName = ""; //Canceled
    }

    if(DialogType == 4 && FileName.length() > 0) // Check Extension while saving
    {
	    // === Extract Choosen Filter ===

    	int Start, End=0;
    	std::string FilterExtension;
    	std::string Filter = ch -> filter();

    	for(int i=0; i<=ch->filter_value(); i++)
    	{
    		Start = Filter.find_first_of('*', End);
    		End   = Filter.find_first_of ('\n', Start);
		
    		FilterExtension = Filter.substr(Start+1, End-Start-1);
    	}
	
    	// === Extract File Extension ===
	
    	int Id = FileName.find_last_of('.');
	
    	if(Id<0) // No extension, add
    	{
    		FileName += FilterExtension;
		
    		if( FileExists(FileName) && fl_choice("File exists:\n%s\n\nDo you want to overwrite it?", "Yes", "No", 0, FileName.c_str()) )
    		{
    			FileName = ""; //Canceled
    		}
			
    		return FileName;
    	}

    	std::string Extension = FileName.substr(Id);

    	if(!boost::iequals(Extension, FilterExtension)) // Extension different than in the filter, add
    	{
    		FileName += FilterExtension;
		
    		if( FileExists(FileName) && fl_choice("File exists:\n%s\n\nDo you want to overwrite it?", "Yes", "No", 0, FileName.c_str()) )
    		{
    			FileName = ""; //Canceled
    		}

    		return FileName;
    	}
	
    	if( FileExists(FileName) && fl_choice("File exists:\n%s\n\nDo you want to overwrite it?", "Yes", "No", 0, FileName.c_str()) )
    	{
    		FileName = ""; //Canceled
    	}	
    }

    return FileName;
}
