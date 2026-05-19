LIB_TARGET = libspecseek.a

CC  := gcc
AR  := ar

LIB_BIN_DIR = bin
LIB_OBJ_DIR = $(LIB_BIN_DIR)/obj

C_FLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -Iinclude

SRCS = $(shell find src -name '*.c')
OBJS = $(patsubst src/%.c,$(LIB_OBJ_DIR)/%.o,$(SRCS))

all: $(LIB_TARGET)

$(LIB_TARGET): $(OBJS)
	@mkdir -p $(LIB_BIN_DIR)
	$(AR) rcs $(LIB_BIN_DIR)/$(LIB_TARGET) $(OBJS) 

$(LIB_OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c $< -o $@

build: $(LIB_TARGET)

clean:
	rm -rf bin

.PHONY: all build clean