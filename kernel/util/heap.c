#include "../../include/util/heap.h"
#include "../../include/util/memory.h"

#include <stddef.h>

typedef struct Block {
    uint32_t size;
    struct Block *next;
    int free;
} Block;

#define BLOCK_SIZE sizeof(Block)

static Block *free_list = NULL;

void heap_init(void *heap_start, uint32_t heap_size) {
    free_list = (Block *)heap_start;
    free_list->size = heap_size - BLOCK_SIZE;
    free_list->next = NULL;
    free_list->free = 1;
}

void *malloc(uint32_t size) {
    Block *current = free_list;
    while (current) {
        if (current->free && current->size >= size) {
            current->free = 0;
            return (void *)(current + 1);
        }
        current = current->next;
    }
    return NULL; // Out of memory
}

void free(void *ptr) {
    if (!ptr) return;

    Block *block = (Block *)ptr - 1;
    block->free = 1;
}

