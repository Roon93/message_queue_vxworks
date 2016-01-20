#include <stdio.h>
#include <stdarg.h>

/* set the timer log level*/
void set_timer_log_level(int level);

/* timer loginfo level log*/
void timer_loginfo(char* fmt, ...);

/* timer error level log*/
void timer_error(char* fmt, ...);

/* timer warning level log*/
void timer_warning(char* fmt, ...);

/* timer debug level log*/
void timer_debug(char* fmt, ...);
