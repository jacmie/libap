#ifndef AP_FILES_HANDLING_H
#define AP_FILES_HANDLING_H

#ifndef _WIN32
	#include <string>
	#include <vector>
	
	#include <pwd.h>
	#include <grp.h>
	#include <sys/stat.h>
	
namespace ap {
	int GetUserGroups(std::vector <gid_t> &groups);
	int CheckPermissions(std::string path, std::vector <bool> &results);
} // namespace ap
#endif

namespace ap {
std::string Browse(const char *filt, int dialogType, bool askOverwriteFlag=1);
} // namespace ap

#endif //AP_FILES_HANDLING_H
