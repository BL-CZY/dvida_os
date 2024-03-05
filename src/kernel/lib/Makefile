#tools
include ../../../make/common.mk

lib_basic: $(BUILD_DIR)/io.o $(BUILD_DIR)/keyboard.o $(BUILD_DIR)/terminalio.o $(BUILD_DIR)/compute_setting.o

$(BUILD_DIR)/io.o : io/io.c
	$(GCC32) -c $< -o $@ $(GCC_CONFIG)

$(BUILD_DIR)/keyboard.o : keyboard/keyboard.c
	$(GCC32) -c $< -o $@ $(GCC_CONFIG)

$(BUILD_DIR)/terminalio.o : terminal/terminalio.c
	$(GCC32) -c $< -o $@ $(GCC_CONFIG)

$(BUILD_DIR)/compute_setting.o : util/compute_setting.c
	$(GCC32) -c $< -o $@ $(GCC_CONFIG)