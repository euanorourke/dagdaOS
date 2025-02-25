OUTPUT_FORMAT("elf32-i386")
ENTRY(kernel_entry)
SECTIONS
{
    . = 1M;
    .text : { 
        *(.multiboot) 
        *(.text) 
    }

    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }
    .data BLOCK(4K) : ALIGN(4K) 
    { 
        *(.data) 
    }
    
    .bss BLOCK(4K) : ALIGN(4K) 
    { 
	*(COMMON)
        *(.bss) 
    }

    .stack ALIGN(16) : {
        _stack_bottom = .;
        . = . + 0x4000;    /* Allocate 16KB (or adjust if needed) */
        _stack_top = .;    /* Set stack top to the end of the allocated space */
    }
}
