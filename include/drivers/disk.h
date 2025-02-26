#ifndef DISK_H
#define DISK_H

#pragma pack(push, 1)
typedef struct {
    uint8_t jump[3];     // Jump instruction
    char oem[8];         // OEM Name
    uint16_t bytes_per_sector;
    uint8_t sectors_per_cluster;
    uint16_t reserved_sectors;
    uint8_t fat_count;
    uint16_t root_entries;
    uint16_t total_sectors_16;
    uint8_t media_type;
    uint16_t sectors_per_fat16;
    uint16_t sectors_per_track;
    uint16_t heads;
    uint32_t hidden_sectors;
    uint32_t total_sectors_32;
    uint32_t sectors_per_fat32;
    uint16_t flags;
    uint16_t version;
    uint32_t root_cluster;
    uint16_t fs_info;
    uint16_t backup_boot_sector;
    uint8_t reserved[12];
    uint8_t drive_number;
    uint8_t reserved1;
    uint8_t boot_signature;
    uint32_t volume_id;
    char volume_label[11];
    char fs_type[8];
} __attribute__((packed)) FAT32BootSector;
#pragma pack(pop)

void ata_irq_handler(struct regs *r);
void ata_read_sectors(uint32_t lba, uint8_t sector_count, uint16_t *buffer);
void ata_wait();
void ata_wait_for_interrupt();
void ata_enable_interrupts();

#endif