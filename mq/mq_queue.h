#include "mq_basic.h"
#include "mq_message.h"
#include "mq_receiver.h"

/* init the message queue global information lock*/
void initMqGlobalInfoLock();

/* lock the global infomation info*/
void lockMqGlobalInfo();

/* unlock the global information*/
void unlockMqGlobalInfo();

/**
 * add message with the given information
 *
 * params:
 *  type: the type of the message
 *  sender: the message sender task id
 *  ttl: the message time to live
 *  description: the description of the message
 *  contentPtr: the content of the message
 * return:
 *  none
 */
void addMessage(MessageType type, TaskIDPtr sender, MSecond ttl, \
        MessageInfo description, ContentPtr content);

/**
 * add a receiver with the given information
 *
 * params:
 *  id: the task id of the receiver
 *  description: the description of the receiver
 *  ttl: the receiver time to live
 *  type: the type of the receiver
 *  sem: the semaphore for the suspended receiver
 *  callback: the callback function of the receiver
 *  contentPtr: the content that the receiver received if there is.
 * return:
 *  none
 */
void addReceiver(TaskIDPtr id, MessageInfo desc, MSecond ttl, \
        ReceiverType type, MySemaphorePtr sem, TaskCallback callback, \
        ContentPtrPtr contentPtr);

/**
 * if there is a message match the receiver process the message and the 
 * receiver.
 *
 * params:
 *  msg: the message that matched
 *  receiver: the receiver that matched
 *  flag: 0: message match the receiver, 1 receiver match the message
 * return:
 *  none
 */
void processReceiverMessage(MessagePtr msg, ReceiverPtr receiver, int flag);


