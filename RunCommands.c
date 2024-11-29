#include "major2.h"

int runCommands(char* command) {

    char **commandArgs = splitCommandsInArguments(command);
    char *path = (char *)malloc(100 * sizeof(char));
    char *s = (char *)malloc(100 * sizeof(char));


    // Create path
    // CD: DOESNT WORK ENCLOSED WITH QUOTES OR WITH / at the first char
    int i=1;
    while(commandArgs[i] != NULL) {
        strcat(path, commandArgs[i]);
        strcat(path, " ");
        i++;
    }

    // Remove the last space
    if (strlen(path) > 0 && path[strlen(path) - 1] == ' ') {
        path[strlen(path) - 1] = '\0';
    }
    printf("path: %s\n", path); //debug

    if (strcmp(command, "cd") == 0) {
        // printf("cd\n"); //debug
        printf("old path: %s\n", getcwd(s, 100)); //100 should be the size of the buffer

        // If no path is specified, go to the user's home directory
        if (strcmp(path, "") == 0 || commandArgs[1] == NULL) {
            chdir(getenv("HOME"));
            printf("new path: %s\n", getcwd(s, 100)); //debug
            return -1;
        } else {
            if (chdir(path) == 0) { //change path
                printf("new path: %s\n", getcwd(s, 100)); //debug
                return -1;
            } else {
                printf("Error: invalid directory");
                return -1;
            }
        }
    } else if (strcmp(command, "exit") == 0) {
        printf("exiting...\n"); //debug
        exit(1);
    } else if (strcmp(command, "path") == 0) {
        printf("path");
    } else if (strcmp(command, "myhistory") == 0) {
        printf("myhistory");
    }

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

    free(s);
    free(path);
}