#include "semLib.h"
#include "common_log.h"

/* the vxworks semaphore type*/
typedef SEM_ID MySemaphorePtr;

/* init a semaphore*/
MySemaphorePtr initSemaphore();

/* take a semaphore*/
void waitSemaphore(MySemaphorePtr sem);

/* delete a semaphore*/
void destroySemaphore(MySemaphorePtr sem);

/* give a semaphore*/
void postSemaphore(MySemaphorePtr sem);
