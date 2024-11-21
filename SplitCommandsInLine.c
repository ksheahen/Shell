#include "major2.h"
#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>

char** splitCommandsInLine(char* input) {
    char** cmd = malloc(100 * sizeof(char*));
    int i = 0;
    char* token = strtok(input, " ");
    while(token != NULL) {
        cmd[i++] = token;
        token = strtok(NULL, " ");
    }
    cmd[i] = NULL; 
    return cmd;
}