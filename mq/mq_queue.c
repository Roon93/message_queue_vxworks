#include "mq_queue.h"

void addMessage(MessageType type, TaskIDPtr sender, MSecond ttl, \
        MessageInfo description, ContentPtr content) {
    MessagePtr msg = createMessage(type, sender, ttl, description, content);
    ReceiverPtr receiver;
    lockMqGlobalInfo();
    receiver = g_mq_receiver_queue;
    mq_debug("addMessage: type %d, ttl %d, description %s", type, ttl, \
            description);
    mq_debug("addMessage: content data %s, length %d", (char*)content->data, \
            content->length);
    /* scan the receiver queue, check if there is a receiver match the message*/
    while (receiver != NULL) {
        if (matchMessageReceiver(msg, receiver) == 1) {
            mq_debug("addMessage: matched a receiver");
            processReceiverMessage(msg, receiver, 0);
            unlockMqGlobalInfo();
            return;
        }
        receiver = receiver->next;
    }
    /* if matched failed, insert the message into the queue*/
    if (msg->type == MQ_TIMEOUT_MESSAGE) {
        /* if the message is the MQ_TIMEOUT_MESSAGE type, add a timer*/
        mq_debug("addMessage: add a timeout message");
        msg->tid = mySetTimeout(msg->ttl, messageTimeoutCallback, (void*)msg);
        if (msg->tid == -1) {
            my_free(msg);
            unlockMqGlobalInfo();
            return;
        }
    }
    insertMessage(msg);
    unlockMqGlobalInfo();
}

void addReceiver(TaskIDPtr id, MessageInfo desc, MSecond ttl, \
        ReceiverType type, MySemaphorePtr sem, TaskCallback callback, \
        ContentPtrPtr contentPtr) {
    ReceiverPtr receiver = createReceiver(id, desc, ttl, type, sem, callback, \
            contentPtr);
    MessagePtr msg;
    lockMqGlobalInfo();
    msg = g_mq_message_queue;
    mq_debug("addReceiver: desc %s, ttl %d, type %d, contentPtr %d", desc, ttl,\
            type, contentPtr);
    /* scan the receiver queue, check if there is a message matched it*/
    while (msg != NULL) {
        if (matchMessageReceiver(msg, receiver) == 1) {
            processReceiverMessage(msg, receiver, 1);
            unlockMqGlobalInfo();
            return;
        }
        msg = msg->next;
    }
    if (receiver->type != MQ_IMMEDIATELY_RECEIVER) {
        /* insert the receiver to the receiver queue if there is need*/
        mq_debug("addReceiver: add a %d type receiver", type);
        /* add a timer for the receiver*/
        receiver->tid = mySetTimeout(receiver->ttl, receiverTimeoutCallback, \
                (void*)receiver);
        if (receiver->tid == -1) {
            my_free(receiver);
        } else {
            insertReceiver(receiver);
        }
    }
    unlockMqGlobalInfo();
}

void processReceiverMessage(MessagePtr msg, ReceiverPtr receiver, int flag) {
    TaskID tmp_task;
    mq_debug("processReceiverMessage: desc %s, flag %d", msg->desc, flag);
    mq_debug("processReceiverMessage: msg->type %d", msg->type);
    mq_debug("processReceiverMessage: receiver->type %d", receiver->type);
    /* if the receiver is the immediately type, nothing need to do except 
     * send the content of the message to the receiver
     */
    if (receiver->type == MQ_IMMEDIATELY_RECEIVER) {
        mq_debug("processReceiverMessage: imme %d", receiver->contentPtr);
        *(receiver->contentPtr) = msg->content;
        mq_debug("processReceiverMessage: after imme %d", *(receiver->contentPtr));
    } else if (receiver->type == MQ_SUSPEND_RECEIVER) {
        /* if the receiver is the suspend receiver, it need to post the 
         * semaphore to unblock the suspend receiver
         */
        *(receiver->contentPtr) = msg->content;
        postSemaphore(receiver->sem);
    } else {
        /* if the receiver is the callback receiver, it needs to create a 
         * subtask and call the callback function
         */
        mq_debug("processReceiverMessage: callback %d", receiver->callback);
        createTask(receiver->callback, (void*)msg->content);
    }
    msg->content = NULL;
    if (flag == 0) {
        /* message matchs a receiver when insert one*/
        destroyMessage(msg, 0);
        destroyReceiver(receiver, 1);
    } else {
        /* receiver matchs a message when insert one*/
        destroyMessage(msg, 1);
        destroyReceiver(receiver, 0);
    }
}
