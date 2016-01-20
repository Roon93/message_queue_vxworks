#include "mq_basic.h"

/**
 * create a message for the given information
 *
 * params:
 *  type: the type of the message
 *  sender: the sender id of the message
 *  ttl: the time to live of the message
 *  description: the description of the message
 *  content: the content unit of the message
 * return:
 *  a pointer of the new message
 */
MessagePtr createMessage(MessageType type, TaskIDPtr sender, MSecond ttl,\
        MessageInfo description, ContentPtr content);

/**
 * insert a message into the message queue
 *
 * params:
 *  msg: the message need to insert into the message queue
 * return:
 *  none
 */
void insertMessage(MessagePtr msg);

/**
 * release a message and detach it from the message queue
 *
 * params:
 *  msg: the message need to be released
 *  detach_queue: 1 detach it, 0 not need to detach
 * return:
 *  none
 */
void destroyMessage(MessagePtr msg, int detach_queue);

/**
 * compare the the description
 *
 * params:
 *  msg_desc: the first description
 *  other_desc: the second description
 * return:
 *  none
 */
int compareMessageDescription(MessageInfo msg_desc, MessageInfo other_desc);

/**
 * compare the message and receiver decide whether their match each other
 *
 * params:
 *  msg: the message need to match
 *  receiver: the receiver need to match
 * return:
 *  1: match success
 *  0: failed
 */
int matchMessageReceiver(MessagePtr msg, ReceiverPtr receiver);

/**
 * the callback function for the timeout message, it delete the timeout message
 * in the message queue
 *
 * params:
 *  arg0: the pointer of the message
 *  others: not used
 * return:
 *  none
 */
void messageTimeoutCallback(long arg0, long arg1, long arg2, long arg3, \
        long arg4, long arg5, long arg6, long arg7, long arg8, long arg9);
