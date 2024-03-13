include make_utils/common.mk

BUILD_DIR=build
BUILD_BOOT_DIR=build/boot
BUILD_KERNEL_DIR=build/kernel

basic: clean init boot kernel bin iso

iso:
	grub-mkrescue -o build/os.iso build/isodir

bin: $(OBJ)
	$(CC) -T src/linker.ld -o build/isodir/boot/os.bin -ffreestanding -O2 -nostdlib $(OBJ) -lgcc

boot: 
	$(MAKE) -C src/boot BUILD_DIR=$(abspath $(BUILD_DIR)) MAKE_UTILS=$(abspath make_utils)

kernel: 
	$(MAKE) -C src/kernel BUILD_DIR=$(abspath $(BUILD_DIR)) MAKE_UTILS=$(abspath make_utils)

init: grub.cfg
	mkdir -p build/isodir/boot/grub
	cp grub.cfg build/isodir/boot/grub

clean:
	rm -f -r build
	
OBJ=$(wildcard build/*.o)