#include "taskLib.h"
#include "common_log.h"

/* the task id */
typedef int TaskID;
/* the task id pointer*/
typedef int* TaskIDPtr;
typedef void (*TaskCallback) (long, long, long, long, long, long, long, long, \
        long, long);

/* create a vxworks task*/
int createTask(TaskCallback callback, void* args);

