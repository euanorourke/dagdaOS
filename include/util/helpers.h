#ifndef HELPERS_H
#define HELPERS_H
#include <stdint.h>

unsigned long long __udivdi3(unsigned long long n, unsigned long long d);
unsigned long long __umoddi3(unsigned long long n, unsigned long long d);
unsigned long long __udivmoddi4(unsigned long long n, unsigned long long d, unsigned long long *rem);
void sleep(uint8_t times);

#define low_16(address) (uint16_t)((address) & 0xFFFF)            
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

#endif