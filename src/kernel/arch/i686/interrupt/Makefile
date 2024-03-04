#tools
include ../../../../../make/common.mk

$(BUILD_DIR)/i686_interrupt.o : interrupt_basic
	$(LD32) -r -o $@ $(BUILD_DIR)/idt.o $(BUILD_DIR)/isr.o $(BUILD_DIR)/pic.o $(BUILD_DIR)/irq.o


interrupt_basic : $(BUILD_DIR)/idt.o $(BUILD_DIR)/isr.o $(BUILD_DIR)/pic.o $(BUILD_DIR)/irq.o

$(BUILD_DIR)/idt.o : int/idt.c
	$(GCC32) -c $< -o $@ $(GCC_CONFIG)

$(BUILD_DIR)/isr.o: int/isr.c int/isr.asm
	$(GCC32) -c $(word 1,$^) -o $(BUILD_DIR)/isr_c.o $(GCC_CONFIG)
	$(ASM) $(ASM_CONFIG) $(word 2,$^) -o $(BUILD_DIR)/isr_asm.o
	$(LD32) -r -o $@ $(BUILD_DIR)/isr_c.o $(BUILD_DIR)/isr_asm.o

$(BUILD_DIR)/pic.o : hardware/pic.c
	$(GCC32) -c $< -o $@ $(GCC_CONFIG)

$(BUILD_DIR)/irq.o : hardware/irq.c
	$(GCC32) -c $< -o $@ $(GCC_CONFIG)