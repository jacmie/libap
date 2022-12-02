#ifndef FILES_HANDLING
#define FILES_HANDLING

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

#include <boost/algorithm/string/predicate.hpp>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <pwd.h>
	#include <grp.h>
	#include <sys/stat.h>

	int  GetUserGroups(std::vector <gid_t> &Groups);
	int  CheckPermissions(std::string Path, std::vector <bool> &Results);
#endif

#include <FL/Fl_Native_File_Chooser.H>

#include "JMdialogs.h"

std::string Browse(const char *Filt, int DialogType, bool AskOverwriteFlag=1);
	
#endif