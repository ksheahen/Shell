#include "major2.h"

// Split commands entered by the user (;)
char** splitCommandsInLine(char* input) {
    char** cmds = malloc(100 * sizeof(char*));
    int i = 0;

    if (!cmds) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    char* token = strtok(input, ";");
    while(token != NULL) {
        cmds[i++] = token;
        token = strtok(NULL, ";");
    }
    cmds[i] = NULL; 
    return cmds;
}

// Split the commands into its respective arguments
char** splitCommandsInArguments(char* input) {
    char** arguments = malloc(100 * sizeof(char*));
    int i = 0;

    if (!arguments) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    char* token = strtok(input, " ");
    while(token != NULL) {
        arguments[i++] = token;
        token = strtok(NULL, " ");
    }
    arguments[i] = NULL; 
    return arguments;
}

// Split the commands and text for intput direction (<)
char** SplitCommandsWithInputRedirection(char* input) {
    char** arguments = malloc(100 * sizeof(char*));
    int i = 0;

    if (!arguments) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    char* token = strtok(input, "<");
    while(token != NULL) {
        arguments[i++] = token;
        token = strtok(NULL, "<");
    }
    arguments[i] = NULL; 
    return arguments;
}

// Split the commands and text for otput direction (>)
char**  SplitCommandsWithOutputRedirection(char* input) {
    char** arguments = malloc(100 * sizeof(char*));
    int i = 0;

    if (!arguments) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    char* token = strtok(input, ">");
    while(token != NULL) {
        arguments[i++] = token;
        token = strtok(NULL, ">");
    }
    arguments[i] = NULL; 
    return arguments;
}