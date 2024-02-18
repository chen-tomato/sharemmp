#include "hash.h"

unsigned int hash_init(unsigned int buckets, uint128_t key)
{
	return (unsigned int)(key % buckets);
}

hash_t **hash_get_bucket(hash_t **hash, uint128_t key)
{
	unsigned int bucket = hash_init(HASH_KEY, key);
	if (bucket >= HASH_KEY)
	{
		fprintf(stderr, "bad buckets lookup\n");
		exit(EXIT_FAILURE);
        }

        return &hash[bucket];
}

intptr_t  *hash_get_node_by_key(mempool *mem_pool,hash_t **hash, uint128_t key)
{
	hash_t **bucket = hash_get_bucket(hash, key);
        hash_t* bucket_current=(hash_t*)bucket;
        hash_node_t* data_node=NULL;
        if(bucket_current->offset == 0) {//当前桶节点链表无数据
                printf("当前桶节点链表无数据,addr=%p\n",bucket_current);
                return &bucket_current->offset;
        }
        data_node=(hash_node_t*)(bucket_current->offset + mem_pool->addr);
        printf("000data_node->name = %s\n", data_node->name);
        if(data_node->md5_value == key) {//第一个节点为所查找的数据
                printf("第一个节点为所查找的数据,addr=%p\n",data_node);
                return &bucket_current->offset;
        }

        while(data_node->next_offset != 0)
	{
                printf("data_node->next_offset = %lx\n", data_node->next_offset);
                intptr_t *offset = &data_node->next_offset;
                data_node=(hash_node_t*)(data_node->next_offset + mem_pool->addr);
                if(data_node->md5_value == key) {
                       return offset;
                }
                printf("111data_node addr = %p\n", data_node);
                printf("111data_node->name = %s\n",data_node->name);
                printf("111data_node->next_offset = %lx\n", data_node->next_offset);
        }

	return &data_node->next_offset;
}

hash_t *hash_index_alloc(mempool *mem_pool)
{
	hash_t *h = (hash_t *)mem_pool->index_current;
	return h;
}

void hash_add_entry(mempool *mem_pool,hash_t **hash,hash_node_t *data)
{
        intptr_t* offset=hash_get_node_by_key(mem_pool, hash, data->md5_value);
        if(offset == NULL) {
                printf("添加失败\n");
                return;
        }
        if(*offset != 0)
        {
		fprintf(stderr, "key重复\n");
		return;
        }
        *offset=(intptr_t)((uint8_t*)data - mem_pool->addr);
        printf("end *offset=%lx\n",*offset);
        return;
}

/*void hash_free_entry(mempool *mem_pool,hash_t *hash, uint128_t key)
{
	intptr_t* offset = hash_get_node_by_key(mem_pool,hash, key);
	if(*offset !=0)
        {
		fprintf(stderr, "key重复\n");
		return;
	}
	
		if (node->prev)
			node->prev->next = node->next;
		else
		{
			hash_node_t **p = hash_get_bucket(hash, key);
			(*p)->next = node->next;
		}
		if (node->next)
			node->next->prev = node->prev;
		share_mempool_free(mem_pool,node);
}*/