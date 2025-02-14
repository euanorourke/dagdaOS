#include "../stdlib/io.h"
#include "../include/drivers/vga.h"
#include "../include/drivers/keyboard.h"

#define KEYBOARD_DATA_PORT 0x60

// polling keyboard driver, read in from port 0x60 and convert
// scancodes to ascii

static char keyboard_buffer[KEYBOARD_BUFFER_SIZE];
static unsigned int buffer_head = 0;
static unsigned int buffer_tail = 0;

static int buffer_size = 0;

char scan_code_to_char(uint8_t scan_code){
    switch (scan_code){
        case 0x0E: return '\b'; // backspace
        case 0x1C: return '\n'; // Enter
        case 0x02: return '1';
        case 0x03: return '2';
        case 0x04: return '3';
        case 0x05: return '4';
        case 0x06: return '5';
        case 0x07: return '6';
        case 0x08: return '7';
        case 0x09: return '8';
        case 0x0A: return '9';
        case 0x0B: return '0';
        case 0x10: return 'q';
        case 0x11: return 'w';
        case 0x12: return 'e';
        case 0x13: return 'r';
        case 0x14: return 't';
        case 0x15: return 'y';
        case 0x16: return 'u';
        case 0x17: return 'i';
        case 0x18: return 'o';
        case 0x19: return 'p';
        case 0x1E: return 'a';
        case 0x1F: return 's';
        case 0x20: return 'd';
        case 0x21: return 'f';
        case 0x22: return 'g';
        case 0x23: return 'h';
        case 0x24: return 'j';
        case 0x25: return 'k';
        case 0x26: return 'l';
        case 0x2C: return 'z';
        case 0x2D: return 'x';
        case 0x2E: return 'c';
        case 0x2F: return 'v';
        case 0x30: return 'b';
        case 0x31: return 'n';
        case 0x32: return 'm';
        case 0x39: return ' '; // Space
        default: return 0;
    }
}

static void buffer_put(char c) {
    if (buffer_size < KEYBOARD_BUFFER_SIZE){
        keyboard_buffer[buffer_head] = c;
        buffer_head = (buffer_head + 1) % KEYBOARD_BUFFER_SIZE;
        buffer_size++;
        
    }

}

char keyboard_read_char() {
    if (buffer_size == 0) {
        return 0;
    }
    char c = keyboard_buffer[buffer_tail];
    buffer_tail = (buffer_tail + 1) % KEYBOARD_BUFFER_SIZE;
    buffer_size--;
    return c;
}

void poll_keyboard(){
    // Constantly check for keystrokes
    while (1){
        if (inb(0x64) & 1){
            uint8_t scan_code = inb(KEYBOARD_DATA_PORT);
            char c = scan_code_to_char(scan_code);
            if (c) {
                _typechar(c);
            }
        }


    }
}