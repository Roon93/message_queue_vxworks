#include "mq_basic.h"

ReceiverPtr createReceiver(TaskIDPtr id, MessageInfo desc, MSecond ttl, \
        ReceiverType type, MySemaphorePtr sem, TaskCallback callback, \
        ContentPtrPtr contentPtr);

void insertReceiver(ReceiverPtr receiver);

void destroyReceiver(ReceiverPtr receiver, int detach_queue);

void *receiverTimeoutCallback(void* args);
