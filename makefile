LIB_TARGET = libspecseek.a

CC  := gcc
AR  := ar

LIB_BIN_DIR = bin/elf
LIB_OBJ_DIR = $(LIB_BIN_DIR)/obj

C_FLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -Iinclude

SRCS = $(shell find src -name '*.c')
OBJS = $(patsubst src/%.c,$(LIB_OBJ_DIR)/%.o,$(SRCS))

# Windows cross-compilation
WIN_CC      = x86_64-w64-mingw32-gcc
WIN_AR      = x86_64-w64-mingw32-ar
WIN_BIN_DIR = bin/win
WIN_OBJ_DIR = $(WIN_BIN_DIR)/obj
WIN_OBJS    = $(patsubst src/%.c,$(WIN_OBJ_DIR)/%.o,$(SRCS))

windows: $(WIN_OBJS)
	@mkdir -p $(WIN_BIN_DIR)
	$(WIN_AR) rcs $(WIN_BIN_DIR)/$(LIB_TARGET) $(WIN_OBJS)

$(WIN_OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(WIN_CC) $(C_FLAGS) -c $< -o $@

all: $(LIB_TARGET) windows

$(LIB_TARGET): $(OBJS)
	@mkdir -p $(LIB_BIN_DIR)
	$(AR) rcs $(LIB_BIN_DIR)/$(LIB_TARGET) $(OBJS)

$(LIB_OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c $< -o $@

build: $(LIB_TARGET)

clean:
	rm -rf bin

.PHONY: all build clean windows