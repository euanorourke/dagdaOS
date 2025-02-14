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
            . = . + 0x4000;
            _stack_top = .;
        }
    }