#ifndef __MEMPOOL
#define __MEMPOOL

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
struct index_head
{
	intptr_t  offset;
};
struct block_head
{
	intptr_t offset;
};

typedef struct
{
	/*zhe pool buffo size*/
        uint32_t capacity;
        //uint32_t index_capacity;
        //uint32_t data_capacity;
        /*zhe pool buffo address*/
	uint8_t *addr;
	int shmid;

	uint32_t headerblockSize;
	uint32_t headerblockCount;
	struct index_head *index_current;
	uint32_t datablockSize;
	uint32_t datablockCount;
	struct block_head *data_current;
        struct block_head *dataend;
	
} mempool;

void share_mempool_init(mempool *pool, uint32_t indexblockSize, uint32_t indexblockCount, uint32_t datablockSize, uint32_t datablockCount);
void get_share_mempool(mempool* pool, uint32_t indexblockSize, uint32_t indexblockCount, uint32_t datablockSize, uint32_t datablockCount);
void *share_mempool_alloc(mempool *pool);
void share_mempool_free(mempool *pool, void *ptr);
void share_mempool_detach(mempool *pool);

#endif
