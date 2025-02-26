#include "../../include/drivers/vga.h"
#include "../../include/drivers/keyboard.h"
#include "../../include/drivers/disk.h"

#include "../../include/stdlib/string.h"
#include "../../include/stdlib/printf.h"
#include "../../include/util/heap.h"
#include "../../include/util/memory.h"
#include "../../include/filesystem/fat32.h"

#define INPUT_BUFFER_SIZE 128

// Function declarations
void shell();
void handle_command(const char *input);
void shell_prompt();
void echo_command(const char *message);
void clear_command();
void help_command();
void info_command();
void disktest_command();
void memtest_command();
void fat32_test_command();
void create_file_command();

void interrupttest_command();

// Shell Main Loop
void shell() {
    char input_buffer[INPUT_BUFFER_SIZE];
    int input_index = 0;

    shell_prompt(); // Display initial prompt

    while (1) {
        char c = keyboard_read_char();

        if (c != 0) { // Only process if a valid key is available
            if (c == '\n') {  // If Enter is pressed, process the command
                
                input_buffer[input_index] = '\0'; // Null-terminate string
                handle_command(input_buffer);
                input_index = 0; // Reset input index
                shell_prompt();  // Show prompt again
            } 
            else if (c == '\b') { // Handle backspace
                if (input_index > 0) { // Ensure we don't erase the prompt
                    input_index--;
                    printf_("\b \b"); // Erase character from screen
                }
            } 
            else if (input_index < INPUT_BUFFER_SIZE - 1) {
                input_buffer[input_index++] = c; // Store character
                _putchar(c); // Print character to screen
            }
        }input_buffer[input_index] = '\n';
    }
}

// Show Shell Prompt
void shell_prompt() {
    printf_("\n! ");
}

// Handle Commands
void handle_command(const char *input) {
    if (strcmp(input, "clior") == 0) {
        clear_command();
    } 
    else if (strncmp(input, "radh ", 5) == 0) {
        _putchar('\n');
        echo_command(input + 5); // Print everything after 'radh '
    } 
    else if (strcmp(input, "help") == 0) {
        _putchar('\n');
        printf_("Sassenach...\n");
        help_command();
    }
    else if (strcmp(input, "cobhair") == 0) {
        _putchar('\n');
        help_command();
    } 
    else if (strcmp(input, "foras") == 0) {
        _putchar('\n');
        info_command();
    }
    else if (strcmp(input, "memtest") == 0) {
        _putchar('\n');
        memtest_command();
    } 
    else if (strcmp(input, "disktest") == 0) {
        _putchar('\n');
        disktest_command();
    } 
    else if (strcmp(input, "inttest") == 0) {
        _putchar('\n');
        interrupttest_command();
    } 
    else if (strcmp(input, "fat32test") == 0) {
        _putchar('\n');
        fat32test_command();
    } 
    else if (strcmp(input, "reumh") == 0) {
        _putchar('\n');
        root_command();
    } 
    else if (strncmp(input, "faidhle ", 8) == 0) {
        _putchar('\n');
        create_file_command(input + 8);
    } 
    else {
        _putchar('\n');
        printf_("Unknown command: %s\n", input);
    }
}

// Commands
void echo_command(const char *message) {
    printf_("%s\n", message);
}

void clear_command() {
    vga_clear_screen();
}

void help_command() {
    printf_("Available commands:\n");
    printf_("  cobhair/help    - Show available commands\n");
    printf_("  clior           - Clear the screen\n");
    printf_("  radh            - \"say\", Print a message (e.g., radh Hello)\n");
    printf_("  foras           - \"information\", Displays information about the project\n");
    printf_("  memtest         - Test the heap.\n");
    printf_("  disktest        - Test the disk driver.\n");
    printf_("  inttest         - Test interrupts.\n");
    printf_("  reumh           - Show the root directory.\n");
    printf_("  faidhle         - Create an empty file.\n");
}

void info_command() {
    printf_("       _                 _         ___  __    \n");
    printf_("    __| | __ _  __ _  __| | __ _  /___\\/ _\\   \n");
    printf_("   / _` |/ _` |/ _` |/ _` |/ _` |//  //\\ \\    \n");
    printf_("  | (_| | (_| | (_| | (_| | (_| / \\_// _\\ \\   \n");
    printf_("   \\__,_|\\__,_|\\__, |\\__,_|\\__,_\\___/  \\__/   \n");
    printf_("               |___/                          \n");
    printf_("-----------------------------------------------\n");
    printf_("The \"Dagda\" is one of the leaders of a mythological\n");
    printf_("Irish people and is an important figure in Celtic\n");    
    printf_("mythology.");
    printf_("\n");
    printf_("dagdaOS is a hobby operating system that uses\n");
    printf_("Scottish Gaelic as an inspiration for system commands.\n");
    printf_("This OS is not intended for daily use, it is written\n");
    printf_("as an excercise in C and low level programming.\n");
                        
   }

void memtest_command(){
    char *test = (char *)malloc(50);
    if (test) {
        printf_("Memory Allocated!\n");
        memcpy(test, "Hello from heap!", 17);
        printf_(test);
        free(test);
        printf_("\nMemory Freed.\n");
    } else {
        printf_("Memory Allocation Failed!\n");
    }
}


void interrupttest_command(){
    struct {
        uint16_t limit;
        uint32_t base;
    } __attribute__((packed)) idtr;

    printf_("dagdaOS: Interrupt Test\n");
    __asm__ __volatile__("sidt %0" : "=m"(idtr));  // Store IDT register
    printf("IDT Base: 0x%x, Limit: 0x%x\n", idtr.base, idtr.limit);
    printf("-Interrupt 1-\n");
    __asm__ __volatile__("int $0x01");
    printf("-Interrupt 2-\n");
    __asm__ __volatile__("int $0x02");
    printf("-Interrupt 3-\n");
    __asm__ __volatile__("int $0x03");
    printf("-Interrupt 4-\n");
    __asm__ __volatile__("int $0x04");
    printf("-Interrupt 5-\n");
    __asm__ __volatile__("int $0x05");
    printf("-Interrupt 6-\n");
    __asm__ __volatile__("int $0x06");
    printf("-Interrupt 7-\n");
    __asm__ __volatile__("int $0x07");
    printf("-Interrupt 8-\n");
    __asm__ __volatile__("int $0x08");
    printf("-Interrupt 9-\n");
    __asm__ __volatile__("int $0x09");
    printf("-Interrupt 10-\n");
    __asm__ __volatile__("int $0x0A");
    printf("-Interrupt 11-\n");
    __asm__ __volatile__("int $0x0B");
    printf("-Interrupt 12-\n");
    __asm__ __volatile__("int $0x0C");
    printf("-Interrupt 13-\n");
    __asm__ __volatile__("int $0x0D");
    printf("-Interrupt 14-\n");
    __asm__ __volatile__("int $0x0E");
    printf("-Interrupt 15-\n");
    __asm__ __volatile__("int $0x0F");
    printf("-Interrupt 16-\n");
    __asm__ __volatile__("int $0x11");
    printf("-Interrupt 17-\n");
    __asm__ __volatile__("int $0x12");
    printf("-Interrupt 18-\n");
    __asm__ __volatile__("int $0x13");
    return;

}

void disktest_command() {
    uint16_t buffer[256];  // One sector (512 bytes = 256 * 2-byte words)

    // Read sector 10
    ata_read_sectors(10, 1, buffer);
    printf_("Read completed!\n");

    // Print sector data in hexadecimal format
    printf_("Sector Data:\n");
    for (int i = 0; i < 16; i++) {
        printf_("%04x ", buffer[i]); // Print 16-bit values as hex
        if ((i + 1) % 8 == 0) {
            printf_("\n");  // Newline every 8 words
        }
    }
    printf_("\n");

    // Modify data and write it back
    buffer[0] = 0x1234; // Modify the first word
    ata_write_sectors(10, 1, buffer);
    printf_("Write completed!\n");
}

void fat32test_command() {
    FAT32BootSector boot;
    fat32_read_boot_sector(&boot);
    fat32_initialize_root_directory(&boot);
    printf_("Writing to disk...\n");

    char data[] = "Testing FAT32 write!";
    
    fat32_create_file("HELLO  TXT", (uint8_t*)data, sizeof(data), &boot);
    
    printf_("File write complete! Listing root directory...\n");
    
    fat32_list_root_directory(&boot);
}

void root_command() {
    FAT32BootSector boot;
    fat32_read_boot_sector(&boot);
    fat32_list_root_directory(&boot);
}

void create_file_command(string filename){
    FAT32BootSector boot;
    fat32_read_boot_sector(&boot);
    char data[] = "";
    


    fat32_create_file(filename, (uint8_t*)data, sizeof(data), &boot);
    printf_("%s written to root. \n", filename);
}