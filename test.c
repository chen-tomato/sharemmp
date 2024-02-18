#include "src/hash.h"

int main(void)
{
        mempool mem_pool;
        char input[100]={ 0 };

        //初始化内存池
        get_share_mempool(&mem_pool, sizeof(hash_t), SHARE_MEM_BLOCKCOUNT_MAX, sizeof(hash_node_t), SHARE_MEM_BLOCKCOUNT_MAX);
        // 获取 索引
        hash_t** sharemem_indexhead=(hash_t**)hash_index_alloc(&mem_pool);

        while(1) {
                printf("请输入md5值: ");
                fgets(input, sizeof(input), stdin);
                intptr_t* offset=hash_get_node_by_key(&mem_pool, sharemem_indexhead, md5ToUint128((uint8_t *)input));
                if(offset && *offset != 0) {
                        uint8_t md5str[32];
                        hash_node_t* result=(hash_node_t*)(*offset + mem_pool.addr);
                        uint128ToMd5(result->md5_value, md5str);
                        printf("name = %s ,md5string = %s\n", result->name, md5str);
                } else {
                        printf("not found\n");
                }
                memset(input,0,100);
        }

        return 0;
}
