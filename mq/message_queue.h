#include "mq_basic.h"
#include "mq_queue.h"

/* Show the current message queue content*/
void showMessageQueue();

/* Show the current receiver queue content*/
void showReceiverQueue();

/* Initialize the MQ, include the timer and memory manage*/
void initMQ(int log_level_mq, int log_level_timer, int log_lever_memory);

/* Deinitialize the MQ, include the the timer, memory manage, the message*/
/* Queue and the receiver queue*/
void deinitMQ();

/**
 * Add a normal message, this kind of message will stay at the message queue
 * if no receiver request it
 * 
 * params:
 *  id: the taskid of which add the message
 *  description: the description of the message
 *  data: the data that the message load
 * return:
 *  none
 */
void MQAddNormalMessage(TaskIDPtr id, MessageInfo description, void* data, \
        int data_length);

/**
 * Add a timeout message, this kind of message will timeout and removed if no
 * receiver request it.
 *
 * params:
 *  id: the taskid of which add the message
 *  description: the description of the message
 *  data: the data that the message load
 *  ttl: the time to live of this message
 * return:
 *  none
 */
void MQAddTimeoutMessage(TaskIDPtr id, MessageInfo description, void* data, \
        int data_length, MSecond ttl);

/**
 * Add a immediately receiver, this kind of receiver will return immediately if
 * it didn't match any message at the first scan
 *
 * params:
 *  id: the taskid which add the receiver
 *  description: the description of the receiver
 *  contentPtr: the pointer which receive the matched message content
 */
void MQAddImmediatelyReceiver(TaskIDPtr id, MessageInfo description, \
        ContentPtrPtr contentPtr);

/**
 * Add a suspend receiver, this kind of receiver will not return until it has
 * matched a message or timeout.
 *
 * params:
 *  id: the task id which add this receiver
 *  description: the description of this receiver
 *  ttl: the time to live of this receiver
 *  contentPtr: the pointer which receive the matched message content
 */
void MQAddSuspendReceiver(TaskIDPtr id, MessageInfo description, MSecond ttl, \
        ContentPtrPtr contentPtr);

/**
 * Add a callback receiver, this kind of receiver will return immediately but
 * it will provide a callback function.If it matched a message success, the 
 * callback function will be called; If it timeout, nothing will happen. 
 *
 * params:
 *  id: the task id which add this receiver
 *  description: the description of this receiver
 *  ttl: the time to live of this receiver
 *  callback: the callback function pointer
 */
void MQAddCallbackReceiver(TaskIDPtr id, MessageInfo description, MSecond ttl, \
         TaskCallback callback);
