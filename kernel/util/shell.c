#include "../../include/drivers/vga.h"
#include "../../include/drivers/keyboard.h"
<<<<<<< HEAD
#include "../../include/drivers/disk.h"

#include "../../include/stdlib/string.h"
#include "../../include/stdlib/printf.h"
#include "../../include/util/heap.h"
#include "../../include/util/memory.h"
=======
#include "../../include/stdlib/strcmp.h"
#include "../../include/stdlib/string.h"
#include "../../include/stdlib/printf.h"
>>>>>>> 6eea6ea (Initial commit)

#define INPUT_BUFFER_SIZE 128

// Function declarations
void shell();
void handle_command(const char *input);
void shell_prompt();
void echo_command(const char *message);
void clear_command();
void help_command();
void info_command();
<<<<<<< HEAD
void memtest_command();
void disktest_command();
void interrupttest_command();
=======
>>>>>>> 6eea6ea (Initial commit)

// Shell Main Loop
void shell() {
    char input_buffer[INPUT_BUFFER_SIZE];
    int input_index = 0;

    shell_prompt(); // Display initial prompt

    while (1) {
        //char c = poll_keyboard(); // Read a character from the keyboard
        char c = keyboard_read_char(); // Read a character from the keyboard
        if (c) {
            if (c == '\n') {
                input_buffer[input_index] = '\0'; // Null-terminate the input
                _putchar('\n'); // New line after user input
                
                // Process the command
                handle_command(input_buffer);
                
                // Reset input buffer
                input_index = 0;
                memset(input_buffer, 0, INPUT_BUFFER_SIZE);
                shell_prompt(); // Show the prompt again
            } 
            else if (c == '\b') {
                // Handle backspace
                if (input_index > 0) {
                    input_index--;
                    vga_backspace();
                }
            } 
            else {
                if (input_index < INPUT_BUFFER_SIZE - 1) {
                    input_buffer[input_index++] = c;
                    _typechar(c); // Print typed character
                }
            }
        }
    }
}

// Show Shell Prompt
void shell_prompt() {
    printf_("\n! ");
}

// Handle Commands
void handle_command(const char *input) {
<<<<<<< HEAD
    if (strcmp(input, "clior") == 0) {
=======
    if (strcmp(input, "clear") == 0) {
>>>>>>> 6eea6ea (Initial commit)
        clear_command();
    } 
    else if (strncmp(input, "radh ", 5) == 0) {
        echo_command(input + 5); // Print everything after 'radh '
    } 
    else if (strcmp(input, "help") == 0) {
<<<<<<< HEAD
        printf_("Sassenach...\n");
=======
>>>>>>> 6eea6ea (Initial commit)
        help_command();
    }
    else if (strcmp(input, "cobhair") == 0) {
        help_command();
    } 
    else if (strcmp(input, "foras") == 0) {
        info_command();
<<<<<<< HEAD
    }
    else if (strcmp(input, "memtest") == 0) {
        memtest_command();
    } 
    else if (strcmp(input, "disktest") == 0) {
        disktest_command();
    } 
    else if (strcmp(input, "inttest") == 0) {
        interrupttest_command();
=======
>>>>>>> 6eea6ea (Initial commit)
    } 
    else {
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
<<<<<<< HEAD
    printf_("  clior           - Clear the screen\n");
    printf_("  radh            - \"say\", Print a message (e.g., radh Hello)\n");
    printf_("  foras           - \"information\", Displays information about the project\n");
    printf_("  memtest         - Test the heap.\n");
    printf_("  disktest        - Test the disk driver.\n");
    printf_("  inttest         - Test interrupts.\n");
=======
    printf_("  clear           - Clear the screen\n");
    printf_("  radh            - \"say\", Print a message (e.g., radh Hello)\n");
>>>>>>> 6eea6ea (Initial commit)
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
<<<<<<< HEAD
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

void disktest_command(){
    printf_("dagdaOS: ATA PIO Disk Driver Test\n");

    uint8_t buffer[512];

    // Test reading a sector
    if (ata_read_sector(0, 1, buffer) == 0) {
        printf_("Read Success! First 16 bytes: ");
        for (int i = 0; i < 16; i++) {
            printf_("%02X ", buffer[i]);
        }
        printf_("\n");
    } else {
        printf_("Read Failed!\n");
    }

    // Test writing a sector
    for (int i = 0; i < 512; i++) buffer[i] = i % 256;  // Fill buffer with test data

    if (ata_write_sector(1, 1, buffer) == 0) {
        printf_("Write Success!\n");
    } else {
        printf_("Write Failed!\n");
    }
    return;
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
=======
 printf_("as an excercise in C and low level programming.\n");                      
>>>>>>> 6eea6ea (Initial commit)
}
