#ifndef MAJOR2_H
#define MAJOR2_H

#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>

void interactive();
// int builtInCommands(char *cmd);
char **splitCommandsInLine(char *input);
char **splitCommandsInArguments(char *input);
int runCommands(char* command);

#endif