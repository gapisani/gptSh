
#include <stdbool.h>

#ifndef PTLS_TYPES_H
#define PTLS_TYPES_H

typedef struct Args_{

  //Help
  bool help;

  //Path
  char* dirPath;

  //Files
  bool all;
  bool almostAll;
  bool ignoreBackups;
  bool time;

  //List
  bool l;

  //Fields
  bool author;
  bool inode;
  bool noGroup;

  //Fields options
  bool fullTime;
  bool fullSize;
  bool decimalSize;
  bool numericUidGid;

  //Group
  bool noDirsTop;

  //Sort
  bool reverse;
  bool sExtension;
  bool sTime;
}Args;

typedef struct ColumnSizes_{
  int name;
  int uid;
  int gid;
  int inode;
  int size;
  int hardlinks;
}ColumnSizes;

typedef struct Fields_{
  int nameLength;
  char *name;
  char *permissions;
  char *uid;
  char *gid;
  char *date;
  char *time;
  char *inode;
  char *hardlinks;
  char *size;
}Fields;

typedef struct File_{
  char* name;
  struct stat* stats;
}File;

typedef struct DirContent_{
  File** files;
  int fileCount;
}DirContent;

#endif
