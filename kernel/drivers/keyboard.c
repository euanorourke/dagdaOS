#include "../../include/interrupts/irq.h"
#include "../../include/util/io.h"
#include "../../include/drivers/keyboard.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define INPUT_BUFFER_SIZE 256

#define LEFT_SHIFT_PRESSED  0x2A
#define RIGHT_SHIFT_PRESSED 0x36
#define LEFT_SHIFT_RELEASED 0xAA
#define RIGHT_SHIFT_RELEASED 0xB6


static char input_buffer[INPUT_BUFFER_SIZE];
static int buffer_start = 0;
static int buffer_end = 0;

unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};		

unsigned char kbdus_shifted[128] =
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
  '(', ')', '_', '+', '\b',	/* Backspace */
  '\t',			/* Tab */
  'Q', 'W', 'E', 'R',	/* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
  '"', '~',   0,		/* Left shift */
  '|', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
  'M', '<', '>', '?',   0,	/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};	

volatile int shift_pressed = 0;  // Track shift key state

void keyboard_handler(struct regs *r) {
    unsigned char scancode = inb(KEYBOARD_DATA_PORT);

    if (scancode == LEFT_SHIFT_PRESSED || scancode == RIGHT_SHIFT_PRESSED) {
        shift_pressed = 1; // Shift key is down
        return;
    }
    if (scancode == LEFT_SHIFT_RELEASED || scancode == RIGHT_SHIFT_RELEASED) {
        shift_pressed = 0; // Shift key is released
        return;
    }

    if (!(scancode & 0x80)) { // Key press event (not release)
        char key = shift_pressed ? kbdus_shifted[scancode] : kbdus[scancode];

        if (key) { // Valid key
            // Store key in circular buffer
            input_buffer[buffer_end] = key;
            buffer_end = (buffer_end + 1) % INPUT_BUFFER_SIZE;
        }
    }

    outb(0x20, 0x20); // Acknowledge interrupt
}

char keyboard_read_char() {
    if (buffer_start == buffer_end) {
        return 0; // Return 0 if no key is available
    }

    char key = input_buffer[buffer_start];
    buffer_start = (buffer_start + 1) % INPUT_BUFFER_SIZE;
    return key;
}