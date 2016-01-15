#include "common_log.h"

#define COMMON_LOG_LEVEL  3

void common_loginfo(char* fmt, ...) {
    va_list args;
    if (COMMON_LOG_LEVEL > 0) {
        printf("<-common_loginfo-> ");
        va_start(args,fmt);
        vprintf(fmt,args);
        va_end(args);
        printf("\n"); 
    }
}

void common_error(char *fmt, ...) {
    va_list args;
    printf("<-common_error-> ");
    va_start(args,fmt);
    vprintf(fmt,args);
    va_end(args);
    printf("\n");
}

void common_warning(char* fmt, ...) {
    va_list args;
    if (COMMON_LOG_LEVEL > 1) {
        printf("<-common_warning-> ");
        va_start(args,fmt);
        vprintf(fmt,args);
        va_end(args);
        printf("\n");
    }
}

void common_debug(char* fmt, ...) {
    va_list args;
    if (COMMON_LOG_LEVEL > 2) {
        printf("<-common_debug-> ");
        va_start(args,fmt);
        vprintf(fmt,args);
        va_end(args);
        printf("\n");
    }
}

