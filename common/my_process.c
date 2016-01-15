#include "my_process.h"

/* @TODO need to replace it with the vxworks create task*/
int createTask(TaskIDPtr task_id_ptr, TaskCallback callback, void* args) {
    common_debug("createTask: %d, %d, %d", args, task_id_ptr, callback);
    return pthread_create(task_id_ptr, NULL, callback, args);
}

/* @TODO need to replace it with the vxworks join*/
void joinTask(TaskID task_id) {
    common_debug("joinTask: before join");
    pthread_join(task_id, NULL); 
    common_debug("joinTask: after join");
}
