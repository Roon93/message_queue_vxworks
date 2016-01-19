#include <stdio.h>
#include <stdarg.h>

/* set the memory log print level*/
void set_memory_log_level(int level);

/* the loginfo level log*/
void memory_loginfo(char* fmt, ...);

/* the error level log*/
void memory_error(char* fmt, ...);

/* the warning level log*/
void memory_warning(char* fmt, ...);

/*the debug level log*/
void memory_debug(char* fmt, ...);
