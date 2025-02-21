OUTPUT_FORMAT("elf32-i386")
ENTRY(kernel_entry)
SECTIONS
{
    . = 0x100000;
    .text : { 
        *(.multiboot) 
        *(.text) 
    }
    .data : { *(.data) }
    .bss : { *(.bss) }

    .stack ALIGN(16) : {
        _stack_bottom = .;
        . = . + 0x4000;    /* Allocate 16KB (or adjust if needed) */
        _stack_top = .;    /* Set stack top to the end of the allocated space */
    }
}
