#include "drivers/vga.h"
#include "drivers/disk.h"
#include "drivers/keyboard.h"
#include "filesystem/fat32.h"
#include "util/heap.h"
#include "util/memory.h"
#include "stdlib/printf.h"
#include "util/shell.h"

#include "multiboot.h"




#define HEAP_START 0x100000  // Start heap at 1MB
#define HEAP_SIZE  0x100000  // 1MB heap size

void print_memory_range(uint8_t* disk) {
    // Print first few bytes of the disk image to verify it's loaded
    printf_("First 16 bytes of disk image: ");
    for (int i = 0; i < 16; i++) {
        printf_("%02X ", disk[i]);
    }
    printf_("\n");
}

void init_disk_driver(void) {
    // Initialize the ATA controller (this will call disk_initialize)
    printf_("Initializing disk driver...\n");
    if (disk_initialize() != 0) {
        printf_("Disk initialization failed!\n");
        return;
    }

    printf_("Disk initialized successfully!\n");
}

// Function to initialize the kernel
void init(multiboot_info_t* mbd) {
    vga_clear_screen();
    printf_("Kernel initialized!\n");

    // Check if there are modules loaded by GRUB
    if (mbd->mods_count >= 0) {
        printf_("Module count: %d\n", mbd->mods_count);

        // Iterate through the modules and print their addresses
        if (mbd->mods_count > 0) {
            multiboot_module_t* modules = (multiboot_module_t*) mbd->mods_addr;
            for (uint32_t i = 0; i < mbd->mods_count; i++) {
                printf_("Module %d: Start: 0x%x, End: 0x%x\n", i, modules[i].mod_start, modules[i].mod_end);
            }
        }
    } else {
        printf_("No modules found!\n");
    }

    // Initialize FAT32 filesystem
    printf_("Initializing FAT32...\n");
    fat32_initialize((void*)1);
}



void kernelMain(multiboot_info_t* mbd) {
    // Initialisation
    init(mbd);
    print_memory_range(0);
    
    printf_("       =================================================================\n");
    printf_("       |                  dagdaOS : Build: 190225                      |\n");
    printf_("       =================================================================\n");
    printf_("\n");
    printf_("Hello world! Start typing to get started!\n");

    
    
    

    shell();
}
