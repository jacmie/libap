#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <string>

namespace ap {

// === int ===

int Ch2int(char Ch)
{
    return Ch - '0';
}

char int2Ch(int i)
{    
    return i+'0';
}

std::string Ch2Str(char Ch, int Pos)
{
    return std::string(Pos, Ch);
}

std::string Cstr2Str(char *Cstr)
{
    return std::string(Cstr);
}

char* Str2Cstr(std::string Str)
{
	static char Cstr[15];
    strcpy(Cstr, Str.c_str());
	return Cstr;
}

int Cstr2int(char *Cstr)
{
    return strtol(Cstr, NULL, 10);
    //return =  atoi(Cstr); //int
	//return =  atol(Cstr); //longint
}

char *int2Cstr(int i)
{
	static char Cstr[15];
    sprintf(Cstr, "%i", i);
	return Cstr;
}

std::string int2Str(int i)
{
	std::string str;
    std::stringstream ss;
    ss << i;
    ss >> str;
    return str;
}

int Str2int(std::string str)
{
    std::stringstream ss;
    int i;
    ss << str;
    ss >> i;
    return i;
}

// === float ===

float Cstr2f(char *Cstr)
{
    return strtod(Cstr, NULL);
}

char *f2Cstr(float f)
{
   static char Cstr[32];
   std::string str;
   
   std::stringstream ss;
   ss.precision(8);
   ss << f;
   ss >> str;
   
   strcpy(Cstr, str.c_str());
   
   return Cstr;
}

char *f2Cstr(std::string format, float f)
{
   static char Cstr[32];
   sprintf(Cstr, format.c_str(), f);
   return Cstr;
}

float Str2f(std::string Str)
{
    return strtod(Str.c_str(), NULL);
}

std::string f2Str(float f)
{
   std::string Str;
   std::stringstream ss;
   ss.precision(8);
   ss << f;
   ss >> Str;
   return Str;
}

std::string f2Str(std::string format, float f)
{
   static char Cstr[32];
   sprintf(Cstr, format.c_str(), f);
   return std::string(Cstr);
}

// === double ===

double Cstr2d(char *Cstr)
{
    return strtod(Cstr, NULL);
}

char *d2Cstr(double d)
{
   static char Cstr[32];
   std::string str;
   
   std::stringstream ss;
   ss.precision(16);
   ss << d;
   ss >> str;
   
   strcpy(Cstr, str.c_str());
   
   return Cstr;
}

char *d2Cstr(std::string format, double d)
{
   static char Cstr[32];
   sprintf(Cstr, format.c_str(), d);
   return Cstr;
}

double Str2d(std::string Str)
{
    return strtod(Str.c_str(), NULL);
}

std::string d2Str(double d)
{
   std::string Str;
   std::stringstream ss;
   ss.precision(16);
   ss << d;
   ss >> Str;
   return Str;
}

std::string d2Str(std::string format, double d)
{
   static char Cstr[32];
   sprintf(Cstr, format.c_str(), d);
   return std::string(Cstr);
}

} // namespace ap
