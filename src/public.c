#include "public.h"

uint8_t charToNibble(char c) 
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    return 0;
}
char nibbleToChar(uint8_t nibble) 
{
    if (nibble >= 0 && nibble <= 9) {
        return '0' + nibble;
    } else if (nibble >= 10 && nibble <= 15) {
        return 'a' + nibble - 10;
    }
    return '0';
}
//printf("Value: %016llx%016llx\n", (long long)(value >> 64), (long long)value);
uint128_t md5ToUint128(const uint8_t* md5) 
{
    uint128_t result = 0;
    for (int i = 0; i < 32; i++) {
        result <<= 4;
        result |= charToNibble(md5[i]);
    }
    return result;
}

void uint128ToMd5(uint128_t value, uint8_t* md5) 
{
    /*for (int i = 31; i >= 0; i--) {
        uint8_t nibble = (value >> (i * 4)) & 0xF;
        md5[31 - i] = nibbleToChar(nibble);
    }*/
    //md5[32] = '\0';
    sprintf((char *)md5,"%016llx%016llx",(long long unsigned int)(value >> 64), (long long unsigned int)value);
}