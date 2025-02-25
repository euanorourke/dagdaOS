#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#define KEYBOARD_BUFFER_SIZE 256

void keyboard_handler(struct regs *r);
char keyboard_read_char();
void keyboard_install();
#endif