#ifndef BASIC_STRUCT
#define BASIC_STRUCT

#include "memory_basic.h"

#endif

#include "bst.h"
#include "memory_log.h"

#include <stdlib.h>

/**
 * according to the block category get the block size
 *
 * parms:
 *  category: the category
 * return:
 *  the size of this kind of block size
 */
int getBlockSizeFromCategory(memo_category category);

/**
 * according to the given size get the correspond block categroy
 *
 * parms:
 *  size: the given size
 * return:
 *  the block category of the size
 */
memo_category getCategoryFromSize(int size);

/**
 * append a new chunk to the chunk chain
 *
 * parms:
 *  info: the memory info struct
 *  addr: the start address of the chun
 *  size: the size of the chunk
 *  category: the category of the chunk
 * return:
 *  none
 *
 */
void appendNewChunkToChunkChain(memory_info_ptr info, char* addr, int size, \
        memo_category category);

/**
 * seperate the new chunk to blocks and add them to the free block chain
 *
 * parms:
 *  info: the memory info struct
 *  addr: the start address of the chunk
 *  num: the number of the block
 *  category: the category of the chunk
 * return:
 *  none
 */
void appendNewChunkToFreeBlockChain(memory_info_ptr info, char* addr, int num, \
        memo_category category);

/**
 * add the chunk to the bst for later check address category
 *
 * parms:
 *  info: the memory info struct
 *  addr: the start address of the chunk
 *  size: the size of the chunck
 *  category: the category of the chunk
 * return:
 *  none
 */
void appendNewChunkToBST(memory_info_ptr info, char* addr, int size, \
        memo_category category);

/** 
 * request more chunk for "category"
 *
 * parms:
 *  info: the memory info struct
 *  category: the category of the memory
 *  num: the num of this category need to add
 * return:
 *  0: no error
 *  others: error
 */
int addChunk(memory_info_ptr info, memo_category category, int num);

/**
 * get the correspond size memory block
 *
 * parms:
 *  info: the memory info struct
 *  size: the request memory size
 * return:
 *  failed: NULL
 *  successed: the pointer of the memory blockj
 */
void* getMemory(memory_info_ptr info, int size);

/**
 * free the memory of the pointer ptr
 *
 * parms:
 *  info: the memory info struct
 *  ptr: the pointer of the memory block
 * return:
 *  0: successed
 *  1: failed
 */
int freeMemory(memory_info_ptr info, void* ptr);

