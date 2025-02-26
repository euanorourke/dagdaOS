#include "../../include/util/io.h"
#include "../../include/drivers/disk.h"
#include "../../include/filesystem/fat32.h"
#include "../../include/util/memory.h"
#include "../../include/util/io.h"

#define SECTOR_SIZE 512
#define FAT32_EOF 0x0FFFFFF8

void fat32_read_boot_sector(FAT32BootSector* boot) {
    uint8_t buffer[SECTOR_SIZE];  // FAT32 uses 512-byte sectors

    printf_("Reading boot sector...\n");
    ata_read_sectors(2048, 1, buffer);  // Read sector 0 (MBR or Boot Sector)

    memcpy(boot, buffer, sizeof(FAT32BootSector));
/*
    printf_("\nFAT32 Boot Sector:\n");
    printf_("Bytes per sector: %d\n", boot->bytes_per_sector);
    printf_("Sectors per cluster: %d\n", boot->sectors_per_cluster);
    printf_("Reserved sectors: %d\n", boot->reserved_sectors);
    printf_("FAT count: %d\n", boot->fat_count);
    printf_("Sectors per FAT: %d\n", boot->sectors_per_fat32);
    printf_("Root cluster: %d\n", boot->root_cluster);
*/
}


// Reads the next cluster from the FAT table
uint32_t fat32_get_next_cluster(uint32_t current_cluster, FAT32BootSector *boot) {
    uint16_t buffer[SECTOR_SIZE / 2]; 
    uint32_t fat_sector = boot->reserved_sectors + (current_cluster * 4) / SECTOR_SIZE;
    uint32_t fat_offset = (current_cluster * 4) % SECTOR_SIZE;

    // Read the FAT sector
    ata_read_sectors(fat_sector, 1, buffer);

    return (*(uint32_t*) ((uint8_t*)buffer + fat_offset)) & 0x0FFFFFFF; // Mask out high bits
}

// Reads a file starting from a given cluster
void fat32_read_file(uint32_t cluster, FAT32BootSector *boot) {
    uint16_t buffer[SECTOR_SIZE / 2];  // Buffer to store sector data

    while (cluster < FAT32_EOF) {  // Keep reading until end of file
        uint32_t sector = boot->reserved_sectors + (boot->fat_count * boot->sectors_per_fat32) +
                          ((cluster - 2) * boot->sectors_per_cluster);

        for (uint32_t i = 0; i < boot->sectors_per_cluster; i++) {
            ata_read_sectors(sector + i, 1, buffer);
            
        }

        cluster = fat32_get_next_cluster(cluster, boot);
    }
}


void fat32_list_root_directory(FAT32BootSector* boot) {
    uint8_t buffer[SECTOR_SIZE];
    uint32_t cluster = boot->root_cluster;

    printf_("Root Directory (starting at cluster %d):\n", cluster);

    if (cluster < 2) {
        printf_("Error: Invalid root cluster %d\n", cluster);
        return;
    }

    while (cluster < FAT32_EOF) {
        uint32_t first_data_sector = boot->reserved_sectors + (boot->fat_count * boot->sectors_per_fat32);
        uint32_t sector = first_data_sector + (cluster - 2) * boot->sectors_per_cluster;

        printf_("Reading sector: %d (Cluster %d)\n", sector, cluster);

        for (int i = 0; i < boot->sectors_per_cluster; i++) {
            ata_read_sectors(sector + i, 1, buffer);

            for (int j = 0; j < SECTOR_SIZE; j += 32) {
                if (buffer[j] == 0x00) {
                    printf_("End of directory entries found.\n");
                    return;
                }
                if (buffer[j] != 0xE5) {  // Not deleted
                    char name[12] = {0};
                    memcpy(name, buffer + j, 11);
                    printf_("File: %s\n", name);
                }
            }
        }

        cluster = fat32_get_next_cluster(cluster, boot);
    }
}

void fat32_initialize_root_directory(FAT32BootSector* boot) {
    uint8_t buffer[SECTOR_SIZE] = {0};  // Empty sector
    uint32_t first_data_sector = boot->reserved_sectors + (boot->fat_count * boot->sectors_per_fat32);
    uint32_t root_dir_sector = first_data_sector + ((boot->root_cluster - 2) * boot->sectors_per_cluster);

    ata_write_sectors(root_dir_sector, 1, buffer);
}


// Find a free cluster in the FAT
uint32_t fat32_find_free_cluster(FAT32BootSector *boot) {
    uint16_t buffer[SECTOR_SIZE / 2];  // Buffer for one sector of the FAT
    uint32_t fat_sector = boot->reserved_sectors;
    
    for (uint32_t cluster = 2; cluster < 0x0FFFFFF0; cluster++) {
        uint32_t sector = fat_sector + (cluster * 4) / SECTOR_SIZE;
        uint32_t offset = (cluster * 4) % SECTOR_SIZE;

        ata_read_sectors(sector, 1, buffer);
        uint32_t entry = *(uint32_t*)((uint8_t*)buffer + offset) & 0x0FFFFFFF;

        if (entry == 0x00000000) {
            return cluster;  // Found a free cluster
        }
    }
    
    return 0xFFFFFFFF;  // No free space found
}

void fat32_write_file(uint8_t *data, uint32_t size, FAT32BootSector *boot) {
    uint32_t first_cluster = fat32_find_free_cluster(boot);
    if (first_cluster == 0xFFFFFFFF) {
        printf_("No free space available!\n");
        return;
    }

    

    uint16_t buffer[SECTOR_SIZE / 2];
    uint32_t current_cluster = first_cluster;
    uint32_t bytes_written = 0;

    while (bytes_written < size) {
        uint32_t sector = boot->reserved_sectors + (boot->fat_count * boot->sectors_per_fat32) +
                          ((current_cluster - 2) * boot->sectors_per_cluster);
        
        memset(buffer, 0, SECTOR_SIZE);
        memcpy(buffer, data + bytes_written, SECTOR_SIZE);

        ata_write_sectors(sector, 1, buffer);
        
        bytes_written += SECTOR_SIZE;

        if (bytes_written < size) {
            uint32_t next_cluster = fat32_find_free_cluster(boot);
            if (next_cluster == 0xFFFFFFFF) {
                printf_("Disk full!\n");
                return;
            }

            // Update FAT
            uint32_t fat_sector = boot->reserved_sectors + (current_cluster * 4) / SECTOR_SIZE;
            uint32_t fat_offset = (current_cluster * 4) % SECTOR_SIZE;
            
            ata_read_sectors(fat_sector, 1, buffer);
            *(uint32_t*)((uint8_t*)buffer + fat_offset) = next_cluster;
            ata_write_sectors(fat_sector, 1, buffer);
            //Debug
            ata_read_sectors(fat_sector, 1, buffer);
            


            current_cluster = next_cluster;
        }
    }

    // Mark last cluster as EOF
    uint32_t fat_sector = boot->reserved_sectors + (current_cluster * 4) / SECTOR_SIZE;
    uint32_t fat_offset = (current_cluster * 4) % SECTOR_SIZE;
    
    
    ata_read_sectors(fat_sector, 1, buffer);
    *(uint32_t*)((uint8_t*)buffer + fat_offset) = FAT32_EOF;
    ata_write_sectors(fat_sector, 1, buffer);

}
 

uint32_t fat32_find_free_directory_entry(FAT32BootSector* boot) {
    uint8_t buffer[SECTOR_SIZE];
    uint32_t first_data_sector = (uint32_t) boot->reserved_sectors + ((uint32_t) boot->fat_count * (uint32_t)boot->sectors_per_fat32);
    uint32_t root_dir_sector = first_data_sector + ((uint32_t) boot->root_cluster - 2) * ((uint32_t)boot->sectors_per_cluster);

    for (uint32_t i = 0; i < boot->sectors_per_cluster; i++) {
        ata_read_sectors(root_dir_sector + i, 1, buffer);

        for (int j = 0; j < SECTOR_SIZE; j += 32) {
            if (buffer[j] == 0x00 || buffer[j] == 0xE5) {  // Free entry found
                return root_dir_sector + i;
            }
        }
    }

    printf_("No free directory entry found!\n");
    return 0xFFFFFFFF;
}

void fat32_create_file(const char *filename, uint8_t *data, uint32_t size, FAT32BootSector *boot) {

    // Find a free cluster for file data
    uint32_t first_cluster = fat32_find_free_cluster(boot);
    if (first_cluster == 0xFFFFFFFF) {
        printf_("No free space available!\n");
        return;
    }


    // Find a free directory entry
    uint32_t dir_sector = fat32_find_free_directory_entry(boot);
    if (dir_sector == 0xFFFFFFFF) {
        printf_("No space in root directory!\n");
        return;
    }

    // Read the directory sector
    uint16_t buffer[SECTOR_SIZE / 2];  // Correct type
    ata_read_sectors(dir_sector, 1, buffer);

    // Find the exact free entry inside the sector
    int entry_offset = -1;
    for (int j = 0; j < SECTOR_SIZE; j += 32) {
        if (((uint8_t*)buffer)[j] == 0x00 || ((uint8_t*)buffer)[j] == 0xE5) {
            entry_offset = j;
            break;
        }
    }

    if (entry_offset == -1) {
        printf_("No free directory entry in sector!\n");
        return;
    }

    // Fill directory entry
    FAT32DirectoryEntry entry;
    memset(&entry, 0, sizeof(FAT32DirectoryEntry));
    memcpy(entry.filename, filename, 11);
    entry.attr = 0x20;  // Archive
    entry.low_cluster = first_cluster & 0xFFFF;
    entry.high_cluster = (first_cluster >> 16) & 0xFFFF;
    entry.file_size = size;

    // Copy the entry into the correct position in the sector
    memcpy(((uint8_t*)buffer) + entry_offset, &entry, sizeof(FAT32DirectoryEntry));

    // Write the updated directory sector back
    ata_write_sectors(dir_sector, 1, buffer);

    // Write file data
    fat32_write_file(data, size, boot);
}
