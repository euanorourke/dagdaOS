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
             $(SRC_DIR)/stdlib/printf.c $(SRC_DIR)/util/helpers.c $(SRC_DIR)/util/shell.c \
             $(SRC_DIR)/stdlib/strcmp.c $(SRC_DIR)/stdlib/strncmp.c $(SRC_DIR)/stdlib/string.c \
             $(SRC_DIR)/util/memory.c $(SRC_DIR)/util/heap.c
             

# Object Files
KERNEL_OBJ = $(BUILD_DIR)/kernel_entry.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/vga.o \
             $(BUILD_DIR)/keyboard.o $(BUILD_DIR)/printf.o $(BUILD_DIR)/helpers.o \
             $(BUILD_DIR)/shell.o $(BUILD_DIR)/strcmp.o $(BUILD_DIR)/strncmp.o \
             $(BUILD_DIR)/string.o $(BUILD_DIR)/memory.o $(BUILD_DIR)/heap.o 

# Target Files
KERNEL_BIN = $(BUILD_DIR)/kernel.bin
ISO = $(BUILD_DIR)/dagdaOS.iso

# Default Target
all: $(ISO) $(DISK_IMG)

# ======= Compilation Rules =======

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


# Compile Disk Driver
$(BUILD_DIR)/disk.o: $(SRC_DIR)/drivers/disk.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile Standard Library and Utilities
$(BUILD_DIR)/printf.o: $(SRC_DIR)/stdlib/printf.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/helpers.o: $(SRC_DIR)/util/helpers.c
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

# Compile Memory Management
$(BUILD_DIR)/memory.o: $(SRC_DIR)/util/memory.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/heap.o: $(SRC_DIR)/util/heap.c
	$(CC) $(CFLAGS) -c -o $@ $<

# ======= Linking =======

# Link Kernel
$(KERNEL_BIN): $(KERNEL_OBJ)
	$(LD) $(LDFLAGS) -T linker.ld -o $@ $^

# ======= ISO Creation =======

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

# Run in QEMU (ISO)
run-iso: $(ISO)
	qemu-system-i386 -cdrom $(ISO)

# Run in QEMU (FAT32 Disk)
run-disk: $(DISK_IMG)
	qemu-system-i386 -fda $(DISK_IMG)

# Debug in QEMU with GDB
debug: $(ISO)
	qemu-system-i386 -cdrom $(ISO) -s -S &
	gdb -ex "target remote localhost:1234" $(KERNEL_BIN)

# ======= Default Behavior =======
.PHONY: all clean run-iso run-disk debug
