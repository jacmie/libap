#include <string>

namespace ap {

//! Convert from char character to int 
int Ch2int(char Ch);

//! Convert from int to char character 
char int2Ch(int i);

//! Convert from char character to std::string 
std::string Ch2Str(char Ch, int Pos);


//! Convert from C string to std::string 
std::string Cstr2Str(char *Cstr);

//! Convert from std::string to C string 
char *Str2Cstr(std::string Str);


//! Convert from C string to int 
int Cstr2int(char *Cstr);

//! Convert from int to C string 
char *int2Cstr(int i);

//! Convert from int to std::string 
std::string int2Str(int i);

//! Convert from std::string to int 
int Str2int(std::string str);


//! Convert from C string to float 
float Cstr2f(char *Cstr);

//! Convert from float to C string with sprintf like format 
char *f2Cstr(std::string format, float f);

//! Convert from float to C string 
char *f2Cstr(float f);

//! Convert from std::string to float 
float Str2f(std::string Str);

//! Convert from float to std::string 
std::string f2Str(float f);

//! Convert from float to std::string with sprintf like format 
std::string f2Str(std::string format, float f);


//! Convert from C string to double 
double Cstr2d(char *Cstr);

//! Convert from double to C string with sprintf like format 
char *d2Cstr(std::string format, double d);

//! Convert from double to C string 
char *d2Cstr(double d);

//! Convert from std::string to double 
double Str2d(std::string Str);

//! Convert from double to std::string 
std::string d2Str(double d);

//! Convert from double to std::string with sprintf like format 
std::string d2Str(std::string format, double d);

} // namespace ap
