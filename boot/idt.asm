global idt_load   ; Allows C code to call idt_load
extern idt_pointer
extern idt_entries
extern isr_handler ; ISR handler function in C

section .text

; Load the IDT
idt_load:
    lidt [idt_pointer] ; Load IDT into CPU
    ret

; ISR Handler Stubs (for exceptions and interrupts)
%macro ISR_STUB 1
    global isr_stub%1
    isr_stub%1:
        cli                     ; Disable interrupts
        push byte 0             ; Error code placeholder if needed
        push byte %1            ; Push interrupt number
        jmp isr_common_stub
%endmacro

%macro ISR_STUB_ERR 1
    global isr_stub%1
    isr_stub%1:
        cli
        push byte %1            ; Push interrupt number
        jmp isr_common_stub
%endmacro

; Define ISRs for CPU exceptions (0-31)
ISR_STUB 0   ; Division by Zero
ISR_STUB 1   ; Debug
ISR_STUB 2   ; Non-Maskable Interrupt
ISR_STUB 3   ; Breakpoint
ISR_STUB 4   ; Overflow
ISR_STUB 5   ; Bound Range Exceeded
ISR_STUB 6   ; Invalid Opcode
ISR_STUB 7   ; Device Not Available
ISR_STUB_ERR 8  ; Double Fault (has error code)
ISR_STUB 9   ; Coprocessor Segment Overrun
ISR_STUB_ERR 10 ; Invalid TSS (has error code)
ISR_STUB_ERR 11 ; Segment Not Present (has error code)
ISR_STUB_ERR 12 ; Stack-Segment Fault (has error code)
ISR_STUB_ERR 13 ; General Protection Fault (has error code)
ISR_STUB_ERR 14 ; Page Fault (has error code)
ISR_STUB 15  ; Reserved
ISR_STUB 16  ; Floating Point Exception
ISR_STUB 17  ; Alignment Check (has error code)
ISR_STUB 18  ; Machine Check
ISR_STUB 19  ; SIMD Floating-Point Exception
ISR_STUB 20  ; Virtualization Exception
ISR_STUB 21  ; Control Protection Exception
; Interrupts 22-31 are reserved

; Define ISRs for IRQs (32-47)
%assign i 32
%rep 16
    ISR_STUB i
    %assign i i+1
%endrep

; Define a software interrupt (e.g., 0x30)
ISR_STUB 48  ; 0x30 - Custom software interrupt

; Common ISR handler
isr_common_stub:
    pusha                   ; Push all registers
    mov ax, ds
    push eax                ; Save data segment
    mov ax, 0x10            ; Load kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp                ; Pass stack pointer to C handler
    call isr_handler        ; Call the ISR handler function in C
    pop esp                 ; Restore stack pointer

    pop eax                 ; Restore data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa                    ; Restore all registers
    add esp, 8              ; Remove error code and interrupt number
    sti                     ; Re-enable interrupts
    iret                    ; Return from interrupt
