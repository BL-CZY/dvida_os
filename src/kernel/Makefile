#tools
include ../../make/common.mk

#src directories
GDT_DIR=arch/i686/gdt
INT_DIR=arch/i686/interrupt

i686: i686_kernel_basic


i686_kernel_basic: i686_gdt i686_interrupt lib kernel_naked


i686_gdt: $(BUILD_DIR)/i686_gdt.o

$(BUILD_DIR)/i686_gdt.o : $(GDT_DIR)/Makefile
	make -C arch/i686/gdt BUILD_DIR=$(abspath $(BUILD_DIR))


i686_interrupt: $(BUILD_DIR)/i686_interrupt.o

$(BUILD_DIR)/i686_interrupt.o : $(INT_DIR)/Makefile
	make -C arch/i686/interrupt BUILD_DIR=$(abspath $(BUILD_DIR))


lib : $(BUILD_DIR)/lib.o

$(BUILD_DIR)/lib.o : lib/Makefile
	make -C lib BUILD_DIR=$(abspath $(BUILD_DIR))


kernel_naked: $(BUILD_DIR)/kernel_naked.o

$(BUILD_DIR)/kernel_naked.o: kernel.c
	$(GCC32) -c kernel.c -o $(BUILD_DIR)/kernel_naked.o $(GCC_CONFIG)

KERNEL_OBJ=$(wildcard $(BUILD_DIR)/*.o)