#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>

#include "ptcp.h"

int main(int argc, char **argv)
{
  Args *args = parseArgs(argc, argv);

  if(args->help)
  {
    displayHelp();
    return 0;
  }

  if(args->sourcePath == NULL || args->destPath == NULL) return 1;

  PtShConfig *config = readConfig();
  
  struct termios oldt, newt;
  
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  MoveData *mData = getMoveData(args, config); 
  if(mData == NULL)
  {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 1;
  }

  if(args->interactive) selectFiles(config, mData);

  printf("%ld bytes\n", mData->totalBytes);
  printf("%d\n", mData->fileCount);

  copyFiles(args, mData);
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  closeConfig(config);
  freeMoveData(mData);
  freeArgs(args);

  return 0;
}
