#include "mempool.h"
#include "sharemem.h"

void share_mempool_init(mempool* pool, uint32_t indexblockSize, uint32_t indexblockCount, uint32_t datablockSize, uint32_t datablockCount)
{
        assert(indexblockSize >= 4);
        assert(indexblockCount > 1);
        assert(datablockSize >= 4);
        assert(datablockCount > 1);

        pool->headerblockSize=indexblockSize;
        pool->headerblockCount=indexblockCount;

        pool->datablockSize=datablockSize;
        pool->datablockCount=datablockCount;

        //pool->data_capacity=datablockSize * datablockCount;
        //pool->index_capacity=indexblockSize * indexblockCount;

        pool->capacity=(datablockSize * datablockCount) + (indexblockSize * indexblockCount);
        pool->shmid=createShm(PATHNAME, pool->capacity);
        pool->addr=(uint8_t*)shmat(pool->shmid, NULL, 0);
        memset(pool->addr, 0, pool->capacity);
        pool->index_current=(struct index_head*)pool->addr;                                       // 指向索引段
        pool->data_current=(struct block_head*)(pool->addr + (indexblockSize * indexblockCount)); // 指向数据段
        pool->dataend=pool->data_current + (datablockSize * datablockCount);
        pool->index_current->offset=0;
        pool->data_current->offset=0;
}
void get_share_mempool(mempool* pool, uint32_t indexblockSize, uint32_t indexblockCount, uint32_t datablockSize, uint32_t datablockCount) {
        assert(indexblockSize >= 4);
        assert(indexblockCount > 1);
        assert(datablockSize >= 4);
        assert(datablockCount > 1);
        pool->headerblockSize=indexblockSize;
        pool->headerblockCount=indexblockCount;

        pool->datablockSize=datablockSize;
        pool->datablockCount=datablockCount;
        pool->capacity=(datablockSize * datablockCount) + (indexblockSize * indexblockCount);
        pool->shmid=createShm(PATHNAME, pool->capacity);
        pool->addr=(uint8_t*)shmat(pool->shmid, NULL, 0);
        pool->index_current=(struct index_head*)pool->addr;                                       // 指向索引段
        pool->data_current=(struct block_head*)(pool->addr + (indexblockSize * indexblockCount)); // 指向数据段
        pool->dataend=pool->data_current + (datablockSize * datablockCount);

}
void* share_mempool_alloc(mempool* pool)
{
        if((pool->dataend - pool->data_current) <= 0) {
                return NULL;
        }
        struct block_head* p=pool->data_current;
        pool->datablockCount--;
        p->offset=(uint8_t*)pool->data_current - pool->addr;
        pool->data_current=(struct block_head*)((uint8_t*)pool->data_current + pool->datablockSize);

        return (void*)p;
}

void share_mempool_free(mempool* pool, void* ptr)
{
        assert(ptr != NULL);

        pool->datablockCount++;
        ((struct block_head*)ptr)->offset=0;
        pool->data_current=ptr;
}

void share_mempool_detach(mempool* pool)
{
        shmdt(pool->addr); // 取挂接
        destoryShm(pool->shmid);
        pool->datablockSize=0;
        pool->datablockCount=0;
        pool->data_current=NULL;

        pool->capacity=0;
        pool->addr=NULL;
}
