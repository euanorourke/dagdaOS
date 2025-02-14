# Directories
SRC_DIR = kernel
BUILD_DIR = bin
ISO_DIR = $(BUILD_DIR)/iso
BOOT_DIR = boot
INCLUDE_DIR = include

# Tools
CC = gcc
AS = nasm
LD = -ld
CFLAGS = -m32 -ffreestanding -fno-stack-protector -nostdlib -I$(INCLUDE_DIR)
LDFLAGS = -m elf_i386

# Files
KERNEL_ASM = $(BOOT_DIR)/kernel_entry.asm
KERNEL_SRC = $(SRC_DIR)/kernel.c $(SRC_DIR)/drivers/vga.c $(SRC_DIR)/drivers/keyboard.c
KERNEL_OBJ = $(BUILD_DIR)/kernel_entry.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/vga.o $(BUILD_DIR)/keyboard.o $(BUILD_DIR)/printf.o $(BUILD_DIR)/helpers.o 

# Target
KERNEL_BIN = $(BUILD_DIR)/kernel.bin
ISO = $(BUILD_DIR)/dagdaOS.iso

# Rules
all: $(ISO)

$(BUILD_DIR)/kernel_entry.o: $(KERNEL_ASM)
	$(AS) -f elf -o $@ $<

$(BUILD_DIR)/kernel.o: $(SRC_DIR)/kernel.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/vga.o: $(SRC_DIR)/drivers/vga.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/keyboard.o: $(SRC_DIR)/drivers/keyboard.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/printf.o: $(SRC_DIR)/stdlib/printf.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/helpers.o: $(SRC_DIR)/stdlib/helpers.c
	$(CC) $(CFLAGS) -c -o $@ $<


$(KERNEL_BIN): $(KERNEL_OBJ) $(INTERRUPT_OBJ)
	$(LD) -m elf_i386 -T linker.ld -o $@ $^

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
clean:
	rm -rf $(BUILD_DIR)/*
	rm -rf $(BUILD_DIR)/iso