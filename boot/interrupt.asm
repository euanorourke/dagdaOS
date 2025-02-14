bits 32
global isr_stub_table

section .text
extern isr_handler

; Declare the isr_stub_table as an array of ISR addresses
isr_stub_table:
    dd ISR0
    dd ISR1
    dd ISR2
    dd ISR3
    dd ISR4
    dd ISR5
    dd ISR6
    dd ISR7
    dd ISR8
    dd ISR9
    dd ISR10
    dd ISR11
    dd ISR12
    dd ISR13
    dd ISR14
    dd ISR15
    dd ISR16
    dd ISR17
    dd ISR18
    dd ISR19
    dd ISR20
    dd ISR21
    dd ISR22
    dd ISR23
    dd ISR24
    dd ISR25
    dd ISR26
    dd ISR27
    dd ISR28
    dd ISR29
    dd ISR30
    dd ISR31

; ISR stubs for interrupts 0-31
%macro ISR_STUB 1
ISR%1:
    pusha                  ; Save all general-purpose registers
    push dword %1          ; Push the interrupt number
    call isr_handler       ; Call the C handler
    add esp, 4             ; Clean up the stack (pop interrupt number)
    popa                   ; Restore registers
    iret                   ; Return from interrupt
%endmacro

ISR_STUB 0
ISR_STUB 1
ISR_STUB 2
ISR_STUB 3
ISR_STUB 4
ISR_STUB 5
ISR_STUB 6
ISR_STUB 7
ISR_STUB 8
ISR_STUB 9
ISR_STUB 10
ISR_STUB 11
ISR_STUB 12
ISR_STUB 13
ISR_STUB 14
ISR_STUB 15
ISR_STUB 16
ISR_STUB 17
ISR_STUB 18
ISR_STUB 19
ISR_STUB 20
ISR_STUB 21
ISR_STUB 22
ISR_STUB 23
ISR_STUB 24
ISR_STUB 25
ISR_STUB 26
ISR_STUB 27
ISR_STUB 28
ISR_STUB 29
ISR_STUB 30
ISR_STUB 31
