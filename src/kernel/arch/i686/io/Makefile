#tools
I686_GCC=/home/tpl/opt/cross/bin/i686-elf-gcc
I686_LD=/home/tpl/opt/cross/bin/i686-elf-ld
NASM = nasm

#dir
BUILD_DIR=../../../../../build
OBJ_DIR=$(BUILD_DIR)/obj

$(OBJ_DIR)/io.o: io.asm io.c
	nasm -f elf32 io.asm -o $(OBJ_DIR)/io_asm.o
	$(I686_GCC) -c io.c -o $(OBJ_DIR)/io_c.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	$(I686_LD) -m elf_i386 -r $(OBJ_DIR)/io_asm.o $(OBJ_DIR)/io_c.o -o $(OBJ_DIR)/io.o