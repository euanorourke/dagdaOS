#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

void *memcpy(void *dest, const void *src, uint32_t n);
void *memset(void *s, int c, uint32_t n);
int memcmp(const void *s1, const void *s2, uint32_t n);

#endif