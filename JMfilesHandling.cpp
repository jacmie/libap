#include "JMfilesHandling.h"

namespace fs = std::filesystem;

std::string Browse_FileExists(std::string FileName, bool AskOverwriteFlag)
{
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

#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include "accctrl.h"
#include "aclapi.h"
#pragma comment(lib, "advapi32.lib")

int win(void)
{
	DWORD dwRtnCode = 0;
	PSID pSidOwner = NULL;
	BOOL bRtnBool = TRUE;
	LPTSTR AcctName = NULL;
	LPTSTR DomainName = NULL;
	DWORD dwAcctName = 1, dwDomainName = 1;
	SID_NAME_USE eUse = SidTypeUnknown;
	HANDLE hFile;
	PSECURITY_DESCRIPTOR pSD = NULL;

	// Get the handle of the file object.
	hFile = CreateFile(
                  TEXT("myfile.txt"),
                  GENERIC_READ,
                  FILE_SHARE_READ,
                  NULL,
                  OPEN_EXISTING,
                  FILE_ATTRIBUTE_NORMAL,
                  NULL);

	// Check GetLastError for CreateFile error code.
	if (hFile == INVALID_HANDLE_VALUE) {
          DWORD dwErrorCode = 0;

          dwErrorCode = GetLastError();
          //_tprintf(TEXT("CreateFile error = %d\n"), dwErrorCode);
          return -1;
	}

	// Get the owner SID of the file.
	dwRtnCode = GetSecurityInfo(
                  hFile,
                  SE_FILE_OBJECT,
                  OWNER_SECURITY_INFORMATION,
                  &pSidOwner,
                  NULL,
                  NULL,
                  NULL,
                  &pSD);

	// Check GetLastError for GetSecurityInfo error condition.
	if (dwRtnCode != ERROR_SUCCESS) {
          DWORD dwErrorCode = 0;

          dwErrorCode = GetLastError();
          //_tprintf(TEXT("GetSecurityInfo error = %d\n"), dwErrorCode);
          return -1;
	}
	/*
	// First call to LookupAccountSid to get the buffer sizes.
	bRtnBool = LookupAccountSid(
                  NULL,           // local computer
                  pSidOwner,
                  AcctName,
                  (LPDWORD)&dwAcctName,
                  DomainName,
                  (LPDWORD)&dwDomainName,
                  &eUse);

	// Reallocate memory for the buffers.
	AcctName = (LPTSTR)GlobalAlloc(
          GMEM_FIXED,
          dwAcctName);

	// Check GetLastError for GlobalAlloc error condition.
	if (AcctName == NULL) {
          DWORD dwErrorCode = 0;

          dwErrorCode = GetLastError();
          _tprintf(TEXT("GlobalAlloc error = %d\n"), dwErrorCode);
          return -1;
	}

    DomainName = (LPTSTR)GlobalAlloc(
           GMEM_FIXED,
           dwDomainName);

    // Check GetLastError for GlobalAlloc error condition.
    if (DomainName == NULL) {
          DWORD dwErrorCode = 0;

          dwErrorCode = GetLastError();
          _tprintf(TEXT("GlobalAlloc error = %d\n"), dwErrorCode);
          return -1;

    }

    // Second call to LookupAccountSid to get the account name.
    bRtnBool = LookupAccountSid(
          NULL,                   // name of local or remote computer
          pSidOwner,              // security identifier
          AcctName,               // account name buffer
          (LPDWORD)&dwAcctName,   // size of account name buffer 
          DomainName,             // domain name
          (LPDWORD)&dwDomainName, // size of domain name buffer
          &eUse);                 // SID type

    // Check GetLastError for LookupAccountSid error condition.
    if (bRtnBool == FALSE) {
          DWORD dwErrorCode = 0;

          dwErrorCode = GetLastError();

          if (dwErrorCode == ERROR_NONE_MAPPED)
              _tprintf(TEXT
                  ("Account owner not found for specified SID.\n"));
          else 
              _tprintf(TEXT("Error in LookupAccountSid.\n"));
          return -1;

    } else if (bRtnBool == TRUE) 

        // Print the account name.
        _tprintf(TEXT("Account owner = %s\n"), AcctName);
	*/
    return 0;
}
/*
int GetUserGroups(std::vector <gid_t> &Groups)
{
	int GroupsNr = 1;
	std::string UserName;

#ifdef WIN32
    UserName = getenv("USERNAME");
#else
    UserName = getenv("USER");
#endif

	Groups.resize(GroupsNr);
	
	struct passwd *pw = getpwnam( UserName.c_str() );
	if(pw == NULL) return 1; 
	
	getgrouplist(&UserName[0], pw->pw_gid, &Groups[0], &GroupsNr);
	Groups.resize(GroupsNr);
	getgrouplist(&UserName[0], pw->pw_gid, &Groups[0], &GroupsNr);

	return 0;
}*/

int CheckPermissions(std::string Path, std::vector <bool> &Results)
{
    /*DIALOGS Dialog;

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
	*/
	return 0;
}
