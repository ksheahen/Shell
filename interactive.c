
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

        printf("\n$ ");
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




        // char *s = (char *)malloc(100 * sizeof(char)); //path 

        // // Built-In Commands

        // if (strcmp(input, "exit") == 0) {
        //     // If the user input is "exit", exit the program.
        //     printf("exiting shell\n");
        //     exit(0);
        
        // } else if (strcmp(input, "cd") == 0) {
        //     // If the user input is "cd", change the directory.
        //     // printf("cd\n"); //debug

        //     //doesn't work rn - need a no-arg function to go back to the previous directory
        //     // error: seg fault
        //     // if (strcmp(cmd[1], "1") == 0 ) {
        //     //     chdir("..");
        //     //     printf("new path: %s\n", getcwd(s, 100));
        //     // }


        //     //doesn't take a path with spaces rn
        //     //cmd = cd /path/to/directory
        //     printf("original path: %s\n", getcwd(s, 100)); //100 should be the size of the buffer
        //     chdir(cmd[1]);
        //     printf("new path: %s\n", getcwd(s, 100));
            
        // } else if (strcmp(input, "path") == 0) {
        //     // If the user input is "path", allows users to show the current
        //     // pathname list, append one pathname, or remove one pathname
        //     printf("path\n");
            
        // } else if (strcmp(input, "myhistory") == 0) {
        //     // If the user input is "myhistory", list the shell history.
        //     printf("myhistory\n");



        if (builtInCommands(input) == -1) {
            continue; 
        } else {
          
                        // // Reset the index
            i = 0;

            // Seperate the command and the arguments entered
            // by the user
            // char *token = strtok(input, " ");
            // while(token != NULL) {
            //     cmd[i++] = token;
            //     token = strtok(NULL, " ");
            // }
            // cmd[i] = NULL; 

            // splitCommandsInLine(input);

            // OTHER COMMANDS
            // printf("other cmds"); //debug
            // if(fork() == 0) {

            // // If the user input is not valid,
            // // print command not found
            // if (execvp(cmd[0], cmd) == -1) {
            //     printf("%s: command not found\n", cmd[0]);
            //     exit(1);
            // }

            // // Parent
            // } else {
            //     // Wait for the child process to finish
            //     wait((int *)0);
            // }
        }
    }
}
