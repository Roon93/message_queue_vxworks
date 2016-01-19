#include "mq_test.h"

void test_add_normal_message(char* desc, char* data, int length) {
    printf("----------------------normal message---------------------------\n");
    printf("test add normal message: desc %s, data %s, length %d\n", desc, \
            data, length);
    MQAddNormalMessage(NULL, desc, data, length);
    printf("test add normal message success\n");
    printf("---------------------------------------------------------------\n");
}

void test_add_timeout_message(char* desc, char* data, int length, int ms) {
    printf("-------------------------timeout messag------------------------\n");
    printf("test add timeout message: desc %s, data %s, length %d, ms %d\n", \
            desc, data, length, ms);
    MQAddTimeoutMessage(NULL, desc, data, length, ms);
    printf("---------------------------------------------------------------\n");
}

void test_add_imm_receiver(char* desc) {
    ContentPtrPtr contentPtr;
    printf("--------------------------im receiver--------------------------\n");
    printf("test add immediately receiver: desc %s\n", desc);
    contentPtr = (ContentPtrPtr)my_malloc(sizeof(ContentPtr));
    *contentPtr = NULL;
    MQAddImmediatelyReceiver(NULL, desc, contentPtr);
    printf("test add immediately receiver success\n");
    if ((*contentPtr) != NULL) {
        printf("the data %s, length %d\n", (*contentPtr)->data, \
                (*contentPtr)->length);
    }
    printf("---------------------------------------------------------------\n");
}

void test_add_suspend_receiver(char* desc, MSecond ms) {
    ContentPtrPtr contentPtr;
    printf("---------------------------suspend receiver--------------------\n");
    printf("test add suspend receiver: desc %s, ms %lld\n", desc, ms);
    contentPtr = (ContentPtrPtr)my_malloc(sizeof(ContentPtr));
    *contentPtr = NULL;
    printf("Suspend before back\n");
    MQAddSuspendReceiver(NULL, desc, ms, contentPtr);
    printf("Suspend after back\n");
    printf("test add suspend receiver success\n");
    if (*contentPtr != NULL) {
        printf("the data %s, length %d\n", (*contentPtr)->data, \
                (*contentPtr)->length);
    }
    printf("---------------------------------------------------------------\n");
}

void test_add_callback_receiver(char* desc, MSecond ms, TaskCallback callback) {
    printf("---------------------------callback receiver--------------------\n");
    printf("test add callback receiver: desc %s, ms %lld, callback %d\n", desc,\
            ms, callback);
    printf("Callback before back\n");
    MQAddCallbackReceiver(NULL, desc, ms, callback);
    printf("Callback after back\n");
    printf("test add callback receiver success\n");
    printf("---------------------------------------------------------------\n");
}

void* showMessage(void* args) {
    showMessageQueue();
    return NULL;
}

void* showReveiver(void* args) {
    showReceiverQueue();
    return NULL;
}

void test_callback(long arg0, long arg1, long arg2, long arg3, long arg4, \
        long arg5, long arg6, long arg7, long arg8, long arg9) {
    ContentPtr content;
    printf("########abc %d\n", arg0);
    if (arg0 != 0) {
        printf("args: %d\n", arg0);
        content = (ContentPtr)arg0;
        printf("the data %s, length %d\n", content->data, content->length);
    }
    printf("#######I am the callbakc fuction######\n");
    return NULL;
}

int mqTest(int log_level_mq, int log_level_timer, int log_level_memory) {
    int showMessageTid;
    int showReveiverTid;
    int i;
    printf("---------------------------Test--------------------------------\n");
    printf("Begin MQ TEST, LOG LEVLEL %d, %d, %d\n", log_level_mq, \
            log_level_timer, log_level_memory);
    init_memory_manage(log_level_memory);
    myTimerInit(log_level_timer);
    initMQ(log_level_mq);

    showMessageTid = mySetInterval(1000, showMessage, NULL);
    showReveiverTid = mySetInterval(1000, showReveiver, NULL);

    test_add_normal_message("aaa", "abcd", 5);
    test_add_normal_message("aaa", "abcd", 5);
    test_add_normal_message("aaa", "abcd", 5);
    test_add_imm_receiver("aaa");
    test_add_imm_receiver("aaa");
    test_add_imm_receiver("aaa");

    test_add_timeout_message("bbb", "bbbbb", 6, 3000);
    test_add_timeout_message("bbb", "bbbbb", 6, 3000);
    for (i = 0; i < 20; i ++) {
        test_add_timeout_message("bbb", "bbbbb", 6, 3000);
        mySleep(100);
    }
    mySleep(100);
    test_add_imm_receiver("bbb");
    test_add_suspend_receiver("ccc", 3000);
    mySleep(100);
    test_add_normal_message("ccc", "ccccc", 6);
    test_add_normal_message("ccc", "ccccc", 6);
    printf("&&&&&&&&&&&&&&&&&&&&&&&\n");

    test_add_callback_receiver("ddd", 4000, test_callback);
    mySleep(200);
    test_add_normal_message("ddd", "ddddd", 6);
    test_add_normal_message("ddd", "ddddd", 6);
    mySleep(200);

    test_add_callback_receiver("ddd", 4000, test_callback);
    mySleep(100);
    test_add_callback_receiver("ddd", 4000, test_callback);
    mySleep(100);
    test_add_callback_receiver("ddd", 4000, test_callback);
    mySleep(100);
    test_add_callback_receiver("ddd", 4000, test_callback);
    mySleep(200);
    test_add_callback_receiver("ddd", 4000, test_callback);

    mySleep(1000);
    myClearInterval(showMessageTid);
    myClearInterval(showReveiverTid);
    deinitMQ();
    myTimerDeinit();
    deinit_memory_manage();
    printf("###############################################################\n");
    return 0;
}
