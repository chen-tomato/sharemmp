#ifndef _PUBLIC_H_
#define _PUBLIC_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ERR_EXIT(m)         \
	do                      \
	{                       \
		perror(m);          \
		exit(EXIT_FAILURE); \
	} while (0)


#define MD5_DIGEST_LENGTH 16
typedef unsigned __int128 uint128_t;

#define SHARE_MEM_BLOCKCOUNT_MAX 1000000
#define FILE_LINE_CHAR_MAX 100

uint8_t charToNibble(char c);
char nibbleToChar(uint8_t nibble);
uint128_t md5ToUint128(const uint8_t *md5);
void uint128ToMd5(uint128_t value, uint8_t *md5);
#endif