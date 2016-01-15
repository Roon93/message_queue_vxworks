#include <pthread.h>
#include "common_log.h"

/* @TODO need according to sys task*/
typedef pthread_t  TaskID;
typedef pthread_t* TaskIDPtr;
typedef void* (*TaskCallback) (void*);

int createTask(TaskIDPtr task_id_ptr, TaskCallback callback, void* args);

void joinTask(TaskID task_id);

