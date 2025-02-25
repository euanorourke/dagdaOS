#include "../../include/util/memory.h"

void *memcpy(void *dest, const void *src, uint32_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    for (uint32_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

void *memset(void *s, int c, uint32_t n) {
    char *p = (char *)s;
    for (uint32_t i = 0; i < n; i++) {
        p[i] = (char)c;
    }
    return s;
}

int memcmp(const void *s1, const void *s2, uint32_t n) {
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;
    for (uint32_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return (p1[i] < p2[i]) ? -1 : 1;
        }
    }
    return 0;
}
