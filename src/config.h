// This is GptSh config file

// Prefixes
/*
 * Prefix is displayed before message, file/directory name etc. Prefix can contain multiple chars.
 * If you want to use a special unicode char as prefix, make sure that your terminal"s font can display this char.
 */

#define DIR_PREFIX   " "                             // Prefix for directories
#define FILE_PREFIX  " "                             // Prefix for files
#define LINK_PREFIX  " "                             // Prefix for links

#define ERROR_PREFIX   "  "                          // Prefix displayed before error message
#define SUCCESS_PREFIX "  "                          // Prefix displayed before success message

/*
 * Messages
 */

#define SUCCESS_MESSAGE "Done"                        // Success message


/*
 *Escape codes
 *You can set ansi escape codes, that will be displayed before prefixes or names to give them effects, such as color
 */

#define DIR_PREFIX_ESCAPE_CODES  "\x1B[35m"           // Escape codes for directory prefix
#define FILE_PREFIX_ESCAPE_CODES "\x1B[94m"           // Escape codes for file prefix
#define LINK_PREFIX_ESCAPE_CODES "\x1B[36m"           // Escape codes for link prefix

#define DIR_NAME_ESCAPE_CODES  ""                     // Escape codes for directory name
#define FILE_NAME_ESCAPE_CODES ""                     // Escape codes for file name
#define LINK_NAME_ESCAPE_CODES ""                     // Escape codes for link name

#define ERROR_PREFIX_ESCAPE_CODES  "\x1B[91m"         // Escape codes for error prefix
#define ERROR_MESSAGE_ESCAPE_CODES ""                 // Escape codes for error message

#define SUCCESS_PREFIX_ESCAPE_CODES  "\x1B[92m"       // Escape codes for success prefix
#define SUCCESS_MESSAGE_ESCAPE_CODES ""               // Escape codes for success message

/*
 * Options for ptls script
 */

#define LS_MIN_FILE_OFFSET 5                          // Offset between displayed files/directories


/*
 * Options for ptpwd script
 */

#define PWD_DIR_SEPARATOR "└ "                        // Separator between directories
#define PWD_DIR_SEPARATOR_ESCAPE_CODES ""             // Escape codes for directory separator
#define PWD_NEXTLINE        1                         // Display directories in next lines
#define PWD_NEXTLINE_MARGIN 2                         // Left margin increment for next lines (can be 0 as well)
#define PWD_SHOW_DIR_PREFIX 1                         // Display directory prefixes


/*
 * Options for ptcp script
 */

#define CP_PROGRESSBAR_BORDER_ESCAPE_CODES "\x1B[40m" // Escape codes for progressbar border
#define CP_PROGRESSBAR_ESCAPE_CODES        "\x1B[45m" // Escape codes for progressbar
