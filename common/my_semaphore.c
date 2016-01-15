#include "my_semaphore.h"
#include <stdlib.h>
#include <stdio.h>

char* getRadomName() {
    int num = rand() % 300;
    char *a = (char *)malloc(4);
    int tmp;
    int i = 0;
    while (i < 3) {
        tmp = num % 10;
        num /= 10;
        a[i++] = tmp + '0';
    }
    a[3] = 0;
    printf("char %s\n", a);
    return a;
}

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

