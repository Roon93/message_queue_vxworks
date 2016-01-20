#include "my_semaphore.h"

MySemaphorePtr initSemaphore() {
    MySemaphorePtr tmp = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
    return tmp;
}

void waitSemaphore(MySemaphorePtr sem) {
    common_debug("waitSemaphore: %d", sem);
    semTake(sem, WAIT_FOREVER);
}

void destroySemaphore(MySemaphorePtr sem) {
    common_debug("destroySemaphore: %d", sem);
    semDelete(sem);
}

void postSemaphore(MySemaphorePtr sem) {
    common_debug("postSemaphore: %d", sem);
    semGive(sem);
}

