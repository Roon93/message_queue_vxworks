#include <stdio.h>
#include <stdarg.h>

/* set the message queue log level*/
void set_mq_log_level(int level);

/* message queue loginfo level log*/
void mq_loginfo(char* fmt, ...);

/* message queue error level log*/
void mq_error(char* fmt, ...);

/* message queue warning level log*/
void mq_warning(char* fmt, ...);

/* message queue debug level log*/
void mq_debug(char* fmt, ...);
