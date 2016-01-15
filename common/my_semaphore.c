#include "my_semaphore.h"
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
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
    char* a = getRadomName();
    common_debug("initSemaphore: %s", a);
    MySemaphorePtr tmp = sem_open(a, O_CREAT, S_IRUSR|S_IWUSR, 1);
    return tmp;
}

void waitSemaphore(MySemaphorePtr sem) {
    common_debug("waitSemaphore: %d", sem);
    sem_wait(sem);  
}

void destroySemaphore(MySemaphorePtr sem) {
    common_debug("destroySemaphore: %d", sem);
    sem_close(sem);
}

void postSemaphore(MySemaphorePtr sem) {
    common_debug("postSemaphore: %d", sem);
    sem_post(sem);
}

