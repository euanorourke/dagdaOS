#include "../../include/interrupts/idt.h"
#include "../../include/util/memory.h"

/* Define the IDT and IDT pointer here (only in this file) */
struct idt_entry idt[IDT_ENTRIES];
struct idt_ptr idtp;

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
    idt[num].base_low = (base & 0xFFFF);
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_install() {
    idtp.limit = (sizeof(struct idt_entry) * IDT_ENTRIES) - 1;
    idtp.base = (unsigned int)&idt;

    memset(&idt, 0, sizeof(struct idt_entry) * IDT_ENTRIES);

    /* Load the new IDT */
    idt_load();
}
