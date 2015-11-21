#include <string>

int     Ch2int(char Ch);
char   int2Ch(int i);
std::string  Ch2Str(char Ch, int Pos);

std::string Cstr2Str(char *Cstr);
char   *Str2Cstr(std::string Str);

int   Cstr2int(char *Cstr);
char  *int2Cstr(int i);
std::string int2Str(int i);
int    Str2int(std::string str);

double Cstr2d(char *Cstr);
char     *d2Cstr(double d);
double  Str2d(std::string Str);
std::string    d2Str(double d);