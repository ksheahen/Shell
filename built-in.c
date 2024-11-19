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

    int i = 0;
    char *token = strtok(input, " ");
    while(token != NULL) {
        cmd[i++] = token;
        token = strtok(NULL, " ");
    }
    cmd[i] = NULL; 

    if (s == NULL) {
        printf("error allocating memory");
        exit(0);
    }

    if (strcmp(input, "exit") == 0) {
        // If the user input is "exit", exit the program.
        printf("exiting shell\n");
        exit(0);
        return -1;
        
    } else if (strcmp(input, "cd") == 0) {
        // If the user input is "cd", change the directory.
        printf("cd\n");

        printf("%s\n", getcwd(s, 100)); //100 should be the size of the buffer
        chdir(cmd[1]);
        printf("%s\n", getcwd(s, 100));
        return -1;
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
        //     if(fork() == 0) {

        //     // If the user input is not valid,
        //     // print command not found
        //     if (execvp(cmd[0], cmd) == -1) {
        //         printf("%s: command not found\n", cmd[0]);
        //         exit(1);
        //     }

        //     // Parent
        //     } else {
        //         // Wait for the child process to finish
        //         wait((int *)0);
        //     }
        return 0;
    }
}