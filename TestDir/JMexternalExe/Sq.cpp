#include <iostream>

using namespace std;

int main(int argc, char *argv[]) 
{
    clog << endl << "=== Square.exe ===" << endl << endl;

    clog << "ArgNr: " << argc << endl << endl;

    double Sum = 1;

    for(int a=1; a<argc; a++)
    {
        Sum *= strtod(argv[a], NULL);
        clog << "Arg_" << a << "\t" << argv[a] << "\t" << Sum << endl;
    }
    
    clog << endl << "Sum = " << Sum << endl << endl;

    return 0;
}
