#include "mq_test.h"

char* mq_test_make_data(char* tmp, int count) {
    char * buffer = (void*)my_malloc(13);
    int i = 0;
    for (i = 0; i < 12; i ++) {
        buffer[i] = tmp[i];
    }
    buffer[11] = count + 'a';
    buffer[12] = 0;
    return buffer;
}

void mq_test_case_1() {
    int count = 0;
    char* data;
    ContentPtrPtr contentPtr;
    
    printf("*********10 normal message and 12 immediately receiver**********\n");
    printf(">>>befor add normal message\n");
    showMessageQueue();
    showReceiverQueue();
    
    for (count = 0; count < 10; count ++) {
        data = mq_test_make_data("case_1_msg-a", count);
        MQAddNormalMessage(NULL, "mq_test_case_1", data, 12);
    }
    printf(">>>after add normal message\n");
    showMessageQueue();
    showReceiverQueue();

    for (count = 0; count < 12; count ++) {
        contentPtr = (ContentPtrPtr)my_malloc(sizeof(ContentPtr));
        *contentPtr = NULL;
        MQAddImmediatelyReceiver(NULL, "mq_test_case_1", contentPtr);
        if (*contentPtr != NULL) {
            printf("the data %s, length %d\n", (*contentPtr)->data, \
                    (*contentPtr)->length);
        }
    }

    printf(">>>after add 12 immediately receiver\n");
    showMessageQueue();
    showReceiverQueue();

    printf("***************************************************************\n\n");
}

void mq_test_timeout_callback(long arg0, long arg1, long arg2, long arg3, long arg4, \
        long arg5, long arg6, long arg7, long arg8, long arg9) {
    static int count = 0;
    ContentPtr content;
    if (arg0 != 0) {
        content = (ContentPtr)arg0;
        printf("I am the %d callback recever, my msg is: ", count);
        printf("data %s, length %d\n", content->data, content->length);
    }
}

void mq_test_case_2() {
    int count = 0;
    char* data;
    ContentPtrPtr contentPtr;
    
    printf("*********10 timeout message and 8 callback receiver*********\n");
    printf(">>>befor add timeout message\n");
    showMessageQueue();
    showReceiverQueue();
    
    for (count = 0; count < 10; count ++) {
        data = mq_test_make_data("case_2_msg-a", count);
        MQAddNormalMessage(NULL, "mq_test_case_2", data, 12);
    }
    printf(">>>after add timeout message\n");
    showMessageQueue();
    showReceiverQueue();

    for (count = 0; count < 8; count ++) {
        contentPtr = (ContentPtrPtr)my_malloc(sizeof(ContentPtr));
        *contentPtr = NULL;
        MQAddCallbackReceiver(NULL, "mq_test_case_2", 3000, \
                mq_test_timeout_callback);
    }

    printf(">>>after add 8 callback receiver\n");
    showMessageQueue();
    showReceiverQueue();

    mySleep(10000);
    printf("***************************************************************\n\n");
}

void mq_test_case_3() {
    int count = 0;
    char* data = mq_test_make_data("case_3_msg-a", 0);
    ContentPtrPtr contentPtr;
    
    printf("*********1 normal message and 2 immediately receiver**********\n");
    printf(">>>befor add normal message\n");
    showMessageQueue();
    showReceiverQueue();
    
    MQAddNormalMessage(NULL, "mq_test_case_3", data, 12);

    printf(">>>after add normal message\n");
    showMessageQueue();
    showReceiverQueue();

    for (count = 0; count < 2; count ++) {
        contentPtr = (ContentPtrPtr)my_malloc(sizeof(ContentPtr));
        *contentPtr = NULL;
        MQAddSuspendReceiver(NULL, "mq_test_case_3", 3000, contentPtr);
        if (*contentPtr != NULL) {
            printf("the data %s, length %d\n", (*contentPtr)->data, \
                    (*contentPtr)->length);
        }
    }

    printf(">>>after add 2 suspend receiver\n");
    showMessageQueue();
    showReceiverQueue();

    mySleep(5000);
    printf("***************************************************************\n\n");
}


int mqTest(int log_level_mq, int log_level_timer, int log_level_memory) {
    init_memory_manage(log_level_memory);
    myTimerInit(log_level_timer);
    initMQ(log_level_mq);

    mq_test_case_1();
    mq_test_case_2();
    mq_test_case_3();

    deinitMQ();
    myTimerDeinit();
    deinit_memory_manage();
    printf("###############################################################\n");
    return 0;
}
