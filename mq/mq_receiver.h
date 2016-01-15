#include "mq_basic.h"

ReceiverPtr createReceiver(TaskIDPtr id, MessageInfo desc, MSecond ttl, \
        ReceiverType type, MySemaphorePtr sem, TaskCallback callback, \
        ContentPtrPtr contentPtr);

void insertReceiver(ReceiverPtr receiver);

void destroyReceiver(ReceiverPtr receiver, int detach_queue);

void receiverTimeoutCallback(long arg0, long arg1, long arg2, long arg3, \
        long arg4, long arg5, long arg6, long arg7, long arg8, long arg9);
