#include "../include/stdlib/string.h"

void memset(char *str, char val, unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
        str[i] = val;
    }
}

unsigned int strlen(const char *str) {
    unsigned int len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}
