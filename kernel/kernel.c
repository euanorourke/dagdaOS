#include "drivers/vga.h"
#include "drivers/keyboard.h"

#include "stdlib/printf.h"

void kernelMain(void) {
    // Initialisation
    vga_clear_screen();
    printf_("       =================================================================\n");
    printf_("       |                  dagdaOS : Build: 140225                      |\n");
    printf_("       =================================================================\n");
    printf_("\n");
    printf_("Hello world! Start typing to get started!\n");

    poll_keyboard();
    while (1) {
        char c = keyboard_read_char();
        if (c) {
            if (c == '\n') {
                printf_("\nYou pressed Enter!\n");
            } else {
                _typechar(c);
            }
        }
    }
}
