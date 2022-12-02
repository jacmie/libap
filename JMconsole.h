#ifndef _CONSOLE_H
#define _CONSOLE_H
 
#ifdef WIN32
#include <windows.h>
#include <ostream>
 
class CONSOLE : private std::basic_streambuf<char>, public std::ostream 
{
    typedef std::char_traits<char> traits_type;
    HANDLE output;

protected:

    int overflow(int character) 
    {
        if(character != traits_type::eof()) 
        {
            DWORD written;
            WriteConsole(output, &character, 1, &written, NULL);
        }
        
        return traits_type::not_eof(character);
    }

public:
    
    CONSOLE() : std::ostream(this) 
    {
        AllocConsole();
        output = GetStdHandle(STD_OUTPUT_HANDLE);
    
        if(output == INVALID_HANDLE_VALUE || output == NULL)
            setstate(badbit);
    }
    
    ~CONSOLE() 
    {
        FreeConsole(); 
    }
};

#endif
 
#endif // CONSOLE_H
