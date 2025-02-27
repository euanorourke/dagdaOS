#ifndef VGA_H
#define VGA_H

void vga_clear_screen(void);
void vga_write_string(const char *string, unsigned char color);
void vga_scroll();
void vga_backspace();
void _putchar(char c);
void _typechar(char c);
void _putchar_at(char c, int x, int y);


#endif