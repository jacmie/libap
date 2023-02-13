#ifndef EXTERNAL_EXE_H
#define EXTERNAL_EXE_H

#include <vector>

int Call(char *buffer);
int Pipe(char *Program, char *input, char *log, char *buffer, char *mode);
int ExeCreateProcess(int ArgNr, char **Arg, bool Wait=1);
int ExeCreateProcess(std::vector <std::string> &Arg, bool Wait=1);

#endif
