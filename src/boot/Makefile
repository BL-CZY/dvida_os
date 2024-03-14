include $(MAKE_UTILS)/common.mk

SRC=$(wildcard *.asm)
#pattern substitution:
#%.asm is the pattern
#$(BUILD_DIR)/%.o is the target
#$(SRC) is the words that we want to change
OBJ=$(patsubst %.asm,$(BUILD_DIR)/%.o,$(SRC))

.PHONY: basic

basic: boot idt

boot: $(OBJ)

$(BUILD_DIR)/%.o: %.asm
	$(ASM) $(ASM_FLAG) $< -o $@

idt: $(BUILD_DIR)/pic.o $(BUILD_DIR)/idt.o $(BUILD_DIR)/isr_wrapper.o

$(BUILD_DIR)/pic.o: interrupt/pic.c
	$(CC) -c $< -o $@ $(CC_FLAGS)

$(BUILD_DIR)/handlers.o: interrupt/handlers.c
	$(CC) -c $< -o $@ $(CC_FLAGS)

$(BUILD_DIR)/idt.o: interrupt/idt.asm
	$(ASM) $(ASM_FLAG) $< -o $@

$(BUILD_DIR)/isr_wrapper.o: interrupt/isr_wrapper.asm
	$(ASM) $(ASM_FLAG) $< -o $@