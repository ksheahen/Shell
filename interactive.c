
#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include "major2.h"

void interactive() {
    bool running = true;    //flag
    char *cmd[100];         //linux commands
    char input[30];         //user input
    int i = 0;              //index

    while (running) {

        printf("\nminor3> ");
        fflush(stdout);
        fgets(input, sizeof(input), stdin);

        //Removes the newline char from user input
        input[strcspn(input, "\n")] = '\0'; 

        // If the user input is "quit", set the flag to false
        // and exit the program.
        if (strcmp(input, "quit") == 0) { 
            running = false; 
            break;
        }

        // Reset the index
        i = 0;

        // Seperate the command and the arguments entered
        // by the user
        char *token = strtok(input, " ");
        while(token != NULL) {
            cmd[i++] = token;
            token = strtok(NULL, " ");
        }
        cmd[i] = NULL; 

        // Child
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

    }

}
