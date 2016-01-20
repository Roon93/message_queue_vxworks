#include "mq_basic.h"

/* create a receiver with the given information*/
ReceiverPtr createReceiver(TaskIDPtr id, MessageInfo desc, MSecond ttl, \
        ReceiverType type, MySemaphorePtr sem, TaskCallback callback, \
        ContentPtrPtr contentPtr);

/* insert a receiver into the receiver queue*/
void insertReceiver(ReceiverPtr receiver);

/**
 * destroy a receiver
 *
 * params:
 *  receiver: the receiver need to be destroy
 *  detach_queue: 0 no need to detach, 1 need to detach to the receiver queue
 * return:
 *  none
 */
void destroyReceiver(ReceiverPtr receiver, int detach_queue);
/**
 * the callback function for the receiver when it timeout
 *
 * params:
 *  arg0: the pointer which point to the receiver struct
 *  other: not used
 * return:
 *  none
 */
void receiverTimeoutCallback(long arg0, long arg1, long arg2, long arg3, \
        long arg4, long arg5, long arg6, long arg7, long arg8, long arg9);
