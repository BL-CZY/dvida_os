ASM=nasm
ASM_FLAG=-felf32

#CC=/home/tpl/opt/cross-i686/bin/i686-elf-gcc
# CC=$(I686_GCC)
CC=i686-elf-gcc -Wno-unknown-pragmas
#LD=/home/tpl/opt/cross-i686/bin/i686-elf-ld
# LD=$(I686_LD)
LD=i686-elf-ld
CC_FLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra

YELLOW=\033[0;33m
DEFAULT=\033[0m
