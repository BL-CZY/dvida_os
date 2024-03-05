#tools
include ../../../../../make/common.mk

OBJ_DIR=$(BUILD_DIR)/int

$(BUILD_DIR)/i686_interrupt.o : interrupt_basic $(INT_OBJ)
	$(LD32) -r -o $@ $(INT_OBJ)
	@echo "$(YELLOW)Successfully built the interrupt module"
	@echo "Clean up...$(RESET)"
	rm -r $(OBJ_DIR)
	@echo ""


interrupt_basic : init $(OBJ_DIR)/idt.o $(OBJ_DIR)/isr.o $(OBJ_DIR)/pic.o $(OBJ_DIR)/irq.o

init:
	mkdir $(BUILD_DIR)/int

#dirs

$(OBJ_DIR)/idt.o : int/idt.c
	$(GCC32) -c $< -o $@ $(GCC_CONFIG)

$(OBJ_DIR)/isr.o: int/isr.c int/isr.asm
	$(GCC32) -c $(word 1,$^) -o $(OBJ_DIR)/isr_c.o $(GCC_CONFIG)
	$(ASM) $(ASM_CONFIG) $(word 2,$^) -o $(OBJ_DIR)/isr_asm.o
	$(LD32) -r -o $@ $(OBJ_DIR)/isr_c.o $(OBJ_DIR)/isr_asm.o
	rm -r $(OBJ_DIR)/isr_c.o $(OBJ_DIR)/isr_asm.o

$(OBJ_DIR)/pic.o : hardware/pic.c
	$(GCC32) -c $< -o $@ $(GCC_CONFIG)

$(OBJ_DIR)/irq.o : hardware/irq.c
	$(GCC32) -c $< -o $@ $(GCC_CONFIG)

INT_OBJ=$(wildcard $(OBJ_DIR)/*.o)