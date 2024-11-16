#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include "major2.h"

char** splitArguments(char *line) {
        // Reset the index
        int i = 0;
        char **arguments = malloc(512 * sizeof(char*));

        // Seperate the command and the arguments entered
        // by the user
        char *argument = strtok(line, " ");
        while(argument != NULL) {
            arguments[i++] = argument;
            argument = strtok(NULL, " ");
        }
        arguments[i] = NULL;

        return arguments;
}
