#include "major2.h"

int color(char** commandArgs) {

    char *cmd = (char *)malloc(100 * sizeof(char));
    cmd[0] = '\0';
    int i=1;

    while(commandArgs[i] != NULL) {
        strcat(cmd, commandArgs[i]);
        strcat(cmd, " ");
        i++;
    }

    // Remove the last space
    if (strlen(cmd) > 0 && cmd[strlen(cmd) - 1] == ' ') {
        cmd[strlen(cmd) - 1] = '\0';
    }

    // Depending on the inputted color, return an integer.
    // NOTE: does not currently support case sensitivity
    if (strcmp(cmd, "red") == 0) {
        return 1;
    } else if (strcmp(cmd, "green") == 0) {
        return 2;
    } else if (strcmp(cmd, "blue") == 0) {
        return 3;
    } else if (strcmp(cmd, "purple") == 0) {
        return 4;
    } else if (strcmp(cmd, "yellow") == 0) {
        return 5;
    } else {
        printf("Color has been set to default. Please choose a supported color (red, blue, green, yellow, purple).\n");
    }

    free(cmd);
    return -1;
}