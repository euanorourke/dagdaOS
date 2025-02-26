#ifndef FAT32_H
#define FAT32_H
void fat32_read_boot_sector(FAT32BootSector* boot);

uint32_t fat32_get_next_cluster(uint32_t current_cluster, FAT32BootSector *boot);

void fat32_read_file(uint32_t cluster, FAT32BootSector *boot);
void fat32_initialize_root_directory(FAT32BootSector *boot);

uint32_t fat32_find_free_directory_entry(FAT32BootSector *boot);

void fat32_list_root_directory(FAT32BootSector* boot);
void fat32_create_file(const char *filename, uint8_t *data, uint32_t size, FAT32BootSector *boot);
uint32_t fat32_find_file_cluster(const char *filename, FAT32BootSector* boot);


typedef struct {
    char filename[11];      // 8.3 format: "FILENAMEEXT"
    uint8_t attr;           // File attributes (0x20 = archive)
    uint8_t reserved;       // Reserved byte
    uint8_t create_time_tenths;
    uint16_t create_time;
    uint16_t create_date;
    uint16_t access_date;
    uint16_t high_cluster;  // High 16 bits of first cluster
    uint16_t modify_time;
    uint16_t modify_date;
    uint16_t low_cluster;   // Low 16 bits of first cluster
    uint32_t file_size;     // File size in bytes
} __attribute__((packed)) FAT32DirectoryEntry;


#endif