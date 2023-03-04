#include "../config.h"
#include "../common/display.h"
#include "../common/limits.h"
#include <stdio.h>
#include <string.h>

#include "argDefs.h"
#include "ptpwd.h"

void displayHelp() {
    printf("Syntax: ptpwd [ARGS]\n");
    printf("\nArguments:\n");
    printHelpLine(LOGICAL_PATH_ARG, LOGICAL_PATH_ARG_W, LOGICAL_PATH_ARG_DESC);
}

PathDirs *getDirs(char *path) {
    PathDirs *dirs = malloc(sizeof(PathDirs));

    for (int i = 0; i < strlen(path); i++)
        if (path[i] == '/')
            dirs->count++;

    dirs->names = calloc(dirs->count, sizeof(char *));

    int actualChar = 0;
    for (int i = 0; i < dirs->count; i++) {
        int length = 0;
        for (int j = actualChar + 1; j < strlen(path); j++)
            if (path[j] == '/')
                break;
            else
                length++;

        dirs->names[i] = calloc(length + 1, sizeof(char));
        strncpy(dirs->names[i], (path + actualChar + 1), length);
        actualChar += length + 1;
    }

    return dirs;
}

void freeDirs(PathDirs *dirs) {
    for (int i = 0; i < dirs->count; i++) {
        free(dirs->names[i]);
    }
    free(dirs->names);
    free(dirs);
}

void displayDir(char *name) {
    if (PWD_SHOW_DIR_PREFIX)
        printf("%s%s\x1b[0m%s", DIR_PREFIX_ESCAPE_CODES, DIR_PREFIX, DIR_NAME_ESCAPE_CODES);

    printf("%s\x1b[0m", name);

    if (PWD_NEXTLINE) printf("\n");
}

void display(char *path) {
    PathDirs *dirs = getDirs(path);

    for (int i = 0; i < dirs->count; i++) {
        if (PWD_NEXTLINE) {
            for (int x = 0; x < PWD_NEXTLINE_MARGIN * i; x++)
                printf(" ");
        }
        printf("%s%s\x1b[0m", PWD_DIR_SEPARATOR_ESCAPE_CODES, PWD_DIR_SEPARATOR);
        displayDir(dirs->names[i]);
    }

    if (PWD_NEXTLINE)
        printf("\n");

    freeDirs(dirs);
}

int main(int argc, char **argv) {
    Args *args = parseArgs(argc, argv);

    if (args->help) {
        displayHelp();
        return 0;
    }

    char *pwd = getenv("PWD");

    if (!args->logical) {
        char *tmp = calloc(PATH_MAX, sizeof(char));
        realpath(pwd, tmp);
        pwd = tmp;
    }

    display(pwd);

    if (!args->logical)
        free(pwd);
    free(args);

    return 0;
}
