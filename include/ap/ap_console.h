#ifndef AP_CONSOLE_H
#define AP_CONSOLE_H
 
#ifdef WIN32
#include <windows.h>
#include <ostream>

namespace ap {

class CONSOLE : private std::basic_streambuf<char>, public std::ostream {
    typedef std::char_traits<char> traits_type;
    HANDLE output;

protected:

    int overflow(int character) {
        if(character != traits_type::eof()) {
            DWORD written;
            WriteConsole(output, &character, 1, &written, NULL);
        }
        
        return traits_type::not_eof(character);
    }

public:
    
    CONSOLE() : std::ostream(this) {
        AllocConsole();
        output = GetStdHandle(STD_OUTPUT_HANDLE);
    
        if(output == INVALID_HANDLE_VALUE || output == NULL)
            setstate(badbit);
    }
    
    ~CONSOLE() {
        FreeConsole(); 
    }
};

} // namespace ap

#endif
 
#endif // AP_CONSOLE_H
