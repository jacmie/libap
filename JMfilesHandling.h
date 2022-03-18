#ifndef FILES_HANDLING
#define FILES_HANDLING

#include <iostream>
#include <fstream>
#include <string>
//#include <filesystem>

#include <FL/Fl_Native_File_Chooser.H>

#include <boost/algorithm/string/predicate.hpp>

bool DirExists(std::string DirName);
bool FileExists(std::string FileName);
std::string Browse(const char *Filt, int DialogType);

#endif
