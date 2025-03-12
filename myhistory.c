#include "major2.h"
int counter = 0;
char** history;

int addToHistory(char* command) {

    // If counter is 0 (no commands stored), then allocate memory for history array. 
    if (counter == 0) {
        history = malloc(100 * sizeof(char*));
    }

    // Allocate memory for the command and copy it to the history array.
    history[counter] = malloc((strlen(command) + 1) * sizeof(char));
    strcpy(history[counter], command);
    counter++;

    return 0;
}

int myCommandHistory(char** commandArgs) {

    char *args = (char *)malloc(100 * sizeof(char));
    args[0] = '\0';
    int i=1;

    // Concatenate the command arguments
    while(commandArgs[i] != NULL) {
        strcat(args, commandArgs[i]);
        strcat(args, " ");
        i++;
    }

    // Remove the last space
    if (strlen(args) > 0 && args[strlen(args) - 1] == ' ') {
        args[strlen(args) - 1] = '\0';
    }

    // Free the memory allocated for each command and reset the counter.
    if (strcmp(args, "-c") == 0) {
        printf("Command history has been cleared.\n");
        for (int i = 0; i < counter; i++) {
            free(history[i]);
        }
        counter = 0;

    // Print the user's command history
    } else if (strcmp(args, "") == 0) {
        //printf("history print"); //debug
        for (int i = 0; i < counter; i++) {
            printf("%s\n", history[i]);
        }
    }

    free(args);
    return 0;
}
