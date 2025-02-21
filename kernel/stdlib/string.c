#include "../include/stdlib/string.h"

<<<<<<< HEAD
=======
void memset(char *str, char val, unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
        str[i] = val;
    }
}
>>>>>>> 6eea6ea (Initial commit)

unsigned int strlen(const char *str) {
    unsigned int len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}
<<<<<<< HEAD
int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}
int strncmp(const char *str1, const char *str2, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0') {
            return (unsigned char)str1[i] - (unsigned char)str2[i];
        }
    }
    return 0;
}
=======
>>>>>>> 6eea6ea (Initial commit)
