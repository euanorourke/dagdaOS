#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define KERNEL_CS 0x08
#define INT_ATTR 0x8E           // 0b10001110
#define IDT_ENTRIES 256

/* Defines an IDT entry */
struct idt_entry
{
    unsigned short base_low;
    unsigned short sel;        /* Our kernel segment goes here! */
    unsigned char always0;     /* This will ALWAYS be set to 0! */
    unsigned char flags;       /* Set using the above table! */
    unsigned short base_high;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/* Declare an IDT of 256 entries. Although we will only use the
*  first 32 entries in this tutorial, the rest exists as a bit
*  of a trap. If any undefined IDT entry is hit, it normally
*  will cause an "Unhandled Interrupt" exception. Any descriptor
*  for which the 'presence' bit is cleared (0) will generate an
*  "Unhandled Interrupt" exception */
extern struct idt_entry idt[IDT_ENTRIES];
extern struct idt_ptr idtp;

/* Function prototypes */
extern void idt_load();
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
void idt_install();
#endif