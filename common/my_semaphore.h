#include <semaphore.h>
#include "common_log.h"

/* @TODO need according to sys sem*/
typedef sem_t* MySemaphorePtr;
typedef sem_t  MySemaphore;

MySemaphorePtr initSemaphore();

void waitSemaphore(MySemaphorePtr sem);

void destroySemaphore(MySemaphorePtr sem);

void postSemaphore(MySemaphorePtr sem);
