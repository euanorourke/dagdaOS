#include "../../include/util/io.h"
#include <stdint.h>

#define ATA_PRIMARY_BASE 0x1F0
#define ATA_CMD_READ 0x20
#define ATA_STATUS_BSY 0x80
#define ATA_STATUS_DRQ 0x08


volatile int disk_request_complete = 0;

void ata_wait() {
    while (inb(ATA_PRIMARY_BASE + 7) & ATA_STATUS_BSY); // Wait until not busy
}

void ata_read_sectors(uint32_t lba, uint8_t sector_count, uint16_t *buffer) {
    disk_request_complete = 0; // Reset completion flag
    
    // Select drive
    outb(0x1F6, 0xE0 | ((lba >> 16) & 0x0FF));

    // Send sector count and LBA
    outb(0x1F2, sector_count);
    outb(0x1F3, (uint8_t) lba);
    outb(0x1F4, (uint8_t)(lba >> 8));
    outb(0x1F5, (uint8_t)(lba >> 16));

    // Send READ command (0x20)
    outb(0x1F7, 0x20);

    // Wait for the interrupt or timeout
    ata_wait_for_interrupt();

    // Read data
    for (int i = 0; i < sector_count * 256; i++) {
        buffer[i] = inw(0x1F0);
        
    }
}

void ata_wait_for_interrupt() {
    int timeout = 1000000; // Arbitrary large value

    while (!disk_request_complete && timeout > 0) {
        __asm__ __volatile__("hlt"); // Wait for an interrupt
        timeout--;
    }

    if (timeout == 0) {
        printf_("DISK INTERRUPT TIMEOUT! Falling back to polling...\n");
        // Fall back to polling if necessary
        while (!(inb(0x1F7) & 0x08)); // Wait for "DRQ" (Data Request)
    }
}

void ata_enable_interrupts() {
    outb(0x1F1, 0x00); // Disable error reporting
    outb(0x1F6, 0xE0); // Select Master drive
    outb(0x1F2, 1);    // Set sector count to 1
    outb(0x1F3, 0);    // LBA low
    outb(0x1F4, 0);    // LBA mid
    outb(0x1F5, 0);    // LBA high
    outb(0x1F7, 0xEF); // SEND "SET FEATURES" command to enable interrupts
}

void ata_write_sectors(uint32_t lba, uint8_t sector_count, uint16_t *buffer) {
    disk_request_complete = 0;
    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F));
    outb(0x1F2, sector_count);
    outb(0x1F3, (uint8_t) lba);
    outb(0x1F4, (uint8_t)(lba >> 8));
    outb(0x1F5, (uint8_t)(lba >> 16));

    // Send the WRITE command
    outb(0x1F7, 0x30);

    // Write data to the disk
    for (int i = 0; i < sector_count * 256; i++) {
        outw(0x1F0, buffer[i]);
    }

    // Wait for completion
    while (!disk_request_complete) {
        __asm__ __volatile__("hlt");
    }
}


void ata_irq_handler(struct regs *r) {
    // Acknowledge the interrupt to the disk controller
    inb(0x1F7); // Read Status Register to clear the interrupt

    // Signal that the request is complete
    disk_request_complete = 1;
}
