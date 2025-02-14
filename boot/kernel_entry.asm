bits 32
    section .multiboot
     ; Multiboot Spec
     align 4
     dd 0x1BADB002 ; Magic number
     dd 0x00 ; Flags
     dd - (0x1BADB002 + 0x00) ; Checksum
    
    global start
    extern kernelMain ; Actual C file
    extern _stack_top

    start:
     cli ; clear interrupts
     mov esp, _stack_top ; Set stack pointer
     call kernelMain
     hlt ; Halts CPU

    section .bss
    resb 8192 ; 8kb of stack space
    stack_space:

