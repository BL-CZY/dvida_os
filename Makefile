#tools
include make/common.mk
LINKER=src/linker.ld

#src directories
BOOT_DIR=src/boot
KERNEL_DIR=src/kernel

#build directories
OBJ_DIR=build/obj
BIN_DIR=build/bin


i686: clean init i686_basic i686_combine i686_build_iso


i686_basic: i686_boot i686_kernel


i686_boot: $(OBJ_DIR)/i686_boot.o

$(OBJ_DIR)/i686_boot.o : $(BOOT_DIR)/boot_i686.asm
	$(ASM) -felf32 $< -o $@


i686_kernel: $(OBJ_DIR)/i686_kernel.o

$(OBJ_DIR)/i686_kernel.o: src/kernel/Makefile
	make -C src/kernel BUILD_DIR=$(abspath $(OBJ_DIR)) LINKER=$(abspath $(LINKER)) i686

i686_combine: $(OBJ_DIR)/i686_boot.o $(OBJ_DIR)/i686_kernel.o
	$(GCC32) -T src/linker.ld -o build/isodir/boot/os.bin $(LINK_CONFIG) $(OBJ_DIR)/i686_boot.o $(OBJ_DIR)/i686_kernel.o -lgcc

i686_build_iso:
	grub-mkrescue -o build/os.iso build/isodir

init:
	mkdir -p build/isodir/boot/grub
	mkdir -p build/obj
	mkdir -p build/bin
	cp make/grub.cfg build/isodir/boot/grub
	@echo "$(YELLOW)GCC is set to: $(GCC), recommand i686-elf-gcc$(RESET)"
	@echo "$(YELLOW)LD is set to: $(LD), recommand i686-elf-ld$(RESET)"
	@echo ""

clean:
	rm -f -r build