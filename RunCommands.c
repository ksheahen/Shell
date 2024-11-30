#include "major2.h"

int runCommands(char* command) {

    int isInput = -1;
    int isOutput = -1;

    if (strstr(command, "<") != NULL) {
        isInput = 1;
    } else if (strstr(command, ">") != NULL) {
        isOutput = 1;
    }

    if (isInput == 1 || isOutput == 1) {

        if (redirection(command, isInput, isOutput) == -1) {
            printf("Error executing redirection\n");
            return -1;
        }

    } 
    
    char **commandArgs = splitCommandsInArguments(command);
    char *path = (char *)malloc(100 * sizeof(char));
    char *s = (char *)malloc(100 * sizeof(char));
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
    // printf("path: %s\n", path); //debug

    // CURRENT BUG: ".." only works sometimes?
    if (strcmp(command, "cd") == 0) {
        // printf("cd\n"); //debug
        // printf("old path: %s\n", getcwd(s, 100)); //100 should be the size of the buffer

        // If no path is specified, go to the user's home directory
        if (strcmp(path, "") == 0 || commandArgs[1] == NULL) {
            chdir(getenv("HOME"));
            // printf("new path: %s\n", getcwd(s, 100)); //debug
            return -1;
        } else {

            //fixes weird bug with it only working sometimes
            if (strcmp(path, "..") == 0) {
                chdir("..");
                return -1;
            }

            else if (chdir(path) == 0) { //change path
                // printf("new path: %s\n", getcwd(s, 100)); //debug
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
    } else {

        if(fork() == 0) {

            // If the user input is not valid, print command not found
            if (execvp(commandArgs[0], commandArgs) == -1) {
                printf("%s: command not found\n", commandArgs[0]);
                exit(1);
            }

        // Parent
        } else {
            // Wait for the child process to finish
            wait((int *)0);
        }
    }
    
    free(s);
    free(path);
}

// I/O Redirection
int redirection(char* command, int isInputRedirection, int isOutputRedirection) {

    int saved_stdin, saved_stdout;  // Store the original stdin and stdout
    saved_stdin = dup(STDIN_FILENO);  // Save the original stdin
    saved_stdout = dup(STDOUT_FILENO); // Save the original stdout

    int ifp, ofp; //input and output file
    char** redirectionArguments;
    char** commandArgs;


    //this works but for some reason wont send user back to entering commands
    if (isInputRedirection == 1) {

        redirectionArguments = SplitCommandsWithInputRedirection(command);
        ifp = open(redirectionArguments[1], O_RDONLY);

        if (ifp == -1) {
            printf("Error opening input file\n");
            return -1;
        }

        dup2(ifp, STDIN_FILENO);
        close(ifp);

        commandArgs = splitCommandsInArguments(redirectionArguments[0]);

        //run the command
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
    } 
    
    
    if (isOutputRedirection == 1) {

        redirectionArguments = SplitCommandsWithOutputRedirection(command);
        ofp = open(redirectionArguments[1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

        dup2(ofp, STDOUT_FILENO);
        close(ofp);

        commandArgs = splitCommandsInArguments(redirectionArguments[0]);

        //run the command
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
        
    }

    // After the command has been executed, restore the original stdin and stdout
    dup2(saved_stdin, STDIN_FILENO);  // Restore stdin
    dup2(saved_stdout, STDOUT_FILENO); // Restore stdout

    close(saved_stdin);  // Close the saved file descriptors
    close(saved_stdout);

    return 0;

}


// Pipelining



