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
<<<<<<< HEAD
KERNEL_SRC = $(SRC_DIR)/kernel.c $(SRC_DIR)/drivers/vga.c $(SRC_DIR)/drivers/keyboard.c \
             $(SRC_DIR)/drivers/disk.c $(SRC_DIR)/stdlib/printf.c $(SRC_DIR)/util/helpers.c $(SRC_DIR)/util/shell.c \
             $(SRC_DIR)/stdlib/string.c $(SRC_DIR)/util/memory.c $(SRC_DIR)/util/heap.c $(SRC_DIR)/filesystem/fat32.c \
             $(SRC_DIR)/util/x86.c $(SRC_DIR)/interrupts/idt.c $(SRC_DIR)/interrupts/isr.c $(SRC_DIR)/interrupts/isr_defs.asm
KERNEL_ASM = $(BOOT_DIR)/kernel_entry.asm $(SRC_DIR)/interrupts/gdt.asm  # Include gdt.asm here

# Object Files
KERNEL_OBJ = $(BUILD_DIR)/kernel_entry.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/vga.o \
             $(BUILD_DIR)/keyboard.o $(BUILD_DIR)/disk.o $(BUILD_DIR)/printf.o $(BUILD_DIR)/helpers.o \
             $(BUILD_DIR)/shell.o $(BUILD_DIR)/string.o $(BUILD_DIR)/memory.o $(BUILD_DIR)/heap.o $(BUILD_DIR)/fat32.o \
             $(BUILD_DIR)/x86.o $(BUILD_DIR)/idt.o $(BUILD_DIR)/isr.o $(BUILD_DIR)/isr_defs.o $(BUILD_DIR)/gdt.o  # Add gdt.o
=======
KERNEL_ASM = $(BOOT_DIR)/kernel_entry.asm
KERNEL_SRC = $(SRC_DIR)/kernel.c $(SRC_DIR)/drivers/vga.c $(SRC_DIR)/drivers/keyboard.c \
             $(SRC_DIR)/stdlib/printf.c $(SRC_DIR)/stdlib/helpers.c $(SRC_DIR)/util/shell.c \
             $(SRC_DIR)/stdlib/strcmp.c $(SRC_DIR)/stdlib/strncmp.c $(SRC_DIR)/stdlib/string.c

# Object Files
KERNEL_OBJ = $(BUILD_DIR)/kernel_entry.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/vga.o \
             $(BUILD_DIR)/keyboard.o $(BUILD_DIR)/printf.o $(BUILD_DIR)/helpers.o \
             $(BUILD_DIR)/shell.o $(BUILD_DIR)/strcmp.o $(BUILD_DIR)/strncmp.o $(BUILD_DIR)/string.o
>>>>>>> 6eea6ea (Initial commit)

# Target Files
KERNEL_BIN = $(BUILD_DIR)/kernel.bin
ISO = $(BUILD_DIR)/dagdaOS.iso
DISK_IMG = $(BUILD_DIR)/disk.img

# Default Target
<<<<<<< HEAD
all: $(ISO) $(DISK_IMG)

# ======= Compilation Rules =======

# Assemble Kernel Entry
$(BUILD_DIR)/kernel_entry.o: $(BOOT_DIR)/kernel_entry.asm
	mkdir -p $(BUILD_DIR)
	$(AS) -f elf -o $@ $<

# Assemble GDT
$(BUILD_DIR)/gdt.o: $(SRC_DIR)/interrupts/gdt.asm
	mkdir -p $(BUILD_DIR)
	$(AS) -f elf -o $@ $<

# Compile Kernel & Drivers
=======
all: $(ISO)

# Assemble kernel entry
$(BUILD_DIR)/kernel_entry.o: $(KERNEL_ASM)
	mkdir -p $(BUILD_DIR)
	$(AS) -f elf -o $@ $<

# Compile Kernel and Drivers
>>>>>>> 6eea6ea (Initial commit)
$(BUILD_DIR)/kernel.o: $(SRC_DIR)/kernel.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/vga.o: $(SRC_DIR)/drivers/vga.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/keyboard.o: $(SRC_DIR)/drivers/keyboard.c
	$(CC) $(CFLAGS) -c -o $@ $<

<<<<<<< HEAD
# Compile Disk Driver
$(BUILD_DIR)/disk.o: $(SRC_DIR)/drivers/disk.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile FAT32 Filesystem
$(BUILD_DIR)/fat32.o: $(SRC_DIR)/filesystem/fat32.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile Standard Library & Utilities
=======
# Compile Standard Library and Utilities
>>>>>>> 6eea6ea (Initial commit)
$(BUILD_DIR)/printf.o: $(SRC_DIR)/stdlib/printf.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/helpers.o: $(SRC_DIR)/util/helpers.c
	$(CC) $(CFLAGS) -c -o $@ $<

<<<<<<< HEAD
$(BUILD_DIR)/string.o: $(SRC_DIR)/stdlib/string.c
	$(CC) $(CFLAGS) -c -o $@ $<

=======
$(BUILD_DIR)/strcmp.o: $(SRC_DIR)/stdlib/strcmp.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/strncmp.o: $(SRC_DIR)/stdlib/strncmp.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/string.o: $(SRC_DIR)/stdlib/string.c
	$(CC) $(CFLAGS) -c -o $@ $<

>>>>>>> 6eea6ea (Initial commit)
# Compile Shell
$(BUILD_DIR)/shell.o: $(SRC_DIR)/util/shell.c
	$(CC) $(CFLAGS) -c -o $@ $<

<<<<<<< HEAD
# Compile Memory Management
$(BUILD_DIR)/memory.o: $(SRC_DIR)/util/memory.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/heap.o: $(SRC_DIR)/util/heap.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/x86.o: $(SRC_DIR)/util/x86.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/idt.o: $(SRC_DIR)/interrupts/idt.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/isr.o: $(SRC_DIR)/interrupts/isr.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/isr_defs.o: $(SRC_DIR)/interrupts/isr_defs.asm
	$(AS) -f elf -o $@ $<

# ======= Linking =======
$(KERNEL_BIN): $(KERNEL_OBJ)
	$(LD) $(LDFLAGS) -T linker.ld -o $@ $^

# ======= ISO Creation =======
=======
# Link Kernel
$(KERNEL_BIN): $(KERNEL_OBJ)
	$(LD) $(LDFLAGS) -T linker.ld -o $@ $^
>>>>>>> 6eea6ea (Initial commit)

# Copy kernel.bin to ISO folder
$(ISO_DIR)/boot/kernel.bin: $(KERNEL_BIN)
	mkdir -p $(ISO_DIR)/boot
	cp $< $@

# Copy disk.img to ISO folder (added this)
$(ISO_DIR)/boot/disk.img: $(DISK_IMG)
	mkdir -p $(ISO_DIR)/boot
	cp $< $@

# Create GRUB configuration
$(ISO_DIR)/boot/grub/grub.cfg:
	mkdir -p $(ISO_DIR)/boot/grub
	echo "set timeout=5" > $@
	echo "set default=0" >> $@
	echo "" >> $@
	echo "menuentry \"dagdaOS\" {" >> $@
	echo "    multiboot /boot/kernel.bin" >> $@
	echo "    module /boot/disk.img" >> $@
	echo "    boot" >> $@
	echo "}" >> $@

# Build the ISO
$(ISO): $(ISO_DIR)/boot/kernel.bin $(ISO_DIR)/boot/disk.img $(ISO_DIR)/boot/grub/grub.cfg
	grub-mkrescue -o $@ $(ISO_DIR)

<<<<<<< HEAD
# ======= Disk Image Creation =======

$(DISK_IMG): $(KERNEL_BIN)
# Create a larger disk image (100MB in size)
	dd if=/dev/zero of=$(DISK_IMG) bs=512 count=204800  # 100MB disk image

# Partition the disk image with GPT (EFI + main partition)
	sudo parted $(DISK_IMG) mklabel msdos
	sudo parted $(DISK_IMG) mkpart primary fat32 1MiB 99MiB

# Set up loop devices and map partitions
	sudo losetup -fP bin/disk.img
	lsblk  # Find the partition (e.g., /dev/loop0p1)
	sudo mkfs.fat -F 32 /dev/loop0p1
	sudo mount /dev/loop0p1 /mnt
	sudo mkdir -p /mnt/boot/grub
	sudo cp bin/kernel.bin /mnt/boot/kernel.bin
	sudo grub-install --target=i386-pc --boot-directory=/mnt/boot --force $(DISK_IMG)

# Create the GRUB configuration on the disk image
	sudo mkdir -p /mnt/boot/grub
	echo "set timeout=5" | sudo tee /mnt/boot/grub/grub.cfg
	echo "set default=0" | sudo tee -a /mnt/boot/grub/grub.cfg
	echo "" | sudo tee -a /mnt/boot/grub/grub.cfg
	echo "menuentry \"dagdaOS\" {" | sudo tee -a /mnt/boot/grub/grub.cfg
	echo "    multiboot /boot/kernel.bin" | sudo tee -a /mnt/boot/grub/grub.cfg
	echo "    module /boot/disk.img" | sudo tee -a /mnt/boot/grub/grub.cfg
	echo "    boot" | sudo tee -a /mnt/boot/grub/grub.cfg
	echo "}" | sudo tee -a /mnt/boot/grub/grub.cfg
	sudo touch /mnt/boot TEST
# Unmount the disk image
	sudo umount /mnt
	sudo losetup -d /dev/loop0  # Detach loop device

# Output the completion message
	echo "Disk image created at $(DISK_IMG)"

=======
>>>>>>> 6eea6ea (Initial commit)
# Clean Build Files
clean:
	rm -rf $(BUILD_DIR)/*
	rm -rf $(ISO_DIR)
<<<<<<< HEAD
	rm -f $(DISK_IMG)

# Run in QEMU (ISO)
run-iso: $(ISO)
	qemu-system-i386 -cdrom $(ISO)

# Run in QEMU (Disk Image)
run-disk: $(DISK_IMG)
	qemu-system-i386 -hda $(DISK_IMG)

# Debug in QEMU with GDB
debug: $(ISO)
	qemu-system-i386 -cdrom $(ISO) -s -S &
	gdb -ex "target remote localhost:1234" $(KERNEL_BIN)

# ======= Default Behavior =======
.PHONY: all clean run-iso run-disk debug
=======
	rm -f $(ISO)

# Run in QEMU
run: $(ISO)
	qemu-system-i386 -cdrom $(ISO)

>>>>>>> 6eea6ea (Initial commit)
