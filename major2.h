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
#include <signal.h>

void interactive();
int runCommands(char* command);
int redirection(char* command, int isInputRedirection, int isOutputRedirection);
int pipeline(char* command);
char **splitCommandsInLine(char *input);
char **splitCommandsInArguments(char *input);
char **SplitCommandsWithInputRedirection(char* input);
char **SplitCommandsWithOutputRedirection(char* input);
char **SplitCommandsWithPipes(char* input);
int changeDirectory(char** command);
int addToHistory(char* command);
int myCommandHistory(char** commandArgs);

#endif