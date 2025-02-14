#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#define KEYBOARD_BUFFER_SIZE 256

char scan_code_to_char(uint8_t scan_code);
void poll_keyboard();
char keyboard_read_char();

#endif