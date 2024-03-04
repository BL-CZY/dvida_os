#tools
include ../../../../../make/common.mk

$(BUILD_DIR)/i686_gdt.o : gdt.asm gdt.c
	$(ASM) $(ASM_CONFIG) $(word 1,$^) -o $(BUILD_DIR)/gdt_asm.o
	$(GCC32) -c $(word 2,$^) -o $(BUILD_DIR)/gdt_c.o $(GCC_CONFIG)
	$(LD32) -r -o $@ $(BUILD_DIR)/gdt_asm.o $(BUILD_DIR)/gdt_c.o
	@echo "$(YELLOW)Successfully built the i686 gdt module$(RESET)"
	@echo "$(YELLOW)Clean up...$(RESET)"
	rm -f $(BUILD_DIR)/gdt_asm.o $(BUILD_DIR)/gdt_c.o
	@echo ""