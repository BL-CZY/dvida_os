#tools
GCC:=$(if $(GCC32),$(GCC32),gcc)
GCC_CONFIG=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
LINK_CONFIG=-ffreestanding -O2 -nostdlib
LD:=$(if $(LD32),$(LD32),ld)
ASM=nasm
ASM_CONFIG=-felf32

#color
YELLOW:=\033[1;33m
RESET:=\033[0m