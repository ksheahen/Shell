#include "major2.h"

void interactive() {
    bool running = true;    //flag
    char input[512];         //user input
    int i = 0;              //index
    char *cwd = (char *)malloc(100 * sizeof(char)); //cwd
    char *user = getenv("USER");
    char **commands;

    while (running) {

        getcwd(cwd, 100); // Get the user's current working directory
        printf("\n%s:%s$ ", user,cwd); // USERNAME:path$
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

        // Seperate the commands entered by the user
        commands = splitCommandsInLine(input);
        i = 0;

        // Call the runCommands function for each command
        while (commands[i] != NULL) {
            // printf("command: %s\n", commands[i]); //debug
            runCommands(commands[i]);
            i++;
        }
        
    }
}
