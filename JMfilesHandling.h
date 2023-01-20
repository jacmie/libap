#ifndef FILES_HANDLING
#define FILES_HANDLING

#ifndef _WIN32
	#include <string>
	#include <vector>
	
	#include <pwd.h>
	#include <grp.h>
	#include <sys/stat.h>
	
	int  GetUserGroups(std::vector <gid_t> &Groups);
	int  CheckPermissions(std::string Path, std::vector <bool> &Results);
#endif

std::string Browse(const char *Filt, int DialogType, bool AskOverwriteFlag=1);
	
#endif
