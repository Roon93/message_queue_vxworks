#include "my_process.h"

#define PRIORITY 0
#define OPTIONS 0
#define STACK_SIZE 0

/* @TODO need to replace it with the vxworks create task*/
int createTask(TaskCallback callback, void* args) {
    common_debug("createTask: %d, %d, %d", args, task_id_ptr, callback);
    return taskSpawn(NULL, PRIORITY, OPTIONS, STACK_SIZE, callback, (long)args,\
            0, 0, 0, 0, 0, 0, 0, 0, 0);
}

/* @TODO need to replace it with the vxworks join*/
void joinTask(TaskID task_id) {
    common_debug("joinTask: before join");
    common_debug("joinTask: after join");
}
