include $(MAKE_UTILS)/common.mk

.PHONY: kernel

kernel: $(BUILD_DIR)/time.o \
		$(BUILD_DIR)/asm_utils.o \
		$(BUILD_DIR)/handlers.o \
		$(BUILD_DIR)/keyboard_driver.o \
		$(BUILD_DIR)/terminal.o \
		$(BUILD_DIR)/kernel.o

$(BUILD_DIR)/time.o: mod/utils/time.c
	$(CC) -c $< -o $@ $(CC_FLAGS)

$(BUILD_DIR)/asm_utils.o: mod/utils/asm_utils.asm
	$(ASM) $(ASM_FLAG) $< -o $@

$(BUILD_DIR)/handlers.o: mod/interrupt/handlers.c
	$(CC) -c $< -o $@ $(CC_FLAGS)

$(BUILD_DIR)/terminal.o: mod/terminal/terminal.c
	$(CC) -c $< -o $@ $(CC_FLAGS)

$(BUILD_DIR)/keyboard_driver.o: mod/keyboard/keyboard_driver.c
	$(CC) -c $< -o $@ $(CC_FLAGS)

$(BUILD_DIR)/kernel.o: kernel.c
	$(CC) -c $< -o $@ $(CC_FLAGS)