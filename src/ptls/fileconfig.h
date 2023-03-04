#ifndef FILECONFIG_H
typedef enum FileType_ { FT_Directory, FT_Link, FT_File } FileType;

typedef struct FileConfigValues_ {
    char *prefixEscapeCodes;
    char *prefix;
    char *nameEscapeCodes;
} FileConfigValues;

FileConfigValues *getFileConfigValues(FileType type);
#endif
