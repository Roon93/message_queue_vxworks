#include "common_log.h"

/* @TODO need according to sys sem*/
typedef SEM_ID MySemaphorePtr;
/* typedef SEM_ID MySemaphore;*/

MySemaphorePtr initSemaphore();

void waitSemaphore(MySemaphorePtr sem);

void destroySemaphore(MySemaphorePtr sem);

void postSemaphore(MySemaphorePtr sem);
