#include "fileconfig.h"
#include "../config.h"
#include <stdlib.h>

FileConfigValues *getFileConfigValues(FileType type) {
    FileConfigValues *val = calloc(1, sizeof(FileConfigValues));
    switch (type) {
    case FT_Directory:
        val->prefixEscapeCodes = DIR_PREFIX_ESCAPE_CODES;
        val->prefix = DIR_PREFIX;
        val->nameEscapeCodes = DIR_NAME_ESCAPE_CODES;
        break;
    case FT_Link:
        val->prefixEscapeCodes = LINK_PREFIX_ESCAPE_CODES;
        val->prefix = LINK_PREFIX;
        val->nameEscapeCodes = LINK_NAME_ESCAPE_CODES;
        break;
    case FT_File:
        val->prefixEscapeCodes = FILE_PREFIX_ESCAPE_CODES;
        val->prefix = FILE_PREFIX;
        val->nameEscapeCodes = FILE_NAME_ESCAPE_CODES;
    }

    return val;
}
