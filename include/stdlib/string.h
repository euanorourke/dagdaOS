#ifndef STRING_H
#define STRING_H


typedef char* string; 

unsigned int strlen(const char *str);
int strncmp(const char *str1, const char *str2, unsigned int n);
int strcmp(const char *str1, const char *str2);
#endif
