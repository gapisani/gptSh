#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "ptcp.h"

int main(int argc, char **argv) {
    Args *args = parseArgs(argc, argv);

    if (args->help) {
        displayHelp();
        return 0;
    }

    if (args->sourcePath == NULL || args->destPath == NULL) {
        printMessage("You must specify source and destination path", true);
        return 1;
    }

    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    MoveData *mData = getMoveData(args);
    if (mData == NULL) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return 1;
    }

    if (args->interactive)
        selectFiles(mData);

    char buff[25];
    printSize(buff, 25, mData->totalBytes, args->decimalSize);

    printf("Copying %d files (%s)", mData->fileCount - mData->ignoredCount,
           buff);

    copyFiles(args, mData);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    freeMoveData(mData);
    freeArgs(args);

    return 0;
}
