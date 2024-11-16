
#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
// #include "major2.h"

//int argc - number of arguments
//argv - argument vector

int main(int argc, char *argv[]) {

    char line[512];
    int i = 0;
    char *cmd[512];         //linux commands

    if (argc == 2) {
        //batch mode
        printf("batch mode\n");

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

            // Seperate the command and the arguments entered
            // by the user
            i = 0;
            char *token = strtok(line, ";");
            while(token != NULL) {
                cmd[i++] = token;
                token = strtok(NULL, ";");
            }
            cmd[i] = NULL;


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


        fclose(file);

    } else if (argc == 1) {
        //interactive
        printf("interactive mode\n");
        // interactive();
    } else {
        //error
        printf("error\n");
    }

  return 0;
} 