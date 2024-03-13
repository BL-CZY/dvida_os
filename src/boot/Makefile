include $(MAKE_UTILS)/common.mk

SRC = $(wildcard *.asm)
#pattern substitution:
#%.asm is the pattern
#$(BUILD_DIR)/%.o is the target
#$(SRC) is the words that we want to change
OBJ = $(patsubst %.asm,$(BUILD_DIR)/%.o,$(SRC))

boot_stage1: $(OBJ)

$(BUILD_DIR)/%.o: %.asm
	$(ASM) $(ASM_FLAG) $< -o $@
	@echo -e "$(YELLOW)boot_stage1 done$(DEFAULT)"