#ifndef __SHAREMEM_H__
#define __SHAREMEM_H__
#include <stdio.h>
#include <string.h> 
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h> 
#include <stdlib.h>
#include <endian.h>
#include <bits/wordsize.h>

#define SHARE_HASH_INDEX_NAX 5
#define PATHNAME "."
#define PROJ_ID 0x6666 

int createShm(const char *pathname,int size);   // 创建共享内存
int getShm(const char *pathname,int size);      // 获取共享内存
int *getShmIndex(int size);
int destoryShm(int shmid); // 销毁共享内存
#endif