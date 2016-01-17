#include "taskLib.h"
#include "common_log.h"

/* @TODO need according to sys task*/
typedef int TaskID;
typedef int* TaskIDPtr;
typedef void (*TaskCallback) (long, long, long, long, long, long, long, long, \
        long, long);

int createTask(TaskCallback callback, void* args);

void joinTask(TaskID task_id);

