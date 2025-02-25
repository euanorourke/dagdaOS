
#include "../../include/interrupts/isr.h"
#include "../../include/interrupts/idt.h"
#include "../../include/drivers/vga.h"
#include "../../include/stdlib/printf.h"


// Give string values for each exception
char *exception_messages[] = {
    "Division by Zero",
    "Debug",
    "Non-Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bat TSS",
    "Segment not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

extern void isr_0(void);
extern void isr_1(void);
extern void isr_2(void);
extern void isr_3(void);
extern void isr_4(void);
extern void isr_5(void);
extern void isr_6(void);
extern void isr_7(void);
extern void isr_8(void);
extern void isr_9(void);
extern void isr_10(void);
extern void isr_11(void);
extern void isr_12(void);
extern void isr_13(void);
extern void isr_14(void);
extern void isr_15(void);
extern void isr_16(void);
extern void isr_17(void);
extern void isr_18(void);
extern void isr_19(void);
extern void isr_20(void);
extern void isr_21(void);
extern void isr_22(void);
extern void isr_23(void);
extern void isr_24(void);
extern void isr_25(void);
extern void isr_26(void);
extern void isr_27(void);
extern void isr_28(void);
extern void isr_29(void);
extern void isr_30(void);
extern void isr_31(void);


void default_isr() {
    printf_("Unhandled Interrupt!\n");
    while (1);
}

// Install the ISR's to the IDT
void isr_install(){
    idt_set_gate(0, (uint16_t) isr_0, 0x08, 0x8E);
    idt_set_gate(1, (uint16_t) isr_1, 0x08, 0x8E);
    idt_set_gate(2, (uint16_t) isr_2, 0x08, 0x8E);
    idt_set_gate(3, (uint16_t) isr_3, 0x08, 0x8E);
    idt_set_gate(4, (uint16_t) isr_4, 0x08, 0x8E);
    idt_set_gate(5, (uint16_t) isr_5, 0x08, 0x8E);
    idt_set_gate(6, (uint16_t) isr_6, 0x08, 0x8E);
    idt_set_gate(7, (uint16_t) isr_7, 0x08, 0x8E);
    idt_set_gate(8, (uint16_t) isr_8, 0x08, 0x8E);
    idt_set_gate(9, (uint16_t) isr_9, 0x08, 0x8E);
    idt_set_gate(10, (uint16_t) isr_10, 0x08, 0x8E);
    idt_set_gate(11, (uint16_t) isr_11, 0x08, 0x8E);
    idt_set_gate(12, (uint16_t) isr_12, 0x08, 0x8E);
    idt_set_gate(13, (uint16_t) isr_13, 0x08, 0x8E);
    idt_set_gate(14, (uint16_t) isr_14, 0x08, 0x8E);
    idt_set_gate(15, (uint16_t) isr_15, 0x08, 0x8E);
    idt_set_gate(16, (uint16_t) isr_16, 0x08, 0x8E);
    idt_set_gate(17, (uint16_t) isr_17, 0x08, 0x8E);
    idt_set_gate(18, (uint16_t) isr_18, 0x08, 0x8E);
    idt_set_gate(19, (uint16_t) isr_19, 0x08, 0x8E);
    idt_set_gate(20, (uint16_t) isr_20, 0x08, 0x8E);
    idt_set_gate(21, (uint16_t) isr_21, 0x08, 0x8E);
    idt_set_gate(22, (uint16_t) isr_22, 0x08, 0x8E);
    idt_set_gate(23, (uint16_t) isr_23, 0x08, 0x8E);
    idt_set_gate(24, (uint16_t) isr_24, 0x08, 0x8E);
    idt_set_gate(25, (uint16_t) isr_25, 0x08, 0x8E);
    idt_set_gate(26, (uint16_t) isr_26, 0x08, 0x8E);
    idt_set_gate(27, (uint16_t) isr_27, 0x08, 0x8E);
    idt_set_gate(28, (uint16_t) isr_28, 0x08, 0x8E);
    idt_set_gate(29, (uint16_t) isr_29, 0x08, 0x8E);
    idt_set_gate(30, (uint16_t) isr_30, 0x08, 0x8E);
    idt_set_gate(31, (uint16_t) isr_31, 0x08, 0x8E);
    printf_("IDT Gates Set...\n");
    // Load the IDT to the CPU
    
    

    // Enable Interrupts
    //__asm__ volatile("sti");
}

__attribute__((sysv_abi))
void isr_handler(uint16_t isr_number, uint16_t error_code){
    printf_("ISR %d triggered! Error Code: %d\n", isr_number, error_code);
    
    if (isr_number < 32) {
        printf_("Message: %s\n", exception_messages[isr_number]);  
    }
}