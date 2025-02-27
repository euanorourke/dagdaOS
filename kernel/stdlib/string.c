#include "../include/stdlib/string.h"

#include <stddef.h>

unsigned int strlen(const char *str) {
    unsigned int len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}
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

void strcpy (char dest[], const char source[]) {
    int i = 0;
    while (1) {
        dest[i] = source[i];
        if (dest[i] == '\0') {
            break;
        }
        i++;
    } 
}

char *strchr(const char *s, int c) {
    while (*s != (char) c) {
        if (!*s++) {
            return NULL;
        }
    }
    return (char *)s;
}

char *strncpy(char *dst, const char *src, size_t n)
{
   int i;
   char *temp;
   temp = dst;  
   for (i = 0; i < n; i++)
      *dst++ = *src++;
   return temp;
}