#tools
include ../../../make/common.mk

lib: init $(BUILD_DIR)/lib.o

init:
	mkdir -p $(BUILD_DIR)/lib

#dirs
OBJ_DIR=$(BUILD_DIR)/lib

$(BUILD_DIR)/lib.o : lib_basic $(OBJ_FILES)
	$(GCC32) -T $(LINKER) -o $@ $(LINK_CONFIG) $(OBJ_FILES) -lgcc
	@echo "$(YELLOW)Successfully built lib.o"
	@echo "Clean up...$(RESET)"
	rm -r $(OBJ_DIR)
	@echo ""

lib_basic: $(OBJ_DIR)/io.o $(OBJ_DIR)/keyboard.o $(OBJ_DIR)/terminalio.o $(OBJ_DIR)/compute_setting.o

$(OBJ_DIR)/io.o : io/io.c
	$(GCC32) -c $< -o $@ $(GCC_CONFIG)

$(OBJ_DIR)/keyboard.o : keyboard/keyboard.c
	$(GCC32) -c $< -o $@ $(GCC_CONFIG)

$(OBJ_DIR)/terminalio.o : terminal/terminalio.c
	$(GCC32) -c $< -o $@ $(GCC_CONFIG)

$(OBJ_DIR)/compute_setting.o : util/compute_setting.c
	$(GCC32) -c $< -o $@ $(GCC_CONFIG)

OBJ_FILES=$(wildcard $(OBJ_DIR)/*.o)