int Call(char *buffer);
int Pipe(char *Program, char *input, char *log, char *buffer, char *mode);
int CreateProcess(bool Wait, char *Proc, char *Arg);
int CreateProcess(bool Wait, std::string Proc, std::string Arg);