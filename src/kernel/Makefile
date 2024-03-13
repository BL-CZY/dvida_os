include $(MAKE_UTILS)/common.mk

.PHONY: kernel

kernel: $(BUILD_DIR)/terminal.o $(BUILD_DIR)/kernel.o

$(BUILD_DIR)/terminal.o: mod/terminal/terminal.c
	$(CC) -c $< -o $@ $(CC_FLAGS)

$(BUILD_DIR)/kernel.o: kernel.c
	$(CC) -c $< -o $@ $(CC_FLAGS)