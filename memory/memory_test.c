#include "memory_test.h"

void test_case_same_category() {
    int* ptr[15];
    int i;
    printf("\n#####request the same kind of memory#####\n");
    showStatus();
    
    printf("=========> after malloc\n");
    for (i = 0; i < 15; i ++) {
        ptr[i] = my_malloc(sizeof(int) * 10);
    }
    showStatus();

    printf("=========> after free\n");
    for (i = 0; i < 15; i ++) {
        my_free(ptr[i]);
    }
    showStatus();
    printf("########################################\n\n");
}

void test_case_different_category() {
    char *ptr_S1, *ptr_S2, *ptr_S4, *ptr_S8, *ptr_S256, *ptr_S1024;
    printf("\n#####request different kind of memory#####\n");
    showStatus();
    
    printf("=========> after malloc\n");
    ptr_S1 = (char*) my_malloc(1);
    ptr_S2 = (char*) my_malloc(2);
    ptr_S4 = (char*) my_malloc(4);
    ptr_S8 = (char*) my_malloc(7);
    ptr_S256 = (char*) my_malloc(188);
    ptr_S1024 = (char*) my_malloc(1000);
    showStatus();

    printf("========> after free\n");
    my_free(ptr_S1);
    my_free(ptr_S2);
    my_free(ptr_S4);
    my_free(ptr_S8);
    my_free(ptr_S256);
    my_free(ptr_S1024);
    showStatus();

    printf("########################################\n\n");
}

void test_case_alloc_error() {
    int* ptr;
    printf("\n#####alloc error#####\n");
    showStatus();
    printf("========> after alloc\n");
    ptr = (int*) my_malloc(0);
    showStatus();
    printf("########################################\n\n");
}

void test_case_free_error() {
    int* ptr;
    printf("\n#####free memory error#####\n");
    showStatus();
    
    printf("=======> after malloc\n");
    ptr = (int*) my_malloc(sizeof(int) * 10);
    showStatus();

    printf("======> after free");
    my_free(ptr + 1);
    showStatus();

    printf("########################################\n\n");
}

void task1(long arg0, long agr1, long arg2, long arg3, long arg4, long arg5, \
        long arg6, long arg7, long arg8, long arg9) {
    /* add test_case*/
    test_case_same_category();
    test_case_different_category();
    test_case_alloc_error();
    test_case_free_error();
}

void task2(long arg0, long agr1, long arg2, long arg3, long arg4, long arg5, \
        long arg6, long arg7, long arg8, long arg9) {
    /* add test_case*/
    test_case_same_category();
    test_case_different_category();
    test_case_alloc_error();
    test_case_free_error();
}

int memoryTest(level) {
    init_memory_manage(level);

    /* add test_case*/
    test_case_same_category();
    test_case_different_category();
    test_case_alloc_error();
    test_case_free_error();

    /* deinitialization*/
    taskDelay(3);
    deinit_memory_manage();
    return 0;
}


int memoryMultTaskTest(level) {
    init_memory_manage(level);

    createTask(task1, NULL);
    createTask(task2, NULL);
    /* deinitialization*/
    taskDelay(3);
    deinit_memory_manage();
    return 0;
}
