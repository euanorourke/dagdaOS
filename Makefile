# Directories
SRC_DIR = kernel
BUILD_DIR = bin
ISO_DIR = $(BUILD_DIR)/iso
BOOT_DIR = boot
INCLUDE_DIR = include

# Tools
CC = gcc
AS = nasm
LD = ld
CFLAGS = -m32 -ffreestanding -fno-stack-protector -nostdlib -I$(INCLUDE_DIR) -O2 -Wall -Wextra
LDFLAGS = -m elf_i386

# Source Files
KERNEL_ASM = $(BOOT_DIR)/kernel_entry.asm
KERNEL_SRC = $(SRC_DIR)/kernel.c $(SRC_DIR)/drivers/vga.c $(SRC_DIR)/drivers/keyboard.c \
             $(SRC_DIR)/stdlib/printf.c $(SRC_DIR)/stdlib/helpers.c $(SRC_DIR)/util/shell.c \
             $(SRC_DIR)/stdlib/strcmp.c $(SRC_DIR)/stdlib/strncmp.c $(SRC_DIR)/stdlib/string.c

# Object Files
KERNEL_OBJ = $(BUILD_DIR)/kernel_entry.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/vga.o \
             $(BUILD_DIR)/keyboard.o $(BUILD_DIR)/printf.o $(BUILD_DIR)/helpers.o \
             $(BUILD_DIR)/shell.o $(BUILD_DIR)/strcmp.o $(BUILD_DIR)/strncmp.o $(BUILD_DIR)/string.o

# Target Files
KERNEL_BIN = $(BUILD_DIR)/kernel.bin
ISO = $(BUILD_DIR)/dagdaOS.iso

# Default Target
all: $(ISO)

# Assemble kernel entry
$(BUILD_DIR)/kernel_entry.o: $(KERNEL_ASM)
	mkdir -p $(BUILD_DIR)
	$(AS) -f elf -o $@ $<

# Compile Kernel and Drivers
$(BUILD_DIR)/kernel.o: $(SRC_DIR)/kernel.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/vga.o: $(SRC_DIR)/drivers/vga.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/keyboard.o: $(SRC_DIR)/drivers/keyboard.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile Standard Library and Utilities
$(BUILD_DIR)/printf.o: $(SRC_DIR)/stdlib/printf.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/helpers.o: $(SRC_DIR)/stdlib/helpers.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/strcmp.o: $(SRC_DIR)/stdlib/strcmp.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/strncmp.o: $(SRC_DIR)/stdlib/strncmp.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/string.o: $(SRC_DIR)/stdlib/string.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile Shell
$(BUILD_DIR)/shell.o: $(SRC_DIR)/util/shell.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Link Kernel
$(KERNEL_BIN): $(KERNEL_OBJ)
	$(LD) $(LDFLAGS) -T linker.ld -o $@ $^

# Copy kernel.bin to ISO folder
$(ISO_DIR)/boot/kernel.bin: $(KERNEL_BIN)
	mkdir -p $(ISO_DIR)/boot
	cp $< $@

# Create GRUB configuration
$(ISO_DIR)/boot/grub/grub.cfg:
	mkdir -p $(ISO_DIR)/boot/grub
	echo "set timeout=0" > $@
	echo "set default=0" >> $@
	echo "" >> $@
	echo "menuentry \"dagdaOS\" {" >> $@
	echo "    multiboot /boot/kernel.bin" >> $@
	echo "    boot" >> $@
	echo "}" >> $@

# Build the ISO
$(ISO): $(ISO_DIR)/boot/kernel.bin $(ISO_DIR)/boot/grub/grub.cfg
	grub-mkrescue -o $@ $(ISO_DIR)

# Clean Build Files
clean:
	rm -rf $(BUILD_DIR)/*
	rm -rf $(ISO_DIR)
	rm -f $(ISO)

# Run in QEMU
run: $(ISO)
	qemu-system-i386 -cdrom $(ISO)

