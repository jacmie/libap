#ifndef AP_FILES_HANDLING_H
#define AP_FILES_HANDLING_H

#include <string>

#ifndef _WIN32
	#include <vector>
	
	#include <pwd.h>
	#include <grp.h>
	#include <sys/stat.h>
	
namespace ap {
	
	//! Gets user groups 
	/*!
 	 * \param groups - received list of user groups in system
 	 * \return 0 on success
 	 */
	int GetUserGroups(std::vector <gid_t> &groups);
	
	//! Checks permitions to the file 
	/*!
 	 * \param path - path to the file to check permissions
 	 * \param results - return results 1 on access granted, 
	 *  - results[0] - read permission
	 *  - results[1] - write permission
	 *  - results[2] - execute permission
 	 * \return 0 on success
 	 */
	int CheckPermissions(std::string path, std::vector <bool> &results);

} // namespace ap
#endif

namespace ap {
	
    bool iequals(const std::string &a, const std::string &b);

	//! File, or directory dialog window 
	/*!
 	 * \param filt - filter for file types
	 * The default is NULL, which browses all files. The filter string can be any of:
   	 * - A single wildcard (eg. "*.txt")
     * - Multiple wildcards (eg. "*.{cxx,h,H}")
     * - A descriptive name followed by a "\t" and a wildcard (eg. "Text Files\t*.txt")
     * - A list of separate wildcards with a "\n" between each (eg. "*.{cxx,H}\n*.txt")
     * - A list of descriptive names and wildcards (eg. "C++ Files\t*.{cxx,H}\nTxt Files\t*.txt")
	 * The format of each filter is a wildcard, or an optional user description followed by '\t' and the wildcard.\n
	 * On most platforms, each filter is available to the user via a pulldown menu in the file chooser. The 'All Files' option is always available to the user.
 	 * \param dialogType - sets dialog type
	 * - 0 - browse files (lets user choose one file)
	 * - 1 - browse directories (lets user choose one directory)
	 * - 2 - browse files (lets user choose multiple files)
	 * - 3 - browse directories (lets user choose multiple directories)
	 * - 4 - browse to save a file
	 * - 5 - browse to save a directory
	 *   (see: Fl_Native_File_Chooser::Type)
 	 * \param askOverwriteFlag - should user be aseked to overwrite if file already exists, default 1
 	 * \return Returns file path, on failer returns empty string
 	 */
	std::string Browse(const char *filt, int dialogType, bool askOverwriteFlag=1);

} // namespace ap

#endif //AP_FILES_HANDLING_H
