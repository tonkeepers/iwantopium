# Compiler and tools
CC      := gcc
AR      := ar

# Directories
PROJECT_DIR  := .
SRC_DIR      := $(PROJECT_DIR)/src
CORE_DIR     := $(SRC_DIR)/core
BRIDGE_DIR   := $(SRC_DIR)/bridge
PLATFORM_DIR := $(SRC_DIR)/platform
KERNELS_DIR  := $(SRC_DIR)/kernels
SERVICES_DIR := $(SRC_DIR)/services

# Build directories
OBJ_DIR      := $(PROJECT_DIR)/build/obj
BIN_DIR      := $(PROJECT_DIR)/build/bin
LIB_DIR      := $(PROJECT_DIR)/build/lib

# Find ALL C source files recursively from src/
SRCS := $(shell find $(SRC_DIR) -type f -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CFLAGS  := -Wall -Wextra -O3 -fPIC -march=native -D_GNU_SOURCE \
           -I$(PROJECT_DIR) \
           -I$(SRC_DIR) \
           -I$(CORE_DIR) \
           -I$(BRIDGE_DIR) \
           -I$(PLATFORM_DIR) \
           -I$(KERNELS_DIR) \
           -I$(SERVICES_DIR) \
           -pthread \
           -Wno-unused-function \
           -Wno-unused-variable

# Targets
TARGET       := $(BIN_DIR)/opium
TARGET_LIB   := $(LIB_DIR)/libopium.a

# Kernel selection (default: posix for Linux)
KERNEL ?= posix

# Add kernel-specific flags
ifeq ($(KERNEL),posix)
    CFLAGS += -DKERNEL_POSIX -I$(KERNELS_DIR)/posix
else ifeq ($(KERNEL),win)
    CFLAGS += -DKERNEL_WIN -I$(KERNELS_DIR)/win
else
    $(error Unknown kernel: $(KERNEL). Use KERNEL=posix or KERNEL=win)
endif

.PHONY: all clean run debug test lib help tree sources objects kernel-posix kernel-win

all: $(TARGET)

# Static library target
lib: $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	@mkdir -p $(LIB_DIR)
	$(AR) rcs $@ $^
	@echo "Static library built: $(TARGET_LIB)"

# Main executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -lm -o $@
	@echo "Executable built: $(TARGET) with kernel=$(KERNEL)"

# Compile object files - ВАЖНО: все .c файлы компилируются сразу
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Kernel selection shortcuts
kernel-posix:
	$(MAKE) KERNEL=posix

kernel-win:
	$(MAKE) KERNEL=win

# Commands
run: all
	@echo "Running $(TARGET)..."
	cd $(PROJECT_DIR) && ./build/bin/opium

debug: CFLAGS += -g -O0 -DDEBUG
debug: clean all

test: all
	@echo "Running tests..."
	# Add your test commands here

clean:
	rm -rf $(PROJECT_DIR)/build
	@echo "Build directory cleaned"

# Generate compile_commands.json
bear: clean
	bear -- make all

# Show project structure
tree:
	@tree -I 'build|*.o|*.a|*.so' --dirsfirst $(PROJECT_DIR)

# Show found source files
sources:
	@echo "Found source files:"
	@echo "$(SRCS)" | tr ' ' '\n'

# Show object files
objects:
	@echo "Object files to build:"
	@echo "$(OBJS)" | tr ' ' '\n'

# Show include paths
includes:
	@echo "Include paths:"
	@echo $(CFLAGS) | tr ' ' '\n' | grep -e '^-I'

# Help
help:
	@echo "Available targets:"
	@echo "  all          - Build everything (default)"
	@echo "  lib          - Build static library only"
	@echo "  kernel-posix - Build with POSIX kernel (default)"
	@echo "  kernel-win   - Build with Windows kernel"
	@echo "  run          - Build and run the executable"
	@echo "  debug        - Build with debug symbols"
	@echo "  test         - Run tests"
	@echo "  clean        - Remove build files"
	@echo "  bear         - Generate compile_commands.json"
	@echo "  tree         - Show project structure"
	@echo "  sources      - List all found source files"
	@echo "  objects      - List all object files"
	@echo "  includes     - Show include paths"
	@echo ""
	@echo "Environment variables:"
	@echo "  KERNEL=posix|win  - Select kernel (default: posix)"
