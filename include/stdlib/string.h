#ifndef STRING_H
#define STRING_H

#include <stddef.h>

typedef char* string; 

unsigned int strlen(const char *str);
int strncmp(const char *str1, const char *str2, unsigned int n);
int strcmp(const char *str1, const char *str2);
void strcpy (char dest[], const char source[]);

char *strchr(const char *s, int c);
char *mystrncpy(char *dst, const char *src, size_t n);



#endif
