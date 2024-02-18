#ifndef _HASH_H_
#define _HASH_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/sendfile.h>
#include <string.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <ctype.h>
#include <linux/capability.h>
#include <netdb.h>
#include <sys/types.h>
#include <pwd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/stat.h>
#include <signal.h>
#include <dirent.h>
#include <sys/time.h>
#include <shadow.h>
#include <crypt.h>
#include <assert.h>
#include "public.h"
#include "mempool.h"
#define HASH_KEY SHARE_MEM_BLOCKCOUNT_MAX

typedef struct share_mem_md5block
{
        uint128_t md5_value;
        char name[40];
        intptr_t next_offset;

} hash_node_t;

typedef struct share_mem_index
{
    intptr_t offset;
} hash_t;

//typedef unsigned int (*hashfunc_t)(size_t, void *);
//unsigned int hash_init(unsigned int buckets, uint128_t key);
hash_t *hash_index_alloc(mempool *mem_pool);
//hash_node_t **hash_get_bucket(hash_t *hash, uint128_t key);
intptr_t *hash_get_node_by_key(mempool *mem_pool,hash_t **hash, uint128_t key);
void hash_add_entry(mempool *mem_pool,hash_t **hash,hash_node_t *data);
//void hash_free_entry(mempool *mem_pool, hash_t *hash, uint128_t key);

#endif
