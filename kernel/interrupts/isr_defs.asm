; The IDT
;
; isr.asm
;

; Notify File of the External Interrupt Handler
[extern isr_handler]

; The size of the General-Purpose registers (32-bit)
REGISTER_SIZE:          equ 0x4       ; 4 bytes for 32-bit system
QUADWORD_SIZE:          equ 0x4       ; 4 bytes for 32-bit system

%macro PUSHALL 0
    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push ebp
    push esp
%endmacro

%macro POPALL 0
    pop esp
    pop ebp
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax
%endmacro

%macro SAVE_REGS_AND_CALL_HANDLER 1
    ; Save all registers since calling context is unknown
    PUSHALL

    ; Configure arguments for the method call (Using SYSV ABI)
    ; EDI Should contain the interrupt Number
    ; ESI Should contain the error code
    ; EDX Should contain the pointer to the registers (AKA the stack pointer)
    mov edx, esp
    mov edi, [esp + REGISTER_SIZE]                 ; ISR Number is last on the stack
    mov esi, [esp + REGISTER_SIZE + QUADWORD_SIZE] ; Error Code is first on the stack

    call %1

    ; Restore all registers before returning
    POPALL
%endmacro

global idt_load
extern idtp
idt_load:
    lidt [idtp]
    ret

; Interrupt Service Routine for ISR 0-7 (No Error Code)
global isr_0:
isr_0:
    cli
    push dword 0            ; No Error Code
    push dword 0            ; ISR Number 0
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8           ; 8 bytes (2 * 4 bytes) for 32-bit system
    sti
    iret

global isr_1:
isr_1:
    cli
    push dword 0            ; No Error Code
    push dword 1            ; ISR Number 1
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_2:
isr_2:
    cli
    push dword 0            ; No Error Code
    push dword 2            ; ISR Number 2
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_3:
isr_3:
    cli
    push dword 0            ; No Error Code
    push dword 3            ; ISR Number 3
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_4:
isr_4:
    cli
    push dword 0            ; No Error Code
    push dword 4            ; ISR Number 4
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_5:
isr_5:
    cli
    push dword 0            ; No Error Code
    push dword 5            ; ISR Number 5
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_6:
isr_6:
    cli
    push dword 0            ; No Error Code
    push dword 6            ; ISR Number 6
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_7:
isr_7:
    cli
    push dword 0            ; No Error Code
    push dword 7            ; ISR Number 7
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

; Special Case: ISR 8 (Usually Double Fault, no Error Code for this)
global isr_8:
isr_8:
    cli
    push dword 0            ; No Error Code (special case)
    push dword 8            ; ISR Number 8
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    ;sti
    iret

; Interrupt Service Routine for ISR 9-31 (with Error Code)
global isr_9:
isr_9:
    cli
    push dword 9            ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_10:
isr_10:
    cli
    push dword 10           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_11:
isr_11:
    cli
    push dword 11           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_12:
isr_12:
    cli
    push dword 12           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_13:
isr_13:
    cli
    push dword 13           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_14:
isr_14:
    cli
    push dword 14           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_15:
isr_15:
    cli
    push dword 15           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_16:
isr_16:
    cli
    push dword 16           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_17:
isr_17:
    cli
    push dword 17           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_18:
isr_18:
    cli
    push dword 18           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_19:
isr_19:
    cli
    push dword 19           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_20:
isr_20:
    cli
    push dword 20           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_21:
isr_21:
    cli
    push dword 21           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_22:
isr_22:
    cli
    push dword 22           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_23:
isr_23:
    cli
    push dword 23           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_24:
isr_24:
    cli
    push dword 24           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_25:
isr_25:
    cli
    push dword 25           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_26:
isr_26:
    cli
    push dword 26           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_27:
isr_27:
    cli
    push dword 27           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_28:
isr_28:
    cli
    push dword 28           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_29:
isr_29:
    cli
    push dword 29           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_30:
isr_30:
    cli
    push dword 30           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global isr_31:
isr_31:
    cli
    push dword 31           ; Error Code
    SAVE_REGS_AND_CALL_HANDLER isr_handler
    add esp, 0x8
    sti
    iret

global gdt_flush     ; Allows the C code to link to this
extern gp            ; Says that '_gp' is in another file
gdt_flush:
    lgdt [gp]        ; Load the GDT with our '_gp' which is a special pointer
    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2   ; 0x08 is the offset to our code segment: Far jump!
flush2:
    ret    

global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

; 32: IRQ0
irq0:
    cli
    push byte 0    ; Note that these don't push an error code on the stack:
                   ; We need to push a dummy error code
    push byte 32
    jmp irq_common_stub
irq1:
    cli
    push byte 0    ; Note that these don't push an error code on the stack:
                   ; We need to push a dummy error code
    push byte 33
    jmp irq_common_stub
irq2:
    cli
    push byte 0    ; Note that these don't push an error code on the stack:
                   ; We need to push a dummy error code
    push byte 34
    jmp irq_common_stub

irq3:
    cli
    push byte 0    ; Note that these don't push an error code on the stack:
                   ; We need to push a dummy error code
    push byte 35
    jmp irq_common_stub

irq4:
    cli
    push byte 0    ; Note that these don't push an error code on the stack:
                   ; We need to push a dummy error code
    push byte 36
    jmp irq_common_stub

irq5:
    cli
    push byte 0    ; Note that these don't push an error code on the stack:
                   ; We need to push a dummy error code
    push byte 37
    jmp irq_common_stub

irq6:
    cli
    push byte 0    ; Note that these don't push an error code on the stack:
                   ; We need to push a dummy error code
    push byte 38
    jmp irq_common_stub

irq7:
    cli
    push byte 0    ; Note that these don't push an error code on the stack:
                   ; We need to push a dummy error code
    push byte 39
    jmp irq_common_stub

irq8:
    cli
    push byte 0    ; Note that these don't push an error code on the stack:
                   ; We need to push a dummy error code
    push byte 40
    jmp irq_common_stub

irq9:
    cli
    push byte 0    ; Note that these don't push an error code on the stack:
                   ; We need to push a dummy error code
    push byte 41
    jmp irq_common_stub

irq10:
    cli
    push byte 0    ; Note that these don't push an error code on the stack:
                   ; We need to push a dummy error code
    push byte 42
    jmp irq_common_stub

irq11:
    cli
    push byte 0    ; Note that these don't push an error code on the stack:
                   ; We need to push a dummy error code
    push byte 43
    jmp irq_common_stub

irq12:
    cli
    push byte 0    ; Note that these don't push an error code on the stack:
                   ; We need to push a dummy error code
    push byte 44
    jmp irq_common_stub

irq13:
    cli
    push byte 0    ; Note that these don't push an error code on the stack:
                   ; We need to push a dummy error code
    push byte 45
    jmp irq_common_stub

irq14:
    cli
    push byte 0    ; Note that these don't push an error code on the stack:
                   ; We need to push a dummy error code
    push byte 46
    jmp irq_common_stub

; 47: IRQ15
irq15:
    cli
    push byte 0
    push byte 47
    jmp irq_common_stub

extern irq_handler

; This is a stub that we have created for IRQ based ISRs. This calls
; '_irq_handler' in our C code. We need to create this in an 'irq.c'
irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, irq_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret