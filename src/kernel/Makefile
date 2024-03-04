#tools
include ../../make/common.mk

#src directories
GDT_DIR=arch/i686/gdt
INT_DIR=arch/i686/interrupt

i686: $(BUILD_DIR)/i686_kernel.o

$(BUILD_DIR)/i686_kernel.o : i686_kernel_basic
	$(LD32) -r -o $@ $(BUILD_DIR)/i686_kernel.o $(BUILD_DIR)/i686_gdt.o $(BUILD_DIR)/i686_interrupt.o $(BUILD_DIR)/kernel_naked.o
	@echo "$(YELLOW)Successfully built the i686 kernel$(RESET)"
	@echo "$(YELLOW)Clean up...$(RESET)"
	rm -f $(BUILD_DIR)i686_gdt.o $(BUILD_DIR)i686_interrupt.o
	@echo ""


i686_kernel_basic: i686_gdt i686_interrupt kernel_naked


i686_gdt: $(BUILD_DIR)/i686_gdt.o

$(BUILD_DIR)/i686_gdt.o : $(GDT_DIR)/Makefile
	make -C arch/i686/gdt BUILD_DIR=$(abspath $(BUILD_DIR))


i686_interrupt: $(BUILD_DIR)/i686_interrupt.o

$(BUILD_DIR)/i686_interrupt.o : $(INT_DIR)/Makefile
	make -C arch/i686/interrupt BUILD_DIR=$(abspath $(BUILD_DIR))


kernel_naked: $(BUILD_DIR)/kernel_naked.o

$(BUILD_DIR)/kernel_naked.o: $(BUILD_DIR)/kernel.c
	$(GCC32) -c kernel.c -o $(BUILD_DIR)/kernel_naked.o $(GCC_CONFIG)