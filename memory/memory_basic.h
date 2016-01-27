#ifndef MEMORY_BASIC
#define MEMORY_BASIC
#include "memory_log.h"
#include "../common/common.h"

/* category num equels the num of memo_category minus 1*/
#define CATEGORY_NUM 12     

/* every time alloc new chunk the default size of blocks num*/
#define INC_BLOCK_NUM 10

/* the address type*/
typedef void* addr_type;

/* the memory type, and the correspond block size equals "2^val(category)"*/
typedef enum {
    NIL = -1,
    CATE1, CATE2, CATE4,
    CATE8, CATE16, CATE32, CATE64,
    CATE128, CATE256, CATE512,
    CATE1024, CATE2048
} memo_category;

/* the name correponding to the memo_category*/
static char* memo_category_str[] = {"CATE1", "CATE2", "CATE4", "CATE8", \
    "CATE16", "CATE32", "CATE64", "CATE128", "CATE256", "CATE512", "CATE1024", \
        "CATE2048"};

/* the balance search tree node*/
typedef struct bst_node {
    addr_type start;        /* the start of the address range*/
    addr_type end;          /* the end of the address range*/
    memo_category category; /* the category of this node*/
    struct bst_node* left;
    struct bst_node* right;
}bst_node, * bst_node_ptr;

typedef struct chunk {
    char* addr; /* the address of this chunk's memory*/
    int size;   /* the size of this memory chunk*/
    struct chunk* next;
}chunk, * chunk_ptr;

typedef struct block {
    void* ptr;
    unsigned char state;
    struct block* next;
}block,* block_ptr;

typedef struct memory_info {
    chunk_ptr chunk_list;

    /* the total chunk of the system*/
    int chunk_total;   

    /* the chunk num of speciafy category*/
    int chunk_category[CATEGORY_NUM];   

    /* the balance search tree*/
    bst_node_ptr category_map_BST;  
    
    /* the free block chain of specify category*/
    block_ptr free_block_chains[CATEGORY_NUM]; 

    /* the total block num of the system*/
    int free_block_total;

    /* the free block num of specify category*/
    int free_block_num[CATEGORY_NUM];

    /* the total block of the system*/
    int total_blocks;

    /* the total block of specify category*/
    int total_category_blocks[CATEGORY_NUM];
}memory_info, * memory_info_ptr;

extern MySemaphorePtr g_memory_global_sem;
extern memory_info_ptr g_memory_info;
#endif
