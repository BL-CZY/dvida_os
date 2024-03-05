#tools
include ../../make/common.mk

#src directories
GDT_DIR=arch/i686/gdt
INT_DIR=arch/i686/interrupt

i686: init $(BUILD_DIR)/i686_kernel.o

init:
	mkdir -p $(BUILD_DIR)/kernel

#build dir
OBJ_DIR=$(BUILD_DIR)/kernel

$(BUILD_DIR)/i686_kernel.o : i686_kernel_basic $(KERNEL_OBJ)
	$(LD32) -r -o $@ $(KERNEL_OBJ)
	@echo "$(YELLOW)Successfully built the i686 kernel$(RESET)"
	@echo "$(YELLOW)Clean up...$(RESET)"
	rm -r $(OBJ_DIR)
	@echo ""


i686_kernel_basic: i686_gdt i686_interrupt lib kernel_naked


i686_gdt: $(OBJ_DIR)/i686_gdt.o

$(OBJ_DIR)/i686_gdt.o : $(GDT_DIR)/Makefile
	make -C arch/i686/gdt BUILD_DIR=$(abspath $(OBJ_DIR))


i686_interrupt: $(OBJ_DIR)/i686_interrupt.o

$(OBJ_DIR)/i686_interrupt.o : $(INT_DIR)/Makefile
	make -C arch/i686/interrupt BUILD_DIR=$(abspath $(OBJ_DIR))


lib : $(OBJ_DIR)/lib.o

$(OBJ_DIR)/lib.o : lib/Makefile
	make -C lib BUILD_DIR=$(abspath $(OBJ_DIR))


kernel_naked: $(OBJ_DIR)/kernel_naked.o

$(OBJ_DIR)/kernel_naked.o: kernel.c
	$(GCC32) -c kernel.c -o $(OBJ_DIR)/kernel_naked.o $(GCC_CONFIG)

KERNEL_OBJ=$(wildcard $(OBJ_DIR)/*.o)