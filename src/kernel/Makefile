#tools
I686_GCC=/home/tpl/opt/cross/bin/i686-elf-gcc

#dir
BUILD_DIR=../../build
OBJ_DIR=$(BUILD_DIR)/obj

#i686 io
I686_IO_DIR=arch/i686/io

i686: $(BUILD_DIR)/bin/kernel.bin

$(BUILD_DIR)/bin/kernel.bin: kernel.c linker.ld
	$(I686_GCC) -c kernel.c -o $(OBJ_DIR)/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	$(MAKE) -C $(I686_IO_DIR)

	$(I686_GCC) -T linker.ld -o $(BUILD_DIR)/bin/kernel.bin -ffreestanding -O2 -nostdlib $(OBJ_DIR)/kernel.o $(OBJ_DIR)/io.o