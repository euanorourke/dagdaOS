#include <stdint.h>
<<<<<<< HEAD
#include "../../include/util/io.h"
=======
#include "../stdlib/io.h"
>>>>>>> 6eea6ea (Initial commit)
#include "../include/drivers/vga.h"

#define VGA_ADDRESS 0xB8000
#define VGA_COLUMNS 80
#define VGA_ROWS 25

static char *vga_buffer = (char *)VGA_ADDRESS;
static uint16_t cursor_x = 0;
static uint16_t cursor_y = 0;

void vga_scroll();
void move_cursor();

// Clear the entire screen
void vga_clear_screen() {
    for (unsigned int i = 0; i < VGA_COLUMNS * VGA_ROWS * 2; i += 2) {
        vga_buffer[i] = ' ';
<<<<<<< HEAD
        vga_buffer[i + 1] = 0x1F; // white on blue
=======
        vga_buffer[i + 1] = 0x1F; // White on Blue
>>>>>>> 6eea6ea (Initial commit)
    }
    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

// Move hardware cursor
void move_cursor() {
    uint16_t pos = cursor_y * VGA_COLUMNS + cursor_x;
    outb(0x3D4, 14);
    outb(0x3D5, (pos >> 8) & 0xFF);
    outb(0x3D4, 15);
    outb(0x3D5, pos & 0xFF);
}

// Scroll the screen upwards by one line
void vga_scroll() {
    // Copy each row to the row above
    for (unsigned int i = 0; i < (VGA_COLUMNS * (VGA_ROWS - 1)) * 2; i++) {
        vga_buffer[i] = vga_buffer[i + VGA_COLUMNS * 2];
    }

    // Clear the last line
    for (unsigned int i = (VGA_COLUMNS * (VGA_ROWS - 1)) * 2; 
         i < VGA_COLUMNS * VGA_ROWS * 2; 
         i += 2) {
        vga_buffer[i] = ' ';
        vga_buffer[i + 1] = 0x1F; // White on Blue
    }

    cursor_y = VGA_ROWS - 1;
}

<<<<<<< HEAD
// Handle typing with scrolling
=======
// Handle character typing with scrolling
>>>>>>> 6eea6ea (Initial commit)
void _typechar(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\b') {
        if (cursor_x > 0) {
            cursor_x--;
            vga_buffer[(cursor_y * VGA_COLUMNS + cursor_x) * 2] = ' ';
            vga_buffer[(cursor_y * VGA_COLUMNS + cursor_x) * 2 + 1] = 0x1F;
        }
    } else {
        vga_buffer[(cursor_y * VGA_COLUMNS + cursor_x) * 2] = c;
        vga_buffer[(cursor_y * VGA_COLUMNS + cursor_x) * 2 + 1] = 0x1F;
        cursor_x++;
    }

<<<<<<< HEAD
    // Move to the next line if screen ends
=======
    // Move to the next line if end of screen
>>>>>>> 6eea6ea (Initial commit)
    if (cursor_x >= VGA_COLUMNS) {
        cursor_x = 0;
        cursor_y++;
    }

<<<<<<< HEAD
=======
    // Scroll if necessary
>>>>>>> 6eea6ea (Initial commit)
    if (cursor_y >= VGA_ROWS) {
        vga_scroll();
    }

    move_cursor();
}

// Print a single character
void _putchar(char c) {
    _typechar(c);
}

// Print a backspace
void vga_backspace() {
    if (cursor_x > 0 || cursor_y > 0) {
        if (cursor_x == 0 && cursor_y > 0) {
            cursor_y--;
            cursor_x = VGA_COLUMNS - 1;
        } else {
            cursor_x--;
        }

        vga_buffer[(cursor_y * VGA_COLUMNS + cursor_x) * 2] = ' ';
        vga_buffer[(cursor_y * VGA_COLUMNS + cursor_x) * 2 + 1] = 0x1F;
        move_cursor();
    }
}
