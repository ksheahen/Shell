#ifndef MAJOR2_H
#define MAJOR2_H

#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

void interactive();
char **splitCommandsInLine(char *input);
char **splitCommandsInArguments(char *input);
int runCommands(char* command);
int redirection(char* command, int isInputRedirection, int isOutputRedirection);
char **SplitCommandsWithInputRedirection(char* input);
char **SplitCommandsWithOutputRedirection(char* input);

#endif