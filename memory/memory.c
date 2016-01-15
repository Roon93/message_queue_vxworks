#include "memory.h"

int getBlockSizeFromCategory(memo_category category) {
    int size = 1;
    while (category > 0) {
        size <<= 2;
        category --;
    }
    memory_debug("getBlockSizeFromCategory: category %d, size %d", category, size);
    return size;
}

memo_category getCategoryFromSize(int size) {
    int count = 0;
    size = size - 1;
    while (size != 0) {
        count ++;
        size >>= 1;
    }
    return (memo_category)count;
}

void appendNewChunkToChunkChain(memory_info_ptr info, char* addr, int size, \
        memo_category category) {
    chunk_ptr new_chunk = (chunk_ptr)malloc(sizeof(chunk));
    new_chunk->addr = addr;
    new_chunk->size = size;
    new_chunk->next = info->chunk_list;
    info->chunk_list = new_chunk;
    info->chunk_total ++;
    info->chunk_category[category] ++;
    memory_debug("appendNewChunkToChunkChain: category %d, size %d", category, size);
}

void appendNewChunkToFreeBlockChain(memory_info_ptr info, char* addr, int num, \
        memo_category category) {
    int block_size = getBlockSizeFromCategory(category);
    block_ptr new_block;
    info->total_blocks += num;
    info->total_category_blocks[category] += num;
    info->free_block_total += num;
    info->free_block_num[category] += num;
    memory_debug("appendNewChunkToFreeBlockChain: category %d, num %d", category, num);
    while (num > 0) {
        new_block = (block_ptr)malloc(sizeof(block));
        new_block->ptr = (void *)addr;
        /* append the new block to the correspond free block chain*/
        new_block->next = info->free_block_chains[category];
        info->free_block_chains[category] = new_block;
        addr += block_size;
        num --;
    }
}

void appendNewChunkToBST(memory_info_ptr info, char* addr, int size, \
        memo_category category) {
    bst_node_ptr new_node = (bst_node_ptr)malloc(sizeof(bst_node));
    new_node->start = (addr_type)addr;
    new_node->end = (addr_type)(addr + size);
    new_node->category = category;
    new_node->left = NULL;
    new_node->right = NULL;
    addNodeToBST(&info->category_map_BST, new_node);
    memory_debug("appendNewChunkToBST: category %d, size %d", category, size);
}

int addChunk(memory_info_ptr info, memo_category category, int num) {
    int block_size = getBlockSizeFromCategory(category);
    int size = block_size * num;
    char* tmp_ptr = (char *)malloc(size);

    memory_loginfo("addChunk: category %d, num %d, size %d", category, num, size);

    if (tmp_ptr == NULL) {
        memory_error("addChunk: request memory failed category %d, size %d", \
                category, size);
        return 1;
    }
    /* append the memory to the chunk list*/
    appendNewChunkToChunkChain(info, tmp_ptr, size, category);

    /* append the memory to the free block chain*/
    appendNewChunkToFreeBlockChain(info, tmp_ptr, num, category);

    /* append the chunk of memory to the category map, using a bst to manage it*/
    appendNewChunkToBST(info, tmp_ptr, size, category);
    return 0;
}

void* getMemory(memory_info_ptr info, int size) {
    void* ptr;
    block_ptr tmp_block;
    memo_category category;

    if (size <= 0) 
        return NULL;

    memory_debug("getMemory: category %d, size %d", category, size);
    category = getCategoryFromSize(size);

    /* make sure there are free blocks*/
    if (info->free_block_num[category] == 0) {
        memory_warning("getMemory: run out of category %d free block", category);

        if (addChunk(info, category, INC_BLOCK_NUM) != 0) {
            memory_loginfo("getMemory failed");
            return NULL;
        }
    }

    /* get the memory block and free the block in the free block chain*/
    tmp_block = info->free_block_chains[category];
    ptr = tmp_block->ptr;
    info->free_block_chains[category] = tmp_block->next;
    info->free_block_total --;
    info->free_block_num[category] --;
    free(tmp_block);

    return ptr;
}

int freeMemory(memory_info_ptr info, void* ptr) {
    addr_type base;
    memo_category category = findCategoryInBST(info->category_map_BST, ptr, \
            &base);
    block_ptr new_block = (block_ptr)malloc(sizeof(block));
    int block_size = getBlockSizeFromCategory(category);

    memory_debug("freeMemory: category %d", category);

    if ((int)(ptr - base) % block_size != 0) {
        memory_error("freeMemory: free error addr %lld is not aglined", ptr);
        return 1;
    }

    new_block->ptr = ptr;
    /* append the free block the to correspond free block chain*/
    new_block->next = info->free_block_chains[category];
    info->free_block_chains[category] = new_block;
    memory_debug("total free block num: %d", info->free_block_total);
    info->free_block_total ++;
    memory_debug("total free block num: %d", info->free_block_total);
    info->free_block_num[category] ++;
    return 0;
}
