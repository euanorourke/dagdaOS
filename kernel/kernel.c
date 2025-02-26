#include "drivers/vga.h"

#include "drivers/keyboard.h"
#include "drivers/disk.h"

#include "util/heap.h"
#include "util/memory.h"
#include "stdlib/printf.h"
#include "util/shell.h"
#include "util/helpers.h"
#include "interrupts/isr.h"
#include "interrupts/gdt.h"
#include "interrupts/irq.h"
#include "util/io.h"
#include "multiboot.h"

#define HEAP_START 0x100000  // Start heap at 1MB
#define HEAP_SIZE  0x100000  // 1MB heap size


// Function to initialize the kernel
void init(multiboot_info_t* mbd) {
    vga_clear_screen();
    printf_("Initializing Heap...\n");
    heap_init((void *)HEAP_START, HEAP_SIZE);
    printf_("Initializing Interrupts...\n");
    
    gdt_install();
    idt_install();
    isr_install();
    irq_install();
    
    printf_("Kernel initialized!\n");
    printf_("Enabling interrupts...\n");
    __asm__ __volatile__("sti");
    printf_("Enabling keyboard...\n");
    outb(0x21, inb(0x21) & ~0x02);
    irq_install_handler(1, keyboard_handler);
    // Disk IRQ

    outb(0x21, inb(0x21) & ~0x40); // Enable IRQ14 (Primary IDE)
    outb(0x21, inb(0x21) & ~0x80); // Enable IRQ15 (Secondary IDE)

    irq_install_handler(14, ata_irq_handler);
    irq_install_handler(15, ata_irq_handler);
    ata_enable_interrupts();
    //outb(0x21, 0xFF);  // Mask all IRQs on PIC1
    //outb(0xA1, 0xFF);  // Mask all IRQs on PIC2
}



void kernelMain(multiboot_info_t* mbd) {
    
    // Initialisation
    vga_clear_screen();
    init(mbd);
    
    printf_("       =================================================================\n");
    printf_("       |                  dagdaOS : Build: 250225                      |\n");
    printf_("       =================================================================\n");
    printf_("\n");
    printf_("Hello world! Start typing to get started!\n");

    __asm__ __volatile__("int $0x2E");
    shell();
}
