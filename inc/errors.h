#ifndef ERRORS_H
# define ERRORS_H

# include <errno.h>
# include <string.h>

# define ERR_MALLOC "Error with malloc(3)"
# define ERR_READ "Error reading file"
# define ERR_FORMAT "Invalid map format, must be \"*.cub\""
# define ERR_MAZE "Invalid maze"
# define INVALID_PATTERN "Invalid file pattern"
# define INVALID_FILE_PARAM "Missing, unrecognized or duplicated input parameter at line "
# define INVALID_TEXT_FILE_PATTERN "Invalid texture pattern at line "
# define EMPTY_PATTERN "Pattern is empty at line "
# define INVALID_COLOR "Invalid color input at line "
# define INVALID_MAZE_CHAR "Unrecognized character in maze at line "
# define UNCLOSED_MAZE "Unclosed maze at line : "
# define SPAWNING "Missing or too many spawning point "

#endif
