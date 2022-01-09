int Call(char *buffer);
int Pipe(char *Program, char *input, char *log, char *buffer, char *mode);
int CreateProcess(int ArgNr, char **Arg, bool Wait=1);
int CreateProcess(std::vector <std::string> Arg, bool Wait=1);
