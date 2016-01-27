#include "memory_test.h"

void memory_test_case_1() {
    int* ptr[10];
    int i;
    printf("\n******Test Case 1*******\n");
    printf("-----before alloc------\n");
    showStatus();
    for (i = 0; i < 10; i ++) {
        ptr[i] = my_malloc(sizeof(int) * 10);
    }
    printf("-----after alloc-------\n");
    showStatus();

    for (i = 0; i < 10; i ++) {
        my_free(ptr[i]);
    }
    printf("------after free------\n");
    showStatus();
    printf("***************************\n\n");
}

void memory_test_case_2() {
    char *ptr_CATE1, *ptr_CATE2, *ptr_CATE4, *ptr_CATE8, *ptr_CATE256, \
        *ptr_CATE1024, *ptr_2048;
    printf("\n********Test Case 2********\n");
    printf("----------before alloc-------\n");
    showStatus();

    ptr_CATE1 = (char*) my_malloc(1);
    ptr_CATE2 = (char*) my_malloc(2);
    ptr_CATE4 = (char*) my_malloc(4);
    ptr_CATE8 = (char*) my_malloc(7);
    ptr_CATE256 = (char*) my_malloc(188);
    ptr_CATE1024 = (char*) my_malloc(1000);

    printf("-------after malloc---------\n");
    showStatus();

    my_free(ptr_CATE1);
    my_free(ptr_CATE2);
    my_free(ptr_CATE4);
    my_free(ptr_CATE8);
    my_free(ptr_CATE256);
    my_free(ptr_CATE1024);
    printf("--------after free----------\n");
    showStatus();

    printf("******************************\n\n");
}

void memory_test_case_3() {
    int* ptr;
    printf("\n*********alloc error**********\n");
    printf("---------before alloc---------\n");
    showStatus();

    ptr = (int*) my_malloc(0);

    printf("after alloc\n");
    showStatus();
    printf("******************************\n\n");
}

void memory_test_case_4() {
    int* ptr;
    printf("\n********free memory error********\n");
    printf("---------before free-----------\n");
    showStatus();
    
    ptr = (int*) my_malloc(sizeof(int) * 10);
    showStatus();

    my_free(ptr + 1);
    showStatus();

    printf("*******************************\n\n");
}

int memoryTest(int level) {
    init_memory_manage(level);

    /* add memory_test_case*/
    memory_test_case_1();
    memory_test_case_2();
    memory_test_case_3();
    memory_test_case_4();

    /* deinitialization*/
    deinit_memory_manage();
    return 0;
}
