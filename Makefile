#src directories
BOOT_DIR=src/boot
KERNEL_DIR=src/kernel

#build directories
OBJ_DIR=build/obj
BIN_DIR=build/bin


i686: clean init i686_basic i686_combine build_iso


1686_basic: i686_boot i686_kernel


i686_boot: $(OBJ_DIR)/i686_boot.o

$(OBJ_DIR)/boot_i686.asm
	nasm -felf32 src/boot.asm -o build/i686_boot.o


i686_kernel: $(OBJ_DIR)/i686_kernel.o

$(OBJ_DIR)/i686_kernel.o: $(OBJ_DIR)/gdt.o $()


init:
	mkdir -p build/isodir/boot/grub
	mkdir -p build/obj
	mkdir -p build/bin
	cp grub.cfg build/isodir/boot/grub

clean:
	rm -f -r build
	rm -f os.iso