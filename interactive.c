#include "major2.h"

extern int colorID;
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define PURPLE "\x1b[35m"
#define DEFAULT  "\x1b[0m"

void interactive() {
    bool running = true;        //flag
    char input[512];            //user input
    int i = 0;                  //index
    char *cwd = (char *)malloc(100 * sizeof(char));
    char *user = getenv("USER");
    char **commands;
    char *currentColor;         // Set custom color

    while (running) {

        // Set the currentColor based on the return from color()
        switch (colorID) {
            case 1:
                currentColor = RED;
                break;
            case 2:
                currentColor = GREEN;
                break;
            case 3:
                currentColor = BLUE;
                break;
            case 4:
                currentColor = PURPLE;
                break;
            case 5:
                currentColor = YELLOW;
                break;
            default:
                currentColor = DEFAULT;
                break;
        }

        getcwd(cwd, 100); // Get the user's current working directory
        printf("\n%s%s:%s$%s ", currentColor, user,cwd, DEFAULT); // USERNAME:path$
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
