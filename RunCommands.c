#include "major2.h"

int runCommands(char* command) {

    char **commandArgs = splitCommandsInArguments(command);

    if(fork() == 0) {

        // If the user input is not valid,
        // print command not found
        if (execvp(commandArgs[0], commandArgs) == -1) {
            printf("%s: command not found\n", commandArgs[0]);
            exit(1);
        }

    // Parent
    } else {
        // Wait for the child process to finish
        wait((int *)0);
    }
}