#include "../../include/drivers/vga.h"
#include "../../include/drivers/keyboard.h"
#include "../../include/stdlib/strcmp.h"
#include "../../include/stdlib/string.h"
#include "../../include/stdlib/printf.h"

#define INPUT_BUFFER_SIZE 128

// Function declarations
void shell();
void handle_command(const char *input);
void shell_prompt();
void echo_command(const char *message);
void clear_command();
void help_command();
void info_command();

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
    if (strcmp(input, "clear") == 0) {
        clear_command();
    } 
    else if (strncmp(input, "radh ", 5) == 0) {
        echo_command(input + 5); // Print everything after 'radh '
    } 
    else if (strcmp(input, "help") == 0) {
        help_command();
    }
    else if (strcmp(input, "cobhair") == 0) {
        help_command();
    } 
    else if (strcmp(input, "foras") == 0) {
        info_command();
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
    printf_("  clear           - Clear the screen\n");
    printf_("  radh            - \"say\", Print a message (e.g., radh Hello)\n");
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
