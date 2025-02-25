#include "../include/stdlib/strncmp.h"

int strncmp(const char *str1, const char *str2, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0') {
            return (unsigned char)str1[i] - (unsigned char)str2[i];
        }
    }
    return 0;
}