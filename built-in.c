#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include "major2.h"

int builtInCommands(char *input) {

    char *s = (char *)malloc(100 * sizeof(char));
    char *cmd[100];         //linux commands
    char *path = (char *)malloc(100 * sizeof(char));

    char **commands;
    char **arguments;

    int i = 0;
    // char *token = strtok(input, " ");
    // while(token != NULL) {
    //     cmd[i++] = token;
    //     token = strtok(NULL, " ");
    // }
    // cmd[i] = NULL; 

    // Seperate the commands entered by the user
    commands = splitCommandsInLine(input);
    i = 0;

    // Call the runCommands function for each command
    while (commands[i] != NULL) {
        // printf("command: %s\n", commands[i]); //debug
        runCommands(commands[i]);
        // arguments = splitCommandsInArguments(commands[i]);
        i++;
    }

    // Create path
    // CD: DOESNT WORK ENCLOSED WITH QUOTES OR WITH / at the first char
    i=1;
    while(arguments[i] != NULL) {
        strcat(path, arguments[i]);
        strcat(path, " ");
        i++;
    }

    // Remove the last space
    if (strlen(path) > 0 && path[strlen(path) - 1] == ' ') {
        path[strlen(path) - 1] = '\0';
    }
    printf("path: %s\n", path); //debug

    if (s == NULL || path == NULL) {
        printf("error allocating memory");
        exit(0);
    }

    if (strcmp(input, "exit") == 0) {
        // If the user input is "exit", exit the program.
        printf("exiting shell\n");
        exit(0);
        return -1;
        
    } else if (strcmp(input, "cd") == 0) {

        // KNOWN BUGS: cut-off for arguments if its long enough

        // If the user input is "cd", change the directory.
        printf("cd\n");
        printf("old path: %s\n", getcwd(s, 100)); //100 should be the size of the buffer

        // If no path is specified, go to the user's home directory
        if (strcmp(path, "") == 0) {
            chdir(getenv("HOME"));
            printf("new path: %s\n", getcwd(s, 100)); //debug
            return -1;
        } else {
            if (chdir(path) == 0) { //change path
                printf("new path: %s\n", getcwd(s, 100)); //debug
                return -1;
            } else {
                printf("error");
                return -1;
            }
        }

    } else if (strcmp(input, "path") == 0) {
        // If the user input is "path", allows users to show the current
        // pathname list, append one pathname, or remove one pathname
        printf("path\n");
        return -1;
    } else if (strcmp(input, "myhistory") == 0) {
        // If the user input is "myhistory", list the shell history.
        printf("myhistory\n");
        return -1;
    } else {
        // printf("other cmds"); //debug
            if(fork() == 0) {

            // If the user input is not valid,
            // print command not found
            if (execvp(cmd[0], cmd) == -1) {
                printf("%s: command not found\n", cmd[0]);
                exit(1);
            }

            // Parent
            } else {
                // Wait for the child process to finish
                wait((int *)0);
            }
        return 0;
    }
    free(s);
    free(path);
}