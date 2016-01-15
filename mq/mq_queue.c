#include "mq_queue.h"

void addMessage(MessageType type, TaskIDPtr sender, MSecond ttl, \
        MessageInfo description, ContentPtr content) {
    MessagePtr msg = createMessage(type, sender, ttl, description, content);
    ReceiverPtr receiver = g_mq_receiver_queue;
    mq_debug("addMessage: type %d, ttl %d, description %s", type, ttl, \
            description);
    mq_debug("addMessage: content data %s, length %d", (char*)content->data, \
            content->length);
    while (receiver != NULL) {
        if (matchMessageReceiver(msg, receiver) == 1) {
            mq_debug("addMessage: matched a receiver");
            processReceiverMessage(msg, receiver, 0);
            return;
        }
        receiver = receiver->next;
    }
    insertMessage(msg);
    if (msg->type == MQ_TIMEOUT_MESSAGE) {
        mq_debug("addMessage: add a timeout message");
        msg->tid = mySetTimeout(msg->ttl, messageTimeoutCallback, (void*)msg);
    }
}

void addReceiver(TaskIDPtr id, MessageInfo desc, MSecond ttl, \
        ReceiverType type, MySemaphorePtr sem, TaskCallback callback, \
        ContentPtrPtr contentPtr) {
    ReceiverPtr receiver = createReceiver(id, desc, ttl, type, sem, callback, \
            contentPtr);
    MessagePtr msg = g_mq_message_queue;
    mq_debug("addReceiver: desc %s, ttl %d, type %d, contentPtr %d", desc, ttl,\
            type, contentPtr);
    while (msg != NULL) {
        if (matchMessageReceiver(msg, receiver) == 1) {
            processReceiverMessage(msg, receiver, 1);
            return;
        }
        msg = msg->next;
    }
    if (receiver->type != MQ_IMMEDIATELY_RECEIVER) {
        insertReceiver(receiver);
        mq_debug("addReceiver: add a %d type receiver", type);
        receiver->tid = mySetTimeout(receiver->ttl, receiverTimeoutCallback, \
                (void*)receiver);
    }
}

void processReceiverMessage(MessagePtr msg, ReceiverPtr receiver, int flag) {
    TaskID tmp_task;
    mq_debug("processReceiverMessage: desc %s, flag %d", msg->desc, flag);
    mq_debug("processReceiverMessage: msg->type %d", msg->type);
    mq_debug("processReceiverMessage: receiver->type %d", receiver->type);
    if (receiver->type == MQ_IMMEDIATELY_RECEIVER) {
        mq_debug("processReceiverMessage: imme %d", receiver->contentPtr);
        *(receiver->contentPtr) = msg->content;
        mq_debug("processReceiverMessage: after imme %d", *(receiver->contentPtr));
    } else if (receiver->type == MQ_SUSPEND_RECEIVER) {
        *(receiver->contentPtr) = msg->content;
        postSemaphore(receiver->sem);
    } else {
        mq_debug("processReceiverMessage: callback %d", receiver->callback);
        createTask(&tmp_task, receiver->callback, (void*)msg->content);
    }
    msg->content = NULL;
    if (flag == 0) {
        destroyMessage(msg, 0);
        destroyReceiver(receiver, 1);
    } else {
        destroyMessage(msg, 1);
        destroyReceiver(receiver, 0);
    }
}
