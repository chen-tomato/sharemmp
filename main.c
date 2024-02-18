#include "src/hash.h"
#define FILENAME "/root/project/sharemmp/md5file.txt"

int init(char* filename, mempool* p,hash_t** sharemem_indexhead) {
        char line[FILE_LINE_CHAR_MAX]={ 0 };
        char* token=NULL;
        char* md5value=NULL, *md5name=NULL;
        int maxnum=1000000, num=0;
        int count=0;
        if(filename == NULL) {
                return -1;
        }
        FILE * file=fopen(filename, "r"); // 以只读模式打开文件
        if(file == NULL) {
                perror("Error opening file");
                return -1;
        }

        while(fgets(line, FILE_LINE_CHAR_MAX, file)) {
                num++;
                if(num >= maxnum) {
                        goto out;
                }
                line[strcspn(line, "\n")]='\0';
                token=strtok(line, " ");
                while(token != NULL && count < 2) {
                        if(count == 0) {
                                md5name=token;
                        } else if(count == 1) {
                                md5value = token;
                        }
                        token=strtok(NULL, " ");
                        count++;
                }
                count=0;
                hash_node_t* data=share_mempool_alloc(p);
                printf("data addr = %p\n",data);
                data->md5_value=md5ToUint128((uint8_t*)md5value);
                strcpy(data->name, md5name);
                hash_add_entry(p, sharemem_indexhead, data);
        }
out:
        fclose(file); // 关闭文件
        return 0;
}
int main(void)
{
        mempool mem_pool;
        mempool* p=&mem_pool;
        //初始化内存池
        share_mempool_init(&mem_pool, sizeof(hash_t), SHARE_MEM_BLOCKCOUNT_MAX, sizeof(hash_node_t), SHARE_MEM_BLOCKCOUNT_MAX);//补充\0
        // 获取 索引
        hash_t** sharemem_indexhead=(hash_t**)hash_index_alloc(&mem_pool);
        // 填充数据
        if(init(FILENAME, p, sharemem_indexhead) != 0) {
                printf("init is faild\n");
                return -1;
        }
        printf("初始化完成\n");
        while(1) {
                sleep(3600);
        }

        // 释放内存
        share_mempool_free(&mem_pool, mem_pool.addr);

       // 销毁内存池
        share_mempool_detach(&mem_pool);

        return 0;
}
