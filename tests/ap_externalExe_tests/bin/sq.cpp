#include <iostream>

using namespace std;

int main(int argc, char *argv[]) 
{
    cout << endl << "=== Square.exe ===" << endl << endl;

    cout << "ArgNr: " << argc << endl << endl;

    double Sum = 1;

    for(int a=1; a<argc; a++)
    {
        Sum *= strtod(argv[a], NULL);
        cout << "Arg_" << a << "\t" << argv[a] << "\t" << Sum << endl;
    }
    
    cout << endl << "Sum = " << Sum << endl << endl;

    return 0;
}
