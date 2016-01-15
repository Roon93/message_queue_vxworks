#include "mq_log.h"

static int MQ_LOG_LEVEL = 0;

void set_mq_log_level(int level) {
    MQ_LOG_LEVEL = level;
}

void mq_loginfo(char* fmt, ...) {
    va_list args;
    if (MQ_LOG_LEVEL > 0) {
        printf("<-mq_loginfo-> ");
        va_start(args,fmt);
        vprintf(fmt,args);
        va_end(args);
        printf("\n"); 
    }
}

void mq_error(char *fmt, ...) {
    va_list args;
    printf("<-mq_error-> ");
    va_start(args,fmt);
    vprintf(fmt,args);
    va_end(args);
    printf("\n");
}

void mq_warning(char* fmt, ...) {
    va_list args;
    if (MQ_LOG_LEVEL > 1) {
        printf("<-mq_warning-> ");
        va_start(args,fmt);
        vprintf(fmt,args);
        va_end(args);
        printf("\n");
    }
}

void mq_debug(char* fmt, ...) {
    va_list args;
    if (MQ_LOG_LEVEL > 2) {
        printf("<-mq_debug-> ");
        va_start(args,fmt);
        vprintf(fmt,args);
        va_end(args);
        printf("\n");
    }
}

