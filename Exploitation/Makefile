# Directory where shared header files are located
INCLUDES_DIR = ../Includes

# Directory where source files (.cc) are located
SRC_DIR = .

# Directory where compiled files (.o) will be stored
BUILD_DIR = build

# List of all .cc files in the source directory
SOURCES = $(wildcard $(SRC_DIR)/*.cc)

# Compiler to be used
CC = g++

# Compiler flags:
CFLAGS = -I$(INCLUDES_DIR) -Os -DBOF

all: x64 x32

x64: $(SOURCES:$(SRC_DIR)/%.cc=$(BUILD_DIR)/x64/%.o)
x32: $(SOURCES:$(SRC_DIR)/%.cc=$(BUILD_DIR)/x32/%.o)

$(BUILD_DIR)/x64/%.o: $(SRC_DIR)/%.cc
	@echo "[+] Compiling $< for x64..."
	mkdir -p $(BUILD_DIR)/x64
	$(CC) $(CFLAGS) -m64 -Wno-attributes -o $@ -c $<

$(BUILD_DIR)/x32/%.o: $(SRC_DIR)/%.cc
	@echo "[+] Compiling $< for x32..."
	mkdir -p $(BUILD_DIR)/x32
	$(CC) $(CFLAGS) -m32 -Wno-attributes -o $@ -c $<

clean:
	@echo "Cleaning up build artifacts..."
	rm -rf $(BUILD_DIR)
	@echo "Cleanup complete!"