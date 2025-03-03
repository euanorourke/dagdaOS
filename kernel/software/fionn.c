#include "../../include/drivers/keyboard.h"
#include "../../include/drivers/vga.h"
#include "../../include/util/io.h"

#include "../../include/stdlib/string.h"

#include "../../include/drivers/disk.h"
#include "../../include/filesystem/fat32.h"


#define TEXT_BUFFER_SIZE 8192
#define COMMAND_BUFFER_SIZE 128
#define VGA_COLUMNS 80
#define VGA_ROWS 25 // Standard VGA text mode: 80x25

/*
Fionn - A basic text editor for DagdaOS with Insert Mode and Command Mode.
*/

char text_buffer[TEXT_BUFFER_SIZE];
int text_index = 0;
int cursor_x = 0, cursor_y = 1; // Cursor for text input

enum Mode { COMMAND_MODE, INSERT_MODE };
enum Mode current_mode = COMMAND_MODE;


void update_status_bar(const char *message) {
    int status_row = VGA_ROWS - 1; // Bottom row
    int col = 0;

    // Clear the status bar
    for (col = 0; col < VGA_COLUMNS; col++) {
        _putchar_at(' ', col, status_row);
    }

    // Print message at the beginning of the status bar
    col = 0;
    while (*message && col < VGA_COLUMNS) {
        _putchar_at(*message++, col++, status_row);
    }
}

void fionn_main(string filename) {
    memset(text_buffer, 0, TEXT_BUFFER_SIZE);
    text_index = 0;
    vga_clear_screen();
    printf_("Fionn Text Editor - (Press 'i' to Insert, ':w' to save, ':q' to quit)\n");
    cursor_y = 1; // Set cursor to below the title
    cursor_x = 0;
    char command_buffer[COMMAND_BUFFER_SIZE];
    int command_index = 0;

    update_status_bar("[COMMAND MODE]");

    while (1) {
        char c = keyboard_read_char();

        if (c != 0) {
            if (current_mode == INSERT_MODE) {
                if (c == 27) { // ESC key (Exit Insert Mode)
                    current_mode = COMMAND_MODE;
                    update_status_bar("[COMMAND MODE]");
                } 
                else if (c == '\b') { // Handle backspace
                    if (text_index > 0) {
                        text_index--;
                
                        if ((text_buffer[text_index] == '\n') && cursor_y > 1) { // If deleting a newline
                            cursor_y--;
                
                            // Find the last non-newline character in the previous line
                            int prev_x = 0;
                            int i = text_index - 1;
                            while (i >= 0 && text_buffer[i] != '\n') {
                                cursor_x--;
                                i--;
                                
                            }
                
                             
                        } else if (cursor_x > 0) {
                            cursor_x--; // Normal character backspace
                            vga_backspace();
                        }
                
                        text_buffer[text_index] = '\0'; // Remove from buffer
                        vga_backspace(); // Call VGA function to update screen
                    }
                }
                
                else if (c == '\n') { // New line
                    if (text_index < TEXT_BUFFER_SIZE - 1) {
                        text_buffer[text_index++] = '\n'; // Just insert newline
                        _putchar('\n');
                        text_index++;
                        cursor_y++;
                        cursor_x = 0;
                        move_cursor();
                    }
                }
            
                else if (text_index < TEXT_BUFFER_SIZE - 1) {
                    text_buffer[text_index++] = c;
                    cursor_x++;
                    _putchar(c);
                    move_cursor();
                }
            } 
            else { // COMMAND MODE
                if (c == 'i') { // Switch to Insert Mode
                    current_mode = INSERT_MODE;
                    update_status_bar("[INSERT MODE]");
                } 
                else if (c == '\n') { // Process command
                    command_buffer[command_index] = '\0';
            
                    if (command_index == 2 && command_buffer[0] == ':' && command_buffer[1] == 'q') {
                        vga_clear_screen();
                        return; // Quit editor
                    } 
                    else if (command_index == 2 && command_buffer[0] == ':' && command_buffer[1] == 'w') {
                        FAT32BootSector boot;
                        fat32_read_boot_sector(&boot);

                        memset(text_buffer + text_index, 0, TEXT_BUFFER_SIZE - text_index);

                        text_buffer[text_index] = '\0';
                        size_t data_size = strlen(text_buffer);
                        update_status_bar("[SAVED]");
                        fat32_create_file(filename, (uint8_t *)text_buffer, data_size, &boot);
                        

                    }
            
                    command_index = 0; // Reset command buffer
                    update_status_bar("[COMMAND MODE]");
                } 
                else if (c == '\b') { // Handle backspace in command mode
                    if (command_index > 0) {
                        command_index--;
                        update_status_bar("");
                    }
                
                    // Redraw status bar to prevent it from being erased
                    update_status_bar(command_buffer);
                }
                else if (command_index < COMMAND_BUFFER_SIZE - 1) {
                    command_buffer[command_index++] = c; 
                    command_buffer[command_index] = '\0';

                    update_status_bar(command_buffer);
                }
            }
        }
    }
}
