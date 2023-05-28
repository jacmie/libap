#ifndef EXTERNAL_EXE_H
#define EXTERNAL_EXE_H

#include <vector>

namespace ap {

//! Call external program
/*!
 * Parent process is redirected to the call. Calling program doesn't respond until the call is done.\n
 * If the called program crushes the calling program will also crush.
 * \param buffer - passed to the system call function
 * \return Result of the system call.
 */
int Call(char *buffer);

//! Creates pipe to the called program
/*!
 * Parent process is redirected to the call. Calling program doesn't respond until the call is done.\n
 * If the called program crushes the calling program will also crush.
 * \param program - the called program
 * \param input - file with data normally passed from the terminal with the '<' sign 
 * \param log - data outputed by the program to the terminal redirected to the file with '>' sign 
 * \param buffer - bufffer for the commands for the program 
 * \param mode - pipe mode:
 * - r - read
 * - w - write
 * \return Result of the pipe call.
 */
int Pipe(char *program, char *input, char *log, char *buffer, char *mode);

//! Creates new process and runs program
/*!
 * Parent process remains responsive.\n
 * If the executed program crushes the parent process is not affected.
 * \param argNr - number of arguments passed
 * \param arg - array of arguments to the executed program 
 * \param wait - flag to wait for the child process until it finishes, default true
 * \return Result from the runned process.
 */
int ExeCreateProcess(int argNr, char **arg, bool wait=1);

//! Creates new process and runs program
/*!
 * Parent process remains responsive.\n
 * If the executed program crushes the parent process is not affected.
 * \param arg - vector of arguments to the executed program 
 * \param wait - flag to wait for the child process until it finishes, default true
 * \return Result from the runned process.
 */
int ExeCreateProcess(std::vector <std::string> &arg, bool wait=1);

} // namespace ap

#endif
