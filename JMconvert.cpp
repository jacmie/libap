#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// === int ===

int Ch2int(char Ch)
{
    return Ch - '0';
}

char int2Ch(int i)
{    
    return i+'0';
}

string Ch2Str(char Ch, int Pos)
{
    return string(Pos, Ch);
}

string Cstr2Str(char *Cstr)
{
    return string(Cstr);
}

char* Str2Cstr(string Str)
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

string int2Str(int i)
{
	string str;
    stringstream ss;
    ss << i;
    ss >> str;
    return str;
}

int Str2int(string str)
{
    stringstream ss;
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
   
   stringstream ss;
   ss.precision(8);
   ss << f;
   ss >> Cstr;
   return Cstr;
}

char *f2Cstr(string format, float f)
{
   static char Cstr[32];
   sprintf(Cstr, format.c_str(), f);
   return Cstr;
}

float Str2f(string Str)
{
    return strtod(Str.c_str(), NULL);
}

string f2Str(float f)
{
   string Str;
   stringstream ss;
   ss.precision(8);
   ss << f;
   ss >> Str;
   return Str;
}

string f2Str(string format, float f)
{
   static char Cstr[32];
   sprintf(Cstr, format.c_str(), f);
   return string(Cstr);
}

// === double ===

double Cstr2d(char *Cstr)
{
    return strtod(Cstr, NULL);
}

char *d2Cstr(double d)
{
   static char Cstr[32];
   
   stringstream ss;
   ss.precision(16);
   ss << d;
   ss >> Cstr;
   return Cstr;
}

char *d2Cstr(string format, double d)
{
   static char Cstr[32];
   sprintf(Cstr, format.c_str(), d);
   return Cstr;
}

double Str2d(string Str)
{
    return strtod(Str.c_str(), NULL);
}

string d2Str(double d)
{
   string Str;
   stringstream ss;
   ss.precision(16);
   ss << d;
   ss >> Str;
   return Str;
}

string d2Str(string format, double d)
{
   static char Cstr[32];
   sprintf(Cstr, format.c_str(), d);
   return string(Cstr);
}
