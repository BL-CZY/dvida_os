#tools
include make/common.mk

#src directories
BOOT_DIR=src/boot
KERNEL_DIR=src/kernel

#build directories
OBJ_DIR=build/obj
BIN_DIR=build/bin

#color
YELLOW:=\033[1;33m
RESET:=\033[0m


i686: clean init i686_basic i686_combine i686_build_iso


1686_basic: i686_boot i686_kernel


i686_boot: $(OBJ_DIR)/i686_boot.o

$(OBJ_DIR)/i686_boot.o : $(OBJ_DIR)/boot_i686.asm
	$(ASM) -felf32 $< -o $@


i686_kernel: $(OBJ_DIR)/i686_kernel.o
	$(MAKE) -c src/kernel BUILD_DIR=(abspath $(OBJ_DIR))

$(OBJ_DIR)/i686_kernel.o: $(OBJ_DIR)/gdt.o $()


init:
	mkdir -p build/isodir/boot/grub
	mkdir -p build/obj
	mkdir -p build/bin
	cp make/grub.cfg build/isodir/boot/grub
	@echo "$(YELLOW)GCC is set to: $(GCC), recommand i686-elf-gcc$(RESET)"
	@echo "$(YELLOW)LD is set to: $(LD), recommand i686-elf-ld$(RESET)"

clean:
	rm -f -r build
	rm -f os.iso