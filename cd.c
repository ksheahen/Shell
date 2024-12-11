#include "major2.h"

int changeDirectory(char** commandArgs) {

    char *path = (char *)malloc(100 * sizeof(char));
    path[0] = '\0';
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

    // If no path is specified, go to the user's home directory
    if (strcmp(path, "") == 0 || commandArgs[1] == NULL) {
        chdir(getenv("HOME"));
        return -1;
    } else {

        // Change path to the specified directory
        if (chdir(path) == 0) { 
            free(path);
            return -1;
        } else {
            printf("Error: invalid directory\n");
            free(path);
            return -1;
        }
    }

    free(path);

    return 0;
}