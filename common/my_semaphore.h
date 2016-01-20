#include "semLib.h"
#include "common_log.h"

/* the vxworks semaphore type*/
typedef SEM_ID MySemaphorePtr;

/* init a semaphore*/
MySemaphorePtr initSemaphore();

void waitSemaphore(MySemaphorePtr sem);

void destroySemaphore(MySemaphorePtr sem);

void postSemaphore(MySemaphorePtr sem);
