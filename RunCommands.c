#include "major2.h"

int runCommands(char* command) {

    // flags
    int isInput = -1;
    int isOutput = -1;
    int isPipe = -1;

    if (strstr(command, "<") != NULL) {
        isInput = 1;
    } else if (strstr(command, ">") != NULL) {
        isOutput = 1;
    } else if (strstr(command, "|") != NULL) {
        isPipe = 1;
    }

    if (isInput == 1 || isOutput == 1) {

        if (redirection(command, isInput, isOutput) == -1) {
            printf("Error executing redirection\n");
            return -1;
        } else {
            return 0;
        }

    } else if (isPipe == 1) {
        if (pipeline(command) == -1) {
            printf("Error executing pipeline\n");
            return -1;
        } else {
            return 0;
        }
    }
    
    char **commandArgs = splitCommandsInArguments(command);
    char *path = (char *)malloc(100 * sizeof(char));
    path[0] = '\0';
    // char *s = (char *)malloc(100 * sizeof(char));
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

            if (chdir(path) == 0) { //change path
                // printf("new path: %s\n", getcwd(s, 100)); //debug
                free(path);
                return -1;
            } else {
                printf("Error: invalid directory\n");
                free(path);
                return -1;
            }
        }
    } else if (strcmp(command, "exit") == 0) {
        // printf("exiting...\n"); //debug
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
    
    // free(s);
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


// Pipes
int pipeline(char* command) {

    char** pipes = SplitCommandsWithPipes(command); //split the commands with pipes
    int counter = 0;
    int commands = 0;
    char **commandArgs;
    char **commandArgs2;
    char **commandArgs3;
    int child1, child2, child3;
    int pipeOne, pipeTwo;

    // Count the number of commands seperated by pipes
    while(pipes[counter] != NULL) {
        counter++;
        commands++;
    }

    switch (commands) {

        // If there are two commands (one pipe), execute case 2.
        case 2:
            // Split the two commands with their respective arguments
            commandArgs = splitCommandsInArguments(pipes[0]);
            commandArgs2 = splitCommandsInArguments(pipes[1]);

            int fd[2]; //file descriptor
            pipeOne = pipe(fd); //create a pipe

            // Check for error creating the pipe
            if (pipeOne == -1) {
                printf("Error creating pipe\n");
                return -1;
            }

            // Execute the first command
            if ((child1 = fork()) == 0) {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);

                if (execvp(commandArgs[0], commandArgs) == -1) {
                    printf("%s: command not found\n", commandArgs[0]);
                    exit(1);
                }
            }

            // Execute the second command
            if ((child2 = fork()) == 0) {
                close(fd[1]);
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);

                if (execvp(commandArgs2[0], commandArgs2) == -1) {
                    printf("%s: command not found\n", commandArgs2[0]);
                    exit(1);
                }
            }

            // Close the file descriptors
            close(fd[0]);
            close(fd[1]);

            // Wait for the child processes to finish
            waitpid(child1, NULL, 0);
            waitpid(child2, NULL, 0);

            break;
        // If there are three commands (two pipes), execute case 3.
        case 3:
            // Split the three commands with their respective arguments
            commandArgs = splitCommandsInArguments(pipes[0]);
            commandArgs2 = splitCommandsInArguments(pipes[1]);
            commandArgs3 = splitCommandsInArguments(pipes[2]);

            // File descriptors
            int fd1[2]; 
            int fd2[2];

            // Create the pipes
            pipeOne = pipe(fd1);
            pipeTwo = pipe(fd2);

            // Check for error creating the pipes
            if (pipeOne == -1 || pipeTwo == -1) {
                printf("Error creating pipe\n");
                return -1;
            }

            // Execute the first command
            if ((child1 = fork()) == 0) {
                dup2(fd1[1], STDOUT_FILENO);
                close(fd1[0]);
                close(fd1[1]);
                close(fd2[0]);
                close(fd2[1]);

                if (execvp(commandArgs[0], commandArgs) == -1) {
                    printf("%s: command not found\n", commandArgs[0]);
                    exit(1);
                }
            }

            // Execute the second command
            if ((child2 = fork()) == 0) {
                dup2(fd1[0], STDIN_FILENO);
                dup2(fd2[1], STDOUT_FILENO);
                close(fd1[0]);
                close(fd1[1]);
                close(fd2[0]);
                close(fd2[1]);

                if (execvp(commandArgs2[0], commandArgs2) == -1) {
                    printf("%s: command not found\n", commandArgs2[0]);
                    exit(1);
                }
            }

            // Execute the third command
            if ((child3 = fork()) == 0) {
                dup2(fd2[0], STDIN_FILENO);
                close(fd1[0]);
                close(fd1[1]);
                close(fd2[0]);
                close(fd2[1]);

                if (execvp(commandArgs3[0], commandArgs3) == -1) {
                    printf("%s: command not found\n", commandArgs3[0]);
                    exit(1);
                }
            }

            // Close the file descriptors
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[0]);
            close(fd2[1]);

            // Wait for the child processes to finish
            waitpid(child1, NULL, 0);
            waitpid(child2, NULL, 0);
            waitpid(child3, NULL, 0);
            
            break;

        // If there are more than three commands (3 or more pipes), print an error message.
        default:
            printf("Error: too many pipes\n");
            return -1;

    }

    return 0;
}



