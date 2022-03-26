#include <string.h>
#include <stdlib.h>
#include "ptmove.h"
#include "argDefs.h"

void getCharArgs(Args* args, char* str){
  for(int i = 1; i < strlen(str); i++)
  {
    switch(str[i])
    {
      case RECURSIVE_ARG:
        args->recursive = true;
        break;
      case INTERACTIVE_ARG:
        args->interactive = true;
        break;
      case UPDATE_ARG:
        args->update = true;
        break;
    }
  }
}

void getWordArg(Args *args, char* str)
{
  if(strcmp(str, RECURSIVE_ARG_W) == 0) args->recursive = true;
  else if(strcmp(str, INTERACTIVE_ARG_W) == 0) args->interactive = true;
  else if(strcmp(str, UPDATE_ARG_W) == 0) args->update = true;
  else if(strcmp(str, HELP_ARG_W) == 0) args->help = true;
}

Args *parseArgs(int argc, char **argv)
{
  Args *args = (Args*)calloc(1, sizeof(Args));
  args->sourcePath = calloc(1, sizeof(char*));

  if(argc == 1) return args;

  for(int i = 1; i < argc; i++)
  {
    if(argv[i][0] == '-'){
      if(argv[i][1] == '-') getWordArg(args, argv[i]);
      else getCharArgs(args, argv[i]);
    }
    else
    {
      args->sourcePath = realloc(args->sourcePath, (args->sourcePathCount+1)*sizeof(char*));
      args->sourcePath[args->sourcePathCount] = calloc(strlen(argv[i])+1, sizeof(char));
      strcpy(args->sourcePath[args->sourcePathCount], argv[i]);
      args->sourcePathCount++;
    }
  }
  args->destPath = calloc(strlen(argv[argc-1])+1, sizeof(char));
  strcpy(args->destPath, argv[argc-1]);

  return args;
}

void freeArgs(Args *args)
{
  for(int i = 0; i < args->sourcePathCount; i++)
    free(args->sourcePath[i]);
  free(args->sourcePath);
  free(args->destPath);
  free(args);
}
