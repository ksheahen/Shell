#include "major2.h"

int main(int argc, char *argv[]) {

    char line[512];
    int i = 0;         
    char **commands;

    if (argc == 2) {
        //batch mode
        // printf("batch mode\n"); //debug

        FILE* file = fopen(argv[1], "r");

        if (file == NULL) {
            printf("error no file");
            exit(0);
        }

        while (fgets(line, sizeof(line), file)) {

            //Removes the newline char
            line[strcspn(line, "\n")] = '\0'; 
            line[strcspn(line, "\r")] = '\0';

            printf("%s\n", line);

            // Seperate the commands entered by the user
            commands = splitCommandsInLine(line);
            i = 0;

            // Call the runCommands function for each command
            while (commands[i] != NULL) {
                // printf("command: %s\n", commands[i]); //debug
                runCommands(commands[i]);
                i++;
            }

        }

        fclose(file); // close the file

    } else if (argc == 1) {
        //interactive
        // printf("interactive mode\n"); //debug
        interactive();
    } else {
        //error
        printf("Error: Too many arguments entered.\n");
    }

  return 0;
} 