#include "../common/limits.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

#include "ptcp.h"
#include "../config.h"

void displayFile(FilePaths *fPaths, unsigned int cols, bool selected) {
    char *selectedPrefix = "";
    if (selected)
        selectedPrefix = "\x1b[7m";

    struct stat stats;
    char path[PATH_MAX + 1];
    realpath(fPaths->sourcePath, path);

    printf("%c[2K", 27);
    printf("%s%s%s\x1b[0m%s%s", selectedPrefix, DIR_PREFIX_ESCAPE_CODES,
           DIR_PREFIX, selectedPrefix, DIR_NAME_ESCAPE_CODES);

    unsigned int actualChar = strlen(DIR_PREFIX) + strlen(fPaths->sourcePath);

    char *fileStatus = SUCCESS_PREFIX;
    char *fileStatusEC = SUCCESS_PREFIX_ESCAPE_CODES;
    if (fPaths->ignore) {
        fileStatus = ERROR_PREFIX;
        fileStatusEC = ERROR_PREFIX_ESCAPE_CODES;
    }

    unsigned int lineChars =
        strlen(DIR_PREFIX) + strlen(fPaths->sourcePath) + strlen(fileStatus);

    if (lineChars > cols) {
        unsigned int length =
            strlen(fPaths->sourcePath) - (lineChars - cols) - 2;

        char *buff = calloc(length + 3, sizeof(char));
        snprintf(buff, length, "%s", fPaths->sourcePath);
        strcat(buff, "...");
        printf("%s", buff);
        free(buff);
    } else {
        printf("%s", fPaths->sourcePath);
    }

    printf("\x1b[0m%s", selectedPrefix);

    if (lineChars <= cols)
        for (int i = 0; i < cols - actualChar - strlen(fileStatus); i++)
            printf(" ");

    printf("%s%s", fileStatusEC, fileStatus);

    printf("\x1b[0m\n");

    fflush(stdout);
}

void displaySelector(unsigned int page,
                     unsigned int lastPage, unsigned int pageFileCount,
                     unsigned int cols, unsigned int selectedFile,
                     MoveData *mData) {
    printf("\n\x1b[45m");
    printf(
        "page (%d/%d) | h,l - jump between pages | j,k - jump between files | "
        "x - remove file | ENTER - add file\n",
        page + 1, lastPage + 1);
    printf("\x1b[0m");
    int firstFile = page * pageFileCount;

    for (int i = 0; i < pageFileCount; i++) {
        if (i + firstFile >= mData->fileCount)
            printf("\n");
        else
            displayFile(mData->files[i + firstFile], cols,
                        i == selectedFile);
    }
}

void nextPage(unsigned int *actualPage, unsigned int *lastPage) {
    (*actualPage)++;
    if ((*actualPage) > (*lastPage))
        (*actualPage) = (*lastPage);
}

void selectFiles(MoveData *mData) {
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    unsigned int pageFileCount = w.ws_row - 3;
    unsigned int lastPage = mData->fileCount / pageFileCount;

    unsigned int page = 0;
    unsigned int selectedFile = 0;

    char c;

    do {
        int fileIndex = selectedFile + page * pageFileCount;
        if (fileIndex >= mData->fileCount) {
            selectedFile = mData->fileCount % pageFileCount - 1;
            continue;
        }

        displaySelector(page, lastPage, pageFileCount, w.ws_col,
                        selectedFile, mData);
        c = getchar();

        switch (c) {
        case '0':
            selectedFile = 0;
            break;
        case 'j':
            if (selectedFile != pageFileCount - 1)
                selectedFile++;
            break;
        case 'k':
            if (selectedFile != 0)
                selectedFile--;
            break;
        case 'l':
            nextPage(&page, &lastPage);
            break;
        case 'h':
            if (page != 0)
                page--;
            break;
        case '\n':
            mData->files[fileIndex]->ignore = false;
            selectedFile++;
            if (selectedFile >= pageFileCount) {
                nextPage(&page, &lastPage);
                selectedFile = 0;
            }
            break;
        case 'x':
            mData->files[fileIndex]->ignore = true;
            selectedFile++;
            if (selectedFile >= pageFileCount) {
                nextPage(&page, &lastPage);
                selectedFile = 0;
            }
            break;
        }
    } while (c != 'q');

    for (int i = 0; i < mData->fileCount; i++) {
        if (!mData->files[i]->ignore)
            continue;

        struct stat stats;
        stat(mData->files[i]->sourcePath, &stats);

        mData->totalBytes -= stats.st_size;
        mData->ignoredCount++;
    }
}
