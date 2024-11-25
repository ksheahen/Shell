
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
    char *cmd[512];         //linux commands
    char input[512];         //user input
    int i = 0;              //index
     char *cwd = (char *)malloc(100 * sizeof(char)); //cwd


    while (running) {

        //commenting this out for now idk if they want the cwd printed each time
        //getcwd(cwd, 100); // Get the user's current working directory
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

        if (builtInCommands(input) == -1) {
            continue; 
        } 
        
    }
}
