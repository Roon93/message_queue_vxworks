#include "mq_receiver.h"

ReceiverPtr createReceiver(TaskIDPtr id, MessageInfo desc, MSecond ttl, \
        ReceiverType type, MySemaphorePtr sem, TaskCallback callback, \
        ContentPtrPtr contentPtr) {
    ReceiverPtr ptr = (ReceiverPtr)my_malloc(sizeof(Receiver));
    ptr->id = id;
    ptr->desc = desc;
    ptr->ttl = ttl;
    ptr->type = type;
    ptr->callback = callback;
    ptr->sem = sem;
    ptr->tid = -1;
    ptr->contentPtr = contentPtr;
    ptr->next = NULL;
    ptr->pre = NULL;
    mq_debug("createReceiver: desc %s, ttl %d, type %d, contentPtr %d", desc, \
            ttl, type, ptr->contentPtr);
    return ptr;
}

void insertReceiver(ReceiverPtr receiver) {
    mq_debug("insertReceiver: desc %s", receiver->desc);
    if (g_mq_receiver_queue != NULL) {
        receiver->next = g_mq_receiver_queue;
        g_mq_receiver_queue->pre = receiver;
    }
    g_mq_receiver_queue = receiver;
}

void destroyReceiver(ReceiverPtr receiver, int detach_queue) {
    mq_debug("destroyReceiver: %d", receiver);
    mq_debug("destroyReceiver: desc %s, tid %d, detach_queue %d", \
            receiver->desc, receiver->tid, detach_queue);
    /* @TODO the description*/
    if (receiver == NULL) {
        return;
    }
    if (detach_queue == 1) {
        if (receiver->tid >= 0) {
            myClearTimeout(receiver->tid);
        }
        if (receiver->pre == NULL) {
            g_mq_receiver_queue = receiver->next;
        } else {
            receiver->pre->next = receiver->next;
        }
        if (receiver->next != NULL) {
            receiver->next->pre = receiver->pre;
        }
    }
    my_free(receiver);
    receiver = NULL;
    mq_debug("destroyReceiver: g_mq_receiver_queue %d", g_mq_receiver_queue);
}

/* @TODO for vxworks*/
void receiverTimeoutCallback(long arg0, long arg1, long arg2, long arg3, \
        long arg4, long arg5, long arg6, long arg7, long arg8, long arg9) {
    ReceiverPtr ptr = (ReceiverPtr)arg0;
    mq_debug("receiverTimeoutCallback: desc %s, tid %d", ptr->desc, ptr->tid);
    if (ptr->type == MQ_SUSPEND_RECEIVER && ptr->sem != NULL) {
        *(ptr->contentPtr) = NULL;
        postSemaphore(ptr->sem);
    }
    ptr->tid = -1;
    waitSemaphore(g_mq_receiver_sem);
    destroyReceiver(ptr, 1);
    postSemaphore(g_mq_receiver_sem);
}
