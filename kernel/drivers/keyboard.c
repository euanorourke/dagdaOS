#include "../../include/util/io.h"
#include "../include/drivers/vga.h"
#include "../include/drivers/keyboard.h"

#define KEYBOARD_DATA_PORT 0x60

static char keyboard_buffer[KEYBOARD_BUFFER_SIZE];
static unsigned int buffer_head = 0;
static unsigned int buffer_tail = 0;
static int buffer_size = 0;
static int shift = 0; // Track Shift Key State

// Lowercase and Shifted (Uppercase/Symbol) Scancode Tables
static char lowercase_map[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=','\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,'\\','z','x','c','v','b','n','m',',','.','/',0,'*',
    0,' '
};

static char shift_map[128] = {
    0,  27, '!','"','#','$','%','^','&','*','(',')','_','+','\b',
    '\t','Q','W','E','R','T','Y','U','I','O','P','{','}','\n',
    0,'A','S','D','F','G','H','J','K','L',':','@','~',
    0,'|','Z','X','C','V','B','N','M','<','>','?',0,'*',
    0,' '
};

// Convert scancode to character based on Shift state
char scan_code_to_char(uint8_t scan_code) {
    if (scan_code < 128) {
        if (shift) {
            return shift_map[scan_code];
        } else {
            return lowercase_map[scan_code];
        }
    }
    return 0;
}

// Store typed characters in a ring buffer
static void buffer_put(char c) {
    if (buffer_size < KEYBOARD_BUFFER_SIZE) {
        keyboard_buffer[buffer_head] = c;
        buffer_head = (buffer_head + 1) % KEYBOARD_BUFFER_SIZE;
        buffer_size++;
    }
}

// Read a character from the buffer
char keyboard_read_char() {
    poll_keyboard();
    if (buffer_size == 0) {
        return 0;
    }
    char c = keyboard_buffer[buffer_tail];
    buffer_tail = (buffer_tail + 1) % KEYBOARD_BUFFER_SIZE;
    buffer_size--;
    return c;
}

// Poll keyboard and process keystrokes
char poll_keyboard() {
    while (1) {
        if (inb(0x64) & 1) {
            uint8_t scan_code = inb(KEYBOARD_DATA_PORT);

            // Handle Shift Press/Release
            if (scan_code == 0x2A || scan_code == 0x36) {
                shift = 1; // Shift pressed
            } else if (scan_code == 0xAA || scan_code == 0xB6) {
                shift = 0; // Shift released
            } else {
                char c = scan_code_to_char(scan_code);
                if (c) {
                    buffer_put(c);
                    return c;
                }
            }
        }
    }
}
