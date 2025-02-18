#include "drivers/vga.h"
#include "drivers/keyboard.h"

#include "stdlib/printf.h"

#include "util/shell.h"

void kernelMain(void) {
    // Initialisation
    vga_clear_screen();
    printf_("       =================================================================\n");
    printf_("       |                  dagdaOS : Build: 180225                      |\n");
    printf_("       =================================================================\n");
    printf_("\n");
    printf_("Hello world! Start typing to get started!\n");

    // Ideally for the shell we want to asynchronously poll the keyboard and then deal with that in the shell program but oh well :)
    shell();
    
}
