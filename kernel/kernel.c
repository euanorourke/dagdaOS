#include "drivers/vga.h"
#include "drivers/disk.h"
#include "drivers/keyboard.h"
#include "filesystem/fat32.h"
#include "util/heap.h"
#include "util/memory.h"
#include "stdlib/printf.h"
#include "util/shell.h"
#include "util/helpers.h"
#include "interrupts/isr.h"
#include "util/io.h"
#include "multiboot.h"

<<<<<<< HEAD
#define HEAP_START 0x100000  // Start heap at 1MB
#define HEAP_SIZE  0x100000  // 1MB heap size


// Function to initialize the kernel
void init(multiboot_info_t* mbd) {
    vga_clear_screen();
    printf_("Initializing Heap...\n");
    heap_init((void *)HEAP_START, HEAP_SIZE);
    printf_("Initializing Interrupts...\n");
    isr_install();
    printf_("Kernel initialized!\n");

}



void kernelMain(multiboot_info_t* mbd) {
=======
#include "util/shell.h"

void kernelMain(void) {
>>>>>>> 6eea6ea (Initial commit)
    // Initialisation
    vga_clear_screen();
    init(mbd);
    
    outb(0x21, 0xFF);  // Mask all IRQs on PIC1
    outb(0xA1, 0xFF);  // Mask all IRQs on PIC2
    __asm__ __volatile__("sti"); // enable interrupts

    
    printf_("       =================================================================\n");
<<<<<<< HEAD
    printf_("       |                  dagdaOS : Build: 210225                      |\n");
=======
    printf_("       |                  dagdaOS : Build: 180225                      |\n");
>>>>>>> 6eea6ea (Initial commit)
    printf_("       =================================================================\n");
    printf_("\n");
    printf_("Hello world! Start typing to get started!\n");

<<<<<<< HEAD
    shell();
=======
    // Ideally for the shell we want to asynchronously poll the keyboard and then deal with that in the shell program but oh well :)
    shell();
    
>>>>>>> 6eea6ea (Initial commit)
}
