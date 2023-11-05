#include "ap_flFilesHandling.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

#ifdef _WIN32
	#include <windows.h>
#endif

#include <FL/Fl_Native_File_Chooser.H>

#include "ap_utils.h"
#include "ap_flDialogs.h"

namespace ap {

std::string Browse_FileExists(std::string fileName, bool askOverwriteFlag) {
	namespace fs = std::filesystem;

    DIALOGS dialog;

    if(askOverwriteFlag && fs::exists(fileName) && !dialog.choice_s("File exists:\n%s\n\nDo you want to overwrite it?", fileName.c_str()) ) fileName = ""; //Canceled
    return fileName;
}

std::string Browse(const char *filter, int dialogType, bool askOverwriteFlag) {
    Fl_Native_File_Chooser *ch = new Fl_Native_File_Chooser();
    ch -> filter(filter);
    ch -> type(dialogType);
    ch -> show();

    std::string fileName;

    if(ch -> filename())    fileName = ch -> filename();
    else                    fileName = ""; //Canceled

    if(dialogType == 4 && fileName.length() > 0) { // Check Extension while saving
	    // === Extract Chosen Filter ===

    	int start, end=0;
    	std::string filterExtension;
    	std::string filter = ch -> filter();

    	for(int i=0; i<=ch->filter_value(); i++)
    	{
    		start = filter.find_first_of('*', end);
    		end   = filter.find_first_of ('\n', start);
		
    		filterExtension = filter.substr(start+1, end-start-1);
    	}
	
    	// === Extract File Extension ===
	
    	int id = fileName.find_last_of('.');

    	if(id<0) return Browse_FileExists(fileName + filterExtension, askOverwriteFlag); // No extension, add
        if(id>=0 && !iequals(fileName.substr(id), filterExtension)) return Browse_FileExists(fileName + filterExtension, askOverwriteFlag); // Extension different than in the filter, add

        return Browse_FileExists(fileName, askOverwriteFlag);
    }

    return fileName;
}

#ifdef __linux__

int GetUserGroups(std::vector <gid_t> &Groups) {
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

int CheckPermissions(std::string path, std::vector <bool> &results) {
	namespace fs = std::filesystem;

    DIALOGS dialog;

	// === Get the File info ===
	
	struct stat info;

	if( -1 == stat(path.c_str(), &info) ) {
        dialog.message("File Permissions couldn't be checked!!!");
		return 1;
	}

	struct passwd *pw = getpwuid(info.st_uid);
	struct group  *gr = getgrgid(info.st_gid);

	if( pw == NULL || gr == NULL ) {
        dialog.message("File Permissions couldn't be checked!!!");
		return 1;
	}

	std::string fileOwner = pw->pw_name;
	std::string fileGroup = gr->gr_name;

	fs::perms perms = fs::status(path).permissions();
	
	// === Get User info ===
	
	std::vector <gid_t> groups;
	GetUserGroups(groups);

	bool readPermRes 	= 0;
	bool writePermRes	= 0;
	bool exePermRes		= 0;

	// === Check the Permissions ===

	std::string userGroupsName;

	// --- Read ---
	
	if( (perms & fs::perms::others_read) != fs::perms::none ) {
		readPermRes	= 1;
	}

	else {
		if( (perms & fs::perms::group_read) != fs::perms::none ) {
			for(unsigned int g=0; g<groups.size(); g++) {
				gr = getgrgid(groups[g]);
				userGroupsName = gr->gr_name;

				if( !userGroupsName.compare(fileGroup) ) {
					readPermRes = 1; 
					break;
				}
			}
		}
		
		else {
	 		if( (perms & fs::perms::owner_read) != fs::perms::none) {
				if( !fileOwner.compare(getenv("USER")) ) readPermRes = 1; 
			}
		}
	} 

	// --- Write ---
	
	if( (perms & fs::perms::others_write) != fs::perms::none ) {
		writePermRes = 1;
	}

	else {
		if( (perms & fs::perms::group_write) != fs::perms::none ) {
			for(unsigned int g=0; g<groups.size(); g++) {
				gr = getgrgid(groups[g]);
				userGroupsName = gr->gr_name;

				if( !userGroupsName.compare(fileGroup) ) {
					writePermRes = 1; 
					break;
				}
			}
		}
		
		else {
	 		if( (perms & fs::perms::owner_write) != fs::perms::none) {
				if( !fileOwner.compare(getenv("USER")) ) writePermRes = 1; 
			}
		}
	} 

	// --- Execute ---

	if( (perms & fs::perms::others_exec) != fs::perms::none ) {
		exePermRes = 1;
	}

	else {
		if( (perms & fs::perms::group_exec) != fs::perms::none ) {
			for(unsigned int g=0; g<groups.size(); g++) {
				gr = getgrgid(groups[g]);
				userGroupsName = gr->gr_name;

				if( !userGroupsName.compare(fileGroup) ) {
					exePermRes = 1; 
					break;
				}
			}
		}
		
		else {
	 		if( (perms & fs::perms::owner_exec) != fs::perms::none) {
				if( !fileOwner.compare(getenv("USER")) ) exePermRes = 1; 
			}
		}
	} 

	// === Resuslts ===
	
    if(results.size() < 3) {
        dialog.message("Permissions results table too small!!!");
		return 1; 
	}

    results[0] = readPermRes;
    results[1] = writePermRes;
    results[2] = exePermRes;
	
	return 0;
}

#endif

} // namespace ap
