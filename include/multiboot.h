#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

// Magic number to identify Multiboot kernel
#define MULTIBOOT_HEADER_MAGIC 0x1BADB002

// Flags indicating available fields in `multiboot_info_t`
#define MULTIBOOT_INFO_MEMORY  0x001
#define MULTIBOOT_INFO_BOOTDEV 0x002
#define MULTIBOOT_INFO_CMDLINE 0x004
#define MULTIBOOT_INFO_MODS    0x008
#define MULTIBOOT_INFO_AOUT    0x010
#define MULTIBOOT_INFO_ELF     0x020
#define MULTIBOOT_INFO_MMAP    0x040

// Multiboot information structure (provided by GRUB)
typedef struct {
    uint16_t flags;        // Multiboot flags
    uint16_t mem_lower;    // Lower memory (in KB)
    uint16_t mem_upper;    // Upper memory (in KB)
    uint16_t boot_device;  // Boot device
    uint16_t cmdline;      // Kernel command line
    uint16_t mods_count;   // Number of modules
    uint16_t mods_addr;    // Address of module structures
    uint16_t syms[4];      // Symbol table (ELF/AOUT)
    uint16_t mmap_length;  // Memory map length
    uint16_t mmap_addr;    // Address of memory map
} __attribute__((packed)) multiboot_info_t;

// Structure representing a loaded module (e.g., initrd)
typedef struct {
    uint16_t mod_start; // Start address of module
    uint16_t mod_end;   // End address of module
    uint16_t string;    // Module name (optional)
    uint16_t reserved;  // Reserved (must be 0)
} __attribute__((packed)) multiboot_module_t;

#endif // MULTIBOOT_H
