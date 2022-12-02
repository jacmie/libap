#ifndef FILES_HANDLING
#define FILES_HANDLING

#include <iostream>
#include <fstream>
#include <string>

#ifdef _WIN32
	#include <windows.h>
#endif

//#include <pwd.h>
//#include <grp.h>
//#include <sys/stat.h>
#include <filesystem>

#include <FL/Fl_Native_File_Chooser.H>

#include <boost/algorithm/string/predicate.hpp>

#include "JMdialogs.h"

std::string Browse(const char *Filt, int DialogType, bool AskOverwriteFlag=1);
//int  GetUserGroups(std::vector <gid_t> &Groups);
int  CheckPermissions(std::string Path, std::vector <bool> &Results);

#endif
