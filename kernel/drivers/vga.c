#include <stdint.h>
#include "../stdlib/io.h"      // For outb()
#include "../include/drivers/vga.h"

#define VGA_ADDRESS 0xB8000
#define VGA_COLUMNS 80
#define VGA_ROWS 25

static char *vga_buffer = (char *)VGA_ADDRESS;
static uint16_t cursor_x = 0;
static uint16_t cursor_y = 0;
static unsigned int cursor_position = 0;

void vga_scroll(); // Forward declaration

void vga_clear_screen() {
    for (unsigned int i = 0; i < VGA_COLUMNS * VGA_ROWS * 2; i += 2) {
        vga_buffer[i] = ' ';
        vga_buffer[i+1] = 0x1F;
    }
    cursor_position = 0;
    cursor_x = 0;
    cursor_y = 0;
}

void move_cursor() {
    uint16_t pos = cursor_y * VGA_COLUMNS + cursor_x;
    outb(0x3D4, 14);
    outb(0x3D5, (pos >> 8) & 0xFF);
    outb(0x3D4, 15);
    outb(0x3D5, pos & 0xFF);
}

void _typechar(char c) {
    static int position = 0; //pos of typed characters
    char *video_memory = (char*) 0xB8000;

    if (c == '\n') {
        cursor_position += 80 - (position % 80); // newline
    } else if (c == '\b') { 
        if (cursor_position > 0 && position > 0) {
            cursor_position--;
            position--;
            video_memory[cursor_position * 2] = ' ';
            video_memory[cursor_position * 2 + 1] = 0x1F;
        }
    } else {
        video_memory[cursor_position * 2] = c;
        video_memory[cursor_position * 2 + 1] = 0x1F;
        cursor_position++;
        position++;
    }

    if (position >= VGA_COLUMNS * VGA_ROWS) {
        vga_scroll();
        position -= VGA_COLUMNS;
    }
}

void _putchar(char c) {
    static int position = 0;
    char *video_memory = (char*) 0xB8000;

    if (c == '\n') {
        cursor_position += 80 - (cursor_position % 80); // newline
    } else {
        video_memory[cursor_position * 2] = c;
        video_memory[cursor_position * 2 + 1] = 0x1F; // White on blue colour
        cursor_position++;
    }

}

void vga_scroll() {
    for (unsigned int i = 0; i < (VGA_COLUMNS * (VGA_ROWS - 1)) * 2; i++) {
        vga_buffer[i] = vga_buffer[i + VGA_COLUMNS * 2];
    }

    for (unsigned int i = (VGA_COLUMNS * (VGA_ROWS - 1)) * 2; 
         i < VGA_COLUMNS * VGA_ROWS * 2; 
         i += 2) {
        vga_buffer[i] = ' ';
        vga_buffer[i+1] = 0x1F;
    }

    cursor_position -= VGA_COLUMNS;
}
