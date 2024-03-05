#tools
include ../../../../../make/common.mk

interrupt_basic : $(BUILD_DIR)/idt.o $(BUILD_DIR)/isr_c.o $(BUILD_DIR)/isr_asm.o $(BUILD_DIR)/pic.o $(BUILD_DIR)/irq.o

#dirs

$(BUILD_DIR)/idt.o : int/idt.c
	$(GCC32) -c $< -o $@ $(GCC_CONFIG)

$(BUILD_DIR)/isr_c.o : int/isr.c
	$(GCC32) -c $< -o $(BUILD_DIR)/isr_c.o $(GCC_CONFIG)

$(BUILD_DIR)/isr_asm.o : int/isr.asm
	$(ASM) $(ASM_CONFIG) $< -o $(BUILD_DIR)/isr_asm.o

$(BUILD_DIR)/pic.o : hardware/pic.c
	$(GCC32) -c $< -o $@ $(GCC_CONFIG)

$(BUILD_DIR)/irq.o : hardware/irq.c
	$(GCC32) -c $< -o $@ $(GCC_CONFIG)