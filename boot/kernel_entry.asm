bits 32

section .multiboot
    ; Multiboot Spec
    align 4
    dd 0x1BADB002      ; Magic number
    dd 0x00            ; Flags
    dd -(0x1BADB002 + 0x00) ; Checksum

global start
extern kernelMain    ; Your C kernel entry point
extern _stack_top    ; Top of the stack

start:
    cli             ; Disable interrupts
    mov esp, _stack_top  ; Set the stack pointer to the top of the stack
    call kernelMain  ; Call the C entry point
    hlt             ; Halt the CPU (should never reach here)

section .bss
align 16
kernel_stack:
    resb 16000   ; Allocate 8KB for stack
kernel_stack_top:

