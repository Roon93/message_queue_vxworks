#include <stdio.h>
#include <stdarg.h>

/* common module loginfo level*/
void common_loginfo(char* fmt, ...);

/* common module error level log*/
void common_error(char* fmt, ...);

/* common module warning level log*/
void common_warning(char* fmt, ...);

/* common module debug level log*/
void common_debug(char* fmt, ...);
