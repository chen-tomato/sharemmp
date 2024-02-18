#include "sharemem.h"
static int commShm(const char *pathname, int size, int flags) // 创建共享内存
{
        key_t key = PROJ_ID; /*= ftok(pathname, PROJ_ID);
        printf("11111111111111");
        if (key < 0)
        {
                perror("ftok");
                return -1;
        }*/
        int shmid = shmget(key, size, flags);
        if (shmid < 0)
        {
                perror("shmget");
                return -2;
        }
        return shmid;
}
int createShm(const char *pathname, int size)
{
        return commShm(pathname, size, IPC_CREAT);
}
int getShm(const char *pathname, int size) // 获取共享内存
{
        return commShm(pathname, size, IPC_CREAT);
}
int destoryShm(int shmid) // 销毁共享内存
{
        if (shmctl(shmid, IPC_RMID, NULL) < 0)
        {
                perror("shmctl");
                return -3;
        }
        return 0;
}
/*char *addrtoarray(char *addr, int hashaddr)
{
        char value[8];

        if (__BYTE_ORDER == __LITTLE_ENDIAN)
        {
                for (int j = 0; j < 8; j++)
                {
                        value[j] = (hashaddr >> (8 * j)) & 0xff;
                }
                return value;
        }
       if (__BYTE_ORDER == __BIG_ENDIAN)
        {
                for (int j = bitfalg; j > 0; j++)
                {
                        value[j] = (hashaddr >> (8 * j)) & 0xff;
                }
                return value;
        }
}*/