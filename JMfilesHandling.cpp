#include "JMfilesHandling.h"

std::string Browse_FileExists(std::string FileName, bool AskOverwriteFlag)
{
	namespace fs = std::filesystem;

    DIALOGS Dialog;

    if(AskOverwriteFlag && fs::exists(FileName) && !Dialog.choice_s("File exists:\n%s\n\nDo you want to overwrite it?", FileName.c_str()) ) FileName = ""; //Canceled
    return FileName;
}

std::string Browse(const char *Filt, int DialogType, bool AskOverwriteFlag)
{
    Fl_Native_File_Chooser *ch = new Fl_Native_File_Chooser();
    ch -> filter(Filt);
    ch -> type(DialogType);
    ch -> show();

    std::string FileName;

    if(ch -> filename())    FileName = ch -> filename();
    else                    FileName = ""; //Canceled

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

    	if(Id<0) return Browse_FileExists(FileName + FilterExtension, AskOverwriteFlag); // No extension, add
        if(Id>=0 && !boost::iequals(FileName.substr(Id), FilterExtension)) return Browse_FileExists(FileName + FilterExtension, AskOverwriteFlag); // Extension different than in the filter, add

        return Browse_FileExists(FileName, AskOverwriteFlag);
    }

    return FileName;
}

#ifndef WIN32

int GetUserGroups(std::vector <gid_t> &Groups)
{
	int GroupsNr = 1;
	std::string UserName;

	//Windows (not used)
    //UserName = getenv("USERNAME"); 
    UserName = getenv("USER");

	Groups.resize(GroupsNr);
	
	struct passwd *pw = getpwnam( UserName.c_str() );
	if(pw == NULL) return 1; 
	
	getgrouplist(&UserName[0], pw->pw_gid, &Groups[0], &GroupsNr);
	Groups.resize(GroupsNr);
	getgrouplist(&UserName[0], pw->pw_gid, &Groups[0], &GroupsNr);

	return 0;
}

int CheckPermissions(std::string Path, std::vector <bool> &Results)
{
	namespace fs = std::filesystem;

    DIALOGS Dialog;

	// === Get the File info ===
	
	struct stat Info;

	if( -1 == stat(Path.c_str(), &Info) )
	{
        Dialog.message("File Permissions couldn't be checked!!!");
		return 1;
	}

	struct passwd *pw = getpwuid(Info.st_uid);
	struct group  *gr = getgrgid(Info.st_gid);

	if( pw == NULL || gr == NULL )
	{
        Dialog.message("File Permissions couldn't be checked!!!");
		return 1;
	}

	std::string FileOwner = pw->pw_name;
	std::string FileGroup = gr->gr_name;

	fs::perms Perms = fs::status(Path).permissions();
	
	// === Get User info ===
	
	std::vector <gid_t> Groups;
	GetUserGroups(Groups);

	bool ReadPermRes 	= 0;
	bool WritePermRes	= 0;
	bool ExePermRes		= 0;

	// === Check the Permissions ===

	std::string UserGroupsName;

	// --- Read ---
	
	if( (Perms & fs::perms::others_read) != fs::perms::none )
	{
		ReadPermRes	= 1;
	}

	else
	{
		if( (Perms & fs::perms::group_read) != fs::perms::none )
		{
			for(unsigned int g=0; g<Groups.size(); g++) 
			{
				gr = getgrgid(Groups[g]);
				UserGroupsName = gr->gr_name;

				if( !UserGroupsName.compare(FileGroup) ) 
				{
					ReadPermRes = 1; 
					break;
				}
			}
		}
		
		else
		{
	 		if( (Perms & fs::perms::owner_read) != fs::perms::none)
			{
				if( !FileOwner.compare(getenv("USER")) ) ReadPermRes = 1; 
			}
		}
	} 

	// --- Write ---
	
	if( (Perms & fs::perms::others_write) != fs::perms::none )
	{
		WritePermRes = 1;
	}

	else
	{
		if( (Perms & fs::perms::group_write) != fs::perms::none )
		{
			for(unsigned int g=0; g<Groups.size(); g++) 
			{
				gr = getgrgid(Groups[g]);
				UserGroupsName = gr->gr_name;

				if( !UserGroupsName.compare(FileGroup) ) 
				{
					WritePermRes = 1; 
					break;
				}
			}
		}
		
		else
		{
	 		if( (Perms & fs::perms::owner_write) != fs::perms::none)
			{
				if( !FileOwner.compare(getenv("USER")) ) WritePermRes = 1; 
			}
		}
	} 

	// --- Execute ---

	if( (Perms & fs::perms::others_exec) != fs::perms::none )
	{
		ExePermRes = 1;
	}

	else
	{
		if( (Perms & fs::perms::group_exec) != fs::perms::none )
		{
			for(unsigned int g=0; g<Groups.size(); g++) 
			{
				gr = getgrgid(Groups[g]);
				UserGroupsName = gr->gr_name;

				if( !UserGroupsName.compare(FileGroup) ) 
				{
					ExePermRes = 1; 
					break;
				}
			}
		}
		
		else
		{
	 		if( (Perms & fs::perms::owner_exec) != fs::perms::none)
			{
				if( !FileOwner.compare(getenv("USER")) ) ExePermRes = 1; 
			}
		}
	} 

	// === Resuslts ===
	
    if(Results.size() < 3)
	{
        Dialog.message("Permissions results table too small!!!");
		return 1; 
	}

    Results[0] = ReadPermRes;
    Results[1] = WritePermRes;
    Results[2] = ExePermRes;
	
	return 0;
}

#endif