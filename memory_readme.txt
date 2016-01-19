嵌入式 memory

memory
实现借鉴slab allocation，系统护维几个块大小不一样的空闲内存块链，分配的基本原则是：找到大于或等于请求内存大小的最小的块大小，在对应size的空闲块链上分配出一个块，用作分配的内存。释放内存的基本原则是：释放使用的内存块到对应size的空闲块链上。基于以上原则，如下描述系统的架构：
block: 系统内存分配单元，每个block都有对应的size，请求到来时，每次都是分配出相应size的block
chunk: 一大块内存，可以分成若干个block，每个chunk都是从操作系统中请求到的内存
chunk链(chuck_chain)：用于记录已经从系统中分到的所有chunk，主要用于记录这些块，用于安全释放已经分配的内存，防止内存泄露
空闲block链(free_block_chain)：用于记录没有被分配出去的block，系统可以存在多个链，每个链中都只能存在唯一size的block
类分映射二叉搜索树(category_map_BST)：此二叉树用于记录已经从系统中分配到的chunk，并根于chunk块地址范围构建的二叉树，每个节点都记录了相应的chunk地址范围和chunk的size类别， 主要用于地址映射到chunk内别

主要文件及其函数说明：
memory_basic.h：本文件主要为memory模块所需的相关数据结构。

memory_manage.h memory_manage.c：本文件为memory模块对外的相关api接口等。
int init_memory_manage():
初始化内存分配相关的数据结构，在使用其它api时必需首先调用此函数进行准备。
void deinit_memory_manage():
释放本模块生成的相关据结构，占用的内存等。
void* my_malloc(int size):
申请内存，size参数指明需要分配的内存大小。
int my_free(void* ptr):
释放内存， ptr是要释放的内存的指针。
void showStatus():
显示系统内存分配使用情况，主要数据有：总申请的chunk的数量、不同类别的chunk数量、总的空闲block、不同类别的空闲block数量、不同类别总的block数量、总的block数量。

memory.h memory.c：本文件主要包括主要的相关操作。
int getBlockSizeFromCategory(memo_category category):
由给出的类别返回相应的类别每个block的大小。
memo_category getCategoryFromSize(int size):
由给出的内存块大小，返回相应的block类别。
void appendNewChunkToChunkChain(memory_info_ptr info, char* addr, int size, memo_category category):
向记录chunk的链表上添加新申请有的chunk。
void appendNewChunkToFreeBlockChain(memory_info_ptr info, char* addr, int num, memo_category category):
在新申请了chunk后，把chunk分割成block并添加到对应类别的空闲链表上。
void appendNewChunkToBST(memory_info_ptr info, char* addr, int size, memo_category category):
在新申请了chunk后，把chunk的相关信息添加到二叉搜索树上。
int addChunk(memory_info_ptr info, memo_category category, int num):
申请分配新的chunk，并完成其它的操作。
void* getMemory(memory_info_ptr info, int size):
依据给出的大小等信息，返回申请的内存块指针。
int freeMemory(memory_info_ptr info, void* ptr):
释放给定的内存。

memory_log.h memory_log.c：主要提供标准输出提示。
void set_memory_log_level(int level):
设置输出级别，0:不输出，1:log info信息，2: warning级别，3:debug级别
void memory_loginfo(char* fmt, …):
输入loginfo级别信息。
void memory_warning(char* fmt, …):
输出warning级别信息。
void memory_debug(char* fmt, …):
输出debug级别信息。
void memory_error(char* fmt, …):
输出error信息。

bst.h bst.c: 本文件主要提供二叉树的相关操作。
void addNodeToBST(bst_node_ptr* root, bst_node_ptr node):
向二叉树中添加节点。
memo_category findCategoryInBST(bst_node_ptr root, addr_type addr, addr_type* base):
根据给出的指针，在二叉树中找出相应的类别。
void destroyBST(bst_node_ptr root):
释放二叉树。

memory_test.h memory_test.c: 本文件主要测试memory模块的相关功能。
test_case_same_category():
分配同一类别的block。
test_case_different_category():
分配不同类别的block。
test_case_alloc_error():
分配错误测试。
test_case_free_error():
释放错误测试。

相关操作：
初始化：
主要初始g_memory_info这一全局变量，此变量中存储chunk链信息、空闲block链信息、二叉搜索树树根、以及其它的统计信息。
分配内存：
首先根据申请的内存块大小，取得要返回内存块大小类别，并检查此内存空闲block链上是否还有空闲块，如果有，取出一个并返回对应的block地址，如果没有，系统新分配一个chunk，完成相关操作后，返回一个此类别的block地址。
释放内存：
首先根据给出的地址，通过二叉搜索树查找到到地址对应的类别，把此地址上的块加入此类别空闲block链上。
系统释放：
释放空闲block的相关信息，释放申请的chunk的相关信息，释放二叉搜索树，释放相关全局数据结构。
