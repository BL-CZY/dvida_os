#tools
NASM=nasm
I686_GCC=/home/tpl/opt/cross/bin/i686-elf-gcc

#boot
BOOT_DIR=src/boot

#kernel
KERNEL_DIR=src/kernel

i686: build/os.img

build/os.img : i686_basic
	dd if=/dev/zero of=build/os.img bs=512 count=2880
	mkfs.fat -F 12 -n "NBOS" build/os.img
	dd if=build/bin/i686_bootloader.bin of=build/os.img conv=notrunc
	mcopy -i build/os.img build/bin/i686_kernel.bin "::i686_kernel.bin"

i686_basic: clear init build/bin/i686_bootloader.bin build/bin/i686_kernel.bin

build/bin/i686_kernel.bin: $(KERNEL_DIR)/kernel.c
	$(MAKE) -C $(KERNEL_DIR) i686

build/bin/i686_bootloader.bin: $(BOOT_DIR)/i686_bootloader.asm
	$(NASM) -f bin -o build/bin/i686_bootloader.bin $(BOOT_DIR)/i686_bootloader.asm

init:
	mkdir -p build/obj
	mkdir -p build/bin

clear:
	rm -f -r build