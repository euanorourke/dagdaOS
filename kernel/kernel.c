#include "drivers/vga.h"
#include "drivers/keyboard.h"
#include "util/heap.h"
#include "util/memory.h"

#include "stdlib/printf.h"

#include "util/shell.h"



#define HEAP_START 0x100000  // Start heap at 1MB
#define HEAP_SIZE  0x100000  // 1MB heap size

void init(){
    printf_("Initialising heap...");
    heap_init((void *)HEAP_START, HEAP_SIZE);
}

void kernelMain(void) {
    // Initialisation
    init();

    vga_clear_screen();
    printf_("       =================================================================\n");
    printf_("       |                  dagdaOS : Build: 180225                      |\n");
    printf_("       =================================================================\n");
    printf_("\n");
    printf_("Hello world! Start typing to get started!\n");

    // Ideally for the shell we want to asynchronously poll the keyboard and then deal with that in the shell program but oh well :)
    shell();
    
    
}


