#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include "major2.h"

void runCommand(char *cmd) {

    char** cmdArgs = splitArguments(cmd);
    if (cmdArgs == NULL) {
        printf("error spliting");
        exit(0);
    }
    // Child
    if(fork() == 0) {

        // If the user input is not valid,
        // print command not found
        if (execvp(cmdArgs[0], cmdArgs) == -1) {
            printf("command not found\n", cmd[0]);
            exit(1);
        }

    // Parent
    } else {
        // Wait for the child process to finish
        wait((int *)0);
    }

    free(cmdArgs);

}