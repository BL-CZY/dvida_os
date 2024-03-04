#tools
GCC:=$(if $(GCC32),$(GCC32),gcc)
LD:=$(if $(LD32),$(LD32),ld)
ASM=nasm