#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>

void heap_init(void *heap_start, uint32_t heap_size);
void *malloc(uint32_t size);
void free(void *ptr);

#endif
